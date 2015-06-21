/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Nicely formated console messages.
*/

#pragma once

#define MSG_SIZE 82 // Fits the console width
class hConsole
{
	static bool LogToFile;
	static std::queue<std::string> MessageQueue;
	static std::string Filename;

	static DWORD _stdcall PrintThread(void *);
	static void Print(const char* message);

public:
	static bool InitializeConsole(const char *Logfilename = nullptr);
	static void StartPrinting();

	static void EnqueueMessage(char *Source, char *Message, char *Data, bool InstantPrint = false);
	static void EnqueueFragmented(uint32_t FragmentCount, char *Source, char **Message, char **Data, bool InstantPrint = false);
};
