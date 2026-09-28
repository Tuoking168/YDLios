#include "stdafx.h"
#include "MainLua.h"
#include "log.h"
#include "LuaWrapper.h"

#include "scene/NotificationHelper.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/UserItemData.h"

#include "event/CPEventDispatcher.h"

#include "network/HandleMessage.h"


/////////Logger////////////////////////////////////////////////////////
namespace Logger
{
	int log(lua_State* L, const std::string &lvl)
	{
		std::ostringstream oss;
		const int n = lua_gettop(L);  /* number of arguments */
		int i;
		lua_getglobal(L, "tostring");
		for (i=1; i<=n; i++) 
		{
			const char *s;
			lua_pushvalue(L, -1);  /* function to be called */
			lua_pushvalue(L, i);   /* value to print */
			lua_call(L, 1, 1);
			s = lua_tostring(L, -1);  /* get result */
			if (s == NULL)
				return luaL_error(L, LUA_QL("tostring") " must return a string to "
				LUA_QL("print"));
			if (i>1) 
			{
				oss<<"\t";
			}
			oss<<s;
			lua_pop(L, 1);  /* pop result */
		}
		CPLog::log(lvl, oss.str().c_str());	
		return 0;
	}

	int log_debug(lua_State* L)
	{
		return log(L, "Debug> ");
	}

	int log_info(lua_State* L)
	{
		return log(L, "Info> ");
	}

	int log_warn(lua_State* L)
	{
		return log(L, "Warn> ");
	}

	int log_error(lua_State* L)
	{
		return log(L, "Error> ");
	}

	static const luaL_Reg log_funcs[] = {
		{"debug", log_debug},
		{"info", log_info},
		{"warn", log_warn},
		{"error", log_error},
		{NULL, NULL}
	};


	int libaray(lua_State* L)
	{
		// fill member list into metatable
		luaL_register(L, "log", log_funcs);

		return 0;
	}
}

/////////CPEventLua////////////////////////////////////////////////////
namespace CPEventLua
{
	int dispatcher(lua_State* L)
	{
		std::string eventName = lua_tolstring(L, -1, NULL);
		if (!eventName.empty())
		{
			CPEvtDispatcher.dispatcherEvent(eventName);
		}
		return 0;
	}

	static const luaL_Reg funcs[] = {
		{"dispatcher", dispatcher},
		{NULL, NULL}
	};

	int libaray(lua_State* L)
	{
		luaL_register(L, "CPEvtDispatcher", funcs);
		return 0;
	}
}

//////////Notification///////////////////////////////////////////////
namespace Notification
{
	int addNote(lua_State* L)
	{
		int noteType = 0;
		CPLua->pop(noteType);
		std::string msg;
		CPLua->pop_utf8(msg);
		NotificationHelper::showNote(msg, noteType);
		return 0;
	}

	static const luaL_Reg notification_funcs[] = {
		{"addNote", addNote},
		{NULL, NULL}
	};

	int libaray(lua_State* L)
	{
		luaL_register(L, "cpnotification", notification_funcs);
		return 0;
	}
}

////////CPMsgHandler/////////////////////////////////////////////////
namespace CPMsgHandler
{
	int send(lua_State* L)
	{
		std::string msgName;
		CPLua->pop(msgName);
		HandleMessage::sendMessage(msgName);
		return 0;
	}

	static const luaL_Reg funcs[] = {
		{"send", send},
		{NULL, NULL}
	};

	int libaray(lua_State* L)
	{
		luaL_register(L, "CPMsgHandler", funcs);

		return 0;
	}
}

///////////Items//////////////////////////////////////////////
namespace Items
{
	int getItemSID(lua_State *L)
	{
		int iid = 0;
		CPLua->pop(iid);
		UserItemData *userItemData = GameData::getUserItemData();
		if (userItemData)
		{
			UserItem *item = userItemData->getItemByIid(iid);
			if (item)
			{
				CPLua->push(item->sid);
				return 1;
			}
		}
		CPLua->push(0);
		return 0;
	}

	static const luaL_Reg funcs[] = {
		{"getItemSID", getItemSID},
		{NULL, NULL}
	};

	int libaray(lua_State* L)
	{
		luaL_register(L, "Items", funcs);

		return 0;
	}
}

//////////MainLua///////////////////////////////////////////////////////
namespace MainLua
{
	int libaray()
	{
		lua_State *L = CPLua->state();

		//
		Logger::libaray(L);
		CPEventLua::libaray(L);
		Notification::libaray(L);
		CPMsgHandler::libaray(L);
		Items::libaray(L);

		//
		return 0;
	}
} // end of scene lua
