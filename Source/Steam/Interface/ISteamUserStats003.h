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

#ifndef ISTEAMUSERSTATS003_H
#define ISTEAMUSERSTATS003_H
#ifdef _WIN32
#pragma once
#endif

#include "..\Common\UserStatsCommon.h"


abstract_class ISteamUserStats003
{
public:

	// Ask the server to send down this user's data and achievements for nGameID
	virtual bool RequestCurrentStats( ) = 0;

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
	virtual bool UpdateAvgRateStat( const char *pchName, float, double dSessionLength ) = 0;


	// Achievement flag accessors
	virtual bool GetAchievement( const char *pchName, bool *pbAchieved ) = 0;
	virtual bool SetAchievement( const char *pchName ) = 0;
	virtual bool ClearAchievement( const char *pchName ) = 0;

	// Store the current data on the server, will get a callback when set
	// And one callback for every new achievement
	virtual bool StoreStats( ) = 0;

	// Gets the icon of the achievement, which is a handle to be used in IClientUtils::GetImageRGBA(), or 0 if none set
	virtual int GetAchievementIcon( const char *pchName ) = 0;
	// Get general attributes (display name / text, etc) for an Achievement
	virtual const char *GetAchievementDisplayAttribute( const char *pchName, const char *pchKey ) = 0;

	// Achievement progress - triggers an AchievementProgress callback, that is all.
	// Calling this w/ N out of N progress will NOT set the achievement, the game must still do that.
	virtual bool IndicateAchievementProgress( const char *pchName, uint32 nCurProgress, uint32 nMaxProgress ) = 0;

};

#endif // ISTEAMUSERSTATS003_H
