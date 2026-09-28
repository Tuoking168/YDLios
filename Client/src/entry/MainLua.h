#ifndef __MAIN_BIND_LUA__
#define __MAIN_BIND_LUA__
#include "script/LuaWrapper.h"

namespace MainLua
{
	int		libaray(lua_State* L);
	int log_debug(lua_State* L);
	int log_info(lua_State* L);
	int log_warn(lua_State* L);
	int log_error(lua_State* L);
}


#endif
