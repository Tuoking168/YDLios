#include "CombinedServerRankPanel.h"
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
#include "scene/Game.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/GameUI.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/HeroData.h"
#include "utils/StringUtils.h"
#include "EvtDataDefinition.h"
#include "MsgActivity.h"

CombinedServerRankPanel::CombinedServerRankPanel():
	m_iCurType(rank_combined_chongzhi),m_TimeLabel(NULL),pDownTitle(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::UI_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

CombinedServerRankPanel::~CombinedServerRankPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::UI_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}

bool CombinedServerRankPanel::init()//跨服排行榜
{
	if (!FullScreenPanel::init())
	{
		return false;
	} 
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	RankData::setRankPanelType(rank_combined_chongzhi);

	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist("rank_border",SystemData::getLayoutValue("rank_border.w"),SystemData::getLayoutValue("rank_border.h"));
	pBorder->setPosition(ccp(3,4));
	pBorder->setAnchorPoint(CCPointZero);
	addChild(pBorder);
	 
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "combinedRankTitle");
	addChild(title);

	m_pMenu = GeneralMenu::create();
	m_pMenu->setAnchorPoint(CCPointZero);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCLabelTTF* pchongzhi=CCLabelTTF::create(SystemData::getLayoutString("combinedrank_chongzhi").c_str(),"微软雅黑",18);
	CCScale9Sprite* pchongzhi1=SystemData::getScale9SpriteByPlist("rank_leftbtn",pchongzhi->getContentSize().width+30,pchongzhi->getContentSize().height+10);
	CCScale9Sprite* pchongzhi2=SystemData::getScale9SpriteByPlist("rank_leftbtn.sel",pchongzhi->getContentSize().width+30,pchongzhi->getContentSize().height+10);
	CCMenuItemSprite* pchongzhiTitle=CCMenuItemSprite::create(pchongzhi1,pchongzhi2,NULL,this,menu_selector(CombinedServerRankPanel::chongzhi));
	if (pchongzhiTitle)
	{
		pchongzhiTitle->setPosition(SystemData::getLayoutPoint("combinedrank_chongzhi"));
		pchongzhi->setPosition(ccp(pchongzhiTitle->getContentSize().width/2, pchongzhiTitle->getContentSize().height/2));
		pchongzhiTitle->addChild(pchongzhi);
		m_pMenu->addChild(pchongzhiTitle);
	}

	CCLabelTTF* pleijichongzhi = CCLabelTTF::create(SystemData::getLayoutString("combinedrank_leijichongzhi").c_str(),"微软雅黑",18);
	CCScale9Sprite* pleijichongzhi1=SystemData::getScale9SpriteByPlist("rank_leftbtn",pchongzhi->getContentSize().width*2+30,pchongzhi->getContentSize().height+15);
	CCScale9Sprite* pleijichongzhi2=SystemData::getScale9SpriteByPlist("rank_leftbtn.sel",pchongzhi->getContentSize().width*2+30,pchongzhi->getContentSize().height+15);
	CCMenuItemSprite* pleijichongzhiTitle=CCMenuItemSprite::create(pleijichongzhi1,pleijichongzhi2,NULL,this,menu_selector(CombinedServerRankPanel::BtnCB));
	if (pleijichongzhiTitle)
	{
		pleijichongzhiTitle->setTag(rank_combined_chongzhi);
		pleijichongzhiTitle->setPosition(SystemData::getLayoutPoint("combinedrank_leijichongzhi"));
		pleijichongzhi->setPosition(ccp(pleijichongzhiTitle->getContentSize().width/2, pleijichongzhiTitle->getContentSize().height/2));
		pleijichongzhiTitle->addChild(pleijichongzhi);
		m_pMenu->addChild(pleijichongzhiTitle);
	}
	
	CCLabelTTF* pxiaofei = CCLabelTTF::create(SystemData::getLayoutString("combinedrank_xiaofei").c_str(),"微软雅黑",18);
	CCScale9Sprite* pxiaofei1=SystemData::getScale9SpriteByPlist("rank_leftbtn",pchongzhi->getContentSize().width*2+30,pchongzhi->getContentSize().height+15);
	CCScale9Sprite* pxiaofei2=SystemData::getScale9SpriteByPlist("rank_leftbtn.sel",pchongzhi->getContentSize().width*2+30,pchongzhi->getContentSize().height+15);
	CCMenuItemSprite* pxiaofeiTitle=CCMenuItemSprite::create(pxiaofei1,pxiaofei2,NULL,this,menu_selector(CombinedServerRankPanel::BtnCB));
	if (pxiaofeiTitle)
	{
		pxiaofeiTitle->setTag(rank_combined_xiaofei);
		pxiaofeiTitle->setPosition(SystemData::getLayoutPoint("combinedrank_xiaofei"));
		pxiaofei->setPosition(ccp(pxiaofeiTitle->getContentSize().width/2, pxiaofeiTitle->getContentSize().height/2));
		pxiaofeiTitle->addChild(pxiaofei);
		//m_pMenu->addChild(pxiaofeiTitle);
	}

	m_iCurType == rank_combined_chongzhi?pleijichongzhiTitle->selected():pxiaofeiTitle->selected();
	 
	CCLabelTTF* pUpTitle = SystemData::getLabelTTF("combinedrank_uptitle");
	pUpTitle->setFontSize(18);
	pUpTitle->setColor(ccWHITE);
	addChild(pUpTitle);

	m_TimeLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "combinedTime");
	addChild(m_TimeLabel);
	
	pDownTitle = SystemData::getLabelTTF("combinedrank_downtitle"); 
	pDownTitle->setFontSize(18);
	pDownTitle->setColor(ccWHITE); 
	addChild(pDownTitle);

	m_pRightMenu = CombinedServerRankRightPanel::create();
	m_pRightMenu->setPosition(SystemData::getLayoutPoint("rank_rightborder"));
	m_pRightMenu->setAnchorPoint(CCPointZero);
	addChild(m_pRightMenu);

	schedule(SEL_SCHEDULE(&CombinedServerRankPanel::onMove),0.1f);
	return true;
}

void CombinedServerRankPanel::onMove(float i)
{
	pDownTitle->setPositionX(pDownTitle->getPositionX()-5);
	if (pDownTitle->getPositionX() <= -500)
	{
		pDownTitle->setPositionX(1280);
	}
}

void CombinedServerRankPanel::onEnter()
{
	FullScreenPanel::onEnter();
	setScale(0.0f);
	runAction(CPNodeHelper::getScaleToBig());	
}

void CombinedServerRankPanel::refreshTime()
{
	int time = HeroData::getRewardTime(EvtData::rw_rwkfcz);
	const ccColor3B &red = LayoutData::getColor3(CPModuleName::COMMON, "red");
	const ccColor3B &green = LayoutData::getColor3(CPModuleName::COMMON, "green");

	ccColor3B color = ((time > 0) ? green : red);
	m_TimeLabel->setString((time>0)?StringUtils::timeToString(time, TimeType::dhms).c_str():SystemData::getLayoutString("combinedrank_huodongjieshu").c_str());
	m_TimeLabel->setColor(color);
}

void CombinedServerRankPanel::chongzhi( CCObject* pSender )
{
	CPEventHelper::openPanel("RechargePanel");
}

void CombinedServerRankPanel::BtnCB( CCObject* pSender )
{
	CCMenuItemSprite* pNode = dynamic_cast<CCMenuItemSprite*>(pSender);
	
	if (pNode)
	{
		int tag = pNode->getTag();
		if (tag == rank_combined_xiaofei)
		{
			CPEventHelper::msgResponse("","",3);
			return;
		}
		if(m_iCurType==tag)
		{
			pNode->selected();
			return;
		}
		pNode->selected();
		CCMenuItemSprite* pChild = dynamic_cast<CCMenuItemSprite*>(m_pMenu->getChildByTag(m_iCurType));
		pChild->unselected();
		m_iCurType = tag;
		RankData::setRankPanelType(tag);
		if (m_pRightMenu)
		{
			m_pRightMenu->initTop();
		}		
	}
}

void CombinedServerRankPanel::hide()
{
	this->removeFromParent();
}

void CombinedServerRankPanel::onSwitch(int tag)
{

}

void CombinedServerRankPanel::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (evtSource == "TimeManager")
		{
			refreshTime();
		}
	}
}


//------------------------------------------------------------------------------------------------------//

CombinedServerRankRightPanel::CombinedServerRankRightPanel():
	m_pInfoMenu(NULL),
	m_pTopLabel(NULL),
	m_iCurPage(1),
	m_iMaxPage(1),
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

CombinedServerRankRightPanel::~CombinedServerRankRightPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::UI_CHANGE, this);
}

bool CombinedServerRankRightPanel::init()
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
	CCMenuItemSprite* pshouyeTitle=CCMenuItemSprite::create(pshouye1,pshouye2,NULL,this,menu_selector(CombinedServerRankRightPanel::shouyeCB));
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
	CCMenuItemSprite* pshangyiyeTitle=CCMenuItemSprite::create(pshangyiye1,pshangyiye2,NULL,this,menu_selector(CombinedServerRankRightPanel::shangyiyeCB));
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
	CCMenuItemSprite* pxiayiyeTitle=CCMenuItemSprite::create(pxiayiye1,pxiayiye2,NULL,this,menu_selector(CombinedServerRankRightPanel::xiayiyeCB));
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
	CCMenuItemSprite* pmoyeTitle=CCMenuItemSprite::create(pmoye1,pmoye2,NULL,this,menu_selector(CombinedServerRankRightPanel::moyeCB));
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

static std::string combinedTop[7] = {
	"rank_sTitle1","rank_sTitle16","rank_sTitle2","rank_sTitle3","rank_sTitle17","rank_sTitle19","rank_sTitle18"
};

void CombinedServerRankRightPanel::initTop()
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
	updateMaxPage();
	std::string strlist[6];		
	for (int i=0;i<6;i++)
	{
		strlist[i]=combinedTop[(i==4&&RankData::getRankPanelType()==rank_combined_xiaofei)?6:i];
	}

	int labelwidth = 0;
	int addwidth = SystemData::getLayoutValue("rank_rightborder.w")/6;
	for (int i=0;i<6;i++)
	{
		CCLabelTTF* pTitle = SystemData::getLabelTTF(strlist[i].c_str());
		pTitle->setColor(ccYELLOW);
		pTitle->setFontSize(18);
		pTitle->setPosition(ccp(SystemData::getLayoutValue("rank_sTitle.x")+labelwidth,SystemData::getLayoutValue("rank_sTitle.y")));
		m_pTopLabel->addChild(pTitle);
		labelwidth += addwidth;
		pos[i] = ccp(pTitle->getPositionX(),SystemData::getLayoutValue("rank_singleline.h")/2);
	}
	addInfoByPage();
}

void CombinedServerRankRightPanel::shouyeCB( CCObject* pSender )
{
	if (m_iCurPage!=1)
	{
		m_iCurPage = 1;
	}
	addInfoByPage();
}

void CombinedServerRankRightPanel::shangyiyeCB( CCObject* pSender )
{
	if (m_iCurPage>m_iMinPage)
	{
		m_iCurPage--;
	}
	addInfoByPage();
}

void CombinedServerRankRightPanel::xiayiyeCB( CCObject* pSender )
{
	if (m_iCurPage<m_iMaxPage)
	{
		m_iCurPage++;
	}
	addInfoByPage();
}

void CombinedServerRankRightPanel::moyeCB( CCObject* pSender )
{
	if (m_iCurPage!=m_iMaxPage)
	{
		m_iCurPage = m_iMaxPage;
	}
	addInfoByPage();
}

void CombinedServerRankRightPanel::addInfoByPage()
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

	CPUpdater* p = CPUpdater::create(this,cpupdater_selector(CombinedServerRankRightPanel::addSingleInfo));
	p->setUpdateTimes(7);
	m_pInfoMenu->addChild(p);
	p->start();
}

void CombinedServerRankRightPanel::addSingleInfo( int number )
{
	if (m_pInfoMenu)
	{
		CCMenuItemImage* pItem = getSingleInfo(number+1);
		if (pItem)
		{
			pItem->setAnchorPoint(CCPointZero);
			pItem->setPosition(ccp(0,318-number*pItem->getContentSize().height));
			m_pInfoMenu->addChild(pItem);
		}
	}
}

void CombinedServerRankRightPanel::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::UI_CHANGE)
	{
		if (evtSource == "CombinedPanel")
		{
			initTop();
		}
		else if (evtSource == "HandleMessageGetWorldChartNotify")
		{
			updateMaxPage();
		}
	}
}

CCMenuItemImage* CombinedServerRankRightPanel::getSingleInfo( int number )
{
	int realnumber = number + (m_iCurPage-1)*7;
	CCMenuItemImage* pItem = SystemData::getScale9MenuItemImageByPlist("combinedrank_singleline");

	std::map<int ,Rank_combined>::iterator it_combined ;

	switch (RankData::getRankPanelType())
	{
	case rank_combined_chongzhi:
		it_combined = RankData::m_rankCombined.find(realnumber);
		if (it_combined==RankData::m_rankCombined.end())
		{
			return NULL;
		}
		break;
	case rank_combined_xiaofei:
		it_combined = RankData::m_rankCombined2.find(realnumber);
		if (it_combined==RankData::m_rankCombined2.end())
		{
			return NULL;
		}
		break;
	default:
		break;
	}

	//第一列
	CCLabelTTF* pTitle1 = CCLabelTTF::create(SystemData::intToString(it_combined->second.rank).c_str(),"",18);
	if (pTitle1)
	{
		pTitle1->setColor(ccYELLOW);
		pTitle1->setFontSize(18);
		pTitle1->setPosition(pos[0]);
		pItem->addChild(pTitle1);
	}

	//第二列
	CCLabelTTF* pTitle2 = CCLabelTTF::create(it_combined->second.servername.c_str(),"",18);
	if (pTitle2)
	{
		pTitle2->setColor(ccYELLOW);
		pTitle2->setFontSize(18);
		pTitle2->setPosition(pos[1]);
		pItem->addChild(pTitle2);
	}

	//第三列
	CCLabelTTF* pTitle3 = CCLabelTTF::create(it_combined->second.name.c_str(),"",18);
	if (pTitle3)
	{
		pTitle3->setColor(ccYELLOW);
		pTitle3->setFontSize(18);
		pTitle3->setPosition(pos[2]);
		pItem->addChild(pTitle3);
	}

	//第四列
	std::string guildnamestr=it_combined->second.guildname;
	if (it_combined->second.guildname=="")
	{
		guildnamestr="-";
	}
	CCLabelTTF* pTitle4 = CCLabelTTF::create(guildnamestr.c_str(),"",18);
	if (pTitle4)
	{
		pTitle4->setColor(ccYELLOW);
		pTitle4->setFontSize(18);
		pTitle4->setPosition(pos[3]);
		pItem->addChild(pTitle4);
	}

	//第五列
	CCLabelTTF* pTitle5 = CCLabelTTF::create(it_combined->second.rechargeamount.c_str(),"",18);
	if (pTitle5)
	{
		pTitle5->setColor(ccYELLOW);
		pTitle5->setFontSize(18);
		pTitle5->setPosition(pos[4]);
		pItem->addChild(pTitle5);
	}

	//第六列
	GeneralMenu* pMenu = GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	pItem->addChild(pMenu);

	CCLabelTTF* pTitle6=CCLabelTTF::create(SystemData::getLayoutString("combinedrank_zhizunlibao").c_str(),"微软雅黑",18);
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("rank_btn",pTitle6->getContentSize().width+25,pTitle6->getContentSize().height+15);
	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("rank_btn.sel",pTitle6->getContentSize().width+25,pTitle6->getContentSize().height+15);
	CCMenuItemSprite* pTitle=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(CombinedServerRankRightPanel::libaoCB));
	if (pTitle)
	{
		pTitle->setTag(it_combined->second.rank);
		pTitle->setPosition(ccp(pos[5].x,pos[5].y+5));
		pTitle6->setPosition(ccp(pTitle->getContentSize().width/2, pTitle->getContentSize().height/2));
		pTitle->addChild(pTitle6);
		pMenu->addChild(pTitle);
	}

	CCSprite* p =CCSprite::create();
	p->setContentSize(pItem->getNormalImage()->getContentSize());
	pItem->setNormalImage(p);
	return pItem;

}

void CombinedServerRankRightPanel::updateMaxPage()
{
	switch (RankData::getRankPanelType())
	{
	case rank_combined_chongzhi:
		m_iMaxPage = (RankData::m_rankCombined.size()-1)/7 + 1;
		break;
	case rank_combined_xiaofei:
		m_iMaxPage = (RankData::m_rankCombined2.size()-1)/7 +1;
		break;
	default:
		m_iMaxPage = 1;
		break;
	}
	if (m_iMaxPage <= 0 || m_iMaxPage > 15)
		m_iMaxPage = 1;
	if (m_pPage)
	{
		CCString* pStr = CCString::createWithFormat("%d / %d",m_iCurPage,m_iMaxPage);
		m_pPage->setString(pStr->getCString());
	}

}

void CombinedServerRankRightPanel::libaoCB( CCObject* pSender )
{
	CCMenuItemSprite* pNode = dynamic_cast<CCMenuItemSprite*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		int sid = SystemData::getLayoutValue("combinedrank_libaoid");
		if(tag == 1){}
		else if (tag == 2)
			sid +=1;
		else if (tag == 3)
			sid += 2;
		else if (tag >= 4 && tag <= 6)
			sid += 3;
		else if (tag >= 7 && tag <= 10)
			sid += 4;
		else if(tag >= 11 && tag <= 20)
			sid += 5;
		else if (tag >= 21 && tag <= 30)
			sid += 6;
		else if (tag >= 31 && tag <= 50)
			sid += 7;
		else
			sid += 8;
		UserItem* pItem = CommonFunction::createNewItem(sid);
		Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
	}
}

