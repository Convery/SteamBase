/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Standard includeheader that links everything together.
*/

#pragma once

// Configuration defines.
#pragma region Defines

// Debug information.
#define NET_DEBUG			// Network logging.
#define FS_DEBUG			// Filesystem logging.
#define PERF_DEBUG			// Performance logging.

// Piracy prevention as mandated by ATVI.
#define NO_PIRACY

// Debug functionallity.
#if !defined(NET_DEBUG) && !defined(FS_DEBUG) && !defined(PERF_DEBUG)
#define DBGPrint(fmt, ...)
#define ERRPrint(fmt, ...) 
#else
// Set them to instaprint for now, as it's helpful for debugging
#define DBGPrint(fmt, ...) WinConsole::EnqueueMessage("DBG", (char *)hString::va(fmt, ##__VA_ARGS__), "", true) 
#define ERRPrint(fmt, ...) WinConsole::EnqueueMessage("ERR", (char *)hString::va(fmt, ##__VA_ARGS__), "", true)
#endif

// Useful for logging.
#define PrintCurrentFunction()	WinConsole::EnqueueMessage("INFO", __FUNCTION__, "", false)

// Individual debug functions.
#ifdef NET_DEBUG
#define nDBGPrint(dta, fmt, ...) WinConsole::EnqueueMessage("NET", (char *)hString::va(fmt, ##__VA_ARGS__), dta)
#else
#define nDBGPrint(fmt, ...)
#endif
#ifdef FS_DEBUG
#define fDBGPrint(dta, fmt, ...) WinConsole::EnqueueMessage("FS", (char *)hString::va(fmt, ##__VA_ARGS__), dta)
#else
#define fDBGPrint(fmt, ...)
#endif
#ifdef PERF_DEBUG
#define pDBGPrint(dta, fmt, ...) WinConsole::EnqueueMessage("PERF", (char *)hString::va(fmt, ##__VA_ARGS__), dta)
#else
#define pDBGPrint(fmt, ...)
#endif

#pragma endregion

// Unneeded warnings.
#pragma region Warnings
#pragma warning(disable:117)			// Non-void function should return a value
#pragma warning(disable:4244)			// Conversion from large type to smaller type can cause data loss.
#pragma warning(disable:4351)			// Elements of an array will be initialized by default.
#pragma warning(disable:4100)			// Unreferenced parameter.
#pragma warning(disable:4820)			// Struct misallignment results in padding.
#pragma warning(disable:4565)			// Symbol redefinition.
#pragma warning(disable:4668)			// Preprocessor macro is not defined.
#pragma warning(disable:4127)			// Conditional expression is constant. while(true) { }
#pragma warning(disable:981)			// Operands are evaluated in unspecified order.
#pragma warning(disable:444)			// Destructor for base class is not virtual.
#pragma warning(disable:2259)			// Non-pointer conversion from type to smaller type.
#pragma warning(disable:1786)			// Winsock function is deprecated.
#pragma endregion

// C\C++ includes.
#pragma region Runtime
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <queue>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <chrono>
#include <thread>
#include <direct.h>
#pragma endregion

// Utility headers.
#pragma region UtilIncludes
#include "Utility\hString.h"
#include "Utility\ByteBuffer.h"
#include "Utility\FileSystem.h"
#include "Utility\hConsole.h"
#include "Utility\WinConsole\WinConsole.h"
#include "Utility\WebIO.h"

#include "JSON\json.h"
#pragma endregion

// Exported functionality.
#pragma region ExportIncludes
#include "External\GlobalVariables.h"
#include "External\GameInformation.h"
#pragma endregion

// Plugin headers.
#pragma region PluginIncludes
#include "Plugin\PluginBase.h"
#include "Plugin\PluginManager.h"
#include "Plugin\Handler\HandlerManager.h"
#pragma endregion

// Steam headers.
#pragma region SteamIncludes
#include "Steam\ConsoleCommandHandler.h"
#include "Steam\InterfaceManager.h"
#include "Steam\SteamCallback.h"

#include "Steam\Common\ClientCommon.h"
#include "Steam\SteamTypes\SteamTypes.h"
#include "Steam\Interface\SteamClient.h"

#include "Steam\Classes\RedactedClasses.h"
#include "Steam\ClassWrappers\SteamClasses.h"

#include "Steam\SteamProxy.h"
#pragma endregion
