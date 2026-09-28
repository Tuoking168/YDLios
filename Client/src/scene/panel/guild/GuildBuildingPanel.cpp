#include "GuildBuildingPanel.h"
#include "GuildModule.h"
#include "EntityDefinition.h"
#include "GuildDefinition.h"
#include "EvtDataDefinition.h"
#include "MsgGuild.h"

#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/FloatPanel.h"

#include "controls/CPItemComponents.h"
#include "controls/CPChecker.h"
#include "controls/CPScrollbar.h"

#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"
#include "userdata/GuildData.h"

#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "logic/ItemOperator.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"

#include "network/HandleMessage.h"

#include "scene/panel/FloatPanel.h"
#include <vector>
#include <stdlib.h>

namespace GuildBuilding
{
	enum
	{
		begin = 0,
		gong_dian = 0,
		guan_gong = 1,
		fu_li = 2,
		mao_xian = 3,
		shen_shou = 4,
		shang_dian = 5,
		guang_huan = 6,

		max,
	};
}

/////////GuildBuildingPanel////////////////////////////////////////////
GuildBuildingPanel::GuildBuildingPanel()
	:mStateLayer(NULL)
	,mContainerLayer(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::UI_OPEN, this);
}

GuildBuildingPanel::~GuildBuildingPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::UI_OPEN, this);
}

bool GuildBuildingPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	initUI();
	refresh();
	
	return true;
}

void GuildBuildingPanel::initUI()
{
	// title
	CCSprite *title = LayoutData::getSprite(CPModuleName::GUILD, "buildingTitle");
	addChild(title);

	// board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, "buildingBoard");
	addChild(board);

	CCScale9Sprite *topSubBoard = LayoutData::getScale9Sprite(CPModuleName::GUILD, "buildingTopSubBoard");
	addChild(topSubBoard);

	CCScale9Sprite *bottomSubBoard = LayoutData::getScale9Sprite(CPModuleName::GUILD, "buildingBottomSubBoard");
	addChild(bottomSubBoard);

	// img
	CCSprite *img = LayoutData::getSpriteByFile(CPModuleName::GUILD, "buildingImg");
	addChild(img);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);
	int openLevel = 0;
	const int gongDianLevel = GuildData::getGuildProp(GuildType::guild_building_gong_dian_level);
	for (int i = GuildBuilding::begin; i < GuildBuilding::max; i++)
	{
		const std::string &key = "building" + StringUtils::toString(i);
		CCMenuItemImage *btn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, key);
		btn->setTarget(this, menu_selector(GuildBuildingPanel::onBuilding));
		menu->addChild(btn, 0, i);

		openLevel = 0;
		StaticData::getGuildBuildingOpenLevel(i + GuildType::guild_building_gong_dian_level, openLevel);
		if (gongDianLevel < openLevel)
		{
			btn->setVisible(false);
		}
	}

	// state layer
	mStateLayer = CCLayer::create();
	addChild(mStateLayer);

	// note label
	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "buildingNote");
	addChild(noteLabel);

	// container layer
	mContainerLayer = CCLayer::create();
	addChild(mContainerLayer, 1);
}

void GuildBuildingPanel::refresh()
{
	mStateLayer->removeAllChildren();

	CCLabelTTF *guildMoney = LayoutData::getLabelTTF(CPModuleName::GUILD, "buildingMoney");
	addChild(guildMoney);

	const int cnt = GuildData::getGuildProp(GuildType::guild_money);
	const std::string &str = guildMoney->getString() + StringUtils::toString(cnt);
	guildMoney->setString(str.c_str());
}

void GuildBuildingPanel::onBuilding( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		openBuilding(node->getTag());
	}
}

void GuildBuildingPanel::openBuilding( int buildingID )
{
	CCNode *subPanel = mContainerLayer->getChildByTag(buildingID);
	if (subPanel)
	{
		subPanel->removeFromParent();
		subPanel = NULL;
	}

	switch (buildingID)
	{
	case GuildBuilding::gong_dian:
		subPanel = GuildBuildingGongDian::create();		
		break;
	case GuildBuilding::guan_gong:
		subPanel = GuildBuildingGuanGong::create();			
		break;
	case GuildBuilding::fu_li:
		subPanel = GuildBuildingFuli::create();		
		break;
	case GuildBuilding::mao_xian:
		subPanel = GuildBuildingTanXian::create();
		break;
	case GuildBuilding::shen_shou:
		//subPanel = GuildBuildingShenShou::create();
		break;
	case GuildBuilding::shang_dian:
		subPanel = GuildBuildingShangDian::create();		
		break;
	case GuildBuilding::guang_huan:
		subPanel=GuildBuildingGuangHuan::create();
		break;
	}

	if (subPanel)
	{
		mContainerLayer->addChild(subPanel, 0, buildingID);
	}
}

void GuildBuildingPanel::onCPEvent(const std::string &eventName)
{
	if (eventName == CPEventName::UI_OPEN)
	{
		const std::string &target = CPEventHelper::getEventTarget();
		if (target == "GuildBuildingPanel")
		{
			const int buildingID = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			openBuilding(buildingID);
		}
	}
}

/////////GuildBuildingGuangHuan//////////////////////////////////////////
GuildBuildingGuangHuan::GuildBuildingGuangHuan()
	:mChecker(NULL)
    ,mBuildings(NULL)
	,mUpgradeBtn(NULL)
	,mOpenBtn(NULL)	
	,mCDLabel(NULL)	
	,mCurrentPage(0)
	,mSelectBuffID(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

GuildBuildingGuangHuan::~GuildBuildingGuangHuan()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool GuildBuildingGuangHuan::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}
	mCurrentPage = getFirstPage();

	initUI();
	refereshList();
	refreshButtons();	
	refreshGuildMoney();

	return true;
}

void GuildBuildingGuangHuan::initUI()
{
	CCLabelTTF *titleLabel=LayoutData::getLabelTTF(CPModuleName::GUILD,"bdGuangHuanTitle");
	addChild(titleLabel);

	const int boardCnt = LayoutData::getInt(CPModuleName::GUILD, "bdGuangHuanBoardCnt");
	for (int i = 0; i < boardCnt; i++)
	{
		const std::string &key = "bdGuangHuanBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, key);
		addChild(board);
	}

	// list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUILD, "bdGuangHuanList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::GUILD, "bdGuangHuanItem");
	const int perLine = LayoutData::getInt(CPModuleName::GUILD, "bdGuangHuanPerLine");
	mItemList = CPItemComponents::create(listSize, new CPLayoutGrid(perLine, itemSize, true));
	mItemList->setClickSensitive(true);
	mItemList->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdGuangHuanList"));
	addChild(mItemList);

	// page label
	mPageLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuangHuanPage");
	addChild(mPageLabel);	

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	mFirstPageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuangHuanFirstPage");
	mFirstPageBtn->setTarget(this, menu_selector(GuildBuildingGuangHuan::onFirstPage));
	menu->addChild(mFirstPageBtn);

	mLastPageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuangHuanLastPage");
	mLastPageBtn->setTarget(this, menu_selector(GuildBuildingGuangHuan::onLastPage));
	menu->addChild(mLastPageBtn);

	mPrePageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuangHuanPrePage");
	mPrePageBtn->setTarget(this, menu_selector(GuildBuildingGuangHuan::onPrePage));
	menu->addChild(mPrePageBtn);

	mNextPageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuangHuanNextPage");
	mNextPageBtn->setTarget(this, menu_selector(GuildBuildingGuangHuan::onNextPage));
	menu->addChild(mNextPageBtn);

	// state layer
	mStateLayer = CCLayer::create();
 	addChild(mStateLayer);	

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void GuildBuildingGuangHuan::refereshList()
{
	mItemList->removeAllItems();

	const int perPage = LayoutData::getInt(CPModuleName::GUILD, "bdGuangHuanPerPage");
	for (int i = 0; i < perPage; i++)
	{
		CCNode *item = getListItem(i + perPage * (mCurrentPage - 1));		
		mItemList->addItem(item);		
	}

	// page label
	const std::string &pageStr = StringUtils::toString(mCurrentPage) + "/" + StringUtils::toString(getLastPage());
	mPageLabel->setString(pageStr.c_str());
}

void GuildBuildingGuangHuan::refreshGuildMoney()
{
	mStateLayer->removeAllChildren();

	CCLabelTTF *guildMoney = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdGuanHuanGuildMoney");
	guildMoney->setString((guildMoney->getString() + StringUtils::toString(GuildData::getGuildProp(GuildType::guild_money))).c_str());
	mStateLayer->addChild(guildMoney);
}

void GuildBuildingGuangHuan::refreshButtons()
{
	mFirstPageBtn->setEnabled(true);
	mLastPageBtn->setEnabled(true);
	mPrePageBtn->setEnabled(true);
	mNextPageBtn->setEnabled(true);
	if (mCurrentPage == getFirstPage())
	{
		mFirstPageBtn->setEnabled(false);
		mPrePageBtn->setEnabled(false);

		if (mCurrentPage == getLastPage())
		{
			mLastPageBtn->setEnabled(false);
			mNextPageBtn->setEnabled(false);
		}
	}
	else if (mCurrentPage == getLastPage())
	{
		mLastPageBtn->setEnabled(false);
		mNextPageBtn->setEnabled(false);
	}	
}

void GuildBuildingGuangHuan::onFirstPage( CCObject *target )
{
	mCurrentPage = getFirstPage();
	refereshList();
	refreshButtons();
}

void GuildBuildingGuangHuan::onLastPage( CCObject *target )
{
	mCurrentPage = getLastPage();
	refereshList();
	refreshButtons();
}

void GuildBuildingGuangHuan::onPrePage( CCObject *target )
{
	mCurrentPage--;
	const int firstPage = getFirstPage();
	if (mCurrentPage < firstPage)
	{
		mCurrentPage = firstPage;
	}
	refereshList();
	refreshButtons();
}

void GuildBuildingGuangHuan::onNextPage( CCObject *target )
{
	mCurrentPage++;
	const int lastPage = getLastPage();
	if (mCurrentPage > lastPage)
	{
		mCurrentPage = lastPage;
	}
	refereshList();
	refreshButtons();
}

void GuildBuildingGuangHuan::onOpen(CCObject *target)
{	
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{		
	  const int index = node->getTag();
	  mSelectBuffID = index;
	  if (index > 0)
	  {
		  int money = 0;
		  string openName = "";
		  int time = 0;
		  StaticData::getGuildBuildingGuangHuan(index ,time,money,openName);
		  StrVector vect;	
		  vect.push_back(StringUtils::toString(money));
		  vect.push_back(openName);		  
		  vect.push_back(StringUtils::toString(time));		 
		  FloatPanel *panel = FloatPanel::show(FloatPanelType::Guild_GuangHuan_open,vect,this,floatpanel_selector(GuildBuildingGuangHuan::onOpen));		  
		  if (panel)
		  {
			  panel->setAlignment(kCCTextAlignmentLeft);

			  CCLabelTTF *label =LayoutData::getLabelTTF(CPModuleName::GUILD,"bdGuangHuanFloatPanelLabel");
		      panel->addChild(label);
		  }		  
	  }	  
	}
}

void GuildBuildingGuangHuan::onOpen(int btnType)
{
	if (btnType==Button_QD)
	{
		mChecker->start();
		MsgGuildOpenBuffRequest *req = new MsgGuildOpenBuffRequest;
		req->buffID = mSelectBuffID;
		HandleMessage::sendMessage(req);
	}
}

CCNode* GuildBuildingGuangHuan::getListItem( int index )
{
	CCNode *ret = CCNode::create();
	ret->setContentSize(LayoutData::getSize(CPModuleName::GUILD, "bdGuangHuanItemImage"));	

	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, "bdGuangHuanItem");
	board->setAnchorPoint(ccp(0, 1));
	board->setPosition(ccp(0, ret->getContentSize().height));	
	ret->addChild(board);

	string hurt = "";
	int time = 0;
	int money = 0;
	string name = "";
	StaticData::getGuildBuildingGuangHuan(index + 1,hurt,time,money,name);
	

	CCLabelTTF* labelHurt=LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuangHuanLabelHurt");
	labelHurt->setString((hurt).c_str());
	ret->addChild(labelHurt);
	CCLabelTTF* labelTime=LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuangHuanLabelTime");
	labelTime->setString((labelTime->getString() + StringUtils::toString(time) + LayoutData::getString(CPModuleName::GUILD,"strText")).c_str());
	ret->addChild(labelTime);
	CCLabelTTF* labelMoney=LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuangHuanLabelMoney");
	labelMoney->setString((labelMoney->getString() + StringUtils::toString(money)).c_str());
	ret->addChild(labelMoney);
	CCLabelTTF* labelHorse=LayoutData::getLabelTTF(CPModuleName::GUILD,"bdGuangHuanLabelHorse");
	labelHorse->setString(name.c_str());
	ret->addChild(labelHorse);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	ret->addChild(menu);

	CCMenuItemImage *openBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuangHuanOpen");
	openBtn->setTag(index + 1);
	openBtn->setTarget(this, menu_selector(GuildBuildingGuangHuan::onOpen));	
	menu->addChild(openBtn);	

	CCScale9Sprite* boardItem=LayoutData::getScale9Sprite(CPModuleName::GUILD,"bdGuangHuanItemBoard");		
	boardItem->setScale(1.1f);
	ret->addChild(boardItem);
	
	string itemImgName = "bdGuangHuanItemImg"+StringUtils::toString(index);
	CCSprite *img = LayoutData::getSprite(CPModuleName::GUILD,itemImgName);
	img->setPosition(boardItem->getPosition());
	ret->addChild(img);

	return ret;
}

int GuildBuildingGuangHuan::getFirstPage() const
{
	return 1;
}

int GuildBuildingGuangHuan::getLastPage() const
{
	int itemCount = 0;
	StaticData::getGuildBuildingGuangHuanItemCount(itemCount);
	int perPage = LayoutData::getInt(CPModuleName::GUILD, "bdGuangHuanPerPage");
	if (perPage <= 0)
	{
		perPage = 6;
	}
	return (itemCount + perPage - 1)/perPage;
}

int GuildBuildingGuangHuan::getCurrentIndex() const
{
	const int perPage = LayoutData::getInt(CPModuleName::GUILD, "bdGuangHuanPerPage");
	return mItemList->getCurrentIndex() + perPage * (mCurrentPage - 1);
}

void GuildBuildingGuangHuan::onEnter()
{
	FullScreenPanel::onEnter();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

void GuildBuildingGuangHuan::onExit()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	FullScreenPanel::onExit();
}

void GuildBuildingGuangHuan::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_FINISH)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if(source == "HandleMessageGuildOpenBuffResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
				mChecker->stop();

				int buff_id = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				int time = 0;
				int money = 0;
				std::string openName = "";
				StaticData::getGuildBuildingGuangHuan(buff_id ,time,money,openName);
				CPEventHelper::msgNotify("","",Opcode::GuildOpenBuff,openName,0,0);
			}
		}

		refreshGuildMoney();
	}
}

////////////GuildBuildingGongDian/////////////////////////////////////////
GuildBuildingGongDian::GuildBuildingGongDian()
	:mChecker(NULL)
	,mBuildings(NULL)
	,mUpgradeBtn(NULL)
	,mOpenBtn(NULL)
	,mGuildMoneyLabel(NULL)
	,mCDLabel(NULL)
	,mCurrentIndex(0)
{
	
}

GuildBuildingGongDian::~GuildBuildingGongDian()
{

}

bool GuildBuildingGongDian::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	initUI();
	refreshList();
	refreshMenu();
	refreshGuildMoney();

	return true;
}

void GuildBuildingGongDian::onEnter()
{
	FullScreenPanel::onEnter();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

void GuildBuildingGongDian::onExit()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	FullScreenPanel::onExit();
}

void GuildBuildingGongDian::initUI()
{
	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianTitle");
	addChild(titleLabel);

	// board
	const int boardCnt = LayoutData::getInt(CPModuleName::GUILD, "bdGongDianBoardCnt");
	for (int i = 0; i < boardCnt; i++)
	{
		const std::string &key = "bdGongDianBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, key);
		addChild(board);
	}

	// labels
	const int labelCnt = LayoutData::getInt(CPModuleName::GUILD, "bdGongDianLabelCnt");
	for (int i = 0; i < labelCnt; i++)
	{
		const std::string &key = "bdGongDianLabel" + StringUtils::toString(i);
		CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::GUILD, key);
		addChild(label);
	}

	mGuildMoneyLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianGuildMoney");
	addChild(mGuildMoneyLabel);

	mCDLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianCDTime");
	addChild(mCDLabel);

	// list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUILD, "bdGongDianList");
	mBuildings = CPItemComponents::create(listSize, new CPLayoutList);
	mBuildings->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdGongDianList"));
	addChild(mBuildings);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	mUpgradeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGongDianUpgrade");
	mUpgradeBtn->setTarget(this, menu_selector(GuildBuildingGongDian::onUpgrade));
	menu->addChild(mUpgradeBtn);

	mOpenBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGongDianOpen");
	mOpenBtn->setTarget(this, menu_selector(GuildBuildingGongDian::onOpen));
	menu->addChild(mOpenBtn);

	mFinishBuildingBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGongDianFinish");
	mFinishBuildingBtn->setTarget(this, menu_selector(GuildBuildingGongDian::onFinishBuilding));
	menu->addChild(mFinishBuildingBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void GuildBuildingGongDian::refreshMenu()
{
	const int buildingID = mCurrentIndex + GuildType::guild_building_gong_dian_level;
	const int level = GuildData::getGuildProp(buildingID);
	if (mCurrentIndex != GuildBuilding::gong_dian &&
		level > 0)
	{
		mOpenBtn->setEnabled(true);
	}
	else
	{
		mOpenBtn->setEnabled(false);
	}
	
	//
	if (GuildData::getGuildProp(GuildType::guild_building_id) == 0)
	{
		if (canUpgradeBuilding(buildingID))
		{
			mUpgradeBtn->setEnabled(true);
		}
		else
		{
			mUpgradeBtn->setEnabled(false);
		}

		mFinishBuildingBtn->setEnabled(false);
	}
	else
	{
		mUpgradeBtn->setEnabled(false);
		mFinishBuildingBtn->setEnabled(true);
	}
}

bool GuildBuildingGongDian::canUpgradeBuilding(int building_id)
{
	int building_max_level = 0;
	StaticData::getGuildBuildingMaxLevel(building_id, building_max_level);
	const int gong_dian_level = GuildData::getGuildProp(GuildType::guild_building_gong_dian_level);

	const int level = GuildData::getGuildProp(building_id);
	if (level <= 0 || level >= building_max_level)
		return false;

	if (building_id - GuildType::guild_building_gong_dian_level
		== GuildBuilding::gong_dian)
	{
		return true;
	}

	return level < gong_dian_level;
}

void GuildBuildingGongDian::refreshList()
{
	mBuildings->removeAllItems();

	for (int i = GuildBuilding::begin; i < GuildBuilding::max; i++)
	{
		CCMenuItem *item = getListItem(i);
		if (item)
		{
			item->setTarget(this, menu_selector(GuildBuildingGongDian::onList));
			mBuildings->addItem(item);
			item->setTag(i);
		}
	}

	mBuildings->setCurrentIndex(mCurrentIndex);
}

void GuildBuildingGongDian::refreshGuildMoney()
{
	mGuildMoneyLabel->setString(StringUtils::toString(GuildData::getGuildProp(GuildType::guild_money)).c_str());
}

void GuildBuildingGongDian::refreshCD()
{
	int time = 0;
	if (GuildData::getGuildProp(GuildType::guild_building_id) >= 0)
	{
		time = GuildData::getGuildProp(GuildType::guild_building_build_time) - ActivityData::getWorldTime();
		if (time < 0)
		{
			time = 0;
		}
	}
	mCDLabel->setString(StringUtils::timeToString(time, TimeType::hms).c_str());
	if (time == 0)
	{
		mCDLabel->setColor(ccGREEN);
	}
	else
	{
		mCDLabel->setColor(ccRED);
	}
}

void GuildBuildingGongDian::onList( CCObject *target )
{
	const int index = mBuildings->getCurrentIndex();
	if (index != mCurrentIndex)
	{
		mCurrentIndex = index;
		refreshMenu();
	}
}

void GuildBuildingGongDian::onUpgrade( CCObject *target )
{
	mChecker->start();
	const int buildingID = mCurrentIndex + GuildType::guild_building_gong_dian_level;
	MsgGuildBuildRequest *msg = new MsgGuildBuildRequest;
	msg->buildingid = buildingID;
	HandleMessage::sendMessage(msg);
}

void GuildBuildingGongDian::onOpen( CCObject *target )
{
	CPEventHelper::setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_1, mBuildings->getCurrentIndex());
	CPEventHelper::dispatcher(CPEventName::UI_OPEN, "GuildBuildingGongDian", "GuildBuildingPanel");
}

void GuildBuildingGongDian::onFinishBuilding(CCObject *target)
{
	time_t finishTime = GuildData::getGuildProp(GuildType::guild_building_build_time);
	time_t now = time(NULL);
	int needGold = ((finishTime - now) / 3600 + 1) * 10;
	if (needGold < 0)
		needGold = 0;

	std::vector<std::string> vec;
	vec.push_back(StringUtils::toString(needGold));
	FloatPanel::show(FloatPanelType::Arena_clear_cd, vec,
		this, floatpanel_selector(GuildBuildingGongDian::onFinishBuilding));
}

void GuildBuildingGongDian::onFinishBuilding(int type)
{
	if (type == Button_QD)
	{
		MsgGuildFinishBuildingRequest *msg =
			new MsgGuildFinishBuildingRequest();
		HandleMessage::sendMessage(msg);
	}
}

CCMenuItem * GuildBuildingGongDian::getListItem( int index )
{
	const int buildingID = index + GuildType::guild_building_gong_dian_level;
	const int level = GuildData::getGuildProp(buildingID);
	if (level <= 0)
	{
		return NULL;
	}

	CCNode *sel = LayoutData::getScale9Sprite(CPModuleName::GUILD, "bdGongDianItemSel");
	const CCSize &size = sel->getContentSize();
	CCNode *norm = CCNode::create();
	norm->setContentSize(size);

	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	//
	const int y = size.height/2;

	std::string name;
	StaticData::getGuildBuildingName(buildingID, name);
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianBuildingName");
	nameLabel->setString(name.c_str());
	nameLabel->setPositionY(y);
	ret->addChild(nameLabel);

	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianBuildingLevel");
	levelLabel->setString(StringUtils::toString(level).c_str());
	levelLabel->setPositionY(y);
	ret->addChild(levelLabel);

	int maxLevel = 0;
	StaticData::getGuildBuildingMaxLevel(buildingID, maxLevel);
	CCLabelTTF *maxLevelLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianBuildingMaxLevel");
	maxLevelLabel->setString(StringUtils::toString(maxLevel).c_str());
	maxLevelLabel->setPositionY(y);
	ret->addChild(maxLevelLabel);

	CCLabelTTF *costLevel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianBuildingUpgradeCost");
	costLevel->setString("-");
	costLevel->setPositionY(y);
	ret->addChild(costLevel);

	CCLabelTTF *timeLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGongDianBuildingUpgradeTime");
	timeLabel->setString("-");
	timeLabel->setPositionY(y);
	ret->addChild(timeLabel);

	if (0 <= level && level < maxLevel &&
		maxLevel > 1)
	{
		int costMoney = 0, costTime = 0;
		StaticData::getGuildBuildingLevelUpData(buildingID, level + 1, costMoney, costTime);
		costLevel->setString(StringUtils::toString(costMoney).c_str());
		timeLabel->setString(StringUtils::timeToString(costTime, TimeType::hms).c_str());
	}
	return ret;
}

void GuildBuildingGongDian::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncGuildExDataNotify")
		{
			const int propID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (propID == GuildType::guild_money)
			{
				refreshGuildMoney();
			}
			else if (GuildType::guild_building_gong_dian_level <= propID &&
				propID <= GuildType::guild_building_guang_huan_level)
			{
				refreshList();
			}
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGuildBuildResponse")
		{
			mChecker->stop();
			const int code = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			if (code == Error::Success)
			{
				mUpgradeBtn->setEnabled(false);
				mFinishBuildingBtn->setEnabled(true);
			}
		}
		else if (source == "HandleMessageGuildFinishBuildingResponse")
		{
			const int code = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			if (code == Error::Success)
			{
				if (canUpgradeBuilding(mCurrentIndex + GuildType::guild_building_gong_dian_level))
					mUpgradeBtn->setEnabled(true);

				mFinishBuildingBtn->setEnabled(false);
			}
		}
	}
	else if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			refreshCD();
		}
	}
}

////////////GuildBuildingTanXian/////////////////////////////////////////
GuildBuildingTanXian::GuildBuildingTanXian()
	:mStateLayer(NULL)
	,mChecker(NULL)
	,mPilgrimageList(NULL)
	,mTanXianMenu(NULL)
	,mUseCount(0)
	,mRandSid(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

GuildBuildingTanXian::~GuildBuildingTanXian()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool GuildBuildingTanXian::init()
{
	if (!MidScreenPanel::init())
	{
		return false;
	}

	vec.clear();

	initUI();
	initLeft();
	initRight();
	

	return true;
}

void GuildBuildingTanXian::initUI()
{
	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdTanXianTitle");
	addChild(titleLabel);

	// board
	const int cnt = LayoutData::getInt(CPModuleName::GUILD, "bdTanXianBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "bdTanXianBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, key);
		addChild(board);
	}

	// list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUILD, "bdTanXianList");
	mItemList = CPItemComponents::create(listSize, new CPLayoutList());	
	mItemList ->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdTanXianList"));
	const CCSize &barSize = LayoutData::getSize(CPModuleName::GUILD, "bdTanXianItemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mItemList->setScrollbar(scrollBar);
	addChild(mItemList);

	// state Layer
	mStateLayer = CCLayer::create();
	addChild(mStateLayer);

	mTanXianMenu = GeneralMenu::create();
	mTanXianMenu->setPosition(CCPointZero);
	addChild(mTanXianMenu);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void GuildBuildingTanXian::initLeft()
{
	HandleMessage::sendMessage(new MsgGuildExploreInitRequest);
	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItem *btn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdTanXianBtn");
	btn->setTarget(this, menu_selector(GuildBuildingTanXian::onExplore));
	menu->addChild(btn);
}

void GuildBuildingTanXian::initRight()
{
	CCLabelTTF *exploreLabel=LayoutData::getLabelTTF(CPModuleName::GUILD, "bdTanXianExploreLabel");
	addChild(exploreLabel);

	const int lineCnt = LayoutData::getInt(CPModuleName::GUILD, "bdTanXianLineCnt"); 
	const int lineReduce = LayoutData::getInt(CPModuleName::GUILD, "bdTanXianLineReduce");
	for (int i = 0; i < lineCnt; i++)
	{
		CCSprite *hengXianImg = LayoutData::getSprite(CPModuleName::GUILD, "bdTanXianHengXianImg");			
		hengXianImg->setPositionY(hengXianImg->getPositionY()-i*lineReduce);		
		addChild(hengXianImg);
	}	
}

CCPoint GuildBuildingTanXian::getPos(int i, int &j)
{  	
	CCPoint point = LayoutData::getPoint(CPModuleName::GUILD, "bdTanXianGetPoint");	
	const int norm =LayoutData::getInt(CPModuleName::GUILD, "bdTanXianNorm");
	const int xIncrease = LayoutData::getInt(CPModuleName::GUILD, "bdTanXianIncrease");
	const int yReduce= LayoutData::getInt(CPModuleName::GUILD, "bdTanXianReduces");
	
	if (i<norm)
	{			
		point.setPoint(point.x + i*xIncrease, point.y);
	}	
	else 
	{
		point.setPoint(point.x + j*xIncrease, point.y-yReduce);	
		j++;
	}
	return point;
}

void GuildBuildingTanXian::getTanXianItem(int i, int &j)
{
	int sid = 0;
	int indexID = i + 1;	
	
	sid = GuildData::getGuildTanXianData(i);
	vec.push_back(sid);		

	CCPoint allPoint = getPos(i, j);
	CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdTanXianItem");
	item->setPosition(allPoint);
	item->setTarget(this,menu_selector(GuildBuildingTanXian::onItem));	
	mTanXianMenu->addChild(item,0,sid);		

	CCSprite *allSprite = LayoutData::getItemIcon(sid);
	allSprite->setPosition(allPoint);	
	mTanXianMenu->addChild(allSprite);		
}

void GuildBuildingTanXian::onExplore( CCObject *target)
{	
	HandleMessage::sendMessage(new MsgGuildExploreRequest);	
   
	const int buildingID = GuildType::guild_building_gong_dian_level;
	int level = GuildData::getGuildProp(buildingID);
	int totalcnt = 0;
	StaticData::getGuildBuildingTanXianCount(level,totalcnt);
    if (mUseCount >= 0 && mUseCount <= totalcnt && HeroData::getProp(Entity::attr_guild_contribution) > 10) //***********此处判断还要加上当前贡献大于10时，才能操作
    {
	   refreshList();	  
    }  
}

void GuildBuildingTanXian::onItem( CCObject *target)
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int sid = node->getTag();
		if (sid > 0)
		{
			ItemTooltip *tips = ItemTooltip::create();
			tips->setTooltipContentbysid(sid);
			tips->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdShangDianTips"));
			addChild(tips);
		}		
	}
}

void GuildBuildingTanXian::refreshList()
{
	mStateLayer->removeAllChildren();
	mItemList->removeAllItems();

	mUseCount = ActivityData::getExDataX(EvtData::evt_guildexplore);
	const int imgCnt = LayoutData::getInt(CPModuleName::GUILD,"bdTanXianImgCnt");
	
	for ( int i = 0, j = 0; i < imgCnt; i++ )
	{
		getTanXianItem( i, j );
	}//for

	//right board
	std::string strInfo = "";
    //下个版本该处字符串由服务器发送过来
	strInfo = LayoutData::getString(CPModuleName::GUILD, "guildTanXianText");

	int fontSize = LayoutData::getInt(CPModuleName::GUILD, "bdTanXianFontSize");
	int width = LayoutData::getInt(CPModuleName::GUILD, "bdTanXianTextWidth");
	CPRichText *text = RichTextUtils::getRichText(strInfo, fontSize, width, 0);//text, fontSize, width, heigh
	mItemList->addItem(text);

	//left board
	GeneralMenu *menu = GeneralMenu::create();
	mStateLayer->addChild(menu);

	CCPoint selectPoint = LayoutData::getPoint(CPModuleName::GUILD, "bdTanXianSelectPoint");
	CCMenuItemImage *selectItem = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdTanXianItem");
	selectItem->setPosition(selectPoint);
	selectItem->setTarget(this, menu_selector(GuildBuildingTanXian::onItem));
	menu->addChild(selectItem, 0, mRandSid);

	if (mRandSid > 0)
	{                                                     
		CCSprite *selectSprite = LayoutData::getItemIcon(mRandSid);
		selectSprite->setPosition(selectPoint);
		menu->addChild(selectSprite);
	}

	const int buildingID = GuildType::guild_building_mao_xian_level;
	int level = GuildData::getGuildProp(buildingID);
	int totalcnt = 0;
	int consumeGX = 0;
	int nowGX = 0;
	StaticData::getGuildBuildingTanXianCount(level, totalcnt);
	StaticData::getGlobalData("guildTanxianCost", consumeGX);
	nowGX = HeroData::getProp(Entity::attr_guild_contribution);	
	
	CCLabelTTF *CiShuLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdTanXianCiShuLabel");
	CiShuLabel->setString((CiShuLabel->getString() + StringUtils::toString(totalcnt - mUseCount) + "/" + StringUtils::toString(totalcnt)).c_str());
	mStateLayer->addChild(CiShuLabel);		

	CCLabelTTF *consumeLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdTanXianXiaoHaoLabel");
	consumeLabel->setString((consumeLabel->getString() + StringUtils::toString(consumeGX)).c_str());
	mStateLayer->addChild(consumeLabel);

	CCLabelTTF *nowLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdTanXianDangQianLabel");
	nowLabel->setString((nowLabel->getString() + StringUtils::toString(nowGX)).c_str());
	mStateLayer->addChild(nowLabel);	
}

void GuildBuildingTanXian::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_FINISH)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageGuildExploreInitResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
				mChecker->stop();				
				refreshList();
			}
			else
			{
			    close();
			}
		}
		else if (source == "HandleMessageGuildExploreResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
				mRandSid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				mChecker->stop();				
				refreshList();
			}		
		}
	}
}

////////GuildBuildingShenShou////////////////////////////////////////////////
GuildBuildingShenShou::GuildBuildingShenShou()
	:mStateLayer(NULL)
	,mChecker(NULL)
	,mPilgrimageList(NULL)
{

}

GuildBuildingShenShou::~GuildBuildingShenShou()
{

}

bool GuildBuildingShenShou::init()
{
	if (!MidScreenPanel::init())
	{
		return false;
	}

	initUI();
	refreshList();	

	return true;
}

void GuildBuildingShenShou::initUI()
{
	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShenShouTitle");
	addChild(titleLabel);

	// board
	const int cnt = LayoutData::getInt(CPModuleName::GUILD, "bdShenShouBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "bdShenShouBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, key);
		addChild(board);
	}

	//list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUILD,"bdShenShouList");
	mItemList = CPItemComponents::create(listSize,new CPLayoutList());
	mItemList ->setPosition(LayoutData::getPoint(CPModuleName::GUILD,"bdShenShouList"));
	addChild(mItemList);

	//
	initLeft();
	initRight();

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void GuildBuildingShenShou::refreshList()
{

}

void GuildBuildingShenShou::initLeft()
{
	// note
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShenShouNameLabel");
	addChild(nameLabel);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	//board0 中的两个箭头
	CCMenuItemImage *doubleLeftBtn = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdShenShouDoubleLeftBtn");
	doubleLeftBtn->setTarget(this, menu_selector(GuildBuildingShenShou::onLeft));	
	menu->addChild(doubleLeftBtn);

	CCMenuItemImage *doubleRightBtn = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdShenShouDoubleRightBtn");
	doubleRightBtn->setTarget(this, menu_selector(GuildBuildingShenShou::onRight));
	menu->addChild(doubleRightBtn);
	
	
	//此处留给播放神兽动画的	

	//board1 中的两个箭头
	CCMenuItemImage *leftBtn = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdShenShouLeftBtn");
	leftBtn ->setTarget(this, menu_selector(GuildBuildingShenShou::onLeft));	
	menu->addChild(leftBtn);

	CCMenuItemImage *rightBtn = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdShenShouRightBtn");
	rightBtn->setTarget(this, menu_selector(GuildBuildingShenShou::onRight));
	menu->addChild(rightBtn);

	//board1 中两个箭头之间的三个框	
	const int bkCnt = LayoutData::getInt(CPModuleName::GUILD,"bdShenShouLeftBianKuangCnt");
	const int bkInterval = LayoutData::getInt(CPModuleName::GUILD,"bdShenShouBianKuangInterval");
	CCPoint bkPoint = LayoutData::getPoint(CPModuleName::GUILD,"bdShenShouLeftBianKuangPoint");
	for (int i=0;i<bkCnt;i++)
	{		
		CCSprite *img = LayoutData::getSprite(CPModuleName::GUILD, "bdShenShou");
		img->setPosition(ccp(bkPoint.x+i*bkInterval,bkPoint.y));		
		addChild(img);		
	}	
}

void GuildBuildingShenShou::initRight()
{
	CCLabelTTF *articleLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShenShouArticleLabel");
	addChild(articleLabel);

	const int perLine = LayoutData::getInt(CPModuleName::GUILD,"bdShenShouPerLine");
	const CCSize &size = LayoutData::getSize(CPModuleName::GUILD,"bdShenShouRightBianKuangInterval");
	const CCPoint &ptFirst = LayoutData::getPoint(CPModuleName::GUILD,"bdShenShouRightBianKuangPoint");
	const int bkcnt = LayoutData::getInt(CPModuleName::GUILD,"bdShenShouRightBianKuangCnt");
	for (int i=0,j=0;i<bkcnt;i++)
	{		
		CCSprite *img = LayoutData::getSprite(CPModuleName::GUILD, "bdShenShou");
		//左上角的框框为起点，向右、向上为正
		img->setPosition(ccp(ptFirst.x + i%perLine * size.width, ptFirst.y - i/perLine * size.height));		
		addChild(img);
	}	

	//神兽界面右边框里的字幕
	int recommendNum =0;
	int levelNum = 0;
	int challengeNum = 0;
	int consume = 0;
	int challengeNums = 0;
	int guildMoney = 0;
	StaticData::getGuildBuildingShenShou(recommendNum,levelNum,challengeNum,consume,challengeNums,guildMoney);

	CCLabelTTF *recommendLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShenShouRecommendLabel");
	recommendLabel->setString((recommendLabel->getString() + StringUtils::toString(recommendNum)).c_str());
	addChild(recommendLabel);
	CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdShenShouLevelLabel");
	levelLabel->setString((levelLabel->getString()+StringUtils::toString(levelNum)).c_str());
	addChild(levelLabel);

	//神兽界面右边框里的两条线
	const int imgLineCnt = LayoutData::getInt(CPModuleName::GUILD,"bdShenShouImgLineCnt");
	const int imgLineInterval = LayoutData::getInt(CPModuleName::GUILD,"bdShenShouImgLineInterval");
	for (int i = 0; i < imgLineCnt; i++)
	{
		CCSprite *hengXianImg = LayoutData::getSprite(CPModuleName::GUILD, "bdShenShouHengXianImg");			
		hengXianImg->setPositionY(hengXianImg->getPositionY()-i*imgLineInterval);
		hengXianImg->setScaleY(1.1f);
		addChild(hengXianImg);
	}
	
	//神兽界面右边框里的字幕
	CCLabelTTF *challengeLabel = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdShenShouChallengeLabel");
	addChild(challengeLabel);
	CCPoint numberPoint = LayoutData::getPoint(CPModuleName::GUILD,"bdShenShouNumberPoint");
	
	CCLabelTTF *numberLabel = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdShenShouNumberLabel");
	numberLabel->setString((StringUtils::toString(challengeNum) + LayoutData::getString(CPModuleName::GUILD,"vipText")).c_str());
	numberLabel->setPosition(numberPoint);
	addChild(numberLabel);
	
	CCLabelTTF *consumeLabel = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdShenShouConsumeLabel");
	consumeLabel->setString((consumeLabel->getString()+StringUtils::toString(consume)).c_str());
	addChild(consumeLabel);

	CCLabelTTF *challengesLabel = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdShenShouChallengesLabel");	
	addChild(challengesLabel);
	CCPoint numbersPoint = LayoutData::getPoint(CPModuleName::GUILD,"bdShenShouNumbersPoint");	
	CCLabelTTF *numbersLabel = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdShenShouNumberLabel");
	numbersLabel->setString((StringUtils::toString(challengeNums)).c_str());
	numbersLabel->setPosition(numbersPoint);
	addChild(numbersLabel);
	
	CCLabelTTF *guildMoneyLabel = LayoutData::getLabelTTF(CPModuleName::GUILD,"bdShenShouGuildMoneyLabel");
	guildMoneyLabel->setString((guildMoneyLabel->getString()+StringUtils::toString(guildMoney)).c_str());
	addChild(guildMoneyLabel);

	//神兽界面的四个button
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *challengeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD,"bdShenShouChallengeBtn");	
	challengeBtn->setTarget(this, menu_selector(GuildBuildingShenShou::personalChallenge));
	menu->addChild(challengeBtn);
	
	CCMenuItemImage *challengesBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD,"bdShenShouChallengesBtn");	
	challengesBtn->setTarget(this, menu_selector(GuildBuildingShenShou::guildChallenge));
	menu->addChild(challengesBtn);

	CCMenuItemImage *enterChallengeBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD,"bdShenShouEnterChallengeBtn");	
	enterChallengeBtn ->setTarget(this, menu_selector(GuildBuildingShenShou::enterChallenge));
	menu->addChild(enterChallengeBtn);
	
	CCMenuItemImage *addBtn = LayoutData::getMenuItemImg(CPModuleName::GUILD,"bdShenShouAddBtn");	
	addBtn ->setTarget(this, menu_selector(GuildBuildingShenShou::addTarget));
	menu->addChild(addBtn);
}

void GuildBuildingShenShou::personalChallenge( CCObject *target )
{

}

void GuildBuildingShenShou::guildChallenge( CCObject *target )
{

}

void GuildBuildingShenShou::enterChallenge( CCObject *target )
{

}

void GuildBuildingShenShou::addTarget( CCObject *target )
{

}

void GuildBuildingShenShou::onLeft( CCObject *target )
{

}

void GuildBuildingShenShou::onRight( CCObject *target )
{

}

void GuildBuildingShenShou::onCPEvent( const std::string &eventName )
{

}

////////GuildBuildingGuanGong////////////////////////////////////////////////
GuildBuildingGuanGong::GuildBuildingGuanGong()
	:mStateLayer(NULL)
	,mChecker(NULL)
	,mPilgrimageList(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

GuildBuildingGuanGong::~GuildBuildingGuanGong()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool GuildBuildingGuanGong::init()
{
	if (!MidScreenPanel::init())
	{
		return false;
	}

	initUI();
	refreshList();
	refreshState();

	return true;
}

void GuildBuildingGuanGong::initUI()
{
	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongTitle");
	addChild(titleLabel);

	// board
	const int cnt = LayoutData::getInt(CPModuleName::GUILD, "bdGuanGongBoardCnt");
	for (int i = 0; i < cnt; i++)
	{
		const std::string &key = "bdGuanGongBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, key);
		addChild(board);
	}

	//
	initLeft();
	initRight();

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}


void GuildBuildingGuanGong::initLeft()
{
	// image
	CCSprite *img = LayoutData::getSprite(CPModuleName::GUILD, "bdGuanGong");
	addChild(img);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	int sid = 0;
	StaticData::getGuanGongCloth(HeroData::getGender(), sid);
	CCMenuItemImage *btn = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdGuanGongItem");
	btn->setTarget(this, menu_selector(GuildBuildingGuanGong::onItem));
	menu->addChild(btn, 0, sid);

	const CCSize &size = btn->getContentSize();
	CCSprite *itemIcon = LayoutData::getItemIcon(sid);
	itemIcon->setPosition(ccp(size.width/2, size.height/2));
	btn->addChild(itemIcon);

	// note
	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongClothNote");
	addChild(noteLabel);
}

void GuildBuildingGuanGong::initRight()
{
	// note
	const CCSize &noteSize = LayoutData::getSize(CPModuleName::GUILD, "bdGuanGongNote");
	CPItemComponents *noteList = CPItemComponents::create(noteSize, new CPLayoutList);
	noteList->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdGuanGongNote"));
	addChild(noteList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::GUILD, "bdGuanGongNoteBar");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	noteList->setScrollbar(scrollBar);

	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongPilgrimageNote");
	noteList->addItem(noteLabel);

	// pilgrimage list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUILD, "bdGuanGongPilgrimage");
	mPilgrimageList = CPItemComponents::create(listSize, new CPLayoutList);
	mPilgrimageList->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdGuanGongPilgrimage"));
	addChild(mPilgrimageList);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *vipBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuanGongVIP");
	vipBtn->setTarget(this, menu_selector(GuildBuildingGuanGong::onVIP));
	menu->addChild(vipBtn);

	CCMenuItemImage *addBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuanGongAdd");
	addBtn->setTarget(this, menu_selector(GuildBuildingGuanGong::onAdd));
	menu->addChild(addBtn);

	CCMenuItemImage *rewardBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuanGongReward");
	rewardBtn->setTarget(this, menu_selector(GuildBuildingGuanGong::onReward));
	menu->addChild(rewardBtn);

	// state layer
	mStateLayer = CCLayer::create();
	addChild(mStateLayer);
}

void GuildBuildingGuanGong::refreshList()
{
	mPilgrimageList->removeAllItems();

	const int cnt = LayoutData::getInt(CPModuleName::GUILD, "bdGuanGongPilgrimageCnt");
	for (int i = 0; i < cnt; i++)
	{
		CCNode *node = getPilgrimageNode(i);
		mPilgrimageList->addItem(node);
	}
}

void GuildBuildingGuanGong::refreshState()
{
	mStateLayer->removeAllChildren();

	CCLabelTTF *pointLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongPilgrimagePoint");
	mStateLayer->addChild(pointLabel);

	CCLabelTTF *pointValueLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongPilgrimagePointValue");
	mStateLayer->addChild(pointValueLabel);

	int point = 0, addCnt = 0, cnt = 0;
	ActivityData::getExData(EvtData::evt_guildpray, cnt, addCnt, point);

	int maxPoint = 0;
	StaticData::getGlobalData("guildPrayMaxContribution", maxPoint);
	const std::string &pointStr = StringUtils::toString(point) + "/" + StringUtils::toString(maxPoint);
	pointValueLabel->setString(pointStr.c_str());

	CCLabelTTF *cntLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongPilgrimageCnt");
	mStateLayer->addChild(cntLabel);

	const int gongDianLevel = GuildData::getGuildProp(GuildType::guild_building_gong_dian_level);
	int maxCnt = 0;
	StaticData::getGuildPrayCount(gongDianLevel, maxCnt);

	int vipPrayTimes = 0;
	const int vipLevel = HeroData::getProp(Entity::attr_vip_level);
	StaticData::getVIPData(vipLevel, "praycnt", vipPrayTimes);
	maxCnt += vipPrayTimes;

	const std::string &cntStr = cntLabel->getString() + StringUtils::toString(maxCnt - cnt) + "/" + StringUtils::toString(maxCnt);
	cntLabel->setString(cntStr.c_str());
}

void GuildBuildingGuanGong::onItem( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int sid = node->getTag();
		if (sid > 0)
		{
			ItemTooltip *tips = ItemTooltip::create();
			tips->setTooltipContentbysid(sid);
			tips->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdGuanGongTips"));
			addChild(tips);
		}
	}
}

void GuildBuildingGuanGong::onPilgrimage( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int type = node->getTag();
		int cost = 0;
		switch (type)
		{
		case GuildType::worship_type_1:
			{
				StaticData::getGlobalData("guildMoneyPrayCost", cost);
				if (!ItemOperator::testMoneyEnough(cost))
				{
					return;
				}
				break;
			}
		case GuildType::worship_type_2:
			{
				StaticData::getGlobalData("guildHonorPrayCost", cost);
				if (!ItemOperator::testHonorEnough(cost))
				{
					return;
				}
				break;
			}
		case GuildType::worship_type_3:
			{
				StaticData::getGlobalData("guildGoldPrayCost", cost);
				if (!ItemOperator::testGoldEnough(cost))
				{
					return;
				}
				break;
			}
		}
		mChecker->start();
		MsgGuildGuanGongWorshipRequest *msg = new MsgGuildGuanGongWorshipRequest;
		msg->type = type;
		HandleMessage::sendMessage(msg);
	}
}

void GuildBuildingGuanGong::onVIP( CCObject *target )
{
	CPEventHelper::openPanel("RechargePanel");
}

void GuildBuildingGuanGong::onAdd( CCObject *target )
{
	int cost = 0;
	StaticData::getGlobalData("guildAddPrayCost", cost);
	cost += ActivityData::getExDataY(EvtData::evt_guildpray);
	cost = cost > 20 ? 20 : cost;
	if (!ItemOperator::testGoldEnough(cost))
	{
		return;
	}

	StrVector vect;
	vect.push_back(StringUtils::toString(cost));
	FloatPanel::show(FloatPanelType::Guild_guan_gong_add_count, vect, this, floatpanel_selector(GuildBuildingGuanGong::onAdd));
}

void GuildBuildingGuanGong::onAdd( int type )
{
	if (type == Button_QD)
	{
		mChecker->start();
		HandleMessage::sendMessage(new MsgGuildGuanGongAddCountRequest);
	}
}

void GuildBuildingGuanGong::onReward( CCObject *target )
{
	if (true)
	{
		mChecker->start();
		HandleMessage::sendMessage(new MsgGuildGuanGongGetRewardRequest);
	}
}

CCNode * GuildBuildingGuanGong::getPilgrimageNode( int index )
{
	CCNode *ret = CCNode::create();
	ret->setContentSize(LayoutData::getSize(CPModuleName::GUILD, "bdGuanGongPilgrimageItem"));

	// icon
	CCSprite *iconBoard = LayoutData::getSprite(CPModuleName::GUILD, "bdGuanGongPilgrimageIconBoard");
	ret->addChild(iconBoard);

	const CCSize &boardSize = iconBoard->getContentSize();
	const std::string &iconKey = "bdGuanGongPilgrimageIcon" + StringUtils::toString(index);
	CCSprite *icon = LayoutData::getSprite(CPModuleName::GUILD, iconKey);
	icon->setPosition(ccp(boardSize.width/2, boardSize.height/2));
	iconBoard->addChild(icon);

	// label
	CCLabelTTF *rewardLabel1 = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongPilgrimageRewardContribution");
	ret->addChild(rewardLabel1);

	CCLabelTTF *rewardLabel2 = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongPilgrimageRewardExp");
	ret->addChild(rewardLabel2);

	int exp = 0;
	StaticData::getGuildPrayExp(HeroData::getLevel(), index, exp);
	const std::string &str2 = rewardLabel2->getString() + StringUtils::toString(exp);
	rewardLabel2->setString(str2.c_str());

	CCLabelTTF *costLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGuanGongPilgrimageCost");
	ret->addChild(costLabel);

	int contribution = 0;
	int cost = 0;
	std::string costStr;
	if (index == GuildType::worship_type_1)
	{
		StaticData::getGlobalData("guildMoneyPrayContribution", contribution);
		StaticData::getGlobalData("guildMoneyPrayCost", cost);
		costStr = costLabel->getString() + StringUtils::toString(cost) + LayoutData::getString(CPModuleName::COMMON, "money");
	}
	else if (index == GuildType::worship_type_2)
	{
		StaticData::getGlobalData("guildHonorPrayContribution", contribution);
		StaticData::getGlobalData("guildHonorPrayCost", cost);
		costStr = costLabel->getString() + StringUtils::toString(cost) + LayoutData::getString(CPModuleName::COMMON, "honor");
	}
	else
	{
		StaticData::getGlobalData("guildGoldPrayContribution", contribution);
		StaticData::getGlobalData("guildGoldPrayCost", cost);
		costStr = costLabel->getString() + StringUtils::toString(cost) + LayoutData::getString(CPModuleName::COMMON, "gold");
	}
	const std::string &str1 = rewardLabel1->getString() + StringUtils::toString(contribution);
	rewardLabel1->setString(str1.c_str());
	costLabel->setString(costStr.c_str());

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	ret->addChild(menu);

	CCMenuItemImage *btn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdGuanGongPilgrimage");
	btn->setTarget(this, menu_selector(GuildBuildingGuanGong::onPilgrimage));
	menu->addChild(btn, 0, index);

	return ret;
}

void GuildBuildingGuanGong::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGuildGuanGongWorshipResponse" ||
			source == "HandleMessageGuildGuanGongAddCountResponse" ||
			source == "HandleMessageGuildGuanGongGetRewardResponse")
		{
			mChecker->stop();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageSyncPlayerEventDataNotify")
		{
			const int wid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (wid == EvtData::evt_guildpray)
			{
				refreshState();
			}
		}
		else if (source == "HandleMessageUpdPlayerLvlExpNotify")
		{
			const int dLevel = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (dLevel != 0)
			{
				refreshList();
			}
		}
	}
}

///////////GuildBuildingFuli/////////////////////////////////////////
GuildBuildingFuli::GuildBuildingFuli()
	:components(NULL)	
	,mStatus(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH,this);
}

GuildBuildingFuli::~GuildBuildingFuli()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH,this);
}

bool GuildBuildingFuli::init()
{
	if (!MidScreenPanel::init())
	{
		return false;
	}

	initUI();

	return true;
}

void GuildBuildingFuli::initUI()
{
	HandleMessage::sendMessage(new MsgGuildWelfareStatusRequest);

	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdFuLiTitle");
	addChild(titleLabel);

	// top board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, "bdFuLiTopBoard");
	addChild(board);

	// note label
	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdFuLiNote");
	addChild(noteLabel);

	// list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUILD, "bdFuLiList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::GUILD, "bdFuLiItem");
	const int perLine = LayoutData::getInt(CPModuleName::GUILD, "bdFuLiPerLine");
	components = CPItemComponents::create(listSize, new CPLayoutGrid(perLine, itemSize, true));
	components->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdFuLiList"));
	addChild(components);		
}

void GuildBuildingFuli::refreshState()
{	
	components->removeAllItems();
	const int listCnt = LayoutData::getInt(CPModuleName::GUILD, "bdFuLiCnt");
	for (int i = 0; i < listCnt; i++)
	{
		CCNode *node = getListItemNode(i);
		components->addItem(node);
	}
}

void GuildBuildingFuli::onItem( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int sid = node->getTag();		
		if (sid > 0)
		{
			ItemTooltip *tips = ItemTooltip::create();
			tips->setTooltipContentbysid(sid);
			tips->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdGuanGongTips"));
			addChild(tips);
		}
	}
}

void GuildBuildingFuli::onOpen( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{		
		const int index = node->getTag();
        MsgGuildOpenWelfareRequest *reqOpen = new MsgGuildOpenWelfareRequest;
	    reqOpen->welfareID = index;
	   HandleMessage::sendMessage(reqOpen);
	}
}

void GuildBuildingFuli::onReward( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{		
		const int index = node->getTag();
	    MsgGuildGetWelfareRequest *reqGet = new MsgGuildGetWelfareRequest;
	    reqGet->welfareID = index;
	    HandleMessage::sendMessage(reqGet);
	}
}

CCNode * GuildBuildingFuli::getListItemNode( int index )
{
	CCScale9Sprite *ret = LayoutData::getScale9Sprite(CPModuleName::GUILD, "bdFuLiItemBoard");

	int sid = 0;
	std::string itemName;
	StaticData::getGuildFuLiItem(index + 1, sid);
	StaticData::getItemName(sid, itemName);

	// label
	CCLabelTTF *itemNameLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdFuLiItemName");
	itemNameLabel->setString(itemName.c_str());
	ret->addChild(itemNameLabel);

	std::string statusStr = "";
	CCLabelTTF *stateLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdFuLiItemState");
	if (mStatus & (1<<(index + 1)))
	{
		statusStr = LayoutData::getString(CPModuleName::GUILD,"FuLiStatusOpenStr");
		stateLabel->setString(statusStr.c_str());
	}	
	ret->addChild(stateLabel);

	const std::string &costKey = "bdFuLiItemCost" + StringUtils::toString(index);
	CCLabelTTF *costLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, costKey);
	ret->addChild(costLabel);

	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdFuLiItemNote");
	ret->addChild(noteLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	ret->addChild(menu);

	CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdFuLiItem");
	itemBtn->setTarget(this, menu_selector(GuildBuildingFuli::onItem));
	menu->addChild(itemBtn, 0, sid);

	const CCSize &itemSize = itemBtn->getContentSize();
	CCSprite *itemIcon = LayoutData::getItemIcon(sid);
	itemIcon->setPosition(ccp(itemSize.width/2, itemSize.height/2));
	itemBtn->addChild(itemIcon);

	CCMenuItemImage *openBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdFuLiOpen");
	openBtn->setTag(index + 1);
	openBtn->setTarget(this, menu_selector(GuildBuildingFuli::onOpen));
	menu->addChild(openBtn);

	CCMenuItemImage *rewardBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdFuLiReward");
	rewardBtn->setTag(index + 1);
	rewardBtn->setTarget(this, menu_selector(GuildBuildingFuli::onReward));
	menu->addChild(rewardBtn);

	return ret;
}

void GuildBuildingFuli::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::MSG_FINISH)
	{
		const std::string &source = CPEventHelper::getEventSource();
		if (source == "HandleMessageGuildWelfareStatusResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
			   mStatus = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			   refreshState();
			}
		}
		else if (source == "HandleMessageGuildOpenWelfareResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
				int welfare_id = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				mStatus |= (1 << welfare_id);
				refreshState();
			}
		} 
		else if (source == "HandleMessageGuildGetWelfareResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{

			}
		}
		
	}
}

/////////GuildBuildingShangDian////////////////////////////////////////////////
GuildBuildingShangDian::GuildBuildingShangDian()
	:mFirstPageBtn(NULL)
	,mLastPageBtn(NULL)
	,mPrePageBtn(NULL)
	,mNextPageBtn(NULL)
	,mItemList(NULL)
	,mPageLabel(NULL)
	,mStateLayer(NULL)
	,mCurrentPage(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

GuildBuildingShangDian::~GuildBuildingShangDian()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool GuildBuildingShangDian::init()
{
	if (!MidScreenPanel::init())
	{
		return false;
	}
	mCurrentPage = getFirstPage();

	initUI();
	refereshList();
	refreshButtons();
	refreshState();

	return true;
}

void GuildBuildingShangDian::initUI()
{
	// title
	CCLabelTTF *titleLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShangDianTitle");
	addChild(titleLabel);

	// board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::GUILD, "bdShangDianBoard");
	addChild(board);

	// list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUILD, "bdShangDianList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::GUILD, "bdShangDianItem");
	const int perLine = LayoutData::getInt(CPModuleName::GUILD, "bdShangDianPerLine");
	mItemList = CPItemComponents::create(listSize, new CPLayoutGrid(perLine, itemSize, true));
	mItemList->setClickSensitive(true);
	mItemList->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdShangDianList"));
	addChild(mItemList);

	// page label
	mPageLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShangDianPage");
	addChild(mPageLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	mFirstPageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdShangDianFirstPage");
	mFirstPageBtn->setTarget(this, menu_selector(GuildBuildingShangDian::onFirstPage));
	menu->addChild(mFirstPageBtn);

	mLastPageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdShangDianLastPage");
	mLastPageBtn->setTarget(this, menu_selector(GuildBuildingShangDian::onLastPage));
	menu->addChild(mLastPageBtn);

	mPrePageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdShangDianPrePage");
	mPrePageBtn->setTarget(this, menu_selector(GuildBuildingShangDian::onPrePage));
	menu->addChild(mPrePageBtn);

	mNextPageBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "bdShangDianNextPage");
	mNextPageBtn->setTarget(this, menu_selector(GuildBuildingShangDian::onNextPage));
	menu->addChild(mNextPageBtn);

	// state layer
	mStateLayer = CCLayer::create();
	addChild(mStateLayer);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void GuildBuildingShangDian::refereshList()
{
	mItemList->removeAllItems();

	const int perPage = LayoutData::getInt(CPModuleName::GUILD, "bdShangDianPerPage");
	for (int i = 0; i < perPage; i++)
	{
		CCMenuItem *item = getListItem(i + perPage * (mCurrentPage - 1));
		item->setTarget(this, menu_selector(GuildBuildingShangDian::onList));
		mItemList->addItem(item);
	}

	// page label
	const std::string &pageStr = StringUtils::toString(mCurrentPage) + "/" + StringUtils::toString(getLastPage());
	mPageLabel->setString(pageStr.c_str());
}

void GuildBuildingShangDian::refreshButtons()
{
	mFirstPageBtn->setEnabled(true);
	mLastPageBtn->setEnabled(true);
	mPrePageBtn->setEnabled(true);
	mNextPageBtn->setEnabled(true);
	if (mCurrentPage == getFirstPage())
	{
		mFirstPageBtn->setEnabled(false);
		mPrePageBtn->setEnabled(false);
	}
	else if (mCurrentPage == getLastPage())
	{
		mLastPageBtn->setEnabled(false);
		mNextPageBtn->setEnabled(false);
	}
}

void GuildBuildingShangDian::refreshState()
{
	mStateLayer->removeAllChildren();

	CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShangDianState");
	mStateLayer->addChild(label);

	const std::string &str = label->getString() + StringUtils::toString(HeroData::getProp(Entity::attr_guild_contribution));
	label->setString(str.c_str());
}

void GuildBuildingShangDian::onItem( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int sid = node->getTag();
		if (sid > 0)
		{
			ItemTooltip *tips = ItemTooltip::create();
			tips->setTooltipContentbysid(sid);
			tips->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdShangDianTips"));
			addChild(tips);
		}
	}
}

void GuildBuildingShangDian::onList( CCObject *target )
{
	int sid = 0, price = 0, needLevel = 0;
	StaticData::getGuildShopItemData(getCurrentIndex() + 1, sid, price, needLevel);
	const int myContribution = HeroData::getProp(Entity::attr_guild_contribution);
	if (myContribution <= 0 ||
		price > myContribution)
	{
		CPEventHelper::uiNotify("GuildBuildingShangDian", "", Error::err_guild_shop_notenough_contribution);
		return;
	}
	NumberBoard *panel = NumberBoard::create(1, myContribution/price, price);
	panel->setHandler(this, numberpanel_selector(GuildBuildingShangDian::onBuyItem));
	panel->setPosition(LayoutData::getPoint(CPModuleName::GUILD, "bdShangDianNumberBoard"));
	addChild(panel);
}

void GuildBuildingShangDian::onFirstPage( CCObject *target )
{
	mCurrentPage = getFirstPage();
	refereshList();
	refreshButtons();
}

void GuildBuildingShangDian::onLastPage( CCObject *target )
{
	mCurrentPage = getLastPage();
	refereshList();
	refreshButtons();
}

void GuildBuildingShangDian::onPrePage( CCObject *target )
{
	mCurrentPage--;
	const int firstPage = getFirstPage();
	if (mCurrentPage < firstPage)
	{
		mCurrentPage = firstPage;
	}
	refereshList();
	refreshButtons();
}

void GuildBuildingShangDian::onNextPage( CCObject *target )
{
	mCurrentPage++;
	const int lastPage = getLastPage();
	if (mCurrentPage > lastPage)
	{
		mCurrentPage = lastPage;
	}
	refereshList();
	refreshButtons();
}

CCMenuItem * GuildBuildingShangDian::getListItem( int index )
{
	CCMenuItemImage *ret = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdShangDianItem");
	ret->setEnabled(false);

	int itemCount = 0;
	StaticData::getGuildShopItemCount(itemCount);
	if (index < itemCount)
	{
		int sid = 0, price = 0, needLevel = 0;
		StaticData::getGuildShopItemData(index + 1, sid, price, needLevel);
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		ret->addChild(menu);

		CCMenuItemImage *iconBtn = LayoutData::getMenuItemImg(CPModuleName::GUILD, "bdShangDianItemIcon");
		iconBtn->setTarget(this, menu_selector(GuildBuildingShangDian::onItem));
		menu->addChild(iconBtn, 0, sid);

		const CCSize &iconSize = iconBtn->getContentSize();
		CCSprite *icon = LayoutData::getItemIcon(sid);
		icon->setPosition(ccp(iconSize.width/2, iconSize.height/2));
		iconBtn->addChild(icon);

		// name
		std::string nameStr;
		StaticData::getItemName(sid, nameStr);
		CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShangDianItemName");
		nameLabel->setString(nameStr.c_str());
		ret->addChild(nameLabel);

		// cost
		const int level = GuildData::getGuildProp(GuildType::guild_building_shang_dian_level);
		if (level >= needLevel)
		{
			ret->setEnabled(true);

			CCLabelTTF *costLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShangDianCost");
			ret->addChild(costLabel);

			const std::string &costStr = StringUtils::toString(price) + costLabel->getString();
			costLabel->setString(costStr.c_str());
		}
		else
		{
			CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdShangDianLevelNote");
			ret->addChild(noteLabel);

			const std::string &noteStr = noteLabel->getString() + StringUtils::toString(needLevel);
			noteLabel->setString(noteStr.c_str());
		}
		
	}
	return ret;
}

int GuildBuildingShangDian::getFirstPage() const
{
	return 1;
}

int GuildBuildingShangDian::getLastPage() const
{
	int itemCount = 0;
	StaticData::getGuildShopItemCount(itemCount);
	int perPage = LayoutData::getInt(CPModuleName::GUILD, "bdShangDianPerPage");
	if (perPage <= 0)
	{
		perPage = 9;
	}
	return (itemCount + perPage - 1)/perPage;
}

int GuildBuildingShangDian::getCurrentIndex() const
{
	const int perPage = LayoutData::getInt(CPModuleName::GUILD, "bdShangDianPerPage");
	return mItemList->getCurrentIndex() + perPage * (mCurrentPage - 1);
}

void GuildBuildingShangDian::onBuyItem( int count )
{
	if (count > 0)
	{
		int sid = 0, price = 0, needLevel = 0;
		StaticData::getGuildShopItemData(getCurrentIndex() + 1, sid, price, needLevel);
		if (sid > 0)
		{
			mChecker->start();
			MsgGuildShopItemBuyRequest *msg = new MsgGuildShopItemBuyRequest;
			msg->sid = sid;
			msg->cnt = count;
			HandleMessage::sendMessage(msg);
		}
	}
}

void GuildBuildingShangDian::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageGuildShopItemBuyResponse")
		{
			mChecker->stop();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (type == Entity::attr_guild_contribution)
			{
				refreshState();
			}
		}
	}
}
