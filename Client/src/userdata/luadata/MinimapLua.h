#ifndef __MINI_MAP_LUA_H__
#define __MINI_MAP_LUA_H__

#include <vector>
#include <string>

struct MiniMapInfo
{
	int m_nID;
	std::string m_strName;
	std::string m_strImage;
};

struct MiniMapIcon
{
	int m_nID;
	std::string m_strName;
	std::string m_strImage;
	int m_nPosX;
	int m_nPosY;
};

struct MiniMapNPC
{
	int m_nID;
	std::string m_strName;
	int m_nPosX;
	int m_nPosY;
};

class MiniMapLua
{
public:
	//register c++ functions that will be called by Lua
	static void Register();
	static bool getMapList();
	static bool getMapIconList();
	static bool getMapPortals();
	static bool getNPCList(int mapid);
	static std::vector<MiniMapInfo> mapList;
	static std::vector<MiniMapIcon> mapIconList;
	static std::vector<MiniMapNPC> npcList;
};


#endif//__MINI_MAP_LUA_H__
