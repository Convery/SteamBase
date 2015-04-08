/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-03-09
	Notes:
		Standard buffer class for HedgehogScience data.
		Based on DemonWares 'bdByteBuffer' class.
*/

#pragma once

class ByteBuffer
{
	std::basic_string<uint8_t> InternalBuffer;
	uint32_t BufferPosition;

public:
	// Constructors.
	ByteBuffer();
	ByteBuffer(uint32_t Length, void *Buffer = nullptr);
	ByteBuffer(std::basic_string<uint8_t> *Buffer);
	ByteBuffer(std::string *Buffer);
	~ByteBuffer();

	// Accessors.
	uint32_t Position();										// Return read/write position.
	uint32_t Length();											// Return the size of the buffer.
	template <typename DataType>								// Return a pointer to a temporary buffer 
	DataType *Buffer();											// with the contents of InternalBuffer.																

	// Utility.
	int32_t FindFirst(void *Src, uint32_t Length);				// First occurance of Src.
	int32_t FindLast(void *Src, uint32_t Length);				// Last occurance of Src.
	uint8_t PeekByte();											// Return the next byte.
	bool SetPosition(uint32_t Position);						// Set the BufferPosition if within range.
	void Rewind();												// Sets the position to 0.
	void Clear();												// Clear the buffer and call Rewind.

	// Base functions.
	bool Read(uint32_t Count, void *Output = nullptr);	// Read [Count] bytes.
	bool Write(uint32_t Count, void *Input = nullptr);	// Write [Count] bytes.

	bool ReadDataType(uint8_t Type);						// Verifies the datatype, internal.
	bool WriteDataType(uint8_t Type);					// Verifies the datatype, internal.
	template <typename DataType> bool Read(DataType *Output = nullptr, bool Typecheck = true);
	template <typename DataType> bool Write(DataType Input = nullptr, bool Typecheck = true);

#pragma region LegacyReadMethods
	bool ReadBoolean(bool *Output, bool Typecheck = true);

	bool ReadInt8(int8_t *Output, bool Typecheck = true);
	bool ReadUInt8(uint8_t *Output, bool Typecheck = true);

	bool ReadInt16(int16_t *Output, bool Typecheck = true);
	bool ReadUInt16(uint16_t *Output, bool Typecheck = true);

	bool ReadInt32(int32_t *Output, bool Typecheck = true);
	bool ReadUInt32(uint32_t *Output, bool Typecheck = true);

	bool ReadInt64(int64_t *Output, bool Typecheck = true);
	bool ReadUInt64(uint64_t *Output, bool Typecheck = true);

	bool ReadFloat32(float *Output, bool Typecheck = true);
	bool ReadFloat64(double *Output, bool Typecheck = true);

	bool ReadString(std::string &Output, bool Typecheck = true);
	bool ReadBlob(std::string *Output);
	bool ReadBlob(std::basic_string<uint8_t> *Output);
	bool ReadArrayStart(uint8_t ExpectedType, uint32_t *ElementCount, uint32_t *ElementSize = nullptr);
#pragma endregion

#pragma region LegacyWriteMethods
	bool WriteBoolean(bool Input, bool Typecheck = true);

	bool WriteInt8(int8_t Input, bool Typecheck = true);
	bool WriteUInt8(uint8_t Input, bool Typecheck = true);

	bool WriteInt16(int16_t Input, bool Typecheck = true);
	bool WriteUInt16(uint16_t Input, bool Typecheck = true);

	bool WriteInt32(int32_t Input, bool Typecheck = true);
	bool WriteUInt32(uint32_t Input, bool Typecheck = true);

	bool WriteInt64(int64_t Input, bool Typecheck = true);
	bool WriteUInt64(uint64_t Input, bool Typecheck = true);

	bool WriteFloat32(float Input, bool Typecheck = true);
	bool WriteFloat64(double Input, bool Typecheck = true);

	bool WriteString(std::string &Input, bool Typecheck = true);
	bool WriteBlob(std::string *Input);
	bool WriteBlob(std::basic_string<uint8_t> *Input);
	bool WriteArrayStart(uint8_t Type, uint32_t ElementCount, uint32_t ElementSize);
#pragma endregion
};
