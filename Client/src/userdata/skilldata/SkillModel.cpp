#include "SkillModel.h"
#include "SkillEffect.h"
#include "MsgScene.h"

#include "network/HandleMessage.h"

#include "ext/CCFlashAnimation.h"

#include "event/CPEventHelper.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"


cSkillCastModel::~cSkillCastModel()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
	if (m_ghost)
	{
		if (GameData::getGhostManager()) GameData::getGhostManager()->removeGhost(m_ghost);
		m_ghost = NULL;
	}
	m_pHero = NULL;
}

void cSkillCastModel::castSkill(int x/* =0 */, int y/* =0 */, int id/* =-1 */)
{
	m_destx = x;
	m_desty = y;
	m_aimID = id;

	if (m_cast)
	{
		CCSprite* pSprite = CCSprite::create();
		m_pHero->attachMe(pSprite);
		pSprite->_setZOrder(4);

		pSprite->runAction(CCSequence::create(
			m_cast->getAnimate(0)
			,CCActionInstantRemoveFromParent::create()
			,CCCallFunc::create(this, callfunc_selector(cSkillCastModel::castOut))
			,NULL
			));
	}
	else
	{
		castOut();
	}
}

CCPoint cSkillCastModel::getOffsetPosition(float angle)
{
	CCPoint offp(0, 0);
	return offp;
}

void cSkillCastModel::castOut()
{
	//over write me
	if(GameData::s_user->m_pGhostManager->isExist(m_pHero))
	{
		m_pHero->m_skill->removeSkill(m_nType);
	}
}

void cSkillCastModel::castEnd()
{
	uiEnd();
	logicEnd();
}

void cSkillCastModel::AC()
{
	CCSprite* pSprite = CCSprite::create();
	m_ghost = new Ghost();
	m_ghost->init(pSprite);
	m_ghost->setZOrder(m_desty);
	m_ghost->mType = GHOST_TYPE_SKILL_BIND;
	pSprite->setPosition(m_pHero->getSpritePosition());
	GameData::s_user->m_pGhostManager->addGhost(m_ghost);

	m_destx = m_destx - m_pHero->getMapPosition().x;
	m_desty = m_desty - m_pHero->getMapPosition().y;

	sendMessage();

	//
	CCSequence *uiSequence = CCSequence::create(
		CCMoveBy::create(0.0f, ccp(m_destx, -m_desty)),
		CCCallFunc::create(this, callfunc_selector(cSkillCastModel::beginUpdate)),
		m_explode->getAnimate(0),
		CCCallFunc::create(this, callfunc_selector(cSkillCastModel::uiEnd)),
		NULL);
	CCSequence *logicSequence = CCSequence::create(
		CCDelayTime::create(0.3f),
		CCCallFunc::create(this, callfunc_selector(cSkillCastModel::logicEnd)),
		NULL);
	CCSpawn *action = CCSpawn::create(uiSequence, logicSequence, NULL);
	pSprite->runAction(action);
}

void cSkillCastModel::sBC()
{
	CCSpriteFrame* frame = m_Animstab->getFirstFrame();
	if(!frame)
	{
		CCLog("sBC, null frame!");
		return;	
	}

 	CCSprite* sprstab = CCSprite::createWithSpriteFrame(frame);
	sprstab->setAnchorPoint(ccp(0.5, 0.5));
 	m_ghost = new Ghost();
 	m_ghost->init(sprstab);
 	m_ghost->setZOrder(m_desty);
	m_ghost->mType = GHOST_TYPE_SKILL_BIND;
 	sprstab->setPosition(ccpAdd(m_pHero->getSpritePosition(),ccp(0,40)));
 
 	m_destx = m_destx - m_pHero->getMapPosition().x;
 	m_desty = m_desty - m_pHero->getMapPosition().y;
 	float angle = SystemData::getAngle(CCPointZero, ccp(m_destx, m_desty)) + 90;
 
 	GameData::s_user->m_pGhostManager->addGhost(m_ghost);

	sendMessage();

	//
#define STEP_1 0.1f
#define STEP_2 0.5f
	CCSequence *uiSequence = CCSequence::create(
		CCRotateTo::create(0, angle),
		CCMoveBy::create(0, ccp(STEP_1 * m_destx, -STEP_1 * m_desty)),
		CCMoveBy::create(0.3f, ccp(STEP_2 * m_destx, -STEP_2 * m_desty)),
		CCRotateTo::create(0, 0),
		NULL);
	CCSequence *logicSequence = CCSequence::create(
		CCDelayTime::create(0.3f),
		CCCallFunc::create(this, callfunc_selector(cSkillCastModel::explode)),
		CCCallFunc::create(this, callfunc_selector(cSkillCastModel::castEnd)),
		NULL);
	CCAction *action = CCSpawn::create(uiSequence, logicSequence, NULL);
	sprstab->runAction(action);
}

void cSkillCastModel::sendMessage()
{
	AliveGhost *myRole = GameData::getMyRole();
	if (m_pHero == myRole)
	{
		MsgPlayerUseSkillonEntityRequest* req = new MsgPlayerUseSkillonEntityRequest;
		req->skillid = m_nType;
		req->eid = m_aimID;
		HandleMessage::sendMessage(req);

		//show cd
		CPEventHelper::setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_2, m_nType);
		CPEventHelper::uiNotify("UINotifyPlayerUseSkill", "", 0);
	}
}

void cSkillCastModel::explode()
{
	AliveGhost* pTarget = dynamic_cast<AliveGhost*>(GameData::s_user->m_pGhostManager->getGhostById(m_aimID));
	if(pTarget && m_explode)
	{
		pTarget->playEffect(m_explode->getAnimate(0));
	}
}

void cSkillCastModel::beginUpdate()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

void cSkillCastModel::uiEnd()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
	GameData::getGhostManager()->removeGhost(m_ghost);
	m_ghost = NULL;
}

void cSkillCastModel::logicEnd()
{
	if(GameData::getGhostManager()->isExist(m_pHero))
	{
		m_pHero->m_skill->removeSkill(m_nType);
	}
}

void cSkillCastModel::update( float dt )
{
	GhostManager *mnger = GameData::getGhostManager();
	if (mnger && mnger->m_parent && mnger->isExist(m_pHero))
	{
		if (m_ghost && (m_ghost->mType == GHOST_TYPE_SKILL_BIND) && mnger->isExist(m_ghost))
		{
			Ghost *target = mnger->getGhostById(m_aimID);
			if (target && target->getBodySprite() && mnger->isExist(target))
			{
				CCSprite *body = m_ghost->getBodySprite();
				if (body)
				{
					body->setPosition(target->getSpritePosition());
				}
			}
		}
	}
}

//////////cSkillJinShenGongJi////////////////////////////////////////////
void cSkillJinShenGongJi::castSkill(int x, int y, int id)
{
	if (m_cast)
	{
		CCSprite* pSprite = CCSprite::create();
		int dir = m_pHero->getDirection();
		int angle = 360 - SystemData::getAngleFromDir(dir);
		m_pHero->attachMe(pSprite);
		pSprite->setRotation(angle);
		if(dir==0 || dir==1 || dir==7)
		{
			pSprite->_setZOrder(-1);
		}
		else
		{
			pSprite->_setZOrder(4);
		}
		pSprite->runAction(CCSequence::create(
			m_cast->getAnimate(0)
			,CCActionInstantRemoveFromParentEx::create(pSprite)
			,CCCallFunc::create(this,callfunc_selector(cSkillJinShenGongJi::castEnd))
			,NULL
			));
	}
}

void cSkillJinShenGongJi::castEnd()
{
	if(GameData::s_user->m_pGhostManager->isExist(m_pHero))
	{
		m_pHero->m_skill->removeSkill(m_nType);
	}
}