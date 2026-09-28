#ifndef __ItemOperator_h__
#define __ItemOperator_h__

#include "utils/MacroUtils.h"
#include "userdata/UserItemData.h"

class ItemOperator
{
public:
	static void useItem(int itemID);
	static void useItem(int itemID, int entityID, int count);

	static void useItemBySID(int sid);
	static void useItemBySID(int sid, int entityID, int count);

	static bool checkItemBetter(int iid);

	static bool testGoldEnough(int needGold);
	static bool testGoldEnough(int needGold, bool couponFirst);
	static bool testMoneyEnough(int needMoney);
	static bool testHonorEnough(int needHonor);

	static int getCurEquipEndure();
	static void swapPositionBySid(int sid,int swappos = 1);

	static int getItemCombatNum(UserItem* useritem);
	static int getCombatTypeNum( int type,int num ,int tag=1);
private:
	CP_MAKE_STATIC_CLASS(ItemOperator);
};
#endif //__ItemOperator_h__