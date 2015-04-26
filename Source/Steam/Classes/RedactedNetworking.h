/*
	This project is released under the GPL 2.0 license.
	Please do no evil.

	Initial author: (https://github.com/)Convery
	Started: 2015-04-08
	Notes:
		Information about the application.
*/

#pragma once

class RedactedNetworking
{
public:
	static bool SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType, int iPort);
	//send p2p packet on default port
	static bool SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType);

	// returns true if any data is available for read, and the amount of data that will need to be read
	static bool IsP2PPacketAvailable(uint32 *pcubMsgSize, int iPort);
	//IsP2PPacketAvailable packet on default port
	static bool IsP2PPacketAvailable(uint32 *pcubMsgSize);

	// reads in a packet that has been sent from another user via SendP2PPacket()
	// returns the size of the message and the steamID of the user who sent it in the last two parameters
	// if the buffer passed in is too small, the message will be truncated
	// this call is not blocking, and will return false if no data is available
	static bool ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote, int iPort);
	//read on default port
	static bool ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote);

	// AcceptP2PSessionWithUser() should only be called in response to a P2PSessionRequest_t callback
	// P2PSessionRequest_t will be posted if another user tries to send you a packet that you haven't talked to yet
	// if you don't want to talk to the user, just ignore the request
	// if the user continues to send you packets, another P2PSessionRequest_t will be posted periodically
	// this may be called multiple times for a single user
	// (if you've called SendP2PPacket() on the other user, this implicitly accepts the session request)
	static bool AcceptP2PSessionWithUser(CSteamID steamIDRemote);

	// call CloseP2PSessionWithUser() when you're done talking to a user, will free up resources under-the-hood
	// if the remote user tries to send data to you again, another P2PSessionRequest_t callback will be posted
	static bool CloseP2PSessionWithUser(CSteamID steamIDRemote);

	static bool CloseP2PChannelWithUser(CSteamID steamIDRemote, int iPort);

	// fills out P2PSessionState_t structure with details about the underlying connection to the user
	// should only needed for debugging purposes
	// returns false if no connection exists to the specified user
	static bool GetP2PSessionState(CSteamID steamIDRemote, P2PSessionState_t *pConnectionState);

	static bool AllowP2PPacketRelay(bool bAllow);

	////////////////////////////////////////////////////////////////////////////////////////////
	// LISTEN / CONNECT style interface functions
	//
	// This is an older set of functions designed around the Berkeley TCP sockets model
	// it's preferential that you use the above P2P functions, they're more robust
	// and these older functions will be removed eventually
	//
	////////////////////////////////////////////////////////////////////////////////////////////


	// creates a socket and listens others to connect
	// will trigger a SocketStatusCallback_t callback on another client connecting
	// nP2PPort is the unique ID that the client will connect to, in case you have multiple ports
	//		this can usually just be 0 unless you want multiple sets of connections
	// unIP is the local IP address to bind to
	//		pass in 0 if you just want the default local IP
	// unPort is the port to use
	//		pass in 0 if you don't want users to be able to connect via IP/Port, but expect to be always peer-to-peer connections only
	static SNetListenSocket_t CreateListenSocket(int nP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay);

	// creates a socket and begin connection to a remote destination
	// can connect via a known steamID (client or game server), or directly to an IP
	// on success will trigger a SocketStatusCallback_t callback
	// on failure or timeout will trigger a SocketStatusCallback_t callback with a failure code in m_eSNetSocketState
	static SNetSocket_t CreateP2PConnectionSocket(CSteamID steamIDTarget, int nPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
	static SNetSocket_t CreateConnectionSocket(uint32 nIP, uint16 nPort, int nTimeoutSec);

	// disconnects the connection to the socket, if any, and invalidates the handle
	// any unread data on the socket will be thrown away
	// if bNotifyRemoteEnd is set, socket will not be completely destroyed until the remote end acknowledges the disconnect
	static bool DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd);
	// destroying a listen socket will automatically kill all the regular sockets generated from it
	static bool DestroyListenSocket(SNetListenSocket_t hSocket, bool bNotifyRemoteEnd);

	// sending data
	// must be a handle to a connected socket
	// data is all sent via UDP, and thus send sizes are limited to 1200 bytes; after this, many routers will start dropping packets
	// use the reliable flag with caution; although the resend rate is pretty aggressive,
	// it can still cause stalls in receiving data (like TCP)
	static bool SendDataOnSocket(SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable);

	// receiving data
	// returns false if there is no data remaining
	// fills out *pcubMsgSize with the size of the next message, in bytes
	static bool IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32 *pcubMsgSize);

	// fills in pubDest with the contents of the message
	// messages are always complete, of the same size as was sent (i.e. packetized, not streaming)
	// if *pcubMsgSize < cubDest, only partial data is written
	// returns false if no data is available
	static bool RetrieveDataFromSocket(SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize);

	// checks for data from any socket that has been connected off this listen socket
	// returns false if there is no data remaining
	// fills out *pcubMsgSize with the size of the next message, in bytes
	// fills out *phSocket with the socket that data is available on
	static bool IsDataAvailable(SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket);

	// retrieves data from any socket that has been connected off this listen socket
	// fills in pubDest with the contents of the message
	// messages are always complete, of the same size as was sent (i.e. packetized, not streaming)
	// if *pcubMsgSize < cubDest, only partial data is written
	// returns false if no data is available
	// fills out *phSocket with the socket that data is available on
	static bool RetrieveData(SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket);

	// returns information about the specified socket, filling out the contents of the pointers
	static bool GetSocketInfo(SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote);

	// returns which local port the listen socket is bound to
	// *pnIP and *pnPort will be 0 if the socket is set to listen for P2P connections only
	static bool GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort);

	// returns true to describe how the socket ended up connecting
	static ESNetSocketConnectionType GetSocketConnectionType(SNetSocket_t hSocket);

	// max packet size, in bytes
	static int GetMaxPacketSize(SNetSocket_t hSocket);
};
