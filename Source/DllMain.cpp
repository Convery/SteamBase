/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		We unprotect the whole module so the plugins can edit it.
		We hook the entry point to call our function once everything is loaded.
		Then we initialize everything and jump to the program's entrypoint.
*/

#include "STDInclude.h"

static BYTE OriginalCode[20];
static PBYTE OriginalEP = 0;
static void InitialCall();

// Unprotect the PE image.
DWORD OriginalProtection = 0;
static void UnprotectModule(HMODULE Module)
{
	PIMAGE_DOS_HEADER DOSHeader = (PIMAGE_DOS_HEADER)Module;
	PIMAGE_NT_HEADERS NTHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)Module + DOSHeader->e_lfanew);
	SIZE_T Size = NTHeader->OptionalHeader.SizeOfImage;

	VirtualProtect((void *)Module, Size, PAGE_EXECUTE_READWRITE, &OriginalProtection);
}

static PBYTE GetEntryPoint(HMODULE Module)
{
	PIMAGE_DOS_HEADER DOSHeader = (PIMAGE_DOS_HEADER)Module;
	PIMAGE_NT_HEADERS NTHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)Module + DOSHeader->e_lfanew);
	return (PBYTE)((DWORD_PTR)Module + NTHeader->OptionalHeader.AddressOfEntryPoint);
}

// Find the EP, set access and replace it.
void SafeInit()
{
	HMODULE Module = GetModuleHandle(NULL);

	if (Module)
	{
		UnprotectModule(Module);

		// Backup.
		PBYTE EP = GetEntryPoint(Module);
		OriginalEP = EP;
		memcpy(OriginalCode, EP, 20);
		memset(EP, 0x90, 20);

		// Patch the original entrypoint.
#ifdef _WIN64
		EP[0] = 0x48; // mov
		EP[1] = 0xB8; // rax
		*(uint64_t *)&EP[2] = (uint64_t)InitialCall;
		EP[10] = 0xFF; // jmp
		EP[11] = 0xE0; // rax
#else
		uint32_t NewEP = (uint32_t)InitialCall - ((uint32_t)EP + 5);
		EP[0] = 0xE9; // jmp
		*(uint32_t *)&EP[1] = NewEP;
#endif
	}
}

// Entrypoint.
BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Patch the entrypoint.
		SafeInit();
	}

	return TRUE;
}

// Read our settings from a file.
static void ReadSettings(const char *Filename)
{
	GetPrivateProfileStringA("Steam", "Username", "redacted", Global::Steam_Username, 16, Filename);
	GetPrivateProfileStringA("Steam", "Language", "english", Global::Steam_Language, 16, Filename);
	
	Global::Steam_Offline = GetPrivateProfileIntA("System", "OfflineMode", 1, Filename) == TRUE;
	Global::Steam_Dedicated = GetPrivateProfileIntA("System", "DedicatedMode", 0, Filename) == TRUE;
}

// The replacement for the games EP.
void InitialCall()
{
	// Return to the hosts entrypoint.
	memcpy(OriginalEP, OriginalCode, 20);

	SteamProxy::RunClient();

	// Initialize minidump handler
	DumpHandler::Initialize();

	// Create our logfile.
	WinConsole::InitializeConsole("RedactedBase.log");

	// A simple reminder for the users.
	WinConsole::EnqueueMessage("INFO", (char *)hString::va("SteamBase - %s\n", __DATE__), "", true);
	WinConsole::EnqueueMessage("INFO", "This software was created for modders, by modders.", "", true);
	WinConsole::EnqueueMessage("INFO", "It's currently maintained by redacted.se and should not be redistributed.", "", true);

	// Check that the INI exists.
	if (!FileSystem::FileExists("./Redacted.ini"))
	{
		// Quit
		MessageBoxA(0, "SteamBase needs a Redacted.ini file to function. Please redownload it.", "REDACTED", 0);
		exit(1);
	}
	else
	{
		ReadSettings("./Redacted.ini");
	}

	// Load all the plugins that we can and
	// let them do their code changes.
	PluginManager::Startup();
	PluginManager::PreInit();

	//Networking init stuff
	Network::SocketManager::InitializeManager();
	Nodes::ClientNode::InitializeNode();

	OriginalEP = GetEntryPoint(GetModuleHandle(NULL));

#ifdef _WIN64
	// x64 needs some stack alignment.
	__asm and rsp, 0xFFFFFFFFFFFFFFF0
	__asm push 0xDEADDEADDEADDEAD
#endif
	__asm jmp OriginalEP;
}
