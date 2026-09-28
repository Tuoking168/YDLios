#ifndef __StaticData_h__
#define __StaticData_h__

#include <string>
#include "CCGeometry.h"
#include "ccTypes.h"
#include "utils/MacroUtils.h"

/**
 * get static data from lua
 */
class StaticData
{
public:
	//
	static bool	reloadLuaFiles();

	// anim path
	static bool getHorseAnimPath( int animType, int id, int animState, std::string &animPath );
	static bool getAnimPath( int animType, int id, int animState, std::string &animPath );

	// map data
	static bool getMapType(int mapID, int &type);
	static bool getMapEventID(int mapID, int &eventID);
	static bool getMapMiningFlag(int mapID, int &flag);
	static bool getMapMusic(int mapID, std::string &musicName);
	static bool getMapPKRedFlag(int mapID, int &flag);
	static bool getMapSaiMaChangFlag(int mapID, int &flag);
	static bool getMapPeaceAreaCnt(int mapID, int &cnt);
	static bool getMapPeaceAreaID(int mapID, int index, int &peaceID);
	static bool getMapHideInWorldMapFlag(int mapID, int &flag);
	static bool getMapMonsterCount(int mapID, int &count);
	static bool getMapMonsterData(int mapID, int index, int &monsterID, int &posX, int &posY);
	static bool getMapEventMonsterCount(int mapID, int &count);
	static bool getMapEventMonsterData(int mapID, int index, int &monsterID, int &posX, int &posY);
	static bool getMapName(int mapID, std::string &name);
	static bool getMapChengBaTianXiaFlag(int mapID, int &flag);

	// item
	static bool getItemAnim(int itemID, std::string &anim);
	static bool getItemName(int itemID, std::string &name);
	static bool getItemIcon(int itemID, std::string &icon);
	static bool getItemIcon(int itemID, int count, std::string &icon);
	static bool getItemMiningFlag(int itemID, int &flag);
	static bool getItemSkillID(int itemID, int &skillID);
	static bool getSuitWeapon(int itemID, int &weaponID);
	static bool getItemRequireLevel(int itemID, int &reborn, int &level);
	static bool getItemRequireJob(int itemID, int &job);
	static bool getItemRequireGender(int itemID, int &gender);
	static bool getItemDataEx(int itemID, int &datax, int &datay);
	static bool getItemDataStr(int itemID, std::string &data);
	static bool getGuanGongCloth(int gender, int &itemID);
	static bool getGuildFuLiItem(int index, int &itemID);
	static bool getCityMasterClothItemID(int gender, int &itemID);
	static bool getDefaultEquip(int level, int gender, int &clothID, int &weaponID, int &wingsID);
	static bool getNPCDefaultEquip(int npcID, int &clothID);
	static bool getChengBaTianXiaEquip(int gender, int &clothID, int &weaponID, int &wingsID);

	// skill
	static bool getSkillNeedMana(int skillID, int &mana);
	static bool getSkillCD(int skillID, int &cd);
	static bool getSkillSound(int skillID, std::string &soundPath);
	static bool getSaiMaChangFirstSkill(int &skillID);

	// monster
	static bool getMonsterPlantFlag(int mID, int &flag);
	static bool getMonsterLevel(int mID, int &level);
	static bool getMonsterScale(int mID, float &scale);
	static bool getMonsterBossFlag(int mID, int &flag);
	static bool getMonsterSelFlag(int mID, int &flag);
	static bool getMonsterName(int mID, std::string &name);

	// pet
	static bool getPetAnimName(int petID, int reborn, std::string &animName);

	// dog
	static bool getDogNameColor(int level, cocos2d::ccColor3B &color);

	// npc
	static bool getFirstRankJobTest(int npcID, int &job, int &gender);
	static bool getPortalNPCFlag(int npcID, int &flag);
	static bool getNPCFunctionCount(int npcID, int &count);
	static bool getNPCFunctionCaption(int npcID, int funcID, std::string &caption);
	static bool getNPCHideInWorldMapFlag(int npcID, int &flag);
	static bool getCityMasterFlag(int npcID, int &flag);
	static bool getCityMasterCloth(int job, int gender, int &clothID);
	static bool getGuildConvoyNPC(int &npcID);
	static bool getNPCName(int npcID, std::string &name);

	// quest
	static bool getQuestSrcNPC(int qID, int &npcID);
	static bool getQuestTgtNPC(int qID, int &npcID);

	// gene
	static bool getGeneIcon(int geneID, std::string &icon);

	// activity
	static bool getActivityData(int activityID, const std::string &key, int &data);
	static bool getActivityName(int activityID, std::string &name);
	static bool getSingleRechargeTableLength(int &length);
	static bool getSingleRechargeArticleID( int indexID,int &data );
	static bool getSingleRechargeLabelData(int wingID,std::string &word);
	static bool getSingleRechargeLabelDesc(int wingID,std::string &info);
	static bool getSingleRechargeLabelProperty(int wingID,std::string &wingProp);
	
	// global
	static bool getGlobalData(const std::string &key, int &data);
	static bool getGlobalData(const std::string &key, float &data);
	static bool getConvoyBeautyExp(int index, int level, int &exp);
	static bool getFunctionOpenNeed(const std::string &funcName, int &needReborn, int &needLevel, int &needQuest, int &hide, int &openDays);
	static bool getNextOpenFunction(const std::string &funcName, std::string &nextFuncName);
	static bool getArenaBuffData(int buffID, float &buffFactor);
	static bool getWeekSalaryData(int openDays, int &coupon, int &honor, int &index);

	// player
	static bool getRebornStrAndColor(int reborn, std::string &str, cocos2d::ccColor3B &color);
	static bool getAnimOrderData(int direction, int action, int animType, int &zOrder);

	// shop
	static bool getGuildShopItemCount(int &count);
	static bool getGuildShopItemData(int index, int &sid, int &price, int &needLevel);
	static bool getShopItemPrice(int sid, int buyType, int &price);

	// gift
	static bool getActivationGiftItemCount(int &count);
	static bool getActivationGiftItemData(int index, int &sid, int &count);
	static bool getLevelSportsGiftData(int index, int &dataX, int &dataY, int &reborn);
	static bool getMountSportsGiftData(int index, int &dataX, int &dataY);
	static bool getStoneSportsGiftData(int index, int &dataX, int &dataY);

	// guild
	static bool getGuildPrayCount(int gongDianLevel, int &count);
	static bool getGuildPrayExp(int level, int prayType, int &exp);
	static bool getGuildBuildingName(int buildingID, std::string &name);
	static bool getGuildBuildingOpenLevel(int buildingID, int &openLevel);
	static bool getGuildBuildingMaxLevel(int buildingID, int &maxLevel);
	static bool getGuildBuildingLevelUpData(int buildingID, int level, int &money, int &time);
	static bool getGuildBuildingGuangHuan(int indexID,std::string &hurt,int &time,int &guildMoney,std::string &name);
	static bool getGuildBuildingGuangHuan(int indexID,int &time,int &guildMoney,std::string &name);
	static bool getGuildBuildingGuangHuanItemCount(int &index);
	static bool getGuildBuildingTanXianCount(int buildingLevel,int &totalcnt);
	static bool getGuildBuildingShenShou(int &recommendNum,int &levelNum,int &challengeNum,int &consume,int &challengeNums,int &guildMoney);

	// vip
	static bool getVIPData(int vipLevel, const std::string &key, int &data);
	static bool getVIPData(int vipLevel, const std::string &key, float &data);
	static bool getVIPDesc(int vipLevel, std::string &info);

	// cd
	static bool getClearCDCost(int cdID, int &cost);

	// head name
	static bool getHeadNamesData(int id, const std::string &key, int &data);
	static bool getHeadNamesData(int id, const std::string &key, std::string &data);
	static bool getHeadNamesTitle(int id, int job, int gender, std::string &title);
	static bool getHeadNamesShowTitle(int id, int job, int gender, std::string &showTitle);
	static bool getHeadNamesGeneId(int id, int job, int gender, int &geneid);
	static bool getHeadNamesAddPropCnt(int id, int &count);
	static bool getHeadNamesCount(int &count);
	static bool getHeadNamesAttrstring( int id, int key , std::string &title );

private:
	CP_MAKE_STATIC_CLASS(StaticData);	
	



};
#endif //__StaticData_h__