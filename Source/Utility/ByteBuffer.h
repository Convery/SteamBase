/*
This class is licensed under the MIT license.
Author: (https://github.com/)Convery
*/

#pragma once

class ByteBuffer
{
    /*
    The buffer will expand when needed but will not shrink.
    The position indicates the next read/write.
    SecureMode XORs the data with 0xCC to thwart dumping.
    */
    std::basic_string<uint8_t> InternalBuffer;
    uint32_t BufferPosition;
    bool SecureMode;

public:
    // Datatypes we can store.
    enum class BBType : uint8_t
    {
        BB_NO_TYPE = 0,
        BB_BOOL_TYPE = 1,
        BB_SIGNED_CHAR8_TYPE = 2,
        BB_UNSIGNED_CHAR8_TYPE = 3,
        BB_WCHAR16_TYPE = 4,
        BB_SIGNED_INTEGER16_TYPE = 5,
        BB_UNSIGNED_INTEGER16_TYPE = 6,
        BB_SIGNED_INTEGER32_TYPE = 7,
        BB_UNSIGNED_INTEGER32_TYPE = 8,
        BB_SIGNED_INTEGER64_TYPE = 9,
        BB_UNSIGNED_INTEGER64_TYPE = 10,
        BB_RANGED_SIGNED_INTEGER32_TYPE = 11,
        BB_RANGED_UNSIGNED_INTEGER32_TYPE = 12,
        BB_FLOAT32_TYPE = 13,
        BB_FLOAT64_TYPE = 14,
        BB_RANGED_FLOAT32_TYPE = 15,
        BB_SIGNED_CHAR8_STRING_TYPE = 16,
        BB_UNSIGNED_CHAR8_STRING_TYPE = 17,
        BB_MBSTRING_TYPE = 18,
        BB_BLOB_TYPE = 19,
        BB_NAN_TYPE = 20,
        BB_FULL_TYPE = 21,
        BB_MAX_TYPE = 32
    };

    // Initialize the internal buffer.
    ByteBuffer(uint32_t InputLength, void *InputData = nullptr);
    ByteBuffer(std::basic_string<uint8_t> *InputData);
    ByteBuffer(std::string *InputData);
    ByteBuffer();
    ~ByteBuffer();

    // Property access.
    uint32_t GetSize();                 // Get the buffer length.
    uint32_t GetLength();               // Get the buffer length.
    uint32_t GetPosition();             // Return BufferPosition.
    bool SetPosition(uint32_t Pos);     // Set BufferPosition, returns true if Pos < Buffer.size.
    template <typename ReturnType>      // Return a pointer to a safe buffer,
    ReturnType *GetBuffer();            // with the contents of InternalBuffer.

    // Utility methods.
    void PrintNext(FILE *Handle);       // Prints the next data entry in the buffer to a handle.
    bool ToggleSecure();                // Obfuscates the data, returns the current status.
    uint8_t PeekByte();                 // Return the next byte, useful to check for a datatype.
    void Rewind();                      // Sets the position to 0.
    void Clear();                       // Clears and deallocates all memory and calls Rewind.

    // Core functionallity.
    bool Read(uint32_t ReadCount, void *OutBuffer = nullptr);
    bool Write(uint32_t WriteCount, void *InBuffer = nullptr);
    bool ReadDatatype(BBType Type);    // Internal method.
    bool WriteDatatype(BBType Type);   // Internal method.

    // Read methods, typecheck reads a byte prefix from data.
    bool ReadBlob(std::string *Output, bool Typecheck = true);
    bool ReadBlob(std::basic_string<uint8_t> *Output, bool Typecheck = true);
    bool ReadBlob(uint32_t DataLength, void *DataBuffer, bool Typecheck = true);
    std::basic_string<uint8_t> ReadBlob(bool Typecheck = true);
    bool ReadBoolean(bool *Output, bool Typecheck = true);
    bool ReadBoolean(bool Typecheck = true);
    bool ReadInt8(int8_t *Output, bool Typecheck = true);
    int8_t ReadInt8(bool Typecheck = true);
    bool ReadInt16(int16_t *Output, bool Typecheck = true);
    int16_t ReadInt16(bool Typecheck = true);
    bool ReadInt32(int32_t *Output, bool Typecheck = true);
    int32_t ReadInt32(bool Typecheck = true);
    bool ReadInt64(int64_t *Output, bool Typecheck = true);
    int64_t ReadInt64(bool Typecheck = true);
    bool ReadUInt8(uint8_t *Output, bool Typecheck = true);
    uint8_t ReadUInt8(bool Typecheck = true);
    bool ReadUInt16(uint16_t *Output, bool Typecheck = true);
    uint16_t ReadUInt16(bool Typecheck = true);
    bool ReadUInt32(uint32_t *Output, bool Typecheck = true);
    uint32_t ReadUInt32(bool Typecheck = true);
    bool ReadUInt64(uint64_t *Output, bool Typecheck = true);
    uint64_t ReadUInt64(bool Typecheck = true);
    bool ReadFloat32(float *Output, bool Typecheck = true);
    float ReadFloat32(bool Typecheck = true);
    bool ReadFloat64(double *Output, bool Typecheck = true);
    double ReadFloat64(bool Typecheck = true);
    bool ReadString(std::string &Output, bool Typecheck = true);
    std::string ReadString(bool Typecheck = true);
    bool ReadArrayStart(BBType ExpectedType, uint32_t *ElementCount, uint32_t *ElementSize = nullptr);
    bool ReadArrayStart(uint32_t ExpectedType, uint32_t *ElementCount, uint32_t *ElementSize = nullptr);

    // Write methods, typecheck adds a byte prefix to data.
    bool WriteBlob(std::string *Input, bool Typecheck = true);
    bool WriteBlob(std::basic_string<uint8_t> *Input, bool Typecheck = true);
    bool WriteBlob(uint32_t DataLength, void *DataBuffer, bool Typecheck = true);
    bool WriteBoolean(bool Input, bool Typecheck = true);
    bool WriteInt8(int8_t Input, bool Typecheck = true);
    bool WriteInt16(int16_t Input, bool Typecheck = true);
    bool WriteInt32(int32_t Input, bool Typecheck = true);
    bool WriteInt64(int64_t Input, bool Typecheck = true);
    bool WriteUInt8(uint8_t Input, bool Typecheck = true);
    bool WriteUInt16(uint16_t Input, bool Typecheck = true);
    bool WriteUInt32(uint32_t Input, bool Typecheck = true);
    bool WriteUInt64(uint64_t Input, bool Typecheck = true);
    bool WriteFloat32(float Input, bool Typecheck = true);
    bool WriteFloat64(double Input, bool Typecheck = true);
    bool WriteString(std::string &Input, bool Typecheck = true);
    bool WriteArrayStart(BBType Type, uint32_t ElementCount, uint32_t ElementSize);
    bool WriteArrayStart(uint32_t Type, uint32_t ElementCount, uint32_t ElementSize);
};
