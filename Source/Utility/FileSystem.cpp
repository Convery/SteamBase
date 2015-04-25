/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-02-16
	Notes:
		Filesystem interaction, Win32 and Posix compatible.
*/

#include "..\StdInclude.h"

bool FileSystem::FileExists(const char *Filename)
{
	return GetFileSize(Filename) != -1;
}
int64_t FileSystem::GetFileSize(const char *Filename)
{
	std::ifstream File(Filename, std::ios::binary);
	std::streamsize Size = 0;

	// ifstream::tellg() returns -1 if there's no file.
	File.seekg(0, std::ios::end);
	Size = File.tellg();
	File.seekg(0, std::ios::beg);

	File.close();
	return Size;
}

bool FileSystem::ReadFile(const char *Filename, void *DataBuffer, uint32_t &BufferLength)
{
	// Waste of time.
	if (!FileExists(Filename))
		return false;

	std::ifstream File(Filename, std::ios::binary);
	int64_t ReadSize = min(BufferLength, GetFileSize(Filename));
	BufferLength = (uint32_t)ReadSize;

	// Read into the buffer.
	if (!File.read((char *)DataBuffer, ReadSize))
	{
		File.close();
		return false;
	}
	else
	{
		File.close();
		return true;
	}
}
bool FileSystem::ReadFile(const char *Filename, ByteString &DataBuffer)
{
	// Waste of time.
	if (!FileExists(Filename))
		return false;

	bool Result = false;
	uint32_t ReadSize = GetFileSize(Filename);
	uint8_t *ReadBuffer = new uint8_t[ReadSize];
	SecureZeroMemory(ReadBuffer, ReadSize);

	// Read the file.
	Result = ReadFile(Filename, ReadBuffer, ReadSize);

	// Append the data.
	DataBuffer.append(ReadBuffer, ReadSize);

	// Clear the buffer.
	SecureZeroMemory(ReadBuffer, ReadSize);
	delete[] ReadBuffer;

	return Result;
}
bool FileSystem::WriteFile(const char *Filename, void *DataBuffer, uint32_t BufferLength, bool Append)
{
	std::ofstream File(Filename, std::ios::binary | (Append ? std::ios::app : 0));

	File.write((const char *)DataBuffer, BufferLength);
	File.close();

	return true;
}
bool FileSystem::WriteFile(const char *Filename, ByteString &DataBuffer, bool Append)
{
	return WriteFile(Filename, (void *)DataBuffer.data(), DataBuffer.size(), Append);
}

static bool Internal_win32_ListFiles(std::string Path, std::vector<std::string>& Results, const char *Extension = nullptr)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	bool Result = false;

	// Append trailing slash.
	if (Path.back() != '\\')
	{
		Path.append("\\");
	}

	// Filename.
	Path.append("*");

	// Extension.
	if (Extension != nullptr)
	{
		if (*Extension != '.')
		{
			Path.append(".");
		}
		
		Path.append(Extension);
	}

	hFind = FindFirstFileA(Path.c_str(), &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// If not a directory.
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				Results.push_back(FindFileData.cFileName);
				Result = true;
			}
		} while (FindNextFileA(hFind, &FindFileData));
		FindClose(hFind);
	}

	return Result;
}
static bool Internal_posix_ListFiles(std::string Path, std::vector<std::string> *Results, const char *Extension = nullptr)
{
	// TODO: This.
	return false;
}
bool FileSystem::ListFiles(std::string Path, std::vector<std::string>& Results, const char *Extension)
{
#ifdef _WIN32
	return Internal_win32_ListFiles(Path, Results, Extension);
#else
	return Internal_posix_ListFiles(Path, Results, Extension);
#endif
}
