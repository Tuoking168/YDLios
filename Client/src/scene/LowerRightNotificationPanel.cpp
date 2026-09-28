#include "LowerRightNotificationPanel.h"
#include "NotificationHelper.h"
#include "NotificationModule.h"

#include "ext/CCActionDestroy.h"
#include "controls/CPNodeHelper.h"

#include "userdata/LayoutData.h"

#define		TAG_LAST_NOTE_START	1
#define		TAG_MOVE_ACTION		7
#define		HIGHT			20

static void showRightNote( CCNode *noteNode, CCNode *containerLayer)
{
	if (!noteNode)
	{
		return;
	}

	int lastTag = 1;

	CCNode *lastNote = NULL;
	if (containerLayer->getChildren())
	{
		lastNote = dynamic_cast<CCNode*>(containerLayer->getChildren()->lastObject());
	}
	if (lastNote)
	{
		lastTag = lastNote->getTag()+1;
		containerLayer->stopActionByTag(TAG_MOVE_ACTION);
		int x = 0, y = 0;
		y = HIGHT*(lastTag-1);
		
		CCAction* action = CCMoveTo::create(0.2f, ccp(x, y));
		if (action)
		{
			action->setTag(TAG_MOVE_ACTION);
			containerLayer->runAction(action);
		}
	}
	else
	{
		containerLayer->setPosition(ccp(0, 0));
	}

	noteNode->setScaleX(1.5f);
	noteNode->setAnchorPoint(ccp(1, 0));
	noteNode->setPosition(ccp(200, HIGHT*(1-lastTag)));
	noteNode->runAction(CCSequence::create(
		CCSpawn::createWithTwoActions(CCFadeIn::create(0.2f), CCScaleTo::create(0.2f, 1.0f)), 
		CCDelayTime::create(5.0f),
		CCFadeOut::create(0.2f),
		CCActionInstantRemoveFromParent::create(),
		NULL));

	containerLayer->addChild(noteNode, 0, lastTag);
}

////////////LowerRightNotificationPanel///////////////////////////////////
LowerRightNotificationPanel::LowerRightNotificationPanel()
	:mContainer(NULL)
{

}

LowerRightNotificationPanel::~LowerRightNotificationPanel()
{

}

bool LowerRightNotificationPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initUI();

	return true;
}

void LowerRightNotificationPanel::onEnter()
{
	CCLayer::onEnter();
	NotificationHelper::setLowerRightPanel(this);
}

void LowerRightNotificationPanel::onExit()
{
	NotificationHelper::setLowerRightPanel(NULL);
	CCLayer::onExit();
}

void LowerRightNotificationPanel::showLowerRightNote( CCNode *noteNode )
{
	showRightNote(noteNode, mContainer);
}

void LowerRightNotificationPanel::initUI()//--右下角通知ui经验那些
{
	// lower right
	const CCSize &lowerRightSize = LayoutData::getSize(CPModuleName::NOTIFICATION, "noteAreaLowerRight");
	CCNode *clipping = CPNodeHelper::getClippingNode(lowerRightSize);
	clipping->setPosition(LayoutData::getPoint(CPModuleName::NOTIFICATION, "noteAreaLowerRight"));
	addChild(clipping);

	mContainer = CCLayer::create();
	clipping->addChild(mContainer);
}
