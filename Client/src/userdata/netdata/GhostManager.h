#ifndef __GHOST_MANAGER_H__
#define __GHOST_MANAGER_H__


#include "cocos2d.h"
#include "pthread.h"
#include "event/IEventListener.h"

using namespace cocos2d;

struct MapNode
{
	std::string name;
	int			parent;
	int         id;
};

class Ghost;
class AliveGhost;
class HeroAvatar;
class IGhostVisitor;
class GhostManager : public IEventListener
{
public:
	GhostManager();
	~GhostManager();

	//update the Zorder of the all the ghost in the ghost list
	//implement the forward and backward shelter relation
	void		sortAllChildren();
	
	//add the ghost object to the ghost list
	void		addGhost(Ghost* ghost);
	
	//get a child by id from the ghost list
	//sequentially search the child,maybe be repalced with a map::find() 
	Ghost*	getGhostById(int id);
	Ghost*	getGhostBySid(int sid);
	std::vector<Ghost*> &getGhosts() { return m_pGhosts; }
	Ghost*	getGhostAtPosition(int tx, int ty);
	Ghost*	getAnyGhostAtPosition(int tx, int ty);
	Ghost*	getTypeGhostAtPosition(int type, int tx, int ty );
	HeroAvatar *getPlayerByPID(int pid);

	//when receive an ghost id from the server,
	//remove it from the Ghostlist 
	void		removeGhost(int id);
	void		removeGhost(Ghost* pGhost);
	void		ghostManagerUpdate(float dt);

	//handle the touches from the window
	//if it is in the same tile as some ghost we should deal with it here
	//return true if it hits a ghost
	bool handleTouches(const CCPoint &touchPos);
	bool touchAnyGhost(const CCPoint &touchPos);
	void		addParent(CCLayer* pa);
	unsigned int pickupSomething(int tx, int ty);
	void		release();
	bool		isExist(Ghost* pGhost);
	
	bool		isGhostNearToMainRole(Ghost* pGhostA, Ghost* pGhostB);
	Ghost*		getNearestEnemy();
	AliveGhost*	getNearestAttackPlayer();
	AliveGhost*	getNearestAttackMonster();

	void        gotoGhostPos(int Ghostid,std::string tb,int type=0);
	int         getGhostAtMapID(int Ghostid,std::string tb);
	void		gotoMap( int Mapid,int type);
	void		gotoMapKillMonster( int Mapid,int type);

	void forEach(IGhostVisitor &visitor);

	void         gotoFindMonster(int Ghostid);
	int         gotoFindNPC(std::string str);
	int			 getNPCIDWithMapid(std::string str,int mapid);
	int			 getMapWaySize(int MapID);
	int			 findNearMapID(int MonsterSID);
	int			 findNearMapIDAboutNPC(std::string str);
	CCPoint		 findNearPos(int MonsterSID,int MapID);

	int          getGhostNearRoleDis(Ghost* pGhost);

	bool isTargetFriendly(AliveGhost *ghost);
	bool ghostVisible(Ghost *ghost);

private:
	void refreshNPCQuestMark();
	void updateNearGhost();

	void refreshGhostVisible(Ghost *ghost);

	void onCPEvent(const std::string &eventName);

public:
	CCLayer* m_parent;
	typedef std::vector<Ghost*> GhostList;
	GhostList m_pGhosts;
	GhostList m_pAloneGhost;

	Ghost*	m_pNearItem;
	Ghost*  m_pNearMoney;
	Ghost*  m_pNearDrug;
	Ghost*	m_pNearMonster;
	Ghost* mNearPlayer;
};


#endif // __GHOST_MANAGER_H__