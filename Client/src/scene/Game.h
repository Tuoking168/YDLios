#ifndef __GAME_H__
#define __GAME_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameMap;
class GameUI;
class GameAlive;
class Game : public cocos2d::CCLayer
{
public:
	Game();
	~Game();
	CREATE_FUNC(Game);

    virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void draw();
	virtual void update(float dt);

public:
	static GameUI* getGameUI();
	static GameAlive* getGameAlive();
	static void changeMap();
	
private:
	void gameUpdate();

private:
	static GameMap*	m_pGameMap;
	static GameUI*	m_pGameUI;
	static GameAlive* m_pGameAlive;
};
#endif