/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
*/

#include "..\..\StdInclude.h"

#pragma region SteamUGC001

#pragma endregion

#pragma region SteamUGC002

#pragma endregion

#pragma region SteamUGC003

UGCQueryHandle_t SteamUGC003::CreateQueryUserUGCRequest(AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
{
	return RedactedUGC::CreateQueryUserUGCRequest(unAccountID, eListType, eMatchingUGCType, eSortOrder, nCreatorAppID, nConsumerAppID, unPage);
}

UGCQueryHandle_t SteamUGC003::CreateQueryAllUGCRequest(EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
{
	return RedactedUGC::CreateQueryAllUGCRequest(eQueryType, eMatchingeMatchingUGCTypeFileType, nCreatorAppID, nConsumerAppID, unPage);
}

SteamAPICall_t SteamUGC003::SendQueryUGCRequest(UGCQueryHandle_t handle)
{
	return RedactedUGC::SendQueryUGCRequest(handle);
}

bool SteamUGC003::GetQueryUGCResult(UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails)
{
	return RedactedUGC::GetQueryUGCResult(handle, index, pDetails);
}

bool SteamUGC003::ReleaseQueryUGCRequest(UGCQueryHandle_t handle)
{
	return RedactedUGC::ReleaseQueryUGCRequest(handle);
}

bool SteamUGC003::AddRequiredTag(UGCQueryHandle_t handle, const char *pTagName)
{
	return RedactedUGC::AddRequiredTag(handle, pTagName);
}

bool SteamUGC003::AddExcludedTag(UGCQueryHandle_t handle, const char *pTagName)
{
	return RedactedUGC::AddExcludedTag(handle, pTagName);
}

bool SteamUGC003::SetReturnLongDescription(UGCQueryHandle_t handle, bool bReturnLongDescription)
{
	return RedactedUGC::SetReturnLongDescription(handle, bReturnLongDescription);
}

bool SteamUGC003::SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly)
{
	return RedactedUGC::SetReturnTotalOnly(handle, bReturnTotalOnly);
}

bool SteamUGC003::SetAllowCachedResponse(UGCQueryHandle_t handle, uint32 unMaxAgeSeconds)
{
	return RedactedUGC::SetAllowCachedResponse(handle, unMaxAgeSeconds);
}

bool SteamUGC003::SetCloudFileNameFilter(UGCQueryHandle_t handle, const char *pMatchCloudFileName)
{
	return RedactedUGC::SetCloudFileNameFilter(handle, pMatchCloudFileName);
}

bool SteamUGC003::SetMatchAnyTag(UGCQueryHandle_t handle, bool bMatchAnyTag)
{
	return RedactedUGC::SetMatchAnyTag(handle, bMatchAnyTag);
}

bool SteamUGC003::SetSearchText(UGCQueryHandle_t handle, const char *pSearchText)
{
	return RedactedUGC::SetSearchText(handle, pSearchText);
}

bool SteamUGC003::SetRankedByTrendDays(UGCQueryHandle_t handle, uint32 unDays)
{
	return RedactedUGC::SetRankedByTrendDays(handle, unDays);
}

SteamAPICall_t SteamUGC003::RequestUGCDetails(PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds)
{
	return RedactedUGC::RequestUGCDetails(nPublishedFileID, unMaxAgeSeconds);
}

SteamAPICall_t SteamUGC003::CreateItem(AppId_t nConsumerAppId, EWorkshopFileType eFileType)
{
	return RedactedUGC::CreateItem(nConsumerAppId, eFileType);
}

UGCUpdateHandle_t SteamUGC003::StartItemUpdate(AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID)
{
	return RedactedUGC::StartItemUpdate(nConsumerAppId, nPublishedFileID);
}

bool SteamUGC003::SetItemTitle(UGCUpdateHandle_t handle, const char *pchTitle)
{
	return RedactedUGC::SetItemTitle(handle, pchTitle);
}

bool SteamUGC003::SetItemDescription(UGCUpdateHandle_t handle, const char *pchDescription)
{
	return RedactedUGC::SetItemDescription(handle, pchDescription);
}

bool SteamUGC003::SetItemVisibility(UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility)
{
	return RedactedUGC::SetItemVisibility(handle, eVisibility);
}

bool SteamUGC003::SetItemTags(UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t *pTags)
{
	return RedactedUGC::SetItemTags(updateHandle, pTags);
}

bool SteamUGC003::SetItemContent(UGCUpdateHandle_t handle, const char *pszContentFolder)
{
	return RedactedUGC::SetItemContent(handle, pszContentFolder);
}

bool SteamUGC003::SetItemPreview(UGCUpdateHandle_t handle, const char *pszPreviewFile)
{
	return RedactedUGC::SetItemPreview(handle, pszPreviewFile);
}

SteamAPICall_t SteamUGC003::SubmitItemUpdate(UGCUpdateHandle_t handle, const char *pchChangeNote)
{
	return RedactedUGC::SubmitItemUpdate(handle, pchChangeNote);
}

EItemUpdateStatus SteamUGC003::GetItemUpdateProgress(UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64* punBytesTotal)
{
	return RedactedUGC::GetItemUpdateProgress(handle, punBytesProcessed, punBytesTotal);
}

SteamAPICall_t SteamUGC003::SubscribeItem(PublishedFileId_t nPublishedFileID)
{
	return RedactedUGC::SubscribeItem(nPublishedFileID);
}

SteamAPICall_t SteamUGC003::UnsubscribeItem(PublishedFileId_t nPublishedFileID)
{
	return RedactedUGC::UnsubscribeItem(nPublishedFileID);
}

uint32 SteamUGC003::GetNumSubscribedItems()
{
	return RedactedUGC::GetNumSubscribedItems();
}

uint32 SteamUGC003::GetSubscribedItems(PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries)
{
	return RedactedUGC::GetSubscribedItems(pvecPublishedFileID, cMaxEntries);
}

bool SteamUGC003::GetItemInstallInfo(PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, bool *pbLegacyItem)
{
	return RedactedUGC::GetItemInstallInfo(nPublishedFileID, punSizeOnDisk, pchFolder, cchFolderSize, pbLegacyItem);
}

bool SteamUGC003::GetItemUpdateInfo(PublishedFileId_t nPublishedFileID, bool *pbNeedsUpdate, bool *pbIsDownloading, uint64 *punBytesDownloaded, uint64 *punBytesTotal)
{
	return RedactedUGC::GetItemUpdateInfo(nPublishedFileID, pbNeedsUpdate, pbIsDownloading, punBytesDownloaded, punBytesTotal);
}

#pragma endregion

#pragma region SteamUGC004

#pragma endregion

#pragma region SteamUGC005

#pragma endregion

#pragma region SteamUGC006

#pragma endregion

#pragma region SteamUGC007

#pragma endregion