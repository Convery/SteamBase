namespace Nodes
{
	class ClientNode
	{
		static hAddress serverNode;
		
		static uint32_t sequenceID;
		static std::unordered_map<uint32_t, std::shared_ptr<ByteBuffer>> pendingData;
		static HANDLE sNodeDiscoveryThread;
		static HANDLE sPacketReceiverThread;
		static HANDLE sFriendThread;
		static std::mutex mutex;
		static HedgeNodeProto::SteamFriendsResult* result;
		static time_t lastPing;

		static DWORD _stdcall NodeDiscoverySender(void  *lparam);
		static DWORD _stdcall NodePacketReceiver(void  *lparam);
		static DWORD _stdcall FriendDiscoveryThread(void  *lparam);
		
	public:
		static bool isSNodeConnected;

		static bool InitializeNode();
		static void SetNetworkData(Network::NetworkPacket *inPacket, EventType eventType); 
		static uint32_t GetSequence();
		static void InviteReceived(uint64_t lobbyID, uint64_t inviteeID);
		static void InviteToGame(uint64_t From, uint64_t lobbyID);
		static int32_t GetFriendCount(int32_t iFriendFlags);
		static void GetFriends();
		static std::string GetFriendName(uint64_t FriendID);
		static uint64_t GetFriendByIndex(int32_t iFriend, int32_t iFriendFlags);
	};
}