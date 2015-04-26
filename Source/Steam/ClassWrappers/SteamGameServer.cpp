/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
*/

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
	
// This is called by SteamGameServer_Init, and you will usually not need to call it directly
bool SteamGameServer011::InitGameServer(uint32 unGameIP, uint16 unGamePort, uint16 usQueryPort, uint32 unServerFlags, AppId_t nAppID, const char *pchVersion)
{
	return RedactedGameServer::InitGameServer(unGameIP, unGamePort, usQueryPort, unServerFlags, nAppID, pchVersion);
}
void SteamGameServer011::SetProduct(const char *pchProductName)
{
	return RedactedGameServer::SetProduct(pchProductName);
}
void SteamGameServer011::SetGameDescription(const char *pchGameDescription)
{
	return RedactedGameServer::SetGameDescription(pchGameDescription);
}
void SteamGameServer011::SetModDir(const char *pchModDir)
{
	return RedactedGameServer::SetModDir(pchModDir);
}
void SteamGameServer011::SetDedicatedServer(bool bDedicatedServer)
{
	return RedactedGameServer::SetDedicatedServer(bDedicatedServer);
}

// Login.
void SteamGameServer011::LogOn(const char *pszAccountName, const char *pszPassword)
{
	return RedactedGameServer::LogOn(pszAccountName, pszPassword);
}
void SteamGameServer011::LogOnAnonymous()
{
	return RedactedGameServer::LogOnAnonymous();
}
void SteamGameServer011::LogOff()
{
	return RedactedGameServer::LogOff();
}

// Status.
bool SteamGameServer011::BLoggedOn()
{
	return RedactedGameServer::BLoggedOn();
}
bool SteamGameServer011::BSecure()
{
	return RedactedGameServer::BSecure();
}
CSteamID SteamGameServer011::GetSteamID()
{
	return RedactedGameServer::GetSteamID();
}
bool SteamGameServer011::WasRestartRequested()
{
	return RedactedGameServer::WasRestartRequested();
}

// Server state.
void SteamGameServer011::SetMaxPlayerCount(int cPlayersMax)
{
	return RedactedGameServer::SetMaxPlayerCount(cPlayersMax);
}
void SteamGameServer011::SetBotPlayerCount(int cBotPlayers)
{
	return RedactedGameServer::SetBotPlayerCount(cBotPlayers);
}
void SteamGameServer011::SetServerName(const char *pszServerName)
{
	return RedactedGameServer::SetServerName(pszServerName);
}
void SteamGameServer011::SetMapName(const char *pszMapName)
{
	return RedactedGameServer::SetMapName(pszMapName);
}
void SteamGameServer011::SetPasswordProtected(bool bPasswordProtected)
{
	return RedactedGameServer::SetPasswordProtected(bPasswordProtected);
}
void SteamGameServer011::SetSpectatorPort(uint16_t unSpectatorPort)
{
	return RedactedGameServer::SetSpectatorPort(unSpectatorPort);
}
void SteamGameServer011::SetSpectatorServerName(const char *pszSpectatorServerName)
{
	return RedactedGameServer::SetSpectatorServerName(pszSpectatorServerName);
}
void SteamGameServer011::ClearAllKeyValues()
{
	return RedactedGameServer::ClearAllKeyValues();
}

// Add/update a key/value pair.
void SteamGameServer011::SetKeyValue(const char *pKey, const char *pValue)
{
	return RedactedGameServer::SetKeyValue(pKey, pValue);
}
void SteamGameServer011::SetGameTags(const char *pchGameTags)
{
	return RedactedGameServer::SetGameTags(pchGameTags);
} 
void SteamGameServer011::SetGameData(const char *pchGameData)
{
	return RedactedGameServer::SetGameData(pchGameData);
}
void SteamGameServer011::SetRegion(const char *pchRegionName)
{
	return RedactedGameServer::SetRegion(pchRegionName);
}

// Player list management.
int SteamGameServer011::SendUserConnectAndAuthenticate(uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser)
{
	return RedactedGameServer::SendUserConnectAndAuthenticate(unIPClient, pvAuthBlob, cubAuthBlobSize, pSteamIDUser);
}
CSteamID SteamGameServer011::CreateUnauthenticatedUserConnection()
{
	return RedactedGameServer::CreateUnauthenticatedUserConnection();
}
void SteamGameServer011::SendUserDisconnect(CSteamID steamIDUser)
{
	return RedactedGameServer::SendUserDisconnect(steamIDUser);
}
bool SteamGameServer011::BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore)
{
	return RedactedGameServer::BUpdateUserData(steamIDUser, pchPlayerName, uScore);
}

// New auth system APIs.
HAuthTicket SteamGameServer011::GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	return RedactedGameServer::GetAuthSessionTicket(pTicket, cbMaxTicket, pcbTicket);
}
EBeginAuthSessionResult SteamGameServer011::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	return RedactedGameServer::BeginAuthSession(pAuthTicket, cbAuthTicket, steamID);
}
void SteamGameServer011::EndAuthSession(CSteamID steamID)
{
	return RedactedGameServer::EndAuthSession(steamID);
}
void SteamGameServer011::CancelAuthTicket(HAuthTicket hAuthTicket)
{
	return RedactedGameServer::CancelAuthTicket(hAuthTicket);
}
EUserHasLicenseForAppResult SteamGameServer011::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	return RedactedGameServer::UserHasLicenseForApp(steamID, appID);
}
bool SteamGameServer011::RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup)
{
	return RedactedGameServer::RequestUserGroupStatus(steamIDUser, steamIDGroup);
}

// Queryable info.
void SteamGameServer011::GetGameplayStats()
{
	return RedactedGameServer::GetGameplayStats();
}
SteamAPICall_t SteamGameServer011::GetServerReputation()
{
	return RedactedGameServer::GetServerReputation();
}
uint32_t SteamGameServer011::GetPublicIP()
{
	return RedactedGameServer::GetPublicIP();
}
bool SteamGameServer011::HandleIncomingPacket(const void *pData, int cbData, uint32 srcIP, uint16 srcPort)
{
	return RedactedGameServer::HandleIncomingPacket(pData, cbData, srcIP, srcPort);
}
int SteamGameServer011::GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort)
{
	return RedactedGameServer::GetNextOutgoingPacket(pOut, cbMaxOut, pNetAdr, pPort);
}

// Heartbeats.
void SteamGameServer011::EnableHeartbeats(bool bActive)
{
	return RedactedGameServer::EnableHeartbeats(bActive);
}
void SteamGameServer011::SetHeartbeatInterval(int iHeartbeatInterval)
{
	return RedactedGameServer::SetHeartbeatInterval(iHeartbeatInterval);
}
void SteamGameServer011::ForceHeartbeat()
{
	return RedactedGameServer::ForceHeartbeat();
}
SteamAPICall_t SteamGameServer011::AssociateWithClan(CSteamID clanID)
{
	return RedactedGameServer::AssociateWithClan(clanID);
}
SteamAPICall_t SteamGameServer011::ComputeNewPlayerCompatibility(CSteamID steamID)
{
	return RedactedGameServer::ComputeNewPlayerCompatibility(steamID);
}

#pragma endregion