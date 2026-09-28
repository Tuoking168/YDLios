#include "BuffExPanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"
#include "ext/GeneralMenu.h"
#include "scene/panel/MainPanel.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "event/CPEventHelper.h"
#include "userdata/HeroData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "MainUIModule.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/luadata/LuaData.h"
#include "utils/StringUtils.h"
#include "userdata/ActivityData.h"

BuffExPanel::BuffExPanel()
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

BuffExPanel::~BuffExPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool BuffExPanel::init()
{
	updateBuff();
	return true;
}

void BuffExPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessagePlayerUpdGeneNotify" ||
			source == "HandleMessagePlayerRmvGeneNotify")
		{
			updateBuff();
		}
	}
}

void BuffExPanel::updateBuff()
{
	removeAllChildren();

	CCPoint pos = CCPointZero;
	CCLabelTTF* pLabel = SystemData::getLabelTTF("buffpanel_text");
	pLabel->setFontSize(16);
	pLabel->setColor(ccWHITE);
	pLabel->setAnchorPoint(CCPointZero);
	pLabel->setPosition(CCPointZero);
	addChild(pLabel);

	const CCPoint &firstPt = ccp(pLabel->getContentSize().width+5,pLabel->getContentSize().height);//LayoutData::getPoint(CPModuleName::MAIN_UI, "buffFirst");
	const int ox = 50;// LayoutData::getInt(CPModuleName::MAIN_UI, "buffOx");
	const int oy = 40;
	std::string iconKey;
	int n = 0;
	int m = 0;
	bool flag = false;
	const IDVector &vect = HeroData::getBuffVect();
	CCMenuEx* pMenu = CCMenuEx::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	for (int i = 0; i < (int)vect.size(); i++)
	{
		iconKey.clear();
		StaticData::getGeneIcon(vect[i], iconKey);
		if (!iconKey.empty() && iconKey != "0")
		{
			CCSprite *iconsprite = LayoutData::getSpriteByFrameName(iconKey);
			CCMenuItemSprite* icon = CCMenuItemSprite::create(iconsprite,NULL,NULL,this,menu_selector(BuffExPanel::buffCallBack));
			if (icon)
			{
				//icon->setScale(1.5f);
				icon->setAnchorPoint(ccp(0,1));
				icon->setTag(i);
				icon->setPosition(ccp(firstPt.x + n * ox, firstPt.y - m * oy));
				pMenu->addChild(icon);
				n++;
				flag = true;
				if (icon->getPositionY()<pos.y)
				{
					pos.y = icon->getPositionY()-10;
				}
			}
		}
		if (n==4)
		{
			n=0;
			m++;
		}
	}

	if (!flag)
	{
		CCLabelTTF* pNull = SystemData::getLabelTTF("attribute_Base_null");
		pNull->setFontSize(16);
		pNull->setColor(ccWHITE);
		pNull->setAnchorPoint(CCPointZero);
		pNull->setPosition(ccp(pLabel->getPositionX()+pLabel->getContentSize().width+5,pLabel->getPositionY()));
		addChild(pNull);
	}

	this->setContentSize(CCSizeMake(SystemData::getLayoutValue("attribute_Base_Content.w"),-pos.y+m*5));
}

void BuffExPanel::buffCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		Game::getGameUI()->showBuffTips(tag);
	}
}

//---------------------------------------------------------------------------------------------------------//

BuffTips::BuffTips():
	m_pTime(NULL),
	m_iTag(0),
	m_iOddTime(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);

}

BuffTips::~BuffTips()
{

	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}

BuffTips* BuffTips::create( int tag )
{
	BuffTips* p = new BuffTips;
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

bool BuffTips::init( int tag )
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
	const IDVector &vect = HeroData::getBuffVect();
	m_iTag = vect[tag];
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

	int curtime = ActivityData::getWorldTime();
	int starttime = HeroData::getBuffStartTime(m_iTag);
	m_iOddTime = HeroData::getBuffTime(m_iTag) - (curtime - starttime);

	if (m_iOddTime>0)
	{
		m_pTime = CCLabelTTF::create(StringUtils::timeToString(m_iOddTime,TimeType::hms).c_str(),"",16);
		m_pTime->setAnchorPoint(CCPointZero);
		m_pTime->setPosition(ccp(picon->getPositionX()+picon->getContentSize().width/2 + 10,picon->getPositionY()));
		addChild(m_pTime);
	}


	return true;
}

void BuffTips::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			if (m_iOddTime>0)
			{
				m_iOddTime--;
			}
			else
			{
				return;
			}
			if (m_pTime)
			{
				m_pTime->setString(StringUtils::timeToString(m_iOddTime,TimeType::hms).c_str());
			}
			if (m_iOddTime==0)
			{
				this->removeFromParent();
			}
		}
	}
}
