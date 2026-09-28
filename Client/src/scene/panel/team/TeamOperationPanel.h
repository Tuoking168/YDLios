#ifndef __TEAM_OPERATION_H__
#define __TEAM_OPERATION_H__

#include "ext/BasePanel.h"

//just an node container
//show the team operation flag
//show the make decision panels
//deal with the event from make decision panels

class TeamOperationPanel : public BasePanel
{
public:
	bool init();
	void callback(CCObject* pSender);
	void handleEvent(int channel);
	CREATE_FUNC(TeamOperationPanel);
	enum TeamOperationTag
	{
		TAG_TEAM_MESSGE,
	};
private:
	CCMenu *m_pMenu;
};


#endif//__TEAM_OPERATION_H__