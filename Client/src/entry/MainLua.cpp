#include "stdafx.h"
#include "MainLua.h"
#include "log.h"



namespace MainLua
{
	int log(lua_State* L, std::string lvl)
	{
		std::ostringstream oss;
		int n = lua_gettop(L);  /* number of arguments */
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
		LOG(lvl.c_str(),oss.str());	
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

} // end of scene lua
