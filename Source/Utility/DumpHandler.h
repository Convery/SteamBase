/*
This project is released under the GPL 2.0 license.
Please do no evil.

Initial author: (https://github.com/)momo5502
Started: 2015-05-29
Notes:
Create mini dumps for debugging purpose
Thanks to NTAuthority for his minidump base
*/

#pragma once

#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")

class DumpHandler // Would a namespace be better here?
{
public:
	static void Initialize();

private:
	static Hook::Stomp SetUnhandledExceptionFilter_Hook;

	static LONG WINAPI CustomUnhandledExceptionFilter(LPEXCEPTION_POINTERS ExceptionInfo);
	static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI SetUnhandledExceptionFilter_Stub(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
};
