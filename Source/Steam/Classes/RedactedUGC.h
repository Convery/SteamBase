/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		Utils.
*/

#pragma once

class RedactedUGC
{
public:
	static UGCQueryHandle_t CreateQueryUserUGCRequest(AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
	static UGCQueryHandle_t CreateQueryAllUGCRequest(EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
	static SteamAPICall_t SendQueryUGCRequest(UGCQueryHandle_t handle);
	static bool GetQueryUGCResult(UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails);
	static bool ReleaseQueryUGCRequest(UGCQueryHandle_t handle);
	static bool AddRequiredTag(UGCQueryHandle_t handle, const char *pTagName);
	static bool AddExcludedTag(UGCQueryHandle_t handle, const char *pTagName);
	static bool SetReturnLongDescription(UGCQueryHandle_t handle, bool bReturnLongDescription);
	static bool SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly);
	static bool SetAllowCachedResponse(UGCQueryHandle_t handle, uint32 unMaxAgeSeconds);
	static bool SetCloudFileNameFilter(UGCQueryHandle_t handle, const char *pMatchCloudFileName);
	static bool SetMatchAnyTag(UGCQueryHandle_t handle, bool bMatchAnyTag);
	static bool SetSearchText(UGCQueryHandle_t handle, const char *pSearchText);
	static bool SetRankedByTrendDays(UGCQueryHandle_t handle, uint32 unDays);
	static SteamAPICall_t RequestUGCDetails(PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds);
	static SteamAPICall_t CreateItem(AppId_t nConsumerAppId, EWorkshopFileType eFileType);
	static UGCUpdateHandle_t StartItemUpdate(AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID);
	static bool SetItemTitle(UGCUpdateHandle_t handle, const char *pchTitle);
	static bool SetItemDescription(UGCUpdateHandle_t handle, const char *pchDescription);
	static bool SetItemVisibility(UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility);
	static bool SetItemTags(UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t *pTags);
	static bool SetItemContent(UGCUpdateHandle_t handle, const char *pszContentFolder);
	static bool SetItemPreview(UGCUpdateHandle_t handle, const char *pszPreviewFile);
	static SteamAPICall_t SubmitItemUpdate(UGCUpdateHandle_t handle, const char *pchChangeNote);
	static EItemUpdateStatus GetItemUpdateProgress(UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64* punBytesTotal);
	static SteamAPICall_t SubscribeItem(PublishedFileId_t nPublishedFileID);
	static SteamAPICall_t UnsubscribeItem(PublishedFileId_t nPublishedFileID);
	static uint32 GetNumSubscribedItems();
	static uint32 GetSubscribedItems(PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries);
	static bool GetItemInstallInfo(PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, bool *pbLegacyItem);
	static bool GetItemUpdateInfo(PublishedFileId_t nPublishedFileID, bool *pbNeedsUpdate, bool *pbIsDownloading, uint64 *punBytesDownloaded, uint64 *punBytesTotal);
};
