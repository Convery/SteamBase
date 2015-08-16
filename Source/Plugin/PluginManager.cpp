/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		The steam_api is fairly useless on it's own.
		Therefore we need to load plugins.
*/

#include "..\STDInclude.h"

std::vector<std::string> PluginManager::PluginNames;
std::vector<HMODULE> PluginManager::PluginModules;
std::vector<PluginBase> PluginManager::Plugins;

// Load all plugin modules into the PluginModules vector and fill the name vector.
void PluginManager::LoadPlugins()
{
	std::vector<std::string> PluginFiles;
	HMODULE Library = NULL;

	// Enumerate all files with our extension.
	if (!FileSystem::ListFiles("Plugins\\", PluginFiles,
#ifdef _WIN64
		".Red64n"
#else
		".Red32n"
#endif
		)) 
	{
		WinConsole::EnqueueMessage("ERR", "No plugins found.", "", true);
	}

	// Load the plugins into process memory.
	for (uint32_t i = 0; i < PluginFiles.size(); i++)
	{
		Library = LoadLibraryA(hString::va("Plugins\\%s", PluginFiles[i].c_str()));

		if (Library != NULL)
		{
			PluginNames.push_back(PluginFiles[i]);
			PluginModules.push_back(Library);
			WinConsole::EnqueueMessage("INFO", (char *)PluginFiles[i].c_str(), "", true);
		}
		else
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Failed to load [%s] for reason: %lu", PluginFiles[i].c_str(), GetLastError()), "", true);
		}

		Library = NULL;
	}
}

// Fill the plugin struct and remove bad plugins.
void PluginManager::VerifyExports()
{
	std::vector<uint32_t> PurgeList;
	PluginBase BasePlugin;

	// Load the plugins into process memory.
	for (uint32_t i = 0; i < PluginNames.size(); i++)
	{
		// Clear the struct and set the name.
		BasePlugin = PluginBase();
		BasePlugin.Name = PluginNames[i];

		// Fill the struct with function pointers.
		BasePlugin.Uninit          = (uint64_t(PLUGIN_CONVENTION *)(void))               GetProcAddress(PluginModules[i], "Uninit");
		BasePlugin.PreInit         = (uint64_t(PLUGIN_CONVENTION *)(void))               GetProcAddress(PluginModules[i], "PreInit");
		BasePlugin.PostInit        = (uint64_t(PLUGIN_CONVENTION *)(void))               GetProcAddress(PluginModules[i], "PostInit");
		BasePlugin.AuthorInfo      = (uint64_t(PLUGIN_CONVENTION *)(void))               GetProcAddress(PluginModules[i], "AuthorInfo");
		BasePlugin.ExtendedInfo    = (uint64_t(PLUGIN_CONVENTION *)(void))               GetProcAddress(PluginModules[i], "ExtendedInfo");
		BasePlugin.OfficialMod     = (uint64_t(PLUGIN_CONVENTION *)(void))               GetProcAddress(PluginModules[i], "OfficialMod");
		BasePlugin.DependencyCount = (uint64_t(PLUGIN_CONVENTION *)(void))               GetProcAddress(PluginModules[i], "DependencyCount");
		BasePlugin.GetDependency   = (uint64_t(PLUGIN_CONVENTION *)(int32_t))            GetProcAddress(PluginModules[i], "GetDependency");
		BasePlugin.SendMessageB    = (uint64_t(PLUGIN_CONVENTION *)(const char*, void*)) GetProcAddress(PluginModules[i], "SendMessageB");

		// Verify that all functions were added.
		if (!BasePlugin.PreInit)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "PreInit"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.PostInit)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "PostInit"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.AuthorInfo)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "AuthorInfo"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.ExtendedInfo)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "ExtendedInfo"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.OfficialMod)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "OfficialMod"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.DependencyCount)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "DependencyCount"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.GetDependency)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "GetDependency"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.SendMessageB)
		{
			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "SendMessageB"), "");
			PurgeList.push_back(i);
			continue;
		}

		// Don't verify uninit, as it's optional
// 		if (!BasePlugin.Uninit)
// 		{
// 			WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "Uninit"), "");
// 			PurgeList.push_back(i);
// 			continue;
// 		}

		// Add the plugin to the vector.
		Plugins.push_back(BasePlugin);
	}

	// Remove the plugins in reverse order.
	for (uint32_t i = 0; i < PurgeList.size(); i++)
	{
		PluginNames.erase(PluginNames.begin() + PurgeList.back());
		PluginModules.erase(PluginModules.begin() + PurgeList.back());
		PurgeList.pop_back();
	}
}

// Verify that essential plugins are loaded.
// Optional plugins can be checked via the API.
void PluginManager::VerifyDependencies()
{
	std::unordered_map<std::string, std::string> PurgedList;
	int32_t DependencyCount = 0;
	bool DependencyMissing = false;
	const char *DependencyName = "";

	// Iterate through the plugins vector and remove bad plugins.
	// Much recursive, very secure.
LABEL_RESTART:
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		// Get the count.
		DependencyCount = 0;
		DependencyCount = i->DependencyCount();

		// Check each dependency.
		for (int32_t c = 0; c < DependencyCount; c++)
		{
			// Set the dependency to not found.
			DependencyMissing = true;

			// Get the name.
			DependencyName = "";
			DependencyName = (const char *)i->GetDependency(c);

			// Iterate through the plugins vector and find by name.
			for (auto k = Plugins.begin(); k != Plugins.end(); ++k)
			{
				if (!_stricmp(k->Name.c_str(), DependencyName))
				{
					DependencyMissing = false;
					break;
				}
			}

			// If the dependency is missing..
			if (DependencyMissing)
			{
				// Report it for debugging.
				PurgedList.emplace(i->Name, DependencyName);

				// Remove the plugin.
				Plugins.erase(i);

				// Restart the loop as already checked plugins may now be missing
				// a dependency since this was removed.
				goto LABEL_RESTART;
			}
		}
	}

	// Print info about the removed plugins so developers can debug.
	for (auto i = PurgedList.begin(); i != PurgedList.end(); ++i)
	{
		WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing a dependency (%s) and has been removed.\n", i->first.c_str(), i->second.c_str()), "");
	}
}

// Verify that the plugin is whitelisted in our DB.
// This needs to be called before dependency checking.
void PluginManager::VerifyOfficial()
{
	std::unordered_map<std::string, std::string> PurgedList;
	std::basic_string<uint8_t> FileBuffer;

	// Check the ini so we know if we should check at all.
	if (GetPrivateProfileIntA("Plugins", "AllowUnofficial", 0, "./Redacted.ini"))
		return;

	// Iterate through the plugins vector.
LABEL_RESTART:
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		do
		{
			// Ask the plugin if it wants to be checked.
			if (i->OfficialMod() == FALSE)
			{
				// Report it for debugging.
				PurgedList.emplace(i->Name, "it does not want to be verified");
				break;
			}

			// Prepare the buffer for input.
			FileBuffer.clear();

			// Read the plugin ito the buffer.
			if (!FileSystem::ReadFile(hString::va("Plugins\\%s", i->Name.c_str()), FileBuffer))
			{
				// Report it for debugging.
				PurgedList.emplace(i->Name, "it could not read the file");
				break;
			}

			// TODO:
			// At this point we should send the hash of the data
			// to our server along with the XUID and plugin name.
			if (true)
			{
				goto LABEL_END;
			}
			else
			{
				// Report it for debugging.
				PurgedList.emplace(i->Name, "the server did not like it");
				break;
			}
		} while (false);

		// Remove the plugin.
		Plugins.erase(i);

		// Restart the loop.
		goto LABEL_RESTART;

		// This is really awkward use of goto but whatever.
		// Nested loops are odd in C/C++.
	LABEL_END:;
	}

	// Print info about the removed plugins so developers can debug.
	for (auto i = PurgedList.begin(); i != PurgedList.end(); ++i)
	{
		WinConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) could not be verified because %s and has therefore been removed.\n", i->first.c_str(), i->second.c_str()), "");
	}
}

// Simply list the plugins and the author info.
// This is just to show the user that everything's loaded.
void PluginManager::PrintAuthorInfo()
{
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		const char *AuthorName = nullptr;
		AuthorName = (const char *)i->AuthorInfo();

		if ((DWORD)AuthorName <= 1) // Preserve compatibility for old plugins.
		{
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Loaded plugin <%s>", i->Name.c_str()), "");
		}
		else
		{
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Loaded plugin <%s> by <%s>", i->Name.c_str(), AuthorName), "");
		}
	}
}

// Loads all plugins and verifies them.
void PluginManager::Startup()
{
	// Let the user know we are loading plugins.
	WinConsole::EnqueueMessage("INFO", "", "", true);
	WinConsole::EnqueueMessage("INFO", "Plugins:", "", true);

	LoadPlugins();
	VerifyExports();
	VerifyOfficial();
	VerifyDependencies();
	PrintAuthorInfo();
}

// Call the preinit function for .text segment modification.
void PluginManager::PreInit()
{
	// Let the user know we are calling.
	WinConsole::EnqueueMessage("INFO", "", "", true);
	WinConsole::EnqueueMessage("INFO", "Plugins::PreInit:", "", true);

	// Iterate through the vector and call the functionpointers.
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		auto Start = std::chrono::high_resolution_clock::now();
		
		if (i->PreInit() != FALSE)
		{
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> preinit succeeded in %ld msec", i->Name.c_str(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Start).count()), "", true);
		}
		else
		{
			// We do not remove the plugin for this.
			// It can still do memory edits if it wants.
			// And it may provide exports for other functions.
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> preinit failed", i->Name.c_str()), "", true);
		}
	}
}

// Call the postinit function for memory modification.
void PluginManager::PostInit()
{
	// Let the user know we are calling.
	WinConsole::EnqueueMessage("INFO", "", "", true);
	WinConsole::EnqueueMessage("INFO", "Plugins::PostInit:", "", true);

	// Iterate through the vector and call the functionpointers.
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		auto Start = std::chrono::high_resolution_clock::now();

		if (i->PostInit() != FALSE)
		{
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> postinit succeeded in %ld msec", i->Name.c_str(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Start).count()), "", true);
		}
		else
		{
			// We do not remove the plugin for this.
			// It can still do memory edits if it wants.
			// And it may provide exports for other functions.
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> postinit failed", i->Name.c_str()), "", true);
		}
	}

	// Start printing our logs.
	WinConsole::EnqueueMessage("INFO", "", "", true);
	WinConsole::EnqueueMessage("INFO", "Gamelog:", "", true);
	//WinConsole::StartPrinting();
}

// Call the uninit function for uninitialization.
void PluginManager::Uninit()
{
	// Let the user know we are calling.
	WinConsole::EnqueueMessage("INFO", "", "", true);
	WinConsole::EnqueueMessage("INFO", "Plugins::Uninit:", "", true);

	// Iterate through the vector and call the functionpointers.
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		auto Start = std::chrono::high_resolution_clock::now();

		if (i->Uninit && i->Uninit() != FALSE)
		{
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> uninit succeeded in %ld msec", i->Name.c_str(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Start).count()), "", true);
		}
		else
		{
			// We do not remove the plugin for this.
			// It can still do memory edits if it wants.
			// And it may provide exports for other functions.
			WinConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> uninit failed", i->Name.c_str()), "", true);
		}
	}
}

// Legacy stuff. Remove that when old plugins are updated.
extern "C"
{
	__declspec(dllexport) int32_t __cdecl Plugin_PluginLoaded(const char *PluginName)
	{
		for (std::vector<PluginBase>::const_iterator i = PluginManager::Plugins.begin(); i != PluginManager::Plugins.end(); ++i)
		{
			if (!_stricmp(PluginName, i->Name.c_str()))
				return TRUE;
		}
		return FALSE;
	}

	__declspec(dllexport) int32_t __cdecl isPluginLoaded(const char *PluginName)
	{
		return Plugin_PluginLoaded(PluginName);
	}

	__declspec(dllexport) int32_t __cdecl Debug_PrintDebugString(const char *Message)
	{
		DBGPrint(Message);
		return TRUE;
	}
}
