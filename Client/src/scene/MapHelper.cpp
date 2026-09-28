#include "MapHelper.h"
#include "cocos2d.h"
#include "MapModule.h"

#include "userdata/LayoutData.h"

using namespace cocos2d;

cocos2d::CCNode * MapHelper::getSignNode( int signType )
{
	CCNode *ret = NULL;
	switch (signType)
	{
	case MapSignType::me:
		{
			ret = LayoutData::getSprite(CPModuleName::MAP, "blueSign");

			//
			CCSize size = ret->getContentSize();
			const float dTime = LayoutData::getFloat(CPModuleName::MAP, "blinkDT");
			CCSprite *purple = LayoutData::getSprite(CPModuleName::MAP, "purpleSign");
			purple->setPosition(ccp(size.width/2, size.height/2));
			purple->runAction(CCRepeatForever::create(CCSequence::create(
				CCHide::create(),
				CCDelayTime::create(dTime),
				CCShow::create(),
				CCDelayTime::create(2 * dTime),
				NULL)));
			ret->addChild(purple);

			//
			CCSprite *yellow = LayoutData::getSprite(CPModuleName::MAP, "yellowSign");
			yellow->setPosition(ccp(size.width/2, size.height/2));
			yellow->runAction(CCRepeatForever::create(CCSequence::create(
				CCHide::create(),
				CCDelayTime::create(2 * dTime),
				CCShow::create(),
				CCDelayTime::create(dTime),
				NULL)));
			ret->addChild(yellow);
			break;
		}
	case MapSignType::monster:
		{
			ret = LayoutData::getSprite(CPModuleName::MAP, "redSign");
			break;
		}
	case MapSignType::pet:
		{
			ret = LayoutData::getSprite(CPModuleName::MAP, "purpleSign");
			break;
		}
	case MapSignType::npc:
		{
			ret = LayoutData::getSprite(CPModuleName::MAP, "yellowSign");
			break;
		}
	case MapSignType::target_pos:
		{
			ret = LayoutData::getSprite(CPModuleName::MAP, "yellowSign");

			CCSize size = ret->getContentSize();
			const float dTime = LayoutData::getFloat(CPModuleName::MAP, "blinkDT");
			CCSprite *blue = LayoutData::getSprite(CPModuleName::MAP, "blueSign");
			blue->setPosition(ccp(size.width/2, size.height/2));
			blue->runAction(CCRepeatForever::create(CCSequence::create(
				CCHide::create(),
				CCDelayTime::create(dTime),
				CCShow::create(),
				CCDelayTime::create(dTime),
				NULL)));
			ret->addChild(blue);
			break;
		}
	case MapSignType::portal:
		{
			ret = LayoutData::getSprite(CPModuleName::MAP, "portalSign");
			break;
		}
	case MapSignType::boss:
		{
			ret = LayoutData::getSprite(CPModuleName::MAP, "bossSign");
			break;
		}
	}
	return ret;
}
