/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
		Networking.
*/

#pragma once

class RedactedNetworking
{
public:
	static bool SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType, int istaticPort);
	static bool IsP2PPacketAvailable(uint32 *pcubMsgSize, int istaticPort);
	static bool ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote, int istaticPort);
	static bool AcceptP2PSessionWithUser(CSteamID steamIDRemote);
	static bool CloseP2PSessionWithUser(CSteamID steamIDRemote);
	static bool CloseP2PChannelWithUser(CSteamID steamIDRemote, int istaticPort);
	static bool GetP2PSessionState(CSteamID steamIDRemote, P2PSessionState_t *pConnectionState);
	static bool AllowP2PPacketRelay(bool bAllow);

	static SNetListenSocket_t CreateListenSocket(int nstaticP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay);
	static SNetSocket_t CreateP2PConnectionSocket(CSteamID steamIDTarget, int nstaticPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
	static SNetSocket_t CreateConnectionSocket(uint32 nIP, uint16 nPort, int nTimeoutSec);
	static bool DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd);
	static bool DestroyListenSocket(SNetListenSocket_t hSocket, bool bNotifyRemoteEnd);
	static bool SendDataOnSocket(SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable);
	static bool IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32 *pcubMsgSize);
	static bool RetrieveDataFromSocket(SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize);
	static bool IsDataAvailable(SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket);
	static bool RetrieveData(SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket);
	static bool GetSocketInfo(SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote);
	static bool GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort);
	static ESNetSocketConnectionType GetSocketConnectionType(SNetSocket_t hSocket);
	static int GetMaxPacketSize(SNetSocket_t hSocket);
};
