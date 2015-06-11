/*
This class is licensed under the MIT license.
Author: (https://github.com/)Convery
*/

#include "..\StdInclude.h"

// Initialize the internal buffer.
ByteBuffer::ByteBuffer()
{
    BufferPosition = 0;
    SecureMode = false;
}
ByteBuffer::~ByteBuffer()
{
    // Clear the memory.
    for (uint32_t i = 0; i < InternalBuffer.size(); i++)
    {
        InternalBuffer[i] = 0xCC;
    }

    InternalBuffer.clear(); // Deallocate the buffer.
    GetBuffer<void>();      // Clear any static memory.

    // Hack to get some templates generated.
    if (false)
    {
        GetBuffer<char>();
        GetBuffer<int8_t>();
        GetBuffer<uint8_t>();
    }
}
ByteBuffer::ByteBuffer(uint32_t InputLength, void *InputData) : ByteBuffer()
{
    InternalBuffer.append((uint8_t *)InputData, InputLength);
}
ByteBuffer::ByteBuffer(std::basic_string<uint8_t> *InputData) : ByteBuffer()
{
    InternalBuffer.append(*InputData);
}
ByteBuffer::ByteBuffer(std::string *InputData) : ByteBuffer()
{
    InternalBuffer.append((uint8_t *)InputData->data(), InputData->size());
}

// Property access.
uint32_t ByteBuffer::GetSize()
{
    return InternalBuffer.size();
}
uint32_t ByteBuffer::GetLength()
{
    return InternalBuffer.size();
}
uint32_t ByteBuffer::GetPosition()
{
    return BufferPosition;
}
bool ByteBuffer::SetPosition(uint32_t Pos)
{
    BufferPosition = min(Pos, InternalBuffer.size());
    return Pos <= InternalBuffer.size();
}
template <typename ReturnType>
ReturnType *ByteBuffer::GetBuffer()
{
    static void *SafeBuffer = nullptr;
    if (SafeBuffer == nullptr)
    {
        std::vector<int> Cake;
        free(SafeBuffer);
        SafeBuffer = nullptr;
    }

    if (InternalBuffer.size())
    {
        SafeBuffer = malloc(InternalBuffer.size());
        if (SafeBuffer == NULL)
        {
            SafeBuffer = nullptr;
            return nullptr;
        }

        if (SecureMode)
        {
            for (uint32_t i = 0; i < InternalBuffer.size(); i++)
            {
                InternalBuffer[i] ^= 0xCC;
            }
        }
    }

    return (ReturnType *)SafeBuffer;
}

// Utility methods.
void ByteBuffer::PrintNext(FILE *Handle)
{
    std::string BlobData;
    bool BoolData;
    float FloatData;
    double DoubleData;
    int8_t sInt8;
    uint8_t uInt8;

    switch ((BBType)PeekByte())
    {
    case BBType::BB_BLOB_TYPE:
        if (ReadBlob(&BlobData))
        {
            fprintf(Handle, "Blob of length %i:\n", BlobData.length());
            for (uint32_t i = 0; i < BlobData.length(); i++)
                fprintf(Handle, "%02X ", BlobData[i]);
            fprintf(Handle, "\n");
        }
        break;

    case BBType::BB_BOOL_TYPE:
        if (ReadBoolean(&BoolData))
            fprintf(Handle, "Bool: %s\n", BoolData ? "true" : "false");
        break;

    case BBType::BB_FLOAT32_TYPE:
        if (ReadFloat32(&FloatData))
            fprintf(Handle, "Float: %f\n", FloatData);
        break;

    case BBType::BB_FLOAT64_TYPE:
        if (ReadFloat64(&DoubleData))
            fprintf(Handle, "Double: %f\n", DoubleData);
        break;

    case BBType::BB_SIGNED_CHAR8_TYPE:
        if (ReadInt8(&sInt8))
            fprintf(Handle, "Int8: %i\n", sInt8);
        break;

    case BBType::BB_UNSIGNED_CHAR8_TYPE:
        if (ReadUInt8(&uInt8))
            fprintf(Handle, "uInt8: %i\n", uInt8);
        break;

    default:
        fprintf(Handle, "Unhandled type\n");
    }
}
bool ByteBuffer::ToggleSecure()
{
    SecureMode = !SecureMode;
    for (uint32_t i = 0; i < InternalBuffer.size(); i++)
        InternalBuffer[i] ^= 0xCC;
    return SecureMode;
}
uint8_t ByteBuffer::PeekByte()
{
    uint8_t CurrentByte = 0;

    ReadUInt8(&CurrentByte, false);
    SetPosition(GetPosition() - 1);

    return CurrentByte;
}
void ByteBuffer::Rewind()
{
    SetPosition(0);
}
void ByteBuffer::Clear()
{
    // Clear the memory.
    for (uint32_t i = 0; i < InternalBuffer.size(); i++)
    {
        InternalBuffer[i] = 0xCC;
    }

    InternalBuffer.clear(); // Deallocate the buffer.
    GetBuffer<void>();      // Clear any static memory.
    Rewind();               // Reset the position.
}

// Core functionallity.
bool ByteBuffer::Read(uint32_t ReadCount, void *OutBuffer)
{
    if (BufferPosition + ReadCount > InternalBuffer.length())
    {
        fprintf(stderr, "ByteBuffer::Read tried to read out of bounds. Missing bytes: %i\n", BufferPosition + ReadCount - InternalBuffer.length());
        return false;
    }

    if (OutBuffer != nullptr)
    {
        memcpy(OutBuffer, InternalBuffer.data() + BufferPosition, ReadCount);
    }

    BufferPosition += ReadCount;
    return true;
}
bool ByteBuffer::Write(uint32_t WriteCount, void *InBuffer)
{
    if (InBuffer != nullptr)
    {
        if (BufferPosition == InternalBuffer.length())
        {
            InternalBuffer.append((const uint8_t *)InBuffer, WriteCount);
            BufferPosition += WriteCount;
            return true;
        }
        else
        {
            if (BufferPosition < InternalBuffer.length())
            {
                if (BufferPosition + WriteCount < InternalBuffer.length())
                {
                    for (uint32_t i = 0; i < WriteCount; i++)
                    {
                        InternalBuffer[i] = ((const uint8_t *)InBuffer)[i];
                        BufferPosition++;
                    }
                    return true;
                }
                else
                {
                    uint32_t FreeBytes = InternalBuffer.length() - BufferPosition;
                    return Write(FreeBytes, InBuffer) && Write(WriteCount - FreeBytes, (uint8_t *)InBuffer + FreeBytes);
                }
            }
            else
            {
                fprintf(stderr, "ByteBuffer::Write, BufferPosition > InternalBuffer.length");
                return false;
            }
        }
    }
    else
    {
        BufferPosition += WriteCount;
        return true;
    }
}
bool ByteBuffer::ReadDatatype(BBType Type)
{
    if (PeekByte() == (uint8_t)Type)
    {
        BufferPosition++;
        return true;
    }
    else
    {
        return false;
    }
}
bool ByteBuffer::WriteDatatype(BBType Type)
{
    return Write(1, &Type);
}

// Read methods, typecheck reads a byte prefix from data.
bool ByteBuffer::ReadBlob(std::string *Output, bool Typecheck)
{
    uint32_t BlobLength = 0;

    if (Typecheck && !ReadDatatype(BBType::BB_BLOB_TYPE))
        return false;

    if (!ReadUInt32(&BlobLength))
        return false;

    if (BufferPosition + BlobLength > InternalBuffer.size())
    {
        fprintf(stderr, "ByteBuffer::ReadBlob, blob (%lli) is larger than the bytebuffer (%lli), check your endians!", BufferPosition + BlobLength, InternalBuffer.size());
        return false;
    }

    for (uint32_t i = BufferPosition; i < BufferPosition + BlobLength; i++)
    {
        Output->push_back(InternalBuffer[i]);
    }
    BufferPosition += BlobLength;

    return true;
}
bool ByteBuffer::ReadBlob(std::basic_string<uint8_t> *Output, bool Typecheck)
{
    uint32_t BlobLength = 0;

    if (Typecheck && !ReadDatatype(BBType::BB_BLOB_TYPE))
        return false;

    if (!ReadUInt32(&BlobLength))
        return false;

    if (BufferPosition + BlobLength > InternalBuffer.size())
    {
        fprintf(stderr, "ByteBuffer::ReadBlob, blob (%lli) is larger than the bytebuffer (%lli), check your endians!", BufferPosition + BlobLength, InternalBuffer.size());
        return false;
    }

    for (uint32_t i = BufferPosition; i < BufferPosition + BlobLength; i++)
    {
        Output->push_back(InternalBuffer[i]);
    }
    BufferPosition += BlobLength;

    return true;
}
bool ByteBuffer::ReadBlob(uint32_t DataLength, void *DataBuffer, bool Typecheck)
{
    uint32_t BlobLength = 0;

    if (Typecheck && !ReadDatatype(BBType::BB_BLOB_TYPE))
        return false;

    if (!ReadUInt32(&BlobLength))
        return false;

    if (BufferPosition + BlobLength > InternalBuffer.size())
    {
        fprintf(stderr, "ByteBuffer::ReadBlob, blob (%lli) is larger than the bytebuffer (%lli), check your endians!", BufferPosition + BlobLength, InternalBuffer.size());
        return false;
    }

    if (BufferPosition + BlobLength > DataLength)
    {
        fprintf(stderr, "ByteBuffer::ReadBlob, blob (%lli) is larger than the result buffer (%lli), check your endians!", BlobLength, DataLength);
    }

    memcpy(DataBuffer, InternalBuffer.data() + BufferPosition, min(BlobLength, DataLength));
    BufferPosition += min(BufferPosition + BlobLength, DataLength);

    return true;
}
std::basic_string<uint8_t> ByteBuffer::ReadBlob(bool Typecheck)
{
    std::basic_string<uint8_t> Result;

    if (!ReadBlob(&Result, Typecheck))
    {
        Result.clear();
    }

    return Result;
}
bool ByteBuffer::ReadBoolean(bool *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_BOOL_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
bool ByteBuffer::ReadBoolean(bool Typecheck)
{
    bool Result;

    if (!ReadBoolean(&Result, Typecheck))
    {
        Result = false;
    }

    return Result;
}
bool ByteBuffer::ReadInt8(int8_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_SIGNED_CHAR8_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
int8_t ByteBuffer::ReadInt8(bool Typecheck)
{
    int8_t Result;

    if (!ReadInt8(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadInt16(int16_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_SIGNED_INTEGER16_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
int16_t ByteBuffer::ReadInt16(bool Typecheck)
{
    int16_t Result;

    if (!ReadInt16(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadInt32(int32_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_SIGNED_INTEGER32_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
int32_t ByteBuffer::ReadInt32(bool Typecheck)
{
    int32_t Result;

    if (!ReadInt32(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadInt64(int64_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_SIGNED_INTEGER64_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
int64_t ByteBuffer::ReadInt64(bool Typecheck)
{
    int64_t Result;

    if (!ReadInt64(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadUInt8(uint8_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_UNSIGNED_CHAR8_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
uint8_t ByteBuffer::ReadUInt8(bool Typecheck)
{
    uint8_t Result;

    if (!ReadUInt8(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadUInt16(uint16_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_UNSIGNED_INTEGER16_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
uint16_t ByteBuffer::ReadUInt16(bool Typecheck)
{
    uint16_t Result;

    if (!ReadUInt16(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadUInt32(uint32_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_UNSIGNED_INTEGER32_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
uint32_t ByteBuffer::ReadUInt32(bool Typecheck)
{
    uint32_t Result;

    if (!ReadUInt32(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadUInt64(uint64_t *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_UNSIGNED_INTEGER64_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
uint64_t ByteBuffer::ReadUInt64(bool Typecheck)
{
    uint64_t Result;

    if (!ReadUInt64(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadFloat32(float *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_FLOAT32_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
float ByteBuffer::ReadFloat32(bool Typecheck)
{
    float Result;

    if (!ReadFloat32(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadFloat64(double *Output, bool Typecheck)
{
    if (!Typecheck || ReadDatatype(BBType::BB_FLOAT64_TYPE))
        return Read(sizeof(*Output), Output);
    else
        return false;
}
double ByteBuffer::ReadFloat64(bool Typecheck)
{
    double Result;

    if (!ReadFloat64(&Result, Typecheck))
    {
        Result = -1;
    }

    return Result;
}
bool ByteBuffer::ReadString(std::string &Output, bool Typecheck)
{
    uint32_t StringLength = 0;

    if (Typecheck && !ReadDatatype(BBType::BB_SIGNED_CHAR8_STRING_TYPE))
        return false;

    StringLength = strlen((char *)InternalBuffer.data() + BufferPosition) + 1;
    Output.append((char *)InternalBuffer.data() + BufferPosition, StringLength);

    BufferPosition += StringLength;
    return true;
}
std::string ByteBuffer::ReadString(bool Typecheck)
{
    std::string Result;

    if (!ReadString(Result, Typecheck))
    {
        Result.clear();
    }

    return Result;
}
bool ByteBuffer::ReadArrayStart(BBType ExpectedType, uint32_t *ElementCount, uint32_t *ElementSize)
{
    uint8_t StoredType = 0;
    uint32_t ArraySize = 0;

    // Get the array type.
    if (!ReadUInt8(&StoredType, false))
    {
        fprintf(stderr, "ByteBuffer::ReadArrayStart - No array header.");
        if (ElementSize != nullptr)
            *ElementCount = 0;
        return false;
    }

    // Check against the type we want.
    if (StoredType - 100 != (uint8_t)ExpectedType)
    {
        fprintf(stderr, "ByteBuffer::ReadArrayStart - Expected type %d but read type %d.", ExpectedType, (StoredType - 100));
        return false;
    }

    // Total size.
    if (!ReadUInt32(&ArraySize))
    {
        if (ElementSize != nullptr)
            *ElementCount = 0;
        return false;
    }

    // Split over X elements.
    if (!ReadUInt32(ElementCount, false))
    {
        if (ElementSize != nullptr)
            *ElementCount = 0;
        return false;
    }

    if (ElementSize != nullptr)
        *ElementSize = ArraySize / *ElementCount;

    return true;
}
bool ByteBuffer::ReadArrayStart(uint32_t ExpectedType, uint32_t *ElementCount, uint32_t *ElementSize)
{
    return ReadArrayStart((BBType)ExpectedType, ElementCount, ElementSize);
}

// Write methods, typecheck adds a byte prefix to data.
bool ByteBuffer::WriteBlob(std::string *Input, bool Typecheck)
{
    if ((Typecheck && !WriteDatatype(BBType::BB_BLOB_TYPE)) || !WriteUInt32(Input->length()))
        return false;
    else
        return Write(Input->length(), (void *)Input->data());
}
bool ByteBuffer::WriteBlob(std::basic_string<uint8_t> *Input, bool Typecheck)
{
    if ((Typecheck && !WriteDatatype(BBType::BB_BLOB_TYPE)) || !WriteUInt32(Input->length()))
        return false;
    else
        return Write(Input->length(), (void *)Input->data());
}
bool ByteBuffer::WriteBlob(uint32_t DataLength, void *DataBuffer, bool Typecheck)
{
    if ((Typecheck && !WriteDatatype(BBType::BB_BLOB_TYPE)) || !WriteUInt32(DataLength))
        return false;
    else
        return Write(DataLength, DataBuffer);
}
bool ByteBuffer::WriteBoolean(bool Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_BOOL_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteInt8(int8_t Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_SIGNED_CHAR8_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteInt16(int16_t Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_SIGNED_INTEGER16_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteInt32(int32_t Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_SIGNED_INTEGER32_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteInt64(int64_t Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_SIGNED_INTEGER64_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteUInt8(uint8_t Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_UNSIGNED_CHAR8_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteUInt16(uint16_t Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_UNSIGNED_INTEGER16_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteUInt32(uint32_t Input, bool Typecheck){
    if (!Typecheck || WriteDatatype(BBType::BB_UNSIGNED_INTEGER32_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteUInt64(uint64_t Input, bool Typecheck){
    if (!Typecheck || WriteDatatype(BBType::BB_UNSIGNED_INTEGER64_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteFloat32(float Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_FLOAT32_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteFloat64(double Input, bool Typecheck)
{
    if (!Typecheck || WriteDatatype(BBType::BB_FLOAT64_TYPE))
        return Write(sizeof(Input), &Input);
    else
        return false;
}
bool ByteBuffer::WriteString(std::string &Input, bool Typecheck)
{
    if (Typecheck && !WriteDatatype(BBType::BB_SIGNED_CHAR8_STRING_TYPE))
        return false;

    return Write(Input.length() + 1, (void *)Input.c_str());
}
bool ByteBuffer::WriteArrayStart(BBType Type, uint32_t ElementCount, uint32_t ElementSize)
{
    return WriteArrayStart(Type, ElementCount, ElementSize);
}
bool ByteBuffer::WriteArrayStart(uint32_t Type, uint32_t ElementCount, uint32_t ElementSize)
{
    // Type is BBType + 100.
    return WriteUInt8(Type + 100, false)
        && WriteUInt32(ElementSize * ElementCount)
        && WriteUInt32(ElementCount, false);
}
