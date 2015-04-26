/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Information about the application.
*/

#include "..\..\StdInclude.h"

static const int defaultPort = 31313;

bool RedactedNetworking::SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType, int iPort)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType)
 {
	 PrintCurrentFunction();
	 return RedactedNetworking::SendP2PPacket(steamIDRemote, pubData, cubData, eP2PSendType, defaultPort);
 }

bool RedactedNetworking::IsP2PPacketAvailable(uint32 *pcubMsgSize, int iPort)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::IsP2PPacketAvailable(uint32 *pcubMsgSize)
 {
	 PrintCurrentFunction();
	 return RedactedNetworking::IsP2PPacketAvailable(pcubMsgSize, defaultPort);
 }


bool RedactedNetworking::ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote)
{
	PrintCurrentFunction();
	return false;
}

bool RedactedNetworking::ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote, int iPort)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::AcceptP2PSessionWithUser(CSteamID steamIDRemote)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::CloseP2PSessionWithUser(CSteamID steamIDRemote)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::CloseP2PChannelWithUser(CSteamID steamIDRemote, int iPort)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::GetP2PSessionState(CSteamID steamIDRemote, P2PSessionState_t *pConnectionState)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::AllowP2PPacketRelay(bool bAllow)
 {
	 PrintCurrentFunction();
	 return false;
 }

SNetListenSocket_t RedactedNetworking::CreateListenSocket(int nP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay)
 {
	 PrintCurrentFunction();
	 return NULL;
 }

SNetSocket_t RedactedNetworking::CreateP2PConnectionSocket(CSteamID steamIDTarget, int nPort, int nTimeoutSec, bool bAllowUseOfPacketRelay)
 {
	 PrintCurrentFunction();
	 return NULL;
 }
SNetSocket_t RedactedNetworking::CreateConnectionSocket(uint32 nIP, uint16 nPort, int nTimeoutSec)
 {
	 PrintCurrentFunction();
	 return NULL;
 }


bool RedactedNetworking::DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::DestroyListenSocket(SNetListenSocket_t hSocket, bool bNotifyRemoteEnd)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::SendDataOnSocket(SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32 *pcubMsgSize)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::RetrieveDataFromSocket(SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::IsDataAvailable(SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::RetrieveData(SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::GetSocketInfo(SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote)
 {
	 PrintCurrentFunction();
	 return false;
 }

bool RedactedNetworking::GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort)
 {
	 PrintCurrentFunction();
	 return false;
 }

ESNetSocketConnectionType RedactedNetworking::GetSocketConnectionType(SNetSocket_t hSocket)
 {
	 PrintCurrentFunction();
	 return k_ESNetSocketConnectionTypeNotConnected;
 }

int RedactedNetworking::GetMaxPacketSize(SNetSocket_t hSocket)
 {
	 PrintCurrentFunction();
	 return 0;
 }