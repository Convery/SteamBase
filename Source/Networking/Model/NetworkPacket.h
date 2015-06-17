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
    class NetworkPacket
    {
        
	public:

		uint32_t ApplicationID;
		uint32_t SequenceID;
		EventType eventType;
		uint32_t	TimeStamp;
		uint32_t		DataLength;
		void *DataBuffer;
        
        NetworkPacket();
		NetworkPacket(uint32_t appId, uint32_t seqId, EventType evType, uint32_t tmstmp, uint32_t len, void *buffer);
        NetworkPacket(ByteBuffer *InBuffer);
        ~NetworkPacket(void);
        bool Serialize(ByteBuffer *OutBuffer);
        //static bool Deserialize(ByteBuffer *InBuffer);

    };
}