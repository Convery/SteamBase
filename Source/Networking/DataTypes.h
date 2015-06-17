/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-25
	Notes:
		Structs and classes used for networking.
*/

#pragma once

// Stores an IPv4 address and port.
class hAddress
{
public:
	uint32_t Address;
	uint16_t Port;

	hAddress();
	hAddress(uint8_t ByteA, uint8_t ByteB, uint8_t ByteC, uint8_t ByteD, uint16_t Port);
};
inline hAddress::hAddress()
{
	this->Address = 0;
	this->Port = 0;
}
inline hAddress::hAddress(uint8_t ByteA, uint8_t ByteB, uint8_t ByteC, uint8_t ByteD, uint16_t Port)
{
	this->Address = (ByteA << 24) | (ByteB << 16) | (ByteC << 8) | ByteD;
	this->Port = Port;
}

// Standardized packet format.
class hPacket
{
public:
	uint32_t ApplicationID;		// Unique identifier.
	uint16_t SequenceID;		// Packet identifier.
	uint32_t Command;			// FNV1_32 hash of a string.
	std::string Data;			// Misc payload.

	hPacket();
	hPacket(int32_t BufferLength, char *DataBuffer);
};
inline hPacket::hPacket()
{
	ApplicationID = 0;
	SequenceID = 0;
	Command = 0;
}
inline hPacket::hPacket(int32_t BufferLength, char *DataBuffer)
{
	// A packet wont be split when using UDP.
	if(BufferLength < 10)
	{
		DBGPrint("Recieved a damaged packet of length %i", BufferLength);
		
		ApplicationID = 0;
		SequenceID = 0;
		Command = 0;
		return;
	}
	
	// Copy from the packetstream and increment the pointer.
	memcpy(&this->ApplicationID, DataBuffer, 4);
	DataBuffer += 4;
	memcpy(&this->SequenceID, DataBuffer, 2);
	DataBuffer += 2;
	memcpy(&this->Command, DataBuffer, 4);
	DataBuffer += 4;

	// Convert endians as needed.
	this->ApplicationID = ntohl(this->ApplicationID);
	this->SequenceID = ntohs(this->SequenceID);
	this->Command = ntohl(this->Command);
	
	// Append the rest of the packet.
	BufferLength -= 10;
	if(BufferLength)
	{
		Data.append(DataBuffer, BufferLength);
	}
}
