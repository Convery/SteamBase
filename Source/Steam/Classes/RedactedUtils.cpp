/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		Utils.
*/

#include "..\..\StdInclude.h"

// Return the number of seconds since
uint32_t RedactedUtils::GetSecondsSinceAppActive()
{
	PrintCurrentFunction();
	return (uint32_t)((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Global::StartupPoint).count()) / 1000);
}
uint32_t RedactedUtils::GetSecondsSinceComputerActive()
{
	PrintCurrentFunction();
	return (uint32_t)GetTickCount64() / 1000;
}

// Each universe is a self-contained Steam instance.
EUniverse RedactedUtils::GetConnectedUniverse()
{
	PrintCurrentFunction();
	return k_EUniversePublic;
}

// Steam servertime, UNIX time.
uint32_t RedactedUtils::GetServerRealTime()
{
	PrintCurrentFunction();
#ifdef _WIN64
	return 0;
#else
	return (uint32_t)time(NULL);
#endif
}

// Return the two digit ISO 3166-1-alpha-2 country code.
const char *RedactedUtils::GetIPCountry()
{
	PrintCurrentFunction();
	return "SE"; // TODO: Query the master..
}

// Returns true if the image exists.
bool RedactedUtils::GetImageSize(int iImage, uint32 *pnWidth, uint32 *pnHeight)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUtils, GetImageSize, iImage, pnWidth, pnHeight);
}

// Returns true if the image exists.
bool RedactedUtils::GetImageRGBA(int iImage, uint8 *pubDest, int nDestBufferSize)
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUtils, GetImageRGBA, iImage, pubDest, nDestBufferSize);
}

// Returns the IP of the reporting server for Valve.
bool RedactedUtils::GetCSERIPPort(uint32_t *unIP, uint16_t *usPort)
{
	PrintCurrentFunction();
	return false;
}

// Return the percent of battery left, 255 for AC power.
uint8_t RedactedUtils::GetCurrentBatteryPower()
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUtils, GetCurrentBatteryPower);
}

// Returns the ID of the current process.
uint32_t RedactedUtils::GetAppID()
{
	PrintCurrentFunction();
	return Global::Steam_AppID;
}

// Sets the position where the overlay instance for the currently calling game should show notifications.
void RedactedUtils::SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
{
	PrintCurrentFunction();
	SteamProxy::SetOverlayNotificationPosition(eNotificationPosition);
}

// API asynchronous call results
bool RedactedUtils::IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool *pbFailed)
{
	PrintCurrentFunction();
	return false;
}
ESteamAPICallFailure RedactedUtils::GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
{
	PrintCurrentFunction();
	return k_ESteamAPICallFailureNone;
}
bool RedactedUtils::GetAPICallResult(SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
{
	PrintCurrentFunction();
	return false;
}

// Called each frame to process matchmaking results.
// Redundant if SteamAPI_RunCallbacks() is called.
void RedactedUtils::RunFrame()
{
	PrintCurrentFunction();
}

// Returns the number of IPC calls made since the last time this func was called.
// For performance debugging.
uint32_t RedactedUtils::GetIPCCallCount()
{
	PrintCurrentFunction();
	return 0;
}

// API warning handling
void RedactedUtils::SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction)
{
	PrintCurrentFunction();
}

// Returns true if the overlay is enabled.
bool RedactedUtils::IsOverlayEnabled()
{
	PrintCurrentFunction();
	return SteamProxy::IsOverlayEnabled();
}

// Used when the game doesn't refresh in a loop.
bool RedactedUtils::BOverlayNeedsPresent()
{
	PrintCurrentFunction();
	return SteamProxy::BOverlayNeedsPresent();
}

// Creates a hash of the file.
SteamAPICall_t RedactedUtils::CheckFileSignature(const char *szFileName)
{
	PrintCurrentFunction();
	return 0; // TODO: Proper hashing.
}

// Gamepad support.
bool RedactedUtils::ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eInputLineMode, const char *szText, uint32 uMaxLength, const char * pUnk)
{
	PrintCurrentFunction();
	return false;
}
uint32_t RedactedUtils::GetEnteredGamepadTextLength()
{
	PrintCurrentFunction();
	return 0;
}
bool RedactedUtils::GetEnteredGamepadTextInput(char *pchValue, uint32_t cchValueMax)
{
	PrintCurrentFunction();
	return false;
}

const char *RedactedUtils::GetSteamUILanguage()
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUtils, GetSteamUILanguage);
}

bool RedactedUtils::IsSteamRunningInVR()
{
	PrintCurrentFunction();
	STEAMPROXY_CALL(ISteamUtils, IsSteamRunningInVR);
}