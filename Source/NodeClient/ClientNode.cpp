/*
This project is licensed under the GNU GPL 2.0 license. Please respect that.

Initial author: (https://github.com/)Sokie
Started: 11-06-2015
Notes
This handles connection to a server node
*/

#include "..\STDInclude.h"

#define waitTimeout 5
namespace Nodes
{
	hAddress ClientNode::serverNode = hAddress::hAddress();
	uint32_t ClientNode::sequenceID = 0;
	bool ClientNode::isSNodeConnected = false;
	HANDLE ClientNode::sNodeDiscoveryThread;
	HANDLE ClientNode::sPacketReceiverThread;
	std::mutex ClientNode::mutex;
	std::unordered_map<uint32_t, std::shared_ptr<ByteBuffer>> ClientNode::pendingData;
	HedgeNodeProto::SteamFriendsResult* ClientNode::result;

	DWORD _stdcall ClientNode::NodeDiscoverySender(void  *lparam)
	{
		uint16_t port = 20000;
		Network::SocketManager::Create_UDP(&port, false);

		DBGPrint("Searching for sNode");

		char recvBuffer[1024] = { 0 };
		while (true)
		{
			Network::PingPacket pingPacket;
			pingPacket.isAnonymous = true;
			pingPacket.isAuthenticated = false;
			pingPacket.SessionID = rand();
			pingPacket.username = Global::Steam_Username;
			SetNetworkData(&pingPacket, HNPingRequest);

			ByteBuffer pingBuffer = ByteBuffer::ByteBuffer();
			pingPacket.Serialize(&pingBuffer);

			Network::SocketManager::Send_UDPBroadcast(31337, pingBuffer.GetLength(), pingBuffer.GetBuffer<void>());

			int len = Network::SocketManager::Receive_UDP(port, 1024, recvBuffer, &serverNode);
			if (len > 0)
			{
				serverNode.Port = 31337;
				DBGPrint("Found sNode, stopping...");
				isSNodeConnected = true;
				sPacketReceiverThread = CreateThread(NULL, NULL, NodePacketReceiver, NULL, NULL, NULL);
				CreateThread(NULL, NULL, FriendDiscoveryThread, NULL, NULL, NULL);
				break;
			}
			Sleep(2000);
		}

		return 0;
	}

	void ClientNode::SetNetworkData(Network::NetworkPacket *inPacket, EventType eventType){
		inPacket->ApplicationID = Global::Steam_AppID;
		inPacket->ClientID = Global::Steam_UserID;
		inPacket->eventType = eventType;
		inPacket->SequenceID = GetSequence();
		inPacket->TimeStamp = time(NULL);
	}

	DWORD _stdcall ClientNode::NodePacketReceiver(void  *lparam)
	{
		uint16_t port = 20000;

		char recvBuffer[1024] = { 0 };
		hAddress sender = hAddress::hAddress();

		while (true)
		{
			int32_t len = Network::SocketManager::Receive_UDP(port, 1024, recvBuffer, &sender);
			if (len > 0)
			{

				ByteBuffer *packetBuffer = new ByteBuffer(len, (void*)recvBuffer);
				Network::NetworkPacket packet;
				packet.Deserialize(packetBuffer);

				mutex.lock();
				pendingData[packet.SequenceID] = std::shared_ptr<ByteBuffer>(packetBuffer);
				mutex.unlock();
			}

			Sleep(100);
		}

		return 0;
	}

	bool ClientNode::InitializeNode(){
		sequenceID = 0;
		result = new HedgeNodeProto::SteamFriendsResult();
		sNodeDiscoveryThread = CreateThread(NULL, NULL, NodeDiscoverySender, NULL, NULL, NULL);
		return true;
	}

	uint32_t ClientNode::GetSequence()
	{
		mutex.lock();
		++sequenceID;
		mutex.unlock();
		return sequenceID;
	}

	int32_t ClientNode::GetFriendCount(int32_t iFriendFlags)
	{
		return result->steamfriendinfo_size();
	}

	uint64_t ClientNode::GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags)
	{
		return result->steamfriendinfo(iFriend).clientid();
	}

	void ClientNode::GetFriends(){
		

		if (!isSNodeConnected)
		{
			return;
		}
		Network::NetworkPacket packet;

		SetNetworkData(&packet, HNFriendsProtoRequest);

		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		packet.Serialize(&packetBuffer);

		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());

		time_t t1 = time(0);

		while (true)
		{
			if (difftime(time(0), t1) > waitTimeout)
			{
				break;
			}

			mutex.lock();
			std::unordered_map<uint32_t, std::shared_ptr<ByteBuffer>>::const_iterator find = pendingData.find(packet.SequenceID);
			mutex.unlock();

			if (find == pendingData.end())
			{
				continue;
			}
			else
			{
				std::shared_ptr<ByteBuffer> packetData = find->second;

				if (packetData == NULL){
					return;
				}

				ByteBuffer *bf = packetData.get();
				if (packetData->GetPosition() > 0)
				{
					packetData->Rewind();
				}

				Network::NetworkPacket friendIndex = Network::NetworkPacket();
				friendIndex.Deserialize(bf);

				uint32_t count = bf->ReadUInt32();

				std::basic_string<uint8_t> buf = bf->ReadBlob();
				std::string sessionData(buf.begin(), buf.end());
			
				result->ParseFromString(sessionData);

				pendingData.erase(find);

				return;
			}
		}
	}

	std::string ClientNode::GetFriendName(uint64_t FriendID)
	{
		for (int i = 0; i < result->steamfriendinfo_size(); i++)
		{
			HedgeNodeProto::SteamFriendInfo info = result->steamfriendinfo(i);
			if (info.clientid() == FriendID){
				return info.name();
			}
		}
		return "";
	}

	DWORD _stdcall ClientNode::FriendDiscoveryThread(void  *lparam){

		while (true)
		{
			GetFriends();
			Sleep(2000);
		}
	}
}
