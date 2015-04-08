/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-02-16
	Notes:
		Filesystem interaction, Win32 and Posix compatible.
*/

#pragma once

class FileSystem
{
public:
	static bool WriteFile(const char *Filename, void *DataBuffer, uint32_t BufferLength, bool Append);
	static bool WriteFile(const char *Filename, ByteString &DataBuffer, bool Append);
	static bool ReadFile(const char *Filename, void *DataBuffer, uint32_t &BufferLength);
	static bool ReadFile(const char *Filename, ByteString &DataBuffer);

	static int64_t GetFileSize(const char *Filename);
	static bool FileExists(const char *Filename);
	static bool ListFiles(std::string Path, std::vector<std::string> *Results, const char *Extension = nullptr);
};