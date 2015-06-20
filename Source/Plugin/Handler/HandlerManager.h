typedef enum Handler_Event
{
	k_HNetworking = 0,
	k_HGenericEvent = 0x01,
} Handler_Event;

class HandlerManager
{

public:
	static void SendEvent(ByteBuffer *inBuffer, void* outBuffer, uint32_t* outLen, int flags);
};