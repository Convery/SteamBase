/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Information about the game.
*/

#pragma once

#pragma region SteamMatchmaking001
class SteamMatchmaking001 : public ISteamMatchmaking001
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint32 unFlags);

	bool GetFavoriteGame2(int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame2(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame2(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	void RequestLobbyList(uint64 ulGameID, MatchMakingKeyValuePair_t *pFilters, uint32 nFilters);
	CSteamID GetLobbyByIndex(int iLobby);
	void CreateLobby(uint64 ulGameID, bool bPrivate);
	void JoinLobby(CSteamID steamIDLobby);
	void LeaveLobby(CSteamID steamIDLobby);
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);
	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);

	const char *GetLobbyData(CSteamID SteamIDLobby, const char *pchKey);
	void SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	void ChangeLobbyAdmin(CSteamID steamIDLobby, CSteamID steamIDNewAdmin);
	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);

	bool RequestLobbyData(CSteamID steamIDLobby);
};
#pragma endregion

#pragma region SteamMatchmaking002
class SteamMatchmaking002 : public ISteamMatchmaking002
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, uint32 *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, RTime32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, RTime32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	void RequestLobbyList();
	CSteamID GetLobbyByIndex(int iLobby);

	void CreateLobby(bool bPrivate);
	void JoinLobby(CSteamID steamIDLobby);
	void LeaveLobby(CSteamID steamIDLobby);
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);
	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);

	const char *GetLobbyData(CSteamID SteamIDLobby, const char *pchKey);
	void SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);

	bool RequestLobbyData(CSteamID steamIDLobby);

	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
};

#pragma endregion

#pragma region SteamMatchmaking003
class SteamMatchmaking003 : public ISteamMatchmaking003
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, RTime32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, RTime32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	SteamAPICall_t RequestLobbyList();
	void AddRequestLobbyListFilter(const char *pchKeyToMatch, const char *pchValueToMatch);
	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, int nComparisonType);
	OBSOLETE_FUNCTION void AddRequestLobbyListSlotsAvailableFilter();

	CSteamID GetLobbyByIndex(int iLobby);
	void CreateLobby(bool bPrivate);
	void JoinLobby(CSteamID steamIDLobby);
	void LeaveLobby(CSteamID steamIDLobby);
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);

	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);

	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey);
	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);

	bool RequestLobbyData(CSteamID steamIDLobby);
	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);
	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers);
	int GetLobbyMemberLimit(CSteamID steamIDLobby);
	OBSOLETE_FUNCTION void SetLobbyVoiceEnabled(CSteamID steamIDLobby, bool bEnabled);

	bool RequestFriendsLobbies();
};
#pragma endregion

#pragma region SteamMatchmaking004
class SteamMatchmaking004 : public ISteamMatchmaking004
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, RTime32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, RTime32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	SteamAPICall_t RequestLobbyList();
	void AddRequestLobbyListFilter(const char *pchKeyToMatch, const char *pchValueToMatch);
	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, int nComparisonType);
	OBSOLETE_FUNCTION void AddRequestLobbyListSlotsAvailableFilter();

	CSteamID GetLobbyByIndex(int iLobby);

	void CreateLobby(bool bPrivate);
	void JoinLobby(CSteamID steamIDLobby);
	void LeaveLobby(CSteamID steamIDLobby);
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);
	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);

	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey);
	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);

	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);
	bool RequestLobbyData(CSteamID steamIDLobby);
	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);
	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers);
	int GetLobbyMemberLimit(CSteamID steamIDLobby);

	bool RequestFriendsLobbies();
};
#pragma endregion

#pragma region SteamMatchmaking005
class SteamMatchmaking005 : ISteamMatchmaking005
{
public:
	// game server favorites storage
	// saves basic details about a multiplayer game server locally

	// returns the number of favorites servers the user has stored
	int GetFavoriteGameCount();

	// returns the details of the game server
	// iGame is of range [0,GetFavoriteGameCount())
	// *pnIP, *pnConnPort are filled in the with IP:port of the game server
	// *punFlags specify whether the game server was stored as an explicit favorite or in the history of connections
	// *pRTime32LastPlayedOnServer is filled in the with the Unix time the favorite was added
	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, RTime32 *pRTime32LastPlayedOnServer);

	// adds the game server to the local list; updates the time played of the server if it already exists in the list
	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, RTime32 rTime32LastPlayedOnServer);

	// removes the game server from the local storage; returns true if one was removed
	bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	///////
	// Game lobby functions

	// Get a list of relevant lobbies
	// this is an asynchronous request
	// results will be returned by LobbyMatchList_t callback & call result, with the number of lobbies found
	// this will never return lobbies that are full
	// to add more filter, the filter calls below need to be call before each and every RequestLobbyList() call
	// use the CCallResult<> object in steam_api.h to match the SteamAPICall_t call result to a function in an object, e.g.
	/*
	class CMyLobbyListManager
	{
	CCallResult<CMyLobbyListManager, LobbyMatchList_t> m_CallResultLobbyMatchList;
	void FindLobbies()
	{
	// SteamMatchmaking()->AddRequestLobbyListFilter*() functions would be called here, before RequestLobbyList()
	SteamAPICall_t hSteamAPICall = SteamMatchmaking()->RequestLobbyList();
	m_CallResultLobbyMatchList.Set( hSteamAPICall, this, &CMyLobbyListManager::OnLobbyMatchList );
	}

	void OnLobbyMatchList( LobbyMatchList_t *pLobbyMatchList, bool bIOFailure )
	{
	// lobby list has be retrieved from Steam back-end, use results
	}
	}
	*/
	// 
	SteamAPICall_t RequestLobbyList();
	// filters for lobbies
	// this needs to be called before RequestLobbyList() to take effect
	// these are cleared on each call to RequestLobbyList()
	void AddRequestLobbyListFilter(const char *pchKeyToMatch, const char *pchValueToMatch);
	// numerical comparison
	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, int nComparisonType);
	// slots available filter
	OBSOLETE_FUNCTION void AddRequestLobbyListSlotsAvailableFilter();
	// returns results closest to the specified value. Multiple near filters can be added, with early filters taking precedence
	void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo);

	// returns the CSteamID of a lobby, as retrieved by a RequestLobbyList call
	// should only be called after a LobbyMatchList_t callback is received
	// iLobby is of the range [0, LobbyMatchList_t::m_nLobbiesMatching)
	// the returned CSteamID::IsValid() will be false if iLobby is out of range
	//STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetLobbyByIndex, int, iLobby) /* CSteamID GetLobbyByIndex( int iLobby );*/
	CSteamID GetLobbyByIndex(int iLobby);

	// Create a lobby on the Steam servers.
	// If private, then the lobby will not be returned by any RequestLobbyList() call; the CSteamID
	// of the lobby will need to be communicated via game channels or via InviteUserToLobby()
	// this is an asynchronous request
	// results will be returned by LobbyCreated_t callback and call result; lobby is joined & ready to use at this pointer
	// a LobbyEnter_t callback will also be received (since the local user is joining their own lobby)
	SteamAPICall_t CreateLobby(ELobbyType eLobbyType);

	// Joins an existing lobby
	// this is an asynchronous request
	// results will be returned by LobbyEnter_t callback & call result, check m_EChatRoomEnterResponse to see if was successful
	// lobby metadata is available to use immediately on this call completing
	SteamAPICall_t JoinLobby(CSteamID steamIDLobby);

	// Leave a lobby; this will take effect immediately on the client side
	// other users in the lobby will be notified by a LobbyChatUpdate_t callback
	void LeaveLobby(CSteamID steamIDLobby);

	// Invite another user to the lobby
	// the target user will receive a LobbyInvite_t callback
	// will return true if the invite is successfully sent, whether or not the target responds
	// returns false if the local user is not connected to the Steam servers
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);

	// Lobby iteration, for viewing details of users in a lobby
	// only accessible if the lobby user is a member of the specified lobby
	// persona information for other lobby members (name, avatar, etc.) will be asynchronously received
	// and accessible via ISteamFriends interface

	// returns the number of users in the specified lobby
	int GetNumLobbyMembers(CSteamID steamIDLobby);
	// returns the CSteamID of a user in the lobby
	// iMember is of range [0,GetNumLobbyMembers())
	//STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetLobbyMemberByIndex, CSteamID, steamIDLobby, int, iMember) /* CSteamID GetLobbyMemberByIndex( CSteamID steamIDLobby, int iMember );*/
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);

	// Get data associated with this lobby
	// takes a simple key, and returns the string associated with it
	// "" will be returned if no value is set, or if steamIDLobby is invalid
	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey);
	// Sets a key/value pair in the lobby metadata
	// each user in the lobby will be broadcast this new value, and any new users joining will receive any existing data
	// this can be used to set lobby names, map, etc.
	// to reset a key, just set it to ""
	// other users in the lobby will receive notification of the lobby data change via a LobbyDataUpdate_t callback
	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);

	// As above, but gets per-user data for someone in this lobby
	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	// Sets per-user metadata (for the local user implicitly)
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);

	// Broadcasts a chat message to the all the users in the lobby
	// users in the lobby (including the local user) will receive a LobbyChatMsg_t callback
	// returns true if the message is successfully sent
	// pvMsgBody can be binary or text data, up to 4k
	// if pvMsgBody is text, cubMsgBody should be strlen( text ) + 1, to include the null terminator
	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	// Get a chat message as specified in a LobbyChatMsg_t callback
	// iChatID is the LobbyChatMsg_t::m_iChatID value in the callback
	// *pSteamIDUser is filled in with the CSteamID of the member
	// *pvData is filled in with the message itself
	// return value is the number of bytes written into the buffer
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);

	// Refreshes metadata for a lobby you're not necessarily in right now
	// you never do this for lobbies you're a member of, only if your
	// this will send down all the metadata associated with a lobby
	// this is an asynchronous call
	// returns false if the local user is not connected to the Steam servers
	// restart are returned by a LobbyDataUpdate_t callback
	bool RequestLobbyData(CSteamID steamIDLobby);

	// sets the game server associated with the lobby
	// usually at this point, the users will join the specified game server
	// either the IP/Port or the steamID of the game server has to be valid, depending on how you want the clients to be able to connect
	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
	// returns the details of a game server set in a lobby - returns false if there is no game server set, or that lobby doesn't exist
	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);

	// set the limit on the # of users who can join the lobby
	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers);
	// returns the current limit on the # of users who can join the lobby; returns 0 if no limit is defined
	int GetLobbyMemberLimit(CSteamID steamIDLobby);

	bool RequestFriendsLobbies();

	// updates which type of lobby it is
	// only lobbies that are k_ELobbyTypePublic will be returned by RequestLobbyList() calls
	bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType);

	// returns the current lobby owner
	// you must be a member of the lobby to access this
	// there always one lobby owner - if the current owner leaves, another user will become the owner
	// it is possible (bur rare) to join a lobby just as the owner is leaving, thus entering a lobby with self as the owner
	//STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetLobbyOwner, CSteamID, steamIDLobby) /* CSteamID GetLobbyOwner( CSteamID steamIDLobby );*/
	CSteamID GetLobbyOwner(CSteamID steamIDLobby);

	OBSOLETE_FUNCTION double GetLobbyDistance(CSteamID steamIDLobby);
};
#pragma endregion

#pragma region SteamMatchmaking006
class SteamMatchmaking006 : public ISteamMatchmaking006
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, RTime32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, RTime32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	SteamAPICall_t RequestLobbyList();
	void AddRequestLobbyListFilter(const char *pchKeyToMatch, const char *pchValueToMatch);
	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, int nComparisonType);
	void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo);


	CSteamID GetLobbyByIndex(int iLobby);
	SteamAPICall_t CreateLobby(ELobbyType eLobbyType);
	SteamAPICall_t JoinLobby(CSteamID steamIDLobby);
	void LeaveLobby(CSteamID steamIDLobby);
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);

	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);

	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey);
	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);

	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);

	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);
	bool RequestLobbyData(CSteamID steamIDLobby);

	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);

	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers);
	int GetLobbyMemberLimit(CSteamID steamIDLobby);

	bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType);

	CSteamID GetLobbyOwner(CSteamID steamIDLobby);
};
#pragma endregion

#pragma region SteamMatchmaking007
class SteamMatchmaking007 : public ISteamMatchmaking007
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	SteamAPICall_t RequestLobbyList();
	void AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType);
	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType);
	void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo);
	void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable);

	CSteamID GetLobbyByIndex(int iLobby);
	SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers);
	SteamAPICall_t JoinLobby(CSteamID steamIDLobby);
	void LeaveLobby(CSteamID steamIDLobby);
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);
	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);
	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey);
	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	int GetLobbyDataCount(CSteamID steamIDLobby);
	bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize);
	bool DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey);
	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);
	bool RequestLobbyData(CSteamID steamIDLobby);
	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);
	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers);
	int GetLobbyMemberLimit(CSteamID steamIDLobby);
	bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType);
	bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable);
	CSteamID GetLobbyOwner(CSteamID steamIDLobby);
	bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner);
};
#pragma endregion


#pragma region SteamMatchmaking008
class SteamMatchmaking008 : public ISteamMatchmaking008
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer);
	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);
	bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	SteamAPICall_t RequestLobbyList();
	void AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType);
	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType);
	void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo);
	void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable);
	void AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter);
	void AddRequestLobbyListResultCountFilter(int cMaxResults);

	CSteamID GetLobbyByIndex(int iLobby);
	SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers);
	SteamAPICall_t JoinLobby(CSteamID steamIDLobby);
	void LeaveLobby(CSteamID steamIDLobby);
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);
	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);
	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey);
	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	int GetLobbyDataCount(CSteamID steamIDLobby);
	bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize);
	bool DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey);
	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);
	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);
	bool RequestLobbyData(CSteamID steamIDLobby);
	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);
	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers);
	int GetLobbyMemberLimit(CSteamID steamIDLobby);
	bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType);
	bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable);
	CSteamID GetLobbyOwner(CSteamID steamIDLobby);
	bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner);
};
#pragma endregion

#pragma region SteamMatchmaking009
class SteamMatchmaking009 : public ISteamMatchmaking009
{
public:
	int GetFavoriteGameCount();

	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer);

	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);

	bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);

	SteamAPICall_t RequestLobbyList();
	void AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType);
	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType);
	void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo);
	void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable);
	void AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter);
	void AddRequestLobbyListResultCountFilter(int cMaxResults);

	void AddRequestLobbyListCompatibleMembersFilter(CSteamID steamID);

	CSteamID GetLobbyByIndex(int iLobby);
	SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers);

	SteamAPICall_t JoinLobby(CSteamID steamIDLobby);

	void LeaveLobby(CSteamID steamIDLobby);

	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee);

	int GetNumLobbyMembers(CSteamID steamIDLobby);
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember);
	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey);
	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);

	int GetLobbyDataCount(CSteamID steamIDLobby);

	bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize);

	bool DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey);

	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey);
	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue);

	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody);
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType);

	bool RequestLobbyData(CSteamID steamIDLobby);

	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer);

	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers);
	int GetLobbyMemberLimit(CSteamID steamIDLobby);

	bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType);

	bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable);

	CSteamID GetLobbyOwner(CSteamID steamIDLobby);
	bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner);

	bool SetLinkedLobby(CSteamID steamIDLobby, CSteamID steamIDLobby2);
};
#pragma endregion