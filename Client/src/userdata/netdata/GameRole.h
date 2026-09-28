#ifndef	___GAME_ROLE_____
#define ___GAME_ROLE_____

#include "NetCharacter.h"
#include "HeroAvatar.h"
#include "CommonType.h"
#include "MsgScene.h"
#include <stack>
#include "event/IEventListener.h"

class AstarPathfinder;
class NetItem;
struct UserItem;

class GameRole : public HeroAvatar, public NetCharacter, public IEventListener
{
public:
	GameRole();
	virtual ~GameRole();
	static GameRole* create(long time);
	virtual bool init();
	virtual void update(float dt);
	void release();

public:
	void releaseRole();

	void setNextStateCallback();
	void stopAnimation();
	bool isSelected(const CCPoint &touchPos);
	void handleMoveRes(int nstep,int movetype, int dir, int x, int y);
	void someoneNeedOut(Ghost* pgh);
	void moveOneStep();	
	bool isBlocked( int tX, int tY );
	bool checkBlockedMove(short &state, int &dir);
	void setState(short state, int dir=-1);
	void setState(short state, int dir, StateInfo* info);
	void setDirection(int dir);
	void clickSkills(int skillID);
	void changeTheAim(AliveGhost*);
	AliveGhost* getTheAim();
	void changeToPlayerAnim(AliveGhost *player);
	
	void touchScreenBegin(const CCPoint& point);
	void touchScreenMoved(const CCPoint& point);
	void touchScreenEnded();
	
	void startAutoMoveTo(int tx, int ty, int type=0 );
	void startAutoMoveTo(Ghost *pGhost);
	void startAutoMoveToCrossMap(int mapid ,int x,int y, int type);
	void checkAutoMove();

	void handleHpChange(int changeHp);
	void delayHpChange( int hp,short delay );
	void setMP(int mp);

	void abandonItem(unsigned int iid, int count);

	void updateSceenPosition();
	CCPoint& getSceenPosition();

	bool isGhostInAIRange(Ghost* pGhost);
	void easyAi();
	void setEasyAI(bool isOn);
	bool isEasyAIOn() const;

	bool isSkillLearned(int skillid, int &skillID);
	bool startCastSkill(int skillID);

	void tryToMine(const CCPoint &touchPos);
	void tryToMineByMapPos(CCPoint mappos);
	void autoToMine();
	void stopAutoMoving();

	bool isQuestDoing() const;
	void setQuestDoing(bool isDoing);
	void updateDoingQuest();
	bool checkGhostIsOwn(AliveGhost* pGhost);

	void autoAttack();
	void onSceneMonstersClean(int sceneId);

	bool checkSummonDog();

	CCPoint getTargetPosition();

private:
	void autoMoveAround();
	void walk(int dir, int newx, int newy);
	void run(int dir, int newx, int newy);
	int  getSkipTime();
	void moveCheck();
	void moveCheckTimerReset();
	void updateMoveStateByTouch();
	int  getThatWayDirection(CCPoint touchPos);
	int  getThatWayState(CCPoint touchPos);
	void turnDirection(int dir);
	bool checkPassObstacle(short &state, int &dir);
	void checkOnPortals();

	void nextPathSegment();
	bool isReached();
	CCPoint bfsFindOKPos(CCPoint nextPos, int nearDir);
	bool searchCrossMapPath();
	bool autoMoveOneStep(CCPoint targetTilePos, short& state);
	bool isReached(CCPoint target);

	void executeMouseSequence();
	void executeMoveAndAttack();
	void executeAutoSkill();
	void executeAutoMove(bool &needOneStep);
	void executeStateList();

	void showExitAutoAttackGuide();

	void pickUp(unsigned int itemid);

	int getFightSkill(int type);
	CCPoint faceFightPoint();

	bool canUseSkill(int skillEnum, int &skillID);
	void useSkillRequest(int skillID, int x, int y, uint32 id);
	void addSkillState(int skillID, int id);
	bool testManaAndCD(int skillID, bool containGCD, bool needNotify);
	bool testSkillDistance( int skillID,CCPoint tgtpoint);
	bool isInPeaceArea();
	bool isInPeaceArea(int tx, int ty);
	bool isTargetOutOfRange();
	bool isTargetOutOfRange(Ghost *ghost);
	AliveGhost *getShortRangeAttackTarget(int &direction);
	AliveGhost *getAliveEnemy(int x, int y);

	void startPickPlant(int plantID);

	// item or monster
	bool changeToNearestTarget();

	void refreshIntoPeaceArea();

	void refreshMitigate();

	void onCPEvent(const std::string &eventName);
	
	bool canPickItem(Ghost* pGhost);
public:

	int m_autoSkillType;
	bool m_bAutoMove;
	bool m_isMoveAndAttack;	
	bool m_bTranfering;
	bool m_bEasyAiKeepAttack;
	bool m_bIsInControlPanel;
	bool m_bBuyShoesTips;

	int m_iExpCount;
	int m_iMoneyCount;
	int m_iHonorCount;

	int m_iTargetSid;
	int m_iCurrentPetiid;
	int m_iTargeteid;
	int m_iTargetpid;

	UserItem* m_pStoneArray[17][5];

	bool m_bMyBooth;
	int m_iTargetMoney1;
	int m_iTargetMoney2;	
	std::string m_iTargetname;
	std::string m_sBoothTargetName;
	std::vector< UserItem* > m_pMarketItemList;
	std::vector< UserItem* > m_pTradeItemList;

private:
	int	mMoveStepRes;
	int	mMoveStep;
	long m_initTime;
	long m_moveTime;
	bool m_bEasyAi;
	bool mLastInPeaceArea;
	int	m_nAutoFightTime;
	int	m_nTargetX;
	int	m_nTargetY;
	int	m_targetMapID;
	int	m_nTargetMapX;
	int	m_nTargetMapY;
	int	m_nTargetGhostId;
	int	m_nTargetGhostType;
	bool m_bCrossAutoMove;
	short m_nLeftStep;
	bool m_isMouseSequence;
	bool m_isMousePickUp;
	bool m_bMovingAndPick;
	bool m_bQuestDoing;
	bool mMoveToTargetByButton;

	CCPoint	m_MousePoint;
	CCPoint mLastMiningPt;
	CCPoint	m_sceenPosition;

	AstarPathfinder* m_pPathFinder;
	std::stack<int>	m_crossMapPath;
	AliveGhost*	m_aimGhost;

	int m_irangex;
	int m_irangey;
};

#endif //___GAME_ROLE_____