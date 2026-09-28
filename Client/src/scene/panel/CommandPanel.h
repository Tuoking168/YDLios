#ifndef __COMMAND_PANEL_H__
#define __COMMAND_PANEL_H__

/*
功能：GM命令调试窗口
*/
#include "cocos2d.h"
#include "event/IEventListener.h"
#include "ext/TextField.h"

using namespace cocos2d;

class CommandPanel : public CCNode, public IEventListener
{
public:
	CommandPanel();
	static CommandPanel* create();
	virtual bool init();
	~CommandPanel(); 

private:
	void menuCallback( CCObject* pSender );
	void sendCmd(const std::string &cmd);
	void readCmd(const std::string &cmd);

	void onCPEvent(const std::string &eventName);

private:
	TextField*			m_pInputTextField;
};

#endif//__COMMAND_PANEL_H__