#include "BlackColorPanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/Ghost.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/OtherRole.h"
#include "userdata/netdata/GhostManager.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "network/HandleMessage.h"
#include "event/EventProtocol.h"
#include "userdata/NPCFunctionData.h"
#include "script/LuaWrapper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

BlackColorPanel::BlackColorPanel()
{
}

BlackColorPanel::~BlackColorPanel()
{

}

BlackColorPanel* BlackColorPanel::create()
{
	BlackColorPanel* pPanel = new BlackColorPanel();
	if(pPanel && pPanel->init())
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

bool BlackColorPanel::init()
{		
	CCLayerColor *blackLayer = CCLayerColor::create(ccc4(0, 0, 0, 0));
	blackLayer->setPosition(CCPointZero);
	addChild(blackLayer);

	return true;
}

void BlackColorPanel::menucallback( CCObject* pSender )
{

}
