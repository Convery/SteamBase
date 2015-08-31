/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		Utils.
*/

#include "..\..\StdInclude.h"

UGCQueryHandle_t RedactedUGC::CreateQueryUserUGCRequest(AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
{
	PrintCurrentFunction();
	return NULL;
}

UGCQueryHandle_t RedactedUGC::CreateQueryAllUGCRequest(EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
{
	PrintCurrentFunction();
	return NULL;
}

SteamAPICall_t RedactedUGC::SendQueryUGCRequest(UGCQueryHandle_t handle)
{
	PrintCurrentFunction();
	return NULL;
}

bool RedactedUGC::GetQueryUGCResult(UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::ReleaseQueryUGCRequest(UGCQueryHandle_t handle)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::AddRequiredTag(UGCQueryHandle_t handle, const char *pTagName)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::AddExcludedTag(UGCQueryHandle_t handle, const char *pTagName)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetReturnLongDescription(UGCQueryHandle_t handle, bool bReturnLongDescription)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetAllowCachedResponse(UGCQueryHandle_t handle, uint32 unMaxAgeSeconds)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetCloudFileNameFilter(UGCQueryHandle_t handle, const char *pMatchCloudFileName)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetMatchAnyTag(UGCQueryHandle_t handle, bool bMatchAnyTag)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetSearchText(UGCQueryHandle_t handle, const char *pSearchText)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetRankedByTrendDays(UGCQueryHandle_t handle, uint32 unDays)
{
	PrintCurrentFunction();
	return NULL;
}

SteamAPICall_t RedactedUGC::RequestUGCDetails(PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds)
{
	PrintCurrentFunction();
	return NULL;
}

SteamAPICall_t RedactedUGC::CreateItem(AppId_t nConsumerAppId, EWorkshopFileType eFileType)
{
	PrintCurrentFunction();
	return NULL;
}

UGCUpdateHandle_t RedactedUGC::StartItemUpdate(AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID)
{
	PrintCurrentFunction();
	return NULL;
}

bool RedactedUGC::SetItemTitle(UGCUpdateHandle_t handle, const char *pchTitle)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetItemDescription(UGCUpdateHandle_t handle, const char *pchDescription)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetItemVisibility(UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetItemTags(UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t *pTags)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetItemContent(UGCUpdateHandle_t handle, const char *pszContentFolder)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::SetItemPreview(UGCUpdateHandle_t handle, const char *pszPreviewFile)
{
	PrintCurrentFunction();
	return false;
}

SteamAPICall_t RedactedUGC::SubmitItemUpdate(UGCUpdateHandle_t handle, const char *pchChangeNote)
{
	PrintCurrentFunction();
	return NULL;
}

EItemUpdateStatus RedactedUGC::GetItemUpdateProgress(UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64* punBytesTotal)
{
	PrintCurrentFunction();
	return k_EItemUpdateStatusInvalid;
}

SteamAPICall_t RedactedUGC::SubscribeItem(PublishedFileId_t nPublishedFileID)
{
	PrintCurrentFunction();
	return NULL;
}

SteamAPICall_t RedactedUGC::UnsubscribeItem(PublishedFileId_t nPublishedFileID)
{
	PrintCurrentFunction();
	return NULL;
}

uint32 RedactedUGC::GetNumSubscribedItems()
{
	PrintCurrentFunction();
	return NULL;
}

uint32 RedactedUGC::GetSubscribedItems(PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries)
{
	PrintCurrentFunction();
	return NULL;
}

bool RedactedUGC::GetItemInstallInfo(PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, bool *pbLegacyItem)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedUGC::GetItemUpdateInfo(PublishedFileId_t nPublishedFileID, bool *pbNeedsUpdate, bool *pbIsDownloading, uint64 *punBytesDownloaded, uint64 *punBytesTotal)
{
	PrintCurrentFunction();
	return false;
}
