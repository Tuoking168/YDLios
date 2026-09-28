#ifndef __PatchUpdatePanel_h__
#define __PatchUpdatePanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class CPProgressBar;
class PatchUpdatePanel : public CCLayer, public IEventListener
{
public:
	PatchUpdatePanel();
	~PatchUpdatePanel();
	CREATE_FUNC(PatchUpdatePanel);
	bool init();
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
	void initUI();
	void refresh(int percent);

	void downloadPatchFile();
	void downloadPatchFileResult(const std::string &result);
	void downloadPatchFileEnd(bool success = false);

	void onCPEvent(const std::string &eventName);

private:
	CPProgressBar *mProgressBar;
	CCLabelTTF *mProgressLabel;
	CCNode *mHeadAnim;

	int mRetryTimes;
};
#endif //__PatchUpdatePanel_h__