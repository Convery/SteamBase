/*
	This project is released under the GPL 2.0 license.
	Some parts are based on research by Bas Timmer and the OpenSteamworks project.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2014-11-04
	Notes:
*/

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

// Session-less connection.
bool SteamNetworking005::SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType, int istaticPort)
{
	return RedactedNetworking::SendP2PPacket(steamIDRemote, pubData, cubData, eP2PSendType, istaticPort);
}
bool SteamNetworking005::IsP2PPacketAvailable(uint32_t *pcubMsgSize, int iVirtualPort)
{
	return RedactedNetworking::IsP2PPacketAvailable(pcubMsgSize, iVirtualPort);
}
bool SteamNetworking005::ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote, int istaticPort)
{
	return RedactedNetworking::ReadP2PPacket(pubDest, cubDest, pcubMsgSize, psteamIDRemote, istaticPort);
}

bool SteamNetworking005::AcceptP2PSessionWithUser(CSteamID steamIDRemote)
{
	return RedactedNetworking::AcceptP2PSessionWithUser(steamIDRemote);
}
bool SteamNetworking005::CloseP2PSessionWithUser(CSteamID steamIDRemote)
{
	return RedactedNetworking::CloseP2PSessionWithUser(steamIDRemote);
}
bool SteamNetworking005::CloseP2PChannelWithUser(CSteamID steamIDRemote, int iVirtualPort)
{
	return RedactedNetworking::CloseP2PChannelWithUser(steamIDRemote, iVirtualPort);
}
bool SteamNetworking005::GetP2PSessionState(CSteamID steamIDRemote, P2PSessionState_t *pConnectionState)
{
	return RedactedNetworking::GetP2PSessionState(steamIDRemote, pConnectionState);
}
bool SteamNetworking005::AllowP2PPacketRelay(bool bAllow)
{
	return RedactedNetworking::AllowP2PPacketRelay(bAllow);
}

// Listen / connect style interface.
SNetListenSocket_t SteamNetworking005::CreateListenSocket(int nstaticP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay)
{
	return RedactedNetworking::CreateListenSocket(nstaticP2PPort, nIP, nPort, bAllowUseOfPacketRelay);
}
SNetSocket_t SteamNetworking005::CreateP2PConnectionSocket(CSteamID steamIDTarget, int nstaticPort, int nTimeoutSec, bool bAllowUseOfPacketRelay)
{
	return RedactedNetworking::CreateP2PConnectionSocket(steamIDTarget, nstaticPort, nTimeoutSec, bAllowUseOfPacketRelay);
}
SNetSocket_t SteamNetworking005::CreateConnectionSocket(uint32 nIP, uint16 nPort, int nTimeoutSec)
{
	return RedactedNetworking::CreateConnectionSocket(nIP, nPort, nTimeoutSec);
}
bool SteamNetworking005::DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd)
{
	return RedactedNetworking::DestroySocket(hSocket, bNotifyRemoteEnd);
}
bool SteamNetworking005::DestroyListenSocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd)
{
	return RedactedNetworking::DestroyListenSocket(hSocket, bNotifyRemoteEnd);
}

bool SteamNetworking005::SendDataOnSocket(SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable)
{
	return RedactedNetworking::SendDataOnSocket(hSocket, pubData, cubData, bReliable);
}
bool SteamNetworking005::IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32 *pcubMsgSize)
{
	return RedactedNetworking::IsDataAvailableOnSocket(hSocket, pcubMsgSize);
}
bool SteamNetworking005::RetrieveDataFromSocket(SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize)
{
	return RedactedNetworking::RetrieveDataFromSocket(hSocket, pubDest, cubDest, pcubMsgSize);
}
bool SteamNetworking005::IsDataAvailable(SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
{
	return RedactedNetworking::IsDataAvailable(hListenSocket, pcubMsgSize, phSocket);
}

bool SteamNetworking005::RetrieveData(SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
{
	return RedactedNetworking::RetrieveData(hListenSocket, pubDest, cubDest, pcubMsgSize, phSocket);
}
bool SteamNetworking005::GetSocketInfo(SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote)
{
	return RedactedNetworking::GetSocketInfo(hSocket, pSteamIDRemote, peSocketStatus, punIPRemote, punPortRemote);
}
bool SteamNetworking005::GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort)
{
	return RedactedNetworking::GetListenSocketInfo(hListenSocket, pnIP, pnPort);
}
ESNetSocketConnectionType SteamNetworking005::GetSocketConnectionType(SNetSocket_t hSocket)
{
	return RedactedNetworking::GetSocketConnectionType(hSocket);
}
int SteamNetworking005::GetMaxPacketSize(SNetSocket_t hSocket)
{
	return RedactedNetworking::GetMaxPacketSize(hSocket);
}

#pragma endregion