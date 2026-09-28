#ifndef __CPEvent_h__
#define __CPEvent_h__

#include <string>
#include "EventModule.h"

namespace CPEventName
{
	// event from net
	static const std::string NET_CHANGE = "net_change";

	// event from msg
	static const std::string MSG_CHANGE = "msg_change";
	static const std::string MSG_FINISH = "msg_finish";
	static const std::string MSG_DATA_READY = "msg_data_ready";

	// event from ui
	static const std::string UI_CHANGE = "ui_change";
	static const std::string UI_FINISH = "ui_finish";
	static const std::string UI_OPEN = "ui_open";
	static const std::string UI_CLOSE = "ui_close";
	static const std::string UI_NOTIFY = "ui_notify";

	// event from logic
	static const std::string LGC_CHANGE = "lgc_change";
	static const std::string LGC_FINISH = "lgc_finish";
	static const std::string LGC_TIMER = "lgc_timer";
	static const std::string LGC_GUIDE = "lgc_guide";
	static const std::string LGC_PLATFORM = "lgc_platform";

	// event from lua
	static const std::string LUA_CHANGE = "lua_change";
	static const std::string LUA_FINISH = "lua_finish";

	// event form data
	static const std::string DATA_CHANGE = "data_change";

	// npc request data
	static const std::string NPC_REQUESTDATA = "npc_requestdata";
	static const std::string NPC_REQUESTINSTANCEDATA= "npc_requestinstancedata";
}

#endif //__CPEvent_h__