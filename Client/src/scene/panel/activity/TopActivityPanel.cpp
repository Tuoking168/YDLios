#include "TopActivityPanel.h"
#include "EntityDefinition.h"
#include "ActivityModule.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"

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

#include "scene/panel/TreasureHuntPanel.h"
#include "LevelSportsPanel.h"
#include "MountSportsPanel.h"
#include "StoneSportsPanel.h"
#include "ConsumeDrawPanel.h"
#include "WealthGodPanel.h"
#include "scene/panel/worship/EmigratedPanel.h"
#include "event/CPEventHelper.h"
#include "TopSportsPanel.h"

#include "OpenActivityPanel.h"
#include "InvestPlanPanel.h"

TopActivityPanel::TopActivityPanel()
{
}

TopActivityPanel::~TopActivityPanel()
{
	
}

bool TopActivityPanel::init()
{
	if (!MenuListPanel::init())
	{
		return false;
	}

	CCSprite *title = LayoutData::getSprite(CPModuleName::ACTIVITY, "investPlanTitle");
	addChild(title);

	return true;
}

void TopActivityPanel::hide()
{
	this->removeFromParent();
}

const std::string TopActivityPanel::dataTableName()
{
	return "gdActivityOptions";
}
void TopActivityPanel::onSwitch(int tag)
{
	switch (tag)
	{
	case Panel_InvestPlan:
		{
			InvestPlanPanel* panel = InvestPlanPanel::create();
			addPanel(panel);
			break;
		}
	default:
		break;
	}
}