/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		The plugin struct is used to verify that the plugin meets standards.
*/

#pragma once

struct PluginBase
{
	// General info.
	bool isOfficial;
	std::string Name;

	// Standard methods.
	uint64_t(__stdcall * PreInit)(void);
	uint64_t(__stdcall * PostInit)(void);
	uint64_t(__stdcall * AuthorInfo)(void);
	uint64_t(__stdcall * OfficialMod)(void);
	uint64_t(__stdcall * ExtendedInfo)(void);
	uint64_t(__stdcall * DependencyCount)(void);
	uint64_t(__stdcall * GetDependency)(int32_t Index);
	uint64_t(__stdcall * SendMessageB)(const char* Message, void* Callback);
};
