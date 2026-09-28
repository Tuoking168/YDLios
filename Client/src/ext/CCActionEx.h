#ifndef __CCCOMMAND_EXT__
#define __CCCOMMAND_EXT__

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class CCActionVertex : public cocos2d::CCActionInstant
{
	public:
		CCActionVertex(){}
		virtual ~CCActionVertex(){}
		/** creates a Place action with a position */
		static CCActionVertex * actionWithVertex(float vertex);
		/** Initializes a Place action with a position */
		bool initWithVertex(float vertex);
		//super methods
		virtual void startWithTarget(CCNode *pTarget);
		//virtual CCObject* copyWithZone(CCZone *pZone);
	protected:
		float	_vertexZ;
};

class CCActionMusicFadeTo : public cocos2d::CCActionInterval
{
public:
	/** initializes the action */
	bool initWithDuration(float duration);

	//virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void update(float time);

public:
	/** creates the action */
	static CCActionMusicFadeTo* create(float duration);

protected:
	float m_fVolumeDst;
	float m_fVolumeSrc;
	float m_fVolumeDiff;
};


class CCFollowOnTop : public cocos2d::CCFollow
{
public:
	static CCFollowOnTop* actionWithTarget(CCNode *pFollowedNode);
protected:
	virtual void step(float dt);

	float	_time_accumulate;
};

#endif
