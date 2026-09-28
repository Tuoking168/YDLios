#ifndef __SceneHelper_h__
#define __SceneHelper_h__

#include "utils/MacroUtils.h"

class SceneHelper
{
public:
	static void teleportToNPCRequest(int npcID );
	static void teleportToMapRequest(int mapID);
	static void teleportToMapRequest(int mapID, int x, int y);
	static void teleportToMonsterRequest(int monsterID);
	static void teleportToActivityBoss(int activityID);

	static void teleportByPortalRequest(int portalID);

	static void autoMoveToNPC(int npcID);
	static void autoMoveToMonster(int monsterID);

	static void backToNormalMapRequest();
	static bool isUnknownMapInMini(const int );//判断地图是否在mini包是否存在

private:
	CP_MAKE_STATIC_CLASS(SceneHelper);
};

#endif //__SceneHelper_h__