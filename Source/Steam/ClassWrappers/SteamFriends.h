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
	virtual const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the friend status of the current user
	virtual EPersonaState GetPersonaState() = 0;
	// sets the status, communicates to server, tells all friends
	virtual void SetPersonaState(EPersonaState ePersonaState) = 0;

	// adds a friend to the users list.  Friend will be notified that they have been added, and have the option of accept/decline
	virtual bool AddFriend(CSteamID steamIDFriend) = 0;
	// removes the friend from the list, and blocks them from contacting the user again
	virtual bool RemoveFriend(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual bool HasFriend(CSteamID steamIDFriend) = 0;

	// gets the relationship to a user
	virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// retrieves details about the game the friend is currently playing - returns false if the friend is not playing any games
	// this is deprecated, please use the GetFriendGamePlayed# functions below
	virtual bool Deprecated_GetFriendGamePlayed(CSteamID steamIDFriend, int32 *pnGameID, uint32 *punGameIP, uint16 *pusGamePort) = 0;

	// returns the name of a friend - guaranteed to not be NULL.
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// adds a friend by email address or account name - value returned in callback
	virtual HSteamCall AddFriendByName(const char *pchEmailOrAccountName) = 0;

	// friend iteration
	virtual int GetFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetFriendByIndex, int, iFriend) /*virtual CSteamID GetFriendByIndex( int iFriend ) = 0;*/

		// generic friend->friend message sending
		// DEPRECATED, use the sized-buffer version instead (has much higher max buffer size)
		virtual void SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const char *pchMsgBody) = 0;

	// steam registry, accessed by friend
	virtual void SetFriendRegValue(CSteamID steamIDFriend, const char *pchKey, const char *pchValue) = 0;
	virtual const char *GetFriendRegValue(CSteamID steamIDFriend, const char *pchKey) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// chat message iteration
	// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
	// returns 0 if the steamID or iChatID are invalid
	virtual int GetChatMessage(CSteamID steamIDFriend, int iChatID, void *pvData, int cubData, EChatEntryType *peFriendMsgType) = 0;

	// generic friend->friend message sending, takes a sized buffer
	virtual bool SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const void *pvMsgBody, int cubMsgBody) = 0;

	// returns the chatID that a chat should be resumed from when switching chat contexts
	virtual OBSOLETE_FUNCTION int GetChatIDOfChatHistoryStart(CSteamID steamIDFriend) = 0;
	// sets where a chat with a user should resume
	virtual OBSOLETE_FUNCTION void SetChatHistoryStart(CSteamID steamIDFriend, int iChatID) = 0;
	// clears the chat history - should be called when a chat dialog closes
	// the chat history can still be recovered by another context using SetChatHistoryStart() to reset the ChatIDOfChatHistoryStart
	virtual void ClearChatHistory(CSteamID steamIDFriend) = 0;

	virtual HSteamCall InviteFriendByEmail(const char *pchEmailOrAccountName) = 0;

	virtual uint32 GetBlockedFriendCount() = 0;

	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort) = 0;
	virtual bool GetFriendGamePlayed2(CSteamID steamDIFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;
};
#pragma endregion

#pragma region SteamFriends002
class SteamFriends002 : public ISteamFriends002
{
public:
	// returns the local players name - guaranteed to not be NULL.
	virtual const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;
	// gets the friend status of the current user
	virtual EPersonaState GetPersonaState() = 0;
	// sets the status, communicates to server, tells all friends
	virtual void SetPersonaState(EPersonaState ePersonaState) = 0;

	// friend iteration
	virtual int GetFriendCount(EFriendFlags iFriendFlags) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, EFriendFlags, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, EFriendFlags iFriendFlags ) = 0;*/

		// gets the relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// steam registry, accessed by friend
	virtual void SetFriendRegValue(CSteamID steamIDFriend, const char *pchKey, const char *pchValue) = 0;
	virtual const char *GetFriendRegValue(CSteamID steamIDFriend, const char *pchKey) = 0;

	// returns true if the friend is actually in a game
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// adds a friend to the users list.  Friend will be notified that they have been added, and have the option of accept/decline
	virtual bool AddFriend(CSteamID steamIDFriend) = 0;
	// removes the friend from the list, and blocks them from contacting the user again
	virtual bool RemoveFriend(CSteamID steamIDFriend) = 0;

	// returns true if the specified user is considered a friend (can see our online status)
	virtual bool HasFriend(CSteamID steamIDFriend, EFriendFlags iFriendFlags) = 0;

	// adds a friend by email address or account name - value returned in callback
	virtual HSteamCall AddFriendByName(const char *pchEmailOrAccountName) = 0;

	virtual bool InviteFriendByEmail(const char *emailAddr) = 0;

	// chat message iteration
	// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
	// returns 0 if the steamID or iChatID are invalid
	virtual int GetChatMessage(CSteamID steamIDFriend, int iChatID, void *pvData, int cubData, EChatEntryType *peFriendMsgType) = 0;

	// generic friend->friend message sending, takes a sized buffer
	virtual bool SendMsgToFriend(CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const void *pvMsgBody, int cubMsgBody) = 0;

	// returns the chatID that a chat should be resumed from when switching chat contexts
	virtual OBSOLETE_FUNCTION int GetChatIDOfChatHistoryStart(CSteamID steamIDFriend) = 0;
	// sets where a chat with a user should resume
	virtual OBSOLETE_FUNCTION void SetChatHistoryStart(CSteamID steamIDFriend, int iChatID) = 0;
	// clears the chat history - should be called when a chat dialog closes
	// the chat history can still be recovered by another context using SetChatHistoryStart() to reset the ChatIDOfChatHistoryStart
	virtual void ClearChatHistory(CSteamID steamIDFriend) = 0;

	// clan functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;

	virtual bool InviteFriendToClan(CSteamID steamIDfriend, CSteamID steamIDclan) = 0;
	virtual bool AcknowledgeInviteToClan(CSteamID steamID, bool) = 0;

	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/
};
#pragma endregion

#pragma region SteamFriends003
class SteamFriends003 : public ISteamFriends003
{
public:
	// returns the local players name - guaranteed to not be NULL.
	virtual const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;
	// gets the friend status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	virtual int GetFriendCount(EFriendFlags iFriendFlags) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, EFriendFlags, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, EFriendFlags iFriendFlags ) = 0;*/

		// gets the relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;
	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetFriendAvatar(CSteamID steamIDFriend) = 0;
	// returns true if the friend is actually in a game
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user is considered a friend
	virtual bool HasFriend(CSteamID steamIDFriend, EFriendFlags iFriendFlags) = 0;

	// clan functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;

	// iterators for any source
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open ("Friends", "Community", "Players", "Settings")
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, EFriendFlags, eFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, EFriendFlags eFriendFlags ) = 0;*/


		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetFriendAvatar(CSteamID steamIDFriend, int eAvatarSize) = 0;

	// returns true if the friend is actually in a game
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort) = 0;

	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetFriendAvatar(CSteamID steamIDFriend, int eAvatarSize) = 0;
	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetFriendAvatar(CSteamID steamIDFriend, int eAvatarSize) = 0;
	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(EFriendFlags eFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		// returns the number of officers in a clan (including the owner)
		virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int iOfficer ) = 0;*/
		// if current user is chat restricted, he can't send or receive any text/voice chat messages.
		// the user can't see custom avatars. But the user can be online and send/recv game invites.
		// a chat restricted user can't add friends or join any groups.
		virtual EUserRestriction GetUserRestrictions() = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(int iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, int iFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		// returns the number of officers in a clan (including the owner)
		virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int iOfficer ) = 0;*/
		// if current user is chat restricted, he can't send or receive any text/voice chat messages.
		// the user can't see custom avatars. But the user can be online and send/recv game invites.
		// a chat restricted user can't add friends or join any groups.
		virtual EUserRestriction GetUserRestrictions() = 0;

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
	virtual bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	virtual void ClearRichPresence() = 0;
	virtual const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	virtual int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	virtual bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	virtual int GetCoplayFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetCoplayFriend, int, iCoplayFriend) /*virtual CSteamID GetCoplayFriend( int iCoplayFriend ) = 0;*/
		virtual int GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	virtual AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(int iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, int iFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	virtual bool GetClanActivityCounts(CSteamID steamID, int *pnOnline, int *pnInGame, int *pnChatting) = 0;
	virtual SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		// returns the number of officers in a clan (including the owner)
		virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int iOfficer ) = 0;*/
		// if current user is chat restricted, he can't send or receive any text/voice chat messages.
		// the user can't see custom avatars. But the user can be online and send/recv game invites.
		// a chat restricted user can't add friends or join any groups.
		virtual EUserRestriction GetUserRestrictions() = 0;

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
	virtual bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	virtual void ClearRichPresence() = 0;
	virtual const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	virtual int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	virtual bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	virtual int GetCoplayFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetCoplayFriend, int, iCoplayFriend) /*virtual CSteamID GetCoplayFriend( int iCoplayFriend ) = 0;*/
		virtual int GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	virtual AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;


	virtual SteamAPICall_t JoinClanChatRoom(CSteamID groupID) = 0;
	virtual bool LeaveClanChatRoom(CSteamID groupID) = 0;
	virtual int GetClanChatMemberCount(CSteamID groupID) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetChatMemberByIndex, CSteamID, groupID, int, iIndex) /*virtual CSteamID GetChatMemberByIndex( CSteamID groupID, int iIndex ) = 0;*/
		virtual bool SendClanChatMessage(CSteamID groupID, const char *cszMessage) = 0;
	virtual int GetClanChatMessage(CSteamID groupID, int iChatID, void *pvData, int cubData, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	virtual bool IsClanChatAdmin(CSteamID groupID, CSteamID userID) = 0;
	virtual bool IsClanChatWindowOpenInSteam(CSteamID groupID) = 0;
	virtual bool OpenClanChatWindowInSteam(CSteamID groupID) = 0;
	virtual bool CloseClanChatWindowInSteam(CSteamID groupID) = 0;
	virtual bool SetListenForFriendsMessages(bool bListen) = 0;
	virtual bool ReplyToFriendMessage(CSteamID friendID, const char *cszMessage) = 0;
	virtual int GetFriendMessage(CSteamID friendID, int iChatID, void *pvData, int cubData, EChatEntryType *peChatEntryType) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(int iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, int iFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	virtual bool GetClanActivityCounts(CSteamID steamID, int *pnOnline, int *pnInGame, int *pnChatting) = 0;
	virtual SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		// returns the number of officers in a clan (including the owner)
		virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int iOfficer ) = 0;*/
		// if current user is chat restricted, he can't send or receive any text/voice chat messages.
		// the user can't see custom avatars. But the user can be online and send/recv game invites.
		// a chat restricted user can't add friends or join any groups.
		virtual EUserRestriction GetUserRestrictions() = 0;

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
	virtual bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	virtual void ClearRichPresence() = 0;
	virtual const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	virtual int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) = 0;
	virtual void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	virtual bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	virtual int GetCoplayFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetCoplayFriend, int, iCoplayFriend) /*virtual CSteamID GetCoplayFriend( int iCoplayFriend ) = 0;*/
		virtual int GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	virtual AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	virtual SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	virtual bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	virtual int GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetChatMemberByIndex, CSteamID, steamIDClan, int, iUser) /*virtual CSteamID GetChatMemberByIndex( CSteamID steamIDClan, int iUser ) = 0;*/
		virtual bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	virtual int GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	virtual bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	virtual bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	virtual bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	virtual bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	virtual int GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	virtual SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	virtual SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	virtual SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual SteamAPICall_t SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(int iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, int iFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	virtual bool GetClanActivityCounts(CSteamID steamID, int *pnOnline, int *pnInGame, int *pnChatting) = 0;
	virtual SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		// returns the number of officers in a clan (including the owner)
		virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int iOfficer ) = 0;*/
		// if current user is chat restricted, he can't send or receive any text/voice chat messages.
		// the user can't see custom avatars. But the user can be online and send/recv game invites.
		// a chat restricted user can't add friends or join any groups.
		virtual EUserRestriction GetUserRestrictions() = 0;

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
	virtual bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	virtual void ClearRichPresence() = 0;
	virtual const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	virtual int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) = 0;
	virtual void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	virtual bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	virtual int GetCoplayFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetCoplayFriend, int, iCoplayFriend) /*virtual CSteamID GetCoplayFriend( int iCoplayFriend ) = 0;*/
		virtual int GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	virtual AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	virtual SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	virtual bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	virtual int GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetChatMemberByIndex, CSteamID, steamIDClan, int, iUser) /*virtual CSteamID GetChatMemberByIndex( CSteamID steamIDClan, int iUser ) = 0;*/
		virtual bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	virtual int GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	virtual bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	virtual bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	virtual bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	virtual bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	virtual int GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	virtual SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	virtual SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	virtual SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual SteamAPICall_t SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(int iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, int iFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	virtual bool GetClanActivityCounts(CSteamID steamID, int *pnOnline, int *pnInGame, int *pnChatting) = 0;
	virtual SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		// returns the number of officers in a clan (including the owner)
		virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int iOfficer ) = 0;*/
		// if current user is chat restricted, he can't send or receive any text/voice chat messages.
		// the user can't see custom avatars. But the user can be online and send/recv game invites.
		// a chat restricted user can't add friends or join any groups.
		virtual EUserRestriction GetUserRestrictions() = 0;

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
	virtual bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	virtual void ClearRichPresence() = 0;
	virtual const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	virtual int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) = 0;
	virtual void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	virtual bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	virtual int GetCoplayFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetCoplayFriend, int, iCoplayFriend) /*virtual CSteamID GetCoplayFriend( int iCoplayFriend ) = 0;*/
		virtual int GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	virtual AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	virtual SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	virtual bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	virtual int GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetChatMemberByIndex, CSteamID, steamIDClan, int, iUser) /*virtual CSteamID GetChatMemberByIndex( CSteamID steamIDClan, int iUser ) = 0;*/
		virtual bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	virtual int GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	virtual bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	virtual bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	virtual bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	virtual bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	virtual int GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	virtual SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	virtual SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	virtual SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
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
	virtual const char *GetPersonaName() = 0;

	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual SteamAPICall_t SetPersonaName(const char *pchPersonaName) = 0;

	// gets the status of the current user
	virtual EPersonaState GetPersonaState() = 0;

	// friend iteration
	// takes a set of k_EFriendFlags, and returns the number of users the client knows about who meet that criteria
	// then GetFriendByIndex() can then be used to return the id's of each of those users
	virtual int GetFriendCount(int iFriendFlags) = 0;

	// returns the steamID of a user
	// iFriend is a index of range [0, GetFriendCount())
	// iFriendsFlags must be the same value as used in GetFriendCount()
	// the returned CSteamID can then be used by all the functions below to access details about the user
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, int, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, int iFriendFlags ) = 0;*/

		// returns a relationship to a user
		virtual EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend) = 0;

	// returns the current status of the specified user
	// this will only be known by the local user if steamIDFriend is in their friends list; on the same game server; in a chat room or lobby; or in a small group with the local user
	virtual EPersonaState GetFriendPersonaState(CSteamID steamIDFriend) = 0;

	// returns the name another user - guaranteed to not be NULL.
	// same rules as GetFriendPersonaState() apply as to whether or not the user knowns the name of the other user
	// note that on first joining a lobby, chat room or game server the local user will not known the name of the other users automatically; that information will arrive asyncronously
	// 
	virtual const char *GetFriendPersonaName(CSteamID steamIDFriend) = 0;

	// returns true if the friend is actually in a game, and fills in pFriendGameInfo with an extra details 
	virtual bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo) = 0;
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) = 0;

	virtual const char *GetPlayerNickname(CSteamID steamIDPlayer) = 0;

	// returns true if the specified user meets any of the criteria specified in iFriendFlags
	// iFriendFlags can be the union (binary or, |) of one or more k_EFriendFlags values
	virtual bool HasFriend(CSteamID steamIDFriend, int iFriendFlags) = 0;

	// clan (group) iteration and access functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
		virtual const char *GetClanName(CSteamID steamIDClan) = 0;
	virtual const char *GetClanTag(CSteamID steamIDClan) = 0;

	virtual bool GetClanActivityCounts(CSteamID steamID, int *pnOnline, int *pnInGame, int *pnChatting) = 0;
	virtual SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int nIds) = 0;

	// iterators for getting users in a chat room, lobby, game server or clan
	// note that large clans that cannot be iterated by the local user
	// steamIDSource can be the steamID of a group, game server, lobby or chat room
	virtual int GetFriendCountFromSource(CSteamID steamIDSource) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/

		// returns true if the local user can see that steamIDUser is a member or in steamIDSource
		virtual bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) = 0;

	// User is in a game pressing the talk button (will suppress the microphone for all voice comms from the Steam friends UI)
	virtual void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) = 0;

	// activates the game overlay, with an optional dialog to open 
	// valid options are "Friends", "Community", "Players", "Settings", "LobbyInvite", "OfficialGameGroup", "Stats", "Achievements"
	virtual void ActivateGameOverlay(const char *pchDialog) = 0;

	// activates game overlay to a specific place
	// valid options are
	//		"steamid" - opens the overlay web browser to the specified user or groups profile
	//		"chat" - opens a chat window to the specified user, or joins the group chat 
	//		"stats" - opens the overlay web browser to the specified user's stats
	//		"achievements" - opens the overlay web browser to the specified user's achievements
	virtual void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID) = 0;

	// activates game overlay web browser directly to the specified URL
	// full address with protocol type is required, e.g. http://www.steamgames.com/
	virtual void ActivateGameOverlayToWebPage(const char *pchURL) = 0;

	// activates game overlay to store page for app
	virtual void ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag) = 0;

	// Mark a target user as 'played with'. This is a client-side only feature that requires that the calling user is 
	// in game 
	virtual void SetPlayedWith(CSteamID steamIDUserPlayedWith) = 0;

	// activates game overlay to open the invite dialog. Invitations will be sent for the provided lobby.
	// You can also use ActivateGameOverlay( "LobbyInvite" ) to allow the user to create invitations for their current public lobby.
	virtual void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) = 0;

	// gets the small (32x32) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetSmallFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the medium (64x64) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetMediumFriendAvatar(CSteamID steamIDFriend) = 0;

	// gets the large (184x184) avatar of the current user, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	// returns -1 if this image has yet to be loaded, in this case wait for a AvatarImageLoaded_t callback and then call this again
	virtual int GetLargeFriendAvatar(CSteamID steamIDFriend) = 0;

	// requests information about a user - persona name & avatar
	// if bRequireNameOnly is set, then the avatar of a user isn't downloaded 
	// - it's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them
	// if returns true, it means that data is being requested, and a PersonaStateChanged_t callback will be posted when it's retrieved
	// if returns false, it means that we already have all the details about that user, and functions can be called immediately
	virtual bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) = 0;

	// requests information about a clan officer list
	// when complete, data is returned in ClanOfficerListResponse_t call result
	// this makes available the calls below
	// you can only ask about clans that a user is a member of
	// note that this won't download avatars automatically; if you get an officer,
	// and no avatar image is available, call RequestUserInformation( steamID, false ) to download the avatar
	virtual SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan) = 0;

	// iteration of clan officers - can only be done when a RequestClanOfficerList() call has completed

	// returns the steamID of the clan owner
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanOwner, CSteamID, steamIDClan) /*virtual CSteamID GetClanOwner( CSteamID steamIDClan ) = 0;*/
		// returns the number of officers in a clan (including the owner)
		virtual int GetClanOfficerCount(CSteamID steamIDClan) = 0;
	// returns the steamID of a clan officer, by index, of range [0,GetClanOfficerCount)
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetClanOfficerByIndex, CSteamID, steamIDClan, int, iOfficer) /*virtual CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int iOfficer ) = 0;*/
		// if current user is chat restricted, he can't send or receive any text/voice chat messages.
		// the user can't see custom avatars. But the user can be online and send/recv game invites.
		// a chat restricted user can't add friends or join any groups.
		virtual EUserRestriction GetUserRestrictions() = 0;

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
	virtual bool SetRichPresence(const char *pchKey, const char *pchValue) = 0;
	virtual void ClearRichPresence() = 0;
	virtual const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey) = 0;
	virtual int GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) = 0;
	virtual const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) = 0;
	virtual void RequestFriendRichPresence(CSteamID steamIDFriend) = 0;

	// rich invite support
	// if the target accepts the invite, the pchConnectString gets added to the command-line for launching the game
	// if the game is already running, a GameRichPresenceJoinRequested_t callback is posted containing the connect string
	// invites can only be sent to friends
	virtual bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString) = 0;

	// recently-played-with friends iteration
	// this iterates the entire list of users recently played with, across games
	// GetFriendCoplayTime() returns as a unix time
	virtual int GetCoplayFriendCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetCoplayFriend, int, iCoplayFriend) /*virtual CSteamID GetCoplayFriend( int iCoplayFriend ) = 0;*/
		virtual int GetFriendCoplayTime(CSteamID steamIDFriend) = 0;
	virtual AppId_t GetFriendCoplayGame(CSteamID steamIDFriend) = 0;

	// chat interface for games
	// this allows in-game access to group (clan) chats from in the game
	// the behavior is somewhat sophisticated, because the user may or may not be already in the group chat from outside the game or in the overlay
	// use ActivateGameOverlayToUser( "chat", steamIDClan ) to open the in-game overlay version of the chat
	virtual SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan) = 0;
	virtual bool LeaveClanChatRoom(CSteamID steamIDClan) = 0;
	virtual int GetClanChatMemberCount(CSteamID steamIDClan) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetChatMemberByIndex, CSteamID, steamIDClan, int, iUser) /*virtual CSteamID GetChatMemberByIndex( CSteamID steamIDClan, int iUser ) = 0;*/
		virtual bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText) = 0;
	virtual int GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter) = 0;
	virtual bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) = 0;

	// interact with the Steam (game overlay / desktop)
	virtual bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;
	virtual bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat) = 0;

	// peer-to-peer chat interception
	// this is so you can show P2P chats inline in the game
	virtual bool SetListenForFriendsMessages(bool bInterceptEnabled) = 0;
	virtual bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend) = 0;
	virtual int GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType) = 0;

	// following apis
	virtual SteamAPICall_t GetFollowerCount(CSteamID steamID) = 0;
	virtual SteamAPICall_t IsFollowing(CSteamID steamID) = 0;
	virtual SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex) = 0;
};
#pragma endregion