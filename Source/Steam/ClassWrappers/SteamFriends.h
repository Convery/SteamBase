/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
	Friendslist.
	*/

#pragma once

#pragma region SteamFriends001
class SteamFriends001 : public ISteamFriends001
{
public:
	// returns the local players name - guaranteed to not be NULL.
	const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the friend status of the current user
	EPersonaState GetPersonaState() = 0;
	// sets the status, communicates to server, tells all friends
	void SetPersonaState(EPersonaState ePersonaState) = 0;

	// adds a friend to the users list.  Friend will be notified that they have been added, and have the option of accept/decline
	bool AddFriend(CSteamID steamIDFriend) = 0;
	// removes the friend from the list, and blocks them from contacting the user again
	bool RemoveFriend(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	bool HasFriend(CSteamID steamIDFriend) = 0;

	// gets the relationship to a user
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// retrieves details about the game the friend is currently playing - returns false if the friend is not playing any games
	// this is deprecated, please use the GetFriendGamePlayed# functions below
	bool Deprecated_GetFriendGamePlayed(CSteamID steamIDFriend, int32 *pnGameID, uint32 *punGameIP, uint16 *pusGamePort) = 0;

	// returns the name of a friend - guaranteed to not be NULL.
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// adds a friend by email address or account name - value returned in callback
	HSteamCall AddFriendByName(const char *pchEmailOrAccountName) = 0;

	// friend iteration
	int32_t GetFriendCount() = 0;
	CSteamID GetFriendByIndex(int32_t iFriend) = 0;

	// generic friend->friend message sending
	// DEPRECATED, use the sized-buffer version instead (has much higher max buffer size)
	void SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const char *pchMsgBody) = 0;

	// steam registry, accessed by friend
	void SetFriendRegValue(CSteamID steamIDFriend, const char *pchKey, const char *pchValue) = 0;
	const char *GetFriendRegValue(CSteamID steamIDFriend, const char *pchKey) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// chat message iteration
	// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
	// returns 0 if the steamID or iChatID are invalid
	int32_t GetChatMessage(CSteamID steamIDFriend, int32_t iChatID, void *pvData, int32_t cubData, EChatEntryType *peFriendMsgType) = 0;

	// generic friend->friend message sending, takes a sized buffer
	bool SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const void *pvMsgBody, int32_t cubMsgBody) = 0;

	// returns the chatID that a chat should be resumed from when switching chat contexts
	OBSOLETE_FUNCTION int32_t GetChatIDOfChatHistoryStart(CSteamID steamIDFriend) = 0;
	// sets where a chat with a user should resume
	OBSOLETE_FUNCTION void SetChatHistoryStart(CSteamID steamIDFriend, int32_t iChatID) = 0;
	// clears the chat history - should be called when a chat dialog closes
	// the chat history can still be recovered by another context using SetChatHistoryStart() to reset the ChatIDOfChatHistoryStart
	void ClearChatHistory(CSteamID steamIDFriend) = 0;

	HSteamCall InviteFriendByEmail(const char *pchEmailOrAccountName) = 0;

	uint32 GetBlockedFriendCount() = 0;

	bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort) = 0;
	bool GetFriendGamePlayed2(CSteamID steamDIFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;
};
#pragma endregion

#pragma region SteamFriends002
class SteamFriends002 : public ISteamFriends002
{
public:
	// returns the local players name - guaranteed to not be NULL.
	const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;
	// gets the friend status of the current user
	EPersonaState GetPersonaState() = 0;
	// sets the status, communicates to server, tells all friends
	void SetPersonaState(EPersonaState ePersonaState) = 0;

	// friend iteration
	int32_t GetFriendCount(EFriendFlags iFriendFlags) = 0;
	CSteamID GetFriendByIndex(int32_t iFriend, EFriendFlags iFriendFlags) = 0;

	// gets the relationship to a user
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// steam registry, accessed by friend
	void SetFriendRegValue(CSteamID steamIDFriend, const char *pchKey, const char *pchValue) = 0;
	const char *GetFriendRegValue(CSteamID steamIDFriend, const char *pchKey) = 0;

	// returns true if the friend is actually in a game
	bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// adds a friend to the users list.  Friend will be notified that they have been added, and have the option of accept/decline
	bool AddFriend(CSteamID steamIDFriend) = 0;
	// removes the friend from the list, and blocks them from contacting the user again
	bool RemoveFriend(CSteamID steamIDFriend) = 0;

	// returns true if the specified user is considered a friend (can see our online status)
	bool HasFriend(CSteamID steamIDFriend, EFriendFlags iFriendFlags) = 0;

	// adds a friend by email address or account name - value returned in callback
	HSteamCall AddFriendByName(const char *pchEmailOrAccountName) = 0;

	bool InviteFriendByEmail(const char *emailAddr) = 0;

	// chat message iteration
	// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
	// returns 0 if the steamID or iChatID are invalid
	int32_t GetChatMessage(CSteamID steamIDFriend, int32_t iChatID, void *pvData, int32_t cubData, EChatEntryType *peFriendMsgType) = 0;

	// generic friend->friend message sending, takes a sized buffer
	bool SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const void *pvMsgBody, int32_t cubMsgBody) = 0;

	// returns the chatID that a chat should be resumed from when switching chat contexts
	OBSOLETE_FUNCTION int32_t GetChatIDOfChatHistoryStart(CSteamID steamIDFriend) = 0;
	// sets where a chat with a user should resume
	OBSOLETE_FUNCTION void SetChatHistoryStart(CSteamID steamIDFriend, int32_t iChatID) = 0;
	// clears the chat history - should be called when a chat dialog closes
	// the chat history can still be recovered by another context using SetChatHistoryStart() to reset the ChatIDOfChatHistoryStart
	void ClearChatHistory(CSteamID steamIDFriend) = 0;

	// clan functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;

	bool InviteFriendToClan(CSteamID steamIDfriend, CSteamID steamIDclan) = 0;
	bool AcknowledgeInviteToClan(CSteamID steamID, bool) = 0;

	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;
};
#pragma endregion

#pragma region SteamFriends003
class SteamFriends003 : public ISteamFriends003
{
public:
	// returns the local players name - guaranteed to not be NULL.
	const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;
	// gets the friend status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	int32_t GetFriendCount(EFriendFlags iFriendFlags) = 0;
	CSteamID GetFriendByIndex(int32_t iFriend, EFriendFlags iFriendFlags) = 0;

	// gets the relationship to a user
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;
	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetFriendAvatar(CSteamID steamIDFriend) = 0;
	// returns true if the friend is actually in a game
	bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user is considered a friend
	bool HasFriend(CSteamID steamIDFriend, EFriendFlags iFriendFlags) = 0;

	// clan functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;

	// iterators for any source
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open ("Friends", "Community", "Players", "Settings")
	void ActivateGameOverlay(const char *pchDialog) = 0;
};
#pragma endregion

#pragma region SteamFriends004
class SteamFriends004 : public ISteamFriends004
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32_t, iFriend, EFriendFlags, eFriendFlags) /*CSteamID GetFriendByIndex( int32_t iFriend, EFriendFlags eFriendFlags ) = 0;*/


		// returns a relationship to a user
		EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetFriendAvatar(CSteamID steamIDFriend, int32_t eAvatarSize) = 0;

	// returns true if the friend is actually in a game
	bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	void ActivateGameOverlay(const char *pchDialog) = 0;
};
#pragma endregion

#pragma region SteamFriends005
class SteamFriends005 : public ISteamFriends005
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32_t, iFriend, int32_t, iFriendFlags) /*CSteamID GetFriendByIndex( int32_t iFriend, int32_t iFriendFlags ) = 0;*/

		// returns a relationship to a user
		EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetFriendAvatar(CSteamID steamIDFriend, int32_t eAvatarSize) = 0;
	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;
};
#pragma endregion

#pragma region SteamFriends006
class SteamFriends006 : public ISteamFriends006
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32_t, iFriend, int32_t, iFriendFlags) /*CSteamID GetFriendByIndex( int32_t iFriend, int32_t iFriendFlags ) = 0;*/

		// returns a relationship to a user
		EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetFriendAvatar(CSteamID steamIDFriend, int32_t eAvatarSize) = 0;
	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;
};
#pragma endregion

#pragma region SteamFriends007
class SteamFriends007 : public ISteamFriends007
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32_t, iFriend, int32_t, iFriendFlags) /*CSteamID GetFriendByIndex( int32_t iFriend, int32_t iFriendFlags ) = 0;*/

		// returns a relationship to a user
		EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;
};
#pragma endregion

#pragma region SteamFriends008
class SteamFriends008 : public ISteamFriends008
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32_t, iFriend, int32_t, iFriendFlags) /*CSteamID GetFriendByIndex( int32_t iFriend, int32_t iFriendFlags ) = 0;*/

		// returns a relationship to a user
		EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	// returns the number of officers in a clan (including the owner)
	int32_t GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer) = 0;
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	EUserRestriction GetUserRestrictions() = 0;
};
#pragma endregion

#pragma region SteamFriends009
class SteamFriends009 : public ISteamFriends009
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(int32_t iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32_t, iFriend, int32_t, iFriendFlags) /*CSteamID GetFriendByIndex( int32_t iFriend, int32_t iFriendFlags ) = 0;*/

		// returns a relationship to a user
		EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	// returns the number of officers in a clan (including the owner)
	int32_t GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer) = 0;
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	EUserRestriction GetUserRestrictions() = 0;

	// Rich Presence data is automatically shared between friends who are in the same game
	// Each user has a set of Key/Value pairs
	// Up to 20 different keys can be set
	// There are two magic keys:
	//		"status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
	//		"connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
	// GetFriendRichPresence() returns an empty string "" if no value is set
	// SetRichPresence() to a NULL or an empty string deletes the key
	// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
	// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
	bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	void ClearRichPresence() = 0;
	const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	int32_t GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	int32_t GetCoplayFriendCount() = 0;
	CSteamID GetCoplayFriend(int32_t iCoplayFriend) = 0;
	int32_t GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;
};
#pragma endregion

#pragma region SteamFriends010
class SteamFriends010 : public ISteamFriends010
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(int32_t iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int32_t, iFriend, int32_t, iFriendFlags) /*CSteamID GetFriendByIndex( int32_t iFriend, int32_t iFriendFlags ) = 0;*/

		// returns a relationship to a user
		EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	bool GetClanActivityCounts(CSteamID steamID, int32_t *pnOnline, int32_t *pnInGame, int32_t *pnChatting) = 0;
	SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int32_t nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	// returns the number of officers in a clan (including the owner)
	int32_t GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer) = 0;
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	EUserRestriction GetUserRestrictions() = 0;

	// Rich Presence data is automatically shared between friends who are in the same game
	// Each user has a set of Key/Value pairs
	// Up to 20 different keys can be set
	// There are two magic keys:
	//		"status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
	//		"connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
	// GetFriendRichPresence() returns an empty string "" if no value is set
	// SetRichPresence() to a NULL or an empty string deletes the key
	// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
	// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
	bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	void ClearRichPresence() = 0;
	const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	int32_t GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	int32_t GetCoplayFriendCount() = 0;
	CSteamID GetCoplayFriend(int32_t iCoplayFriend) = 0;
	int32_t GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;


	SteamAPICall_t JoinClanChatRoom(CSteamID groupID) = 0;
	bool LeaveClanChatRoom(CSteamID groupID) = 0;
	int32_t GetClanChatMemberCount(CSteamID groupID) = 0;
	CSteamID GetChatMemberByIndex(CSteamID groupID, int32_t iIndex) = 0;
	bool SendClanChatMessage(CSteamID groupID, const char *cszMessage) = 0;
	int32_t GetClanChatMessage(CSteamID groupID, int32_t iChatID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	bool IsClanChatAdmin(CSteamID groupID, CSteamID userID) = 0;
	bool IsClanChatWindowOpenInSteam(CSteamID groupID) = 0;
	bool OpenClanChatWindowInSteam(CSteamID groupID) = 0;
	bool CloseClanChatWindowInSteam(CSteamID groupID) = 0;
	bool SetListenForFriendsMessages(bool bListen) = 0;
	bool ReplyToFriendMessage(CSteamID friendID, const char *cszMessage) = 0;
	int32_t GetFriendMessage(CSteamID friendID, int32_t iChatID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType) = 0;
};
#pragma endregion

#pragma region SteamFriends011
class SteamFriends011 : public ISteamFriends011
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(int32_t iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	CSteamID GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags) = 0;

	// returns a relationship to a user
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	bool GetClanActivityCounts(CSteamID steamID, int32_t *pnOnline, int32_t *pnInGame, int32_t *pnChatting) = 0;
	SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int32_t nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	// returns the number of officers in a clan (including the owner)
	int32_t GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer) = 0;
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	EUserRestriction GetUserRestrictions() = 0;

	// Rich Presence data is automatically shared between friends who are in the same game
	// Each user has a set of Key/Value pairs
	// Up to 20 different keys can be set
	// There are two magic keys:
	//		"status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
	//		"connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
	// GetFriendRichPresence() returns an empty string "" if no value is set
	// SetRichPresence() to a NULL or an empty string deletes the key
	// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
	// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
	bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	void ClearRichPresence() = 0;
	const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	int32_t GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey) = 0;
	void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	int32_t GetCoplayFriendCount() = 0;
	CSteamID GetCoplayFriend(int32_t iCoplayFriend) = 0;
	int32_t GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	int32_t GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	CSteamID GetChatMemberByIndex(CSteamID steamIDClan, int32_t iUser) = 0;
	bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	int32_t GetClanChatMessage(CSteamID steamIDClanChat, int32_t iMessage, void *prgchText, int32_t cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	int32_t GetFriendMessage(CSteamID steamIDFriend, int32_t iMessageID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
};
#pragma endregion

#pragma region SteamFriends012
class SteamFriends012 : public ISteamFriends012
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	SteamAPICall_t SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(int32_t iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	CSteamID GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags) = 0;

	// returns a relationship to a user
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	bool GetClanActivityCounts(CSteamID steamID, int32_t *pnOnline, int32_t *pnInGame, int32_t *pnChatting) = 0;
	SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int32_t nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	// returns the number of officers in a clan (including the owner)
	int32_t GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer) = 0;
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	EUserRestriction GetUserRestrictions() = 0;

	// Rich Presence data is automatically shared between friends who are in the same game
	// Each user has a set of Key/Value pairs
	// Up to 20 different keys can be set
	// There are two magic keys:
	//		"status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
	//		"connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
	// GetFriendRichPresence() returns an empty string "" if no value is set
	// SetRichPresence() to a NULL or an empty string deletes the key
	// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
	// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
	bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	void ClearRichPresence() = 0;
	const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	int32_t GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey) = 0;
	void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	int32_t GetCoplayFriendCount() = 0;
	CSteamID GetCoplayFriend(int32_t iCoplayFriend) = 0;
	int32_t GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	int32_t GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	CSteamID GetChatMemberByIndex(CSteamID steamIDClan, int32_t iUser) = 0;
	bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	int32_t GetClanChatMessage(CSteamID steamIDClanChat, int32_t iMessage, void *prgchText, int32_t cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	int32_t GetFriendMessage(CSteamID steamIDFriend, int32_t iMessageID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
};
#pragma endregion

#pragma region SteamFriends013
class SteamFriends013 : public ISteamFriends013
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	SteamAPICall_t SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(int32_t iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	CSteamID GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags) = 0;

	// returns a relationship to a user
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	bool GetClanActivityCounts(CSteamID steamID, int32_t *pnOnline, int32_t *pnInGame, int32_t *pnChatting) = 0;
	SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int32_t nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	// returns the number of officers in a clan (including the owner)
	int32_t GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer) = 0;
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	EUserRestriction GetUserRestrictions() = 0;

	// Rich Presence data is automatically shared between friends who are in the same game
	// Each user has a set of Key/Value pairs
	// Up to 20 different keys can be set
	// There are two magic keys:
	//		"status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
	//		"connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
	// GetFriendRichPresence() returns an empty string "" if no value is set
	// SetRichPresence() to a NULL or an empty string deletes the key
	// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
	// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
	bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	void ClearRichPresence() = 0;
	const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	int32_t GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey) = 0;
	void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	int32_t GetCoplayFriendCount() = 0;
	CSteamID GetCoplayFriend(int32_t iCoplayFriend) = 0;
	int32_t GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	int32_t GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	CSteamID GetChatMemberByIndex(CSteamID steamIDClan, int32_t iUser) = 0;
	bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	int32_t GetClanChatMessage(CSteamID steamIDClanChat, int32_t iMessage, void *prgchText, int32_t cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	int32_t GetFriendMessage(CSteamID steamIDFriend, int32_t iMessageID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
};
#pragma endregion

#pragma region SteamFriends014
class SteamFriends014 : public ISteamFriends014
{
public:
	// returns the local players name - guaranteed to not be NULL.
	// this is the same name as on the users community profile page
	// this is stored in UTF-8 format
	// like all the other interface functions that return a char *, it's important that this pointer is not saved
	// off; it will eventually be free'd or re-allocated
	const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	SteamAPICall_t SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	int32_t GetFriendCount(int32_t iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	CSteamID GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags) = 0;

	// returns a relationship to a user
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName) = 0;

	const char *GetPlayerNickname(CSteamID steamIDPlayer) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	bool HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags) = 0;

	// clan (group) iteration and access functions
	int32_t GetClanCount() = 0;
	CSteamID GetClanByIndex(int32_t iClan) = 0;
	const char *GetClanName(CSteamID steamIDClan) = 0;
	const char *GetClanTag(CSteamID steamIDClan) = 0;

	bool GetClanActivityCounts(CSteamID steamID, int32_t *pnOnline, int32_t *pnInGame, int32_t *pnChatting) = 0;
	SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int32_t nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	int32_t GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	CSteamID GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend) = 0;

	// returns true if the local user can see that steamIDUser is a member or in steamIDSource
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	void ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	CSteamID GetClanOwner(CSteamID steamIDClan) = 0;
	// returns the number of officers in a clan (including the owner)
	int32_t GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	CSteamID GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer) = 0;
	// if current user is chat restricted, he can't send or receive any text/voice chat messages.
	// the user can't see custom avatars. But the user can be online and send/recv game invites.
	// a chat restricted user can't add friends or join any groups.
	EUserRestriction GetUserRestrictions() = 0;

	// Rich Presence data is automatically shared between friends who are in the same game
	// Each user has a set of Key/Value pairs
	// Up to 20 different keys can be set
	// There are two magic keys:
	//		"status"  - a UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list
	//		"connect" - a UTF-8 string that contains the command-line for how a friend can connect to a game
	// GetFriendRichPresence() returns an empty string "" if no value is set
	// SetRichPresence() to a NULL or an empty string deletes the key
	// You can iterate the current set of keys for a friend with GetFriendRichPresenceKeyCount()
	// and GetFriendRichPresenceKeyByIndex() (typically only used for debugging)
	bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	void ClearRichPresence() = 0;
	const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	int32_t GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey) = 0;
	void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	int32_t GetCoplayFriendCount() = 0;
	CSteamID GetCoplayFriend(int32_t iCoplayFriend) = 0;
	int32_t GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	int32_t GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	CSteamID GetChatMemberByIndex(CSteamID steamIDClan, int32_t iUser) = 0;
	bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	int32_t GetClanChatMessage(CSteamID steamIDClanChat, int32_t iMessage, void *prgchText, int32_t cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	int32_t GetFriendMessage(CSteamID steamIDFriend, int32_t iMessageID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
};
#pragma endregion