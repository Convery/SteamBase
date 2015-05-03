/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		Users.
*/

#include "..\..\StdInclude.h"

// Returns the HSteamUser this interface represents.
HSteamUser RedactedUser::GetHSteamUser()
{
	PrintCurrentFunction();
	return NULL;
}

// If we are connected to the backend.
bool RedactedUser::BLoggedOn()
{
	return true;
}

// Returns the current XUID.
CSteamID RedactedUser::GetSteamID()
{
	if (!Global::Steam_UserID)
	{
		Global::Steam_UserID = 0x1100001DEADC0DE;
	}

	return CSteamID(Global::Steam_UserID);
}

// Multiplayer authentication.
int RedactedUser::InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
	PrintCurrentFunction();

	// Offline auth server.
	if (steamIDGameServer.ConvertToUint64() == 0xDEADC0DE)
	{
		memcpy(pAuthBlob, "Legit auth", 11);
		return 11;
	}

	return cbMaxAuthBlob;
}
void RedactedUser::TerminateGameConnection(uint32_t unIPServer, uint16_t usPortServer)
{
	PrintCurrentFunction();
}

// #### Legacy functions ####

// Rarely used, ignore.
void RedactedUser::TrackAppUsageEvent(CGameID gameID, EAppUsageEvent eAppUsageEvent, const char *pchExtraInfo)
{
	PrintCurrentFunction();
}

// Get storage relative to stem, like "C:\Progam Files\Steam\userdata\<SteamID>\<AppID>\local"
bool RedactedUser::GetUserDataFolder(char *pchBuffer, int cubBuffer)
{
	PrintCurrentFunction();
	return true;
}

// Starts voice recording. Once started, use GetCompressedVoice() to get the data.
void RedactedUser::StartVoiceRecording()
{
	PrintCurrentFunction();
}

// Stops voice recording. Because people often release push-to-talk keys early, the system will keep recording for a sec.
void RedactedUser::StopVoiceRecording()
{
	PrintCurrentFunction();
}

// Determine the amount of captured audio data that is available in bytes.
EVoiceResult RedactedUser::GetAvailableVoice(uint32_t *pcbCompressed, uint32_t *pcbUncompressed, uint32_t nUncompressedVoiceDesiredSampleRate)
{
	PrintCurrentFunction();
	return k_EVoiceResultOK;
}

// Gets the latest voice data from the microphone.
EVoiceResult RedactedUser::GetVoice(bool bWantCompressed, void *pDestBuffer, uint32_t cbDestBufferSize, uint32_t *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32_t cbUncompressedDestBufferSize, uint32_t *nUncompressBytesWritten, uint32_t nUncompressedVoiceDesiredSampleRate)
{
	PrintCurrentFunction();
	return k_EVoiceResultOK;
}

// Decompresses a chunk of compressed data produced by GetVoice().
EVoiceResult RedactedUser::DecompressVoice(const void *pCompressed, uint32_t cbCompressed, void *pDestBuffer, uint32_t cbDestBufferSize, uint32_t *nBytesWritten, uint32_t nDesiredSampleRate)
{
	PrintCurrentFunction();
	return k_EVoiceResultOK;
}

// This returns the frequency of the voice data as it's stored internally; calling DecompressVoice() with this size will yield the best results.
uint32_t RedactedUser::GetVoiceOptimalSampleRate()
{
	PrintCurrentFunction();
	return 44100;
}

// Retrieve ticket to be sent to the entity who wishes to authenticate you. 
uint32_t RedactedUser::GetAuthSessionTicket(void *pTicket, int32_t cbMaxTicket, uint32_t *pcbTicket)
{
	PrintCurrentFunction();
	return 0;
}

// Authenticate ticket from entity steamID to be sure it is valid and isnt reused.
EBeginAuthSessionResult RedactedUser::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	PrintCurrentFunction();
	return k_EBeginAuthSessionResultOK;
}

// Stop tracking started by BeginAuthSession - called when no longer playing game with this entity.
void RedactedUser::EndAuthSession(CSteamID steamID)
{
	PrintCurrentFunction();
}

// Cancel auth ticket from GetAuthSessionTicket, called when no longer playing game with the entity you gave the ticket to.
void RedactedUser::CancelAuthTicket(uint32_t hAuthTicket)
{
	PrintCurrentFunction();
}

// After receiving a user's authentication data, and passing it to BeginAuthSession, use this function
// to determine if the user owns downloadable content specified by the provided AppID.
EUserHasLicenseForAppResult RedactedUser::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	PrintCurrentFunction();
	return k_EUserHasLicenseResultHasLicense;
}

// Misc.
bool RedactedUser::BIsBehindNAT()
{
	PrintCurrentFunction();
	return false; // TODO: Actually check.
}
void RedactedUser::AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
{
	PrintCurrentFunction();
}

static unsigned char TicketData[128];
SteamAPICall_t RedactedUser::RequestEncryptedAppTicket(void *pUserData, int cbUserData)
{
	PrintCurrentFunction();

	uint64_t callID = NULL;
	EncryptedAppTicketResponse_t *response = nullptr;

	memset(TicketData, 0, sizeof(TicketData));
	memcpy(&TicketData[32], pUserData, min(cbUserData, sizeof(TicketData)));

	callID = SteamCallback::RegisterCall();
	response = static_cast<EncryptedAppTicketResponse_t*>(malloc(sizeof(EncryptedAppTicketResponse_t)));
	response->m_eResult = k_EResultOK;

	SteamCallback::ReturnCall(response, sizeof(EncryptedAppTicketResponse_t), response->k_iCallback, callID);
	return callID;
}
bool RedactedUser::GetEncryptedAppTicket(void *pTicket, int32_t cbMaxTicket, uint32_t *pcbTicket)
{
	PrintCurrentFunction();

	memcpy(pTicket, TicketData, min(cbMaxTicket, sizeof(TicketData)));
	*pcbTicket = sizeof(TicketData);
	return true;
}
int RedactedUser::GetGameBadgeLevel(int nSeries, bool bFoil)
{
	PrintCurrentFunction();
	return 0;
}
int RedactedUser::GetPlayerSteamLevel()
{
	PrintCurrentFunction();
	return 0;
}