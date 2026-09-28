#include "RankPanel.h"
#include "ActivityModule.h"
#include "controls/CPNodeHelper.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "ext/GeneralMenu.h"
#include "userdata/RankData.h"
#include "controls/CPUpdater.h"
#include "ext/CCActionDestroy.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "event/IEventListener.h"
#include "script/LuaWrapper.h"
#include "MsgPlayer.h"
#include "network/HandleMessage.h"
#include "ext/CCMenuEx.h"

RankPanel::RankPanel():
	m_pSelfRankLabel(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::UI_CHANGE, this);
}

RankPanel::~RankPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::UI_CHANGE, this);
}
/*

RankPanel* RankPanel::create()
{
	RankPanel* bagPanel = new RankPanel();
	if(bagPanel && bagPanel->init())
	{
		bagPanel->autorelease();
		return bagPanel;
	}
	if (bagPanel)
	{
		delete bagPanel; 
	}
	return NULL;
}*/

bool RankPanel::init()//排行榜ui
{
	if (!FullScreenPanel::init())
	{
		return false;
	} 
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	RankData::setRankPanelType(rank_combatnum_all);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("rank_border",SystemData::getLayoutValue("rank_border.w"),SystemData::getLayoutValue("rank_border.h"));
	pBorder->setPosition(ccp(3,4));
	pBorder->setAnchorPoint(CCPointZero);
	addChild(pBorder);
	 
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "rankTitle");
	addChild(title);
	 
	CCLabelTTF* pDownTitle1 = SystemData::getLabelTTF("rank_downtitle1"); 
	pDownTitle1->setFontSize(18);
	pDownTitle1->setColor(ccGREEN); 
	addChild(pDownTitle1);

	m_pSelfRankLabel = SystemData::getLabelTTF("rank_downtitle2"); 
	m_pSelfRankLabel->setFontSize(18);
	m_pSelfRankLabel->setColor(ccYELLOW); 
	addChild(m_pSelfRankLabel);

	RankLeftPanel* pLeftMenu = RankLeftPanel::create();
	pLeftMenu->setPosition(SystemData::getLayoutPoint("rank_leftborder"));
	pLeftMenu->setAnchorPoint(CCPointZero);
	addChild(pLeftMenu);

	RankRightPanel* pRightMenu = RankRightPanel::create();
	pRightMenu->setPosition(SystemData::getLayoutPoint("rank_rightborder"));
	pRightMenu->setAnchorPoint(CCPointZero);
	addChild(pRightMenu);
	return true;
}

void RankPanel::hide()
{
	this->removeFromParent();
}

void RankPanel::onSwitch(int tag)
{

}

void RankPanel::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::UI_CHANGE)
	{
		if (evtSource == "RankLeftPanel")
		{
			CCString* pstr = NULL;
			if (RankData::getSelfRank(RankData::getRankServerType())==0)
			{
				 pstr = CCString::createWithFormat(SystemData::getLayoutString("rank_downtitle3").c_str());
			}
			else
			{
				 pstr = CCString::createWithFormat(SystemData::getLayoutString("rank_downtitle2").c_str(),RankData::getSelfRank(RankData::getRankServerType()));
			}
			//CCString* pstr = CCString::createWithFormat(SystemData::getLayoutString("rank_downtitle2").c_str(),RankData::getSelfRank(RankData::getRankServerType()));
			m_pSelfRankLabel->setString(pstr->getCString());
		}
	}
}

void RankPanel::onEnter()
{
	FullScreenPanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}

//-------------------------------------------------------------------------------------------------------------------------//

RankLeftPanel::RankLeftPanel():
	m_iCurType(0),
	m_pBtnMenu(NULL),
	m_pTableView(NULL)
{

}

RankLeftPanel::~RankLeftPanel()
{

}

bool RankLeftPanel::init()
{
	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("rank_smallborder",SystemData::getLayoutValue("rank_leftborder.w"),SystemData::getLayoutValue("rank_leftborder.h"));
	pBorder->setAnchorPoint(CCPointZero);
	pBorder->setPosition(CCPointZero);
	addChild(pBorder);

	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("rank_leftborder"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(CCPointZero);
	m_pTableView->reloadData();  
	addChild(m_pTableView);
	//initBtn();

	return true;
}

std::string leftStr[6]={
	"rank_lTitle1","rank_lTitle2","rank_lTitle3","rank_lTitle4","rank_lTitle5","rank_lTitle6"
};
std::string leftStrSize[6]={
	"rank_lTitle1_size","rank_lTitle2_size","rank_lTitle3_size","rank_lTitle4_size","rank_lTitle5_size","rank_lTitle6_size"
};
std::string leftStrSub[6]={
	"rank_lTitle1_","rank_lTitle2_","rank_lTitle3_","rank_lTitle4_","rank_lTitle5_","rank_lTitle6_"
};

const int flagint = 100;
void RankLeftPanel::initBtn()
{
	if (m_pBtnMenu)
	{
		CCArray *children = m_pBtnMenu->getChildren();
		if (children && children->count() > 0)
		{
			CCObject *obj = NULL;
			CCARRAY_FOREACH(children, obj)
			{
				CCNode *child = dynamic_cast<CCNode *>(obj);
				if (child)
				{
					CCHide *hi = CCHide::create();
					CCDelayTime *dl = CCDelayTime::create(0.5f);
					CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
					CCAction *action = CCSequence::create(hi, dl, rmv, NULL);
					child->runAction(action);
				}
			}
		}
	}
	else
	{
		m_pBtnMenu = GeneralMenu::create();
		m_pBtnMenu->setPosition(CCPointZero);
		m_pBtnMenu->setAnchorPoint(CCPointZero);
		addChild(m_pBtnMenu);
	}

	CCPoint pos = ccp(66,390);

	for (int i =0;i<6;i++)
	{
		CCLabelTTF* ptitle = SystemData::getLabelTTF(leftStr[i].c_str());
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("rank_leftbtn",SystemData::getLayoutValue("rank_leftbtn.w"),SystemData::getLayoutValue("rank_leftbtn.h"));
		CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("rank_leftbtn.sel",SystemData::getLayoutValue("rank_leftbtn.w"),SystemData::getLayoutValue("rank_leftbtn.h"));
		CCMenuItemSprite* pTitleSprite=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(RankLeftPanel::BtnCB));
		if (pTitleSprite)
		{
			pTitleSprite->setTag(i);
			pTitleSprite->setPosition(pos);
			ptitle->setFontSize(18);
			ptitle->setColor(ccWHITE);
			ptitle->setPosition(ccp(pTitleSprite->getContentSize().width/2, pTitleSprite->getContentSize().height/2));
			pTitleSprite->addChild(ptitle);
			m_pBtnMenu->addChild(pTitleSprite);
		}
		pos = ccp(pos.x,pos.y-pTitleSprite->getContentSize().height-15);
		if (m_iCurType == i)
		{
			pos=ccp(pos.x,pos.y+10);
			pTitleSprite->selected();
			int subsize = SystemData::getLayoutValue(leftStrSize[i].c_str());
			for (int j=1 ;j<=subsize;j++)
			{
				CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString(leftStrSub[i]).c_str(),j);
				CCMenuItemFont* pLabel =CCMenuItemFont::create(SystemData::getLayoutString(pStr->getCString()).c_str(),this,menu_selector(RankLeftPanel::LabelCB));
				pLabel->setFontSize(18);
				pLabel->setFontSizeObj(18);
				pLabel->setTag(flagint+i*10+j-1); 
				pLabel->setPosition(pos);
				m_pBtnMenu->addChild(pLabel);
				pos = ccp(pos.x,pos.y-pLabel->getContentSize().height-15);

				if (RankData::getRankPanelType()==(pLabel->getTag()-flagint))
				{
					pLabel->setColor(ccGREEN);
				}
			}
		}
	}
}

void RankLeftPanel::BtnCB( CCObject* pSender )
{
	CCMenuItemSprite* pNode = dynamic_cast<CCMenuItemSprite*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		if(m_iCurType==tag)
		{
			pNode->selected();
			return;
		}
		m_iCurType = tag;
		RankData::setRankPanelType(tag*10);
		if (m_pTableView)
		{
			m_pTableView->reloadData();
		}
		//initBtn();
	}
}

void RankLeftPanel::LabelCB( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		RankData::setRankPanelType(tag-flagint);
		//initLabel();
		m_pTableView->reloadData();
	}
}

void RankLeftPanel::initLabel()
{
	for (int i = rank_combatnum_all;i<rank_max;i++)
	{
		if (m_pBtnMenu && m_pBtnMenu->getChildByTag(i+flagint))
		{
			if (i == RankData::getRankPanelType())
			{
				((CCMenuItemFont* )m_pBtnMenu->getChildByTag(i+flagint))->setColor(ccGREEN);
			}
			else
			{
				((CCMenuItemFont* )m_pBtnMenu->getChildByTag(i+flagint))->setColor(ccWHITE);
			}
		}
	}
}

cocos2d::CCSize RankLeftPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return SystemData::getLayoutSize("rank_leftborder");
}

cocos2d::extension::CCTableViewCell* RankLeftPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		CCMenuEx* BtnMenu = CCMenuEx::create();
		BtnMenu->setPosition(CCPointZero);
		BtnMenu->setAnchorPoint(CCPointZero);
		pLayer->addChild(BtnMenu);

		CCPoint pos = ccp(66,390);

		for (int i =0;i<6;i++)
		{
			CCLabelTTF* ptitle = SystemData::getLabelTTF(leftStr[i].c_str());
			CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("rank_leftbtn",SystemData::getLayoutValue("rank_leftbtn.w"),SystemData::getLayoutValue("rank_leftbtn.h"));
			CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("rank_leftbtn.sel",SystemData::getLayoutValue("rank_leftbtn.w"),SystemData::getLayoutValue("rank_leftbtn.h"));
			CCMenuItemSprite* pTitleSprite=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(RankLeftPanel::BtnCB));
			if (pTitleSprite)
			{
				pTitleSprite->setTag(i);
				pTitleSprite->setPosition(pos);
				ptitle->setFontSize(18);
				ptitle->setColor(ccWHITE);
				ptitle->setPosition(ccp(pTitleSprite->getContentSize().width/2, pTitleSprite->getContentSize().height/2));
				pTitleSprite->addChild(ptitle);
				BtnMenu->addChild(pTitleSprite);
			}
			pos = ccp(pos.x,pos.y-pTitleSprite->getContentSize().height-15);
			if (m_iCurType == i)
			{
				pos=ccp(pos.x,pos.y+10);
				pTitleSprite->selected();
				int subsize = SystemData::getLayoutValue(leftStrSize[i].c_str());
				for (int j=1 ;j<=subsize;j++)
				{
					CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString(leftStrSub[i]).c_str(),j);
					CCMenuItemFont* pLabel =CCMenuItemFont::create(SystemData::getLayoutString(pStr->getCString()).c_str(),this,menu_selector(RankLeftPanel::LabelCB));
					pLabel->setFontSize(18);
					pLabel->setFontSizeObj(18);
					pLabel->setTag(flagint+i*10+j-1); 
					pLabel->setPosition(pos);
					BtnMenu->addChild(pLabel);
					pos = ccp(pos.x,pos.y-pLabel->getContentSize().height-15);

					if (RankData::getRankPanelType()==(pLabel->getTag()-flagint))
					{
						pLabel->setColor(ccGREEN);
					}
				}
			}
			for (int i = rank_combatnum_all;i<rank_max;i++)
			{
				if (BtnMenu && BtnMenu->getChildByTag(i+flagint))
				{
					if (i == RankData::getRankPanelType())
					{
						((CCMenuItemFont* )BtnMenu->getChildByTag(i+flagint))->setColor(ccGREEN);
					}
					else
					{
						((CCMenuItemFont* )BtnMenu->getChildByTag(i+flagint))->setColor(ccWHITE);
					}
				}
			}
		}
	}
	return cell;
}

unsigned int RankLeftPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

//------------------------------------------------------------------------------------------------------//



RankRightPanel::RankRightPanel():
	m_pInfoMenu(NULL),
	m_pTopLabel(NULL),
	m_iCurPage(1),
	m_iMaxPage(0),
	m_iMinPage(1),
	m_iListSize(0),
	m_pPage(NULL)
{
	for (int i=0;i<10;i++)
	{
		pos[i]=CCPointZero;
	}
	CPEvtDispatcher.addEventListener(CPEventName::UI_CHANGE, this);
}

RankRightPanel::~RankRightPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::UI_CHANGE, this);
}

bool RankRightPanel::init()
{
	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("rank_smallborder",SystemData::getLayoutValue("rank_rightborder.w"),SystemData::getLayoutValue("rank_rightborder.h"));
	pBorder->setAnchorPoint(CCPointZero);
	pBorder->setPosition(CCPointZero);
	addChild(pBorder);

	GeneralMenu* pMenu = GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCLabelTTF* pshouye=CCLabelTTF::create(SystemData::getLayoutString("rank_shouye").c_str(),"微软雅黑",16);
	CCScale9Sprite* pshouye1=SystemData::getScale9SpriteByPlist("rank_btn",pshouye->getContentSize().width+30,pshouye->getContentSize().height+15);
	CCScale9Sprite* pshouye2=SystemData::getScale9SpriteByPlist("rank_btn.sel",pshouye->getContentSize().width+30,pshouye->getContentSize().height+15);
	CCMenuItemSprite* pshouyeTitle=CCMenuItemSprite::create(pshouye1,pshouye2,NULL,this,menu_selector(RankRightPanel::shouyeCB));
	if (pshouyeTitle)
	{
		pshouyeTitle->setPosition(SystemData::getLayoutPoint("rank_shouye"));
		pshouye->setPosition(ccp(pshouyeTitle->getContentSize().width/2, pshouyeTitle->getContentSize().height/2));
		pshouyeTitle->addChild(pshouye);
		pMenu->addChild(pshouyeTitle);
	}

	CCLabelTTF* pshangyiye=CCLabelTTF::create(SystemData::getLayoutString("rank_shangyiye").c_str(),"微软雅黑",16);
	CCScale9Sprite* pshangyiye1=SystemData::getScale9SpriteByPlist("rank_btn",pshangyiye->getContentSize().width+30,pshangyiye->getContentSize().height+15);
	CCScale9Sprite* pshangyiye2=SystemData::getScale9SpriteByPlist("rank_btn.sel",pshangyiye->getContentSize().width+30,pshangyiye->getContentSize().height+15);
	CCMenuItemSprite* pshangyiyeTitle=CCMenuItemSprite::create(pshangyiye1,pshangyiye2,NULL,this,menu_selector(RankRightPanel::shangyiyeCB));
	if (pshangyiyeTitle)
	{
		pshangyiyeTitle->setPosition(SystemData::getLayoutPoint("rank_shangyiye"));
		pshangyiye->setPosition(ccp(pshangyiyeTitle->getContentSize().width/2, pshangyiyeTitle->getContentSize().height/2));
		pshangyiyeTitle->addChild(pshangyiye);
		pMenu->addChild(pshangyiyeTitle);
	}

	CCLabelTTF* pxiayiye=CCLabelTTF::create(SystemData::getLayoutString("rank_xiayiye").c_str(),"微软雅黑",16);
	CCScale9Sprite* pxiayiye1=SystemData::getScale9SpriteByPlist("rank_btn",pxiayiye->getContentSize().width+30,pxiayiye->getContentSize().height+15);
	CCScale9Sprite* pxiayiye2=SystemData::getScale9SpriteByPlist("rank_btn.sel",pxiayiye->getContentSize().width+30,pxiayiye->getContentSize().height+15);
	CCMenuItemSprite* pxiayiyeTitle=CCMenuItemSprite::create(pxiayiye1,pxiayiye2,NULL,this,menu_selector(RankRightPanel::xiayiyeCB));
	if (pxiayiyeTitle)
	{
		pxiayiyeTitle->setPosition(SystemData::getLayoutPoint("rank_xiayiye"));
		pxiayiye->setPosition(ccp(pxiayiyeTitle->getContentSize().width/2, pxiayiyeTitle->getContentSize().height/2));
		pxiayiyeTitle->addChild(pxiayiye);
		pMenu->addChild(pxiayiyeTitle);
	}

	CCLabelTTF* pmoye=CCLabelTTF::create(SystemData::getLayoutString("rank_moye").c_str(),"微软雅黑",16);
	CCScale9Sprite* pmoye1=SystemData::getScale9SpriteByPlist("rank_btn",pmoye->getContentSize().width+30,pmoye->getContentSize().height+15);
	CCScale9Sprite* pmoye2=SystemData::getScale9SpriteByPlist("rank_btn.sel",pmoye->getContentSize().width+30,pmoye->getContentSize().height+15);
	CCMenuItemSprite* pmoyeTitle=CCMenuItemSprite::create(pmoye1,pmoye2,NULL,this,menu_selector(RankRightPanel::moyeCB));
	if (pmoyeTitle)
	{
		pmoyeTitle->setPosition(SystemData::getLayoutPoint("rank_moye"));
		pmoye->setPosition(ccp(pmoyeTitle->getContentSize().width/2, pmoyeTitle->getContentSize().height/2));
		pmoyeTitle->addChild(pmoye);
		pMenu->addChild(pmoyeTitle);
	}

	m_pPage = CCLabelTTF::create("","",16);
	m_pPage->setPosition(ccp((SystemData::getLayoutPoint("rank_shangyiye").x+SystemData::getLayoutPoint("rank_xiayiye").x)/2,SystemData::getLayoutPoint("rank_shangyiye").y));
	addChild(m_pPage);

	initTop();

	return true;
}

std::string combatnumTop[5] = {
	"rank_sTitle1","rank_sTitle2","rank_sTitle3","rank_sTitle4","rank_sTitle5"
};

std::string levelTop[6] = {
	"rank_sTitle1","rank_sTitle2","rank_sTitle3","rank_sTitle6","rank_sTitle7","rank_sTitle5"
};

std::string petTop[4] = {
	"rank_sTitle1","rank_sTitle2","rank_sTitle8","rank_sTitle9"
};

std::string moneyTop[5] = {
	"rank_sTitle1","rank_sTitle2","rank_sTitle6","rank_sTitle7","rank_sTitle10"
};

std::string guildlevelTop[5] = {
	"rank_sTitle1","rank_sTitle3","rank_sTitle11","rank_sTitle12","rank_sTitle13"
};

std::string guildyltTop[5] = {
	"rank_sTitle1","rank_sTitle3","rank_sTitle14","rank_sTitle12","rank_sTitle13"
};

std::string fireworkTop[5] = {
	"rank_sTitle1","rank_sTitle2","rank_sTitle7","rank_sTitle15"
};
void RankRightPanel::initTop()
{
	if (m_pTopLabel)
	{
		m_pTopLabel->removeAllChildren();
	}
	else
	{
		m_pTopLabel = CCLayer::create();
		m_pTopLabel->setPosition(CCPointZero);
		m_pTopLabel->setAnchorPoint(CCPointZero);
		addChild(m_pTopLabel);
	}
	m_iCurPage = 1;
	std::string strlist[10];
	switch (RankData::getRankPanelType())
	{
	case rank_combatnum_all:
	case rank_combatnum_zs:
	case rank_combatnum_fs:
	case rank_combatnum_ds:
		m_iListSize = 5;
		for (int i=0;i<m_iListSize;i++)
		{
			strlist[i]=combatnumTop[i];
		}
		break;
	case rank_level_all	:
	case rank_level_zs:
	case rank_level_fs:
	case rank_level_ds:
		m_iListSize = 6;
		for (int i=0;i<m_iListSize;i++)
		{
			strlist[i]=levelTop[i];
		}
		break;
	case rank_pet_all:
		m_iListSize = 4;
		for (int i=0;i<m_iListSize;i++)
		{
			strlist[i]=petTop[i];
		}
		break;
	case rank_rich_all:
		m_iListSize = 5;
		for (int i=0;i<m_iListSize;i++)
		{
			strlist[i]=moneyTop[i];
		}
		break;
	case rank_guild_level:
		m_iListSize = 5;
		for (int i=0;i<m_iListSize;i++)
		{
			strlist[i]=guildlevelTop[i];
		}
		break;
	case rank_guild_lyt:
		m_iListSize = 5;
		for (int i=0;i<m_iListSize;i++)
		{
			strlist[i]=guildyltTop[i];
		}
		break;
	case rank_firework:
		m_iListSize = 4;
		for (int i=0;i<m_iListSize;i++)
		{
			strlist[i]=fireworkTop[i];
		}
	default:
		break;
	}	

	updateMaxPage();

	int labelwidth = 0;
	int addwidth = 640/(m_iListSize);
	for (int i=0;i<m_iListSize;i++)
	{
		CCLabelTTF* pTitle = SystemData::getLabelTTF(strlist[i].c_str());
		pTitle->setColor(ccYELLOW);
		pTitle->setFontSize(18);
		pTitle->setPosition(ccp(SystemData::getLayoutValue("rank_sTitle.x")+labelwidth,SystemData::getLayoutValue("rank_sTitle.y")));
		m_pTopLabel->addChild(pTitle);
		//labelwidth += pTitle->getContentSize().width+addwidth;
		labelwidth += addwidth;
		pos[i] = ccp(pTitle->getPositionX(),SystemData::getLayoutValue("rank_singleline.h")/2);
	}
	addInfoByPage();
}

void RankRightPanel::shouyeCB( CCObject* pSender )
{
	if (m_iCurPage!=1)
	{
		m_iCurPage = 1;
	}
	addInfoByPage();
}

void RankRightPanel::shangyiyeCB( CCObject* pSender )
{
	if (m_iCurPage>m_iMinPage)
	{
		m_iCurPage--;
	}
	addInfoByPage();
}

void RankRightPanel::xiayiyeCB( CCObject* pSender )
{
	if (m_iCurPage<m_iMaxPage)
	{
		m_iCurPage++;
	}
	addInfoByPage();
}

void RankRightPanel::moyeCB( CCObject* pSender )
{
	if (m_iCurPage!=m_iMaxPage)
	{
		m_iCurPage = m_iMaxPage;
	}
	addInfoByPage();
}

void RankRightPanel::addInfoByPage()
{
	if (m_pInfoMenu)
	{
		m_pInfoMenu->removeAllChildren();
	}
	else
	{
		m_pInfoMenu = GeneralMenu::create();
		m_pInfoMenu->setPosition(CCPointZero);
		m_pInfoMenu->setAnchorPoint(CCPointZero);
		addChild(m_pInfoMenu);
	}

	if (m_pPage)
	{
		CCString* pStr = CCString::createWithFormat("%d / %d",m_iCurPage,m_iMaxPage);
		m_pPage->setString(pStr->getCString());
	}

	CPUpdater* p = CPUpdater::create(this,cpupdater_selector(RankRightPanel::addSingleInfo));
	p->setUpdateTimes(9);
	m_pInfoMenu->addChild(p);
	p->start();
}

void RankRightPanel::addSingleInfo( int number )
{
	if (m_pInfoMenu)
	{
		CCMenuItemImage* pItem = getSingleInfo(number+1);
		if (pItem)
		{
			pItem->setAnchorPoint(CCPointZero);
			pItem->setPosition(ccp(0,328-number*pItem->getContentSize().height));
			m_pInfoMenu->addChild(pItem);
		}
	}
}

void RankRightPanel::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::UI_CHANGE)
	{
		if (evtSource == "RankLeftPanel")
		{
			initTop();
		}
		else if (evtSource == "HandleMessageGetWorldChartNotify")
		{
			updateMaxPage();
		}
	}
}

CCMenuItemImage* RankRightPanel::getSingleInfo( int number )
{
	int realnumber = number + (m_iCurPage-1)*9;
	switch (RankData::getRankPanelType())
	{
	case rank_combatnum_all:
	case rank_combatnum_zs:
	case rank_combatnum_fs:
	case rank_combatnum_ds:
		return getSingleInfoByCombatNum(realnumber);
		break;
	case rank_level_all	:
	case rank_level_zs:
	case rank_level_fs:
	case rank_level_ds:
		return getSingleInfoByLevel(realnumber);
		break;
	case rank_pet_all:
		return getSingleInfoByPet(realnumber);
		break;
	case rank_rich_all:
		return getSingleInfoByMoney(realnumber);
		break;
	case rank_guild_level:
		return getSingleInfoByGuildLevel(realnumber);
		break;
	case rank_guild_lyt:
		return getSingleInfoByGuildYLT(realnumber);
		break;
	case rank_firework:
		return getSingleInfoByFireWork(realnumber);
		break;
	default:
		break;
	}
	return NULL;	
}

CCMenuItemImage* RankRightPanel::getSingleInfoByCombatNum( int number )
{
	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("rank_singleline");

	std::map<int ,Rank_combatnum>::iterator it_combatnum ;

	switch (RankData::getRankPanelType())
	{
	case rank_combatnum_all:
		it_combatnum = RankData::m_rankCombatNumAll.find(number);
		if (it_combatnum==RankData::m_rankCombatNumAll.end())
		{
			return NULL;
		}
		break;
	case rank_combatnum_zs:
		it_combatnum = RankData::m_rankCombatNumZS.find(number);
		if (it_combatnum==RankData::m_rankCombatNumZS.end())
		{
			return NULL;
		}
		break;
	case rank_combatnum_fs:
		it_combatnum = RankData::m_rankCombatNumFS.find(number);
		if (it_combatnum==RankData::m_rankCombatNumFS.end())
		{
			return NULL;
		}
		break;
	case rank_combatnum_ds:
		it_combatnum = RankData::m_rankCombatNumDS.find(number);
		if (it_combatnum==RankData::m_rankCombatNumDS.end())
		{
			return NULL;
		}
		break;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_combatnum->second.rank).c_str(),"",16);
	if (pTitle1)
	{
		pTitle1->setColor(ccYELLOW);
		pTitle1->setFontSize(18);
		pTitle1->setPosition(pos[0]);
		pItem->addChild(pTitle1);
	}

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_combatnum->second.name.c_str(),"",16);
	if (pTitle2)
	{
		pTitle2->setColor(ccYELLOW);
		pTitle2->setFontSize(18);
		pTitle2->setPosition(pos[1]);
		pItem->addChild(pTitle2);
	}

	//第三列
	std::string guildnamestr="";
	if (it_combatnum->second.guildname=="")
	{
		guildnamestr="-";
	}
	CCLabelTTF* pTitle3 = CCLabelTTF::create(guildnamestr.c_str(),"",16);
	if (pTitle3)
	{
		pTitle3->setColor(ccYELLOW);
		pTitle3->setFontSize(18);
		pTitle3->setPosition(pos[2]);
		pItem->addChild(pTitle3);
	}

	//第四列
	CCLabelTTF* pTitle4 = CCLabelTTF::create(SystemData::intToString(it_combatnum->second.combatnum).c_str(),"",16);
	if (pTitle4)
	{
		pTitle4->setColor(ccYELLOW);
		pTitle4->setFontSize(18);
		pTitle4->setPosition(pos[3]);
		pItem->addChild(pTitle4);
	}

	//第五列
	std::string headstr="";
	if (it_combatnum->second.rank==1 && RankData::getRankPanelType() != rank_combatnum_all)
	{
		switch (it_combatnum->second.job)
		{
		case 1:
			headstr=SystemData::getLayoutString("head_diyizhanshi");
			break;
		case 2:
			headstr=SystemData::getLayoutString("head_diyifashi");
			break;
		case 3:
			headstr=SystemData::getLayoutString("head_diyidaoshi");
			break;
		default:
			break;
		}
	}
	else if(it_combatnum->second.headname==0 )
	{
		headstr="-";
	}

	CCLabelTTF* pTitle5 = CCLabelTTF::create(headstr.c_str(),"",16);
	if (pTitle5)
	{
		pTitle5->setColor(ccYELLOW);
		pTitle5->setFontSize(18);
		pTitle5->setPosition(pos[4]);
		pItem->addChild(pTitle5);
	}

	pItem->setTarget(this,menu_selector(RankRightPanel::singleCB));
	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);

	pItem->setTag(it_combatnum->second.id_to_server);
	return pItem;

}

CCMenuItemImage* RankRightPanel::getSingleInfoByLevel( int number )
{
	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("rank_singleline");

	std::map<int ,Rank_level>::iterator it_level ;

	switch (RankData::getRankPanelType())
	{
	case rank_level_all:
		it_level = RankData::m_rankLevelAll.find(number);
		if (it_level==RankData::m_rankLevelAll.end())
		{
			return NULL;
		}
		break;
	case rank_level_zs:
		it_level = RankData::m_rankLevelZS.find(number);
		if (it_level==RankData::m_rankLevelZS.end())
		{
			return NULL;
		}
		break;
	case rank_level_fs:
		it_level = RankData::m_rankLevelFS.find(number);
		if (it_level==RankData::m_rankLevelFS.end())
		{
			return NULL;
		}
		break;
	case rank_level_ds:
		it_level = RankData::m_rankLevelDS.find(number);
		if (it_level==RankData::m_rankLevelDS.end())
		{
			return NULL;
		}
		break;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_level->second.rank).c_str(),"",16);
	pTitle1->setColor(ccYELLOW);
	pTitle1->setFontSize(18);
	pTitle1->setPosition(pos[0]);
	pItem->addChild(pTitle1);

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_level->second.name.c_str(),"",16);
	pTitle2->setColor(ccYELLOW);
	pTitle2->setFontSize(18);
	pTitle2->setPosition(pos[1]);
	pItem->addChild(pTitle2);

	//第三列
	std::string guildnamestr="";
	if (it_level->second.guildname=="0")
	{
		guildnamestr="-";
	}
	else
	{
		guildnamestr = it_level->second.guildname;
	}
	CCLabelTTF* pTitle3 = CCLabelTTF::create(guildnamestr.c_str(),"",16);
	pTitle3->setColor(ccYELLOW);
	pTitle3->setFontSize(18);
	pTitle3->setPosition(pos[2]);
	pItem->addChild(pTitle3);

	//第四列
	std::string jobstr="";
	switch (it_level->second.job)
	{
	case 1:
		jobstr="战士";
		break;
	case 2:
		jobstr="法师";
		break;
	case 3:
		jobstr="道士";
		break;
	default:
		break;
	}
	CCLabelTTF* pTitle4 = CCLabelTTF::create(AToU8(jobstr.c_str()),"",16);
	pTitle4->setColor(ccYELLOW);
	pTitle4->setFontSize(18);
	pTitle4->setPosition(pos[3]);
	pItem->addChild(pTitle4);

	//第五列
	std::string lvlstr= "";
	if (it_level->second.reborn == 0)
	{
		lvlstr = SystemData::intToString(it_level->second.level) + "级";
	}
	else
	{
		lvlstr =  SystemData::intToString(it_level->second.reborn) + "转" + SystemData::intToString(it_level->second.level) + "级";
	}
	CCLabelTTF* pTitle5 = CCLabelTTF::create(AToU8(lvlstr.c_str()),"",16);
	pTitle5->setColor(ccYELLOW);
	pTitle5->setFontSize(18);
	pTitle5->setPosition(pos[4]);
	pItem->addChild(pTitle5);

	//第六列
	std::string headstr="";
	if (it_level->second.rank==1 && RankData::getRankPanelType()!=rank_level_all)
	{
		switch (it_level->second.job)
		{
		case 1:
			headstr=SystemData::getLayoutString("head_zhanshiderongyao");
			break;
		case 2:
			headstr=SystemData::getLayoutString("head_fashiderongyao");
			break;
		case 3:
			headstr=SystemData::getLayoutString("head_daoshiderongyao");
			break;
		default:
			break;
		} 
	}
	else if (it_level->second.rank==1 && RankData::getRankPanelType()==rank_level_all)
	{
		headstr=SystemData::getLayoutString("head_tianxiadiyi");
	}
	else if (it_level->second.headname==0)
	{
		headstr="-";
	}
	CCLabelTTF* pTitle6 = CCLabelTTF::create(headstr.c_str(),"",16);
	pTitle6->setColor(ccYELLOW);
	pTitle6->setFontSize(18);
	pTitle6->setPosition(pos[5]);
	pItem->addChild(pTitle6);


	pItem->setTarget(this,menu_selector(RankRightPanel::singleCB));
	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);

	pItem->setTag(it_level->second.id_to_server);
	return pItem;
}

CCMenuItemImage* RankRightPanel::getSingleInfoByPet( int number )
{
	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("rank_singleline");

	std::map<int ,Rank_pet>::iterator it_pet = RankData::m_rankPet.find(number);
	if (it_pet==RankData::m_rankPet.end())
	{
		return NULL;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_pet->second.rank).c_str(),"",16);
	pTitle1->setColor(ccYELLOW);
	pTitle1->setFontSize(18);
	pTitle1->setPosition(pos[0]);
	pItem->addChild(pTitle1);

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_pet->second.name.c_str(),"",16);
	pTitle2->setColor(ccYELLOW);
	pTitle2->setFontSize(18);
	pTitle2->setPosition(pos[1]);
	pItem->addChild(pTitle2);

	//第三列
	CCLabelTTF* pTitle3 = CCLabelTTF::create(it_pet->second.petname.c_str(),"",16);
	pTitle3->setColor(ccYELLOW);
	pTitle3->setFontSize(18);
	pTitle3->setPosition(pos[2]);
	pItem->addChild(pTitle3);

	//第四列
	CCLabelTTF* pTitle4 = CCLabelTTF::create(SystemData::intToString(it_pet->second.petstars).c_str(),"",16);
	pTitle4->setColor(ccYELLOW);
	pTitle4->setFontSize(18);
	pTitle4->setPosition(pos[3]);
	pItem->addChild(pTitle4);


	pItem->setTarget(this,menu_selector(RankRightPanel::singleCB));
	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);

	pItem->setTag(it_pet->second.id_to_server);
	return pItem;
}

CCMenuItemImage* RankRightPanel::getSingleInfoByMoney( int number )
{
	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("rank_singleline");

	std::map<int ,Rank_money>::iterator it_money = RankData::m_rankMoney.find(number);
	if (it_money==RankData::m_rankMoney.end())
	{
		return NULL;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_money->second.rank).c_str(),"",16);
	pTitle1->setColor(ccYELLOW);
	pTitle1->setFontSize(18);
	pTitle1->setPosition(pos[0]);
	pItem->addChild(pTitle1);

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_money->second.name.c_str(),"",16);
	pTitle2->setColor(ccYELLOW);
	pTitle2->setFontSize(18);
	pTitle2->setPosition(pos[1]);
	pItem->addChild(pTitle2);

	//第三列
	std::string jobstr="";
	switch (it_money->second.job)
	{
	case 1:
		jobstr="战士";
		break;
	case 2:
		jobstr="法师";
		break;
	case 3:
		jobstr="道士";
		break;
	default:
		break;
	}
	CCLabelTTF* pTitle3 = CCLabelTTF::create(AToU8(jobstr.c_str()),"",16);
	pTitle3->setColor(ccYELLOW);
	pTitle3->setFontSize(18);
	pTitle3->setPosition(pos[2]);
	pItem->addChild(pTitle3);

	//第四列
	std::string lvlstr= "";
	if (it_money->second.reborn == 0)
	{
		lvlstr = SystemData::intToString(it_money->second.level) + "级";
	}
	else
	{
		lvlstr =  SystemData::intToString(it_money->second.reborn) + "转" + SystemData::intToString(it_money->second.level) + "级";
	}
	CCLabelTTF* pTitle4 = CCLabelTTF::create(AToU8(lvlstr.c_str()),"",16);
	pTitle4->setColor(ccYELLOW);
	pTitle4->setFontSize(18);
	pTitle4->setPosition(pos[3]);
	pItem->addChild(pTitle4);

	//第五列
	CCLabelTTF* pTitle5 = CCLabelTTF::create(SystemData::intToString(it_money->second.money).c_str(),"",16);
	pTitle5->setColor(ccYELLOW);
	pTitle5->setFontSize(18);
	pTitle5->setPosition(pos[4]);
	pItem->addChild(pTitle5);

	pItem->setTarget(this,menu_selector(RankRightPanel::singleCB));
	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);

	pItem->setTag(it_money->second.id_to_server);

	return pItem;
}

CCMenuItemImage* RankRightPanel::getSingleInfoByGuildLevel( int number )
{
	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("rank_singleline");

	std::map<int ,Rank_guildlevel>::iterator it_guildlevel = RankData::m_rankGuildLevel.find(number);
	if (it_guildlevel==RankData::m_rankGuildLevel.end())
	{
		return NULL;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_guildlevel->second.rank).c_str(),"",16);
	pTitle1->setColor(ccYELLOW);
	pTitle1->setFontSize(18);
	pTitle1->setPosition(pos[0]);
	pItem->addChild(pTitle1);

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_guildlevel->second.guildname.c_str(),"",16);
	pTitle2->setColor(ccYELLOW);
	pTitle2->setFontSize(18);
	pTitle2->setPosition(pos[1]);
	pItem->addChild(pTitle2);

	//第三列
	CCLabelTTF* pTitle3 = CCLabelTTF::create(SystemData::intToString(it_guildlevel->second.guildlevel).c_str(),"",16);
	pTitle3->setColor(ccYELLOW);
	pTitle3->setFontSize(18);
	pTitle3->setPosition(pos[2]);
	pItem->addChild(pTitle3);

	//第四列
	CCLabelTTF* pTitle4 = CCLabelTTF::create(it_guildlevel->second.guildheadname.c_str(),"",16);
	pTitle4->setColor(ccYELLOW);
	pTitle4->setFontSize(18);
	pTitle4->setPosition(pos[3]);
	pItem->addChild(pTitle4);

	//第五列
	CCLabelTTF* pTitle5 = CCLabelTTF::create(SystemData::intToString(it_guildlevel->second.workers).c_str(),"",16);
	pTitle5->setColor(ccYELLOW);
	pTitle5->setFontSize(18);
	pTitle5->setPosition(pos[4]);
	pItem->addChild(pTitle5);

	pItem->setTarget(this,menu_selector(RankRightPanel::singleCB));
	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);

	pItem->setTag(it_guildlevel->second.id_to_server);
	return pItem;

}

CCMenuItemImage* RankRightPanel::getSingleInfoByGuildYLT( int number )
{
	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("rank_singleline");

	std::map<int ,Rank_guildlyt>::iterator it_guildlyt  = RankData::m_rankGuildLYT.find(number);
	if (it_guildlyt==RankData::m_rankGuildLYT.end())
	{
		return NULL;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_guildlyt->second.rank).c_str(),"",16);
	pTitle1->setColor(ccYELLOW);
	pTitle1->setFontSize(18);
	pTitle1->setPosition(pos[0]);
	pItem->addChild(pTitle1);

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_guildlyt->second.guildname.c_str(),"",16);
	pTitle2->setColor(ccYELLOW);
	pTitle2->setFontSize(18);
	pTitle2->setPosition(pos[1]);
	pItem->addChild(pTitle2);

	//第三列
	CCLabelTTF* pTitle3 = CCLabelTTF::create(SystemData::intToString(it_guildlyt->second.killcnt).c_str(),"",16);
	pTitle3->setColor(ccYELLOW);
	pTitle3->setFontSize(18);
	pTitle3->setPosition(pos[2]);
	pItem->addChild(pTitle3);

	//第四列
	CCLabelTTF* pTitle4 = CCLabelTTF::create(it_guildlyt->second.guildheadname.c_str(),"",16);
	pTitle4->setColor(ccYELLOW);
	pTitle4->setFontSize(18);
	pTitle4->setPosition(pos[3]);
	pItem->addChild(pTitle4);

	//第五列
	CCLabelTTF* pTitle5 = CCLabelTTF::create(SystemData::intToString(it_guildlyt->second.workers).c_str(),"",16);
	pTitle5->setColor(ccYELLOW);
	pTitle5->setFontSize(18);
	pTitle5->setPosition(pos[4]);
	pItem->addChild(pTitle5);

	pItem->setTarget(this,menu_selector(RankRightPanel::singleCB));
	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);

	pItem->setTag(it_guildlyt->second.id_to_server);
	return pItem;
}

void RankRightPanel::singleCB( CCObject* pSender )
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		if (RankData::getRankPanelType()==rank_combatnum_all ||
			RankData::getRankPanelType()==rank_combatnum_zs ||
			RankData::getRankPanelType()==rank_combatnum_fs ||
			RankData::getRankPanelType()==rank_combatnum_ds ||
			RankData::getRankPanelType()==rank_level_all  ||
			RankData::getRankPanelType()==rank_level_zs  ||
			RankData::getRankPanelType()==rank_level_fs  ||
			RankData::getRankPanelType()==rank_level_ds  ||
			RankData::getRankPanelType()==rank_rich_all  ||
			RankData::getRankPanelType()==rank_pet_all  ||
			RankData::getRankPanelType()==rank_firework  
			)
		{
			//打开查看角色的界面
			MsgGetOtherPlayerDataRequest* msg=new MsgGetOtherPlayerDataRequest;
			msg->pid = tag;
			HandleMessage::sendMessage(msg);
		}

	}
}

void RankRightPanel::updateMaxPage()
{
	switch (RankData::getRankPanelType())
	{
	case rank_combatnum_all:
		m_iMaxPage = (RankData::m_rankCombatNumAll.size()-1)/9+1;
		break;
	case rank_combatnum_zs:
		m_iMaxPage = (RankData::m_rankCombatNumZS.size()-1)/9+1;
		break;
	case rank_combatnum_fs:
		m_iMaxPage = (RankData::m_rankCombatNumFS.size()-1)/9+1;
		break;
	case rank_combatnum_ds:
		m_iMaxPage = (RankData::m_rankCombatNumDS.size()-1)/9+1;
		break;
	case rank_level_all	:
		m_iMaxPage = (RankData::m_rankLevelAll.size()-1)/9+1;
		break;
	case rank_level_zs:
		m_iMaxPage = (RankData::m_rankLevelZS.size()-1)/9+1;
		break;
	case rank_level_fs:
		m_iMaxPage = (RankData::m_rankLevelFS.size()-1)/9+1;
		break;
	case rank_level_ds:
		m_iMaxPage = (RankData::m_rankLevelDS.size()-1)/9+1;
		break;
	case rank_pet_all:
		m_iMaxPage = (RankData::m_rankPet.size()-1)/9+1;
		break;
	case rank_rich_all:
		m_iMaxPage = (RankData::m_rankMoney.size()-1)/9+1;
		break;
	case rank_guild_level:
		m_iMaxPage = (RankData::m_rankGuildLevel.size()-1)/9+1;
		break;
	case rank_guild_lyt:
		m_iMaxPage = (RankData::m_rankGuildLYT.size()-1)/9+1;
		break;
	case rank_firework:
		m_iMaxPage = (RankData::m_rankFireWork.size()-1)/9+1;
		break;
	default:
		m_iMaxPage = 1;
		break;
	}
	if (m_iMaxPage>10 ||m_iMaxPage<0)
	{
		m_iMaxPage = 1;
	}

	if (m_pPage)
	{
		CCString* pStr = CCString::createWithFormat("%d / %d",m_iCurPage,m_iMaxPage);
		m_pPage->setString(pStr->getCString());
	}

}

CCMenuItemImage* RankRightPanel::getSingleInfoByFireWork( int number )
{

	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("rank_singleline");

	std::map<int ,Rank_firework>::iterator it_firework = RankData::m_rankFireWork.find(number);
	if (it_firework==RankData::m_rankFireWork.end())
	{
		return NULL;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_firework->second.rank).c_str(),"",16);
	pTitle1->setColor(ccYELLOW);
	pTitle1->setFontSize(18);
	pTitle1->setPosition(pos[0]);
	pItem->addChild(pTitle1);

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_firework->second.name.c_str(),"",16);
	pTitle2->setColor(ccYELLOW);
	pTitle2->setFontSize(18);
	pTitle2->setPosition(pos[1]);
	pItem->addChild(pTitle2);

	//第三列
	CCLabelTTF* pTitle3 = CCLabelTTF::create(SystemData::intToString(it_firework->second.level).c_str(),"",16);
	pTitle3->setColor(ccYELLOW);
	pTitle3->setFontSize(18);
	pTitle3->setPosition(pos[2]);
	pItem->addChild(pTitle3);

	//第四列
	CCLabelTTF* pTitle5 = CCLabelTTF::create(SystemData::intToString(it_firework->second.fireworkcnt).c_str(),"",16);
	pTitle5->setColor(ccYELLOW);
	pTitle5->setFontSize(18);
	pTitle5->setPosition(pos[4]);
	pItem->addChild(pTitle5);

	pItem->setTarget(this,menu_selector(RankRightPanel::singleCB));
	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);

	pItem->setTag(it_firework->second.id_to_server);
	return pItem;

}
