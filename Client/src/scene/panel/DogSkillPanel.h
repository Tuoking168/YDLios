#ifndef __DOGSKILL_PANEL_H__
#define __DOGSKILL_PANEL_H__

/*
功能：GM命令调试窗口
*/
#include "cocos2d.h"
#include "scene/GameUI.h"
#include "ext/TextField.h"
#include "event/CPEventDispatcher.h"

using namespace cocos2d;

class DogSkillPanel : public CCNode, public IEventListener
{
public:
	DogSkillPanel();
	static DogSkillPanel* create();
	virtual bool init();
	~DogSkillPanel(); 

	void refreshButtons();
	void onCPEvent(const std::string &eventName);
protected:
	void menuCallback( CCObject* pSender );
	
private:
	//TextField*			m_pInputTextField;
	CCMenu* m_pMainMenu;

	bool m_isStop;

	enum ChildTag
	{
		Tag_NULL = 0,
		Button_Update,
		Button_Call,
		Button_Stop,
		Button_Attack,
	};
};

#endif//__DOGSKILL_PANEL_H__