#include "EffectSprite.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "userdata/SystemData.h"
#include "ext/CCActionDestroy.h"
#include "ext/CCFlashAnimation.h"
#include "EffectDefinition.h"
#include "userdata/luadata/LuaData.h"

EffectSprite::EffectSprite():
	m_iCurType(0),
	m_iLifeTime(0),
	m_iPlayTimes(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

EffectSprite::~EffectSprite()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}

EffectSprite* EffectSprite::create( int type ,int playtimes,int lifetime)
{
	EffectSprite* sprite = new EffectSprite();
	if(sprite && sprite->init(type,playtimes,lifetime))
	{
		sprite->autorelease();
		return sprite;
	}
	if (sprite)
	{
		delete sprite;
	}
	return NULL;
}

bool EffectSprite::init( int type ,int playtimes,int lifetime)
{
	if (!CCSprite::init())
	{
		return false;
	}
	m_iCurType=type;
	m_iPlayTimes=playtimes;
	m_iLifeTime=lifetime;
	initEffect();
	return true;
}

void EffectSprite::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			updateLifeTime(1);
		}
	}
}

void EffectSprite::initEffect()
{
	/*if (m_pEffectSprite)
	{
		m_pEffectSprite->stopAllActions();
		m_pEffectSprite->removeFromParent();
	}*/
	CCFlashAnimation *anim = SystemData::getAnimationOneDir(getEffectUrl());
	if (anim)
	{
		//m_pEffectSprite=CCSprite::create();	
		CCSpriteFrame *frame = anim->getSprite(0);
		if (frame)
		{
			this->setContentSize(frame->getRect().size); 
		}
		CCActionInstantRemoveFromParentEx *rmv = CCActionInstantRemoveFromParentEx::create(this);

		if (m_iPlayTimes==0)
		{
			this->runAction(CCRepeatForever::create(anim->getAnimate(0)));
		}
		else
		{
			this->runAction(CCSequence::create(CCRepeat::create(anim->getAnimate(0),m_iPlayTimes),rmv,NULL));
		}
	}
}

std::string EffectSprite::getEffectUrl()
{
	std::string url="";
	LuaData::getProp("gdEffect",m_iCurType,"path",url);
	return url;
}

void EffectSprite::setEffectTime( int playtimes,int lifetime )
{
	m_iPlayTimes=playtimes;
	m_iLifeTime=lifetime;
	initEffect();
}

void EffectSprite::updateLifeTime( int seconds )
{
	if (m_iLifeTime!=0)
	{
		m_iLifeTime=m_iLifeTime-seconds;
		if (m_iLifeTime==0)
		{
			this->removeFromParent();
		}
	}
}

