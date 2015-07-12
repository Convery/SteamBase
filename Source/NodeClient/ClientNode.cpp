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

	uint64_t ClientNode::CreateSession(ByteBuffer *Buffer, int32_t iFriendFlags)
	{
		if (!isSNodeConnected)
		{
			return 0x1100001DEADC0DE;
		}
		Network::NetworkPacket packet;

		std::string HostAddress;
		Buffer->ReadBlob(&HostAddress);
		uint32_t Gametype = Buffer->ReadUInt32();
		uint32_t MaxPlayers = Buffer->ReadUInt32();

		SetNetworkData(&packet, HNCreateSessionRequest);

		ByteBuffer packetBuffer;
		packet.Serialize(&packetBuffer);
		
		packetBuffer.WriteString(HostAddress);
		packetBuffer.WriteUInt32(Gametype);
		packetBuffer.WriteUInt32(MaxPlayers);

		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());

		uint64_t sessionID = 0;
		time_t t1 = time(0);

		while (true)
		{
			if (difftime(time(0), t1) > waitTimeout)
			{
				break;
			}

			mutex.lock();
			auto find = pendingData.find(packet.SequenceID);
			mutex.unlock();

			if (find == pendingData.end())
			{
				continue;
			}
			else
			{
				DBGPrint("received create session response");
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

				sessionID = bf->ReadUInt64();

				pendingData.erase(find);

				return sessionID;
			}
		}

		return sessionID;
	}

	void ClientNode::UpdateSession(ByteBuffer *Buffer, int32_t iFriendFlags)
	{
		if (!isSNodeConnected)
		{
			return;
		}
		Network::NetworkPacket packet;
		SetNetworkData(&packet, HNUpdateSessionRequest);

		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		packet.Serialize(&packetBuffer);

		packetBuffer.WriteUInt64(Buffer->ReadUInt64());

		auto blob = Buffer->ReadBlob();
		packetBuffer.WriteBlob(&blob);

		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());
	}

	void ClientNode::DeleteSession(ByteBuffer *Buffer, int32_t iFriendFlags)
	{
		if (!isSNodeConnected)
		{
			return;
		}
		Network::NetworkPacket packet;
		SetNetworkData(&packet, HNDeleteSessionRequest);

		ByteBuffer packetBuffer;
		packet.Serialize(&packetBuffer);

		packetBuffer.WriteUInt64(Buffer->ReadUInt64());

		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());
	}

	void ClientNode::FindSessions(ByteBuffer *Buffer, int32_t iFriendFlags, void* outBuffer, uint32_t* outLen)
	{
		if (!isSNodeConnected)
		{
			return;
		}
		Network::NetworkPacket packet;
		SetNetworkData(&packet, HNFindSessionsRequest);

		ByteBuffer packetBuffer = ByteBuffer::ByteBuffer();
		packet.Serialize(&packetBuffer);

		Network::SocketManager::Send_UDP(&serverNode, packetBuffer.GetLength(), packetBuffer.GetBuffer<void>());

		uint64_t sessionID = 0;
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
				DBGPrint("received find session response");
				std::shared_ptr<ByteBuffer> packetData = find->second;

				if (packetData == NULL) return;

				ByteBuffer *bf = packetData.get();
				if (packetData->GetPosition() > 0)
				{
					packetData->Rewind();
				}

				Network::NetworkPacket packet;
				packet.Deserialize(bf);

				ByteBuffer outByteBuffer;
				uint32_t lobbies = bf->ReadUInt32();
				outByteBuffer.WriteUInt32(lobbies);

				for (uint32_t i = 0; i < lobbies; i++)
				{
					auto blob = bf->ReadBlob();
					outByteBuffer.WriteBlob(&blob);
				}

				void* readBuffer = outByteBuffer.GetBuffer<void>();
				memcpy(outBuffer, readBuffer, min(outByteBuffer.GetLength(), 1024));
				*outLen = outByteBuffer.GetLength();
				return;
			}
		}
	}

}
