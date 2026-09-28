#include "IconTipPanel.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/StaticData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/UserItemData.h"
#include "event/EventProtocol.h"
#include "userdata/IconTipsData.h"
#include "event/CPEventHelper.h"
#include "userdata/HeroData.h"
#include "EntityDefinition.h"
#include "event/CPEventDispatcher.h"
#include "ActivityDefinition.h"
#include "userdata/luadata/LuaData.h"
#include "RelationshipDefinition.h"
#include "module/ModuleData.h"
#include "module/GuideModule.h"
#include "userdata/NPCFunctionData.h"
#include "SceneDefinition.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/ActivityData.h"
#include "element/AnimElement.h"
#include "element/ElementDefinition.h"
#include "scene/panel/functionPanel/ActivityPanel.h"
#include "scene/panel/functionPanel/CharacterPanel.h"
#include "scene/SceneHelper.h"
#include "scene/NotificationHelper.h"
#include "scene/panel/shop/NpcShopPanel.h"
#include "ext/CCActionDestroy.h"
#include "scene/GameUI.h"
#include "scene/Game.h"
#include "module/UserDataModule.h"
#include "script/LuaWrapper.h"
#include "userdata/FuncData.h"
#include "scene/panel/FloatPanelType.h"
#include "utils/StringUtils.h"
#include "utils/MacroUtils.h"
#include "userdata/BoothData.h"
#include "userdata/socialdata/SocialData.h"

IconTipPanel::IconTipPanel():
	m_pMainMenu(NULL)
{
	if (!IconTipsData::m_isInit)
	{
		IconTipsData::initorclear();
	}
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.addEventListener("closeTip", this);
}

IconTipPanel::~IconTipPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.removeEventListener("closeTip", this);
}

IconTipPanel* IconTipPanel::create()
{
	IconTipPanel* characterPanel = new IconTipPanel();
	if(characterPanel && characterPanel->init())
	{
		characterPanel->autorelease();
		return characterPanel;
	}

	if (characterPanel)
	{
		delete characterPanel;
	}
	return NULL;
}

bool IconTipPanel::init()
{
	m_pMainMenu=GeneralMenu::create();
	if (!m_pMainMenu) return false;
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	showBossTips(0);

	/*if (CheckRebornReq())
	{
		addIcon(T_reborntips);
	}
	else
	{
		removeIcon(T_reborntips);
	}*/
	initCheckList();
	refreshList();
	return true;
}

void IconTipPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();
		CCMenuItemImageEx* pItem = dynamic_cast<CCMenuItemImageEx*>(pNode);
		IconData tips;
		tips.icondata = 0;
		tips.icontag = 0;
		if (pItem)
		{
			tips.icontag = pItem->getDataX();
			tips.icondata = pItem->getDataY();
		}

		switch (tag)
		{
		case T_bagfull:
			CPEventHelper::openPanel("NpcShopComp",TAG_NPCSHOP_CARRY,0,0,0);
			break;
		case T_itemendure:
			CPEventHelper::openPanel("FloatPanel",FloatPanelType::Item_NotEndure,0,0,0);
			break;
		case T_itembroken:
			CPEventHelper::openPanel("FloatPanel",FloatPanelType::Item_NotEndure,0,0,0);
			break;
		case T_reborntips:
			CPEventHelper::openPanel("FloatPanel",FloatPanelType::Reborn_Tips,0,0,0);
			break;
		case T_shortmedicinal:
			CPEventHelper::openPanel("NpcShopComp",TAG_NPCSHOP_CARRY,0,0,0);
			break;
		case T_mining:
			if (equipedMineTools())
			{
				NotificationHelper::showNote(LayoutData::getString(CPModuleName::COMMON, "hasChangedMiningTools"));
				//开始自动挖矿
				GameData::s_user->m_pMainRole->autoToMine();
			}
			else
			{
				int mineiid = 0, minesid = 0;
				if (getMineToolsInBag(mineiid, minesid))
				{
					ModuleData::setInt(CPModuleName::GUIDE, CPGuideData::VALUE_1, minesid);
					ModuleData::setInt(CPModuleName::GUIDE, CPGuideData::VALUE_2, mineiid);
					CPEventHelper::openPanel("NewItemUsePanel");
				}
				else
				{
					NotificationHelper::showNote(LayoutData::getString(CPModuleName::COMMON, "noMiningTools"));
				}
			}
			break;
		case T_perpareactivity:
			CPEventHelper::openPanel("MainPanel",2,Activity::AoB_Activity,tips.icondata,1);
			break;
		case T_findapprentice:
			CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"AddApprenticeConfirmDialog");
			CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_3,tips.icondata);
			CPEventHelper::uiNotify("UIShowSocialDialog","",0);
			break;
		case T_findmaster:
			CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"AddMasterConfirmDialog");
			CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_3,tips.icondata);
			CPEventHelper::uiNotify("UIShowSocialDialog","",0);
			break;
		case T_addfriend:
			CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2,"AddFriendConfirmDialog");
			CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_3,tips.icondata);
			CPEventHelper::uiNotify("UIShowSocialDialog","",0);
			break;
		case T_perpareboss:
			CPEventHelper::openPanel("MainPanel",2,Activity::AoB_Boss,tips.icondata,1);
			break;
		case T_forgetreward:
			ModuleData::setString(CPModuleName::GUIDE, CPGuideData::VALUE_1, IconTipsData::getForgetGiftStr(tips.icondata));
			ModuleData::setInt(CPModuleName::GUIDE, CPGuideData::VALUE_2, tips.icondata);
			CPEventHelper::openPanel("SystemGiftPanel");
			break;
		case T_hollowitem:
			ModuleData::setString(CPModuleName::GUIDE, CPGuideData::VALUE_1, SystemData::getLayoutString("Find_HollowItem"));
			ModuleData::setInt(CPModuleName::GUIDE, CPGuideData::VALUE_2,IconTipsData::getHollowIID());
			CPEventHelper::openPanel("HollowItemPanel");	
			break;
		case T_rubbish:
			CPEventHelper::openPanel("RubbishBagPanel");
			break;
		case T_boothsell:
			CPEventHelper::openPanel("BoothsellNotify",tips.icondata,0,0,0);
			removeIcon(T_boothsell,tips.icondata);
			break;
		case T_mail:
			ModuleData::setInt(CPModuleName::GUIDE, CPGuideData::VALUE_1, tips.icondata);
			CPEventHelper::openPanel("MailPanel");
			break;
		default:
			break;
		}
	}
}

void IconTipPanel::refreshList()
{
	if (!m_pMainMenu)
	{
		CCLog("m_pMainMenu is NULL");
		return;
	}
	CCArray* pChild = m_pMainMenu->getChildren();
	if (pChild && pChild->count()>0)
	{
		CCObject* pNode = NULL;
		CCARRAY_FOREACH(pChild,pNode)
		{
			CCMenuItemImage* p = dynamic_cast<CCMenuItemImage *>(pNode);
			if (p) p->runAction(CCSequence::create(CCShow::create(),CCActionInstantRemoveFromParent::create(),NULL));
		}
	}
	//m_pMainMenu->removeAllChildren();
	//int i=0;
	int n=0;
	int m=1;
	/*int size=IconTipsData::icontips_icondata.size();
	if (size>6)
	{
		i=size-6;
	}*/
	bool hasForgetReward = false;
	bool hasMail = false;
	std::vector<IconData>::iterator it= IconTipsData::icontips_icondata.begin();
	for (it;it!=IconTipsData::icontips_icondata.end();it++)
	{
		IconData& tips=*it;
		if (tips.icontag==T_perpareboss )
		{
			showBossTips(tips.icondata);
		}
		else
		{
			CCMenuItemImageEx* pItem=createIcon(tips.icontag,tips.icondata);
			if (pItem)
			{
				if (tips.icontag==T_forgetreward && hasForgetReward)
				{
					continue;
				}
				if (tips.icontag==T_forgetreward)
				{
					hasForgetReward = true;
				}
				if (tips.icontag==T_mail && hasMail)
				{
					continue;
				}
				if (tips.icontag==T_mail)
				{
					hasMail = true;
				}
				CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("icon_tips_pos").c_str(),m);
				pItem->setPosition(SystemData::getLayoutPoint(pStr->getCString()));
				m_pMainMenu->addChild(pItem);
				m++;
			}	
			/*if (n>=i)
			{
			}
			n++;*/
		}
	}
	IconTipsData::setIconCnt(m_pMainMenu->getChildrenCount());
	//int cnt=m_pMainMenu->getChildrenCount();
}

void IconTipPanel::addIcon(int tag,int data)
{
	if (IconTipsData::getIconArray(tag,data))
	{
		return;
	}
	IconTipsData::setIconArray(tag,data,true);
	//IconTipsData::icontips_map[tag]=data;

	IconData tips;
	tips.icontag=tag;
	tips.icondata=data;
	IconTipsData::icontips_icondata.push_back(tips);
	refreshList();
}

void IconTipPanel::removeIcon(int tag,int data)
{
	IconTipsData::setIconArray(tag,data,false);
	std::vector<IconData>::iterator it= IconTipsData::icontips_icondata.begin();
	for (it;it!=IconTipsData::icontips_icondata.end();it++)
	{
		IconData tips=*it;
		if (tips.icontag==T_perpareboss)
		{
			if (getChildByTag(boss_tips_panel))
			{
				showBossTips(0);
				//removeChildByTag(boss_tips_panel);
			}
		}
		if (tips.icontag==tag && tips.icondata==data)
		{
			IconTipsData::icontips_icondata.erase(it);
			break;
		}
	}
	refreshList();
}

CCMenuItemImageEx* IconTipPanel::createIcon(int tag,int data)
{
	CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("icon_tips").c_str(),tag);
	CCMenuItemImageEx* pMenu=CCMenuItemImageEx::create(pStr->getCString());
	if (!pMenu) return NULL;
	pMenu->setAnchorPoint(ccp(0.5,0.5));
	pMenu->setTarget(this,menu_selector(IconTipPanel::menucallback));
	pMenu->setTag(tag);
	pMenu->setExData(tag,data,0);
	if (tag==T_itemendure || tag==T_itembroken)
	{
		int count=abs(getItemEndure());
		CCLabelTTF* p=CCLabelTTF::create(SystemData::intToString(count).c_str(),"",14);
		p->setColor(ccWHITE);
		p->setAnchorPoint(ccp(0,1));
		p->setPosition(ccp(5,pMenu->getContentSize().height));
		pMenu->addChild(p);
	}
	if (pMenu)
	{
		return pMenu;
	}
	return NULL;
}

void IconTipPanel::initCheckList()
{
	if (IsBagFull())
	{
		addIcon(T_bagfull);
	}
	else
	{
		removeIcon(T_bagfull);
	}
	if (CheckRubishEquip())
	{
		addIcon(T_rubbish);
	}
	else
	{
		removeIcon(T_rubbish);
	}
	CheckItemEndure();
	if (CheckMedicine())
	{
		addIcon(T_shortmedicinal);
	}
	else
	{
		removeIcon(T_shortmedicinal);
	}
	int iid = CheckHasHollowItem();
	IconTipsData::setHollowIID(0);
	removeIcon(T_hollowitem);
	if (iid==0)
	{
		removeIcon(T_hollowitem);
	}
	else
	{
		IconTipsData::setHollowIID(iid);
		addIcon(T_hollowitem);
	}
	CheckHasRelationApply();
}

void IconTipPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		initCheckList();
	}
}

void IconTipPanel::onCPEvent( const std::string &eventName )
{
	//initCheckList();
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerLvlExpNotify" || source=="HandleMessageUpdPlayerLvlExpNotify|Init" )
		{
			if (CheckRebornReq())
			{
				addIcon(T_reborntips);
			}
			else
			{
				removeIcon(T_reborntips);
			}
		}
		else if (source=="HandleMessageUpdPlayerPropsDataNotify")
		{
			int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (data1==Entity::attr_reborn)
			{
				if (CheckRebornReq())
				{
					addIcon(T_reborntips);
				}
				else
				{
					removeIcon(T_reborntips);
				}
			}
		}
		else if (source == "HandleMessageSyncActivityBossStateNotify" )
		{
			int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
			int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
			if ( data3==Activity::AoB_has_began && data1==Activity::AoB_Boss)
			{
				addIcon(T_perpareboss,data2);
			}
			else if (data3==Activity::AoB_is_end  && data1==Activity::AoB_Boss)
			{
				removeIcon(T_perpareboss,data2);
			}
		}
		else if (source == "HandleMessageMapSelfEnterNotify" )
		{
			if (isMineScene())
			{
				addIcon(T_mining);
			}
			else
			{
				removeIcon(T_mining);
			}
		}
		else if (source == "UIShowSocialDialog")
		{
			int op=CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
			int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
			switch (op)
			{
			case Opcode::SOCIAL_OP_REQUEST_ADD_FRIEND_NOTIFY:
				addIcon(T_addfriend,data1);
				break;
			case Opcode::SOCIAL_OP_REQUEST_ADD_MASTER_NOTIFY:
				addIcon(T_findmaster,data1);
				break;
			case Opcode::SOCIAL_OP_REQUEST_ADD_APPRENTICE_NOTIFY:
				addIcon(T_findapprentice,data1);
				break;
			case Opcode::SOCIAL_OP_REQUEST_ADD_COUPLE_NOTIFY:
				CCLog(" jie hun ~");
				break;
			default:
				break;
			}
		}
		else if (source == "HandleMessageFuncDataNotify")
		{
			int op=CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
			int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
			std::string data4=CPEventHelper::getEventStringData(CPEventData::VALUE_5);

			int funcid = FuncData::getCurFuncID();
			if (funcid==12)
			{
				int idx = BoothData::addSellData(data1,data2,data3);
				if (idx != 0)
				{
					addIcon(T_boothsell,idx);
				}
			}
			else
			{
				int showicon = 0;
				Lua::instance()->push(funcid);
				Lua::instance()->call("showIconTips",1,1);
				Lua::instance()->pop(showicon);

				if (showicon)
				{
					if (funcid==6)
					{
						if (data1==1)
						{
							addIcon(T_forgetreward,data2);
							IconTipsData::addForgetGiftData(data2,data3,data4 );
						}
						else
						{
							removeIcon(T_forgetreward,data2);
							IconTipsData::removeForgetGiftData(data2);
						}
					}
					else if (funcid==17)
					{
						if (data1==1)
						{
							addIcon(T_mail,data2);
							IconTipsData::addMailData(data2,data4 );
						}
						else
						{
							removeIcon(T_mail,data2);
							IconTipsData::removeMailData(data2);
						}
					}
				}
			}
		}
	}
	else if (eventName  == "closeTip")
	{
		int data1=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
		int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
		removeIcon(data1,data2);
	}
	else if (eventName == CPEventName::LGC_TIMER)
	{
		if (source =="TimeManager")
		{
			IconTipsData::checkForgetGiftTime();
		}
	}
	//refreshList();
}

bool IconTipPanel::IsBagFull()
{
	int count=0;
	UserItems useritem=GameData::s_user->getUserItemData()->userItems;
	for (UserItems::iterator it=useritem.begin();it!=useritem.end();it++)
	{
		if (it->first>=ItemPos::Player_Bag_Start && it->first<ItemPos::Player_Bag_End)
		{
			count++;
		}
	}
	if (UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_BAGWARM))
	{
		if (HeroData::getProp(Entity::attr_bagslot)-count<=2)
		{
			return true;
		}
	}
	else if(HeroData::getProp(Entity::attr_bagslot)-count<=0)
	{
		return true;
	}
	return false;
}

void IconTipPanel::CheckItemEndure()
{
	int count=getItemEndure();
	if (count<0)
	{
		addIcon(T_itembroken);
		removeIcon(T_itemendure);
	}
	else if (count>0)
	{
		addIcon(T_itemendure);
		removeIcon(T_itembroken);
	}
	else
	{
		//addIcon(T_itembroken);
		removeIcon(T_itembroken);
		removeIcon(T_itemendure);
	}
}

bool IconTipPanel::CheckMedicine()
{
	return false;
}

bool IconTipPanel::isMineScene()
{
	int miningFlag = 0;
	StaticData::getMapMiningFlag(GameData::s_user->mMap.mID, miningFlag);
	return (miningFlag != 0);
}

bool IconTipPanel::equipedMineTools()
{
	UserItem *item = GameData::s_user->getUserItemData()->getItemByPosition(-Pos_Weapon);
	if (item)
	{
		int miningFlag = 0;
		StaticData::getItemMiningFlag(item->sid, miningFlag);
		return (miningFlag != 0);
	}
	return false;
}

bool IconTipPanel::getMineToolsInBag( int &iid, int &sid )
{
	int miningFlag = 0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(UserItems::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (ItemPos::Player_Bag_Start <= it->first &&
			it->first <= ItemPos::Player_Bag_End)
		{
			UserItem *item = it->second;
			if (item)
			{
				StaticData::getItemMiningFlag(item->sid, miningFlag);
				if (miningFlag != 0)
				{
					iid = item->iid;
					sid = item->sid;
					return true;
				}
			}
		}
	}
	return false;
}

void IconTipPanel::showBossTips( int id )
{
	int size=IconTipsData::getIconCnt();
	int n = (size-1)/3+1;
	if (size == 0)
	{
		n = 0;
	}
	if (id==0)
	{
		BossTipsPanel* panel = (BossTipsPanel*)getChildByTag(boss_tips_panel);
		if (panel)
		{
			panel->setVisible(false);
			panel->setTouchEnabled(false);
		}
		else
		{
			panel=BossTipsPanel::create(id);
			if (!panel)
			{
				return;
			}
			panel->setPosition(ccp(SystemData::getLayoutValue("boss_tipspanel.x")-n*40,SystemData::getLayoutValue("boss_tipspanel.y")));
			panel->setVisible(false);
			panel->setTag(boss_tips_panel);
			addChild(panel,0);
			GameRole* myRole = GameData::getMyRole();
			if (myRole && myRole->mLevel<35)
			{
				panel->setVisible(false);
				panel->setTouchEnabled(false);
			}
		}
		panel->setPosition(ccp(SystemData::getLayoutValue("boss_tipspanel.x")-n*40,SystemData::getLayoutValue("boss_tipspanel.y")));
	}
	BossTipsPanel* panel = (BossTipsPanel*)getChildByTag(boss_tips_panel);
	if (panel)
	{
		panel->updatebossid(id);
		GameRole* myRole = GameData::getMyRole();
		if (myRole && myRole->mLevel>=35 && id!=0)
		{
			panel->setVisible(true);
			panel->setTouchEnabled(true);			
		}
		panel->setPosition(ccp(SystemData::getLayoutValue("boss_tipspanel.x")-n*40,SystemData::getLayoutValue("boss_tipspanel.y")));
	}
}

int IconTipPanel::getItemEndure()
{
	UserItems useritem=GameData::s_user->getUserItemData()->userItems;
	int count=0;
	int brokencnt = 0;
	bool flag = false;
	for (UserItems::iterator it=useritem.begin();it!=useritem.end();it++)
	{
		if (it->first>=ItemPosition_Equip_Shenqi6 && it->first<ItemPosition_Null)//神器6
		{
			UserItem* p=it->second;
			int MaxEndure=0;
			LuaData::getProp(LuaData::ITEM,p->sid,"durable",MaxEndure);	
			float max=(float)MaxEndure;
			float now=(float)p->data[ItemEquip::Item_Durable];
			float per=now/max;
			if (now == max && max!=0)
			{
				brokencnt++;
				flag = true;
			}
			if (per>0.9)
			{
				count++;
			}
		}
	}
	if (flag)
	{
		return -brokencnt;
	}
	return count;
}

bool IconTipPanel::CheckRebornReq()
{
	int curlvl = HeroData::getLevel();
	int maxlvl = 0;
	LuaData::getProp("gdEvolutionCondition",HeroData::getProp(Entity::attr_reborn),"maxlvl",maxlvl);
	if (curlvl!=maxlvl)
	{
		return false;
	}
	return true;
}

bool IconTipPanel::CheckRubishEquip()
{
	int curlvl = HeroData::getLevel();
	int rebornLv = 0;
	rebornLv = HeroData::getProp(Entity::attr_reborn);
	if (curlvl >= 40 || rebornLv > 0)
	{
		UserItems items = GameData::s_user->getUserItemData()->userItems;
		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			if (it->first >= ItemPos::Player_Bag_Start && it->first < ItemPos::Player_Bag_End)
			{
				UserItem* pItem=(UserItem*)it->second;
				int id = pItem->sid;
				bool ex = LuaData::checkIdExist("gdRubishEquipResList",id);

				if (pItem && ex)
				{
					return true;
				}
			}
		}
	}
	return false;
}

int IconTipPanel::CheckHasHollowItem()
{
	UserItems useritem=GameData::s_user->getUserItemData()->userItems;
	bool flag = false;
	for (UserItems::iterator it=useritem.begin();it!=useritem.end();it++)
	{
		if (it->first>=ItemPos::Hollow_Bag_Start && it->first<ItemPos::Hollow_Bag_End)
		{
			return it->second->iid;
		}
	}
	return 0;
}

bool IconTipPanel::CheckIsSellOut()
{
	return false;
}

void IconTipPanel::CheckHasRelationApply()
{
	typedef std::map<int ,std::string> socialMap;
	const socialMap &fMap = SocialData::getFriendList();
	for (socialMap::const_iterator it =fMap.begin();it!=fMap.end();it++)
	{
		addIcon(T_addfriend,it->first);
	}
	const socialMap &mMap = SocialData::getMasterList();
	for (socialMap::const_iterator it =mMap.begin();it!=mMap.end();it++)
	{
		addIcon(T_findmaster,it->first);
	}
	const socialMap &aMap = SocialData::getApprenticeList();
	for (socialMap::const_iterator it =aMap.begin();it!=aMap.end();it++)
	{
		addIcon(T_findapprentice,it->first);
	}
}



//-----------------------------------------------------------------------------------------------------------------------//
#define BOSS_ANIM_TAG 100

BossTipsPanel::BossTipsPanel():
	m_iBossId(0),
	m_iBoosSid(0),
	mapNameBtn(NULL)
{

}

BossTipsPanel::~BossTipsPanel()
{

}

BossTipsPanel* BossTipsPanel::create( int id )
{
	BossTipsPanel* characterPanel = new BossTipsPanel();
	if(characterPanel && characterPanel->init(id))
	{
		characterPanel->autorelease();
		return characterPanel;
	}

	if (characterPanel)
	{
		delete characterPanel;
	}
	return NULL;
}

bool BossTipsPanel::init( int id )
{
	initUI();
	updatebossid(id);
	return true;
}

void BossTipsPanel::initUI()
{
	CCScale9Sprite* bkg=SystemData::getScale9SpriteByPlist("boss_tips",SystemData::getLayoutValue("boss_tips.w"),SystemData::getLayoutValue("boss_tips.h")); 
	bkg->setAnchorPoint(CCPointZero);
	bkg->setPosition(CCPointZero);
	addChild(bkg);

	m_nHeight=bkg->getContentSize().width;
	m_nWidth=bkg->getContentSize().height;
	addCover();

	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));

	CCSprite* pTitle = SystemData::getSpriteByPlist("boss_titlebkg");
	pTitle->setAnchorPoint(ccp(0.5,1));
	pTitle->setPosition(ccp(m_nWidth/2+5,m_nHeight-10));
	addChild(pTitle);

	//底盘
	CCSprite* pBottomSprite = SystemData::getSpriteByPlist("boss_dipan"); 
	pBottomSprite->setPosition(ccp(m_nWidth/2,18));
	pBottomSprite->setScale(0.5f);
	addChild(pBottomSprite);

	CCMenu* pMenu=CCMenu::create();
	if (!pMenu) return;
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pShoes=SystemData::getMenuItemImageByPlist("boss_shoes");
	if (!pShoes) return;
	//pShoes->setAnchorPoint(ccp(0.5,0));
	pShoes->setScale(0.8f);
	pShoes->setPosition(ccp(bkg->getPositionX()+bkg->getContentSize().width-pShoes->getContentSize().width/2+10,bkg->getPositionY()+pShoes->getContentSize().height/2+5));
	pShoes->setTarget(this,menu_selector(BossTipsPanel::clickShoes));
	pMenu->addChild(pShoes);

	/*CCLabelTTF* pLabel=CCLabelTTF::create("BOSS","",20);
	pLabel->setColor(ccYELLOW);
	pLabel->setPosition(ccp(bkg->getPositionX()+bkg->getContentSize().width/2,bkg->getPositionY()+bkg->getContentSize().height-pLabel->getContentSize().height));
	addChild(pLabel);*/


	mapNameBtn = CCMenuItemFont::create(" ",this, menu_selector(BossTipsPanel::clickName));
	//mapNameBtn->setAnchorPoint(CCPointZero);
	mapNameBtn->setAnchorPoint(ccp(0,0.5));
	mapNameBtn->setPosition(ccp(pTitle->getPositionX()-pTitle->getContentSize().width/2+20,pTitle->getPositionY()-pTitle->getContentSize().height/2));
	mapNameBtn->setScale(0.6f);
	pMenu->addChild(mapNameBtn);
	//CCMenuItemTextImage* pbossname=CCMenuItemTextImage::create("","","",this,menu_selector(BossTipsPanel::clickName));
	

	CCMenuItemImage* p=SystemData::getMenuItemImageByPlist("boss_close");
	p->setScale(0.7f);
	p->setPosition(ccp(pTitle->getPositionX()+pTitle->getContentSize().width/2-p->getContentSize().width/2-10,pTitle->getPositionY()-pTitle->getContentSize().height/2));
	p->setTarget(this,menu_selector(BossTipsPanel::close));
	pMenu->addChild(p);

	CCMenuItem* pBossBtn=CCMenuItem::create(this,menu_selector(BossTipsPanel::clickboss));
	pBossBtn->setContentSize(CCSizeMake(m_nWidth,m_nHeight-10));
	pBossBtn->setAnchorPoint(CCPointZero);
	pBossBtn->setPosition(ccp(10,25));
	pMenu->addChild(pBossBtn);

}

void BossTipsPanel::close( CCObject* pSender )
{
	if (m_iBossId==0 && m_iBoosSid==0)
	{
		return;
	}
	closeself();
}

void BossTipsPanel::clickShoes( CCObject* pSender )
{
	if (m_iBossId==0 && m_iBoosSid==0)
	{
		return;
	}
	int playerLv = 0;
	int bossLv = 0;
	playerLv = HeroData::getLevel();
	LuaData::getProp(LuaData::MONSTER,m_iBoosSid,"lvl",bossLv);
	if (playerLv < bossLv && HeroData::getProp(Entity::attr_reborn) < 1)
	{
		CPEventHelper::uiNotify("","",Error::Not_enough_lvl_for_boss);
		return;
	}
	SceneHelper::teleportToActivityBoss(m_iBossId);
	closeself();
}

void BossTipsPanel::clickName( CCObject* pSender )
{
	if (m_iBossId==0 && m_iBoosSid==0)
	{
		return;
	}
	int mapID = 0, x = 0, y = 0;
	ActivityPanelHelper::getBossPos(m_iBossId,mapID,x,y);
	if (mapID > 0 &&
		x > 0 &&
		y > 0)
	{
		GameRole* myRole = GameData::getMyRole();
		if (!myRole) return;
		myRole->m_iTargetSid=m_iBoosSid;
		myRole->startAutoMoveToCrossMap(mapID, x, y, GHOST_TYPE_MONSTER);
	}
}

void BossTipsPanel::clickboss( CCObject* pSender )
{
	if (m_iBossId==0 && m_iBoosSid==0)
	{
		return;
	}
	int mapID = 0, x = 0, y = 0;
	ActivityPanelHelper::getBossPos(m_iBossId,mapID,x,y);
	if (mapID > 0 &&
		x > 0 &&
		y > 0)
	{
		GameRole* myRole = GameData::getMyRole();
		if (!myRole) return;
		myRole->m_iTargetSid=m_iBoosSid;
		myRole->startAutoMoveToCrossMap(mapID, x, y, GHOST_TYPE_MONSTER);
		//GameData::s_user->m_pMainRole->setEasyAI(true);
	}
}

void BossTipsPanel::updatebossid( int id )
{
	mapNameBtn->setString(" ");
	CCNode *animNode = getChildByTag(BOSS_ANIM_TAG);
	if (animNode)
	{
		animNode->removeFromParent();
	}

	if (id==0)
	{
		this->setVisible(false);
		this->setTouchEnabled(false);
		m_iBossId=0;
		m_iBoosSid=0;
		return;
	}

	this->setVisible(true);
	this->setTouchEnabled(true);
	m_iBossId=id;
	m_iBoosSid = ActivityData::getWorldBossSID(m_iBossId);


	std::string name;
	LuaData::getProp(LuaData::MONSTER,m_iBoosSid,"name",name);
	mapNameBtn->setString(name.c_str());

	AnimElement *anim = AnimElement::create(m_iBoosSid, CPElement::Type::monster);
	if (!anim) return;
	anim->setCloth(m_iBoosSid);
	anim->setScale(0.8f);
	anim->setPosition(ccp(m_nWidth/2,m_nHeight/2-50));
	anim->setTag(BOSS_ANIM_TAG);
	addChild(anim);

	this->runAction(CCSequence::create(CCDelayTime::create(120),CCCallFunc::create(this,callfunc_selector(BossTipsPanel::closeself)),NULL));
}

void BossTipsPanel::closeself()
{
	((IconTipPanel*)(this->getParent()))->removeIcon(T_perpareboss,m_iBossId);
	this->setVisible(false);
	this->setTouchEnabled(false);
	m_iBossId=0;
	m_iBoosSid=0;
	mapNameBtn->setString(" ");

	CCNode *anim = getChildByTag(BOSS_ANIM_TAG);
	if (anim)
	{
		anim->removeFromParent();
	}
}

CCMenuItemImageEx::CCMenuItemImageEx()
{

}

CCMenuItemImageEx::~CCMenuItemImageEx()
{

}

CCMenuItemImageEx * CCMenuItemImageEx::create( const std::string& key )
{
	CCMenuItemImageEx *ret = new CCMenuItemImageEx;
	if (ret && ret->initbyplist(key))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return ret;
}

void CCMenuItemImageEx::setExData( int dataX, int dataY, int dataZ )
{
	mDataX = dataX;
	mDataY = dataY;
	mDataZ = dataZ;
}

int CCMenuItemImageEx::getDataX()
{
	return mDataX;
}

int CCMenuItemImageEx::getDataY()
{
	return mDataY;

}

int CCMenuItemImageEx::getDataZ()
{

	return mDataZ;
}

bool CCMenuItemImageEx::initbyplist( const std::string& key )
{
	this->init();
	std::string file;
	if (SystemData::layout.parse(key, file))
	{
		std::string file_sel;
		std::string key_ex = key + ".sel";
		CCSpriteFrame *normalframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file.c_str());	
		this->setNormalSpriteFrame(normalframe);
		if(SystemData::layout.parse(key_ex, file_sel))
		{
			CCSpriteFrame *selframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file_sel.c_str());
			this->setSelectedSpriteFrame(selframe);
		}
	}
	return true;
}


//-------------------------------------------------------------------------------------------------------------------------------------


CopyNotifyTipPanel::CopyNotifyTipPanel():
	copyID(0),
	m_textDesc(NULL),
	m_copyName(NULL),
	m_recLvl(NULL),
	m_recBattel(NULL)
{

}

CopyNotifyTipPanel::~CopyNotifyTipPanel()
{

}

bool CopyNotifyTipPanel::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	initUI();
	copyID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
	initCopyDesc();
	return true;
}

void CopyNotifyTipPanel::initUI()
{
	CCScale9Sprite* bkg=SystemData::getScale9SpriteByPlist("copynotify_tip",SystemData::getLayoutValue("copynotify_tip.w"),SystemData::getLayoutValue("copynotify_tip.h")); 
	bkg->setAnchorPoint(CCPointZero);
	bkg->setPosition(ccp(250,145));
	addChild(bkg);

	CCLayer* descLayer = CCLayer::create();
	descLayer->setAnchorPoint(CCPointZero);
	descLayer->setPosition(ccp(250,145));
	descLayer->setContentSize(CCSizeMake(305,230));
	addChild(descLayer);

	m_nHeight=bkg->getContentSize().width;
	m_nWidth=bkg->getContentSize().height;
	addCover();

	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));

	CCScale9Sprite* pTitlesp = SystemData::getScale9SpriteByPlist("copynotify_title",SystemData::getLayoutValue("copynotify_title.w"),SystemData::getLayoutValue("copynotify_title.h"));
	pTitlesp->setPosition(ccp(403,370));
	addChild(pTitlesp);

	CCLabelTTF* pTitle = SystemData::getLabelTTF("copynotify_tip_title");
	pTitle->setColor(ccYELLOW);
	pTitle->setFontSize(18);
	pTitle->setPosition(ccp(403,370));
	addChild(pTitle);

	m_textDesc = CCLabelTTF::create();
	m_textDesc->setAnchorPoint(ccp(0,1.0));
	m_textDesc->setDimensions(CCSizeMake(descLayer->getContentSize().width-20,0));
	m_textDesc->setPosition(ccp(10,200));
	descLayer->addChild(m_textDesc);

	CCLabelTTF* pLabel1 = SystemData::getLabelTTF("copynotify_tip_label1");
	pLabel1->setColor(ccORANGE);
	pLabel1->setFontSize(16);
	pLabel1->setAnchorPoint(CCPointZero);
	pLabel1->setPosition(ccp(10,105));
	descLayer->addChild(pLabel1);

	m_copyName = CCLabelTTF::create();
	m_copyName->setAnchorPoint(CCPointZero);
	m_copyName->setPosition(ccp(pLabel1->getPositionX()+160,pLabel1->getPositionY()));
	descLayer->addChild(m_copyName);

	CCLabelTTF* pLabel2 = SystemData::getLabelTTF("copynotify_tip_label2");
	pLabel2->setColor(ccORANGE);
	pLabel2->setFontSize(16);
	pLabel2->setAnchorPoint(CCPointZero);
	pLabel2->setPosition(ccp(10,85));
	descLayer->addChild(pLabel2);

	m_recLvl = CCLabelTTF::create();
	m_recLvl->setAnchorPoint(CCPointZero);
	m_recLvl->setPosition(ccp(pLabel2->getPositionX()+160,pLabel2->getPositionY()));
	descLayer->addChild(m_recLvl);

	CCLabelTTF* pLabel3 = SystemData::getLabelTTF("copynotify_tip_label3");
	pLabel3->setColor(ccORANGE);
	pLabel3->setFontSize(16);
	pLabel3->setAnchorPoint(CCPointZero);
	pLabel3->setPosition(ccp(10,65));
	descLayer->addChild(pLabel3);

	m_recBattel = CCLabelTTF::create();
	m_recBattel->setAnchorPoint(CCPointZero);
	m_recBattel->setPosition(ccp(pLabel3->getPositionX()+160,pLabel3->getPositionY()));
	descLayer->addChild(m_recBattel);

	CCMenu* cp=CCMenu::create();
	cp->setAnchorPoint(CCPointZero);
	cp->setPosition(CCPointZero);
	descLayer->addChild(cp);

	CCMenuItemImage* pShoes=SystemData::getMenuItemImageByPlist("boss_shoes");	
	pShoes->setAnchorPoint(ccp(0.5,0));
	pShoes->setScale(0.8f);
	pShoes->setPosition(ccp(270,61));
	pShoes->setTarget(this,menu_selector(CopyNotifyTipPanel::clickShoes));
	cp->addChild(pShoes);

	CCMenuItemImage* p=SystemData::getMenuItemImageByPlist("copynotify_close");
	p->setScale(0.7f);
	p->setPosition(ccp(283,225));
	p->setTarget(this,menu_selector(CopyNotifyTipPanel::close));
	cp->addChild(p);

	CCMenuItem* pBtn=SystemData::getMenuItemImageByPlist("copynotify_confirm");
	pBtn->setTarget(this,menu_selector(CopyNotifyTipPanel::close));
	pBtn->setPosition(ccp(153,35));
	cp->addChild(pBtn);

	CCLabelTTF* pLbl=SystemData::getLabelTTF("panel_QueDing_label");
	pLbl->setFontSize(18);
	pLbl->setColor(ccWHITE);
	pLbl->setPosition(pBtn->getPosition()); 
	descLayer->addChild(pLbl);
}

void CopyNotifyTipPanel::close( CCObject* pSender )
{
	this->removeFromParent();
}

void CopyNotifyTipPanel::clickShoes( CCObject* pSender )
{
	int goalID = 0;
	LuaData::getProp("gdCopyNotify",copyID,"flygoal",goalID);
	NPCFunctionData::useShoes(goalID,Scene::seNpc);
	this->removeFromParent();
}

void CopyNotifyTipPanel::initCopyDesc()
{
	std::string name = "";
	std::string desc = "";
	int battel = 0;
	int lvl = 0;
	int reborn = 0;
	LuaData::getProp("gdCopyNotify",copyID,"copyName",name);
	LuaData::getProp("gdCopyNotify",copyID,"recommendbattle",battel);
	LuaData::getProp("gdCopyNotify",copyID,"desc",desc);
	LuaData::getProp("gdCopyNotify",copyID,"recommend_lvl",lvl);
	LuaData::getProp("gdCopyNotify",copyID,"recommend_reborn",reborn);
	m_copyName->setString(name.c_str());
	m_copyName->setFontSize(16);
	m_copyName->setColor(ccORANGE);

	m_recBattel->setString(SystemData::intToString(battel).c_str());
	m_recBattel->setFontSize(16);
	m_recBattel->setColor(ccORANGE);

	m_textDesc->setString(desc.c_str());
	m_textDesc->setFontSize(16);
	m_textDesc->setColor(ccWHITE);

	//	recLvl->setString(SystemData::intToString(lvl).c_str());
	if (reborn > 0)
	{
		m_recLvl->setString(StringUtils::levelToString(reborn,lvl).c_str());
	}else
	{
		m_recLvl->setString(SystemData::intToString(lvl).c_str());
	}
	m_recLvl->setFontSize(16);
	m_recLvl->setColor(ccORANGE);
}
