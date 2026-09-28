#ifndef __GUILD_PANEL_H__
#define __GUILD_PANEL_H__

/*
功能：行会
*/

#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "MsgQuest.h"

#include "GuildInfoPanel.h"
#include "GuildMemberPanel.h"
#include "GuildCombatPanel.h"
#include "GuildBrowsePanel.h"
#include "PopPullDownPanel.h"
#include "event/IEventListener.h"

USING_NS_CC_EXT;

enum Button_TAG
	{
		TAG_NULL=0,
		TAG_GUILDINFO,
		TAG_GUILDCOMBAT,
		TAG_GUILDMEMBER,
		TAG_GUILDBROWSE,
	};

class GuildPanel : public BasePanel, public IEventListener//, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	GuildPanel();
	~GuildPanel();
	virtual bool init(const char* filename);
	static GuildPanel* create();
	virtual void onEnter();
	virtual void onExit();
	void onCPEvent(const std::string &eventName);
public:
	void selectPanel(int tag,bool guildLimit=true);
protected:
	void updateSwitchButtons(int tag);
	void MenuCallBack(CCObject* pSender);
	
protected:
	GeneralMenu* m_pMainMenu;
	int m_iCurrentType;
	PopPullDownTable* m_pTipTable;
	CCNode* m_showPanel;
};
#endif//__GUILD_PANEL_H__