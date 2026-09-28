#include "HorsePanel.h"
#include "HorseAttributePanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "network/HandleMessage.h"
#include "MsgItem.h"
#include "MsgPet.h"
#include "userdata/netdata/NetItem.h"
#include "ActivityModule.h"

#include "userdata/netdata/HeroModel.h"
#include "event/EventProtocol.h"
#include "userdata/netdata/HeroModel.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "ext/GeneralMenu.h"
#include "userdata/UserPetData.h"

#include "script/LuaWrapper.h"
#include "CommonPanel.h"
#include "userdata/luadata/LuaData.h"
#include "EntityDefinition.h"
#include "ext/CCFlashAnimation.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"
#include "event/CPEventHelper.h"
#include "utils/TestUtils.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "event/CPEventDispatcher.h"
#include "scene/panel/functionPanel/PetAttributePanel.h"
#include "controls/CPItemComponents.h"


HorsePanel::HorsePanel():
	m_pList(NULL),
	m_pMainMenu(NULL),
	m_pEquipMenu(NULL),
	m_pVcoinLabel(NULL),
	//m_pHonorLabel(NULL),
	m_pMabianCnt(NULL),
	m_bIsInitOver(false),
	m_pHorseStateLabel(NULL),
	m_pExppoint(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

HorsePanel::~HorsePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool HorsePanel::init()
{
	CCScale9Sprite* panel=SystemData::getScale9SpriteByPlist("ui_horse_panel");
	panel->setAnchorPoint(CCPointZero);
	panel->setPosition(SystemData::getLayoutPoint("ui_horse_panel_pos")); 
	addChild(panel);

	// 坐骑站的平台
	CCScale9Sprite *bkg=SystemData::getScale9SpriteByPlist("ui_horse_stage");
	bkg->setPosition(SystemData::getLayoutPoint("ui_horse_stage_pos"));
	addChild(bkg);

	m_nWidth=panel->getContentSize().width;
	m_nHeight=panel->getContentSize().height;
	addCover();//保证点击事件

	m_pMainMenu=GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	// 装备Menu
	m_pEquipMenu=GeneralMenu::create();
	m_pEquipMenu->setPosition(CCPointZero);
	m_pEquipMenu->setAnchorPoint(CCPointZero);
	addChild(m_pEquipMenu);
	
	initHorseEquip();


	// 上马
	CCMenuItemImage* pBtnSM=SystemData::getScale9MenuItemImageByPlist("ui_horse_btn");
	pBtnSM->setPosition(SystemData::getLayoutPoint("ui_horse_btn_sm_pos"));
	pBtnSM->setTag(HORSE_RideHorse);
	pBtnSM->setTarget(this,menu_selector(HorsePanel::MenuShangmaCallBack));
	m_pMainMenu->addChild(pBtnSM);
	CCLabelTTF* pLblSM=SystemData::getLabelTTF("ui_horse_lbl_sm");
	pLblSM->setFontSize(20);
	pLblSM->setColor(ccWHITE);
	pLblSM->setPosition(ccp(pBtnSM->getContentSize().width/2, pBtnSM->getContentSize().height/2));
	pBtnSM->addChild(pLblSM);

	// 下马
	CCMenuItemImage* pBtnXM=SystemData::getScale9MenuItemImageByPlist("ui_horse_btn");
	pBtnXM->setPosition(SystemData::getLayoutPoint("ui_horse_btn_sm_pos"));
	pBtnXM->setTag(HORSE_XiaMa);
	pBtnXM->setTarget(this,menu_selector(HorsePanel::MenuXiamaCallBack));
	m_pMainMenu->addChild(pBtnXM);
	CCLabelTTF* pLblXM=SystemData::getLabelTTF("ui_horse_lbl_xm");
	pLblXM->setFontSize(20);
	pLblXM->setColor(ccWHITE);
	pLblXM->setPosition(ccp(pBtnXM->getContentSize().width/2, pBtnXM->getContentSize().height/2));
	pBtnXM->addChild(pLblXM);
	pBtnXM->setVisible(false);

	// 荣誉培养
	CCMenuItemImage* pBtnRYPY=SystemData::getScale9MenuItemImageByPlist("ui_horse_btn");
	pBtnRYPY->setPosition(SystemData::getLayoutPoint("ui_horse_btn_addexp1_pos"));
	pBtnRYPY->setTag(HORSE_AddExpOnce);
	pBtnRYPY->setTarget(this,menu_selector(HorsePanel::MenuPeiYangCallBack));
	m_pMainMenu->addChild(pBtnRYPY);
	CCLabelTTF* pLblRYPY=SystemData::getLabelTTF("ui_horse_lbl_addexp1");
	pLblRYPY->setFontSize(20);
	pLblRYPY->setColor(ccWHITE);
	pLblRYPY->setPosition(ccp(pBtnRYPY->getContentSize().width/2, pBtnRYPY->getContentSize().height/2));
	pBtnRYPY->addChild(pLblRYPY);

	// 元宝培养
	CCMenuItemImage* pBtnYBPY=SystemData::getScale9MenuItemImageByPlist("ui_horse_btn");
	pBtnYBPY->setPosition(SystemData::getLayoutPoint("ui_horse_btn_addexp10_pos"));
	pBtnYBPY->setTag(HORSE_AddExp10);
	pBtnYBPY->setTarget(this,menu_selector(HorsePanel::MenuPeiYangCallBack));
	m_pMainMenu->addChild(pBtnYBPY);
	CCLabelTTF* pLblYBPY=SystemData::getLabelTTF("ui_horse_lbl_addexp10");
	pLblYBPY->setFontSize(20);
	pLblYBPY->setColor(ccWHITE);
	pLblYBPY->setPosition(ccp(pBtnYBPY->getContentSize().width/2,pBtnYBPY->getContentSize().height/2));
	pBtnYBPY->addChild(pLblYBPY);

	//一键升级
	CCMenuItemImage* pBtnOneKeyUp=SystemData::getScale9MenuItemImageByPlist("ui_horse_btn");
	pBtnOneKeyUp->setPosition(SystemData::getLayoutPoint("ui_horse_btn_addexp50_pos"));
	pBtnOneKeyUp->setTag(HORSE_AddExp50);
	pBtnOneKeyUp->setTarget(this,menu_selector(HorsePanel::MenuPeiYangCallBack));
	m_pMainMenu->addChild(pBtnOneKeyUp);
	CCLabelTTF* pLblOneKeyUp=SystemData::getLabelTTF("ui_horse_lbl_addexp50");
	pLblOneKeyUp->setFontSize(20);
	pLblOneKeyUp->setColor(ccWHITE);
	pLblOneKeyUp->setPosition(ccp(pBtnOneKeyUp->getContentSize().width/2,pBtnOneKeyUp->getContentSize().height/2));
	pBtnOneKeyUp->addChild(pLblOneKeyUp);



	//项圈个数
	CCLabelTTF* plabelXiangquan = SystemData::getLabelTTF("ui_horse_mabian");
	plabelXiangquan->setFontSize(14);
	plabelXiangquan->setColor(ccYELLOW);
	plabelXiangquan->setPosition(SystemData::getLayoutPoint("ui_horse_mabian_pos"));
	m_pMainMenu->addChild(plabelXiangquan);
	m_pMabianCnt=CCLabelTTF::create(" ","Times New Roman",14);
	int mabiancnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("mabian_id"),ItemPos::Player_Bag_Start);
	m_pMabianCnt->setString(SystemData::intToString(mabiancnt).c_str());
	m_pMabianCnt->setAnchorPoint(ccp(0,0.5));
	m_pMabianCnt->setPosition(SystemData::getLayoutPoint("ui_horse_mabian_cnt_pos"));
	addChild(m_pMabianCnt); 

	//// 荣誉
	//CCSprite* pSprite_rongyu=SystemData::getSpriteByPlist("ui_horse_rongyu");
	//pSprite_rongyu->setPosition(SystemData::getLayoutPoint("ui_horse_rongyu_pos"));
	//pSprite_rongyu->setAnchorPoint(CCPointZero);
	//addChild(pSprite_rongyu);
	//m_pHonorLabel=CCLabelTTF::create(" ","Times New Roman",14);
	//m_pHonorLabel->setAnchorPoint(CCPointZero);
	//m_pHonorLabel->setPosition(SystemData::getLayoutPoint("ui_horse_rongyu_cnt_pos"));
	//addChild(m_pHonorLabel);
	//m_pHonorLabel->setString(SystemData::intToString(GameData::s_user->m_pMainRole->Honour).c_str());

	// 元宝
	CCSprite* pSprite_yuanbao=SystemData::getSpriteByPlist("ui_horse_yuanbao");
	pSprite_yuanbao->setPosition(SystemData::getLayoutPoint("ui_horse_yuanbao_pos"));
	pSprite_yuanbao->setAnchorPoint(CCPointZero);
	addChild(pSprite_yuanbao);
	m_pVcoinLabel=CCLabelTTF::create(" ","Times New Roman",14);
	m_pVcoinLabel->setAnchorPoint(CCPointZero);
	m_pVcoinLabel->setPosition(SystemData::getLayoutPoint("ui_horse_yuanbao_cnt_pos"));
	addChild(m_pVcoinLabel); 
	m_pVcoinLabel->setString(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str());


	m_pName=SystemData::getLabelTTF("XXXX");
	m_pName->setFontSize(20);
	m_pName->setColor(ccWHITE);
	m_pName->setPosition(SystemData::getLayoutPoint("ui_horse_name_pos"));
	addChild(m_pName);
	
	// 经验条
	CCScale9Sprite* pExpboard=SystemData::getScale9SpriteByPlist("ui_horse_expboard");
	pExpboard->setAnchorPoint(ccp(0,0.5));
	pExpboard->setPosition(SystemData::getLayoutPoint("ui_horse_exp_pos"));
	addChild(pExpboard);
	initExp();

	// 升级
	CCMenuItemImage* pBtnSJ=SystemData::getScale9MenuItemImageByPlist("ui_horse_btn");
	pBtnSJ->setPosition(SystemData::getLayoutPoint("ui_horse_btn_sj_pos"));
	pBtnSJ->setTag(HORSE_LevelUp);
	pBtnSJ->setTarget(this,menu_selector(HorsePanel::MenuPeiYangCallBack));
	m_pMainMenu->addChild(pBtnSJ);
	CCLabelTTF* pLblSJ=SystemData::getLabelTTF("ui_horse_lbl_sj");
	pLblSJ->setFontSize(20);
	pLblSJ->setColor(ccWHITE);
	pLblSJ->setPosition(ccp(pBtnSJ->getContentSize().width/2,pBtnSJ->getContentSize().height/2));
	pBtnSJ->addChild(pLblSJ);

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	m_pMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMenu);

	m_pHorseStateLabel=CCLabelTTF::create("","",18);
	m_pHorseStateLabel->setPosition(SystemData::getLayoutPoint("ui_horse_label_state_pos"));
	addChild(m_pHorseStateLabel);


	CCSprite* ptitle=SystemData::getSpriteByPlist("ui_horse_yl_title");
	ptitle->setPosition(SystemData::getLayoutPoint("ui_horse_yl_title_pos"));
	addChild(ptitle);

	CCLabelTTF *plabel=SystemData::getLabelTTF("ui_horse_label_yl");
	plabel->setFontSize(20);
	plabel->setColor(ccWHITE);
	plabel->setPosition(ptitle->getPosition());
	addChild(plabel);

	initHorseHead();

	this->scheduleUpdate();

	return true;
}


void HorsePanel::initHorseEquip()
{
	m_pEquipMenu->removeAllChildren();

	// 装备
	int count = SystemData::getLayoutValue("ui_horse_zb_cnt");
	for (int i = 1; i <= count; i++)
	{
		CCString *url = CCString::createWithFormat("ui_horse_zb%d_pos", i);
		CCSprite *base=SystemData::getSpriteByPlist("ui_horse_base");
		base->setPosition(SystemData::getLayoutPoint(url->getCString()));
		base->setAnchorPoint(CCPointZero);
		m_pEquipMenu->addChild(base);

		int proplv = HeroData::getProp(Entity::attr_horse_equip1_level + (i - 1) * 2);
		bool isopen = true;
		if (proplv < 1)
		{
			proplv = 1;
			isopen = false;
		}

		//添加装备层级特效
		const int coloreffect[ItemQuality_Max] = {0, Effect::effect_equipcolor1, Effect::effect_equipcolor2, Effect::effect_equipcolor3, Effect::effect_equipcolor4, Effect::effect_equipcolor5, Effect::effect_equipcolor6, Effect::effect_equipcolor7};
		int color = 0;
		LuaData::getProp("gdHorseEquipBaseStats", i, proplv, "Color", color);
		switch (color)
		{
		case ItemQuality_Null:
		case ItemQuality_Green:
		case ItemQuality_Blue:
		case ItemQuality_Magenta:
		case ItemQuality_Yellow:
		case ItemQuality_Hose:
		case ItemQuality_Tuo:
		case ItemQuality_King:
			{
				EffectSprite* pEffect = EffectSprite::create(coloreffect[color]);
				pEffect->setPosition(ccp(base->getContentSize().width/2, base->getContentSize().height/2));
				base->addChild(pEffect);
			}
			break;
		default:
			break;
		}

		// 装备图标
		std::string itemurl = "";
		LuaData::getProp("gdHorseEquipBaseStats", i, proplv, "Image", itemurl);
		itemurl = LayoutData::getString(CPModuleName::COMMON, "itemIconPath") + itemurl;
		CCMenuItemImage* pButton = CCMenuItemImage::create(itemurl.c_str(), itemurl.c_str());
		pButton->setPosition(base->getContentSize().width / 2, base->getContentSize().height / 2);
		base->addChild(pButton);

		// 点击对象
		CCMenuItemImage* pItem=CCMenuItemImage::create();
		pItem->setAnchorPoint(CCPointZero);
		pItem->setPosition(SystemData::getLayoutPoint(url->getCString()));
		pItem->setContentSize(base->getContentSize());
		pItem->setTag(i);
		pItem->setTarget(this, menu_selector(HorsePanel::MenuEquipCallBack));
		m_pEquipMenu->addChild(pItem);
		

		if (!isopen)
		{
			CCMenuItemImage* pLock = SystemData::getMenuItemImageByPlist("ui_horse_lock");
			pLock->setPosition(ccp(base->getContentSize().width / 2, base->getContentSize().height / 2));
			base->addChild(pLock);
		}
	}
}

void HorsePanel::initHorseModel(int idx)
{
	std::string model = "";
	LuaData::getProp("gdHorseBaseStats", idx, "AppearanceImage", model);
	std::string url="horse/"+ model +"_0";
	CCFlashAnimation* animation = SystemData::getAnimation(url);

	CCNode *pOldModel = getChildByTag(TAG_HORSE_MODEL);
	if (pOldModel)
	{
		pOldModel->removeFromParentAndCleanup(true);
	}

	CCSprite* pModel=CCSprite::create();
	pModel->runAction(CCRepeatForever::create(CCSequence::create(CCFlipX::create(true),animation->getAnimate(2),NULL)));
	pModel->setPosition(SystemData::getLayoutPoint("ui_horse_model_pos"));
	pModel->setTag(TAG_HORSE_MODEL);
	addChild(pModel);

	std::string horsename = "";
	LuaData::getProp("gdHorseBaseStats", idx, "Name", horsename);
	m_pName->setString(horsename.c_str());
}

void HorsePanel::initHorseHead()
{
	int horseLevel = HeroData::getProp(Entity::attr_horse_level);
	int appearLevel = HeroData::getProp(Entity::attr_horse_appearance);
	if (appearLevel <= 0)
	{
		appearLevel = horseLevel;
	}
	if (!m_pList)
	{
		m_pList = CPItemComponents::create(SystemData::getLayoutSize("ui_horse_head_list_size"), 
			new CPLayoutList(SystemData::getLayoutSize("ui_horse_head_size"), false));
		m_pList->setAnchorPoint(CCPointZero);
		m_pList->setPosition(SystemData::getLayoutPoint("ui_horse_head_list_pos"));
		addChild(m_pList);
	}

	m_pList->removeAllItems();

	int maxlv = 0;
	LuaData::getProp("gdHorseBaseStats", "MaxLevel", maxlv);
	for (int i = 1; i <= maxlv; i++)
	{
		CCMenuItemImage* pLayer=CCMenuItemImage::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		pLayer->setContentSize(SystemData::getLayoutSize("ui_horse_head_size"));
		pLayer->setTarget(this, menu_selector(HorsePanel::MenuHeadCallBack));
		m_pList->addItem(pLayer);
		pLayer->setTag(i);

		// ????????????
		CCSize layerSize = pLayer->getContentSize();
		CCLayerColor* pSelectBg = CCLayerColor::create(ccc4(255, 200, 50, 80), layerSize.width + 10, layerSize.height + 10);
		pSelectBg->setPosition(ccp(-5, -5));
		pSelectBg->setVisible(false);
		pSelectBg->setTag(TAG_HORSE_SELECT_FRAME);
		pLayer->addChild(pSelectBg, 10);
		if (i == appearLevel)
		{
			pSelectBg->setVisible(true);
		}

		CCSprite *pEquip=SystemData::getSpriteByPlist("ui_horse_base");
		pEquip->setPosition(ccp(0,30));
		pEquip->setAnchorPoint(CCPointZero);
		pLayer->addChild(pEquip);

		std::string url = "";
		LuaData::getProp("gdHorseBaseStats", i, "HeadPortraitImage", url);
		url = LayoutData::getString(CPModuleName::COMMON, "itemIconPath") + url;
		CCMenuItemImage* pButton = CCMenuItemImage::create(url.c_str(), url.c_str());
		pButton->setPosition(pEquip->getContentSize().width / 2, pEquip->getContentSize().height / 2);
		pEquip->addChild(pButton);

		CCString *info = CCString::createWithFormat("index:%d", i);
		CCLabelTTF* pLabel = SystemData::getLabelTTF(info->getCString());
		pLabel->setColor(ccWHITE);
		pLabel->setString(info->getCString());
		pLabel->setFontSize(18);
		pLabel->setPosition(ccp(pButton->getContentSize().width/2, 10));
		pLayer->addChild(pLabel);

		if (horseLevel + 1 < i)
		{
			CCMenuItemImage* pLock = SystemData::getMenuItemImageByPlist("ui_horse_lock");
			pLock->setPosition(ccp(pEquip->getContentSize().width / 2, pEquip->getContentSize().height / 2));
			pEquip->addChild(pLock);
		}
	}

	m_pList->setCurrentIndex(appearLevel);
	initHorseModel(appearLevel);
	showRideButtons();
}

void HorsePanel::showRideButtons()
{
	if (!m_pMainMenu) return;
	int rideState = HeroData::getProp(Entity::attr_horse_ride_state);

	CCArray* children = m_pMainMenu->getChildren();
	if (!children) return;
	for (int i = 0; i < children->count(); i++)
	{
		CCNode* child = (CCNode*)children->objectAtIndex(i);
		if (!child) continue;
		if (child->getTag() == HORSE_RideHorse)
		{
			child->setVisible(rideState == 0);
		}
		else if (child->getTag() == HORSE_XiaMa)
		{
			child->setVisible(rideState != 0);
		}
	}
}


void HorsePanel::MenuPeiYangCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(!pNode)
	{
		return;
	}
	StrVector vect;
	CCNode *pMainUI = Game::getGameUI()->getPanel(TAG_MAIN_PANEL);
	switch (pNode->getTag())
	{
	case HORSE_AddExpOnce:
		FloatPanel::show(FloatPanelType::Horse_RYPY, vect, pMainUI, floatpanel_selector(HorsePanel::AddExp1));
		break;
	case HORSE_AddExp10:
		FloatPanel::show(FloatPanelType::Horse_YBPY, vect, pMainUI, floatpanel_selector(HorsePanel::AddExp10));
		break;
	case HORSE_AddExp50:
		FloatPanel::show(FloatPanelType::Horse_YJSJ, vect, pMainUI, floatpanel_selector(HorsePanel::AddExp50));
		break;
	case HORSE_LevelUp:
		{
			int horseLevel = HeroData::getProp(Entity::attr_horse_level);
			int needid = 0;
			LuaData::getProp("gdHorseJinJie", horseLevel, "ItemCfgID", needid);
			int needCnt = 0;
			LuaData::getProp("gdHorseJinJie", horseLevel, "ItemCount", needCnt);
			int shopprice=0;
			LuaData::getProp("gdItems",needid,"shopprice",shopprice);
			int price = needCnt * shopprice;
			int mabiancnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("horsejinjie_id"),ItemPos::Player_Bag_Start);
			vect.push_back(SystemData::intToString(needCnt));
			vect.push_back(SystemData::intToString(price));
			vect.push_back(SystemData::intToString(mabiancnt));
			FloatPanel::show(FloatPanelType::Horse_SJ, vect, pMainUI, floatpanel_selector(HorsePanel::levelUp));
		}
		break;
	default:
		break;
	}

}

void HorsePanel::MenuShangmaCallBack( CCObject* pSender )
{
	HeroData::setProp(Entity::attr_horse_ride_state, 1);
	GameRole* myRole = GameData::getMyRole();
	if (myRole)
	{
		myRole->setDress(AVATAR_TYPE_HORSE, 1);
		myRole->setDress(AVATAR_TYPE_HORSEHEAD, 1);
		myRole->setExData(Entity::attr_horse_ride_state, 1);
	}
	MsgRideReq* msg=new MsgRideReq;
	msg->OnOrOff = 1;
	HandleMessage::sendMessage(msg);

	showRideButtons();
}

void HorsePanel::MenuXiamaCallBack( CCObject* pSender )
{
	HeroData::setProp(Entity::attr_horse_ride_state, 0);
	GameRole* myRole = GameData::getMyRole();
	if (myRole)
	{
		myRole->setExData(Entity::attr_horse_ride_state, 0);
	}
	MsgRideReq* msg=new MsgRideReq;
	msg->OnOrOff = 0;
	HandleMessage::sendMessage(msg);

	showRideButtons();
}

void HorsePanel::MenuHeadCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(!pNode)
	{
		return;
	}

	int horseLevel = HeroData::getProp(Entity::attr_horse_level);
	int tag = pNode->getTag();

	// ???????????????,???????
	if (HeroData::getProp(Entity::attr_horse_ride_state) != 0)
	{
		CPEventHelper::uiNotify("", "", Error::HorseRideStateError);
		return;
	}

	if (tag > horseLevel)
	{		
		CPEventHelper::uiNotify("", "", Error::Item_HorseLvlLess);
		return;
	}

	// ?????????????
	initHorseModel(tag);

	// ?????????????
	for (int i = 0; i < m_pList->getItemCount(); i++)
	{
		CCNode* pItem = m_pList->getItem(i);
		if (pItem)
		{
			CCNode* pFrame = pItem->getChildByTag(TAG_HORSE_SELECT_FRAME);
			if (pFrame) pFrame->setVisible(false);
		}
	}
	CCNode* pSelFrame = pNode->getChildByTag(TAG_HORSE_SELECT_FRAME);
	if (pSelFrame) pSelFrame->setVisible(true);

	// ????????????(????=0??????????)
	MsgHorseSetAppearanceReq* msg = new MsgHorseSetAppearanceReq;
	msg->AppearanceLevel = tag;
	HandleMessage::sendMessage(msg);
}

void HorsePanel::MenuEquipCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(!pNode)
	{
		return;
	}
	int tag = pNode->getTag();

	int proplv = HeroData::getProp(Entity::attr_horse_equip1_level + (tag - 1) * 2);
	if (proplv < 1)
	{
		CPEventHelper::uiNotify("", "", Error::Item_HorseLvlLess);
		return;
	}

	CCNode *pMainUI = Game::getGameUI()->getPanel(TAG_MAIN_PANEL);
	HorseEquipEnhancePanel *panel = HorseEquipEnhancePanel::create(tag);
	pMainUI->addChild(panel);
}


void HorsePanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_HORSE_ADD_EXP)
	{
		initExp();
	}
	else if(channel == EventProtocol::EVENT_HORSE_LEVEL_UP)
	{
		initExp();
		initHorseHead();
		initHorseEquip();
		addLevelUpEffect();
	}
	else if (channel == EventProtocol::EVENT_HORSE_EQUIP_LEVEL_UP)
	{
		initHorseEquip();
	}
	m_pVcoinLabel->setString(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str());
	//m_pHonorLabel->setString(SystemData::intToString(GameData::s_user->m_pMainRole->Honour).c_str());
	int mabiancnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("mabian_id"),ItemPos::Player_Bag_Start);
	m_pMabianCnt->setString(SystemData::intToString(mabiancnt).c_str());
}

void HorsePanel::postMsg()
{

}

void HorsePanel::initExp()
{
	int curexp = HeroData::getProp(Entity::attr_horse_exp);
	int horseLevel = HeroData::getProp(Entity::attr_horse_level);
	int maxexp = 0;
	LuaData::getProp("gdHorseBaseStats", horseLevel, "UpLevelExp", maxexp);

	float ratio = 0.0f;
	if (maxexp != 0)
	{
		ratio = (float)curexp / maxexp;
	}
	if (ratio > 1.0f)
	{
		ratio = 1.0f;
	}

	if (ratio < 0.0f)
	{
		ratio = 0.0f;
	}

	if (!m_pExppoint)
	{
		m_pExppoint=SystemData::getScale9SpriteByPlist("ui_horse_exppoint");
		m_pExppoint->setContentSize(SystemData::getLayoutSize("ui_horse_expboard"));
		addChild(m_pExppoint);
	}
	m_pExppoint->setPosition(SystemData::getLayoutPoint("ui_horse_exp_pos"));
	m_pExppoint->setAnchorPoint(ccp(0,0.5));

	m_pExppoint->setScaleX(ratio);
	m_pExppoint->setScaleY(0.5);

}


void HorsePanel::update( float dt )
{

}

void HorsePanel::updateRightAttr()
{
	((CommonPanel*)this->getParent())->selectTop(PETSKILL);
}


bool  HorsePanel::checkVcoin()
{
	int req=0;
	LuaData::getProp("gdGame","PetFeedGold",req);
	if (HeroData::getProp(Entity::attr_gold)>=req)
	{
		return true;
	}
	return false;
}

bool  HorsePanel::checkHonor()
{
	int req=0;
	LuaData::getProp("gdGame","PetFeedHonor",req);
	if (GameData::s_user->m_pMainRole->Honour>=req)
	{
		return true;
	}
	return false;
}

void HorsePanel::addLevelUpEffect()
{
	EffectSprite* p=EffectSprite::create(Effect::effect_petlvlup,1);
	p->setPosition(ccp((SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").x+SystemData::getLayoutPoint("ui_pet_rightbutton1_pos").x)/2+10,SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").y-90));
	addChild(p); 
}

void HorsePanel::initAll()
{

}

void HorsePanel::AddExp1(int tag)
{
	if (tag != Button_QD)
	{
		return;
	}
	MsgHorsePeiYangReq* msg=new MsgHorsePeiYangReq;
	msg->count = 1;
	HandleMessage::sendMessage(msg);
}

void HorsePanel::AddExp10(int tag)
{
	if (tag != Button_QD)
	{
		return;
	}
	MsgHorsePeiYangReq* msg=new MsgHorsePeiYangReq;
	msg->count = 10;
	HandleMessage::sendMessage(msg);
}

void HorsePanel::AddExp50(int tag)
{
	if (tag != Button_QD)
	{
		return;
	}
	MsgHorsePeiYangReq* msg=new MsgHorsePeiYangReq;
	msg->count = 50;
	HandleMessage::sendMessage(msg);
}


void HorsePanel::levelUp(int tag)
{
	if (tag != Button_QD)
	{
		return;
	}
	MsgHorseJinJieReq* msg=new MsgHorseJinJieReq;
	HandleMessage::sendMessage(msg);
}

void HorsePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		
	}
}



