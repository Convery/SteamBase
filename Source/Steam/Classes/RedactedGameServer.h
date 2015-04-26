/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		GameServer.
*/

#pragma once

class RedactedGameServer
{
public:
	static bool InitGameServer(uint32 unGameIP, uint16 unGamePort, uint16 usQueryPort, uint32 unServerFlags, AppId_t nAppID, const char *pchVersion);
	static void SetProduct(const char *pchProductName);
	static void SetGameDescription(const char *pchGameDescription);
	static void SetModDir(const char *pchModDir);
	static void SetDedicatedServer(bool bDedicatedServer);

	static void LogOn(const char *pszUnk);
	static void LogOn(const char *pszAccountName, const char *pszPassword);
	static void LogOnAnonymous();
	static void LogOff();
	static bool BLoggedOn();
	static bool BSecure();
	static CSteamID GetSteamID();
	static bool WasRestartRequested();

	static void SetMaxPlayerCount(int cPlayersMax);
	static void SetBotPlayerCount(int cBotPlayers);
	static void SetServerName(const char *pszServerName);
	static void SetMapName(const char *pszMapName);
	static void SetPasswordProtected(bool bPasswordProtected);
	static void SetSpectatorPort(uint16 unSpectatorPort);
	static void SetSpectatorServerName(const char *pszSpectatorServerName);
	static void ClearAllKeyValues();
	static void SetKeyValue(const char *pKey, const char *pValue);
	static void SetGameTags(const char *pchGameTags);
	static void SetGameData(const char *pchGameData);
	static void SetRegion(const char *pchRegionName);

	static int SendUserConnectAndAuthenticate(uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser);
	static CSteamID CreateUnauthenticatedUserConnection();
	static void SendUserDisconnect(CSteamID steamIDUser);
	static bool BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore);

	static HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket);
	static EBeginAuthSessionResult BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID);
	static void EndAuthSession(CSteamID steamID);
	static void CancelAuthTicket(HAuthTicket hAuthTicket);
	static EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID);
	static bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup);

	static void GetGameplayStats();
	static SteamAPICall_t GetServerReputation();
	static uint32 GetPublicIP();
	static bool HandleIncomingPacket(const void *pData, int cbData, uint32 srcIP, uint16 srcPort);
	static int GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort);
	static void EnableHeartbeats(bool bActive);
	static void SetHeartbeatInterval(int iHeartbeatInterval);
	static void ForceHeartbeat();
	static SteamAPICall_t AssociateWithClan(CSteamID clanID);
	static SteamAPICall_t ComputeNewPlayerCompatibility(CSteamID steamID);
};
