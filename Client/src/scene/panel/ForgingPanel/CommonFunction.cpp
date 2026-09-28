#include "userdata/SystemData.h"
#include "cocos2d.h"
#include "res/Path.h"
#include <fstream>
#include <sstream>
#include "userdata/GameData.h"
#include "CommonFunction.h"
#include "EvtDataDefinition.h"
#include "CCFileUtils.h"
#include "ext/CCMenuItemTextImage.h"
#include "curl.h"
#include "script/MainLua.h"
#include "userdata/luadata/LuaData.h"
#include "QuestDefinition.h"
#include "network/HandleMessage.h"
#include "userdata/UserData.h"
#include "MsgItem.h"
#include "MsgActivity.h"
#include "MsgPet.h"
#include "userdata/HeroData.h"
#include "userdata/UserItemData.h"
#include "EntityDefinition.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "userdata/ActivityData.h"
#include "userdata/activitydata/SpiderData.h"

#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/ForgingPanel/HWpanel.h"
#include "script/LuaWrapper.h"

#include "userdata/netdata/GameRole.h"
#include "ItemDefinition.h"
#include "ext/CCFlashAnimation.h"
#include "ext/CCActionDestroy.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"
#include "SceneDefinition.h"
#include "userdata/StaticData.h"
#include "event/CPEventHelper.h"
#include "scene/panel/EffectSprite.h"
#include "EffectDefinition.h"
#include "GeneralMenu.h"
#include "logic/ItemOperator.h"

using namespace cocos2d;


void CommonFunction::sendmsgSpider( int isdouble,int useVcoin/*=0*/ )
{
	MsgSpiderThorwItemRequest* req = new MsgSpiderThorwItemRequest;
//	std::vector<UserItem*>::iterator it=spiderdata::zmjz_list.begin();
	std::vector<int>::iterator it=spiderdata::vec_iid.begin();
// 	for (it;it!=spiderdata::zmjz_list.end();it++)
// 	{
// 		UserItem* p1=*it;
// 		req->itemlist.push_back(p1->iid);
// 	}
	for (it;it!=spiderdata::vec_iid.end();it++)
	{
		int p1=*it;
		req->itemlist.push_back(p1);
	}
	req->isdouble=isdouble;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}


void CommonFunction::sendmsgEnhance(int iid, int enhancetype, int isProtect, int useVcoin)
{	
	MsgItemOperationRequestEnhance* req = new MsgItemOperationRequestEnhance;
	req->iid=iid;
	req->enhancetype=enhancetype;
	req->isProtect=isProtect;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}


void CommonFunction::sendmsgFuMo(int iid, int IsUseGold)
{	
	MsgItemOperationRequestFuMoEx* req = new MsgItemOperationRequestFuMoEx;
	req->IID=iid;
	req->IsUseGold=IsUseGold;
	HandleMessage::sendMessage(req);
}


void CommonFunction::sendmsgFuMoEnhance(int iid, int IsUsePerfectFMF, int IsUseGold)
{	
	MsgItemOperationRequestFuMoEnhanceEx* req = new MsgItemOperationRequestFuMoEnhanceEx;
	req->IID=iid;
	req->IsUsePerfectFMF=IsUsePerfectFMF;
	req->IsUseGold=IsUseGold;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgQiling(int iid,int usevcoin)
{
	MsgItemOperationRequestQL* req = new MsgItemOperationRequestQL;
	req->iid = iid;
	req->usevcoin = usevcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgFootUp(int iid,int usevcoin)
{
	MsgItemOperationRequestFootUp* req = new MsgItemOperationRequestFootUp;
	req->iid = iid;
	req->usevcoin = usevcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgEvaluate(int iid, int useVcoin)
{	
	MsgItemOperationRequestEvaluate* req = new MsgItemOperationRequestEvaluate;
	req->iid=iid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgClearItem( int iid , int block1,int block2, int block3, int useVcoin)
{
	MsgItemOperationRequestClearItem* req = new MsgItemOperationRequestClearItem;
	req->iid=iid;
	req->block1=block1;
	req->block2=block2;
	req->block3=block3;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgMerge( int sid , int useVcoin)
{
	MsgItemOperationRequestMerge* req = new MsgItemOperationRequestMerge;
	req->sid=sid;
	req->usevcoin=useVcoin; 
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgUpgrade( int iid , int useVcoin)
{
	MsgItemOperationRequestUpgrade* req=new MsgItemOperationRequestUpgrade;
	req->iid=iid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgStoneTrans( int iid ,int tgtsid)
{
	MsgItemOperationRequestStoneTrans * req=new MsgItemOperationRequestStoneTrans;
	req->iid=iid;
	req->tgtsid=tgtsid;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgChangeMagicWeapon( int iid,int tgtiid )
{
	MsgItemOperationRequestChangeMagicWeaponEx * req=new MsgItemOperationRequestChangeMagicWeaponEx;
	req->iid=iid;
	req->tgtiid=tgtiid;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgChangeFoot( int iid,int tgtiid )
{
	MsgItemOperationRequestChangeFootEx * req = new MsgItemOperationRequestChangeFootEx;
	req->iid = iid;
	req->tgtiid = tgtiid;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgChangeSpecialAttr( int iid,int tgtiid, int useVcoin)
{
	MsgItemOperationRequestChangeSpecialAttrEx * req=new MsgItemOperationRequestChangeSpecialAttrEx;
	req->iid=iid;
	req->tgtiid=tgtiid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgReborn( int iid1,int iid2,int useVcoin/*=0*/ )
{
	MsgItemOperationRequestReborn * req=new MsgItemOperationRequestReborn;
	req->iidtgt=iid1;
	req->iidreq=iid2;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);

}

void CommonFunction::sendmsgChangeEnhance( int iid,int tgtiid, int useVcoin/*=0*/ )
{	
	MsgItemOperationRequestChangeEnhanceEx * req=new MsgItemOperationRequestChangeEnhanceEx;
	req->iid=iid;
	req->tgtiid=tgtiid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgChangeEvaluate( int iid,int tgtiid, int useVcoin/*=0*/ )
{
	MsgItemOperationRequestChangeEvaluateEx * req=new MsgItemOperationRequestChangeEvaluateEx;
	req->iid=iid;
	req->tgtiid=tgtiid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgClearSpecialAttr( int iid, int useVcoin/*=0*/ )
{
	MsgItemOperationRequestClearSpecialAttr * req=new MsgItemOperationRequestClearSpecialAttr;
	req->iid=iid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}


void CommonFunction::sendmsgPerfectEnhance( int iid ,int reqtype ,int useVcoin/*=0*/ )
{
	MsgItemOperationRequestPerfectEnhance * req=new MsgItemOperationRequestPerfectEnhance;
	req->iid=iid;
	req->reqtype=reqtype;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgPolish( int iid ,int useVcoin/*=0*/ )
{
	MsgItemOperationRequestPolish * req=new MsgItemOperationRequestPolish;
	req->iid=iid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgWingEnhance( int iid ,int useVcoin/*=0*/ )
{
	MsgItemOperationRequestWingEnhance * req=new MsgItemOperationRequestWingEnhance;
	req->iid=iid;
	req->usevcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgPetAdvance( int petiid , int block1,int block2, int block3 ,int useVcoin/*=0*/ )
{
	MsgImprovePetAdvanceRequest* req=new MsgImprovePetAdvanceRequest;
	req->petid=petiid;
	req->datax=block1;
	req->datay=block2;
	req->dataz=block3;
	req->isvcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

void CommonFunction::sendmsgPetSpeAttr( int petiid , int useVcoin/*=0*/ )
{
	MsgChangePetBestAttrRequest* req=new MsgChangePetBestAttrRequest;
	req->petid=petiid;
	req->isvcoin=useVcoin;
	HandleMessage::sendMessage(req);
}

//-------------------------------------------------------------------------------------------------------//


/// @brief 根据类型和背包类型获取物品列表
/// @param type 物品筛选类型
/// @param BagType 背包类型
/// @return 符合条件的物品列表
std::vector<UserItem*> CommonFunction::getBagItem(int type, int BagType)
{
	int startid = 0;
	int endid = 0;
	
	// 根据背包类型确定物品位置范围
	if (BagType == Role_Bag)        // 身上装备
	{
		startid = ItemPosition_stone_end;
		endid = ItemPosition_Null;
	}
	else if (BagType == Self_Bag)   // 自身背包
	{
		startid = ItemPos::Player_Bag_Start;
		endid = ItemPos::Player_Bag_End;
	}
	else if (BagType == Pet_Bag)    // 宠物背包
	{
		startid = ItemPos::Pet_Bag_Start;
		endid = ItemPos::Pet_Bag_End;
	}
	else if (BagType == Sell_Bag)   // 出售背包（使用玩家背包范围）
	{
		startid = ItemPos::Player_Bag_Start;
		endid = ItemPos::Player_Bag_End;
	}
	
	std::vector<UserItem*> equipItem;
	equipItem.clear();
	
	// 获取所有用户物品
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	
	// 遍历所有物品
	for(std::map<short, UserItem*>::iterator it = items.begin(); it != items.end(); it++)
	{
		UserItem* pItem = (UserItem*)it->second;
		
		// 检查物品是否在指定背包范围内
		if (pItem->position >= startid && pItem->position <= endid)
		{
			// 根据类型进行筛选
			if (type == Type_wing)  // 翅膀类型
			{
				if (pItem->category == ItemCate_Equip && pItem->type == ItemType_Equip_Wings)
				{
					equipItem.push_back(pItem);
				}
			}
			else if (type == Type_rubbish)  // 垃圾装备类型
			{
				if (BagType == Sell_Bag)
				{
					if (CheckRubishEquip(pItem->sid))  // 检查是否为垃圾装备
					{
						equipItem.push_back(pItem);
					}
				}
			}
			else if (type == Type_Chart)  // 图表类型
			{
				if (BagType == Role_Bag)  // 身上装备只显示装备类
				{
					if (pItem->category == ItemCate_Equip)
					{
						equipItem.push_back(pItem);
					}
				}
				else  // 其他背包显示所有物品
				{
					equipItem.push_back(pItem);
				}
			}
			else if (type == Type_Spider)  // 蜘蛛类型（特殊筛选）
			{
				if (pItem->category == ItemCate_Equip)
				{
					// 排除足迹、魔器、翅膀、时装、元神 神器 等特殊装备
					if (pItem->type != ItemType_Equip_Foot && 
						pItem->type != ItemType_Equip_Magic_Weapon && 
						pItem->type != ItemType_Equip_Wings && 
						pItem->type != ItemType_Equip_Fashion &&
						pItem->type != ItemType_Equip_Yuanshen &&
						pItem->type != ItemType_Equip_Shenqi1 &&
						pItem->type != ItemType_Equip_Shenqi2 &&
						pItem->type != ItemType_Equip_Shenqi3 &&
						pItem->type != ItemType_Equip_Shenqi4 &&
						pItem->type != ItemType_Equip_Shenqi5 &&
						pItem->type != ItemType_Equip_Shenqi6)
					{
						// 排除特定ID范围的装备
						if (pItem->sid >= 70169 && pItem->sid <= 70175)
						{
							continue;
						}
						
						int lvl = 0;
						LuaData::getProp(LuaData::ITEM, pItem->sid, "req_level", lvl);
						// 等级≥35且不在蜘蛛数据中的装备
						if (lvl >= 35 && (!spiderdata::hasItem(pItem)))
						{
							equipItem.push_back(pItem);
						}
					}
				}
			}
			else if (type == Type_Npcshop)  // NPC商店类型
			{
				int price = 0;
				LuaData::getProp("gdItems", pItem->sid, "price", price);
				// 有价格的物品可以出售
				if (price != 0)
				{
					equipItem.push_back(pItem);
				}
			}
			else if (type == Type_Setting)  // 设置类型（快捷使用）
			{
				// 药品类或快速设置类物品
				if (pItem->category == ItemCate_Medicine || 
					(pItem->category == ItemCate_Extension && pItem->type == ItemType_FastSettting))
				{
					equipItem.push_back(pItem);
				}
				else
				{
					// 通过Lua脚本检查是否可以快速使用
					int sid = pItem->sid;
					bool flag1 = false;
					Lua::instance()->push(sid);
					if (Lua::instance()->call("ItemCheckCanFastUse", 1, 1) && 
						Lua::instance()->pop(flag1))
					{
						if (flag1)
						{
							equipItem.push_back(pItem);
						}
					}
				}
			}
			else if (type == Type_Stone)  // 魂石类型
			{
				if (pItem->category == ItemCate_Stone)
				{
					equipItem.push_back(pItem);
				}
			}
			else if (type == TYPE_OTHER)  // 其他装备类型
			{
				if (pItem->category == ItemCate_Equip)
				{
					equipItem.push_back(pItem);
				}
			}
			else if (type == TYPE_JPQX)  // 极品属性类型
			{
				if (pItem->category == ItemCate_Equip && pItem->data[ItemEquip::Item_SpecialIdx] != 0)
				{
					equipItem.push_back(pItem);
				}
			}
			else if (type == TYPE_JDZY)  // 鉴定转移类型
			{
				if (pItem->category == ItemCate_Equip)
				{
					int lvl = 0;
					LuaData::getProp(LuaData::ITEM, pItem->sid, "req_level", lvl);
					// 等级≥20的装备
					if (lvl >= 20)
					{
							// 排除 元神 神器 等特殊装备
					if (
						pItem->type != ItemType_Equip_Yuanshen &&
						pItem->type != ItemType_Equip_Shenqi1 &&
						pItem->type != ItemType_Equip_Shenqi2 &&
						pItem->type != ItemType_Equip_Shenqi3 &&
						pItem->type != ItemType_Equip_Shenqi4 &&
						pItem->type != ItemType_Equip_Shenqi5 &&
						pItem->type != ItemType_Equip_Shenqi6)
					{
						
						equipItem.push_back(pItem);
					}
				}
			}
		}
			else if (type == TYPE_QHZY)  // 强化转移类型
			{
				if (pItem->category == ItemCate_Equip)
				{
					// 排除翅膀、魔器、材料、足迹、时装 元神 神器 等特殊装备
					if (pItem->type != ItemType_Equip_Wings && 
						pItem->type != ItemType_Equip_Magic_Weapon && 
						pItem->type != ItemType_Equip_Material && 
						pItem->type != ItemType_Equip_Foot && 
						pItem->type != ItemType_Equip_Fashion &&
						pItem->type != ItemType_Equip_Yuanshen &&
						pItem->type != ItemType_Equip_Shenqi1 &&
						pItem->type != ItemType_Equip_Shenqi2 &&
						pItem->type != ItemType_Equip_Shenqi3 &&
						pItem->type != ItemType_Equip_Shenqi4 &&
						pItem->type != ItemType_Equip_Shenqi5 &&
						pItem->type != ItemType_Equip_Shenqi6)
					{
					equipItem.push_back(pItem);
				}
			}
				}
			else if (type == TYPE_ZBFM)  // 装备附魔类型
			{
				if (pItem->category == ItemCate_Equip)
				{
					// 排除翅膀、魔器、材料、足迹、时装 元神 神器 等特殊装备
					if (pItem->type != ItemType_Equip_Wings && 
						pItem->type != ItemType_Equip_Magic_Weapon && 
						pItem->type != ItemType_Equip_Material && 
						pItem->type != ItemType_Equip_Foot && 
						pItem->type != ItemType_Equip_Fashion &&
						pItem->type != ItemType_Equip_Yuanshen &&
						pItem->type != ItemType_Equip_Shenqi1 &&
						pItem->type != ItemType_Equip_Shenqi2 &&
						pItem->type != ItemType_Equip_Shenqi3 &&
						pItem->type != ItemType_Equip_Shenqi4 &&
						pItem->type != ItemType_Equip_Shenqi5 &&
						pItem->type != ItemType_Equip_Shenqi6)
					{
						equipItem.push_back(pItem);
					}
				}
			}
			else if (type == TYPE_ZSDZ)  // 装备重生锻造类型
			{
				// 检查是否存在重生配置
				if (LuaData::checkIdExist("gdItemReBorn", pItem->sid))
				{
					equipItem.push_back(pItem);
				}
			}
			else if (type == TYPE_ZBQH)  // 装备强化类型
			{
				int lvl = 0;
				if (pItem->category == ItemCate_Equip)
				{
					LuaData::getProp(LuaData::ITEM, pItem->sid, "req_level", lvl);
					// 等级≥20且排除特殊装备
					if (lvl >= 20 && 
						pItem->type != ItemType_Equip_Wings && 
						pItem->type != ItemType_Equip_Magic_Weapon && 
						pItem->type != ItemType_Equip_Material && 
						pItem->type != ItemType_Equip_Foot && 
						pItem->type != ItemType_Equip_Fashion &&
						pItem->type != ItemType_Equip_Yuanshen &&
						pItem->type != ItemType_Equip_Shenqi1 &&
						pItem->type != ItemType_Equip_Shenqi2 &&
						pItem->type != ItemType_Equip_Shenqi3 &&
						pItem->type != ItemType_Equip_Shenqi4 &&
						pItem->type != ItemType_Equip_Shenqi5 &&
						pItem->type != ItemType_Equip_Shenqi6)
						
					{
						equipItem.push_back(pItem);
					}
				}
			}
			// 处理装备分解类型
			else if (type == TYPE_ZBJD)
			{
				int lvl = 0;
				if (pItem->category == ItemCate_Equip)
				{
					LuaData::getProp(LuaData::ITEM, pItem->sid, "req_level", lvl);
					// 等级≥20且排除各种特殊装备
					if (lvl >= 20 && 
						pItem->type != ItemType_Equip_Wings && 
						pItem->type != ItemType_Equip_Magic_Weapon && 
						pItem->type != ItemType_Equip_Material && 
						pItem->type != ItemType_Equip_Foot && 
						pItem->type != ItemType_Equip_Fashion && 
						pItem->type != ItemType_Equip_Yuanshen && 
						pItem->type != ItemType_Equip_Shenqi1 && 
						pItem->type != ItemType_Equip_Shenqi2 && 
						pItem->type != ItemType_Equip_Shenqi3 && 
						pItem->type != ItemType_Equip_Shenqi4 && 
						pItem->type != ItemType_Equip_Shenqi5 && 
						pItem->type != ItemType_Equip_Shenqi6)
					{
						equipItem.push_back(pItem);
					}
				}
			}
			// 处理装备升级类型
			else if (type == TYPE_ZBSJ)
			{
				int lvl = 0;
				if (pItem->category == ItemCate_Equip)
				{
					// 检查是否存在升级配置
					if (LuaData::checkIdExist("gdEquipUpgrade", pItem->sid))
					{
						equipItem.push_back(pItem);
					}
				}
			}
			// 处理魂武替换类型
			else if (type == TYPE_HWTH)
			{
				if (pItem->category == ItemCate_Equip && pItem->type == ItemType_Equip_Magic_Weapon)
				{
					equipItem.push_back(pItem);
				}
			}
			// 处理足迹替换类型
			else if (type == TYPE_ZJTH)
			{
				if (pItem->category == ItemCate_Equip && pItem->type == ItemType_Equip_Foot)
				{
					equipItem.push_back(pItem);
				}
			}
			// 处理极品转移类型
			else if (type == TYPE_JPZY)
			{
				if (pItem->category == ItemCate_Equip)
				{
					equipItem.push_back(pItem);
				}
			}
			// 处理合成类型
else if (type > TYPE_HC && type < TYPE_HCMAX)
{
    bool flag = false;
    // 特殊处理：类型8（魂石转换）
    if ((type - 100) == 8)
    {
        if (pItem->category == ItemCate_Stone || pItem->category == ItemCate_Equip)  // 增加装备转换
        {
            int n = 0;
            // 装备和魂石都使用同一个配置表
            LuaData::getProp("gdItemStoneTransform", pItem->sid, "reqGold", n);
            
            if (n != 0)
            {
                equipItem.push_back(pItem);
            }
        }
    }


				else
				{
					// 检查是否符合合成类型要求
					LuaData::getProp_mergefindsrc("gdsrcItemMergeType", type - 100, pItem->sid, flag);
					if (flag)
					{
						equipItem.push_back(pItem);
					}
				}
			}
			// 处理特殊属性类型
			else if (type >= Type_special && type < Type_enhance)
			{
				int passid = type - Type_special;
				if (pItem->category == ItemCate_Equip && pItem->type == passid)
				{
					// 有特殊属性的装备
					if (pItem->data[ItemEquip::Item_SpecialIdx] != 0 && 
						pItem->data[ItemEquip::Item_SpecialData] != 0)
					{
						equipItem.push_back(pItem);
					}
				}
			}
			// 处理强化类型
			else if (type >= Type_enhance && type < Type_wing)
			{
				int passid = type - Type_enhance;
				// 有强化等级的装备
				if (pItem->category == ItemCate_Equip && 
					pItem->data[ItemEquip::Item_EnhanceLevel] != 0 && 
					pItem->type == passid)
				{
					equipItem.push_back(pItem);
				}
			}
			// 处理装备评价类型
			else if (type >= Type_evaluate && type < Type_max)
			{
				int passid = type - Type_evaluate;
				// 有完整评价数据的装备
				if (pItem->category == ItemCate_Equip && 
					pItem->data[ItemEquip::Item_DataCombo] != 0 && 
					pItem->type == passid && 
					pItem->data[ItemEquip::Item_DataZ] != 0 && 
					pItem->data[ItemEquip::Item_DataY] != 0 && 
					pItem->data[ItemEquip::Item_DataX] != 0)
				{
					int lvl = 0;
					LuaData::getProp(LuaData::ITEM, pItem->sid, "req_level", lvl);
					// 等级≥20
					if (lvl >= 20)
					{
						equipItem.push_back(pItem);
					}
				}
			}
			// 默认情况：所有物品都加入
			else
			{
				equipItem.push_back(pItem);
			}
		}
	}
	return equipItem;
}

CCMenuItemImage* CommonFunction::getReqWingEnhanceItem1( UserItem* pUserItem )
{
	int reqid;
	int reqcnt;
	int enhancelvl=pUserItem->data[ItemEquip::Item_EnhanceLevel];
	LuaData::getProp("gdWingEnhance",enhancelvl,"firstItem",reqid);
	LuaData::getProp("gdWingEnhance",enhancelvl,"firstCnt",reqcnt);  
	if (reqid==0 || reqcnt==0)
	{
		return NULL;
	}
	UserItem* pItem=createNewItem(reqid);  
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqWingEnhanceItem2( UserItem* pUserItem )
{
	int reqid;
	int reqcnt;
	int enhancelvl=pUserItem->data[ItemEquip::Item_EnhanceLevel];
	LuaData::getProp("gdWingEnhance",enhancelvl,"secondItem",reqid);
	LuaData::getProp("gdWingEnhance",enhancelvl,"secondCnt",reqcnt);  
	if (reqid==0 || reqcnt==0)
	{
		return NULL;
	}
	UserItem* pItem=createNewItem(reqid);  
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqEnhanceItem( UserItem* pUserItem )
{
	int reqid;
	int reqcnt;
	int enhancelvl=pUserItem->data[ItemEquip::Item_EnhanceLevel];
	LuaData::getProp("gdEquipEnhance",enhancelvl,"reqItemId",reqid);
	LuaData::getProp("gdEquipEnhance",enhancelvl,"reqItemCnt",reqcnt);  

	UserItem* pItem=createNewItem(reqid);  

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	
	return reqItem;
}


CCMenuItemImage* CommonFunction::getReqFMCLItem( UserItem* pUserItem )
{
	int reqid=SystemData::getLayoutValue("fumojuan_id");
	int reqcnt=1;
	UserItem* pItem=createNewItem(reqid);
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqFMFItem( UserItem* pUserItem )
{
	int reqid = 0;
	int reqcnt = 0;
	LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "itemCfgID",reqid);
	LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "itemCount",reqcnt);

	UserItem* pItem=createNewItem(reqid);  

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqJPFMFItem( UserItem* pUserItem )
{
	int reqid = 0;
	int reqcnt = 0;
	LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "perfectItemCfgID",reqid);
	LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "perfectItemCount",reqcnt);


	UserItem* pItem=createNewItem(reqid);  

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

bool CommonFunction::IsEnoughReq( UserItem* pUserItem ,int tag , int data1)
{
	int reqid=0;
	int reqcnt=0;
	int d_value = 0;
	switch (tag)
	{
	case TAG_PerfectQH:
		if (data1==5)
		{
			reqid=40125;
		}
		else if (data1==8)
		{
			reqid=40126;
		}
		else if (data1==10)
		{
			reqid=40127;
		}
		reqcnt=1;
		break;
	case Type_Spider:
		reqid=SystemData::getLayoutValue("斑斓石");
		reqcnt=getCurSpiderReq();	
		if (spiderdata::m_bisdouble)
		{
			reqcnt=reqcnt;
		}
		else
		{
			reqcnt=0;
		}
		break;
	case TAG_ClearAttr:
		reqid=SystemData::getLayoutValue("极品属性清洗符");
		reqcnt=1;		
		break;
	case TAG_MoveOther:
		reqid=SystemData::getLayoutValue("转移神符");
		reqcnt=1;		
		break;
	case TAG_Reborn:
		LuaData::getProp("gdItemReBorn",pUserItem->sid,"reqid",reqid);
		LuaData::getProp("gdItemReBorn",pUserItem->sid,"reqcnt",reqcnt);
		if (LuaData::checkIdExist("gdSpecialRebornItem",pUserItem->sid))
		{
//			d_value = 2;
		}
		reqcnt=reqcnt*(pUserItem->data[ItemEquip::Item_RebornLvl]+1+d_value);
		break;
	case TAG_Upgrade:
		LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqItemId",reqid);
		LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqItemCnt",reqcnt);
		if (pUserItem->data[ItemEquip::Item_RebornLvl]!=0)
		{
			reqcnt=reqcnt*(pow(2,pUserItem->data[ItemEquip::Item_RebornLvl]));
		}
		/*if (pUserItem->sid==reqid)
		{
			reqcnt++;
		}*/
		break;
	case TAG_Wing:
		LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"firstItem",reqid);
		LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"firstCnt",reqcnt);
		break;
	case TAG_Ehance:
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqItemId",reqid);
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqItemCnt",reqcnt);
		break;
	case TAG_QiLing:
		LuaData::getProp("gdOpenMagicWeapon",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqId",reqid);
		LuaData::getProp("gdOpenMagicWeapon",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqCnt",reqcnt);
		break;
	case TAG_Evaluate:
		reqid=SystemData::getLayoutValue("鉴定图鉴");
		for (int b=0;b<3;b++)
		{
			int c=(int)((pUserItem->data[ItemEquip::Item_DataCombo] >> (8*b)) & 255);
			if(c!=0)
			{
				reqcnt++;
			}
		}
		if (reqcnt==3)
		{
			reqid=SystemData::getLayoutValue("清洗砂");
			reqcnt=1;
		}
		else
		{
			reqcnt++;
		}
		break;	
	case TAG_MoveAttr:
		reqid=SystemData::getLayoutValue("极品属性转移符");
		reqcnt=1;		
		break;
	default:
		break;
	}
	if (tag==TAG_Merge)
	{	
		for (int i=1;i<=5;i++)
		{
			LuaData::getProp_merge("gdItemMerge",pUserItem->sid,i,"id","cnt",reqcnt,reqid); 
			if (reqid!=0)
			{
				int count=0;
				UserItems items = GameData::s_user->getUserItemData()->userItems;
				for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
				{
					UserItem* pItem=(UserItem*)it->second;
					if (pItem->sid==reqid)
					{
						count+=pItem->count;
					}
				}
				if (count<reqcnt)
				{
					return false;
				}
			}			
		}		
	}
	else if (tag==TAG_Upgrade && pUserItem->data[ItemEquip::Item_RebornLvl]!=0)
	{
		int count=0;
		int reqsid=0;
		int reqcount=0;
		LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"rebornreq",reqsid);
		LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reborncnt",reqcount);
		reqcount=reqcount*2*pUserItem->data[ItemEquip::Item_RebornLvl];
		UserItems items = GameData::s_user->getUserItemData()->userItems;
		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (((UserItem*)(it->second))->sid==reqsid)
			{
				count+=((UserItem*)(it->second))->count;
			}
		}
		if (reqcount>count)
		{
			return false;
		}
	}
	else
	{
		int count=0;
		UserItems items = GameData::s_user->getUserItemData()->userItems;
		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			UserItem* pItem=(UserItem*)it->second;
			if (pItem->sid==reqid && pItem->position>0)
			{
				count+=pItem->count;
			}
		}
		if (count<reqcnt)
		{
			return false;
		}

		if (tag==TAG_Wing)
		{
			LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"secondItem",reqid);
			LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"secondCnt",reqcnt);
			for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
			{
				UserItem* pItem=(UserItem*)it->second;
				if (pItem->sid==reqid && pItem->position>0)
				{
					count+=pItem->count;
				}
			}
			if (count<reqcnt)
			{
				return false;
			}
		}
	}	
	return true;
}

/**
 * 检查用户是否有足够的货币（如金币）来执行特定操作
 * 
 * @param pUserItem 用户物品指针，包含物品相关信息
 * @param tag 操作类型标识，决定从哪个配置表读取所需货币数量
 * @return bool 是否有足够的货币执行操作
 */
bool CommonFunction::IsEnoughMoney(UserItem* pUserItem, int tag)
{
    int reqMoney;          // 所需货币数量
    int extra;             // 额外货币（用于重生计算）
    int count = HeroData::getProp(Entity::attr_money);  // 用户当前拥有的货币数量
    int d_value = 0;       // 重生特殊物品的附加值
    
    // 根据操作类型（tag）从不同配置表读取所需货币数量
    switch (tag)
    {
    case TAG_Wing:  // 翅膀强化
        LuaData::getProp("gdWingEnhance", pUserItem->data[ItemEquip::Item_EnhanceLevel], "reqGold", reqMoney);
        break;
        
    case TAG_Upgrade:  // 装备升级
        LuaData::getProp("gdEquipUpgrade", pUserItem->sid, "reqGold", reqMoney);
        break;
        
    case TAG_Ehance:  // 装备强化
        LuaData::getProp("gdEquipEnhance", pUserItem->data[ItemEquip::Item_EnhanceLevel], "reqGold", reqMoney);
        break;
        
    case TAG_QiLing:  // 器灵开启
        LuaData::getProp("gdOpenMagicWeapon", pUserItem->data[ItemEquip::Item_EnhanceLevel], "reqGold", reqMoney);
        break;
        
    case TAG_Evaluate:  // 装备鉴定
        LuaData::getProp("gdEquipEvaluate", 1, "reqGold", reqMoney);
        break;
        
    case TAG_StoneTrans:  // 宝石转换
        LuaData::getProp("gdItemStoneTransform", pUserItem->sid, "reqGold", reqMoney);
        break;
        
    case TAG_Merge:  // 物品合成
        LuaData::getProp("gdItemMerge", pUserItem->sid, "reqGold", reqMoney);
        break;
        
    case TAG_Reborn:  // 物品重生
        // 获取基础货币和额外货币
        LuaData::getProp("gdItemReBorn", pUserItem->sid, "reqmoney", reqMoney);
        LuaData::getProp("gdItemReBorn", pUserItem->sid, "reqExtramoney", extra);
        
        // 检查是否为特殊重生物品
        if (LuaData::checkIdExist("gdSpecialRebornItem", pUserItem->sid))
        {
            d_value = 2;  // 特殊物品增加2倍系数
        }
        
        // 重生花费公式：(基础花费 + 额外花费) × (重生等级 + 1 + 特殊附加值)
        reqMoney = (reqMoney + extra) * (pUserItem->data[ItemEquip::Item_RebornLvl] + 1 + d_value);
        break;
        
    default:  // 默认情况
        reqMoney = 0;
        break;
    }
    
    // 比较用户当前货币数量与所需货币数量
    if (count < reqMoney)
    {
        return false;  // 货币不足
    }
    
    return true;  // 货币足够
}


bool CommonFunction::IsEnoughOther( UserItem* pUserItem ,int tag )
{
	bool flag=false;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	int m;
	int count=0;
	switch (tag)
	{
	case TAG_Reborn:
		LuaData::getProp("gdItemReBorn",pUserItem->sid,"second",m);
		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (it->second->sid==m)
			{
				if(it->second->data[ItemEquip::Item_RebornLvl]==pUserItem->data[ItemEquip::Item_RebornLvl] && pUserItem->iid!=it->second->iid)
				{
					count+=it->second->count;
				}
			}
			else if(m==0)
			{
				flag=true;
			}
			if (count>0)
			{
				flag=true;
			}
		}
		break;
	case TAG_Upgrade:
		LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqEhLevel",m);
		if (m<=pUserItem->data[ItemEquip::Item_EnhanceLevel])
		{
			flag=true;
		}
		break;
	case TAG_Ehance:
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqProtect",m);
		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (((UserItem*)(it->second))->sid==40012)
			{
				count+=((UserItem*)(it->second))->count;
			}
		}
		if (m<=count)
		{
			flag=true;
		}
		break;
	default:
		flag=true;
		break;
	}
	return flag;
}


ItemTooltip* CommonFunction::getItemTips( UserItem* pUserItem ,int type)
{
	ItemTooltip* tooltip = ItemTooltip::create();
	tooltip->setTooltipContent(pUserItem, type);
	return tooltip;
}


ItemTooltip* CommonFunction::getPetBaseTips( UserPet* pPet,int type/*=0*/ )
{
	ItemTooltip* tooltip = ItemTooltip::create();
	tooltip->setToolTipPetBase(pPet, type);
	return tooltip;
}


CCMenuItemImage* CommonFunction::getReqEvaluateItem(UserItem* pUserItem)
{
	int reqid=SystemData::getLayoutValue("鉴定图鉴");
	int reqcnt=0;	
	for (int b=0;b<3;b++)
	{
		int c=(int)((pUserItem->data[ItemEquip::Item_DataCombo] >> (8*b)) & 255);
		if(c!=0)
		{
			reqcnt++;
		}
	}
	if (reqcnt==3)
	{
		reqid=SystemData::getLayoutValue("清洗砂");
		reqcnt=0;
	}

	UserItem* pItem=createNewItem(reqid);

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt+1);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<(reqcnt+1))
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqUpgradeItem( UserItem* pUserItem )
{
	int reqid;
	int reqcnt;
	LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqItemId",reqid);
	LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqItemCnt",reqcnt);

	UserItem* pItem=createNewItem(reqid);

	if (pUserItem->data[ItemEquip::Item_RebornLvl]!=0)
	{
		int sid = pUserItem->sid;
		bool flag1 =false;
		Lua::instance()->push(sid);		
		if(	Lua::instance()->call("ItemCheckSpecialUpgrade", 1, 1) && 
			Lua::instance()->pop(flag1))
		{
			if (!flag1)
			{
				reqcnt=reqcnt*(pow(2,pUserItem->data[ItemEquip::Item_RebornLvl]));
			}
		}
	}

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	if (pUserItem->sid==reqid && pUserItem->position>=ItemPos::Player_Bag_Start && pUserItem->position<ItemPos::Pet_Bag_End )
	{
		if (count!=0)
		{
			count--;
		}
	}
	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	return reqItem;
}

CCArray* CommonFunction::getReqMergeItem(UserItem* pUserItem)
{
	CCArray* pArray=CCArray::create();
	int reqid;
	int reqcnt;
	for (int i=1;i<=5;i++)
	{
		LuaData::getProp_merge("gdItemMerge",pUserItem->sid,i,"id","cnt",reqcnt,reqid); 
		if (reqid!=0)  
		{
			UserItem* pItem=createNewItem(reqid);
			/*	new UserItem;
			pItem->sid=reqid;			
			pItem->iid=0;
			LuaData::getProp(LuaData::ITEM,reqid,"name",pItem->name);
			LuaData::getProp(LuaData::ITEM,reqid,"icon",pItem->icon);*/

			CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

			int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

			CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
			CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
			if (count<reqcnt)
			{
				pLable->setColor(ccRED);
				reqItem->setColor(ccGRAY);
			}
			else
			{
				pLable->setColor(ccGREEN);
			}
			pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
			reqItem->addChild(pLable);

			

			pArray->addObject(reqItem);
		}		
	}
	
	return pArray;
}

CCArray* CommonFunction::getReqStoneItem( UserItem* pUserItem )
{
	CCArray* pArray=CCArray::create();
	int reqid = pUserItem->sid;
	int lvl = 0;
	LuaData::getProp("gdItems",reqid,"level",lvl);
	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Player_Bag_End);
	int cnt = 3;//默认3个框

	if (count>=3)
	{
		count=3;
	}
	if (lvl == 10 && count>=2)
	{
//		count = 2;
	}

	if (lvl == 10)//当魂石等级是10的时候2个框//策划重新要求消耗3个
	{
		cnt = 2;
	}
	
	for (int i=1;i<=3;i++)
	{			
		UserItem* pItem=createNewItem(pUserItem->sid);
		CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
		
		if (i>count)
		{
			reqItem->setColor(ccGRAY);
		}

		pArray->addObject(reqItem);			
	}

	return pArray;
}

CCMenuItemImage* CommonFunction::getReqPetAdvanceItem()
{
	int reqid = SystemData::getLayoutValue("宠物进阶符");
	int reqcnt = 1;

	UserItem* pItem=createNewItem(reqid);


	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);


	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqPetSpeItem()
{
	int reqid = SystemData::getLayoutValue("宠物极品符");
	int reqcnt = 1;

	UserItem* pItem = createNewItem(reqid);

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);


	CCString* pStr=CCString::createWithFormat("%d/%d",count,reqcnt);
	CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLabel->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLabel->setColor(ccGREEN);
	}
	pLabel->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLabel);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getTgtEnhanceItem( UserItem* pUserItem )
{
	UserItem* pItem=createNewItem(pUserItem->sid);	
	pItem->iid=pUserItem->iid;
	pItem->name=pUserItem->name;
	pItem->category=pUserItem->category;
	pItem->icon=pUserItem->icon;
	pItem->profession=pUserItem->profession;
	for (int idx=0;idx<ItemEquip::Item_Max;idx++)
	{
		if (idx==ItemEquip::Item_EnhanceLevel)
		{
			pItem->data[idx]=pUserItem->data[idx]+1;
		}
		else
		{
			pItem->data[idx]=pUserItem->data[idx];
		}		
	}
	CCMenuItemImage* EnhanceAft=CommonFunction::getItemIconButDelete(pItem,false);
	
	EnhanceAft->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(EnhanceAft->getContentSize().width/2,EnhanceAft->getContentSize().height/2));
	EnhanceAft->addChild(pEffect);
	
	return EnhanceAft;
}

CCMenuItemImage* CommonFunction::getTgtUpgradeItem( UserItem* pUserItem )
{
	int sidAft=0;
	LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"dstEquipId",sidAft);
	std::string iconAft;
	LuaData::getProp(LuaData::ITEM,sidAft,"icon",iconAft);
	UserItem* pItem=new UserItem;
	pItem->sid=sidAft;
	pItem->iid=pUserItem->iid;
	LuaData::getProp(LuaData::ITEM,sidAft,"name",pItem->name);
	pItem->category=pUserItem->category;
	pItem->icon=iconAft;
	pItem->profession=pUserItem->profession;
	for (int idx=0;idx<ItemEquip::Item_Max;idx++)
	{
		pItem->data[idx]=pUserItem->data[idx];
	}

	CCMenuItemImage* UpgradeAft=CommonFunction::getItemIconButDelete(pItem,false);
	
	UpgradeAft->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(UpgradeAft->getContentSize().width/2,UpgradeAft->getContentSize().height/2));
	UpgradeAft->addChild(pEffect);
	
	return UpgradeAft;
}


CCMenuItemImage* CommonFunction::getTgtWingEnhanceItem( UserItem* pUserItem )
{
	UserItem* pItem=createNewItem(pUserItem->sid);	
	pItem->iid=pUserItem->iid;
	pItem->name=pUserItem->name;
	pItem->category=pUserItem->category;
	pItem->icon=pUserItem->icon;
	pItem->profession=pUserItem->profession;
	for (int idx=0;idx<ItemEquip::Item_Max;idx++)
	{
		if (idx==ItemEquip::Item_EnhanceLevel)
		{
			pItem->data[idx]=pUserItem->data[idx]+1;
		}
		else
		{
			pItem->data[idx]=pUserItem->data[idx];
		}		
	}
	CCMenuItemImage* EnhanceAft=CommonFunction::getItemIconButDelete(pItem,false);

	EnhanceAft->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(EnhanceAft->getContentSize().width/2,EnhanceAft->getContentSize().height/2));
	EnhanceAft->addChild(pEffect);

	return EnhanceAft;
}


CCMenuItemImage* CommonFunction::getTgtMergeItem( UserItem* pUserItem )
{
	//加载最终合成物品
	UserItem* pItem=createNewItem(pUserItem->sid);
	pItem->iid=pUserItem->iid;
	pItem->name=pUserItem->name;
	pItem->category=pUserItem->category;
	pItem->icon=pUserItem->icon;
	pItem->profession=pUserItem->profession;
	CCMenuItemImage* MergeAft=CommonFunction::getItemIconButDelete(pItem,false);
	
	MergeAft->setPosition(SystemData::getLayoutPoint("WPHC_Center_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(MergeAft->getContentSize().width/2,MergeAft->getContentSize().height/2));
	MergeAft->addChild(pEffect);
	return MergeAft;
}

CCMenuItemImage* CommonFunction::getTgtStoneItem( UserItem* pUserItem )
{
	int sid=0;
	LuaData::getProp_mergefindtgt("gdtgtItemMergeType",7,"gdItemMerge",pUserItem->sid,sid);
	UserItem* pItem=createNewItem(sid);
	LuaData::getProp(LuaData::ITEM,pItem->sid,"name",pItem->name);
	LuaData::getProp(LuaData::ITEM,pItem->sid,"cate",pItem->category);
	LuaData::getProp(LuaData::ITEM,pItem->sid,"icon",pItem->icon);
	pItem->profession=pUserItem->profession;

	CCMenuItemImage* Stone=CommonFunction::getItemIconButDelete(pItem,false);
	
	Stone->setPosition(SystemData::getLayoutPoint("HSHC_HSHC_Center_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(Stone->getContentSize().width/2,Stone->getContentSize().height/2));
	Stone->addChild(pEffect);
	return Stone;
}


CCMenuItemImage* CommonFunction::getTgtSpecialAttrItem( UserItem* pUserItem1 , UserItem* pUserItem2)
{
	UserItem* pItem=new UserItem;
	pItem->sid=pUserItem1->sid;
	pItem->iid=pUserItem1->iid;
	pItem->name=pUserItem1->name;
	pItem->category=pUserItem1->category;
	pItem->icon=pUserItem1->icon;
	pItem->profession=pUserItem1->profession;
	for (int i=ItemEquip::Item_EnhanceLevel;i<ItemEquip::Item_Max;i++)
	{
		pItem->data[i]=pUserItem1->data[i];
	}
	pItem->data[ItemEquip::Item_SpecialIdx]=pUserItem2->data[ItemEquip::Item_SpecialIdx];
	pItem->data[ItemEquip::Item_SpecialData]=pUserItem2->data[ItemEquip::Item_SpecialData];

	CCMenuItemImage* SpecialAttr=CommonFunction::getItemIconButDelete(pItem,false);

	SpecialAttr->setPosition(SystemData::getLayoutPoint("JPZY_button3_pos"));


	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(SpecialAttr->getContentSize().width/2,SpecialAttr->getContentSize().height/2));
	SpecialAttr->addChild(pEffect);
	return SpecialAttr;
}


CCMenuItemImage* CommonFunction::getTgtEnhanceAttrItem( UserItem* pUserItem1 , UserItem* pUserItem2)
{
	UserItem* pItem=new UserItem;
	pItem->sid=pUserItem1->sid;
	pItem->iid=pUserItem1->iid;
	pItem->name=pUserItem1->name;
	pItem->category=pUserItem1->category;
	pItem->icon=pUserItem1->icon;
	pItem->profession=pUserItem1->profession;
	for (int i=ItemEquip::Item_EnhanceLevel;i<ItemEquip::Item_Max;i++)
	{
		pItem->data[i]=pUserItem1->data[i];
	}
	pItem->data[ItemEquip::Item_EnhanceLevel]=pUserItem2->data[ItemEquip::Item_EnhanceLevel];

	CCMenuItemImage* SpecialAttr=CommonFunction::getItemIconButDelete(pItem,false);

	SpecialAttr->setPosition(SystemData::getLayoutPoint("JPZY_button3_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(SpecialAttr->getContentSize().width/2,SpecialAttr->getContentSize().height/2));
	SpecialAttr->addChild(pEffect);
	return SpecialAttr;
}

CCMenuItemImage* CommonFunction::getTgtEvaluateAttrItem( UserItem* pUserItem1 , UserItem* pUserItem2 )
{
	UserItem* pItem=new UserItem;
	pItem->sid=pUserItem1->sid;
	pItem->iid=pUserItem1->iid;
	pItem->name=pUserItem1->name;
	pItem->category=pUserItem1->category;
	pItem->icon=pUserItem1->icon;
	pItem->profession=pUserItem1->profession;
	for (int i=ItemEquip::Item_EnhanceLevel;i<ItemEquip::Item_Max;i++)
	{
		pItem->data[i]=pUserItem1->data[i];
	}
	pItem->data[ItemEquip::Item_DataCombo]=pUserItem2->data[ItemEquip::Item_DataCombo];
	pItem->data[ItemEquip::Item_DataX]=pUserItem2->data[ItemEquip::Item_DataX];
	pItem->data[ItemEquip::Item_DataY]=pUserItem2->data[ItemEquip::Item_DataY];
	pItem->data[ItemEquip::Item_DataZ]=pUserItem2->data[ItemEquip::Item_DataZ];

	CCMenuItemImage* SpecialAttr=CommonFunction::getItemIconButDelete(pItem,false);

	SpecialAttr->setPosition(SystemData::getLayoutPoint("JPZY_button3_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(SpecialAttr->getContentSize().width/2,SpecialAttr->getContentSize().height/2));
	SpecialAttr->addChild(pEffect);
	return SpecialAttr;
}

CCMenuItemImage* CommonFunction::getTgtClearSpecialAttrItem( UserItem* pUserItem )
{
	UserItem* pItem=new UserItem;
	pItem->sid=pUserItem->sid;
	pItem->iid=pUserItem->iid;
	pItem->name=pUserItem->name;
	pItem->category=pUserItem->category;
	pItem->icon=pUserItem->icon;
	pItem->profession=pUserItem->profession;
	for (int i=ItemEquip::Item_EnhanceLevel;i<ItemEquip::Item_Max;i++)
	{
		pItem->data[i]=pUserItem->data[i];
	}
	pItem->data[ItemEquip::Item_SpecialIdx]=0;
	pItem->data[ItemEquip::Item_SpecialData]=0;

	CCMenuItemImage* SpecialAttr=CommonFunction::getItemIconButDelete(pItem,false);

	SpecialAttr->setPosition(SystemData::getLayoutPoint("JPQX_down_pos"));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(SpecialAttr->getContentSize().width/2,SpecialAttr->getContentSize().height/2));
	SpecialAttr->addChild(pEffect);
	return SpecialAttr;
}

CCMenuItemImage* CommonFunction::getItemIconInSkillLayer( UserItem* pUserItem )
{
	CCMenuItemImage* icon = CCMenuItemImage::create();
	icon->setNormalImage(LayoutData::getItemIcon(pUserItem->sid));
	icon->setSelectedImage(LayoutData::getItemIcon(pUserItem->sid));
	icon->setUserData(pUserItem);

// 	int itmecount=pUserItem->count;
// 	if (itmecount==0)
// 	{
// 		UserItems items = GameData::s_user->getUserItemData()->userItems;
// 		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
// 		{
// 			UserItem* pItem=(UserItem*)it->second;
// 			if (pItem->sid==pUserItem->sid)
// 			{
// 				itmecount+=pItem->count;
// 			}
// 		}
// 	}
	int itmecount = GameData::s_user->getUserItemData()->getItemCntBySid(pUserItem->sid,ItemPos::Player_Bag_Start,ItemPos::Player_Bag_End);
	CCLabelAtlas* countLabel=CCLabelAtlas::create(SystemData::intToString(itmecount).c_str(), SystemData::getLayoutString("ui_item_number").c_str(), 10, 11, '0');
	countLabel->setAnchorPoint(CCPointZero);
	countLabel->setTag(100);
	countLabel->setPosition(ccp(1,1));
	icon->addChild(countLabel);

	return icon;	
}


/// @brief 创建带有物品信息的图标菜单项
/// @param pUserItem 用户物品指针
/// @param flag 是否显示数量标志
/// @param isdelete 是否为可删除状态
/// @return 创建好的图标菜单项
CCMenuItemImageWithItem* CommonFunction::getItemIcon(UserItem* pUserItem, bool flag, bool isdelete)
{
	// 创建基础图标菜单项
	CCMenuItemImageWithItem* icon = CCMenuItemImageWithItem::create(pUserItem, isdelete);
	// 设置正常和选中状态的图标
	icon->setNormalImage(LayoutData::getItemIcon(pUserItem->sid));
	icon->setSelectedImage(LayoutData::getItemIcon(pUserItem->sid));
	icon->setUserData(pUserItem);
	
	// 添加物品数量显示（如果启用标志）
	if (flag)
	{
		int itmecount = pUserItem->count;
		// 如果当前物品数量为0，统计所有同类型物品的总数量
		if (itmecount == 0)
		{
			UserItems items = GameData::s_user->getUserItemData()->userItems;
			for(std::map<short,UserItem*>::iterator it = items.begin(); it != items.end(); it++)
			{
				UserItem* pItem = (UserItem*)it->second;
				if (pItem->sid == pUserItem->sid)  // 相同物品ID
				{
					itmecount += pItem->count;
				}
			}
		}
		
		// 数量大于1时显示数量标签
		if (itmecount > 1)
		{
			if (itmecount >= 1000000)  // 数量超过百万，以万为单位显示
			{
				itmecount = itmecount / 10000;  // 转换为万单位
				CCLabelAtlas* countLabel = CCLabelAtlas::create(SystemData::intToString(itmecount).c_str(), 
					SystemData::getLayoutString("ui_item_number").c_str(), 10, 11, '0');
				countLabel->setAnchorPoint(CCPointZero);
				countLabel->setPosition(ccp(0, 1));
				icon->addChild(countLabel);

				// 添加"W"（万）单位标识
				CCLabelTTF* p = CCLabelTTF::create("W", "", 18);
				p->setPosition(ccp(countLabel->getContentSize().width + 5, countLabel->getContentSize().height / 2));
				countLabel->addChild(p);
			}
			else  // 正常显示数量
			{
				CCLabelAtlas* countLabel = CCLabelAtlas::create(SystemData::intToString(itmecount).c_str(), 
					SystemData::getLayoutString("ui_item_number").c_str(), 10, 11, '0');
				countLabel->setAnchorPoint(CCPointZero);
				countLabel->setPosition(ccp(0, 1));
				icon->addChild(countLabel);
			}
		}
	}
	
	// 添加绑定标识（如果物品已绑定）
	if(pUserItem->data[ItemEquip::Item_Bind] == ItemEquip::Item_Has_bind)
	{
		CCSprite* plock = SystemData::getSpriteByPlist("ui_item_lock");
		plock->setScale(0.5f);
		plock->setPosition(ccp(5, 50));  // 右上角位置
		icon->addChild(plock);
	}
	
	// 添加装备品质特效
	int effectid = 0;
	// 根据装备品质设置不同的特效
	switch (GameData::getUserItemData()->getEquipColor(pUserItem->sid))
	{
	case ItemQuality_Null:    // 无品质
		effectid = 0;
		break;
	case ItemQuality_Green:   // 绿色品质
		effectid = Effect::effect_equipcolor1;
		break;
	case ItemQuality_Blue:    // 蓝色品质
		effectid = Effect::effect_equipcolor2;
		break;
	case ItemQuality_Magenta: // 紫色品质
		effectid = Effect::effect_equipcolor3;
		break;
	case ItemQuality_Yellow:  // 黄色品质
		effectid = Effect::effect_equipcolor4;
		break;
	case ItemQuality_Hose:  // 红色品质
		effectid = Effect::effect_equipcolor5;
		break;
	case ItemQuality_Tuo:  // 托品质
		effectid = Effect::effect_equipcolor6;
		break;
	case ItemQuality_King:  // king品质
		effectid = Effect::effect_equipcolor7;
		break;
	default:
		effectid = 0;
		break;
	}
	// 创建并添加品质特效
	EffectSprite* pEffect = EffectSprite::create(effectid);
	pEffect->setPosition(ccp(icon->getContentSize().width / 2, icon->getContentSize().height / 2));
	icon->addChild(pEffect);

	// 添加转生等级标识（钻石图标）
	int i = pUserItem->data[ItemEquip::Item_RebornLvl];  // 获取转生等级
	if(i >= 5)  //5 最高显示5个钻石
	{
		i = 5;
	}
	// 根据转生等级添加对应数量的钻石图标
	for (int n = 0; n < i; n++)
	{
		CCSprite* pDiamond = SystemData::getSpriteByPlist("Tips_diamond2");
		pDiamond->setAnchorPoint(CCPointZero);
		pDiamond->setPosition(ccp(icon->getContentSize().width / 80 + n * 12 - 3, icon->getContentSize().height / 10 - 10));
		icon->addChild(pDiamond);
	}
	
	return icon;
}

CCMenuItemImage* CommonFunction::getReqPerfectEhanceItem( UserItem* pUserItem )
{
	int reqcnt=1;
	int reqid = pUserItem->sid;
	CCMenuItemImage* reqItem=CommonFunction::getItemIcon(pUserItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}


CCArray* CommonFunction::getReqStoneTransItem( UserItem* pUserItem )
{
	CCArray* pArray=CCArray::create();
	if (!pUserItem)
		return pArray;
	
	// 检查是否是支持的类型
	if (pUserItem->category != ItemCate_Stone && pUserItem->category != ItemCate_Equip)//增加装备转换
		return pArray;
	
	// 魂石和装备都使用同一个配置表
	const char* configTable = "gdItemStoneTransform";
	
	// 检查配置是否存在
	if (!LuaData::checkIdExist(configTable, pUserItem->sid))
		return pArray;
	
	// 第一个转换目标
	int firstsid = 0;
	LuaData::getProp(configTable, pUserItem->sid, "firstItem", firstsid);
	if (firstsid > 0)
	{
		UserItem* pItem1 = CommonFunction::createNewItem(firstsid);
		CCMenuItemImage* icon1 = CommonFunction::getItemIconButDelete(pItem1, false);
		if (icon1)
		{
			pArray->addObject(icon1);
		}
	}
	
	// 第二个转换目标
	int secondsid = 0;
	LuaData::getProp(configTable, pUserItem->sid, "secondItem", secondsid);
	if (secondsid > 0)
	{
		UserItem* pItem2 = CommonFunction::createNewItem(secondsid);
		CCMenuItemImage* icon2 = CommonFunction::getItemIconButDelete(pItem2, false);
		if (icon2)
		{
			pArray->addObject(icon2);
		}
	}
	
	return pArray;
}

CCMenuItemImage* CommonFunction::getReqChangeAttrItem( UserItem* pUserItem )
{
	int reqid=SystemData::getLayoutValue("极品属性转移符");
	int reqcnt=1;
	UserItem* pItem=createNewItem(reqid);
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	return reqItem;
}


CCMenuItemImage* CommonFunction::getReqEnhanceAttrItem( UserItem* pUserItem )
{
	int reqid=SystemData::getLayoutValue("转移神符");
	int reqcnt=1;
	UserItem* pItem=createNewItem(reqid);
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	return reqItem;
}


CCMenuItemImage* CommonFunction::getReqEvaluateAttrItem( UserItem* pUserItem )
{
	int reqid=SystemData::getLayoutValue("转移神符");
	int reqcnt=1;
	UserItem* pItem=createNewItem(reqid);
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqClearSpecialAttrItem( UserItem* pUserItem )
{
	int reqid=SystemData::getLayoutValue("极品属性清洗符");
	int reqcnt=1;
	UserItem* pItem=createNewItem(reqid);
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);
	return reqItem;
}


CCMenuItemImage* CommonFunction::getReqRebornItem( UserItem* pUserItem )
{
	int reqid;
	int reqcnt;
	int d_value = 0;
	LuaData::getProp("gdItemReBorn",pUserItem->sid,"reqid",reqid);
	LuaData::getProp("gdItemReBorn",pUserItem->sid,"reqcnt",reqcnt);
	if (LuaData::checkIdExist("gdSpecialRebornItem",pUserItem->sid))
	{
//		d_value = 2;
	}
	reqcnt=reqcnt*(pUserItem->data[ItemEquip::Item_RebornLvl]+1+d_value);
	UserItem* pItem=createNewItem(reqid);
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);

	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqRebornItemSecond( UserItem* pUserItem )
{
	int reqid;
	int reqcnt=1;
	LuaData::getProp("gdItemReBorn",pUserItem->sid,"second",reqid);

	if (reqid==0)
	{
		return NULL;
	}

	UserItem* pItem=createNewItem(reqid);
	pItem->data[ItemEquip::Item_RebornLvl]=pUserItem->data[ItemEquip::Item_RebornLvl];
	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);
	int count=0;
	UserItem* pItem2=NULL;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (it->first>=ItemPos::Player_Bag_Start && it->first<ItemPos::Pet_Bag_End)
		{
			UserItem* pitem=(UserItem*)it->second;
			if (pitem->sid==reqid && pitem->data[ItemEquip::Item_RebornLvl]==pUserItem->data[ItemEquip::Item_RebornLvl] && pitem->iid!=pUserItem->iid && pitem->position>0)
			{
				count+=pitem->count;
				if (pItem2 && pItem2->data[ItemEquip::Item_EnhanceLevel]>pitem->data[ItemEquip::Item_EnhanceLevel])
				{
					pItem2=pitem;
				}
				if (pItem2==NULL)
				{
					pItem2=pitem;
				}
				break;
			}
		}
	}
	CCMenuItemImage* reqItem2=NULL;
	if (pItem2)
	{
		reqItem2=CommonFunction::getItemIcon(pItem2,false);
	}
	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
		reqItem->setColor(ccGRAY);
	}
	else
	{
		pLable->setColor(ccGREEN);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	if (reqItem2)
	{
		reqItem2->addChild(pLable);
		return reqItem2;
	}
	else
	{
		reqItem->addChild(pLable);
	}


	return reqItem;
}

CCMenuItemImage* CommonFunction::getTgtRebornItem( UserItem* pUserItem )
{
	UserItem* pItem=new UserItem;
	pItem->sid=pUserItem->sid;
	pItem->iid=pUserItem->iid;
	pItem->name=pUserItem->name;
	pItem->category=pUserItem->category;
	pItem->icon=pUserItem->icon;
	pItem->profession=pUserItem->profession;
	for (int i=ItemEquip::Item_EnhanceLevel;i<ItemEquip::Item_Max;i++)
	{
		pItem->data[i]=pUserItem->data[i];
	}
	pItem->data[ItemEquip::Item_SpecialIdx]=pUserItem->data[ItemEquip::Item_SpecialIdx];
	pItem->data[ItemEquip::Item_SpecialData]=pUserItem->data[ItemEquip::Item_SpecialData];

	pItem->data[ItemEquip::Item_RebornLvl]=pUserItem->data[ItemEquip::Item_RebornLvl]+1;

	CCMenuItemImage* Reborn=CommonFunction::getItemIconButDelete(pItem,false);
	Reborn->setPosition(ccp(SystemData::getLayoutPoint("ZSDZ_smallborder_pos").x,SystemData::getLayoutPoint("ZSDZ_smallborder_pos").y-20));

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(Reborn->getContentSize().width/2,Reborn->getContentSize().height/2));
	Reborn->addChild(pEffect);
	return Reborn;
}

/**
 * 创建新的用户物品对象
 * @param sid 物品静态ID（配置表ID）
 * @return 新创建的UserItem对象指针
 */
UserItem* CommonFunction::createNewItem(int sid)
{
	// 创建新的UserItem对象
	UserItem* pItem = new UserItem;
	
	// 设置物品基本属性
	pItem->sid = sid;        // 静态ID（配置ID）
	pItem->iid = 0;          // 实例ID（初始为0，可能需要服务器分配）
	pItem->profession = 0;   // 职业限制（初始为0，表示无限制）
	pItem->count = 0;        // 物品数量（初始为0）
	
	// 从Lua配置表中读取物品属性
	LuaData::getProp(LuaData::ITEM, sid, "name", pItem->name);        // 物品名称
	LuaData::getProp(LuaData::ITEM, sid, "icon", pItem->icon);        // 物品图标
	LuaData::getProp(LuaData::ITEM, sid, "type", pItem->type);        // 物品类型
	LuaData::getProp(LuaData::ITEM, sid, "cate", pItem->category);    // 物品分类
	LuaData::getProp(LuaData::ITEM, sid, "class", pItem->profession); // 职业要求
	
	// 初始化装备增强相关数据数组
	for (int a = ItemEquip::Item_EnhanceLevel; a != ItemEquip::Item_Max; a++)
	{
		pItem->data[a] = 0;  // 将所有增强属性初始化为0
	}
	
	// 从配置表读取转生等级要求
	LuaData::getProp(LuaData::ITEM, sid, "rebornlvl", pItem->data[ItemEquip::Item_RebornLvl]);
	
	return pItem;
}

int CommonFunction::CheckIsEnoughReqOrMoneyOrOther( 
    UserItem* pUserItem,  // 用户物品指针（可能为NULL）
    int tag,              // 操作类型标识符
    bool useVcoin,        // 是否使用元宝代替材料
    int data1,            // 扩展数据1
    int data2,            // 扩展数据2
    int data3)            // 扩展数据3
{
    // 1. 参数有效性检查：如果用户物品为空且不是蜘蛛类型操作，返回错误
	if (pUserItem == NULL && tag != Type_Spider)
	{
		return Error::NotEquip;
	}
    
    // 2. 如果没有勾选"元宝代替材料"选项
	if (!useVcoin)
	{
        // 2.1 检查需求物品是否足够
		if (!IsEnoughReq(pUserItem, tag, data1))
		{
			return Error::NotEnoughReq;
		}
        
        // 2.2 检查金币是否足够
		if (!IsEnoughMoney(pUserItem, tag))
		{
			return Error::NotEnoughMoney;
		}
        
        // 2.3 根据不同操作类型检查其他特殊条件
		if (tag == TAG_Ehance && data1 == 1)
		{
            // 强化操作（且data1为1时）检查其他条件
			if (!IsEnoughOther(pUserItem, tag))
			{
				return Error::NotEnoughReq;
			}
		}
		else if (tag == TAG_Upgrade)
		{
            // 升级操作检查其他条件
			if (!IsEnoughOther(pUserItem, tag))
			{
				return Error::Item_NotEnoughEhanceLevel;
			}
		}
		else if (tag == TAG_Reborn)
		{
            // 重生操作检查其他条件
			if (!IsEnoughOther(pUserItem, tag))
			{
				return Error::NotEnoughReq;
			}
		}
		else if (tag == TAG_QiLing)
		{
            // 器灵操作检查其他条件
			if (!IsEnoughOther(pUserItem, tag))
			{
				return Error::NotEnoughReq;
			}
		}
		else if (tag == TAG_FootShengjie)
		{
            // 脚部升阶操作检查其他条件
			if (!IsEnoughOther(pUserItem, tag))
			{
				return Error::NotEnoughReq;
			}
		}
	}
	else  // 3. 如果勾选了"元宝代替材料"选项
	{
        // 3.1 检查元宝是否足够（可能用元宝代替部分材料）
		int rvt = IsEnoughVcoin(pUserItem, tag, data1);
		if (rvt != Error::Success)
		{
			return rvt;  // 返回具体的错误码
		}
        
        // 3.2 检查金币是否足够
		if (!IsEnoughMoney(pUserItem, tag))
		{
			return Error::NotEnoughMoney;
		}
        
        // 3.3 重生操作需要额外检查其他条件（即使使用元宝）
		if (tag == TAG_Reborn)
		{
			if (!IsEnoughOther(pUserItem, tag))
			{
				return Error::NotEnoughReq;
			}
		}
	}
    
    // 4. 所有检查通过，返回成功
	return Error::Success;
}

int CommonFunction::IsEnoughVcoin( UserItem* pUserItem ,int tag ,int data1)
{
	int count=getReqVcoin(pUserItem,tag,data1);
	if (count==-1)
	{
		return Error::CanNotReplace;
	}
	if (count>HeroData::getProp(Entity::attr_gold))
	{
		//打开充值界面 
		Game::getGameUI()->showFloatPanel(FloatPanelType::Gold_NotEnough);
		CPEventHelper::uiNotify("","",Error::NotEnoughGold);

		return Error::NotEnoughGold;
	}
	return Error::Success;
}

int CommonFunction::getReqVcoin( UserItem* pUserItem ,int tag,int data1 )
{
	int count=0;
	int reqid=0;
	int reqcnt=0;
	int d_value = 0;
	bool flag1 =false;
	switch (tag)
	{
	case Type_PetAdvance:
		reqid  = SystemData::getLayoutValue("宠物进阶符");
		reqcnt = 1;
		break;
	case Type_PetSpec:
		reqid = SystemData::getLayoutValue("宠物极品符");
		reqcnt = 1;
		break;
	case TAG_PerfectQH:
		if (data1==5)
		{
			reqid=SystemData::getLayoutValue("5级完美强化符");;
		}
		else if (data1==8)
		{
			reqid=SystemData::getLayoutValue("8级完美强化符");;
		}
		else if (data1==10)
		{
			reqid=SystemData::getLayoutValue("10级完美强化符");;
		}
		reqcnt=1;
		break;
	case Type_Spider:
		reqid=SystemData::getLayoutValue("斑斓石");
		reqcnt=getCurSpiderReq();	
		if (spiderdata::m_bisdouble)
		{
			reqcnt=reqcnt;
		}
		break;
	case TAG_ClearAttr:
		reqid=SystemData::getLayoutValue("极品属性清洗符");
		reqcnt=1;		
		break;
	case TAG_ZHUANGBEIFUMO:
		LuaData::getProp("gdFuMo", "itemCfgID",reqid);
		LuaData::getProp("gdFuMo", "itemCount",reqcnt);
		break;
	case TAG_FUMOQIANGHUA:
		LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "itemCfgID",reqid);
		LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "itemCount",reqcnt);
		break;
	case TAG_MoveOther:
		reqid=SystemData::getLayoutValue("转移神符");
		reqcnt=1;		
		break;
	case TAG_Reborn:
		if (pUserItem==NULL)
		{
			return 0;
		}
		LuaData::getProp("gdItemReBorn",pUserItem->sid,"reqid",reqid);
		LuaData::getProp("gdItemReBorn",pUserItem->sid,"reqcnt",reqcnt);
		if (LuaData::checkIdExist("gdSpecialRebornItem",pUserItem->sid))
		{
//			d_value = 2;
		}
		reqcnt=reqcnt*(pUserItem->data[ItemEquip::Item_RebornLvl]+1+d_value);
		break;
	case TAG_Upgrade:
		if (pUserItem==NULL)
		{
			return 0;
		}
		LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqItemId",reqid);
		LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reqItemCnt",reqcnt);
		if (pUserItem->data[ItemEquip::Item_RebornLvl]!=0)
		{
			Lua::instance()->push(pUserItem->sid);		
			if(	Lua::instance()->call("ItemCheckSpecialUpgrade", 1, 1) && 
				Lua::instance()->pop(flag1))
			{
				if (!flag1)
				{
					reqcnt=reqcnt*(pow(2,pUserItem->data[ItemEquip::Item_RebornLvl]));
				}
			}
		}
		break;
	case TAG_Wing:
		if (pUserItem==NULL)
		{
			return 0;
		}
		LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"firstItem",reqid);
		LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"firstCnt",reqcnt);
		break;
	case TAG_Ehance:
		if (pUserItem==NULL)
		{
			return 0;
		}
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqItemId",reqid);
		LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqItemCnt",reqcnt);
		break;
	case TAG_QiLing:
		if (pUserItem==NULL)
		{
			return 0;
		}
		LuaData::getProp("gdOpenMagicWeapon",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqId",reqid);
		LuaData::getProp("gdOpenMagicWeapon",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqCnt",reqcnt);
		break;
	case TAG_FootShengjie:
		if (pUserItem==NULL)
		{
			return 0;
		}
		LuaData::getProp("gdFootUp",pUserItem->sid,"reqId",reqid);
		LuaData::getProp("gdFootUp",pUserItem->sid,"reqCnt",reqcnt);
		break;
	case TAG_Evaluate:
		if (pUserItem==NULL)
		{
			return 0;
		}
		reqid=SystemData::getLayoutValue("鉴定图鉴");
		for (int b=0;b<3;b++)
		{

			int a = pUserItem->data[ItemEquip::Item_DataCombo];
			int c=(int)((a >> (8*b)) & 255);
			if(c!=0)
			{
				reqcnt++;
			}
		}
		if (reqcnt==3)
		{
			reqid=SystemData::getLayoutValue("清洗砂");
			reqcnt=1;
		}
		else
		{
			reqcnt++;
		}
		break;	
	case TAG_MoveAttr:
		reqid=SystemData::getLayoutValue("极品属性转移符");
		reqcnt=1;		
		break;
	default:
		break;
	}
	if (tag==TAG_Merge)                                   //这个标签是////
	{	
		if (pUserItem==NULL)
		{
			return 0;
		}
		int allprice=0;
		for (int i=1;i<=5;i++)
		{
			count=0;
			LuaData::getProp_merge("gdItemMerge",pUserItem->sid,i,"id","cnt",reqcnt,reqid);
			if (reqid!=0)
			{
				count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
				if (count<reqcnt)
				{
					int cntEx=reqcnt-count;
					int shopprice=0;
					LuaData::getProp("gdItems",reqid,"shopprice",shopprice);
					if (shopprice==0)
					{
						return -1;
					}
					allprice+=cntEx*shopprice;
				}
			}			
		}	
		return allprice;	
	}
	else
	{
		int count = GameData::s_user->getUserItemData()->getItemCntBySid(reqid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
		int vcoinEx=0;
		int cntEx=reqcnt-count;
		int shopprice=0;
		LuaData::getProp("gdItems",reqid,"shopprice",shopprice);
		if (count<reqcnt)
		{ 
			if (shopprice==0)
			{
				return -1;
			}
			if (tag==TAG_Ehance && data1==1)
			{
				if (pUserItem==NULL)
				{
					return 0;
				}
				int m=0;
				LuaData::getProp("gdEquipEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"reqProtect",m);
				count = GameData::s_user->getUserItemData()->getItemCntBySid(40012,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
				if (m>count)
				{
					int shopprice_=0;
					int reqcnt_=m-count;
					LuaData::getProp("gdItems",40012,"shopprice",shopprice_); 
					if (shopprice_==0)
					{
						return -1;
					}
					vcoinEx=shopprice_*reqcnt_;
				}
			}
			else if (tag==TAG_FUMOQIANGHUA && data1==1)
			{
				// 附魔强化
				if (pUserItem==NULL)
				{
					return 0;
				}

				int jpfmfreqid=SystemData::getLayoutValue("fumoqianghuafu_id");
				int jpfmfcount = 0;
				LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "perfectItemCfgID",jpfmfreqid);
				LuaData::getProp("gdFuMoEnhance", pUserItem->data[ItemEquip::Item_FuMoEnhanceCount] + 1, "perfectItemCount",jpfmfcount);
				count = GameData::s_user->getUserItemData()->getItemCntBySid(jpfmfreqid, ItemPos::Player_Bag_Start, ItemPos::Pet_Bag_End);
				if (jpfmfcount > count)
				{
					int shopprice_=0;
					int reqcnt_=jpfmfcount-count;
					LuaData::getProp("gdItems",jpfmfreqid,"shopprice",shopprice_); 
					if (shopprice_==0)
					{
						return -1;
					}
					vcoinEx=shopprice_*reqcnt_;
				}
			}
			else if (tag==TAG_Upgrade && pUserItem->data[ItemEquip::Item_RebornLvl]!=0)
			{
				if (pUserItem==NULL)
				{
					return 0;
				}
				int reqsid=0;
				int reqcount=0;
				int reborncnt = 0;
				LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"rebornreq",reqsid);
				LuaData::getProp("gdEquipUpgrade",pUserItem->sid,"reborncnt",reborncnt);
				reqcount=reborncnt*2*pUserItem->data[ItemEquip::Item_RebornLvl];

				count = GameData::s_user->getUserItemData()->getItemCntBySid(reqsid,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
				if (reqcount>count)
				{
					int shopprice_=0;
					int reqcnt_=reqcount-count;
					LuaData::getProp("gdItems",reqsid,"shopprice",shopprice_); 
					if (shopprice_==0)
					{
						return -1;
					}
					vcoinEx=shopprice_*reqcnt_;
				}
			}
			else if (tag==TAG_Evaluate && reqid==SystemData::getLayoutValue("清洗砂") && data1!=0)
			{
//				int reqid_=SystemData::getLayoutValue("鉴定锁");
//				int reqcnt_=data1;
//				int shopprice_=0;
//				LuaData::getProp("gdItems",reqid_,"shopprice",shopprice_); 
//				if (shopprice_==0)
//				{
//					return -1;
//				}
//				vcoinEx=shopprice_*reqcnt_;
			}
			else if (tag==TAG_Wing)
			{
				int reqid_=0;
				int reqcnt_=0;
				LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"secondItem",reqid_);
				LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"secondCnt",reqcnt_);
				if (reqcnt_!=0 && reqid_!=0)
				{
					int secondcount=0;

					secondcount = GameData::s_user->getUserItemData()->getItemCntBySid(reqid_,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
					if (secondcount<reqcnt_)
					{
						int shopprice_=0;
						reqcnt_=reqcnt_-secondcount;
						LuaData::getProp("gdItems",reqid_,"shopprice",shopprice_); 
						if (shopprice_==0)
						{
							return -1;
						}
						vcoinEx=shopprice_*reqcnt_;
					}
				}
			}
			return (cntEx*shopprice+vcoinEx);
		}
		else
		{
			if (tag==TAG_Wing)
			{
				int reqid_=0;
				int reqcnt_=0;
				LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"secondItem",reqid_);
				LuaData::getProp("gdWingEnhance",pUserItem->data[ItemEquip::Item_EnhanceLevel],"secondCnt",reqcnt_);
				if (reqcnt_!=0 && reqid_!=0)
				{
					int secondcount=0;

					secondcount = GameData::s_user->getUserItemData()->getItemCntBySid(reqid_,ItemPos::Player_Bag_Start,ItemPos::Pet_Bag_End);
					if (secondcount<reqcnt_)
					{
						int shopprice_=0;
						reqcnt_=reqcnt_-secondcount;
						LuaData::getProp("gdItems",reqid_,"shopprice",shopprice_); 
						if (shopprice_==0)
						{
							return -1;
						}
						vcoinEx=shopprice_*reqcnt_;
					}
				}
				return (cntEx*shopprice+vcoinEx);
			}
		}
	}	
	return 0;
}

int CommonFunction::getCurSpiderReq()
{
	int i=0;
	std::vector<UserItem*>::iterator it=spiderdata::zmjz_list.begin();
	for (it;it!=spiderdata::zmjz_list.end();it++)
	{
		UserItem* p1=*it;
		int lvl=0;
		LuaData::getProp(LuaData::ITEM,p1->sid,"req_level",lvl);
		if (lvl>=35)
		{
			int cnt=0;
			LuaData::getProp_Spider(p1->sid,cnt);
			i+=cnt;
		}
	}
	return i; 
}

CCMenuItemImage* CommonFunction::getTgtPerfectEnhanceItem( UserItem* pUserItem, int type )
{
	int enhancelvl=type;

	UserItem* pItem=new UserItem;
	pItem->sid=pUserItem->sid;
	pItem->iid=pUserItem->iid;
	pItem->name=pUserItem->name;
	pItem->category=pUserItem->category;
	pItem->icon=pUserItem->icon;
	pItem->profession=pUserItem->profession;
	for (int idx=0;idx<ItemEquip::Item_Max;idx++)
	{
		if (idx==ItemEquip::Item_EnhanceLevel && pUserItem->data[ItemEquip::Item_EnhanceLevel]<enhancelvl)
		{
			pItem->data[idx]=enhancelvl;
		}
		else
		{
			pItem->data[idx]=pUserItem->data[idx];
		}		
	}
	CCMenuItemImage* EnhanceAft=CommonFunction::getItemIconButDelete(pItem,false);

	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(EnhanceAft->getContentSize().width/2,EnhanceAft->getContentSize().height/2));
	EnhanceAft->addChild(pEffect);
	//EnhanceAft->setPosition(SystemData::getLayoutPoint("ZBSJ_button4_pos"));

	return EnhanceAft;
}

int CommonFunction::checkShoesCount(int sid,int reason)
{
	//判断该场景是否能传送
	int mapType=0;
	if (StaticData::getMapType(GameData::s_user->mMap.mID,mapType))
	{
		if (mapType!=Scene::stSceneNormal)
		{
			CPEventHelper::uiNotify("","",Error::FlyBootisDisable);
			return Error::FlyBootisDisable;
		}
	}

	// vip free count
	const int vipLevel = HeroData::getProp(Entity::attr_vip_level);
	if (vipLevel > 0)
	{
		const int totalCount = ActivityData::getExDataY(EvtData::evt_freeshoes);
		// free count unlimited
		if (totalCount < 0)
		{
			return Error::Success;
		}

		const int usedCount = ActivityData::getExDataX(EvtData::evt_freeshoes);
		if (usedCount < totalCount)
		{
			return Error::Success;
		}
	}

	const int shoessid=SystemData::getLayoutValue("飞鞋");
	int count=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==shoessid)
		{
			count+=pItem->count;
		}
	}
	if (count==0)
	{
		if (GameData::s_user->m_pMainRole->m_bBuyShoesTips)
		{
			int cost = 0, buyType = 0;
			StaticData::getShopItemPrice(shoessid, Things_gold, cost);
			if (!ItemOperator::testGoldEnough(cost))
			{
				return Error::NotEnoughGold;
			}
			return Error::Success;
		}
		//弹出提示框界面
		Game::getGameUI()->showFloatPanel(FloatPanelType::Item_shoesUse);
		((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setData(sid,reason);
		return Error::NotEnoughItem;
	}
	return Error::Success;
}


int CommonFunction::checkZhuiZonglingCount()
{
	const int zzlsid=SystemData::getLayoutValue("zhuizongling_sid");
	int count=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==zzlsid)
		{
			count+=pItem->count;
		}
	}
	if (count==0)
	{
		//弹出提示框界面
		Game::getGameUI()->showFloatPanel(FloatPanelType::Use_zhuizongling);
		return Error::NotEnoughItem;
	}
	return Error::Success;
}

CCMenuItemImage* CommonFunction::getReqMagicWeaponQLItem( UserItem* pUserItem )
{
	int reqid;
	int reqcnt;
	int qiLinglvl=pUserItem->data[ItemEquip::Item_EnhanceLevel];
	LuaData::getProp("gdOpenMagicWeapon",qiLinglvl,"reqId",reqid);
	LuaData::getProp("gdOpenMagicWeapon",qiLinglvl,"reqCnt",reqcnt);  

	UserItem* pItem=createNewItem(reqid);  

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==reqid)
		{
			count+=pItem->count;
		}
	}
	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getReqFootUpItem( UserItem* pUserItem )
{
	int reqid;
	int reqcnt;
	int id=pUserItem->sid;
	LuaData::getProp("gdFootUp",id,"reqId",reqid);
	LuaData::getProp("gdFootUp",id,"reqCnt",reqcnt);  

	UserItem* pItem=createNewItem(reqid);  

	CCMenuItemImage* reqItem=CommonFunction::getItemIconButDelete(pItem,false);

	int count=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==reqid)
		{
			count+=pItem->count;
		}
	}
	CCString *pStr=CCString::createWithFormat("%d/%d" , count, reqcnt);
	CCLabelTTF *pLable=CCLabelTTF::create(pStr->getCString(),"微软雅黑",20);
	if (count<reqcnt)
	{
		pLable->setColor(ccRED);
	}
	pLable->setPosition(ccp(reqItem->getContentSize().width/2,reqItem->getContentSize().height/2));
	reqItem->addChild(pLable);

	return reqItem;
}

CCMenuItemImage* CommonFunction::getTgtMagicWeaponQLItem( UserItem* pUserItem )
{
	UserItem* pItem = createNewItem(pUserItem->sid);
	pItem->iid = pUserItem->iid;
	pItem->name = pUserItem->name;
	pItem->category = pUserItem->category;
	pItem->icon = pUserItem->icon;
	pItem->profession = pUserItem->profession;
	for (int idx = 0;idx < ItemEquip::Item_Max;idx++)
	{
		if (idx == ItemEquip::Item_EnhanceLevel)
		{
			pItem->data[idx] = pUserItem->data[idx]+1;
		}
		else
		{
			pItem->data[idx] = pUserItem->data[idx];
		}
	}
	CCMenuItemImage* QilingAft = CommonFunction::getItemIconButDelete(pItem,false);  
	QilingAft->setPosition(SystemData::getLayoutPoint("HWQL_SJXGYL_pos"));
	EffectSprite* pEffect = EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(QilingAft->getContentSize().width/2,QilingAft->getContentSize().height/2));
	QilingAft->addChild(pEffect);

	return QilingAft;
	
}

CCMenuItemImage* CommonFunction::getTgtFootUpItem( UserItem* pUserItem )
{
	int sidAft=0;
	sidAft = pUserItem->sid + 1 ;
	std::string iconAft;
	LuaData::getProp(LuaData::ITEM,sidAft,"icon",iconAft);
	UserItem* pItem=new UserItem;
	pItem->sid=sidAft;
	pItem->iid=pUserItem->iid;
	LuaData::getProp(LuaData::ITEM,sidAft,"name",pItem->name);
	pItem->category=pUserItem->category;
	pItem->icon=iconAft;
	pItem->profession=pUserItem->profession;
	for (int idx=0;idx<ItemEquip::Item_Max;idx++)
	{
		pItem->data[idx]=pUserItem->data[idx];
	}

	CCMenuItemImage* UpgradeAft=CommonFunction::getItemIconButDelete(pItem,false);
	UpgradeAft->setPosition(SystemData::getLayoutPoint("HWQL_SJXGYL_pos"));
	EffectSprite* pEffect=EffectSprite::create(Effect::effect_itemborder);
	pEffect->setPosition(ccp(UpgradeAft->getContentSize().width/2,UpgradeAft->getContentSize().height/2));
	UpgradeAft->addChild(pEffect);

	return UpgradeAft;
}

int CommonFunction::getContentID( int m_iCurSubType )
{
	if (m_iCurSubType == TAG_HWTH)
	{
		return 4;
	}
	if (m_iCurSubType == TAG_HWQL)
	{
		return 17;
	}
	if (m_iCurSubType==TAG_PTQH)
	{
		return 2;
	}
	if (m_iCurSubType==TAG_WMQH)
	{
		return 19;
	}
	if (m_iCurSubType==TAG_QHDM)
	{
		return 18;
	}
	if (m_iCurSubType==TAG_CBYH)
	{
		return 20;
	}
	return 0;
}

int CommonFunction::getStoneLvl(std::string itemname)
{
	std::string name=itemname;
	int cnt_int=0;
	const char *c=name.c_str();
	for(int i=0;c[i]!='\0';++i)
	{
		if(c[i]>='0'&& c[i]<='9') //如果是数字.
		{
			cnt_int*=10;
			cnt_int+=c[i]-'0';
		}
	}
	return cnt_int;
}

int CommonFunction::getItemCnt( int itemId )
{
	int count=0;
	//LuaData::getProp("gdOpenMagicWeapon",qiLinglvl,"reqId",reqid);
	UserItem* pItem=createNewItem(itemId); 
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==itemId)
		{
			count+=pItem->count;
		}
	}
	return count;
}

CCMenuItemImageWithItem* CommonFunction::getItemIconButDelete( UserItem* pUserItem, bool flagcount/*=true*/ )
{
	return CommonFunction::getItemIcon(pUserItem,flagcount,true);
}

CCMenuItemImageWithItem::CCMenuItemImageWithItem()
{
	m_pUserItem = NULL;
}

CCMenuItemImageWithItem::~CCMenuItemImageWithItem()
{
	if (m_bisDelete)
	{
		CC_SAFE_DELETE(m_pUserItem);
	}
}

CCMenuItemImageWithItem * CCMenuItemImageWithItem::create( UserItem* pUserItem ,bool isdelete)
{
	CCMenuItemImageWithItem *ret = new CCMenuItemImageWithItem;
	if (ret && ret->initWithItem(pUserItem,isdelete))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return ret;
}

bool CCMenuItemImageWithItem::initWithItem( UserItem* pUserItem ,bool isdelete)
{
	this->init();
	m_pUserItem = pUserItem;
	m_bisDelete = isdelete;
	return true;
}

UserItem* CCMenuItemImageWithItem::getItemData()
{
	return m_pUserItem;
}

bool CommonFunction::CheckRubishEquip(int sid)
{
	int curlvl = HeroData::getLevel();
	int rebornLv = 0;
	rebornLv = HeroData::getProp(Entity::attr_reborn);
	if (curlvl >= 40 || rebornLv > 0)
	{
		bool ex = LuaData::checkIdExist("gdRubishEquipResList",sid);

		if (ex)
		{
			return true;
		}
	}
	return false;
}

bool CommonFunction::checkCanBatchedUsing( int sid )
{
	bool flag1 =false;
	Lua::instance()->push(sid);		
	if( Lua::instance()->call("ItemCheckSpecialBatchedUsing", 1, 1) 
		&& Lua::instance()->pop(flag1))
	{
		return flag1;
	}
	return flag1;
}
