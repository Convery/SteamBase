/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Information about the application.
*/

#include "..\..\StdInclude.h"

int GetFavoriteGameCount()
{
	PrintCurrentFunction();
	return 0;
}

bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer)
{
	PrintCurrentFunction();
	return false;
}

int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer)
{
	PrintCurrentFunction();
	return 0;
}

bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
{
	PrintCurrentFunction();
	return true;
}

SteamAPICall_t RequestLobbyList()
{
	PrintCurrentFunction();
	return NULL;
}

void AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType)
{
	PrintCurrentFunction();
}
void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType)
{
	PrintCurrentFunction();
}
void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo)
{
	PrintCurrentFunction();
}
void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable)
{
	PrintCurrentFunction();
}
void AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter)
{
	PrintCurrentFunction();
}
void AddRequestLobbyListResultCountFilter(int cMaxResults)
{
	PrintCurrentFunction();
}

void AddRequestLobbyListCompatibleMembersFilter(CSteamID steamID)
{
	PrintCurrentFunction();
}

CSteamID GetLobbyByIndex(int iLobby)
{
	PrintCurrentFunction();
	CSteamID id = CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeChat);
	return id;
}
SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers)
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

SteamAPICall_t JoinLobby(CSteamID steamIDLobby)
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

void LeaveLobby(CSteamID steamIDLobby)
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

bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee)
{
	PrintCurrentFunction();
	return true;
}

int GetNumLobbyMembers(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return 1;
}
CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember)
{
	PrintCurrentFunction();
	return SteamProxy::GetUserID();
}
const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey)
{
	PrintCurrentFunction();
	return "data";
}
bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
{
	PrintCurrentFunction();
	return true;
}

int GetLobbyDataCount(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return 0;
}

bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize)
{
	PrintCurrentFunction();
	return true;
}

bool DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey)
{
	PrintCurrentFunction();
	return true;
}

const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey)
{
	PrintCurrentFunction();
	return "data";
}
void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
{
	PrintCurrentFunction();
}

bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody)
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
int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType)
{
	PrintCurrentFunction();
	return 0;
}

bool RequestLobbyData(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return true;
}

void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer)
{
	PrintCurrentFunction();
}
bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer)
{
	PrintCurrentFunction();
	return true;
}

bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers)
{
	PrintCurrentFunction();
	return true;
}
int GetLobbyMemberLimit(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return 1;
}

bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType)
{
	PrintCurrentFunction();
	return true;
}

bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable)
{
	PrintCurrentFunction();
	return true;
}

CSteamID GetLobbyOwner(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	return SteamProxy::GetUserID();
}
bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner)
{
	PrintCurrentFunction();
	return true;
}

bool SetLinkedLobby(CSteamID steamIDLobby, CSteamID steamIDLobby2)
{
	PrintCurrentFunction();
	return true;
}