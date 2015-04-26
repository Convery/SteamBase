/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		UserStats
*/

#include "..\..\StdInclude.h"

// Ask the server to send down this user's data and achievements for this game.
bool RedactedUserStats::RequestCurrentStats()
{
	PrintCurrentFunction();
	return true;
}

// Data accessors.
bool RedactedUserStats::GetStat(const char *pchName, int32 *pData)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedUserStats::GetStat(const char *pchName, float *pData)
{
	PrintCurrentFunction();
	return false;
}

// Set / update data.
bool RedactedUserStats::SetStat(const char *pchName, int32_t nData)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedUserStats::SetStat(const char *pchName, float fData)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedUserStats::UpdateAvgRateStat(const char *pchName, float flCountThisSession, double dSessionLength)
{
	PrintCurrentFunction();
	return false;
}

// Achievement flag accessors.
bool RedactedUserStats::GetAchievement(const char *pchName, bool *pbAchieved)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetAchievement, pchName, pbAchieved);
}
bool RedactedUserStats::SetAchievement(const char *pchName)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, SetAchievement, pchName);
}
bool RedactedUserStats::ClearAchievement(const char *pchName)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, ClearAchievement, pchName);
}

// Most likely a bool return here.
bool RedactedUserStats::GetAchievementAndUnlockTime(const char *pchName, bool *pbAchieved, uint32_t *prtTime)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetAchievementAndUnlockTime, pchName, pbAchieved, prtTime);
}

// Store the current data on the server.
bool RedactedUserStats::StoreStats()
{
	PrintCurrentFunction();
	return true;
}

// Gets the icon of the achievement, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set.
int32_t RedactedUserStats::GetAchievementIcon(const char *pchName)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetAchievementIcon, pchName);
}

// Get general attributes (display name / text, etc) for an Achievement.
const char *RedactedUserStats::GetAchievementDisplayAttribute(const char *pchName, const char *pchKey)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetAchievementDisplayAttribute, pchName, pchKey);
}

// Achievement progress - triggers an AchievementProgress callback, that is all.
// Calling this w/ N out of N progress will NOT set the achievement, the game must still do that.
bool RedactedUserStats::IndicateAchievementProgress(const char *pchName, uint32_t nCurProgress, uint32_t nMaxProgress)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, IndicateAchievementProgress, pchName, nCurProgress, nMaxProgress);
}

// Download stats for user X.
SteamAPICall_t RedactedUserStats::RequestUserStats(CSteamID steamIDUser)
{
	PrintCurrentFunction();
	return 0;
}

// Requests stat information for a user, usable after a successful call to RequestUserStats().
bool RedactedUserStats::GetUserStat(CSteamID steamIDUser, const char *pchName, int32_t *pData)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedUserStats::GetUserStat(CSteamID steamIDUser, const char *pchName, float *pData)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedUserStats::GetUserAchievement(CSteamID steamIDUser, const char *pchName, bool *pbAchieved)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetUserAchievement, steamIDUser, pchName, pbAchieved);
}
bool RedactedUserStats::GetUserAchievementAndUnlockTime(CSteamID steamIDUser, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetUserAchievementAndUnlockTime, steamIDUser, pchName, pbAchieved, punUnlockTime);
}

// Reset stats 
bool RedactedUserStats::ResetAllStats(bool bAchievementsToo)
{
	PrintCurrentFunction();
	return false;
}

// Asks the Steam back-end for a leaderboard by name, and will create it if it's not yet.
SteamAPICall_t RedactedUserStats::FindOrCreateLeaderboard(const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType)
{
	PrintCurrentFunction();
	return 0;
}

// Will create it if not found.
SteamAPICall_t RedactedUserStats::FindLeaderboard(const char *pchLeaderboardName)
{
	PrintCurrentFunction();
	return 0;
}

// Returns the name of a leaderboard.
const char *RedactedUserStats::GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard)
{
	PrintCurrentFunction();
	return "";
}

// Returns the total number of entries in a leaderboard, as of the last request.
int32_t RedactedUserStats::GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard)
{
	PrintCurrentFunction();
	return 0;
}

// Returns the sort method of the leaderboard.
ELeaderboardSortMethod RedactedUserStats::GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard)
{
	PrintCurrentFunction();
	return k_ELeaderboardSortMethodNone;
}

// Returns the display type of the leaderboard.
ELeaderboardDisplayType RedactedUserStats::GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard)
{
	PrintCurrentFunction();
	return k_ELeaderboardDisplayTypeNone;
}

// Asks the Steam back-end for a set of rows in the leaderboard.
SteamAPICall_t RedactedUserStats::DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd)
{
	PrintCurrentFunction();
	return 0;
}

// Capped at 100 users per call.
SteamAPICall_t RedactedUserStats::DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard, CSteamID *prgUsers, int cUsers)
{
	PrintCurrentFunction();
	return 0;
}

// Returns data about a single leaderboard entry, should be called ina loop.
bool RedactedUserStats::GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t *pLeaderboardEntry, int32 pDetails[], int cDetailsMax)
{
	PrintCurrentFunction();
	return 0;
}

// Uploads a user score to the Steam back-end.
SteamAPICall_t RedactedUserStats::UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32 *pScoreDetails, int cScoreDetailsCount)
{
	PrintCurrentFunction();
	return 0;
}

// Attaches a piece of user generated content the user's entry on a leaderboard.
SteamAPICall_t RedactedUserStats::AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
{
	PrintCurrentFunction();
	return 0;
}

// Retrieves the number of players currently playing the game (online + offline).
SteamAPICall_t RedactedUserStats::GetNumberOfCurrentPlayers()
{
	PrintCurrentFunction();
	return 0;
}

// Requests that Steam fetch data on the percentage of players who have received each achievement globally.
SteamAPICall_t RedactedUserStats::RequestGlobalAchievementPercentages()
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, RequestGlobalAchievementPercentages);
}

// Get the info on the most achieved achievement for the game.
int32_t RedactedUserStats::GetMostAchievedAchievementInfo(char *pchName, uint32_t unNameBufLen, float *pflPercent, bool *pbAchieved)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetMostAchievedAchievementInfo, pchName, unNameBufLen, pflPercent, pbAchieved);
}
int32_t RedactedUserStats::GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetNextMostAchievedAchievementInfo, iIteratorPrevious, pchName, unNameBufLen, pflPercent, pbAchieved);
}

// Returns the percentage of users who have achieved the specified achievement.
bool RedactedUserStats::GetAchievementAchievedPercent(const char *pchName, float *pflPercent)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetAchievementAchievedPercent, pchName, pflPercent);
}

// Requests global stats data, which is available for stats marked as "aggregated".
SteamAPICall_t RedactedUserStats::RequestGlobalStats(int32_t nHistoryDays)
{
	PrintCurrentFunction();
	return 0;
}

// Gets the lifetime totals for an aggregated stat.
bool RedactedUserStats::GetGlobalStat(const char *pchStatName, int64_t *pData)
{
	PrintCurrentFunction();
	return false;
}
bool RedactedUserStats::GetGlobalStat(const char *pchStatName, double *pData)
{
	PrintCurrentFunction();
	return false;
}

// Gets history for an aggregated stat. pData will be filled with daily values, starting with today.
int32_t RedactedUserStats::GetGlobalStatHistory(const char *pchStatName, int64_t *pData, uint32_t cubData)
{
	PrintCurrentFunction();
	return 0;
}
int32_t RedactedUserStats::GetGlobalStatHistory(const char *pchStatName, double *pData, uint32_t cubData)
{
	PrintCurrentFunction();
	return 0;
}

uint32_t RedactedUserStats::GetNumAchievements(CGameID nGameID)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetNumAchievements, nGameID);
}
const char* RedactedUserStats::GetAchievementName(uint32_t iAchievement)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUserStats, GetAchievementName, iAchievement);
}