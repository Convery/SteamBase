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

#include "..\StdInclude.h"

#pragma region Enumerations
enum BBTypes
{
	BB_NO_TYPE							= 0,
	BB_BOOL_TYPE						= 1,
	BB_SIGNED_CHAR8_TYPE				= 2,
	BB_UNSIGNED_CHAR8_TYPE				= 3,
	BB_WCHAR16_TYPE						= 4,
	BB_SIGNED_INTEGER16_TYPE			= 5,
	BB_UNSIGNED_INTEGER16_TYPE			= 6,
	BB_SIGNED_INTEGER32_TYPE			= 7,
	BB_UNSIGNED_INTEGER32_TYPE			= 8,
	BB_SIGNED_INTEGER64_TYPE			= 9,
	BB_UNSIGNED_INTEGER64_TYPE			= 10,
	BB_RANGED_SIGNED_INTEGER32_TYPE		= 11,
	BB_RANGED_UNSIGNED_INTEGER32_TYPE	= 12,
	BB_FLOAT32_TYPE						= 13,
	BB_FLOAT64_TYPE						= 14,
	BB_RANGED_FLOAT32_TYPE				= 15,
	BB_SIGNED_CHAR8_STRING_TYPE			= 16,
	BB_UNSIGNED_CHAR8_STRING_TYPE		= 17,
	BB_MBSTRING_TYPE					= 18,
	BB_BLOB_TYPE						= 19,
	BB_NAN_TYPE							= 20,
	BB_FULL_TYPE						= 21,
	BB_MAX_TYPE							= 32
};
#pragma endregion

#pragma region Constructors
ByteBuffer::ByteBuffer()
{
	InternalBuffer.clear();
	BufferPosition = 0;
}
ByteBuffer::ByteBuffer(uint32_t Length, void *Buffer)
{
	InternalBuffer.clear();
	BufferPosition = 0;

	if (Buffer != nullptr)
	{
		InternalBuffer.append((const uint8_t *)Buffer, Length);
	}
	else
	{
		InternalBuffer.resize(Length, 0);
	}
}
ByteBuffer::ByteBuffer(std::basic_string<uint8_t> *Buffer)
{
	InternalBuffer.clear();
	BufferPosition = 0;

	InternalBuffer.append(Buffer->data(), Buffer->size());
}
ByteBuffer::ByteBuffer(std::string *Buffer)
{
	InternalBuffer.clear();
	BufferPosition = 0;

	InternalBuffer.append((const uint8_t *)Buffer->data(), Buffer->size());
}
ByteBuffer::~ByteBuffer()
{
	for (uint32_t i = 0; i < InternalBuffer.size(); i++)
	{
		InternalBuffer[i] = 0;
	}
	InternalBuffer.clear();
}
#pragma endregion

#pragma region Accessors
uint32_t ByteBuffer::Position()
{
	return BufferPosition;
}
uint32_t ByteBuffer::Length()
{
	return InternalBuffer.size();
}
template <> char *ByteBuffer::Buffer<char>()
{
	return (char *)InternalBuffer.data();
}
template <> int8_t *ByteBuffer::Buffer<int8_t>()
{
	return (int8_t *)InternalBuffer.data();
}
template <> uint8_t *ByteBuffer::Buffer<uint8_t>()
{
	return (uint8_t *)InternalBuffer.data();
}
#pragma endregion

#pragma region Utility
int32_t ByteBuffer::FindFirst(void *Src, uint32_t Length)
{
	const uint8_t *pBuffer = InternalBuffer.data();
	for (int32_t i = 0; i < static_cast<int32_t>(min(InternalBuffer.size() - Length, INT32_MAX)); i++)
	{
		if (_memicmp(pBuffer + i, Src, Length) == 0)
			return i;
	}

	return -1;
}
int32_t ByteBuffer::FindLast(void *Src, uint32_t Length)
{
	const uint8_t *pBuffer = InternalBuffer.data();
	for (int32_t i = min(InternalBuffer.size() - Length, INT32_MAX); i >= 0; --i)
	{
		if (_memicmp(pBuffer + i, Src, Length) == 0)
			return i;
	}

	return -1;
}
uint8_t ByteBuffer::PeekByte()
{
	uint8_t Result = 0;

	if (Read(1, &Result))
	{
		BufferPosition--;
		return Result;
	}
	else
	{
		BufferPosition--;
		return BBTypes::BB_NO_TYPE;
	}
}
bool ByteBuffer::SetPosition(uint32_t Position)
{
	if (Position < InternalBuffer.length())
	{
		BufferPosition = Position;
		return true;
	}
	else
	{
		return false;
	}
}
void ByteBuffer::Rewind()
{
	BufferPosition = 0;
}
void ByteBuffer::Clear()
{
	for (uint32_t i = 0; i < InternalBuffer.size(); i++)
	{
		InternalBuffer[i] = 0;
	}
	InternalBuffer.clear();
	BufferPosition = 0;
}
#pragma endregion 

#pragma region Core
bool ByteBuffer::Read(uint32_t Count, void *Output)
{
	if (BufferPosition + Count > InternalBuffer.length())
	{
		fDBGPrint("%s tried to read out of bounds. Missing bytes: %i", __FUNCTION__, BufferPosition + Count - InternalBuffer.length());
		return false;
	}

	if (Output != nullptr)
	{
		memcpy(Output, InternalBuffer.data() + BufferPosition, Count);
	}

	BufferPosition += Count;
	return true;
}
bool ByteBuffer::Write(uint32_t Count, void *Input)
{
	if (Input != nullptr)
	{
		if (BufferPosition == InternalBuffer.length())
		{
			InternalBuffer.append((const uint8_t *)Input, Count);
			BufferPosition += Count;
			return true;
		}
		else
		{
			if (BufferPosition < InternalBuffer.length())
			{
				if (BufferPosition + Count < InternalBuffer.length())
				{
					for (uint32_t i = 0; i < Count; i++)
					{
						InternalBuffer[i] = ((const uint8_t *)Input)[i];
						BufferPosition++;
					}
					return true;
				}
				else
				{
					uint32_t FreeBytes = InternalBuffer.length() - BufferPosition;
					return	Write(FreeBytes, Input) && Write(Count - FreeBytes, (uint8_t *)Input + FreeBytes);
				}
			}
			else
			{
				fDBGPrint("%s error, BufferPosition > InternalBuffer.length", __FUNCTION__);
				return false;
			}
		}
	}
	else
	{
		BufferPosition += Count;
		return true;
	}	
}
bool ByteBuffer::ReadDataType(uint8_t Type)
{
	if (PeekByte() == Type)
	{
		BufferPosition++;
		return true;
	}
	else
	{
		return false;
	}
}
bool ByteBuffer::WriteDataType(uint8_t Type)
{
	return Write((uint32_t)1, &Type);
}
#pragma endregion

#pragma region CoreRead
template <> bool ByteBuffer::Read<bool>(bool *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_BOOL_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<int8_t>(int8_t *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_SIGNED_CHAR8_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<uint8_t>(uint8_t *Output, bool Typecheck) 
{
	if (!Typecheck || ReadDataType(BBTypes::BB_UNSIGNED_CHAR8_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<int16_t>(int16_t *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_SIGNED_INTEGER16_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<uint16_t>(uint16_t *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_UNSIGNED_INTEGER16_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<int32_t>(int32_t *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_SIGNED_INTEGER32_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<uint32_t>(uint32_t *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_UNSIGNED_INTEGER32_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<int64_t>(int64_t *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_SIGNED_INTEGER64_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<uint64_t>(uint64_t *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_UNSIGNED_INTEGER64_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<float>(float *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_FLOAT32_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
template <> bool ByteBuffer::Read<double>(double *Output, bool Typecheck)
{
	if (!Typecheck || ReadDataType(BBTypes::BB_FLOAT64_TYPE))
		return Read((uint32_t)sizeof(*Output), Output);
	else
		return false;
}
#pragma endregion

#pragma region CoreWrite
template <> bool ByteBuffer::Write<bool>(bool Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_BOOL_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<int8_t>(int8_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_SIGNED_CHAR8_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<uint8_t>(uint8_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_UNSIGNED_CHAR8_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<int16_t>(int16_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_SIGNED_INTEGER16_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<uint16_t>(uint16_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_UNSIGNED_INTEGER16_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<int32_t>(int32_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_SIGNED_INTEGER32_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<uint32_t>(uint32_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_UNSIGNED_INTEGER32_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<int64_t>(int64_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_SIGNED_INTEGER64_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<uint64_t>(uint64_t Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_UNSIGNED_INTEGER64_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<float>(float Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_FLOAT32_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
template <> bool ByteBuffer::Write<double>(double Input, bool Typecheck)
{
	if (!Typecheck || WriteDataType(BBTypes::BB_FLOAT64_TYPE))
		return Write((uint32_t)sizeof(Input), &Input);
	else
		return false;
}
#pragma endregion

#pragma region LegacyReadMethods
bool ByteBuffer::ReadBoolean(bool *Output, bool Typecheck)
{ 
	return Read<bool>(Output, Typecheck);
}
bool ByteBuffer::ReadInt8(int8_t *Output, bool Typecheck)
{
	return Read<int8_t>(Output, Typecheck);
}
bool ByteBuffer::ReadUInt8(uint8_t *Output, bool Typecheck)
{
	return Read<uint8_t>(Output, Typecheck);
}
bool ByteBuffer::ReadInt16(int16_t *Output, bool Typecheck)
{
	return Read<int16_t>(Output, Typecheck);
}
bool ByteBuffer::ReadUInt16(uint16_t *Output, bool Typecheck)
{
	return Read<uint16_t>(Output, Typecheck);
}
bool ByteBuffer::ReadInt32(int32_t *Output, bool Typecheck)
{
	return Read<int32_t>(Output, Typecheck);
}
bool ByteBuffer::ReadUInt32(uint32_t *Output, bool Typecheck)
{
	return Read<uint32_t>(Output, Typecheck);
}
bool ByteBuffer::ReadInt64(int64_t *Output, bool Typecheck)
{
	return Read<int64_t>(Output, Typecheck);
}
bool ByteBuffer::ReadUInt64(uint64_t *Output, bool Typecheck)
{
	return Read<uint64_t>(Output, Typecheck);
}
bool ByteBuffer::ReadFloat32(float *Output, bool Typecheck)
{
	return Read<float>(Output, Typecheck);
}
bool ByteBuffer::ReadFloat64(double *Output, bool Typecheck)
{
	return Read<double>(Output, Typecheck);
}

bool ByteBuffer::ReadString(std::string &Output, bool Typecheck)
{ 
	uint32_t StringLength = 0;

	if (Typecheck && !ReadDataType((uint8_t)BBTypes::BB_SIGNED_CHAR8_STRING_TYPE))
		return false;

	StringLength = strlen((char *)InternalBuffer.data() + BufferPosition) + 1;
	Output.append((char *)InternalBuffer.data() + BufferPosition, StringLength);

	BufferPosition += StringLength;
	return true;
}
bool ByteBuffer::ReadBlob(std::string *Output)
{ 
	uint32_t BlobLength = 0;

	if (!ReadDataType((uint8_t)BBTypes::BB_BLOB_TYPE) || !Read<uint32_t>(&BlobLength))
		return false;

	if (BufferPosition + BlobLength > InternalBuffer.size())
	{
		fDBGPrint("%s - Blob (%lli) is larger than the buffer (%lli), check the endians.", __FUNCTION__, BufferPosition + BlobLength, InternalBuffer.size());
		__debugbreak();
		return false;
	}
	
	for (uint32_t i = BufferPosition; i < BufferPosition + BlobLength; i++)
	{
		Output->push_back(InternalBuffer[i]);
	}
	BufferPosition += BlobLength;

	return true;
}
bool ByteBuffer::ReadBlob(std::basic_string<uint8_t> *Output)
{
	uint32_t BlobLength = 0;

	if (!ReadDataType((uint8_t)BBTypes::BB_BLOB_TYPE) || !Read<uint32_t>(&BlobLength))
		return false;

	if (BufferPosition + BlobLength > InternalBuffer.size())
	{
		fDBGPrint("%s - Blob (%lli) is larger than the buffer (%lli), check the endians.", __FUNCTION__, BufferPosition + BlobLength, InternalBuffer.size());
		__debugbreak();
		return false;
	}

	for (uint32_t i = BufferPosition; i < BufferPosition + BlobLength; i++)
	{
		Output->push_back(InternalBuffer[i]);
	}
	BufferPosition += BlobLength;

	return true;
}
bool ByteBuffer::ReadArrayStart(uint8_t ExpectedType, uint32_t *ElementCount, uint32_t *ElementSize)
{
	uint8_t StoredType = 0;
	uint32_t ArraySize = 0;

	// Get the array type.
	if (!Read<uint8_t>(&StoredType, false))
	{
		fDBGPrint("%s - No array header.", __FUNCTION__);
		if (ElementSize != nullptr)
			*ElementCount = 0;
		return false;
	}

	// Check against the type we want.
	if (StoredType - 100 != ExpectedType)
	{
		fDBGPrint("%s - Expected type %d but read type %d.", __FUNCTION__, ExpectedType, (StoredType - 100));
		return false;
	}

	// Total size.
	if (!Read<uint32_t>(&ArraySize))
	{
		if (ElementSize != nullptr)
			*ElementCount = 0;
		return false;
	}

	// Split over X elements.
	if (!Read<uint32_t>(ElementCount, false))
	{
		if (ElementSize != nullptr)
			*ElementCount = 0;
		return false;
	}

	if (ElementSize != nullptr)
		*ElementSize = ArraySize / *ElementCount;
	return true;
}
#pragma endregion

#pragma region LegacyWriteMethods
bool ByteBuffer::WriteBoolean(bool Input, bool Typecheck)
{
	return Write<bool>(Input, Typecheck);
}
bool ByteBuffer::WriteInt8(int8_t Input, bool Typecheck)
{
	return Write<int8_t>(Input, Typecheck);
}
bool ByteBuffer::WriteUInt8(uint8_t Input, bool Typecheck)
{
	return Write<uint8_t>(Input, Typecheck);
}
bool ByteBuffer::WriteInt16(int16_t Input, bool Typecheck)
{
	return Write<int16_t>(Input, Typecheck);
}
bool ByteBuffer::WriteUInt16(uint16_t Input, bool Typecheck)
{
	return Write<uint16_t>(Input, Typecheck);
}
bool ByteBuffer::WriteInt32(int32_t Input, bool Typecheck)
{
	return Write<int32_t>(Input, Typecheck);
}
bool ByteBuffer::WriteUInt32(uint32_t Input, bool Typecheck)
{
	return Write<uint32_t>(Input, Typecheck);
}
bool ByteBuffer::WriteInt64(int64_t Input, bool Typecheck)
{
	return Write<int64_t>(Input, Typecheck);
}
bool ByteBuffer::WriteUInt64(uint64_t Input, bool Typecheck)
{
	return Write<uint64_t>(Input, Typecheck);
}
bool ByteBuffer::WriteFloat32(float Input, bool Typecheck)
{
	return Write<float>(Input, Typecheck);
}
bool ByteBuffer::WriteFloat64(double Input, bool Typecheck)
{
	return Write<double>(Input, Typecheck);
}

bool ByteBuffer::WriteString(std::string &Input, bool Typecheck)
{ 
	if (Typecheck && !WriteDataType(BBTypes::BB_SIGNED_CHAR8_STRING_TYPE))
		return false;
	
	return Write((uint32_t)Input.length() + 1, (void *)Input.c_str());
}
bool ByteBuffer::WriteBlob(std::string *Input)
{ 
	if (!WriteDataType(BBTypes::BB_BLOB_TYPE) || !WriteUInt32(Input->length()))
		return false;
	else
		return Write((uint32_t)Input->length(), (void *)Input->data());
}
bool ByteBuffer::WriteBlob(std::basic_string<uint8_t> *Input)
{
	if (!WriteDataType(BBTypes::BB_BLOB_TYPE) || !WriteUInt32(Input->length()))
		return false;
	else
		return Write((uint32_t)Input->length(), (void *)Input->data());
}
bool ByteBuffer::WriteArrayStart(uint8_t Type, uint32_t ElementCount, uint32_t ElementSize)
{
	// Type is BBType + 100.
	return Write<uint8_t>(Type + 100, false)
		&& Write<uint32_t>(ElementSize * ElementCount)
		&& Write<uint32_t>(ElementCount, false);
}
#pragma endregion
