#ifndef __CPProgressBar_h__
#define __CPProgressBar_h__

#include "misc_nodes/CCProgressTimer.h"

class CPProgressBar : public cocos2d::CCNode
{
public:
	CPProgressBar();
	~CPProgressBar();

public:
	static CPProgressBar *create(cocos2d::CCSprite *body);
	static CPProgressBar *create(cocos2d::CCSprite *body, cocos2d::CCNode *nHead, cocos2d::CCNode *nTail);

	void	setPercentage(float fp);
	float	getPercentage(void);

	void	runProgressTo(float dt, float fp);

private:
	bool initWithData(cocos2d::CCSprite *body, cocos2d::CCNode *nHead, cocos2d::CCNode *nTail);
	void doUpdate(float dt);

private:
	cocos2d::CCProgressTimer *mProgress;
	cocos2d::CCNode *mHead;
	cocos2d::CCNode *mTail;

	float   mfp;
	float	mdfp;
};
#endif //__CPProgressBar_h__