/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
*/

#include "..\..\StdInclude.h"

#pragma region SteamUser001

#pragma endregion

#pragma region SteamUser002

#pragma endregion

#pragma region SteamUser003

#pragma endregion

#pragma region SteamUser004

#pragma endregion

#pragma region SteamUser005

#pragma endregion

#pragma region SteamUser006

#pragma endregion

#pragma region SteamUser007

#pragma endregion

#pragma region SteamUser008

#pragma endregion

#pragma region SteamUser009

#pragma endregion

#pragma region SteamUser010

#pragma endregion

#pragma region SteamUser011

#pragma endregion

#pragma region SteamUser012

#pragma endregion

#pragma region SteamUser013

#pragma endregion

#pragma region SteamUser014

#pragma endregion

#pragma region SteamUser015

#pragma endregion

#pragma region SteamUser016

// Returns the HSteamUser this interface represents.
HSteamUser SteamUser016::GetHSteamUser()
{
	return RedactedUser::GetHSteamUser();
}

// If we are connected to the backend.
bool SteamUser016::BLoggedOn()
{
	return RedactedUser::BLoggedOn();
}

// Returns the current XUID.
CSteamID SteamUser016::GetSteamID()
{
	return RedactedUser::GetSteamID();
}

// Multiplayer authentication.
int32_t SteamUser016::InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
	return RedactedUser::InitiateGameConnection(pAuthBlob, cbMaxAuthBlob, steamIDGameServer, unIPServer, usPortServer, bSecure);
}
void SteamUser016::TerminateGameConnection(uint32_t unIPServer, uint16_t usPortServer)
{
	return RedactedUser::TerminateGameConnection(unIPServer, usPortServer);
}

// #### Legacy functions ####

// Rarely used, ignore.
void SteamUser016::TrackAppUsageEvent(CGameID gameID, EAppUsageEvent eAppUsageEvent, const char *pchExtraInfo)
{
	return RedactedUser::TrackAppUsageEvent(gameID, eAppUsageEvent, pchExtraInfo);
}

// Get storage relative to stem, like "C:\Progam Files\Steam\userdata\<SteamID>\<AppID>\local"
bool SteamUser016::GetUserDataFolder(char *pchBuffer, int32_t cubBuffer)
{
	return RedactedUser::GetUserDataFolder(pchBuffer, cubBuffer);
}

// Starts voice recording. Once started, use GetCompressedVoice() to get the data.
void SteamUser016::StartVoiceRecording()
{
	return RedactedUser::StartVoiceRecording();
}

// Stops voice recording. Because people often release push-to-talk keys early, the system will keep recording for a sec.
void SteamUser016::StopVoiceRecording()
{
	return RedactedUser::StopVoiceRecording();
}

// Determine the amount of captured audio data that is available in bytes.
EVoiceResult SteamUser016::GetAvailableVoice(uint32 *pcbCompressed, uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
{
	return RedactedUser::GetAvailableVoice(pcbCompressed, pcbUncompressed, nUncompressedVoiceDesiredSampleRate);
}

// Gets the latest voice data from the microphone.
EVoiceResult SteamUser016::GetVoice(bool bWantCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
{
	return RedactedUser::GetVoice(bWantCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, bWantUncompressed, pUncompressedDestBuffer, cbUncompressedDestBufferSize, nUncompressBytesWritten, nUncompressedVoiceDesiredSampleRate);
}

// Decompresses a chunk of compressed data produced by GetVoice().
EVoiceResult SteamUser016::DecompressVoice(const void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate)
{
	return RedactedUser::DecompressVoice(pCompressed, cbCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, nDesiredSampleRate);
}

// This returns the frequency of the voice data as it's stored internally; calling DecompressVoice() with this size will yield the best results.
uint32_t SteamUser016::GetVoiceOptimalSampleRate()
{
	return RedactedUser::GetVoiceOptimalSampleRate();
}

// Retrieve ticket to be sent to the entity who wishes to authenticate you. 
uint32_t SteamUser016::GetAuthSessionTicket(void *pTicket, int32_t cbMaxTicket, uint32_t *pcbTicket)
{
	return RedactedUser::GetAuthSessionTicket(pTicket, cbMaxTicket, pcbTicket);
}

// Authenticate ticket from entity steamID to be sure it is valid and isnt reused.
EBeginAuthSessionResult SteamUser016::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	return RedactedUser::BeginAuthSession(pAuthTicket, cbAuthTicket, steamID);
}

// Stop tracking started by BeginAuthSession - called when no longer playing game with this entity.
void SteamUser016::EndAuthSession(CSteamID steamID)
{
	return RedactedUser::EndAuthSession(steamID);
}

// Cancel auth ticket from GetAuthSessionTicket, called when no longer playing game with the entity you gave the ticket to.
void SteamUser016::CancelAuthTicket(HAuthTicket hAuthTicket)
{
	return RedactedUser::CancelAuthTicket(hAuthTicket);
}

// After receiving a user's authentication data, and passing it to BeginAuthSession, use this function
// to determine if the user owns downloadable content specified by the provided AppID.
EUserHasLicenseForAppResult SteamUser016::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	return RedactedUser::UserHasLicenseForApp(steamID, appID);
}

// Misc.
bool SteamUser016::BIsBehindNAT()
{
	return RedactedUser::BIsBehindNAT();
}
void SteamUser016::AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
{
	return RedactedUser::AdvertiseGame(steamIDGameServer, unIPServer, usPortServer);
}

SteamAPICall_t SteamUser016::RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude)
{
	return RedactedUser::RequestEncryptedAppTicket(pDataToInclude, cbDataToInclude);
}
bool SteamUser016::GetEncryptedAppTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	return RedactedUser::GetEncryptedAppTicket(pTicket, cbMaxTicket, pcbTicket);
}

#pragma endregion

#pragma region SteamUser017

#pragma endregion

#pragma region SteamUser018

HSteamUser SteamUser018::GetHSteamUser()
{
	return RedactedUser::GetHSteamUser();
}

// If we are connected to the backend.
bool SteamUser018::BLoggedOn()
{
	return RedactedUser::BLoggedOn();
}

// Returns the current XUID.
CSteamID SteamUser018::GetSteamID()
{
	return RedactedUser::GetSteamID();
}

// Multiplayer authentication.
int32_t SteamUser018::InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
	return RedactedUser::InitiateGameConnection(pAuthBlob, cbMaxAuthBlob, steamIDGameServer, unIPServer, usPortServer, bSecure);
}
void SteamUser018::TerminateGameConnection(uint32_t unIPServer, uint16_t usPortServer)
{
	return RedactedUser::TerminateGameConnection(unIPServer, usPortServer);
}

// #### Legacy functions ####

// Rarely used, ignore.
void SteamUser018::TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo)
{
	return RedactedUser::TrackAppUsageEvent(gameID, EAppUsageEvent(eAppUsageEvent), pchExtraInfo);
}

// Get storage relative to stem, like "C:\Progam Files\Steam\userdata\<SteamID>\<AppID>\local"
bool SteamUser018::GetUserDataFolder(char *pchBuffer, int32_t cubBuffer)
{
	return RedactedUser::GetUserDataFolder(pchBuffer, cubBuffer);
}

// Starts voice recording. Once started, use GetCompressedVoice() to get the data.
void SteamUser018::StartVoiceRecording()
{
	return RedactedUser::StartVoiceRecording();
}

// Stops voice recording. Because people often release push-to-talk keys early, the system will keep recording for a sec.
void SteamUser018::StopVoiceRecording()
{
	return RedactedUser::StopVoiceRecording();
}

// Determine the amount of captured audio data that is available in bytes.
EVoiceResult SteamUser018::GetAvailableVoice(uint32 *pcbCompressed, uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
{
	return RedactedUser::GetAvailableVoice(pcbCompressed, pcbUncompressed, nUncompressedVoiceDesiredSampleRate);
}

// Gets the latest voice data from the microphone.
EVoiceResult SteamUser018::GetVoice(bool bWantCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
{
	return RedactedUser::GetVoice(bWantCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, bWantUncompressed, pUncompressedDestBuffer, cbUncompressedDestBufferSize, nUncompressBytesWritten, nUncompressedVoiceDesiredSampleRate);
}

// Decompresses a chunk of compressed data produced by GetVoice().
EVoiceResult SteamUser018::DecompressVoice(const void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate)
{
	return RedactedUser::DecompressVoice(pCompressed, cbCompressed, pDestBuffer, cbDestBufferSize, nBytesWritten, nDesiredSampleRate);
}

// This returns the frequency of the voice data as it's stored internally; calling DecompressVoice() with this size will yield the best results.
uint32_t SteamUser018::GetVoiceOptimalSampleRate()
{
	return RedactedUser::GetVoiceOptimalSampleRate();
}

// Retrieve ticket to be sent to the entity who wishes to authenticate you. 
uint32_t SteamUser018::GetAuthSessionTicket(void *pTicket, int32_t cbMaxTicket, uint32_t *pcbTicket)
{
	return RedactedUser::GetAuthSessionTicket(pTicket, cbMaxTicket, pcbTicket);
}

// Authenticate ticket from entity steamID to be sure it is valid and isnt reused.
EBeginAuthSessionResult SteamUser018::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	return RedactedUser::BeginAuthSession(pAuthTicket, cbAuthTicket, steamID);
}

// Stop tracking started by BeginAuthSession - called when no longer playing game with this entity.
void SteamUser018::EndAuthSession(CSteamID steamID)
{
	return RedactedUser::EndAuthSession(steamID);
}

// Cancel auth ticket from GetAuthSessionTicket, called when no longer playing game with the entity you gave the ticket to.
void SteamUser018::CancelAuthTicket(HAuthTicket hAuthTicket)
{
	return RedactedUser::CancelAuthTicket(hAuthTicket);
}

// After receiving a user's authentication data, and passing it to BeginAuthSession, use this function
// to determine if the user owns downloadable content specified by the provided AppID.
EUserHasLicenseForAppResult SteamUser018::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	return RedactedUser::UserHasLicenseForApp(steamID, appID);
}

// Misc.
bool SteamUser018::BIsBehindNAT()
{
	return RedactedUser::BIsBehindNAT();
}
void SteamUser018::AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
{
	return RedactedUser::AdvertiseGame(steamIDGameServer, unIPServer, usPortServer);
}

SteamAPICall_t SteamUser018::RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude)
{
	return RedactedUser::RequestEncryptedAppTicket(pDataToInclude, cbDataToInclude);
}
bool SteamUser018::GetEncryptedAppTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
{
	return RedactedUser::GetEncryptedAppTicket(pTicket, cbMaxTicket, pcbTicket);
}

int SteamUser018::GetGameBadgeLevel(int nSeries, bool bFoil){
	//not implemented for now
	return 1;
}
int SteamUser018::GetPlayerSteamLevel(){
	//not implemented for now
	return 1;
}
SteamAPICall_t SteamUser018::RequestStoreAuthURL(const char *pchRedirectURL){
	//not implemented for now
	return 0;
}

#pragma endregion