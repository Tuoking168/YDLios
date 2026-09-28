#include "OpenSportsPanel.h"
#include "EntityDefinition.h"

#include "userdata/SystemData.h"
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
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"

#include "utils/StringUtils.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "controls/CPItemComponents.h"
#include "event/CPEventHelper.h"
#include "ActivityDataHelper.h"

#include "LevelSportsPanel.h"
#include "MountSportsPanel.h"
#include "StoneSportsPanel.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"

OpenSportsPanel::OpenSportsPanel()
{

}

OpenSportsPanel::~OpenSportsPanel()
{

}

bool OpenSportsPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	LevelSportsInfoPanel* levelSport = LevelSportsInfoPanel::create();
	addChild(levelSport);

	MountSportsInfoPanel* mountSport = MountSportsInfoPanel::create();
	addChild(mountSport);

	StoneSportsInfoPanel* stoneSport = StoneSportsInfoPanel::create();
	addChild(stoneSport);

	for (int i=0;i<2;i++)
	{
		CCSize size = SystemData::getLayoutSize("opensports.sprite.line");
		CCPoint point = SystemData::getLayoutPoint("opensports.sprite.line"+StringUtils::toString(i));
		CCScale9Sprite* sprite=SystemData::getScale9SpriteByPlist("opensports.sprite.line",size.width,size.height);
		sprite->setAnchorPoint(CCPointZero);  
		sprite->setPosition(point);
		addChild(sprite); 
	}

	return true;
}