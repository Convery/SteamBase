/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-25
	Notes:
		Store and maintain our sockets.
*/

#include "..\StdInclude.h"

namespace Network
{
	// Static data.
	std::unordered_map<int32_t, uint16_t> SocketManager::UDPSockets;
	std::unordered_map<int32_t, uint32_t> SocketManager::TCPSockets;
	std::mutex SocketManager::ThreadSafe;

	// Ctor & dtor since we use static data.
	bool SocketManager::InitializeManager()
	{
#if PLATFORM == PLATFORM_WINDOWS
		WSADATA WsaData;
		return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#else
		return true;
#endif
	}
	void SocketManager::ShutdownManager()
	{
#if PLATFORM == PLATFORM_WINDOWS
		WSACleanup();
#endif
	}

	// Create a new socket.
	bool SocketManager::Create_UDP(uint16_t *RequestedPort, bool Blocking)
	{
		sockaddr_in Address;
		int32_t Handle = 0;
		int16_t Port = *RequestedPort;
		
		// Create the socket.
		Handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (Handle <= 0)
		{
			DBGPrint("Failed to create a UDP socket for port %u", Port);
			return false;
		}

		// Set up the address info.
		Address.sin_family = AF_INET;
#if PLATFORM == PLATFORM_WINDOWS
		Address.sin_addr.S_un.S_addr = INADDR_ANY;
#elif PLATFORM == PLATFORM_MAC ||  PLATFORM == PLATFORM_UNIX
		Address.sin_addr.s_addr = INADDR_ANY;
#endif

		// Bind to the port, retry up to ten times.
		for (uint8_t i = 0; i < 11; i++)
		{
			// Increment the port for each pass.
			Address.sin_port = htons(Port + i);

			// Attempt to bind.
			if (bind(Handle, (const sockaddr*)&Address, sizeof(sockaddr_in)) < 0)
			{
				// Out of attempts.
				if (i == 9)
				{
					DBGPrint("Failed to bind UDP socket for port %u", Port);
					return false;
				}
				else
				{
					DBGPrint("Failed to bind UDP socket for port %u, retrying", Port);
				}
			}
			else
			{	
				// Leave the loop and set the result port.
				DBGPrint("Bound UDP socket for port %u", Port + i);
				*RequestedPort = Port + i;
				break;
			}
		}

		// Set our blocking status.
#if PLATFORM == PLATFORM_WINDOWS
		DWORD NonBlocking = Blocking ? 0 : 1;
		if(ioctlsocket(Handle, FIONBIO, &NonBlocking) != 0)
		{
			DBGPrint("Failed set blocking status on UDP socket for port %u", Port);
			return false;
		}
#elif PLATFORM == PLATFORM_MAC ||  PLATFORM == PLATFORM_UNIX
		int32_t NonBlocking = Blocking ? 0 : 1;
		if (fcntl(Handle, F_SETFL, O_NONBLOCK, NonBlocking) == -1)
		{
			DBGPrint("Failed set blocking status on UDP socket for port %u", Port);
			return false;
		}
#endif
		
		// Add our new socket to the map.
		ThreadSafe.lock();
		/*if (UDPSockets[*RequestedPort])
		{
			DBGPrint("UDP socket for port %u already exists, overwriting", *RequestedPort);
		}*/
		UDPSockets.emplace(*RequestedPort, Handle);
		ThreadSafe.unlock();

		// Finally return.
		return true;
	}
	bool SocketManager::Create_TCP(class hAddress *Destination, bool Blocking)
	{
		sockaddr_in Address;
		int32_t Handle = 0;

		// Create the socket.
		Handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (Handle <= 0)
		{
			DBGPrint("Failed to create a TCP socket for IP %s", inet_ntoa(*(in_addr *)&Destination->Address));
			return false;
		}

		// Set up the address info.
		Address.sin_family = AF_INET;
#if PLATFORM == PLATFORM_WINDOWS
		Address.sin_addr.S_un.S_addr = Destination->Address;
#elif PLATFORM == PLATFORM_MAC ||  PLATFORM == PLATFORM_UNIX
		Address.sin_addr.s_addr = Destination->Address;
#endif
		Address.sin_port = htons(Destination->Port);

		// Attempt to connect.
#if PLATFORM == PLATFORM_WINDOWS
		if (connect(Handle, (SOCKADDR *)&Address, sizeof(sockaddr_in)) == SOCKET_ERROR)
#elif PLATFORM == PLATFORM_MAC ||  PLATFORM == PLATFORM_UNIX
		if (connect(Handle, (sockaddr *)&Address, sizeof(sockaddr_in)) != 0)
#endif
		{
#if PLATFORM == PLATFORM_WINDOWS
			DBGPrint("Failed to connect to IP %s with error %i", inet_ntoa(*(in_addr *)&Destination->Address), WSAGetLastError());
#elif PLATFORM == PLATFORM_MAC ||  PLATFORM == PLATFORM_UNIX
			DBGPrint("Failed to connect to IP %s with error %s", inet_ntoa(*(in_addr *)&Destination->Address), strerror(errno));
#endif
			return false;
		}

		// Set our blocking status.
#if PLATFORM == PLATFORM_WINDOWS
		DWORD NonBlocking = Blocking ? 0 : 1;
		if (ioctlsocket(Handle, FIONBIO, &NonBlocking) != 0)
		{
			DBGPrint("Failed set blocking status on TCP socket for IP %s", inet_ntoa(*(in_addr *)&Destination->Address));
			return false;
		}
#elif PLATFORM == PLATFORM_MAC ||  PLATFORM == PLATFORM_UNIX
		int32_t NonBlocking = Blocking ? 0 : 1;
		if (fcntl(Handle, F_SETFL, O_NONBLOCK, NonBlocking) == -1)
		{
			DBGPrint("Failed set blocking status on TCP socket for IP %s", inet_ntoa(*(in_addr *)&Destination->Address));
			return false;
		}
#endif

		// Add our new socket to the map.
		ThreadSafe.lock();
		/*if (TCPSockets[Destination->Address])
		{
			HedgePrint("A TCP socket for IP %s already exists, overwriting", inet_ntoa(*(in_addr *)&Destination->Address));
		}*/
		TCPSockets.emplace(Destination->Address, Handle);
		ThreadSafe.unlock();

		// Finally return.
		return true;
	}

	// Send data over a socket.
	bool SocketManager::Send_UDP(class hAddress *Destination, uint16_t DataLength, void *DataBuffer)
	{
		int32_t SentBytes = 0;

		// Create the address struct.
		sockaddr_in Address;
		Address.sin_family = AF_INET;
		Address.sin_addr.s_addr = htonl(Destination->Address);
		Address.sin_port = htons(Destination->Port);
		int sockfd;
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		// Send the data.
		SentBytes = sendto(sockfd, (const char *)DataBuffer, DataLength, 0, (sockaddr *)&Address, sizeof(sockaddr_in));
		return SentBytes == DataLength;
	}

	// Send udp broadcast
	bool SocketManager::Send_UDPBroadcast(uint16_t port, uint16_t DataLength, void *DataBuffer)
	{
		int32_t SentBytes = 0;
		int yes = 1;
		// Create the address struct.
		sockaddr_in Address;
		Address.sin_family = AF_INET;
		Address.sin_addr.s_addr = htonl(INADDR_BROADCAST);
		Address.sin_port = htons(port);
		int sockfd;
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		int status = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(int));
		// Send the data.
		SentBytes = sendto(sockfd, (const char *)DataBuffer, DataLength, 0, (sockaddr *)&Address, sizeof(sockaddr_in));
		return SentBytes == DataLength;
	}

	bool SocketManager::Send_TCP(class hAddress *SocketInfo, uint16_t DataLength, void *DataBuffer)
	{
		int32_t SentBytes = 0;
		int32_t Handle = 0;

		// Retrieve the socket.
		ThreadSafe.lock();
		Handle = TCPSockets[SocketInfo->Address];
		ThreadSafe.unlock();

		// Send the data.
		SentBytes = send(Handle, (const char *)DataBuffer, DataLength, 0);
		return SentBytes == DataLength;
	}

	// Receive data over a socket.
#if PLATFORM == PLATFORM_WINDOWS
	typedef int32_t socklen_t;
#endif
	int32_t SocketManager::Receive_UDP(uint16_t SocketPort, uint16_t BufferLength, void *DataBuffer,class hAddress *Sender)
	{
		sockaddr_in From;
		socklen_t FromLength = sizeof(From);
		int32_t BytesRecvd = 0;
		int32_t Handle = 0;
		
		// Retrieve the socket.
		ThreadSafe.lock();
		Handle = UDPSockets[SocketPort];
		ThreadSafe.unlock();

		// Receive a packet of max length BufferLength.
		BytesRecvd = recvfrom(Handle, (char *)DataBuffer, BufferLength, 0, (sockaddr *)&From, &FromLength);

		// Set the Sender struct if we got a packet.
		if (BytesRecvd)
		{
			if (Sender != nullptr)
			{
#if PLATFORM == PLATFORM_WINDOWS
				Sender->Address = ntohl(From.sin_addr.S_un.S_addr);
#elif PLATFORM == PLATFORM_MAC ||  PLATFORM == PLATFORM_UNIX
				Sender->Address = ntohl(From.sin_addr.s_addr);
#endif
				Sender->Port = ntohs(From.sin_port);
			}
		}

		return BytesRecvd;
	}
	int32_t SocketManager::Receive_TCP(class hAddress *SocketInfo, uint16_t BufferLength, void *DataBuffer)
	{
		int32_t BytesRecvd = 0;
		int32_t Handle = 0;

		// Retrieve the socket.
		ThreadSafe.lock();
		Handle = TCPSockets[SocketInfo->Address];
		ThreadSafe.unlock();

		// Recieve a packet of max length BufferLength.
		BytesRecvd = recv(Handle, (char *)DataBuffer, BufferLength, 0);
		return BytesRecvd;
	}
}
