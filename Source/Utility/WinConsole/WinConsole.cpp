/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Sokie
	Started: 2015-05-25
	Notes:
		A win32 console.
*/

#include "..\..\StdInclude.h"

static std::mutex ThreadSafe;
bool WinConsole::LogToFile;
std::string WinConsole::Filename;
static HWND aDiag;
WNDPROC WinConsole::oldEditProc;

LRESULT CALLBACK WinConsole::subEditProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN && wParam == VK_RETURN)
	{
		HWND parentDlg = GetParent(wnd);

		HWND edit = GetDlgItem(parentDlg, IDC_EDIT2);

		TCHAR buff[1024];
		GetWindowText(edit, buff, 1024);

		AppendText(parentDlg, "\n]");
		AppendText(parentDlg, buff);
		AppendText(parentDlg, "\n");

		ConsoleCommandHandler::ExecuteCommand(buff);

		SetWindowText(edit, "");

		return 0;
	}

	return CallWindowProc(oldEditProc, wnd, msg, wParam, lParam);
}

static HMODULE GetThisDllHandle()
{
	MEMORY_BASIC_INFORMATION info;
	size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)GetThisDllHandle, &info, sizeof(info));
	return len ? (HMODULE)info.AllocationBase : NULL;
}

DWORD _stdcall WinConsole::ConsoleThread(void  *lparam)
{
	ThreadSafe.lock();
	//HMODULE Module = GetModuleHandle(NULL);
	//HACKY HACK HACK
	HMODULE Module = GetThisDllHandle();
	aDiag = CreateDialog(Module,
		MAKEINTRESOURCE(IDD_DIALOG1),
		0,
		(DLGPROC)DialogProc);

	ShowWindow(aDiag, SW_SHOW);
	ThreadSafe.unlock();
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

DWORD _stdcall WinConsole::StdOutThread(void  *lparam)
{
	HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE g_hChildStd_OUT_Rd = NULL;
	DWORD dwRead, dwWritten;
	CHAR chBuf[4096];
	BOOL bSuccess = FALSE;
	for (;;)
	{
		bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, 4096, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) continue;
		
		WinConsole::Print(chBuf);
	}
}

void WinConsole::ActivateCommandField()
{
	HWND hSta = GetDlgItem(aDiag, IDC_EDIT2);
	SendMessageA(hSta, EM_SETREADONLY, 0, 0);
}

void WinConsole::Print(const char* message)
{
	// Clear message
	char* buffer = (char*)message;
	int len = strlen(buffer);
	if (len && buffer[len - 1] == '\n')
	{
		for (int i = len - 2; i >= 0; i--)
		{
			if (buffer[i] != ' ')
			{
				buffer[i + 1] = '\n';
				buffer[i + 2] = 0;
				break;
			}
		}
	}

	//if user manually closes console there is no reason to send events
	if (aDiag)
	{
		AppendText(aDiag, (char *)message);
	}
}

bool WinConsole::InitializeConsole(const char *Logfilename)
{
	// People using steams BigPicture mode doesn't like consoles.
	if (!strstr(GetCommandLineA(), "-nocon"))
	{
		ThreadSafe.lock();
		HANDLE td = CreateThread(NULL, NULL, ConsoleThread, NULL, NULL, NULL);
		ThreadSafe.unlock();
		//does not work
		//HANDLE tout = CreateThread(NULL, NULL, StdOutThread, NULL, NULL, NULL);
	}
	
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

void WinConsole::EnqueueMessage(char *Source, char *Message, char *Data, bool InstantPrint)
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
    snprintf(Time, 7, "%u", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Global::StartupPoint).count());

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
	
	// Print to the logfile.
	if (LogToFile)
	{
		FileSystem::WriteFile(Filename.c_str(), (void *)FormatedString.c_str(), FormatedString.length(), true);
	}

	WinConsole::Print(FormatedString.c_str());
	ThreadSafe.unlock();
}
void WinConsole::EnqueueFragmented(uint32_t FragmentCount, char *Source, char **Message, char **Data, bool InstantPrint)
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
		WinConsole::Print(FormatedString.c_str());
	}	

	ThreadSafe.unlock();
}

BOOL WinConsole::OnDlgInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HWND hSta = GetDlgItem(hwnd, IDC_EDIT2);
	oldEditProc = (WNDPROC)SetWindowLongPtr(hSta, GWLP_WNDPROC, (LONG_PTR)subEditProc);

	HICON t = LoadIcon(GetThisDllHandle(), MAKEINTRESOURCE(IDI_ICON2));
	SendMessageA(hwnd, WM_SETICON, ICON_BIG, (LPARAM)t);
	SendMessageA(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)t);

	HWND headerLogoHWND = GetDlgItem(hwnd, IDC_STATIC2);

	/*LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
	SetWindowLong(hwnd, GWL_STYLE, lStyle);*/

	return TRUE;
}

INT_PTR CALLBACK WinConsole::DialogProc(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	switch (uMsg) {	
		HANDLE_MSG(hwndDlg, WM_CLOSE, OnDlgClose);
		HANDLE_MSG(hwndDlg, WM_INITDIALOG, OnDlgInitDialog);
		HANDLE_MSG(hwndDlg, WM_COMMAND, OnDlgCommand);
	}

	return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
}

void WinConsole::OnDlgCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	//NO-OP for now
}

void WinConsole::OnDlgClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
	aDiag = nullptr;

	ConsoleCommandHandler::ExecuteCommand("quit;");
}

void WinConsole::AppendText(const HWND &hwnd, TCHAR *newText)
{
	// get edit control from dialog
	HWND hwndOutput = GetDlgItem(hwnd, IDC_EDIT1);

	// get the current selection
	DWORD StartPos, EndPos;
	SendMessageA(hwndOutput, EM_GETSEL, reinterpret_cast<WPARAM>(&StartPos), reinterpret_cast<WPARAM>(&EndPos));

	// move the caret to the end of the text
	int outLength = GetWindowTextLength(hwndOutput);
	int oldOutLength = outLength;
	if (outLength > 20000)
	{
		SetWindowText(hwndOutput, "");
		outLength = 0;
	}

	SendMessageA(hwndOutput, EM_SETSEL, outLength, outLength);

	// insert the text at the new caret position
	SendMessageA(hwndOutput, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(newText));

	// restore the previous selection only if it's still valid
	if (oldOutLength <= 20000) SendMessageA(hwndOutput, EM_SETSEL, StartPos, EndPos);
}

#pragma region UGLY_SHIT
extern "C" __declspec(dllexport) void Com_Printf(int channel, const char* message, ...)
{
	char buffer[65536] = { 0 };

	va_list ap;
	va_start(ap, message);
	_vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, message, ap);
	buffer[sizeof(buffer) - 1] = '\0';
	va_end(ap);

	switch (channel)
	{
	case 1:
		WinConsole::Print(buffer);
		break;

	default:
		DBGPrint("%s", buffer);
		break;
	}
	
}
#pragma endregion