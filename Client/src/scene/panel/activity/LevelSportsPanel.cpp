#include "LevelSportsPanel.h"
#include "EntityDefinition.h"
#include "EffectDefinition.h"
#include "ActivityDataHelper.h"
#include "ModuleData.h"
#include "ActivityModule.h"
#include "WorldDefinition.h"
#include "MsgWorld.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/LayoutData.h"
#include "userdata/ActivityData.h"

#include "userdata/luadata/LuaData.h"

#include "userdata/netdata/GameRole.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"

#include "network/HandleMessage.h"

#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "utils/StringUtils.h"

#include "res/CPAnimationManager.h"

#include "controls/CPItemComponents.h"
#include "controls/CPDelayRefresh.h"


LevelSportsInfoPanel::LevelSportsInfoPanel()
	: m_updater(NULL)
{
	
}

LevelSportsInfoPanel::~LevelSportsInfoPanel()
{
	
}

bool LevelSportsInfoPanel::init()
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

void LevelSportsInfoPanel::initSprite()
{
	CCSprite* sprite1 = SystemData::getSpriteByPlist("levelsports.sprite.activityname");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1); 
}

void LevelSportsInfoPanel::MenuCallBack(CCObject* pSender)
{
	CCLog("______________%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		CPEventHelper::openPanel("LevelSportsPanel");
	}
}

void LevelSportsInfoPanel::initLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("levelsports.label.activitytime");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("levelsports.label.rewardinfo");
	label2->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label2);

	CCLabelTTF* label3 = SystemData::getLabelTTF("levelsports.label.rewardnotice");
	label3->setHorizontalAlignment(kCCTextAlignmentLeft);   
	addChild(label3);
}

void LevelSportsInfoPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("activity.button.frame",110,50);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",110,50);
	CCMenuItemSprite *button1 =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(LevelSportsInfoPanel::MenuCallBack));
	if(button1)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("levelsports.button.lookdetail.label"); 
		pLabel->setFontSize(20);
		pLabel->setColor(ccWHITE);
		button1->setPosition(SystemData::getLayoutPoint("levelsports.button.lookdetail"));
		pLabel->setPosition(button1->getPosition());
		m_pMainMenu->addChild(button1);
		m_pMainMenu->addChild(pLabel);
	}
}


/////////LevelSportsPanel////////////////////////////////////////////////
LevelSportsPanel::LevelSportsPanel()
	: m_updater(NULL)
	,mLabelContainer(NULL)
	,mRefresher(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

LevelSportsPanel::~LevelSportsPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool LevelSportsPanel::init()
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

void LevelSportsPanel::initFrame()
{
	CCSize bgSize = SystemData::getLayoutSize("levelsports.frame.bigbg");
	CCPoint bgPoint = SystemData::getLayoutPoint("levelsports.frame.bigbg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",bgSize.width,bgSize.height);
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(bgPoint);
	addChild(bg);

	for (int i=0;i<6;i++)
	{
		CCSize size = SystemData::getLayoutSize("levelsports.frame.bg"+StringUtils::toString(i));
		CCPoint point = SystemData::getLayoutPoint("levelsports.frame.bg"+StringUtils::toString(i));
		CCScale9Sprite *frame=SystemData::getScale9SpriteByPlist("guild.menuback",size.width,size.height);
		frame->setAnchorPoint(CCPointZero);  
		frame->setPosition(point); 
		addChild(frame);	
	}
}
void LevelSportsPanel::initSprite()
{
	CCSprite* sprite1 = SystemData::getSprite("levelsports.sprite.trapezoid");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1);
}

void LevelSportsPanel::initLabels()
{
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::ACTIVITY, "levelSportsTitle");
	addChild(titleLabel);

	CCLabelTTF *myLabel = SystemData::getLabelTTF("levelsports.label.yourlevel");
	myLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
	addChild(myLabel);

	const std::string &myStr = myLabel->getString() + HeroData::getLevelString();
	myLabel->setString(myStr.c_str());

	mLabelContainer = CCLayer::create();
	addChild(mLabelContainer);

	mRefresher = CPDelayRefresh::create(this, callfunc_selector(LevelSportsPanel::refreshLabel));
	addChild(mRefresher);
}

void LevelSportsPanel::initRewards()
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

		int sid = ActivityDataHelper::getItemStaticID(Gift_LevelSports,5-sec+1,row+1);
		int cnt = ActivityDataHelper::getItemCount(Gift_LevelSports,5-sec+1,row+1); 
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
			pItem->setTarget(this,menu_selector(LevelSportsPanel::itemCallBack));
			m_pMainMenu->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_pMainMenu->addChild(pSprite);
		} 
	}
}

void LevelSportsPanel::refreshLabel()
{
	mLabelContainer->removeAllChildren();

	const int staticLabelCnt = 3;
	const int dynamicLabelCnt = 5;
	int level = 0, total = 0, remain = 0, reborn = 0;
	for (int i = 0; i < (staticLabelCnt + dynamicLabelCnt); i++)
	{
		if (i < staticLabelCnt)
		{
			CCLabelTTF *staticLabel = SystemData::getLabelTTF("levelsports.label.label" + StringUtils::toString(i));
			staticLabel->setHorizontalAlignment(kCCTextAlignmentCenter); 
			mLabelContainer->addChild(staticLabel);
		}
		else
		{
			const int j = i - staticLabelCnt;
			StaticData::getLevelSportsGiftData(dynamicLabelCnt - j, level, total, reborn);
			CCLabelTTF *dynamicLabel1 = SystemData::getLabelTTF("levelsports.label.label" + StringUtils::toString(i));
			dynamicLabel1->setString(StringUtils::levelToString(reborn, level).c_str());
			dynamicLabel1->setHorizontalAlignment(kCCTextAlignmentCenter); 
			mLabelContainer->addChild(dynamicLabel1);

			remain = ActivityData::getWorldIntProp(WorldDefination::prop_ns_fight_lvl_5 - j, 0);
			const std::string &str2 = StringUtils::toString(remain) + "/" + StringUtils::toString(total);
			CCLabelTTF *dynamicLabel2 = SystemData::getLabelTTF("levelsports.label.remain");
			dynamicLabel2->setString(str2.c_str());
			dynamicLabel2->setPosition(SystemData::getLayoutPoint("levelsports.label.remain" + StringUtils::toString(j)));
			dynamicLabel2->setHorizontalAlignment(kCCTextAlignmentCenter);     
			mLabelContainer->addChild(dynamicLabel2);
		}
	}
}

void LevelSportsPanel::showTooltip(CCMenuItem* pImage)
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

void LevelSportsPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}

void LevelSportsPanel::dataRequest()
{
	for (int i = WorldDefination::prop_ns_fight_lvl_1; i <= WorldDefination::prop_ns_fight_lvl_5; i++)
	{
		MsgSyncWorldDataRequest *msg = new MsgSyncWorldDataRequest;
		msg->wid = i;
		msg->version = ActivityData::getWorldIntPropVersion(i);
		HandleMessage::sendMessage(msg);
	}
}

bool LevelSportsPanel::hasGet( int index )
{
	const int data = HeroData::getProp(Entity::attr_ns_fight_lvl_gift);
	const int mark = 1 << (index + 1);
	const int result = data & mark;
	return (result != 0);
}

void LevelSportsPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageSyncWorldDataResponse")
		{
			const int wid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (WorldDefination::prop_ns_fight_lvl_1 <= wid
				&& wid <= WorldDefination::prop_ns_fight_lvl_5)
			{
				mRefresher->refresh();
			}
		}
	}
}