#include "ItemOperator.h"
#include "CCCommon.h"
#include "MsgItem.h"
#include "ErrorDefinition.h"
#include "EntityDefinition.h"

#include "scene/panel/FloatPanelType.h"

#include "userdata/GameData.h"
#include "userdata/HeroData.h"
#include "userdata/UserData.h"
#include "userdata/StaticData.h"
#include "userdata/UserItemData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/GameRole.h"

#include "event/CPEventHelper.h"
#include "logic/BagOperator.h"

#include "network/HandleMessage.h"


using namespace cocos2d;

static bool testLevel( int rebornLevel, int level )
{
	if (HeroData::getProp(Entity::attr_reborn) > rebornLevel)
	{
		return true;
	}
	else if (HeroData::getProp(Entity::attr_reborn) == rebornLevel &&
		HeroData::getLevel() >= level)
	{
		return true;
	}
	return false;
}

static bool testJob( int job )
{
	if (job == 0 ||
		HeroData::getJob() == job)
	{
		return true;
	}
	return false;
}

static bool testGender( int gender )
{
	if (gender == 0 ||
		HeroData::getGender() == gender)
	{
		return true;
	}
	return false;
}

/////////ItemOperator////////////////////////////////////////////////
void ItemOperator::useItem( int itemID )
{
	useItem(itemID, 0, 1);
}

void ItemOperator::useItem( int itemID, int entityID, int count )
{
	if (itemID > 0 &&
		count > 0)
	{
		MsgItemOperationRequestUse *msg = new MsgItemOperationRequestUse;
		msg->iid = itemID;
		msg->eid = entityID;
		msg->cnt = count;
		HandleMessage::sendMessage(msg);
	}
	else
	{
		CCLog(">>>Error: ItemOperator::useItem, itemID = %d, entityID = %d, count = %d", itemID, entityID, count);
	}
}

void ItemOperator::useItemBySID( int sid )
{
	useItemBySID(sid, 0, 1);
}


void ItemOperator::useItemBySID( int sid, int entityID, int count )
{
	UserItemData *userItems = GameData::s_user->getUserItemData();
	if (userItems)
	{
		const int iid = userItems->getItemBySid(sid);
		if (iid > 0)
		{
			int eid = GameData::s_user->getUserItemData()->getEquipPutOnPositionByiid(iid);
			ItemOperator::useItem(iid,eid,count);
		}
		else
		{
			CCLog(">>>Error: ItemOperator::useItemBySID, getItemBySid failed, sid = %d", sid);
		}
	}
	else
	{
		CCLog(">>>Error: ItemOperator::useItemBySID, getUserItemData failed!");
	}
}

bool ItemOperator::checkItemBetter( int iid )
{
	if (iid <= 0)
	{
		return false;
	}

	UserItemData *userItemData = GameData::s_user->getUserItemData();
	UserItem* pNewItem = userItemData->getItemByIid(iid);
	if (!pNewItem)
	{
		return false;
	}

	int requireReborn = 0, requireLevel = 0, requireJob = 0, requireGender = 0;
	StaticData::getItemRequireLevel(pNewItem->sid, requireReborn, requireLevel);
	StaticData::getItemRequireJob(pNewItem->sid, requireJob);
	StaticData::getItemRequireGender(pNewItem->sid, requireGender);
	if (testLevel(requireReborn, requireLevel) &&
		testJob(requireJob) &&
		testGender(requireGender))
	{
		int cnt = 0;
		int newcombatnum=userItemData->getCombatNumByIid(iid);
		for (int pos = ItemPosition_Equip_Shenqi6;pos<ItemPosition_Null;pos++)//神器6
		{
			UserItem* p = userItemData->getItemByPosition(pos);
			if (p)
			{
				if (p->type == pNewItem->type)
				{
					cnt++;
					int oldcombatnum=userItemData->getCombatNum(p);
					if (oldcombatnum<newcombatnum)
					{
						return true;
					}
				}
			}
		}
		if (cnt==0 || (cnt<2 && pNewItem->type == ItemType_Equip_Ring) || (cnt<2 && pNewItem->type == ItemType_Equip_Bangle))
		{
			return true;
		}
	}
	return false;
}

bool ItemOperator::testGoldEnough( int needGold )
{
	return testGoldEnough(needGold, false);
}

bool ItemOperator::testGoldEnough( int needGold, bool couponFirst )
{
	if (couponFirst)
	{
		if (HeroData::getProp(Entity::attr_diamond) < needGold)
		{
			if (HeroData::getProp(Entity::attr_gold) < needGold)
			{
				CPEventHelper::openPanel("FloatPanel", FloatPanelType::Gold_NotEnough, 0, 0, 0);
				return false;
			}
		}
	}
	else
	{
		if (HeroData::getProp(Entity::attr_gold) < needGold)
		{
			CPEventHelper::openPanel("FloatPanel", FloatPanelType::Gold_NotEnough, 0, 0, 0);
			return false;
		}
	}
	return true;
}

bool ItemOperator::testMoneyEnough( int needMoney )
{
	if (HeroData::getProp(Entity::attr_money) < needMoney)
	{
		CPEventHelper::uiNotify("ItemOperator", "", Error::NotEnoughMoney);
		return false;
	}
	return true;
}

bool ItemOperator::testHonorEnough( int needHonor )
{
	GameRole* myRole = GameData::getMyRole();
	if (!myRole)
	{
		return false;
	}
	if (myRole->Honour < needHonor)
	{
		CPEventHelper::uiNotify("ItemOperator", "", Error::NotEnoughHonor);
		return false;
	}
	return true;
}

int ItemOperator::getCurEquipEndure()
{
	float minEndurePer = 1;

	for (int i = ItemPosition_Equip_Neckless ; i> ItemPosition_Equip_Shenqi6 ; i--)//最大神器6
	{
		UserItem* pItem = GameData::s_user->getUserItemData()->getItemByPosition(i);
		if(pItem)
		{
			float allendure = 0;
			float nowendure = 0;

			LuaData::getProp(LuaData::ITEM,pItem->sid,"durable",allendure);
			nowendure = allendure-pItem->data[ItemEquip::Item_Durable];
			if(allendure==0)
			{
				continue;
			}
			float endureper = nowendure/allendure;
			if (minEndurePer == 1)
			{
				minEndurePer = endureper;
			}
			else if(minEndurePer > endureper)
			{
				minEndurePer = endureper;
			}
		}
	}

	return minEndurePer*100;
}

void ItemOperator::swapPositionBySid( int sid,int swappos )
{
	const int iid = GameData::s_user->getUserItemData()->getItemBySid(sid);
	if (iid > 0)
	{
		BagOperator::SendSortBagMsg(iid,swappos);
	}
}

int ItemOperator::getItemCombatNum( UserItem* userItem )
{
	if (!userItem)
		return 0;
	int CombatNum=0;
	int size;
	LuaData::getProp_size(LuaData::ITEM,userItem->sid,"attr",size);

	bool hasluck=false;
	//基础属性加成
	for (int i=1;i<=size;i++) 
	{
		int min,max,type;
		LuaData::getProp_ItemInfo(LuaData::ITEM,userItem->sid,"attr",i,"max","min","type",type,min,max);

		if(userItem->data[ItemEquip::Item_RebornLvl]!=0)
		{
			if (type==Combat::prop_Physical_Attack||type==Combat::prop_Magical_Attack||type==Combat::prop_Taoism_Attack||type==Combat::prop_Physical_Defense||type==Combat::prop_Magical_Defense)
			{
				min+=min/5*userItem->data[ItemEquip::Item_RebornLvl];
				max+=max/5*userItem->data[ItemEquip::Item_RebornLvl];
			}
		}

		// 修改：增加防御属性强化，防御是攻击的80%
		if (userItem->data[ItemEquip::Item_EnhanceLevel]!=0)
		{
			// 判断是否是可强化的属性
			if (type==Combat::prop_Physical_Attack||
				type==Combat::prop_Magical_Attack||
				type==Combat::prop_Taoism_Attack||
				type==Combat::prop_Physical_Defense||
				type==Combat::prop_Magical_Defense)
			{
				int value;
				LuaData::getProp("gdEquipEnhance",userItem->data[ItemEquip::Item_EnhanceLevel]-1,"enhanceValue",value);
				
				// 防御属性强化值是攻击的80%
				if (type==Combat::prop_Physical_Defense||type==Combat::prop_Magical_Defense) {
					value = value * 8 / 10;  // 80%
				}
				
				max+=value;  // 强化数值只加最大值
			}
		}
		
		if (type==1 || type==2)
		{
			min = min/100;
		}
		CombatNum+=ItemOperator::getCombatTypeNum(type,min);
		if (type==Combat::prop_Physical_Attack||type==Combat::prop_Magical_Attack||type==Combat::prop_Taoism_Attack||type==Combat::prop_Physical_Defense||type==Combat::prop_Magical_Defense)
		{
			CombatNum+=ItemOperator::getCombatTypeNum(type+1,max);
		}
		if (type==Combat::prop_Luck)
		{
			hasluck=true;
			CombatNum+=ItemOperator::getCombatTypeNum(type,userItem->data[ItemEquip::Item_Lucky]+min);
		}
	}
	if (!hasluck)
	{
		if (userItem->data[ItemEquip::Item_Lucky]!=0)
		{
			CombatNum+=ItemOperator::getCombatTypeNum(Combat::prop_Luck,userItem->data[ItemEquip::Item_Lucky]);
		}
	}

	//鉴定属性
	int reqlvl;
	LuaData::getProp(LuaData::ITEM,userItem->sid,"req_level",reqlvl);
	int combo=userItem->data[ItemEquip::Item_DataCombo];
	if (reqlvl>=20 && combo!=0)
	{
		int number=0;
		for (int b=0;b<3;b++)
		{
			int c=(int)((int)combo >> (8*b) & 255);
			if(c!=0)
			{
				number++;
			}
		}	
		int n=0;
		for (n;(int)((int)combo>>(n*8) & 255)!=0;n++)
		{
			int x=(int)((int)combo>>(n*8) & 255);
			float combovalue;
			if (x==11 || x==12 || x==13 || x==15 || x==17|| x==18)
			{
				combovalue=(float)userItem->data[ItemEquip::Item_DataX+n];
				combovalue=combovalue/100;
			}
			else
			{
				combovalue=userItem->data[ItemEquip::Item_DataX+n];
			}
			CombatNum+=ItemOperator::getCombatTypeNum(x,combovalue,2);
		}
	}

	// 极品属性
	int spAttrid=userItem->data[ItemEquip::Item_SpecialIdx];
	int spAttrdata=userItem->data[ItemEquip::Item_SpecialData];
	if (spAttrid!=0)
	{
		CombatNum+=ItemOperator::getCombatTypeNum(spAttrid,spAttrdata,2);
	}

	return CombatNum;
}

int ItemOperator::getCombatTypeNum( int type,int num ,int tag)
{
	int combatnum=0;
	if (tag==1)
	{
		switch (type)
		{
		case Combat::prop_HPMax	:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/440;
			}
			else if (HeroData::getJob() == UserData::CARRER_FS)
			{
				combatnum=num/110;
			}
			else if (HeroData::getJob() == UserData::CARRER_DS)
			{
				combatnum=num/175;
			}
			break;
		case Combat::prop_MPMax	:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/440;
			}
			else if (HeroData::getJob() == UserData::CARRER_FS)
			{
				combatnum=num/110;
			}
			else if (HeroData::getJob() == UserData::CARRER_DS)
			{
				combatnum=num/175;
			}
			break;
		case Combat::prop_HP	:
			break;
		case Combat::prop_MP	:
			break;
		case Combat::prop_Physical_Attack	:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case Combat::prop_PATK_Max	:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case Combat::prop_Magical_Attack	:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case Combat::prop_MATK_Max	:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case Combat::prop_Taoism_Attack	:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case Combat::prop_TATK_Max	:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case Combat::prop_PDEF_Min	:
			combatnum=num/2*1;
			break;
		case Combat::prop_PDEF_Max	:
			combatnum=num/2*1;
			break;
		case Combat::prop_MDEF_Min	:
			combatnum=num/2*1;
			break;
		case Combat::prop_MDEF_Max	:
			combatnum=num/2*1;
			break;
		case Combat::prop_Health_Recovery_Point	:
			combatnum=num/50/100*1;
			break;
		case Combat::prop_Magic_Recovery_Point	:
			combatnum=num/50/100*1;
			break;	
		case Combat::prop_Hit	:
			combatnum=num/1*10;
			break;	
		case Combat::prop_Dodge	:
			combatnum=num/1*20;
			break;	
		case Combat::prop_Magic_Hit	:
			combatnum=num/0.5/100*1;
			break;	
		case Combat::prop_Magic_Dodge	:
			combatnum=num/0.5/100*1;
			break;	
		case Combat::prop_Posion_Dodge	:
			break;	
		case Combat::prop_Posion_Recovery_Point	:
			combatnum=num/50/100*1;
			break;	
		case Combat::prop_Palsy	:
			combatnum=num/1*50;
			break;	
		case Combat::prop_Death_Recovery_Percent	:
			combatnum=num/1/100*7;
			break;	
		case Combat::prop_Luck	:
			combatnum=num/1*25;
			break;	
		case Combat::prop_Curse	:
			break;	
		case Combat::prop_Holy_Damage	:
			combatnum=num/25*1;
			break;	
		case Combat::prop_Damage_to_Magic	:
			combatnum=num/1/100*7;
			break;	

		case Combat::prop_HPMax + Combat::prop_End:
			combatnum=num/100*20 ;
			break;
		case Combat::prop_MPMax + Combat::prop_End:
			combatnum=num/100*20;
			break;
		case Combat::prop_Critical_Damage_Bonus	:
			combatnum=num/1 * 10; // 1点暴击 = 10战斗力
			break;
		case Combat::prop_Anti_Critical	:
			combatnum=num/1 * 10;// 1点防爆 = 10战斗力
			break;
		case Combat::prop_Damage_Reflect_Rate :
	        combatnum=num/1 * 10;// 1点反弹 = 10战斗力
	        break;
		case Combat::prop_Life_Steal_Rate :
	        combatnum=num/1 * 1;// 1点吸血 = 1战斗力
	        break;
		case Combat::prop_Mana_Steal_Rate :
	        combatnum=num/1 * 1;// 1点吸蓝 = 1战斗力
	        break;
		default:
			break;
		}
	}
	else if (tag==2)
	{
		switch (tag)
		{
		case 1:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case 2:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case 3:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*0.5;
			}
			else
			{
				combatnum=num/130*1;
			}
			break;
		case 4:
			if (HeroData::getJob()==UserData::CARRER_ZS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case 5:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case 6:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				combatnum=num/1*2;
			}
			else
			{
				combatnum=num/32.5*1;
			}
			break;
		case 7:
			combatnum=num/2*1;
			break;
		case 8:
			combatnum=num/2*1;
			break;
		case 9:
			combatnum=num/2*1;
			break;
		case 10:
			combatnum=num/2*1;
			break;
		case 11:
			combatnum=num/50*1;
			break;
		case 12:
			combatnum=num/50*1;
			break;
		case 13:
			combatnum=num/0.5*1;
			break;
		case 14:
			combatnum=num/25*1;
			break;
		case 15:
			combatnum=num/50*1;
			break;
		case 16:
			combatnum=num/1*10;
			break;
		case 17:
			combatnum=num/0.5*1;
			break;
		case 18:
			break;
		case 19:
			combatnum=num/1*20;
			break;
		default:
			break;
		}
	}
	return combatnum;
}
