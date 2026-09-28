#include "GuidePanel.h"
#include "GuideModule.h"
#include "UserDataModule.h"
#include "ModuleData.h"
#include "QuestDefinition.h"
#include "EntityDefinition.h"
#include "PlatformDefinition.h"
#include "Event.h"

#include "scene/NotificationHelper.h"
#include "scene/panel/functionPanel/ItemTooltip.h"

#include "controls/CPNodeHelper.h"
#include "controls/CPRichText.h"

#include "logic/ItemOperator.h"
#include "logic/platform/IPlatform.h"

#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"
#include "userdata/TaskData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/StaticData.h"
#include "userdata/SceneData.h"
#include "userdata/NPCFunctionData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/FuncData.h"
#include "userdata/SystemData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "utils/RichTextUtils.h"
#include "userdata/IconTipsData.h"
#include "controls/CPItemComponents.h"
#include "userdata/luadata/LuaData.h"


#define GUIDE_TOUCH_PRIORITY  2 * kCCMenuHandlerPriority
#define GUIDE_TIME_OUT  8

namespace GuideType
{
	enum
	{
		null = 0,

		welcome = 1,
		to_npc = 2,
		stop_auto_move = 3,

		arrow_black = 10,
		arrow_black_with_move_item = 11,
		arrow_normal = 20,
		arrow_normal_time = 30,
	};
}

namespace GuideArrow
{
	enum
	{
		dir_up = 0,
		dir_left = 1,
		dir_down = 2,
		dir_right = 3,
	};
}

static void guideNotify( const std::string &source, const std::string &target, const std::string &data )
{
	CPEventHelper::setEventStringData(CPEventName::LGC_GUIDE, CPEventData::VALUE_1, data);
	CPEventHelper::dispatcher(CPEventName::LGC_GUIDE, source, target);
}

static int getGuideType()
{
	int ret = GuideType::null;
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::GUIDE_TYPE, ret);
	return ret;
}

static int getGuideQuest()
{
	const IDVector &quests = TaskData::getAccessTasks();
	if (!quests.empty())
	{
		return quests[0];
	}
	return 0;
}

static CCRect getFunctionArea()
{
	int x = 0, y = 0, w = 0, h = 0;
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::FUNCTION_AREA_X, x);
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::FUNCTION_AREA_Y, y);
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::FUNCTION_AREA_W, w);
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::FUNCTION_AREA_H, h);
	return CCRectMake(x, y, w, h);
}

static int getArrowDirection()
{
	int ret = GuideArrow::dir_up;
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::ARROW_DIRECTION, ret);
	return ret;
}

static CCSize getArrowBoardSize()
{
	int w = 0, h = 0;
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::ARROW_BOARD_W, w);
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::ARROW_BOARD_H, h);
	return CCSizeMake(w, h);
}

static std::string getArrowNote()
{
	std::string ret;
	ModuleData::getString(CPModuleName::GUIDE, CPGuideData::ARROW_NOTE, ret);
	return ret;
}

static CCPoint getArrowPosition()
{
	int x = 0, y = 0;
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::ARROW_BOARD_X, x);
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::ARROW_BOARD_Y, y);
	return ccp(x, y);
}

static void getGuideExData( int &data1, int &data2, int &data3 )
{
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::VALUE_1, data1);
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::VALUE_2, data2);
	ModuleData::getInt(CPModuleName::GUIDE, CPGuideData::VALUE_3, data3);
}

static void getGuideExData( std::string &data1, std::string &data2, std::string &data3 )
{
	ModuleData::getString(CPModuleName::GUIDE, CPGuideData::VALUE_1, data1);
	ModuleData::getString(CPModuleName::GUIDE, CPGuideData::VALUE_2, data2);
	ModuleData::getString(CPModuleName::GUIDE, CPGuideData::VALUE_3, data3);
}

static CCNode *getArrowNode()
{
	const int direction = getArrowDirection();
	const CCSize &size = getArrowBoardSize();
	const CCPoint &pos = getArrowPosition();
	const std::string &note = getArrowNote();

	const int angle = -direction * 90;
	CCNode *ret = LayoutData::getScale9Sprite(CPModuleName::GUIDE, "arrowBoard");
	ret->setRotation(angle);
	ret->setPosition(pos);

	CCSprite *arrow = LayoutData::getSprite(CPModuleName::GUIDE, "arrow");
	ret->addChild(arrow);

	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::GUIDE, "note");
	noteLabel->setString(note.c_str());
	noteLabel->setRotation(-angle);
	ret->addChild(noteLabel);

	const float dt = 0.7f;
	const int ds = 10;
	if (direction == GuideArrow::dir_up ||
		direction == GuideArrow::dir_down)
	{
		ret->setContentSize(size);
		arrow->setPositionX(size.width/2);
		arrow->setPositionY(arrow->getPositionY() + size.height);
		noteLabel->setPosition(ccp(size.width/2, size.height/2));

		CCMoveBy *mb1 = CCMoveBy::create(dt, ccp(0, ds));
		CCMoveBy *mb2 = CCMoveBy::create(dt, ccp(0, -ds));
		CCAction *action = CCRepeatForever::create(CCSequence::create(mb1, mb2, NULL));
		ret->runAction(action);
	}
	else
	{
		ret->setContentSize(CCSizeMake(size.height, size.width));
		arrow->setPositionX(size.height/2);
		arrow->setPositionY(arrow->getPositionY() + size.width);
		noteLabel->setPosition(ccp(size.height/2, size.width/2));

		CCMoveBy *mb1 = CCMoveBy::create(dt, ccp(ds, 0));
		CCMoveBy *mb2 = CCMoveBy::create(dt, ccp(-ds, 0));
		CCAction *action = CCRepeatForever::create(CCSequence::create(mb1, mb2, NULL));
		ret->runAction(action);
	}

	return ret;
}

static CCNode *getBlackLayer()
{
	const CCRect &whiteArea = getFunctionArea();
	CCClippingNode *clippingNode = CPNodeHelper::getClippingNode(whiteArea.size);
	clippingNode->setInverted(true);
	clippingNode->setPosition(whiteArea.origin);

	CCLayerColor *blackLayer = CCLayerColor::create(ccc4(0, 0, 0, 0));
	blackLayer->setPosition(ccp(-whiteArea.getMinX(), -whiteArea.getMinY()));
	clippingNode->addChild(blackLayer);

	blackLayer->runAction(CCFadeTo::create(0.3f, 150));

	return clippingNode;
}

static CCNode *getSkipItem(CCNode *panel)
{
	CCMenu *pTopList = CCMenu::create();
	pTopList->setPosition(CCPointZero);

	CCMenuItemImage* pItem=LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "skip");
	pItem->setTarget(panel, menu_selector(GuidePanel::skipCallBack));
	pTopList->addChild(pItem);
	
	pTopList->setTouchPriority(GUIDE_TOUCH_PRIORITY);

	pItem->runAction(CCFadeTo::create(0.3f, 150));

	return pTopList;
}

////////GuidePanel////////////////////////////////////////////////
GuidePanel::GuidePanel()
	:mSubLayer(NULL)
	,mHasBlackGuide(false)
{
	CPEvtDispatcher.addEventListener(CPEventName::LGC_GUIDE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_OPEN, this);
}

GuidePanel::~GuidePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_GUIDE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_OPEN, this);
}

void GuidePanel::skipCallBack( CCObject *pSender )
{
	hide();
}

bool GuidePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	resetArea();

	mSubLayer = CCLayer::create();
	addChild(mSubLayer);

	return true;
}

void GuidePanel::onEnter()
{
	CCLayer::onEnter();
}

void GuidePanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this, GUIDE_TOUCH_PRIORITY, true);
}

bool GuidePanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pEvent);
	if (mSubLayer->getChildrenCount() == 0)
	{
		return false;
	}

	const CCPoint &touchPt = convertTouchToNodeSpace(pTouch);
	if (mFunctionArea.containsPoint(touchPt))
	{
		unschedule(schedule_selector(GuidePanel::onTimeOut));
		guideNotify("GuidePanel::ccTouchBegan", "", "Yes");
		return false;
	}
	guideNotify("GuidePanel::ccTouchBegan", "", "No");
	if (mHasBlackGuide)
	{
		return true;
	}
	return false;
}

void GuidePanel::show()
{
	mSubLayer->removeAllChildren();

	mHasBlackGuide = false;
	mFunctionArea = getFunctionArea();
	const int guideType = getGuideType();
	switch (guideType)
	{
	case GuideType::welcome:
		{
			mHasBlackGuide = true;
			CCLayer *layer = GuideWelcomeLayer::create();
			mSubLayer->addChild(layer);
			break;
		}
	case GuideType::stop_auto_move:
		{
			GameRole* myRole = GameData::getMyRole();
			if (myRole) myRole->stopAutoMoving();
			break;
		}
	case GuideType::to_npc:
		{
			NPCFunctionData::dealwithQuest(getGuideQuest());
			break;
		}
	case GuideType::arrow_black:
		{
			mHasBlackGuide = true;
			mSubLayer->addChild(getBlackLayer());
			mSubLayer->addChild(getArrowNode());
			mSubLayer->addChild(getSkipItem(this));
			break;
		}
	case  GuideType::arrow_black_with_move_item:
		{
			mHasBlackGuide = true;
			mSubLayer->addChild(getBlackLayer());
			mSubLayer->addChild(getArrowNode());
			mSubLayer->addChild(getSkipItem(this));

			int data1 = 0, data2 = 0, itemSID = 0;
			getGuideExData(data1, data2, itemSID);
			if (itemSID > 0)
			{
				ItemOperator::swapPositionBySid(itemSID);
			}
			break;
		}
	case GuideType::arrow_normal:
		{
			mSubLayer->addChild(getArrowNode());
			break;
		}
	case GuideType::arrow_normal_time:
		{
			mSubLayer->addChild(getArrowNode());
			startTimer();
			break;
		}
	}
}

void GuidePanel::hide()
{
	mSubLayer->removeAllChildren();
	mHasBlackGuide = false;
	resetArea();
}

void GuidePanel::resetArea()
{
	const CCSize &size = CCDirector::sharedDirector()->getWinSize();
	mFunctionArea = CCRectMake(0, 0, size.width, size.height);
}

void GuidePanel::startTimer()
{
	unschedule(schedule_selector(GuidePanel::onTimeOut));
	schedule(schedule_selector(GuidePanel::onTimeOut), GUIDE_TIME_OUT);
}

void GuidePanel::onTimeOut( float dt )
{
	guideNotify("GuidePanel::onTimeOut", "", "");
}

void GuidePanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	const std::string &target = CPEventHelper::getEventTarget();
	if (eventName == CPEventName::LGC_GUIDE)
	{
		if (target == "GuidePanel")
		{
			const std::string &data = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
			if (data == "show")
			{
				show();
			}
			else
			{
				hide();
			}
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageQuestUpdate")
		{
			if (SceneData::hasEnterScene())
			{
				if (!mHasBlackGuide)
				{
					const int opcode = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
					if (opcode != Opcode::Op_Quest_Remove)
					{
						const int qid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
						const int line = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
						if (line==Quest::line_Main)
						{
							NPCFunctionData::hideNPCTalkPanel();
							NPCFunctionData::dealwithQuest(qid);
						}
					}
				}
			}
		}
	}
	else if (eventName == CPEventName::UI_OPEN)
	{
		if (source == "NewFunctionPanel::onShowNext")
		{
			mHasBlackGuide = false;
		}
// 		else if (source == "guide:showNewFuncPre")
// 		{
// 			mHasBlackGuide = true;
// 		}
	}
}

///////////GuideWelcomeLayer////////////////////////////////////////////
GuideWelcomeLayer::GuideWelcomeLayer()
{
	
}

GuideWelcomeLayer::~GuideWelcomeLayer()
{

}

bool GuideWelcomeLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	UserData::saveData();
	initUI();

	return true;
}

void GuideWelcomeLayer::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool GuideWelcomeLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pTouch);
	CC_UNUSED_PARAM(pEvent);
	return true;
}

void GuideWelcomeLayer::initUI()
{
	CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 0));
	layer->runAction(CCFadeTo::create(0.3f, 150));
	addChild(layer);

	CCSprite *board = LayoutData::getSpriteByFile(CPModuleName::GUIDE, "welcome");
	addChild(board);

	CCSprite *logo = LayoutData::getSprite(CPModuleName::GUIDE, "logo");
	const CCPoint pt = logo->getPosition();
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::_35i_another
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::wdj_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::qihoo_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::duoku_jianzhixuanyuan
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::mi_jianzhixuanyuan)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoJianZhiXuanYuan");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::jvyou
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shouyougu_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::kugou_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::vivo_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::coolpay_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::lenovo_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::qixiazi_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::youlong_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::lingqisan_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::uc_lieyanzhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::huawei_lieyanzhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoLieYanZhanShen");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::muzhiwan_rexuetulong
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shouyougu_ruanyou)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoReXueTuLong");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::sijiuyou_xueren)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoXueRen");
	}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_chuanqizhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoChuanQiZhanShen");
	}else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_yingxiongchuanqi)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoYingXiongChuanQi");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shoumeng_chiyanzhanshen)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoChiYanZhanShen");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::shoumeng_lieyanfentian)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoLieYanFenTian");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_shachengchuanqi)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoShaChengChuanQi");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::youmi_menghuishacheng)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoMengHuiShaCheng");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::youmi_jinglongzhuan)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoJingLongZhuan");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::aboluo_rexuetianya)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoReXueTianYa");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::fivegame_damodaoge)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoDaMoDaoGe");
	}
	else if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::yayawan_badao)
	{
		logo = LayoutData::getSpriteByFile(CPModuleName::COMMON, "logoBaDao");
	}
	logo->setPosition(pt);
	logo->setScale(0.6f);
	addChild(logo);

	CCMenuItemImage *beginBtn = LayoutData::getMenuItemImg(CPModuleName::GUIDE, "welcome");
	addChild(beginBtn);
}

/////////BaseNotePanel////////////////////////////////////////////////
BaseNotePanel::BaseNotePanel()
	:mBoard(NULL)
	,mTitleLabel(NULL)
	,mDescLabel(NULL)
	,mHandler(NULL)
	,mHandleFunc(NULL)
	,mIsBig(false)
{

}

BaseNotePanel::~BaseNotePanel()
{

}

BaseNotePanel * BaseNotePanel::create()
{
	return create(false);
}

BaseNotePanel * BaseNotePanel::create( bool isBig )
{
	BaseNotePanel *ret = new BaseNotePanel;
	if (ret && ret->init(isBig))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool BaseNotePanel::init()
{
	return init(false);
}

bool BaseNotePanel::init(bool isBig)
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	mIsBig = isBig;

	initUI();
	
	return true;
}

void BaseNotePanel::initUI()
{
	if (mIsBig)
	{
		mBoard = LayoutData::getSprite(CPModuleName::COMMON, "noteBigPanelBoard");
		addChild(mBoard);

		CCScale9Sprite *boardIn = LayoutData::getScale9Sprite(CPModuleName::COMMON, "noteBigPanelBoardIn");
		addChild(boardIn);

		mTitleLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "noteBigPanelTitle");
		addChild(mTitleLabel);

		mDescLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "noteBigPanelDesc");
		addChild(mDescLabel);
	}
	else
	{
		mBoard = LayoutData::getSprite(CPModuleName::COMMON, "notePanelBoard");
		addChild(mBoard);

		mTitleLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "notePanelTitle");
		addChild(mTitleLabel);

		mDescLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "notePanelDesc");
		addChild(mDescLabel);

		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		addChild(menu);

		CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "notePanelClose");
		closeBtn->setTarget(this, menu_selector(BaseNotePanel::onClose));
		menu->addChild(closeBtn);
	}
}

void BaseNotePanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool BaseNotePanel::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pEvent);
	const CCPoint &pt = mBoard->convertTouchToNodeSpace(pTouch);
	const CCSize &size = mBoard->getContentSize();
	const CCRect &rect = CCRectMake(0, 0, size.width, size.height);
	const bool inArea = rect.containsPoint(pt);
	if (!inArea && mIsBig)
	{
		close();
	}
	return inArea;
}

void BaseNotePanel::setTitle( const std::string &title )
{
	mTitleLabel->setString(title.c_str());
}

void BaseNotePanel::setDesc( const std::string &desc )
{
	mDescLabel->setString(desc.c_str());
}

void BaseNotePanel::setCloseHandler( CCObject *handler, SEL_CallFunc func )
{
	mHandler = handler;
	mHandleFunc = func;
}

void BaseNotePanel::close()
{
	if (mHandler && mHandleFunc)
	{
		(mHandler->*mHandleFunc)();
	}
	removeFromParent();
}

void BaseNotePanel::onClose( CCObject *target )
{
	close();
}


///////NewEquipLayer/////////////////////////////////////////////////////
NewEquipPanel::NewEquipPanel()
	:mItemSID(0)
{

}

NewEquipPanel::~NewEquipPanel()
{

}

bool NewEquipPanel::init()//装备更新ui
{
	if (!BaseNotePanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	int itemID = 0, data3 = 0;
	getGuideExData(mItemSID, itemID, data3);
	if (!ItemOperator::checkItemBetter(itemID))
	{
		return false;
	}

	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->stopAutoMoving();

	initUI();
	
	return true;
}

void NewEquipPanel::initUI()
{
	setTitle(LayoutData::getString(CPModuleName::GUIDE, "newEquipTitle"));
	setDesc(LayoutData::getString(CPModuleName::GUIDE, "newEquipDesc"));

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid1");
	itemBtn->setTarget(this, menu_selector(NewEquipPanel::onItem));
	itemBtn->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newItem"));
	menu->addChild(itemBtn);

	CCSprite *icon = LayoutData::getItemIcon(mItemSID);
	if (icon)
	{
		const CCSize &size = itemBtn->getContentSize();
		icon->setPosition(ccp(size.width/2, size.height/2));
		itemBtn->addChild(icon);
	}
	
	CCMenuItemImage *equipBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "equipNow");
	equipBtn->setTarget(this, menu_selector(NewEquipPanel::onEquip));
	menu->addChild(equipBtn);
}

void NewEquipPanel::onItem( CCObject *target )
{
	CCNode* pNode = dynamic_cast<CCNode*>(target);
	const CCPoint &tipsPt = LayoutData::getPoint(CPModuleName::GUIDE, "newItemTips");
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(mItemSID);
	tips->setPosition(ccp(tipsPt.x, tipsPt.y - tips->getContentSize().height+pNode->getContentSize().height));
	NotificationHelper::addNode(tips);
}

void NewEquipPanel::onEquip( CCObject *target )
{
	ItemOperator::useItemBySID(mItemSID);
	CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "NewEquipPanel::close", "");
	close();
}

////////NewSkillPanel////////////////////////////////////////////////
NewSkillPanel::NewSkillPanel()
	:mItemSID(0)
{

}

NewSkillPanel::~NewSkillPanel()
{

}

bool NewSkillPanel::init()//有新学技能ui
{
	if (!BaseNotePanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	int data2 = 0, data3 = 0;
	getGuideExData(mItemSID, data2, data3);

	int skillID = 0, datay = 0;
	StaticData::getItemDataEx(mItemSID, skillID, datay);
	GameRole* myRole = GameData::getMyRole();
	if (!myRole)
	{
		return false;
	}
	if (myRole->isSkillLearned(skillID, datay) &&
		skillID <= datay)
	{
		return false;
	}

	myRole->stopAutoMoving();
	initUI();

	return true;
}

void NewSkillPanel::initUI()
{
	setTitle(LayoutData::getString(CPModuleName::GUIDE, "newSkillTitle"));
	setDesc(LayoutData::getString(CPModuleName::GUIDE, "newSkillDesc"));

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid1");
	itemBtn->setTarget(this, menu_selector(NewSkillPanel::onItem));
	itemBtn->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newItem"));
	menu->addChild(itemBtn);

	CCSprite *icon = LayoutData::getItemIcon(mItemSID);
	if (icon)
	{
		const CCSize &size = itemBtn->getContentSize();
		icon->setPosition(ccp(size.width/2, size.height/2));
		itemBtn->addChild(icon);
	}

	CCMenuItemImage *learnBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "leanNow");
	learnBtn->setTarget(this, menu_selector(NewSkillPanel::onLearn));
	menu->addChild(learnBtn);
}

void NewSkillPanel::onItem( CCObject *target )
{
	const CCPoint &tipsPt = LayoutData::getPoint(CPModuleName::GUIDE, "newItemTips");
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(mItemSID);
	tips->setPosition(ccp(tipsPt.x, tipsPt.y - tips->getContentSize().height));
	NotificationHelper::addNode(tips);
}

void NewSkillPanel::onLearn( CCObject *target )
{
	ItemOperator::useItemBySID(mItemSID);
	CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "NewSkillPanel::close", "");
	close();
}

////////NewFunctionPanel///////////////////////////////////////////////
NewFunctionPanel::NewFunctionPanel()
	:mNextFunctionLayer(NULL)
{

}

NewFunctionPanel::~NewFunctionPanel()
{

}

bool NewFunctionPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	setZOrder(10);
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->stopAutoMoving();

	string data2, data3;
	getGuideExData(mFuncName, data2, data3);

	initUI();

	return true;
}

void NewFunctionPanel::initUI()
{
	CCLayer *newFunctionLayer = CCLayer::create();
	addChild(newFunctionLayer);

	CCSprite *board = LayoutData::getSprite(CPModuleName::GUIDE, "newFunction");
	newFunctionLayer->addChild(board);

	std::string key = "icon_" + mFuncName;
	CCSprite *iconA = LayoutData::getSpriteByFile(CPModuleName::GUIDE, key);
	if (iconA)
	{
		iconA->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newFunctionIcon"));
		newFunctionLayer->addChild(iconA);
	}

	key = "icon_sel_" + mFuncName;
	CCSprite *iconB = LayoutData::getSpriteByFile(CPModuleName::GUIDE, key);
	if (iconB)
	{
		iconB->setPosition(iconA->getPosition());
		newFunctionLayer->addChild(iconB);
		iconB->runAction(CCRepeatForever::create(
			CCSequence::create(
			CCFadeOut::create(0.3f),
			CCFadeIn::create(0.3f),
			NULL)));
	}
	
	CCDelayTime *dl = CCDelayTime::create(2.5f);
	CCHide *hd = CCHide::create();
	CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(NewFunctionPanel::onShowNext));
	CCAction *action = CCSequence::create(dl, hd, func, NULL);
	newFunctionLayer->runAction(action);

	// next
	std::string nextFuncName;
	StaticData::getNextOpenFunction(mFuncName, nextFuncName);
	if (!nextFuncName.empty())
	{
		mNextFunctionLayer = BaseNotePanel::create(true);
		mNextFunctionLayer->setVisible(false);
		mNextFunctionLayer->setTitle(LayoutData::getString(CPModuleName::GUIDE, "nextFunctionTitle"));
		mNextFunctionLayer->setDesc(LayoutData::getString(CPModuleName::GUIDE, "nextFunctionDesc"));
		mNextFunctionLayer->setCloseHandler(this, callfunc_selector(NewFunctionPanel::close));
		addChild(mNextFunctionLayer);

		// board
		CCScale9Sprite *border = LayoutData::getScale9Sprite(CPModuleName::GUIDE, "newFunctionBorder");
		CCSprite *boardNext = LayoutData::getSpriteByFile(CPModuleName::GUIDE, nextFuncName);
		if (boardNext)
		{
			boardNext->setPosition(border->getPosition());
			mNextFunctionLayer->addChild(boardNext);
			mNextFunctionLayer->addChild(border);
		}

		// detail
		const std::string &desc = LayoutData::getString(CPModuleName::GUIDE, nextFuncName);
		const int fontSize = LayoutData::getInt(CPModuleName::GUIDE, "nextFunctionDetailFontSize");
		const CCSize &descSize = LayoutData::getSize(CPModuleName::GUIDE, "nextFunctionDetail");
		CPRichText *descText = RichTextUtils::getRichText(desc, fontSize, descSize.width, descSize.height);
		descText->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "nextFunctionDetail"));
		mNextFunctionLayer->addChild(descText);

		//
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		mNextFunctionLayer->addChild(menu);

		CCMenuItemImage *confirmBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "confirm");
		confirmBtn->setTarget(this, menu_selector(NewFunctionPanel::onConfirm));
		menu->addChild(confirmBtn);
	}
}

void NewFunctionPanel::onShowNext()
{
	if (mNextFunctionLayer)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->stopAutoMoving();

		mNextFunctionLayer->setVisible(true);
		CPEventHelper::dispatcher(CPEventName::UI_OPEN, "NewFunctionPanel::onShowNext", "");
	}
	else
	{
		close();
	}
}

void NewFunctionPanel::onConfirm( CCObject *target )
{
	close();
}

void NewFunctionPanel::close()
{
	CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "NewFunctionPanel::close", "");
	removeFromParent();
}

//////////NewGiftPanel/////////////////////////////////////////////////////
NewGiftPanel::NewGiftPanel()
	:mItemSID(0)
{

}

NewGiftPanel::~NewGiftPanel()
{

}

bool NewGiftPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	int data2 = 0, data3 = 0;
	getGuideExData(mItemSID, data2, data3);

	initUI();

	return true;
}

void NewGiftPanel::initUI()
{
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCSprite *icon = LayoutData::getItemIcon(mItemSID);
	const CCSize &size = icon->getContentSize();
	icon->setPosition(ccp(size.width/2, size.height/2));

	CCMenuItem *giftBtn = CCMenuItem::create();
	giftBtn->setTarget(this, menu_selector(NewGiftPanel::onOpen));
	giftBtn->setContentSize(size);
	giftBtn->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newGift"));
	giftBtn->addChild(icon);
	menu->addChild(giftBtn);

	CCDelayTime *dl = CCDelayTime::create(20.0f);
	CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(NewGiftPanel::close));
	CCAction *action = CCSequence::create(dl, func, NULL);
	runAction(action);
}

void NewGiftPanel::onOpen( CCObject *target )
{
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->stopAutoMoving();
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		node->setVisible(false);
	}
	stopAllActions();

	BaseNotePanel *layer = BaseNotePanel::create();
	layer->setTitle(LayoutData::getString(CPModuleName::GUIDE, "newGiftTitle"));
	layer->setDesc(LayoutData::getString(CPModuleName::GUIDE, "newGiftDesc"));
	layer->setCloseHandler(this, callfunc_selector(NewGiftPanel::close));
	addChild(layer);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	layer->addChild(menu);

	const int cnt = 1;
	for (int i = 0; i < cnt; i++)
	{
		CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid1");
		itemBtn->setTarget(this, menu_selector(NewGiftPanel::onItem));
		itemBtn->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newGift"));
		menu->addChild(itemBtn);

		const CCSize &size = itemBtn->getContentSize();
		CCSprite *icon = LayoutData::getItemIcon(mItemSID);
		icon->setPosition(ccp(size.width/2, size.height/2));
		itemBtn->addChild(icon);
	}

	CCMenuItemImage *getBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "get");
	getBtn->setTarget(this, menu_selector(NewGiftPanel::onGet));
	menu->addChild(getBtn);
}

void NewGiftPanel::onItem( CCObject *target )
{
	const CCPoint &tipsPt = LayoutData::getPoint(CPModuleName::GUIDE, "newItemTips");
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(mItemSID);
	tips->setPosition(ccp(tipsPt.x, tipsPt.y - tips->getContentSize().height));
	NotificationHelper::addNode(tips);
}

void NewGiftPanel::onGet( CCObject *target )
{
	ItemOperator::useItemBySID(mItemSID);
	close();
}

void NewGiftPanel::close()
{
	removeFromParent();
}

////////NewItemUsePanel////////////////////////////////////////////
NewItemUsePanel::NewItemUsePanel()
	:mItemSID(0)
{

}

NewItemUsePanel::~NewItemUsePanel()
{

}

bool NewItemUsePanel::init()//使用物品ui
{
	if (!BaseNotePanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	int itemID = 0, data3 = 0;
	getGuideExData(mItemSID, itemID, data3);
	if (mItemSID <= 0)
	{
		return false;
	}
	
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->stopAutoMoving();

	initUI();

	return true;
}

void NewItemUsePanel::initUI()
{
	setTitle(LayoutData::getString(CPModuleName::GUIDE, "newItemUseTitle"));
	setDesc(LayoutData::getString(CPModuleName::GUIDE, "newItemUseDesc"));

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid1");
	itemBtn->setTarget(this, menu_selector(NewItemUsePanel::onItem));
	itemBtn->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newItem"));
	menu->addChild(itemBtn);

	CCSprite *icon = LayoutData::getItemIcon(mItemSID);
	if (icon)
	{
		const CCSize &size = itemBtn->getContentSize();
		icon->setPosition(ccp(size.width/2, size.height/2));
		itemBtn->addChild(icon);
	}

	CCMenuItemImage *useBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "use");
	useBtn->setTarget(this, menu_selector(NewItemUsePanel::onUse));
	menu->addChild(useBtn);
}

void NewItemUsePanel::onItem( CCObject *target )
{
	const CCPoint &tipsPt = LayoutData::getPoint(CPModuleName::GUIDE, "newItemTips");
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(mItemSID);
	tips->setPosition(ccp(tipsPt.x, tipsPt.y - tips->getContentSize().height));
	NotificationHelper::addNode(tips);
}

void NewItemUsePanel::onUse( CCObject *target )
{
	ItemOperator::useItemBySID(mItemSID);
	close();
}

//-------------------------------------------------------------------------------------------------------------------------------//

SystemGiftPanel::SystemGiftPanel():
	mItemSID(0),
	mData(0)
{

}

SystemGiftPanel::~SystemGiftPanel()
{

}

bool SystemGiftPanel::init()//系统礼包ui
{
	if (!PartPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	int data2 = 0, data3 = 0;
	getGuideExData(mItemSID, mData, data3);
	std::string str2,str3;
	getGuideExData(mString, str2,str3);
	initUI();

	return true;
}

void SystemGiftPanel::initUI()
{
	BaseNotePanel *layer = BaseNotePanel::create();
	layer->setTitle(LayoutData::getString(CPModuleName::GUIDE, "newGiftTitle"));
	layer->setDesc(LayoutData::getString(CPModuleName::GUIDE, "newGiftDesc"));
	layer->setCloseHandler(this, callfunc_selector(SystemGiftPanel::close));
	addChild(layer);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	layer->addChild(menu);

	const int cnt = 1;
	for (int i = 0; i < cnt; i++)
	{
		CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid1");
		//itemBtn->setTarget(this, menu_selector(SystemGiftPanel::onItem));
		itemBtn->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newGift"));
		menu->addChild(itemBtn);

		const CCSize &size = itemBtn->getContentSize();
		CCSprite *icon = SystemData::getSpriteByPlist("icon_forgetreward");
		//CCSprite *icon = LayoutData::getItemIcon(mItemSID);
		icon->setPosition(ccp(size.width/2, size.height/2));
		itemBtn->addChild(icon);
	}

	CCMenuItemImage *getBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "get");
	getBtn->setTarget(this, menu_selector(SystemGiftPanel::onGet));
	menu->addChild(getBtn);

	CCLabelTTF* pLabel = CCLabelTTF::create(mString.c_str(),"",18);
	pLabel->setPosition(ccp(getBtn->getPositionX(),getBtn->getPositionY()+60));
	addChild(pLabel);
}

void SystemGiftPanel::onItem( CCObject *target )
{
	const CCPoint &tipsPt = LayoutData::getPoint(CPModuleName::GUIDE, "newItemTips");
	ItemTooltip *tips = ItemTooltip::create();
	tips->setTooltipContentbysid(mItemSID);
	tips->setPosition(ccp(tipsPt.x, tipsPt.y - tips->getContentSize().height));
	NotificationHelper::addNode(tips);
}

void SystemGiftPanel::onGet( CCObject *target )
{
	//ItemOperator::useItemBySID(mItemSID);

	FuncData::sendFuncMsgWithID(6,mData);
	//FuncData::sendFuncMsg(mData);

	close();
}

void SystemGiftPanel::close()
{
	removeFromParent();
}

//-------------------------------------------------------------------------------------------------------------------------------//

HollowItemPanel::HollowItemPanel():
	mItemIID(0)
{

}

HollowItemPanel::~HollowItemPanel()
{

}

bool HollowItemPanel::init()//物品找回ui
{
	if (!PartPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	int data2 = 0, data3 = 0;
	getGuideExData(data2, mItemIID, data3);
	std::string str2,str3;
	getGuideExData(mString, str2,str3);
	initUI();

	return true;
}

void HollowItemPanel::initUI()
{
	BaseNotePanel *layer = BaseNotePanel::create();
	layer->setTitle(LayoutData::getString(CPModuleName::GUIDE, "hollowTitle"));
	layer->setDesc(LayoutData::getString(CPModuleName::GUIDE, "hollowDesc"));
	layer->setCloseHandler(this, callfunc_selector(HollowItemPanel::close));
	addChild(layer);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	layer->addChild(menu);

	const int cnt = 1;
	for (int i = 0; i < cnt; i++)
	{
		CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid1");
		itemBtn->setTarget(this, menu_selector(HollowItemPanel::onItem));
		itemBtn->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "newGift"));
		menu->addChild(itemBtn);

		const CCSize &size = itemBtn->getContentSize();
		//CCSprite *icon = SystemData::getSpriteByPlist("icon_forgetreward");
		UserItem* pItem = GameData::s_user->getUserItemData()->getItemByIid(mItemIID);
		int mItemSID = 0;
		if (pItem)
		{
			mItemSID = pItem->sid;
		}
		CCSprite *icon = NULL;
		if (mItemSID==0)
		{
			icon = SystemData::getSpriteByPlist("icon_forgetreward");
		}
		else
		{
			icon = 	LayoutData::getItemIcon(mItemSID);
		}
		icon->setPosition(ccp(size.width/2, size.height/2));
		itemBtn->addChild(icon);
	}

	CCMenuItemImage *getBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "get");
	getBtn->setTarget(this, menu_selector(HollowItemPanel::onGet));
	menu->addChild(getBtn);

	CCLabelTTF* pLabel = CCLabelTTF::create(mString.c_str(),"",18);
	pLabel->setPosition(ccp(getBtn->getPositionX(),getBtn->getPositionY()+60));
	addChild(pLabel);
}

void HollowItemPanel::onItem( CCObject *target )
{
	const CCPoint &tipsPt = LayoutData::getPoint(CPModuleName::GUIDE, "newItemTips");
	ItemTooltip *tips = ItemTooltip::create();
	UserItem* pItem = GameData::s_user->getUserItemData()->getItemByIid(mItemIID);
	if (pItem)
	{
		tips->setTooltipContent(pItem);
		tips->setPosition(ccp(tipsPt.x, tipsPt.y - tips->getContentSize().height));
		NotificationHelper::addNode(tips);
	}
}

void HollowItemPanel::onGet( CCObject *target )
{
	//ItemOperator::useItemBySID(mItemSID);

	//FuncData::sendFuncMsg(mItemIID);
	FuncData::sendFuncMsgWithID(8,mItemIID);
	close();
}

void HollowItemPanel::close()
{
	removeFromParent();
}

//////////////////----------------------------------------------MailPanel -----------------------------------------//

MailPanel::MailPanel():
	mData(0)
{

}

MailPanel::~MailPanel()
{

}

bool MailPanel::init()//系统邮件ui
{
	if (!PartPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	int data2 = 0, data3 = 0;
	getGuideExData(mData, data2, data3);
	mTitle = IconTipsData::getMailTitleStr(mData);
	mContent = IconTipsData::getMailContentStr(mData);
	mGift = IconTipsData::getMailGiftStr(mData);
	initUI();

	return true;
}

void MailPanel::initUI()
{
	BaseNotePanel *layer = BaseNotePanel::create();
	layer->setTitle(LayoutData::getString(CPModuleName::GUIDE, "mailTitle"));
	layer->setCloseHandler(this, callfunc_selector(MailPanel::close));
	addChild(layer);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	layer->addChild(menu);

	CCMenuItemImage *getBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "get");
	getBtn->setTarget(this, menu_selector(MailPanel::onGet));
	menu->addChild(getBtn);

	int height = 0;
	CCNode* pLayer = CCNode::create();
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(CCPointZero);

	if (mGift!="")
	{
		height += 20;
		CCMenuItemImage *itemBtn = LayoutData::getMenuItemImg(CPModuleName::COMMON, "bagGrid1");
		itemBtn->setPosition(ccp(LayoutData::getInt(CPModuleName::GUIDE, "maillist")/2,itemBtn->getContentSize().height));
		pLayer->addChild(itemBtn);

		const CCSize &size = itemBtn->getContentSize();
		CCSprite *icon = SystemData::getSpriteByPlist("icon_forgetreward");
		icon->setPosition(ccp(size.width/2, size.height/2));
		itemBtn->addChild(icon);

		height+=itemBtn->getContentSize().height;
	}

	height += 20;
	CCLabelTTF* pContent = CCLabelTTF::create(mContent.c_str(),"",20);
	pContent->setDimensions(CCSizeMake(LayoutData::getInt(CPModuleName::GUIDE, "maillist"),0));
	pContent->setAnchorPoint(CCPointZero);
	pContent->setHorizontalAlignment(kCCTextAlignmentLeft);
	pContent->setPosition(ccp(0,height));
	pLayer->addChild(pContent); 
	height += pContent->getContentSize().height;

	height += 20;
	CCLabelTTF* pTitle = CCLabelTTF::create(mTitle.c_str(),"",20);
	pTitle->setAnchorPoint(CCPointZero);
	pTitle->setPosition(ccp(0,height));
	pLayer->addChild(pTitle);
	height += pTitle->getContentSize().height;

	const CCSize &listSize = LayoutData::getSize(CPModuleName::GUIDE, "maillist");
	CPItemComponents* mList = CPItemComponents::create(listSize, new CPLayoutList());
	mList->setPosition(LayoutData::getPoint(CPModuleName::GUIDE, "maillist"));
	addChild(mList); 

	pLayer->setContentSize(CCSizeMake(LayoutData::getInt(CPModuleName::GUIDE, "maillist"),height));
	mList->addItem(pLayer);
}

void MailPanel::onGet( CCObject *target )
{
	FuncData::sendFuncMsgWithID(17,mData);
	close();
}

void MailPanel::close()
{
	removeFromParent();
}

//--------------------------------------------------------------------------------//

NoticePanel::NoticePanel()
{

}

NoticePanel::~NoticePanel()
{

}

bool NoticePanel::init()//追踪结果ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	mName = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
	mSceneID = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
	mPosx = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
	mPosy = CPEventHelper::getEventIntData(CPEventData::VALUE_5);
	initUI();

	return true;
}

void NoticePanel::initUI()
{
	BaseNotePanel *layer = BaseNotePanel::create();
	layer->setTitle(LayoutData::getString(CPModuleName::GUIDE, "trackTitle"));
	layer->setCloseHandler(this, callfunc_selector(NoticePanel::close));
	addChild(layer);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	layer->addChild(menu);
	
	CCMenuItemImage *getBtn = LayoutData::getMenuItemLabelImage(CPModuleName::GUIDE, "ok");
	getBtn->setTarget(this, menu_selector(NoticePanel::onGet));
	menu->addChild(getBtn);

	CCPoint pos0 = LayoutData::getPoint(CPModuleName::GUIDE,"tracklabel0");

	CCLabelTTF* pLable = CCLabelTTF::create(LayoutData::getString(CPModuleName::GUIDE, "trackTitle0").c_str(),"",20);
	pLable->setAnchorPoint(CCPointZero);
	pLable->setPosition(pos0);
	layer->addChild(pLable);
	CCLabelTTF* pLable_ = CCLabelTTF::create( mName.c_str(),"",20);
	pLable_->setColor(ccYELLOW);
	pLable_->setAnchorPoint(CCPointZero);
	pLable_->setPosition(ccp(pLable->getPositionX() + pLable->getContentSize().width+20,pLable->getPositionY()));
	layer->addChild(pLable_);
	 

	CCPoint pos1 = LayoutData::getPoint(CPModuleName::GUIDE,"tracklabel1");
	std::string scenename = "";
	LuaData::getProp(LuaData::MAP,mSceneID,"name",scenename);
	CCLabelTTF* pLable0 = CCLabelTTF::create( LayoutData::getString(CPModuleName::GUIDE, "trackTitle1").c_str(),"",20);
	pLable0->setAnchorPoint(CCPointZero);
	pLable0->setPosition(pos1);
	layer->addChild(pLable0);
	CCLabelTTF* pLable_0 = CCLabelTTF::create( scenename.c_str(),"",20);
	pLable_0->setColor(ccc3(128,64,0));
	pLable_0->setAnchorPoint(CCPointZero);
	pLable_0->setPosition(ccp(pLable0->getPositionX() + pLable0->getContentSize().width+20,pLable0->getPositionY()));
	layer->addChild(pLable_0);

	CCPoint pos2 = LayoutData::getPoint(CPModuleName::GUIDE,"tracklabel2");
	CCLabelTTF* pLable1 = CCLabelTTF::create(LayoutData::getString(CPModuleName::GUIDE, "trackTitle2").c_str(),"",20);
	pLable1->setAnchorPoint(CCPointZero);
	pLable1->setPosition(pos2);
	layer->addChild(pLable1);
	CCLabelTTF* pLable_1 = CCLabelTTF::create( SystemData::intToString(mPosx).c_str(),"",20);
	pLable_1->setColor(ccGREEN);
	pLable_1->setAnchorPoint(CCPointZero);
	pLable_1->setPosition(ccp(pLable1->getPositionX() + pLable1->getContentSize().width+20,pLable1->getPositionY()));
	layer->addChild(pLable_1);

	CCPoint pos3 = LayoutData::getPoint(CPModuleName::GUIDE,"tracklabel3");
	CCLabelTTF* pLable2 = CCLabelTTF::create(LayoutData::getString(CPModuleName::GUIDE, "trackTitle3").c_str(),"",20);
	pLable2->setAnchorPoint(CCPointZero);
	pLable2->setPosition(pos3);
	layer->addChild(pLable2);
	CCLabelTTF* pLable_2 = CCLabelTTF::create( SystemData::intToString(mPosy).c_str(),"",20);
	pLable_2->setColor(ccGREEN);
	pLable_2->setAnchorPoint(CCPointZero);
	pLable_2->setPosition(ccp(pLable2->getPositionX() + pLable2->getContentSize().width+20,pLable2->getPositionY()));
	layer->addChild(pLable_2);
}

void NoticePanel::onGet( CCObject *target )
{
	GameRole* myRole = GameData::getMyRole();
	if (!myRole) return;
	myRole->startAutoMoveToCrossMap(mSceneID,mPosx,mPosy,GHOST_TYPE_PLAYER);
	CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "NoticePanel::onGet", "");
	close();
}

void NoticePanel::close()
{

	removeFromParent();
}
