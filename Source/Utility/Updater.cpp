/*
    This module is licensed under the MIT license.
    Author: (https://github.com/)Convery

    1. Find a file by its name.
    2. Check the filesize, if !=, download it and goto 4.
    3. Check the hash, if !=, download it.
    4. Find any directories in the repo.
    5. Repeat with each dir as relative path.
*/

#include "..\StdInclude.h"

// Item type.
enum class RepoItemType
{
    ITEM_NONE,
    FILE,
    DIRECTORY,
    LINK,
    ITEM_MAX
};

// File metadata.
struct RepoItemMeta
{
    RepoItemType Type;
    std::string Filename;
    uint32_t Filesize;
    uint64_t FileHash;
};

// Collection of metadata for a directory.
struct Repository
{
    std::string RelativePath;
    std::vector<RepoItemMeta> Itemcollection;
};

// Globals related to updating, remember to free them.
std::vector<Repository> MonitoredFolders;
std::vector<std::string> FilesRequiringUpdates;

// Quick file hash.
uint64_t FNV1_64(void *Data, uint32_t Length)
{
    uint64_t Prime = 1099511628211u;
    uint64_t Offset = 14695981039346656037u;

    for (uint32_t i = 0; i < Length; i++)
        Offset = (Offset * Prime) ^ ((uint8_t *)Data)[i];

    return Offset;
}

// Enumerate all files in a folder and check properties.
bool EnumerateFiles_CheckExist(Repository &Folder)
{
    uint32_t InitialSize = FilesRequiringUpdates.size();

    // Check each file.
    for (uint32_t c = 0; c < Folder.Itemcollection.size(); c++)
    {
        if (!Folder.Itemcollection[c].Filename.size())
            continue;

        if (!FileSystem::FileExists(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str())))
        {
            // No duplicates.
            for (uint32_t i = 0; i < InitialSize; i++)
            {
                if (!_stricmp(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str()), FilesRequiringUpdates[i].c_str()))
                    goto LABEL_SKIP_PUSH;
            }

            Folder.Itemcollection[c].Filename.clear();
            FilesRequiringUpdates.push_back(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str()));
            LABEL_SKIP_PUSH:;
        }
    }

    // Return if we have pushed more files.
    return FilesRequiringUpdates.size() > InitialSize;
}
bool EnumerateFiles_CheckSize(Repository &Folder)
{
    uint32_t InitialSize = FilesRequiringUpdates.size();

    // Check each file.
    for (uint32_t c = 0; c < Folder.Itemcollection.size(); c++)
    {
        if (!Folder.Itemcollection[c].Filename.size())
            continue;

        if (Folder.Itemcollection[c].Filesize != FileSystem::GetFileSize(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str())))
        {
            // No duplicates.
            for (uint32_t i = 0; i < InitialSize; i++)
            {
                if (!_stricmp(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str()), FilesRequiringUpdates[i].c_str()))
                    goto LABEL_SKIP_PUSH;
            }

            Folder.Itemcollection[c].Filename.clear();
            FilesRequiringUpdates.push_back(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str()));
            LABEL_SKIP_PUSH:;
        }
    }

    // Return if we have pushed more files.
    return FilesRequiringUpdates.size() > InitialSize;
}
bool EnumerateFiles_CheckHash(Repository &Folder)
{
    uint32_t InitialSize = FilesRequiringUpdates.size();
    ByteString FileBuffer;

    // Check each file.
    for (uint32_t c = 0; c < Folder.Itemcollection.size(); c++)
    {
        if (!Folder.Itemcollection[c].Filename.size())
            continue;

        FileSystem::ReadFile(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str()), FileBuffer);

        if (Folder.Itemcollection[c].FileHash != FNV1_64((void *)FileBuffer.data(), FileBuffer.size()))            
        {
            // No duplicates.
            for (uint32_t i = 0; i < InitialSize; i++)
            {
                if (!_stricmp(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str()), FilesRequiringUpdates[i].c_str()))
                    goto LABEL_SKIP_PUSH;
            }

            Folder.Itemcollection[c].Filename.clear();
            FilesRequiringUpdates.push_back(hString::va("%s\\%s", Folder.RelativePath.c_str(), Folder.Itemcollection[c].Filename.c_str()));
            LABEL_SKIP_PUSH:;
        }

        FileBuffer.clear();
    }

    // Return if we have pushed more files.
    return FilesRequiringUpdates.size() > InitialSize;
}

// File interactions.
bool UpdateFile(std::string Path, ByteString *Data)
{
    // Sanity check.
    if (!FileSystem::FileExists(Path.c_str()))
        return false;

    // Rename the file to get around windows locks.
    std::remove(hString::va("%s.old", Path.c_str()));
    if (!std::rename(Path.c_str(), hString::va("%s.old", Path.c_str())))
        return false;

    // Create a new file with the name and data we want.
    if (!FileSystem::WriteFile(Path.c_str(), *Data, true))
        return false;

    // Remove the old file.
    std::remove(hString::va("%s.old", Path.c_str()));

    return true;
}
bool WriteFile(std::string Path, ByteString *Data)
{
    return FileSystem::WriteFile(Path.c_str(), *Data, true);
}
