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
	//TODO: handle cmd
	return (char *)hString::va("ERROR: ", cmd, " invalid command");
}