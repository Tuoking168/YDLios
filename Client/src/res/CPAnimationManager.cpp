#include "CPAnimationManager.h"
#include "cocos2d.h"

#include "ext/CCFlashAnimation.h"

#include "utils/TestUtils.h"

using namespace cocos2d;

////////CPAnimationManager/////////////////////////////////////////
CPAnimationManager::CPAnimationManager()
{

}

CPAnimationManager::~CPAnimationManager()
{
	clear(true);
}

CPAnimationManager & CPAnimationManager::instance()
{
	static CPAnimationManager ret;
	return ret;
}

CCFlashAnimation * CPAnimationManager::getAnimationMultDir( const std::string &name )
{
	return getAnimationMultDir(name, false);
}

CCFlashAnimation * CPAnimationManager::getAnimationMultDir( const std::string &name, bool needRetain )
{
	return getAnimation(name, false, needRetain);
}

CCFlashAnimation * CPAnimationManager::getAnimationOneDir( const std::string &name )
{
	return getAnimationOneDir(name, false);
}

CCFlashAnimation * CPAnimationManager::getAnimationOneDir( const std::string &name, bool needRetain )
{
	return getAnimation(name, true, needRetain);
}

cocos2d::CCSprite * CPAnimationManager::getOneDirAnimSprite( const std::string &name )
{
	return getOneDirAnimSprite(name, false);
}

cocos2d::CCSprite * CPAnimationManager::getOneDirAnimSprite( const std::string &name, bool needRetain )
{
	CCSprite *ret = CCSprite::create();
	CCFlashAnimation *anim = getAnimationOneDir(name, needRetain);
	if (anim)
	{
		CCSpriteFrame *frame = anim->getSprite(0);
		if (frame)
		{
			ret->setContentSize(frame->getRect().size);
		}
		ret->runAction(CCRepeatForever::create(anim->getAnimate(0)));
	}
	return ret;
}

void CPAnimationManager::clear( bool deep )
{
	AnimationMap temp;
	AnimationMap::const_iterator it = mAnimMap.begin();
	AnimationMap::const_iterator itEnd = mAnimMap.end();
	while (it != itEnd)
	{
		const AnimData &data = it->second;
		if (deep)
		{
			data.anim->release();
		}
		else
		{
			if (data.needRetain)
			{
				temp[it->first] = data;
			}
			else
			{
				data.anim->release();
			}
		}
		it++;
	}
	mAnimMap = temp;
}

CCFlashAnimation * CPAnimationManager::getAnimation( const std::string &name, bool isOneDir, bool needRetain )
{
	AnimationMap::iterator it = mAnimMap.find(name);
	if (it != mAnimMap.end())
	{
		return it->second.anim;
	}

	CCFlashAnimation *anim = NULL;
	if (isOneDir)
	{
		anim = CCFlashAnimation::createFAWithFileNameOneDir(name);
	}
	else
	{
		anim = CCFlashAnimation::createFAWithFileName(name);
	}
	
	if (anim)
	{
		mAnimMap[name].anim = anim;
		mAnimMap[name].needRetain = needRetain;
		return anim;
	}
	CCLog(">>>Error: CPAnimationManager::getAnimationOneDir failed, name = %s", name.c_str());
	return NULL;
}
