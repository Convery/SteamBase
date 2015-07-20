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

	DWORD _stdcall ClientNode::NodeDiscoverySender(void  *lparam)
	{
		uint16_t port = 20000;
		Network::SocketManager::Create_UDP(&port, false);

		DBGPrint("Searching for sNode");

		char recvBuffer[1024] = { 0 };
		while (true)
		{
			Network::PingPacket pingPacket;
			pingPacket.ClientID = Global::Steam_UserID;
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
				break;
			}
			Sleep(2000);
		}

		return 0;
	}

	void ClientNode::SetNetworkData(Network::NetworkPacket *inPacket, EventType eventType){
		inPacket->ApplicationID = Global::Steam_AppID;
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
		if (!isSNodeConnected)
		{
			return 0;
		}

		Network::NetworkPacket packet;
		SetNetworkData(&packet, HNFriendCountRequest);

		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		packet.Serialize(&packetBuffer);

		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());

		int32_t friendsCount = 0;
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

				if (packetData == NULL)
				{
					return 0;
				}

				ByteBuffer *bf = packetData.get();
				if (packetData->GetPosition() > 0)
				{
					packetData->Rewind();
				}

				Network::FriendCountPacket friendCount = Network::FriendCountPacket();
				friendCount.Deserialize(bf);

				friendsCount = friendCount.friendsCount;

				pendingData.erase(find);

				return friendsCount;
			}
		}

		return friendsCount;
	}

	uint64_t ClientNode::GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags)
	{
		if (!isSNodeConnected)
		{
			return 0x1100001DEADC0DE;
		}
		Network::NetworkPacket packet;

		SetNetworkData(&packet, HNFriendAtIndexRequest);

		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		packet.Serialize(&packetBuffer);

		packetBuffer.WriteInt32(iFriend);

		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());

		uint64_t steamID = 0;
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
					return 0;
				}

				ByteBuffer *bf = packetData.get();
				if (packetData->GetPosition() > 0)
				{
					packetData->Rewind();
				}

				Network::FriendAtIndex friendIndex = Network::FriendAtIndex();
				friendIndex.Deserialize(bf);
				steamID = friendIndex.friendSteamID;

				pendingData.erase(find);

				return steamID;
			}
		}

		return steamID;
	}

	std::string ClientNode::GetFriendName(uint64_t FriendID)
	{
		if (!isSNodeConnected)
		{
			return "";
		}
		Network::NetworkPacket packet;

		SetNetworkData(&packet, HNFriendNameRequest);

		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		packet.Serialize(&packetBuffer);

		packetBuffer.WriteUInt64(FriendID);

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
					return 0;
				}

				ByteBuffer *bf = packetData.get();
				if (packetData->GetPosition() > 0)
				{
					packetData->Rewind();
				}

				Network::NetworkPacket friendIndex = Network::NetworkPacket();
				friendIndex.Deserialize(bf);
				std::string name = bf->ReadString();

				pendingData.erase(find);

				return name;
			}
		}

		return "";
	}
}
