/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-03-10
	Notes:
		String manipulation and tokenisation.
*/

#pragma once

// Simple types.
using ByteString	= std::basic_string < uint8_t > ;
using ShortString	= std::basic_string < uint16_t >;
using LongString	= std::basic_string < uint32_t >;

class hString
{
public:
	// Formats a string using variadic arguments.
	static const char *va(const char *fmt, ...);

	// Seperate and join strings by a seperator.
	static std::vector<char *> Explode(char *Input, const char *Separator);
	static const char *Implode(std::vector<char *> &Input, const char *Separator);

	// Encode and decode strings.
	static const char *Base64Encode(char *String);
	static const char *Base64Decode(char *String);

	// Bytes to readable strings.
	static std::string ToReadableString(std::basic_string<uint8_t> &Input, const char *Token = "");
	static const char *ToReadableString(uint8_t *Input, uint32_t Length, const char *Token = "");
};
