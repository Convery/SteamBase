/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Information about the application.
*/

#include "..\..\StdInclude.h"

bool RedactedApps::IsSubscribedToCurrentApp()
{
	PrintCurrentFunction();

#ifdef NO_PIRACY
	return false;
#else
	return true;
#endif
}
bool RedactedApps::IsMatureContentDisabled()
{
	PrintCurrentFunction();
	return false;
}
bool RedactedApps::IsACybercafeAccount()
{
	PrintCurrentFunction();
	return false;
}
bool RedactedApps::IsUserVACBanned()
{
	PrintCurrentFunction();
	return false;
}

const char *RedactedApps::GetCurrentGameLanguage()
{
	PrintCurrentFunction();
	return Global::Steam_Language;
}
const char *RedactedApps::GetAvailableGameLanguages()
{
	PrintCurrentFunction();
	return Global::Steam_Language;
}

bool RedactedApps::IsSubscribedToApp(uint32_t AppID)
{
	PrintCurrentFunction();

#ifdef NO_PIRACY
	return false;
#else
	return true;
#endif
}
bool RedactedApps::IsDlcInstalled(uint32_t DLCID)
{
	DBGPrint("%s(%i)", __FUNCTION__, DLCID);

#ifndef NO_PIRACY
	return false;
#else
	char FilePath[256];

	// Read the DLC path from the game ini.
	GetPrivateProfileStringA("DLC", hString::va("%i", DLCID), "404", FilePath, 256, hString::va("%s.ini", Global::Game_BinaryName));
	return FileSystem::FileExists(FilePath);
#endif
}
uint32_t RedactedApps::GetEarliestPurchaseUnixTime(uint32_t AppID)
{
	PrintCurrentFunction();
	return 0;
}

uint32_t RedactedApps::GetDLCCount()
{
	PrintCurrentFunction();
	return GetPrivateProfileIntA("DLC", "DLCCount", 0, hString::va("%s.ini", Global::Game_BinaryName));
}
bool RedactedApps::IsSubscribedFromFreeWeekend()
{
	PrintCurrentFunction();
	return false;
}
bool RedactedApps::GetDLCDataByIndex(uint32_t iDLC, uint32_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize)
{
	PrintCurrentFunction();
	return false;
}

void RedactedApps::InstallDLC(uint32_t DLCID)
{
	PrintCurrentFunction();
}
void RedactedApps::UninstallDLC(uint32_t DLCID)
{
	PrintCurrentFunction();
}

void RedactedApps::RequestAppProofOfPurchaseKey(AppId_t nAppID)
{
	PrintCurrentFunction();

#ifdef NO_PIRACY

#endif
}
bool RedactedApps::GetCurrentBetaName(char *pchName, uint32_t cchNameBufferSize)
{
	PrintCurrentFunction();

	pchName = "public";
	cchNameBufferSize = 7;
	return true;
}

uint32_t RedactedApps::GetInstalledDepots(uint32_t puDepots[], uint32_t cuDepotsMax)
{
	PrintCurrentFunction();
	return FALSE;
}
uint32_t RedactedApps::GetAppInstallDir(uint32_t nAppID, char *pchPath, uint32_t cchPath)
{
	PrintCurrentFunction();
	if (nAppID == Global::Steam_AppID)
	{
		strncpy(pchPath, Global::Game_Argv[0].c_str(), cchPath);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
bool RedactedApps::BIsAppInstalled(AppId_t appID)
{
	PrintCurrentFunction();

#ifdef NO_PIRACY
	return false;
#else
	return false;
#endif
}
bool RedactedApps::MarkContentCorrupt(bool bMissingFilesOnly)
{
	PrintCurrentFunction();

	return false;
}

CSteamID RedactedApps::GetAppOwner()
{
	PrintCurrentFunction();

	return CSteamID(Global::Steam_UserID);
}
const char *RedactedApps::GetLaunchQueryParam(const char *pchKey)
{
	PrintCurrentFunction();

	return "";
}
