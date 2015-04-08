/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-04-08
	Notes:
		The steam_api is fairly useless on it's own.
		Therefore we need to load plugins.
*/

#pragma once

class PluginManager
{
	static std::vector<std::string> PluginNames;
	static std::vector<HMODULE> PluginModules;

	static void LoadPlugins();
	static void VerifyExports();
	static void VerifyDependencies();
	static void VerifyOfficial();
	static void PrintAuthorInfo();

public:
	static std::vector<PluginBase> Plugins;

	static void Startup();
	static void PreInit();
	static void PostInit();
};
