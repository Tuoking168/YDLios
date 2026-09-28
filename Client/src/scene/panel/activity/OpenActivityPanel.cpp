#include "OpenActivityPanel.h"
#include "EntityDefinition.h"
#include "EffectDefinition.h"
#include "ActivityModule.h"
#include "WorldDefinition.h"
#include "MsgWorld.h"
#include "ActivityDataHelper.h"
#include "ModuleData.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "userdata/ActivityData.h"
#include "userdata/NPCFunctionData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"

#include "event/EventProtocol.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"

#include "network/HandleMessage.h"

#include "scene/panel/EffectSprite.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "controls/CPItemComponents.h"
#include "controls/CPRichText.h"
#include "controls/CPDelayRefresh.h"

#include "utils/StringUtils.h"

#include "res/CPAnimationManager.h"


//////////OpenActivityPanel////////////////////////////////////////////
OpenActivityPanel::OpenActivityPanel()
	: m_updater(NULL)
	, m_pSlideItems(NULL)
	, m_PageInfo(NULL)
	, mOpenDays(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

OpenActivityPanel::~OpenActivityPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool OpenActivityPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	mOpenDays = ActivityData::getWorldBeginDays();
	
	initFrame();
	initSprite();
	
	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	CCPoint beginPos = SystemData::getLayoutPoint("openactivity.frame.table");
	CCSize slideSize = SystemData::getLayoutSize("openactivity.frame.table");
	CCSize spanSize = SystemData::getLayoutSize("openactivity.frame.span");
	m_pSlideItems = SlideTable::create(beginPos.x,beginPos.y,slideSize.width,slideSize.height,1,5,spanSize.width,spanSize.height);
	m_pSlideItems->setPosition(beginPos);
	addChild(m_pSlideItems);
	m_pSlideItems->setPageFlagVisible(false);
	m_pSlideItems->setPageChangeTarget(this,menu_selector(OpenActivityPanel::pageChangeCallBack));

	initLabels();
	initButtons();
	initItemPages();
	dataRequest();

	return true;
}

void OpenActivityPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageSyncWorldDataStringResponse")
		{
			mDelayRefresh->refresh();
		}
	}
}

void OpenActivityPanel::initFrame()
{
	CCSize bgSize = SystemData::getLayoutSize("openactivity.frame.bigbg");
	CCPoint bgPoint = SystemData::getLayoutPoint("openactivity.frame.bigbg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",bgSize.width,bgSize.height);
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(bgPoint);
	addChild(bg);

	mDelayRefresh = CPDelayRefresh::create(this, callfunc_selector(OpenActivityPanel::refresh));
	addChild(mDelayRefresh);
}

void OpenActivityPanel::initSprite()
{
	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "openActivityTitle");
	addChild(title);

	CCSprite* sprite1 = SystemData::getSpriteByPlist("openactivity.sprite.shitianjianianhua");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1);
}

void OpenActivityPanel::MenuCallBack(CCObject* pSender)
{
	CCLog("______________%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag>=Cell_Start&&tag<=Cell_End)
		{
			tag-=Cell_Start;
			ActivityDetailPanel* panel = ActivityDetailPanel::create(tag);
			addChild(panel);
		}
	}
}

void OpenActivityPanel::initLabels()
{
	m_PageInfo = SystemData::getLabelTTF("openactivity.label.page");
	m_PageInfo->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(m_PageInfo);
}

void OpenActivityPanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("openactivity.button.up");
	button1->setTarget(this,menu_selector(OpenActivityPanel::MenuCallBack));
	button1->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button1);
	CCSprite* sprite1 = SystemData::getSpriteByPlist("openactivity.button.up");
	sprite1->setFlipX(true);
	sprite1->setPosition(CCPointZero);
	sprite1->setAnchorPoint(CCPointZero);
	CCSprite* sprite2 = SystemData::getSpriteByPlist("openactivity.button.up.sel");
	sprite2->setFlipX(true);
	sprite2->setPosition(CCPointZero);
	sprite2->setAnchorPoint(CCPointZero);
	button1->setNormalImage(sprite1);
	button1->setSelectedImage(sprite2);
	button1->setEnabled(false);

	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("openactivity.button.down");
	button2->setTarget(this,menu_selector(OpenActivityPanel::MenuCallBack));
	button2->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button2);
	button2->setEnabled(false);
}

void OpenActivityPanel::refresh()
{
	const int UNIT = 3;
	const int itemNum = ActivityDataHelper::getOpenActivitySize();
	const std::string &zhanShi = SystemData::getLayoutString("openactivity.cell.label.zhanshi");
	const std::string &faShi = SystemData::getLayoutString("openactivity.cell.label.fashi");
	const std::string &doShi = SystemData::getLayoutString("openactivity.cell.label.daoshi");
	for (int i = 0; i < (int)mLabels.size(); i += UNIT)
	{
		const int k = i/UNIT;
		if (0 < k && k < (itemNum - 1))
		{
			const int j = i + 1;
			if (j < (int)mLabels.size())
			{
				CCLabelTTF *label = dynamic_cast<CCLabelTTF *>(mLabels[j]);
				if (label)
				{
					const int propID = WorldDefination::prop_world_wings_max + k - 1;
					const std::string &playerName = ActivityData::getWorldStringProp(propID, 0);
					if ((k + 1) < mOpenDays
						&& playerName.empty())
					{
						label->setString(SystemData::getLayoutString("openactivity.cell.label.rewardnobody").c_str());
					}
					else
					{
						label->setString(playerName.c_str());
					}
				}
			}
		}
		else
		{
			int propID = WorldDefination::prop_world_first_cbt_zs_max;
			if (k == 0)
			{
				propID = WorldDefination::prop_world_first_zs_lvl;
			}
			CCLabelTTF *label = dynamic_cast<CCLabelTTF *>(mLabels[i]);
			if (label)
			{
				label->setString((zhanShi + ActivityData::getWorldStringProp(propID, 0)).c_str());
			}

			int j = i + 1;
			if (j < (int)mLabels.size())
			{
				label = dynamic_cast<CCLabelTTF *>(mLabels[j]);
				if (label)
				{
					label->setString((faShi + ActivityData::getWorldStringProp(propID + 1, 0)).c_str());
				}
			}

			j = i + 2;
			if (j < (int)mLabels.size())
			{
				label = dynamic_cast<CCLabelTTF *>(mLabels[j]);
				if (label)
				{
					label->setString((doShi + ActivityData::getWorldStringProp(propID + 2, 0)).c_str());
				}
			}
		}
	}
}

void OpenActivityPanel::showTooltip(CCMenuItem* pImage)
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

void OpenActivityPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}
void OpenActivityPanel::addListItem(int i )
{
	CCNode* pItem = CCNode::create();
	m_pSlideItems->addElement(pItem);

	for (int j=0;j<2;j++)
	{
		CCSize bgSize = SystemData::getLayoutSize("openactivity.cell.frame"+StringUtils::toString(j));
		CCPoint bgPoint = SystemData::getLayoutPoint("openactivity.cell.frame"+StringUtils::toString(j));
		CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",bgSize.width,bgSize.height);
		bg->setAnchorPoint(CCPointZero);
		bg->setPosition(bgPoint);
		pItem->addChild(bg);  
	}
	CCLabelTTF* label1 = SystemData::getLabelTTF("openactivity.cell.label.activityname");
	label1->setHorizontalAlignment(kCCTextAlignmentCenter); 
	pItem->addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("openactivity.cell.label.listtitle");
	label2->setHorizontalAlignment(kCCTextAlignmentCenter); 
	pItem->addChild(label2);

	const int FIRST_ACTIVITY_SETTLEMENT_DATE = 5;
	if ((i == 0 && mOpenDays > FIRST_ACTIVITY_SETTLEMENT_DATE)
		|| (0 < i && (i + 1) < mOpenDays))
	{
		label2->setString(SystemData::getLayoutString("openactivity.cell.label.listtitlereward").c_str());
	}
	
	//
	CCLabelTTF* label3 = SystemData::getLabelTTF("openactivity.cell.label.zhanshi");
	label3->setHorizontalAlignment(kCCTextAlignmentCenter); 
	pItem->addChild(label3);
	mLabels.push_back(label3);

	CCLabelTTF* label4 = SystemData::getLabelTTF("openactivity.cell.label.fashi");
	label4->setHorizontalAlignment(kCCTextAlignmentCenter); 
	pItem->addChild(label4);
	mLabels.push_back(label4);

	CCLabelTTF* label5 = SystemData::getLabelTTF("openactivity.cell.label.daoshi");
	label5->setHorizontalAlignment(kCCTextAlignmentCenter); 
	pItem->addChild(label5);
	mLabels.push_back(label5);
	const int itemNum = ActivityDataHelper::getOpenActivitySize();
	if (0 < i && i < (itemNum - 1))
	{
		label3->setVisible(false);
		label4->setString("");
		label4->setColor(ccYELLOW);
		label4->setAnchorPoint(label2->getAnchorPoint());
		label4->setPositionX(label2->getPositionX());
		label5->setVisible(false);
	}

	//
	CCLabelTTF* label6 = SystemData::getLabelTTF("openactivity.cell.label.reward");
	label6->setHorizontalAlignment(kCCTextAlignmentCenter); 
	pItem->addChild(label6);
	CCLabelTTF* label7 = SystemData::getLabelTTF("openactivity.cell.label.condition");
	label7->setHorizontalAlignment(kCCTextAlignmentCenter); 
	pItem->addChild(label7); 
	label1->setString(ActivityDataHelper::getOpenActivityTitle(i+1).c_str());
	label7->setFontName("Arial");
	label7->setString(ActivityDataHelper::getOpenActivityRewardInfo(i+1).c_str());

	CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
	CCPoint point = SystemData::getLayoutPoint("openactivity.cell.sprite.reward");
	sprite->setAnchorPoint(CCPointZero);
	sprite->setPosition(point); 
	pItem->addChild(sprite); 

	CCSprite* specialSprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
	CCPoint specialPoint = SystemData::getLayoutPoint("openactivity.cell.sprite.specialreward");
	specialSprite->setAnchorPoint(CCPointZero);
	specialSprite->setPosition(specialPoint); 
	pItem->addChild(specialSprite); 

	CCMenu* m_pMenu = GeneralMenu::create();
	m_pMenu->setPosition(CCPointZero);
	m_pMenu->setAnchorPoint(CCPointZero); 
	pItem->addChild(m_pMenu);
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.placard.button",80,35);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",80,35);
	CCMenuItemSprite *button =CCMenuItemSprite::create(p1, pSel1, NULL, this, menu_selector(OpenActivityPanel::MenuCallBack));
	if(button)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("openactivity.cell.button.detail.label"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button->setTag(Cell_Start+i);      
		button->setPosition(SystemData::getLayoutPoint("openactivity.cell.button.detail"));
		pLabel->setPosition(button->getPosition()); 
		m_pMenu->addChild(button); 
		m_pMenu->addChild(pLabel);
	}

	const int itemID = ActivityDataHelper::getOpenActivityNormalReward(i+1);
	if (itemID > 0)
	{
		UserItem* item = CommonFunction::createNewItem(itemID);
		CCMenuItemImage* pItem=CommonFunction::getItemIcon(item);
		pItem->setPosition(ccp(point.x+33, point.y+33));
		pItem->setTarget(this,menu_selector(OpenActivityPanel::itemCallBack));
		m_pMenu->addChild(pItem); 

		CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
		pSprite->setPosition(pItem->getPosition());
		m_pMenu->addChild(pSprite);
	}

	int SpecialRewardSid = ActivityDataHelper::getOpenActivitySpecialReward(i+1);
	int SpecialRewardCount = ActivityDataHelper::getOpenActivitySpecialRewardCount(i+1);
	if (SpecialRewardSid>0&&SpecialRewardCount>0)
	{ 
		UserItem* item = CommonFunction::createNewItem(SpecialRewardSid);
		item->count = SpecialRewardCount;
		CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
		pItem->setPosition(ccp(specialPoint.x+33,specialPoint.y+33));
		pItem->setTarget(this,menu_selector(OpenActivityPanel::itemCallBack));
		m_pMenu->addChild(pItem); 

		CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
		pSprite->setPosition(pItem->getPosition());
		m_pMenu->addChild(pSprite);
	} 
}

void OpenActivityPanel::addListFinish()
{
	refresh();
}

void OpenActivityPanel::initItemPages()
{
	m_pSlideItems->clear();
	if (m_updater)
	{
		m_updater->removeFromParentAndCleanup(true);
		m_updater = NULL;
	}

	mLabels.clear();
	const int itemNum = ActivityDataHelper::getOpenActivitySize();
	m_updater = CPUpdater::create(this, cpupdater_selector(OpenActivityPanel::addListItem));
	m_updater->setUpdateTimes(itemNum);
	m_updater->setFinishHandler(this, callfunc_selector(OpenActivityPanel::addListFinish));
	addChild(m_updater);
	m_updater->start();
}

void OpenActivityPanel::pageChangeCallBack(CCObject* pSender)
{
	if (!m_pSlideItems||!m_PageInfo)
		return;
	int curPage = m_pSlideItems->getCurPage()+1;
	int totalPage = m_pSlideItems->getTotalPage();
	std::string pageStr = StringUtils::toString(curPage)+"/"+StringUtils::toString(totalPage);
	m_PageInfo->setString(pageStr.c_str());
}

void OpenActivityPanel::dataRequest()
{
	for (int i = WorldDefination::prop_world_first_zs_lvl; i <= WorldDefination::prop_world_first_cbt_ds_max; i++)
	{
		MsgSyncWorldDataStringRequest *msg = new MsgSyncWorldDataStringRequest;
		msg->wid = i;
		msg->version = ActivityData::getWorldStringPropVersion(i);
		HandleMessage::sendMessage(msg);
	}
}

///////////////ActivityDetailPanel///////////////////////////////////////////
ActivityDetailPanel::ActivityDetailPanel()
	:m_pMainMenu(NULL)
	,m_selIndex(-1)
	,m_pRichText(NULL)
{

}

ActivityDetailPanel::~ActivityDetailPanel()
{

}

ActivityDetailPanel* ActivityDetailPanel::create(int tag)
{
	ActivityDetailPanel* pPanel = new ActivityDetailPanel();
	if(pPanel && pPanel->init(tag))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("GuildPanel create failed!");
	}
	return NULL;
}

bool ActivityDetailPanel::init( int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_selIndex = tag;

	m_nHeight = SystemData::size_y+1000;
	m_nWidth = SystemData::size_x+1000;

	addCover(ccp(-1000,-1000));

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();

	return true;
}

void ActivityDetailPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		closeSelf();		
	}
}

void ActivityDetailPanel::closeSelf()
{
	this->removeFromParentAndCleanup(true);
}

void ActivityDetailPanel::initFrame()
{
	CCSprite* frame = SystemData::getSpriteByPlist("openactivity.alert.frame.background");
	frame->setAnchorPoint(ccp(0.5,0.5));  
	addChild(frame);

	CCSize bgSize = SystemData::getLayoutSize("openactivity.alert.frame.scalebg");
	CCPoint bgPoint = SystemData::getLayoutPoint("openactivity.alert.frame.scalebg");
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize.width,bgSize.height);
	bg->setAnchorPoint(ccp(0.5,0.5));
	bg->setPosition(bgPoint); 
	addChild(bg);
}

void ActivityDetailPanel::initLabels()
{
	CCSize size = SystemData::getLayoutSize("openactivity.alert.label.content"); 


	CPItemComponents *descList = CPItemComponents::create(size, new CPLayoutList());
	descList->setAnchorPoint(ccp(0.5,0.5));
	descList->setTouchEnabled(true);
	descList->setPosition(SystemData::getLayoutPoint("openactivity.alert.label.content")); 
	addChild(descList);

	CPRichText* pText=NPCFunctionData::getBigContent(ActivityDataHelper::getOpenActivityInfo(m_selIndex+1),size.width,0); 
	m_pRichText = CPRichText::create(size.width,pText->getContentSize().height);

	int contentsize=0;
	int idx = ActivityDataHelper::getOpenActivityInfo(m_selIndex+1);
	LuaData::getProp_size("gdBigContent",idx,"text",contentsize);
	CPUpdater* ptime=CPUpdater::create(this,cpupdater_selector(ActivityDetailPanel::addSubContent));
	ptime->setUpdateTimes(contentsize);
	addChild(ptime);
	ptime->start();

	CCLabelTTF* label1 = SystemData::getLabelTTF("openactivity.alert.label.page");
	label1->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(label1);
	label1->setString(ActivityDataHelper::getOpenActivityTitle(m_selIndex+1).c_str());


	descList->addItem(m_pRichText);
}
 
void ActivityDetailPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,45); 
	CCMenuItemSprite *button =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(ActivityDetailPanel::MenuCallBack));
	if(button)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("openactivity.alert.button.ok.label"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button->setPosition(SystemData::getLayoutPoint("openactivity.alert.button.ok"));
		pLabel->setPosition(button->getPosition()); 
		m_pMainMenu->addChild(button); 
		m_pMainMenu->addChild(pLabel);
	}

	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("openactivity.alert.button.close");
	button2->setTarget(this,menu_selector(ActivityDetailPanel::MenuCallBack));
	button2->setAnchorPoint(ccp(1,1));
	m_pMainMenu->addChild(button2);
}

void ActivityDetailPanel::addSubContent( int id )
{
	int i=id+1;
	std::string oldstr;
	std::string colorstr;
	LuaData::getProp("gdBigContent",ActivityDataHelper::getOpenActivityInfo(m_selIndex+1),"text",i,"color",colorstr);
	LuaData::getProp("gdBigContent",ActivityDataHelper::getOpenActivityInfo(m_selIndex+1),"text",i,"content",oldstr);
	ccColor3B color=ccWHITE;
	if (colorstr=="g")
	{
		color=ccGREEN;
	}
	else if (colorstr=="b")
	{
		color=ccBLUE;
	}
	else if (colorstr=="y")
	{
		color=ccYELLOW;
	}
	else if (colorstr=="o")
	{
		color=ccORANGE;
	}
	else if (colorstr=="w")
	{
		color=ccWHITE;
	}
	CPRichTextItemLabel* pText=new CPRichTextItemLabel(oldstr,"",18,color);
	if (m_pRichText)
	{
		m_pRichText->addItem(pText);
	}
}
