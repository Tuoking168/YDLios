#include "PetPanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "network/HandleMessage.h"
#include "MsgItem.h"
#include "MsgPet.h"
#include "userdata/netdata/NetItem.h"

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


PetPanel::PetPanel():
	m_pMainMenu(NULL),
	m_pVcoinLabel(NULL),
	m_pHonorLabel(NULL),
	m_pCntXiangquan(NULL),
	m_pUserPet(NULL),
	m_pTabelView(NULL),
	m_iCurPage(0),
	m_bIsInitOver(false),
	m_pPetStateLabel(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

PetPanel::~PetPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}
/*

PetPanel* PetPanel::create()
{
	PetPanel* petPanel = new PetPanel();
	if(petPanel && petPanel->init())
	{
		petPanel->autorelease();
		return petPanel;
	}


	if (petPanel)
	{
		delete petPanel;
	}
	return NULL;
}*/

bool PetPanel::init()
{
	m_pUserPet = GameData::s_user->getUserPetData()->initCurrentPet();
	if (m_pUserPet)
	{
		m_iCurPage=GameData::s_user->getUserPetData()->getCurrentNum();
	}
	 
	CCScale9Sprite* pbkg=SystemData::getScale9SpriteByPlist("ui_pet_main",SystemData::getLayoutValue("ui_pet_main_size.w"),SystemData::getLayoutValue("ui_pet_main_size.h"));
	pbkg->setAnchorPoint(CCPointZero);
	pbkg->setPosition(SystemData::getLayoutPoint("ui_pet_main_pos")); 
	addChild(pbkg);

	if (!m_pUserPet)
	{
		CCScale9Sprite *bkg=SystemData::getScale9SpriteByPlist("ui_pet_bkg");
		bkg->setPosition(SystemData::getLayoutPoint("ui_pet_bkg_pos"));
		addChild(bkg);
	}

	m_nWidth=pbkg->getContentSize().width;
	m_nHeight=pbkg->getContentSize().height;
	addCover();//保证点击事件

	m_pMainMenu=GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	CCMenuItemImage* pItem5=SystemData::getMenuItemImageByPlist("ui_pet_topbutton1");
	pItem5->setPosition(SystemData::getLayoutPoint("ui_pet_rightbutton3_pos"));
	pItem5->setTag(PET_Lock);
	pItem5->setTarget(this,menu_selector(PetPanel::MenuCallBack));
	m_pMainMenu->addChild(pItem5);
	CCLabelTTF* plabel5=SystemData::getLabelTTF("ui_pet_fengyin");
	plabel5->setFontSize(20);
	plabel5->setColor(ccWHITE);
	plabel5->setPosition(ccp(pItem5->getContentSize().width/2,pItem5->getContentSize().height/2));
	pItem5->addChild(plabel5);
	 
	CCMenuItemImage* pItem3=SystemData::getScale9MenuItemImageByPlist("ui_pet_topbutton2");
	pItem3->setPosition(SystemData::getLayoutPoint("ui_pet_rongyupeiyang_pos"));
	pItem3->setTag(PET_HonorUP);
	pItem3->setTarget(this,menu_selector(PetPanel::MenuCallBack));
	m_pMainMenu->addChild(pItem3);
	CCLabelTTF* plabel3=SystemData::getLabelTTF("ui_pet_rongyupeiyang");
	plabel3->setFontSize(20);
	plabel3->setColor(ccWHITE);
	plabel3->setPosition(ccp(pItem3->getContentSize().width/2,pItem3->getContentSize().height/2));
	pItem3->addChild(plabel3);

	CCMenuItemImage* pItem4=SystemData::getScale9MenuItemImageByPlist("ui_pet_topbutton2");
	pItem4->setPosition(SystemData::getLayoutPoint("ui_pet_yuanbaopeiyang_pos"));
	pItem4->setTag(PET_VcoinUP);
	pItem4->setTarget(this,menu_selector(PetPanel::MenuCallBack));
	m_pMainMenu->addChild(pItem4);
	CCLabelTTF* plabel4=SystemData::getLabelTTF("ui_pet_yuanbaopeiyang");
	plabel4->setFontSize(20);
	plabel4->setColor(ccWHITE);
	plabel4->setPosition(ccp(pItem4->getContentSize().width/2,pItem4->getContentSize().height/2));
	pItem4->addChild(plabel4);
	//一键升级
	CCMenuItemImage* pItemOneKeyUp=SystemData::getScale9MenuItemImageByPlist("ui_pet_topbutton2");
	pItemOneKeyUp->setPosition(SystemData::getLayoutPoint("ui_pet_onekeyshengji_pos"));
	pItemOneKeyUp->setTag(PET_OneKeyUp);
	int vipLv = HeroData::getProp(Entity::attr_vip_level);
	pItemOneKeyUp->setTarget(this,menu_selector(PetPanel::MenuCallBack));
	
	m_pMainMenu->addChild(pItemOneKeyUp);
	CCLabelTTF* plabelOneKeyUp=SystemData::getLabelTTF("ui_pet_petyijianshengji");
	plabelOneKeyUp->setFontSize(20);
	plabelOneKeyUp->setColor(ccWHITE);
	plabelOneKeyUp->setPosition(ccp(pItem4->getContentSize().width/2,pItem4->getContentSize().height/2));
	pItemOneKeyUp->addChild(plabelOneKeyUp);


	//项圈个数
	CCLabelTTF* plabelXiangquan = SystemData::getLabelTTF("ui_pet_xiangquan");
	plabelXiangquan->setFontSize(14);
	plabelXiangquan->setColor(ccYELLOW);
	plabelXiangquan->setPosition(SystemData::getLayoutPoint("ui_pet_xiangquan_pos"));
	m_pMainMenu->addChild(plabelXiangquan);
	m_pCntXiangquan=CCLabelTTF::create(" ","Times New Roman",14);
	m_pCntXiangquan->setString(SystemData::intToString(GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("ui_pet_xiangquan_id"),ItemPos::Player_Bag_Start)).c_str());
	m_pCntXiangquan->setAnchorPoint(ccp(0,0.5));
	m_pCntXiangquan->setPosition(ccp(plabelXiangquan->getPositionX()+50,plabelXiangquan->getPositionY()));
	addChild(m_pCntXiangquan); 


	CCSprite* ptitle=SystemData::getSpriteByPlist("ui_pet_title");
	ptitle->setPosition(SystemData::getLayoutPoint("ui_pet_title_pos"));
	addChild(ptitle);

	CCLabelTTF *plabel=SystemData::getLabelTTF("ui_pet_CWJN");
	plabel->setFontSize(20);
	plabel->setColor(ccWHITE);
	plabel->setPosition(ptitle->getPosition());
	addChild(plabel);
	

	CCScale9Sprite* pExpboard=SystemData::getScale9SpriteByPlist("ui_pet_expboard",223,8);
	pExpboard->setAnchorPoint(ccp(0,0.5));
	pExpboard->setPosition(SystemData::getLayoutPoint("ui_pet_exp_pos"));
	addChild(pExpboard);

	//箭头，宠物切换
	CCMenuItemImage* pItemLeft=SystemData::getMenuItemImageByPlist("ui_pet_jiantou");
	pItemLeft->setOpacity(100);
	pItemLeft->setPosition(ccp(SystemData::getLayoutPoint("ui_pet_left_pos").x,SystemData::getLayoutPoint("ui_pet_left_pos").y));
	pItemLeft->setTarget(this,menu_selector(PetPanel::MenuCallBack));
	pItemLeft->setTag(TAG_Left);
	m_pMainMenu->addChild(pItemLeft);
	CCSprite* psprite=SystemData::getSpriteByPlist("ui_pet_jiantou");
	psprite->runAction(CCFlipX::create(true));
	CCMenuItemSprite* pItemRight=CCMenuItemSprite::create(psprite,psprite,NULL,this,menu_selector(PetPanel::MenuCallBack));
	pItemRight->setOpacity(100);
	pItemRight->setPosition(SystemData::getLayoutPoint("ui_pet_right_pos"));
	pItemRight->setTarget(this,menu_selector(PetPanel::MenuCallBack));
	pItemRight->setTag(TAG_Right);
	m_pMainMenu->addChild(pItemRight);

	if (m_pUserPet==NULL)
	{
		pItemLeft->setTarget(this,NULL);
		pItemRight->setTarget(this,NULL);
	}

	//元宝，荣誉
	CCSprite* pSprite_rongyu=SystemData::getSpriteByPlist("ui_pet_rongyu");
	pSprite_rongyu->setPosition(SystemData::getLayoutPoint("ui_pet_rongyu_pos"));
	pSprite_rongyu->setAnchorPoint(CCPointZero);
	addChild(pSprite_rongyu);
	m_pHonorLabel=CCLabelTTF::create(" ","Times New Roman",14);
	m_pHonorLabel->setAnchorPoint(CCPointZero);
	m_pHonorLabel->setPosition(ccp(pSprite_rongyu->getPositionX()+40,pSprite_rongyu->getPositionY()));
	addChild(m_pHonorLabel);

	CCSprite* pSprite_yuanbao=SystemData::getSpriteByPlist("ui_pet_yuanbao");
	pSprite_yuanbao->setPosition(SystemData::getLayoutPoint("ui_pet_yuanbao_pos"));
	pSprite_yuanbao->setAnchorPoint(CCPointZero);
	addChild(pSprite_yuanbao);
	m_pVcoinLabel=CCLabelTTF::create(" ","Times New Roman",14);
	m_pVcoinLabel->setAnchorPoint(CCPointZero);
	m_pVcoinLabel->setPosition(ccp(pSprite_yuanbao->getPositionX()+40,pSprite_yuanbao->getPositionY()));
	addChild(m_pVcoinLabel); 
	
	m_pVcoinLabel->setString(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str());
	m_pHonorLabel->setString(SystemData::intToString(GameData::s_user->m_pMainRole->Honour).c_str());

	m_pMenu=GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	m_pMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMenu);

	m_pPetStateLabel=CCLabelTTF::create("","",18);
	addChild(m_pPetStateLabel);

	this->scheduleUpdate();

	//this->runAction(CCSequence::create(CCDelayTime::create(0.1f),CCCallFunc::create(this,callfunc_selector(PetPanel::updateRightAttr)),NULL));

	return true;
}

void PetPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		std::vector<string> strlist(0);
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_Left:
			//--m_iCurPage;
			m_pUserPet=GameData::s_user->getUserPetData()->getLastPet();
			m_iCurPage=GameData::s_user->getUserPetData()->getCurrentNum();
			//m_iCurPage=GameData::s_user->getUserPetData()->getPetNumByIid(m_pUserPet->iid);
			initPetBase();
			initPetAnimation();
			((CommonPanel*)this->getParent())->selectTop(PETSKILL);
			break;
		case TAG_Right:
			//++m_iCurPage;
			m_pUserPet=GameData::s_user->getUserPetData()->getNextPet();
			m_iCurPage=GameData::s_user->getUserPetData()->getCurrentNum();
			//m_iCurPage=GameData::s_user->getUserPetData()->getPetNumByIid(m_pUserPet->iid);
			initPetBase();
			initPetAnimation();
			((CommonPanel*)this->getParent())->selectTop(PETSKILL);
			break;
		case PET_Combat:
			//m_pUserPet=GameData::s_user->getUserPetData()->getCurrentPet();
			if (m_pUserPet)
			{
				MsgActivePetStateRequest* msg=new MsgActivePetStateRequest;
				msg->id=m_pUserPet->iid;
				HandleMessage::sendMessage(msg);
			}
			break;
		case PET_Sleep:
			//m_pUserPet=GameData::s_user->getUserPetData()->getCurrentPet();
			if (m_pUserPet)
			{
				MsgSleepPetStateRequest* msg=new MsgSleepPetStateRequest;
				msg->id=m_pUserPet->iid;
				HandleMessage::sendMessage(msg);
			}
			break;
		case PET_CloseBooth:
			if (m_pUserPet)
			{
				MsgCloseMarketRequest* msg=new MsgCloseMarketRequest;
				HandleMessage::sendMessage(msg);
			}
			break;
		case PET_Lock:
			petlock();
			//m_pUserPet=GameData::s_user->getUserPetData()->getCurrentPet();
			break;
		case PET_HonorUP:
			if (GameData::s_user->getUserPetData()->honortips)
			{
				useHonorToUp(0);
			}
			else
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Pet_FeedHonor);
				((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setHandler(this,floatpanel_selector(PetPanel::useHonorToUp));
			}
			break;
		case PET_VcoinUP:
			if (GameData::s_user->getUserPetData()->vcointips)
			{
				useVcoinToUp(0);
			}
			else
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::Pet_FeedVcoin);
				((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setHandler(this,floatpanel_selector(PetPanel::useVcoinToUp));
			}
			break;
		case PET_OneKeyUp:
			{
				//弹出对话框界面代码		
				Game::getGameUI()->showFloatPanel(FloatPanelType::Pet_onekeyup);
			}
			//oneKeyUp(0);
			break;
		case PET_SKILL_MONEY:  
			//发送消息，哪个宠物摆摊
			if (m_pUserPet)
			{
				/*if (m_pUserPet->lvl<1)
				{
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_MONEY,strlist,false,false);  
				}*/
				
				
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_MONEY);
				
			}
			else
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::PET_MONEY,strlist,false,false);
			}

			break;
		case PET_SKILL_ITEM:
			if (m_pUserPet)
			{
				if (m_pUserPet->lvl<2)
				{
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_ITEM,strlist,false,false);
				}
				else
				{
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_ITEM);
				}
			}
			else
			{

				Game::getGameUI()->showFloatPanel(FloatPanelType::PET_ITEM,strlist,false,false);
			}
			break;
		case PET_SKILL_OUT:
			if (m_pUserPet)
			{
				if (m_pUserPet->lvl>=10)
				{
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_LowBooth);
				}
				else
				{
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_LowBooth,strlist,false,false);
				}
			}
			else
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::PET_LowBooth,strlist,false,false);

			}
			break;
		case PET_SKILL_HIGHOUT:
			if (m_pUserPet)
			{
				if (m_pUserPet->lvl>=40)
				{					
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_HighBooth);
				}
				else
				{
					Game::getGameUI()->showFloatPanel(FloatPanelType::PET_HighBooth,strlist,false,false);
				}
			}
			else
			{
				Game::getGameUI()->showFloatPanel(FloatPanelType::PET_HighBooth,strlist,false,false);
			}
			break;
		case PET_Reborn:
			if (m_pUserPet)
			{
				int lvl = m_pUserPet->lvl;
				int rebornLv = 120;
				LuaData::getProp("gdPetReborn","rebornlv",rebornLv);
				if (lvl < rebornLv)
				{
					Game::getGameUI()->showFloatPanel(FloatPanelType::Pet_reborn_desc);
					return;
				}
				else
				{
// 					if (GameData::s_user->getUserPetData()->getPetCount()>=2)//two pets at least
// 					{
// 						
// 					}
// 					else
// 					{
// 						CPEventHelper::uiNotify("","",Error::NotEnoughPetCnt);
// 					}
					PetReborn::setPet(m_pUserPet);
					Game::getGameUI()->showPetReborn();
				}
			}
			break;
		}
	}
}

void PetPanel::initPetBase()
{/*
	TestUtils::timeTestBegin();*/
	//this->runAction(CCSequence::create(CCDelayTime::create(0.02f),CCCallFunc::create(this,callfunc_selector(PetPanel::initPetBtn)),CCCallFunc::create(this,callfunc_selector(PetPanel::initPetInfo)),NULL));
	initPetBtn();
	/*TestUtils::timeTestEnd("pet initPetBtn");*/
	initPetInfo();

}

void PetPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_PET_UPDDATA)
	{
		initPetBase();
	}
	else if (channel == EventProtocol::EVENT_PET_GETEXP)
	{
		initExp();
	}
	else if(channel == EventProtocol::EVENT_PET_LEVELUP)
	{
		initPetBase();
		addLevelUpEffect();
	}
	else if (channel == EventProtocol::EVENT_PET_REMOVE)
	{
		initAll();
	}
	m_pVcoinLabel->setString(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str());
	m_pHonorLabel->setString(SystemData::intToString(GameData::s_user->m_pMainRole->Honour).c_str());
	m_pCntXiangquan->setString(SystemData::intToString(GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("ui_pet_xiangquan_id"),ItemPos::Player_Bag_Start)).c_str());
}

void PetPanel::postMsg()
{
	if (m_pUserPet)
	{
		MsgMarketSelectPetRequest* req=new MsgMarketSelectPetRequest;
		req->petid=m_pUserPet->iid;
		HandleMessage::sendMessage(req); 
	}
}

void PetPanel::initExp()
{
	if (m_pMenu->getChildByTag(100))
	{
		m_pMenu->removeChildByTag(100);
	}
	int expcount;
	LuaData::getProp("gdPetGrow",m_pUserPet->lvl,"exp",expcount);
	CCScale9Sprite* pExppoint=SystemData::getScale9SpriteByPlist("ui_pet_exppoint",223,8);
	pExppoint->setPosition(SystemData::getLayoutPoint("ui_pet_exp_pos"));
	pExppoint->setAnchorPoint(ccp(0,0.5));
	//pExppoint->setScaleY(0.6f);
	float n=(float)m_pUserPet->exp/(float)expcount;
	if (n>1)
	{
		n=1;
	}
	pExppoint->setScaleX(n);
	pExppoint->setTag(100);
	m_pMenu->addChild(pExppoint);
}


void PetPanel::initPetAnimation()
{

	TestUtils::timeTestBegin();
	//加载tabelview
	if (m_pUserPet==NULL)
	{
		return;
	}
	if (m_pTabelView)
	{
		m_pTabelView->setCurPage(m_iCurPage);
	}
	else
	{
		m_pTabelView=CCTableViewEx::create(this,CCSizeMake(300,158),kCCScrollViewDirectionHorizontal,this,NULL);
		m_pTabelView->setAnchorPoint(CCPointZero);
		m_pTabelView->setPosition(ccp(60,210));
		m_pTabelView->setIsadjust(true);
		m_pTabelView->reloadData();  
		addChild(m_pTabelView);

		if (GameData::s_user->getUserPetData()->getPetCount()==1)
		{
			m_pTabelView->setTouchEnabled(false);
		}

		m_pTabelView->setCurPageWithInit(m_iCurPage);
	}
	TestUtils::timeTestEnd("pet action");
}

cocos2d::CCSize PetPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(311, 158);  
}

cocos2d::extension::CCTableViewCell* PetPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCLayer* pLayer=CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCScale9Sprite *bkg=SystemData::getScale9SpriteByPlist("ui_pet_bkg");
		bkg->setPosition(ccp(160,55));
		pLayer->addChild(bkg);

		UserPet* pPet=GameData::s_user->getUserPetData()->getPetByNum(idx+1);

		//拿路径
		std::string anim;
		LuaData::getProp_pet("gdPets",pPet->sid,"anim","n",anim); 
		std::string url="pet/"+anim+"_0";
		int rebornLV = 0;
		rebornLV = pPet->exdata[Entity::attr_pet_reborn_cnt];
		if (rebornLV > 0)
		{
			LuaData::getProp_pet("gdPets",pPet->sid,"anim","s",anim); 
			url = "pet/"+anim+"_0";
		}

		CCFlashAnimation* animation = SystemData::getAnimation(url);
		CCSprite* p=CCSprite::create();
		p->runAction(CCRepeatForever::create(CCSequence::create(CCFlipX::create(true),animation->getAnimate(2),NULL)));
		p->setPosition(ccp(140,75));
		pLayer->addChild(p);
	}
	return cell;
}

unsigned int PetPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return GameData::s_user->getUserPetData()->getPetCount();
}

void PetPanel::update( float dt )
{
	if (m_pTabelView==NULL)
	{
		if (!m_bIsInitOver)
		{
			this->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(PetPanel::initPetBase)),CCCallFunc::create(this,callfunc_selector(PetPanel::initPetAnimation)),NULL));	
			
		}
		return;
	}
	int page=m_pTabelView->getCurPage();
	buttoncheck();
	if (m_iCurPage==page)
	{
		return;
	}
	else
	{
		if (m_iCurPage<page)
		{
			m_pUserPet=GameData::s_user->getUserPetData()->getNextPet();
		}
		else
		{
			m_pUserPet=GameData::s_user->getUserPetData()->getLastPet();
		}
		m_iCurPage=page;
		initPetBase();
		//this->stopAllActions();
		this->runAction(CCSequence::create(CCDelayTime::create(0.1f),CCCallFunc::create(this,callfunc_selector(PetPanel::updateRightAttr)),NULL));		
	}
}

void PetPanel::updateRightAttr()
{
	((CommonPanel*)this->getParent())->selectTop(PETSKILL);
}
void PetPanel::buttoncheck()
{
	if (m_pMainMenu->getChildByTag(TAG_Left))
	{
		m_pMainMenu->getChildByTag(TAG_Left)->setVisible(true);
	}
	if (m_pMainMenu->getChildByTag(TAG_Right))
	{
		m_pMainMenu->getChildByTag(TAG_Right)->setVisible(true);
	}
	if (m_iCurPage==0)
	{
		if (m_pMainMenu->getChildByTag(TAG_Left))
		{
			m_pMainMenu->getChildByTag(TAG_Left)->setVisible(false);
		}
		
		//朝左失效
	}
	if ((m_iCurPage+1)==GameData::s_user->getUserPetData()->getPetCount())
	{
		if (m_pMainMenu->getChildByTag(TAG_Right))
		{
			m_pMainMenu->getChildByTag(TAG_Right)->setVisible(false);
		}
		//朝右失效
	}

	/*if (m_iCurPage!=0 && (m_iCurPage+1)!=GameData::s_user->getUserPetData()->getPetCount())
	{
		
	}*/
}

void PetPanel::initPetInfo()
{
	// 宠物名字，等级,经验条	
	if (m_pUserPet)
	{
		int number=0;
		number=GameData::s_user->getUserPetData()->getPetNumByIid(m_pUserPet->iid)+1;
		std::string str_name = "";
		LuaData::getProp("gdPets",m_pUserPet->sid,"name",str_name);
//		m_pUserPet->name = str_name;
//		CCString* pStr1=CCString::createWithFormat("%d号：%s",number,m_pUserPet->name.c_str());
		//std::string str="%d号："+m_pUserPet->name;
// 		CCLabelTTF* PetName=CCLabelTTF::create(AToU8(pStr1->getCString()),"微软雅黑",16);
// 		PetName->setAnchorPoint(ccp(1,0));
// 		PetName->setPosition(SystemData::getLayoutPoint("ui_pet_name_pos"));
//		m_pMenu->addChild(PetName);

// 		CCString* pStr=CCString::createWithFormat("(%d级)",m_pUserPet->lvl);
// 		CCLabelTTF* Petlvl=CCLabelTTF::create(AToU8(pStr->getCString()),"微软雅黑",16);
// 		Petlvl->setAnchorPoint(CCPointZero);
// 		Petlvl->setPosition(SystemData::getLayoutPoint("ui_pet_name_pos"));
//		m_pMenu->addChild(Petlvl);

		char szBuffer[1024] = {0};
		sprintf(szBuffer, AToU8("%d号：%s(%d级)"), number, str_name.c_str(), m_pUserPet->lvl);
		int rebornLV = 0;
		rebornLV = m_pUserPet->exdata[Entity::attr_pet_reborn_cnt];
		if (rebornLV > 0)
		{
			sprintf(szBuffer, AToU8("%d号：%s(%d转%d级)"), number, str_name.c_str(), rebornLV, m_pUserPet->lvl);
		}
		CCLabelTTF* petNameLvl = CCLabelTTF::create(szBuffer,"微软雅黑",16);
		petNameLvl->setAnchorPoint(ccp(0.5,0));
		petNameLvl->setPosition(SystemData::getLayoutPoint("ui_pet_name_pos"));
		m_pMenu->addChild(petNameLvl);

		std::string pos[4]={
			"ui_pet_button1_pos","ui_pet_button2_pos","ui_pet_button3_pos","ui_pet_button4_pos"
		};

		int skilltag[4]={
			PET_SKILL_MONEY,PET_SKILL_ITEM,PET_SKILL_OUT,PET_SKILL_HIGHOUT
		};

		std::string skill[4]={
			"ui_pet_button1","ui_pet_button2","ui_pet_button3","ui_pet_button4"
		};
		for (int i=0;i<4;i++)
		{
			CCMenuItemImage* p=SystemData::getMenuItemImageByPlist(skill[i]);
			p->setTag(skilltag[i]);
			p->setTarget(this,menu_selector(PetPanel::MenuCallBack));
			p->setPosition(SystemData::getLayoutPoint(pos[i]));
			if (m_pUserPet && p->getTag()!=PET_SKILL_MONEY)
			{
				if (m_pUserPet->lvl<2)
				{
					if (i>0)
					{
						p->setColor(ccGRAY);
					}
				}
				else if (m_pUserPet->lvl<10)
				{
					if (i>1)
					{
						p->setColor(ccGRAY);
					}
				}
				else if (m_pUserPet->lvl<40)
				{
					if (i>2)
					{
						p->setColor(ccGRAY);
					}
				}
			}
			else
			{
//				p->setColor(ccGRAY);
			}

			m_pMenu->addChild(p);
		} 
		initExp();	
		initHPandSPEED();
		initStatusWords();
	}
}

void PetPanel::initPetBtn()
{
	m_bIsInitOver=true;
	m_pMenu->removeAllChildren();
	if (m_pUserPet)
	{
		if (m_pUserPet->state==Entity::pet_sleep)
		{
			CCMenuItemImage* pItem1=SystemData::getMenuItemImageByPlist("ui_pet_topbutton1"); 
			pItem1->setPosition(SystemData::getLayoutPoint("ui_pet_leftbutton1_pos"));
			pItem1->setTag(PET_Combat);
			pItem1->setTarget(this,menu_selector(PetPanel::MenuCallBack));
			m_pMenu->addChild(pItem1);
			CCLabelTTF* plabel1=SystemData::getLabelTTF("ui_pet_chuzhan");
			plabel1->setFontSize(20);
			plabel1->setColor(ccWHITE);
			plabel1->setPosition(ccp(pItem1->getContentSize().width/2,pItem1->getContentSize().height/2));
			pItem1->addChild(plabel1);
		}

		if (m_pUserPet->state==Entity::pet_on)
		{
			CCMenuItemImage* pItem2=SystemData::getMenuItemImageByPlist("ui_pet_topbutton1");
			pItem2->setPosition(SystemData::getLayoutPoint("ui_pet_rightbutton1_pos"));
			pItem2->setTag(PET_Sleep);
			pItem2->setTarget(this,menu_selector(PetPanel::MenuCallBack));	
			m_pMenu->addChild(pItem2);
			CCLabelTTF* plabel2=SystemData::getLabelTTF("ui_pet_xiuxi");
			plabel2->setFontSize(20);
			plabel2->setColor(ccWHITE);
			plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
			pItem2->addChild(plabel2);
		}

		if (m_pUserPet->state==Entity::pet_market)
		{
			CCMenuItemImage* pItem2=SystemData::getMenuItemImageByPlist("ui_pet_topbutton1");
			pItem2->setPosition(SystemData::getLayoutPoint("ui_pet_rightbutton1_pos"));
			pItem2->setTag(PET_CloseBooth);
			pItem2->setTarget(this,menu_selector(PetPanel::MenuCallBack));	
			m_pMenu->addChild(pItem2);
			CCLabelTTF* plabel2=SystemData::getLabelTTF("ui_pet_shoutan");
			plabel2->setFontSize(20);
			plabel2->setColor(ccWHITE);
			plabel2->setPosition(ccp(pItem2->getContentSize().width/2,pItem2->getContentSize().height/2));
			pItem2->addChild(plabel2);
		}

		std::string sState="";
		switch (m_pUserPet->state)
		{
		case Entity::pet_sleep:
			sState=sState+"休息中";
			break;
		case Entity::pet_on:
			sState=sState+"出战中";
			break;
		case Entity::pet_dead:
			sState=sState+"死亡中";
			break;
		case Entity::pet_market:
			sState=sState+"摆摊中";
			break;
		case Entity::pet_imprison:
			sState=sState+"禁锢中";
			break;
		default:
			sState=sState+"不明真相中";
			break;
		}
		m_pPetStateLabel->setString(AToU8(sState.c_str()));
		m_pPetStateLabel->setPosition(ccp((SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").x+SystemData::getLayoutPoint("ui_pet_rightbutton1_pos").x)/2,SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").y-15));

		//宠物转生按钮
		CCMenuItemImage* pItem6=SystemData::getMenuItemImageByPlist("ui_pet_topbutton1");
		pItem6->setPosition(SystemData::getLayoutPoint("ui_pet_zhuansheng_pos"));
		pItem6->setTag(PET_Reborn);
		pItem6->setTarget(this,menu_selector(PetPanel::MenuCallBack));
		m_pMainMenu->addChild(pItem6);
		CCLabelTTF* plabel6=SystemData::getLabelTTF("ui_pet_petzhuansheng");
		plabel6->setFontSize(20);
		plabel6->setColor(ccWHITE);
		plabel6->setPosition(ccp(pItem6->getContentSize().width/2,pItem6->getContentSize().height/2));
		pItem6->addChild(plabel6);
		int rebornlvl = 0 ;
		LuaData::getProp("gdPetReborn","rebornlv",rebornlvl);
		if (m_pUserPet->lvl < rebornlvl)
		{
			pItem6->setColor(ccGRAY);
		}
	}
}

bool  PetPanel::checkVcoin()
{
	int req=0;
	LuaData::getProp("gdGame","PetFeedGold",req);
	if (HeroData::getProp(Entity::attr_gold)>=req)
	{
		return true;
	}
	return false;
}

bool  PetPanel::checkHonor()
{
	int req=0;
	LuaData::getProp("gdGame","PetFeedHonor",req);
	if (GameData::s_user->m_pMainRole->Honour>=req)
	{
		return true;
	}
	return false;
}

void PetPanel::addLevelUpEffect()
{
	//CCSprite* p=CommonFunction::getEffect(2);
	EffectSprite* p=EffectSprite::create(Effect::effect_petlvlup,1);
	p->setPosition(ccp((SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").x+SystemData::getLayoutPoint("ui_pet_rightbutton1_pos").x)/2+10,SystemData::getLayoutPoint("ui_pet_leftbutton1_pos").y-90));
	addChild(p); 
}

void PetPanel::initAll()
{
	m_pUserPet=GameData::s_user->getUserPetData()->initCurrentPet();
	m_iCurPage=0;
	m_pTabelView->reloadData();  
	if (GameData::s_user->getUserPetData()->getPetCount()==1)
	{
		m_pTabelView->setTouchEnabled(false);
	}
	initPetBase();
}

void PetPanel::useHonorToUp(int tag)
{
	//m_pUserPet=GameData::s_user->getUserPetData()->getCurrentPet();
	if (tag!=0)
	{
		return;
	}
	if (m_pUserPet)
	{
		if (checkHonor())
		{
			MsgFeedPetRequest* msg=new MsgFeedPetRequest;
			msg->id=m_pUserPet->iid;
			msg->feedtype=Entity::attr_honor;
			HandleMessage::sendMessage(msg);
		}
		else
		{
			CPEventHelper::uiNotify("","",Error::NotEnoughHonor);
		}
	}
}

void PetPanel::useVcoinToUp(int tag)
{
	//m_pUserPet=GameData::s_user->getUserPetData()->getCurrentPet();
	if (tag!=0)
	{
		return;
	}
	if (m_pUserPet)
	{
		int reqcnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("宠物项圈"));
		if (checkVcoin() || reqcnt!=0)
		{
			MsgFeedPetRequest* msg=new MsgFeedPetRequest;
			msg->id=m_pUserPet->iid;
			msg->feedtype=Entity::attr_gold;
			HandleMessage::sendMessage(msg);
		}
		else
		{			
			Game::getGameUI()->showFloatPanel(FloatPanelType::Gold_NotEnough);
			CPEventHelper::uiNotify("","",Error::NotEnoughGold);
		}
	}
}

void PetPanel::oneKeyUp(int tag)
{
	//m_pUserPet=GameData::s_user->getUserPetData()->getCurrentPet();
	if (tag!=0)
	{
		return;
	}
	if (m_pUserPet)
	{
		int reqcnt = GameData::s_user->getUserItemData()->getItemCntBySid(SystemData::getLayoutValue("宠物项圈"));
		if (HeroData::getProp(Entity::attr_vip_level)<4)
		{
			CPEventHelper::uiNotify("","",Error::NotEnoughVipLevel);
			return;
		}
		if (checkVcoin() || reqcnt!=0)
		{
			MsgFeedPetRequest* msg=new MsgFeedPetRequest;
			msg->id=m_pUserPet->iid;
			msg->feedtype=0;
			HandleMessage::sendMessage(msg);		
		}
		else
		{			
			Game::getGameUI()->showFloatPanel(FloatPanelType::Gold_NotEnough);
			CPEventHelper::uiNotify("","",Error::NotEnoughGold);
		}
	}
}

void PetPanel::lockpet( int tag )
{
	if (tag!=0)
	{
		return;
	}
	if (m_pUserPet)
	{
		MsgImprisonPetRequest* msg = new MsgImprisonPetRequest;
		msg->id = m_pUserPet->iid;
		HandleMessage::sendMessage(msg);
	}
}

void PetPanel::petlock()
{
	if (m_pUserPet)
	{
		int money=0;
		LuaData::getProp("gdImprisonGold",m_pUserPet->lvl,money);
		std::vector<std::string> strvec;
		strvec.push_back(SystemData::intToString(money));
		Game::getGameUI()->showFloatPanel(FloatPanelType::Pet_seal,strvec);
		((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setHandler(this,floatpanel_selector(PetPanel::lockpet));
	}
}

void PetPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPetLvlExpNotify")
		{
			int value = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (value==0)
			{
				EffectSprite* peffect = EffectSprite::create(Effect::effect_zhishengyiji,1); 
				peffect->setPosition(ccp(SystemData::getLayoutPoint("ui_pet_exp_pos").x+223/2,SystemData::getLayoutPoint("ui_pet_exp_pos").y));
				addChild(peffect);
			}
			else if (value>50) 
			{
				EffectSprite* peffect = EffectSprite::create(Effect::effect_10beijingyan,1);
				peffect->setPosition(ccp(SystemData::getLayoutPoint("ui_pet_exp_pos").x+223/2,SystemData::getLayoutPoint("ui_pet_exp_pos").y));
				addChild(peffect);
			}
		}
		if(source == "PetOneKeyUp")
		{
			oneKeyUp(0);
		}
		if (source == "HandleMessagePetRebornResponse")
		{
			initAll();
		}
	}
}

void PetPanel::initHPandSPEED()
{
	int lvl = m_pUserPet->lvl;
	int hp  = 0;
	int speed = 0;
	LuaData::getProp("gdPetSelf",lvl,"maxhp",hp);
	LuaData::getProp("gdPetSelf",lvl,"speed",speed);
	float realspeed = (float)1000/(float)speed;

	CCLabelTTF* PetHPTitle=CCLabelTTF::create(SystemData::getLayoutString("ui_pet_hp").c_str(),"微软雅黑",16);
	PetHPTitle->setAnchorPoint(CCPointZero);
	PetHPTitle->setPosition(SystemData::getLayoutPoint("ui_pet_hp_pos"));
	m_pMenu->addChild(PetHPTitle); 

	CCLabelTTF* PetHP=CCLabelTTF::create(SystemData::intToString(hp).c_str(),"微软雅黑",16);
	PetHP->setColor(ccGREEN);
	PetHP->setAnchorPoint(CCPointZero);
	PetHP->setPosition(ccp(PetHPTitle->getPositionX()+PetHPTitle->getContentSize().width,PetHPTitle->getPositionY()));
	m_pMenu->addChild(PetHP); 

	CCLabelTTF* PetSPEEDTitle=CCLabelTTF::create(SystemData::getLayoutString("ui_pet_speed").c_str(),"微软雅黑",16);
	PetSPEEDTitle->setAnchorPoint(CCPointZero);
	PetSPEEDTitle->setPosition(SystemData::getLayoutPoint("ui_pet_speed_pos"));
	m_pMenu->addChild(PetSPEEDTitle);

	CCLabelTTF* PetSPEED=CCLabelTTF::create(SystemData::floatToString(realspeed).c_str(),"微软雅黑",16);
	PetSPEED->setAnchorPoint(CCPointZero);
	PetSPEED->setColor(ccGREEN);
	PetSPEED->setPosition(ccp(PetSPEEDTitle->getPositionX()+PetSPEEDTitle->getContentSize().width,PetSPEEDTitle->getPositionY()));
	m_pMenu->addChild(PetSPEED);
}

void PetPanel::initStatusWords()
{
	int lvl = m_pUserPet->lvl;
	CCLabelTTF* statuswords = CCLabelTTF::create();
	int begobbleuplv = 60,rebornlv = 120;
	LuaData::getProp("gdPetReborn","begobbleuplv",begobbleuplv);
	LuaData::getProp("gdPetReborn","rebornlv",rebornlv);
	if (lvl < begobbleuplv)
	{
		statuswords = SystemData::getLabelTTF("ui_pet_status_words_01");
	}
	else if (lvl >=begobbleuplv && lvl < rebornlv)
	{
		statuswords = SystemData::getLabelTTF("ui_pet_status_words_02");
	} 
	else
	{
		statuswords = SystemData::getLabelTTF("ui_pet_status_words_03");
	}
	statuswords->setAnchorPoint(ccp(0,1));
	CCPoint p = SystemData::getLayoutPoint("ui_pet_hp_pos");
	statuswords->setPosition(ccp(p.x,p.y-55));
	statuswords->setColor(ccWHITE);
	statuswords->setFontSize(14);
	m_pMenu->addChild(statuswords);
}


