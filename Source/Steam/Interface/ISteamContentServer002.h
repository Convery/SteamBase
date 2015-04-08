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

#ifndef ISTEAMCONTENTSERVER002_H
#define ISTEAMCONTENTSERVER002_H
#ifdef _WIN32
#pragma once
#endif

#include "..\Common\ContentServerCommon.h"

abstract_class ISteamContentServer002
{
public:
	virtual bool LogOn( uint32 uContentServerID ) = 0;
	virtual bool LogOff() = 0;

	virtual bool BLoggedOn() = 0;

	virtual void SendClientContentAuthRequest( CSteamID steamID, uint32 uContentID, uint64 ulSessionToken, bool bTokenPresent ) = 0;

	virtual bool BCheckTicket( CSteamID steamID, uint32 uContentID, const void *pvTicketData, uint32 cubTicketLength ) = 0;
};


#endif // ISTEAMCONTENTSERVER001_H
