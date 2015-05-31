typedef char*(*Cmd_Callback_t)(const char*);

class ConsoleCommandHandler
{
	static Cmd_Callback_t ExecuteCallback;

public:
	static void RegisterCallback(Cmd_Callback_t callback);
	static char* ExecuteCommand(char *cmd);

};