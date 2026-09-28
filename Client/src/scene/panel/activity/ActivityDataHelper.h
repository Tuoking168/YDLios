#ifndef __ActivityDataHelper_h__
#define __ActivityDataHelper_h__

#include <string>
#include "LoginModule.h"
#include "CCSprite.h"
#include "MsgGuild.h"

using namespace cocos2d;

struct GiftInfo {
	int sid;
	int cnt;
}; 
typedef std::vector<GiftInfo> GiftList;

enum ActivityGiftID
{
	Tag_NULL=0,
	
	Gift_FirstCharge					=1,
	Gift_EveryDayFirstCharge	=2,
	Gift_AddUpCharge				=3,
	Gift_MonthGift					=4 ,
	Gift_TimeLimitGift				=5,
	Gift_OnlineGift					=6,
	Gift_EveryDaySalary			=7,

	Gift_ConsumeDraw				=8,
	Gift_OpenActivity				=9,
	Gift_LevelSports					=10 ,
	Gift_MountSports				=11,
	Gift_StoneSports				=12,

	Gift_InvestPlan					=13,
	Gift_MarsHistory				=14,
	Gift_WealthGod					=15,
	Gift_TreasureHunt				=16,

	Gift_EveryDayActive			=17,
};
enum StaticDataType
{
	Type_Normal			=0,
	Type_Job				=1,
	Type_Gender			=2,
};

class ActivityDataHelper
{
protected:
	static int getMainSize();
	static bool  hasRewards(int idx);
	
	static int  getRewardID(int idx,int sidx);
	

	static bool  isGiftPack(int sid);
	static int getGiftID(int sid);
	static std::string  getGiftName(int idx);
	static bool  hasGiftItem(int sid);
	static bool  hasGiftExItem(int sid);
	static int getItemsSize(int idx);
	static int getExItemsSize(int idx);
	static int  getItemType(int idx,int sidx);
	static int  getExItemType(int idx,int sidx);
	static int  getItemID(int idx,int sidx);
	static int  getExItemID(int idx,int sidx);
	static int  getItemID(int idx,int sidx,std::string key);
	static int  getExItemID(int idx,int sidx,std::string key);
	static int  getItemCnt(int idx,int sidx);
	static int  getExItemCnt(int idx,int sidx);
	static std::string  getItemIcon(int iid);
	static std::string getPlayerJob();
	static std::string getPlayerGender();
	
public:
	static int getRewardsSize(int idx);
	static int getDataX(int idx,int sidx);
	static int getDataY(int idx, int sidx);

	static int  getItemStaticID(int giftType,int idx,int sidx);
	static int  getExItemStaticID(int giftType,int idx,int sidx);
	static int  getItemCount(int giftType,int idx,int sidx);
	static int  getExItemCount(int giftType,int idx,int sidx);

	//开服活动
	static int getOpenActivitySize();
	static int  getOpenActivityID(int idx);
	static int  getOpenActivityInfo(int idx);
	static std::string  getOpenActivityTitle(int idx);
	static std::string  getOpenActivityRewardInfo(int idx);
	static int  getOpenActivityNormalReward(int idx);
	static int  getOpenActivitySpecialReward(int idx);
	static int  getOpenActivitySpecialRewardCount(int idx);
	static int  getActivityGiftTableCellCount(int idbegin);
	//投资计划
	static int getInvestPlanSize();
	static int  getInvestPlanID(int idx);
	static int  getInvestPlanItemFir(int idx);
	static int  getInvestPlanItemSec(int idx);
	static int  getInvestPlanItemCountFir(int idx);
	static int  getInvestPlanItemCountSec(int idx);
	static std::string  getInvestPlanRewardInfo(int idx);
	static std::string  getInvestPlanItemNameFir(int idx);
	static std::string  getInvestPlanItemNameSec(int idx);
	//每日活跃
	static int getActiveSize();
	static int  getActiveID(int idx);
	static int  getActiveReward(int idx);
	static int  getActiveDataX(int idx); 
	static int  getActiveDataY(int idx);
	static int  getActiveDataZ(int idx);
	static int  getActiveGoldEnable(int idx);
	static int  getActiveNeedLevel(int idx);
	static int  getActiveNPC(int idx);  
	static int  getActivePrice(int idx);
	static int  getActiveTimes(int idx);
	static std::string  getActiveName(int idx);
	static std::string  getActiveDesc(int idx);
private:
	ActivityDataHelper();
	ActivityDataHelper(const ActivityDataHelper &);
	ActivityDataHelper &operator=(const ActivityDataHelper &);  
	~ActivityDataHelper();

};

#endif //__ActivityDataHelper_h__