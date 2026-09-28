#ifndef __EffectSprite_H__
#define __EffectSprite_H__


#include "cocos-ext.h"
#include "event/IEventListener.h"
#include "cocos2d.h"
USING_NS_CC_EXT;
USING_NS_CC;


class EffectSprite :public CCSprite, public IEventListener
{
public:
	EffectSprite();
	~EffectSprite();
	virtual bool init(int type,int playtimes,int lifetime);
	static EffectSprite* create(int type,int playtimes=0,int lifetime=0);
	void setEffectTime(int playtimes,int lifetime);

	void onCPEvent(const std::string &eventName);
private:
	void initEffect();
	std::string getEffectUrl();
	void updateLifeTime(int seconds);
private:
	int m_iCurType;
	int m_iLifeTime;
	int m_iPlayTimes;
};

#endif//__EffectSprite_H__