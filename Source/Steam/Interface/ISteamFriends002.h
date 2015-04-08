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

#ifndef ISTEAMFRIENDS002_H
#define ISTEAMFRIENDS002_H
#ifdef _WIN32
#pragma once
#endif

#include "..\Common\FriendsCommon.h"

abstract_class ISteamFriends002
{
public:
	// returns the local players name - guaranteed to not be NULL.
	virtual const char *GetPersonaName() = 0;
	// sets the player name, stores it on the server and publishes the changes to all friends who are online
	virtual void SetPersonaName( const char *pchPersonaName ) = 0;
	// gets the friend status of the current user
	virtual EPersonaState GetPersonaState() = 0;
	// sets the status, communicates to server, tells all friends
	virtual void SetPersonaState( EPersonaState ePersonaState ) = 0;

	// friend iteration
	virtual int GetFriendCount( EFriendFlags iFriendFlags ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendByIndex, int, iFriend, EFriendFlags, iFriendFlags) /*virtual CSteamID GetFriendByIndex( int iFriend, EFriendFlags iFriendFlags ) = 0;*/

	// gets the relationship to a user
	virtual EFriendRelationship GetFriendRelationship( CSteamID steamIDFriend ) = 0;
	// returns true if the specified user is considered a friend (can see our online status)
	virtual EPersonaState GetFriendPersonaState( CSteamID steamIDFriend ) = 0;
	// returns the name of a friend - guaranteed to not be NULL.
	virtual const char *GetFriendPersonaName( CSteamID steamIDFriend ) = 0;

	// steam registry, accessed by friend
	virtual void SetFriendRegValue( CSteamID steamIDFriend, const char *pchKey, const char *pchValue ) = 0;
	virtual const char *GetFriendRegValue( CSteamID steamIDFriend, const char *pchKey ) = 0;

	// returns true if the friend is actually in a game
	virtual bool GetFriendGamePlayed( CSteamID steamIDFriend, uint64 *pulGameID, uint32 *punGameIP, uint16 *pusGamePort, uint16 *pusQueryPort ) = 0;
	
	// accesses old friends names - returns an empty string when their are no more items in the history
	virtual const char *GetFriendPersonaNameHistory( CSteamID steamIDFriend, int iPersonaName ) = 0;

	// adds a friend to the users list.  Friend will be notified that they have been added, and have the option of accept/decline
	virtual bool AddFriend( CSteamID steamIDFriend ) = 0;
	// removes the friend from the list, and blocks them from contacting the user again
	virtual bool RemoveFriend( CSteamID steamIDFriend ) = 0;

	// returns true if the specified user is considered a friend (can see our online status)
	virtual bool HasFriend( CSteamID steamIDFriend, EFriendFlags iFriendFlags ) = 0;

	// adds a friend by email address or account name - value returned in callback
	virtual HSteamCall AddFriendByName( const char *pchEmailOrAccountName ) = 0;

	virtual bool InviteFriendByEmail( const char *emailAddr ) = 0;

	// chat message iteration
	// returns the number of bytes in the message, filling pvData with as many of those bytes as possible
	// returns 0 if the steamID or iChatID are invalid
	virtual int GetChatMessage( CSteamID steamIDFriend, int iChatID, void *pvData, int cubData, EChatEntryType *peFriendMsgType ) = 0;

	// generic friend->friend message sending, takes a sized buffer
	virtual bool SendMsgToFriend( CSteamID steamIDFriend, EChatEntryType eFriendMsgType, const void *pvMsgBody, int cubMsgBody ) = 0;

	// returns the chatID that a chat should be resumed from when switching chat contexts
	virtual OBSOLETE_FUNCTION int GetChatIDOfChatHistoryStart( CSteamID steamIDFriend ) = 0;
	// sets where a chat with a user should resume
	virtual OBSOLETE_FUNCTION void SetChatHistoryStart( CSteamID steamIDFriend, int iChatID ) = 0;
	// clears the chat history - should be called when a chat dialog closes
	// the chat history can still be recovered by another context using SetChatHistoryStart() to reset the ChatIDOfChatHistoryStart
	virtual void ClearChatHistory( CSteamID steamIDFriend ) = 0;

	// clan functions
	virtual int GetClanCount() = 0;
	STEAMWORKS_STRUCT_RETURN_1(CSteamID, GetClanByIndex, int, iClan) /*virtual CSteamID GetClanByIndex( int iClan ) = 0;*/
	virtual const char *GetClanName( CSteamID steamIDClan ) = 0;

	virtual bool InviteFriendToClan( CSteamID steamIDfriend, CSteamID steamIDclan ) = 0;
	virtual bool AcknowledgeInviteToClan( CSteamID steamID, bool ) = 0;

	virtual int GetFriendCountFromSource( CSteamID steamIDSource ) = 0;
	STEAMWORKS_STRUCT_RETURN_2(CSteamID, GetFriendFromSourceByIndex, CSteamID, steamIDSource, int, iFriend) /*virtual CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend ) = 0;*/
};

#endif // ISTEAMFRIENDS002_H
