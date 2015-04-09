#ifdef _WIN64
#define GAMEOVERLAY_LIB "gameoverlayrenderer64.dll"
#define STEAMCLIENT_LIB "steamclient64.dll"
#define STEAM_REGISTRY_PATH "Software\\Wow6432Node\\Valve\\Steam"
#else
#define GAMEOVERLAY_LIB "gameoverlayrenderer.dll"
#define STEAMCLIENT_LIB "steamclient.dll"
#define STEAM_REGISTRY_PATH "Software\\Valve\\Steam"
#endif

#define STEAMPROXY_ASSERT(x)                            \
if(!SteamProxy::x)                                      \
{                                                       \
	DBGPrint("SteamProxy: " #x " creation failed!");    \
	return false;	                                    \
}                                                       \
else                                                    \
{                                                       \
	DBGPrint("SteamProxy: " #x " creation succeeded!"); \
}

#define STEAMPROXY_CREATEINTERFACE(_var, _type, _function, _version) \
SteamProxy::_var = reinterpret_cast<_type*>(SteamProxy::ISteamClient->_function(SteamProxy::GlobalUser, SteamProxy::Pipe, _version)); \
STEAMPROXY_ASSERT(_var)

#define STEAMPROXY_CREATEINTERFACE_NO_USER(_var, _type, _function, _version) \
SteamProxy::_var = reinterpret_cast<_type*>(SteamProxy::ISteamClient->_function(SteamProxy::Pipe, _version)); \
STEAMPROXY_ASSERT(_var)

class SteamProxy
{
	public:
		static bool Inititalize();

		// SteamInterface objects
//		static ISteamAppList001*             ISteamAppList;
		static ISteamApps006*                ISteamApps;
//		static ISteamAppTicket001*           ISteamAppTicket;
//		static ISteamBilling002*             ISteamBilling;
		static ISteamClient012*              ISteamClient;
//		static ISteamContentServer002*       ISteamContentServer;
		static ISteamController001*          ISteamController;
		static ISteamFriends014*             ISteamFriends;
//		static ISteamGameCoordinator001*     ISteamGameCoordinator;
		static ISteamGameServer012*          ISteamGameServer;
		static ISteamGameServerStats001*     ISteamGameServerStats;
//		static ISteamGameStats001*           ISteamGameStats;
		static ISteamHTTP002*                ISteamHTTP;
//		static ISteamMasterServerUpdater001* ISteamMasterServerUpdater;
		static ISteamMatchmaking009*         ISteamMatchmaking;
		static ISteamMatchmakingServers002*  ISteamMatchmakingServers;
		static ISteamMusic001*               ISteamMusic;
		static ISteamNetworking005*          ISteamNetworking;
//		static ISteamOAuth001*               ISteamOAuth;
		static ISteamRemoteStorage012*       ISteamRemoteStorage;
		static ISteamScreenshots002*         ISteamScreenshots;
//		static ISteamStreamLauncher001*      ISteamStreamLauncher;
//		static ISteamUGC002*                 ISteamUGC;
		static ISteamUnifiedMessages001*     ISteamUnifiedMessages;
		static ISteamUser017*                ISteamUser;
		static ISteamUserStats011*           ISteamUserStats;
		static ISteamUtils007*               ISteamUtils;

	private:
		static char SteamPath[MAX_PATH];
		static char AppName[MAX_PATH * 2];

		static HMODULE SteamClient;
		static HMODULE SteamOverlay;

		static CreateInterfaceFn ClientFactory;
		static HSteamPipe Pipe;
		static HSteamUser GlobalUser;

		static IClientEngine* ClientEngine;
		static IClientUser* ClientUser;

		static void LoadOverlay();
		static void SetSteamDirectory();

		static bool CreateClient();
		static bool CreateInterfaces();
};