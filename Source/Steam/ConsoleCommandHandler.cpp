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

Cmd_Callback_t ConsoleCommandHandler::ExecuteCallback = 0;

char* ConsoleCommandHandler::ExecuteCommand(char *cmd)
{
	if (ConsoleCommandHandler::ExecuteCallback)
	{
		return ConsoleCommandHandler::ExecuteCallback(cmd);
	}

	//TODO: handle cmd
	return (char *)hString::va("ERROR: '%s' invalid command", cmd);
}

void ConsoleCommandHandler::RegisterCallback(Cmd_Callback_t callback)
{
	ConsoleCommandHandler::ExecuteCallback = callback;
	WinConsole::ActivateCommandField();
}

extern "C" __declspec(dllexport) void Cmd_RegisterCallback(Cmd_Callback_t callback)
{
	return ConsoleCommandHandler::RegisterCallback(callback);
}