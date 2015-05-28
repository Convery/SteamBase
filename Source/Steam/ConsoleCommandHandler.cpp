/*
This project is released under the GPL 2.0 license.
Please do no evil.

Initial author: (https://github.com/)sokie
Started: 2015-05-25
Notes:
Will handle commands to our base from console
NO-OP for now
*/

#include "..\STDInclude.h"

char* ConsoleCommandHandler::ExecuteCommand(char *cmd)
{
#pragma region UGLY_SHIT
	// Pretty ugly and hack-y way, but it works for now :P
	HMODULE steamAPI = GetModuleHandleA("ExtendedConsole.Red32n");
	if (!steamAPI) return "Console plugin not loaded!";
	FARPROC Cmd_ExecuteCommand = GetProcAddress(steamAPI, "Cmd_ExecuteCommand");
	if (!Cmd_ExecuteCommand) return "Cmd_ExecuteCommand not exported!";
	__asm
	{
		push 0 // Execute command asynchronously, as we run in our own thread
		push cmd
		call Cmd_ExecuteCommand
		add esp, 8h
	}
#pragma endregion

	//TODO: handle cmd
	return (char *)hString::va("ERROR: ", cmd, " invalid command");
}