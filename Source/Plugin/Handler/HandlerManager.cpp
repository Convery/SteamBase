#include "..\..\STDInclude.h"

static CRITICAL_SECTION ThreadSafe;

std::unordered_map<Handler_Event, PluginBase *> HandlerManager::Instances;

bool HandlerManager::RegisterHandler(Handler_Event EventType, PluginBase* HandlerBase)
{
	EnterCriticalSection(&ThreadSafe);

	switch (EventType)
	{
	case Handler_Event::k_HNetworking:
		//this is just not safe
		if(HandlerBase->Name.compare("HedgeNode"))
		{
			Instances[EventType] = HandlerBase;
		}
		else
		{
			DBGPrint("Plugin %s tried to register as network handler", HandlerBase->Name);
		}
		break;

	case Handler_Event::k_HGenericEvent:
		Instances[EventType] = HandlerBase;

	default:
		break;
	}

	Instances[EventType] = HandlerBase;

	LeaveCriticalSection(&ThreadSafe);

	return true;
}

bool HandlerManager::SendEvent(Handler_Event EventType, const char *Message, void * Callback)
{
	EnterCriticalSection(&ThreadSafe);

	if (Instances.find(EventType) != Instances.end())
	{
		Instances[EventType]->SendMessageB(Message, Callback);
	}

	LeaveCriticalSection(&ThreadSafe);

	return true; // ?
}