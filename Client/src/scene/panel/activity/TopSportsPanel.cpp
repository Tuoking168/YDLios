#include "TopSportsPanel.h"
#include "EntityDefinition.h"
#include "ActivityModule.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"
#include "SceneDefinition.h"

#include "ext/CCActionDestroy.h"

#include "ext/CCMenuEx.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"

#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/NPCFunctionData.h"
#include "controls/CPRichText.h"
#include "event/CPEventHelper.h"
#include "OpenSportsPanel.h"

TopSportsPanel::TopSportsPanel():
	m_pRightMenu(NULL)
{
}

TopSportsPanel::~TopSportsPanel()
{
	
}

bool TopSportsPanel::init()
{
	if (!MenuListPanel::init())
	{
		return false;
	}

	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "openSportsTitle");
	addChild(title);

	return true; 
}

void TopSportsPanel::hide()
{
	this->removeFromParent();
}

const std::string TopSportsPanel::dataTableName()
{
	return "gdSportsOptions";
}
void TopSportsPanel::onSwitch(int tag)
{
	switch (tag)
	{
	case Panel_OpenSports: 
		{
			OpenSportsPanel* panel = OpenSportsPanel::create();
			addPanel(panel);
			break;  
		}
	default:
		break;
	}	
}
