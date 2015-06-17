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
	std::unordered_map<uint32_t, Network::NetworkPacket*> ClientNode::pendingData;

	DWORD _stdcall ClientNode::NodeDiscoverySender(void  *lparam)
	{
		uint16_t port = 20000;
		Network::SocketManager::Create_UDP(&port, false);

		char *recvBuffer = (char *)malloc(sizeof(char) * 1024);
		while (true){
			DBGPrint("Searching for sNode");
			ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();

			Network::PingPacket *pingPacket = new Network::PingPacket();
			pingPacket->ClientID = Global::Steam_UserID;
			pingPacket->isAnonymous = true;
			pingPacket->isAuthenticated = false;
			pingPacket->SessionID = rand();
			pingPacket->username = Global::Steam_Username;
			ByteBuffer pingBuffer = ByteBuffer::ByteBuffer();
			pingPacket->Serialize(&pingBuffer);
			Network::NetworkPacket *packet = CreateNetworkPacket(HNPingRequest, pingBuffer.GetLength(), pingBuffer.GetBuffer<void>());
			packet->Serialize(&packetBuffer);
			Network::SocketManager::Send_UDPBroadcast(31337, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());
			int len = Network::SocketManager::Receive_UDP(port, 1024, recvBuffer, &serverNode);
			if (len > 0){
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
	Network::NetworkPacket* ClientNode::CreateNetworkPacket(EventType eventType, uint32_t DataLength, void* DataBuffer){
		Network::NetworkPacket *packet = new Network::NetworkPacket();
		packet->ApplicationID = Global::Steam_AppID;
		packet->eventType = eventType;
		packet->SequenceID = GetSequence();
		packet->TimeStamp = time(NULL);
		packet->DataLength = DataLength;
		packet->DataBuffer = DataBuffer;
		return packet;
	}

	DWORD _stdcall ClientNode::NodePacketReceiver(void  *lparam)
	{
		uint16_t port = 20000;

		char *recvBuffer = (char *)malloc(sizeof(char) * 1024);
		hAddress sender = hAddress::hAddress();
		while (true){

			int32_t len = Network::SocketManager::Receive_UDP(port, 1024, recvBuffer, &sender);
			if (len > 0){
				ByteBuffer *packetBuffer = new ByteBuffer(len, (void*)recvBuffer);
				Network::NetworkPacket *packet = new Network::NetworkPacket(packetBuffer);
				mutex.lock();
				pendingData[packet->SequenceID] = packet;
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

	uint32_t ClientNode::GetSequence(){
		mutex.lock();
		++sequenceID;
		mutex.unlock();
		return sequenceID;
	}

	int32_t ClientNode::GetFriendCount(int32_t iFriendFlags)
	{
		if (!isSNodeConnected){
			return 0;
		}
		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		Network::NetworkPacket *packet = CreateNetworkPacket(HNFriendCountRequest, 0, nullptr);
		packet->Serialize(&packetBuffer);
		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());
		
		int32_t friendsCount = 0;
		time_t t1 = time(0);
		while (true){
			if (difftime(time(0), t1) > waitTimeout){
				break;
			}
			std::unordered_map<uint32_t, Network::NetworkPacket*>::const_iterator find = pendingData.find(packet->SequenceID);

			if (find == pendingData.end()){
				continue;
			}else{
				Network::NetworkPacket* friendsResponse = find->second;
				friendsCount = *((int32_t *)friendsResponse->DataBuffer);
			}
		}
		return friendsCount;
	}

	uint64_t ClientNode::GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags){
		if (!isSNodeConnected){
			return 0x1100001DEADC0DE;
		}
		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		Network::NetworkPacket *packet = CreateNetworkPacket(HNFriendAtIndexRequest, 0, nullptr);
		packet->DataLength = sizeof(int32_t);
		int32_t index = iFriend;
		packet->DataBuffer = &index;
		packet->Serialize(&packetBuffer);
		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());

		uint64_t steamID = 0;
		time_t t1 = time(0);
		while (true){
			if (difftime(time(0), t1) > waitTimeout){
				break;
			}
			std::unordered_map<uint32_t, Network::NetworkPacket*>::const_iterator find = pendingData.find(packet->SequenceID);

			if (find == pendingData.end()){
				continue;
			}
			else{
				Network::NetworkPacket* friendsResponse = find->second;
				steamID = *((uint64_t *)friendsResponse->DataBuffer);
			}
		}
		return steamID;
	}
}