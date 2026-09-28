#include "OtherRole.h"
#include <queue>
#include <fstream>
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
#include "scene/panel/functionPanel/CharacterPanel.h"

#include "res/AudioLoader.h"

#include "AreaChecker/AreaChecker.h"
#include "userdata/luadata/LuaData.h"

//////////OtherRole/////////////////////////////////////////////
OtherRole::OtherRole()
: mMoveStep(0)
, mrebornitem(0)
, mlingliitem(0)//¡È¡¶
, mRebornlvl(0)
, mMoveStepRes(0)
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
{

	for (int i=0;i<17;i++)//17
	{
		for (int j=0;j<5;j++)
		{
			m_pStoneArray[i][j]=NULL;
		}
	}
	m_pMarketItemList.clear();
	m_pTradeItemList.clear();
	m_pAllItemList.clear();
	m_pAllItemMap.clear();
}

OtherRole::~OtherRole()
{

}

OtherRole* OtherRole::create()
{
	OtherRole* pRoleData = new OtherRole;
	return pRoleData;
}

bool OtherRole::init()
{
	return true;
}

void OtherRole::onCPEvent( const std::string &eventName )
{

}

void OtherRole::UpdStoneArray()
{
	for (int i=0;i<16;i++)
	{
		for (int j=0;j<5;j++)
		{
			m_pStoneArray[i][j]=NULL;
		}
	}

	UserItems items = m_pAllItemMap;
	int n=0;
	int m=n;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem && pItem->position<ItemPosition_stone_begin && pItem->position>ItemPosition_stone_end)
		{
			int i=(ItemPosition_stone_begin-1-pItem->position)/5;
			int j=(ItemPosition_stone_begin-1-pItem->position)%5;
			m_pStoneArray[i][j]=pItem;
		}
	}
}

int OtherRole::getSuitCnt( int suitid )
{
	int start = ItemPosition_Equip_Neckless;
	int end = ItemPosition_Equip_Max;
	int cnt = 0;
	for(std::vector<UserItem*>::iterator it = OtherRole::m_pAllItemList.begin(); it!=m_pAllItemList.end(); it++)
	{
		UserItem* p = *it;
		if (p->position<=start && p->position>end)
		{
			int thissuitid = 0;
			LuaData::getProp(LuaData::ITEM,p->sid,"suite_id",thissuitid);
			if (thissuitid!=0 && thissuitid== suitid)
			{
				cnt++;
			}
		}
	}
	return cnt;
}
