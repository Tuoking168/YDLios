#include "GameRole.h"
#include <queue>
#include <fstream>
#include <cmath>
#include "MsgItem.h"
#include "MsgScene.h"
#include "EntityDefinition.h"
#include "UserDataModule.h"
#include "CCActionDestroy.h"
#include "SceneDefinition.h"
#include "CombatDefinition.h"
#include "EffectDefinition.h"
#include "CCFlashAnimation.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/Userdata.h"
#include "userdata/SystemData.h"
#include "userdata/StaticData.h"
#include "userdata/HeroData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/NPCFunctionData.h"
#include "userdata/TaskData.h"
#include "userdata/netdata/AutoAttack.h"
#include "userdata/UserPetData.h"
#include "userdata/mapdata/PixesMap.h"
#include "userdata/skilldata/SkillEffect.h"
#include "userdata/statetimer/FightingState.h"
#include "userdata/skilldata/SkillState.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/netdata/NetItem.h"

#include "network/NetProtocol.h"
#include "network/HandleMessage.h"

#include "ext/AstarPathfinder.h"
#include "ext/AstarPathfinder.h"

#include "event/EventProtocol.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/ControlPanel.h"
#include "scene/NotificationHelper.h"
#include "scene/SceneHelper.h"
#include "scene/panel/functionPanel/CharacterPanel.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "res/AudioLoader.h"

#include "utils/StringUtils.h"
#include "utils/TestUtils.h"

#include "logic/CPUpdateFunctor/CPUpdateFunctorManager.h"
#include "logic/ItemOperator.h"

#include "AreaChecker/AreaChecker.h"



const float RtoA = (float)(180.0/3.141592653);
const float eps = (float)(1E-6);

const int SegmentLength = 20;
const int ReachDistance = 3;
const int ReachNPCDistanceNormal = 5;
const int ReachNPCDistanceQuest = 2;

bool m_visit[305][305];

const int AUTO_FIGHT_TIME_INTERVAL = 500;
const int MAX_CAST_RANGE_BY_TILE_X = 7;
const int MAX_CAST_RANGE_BY_TILE_Y = 7;

static CCPoint convertToMapTile( const CCPoint &touchPt )
{
	CCPoint mapPos = touchPt;
	mapPos = SystemData::convertToMapPosition(mapPos);
	mapPos = ccp((mapPos.x/PixesMap::TILE_WIDTH), (mapPos.y/PixesMap::TILE_HEIGHT));
	return mapPos;
}

//////////GameRole/////////////////////////////////////////////
GameRole::GameRole()
: mMoveStep(0)
, mMoveStepRes(0)
, m_pPathFinder(NULL)
, m_bAutoMove(false)
, m_aimGhost(NULL)
, m_isMouseSequence(false)
, m_isMoveAndAttack(false)
, m_isMousePickUp(false)
, m_nTargetGhostId(-1)
, m_bCrossAutoMove(false)
, m_nTargetGhostType(-1)
, m_nLeftStep(-1)
, m_autoSkillType(-1)
, m_bMovingAndPick(false)
, m_bEasyAi(false)
, m_bEasyAiKeepAttack(false)
, m_bIsInControlPanel(false)
, m_nTargetX(0)
, m_nTargetY(0)
, m_bTranfering(false)
,m_iExpCount(0)
,m_iHonorCount(0)
,m_iMoneyCount(0)
,m_iCurrentPetiid(0)
,m_bMyBooth(true)
,m_iTargetMoney1(0)
,m_iTargetMoney2(0)
,m_bQuestDoing(false)
,mLastInPeaceArea(false)
,mMoveToTargetByButton(false)
,m_iTargetSid(0)
,m_irangex(MAX_CAST_RANGE_BY_TILE_X)
,m_irangey(MAX_CAST_RANGE_BY_TILE_Y)
,m_bBuyShoesTips(false)
{
	for (int i=0;i<17;i++)
	{
		for (int j=0;j<5;j++)
		{
			m_pStoneArray[i][j]=NULL;
		}
	}
	m_pMarketItemList.clear();
	m_pTradeItemList.clear();

	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.addEventListener(CPEventName::NPC_REQUESTDATA, this);
	CPEvtDispatcher.addEventListener(CPEventName::NPC_REQUESTINSTANCEDATA, this);
}

GameRole::~GameRole()
{
	if (m_pPathFinder)
	{
		delete m_pPathFinder;
	}
}

GameRole* GameRole::create(long time)
{
	GameRole* pGameRole = new GameRole;
	pGameRole->m_initTime = time;
	return pGameRole;
}

bool GameRole::init()
{
	if(!HeroAvatar::init())
	{
		return false;
	}
	m_nAutoFightTime = GameData::s_user->getTime();

	return true;
}

void GameRole::release()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.removeEventListener(CPEventName::NPC_REQUESTDATA, this);
	CPEvtDispatcher.removeEventListener(CPEventName::NPC_REQUESTINSTANCEDATA, this);
	HeroAvatar::release();
}

void GameRole::walk(int dir, int newx, int newy)
{
	mMoveStep++;
	MsgPlayerWalkRequest* walkreq = new MsgPlayerWalkRequest;
	walkreq->dir = dir;
	walkreq->posx = newx;
	walkreq->posy = newy;
	walkreq->mMoveStep = mMoveStep;
	walkreq->SkipTime = getSkipTime();
	HandleMessage::sendMessage(walkreq);
}

void GameRole::run(int dir, int newx, int newy)
{
	mMoveStep++;
	MsgPlayerRunRequest* runreq = new MsgPlayerRunRequest;
	runreq->dir = dir;
	runreq->posx = newx;
	runreq->posy = newy;
	runreq->mMoveStep = mMoveStep;
	runreq->SkipTime = getSkipTime();
	HandleMessage::sendMessage(runreq);
}

void GameRole::moveCheckTimerReset()
{
	m_moveTime = GameData::s_user->getTime();
}

int GameRole::getSkipTime()
{
	int t = (int)(GameData::s_user->getTime() - m_initTime);
	return t;
}

void GameRole::moveCheck()
{
	if (mMoveStepRes == mMoveStep)
	{
		moveCheckTimerReset();
		const short& dir=getDirection();
		if (mTx != m_serverTx || mTy != m_serverTy || dir != m_serverDir)
		{
			if (dir != m_serverDir && mTx == m_serverTx && mTy == m_serverTy)
			{
				setDirection(m_serverDir);
			}
			else
			{
				forceMoveTo(m_serverDir, m_serverTx, m_serverTy);
			}
			CCLog("force move 1");
		}
	}
	else
	{
		int st = GameData::s_user->getTime() - m_moveTime;
		if (st > 3000)
		{
			moveCheckTimerReset();
			mMoveStep = mMoveStepRes;
			const short& dir=getDirection();
			if (mTx != m_serverTx || mTy != m_serverTy || dir != m_serverDir)
			{
				CCLog("force move st: %d, resstep: %d, mmovestep: %d", st, mMoveStepRes, mMoveStep);
				forceMoveTo(m_serverDir, m_serverTx, m_serverTy);
			}
		}
	}
}

void GameRole::update( float dt )
{
	if (m_pBodySprite == NULL)
	{
		return;
	}

	HeroAvatar::update(dt);
	moveCheck();
	checkOnPortals();
	// checkAutoMove();
	int curTime = GameData::s_user->millisecondNow();
	// 攻速0保持原始500ms挂机轮询; 有攻速装备时缩短到50ms, 保证高攻速下AI及时出手
	int autoFightInterval = (CombatData[Combat::prop_Attack_Speed] > 0) ? 50 : AUTO_FIGHT_TIME_INTERVAL;
	if(curTime - m_nAutoFightTime > autoFightInterval)
	{
		m_nAutoFightTime = curTime;
		easyAi();
	}
	refreshIntoPeaceArea();
}

void GameRole::moveOneStep()
{
	HeroAvatar::moveOneStep();

	if (mMoveStep == 0)
	{
		m_moveTime = GameData::s_user->getTime();
	}

	const short &dir = getDirection();
	if(m_state == AVATAR_ACTION_RUN)
	{
		run(dir, mTx, mTy);
	}
	else if(m_state == AVATAR_ACTION_WALK)
	{
		walk(dir, mTx, mTy);
	}
}

void GameRole::handleMoveRes(int nstep, int movetype ,int dir, int x, int y)
{
	if (mMoveStepRes < nstep && nstep > 0)
	{
		mMoveStepRes = nstep;
	}
	m_serverDir = dir;
	m_serverTx = x;
	m_serverTy = y;
	if (movetype == Avatar_Collide)
	{
		mMoveStep++;
		handleCollideRes(x, y, dir);
	}
	CCLog(">>>sever move %d, %d %d %d", nstep, m_serverDir, x, y);
	moveCheckTimerReset();

	if (UserData::getIntData(HeroData::getPID(), CPUserData::PICKITEM_AUTOPICK_ON) != 0)
	{
		GhostManager* pGhostManager = GameData::getGhostManager();
		Ghost *pGhost = pGhostManager != NULL ? pGhostManager->getTypeGhostAtPosition(GHOST_TYPE_MAP_ITEM, x, y) : NULL;
		if(pGhost)
		{
			CCLog(">>>pick up %d", pGhost->mID);
			/*if (canPickItem(pGhost))
			{
				pickUp(pGhost->mID);
			}*/
			pickUp(pGhost->mID);
		}
	}
}

int GameRole::getThatWayDirection(CCPoint touchPos)
{
	//caculate the angle , and get the direction.
	if(m_bIsInControlPanel)
	{
		return SystemData::getDirection(ccp(SystemData::size_x/2,SystemData::size_y/2),CCDirector::sharedDirector()->convertToUI(touchPos));
	}
	else
	{
		return SystemData::getDirection(CCDirector::sharedDirector()->convertToUI(m_sceenPosition), CCDirector::sharedDirector()->convertToUI(touchPos));
	}
}

int GameRole::getThatWayState(CCPoint touchPos)
{
	//set the state with the distance
	if(m_bIsInControlPanel)
	{
		if(ControlPanel::m_timetouchkeep < 0.5f)
		{
			return AVATAR_ACTION_WALK;
		}
		else
		{
			return AVATAR_ACTION_RUN;
		}
	}
	else
	{
		touchPos.x = touchPos.x + getMapPosition().x - m_sceenPosition.x;
		touchPos.y = -touchPos.y + getMapPosition().y + m_sceenPosition.y;
		float dis = ccpDistance(touchPos, getMapPosition());
		if(dis < 60)
		{
			return AVATAR_ACTION_WALK;
		}
		else
		{
			return AVATAR_ACTION_RUN;
		}
	}
}

void GameRole::touchScreenBegin(const CCPoint& point)
{
	CPEventHelper::dispatcher(CPEventName::UI_CHANGE, "GameRole::touchScreenBegin", "");
	stopAutoMoving();
	AutoAttack::closeAutoAttack();

	m_isMouseSequence = true;
	m_isMousePickUp = true;
	m_MousePoint = point;

	if (m_state != AVATAR_ACTION_WALK &&
		m_state != AVATAR_ACTION_RUN)
	{
		updateMoveStateByTouch();
	}

	tryToMine(point);
}

void GameRole::touchScreenMoved(const CCPoint& point)
{
	m_isMouseSequence = true;
	m_isMousePickUp = true;
	m_MousePoint = point;
}

void GameRole::touchScreenEnded()
{
	m_isMouseSequence = false;
	m_bIsInControlPanel = false;
	
	if (m_state != AVATAR_ACTION_MINE)
	{
		setState(AVATAR_ACTION_IDLE);
	}
}

void GameRole::updateMoveStateByTouch()
{
	//set the state with the distance
	int state = getThatWayState(m_MousePoint);
	if (state != AVATAR_ACTION_IDLE)
	{
		setState(state, getThatWayDirection(m_MousePoint));
	}	
}

bool GameRole::checkPassObstacle( short &state, int &dir )
{
	//check the two adjacent directions, if either could be gone through
	int sideDir = (dir+7)%8;
	int sideX = mTx + tile_step[sideDir][0];
	int sideY = mTy + tile_step[sideDir][1];
	if(!isBlocked(sideX,sideY))
	{
		state = AVATAR_ACTION_WALK;
		dir = sideDir;
		return true;
	}
	sideDir = (dir+1)%8;
	sideX = mTx + tile_step[sideDir][0];
	sideY = mTy + tile_step[sideDir][1];
	if(!isBlocked(sideX,sideY))
	{
		state = AVATAR_ACTION_WALK;
		dir = sideDir;
		return true;
	}
	state = AVATAR_ACTION_IDLE;
	return false;
}

void GameRole::clickSkills(int skillID)
{
	if (SKILL_TYPE_LieYanChongSheng != skillID/10)
	{
		AutoAttack::closeAutoAttack();
	}
	if (skillID > 0)
	{
		if(m_skill->overLimit(skillID))
		{
			return;
		}

		if (testManaAndCD(skillID, true, true))
		{
			startCastSkill(skillID);
		}
	}
	else
	{
		if (!m_isMoveAndAttack &&
			!m_bEasyAiKeepAttack &&
			!isEasyAIOn())
		{
			m_autoSkillType = -1;
			setEasyAI(true);
		}
	}
}

bool GameRole::startCastSkill(int skillID)
{
	if (isDead())
	{
		m_bEasyAi = false;
		m_bAutoMove = false;
		m_isMoveAndAttack = false;
		m_bMovingAndPick = false;
		return false;
	}

	const int typeEnum = skillID/10;
	// peace area test
	if (typeEnum == SKILL_TYPE_HuoQiang &&
		isInPeaceArea())
	{
		m_bEasyAi = false;
		m_bAutoMove = false;
		m_isMoveAndAttack = false;
		m_bMovingAndPick = false;
		CPEventHelper::uiNotify("GameRole::startCastSkill", "", Error::Scene_Peace_Area);
		return false;
	}

	int newDirection = getDirection();
	const bool skillNeedTarget = SkillEffect::isSkillNeedTarget(skillID);
	if (skillNeedTarget)
	{
		if (!m_aimGhost &&
			!changeToNearestTarget())
		{
			return false;
		}
		
		// alive test
		if (m_aimGhost->isDead())
		{
			return false;
		}

		// plant test
		if (m_aimGhost->mType == GHOST_TYPE_PLANT)
		{
			changeTheAim(m_aimGhost);
			return false;
		}
		else if (!testSkillDistance(skillID, ccp(m_aimGhost->mTx, m_aimGhost->mTy)))
		{
			return false;
		}

		newDirection = SystemData::getDirection(ccp(mTx, mTy), ccp(m_aimGhost->mTx, m_aimGhost->mTy));
	}
	else
	{
		if (m_aimGhost &&
			SkillEffect::needTurnToTarget(skillID))
		{
			newDirection = SystemData::getDirection(ccp(mTx, mTy), ccp(m_aimGhost->mTx, m_aimGhost->mTy));
		}
		else
		{
			const int typeEnum = skillID/10;
			if (typeEnum == SKILL_TYPE_HuoQiang)
			{
				newDirection = SystemData::getDirection(ccp(mTx, mTy), ccp(SkillState::_s_state_fire_wall_position.x, SkillState::_s_state_fire_wall_position.y));
			}
		}
	}

	// state list test
	if (!m_statelist.empty())
	{
		return false;
	}

	// check if the skill num is over its limit now
	if(m_skill->overLimit(skillID))
	{
		return false;
	}

	// mana and cd test
	if (!testManaAndCD(skillID, true, false))
	{
		return false;
	}

	// turn direction
	const int myDir = getDirection();
	if (myDir != newDirection)
	{
		turnDirection(newDirection);
	}

	// use skill
	if(skillNeedTarget)
	{
		useSkillRequest(skillID, m_aimGhost->mTx, m_aimGhost->mTy, m_aimGhost->mID);
	}
	else
	{
		if (typeEnum == SKILL_TYPE_HuoQiang &&
			SkillState::_s_state_pre_fire_wall)
		{
			if (isInPeaceArea(SkillState::_s_state_fire_wall_position.x, SkillState::_s_state_fire_wall_position.y))
			{
				SkillState::_s_state_pre_fire_wall = false;
				return false;
			}
			useSkillRequest(skillID, SkillState::_s_state_fire_wall_position.x, SkillState::_s_state_fire_wall_position.y, mID);
		}
		else
		{
			useSkillRequest(skillID, mTx, mTy, mID);
		}
	}
	return true;
}

void GameRole::changeTheAim(AliveGhost* aim)
{
	// aim can be NULL
	if (m_aimGhost)
	{
		if (m_aimGhost->mType == GHOST_TYPE_MONSTER ||
			m_aimGhost->mType == GHOST_TYPE_PLANT)
		{
			m_aimGhost->refreshNameLabel(false);
		}
		m_aimGhost->toBeSelected(false);
	}

	const bool theSameAim = (m_aimGhost && m_aimGhost == aim);
	if (theSameAim && 
		(m_aimGhost->mType == GHOST_TYPE_MONSTER
		|| m_aimGhost->mType == GHOST_TYPE_PLAYER
		|| m_aimGhost->mType == GHOST_TYPE_SLAVE
		|| m_aimGhost->mType == GHOST_TYPE_PET))
	{
		//if (!GameData::getGhostManager()->isTargetFriendly(m_aimGhost))
		{
			setEasyAI(true);
			m_isMoveAndAttack = true;
		}
	}

	m_aimGhost = aim;
	int bossFlag = 0;
	if (m_aimGhost)
	{
		bool needShowName = true;
		m_aimGhost->toBeSelected(true);
		if (m_aimGhost->mType == GHOST_TYPE_MONSTER)
		{
			if (UserData::getIntData(HeroData::getPID(), CPUserData::SHOW_MONSTERNAME) == 0)
			{
				needShowName = false;
			}

			if (!GameData::getGhostManager()->isTargetFriendly(m_aimGhost))
			{
				if (HeroData::getJob() == UserData::CARRER_ZS)
				{
					int selFlag = 0;
					StaticData::getMonsterSelFlag(m_aimGhost->mStaticID, selFlag);
					if (selFlag == 0)
					{
						m_isMoveAndAttack = true;
					}
				}

				if (m_bQuestDoing && !NPCFunctionData::checkIsQuestMonster(m_aimGhost->getDress(AVATAR_TYPE_CLOTH)))
				{
					m_aimGhost = NULL;
					Game::getGameUI()->hideTargetPanel();
					return;
				}
			}

			if(m_aimGhost)
			{
				StaticData::getMonsterBossFlag(m_aimGhost->mStaticID, bossFlag);
			}
		}
		else if (m_aimGhost->mType == GHOST_TYPE_PLANT)
		{
			m_isMoveAndAttack = true;
		}
		else if (m_bQuestDoing)
		{
			m_aimGhost = NULL;
			Game::getGameUI()->hideTargetPanel();
			return;
		}

		m_aimGhost->refreshNameLabel(needShowName);
		if (!theSameAim)
		{
			Game::getGameUI()->hideTargetPanel();
		}
	}

	if (bossFlag)
	{
		CPEventHelper::setEventStringData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2, "Boss");
	}
	CPEventHelper::dispatcher(CPEventName::UI_NOTIFY, "GameRole::changeTheAim", "");

	if(m_isMoveAndAttack && m_state == AVATAR_ACTION_IDLE)
	{
		setNextStateCallback();
	}
}

void GameRole::changeToPlayerAnim( AliveGhost *player )
{
	GameData::s_user->m_pMainRole->changeTheAim(player);
	GameData::s_user->m_pMainRole->m_iTargeteid = player->mID;
	Game::getGameUI()->showTargetPanel();
	MsgGetSceneEntityInfoRequest* request = new MsgGetSceneEntityInfoRequest;
	request->eid = player->mID;
	HandleMessage::sendMessage(request);
}

void GameRole::setNextStateCallback()
{
	bool needCallNext = false;
	if (m_statelist.empty())
	{
		if (m_isMouseSequence)
		{
			executeMouseSequence();
		}
		else if (m_isMoveAndAttack)
		{
			executeMoveAndAttack();
		}
		else if (m_autoSkillType != -1)
		{
			executeAutoSkill();
		}
		else if(m_bAutoMove)
		{
			executeAutoMove(needCallNext);
		}
		else
		{
			if (m_state==AVATAR_ACTION_MINE)
			{
				m_state = AVATAR_ACTION_MINE;
			}
			else
			{
				m_state = AVATAR_ACTION_IDLE;
			}
		}
	}
	else 
	{
		executeStateList();
		needCallNext = (m_state == AVATAR_ACTION_IDLE);
	}

	//
	if (needCallNext)
	{
		setNextStateCallback();
	}
	else
	{
		runAnimation();
	}
}

void GameRole::executeMouseSequence()
{
	m_state = getThatWayState(m_MousePoint);
	if (m_state != AVATAR_ACTION_IDLE)
	{
		int dir = getThatWayDirection(m_MousePoint);
		checkBlockedMove(m_state, dir);
		setDirection(dir);
	}
}

void GameRole::executeMoveAndAttack()
{
	if (!m_aimGhost || m_aimGhost->isDead())
	{
		m_state = AVATAR_ACTION_IDLE;
		m_isMoveAndAttack = false;
	}
	else
	{
		const CCPoint &pt = faceFightPoint();
		if (m_aimGhost->mType == GHOST_TYPE_PLANT)
		{
			if (!autoMoveOneStep(pt, m_state))
			{
				m_state = AVATAR_ACTION_IDLE;
				startPickPlant(m_aimGhost->mID);
			}
		}
		else
		{
			const int skillID = getFightSkill(0);
			if (SkillEffect::isShortRange(skillID))
			{
				if (!autoMoveOneStep(pt, m_state))
				{
					m_state = AVATAR_ACTION_IDLE;
					startCastSkill(skillID);
				}
			}
			else
			{
				m_state = AVATAR_ACTION_IDLE;
				startCastSkill(skillID);
			}
		}
	}
}

void GameRole::executeAutoSkill()
{
	if (!m_aimGhost || m_aimGhost->isDead())
	{
		m_autoSkillType = -1;
		m_state = AVATAR_ACTION_IDLE;
		m_isMoveAndAttack = false;
		return;
	}
	
	if (!startCastSkill(m_autoSkillType))
	{
		m_state = AVATAR_ACTION_IDLE;
		m_isMoveAndAttack = false;
	}
}

void GameRole::executeAutoMove( bool &needOneStep )
{
	if(m_nTargetGhostId == -1)
	{
		Ghost* targetGhost = GameData::s_user->m_pGhostManager->getGhostAtPosition(m_nTargetX,m_nTargetY);
		if(targetGhost)
		{
			m_nTargetGhostId = targetGhost->mID;
			m_nTargetGhostType = targetGhost->mType;
		}
	}

	if(isReached())
	{
		if (m_nTargetGhostId != -1)
		{
			if(m_nTargetGhostType == GHOST_TYPE_NPC)
			{
				GameData::s_user->m_nNpcTalkId=m_nTargetGhostId;
				GameUI *panel = Game::getGameUI();
				if (panel)
				{
					panel->showPanel(TAG_TALK_PANEL);
				}
			}	
			setQuestDoing(false);
			m_nTargetGhostId = -1;
		}

		if (m_nTargetGhostType == GHOST_TYPE_MONSTER)
		{
			if (m_iTargetSid!=0)
			{
				changeTheAim((AliveGhost*)GameData::s_user->m_pGhostManager->getGhostBySid(m_iTargetSid));
				m_iTargetSid=0;
			}
			setEasyAI(true);
		}

		if (m_nTargetGhostType == GHOST_TYPE_MINE)
		{
			//??????????
			CCPoint mapos ;
			mapos.x = m_nTargetX;
			mapos.y = m_nTargetY;
			tryToMineByMapPos(mapos);

			//???????
			CCPoint rolepos;
			rolepos.x = mTx;
			rolepos.y = mTy;
			int dir = SystemData::getDirection(rolepos,mapos);
			setDirection(dir);
		}

		m_bAutoMove = false;
		mMoveToTargetByButton = false;
		m_nLeftStep = -1;
		if (m_state!=AVATAR_ACTION_MINE)
		{
			m_state = AVATAR_ACTION_IDLE;
		}
		m_pPathFinder->clear();
	}
	else
	{
		//?????????????????????????????????????????????????????????????????????
		//?????????????????????????????????????????????????????????
		if(m_pPathFinder->getLeftStepNum() >= 1)
		{
			const short nextDir = m_pPathFinder->getNextStep();
			m_state = AVATAR_ACTION_WALK;
			//??????????????????????????????????
			if(m_pPathFinder->hasNextStep() && m_pPathFinder->watchNextStep()==nextDir)
			{
				m_pPathFinder->getNextStep();//???????????
				m_state = AVATAR_ACTION_RUN;
			}
			setDirection(nextDir);
		}
		else
		{
			nextPathSegment();
			needOneStep = true;
			return;
		}
		GameUI *panel = Game::getGameUI();
		if (panel)
		{
			panel->hidePanel(TAG_TALK_PANEL);
			panel->hidePanel(TAG_TASK_PANEL);
		}
	}
	needOneStep = false;
}

void GameRole::executeStateList()
{
	while (!m_statelist.empty())
	{
		const StateInfo &info = m_statelist.front();
		const short& dir=getDirection();
		if (info.dir != -1 && dir != info.dir)
		{
			setDirection(info.dir);
		}

		m_state = info.state;
		if (m_state != AVATAR_ACTION_IDLE)
		{
			if (isAttackKindState(info.skilltype))
			{
				AliveGhost* ag = dynamic_cast<AliveGhost*>(GameData::getGhostManager()->getGhostById(info.pid));
				castSkill(info.skilltype, info.ptx, info.pty, ag);
				//
			}
			m_statelist.pop();
			break;
		}
		m_statelist.pop();
	}
}

CCPoint GameRole::faceFightPoint()
{
	int tx = mTx;
	int ty = mTy;
	int ax = m_aimGhost->mTx;
	int ay = m_aimGhost->mTy;

	if (tx == ax && ty == ay)
	{
		do 
		{
			tx = ax+1;
			if (!isBlocked(tx, ty))
				break;
			ty = ay-1;
			if (!isBlocked(tx, ty))
				break;
			ty = ay+1;
			if (!isBlocked(tx, ty))
				break;
			ty = ay;
			tx = ax-1;
			if (!isBlocked(tx, ty))
				break;
			ty = ay-1;
			if (!isBlocked(tx, ty))
				break;
			ty = ay+1;
			if (!isBlocked(tx, ty))
				break;
			tx = ax;
			ty = ay-1;
			if (!isBlocked(tx, ty))
				break;
			ty = ay+1;
			if (!isBlocked(tx, ty))
				break;
		} while (0);
		
		return ccp(tx, ty);
	}

	tx = m_aimGhost->mTx + ((m_aimGhost->mTx < mTx) ? 1 : (m_aimGhost->mTx > mTx ? -1 : 0));
	ty = m_aimGhost->mTy + ((m_aimGhost->mTy < mTy) ? 1 : (m_aimGhost->mTy > mTy ? -1 : 0));

	if (!isBlocked(tx, ty))
		return ccp(tx, ty);
	ty = ay;
	do 
	{
		tx = ax+1;
		if (!isBlocked(tx, ty))
			break;
		ty = ay-1;
		if (!isBlocked(tx, ty))
			break;
		ty = ay+1;
		if (!isBlocked(tx, ty))
			break;
		ty = ay;
		tx = ax-1;
		if (!isBlocked(tx, ty))
			break;
		ty = ay-1;
		if (!isBlocked(tx, ty))
			break;
		ty = ay+1;
		if (!isBlocked(tx, ty))
			break;
		tx = ax;
		ty = ay-1;
		if (!isBlocked(tx, ty))
			break;
		ty = ay+1;
		if (!isBlocked(tx, ty))
			break;
	} while (0);
	return ccp(tx, ty);
}

void GameRole::useSkillRequest(int skillID, int x, int y, uint32 id)
{
	addSkillState(skillID, id);

	const int typeEnum = skillID/10;
	if(typeEnum == SKILL_TYPE_WaKuang)
	{
		MsgPlayerMineonPosRequest* req = new MsgPlayerMineonPosRequest;
		req->mineid = skillID;
		req->targetx = x;
		req->targety = y;
		HandleMessage::sendMessage(req);
		FightingState::start();
		return;
	}
	
	HeroData::resetGlobalCD();
	if (SkillEffect::isSkillNeedTarget(skillID))
	{
		if (!(typeEnum == SKILL_TYPE_HuoQiuShu ||
			typeEnum == SKILL_TYPE_LeiDianShu ||
			typeEnum == SKILL_TYPE_BingPaoXiao ||
			typeEnum == SKILL_TYPE_LingHunHuoFu ||
			typeEnum == SKILL_TYPE_ShiDuShu))
		{
			MsgPlayerUseSkillonEntityRequest* req = new MsgPlayerUseSkillonEntityRequest;
			req->skillid = skillID;
			req->eid = id;
			HandleMessage::sendMessage(req);

			//show cd
			if (typeEnum != SKILL_TYPE_LieHuoJianFa
				|| !hasEffectBuff(Effect::effect_firereborn))
			{
				CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2, skillID);
				CPEventHelper::uiNotify("UINotifyPlayerUseSkill", "", 0);
			}
		}
	}
	else
	{
		MsgPlayerUseSkillonPosRequest* req = new MsgPlayerUseSkillonPosRequest;
		req->skillid = skillID;
		req->targetx = x;
		req->targety = y;
		HandleMessage::sendMessage(req);

		//show cd
		CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2, skillID);
		CPEventHelper::uiNotify("UINotifyPlayerUseSkill", "", 0);
	}
	FightingState::start();
}

void GameRole::addSkillState( int skillID, int id )
{
	const int typeEnum = skillID/10;
	StateInfo info;
	if (typeEnum == SKILL_TYPE_YiBanGongJi ||
		(SKILL_TYPE_JiChuJianShu <= typeEnum && typeEnum < SKILL_TYPE_HuoQiang))
	{
		if (typeEnum == SKILL_TYPE_YeManChongZhuang)
		{
			info.state = AVATAR_ACTION_RUN;
		}
		else if (typeEnum == SKILL_TYPE_LieYanChongSheng)
		{
			info.state = AVATAR_ACTION_MAGIC;
		}
		else
		{
			info.state = AVATAR_ACTION_ATTACK;
		}
	}
	else if (typeEnum == SKILL_TYPE_WaKuang)
	{
		info.state = AVATAR_ACTION_MINE;
	}
	else
	{
		info.state = AVATAR_ACTION_MAGIC;
	}
	info.pid = id;
	info.skilltype = skillID;
	AliveGhost::setState(info);
}

bool GameRole::isBlocked( int tX, int tY )
{
	if(!GameData::s_user->m_pPixesMap)
	{
		return true;
	}
	//when out of the bound,we treat is as blocked
	if (tX < 0 || tY < 0 ||
		tX >= GameData::s_user->m_pPixesMap->mLogicWidth ||
		tY >= GameData::s_user->m_pPixesMap->mLogicHeight)
	{
		//CCLog("Out of the MAP BOUND");
		return true;
	}

	if(GameData::s_user->m_pPixesMap->mBlockData)
	{
		if (GameData::s_user->m_pPixesMap->mBlockData[tY][tX] == 1)
		{
			return true;
		}
	}

	return false;
}

void GameRole::setState( short state, int dir/*=-1*/ )
{
	//if the current state is not idle, we shouldn't accept the be hit state
	if ((m_state != AVATAR_ACTION_IDLE || m_bAutoMove) &&
		state == AVATAR_ACTION_INJURY)
	{
		return;
	}

	//??????????????????????????????????????????????
	//state??dir???????????????????????????????????
	if(!m_bAutoMove)
	{
		checkBlockedMove(state, dir);
	}

	//????????setState??????????
	AliveGhost::setState(state, dir);
}

void GameRole::setState( short state, int dir, StateInfo* info )
{
	AliveGhost::setState(state, dir, info);
}

bool GameRole::checkBlockedMove( short &state, int &dir )
{
	if (state != AVATAR_ACTION_WALK && state != AVATAR_ACTION_RUN)
		return false;

	if (isBlocked(mTx+tile_step[dir][0], mTy+tile_step[dir][1]))
	{
		checkPassObstacle(state,dir);
	}
	else if (state == AVATAR_ACTION_RUN && isBlocked(mTx+tile_step[dir][0]*2, mTy+tile_step[dir][1]*2))
	{
		state = AVATAR_ACTION_WALK;
	}

	if(state==AVATAR_ACTION_IDLE)
	{
		return false;
	}

	return true;
}

void GameRole::stopAnimation()
{
	HeroAvatar::stopAnimation();
}

bool GameRole::isSelected( const CCPoint &touchPos )
{
	CPUnused(touchPos);
	return false;
}

void GameRole::nextPathSegment()
{
	//???????????????????????
	const CCPoint &okTarget = bfsFindOKPos(ccp(m_nTargetX, m_nTargetY), SystemData::getDirection(ccp(mTx, mTy), ccp(m_nTargetX, m_nTargetY)));
	if(isBlocked(okTarget.x, okTarget.y))
	{
		CCLog("Target is blocked!!");
		m_bAutoMove = false;
		return;
	}
	
	//????????????????
	if(!m_pPathFinder->A_StarPathFinding(okTarget))
	{
		CCLog("Failed to find a way with A Star Path finder...");
		m_bAutoMove = false;
	}
}

bool GameRole::isReached()
{
	const CCPoint &target = ccp(m_nTargetX, m_nTargetY);
	if (m_bCrossAutoMove ||
		m_nTargetGhostType == GHOST_TYPE_MAP_ITEM ||
		m_bMovingAndPick)
	{
		return isReached(target);
	}

	const CCPoint &start = ccp(mTx, mTy);
	const int distance = ccpDistance(start, bfsFindOKPos(target, SystemData::getDirection(start, target)));
	if (m_nTargetGhostType == GHOST_TYPE_NPC)
	{
		const int maxD = (mMoveToTargetByButton ? ReachNPCDistanceQuest : ReachNPCDistanceNormal);
		return (distance <= maxD);
	}
	else if (m_nTargetGhostType == GHOST_TYPE_MINE)
	{
		return (distance <= 1);
	}
	return (distance <= ReachDistance);
}

bool GameRole::isReached( CCPoint target )
{
	return (mTx == target.x && mTy == target.y);
}

cocos2d::CCPoint GameRole::bfsFindOKPos( CCPoint nextPos, int nearDir)
{
	memset(m_visit,false,sizeof(m_visit));
	std::queue<CCPoint> q;
	m_visit[(int)(nextPos.x)][(int)(nextPos.y)] = true;
	q.push(nextPos);
	while(!q.empty())
	{
		CCPoint p = q.front();
		q.pop();
		if(!isBlocked(p.x,p.y))
		{
			return p;
		}
		for(int i=0; i<MAX_MoveDirections; i++)
		{
			int j = (nearDir+i)%MAX_MoveDirections;
			int x = p.x+tile_step[j][0];
			int y = p.y+tile_step[j][1];
			if(x>=0 && x<300 && y>=0 && y<300 && !m_visit[x][y])
			{
				m_visit[x][y] = true;
				q.push(ccp(x,y));
			}
		}
	}
	CCLog(">>>Error: GameRole::bfsFindOKPos failed!");
	return ccp(-1,-1);
}

bool GameRole::autoMoveOneStep( CCPoint targetTilePos, short& state )
{
	if(isReached(targetTilePos))
	{
		return false;
	}

	if(!m_pPathFinder)
	{
		m_pPathFinder = new AstarPathfinder(this);
	}

	m_pPathFinder->A_StarPathFinding(targetTilePos);
	if(!m_pPathFinder->hasNextStep())
	{
		return false;
	}

	const int direction = m_pPathFinder->getNextStep();
	setDirection(direction);

	const int dir = m_pPathFinder->hasNextStep() ? m_pPathFinder->watchNextStep() : -1;
	state = (dir == direction) ? AVATAR_ACTION_RUN : AVATAR_ACTION_WALK;
	m_pPathFinder->clear();
	return true;
}

void GameRole::turnDirection(int dir)
{
	setDirection(dir);

	MsgEntityTurnRequest* msg = new MsgEntityTurnRequest;
	msg->dir = dir;	
	HandleMessage::sendMessage(msg);
}

void GameRole::setDirection(int dir)
{
	AliveGhost::setDirection(dir);
	m_serverDir = dir;
}

void GameRole::pickUp(unsigned int itemid)
{
	MsgFetchItemRequest* req = new MsgFetchItemRequest;
	req->eid = itemid;
	HandleMessage::sendMessage(req);
}

void GameRole::abandonItem(unsigned int iid, int count)
{
	MsgAbandonItemRequest* req = new MsgAbandonItemRequest;
	req->eid = iid;
	req->count=count;
	HandleMessage::sendMessage(req);
}

void GameRole::startAutoMoveTo( int tx, int ty , int type)
{
	if (GameData::s_user->m_pPixesMap==NULL)
	{
		return;
	}

	m_nTargetX = tx;
	m_nTargetY = ty;
	if (m_nTargetX < 0 ||
		m_nTargetX > GameData::s_user->m_pPixesMap->mLogicWidth ||
		m_nTargetY < 0 ||
		m_nTargetY > GameData::s_user->m_pPixesMap->mLogicHeight)
	{
		return;
	}
	m_bAutoMove = true;

	m_nTargetGhostId = -1;
	if (type==0)
	{
		m_nTargetGhostType = -1;
	}
	else
	{
		m_nTargetGhostType = type;
	}
	m_isMoveAndAttack = false;
	if(!m_pPathFinder)
	{
		m_pPathFinder = new AstarPathfinder(this);
	}

	if(m_pPathFinder)
	{
		m_pPathFinder->clear();
	}
}

void GameRole::startAutoMoveTo( Ghost *pGhost )
{
	//if the item position is blocked, we won't go to pick it
	if(pGhost->mType == GHOST_TYPE_MAP_ITEM)
	{
		if (isBlocked(pGhost->mTx,pGhost->mTy))
		{
			CCLog("ERROR, item: %d is blocked.",pGhost->mID);
			return;
		}
		else
		{
			if (mTx == pGhost->mTx &&
				mTy == pGhost->mTy)
			{
				pickUp(pGhost->mID);
				return;
			}
		}
	}

	m_nTargetX = pGhost->mTx;
	m_nTargetY = pGhost->mTy;
	m_nTargetGhostId = pGhost->mID;
	m_nTargetGhostType = pGhost->mType;
	m_bAutoMove = true;
	//setEasyAI(false);
	m_isMoveAndAttack = false;
	if(!m_pPathFinder)
	{
		m_pPathFinder = new AstarPathfinder(this);
	}
	if(m_pPathFinder)
	{
		m_pPathFinder->clear();
	}
	m_bCrossAutoMove = false;
	if(m_state==AVATAR_ACTION_IDLE&&m_statelist.empty())
	{
		setNextStateCallback();
	}
}

void GameRole::startAutoMoveToCrossMap( int mapid,  int x,int y, int type )
{
	m_targetMapID = mapid;
	m_bMovingAndPick = false;
	mMoveToTargetByButton = true;
	m_nTargetGhostId = -1;
	if (type==0)
	{
		m_nTargetGhostType = -1;
	}
	else
	{
		m_nTargetGhostType = type;
	}
	//setEasyAI(false);
	if(GameData::s_user->mMap.mID == mapid)
	{
		m_bCrossAutoMove = false;
		startAutoMoveTo(x,y,type);
	}
	else
	{
		m_nTargetMapX = x;
		m_nTargetMapY = y;
		if(searchCrossMapPath())
		{
			m_bCrossAutoMove = true;
			MapConnVect vec = GameData::s_map->mMiniMapConn[GameData::s_user->mMap.mID];
			for(MapConnVect::iterator it=vec.begin(); it!=vec.end(); it++)
			{
				NetMapConn* s=*it;
				if (s->mDesMapID==m_crossMapPath.top())
				{
					startAutoMoveTo(s->mFromX,s->mFromY,m_nTargetGhostType);
				}
			}
			m_crossMapPath.pop();			
		}
		else
		{
			CCLog("Failed to search a road!!!");
		}
	}
}

bool GameRole::searchCrossMapPath()
{
	while(!m_crossMapPath.empty())m_crossMapPath.pop();
	std::set<NetMapConn*> visitSet;
	std::queue<MapNode> q;
	std::vector<MapNode> closeList;
	MapNode cur;
	cur.id = GameData::s_user->mMap.mID;
	cur.parent = -1;
	q.push(cur);
	while(!q.empty())
	{
		cur = q.front();
		q.pop();
		closeList.push_back(cur);
		if(cur.id == m_targetMapID)
		{
			//the end
			while(cur.parent != -1)
			{
				m_crossMapPath.push(cur.id);
				cur = closeList[cur.parent];
			}
			return true;
		}
		int p = closeList.size()-1;
		typedef std::vector<NetMapConn*> StringVector;
		StringVector vec = GameData::s_map->mMiniMapConn[cur.id];
		for(StringVector::iterator it=vec.begin(); it!=vec.end(); it++)
		{
			NetMapConn* s=*it;
			if(visitSet.find(s) == visitSet.end())
			{
				visitSet.insert(s);
				cur.id = s->mDesMapID;
				cur.parent = p;
				q.push(cur);
			}
		}
	}
	return false;
}


void GameRole::updateSceenPosition()
{
	const int oy = LayoutData::getInt(CPModuleName::COMMON, "myRoleOy");
	m_sceenPosition.x = getMapPosition().x - SystemData::size_x/2;
	m_sceenPosition.y = getMapPosition().y - SystemData::size_y/2 + oy;
	const int mapwidth = GameData::s_user->m_pPixesMap->mLogicWidth * PixesMap::TILE_WIDTH;
	const int mapheight = GameData::s_user->m_pPixesMap->mLogicHeight * PixesMap::TILE_HEIGHT;
	if (m_sceenPosition.x < 0)
	{
		m_sceenPosition.x = 0;
	}
	else if (m_sceenPosition.x + SystemData::size_x > mapwidth)
	{
		m_sceenPosition.x = mapwidth - SystemData::size_x;
	}

	if (m_sceenPosition.y < 0)
	{
		m_sceenPosition.y = 0;
	}
	else if (m_sceenPosition.y + SystemData::size_y > mapheight)
	{
		m_sceenPosition.y = mapheight - SystemData::size_y;
	}

	m_sceenPosition.x = getMapPosition().x - m_sceenPosition.x;
	m_sceenPosition.y = SystemData::size_y - (getMapPosition().y - m_sceenPosition.y);
}

CCPoint& GameRole::getSceenPosition()
{
	return m_sceenPosition;
}

void GameRole::someoneNeedOut( Ghost* pgh )
{
	if (!m_aimGhost || !pgh)
	{
		return;
	}

	if (m_aimGhost == pgh)
	{
		m_isMoveAndAttack = false;
		changeTheAim(NULL);
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TARGET_DISAPPEAR);
	}
}

void GameRole::releaseRole()
{
	stopAnimation();
	for (int type =0; type<AVATAR_TYPE_NUMBER; type++)
	{
		m_pSprite[type] = NULL;
		for (int state=0; state<AVATAR_ACTION_COUNT; state++)
		{
			m_pAnimations[type][state] = NULL;
			m_nCurrentDress[type][state] = 0;
		}
	}

	if (m_pBodySprite)
	{
		m_pBodySprite->release();
		m_pBodySprite = NULL;
	}
	
	m_pSprMofadun = NULL;
	m_sprShadow = NULL;
	m_pHpBarOnHead = NULL;
	m_pHpBarBkg = NULL;
	m_disName = NULL;
	mHeadNameContainer = NULL;
	m_pEffectSprite = NULL;

	m_skill->removeAllSkills(); 

	m_isMouseSequence = false;
	m_isMoveAndAttack = false;
	m_isMousePickUp = false;
	m_aimGhost = NULL;
}

void GameRole::checkAutoMove()
{
	if(m_bCrossAutoMove)
	{
		if(m_targetMapID != GameData::s_user->mMap.mID)
		{ 
			if(!m_crossMapPath.empty())
			{
				typedef std::vector<NetMapConn*> StringVector;
				StringVector vec = GameData::s_map->mMiniMapConn[GameData::s_user->mMap.mID];
				for(StringVector::iterator it=vec.begin(); it!=vec.end(); it++)
				{
					NetMapConn* s=*it;
					if (s->mDesMapID==m_crossMapPath.top())
					{
						startAutoMoveTo(s->mFromX,s->mFromY,m_nTargetGhostType);
						break;
					}					
				}
				m_crossMapPath.pop();
			}
			else
			{
				CCLog("The cross path list is already empty!");
				m_bCrossAutoMove = false;
			}
		}
		else
		{
			m_bCrossAutoMove = false;
			startAutoMoveTo(m_nTargetMapX,m_nTargetMapY,m_nTargetGhostType);
		}
	}
}

int GameRole::getFightSkill( int type )
{
	if (type != 0)
	{
		return type;
	}

	int skillID = 0;
	bool hasFind = false;
	switch (HeroData::getJob())
	{
	case UserData::CARRER_ZS:
	case UserData::CARRER_OMNI:
		{
			if (hasEffectBuff(Effect::effect_firereborn) && isSkillLearned(SKILL_TYPE_LieHuoJianFa * 10, skillID))
			{
				return skillID;
			}

			if (canUseSkill(SKILL_TYPE_LieHuoJianFa, skillID) ||
				canUseSkill(SKILL_TYPE_BanYueWanDao, skillID) ||
				canUseSkill(SKILL_TYPE_CiShaJianShu, skillID) ||
				canUseSkill(SKILL_TYPE_JiChuJianShu, skillID))
			{
				return skillID;
			}
			break;
		}
	case UserData::CARRER_DS:
		{
			if (canUseSkill(SKILL_TYPE_LingHunHuoFu, skillID))
			{
				return skillID;
			}
			break;
		}
	case UserData::CARRER_FS:
		{
			if (UserData::getIntData(HeroData::getPID(), CPUserData::AUTO_FS_ZIDONGBINGFENGBAO) != 0)
			{
				if (canUseSkill(SKILL_TYPE_BingPaoXiao, skillID) ||
					canUseSkill(SKILL_TYPE_LeiDianShu, skillID) ||
					canUseSkill(SKILL_TYPE_HuoQiuShu, skillID))
				{
					return skillID;
				}
			}
			else
			{
				if (canUseSkill(SKILL_TYPE_LeiDianShu, skillID) ||
					canUseSkill(SKILL_TYPE_HuoQiuShu, skillID))
				{
					return skillID;
				}
			}
			
			break;
		}
	}

	return SKILL_TYPE_YiBanGongJi * 10 + 1;
}

bool GameRole::isGhostInAIRange( Ghost* pGhost )
{
	return !isTargetOutOfRange(pGhost);
}

#define AI_DEBUG(text) CCLog("EASY AI DEBUG:" text)

void GameRole::autoMoveAround()
{
	AI_DEBUG("No ghost found, walking around to find...");
	if (!m_bAutoMove)
	{
		const int tiles = 7;
		do
		{
			int rangex = rand() % tiles;
			int rangey = rand() % tiles;
			int x = mTx + rangex * (rand() % 2 == 0 ? 1 : -1);
			int y = mTy + rangex * (rand() % 2 == 0 ? 1 : -1);
			if (x != mTx && y != mTy)
			{
				startAutoMoveTo(x, y);
				break;
			}
		} while (true);
	}
}

void GameRole::easyAi()
{
	if(!isEasyAIOn())
	{
		return;
	}
	// If not doing task but in peace area, then just return
	if (isInPeaceArea() && !m_bQuestDoing)
	{
		setEasyAI(false);
		m_bEasyAiKeepAttack = false;
		return;
	}
	// Just doing AI, but not attack
	if(!m_bEasyAiKeepAttack)
	{
		AI_DEBUG("m_bEasyAiKeepAttack is false");
		//pick up things or attack 
		Ghost* pGhost = m_aimGhost;
		// No target is set
		if (!pGhost)
		{	
			AI_DEBUG("pGhost = m_aimGhost is NULL");	
			// Find the nearest ghost
			pGhost = GameData::s_user->m_pGhostManager->getNearestEnemy();
			// If target sid has set yet, then find it exactly
			if (m_iTargetSid!=0)
			{
				Ghost* pSidGhost=GameData::s_user->m_pGhostManager->getGhostBySid(m_iTargetSid);
				AI_DEBUG("m_iTargeteid != 0, pGhost is updated");
				// Make sure nearest ghost or sid ghost found
				// Ronghui Yu, Nov 27, 2014
				if (pSidGhost) pGhost = pSidGhost;
			}
			// If no nearest ghost nor sid ghost found
			if (!pGhost)
			{
				AI_DEBUG("pGhost is NULL");
				// If doing task
				if (m_bQuestDoing)
				{
					// Just walking around
					autoMoveAround();
				}
				// Not doing task, no sid set either, just stop AI
				else if (m_iTargetSid==0)
				{
					AI_DEBUG("!m_bQuestDoing && m_iTargetSid==0 is true, setEasyAI(false) will be called");
					setEasyAI(false);
				}

				
			}
		}
		// If nearest ghost found, or sid ghost found
		if(pGhost)
		{
			AI_DEBUG("pGhost is not NULL");
			// A map item, go and pick it up
			if(pGhost->mType == GHOST_TYPE_MAP_ITEM)
			{
				AI_DEBUG("pGhost is a map item, will pick it up");
				// If doing task, DO NOT stop AI
				// Not sure why stop before
				// Ronghui Yu, Nov 27, 2014
				if (!m_bQuestDoing) setEasyAI(false);
				startAutoMoveTo(pGhost);
			}
			else
			{
				// Doing task
				if(m_bQuestDoing)
				{
					AI_DEBUG("m_bQuestDoing is true");
					// Ghost is not a monster or plant
					if (pGhost->mType != GHOST_TYPE_MONSTER
						&& pGhost->mType != GHOST_TYPE_PLANT)
					{
						AI_DEBUG("pGhost is not monster nor plant, change the aim to NULL");
						// Set the target to NULL, next update, it will find another target
						changeTheAim(NULL);		
						return;
					}
					// Ghost is not for the task
					else if (!NPCFunctionData::checkIsQuestMonster(pGhost->mStaticID))
					{
						AI_DEBUG("pGhost is not the quest monster, change the aim to NULL");
						changeTheAim(NULL);	
						// Walk around, and wait for next update
						autoMoveAround();
						return;
					}
				} // m_bQuestDoing

				AliveGhost* pMonster = dynamic_cast<AliveGhost*>(pGhost);
				// If the ghost is not an alive ghost, or it is dead, or out of range
				if (!pMonster ||
					pMonster->isDead())
				{
					AI_DEBUG("Failed to cast the pGhost to AliveGhost or pGhost is dead");
					changeTheAim(NULL);
					setEasyAI(false);		
					return;
				}

				if (!m_aimGhost ||
					m_aimGhost->mType != GHOST_TYPE_MONSTER ||
					m_aimGhost->isDead())
				{
					AI_DEBUG("m_aimGhost is NULL or type is not monster or is dead, change the aim the pMonster");
					changeTheAim(pMonster);
				}

				m_autoSkillType = getFightSkill(0);
				const int typeEnum = m_autoSkillType/10;
				if (typeEnum == SKILL_TYPE_YiBanGongJi ||
					typeEnum == SKILL_TYPE_JiChuJianShu)
				{
					m_isMoveAndAttack = true;
					//setEasyAI(false);
				}
				else
				{
					startCastSkill(m_autoSkillType);
					m_bEasyAiKeepAttack = true;
				}
			}
		}
	} // !m_bEasyAiKeepAttack
	else
	{
		AI_DEBUG("m_bEasyAiKeepAttack is true");
		// No target is set, or the target has died, or the target out of range
		if (!m_aimGhost ||
			m_aimGhost->isDead() ||
			isTargetOutOfRange(m_aimGhost))
		{
			AI_DEBUG("m_aimGhost is NULL or is dead");
			if (m_bQuestDoing)
			{
				AI_DEBUG("m_bQuestDoing is true");
				// Find the nearest ghost
				Ghost* pGhost = GameData::s_user->m_pGhostManager->getNearestEnemy();
				AI_DEBUG("pGhost is the nearest enemy");
				if (m_iTargetSid!=0)
				{
					Ghost* pSidGhost=GameData::s_user->m_pGhostManager->getGhostBySid(m_iTargetSid);
					AI_DEBUG("m_iTargeteid != 0, pGhost is updated");
					// Make sure either nearest ghost or sid ghost is set
					if (pSidGhost) pGhost = pSidGhost;
				}
				AliveGhost* pMonster = dynamic_cast<AliveGhost*>(pGhost);
				// If this is the task ghost
				if (pMonster &&
					NPCFunctionData::checkIsQuestMonster(pMonster->mStaticID))
				{
					AI_DEBUG("Success to cast to AliveGhost, and it is the quest monster");
					changeTheAim(pMonster);
					startAutoMoveTo(pMonster);
				}
				// Not the task ghost, just moving around
				else
				{
					autoMoveAround();
					CCLog("Cannot find the nearest ghost for task doing");
				}
			} // m_bQuestDoing
			else
			{
				AI_DEBUG("m_bQuestDoing is false, setEasyAI(false) will be called");
				setEasyAI(false);
				AI_DEBUG("m_bEasyAiKeepAttack is set to false");
				m_bEasyAiKeepAttack = false;
			}
		} // Aim ghost is still there
		else
		{
			m_autoSkillType = getFightSkill(0);
			const int typeEnum = m_autoSkillType/10;
			if (typeEnum == SKILL_TYPE_YiBanGongJi ||
				typeEnum == SKILL_TYPE_JiChuJianShu)
			{
				m_isMoveAndAttack = true;
				//setEasyAI(false);
				//m_bEasyAiKeepAttack = false;
			}
			else
			{
				startCastSkill(m_autoSkillType);
			}
		}
	}

	//
	if(m_isMoveAndAttack && m_state == AVATAR_ACTION_IDLE)
	{
		setNextStateCallback();
	}
}

void GameRole::setMP(int mp)
{
	AliveGhost::setMP(mp);
	CombatData[Combat::prop_MP] = mp;
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_CHANGE_MP);
}

void GameRole::handleHpChange(int changeHp)
{
	addInjury(true, changeHp);
	if(changeHp < 0)
	{
		if(isDead())
		{
			m_bEasyAi = false;
			m_bAutoMove = false;
			m_isMoveAndAttack = false;
			m_bMovingAndPick = false;
			stopAutoMoving();
			setState(AVATAR_ACTION_DIE);
		}
		else
		{
			if (CPUpdateFunctorManager::instance()->hasFunctor(CPUFDefination::HpLow_Scroll) &&
				!isInPeaceArea())
			{
				const std::string &key = CPUserData::UPDATE_FUNCTOR_ID + StringUtils::toString(CPUFDefination::HpLow_Scroll) + "_";
				const float nowPercent = (float)mHp / (float)mMaxHp;
				const float percent = UserData::getIntData(HeroData::getPID(), key, 3) / 100.0f;
				if (nowPercent < percent)
				{
					UserItemData *userItems = GameData::s_user->getUserItemData();
					if (userItems)
					{
						const int sid = UserData::getIntData(HeroData::getPID(), key, 4);
						const int iid = userItems->getItemBySid(sid);
						if (iid > 0)
						{
							ItemOperator::useItem(iid);
						}
					}
				}
			}
		}
	}
	else
	{
		if (m_state == AVATAR_ACTION_DIE &&
			!isDead())
		{
			setState(AVATAR_ACTION_IDLE);
		}
	}
}

void GameRole::delayHpChange( int hp,short delay )
{
	HPChangeDelay changdata;
	changdata.m_nChangType = Combat::batt_hpchange;
	changdata.m_nHpChangeDelay = delay;
	if (hp < 0)
		hp = 0;
	changdata.m_nHpChange = hp - mHp;
	m_nHpChangeList.push_back(changdata);
	if (mHp==0 && hp>0)
	{
		SkillEffect *skill = m_skill;
		if (skill)
		{
			skill->runSkill(SKILL_TYPE_Relive * 10, mTx, mTy, NULL);
		}
	}
	mHp = hp;
	CombatData[Combat::prop_HP] = mHp;
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_CHANGE_HP);
	FightingState::start();
}

void GameRole::checkOnPortals()
{
	if(m_bTranfering)
	{
		return;
	}

	//???????????????????????????????????????????????????????????????????????????????????????????	
	MapConnsMap::iterator connsIt = GameData::s_map->mMiniMapConn.find(GameData::s_user->mMap.mID);
	if(connsIt == GameData::s_map->mMiniMapConn.end())
	{
		return;
	}

	const MapConnVect &mapconns = connsIt->second;
	for(unsigned int i = 0; i < mapconns.size(); i++)	
	{
		NetMapConn* pConn = mapconns[i];
		if(pConn)
		{
			int accessDistance = 0;
			StaticData::getGlobalData("portalssize", accessDistance);
			const float distance = ccpDistance(ccp(mTx, mTy), ccp(pConn->mFromX, pConn->mFromY));
			if (distance <= accessDistance)
			{
				m_bTranfering = true;
				if (SceneHelper::isUnknownMapInMini(pConn->mDesMapID))
				{
					CPEventHelper::msgNotify("PreventMiniSwitchToUnknownMap", "",0,0,0,0);
					return;
				}
				SceneHelper::teleportByPortalRequest(pConn->mStaticID);
				return;
			}
		}
		else
		{
			CCLog("ERROR, null map conns.");
		}
	}
}

bool GameRole::isSkillLearned( int skillid, int &skillID )
{
	const int skillEnum = skillid/10;
	if (skillEnum > 0)
	{
		const IDVector &skillIDVect = HeroData::getSkillVect();
		for (int i = 0; i < (int)skillIDVect.size(); i++)
		{
			if (skillEnum == skillIDVect[i]/10)
			{
				skillID = skillIDVect[i];
				return true;
			}
		}
	}
	return false;
}

bool GameRole::canUseSkill( int skillEnum, int &skillID )
{
	if(!m_aimGhost ||
		m_aimGhost->mHp <= 0)
	{
		return false;
	}

	// learn test
	if (!isSkillLearned(skillEnum * 10, skillID))
	{
		return false;
	}

	if (!testManaAndCD(skillID, true, false))
	{
		return false;
	}

	// base test
	bool baseFlag = false;
	switch (skillEnum)
	{
	case SKILL_TYPE_LieHuoJianFa:
		{
			if (UserData::getIntData(HeroData::getPID(), CPUserData::SKILL_LIE_HUO_OFF) == 0)
			{
				int direction = 0;
				AliveGhost *target = getShortRangeAttackTarget(direction);
				if (target &&
					target == m_aimGhost)
				{
					return true;
				}
			}
			return false;
		}
	case SKILL_TYPE_BanYueWanDao:
		{
			if (UserData::getIntData(HeroData::getPID(), CPUserData::SKILL_BAN_YUE_OFF) == 0)
			{
				int direction = 0;
				AliveGhost *target = getShortRangeAttackTarget(direction);
				if (target &&
					target == m_aimGhost)
				{
					for (int i = 0; i < 3; i++)
					{
						int x = m_aimGhost->mTx + halfmoon[direction][i][0];
						int y = m_aimGhost->mTy + halfmoon[direction][i][1];
						AliveGhost *ghost = getAliveEnemy(x, y);
						if (ghost)
						{
							return true;
						}
					}
				}
			}
			return false;
		}
	case SKILL_TYPE_CiShaJianShu:
		{
			if (UserData::getIntData(HeroData::getPID(), CPUserData::SKILL_CI_SHA_OFF) == 0)
			{
				if (m_aimGhost)
				{
					const int dir = SystemData::getDirection(ccp(mTx, mTy), ccp(m_aimGhost->mTx, m_aimGhost->mTy));
					int x = mTx + tile_step[dir][0];
					int y = mTy + tile_step[dir][1];
					AliveGhost *ghost1 = getAliveEnemy(x, y);
					x = mTx + tile_step[dir][0] * 2;
					y = mTy + tile_step[dir][1] * 2;
					AliveGhost *ghost2 = getAliveEnemy(x, y);
					if (ghost2)
					{
						if (ghost1 == m_aimGhost
							|| ghost2 == m_aimGhost)
						{
							return true;
						}
					}	
				}
			}
			return false;
		}
	}

	return true;
}

bool GameRole::testManaAndCD( int skillID, bool containGCD, bool needNotify )
{
	// mana test
	int mana = 0;
	StaticData::getSkillNeedMana(skillID, mana);
	if (mMp < mana)
	{
		if (needNotify)
		{
			CPEventHelper::uiNotify("GameRole", "", Error::Combat_OutOfMana);
		}
		return false;
	}

	// cd test
	
		const int typeEnum = skillID/10;

		//????????????????global CD
		if (typeEnum==SKILL_TYPE_LieYanChongSheng && HeroData::getSkillCD(skillID)<=0)
		{
			return true;
		}
		else if (typeEnum != SKILL_TYPE_LieHuoJianFa
			|| !hasEffectBuff(Effect::effect_firereborn))
		{
			// 攻速门控: 仅"有攻速装备的普攻"跳过全局CD; 攻速0或其它技能完全保持原始判断
			int atkTypeEnum = skillID / 10;
			bool isAtkSkillForGCD = (atkTypeEnum == 100) || (atkTypeEnum >= 10 && atkTypeEnum < 20);
			bool skipGCD = isAtkSkillForGCD && CombatData[Combat::prop_Attack_Speed] > 0;
			if ((!skipGCD && containGCD && HeroData::getGlobalCD() > 0)
				|| HeroData::getSkillCD(skillID) > 0)
			{
				if (needNotify)
				{
					CPEventHelper::uiNotify("GameRole", "", Error::Combat_InCoolDown);
					AudioLoader::play(Sound::Effect::jinenglengque);
				}
				return false;
			}
		}

		return true;
}

bool GameRole::testSkillDistance( int skillID, CCPoint tgtpoint)
{
	const int dx = abs((int)tgtpoint.x - mTx);
	const int dy = abs((int)tgtpoint.y - mTy);
	int skillrangemax = 0;
	LuaData::getProp(LuaData::SKILL,skillID,"distance",skillrangemax);
	if (skillrangemax < 1)
		skillrangemax = 1;
	if (dx > skillrangemax ||
		dy > skillrangemax)
	{
		return false;
	}
	return true;
}

bool GameRole::isInPeaceArea()
{
	return isInPeaceArea(mTx, mTy);
}

bool GameRole::isInPeaceArea( int tx, int ty )
{
	const int mapID = GameData::getCurrentMap()->mID;
	int cnt = 0;
	StaticData::getMapPeaceAreaCnt(mapID, cnt);
	int areaID = 0;
	for (int i = 0; i < cnt; i++)
	{
		areaID = 0;
		StaticData::getMapPeaceAreaID(mapID, i + 1, areaID);
		if (AreaChecker::instance().checkerInArea(areaID, tx, ty))
		{
			if (AreaChecker::instance().getAreaType(areaID) == Scene::safearea)
			{
				return true;
			}
		}
	}
	return false;
}

void GameRole::tryToMine( const CCPoint &touchPos )
{
	const CCPoint &mapPos = convertToMapTile(touchPos);
	if (isBlocked(int(mapPos.x), int(mapPos.y)))
	{
		//??????????????
		int miningFlag = 0;
		StaticData::getMapMiningFlag(GameData::s_user->mMap.mID, miningFlag);
		if (miningFlag!=0)
		{
			UserItem *item = GameData::s_user->getUserItemData()->getItemByPosition(-Pos_Weapon);
			if (item)
			{
				int skillID = 0;
				StaticData::getItemSkillID(item->sid, skillID);
				if (skillID)
				{
					startAutoMoveTo(mapPos.x,mapPos.y,GHOST_TYPE_MINE);
				}
				else
				{
					NotificationHelper::showNote(LayoutData::getString(CPModuleName::COMMON, "changeMiningTools"));
				}
			}
		}
	}
}

AliveGhost * GameRole::getShortRangeAttackTarget(int &direction)
{
	direction = getDirection();
	if (m_aimGhost)
	{
		const int dir = SystemData::getDirection(ccp(mTx, mTy), ccp(m_aimGhost->mTx, m_aimGhost->mTy));
		if (dir != direction)
		{
			direction = dir;
		}
	}
	int x = mTx + tile_step[direction][0];
	int y = mTy + tile_step[direction][1];
	return getAliveEnemy(x, y);
}

AliveGhost * GameRole::getAliveEnemy( int x, int y )
{
	AliveGhost *ret = dynamic_cast<AliveGhost *>(GameData::getGhostManager()->getAnyGhostAtPosition(x, y));
	if (ret && !ret->isDead()
		&& (ret->mType == GHOST_TYPE_PLAYER || ret->mType == GHOST_TYPE_PET || ret->mType == GHOST_TYPE_SLAVE || ret->mType == GHOST_TYPE_MONSTER)
		&& !GameData::getGhostManager()->isTargetFriendly(ret))
	{
		return ret;
	}
	return NULL;
}

void GameRole::setEasyAI( bool isOn )
{
	if (!m_bEasyAi &&
		isOn)
	{
		m_nAutoFightTime = GameData::s_user->millisecondNow();
	}
	m_bEasyAi = isOn;
}

bool GameRole::isEasyAIOn() const
{
	return m_bEasyAi;
}

bool GameRole::isQuestDoing() const
{
	return m_bQuestDoing;
}

void GameRole::setQuestDoing( bool isDoing )
{
	m_bQuestDoing = isDoing;
}

bool GameRole::isTargetOutOfRange()
{
	return isTargetOutOfRange(m_aimGhost);
}

bool GameRole::isTargetOutOfRange( Ghost *ghost )
{
	if (ghost)
	{
		const int dx = abs(ghost->mTx - mTx);
		const int dy = abs(ghost->mTy - mTy);
		if (dx > m_irangex ||
			dy > m_irangey )
		{
			return true;
		}
	}
	return false;
}

void GameRole::startPickPlant( int plantID )
{
	MsgPickPlantRequest *msg = new MsgPickPlantRequest;
	msg->eid = plantID;
	HandleMessage::sendMessage(msg);
}

bool GameRole::changeToNearestTarget()
{
	AliveGhost *anim = dynamic_cast<AliveGhost *>(GameData::s_user->m_pGhostManager->getNearestEnemy());
	if (!anim ||
		isTargetOutOfRange(anim))
	{
		return false;
	}
	if (AutoAttack::checkAutoAttack() && GameData::s_user->m_pMainRole->mLevel<30)
	{
		int petPickState = HeroData::getProp(Entity::attr_pet_pick_state); 
		UserPet* pPet = GameData::s_user->getUserPetData()->getCurrentCombatPet();
		if (!pPet)
		{
			if (GameData::s_user->m_pGhostManager->m_pNearItem )//&& canPickItem(GameData::s_user->m_pGhostManager->m_pNearItem))
			{
				AliveGhost* p  = dynamic_cast<AliveGhost*>(GameData::s_user->m_pGhostManager->m_pNearItem);
				if (p && checkGhostIsOwn(p))
				{
					GameData::s_user->m_pMainRole->startAutoMoveTo(GameData::s_user->m_pGhostManager->m_pNearItem);
					changeTheAim(NULL);
					setEasyAI(false);
					return true;
				}
			}
			else if (GameData::s_user->m_pGhostManager->m_pNearMoney)// && canPickItem(GameData::s_user->m_pGhostManager->m_pNearMoney))
			{
				AliveGhost* p  = dynamic_cast<AliveGhost*>(GameData::s_user->m_pGhostManager->m_pNearMoney);
				if (p && checkGhostIsOwn(p))
				{
					GameData::s_user->m_pMainRole->startAutoMoveTo(GameData::s_user->m_pGhostManager->m_pNearMoney);
					changeTheAim(NULL);
					setEasyAI(false);
					return true;
				}
			}
			else if (GameData::s_user->m_pGhostManager->m_pNearDrug )//&& canPickItem(GameData::s_user->m_pGhostManager->m_pNearDrug))
			{
				AliveGhost* p  = dynamic_cast<AliveGhost*>(GameData::s_user->m_pGhostManager->m_pNearDrug);
				if (p && checkGhostIsOwn(p))
				{
					GameData::s_user->m_pMainRole->startAutoMoveTo(GameData::s_user->m_pGhostManager->m_pNearDrug);
					changeTheAim(NULL);
					setEasyAI(false);
					return true;
				}
			}
		}
		else
		{
			if ((petPickState&1) == 0)
			{
				if (GameData::s_user->m_pGhostManager->m_pNearMoney && canPickItem(GameData::s_user->m_pGhostManager->m_pNearMoney) && checkGhostIsOwn((AliveGhost*)GameData::s_user->m_pGhostManager->m_pNearMoney))
				{
					startAutoMoveTo(GameData::s_user->m_pGhostManager->m_pNearMoney);
					changeTheAim(NULL);
					setEasyAI(false);
					return true;
				}
			}
			if ((petPickState&2) == 0)
			{
				if (GameData::s_user->m_pGhostManager->m_pNearDrug && canPickItem(GameData::s_user->m_pGhostManager->m_pNearDrug)&& checkGhostIsOwn((AliveGhost*)GameData::s_user->m_pGhostManager->m_pNearDrug))
				{
					startAutoMoveTo(GameData::s_user->m_pGhostManager->m_pNearDrug);
					changeTheAim(NULL);
					setEasyAI(false);
					return true;
				}
			}
		}
	}
	changeTheAim(anim);
	return true;
}

void GameRole::refreshIntoPeaceArea()
{
	if (isInPeaceArea())
	{
		if (!mLastInPeaceArea)
		{
			NotificationHelper::showPeaceAreaNote(true);
		}
		mLastInPeaceArea = true;
	}
	else
	{
		if (mLastInPeaceArea)
		{
			NotificationHelper::showPeaceAreaNote(false);
		}
		mLastInPeaceArea = false;
	}
}

void GameRole::refreshMitigate()
{
	int saimachangFlag = 0;
	StaticData::getMapSaiMaChangFlag(GameData::getCurrentMap()->mID, saimachangFlag);
	if (saimachangFlag)
	{
		return;
	}

#define MITIGATE_RATE 1
	static int count = 0;
	if (count < MITIGATE_RATE)
	{
		count++;
		return;
	}
	count = 0;
	if ((mGhostJob == UserData::CARRER_FS || mGhostJob == UserData::CARRER_OMNI)
		&& UserData::getIntData(HeroData::getPID(), CPUserData::AUTO_FS_ZIDONGKAIDUN) != 0
		&& !isDead()
		&& !hasEffectBuff(Effect::effect_mitigate))
	{
		int skillID = 0;
		if (isSkillLearned(SKILL_TYPE_MoFaDun * 10, skillID))
		{
			if (testManaAndCD(skillID, false, false))
			{
				useSkillRequest(skillID, 0, 0, 0);
			}
		}
	}
}

void GameRole::stopAutoMoving()
{
	if (m_bAutoMove)
	{
		m_bAutoMove = false;
		m_pPathFinder->clear(); 
	}
	m_bQuestDoing=false;
	m_bCrossAutoMove = false;
	m_isMoveAndAttack = false;
	m_bMovingAndPick = false;
	setEasyAI(false);
	m_bEasyAiKeepAttack = false;
	m_autoSkillType = -1;
	m_bTranfering = false;
	mMoveToTargetByButton = false;
}

void GameRole::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (GameData::s_game_state == GAME_STATE_RUNNING)
		{
			if (source == "TimeManager")
			{
				refreshMitigate();
				autoAttack();
			}
		}	
	}
	else if (eventName == CPEventName::NPC_REQUESTDATA)
	{
		int wid=CPEventHelper::getEventIntData(CPEventData::VALUE_1);	
		int type=CPEventHelper::getEventIntData(CPEventData::VALUE_2);	
		NPCFunctionData::sendupdatedynamicData(wid,type);  
	}
	else if (eventName == CPEventName::NPC_REQUESTINSTANCEDATA)
	{
		NPCFunctionData::sendupdateinstanceData();   
	}
}

AliveGhost* GameRole::getTheAim()
{
	return m_aimGhost;
}

void GameRole::updateDoingQuest()
{
	if (m_bQuestDoing )
	{
		//setEasyAI(true);
		NPCFunctionData::dealwithQuest(TaskData::getCurrentDoingTask());


		CCLog("update quest road again!");
	}
}

bool GameRole::checkGhostIsOwn( AliveGhost* pGhost )
{
	if (pGhost==NULL)
	{
		return false;
	}
	if (pGhost->getExData(Entity::attr_owner_type)==Entity::eot_SinglePlayer || pGhost->getExData(Entity::attr_owner_type)==Entity::eot_None)
	{
		if (pGhost->getExData(Entity::attr_owner_data)==HeroData::getPID() || pGhost->getExData(Entity::attr_owner_data)==0)
		{
			return true;
		}
	}
	return false;
}

void GameRole::onSceneMonstersClean(int sceneId)
{
	if (AutoAttack::checkAutoAttack())
	{
		
		//
		int currentMapID = GameData::s_user->mMap.mID;
		int mapType=0;
		StaticData::getMapType(GameData::s_user->mMap.mID,mapType);
		if (mapType == Scene::stSceneInstance)
		{
			if(currentMapID == 1002)
				GameData::s_user->m_pGhostManager->gotoMap(currentMapID+1,GHOST_TYPE_MONSTER);				
			else{
				AutoAttack::closeAutoAttack();
				showExitAutoAttackGuide();
			}
		}
	}
}

void GameRole::autoAttack()
{
	if (!GameData::s_user || !GameData::s_user->m_pPixesMap)
	{
		return;
	}

	if (AutoAttack::checkAutoAttack() && !isEasyAIOn())
	{
		m_bQuestDoing = false;
		changeToNearestTarget();
		if (!m_bAutoMove)
		{			
			if (getTheAim()==NULL)
			{
				int currentMapID = GameData::s_user->mMap.mID;
				int monsterSize = 0;
				LuaData::getProp_size(LuaData::MAP,currentMapID,"monsters",monsterSize);
				int mapType=0;
				StaticData::getMapType(GameData::s_user->mMap.mID,mapType);

				if (monsterSize == 0 && 
					    // Close auto attack when scene type is stSceneInstance
						// Ronghui Yu, Aug 25, 2014
						(mapType==Scene::stSceneNormal || mapType == Scene::stSceneInstance))
				{
					AutoAttack::closeAutoAttack();
					CPEventHelper::uiNotify("","",Error::Not_Has_Monster);
					return;
				}			

				int x = 0, y = 0;
				if (mapType!=Scene::stSceneNormal &&
					// DO NOT randomly go when in instance scene
					// Ronghui Yu, Aug 25, 2014
					mapType != Scene::stSceneInstance)
				{
					x = rand()%GameData::s_user->m_pPixesMap->mLogicWidth;
					y = rand()%GameData::s_user->m_pPixesMap->mLogicHeight;
					while (isBlocked(x,y))
					{
						x = rand()%GameData::s_user->m_pPixesMap->mLogicWidth;
						y = rand()%GameData::s_user->m_pPixesMap->mLogicHeight;
					}
					CCLog("x = %d,y = %d",x,y);
				}
				else
				{
					srand((int)time(0)); 
					int randomnum = 1 + rand()%monsterSize;
					LuaData::getProp(LuaData::MAP,currentMapID,"monsters",randomnum,"posx","posy",y,x);
				}

				startAutoMoveTo(x, y, GHOST_TYPE_MONSTER);
			}
			setEasyAI(true);
		}
	}
}

void GameRole::showExitAutoAttackGuide()
{
	CPEventHelper::dispatcher(CPEventName::UI_OPEN, "GameRole::ExitAutoAttack", "GameUI");
}

bool GameRole::canPickItem( Ghost* pGhost )
{
	/*
	int sid = pGhost->mStaticID;
	UserItem* pitem = CommonFunction::createNewItem(sid);
	if (pitem->category==ItemCate_Equip)
	{
		int reqlvl = 0;
		LuaData::getProp(LuaData::ITEM,sid,"lvl",reqlvl);
		if (reqlvl>=0 && reqlvl<35)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_1_35_ON))
			{
				return false;
			}
		}
		else if (reqlvl>=35 && reqlvl<40)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_35_40_ON))
			{
				return false;
			}
		}
		else if (reqlvl>=40 && reqlvl<45)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_40_45_ON))
			{
				return false;
			}
		}
		else if (reqlvl>=45 && reqlvl<50)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_45_50_ON))
			{
				return false;
			}
		}
		else if (reqlvl>=50 && reqlvl<55)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_50_55_ON))
			{
				return false;
			}
		}
		else if (reqlvl>=55)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_55__ON))
			{
				return false;
			}
		}
	}
	else if (pitem->category==ItemCate_Extension || pitem->category==ItemCata_Gift )
	{
		if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_SHIYONG_ON))
		{
			return false;
		}
	}
	else if (pitem->category==ItemCate_Stone || pitem->category==ItemCate_Material)
	{
		if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_CAILIAO_ON))
		{
			return false;
		}
	}
	else if (pitem->category==ItemCate_Medicine)
	{
		if (pitem->type==1)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_SHUNHUIYAO_ON))
			{
				return false;
			}
		}
		else if (pitem->type==2)
		{
			if (!UserData::getIntData(HeroData::getPID(),CPUserData::PICKITEM_CHIXUYAO_ON))
			{
				return false;
			}
		}
	}
	*/
	return true;
}

void GameRole::autoToMine()
{
	//???????????\??
	int r = 10;
	int minlengh = 0;
	int minx = 0;
	int miny = 0;
	for (int x = (mTx-r)>0?(mTx-r):0;x<mTx+r;x++)
	{
		for (int y = (mTy-r)>0?(mTy-r):0;y<mTy+r;y++)
		{
			if(isBlocked(x,y))
			{
				if (minlengh==0)
				{
					minlengh = (x-mTx)*(x-mTx)+(y-mTy)*(y-mTy);
					minx = x;
					miny = y;
				}
				else
				{
					if (minlengh>(x-mTx)*(x-mTx)+(y-mTy)*(y-mTy))
					{
						minlengh = (x-mTx)*(x-mTx)+(y-mTy)*(y-mTy);
						minx = x;
						miny = y;
						//CCLog("x:%d,y:%d,lengh:%d",x,y,minlengh);
					}
				}
			}
		}
	}

	//??????\??
	startAutoMoveTo(minx,miny,GHOST_TYPE_MINE);
	//updateMoveState(m_MousePoint);

}

void GameRole::tryToMineByMapPos( CCPoint mapPos )
{
	UserItem *item = GameData::s_user->getUserItemData()->getItemByPosition(-Pos_Weapon);
	if (item)
	{
		if (isBlocked(int(mapPos.x), int(mapPos.y)))
		{
			int miningFlag = 0;
			StaticData::getItemMiningFlag(item->sid, miningFlag);
			if (miningFlag != 0)
			{
				int skillID = 0;
				StaticData::getItemSkillID(item->sid, skillID);
				if (skillID)
				{
					mLastMiningPt = mapPos;
					useSkillRequest(skillID, mapPos.x, mapPos.y, 0);
				}
			}
			else
			{
				NotificationHelper::showNote(LayoutData::getString(CPModuleName::COMMON, "changeMiningTools"));
			}
		}
	}
	
}

bool GameRole::checkSummonDog()
{
	int skillID = 0;
	const int dogCnt = HeroData::getProp(Entity::attr_dog_cnt);
	const int dogMax = HeroData::getProp(Entity::attr_dog_max);
	if (mGhostJob == UserData::CARRER_DS
		&& UserData::getIntData(HeroData::getPID(), CPUserData::AUTO_DS_ZIDONGZHAOHUANBAOBAO) != 0
		&& isSkillLearned(SKILL_TYPE_ZhaoHuanShenShou * 10, skillID)
		&& dogCnt < dogMax)
	{
		startCastSkill(skillID);
		return true;
	}
	return false;
}

cocos2d::CCPoint GameRole::getTargetPosition()
{
	return ccp(m_nTargetX, m_nTargetY);
}
