/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Sokie
	Started: 2015-05-25
	Notes:
		A win32 console.
*/
#include "..\..\..\resource.h"

class WinConsole
{
	static bool LogToFile;
	static std::string Filename;

	//static HWND aDiag;
	static WNDPROC oldEditProc;

	static DWORD _stdcall ConsoleThread(void  *lparam);
	static DWORD _stdcall StdOutThread(void  *lparam);

	static void Print(const char* message);

	static void(*PrintCallback)(const char*);

	static void OnDlgClose(HWND hWnd);
	static BOOL OnDlgInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	static void OnDlgCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	static void AppendText(const HWND &hwnd, TCHAR *newText);
	static INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK subEditProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	static bool InitializeConsole(const char *Logfilename = nullptr);

	static void EnqueueMessage(char *Source, char *Message, char *Data, bool InstantPrint = false);
	static void EnqueueFragmented(uint32_t FragmentCount, char *Source, char **Message, char **Data, bool InstantPrint = false);

	static void RedirectOutput(void(*callback)(const char*));

};
