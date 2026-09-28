#ifndef __BagOperator_h__
#define __BagOperator_h__

#include "utils/MacroUtils.h"
#include <vector>
#include <map>

typedef std::pair<int,int> PAIR;

class BagOperator
{
public:
	static void SetBagType(int bagtype);
	static void StartDoSortBag();//进入整理背包流程
	static void PileItem();//堆叠背包
	static void SortBag();//整理背包
	static void DoNextPile();//执行下一步操作

	static void SendPileItemMsg();//发送堆叠物品消息
	static void SendSortBagMsg(int iid,int pos);//发送整理背包消息
	static void ClearPileInfo();

	static void setcanSort(bool flag);
	static bool getcanSort();

private:
	static std::vector<int> pileList;
	static std::vector<int>::iterator pile_it;
	static int bagtype;
	static int startpos;
	static int endpos;
	static bool canSort;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	static void RepairAllFromServer(int type);
	static void StartDoRepairItem();//进入修理物品流程
	static void RepairItem();//修理物品
	static void DoNextRepair();//执行下一步操作
	static int  getRepairMoney(int sid,int endure);

	static void SendRepairMsg(int iid);//发送修理物品iid
	static void ClearRepairInfo();

private:
	static std::vector<PAIR> repairList;
	static std::vector<PAIR>::iterator repair_it;
};
#endif //__BagOperator_h__