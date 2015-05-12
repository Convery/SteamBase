/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Sokie
	Started: 2015-04-28
	Notes:
	Remote storage class.
*/

#include "..\..\StdInclude.h"

bool RedactedRemoteStorage::FileWrite( const char *pchFile, const void *pvData, int32 cubData )
{
     PrintCurrentFunction();
	 std::string FilePath;

	 FilePath.append("Storage\\");
	 FilePath.append(pchFile);
	 FileSystem::WriteFile(FilePath.c_str(), (void *)pvData, cubData, false);

    return true;
}
int32 RedactedRemoteStorage::FileRead( const char *pchFile, void *pvData, int32 cubDataToRead )
{
     PrintCurrentFunction();

	 std::string FilePath;
	 ByteString Buffer;

	 FilePath.append("Storage\\");
	 FilePath.append(pchFile);

	 FileSystem::ReadFile(FilePath.c_str(), Buffer);

	 memcpy(pvData, Buffer.data(), min(cubDataToRead, Buffer.length()));

	 return min(cubDataToRead, Buffer.length());
}
bool RedactedRemoteStorage::FileForget( const char *pchFile )
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::FileDelete( const char *pchFile )
{
     PrintCurrentFunction();
    return true;
}
SteamAPICall_t RedactedRemoteStorage::FileShare( const char *pchFile )
{
     PrintCurrentFunction();
    return NULL;
}
bool RedactedRemoteStorage::SetSyncPlatforms( const char *pchFile, ERemoteStoragePlatform eRemoteStoragePlatform )
{
     PrintCurrentFunction();
    return true;
}

GID_t RedactedRemoteStorage::FileWriteStreamOpen( const char *pchFile )
{
     PrintCurrentFunction();
    return NULL;
}
EResult RedactedRemoteStorage::FileWriteStreamWriteChunk( GID_t hStream, const void *pvData, int32 cubData )
{
     PrintCurrentFunction();
    return EResult::k_EResultOK;
}
EResult RedactedRemoteStorage::FileWriteStreamClose( GID_t hStream )
{
     PrintCurrentFunction();
    return EResult::k_EResultOK;
}
EResult RedactedRemoteStorage::FileWriteStreamCancel( GID_t hStream )
{
     PrintCurrentFunction();
    return EResult::k_EResultOK;
}

// file information
bool RedactedRemoteStorage::FileExists( const char *pchFile )
{
	std::string FilePath;

	FilePath.append("Storage\\");
	FilePath.append(pchFile);

	return (GetFileAttributesA(FilePath.c_str()) != INVALID_FILE_ATTRIBUTES);
}
bool RedactedRemoteStorage::FilePersisted( const char *pchFile )
{
     PrintCurrentFunction();
    return true;
}
int32 RedactedRemoteStorage::GetFileSize( const char *pchFile )
{
	PrintCurrentFunction();
	std::string FilePath;

	FilePath.append("Storage\\");
	FilePath.append(pchFile);

	return FileSystem::GetFileSize(FilePath.c_str());
}
int64 RedactedRemoteStorage::GetFileTimestamp( const char *pchFile )
{
     PrintCurrentFunction();
    return 0;
}
ERemoteStoragePlatform RedactedRemoteStorage::GetSyncPlatforms( const char *pchFile )
{
     PrintCurrentFunction();
	return ERemoteStoragePlatform::k_ERemoteStoragePlatformAll;
}

// iteration
int32 RedactedRemoteStorage::GetFileCount()
{
     PrintCurrentFunction();
    return 0;
}
const char *RedactedRemoteStorage::GetFileNameAndSize( int iFile, int32 *pnFileSizeInBytes )
{
     PrintCurrentFunction();
    return "";
}

// configuration management
bool RedactedRemoteStorage::GetQuota( int32 *pnTotalBytes, int32 *puAvailableBytes )
{
	PrintCurrentFunction();
	*pnTotalBytes = 0x10000000;
	*puAvailableBytes = 0x10000000;

	return true;
}
bool RedactedRemoteStorage::IsCloudEnabledForAccount()
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::IsCloudEnabledForApp()
{
     PrintCurrentFunction();
    return true;
}
void RedactedRemoteStorage::SetCloudEnabledForApp( bool bEnabled )
{
     PrintCurrentFunction();
}

// user generated content
SteamAPICall_t RedactedRemoteStorage::UGCDownload( UGCHandle_t hContent, uint32 uUnk )
{
     PrintCurrentFunction();
    return NULL;
} // Returns a RemoteStorageDownloadUGCResult_t callback

bool RedactedRemoteStorage::GetUGCDownloadProgress( UGCHandle_t hContent, uint32 *puDownloadedBytes, uint32 *puTotalBytes )
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::GetUGCDetails( UGCHandle_t hContent, AppId_t *pnAppID, char **ppchName, int32 *pnFileSizeInBytes, CSteamID *pSteamIDOwner )
{
     PrintCurrentFunction();
    return true;
}
int32 RedactedRemoteStorage::UGCRead( UGCHandle_t hContent, void *pvData, int32 cubDataToRead, uint32 uOffset, EUGCReadAction eAction )
{
     PrintCurrentFunction();
    return 0;
}

// user generated content iteration
int32 RedactedRemoteStorage::GetCachedUGCCount()
{
     PrintCurrentFunction();
    return 0;
}
UGCHandle_t RedactedRemoteStorage::GetCachedUGCHandle( int32 iCachedContent )
{
     PrintCurrentFunction();
    return true;
}

// publishing UGC
SteamAPICall_t RedactedRemoteStorage::PublishWorkshopFile( const char *pchFile, const char *pchPreviewFile, AppId_t nConsumerAppId, const char *pchTitle, const char *pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags, EWorkshopFileType eWorkshopFileType )
{
     PrintCurrentFunction();
    return NULL;
}
JobID_t RedactedRemoteStorage::CreatePublishedFileUpdateRequest( PublishedFileId_t unPublishedFileId )
{
     PrintCurrentFunction();
    return NULL;
}
bool RedactedRemoteStorage::UpdatePublishedFileFile( JobID_t hUpdateRequest, const char *pchFile )
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::UpdatePublishedFilePreviewFile( JobID_t hUpdateRequest, const char *pchPreviewFile )
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::UpdatePublishedFileTitle( JobID_t hUpdateRequest, const char *pchTitle )
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::UpdatePublishedFileDescription( JobID_t hUpdateRequest, const char *pchDescription )
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::UpdatePublishedFileVisibility( JobID_t hUpdateRequest, ERemoteStoragePublishedFileVisibility eVisibility )
{
     PrintCurrentFunction();
    return true;
}
bool RedactedRemoteStorage::UpdatePublishedFileTags( JobID_t hUpdateRequest, SteamParamStringArray_t *pTags )
{
     PrintCurrentFunction();
    return true;
}
SteamAPICall_t RedactedRemoteStorage::CommitPublishedFileUpdate( JobID_t hUpdateRequest )
{
     PrintCurrentFunction();
    return NULL;
}

SteamAPICall_t RedactedRemoteStorage::GetPublishedFileDetails( PublishedFileId_t unPublishedFileId, uint32 )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::DeletePublishedFile( PublishedFileId_t unPublishedFileId )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::EnumerateUserPublishedFiles( uint32 uStartIndex )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::SubscribePublishedFile( PublishedFileId_t unPublishedFileId )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::EnumerateUserSubscribedFiles( uint32 uStartIndex )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::UnsubscribePublishedFile( PublishedFileId_t unPublishedFileId )
{
     PrintCurrentFunction();
    return NULL;
}

bool RedactedRemoteStorage::UpdatePublishedFileSetChangeDescription( JobID_t hUpdateRequest, const char *cszDescription )
{
     PrintCurrentFunction();
    return true;
}
SteamAPICall_t RedactedRemoteStorage::GetPublishedItemVoteDetails( PublishedFileId_t unPublishedFileId )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::UpdateUserPublishedItemVote( PublishedFileId_t unPublishedFileId, bool bVoteUp )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::GetUserPublishedItemVoteDetails( PublishedFileId_t unPublishedFileId )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::EnumerateUserSharedWorkshopFiles( AppId_t nAppId, CSteamID creatorSteamID, uint32 uStartIndex, SteamParamStringArray_t * pRequiredTags, SteamParamStringArray_t * pExcludedTags )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::PublishVideo( EWorkshopVideoProvider eVideoProvider, const char *cszVideoAccountName, const char *cszVideoIdentifier, const char *cszFileName, AppId_t nConsumerAppId, const char *cszTitle, const char *cszDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t *pTags )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::SetUserPublishedFileAction( PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::EnumeratePublishedFilesByUserAction( EWorkshopFileAction eAction, uint32 uStartIndex )
{
     PrintCurrentFunction();
    return NULL;
}
SteamAPICall_t RedactedRemoteStorage::EnumeratePublishedWorkshopFiles( EWorkshopEnumerationType eType, uint32 uStartIndex, uint32 cDays, uint32 cCount, SteamParamStringArray_t *pTags, SteamParamStringArray_t *pUserTags )
{
     PrintCurrentFunction();
    return NULL;
}

SteamAPICall_t RedactedRemoteStorage::UGCDownloadToLocation( UGCHandle_t hContent, const char *cszLocation, uint32 uUnk )
{
     PrintCurrentFunction();
    return NULL;
}