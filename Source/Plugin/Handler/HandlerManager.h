typedef enum Handler_Event
{
	k_HNetworking = 0,
	k_HGenericEvent = 0x01,
} Handler_Event;

class HandlerManager
{
	static std::unordered_map<Handler_Event, PluginBase *> Instances;

public:
	static bool RegisterHandler(Handler_Event EventType, PluginBase* HandlerBase);
	static bool SendEvent(Handler_Event EventType, const char *Message, void * Callback);
};