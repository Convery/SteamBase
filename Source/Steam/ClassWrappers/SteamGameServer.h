/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
*/

#pragma once

#include "..\..\StdInclude.h"

#pragma region SteamGameServer001

#pragma endregion

#pragma region SteamGameServer002

#pragma endregion

#pragma region SteamGameServer003

#pragma endregion

#pragma region SteamGameServer004

#pragma endregion

#pragma region SteamGameServer005

#pragma endregion

#pragma region SteamGameServer006

#pragma endregion

#pragma region SteamGameServer007

#pragma endregion

#pragma region SteamGameServer008

#pragma endregion

#pragma region SteamGameServer009

#pragma endregion

#pragma region SteamGameServer010

#pragma endregion

#pragma region SteamGameServer011

class SteamGameServer011 : public ISteamGameServer011
{
public:
	bool InitGameServer(uint32 unGameIP, uint16 unGamePort, uint16 usQueryPort, uint32 unServerFlags, AppId_t nAppID, const char *pchVersion);
	void SetProduct(const char *pchProductName);
	void SetGameDescription(const char *pchGameDescription);
	void SetModDir(const char *pchModDir);
	void SetDedicatedServer(bool bDedicatedServer);

	void LogOn(const char *pszAccountName, const char *pszPassword);
	void LogOnAnonymous();
	void LogOff();
	bool BLoggedOn();
	bool BSecure();
	CSteamID GetSteamID();
	bool WasRestartRequested();

	void SetMaxPlayerCount(int cPlayersMax);
	void SetBotPlayerCount(int cBotPlayers);
	void SetServerName(const char *pszServerName);
	void SetMapName(const char *pszMapName);
	void SetPasswordProtected(bool bPasswordProtected);
	void SetSpectatorPort(uint16 unSpectatorPort);
	void SetSpectatorServerName(const char *pszSpectatorServerName);
	void ClearAllKeyValues();
	void SetKeyValue(const char *pKey, const char *pValue);
	void SetGameTags(const char *pchGameTags);
	void SetGameData(const char *pchGameData);
	void SetRegion(const char *pchRegionName);

	int SendUserConnectAndAuthenticate(uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser);
	CSteamID CreateUnauthenticatedUserConnection();
	void SendUserDisconnect(CSteamID steamIDUser);
	bool BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore);

	HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket);
	EBeginAuthSessionResult BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID);
	void EndAuthSession(CSteamID steamID);
	void CancelAuthTicket(HAuthTicket hAuthTicket);
	EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID);
	bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup);

	void GetGameplayStats();
	SteamAPICall_t GetServerReputation();
	uint32 GetPublicIP();
	bool HandleIncomingPacket(const void *pData, int cbData, uint32 srcIP, uint16 srcPort);
	int GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort);
	void EnableHeartbeats(bool bActive);
	void SetHeartbeatInterval(int iHeartbeatInterval);
	void ForceHeartbeat();
	SteamAPICall_t AssociateWithClan(CSteamID clanID);
	SteamAPICall_t ComputeNewPlayerCompatibility(CSteamID steamID);
};

#pragma endregion