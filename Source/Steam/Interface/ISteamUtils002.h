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

#ifndef ISTEAMUTILS002_H
#define ISTEAMUTILS002_H
#ifdef _WIN32
#pragma once
#endif

#include "..\Common\UtilsCommon.h"

//-----------------------------------------------------------------------------
// Purpose: interface to user independent utility functions
//-----------------------------------------------------------------------------
abstract_class ISteamUtils002
{
public:
	// return the number of seconds since the user 
	virtual uint32 GetSecondsSinceAppActive() = 0;
	virtual uint32 GetSecondsSinceComputerActive() = 0;

	// the universe this client is connecting to
	virtual EUniverse GetConnectedUniverse() = 0;

	// Steam server time - in PST, number of seconds since January 1, 1970 (i.e unix time)
	virtual uint32 GetServerRealTime() = 0;

	// returns the 2 digit ISO 3166-1-alpha-2 format country code this client is running in (as looked up via an IP-to-location database)
	// e.g "US" or "UK".
	virtual const char *GetIPCountry() = 0;

	// returns true if the image exists, and valid sizes were filled out
	virtual bool GetImageSize( int iImage, uint32 *pnWidth, uint32 *pnHeight ) = 0;

	// returns true if the image exists, and the buffer was successfully filled out
	// results are returned in RGBA format
	// the destination buffer size should be 4 * height * width * sizeof(char)
	virtual bool GetImageRGBA( int iImage, uint8 *pubDest, int nDestBufferSize ) = 0;

	// returns the IP of the reporting server for valve - currently only used in Source engine games
	virtual bool GetCSERIPPort( uint32 *unIP, uint16 *usPort ) = 0;

	// return the amount of battery power left in the current system in % [0..100], 255 for being on AC power
	virtual uint8 GetCurrentBatteryPower() = 0;
};


#endif // ISTEAMUTILS002_H
