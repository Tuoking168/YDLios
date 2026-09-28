#include "MonsterLua.h"
#include "script/LuaWrapper.h"



//////////////////////////////////////////////////////////////////////////
bool ItemLua::getMonsterProp( int inx, const std::string& key,std::string& prop )
{
	Lua::instance()->push(inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_monster_prop","get_monster_prop", 2, 1) &&
		Lua::instance()->pop_utf8(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_monster_prop string");
		return false;
	}
}

bool ItemLua::getMonsterProp( int inx, const std::string& key,int& prop )
{
	Lua::instance()->push(inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_monster_prop","get_monster_prop", 2, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_monster_prop int");
		return false;
	}
}

bool ItemLua::getMonsterProp( int inx, const std::string& key,float& prop )
{
	Lua::instance()->push(inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_monster_prop","get_monster_prop", 2, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_monster_prop float");
		return false;
	}
}
