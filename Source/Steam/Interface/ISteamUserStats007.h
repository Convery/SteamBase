//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef ISTEAMUSERSTATS007_H
#define ISTEAMUSERSTATS007_H
#ifdef _WIN32
#pragma once
#endif

#include "..\Common\UserStatsCommon.h"

//-----------------------------------------------------------------------------
// Purpose: Functions for accessing stats, achievements, and leaderboard information
//-----------------------------------------------------------------------------
abstract_class ISteamUserStats007
{
public:
	// Ask the server to send down this user's data and achievements for this game
	virtual bool RequestCurrentStats() = 0;

	// Data accessors
#if !(defined(_WIN32) && defined(__GNUC__))
	virtual bool GetStat( const char *pchName, int32 *pData ) = 0;
	virtual bool GetStat( const char *pchName, float *pData ) = 0;
#else
	virtual bool GetStat( const char *pchName, float *pData ) = 0;
	virtual bool GetStat( const char *pchName, int32 *pData ) = 0;	
#endif

	// Set / update data
#if !(defined(_WIN32) && defined(__GNUC__))
	virtual bool SetStat( const char *pchName, int32 nData ) = 0;
	virtual bool SetStat( const char *pchName, float fData ) = 0;
#else
	virtual bool SetStat( const char *pchName, float fData ) = 0;
	virtual bool SetStat( const char *pchName, int32 nData ) = 0;
#endif
	virtual bool UpdateAvgRateStat( const char *pchName, float flCountThisSession, double dSessionLength ) = 0;

	// Achievement flag accessors
	virtual bool GetAchievement( const char *pchName, bool *pbAchieved ) = 0;
	virtual bool SetAchievement( const char *pchName ) = 0;
	virtual bool ClearAchievement( const char *pchName ) = 0;

	// most likely a bool return here
	virtual bool GetAchievementAndUnlockTime( const char *pchName, bool *pbAchieved, RTime32 *prtTime ) = 0;

	// Store the current data on the server, will get a callback when set
	// And one callback for every new achievement
	virtual bool StoreStats() = 0;

	// Gets the icon of the achievement, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetAchievementIcon( const char *pchName ) = 0;
	// Get general attributes (display name / text, etc) for an Achievement
	virtual const char *GetAchievementDisplayAttribute( const char *pchName, const char *pchKey ) = 0;

	// Achievement progress - triggers an AchievementProgress callback, that is all.
	// Calling this w/ N out of N progress will NOT set the achievement, the game must still do that.
	virtual bool IndicateAchievementProgress( const char *pchName, uint32 nCurProgress, uint32 nMaxProgress ) = 0;

	// Friends stats & achievements

	// downloads stats for the user
	// returns a UserStatsReceived_t received when completed
	// if the other user has no stats, UserStatsReceived_t.m_eResult will be set to k_EResultFail
	// these stats won't be auto-updated; you'll need to call RequestUserStats() again to refresh any data
	virtual SteamAPICall_t RequestUserStats( CSteamID steamIDUser ) = 0;


	// requests stat information for a user, usable after a successful call to RequestUserStats()
#if !(defined(_WIN32) && defined(__GNUC__))
	virtual bool GetUserStat( CSteamID steamIDUser, const char *pchName, int32 *pData ) = 0;
	virtual bool GetUserStat( CSteamID steamIDUser, const char *pchName, float *pData ) = 0;
#else
	virtual bool GetUserStat( CSteamID steamIDUser, const char *pchName, float *pData ) = 0;
	virtual bool GetUserStat( CSteamID steamIDUser, const char *pchName, int32 *pData ) = 0;
#endif
	virtual bool GetUserAchievement( CSteamID steamIDUser, const char *pchName, bool *pbAchieved ) = 0;
	virtual bool GetUserAchievementAndUnlockTime( CSteamID steamIDUser, const char *pchName, bool *pbAchieved, RTime32 *prtTime ) = 0;

	// Reset stats 
	virtual bool ResetAllStats( bool bAchievementsToo ) = 0;


	// Leaderboard functions

	// asks the Steam back-end for a leaderboard by name, and will create it if it's not yet
	// This call is asynchronous, with the result returned in LeaderboardFindResult_t
	virtual SteamAPICall_t FindOrCreateLeaderboard( const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType ) = 0;

	// as above, but won't create the leaderboard if it's not found
	// This call is asynchronous, with the result returned in LeaderboardFindResult_t
	virtual SteamAPICall_t FindLeaderboard( const char *pchLeaderboardName ) = 0;


	// returns the name of a leaderboard
	virtual const char *GetLeaderboardName( SteamLeaderboard_t hSteamLeaderboard ) = 0;

	// returns the total number of entries in a leaderboard, as of the last request
	virtual int GetLeaderboardEntryCount( SteamLeaderboard_t hSteamLeaderboard ) = 0;

	// returns the sort method of the leaderboard
	virtual ELeaderboardSortMethod GetLeaderboardSortMethod( SteamLeaderboard_t hSteamLeaderboard ) = 0;

	// returns the display type of the leaderboard
	virtual ELeaderboardDisplayType GetLeaderboardDisplayType( SteamLeaderboard_t hSteamLeaderboard ) = 0;

	// Asks the Steam back-end for a set of rows in the leaderboard.
	// This call is asynchronous, with the result returned in LeaderboardScoresDownloaded_t
	// LeaderboardScoresDownloaded_t will contain a handle to pull the results from GetDownloadedLeaderboardEntries() (below)
	// You can ask for more entries than exist, and it will return as many as do exist.
	// k_ELeaderboardDataRequestGlobal requests rows in the leaderboard from the full table, with nRangeStart & nRangeEnd in the range [1, TotalEntries]
	// k_ELeaderboardDataRequestGlobalAroundUser requests rows around the current user, nRangeStart being negate
	//   e.g. DownloadLeaderboardEntries( hLeaderboard, k_ELeaderboardDataRequestGlobalAroundUser, -3, 3 ) will return 7 rows, 3 before the user, 3 after
	// k_ELeaderboardDataRequestFriends requests all the rows for friends of the current user 
	virtual SteamAPICall_t DownloadLeaderboardEntries( SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd ) = 0;

	// Returns data about a single leaderboard entry
	// use a for loop from 0 to LeaderboardScoresDownloaded_t::m_cEntryCount to get all the downloaded entries
	// e.g.
	//		void OnLeaderboardScoresDownloaded( LeaderboardScoresDownloaded_t *pLeaderboardScoresDownloaded )
	//		{
	//			for ( int index = 0; index < pLeaderboardScoresDownloaded->m_cEntryCount; index++ )
	//			{
	//				LeaderboardEntry_t leaderboardEntry;
	//				int32 details[3];		// we know this is how many we've stored previously
	//				GetDownloadedLeaderboardEntry( pLeaderboardScoresDownloaded->m_hSteamLeaderboardEntries, index, &leaderboardEntry, details, 3 );
	//				assert( leaderboardEntry.m_cDetails == 3 );
	//				...
	//			}
	// once you've accessed all the entries, the data will be free'd, and the SteamLeaderboardEntries_t handle will become invalid
	virtual bool GetDownloadedLeaderboardEntry( SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry001_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax ) = 0;

	// Uploads a user score to the Steam back-end.
	// This call is asynchronous, with the result returned in LeaderboardScoreUploaded_t
	// If the score passed in is no better than the existing score this user has in the leaderboard, then the leaderboard will not be updated.
	// Details are extra game-defined information regarding how the user got that score
	// pScoreDetails points to an array of int32's, cScoreDetailsCount is the number of int32's in the list
	virtual SteamAPICall_t UploadLeaderboardScore( SteamLeaderboard_t hSteamLeaderboard,ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, int32 *pScoreDetails, int cScoreDetailsCount ) = 0;

	// Retrieves the number of players currently playing your game (online + offline)
	// This call is asynchronous, with the result returned in NumberOfCurrentPlayers_t
	virtual SteamAPICall_t GetNumberOfCurrentPlayers() = 0;
};

#endif // ISTEAMUSERSTATS007_H
