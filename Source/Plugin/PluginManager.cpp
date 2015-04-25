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
	if (!FileSystem::ListFiles(
		"Plugins\\", 
		&PluginFiles,
#ifdef _WIN64
		".Red64n"
#else
		".Red32n"
#endif
		)) 
	{

	}

	// Load the plugins into process memory.
	for (uint32_t i = 0; i < PluginFiles.size(); i++)
	{
		Library = LoadLibraryA(hString::va("Plugins\\%s", PluginFiles[i].c_str()));

		if (Library != NULL)
		{
			PluginNames.push_back(PluginFiles[i]);
			PluginModules.push_back(Library);
			hConsole::EnqueueMessage("INFO", (char *)PluginFiles[i].c_str(), "", true);
		}
		else
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Failed to load [%s] for reason: %lu", PluginFiles[i].c_str(), GetLastError()), "");
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
		BasePlugin.PreInit         = (uint64_t(__stdcall *)(void))     GetProcAddress(PluginModules[i], "PreInit");
		BasePlugin.PostInit        = (uint64_t(__stdcall *)(void))     GetProcAddress(PluginModules[i], "PostInit");
		BasePlugin.AuthorInfo      = (uint64_t(__stdcall *)(void))     GetProcAddress(PluginModules[i], "AuthorInfo");
		BasePlugin.ExtendedInfo    = (uint64_t(__stdcall *)(void))     GetProcAddress(PluginModules[i], "ExtendedInfo");
		BasePlugin.OfficialMod     = (uint64_t(__stdcall *)(void))     GetProcAddress(PluginModules[i], "OfficialMod");
		BasePlugin.DependencyCount = (uint64_t(__stdcall *)(void))     GetProcAddress(PluginModules[i], "DependencyCount");
		BasePlugin.GetDependency   = (uint64_t(__stdcall *)(int32_t))  GetProcAddress(PluginModules[i], "GetDependency");
		BasePlugin.SendMessageB    = (uint64_t(__stdcall *)(uint64_t)) GetProcAddress(PluginModules[i], "SendMessageB");

		// Verify that all functions were added.
		if (!BasePlugin.PreInit)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "PreInit"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.PostInit)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "PostInit"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.AuthorInfo)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "AuthorInfo"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.ExtendedInfo)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "ExtendedInfo"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.OfficialMod)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "OfficialMod"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.DependencyCount)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "DependencyCount"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.GetDependency)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "GetDependency"), "");
			PurgeList.push_back(i);
			continue;
		}

		if (!BasePlugin.SendMessageB)
		{
			hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing an export (%s) and will be removed.\n", BasePlugin.Name.c_str(), "SendMessageB"), "");
			PurgeList.push_back(i);
			continue;
		}

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
			for (auto k = Plugins.begin(); k != Plugins.end(); ++i)
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
		hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) is missing a dependency (%s) and has been removed.\n", i->first.c_str(), i->second.c_str()), "");
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
		hConsole::EnqueueMessage("ERR", (char *)hString::va("Plugin (%s) could not be verified because %s and has therefore been removed.\n", i->first.c_str(), i->second.c_str()), "");
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

		if (AuthorName == nullptr)
		{
			hConsole::EnqueueMessage("INFO", (char *)hString::va("Loaded plugin <%s>", i->Name.c_str()), "");
		}
		else
		{
			hConsole::EnqueueMessage("INFO", (char *)hString::va("Loaded plugin <%s> by <%s>", i->Name.c_str(), AuthorName), "");
		}
	}
}

// Loads all plugins and verifies them.
void PluginManager::Startup()
{
	// Let the user know we are loading plugins.
	hConsole::EnqueueMessage("INFO", "", "", true);
	hConsole::EnqueueMessage("INFO", "Plugins:", "", true);

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
	hConsole::EnqueueMessage("INFO", "", "", true);
	hConsole::EnqueueMessage("INFO", "Plugins::PreInit:", "", true);

	// Iterate through the vector and call the functionpointers.
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		auto Start = std::chrono::high_resolution_clock::now();
		
		if (i->PreInit() == TRUE)
		{
			hConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> preinit succeeded in %ld msec", i, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Start).count()), "", true);
		}
		else
		{
			// We do not remove the plugin for this.
			// It can still do memory edits if it wants.
			// And it may provide exports for other functions.
			hConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> preinit failed", i), "", true);
		}
	}
}

// Call the postinit function for memory modification.
void PluginManager::PostInit()
{
	// Let the user know we are calling.
	hConsole::EnqueueMessage("INFO", "", "", true);
	hConsole::EnqueueMessage("INFO", "Plugins::PostInit:", "", true);

	// Iterate through the vector and call the functionpointers.
	for (auto i = Plugins.begin(); i != Plugins.end(); ++i)
	{
		auto Start = std::chrono::high_resolution_clock::now();

		if (i->PostInit() == TRUE)
		{
			hConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> postinit succeeded in %ld msec", i, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Start).count()), "", true);
		}
		else
		{
			// We do not remove the plugin for this.
			// It can still do memory edits if it wants.
			// And it may provide exports for other functions.
			hConsole::EnqueueMessage("INFO", (char *)hString::va("Plugin <%s> postinit failed", i), "", true);
		}
	}

	// Start printing our logs.
	hConsole::EnqueueMessage("INFO", "", "", true);
	hConsole::EnqueueMessage("INFO", "Gamelog:", "", true);
	hConsole::StartPrinting();
}
