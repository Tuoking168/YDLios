#ifndef ___MSGHANDLER__H___
#define ___MSGHANDLER__H___

#include "MsgMaster.h"
#include <map>
#include "CommonType.h"

class IMsg;

struct MsgHandler
{
	const char * name;
	void (*handler)(IMsg*);
};

typedef std::map<uint32, MsgHandler> MsgHandlerMap;

bool InitMsgHandler();

extern MsgHandlerMap msgTable;

#endif //___MSGHANDLER__H___
