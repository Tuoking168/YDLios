#include "CommandPanel.h"
#include "MsgTest.h"
#include "MsgScene.h"
#include "MsgPlayer.h"
#include "MsgItem.h"
#include "MsgPet.h"
#include "MsgGuild.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "scene/LoginHelper.h"
#include "scene/panel/shop/NpcShopComp.h"
#include "scene/PanelFactory.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/netdata/IGhostVisitor.h"

#include "network/HandleMessage.h"
#include "network/MsgListener.h"

#include "script/LuaWrapper.h"


CommandPanel::CommandPanel()
{
	CPEvtDispatcher.addEventListener(CPEventName::LUA_CHANGE, this);
}

CommandPanel::~CommandPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LUA_CHANGE, this);
}

CommandPanel* CommandPanel::create()
{
	CommandPanel* pPanel = new CommandPanel();
	if(pPanel && pPanel->init())
	{
		CCLog("Successfully create CommandPanel!");
		pPanel->autorelease();

		return pPanel;
	}
	else
	{
		CCLog("Failed to create commond panel!!");
	}
	return NULL;
}

bool CommandPanel::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	this->setContentSize(CCSizeMake(200,50));

	m_pInputTextField = TextField::create(200,30,kCCTextAlignmentLeft,"ËÎÌו",20,ccWHITE);
	m_pInputTextField->setPosition(CCPointZero);
	m_pInputTextField->setAnchorPoint(CCPointZero);
	m_pInputTextField->setIsShowBoard(true);
	addChild(m_pInputTextField);

	CCMenuItemFont* ok =  CCMenuItemFont::create("OK",this,menu_selector(CommandPanel::menuCallback));

	CCMenu* menu = CCMenu::create(ok,NULL);
	menu->setPosition(ccp(120, 0));
	addChild(menu);

	return true; 
}

void CommandPanel::menuCallback( CCObject* pSender )
{
	if(strlen(m_pInputTextField->getText())<=0)
	{
		CCLOG("null cmd input");
		return;
	}

	sendCmd(m_pInputTextField->getText());
	readCmd(m_pInputTextField->getText());
}

void CommandPanel::sendCmd( const std::string &cmd )
{
	MsgGMCommand* command = new MsgGMCommand;
	command->cmd = cmd;
	HandleMessage::sendMessage(command);
}

void CommandPanel::readCmd( const std::string &cmd )
{
	const std::string &openCmdHead = "o ";
	const std::string &loadCmdHead0 = "load";
	const std::string &loadCmdHead1 = "load ";
	const std::string &whoCmd = "who";
	const std::string &dumpCmt = "dump";

	if (cmd.find(openCmdHead) != cmd.npos)
	{
		typedef std::map<std::string, std::string> PanelNameMap;
		static PanelNameMap nameMap;
		if (nameMap.empty())
		{
			nameMap["cb"] = "ConvoyBeautyPanel";
			nameMap["arena"] = "ArenaPanel";
			nameMap["chg"] = "EmigratedPanel";
			nameMap["xb"] = "TreasureHuntPanel";
		}

		const std::string &key = cmd.substr(openCmdHead.size());
		PanelNameMap::iterator it = nameMap.find(key);
		if (it != nameMap.end())
		{
			CCNode *panel = PanelFactory::create(it->second);
			if (panel)
			{
				CCNode *parentNode = getParent();
				parentNode->addChild(panel);
			}
		}
	}
	else if (cmd == loadCmdHead0 ||
		cmd.find(loadCmdHead1) != cmd.npos)
	{
		std::string key;
		if (cmd != loadCmdHead0)
		{
			key = cmd.substr(loadCmdHead1.size());
		}

		if (key.empty())
		{
			key = "test";
		}
		key = "script/" + key;
		Lua::instance()->push(key);
		Lua::instance()->call("reload_script_data", 1, 0);
	}
	else if (cmd == whoCmd)
	{
		GhostManager* pGhostManager = GameData::getGhostManager();
		if (!pGhostManager) return;
		WhoGhostVisitor visitor;
		pGhostManager->forEach(visitor);
	}
	else if (cmd == dumpCmt)
	{
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	}
}

void CommandPanel::onCPEvent( const std::string &eventName )
{
	if (eventName == CPEventName::LUA_CHANGE)
	{
		const std::string &source = CPEventHelper::getEventSource();
		const std::string &target = CPEventHelper::getEventTarget();
		if (source == "send_cmd" &&
			target == "CommandPanel")
		{
			const std::string &cmd = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
			if (!cmd.empty())
			{
				sendCmd(cmd);
			}
		}
	}
}
