#include "BoothSellBook.h"
#include "userData/SystemData.h"
#include "utils/StringUtils.h"
#include "userdata/LayoutData.h"
#include "userdata/BoothData.h"
#include "userdata/StaticData.h"
#include "userdata/HeroData.h"
#include "userdata/luadata/LuaData.h"
#include "EntityDefinition.h"
#include "userdata/ActivityData.h"
#include "MsgPet.h"
#include "network/HandleMessage.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"


BoothSellBook::BoothSellBook()
{

}

BoothSellBook::~BoothSellBook()
{

}

bool BoothSellBook::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initUI();
	return true;
}

void BoothSellBook::initUI()
{
	CCSize bgSize = SystemData::getLayoutSize("boothsellbook.frame.bigbg");
	CCPoint bgPoint = SystemData::getLayoutPoint("boothsellbook.frame.bigbg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",bgSize.width,bgSize.height);
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(bgPoint);
	addChild(bg);

	m_nHeight=bgSize.height;
	m_nWidth=bgSize.width;

	addCover(bg->getPosition());

	GeneralMenu* menu = GeneralMenu::create();
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(bgPoint);
	addChild(menu);

	//整体分4个部分
	for (int i = 0; i < 4; i++)
	{ 
		CCSize size1 = SystemData::getLayoutSize("boothsellbook.frame.bg"+StringUtils::toString(i));
		CCPoint point1 = SystemData::getLayoutPoint("boothsellbook.frame.bg"+StringUtils::toString(i));
		CCScale9Sprite *frame1=SystemData::getScale9SpriteByPlist("boothsellbook.frame.bg",size1.width,size1.height); 
		frame1->setAnchorPoint(CCPointZero);  
		frame1->setPosition(point1); 
		addChild(frame1);
	}

	CCSprite *pback1=SystemData::getSpriteByPlist("boothsellbook_biaoti_back");
	pback1->setPosition(ccp(556,374));
	addChild(pback1);

	CCSprite* biaoti1 = SystemData::getSpriteByPlist("boothsellbook_word_biaoti01");
	biaoti1->setPosition(pback1->getPosition());
	addChild(biaoti1);

	CCSprite *pback2=SystemData::getSpriteByPlist("boothsellbook_biaoti_back");
	pback2->setPosition(ccp(556,214));
	addChild(pback2);

	CCSprite* biaoti2 = SystemData::getSpriteByPlist("boothsellbook_word_biaoti02");
	biaoti2->setPosition(pback2->getPosition());
	addChild(biaoti2);

	CCMenuItem* queding = SystemData::getMenuItemImageByPlist("btn_boothbook_queding");
	queding->setTarget(this,menu_selector(BoothSellBook::bottonCallBack));
	queding->setPosition(ccp(150,25));
	menu->addChild(queding);

	CCLabelTTF* QD = SystemData::getLabelTTF("panel_QueDing_label");
	QD->setFontSize(20);
	QD->setColor(ccWHITE);
	QD->setPosition(LayoutData::getCenter(queding->getContentSize()));
	queding->addChild(QD);

	SellBook* sellbook = SellBook::create();
	addChild(sellbook);

	int gold = sellbook->getGold();
	int vcoin = sellbook->getVcoin();

	int begintime =HeroData::getProp(Entity::attr_market_player_begin_time);
	int curtime = ActivityData::getWorldTime();

	CCString* times = CCString::createWithFormat(StringUtils::timeToString(curtime-begintime,TimeType::dh).c_str());
	CCString* title = CCString::createWithFormat(SystemData::getLayoutString("sellbook_title_label").c_str(),times->getCString(),gold,vcoin);

	CCLabelTTF* titleLabel = CCLabelTTF::create(title->getCString(),"",13);
	titleLabel->setAnchorPoint(ccp(0,1.0f));
	titleLabel->setDimensions(CCSizeMake(m_nWidth-10,0));
	titleLabel->setPosition(SystemData::getLayoutPoint("sellbook_title_label_pos"));
	addChild(titleLabel);

	LeavewordBook* leavewordbook = LeavewordBook::create();
	addChild(leavewordbook);

}

void BoothSellBook::bottonCallBack( CCObject* pSender )
{
	this->removeFromParent();
}

//--------------------------------------------------------------------------------------------------------------------------------

SellBook::SellBook():
	m_pTableView(NULL),
	m_pBookdesc(NULL),
	d_value(0),
	m_gold(0),
	m_vcoin(0)
{

}

SellBook::~SellBook()
{

}

bool SellBook::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	d_value = initMostCnt();

	m_pTableView=CCTableViewEx::create(this,SystemData::getLayoutSize("boothsellbook_sell"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(SystemData::getLayoutPoint("boothsellbook.frame.bg1"));
	m_pTableView->reloadData();  
	addChild(m_pTableView);

	return true;
}

int SellBook::initMostCnt()
{
	int s[10] = {};
	sellMap = BoothData::getSellDataMap();
	std::map<int,sellData>::iterator it;
	int size = sellMap.size();
	int mostCnt = SystemData::getLayoutValue("booksell_cnt");
	if (size>mostCnt)
	{
		int i = 0;
		for (it=sellMap.begin();it!=sellMap.end();it++)
		{
			if (it->first < size-mostCnt+1)
			{
				s[i] = it->first;
				i++;
			}
		}
		for (int n=0;n<i;n++)
		{
			sellMap.erase(s[n]);
		}
		return size-mostCnt;
	}
	return 0;
}

cocos2d::CCSize SellBook::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return (SystemData::getLayoutSize("boothsellbook_cell"));//
}

unsigned int SellBook::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return sellMap.size();
}

cocos2d::extension::CCTableViewCell* SellBook::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		int size = sellMap.size();
		if (size)
		{
			sellData sd = BoothData::getSellData(idx+1+d_value);
			if(sd.sid)
			{
				int sid = sd.sid;
				int price = sd.price;
				int type = sd.type;
				std::string name = "";
				CCString* pStr = NULL;
				StaticData::getItemName(sid,name);
				name = SystemData::getLayoutString("sellnotify_label1")+name;
				CCLabelTTF* label1 = CCLabelTTF::create(name.c_str(),"",15);
				label1->setAnchorPoint(ccp(0,0.5f));
				label1->setPosition(ccp(3,11));

				pLayer->addChild(label1);
				pStr = CCString::create("");
				if (type == 2)
				{
					pStr=CCString::createWithFormat(SystemData::getLayoutString("sellnotify_label2").c_str(),price);
					m_gold += price;
				}
				if (type == 3)
				{
					pStr=CCString::createWithFormat(SystemData::getLayoutString("sellnotify_label3").c_str(),price);
					m_vcoin += price;
				}
				CCLabelTTF* label2 = CCLabelTTF::create(pStr->getCString(),"",15);
				label2->setAnchorPoint(ccp(0,0.5f));
				label2->setPosition(ccp(180,11));
				pLayer->addChild(label2);
			}
		}
	}
	return cell;
}

int SellBook::getGold()
{
	return m_gold/3;
}

int SellBook::getVcoin()
{
	return m_vcoin/3;
}

/*
void SellBook::setTimes( int time )
{
	this->m_times = time;
}

void SellBook::setGold( int gold )
{
	this->m_gold = gold;
}

void SellBook::setVcoin( int vcoin )
{
	this->m_vcoin = vcoin;
}*/


//---------------------------------------------------------------------------------------------------------------------------------


LeavewordBook::LeavewordBook():
	m_pTableView(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

LeavewordBook::~LeavewordBook()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool LeavewordBook::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	words = BoothData::getWords();

	m_pTableView=CCTableViewEx::create(this,SystemData::getLayoutSize("boothsellbook_leavewords"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(SystemData::getLayoutPoint("boothsellbook.frame.bg2"));
	m_pTableView->reloadData();  
	addChild(m_pTableView);

	return true;
}

cocos2d::CCSize LeavewordBook::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("boothsellbook_leavewords").width,SystemData::getLayoutValue("singal_leaveword_height"));
}

unsigned int LeavewordBook::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return words.size();
}

cocos2d::extension::CCTableViewCell* LeavewordBook::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
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

		int size = words.size();
		if (size)
		{
			MarketWords word = words[idx];
			time_t time = word.time;
			std::string name = word.name;
			std::string str = word.content;
			std::string time_str = StringUtils::getFormatTime(time);
			CCString* leavewords = CCString::createWithFormat(SystemData::getLayoutString("leavewords_text").c_str(),str.c_str(),name.c_str(),
				time_str.c_str());
			CCLabelTTF* lwLabel = CCLabelTTF::create(leavewords->getCString(),"",15);
			lwLabel->setDimensions(CCSizeMake(SystemData::getLayoutSize("boothsellbook_leavewords").width-10,0));
			lwLabel->setAnchorPoint(ccp(0,1.0f));
			lwLabel->setPosition(ccp(3,45));
			pLayer->addChild(lwLabel);
		}
	}
	return cell;
}

void LeavewordBook::onCPEvent( const std::string &eventName )
{
	//initCheckList();
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
//		words.clear();
		if (source == "MsgEntityMarketInfoNotify")
		{
			words = BoothData::getWords();
			if (m_pTableView)
			{
				m_pTableView->reloadData();
			}
		}
	}
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGetMarketWordsResponse")
		{
			words = BoothData::getWords();
			if (m_pTableView)
			{
				m_pTableView->reloadData();
			}
		}
	}
}

void LeavewordBook::onEnter()
{
	CCLayer::onEnter();
}
