#include "ActivityDataHelper.h"
#include "cocos2d.h"
#include "MsgAuth.h"
#include "MsgLogin.h"
#include "UserDataModule.h"
#include "ModuleData.h"

#include "ext/CCFlashAnimation.h"
#include "event/CPEvent.h"
#include "script/LuaWrapper.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userData/SystemData.h"
#include "userdata/HeroData.h"
#include "userData/netdata/AliveGhost.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/GameRole.h"

#include "network/HandleMessage.h"
#include "network/MsgListener.h"
#include "ErrorDefinition.h"
#include "GuildDefinition.h"

#include "GuildModule.h"

using namespace cocos2d;

//////////ActivityDataHelper///////////////////////////////////////////////
const std::string gdActivityGift = "gdActivityGift";
const std::string gdGiftPacks = "gdGiftPacks";
const std::string gdItems = "gdItems";
const std::string gdOpenActivitys = "gdOpenActivitys";
const std::string gdInvestPlan = "gdInvestPlan";
const std::string gdActiveData = "gdActiveData";

int ActivityDataHelper::getMainSize()
{
	int value;
	if (LuaData::getProp_size(gdActivityGift,0,"",value))
	{
		return value;
	}
	return 0;
}
bool  ActivityDataHelper::hasRewards(int idx)
{
	int oSize = getRewardsSize(idx);
	return (oSize>0)?true:false;
}
int ActivityDataHelper::getRewardsSize(int idx)
 {
	 int value;
	 if (LuaData::getProp_size(gdActivityGift,idx,"rewards",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getRewardID(int idx,int sidx)
 {
	 int value;
	 if (LuaData::getProp(gdActivityGift,idx,"rewards",sidx,"iid",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getDataX(int idx,int sidx)
 {
	 int value = 0;
	 if (LuaData::getProp(gdActivityGift,idx,"rewards",sidx,"datax",value))
	 {
		 return value;
	 }
	 return 0;
 }

 int ActivityDataHelper::getDataY( int idx, int sidx )
 {
	 int ret = 0;
	 if (LuaData::getProp(gdActivityGift,idx,"rewards",sidx,"datay",ret))
	 {
		 return ret;
	 }
	 return 0;
 }

 bool  ActivityDataHelper::isGiftPack(int sid)
 {
	 int gid = getGiftID(sid);
	 return (gid>0)?true:false;
 }
  int ActivityDataHelper::getGiftID(int sid)
 {
	 int value;
	 if (LuaData::getProp(gdItems,sid,"gift",value))
	 {
		 return value;
	 }
	 return false;
 }
 std::string  ActivityDataHelper::getGiftName(int idx)
 {
	 std::string value;
	 if (LuaData::getProp(gdGiftPacks,idx,"name",value))
	 {
		 return value;
	 }
	 return 0;
 }
 bool  ActivityDataHelper::hasGiftItem(int sid)
 {
	 int oSize = getItemsSize(sid);
	 return (oSize>0)?true:false;
 }
 bool  ActivityDataHelper::hasGiftExItem(int sid)
 {
	 int oSize = getExItemsSize(sid);
	 return (oSize>0)?true:false;
 }
 int ActivityDataHelper::getItemsSize(int idx)
 {
	 int value;
	 if (LuaData::getProp_size(gdGiftPacks,idx,"items",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int ActivityDataHelper::getExItemsSize(int idx)
 {
	 int value;
	 if (LuaData::getProp_size(gdGiftPacks,idx,"exitems",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getItemID(int idx,int sidx)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"items",sidx,"iid",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getExItemID(int idx,int sidx)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"exitems",sidx,"iid",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getItemID(int idx,int sidx,std::string key)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"items",sidx,key,value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getExItemID(int idx,int sidx,std::string key)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"exitems",sidx,key,value))
	 {
		 return value;
	 }
	 return 0;
 }

  int  ActivityDataHelper::getItemType(int idx,int sidx)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"items",sidx,"type",value))
	 {
		 return value;
	 }
	 return 0;
 }
  int  ActivityDataHelper::getExItemType(int idx,int sidx)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"exitems",sidx,"type",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getItemCnt(int idx,int sidx)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"items",sidx,"count",value))
	 {
		 return value;
	 }
	 return 0;
 }
 int  ActivityDataHelper::getExItemCnt(int idx,int sidx)
 {
	 int value;
	 if (LuaData::getProp(gdGiftPacks,idx,"exitems",sidx,"count",value))
	 {
		 return value;
	 }
	 return 0;
 }
 std::string  ActivityDataHelper::getItemIcon(int iid)
 {
	 std::string value;
	 if (LuaData::getProp(gdItems,iid,"icon",value))
	 {
		 return value;
	 }
	 return 0;
 }

  int  ActivityDataHelper::getItemStaticID(int giftType,int idx,int sidx)
 {
	 if (ActivityDataHelper::hasRewards(giftType))
	 {
		 int sid = ActivityDataHelper::getRewardID(giftType,idx);
		 if (ActivityDataHelper::isGiftPack(sid))
		 {
			 int gid = ActivityDataHelper::getGiftID(sid);
			 if (ActivityDataHelper::hasGiftItem(gid))
			 {
				 int pType = ActivityDataHelper::getItemType(gid,sidx);
				 if (pType==Type_Job) 
				 {
					 return ActivityDataHelper::getItemID(gid,sidx,getPlayerJob());
				 }
				 else if (pType==Type_Gender)
				 {
					 return ActivityDataHelper::getItemID(gid,sidx,getPlayerGender());
				 }
				 return ActivityDataHelper::getItemID(gid,sidx);
			 }
		 }
		 else
		 {
			 return sid;
		 }
	 }
	 return 0;
 }
  int  ActivityDataHelper::getExItemStaticID(int giftType,int idx,int sidx)
 {
	 if (ActivityDataHelper::hasRewards(giftType))
	 {
		 int sid = ActivityDataHelper::getRewardID(giftType,idx);
		 if (ActivityDataHelper::isGiftPack(sid))
		 {
			 int gid = ActivityDataHelper::getGiftID(sid);
			 if (ActivityDataHelper::hasGiftItem(gid))
			 {
				 int pType = ActivityDataHelper::getExItemType(gid,sidx);
				 if (pType==Type_Job)
				 {
					 return ActivityDataHelper::getExItemID(gid,sidx,getPlayerJob());
				 }
				 else if (pType==Type_Gender)
				 {
					 return ActivityDataHelper::getExItemID(gid,sidx,getPlayerGender());
				 }
				return ActivityDataHelper::getExItemID(gid,sidx);
			 }
		 }
		 else
		 {
			 return sid;
		 }
	 }
	 return 0;
 }
   int  ActivityDataHelper::getItemCount(int giftType,int idx,int sidx)
  {
	  if (ActivityDataHelper::hasRewards(giftType))
	  {
		  int sid = ActivityDataHelper::getRewardID(giftType,idx);
		  if (ActivityDataHelper::isGiftPack(sid))
		  {
			  int gid = ActivityDataHelper::getGiftID(sid);
			  if (ActivityDataHelper::hasGiftItem(gid))
			  {
				  return ActivityDataHelper::getItemCnt(gid,sidx);
			  }
		  }
		  else
		  {
			  return 0;
		  }
	  }
	  return 0;
  }
   int  ActivityDataHelper::getExItemCount(int giftType,int idx,int sidx)
  {
	  if (ActivityDataHelper::hasRewards(giftType))
	  {
		  int sid = ActivityDataHelper::getRewardID(giftType,idx); 
		  if (ActivityDataHelper::isGiftPack(sid))
		  {
			  int gid = ActivityDataHelper::getGiftID(sid);
			  if (ActivityDataHelper::hasGiftItem(gid))
			  {
				  return ActivityDataHelper::getExItemCnt(gid,sidx);
			  }
		  }
		  else
		  {
			  return 0;
		  }
	  }
	  return 0;
  }

std::string ActivityDataHelper::getPlayerJob()
{
	const int job = HeroData::getJob();
	if (job==UserData::CARRER_ZS)
	{
		return "z";
	}
	else if (job==UserData::CARRER_FS)
	{
		return "f";
	}
	else if (job==UserData::CARRER_DS)
	{
		return "d";
	}
	CCLog("+++++++++++++Error! ActivityDataHelp getPlayerJob job = %d",job);
	return "";
}
std::string ActivityDataHelper::getPlayerGender()
{
	const int gender = HeroData::getGender();
	if (gender==UserData::SEX_MALE)
	{
		return "m";
	}
	else if (gender==UserData::SEX_FEMALE)
	{
		return "w";
	}
	CCLog("+++++++++++++Error! ActivityDataHelp getPlayerGender gender = %d", gender);
	return "";
}

//开服活动
int ActivityDataHelper::getOpenActivitySize()
{
	int value;
	if (LuaData::getProp_size(gdOpenActivitys,0,"",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getOpenActivityID(int idx)
{
	int value;
	if (LuaData::getProp(gdOpenActivitys,idx,"id",value))
	{
		return value;
	}
	return 0;
}
std::string  ActivityDataHelper::getOpenActivityTitle(int idx)
{
	std::string value;
	if (LuaData::getProp(gdOpenActivitys,idx,"title",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getOpenActivityInfo(int idx)
{
	int value;
	if (LuaData::getProp(gdOpenActivitys,idx,"activityinfo",value))
	{
		return value;
	}
	return 0;
}
std::string  ActivityDataHelper::getOpenActivityRewardInfo(int idx)
{
	std::string value;
	if (LuaData::getProp(gdOpenActivitys,idx,"rewardinfo",value))
	{
		return value;
	}
	return 0;
}

int ActivityDataHelper::getOpenActivityNormalReward(int idx)
{
	int giftID = 0;
	if (LuaData::getProp(gdOpenActivitys, idx, "normalreward", 1, "reward", giftID))
	{
		int itemID = 0;
		if (LuaData::getProp(gdGiftPacks, giftID, "itemID", itemID))
		{
			return itemID;
		}
	}
	return 0;
}

int   ActivityDataHelper::getOpenActivitySpecialReward(int idx)
{
	int giftID = 0;
	if (LuaData::getProp(gdOpenActivitys, idx, "specialreward", 1, "reward", giftID))
	{
		int type = 0;
		std::string key = "iid";
		if (LuaData::getProp(gdGiftPacks, giftID, "items", 1, "type", type))
		{
			if (type==Type_Job) 
			{
				key = getPlayerJob();
			}
			else if (type==Type_Gender)
			{
				key = getPlayerGender();
			}
		}

		int sid = 0;
		if (LuaData::getProp(gdGiftPacks, giftID, "items", 1, key, sid))
		{
			return sid;
		}
	}
	return 0;
}
int   ActivityDataHelper::getOpenActivitySpecialRewardCount(int idx)
{
	int giftID = 0;
	if (LuaData::getProp(gdOpenActivitys, idx, "specialreward", 1, "reward", giftID))
	{
		int count = 0;
		if (LuaData::getProp(gdGiftPacks, giftID, "items", 1, "count", count))
		{
			return count;
		}
	}
	return 0;
}
//投资计划
int ActivityDataHelper::getInvestPlanSize()
{
	int value;
	if (LuaData::getProp_size(gdInvestPlan,0,"",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getInvestPlanID(int idx)
{
	int value;
	if (LuaData::getProp(gdInvestPlan,idx,"id",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getInvestPlanItemFir(int idx)
{
	int value;
	if (LuaData::getProp(gdInvestPlan,idx,"item1",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getInvestPlanItemSec(int idx)
{
	int value;
	if (LuaData::getProp(gdInvestPlan,idx,"item2",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getInvestPlanItemCountFir(int idx)
{
	int value;
	if (LuaData::getProp(gdInvestPlan,idx,"count1",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getInvestPlanItemCountSec(int idx)
{
	int value;
	if (LuaData::getProp(gdInvestPlan,idx,"count2",value))
	{
		return value;
	}
	return 0;
}

std::string  ActivityDataHelper::getInvestPlanRewardInfo(int idx)
{
	return 0;
}
std::string  ActivityDataHelper::getInvestPlanItemNameFir(int idx)
{
	std::string value;
	if (LuaData::getProp(gdInvestPlan,idx,"itemname1",value))
	{
		return value;
	}
	return 0;
}
std::string  ActivityDataHelper::getInvestPlanItemNameSec(int idx)
{
	std::string value;
	if (LuaData::getProp(gdInvestPlan,idx,"itemname2",value))
	{
		return value;
	}
	return 0;
}


int ActivityDataHelper::getActiveSize()
{
	int value;
	if (LuaData::getProp_size(gdActiveData,0,"",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveID(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"id",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveReward(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"active",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveDataX(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"datax",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveDataY(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"datay",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveDataZ(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"dataz",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveGoldEnable(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"goldenable",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveNeedLevel(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"needlvl",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveNPC(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"npc",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActivePrice(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"price",value))
	{
		return value;
	}
	return 0;
}
int  ActivityDataHelper::getActiveTimes(int idx)
{
	int value;
	if (LuaData::getProp(gdActiveData,idx,"times",value))
	{
		return value;
	}
	return 0;
}
std::string  ActivityDataHelper::getActiveName(int idx)
{
	std::string value;
	if (LuaData::getProp(gdActiveData,idx,"itemname2",value))
	{
		return value;
	}
	return 0;
}
std::string  ActivityDataHelper::getActiveDesc(int idx)
{
	std::string value;
	if (LuaData::getProp(gdActiveData,idx,"desc",value))
	{
		return value;
	}
	return 0;
}

int ActivityDataHelper::getActivityGiftTableCellCount( int idbegin )
{
	int count = 0;
	CPLua->push(idbegin);
	if (CPLua->call("g_activity_gift_count", 1, 1)
		&& CPLua->pop(count))
	{
		return count;
	}
	return 0;
}
