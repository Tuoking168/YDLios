//////////////////////////////////////////////////////////////////////////
//Function: Sprite with an Animation.
//  1.this could be used as a plugin to other CCNode
//	2.this could be used as the cloth or weapon of players
//Author:tom
//Time:6/6/2013
//////////////////////////////////////////////////////////////////////////

#ifndef __CC_ANIMATION_SPRITE__
#define __CC_ANIMATION_SPRITE__

#include "CCSprite.h"
using namespace cocos2d;

class CCAnimationSprite : public CCSprite
{
public:
	CCAnimationSprite();

	static CCAnimationSprite* create(const char* name, bool repeat = false);

	//dynamically bind one animation to the sprite, this will take effect at next time run the animation
	void setAnimation(const char* name);

	//set the if the sprite run animation repeatedly, this will take effect at next time run the animation
	void setRepeat(bool bRepeat);

	bool initWithAnimation(const char* name, bool repeat=false);

	//run the animation
	void runAnimation();

private:
	CCAnimation* m_pAnimation;
	bool		 m_bRepeat;
};
#endif//__CC_ANIMATION_SPRITE__
