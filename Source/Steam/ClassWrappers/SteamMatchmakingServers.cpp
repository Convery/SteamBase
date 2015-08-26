/*
This project is released under the GPL 2.0 license.
Please do no evil.

Initial author: (https://github.com/)Sokie
Started: 2015-04-29
Purpose: Functions for match making services for clients to get to game lists and details
*/
#include "..\..\StdInclude.h"

#pragma region SteamMatchmakingServers001
void SteamMatchmakingServers001::RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001 *pRequestServersResponse)
{
	//RedactedMatchmakingServers::RequestInternetServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
void SteamMatchmakingServers001::RequestLANServerList(AppId_t iApp, ISteamMatchmakingServerListResponse001 *pRequestServersResponse)
{
	// RedactedMatchmakingServers::RequestLANServerList(iApp, pRequestServersResponse);
}
void SteamMatchmakingServers001::RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001 *pRequestServersResponse)
{
	//RedactedMatchmakingServers::RequestFriendsServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
void SteamMatchmakingServers001::RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001 *pRequestServersResponse)
{
	// RedactedMatchmakingServers::RequestFavoritesServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
void SteamMatchmakingServers001::RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001 *pRequestServersResponse)
{
	//RedactedMatchmakingServers::RequestHistoryServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
void SteamMatchmakingServers001::RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse001 *pRequestServersResponse)
{
	//RedactedMatchmakingServers::RequestSpectatorServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}

gameserveritem_t *SteamMatchmakingServers001::GetServerDetails(EMatchMakingType eType, int iServer)
{
	return RedactedMatchmakingServers::GetServerDetails(eType, iServer);
}

void SteamMatchmakingServers001::CancelQuery(EMatchMakingType eType)
{
	RedactedMatchmakingServers::CancelQuery(eType);
}
void SteamMatchmakingServers001::RefreshQuery(EMatchMakingType eType)
{
	RedactedMatchmakingServers::RefreshQuery(eType);
}
bool SteamMatchmakingServers001::IsRefreshing(EMatchMakingType eType)
{
	return RedactedMatchmakingServers::IsRefreshing(eType);
}

int SteamMatchmakingServers001::GetServerCount(EMatchMakingType eType)
{
	return RedactedMatchmakingServers::GetServerCount(eType);
}
void SteamMatchmakingServers001::RefreshServer(EMatchMakingType eType, int iServer)
{
	RedactedMatchmakingServers::RefreshServer(eType, iServer);
}

HServerQuery SteamMatchmakingServers001::PingServer(uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::PingServer(unIP, usPort, pRequestServersResponse);
}

HServerQuery SteamMatchmakingServers001::PlayerDetails(uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::PlayerDetails(unIP, usPort, pRequestServersResponse);
}

HServerQuery SteamMatchmakingServers001::ServerRules(uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::ServerRules(unIP, usPort, pRequestServersResponse);
}

void SteamMatchmakingServers001::CancelServerQuery(HServerQuery hServerQuery)
{
	RedactedMatchmakingServers::CancelServerQuery(hServerQuery);
}
#pragma endregion

#pragma region SteamMatchmakingServers002

HServerListRequest SteamMatchmakingServers002::RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::RequestInternetServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
HServerListRequest SteamMatchmakingServers002::RequestLANServerList(AppId_t iApp, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::RequestLANServerList(iApp, pRequestServersResponse);
}
HServerListRequest SteamMatchmakingServers002::RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::RequestFriendsServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
HServerListRequest SteamMatchmakingServers002::RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::RequestFavoritesServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
HServerListRequest SteamMatchmakingServers002::RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::RequestHistoryServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}
HServerListRequest SteamMatchmakingServers002::RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::RequestSpectatorServerList(iApp, ppchFilters, nFilters, pRequestServersResponse);
}

void SteamMatchmakingServers002::ReleaseRequest(HServerListRequest hServerListRequest)
{
	RedactedMatchmakingServers::ReleaseRequest(hServerListRequest);
}

gameserveritem_t *SteamMatchmakingServers002::GetServerDetails(HServerListRequest hRequest, int iServer)
{
	return RedactedMatchmakingServers::GetServerDetails(hRequest, iServer);
}

void SteamMatchmakingServers002::CancelQuery(HServerListRequest hRequest)
{
	RedactedMatchmakingServers::CancelQuery(hRequest);
}

void SteamMatchmakingServers002::RefreshQuery(HServerListRequest hRequest)
{
	RedactedMatchmakingServers::RefreshQuery(hRequest);
}

bool SteamMatchmakingServers002::IsRefreshing(HServerListRequest hRequest)
{
	return RedactedMatchmakingServers::IsRefreshing(hRequest);
}

int SteamMatchmakingServers002::GetServerCount(HServerListRequest hRequest)
{
	return RedactedMatchmakingServers::GetServerCount(hRequest);
}

void SteamMatchmakingServers002::RefreshServer(HServerListRequest hRequest, int iServer)
{
	RedactedMatchmakingServers::RefreshServer(hRequest, iServer);
}

HServerQuery SteamMatchmakingServers002::PingServer(uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::PingServer(unIP, usPort, pRequestServersResponse);
}

HServerQuery SteamMatchmakingServers002::PlayerDetails(uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::PlayerDetails(unIP, usPort, pRequestServersResponse);
}

HServerQuery SteamMatchmakingServers002::ServerRules(uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse)
{
	return RedactedMatchmakingServers::ServerRules(unIP, usPort, pRequestServersResponse);
}

void SteamMatchmakingServers002::CancelServerQuery(HServerQuery hServerQuery)
{
	RedactedMatchmakingServers::CancelServerQuery(hServerQuery);
}
#pragma endregion