#include "..\..\StdInclude.h"

namespace Network
{
        
    NetworkPacket::NetworkPacket(){
        eventType = HNUnknownEvent;
        DataLength = 0;
        ApplicationID = 0;
        SequenceID = 0;
        DataBuffer = nullptr;
    }
    
	NetworkPacket::NetworkPacket(uint32_t appId, uint32_t seqId, EventType evType, uint32_t	tmstmp, uint32_t len, void *buffer){
        ApplicationID = appId;
        SequenceID = seqId;
        eventType = evType;
        TimeStamp = tmstmp;
        DataLength = len;
        DataBuffer = buffer;
    }
    
    NetworkPacket::NetworkPacket(ByteBuffer *InBuffer){
		int16_t *evtType = (int16_t *)malloc(sizeof(int16_t));
		InBuffer->ReadInt16(evtType);
		eventType = (EventType)*evtType;
        InBuffer->ReadUInt32(&ApplicationID);
        InBuffer->ReadUInt32(&SequenceID);
        InBuffer->ReadUInt32(&TimeStamp);
        InBuffer->ReadUInt32(&DataLength);
		if (DataLength > 0){
			InBuffer->ReadBlob(DataLength, DataBuffer);
		}	
    }
    
    NetworkPacket::~NetworkPacket(void){
        
    }
    
    bool NetworkPacket::Serialize(ByteBuffer *OutBuffer){
        //EventType first so we can peak at packets

        OutBuffer->WriteInt16((int16_t)eventType);
        OutBuffer->WriteUInt32(ApplicationID);
        OutBuffer->WriteUInt32(SequenceID);
        OutBuffer->WriteUInt32(TimeStamp);
        OutBuffer->WriteUInt32(DataLength);
		if (DataLength > 0){
			OutBuffer->WriteBlob(DataLength, DataBuffer);
		}
        return true;
    }
}