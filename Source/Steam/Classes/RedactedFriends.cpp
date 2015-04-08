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
	PrintCurrentFunction();
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
	return 0;
}
CSteamID RedactedFriends::GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags)
{
	PrintCurrentFunction();
	return CSteamID();
}
EFriendRelationship RedactedFriends::GetFriendRelationship(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return EFriendRelationship::k_EFriendRelationshipNone;
}

EPersonaState RedactedFriends::GetFriendPersonaState(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return EPersonaState::k_EPersonaStateOffline;
}
const char *RedactedFriends::GetFriendPersonaName(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return "";
}

bool RedactedFriends::GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo)
{
	PrintCurrentFunction();
	return false;
}
const char *RedactedFriends::GetFriendPersonaNameHistory(CSteamID steamIDFriend, int32_t iPersonaName)
{
	PrintCurrentFunction();
	return "";
}
const char *RedactedFriends::GetPlayerNickname(CSteamID steamIDPlayer)
{
	PrintCurrentFunction();
	return "";
}
bool RedactedFriends::HasFriend(CSteamID steamIDFriend, int32_t iFriendFlags)
{
	PrintCurrentFunction();
	return false;
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
	return 0;
}
CSteamID RedactedFriends::GetFriendFromSourceByIndex(CSteamID steamIDSource, int32_t iFriend)
{
	PrintCurrentFunction();
	return CSteamID();
}
bool RedactedFriends::IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource)
{
	PrintCurrentFunction();
	return false;
}

void RedactedFriends::SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking)
{
	PrintCurrentFunction();
}
void RedactedFriends::ActivateGameOverlay(const char *pchDialog)
{
	PrintCurrentFunction();
}
void RedactedFriends::ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID)
{
	PrintCurrentFunction();
}
void RedactedFriends::ActivateGameOverlayToWebPage(const char *pchURL)
{
	PrintCurrentFunction();
}
void RedactedFriends::ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag)
{
	PrintCurrentFunction();
}

void RedactedFriends::SetPlayedWith(CSteamID steamIDUserPlayedWith)
{
	PrintCurrentFunction();
}
void RedactedFriends::ActivateGameOverlayInviteDialog(CSteamID steamIDLobby)
{
	PrintCurrentFunction();
}

int32_t RedactedFriends::GetSmallFriendAvatar(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return 0;
}
int32_t RedactedFriends::GetMediumFriendAvatar(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return 0;
}
int32_t RedactedFriends::GetLargeFriendAvatar(CSteamID steamIDFriend)
{
	PrintCurrentFunction();
	return 0;
}

bool RedactedFriends::RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly)
{
	PrintCurrentFunction();
	return false;
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
	PrintCurrentFunction();
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
	PrintCurrentFunction();
}

bool RedactedFriends::InviteUserToGame(CSteamID steamIDFriend, const char *pchConnectString)
{
	PrintCurrentFunction();
	return false;
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
