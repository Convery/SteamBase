/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-25
	Notes:
		Exports global accessors.
*/

#include "..\STDInclude.h"

#define API __declspec(dllexport)

extern "C"
{
	// Global::Steam
	API void __cdecl Steam_GetUsername(char *Buffer, uint32_t Maxlen = NULL)
	{
		strcpy_s(Buffer, Maxlen == NULL ? sizeof(Global::Steam_Username) : min(sizeof(Global::Steam_Username), Maxlen), Global::Steam_Username);
	};
	API void __cdecl Steam_GetLanguage(char *Buffer, uint32_t Maxlen = NULL)
	{
		strcpy_s(Buffer, Maxlen == NULL ? sizeof(Global::Steam_Language) : min(sizeof(Global::Steam_Language), Maxlen), Global::Steam_Language);
	};
	API void __cdecl Steam_GetXUID(void *Buffer, bool Full64 = true)
	{
		if(Full64)
			memcpy(Buffer, &Global::Steam_UserID, 8);
		else
			memcpy(Buffer, &Global::Steam_UserID + 4, 4);
	}

	API uint64_t __cdecl Steam_GetFullXUID()
	{
		return Global::Steam_UserID;
	}

	API const char* __cdecl Steam_GetSteamUsername()
	{
		return SteamProxy::GetUsername();
	};

	// Global::System
	API int32_t __cdecl System_GetOfflineMode()
	{
		return Global::Steam_Offline ? 1 : 0;
	};
	API int32_t __cdecl System_GetDedicatedMode()
	{
		return Global::Steam_Dedicated ? 1 : 0;
	};
}