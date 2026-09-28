#include "MiniChatPanel.h"
#include "EntityDefinition.h"
#include "MainUIModule.h"
#include "ModuleData.h"
#include "ChatModule.h"

#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPRichText.h"

#include "scene/panel/ChatPanel.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/LayoutData.h"
#include "userdata/UserData.h"
#include "userdata/StaticData.h"

#include "script/LuaWrapper.h"

#include "utils/StringUtils.h"


/////MiniChatPanel/////////////////////////////////////////////////////
MiniChatPanel::MiniChatPanel()
	:mChatContainer(NULL)
	,mChatList(NULL)
	,mCurrentChat(NULL)
	,mChatBtn(NULL)
	,mPlayerID(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::LUA_CHANGE, this);
}

MiniChatPanel::~MiniChatPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LUA_CHANGE, this);
}

bool MiniChatPanel::init()//迷你聊天ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 0.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));
	initUI();

	return true;
}

void MiniChatPanel::initUI()
{
	mChatContainer = CCLayer::create();
	mChatContainer->setVisible(false);
	addChild(mChatContainer);

	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::MAIN_UI, "chatBoard");
	mChatContainer->addChild(board);

	const CCSize &chatSize = LayoutData::getSize(CPModuleName::MAIN_UI, "miniChat");
	mChatList = CPItemComponents::create(chatSize, new CPLayoutList());
	mChatList->setClickHandler(this, callfunc_selector(MiniChatPanel::openChat));
	mChatList->setClickSensitive(true);
	mChatList->setPosition(board->getPosition());
	mChatContainer->addChild(mChatList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::MAIN_UI, "miniChatScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mChatList->setScrollbar(scrollBar);

	// chat button
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	mChatBtn = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, "openChat");
	mChatBtn->setTarget(this, menu_selector(MiniChatPanel::onChat));
	menu->addChild(mChatBtn);
}

void MiniChatPanel::buildChatMsg()
{
	const CCSize &chatSize = LayoutData::getSize(CPModuleName::MAIN_UI, "miniChat");
	const int fontSize = LayoutData::getInt(CPModuleName::CHAT, "chatFontSize");
	const std::string &fontName = LayoutData::getString(CPModuleName::CHAT, "chatFontName");

	const int buildType = CPEventHelper::getEventIntData(CPEventData::VALUE_1);
	const int chatType = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
	const std::string &content = CPEventHelper::getEventStringData(CPEventData::VALUE_3);

	const std::string &colorKey = "channel" + StringUtils::toString(chatType);
	const ccColor3B &channelColor = LayoutData::getColor3(CPModuleName::CHAT, colorKey);

	switch (buildType)
	{
	case ChatBuilder::type_start:
		{
			mCurrentChat = CPRichText::create(chatSize.width, 0);
			break;
		}
	case ChatBuilder::type_stop:
		{
			if (mCurrentChat)
			{
				mChatList->addItem(mCurrentChat);
				mChatList->setPercent(100);

				mCurrentChat = NULL;
			}
			break;
		}
	case ChatBuilder::type_label:
		{
			if (mCurrentChat)
			{
				mCurrentChat->addItem(new CPRichTextItemLabel(content, fontName, fontSize, channelColor));
			}
			break;
		}
	case ChatBuilder::type_icon:
		{
			if (mCurrentChat)
			{
				const std::string &moduleName = CPEventHelper::getEventStringData(CPEventData::VALUE_4);
				CCNode *node = LayoutData::getSprite(moduleName, content);
				if (node)
				{
					if (content.find("vip") != content.npos)
					{
						node->setScale(LayoutData::getFloat(CPModuleName::CHAT, "vipIconScale"));
					}
					mCurrentChat->addItem(new CPRichTextItemNode(node));
				}
			}
			break;
		}
	case ChatBuilder::type_player_name:
		{
			if (mCurrentChat)
			{
				if (!content.empty())
				{
					CCMenuItemFont *nameBtn = CCMenuItemFont::create(content.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "player"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	case ChatBuilder::type_player_gender:
		{
			if (mCurrentChat)
			{
				mCurrentChat->addItem(new CPRichTextItemLabel(content, fontName, fontSize, channelColor));
			}
			break;
		}
	case ChatBuilder::type_item_name:
		{
			if (mCurrentChat)
			{
				const int itemSID = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				const int playerID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
				const int itemID = CPEventHelper::getEventIntData(CPEventData::VALUE_5);
				std::string name;
				StaticData::getItemName(itemSID, name);
				name = "[" + name + "]";

				CCMenuItemFont *nameBtn = CCMenuItemFont::create(name.c_str());
				nameBtn->setFontNameObj(fontName.c_str());
				nameBtn->setFontSizeObj(fontSize);
				nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "item"));
				nameBtn->setAnchorPoint(CCPointZero);
				nameBtn->setPosition(CCPointZero);
				mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
			}
			break;
		}
	case ChatBuilder::type_scene_name:
		{
			if (mCurrentChat)
			{
				const int sceneID = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				std::string name;
				StaticData::getMapName(sceneID, name);
				if (!name.empty())
				{
					CCMenuItemFont *nameBtn = CCMenuItemFont::create(name.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "scene"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	case ChatBuilder::type_npc_name:
		{
			if (mCurrentChat)
			{
				const int npcID = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				std::string name;
				StaticData::getNPCName(npcID, name);
				if (!name.empty())
				{
					CCMenuItemFont *nameBtn = CCMenuItemFont::create(name.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "npc"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	case ChatBuilder::type_monster_name:
		{
			if (mCurrentChat)
			{
				const int monsterID = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				std::string name;
				StaticData::getMonsterName(monsterID, name);
				if (!name.empty())
				{
					CCMenuItemFont *nameBtn = CCMenuItemFont::create(name.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "monster"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	case ChatBuilder::type_activity_name:
		{
			if (mCurrentChat)
			{
				const int activityID = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				std::string name;
				StaticData::getActivityName(activityID, name);
				if (!name.empty())
				{
					CCMenuItemFont *nameBtn = CCMenuItemFont::create(name.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "activity"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	case ChatBuilder::type_position:
		{
			if (mCurrentChat)
			{
				const int px = CPEventHelper::getEventIntData(CPEventData::VALUE_3);
				const int py = CPEventHelper::getEventIntData(CPEventData::VALUE_4);
				const std::string &text = "(" + StringUtils::toString(px) + "," + StringUtils::toString(py) + ")";
				if (!text.empty())
				{
					CCMenuItemFont *nameBtn = CCMenuItemFont::create(text.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "position"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	case ChatBuilder::type_team:
		{
			if (mCurrentChat)
			{
				if (!content.empty())
				{
					const int pid = CPEventHelper::getEventIntData(CPEventData::VALUE_4);

					CCMenuItemFont *nameBtn = CCMenuItemFont::create(content.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "team"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	case ChatBuilder::type_gm:
		{
			if (mCurrentChat)
			{
				if (!content.empty())
				{
					CCMenuItemFont *nameBtn = CCMenuItemFont::create(content.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "gm"));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					mCurrentChat->addItem(new CPRichTextItemNode(nameBtn));
				}
			}
			break;
		}
	default:
		{
			CCLog(">>>Error:MiniChatPanel::buildChatMsg, unknown buildType: %d!", buildType);
			break;
		}
	}		
}

void MiniChatPanel::show()
{
	mChatContainer->stopAllActions();
	CCAction *action = CCSequence::create(
		CCDelayTime::create(LayoutData::getFloat(CPModuleName::MAIN_UI, "miniChatDelayTime")),
		CCCallFunc::create(this, callfunc_selector(MiniChatPanel::hide)),
		NULL);
	mChatContainer->runAction(action);

	mChatBtn->setVisible(false);
	mChatContainer->setVisible(true);
}

void MiniChatPanel::hide()
{
	mChatBtn->setVisible(true);
	mChatContainer->setVisible(false);
	hidePrivateChatNote(true);
}

void MiniChatPanel::showPrivateChatNote()
{
	hidePrivateChatNote(false);
	mChatBtn->setVisible(true);
	mChatBtn->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "miniChatPrivateNote1"));
	mChatBtn->runAction(CCRepeatForever::create(
		CCSequence::create(
			CCFadeOut::create(0.8f)
			, CCFadeIn::create(0.3f)
			, CCDelayTime::create(0.5f)
			, NULL)));
}

void MiniChatPanel::hidePrivateChatNote( bool clean )
{
	if (clean)
	{
		mPlayerID = 0;
		mPlayerName.clear();
	}
	mChatBtn->stopAllActions();
	mChatBtn->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "miniChatPrivateNote2"));
	mChatBtn->setVisible(!mChatContainer->isVisible());
}

void MiniChatPanel::onChat( CCObject *target )
{
	openChat(mChatContainer->numberOfRunningActions() > 0);
}

void MiniChatPanel::openChat()
{
	openChat(false);
}

void MiniChatPanel::openChat( bool isPrivate )
{
	if (isPrivate)
	{
		ChatPanelHelper::openChatWithPartner(mPlayerID, mPlayerName);
	}
	else
	{
		CPEventHelper::openPanel("ChatPanel");
	}
	hidePrivateChatNote(true);
}

void MiniChatPanel::clearIfNeed()
{
	const int cntMax = LayoutData::getInt(CPModuleName::MAIN_UI, "miniChatRecordMax");
	const int count = mChatList->getItemCount();
	if (count >= cntMax)
	{
		typedef std::vector<CCNode *> NodeVect;
		NodeVect vect;
		for (int i = 1; i < count; i++)
		{
			CCNode *child = mChatList->getItem(i);
			if (child)
			{
				child->retain();
				vect.push_back(child);
			}
		}
		mChatList->removeAllItems();

		for (int i = 0; i < (int)vect.size(); i++)
		{
			mChatList->addItem(vect[i]);
			vect[i]->release();
		}
	}
}

void MiniChatPanel::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (evtSource == "HandleMessageChatNotify")
		{
			clearIfNeed();
			show();

			int pid = 0;
			std::string name;
			MiniChatPanelHelper::addChatMsg(pid, name);

			const int chatType = ChatPanelHelper::getLastChatType();
			if (chatType == ChatDefinition::type_private && pid > 0)
			{
				mPlayerID = pid;
				mPlayerName = name;
				showPrivateChatNote();
			}
		}
	}
	else if(eventName == CPEventName::LUA_CHANGE)
	{
		if (evtSource == "cb_build_mini_chat_msg")
		{
			buildChatMsg();
		}
	}
}


//////////MiniChatPanelHelper////////////////////////////////////////////
void MiniChatPanelHelper::addChatMsg( int &partnerID, std::string &partnerName )
{
	std::string recordType = CPChatData::NORM_CHAT_LIST;
	int chatType = ChatPanelHelper::getLastChatType();
	if (chatType == ChatDefinition::type_horn)
	{
		recordType = CPChatData::HORN_CHAT_LIST;
	}
	IDVector vect;
	SubModuleData::init(CPModuleName::CHAT, recordType);
	SubModuleData::getIDVector(vect);
	if (!vect.empty())
	{
		const int chatID = vect[vect.size() - 1];
		int chatType = ChatDefinition::type_nearby;
		int pid = 0;
		std::string playerName;
		int gender = UserData::SEX_MALE;
		int vipLevel = 0;
		std::string chatText;
		SubModuleData::init(CPModuleName::CHAT, recordType);
		SubModuleData::getInt(chatID, CPChatData::CHAT_TYPE, chatType);
		SubModuleData::getInt(chatID, CPChatData::PID, pid);
		SubModuleData::getString(chatID, CPChatData::PLAYER_NAME, playerName);
		SubModuleData::getInt(chatID, CPChatData::GENDER, gender);
		SubModuleData::getInt(chatID, CPChatData::VIP_LEVEL, vipLevel);
		SubModuleData::getString(chatID, CPChatData::CHAT_TEXT, chatText);
		addChatMsg(chatType, pid, playerName, gender, vipLevel, chatText);
		partnerID = pid;
		partnerName = playerName;
	}
}

void MiniChatPanelHelper::addChatMsg( int chatType, int pid, const std::string &playerName, int gender, int vipLevel, const std::string &chatText )
{
	std::string name = playerName;
	std::string text = chatText;
	Lua::instance()->push(chatType);
	Lua::instance()->push(pid);
	Lua::instance()->push_utf8(name);
	Lua::instance()->push(gender);
	Lua::instance()->push(vipLevel);
	Lua::instance()->push_utf8(text);
	Lua::instance()->call("cb_build_mini_chat_msg", 6, 0);
}
