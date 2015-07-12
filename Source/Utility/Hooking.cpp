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

void Hook::Stomp::Initialize(uintptr_t Place, void *HookToInstall, uint8_t ByteCount, bool useJump)
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
		*(DWORD *)(_Place + 1) = (uint8_t *)_Hook - _Place - 5;

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
void Hook::Stomp::PermanentHook(uintptr_t Place, void *HookToInstall)
{
	memset((uint8_t *)Place, 0x90, 5);
	*(uint8_t *)Place = 0xE9;
	*(DWORD *)((uint8_t *)Place + 1) = (uint8_t *)HookToInstall - (uint8_t *)Place - 5;
}


PIMAGE_NT_HEADERS xImageNTHeader(uint64_t ImgBase)
{
	PIMAGE_DOS_HEADER DosHeader;
	PIMAGE_NT_HEADERS Image;

	DosHeader = (PIMAGE_DOS_HEADER)ImgBase;

	if (DosHeader->e_magic == IMAGE_DOS_SIGNATURE)
	{
		Image = reinterpret_cast<PIMAGE_NT_HEADERS> (DosHeader->e_lfanew + ImgBase);
		if (Image->Signature == IMAGE_NT_SIGNATURE)
		{
			return (PIMAGE_NT_HEADERS)(DosHeader->e_lfanew + ImgBase);
		}
	}
	return 0;
}
size_t Hook::IAT::GetIATAddress(const char* ModuleName, const char* FunctionName, uint64_t ImgBase)
{
	PIMAGE_NT_HEADERS Image;
	PIMAGE_IMPORT_DESCRIPTOR ImportDesc;
	PIMAGE_THUNK_DATA ThunkData;

	Image = xImageNTHeader(ImgBase);
	if (!Image)
		return 0;

	ImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((Image->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) + (size_t)ImgBase);
	for (int i = 0;; i++)
	{
		if (ImportDesc->Name == NULL)
			break;

		if (!_stricmp((char *)(ImportDesc->Name + ImgBase), ModuleName))
		{
			if ((ImportDesc->OriginalFirstThunk) != NULL)
			{
				for (int c = 0;; c++)
				{
					ThunkData = (PIMAGE_THUNK_DATA)((size_t)ImportDesc->OriginalFirstThunk + c * sizeof(IMAGE_THUNK_DATA) + ImgBase);

					if (ThunkData->u1.AddressOfData == NULL)
						break;

					if (!_stricmp((char *)(((PIMAGE_IMPORT_BY_NAME)((size_t)ThunkData->u1.AddressOfData + ImgBase))->Name), FunctionName))
					{
						return (size_t)(((PIMAGE_THUNK_DATA)((size_t)ImportDesc->FirstThunk + c * sizeof(IMAGE_THUNK_DATA) + (size_t)ImgBase))->u1.Function);
					}
				}
			}
		}
	}

	return 0;
}
size_t Hook::IAT::WriteIATAddress(const char* ModuleName, const char* FunctionName, uint64_t ImgBase, void *NewProc)
{
	PIMAGE_NT_HEADERS Image;
	PIMAGE_IMPORT_DESCRIPTOR ImportDesc;
	PIMAGE_THUNK_DATA ThunkData;
	size_t oldValue;

	Image = xImageNTHeader(ImgBase);

	if (!Image) return 0;

	ImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((Image->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) + (size_t)ImgBase);

	HMODULE origHandle = nullptr;
	LPVOID origProc = NULL;

	if (ModuleName != NULL)
		origHandle = GetModuleHandle(ModuleName);
	if (origHandle != nullptr)
		origProc = GetProcAddress(origHandle, FunctionName);
	else
		return 0;

	for (int i = 0;; i++)
	{
		if (ImportDesc->Name == NULL) break;

		if (!_stricmp((char*)((size_t)ImportDesc->Name + (size_t)ImgBase), ModuleName))
		{
			if ((ImportDesc->OriginalFirstThunk) != 0)
			{
				for (int c = 0;; c++)
				{
					ThunkData = (PIMAGE_THUNK_DATA)((size_t)ImportDesc->OriginalFirstThunk + c*sizeof(IMAGE_THUNK_DATA) + (size_t)ImgBase);

					if (ThunkData->u1.AddressOfData == NULL) break;

					if (ThunkData->u1.AddressOfData & 0x80000000)
					{
						uint32_t ordinalNumber = ThunkData->u1.AddressOfData & 0xFFFFFFF;

						if (GetProcAddress(origHandle, (LPCSTR)ordinalNumber) == origProc)
						{
							oldValue = (uint32_t)(((PIMAGE_THUNK_DATA)((size_t)ImportDesc->FirstThunk + c*sizeof(IMAGE_THUNK_DATA) + (size_t)ImgBase))->u1.Function);
							((PIMAGE_THUNK_DATA)((size_t)ImportDesc->FirstThunk + c*sizeof(IMAGE_THUNK_DATA) + (size_t)ImgBase))->u1.Function = (size_t)NewProc;
							return oldValue;
						}
					}
					else
					{
						if (!_stricmp((char*)(((PIMAGE_IMPORT_BY_NAME)((size_t)ThunkData->u1.AddressOfData + (size_t)ImgBase))->Name), FunctionName))
						{
							oldValue = (size_t)(((PIMAGE_THUNK_DATA)((size_t)ImportDesc->FirstThunk + c*sizeof(IMAGE_THUNK_DATA) + (size_t)ImgBase))->u1.Function);
							((PIMAGE_THUNK_DATA)((size_t)ImportDesc->FirstThunk + c*sizeof(IMAGE_THUNK_DATA) + (size_t)ImgBase))->u1.Function = (size_t)NewProc;
							return oldValue;
						}
					}
				}
			}
		}
		ImportDesc++;
	}

	return 0;
}
