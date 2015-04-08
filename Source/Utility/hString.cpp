/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-03-10
	Notes:
		String manipulation and tokenisation.
*/

#include "..\StdInclude.h"

#pragma region Variadic
static char VariadicBuffer[4][8192];
static uint32_t NextVariadicBufferIndex;
static std::mutex ThreadSafe;

const char *hString::va(const char *fmt, ...)
{
	va_list VarArgs;
	int32_t StringLength = 0;
	char *DestinationBuffer = nullptr;

	ThreadSafe.lock();
	DestinationBuffer = &VariadicBuffer[NextVariadicBufferIndex][0];
	SecureZeroMemory(DestinationBuffer, 8192);							// Clear any old data..
	NextVariadicBufferIndex = (NextVariadicBufferIndex + 1) % 4;		// Mod by buffercount.

	va_start(VarArgs, fmt);
	StringLength = _vsnprintf_s(DestinationBuffer, 8192, _TRUNCATE, fmt, VarArgs);
	va_end(VarArgs);

	if (StringLength < 0 || StringLength == 8192)
	{
		fDBGPrint("", "%s - Attempted to overrun string, increase the buffer. StrLen: %i", __FUNCTION__, StringLength);
	}

	ThreadSafe.unlock();
	return DestinationBuffer;
}
#pragma endregion

#pragma region Tokens
std::vector<char *> hString::Explode(char *Input, const char *Separator)
{
	std::vector<char *> Result;
	char *Context = nullptr;
	char *Token = strtok_s(Input, Separator, &Context);

	while (Token)
	{
		Result.push_back(Token);
		Token = strtok_s(NULL, Separator, &Context);
	}

	return Result;
}
const char *hString::Implode(std::vector<char *> &Input, const char *Separator)
{
	static std::string Result;
	Result.clear();

	for (uint32_t i = 0; i < Input.size(); i++)
	{
		Result.append(Separator);
		Result.append(Input[i]);
	}

	return Result.c_str();
}
#pragma endregion

#pragma region Base64
static char Base64Result[8192];
static const char Base64Chars[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

// Validate character.
static inline bool isBase64(char Char)
{
	return (isalnum(Char) || Char == '+' || Char == '/');
}

// Find the char index.
static inline char findBase64(char Char)
{
	for (uint8_t i = 0; i < sizeof(Base64Chars); i++)
	{
		if (Char == Base64Chars[i])
			return i;
	}

	return 0;
}

#define capIndex(x) min(x, 8191)
const char *hString::Base64Encode(char *String)
{
	int32_t i = 0, j = 0, k = 0, Length = strlen(String);
	char Array3[3];
	char Array4[4];

	while (Length--)
	{
		Array3[i++] = *(String++);

		if (i == 3)
		{
			Array4[0] = (Array3[0] & 0xFC) >> 2;
			Array4[1] = ((Array3[0] & 0x03) << 4) + ((Array3[1] & 0xF0) >> 4);
			Array4[2] = ((Array3[1] & 0x0F) << 2) + ((Array3[2] & 0xC0) >> 6);
			Array4[3] = Array3[2] & 0x3F;

			for (i = 0; i < 4; i++)
			{
				Base64Result[capIndex(k + i)] = Base64Chars[Array4[i]];
			}

			k += i;
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
		{
			Array3[j] = '\0';
		}

		Array4[0] = (Array3[0] & 0xFC) >> 2;
		Array4[1] = ((Array3[0] & 0x03) << 4) + ((Array3[1] & 0xF0) >> 4);
		Array4[2] = ((Array3[1] & 0x0F) << 2) + ((Array3[2] & 0xC0) >> 6);
		Array4[3] = Array3[2] & 0x3F;

		for (j = 0; j < i + 1; j++)
		{
			Base64Result[capIndex(k + j)] = Base64Chars[Array4[j]];
		}

		while (i++ < 3)
		{
			Base64Result[capIndex(k + i + j)] = '=';
		}
	}

	Base64Result[capIndex(k + i + j + 1)] = '\0';

	return Base64Result;
}
const char *hString::Base64Decode(char *String)
{
	int32_t inLength = strlen(String);
	int32_t i = 0, j = 0, k = 0, in = 0;
	char Array3[3];
	char Array4[4];

	while (inLength-- && String[in] != '=' && isBase64(String[in]))
	{
		Array4[i++] = String[in++];

		if (i == 4)
		{
			for (i = 0; i < 4; i++)
			{
				Array4[i] = findBase64(Array4[i]);
			}

			Array3[0] = (Array4[0] << 2) + ((Array4[1] & 0x30) >> 4);
			Array3[1] = ((Array4[1] & 0xF) << 4) + ((Array4[2] & 0x3C) >> 2);
			Array3[2] = ((Array4[2] & 0x3) << 6) + Array4[3];

			for (i = 0; i < 3; i++)
			{
				Base64Result[capIndex(k + i)] = Array3[i];
			}

			k += i;
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
		{
			Array4[j] = 0;
		}

		for (j = 0; j < 4; j++)
		{
			Array4[j] = findBase64(Array4[j]);
		}

		Array3[0] = (Array4[0] << 2) + ((Array4[1] & 0x30) >> 4);
		Array3[1] = ((Array4[1] & 0xF) << 4) + ((Array4[2] & 0x3C) >> 2);
		Array3[2] = ((Array4[2] & 0x3) << 6) + Array4[3];

		for (j = 0; j < i - 1; j++)
		{
			Base64Result[capIndex(k + j)] = Array3[j];
		}
	}
	Base64Result[capIndex(k + j + 1)] = '\0';

	return Base64Result;
}
#pragma endregion

#pragma region HexToText
std::string hString::ToReadableString(std::basic_string<uint8_t> &Input, const char *Token)
{
	std::string Result;

	// Append the bytes in readable form.
	for (uint32_t i = 0; i < Input.size(); i++)
	{
		Result.append(va("%02X%s", *(uint8_t *)(Input.data() + i), Token));
	}

	return Result;
}
const char *hString::ToReadableString(uint8_t *Input, uint32_t Length, const char *Token)
{
	static char Result[1024] = {};
	const char hex_chars[] = "0123456789ABCDEF";
	size_t i = 0, j = 0;
	size_t TokenLen = strlen(Token);

	while (i < Length)
	{
		Result[j++] = hex_chars[(Input[i] >> 4) & 0x0F];
		Result[j++] = hex_chars[Input[i] & 0x0F];
		i++;

		for (size_t c = 0; c < TokenLen; c++)
		{
			Result[j++] = Token[c];
		}
	}

	Result[j++] = '\0';
	return Result;
}
#pragma endregion
