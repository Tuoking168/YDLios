#include "MinimapLua.h"
#include "script/LuaWrapper.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/mapdata/MapData.h"
#include "userdata/Gamedata.h"

int setMapInfo( lua_State* L )
{
	MiniMapInfo mapinfo;
	Lua::instance()->pop_utf8(mapinfo.m_strImage);
	Lua::instance()->pop_utf8(mapinfo.m_strName);
	Lua::instance()->pop(mapinfo.m_nID);

	MiniMapLua::mapList.push_back(mapinfo);

	return 0;
}

int setMapIcon( lua_State* L )
{
	MiniMapIcon mapicon;
	Lua::instance()->pop(mapicon.m_nPosY);
	Lua::instance()->pop(mapicon.m_nPosX);
	Lua::instance()->pop_utf8(mapicon.m_strImage);
	Lua::instance()->pop_utf8(mapicon.m_strName);
	Lua::instance()->pop(mapicon.m_nID);

	MiniMapLua::mapIconList.push_back(mapicon);

	return 0;
}

int setMapPortal( lua_State* L )
{
	NetMapConn* p=new NetMapConn(); 
	Lua::instance()->pop_utf8(p->mDesMapName);
	Lua::instance()->pop(p->mDesY);
	Lua::instance()->pop(p->mDesX);
	Lua::instance()->pop(p->mFromY);
	Lua::instance()->pop(p->mFromX);
	Lua::instance()->pop(p->mDesMapID);
	Lua::instance()->pop(p->mMapID);
	Lua::instance()->pop(p->mStaticID);
	GameData::s_map->mMiniMapConn[p->mMapID].push_back(p);
//	CCLog("MiniMap lua new map conn!");
	return 0;
}

int setNPCInfo( lua_State* L )
{
	MiniMapNPC npcinfo;
	Lua::instance()->pop(npcinfo.m_nPosY);
	Lua::instance()->pop(npcinfo.m_nPosX);
	Lua::instance()->pop_utf8(npcinfo.m_strName);
	Lua::instance()->pop(npcinfo.m_nID);

	MiniMapLua::npcList.push_back(npcinfo);

	return 0;
 }

static const luaL_Reg lua_funcs[] = 
{
	{"setMapInfo",setMapInfo},
	{"setMapIcon",setMapIcon},
	{"setMapPortal",setMapPortal},
	{"setNPCInfo",setNPCInfo},
	{NULL,NULL}
};

void MiniMapLua::Register()
{
	luaL_register(Lua::instance()->state(),"minimap",lua_funcs);
}

bool MiniMapLua::getMapList()
{
	//avoid repeating load the same data
	if(mapList.size()>0)
		return true;

	//clear the map list
	mapList.clear();

	//call Lua to start the set process
	if(	Lua::instance()->call("minimap","getMapList", 0, 1))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getMapList");
		return false;
	}
}

bool MiniMapLua::getNPCList( int mapid )
{
	//clear the npclist
	npcList.clear();

	//call Lua to start the set process
	Lua::instance()->push(mapid);
	if(	Lua::instance()->call("minimap","getNPCList", 1, 1))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getNPCList");
		return false;
	}
}

bool MiniMapLua::getMapPortals()
{
	//call Lua to start the set process
	if(	Lua::instance()->call("minimap","getMapPortals", 0, 1))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getMapPortals");
		return false;
	}
}

bool MiniMapLua::getMapIconList()
{
	//avoid repeating load the same data
	if(mapIconList.size()>0)
		return true;

	//clear the map list
	mapIconList.clear();

	//call Lua to start the set process
	if(	Lua::instance()->call("minimap","getMapIconList", 0, 1))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getMapIconList");
		return false;
	}
}

std::vector<MiniMapIcon> MiniMapLua::mapIconList;

std::vector<MiniMapNPC> MiniMapLua::npcList;

std::vector<MiniMapInfo> MiniMapLua::mapList;
