/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-02-13
	Notes:
		Largely based on an unknown authors work.
*/

#include "..\StdInclude.h"

void Hook::Stomp::Initialize(uint32_t Place, void *HookToInstall, uint8_t ByteCount, bool useJump)
{
	_Place = (uint8_t *)Place;
	_ByteCount = ByteCount < sizeof(_OriginalCode) ? ByteCount : sizeof(_OriginalCode);
	memcpy(_OriginalCode, _Place, sizeof(_OriginalCode));

	_Hook = HookToInstall;
	_Jump = useJump;
}
void Hook::Stomp::InstallHook(void *HookToInstall)
{
	if (HookToInstall)
		_Hook = HookToInstall;

	if (_Hook)
	{
		DWORD d = 0;
		VirtualProtect(_Place, _ByteCount, PAGE_READWRITE, &d);

		memset(_Place, 0x90, _ByteCount);
		_Place[0] = _Jump ? (uint8_t)0xE9 : (uint8_t)0xE8;
		*(ptrdiff_t *)(_Place + 1) = (uint8_t *)_Hook - _Place - 5;

		VirtualProtect(_Place, _ByteCount, d, &d);
	}
}
void Hook::Stomp::ReleaseHook()
{
	DWORD d = 0;
	VirtualProtect(_Place, _ByteCount, PAGE_READWRITE, &d);

	memcpy(_Place, _OriginalCode, _ByteCount);

	VirtualProtect(_Place, _ByteCount, d, &d);
}
void Hook::Stomp::PermanentHook(uint32_t Place, void *HookToInstall)
{
	memset((uint8_t *)Place, 0x90, 5);
	*(uint8_t *)Place = 0xE9;
	*(ptrdiff_t *)((uint8_t *)Place + 1) = (uint8_t *)HookToInstall - (uint8_t *)Place - 5;
}
