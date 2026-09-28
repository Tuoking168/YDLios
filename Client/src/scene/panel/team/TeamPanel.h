#ifndef __GROUP_PANEL_H__
#define __GROUP_PANEL_H__

#include "cocos2d.h"
#include "event/IEventListener.h"

using namespace cocos2d;


class OperateMenu;
class CPItemComponents;
class CPChecker;
class TeamPanel : public CCLayer, public IEventListener
{
public:
	TeamPanel();
	~TeamPanel();
	CREATE_FUNC(TeamPanel);
	bool init();
	void onEnter();

private:
	void initUI();
	void refresh();

	void onMember(CCObject *target);
	void onExitTeam(CCObject *target);

	void onCPEvent(const std::string &evtName);

private:
	OperateMenu *m_pOpMenu;
	CPItemComponents *mTeamList;
	CCMenuItemImage *mExitBtn;
	CPChecker *mChecker;
};

#endif//__GROUP_PANEL_H__