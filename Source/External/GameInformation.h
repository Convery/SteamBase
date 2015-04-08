/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-03-21
	Notes:
		These methods fill the Global::Game_ information.
*/

#pragma once

inline bool Fill_Global_Argv()
{
	for (int32_t i = 0; i < __argc; i++)
	{
		Global::Game_Argv.push_back(__argv[i]);
	}

	return true;
}
inline bool Fill_Global_BinaryName()
{
	std::string Path = Global::Game_Argv[0];
	std::string Filename = Path.substr(Path.find_last_of("\\") + 1);

	return strcpy_s(Global::Game_BinaryName, 64, Filename.c_str()) == 0;
}
inline bool Fill_Global_CommandLine()
{
	for (size_t i = 1; i < Global::Game_Argv.size(); i++)
	{
		Global::Game_Commandline.append(Global::Game_Argv[i]);
		Global::Game_Commandline.append(" ");
	}
	return true;
}
