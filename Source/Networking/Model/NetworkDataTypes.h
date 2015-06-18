#pragma once
typedef enum
{
    HNUnknownEvent = 0,
    HNPingRequest = 1,
    HNPingResponse = 2,
    HNFriendsRequest = 3,
    HNFriendsResponse = 4,
    HNFriendCountRequest = 5,
    HNFriendCountResponse = 6,
    HNFriendAtIndexRequest = 7,
    HNFriendAtIndexResponse = 8
} EventType;

namespace Network
{
	class NetworkPacket : public Network::ISerializable
    {
    public:
        
        uint32_t ApplicationID;
        uint32_t SequenceID;
        EventType eventType;
        uint32_t	TimeStamp;
        
        void Serialize(ByteBuffer *OutBuffer)
        {
            //EventType first so we can peak at packets
            OutBuffer->WriteInt16(eventType);
            OutBuffer->WriteUInt32(ApplicationID);
            OutBuffer->WriteUInt32(SequenceID);
            OutBuffer->WriteUInt32(TimeStamp);
        }
        void Deserialize(ByteBuffer *InBuffer)
        {
            int16_t *evtType = (int16_t *)malloc(sizeof(int16_t));
            InBuffer->ReadInt16(evtType);
            eventType = (EventType)*evtType;
            InBuffer->ReadUInt32(&ApplicationID);
            InBuffer->ReadUInt32(&SequenceID);
            InBuffer->ReadUInt32(&TimeStamp);
        }
    };
    
    class PingPacket : public NetworkPacket
    {
    public:
        
        uint64_t ClientID;
        uint32_t SessionID;
        bool isAuthenticated = false;
        bool isAnonymous = false;
        std::string username;
        
        void Serialize(ByteBuffer *OutBuffer)
        {
            NetworkPacket::Serialize(OutBuffer);
            
            OutBuffer->WriteUInt64(ClientID);
            OutBuffer->WriteUInt32(SessionID);
            OutBuffer->WriteBoolean(isAuthenticated);
            OutBuffer->WriteBoolean(isAnonymous);
            OutBuffer->WriteString(username);
        }
        void Deserialize(ByteBuffer *InBuffer)
        {
            NetworkPacket::Deserialize(InBuffer);
            
            InBuffer->ReadUInt64(&ClientID);
            InBuffer->ReadUInt32(&SessionID);
            InBuffer->ReadBoolean(&isAuthenticated);
            InBuffer->ReadBoolean(&isAnonymous);
            InBuffer->ReadString(username);
        }
    };

    
    class FriendCountPacket : public NetworkPacket
    {
    public:
        
        uint32_t friendsCount;
        
        void Serialize(ByteBuffer *OutBuffer)
        {
            NetworkPacket::Serialize(OutBuffer);
            
            OutBuffer->WriteUInt32(friendsCount);
        }
        void Deserialize(ByteBuffer *InBuffer)
        {
            NetworkPacket::Deserialize(InBuffer);
            
            InBuffer->ReadUInt32(&friendsCount);
        }
    };
    
    class FriendAtIndex : public NetworkPacket
    {
    public:
        
        uint64_t friendSteamID;
        
        void Serialize(ByteBuffer *OutBuffer)
        {
            NetworkPacket::Serialize(OutBuffer);
            
            OutBuffer->WriteUInt64(friendSteamID);
        }
        void Deserialize(ByteBuffer *InBuffer)
        {
            NetworkPacket::Deserialize(InBuffer);
            
            InBuffer->ReadUInt64(&friendSteamID);
        }
    };
}