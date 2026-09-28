#include "Game.h"
#include "cocos2d.h"
#include "GameMap.h"
#include "GameUI.h"
#include "GameAlive.h"
#include "UserDataModule.h"

#include "ext/AstarPathfinder.h"

#include "userdata/netdata/GhostManager.h"
#include "userdata/mapdata/PixesMap.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/UserData.h"
#include "userdata/GameData.h"
#include "userdata/SceneData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GameRole.h"

#include "panel/TaskPanel.h"

#include "res/AudioLoader.h"
#include "res/PlistLoader.h"

#include "event/CPEventHelper.h"
#include "logic/CPUpdateFunctor/CPUpdateFunctorManager.h"


//////Game/////////////////////////////////////////////////////////
GameUI*	Game::m_pGameUI = NULL;
static int sGameCount = 0;
GameAlive* Game::m_pGameAlive = NULL;
GameMap* Game::m_pGameMap = NULL;

Game::Game()
{
	sGameCount++;
}

Game::~Game()
{
	sGameCount--;
	if (sGameCount <= 0)
	{
		m_pGameUI = NULL;
	}
}

bool Game::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
 	setTouchEnabled(true);
 	CCLog("Game init begin...");
	
	m_pGameMap = GameMap::create();	
	m_pGameMap->setPosition(CCPointZero);
	addChild(m_pGameMap);

	m_pGameAlive = GameAlive::create();
	addChild(m_pGameAlive);

	m_pGameUI = GameUI::create();
	m_pGameUI->setPosition(CCPointZero);
	addChild(m_pGameUI);

	CCLog("##********** 1");
	//
	changeMap();

	CCLog("Game init end...");

	return true;
}

void Game::onEnter()
{
	CCLayer::onEnter();

	PlistLoader::unloadLoading();
	SceneData::setHasEnterScene(true);

	schedule(schedule_selector(Game::update), 0.1f);
	m_pGameMap->setVisible(true);
}

void Game::onExit()
{
	unschedule(schedule_selector(Game::update));
	CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "Game", "");
	m_pGameMap->setVisible(false);
	CCDirector::sharedDirector()->purgeCachedData();
	CCLayer::onExit();
}

void Game::draw()
{
	CCLayer::draw();
	gameUpdate();
}

void Game::update( float dt )
{
	float gCD = HeroData::getGlobalCD();
	gCD -= 0.1f;
	if (gCD < 0)
	{
		gCD = 0;
	}
	HeroData::setGlobalCD(gCD);

	//
	GhostManager *ghostMnger = GameData::getGhostManager();
	if(ghostMnger)
	{
		ghostMnger->ghostManagerUpdate(dt);
	}
	CPUpdateFunctorManager::instance()->onUpdate(dt);
}

void Game::gameUpdate()
{
	GameRole* pHero = GameData::getMyRole();
	if (pHero->getBodySprite())
	{
		pHero->updateSceenPosition();
		const CCPoint &mapPt = pHero->getMapPosition();
		const CCPoint &screenPt = pHero->getSceenPosition();
		const int x = mapPt.x - screenPt.x;
		const int y = mapPt.y + screenPt.y - SystemData::size_y;
		GameData::getPixesMap()->render(x, y);
		m_pGameAlive->setPosition(ccp(-x, y));
	}
}

GameUI* Game::getGameUI()
{
	return m_pGameUI;
}

GameAlive* Game::getGameAlive()
{
	return m_pGameAlive;
}

void Game::changeMap()
{
	m_pGameMap->removeAllChildren();
	m_pGameAlive->removeAllChildren();
	PixesMap* map = GameData::getPixesMap();
	if (map) map->attach(m_pGameMap);
	GhostManager* pGhostManager = GameData::getGhostManager();
	if (pGhostManager) pGhostManager->addParent(m_pGameAlive);
	GameData::s_user->addMapConns();

	// music
	const int mapID = GameData::getCurrentMap()->mID;
	std::string musicPath;
	StaticData::getMapMusic(mapID, musicPath);
	AudioLoader::transform(musicPath);

	// auto
	CPEventHelper::setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_1, GameData::getCurrentMap()->mID);
	CPEventHelper::dispatcher(CPEventName::UI_OPEN, "Game", "");
	GameRole* myRole = GameData::getMyRole();
	if (myRole)
	{
		myRole->checkAutoMove();
		myRole->m_bTranfering = false;
	}
}
