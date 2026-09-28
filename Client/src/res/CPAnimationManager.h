#ifndef __CPAnimationManager_h__
#define __CPAnimationManager_h__

#include <string>
#include <map>
#include "utils/MacroUtils.h"

namespace cocos2d
{
	class CCSprite;
}

class CCFlashAnimation;
class CPAnimationManager
{
public:
	static CPAnimationManager &instance();

	CCFlashAnimation *getAnimationMultDir(const std::string &name);
	CCFlashAnimation *getAnimationMultDir(const std::string &name, bool needRetain);
	CCFlashAnimation *getAnimationOneDir(const std::string &name);
	CCFlashAnimation *getAnimationOneDir(const std::string &name, bool needRetain);

	cocos2d::CCSprite *getOneDirAnimSprite(const std::string &name);
	cocos2d::CCSprite *getOneDirAnimSprite(const std::string &name, bool needRetain);

	void clear(bool deep);

private:
	CP_MAKE_STATIC_CLASS(CPAnimationManager);

	CCFlashAnimation *getAnimation(const std::string &name, bool isOneDir, bool needRetain);

private:
	struct AnimData
	{
		AnimData()
			:anim(NULL)
			,needRetain(false)
		{}
		CCFlashAnimation *anim;
		bool needRetain;
	};
	typedef std::map<std::string, AnimData> AnimationMap;
	AnimationMap mAnimMap;
};
#define CPAnimMnger CPAnimationManager::instance()

#endif //__CPAnimationManager_h__