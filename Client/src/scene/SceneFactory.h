#ifndef ___SCENE_FACTORY_HH___
#define ___SCENE_FACTORY_HH___

#include "CCScene.h"

class SceneFactory
{
public:
	static cocos2d::CCScene *sceneWelcomeScene();
	static cocos2d::CCScene *sceneGame();
	static cocos2d::CCScene *sceneLogin();
	static cocos2d::CCScene *sceneResLoading();

	static float	switch_time;
protected:
};

#endif


