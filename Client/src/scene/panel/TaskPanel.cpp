#include "TaskPanel.h"
#include "TaskModule.h"
#include "EntityDefinition.h"

#include "controls/CPItemComponents.h"
#include "controls/CPRichText.h"
#include "controls/CPScrollbar.h"

#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/AutoAttack.h"

#include "script/LuaWrapper.h"
#include "utils/StringUtils.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/TaskData.h"
#include "ext/CCMenuItemFontEx.h"
#include "ext/GeneralMenu.h"
#include "event/EventProtocol.h"

#include "userdata/luadata/TasktipsLua.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "ext/TouchCover.h"
#include "QuestDefinition.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "userdata/netdata/GhostManager.h"
#include "MsgScene.h"
#include "MsgItem.h"
#include "userdata/NPCFunctionData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/statetimer/FightingState.h"
#include "scene/panel/FloatPanelType.h"
#include "scene/panel/FloatPanel.h"

namespace TaskTipsBuilder
{
	enum
	{
		start = 1,
		doing = 2,
		stop = 3,
	};
}

namespace TaskTipsType
{
	enum
	{
		current_task = 0,
		access_task = 1,
	};
}

static void pushQuestData( int lineID, int qid, int state, int datax, int datay, int dataz, int index )
{
	Lua::instance()->push(lineID);
	Lua::instance()->push(qid);
	Lua::instance()->push(state);
	Lua::instance()->push(datax);
	Lua::instance()->push(datay);
	Lua::instance()->push(dataz);
	Lua::instance()->push(index);
}

static IDVector getQuestVect( int questType )
{
	if (questType == TaskTipsType::current_task)
	{
		return TaskData::getCurrentTasks();
	}
	return TaskData::getAccessTasks();
}

static int getQuestID( int questType, int index )
{
	const IDVector &quests = getQuestVect(questType);
	if (0 <= index && index < (int)quests.size())
	{
		return quests[index];
	}
	return 0;
}

static void addTaskDesc( int questType )
{
	const IDVector &questVect = getQuestVect(questType);
	const int len = questVect.size();
	if (len == 0)
	{
		pushQuestData(1, 0, 0, 0, 0, 0, 0);
		Lua::instance()->call("cb_build_task_desc", 7, 0);
		return;
	}

	for (int i = 0; i < len; i++)
	{
		const int qid = questVect[i];
		int datax = 0, datay = 0, dataz = 0;
		TaskData::getTaskExData(qid, datax, datay, dataz);
		pushQuestData(TaskData::getTaskLine(qid), qid, TaskData::getTaskState(qid), datax, datay, dataz, i);
		Lua::instance()->call("cb_build_task_desc", 7, 0);
	}	
}

////////////TaskTipsPanel/////////////////////////////////////////////
TaskTipsPanel::TaskTipsPanel()
	:mSwitchMenu(NULL)
	,mDescList(NULL)
	,mCurrentText(NULL)
	,mCurrentTaskBoard(NULL)
	,mCurrentType(TaskTipsType::current_task)
{
	CPEvtDispatcher.addEventListener(CPEventName::LUA_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

TaskTipsPanel::~TaskTipsPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LUA_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool TaskTipsPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();
	autoRefresh();

	return true;
}

void TaskTipsPanel::initUI()
{
	CCScale9Sprite *titleBoard = LayoutData::getScale9Sprite(CPModuleName::TASK, "titleBoard");
	addChild(titleBoard);

	// swith menu
	const CCSize &switchSize = LayoutData::getSize(CPModuleName::TASK, "switch");
	const CCPoint &switchPt = LayoutData::getPoint(CPModuleName::TASK, "switch");
	mSwitchMenu = CPItemComponents::create(switchSize, new CPLayoutList(CCSizeZero, false));
	mSwitchMenu->setPosition(switchPt);
	addChild(mSwitchMenu);

	CCMenuItemImage *currentTaskBtn = LayoutData::getMenuItemImg(CPModuleName::TASK, "currentTask");
	currentTaskBtn->setTarget(this, menu_selector(TaskTipsPanel::onSwitch));
	mSwitchMenu->addItem(currentTaskBtn);

	CCMenuItemImage *accessTaskBtn = LayoutData::getMenuItemImg(CPModuleName::TASK, "accessTask");
	accessTaskBtn->setTarget(this, menu_selector(TaskTipsPanel::onSwitch));
	mSwitchMenu->addItem(accessTaskBtn);
}

void TaskTipsPanel::refresh()
{
	if (!mDescList)
	{
		const CCSize &descSize = LayoutData::getSize(CPModuleName::TASK, "descList");
		const CCPoint &descPoint = LayoutData::getPoint(CPModuleName::TASK, "descList");
		mDescList = CPItemComponents::create(descSize, new CPLayoutList);
		mDescList->setClickSensitive(true);
		mDescList->setPosition(descPoint);
		addChild(mDescList);

		const CCSize &barSize = LayoutData::getSize(CPModuleName::TASK, "scrollBar");
		CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
		mDescList->setScrollbar(scrollBar);
	}

	mDescList->removeAllItems();
	addTaskDesc(mCurrentType);
}

void TaskTipsPanel::autoRefresh()
{
	mCurrentType = TaskTipsType::current_task;
	const IDVector &quests = getQuestVect(TaskTipsType::current_task);
	if (quests.empty())
	{
		mCurrentType = TaskTipsType::access_task;
	}
	refresh();
	mSwitchMenu->setCurrentIndex(mCurrentType);
}

void TaskTipsPanel::onSwitch( CCObject *target )
{
	const int type = mSwitchMenu->getCurrentIndex();
	if (type != mCurrentType)
	{
		mCurrentType = type;
		refresh();
	}
}

void TaskTipsPanel::onAutoMove(CCObject *target)
{
	const int activityID = HeroData::getProp(Entity::attr_event_in);
	if (activityID <= 0)
	{
		const int qid = getQuestID(mCurrentType, mDescList->getCurrentIndex());
		if (qid > 0)
		{
			AutoAttack::closeAutoAttack();
			NPCFunctionData::dealwithQuest(qid);
			MsgRideApproachNotity *msg = new MsgRideApproachNotity;
			HandleMessage::sendMessage(msg);
		}
	}
}

void TaskTipsPanel::buildDesc()
{
	const CCSize &descSize = LayoutData::getSize(CPModuleName::TASK, "descList");
	const int buildType = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
	switch (buildType)
	{
	case TaskTipsBuilder::start:
		{
			const int isNewTask = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (isNewTask != 0)
			{
				const CCSize &size = LayoutData::getSize(CPModuleName::TASK, "descItem");
				CCScale9Sprite *normNode = LayoutData::getScale9Sprite(CPModuleName::TASK, "descItemBoardNorm");
				normNode->setContentSize(size);
				CCScale9Sprite *selNode = LayoutData::getScale9Sprite(CPModuleName::TASK, "descItemBoardSel");
				selNode->setContentSize(size);

				mCurrentTaskBoard = CCMenuItemSprite::create(normNode, selNode);
				mCurrentTaskBoard->setTarget(this, menu_selector(TaskTipsPanel::onAutoMove));
			}
			mCurrentText = CPRichText::create(descSize.width, 0);
			break;
		}
	case TaskTipsBuilder::doing:
		{
			if (mCurrentText)
			{
				const std::string &text = CPEventHelper::getEventStringData(CPEventData::VALUE_2);
				const std::string &fontName = "Arial";
				int fontSize = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				int colorID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
				const ccColor3B &color = LayoutData::getColor3(CPModuleName::TASK, "desc" + StringUtils::toString(colorID));
				mCurrentText->addItem(new CPRichTextItemLabel(text, fontName, fontSize, color));
			}
			break;
		}
	case TaskTipsBuilder::stop:
		{
			if (mDescList && mCurrentText && mCurrentTaskBoard)
			{
#define TASK_DESC_TAG_BEGIN 10

				static int currentTag = TASK_DESC_TAG_BEGIN;
				mCurrentText->setAnchorPoint(CCPointZero);
				mCurrentText->setPosition(CCPointZero);
				mCurrentTaskBoard->addChild(mCurrentText, 0, currentTag);
				currentTag++;

				const int isFinish = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				if (isFinish != 0)
				{
					int heigh = 0;
					const CCPoint &firstPt = LayoutData::getPoint(CPModuleName::TASK, "descListFirst");
					for (int i = TASK_DESC_TAG_BEGIN; i < currentTag; i++)
					{
						CCNode *child = mCurrentTaskBoard->getChildByTag(i);
						if (child)
						{
							child->setPosition(ccp(firstPt.x, firstPt.y + heigh));
							heigh += child->getContentSize().height;
						}
					}
					mDescList->addItem(mCurrentTaskBoard);
					const int index = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
					mCurrentTaskBoard->setTag(index);

					currentTag = TASK_DESC_TAG_BEGIN;
					mCurrentTaskBoard = NULL;
				}
			}
			mCurrentText = NULL;
			break;
		}
	default:
		{
			CCLog(">>>Error: TaskTipsPanel::buildDesc, unknown buildType = %d", buildType);
			break;
		}
	}
}

void TaskTipsPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LUA_CHANGE)
	{
		if (source == "cb_build_task_desc")
		{
			buildDesc();
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageQuestUpdateList" ||
			source == "HandleMessageQuestUpdate")
		{
			autoRefresh();
			/*int data1 = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			int state = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
			int line = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
			int type;
			LuaData::getProp(LuaData::QUEST,data1,"type",type);
			if ( (state == Quest::state_NotFinished || state == Quest::state_Finished) && type== Quest::type_MonsterKillInMap)
			{
				NPCFunctionData::dealwithQuest(data1);
			}*/
		}
	}
}


//-----------------------------------------------------------------------------------------------------------//
TaskContentPanel::TaskContentPanel():
	m_pMainMenu(NULL),
	m_pLeftMenu(NULL),
	m_iCurrentType(-1),
	m_pRightMenu(NULL),
	mHeight(0),
	m_iCurrentQuestID(0),
	m_pCurrentQuestSprite(NULL),
	m_pRightBtnMenu(NULL)
{

}

TaskContentPanel::~TaskContentPanel()
{

}

TaskContentPanel* TaskContentPanel::create()
{
	TaskContentPanel* pPanel = new TaskContentPanel();
	if(pPanel && pPanel->init(""))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("TaskPanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}


bool TaskContentPanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_iCurrentType=TAG_CURRENTQUEST;

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	CCScale9Sprite* pBorder=SystemData::getScale9SpriteByPlist("taskcontent_bigborder",SystemData::getLayoutValue("taskcontent_bigborder.w"),SystemData::getLayoutValue("taskcontent_bigborder.h"));
	pBorder->setAnchorPoint(CCPointZero);
	pBorder->setPosition(SystemData::getLayoutPoint("taskcontent_bigborder"));
	addChild(pBorder);

	//左边任务列表
	CCScale9Sprite *pLeftborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",SystemData::getLayoutValue("taskcontent_leftmenu_size.w"),SystemData::getLayoutValue("taskcontent_leftmenu_size.h"));
	pLeftborder->setAnchorPoint(CCPointZero);
	pLeftborder->setPosition(SystemData::getLayoutPoint("taskcontent_leftmenu_pos"));
	addChild(pLeftborder);

	//右侧任务列表 
	CCScale9Sprite *pRightborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",SystemData::getLayoutValue("taskcontent_rightmenu_size.w"),SystemData::getLayoutValue("taskcontent_rightmenu_size.h"));
	pRightborder->setAnchorPoint(CCPointZero);
	pRightborder->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu_pos")); 
	addChild(pRightborder);	


	CCSprite* ptitle1=SystemData::getSpriteByPlist("taskcontent_righttitleback");
	ptitle1->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu_title1_pos"));
	addChild(ptitle1);
	CCLabelTTF* plabel1=SystemData::getLabelTTF("task_renwuneirong");
	plabel1->setFontSize(18);
	plabel1->setColor(ccWHITE);
	plabel1->setPosition(ccp(ptitle1->getContentSize().width/2,ptitle1->getContentSize().height/2));
	ptitle1->addChild(plabel1);

	CCSprite* ptitle2=SystemData::getSpriteByPlist("taskcontent_righttitleback");
	ptitle2->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu_title2_pos"));
	addChild(ptitle2);
	CCLabelTTF* plabel2=SystemData::getLabelTTF("task_renwujiangli");
	plabel2->setFontSize(18);
	plabel2->setColor(ccWHITE);
	plabel2->setPosition(ccp(ptitle2->getContentSize().width/2,ptitle2->getContentSize().height/2));
	ptitle2->addChild(plabel2);

	m_pLeftMenu = GeneralMenu::create();
	m_pLeftMenu->setPosition(CCPointZero);
	m_pLeftMenu->setAnchorPoint(CCPointZero);
	addChild(m_pLeftMenu);

	m_pRightMenu= GeneralMenu::create();
	m_pRightMenu->setPosition(CCPointZero);
	m_pRightMenu->setAnchorPoint(CCPointZero);
	addChild(m_pRightMenu);

	//加载顶部按钮
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("taskcontent_button",105,45);
	CCMenuItemSprite *pcurrent =CCMenuItemSprite::create(p1,p1,NULL,this,menu_selector(TaskContentPanel::MenuCallBack));//当前任务按钮
	if(pcurrent)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("taskcontent_currentquest");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pcurrent->setTag(TAG_CURRENTQUEST);
		pcurrent->setAnchorPoint(CCPointZero);
		pcurrent->setPosition(SystemData::getLayoutPoint("taskcontent_currentquest"));
		pLabel->setPosition(ccp(pcurrent->getPositionX()+pcurrent->getContentSize().width/2,pcurrent->getPositionY()+pcurrent->getContentSize().height/2));
		m_pMainMenu->addChild(pcurrent);
		m_pMainMenu->addChild(pLabel);
	} 
	
	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("taskcontent_button",105,45);
	CCMenuItemSprite *paccess =CCMenuItemSprite::create(p2,p2,NULL,this,menu_selector(TaskContentPanel::MenuCallBack));//可接受任务按钮
	if(paccess)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("taskcontent_accessquest");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		paccess->setTag(TAG_ACCESSQUEST);
		paccess->setAnchorPoint(CCPointZero);
		paccess->setPosition(SystemData::getLayoutPoint("taskcontent_accessquest"));
		pLabel->setPosition(ccp(paccess->getPositionX()+paccess->getContentSize().width/2,paccess->getPositionY()+paccess->getContentSize().height/2));
		m_pMainMenu->addChild(paccess);
		m_pMainMenu->addChild(pLabel);
	}

	
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pLeftborder->getContentSize().width-15,pLeftborder->getContentSize().height-40),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(pLeftborder->getPositionX()+5,pLeftborder->getPositionY()+30));
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pLeftMenu->addChild(m_pTableView);

	m_pRightBtnMenu = GeneralMenu::create();
	m_pRightBtnMenu->setAnchorPoint(CCPointZero);
	m_pRightBtnMenu->setPosition(CCPointZero);
	addChild(m_pRightBtnMenu);

	this->runAction(CCSequence::create(CCDelayTime::create(0.02f),CCCallFunc::create(this,callfunc_selector(TaskContentPanel::initUpdateLeft)),NULL));
	 
	return true;
}

void TaskContentPanel::initUpdateLeft()
{
	if (!TaskData::getCurrentTasks().empty())
	{
		m_iCurrentType=TAG_CURRENTQUEST;
		updateLeftList(TAG_CURRENTQUEST);
	}
	else
	{
		m_iCurrentType=TAG_ACCESSQUEST;
		updateLeftList(TAG_ACCESSQUEST);
	}
}

void TaskContentPanel::updateRightMenu()
{
	m_pRightMenu->removeAllChildren();
	if (m_iCurrentQuestID > 0)
	{
		NPCFunctionData::removechildfromparent(m_pRightBtnMenu);
		FirstPart();
		SecondPart();		
	}
	else
	{
		NPCFunctionData::removechildfromparent(m_pRightBtnMenu);

		CCLayerColor *blackLayer = CCLayerColor::create(ccc4(0, 0, 0, 100));
		blackLayer->setContentSize(CCSizeMake(800,437));
		blackLayer->setPosition(CCPointZero);
		m_pRightMenu->addChild(blackLayer);

		std::string str= "";
		if (m_iCurrentType==TAG_ACCESSQUEST)
		{
			str= "taskcontent_warm2";
		}
		else
		{
			str= "taskcontent_warm1";
		}
		CCLabelTTF* pWarm=SystemData::getLabelTTF(str.c_str());
		pWarm->setFontSize(20);
		pWarm->setColor(ccORANGE);

		CCScale9Sprite* psbkg = SystemData::getScale9SpriteByPlist("taskcontent_sbkg",pWarm->getContentSize().width+100,pWarm->getContentSize().height+80);
		psbkg->setPosition(ccp(blackLayer->getContentSize().width/2,blackLayer->getContentSize().height/2));
		blackLayer->addChild(psbkg);
		 
		pWarm->setPosition(ccp(psbkg->getContentSize().width/2,psbkg->getContentSize().height/2));
		psbkg->addChild(pWarm);
	}
}

void TaskContentPanel::FirstPart()
{
	if (m_iCurrentType==TAG_ACCESSQUEST)
	{
		CCLabelTTF* pbutton=SystemData::getLabelTTF("taskcontent_rightbutton1");
		pbutton->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu1_pos"));
		pbutton->setColor(ccWHITE);
		pbutton->setFontSize(18);
		 
		CCMenuItemImage *pbuttonbkg=SystemData::getMenuItemImageByPlist("taskcontent_basebutton");
		pbuttonbkg->setScaleX(1.1f);
		pbuttonbkg->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu1_pos"));
		pbuttonbkg->setTarget(this,menu_selector(TaskContentPanel::MenuCallBack));
		pbuttonbkg->setTag(TAG_SEARCHTASK);
		m_pRightMenu->addChild(pbuttonbkg);
		m_pRightMenu->addChild(pbutton);
	}

	if (m_iCurrentType==TAG_CURRENTQUEST)
	{
		CCLabelTTF* pbutton=SystemData::getLabelTTF("taskcontent_rightbutton2");
		pbutton->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu2_pos"));
		pbutton->setColor(ccWHITE);
		pbutton->setFontSize(18);

		CCMenuItemImage *pbuttonbkg=SystemData::getMenuItemImageByPlist("taskcontent_basebutton");
		pbuttonbkg->setScaleX(1.1f);
		pbuttonbkg->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu2_pos"));
		pbuttonbkg->setTarget(this,menu_selector(TaskContentPanel::MenuCallBack));
		pbuttonbkg->setTag(TAG_DOINGTASK);
		m_pRightMenu->addChild(pbuttonbkg);
		m_pRightMenu->addChild(pbutton);		
	}	

	TaskContentSubPanel* pSubPanel=TaskContentSubPanel::create(m_iCurrentQuestID);
	m_pRightMenu->addChild(pSubPanel);

	TaskRewardPanel* pPanel=TaskRewardPanel::create(m_iCurrentQuestID,2,2);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(SystemData::getLayoutPoint("taskcontent_rightreward_pos"));
	m_pRightMenu->addChild(pPanel);

}

void TaskContentPanel::SecondPart() 
{
	if (m_iCurrentQuestID > 0)
	{
		CCMenuItemImage *pShoes=SystemData::getMenuItemImageByPlist("tasktips_shoes");	
		pShoes->setTarget(this,menu_selector(TaskContentPanel::MenuCallBack));
		pShoes->setTag(TAG_SpeedShoes);
		m_pRightBtnMenu->addChild(pShoes);

		CCLabelTTF* pLabel=SystemData::getLabelTTF("tasktips_shoes_text");
		pLabel->setColor(ccORANGE);
		m_pRightBtnMenu->addChild(pLabel);

		if (m_iCurrentType==TAG_CURRENTQUEST)
		{
			CCLabelTTF* pbutton=SystemData::getLabelTTF("taskcontent_rightbutton3");//放弃任务
			pbutton->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu3_pos"));
			pbutton->setColor(ccWHITE);
			pbutton->setFontSize(18);

			CCMenuItemImage *pbuttonbkg=SystemData::getMenuItemImageByPlist("taskcontent_basebutton");
			pbuttonbkg->setScaleX(1.1f);
			pbuttonbkg->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu3_pos"));
			pbuttonbkg->setTarget(this,menu_selector(TaskContentPanel::MenuCallBack));
			pbuttonbkg->setTag(TAG_GIVEUPTASK);
			m_pRightBtnMenu->addChild(pbuttonbkg);
			m_pRightBtnMenu->addChild(pbutton);

			if (TaskData::getTaskLine(m_iCurrentQuestID)!=Quest::line_Main && TaskData::getTaskState(m_iCurrentQuestID)==Quest::state_NotFinished)
			{
				CCLabelTTF* pQuickLabel = SystemData::getLabelTTF("taskcontent_quickfinishquest");//快速完成
				pQuickLabel->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu4_pos"));
				pQuickLabel->setColor(ccWHITE);
				pQuickLabel->setFontSize(18);

				CCMenuItemImage *pQuickButton=SystemData::getMenuItemImageByPlist("taskcontent_basebutton");
				pQuickButton->setScaleX(1.1f);
				pQuickButton->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenu4_pos"));
				pQuickButton->setTarget(this,menu_selector(TaskContentPanel::quickFinishQuest));
				pQuickButton->setTag(TAG_QuickFinish);
				m_pRightBtnMenu->addChild(pQuickButton);
				m_pRightBtnMenu->addChild(pQuickLabel);
			}
		}
	}
}


void TaskContentPanel::updateLeftList( int tag )
{
	NPCFunctionData::removechildfromparent(m_pRightBtnMenu);
	initButton(tag);
	m_pTableView->reloadData();
	updateRightMenu();
	SecondPart();
}

void TaskContentPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==TAG_ACCESSQUEST)
		{
			if (m_iCurrentType==tag)
			{
				return;
			}
			else
			{				
				m_iCurrentType=tag;
				updateLeftList(tag);
			}			
		}
		else if (tag==TAG_CURRENTQUEST)
		{
			if (m_iCurrentType==tag)
			{
				return;
			}
			else
			{
				m_iCurrentType=tag;
				updateLeftList(tag);
			}
		}
		else if(tag==TAG_DOINGTASK)
		{			
			int NPCID=0;
			const int state = TaskData::getTaskState(m_iCurrentQuestID);
			if (state==Quest::state_Finished)
			{
				LuaData::getProp(LuaData::QUEST,m_iCurrentQuestID,"npc_tgt",NPCID);
				GameData::s_user->m_pGhostManager->gotoGhostPos(NPCID,"npcs");	
			}	
			else if (state==Quest::state_NotFinished)
			{
				int type = Quest::type_Invalid;
				LuaData::getProp(LuaData::QUEST,m_iCurrentQuestID,"type",type);
				int datax = 0, datay = 0, dataz = 0;
				TaskData::getTaskExData(m_iCurrentQuestID, datax, datay, dataz);
				if (type == Quest::type_MonsterKill)//如果是杀指定怪任务
				{
					GameData::s_user->m_pGhostManager->gotoGhostPos(datax,"monsters",GHOST_TYPE_MONSTER);
				}
				else
				{
					LuaData::getProp(LuaData::QUEST,m_iCurrentQuestID,"npc_tgt",NPCID);
					GameData::s_user->m_pGhostManager->gotoGhostPos(NPCID,"npcs");
				}
			}
			CloseSelf(NULL);
		}
		else if(tag==TAG_GIVEUPTASK)
		{
			NPCFunctionData::GiveUpQuest(m_iCurrentQuestID);			
		}
		else if (tag==TAG_SpeedShoes)
		{
			NPCFunctionData::getShoesFunc(m_iCurrentQuestID,TAG_GOTONPC);
		}
		else if(tag==TAG_SEARCHTASK)
		{		
			int NPCID=0;
			LuaData::getProp(LuaData::QUEST,m_iCurrentQuestID,"npc_src",NPCID);		
			GameData::s_user->m_pGhostManager->gotoGhostPos(NPCID,"npcs");

			if (false)
			{
				NPCFunctionData::AcceptQuest(m_iCurrentQuestID);	
			}
			else
			{
				CloseSelf(NULL);
			}
		}
	}
}


void TaskContentPanel::initButton(int tag)
{	
	CCMenuItemImage *p=(CCMenuItemImage *)(m_pMainMenu->getChildByTag(tag));
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("taskcontent_button.sel",105,45);
	p->setNormalImage(p1);
	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("taskcontent_button",105,45);
	if (tag==TAG_CURRENTQUEST)
	{
		CCMenuItemImage *pItem=(CCMenuItemImage *)(m_pMainMenu->getChildByTag(TAG_ACCESSQUEST));
		pItem->setNormalImage(p2);
	}
	else
	{
		CCMenuItemImage *pItem=(CCMenuItemImage *)(m_pMainMenu->getChildByTag(TAG_CURRENTQUEST));
		pItem->setNormalImage(p2);
	}
}


cocos2d::CCSize TaskContentPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("taskcontent_leftmenu_size").width-20, mHeight);
}

cocos2d::extension::CCTableViewCell* TaskContentPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCMenuEx* pMenu = CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

		initQuestList(pMenu);	
	}
	return cell;
}

unsigned int TaskContentPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void TaskContentPanel::CloseSelf(CCObject* pSender)
{
	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
}

void TaskContentPanel::initQuestList(CCMenuEx* pMenu)
{
	int Height=0;
	bool HasFirstQuest=false;
	if (m_iCurrentType==TAG_CURRENTQUEST)
	{
		Height=(TaskData::getCurrentTasks().size()+4)*35;
	}
	else if (m_iCurrentType==TAG_ACCESSQUEST)
	{
		Height=(TaskData::getAccessTasks().size()+4)*35;
	}
	mHeight=Height;

	int questType[Quest::line_Max-1]={
		Quest::line_Main,Quest::line_Daily,Quest::line_Honor,Quest::line_Exp,Quest::line_Money,Quest::line_Emigrated
	};	

	for (int i=0;i<Quest::line_Max-1;i++)
	{
		CCObject *pObject;
		
		CCPoint Pos=ccp(SystemData::getLayoutSize("taskcontent_leftmenu_size").width/2,Height-20);

		CCArray* pMainArray=getTypeQuest(questType[i]);
		int count=0;
		CCARRAY_FOREACH(pMainArray,pObject)
		{
			CCMenuItemSprite* pItem=(CCMenuItemSprite*)pObject;
			if (!HasFirstQuest)
			{
				m_iCurrentQuestID=pItem->getTag();
				HasFirstQuest=true;
				m_pCurrentQuestSprite=pItem;
				CCSprite* ptitle=SystemData::getSpriteByPlist("taskcontent_titlebkgduan");
				ptitle->setPosition(ccp(m_pCurrentQuestSprite->getContentSize().width/2,m_pCurrentQuestSprite->getContentSize().height/2));
				ptitle->setTag(10);
				m_pCurrentQuestSprite->addChild(ptitle,-10);
			}
			pItem->setPosition(ccp(Pos.x,Pos.y-40*count));
			pMenu->addChild(pItem);
			count++;
		}
		if (count==0 && !HasFirstQuest)
		{
			m_iCurrentQuestID=-1;
		}
		Height=Height-(count)*40;
	}
}

CCArray * TaskContentPanel::getTypeQuest( int type )
{
	std::string questLabel[Quest::line_Max-1]={
		"task_zhuxian","task_meiri","task_rongyu","task_jingyan","task_jinbi","task_caishen"
	};
	CCArray *pArray=CCArray::create();
	if (m_iCurrentType==TAG_CURRENTQUEST)
	{
		const IDVector &quests = TaskData::getCurrentTasks();
		for (int i = 0; i < (int)quests.size(); i++)
		{
			CCLabelTTF *ptype=SystemData::getLabelTTF(questLabel[type-1]);
			ptype->setColor(ccYELLOW);
			ptype->setFontSize(20);
			ptype->setAnchorPoint(ccp(0,0.5));
			ptype->setPosition(ccp(-25,0));
			if (type == TaskData::getTaskLine(quests[i]))
			{
				std::string str;
				LuaData::getProp(LuaData::QUEST,quests[i],"name",str);	
				CCLabelTTF *pLabel=CCLabelTTF::create(str.c_str(),"微软雅黑",20);
				pLabel->setAnchorPoint(ccp(0,0.5));
				pLabel->setPosition(ccp(75,ptype->getContentSize().height/2));
				ptype->addChild(pLabel);
				ptype->setContentSize(ccp(ptype->getContentSize().width+pLabel->getContentSize().width,ptype->getContentSize().height));
				CCMenuItemSprite* pItem=CCMenuItemSprite::create(ptype,NULL,NULL,this,menu_selector(TaskContentPanel::QuestCallBack));
				pItem->setTag(quests[i]);
				pArray->addObject(pItem);
			}
		}
	}
	else if (m_iCurrentType==TAG_ACCESSQUEST)
	{
		const IDVector &quests = TaskData::getAccessTasks();
		for (int i = 0; i < (int)quests.size(); i++)
		{
			CCLabelTTF *ptype=SystemData::getLabelTTF(questLabel[type-1]);
			ptype->setColor(ccYELLOW);
			ptype->setFontSize(20);
			ptype->setAnchorPoint(ccp(0,0.5));
			ptype->setPosition(ccp(-25,0));
			if (type == TaskData::getTaskLine(quests[i]))
			{
				std::string str;
				LuaData::getProp(LuaData::QUEST,quests[i],"name",str);
				CCLabelTTF *pLabel=CCLabelTTF::create(str.c_str(),"微软雅黑",20);
				pLabel->setAnchorPoint(ccp(0,0.5));
				pLabel->setPosition(ccp(75,ptype->getContentSize().height/2));
				ptype->addChild(pLabel);
				ptype->setContentSize(ccp(ptype->getContentSize().width+pLabel->getContentSize().width,ptype->getContentSize().height));
				CCMenuItemSprite* pItem=CCMenuItemSprite::create(ptype,NULL,NULL,this,menu_selector(TaskContentPanel::QuestCallBack));
				pItem->setTag(quests[i]);
				pArray->addObject(pItem);
			}
		}
	}
	return pArray;
}

void TaskContentPanel::handleEvent( int channel )
{	
	if(channel == EventProtocol::EVENT_TASK_RECEIVED)
	{
		//CCLog("Event Recieve");
		updateLeftList(m_iCurrentType);
	}
}

void TaskContentPanel::QuestCallBack( CCObject* pSender )
{
	CCMenuItemSprite* pNode = dynamic_cast<CCMenuItemSprite*>(pSender);
	if(pNode)
	{
		if (m_pCurrentQuestSprite)
		{
			m_pCurrentQuestSprite->removeChildByTag(10);
		}
		m_pCurrentQuestSprite=pNode;
		CCSprite* ptitle=SystemData::getSpriteByPlist("taskcontent_titlebkgduan");
		ptitle->setPosition(ccp(m_pCurrentQuestSprite->getContentSize().width/2,m_pCurrentQuestSprite->getContentSize().height/2));
		ptitle->setTag(10);
		m_pCurrentQuestSprite->addChild(ptitle,-10);

		m_iCurrentQuestID=pNode->getTag();
		initButton(m_iCurrentType);
		updateRightMenu();
	}
}

void TaskContentPanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		UserItem* pItem=(UserItem*)pImage->getUserData();
		Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
	}
}

void TaskContentPanel::quickFinishQuest( CCObject* pSender )
{
	Game::getGameUI()->showFloatPanel(FloatPanelType::Quest_QuickFinish);
	if (Game::getGameUI()->getPanel(TAG_FLOAT_PANEL))
	{
		FloatPanel* pPanel = dynamic_cast<FloatPanel*>(Game::getGameUI()->getPanel(TAG_FLOAT_PANEL));
		pPanel->setHandler(this,floatpanel_selector(TaskContentPanel::quickFinishCB));
	}
}

void TaskContentPanel::quickFinishCB(int tag)
{
	if (tag==0)
	{
		NPCFunctionData::QuickQuest(m_iCurrentQuestID);
	}
}



///-------------------------------------------------------------------------------------------------------------------------------///


TaskContentSubPanel::TaskContentSubPanel():
	m_pTableView(NULL),
	mQuestID(0)
{

}

TaskContentSubPanel::~TaskContentSubPanel()
{

}

TaskContentSubPanel* TaskContentSubPanel::create( int qid )
{
	TaskContentSubPanel* pPanel = new TaskContentSubPanel();
	if(pPanel && pPanel->init(qid))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("TaskContentSubPanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

bool TaskContentSubPanel::init( int qid )
{	
	mQuestID = qid;
	m_pTableView = CCTableViewEx::create(this,SystemData::getLayoutSize("taskcontent_rightmenusub_size"),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(SystemData::getLayoutPoint("taskcontent_rightmenusub_pos"));
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(m_pTableView);

	return true;
}

cocos2d::CCSize TaskContentSubPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("taskcontent_rightmenusub_size").width,mHeight);
}

cocos2d::extension::CCTableViewCell* TaskContentSubPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCLayer* player=CCLayer::create();
		player->setAnchorPoint(CCPointZero);
		player->setPosition(CCPointZero);
		cell->addChild(player);

		CCMenuEx* pMenu = CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		player->addChild(pMenu);

		addContent(player,pMenu);

	}
	return cell;
}

unsigned int TaskContentSubPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void TaskContentSubPanel::addContent( CCLayer* pLayer, CCMenuEx* pMenu )
{
	//文字加layer 按钮加menu
	mHeight=0;
	std::string str;
	LuaData::getProp(LuaData::QUEST,mQuestID,"des",str);
	CCLabelTTF *pLabel=CCLabelTTF::create(str.c_str(),"微软雅黑",16);
	pLabel->setAnchorPoint(ccp(0,1));
	pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel->setDimensions(CCSizeMake( SystemData::getLayoutSize("taskcontent_rightmenusub_size").width-30,0));
	pLayer->addChild(pLabel);

	CCString *pStr=NPCFunctionData::getCString(mQuestID,12);			
	CCLabelTTF *pLabel1=CCLabelTTF::create(pStr->getCString(),"微软雅黑",16);
	pLabel1->setAnchorPoint(ccp(0,1));
	pLabel1->setHorizontalAlignment(kCCTextAlignmentLeft);
	pLabel1->setDimensions(CCSizeMake( SystemData::getLayoutSize("taskcontent_rightmenusub_size").width-30,0));
	pLayer->addChild(pLabel1);

	mHeight=pLabel->getContentSize().height+pLabel1->getContentSize().height+130;

	pLabel->setPosition(ccp(0,mHeight-20));
	pLabel1->setPosition(ccp(0,mHeight-pLabel->getContentSize().height-20));
}
