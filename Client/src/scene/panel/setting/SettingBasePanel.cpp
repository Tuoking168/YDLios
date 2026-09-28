#include "SettingBasePanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"
#include "module/UserDataModule.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "userdata/HeroData.h"
#include "userdata/FuncData.h"

SettingBasePanel::SettingBasePanel( void ):
	m_pLeftMenu(NULL)
{

}

SettingBasePanel::~SettingBasePanel( void )
{

}

bool SettingBasePanel::init()
{
	//×ó±ß
	CCScale9Sprite* pleftborder2=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_base_border2.w"),SystemData::getLayoutValue("ui_setting_base_border2.h"));
	pleftborder2->setAnchorPoint(CCPointZero);
	pleftborder2->setPosition(SystemData::getLayoutPoint("ui_setting_base_left_text"));
	addChild(pleftborder2);

	CCScale9Sprite* pleftborder1=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_base_border1.w"),SystemData::getLayoutValue("ui_setting_base_border1.h"));
	pleftborder1->setAnchorPoint(CCPointZero);
	pleftborder1->setPosition(ccp(pleftborder2->getPositionX(),pleftborder2->getPositionY()+pleftborder2->getContentSize().height));
	addChild(pleftborder1);

	CCLabelTTF* pleftlabel=SystemData::getLabelTTF("ui_setting_base_left_text");
	pleftlabel->setColor(ccWHITE);
	pleftlabel->setFontSize(18);
	pleftlabel->setPosition(ccp(pleftborder1->getContentSize().width/2,pleftborder1->getContentSize().height/2));
	pleftborder1->addChild(pleftlabel);

	initLeftPanel();

	//you±ß
	CCScale9Sprite* prightborder2=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_base_border2.w"),SystemData::getLayoutValue("ui_setting_base_border2.h"));
	prightborder2->setAnchorPoint(CCPointZero);
	prightborder2->setPosition(SystemData::getLayoutPoint("ui_setting_base_right_text"));
	addChild(prightborder2);

	CCScale9Sprite* prightborder1=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_base_border1.w"),SystemData::getLayoutValue("ui_setting_base_border1.h"));
	prightborder1->setAnchorPoint(CCPointZero);
	prightborder1->setPosition(ccp(prightborder2->getPositionX(),prightborder2->getPositionY()+prightborder2->getContentSize().height));
	addChild(prightborder1);

	CCLabelTTF* prightlabel=SystemData::getLabelTTF("ui_setting_base_right_text");
	prightlabel->setColor(ccWHITE);
	prightlabel->setFontSize(18);
	prightlabel->setPosition(ccp(prightborder1->getContentSize().width/2,prightborder1->getContentSize().height/2));
	prightborder1->addChild(prightlabel);

	initrightPanel();

	return true;
}

void SettingBasePanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{
		case 1:
			UserData::setIntData(HeroData::getPID(),CPUserData::SHOW_MONSTERNAME,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_MONSTERNAME));
			break;
		case 2:
			UserData::setIntData(HeroData::getPID(),CPUserData::SHOW_ITEMNAME,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_ITEMNAME));
			break;
		case 3:
			UserData::setIntData(HeroData::getPID(),CPUserData::CONTROL_OFF,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::CONTROL_OFF));
			Game::getGameUI()->initControlPanel();
			break;
		case 4:
			UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_SETTING,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_SETTING));
			initHideSetting();
			break;
		case 5:
			UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_PET,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_PET));
			break;
		case 6:
			UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_DOG,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_DOG));
			break;
		case 7:
			UserData::setIntData(HeroData::getPID(),CPUserData::SHOW_MY_GUILD_PLAYER,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_MY_GUILD_PLAYER));
			break;
		case 8:
			UserData::setIntData(HeroData::getPID(),CPUserData::SHOW_MY_SOCIAL_PLAYER,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_MY_SOCIAL_PLAYER));
			break;
		case 9:
			UserData::setIntData(HeroData::getPID(),CPUserData::USE_DEFAULT_EQUIP,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::USE_DEFAULT_EQUIP));
			break;
		case 10:
			UserData::setIntData(HeroData::getPID(),CPUserData::NPC_DEFAULT_EQUIP,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::NPC_DEFAULT_EQUIP));
			break;
		case 11:
			AudioLoader::setSilent(!AudioLoader::isSilent());
			UserData::setIntData(CPUserData::BGM_OFF,AudioLoader::isSilent());
			break;
		case 12:
			AudioLoader::setEffectSilent(!AudioLoader::isEffectSilent());
			UserData::setIntData(CPUserData::EFFECT_OFF,AudioLoader::isEffectSilent());
			break;
		case 13:
			FuncData::sendFuncMsgWithID(2,Entity::attr_refuse_addfriend,!HeroData::getProp(Entity::attr_refuse_addfriend));
			break;
		case 14:
			FuncData::sendFuncMsgWithID(2,Entity::attr_refuse_trade,!HeroData::getProp(Entity::attr_refuse_trade));
			break;
		case 15:
			UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_WING,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_WING));
			break;
		case 16:
			UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_HEADNAME,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_HEADNAME));
			break;
		case 17:
			UserData::setIntData(HeroData::getPID(),CPUserData::SHOW_BAGWARM,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_BAGWARM));
			break;
		case 18:
			UserData::setIntData(HeroData::getPID(),CPUserData::BEATTACK_EFFECT_OFF,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::BEATTACK_EFFECT_OFF));
			break;
		default:
			break;
		}
		UserData::saveData();
	}
}

void SettingBasePanel::initLeftPanel() 
{
	if (m_pLeftMenu)
	{
		CCArray* pChildren = m_pLeftMenu->getChildren();
		CCObject* pObject;
		CCARRAY_FOREACH(pChildren,pObject)
		{
			CCNode* p = dynamic_cast<CCNode*>(pObject);

		}
	}
	m_pLeftMenu=GeneralMenu::create();
	m_pLeftMenu->setAnchorPoint(CCPointZero);
	m_pLeftMenu->setPosition(CCPointZero);
	addChild(m_pLeftMenu);
	CCPoint pos=SystemData::getLayoutPoint("ui_setting_base_left_select");
	for (int i=1;i<=SystemData::getLayoutValue("ui_setting_base_left_label_size");i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("ui_setting_base_left_label").c_str(),i);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(pStr->getCString());
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setDimensions(CCSizeMake(275,0));
		CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
		pBox->setAnchorPoint(CCPointZero);
		pBox->setTag(i);
		pBox->setHandler(this,menu_selector(SettingBasePanel::menucallback));
		pBox->setPosition(ccp(pos.x,pos.y-(i-1)*40));
		m_pLeftMenu->addChild(pBox);

		if (i>4 && !UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_SETTING))
		{
			pLabel->setColor(ccGRAY);
			pBox->setEnable(false);
		}
		if (i>4)
		{
			pLabel->setFontSize(14);
			pBox->setPosition(ccp(pos.x+20,pos.y-(i-1)*39));
		}

		switch (i)
		{
		case 1:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_MONSTERNAME));
			break;
		case 2:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_ITEMNAME));
			break;
		case 3:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::CONTROL_OFF));
			break;
		case 4:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_SETTING));
			break;
		case 5:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_PET));
			break;
		case 6:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_DOG));
			break;
		case 7:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_MY_GUILD_PLAYER));
			break;
		case 8:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_MY_SOCIAL_PLAYER));
			break;
		case 9:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::USE_DEFAULT_EQUIP));
			break;
		case 10:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::NPC_DEFAULT_EQUIP));
			break;
			
		default:
			break;
		}
	}
}

void SettingBasePanel::initrightPanel()
{
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCPoint pos=SystemData::getLayoutPoint("ui_setting_base_right_select");
	for (int i=1;i<=SystemData::getLayoutValue("ui_setting_base_right_label_size");i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("ui_setting_base_right_label").c_str(),i);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(pStr->getCString());
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setDimensions(CCSizeMake(275,0));
		CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
		pBox->setAnchorPoint(CCPointZero);
		pBox->setTag(i+10);
		pBox->setHandler(this,menu_selector(SettingBasePanel::menucallback));
		pBox->setPosition(ccp(pos.x,pos.y-(i-1)*45));
		pMenu->addChild(pBox);

		switch (i)
		{
		case 1:
			pBox->setChecked(UserData::getIntData(CPUserData::BGM_OFF));
			break;
		case 2:
			pBox->setChecked(UserData::getIntData(CPUserData::EFFECT_OFF));
			break;
		case 3:
			pBox->setChecked(HeroData::getProp(Entity::attr_refuse_addfriend));
			break;
		case 4:
			pBox->setChecked(HeroData::getProp(Entity::attr_refuse_trade));
			break;
		case 5:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_WING));
			break;
		case 6:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_HEADNAME));
			break;
		case 7:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::SHOW_BAGWARM));
			break;
		case 8:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::BEATTACK_EFFECT_OFF));
			break;
		default:
			break;
		}
	} 
}

void SettingBasePanel::onEnter()
{
	BasePanel::onEnter();
}

void SettingBasePanel::onExit()
{
	UserData::saveData();
	BasePanel::onExit();
}

void SettingBasePanel::initHideSetting()
{
	if (m_pLeftMenu)
	{
		for (int i = 4;i<=SystemData::getLayoutValue("ui_setting_base_left_label_size");i++)
		{
			CPCheckBox* pBox = dynamic_cast<CPCheckBox*>(m_pLeftMenu->getChildByTag(i));
			if (i>4 && !UserData::getIntData(HeroData::getPID(),CPUserData::HIDE_SETTING))
			{
				pBox->getLabel()->setColor(ccGRAY);
				pBox->setEnable(false);
				if (i==5)
				{
					UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_PET,false);
				}
				else if (i==6)
				{
					UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_DOG,false);
				}
				else if (i==7)
				{
					UserData::setIntData(HeroData::getPID(),CPUserData::SHOW_MY_GUILD_PLAYER,false);
				}
				else if (i==8)
				{
					UserData::setIntData(HeroData::getPID(),CPUserData::SHOW_MY_SOCIAL_PLAYER,false);
				}
				else if (i==9)
				{
					UserData::setIntData(HeroData::getPID(),CPUserData::USE_DEFAULT_EQUIP,false);
				}
				else if (i==10)
				{
					UserData::setIntData(HeroData::getPID(),CPUserData::NPC_DEFAULT_EQUIP,false);
				}
				pBox->setChecked(false);
			}
			else
			{
				pBox->getLabel()->setColor(ccWHITE);
				pBox->setEnable(true);
				int n = FuncData::checkNowMemory();
				if (n==1)
				{
					if (i==5 )
					{
						UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_PET,true);
						pBox->setChecked(true);
					}
					else if (i==6 )
					{
						UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_DOG,true);
						pBox->setChecked(true);
					}
					else if (i==10)
					{
						UserData::setIntData(HeroData::getPID(),CPUserData::NPC_DEFAULT_EQUIP,true);
						pBox->setChecked(true);
					}
				}
				else if (n==2)
				{
					if (i==5 )
					{
						UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_PET,true);
						pBox->setChecked(true);
					}
					else if (i==6 )
					{
						UserData::setIntData(HeroData::getPID(),CPUserData::HIDE_DOG,true);
						pBox->setChecked(true);
					}
					else if (i==9)
					{
						UserData::setIntData(HeroData::getPID(),CPUserData::USE_DEFAULT_EQUIP,true);
						pBox->setChecked(true);
					}
					else if (i==10)
					{
						UserData::setIntData(HeroData::getPID(),CPUserData::NPC_DEFAULT_EQUIP,true);
						pBox->setChecked(true);
					}
				}
			}
		}
	}
}
