#ifndef __RubbishBagPanel_H__
#define __RubbishBagPanel_H__

#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "ext/PartPanel.h"
#include "userdata/UserItemData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "CCObject.h"
#include "CCTabelViewEx.h"
USING_NS_CC_EXT;

class RubbishBagPanel: public PartPanel
{
public:
	RubbishBagPanel();
	~RubbishBagPanel();
	virtual bool init();
	CREATE_FUNC(RubbishBagPanel);

private:
	bool initUI();
	void closecallback( CCObject* pSender );
	void initButton();
	void buttonCallBack( CCObject* pSender );

private:
	enum MyEnum
	{
		oneKeySell,
	};
};

#endif