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
#define NOPIRACY

// Debug functionallity.
#if !defined(NET_DEBUG) && !defined(FS_DEBUG) && !defined(PERF_DEBUG)
	#define DBGPrint(fmt, ...)
#else
	#define DBGPrint(fmt, ...) printf(fmt"\n",  ##__VA_ARGS__)
#endif

#pragma endregion

// Unneeded warnings.
#pragma region Warnings
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
#include <string>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
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
#pragma endregion

// Exported functionality.
#pragma region ExportIncludes
#include "External\GlobalVariables.h"
#include "External\GameInformation.h"
#pragma endregion
