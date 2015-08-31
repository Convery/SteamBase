/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
*/

#pragma once

#pragma region SteamUGC001

#pragma endregion

#pragma region SteamUGC002

#pragma endregion

#pragma region SteamUGC003

class SteamUGC003 : public ISteamUGC003
{
public:

	// Query UGC associated with a user. Creator app id or consumer app id must be valid and be set to the current running app. unPage should start at 1.
	UGCQueryHandle_t CreateQueryUserUGCRequest(AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);

	// Query for all matching UGC. Creator app id or consumer app id must be valid and be set to the current running app. unPage should start at 1.
	UGCQueryHandle_t CreateQueryAllUGCRequest(EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);

	// Send the query to Steam
	SteamAPICall_t SendQueryUGCRequest(UGCQueryHandle_t handle);

	// Retrieve an individual result after receiving the callback for querying UGC
	bool GetQueryUGCResult(UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t *pDetails);

	// Release the request to free up memory, after retrieving results
	bool ReleaseQueryUGCRequest(UGCQueryHandle_t handle);

	// Options to set for querying UGC
	bool AddRequiredTag(UGCQueryHandle_t handle, const char *pTagName);
	bool AddExcludedTag(UGCQueryHandle_t handle, const char *pTagName);
	bool SetReturnLongDescription(UGCQueryHandle_t handle, bool bReturnLongDescription);
	bool SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly);
	bool SetAllowCachedResponse(UGCQueryHandle_t handle, uint32 unMaxAgeSeconds);

	// Options only for querying user UGC
	bool SetCloudFileNameFilter(UGCQueryHandle_t handle, const char *pMatchCloudFileName);

	// Options only for querying all UGC
	bool SetMatchAnyTag(UGCQueryHandle_t handle, bool bMatchAnyTag);
	bool SetSearchText(UGCQueryHandle_t handle, const char *pSearchText);
	bool SetRankedByTrendDays(UGCQueryHandle_t handle, uint32 unDays);

	// Request full details for one piece of UGC
	SteamAPICall_t RequestUGCDetails(PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds);

	// Steam Workshop Creator API
	SteamAPICall_t CreateItem(AppId_t nConsumerAppId, EWorkshopFileType eFileType); // create new item for this app with no content attached yet

	UGCUpdateHandle_t StartItemUpdate(AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID); // start an UGC item update. Set changed properties before commiting update with CommitItemUpdate()

	bool SetItemTitle(UGCUpdateHandle_t handle, const char *pchTitle); // change the title of an UGC item
	bool SetItemDescription(UGCUpdateHandle_t handle, const char *pchDescription); // change the description of an UGC item
	bool SetItemVisibility(UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility); // change the visibility of an UGC item
	bool SetItemTags(UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t *pTags); // change the tags of an UGC item
	bool SetItemContent(UGCUpdateHandle_t handle, const char *pszContentFolder); // update item content from this local folder
	bool SetItemPreview(UGCUpdateHandle_t handle, const char *pszPreviewFile); //  change preview image file for this item. pszPreviewFile points to local image file, which must be under 1MB in size

	SteamAPICall_t SubmitItemUpdate(UGCUpdateHandle_t handle, const char *pchChangeNote); // commit update process started with StartItemUpdate()
	EItemUpdateStatus GetItemUpdateProgress(UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64* punBytesTotal);

	// Steam Workshop Consumer API
	SteamAPICall_t SubscribeItem(PublishedFileId_t nPublishedFileID); // subscript to this item, will be installed ASAP
	SteamAPICall_t UnsubscribeItem(PublishedFileId_t nPublishedFileID); // unsubscribe from this item, will be uninstalled after game quits
	uint32 GetNumSubscribedItems(); // number of subscribed items 
	uint32 GetSubscribedItems(PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries); // all subscribed item PublishFileIDs

	// Get info about the item on disk.  If you are supporting items published through the legacy RemoteStorage APIs then *pbLegacyItem will be set to true
	// and pchFolder will contain the full path to the file rather than the containing folder.
	bool GetItemInstallInfo(PublishedFileId_t nPublishedFileID, uint64 *punSizeOnDisk, char *pchFolder, uint32 cchFolderSize, bool *pbLegacyItem); // returns true if item is installed
	bool GetItemUpdateInfo(PublishedFileId_t nPublishedFileID, bool *pbNeedsUpdate, bool *pbIsDownloading, uint64 *punBytesDownloaded, uint64 *punBytesTotal);
};

#pragma endregion

#pragma region SteamUGC004

#pragma endregion

#pragma region SteamUGC005

#pragma endregion

#pragma region SteamUGC006

#pragma endregion

#pragma region SteamUGC007

#pragma endregion