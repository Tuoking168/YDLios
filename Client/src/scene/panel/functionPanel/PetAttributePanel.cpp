#include "PetAttributePanel.h"
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
#include "userdata/LayoutData.h"
#include "userdata/UserPetData.h"
#include "module/GuideModule.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
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

PetAttributePanel::PetAttributePanel()
{
	m_pMainMenu=NULL;
}


PetAttributePanel::~PetAttributePanel()
{

	CC_SAFE_RELEASE(m_pMainMenu);
}

void PetAttributePanel::setMainMenu(CCLayer* var)
{
	CC_SAFE_RELEASE(m_pMainMenu);
	m_pMainMenu=var;
	CC_SAFE_RETAIN(m_pMainMenu);
}

CCLayer* PetAttributePanel::getMainMenu()
{
	return m_pMainMenu;
}

bool PetAttributePanel::init()
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


	if (GameData::s_user->getUserPetData()->getFirstPet()==NULL)
	{
		CCLayerColor *blackLayer = CCLayerColor::create(ccc4(0, 0, 0, 100));
		blackLayer->setContentSize(CCSizeMake(800,437));
		blackLayer->setPosition(ccp(-400,-8));
		addChild(blackLayer);

		CCLabelTTF* pWarm=SystemData::getLabelTTF("NoPet_text");
		pWarm->setFontSize(20);
		pWarm->setColor(ccORANGE);

		CCScale9Sprite* psbkg = SystemData::getScale9SpriteByPlist("taskcontent_sbkg",pWarm->getContentSize().width+100,pWarm->getContentSize().height+80);
		psbkg->setPosition(ccp(blackLayer->getContentSize().width/2,blackLayer->getContentSize().height/2));
		blackLayer->addChild(psbkg);

		pWarm->setPosition(ccp(psbkg->getContentSize().width/2,psbkg->getContentSize().height/2));
		psbkg->addChild(pWarm);

		pTabelView->setTouchEnabled(false);
		m_nWidth=blackLayer->getContentSize().width;
		m_nHeight=blackLayer->getContentSize().height;
		addCover(blackLayer->getPosition());
	}

	return true;
}

void PetAttributePanel::updateList()
{
	//pTabelView->removeAllChildren();
	CCLayer* layer=PetBaseMenu::create();	
	mHeight=layer->getContentSize().height;
	pTabelView->reloadData();
}


CCSize PetAttributePanel::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(SystemData::getLayoutSize("attribute_PetBase_Content").width,mHeight);
}

CCTableViewCell* PetAttributePanel::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* layer=PetBaseMenu::create();	
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

unsigned int PetAttributePanel::numberOfCellsInTableView(CCTableView *table)
{
	return 1;
}

void PetAttributePanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_PET_UPDDATA)
	{
		//CCLog("Event Recieve");
		updateList();
	}
}



//-----------------------------------------------------------------//


PetBaseMenu::PetBaseMenu():
	mHeight(0),
	m_iCurrentPetiid(0),
	m_pPet(NULL)
{

}

PetBaseMenu::~PetBaseMenu()
{

}

bool PetBaseMenu::init()
{
	m_pPet = GameData::s_user->getUserPetData()->getCurrentPet();
	
	initFirstPart();
	initSecondPart();
	initThirdPart();

	this->setContentSize(CCSizeMake(SystemData::getLayoutSize("attribute_PetBase_Content").width,mHeight));

	return true;
}

void PetBaseMenu::initFirstPart()
{	
	//标题 
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("PetBase_1_contentsize"));	
	CCSprite *ptitle=SystemData::getSpriteByPlist("ui_pet_jichu");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,0));
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);
	if (m_pPet)
	{		
		//准备数据
		std::string str[8]={
			SystemData::intToString(m_pPet->data[Combat::prop_PATK_Max]),
			SystemData::intToString(m_pPet->data[Combat::prop_TATK_Max]),
			SystemData::intToString(m_pPet->data[Combat::prop_MATK_Max]),
			SystemData::intToString(m_pPet->data[Combat::prop_Curse]),
			SystemData::intToString(m_pPet->data[Combat::prop_PDEF_Max]),
			SystemData::intToString(m_pPet->data[Combat::prop_MDEF_Max]),
			SystemData::intToString(m_pPet->data[Combat::prop_MPMax]),
			SystemData::intToString(m_pPet->exdata[Entity::attr_pet_combat_data_num])//需要修改为保存战力的数值
		};

		std::string strlist[8]={
			"pet_wuligongji","pet_daoshugongji","pet_mofagongji","pet_shengming","pet_wulifangyu","pet_mofafangyu","pet_mofa","pet_zhanli"
		};
		int x=0;
		int y=0;
		for (int i=0;i<7;i++)//hide pet combact
		{		
			CCLabelTTF *plabel=SystemData::getLabelTTF(strlist[i]);
			plabel->setFontSize(14);
			plabel->setColor(ccWHITE);
			plabel->setAnchorPoint(CCPointZero);
			plabel->setPosition(ccp(ptitle->getPositionX()-140+x*150,ptitle->getPositionY()-45-y*30));

			CCLabelTTF *pValue=CCLabelTTF::create(str[i].c_str(),"微软雅黑",14);		
			pValue->setColor(ccGREEN);
			pValue->setAnchorPoint(CCPointZero);
			pValue->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width+10,plabel->getPositionY()));
			pLayer->addChild(pValue);	
			pLayer->addChild(plabel);
			y++;
			if (y==4)
			{
				y=0;
				x++;
			}
		}

		CCLabelTTF *plabel=SystemData::getLabelTTF("pet_chongwutexing");
		plabel->setFontSize(14);
		plabel->setColor(ccWHITE);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setPosition(ccp(ptitle->getPositionX()-140,ptitle->getPositionY()-45-4*30));
//		pLayer->addChild(plabel);
		
	}

	pLayer->setAnchorPoint(ccp(0,1));
	pLayer->setPosition(ccp(0,-20));
	mHeight+=pLayer->getContentSize().height;
	this->addChild(pLayer);
}

void PetBaseMenu::initSecondPart()
{
	//标题
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("PetBase_2_contentsize"));
	CCSprite *ptitle=SystemData::getSpriteByPlist("ui_pet_jinjie");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,0));
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);
	if (m_pPet)
	{
		int attrcnt = GameData::s_user->getUserPetData()->getPetAdvanceCnt(m_pPet);

		for (int i = 0;i<attrcnt;i++)
		{
			int advancetype = m_pPet->exdata[Entity::attr_pet_ex_prop_type];
			int c=(int)((int)advancetype >> (8*i) & 255);
			if(c!=0)
			{
				int type=c;
				std::string name;
				LuaData::getProp("attr_type_to_name",c,name);
				int data = m_pPet->exdata[Entity::attr_pet_ex_prop_type+attrcnt-i];
				float combovalue;
				CCString* pStr;
				if (type==Combat::prop_Death_Recovery_Percent || type==Combat::prop_Health_Recovery_Point || type==Combat::prop_Magic_Recovery_Point || type==Combat::prop_Posion_Recovery_Point || type==Combat::prop_Magic_Hit|| type==Combat::prop_Magic_Dodge || type==Combat::prop_Posion_Dodge)
				{
					combovalue=(float)data;
					combovalue=combovalue/100;
					pStr=CCString::createWithFormat("%s:+%.2f%%",name.c_str(),combovalue);
				}
				else
				{
					pStr=CCString::createWithFormat("%s:+%d",name.c_str(),data);
				}

				CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",18);
				pLabel->setPosition(ccp(ptitle->getPositionX()-140,ptitle->getPositionY()-40*(i+1)));
				pLabel->setAnchorPoint(CCPointZero);
				pLayer->addChild(pLabel);
			}
		}

		for (int i = attrcnt;i<3;i++)
		{
			CCLabelTTF* pLabel=SystemData::getLabelTTF("ui_petadvance_text4");
			pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
			pLabel->setAnchorPoint(CCPointZero);
			pLabel->setColor(ccWHITE);
			pLabel->setPosition(ccp(ptitle->getPositionX()-140,ptitle->getPositionY()-40*(i+1)));
			pLabel->setFontSize(18);
			pLayer->addChild(pLabel);
		}

		GeneralMenu* pMenu = GeneralMenu::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		pLayer->addChild(pMenu);

		CCMenuItemImage* pButton = SystemData::getMenuItemImageByPlist("ui_pet_topbutton2");
		pButton->setAnchorPoint(CCPointZero);
		pButton->setPosition(ccp(ptitle->getPositionX()+pButton->getContentSize().width/2,ptitle->getPositionY()-pButton->getContentSize().height-ptitle->getContentSize().height));
		pButton->setTag(tag_advance);
		pButton->setTarget(this,menu_selector(PetBaseMenu::menuCallBack));
		pMenu->addChild(pButton);

		CCLabelTTF* pLabel = SystemData::getLabelTTF("ui_petadvance_text");
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
		pButton->addChild(pLabel);

		if (attrcnt==0)
		{
			//pButton->setEnabled(false);
		}
	}	


	pLayer->setAnchorPoint(ccp(0,1));
	pLayer->setPosition(ccp(0,-20-SystemData::getLayoutSize("PetBase_1_contentsize").height));		
	mHeight+=pLayer->getContentSize().height;
	this->addChild(pLayer); 
}

void PetBaseMenu::initThirdPart()
{
	//标题
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("PetBase_3_contentsize"));
	CCSprite *ptitle=SystemData::getSpriteByPlist("ui_pet_jipin");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,0));
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);
	if (m_pPet)
	{
		int specialattr = m_pPet->exdata[Entity::attr_pet_top_prop_type];
		int specialdata = m_pPet->exdata[Entity::attr_pet_top_prop];
		if (specialattr!=0)
		{
			std::string name;
			LuaData::getProp("attr_type_to_name",specialattr,name);
			CCString* pStr=NULL;
			if (specialattr==Combat::prop_Death_Recovery_Percent || specialattr==Combat::prop_Damage_to_Magic)
			{
				pStr = CCString::createWithFormat("%s : + %.2f%% ",name.c_str(),(float)specialdata/(float)100);
			}
			else
			{
				pStr = CCString::createWithFormat("%s : + %d ",name.c_str(),specialdata);
			}
			CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",15);
			pLabel->setPosition(ccp(ptitle->getPositionX()-140,ptitle->getPositionY()-45));
			pLabel->setAnchorPoint(CCPointZero);
			pLayer->addChild(pLabel);
		}
		else
		{
			CCLabelTTF* pLabel=SystemData::getLabelTTF("ui_petadvance_text4"); 
			pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
			pLabel->setAnchorPoint(CCPointZero);
			pLabel->setColor(ccWHITE);
			pLabel->setPosition(ccp(ptitle->getPositionX()-140,ptitle->getPositionY()-45));
			pLabel->setFontSize(18);
			pLayer->addChild(pLabel);
		}
		/*std::string str[2]={
			SystemData::intToString(GameData::s_user->m_pMainRole->Honour),
			SystemData::intToString(GameData::s_user->m_pMainRole->PK_NUM)		
		};


		std::string strlist[2]={
			"Base_3_rongyu","Base_3_PKzhi"
		};
		int x=0;
		int y=0;
		for (int i=0;i<2;i++)
		{		
			CCLabelTTF *plabel=SystemData::getLabelTTF(strlist[i]);
			plabel->setFontSize(14);
			plabel->setAnchorPoint(CCPointZero);
			plabel->setColor(ccWHITE);
			plabel->setPosition(ccp(ptitle->getPositionX()-140,ptitle->getPositionY()-45-y*30));

			CCLabelTTF *pValue=CCLabelTTF::create(str[i].c_str(),"微软雅黑",14);		
			pValue->setColor(ccGREEN);
			pValue->setAnchorPoint(CCPointZero);
			pValue->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width+10,plabel->getPositionY()));
			pLayer->addChild(pValue);

			pLayer->addChild(plabel);
			y++;
		}*/
		GeneralMenu* pMenu = GeneralMenu::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		pLayer->addChild(pMenu);

		CCMenuItemImage* pButton = SystemData::getMenuItemImageByPlist("ui_pet_topbutton2");
		pButton->setAnchorPoint(CCPointZero);
		pButton->setPosition(ccp(ptitle->getPositionX()+pButton->getContentSize().width/2,ptitle->getPositionY()-pButton->getContentSize().height-ptitle->getContentSize().height));
		pButton->setTag(tag_speattr);
		pButton->setTarget(this,menu_selector(PetBaseMenu::menuCallBack));
		pMenu->addChild(pButton);

		CCLabelTTF* pLabel = SystemData::getLabelTTF("ui_petspeattr_text");
		pLabel->setColor(ccWHITE);
		pLabel->setFontSize(18);
		pLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
		pButton->addChild(pLabel);

		if (specialattr==0)
		{
			//pButton->setEnabled(false);
		}
	}
	pLayer->setAnchorPoint(ccp(0,1));
	pLayer->setPosition(ccp(0,-20-SystemData::getLayoutSize("PetBase_1_contentsize").height-SystemData::getLayoutSize("PetBase_2_contentsize").height));
	mHeight+=pLayer->getContentSize().height;
	this->addChild(pLayer);
}

void PetBaseMenu::menuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		if (tag == tag_advance)
		{
			Game::getGameUI()->showPetAdvance();
		}
		else if (tag == tag_speattr)
		{
			Game::getGameUI()->showPetSpeAttr();
		}
	}
}



//----------------------------------------------------------------//


//////------------------------------------------------------------------------------------------------------------------------//

PetAdvancedPanel::PetAdvancedPanel():
	m_bVcoin(false),
	m_pMenu(NULL),
	m_iAttrCnt(0),
	m_pLabelVcoin(NULL)
{
	for (int i = 0;i<3;i++)
	{
		m_bBlock[i] = false;
	}
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

PetAdvancedPanel::~PetAdvancedPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);

}

bool PetAdvancedPanel::init()
{
	if (!PartPanel::init())
	{
		return false;
	}
	CCSprite* pBkg = SystemData::getSpriteByPlist("ui_petadvance_bkg");
	pBkg->setAnchorPoint(CCPointZero);
	pBkg->setPosition(CCPointZero);
	addChild(pBkg);

	m_nHeight = pBkg->getContentSize().height;
	m_nWidth = pBkg->getContentSize().width;
	addCover();


	CCScale9Sprite* pborder = SystemData::getScale9SpriteByPlist("ui_petadvance_border",SystemData::getLayoutValue("ui_petadvance_border.w"),SystemData::getLayoutValue("ui_petadvance_border.h"));
	pborder->setAnchorPoint(CCPointZero);
	pBkg->addChild(pborder);

	CCLabelTTF* pTitle = SystemData::getLabelTTF("ui_petadvance_title");
	pTitle->setColor(ccYELLOW);
	pTitle->setFontSize(20);
	pTitle->setPosition(ccp(pBkg->getContentSize().width/2,pBkg->getContentSize().height-25));
	pBkg->addChild(pTitle);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pButton = SystemData::getMenuItemImageByPlist("ui_pet_topbutton2");
	pButton->setPosition(ccp(pBkg->getContentSize().width/2,45));
	pButton->setTarget(this,menu_selector(PetAdvancedPanel::menuCallBack));
	pMenu->addChild(pButton);

	CCLabelTTF* pbuttonlabel = SystemData::getLabelTTF("ui_petadvance_text5");
	pbuttonlabel->setColor(ccWHITE);
	pbuttonlabel->setFontSize(18);
	pbuttonlabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
	pButton->addChild(pbuttonlabel);

	m_iAttrCnt = GameData::s_user->getUserPetData()->getPetAdvanceCnt(GameData::s_user->getUserPetData()->getCurrentPet());

	CCLabelTTF* pLabel2 = SystemData::getLabelTTF("ui_petadvance_text2");
	pLabel2->setPosition(SystemData::getLayoutPoint("ui_petadvance_text2"));
	pLabel2->setFontSize(18);
	pLabel2->setColor(ccYELLOW);
	addChild(pLabel2);

	// 材料
	CCSprite* pSprite  = SystemData::getSpriteByPlist("forging_result");
	pSprite->setPosition(ccp(pLabel2->getPositionX(),pLabel2->getPositionY()-60));
	addChild(pSprite);

	CCLabelTTF* pCLBZ=SystemData::getLabelTTF("ui_petadvance_text3");
	pCLBZ->setHorizontalAlignment(kCCTextAlignmentLeft);
	pCLBZ->setColor(ccYELLOW);
	pCLBZ->setFontSize(18);
	CPCheckBox* pBZBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pCLBZ);
	//pBZBox->setAnchorPoint(CCPointZero);
	pBZBox->setTag(tag_vcoin);
	pBZBox->setHandler(this,menu_selector(PetAdvancedPanel::blockCallBack));
	pBZBox->setPosition(ccp(pSprite->getPositionX(),pSprite->getPositionY()-75));
	addChild(pBZBox);

	CCLabelTTF* pmoney = SystemData::getLabelTTF("ui_petadvance_text6");
	pmoney->setAnchorPoint(CCPointZero);
	pmoney->setPosition(ccp(pBZBox->getPositionX()-pBZBox->getContentSize().width/2,pBZBox->getPositionY()-50));
	pmoney->setColor(ccWHITE);
	pmoney->setFontSize(18);
	addChild(pmoney);

	m_pLabelVcoin = CCLabelTTF::create("0","",18);
	m_pLabelVcoin->setAnchorPoint(CCPointZero);
	m_pLabelVcoin->setPosition(ccp(pmoney->getContentSize().width+pmoney->getPositionX(),pmoney->getPositionY()));
	addChild(m_pLabelVcoin);

	m_pMenu = GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("ui_float_menu_close");
	pClose->setPosition(ccp(pborder->getContentSize().width-15,pTitle->getPositionY()+2));
	pClose->setTarget(this,menu_selector(PetAdvancedPanel::menuCallBack));
	pClose->setTag(tag_cancel);
	pMenu->addChild(pClose);

	initInfo();
	return true;
}

void PetAdvancedPanel::blockCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag  = pNode->getTag();
		if (tag==tag_vcoin)
		{
			m_bVcoin = !m_bVcoin;
			int vcoin = SystemData::getLayoutValue("宠物进阶消耗元宝");
			if (m_bVcoin)
			{
				int addvcoin = CommonFunction::getReqVcoin( NULL,Type_PetAdvance,0);
				vcoin += addvcoin;
			}
			m_pLabelVcoin->setString(SystemData::intToString(vcoin).c_str());
			return;
		}
		else if (tag>=0 && tag<3)
		{
			m_bBlock[tag] = !m_bBlock[tag] ;
		}
	}
}

void PetAdvancedPanel::menuCallBack( CCObject* pSender )
{
	//提升
	UserPet* pPet = GameData::s_user->getUserPetData()->getCurrentPet();
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if (pNode)
	{
		int  tag = pNode->getTag();
		if (tag==tag_cancel)
		{
			this->removeFromParent();
			return;
		}
	}
	 
	
	if (pPet)
	{
		if (m_iAttrCnt!=0 && (m_bBlock[0] || m_bBlock[1] ||  m_bBlock[2]))
		{
			int rtv = CommonFunction::IsEnoughVcoin(NULL,Type_PetAdvance,0);
			if (rtv==Error::Success)
			{
				CommonFunction::sendmsgPetAdvance( pPet->iid, m_bBlock[0], m_bBlock[1],  m_bBlock[2], (int)m_bVcoin);
			}
			else
			{
				CPEventHelper::uiNotify("","",rtv);
			}
		}
		else
		{
			CPEventHelper::uiNotify("","",Error::NotAdvanceAttr);
		}
	}
}

void PetAdvancedPanel::initInfo()
{
	m_pMenu->removeAllChildren();

	CCLabelTTF* pLabel1 = SystemData::getLabelTTF("ui_petadvance_text1");
	pLabel1->setPosition(SystemData::getLayoutPoint("ui_petadvance_text1"));
	pLabel1->setFontSize(18);
	pLabel1->setColor(ccYELLOW);
	m_pMenu->addChild(pLabel1);

	//属性
	for (int i = 0;i<m_iAttrCnt;i++)
	{
		UserPet* pPet = GameData::s_user->getUserPetData()->getCurrentPet();
		if (pPet)
		{
			int advancetype = pPet->exdata[Entity::attr_pet_ex_prop_type];
			int c=(int)((int)advancetype >> (8*i) & 255);
			if(c!=0)
			{
				int type=c;
				std::string name;
				LuaData::getProp("attr_type_to_name",c,name);
				//LuaData::getProp("gdEquipEvaluate",c,"attrtype",type);
				int data = pPet->exdata[Entity::attr_pet_ex_prop_type+m_iAttrCnt-i];
				float combovalue;
				CCString* pStr;
				if (type==Combat::prop_Death_Recovery_Percent || type==Combat::prop_Health_Recovery_Point || type==Combat::prop_Magic_Recovery_Point || type==Combat::prop_Posion_Recovery_Point || type==Combat::prop_Magic_Hit|| type==Combat::prop_Magic_Dodge || type==Combat::prop_Posion_Dodge)
				{
					combovalue=(float)data;
					combovalue=combovalue/100;
					pStr=CCString::createWithFormat("%s:+%.2f%%",name.c_str(),combovalue);
				}
				else
				{
					pStr=CCString::createWithFormat("%s:+%d",name.c_str(),data);
				}

				CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",18);
				pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
				CPCheckBox* pBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pLabel);
				pBox->setAnchorPoint(CCPointZero);
				pBox->setTag(i);
				pBox->setHandler(this,menu_selector(PetAdvancedPanel::blockCallBack));
				pBox->setPosition(ccp(pLabel1->getPositionX()-pLabel1->getContentSize().width/2,pLabel1->getPositionY()-40*(i+1)));
				m_pMenu->addChild(pBox);
				pBox->setChecked(m_bBlock[pBox->getTag()]);
			}
		}		
	}

	for (int i = m_iAttrCnt;i<3;i++)
	{
		CCLabelTTF* pLabel=SystemData::getLabelTTF("ui_petadvance_text4");
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
		pLabel->setAnchorPoint(ccp(0.5,0));
		pLabel->setColor(ccWHITE);
		pLabel->setPosition(ccp(pLabel1->getPositionX(),pLabel1->getPositionY()-40*(i+1)));
		pLabel->setFontSize(18);
		m_pMenu->addChild(pLabel);
	}

	// 材料
	CCMenuItemImage* pIcon = CommonFunction::getReqPetAdvanceItem();
	pIcon->setTarget(this,menu_selector(PetAdvancedPanel::ItemCallBack));
	pIcon->setPosition(ccp(SystemData::getLayoutPoint("ui_petadvance_text2").x,SystemData::getLayoutPoint("ui_petadvance_text2").y-60));
	m_pMenu->addChild(pIcon);

	int vcoin = SystemData::getLayoutValue("宠物进阶消耗元宝");
	if (m_bVcoin)
	{
		int addvcoin = CommonFunction::getReqVcoin( NULL,Type_PetAdvance,0);
		vcoin += addvcoin;
	}
	m_pLabelVcoin->setString(SystemData::intToString(vcoin).c_str());
}

void PetAdvancedPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncPetExPropDataNotify")
		{
			int data1 = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (data1==Entity::attr_pet_ex_prop_type|| data1==Entity::attr_pet_ex_prop_one|| data1==Entity::attr_pet_ex_prop_two|| data1==Entity::attr_pet_ex_prop_three)
			{
				initInfo();
			}
		}
	}
}

void PetAdvancedPanel::checkAdvanceCnt()
{
	UserPet* pPet = GameData::s_user->getUserPetData()->getCurrentPet();
	if (pPet)
	{
		int advancetype = pPet->exdata[Entity::attr_pet_ex_prop_type];
		int count= 0;
		int n=0;
		for (int b=0;b<3;b++)
		{
			int c=(int)((int)advancetype >> (8*b) & 255);
			if(c!=0)
			{
				count++;
			}
		}
		m_iAttrCnt = count;
		return;
	}
	m_iAttrCnt = 0;
}

void PetAdvancedPanel::ItemCallBack( CCObject* pSender )
{
	CCNode* pImage=dynamic_cast<CCNode*>(pSender);
	if (pImage)
	{
		UserItem* pItem=(UserItem*)pImage->getUserData();
		Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
	}
}

//////------------------------------------------------------------------------------------------------------------------------//

PetSpeAttrPanel::PetSpeAttrPanel():
	m_bBlock(false),
	m_pMenu(NULL),
	pSprite(NULL),
	m_pLabelVcoin(NULL),
	m_bVcoin(false)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);

}

PetSpeAttrPanel::~PetSpeAttrPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);

}

bool PetSpeAttrPanel::init()
{
	if (!PartPanel::init())
	{
		return false; 
	}	
	
	CCSprite* pBkg = SystemData::getSpriteByPlist("ui_petadvance_bkg");
	pBkg->setAnchorPoint(CCPointZero);
	pBkg->setPosition(CCPointZero);
	addChild(pBkg);

	m_nHeight = pBkg->getContentSize().height;
	m_nWidth = pBkg->getContentSize().width;

	addCover();

	CCScale9Sprite* pborder = SystemData::getScale9SpriteByPlist("ui_petadvance_border",SystemData::getLayoutValue("ui_petadvance_border.w"),SystemData::getLayoutValue("ui_petadvance_border.h"));
	pborder->setAnchorPoint(CCPointZero);
	pBkg->addChild(pborder);

	//------------------------------------------------------------------------------------------------------------------------------------//
	CCLabelTTF* pTitle = SystemData::getLabelTTF("ui_petspeattr_title");
	pTitle->setColor(ccYELLOW);
	pTitle->setFontSize(20);
	pTitle->setPosition(ccp(pBkg->getContentSize().width/2,pBkg->getContentSize().height-25));
	pBkg->addChild(pTitle);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pButtonChange = SystemData::getMenuItemImageByPlist("ui_pet_topbutton2");
	pButtonChange->setPosition(ccp(pBkg->getContentSize().width/6,45));
	pButtonChange->setTag(tag_change);
	pButtonChange->setTarget(this,menu_selector(PetSpeAttrPanel::menuCallBack));
	pMenu->addChild(pButtonChange);

	CCMenuItemImage* pButtonCancel = SystemData::getMenuItemImageByPlist("ui_pet_topbutton2");
	pButtonCancel->setPosition(ccp(pBkg->getContentSize().width*5/6,45));
	pButtonCancel->setTag(tag_cancel);
	pButtonCancel->setTarget(this,menu_selector(PetSpeAttrPanel::menuCallBack));
	pMenu->addChild(pButtonCancel);

	CCLabelTTF* pbuttonlabelChange = SystemData::getLabelTTF("ui_petspeattr_text");
	pbuttonlabelChange->setColor(ccWHITE);
	pbuttonlabelChange->setFontSize(18);
	pbuttonlabelChange->setPosition(ccp(pButtonChange->getContentSize().width/2,pButtonChange->getContentSize().height/2));
	pButtonChange->addChild(pbuttonlabelChange);

	CCLabelTTF* pbuttonlabelCancel = SystemData::getLabelTTF("ui_petadvance_cancel");
	pbuttonlabelCancel->setColor(ccWHITE);
	pbuttonlabelCancel->setFontSize(18);
	pbuttonlabelCancel->setPosition(ccp(pButtonCancel->getContentSize().width/2,pButtonCancel->getContentSize().height/2));
	pButtonCancel->addChild(pbuttonlabelCancel);
	

//	m_iAttrCnt = 1;
	//当前极品属性
	//PetSpeAttrPanel* p_CurSpe = NULL;
//	p_CurSpe = CCLabelTTF::create(NULL);


	CCLabelTTF* pLabel2 = SystemData::getLabelTTF("ui_petspeattr_curjpsx");
	pLabel2->setPosition(ccp(pBkg->getContentSize().width/6,SystemData::getLayoutPoint("ui_petadvance_text2").y));
	pLabel2->setFontSize(18);
	pLabel2->setColor(ccYELLOW);
	addChild(pLabel2);

	// 材料
	pSprite  = SystemData::getSpriteByPlist("forging_result");
	pSprite->setPosition(ccp(pLabel2->getPositionX(),pLabel2->getPositionY()-150));
	addChild(pSprite);
		
    CCLabelTTF* pXYCL=SystemData::getLabelTTF("ui_petadvance_text2");
	pXYCL->setHorizontalAlignment(kCCTextAlignmentLeft);
	pXYCL->setColor(ccYELLOW);
	pXYCL->setFontSize(18);
	pXYCL->setPosition(ccp(pSprite->getPositionX(),pSprite->getPositionY()+45));
	addChild(pXYCL);

	CCLabelTTF* pCLBZ=SystemData::getLabelTTF("ui_petadvance_text3");
	pCLBZ->setHorizontalAlignment(kCCTextAlignmentLeft);
	pCLBZ->setColor(ccYELLOW);
	pCLBZ->setFontSize(18);
	CPCheckBox* pBZBox=CPCheckBox::create(SystemData::getMenuItemImageByPlist("ui_setting_unSelectBtn"),SystemData::getSpriteByPlist("ui_setting_isSelectBtn"),pCLBZ);
//	pBZBox->setAnchorPoint(CCPointZero);
	pBZBox->setTag(tag_vcoin);
	pBZBox->setHandler(this,menu_selector(PetSpeAttrPanel::blockCallBack));
	pBZBox->setPosition(ccp(400,pSprite->getPositionY()-35));
	addChild(pBZBox);
	
	CCLabelTTF* pmoney = SystemData::getLabelTTF("ui_petadvance_text6");
	pmoney->setAnchorPoint(CCPointZero);
	pmoney->setPosition(ccp(pBZBox->getPositionX()-pBZBox->getContentSize().width/2,pBZBox->getPositionY()+40));
	pmoney->setColor(ccWHITE);
	pmoney->setFontSize(18);
	addChild(pmoney);

	m_pLabelVcoin = CCLabelTTF::create("0","",18);
	m_pLabelVcoin->setAnchorPoint(CCPointZero);
	m_pLabelVcoin->setPosition(ccp(pmoney->getContentSize().width+pmoney->getPositionX(),pmoney->getPositionY()));
	addChild(m_pLabelVcoin);

	m_pMenu = GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("ui_float_menu_close");
	pClose->setPosition(ccp(pborder->getContentSize().width-15,pTitle->getPositionY()+2));
	pClose->setTarget(this,menu_selector(PetSpeAttrPanel::menuCallBack));
	pClose->setTag(tag_cancel);
	pMenu->addChild(pClose);

	initInfo();

	//------------------------------------------------------------------------------------------------------------------------------------//

	return true;
}

void PetSpeAttrPanel::blockCallBack( CCObject* pSender )
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

void PetSpeAttrPanel::menuCallBack( CCObject* pSender )
{
	
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		if (tag==tag_cancel)
		{
			this->removeFromParent();
		}
		else if (tag==tag_change)
		{
			UserPet* pPet = GameData::s_user->getUserPetData()->getCurrentPet();
			if (pPet)
			{
				int rtv = CommonFunction::IsEnoughVcoin(NULL,Type_PetSpec,0);
				if (rtv==Error::Success)
				{
					CommonFunction::sendmsgPetSpeAttr( pPet->iid, (int)m_bVcoin);
				}
				else
				{
					CPEventHelper::uiNotify("","",rtv);
				}
			}
		}
	}
}

void PetSpeAttrPanel::initInfo()
{
	m_pMenu->removeAllChildren();

	UserPet* pPet = GameData::s_user->getUserPetData()->getCurrentPet();
	if (pPet)
	{
		int specialattr = pPet->exdata[Entity::attr_pet_top_prop_type];
		int specialdata = pPet->exdata[Entity::attr_pet_top_prop];
		if (specialattr!=0)
		{
			std::string name;
			LuaData::getProp("attr_type_to_name",specialattr,name);
			CCString* pStr=NULL;
			pStr = CCString::createWithFormat("%s : + %d ",name.c_str(),specialdata);
			if (specialattr==Combat::prop_Damage_to_Magic || specialattr==Combat::prop_Death_Recovery_Percent)
			{
				float d = (float)specialdata/(float)100;
				pStr = CCString::createWithFormat("%s : + %.2f%% ",name.c_str(),d);
			}
			
			CCLabelTTF* pLabel=CCLabelTTF::create(pStr->getCString(),"",15);
			pLabel->setPosition(ccp(m_nWidth/2,SystemData::getLayoutPoint("ui_petadvance_text2").y));
			pLabel->setAnchorPoint(CCPointZero);
			m_pMenu->addChild(pLabel);
		}
		else
		{
			CCLabelTTF* pLabel=SystemData::getLabelTTF("ui_petadvance_text4");
			pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
			pLabel->setAnchorPoint(CCPointZero);
			pLabel->setColor(ccWHITE);
			pLabel->setPosition(ccp(m_nWidth/2,SystemData::getLayoutPoint("ui_petadvance_text2").y));
			pLabel->setFontSize(18);
			m_pMenu->addChild(pLabel);
		}
	}

	// 材料
	CCMenuItemImage* pIcon = CommonFunction::getReqPetSpeItem();
	pIcon->setTarget(this,menu_selector(PetSpeAttrPanel::ItemCallBack));
	pIcon->setPosition(pSprite->getPosition());
	m_pMenu->addChild(pIcon);

	int vcoin = SystemData::getLayoutValue("宠物极品属性更改消耗元宝");
	if (m_bVcoin)
	{
		int addvcoin = CommonFunction::getReqVcoin( NULL,Type_PetSpec,0);
		vcoin += addvcoin;
	}
	m_pLabelVcoin->setString(SystemData::intToString(vcoin).c_str());
}

void PetSpeAttrPanel::ItemCallBack( CCObject* pSender )
{

	CCNode* pImage=dynamic_cast<CCNode*>(pSender);
	if (pImage)
	{
		UserItem* pItem=(UserItem*)pImage->getUserData();
		Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
	}
}

void PetSpeAttrPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncPetExPropDataNotify")
		{
			int data1 = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (data1==Entity::attr_pet_top_prop_type || data1==Entity::attr_pet_top_prop)
			{
				initInfo();
			}
		}
	}
}

///////////////////////////////////////////宠物转生////////////////////////////////////////////
UserPet* PetReborn::m_pUserPet = NULL;
PetReborn::PetReborn()
	:m_pTopList(NULL)
	,m_pUserPet2(NULL)
	,rebornDesc(NULL)
	,mList(NULL)
	,mCurrentIndex(0)
	,hasNo(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE,this);
}

PetReborn::~PetReborn()
{
	CPEvtDispatcher.removeEventListener(this);
}

bool PetReborn::init()
{
	if (!PartPanel::init())
	{
		return false;
	}
	initUI();
	initButton();
	initPetDesc();
	initItemPet();
	return true;
}

void PetReborn::initUI()
{
	CCSprite* pBkg = SystemData::getSpriteByPlist("ui_petadvance_bkg");
	pBkg->setAnchorPoint(CCPointZero);
	pBkg->setPosition(CCPointZero);
	addChild(pBkg);

	m_nHeight = pBkg->getContentSize().height;
	m_nWidth = pBkg->getContentSize().width;

	addCover();

	CCLabelTTF* pTitle = SystemData::getLabelTTF("ui_petreborn_title");
	pTitle->setColor(ccYELLOW);
	pTitle->setFontSize(20);
	pTitle->setPosition(ccp(pBkg->getContentSize().width/2,pBkg->getContentSize().height-25));
	pBkg->addChild(pTitle);

	CCScale9Sprite* pSprite=SystemData::getScale9SpriteByPlist("ui_pet_fengetiao",
		SystemData::getLayoutValue("ui_pet_fengetiao_size.w"),SystemData::getLayoutValue("ui_pet_fengetiao_size.h"));
	pSprite->setAnchorPoint(CCPointZero);
	pSprite->setPosition(SystemData::getLayoutPoint("ui_pet_fengetiao_pos"));
	addChild(pSprite);

	m_pTopList=GeneralMenu::create();
	m_pTopList->setAnchorPoint(CCPointZero);
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	GeneralMenu *closeMenu = GeneralMenu::create();
	closeMenu->setAnchorPoint(CCPointZero);
	closeMenu->setPosition(CCPointZero);
	addChild(closeMenu);

	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("ui_float_menu_close");
	pClose->setPosition(ccp(pBkg->getContentSize().width-25,pTitle->getPositionY()+2));
	pClose->setTarget(this,menu_selector(PetReborn::close));
	closeMenu->addChild(pClose);

	CCPoint point1 = SystemData::getLayoutPoint("ui_pet_pButton1_pos");
	CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("ui_pet_huodeshuxing").c_str(),0);
	std::string str_rdsc = SystemData::getLayoutString(pStr->getCString());
	rebornDesc = CCLabelTTF::create();
	rebornDesc->setColor(ccWHITE);
	rebornDesc->setFontSize(14);
	rebornDesc->setAnchorPoint(ccp(0,0.5));
	rebornDesc->setPosition(ccp(point1.x+45,point1.y+20-15));
	rebornDesc->setString(str_rdsc.c_str());
	m_pTopList->addChild(rebornDesc);

	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUIDE, "beiXuanPetList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::GUIDE, "beiXuanPetListItem");
	mList = CPItemComponents::create(listSize, new CPLayoutList(itemSize, false));
	mList->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "beiXuanPetList"));
	m_pTopList->addChild(mList);

//	mList->setCurrentIndex(mCurrentIndex);

}

void PetReborn::initPetDesc()
{
	const std::string desc = LayoutData::getString(CPModuleName::GUIDE, "pet_reborn_notice");
	const CCSize descSize = CCSizeMake(290,40);
	CPRichText *descText = RichTextUtils::getRichText(desc, 16, descSize.width, descSize.height);
	descText->setPosition(SystemData::getLayoutPoint("ui_pet_notice_pos"));
	addChild(descText);

	hasNo = CCLabelTTF::create();
	hasNo->setAnchorPoint(ccp(0,0.5));
	hasNo->setPosition(SystemData::getLayoutPoint("ui_pet_pButton2_pos"));
	m_pTopList->addChild(hasNo);
}

void PetReborn::initButton()
{
	CCMenuItemImage* pReborn = SystemData::getMenuItemImageByPlist("forging_button3");
	pReborn->setTarget(this,menu_selector(PetReborn::onreborn));
	pReborn->setPosition(SystemData::getLayoutPoint("ui_pet_btnzhuansheng_pos"));
	m_pTopList->addChild(pReborn);

	CCLabelTTF* pUpLevelLabel = SystemData::getLabelTTF("ui_pet_petkszhuansheng");
	pUpLevelLabel->setFontSize(18);
	pUpLevelLabel->setColor(ccWHITE);
	pUpLevelLabel->setPosition(SystemData::getLayoutPoint("ui_pet_btnzhuansheng_pos"));
	m_pTopList->addChild(pUpLevelLabel);
}

void PetReborn::onreborn( CCObject* pSender )
{
	UserPet* userPet = getPet();
//	m_pUserPet = GameData::s_user->getUserPetData()->getCurrentPet();
	//判断第二只宠物
//	m_pUserPet2 = GameData::s_user->getUserPetData()->getNextPet();
	if (userPet && m_pUserPet2)
	{
		int iid_1 = m_pUserPet->iid;
		int iid_2 = m_pUserPet2->iid;
		MsgpetRebornRequest* msg = new MsgpetRebornRequest;
		msg->PetID = iid_1;
		msg->BeGobbleupPetID = iid_2;
		HandleMessage::sendMessage(msg);
	}
	else
	{
		CPEventHelper::uiNotify("","",Error::NotEnoughCondition);
		return;
	}
}

void PetReborn::close( CCObject* pSender )
{
	this->removeFromParent();
}

void PetReborn::initItemPet()
{
	CCSprite* pButton1 = SystemData::getSpriteByPlist("forging_base");
	pButton1->setPosition(SystemData::getLayoutPoint("ui_pet_pButton1_pos"));
	m_pTopList->addChild(pButton1);

	mList->setCurrentIndex(mCurrentIndex);
	UserPet* userPet = getPet();
	CCPoint point1 = SystemData::getLayoutPoint("ui_pet_pButton1_pos");
	int pic_sid = 0;
	//获得转生次数
	int rebornLV = 0;
	rebornLV = userPet->exdata[Entity::attr_pet_reborn_cnt];
	std::string headimgid = "headImageID_n";
	if (rebornLV > 0)
	{
		headimgid = "headImageID_s";
	}
	LuaData::getProp("gdPets",userPet->sid,headimgid,pic_sid);
	UserItem* pUserItem = CommonFunction::createNewItem(pic_sid);
	CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
	pItem->setTarget(this,menu_selector(PetReborn::itemClickCallBack));
	pItem->setPosition(SystemData::getLayoutPoint("ui_pet_pButton1_pos"));
	m_pTopList->addChild(pItem);

	int number=0;
	number=GameData::s_user->getUserPetData()->getPetNumByIid(userPet->iid)+1;
	std::string str_name = "";
	LuaData::getProp("gdPets",userPet->sid,"name",str_name);

	char szBuffer[1024] = {0};
	sprintf(szBuffer, AToU8("%d号：%s(%d转%d级)"), number, str_name.c_str(),rebornLV, userPet->lvl);
	CCLabelTTF* pet1Info = CCLabelTTF::create(szBuffer,"",14);
	pet1Info->setAnchorPoint(ccp(0,0.5));
	pet1Info->setPosition(ccp(point1.x+45,point1.y+20));
	pet1Info->setTag(Tag_name4);
	m_pTopList->addChild(pet1Info);
	
	CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("ui_pet_huodeshuxing").c_str(),rebornLV>=4?4:rebornLV);
	std::string str_rdsc = SystemData::getLayoutString(pStr->getCString());
	rebornDesc->setString(str_rdsc.c_str());

	userpets = GameData::s_user->getUserPetData()->userpets;

	CCPoint point[3] = {SystemData::getLayoutPoint("ui_pet_pButton2_pos")
	,SystemData::getLayoutPoint("ui_pet_pButton3_pos")
	,SystemData::getLayoutPoint("ui_pet_pButton4_pos")};
//	CCMenuItemImage *pB[3] = {pButton2,pButton3,pButton4};
	int i = 0;
	int begobbleuplv = 60;
	LuaData::getProp("gdPetReborn","begobbleuplv",begobbleuplv);
	for(std::map<int,UserPet*>::iterator it = userpets.begin(); it!=userpets.end(); it++)
	{
		UserPet* up = it->second;
		if(it->second->iid == userPet->iid || it->second->lvl<begobbleuplv)
		{
			continue;
		}
		else
		{
			CCMenuItemImage *pButton = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY, "juBaoPenBox");
			pButton->setTarget(this, menu_selector(PetReborn::onList));
			mList->addItem(pButton);
			int pic_sid = 0;
			if (up->exdata[Entity::attr_pet_reborn_cnt]>0)
			{
				LuaData::getProp("gdPets",it->second->sid,"headImageID_s",pic_sid);
			}
			else
			{
				LuaData::getProp("gdPets",it->second->sid,"headImageID_n",pic_sid);
			}
			//		UserItem* pUserItem = CommonFunction::createNewItem(pic_sid);
			//		CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			CCSprite *icon = LayoutData::getItemIcon(pic_sid);
			icon->setPosition(LayoutData::getCenter(pButton->getContentSize()));
			pButton->addChild(icon);
			//		pItem->setTarget(this,menu_selector(PetReborn::itemClickCallBack));
			//		pItem->setPosition(point[i]);
			std::string str = "";
			{
				int number=0;
				number=GameData::s_user->getUserPetData()->getPetNumByIid(up->iid)+1;
				std::string str_name = "";
				LuaData::getProp("gdPets",up->sid,"name",str_name);
				up->name = str_name;

				char szBuffer[100] = {0};
				if (up->exdata[Entity::attr_pet_reborn_cnt]>0)
				{
					std::string str_ds = SystemData::getLayoutString("str_pet_de");
					sprintf(szBuffer, str_ds.c_str(), number, str_name.c_str(), up->exdata[Entity::attr_pet_reborn_cnt],up->lvl);
				}else
				{
					std::string str_ds = SystemData::getLayoutString("str_pet_de_1");
					sprintf(szBuffer, str_ds.c_str(), number, str_name.c_str(),up->lvl);
				}

				str = szBuffer;
			}

			initPetLabel(str,point[i],i);
			m_Pets[i] = it->second;
			i++;
		}
	}
	m_pUserPet2 = m_Pets[mCurrentIndex];
	mList->setCurrentIndex(mCurrentIndex);
	if (!m_pUserPet2)
	{
		hasNo->setString(LayoutData::getString(CPModuleName::GUIDE,"pet_has_no").c_str());
		hasNo->setFontSize(18);
	}
	else
	{
		hasNo->setString("");
	}
}

void PetReborn::setPet( UserPet* userPet )
{
	PetReborn::m_pUserPet = userPet;
}

UserPet* PetReborn::getPet()
{
	return PetReborn::m_pUserPet;
}

void PetReborn::itemClickCallBack( CCObject* pSender )
{
	if (m_pUserPet)
	{
		Game::getGameUI()->showPetBaseTipPanel(m_pUserPet,TAG_Tips);
	}
}

void PetReborn::initPetLabel( string str, CCPoint p ,int tag)
{
//	string str1 =  AToU8(str.c_str());
	CCLabelTTF* petInfo = CCLabelTTF::create(str.c_str(),"",14);
	petInfo->setPosition(ccp(p.x,p.y-45));
	petInfo->setTag(tag);
	m_pTopList->addChild(petInfo);
}

void PetReborn::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessagePetRebornResponse")
		{
			mList->removeAllItems();
			for (int i=0;i<Tag_Max;i++)
			{
				if (m_pTopList->getChildByTag(i))
				{
					m_pTopList->removeChildByTag(i);
				}
			}
			mCurrentIndex = 0;
			m_pUserPet2 = NULL;
			m_Pets.clear();
			initItemPet();
			//
			MsgSleepPetStateRequest* msg1=new MsgSleepPetStateRequest;
			msg1->id=m_pUserPet->iid;
			HandleMessage::sendMessage(msg1);
			MsgActivePetStateRequest* msg2=new MsgActivePetStateRequest;
			msg2->id=m_pUserPet->iid;
			HandleMessage::sendMessage(msg2);
		}
	}
}

void PetReborn::onList( CCObject *target )
{
	const int index = mList->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
	}

	m_pUserPet2 = m_Pets[mCurrentIndex];

	if (m_pUserPet2)
	{
		Game::getGameUI()->showPetBaseTipPanel(m_pUserPet2,TAG_Tips);
	}
	//找到对应宠物蛋的iid
//	UserItem* pItem = GameData::s_user->getUserItemData()->getItemByIid(43359);
//	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}
