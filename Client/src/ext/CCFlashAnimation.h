#ifndef __CCFLASHANIMATION__
#define __CCFLASHANIMATION__

#include <string>
#include <vector>
#include "cocos2d.h"

using namespace cocos2d;

class CPAnimation;
class CCFlashAnimation : public CCObject
{
public:
	CCFlashAnimation();
	~CCFlashAnimation();

	static CCFlashAnimation* createFAWithFileName(const std::string &fileName);
	static CCFlashAnimation* createFAWithFileNameOneDir(const std::string &fileName);

	CCActionInterval* getAnimate(int dir);
	CCSpriteFrame* getSprite(int dir);
	CCArray *getSpriteFrames(int dir);
	CCSpriteFrame *	getFirstFrame();
	void setSpeed(float speed);
	int getFrameCount() const;

private:
	void initAnimationLoader(const std::string &fileName, bool isOneDir);
	void initAnimVect(int dirCount);

	void onLoadFinish(CCObject *texture);
	void setAnimFrames(bool isTemporary);
	void setAnimFramesOneDir(bool isTemporary);
	void setAnimFramesFiveDir(bool isTemporary);

	int changeDirToSource(int dir);
	
public:
	static const float FRAME_TIME;

private:
	CCSpriteFrame *mFirstFrame;

	typedef std::vector<CPAnimation *> AnimVect;
	AnimVect mAnims;

	int mFrameCount;
	int mDirCount;
	int mState;
	std::string mFileName;
};

///////CPAnimation////////////////////////////////////////////////////
class CPAnimation : public CCAnimation
{
public:
	CPAnimation();
	~CPAnimation();

	void setFrames(CCArray* var);

public:
	static CPAnimation *create();
};

#endif // __CCFLASHANIMATION__