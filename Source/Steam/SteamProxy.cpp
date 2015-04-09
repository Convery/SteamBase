#include "..\StdInclude.h"

char SteamProxy::SteamPath[MAX_PATH] = { 0 };
char SteamProxy::AppName[MAX_PATH * 2] = { 0 };

HMODULE SteamProxy::SteamClient = 0;
HMODULE SteamProxy::SteamOverlay = 0;

CreateInterfaceFn SteamProxy::ClientFactory = 0;
HSteamPipe SteamProxy::Pipe = 0;
HSteamUser SteamProxy::User = 0;

IClientEngine* SteamProxy::ClientEngine = 0;
IClientUser* SteamProxy::ClientUser = 0;

//ISteamAppList001*             SteamProxy::ISteamAppList             = 0;
ISteamApps006*                  SteamProxy::ISteamApps                = 0;
//ISteamAppTicket001*           SteamProxy::ISteamAppTicket           = 0;
//ISteamBilling002*             SteamProxy::ISteamBilling             = 0;
ISteamClient012*                SteamProxy::ISteamClient              = 0;
//ISteamContentServer002*       SteamProxy::ISteamContentServer       = 0;
ISteamController001*            SteamProxy::ISteamController          = 0;
ISteamFriends014*               SteamProxy::ISteamFriends             = 0;
//ISteamGameCoordinator001*     SteamProxy::ISteamGameCoordinator     = 0;
ISteamGameServer012*            SteamProxy::ISteamGameServer          = 0;
ISteamGameServerStats001*       SteamProxy::ISteamGameServerStats     = 0;
//ISteamGameStats001*           SteamProxy::ISteamGameStats           = 0;
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
//ISteamUGC002*                 SteamProxy::ISteamUGC                 = 0;
ISteamUnifiedMessages001*       SteamProxy::ISteamUnifiedMessages     = 0;
ISteamUser017*                  SteamProxy::ISteamUser                = 0;
ISteamUserStats011*             SteamProxy::ISteamUserStats           = 0;
ISteamUtils007*                 SteamProxy::ISteamUtils               = 0;

bool SteamProxy::Inititalize()
{
	SteamProxy::LoadOverlay();
	return SteamProxy::CreateInterfaces();
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
		SteamProxy::SteamOverlay = LoadLibraryA(GAMEOVERLAY_LIB);
	}
}

bool SteamProxy::CreateClient()
{
	SteamProxy::SteamClient = GetModuleHandleA(STEAMCLIENT_LIB);
	if (!SteamProxy::SteamClient) SteamProxy::SteamClient = LoadLibraryA(STEAMCLIENT_LIB);
	STEAMPROXY_ASSERT_VAR(SteamProxy::SteamClient, "SteamClient")

	SteamProxy::ClientFactory = (CreateInterfaceFn)GetProcAddress(SteamProxy::SteamClient, "CreateInterface");
	STEAMPROXY_ASSERT_VAR(SteamProxy::ClientFactory, "ClientFactory")

	SteamProxy::ClientEngine = (IClientEngine*)SteamProxy::ClientFactory(CLIENTENGINE_INTERFACE_VERSION, NULL);
	STEAMPROXY_ASSERT_VAR(SteamProxy::ClientEngine, "ClientEngine")

	SteamProxy::ClientUser = SteamProxy::ClientEngine->GetIClientUser(SteamProxy::User, SteamProxy::Pipe, CLIENTUSER_INTERFACE_VERSION);
	STEAMPROXY_ASSERT_VAR(SteamProxy::ClientUser, "ClientUser")

	SteamProxy::ISteamClient = (ISteamClient012*)SteamProxy::ClientFactory(STEAMCLIENT_INTERFACE_VERSION_012, NULL);
	STEAMPROXY_ASSERT(SteamProxy::ISteamClient)

	SteamProxy::Pipe = SteamProxy::ISteamClient->CreateSteamPipe();
	STEAMPROXY_ASSERT(SteamProxy::Pipe)

	SteamProxy::User = SteamProxy::ISteamClient->ConnectToGlobalUser(SteamProxy::Pipe);
	STEAMPROXY_ASSERT(SteamProxy::User)

	return true;
}

bool SteamProxy::CreateInterfaces()
{
	if (!SteamProxy::CreateClient()) return false;

	STEAMPROXY_CREATEINTERFACE(ISteamApps,               ISteamApps006,               GetISteamApps,               STEAMAPPS_INTERFACE_VERSION_006)
	STEAMPROXY_CREATEINTERFACE(ISteamController,         ISteamController001,         GetISteamController,         STEAMCONTROLLER_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamFriends,            ISteamFriends014,            GetISteamFriends,            STEAMFRIENDS_INTERFACE_VERSION_014)
	STEAMPROXY_CREATEINTERFACE(ISteamGameServer,         ISteamGameServer012,         GetISteamGameServer,         STEAMGAMESERVER_INTERFACE_VERSION_012)
	STEAMPROXY_CREATEINTERFACE(ISteamGameServerStats,    ISteamGameServerStats001,    GetISteamGameServerStats,    STEAMGAMESERVERSTATS_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamHTTP,               ISteamHTTP002,               GetISteamHTTP,               STEAMHTTP_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamMatchmaking,        ISteamMatchmaking009,        GetISteamMatchmaking,        STEAMMATCHMAKING_INTERFACE_VERSION_009)
	STEAMPROXY_CREATEINTERFACE(ISteamMatchmakingServers, ISteamMatchmakingServers002, GetISteamMatchmakingServers, STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamNetworking,         ISteamNetworking005,         GetISteamNetworking,         STEAMNETWORKING_INTERFACE_VERSION_005)
	STEAMPROXY_CREATEINTERFACE(ISteamRemoteStorage,      ISteamRemoteStorage012,      GetISteamRemoteStorage,      STEAMREMOTESTORAGE_INTERFACE_VERSION_012)
	STEAMPROXY_CREATEINTERFACE(ISteamScreenshots,        ISteamScreenshots002,        GetISteamScreenshots,        STEAMSCREENSHOTS_INTERFACE_VERSION_002)
	STEAMPROXY_CREATEINTERFACE(ISteamUnifiedMessages,    ISteamUnifiedMessages001,    GetISteamUnifiedMessages,    STEAMUNIFIEDMESSAGES_INTERFACE_VERSION_001)
	STEAMPROXY_CREATEINTERFACE(ISteamUser,               ISteamUser017,               GetISteamUser,               STEAMUSER_INTERFACE_VERSION_017)
	STEAMPROXY_CREATEINTERFACE(ISteamUserStats,          ISteamUserStats011,          GetISteamUserStats,          STEAMUSERSTATS_INTERFACE_VERSION_011)
	STEAMPROXY_CREATEINTERFACE_NO_USER(ISteamUtils,      ISteamUtils007,              GetISteamUtils,              STEAMUTILS_INTERFACE_VERSION_007)

	return true;
}