/*
This project is released under the GPL 2.0 license.
Please do no evil.

Initial author: (https://github.com/)Sokie
Started: 2015-04-29
Purpose: Functions for match making services for clients to get to game lists and details
*/

#include "..\..\StdInclude.h"

HServerListRequest RedactedMatchmakingServers::RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}
HServerListRequest RedactedMatchmakingServers::RequestLANServerList(AppId_t iApp, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}
HServerListRequest RedactedMatchmakingServers::RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}
HServerListRequest RedactedMatchmakingServers::RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}
HServerListRequest RedactedMatchmakingServers::RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}
HServerListRequest RedactedMatchmakingServers::RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t **ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}

#pragma region v1_queries
gameserveritem_t *RedactedMatchmakingServers::GetServerDetails(EMatchMakingType eType, int iServer)
{
	PrintCurrentFunction();
	return NULL;
}

void RedactedMatchmakingServers::CancelQuery(EMatchMakingType eType)
{
	PrintCurrentFunction();
}
void RedactedMatchmakingServers::RefreshQuery(EMatchMakingType eType)
{
	PrintCurrentFunction();
}
bool RedactedMatchmakingServers::IsRefreshing(EMatchMakingType eType)
{
	PrintCurrentFunction();
	return false;
}
int RedactedMatchmakingServers::GetServerCount(EMatchMakingType eType)
{
	PrintCurrentFunction();
	return 1;
}
void RedactedMatchmakingServers::RefreshServer(EMatchMakingType eType, int iServer)
{
	PrintCurrentFunction();
}
#pragma endregion

#pragma region v2_queries
void RedactedMatchmakingServers::ReleaseRequest(HServerListRequest hServerListRequest)
{
	PrintCurrentFunction();
}

gameserveritem_t *RedactedMatchmakingServers::GetServerDetails(HServerListRequest hRequest, int iServer)
{
	PrintCurrentFunction();
	return NULL;
}

void RedactedMatchmakingServers::CancelQuery(HServerListRequest hRequest)
{
	PrintCurrentFunction();
}

void RedactedMatchmakingServers::RefreshQuery(HServerListRequest hRequest)
{
	PrintCurrentFunction();
}

bool RedactedMatchmakingServers::IsRefreshing(HServerListRequest hRequest)
{
	PrintCurrentFunction();
	return false;
}

int RedactedMatchmakingServers::GetServerCount(HServerListRequest hRequest)
{
	PrintCurrentFunction();
	return 1;
}

void RedactedMatchmakingServers::RefreshServer(HServerListRequest hRequest, int iServer)
{
	PrintCurrentFunction();
}
#pragma endregion

HServerQuery RedactedMatchmakingServers::PingServer(uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}

HServerQuery RedactedMatchmakingServers::PlayerDetails(uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}

HServerQuery RedactedMatchmakingServers::ServerRules(uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse *pRequestServersResponse)
{
	PrintCurrentFunction();
	return NULL;
}

void RedactedMatchmakingServers::CancelServerQuery(HServerQuery hServerQuery)
{
	PrintCurrentFunction();
}