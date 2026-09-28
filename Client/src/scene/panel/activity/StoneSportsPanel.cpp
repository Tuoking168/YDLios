#include "StoneSportsPanel.h"
#include "EntityDefinition.h"
#include "EffectDefinition.h"
#include "ActivityModule.h"
#include "WorldDefinition.h"
#include "ActivityDataHelper.h"
#include "ModuleData.h"
#include "MsgWorld.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/ActivityData.h"


#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"

#include "network/HandleMessage.h"

#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "utils/StringUtils.h"

#include "controls/CPItemComponents.h"
#include "controls/CPDelayRefresh.h"

#include "res/CPAnimationManager.h"


StoneSportsInfoPanel::StoneSportsInfoPanel()
	: m_updater(NULL)
{

}

StoneSportsInfoPanel::~StoneSportsInfoPanel()
{

}

bool StoneSportsInfoPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initSprite();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();

	return true;
}

void StoneSportsInfoPanel::initSprite()
{
	CCSprite* sprite1 = SystemData::getSpriteByPlist("stonesports.sprite.activityname");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1); 
}

void StoneSportsInfoPanel::MenuCallBack(CCObject* pSender)
{
	CCLog("______________%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		CPEventHelper::openPanel("StoneSportsPanel");
	}
}

void StoneSportsInfoPanel::initLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("stonesports.label.activitytime");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("stonesports.label.rewardinfo");
	label2->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label2);

	CCLabelTTF* label3 = SystemData::getLabelTTF("stonesports.label.rewardnotice");
	label3->setHorizontalAlignment(kCCTextAlignmentLeft);   
	addChild(label3);
}

void StoneSportsInfoPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("activity.button.frame",110,50);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",110,50);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(StoneSportsInfoPanel::MenuCallBack)); 
	if(button1)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("stonesports.button.lookdetail.label"); 
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		button1->setPosition(SystemData::getLayoutPoint("stonesports.button.lookdetail"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel);
	}
}

/////////StoneSportsPanel///////////////////////////////////////////////
StoneSportsPanel::StoneSportsPanel()
	: m_updater(NULL)
	,mLabelContainer(NULL)
	,mRefresher(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

StoneSportsPanel::~StoneSportsPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool StoneSportsPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}
	
	initFrame();
	initSprite();
	
	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initRewards();
	refreshLabel();

	dataRequest();
	
	return true;
}

void StoneSportsPanel::initFrame()
{
	CCSize bgSize = SystemData::getLayoutSize("stonesports.frame.bigbg");
	CCPoint bgPoint = SystemData::getLayoutPoint("stonesports.frame.bigbg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",bgSize.width,bgSize.height);
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(bgPoint);
	addChild(bg);

	for (int i=0;i<6;i++)
	{
		CCSize size = SystemData::getLayoutSize("stonesports.frame.bg"+StringUtils::toString(i));
		CCPoint point = SystemData::getLayoutPoint("stonesports.frame.bg"+StringUtils::toString(i));
		CCScale9Sprite *frame=SystemData::getScale9SpriteByPlist("guild.menuback",size.width,size.height);
		frame->setAnchorPoint(CCPointZero);  
		frame->setPosition(point); 
		addChild(frame);	
	}
}
void StoneSportsPanel::initSprite()
{
	CCSprite* sprite1 = SystemData::getSprite("stonesports.sprite.trapezoid");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1);
}

void StoneSportsPanel::initLabels()
{
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "stoneSportsTitle");
	addChild(titleLabel);
	 
	CCLabelTTF* myLabel = SystemData::getLabelTTF("stonesports.label.yourlevel");
	myLabel->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(myLabel);

	const std::string &myStr = myLabel->getString() + StringUtils::toString(HeroData::getProp(Entity::attr_stone_point));
	myLabel->setString(myStr.c_str());

	mLabelContainer = CCLayer::create();
	addChild(mLabelContainer);

	mRefresher = CPDelayRefresh::create(this, callfunc_selector(StoneSportsPanel::refreshLabel));
	addChild(mRefresher);
}

void StoneSportsPanel::initRewards()
{
	const int cnt = 5;
	int section[cnt] = {0,4,7,9,10};
	int row = 0;
	int sec = 0;
	const CCPoint &ptFirst = LayoutData::getPoint(CPModuleName::ACTIVITY, "openServerGiftFirstPt");
	const CCSize &offset = LayoutData::getSize(CPModuleName::ACTIVITY, "openServerGiftOffset");
	for (int i=0;i<11;i++,row++)
	{
		if (sec<5&&i==section[sec])
		{
			row=0;
			sec++;
			if (hasGet(cnt - sec))
			{
				CCSprite *getFlag = LayoutData::getSprite(CPModuleName::ACTIVITY, "openServerGiftHasGet");
				getFlag->setPositionY(ptFirst.y - offset.height * (sec - 1));
				m_pMainMenu->addChild(getFlag, 1);
			}
		}
		
		int sid = ActivityDataHelper::getItemStaticID(Gift_StoneSports,5-sec+1,row+1);
		int cnt = ActivityDataHelper::getItemCount(Gift_StoneSports,5-sec+1,row+1); 
		if (sid>0&&cnt>0)
		{ 
			const CCPoint &point = ccp(ptFirst.x - offset.width * row, ptFirst.y - offset.height * (sec - 1));
			CCSprite* board = SystemData::getSpriteByPlist("activity.sprite.item.frame");
			board->setPosition(point);
			m_pMainMenu->addChild(board);

			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(point);
			pItem->setTarget(this,menu_selector(StoneSportsPanel::itemCallBack));
			m_pMainMenu->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_pMainMenu->addChild(pSprite);
		} 
	}
}

void StoneSportsPanel::refreshLabel()
{
	mLabelContainer->removeAllChildren();

	const int staticLabelCnt = 3;
	const int dynamicLabelCnt = 5;
	int point = 0, total = 0, remain = 0;
	for (int i = 0; i < (staticLabelCnt + dynamicLabelCnt); i++)
	{
		if (i < staticLabelCnt)
		{
			CCLabelTTF *staticLabel =  SystemData::getLabelTTF("stonesports.label.label" + StringUtils::toString(i));
			staticLabel->setHorizontalAlignment(kCCTextAlignmentCenter); 
			mLabelContainer->addChild(staticLabel);
		}
		else
		{
			const int j = i - staticLabelCnt;
			StaticData::getStoneSportsGiftData(dynamicLabelCnt - j, point, total);
			CCLabelTTF *dynamicLabel1 = SystemData::getLabelTTF("stonesports.label.label" + StringUtils::toString(i));
			dynamicLabel1->setString(StringUtils::toString(point).c_str());
			dynamicLabel1->setHorizontalAlignment(kCCTextAlignmentCenter); 
			mLabelContainer->addChild(dynamicLabel1);

			remain = ActivityData::getWorldIntProp(WorldDefination::prop_ns_fight_stone_5 - j, 0);
			const std::string &str2 = StringUtils::toString(remain) + "/" + StringUtils::toString(total);
			CCLabelTTF *dynamicLabel2 = SystemData::getLabelTTF("mountsports.label.remain");
			dynamicLabel2->setString(str2.c_str());
			dynamicLabel2->setPosition(SystemData::getLayoutPoint("stonesports.label.remain" + StringUtils::toString(j)));
			dynamicLabel2->setHorizontalAlignment(kCCTextAlignmentCenter);
			mLabelContainer->addChild(dynamicLabel2);
		}
	}
}

void StoneSportsPanel::showTooltip(CCMenuItem* pImage)
{
	// show tips
	CCPoint tipsPos = pImage->convertToWorldSpace(ccp(pImage->getContentSize().width,pImage->getContentSize().height-125));
	if(tipsPos.x+245>SystemData::size_x) 
	{
		tipsPos.x -= 245+pImage->getContentSize().width;
	}
	UserItem* userItem = (UserItem*)pImage->getUserData();
	if (userItem->category==ItemCate_Equip)
	{
		tipsPos.y=0;
	}
	if (tipsPos.y>200)
	{
		tipsPos.y=200;
	}
	Game::getGameUI()->showTipsPanel(userItem,TAG_Tips,tipsPos);
}

void StoneSportsPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}

void StoneSportsPanel::dataRequest()
{
	for (int i = WorldDefination::prop_ns_fight_stone_1; i <= WorldDefination::prop_ns_fight_stone_5; i++)
	{
		MsgSyncWorldDataRequest *msg = new MsgSyncWorldDataRequest;
		msg->wid = i;
		msg->version = ActivityData::getWorldIntPropVersion(i);
		HandleMessage::sendMessage(msg);
	}
}

bool StoneSportsPanel::hasGet( int index )
{
	const int data = HeroData::getProp(Entity::attr_ns_fight_stone_gift);
	const int mark = 1 << (index + 1);
	const int result = data & mark;
	return (result != 0);
}

void StoneSportsPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageSyncWorldDataResponse")
		{
			const int wid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (WorldDefination::prop_ns_fight_stone_1 <= wid
				&& wid <= WorldDefination::prop_ns_fight_stone_5)
			{
				mRefresher->refresh();
			}
		}
	}
}
