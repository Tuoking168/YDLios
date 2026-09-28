#include "LoginRewardPanel.h"
#include "ActivityModule.h"
#include "controls/CPNodeHelper.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "ext/GeneralMenu.h"
#include "controls/CPUpdater.h"
#include "ext/CCActionDestroy.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "event/IEventListener.h"
#include "script/LuaWrapper.h"
#include "MsgPlayer.h"
#include "network/HandleMessage.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/luadata/LuaData.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "controls/CPRichText.h"
#include "utils/RichTextUtils.h"
#include "userdata/HeroData.h"
#include "userdata/UserData.h"
#include "userdata/FuncData.h"
#include "userdata/ActivityData.h"
#include "ext/TouchCover.h"
#include "EvtDataDefinition.h"

LoginRewardPanel::LoginRewardPanel():
	m_pTableView(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

LoginRewardPanel::~LoginRewardPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	
}

bool LoginRewardPanel::init()
{
	if (!PartPanel::init())
	{
		return false;
	}

	CCSprite* pBkg = SystemData::getSpriteByPlist("Login_Reward_bkg");
	pBkg->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));

	m_nWidth = pBkg->getContentSize().width;
	m_nHeight = pBkg->getContentSize().height;
	addCover(ccp(pBkg->getPositionX()-m_nWidth/2, pBkg->getPositionY()-m_nHeight/2));
	addChild(pBkg);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	pBkg->addChild(pMenu);

	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("Login_Reward_Close");
	pClose->setTarget(this,menu_selector(LoginRewardPanel::close));
	pClose->setPosition(ccp(m_nWidth-pClose->getContentSize().width/2,m_nHeight-pClose->getContentSize().height/2));
	pMenu->addChild(pClose);

	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "loginRewardTitle");
	pBkg->addChild(title);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("Login_Reward_border",SystemData::getLayoutValue("Login_Reward_border.w"),SystemData::getLayoutValue("Login_Reward_border.h"));
	pBorder->setPosition(ccp(10,20));
	pBorder->setAnchorPoint(CCPointZero);
	pBkg->addChild(pBorder);

	m_pTableView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("Login_Reward_border").width,SystemData::getLayoutSize("Login_Reward_border").height),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(CCPointZero);
	m_pTableView->reloadData();  
	pBorder->addChild(m_pTableView);

	
	m_pPos = ccp(0,pBorder->getPositionY()+pBorder->getContentSize().height); 
	CCRect inner = CCRectZero;
	CCRect outer = CCRectMake(m_pPos.x,m_pPos.y,pBkg->getContentSize().width-pClose->getContentSize().width,pClose->getContentSize().height+10);
	TouchCover* pCover = TouchCover::create(inner,outer);
	pCover->setAnchorPoint(CCPointZero);
	pCover->setPosition(m_pPos);
	pCover->setTouchPriority(kCCMenuHandlerPriority-1);
	pBkg->addChild(pCover);

	return true;
}

void LoginRewardPanel::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (evtSource=="HandleMessageUpdPlayerPropsDataNotify")
		{
			if (CPEventHelper::getEventIntData(CPEventData::VALUE_2) == Entity::attr_gfmrdllb_times)
			{
				if (m_pTableView)
				{
					CCPoint point = m_pTableView->getContentOffset();
					m_pTableView->reloadData();
					m_pTableView->setContentOffset(point);
				}
			}
		}
	}
}

void LoginRewardPanel::close( CCObject* pSender )
{
	this->removeFromParent();
}

cocos2d::CCSize LoginRewardPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("Login_Reward_cell");
}

cocos2d::extension::CCTableViewCell* LoginRewardPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		
		CCLayer* pLayer = CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		CCMenuEx* pMenu = CCMenuEx::create();
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		CCScale9Sprite* pTitlebkg = SystemData::getScale9SpriteByPlist("Login_Reward_titlebkg",SystemData::getLayoutValue("Login_Reward_cell.w"),34);
		pTitlebkg->setPosition(ccp(SystemData::getLayoutValue("Login_Reward_cell.w")/2,SystemData::getLayoutValue("Login_Reward_cell.h")-pTitlebkg->getContentSize().height/2));
		pLayer->addChild(pTitlebkg);

		CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("Login_Reward_Number").c_str(),idx+1);
		CCLabelTTF* pTitle = SystemData::getLabelTTF(pStr->getCString());
		pTitle->setColor(ccWHITE);
		pTitle->setFontSize(20);
		pTitle->setPosition(ccp(pTitlebkg->getContentSize().width/2,pTitlebkg->getContentSize().height/2));
		pTitlebkg->addChild(pTitle);
		 
		int size = 0;
		int nowday = HeroData::getProp(Entity::attr_gfmrdllb_times)+1;
		LuaData::getProp_size("gdLoginReward",idx+1,"reward",size);
		bool flag = ActivityData::getExDataX(EvtData::evt_gfmrdllb);
		if (flag)
		{
			nowday = nowday-1;
		}

		for (int i = 0;i<size;i++)
		{
			CCScale9Sprite* pItemborder  = SystemData::getScale9SpriteByPlist("Login_Reward_Item",SystemData::getLayoutValue("Login_Reward_Item.w"),SystemData::getLayoutValue("Login_Reward_Item.h"));
			pItemborder->setPosition(ccp(SystemData::getLayoutPoint("Login_Reward_Item").x+85*i,SystemData::getLayoutPoint("Login_Reward_Item").y));
			pLayer->addChild(pItemborder);

			int reqsid = 0;
			int reqcnt = 0;
			LuaData::getProp("gdLoginReward",idx+1,"reward",i+1,"type",reqsid);
			LuaData::getProp("gdLoginReward",idx+1,"reward",i+1,"count",reqcnt); 
			if (reqsid==0)
			{
				int id=0;
				switch (HeroData::getJob())
				{
				case UserData::CARRER_ZS:
					id=1;
					break;
				case UserData::CARRER_FS:
					id=3;
					break;
				case UserData::CARRER_DS:
					id=5;
					break;
				default:
					break;
				}
				if (HeroData::getGender()==UserData::SEX_FEMALE)
				{
					id++;
				}
				std::string rewardname;
				LuaData::getProp("gdLoginReward",idx+1,"reward",i+1,"name",rewardname);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"type",reqsid);
				LuaData::getProp("gdRewardEx",rewardname,"reward",id,"count",reqcnt);
				if (reqsid == 0)
				{
					continue;
				}
			}
			UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
			pUserItem->count = reqcnt;
			CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
			pItem->setTarget(this,menu_selector(LoginRewardPanel::itemClickCallBack));
			pItem->setPosition(pItemborder->getPosition());
			pMenu->addChild(pItem);

			int dayLvl = 0;
			//添加后缀 还差XX天
			int day = idx+1-nowday;
			if (day>0)
			{
				CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("Login_Reward_Time").c_str(),day); 
				CPRichText* pText = RichTextUtils::getRichText(pStr->getCString(),20);
				//pText->setAnchorPoint(ccp(0,0.5));
				pText->setPosition(ccp(SystemData::getLayoutPoint("Login_Reward_Item").x+85*5,SystemData::getLayoutPoint("Login_Reward_Item").y));
				pLayer->addChild(pText);
			}
			else if (day==0 && !flag)
			{
				CCMenuItemImage* pButton = SystemData::getMenuItemImageByPlist("Login_Reward_Button");
				pButton->setTarget(this,menu_selector(LoginRewardPanel::getReward));
				pButton->setTag(idx+1);
				pButton->setPosition(ccp(SystemData::getLayoutPoint("Login_Reward_Item").x+85*5,SystemData::getLayoutPoint("Login_Reward_Item").y));
				pMenu->addChild(pButton);

				LuaData::getProp("gdLoginReward",idx+1,"lvl",dayLvl);
				CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("Login_Reward_LvL").c_str(),dayLvl);
				CCLabelTTF* pButtonLabel = CCLabelTTF::create(pStr->getCString(),"",18);
				pButtonLabel->setColor(ccWHITE);
				pButtonLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
				pButton->addChild(pButtonLabel);

			}
			else
			{
				CCSprite* pFlag = SystemData::getSpriteByPlist("Login_Reward_hasget");
				pFlag->setPosition(ccp(SystemData::getLayoutPoint("Login_Reward_Item").x+85*5,SystemData::getLayoutPoint("Login_Reward_Item").y));
				pLayer->addChild(pFlag);
			}			
		}
	}
	return cell;
}

unsigned int LoginRewardPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutValue("Login_Reward_Number_size");
}

void LoginRewardPanel::itemClickCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}

void LoginRewardPanel::getReward( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		int Lv = HeroData::getLevel();
		int dLv = 0;
		int rebornLv = 0;
		rebornLv = HeroData::getProp(Entity::attr_reborn);
		LuaData::getProp("gdLoginReward",tag,"lvl",dLv);
		if (Lv >= dLv || rebornLv != 0)
		{
			FuncData::setCurFuncID(7);
			FuncData::sendFuncMsg(tag);
		}
		else
		{
			CPEventHelper::uiNotify("","",Error::NotEnoughLevel);
		}
		
	}
}
