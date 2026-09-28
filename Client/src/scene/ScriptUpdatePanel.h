#ifndef __ScriptUpdatePanel_h__
#define __ScriptUpdatePanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class CPProgressBar;
class ScriptUpdatePanel : public CCLayer, public IEventListener
{
public:
	ScriptUpdatePanel();
	~ScriptUpdatePanel();
	CREATE_FUNC(ScriptUpdatePanel);
	bool init();
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
	void initUI();
	void refresh();

	void downloadListFile();
	void downloadListFileResult(const std::string &result);

	void downloadDataFileBegin();
	void downloadDataFileResult(const std::string &result);
	void downloadDataFileEnd(bool success = false);

	void onCPEvent(const std::string &eventName);

private:
	CPProgressBar *mProgressBar;
	CCLabelTTF *mProgressLabel;
	CCNode *mHeadAnim;

	int mDownloadCnt;
	int mDownloadIndex;
	int mDownloadType;
	int mRetryTimes;
};
#endif //__ScriptUpdatePanel_h__