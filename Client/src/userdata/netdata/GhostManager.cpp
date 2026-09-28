#include "GhostManager.h"
#include "Ghost.h"
#include "AliveGhost.h"
#include "IGhostVisitor.h"
#include "ItemGhost.h"
#include "MsgScene.h"
#include "QuestDefinition.h"
#include "EffectDefinition.h"
#include "TaskModule.h"
#include "UserDataModule.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/TaskData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/NPCFunctionData.h"
#include "userdata/mapdata/PixesMap.h"
#include "userdata/luadata/LuaData.h"

#include "event/EventProtocol.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/functionPanel/BoothPanel.h"

#include "network/HandleMessage.h"
#include "userdata/netdata/AutoAttack.h"
#include "SceneDefinition.h"


#define NPC_QUEST_MARK_TAG 17


static void removeNPCQuestMark( AliveGhost *npc )
{
	CCSprite *bodySprite = npc->getBodySprite();
	if (bodySprite)
	{
		CCNode *mark = bodySprite->getChildByTag(NPC_QUEST_MARK_TAG);
		if (mark)
		{
			mark->removeFromParent();
		}
	}
}

static void checkNPCQuestMark( AliveGhost *npc, const IDVector &taskVect )
{
	int srcNPC = 0;
	int tgtNPC = 0;
	const int npcID = npc->mStaticID;
	for (int i = 0; i < (int)taskVect.size(); i++)
	{
		const int qid = taskVect[i];
		srcNPC = 0;
		tgtNPC = 0;
		StaticData::getQuestSrcNPC(qid, srcNPC);
		StaticData::getQuestTgtNPC(qid, tgtNPC);
		CCSprite *bodySprite = npc->getBodySprite();
		if (bodySprite)
		{
			CCNode *mark = NULL;
			const int questState = TaskData::getTaskState(qid);
			if (npcID == srcNPC &&
				questState == Quest::state_Available)
			{
				mark = LayoutData::getSprite(CPModuleName::TASK, "questAvailable");
			}
			else if (npcID == tgtNPC)
			{
				if (questState == Quest::state_Finished)
				{
					mark = LayoutData::getSprite(CPModuleName::TASK, "questDone");
				}
				else if (questState == Quest::state_NotFinished)
				{
					mark = LayoutData::getSprite(CPModuleName::TASK, "questDoing");
				}
			}

			if (mark)
			{
				removeNPCQuestMark(npc);
				bodySprite->addChild(mark, 0, NPC_QUEST_MARK_TAG);

				mark->runAction(CCRepeatForever::create(CCSequence::create(
					CCMoveBy::create(0.7f, ccp(0, 10)),
					CCMoveBy::create(0.7f, ccp(0, -10)),
					NULL)));
			}
		}
	}
}

static void checkNPCQuestMark( Ghost *npcGhost )
{
	AliveGhost *npc = dynamic_cast<AliveGhost *>(npcGhost);
	if (!npc)
	{
		return;
	}

	removeNPCQuestMark(npc);
	IDVector taskVect = TaskData::getAccessTasks();
	checkNPCQuestMark(npc, taskVect);
	taskVect = TaskData::getCurrentTasks();
	checkNPCQuestMark(npc, taskVect);
}

//////////////GhostManager///////////////////////////////////////////
GhostManager::GhostManager()
: m_parent(NULL)
,m_pNearItem(NULL)
,m_pNearMoney(NULL)
,m_pNearDrug(NULL)
,m_pNearMonster(NULL)
,mNearPlayer(NULL)
{
	m_pGhosts.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

GhostManager::~GhostManager()
{
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if (m_pGhosts[i] != GameData::s_user->m_pMainRole)
			m_pGhosts[i]->release();
		else
			GameData::s_user->m_pMainRole->releaseRole();
	}
	m_pGhosts.clear();
	m_pAloneGhost.clear();
}

void GhostManager::addGhost( Ghost* pGhost)
{
	if(pGhost)
	{
		//if the parent exists, add to the m_pGhosts
		//else add to the m_pAloneGhost for temporary storage
		if (m_parent)
		{
			for(size_t i=0; i<m_pGhosts.size(); i++)
			{
				if (m_pGhosts[i] && m_pGhosts[i]->mID > 0 && m_pGhosts[i]->mID == pGhost->mID)
				{
					if(m_pGhosts[i] != pGhost)
					{
						delete pGhost;
					}
					return;
				}
			}
			
			m_pGhosts.push_back(pGhost);
			
			//here we init the graphical relevant part of a ghost
			pGhost->init();
			pGhost->attach(m_parent);
		}
		else
		{
			m_pAloneGhost.push_back(pGhost);
		}

		//
		if (pGhost->mType == GHOST_TYPE_NPC)
		{
			checkNPCQuestMark(pGhost);
		}
	}
}

void GhostManager::addParent(CCLayer* pa)
{
	m_parent = pa;
	if (m_parent)
	{
		//add the previous stored ghosts to the ghost list and add them to the parent layer to show them
		for(size_t i=0; i<m_pAloneGhost.size(); i++)
		{
			if(m_pAloneGhost[i])
			{
				addGhost(m_pAloneGhost[i]);
			}
		}
		m_pAloneGhost.clear();
	}
}

Ghost* GhostManager::getGhostById( int id )
{
	//sequentially search
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if(m_pGhosts[i] && m_pGhosts[i]->mID == id)
		{
			return m_pGhosts[i];
		}
	}
	for (size_t i=0; i<m_pAloneGhost.size(); i++)
	{
		if (m_pAloneGhost[i] && m_pAloneGhost[i]->mID == id)
		{
			return m_pAloneGhost[i];
		}
	}
	
	return NULL;
}


Ghost* GhostManager::getGhostBySid( int sid )
{
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if(m_pGhosts[i] && m_pGhosts[i]->mStaticID == sid)
		{
			return m_pGhosts[i];
		}
	}
	for (size_t i=0; i<m_pAloneGhost.size(); i++)
	{
		if (m_pAloneGhost[i] && m_pAloneGhost[i]->mID == sid)
		{
			return m_pAloneGhost[i];
		}
	}

	return NULL;
}

HeroAvatar * GhostManager::getPlayerByPID( int pid )
{
	for(size_t i = 0; i < m_pGhosts.size(); i++)
	{
		if (m_pGhosts[i]
			&& m_pGhosts[i]->mType == GHOST_TYPE_PLAYER
			&& m_pGhosts[i]->mStaticID == pid)
		{
			return dynamic_cast<HeroAvatar *>(m_pGhosts[i]);
		}
	}
	return NULL;
}

void GhostManager::removeGhost( int id )
{
	//sequentially search
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if(m_pGhosts[i] && m_pGhosts[i]->mID == id)
		{
			Ghost* gh = m_pGhosts[i];
			m_pGhosts.erase(m_pGhosts.begin()+i);
			gh->detach(m_parent);
			GameRole* myRole = GameData::getMyRole();
			if (myRole) myRole->someoneNeedOut(gh);
			gh->release();
			break;
		}
	}

	//
	for (size_t i=0; i<m_pAloneGhost.size(); i++)
	{
		if(m_pAloneGhost[i] && m_pAloneGhost[i]->mID == id)
		{
			Ghost* gh = m_pAloneGhost[i];
			m_pAloneGhost.erase(m_pAloneGhost.begin()+i);
			gh->detach(m_parent);
			gh->release();
			break;
		}
	}
}

void GhostManager::removeGhost(Ghost* pGhost)
{
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if(pGhost == m_pGhosts[i])
		{
			m_pGhosts[i]->detach(m_parent);
			m_pGhosts.erase(m_pGhosts.begin()+i);
			GameRole* myRole = GameData::getMyRole();
			if (myRole) myRole->someoneNeedOut(pGhost);
			pGhost->release();
			break;
		}
	}

	//
	for (size_t i=0; i<m_pAloneGhost.size(); i++)
	{
		if(pGhost == m_pAloneGhost[i])
		{
			Ghost* gh = m_pAloneGhost[i];
			m_pAloneGhost.erase(m_pAloneGhost.begin()+i);
			gh->detach(m_parent);
			gh->release();
			break;
		}
	}
}

void GhostManager::sortAllChildren()
{
	if(!m_parent)
	{
		CCLog("GhostManager::sortAllChildren, the m_parent is null now!~");
		//return;
	}

	//set the zorder of all the ghosts by their Y position
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if(m_pGhosts[i])
		{
			const int type = m_pGhosts[i]->mType;
			if (type != GHOST_TYPE_MAP_ITEM
				&& type != GHOST_TYPE_SKILL
				&& type != GHOST_TYPE_COLLECTION)
			{
				m_pGhosts[i]->setGhostZOrder(m_pGhosts[i]->getMapPosition().y);
			}
		}
		else
		{
			CCLog("NULL Ghost has not been cleaned from the manager!");
		}
	}
}

void GhostManager::ghostManagerUpdate( float dt )
{
	for(size_t i = 0; i < m_pGhosts.size(); i++)
	{
		Ghost *ghost = m_pGhosts[i];
		if (ghost)
		{
			ghost->update(dt);
			refreshGhostVisible(ghost);
		}
	}
	sortAllChildren();
}

bool GhostManager::handleTouches( const CCPoint &touchPos )
{
	typedef std::map<int, Ghost *> GhostMap;
	GhostMap touchedGhost;
	for(int i = 0; i < (int)m_pGhosts.size(); i++)
	{
		Ghost *ghost = m_pGhosts[i];
		if(ghost
			&& ghostVisible(ghost)
			&& ghost->isSelected(touchPos))
		{
			if (!touchedGhost[ghost->mType] ||
				touchedGhost[ghost->mType]->getZOrder() < ghost->getZOrder())
			{
				touchedGhost[ghost->mType] = ghost;
			}
		}
	}

	if (touchedGhost.empty())
	{
		return false;
	}

	// map item
	GhostMap::iterator itEnd = touchedGhost.end();
	GhostMap::iterator it = touchedGhost.find(GHOST_TYPE_MAP_ITEM);
	if (it != itEnd)
	{
		Ghost *ghost = it->second;
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->startAutoMoveTo(ghost);
		return true;
	}

	// collection
	it = touchedGhost.find(GHOST_TYPE_COLLECTION);
	if (it != itEnd)
	{
		Ghost *ghost = it->second;
		if (ghost)
		{
			Game::getGameUI()->showBoothPanel(ghost->mID, Booth_Buy,1);
		}
		return true;
	}

	// npc
	it = touchedGhost.find(GHOST_TYPE_NPC);
	if (it != itEnd)
	{
		Ghost *ghost = it->second;
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->startAutoMoveTo(ghost);
		return true;
	}

	// plant
	it = touchedGhost.find(GHOST_TYPE_PLANT);
	if (it != itEnd)
	{
		AliveGhost *ghost = dynamic_cast<AliveGhost *>(it->second);
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->changeTheAim(ghost);
		return true;
	}

	// monster
	it = touchedGhost.find(GHOST_TYPE_MONSTER);
	if (it != itEnd)
	{
		AliveGhost *ghost = dynamic_cast<AliveGhost *>(it->second);
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->changeTheAim(ghost);
		return true;
	}

	// player
	it = touchedGhost.find(GHOST_TYPE_PLAYER);
	if (it != itEnd)
	{
		AliveGhost *player = dynamic_cast<AliveGhost *>(it->second);
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->changeToPlayerAnim(player);
		return true;
	}

	// other
	it = touchedGhost.begin();
	AliveGhost *ghost = dynamic_cast<AliveGhost *>(it->second);
	if (ghost)
	{
		GameRole* myRole = GameData::getMyRole();
		if (myRole) myRole->changeTheAim(ghost);
		return true;
	}

	return false;
}

bool GhostManager::touchAnyGhost( const CCPoint &touchPos )
{
	for(int i = 0; i < (int)m_pGhosts.size(); i++)
	{
		Ghost *ghost = m_pGhosts[i];
		if(ghost
			&& ghostVisible(ghost)
			&& ghost->isSelected(touchPos))
		{
			return true;
		}
	}
	return false;
}

unsigned int GhostManager::pickupSomething( int tx, int ty )
{	
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if (m_pGhosts[i]->mType != GHOST_TYPE_MAP_ITEM)
			continue;
		if (m_pGhosts[i]->mTx == tx && m_pGhosts[i]->mTy == ty)
		{
			return m_pGhosts[i]->mID;
		}
	}
	
	return -1;
}

void GhostManager::release()
{
	// release normal ghost
	GhostList otherGhosts;
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if (m_pGhosts[i]->mType != GHOST_TYPE_SKILL_BIND)
		{
			if (m_pGhosts[i]->mType != GHOST_TYPE_PLAYER
				&& m_pGhosts[i]->mType != GHOST_TYPE_THIS)
			{
				m_pGhosts[i]->detach(m_parent);
				m_pGhosts[i]->release();
			}
			else
			{
				otherGhosts.push_back(m_pGhosts[i]);
			}
		}
	}

	// release other player ghost
	for(size_t i=0; i < otherGhosts.size(); i++)
	{
		otherGhosts[i]->detach(m_parent);
		if (otherGhosts[i]->mType != GHOST_TYPE_THIS)
		{
			otherGhosts[i]->release();
		}
	}

	// release my hero
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->releaseRole();

	{
		GhostList empty;
		m_pGhosts.swap(empty);
	}
	{
		GhostList empty;
		m_pAloneGhost.swap(empty);
	}

	m_parent = NULL; 
}

Ghost* GhostManager::getGhostAtPosition( int tx, int ty )
{
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		Ghost* aghost = m_pGhosts[i];
		if(aghost)
		{
			if(aghost->mType != GHOST_TYPE_MONSTER &&
				aghost->mTx==tx &&
				aghost->mTy==ty)
			{
				
				return aghost;
			}
		}
	}
	
	return NULL;
}

bool GhostManager::isExist( Ghost* pGhost )
{
	if(!pGhost)
	{
		return false;
	}
	
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		if(pGhost == m_pGhosts[i])
		{
			return true;
		}
	}
	
	return false;
}

void GhostManager::updateNearGhost()
{
	m_pNearItem = NULL;
	m_pNearMonster = NULL;
	m_pNearDrug = NULL;
	m_pNearMoney = NULL;
	mNearPlayer = NULL;
	int nearest=0;
	GameRole *myRole = GameData::getMyRole();
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		Ghost* aghost = m_pGhosts[i];
		if(aghost)
		{
			if(!myRole->isGhostInAIRange(aghost))
			{
			 	continue;
			}
			if(aghost->mType == GHOST_TYPE_MAP_ITEM)
			{
				ItemGhost* pItemGhost = dynamic_cast<ItemGhost*>(aghost);
				if(pItemGhost)
				{
					int typeID = pItemGhost->mStaticID;
					if(typeID == 2)//money
					{
						if(!m_pNearMoney || isGhostNearToMainRole(pItemGhost,m_pNearMoney))
						{
							m_pNearMoney = pItemGhost;
						}
					}
					else if(typeID/1000 == 39)
					{
						if(!m_pNearDrug || isGhostNearToMainRole(pItemGhost,m_pNearDrug))
						{
							m_pNearDrug = pItemGhost;
						}
					}
					else
					{
						if(!m_pNearItem || isGhostNearToMainRole(pItemGhost,m_pNearItem))
						{
							m_pNearItem = pItemGhost;
						}
					}
				}
			}
			else if(aghost->mType == GHOST_TYPE_MONSTER || aghost->mType == GHOST_TYPE_PLANT)
			{
				AliveGhost* pAliveGhost = dynamic_cast<AliveGhost*>(aghost);
				if (!pAliveGhost ||
					pAliveGhost->isDead() ||
					isTargetFriendly(pAliveGhost))
				{
					continue;
				}

				// Ìø¹ýÊØÎÀNPC
				if (aghost->mType == GHOST_TYPE_MONSTER)
				{
					int selFlag = 0;
					StaticData::getMonsterSelFlag(aghost->mStaticID, selFlag);
					if (selFlag != 0)
					{
						continue;
					}
				}

				if (myRole->isQuestDoing())
				{
					if(!NPCFunctionData::checkIsQuestMonster(pAliveGhost->getDress(AVATAR_TYPE_CLOTH)))
					{
						continue;
					}
				}

				if(!m_pNearMonster || isGhostNearToMainRole(aghost,m_pNearMonster))
				{
					const int dis=getGhostNearRoleDis(aghost);
					if (nearest==0)
					{
						m_pNearMonster = aghost;
						nearest=dis;
					}
					else if(nearest>dis)
					{
						m_pNearMonster = aghost;
						nearest=dis;
					}
				}
			}
			else if (aghost->mType == GHOST_TYPE_PLAYER)
			{
				AliveGhost* pAliveGhost = dynamic_cast<AliveGhost*>(aghost);
				if (!pAliveGhost ||
					pAliveGhost->isDead())
				{
					continue;
				}

				if (myRole->isQuestDoing())
				{
					if(!NPCFunctionData::checkIsQuestMonster(pAliveGhost->getDress(AVATAR_TYPE_CLOTH)))
					{
						continue;
					}
				}

				if(!mNearPlayer || isGhostNearToMainRole(aghost, mNearPlayer))
				{
					if (!isTargetFriendly(pAliveGhost))
					{
						const int dis=getGhostNearRoleDis(aghost);
						if (nearest == 0 ||
							nearest > dis)
						{
							mNearPlayer = aghost;
							nearest=dis;
						}
					}
				}
			}
		}
	}
}

bool GhostManager::isGhostNearToMainRole( Ghost* pGhostA, Ghost* pGhostB )
{
	if(!pGhostA)
	{
		return false;
	}
	if(!pGhostB)
	{
		return true;
	}
	return ccpDistanceSQ(pGhostA->getSpritePosition(),GameData::s_user->m_pMainRole->getSpritePosition())
		<= ccpDistanceSQ(pGhostB->getSpritePosition(),GameData::s_user->m_pMainRole->getSpritePosition());
}

Ghost* GhostManager::getNearestEnemy()
{
	updateNearGhost();
	if (isGhostNearToMainRole(mNearPlayer, m_pNearMonster) && !AutoAttack::checkAutoAttack())
	{
		return mNearPlayer;
	}
	return m_pNearMonster;
}

AliveGhost* GhostManager::getNearestAttackPlayer()
{
	AliveGhost* best = NULL;
	for(size_t i = 0; i < m_pGhosts.size(); i++)
	{
		Ghost* ghost = m_pGhosts[i];
		if (!ghost || ghost->mType != GHOST_TYPE_PLAYER)
		{
			continue;
		}
		AliveGhost* player = dynamic_cast<AliveGhost*>(ghost);
		if (!player || player->isDead() || isTargetFriendly(player))
		{
			continue;
		}
		if (!best || isGhostNearToMainRole(player, best))
		{
			best = player;
		}
	}
	return best;
}

AliveGhost* GhostManager::getNearestAttackMonster()
{
	AliveGhost* best = NULL;
	for(size_t i = 0; i < m_pGhosts.size(); i++)
	{
		Ghost* ghost = m_pGhosts[i];
		if (!ghost || ghost->mType != GHOST_TYPE_MONSTER)
		{
			continue;
		}
		AliveGhost* monster = dynamic_cast<AliveGhost*>(ghost);
		if (!monster || monster->isDead())
		{
			continue;
		}
		int selFlag = 0;
		StaticData::getMonsterSelFlag(monster->mStaticID, selFlag);
		if (selFlag != 0)
		{
			continue;
		}
		if (!best || isGhostNearToMainRole(monster, best))
		{
			best = monster;
		}
	}
	return best;
}

void GhostManager::gotoMap( int Mapid,int type)
{
	int x=0,y=0; 	
	LuaData::getProp("gdMaps",Mapid,"defaultx",x);
	LuaData::getProp("gdMaps",Mapid,"defaulty",y);
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->startAutoMoveToCrossMap(Mapid,x,y,type);
}  

void GhostManager::gotoGhostPos( int Ghostid,std::string tb ,int type)
{
	int x=0,y=0; 	
	int mapid=0;
	mapid=getGhostAtMapID(Ghostid,tb);
	LuaData::getProp_Ghostpos("gdMaps",mapid,Ghostid,tb,y,x);
	mapid=getGhostAtMapID(Ghostid,tb);
	if(LuaData::checkMonsterInMapExist(LuaData::MAP,GameData::s_user->mMap.mID,tb,Ghostid) && type==GHOST_TYPE_MONSTER)
	{
		mapid=GameData::s_user->mMap.mID;
		LuaData::getProp_Ghostpos("gdMaps",mapid,Ghostid,tb,y,x);
	}
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->startAutoMoveToCrossMap(mapid,x,y,type);
}  

int GhostManager::getGhostAtMapID( int Ghostid ,std::string tb )
{
	int mapID=0;	
	LuaData::getProp_GhostMapID(LuaData::MAP,Ghostid,tb,mapID); 
	return mapID;
}

Ghost* GhostManager::getAnyGhostAtPosition( int tx, int ty )
{
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		Ghost* aghost = m_pGhosts[i];
		if(aghost)
		{
			if(aghost->mTx==tx && aghost->mTy==ty)
			{
				return aghost;
			}
		}
	}
	
	return NULL;
}

Ghost* GhostManager::getTypeGhostAtPosition(int type, int tx, int ty )
{
	for(size_t i=0; i<m_pGhosts.size(); i++)
	{
		Ghost* aghost = m_pGhosts[i];
		if(aghost)
		{
			if(aghost->mTx==tx && aghost->mTy==ty && aghost->mType == type)
			{
				return aghost;
			}
		}
	}

	return NULL;
}

void GhostManager::refreshNPCQuestMark()
{
	for(int i = 0; i < (int)m_pGhosts.size(); i++)
	{
		Ghost *ghost = m_pGhosts[i];
		if (ghost &&
			ghost->mType == GHOST_TYPE_NPC)
		{
			checkNPCQuestMark(ghost);
		}
	}
}

void GhostManager::forEach( IGhostVisitor &visitor )
{
	for (int i = 0; i < (int)m_pGhosts.size(); i++)
	{
		visitor.visit(m_pGhosts[i]);
	}
}

void GhostManager::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageQuestUpdateList" ||
			source == "HandleMessageQuestUpdate")
		{
			refreshNPCQuestMark();
		}
	}
}

int GhostManager::findNearMapID( int MonsterSID )
{
	int MapID=0;
	int CntSize=0;
	LuaData::getProp_size("gdMonsterWithMap",MonsterSID,"",CntSize); 
	std::map<int ,int> MapMapID;
	for (int i=1;i<=CntSize;i++)
	{
		int id=0;
		LuaData::getProp("gdMonsterWithMap",MonsterSID,i,"id",id);
		MapMapID[id]=id;
	}
	int NearestPath=0;
	for (std::map<int ,int>::iterator it=MapMapID.begin();it!=MapMapID.end();it++)
	{
		int id=it->first;
		if (MapID!=0)
		{
			int size=getMapWaySize(id);
			if (size<NearestPath)
			{
				NearestPath=size;
				MapID=id;
			}
		}
		else
		{
			MapID=id;
			NearestPath=getMapWaySize(id);
		}
	}
	return MapID;
}

int GhostManager::findNearMapIDAboutNPC( std::string str )
{
	int MapID=0;
	int CntSize=4;
	int testMapid[4] = {1,2,3,128};
	//LuaData::getProp_size("gdMonsterWithMap",MonsterSID,"",CntSize); 
	std::map<int ,int> MapMapID;
	for (int i=1;i<=CntSize;i++)
	{
		int id=testMapid[i-1];
		//LuaData::getProp("gdMonsterWithMap",MonsterSID,i,"id",id);
		MapMapID[id]=id;
	}
	int NearestPath=0;
	for (std::map<int ,int>::iterator it=MapMapID.begin();it!=MapMapID.end();it++)
	{
		int id=it->first;
		if (MapID!=0)
		{
			int size=getMapWaySize(id);
			if (size<NearestPath)
			{
				NearestPath=size;
				MapID=id;
			}
		}
		else
		{
			MapID=id;
			NearestPath=getMapWaySize(id);
		}
	}
	return MapID;
}

cocos2d::CCPoint GhostManager::findNearPos( int MonsterSID,int MapID )
{
	CCPoint Pos=CCPointZero;
	GameRole* myRole = GameData::getMyRole();
	if (myRole)
	{
		int num=myRole->mTx*myRole->mTx+myRole->mTy*myRole->mTy;
		int x=0;
		int y=0;
		if (MapID!=GameData::s_user->mMap.mID)
		{
			int x_1=0;
			int y_1=0;
			LuaData::getProp("gdMaps",MapID,"defaultx",x_1);
			LuaData::getProp("gdMaps",MapID,"defaulty",y_1);
			num=x_1*x_1+y_1*y_1;
		} 
		LuaData::getProp_NearestMonsterPos("gdMonsterWithMap",MonsterSID,MapID,num,x,y); 
		Pos.x=x;
		Pos.y=y;
		return Pos;
	}
}

int GhostManager::getMapWaySize( int MapID )
{
	int WaySize=0;
	std::stack<int> crossMapPath;
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
		if(cur.id == MapID)
		{
			//the end
			while(cur.parent != -1)
			{
				crossMapPath.push(cur.id);
				cur = closeList[cur.parent];
			}
			WaySize=crossMapPath.size();
			return WaySize;
		}
		int p = closeList.size()-1;
		MapConnVect vec = GameData::s_map->mMiniMapConn[cur.id];
		for(MapConnVect::iterator it=vec.begin(); it!=vec.end(); it++)
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
	return WaySize;
}

void GhostManager::gotoFindMonster( int Ghostid )
{
	int mapid=findNearMapID(Ghostid);
	CCPoint Pos=findNearPos(Ghostid,mapid); 	
	int x=Pos.x;
	int y=Pos.y;
	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->startAutoMoveToCrossMap(mapid,x,y,GHOST_TYPE_MONSTER); 
}

int GhostManager::getNPCIDWithMapid( std::string str,int mapid )
{
	int npcid = 166;
	if (mapid==1)
	{
		npcid = 100;
	}
	else if (mapid==2)
	{
		npcid = 116;
	}
	else if (mapid==3)
	{
		npcid = 166;
	}
	else if (mapid==128)
	{
		npcid = 210;
	}
	return npcid;
}

int GhostManager::gotoFindNPC( std::string str )
{
	int mapid=findNearMapIDAboutNPC(str);
	int npcid = getNPCIDWithMapid(str,mapid);
	gotoGhostPos(npcid,"npcs",GHOST_TYPE_NPC);
	return npcid;
}

int GhostManager::getGhostNearRoleDis( Ghost* pGhost )
{
	int mx=GameData::s_user->m_pMainRole->mTx;
	int my=GameData::s_user->m_pMainRole->mTy;
	int gx=pGhost->mTx;
	int gy=pGhost->mTy;
	return (mx-gx)*(mx-gx)+(my-gy)*(my-gy);
}

bool GhostManager::isTargetFriendly( AliveGhost *ghost )
{
	if (ghost)
	{
		const int type = ghost->mType;
		if (type == GHOST_TYPE_PLAYER ||
			type == GHOST_TYPE_PET ||
			type == GHOST_TYPE_SLAVE)
		{
			int pid = 0;
			std::string name;
			ghost->getOwnerInfo(pid, name);
			if (pid == HeroData::getPID())
			{
				return true;
			}
			else
			{
				const int pkMode = HeroData::getProp(Entity::attr_pkmode);
				switch (pkMode)
				{
				case Entity::pk_Peace:
					{
						return true;
					}
				case Entity::pk_Team:
					{
						const int teamID = ghost->getExData(Entity::attr_team_id);
						if (teamID > 0
							&& teamID == HeroData::getProp(Entity::attr_team_id))
						{
							return true;
						}
						break;
					}
				case Entity::pk_Guild:
					{
						const int guildID = ghost->getExData(Entity::attr_guild_id);
						if (guildID > 0
							&& guildID == HeroData::getProp(Entity::attr_guild_id))
						{
							return true;
						}
						break;
					}
				case Entity::pk_Red:
					{
						const int pkState = ghost->getExData(Entity::attr_pkstate);
						if (pkState != Entity::pks_red &&
							pkState != Entity::pks_gray)
						{
							return true;
						}
						break;
					}
				case Entity::pk_Faction:
					{
						const int factionID = ghost->getExData(Entity::attr_faction_id);
						if (factionID > 0
							&& factionID == HeroData::getProp(Entity::attr_faction_id))
						{
							return true;
						}
						break;
					}
				}
			}
		}
		else if (type == GHOST_TYPE_MONSTER)
		{
			const int owner = ghost->getExData(Entity::attr_owner_id);
			if (owner == HeroData::getPID())
			{
				return true;
			}
			else
			{
				const int pkMode = HeroData::getProp(Entity::attr_pkmode);
				if (pkMode == Entity::pk_Faction)
				{
					const int factionID = ghost->getExData(Entity::attr_faction_id);
					if (factionID != 0 &&
						factionID == HeroData::getProp(Entity::attr_faction_id))
					{
						return true;
					}
				}
			}
		}
		else if (type == GHOST_TYPE_THIS)
		{
			return true;
		}
	}
	return false;
}

void GhostManager::gotoMapKillMonster( int Mapid,int type )
{
	int x=0,y=0; 	
	int monsterSize = 0;
	LuaData::getProp_size(LuaData::MAP,Mapid,"monsters",monsterSize);
	int mapType=0;
	StaticData::getMapType(GameData::s_user->mMap.mID,mapType);

	if (monsterSize == 0 && mapType==Scene::stSceneNormal)
	{
		CPEventHelper::uiNotify("","",Error::Not_Has_Monster);
		return;
	}			

	if (mapType==Scene::stSceneNormal)
	{
		srand((int)time(0)); 
		int randomnum = 1 + rand()%monsterSize;
		LuaData::getProp(LuaData::MAP,Mapid,"monsters",randomnum,"posx","posy",y,x);
	}
	else
	{
		LuaData::getProp("gdMaps",Mapid,"defaultx",x);
		LuaData::getProp("gdMaps",Mapid,"defaulty",y);
	}

	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->startAutoMoveToCrossMap(Mapid,x,y,type);
}

void GhostManager::refreshGhostVisible( Ghost *ghost )
{
	AliveGhost *aliveGhost = dynamic_cast<AliveGhost *>(ghost);
	if (!aliveGhost)
	{
		return;
	}

	int pid = 0;
	std::string name;
	aliveGhost->getOwnerInfo(pid, name);
	if (pid == HeroData::getPID())
	{
		return;
	}

	CCSprite *body = aliveGhost->getBodySprite();
	if (body)
	{
		const int type = aliveGhost->mType;
		if (type == GHOST_TYPE_PET)
		{
			body->setVisible(UserData::getIntData(HeroData::getPID(), CPUserData::HIDE_PET) == 0);
		}
		else if (type == GHOST_TYPE_SLAVE)
		{
			body->setVisible(UserData::getIntData(HeroData::getPID(), CPUserData::HIDE_DOG) == 0);
		}
		else if (type == GHOST_TYPE_PLAYER)
		{
			if (aliveGhost->hasEffectBuff(Effect::effect_offline))
			{
				body->setVisible(false);
			}
			else
			{
				if (UserData::getIntData(HeroData::getPID(), CPUserData::SHOW_MY_GUILD_PLAYER) != 0)
				{
					if (HeroData::getProp(Entity::attr_guild_id) > 0
						&& aliveGhost->getExData(Entity::attr_guild_id) == HeroData::getProp(Entity::attr_guild_id))
					{
						body->setVisible(true);
					}
					body->setVisible(false);
				}
				else if (UserData::getIntData(HeroData::getPID(), CPUserData::SHOW_MY_SOCIAL_PLAYER) != 0)
				{
					if (HeroData::getProp(Entity::attr_team_id) > 0
						&& aliveGhost->getExData(Entity::attr_team_id) == HeroData::getProp(Entity::attr_team_id))
					{
						body->setVisible(true);
					}
					body->setVisible(false);
				}
				else
				{
					body->setVisible(true);
				}
			}
		}
	}
}

bool GhostManager::ghostVisible( Ghost *ghost )
{
	if (ghost)
	{
		CCSprite *body = ghost->getBodySprite();
		if (body)
		{
			if (body->isVisible() && body->getOpacity() > 0)
			{
				return true;
			}
		}
	}
	return false;
}

