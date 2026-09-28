#include "SettingTakePanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"
#include "module/UserDataModule.h"
#include "userdata/HeroData.h"
#include "MsgPet.h"
#include "network/HandleMessage.h"

SettingTakePanel::SettingTakePanel( void )
{

}

SettingTakePanel::~SettingTakePanel( void )
{

}

SettingTakePanel* SettingTakePanel::create()
{
	SettingTakePanel* pPanel = new SettingTakePanel();
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

bool SettingTakePanel::init()
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

	CCLabelTTF* pleftlabel=SystemData::getLabelTTF("ui_setting_take_left_text");
	pleftlabel->setColor(ccWHITE);
	pleftlabel->setFontSize(18);
	pleftlabel->setPosition(ccp(pleftborder1->getContentSize().width/2,pleftborder1->getContentSize().height/2));
	pleftborder1->addChild(pleftlabel);

	initLeftPanel();

	//you±ß
	CCScale9Sprite* prightborder2=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_take_border2.w"),SystemData::getLayoutValue("ui_setting_take_border2.h"));
	prightborder2->setAnchorPoint(CCPointZero);
	prightborder2->setPosition(SystemData::getLayoutPoint("ui_setting_base_right_text"));
	addChild(prightborder2);

	CCScale9Sprite* prightborder1=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_take_border1.w"),SystemData::getLayoutValue("ui_setting_take_border1.h"));
	prightborder1->setAnchorPoint(CCPointZero);
	prightborder1->setPosition(ccp(prightborder2->getPositionX(),prightborder2->getPositionY()+prightborder2->getContentSize().height));
	addChild(prightborder1);

	CCLabelTTF* prightlabel=SystemData::getLabelTTF("ui_setting_take_right_text2");
	prightlabel->setColor(ccWHITE);
	prightlabel->setFontSize(18);
	prightlabel->setPosition(ccp(prightborder1->getContentSize().width/2,prightborder1->getContentSize().height/2));
	prightborder1->addChild(prightlabel);


	CCScale9Sprite* prightborder4=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_take_border4.w"),SystemData::getLayoutValue("ui_setting_take_border4.h"));
	prightborder4->setAnchorPoint(CCPointZero);
	prightborder4->setPosition(ccp(prightborder1->getPositionX(),prightborder1->getPositionY()+prightborder1->getContentSize().height));
	addChild(prightborder4);

	CCScale9Sprite* prightborder3=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_take_border3.w"),SystemData::getLayoutValue("ui_setting_take_border3.h"));
	prightborder3->setAnchorPoint(CCPointZero);
	prightborder3->setPosition(ccp(prightborder4->getPositionX(),prightborder4->getPositionY()+prightborder4->getContentSize().height));
	addChild(prightborder3);

	CCLabelTTF* prightlabel2=SystemData::getLabelTTF("ui_setting_take_right_text1");
	prightlabel2->setColor(ccWHITE);
	prightlabel2->setFontSize(18);
	prightlabel2->setPosition(ccp(prightborder3->getContentSize().width/2,prightborder3->getContentSize().height/2));
	prightborder3->addChild(prightlabel2);

	initright1Panel();
	initright2Panel();

	return true;
}

void SettingTakePanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{
		case 1:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_1_35_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_1_35_ON));
			break;
		case 2:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_35_40_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_35_40_ON));
			break;
		case 3:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_40_45_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_40_45_ON));
			break;
		case 4:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_45_50_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_45_50_ON));
			break;
		case 5:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_50_55_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_50_55_ON));
			break;
		case 6:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_55__ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_55__ON));
			break;
		case 7:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_CAILIAO_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_CAILIAO_ON));
			break;
		case 8:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_SHIYONG_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_SHIYONG_ON));
			break;
		case 9:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_PICKMONEY_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_PICKMONEY_ON));
			break;
		case 11:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_CHIXUYAO_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_CHIXUYAO_ON));
			break;
		case 12:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_SHUNHUIYAO_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_SHUNHUIYAO_ON));
			break;
		case 21:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_AUTOPICK_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_AUTOPICK_ON));
			break;
		case 22:
			UserData::setIntData(HeroData::getPID(),CPUserData::PICKITEM_TIPS_ON,!(bool)UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_TIPS_ON));
			break;
		default:
			break;
		}
		UserData::saveData();
	}
}

void SettingTakePanel::initLeftPanel()
{
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCPoint pos=SystemData::getLayoutPoint("ui_setting_take_left_select");
	for (int i=0;i<SystemData::getLayoutValue("ui_setting_take_left_label_size");i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("ui_setting_take_left_label").c_str(),i+1);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(pStr->getCString());
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setDimensions(CCSizeMake(275,0));
		CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
		pBox->setAnchorPoint(CCPointZero);
		pBox->setTag(i+1);
		pBox->setHandler(this,menu_selector(SettingTakePanel::menucallback));
		pBox->setPosition(ccp(pos.x+(i/6)*175,pos.y-(i%6)*45));
		pMenu->addChild(pBox); 

		switch (i)
		{
		case 0:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_1_35_ON));
			break;
		case 1:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_35_40_ON));
			break;
		case 2:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_40_45_ON));
			break;
		case 3:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_45_50_ON));
			break;
		case 4:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_50_55_ON));
			break;
		case 5:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_55__ON));
			break;
		case 6:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_CAILIAO_ON));
			break;
		case 7:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_SHIYONG_ON));
			break;
		case 8:
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_PICKMONEY_ON));
			break;
		default:
			break;
		}
	}
}

void SettingTakePanel::initright1Panel()
{
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCPoint pos=SystemData::getLayoutPoint("ui_setting_take_right1_select");
	for (int i=1;i<=SystemData::getLayoutValue("ui_setting_take_right1_label_size");i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("ui_setting_take_right1_label").c_str(),i);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(pStr->getCString());
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setDimensions(CCSizeMake(275,0));
		CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
		pBox->setAnchorPoint(CCPointZero);
		pBox->setTag(i+10);
		pBox->setHandler(this,menu_selector(SettingTakePanel::menucallback));
		pBox->setPosition(ccp(pos.x,pos.y-(i-1)*45));
		pMenu->addChild(pBox);

		if (i==1)
		{
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_CHIXUYAO_ON));
		}
		else if (i==2)
		{
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_SHUNHUIYAO_ON));
		}
	} 
}

void SettingTakePanel::initright2Panel()
{
	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCPoint pos=SystemData::getLayoutPoint("ui_setting_take_right2_select");
	for (int i=1;i<=SystemData::getLayoutValue("ui_setting_take_right2_label_size");i++)
	{
		CCString* pStr=CCString::createWithFormat(SystemData::getLayoutString("ui_setting_take_right2_label").c_str(),i);
		CCLabelTTF* pLabel=SystemData::getLabelTTF(pStr->getCString());
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setDimensions(CCSizeMake(275,0));
		CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
		pBox->setAnchorPoint(CCPointZero);
		pBox->setTag(i+20);
		pBox->setHandler(this,menu_selector(SettingTakePanel::menucallback));
		pBox->setPosition(ccp(pos.x,pos.y-(i-1)*45));
		pMenu->addChild(pBox);


		if (i==1)
		{
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_AUTOPICK_ON));
		}
		else if (i==2)
		{
			pBox->setChecked(UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_TIPS_ON));
		}
	} 
}


void SettingTakePanel::onEnter()
{
	BasePanel::onEnter();
}

void SettingTakePanel::onExit()
{
	sendmsgToServer();
	UserData::saveData();
	BasePanel::onExit();
}

void SettingTakePanel::sendmsgToServer()
{
	std::string takeArray[11] = {CPUserData::PICKITEM_1_35_ON,CPUserData::PICKITEM_35_40_ON,CPUserData::PICKITEM_40_45_ON,CPUserData::PICKITEM_45_50_ON,CPUserData::PICKITEM_50_55_ON,CPUserData::PICKITEM_55__ON,CPUserData::PICKITEM_CAILIAO_ON,CPUserData::PICKITEM_SHIYONG_ON,CPUserData::PICKITEM_CHIXUYAO_ON,CPUserData::PICKITEM_SHUNHUIYAO_ON,CPUserData::PICKITEM_PICKMONEY_ON};
	int statevalue = 0;
	for (int i = 0;i<11;i++)
	{
		int value = UserData::getIntData(HeroData::getPID(),takeArray[i]);
		statevalue += value<<i;
	}
	MsgSetPetPickSettingRequest* msg = new MsgSetPetPickSettingRequest;
	msg->state = statevalue;
	HandleMessage::sendMessage(msg);
}
