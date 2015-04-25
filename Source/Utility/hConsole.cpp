/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Nicely formated console messages.
*/

#include "..\StdInclude.h"

static std::mutex ThreadSafe;
bool hConsole::LogToFile;
std::queue<std::string> hConsole::MessageQueue;
std::string hConsole::Filename;

DWORD _stdcall hConsole::PrintThread(void *)
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		ThreadSafe.lock();

		if (!MessageQueue.empty())
		{
			printf(MessageQueue.front().c_str());
			MessageQueue.pop();
		}
		ThreadSafe.unlock();
	}

	return 0;
}

bool hConsole::InitializeConsole(const char *Logfilename)
{
	// People using steams BigPicture mode doesn't like consoles.
	if (!strstr(GetCommandLineA(), "-nocon"))
	{
		// We create a console window if it doesn't exist.
		AllocConsole();

		// Take ownership of it.
		AttachConsole(GetCurrentProcessId());

		// Redirect STDOUT (printf) to the console.
		if (freopen("CON", "w", stdout) == nullptr)	
		{
			MessageBoxA(0, "Unable to redirect stdout to Console", "REDACTED", 0);
		}
	}

	// Resize the console.
	_COORD coord;
	coord.X = 100;
	coord.Y = 50;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = 49;
	Rect.Right = 99;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get handle.
	SetConsoleScreenBufferSize(Handle, coord);            // Set buffer size.
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set window size.

	// Check if we should use a logfile.
	if (Logfilename != nullptr)
	{
		LogToFile = true;
		Filename = Logfilename;
	}

	// Delete the old logfile.
	if (LogToFile)
	{
		if (remove(Filename.c_str()) != 0)
		{
			// Append to the old logfile.
			EnqueueFragmented(3, "INFO", new char *[3]{"==================", "Failed to delete this log =(", "=================="}, new char *[3]{"", "", ""});
		}
		else
		{
			// Append to create a new logfile.
			EnqueueMessage("INFO", "Starting up...", "");
			return true;
		}
	}

	return !LogToFile;
}
void hConsole::StartPrinting()
{
	CreateThread(NULL, NULL, PrintThread, NULL, NULL, NULL);
}

void hConsole::EnqueueMessage(char *Source, char *Message, char *Data, bool InstantPrint)
{
	char Time[7        + 1];
	char Src [4        + 1];
	char Msg [MSG_SIZE + 1];
	char Dta [6        + 1];
	std::string FormatedString;

	// Threadsafe operation.
	ThreadSafe.lock();

	// Clear any old data.
	memset(Time, ' ', 7);
	memset(Src, ' ', 4);
	memset(Msg, ' ', MSG_SIZE);
	memset(Dta, ' ', 6);

	// Create the timestamp.
	strcpy_s(Time, 7, hString::va("%u", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Global::StartupPoint).count()));

	// Truncate the args.
	if (Source)  memcpy(Src, Source, 4);
	if (Message) memcpy(Msg, Message, MSG_SIZE);
	if (Data)    memcpy(Dta, Data, 6);

	// Remove any null chars.
	bool clear = false;
	for (uint32_t i = 0; i < 7; i++)
	{
		if (!clear && Time[i] == '\0') clear = true;
		if (clear) Time[i] = ' ';
	}

	clear = false;
	for (uint32_t i = 0; i < 4; i++)
	{
		if (!clear && Src[i] == '\0') clear = true;
		if (clear) Src[i] = ' ';
	}

	clear = false;
	for (uint32_t i = 0; i < MSG_SIZE; i++)
	{
		if (!clear && Msg[i] == '\0') clear = true;
		if (clear) Msg[i] = ' ';
	}
	
	clear = false;
	for (uint32_t i = 0; i < 6; i++)
	{
		if (!clear && Dta[i] == '\0') clear = true;
		if (clear) Dta[i] = ' ';
	}

	// Terminate the strings
	Time[7]        = 0;
	Src [4]        = 0;
	Msg [MSG_SIZE] = 0;
	Dta [6]        = 0;

	// Format the string.
	FormatedString.append(Time);
	FormatedString.append(" | ");
	FormatedString.append(Src);
	FormatedString.append(" | ");
	FormatedString.append(Msg);

	if (strlen(Data))
	{
		FormatedString.append(" | ");
		FormatedString.append(Dta);
	}

	FormatedString.append("\n");

	OutputDebugStringA(FormatedString.c_str());
	
	// Print to the logfile.
	if (LogToFile)
	{
		FileSystem::WriteFile(Filename.c_str(), (void *)FormatedString.c_str(), FormatedString.length(), true);
	}
	if (InstantPrint)
	{
		printf(FormatedString.c_str());
	}
	else
	{
		MessageQueue.push(FormatedString);
	}
	ThreadSafe.unlock();
}
void hConsole::EnqueueFragmented(uint32_t FragmentCount, char *Source, char **Message, char **Data, bool InstantPrint)
{
	char Msg[74 + 1];
	char Dta[6  + 1];
	char Pos[7  + 1];
	std::string FormatedString;
	EnqueueMessage(Source, "Fragmented message:", "");

	// Threadsafe operation.
	ThreadSafe.lock();

	for (uint32_t i = 0; i < min(FragmentCount, 99); i++)
	{
		// Clear any old data.
		memset(Msg, ' ', 74);
		memset(Dta, ' ', 6);
		memset(Pos, ' ', 7);

		// Truncate the args.
		strcpy_s(Msg, 74, Message[i]);
		strcpy_s(Dta, 6, Data[i]);
		strcpy_s(Pos, 7, hString::va("(%i/%i)", (i + 1), min(FragmentCount, 99)));

		// Remove any null chars.
		bool clear = false;
		for (uint32_t j = 0; j < 74; j++)
		{
			if (!clear && Msg[j] == '\0') clear = true;
			if (clear) Msg[j] = ' ';
		}

		clear = false;
		for (uint32_t j = 0; j < 6; j++)
		{
			if (!clear && Dta[j] == '\0') clear = true;
			if (clear) Dta[j] = ' ';
		}

		clear = false;
		for (uint32_t j = 0; j < 7; j++)
		{
			if (!clear && Pos[j] == '\0') clear = true;
			if (clear) Pos[j] = ' ';
		}

		// Terminate the strings
		Msg[74] = 0;
		Dta[6]  = 0;
		Pos[7]  = 0;

		// Format the string.
		FormatedString.append(Pos);
		FormatedString.append(": ");
		FormatedString.append(Msg);

		if (strlen(Data[i]))
		{
			FormatedString.append("  | ");
			FormatedString.append(Dta);
			FormatedString.append("\n");
		}

		// Print to the logfile.
		if (LogToFile)
		{
			FileSystem::WriteFile(Filename.c_str(), (void *)FormatedString.c_str(), FormatedString.length(), true);
		}
		if (InstantPrint)
		{
			printf(FormatedString.c_str());
		}
		else
		{
			MessageQueue.push(FormatedString);
		}
	}	

	ThreadSafe.unlock();
}
