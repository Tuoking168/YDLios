#include "LayerDataLua.h"
#include "script/LuaWrapper.h"
bool LayerDataLua::getNodeUnitName(int id,std::string& name)
{
	Lua::instance()->push(id);
	if(	Lua::instance()->call("layer_data","get_node_unit_name", 1, 1) &&
		Lua::instance()->pop_utf8(name))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_node_unit_name.");
		return false;
	}
}

