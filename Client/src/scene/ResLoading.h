#ifndef __RES_LOADING_H__
#define __RES_LOADING_H__

#include "CCLayer.h"
#include "CCLabelTTF.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class CPProgressBar;
class ResLoading : public CCLayer, public IEventListener
{
public:
	ResLoading();
	~ResLoading();
    CREATE_FUNC(ResLoading);
	bool init();

private:
	void initUI();

	void onUpdate(int index);
	void onUpdateEnd();

	void enterGame();
	void backLogin();
	void checkTimeOut(float dt);

	void onCPEvent(const std::string &eventName);
	
private:
	CPProgressBar *mProgressBar;
	CCLabelTTF *mPercentLabel;
	CCNode *mHeadAnim;

	int mTotalSource;
};

#endif  // __RES_LOADING_H__