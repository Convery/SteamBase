/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Friendslists.
*/

#include "..\..\StdInclude.h"

const char *RedactedFriends::GetPersonaName()
{
	//PrintCurrentFunction(); // Spams the console
	return Global::Steam_Username;
}
SteamAPICall_t RedactedFriends::SetPersonaName(const char *pchPersonaName)
{
	PrintCurrentFunction();
	return 0;
}
EPersonaState RedactedFriends::GetPersonaState()
{
	PrintCurrentFunction();
	return EPersonaState::k_EPersonaStateOnline;
}

int32_t RedactedFriends::GetFriendCount(int32_t iFriendFlags)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetFriendCount, iFriendFlags);
}
CSteamID RedactedFriends::GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags)
{
	//PrintCurrentFunction(); // Spams the console
	STEAMPROXY_CALL(ISteamFriends, GetFriendByIndex, iFriend, iFriendFlags);
}
EFriendRelationship RedactedFriends::GetFriendRelationship(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetFriendRelationship, steamIDFriend);
}

EPersonaState RedactedFriends::GetFriendPersonaState(CSteamID steamIDFriend)
{
	//PrintCurrentFunction(); // Spams the console
	STEAMPROXY_CALL(ISteamFriends, GetFriendPersonaState, steamIDFriend);
}
const char *RedactedFriends::GetFriendPersonaName(CSteamID steamIDFriend)
{
	//PrintCurrentFunction(); // Spams the console
	STEAMPROXY_CALL(ISteamFriends, GetFriendPersonaName, steamIDFriend);
}

bool RedactedFriends::GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo)
{
	//PrintCurrentFunction(); // Spams the console
	STEAMPROXY_CALL(ISteamFriends, GetFriendGamePlayed, steamIDFriend, pFriendGameInfo);
}
const char *RedactedFriends::GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetFriendPersonaNameHistory, steamIDFriend, iPersonaName);
}
const char *RedactedFriends::GetPlayerNickname(CSteamID steamIDPlayer)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetPlayerNickname, steamIDPlayer);
}
bool RedactedFriends::HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, HasFriend, steamIDFriend, iFriendFlags);
}

int32_t RedactedFriends::GetClanCount()
{
	PrintCurrentFunction();
	return 0;
}
CSteamID RedactedFriends::GetClanByIndex(int32_t iClan)
{
	PrintCurrentFunction();
	return CSteamID();
}
const char *RedactedFriends::GetClanName(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return "HHS";
}
const char *RedactedFriends::GetClanTag(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return "";
}

bool RedactedFriends::GetClanActivityCounts(CSteamID steamID, int32_t *pnOnline, int32_t *pnInGame, int32_t *pnChatting)
{
	PrintCurrentFunction();
	return false;
}
SteamAPICall_t RedactedFriends::DownloadClanActivityCounts(CSteamID groupIDs[], int32_t nIds)
{
	PrintCurrentFunction();
	return 0;
}

int32_t RedactedFriends::GetFriendCountFromSource(CSteamID steamIDSource)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetFriendCountFromSource, steamIDSource);
}
CSteamID RedactedFriends::GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetFriendFromSourceByIndex, steamIDSource, iFriend);
}
bool RedactedFriends::IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, IsUserInSource, steamIDUser, steamIDSource);
}

void RedactedFriends::SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking)
{
	PrintCurrentFunction();
}
void RedactedFriends::ActivateGameOverlay(const char *pchDialog)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, ActivateGameOverlay, pchDialog);
}
void RedactedFriends::ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, ActivateGameOverlayToUser, pchDialog, steamID);
}
void RedactedFriends::ActivateGameOverlayToWebPage(const char *pchURL)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, ActivateGameOverlayToWebPage, pchURL);
}
void RedactedFriends::ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, ActivateGameOverlayToStore, nAppID, eFlag);
}

void RedactedFriends::SetPlayedWith(CSteamID steamIDUserPlayedWith)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, SetPlayedWith, steamIDUserPlayedWith);
}
void RedactedFriends::ActivateGameOverlayInviteDialog(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, ActivateGameOverlayInviteDialog, steamIDLobby);
}

int32_t RedactedFriends::GetSmallFriendAvatar(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetSmallFriendAvatar, steamIDFriend);
}
int32_t RedactedFriends::GetMediumFriendAvatar(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetMediumFriendAvatar, steamIDFriend);
}
int32_t RedactedFriends::GetLargeFriendAvatar(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, GetLargeFriendAvatar, steamIDFriend);
}

bool RedactedFriends::RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, RequestUserInformation, steamIDUser, bRequireNameOnly);
}
SteamAPICall_t RedactedFriends::RequestClanOfficerList(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return 0;
}
CSteamID RedactedFriends::GetClanOwner(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return CSteamID();
}
int32_t RedactedFriends::GetClanOfficerCount(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return 0;
}
CSteamID RedactedFriends::GetClanOfficerByIndex(CSteamID steamIDClan, int32_t iOfficer)
{
	PrintCurrentFunction();
	return CSteamID();
}
EUserRestriction RedactedFriends::GetUserRestrictions()
{
	PrintCurrentFunction();
	return EUserRestriction::k_nUserRestrictionNone;
}

bool RedactedFriends::SetRichPresence(const char *pchKey, const char *pchValue)
{
	PrintCurrentFunction();
	return false;
}
void RedactedFriends::ClearRichPresence()
{
	PrintCurrentFunction();
}
const char *RedactedFriends::GetFriendRichPresence(CSteamID steamIDFriend, const char *pchKey)
{
	//PrintCurrentFunction();
	return "";
}
int32_t RedactedFriends::GetFriendRichPresenceKeyCount(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return 0;
}
const char *RedactedFriends::GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int32_t iKey)
{
	PrintCurrentFunction();
	return "";
}
void RedactedFriends::RequestFriendRichPresence(CSteamID steamIDFriend)
{
	//PrintCurrentFunction();
}

bool RedactedFriends::InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamFriends, InviteUserToGame, steamIDFriend, pchConnectString);
}
int32_t RedactedFriends::GetCoplayFriendCount()
{
	PrintCurrentFunction();
	return 0;
}
CSteamID RedactedFriends::GetCoplayFriend(int32_t iCoplayFriend)
{
	PrintCurrentFunction();
	return CSteamID();
}
int32_t RedactedFriends::GetFriendCoplayTime(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return 0;
}
AppId_t RedactedFriends::GetFriendCoplayGame(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return 0;
}

SteamAPICall_t RedactedFriends::JoinClanChatRoom(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return 0;
}
bool RedactedFriends::LeaveClanChatRoom(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return false;
}
int32_t RedactedFriends::GetClanChatMemberCount(CSteamID steamIDClan)
{
	PrintCurrentFunction();
	return 0;
}
CSteamID RedactedFriends::GetChatMemberByIndex(CSteamID steamIDClan, int32_t iUser)
{
	PrintCurrentFunction();
	return CSteamID();
}
bool RedactedFriends::SendClanChatMessage(CSteamID steamIDClanChat, const char *pchText)
{
	PrintCurrentFunction();
	return false;
}
int32_t RedactedFriends::GetClanChatMessage(CSteamID steamIDClanChat, int32_t iMessage, void *prgchText, int32_t cchTextMax, EChatEntryType *peChatEntryType, CSteamID *pSteamIDChatter)
{
	PrintCurrentFunction();
	return 0;
}
bool RedactedFriends::IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedFriends::IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedFriends::OpenClanChatWindowInSteam(CSteamID steamIDClanChat)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedFriends::CloseClanChatWindowInSteam(CSteamID steamIDClanChat)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedFriends::SetListenForFriendsMessages(bool bInterceptEnabled)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedFriends::ReplyToFriendMessage(CSteamID steamIDFriend, const char *pchMsgToSend)
{
	PrintCurrentFunction();
	return false;
}
int32_t RedactedFriends::GetFriendMessage(CSteamID steamIDFriend, int32_t iMessageID, void *pvData, int32_t cubData, EChatEntryType *peChatEntryType)
{
	PrintCurrentFunction();
	return 0;
}

SteamAPICall_t RedactedFriends::GetFollowerCount(CSteamID steamID)
{
	PrintCurrentFunction();
	return 0;
}
SteamAPICall_t RedactedFriends::IsFollowing(CSteamID steamID)
{
	PrintCurrentFunction();
	return 0;
}
SteamAPICall_t RedactedFriends::EnumerateFollowingList(uint32 unStartIndex)
{
	PrintCurrentFunction();
	return 0;
}
// Extra methods.
EPersonaState RedactedFriends::SetPersonaState(EPersonaState ePersonaState)
{
	PrintCurrentFunction();
	return ePersonaState;
}
bool RedactedFriends::AddFriend(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedFriends::RemoveFriend(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return false;
}
HSteamCall RedactedFriends::AddFriendByName(const char *pchEmailOrAccountName)
{
	PrintCurrentFunction();
	return 0;
}

int RedactedFriends::GetFriendSteamLevel(CSteamID steamIDFriend){
	PrintCurrentFunction();
	return 1;
}