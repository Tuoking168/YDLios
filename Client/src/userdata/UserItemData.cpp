#include "UserItemData.h"
#include "userdata/luadata/LuaData.h"
#include "CombatDefinition.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GameRole.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/UserPetData.h"
#include "logic/ItemOperator.h"
#include <algorithm>
#include "script/LuaWrapper.h"

bool CountSort(UserItem* v1, UserItem* v2){	
	return v1->count < v2->count;	
}

UserItemData::UserItemData()
:treasureDepotCapacity(0)
,treasureDepotCapacityMax(0)
{
}


UserItemData::~UserItemData()
{
	clear();
}

void UserItemData::addItem(UserItem* userItem)
{
	std::string icon = getItemIcon(userItem->sid);
	userItem->icon = icon;
	std::string name = getItemName(userItem->sid);
	userItem->name = name;
	std::string desc = getItemDesc(userItem->sid);
	userItem->desc = desc;
	int type = getItemType(userItem->sid);
	userItem->type = type;
	int cate = getItemCate(userItem->sid);
	userItem->category = cate;
	userItem->maxStack = getItemMaxStack(userItem->sid);
	userItem->bind = getItemBind(userItem->sid);;
	userItems[userItem->position] = userItem;
	userItemsByIid[userItem->iid] = userItem;
	for (int i=ItemEquip::Item_EnhanceLevel;i<ItemEquip::Item_Max;i++)
	{
		userItem->data[i]=0;
	}
	
	int rebornlvl = getItemRebornlvl(userItem->sid);
	userItem->data[ItemEquip::Item_RebornLvl]=rebornlvl;
	int profession = getItemClass(userItem->sid);
	userItem->profession=profession;
	userItem->pid = 0;
}

UserItem* UserItemData::getItemByPosition(short pos)
{
	std::map<short, UserItem*>::iterator it = userItems.find(pos);
	if(it == userItems.end())
	{
		return NULL;
	}
	return it->second;
}

UserItem* UserItemData::getItemByIid(int iid)
{
	std::map<int, UserItem*>::iterator it = userItemsByIid.find(iid);
	if(it == userItemsByIid.end())
	{
		return NULL;
	}
	return it->second;
}

bool UserItemData::changeItemPosition(int iid, short oldPos, short pos)
{
	// remove item
	std::map<int, UserItem*>::iterator it = userItemsByIid.find(iid);
	if(it == userItemsByIid.end())
	{
		return false;
	}
	UserItem* userItem = it->second;
	userItem->position = pos;

	std::map<short, UserItem*>::iterator it2 = userItems.find(oldPos);
	if(it2 == userItems.end())
	{
		return false;
	}
	UserItem* userItemOld = it2->second;
	if(userItemOld->iid == userItem->iid)
	{
		userItems.erase(it2);
	}

	// add item only position changed
	if(pos != 0) // remove directly
	{
		userItems[pos] = userItem;
	}else
	{
		// remove from userItemsByIid
		userItemsByIid.erase(it);
		userItem = NULL;
	}

	if (oldPos>=ItemPos::Treasure_Warehouse_Start&&oldPos<=ItemPos::Treasure_Warehouse_End)
	{
		if (!(pos>=ItemPos::Treasure_Warehouse_Start&&pos<=ItemPos::Treasure_Warehouse_End))
		{
			if (treasureDepotCapacity>0)
			{
				treasureDepotCapacity--;
			}
		}
	}
	return true;
}

std::string UserItemData::getItemIcon(int sid)
{
	std::string icon = "";
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "icon", icon);
	if(flag)
	{
		return icon;
	}
	return icon;
}

std::string UserItemData::getItemName(int sid)
{
	std::string name = "";
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "name", name);
	if(flag)
	{
		return name;
	}
	return name;
}

std::string UserItemData::getItemDesc(int sid)
{
	std::string desc = "";
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "desc", desc);
	if(flag)
	{
		return desc;
	}
	return desc;
}

int UserItemData::getItemCate( int sid )
{
	int cate;
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "cate", cate);
	if(flag)
	{
		return cate;
	}
	return cate;
}

int UserItemData::getItemType( int sid )
{
	int type;
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "type", type);
	if(flag)
	{
		return type;
	}
	return type;
}

int UserItemData::getItemBind( int sid )
{
	int bind;
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "bind_type", bind);
	if(flag)
	{
		return bind;
	}
	return bind;
}

int UserItemData::getEquipColor(int sid)
{
	int color = 1;
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "equip_color", color);
	if(flag)
	{
		return color;
	}
	return color;
}

int UserItemData::getEmptyPosition( int startIndex ,int n)
{
	int endIndex=0;
	if (startIndex==ItemPos::Player_Bag_Start)
	{
		endIndex=ItemPos::Player_Bag_End;
	}
	if (startIndex==ItemPos::Pet_Bag_Start)
	{
		endIndex=ItemPos::Pet_Bag_End;
	}
	if (startIndex==ItemPos::Treasure_Warehouse_Start)
	{
		endIndex=ItemPos::Treasure_Warehouse_End;
	}
	if (startIndex==ItemPos::Market_Bag_Start)
	{
		endIndex=ItemPos::Market_Bag_End;
	}
	if (startIndex==ItemPos::Trade_Bag_Start)
	{
		endIndex=ItemPos::Trade_Bag_End;
	}
	if (startIndex==ItemPos::NPC_Bag_Start)
	{
		endIndex=ItemPos::NPC_Bag_End;
	}
	int m=1;
	for (int i=startIndex;i<endIndex;i++)
	{
		std::map<short, UserItem*>::iterator it = userItems.find(i);
		if (it == userItems.end() )
		{
			if (m==n)
			{
				return i;
			}
			m++;
		}
	}
	return 0;

}

void UserItemData::clear()
{
	UserItems::iterator it = userItems.begin();
	UserItems::iterator itEnd = userItems.end();
	while (it != itEnd)
	{
		CC_SAFE_DELETE(it->second);
		it++;
	}
	userItems.clear();
	userItemsByIid.clear();
}

int UserItemData::getItemRebornlvl( int sid )
{
	int rebornlvl=0;
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "rebornlvl", rebornlvl);
	if(flag)
	{
		return rebornlvl;
	}
	return rebornlvl;
}

int UserItemData::getItemClass( int sid )
{
	int profession=0;
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "class", profession);
	if(flag)
	{
		return profession;
	}
	return profession;
}


int UserItemData::getItemBySid( int sid )
{
	bool flag_bind = false;
	std::vector<UserItem*> itemlist;
	std::map<short, UserItem*>::iterator it = userItems.begin();
	for(it;it!=userItems.end();it++)
	{
		if (it->first>=ItemPos::Player_Bag_Start && it->first<ItemPos::Player_Bag_End)
		{
			if (sid==it->second->sid)
			{
				if (it->second->data[ItemEquip::Item_Bind]==ItemEquip::Item_Has_bind)
				{
					flag_bind = true;
				}
				itemlist.push_back(it->second);
				//return it->second->iid;
			}
		}
	}

	if (itemlist.size()>0)
	{
		std::sort(itemlist.begin(),itemlist.end(),CountSort);		
		std::vector<UserItem*>::iterator itemlist_it = itemlist.begin();

		if (flag_bind)//存在绑定物品
		{
			for (itemlist_it;itemlist_it!=itemlist.end();itemlist_it++)
			{
				UserItem* pItem = *itemlist_it;
				if (pItem->data[ItemEquip::Item_Bind]==ItemEquip::Item_Has_bind)
				{
					return pItem->iid;
				}
			}
		}
		else
		{
			UserItem* pItem = *itemlist_it;
			return pItem->iid;
		}
	}
	
	return 0;
}


int UserItemData::getCombatNumByIid( int iid )
{
	UserItem* userItem=UserItemData::getItemByIid(iid);
	return ItemOperator::getItemCombatNum(userItem);
}

int UserItemData::getItemCntBySid( int sid,int startIndex,int endIndex )
{
	if (endIndex==0)
	{
		if (startIndex==ItemPos::Player_Bag_Start)
		{
			endIndex=ItemPos::Player_Bag_End;
		}
		if (startIndex==ItemPos::Pet_Bag_Start)
		{
			endIndex=ItemPos::Pet_Bag_End;
		}
		if (startIndex==ItemPos::Treasure_Warehouse_Start)
		{
			endIndex=ItemPos::Treasure_Warehouse_End;
		}
		if (startIndex==ItemPos::Market_Bag_Start)
		{
			endIndex=ItemPos::Market_Bag_End;
		}
		if (startIndex==ItemPos::Trade_Bag_Start)
		{
			endIndex=ItemPos::Trade_Bag_End;
		}
		if (startIndex==ItemPos::NPC_Bag_Start)
		{
			endIndex=ItemPos::NPC_Bag_End;
		}
		if (startIndex==0)
		{
			endIndex=ItemPos::BagSlotEnd;
		}
	}
	int count=0;
	for(std::map<short,UserItem*>::iterator it = userItems.begin(); it!=userItems.end(); it++)
	{
		if (it->first>=startIndex && it->first<endIndex)
		{
			UserItem* pItem=(UserItem*)it->second;
			if (pItem->sid==sid)
			{
				count+=pItem->count;
			}
		}
	}
	return count;
}

int UserItemData::getCombatNumBySid( int sid )
{
	UserItem* userItem=CommonFunction::createNewItem(sid);
	int combatNum = ItemOperator::getItemCombatNum(userItem);	
	delete userItem;
	return combatNum;
}

int UserItemData::getCombatNum( UserItem* userItem )
{
	if (userItem->iid==0)
	{
		return getCombatNumBySid(userItem->sid);
	}
	return getCombatNumByIid(userItem->iid);
}

int UserItemData::getEquipPutOnPositionByiid(int iid)
{
	return getEquipPutOnPosition(getItemByIid(iid));
}

int UserItemData::getEquipPutOnPosition( UserItem* userItem )
{
	if (userItem)
	{
		if (userItem->category==ItemCate_Equip)
		{
			if (userItem->type==ItemType_Equip_Ring)
			{
				int e1=0;
				int e2=0;
				//int self = getCombatNumByIid(userItem->iid);
				UserItem* pe1 = getItemByPosition(ItemPosition_Equip_Ring);
				if (pe1)
				{
					e1 = getCombatNumByIid(pe1->iid);
				}
				UserItem* pe2 = getItemByPosition(ItemPosition_Equip_Ring_Two);
				if (pe2)
				{
					e2 = getCombatNumByIid(pe2->iid);
				}
				if (e1<e2)
				{
					return ItemPosition_Equip_Ring;
				}
				else
				{
					return ItemPosition_Equip_Ring_Two;
				}
			}
			else if (userItem->type==ItemType_Equip_Bangle)
			{
				int e1=0;
				int e2=0;
				//int self = getCombatNumByIid(userItem->iid);
				UserItem* pe1 = getItemByPosition(ItemPosition_Equip_Bangle);
				if (pe1)
				{
					e1 = getCombatNumByIid(pe1->iid);
				}
				UserItem* pe2 = getItemByPosition(ItemPosition_Equip_Bangle_Two);
				if (pe2)
				{
					e2 = getCombatNumByIid(pe2->iid);
				}
				if (e1<e2)
				{
					return ItemPosition_Equip_Bangle;
				}
				else
				{
					return ItemPosition_Equip_Bangle_Two;
				}
			}
		}
	}
	return 1;
}

int UserItemData::getItemSoltCnt( int startIndex )
{
	int endIndex=0;
	if (startIndex==ItemPos::Player_Bag_Start)
	{
		endIndex=ItemPos::Player_Bag_End;
	}
	if (startIndex==ItemPos::Pet_Bag_Start)
	{
		endIndex=ItemPos::Pet_Bag_End;
	}
	if (startIndex==ItemPos::Treasure_Warehouse_Start)
	{
		endIndex=ItemPos::Treasure_Warehouse_End;
	}
	if (startIndex==ItemPos::Market_Bag_Start)
	{
		endIndex=ItemPos::Market_Bag_End;
	}
	if (startIndex==ItemPos::Trade_Bag_Start)
	{
		endIndex=ItemPos::Trade_Bag_End;
	}
	if (startIndex==ItemPos::NPC_Bag_Start)
	{
		endIndex=ItemPos::NPC_Bag_End;
	}
	if (startIndex==0)
	{
		endIndex=ItemPos::BagSlotEnd;
	}
	int count=0;
	for(std::map<short,UserItem*>::iterator it = userItems.begin(); it!=userItems.end(); it++)
	{
		if (it->first>=startIndex && it->first<endIndex)
		{
			count++;
		}
	}
	return count;
}

int UserItemData::getItemMaxStack( int sid )
{
	int max_stack ;
	bool flag = LuaData::getProp(LuaData::ITEM, sid, "max_stack", max_stack);
	if(flag)
	{
		return max_stack;
	}
	return 0;
}

int UserItemData::getItemSuitCnt( int suitid )
{
	int start = ItemPosition_Equip_Neckless;
	int end = ItemPosition_Equip_Max;
	int cnt = 0;
	for(std::map<short,UserItem*>::iterator it = userItems.begin(); it!=userItems.end(); it++)
	{
		if (it->first<=start && it->first>end)
		{
			int thissuitid = 0;
			LuaData::getProp(LuaData::ITEM,it->second->sid,"suite_id",thissuitid);
			if (thissuitid!=0 && thissuitid== suitid)
			{
				cnt++;
			}
			if (thissuitid == 999)
			{
				int thistype = 0;
				bool flag1 = false;
				bool flag2 = false;
				LuaData::getProp(LuaData::ITEM,it->second->sid,"type",thistype);
				Lua::instance()->push(suitid);
				Lua::instance()->push(thistype);
				if( Lua::instance()->call("checkBaiDa", 2, 1) 
					&& Lua::instance()->pop(flag1))
				{
					if(flag1)
					{
						cnt++;
					}
				}

			}
		}
	}
	return cnt;
}

void UserItemData::rmvItemByiid( int iid )
{	
	for(std::map<short,UserItem*>::iterator it = userItems.begin(); it!=userItems.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->iid==iid)
		{
			int petlink = pItem->data[ItemEquip::Item_Link_Pet];
			if (petlink!=0)
			{
				GameData::s_user->getUserPetData()->rmvPetEggByid(petlink);
			}
			userItems.erase(it);
			break;
		}
	}	

	std::map<int, UserItem*>::iterator it = userItemsByIid.find(iid);
	if(it != userItemsByIid.end())
	{
		UserItem* p = it->second;
		userItemsByIid.erase(it);
		delete p;
	}
}

