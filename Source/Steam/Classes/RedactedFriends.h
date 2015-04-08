/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Friendslists.
*/

#pragma once

class RedactedFriends
{
public:
	const char *GetPersonaName();
	SteamAPICall_t SetPersonaName(const char *pchPersonaName);
	EPersonaState GetPersonaState();

	int32_t GetFriendCount(int32_t iFriendFlags);
	CSteamID GetFriendByIndex( int32_t iFriend, int32_t iFriendFlags );
	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend);

	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend);
	const char *GetFriendPersonaName(CSteamID steamIDFriend);

	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo);
	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName);
	const char *GetPlayerNickname(CSteamID steamIDPlayer);
	bool HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags);

	int32_t GetClanCount();
	CSteamID GetClanByIndex( int32_t iClan );
	const char *GetClanName(CSteamID steamIDClan);
	const char *GetClanTag(CSteamID steamIDClan);

	bool GetClanActivityCounts(CSteamID steamID, int32_t *pnOnline, int32_t *pnInGame, int32_t *pnChatting);
	SteamAPICall_t DownloadClanActivityCounts(CSteamID groupIDs[], int32_t nIds);

	int32_t GetFriendCountFromSource(CSteamID steamIDSource);
	CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int32_t iFriend );
	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource);

	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking);
	void ActivateGameOverlay(const char *pchDialog);
	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID);
	void ActivateGameOverlayToWebPage(const char *pchURL);
	void ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag);

	void SetPlayedWith(CSteamID steamIDUserPlayedWith);
	void ActivateGameOverlayInviteDialog(CSteamID steamIDLobby);


	int32_t GetSmallFriendAvatar(CSteamID steamIDFriend);
	int32_t GetMediumFriendAvatar(CSteamID steamIDFriend);
	int32_t GetLargeFriendAvatar(CSteamID steamIDFriend);

	bool RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly);
	SteamAPICall_t RequestClanOfficerList(CSteamID steamIDClan);
	CSteamID GetClanOwner( CSteamID steamIDClan );
	int32_t GetClanOfficerCount(CSteamID steamIDClan);
	CSteamID GetClanOfficerByIndex( CSteamID steamIDClan, int32_t iOfficer );
	EUserRestriction GetUserRestrictions();

	bool SetRichPresence(const char *pchKey, const char *pchValue);
	void ClearRichPresence();
	const char *GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey);
	int32_t GetFriendRichPresenceKeyCount(CSteamID steamIDFriend);
	const char *GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey);
	void RequestFriendRichPresence(CSteamID steamIDFriend);

	bool InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString);
	int32_t GetCoplayFriendCount();
	CSteamID GetCoplayFriend( int32_t iCoplayFriend );
	int32_t GetFriendCoplayTime(CSteamID steamIDFriend);
	AppId_t GetFriendCoplayGame(CSteamID steamIDFriend);

	SteamAPICall_t JoinClanChatRoom(CSteamID steamIDClan);
	bool LeaveClanChatRoom(CSteamID steamIDClan);
	int32_t GetClanChatMemberCount(CSteamID steamIDClan);
	CSteamID GetChatMemberByIndex( CSteamID steamIDClan, int32_t iUser );
	bool SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText);
	int32_t GetClanChatMessage(CSteamID steamIDClanChat, int32_t iMessage, void *prgchText, int32_t cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter);
	bool IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser);

	bool IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat);
	bool OpenClanChatWindowInSteam(CSteamID steamIDClanChat);
	bool CloseClanChatWindowInSteam(CSteamID steamIDClanChat);

	bool SetListenForFriendsMessages(bool bInterceptEnabled);
	bool ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend);
	int32_t GetFriendMessage(CSteamID steamIDFriend, int32_t iMessageID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType);

	SteamAPICall_t GetFollowerCount(CSteamID steamID);
	SteamAPICall_t IsFollowing(CSteamID steamID);
	SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex);
};
