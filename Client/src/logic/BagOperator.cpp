#include "BagOperator.h"
#include "ItemDefinition.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/UserItemData.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "MsgItem.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "script/LuaWrapper.h"
#include "MsgItem.h"
#include <algorithm>


std::vector<int>::iterator BagOperator::pile_it;

std::vector<int> BagOperator::pileList;
int BagOperator::bagtype = 0;
int BagOperator::startpos = 0;
int BagOperator::endpos = 0;
bool BagOperator::canSort = true;

bool BagSort(UserItem* v1, UserItem* v2){	
	return v1->sid < v2->sid;	
}

void BagOperator::StartDoSortBag()
{	
	if (getcanSort())
	{
		setcanSort(false);
		ClearPileInfo();
		PileItem();
		DoNextPile();
	}
}

void BagOperator::SetBagType( int bagtype )
{
	int bag_type = 0;
	int start,end;
	switch (bagtype)
	{
	case Self_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		bag_type =  ItemPos::Bag_Player;
		break;
	case Role_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		bag_type =  ItemPos::Bag_Player;
		break;
	case Pet_Bag:
		start = ItemPos::Pet_Bag_Start;
		end =  ItemPos::Pet_Bag_End;
		bag_type =  ItemPos::Bag_Pet;
		break;
	case House_Bag:
		start = ItemPos::Treasure_Warehouse_Start;
		end =  ItemPos::Treasure_Warehouse_End;
		bag_type =  ItemPos::Bag_Warehouse;
		break;
	case Booth_Bag:
		start = ItemPos::Market_Bag_Start;
		end =  ItemPos::Market_Bag_End;
		bag_type =  ItemPos::Bag_Market;
		break;
	case Pet_Bag_Shop:
		start = ItemPos::Pet_Bag_Start;
		end =  ItemPos::Pet_Bag_End;
		bag_type =  ItemPos::Bag_Pet;
		break;
	case Stone_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		bag_type =  ItemPos::Bag_Player;
		break;
	case NPC_Bag:
		start = ItemPos::NPC_Bag_Start;
		end =  ItemPos::NPC_Bag_End;
		bag_type =  ItemPos::Bag_NPC;
		break;
	case Sell_Bag:
		start = ItemPos::Player_Bag_Start;
		end =  ItemPos::Player_Bag_End;
		bag_type =  ItemPos::Bag_Player;
		break;
	default:
		start = 0;
		end =  0;
		bag_type =  ItemPos::Bag_All;
		break;
	}
	BagOperator::startpos = start;
	BagOperator::endpos = end;
	BagOperator::bagtype = bag_type;
}

void BagOperator::PileItem()
{
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	std::map<int,int> ItemList;
	ItemList.clear();
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		int pos=it->first;
		if ((pos >= BagOperator::startpos && pos<BagOperator::endpos ))
		{
			UserItem* item=it->second;
			if (item->count<item->maxStack)
			{
				int n = ItemList[item->sid];
				ItemList[item->sid] = ++n;
			}
		}
	}

	for (std::map<int,int>::iterator it1 = ItemList.begin();it1!=ItemList.end();it1++ )
	{
		int cnt = it1->second;
		if (cnt>1)
		{
			BagOperator::pileList.push_back(it1->first);
		}
	}
	BagOperator::pile_it = BagOperator::pileList.begin();
}

void BagOperator::SortBag()
{
	int n=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	std::vector<UserItem*> ItemList;
	ItemList.clear();
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		int pos=it->first;
		if ((pos >= BagOperator::startpos && pos<BagOperator::endpos ))
		{
			UserItem* item=it->second;
			ItemList.push_back(item);
			n++;				
		}
	}

	std::sort(ItemList.begin(),ItemList.end(),BagSort);

	n=0;

	for (std::vector<UserItem*>::iterator it1 = ItemList.begin();it1!=ItemList.end();it1++ )
	{
		UserItem* item=(UserItem*)*it1;
		if ((BagOperator::startpos+n)!=item->position)
		{
			SendSortBagMsg(item->iid,BagOperator::startpos+n);
		}
		n++;
	}
}

void BagOperator::DoNextPile()
{
	if (BagOperator::pile_it!=BagOperator::pileList.end())
	{
		SendPileItemMsg();
	}
	else
	{
		ClearPileInfo();
		SortBag();
		setcanSort(true);
	}
}

void BagOperator::SendPileItemMsg()
{
	MsgItemOperationRequestPile* req=new MsgItemOperationRequestPile;
	req->sid=*BagOperator::pile_it;
	req->bagtype=BagOperator::bagtype;
	HandleMessage::sendMessage(req);
	BagOperator::pile_it++;
}

void BagOperator::SendSortBagMsg(int iid,int pos)
{
	MsgItemOperationRequestSetPosition* req1=new MsgItemOperationRequestSetPosition;
	req1->iid=iid;
	req1->position=pos;
	HandleMessage::sendMessage(req1);
}

void BagOperator::ClearPileInfo()
{
	 BagOperator::pileList.clear();
}

void BagOperator::setcanSort( bool flag )
{
	BagOperator::canSort = flag;
}

bool BagOperator::getcanSort()
{
	return BagOperator::canSort;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//typedef pair<int,int> PAIR;

std::vector<PAIR>::iterator BagOperator::repair_it;//<iid,money>

std::vector<PAIR>  BagOperator::repairList;


bool RepairMoneySort(PAIR v1, PAIR v2){	
	return v1.second < v2.second;	
}

void BagOperator::StartDoRepairItem()
{
	ClearRepairInfo();
	BagOperator::startpos = ItemPosition_Equip_Max;
	BagOperator::endpos = ItemPosition_Null;
	RepairItem();
	DoNextRepair();
}

void BagOperator::RepairItem()
{
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		int pos=it->first;
		if ((pos >= BagOperator::startpos && pos<BagOperator::endpos ))
		{
			UserItem* item=it->second;
			if (item->data[ItemEquip::Item_Durable]!=0)
			{
				int cnt = getRepairMoney(item->sid,item->data[ItemEquip::Item_Durable]);
				PAIR pair;
				pair.first = item->iid;
				pair.second = cnt;
				BagOperator::repairList.push_back(pair);
			}
		}
	}

	sort(BagOperator::repairList.begin(),BagOperator::repairList.end(),RepairMoneySort);
	BagOperator::repair_it = BagOperator::repairList.begin();
}

int BagOperator::getRepairMoney( int sid,int endure )
{
	int money = 0;
	Lua::instance()->push(sid);
	Lua::instance()->push(endure);
	if(Lua::instance()->call("itemdurablemoney",2,1) 
		&& Lua::instance()->pop(money))
	{
		CCLog("%d should cost %d money to repair",sid,money);
		return money;
	}
	CCLog("getRepairMoney  error!!");
	return money;
}

void BagOperator::DoNextRepair()
{
	if (BagOperator::repair_it!=BagOperator::repairList.end())
	{
		int iid = (*BagOperator::repair_it).first;
		SendRepairMsg(iid);
	}
	else
	{
		ClearRepairInfo();
	}
}

void BagOperator::SendRepairMsg( int iid )
{
	MsgItemOperationRequestRepair* msg = new MsgItemOperationRequestRepair;
	msg->iid = iid;
	HandleMessage::sendMessage(msg);
	BagOperator::repair_it++;
}

void BagOperator::ClearRepairInfo()
{
	BagOperator::repairList.clear();
}

void BagOperator::RepairAllFromServer(int type)
{
	MsgItemOperationRequestRepairAll* msg = new MsgItemOperationRequestRepairAll;
	msg->RepairType = type;//ItemRepair_Money;
	HandleMessage::sendMessage(msg);
}






