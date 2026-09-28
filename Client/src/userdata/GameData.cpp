#include "GameData.h"
#include "UserData.h"
#include "network/HandleMessage.h"
#include "msgHandler/MsgMaster.h"

UserData* GameData::s_user = NULL;
MapData*	GameData::s_map=NULL;

int GameData::s_game_state = GAME_STATE_LOGIN;


void GameData::initMapData()
{
	CC_SAFE_DELETE(s_map);
	s_map = new MapData();
	s_map->initMapDate();
}

void GameData::initUserData()
{
	CC_SAFE_DELETE(s_user);
	s_user = new UserData();
}

void GameData::releaseUserData()
{
	CC_SAFE_DELETE(s_user);
	s_user = NULL;
}

void GameData::releaseMapData()
{
	CC_SAFE_DELETE(s_map);
	s_map = NULL;
}

void GameData::releaseGameDataForExit()
{
	s_game_state = GAME_STATE_EXIT;
	releaseUserData();
	releaseMapData();
	HandleMessage::setUser(NULL);
}

void GameData::initNetWorkHandle()
{
	if (!HandleMessage::hasUser())
	{
		HandleMessage::setUser( new MsgMaster);
	}
}

GameRole * GameData::getMyRole()
{
	if (s_user)
	{
		return s_user->m_pMainRole;
	}
	CCLog("GameData::getMyRole returns NULL");
	return NULL;
}

GhostManager * GameData::getGhostManager()
{
	if (s_user)
	{
		return s_user->m_pGhostManager;
	}
	CCLog("GameData::getGhostManager returns NULL");
	return NULL;
}

NetMap  * GameData::getCurrentMap()
{
	if (s_user)
	{
		return &s_user->mMap;
	}
	CCLog("GameData::getCurrentMap returns NULL");
	return NULL;
}

PixesMap * GameData::getPixesMap()
{
	if (s_user)
	{
		return s_user->m_pPixesMap;
	}
	CCLog("GameData::getPixesMap returns NULL");
	return NULL;
}

UserItemData * GameData::getUserItemData()
{
	if (s_user)
	{
		return s_user->getUserItemData();
	}
	CCLog("GameData::getUserItemData returns NULL");
	return NULL;
}

