#include "StaticData.h"
#include "CCCommon.h"
#include "script/LuaWrapper.h"

using namespace cocos2d;

static void logError( const std::string &funcName )
{
	CCLog(">>>Error: lua call func %s failed!", funcName.c_str());
}

/////////StaticData///////////////////////////////////////////////////////
bool StaticData::reloadLuaFiles()
{
	CCLog(">>> StaticData::reloadLuaFiles!");
	bool test = Lua::instance()->call("package.loaded['script/main'] = false");
	if(test)
	{
		test = Lua::instance()->call("require 'script/main'");
		if(test)
		{
			test = Lua::instance()->call("reload_client_data()");
		}
	}
	return test;
}

bool StaticData::getHorseAnimPath( int animType, int id, int animState, std::string &animPath )
{
	CPLua->push(animType);
	CPLua->push(id);
	CPLua->push(animState);
	if (Lua::instance()->call("g_get_horse_anim_path", 3, 1) &&
		Lua::instance()->pop(animPath))
	{
		return true;
	}
	logError("g_get_horse_anim_path");
	return false;
}

bool StaticData::getAnimPath( int animType, int id, int animState, std::string &animPath )
{
	CPLua->push(animType);
	CPLua->push(id);
	CPLua->push(animState);
	if (Lua::instance()->call("g_get_anim_path", 3, 1) &&
		Lua::instance()->pop(animPath))
	{
		return true;
	}
	logError("g_get_anim_path");
	return false;
}

bool StaticData::getMapType( int mapID, int &type )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("cb_get_scene_type", 1, 1) &&
		Lua::instance()->pop(type))
	{
		return true;
	}
	logError("cb_get_scene_type");
	return false;
}

bool StaticData::getMapEventID( int mapID, int &eventID )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("cb_get_scene_event_id", 1, 1) &&
		Lua::instance()->pop(eventID))
	{
		return true;
	}
	logError("cb_get_scene_event_id");
	return false;
}

bool StaticData::getMapMiningFlag( int mapID, int &flag )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("g_get_map_mining_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_map_mining_flag");
	return false;
}

bool StaticData::getMapMusic( int mapID, std::string &musicName )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("g_get_scene_music", 1, 1) &&
		Lua::instance()->pop(musicName))
	{
		return true;
	}
	logError("g_get_scene_music");
	return false;
}

bool StaticData::getMapPKRedFlag( int mapID, int &flag )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("g_get_scene_pk_red_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_scene_pk_red_flag");
	return false;
}

bool StaticData::getMapSaiMaChangFlag( int mapID, int &flag )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("g_get_map_sai_ma_chang_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_map_sai_ma_chang_flag");
	return false;
}

bool StaticData::getMapPeaceAreaCnt( int mapID, int &cnt )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("g_get_map_peace_area_cnt", 1, 1) &&
		Lua::instance()->pop(cnt))
	{
		return true;
	}
	logError("g_get_map_peace_area_cnt");
	return false;
}

bool StaticData::getMapPeaceAreaID( int mapID, int index, int &peaceID )
{
	Lua::instance()->push(mapID);
	Lua::instance()->push(index);
	if (Lua::instance()->call("g_get_map_peace_area_id", 2, 1) &&
		Lua::instance()->pop(peaceID))
	{
		return true;
	}
	logError("g_get_map_peace_area_id");
	return false;
}

bool StaticData::getMapHideInWorldMapFlag( int mapID, int &flag )
{
	Lua::instance()->push(mapID);
	if (Lua::instance()->call("g_get_map_hide_in_world_map_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_map_hide_in_world_map_flag");
	return false;
}

bool StaticData::getMapMonsterCount( int mapID, int &count )
{
	CPLua->push(mapID);
	if (CPLua->call("g_get_map_monster_count", 1, 1)
		&& CPLua->pop(count))
	{
		return true;
	}
	logError("g_get_map_monster_count");
	return false;
}

bool StaticData::getMapMonsterData( int mapID, int index, int &monsterID, int &posX, int &posY )
{
	CPLua->push(mapID);
	CPLua->push(index);
	if (CPLua->call("g_get_map_monster_data", 2, 3)
		&& CPLua->pop(posY)
		&& CPLua->pop(posX)
		&& CPLua->pop(monsterID))
	{
		return true;
	}
	logError("g_get_map_monster_data");
	return false;
}

bool StaticData::getMapEventMonsterCount( int mapID, int &count )
{
	CPLua->push(mapID);
	if (CPLua->call("g_get_map_event_monster_count", 1, 1)
		&& CPLua->pop(count))
	{
		return true;
	}
	logError("g_get_map_event_monster_count");
	return false;
}

bool StaticData::getMapEventMonsterData( int mapID, int index, int &monsterID, int &posX, int &posY )
{
	CPLua->push(mapID);
	CPLua->push(index);
	if (CPLua->call("g_get_map_event_monster_data", 2, 3)
		&& CPLua->pop(posY)
		&& CPLua->pop(posX)
		&& CPLua->pop(monsterID))
	{
		return true;
	}
	logError("g_get_map_event_monster_data");
	return false;
}

bool StaticData::getMapName( int mapID, std::string &name )
{
	CPLua->push(mapID);
	if (CPLua->call("cb_get_scene_name", 1, 1)
		&& CPLua->pop_utf8(name))
	{
		return true;
	}
	logError("cb_get_scene_name");
	return false;
}

bool StaticData::getMapChengBaTianXiaFlag( int mapID, int &flag )
{
	CPLua->push(mapID);
	if (CPLua->call("g_get_map_cheng_ba_tian_xia_flag", 1, 1)
		&& CPLua->pop(flag))
	{
		return true;
	}
	logError("g_get_map_cheng_ba_tian_xia_flag");
	return false;
}

bool StaticData::getItemAnim( int itemID, std::string &anim )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("get_item_anim", 1, 1) &&
		Lua::instance()->pop_utf8(anim))
	{
		return true;
	}
	logError("get_item_anim");
	return false;
}

bool StaticData::getItemName( int itemID, std::string &name )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_name", 1, 1) &&
		Lua::instance()->pop_utf8(name))
	{
		return true;
	}
	logError("g_get_item_name");
	return false;
}

bool StaticData::getItemIcon( int itemID, std::string &icon )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("cb_get_item_icon", 1, 1) &&
		Lua::instance()->pop(icon))
	{
		return true;
	}
	logError("cb_get_item_icon");
	return false;
}

bool StaticData::getItemIcon( int itemID, int count, std::string &icon )
{
	Lua::instance()->push(itemID);
	Lua::instance()->push(count);
	if (Lua::instance()->call("cb_get_item_icon_with_count", 2, 1) &&
		Lua::instance()->pop(icon))
	{
		return true;
	}
	logError("cb_get_item_icon_with_count");
	return false;
}

bool StaticData::getItemMiningFlag( int itemID, int &flag )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_mining_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_item_mining_flag");
	return false;
}

bool StaticData::getItemSkillID( int itemID, int &skillID )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_skill_id", 1, 1) &&
		Lua::instance()->pop(skillID))
	{
		return true;
	}
	logError("g_get_item_skill_id");
	return false;
}

bool StaticData::getSuitWeapon( int itemID, int &weaponID )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_suit_weapon_id", 1, 1) &&
		Lua::instance()->pop(weaponID))
	{
		return true;
	}
	logError("g_get_item_suit_weapon_id");
	return false;
}

bool StaticData::getItemRequireLevel( int itemID, int &reborn, int &level )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_require_level", 1, 2) &&
		Lua::instance()->pop(level) &&
		Lua::instance()->pop(reborn))
	{
		return true;
	}
	logError("g_get_item_require_level");
	return false;
}

bool StaticData::getItemRequireJob( int itemID, int &job )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_require_job", 1, 1) &&
		Lua::instance()->pop(job))
	{
		return true;
	}
	logError("g_get_item_require_job");
	return false;
}

bool StaticData::getItemRequireGender( int itemID, int &gender )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_require_gender", 1, 1) &&
		Lua::instance()->pop(gender))
	{
		return true;
	}
	logError("g_get_item_require_gender");
	return false;
}

bool StaticData::getItemDataEx( int itemID, int &datax, int &datay )
{
	Lua::instance()->push(itemID);
	if (Lua::instance()->call("g_get_item_data_ex", 1, 2) &&
		Lua::instance()->pop(datay) &&
		Lua::instance()->pop(datax))
	{
		return true;
	}
	logError("g_get_item_data_ex");
	return false;
}

bool StaticData::getItemDataStr( int itemID, std::string &data )
{
	CPLua->push(itemID);
	if (CPLua->call("g_get_item_data_str", 1, 1) &&
		CPLua->pop(data))
	{
		return true;
	}
	logError("g_get_item_data_str");
	return false;
}

bool StaticData::getGuanGongCloth( int gender, int &itemID )
{
	Lua::instance()->push(gender);
	if (Lua::instance()->call("g_get_guan_gong_cloth", 1, 1) &&
		Lua::instance()->pop(itemID))
	{
		return true;
	}
	logError("g_get_guan_gong_cloth");
	return false;
}

bool StaticData::getGuildFuLiItem( int index, int &itemID )
{
	Lua::instance()->push(index);
	if (Lua::instance()->call("g_get_guild_fu_li_item", 1, 1) &&
		Lua::instance()->pop(itemID))
	{
		return true;
	}
	logError("g_get_guild_fu_li_item");
	return false;
}

bool StaticData::getCityMasterClothItemID( int gender, int &itemID )
{
	CPLua->push(gender);
	if (CPLua->call("g_get_city_master_cloth_item_id", 1, 1)
		&& CPLua->pop(itemID))
	{
		return true;
	}
	logError("g_get_city_master_cloth_item_id");
	return false;
}

bool StaticData::getDefaultEquip( int level, int gender, int &clothID, int &weaponID, int &wingsID )
{
	CPLua->push(level);
	CPLua->push(gender);
	if (CPLua->call("g_get_default_equip", 2, 3)
		&& CPLua->pop(wingsID)
		&& CPLua->pop(weaponID)
		&& CPLua->pop(clothID))
	{
		return true;
	}
	logError("g_get_default_equip");
	return false;
}

bool StaticData::getNPCDefaultEquip( int npcID, int &clothID )
{
	CPLua->push(npcID);
	if (CPLua->call("g_get_npc_default_equip", 1, 1)
		&& CPLua->pop(clothID))
	{
		return true;
	}
	logError("g_get_npc_default_equip");
	return false;
}

bool StaticData::getChengBaTianXiaEquip( int gender, int &clothID, int &weaponID, int &wingsID )
{
	CPLua->push(gender);
	if (CPLua->call("g_get_cheng_ba_tian_xia_equip", 1, 3)
		&& CPLua->pop(wingsID)
		&& CPLua->pop(weaponID)
		&& CPLua->pop(clothID))
	{
		return true;
	}
	logError("g_get_cheng_ba_tian_xia_equip");
	return false;
}

bool StaticData::getSkillNeedMana( int skillID, int &mana )
{
	Lua::instance()->push(skillID);
	if (Lua::instance()->call("g_get_skill_need_mana", 1, 1) &&
		Lua::instance()->pop(mana))
	{
		return true;
	}
	logError("g_get_skill_need_mana");
	return false;
}

bool StaticData::getSkillCD( int skillID, int &cd )
{
	Lua::instance()->push(skillID);
	if (Lua::instance()->call("g_get_skill_cd", 1, 1) &&
		Lua::instance()->pop(cd))
	{
		return true;
	}
	logError("g_get_skill_cd");
	return false;
}

bool StaticData::getSkillSound( int skillID, std::string &soundPath )
{
	Lua::instance()->push(skillID);
	if (Lua::instance()->call("g_get_skill_sound", 1, 1) &&
		Lua::instance()->pop(soundPath))
	{
		return true;
	}
	logError("g_get_skill_sound");
	return false;
}

bool StaticData::getSaiMaChangFirstSkill( int &skillID )
{
	if (Lua::instance()->call("g_get_sai_ma_chang_first_skill", 0, 1) &&
		Lua::instance()->pop(skillID))
	{
		return true;
	}
	logError("g_get_sai_ma_chang_first_skill");
	return false;
}

bool StaticData::getMonsterPlantFlag( int mID, int &flag )
{
	Lua::instance()->push(mID);
	if (Lua::instance()->call("g_get_monster_plant_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_monster_plant_flag");
	return false;
}

bool StaticData::getMonsterLevel( int mID, int &level )
{
	Lua::instance()->push(mID);
	if (Lua::instance()->call("g_get_monster_level", 1, 1) &&
		Lua::instance()->pop(level))
	{
		return true;
	}
	logError("g_get_monster_level");
	return false;
}

bool StaticData::getMonsterScale( int mID, float &scale )
{
	Lua::instance()->push(mID);
	if (Lua::instance()->call("g_get_monster_scale", 1, 1) &&
		Lua::instance()->pop(scale))
	{
		return true;
	}
	logError("g_get_monster_scale");
	return false;
}

bool StaticData::getMonsterBossFlag( int mID, int &flag )
{
	Lua::instance()->push(mID);
	if (Lua::instance()->call("g_get_monster_boss_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_monster_boss_flag");
	return false;
}

bool StaticData::getMonsterSelFlag( int mID, int &flag )
{
	Lua::instance()->push(mID);
	if (Lua::instance()->call("g_get_monster_sel_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_monster_sel_flag");
	return false;
}

bool StaticData::getMonsterName( int mID, std::string &name )
{
	CPLua->push(mID);
	if (CPLua->call("g_get_monster_name", 1, 1)
		&& CPLua->pop_utf8(name))
	{
		return true;
	}
	logError("g_get_monster_name");
	return false;
}

bool StaticData::getPetAnimName( int petID, int reborn, std::string &animName )
{
	Lua::instance()->push(petID);
	Lua::instance()->push(reborn);
	if (Lua::instance()->call("g_get_pet_anim_name", 2, 1) &&
		Lua::instance()->pop(animName))
	{
		return true;
	}
	logError("g_get_pet_anim_name");
	return false;
}

bool StaticData::getDogNameColor( int level, ccColor3B &color )
{
	int r = 255, g = 255, b = 255;
	Lua::instance()->push(level);
	if (Lua::instance()->call("g_get_dog_name_color", 1, 3) &&
		Lua::instance()->pop(b) &&
		Lua::instance()->pop(g) &&
		Lua::instance()->pop(r))
	{
		color = ccc3(r, g, b);
		return true;
	}
	logError("g_get_dog_name_color");
	return false;
}

bool StaticData::getFirstRankJobTest( int npcID, int &job, int &gender )
{
	Lua::instance()->push(npcID);
	if (Lua::instance()->call("g_get_first_rank_job_test", 1, 2) &&
		Lua::instance()->pop(gender) &&
		Lua::instance()->pop(job))
	{
		return true;
	}
	logError("g_get_first_rank_job_test");
	return false;
}

bool StaticData::getPortalNPCFlag( int npcID, int &flag )
{
	Lua::instance()->push(npcID);
	if (Lua::instance()->call("g_get_portal_npc_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_portal_npc_flag");
	return false;
}

bool StaticData::getNPCFunctionCount( int npcID, int &count )
{
	Lua::instance()->push(npcID);
	if (Lua::instance()->call("g_get_npc_function_count", 1, 1) &&
		Lua::instance()->pop(count))
	{
		return true;
	}
	logError("g_get_npc_function_count");
	return false;
}

bool StaticData::getNPCFunctionCaption( int npcID, int funcID, std::string &caption )
{
	Lua::instance()->push(npcID);
	Lua::instance()->push(funcID);
	if (Lua::instance()->call("g_get_npc_function_caption", 2, 1) &&
		Lua::instance()->pop_utf8(caption))
	{
		return true;
	}
	logError("g_get_npc_function_caption");
	return false;
}

bool StaticData::getNPCHideInWorldMapFlag( int npcID, int &flag )
{
	Lua::instance()->push(npcID);
	if (Lua::instance()->call("g_get_npc_hide_in_world_map_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_npc_hide_in_world_map_flag");
	return false;
}

bool StaticData::getCityMasterFlag( int npcID, int &flag )
{
	Lua::instance()->push(npcID);
	if (Lua::instance()->call("g_get_city_master_flag", 1, 1) &&
		Lua::instance()->pop(flag))
	{
		return true;
	}
	logError("g_get_city_master_flag");
	return false;
}

bool StaticData::getCityMasterCloth( int job, int gender, int &clothID )
{
	Lua::instance()->push(job);
	Lua::instance()->push(gender);
	if (Lua::instance()->call("g_get_city_master_cloth", 2, 1) &&
		Lua::instance()->pop(clothID))
	{
		return true;
	}
	logError("g_get_city_master_cloth");
	return false;
}

bool StaticData::getGuildConvoyNPC( int &npcID )
{
	if (CPLua->call("g_get_guild_convoy_npc", 0, 1) &&
		CPLua->pop(npcID))
	{
		return true;
	}
	logError("g_get_guild_convoy_npc");
	return false;
}

bool StaticData::getNPCName( int npcID, std::string &name )
{
	CPLua->push(npcID);
	if (CPLua->call("cb_get_npc_name", 1, 1)
		&& CPLua->pop_utf8(name))
	{
		return true;
	}
	logError("cb_get_npc_name");
	return false;
}

bool StaticData::getQuestSrcNPC( int qID, int &npcID )
{
	Lua::instance()->push(qID);
	if (Lua::instance()->call("cb_get_quest_src_npc", 1, 1) &&
		Lua::instance()->pop(npcID))
	{
		return true;
	}
	logError("cb_get_quest_src_npc");
	return false;
}

bool StaticData::getQuestTgtNPC( int qID, int &npcID )
{
	Lua::instance()->push(qID);
	if (Lua::instance()->call("cb_get_quest_tgt_npc", 1, 1) &&
		Lua::instance()->pop(npcID))
	{
		return true;
	}
	logError("cb_get_quest_tgt_npc");
	return false;
}

bool StaticData::getGeneIcon( int geneID, std::string &icon )
{
	Lua::instance()->push(geneID);
	if (Lua::instance()->call("g_get_gene_icon", 1, 1) &&
		Lua::instance()->pop(icon))
	{
		return true;
	}
	logError("g_get_gene_icon");
	return false;
}

bool StaticData::getActivityData( int activityID, const std::string &key, int &data )
{
	Lua::instance()->push(activityID);
	Lua::instance()->push(key);
	if (Lua::instance()->call("get_activity_data", 2, 1) &&
		Lua::instance()->pop(data))
	{
		return true;
	}
	logError("get_activity_data");
	return false;
}

bool StaticData::getActivityName( int activityID, std::string &name )
{
	CPLua->push(activityID);
	if (CPLua->call("get_activity_name", 1, 1)
		&& CPLua->pop_utf8(name))
	{
		return true;
	}
	logError("get_activity_name");
	return false;
}

bool StaticData::getGlobalData( const std::string &key, int &data )
{
	Lua::instance()->push(key);
	if (Lua::instance()->call("g_get_global_game_data", 1, 1) &&
		Lua::instance()->pop(data))
	{
		return true;
	}
	logError("g_get_global_game_data");
	return false;
}

bool StaticData::getGlobalData( const std::string &key, float &data )
{
	Lua::instance()->push(key);
	if (Lua::instance()->call("g_get_global_game_data", 1, 1) &&
		Lua::instance()->pop(data))
	{
		return true;
	}
	logError("g_get_global_game_data");
	return false;
}

bool StaticData::getConvoyBeautyExp( int index, int level, int &exp )
{
	Lua::instance()->push(index);
	Lua::instance()->push(level);
	if (Lua::instance()->call("gdGame", "getGirlExp", 2, 1) &&
		Lua::instance()->pop(exp))
	{
		return true;
	}
	logError("gdGame.getGirlExp");
	return false;
}

bool StaticData::getFunctionOpenNeed( const std::string &funcName, int &needReborn, int &needLevel, int &needQuest, int &hide, int &openDays )
{
	Lua::instance()->push(funcName);
	if (Lua::instance()->call("gdGame", "getFunctionOpenNeed", 1, 5) &&
		Lua::instance()->pop(openDays) &&
		Lua::instance()->pop(hide) &&
		Lua::instance()->pop(needQuest) &&
		Lua::instance()->pop(needLevel) &&
		Lua::instance()->pop(needReborn))
	{
		return true;
	}
	logError("gdGame.getFunctionOpenNeed");
	return false;
}

bool StaticData::getNextOpenFunction( const std::string &funcName, std::string &nextFuncName )
{
	Lua::instance()->push(funcName);
	if (Lua::instance()->call("gdGame", "getNextOpenFunction", 1, 1) &&
		Lua::instance()->pop(nextFuncName))
	{
		return true;
	}
	logError("gdGame.getNextOpenFunction");
	return false;
}

bool StaticData::getArenaBuffData( int buffID, float &buffFactor )
{
	Lua::instance()->push(buffID);
	if (Lua::instance()->call("gdGame", "getChallengeBuff", 1, 1) &&
		Lua::instance()->pop(buffFactor))
	{
		return true;
	}
	logError("gdGame.getChallengeBuff");
	return false;
}

bool StaticData::getWeekSalaryData( int openDays, int &coupon, int &honor, int &index )
{
	CPLua->push(openDays);
	if (CPLua->call("gdGame", "getWeekfleeData", 1, 3)
		&& CPLua->pop(index)
		&& CPLua->pop(honor)
		&& CPLua->pop(coupon))
	{
		return true;
	}
	logError("gdGame.getWeekfleeData");
	return false;
}

bool StaticData::getRebornStrAndColor( int reborn, std::string &str, cocos2d::ccColor3B &color )
{
	int r = 0, g = 0, b = 0;
	Lua::instance()->push(reborn);
	if (Lua::instance()->call("g_get_reborn_str_and_color", 1, 4) &&
		Lua::instance()->pop(b) &&
		Lua::instance()->pop(g) &&
		Lua::instance()->pop(r) &&
		Lua::instance()->pop_utf8(str))
	{
		color = ccc3(r, g, b);
		return true;
	}
	logError("g_get_reborn_str_and_color");
	return false;
}

bool StaticData::getAnimOrderData( int direction, int action, int animType, int &zOrder )
{
	CPLua->push(direction);
	CPLua->push(action);
	CPLua->push(animType);
	if (CPLua->call("g_get_anim_order_data", 3, 1)
		&& CPLua->pop(zOrder))
	{
		return true;
	}
	logError("g_get_anim_order_data");
	return false;
}

bool StaticData::getGuildShopItemCount( int &count )
{
	if (Lua::instance()->call("g_get_guild_shop_item_count", 0, 1) &&
		Lua::instance()->pop(count))
	{
		return true;
	}
	logError("g_get_guild_shop_item_count");
	return false;
}

bool StaticData::getGuildShopItemData( int index, int &sid, int &price, int &needLevel )
{
	Lua::instance()->push(index);
	if (Lua::instance()->call("g_get_guild_shop_item_data", 1, 3) &&
		Lua::instance()->pop(needLevel) &&
		Lua::instance()->pop(price) &&
		Lua::instance()->pop(sid))
	{
		return true;
	}
	logError("g_get_guild_shop_item_data");
	return false;
}

bool StaticData::getShopItemPrice( int sid, int buyType, int &price )
{
	Lua::instance()->push(sid);
	Lua::instance()->push(buyType);
	if (Lua::instance()->call("g_get_shop_item_price_by_sid", 2, 1) &&
		Lua::instance()->pop(price))
	{
		return true;
	}
	logError("g_get_shop_item_price_by_sid");
	return false;
}

bool StaticData::getActivationGiftItemCount( int &count )
{
	if (Lua::instance()->call("g_get_activation_gift_item_count", 0, 1) &&
		Lua::instance()->pop(count))
	{
		return true;
	}
	logError("g_get_activation_gift_item_count");
	return false;
}

bool StaticData::getActivationGiftItemData( int index, int &sid, int &count )
{
	Lua::instance()->push(index);
	if (Lua::instance()->call("g_get_activation_gift_item_data", 1, 2) &&
		Lua::instance()->pop(count) &&
		Lua::instance()->pop(sid))
	{
		return true;
	}
	logError("g_get_activation_gift_item_data");
	return false;
}

bool StaticData::getLevelSportsGiftData( int index, int &dataX, int &dataY, int &reborn )
{
	CPLua->push(index);
	if (CPLua->call("g_get_level_sport_gift_data", 1, 3)
		&& CPLua->pop(reborn)
		&& CPLua->pop(dataY)
		&& CPLua->pop(dataX))
	{
		return true;
	}
	logError("g_get_level_sport_gift_data");
	return false;
}

bool StaticData::getMountSportsGiftData( int index, int &dataX, int &dataY )
{
	CPLua->push(index);
	if (CPLua->call("g_get_mount_sport_gift_data", 1, 2) &&
		CPLua->pop(dataY) &&
		CPLua->pop(dataX))
	{
		return true;
	}
	logError("g_get_mount_sport_gift_data");
	return false;
}

bool StaticData::getStoneSportsGiftData( int index, int &dataX, int &dataY )
{
	CPLua->push(index);
	if (CPLua->call("g_get_stone_sport_gift_data", 1, 2) &&
		CPLua->pop(dataY) &&
		CPLua->pop(dataX))
	{
		return true;
	}
	logError("g_get_stone_sport_gift_data");
	return false;
}

bool StaticData::getGuildPrayCount( int gongDianLevel, int &count )
{
	Lua::instance()->push(gongDianLevel);
	if (Lua::instance()->call("g_get_guild_pray_count", 1, 1) &&
		Lua::instance()->pop(count))
	{
		return true;
	}
	logError("g_get_guild_pray_count");
	return false;
}

bool StaticData::getGuildPrayExp( int level, int prayType, int &exp )
{
	Lua::instance()->push(level);
	Lua::instance()->push(prayType);
	if (Lua::instance()->call("g_get_guild_pray_exp", 2, 1) &&
		Lua::instance()->pop(exp))
	{
		return true;
	}
	logError("g_get_guild_pray_exp");
	return false;
}

bool StaticData::getGuildBuildingGuangHuan(int indexID,std::string &hurt,int &time,int &guildMoney,std::string &name)
{
	Lua::instance()->push(indexID);
	if (Lua::instance()->call("g_get_guild_building_guang_huan",1,4) &&
		Lua::instance()->pop_utf8(name) &&
		Lua::instance()->pop(guildMoney) &&
		Lua::instance()->pop(time) &&
		Lua::instance()->pop_utf8(hurt))
	{
		return true;
	}
	logError("g_get_guild_building_guang_huan");
	return false;
}

bool StaticData::getGuildBuildingGuangHuan(int indexID,int &time,int &guildMoney,std::string &name)
{
    Lua::instance()->push(indexID);
	if (Lua::instance()->call("g_get_guild_building_guang_huan_float_panel",1,3) &&
		Lua::instance()->pop_utf8(name) &&
		Lua::instance()->pop(guildMoney) &&
		Lua::instance()->pop(time))
	{
		return true;
	}
	logError("g_get_guild_building_guang_huan_float_panel");
	return false;
}

bool StaticData::getGuildBuildingGuangHuanItemCount(int &index)
{
	if (Lua::instance()->call("g_get_guild_building_guang_huan_item_count",0,1) &&
		Lua::instance()->pop(index))
	{
		return true;
	}
	logError("g_get_guild_building_guang_huan_item_count");
	return false;
} 

bool StaticData::getGuildBuildingTanXianCount(int buildingLevel,int &totalcnt)
{
	Lua::instance()->push(buildingLevel);
	if (Lua::instance()->call("g_guild_building_tan_xian_count",1,1) && 		
		Lua::instance()->pop(totalcnt))	
	{
		return true;
	}
	logError("g_guild_building_tan_xian_count");
	return false;
}

bool StaticData::getGuildBuildingShenShou(int &recommendNum,int &levelNum,int &challengeNum,int &consume,int &challengeNums,int &guildMoney)
{
	if (Lua::instance()->call("g_get_guild_building_shen_shou",0,6) &&
		Lua::instance()->pop(guildMoney) &&
		Lua::instance()->pop(challengeNums) &&
		Lua::instance()->pop(consume) &&
		Lua::instance()->pop(challengeNum) &&
		Lua::instance()->pop(levelNum) &&
		Lua::instance()->pop(recommendNum))
	{
		return true;
	}
	logError("g_get_guild_building_shen_shou");
	return false;
}

bool StaticData::getGuildBuildingName( int buildingID, std::string &name )
{
	Lua::instance()->push(buildingID);
	if (Lua::instance()->call("g_get_guild_building_name", 1, 1) &&
		Lua::instance()->pop_utf8(name))
	{
		return true;
	}
	logError("g_get_guild_building_name");
	return false;
}

bool StaticData::getGuildBuildingOpenLevel( int buildingID, int &openLevel )
{
	Lua::instance()->push(buildingID);
	if (Lua::instance()->call("g_get_guild_building_open_level", 1, 1) &&
		Lua::instance()->pop(openLevel))
	{
		return true;
	}
	logError("g_get_guild_building_open_level");
	return false;
}

bool StaticData::getGuildBuildingMaxLevel( int buildingID, int &maxLevel )
{
	Lua::instance()->push(buildingID);
	if (Lua::instance()->call("g_get_guild_building_max_level", 1, 1) &&
		Lua::instance()->pop(maxLevel))
	{
		return true;
	}
	logError("g_get_guild_building_max_level");
	return false;
}

bool StaticData::getGuildBuildingLevelUpData( int buildingID, int level, int &money, int &time )
{
	Lua::instance()->push(buildingID);
	Lua::instance()->push(level);
	if (Lua::instance()->call("g_get_guild_building_level_up_data", 2, 2) &&
		Lua::instance()->pop(time) &&
		Lua::instance()->pop(money))
	{
		return true;
	}
	logError("g_get_guild_building_level_up_data");
	return false;
}

bool StaticData::getVIPData( int vipLevel, const std::string &key, int &data )
{
	Lua::instance()->push(vipLevel);
	Lua::instance()->push(key);
	if (Lua::instance()->call("g_get_vip_data", 2, 1) &&
		Lua::instance()->pop(data))
	{
		return true;
	}
	logError("g_get_vip_data");
	return false;
}

bool StaticData::getVIPData( int vipLevel, const std::string &key, float &data )
{
	Lua::instance()->push(vipLevel);
	Lua::instance()->push(key);
	if (Lua::instance()->call("g_get_vip_data", 2, 1) &&
		Lua::instance()->pop(data))
	{
		return true;
	}
	logError("g_get_vip_data");
	return false;
}

bool StaticData::getVIPDesc( int vipLevel, std::string &info )
{
    Lua::instance()->push(vipLevel);	
	if (Lua::instance()->call("g_get_vip_desc",1,1) && 
		Lua::instance()->pop_utf8(info))
	{
		return true;
	}
	logError("g_get_vip_desc");
	return false;
}

bool StaticData::getClearCDCost( int cdID, int &cost )
{
	Lua::instance()->push(cdID);
	if (Lua::instance()->call("g_get_clear_cd_cost", 1, 1) &&
		Lua::instance()->pop(cost))
	{
		return true;
	}
	logError("g_get_clear_cd_cost");
	return false;
}

bool StaticData::getHeadNamesData( int id, const std::string &key, int &data )
{
	CPLua->push(id);
	CPLua->push(key);
	if (CPLua->call("g_get_head_names_int_data", 2, 1)
		&& CPLua->pop(data))
	{
		return true;
	}
	logError("g_get_head_names_int_data");
	return false;
}

bool StaticData::getHeadNamesData( int id, const std::string &key, std::string &data )
{
	CPLua->push(id);
	CPLua->push(key);
	if (CPLua->call("g_get_head_names_str_data", 2, 1)
		&& CPLua->pop_utf8(data))
	{
		return true;
	}
	logError("g_get_head_names_str_data");
	return false;
}

//bool StaticData::getHeadNamesData( int id, const std::string &key,std::string )

bool StaticData::getHeadNamesTitle( int id, int job, int gender, std::string &title )
{
	CPLua->push(id);
	CPLua->push(job);
	CPLua->push(gender);
	if (CPLua->call("g_get_head_names_title", 3, 1)
		&& CPLua->pop_utf8(title))
	{
		return true;
	}
	logError("g_get_head_names_title");
	return false;
}

bool StaticData::getHeadNamesGeneId( int id, int job, int gender, int &geneid )
{
	CPLua->push(id);
	CPLua->push(job);
	CPLua->push(gender);
	if (CPLua->call("g_get_head_names_geneid", 3, 1)
		&& CPLua->pop(geneid))
	{
		return true;
	}
	logError("g_get_head_names_geneid");
	return false;
}

bool StaticData::getHeadNamesAttrstring( int id, int key , std::string &title )
{
	CPLua->push(id);
	CPLua->push(key);
	if (CPLua->call("g_get_head_names_attrstring", 2, 1)
		&& CPLua->pop_utf8(title))
	{
		return true;
	}
	logError("g_get_head_names_attrstring");
	return false;
}

bool StaticData::getHeadNamesShowTitle( int id, int job, int gender, std::string &showTitle )
{
	CPLua->push(id);
	CPLua->push(job);
	CPLua->push(gender);
	if (CPLua->call("g_get_head_names_show_title", 3, 1)
		&& CPLua->pop_utf8(showTitle))
	{
		return true;
	}
	logError("g_get_head_names_show_title");//g_get_head_names_show_prop
	return false;
}

bool StaticData::getHeadNamesAddPropCnt( int id, int &count )
{
	CPLua->push(id);
	if (CPLua->call("g_get_head_names_add_prop_count", 1, 1)
		&& CPLua->pop(count))
	{
		return true;
	}
	logError("g_get_head_names_add_prop_count");
	return false;
}

bool StaticData::getHeadNamesCount( int &count )
{
	if (CPLua->call("g_get_head_names_count", 0, 1)
		&& CPLua->pop(count))
	{
		return true;
	}
	logError("g_get_head_names_count");
	return false;
}

bool StaticData::getSingleRechargeTableLength( int &length )
{
	if (Lua::instance()->call("get_single_recharge_table_length",0,1) &&
		Lua::instance()->pop(length))
	{
		return true;
	}
	logError("get_single_recharge_table_length");
	return false;
}

bool StaticData::getSingleRechargeArticleID( int indexID,int &data )
{
	Lua::instance()->push(indexID);
	if (Lua::instance()->call("get_single_recharge_article_id",1,1) &&
		Lua::instance()->pop(data))
	{
		return true;
	}
	logError("get_single_recharge_article_id");
	return false;
}

bool StaticData::getSingleRechargeLabelData(int wingID,std::string &word)
{
	Lua::instance()->push(wingID);	
	if (Lua::instance()->call("get_single_recharge_label_data",1,1) &&
		Lua::instance()->pop_utf8(word))
	{
		return true;
	}
	logError("get_single_recharge_label_data");

	return false;
}

bool StaticData::getSingleRechargeLabelDesc( int wingID,std::string &info )
{
	Lua::instance()->push(wingID);
	if (Lua::instance()->call("get_single_recharge_label_desc",1,1) &&
		Lua::instance()->pop_utf8(info))
	{
		return true;
	}
	logError("get_single_recharge_label_desc");

	return false;
}

bool StaticData::getSingleRechargeLabelProperty( int wingID,std::string &wingProp )
{
	Lua::instance()->push(wingID);
	if (Lua::instance()->call("get_single_recharge_label_property",1,1) &&
		Lua::instance()->pop_utf8(wingProp))
	{
		return true;
	}
	logError("get_single_recharge_label_property");

	return false;
}


