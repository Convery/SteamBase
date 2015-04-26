/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
*/

#pragma once

#include "..\..\StdInclude.h"

#pragma region SteamNetworking001

#pragma endregion

#pragma region SteamNetworking002

#pragma endregion

#pragma region SteamNetworking003

#pragma endregion

#pragma region SteamNetworking004

#pragma endregion

#pragma region SteamNetworking005

class SteamNetworking005 : public ISteamNetworking005
{
public:
	bool SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType, int istaticPort);
	bool IsP2PPacketAvailable(uint32 *pcubMsgSize, int istaticPort);
	bool ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote, int istaticPort);
	bool AcceptP2PSessionWithUser(CSteamID steamIDRemote);
	bool CloseP2PSessionWithUser(CSteamID steamIDRemote);
	bool CloseP2PChannelWithUser(CSteamID steamIDRemote, int istaticPort);
	bool GetP2PSessionState(CSteamID steamIDRemote, P2PSessionState_t *pConnectionState);
	bool AllowP2PPacketRelay(bool bAllow);

	SNetListenSocket_t CreateListenSocket(int nstaticP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay);
	SNetSocket_t CreateP2PConnectionSocket(CSteamID steamIDTarget, int nstaticPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
	SNetSocket_t CreateConnectionSocket(uint32 nIP, uint16 nPort, int nTimeoutSec);
	bool DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd);
	bool DestroyListenSocket(SNetListenSocket_t hSocket, bool bNotifyRemoteEnd);
	bool SendDataOnSocket(SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable);
	bool IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32 *pcubMsgSize);
	bool RetrieveDataFromSocket(SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize);
	bool IsDataAvailable(SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket);
	bool RetrieveData(SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket);
	bool GetSocketInfo(SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote);
	bool GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort);
	ESNetSocketConnectionType GetSocketConnectionType(SNetSocket_t hSocket);
	int GetMaxPacketSize(SNetSocket_t hSocket);
};

#pragma endregion