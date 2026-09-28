#ifndef __LUA_DATA_H__
#define __LUA_DATA_H__
#include "cocos2d.h"
using namespace cocos2d;

class LuaData
{
public:
	//functions that will call lua
	//static bool getPropEx( std::string& prop, const char* code ...);
	//static bool getPropEx( int& prop, const char* code ...);

	static bool getProp_size( std::string table, int& prop );
	static bool getProp_size( std::string table, int inx, int sub_inx, const std::string& key1,int& prop );
	static bool getProp( std::string table, const std::string& key,std::string& prop );
	static bool getProp( std::string table, int key,int& prop );
	static bool getProp( std::string table, int idx, std::string subtable, int sidx, const std::string& key,std::string& prop );
	static bool getProp( std::string table, int idx, std::string subtable, int sidx, const std::string& key, int& prop );
	static bool getProp( std::string table, const std::string& key,int& prop );
	static bool getProp( std::string table, int key,std::string& prop );
	static bool getProp( std::string table, std::string keyname, std::string subtable, int sidx, const std::string& key, int& prop );
	static bool getProp( std::string table, const std::string& key,float& prop );
	static bool getProp( std::string table, int inx, const std::string& key,std::string& prop );
	static bool getProp( std::string table, int inx, const std::string& key,int& prop );
	static bool getProp( std::string table, int inx, const std::string& key,float& prop );
	static bool getProp( std::string table, int inx, int sub_inx, const std::string& key1,int& prop );
	static bool getProp( std::string table, int inx, int sub_inx, const std::string& key1,std::string& prop );
	static bool getProp( std::string table, int inx, int sub_inx, int sub_inx2,const std::string keyname,std::string& prop );
	static bool getProp( std::string table, int inx, int sub_inx, const std::string subtable, int sub_inx2, const std::string keyname, int& prop );
	static bool getProp_size( std::string table, int inx, const std::string& tabel_1,int& prop );
	static bool getProp_size( std::string table, int inx, int inx_sub,int& prop );
	static bool getProp( std::string table, int inx, const std::string& tabel_1 ,int inx_sub,const std::string& key1,const std::string& key2 ,int& prop1 ,int& prop2);
	static bool getProp_Ghostpos(std::string table,int mapid, int inx,std::string tb1,int& prop1 ,int& prop2);
	static bool getProp_GhostMapID(std::string table, int inx,std::string tb1,int& prop);
	static bool getProp_Map(std::string table, int inx,int count,int& prop1,int& prop2,int& prop3,int& prop4,int& prop5);
	static bool getProp_MapConnCount(std::string table, int inx,int& prop);
	static bool getProp_ItemInfo( std::string table, int inx, const std::string& tabel_1 ,int inx_sub,const std::string& key1,const std::string& key2 ,const std::string& key3,int& prop1 ,int& prop2,int& prop3);
	static bool checkIdExist(std::string table, int inx);
	static bool checkKeyExist(std::string table, const std::string& key);
	static bool getProp_merge( std::string table, int inx,int inx_sub,const std::string& key1,const std::string& key2 ,int& prop1 ,int& prop2);
	static bool getProp_mergefindsrc( std::string table, int type, int sid, bool& flag );
	static bool getProp_mergefindtgt( std::string table, int type, const std::string& tabel_1, int srcsid, int& sid );
	static bool getProp_pet( std::string table, int inx, const std::string& tabel_1, const std::string& tabel_2,std::string& prop);
	static bool getProp_NPCfunc( std::string table, int inx, const std::string& tabel_1, int type  ,int funcid, std::string& prrp);
	static bool getProp_tips( std::string table, int inx, const std::string& tabel_1, int tabel_1id, const std::string& tabel_2 , std::string& prrp);
	static bool getProp_Spider( int inx ,int& prop );
	static bool getProp_NearestMonsterPos( std::string table, int monsterid, int mapid,int num, int& prop1 ,int& prop2 );
	static bool getProp_getsuitstring( std::string table, int suitid,int suitcnt, int subid,std::string& prop);

	static bool checkMonsterInMapExist(std::string table,int inx,std::string tb1,int ghostid);
	static std::string ITEM;
	static std::string SKILL;
	static std::string SKILLENT;
	static std::string MONSTER;
	static std::string PET;
	static std::string QUESTEX;
	static std::string MAP;
	static std::string NPC;
	static std::string SHOP;
	static std::string QUEST;
	static std::string QUEST_SUB;
	static std::string QUEST_SUB_1;
	static std::string QUEST_SUB_2;
	static std::string ANIM_FRAME_COUNT;
	static std::string GUILD_DATA;
	static std::string GUILD_JOB_REWARD;
};
#endif//__LUA_DATA_H__