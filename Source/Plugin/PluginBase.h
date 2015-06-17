/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		The plugin struct is used to verify that the plugin meets standards.
*/

#pragma once

#define PLUGIN_CONVENTION __cdecl

struct PluginBase
{
	// General info.
	bool isOfficial;
	std::string Name;

	// Standard methods.
	uint64_t(PLUGIN_CONVENTION * PreInit)(void);
	uint64_t(PLUGIN_CONVENTION * PostInit)(void);
	uint64_t(PLUGIN_CONVENTION * AuthorInfo)(void);
	uint64_t(PLUGIN_CONVENTION * OfficialMod)(void);
	uint64_t(PLUGIN_CONVENTION * ExtendedInfo)(void);
	uint64_t(PLUGIN_CONVENTION * DependencyCount)(void);
	uint64_t(PLUGIN_CONVENTION * GetDependency)(int32_t Index);
	uint64_t(PLUGIN_CONVENTION * SendMessageB)(const char* Message, void* Callback);
};
