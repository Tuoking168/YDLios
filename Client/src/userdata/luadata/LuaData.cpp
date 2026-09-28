#include "LuaData.h"
#include "script/LuaWrapper.h"
#include "md5.h"



//////////////////////////////////////////////////////////////////////////


bool LuaData::getProp_size( std::string table, int& prop )
{
	Lua::instance()->push(table);
	if(	Lua::instance()->call("parse_prop","get_prop_size", 1, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	} 
	else
	{
		CCLog("StaticData, failed to call function name : get_prop_size int");
		return false;
	}
}

bool LuaData::getProp_size( std::string table, int inx, int sub_inx, const std::string& key1,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(sub_inx);
	Lua::instance()->push(key1);
	if(	Lua::instance()->call("parse_prop","get_prop_size", 4, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	} 
	else
	{
		CCLog("StaticData, failed to call function name : get_prop_size int");
		return false;
	}
}

bool LuaData::getProp( std::string table,int inx, const std::string& key,std::string& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop", 3, 1) &&
		Lua::instance()->pop_utf8(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_prop string");
		return false;
	}
}

bool LuaData::getProp( std::string table, int inx, int sub_inx, const std::string subtable, int sub_inx2, const std::string keyname, int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(sub_inx);
	Lua::instance()->push(subtable);
	Lua::instance()->push(sub_inx2);
	Lua::instance()->push(keyname);
	if(	Lua::instance()->call("parse_prop","get_prop", 6, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_prop int");
		return false;
	}
}

bool LuaData::getProp( std::string table,int inx, const std::string& key,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop", 3, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_prop int");
		return false;
	}
}

bool LuaData::getProp( std::string table,int inx, const std::string& key,float& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop", 3, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_prop float");
		return false;
	}
}

bool LuaData::getProp_size( std::string table, int inx ,const std::string& tabel_1 ,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(tabel_1);
	if(	Lua::instance()->call("parse_prop","get_prop_size", 3, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	} 
	else
	{
		CCLog("StaticData, failed to call function name : get_prop_size int");
		return false;
	}
}

bool LuaData::getProp_size( std::string table, int inx, int inx_sub,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(inx_sub);
	if(	Lua::instance()->call("parse_prop","get_prop_size", 3, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	} 
	else
	{
		CCLog("StaticData, failed to call function name : get_prop_size int");
		return false;
	}
}

bool LuaData::getProp( std::string table, int inx,const std::string& tabel_1 ,int inx_sub,const std::string& key1,const std::string& key2 ,int& prop1 ,int& prop2 )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(tabel_1);
	Lua::instance()->push(inx_sub);
	Lua::instance()->push(key1);
	Lua::instance()->push(key2);
	if(	Lua::instance()->call("parse_prop","get_prop_subprop", 6, 2) &&
		Lua::instance()->pop(prop1) &&
		Lua::instance()->pop(prop2))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_prop_subprop int int");
		return false;
	}
}

bool LuaData::getProp( std::string table, int inx, int sub_inx ,const std::string& key ,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(sub_inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop_merge", 4, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_prop_merge int");
		return false;
	}
}

bool LuaData::getProp( std::string table, int inx, int sub_inx ,const std::string& key ,std::string& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(sub_inx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop_merge", 4, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_prop_merge string");
		return false;
	}
}

bool LuaData::getProp( std::string table, const std::string& key,std::string& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop_by_key", 2, 1) &&
		Lua::instance()->pop_utf8(prop))
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop_by_key string");
		return false;
	}
}

bool LuaData::getProp( std::string table, const std::string& key,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop_by_key", 2, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop_by_key int");
		return false;
	}
}

bool LuaData::getProp( std::string table, const std::string& key,float& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop_by_key", 2, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop_by_key float");
		return false;
	}
}

bool LuaData::getProp( std::string table, int idx, std::string subtable, int sidx, const std::string& key,std::string& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(idx);
	Lua::instance()->push(subtable);
	Lua::instance()->push(sidx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_sub_prop", 5, 1) &&
		Lua::instance()->pop_utf8(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_sub_prop string");
		return false;
	}
}

bool LuaData::getProp( std::string table, int idx, std::string subtable, int sidx, const std::string& key, int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(idx);
	Lua::instance()->push(subtable);
	Lua::instance()->push(sidx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_sub_prop", 5, 1) && Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_sub_prop int");
		return false;
	}
}

bool LuaData::getProp( std::string table, std::string keyname, std::string subtable, int sidx, const std::string& key, int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push_utf8(keyname);
	Lua::instance()->push(subtable);
	Lua::instance()->push(sidx);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_sub_prop", 5, 1) && Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_sub_prop int");
		return false;
	}
}

bool LuaData::getProp( std::string table, int key,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop_by_key", 2, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop_by_key int");
		return false;
	}
}

bool LuaData::getProp( std::string table, int key,std::string& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(key);
	if(	Lua::instance()->call("parse_prop","get_prop_by_key", 2, 1) &&
		Lua::instance()->pop_utf8(prop))
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop_by_key string");
		return false;
	}
}

bool LuaData::getProp( std::string table, int inx, int sub_inx, int sub_inx2,const std::string keyname,std::string& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(sub_inx);
	Lua::instance()->push(sub_inx2);
	Lua::instance()->push(keyname);
	if(	Lua::instance()->call("parse_prop","get_sub_prop", 5, 1) && Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_sub_prop string");
		return false;
	}
}

bool LuaData::getProp_ItemInfo( std::string table, int inx, const std::string& tabel_1 ,int inx_sub,const std::string& key1,const std::string& key2 ,const std::string& key3,int& prop1 ,int& prop2,int& prop3 )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(tabel_1);
	Lua::instance()->push(inx_sub);
	Lua::instance()->push(key1);
	Lua::instance()->push(key2);
	Lua::instance()->push(key3);
	if(	Lua::instance()->call("parse_prop","get_prop_ItemInfo", 7, 3) &&
		Lua::instance()->pop(prop1) &&
		Lua::instance()->pop(prop2) &&
		Lua::instance()->pop(prop3))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_ItemInfo");
		return false;
	}
}



bool LuaData::getProp_Ghostpos( std::string table,int mapid, int inx,std::string tb1,int& prop1 ,int& prop2)
{
	Lua::instance()->push(table);
	Lua::instance()->push(mapid);
	Lua::instance()->push(inx);
	Lua::instance()->push(tb1);
	if(	Lua::instance()->call("parse_prop","getProp_Ghostpos", 4, 2) &&
		Lua::instance()->pop(prop1) &&
		Lua::instance()->pop(prop2) 
		)
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_Ghostpos");
		return false;
	}
}

bool LuaData::getProp_GhostMapID( std::string table, int inx,std::string tb1 ,int& prop )
{
	Lua::instance()->push(table); 
	Lua::instance()->push(inx);
	Lua::instance()->push(tb1);
	if(	Lua::instance()->call("parse_prop","getProp_GhostMapID", 3, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_GhostMapID");
		return false;
	}
}

bool LuaData::getProp_Map( std::string table, int inx,int count,int& prop1,int& prop2,int& prop3,int& prop4,int& prop5 )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(count);
	if(	Lua::instance()->call("parse_prop","getProp_Map", 3, 5) &&
		Lua::instance()->pop(prop1) &&
		Lua::instance()->pop(prop2) &&
		Lua::instance()->pop(prop3) &&
		Lua::instance()->pop(prop4) &&
		Lua::instance()->pop(prop5))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_Map");
		return false;
	}
}

bool LuaData::getProp_MapConnCount( std::string table, int inx,int& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	if(	Lua::instance()->call("parse_prop","getProp_MapConnCount", 2, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_MapConnCount");
		return false;
	}
}

bool LuaData::checkIdExist( std::string table, int inx )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	int prop = 0;
	if(	Lua::instance()->call("parse_prop","checkExist", 2, 1)&&
		Lua::instance()->pop(prop))
	{
		return prop;
	}
	else
	{
		CCLog("StaticData, failed to call function name : checkExist");
		return false;
	}
}

bool LuaData::checkKeyExist( std::string table, const std::string& key )
{
	Lua::instance()->push(table);
	Lua::instance()->push(key);
	int result = 0;
	if(	Lua::instance()->call("parse_prop","get_prop", 2, 1)&& Lua::instance()->pop(result) && result)
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop string");
		return false;
	}
}

bool LuaData::getProp_merge( std::string table, int inx,int inx_sub,const std::string& key1,const std::string& key2 ,int& prop1 ,int& prop2 )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(inx_sub);
	Lua::instance()->push(key1);
	Lua::instance()->push(key2);
	if(	Lua::instance()->call("parse_prop","getProp_merge", 5, 2) &&
		Lua::instance()->pop(prop1) &&
		Lua::instance()->pop(prop2))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_merge int");
		return false;
	}
}


bool LuaData::getProp_mergefindsrc( std::string table, int type, int sid, bool& flag )
{
	Lua::instance()->push(table);
	Lua::instance()->push(type);
	Lua::instance()->push(sid);
	if(	Lua::instance()->call("parse_prop","getProp_mergefindsrc", 3, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_mergefindsrc int");
		return false;
	}
}

bool LuaData::getProp_mergefindtgt( std::string table, int type, const std::string& tabel_1,int srcsid, int& sid )
{
	Lua::instance()->push(table);
	Lua::instance()->push(type);
	Lua::instance()->push(tabel_1);
	Lua::instance()->push(srcsid);
	if(	Lua::instance()->call("parse_prop","getProp_mergefindtgt", 4, 1) &&
		Lua::instance()->pop(sid))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_mergefindtgt int");
		return false;
	}
}

bool LuaData::getProp_pet( std::string table, int inx, const std::string& tabel_1, const std::string& tabel_2,std::string& prop )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(tabel_1);
	Lua::instance()->push(tabel_2);
	if(	Lua::instance()->call("parse_prop","get_prop_pet", 4, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_pet string");
		return false;
	}
}

bool LuaData::getProp_NPCfunc( std::string table, int inx, const std::string& tabel_1, int type ,int funcid, std::string& prrp )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(tabel_1);
	Lua::instance()->push(type);
	Lua::instance()->push(funcid);
	if(	Lua::instance()->call("parse_prop","getProp_NPCfunc", 5, 1) &&
		Lua::instance()->pop_utf8(prrp))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_NPCfunc string");
		return false;
	}
}

bool LuaData::getProp_tips( std::string table, int inx, const std::string& tabel_1, int tabel_1id, const std::string& tabel_2 , std::string& prrp )
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(tabel_1);
	Lua::instance()->push(tabel_1id);
	Lua::instance()->push(tabel_2);
	if(	Lua::instance()->call("parse_prop","get_prop_tips", 5, 1) &&
		Lua::instance()->pop(prrp))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_tips string");
		return false;
	}
}

bool LuaData::getProp_Spider( int inx ,int& prop )
{
	Lua::instance()->push(inx);
	if(	Lua::instance()->call("parse_prop","get_prop_spider", 1, 1) &&
		Lua::instance()->pop(prop))
	{
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : getProp_Spider int");
		return false;
	}
}

bool LuaData::checkMonsterInMapExist( std::string table,int inx,std::string tb1,int ghostid)
{
	Lua::instance()->push(table);
	Lua::instance()->push(inx);
	Lua::instance()->push(tb1);
	Lua::instance()->push(ghostid);
	int result = 0;
	if(	Lua::instance()->call("parse_prop","check_monsterinmap", 4, 1)&& Lua::instance()->pop(result) && result)
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop string");
		return false;
	}
}

bool LuaData::getProp_NearestMonsterPos( std::string table, int monsterid, int mapid,int num, int& prop1 ,int& prop2 )
{
	Lua::instance()->push(table);
	Lua::instance()->push(monsterid);
	Lua::instance()->push(mapid);
	Lua::instance()->push(num);
	if(	Lua::instance()->call("parse_prop","getprop_getnearestPos", 4, 2)&&
		Lua::instance()->pop(prop2) &&
		Lua::instance()->pop(prop1))
	{
		return true;
	}
	else
	{
		//CCLog("StaticData, failed to call function name : get_prop string");
		return false;
	}
}

std::string LuaData::PET = "gdPets";

std::string LuaData::SHOP = "gdShops";

std::string LuaData::MAP = "gdMaps";

std::string LuaData::NPC = "gdNPC";

std::string LuaData::MONSTER = "gdMonsters";

std::string LuaData::SKILL = "gdSkills";

std::string LuaData::ITEM = "gdItems"; 

std::string LuaData::SKILLENT = "gdSkillEntity";

std::string LuaData::QUEST = "gdQuests";

std::string LuaData::QUESTEX = "gdReward";

std::string LuaData::QUEST_SUB = "reward";

std::string LuaData::QUEST_SUB_1 = "count";

std::string LuaData::QUEST_SUB_2 = "type";

std::string LuaData::ANIM_FRAME_COUNT = "animframes";

std::string LuaData::GUILD_DATA = "gdGuilddata";

std::string LuaData::GUILD_JOB_REWARD = "gdGuildJobReward";
