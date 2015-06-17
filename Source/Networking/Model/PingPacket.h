#pragma once

namespace Network
{
	class PingPacket
	{

	public:

		uint64_t ClientID;
		uint32_t SessionID;
		bool isAuthenticated = false;
		bool isAnonymous = false;
		std::string username;

		PingPacket();
		PingPacket(uint64_t cId, uint32_t sessID, bool isAuth, bool isAnon, std::string user);
		PingPacket(ByteBuffer *InBuffer);
		~PingPacket(void);
		bool Serialize(ByteBuffer *OutBuffer);
		//static bool Deserialize(ByteBuffer *InBuffer);

	};
}