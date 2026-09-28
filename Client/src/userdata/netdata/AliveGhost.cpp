#include "AliveGhost.h"
#include "EffectDefinition.h"
#include "SceneDefinition.h"
#include "EntityDefinition.h"
#include "MainUIModule.h"
#include "UserDataModule.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/EffectSprite.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/UserData.h"
#include "userdata/GameData.h"
#include "userdata/StaticData.h"
#include "userdata/HeroData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/mapdata/PixesMap.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/skilldata/SkillEffect.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/NPCFunctionData.h"

#include "ext/ProgressBar.h"
#include "ext/CCFlashAnimation.h"
#include "ext/AstarPathfinder.h"
#include "ext/CCActionDestroy.h"

#include "network/NetProtocol.h"
#include "network/HandleMessage.h"

#include "res/AudioLoader.h"

#include "event/EventProtocol.h"

#include "utils/StringUtils.h"
#include "MsgItem.h"


#define  abs(v) (v < 0 ? -v : v)


const CCPoint offset = ccp(PixesMap::TILE_WIDTH/2.0, PixesMap::TILE_WIDTH/2.0);

AliveGhost::AliveGhost()
: m_state(AVATAR_ACTION_IDLE)
, m_direction(0)
, m_serverDir(0)
, m_serverTx(0)
, m_serverTy(0)
, mHp(33)
, mMp(18)
, mMaxHp(33)
, mMaxMp(18)
, mLevel(0)
, mReborn(0)
, mPetReborn(0)
, m_disName(NULL)
, mPKValue(0)
, m_pHpBarOnHead(NULL)
, m_pHpBarBkg(NULL)
, m_skill(NULL)
, m_frameCount(12)
, m_pEffectSprite(NULL)
, m_pSprMofadun(NULL)
,m_pSprBeAttackedCircle(NULL)
,mOwnerPid(0)
,mRealWeapon(0)
,mClothSizeByHeight(CCSizeZero)
,mClothOffsetByHeight(CCPointZero)
,mClothSizeByArea(CCSizeZero)
,mClothOffsetByArea(CCPointZero)
,mHPChangeDelayTime(0)
{
	for (int type =0; type<AVATAR_TYPE_NUMBER; type++)
	{
		m_pSprite[type] = NULL;
		m_nDress[type] = 0;

		for (int state=0; state<AVATAR_ACTION_COUNT; state++)
		{
			m_pAnimations[type][state] = NULL;
			m_nCurrentDress[type][state] = 0;
		}
	}
	m_skill = SkillEffect::create(this);
	mName = "";
}

AliveGhost::~AliveGhost()
{
 	if (m_pBodySprite)
	{
 		m_pBodySprite->release();
		m_pBodySprite = NULL;
	}

	if(m_skill)
	{
		delete m_skill;
	}
	m_skill = NULL;
}

bool AliveGhost::init()
{
	m_pBodySprite = CCSprite::create();
	m_pBodySprite->retain();

	char url[60];
	if (mType == GHOST_TYPE_MAP_ITEM)
	{
		if (getDress(AVATAR_TYPE_CLOTH))
		{
		 	sprintf(url, "%s_%d", SystemData::getAnimationName(getDress(AVATAR_TYPE_CLOTH), mType, AVATAR_TYPE_CLOTH, mGhostGender).c_str(), m_state);
			m_nCurrentDress[AVATAR_TYPE_CLOTH][m_state] = getDress(AVATAR_TYPE_CLOTH);
			m_pSprite[AVATAR_TYPE_CLOTH] = CCSprite::create(url);
		}
	}
	else if (mType == GHOST_TYPE_NPC ||
		mType == GHOST_TYPE_MONSTER ||
		mType == GHOST_TYPE_SLAVE ||
		mType == GHOST_TYPE_PLANT)
	{
		if (getDress(AVATAR_TYPE_CLOTH))
		{
			if(mType == GHOST_TYPE_NPC)
			{
				sprintf(url, "%s", SystemData::getAnimationName(getDress(AVATAR_TYPE_CLOTH), mType, AVATAR_TYPE_CLOTH, mGhostGender).c_str());
			}
			else
			{
				sprintf(url, "%s_%d", SystemData::getAnimationName(getDress(AVATAR_TYPE_CLOTH), mType, AVATAR_TYPE_CLOTH, mGhostGender ,mPetReborn).c_str(), m_state);
			}
			safeToLoad(AVATAR_TYPE_CLOTH, m_state, url);
			m_nCurrentDress[AVATAR_TYPE_CLOTH][m_state] = getDress(AVATAR_TYPE_CLOTH);
			m_pSprite[AVATAR_TYPE_CLOTH] = CCSprite::create();
			if (m_pBodySprite)
			{
				m_pBodySprite->addChild(m_pSprite[AVATAR_TYPE_CLOTH]);
			}
		}
	}
	// shadow
	m_sprShadow = SystemData::getSpriteByPlist("ui.ghost.shadow");
	m_sprShadow->_setZOrder(AVATAR_SHADOW_ZORDER);
	if (m_pBodySprite)
	{
		m_pBodySprite->addChild(m_sprShadow);
	}

	initName();

	if (isDead())
	{
		setState(AVATAR_ACTION_DIE);
	}

	setMapPosition(m_direction, mTx, mTy);
	runAnimation();

	return true;
}

void AliveGhost::initName()
{
	if (!m_pBodySprite)
	{
		return;
	}

	if (!m_disName)
	{
		m_disName = LayoutData::getLabelTTF(CPModuleName::COMMON, "aliveGhostName");
		m_disName->setAnchorPoint(ccp(0.5f, 0));
		m_pBodySprite->addChild(m_disName, 10);

		if (mType == GHOST_TYPE_THIS ||
			mType == GHOST_TYPE_PLAYER ||
			mType == GHOST_TYPE_NPC ||
			mType == GHOST_TYPE_PET ||
			mType == GHOST_TYPE_SLAVE)
		{
			refreshNameLabel(true);
		}
	}
}

void AliveGhost::safeToLoad( short type, short state, const std::string& url )
{
	if(mType == GHOST_TYPE_NPC)
	{
		m_pAnimations[type][state] = SystemData::getAnimationOneDir(url);
	}
	else if (mType == GHOST_TYPE_MONSTER)
	{
		if (state == AVATAR_ACTION_DIE)
		{
			m_pAnimations[type][state] = SystemData::getAnimationOneDir(LayoutData::getString(CPModuleName::COMMON, "monsterDieAnim"));
		}
		else
		{
			m_pAnimations[type][state] = SystemData::getAnimation(url);
		}
	}
	else
	{
		m_pAnimations[type][state] = SystemData::getAnimation(url);
	}
}

void AliveGhost::runAnimation()
{
	if (isMoving())
	{
		moveOneStep();
	}
	runAvatarAnimation();
	moveBy();
}

void AliveGhost::stopAnimation()
{
	if (m_pBodySprite)
	{
		m_pBodySprite->stopAllActions();
		for(short type=0; type < AVATAR_TYPE_NUMBER; type++)
		{
			if(m_pSprite[type] && m_pAnimations[type])
			{
				m_pSprite[type]->stopAllActions();
			}
		}
	}
}

void AliveGhost::attach( CCLayer* target )
{
	Ghost::attach(target);
	setMapPosition(m_direction, mTx, mTy);
}

void AliveGhost::setNextStateCallback()
{
	if (m_statelist.empty())
	{
		m_state = AVATAR_ACTION_IDLE;
	}
	else
	{
		while (!m_statelist.empty())
		{
			StateInfo info = m_statelist.front();
			if (info.dir != -1 && m_direction != info.dir)
			{
				setDirection(info.dir);
			}
			m_state = info.state;
			if (m_state != AVATAR_ACTION_IDLE)
			{
				if(mType == GHOST_TYPE_MONSTER && m_state == AVATAR_ACTION_MAGIC)
				{
					m_state = AVATAR_ACTION_ATTACK;
				}

				if (isAttackKindState(info.skilltype))
				{
					AliveGhost* ag = dynamic_cast<AliveGhost*>(GameData::s_user->m_pGhostManager->getGhostById(info.pid));
					castSkill(info.skilltype, info.ptx, info.pty, ag);
				}
				m_statelist.pop();
				break;
			}
			else
			{
				m_statelist.pop();
			}
		}
	}
	runAnimation();
}

short AliveGhost::getState() const
{
	return m_state;
}

short AliveGhost::getDirection() const
{
	return m_direction;
}

void AliveGhost::setDirection(int dir)
{
	m_direction = dir;
}

void AliveGhost::setState(StateInfo info)
{
	setState(info.state , info.dir, &info);
}

void AliveGhost::setState( short state , int dir)
{
	if (state == AVATAR_ACTION_DIE)
	{
		if (mType == GHOST_TYPE_MONSTER)
		{
			if (m_sprShadow)
			{
				m_sprShadow->setVisible(false);
			}
			GameRole* myRole = GameData::getMyRole();
			if (myRole && myRole->getTheAim() == this)
			{
				myRole->changeTheAim(NULL);
				if (!myRole->checkGhostIsOwn(this) && NPCFunctionData::checkIsQuestMonster(this->getDress(AVATAR_TYPE_CLOTH)))
				{
					myRole->setQuestDoing(true);
					myRole->updateDoingQuest();	
				}	
			}
		}
	}
	setState(state, dir, NULL);
}

void AliveGhost::setState( short state , int dir, StateInfo* info)
{
	if (m_state == AVATAR_ACTION_IDLE && m_statelist.empty())
	{
		if (dir != -1 &&
			dir != m_direction)
		{
			setDirection(dir);
		}

		if (state != AVATAR_ACTION_IDLE)
		{
			m_state = state;
			if (info)
			{
				if (isAttackKindState(info->skilltype))
				{
					AliveGhost* gost = dynamic_cast<AliveGhost*>(GameData::s_user->m_pGhostManager->getGhostById(info->pid));
					castSkill(info->skilltype, info->ptx, info->pty, gost);
					const int skillEnum = info->skilltype/10;
					if (m_state == AVATAR_ACTION_RUN && skillEnum == SKILL_TYPE_YeManChongZhuang)
					{
						m_state = AVATAR_ACTION_IDLE;
					}
				}
			}
			runAnimation();
		}
	}
	else if (m_state == AVATAR_ACTION_DIE)
	{
		if (state == AVATAR_ACTION_IDLE &&
			!isDead())
		{
			m_state = state;
			runAnimation();
		}
	}
	else
	{
		if (!info)
		{
			StateInfo sinfo;
			sinfo.state = state;
			sinfo.dir = dir;
			info = &sinfo;
		}

		if (!m_statelist.empty())
		{
			m_statelist.pop();
		}
		m_statelist.push(*info);
	}
}

void AliveGhost::setMapPosition(int dir, int tx, int ty)
{
	Ghost::setMapPosition(dir, tx, ty);
	m_serverDir = dir;
	setDirection(m_serverDir);
	m_serverTx = mTx = tx;
	m_serverTy = mTy = ty;
}

int AliveGhost::getNextTilePosX() const
{
	return mTx+tile_step[m_direction][0];
}

int AliveGhost::getNextTilePosY() const
{
	return mTy+tile_step[m_direction][1];
}

int AliveGhost::getNextTwoTilePosX() const
{
	return mTx+tile_step[m_direction][0]*2;
}

int AliveGhost::getNextTwoTilePosY() const
{
	return mTy+tile_step[m_direction][1]*2;
}

void AliveGhost::moveOneStep()
{
	if(m_state==AVATAR_ACTION_RUN)
	{
		//modify the tile position of the role 
		mTx += tile_step[m_direction][0]*2;
		mTy += tile_step[m_direction][1]*2;
	}
	else if(m_state==AVATAR_ACTION_WALK)
	{
		//modify the tile position of the role 
		mTx += tile_step[m_direction][0];
		mTy += tile_step[m_direction][1];
	}
	AudioLoader::play(Sound::Effect::zoulu);
}

bool AliveGhost::isMoving() const
{
	return m_state == AVATAR_ACTION_RUN || m_state == AVATAR_ACTION_WALK;
}

void AliveGhost::update( float dt )
{
	if(m_pBodySprite)
	{
		updateEffectBuff();

		if (mHPChangeDelayTime >= 0.5f)
		{
			refreshHPChangeList();
			mHPChangeDelayTime = 0;
		}
		mHPChangeDelayTime += 0.1f;
	}
}

void AliveGhost::forceMoveTo( int dir, int x, int y )
{
	CCLog("%s force Move to %d:%d", mName.c_str(), x, y);
	m_serverDir = dir;
	setDirection(m_serverDir);
	m_serverTx = mTx = x;
	m_serverTy = mTy = y;
	if(mType == GHOST_TYPE_THIS)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->m_bAutoMove = false;
	}
	setMapPosition(dir,mTx,mTy);
	m_state = AVATAR_ACTION_IDLE;
	while(!m_statelist.empty())
	{
		m_statelist.pop();
	}
	runAnimation();
	
}

bool AliveGhost::isSelected( const CCPoint &touchPos )
{
	if(isDead())
	{
		return false;
	}

	if (mType == GHOST_TYPE_COLLECTION
		|| mType == GHOST_TYPE_MAP_ITEM)
	{
		return Ghost::isSelected(touchPos);
	}

	if (m_pAnimations[AVATAR_TYPE_CLOTH][AVATAR_ACTION_IDLE] == NULL)
	{
		return false;
	}

	if(m_pAnimations[AVATAR_TYPE_CLOTH][m_state] == NULL)
	{
		return false;
	}

	if (mType == GHOST_TYPE_PET
		|| mType == GHOST_TYPE_SLAVE)
	{
		if (mOwnerPid == HeroData::getPID())
		{
			return false;
		}
	}

	CCSize clothSize = mClothSizeByArea;
	CCPoint clothOffset = mClothOffsetByArea;
	if (m_direction > DIR_DOWN)
	{
		clothOffset.x = -clothOffset.x;
	}

	const CCPoint &originPt = ccpSub(clothOffset, ccp(clothSize.width/2, clothSize.height/2));
	const CCPoint &clothPt = m_pSprite[AVATAR_TYPE_CLOTH]->getPosition();
	const CCPoint &pos = m_pBodySprite->convertToNodeSpace(touchPos);
	CCRect rect = CCRectZero;
	rect.origin = ccpAdd(clothPt, originPt);
	rect.size = clothSize;
	return rect.containsPoint(pos);
}

void AliveGhost::setLevel(int lv)
{
	mLevel = lv;
}

void AliveGhost::setPetRebornLv( int lv )
{
	mPetReborn = lv;
}


void AliveGhost::setDogSid( int dSid )
{
	mDogSid = dSid;
}

const static int SEL_ATTACKED_EFFECT = 201411;
void AliveGhost::showBeAttackedEffect(bool issel)
{
	if (issel)
	{
		if (m_pBodySprite->getChildByTag(SEL_ATTACKED_EFFECT) == NULL)
		{
			CCSprite *selAnim = EffectSprite::create(Effect::effect_attack_by_stone);
			if (selAnim)
			{
				m_pBodySprite->addChild(selAnim, 0, SEL_ATTACKED_EFFECT);
				selAnim->_setZOrder(-1);
				selAnim->setVisible(true);
			}
		}
	}
	else
	{
		CCNode* node = m_pBodySprite->getChildByTag(SEL_ATTACKED_EFFECT);
		if (node)
		{
			node->setVisible(false);
			node->removeFromParent();
		}
	}
}
const static int BE_FROZEN_EFFECT = 2014112;
void AliveGhost::showBeFrozenEffect( bool isFrozen )
{
	if (isFrozen)
	{
		if (m_pBodySprite->getChildByTag(BE_FROZEN_EFFECT) == NULL)
		{
			CCSprite *selAnim = EffectSprite::create(Effect::effect_freezon_byice);
			if (selAnim)
			{
				m_pBodySprite->addChild(selAnim, 0, BE_FROZEN_EFFECT);
//				selAnim->_setZOrder(-1);
				selAnim->setVisible(true);
			}
		}
	}
	else
	{
		CCNode* node = m_pBodySprite->getChildByTag(BE_FROZEN_EFFECT);
		if (node)
		{
			node->setVisible(false);
			node->removeFromParent();
		}
	}
}


void AliveGhost::toBeSelected( bool issel )
{
	GhostSelectedAnim *anim = GhostSelectedAnim::node();
	if (issel)
	{
		anim->show();
		attachMe(anim);
	}
	else
	{
		anim->hide();
	}
}

void AliveGhost::castSkill( int type, int x, int y, AliveGhost* aim )
{	
	if (mType == GHOST_TYPE_PLAYER ||
		mType == GHOST_TYPE_THIS)
	{
		if (isAttackKindState(type))
		{
			std::string skillSound;
			StaticData::getSkillSound(type, skillSound);
			if (skillSound.empty())
			{
				if (mGhostGender == UserData::SEX_MALE)
				{
					AudioLoader::play(Sound::Effect::nangongji);
				}
				else
				{
					AudioLoader::play(Sound::Effect::nvgongji);
				}
			}
			else
			{
				AudioLoader::play(skillSound);
			}
		}
	}
	m_skill->runSkill(type, x, y, aim);
}

void AliveGhost::addInjury( bool lifeChange, int data )
{
	CCNode *showNode = NULL;
	if (lifeChange)
	{
		if (data != 0)
		{
			char head = '%';
			if(data < 0) 
			{ 
				data = -data;
				head = '0';
			}
			char strdhp[60];
			sprintf(strdhp, ":%d", data);
			const std::string &path = LayoutData::getString(CPModuleName::COMMON, "combatNumber");
			const CCSize &size = LayoutData::getSize(CPModuleName::COMMON, "combatNumber");
			showNode = CCLabelAtlas::create(strdhp, path.c_str(), size.width, size.height, head);
		}

		if (isDead())
		{
			if (mType == GHOST_TYPE_PLAYER ||
				mType == GHOST_TYPE_THIS)
			{
				if (mGhostGender == UserData::SEX_MALE)
				{
					AudioLoader::play(Sound::Effect::nansiwang);
				}
				else
				{
					AudioLoader::play(Sound::Effect::nvsiwang);
				}
			}
		}
	}
	else
	{
		if (data == Combat::batt_immunity)
		{
			showNode = LayoutData::getSprite(CPModuleName::MAIN_UI, "combatImmunity");
		}
		else if (data == Combat::batt_miss)
		{
			showNode = LayoutData::getSprite(CPModuleName::MAIN_UI, "combatMiss");
		}
		// 添加暴击和防爆特效判断
        else if (data == Combat::batt_critical)
       {
    showNode = LayoutData::getSprite(CPModuleName::MAIN_UI, "combatcritical");//暴击
        }
        else if (data == Combat::batt_anticritical)
        {
    showNode = LayoutData::getSprite(CPModuleName::MAIN_UI, "combatanticritical");//防爆
        }
		else if (data == Combat::batt_reflect)
        {
    showNode = LayoutData::getSprite(CPModuleName::MAIN_UI, "combatreflect");//反弹
	}


	}

	if (showNode)
	{
		m_pBodySprite->addChild(showNode);
		showNode->_setZOrder(AVATAR_DAMEGE_ZORDER);
		showNode->setAnchorPoint(ccp(0.5, 0));

		int h = 100;
		if(m_pSprite[0])
		{
			h = m_pSprite[0]->getTextureRect().size.height;
		}
		showNode->setPosition(ccp(0, 80));
		showNode->runAction(CCSequence::create(
			CCMoveBy::create(1.0f, ccp(0, h)),
			CCActionInstantRemoveFromParent::create(),
			NULL));
	}
}

void AliveGhost::updateHpOnHead()
{
	if (isDead() ||
		mHp >= mMaxHp)
	{
		if (m_pHpBarBkg)
		{
			m_pHpBarBkg->removeFromParentAndCleanup(true);
			m_pHpBarBkg = NULL;
			m_pHpBarOnHead = NULL;
		}

		if (isDead())
		{
			refreshNameLabel(false);
		}
		return;
	}

	if(!m_pHpBarBkg)
	{
		m_pHpBarBkg = CCSprite::createWithSpriteFrameName(LayoutData::getString(CPModuleName::COMMON, "lifeBarBoardFrameName").c_str());
		attachMe(m_pHpBarBkg);

		m_pHpBarOnHead = ProgressBar::createWithSpriteFrameName(LayoutData::getString(CPModuleName::COMMON, "lifeBarFrameName").c_str());
		m_pHpBarOnHead->setAnchorPoint(CCPointZero);
		m_pHpBarOnHead->setPosition(CCPointZero);
		m_pHpBarBkg->addChild(m_pHpBarOnHead);
	}

	if(m_pHpBarBkg && m_pHpBarOnHead)
	{
		const int oy = LayoutData::getInt(CPModuleName::COMMON, "ghostLifeBarOy");
		CCSize clothSize = CCSizeZero;
		CCPoint clothOffset = CCPointZero;
		getClothSizeByHeight(clothSize, clothOffset);
		m_pHpBarBkg->setAnchorPoint(ccp(0.5, 0));
		m_pHpBarBkg->setPosition(ccp(0, clothOffset.y + clothSize.height/2 + oy));
		m_pHpBarOnHead->setNewProgress(mHp, mMaxHp);
	}
}

bool AliveGhost::isSheltered()
{
	if (mTx < 0 || mTy < 0 ||
		mTx >= GameData::s_user->m_pPixesMap->mLogicWidth ||
		mTy >= GameData::s_user->m_pPixesMap->mLogicHeight)
	{
		//CCLog("Out of the MAP BOUND");
		return false;
	}

	if(GameData::s_user->m_pPixesMap->mBlockData)
	{
		return (GameData::s_user->m_pPixesMap->mBlockData[mTy][mTx] == 2);
		//return (GameData::s_user->m_pPixesMap->mBlockData[mTy][mTx] & 0x2) != 0;
	}
	return false;
}

void AliveGhost::handleRunRes( int tx, int ty, int dir )
{
	//run the RUN animation 
	m_state = AVATAR_ACTION_RUN;
	if(mType != GHOST_TYPE_THIS
		&& mType != GHOST_TYPE_PLAYER)
	{
		m_state = AVATAR_ACTION_WALK;
	}
	m_direction = dir;
	m_serverTx = tx;
	m_serverTy = ty;

	runAvatarAnimation();
	moveTo(tx, ty);

	mTx = tx;
	mTy = ty;
}

void AliveGhost::handleWalkRes( int tx, int ty, int dir )
{
	//run the RUN animation 
	m_state = AVATAR_ACTION_WALK;
	m_direction = dir;
	m_serverTx = tx;
	m_serverTy = ty;
	runAvatarAnimation();
	//move to the target position
	moveTo(tx,ty);
	mTx = tx;
	mTy = ty;
}

void AliveGhost::handleCollideRes( int tx, int ty, int dir )
{
	//run the RUN animation 
	m_state = AVATAR_ACTION_RUN;
	if(mType != GHOST_TYPE_THIS
		&& mType != GHOST_TYPE_PLAYER)
	{
		m_state = AVATAR_ACTION_WALK;
	}
	m_direction = dir;
	m_serverTx = tx;
	m_serverTy = ty;

	runAvatarAnimation();

	const float speedAdd = LayoutData::getFloat(CPModuleName::COMMON, "skillYeManChongZhuangSpeed");
	float speed = 1.0f + speedAdd + getExData(Entity::attr_move_speed)/100.0f;
	GameRole* pMyRole = GameData::getMyRole();
	if (pMyRole && this == pMyRole)
	{
		speed += pMyRole->CombatData[Combat::prop_Move_Speed]/100.0f;
	}
	moveTo(tx, ty, speed);

	mTx = tx;
	mTy = ty;
}

void AliveGhost::handleSetPosition( int tx, int ty )
{
	if (!m_pBodySprite)
	{
		return;
	}

	m_serverTx = tx;
	m_serverTy = ty;
	mTx = tx;
	mTy = ty;
	const CCPoint &pt = PixesMap::getPixelPoint(tx, ty);
	m_pBodySprite->setPosition(ccp(pt.x, SystemData::size_y - pt.y));
}

void AliveGhost::refreshHorseAppearanceOnly()
{
	// ????????????,???????CLOTH/HORSE/HORSEHEAD??????????
	// CLOTH????????????????????(10????????)
	if (!m_pBodySprite) return;
	if (getExData(Entity::attr_horse_ride_state) == 0) return;

	int state = m_state;
	if (m_state == AVATAR_ACTION_MINE)
	{
		state = AVATAR_ACTION_ATTACK;
	}

	int horseLevel = getExData(Entity::attr_horse_level);
	int appearLevel = getExData(Entity::attr_horse_appearance);
	int visualLevel = horseLevel;
	if (appearLevel > 0 && appearLevel <= horseLevel)
	{
		visualLevel = appearLevel;
	}

	// ???????CLOTH/HORSE/HORSEHEAD
	int refreshTypes[] = { AVATAR_TYPE_CLOTH, AVATAR_TYPE_HORSE, AVATAR_TYPE_HORSEHEAD };
	for (int i = 0; i < 3; i++)
	{
		int index = refreshTypes[i];
		if (m_pSprite[index])
		{
			m_pSprite[index]->stopAllActions();
			m_pSprite[index]->removeFromParentAndCleanup(true);
			m_pSprite[index] = NULL;
		}
	}

	// ??CLOTH
	{
		char url[64];
		if (visualLevel >= 10)
		{
			sprintf(url, "horse/zm_touming_%d", state);
		}
		else
		{
			sprintf(url,"%s_%d", SystemData::getHorseAnimationName(getDress(AVATAR_TYPE_CLOTH), AVATAR_TYPE_CLOTH, mGhostGender).c_str(), state);
		}
		safeToLoad(AVATAR_TYPE_CLOTH, state, url);
		if (m_pAnimations[AVATAR_TYPE_CLOTH][state])
		{
			m_pSprite[AVATAR_TYPE_CLOTH] = CCSprite::create();
			m_pBodySprite->addChild(m_pSprite[AVATAR_TYPE_CLOTH]);
			m_pSprite[AVATAR_TYPE_CLOTH]->runAction(m_pAnimations[AVATAR_TYPE_CLOTH][state]->getAnimate(m_direction));
			m_frameCount = m_pAnimations[AVATAR_TYPE_CLOTH][state]->getFrameCount();
		}
	}

	// ??HORSE
	{
		std::string model = "";
		LuaData::getProp("gdHorseBaseStats", visualLevel, "AppearanceImage", model);
		char url[64];
		sprintf(url, "horse/%s_%d", model.c_str(), state);
		safeToLoad(AVATAR_TYPE_HORSE, state, url);
		if (m_pAnimations[AVATAR_TYPE_HORSE][state])
		{
			m_pSprite[AVATAR_TYPE_HORSE] = CCSprite::create();
			m_pBodySprite->addChild(m_pSprite[AVATAR_TYPE_HORSE]);
			m_pSprite[AVATAR_TYPE_HORSE]->runAction(m_pAnimations[AVATAR_TYPE_HORSE][state]->getAnimate(m_direction));
		}
	}

	// ??HORSEHEAD
	{
		std::string model = "";
		LuaData::getProp("gdHorseBaseStats", visualLevel, "HeadImage", model);
		char url[64];
		sprintf(url, "horse/%s_%d", model.c_str(), state);
		safeToLoad(AVATAR_TYPE_HORSEHEAD, state, url);
		if (m_pAnimations[AVATAR_TYPE_HORSEHEAD][state])
		{
			m_pSprite[AVATAR_TYPE_HORSEHEAD] = CCSprite::create();
			m_pBodySprite->addChild(m_pSprite[AVATAR_TYPE_HORSEHEAD]);
			m_pSprite[AVATAR_TYPE_HORSEHEAD]->runAction(m_pAnimations[AVATAR_TYPE_HORSEHEAD][state]->getAnimate(m_direction));
		}
	}
}

void AliveGhost::runAvatarAnimation()//骑马外观
{
	if (!m_pBodySprite)
	{
		return;
	}
	int state = m_state;
	if (m_state == AVATAR_ACTION_MINE)
	{
		state = AVATAR_ACTION_ATTACK;
	}
	stopAnimation();

	// 模型转换
	if (mType == GHOST_TYPE_THIS || mType == GHOST_TYPE_PLAYER)
	{
		// 人物的马上动作只有两种
		if (getExData(Entity::attr_horse_ride_state) > 0)
		{
			if (state != AVATAR_ACTION_RUN && state != AVATAR_ACTION_WALK && state != AVATAR_ACTION_IDLE )
			{
				setExData(Entity::attr_horse_ride_state, 0);
				setDress(AVATAR_TYPE_HORSE, 0);
				// 自己的话同步属性
				if (mType == GHOST_TYPE_THIS)
				{
					HeroData::setProp(Entity::attr_horse_ride_state, 0);

					MsgRideReq* msg=new MsgRideReq;
					msg->OnOrOff = 0;
					HandleMessage::sendMessage(msg);
				}
			}
		}
	}

	// 贴图部位
	std::vector<int> vecAvatar;
	if (getExData(Entity::attr_horse_ride_state) == 0)
	{	
		if (m_pSprite[AVATAR_TYPE_HORSE])
		{
			m_pSprite[AVATAR_TYPE_HORSE]->removeFromParentAndCleanup(true);
			m_pSprite[AVATAR_TYPE_HORSE] = NULL;
		}
		if (m_pSprite[AVATAR_TYPE_HORSEHEAD])
		{
			m_pSprite[AVATAR_TYPE_HORSEHEAD]->removeFromParentAndCleanup(true);
			m_pSprite[AVATAR_TYPE_HORSEHEAD] = NULL;
		}
		vecAvatar.push_back(AVATAR_TYPE_CLOTH);
		vecAvatar.push_back(AVATAR_TYPE_WEAPON);
		vecAvatar.push_back(AVATAR_TYPE_WINGS);
		vecAvatar.push_back(AVATAR_TYPE_YUANSHEN);//元神外观添加
	}
	else
	{
		if (m_pSprite[AVATAR_TYPE_WEAPON])
		{
			m_pSprite[AVATAR_TYPE_WEAPON]->removeFromParentAndCleanup(true);
			m_pSprite[AVATAR_TYPE_WEAPON] = NULL;
		}
		if (m_pSprite[AVATAR_TYPE_WINGS])
		{
			m_pSprite[AVATAR_TYPE_WINGS]->removeFromParentAndCleanup(true);
			m_pSprite[AVATAR_TYPE_WINGS] = NULL;
		}
		if (m_pSprite[AVATAR_TYPE_YUANSHEN])
		{
			m_pSprite[AVATAR_TYPE_YUANSHEN]->removeFromParentAndCleanup(true);
			m_pSprite[AVATAR_TYPE_YUANSHEN] = NULL;//元神外观作用是骑上坐骑时清理该外观
		}
		vecAvatar.push_back(AVATAR_TYPE_CLOTH);
		vecAvatar.push_back(AVATAR_TYPE_HORSE);
		vecAvatar.push_back(AVATAR_TYPE_HORSEHEAD);
	}

//	for ( int index = 0; index < AVATAR_TYPE_NUMBER; index ++ ) 
	for (std::vector<int>::iterator it = vecAvatar.begin(); it != vecAvatar.end(); it++ ) 
	{
		int index = *it;
		if ((getDress(index) == 0) && (getExData(Entity::attr_horse_ride_state) == 0))
		{
			// 没有这类装饰
			if (m_pSprite[index])
			{
				m_pSprite[index]->removeFromParentAndCleanup(true);
				m_pSprite[index] = NULL;
			}
			continue;
		}

		if (m_nCurrentDress[index][state] != getDress(index) || (index == AVATAR_TYPE_CLOTH || index == AVATAR_TYPE_HORSE || index == AVATAR_TYPE_HORSEHEAD))
		{
			// 新装饰
			char url[64];
			if (mType == GHOST_TYPE_THIS || mType == GHOST_TYPE_PLAYER)
			{
				if (getExData(Entity::attr_horse_ride_state) > 0)
				{
					int horseLevel = getExData(Entity::attr_horse_level);
					int appearLevel = getExData(Entity::attr_horse_appearance);
					int visualLevel = horseLevel;
					if (appearLevel > 0 && appearLevel <= horseLevel)
					{
						visualLevel = appearLevel;
					}

					if (index == AVATAR_TYPE_CLOTH)
					{
						if (visualLevel >= 10)//???????????????
						{
							sprintf(url, "horse/zm_touming_%d", state);
						}
						else
						{
							sprintf(url,"%s_%d", SystemData::getHorseAnimationName(getDress(index), index, mGhostGender).c_str(), state);
						}
					}
					if (index == AVATAR_TYPE_HORSE)
					{
						std::string model = "";
						LuaData::getProp("gdHorseBaseStats", visualLevel, "AppearanceImage", model);
						sprintf(url, "horse/%s_%d", model.c_str(), state);
					}
					if (index == AVATAR_TYPE_HORSEHEAD)
					{
						std::string model = "";
						LuaData::getProp("gdHorseBaseStats", visualLevel, "HeadImage", model);
						sprintf(url, "horse/%s_%d", model.c_str(), state);
					}
				}
				else
				{
					sprintf(url,"%s_%d", SystemData::getAnimationName(getDress(index), mType, index, mGhostGender ,mPetReborn).c_str(), state);
				}
			}
			else if(mType!=GHOST_TYPE_NPC)
			{
				sprintf(url,"%s_%d", SystemData::getAnimationName(getDress(index), mType, index, mGhostGender ,mPetReborn).c_str(), state);
			}
			else
			{
				sprintf(url,"%s", SystemData::getAnimationName(getDress(index), mType, index, mGhostGender).c_str());
			}
			const std::string &strurl = url;
			safeToLoad(index, state, strurl);
			m_nCurrentDress[index][state] = getDress(index);
		}

		if (m_pAnimations[index][state])
		{
			if (!m_pSprite[index])
			{
				m_pSprite[index] = CCSprite::create();
				m_pBodySprite->addChild(m_pSprite[index]);
			}

			m_pSprite[index]->runAction(m_pAnimations[index][state]->getAnimate(m_direction));
			if (index == AVATAR_TYPE_CLOTH)
			{
				m_frameCount = m_pAnimations[AVATAR_TYPE_CLOTH][state]->getFrameCount();
			}

			// reset zOrder
			if ((mType == GHOST_TYPE_PLAYER || mType == GHOST_TYPE_THIS)
				&& index < AVATAR_TYPE_NUMBER)
			{
				int zOrder = m_pSprite[index]->getZOrder();
				StaticData::getAnimOrderData(m_direction, state, index, zOrder);
				m_pBodySprite->reorderChild(m_pSprite[index], zOrder);
			}
		}
		else if (m_pSprite[index])
		{
			m_pSprite[index]->removeFromParentAndCleanup(true);
			m_pSprite[index] = NULL;
		}

	}
	adjustClothSize();
}

void AliveGhost::moveBy()
{
	if (!m_pBodySprite)
	{
		return;
	}

	CCAction *action = NULL;
	if (m_state == AVATAR_ACTION_RUN
		|| m_state == AVATAR_ACTION_WALK)
	{
		if (mType == GHOST_TYPE_THIS)
		{
			moveTo(mTx, mTy);
		}
	}
	else if (m_state == AVATAR_ACTION_DIE)
	{
		action = CCSequence::create(
			CCDelayTime::create(CCFlashAnimation::FRAME_TIME * m_frameCount)
			,NULL
			);
	}
	else
	{
		// 普攻动画时长随 prop_Attack_Speed 缩短(百分比: 0=原始, 100=2倍速)
		float actionDelay = CCFlashAnimation::FRAME_TIME * m_frameCount;
		if (m_state == AVATAR_ACTION_ATTACK)
		{
			// 只对本地玩家自己生效, 其它玩家/怪物保持原始速度
			float atkSpeedMul = 1.0f;
			GameRole* myRole = GameData::getMyRole();
			if (myRole && dynamic_cast<GameRole*>(this) == myRole)
			{
				atkSpeedMul = 1.0f + myRole->CombatData[Combat::prop_Attack_Speed] / 100.0f;
				if (atkSpeedMul < 0.1f) atkSpeedMul = 0.1f;
			}
			actionDelay /= atkSpeedMul;
		}
		action = CCSequence::create(
			CCDelayTime::create(actionDelay)
			,CCCallFunc::create(this, callfunc_selector(AliveGhost::setNextStateCallback))
			,NULL
			);
	}

	if (action)
	{
		m_pBodySprite->runAction(action);
	}
}

void AliveGhost::moveTo( int tx, int ty)
{
	float speed = 1.0f + getExData(Entity::attr_move_speed)/100.0f;
	GameRole* myRole = GameData::getMyRole();
	if (myRole && this == myRole)
	{
		speed += myRole->CombatData[Combat::prop_Move_Speed]/100.0f;
	}
	moveTo(tx, ty, speed);
}

void AliveGhost::moveTo( int tx, int ty, float speed )
{
	if (!m_pBodySprite)
	{
		return;
	}

	if (speed < 0.1f)
	{
		speed = 0.1f;
	}

	float moveTime = CCFlashAnimation::FRAME_TIME * m_frameCount / speed;
	if (mType == GHOST_TYPE_THIS || mType == GHOST_TYPE_PLAYER)
	{
		float baseSpeed = 0;
		StaticData::getGlobalData("roleBaseSpeed", baseSpeed);
		if (baseSpeed < 0.1f)
		{
			baseSpeed = 0.1f;
		}
		moveTime = 1/(baseSpeed * speed);
	}
	const CCPoint &pt = PixesMap::getPixelPoint(tx, ty);
	CCAction *action = CCSequence::create(
		CCMoveTo::create(moveTime, ccp(pt.x, SystemData::size_y - pt.y))
		,CCCallFunc::create(this, callfunc_selector(AliveGhost::setNextStateCallback))
		,NULL
		);
	m_pBodySprite->runAction(action);
}

void AliveGhost::setColor( const ccColor3B color )
{
	for(int i=0;i<AVATAR_TYPE_NUMBER;i++)
	{
		if(m_pSprite[i])
		{
			m_pSprite[i]->setColor(color);
		}
	}
}

void AliveGhost::setOpacity( int opacity )
{
	for(int i=0;i<AVATAR_TYPE_NUMBER;i++)
	{
		if(m_pSprite[i])
		{
			m_pSprite[i]->setOpacity(opacity);
		}
	}
}

void AliveGhost::setOpacity(CCObject* object, GLubyte opaque)
{
	CCNode *node = (CCNode*)object;
	if (node)
	{
		CCRGBAProtocol *rgbNode = dynamic_cast<CCRGBAProtocol *>(node);
		if (rgbNode)
		{
			rgbNode->setOpacity(opaque);
		}

		CCArray *childs = node->getChildren();
		if (childs && childs->count() > 0)
		{
			CCObject *child = NULL;
			CCARRAY_FOREACH(childs, child)
			{
				setOpacity(child, opaque);
			}
		}
	}
}

void AliveGhost::playEffect( CCAction* action )
{
	if (action)
	{
		if(!m_pEffectSprite)
		{
			m_pEffectSprite = CCSprite::create();
			attachMe(m_pEffectSprite);
			m_pEffectSprite->_setZOrder(5);
		}

		if(m_pEffectSprite)
		{
			m_pEffectSprite->stopAllActions();
			m_pEffectSprite->runAction(CCSequence::create(
				CCShow::create()
				, action
				, CCHide::create()
				, NULL));
		}
	}	
}
/**
 * 播放技能特效动画
 * 根据技能ID和特效类型（来源/目标）播放对应的特效动画
 * 
 * @param skillID 技能ID，用于查找对应的特效配置
 * @param isSrc 特效类型标识
 *        - true: 播放来源特效（技能释放者特效）
 *        - false: 播放目标特效（技能受击者特效）
 */
void AliveGhost::playEffect( int skillID, bool isSrc )
{
	const std::string &key = isSrc ? "effect_src" : "effect_tgt";
	std::string animName = "";
	LuaData::getProp(LuaData::SKILL, skillID, key, animName);
	if(!animName.empty() && animName != "none")
	{
		animName = "effect/" + animName;
		CCFlashAnimation *anim = SystemData::getAnimationOneDir(animName);
		if (anim)
		{
			playEffect(anim->getAnimate(0));
		}
	}
}

void AliveGhost::setGhostZOrder( int z )
{
	setZOrder(z);
}

void AliveGhost::handleHpChange(int changeHp)
{
	addInjury(true, changeHp);
	if(changeHp < 0)
	{
		if(isDead())
		{
			setState(AVATAR_ACTION_DIE);
			if(mType == GHOST_TYPE_MONSTER)
			{
				GameRole* myRole = GameData::getMyRole();
				if (myRole) myRole->someoneNeedOut(this);
			}
		}
	}
	else
	{
		if (m_state == AVATAR_ACTION_DIE)
		{
			setState(AVATAR_ACTION_IDLE);
		}
	}
}

void AliveGhost::delayHpChange( int hp, short delay )
{
	HPChangeDelay changdata;
	changdata.m_nChangType = Combat::batt_hpchange;
	changdata.m_nHpChangeDelay = delay;
	if (hp < 0)
		hp = 0;
	if (hp > mMaxHp)
		hp = mMaxHp;
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
}

void AliveGhost::delayBeAttack( int type, short delay )
{
	HPChangeDelay changdata;
	changdata.m_nChangType = type;
	changdata.m_nHpChangeDelay = delay;
	changdata.m_nHpChange = 0;
	m_nHpChangeList.push_back(changdata);
}

void AliveGhost::setMP( int mp )
{
	mMp = mp;
	if (mMp < 0)
	{
		mMp = 0;
	}
	if (mMp > mMaxMp)
	{
		mMp = mMaxMp;
	}
}

void AliveGhost::refreshNameLabel( bool visible )
{
	if (!m_disName)
	{
		return;
	}

	if (!visible)
	{
		m_disName->setVisible(false);
		return;
	}

	std::string name = mName;
	if (mType == GHOST_TYPE_MONSTER)
	{
		name += " Lv:" + SystemData::intToString(mLevel);
	}
	else if (mType == GHOST_TYPE_PET)
	{
		name = mOwnerName + LayoutData::getString(CPModuleName::COMMON, "pet");
		name += "(";
		if (mPetReborn > 0)
		{
			name += StringUtils::toString(mPetReborn) + LayoutData::getString(CPModuleName::COMMON, "reborn");
		}
		name +=	StringUtils::toString(mLevel) + LayoutData::getString(CPModuleName::COMMON, "level");
		name += ")";
	}
	else if (mType == GHOST_TYPE_SLAVE)
	{
		name = mOwnerName + LayoutData::getString(CPModuleName::COMMON, "dog");
		if (mDogSid == 2)
		{
			name = mOwnerName + LayoutData::getString(CPModuleName::COMMON, "dog2");
		}
		name += "(";
		name += StringUtils::toString(mLevel) + LayoutData::getString(CPModuleName::COMMON, "level");
		name += ")";
	}

	DebugCode(
		int sid = getDress(AVATAR_TYPE_CLOTH);
		if(sid>=0)
		{
			char staticid[20];
			sprintf(staticid,"(%d)",sid);
			name += staticid;
		}
		name += SystemData::intToString(mID);
	);
	if (m_disName->getString()!=name)
	{
		m_disName->setString(name.c_str());
	}
	
	// color
	if (mType == GHOST_TYPE_NPC)
	{
		m_disName->setColor(ccGREEN);
	}
	else if (mType == GHOST_TYPE_MONSTER ||
		mType == GHOST_TYPE_PLANT)
	{
		m_disName->setColor(ccc3(0xFF, 0x99, 0x22));
	}
	else if (mType == GHOST_TYPE_SLAVE)
	{
		ccColor3B color;
		StaticData::getDogNameColor(mLevel, color);
		m_disName->setColor(color);
	}
	else if (mType == GHOST_TYPE_PET)
	{
		m_disName->setColor(ccWHITE);
	}
	else
	{
		int pkDropFlag = 1;
		StaticData::getMapPKRedFlag(GameData::s_user->mMap.mID, pkDropFlag);
		if (pkDropFlag)
		{
			const int pkState = getExData(Entity::attr_pkstate);
			if (pkState == Entity::pks_yellow)
				m_disName->setColor(ccYELLOW);
			else if (pkState == Entity::pks_gray)
				m_disName->setColor(LayoutData::getColor3(CPModuleName::COMMON, "brown"));
			else if (pkState == Entity::pks_red)
				m_disName->setColor(ccRED);
			else
				m_disName->setColor(ccWHITE);
		}
		else
		{
			if (GameData::getGhostManager() && GameData::getGhostManager()->isTargetFriendly(this))
			{
				m_disName->setColor(ccWHITE);
			}
			else
			{
				m_disName->setColor(ccRED);
			}
		}
	}
	
	// pos
	refreshNameLabelPosition();

	//
	m_disName->setVisible(true);
}

void AliveGhost::adjustClothSize()
{
	// height
	for (int i = AVATAR_ACTION_IDLE; i < AVATAR_ACTION_COUNT; i++)
	{
		forEachClothFrame(i, DIR_UP, callfuncO_selector(AliveGhost::onAdjustClothSizeByHeight));
	}
	refreshNameLabelPosition();
	updateHpOnHead();

	// area
	mClothSizeByArea = CCSizeZero;
	mClothOffsetByArea = CCPointZero;
	forEachClothFrame(m_state, m_direction, callfuncO_selector(AliveGhost::onAdjustClothSizeByArea));
}

void AliveGhost::forEachClothFrame( int state, int dir, SEL_CallFuncO handleFuc )
{
	if (state < AVATAR_ACTION_IDLE || AVATAR_ACTION_COUNT <= state)
	{
		return;
	}

	if (handleFuc == NULL)
	{
		return;
	}

	CCFlashAnimation *anim = m_pAnimations[AVATAR_TYPE_CLOTH][state];
	if (anim)
	{
		CCArray *frames = anim->getSpriteFrames(dir);
		if (frames && frames->count() > 0)
		{
			CCObject *obj = NULL;
			CCARRAY_FOREACH(frames, obj)
			{
				CCAnimationFrame *animFrame = dynamic_cast<CCAnimationFrame*>(obj);
				if (animFrame)
				{
					CCSpriteFrame *frame = animFrame->getSpriteFrame();
					if (frame)
					{
						(this->*handleFuc)(frame);
					}
				}
			}
		}
	}
}

void AliveGhost::onAdjustClothSizeByHeight( CCObject *frame )
{
	CCSpriteFrame *spriteFrame = dynamic_cast<CCSpriteFrame *>(frame);
	if (spriteFrame)
	{
		const CCSize &frameSize = spriteFrame->getRect().size;
		if (frameSize.height > mClothSizeByHeight.height)
		{
			mClothSizeByHeight = frameSize;
			mClothOffsetByHeight = spriteFrame->getOffset();
		}
	}
}

void AliveGhost::onAdjustClothSizeByArea( CCObject *frame )
{
	CCSpriteFrame *spriteFrame = dynamic_cast<CCSpriteFrame *>(frame);
	if (spriteFrame)
	{
		const CCSize &frameSize = spriteFrame->getRect().size;
		if ((frameSize.width * frameSize.height) > (mClothSizeByArea.width * mClothSizeByArea.height))
		{
			mClothSizeByArea = frameSize;
			mClothOffsetByArea = spriteFrame->getOffset();
		}
	}
}

void AliveGhost::getClothSizeByHeight( CCSize &size, CCPoint &offset ) const
{
	size = mClothSizeByHeight;
	offset = mClothOffsetByHeight;
}

void AliveGhost::setOwnerInfo( int ownerPID, const std::string &ownerName )
{
	mOwnerPid = ownerPID;
	mOwnerName = ownerName;
}

void AliveGhost::getOwnerInfo( int &ownerPID, std::string &ownerName )
{
	ownerPID = mOwnerPid;
	ownerName = mOwnerName;
}

/**
 * 更新实体的特效和Buff状态表现
 * 根据当前生效的Buff类型，更新实体的视觉效果（透明度、颜色、附加特效等）
 * 主要包括：隐身、中毒、狂暴、魔法盾、特殊技能效果等
 */
void AliveGhost::updateEffectBuff()
{
	// 定义常用颜色常量
	const ccColor3B &WHITE = ccc3(255, 255, 255);
	const ccColor3B &GREEN = ccc3(0, 255, 0);		// 中毒效果
	const ccColor3B &RED = ccc3(255, 0, 0);		// 狂暴效果
	const ccColor3B &PALSY = ccc3(175, 175, 175);	// 麻痹/眩晕效果

	// 1. 隐身/可见性相关效果处理
	//    优先级：隐身 > 显隐 > 遮蔽 > 正常
	if (hasEffectBuff(Effect::effect_hide))		// 隐身效果
	{
		if (mType == GHOST_TYPE_THIS)			// 如果是自身角色
		{
			setOpacity(160);					// 自身可见但半透明（160/255）
		}
		else									// 如果是其他实体
		{
			setOpacity(m_pBodySprite, 0);		// 完全透明（不可见）
			GameRole* myRole = GameData::getMyRole();
			if (myRole) myRole->someoneNeedOut(this);	// 通知主角色有实体进入隐身
		}
	}
	else if (hasEffectBuff(Effect::effect_visable))	// 显隐效果（被探测到）
	{
		setOpacity(160);						// 半透明显示
	}
	else if (isSheltered())					// 遮蔽效果
	{
		setOpacity(120);						// 更深的半透明
	}
	else										// 正常状态
	{
		setOpacity(m_pBodySprite, 255);			// 完全不透明
	}

	// 2. 颜色变化效果处理
	//    优先级：中毒绿 > 中毒红 > 狂暴红 > 麻痹灰 > 正常白
	if (hasEffectBuff(Effect::effect_posion_green) ||
		hasEffectBuff(Effect::effect_posion_red))	// 中毒效果
	{
		setColor(GREEN);						// 绿色（中毒）
	}
	else if (hasEffectBuff(Effect::effect_violent))	// 狂暴效果
	{
		setColor(RED);							// 红色（狂暴）
	}
	else if (hasEffectBuff(Effect::effect_daze))	// 麻痹/眩晕效果
	{
		setColor(PALSY);						// 灰色（麻痹）
	}
	else										// 正常状态
	{
		setColor(WHITE);						// 白色（正常）
	}

	// 3. 魔法盾特效处理
	if (hasEffectBuff(Effect::effect_mitigate))	// 魔法盾Buff
	{
		if (!m_pSprMofadun)						// 如果还没有创建魔法盾精灵
		{
			std::string skill_anim;
			// 从Lua配置获取魔法盾特效动画
			// SKILL_TYPE_MoFaDun * 10 + 1 构造技能ID
			LuaData::getProp(LuaData::SKILL, SKILL_TYPE_MoFaDun * 10 + 1, "effect_mid", skill_anim);
			
			if(!skill_anim.empty())
			{
				skill_anim = "effect/" + skill_anim;	// 添加特效路径前缀
				CCFlashAnimation* mofadun = SystemData::getAnimationOneDir(skill_anim);
				
				if (mofadun)						// 成功加载动画
				{
					// 创建魔法盾精灵并添加到实体
					m_pSprMofadun = CCSprite::create();
					attachMe(m_pSprMofadun);		// 附加到当前实体
					// 运行动画（循环播放）
					m_pSprMofadun->runAction(CCRepeatForever::create(mofadun->getAnimate(0)));
					m_pSprMofadun->_setZOrder(4);	// 设置渲染层级
				}
			}
		}
	}
	else	// 没有魔法盾效果
	{
		if (m_pSprMofadun)						// 如果存在魔法盾精灵
		{
			// 移除魔法盾特效
			m_pSprMofadun->removeFromParentAndCleanup(true);
			m_pSprMofadun = NULL;
		}

		if(mType == GHOST_TYPE_THIS)			// 如果是自身角色
		{
			if (m_skill->hasSkill(SKILL_TYPE_MoFaDun * 10))	// 检查是否有魔法盾技能
			{
				m_skill->removeSkill(SKILL_TYPE_MoFaDun * 10);	// 移除技能
			}
		}
	}
	
	// 注释：预留位置，可用于添加"陨石攻击特效"等

	// 4. 转生技能：烈焰重生特效
	if (hasEffectBuff(Effect::effect_firereborn))	// 烈焰重生效果
	{
		// 设置特效外观ID（用于后续外观更新）
		m_nDress[AVATAR_TYPE_EFFECT] = SKILL_TYPE_LieYanChongSheng * 10 + 1;
	}
	else
	{
		m_nDress[AVATAR_TYPE_EFFECT] = 0;		// 清除特效外观
	}

	// 5. 显示被攻击和冰冻特效
	showBeAttackedEffect(hasEffectBuff(Effect::effect_be_attacking));	// 被攻击特效
	showBeFrozenEffect(hasEffectBuff(Effect::effect_freezon_ice));		// 冰冻特效
}

bool AliveGhost::hasEffectBuff( int buffID )
{
	if (buffID < 0)
	{
		return false;
	}

	const int buffList = getExData(Entity::attr_effect_data);
	int mark = 1 << buffID;
	int result = buffList & mark;
	return (result != 0);
}

bool AliveGhost::isDead()
{
	return (mHp <= 0);
}

void AliveGhost::refreshNameLabelPosition()
{
	if (m_disName)
	{
		const int oy = LayoutData::getInt(CPModuleName::COMMON, "ghostNameOy");
		CCSize clothSize = CCSizeZero;
		CCPoint offset = CCPointZero;
		getClothSizeByHeight(clothSize, offset);

		float posY = clothSize.height/2 + offset.y + oy;
		if (mType == GHOST_TYPE_NPC)
		{
			int testJob = 0, testGender = 0, cityMasterFlag = 0;
			StaticData::getFirstRankJobTest(mStaticID, testJob, testGender);
			StaticData::getCityMasterFlag(mStaticID, cityMasterFlag);
			if ((testJob && testGender) ||
				cityMasterFlag)
			{
				posY = LayoutData::getInt(CPModuleName::COMMON, "firstRankJobNameY");
			}
		}
		
		m_disName->setPositionY(posY);
	}
}

void AliveGhost::refreshHPChangeList()
{
	int hpTotalChange = 0;
	for (int i = 0; i < (int)m_nHpChangeList.size(); i++)
	{
		const HPChangeDelay &data = m_nHpChangeList[i];
		if (data.m_nChangType == Combat::batt_hpchange)
		{
			hpTotalChange += data.m_nHpChange;
		}
		else
		{
			addInjury(false, data.m_nChangType);
		}
	}
	m_nHpChangeList.clear();

	if (hpTotalChange != 0)
	{
		handleHpChange(hpTotalChange);
	}
}

void AliveGhost::setDress( int dressType, int dressID )
{
	if (AVATAR_TYPE_CLOTH <= dressType &&
		dressType < AVATAR_TYPE_NUMBER)
	{
		m_nDress[dressType] = dressID;
		if (dressType == AVATAR_TYPE_WEAPON)
		{
			mRealWeapon = dressID;
		}
		
		const bool isPlayer = (mType == GHOST_TYPE_PLAYER || mType == GHOST_TYPE_THIS);
		if (isPlayer)
		{
			testSuitWeapon();
		}
	}
}
// 获取角色指定类型的外观装备ID
int AliveGhost::getDress( int dressType ) const
{
	if (AVATAR_TYPE_CLOTH <= dressType &&
		dressType < AVATAR_TYPE_NUMBER)
	{
		if (mType == GHOST_TYPE_THIS)
		{
			int dress[AVATAR_TYPE_NUMBER] = {0, 0, 0, m_nDress[AVATAR_TYPE_EFFECT], 0};
			int flag = 0;
			StaticData::getMapChengBaTianXiaFlag(GameData::getCurrentMap()->mID, flag);
			if (flag != 0)
			{
				StaticData::getChengBaTianXiaEquip(mGhostGender, dress[AVATAR_TYPE_CLOTH],
					dress[AVATAR_TYPE_WEAPON],
					dress[AVATAR_TYPE_WINGS]);
				return dress[dressType];
			}
		}
		else if (mType == GHOST_TYPE_PLAYER)
		{
			int dress[AVATAR_TYPE_NUMBER] = {0, 0, 0, m_nDress[AVATAR_TYPE_EFFECT], 0};
			int flag = 0;
			StaticData::getMapChengBaTianXiaFlag(GameData::getCurrentMap()->mID, flag);
			if (flag != 0)
			{
				StaticData::getChengBaTianXiaEquip(mGhostGender, 
					dress[AVATAR_TYPE_CLOTH],
					dress[AVATAR_TYPE_WEAPON], 
					dress[AVATAR_TYPE_WINGS]);
				return dress[dressType];
			}
			else if (UserData::getIntData(HeroData::getPID(), CPUserData::USE_DEFAULT_EQUIP) != 0)
			{
				StaticData::getDefaultEquip(mLevel, mGhostGender,
					dress[AVATAR_TYPE_CLOTH], 
					dress[AVATAR_TYPE_WEAPON],
					dress[AVATAR_TYPE_WINGS]);
				return dress[dressType];
			}			
		}
		else if (mType == GHOST_TYPE_NPC
			&& UserData::getIntData(HeroData::getPID(), CPUserData::NPC_DEFAULT_EQUIP) != 0)
		{
			int dress[AVATAR_TYPE_NUMBER] = {0, 0, 0, 0, 0};
			StaticData::getNPCDefaultEquip(mStaticID, dress[AVATAR_TYPE_CLOTH]);
			return dress[dressType];
		}
		return m_nDress[dressType];
	}
	return 0;
}

void AliveGhost::testSuitWeapon()
{
	if (UserData::getIntData(HeroData::getPID(), CPUserData::USE_DEFAULT_EQUIP) != 0)
	{
		return;
	}

	if (mRealWeapon > 0)
	{
		const int dressID = getDress(AVATAR_TYPE_CLOTH);
		if (dressID > 0)
		{
			int suitWeapon = 0;
			StaticData::getSuitWeapon(dressID, suitWeapon);
			if (suitWeapon > 0)
			{
				m_nDress[AVATAR_TYPE_WEAPON] = suitWeapon;
				return;
			}
		}
		m_nDress[AVATAR_TYPE_WEAPON] = mRealWeapon;
	}
}
//这段代码是设置角色的额外属性数据，并在设置移动速度时更新动画播放速度。
//如果要将元神外观的动画速度也包含在内，需要修改代码：
void AliveGhost::setExData( int type, int data )
{
	mExData[type] = data;
		switch (type)
		{
		case Entity::attr_horse_appearance:
			{
				// ????????????,???????HORSE/HORSEHEAD??????????
				refreshHorseAppearanceOnly();
				break;
			}
		case Entity::attr_pkstate:
		{
			refreshNameLabel(true);
			break;
		}
	case Entity::attr_move_speed:
		{
			float speedRatio = 1.0000001f + data/100.0f;
			GameRole* pMyRole = GameData::getMyRole();
			if (pMyRole && this == pMyRole)
			{
				speedRatio += pMyRole->CombatData[Combat::prop_Move_Speed]/100.0f;
			}
			const float speed = speedRatio;
			CCLog(">>>Speed ratio = %f", speed);
			const int animCnt = 3;
			const int actionCnt = 3;
			const int nAnimType[animCnt] = {AVATAR_TYPE_CLOTH, AVATAR_TYPE_WEAPON, AVATAR_TYPE_WINGS};
			const int nAction[actionCnt] = {AVATAR_ACTION_WALK, AVATAR_ACTION_RUN, AVATAR_ACTION_ATTACK};
			for (int i = 0; i < animCnt; i++)
			{
				for (int j = 0; j < actionCnt; j++)
				{
					CCFlashAnimation* pAnim = m_pAnimations[nAnimType[i]][nAction[j]];
					if (pAnim)
					{
						pAnim->setSpeed(speed);
					}	
				}
			}
			break;
		}
	}
}

int AliveGhost::getExData( int type ) const
{
	ExData::const_iterator it = mExData.find(type);
	if (it != mExData.end())
	{
		return it->second;
	}
	return 0;
}

void AliveGhost::setExStr( int type, const std::string &str )
{
	mExStr[type] = str;
}

std::string AliveGhost::getExStr( int type ) const
{
	ExStr::const_iterator it = mExStr.find(type);
	if (it != mExStr.end())
	{
		return it->second;
	}
	return "";
}

void AliveGhost::clearExData()
{
	mExData.clear();
	mExStr.clear();
}

bool AliveGhost::isAttackKindState( int skillID )
{
	if (m_state == AVATAR_ACTION_MAGIC ||
		m_state == AVATAR_ACTION_ATTACK ||
		m_state == AVATAR_ACTION_MINE)
	{
		return true;
	}
	else if (m_state == AVATAR_ACTION_IDLE ||
		m_state == AVATAR_ACTION_RUN)
	{
		const int skillEnum = skillID/10;
		if (skillEnum == SKILL_TYPE_YeManChongZhuang)
		{
			return true;
		}
	}
	return false;
}


///////////GhostSelectedAnim///////////////////////////////////////////
static const int SEL_ANIM_TAG = 12;
GhostSelectedAnim::GhostSelectedAnim()
{
	init();
}

GhostSelectedAnim::~GhostSelectedAnim()
{

}

GhostSelectedAnim * GhostSelectedAnim::node()
{
	static GhostSelectedAnim ret;
	return &ret;
}

void GhostSelectedAnim::show()
{
	hide();
	CCSprite *selAnim = EffectSprite::create(Effect::effect_sel_ghost);
	if (selAnim)
	{
		addChild(selAnim, 0, SEL_ANIM_TAG);
	}
	_setZOrder(-1);
	setVisible(true);
}

void GhostSelectedAnim::hide()
{
	setVisible(false);
	removeAllChildren();
	removeFromParent();
}
