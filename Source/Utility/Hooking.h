/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-02-13
	Notes:
		Largely based on an unknown authors work.
*/

#pragma once

class Hook
{
public:
	class Stomp
	{
	public:
		uint8_t _OriginalCode[5];
		uint8_t _ByteCount;
		uint8_t *_Place;
		void *_Hook;
		bool _Jump;

		void Initialize(uint32_t Place, void *HookToInstall = NULL, uint8_t ByteCount = 5, bool useJump = true);
		void InstallHook(void *HookToInstall = NULL);
		void ReleaseHook();
		static void PermanentHook(uint32_t Place, void *HookToInstall);
	};
};
