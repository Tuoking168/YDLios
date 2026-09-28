#include "SettingProtectPanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"
#include "module/UserDataModule.h"
#include "controls/CPComboBox.h"
#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"
#include "module/ModuleData.h"
#include "userdata/luadata/LuaData.h"
#include "scene/GameUI.h"
#include "event/EventProtocol.h"
#include "logic/CPUpdateFunctor/CPUpdateFunctorDefination.h"
#include "logic/CPUpdateFunctor/CPUpdateFunctorManager.h"
#include "userdata/UserData.h"


SettingProtectPanel::SettingProtectPanel( void ):
	m_CurNode(NULL),
	m_iCurClickBoxID(0)
{
	memset(taglist, 0, sizeof(taglist));
	taglist[Slow_HP] = CPUFDefination::HpLow_Potion1;
	taglist[Fast_HP] = CPUFDefination::HpLow_Potion2;
	taglist[Slow_MP] = CPUFDefination::MpLow_Potion1;
	taglist[Fast_MP] = CPUFDefination::MpLow_Potion2;
	taglist[Home_Set] = CPUFDefination::HpLow_Scroll;
	taglist[Item_Endure] = CPUFDefination::EquipDuration;
	taglist[SS_Special] = CPUFDefination::Skill_DS_Hui_Fu_Shu;

	//
	for (int i=0;i<MyEnum_Max;i++)
	{
		const std::string &strsr=CPUserData::UPDATE_FUNCTOR_ID+SystemData::intToString(taglist[i])+ "_";	
	
		m_setData[taglist[i]].m_open = (bool)UserData::getIntData(HeroData::getPID(),strsr,1);
		m_setData[taglist[i]].m_seconds = UserData::getIntData(HeroData::getPID(),strsr,2);
		m_setData[taglist[i]].m_life = UserData::getIntData(HeroData::getPID(),strsr,3);
		m_setData[taglist[i]].m_itemSid = UserData::getIntData(HeroData::getPID(),strsr,4);
	}
}

SettingProtectPanel::~SettingProtectPanel( void )
{

}

SettingProtectPanel* SettingProtectPanel::create()
{
	SettingProtectPanel* pPanel = new SettingProtectPanel();
	if(pPanel && pPanel->init())
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

bool SettingProtectPanel::init()
{
	CCScale9Sprite* prightborder2=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_protect_border2.w"),SystemData::getLayoutValue("ui_setting_protect_border2.h"));
	prightborder2->setAnchorPoint(CCPointZero);
	prightborder2->setPosition(SystemData::getLayoutPoint("ui_setting_base_left_text"));
	addChild(prightborder2);

	CCScale9Sprite* prightborder1=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_protect_border1.w"),SystemData::getLayoutValue("ui_setting_protect_border1.h"));
	prightborder1->setAnchorPoint(CCPointZero);
	prightborder1->setPosition(ccp(prightborder2->getPositionX(),prightborder2->getPositionY()+prightborder2->getContentSize().height));
	addChild(prightborder1);

	CCLabelTTF* prightlabel=SystemData::getLabelTTF("ui_setting_protect_down_text");
	prightlabel->setColor(ccWHITE);
	prightlabel->setFontSize(18);
	prightlabel->setPosition(ccp(prightborder1->getContentSize().width/2,prightborder1->getContentSize().height/2));
	prightborder1->addChild(prightlabel);

	CCScale9Sprite* prightborder4=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_protect_border4.w"),SystemData::getLayoutValue("ui_setting_protect_border4.h"));
	prightborder4->setAnchorPoint(CCPointZero);
	prightborder4->setPosition(ccp(prightborder1->getPositionX(),prightborder1->getPositionY()+prightborder1->getContentSize().height));
	addChild(prightborder4);

	CCScale9Sprite* prightborder3=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_protect_border3.w"),SystemData::getLayoutValue("ui_setting_protect_border3.h"));
	prightborder3->setAnchorPoint(CCPointZero);
	prightborder3->setPosition(ccp(prightborder4->getPositionX(),prightborder4->getPositionY()+prightborder4->getContentSize().height));
	addChild(prightborder3);

	CCLabelTTF* prightlabel2=SystemData::getLabelTTF("ui_setting_protect_up_text");
	prightlabel2->setColor(ccWHITE);
	prightlabel2->setFontSize(18);
	prightlabel2->setPosition(ccp(prightborder3->getContentSize().width/2,prightborder3->getContentSize().height/2));
	prightborder3->addChild(prightlabel2);

	initUpPanel();
	initDownPanel();

	return true;
}

void SettingProtectPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		const int tag=pNode->getTag();
		switch (tag)
		{
		case 1:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON));
			}
			else if (HeroData::getJob()==UserData::CARRER_FS)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::AUTO_FS_ZIDONGKAIDUN,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_FS_ZIDONGKAIDUN));
			}
			else if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::SKILL_BAN_YUE_OFF,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SKILL_BAN_YUE_OFF));
				EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE);
			}
			break;
		case 2:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::AUTO_DS_ZIDONGZHAOHUANBAOBAO,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_DS_ZIDONGZHAOHUANBAOBAO));
			}
			else if (HeroData::getJob()==UserData::CARRER_FS)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON));
			}
			else if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::SKILL_CI_SHA_OFF,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SKILL_CI_SHA_OFF));
				EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE);
			}
			break;
		case 3:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::AUTO_FS_ZIDONGBINGFENGBAO,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_FS_ZIDONGBINGFENGBAO));
			}
			else if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::SKILL_LIE_HUO_OFF,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SKILL_LIE_HUO_OFF));
				EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE);
			}
			break;
		case 4:
			if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON));
			}
			break;
		default:
			break;
		}
		UserData::saveData();
	}
}

void SettingProtectPanel::initUpPanel()
{
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCPoint pos=SystemData::getLayoutPoint("ui_setting_protect_up_select");
	std::string sizestr="";
	std::string labelstr="";
	if (HeroData::getJob()==UserData::CARRER_ZS)
	{
		sizestr="ui_setting_protect_up_zs_size";
		labelstr="ui_setting_protect_up_zs";
	}
	else if (HeroData::getJob()==UserData::CARRER_FS)
	{
		sizestr="ui_setting_protect_up_fs_size";
		labelstr="ui_setting_protect_up_fs";
	}
	else if (HeroData::getJob()==UserData::CARRER_DS)
	{
		sizestr="ui_setting_protect_up_ds_size";
		labelstr="ui_setting_protect_up_ds";
	}
	else if (HeroData::getJob()==UserData::CARRER_OMNI)
	{
		sizestr="ui_setting_protect_up_zs_size";
		labelstr="ui_setting_protect_up_zs";
	}

	for (int i=1;i<=SystemData::getLayoutValue(sizestr);i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString(labelstr).c_str(),i);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(pStr->getCString());
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setDimensions(CCSizeMake(300,0));
		if (HeroData::getJob()==UserData::CARRER_FS && i==3)
		{
			pLabel->setDimensions(CCSizeMake(400,0));
		}
		CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
		pBox->setAnchorPoint(CCPointZero);
		pBox->setTag(i);
		pBox->setHandler(this,menu_selector(SettingProtectPanel::menucallback));
		pBox->setPosition(ccp(pos.x+(i-1)%2*300,pos.y-(i-1)/2*40));
		pMenu->addChild(pBox);

		switch (i)
		{
		case 1:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON));
				pBox->setChecked(false);
				pBox->setEnable(false);
				pLabel->setColor(ccGRAY);
			}
			else if (HeroData::getJob()==UserData::CARRER_FS)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_FS_ZIDONGKAIDUN));
			}
			else if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SKILL_BAN_YUE_OFF) == 0);
			}
			break;
		case 2:
			if (HeroData::getJob()==UserData::CARRER_DS)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_DS_ZIDONGZHAOHUANBAOBAO));
			}
			else if (HeroData::getJob()==UserData::CARRER_FS)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON));
				pBox->setChecked(false);
				pBox->setEnable(false);
				pLabel->setColor(ccGRAY);
			}
			else if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SKILL_CI_SHA_OFF) == 0);
			}
			break;
		case 3:
			if (HeroData::getJob()==UserData::CARRER_FS)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_FS_ZIDONGBINGFENGBAO));
			}
			else if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SKILL_LIE_HUO_OFF) == 0);
			}
			break;
		case 4:
			if (HeroData::getJob()==UserData::CARRER_ZS || HeroData::getJob()==UserData::CARRER_OMNI)
			{
				pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::AUTO_ATTACK_ON));
				pBox->setChecked(false);
				pBox->setEnable(false);
				pLabel->setColor(ccGRAY);
			}
			break;
		default:
			break;
		}
	}

	if (HeroData::getJob()==UserData::CARRER_DS)
	{
		int i = 3;
		CCLayer* p=getSSSpecial();
		p->setPosition(ccp(pos.x+(i-1)%2*300,pos.y-(i-1)/2*40));
		pMenu->addChild(p);
	}
}

void SettingProtectPanel::initDownPanel()
{
	const int size=MyEnum_Max-1;
	for (int i=0;i<size;i++)
	{
		CCLayer* p=getItemSetting(i);
		p->setPosition(ccp(SystemData::getLayoutPoint("ui_setting_protect_down_select").x,SystemData::getLayoutPoint("ui_setting_protect_down_select").y-i*46));
		addChild(p);
	} 
}

void SettingProtectPanel::onEnter()
{
	BasePanel::onEnter();
}

void SettingProtectPanel::onExit()
{
	UserData::saveData();
	BasePanel::onExit();
}

CCLayer* SettingProtectPanel::getItemSetting( int tag )
{
	CCLayer* pLayer=CCLayer::create();
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	pLayer->addChild(pMenu);

	std::string text1="";
	std::string sizestr="";
	std::string itemstr="";
	switch (tag)
	{
	case Slow_HP:
		sizestr="ui_setting_protect_slowhp_item_size";
		itemstr="ui_setting_protect_slowhp_item";
		text1="ui_setting_protect_hp_text";
		break;
	case Fast_HP:
		sizestr="ui_setting_protect_fasthp_item_size";
		itemstr="ui_setting_protect_fasthp_item";
		text1="ui_setting_protect_hp_text";
		break;
	case Slow_MP:
		sizestr="ui_setting_protect_slowmp_item_size";
		itemstr="ui_setting_protect_slowmp_item";
		text1="ui_setting_protect_mp_text";
		break;
	case Fast_MP:
		sizestr="ui_setting_protect_fastmp_item_size";
		itemstr="ui_setting_protect_fastmp_item";
		text1="ui_setting_protect_mp_text";
		break;
	case Home_Set:
		sizestr="ui_setting_protect_lushi_item_size";
		itemstr="ui_setting_protect_lushi_item";
		text1="ui_setting_protect_hp_text";
		break;
	case Item_Endure:
		sizestr="ui_setting_protect_endure_item_size";
		itemstr="ui_setting_protect_endure_item";
		text1="ui_setting_protect_zhuangbeinaijiu";
		break;
	case SS_Special:
		sizestr="ui_setting_protect_endure_item_size";
		itemstr="ui_setting_protect_endure_item";
		text1="ui_setting_protect_zidongbuxue";
		break;
	default:
		break;
	}
	
	int realtag = taglist[tag];

	CCLabelTTF* pLabel=SystemData::getLabelTTF(text1.c_str());
	pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel->setColor(ccWHITE); 
	pLabel->setFontSize(18);

	CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
	pBox->setAnchorPoint(CCPointZero);
	pBox->setTag(tag);
	pBox->setHandler(this,menu_selector(SettingProtectPanel::openprocallback));
	pBox->setPosition(CCPointZero);
	pMenu->addChild(pBox);
	if (m_setData[realtag].m_open)
	{
		pBox->setChecked(true);
	}


	CCMenuItemImage* pItem1=SystemData::getScale9MenuItemImageByPlist("ui_setting_protect_item"); 
	pItem1->setAnchorPoint(ccp(0,0.5));
	pItem1->setPosition(ccp(pBox->getPositionX()+pBox->getContentSize().width+5,pBox->getPositionY()+pBox->getContentSize().height/2));
	pItem1->setTarget(this,menu_selector(SettingProtectPanel::changelifecallback));
	pItem1->setTag(tag);
	pMenu->addChild(pItem1);
	CCLabelTTF* pValue1=CCLabelTTF::create(SystemData::intToString(m_setData[realtag].m_life).c_str(),"",16);
	pValue1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
	pValue1->setTag(LabelValue);
	pItem1->addChild(pValue1);

	CCLabelTTF* pLabel1=SystemData::getLabelTTF("ui_setting_protect_shiyong");
	pLabel1->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel1->setColor(ccWHITE);
	pLabel1->setFontSize(18);
	pLabel1->setAnchorPoint(ccp(0,0.5));
	pLabel1->setPosition(ccp(pItem1->getPositionX()+pItem1->getContentSize().width+5,pItem1->getPositionY()));
	pMenu->addChild(pLabel1);

	CPComboBox* pComboBox=LayoutData::getComboBox(CPModuleName::COMMON, "normal");
	for (int i=1;i<=SystemData::getLayoutValue(sizestr);i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString(itemstr).c_str(),i);
		int sid = SystemData::getLayoutValue(pStr->getCString());
		std::string name;
		LuaData::getProp(LuaData::ITEM,sid,"name",name);
		pComboBox->addLabelItem(name.c_str(),sid);
		pComboBox->setDirection(ComboBoxOpenType::open_Up);
		pComboBox->setChangeHandler(this,callfuncN_selector(SettingProtectPanel::changeitem));
		pComboBox->setTag(tag);
	} 
	pComboBox->setChangeHandler_(this,callfuncN_selector(SettingProtectPanel::clickboxitem));
	pComboBox->setCurrentIndex(m_setData[realtag].m_itemSid);
	pComboBox->setAnchorPoint(ccp(0,0.5));
	pComboBox->setPosition(ccp(pLabel1->getPositionX()+pLabel1->getContentSize().width+5,pLabel1->getPositionY()));
	pMenu->addChild(pComboBox);

	if (tag!=Home_Set && tag!=Item_Endure ) 
	{
		CCLabelTTF* pLabel2=SystemData::getLabelTTF("ui_setting_protect_jiange");
		pLabel2->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel2->setColor(ccWHITE);
		pLabel2->setFontSize(18);
		pLabel2->setAnchorPoint(ccp(0,0.5));
		pLabel2->setPosition(ccp(pComboBox->getPositionX()+pComboBox->getContentSize().width+5,pComboBox->getPositionY()));
		pMenu->addChild(pLabel2);

		CCMenuItemImage* pItem2=SystemData::getScale9MenuItemImageByPlist("ui_setting_protect_item");
		pItem2->setTarget(this,menu_selector(SettingProtectPanel::changesecondscallback));
		pItem2->setTag(tag);
		pItem2->setAnchorPoint(ccp(0,0.5));
		pItem2->setPosition(ccp(pLabel2->getPositionX()+pLabel2->getContentSize().width+5,pLabel2->getPositionY()));
		pMenu->addChild(pItem2);
		CCLabelTTF* pValue2=CCLabelTTF::create(SystemData::intToString(m_setData[realtag].m_seconds).c_str(),"",16);
		pValue2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
		pValue2->setTag(LabelValue);
		pItem2->addChild(pValue2);

		CCLabelTTF* pLabel3=SystemData::getLabelTTF("ui_setting_protect_miao");
		pLabel3->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel3->setColor(ccWHITE);
		pLabel3->setFontSize(18);
		pLabel3->setAnchorPoint(ccp(0,0.5));
		pLabel3->setPosition(ccp(pItem2->getPositionX()+pItem2->getContentSize().width+5,pItem2->getPositionY()));
		pMenu->addChild(pLabel3);
	}
	return pLayer;
}

void SettingProtectPanel::changelifecallback( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		int realtag = taglist[tag];
		m_CurNode=pNode;
		Game::getGameUI()->showNumberBoard(&m_setData[realtag].m_life,100,EventProtocol::EVENT_PUTIN_OVER_Life,1);
	}
}

void SettingProtectPanel::changesecondscallback( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		int realtag = taglist[tag];
		m_CurNode=pNode;
		Game::getGameUI()->showNumberBoard(&m_setData[realtag].m_seconds,100,EventProtocol::EVENT_PUTIN_OVER_Seconds,1);
	}
}

void SettingProtectPanel::openprocallback( CCObject* pSender )
{
	CPCheckBox* pNode=(CPCheckBox*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		int realtag = taglist[tag];
		m_setData[realtag].m_open=pNode->isChecked();
		saveUserDate(); 
		if (m_setData[realtag].m_open)
		{
			CPUpdateFunctorManager::instance()->addFunctor(realtag);
		}
		else
		{
			CPUpdateFunctorManager::instance()->rmvFunctor(realtag);
		}
	}
}

void SettingProtectPanel::saveUserDate()
{
	for (int i=0;i<MyEnum_Max;i++)
	{
		std::string strsr=CPUserData::UPDATE_FUNCTOR_ID+SystemData::intToString(taglist[i])+ "_";	
		UserData::setIntData(HeroData::getPID(),strsr,1,m_setData[taglist[i]].m_open);
		UserData::setIntData(HeroData::getPID(),strsr,2,m_setData[taglist[i]].m_seconds);
		UserData::setIntData(HeroData::getPID(),strsr,3,m_setData[taglist[i]].m_life);
		UserData::setIntData(HeroData::getPID(),strsr,4,m_setData[taglist[i]].m_itemSid);
	}
}

void SettingProtectPanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_PUTIN_OVER_Seconds)
	{
		if (m_CurNode)
		{
			int tag=m_CurNode->getTag();
			if (m_CurNode->getChildByTag(LabelValue))
			{
				CCLabelTTF* p=(CCLabelTTF*)(m_CurNode->getChildByTag(LabelValue));
				int realtag = taglist[tag];
				p->setString(SystemData::intToString(m_setData[realtag].m_seconds).c_str());
				ICPUpdateFunctor *func = CPUpdateFunctorManager::instance()->getFunctor(realtag);
				if (func)
				{
					func->setInterval(m_setData[realtag].m_seconds);
				}
				saveUserDate();
				UserData::saveData();
			}
		}
	}
	else if (channel == EventProtocol::EVENT_PUTIN_OVER_Life)
	{
		if (m_CurNode)
		{
			int tag=m_CurNode->getTag();
			if (m_CurNode->getChildByTag(LabelValue))
			{
				CCLabelTTF* p=(CCLabelTTF*)(m_CurNode->getChildByTag(LabelValue));
				int realtag = taglist[tag];
				p->setString(SystemData::intToString(m_setData[realtag].m_life).c_str());
				saveUserDate();
				UserData::saveData();
			}
		}
	}
}

CCLayer* SettingProtectPanel::getSSSpecial()
{
	CCLayer* pLayer=CCLayer::create();
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	pLayer->addChild(pMenu);

	int tag = SS_Special;

	std::string text1="ui_setting_protect_zidongbuxue";
	std::string sizestr="ui_setting_protect_endure_item_size";
	std::string itemstr="ui_setting_protect_endure_item";

	int realtag = taglist[tag];

	CCLabelTTF* pLabel=SystemData::getLabelTTF(text1.c_str());
	pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel->setColor(ccWHITE); 
	pLabel->setFontSize(18);

	CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
	pBox->setAnchorPoint(CCPointZero);
	pBox->setTag(tag);
	pBox->setHandler(this,menu_selector(SettingProtectPanel::openprocallback));
	pBox->setPosition(CCPointZero);
	pMenu->addChild(pBox);
	if (m_setData[realtag].m_open)
	{
		pBox->setChecked(true);
	}
	CCLabelTTF* pLabel1=SystemData::getLabelTTF("ui_setting_protect_hp_text");
	pLabel1->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel1->setColor(ccWHITE);
	pLabel1->setFontSize(18);
	pLabel1->setAnchorPoint(ccp(0,0.5));
	pLabel1->setPosition(ccp(pBox->getPositionX()+pBox->getContentSize().width+5,pBox->getPositionY()+pBox->getContentSize().height/2));
	pMenu->addChild(pLabel1);

	CCMenuItemImage* pItem1=SystemData::getScale9MenuItemImageByPlist("ui_setting_protect_item"); 
	pItem1->setTarget(this,menu_selector(SettingProtectPanel::changelifecallback));
	pItem1->setTag(tag);
	pItem1->setAnchorPoint(ccp(0,0.5));
	pItem1->setPosition(ccp(pLabel1->getPositionX()+pLabel1->getContentSize().width+5,pLabel1->getPositionY()));
	pMenu->addChild(pItem1);
	CCLabelTTF* pValue1=CCLabelTTF::create(SystemData::intToString(m_setData[realtag].m_life).c_str(),"",16);
	pValue1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
	pValue1->setTag(LabelValue);
	pItem1->addChild(pValue1);

	CCLabelTTF* pLabel2=SystemData::getLabelTTF("ui_setting_protect_shiyonghuifushu");
	pLabel2->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel2->setColor(ccWHITE);
	pLabel2->setFontSize(18);
	pLabel2->setAnchorPoint(ccp(0,0.5));
	pLabel2->setPosition(ccp(pItem1->getPositionX()+pItem1->getContentSize().width+5,pItem1->getPositionY()));
	pMenu->addChild(pLabel2);

	CCMenuItemImage* pItem2=SystemData::getScale9MenuItemImageByPlist("ui_setting_protect_item");
	pItem2->setTarget(this,menu_selector(SettingProtectPanel::changesecondscallback));
	pItem2->setTag(tag);
	pItem2->setAnchorPoint(ccp(0,0.5));
	pItem2->setPosition(ccp(pLabel2->getPositionX()+pLabel2->getContentSize().width+5,pLabel2->getPositionY()));
	pMenu->addChild(pItem2);
	CCLabelTTF* pValue2=CCLabelTTF::create(SystemData::intToString(m_setData[realtag].m_seconds).c_str(),"",16);
	pValue2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
	pValue2->setTag(LabelValue);
	pItem2->addChild(pValue2);

	CCLabelTTF* pLabel3=SystemData::getLabelTTF("ui_setting_protect_miao");
	pLabel3->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel3->setColor(ccWHITE);
	pLabel3->setFontSize(18);
	pLabel3->setAnchorPoint(ccp(0,0.5));
	pLabel3->setPosition(ccp(pItem2->getPositionX()+pItem2->getContentSize().width+5,pItem2->getPositionY()));
	pMenu->addChild(pLabel3);

	return pLayer;
}

void SettingProtectPanel::changeitem( CCNode* pNode )
{
	CPComboBox* pComboBox = dynamic_cast<CPComboBox*>(pNode);
	if (pComboBox)
	{
		int tag = pComboBox->getCurrentIndex();
		m_setData[ taglist[m_iCurClickBoxID]].m_itemSid = tag;
		saveUserDate();
	}
}

void SettingProtectPanel::clickboxitem(  CCNode* pNode )
{
	if (pNode)
	{
		int tag = pNode->getTag();
		m_iCurClickBoxID = tag;
	}
}
