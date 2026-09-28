#include "CCAnimationSprite.h"
#include "cocos2d.h"
USING_NS_CC;

CCAnimationSprite::CCAnimationSprite()
	: m_pAnimation(NULL)
	, m_bRepeat(false)
{

}

CCAnimationSprite*	CCAnimationSprite::create(const char* name, bool repeat)
{
	if (name!=NULL)
	{
		CCAnimationSprite *sprite = new CCAnimationSprite();
		if (sprite && sprite->initWithAnimation(name, repeat))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
	}
	return NULL;
}

bool CCAnimationSprite::initWithAnimation(const char* name, bool repeat)
{
	if (name!=NULL)
	{
		if(!init())
		{
			return false;
		}
		setAnimation(name);
		if (m_pAnimation)
		{
			setRepeat(repeat);
			return true;
		}
	}

	return false;
}

void CCAnimationSprite::runAnimation()
{
	if (m_pAnimation)
	{
		//stop all the actions before
		stopAllActions();
		CCAction* action = NULL;
		if (!m_bRepeat)
		{
			action = CCAnimate::create(m_pAnimation);
		}
		else
		{
			action = CCRepeatForever::create(CCAnimate::create(m_pAnimation));
		}

		if (action)
		{
			runAction(action);
		}
	}
}

void CCAnimationSprite::setAnimation( const char* name )
{
	CCAnimation* anim = CCAnimationCache::sharedAnimationCache()->animationByName(name);
	if(anim)
	{
		m_pAnimation = anim;
	}
}

void CCAnimationSprite::setRepeat( bool bRepeat )
{
	m_bRepeat = bRepeat;
}

