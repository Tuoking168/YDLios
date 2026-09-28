#include "HorseAttributePanel.h"
#include "ActivityModule.h"
#include "userdata/SystemData.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "event/EventProtocol.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "CombatDefinition.h"
#include "PetDefinition.h"
#include "userdata/UserPetData.h"
#include "userdata/HeroData.h"
#include "userdata/SystemData.h"
#include "userdata/StaticData.h"
#include "userdata/LayoutData.h"
#include "userdata/UserPetData.h"
#include "module/GuideModule.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"
#include "controls/CPCheckBox.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "userdata/luadata/LuaData.h"
#include "MsgPet.h"
#include "network/HandleMessage.h"
#include "script/LuaWrapper.h"
#include "controls/CPItemComponents.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"
#include "MsgItem.h"

HorseAttributePanel::HorseAttributePanel()
{
	m_pMainMenu=NULL;
}


HorseAttributePanel::~HorseAttributePanel()
{
	CC_SAFE_RELEASE(m_pMainMenu);
}

void HorseAttributePanel::setMainMenu(CCLayer* var)
{
	CC_SAFE_RELEASE(m_pMainMenu);
	m_pMainMenu=var;
	CC_SAFE_RETAIN(m_pMainMenu);
}

CCLayer* HorseAttributePanel::getMainMenu()
{
	return m_pMainMenu;
}

bool HorseAttributePanel::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCScale9Sprite* m_pBkgSprite = SystemData::getScale9SpriteByPlist("ui.bag.small_bkg", 305, 429);

	if(!m_pBkgSprite)
	{
		return false;
	}
	m_pBkgSprite->setAnchorPoint(CCPointZero);
	m_pBkgSprite->setPosition(CCPointZero);
	addChild(m_pBkgSprite);

	//加载滚动界面
	pTabelView=CCTableViewEx::create(this,CCSizeMake(284, 415),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(SystemData::getLayoutPoint("attribute_pos"));
	//pTabelView->reloadData();  
	this->addChild(pTabelView);

	updateList();

	return true;
}

void HorseAttributePanel::updateList()
{
	//pTabelView->removeAllChildren();
	CCLayer* layer=HorseBasePanel::create();	
	mHeight=layer->getContentSize().height;
	pTabelView->reloadData();
}


CCSize HorseAttributePanel::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(SystemData::getLayoutSize("attribute_PetBase_Content").width,mHeight);
}

CCTableViewCell* HorseAttributePanel::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* layer=HorseBasePanel::create();	
		mHeight=layer->getContentSize().height;
		if (layer)
		{
			layer->setAnchorPoint(CCPointZero);
			layer->setPosition(ccp(0,mHeight));
			cell->addChild(layer);
		}
	}
	return cell;
}

unsigned int HorseAttributePanel::numberOfCellsInTableView(CCTableView *table)
{
	return 1;
}



//-----------------------------------------------------------------//


HorseBasePanel::HorseBasePanel():
	mHeight(0)
{
	EventDispatcher::sharedEventDispather()->addListener(this);
}

HorseBasePanel::~HorseBasePanel()
{
	EventDispatcher::sharedEventDispather()->removeListener(this);
}

void HorseBasePanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_HORSE_LEVEL_UP)
	{
		removeAllChildren();
		initFirstPart();
		initSecondPart();

		this->setContentSize(CCSizeMake(SystemData::getLayoutSize("attribute_PetBase_Content").width,mHeight));
	}
}

bool HorseBasePanel::init()
{
	removeAllChildren();

	initHorseGene();
	initFirstPart();
	initSecondPart();

	this->setContentSize(CCSizeMake(SystemData::getLayoutSize("attribute_PetBase_Content").width,mHeight));

	return true;
}

void HorseBasePanel::initHorseGene()
{
	int maxlv = 0;
	LuaData::getProp("gdHorseBaseStats", "MaxLevel", maxlv);
	
	for (int i = 1; i <= maxlv; i++)
	{
		int id = 0;
		LuaData::getProp("gdHorseBaseStats", i, "GeneCfgID", id);
		if (id == 0)
		{
			continue;
		}
		m_vecGeneLv.push_back(GeneLv(i, id));
	}
}

void HorseBasePanel::initFirstPart()
{	
	//标题 
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("ui_horse_attr_1_contentsize"));	
	CCSprite *ptitle=SystemData::getSpriteByPlist("ui_pet_jichu");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,0));
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);
	
	int horseLevel = HeroData::getProp(Entity::attr_horse_level);
	std::map<int, int> mapAttr;

	// 基础属性
	int basesize = 0;
	LuaData::getProp_size("gdHorseBaseStats", horseLevel, "AttrAdd", basesize);
	for (int i = 1; i <= basesize; i++)
	{
		int attr = 0;
		LuaData::getProp("gdHorseBaseStats", horseLevel, "AttrAdd", i, "AttrID", attr);
		int value = 0;
		LuaData::getProp("gdHorseBaseStats", horseLevel, "AttrAdd", i, "AttrValue", value);
		if (value == 0)
		{
			continue;
		}
		mapAttr[attr] = value;
	}

	// 装备属性
	int equipsize = 0;
	LuaData::getProp_size("gdHorseEquipBaseStats", equipsize);
	for (int i = 1; i <= equipsize; i++)
	{
		// 装备等级,经验格式是交叉的
		int proplv = HeroData::getProp(Entity::attr_horse_equip1_level + i * 2);
		if (proplv == 0)
		{
			continue;
		}

		int attrsize = 0;
		LuaData::getProp_size("gdHorseEquipBaseStats", i, proplv, "AttrAdd", attrsize);
		for (int j = 1; j <= attrsize; j++)
		{
			// 装备等级,经验格式是交叉的
			int proplv = HeroData::getProp(Entity::attr_horse_equip1_level + i * 2);

			int attr = 0;
			LuaData::getProp("gdHorseEquipBaseStats", i, proplv, "AttrAdd", j, "AttrID", attr);
			int value = 0;
			LuaData::getProp("gdHorseEquipBaseStats", i, proplv, "AttrAdd", j, "AttrValue", value);
			if (value == 0)
			{
				continue;
			}
			mapAttr[attr] = mapAttr[attr] + value;
		}
	}

	std::string strlist[8]=
	{
		"pet_wuligongji","pet_daoshugongji","pet_mofagongji","pet_shengming","pet_wulifangyu","pet_mofafangyu","pet_mofa"
	};
	int proplist[7] = 
	{
		Combat::prop_PATK_Max,
		Combat::prop_TATK_Max,
		Combat::prop_MATK_Max,
		Combat::prop_HPMax,
		Combat::prop_PDEF_Max,
		Combat::prop_MDEF_Max,
		Combat::prop_MPMax
	};
	int basex = ptitle->getPositionX()-140;
	int basey = ptitle->getPositionY()-45;
	for (int i = 0; i < 7; i++)//hide pet combact
	{		
		CCLabelTTF *plabel=SystemData::getLabelTTF(strlist[i]);
		plabel->setFontSize(14);
		plabel->setColor(ccWHITE);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setPosition(ccp(basex + (i / 4)*150, basey - (i % 4)*30));

		CCLabelTTF *pValue=CCLabelTTF::create(SystemData::intToString(mapAttr[proplist[i]]).c_str(), "微软雅黑", 14);		
		pValue->setColor(ccGREEN);
		pValue->setAnchorPoint(CCPointZero);
		pValue->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width+10,plabel->getPositionY()));
		pLayer->addChild(pValue);	
		pLayer->addChild(plabel);
	}


	pLayer->setAnchorPoint(ccp(0,1));
	pLayer->setPosition(ccp(0,-20));
	mHeight+=pLayer->getContentSize().height;
	this->addChild(pLayer);
}

void HorseBasePanel::initSecondPart()
{
	//标题
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("ui_horse_attr_2_contentsize"));
	CCSprite *ptitle=SystemData::getSpriteByPlist("ui_pet_jinjie");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,0));
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);


	GeneralMenu* pMenu = GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	pLayer->addChild(pMenu);

	int horseLevel = HeroData::getProp(Entity::attr_horse_level);


	// 技能框框
	int skillcount = SystemData::getLayoutValue("ui_horse_attr_skill_count");
	for (int i = 0; i < skillcount; i++)
	{
		CCSprite *pEquip=SystemData::getSpriteByPlist("forging_base");
		CCString* pStr = CCString::createWithFormat("ui_horse_attr_skill%d_pos", i);
		pEquip->setPosition(SystemData::getLayoutPoint(pStr->getCString()));
		pEquip->setAnchorPoint(CCPointZero);
		pMenu->addChild(pEquip);

		if (i < m_vecGeneLv.size())
		{
			int id = m_vecGeneLv[i].id;
			int lv = m_vecGeneLv[i].lv;
			// 添加Buff图标
			std::string iconKey;
			StaticData::getGeneIcon(id, iconKey);
			CCSprite* picon = LayoutData::getSpriteByFrameName(iconKey);
			picon->setPosition(ccp(pEquip->getContentSize().width/2,pEquip->getContentSize().height/2));
			pEquip->addChild(picon);

			// 点击对象
			CCMenuItemImage* pItem=CCMenuItemImage::create();
			pItem->setAnchorPoint(CCPointZero);
			pItem->setPosition(SystemData::getLayoutPoint(pStr->getCString()));
			pItem->setContentSize(pEquip->getContentSize());
			pItem->setTag(id);
			pItem->setTarget(this, menu_selector(HorseBasePanel::menuCallBack));
			pMenu->addChild(pItem);

			if (lv > horseLevel)
			{
				pItem->setTag(0);
				CCMenuItemImage* pLock = SystemData::getMenuItemImageByPlist("ui_horse_lock");
				CCString* pStr = CCString::createWithFormat("ui_horse_attr_skill%d_pos", i);
				pLock->setPosition(ccp(pEquip->getContentSize().width / 2, pEquip->getContentSize().height / 2));
				pEquip->addChild(pLock);
			}
		}
		else
		{
			CCMenuItemImage* pLock = SystemData::getMenuItemImageByPlist("ui_horse_lock");
			CCString* pStr = CCString::createWithFormat("ui_horse_attr_skill%d_pos", i);
			pLock->setPosition(ccp(pEquip->getContentSize().width / 2, pEquip->getContentSize().height / 2));
			pEquip->addChild(pLock);
		}

	}

	pLayer->setAnchorPoint(ccp(0,1));
	pLayer->setPosition(ccp(0,-20-SystemData::getLayoutSize("PetBase_1_contentsize").height));		
	mHeight+=pLayer->getContentSize().height;
	this->addChild(pLayer); 
}


void HorseBasePanel::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (!pNode)
	{
		return;
	}

	int tag = pNode->getTag();
	if (tag == 0)
	{
		CPEventHelper::uiNotify("", "", Error::Item_HorseLvlLess);
		return;
	}

	HorseBuffTips* ptips=HorseBuffTips::create(tag);
	ptips->setPosition(80, -130);
	addChild(ptips);
}



//----------------------------------------------------------------//

HorseBuffTips::HorseBuffTips():
	m_iTag(0)
{
}

HorseBuffTips::~HorseBuffTips()
{
}

HorseBuffTips* HorseBuffTips::create( int tag )
{
	HorseBuffTips* p = new HorseBuffTips;
	if (p && p->init(tag))
	{
		p->autorelease();
		return p;
	}
	if (p)
	{
		delete p;
		return NULL;
	}
	return NULL;
}

bool HorseBuffTips::init( int tag )
{
	if (!PartPanel::init())
	{
		return false;
	}

	int height = 0;

	CCLayer* pLayer = CCLayer::create();
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(CCPointZero);
	addChild(pLayer);

	std::string iconKey;
	m_iTag = tag;
	StaticData::getGeneIcon(m_iTag, iconKey);
	CCSprite* picon = LayoutData::getSpriteByFrameName(iconKey);
	//picon->setScale(1.5f);
	addChild(picon);


	std::string namestr;
	LuaData::getProp("gdGenes",m_iTag,"name",namestr);
	if (namestr=="0")
	{
		namestr = SystemData::getLayoutString("attribute_Base_null");
	}
	CCString* pnameStr = CCString::createWithFormat("%s%s",SystemData::getLayoutString("buffpanel_buffName").c_str(),namestr.c_str());

	CCLabelTTF* pName =  CCLabelTTF::create(pnameStr->getCString(),"",16); 
	pName->setColor(ccWHITE);
	pName->setAnchorPoint(ccp(0,1));
	pName->setHorizontalAlignment(kCCTextAlignmentLeft);
	pName->setDimensions(SystemData::getLayoutSize("buffpanel_desc"));
	pName->setPosition(ccp(picon->getPositionX()-picon->getContentSize().width/2,picon->getPositionY()-picon->getContentSize().height/2-5)); 
	addChild(pName);

	std::string descstr;
	LuaData::getProp("gdGenes",m_iTag,"desc",descstr);
	if (descstr=="0")
	{
		descstr = SystemData::getLayoutString("attribute_Base_null");
	}
	CCString* pdescStr = CCString::createWithFormat("%s%s",SystemData::getLayoutString("buffpanel_buffDesc").c_str(),descstr.c_str());

	CCLabelTTF* pDesc = CCLabelTTF::create(pdescStr->getCString(),"",16);
	pDesc->setColor(ccWHITE);
	pDesc->setHorizontalAlignment(kCCTextAlignmentLeft);
	pDesc->setDimensions(SystemData::getLayoutSize("buffpanel_desc"));
	pDesc->setAnchorPoint(ccp(0,1));
	pDesc->setPosition(ccp(pName->getPositionX(),pName->getPositionY()-pName->getContentSize().height-5));
	addChild(pDesc);

	height = pDesc->getContentSize().height + pName->getContentSize().height + picon->getContentSize().height +45;

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("topactivity_bkg",SystemData::getLayoutValue("buffpanel_border.w"),height);
	pBorder->setAnchorPoint(ccp(0,1));
	pBorder->setPosition(ccp(picon->getPositionX()-picon->getContentSize().width,picon->getPositionY()+picon->getContentSize().height));
	pLayer->addChild(pBorder);

	m_nWidth = pBorder->getContentSize().width;
	m_nHeight = pBorder->getContentSize().height;
	addCover(ccp(pBorder->getPositionX(),pBorder->getPositionY()-m_nHeight));

	this->setContentSize(CCSizeMake(m_nWidth,m_nHeight));


	return true;
}

//////------------------------------------------------------------------------------------------------------------------------//

HorseEquipEnhancePanel::HorseEquipEnhancePanel():
	m_bBlock(false),
	m_pMenu(NULL),
	m_pEquipLayer(NULL),
	m_pExppoint(NULL),
	pSprite(NULL),
	m_pLabelVcoin(NULL),
	m_bVcoin(false),
	m_equipindex(0)
{
	EventDispatcher::sharedEventDispather()->addListener(this);

}

HorseEquipEnhancePanel::~HorseEquipEnhancePanel()
{
	EventDispatcher::sharedEventDispather()->removeListener(this);

}

HorseEquipEnhancePanel* HorseEquipEnhancePanel::create( int tag )
{
	HorseEquipEnhancePanel* p = new HorseEquipEnhancePanel;
	if (p && p->init(tag))
	{
		p->autorelease();
		return p;
	}
	if (p)
	{
		delete p;
		return NULL;
	}
	return NULL;
}

bool HorseEquipEnhancePanel::init(int tag)
{
	if (!PartPanel::init())
	{
		return false; 
	}	
	m_equipindex = tag;

	int x = getPositionX();
	int y = getPositionY();
	m_pBkg = SystemData::getSpriteByPlist("ui_horse_equip_bkg");
	m_pBkg->setAnchorPoint(CCPointZero);
	m_pBkg->setPosition(SystemData::getLayoutPoint("ui_horse_equip_bkg"));
	addChild(m_pBkg);

	m_nHeight = m_pBkg->getContentSize().height;
	m_nWidth = m_pBkg->getContentSize().width;

	// 标题文字
	CCLabelTTF* pTitle = SystemData::getLabelTTF("ui_horse_equip_title");
	pTitle->setColor(ccYELLOW);
	pTitle->setFontSize(20);
	pTitle->setPosition(ccp(m_pBkg->getContentSize().width/2,m_pBkg->getContentSize().height-25));
	m_pBkg->addChild(pTitle);

	CCScale9Sprite* pborder = SystemData::getScale9SpriteByPlist("ui_horse_equip_border");
	pborder->setAnchorPoint(CCPointZero);
	m_pBkg->addChild(pborder);

	addCover();
	//------------------------------------------------------------------------------------------------------------------------------------//
	m_pEquipLayer = CCLayer::create();
	m_pEquipLayer->setAnchorPoint(CCPointZero);
	m_pEquipLayer->setPosition(CCPointZero);
	m_pBkg->addChild(m_pEquipLayer);

	initEquip();

	// 经验条
	CCScale9Sprite* pExpboard=SystemData::getScale9SpriteByPlist("ui_horse_equip_expboard");
	pExpboard->setAnchorPoint(ccp(0,0.5));
	pExpboard->setPosition(SystemData::getLayoutPoint("ui_horse_equip_exp_pos"));
	m_pBkg->addChild(pExpboard);

	m_pExppoint = SystemData::getScale9SpriteByPlist("ui_pet_exppoint");
	m_pExppoint->setContentSize(SystemData::getLayoutSize("ui_horse_expboard"));
	m_pExppoint->setPosition(SystemData::getLayoutPoint("ui_horse_equip_exp_pos"));
	m_pExppoint->setAnchorPoint(ccp(0,0.5));
	m_pBkg->addChild(m_pExppoint);

	initExp();

	

	// 盘古碎片数量
	CCLabelTTF* plabelPangu = SystemData::getLabelTTF("ui_horse_equip_label_pgsp");
	plabelPangu->setFontSize(14);
	plabelPangu->setColor(ccYELLOW);
	plabelPangu->setPosition(SystemData::getLayoutPoint("ui_horse_equip_label_pgsp"));
	m_pBkg->addChild(plabelPangu);
	m_pLabelPangu=CCLabelTTF::create("XXXX","Times New Roman",14);
	m_pLabelPangu->setAnchorPoint(ccp(0,0.5));
	m_pLabelPangu->setPosition(SystemData::getLayoutPoint("ui_horse_equip_label_pgsp_cnt"));
	m_pBkg->addChild(m_pLabelPangu); 

	// 开天玉数量
	CCLabelTTF* plabelKaitian = SystemData::getLabelTTF("ui_horse_equip_label_kty");
	plabelKaitian->setFontSize(14);
	plabelKaitian->setColor(ccYELLOW);
	plabelKaitian->setPosition(SystemData::getLayoutPoint("ui_horse_equip_label_kty"));
	m_pBkg->addChild(plabelKaitian);
	m_pLabelKaitian=CCLabelTTF::create("XXXX","Times New Roman",14);
	m_pLabelKaitian->setAnchorPoint(ccp(0,0.5));
	m_pLabelKaitian->setPosition(SystemData::getLayoutPoint("ui_horse_equip_label_kty_cnt"));
	m_pBkg->addChild(m_pLabelKaitian); 

	// 元宝
	CCSprite* pSprite_yuanbao=SystemData::getSpriteByPlist("ui_horse_equip_yuanbao");
	pSprite_yuanbao->setPosition(SystemData::getLayoutPoint("ui_horse_equip_yuanbao_pos"));
	pSprite_yuanbao->setAnchorPoint(CCPointZero);
	m_pBkg->addChild(pSprite_yuanbao);
	m_pLabelVcoin=CCLabelTTF::create(" ","Times New Roman",14);
	m_pLabelVcoin->setAnchorPoint(CCPointZero);
	m_pLabelVcoin->setPosition(SystemData::getLayoutPoint("ui_horse_equip_yuanbao_cnt_pos"));
	m_pBkg->addChild(m_pLabelVcoin); 

	
	m_pMenu = GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	m_pBkg->addChild(m_pMenu);



	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(SystemData::getLayoutPoint("ui_horse_equip_bkg"));
	addChild(pMenu);

	// 加经验
	CCMenuItemImage* pButtonAddExp = SystemData::getMenuItemImageByPlist("ui_horse_btn");
	pButtonAddExp->setPosition(SystemData::getLayoutPoint("ui_horse_equip_btn_lbl_addexp_pos"));
	pButtonAddExp->setTarget(this,menu_selector(HorseEquipEnhancePanel::menuAddExpCallBack));
	pMenu->addChild(pButtonAddExp);
	CCLabelTTF* pbuttonlabelAddExp = SystemData::getLabelTTF("ui_horse_equip_btn_lbl_addexp");
	pbuttonlabelAddExp->setColor(ccWHITE);
	pbuttonlabelAddExp->setFontSize(18);
	pbuttonlabelAddExp->setPosition(ccp(pButtonAddExp->getContentSize().width/2,pButtonAddExp->getContentSize().height/2));
	pButtonAddExp->addChild(pbuttonlabelAddExp);

	// 升级
	CCMenuItemImage* pButtonLvlUp = SystemData::getMenuItemImageByPlist("ui_horse_btn");
	pButtonLvlUp->setPosition(SystemData::getLayoutPoint("ui_horse_equip_btn_lbl_lvlup_pos"));
	pButtonLvlUp->setTarget(this,menu_selector(HorseEquipEnhancePanel::menuLevelUpCallBack));
	pMenu->addChild(pButtonLvlUp);
	CCLabelTTF* pbuttonlabelLvlUp = SystemData::getLabelTTF("ui_horse_equip_btn_lbl_lvlup");
	pbuttonlabelLvlUp->setColor(ccWHITE);
	pbuttonlabelLvlUp->setFontSize(18);
	pbuttonlabelLvlUp->setPosition(ccp(pButtonLvlUp->getContentSize().width/2,pButtonLvlUp->getContentSize().height/2));
	pButtonLvlUp->addChild(pbuttonlabelLvlUp);

	// 取消
	CCMenuItemImage* pButtonCancel = SystemData::getMenuItemImageByPlist("ui_horse_btn");
	pButtonCancel->setPosition(SystemData::getLayoutPoint("ui_horse_equip_btn_lbl_cancel_pos"));
	pButtonCancel->setTarget(this,menu_selector(HorseEquipEnhancePanel::menuCancelCallBack));
	pMenu->addChild(pButtonCancel);
	CCLabelTTF* pbuttonlabelCancel = SystemData::getLabelTTF("ui_horse_equip_btn_lbl_cancel");
	pbuttonlabelCancel->setColor(ccWHITE);
	pbuttonlabelCancel->setFontSize(18);
	pbuttonlabelCancel->setPosition(ccp(pButtonCancel->getContentSize().width/2,pButtonCancel->getContentSize().height/2));
	pButtonCancel->addChild(pbuttonlabelCancel);

	// 右上角关闭
	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("ui_float_menu_close");
	pClose->setPosition(ccp(pborder->getContentSize().width-15,pTitle->getPositionY()+2));
	pClose->setTarget(this,menu_selector(HorseEquipEnhancePanel::menuCancelCallBack));
	pMenu->addChild(pClose);

// 	CCLabelTTF* pCLBZ=SystemData::getLabelTTF("ui_petadvance_text3");
// 	pCLBZ->setHorizontalAlignment(kCCTextAlignmentLeft);
// 	pCLBZ->setColor(ccYELLOW);
// 	pCLBZ->setFontSize(18);
// 	CPCheckBox* pBZBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pCLBZ);
// 	pBZBox->setTag(tag_vcoin);
// 	pBZBox->setHandler(this,menu_selector(HorseEquipEnhancePanel::blockCallBack));
// 	pBZBox->setPosition(ccp(400,100));
// 	pMenu->addChild(pBZBox);

	initInfo();

	//------------------------------------------------------------------------------------------------------------------------------------//

	return true;
}
void HorseEquipEnhancePanel::initEquip()
{
	m_pEquipLayer->removeAllChildren();

	int proplv = HeroData::getProp(Entity::attr_horse_equip1_level + (m_equipindex - 1) * 2);
	if (proplv == 0)
	{
		return;
	}

	// 装备
	CCSprite *base=SystemData::getSpriteByPlist("ui_horse_base");
	base->setPosition(SystemData::getLayoutPoint("ui_horse_equip_equip_pos"));
	base->setAnchorPoint(CCPointZero);
	m_pEquipLayer->addChild(base);

	//添加装备层级特效
	const int coloreffect[ItemQuality_Max] = {0, Effect::effect_equipcolor1, Effect::effect_equipcolor2, Effect::effect_equipcolor3, Effect::effect_equipcolor4, Effect::effect_equipcolor5, Effect::effect_equipcolor6, Effect::effect_equipcolor7};
	int color = 0;
	LuaData::getProp("gdHorseEquipBaseStats", m_equipindex, proplv, "Color", color);
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
	LuaData::getProp("gdHorseEquipBaseStats", m_equipindex, proplv, "Image", itemurl);
	itemurl = LayoutData::getString(CPModuleName::COMMON, "itemIconPath") + itemurl;
	CCSprite* pButton = CCSprite::create(itemurl.c_str());
	pButton->setPosition(ccp(base->getContentSize().width / 2, base->getContentSize().height / 2));
	base->addChild(pButton);

	// 装备属性
	// 装备等级,经验格式是交叉的

	std::map<int, int> mapAttr;
	int attrsize = 0;
	LuaData::getProp_size("gdHorseEquipBaseStats", m_equipindex, proplv, "AttrAdd", attrsize);
	for (int j = 1; j <= attrsize; j++)
	{
		int attr = 0;
		LuaData::getProp("gdHorseEquipBaseStats", m_equipindex, proplv, "AttrAdd", j, "AttrID", attr);
		int value = 0;
		LuaData::getProp("gdHorseEquipBaseStats", m_equipindex, proplv, "AttrAdd", j, "AttrValue", value);
		if (value == 0)
		{
			continue;
		}
		mapAttr[attr] = mapAttr[attr] + value;
	}

	int propindex = 0;
	for (std::map<int, int>::iterator it = mapAttr.begin(); it != mapAttr.end(); it++)
	{
		CCLabelTTF* pLblProp = SystemData::getLabelTTF("XXXX");
		std::string name;
		LuaData::getProp("fm_attr_type_to_name", it->first, name);
		CCString* pStr = CCString::createWithFormat("%s : + %d",name.c_str(), it->second);
		pLblProp->setString(pStr->getCString());
		pLblProp->setColor(ccWHITE);
		pLblProp->setFontSize(18);
		pLblProp->setPosition(ccp(SystemData::getLayoutPoint("ui_horse_equip_prop_pos").x, SystemData::getLayoutPoint("ui_horse_equip_prop_pos").y + propindex * 30));
		pLblProp->setAnchorPoint(CCPointZero);

		m_pEquipLayer->addChild(pLblProp);
		propindex ++;
	}
}

void HorseEquipEnhancePanel::initExp()
{
	int curexp = HeroData::getProp(Entity::attr_horse_equip1_exp + (m_equipindex - 1) * 2);
	int proplv = HeroData::getProp(Entity::attr_horse_equip1_level + (m_equipindex - 1) * 2);
	int maxexp = 0;
	LuaData::getProp("gdHorseEquipBaseStats", m_equipindex, proplv, "UpLevelExp", maxexp);


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

	m_pExppoint->setScaleX(ratio);
	m_pExppoint->setScaleY(0.5);

}

void HorseEquipEnhancePanel::initInfo()
{
	int pangucnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("pangusuipian_id"),ItemPos::Player_Bag_Start);
	m_pLabelPangu->setString(SystemData::intToString(pangucnt).c_str());
	int kaitiancnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("kaitianyu_id"),ItemPos::Player_Bag_Start);
	m_pLabelKaitian->setString(SystemData::intToString(kaitiancnt).c_str());
	m_pLabelVcoin->setString(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str());
}

void HorseEquipEnhancePanel::blockCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag  = pNode->getTag();
		if (tag==tag_vcoin)
		{
			m_bVcoin = !m_bVcoin;
			int vcoin = SystemData::getLayoutValue("宠物极品属性更改消耗元宝");
			if (m_bVcoin)
			{
				int addvcoin = CommonFunction::getReqVcoin( NULL,Type_PetSpec,0);
				vcoin += addvcoin;
			}
			m_pLabelVcoin->setString(SystemData::intToString(vcoin).c_str());
			return;
		}
	}
}

void HorseEquipEnhancePanel::menuAddExpCallBack( CCObject* pSender )
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if (!pNode)
	{
		return;
	}

	CCNode *pMainUI = Game::getGameUI()->getPanel(TAG_MAIN_PANEL);
	std::vector<std::string> vect;
	FloatPanel::show(FloatPanelType::HORSE_EQUIP_ADDEXP, vect, this, floatpanel_selector(HorseEquipEnhancePanel::equipAddExp));

}

void HorseEquipEnhancePanel::menuLevelUpCallBack( CCObject* pSender )
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if (!pNode)
	{
		return;
	}

	CCNode *pMainUI = Game::getGameUI()->getPanel(TAG_MAIN_PANEL);
	std::vector<std::string> vect;
	FloatPanel::show(FloatPanelType::Horse_EQUIP_SJ, vect, this, floatpanel_selector(HorseEquipEnhancePanel::equipLvlUp));
}

void HorseEquipEnhancePanel::menuCancelCallBack( CCObject* pSender )
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if (!pNode)
	{
		return;
	}
	
	this->removeFromParent();
}

void HorseEquipEnhancePanel::equipAddExp(int tag)
{
	if (tag != Button_QD)
	{
		return;
	}
	MsgHorseEquipQiangHuaReq* msg=new MsgHorseEquipQiangHuaReq;
	msg->HorseEquipID = m_equipindex;
	msg->IsUseGold = 1;
	HandleMessage::sendMessage(msg);
}

void HorseEquipEnhancePanel::equipLvlUp(int tag)
{
	if (tag != Button_QD)
	{
		return;
	}
	MsgHorseEquipJinJieReq* msg=new MsgHorseEquipJinJieReq;
	msg->HorseEquipID = m_equipindex;
	msg->IsUseGold = 1;
	HandleMessage::sendMessage(msg);
}

void HorseEquipEnhancePanel::addLevelUpEffect()
{
	EffectSprite* p=EffectSprite::create(Effect::effect_petlvlup,1);
	p->setPosition(ccp((SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").x+SystemData::getLayoutPoint("ui_pet_rightbutton1_pos").x)/2+10,SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").y-90));
	addChild(p); 
}

void HorseEquipEnhancePanel::handleEvent( int channel )
{
	if (channel == EventProtocol::EVENT_HORSE_EQUIP_ADD_EXP)
	{
		initExp();
	}
	else if(channel == EventProtocol::EVENT_HORSE_EQUIP_LEVEL_UP)
	{
		initEquip();
		addLevelUpEffect();
	}
	initInfo();
}
