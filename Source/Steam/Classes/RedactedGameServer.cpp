/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		GameServer.
*/

#include "..\..\StdInclude.h"


// This is called by SteamGameServer_Init, and you will usually not need to call it directly
bool RedactedGameServer::InitGameServer(uint32 unGameIP, uint16 unGamePort, uint16 usQueryPort, uint32 unServerFlags, AppId_t nAppID, const char *pchVersion)
{
	PrintCurrentFunction();
	return true;
}
void RedactedGameServer::SetProduct(const char *pchProductName)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetGameDescription(const char *pchGameDescription)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetModDir(const char *pchModDir)
{
	PrintCurrentFunction();
}

void RedactedGameServer::SetDedicatedServer(bool bDedicatedServer)
{
	PrintCurrentFunction();
}

// Login.
void RedactedGameServer::LogOn(const char *pszUnk)
{
	PrintCurrentFunction();
}

void RedactedGameServer::LogOn(const char *pszAccountName, const char *pszPassword)
{
	PrintCurrentFunction();
}

void RedactedGameServer::LogOnAnonymous()
{
	PrintCurrentFunction();
	uint64_t callID = NULL;
	SteamServersConnected_t *Response = nullptr;

	callID = SteamCallback::RegisterCall();
	Response = static_cast<SteamServersConnected_t*>(malloc(sizeof(SteamServersConnected_t)));

	SteamCallback::ReturnCall(Response, sizeof(SteamServersConnected_t), Response->k_iCallback, callID);
}
void RedactedGameServer::LogOff()
{
	PrintCurrentFunction();
}

// Status.
bool RedactedGameServer::BLoggedOn()
{
	PrintCurrentFunction();
	return true;
}
bool RedactedGameServer::BSecure()
{
	PrintCurrentFunction();
	return false;
}
CSteamID RedactedGameServer::GetSteamID()
{
	PrintCurrentFunction();
	return CSteamID((uint64_t)0x01400000DEADC0DE);
}
bool RedactedGameServer::WasRestartRequested()
{
	PrintCurrentFunction();
	return false;
}

// Server state.
void RedactedGameServer::SetMaxPlayerCount(int cPlayersMax)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetBotPlayerCount(int cBotPlayers)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetServerName(const char *pszServerName)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetMapName(const char *pszMapName)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetPasswordProtected(bool bPasswordProtected)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetSpectatorPort(uint16_t unSpectatorPort)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetSpectatorServerName(const char *pszSpectatorServerName)
{
	PrintCurrentFunction();
}
void RedactedGameServer::ClearAllKeyValues()
{
	PrintCurrentFunction();
}

// Add/update a key/value pair.
void RedactedGameServer::SetKeyValue(const char *pKey, const char *pValue)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetGameTags(const char *pchGameTags)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetGameData(const char *pchGameData)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetRegion(const char *pchRegionName)
{
	PrintCurrentFunction();
}

// Player list management.
int RedactedGameServer::SendUserConnectAndAuthenticate(uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser)
{
	PrintCurrentFunction();
	return 0;
}
CSteamID RedactedGameServer::CreateUnauthenticatedUserConnection()
{
	PrintCurrentFunction();
	return CSteamID((uint64_t)0x01400000DEADC0DE);
}
void RedactedGameServer::SendUserDisconnect(CSteamID steamIDUser)
{
	PrintCurrentFunction();
}
bool RedactedGameServer::BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore)
{
	PrintCurrentFunction();
	return false;
}

// New auth system APIs.
HAuthTicket RedactedGameServer::GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	PrintCurrentFunction();
	return 0;
}
EBeginAuthSessionResult RedactedGameServer::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	PrintCurrentFunction();
	return k_EBeginAuthSessionResultDuplicateRequest;
}
void RedactedGameServer::EndAuthSession(CSteamID steamID)
{
	PrintCurrentFunction();
}
void RedactedGameServer::CancelAuthTicket(HAuthTicket hAuthTicket)
{
	PrintCurrentFunction();
}
EUserHasLicenseForAppResult RedactedGameServer::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	PrintCurrentFunction();
	return k_EUserHasLicenseResultNoAuth;
}
bool RedactedGameServer::RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup)
{
	PrintCurrentFunction();
	return false;
}

// Queryable info.
void RedactedGameServer::GetGameplayStats()
{
	PrintCurrentFunction();
}
uint64_t RedactedGameServer::GetServerReputation()
{
	PrintCurrentFunction();
	return 0;
}
uint32_t RedactedGameServer::GetPublicIP()
{
	PrintCurrentFunction();
	//return Global::System_ExternalIP;
	return 0;
}
bool RedactedGameServer::HandleIncomingPacket(const void *pData, int cbData, uint32 srcIP, uint16 srcPort)
{
	PrintCurrentFunction();
	return true;
}
int RedactedGameServer::GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort)
{
	PrintCurrentFunction();
	return 0;
}

// Heartbeats.
void RedactedGameServer::EnableHeartbeats(bool bActive)
{
	PrintCurrentFunction();
}
void RedactedGameServer::SetHeartbeatInterval(int iHeartbeatInterval)
{
	PrintCurrentFunction();
}
void RedactedGameServer::ForceHeartbeat()
{
	PrintCurrentFunction();
}
SteamAPICall_t RedactedGameServer::AssociateWithClan(CSteamID clanID)
{
	PrintCurrentFunction();
	return 0;
}
SteamAPICall_t RedactedGameServer::ComputeNewPlayerCompatibility(CSteamID steamID)
{
	PrintCurrentFunction();
	return 0;
}
