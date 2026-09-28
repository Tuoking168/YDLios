#include "AnimationLoader.h"
#include "cocos2d.h"
USING_NS_CC;

void AnimationLoader::loadAnimationFromPlist( const char* plistfile )
{
	//add the sprite frames to frame cache
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistfile);

	//put all the frames to a frame array
	CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile(plistfile);

	//
	
}

