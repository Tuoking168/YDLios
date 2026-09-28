#include "BuffPanel.h"
#include "MainUIModule.h"

#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/LayoutData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "utils/StringUtils.h"


BuffPanel::BuffPanel()
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

BuffPanel::~BuffPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool BuffPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	refresh();

	return true;
}

void BuffPanel::refresh()
{
	removeAllChildren();

	const CCPoint &firstPt = LayoutData::getPoint(CPModuleName::MAIN_UI, "buffFirst");
	const int ox = LayoutData::getInt(CPModuleName::MAIN_UI, "buffOx");
	std::string iconKey;
	int k = 0;
	const IDVector &vect = HeroData::getBuffVect();
	for (int i = 0; i < (int)vect.size(); i++)
	{
		iconKey.clear();
		StaticData::getGeneIcon(vect[i], iconKey);
		if (!iconKey.empty() && iconKey != "0")
		{
			CCSprite *icon = LayoutData::getSpriteByFrameName(iconKey);
			if (icon)
			{
				icon->setAnchorPoint(CCPointZero);
				icon->setPosition(ccp(firstPt.x + k * ox, firstPt.y));
				icon->setScale(0.5f); 
				addChild(icon);
				k++;
			}
		}
	}
}

void BuffPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessagePlayerUpdGeneNotify" ||
			source == "HandleMessagePlayerRmvGeneNotify")
		{
			refresh();
		}
	}
}
