/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Information about the application.
*/

#include "..\..\StdInclude.h"

int RedactedMatchmaking::GetFavoriteGameCount()
{
	PrintCurrentFunction();
	return 0;
}

bool RedactedMatchmaking::GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer)
{
	PrintCurrentFunction();
	return false;
}

int RedactedMatchmaking::AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer)
{
	PrintCurrentFunction();
	return 0;
}

bool RedactedMatchmaking::RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
{
	PrintCurrentFunction();
	return true;
}

void RedactedMatchmaking::RequestLobbyList(uint64 ulGameID, MatchMakingKeyValuePair_t *pFilters, uint32 nFilters)
{
	PrintCurrentFunction();
}

SteamAPICall_t RedactedMatchmaking::RequestLobbyList()
{
	PrintCurrentFunction();
	return NULL;
}

void RedactedMatchmaking::AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType)
{
	PrintCurrentFunction();
}
void RedactedMatchmaking::AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType)
{
	PrintCurrentFunction();
}
void RedactedMatchmaking::AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo)
{
	PrintCurrentFunction();
}
void RedactedMatchmaking::AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable)
{
	PrintCurrentFunction();
}
void RedactedMatchmaking::AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter)
{
	PrintCurrentFunction();
}
void RedactedMatchmaking::AddRequestLobbyListResultCountFilter(int cMaxResults)
{
	PrintCurrentFunction();
}

void RedactedMatchmaking::AddRequestLobbyListCompatibleMembersFilter(CSteamID steamID)
{
	PrintCurrentFunction();
}

bool RedactedMatchmaking::RequestFriendsLobbies()
{
	PrintCurrentFunction();
	return false;
}

CSteamID RedactedMatchmaking::GetLobbyByIndex(int iLobby)
{
	PrintCurrentFunction();
	CSteamID id = CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeChat);
	return id;
}

SteamAPICall_t RedactedMatchmaking::CreateLobby(ELobbyType eLobbyType)
{
	return RedactedMatchmaking::CreateLobby(eLobbyType, 18);
}

SteamAPICall_t RedactedMatchmaking::CreateLobby(ELobbyType eLobbyType, int cMaxMembers)
{
	PrintCurrentFunction();

	
	SteamAPICall_t result = SteamCallback::RegisterCall();

	/* example callback use case
	LobbyCreated_t* retvals = (LobbyCreated_t*)malloc(sizeof(LobbyCreated_t));
	
	//generate lobby and persist
	CSteamID id = CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeChat);

	retvals->m_eResult = k_EResultOK;
	retvals->m_ulSteamIDLobby = id.ConvertToUint64();

	SteamCallback::ReturnCall(retvals, sizeof(LobbyCreated_t), LobbyCreated_t::k_iCallback, result);
	//create a callback for the join for the lobby owner
	JoinLobby(id);
	
	*/
	
	return result;
}

SteamAPICall_t RedactedMatchmaking::JoinLobby(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	SteamAPICall_t result = SteamCallback::RegisterCall();
	/* example callback use case
	LobbyEnter_t* retvals = (LobbyEnter_t*)malloc(sizeof(LobbyEnter_t));
	retvals->m_bLocked = false;
	retvals->m_EChatRoomEnterResponse = k_EChatRoomEnterResponseSuccess;
	retvals->m_rgfChatPermissions = k_EChatPermissionEveryoneDefault;
	retvals->m_ulSteamIDLobby = steamIDLobby.ConvertToUint64();

	SteamCallback::ReturnCall(retvals, sizeof(LobbyEnter_t), LobbyEnter_t::k_iCallback, result);*/
	return result;
}

void RedactedMatchmaking::LeaveLobby(CSteamID steamIDLobby)
{
	PrintCurrentFunction();

	/* example callback use case
	SteamAPICall_t result = SteamCallback::RegisterCall();
	LobbyChatUpdate_t* retvals = (LobbyChatUpdate_t*)malloc(sizeof(LobbyChatUpdate_t));
	retvals->m_rgfChatMemberStateChange = EChatMemberStateChange::k_EChatMemberStateChangeLeft;
	retvals->m_ulSteamIDLobby = steamIDLobby;
	retvals->m_ulSteamIDMakingChange = SteamProxy::GetUserID();
	retvals->m_ulSteamIDUserChanged = SteamProxy::GetUserID();

	SteamCallback::ReturnCall(retvals, sizeof(LobbyChatUpdate_t), LobbyChatUpdate_t::k_iCallback, result);*/
}

bool RedactedMatchmaking::InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee)
{
	PrintCurrentFunction();
	return true;
}

int RedactedMatchmaking::GetNumLobbyMembers(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return 1;
}
CSteamID RedactedMatchmaking::GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember)
{
	PrintCurrentFunction();
	return SteamProxy::GetUserID();
}
const char *RedactedMatchmaking::GetLobbyData(CSteamID steamIDLobby, const char *pchKey)
{
	PrintCurrentFunction();
	return "data";
}
bool RedactedMatchmaking::SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
{
	PrintCurrentFunction();
	return true;
}

int RedactedMatchmaking::GetLobbyDataCount(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return 0;
}

bool RedactedMatchmaking::GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize)
{
	PrintCurrentFunction();
	return true;
}

bool RedactedMatchmaking::DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey)
{
	PrintCurrentFunction();
	return true;
}

const char *RedactedMatchmaking::GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey)
{
	PrintCurrentFunction();
	return "data";
}
void RedactedMatchmaking::SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
{
	PrintCurrentFunction();
}

bool RedactedMatchmaking::SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody)
{
	PrintCurrentFunction();

	/* example callback use case
	SteamAPICall_t result = SteamCallback::RegisterCall();
	LobbyChatMsg_t* retvals = (LobbyChatMsg_t*)malloc(sizeof(LobbyChatMsg_t));
	retvals->m_eChatEntryType = 0;
	retvals->m_iChatID = 0;
	retvals->m_ulSteamIDLobby = CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeChat).ConvertToUint64;
	retvals->m_ulSteamIDUser = SteamProxy::GetUserID().ConvertToUint64;

	SteamCallback::ReturnCall(retvals, sizeof(LobbyChatMsg_t), LobbyChatMsg_t::k_iCallback, result);*/

	return true;
}
int RedactedMatchmaking::GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType)
{
	PrintCurrentFunction();
	return 0;
}

bool RedactedMatchmaking::RequestLobbyData(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return true;
}

void RedactedMatchmaking::SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer)
{
	PrintCurrentFunction();
}
bool RedactedMatchmaking::GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer)
{
	PrintCurrentFunction();
	return true;
}

bool RedactedMatchmaking::SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers)
{
	PrintCurrentFunction();
	return true;
}
int RedactedMatchmaking::GetLobbyMemberLimit(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return 1;
}

bool RedactedMatchmaking::SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType)
{
	PrintCurrentFunction();
	return true;
}

bool RedactedMatchmaking::SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable)
{
	PrintCurrentFunction();
	return true;
}

CSteamID RedactedMatchmaking::GetLobbyOwner(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return SteamProxy::GetUserID();
}
bool RedactedMatchmaking::SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner)
{
	PrintCurrentFunction();
	return true;
}

bool RedactedMatchmaking::SetLinkedLobby(CSteamID steamIDLobby, CSteamID steamIDLobby2)
{
	PrintCurrentFunction();
	return true;
}