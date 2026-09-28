#include "ModuleData.h"
#include "cocos2d.h"
#include "script/LuaWrapper.h"

using namespace cocos2d;

static bool luaCall( const std::string &func, int narg, int nret )
{
	if (Lua::instance()->call("gdceapon", func.c_str(), narg, nret))
	{
		return true;
	}
	CCLog(">>>Error, lua call gdceapon.%s failed!", func.c_str());
	return false;
}

static void luaPush( const std::string &module, const std::string &key )
{
	Lua::instance()->push(module);
	Lua::instance()->push(key);
}

static bool luaSet()
{
	return luaCall("set_data", 3, 0);
}

static bool luaGet()
{
	return luaCall("get_data", 2, 1);
}

static bool luaSize()
{
	return luaCall("get_size", 1, 1);
}

static bool luaLoadModule()
{
	return luaCall("load_module", 1, 0);
}

static bool luaSaveModule()
{
	return luaCall("save_module", 2, 0);
}

static bool luaClearModule()
{
	return luaCall("clear_module", 1, 0);
}

static bool luaClearAll()
{
	return luaCall("clear_all", 0, 0);
}

//
// sub module
//
static void luaSubPush( const std::string &module, const std::string &subModule, int id, const std::string &key )
{
	Lua::instance()->push(module);
	Lua::instance()->push(subModule);
	Lua::instance()->push(id);
	Lua::instance()->push(key);
}

static bool luaSubSet()
{
	return luaCall("set_sub_data", 5, 0);
}

static bool luaSubGet()
{
	return luaCall("get_sub_data", 4, 1);
}

static bool luaSubSize()
{
	return luaCall("get_sub_size", 2, 1);
}

static bool luaSubIDVector()
{
	return luaCall("get_sub_id_vector", 2, 1);
}

static bool luaClearSubData()
{
	return luaCall("clear_sub_data", 3, 0);
}

static bool luaClearSubAll()
{
	return luaCall("clear_sub_all", 2, 0);
}


////////////ModuleData//////////////////////////////////////////////
void ModuleData::setInt( const std::string &module, const std::string &key, int value )
{
	luaPush(module, key);
	Lua::instance()->push(value);
	luaSet();
}

void ModuleData::setFloat( const std::string &module, const std::string &key, float value )
{
	luaPush(module, key);
	Lua::instance()->push(value);
	luaSet();
}

void ModuleData::setString( const std::string &module, const std::string &key, const std::string &value )
{
	luaPush(module, key);
	std::string temp = value;
	Lua::instance()->push_utf8(temp);
	luaSet();
}

bool ModuleData::getInt( const std::string &module, const std::string &key, int &value )
{
	luaPush(module, key);
	if (luaGet() &&
		Lua::instance()->pop(value))
	{
		return true;
	}
	return false;
}

bool ModuleData::getFloat( const std::string &module, const std::string &key, float &value )
{
	luaPush(module, key);
	if (luaGet() &&
		Lua::instance()->pop(value))
	{
		return true;
	}
	return false;
}

bool ModuleData::getString( const std::string &module, const std::string &key, std::string &value )
{
	luaPush(module, key);
	if (luaGet() &&
		Lua::instance()->pop_utf8(value))
	{
		return true;
	}
	return false;
}

bool ModuleData::getSize( const std::string &module, int &size )
{
	Lua::instance()->push(module);
	if (luaSize() &&
		Lua::instance()->pop(size))
	{
		return true;
	}
	return false;
}

bool ModuleData::loadModule( const std::string &module )
{
	if (!module.empty())
	{
		char ch[128];
		sprintf(ch, "require '%s'", module.c_str());
		if (Lua::instance()->call(ch))
		{
			Lua::instance()->push(module);
			return luaLoadModule();
		}
	}
	return false;
}

bool ModuleData::saveModule( const std::string &module )
{
	if (!module.empty())
	{
		std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
		filePath += module + ".lua";
		Lua::instance()->push(module);
		Lua::instance()->push(filePath);
		return luaSaveModule();
	}
	return false;
}

bool ModuleData::clearModule( const std::string &module )
{
	Lua::instance()->push(module);
	return luaClearModule();
}

bool ModuleData::clearAll()
{
	return luaClearAll();
}

////////////SubModuleData/////////////////////////////////////////////
std::string SubModuleData::moduleName;
std::string SubModuleData::subModuleName;

void SubModuleData::init( const std::string &module, const std::string &subModule )
{
	moduleName = module;
	subModuleName = subModule;
}

void SubModuleData::setInt( int id, const std::string &key, int value )
{
	luaSubPush(moduleName, subModuleName, id, key);
	Lua::instance()->push(value);
	luaSubSet();
}

void SubModuleData::setFloat( int id, const std::string &key, float value )
{
	luaSubPush(moduleName, subModuleName, id, key);
	Lua::instance()->push(value);
	luaSubSet();
}

void SubModuleData::setString( int id, const std::string &key, const std::string &value )
{
	luaSubPush(moduleName, subModuleName, id, key);
	std::string temp = value;
	Lua::instance()->push_utf8(temp);
	luaSubSet();
}

bool SubModuleData::getInt( int id, const std::string &key, int &value )
{
	luaSubPush(moduleName, subModuleName, id, key);
	if (luaSubGet() &&
		Lua::instance()->pop(value))
	{
		return true;
	}
	return false;
}

bool SubModuleData::getFloat( int id, const std::string &key, float &value )
{
	luaSubPush(moduleName, subModuleName, id, key);
	if (luaSubGet() &&
		Lua::instance()->pop(value))
	{
		return true;
	}
	return false;
}

bool SubModuleData::getString( int id, const std::string &key, std::string &value )
{
	luaSubPush(moduleName, subModuleName, id, key);
	if (luaSubGet() &&
		Lua::instance()->pop_utf8(value))
	{
		return true;
	}
	return false;
}

bool SubModuleData::getSize( int &size )
{
	luaPush(moduleName, subModuleName);
	if (luaSubSize() &&
		Lua::instance()->pop(size))
	{
		return true;
	}
	return false;
}

bool SubModuleData::getIDVector( IDVector &idVector )
{
	std::string idString;
	luaPush(moduleName, subModuleName);
	if (luaSubIDVector() &&
		Lua::instance()->pop(idString))
	{
		std::string s;
		int k = idString.find("|");
		while (k != idString.npos)
		{
			s = idString.substr(0, k);
			if (!s.empty())
			{
				idVector.push_back(atoi(s.c_str()));
			}
			idString = idString.substr(k + 1);
			k = idString.find("|");
		}
		return true;
	}
	return false;
}

bool SubModuleData::clearData( int id )
{
	luaPush(moduleName, subModuleName);
	Lua::instance()->push(id);
	return luaClearSubData();
}

bool SubModuleData::clearAll()
{
	luaPush(moduleName, subModuleName);
	return luaClearSubAll();
}

