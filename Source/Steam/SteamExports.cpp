/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-25
	Notes:
		Exports basic steam_api functions.
*/

#include "..\STDInclude.h"

#pragma region Interfaces
static SteamInterface_t _SteamAppList;
static SteamInterface_t _SteamApps;
static SteamInterface_t _SteamClient;
static SteamInterface_t _SteamContentServer;
static SteamInterface_t _SteamController;
static SteamInterface_t _SteamFriends;
static SteamInterface_t _SteamGameServer;
static SteamInterface_t _SteamGameServerStats;
static SteamInterface_t _SteamHTTP;
static SteamInterface_t _SteamMasterServerUpdater;
static SteamInterface_t _SteamMatchMaking;
static SteamInterface_t _SteamMatchMakingServers;
static SteamInterface_t _SteamMusic;
static SteamInterface_t _SteamMusicRemote;
static SteamInterface_t _SteamNetworking;
static SteamInterface_t _SteamRemoteStorage;
static SteamInterface_t _SteamScreenshots;
static SteamInterface_t _SteamUGC;
static SteamInterface_t _SteamUnifiedMessages;
static SteamInterface_t _SteamUser;
static SteamInterface_t _SteamUserStats;
static SteamInterface_t _SteamUtils;
#pragma endregion

#define PARSEINTERFACE(obj, var, key, default)                       \
{                                                                    \
	auto value = obj[key];                                           \
	int val = (value.type() == Json::nullValue ? 1 : value.asInt()); \
	var = (SteamInterface_t)(default - 1 + val);                     \
}

#ifndef _WIN64
#define INTERFACE_VERSION_FILE "steam_api.json"
#else
#define INTERFACE_VERSION_FILE "steam_api64.json"
#endif

static bool ReadInterfaces()
{
	ByteString buffer;
	if (FileSystem::FileExists(INTERFACE_VERSION_FILE))
	{
		FileSystem::ReadFile(INTERFACE_VERSION_FILE, buffer);
	}
	else
	{
		std::string data = WebIO("Redacted").Get(hString::va("https://momo5502.com/SteamAPI/?app=%d", Global::Steam_AppID));

		buffer.append(data.begin(), data.end());
		FileSystem::WriteFile(INTERFACE_VERSION_FILE, buffer, false);
	}

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(std::string(buffer.begin(), buffer.end()), root) && root.type() == Json::objectValue)
	{
		PARSEINTERFACE(root, _SteamApps,                "Apps",                INTERFACE_STEAMAPPS001)
		PARSEINTERFACE(root, _SteamClient,              "Client",              INTERFACE_STEAMCLIENT001)
		PARSEINTERFACE(root, _SteamContentServer,       "ContentServer",       INTERFACE_STEAMCONTENTSERVER001)
//		PARSEINTERFACE(root, _SteamController,          "Controller",          INTERFACE_STEAMCONTROLLER001)
		PARSEINTERFACE(root, _SteamFriends,             "Friends",             INTERFACE_STEAMFRIENDS001)
		PARSEINTERFACE(root, _SteamGameServer,          "GameServer",          INTERFACE_STEAMGAMESERVER001)
		PARSEINTERFACE(root, _SteamGameServerStats,     "GameServerStats",     INTERFACE_STEAMGAMESERVER001)
		PARSEINTERFACE(root, _SteamHTTP,                "HTTP",                INTERFACE_STEAMHTTP001)
		PARSEINTERFACE(root, _SteamMasterServerUpdater, "MasterServerUpdater", INTERFACE_STEAMMASTERUPDATER001)
		PARSEINTERFACE(root, _SteamMatchMaking,         "MatchMaking",         INTERFACE_STEAMMATCHMAKING001)
		PARSEINTERFACE(root, _SteamMatchMakingServers,  "MatchMakingServers",  INTERFACE_STEAMMATCHMAKINGSERVERS001)
		PARSEINTERFACE(root, _SteamMusic,               "Music",               INTERFACE_STEAMMUSIC001)
//		PARSEINTERFACE(root, _SteamMusicRemote,         "MusicRemote",         INTERFACE_STEAMMUSICREMOTE001)
		PARSEINTERFACE(root, _SteamNetworking,          "Networking",          INTERFACE_STEAMNETWORKING001)
		PARSEINTERFACE(root, _SteamRemoteStorage,       "RemoteStorage",       INTERFACE_STEAMREMOTESTORAGE001)
		PARSEINTERFACE(root, _SteamScreenshots,         "Screenshots",         INTERFACE_STEAMSCREENSHOTS001)
		PARSEINTERFACE(root, _SteamUnifiedMessages,     "UnifiedMessages",     INTERFACE_STEAMUNIFIEDMESSAGES001)
		PARSEINTERFACE(root, _SteamUser,                "User",                INTERFACE_STEAMUSER001)
		PARSEINTERFACE(root, _SteamUserStats,           "UserStats",           INTERFACE_STEAMUSERSTATS001)
		PARSEINTERFACE(root, _SteamUtils,               "Utils",               INTERFACE_STEAMUTILS001)

		return true;
	}

	MessageBox(0, "Failed to parse interfaces from 'steam_api.json", "Error", MB_ICONERROR);
	return false;
}

#define API __declspec(dllexport)
extern "C"
{
	API void *__cdecl SteamApps()
	{
		return InterfaceManager::GetInterface(_SteamApps);
	}
	API void *__cdecl SteamFriends()
	{
		return InterfaceManager::GetInterface(_SteamFriends);
	}
	API void *__cdecl SteamGameServer()
	{
		return InterfaceManager::GetInterface(_SteamGameServer);
	}
	API void *__cdecl SteamNetworking()
	{
		return InterfaceManager::GetInterface(_SteamNetworking);
	}
	API void *__cdecl SteamUser()
	{
		return InterfaceManager::GetInterface(_SteamUser);
	}
	API void *__cdecl SteamUserStats()
	{
		return InterfaceManager::GetInterface(_SteamUserStats);
	}
	API void *__cdecl SteamUtils()
	{
		return InterfaceManager::GetInterface(_SteamUtils);
	}
	API void *__cdecl SteamMatchmaking()
	{
		return InterfaceManager::GetInterface(_SteamMatchMaking);
	}
	API void *__cdecl SteamRemoteStorage()
	{
		return InterfaceManager::GetInterface(_SteamRemoteStorage);
	}
	API void *__cdecl SteamMasterServerUpdater()
	{
		return InterfaceManager::GetInterface(_SteamMasterServerUpdater);
	}
	API void *__cdecl SteamMatchmakingServers()
	{
		return InterfaceManager::GetInterface(_SteamMatchMakingServers);
	}

	API const char *__cdecl SteamAPI_GetSteamInstallPath()
	{
		PrintCurrentFunction();
		return "";
	}
	API bool __cdecl SteamAPI_RestartAppIfNecessary(int appid)
	{
		DBGPrint("%s: Current AppId: %d", __FUNCTION__, appid);

		Global::Steam_AppID = appid;

		return false;
	}
	API bool __cdecl SteamAPI_Init()
	{
		PrintCurrentFunction();

		// Game didn't call SteamAPI_RestartAppIfNecessary
		// Try to read the appid from steam_appid.txt
		// If the game doesn't create it, then we're fucked.
		if (!Global::Steam_AppID)
		{
			ByteString buffer;
			if (FileSystem::FileExists("steam_appid.txt") && FileSystem::ReadFile("steam_appid.txt", buffer))
			{
				Global::Steam_AppID = atoi((char*)buffer.c_str());
			}
			else
			{
				// TODO: Find another identification method. Binary hash checks or so? 
				MessageBox(0, "Unable to determine current AppID!", "Error", MB_ICONERROR);
				return false;
			}
		}

		ReadInterfaces();

		PluginManager::PostInit();

		return SteamProxy::Inititalize();
	}
	API void __cdecl SteamAPI_RunCallbacks()
	{
		SteamCallback::RunCallbacks();
	}
	API void __cdecl SteamAPI_RegisterCallResult(void *Result, uint64_t APICall)
	{
		SteamCallback::RegisterCallResult(APICall, static_cast<CallbackBase *>(Result));
	}
	API void __cdecl SteamAPI_RegisterCallback(void *Callback, uint32_t APICall)
	{
		DBGPrint("Registering callback <%s>", SteamCallback::GetCallbackName(APICall));
		SteamCallback::RegisterCallback(static_cast<CallbackBase *>(Callback), APICall);
	}
	API void __cdecl SteamAPI_UnregisterCallResult(void *Result, uint64_t APICall)
	{
		SteamCallback::UnregisterCallResult(APICall, static_cast<CallbackBase *>(Result));
	}
	API void __cdecl SteamAPI_UnregisterCallback(void *Callback, uint32_t APICall)
	{
		DBGPrint("Unregistering callback <%s>", SteamCallback::GetCallbackName(APICall));
		SteamCallback::UnregisterCallback(static_cast<CallbackBase *>(Callback), APICall);
	}
	API void __cdecl SteamAPI_Shutdown()
	{
		PrintCurrentFunction();
	}

	API bool __cdecl SteamGameServer_Init(uint32_t unIP, uint16_t usPort, uint16_t usGamePort, uint32_t Unk, int32_t eServerMode, const char *pchVersionString)
	{
		in_addr ip_addr;
		ip_addr.s_addr = unIP;

		PrintCurrentFunction();
		DBGPrint(">> Bind to IP: %s", inet_ntoa(ip_addr));
		DBGPrint(">> Query Port: %i", usPort);
		DBGPrint(">> Game Port: %i", usGamePort);
		// IW4 compat.
		//DBG(">> ServerMode: %i", eServerMode);
		//DBG(">> ServerVersion: %s", pchVersionString);

		// I think the best way would be to have a custom class for servers.
		// Then the different versions can call that as needed.
		//return ((SteamGameServer011 *)InterfaceManager::GetInterface(_SteamGameServer))->InitGameServer(unIP, usPort, usGamePort, Unk, eServerMode, pchVersionString);
		return true;
	}
	API void __cdecl SteamGameServer_RunCallbacks()
	{
		SteamCallback::RunCallbacks();
	}
	API void __cdecl SteamGameServer_Shutdown()
	{
		PrintCurrentFunction();
	}
}