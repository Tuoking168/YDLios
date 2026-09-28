#ifndef __GENERAL_MENU_LISTENER_H__
#define __GENERAL_MENU_LISTENER_H__

/*
功能：可以放入任意Node类型对象的容器。
*/

#include "event/EventListener.h"
#include "ext/GeneralMenu.h"
#include "cocos2d.h"
USING_NS_CC;

class GeneralMenuListener : public GeneralMenu, public EventListener
{
public:
	GeneralMenuListener();
	CREATE_FUNC(GeneralMenuListener);
	virtual bool init();
	~GeneralMenuListener();

public:
	virtual void onEnter();
	virtual void onExit();
};

#endif//__GENERAL_MENU_LISTENER_H__