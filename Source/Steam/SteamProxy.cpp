/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)momo5502
	Started: 2015-01-10
	Notes:
		Steam communication class.
*/

#include "..\StdInclude.h"

std::mutex SteamProxy::CallMutex;
std::unordered_map<int32, void*> SteamProxy::Callbacks;
std::vector<SteamProxy::CallContainer> SteamProxy::Calls;

char SteamProxy::SteamPath[MAX_PATH] = { 0 };
char SteamProxy::AppName[MAX_PATH * 2] = { 0 };

HMODULE SteamProxy::SteamClient = 0;
HMODULE SteamProxy::SteamOverlay = 0;

CreateInterfaceFn SteamProxy::ClientFactory = 0;
SteamBGetCallbackFn SteamProxy::SteamBGetCallback = 0;
SteamFreeLastCallbackFn SteamProxy::SteamFreeLastCallback = 0;
SteamGetAPICallResultFn SteamProxy::SteamGetAPICallResult = 0;
HSteamPipe SteamProxy::Pipe = 0;
HSteamUser SteamProxy::GlobalUser = 0;

IClientEngine*  SteamProxy::ClientEngine  = 0;
IClientUser*    SteamProxy::ClientUser    = 0;
IClientApps*    SteamProxy::ClientApps    = 0;
IClientFriends* SteamProxy::ClientFriends = 0;

ISteamAppList001*               SteamProxy::ISteamAppList             = 0;
ISteamApps007*                  SteamProxy::ISteamApps                = 0;
//ISteamAppTicket001*           SteamProxy::ISteamAppTicket           = 0;
//ISteamBilling002*             SteamProxy::ISteamBilling             = 0;
ISteamClient017*                SteamProxy::ISteamClient              = 0;
//ISteamContentServer002*       SteamProxy::ISteamContentServer       = 0;
ISteamController001*            SteamProxy::ISteamController          = 0;
ISteamFriends015*               SteamProxy::ISteamFriends             = 0;
//ISteamGameCoordinator001*     SteamProxy::ISteamGameCoordinator     = 0;
ISteamGameServer012*            SteamProxy::ISteamGameServer          = 0;
ISteamGameServerStats001*       SteamProxy::ISteamGameServerStats     = 0;
//ISteamGameStats001*           SteamProxy::ISteamGameStats           = 0;
ISteamHTMLSurface002*           SteamProxy::ISteamHTMLSurface         = 0;
ISteamHTTP002*                  SteamProxy::ISteamHTTP                = 0;
//ISteamMasterServerUpdater001* SteamProxy::ISteamMasterServerUpdater = 0;
ISteamMatchmaking009*           SteamProxy::ISteamMatchmaking         = 0;
ISteamMatchmakingServers002*    SteamProxy::ISteamMatchmakingServers  = 0;
ISteamMusic001*                 SteamProxy::ISteamMusic               = 0;
ISteamNetworking005*            SteamProxy::ISteamNetworking          = 0;
//ISteamOAuth001*               SteamProxy::ISteamOAuth               = 0;
ISteamRemoteStorage012*         SteamProxy::ISteamRemoteStorage       = 0;
ISteamScreenshots002*           SteamProxy::ISteamScreenshots         = 0;
//ISteamStreamLauncher001*      SteamProxy::ISteamStreamLauncher      = 0;
ISteamUGC002*                   SteamProxy::ISteamUGC                 = 0;
ISteamUnifiedMessages001*       SteamProxy::ISteamUnifiedMessages     = 0;
ISteamUser017*                  SteamProxy::ISteamUser                = 0;
ISteamUserStats011*             SteamProxy::ISteamUserStats           = 0;
ISteamUtils007*                 SteamProxy::ISteamUtils               = 0;

bool SteamProxy::Inititalize()
{
	SteamProxy::GenerateID();

	SteamProxy::LoadOverlay();

	if (SteamProxy::CreateInterfaces())
	{
		SteamProxy::StartGame();

#ifdef NO_PIRACY
		if (SteamProxy::DoUserChecks()) {
#endif

			DBGPrint("SteamProxy: Initialization succeeded");
			return true;

#ifdef NO_PIRACY
		}
#endif
	}

	ERRPrint("SteamProxy: Initialization failed");
	return false;
}

void SteamProxy::GenerateID()
{
	DATA_BLOB DataIn;
	DATA_BLOB DataOut;
	unsigned int hash, i;

	DataIn.pbData = (BYTE *)"AAAAAAAAAA";
	DataIn.cbData = 10;
	CryptProtectData(&DataIn, NULL, NULL, NULL, NULL, CRYPTPROTECT_LOCAL_MACHINE, &DataOut);

	// gives us 230 bytes but apparently only the first 52 or so are deterministic
	for (hash = i = 0; i < 52; ++i)
	{
		hash += ((char*)DataOut.pbData)[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	Global::Steam_UserID = CSteamID(hash, k_unSteamUserWebInstance, k_EUniverseInternal, k_EAccountTypeIndividual).ConvertToUint64();
}

void SteamProxy::SetSteamDirectory()
{
	HKEY hRegKey;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, STEAM_REGISTRY_PATH, 0, KEY_QUERY_VALUE, &hRegKey) == ERROR_SUCCESS)
	{
		DWORD dwLength = sizeof(SteamProxy::SteamPath);
		RegQueryValueExA(hRegKey, "InstallPath", NULL, NULL, (BYTE*)SteamProxy::SteamPath, &dwLength);
		RegCloseKey(hRegKey);

		SetDllDirectory(SteamProxy::SteamPath);
	}
}

void SteamProxy::LoadOverlay()
{
	if (!*SteamProxy::SteamPath) SteamProxy::SetSteamDirectory();

	SteamProxy::SteamOverlay = GetModuleHandleA(GAMEOVERLAY_LIB);

	if (!SteamProxy::SteamOverlay)
	{
		SteamProxy::SteamOverlay = LoadLibraryA(hString::va("%s\\%s", SteamProxy::SteamPath, GAMEOVERLAY_LIB));
	}
}

bool SteamProxy::CreateClient()
{
	SteamProxy::SteamClient = GetModuleHandleA(STEAMCLIENT_LIB);
	if (!SteamProxy::SteamClient) SteamProxy::SteamClient = LoadLibraryA(hString::va("%s\\%s", SteamProxy::SteamPath, STEAMCLIENT_LIB));
	STEAMPROXY_ASSERT(SteamClient)

	SteamProxy::ClientFactory = (CreateInterfaceFn)GetProcAddress(SteamProxy::SteamClient, "CreateInterface");
	STEAMPROXY_ASSERT(ClientFactory)

	SteamProxy::SteamBGetCallback = (SteamBGetCallbackFn)GetProcAddress(SteamProxy::SteamClient, "Steam_BGetCallback");
	STEAMPROXY_ASSERT(SteamBGetCallback)

	SteamProxy::SteamFreeLastCallback = (SteamFreeLastCallbackFn)GetProcAddress(SteamProxy::SteamClient, "Steam_FreeLastCallback");
	STEAMPROXY_ASSERT(SteamFreeLastCallback)

	SteamProxy::SteamGetAPICallResult = (SteamGetAPICallResultFn)GetProcAddress(SteamProxy::SteamClient, "Steam_GetAPICallResult");
	STEAMPROXY_ASSERT(SteamGetAPICallResult)

	SteamProxy::ClientEngine = (IClientEngine*)SteamProxy::ClientFactory(CLIENTENGINE_INTERFACE_VERSION, NULL);
	STEAMPROXY_ASSERT(ClientEngine)

	SteamProxy::ISteamClient = (ISteamClient017*)SteamProxy::ClientFactory(STEAMCLIENT_INTERFACE_VERSION_017, NULL);
	STEAMPROXY_ASSERT(ISteamClient)

	SteamProxy::Pipe = SteamProxy::ISteamClient->CreateSteamPipe();
	STEAMPROXY_ASSERT(Pipe)

	SteamProxy::GlobalUser = SteamProxy::ISteamClient->ConnectToGlobalUser(SteamProxy::Pipe);
	STEAMPROXY_ASSERT(GlobalUser)

	SteamProxy::ClientUser = SteamProxy::ClientEngine->GetIClientUser(SteamProxy::GlobalUser, SteamProxy::Pipe, CLIENTUSER_INTERFACE_VERSION);
	STEAMPROXY_ASSERT(ClientUser)

	SteamProxy::ClientApps = SteamProxy::ClientEngine->GetIClientApps(SteamProxy::GlobalUser, SteamProxy::Pipe, CLIENTAPPS_INTERFACE_VERSION);
	STEAMPROXY_ASSERT(ClientApps)

	SteamProxy::ClientFriends = SteamProxy::ClientEngine->GetIClientFriends(SteamProxy::GlobalUser, SteamProxy::Pipe, CLIENTFRIENDS_INTERFACE_VERSION);
	STEAMPROXY_ASSERT(ClientFriends)

	return true;
}

bool SteamProxy::CreateInterfaces()
{
	if (!SteamProxy::CreateClient()) return false;

	STEAMPROXY_CREATEINTERFACE(ISteamAppList,            ISteamAppList001,            GetISteamAppList,            STEAMAPPLIST_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamApps,               ISteamApps007,               GetISteamApps,               STEAMAPPS_INTERFACE_VERSION_007)
	STEAMPROXY_CREATEINTERFACE(ISteamController,         ISteamController001,         GetISteamController,         STEAMCONTROLLER_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamFriends,            ISteamFriends015,            GetISteamFriends,            STEAMFRIENDS_INTERFACE_VERSION_015)
	STEAMPROXY_CREATEINTERFACE(ISteamGameServer,         ISteamGameServer012,         GetISteamGameServer,         STEAMGAMESERVER_INTERFACE_VERSION_012)
	STEAMPROXY_CREATEINTERFACE(ISteamGameServerStats,    ISteamGameServerStats001,    GetISteamGameServerStats,    STEAMGAMESERVERSTATS_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamHTMLSurface,        ISteamHTMLSurface002,        GetISteamHTMLSurface,        STEAMHTMLSURFACE_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamHTTP,               ISteamHTTP002,               GetISteamHTTP,               STEAMHTTP_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamMatchmaking,        ISteamMatchmaking009,        GetISteamMatchmaking,        STEAMMATCHMAKING_INTERFACE_VERSION_009)
	STEAMPROXY_CREATEINTERFACE(ISteamMatchmakingServers, ISteamMatchmakingServers002, GetISteamMatchmakingServers, STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamMusic,              ISteamMusic001,              GetISteamMusic,              STEAMMUSIC_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamNetworking,         ISteamNetworking005,         GetISteamNetworking,         STEAMNETWORKING_INTERFACE_VERSION_005)
	STEAMPROXY_CREATEINTERFACE(ISteamRemoteStorage,      ISteamRemoteStorage012,      GetISteamRemoteStorage,      STEAMREMOTESTORAGE_INTERFACE_VERSION_012)
	STEAMPROXY_CREATEINTERFACE(ISteamScreenshots,        ISteamScreenshots002,        GetISteamScreenshots,        STEAMSCREENSHOTS_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamUGC,                ISteamUGC002,                GetISteamUGC,                STEAMUGC_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamUnifiedMessages,    ISteamUnifiedMessages001,    GetISteamUnifiedMessages,    STEAMUNIFIEDMESSAGES_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamUser,               ISteamUser017,               GetISteamUser,               STEAMUSER_INTERFACE_VERSION_017)
	STEAMPROXY_CREATEINTERFACE(ISteamUserStats,          ISteamUserStats011,          GetISteamUserStats,          STEAMUSERSTATS_INTERFACE_VERSION_011)
	STEAMPROXY_CREATEINTERFACE_NO_USER(ISteamUtils,      ISteamUtils007,              GetISteamUtils,              STEAMUTILS_INTERFACE_VERSION_007)
	return true;
}

bool SteamProxy::GetAppName(uint32_t appID, char* buffer, size_t bufferLen)
{
	if (!SteamProxy::ClientApps)
	{
		return false;
	}

	// Seems to read from app manifests, so you have to own the game!
	SteamProxy::ClientApps->GetAppData(appID, "name", buffer, bufferLen);

	return true;
}

void SteamProxy::SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
{
	if (SteamProxy::SteamOverlay)
	{
		FARPROC _SetNotificationPosition = GetProcAddress(SteamProxy::SteamOverlay, "SetNotificationPosition");

		if (_SetNotificationPosition)
		{
			((void(*)(ENotificationPosition))_SetNotificationPosition)(eNotificationPosition);
		}
	}
	else if (SteamProxy::ISteamUtils)
	{
		SteamProxy::ISteamUtils->SetOverlayNotificationPosition(eNotificationPosition);
	}
}

bool SteamProxy::IsOverlayEnabled()
{
	if (SteamProxy::SteamOverlay)
	{
		FARPROC _IsOverlayEnabled = GetProcAddress(SteamProxy::SteamOverlay, "IsOverlayEnabled");

		if (_IsOverlayEnabled)
		{
			return ((bool(*)())_IsOverlayEnabled)();
		}
	}
	else if (SteamProxy::ISteamUtils)
	{
		return SteamProxy::ISteamUtils->IsOverlayEnabled();
	}

	return false;
}

bool SteamProxy::BOverlayNeedsPresent()
{
	if (SteamProxy::SteamOverlay)
	{
		FARPROC _BOverlayNeedsPresent = GetProcAddress(SteamProxy::SteamOverlay, "BOverlayNeedsPresent");

		if (_BOverlayNeedsPresent)
		{
			return ((bool(*)())_BOverlayNeedsPresent)();
		}
	}
	else if (SteamProxy::ISteamUtils)
	{
		return SteamProxy::ISteamUtils->BOverlayNeedsPresent();
	}

	return false;
}

void SteamProxy::StartGame()
{
	SetEnvironmentVariableA("SteamAppId", hString::va("%lu", Global::Steam_AppID));
	SetEnvironmentVariableA("SteamGameId", hString::va("%llu", Global::Steam_AppID & 0xFFFFFF));

	if (!FileSystem::FileExists("steam_appid.txt"))
	{
		FileSystem::WriteFile("steam_appid.txt", ByteString((BYTE*)hString::va("%lu", Global::Steam_AppID)), false);
	}

	SteamProxy::GetAppName(Global::Steam_AppID, SteamProxy::AppName, sizeof(SteamProxy::AppName));

	// Use real XUID if possible.
	Global::Steam_UserID = SteamProxy::GetUserID().ConvertToUint64();

	// Causes Steam to crash. Idk why xD
#ifndef _WIN64
	SteamProxy::StartMod();
#endif
}

void SteamProxy::StartMod()
{
	if (!SteamProxy::ClientUser)
	{
		return;
	}

	CGameID gameID(0xF159010201000000 | Global::Steam_AppID);

	char ourPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(GetModuleHandle(NULL), ourPath, sizeof(ourPath));

	char ourDirectory[MAX_PATH] = { 0 };
	GetCurrentDirectoryA(sizeof(ourDirectory), ourDirectory);

	char blob[1] = { 0 };
	const char* modTitle = hString::va(MOD_TITLE ": %s", SteamProxy::AppName);
	SteamProxy::ClientUser->SpawnProcess(blob, 0, ourPath, hString::va("\"%s\" -parentProc %d", ourPath, GetCurrentProcessId()), 0, ourDirectory, gameID, Global::Steam_AppID, modTitle, 0);
}

void SteamProxy::RunClient()
{
	char* command = "-parentProc ";
	char* parentProc = strstr(GetCommandLineA(), command);

	if (parentProc)
	{
		parentProc += strlen(command);
		int pid = atoi(parentProc);

		HANDLE processHandle = OpenProcess(SYNCHRONIZE, FALSE, pid);

		if (processHandle != INVALID_HANDLE_VALUE)
		{
			WaitForSingleObject(processHandle, INFINITE);
			CloseHandle(processHandle);
		}

		exit(0);
	}
}

void SteamProxy::RegisterCall(int32 callId, uint32 size, SteamAPICall_t call)
{
	SteamProxy::CallContainer contianer;

	contianer.call = call;
	contianer.dataSize = size;
	contianer.callId = callId;
	contianer.handled = false;

	SteamProxy::CallMutex.lock();
	SteamProxy::Calls.push_back(contianer);
	SteamProxy::CallMutex.unlock();
}

void SteamProxy::UnregisterCalls()
{
	SteamProxy::CallMutex.lock();

	std::vector<SteamProxy::CallContainer> tempVector;

	for (auto &call : SteamProxy::Calls)
	{
		if (!call.handled)
		{
			tempVector.push_back(call);
		}
	}

	SteamProxy::Calls = tempVector;

	SteamProxy::CallMutex.unlock();
}

void SteamProxy::RegisterCallback(int32 callId, void* callback)
{
	SteamProxy::Callbacks[callId] = callback;
}

void SteamProxy::UnregisterCallback(int32 callId)
{
	SteamProxy::Callbacks.erase(callId);
}

void SteamProxy::RunFrame()
{
	if (SteamProxy::ISteamUtils)
	{
		SteamProxy::ISteamUtils->RunFrame();
	}

	CallbackMsg_t message;
	while (SteamProxy::SteamBGetCallback(SteamProxy::Pipe, &message))
	{
		DBGPrint("SteamProxy: Callback dispatched (%d): %s", message.m_iCallback, SteamCallback::GetCallbackName(message.m_iCallback));
		SteamProxy::RunCallback(message.m_iCallback, message.m_pubParam);
		SteamCallback::RunCallback(message.m_iCallback, message.m_pubParam); // Dispatch to our isolated callback system
		SteamProxy::SteamFreeLastCallback(SteamProxy::Pipe);
	}

	if (SteamProxy::ISteamUtils)
	{
		SteamProxy::CallMutex.lock();

		for (auto &call : SteamProxy::Calls)
		{
			bool failed = false;
			if (SteamProxy::ISteamUtils->IsAPICallCompleted(call.call, &failed))
			{
				DBGPrint("SteamProxy: Handling call (%d): %s", call.callId, SteamCallback::GetCallbackName(call.callId));
				call.handled = true;

				if (failed)
				{
					auto error = SteamProxy::ISteamUtils->GetAPICallFailureReason(call.call);
					DBGPrint("SteamProxy: API call failed: %X Handle: %llX", error, call.call);
					continue;
				}

				char* buffer = new char[call.dataSize];
				SteamProxy::ISteamUtils->GetAPICallResult(call.call, buffer, call.dataSize, call.callId, &failed);

				if (failed)
				{
					auto error = SteamProxy::ISteamUtils->GetAPICallFailureReason(call.call);
					DBGPrint("SteamProxy: GetAPICallResult failed: %X Handle: %llX", error, call.call);
					continue;
				}

				SteamProxy::RunCallback(call.callId, buffer);
				delete[] buffer;
			}
		}

		SteamProxy::CallMutex.unlock();
	}

	SteamProxy::UnregisterCalls();
}

void SteamProxy::RunCallback(int32 callId, void* data)
{
	if (SteamProxy::Callbacks.find(callId) != SteamProxy::Callbacks.end())
	{
		((Callback)SteamProxy::Callbacks[callId])(data);
	}
}

bool SteamProxy::DoUserChecks()
{
	const char* username = SteamProxy::GetUsername();
	if (username) DBGPrint("SteamProxy: Username: %s", username);

	DBGPrint("SteamProxy: SteamID: %16llX", SteamProxy::GetUserID().ConvertToUint64());

	if (!SteamProxy::IsSubscribedApp())
	{
		MessageBox(0, "You do not own this game!", "Error", MB_ICONERROR);
		return false;
	}

	if (SteamProxy::IsVACBanned())
	{
		MessageBox(0, hString::va("You are VAC banned from '%s'", SteamProxy::AppName), "Error", MB_ICONERROR);
		return false;
	}

	return true;
}

bool SteamProxy::IsSubscribedApp()
{
	return SteamProxy::IsSubscribedApp(Global::Steam_AppID);
}

bool SteamProxy::IsSubscribedApp(uint32_t appID)
{
	if (SteamProxy::ISteamApps)
	{
		return SteamProxy::ISteamApps->BIsSubscribedApp(appID);
	}

	return false;
}

bool SteamProxy::IsVACBanned()
{
	return false; // Don't prevent VAC banned players from playing. Only log their status for the anticheat.
	return SteamProxy::IsVACBanned(Global::Steam_AppID);
}

bool SteamProxy::IsVACBanned(uint32_t appID)
{
	if (SteamProxy::ClientUser)
	{
		return SteamProxy::ClientUser->IsVACBanned(appID);
	}

	return false;
}

const char* SteamProxy::GetUsername()
{
	const char* username = "";

	if (SteamProxy::ISteamFriends)
	{
		username = SteamProxy::ISteamFriends->GetPersonaName();
	}

	return username;
}

CSteamID SteamProxy::GetUserID()
{
	CSteamID id(Global::Steam_UserID);

	if (SteamProxy::ISteamUser)
	{
		id = SteamProxy::ISteamUser->GetSteamID();
		Global::Steam_UserID = id.ConvertToUint64();
	}

	return id;
}

uint32_t SteamProxy::GetDLCCount()
{
	if (SteamProxy::ISteamApps)
	{
		return SteamProxy::ISteamApps->GetDLCCount();
	}

	return 0;
}

bool SteamProxy::IsDlcInstalled(uint32_t appID)
{
	bool isInstalled = SteamProxy::IsSubscribedApp(appID);

	if (SteamProxy::ISteamApps)
	{
		isInstalled = isInstalled || SteamProxy::ISteamApps->BIsDlcInstalled(appID);
	}

	return isInstalled;
}