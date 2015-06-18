/*
This project is released under the GPL 2.0 license.
Please do no evil.

Initial author: (https://github.com/)momo5502
Started: 2015-05-29
Notes:
Create mini dumps for debugging purpose
Thanks to NTAuthority for his minidump base
*/

#include "..\StdInclude.h"

Hook::Stomp DumpHandler::SetUnhandledExceptionFilter_Hook;

void DumpHandler::Initialize()
{
	SetUnhandledExceptionFilter(&DumpHandler::CustomUnhandledExceptionFilter);

	DumpHandler::SetUnhandledExceptionFilter_Hook.Initialize((uintptr_t)SetUnhandledExceptionFilter, DumpHandler::SetUnhandledExceptionFilter_Stub);
	DumpHandler::SetUnhandledExceptionFilter_Hook.InstallHook();
}

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI DumpHandler::SetUnhandledExceptionFilter_Stub(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	DumpHandler::SetUnhandledExceptionFilter_Hook.ReleaseHook();
	LPTOP_LEVEL_EXCEPTION_FILTER retVal = SetUnhandledExceptionFilter(&DumpHandler::CustomUnhandledExceptionFilter);
	DumpHandler::SetUnhandledExceptionFilter_Hook.InstallHook();

	return retVal;
}

// Credit to NTAuthority
LONG WINAPI DumpHandler::CustomUnhandledExceptionFilter(LPEXCEPTION_POINTERS ExceptionInfo)
{
	// Ignore breakpoints.
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) return EXCEPTION_CONTINUE_EXECUTION;

	// step 1: write minidump
	char error[1024];
	char filename[MAX_PATH];
	__time64_t time;
	tm* ltime;

	_time64(&time);
	ltime = _localtime64(&time);
	strftime(filename, sizeof(filename) - 1, "Redacted - %H-%M-%S %d.%m.%Y.dmp", ltime);
	_snprintf(error, sizeof(error) - 1, "A minidump has been written to %s.", filename);

	HANDLE hFile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION ex = { 0 };
		ex.ThreadId = GetCurrentThreadId();
		ex.ExceptionPointers = ExceptionInfo;
		ex.ClientPointers = FALSE;

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ex, NULL, NULL);

		CloseHandle(hFile);
	}
	else
	{
		_snprintf(error, sizeof(error) - 1, "An error (0x%x) occurred during creating %s.", GetLastError(), filename);
	}

	// step 2: exit the application
	// why was this removed?
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
	{
		MessageBox(0, "Termination because of a stack overflow.", "ERROR", MB_ICONERROR);
	}
	else
	{
		MessageBox(0, hString::va("Fatal error (0x%08x) at 0x%08x.\n%s", ExceptionInfo->ExceptionRecord->ExceptionCode, ExceptionInfo->ExceptionRecord->ExceptionAddress, error), "ERROR", MB_ICONERROR);
	}

	TerminateProcess(GetCurrentProcess(), ExceptionInfo->ExceptionRecord->ExceptionCode);
	return 0;
}
