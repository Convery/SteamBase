/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-25
	Notes:
		Store and maintain our sockets.
*/

#pragma once

namespace Network
{
	class SocketManager
	{
		static std::unordered_map<int32_t, uint16_t> UDPSockets;
		static std::unordered_map<int32_t, uint32_t> TCPSockets;
		static std::mutex ThreadSafe;

	public:
		// Ctor & dtor since we use static data.
		static bool InitializeManager();
		static void ShutdownManager();

		// Create a new socket.
		static bool Create_UDP(uint16_t *RequestedPort, bool Blocking = false);
		static bool Create_TCP(class hAddress *Destination, bool Blocking = false);

		// Send data over a socket.
		static bool Send_UDP(class hAddress *Destination, uint16_t DataLength, void *DataBuffer);
		static bool Send_UDPBroadcast(uint16_t port, uint16_t DataLength, void *DataBuffer);
		static bool Send_TCP(class hAddress *SocketInfo, uint16_t DataLength, void *DataBuffer);

		// Receive data over a socket.
		static int32_t Receive_UDP(uint16_t SocketPort, uint16_t BufferLength, void *DataBuffer, class hAddress *Sender = nullptr);
		static int32_t Receive_TCP(class hAddress *SocketInfo, uint16_t BufferLength, void *DataBuffer);
	};
}
