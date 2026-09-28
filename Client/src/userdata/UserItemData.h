#ifndef __USER_ITEM_DATA_H__
#define __USER_ITEM_DATA_H__

#include <string>
#include <vector>
#include <map>
#include "ItemDefinition.h"

// DataModel of User Items
struct UserItem
{
	UserItem()
		:iid(0)
		,sid(0)
		,category(0)
		,type(0)
		,bind(0)
		,count(0)
		,maxStack(0)
		,position(0)
		,propsCnt(0)
		,iconId(0)
		,profession(0)
		,pid(0)
	{
// 		for (int i = 0; i < ItemEquip::Item_Max; i++)
// 		{
// 			data[i] = 0;
// 		}
		icon.clear();
		name.clear();
		desc.clear();
	}

	int   iid;
	int   sid;
	int   category;
	int   type;
	int   colour;
	short bind;
	int count;
	short maxStack;
	short position;
	short propsCnt;
	// TODO: add props
	//int   data[ItemEquip::Item_Max];
	// 服务器数据有可能加属性，可能导致崩溃
	std::map<int, int> data;

	int iconId;
	int profession;
	int pid;
	std::string icon;
	std::string name;
	std::string desc;
};
typedef std::map<short,UserItem*> UserItems;
typedef std::map<int,UserItem*> UserItemsByIid;

class UserItemData
{
public:
	UserItemData();
	~UserItemData();
	void		addItem(UserItem* userItem);
	UserItem*	getItemByPosition(short pos);
	UserItem*	getItemByIid(int iid);
	int			getItemBySid(int sid);
	bool		changeItemPosition(int iid, short oldPos, short pos);
	std::string getItemIcon(int sid);
	std::string getItemName(int sid);
	std::string getItemDesc(int sid);
	int getItemCate(int sid);
	int getItemType(int sid);
	int getEquipColor(int sid);
	int getEmptyPosition(int startIndex,int n=1);
	int getItemBind(int sid);
	int getItemRebornlvl(int sid);
	int getItemClass(int sid);
	int getItemMaxStack(int sid);
	void clear();
	int getCombatNum(UserItem* userItem);
	int getCombatNumByIid(int iid);
	int getCombatNumBySid(int sid);
	int getItemCntBySid(int sid,int startIndex =0,int endIndex = 0);
	int getEquipPutOnPosition(UserItem* userItem);
	int getItemSoltCnt(int startIndex);
	int getItemSuitCnt(int suitid);
	int getEquipPutOnPositionByiid(int iid);
	void rmvItemByiid(int iid);
private:

public:
	UserItems	   userItems;
	UserItemsByIid userItemsByIid;

	int treasureDepotCapacity;
	int treasureDepotCapacityMax;
};

#endif