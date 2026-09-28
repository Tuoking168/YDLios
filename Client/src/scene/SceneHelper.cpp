#include "SceneHelper.h"
#include "MsgScene.h"
#include "SceneDefinition.h"
#include "ErrorDefinition.h"

#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/Ghost.h"
#include "userdata/netdata/GhostManager.h"

#include "network/HandleMessage.h"
#include "event/CPEventHelper.h"
#include "userdata/SystemData.h"



static void enterSceneRequest( int reason, int id, bool needShoes )
{
	if (SceneHelper::isUnknownMapInMini(id))
	{
		CPEventHelper::msgNotify("PreventMiniSwitchToUnknownMap", "",0,0,0,0);
		return ;
	}

	if (needShoes)
	{
		if (CommonFunction::checkShoesCount(id, reason) != Error::Success)
		{
			return;
		}
	}

	MsgEnterSceneRequest *msg = new MsgEnterSceneRequest;
	msg->reason = reason;
	msg->sid = id;
	HandleMessage::sendMessage(msg);
}

bool SceneHelper::isUnknownMapInMini(const int nMapID)
{
	if (1==SystemData::getConfigInt("mini") && (130==nMapID || 150==nMapID || 160==nMapID || 170==nMapID || 
		1004 == nMapID || 1005 ==nMapID || 1008 ==nMapID || 1006 ==nMapID
		|| 1009 ==nMapID || 1030 ==nMapID ))
	{
		return true;
	}
	return false;
}
////////SceneHelper/////////////////////////////////////////////////////
void SceneHelper::teleportToNPCRequest( int npcID )
{
	enterSceneRequest(Scene::seNpc, npcID, true);
}

void SceneHelper::teleportToMapRequest( int mapID )
{
	teleportToMapRequest(mapID, 0, 0);
}

void SceneHelper::teleportToMapRequest( int mapID, int x, int y )
{
	enterSceneRequest(Scene::seInstance, mapID, true);
}

void SceneHelper::teleportToMonsterRequest( int monsterID )
{
	enterSceneRequest(Scene::seMonster, monsterID, true);
}

void SceneHelper::teleportToActivityBoss( int activityID )
{
	enterSceneRequest(Scene::seBoss, activityID, true);
}

void SceneHelper::teleportByPortalRequest( int portalID )
{
	enterSceneRequest(Scene::sePortal, portalID, false);
}

void SceneHelper::autoMoveToNPC( int npcID )
{
	GameData::getGhostManager()->gotoGhostPos(npcID, "npcs", GHOST_TYPE_NPC);
}

void SceneHelper::autoMoveToMonster( int monsterID )
{
	GameData::getGhostManager()->gotoGhostPos(monsterID, "monsters", GHOST_TYPE_MONSTER);
}

void SceneHelper::backToNormalMapRequest()
{
	enterSceneRequest(Scene::seBack, GameData::s_user->mMap.mID, false);
}
