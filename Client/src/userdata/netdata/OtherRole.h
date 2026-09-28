#ifndef	___OTHER_ROLE_____
#define ___OTHER_ROLE_____

#include "NetCharacter.h"
#include "HeroAvatar.h"
#include "CommonType.h"
#include "MsgScene.h"
#include <stack>
#include "event/IEventListener.h"

struct UserItem;

class OtherRole :public HeroAvatar,  public NetCharacter, public IEventListener
{
public:
	OtherRole();
	virtual ~OtherRole();
	static OtherRole* create();
	virtual bool init();

	void onCPEvent(const std::string &eventName);

	void UpdStoneArray();
	int	 getSuitCnt(int suitid);
public:
	int m_autoSkillType;
	bool m_bAutoMove;
	bool m_isMoveAndAttack;	
	bool m_bTranfering;
	bool m_bEasyAiKeepAttack;
	bool m_bIsInControlPanel;
	bool m_bQuestDoing;

	int mrebornitem;
	int mRebornlvl;
	int m_iExpCount;
	int m_iMoneyCount;
	int m_iHonorCount;
	int mlingliitem;//¡È¡¶

	int m_iCurrentPetiid;
	int m_iTargeteid;
	int m_iTargetpid;

	AliveGhost*	m_aimGhost;
	UserItem* m_pStoneArray[17][5];

	bool m_bMyBooth;
	int m_iTargetMoney1;
	int m_iTargetMoney2;	
	std::string m_iTargetname;
	std::string m_sBoothTargetName;
	std::vector< UserItem* > m_pMarketItemList;
	std::vector< UserItem* > m_pTradeItemList;
	std::vector< UserItem* > m_pAllItemList;
	std::map<short, UserItem* > m_pAllItemMap;

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

	CCPoint	m_MousePoint;
	CCPoint mLastMiningPt;
	CCPoint	m_sceenPosition;
};




#endif //___GAME_ROLE_____