#include "GameUI.h"
#include "MsgPlayer.h"
#include "MsgScene.h"
#include "EntityDefinition.h"
#include "SceneDefinition.h"
#include "GameMap.h"
#include "ControlPanel.h"
#include "LoginHelper.h"
#include "SceneFactory.h"
#include "PanelFactory.h"
#include "NotificationModule.h"
#include "CombatDefinition.h"
#include "ModuleData.h"
#include "MainUIModule.h"
#include "UserDataModule.h"
#include "TaskModule.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "UserData/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/LayoutData.h"
#include "userdata/TaskData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/skilldata/SkillEffect.h"
#include "userdata/skilldata/SkillState.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/AutoAttack.h"
#include "userdata/mapdata/PixesMap.h"

#include "userdata/NPCFunctionData.h"
#include "userdata/MineData.h"
#include "userdata/GuildData.h"

#include "ext/GeneralMenu.h"
#include "ext/CCFlashAnimation.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCActionDestroy.h"

#include "controls/CPComboBox.h"
#include "controls/CPNodeHelper.h"

#include "res/AudioLoader.h"
#include "res/CPAnimationManager.h"

#include "utils/StringUtils.h"
#include "utils/TestUtils.h"

#include "MiniChatPanel.h"
#include "Login.h"
#include "SkillLayer.h"
#include "MiniMapLayer.h"
#include "BossLifeBar.h"
#include "scene/panel/LeftTipsPanel.h"
#include "scene/TopActivity.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/HeadPanel.h"
#include "scene/NotificationHelper.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/TradePanel.h"
#include "scene/panel/TargetPanel.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/OperateMenu.h"
#include "scene/panel/team/TeamOperationPanel.h"
#include "scene/panel/ChatPanel.h"
#include "scene/panel/mining/MiningPanel.h"
#include "scene/panel/setting/SystemSetting.h"
#include "scene/panel/functionPanel/BagCellPanel.h"
#include "scene/panel/functionPanel/BuffExPanel.h"
#include "scene/panel/guide/GuideHelper.h"
#include "scene/LowerRightNotificationPanel.h"
#include "scene/panel/ReliveAlertPanel.h"
#include "scene/panel/shop/ShopPanel.h"
#include "scene/panel/functionPanel/PetAttributePanel.h"
#include "scene/panel/activity/PanLongEquipPanel.h"
#include "scene/panel/activity/ItemBindListPanel.h"
#include "scene/SceneManager.h"

#include "panel/BuffPanel.h"
#include "panel/CommandPanel.h"
#include "panel/MainPanel.h"
#include "panel/TaskPanel.h"
#include "panel/NPCPanel.h"
#include "panel/MinMapPanel.h"
#include "panel/functionPanel/CharacterPanel.h"
#include "panel/DogSkillPanel.h"
#include "panel/IconTipPanel.h"
#include "panel/MinePanel.h"
#include "panel/functionPanel/BoothsellNotify.h"

#include "event/EventProtocol.h"
#include "event/EventDispatcher.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "network/NetProtocol.h"
#include "network/HandleMessage.h"
#include "network/MsgListener.h"

#include "userdata/FuncData.h"
#include "SceneHelper.h"
#include "logic/platform/IPlatform.h"
#include "PlatformDefinition.h"

using namespace cocos2d;

#define RELIVE_ALERT_TAG -999
#define RELIVE_BUTTON_TAG1 -1000
#define RELIVE_BUTTON_TAG2 -1001
#define RELIVE_BUTTON_TAG3 -1002
#define BOSS_LIFE_BAR_TAG	133

#define LEVEL_UP_BOARD_TAG	-1010
#define LEVEL_UP_BOARD_ZORDER 2

#define DANGEROUS_TAG -1100

#define TELEPORT_NOTE_LABEL_TAG 12

static const int MODE_BORDER_TAG = 12345;
static const int RESET_CLICK_ACTION_TAG = 3; 


GameUI::GameUI()
:m_pBelowMenu(NULL)
,mSubPanelContainer(NULL)
, m_roteLabel(NULL)
, m_rolemenu(NULL)
, m_pControlPanel(NULL)
,m_bIsDeath(false)
,mIsShortClick(false)
,mClickPoint(CCPointZero)
,m_experiencebar(NULL)
,mAutoMoveNode(NULL)
,mAutoFightNode(NULL)
,m_DogSkillPanel(NULL)
,mPKModeBox(NULL)
,mHeadPanel(NULL)
,mTeleportBtn(NULL)
{
	m_panels.resize(TAG_MAX_PANEL);
	for(int i=0; i<TAG_MAX_PANEL; i++)
	{
		m_panels[i] = NULL; 
	}

	m_IsInUnknownMap = false ;

	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_OPEN, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_CLOSE, this);
}

GameUI::~GameUI()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_OPEN, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_CLOSE, this);
}

// on "init" you need to initialize your instance
bool GameUI::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	bool bRet = false;
	do
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		
		CCLog("Game UI init begin...");
		
		initMainMenu();

		schedule(schedule_selector(GameUI::update), 0.1f);

		CCLog("Game UI init end...");

		BuffPanel *buffPanel = BuffPanel::create();
		if (buffPanel)
		{
			addChild(buffPanel);
		}


		MiniMapLayer* pMinMap = MiniMapLayer::create();
		pMinMap->setPosition(CCPointZero);
		addChild(pMinMap);

		LowerRightNotificationPanel *notificationPanel = LowerRightNotificationPanel::create();
		addChild(notificationPanel);

		TeamOperationPanel* pTeamOp = TeamOperationPanel::create();
		pTeamOp->setAnchorPoint(CCPointZero);
		pTeamOp->setPosition(CCPointZero);
		addChild(pTeamOp);

		initAutoMoveNote();
		initAutoFightNote();
		initTeleportButton();
		// sub panel container
		mSubPanelContainer = CCLayer::create();
		addChild(mSubPanelContainer, 1);
		bRet = true;
	} while (0);

	setTouchEnabled(true);


	//当前角色在小包中不存在的地图中
	if (SceneHelper::isUnknownMapInMini(GameData::getCurrentMap()->mID))
	{
		m_IsInUnknownMap = true ;
		showMiniUpdatePanel(LayoutData::getString(CPModuleName::LOGIN, "MiniGotoUnknownMap"),NotePanel::confirm_only);
		return bRet;
	}

	//40集强更
	if (SystemData::getConfigInt("mini")==1&& HeroData::getLevel() >= 40 )
	{
		showMiniUpdatePanel(LayoutData::getString(CPModuleName::LOGIN, "MiniUpgrade40ToStrongUpdate"),NotePanel::confirm_only);
		return bRet;
	}

	return bRet;
}

void GameUI::initMapName()
{
	m_mapNameNode=CCNode::create();
	m_mapNameNode->setPosition(ccp(215,425));
	addChild(m_mapNameNode,-100);

	CCSprite* mapNameBackground=SystemData::getSpriteByPlist("ui.common.mapname");
	mapNameBackground->setAnchorPoint(CCPointZero);
	mapNameBackground->setPosition(ccp(0,0));
	m_mapNameNode->addChild(mapNameBackground);

	CCLabelTTF* mapName=SystemData::getLabelTTF("mapname");
	mapName->setColor(ccc3(255,255,255)); 
	mapName->setFontSize(13);
	mapName->setString(GameData::s_user->mMap.mName.c_str());
	m_mapNameNode->addChild(mapName);
	mapCoordinates =SystemData::getLabelTTF("mappos");
	mapCoordinates->setColor(ccc3(255,255,255));
	mapCoordinates->setString(("("+SystemData::intToString(GameData::s_user->m_pMainRole->mTx)+","+SystemData::intToString(GameData::s_user->m_pMainRole->mTy)+")").c_str());
	m_mapNameNode->addChild(mapCoordinates);
}

void GameUI::initMainMenu()
{
	//init the top activities
	TopActiviy* pTopActivity = TopActiviy::create();
	if (!pTopActivity)
	{
		CCLog("Failed to create top activity");
		return;
	}
	pTopActivity->setAnchorPoint(CCPointZero);
	pTopActivity->setPosition(CCPointZero);
	addChild(pTopActivity);

	initExperienceBar();
	setExpProgress();
	
	initHeadPanel();
	initIconTips();
	initControlPanel();
	initSkillButtom();
	initCommondPanel();
	initDogSkillPanel();
	initControlTipsPanel();
	//提示地图名称
	showMapName();
	
	initAttackMode();
	updateAttackMode();
	
	// chat
	MiniChatPanel *miniChatPanel = MiniChatPanel::create();
	if (!miniChatPanel) return;
	addChild(miniChatPanel);
}

void GameUI::update(float dt)
{
	GameRole* pHero = GameData::s_user->m_pMainRole;

	if(GameData::s_user->m_bAttackModeChanged)
	{
		GameData::s_user->m_bAttackModeChanged = false;
		updateAttackMode();
	}
	if(GameData::s_user->m_bExperienceChanged)
	{
		GameData::s_user->m_bExperienceChanged = false;
		setExpProgress();
	}
	if (m_roteLabel)
	{
		if (m_rotex > SystemData::size_x/2 - 100 - m_rotew)
		{
			m_rotex -= 2;
			if (m_rotex < SystemData::size_x/2 - 100)
				m_roteLabel->setPositionX(SystemData::size_x/2 - 100);
			else
				m_roteLabel->setPositionX(m_rotex);
			float x = SystemData::size_x/2 - 100 - m_rotex;
			if (x <= 0)
				x = 0;
			float w = SystemData::size_x/2 + 100 - m_rotex;
			if (m_rotex > SystemData::size_x/2 - 100)
			{	
				if (w > m_rotew)
					w = m_rotew;
			}
			else
			{
				if (w > m_rotew - (SystemData::size_x/2 - 100 - m_rotex))
					w = m_rotew - (SystemData::size_x/2 - 100 - m_rotex);
				if (w>200)
					w=200;
				if (w<0)
					w=0;
			}
			m_roteLabel->setTextureRect(CCRectMake(x, m_roteLabel->getTextureRect().origin.y, w, m_roteLabel->getTextureRect().size.height));
		}
		else
		{
			m_roteLabel->removeFromParentAndCleanup(true);
			m_roteLabel = NULL;
		}
	}
	updateAutoMoveFlag();
	updateAutoFightFlag();
	updateTeleportButton();
}
/**
 * 显示指定标签的面板
 * 统一的面板创建和显示入口，支持多种类型的游戏功能面板
 * @param tag 面板标识符，对应PANEL_TAG枚举值
 */
void GameUI::showPanel( int tag )
{
	if (tag >= (int)m_panels.size())
	{
		return;
	}
	
	if(!hasSubPanel(tag))
	{
		CCLayer *panel = NULL;
		switch(tag)
		{
		case TAG_MAIN_PANEL:
			panel=MainPanel::create();
			panel->setAnchorPoint(ccp(0.5,0.5));
			panel->setPosition(ccp(200,60));
			break;
		case TAG_TASKCONTENT_PANEL:
			panel = TaskContentPanel::create();
			panel->setAnchorPoint(ccp(0.5,0.5));
			panel->setPosition(ccp(200,60));
			break;
		case TAG_TASK_PANEL:
			panel = TaskTipsPanel::create();
			panel->setAnchorPoint(ccp(0.5,0.5));
			panel->setPosition(ccp(200,60));
			break;
		case TAG_TALK_PANEL:
			panel = NPCTalkPanel::create();	
			panel->setAnchorPoint(ccp(0.5,0.5));
			panel->setPosition(ccp(200,60));
			break;
		case TAG_MINMAP_PANEL:
			panel = MiniMapPanel::create();
			panel->setAnchorPoint(ccp(0.5,0.5));
			panel->setPosition(ccp(200,60));
			break;
		case TAG_SHOP_PANEL:
			panel = ShopPanel::create();
			panel->setAnchorPoint(ccp(0.5,0.5));
			panel->setPosition(ccp(200,60));
			break;
		default:
			break;
		}
		if (panel)
		{
			panel->setTag(tag);
			addSubPanel(panel);
			m_panels[tag] = panel;
			m_pOpenWindowStack.push(tag);
		}
	}
	
}

void GameUI::hidePanel( int tag )
{
	if (tag != -1)
	{
		CCNode *subPanel = mSubPanelContainer->getChildByTag(tag);
		if (subPanel)
		{
			subPanel->removeFromParent();
		}

		if (0 <= tag && tag < (int)m_panels.size())
		{
			if(m_panels[tag] != NULL)
			{

				if (tag == TAG_TASK_PANEL
					||tag == TAG_TEAM_PANEL)
				{
					m_pBuleFlag[tag-30]->setVisible(false);
				}
				m_panels[tag] = NULL;
			}
		}
	}
}

void GameUI::hidePanel(CCNode* panel)
{
	if (panel)
	{
		int tag = panel->getTag();
		panel->removeFromParent();
		//
		if (0 <= tag && tag < (int)m_panels.size())
		{
			if(m_panels[tag] != NULL)
			{

				if (tag == TAG_TASK_PANEL
					||tag == TAG_TEAM_PANEL)
				{
					m_pBuleFlag[tag-30]->setVisible(false);
				}
				m_panels[tag] = NULL;
			}
		}
	}
}

void GameUI::hideAllPanels()
{
	//
	// remove all sub panel except ReliveAlertPanel
	//
	// while(!m_pOpenWindowStack.empty()
	// 	&& m_pOpenWindowStack.top() < (int)m_panels.size()
	// 	&& !m_panels[m_pOpenWindowStack.top()])
	// {
	// 	m_pOpenWindowStack.pop();
	// }

	//
	while (!m_pOpenWindowStack.empty())
	{
		hidePanel(m_pOpenWindowStack.top());
		m_pOpenWindowStack.pop();
	}

	//
	CCArray *children = mSubPanelContainer->getChildren();
	if (children)
	{
		// We need a copy of the children array during the iteration
		// Because within the loop, we remove the child from the container
		// Which results in memory moving in the array
		// WARN: DO NOT use CCArray::createWithArray, it won't work unless for current version of cocos2d
		// Ronghui Yu, Aug 29, 2014
		std::vector<CCObject*> _children(children->data->arr, children->data->arr + children->data->num);
		for (std::vector<CCObject*>::const_iterator iter = _children.begin(), end = _children.end();
			iter != end; ++ iter)
		{
			CCNode *subPanel = dynamic_cast<CCNode *>(*iter);
			if (subPanel)
			{
				hidePanel(subPanel);
			}
		}
	}
}

CCNode * GameUI::getPanel( int tag )
{
	return mSubPanelContainer->getChildByTag(tag);
}

void GameUI::addSubPanel( CCNode *subPanel )
{
	addSubPanel(subPanel, 1);
}

void GameUI::addSubPanel( CCNode *subPanel, int zOrder )
{
	addSubPanel(subPanel, zOrder, subPanel->getTag());
}

void GameUI::addSubPanel( CCNode *subPanel, int zOrder, int tag )
{
	if (subPanel)
	{
		mSubPanelContainer->addChild(subPanel, zOrder, tag);
	}
}

bool GameUI::hasSubPanel( int tag )
{
	if (mSubPanelContainer->getChildByTag(tag))
	{
		return true;
	}
	return false;
}

void GameUI::updateAttackMode()
{
	if (mPKModeBox)
	{
		int mapType = Scene::stSceneNormal;
		StaticData::getMapType(GameData::s_user->mMap.mID, mapType);
		mPKModeBox->setVisible(mapType == Scene::stSceneNormal);
		
		const int curState = HeroData::getProp(Entity::attr_pkmode);
		if (Entity::pk_Peace <= curState && curState <= Entity::pk_Any)
		{
			mPKModeBox->setCurrentIndex(curState);
		}
	}
}

void GameUI::changeAttackModeRequest( int mode )
{
	MsgSetPlayerPkModeRequest *msg = new MsgSetPlayerPkModeRequest;
	msg->pkmode = mode;
	HandleMessage::sendMessage(msg);
}

void GameUI::onEnter()
{
	CCLayer::onEnter();
	setKeypadEnabled(true);
	EventDispatcher::sharedEventDispather()->addListener(this);
}

void GameUI::onExit()
{
	EventDispatcher::sharedEventDispather()->removeListener(this);
	CCLayer::onExit();
}

void GameUI::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_MAIN_ROLE_RELIVE)
	{
		Game* pGame = dynamic_cast<Game*>(getParent());
		if(pGame)
		{
			pGame->setTouchEnabled(true);
		}
	}
	else if(channel == EventProtocol::EVENT_CHANGE_HP ||
		channel == EventProtocol::EVENT_CHANGE_MP ||
		channel == EventProtocol::EVENT_ATTRIBUTE_CHANGE)
	{
		refreshRedBarAndBlueBar();
	}
	else if (channel == EventProtocol::EVENT_EQUIPBETTER_CHANGE)
	{
		if (GameData::s_user->m_changeEquipMsg)
		{
			GameData::s_user->m_changeEquipMsg = false;
		}
	}
	else if(channel == EventProtocol::EVENT_CHANGE_LEVEL)
	{
		mHeadPanel->setLevel(HeroData::getLevel());
	}
	else if(channel == EventProtocol::EVENT_EXPERIENCE_CHANGE)
	{
		GameRole* pHero = GameData::s_user->m_pMainRole;
		m_experiencebar->setNewProgress(pHero->mExperience,pHero->mExperienceNext);
	}
	else if(channel == EventProtocol::EVENT_TARGET_DISAPPEAR)
	{
		hideTargetPanel();
		hideBossLifeBar();
	}
}

void GameUI::keyBackClicked()
{
	const int SETTING_PANEL_TAG = 3152;
	if (mSubPanelContainer->getChildrenCount() == 0)
	{
		SystemSetting *panel = SystemSetting::create();		
		panel->setTag(SETTING_PANEL_TAG);
		panel->setPosition(CCPointZero);
		addSubPanel(panel);
	}
	else
	{
		hideAllPanels();
	}
}

void GameUI::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	NPCFunctionData::clearNpcStack();
	hidePanel(TAG_TALK_PANEL);
	hidePanel(TAG_NPCTASK_PANEL);
	MineData::clear();
	hidePanel(TAG_MINE_PANEL);
	hidePanel(TAG_FLYSHOES_MENU);
	
	if (pTouches == NULL)
	{
		return;
	}

	if (GameData::getPixesMap() == NULL)
	{
		return;
	}
	
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	CCPoint touchPos = touch->getLocation();

	GameRole* pHero = GameData::s_user->m_pMainRole;
	if (SkillState::_s_state_pre_fire_wall)
	{
		CCPoint mapPos = SystemData::convertToMapPosition(touchPos);
		mapPos = ccp(int(mapPos.x/PixesMap::TILE_WIDTH), int(mapPos.y/PixesMap::TILE_HEIGHT));
		if (!pHero->isBlocked(mapPos.x, mapPos.y))
		{
			SkillState::_s_state_fire_wall_position = ccp(mapPos.x, mapPos.y);
			int skillID = 0;
			if (pHero->isSkillLearned(SKILL_TYPE_HuoQiang*10, skillID))
			{
				pHero->clickSkills(skillID);
			}
			SkillState::_s_state_pre_fire_wall = false;
		}
	}
	else
	{
		if (GameData::getGhostManager()->touchAnyGhost(touchPos))
		{
			mIsShortClick = true;
			mClickPoint = touchPos;
			
			stopActionByTag(RESET_CLICK_ACTION_TAG);
			CCAction *action = CCSequence::create(CCDelayTime::create(0.5f)
				, CCCallFunc::create(this, callfunc_selector(GameUI::onResetClickState))
				, NULL);
			action->setTag(RESET_CLICK_ACTION_TAG);
			runAction(action);
		}
		else
		{
			mIsShortClick = false;
			mClickPoint = CCPointZero;
			pHero->touchScreenBegin(touchPos);
		}
	}
}

void GameUI::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	CCLayer::ccTouchesMoved(pTouches,pEvent);
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	if(touch)
	{
		CCPoint touchPos = touch->getLocationInView();
		touchPos = CCDirector::sharedDirector()->convertToGL(touchPos); 
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->touchScreenMoved(touchPos);
	}
}
/**
 * 触摸结束事件处理
 * 当玩家抬起手指时调用，处理短按点击逻辑和角色触摸结束状态
 */
void GameUI::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCLayer::ccTouchesEnded(pTouches,pEvent);
	GameRole* myRole = GameData::getMyRole();
	if(myRole) myRole->touchScreenEnded();
	if (mIsShortClick)
	{
		mIsShortClick = false;
		mClickPoint = CCPointZero;
		stopActionByTag(RESET_CLICK_ACTION_TAG);

		CCTouch *touch = (CCTouch*)pTouches->anyObject();
		if(touch)
		{
			GameData::getGhostManager()->handleTouches(touch->getLocation());
		}
	}
}
/**
 * 触摸取消事件处理
 * 当触摸被系统取消时（如来电、弹窗等中断），清理点击状态
 * 防止触摸中断导致的状态不一致问题
 */
void GameUI::ccTouchesCancelled( CCSet *pTouches, CCEvent *pEvent )
{
	CCLayer::ccTouchesCancelled(pTouches, pEvent);
	if (mIsShortClick)
	{
		mIsShortClick = false;
		mClickPoint = CCPointZero;
		stopActionByTag(RESET_CLICK_ACTION_TAG);
	}
}
/**
 * 更新自动移动标志的显示状态
 * 根据玩家是否处于自动移动状态，显示或隐藏自动移动提示图标
 */
void GameUI::updateAutoMoveFlag()
{
	GameRole* myRole = GameData::getMyRole();
	if (myRole) mAutoMoveNode->setVisible(myRole->m_bAutoMove);
}

void GameUI::updateAutoFightFlag()
{
	mAutoFightNode->setVisible(AutoAttack::checkAutoAttack());
	if (mAutoMoveNode->isVisible())
	{
		mAutoMoveNode->setVisible(!mAutoFightNode->isVisible());
	}
}
/**
 * 更新传送按钮的显示状态
 * 根据玩家任务状态和自动移动状态，智能显示或隐藏传送按钮
 * 同时根据玩家等级控制提示标签的显示
 */
void GameUI::updateTeleportButton()
{
	GameRole* myRole = GameData::getMyRole();
	if (!myRole)
	{
		return;
	}
	mTeleportBtn->setVisible(myRole->isQuestDoing() && myRole->m_bAutoMove);
	if (mTeleportBtn->isVisible())
	{
		CCNode *noteLabel = mTeleportBtn->getChildByTag(TELEPORT_NOTE_LABEL_TAG);
		if (noteLabel)
		{
			const int noteLevel = LayoutData::getInt(CPModuleName::TASK, "teleportNoteLevel");
			noteLabel->setVisible(HeroData::getLevel() <= noteLevel);
		}
	}
}
/**
 * 初始化攻击模式选择框
 * 创建并设置PK模式选择下拉框，只在普通地图显示，用于切换玩家的攻击模式
 * 攻击模式包括和平模式、组队模式、行会模式、全体模式等
 */
void GameUI::initAttackMode()
{
	if (!GameData::s_user)
	{
		return;
	}
	int mapType = Scene::stSceneNormal;
	StaticData::getMapType(GameData::s_user->mMap.mID, mapType);
	if (mapType != Scene::stSceneNormal)
	{
		return;
	}

	mPKModeBox = LayoutData::getComboBox(CPModuleName::MAIN_UI, "pkMode");
	mPKModeBox->setChangeHandler(this, callfuncN_selector(GameUI::onChangeAttackMode));
	mPKModeBox->setDirection(ComboBoxOpenType::open_Down);
	addChild(mPKModeBox);
	for (int i = Entity::pk_Peace; i <= Entity::pk_Any; i++)
	{
		const std::string &key = "pkModeFrame" + StringUtils::toString(i);
		mPKModeBox->addSpriteItem(LayoutData::getString(CPModuleName::MAIN_UI, key));
	}

	if (!GuideHelper::canOpenFunction(FunctionName::GONG_JI_MO_SHI))
	{
		mPKModeBox->setVisible(false);
	}
}

void GameUI::initSkillButtom()
{
	SkillLayer* pSkillLayer = SkillLayer::create();
	pSkillLayer->setPosition(CCPointZero);
	pSkillLayer->setAnchorPoint(CCPointZero);
	addChild(pSkillLayer);
}

void GameUI::setExpProgress()
{
	GameRole* pHero = GameData::s_user->m_pMainRole;
	m_experiencebar->setNewProgress(pHero->mExperience,pHero->mExperienceNext);
}
/**
 * 初始化角色头部信息面板
 * 创建并设置显示玩家基本信息的头部面板，包括姓名、等级、职业、血量等
 * 头部面板通常位于屏幕左上角，是玩家最重要的信息展示区域
 */
void GameUI::initHeadPanel()
{
	const GameRole *myRole = GameData::getMyRole();
	if (!myRole)
	{
		return;
	}

	mHeadPanel = HeadPanel::create();
	mHeadPanel->setName(myRole->mName);
	mHeadPanel->setLevel(HeroData::getLevel());
	mHeadPanel->setJob(HeroData::getJob());
	mHeadPanel->setGender(HeroData::getGender());
	mHeadPanel->setVIP(HeroData::getProp(Entity::attr_vip_level));
	mHeadPanel->setHP(myRole->mHp, myRole->mMaxHp);
	mHeadPanel->setMP(myRole->mMp, myRole->mMaxMp);
	mHeadPanel->setClickHandler(this, callfunc_selector(GameUI::onHeadPanel));
	mHeadPanel->setAnchorPoint(ccp(0, 1));
	mHeadPanel->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "headPanel"));
	addChild(mHeadPanel);
}
/**
 * 初始化经验条
 * 创建并设置玩家经验进度条，显示当前等级和经验进度
 * 经验条通常位于屏幕顶部，显示玩家的升级进度
 */
void GameUI::initExperienceBar()
{
	//experience bar
	GameRole* pHero = GameData::getMyRole();
	if (!pHero)
	{
		return;
	}

	CCSprite* shortcutframe = SystemData::getSpriteByPlist("main_ui.experience_bkg");
	addChild(shortcutframe);
	m_experiencebar = SystemData::getProgresBarByPlist("main_ui.experience_bar");
	m_experiencebar->setNewProgress(pHero->mExperience,pHero->mExperienceNext);
	addChild(m_experiencebar);
	CCSprite* shortcutgrid = SystemData::getSpriteByPlist("main_ui.experience_grid");
	addChild(shortcutgrid);
}

void GameUI::initCommondPanel()
{
	Win32Code(
		CommandPanel* panel = CommandPanel::create();
		if (!panel) return;
		panel->setPosition(ccp(820,500));//gm调试ui--500-400
		panel->setAnchorPoint(CCPointZero);
		addChild(panel);
	);
}

void GameUI::initDogSkillPanel()
{
	m_DogSkillPanel = DogSkillPanel::create();
	if (!m_DogSkillPanel) return;
	m_DogSkillPanel->setPosition(CCPointZero);
	m_DogSkillPanel->setAnchorPoint(CCPointZero);
	addChild(m_DogSkillPanel);

	showDogSkillPanelIfNeed();
}

void GameUI::showDogSkillPanelIfNeed()
{
	if (!m_DogSkillPanel)
	{
		return;
	}

	int saiMaChangFlag = 0;
	StaticData::getMapSaiMaChangFlag(GameData::getCurrentMap()->mID, saiMaChangFlag);
	const int dogCnt = HeroData::getProp(Entity::attr_dog_cnt);
	if (saiMaChangFlag == 0 && dogCnt > 0)
	{
		m_DogSkillPanel->setVisible(true);
	}
	else
	{
		hideDogSkillPanel();
	}
}

void GameUI::hideDogSkillPanel()
{
	if (m_DogSkillPanel)
	{
		m_DogSkillPanel->setVisible(false);
	}
}

void GameUI::checkDeath(const std::string& killName,int killType)
{
	int mid = GameData::s_user->mMap.mID;
	int relivemode = 0;
	LuaData::getProp(LuaData::MAP,mid,"relivemode",relivemode);
	int mapType = 0;
	LuaData::getProp(LuaData::MAP,mid,"type",mapType);

	if (relivemode)
	{
		showReliveAlert(ReliveAlertPanel::Relive_Orientation,killName,killType);
	}
	else
	{
		if (mapType==2||mapType==3)
		{
			showReliveAlert(ReliveAlertPanel::Relive_Instance,killName,killType);
		}
		else
		{
			showReliveAlert(ReliveAlertPanel::Relive_Normal,killName,killType);
		}
	}
}

void GameUI::showReliveAlert(int reliveMode,const std::string& killName,int killType)
{
	//关闭其他页面复活
	hideAllPanels();
	AutoAttack::closeAutoAttack();
	if (!hasSubPanel(RELIVE_ALERT_TAG))
	{
		ReliveAlertPanel *panel = ReliveAlertPanel::create(killName,reliveMode);
		if (!panel) return;
		addSubPanel(panel, 1, RELIVE_ALERT_TAG);
	}
}

void GameUI::DeathCallBack( CCObject* pSender )//复活ui
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		const int tag = pNode->getTag();
		if (tag == RELIVE_BUTTON_TAG1)
		{	
			std::vector<std::string> strlist;
			std::string gold="10";
			strlist.push_back(gold);
			Game::getGameUI()->showFloatPanel(FloatPanelType::RELIVE_SITU,strlist);
		}
		else if(tag == RELIVE_BUTTON_TAG2)
		{
			MsgReviveEntityRequest* req = new MsgReviveEntityRequest;
			req->eid=GameData::s_user->m_pMainRole->mID;
			req->type=Entity::revive_safe;
			HandleMessage::sendMessage(req);		
		}
		else if(tag == RELIVE_BUTTON_TAG3)
		{
			MsgReviveEntityRequest* req = new MsgReviveEntityRequest;
			req->eid=GameData::s_user->m_pMainRole->mID;
			req->type=Entity::revive_safe;
			HandleMessage::sendMessage(req);		
		}
	}
}
/**
 * 显示地图名称动画效果
 * 在屏幕上方显示当前地图名称，3秒后淡出消失
 * 通常用于玩家进入新地图时的提示
 */
void GameUI::showMapName()
{
	CCSize WinSize=CCDirector::sharedDirector()->getWinSize();
	std::string mapname;
	LuaData::getProp(LuaData::MAP,GameData::s_user->mMap.mID,"name",mapname);
	CCLabelTTF *pLabel=CCLabelTTF::create(mapname.c_str(),"Arial",40);
	pLabel->setColor(ccYELLOW);
	pLabel->setPosition(ccp(WinSize.width/2,WinSize.height*4/5));
	addChild(pLabel);
	pLabel->runAction(CCSequence::create(CCFadeOut::create(3),CCActionInstantRemoveFromParentEx::create(pLabel),NULL));
}

void GameUI::initControlPanel()
{
	if(UserData::getIntData(HeroData::getPID(),CPUserData::CONTROL_OFF))//摇杆ui
	{
		if (m_pControlPanel)
		{
			m_pControlPanel->setVisible(false);
			m_pControlPanel->setTouchEnabled(false);
		}
		return ;
	}
	else
	{
		if (m_pControlPanel)
		{
			m_pControlPanel->setVisible(true);
			m_pControlPanel->setTouchEnabled(true);
			return;
		}
		m_pControlPanel = ControlPanel::create();
		if(m_pControlPanel)
		{
			m_pControlPanel->setAnchorPoint(CCPointZero);
			m_pControlPanel->setPosition(ccp(50,50));
			 // 设置摇杆变大 - 1.5倍大小
            m_pControlPanel->setScale(1.5f);
			addChild(m_pControlPanel);
		}
	}
}

void GameUI::initControlTipsPanel()
{
	CCNode *panel = LeftTipsPanel::create();
	if (!panel) return;
	panel->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "leftMenuPanel"));//任务ui
	addChild(panel);	
}

void GameUI::initAutoMoveNote()
{
	mAutoMoveNode = LayoutData::getSprite(CPModuleName::MAIN_UI, "autoMove");//自动战斗ui
	mAutoMoveNode->setVisible(false);
	addChild(mAutoMoveNode);
}

void GameUI::initAutoFightNote()
{
	mAutoFightNode = LayoutData::getSprite(CPModuleName::MAIN_UI, "autoFight");//寻路ui
	mAutoFightNode->setVisible(false);
	addChild(mAutoFightNode);
}

void GameUI::initTeleportButton()
{
	// teleport menu
	CCMenu *teleportMenu = CCMenu::create();
	if (!teleportMenu) return;
	teleportMenu->setPosition(CCPointZero);
	addChild(teleportMenu);

	mTeleportBtn = LayoutData::getMenuItemImg(CPModuleName::TASK, "teleport");
	mTeleportBtn->setTarget(this, menu_selector(GameUI::onTeleport));
	mTeleportBtn->setVisible(false);
	mTeleportBtn->setPosition(ccp(800, 100));//强制飞鞋ui
	teleportMenu->addChild(mTeleportBtn);

	CCLabelTTF *noteLabel = LayoutData::getLabelTTF(CPModuleName::TASK, "teleportNote");
	noteLabel->setPositionX(mTeleportBtn->getContentSize().width/2);
	mTeleportBtn->addChild(noteLabel, 0, TELEPORT_NOTE_LABEL_TAG);
}
//这是显示浮动面板的函数。浮动面板（FloatPanel）通常用于显示提示、确认框等，应该居中显示。
FloatPanel* GameUI::showFloatPanel( int type , const std::vector<string>& strlist,bool visibleSelect , bool visibleButton)
{
	if(m_panels[TAG_FLOAT_PANEL] != NULL)
	{
		hidePanel(TAG_FLOAT_PANEL);
	}
	FloatPanel* panel=FloatPanel::create(type);
	if (panel)
	{
		panel->setAnchorPoint(ccp(0.5f, 0.5f));
		panel->setTipsContent(strlist);
		panel->setbtnVisible(visibleButton);
		panel->setselectVisible(visibleButton);
		addSubPanel(panel, 1, TAG_FLOAT_PANEL);
		m_panels[TAG_FLOAT_PANEL] = panel;
		m_pOpenWindowStack.push(TAG_FLOAT_PANEL); 
	}
	return panel;
}
//显示物品提示面板ui
//void GameUI::showTipsPanel(UserItem* pItem, int type, const CCPoint& pos, const CCPoint& anpos)//戒指手镯
//{
//	if(m_panels[TAG_Tips_PANEL] != NULL)
//	{
//		hidePanel(TAG_Tips_PANEL);
//	}
//
//	ItemTooltip* pTip=CommonFunction::getItemTips(pItem,type);
//	if (pTip)
//	{
//		pTip->setAnchorPoint(anpos);
//		if (pTip->getPositionX()==-1 && pTip->getPositionY()==-1)
//		{
//			pTip->setPosition(ccp(700,65));
//		}
//		else
//		{
//			pTip->setPosition(pos);
//		}
//		pTip->setTag(TAG_Tips_PANEL);
//		addSubPanel(pTip);
//		m_panels[TAG_Tips_PANEL] = pTip; 
//		m_pOpenWindowStack.push(TAG_Tips_PANEL);
//	}
//}
//void GameUI::showTipsPanel(UserItem* pItem, int type, const CCPoint& pos, const CCPoint& anpos)
//{
//	if(m_panels[TAG_Tips_PANEL] != NULL) hidePanel(TAG_Tips_PANEL);
//
//	ItemTooltip* pTip = CommonFunction::getItemTips(pItem, type);
//	if (pTip)
//	{
//		pTip->setAnchorPoint(anpos);
//		pTip->setPosition(ccp(700, 85));  // 所有提示框固定位置
//		
//		pTip->setTag(TAG_Tips_PANEL);
//		addSubPanel(pTip);
//		m_panels[TAG_Tips_PANEL] = pTip; 
//		m_pOpenWindowStack.push(TAG_Tips_PANEL);
//	}
//}
void GameUI::showTipsPanel(UserItem* pItem, int type, const CCPoint& pos, const CCPoint& anpos)//显示物品提示面板ui
{
	if(m_panels[TAG_Tips_PANEL] != NULL) hidePanel(TAG_Tips_PANEL);

	ItemTooltip* pTip = CommonFunction::getItemTips(pItem, type);
	if (pTip)
	{
		// 简单跟随：鼠标右下方偏移20像素
		pTip->setAnchorPoint(ccp(0, 1));  // 左上角锚点
		pTip->setPosition(ccp(pos.x + 255, pos.y + 66));
		
		pTip->setTag(TAG_Tips_PANEL);
		addSubPanel(pTip);
		m_panels[TAG_Tips_PANEL] = pTip; 
		m_pOpenWindowStack.push(TAG_Tips_PANEL);
	}
}

void GameUI::showPetBaseTipPanel(UserPet* pPet, int type, const CCPoint& pos, const CCPoint& anpos)
{
	if(m_panels[TAG_Tips_PANEL] != NULL)
	{
		hidePanel(TAG_Tips_PANEL);
	}

	ItemTooltip* pTip=CommonFunction::getPetBaseTips(pPet,type);
	if (pTip)
	{
		pTip->setAnchorPoint(anpos);
		if (pTip->getPositionX()==-1 && pTip->getPositionY()==-1)
		{
			pTip->setPosition(ccp(535,10));
		}
		else
		{
			pTip->setPosition(pos);
		}
		pTip->setTag(TAG_Tips_PANEL);
		addSubPanel(pTip);
		m_panels[TAG_Tips_PANEL] = pTip; 
		m_pOpenWindowStack.push(TAG_Tips_PANEL);
	}
}
//npc面板
void GameUI::showNPCTaskPanel( int qid )
{
	if (m_panels[TAG_TALK_PANEL] != NULL)
	{
		m_panels[TAG_TALK_PANEL]->setVisible(false);
	}
	if(m_panels[TAG_NPCTASK_PANEL] != NULL)
	{
		hidePanel(TAG_NPCTASK_PANEL);
	}
	NPCTaskPanel* panel=NPCTaskPanel::create(qid);
	if (panel)
	{
		panel->setPosition(CCPointZero);
		panel->setTag(TAG_NPCTASK_PANEL);
		addSubPanel(panel);
		m_panels[TAG_NPCTASK_PANEL] = panel; 
		m_pOpenWindowStack.push(TAG_NPCTASK_PANEL);
	}
}

void GameUI::showTalkPanel(bool flag)
{
	if (m_panels[TAG_TALK_PANEL] != NULL)
	{
		m_panels[TAG_TALK_PANEL]->setVisible(true);
		((NPCTalkPanel*)m_panels[TAG_TALK_PANEL])->setShowQuest(flag);
	}
	else
	{
		showPanel(TAG_TALK_PANEL);
	}
}
//摆摊面板
void GameUI::showBoothPanel( int targeteid,int type ,bool isHighBooth)
{
	//请求玩家数据
	MsgGetSceneEntityInfoRequest* msg=new MsgGetSceneEntityInfoRequest;
	msg->eid=targeteid;
	HandleMessage::sendMessage(msg);

	if (getPanel(TAG_MAIN_PANEL))
	{
		MainPanel* panel = dynamic_cast<MainPanel*>(getPanel(TAG_MAIN_PANEL));
		if (panel)
		{
			panel->addPanel(TAG_Booth_Panel,type,1);
			m_pOpenWindowStack.push(TAG_Booth_Panel);
		}
	}
	else
	{
		MainPanel* panel=MainPanel::create();
		if (!panel) return;
		panel->setAnchorPoint(CCPointZero);
		panel->setPosition(CCPointZero);

		//if (panel)
		//{
		panel->setTag(TAG_MAIN_PANEL);
		panel->setPosition(ccp(200, 60));//点摆摊ui
		addSubPanel(panel);
		m_panels[TAG_MAIN_PANEL] = panel;
		//}
		panel->addPanel(TAG_Booth_Panel,type,1);
		m_pOpenWindowStack.push(TAG_Booth_Panel);
	}
}
//交易面板
void GameUI::showTradePanel()//交易里面ui
{
	if(m_panels[TAG_TRADE_PANEL] != NULL)
	{
		return;
	}
	TradePanel* panel=TradePanel::create();
	if (!panel) return;
	panel->setAnchorPoint(CCPointZero);
	panel->setPosition(ccp(200, 60));
	//if (panel)
	//{
	panel->setTag(TAG_TRADE_PANEL);
	addSubPanel(panel);
	m_panels[TAG_TRADE_PANEL] = panel;
	m_pOpenWindowStack.push(TAG_TRADE_PANEL);
	//}
}
//这是显示目标面板
void GameUI::showTargetPanel()
{
	TargetPanel *panel = dynamic_cast<TargetPanel *>(getPanel(TAG_TARGET_PANEL));
	if (panel)
	{
		panel->refresh();
		return;
	}

	panel = TargetPanel::create();
	if (panel)
	{
		panel->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "otherHeadPanel"));
		addSubPanel(panel, 0, TAG_TARGET_PANEL);
		m_panels[TAG_TARGET_PANEL] = panel;
		m_pOpenWindowStack.push(TAG_TARGET_PANEL);
	}
}

void GameUI::hideTargetPanel()
{
	if(m_panels[TAG_TARGET_PANEL] != NULL)
	{
		hidePanel(TAG_TARGET_PANEL);
	}
}
//数字面板（用于输入数量等）
void GameUI::showNumberBoard( int *a,int b,int eventc,int d ,const std::string& str)
{
	if(m_panels[TAG_NUMBER_PANEL] != NULL)
	{
		hidePanel(TAG_NUMBER_PANEL);
		// mSubPanelContainer->removeChildByTag(TAG_NUMBER_PANEL);
		// m_panels[TAG_NUMBER_PANEL] =NULL;
	}
	NumberBoard* pKeyBoard=NumberBoard::create(a,b,eventc,d);
	if (pKeyBoard)
	{
		pKeyBoard->setAnchorPoint(CCPointZero);
		pKeyBoard->setPosition(SystemData::getLayoutPoint("ui_sellpanel_pos"));
		if (!str.empty())
		{
			pKeyBoard->setCurLabelStr(str);
		}
		pKeyBoard->setTag(TAG_NUMBER_PANEL);
		addSubPanel(pKeyBoard);
		m_panels[TAG_NUMBER_PANEL] = pKeyBoard;
		m_pOpenWindowStack.push(TAG_NUMBER_PANEL);
	}
}
//这是显示操作菜单
void GameUI::showOperationMenu( int type )
{
	if(m_panels[TAG_OPERATION_MENU] != NULL)
	{
		hidePanel(TAG_OPERATION_MENU);
		// mSubPanelContainer->removeChildByTag(TAG_OPERATION_MENU);
		// m_panels[TAG_OPERATION_MENU] =NULL;
	}
	OperateMenu* pOperationMenu=OperateMenu::create(type);
	if (pOperationMenu)
	{
		pOperationMenu->setAnchorPoint(ccp(0,1));
		pOperationMenu->setTag(TAG_OPERATION_MENU);
		addSubPanel(pOperationMenu);
		m_panels[TAG_OPERATION_MENU] = pOperationMenu;
		m_pOpenWindowStack.push(TAG_OPERATION_MENU);
	}
}

void GameUI::onChangeAttackMode(CCNode* pSender)
{
	changeAttackModeRequest(mPKModeBox->getCurrentIndex());
}

void GameUI::onHeadPanel()
{
	showPanel(TAG_MAIN_PANEL);
}

void GameUI::onTeleport( CCObject *target )
{
	const int activityID = HeroData::getProp(Entity::attr_event_in);
	if (activityID <= 0)
	{
		const int qid = TaskData::getCurrentDoingTask();
		NPCFunctionData::getShoesFunc(qid, TAG_GOTONPC);
	}
}

void GameUI::showApplicationPanel()
{
	PopApplicationPanel* m_pApplicationPanel = NULL;
	m_pApplicationPanel = (PopApplicationPanel*)this->getChildByTag(789);
	if (m_pApplicationPanel)
	{
		m_pApplicationPanel->removeFromParentAndCleanup(true);
		m_pApplicationPanel = NULL;
	}
	int cnt = GuildData::getGuildApplicationCnt();
	if (cnt>0)
	{
		m_pApplicationPanel = PopApplicationPanel::create();
		m_pApplicationPanel->setTag(789);
		m_pApplicationPanel->setPosition(SystemData::getLayoutPoint("popalert.normal"));  
		addChild(m_pApplicationPanel,1);
	}
}

void GameUI::showMiniUpdatePanel(std::string strContent,int panel_format)
{
	//ewan聚到mini包更新可选
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan 
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_chuanqizhanshen
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_shachengchuanqi
		|| CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::ewan_yingxiongchuanqi)
	{
		if (m_IsInUnknownMap)
		{
			strContent = LayoutData::getString(CPModuleName::LOGIN, "UnknownMapInMini");
		}
		panel_format = NotePanel::normal ;
	}
	NotePanel *subPanel = NotePanel::create(panel_format);
	if (!subPanel) return;
	subPanel->setTitle(LayoutData::getString(CPModuleName::LOGIN, "optionalUpdateTitle"));
	subPanel->setContent(strContent);
	subPanel->setHandler(this, notepanel_selector(GameUI::miniUpdate));
	CPTips *tips = CPTips::create(subPanel, CPTipsType::modal);
	if (!tips) return;
	tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
	if (mSubPanelContainer->getChildrenCount()==0)
	{
		addChild(tips);
	}
	else
	{
		addSubPanel(tips);
	}
}

void GameUI::miniUpdate(int code)
{
	if (code == NotePanel::confirm)
	{
		LoginFace::s_mini=1;//设置小包强制更新标志
		SceneManager::switchToLogin();
	}
	else
	{
		if (m_IsInUnknownMap)
		{
			m_IsInUnknownMap=false;
			SceneHelper::teleportToNPCRequest( 165 ); //默认传送至土城传送石安全区
		}
	}
}

void GameUI::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if(source=="HandleMessageReviveEntityResponse")
		{
			if (!CPEventHelper::isRequestSuccess())
			{
				const int errcode = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
				if (errcode==Error::NotEnoughGold)
				{
					std::vector<std::string> strList;
					strList.push_back("10");
					showFloatPanel(FloatPanelType::Relive_Item_NotEnough,strList); 
				}
			}
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerLvlExpNotify")
		{
			const int dLevel = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (dLevel > 0)
			{
				mHeadPanel->setLevel(HeroData::getLevel());
				showLevelUp();
				if (mPKModeBox &&
					!mPKModeBox->isVisible() &&
					GuideHelper::canOpenFunction(FunctionName::GONG_JI_MO_SHI))
				{
					mPKModeBox->runAction(CPNodeHelper::getScaleToBig());
				}
			}

			//迷你包>40集，强制升级
			if (SystemData::getConfigInt("mini")==1&& HeroData::getLevel() >= 40 )
			{
				//hideAllPanels();
				showMiniUpdatePanel(LayoutData::getString(CPModuleName::LOGIN, "MiniUpgrade40ToStrongUpdate"),NotePanel::confirm_only);
			}
		}
		else if(source=="PreventMiniSwitchToUnknownMap")
		{
			hidePanel(TAG_TALK_PANEL);//隐藏NPC talk面板
			showMiniUpdatePanel(LayoutData::getString(CPModuleName::LOGIN, "MiniGotoUnknownMap"),NotePanel::confirm_only);
		}
		else if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			 const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			 if (type == Entity::attr_vip_level)
			 {
				 mHeadPanel->setVIP(HeroData::getProp(Entity::attr_vip_level));
			 }
			 else if (type == Entity::attr_pkmode)
			 {
				 updateAttackMode();
			 }
		}
		else if (source == "HandleMessageUpdPlayerBaseNotify")
		{
			GameRole* myRole = GameData::getMyRole();
			if (myRole) mHeadPanel->setName(myRole->mName);
		}
		else if (source == "HandleMessageImBeAttackedDelayNotify")
		{
			GameRole *myRole = GameData::getMyRole();
			if (myRole && UserData::getIntData(HeroData::getPID(), CPUserData::BEATTACK_EFFECT_OFF) == 0)
			{
				const float percent = myRole->mHp/(myRole->mMaxHp + 0.01f);
				if (percent < LayoutData::getFloat(CPModuleName::COMMON, "dangerousPercent"))
				{
					showDangerous();
				}
			}

			const int eid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			AliveGhost *player = dynamic_cast<AliveGhost *>(GameData::getGhostManager()->getGhostById(eid));
			if (player)
			{
				AliveGhost *aimGhost = myRole->getTheAim();
				if (aimGhost == NULL
					|| aimGhost->mType != GHOST_TYPE_PLAYER)
				{
					myRole->changeToPlayerAnim(player);
				}

				if (getPanel(TAG_TARGET_PANEL) == NULL)
				{
					showTargetPanel();
				}
			}
		}
		else if(source == "HandleMesssagePlayerDeadInfoNotify")
		{
			const std::string &killName = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
			int killType = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
			//checkDeath(killName,killType);
		}
		else if(source == "HandleMessageGuildInviteNotify")
		{
			std::vector<std::string> strList;
			strList.push_back(CPEventHelper::getEventStringData(CPEventData::VALUE_2).c_str());
			strList.push_back(CPEventHelper::getEventStringData(CPEventData::VALUE_3).c_str());
			int pid = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
			int gid = CPEventHelper::getEventIntData(CPEventData::VALUE_5);
			FloatPanel* panel = showFloatPanel(FloatPanelType::Guild_Invite,strList); 
			if (!panel) return;
			panel->setData(pid,gid);
		}
		else if (source == "HandleMessageMapSelfEnterNotify")
		{
			showDogSkillPanelIfNeed();
			hideAllPanels();
			updateAttackMode();
		}
		else if (source == "HandleMessageCrossServerNotify")
		{
			const int &err = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			if (err == Error::Success)
			{
				const string &ip = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
				const int &port = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				const int &serverid = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
				CPPlatformMnger.setIntData(CPPlatformData::SERVER_ID, serverid);

				HandleMessage::startCSServer(ip, port);
				const int pid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				LoginHelper::enterGame(LoginHelper::getIndexByPID(pid));
				//CCDirector::sharedDirector()->replaceScene(SceneFactory::sceneResLoading());
			}
		}
	}
	else if (eventName == CPEventName::UI_CLOSE)
	{
		const std::string &target = CPEventHelper::getEventTarget();
		if (target == "GameUI")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
			if (type==16 || type == 21)
			{
				if (hasSubPanel(TAG_SPECIAL_PANEL))
				{
					hidePanel(TAG_SPECIAL_PANEL);
					// mSubPanelContainer->removeChildByTag(TAG_SPECIAL_PANEL);
				}
			}
		}
	}
	else if (eventName == CPEventName::UI_OPEN)
	{
		const std::string &target = CPEventHelper::getEventTarget();
		if (target == "GameUI")
		{
			const std::string &panelName = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
			if (panelName == "MainPanel")
			{
				showPanel(TAG_MAIN_PANEL);
			}
			else if (panelName == "ChatPanel")
			{
				ChatPanel *node = ChatPanel::instance();
				node->removeFromParent();
				addSubPanel(node);
				node->show(CPEventHelper::getEventIntData(CPEventData::VALUE_2));
			}
			else if (panelName == "ShopPanel")
			{
				showPanel(TAG_SHOP_PANEL);
			}
			else if (panelName == "FloatPanel")
			{
				const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				const std::string &str = CPEventHelper::getEventStringData(CPEventData::VALUE_3);
				StringVector vect;
				vect.push_back(str);
				showFloatPanel(type, vect); 
			}
			else if (panelName == "BagUnlock")
			{
				if (HeroData::getProp(Entity::attr_bagslot)>=SystemData::getLayoutValue("MaxPlayerBagSlot"))
				{
					CPEventHelper::uiNotify("","",Error::MaxBagSolt);
					return;
				}
				showUnlockPanel(1,1);
			}
			else if (panelName == "ReliveAlertPanel") 
			{
				const std::string &killName = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
				int killType = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				checkDeath(killName,killType);
			}
			else if (panelName == "BoothsellNotify")
			{
				const int idx = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				BoothsellNotify* pPanel=BoothsellNotify::create(idx);
				pPanel->setAnchorPoint(CCPointZero);
				addSubPanel(pPanel);
			}
			else if (panelName == "PanLongEquipPanel")
			{
				PanLongEquipPanel* panel = PanLongEquipPanel::create();
				if (!panel) return;
				CPTips *tips = CPTips::create(panel);
				if (!tips) return;
				tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
				addSubPanel(tips,1,TAG_SPECIAL_PANEL);
			}
			else if (panelName == "ItemBindListPanel")
			{
				ItemBindListPanel* panel = ItemBindListPanel::create();
				if (!panel)
				{
					CPEventHelper::uiNotify("NoItemToBind","",290);
					return;
				}
				CPTips *tips = CPTips::create(panel);
				if (!tips) return;
				tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
				addSubPanel(tips,1,TAG_SPECIAL_PANEL);
			}
			else if (panelName == "MailPanel")
			{
				if (getPanel(TAG_Mail_PANEL))
				{
					return ;
				}
				CCNode *panel = PanelFactory::create(panelName);
				if (panel)
				{
					addSubPanel(panel,1,TAG_Mail_PANEL);
				}
			}
			else if (panelName == "CPTips")
			{
				const std::string &subName = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
				CPTipsSub *panel = dynamic_cast<CPTipsSub *>(PanelFactory::create(subName));
				if (panel)
				{
					CPTips *tips = CPTips::create(panel);
					if (!tips) return;
					tips->setPosition(LayoutData::getPoint(CPModuleName::COMMON, "center"));
					addSubPanel(tips);
				}
			}
			else
			{
				CCNode *panel = PanelFactory::create(panelName);
				if (panel)
				{
					addSubPanel(panel);
				}
				else
				{
					if (panelName == "TreasureHuntPanel")
					{
						CPEventHelper::uiNotify("","",Error::NotOpenNewFunc);	
					}
				}
			}
		}
	}
	else if(eventName == CPEventName::UI_NOTIFY)
	{
		if (source == "UIShowDogSkillPanel")
		{
			showDogSkillPanelIfNeed();
		}
		else if (source == "UIHideDogSkillPanel")
		{
			hideDogSkillPanel();
		}
		else if (source == "UIRefreshDogMode")
		{
			if (m_DogSkillPanel)
			{
				m_DogSkillPanel->refreshButtons();
			}
		}
		else if(source == "UIShowSocialDialog")
		{
			CCLog("___GameUI onCPEvent,UIShowSocialDialog,Key:%s", CPEventHelper::getEventStringData(CPEventData::VALUE_2).c_str());
			CCNode *panel = PanelFactory::create(CPEventHelper::getEventStringData(CPEventData::VALUE_2));
			if (panel)
			{
				addSubPanel(panel);
			}
		}
		else if (source == "GameRole::changeTheAim")
		{
			const std::string &aim = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
			if (aim == "Boss")
			{
				showBossLifeBar();
			}
			else
			{
				hideBossLifeBar();
			}
		}
		else if (source == "UINotifyPlayerMine")
		{
			int skillid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			UserItem *item = GameData::s_user->getUserItemData()->getItemByPosition(-Pos_Weapon);
			if (item)
			{
				int skillID = 0;
				StaticData::getItemSkillID(item->sid, skillID);
				if (skillid == skillID )
				{
					showMinePanel();
				}
			}			
		}
		else if (source == "useFireworks")
		{
			 const int sid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			 showFireworks(sid);
		}
	}
}
//这是显示解锁面板（背包解锁）的函数。
void GameUI::showUnlockPanel( int cnt, int bagtype )
{
	if (hasSubPanel(TAG_UNLOCKBAG_PANEL))
	{
		hidePanel(TAG_UNLOCKBAG_PANEL);
	}
	BagUnlockPanel* pPanel=BagUnlockPanel::create(cnt,bagtype);
	if (!pPanel) return;
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(ccp(577,95));
	pPanel->setTag(TAG_UNLOCKBAG_PANEL);
	addSubPanel(pPanel);
}

void GameUI::setUnlockCount( int count )
{
	if (hasSubPanel(TAG_UNLOCKBAG_PANEL))
	{
		((BagUnlockPanel*)mSubPanelContainer->getChildByTag(TAG_UNLOCKBAG_PANEL))->setUnlockCount(count);
	}
}

void GameUI::tryToMine( const CCPoint &touchPos )
{
	int miningFlag = 0;
	StaticData::getMapMiningFlag(GameData::s_user->mMap.mID, miningFlag);
	if (miningFlag != 0)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->tryToMine(touchPos);
	}
}

void GameUI::refreshRedBarAndBlueBar()
{
	const GameRole *myRole = GameData::getMyRole();
	if (!myRole) return;
	mHeadPanel->setHP(myRole->mHp, myRole->mMaxHp);
	mHeadPanel->setMP(myRole->mMp, myRole->mMaxMp);
	if (myRole->mHp>0)
	{
		hidePanel(RELIVE_ALERT_TAG);
	}
}

void GameUI::showLevelUp()
{
	CCNode *node = getChildByTag(LEVEL_UP_BOARD_TAG);
	if (node)
	{
		node->removeFromParent();
	}
	CCSprite *board = LayoutData::getSprite(CPModuleName::MAIN_UI, "lvlUpBoard");
	addChild(board, LEVEL_UP_BOARD_ZORDER, LEVEL_UP_BOARD_TAG);

	const std::string &path = LayoutData::getString(CPModuleName::MAIN_UI, "lvlUpNum");
	const CCSize &size = LayoutData::getSize(CPModuleName::MAIN_UI, "lvlUpNum");
	CCLabelAtlas *label = CCLabelAtlas::create(StringUtils::toString(HeroData::getLevel()).c_str(), path.c_str(), size.width, size.height, '0');
	label->setAnchorPoint(ccp(0.5f, 0));
	label->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "lvlUpNum"));
	board->addChild(label);

	CCDelayTime *dl1 = CCDelayTime::create(1.5f);
	CCFadeOut *fo1 = CCFadeOut::create(0.5f);
	CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
	CCAction *action1 = CCSequence::create(dl1, fo1, rmv, NULL);
	board->runAction(action1);

	CCDelayTime *dl2 = CCDelayTime::create(1.5f);
	CCFadeOut *fo2 = CCFadeOut::create(0.5f);
	CCAction *action2 = CCSequence::create(dl2, fo2, NULL);
	label->runAction(action2);
}

void GameUI::showDangerous()
{
	if (!getChildByTag(DANGEROUS_TAG))
	{
		CCSprite *redBorder = LayoutData::getSpriteByFile(CPModuleName::MAIN_UI, "dangerous");
		addChild(redBorder, 1, DANGEROUS_TAG);

		redBorder->setOpacity(0);
		CCFadeIn *fi = CCFadeIn::create(0.3f);
		CCFadeOut *fo = CCFadeOut::create(0.3f);
		CCRepeat *repeat = CCRepeat::create(CCSequence::create(fi, fo, NULL), 2);
		CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
		CCAction *action = CCSequence::create(repeat, rmv, NULL);
		redBorder->runAction(action);
	}
}

void GameUI::showBossLifeBar()
{
	BossLifeBar *bossLifeBar = dynamic_cast<BossLifeBar *>(getChildByTag(BOSS_LIFE_BAR_TAG));
	if (bossLifeBar)
	{
		bossLifeBar->refresh();
		return;
	}
	bossLifeBar = BossLifeBar::create();
	if (!bossLifeBar) return;
	bossLifeBar->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "bossLifeBar"));
	addChild(bossLifeBar, 0, BOSS_LIFE_BAR_TAG);
}

void GameUI::hideBossLifeBar()
{
	CCNode *bossLifeBar = getChildByTag(BOSS_LIFE_BAR_TAG);
	if (bossLifeBar)
	{
		bossLifeBar->removeFromParent();
	}
}
//这是显示烟花特效的函数
void GameUI::showFireworks( int itemSID )
{
	if (itemSID > 0)
	{
		std::string key;
		StaticData::getItemDataStr(itemSID, key);
		key = LayoutData::getString(CPModuleName::COMMON, "effectAnimPath") + key;
		CCSprite *anim = CPAnimMnger.getOneDirAnimSprite(key);
		anim->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "fireworks"));
		addChild(anim);

		anim->runAction(CCSequence::create(
			CCDelayTime::create(2.5f),
			CCActionInstantRemoveFromParent::create(),
			NULL));
	}
}

void GameUI::initIconTips()
{
	IconTipPanel* pPanel = IconTipPanel::create();
	if (!pPanel) return;
	pPanel->setPosition(CCPointZero);
	pPanel->setAnchorPoint(CCPointZero);
	addChild(pPanel);
}
//这是显示技能详细面板
void GameUI::showSkillTipsPanel( int skillid )
{
	if (hasSubPanel(TAG_Tips_PANEL))
	{
		// child->removeFromParentAndCleanup(true);
		hidePanel(TAG_Tips_PANEL);
	}
	ItemTooltip* ptips=ItemTooltip::create();
	if (ptips)
	{
		ptips->setAnchorPoint(ccp(0.5,0.5));
		CCPoint pos=ccp(330,130);
		//pos=convertToNodeSpace(pos);
		ptips->setTooltipSkill(skillid);
		ptips->setTag(TAG_Tips_PANEL);
		ptips->setPosition(pos);
		//ptips->setTag(100);
		addSubPanel(ptips);

		m_panels[TAG_Tips_PANEL] = ptips; 
		m_pOpenWindowStack.push(TAG_Tips_PANEL);
	}
}
//挖矿提示面板
void GameUI::showMinePanel()
{
	CCNode *child =mSubPanelContainer->getChildByTag(TAG_MINE_PANEL);
	if (child)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole && myRole->getState() == AVATAR_ACTION_MINE) 
		{
			child -> setVisible(true);
			return;
		}
		else
		{
			// child->removeFromParentAndCleanup(true);
			hidePanel(TAG_MINE_PANEL);
		}
	}
	MinePanel* ptips=MinePanel::create();
	if (ptips)
	{
		ptips->setAnchorPoint(ccp(0.5,0.5));
		CCPoint pos=ccp(330,130);
		//pos=convertToNodeSpace(pos);
		ptips->setTag(TAG_MINE_PANEL);
		ptips->setPosition(pos);
		addSubPanel(ptips);

		m_panels[TAG_MINE_PANEL] = ptips; 
		m_pOpenWindowStack.push(TAG_MINE_PANEL);
	}
}

void GameUI::showNumberKeyBoard( int a,int b,int eventc,int d,const std::string& str)
{
	if(hasSubPanel(TAG_NUMBER_PANEL))
	{
		hidePanel(TAG_NUMBER_PANEL);
	}
	NumberKeyBoard* pKeyBoard=NumberKeyBoard::create(a,b,eventc,d);
	if (pKeyBoard)
	{
		pKeyBoard->setAnchorPoint(CCPointZero);
		pKeyBoard->setPosition(ccp(SystemData::getLayoutPoint("ui_sellpanel_pos").x+50,SystemData::getLayoutPoint("ui_sellpanel_pos").y-30));
		if (!str.empty())
		{
			pKeyBoard->setCurLabelStr(str);
		}
		pKeyBoard->setTag(TAG_NUMBER_PANEL);
		addSubPanel(pKeyBoard);
		m_panels[TAG_NUMBER_PANEL] = pKeyBoard;
		m_pOpenWindowStack.push(TAG_NUMBER_PANEL);
	}
}

void GameUI::showNumberKeyBoard(int curValue,int MaxValue,int tag,int iid,int str)
{
	if(hasSubPanel(TAG_NUMBER_PANEL))
	{
		hidePanel(TAG_NUMBER_PANEL);
	}
	NumberKeyBoard* pKeyBoard=NumberKeyBoard::create(curValue,MaxValue,tag,iid,str);
	if (pKeyBoard)
	{
		pKeyBoard->setAnchorPoint(CCPointZero);
		pKeyBoard->setPosition(ccp(SystemData::getLayoutPoint("ui_sellpanel_pos").x+50,SystemData::getLayoutPoint("ui_sellpanel_pos").y-30));
		if (curValue!=0)
		{
			pKeyBoard->setCurLabelStr(SystemData::intToHexString(curValue));
		}
		pKeyBoard->setTag(TAG_NUMBER_PANEL);
		addSubPanel(pKeyBoard);
		m_panels[TAG_NUMBER_PANEL] = pKeyBoard;
		m_pOpenWindowStack.push(TAG_NUMBER_PANEL);
	}
}
//宠物进阶界面
void GameUI::showPetAdvance()
{
	if (hasSubPanel(TAG_PET_ADVANCE_PANEL))
	{
		hidePanel(TAG_PET_ADVANCE_PANEL);
	}
	PetAdvancedPanel* ptips=PetAdvancedPanel::create();
	if (ptips)
	{
		ptips->setAnchorPoint(ccp(0.5,0.5));
		CCPoint pos=ccp(330,130);
		ptips->setTag(TAG_PET_ADVANCE_PANEL);
		ptips->setPosition(pos);
		addSubPanel(ptips);

		m_panels[TAG_PET_ADVANCE_PANEL] = ptips; 
		m_pOpenWindowStack.push(TAG_PET_ADVANCE_PANEL);
	}
}

void GameUI::showPetReborn()//宠物转生界面
{
	CCNode *child =mSubPanelContainer->getChildByTag(TAG_PET_REBORN_PANEL);
	if (child)
	{
		mSubPanelContainer->removeChildByTag(TAG_PET_REBORN_PANEL);
		m_panels[TAG_PET_REBORN_PANEL] =NULL;
	}
	PetReborn* ptips=PetReborn::create();
	if (!ptips) return;
	ptips->setAnchorPoint(ccp(0.5,0.5));
	CCPoint pos=ccp(330,130);
	ptips->setTag(TAG_PET_REBORN_PANEL);
	ptips->setPosition(pos);
	addSubPanel(ptips);

	m_panels[TAG_PET_REBORN_PANEL] = ptips; 
	m_pOpenWindowStack.push(TAG_PET_REBORN_PANEL);
}

void GameUI::showPetSpeAttr()
{
	if (hasSubPanel(TAG_PET_APEATTR_PANEL))
	{
		hidePanel(TAG_PET_APEATTR_PANEL);
	}
	PetSpeAttrPanel* ptips=PetSpeAttrPanel::create();
	if (ptips)
	{
		ptips->setAnchorPoint(ccp(0.5,0.5));
		CCPoint pos=ccp(330,130);
		ptips->setTag(TAG_PET_APEATTR_PANEL);
		ptips->setPosition(pos);
		addSubPanel(ptips);

		m_panels[TAG_PET_APEATTR_PANEL] = ptips; 
		m_pOpenWindowStack.push(TAG_PET_APEATTR_PANEL);
	}
}

void GameUI::showFlyShoes( int data )
{
	if (hasSubPanel(TAG_FLYSHOES_MENU))
	{
		hidePanel(TAG_FLYSHOES_MENU);
	}
	FlyShoesMenu* ptips=FlyShoesMenu::create(data);
	if (ptips)
	{
		ptips->setTag(TAG_FLYSHOES_MENU);
		addSubPanel(ptips);

		m_panels[TAG_FLYSHOES_MENU] = ptips; 
		m_pOpenWindowStack.push(TAG_FLYSHOES_MENU);
	}
}

void GameUI::showBuffTips( int tag )
{
	if (hasSubPanel(TAG_Tips_PANEL))
	{
		hidePanel(TAG_Tips_PANEL);
	}
	BuffTips* ptips=BuffTips::create(tag);
	if (ptips)
	{
		ptips->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height*2/3));
		ptips->setTag(TAG_Tips_PANEL);
		addSubPanel(ptips);

		m_panels[TAG_Tips_PANEL] = ptips; 
		m_pOpenWindowStack.push(TAG_Tips_PANEL);
	}
}

void GameUI::onResetClickState()
{
	if (mIsShortClick)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->touchScreenBegin(mClickPoint);
		mIsShortClick = false;
		mClickPoint = CCPointZero;
	}
}
