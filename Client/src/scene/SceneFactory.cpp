#include "SceneFactory.h"
#include "WelcomeScene.h"
#include "Login.h"
#include "ResLoading.h"
#include "Game.h"

using namespace cocos2d;

float SceneFactory::switch_time = 0.5f;

#define MAKESCENE(className)\
	cocos2d::CCScene*SceneFactory::scene##className()\
{\
CCScene*scene=NULL;\
do\
{\
scene=CCScene::create();\
CC_BREAK_IF(!scene);\
className *layer=className::create();\
CC_BREAK_IF(!layer);\
scene->addChild(layer);\
}while(0);\
return scene;\
}


MAKESCENE(WelcomeScene)

MAKESCENE(Login)

MAKESCENE(ResLoading)

MAKESCENE(Game)
