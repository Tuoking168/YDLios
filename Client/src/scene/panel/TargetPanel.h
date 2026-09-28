#ifndef __Target_PANEL_H__
#define __Target_PANEL_H__


#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;

class HeadPanel;
class TargetPanel : public CCLayer, public IEventListener
{
public:
	TargetPanel();
	~TargetPanel();
	bool init();
	CREATE_FUNC(TargetPanel);
	void onEnter();
	void onExit();

	void refresh();

private:
	void initUI();

	void menucallback();
	void closeCallBack( CCObject* pSender );

	void onCPEvent(const std::string &eventName);

private:
	HeadPanel *mHeadPanel;
};

#endif//__Target_PANEL_H__