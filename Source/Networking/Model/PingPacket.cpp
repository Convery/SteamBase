#include "..\..\StdInclude.h"

namespace Network
{

	PingPacket::PingPacket(){
		ClientID = 0;
		SessionID = 0;
		isAuthenticated = false;
		isAnonymous = false;
		username = "";
	}

	PingPacket::PingPacket(uint64_t cId, uint32_t sessID, bool isAuth, bool isAnon, std::string user){
		ClientID = cId;
		SessionID = sessID;
		isAuthenticated = isAuth;
		isAnonymous = isAnon;
		username = user;
	}

	PingPacket::PingPacket(ByteBuffer *InBuffer){
		InBuffer->ReadUInt64(&ClientID);
		InBuffer->ReadUInt32(&SessionID);
		InBuffer->ReadBoolean(&isAuthenticated);
		InBuffer->ReadBoolean(&isAnonymous);
		InBuffer->ReadString(username);
	}

	PingPacket::~PingPacket(void){

	}

	bool PingPacket::Serialize(ByteBuffer *OutBuffer){
		OutBuffer->WriteUInt64(ClientID);
		OutBuffer->WriteUInt32(SessionID);
		OutBuffer->WriteBoolean(isAuthenticated);
		OutBuffer->WriteBoolean(isAnonymous);
		OutBuffer->WriteString(username);
		return true;
	}
}