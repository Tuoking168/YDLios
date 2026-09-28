#include "ChatPanel.h"
#include "ModuleData.h"
#include "ChatModule.h"
#include "MsgPlayer.h"
#include "MsgTest.h"
#include "MsgItem.h"
#include "MsgGuild.h"
#include "EntityDefinition.h"
#include "PlatformDefinition.h"

#include "scene/SceneHelper.h"
#include "scene/panel/SpecialBagPanel.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/social/SocialHelper.h"

#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "controls/CPChecker.h"
#include "controls/CPCheckBox.h"
#include "controls/CPRichText.h"
#include "controls/CPUpdater.h"
#include "controls/CPComboBox.h"

#include "ext/CCActionDestroy.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/LayoutData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"
#include "userdata/GameData.h"
#include "userdata/StaticData.h"
#include "userdata/teamdata/TeamMsgSender.h"

#include "script/LuaWrapper.h"

#include "logic/platform/IPlatform.h"

#include "network/HandleMessage.h"

#include "utils/StringUtils.h"


#define ITEM_SHOW_PANEL 998


namespace ChatFilter
{
	enum
	{
		index_begin = 0,

		index_all = 0,
		index_world = 1,
		index_nearby = 2,
		index_group = 3,
		index_guild = 4,
		index_private = 5,

		index_max,
	};
}

namespace ChatChannel
{
	enum
	{
		c_system = 1,
		c_world = 2,
		c_nearby = 3,
		c_group = 4,
		c_guild = 5,
		c_private = 6,
		c_horn = 7,
		c_gm = 8,

		c_max,
	};
}

namespace ChatState
{
	enum
	{
		horn_ready,
		horn_loading,
	};

	enum
	{
		norm_ready,
		norm_loading,
	};
}

static bool hasChannel( int channelID )
{
	switch (channelID)
	{
	case ChatChannel::c_group:
		return (HeroData::getProp(Entity::attr_team_id) > 0);
	case ChatChannel::c_guild:
		return (HeroData::getProp(Entity::attr_guild_id) > 0);
	case ChatChannel::c_gm:
		return false;
	}
	return true;
}

//////////ChatPanel//////////////////////////////////////////////////
ChatPanel::ChatPanel()
	:mInputText(NULL)
	,mChecker(NULL)
	,mFilter(NULL)
	,mHornChats(NULL)
	,mNormChats(NULL)
	,mCurrentChat(NULL)
	,mChannelBox(NULL)
	,mCurrentFilter(ChatFilter::index_all)
	,mHornChatState(ChatState::horn_ready)
	,mNormChatState(ChatState::norm_ready)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::LUA_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
	init();
}

ChatPanel::~ChatPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LUA_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
}

ChatPanel * ChatPanel::instance()
{
	static ChatPanel panel;
	return &panel;
}

void ChatPanel::show()
{
	if (ChatPanelHelper::getChatPartnerID() > 0)
	{
		show(ChatChannel::c_private);
	}
	else
	{
		ChatPanelHelper::setToGM(false);
		show(0);
	}
}

void ChatPanel::show( int channel )
{
	rebuildFilter();
	rebuildChannel();

	if (mHornChats)
	{
		mHornChats->setPercent(100);
	}

	if (mNormChats)
	{
		mNormChats->setPercent(100);
	}

	if (ChatChannel::c_world <= channel
		&& channel < ChatChannel::c_max)
	{
		mChannelBox->setCurrentIndex(channel);
	}
	refreshInputPlaceHolder();
	setVisible(true);
}

bool ChatPanel::init()//聊天ui
{
	if (!FullScreenPanel::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	setVisible(false);

	initUI();
	rebuildFilter();
	rebuildChannel();
	refreshHorn();
	refreshNorm();
	refreshInputPlaceHolder();

	return true;
}

void ChatPanel::onExit()
{
	setVisible(false);
	CCLayer::onExit();
}

void ChatPanel::initUI()
{
	// title
	CCSprite *title = LayoutData::getSprite(CPModuleName::CHAT, "title");
	addChild(title);

	// board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::CHAT, "board");
	addChild(board);

	CCScale9Sprite *topBorder = LayoutData::getScale9Sprite(CPModuleName::CHAT, "topBorder");
	addChild(topBorder);

	CCScale9Sprite *midBorder = LayoutData::getScale9Sprite(CPModuleName::CHAT, "midBorder");
	addChild(midBorder);

	// input edit box
	mInputText = LayoutData::getEditBox(CPModuleName::CHAT, "input");
	mInputText->setTouchPriority(kCCMenuHandlerPriority);
	addChild(mInputText);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *sendBtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "send");
	sendBtn->setTarget(this, menu_selector(ChatPanel::onSend));
	menu->addChild(sendBtn);

	CCMenuItemImage *emoticonsBtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "emoticons");
	emoticonsBtn->setTarget(this, menu_selector(ChatPanel::onEmoticons));
	menu->addChild(emoticonsBtn);

	CCMenuItemImage *showItemBtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "show");
	showItemBtn->setTarget(this, menu_selector(ChatPanel::onShowItem));
	menu->addChild(showItemBtn);

	// checker
	mChecker = CPChecker::create();
	addChild(mChecker, 1);
}

void ChatPanel::rebuildFilter()
{
	if (mFilter)
	{
		mFilter->removeFromParent();
	}

	const CCSize &filterSize = LayoutData::getSize(CPModuleName::CHAT, "filter");
	const CCSize &filterItemSize = LayoutData::getSize(CPModuleName::CHAT, "filterItem");
	mFilter = CPItemComponents::create(filterSize, new CPLayoutList(filterItemSize, true));
	mFilter->setPosition(LayoutData::getPoint(CPModuleName::CHAT, "filter"));
	addChild(mFilter);

	for (int i = ChatFilter::index_begin; i < ChatFilter::index_max; i++)
	{
		const std::string &key = "filter" + StringUtils::toString(i);
		CCMenuItemImage *btn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, key);
		btn->setTarget(this, menu_selector(ChatPanel::onFilter));
		mFilter->addItem(btn);
		btn->setTag(i);
	}
	mFilter->setCurrentIndex(mCurrentFilter);
}

void ChatPanel::rebuildChannel()
{
	if (mChannelBox)
	{
		mChannelBox->removeFromParent();
	}

	mChannelBox = LayoutData::getComboBox(CPModuleName::COMMON, "normal");
	mChannelBox->setChangeHandler(this, callfuncN_selector(ChatPanel::onChannelChange));
	mChannelBox->setPosition(LayoutData::getPoint(CPModuleName::CHAT, "channel"));
	addChild(mChannelBox, 1);
	for (int i = ChatChannel::c_world; i < ChatChannel::c_max; i++)
	{
		if (hasChannel(i))
		{
			const std::string &key = "channel" + StringUtils::toString(i);
			mChannelBox->addLabelItem(LayoutData::getString(CPModuleName::CHAT, key), i);
		}
	}
}

void ChatPanel::refreshHorn()
{
	if (mHornChats)
	{
		mHornChats->removeFromParentAndCleanup(true);
	}
	const CCSize &chatSize = LayoutData::getSize(CPModuleName::CHAT, "hornChat");
	mHornChats = CPItemComponents::create(chatSize, new CPLayoutList());
	mHornChats->setPosition(LayoutData::getPoint(CPModuleName::CHAT, "hornChat"));
	addChild(mHornChats);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::CHAT, "hornScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mHornChats->setScrollbar(scrollBar);

	mHornChatState = ChatState::horn_ready;
	int listSize = 0;
	SubModuleData::init(CPModuleName::CHAT, CPChatData::HORN_CHAT_LIST);
	SubModuleData::getSize(listSize);
	if (listSize > 0)
	{
		CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(ChatPanel::addHornChatMsg));
		updater->setUpdateTimes(listSize);
		updater->setFinishHandler(this, callfunc_selector(ChatPanel::addHornChatFinish));
		mHornChats->addChild(updater);
		updater->start();

		mHornChatState = ChatState::horn_loading;
	}
}

void ChatPanel::refreshNorm()
{
	if (mNormChats)
	{
		mNormChats->removeFromParentAndCleanup(true);
	}
	const CCSize &chatSize = LayoutData::getSize(CPModuleName::CHAT, "normChat");
	mNormChats = CPItemComponents::create(chatSize, new CPLayoutList());
	mNormChats->setPosition(LayoutData::getPoint(CPModuleName::CHAT, "normChat"));
	addChild(mNormChats);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::CHAT, "normScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mNormChats->setScrollbar(scrollBar);

	mNormChatState = ChatState::norm_ready;
	int listSize = 0;
	SubModuleData::init(CPModuleName::CHAT, CPChatData::NORM_CHAT_LIST);
	SubModuleData::getSize(listSize);
	if (listSize > 0)
	{
		CPUpdater *updater = CPUpdater::create(this, cpupdater_selector(ChatPanel::addNormChatMsg));
		updater->setUpdateTimes(listSize);
		updater->setFinishHandler(this, callfunc_selector(ChatPanel::addNormChatFinish));
		mNormChats->addChild(updater);
		updater->start();

		mNormChatState = ChatState::norm_loading;
	}
}

void ChatPanel::refreshIfNeed()
{
	if (!isVisible())
	{
		const int factor = 2;
		const int lastChatType = ChatPanelHelper::getLastChatType();
		if (lastChatType != ChatDefinition::type_horn)
		{
			const int maxCnt = LayoutData::getInt(CPModuleName::CHAT, "normRecord");
			if (mNormChats
				&& mNormChats->getItemCount() > factor * maxCnt)
			{
				refreshNorm();
			}
		}
		else
		{
			const int maxCnt = LayoutData::getInt(CPModuleName::CHAT, "hornRecord");
			if (mHornChats
				&& mHornChats->getItemCount() > factor * maxCnt)
			{
				refreshHorn();
			}
		}
	}
}

void ChatPanel::refreshInputPlaceHolder()
{
	const int channel = mChannelBox->getCurrentIndex();
	std::string placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNote");
	switch (channel)
	{
	case ChatChannel::c_world:
		placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteWorld");
		break;
	case ChatChannel::c_nearby:
		placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteNearBy");
		break;
	case ChatChannel::c_group:
		if (HeroData::getProp(Entity::attr_team_id))
		{
			placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteGroup");
		}
		else
		{
			placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteNoGroup");
		}
		break;
	case ChatChannel::c_guild:
		if (HeroData::getProp(Entity::attr_guild_id))
		{
			placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteGuild");
		}
		else
		{
			placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteNoGuild");
		}
		break;
	case ChatChannel::c_private:
		{
			const int partnerPID = ChatPanelHelper::getChatPartnerID();
			const std::string &partnerName = ChatPanelHelper::getChatPartnerName();
			if (partnerPID <= 0 || partnerName.empty())
			{
				placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteWithNoPartner");
			}
			else
			{
				placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteWithPartner") + partnerName;
			}
			break;
		}
	case ChatChannel::c_horn:
		placeHorder = LayoutData::getString(CPModuleName::CHAT, "inputNoteHorn");
		break;
	}
	mInputText->setPlaceHolder(placeHorder.c_str());
}

void ChatPanel::clearChat()
{
	refreshNorm();
	refreshHorn();
}

void ChatPanel::showItemTips()
{
	ChatPanelHelper::initItemData(mShowItemData);
	ItemTooltip *itemTips = ItemTooltip::create();
	itemTips->setTooltipContent(&mShowItemData, TAG_Tips);
	itemTips->setPosition(LayoutData::getPoint(CPModuleName::CHAT, "itemTips"));
	addChild(itemTips);
}

void ChatPanel::onFilter( CCObject *target )
{
	const int filterIndex = mFilter->getCurrentIndex();
	if (filterIndex != mCurrentFilter)
	{
		mCurrentFilter = filterIndex;
		refreshNorm();
	}
}

void ChatPanel::onEmoticons( CCObject *target )
{
	EmoticonsPanel *panel = EmoticonsPanel::create();
	panel->setHandler(this, emoticons_selector(ChatPanel::onAddEmoticons));
	addChild(panel);
}

void ChatPanel::onSend( CCObject *target )
{
	const std::string &chatMsg = mInputText->getText();
	mInputText->setText("");
	if (ChatPanelHelper::testChatText(chatMsg))
	{
		int channel = mChannelBox->getCurrentIndex();
		int partnerID = 0;
		if (channel == ChatChannel::c_world)
		{
			int freeTime = 0;
			StaticData::getGlobalData("chatWorldChannelFreeTime", freeTime);
			const int passTime = time(NULL) - ActivityData::getWorldBeginTime();
			if (passTime > freeTime)
			{
				int needLevel = 0;
				StaticData::getGlobalData("chatWorldChannelLevel", needLevel);
				if (HeroData::getProp(Entity::attr_reborn) == 0
					&& HeroData::getLevel() < needLevel)
				{
					ChatPanelHelper::addSystemMsg(StringUtils::toString(needLevel) + LayoutData::getString(CPModuleName::CHAT, "lvlNotEnough"));
					return;
				}
			}
		}
		else if (channel == ChatChannel::c_private)
		{
			partnerID = ChatPanelHelper::getChatPartnerID();
			if (partnerID <= 0)
			{
				ChatPanelHelper::addSystemMsg(LayoutData::getString(CPModuleName::CHAT, "noPartner"));
				return;
			}

			if (ChatPanelHelper::isToGM())
			{
				channel = ChatChannel::c_gm;
			}
		}
		mChecker->start();
		ChatPanelHelper::sendChatRequest(channel, partnerID, chatMsg);
	}
}

void ChatPanel::onShowItem( CCObject *target )
{
	CCNode *bagPanel = getChildByTag(ITEM_SHOW_PANEL);
	if (bagPanel)
	{
		bagPanel->removeFromParent();
		bagPanel = NULL;
		return;
	}

	bagPanel = SpecialBagPanel::create(Bag_Type_Chart);
	bagPanel->setAnchorPoint(CCPointZero);
	bagPanel->setPosition(SystemData::getLayoutPoint("activity_spider_bkg_right"));
	addChild(bagPanel, 0, ITEM_SHOW_PANEL);
}

void ChatPanel::onPlayer( CCObject *target )
{
	CCMenuItemFont *nameBtn = dynamic_cast<CCMenuItemFont *>(target);
	if (nameBtn)
	{
		const int pid = nameBtn->getTag();
		if (pid != HeroData::getPID())
		{
			CCArray *children = nameBtn->getChildren();
			if (children && children->count() > 0)
			{
				CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>(children->objectAtIndex(0));
				if (nameLabel)
				{
					PlayerOperationPanel *panel = PlayerOperationPanel::create();
					panel->setPlayerID(pid);
					panel->setPlayerName(nameLabel->getString());
					addChild(panel);
				}
			}	
		}
	}
}

void ChatPanel::onItem( CCObject *target )
{
	CCMenuItemFontEx *item = dynamic_cast<CCMenuItemFontEx *>(target);
	if (item)
	{
		ChatPanelHelper::clearItemData();
		mShowItemData = UserItem();
		mShowItemData.sid = item->getDataX();
		const int pid = item->getDataY();
		const int iid = item->getDataZ();
		if (pid > 0 && iid > 0)
		{
			mChecker->start();
			ChatPanelHelper::itemInfoRequest(pid, iid);
		}
		else
		{
			showItemTips();
		}
	}
}

void ChatPanel::onScene( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		CCLog(">>>scene id: %d", node->getTag());
	}
}

void ChatPanel::onNPC( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int npcID = node->getTag();
		if (npcID > 0)
		{
			SceneHelper::autoMoveToNPC(npcID);
		}
	}
}

void ChatPanel::onMonster( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		CCLog(">>>monster id: %d", node->getTag());
	}
}

void ChatPanel::onActivity( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		CCLog(">>>activity id: %d", node->getTag());
	}
}

void ChatPanel::onPosition( CCObject *target )
{
	//
}

void ChatPanel::onTeam( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int pid = node->getTag();
		if (pid > 0	&& pid != HeroData::getPID())
		{
			mChecker->start();
			TeamMsgSender::Join(pid);
		}
	}
}

void ChatPanel::onGM( CCObject *target )
{
	CCMenuItemFont *nameBtn = dynamic_cast<CCMenuItemFont *>(target);
	if (nameBtn)
	{
		const int gmID = nameBtn->getTag();
		if (gmID > 0)
		{
			CCArray *children = nameBtn->getChildren();
			if (children && children->count() > 0)
			{
				CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>(children->objectAtIndex(0));
				if (nameLabel)
				{
					ChatPanelHelper::openChatWithPartner(gmID, nameLabel->getString(), true);
				}
			}	
		}
	}
}

void ChatPanel::onChannelChange( CCNode *box )
{
	refreshInputPlaceHolder();
}

void ChatPanel::onAddEmoticons( int eID )
{
	std::string text = mInputText->getText();
	text += "[emoticons:" + StringUtils::toString(eID) + "]";
	mInputText->setText(text.c_str());
}

bool ChatPanel::needShow( int chatType )
{
	if (mCurrentFilter == ChatFilter::index_all)
	{
		return true;
	}

	const int index = ChatPanelHelper::getIndexByType(chatType);
	return (index == mCurrentFilter);
}

void ChatPanel::buildChatMsg()
{
	const CCSize &chatSize = LayoutData::getSize(CPModuleName::CHAT, "normChat");
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
				CPItemComponents *chatCompnents = NULL;
				if (chatType != ChatDefinition::type_horn)
				{
					chatCompnents = mNormChats;
				}
				else
				{
					chatCompnents = mHornChats;
				}

				int percent = chatCompnents->getPercent();
				chatCompnents->addItem(mCurrentChat);
				if (percent == 100)
				{
					chatCompnents->setPercent(100);
				}

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
					const int pid = CPEventHelper::getEventIntData(CPEventData::VALUE_4);

					CCMenuItemFont *nameBtn = CCMenuItemFont::create(content.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "player"));
					nameBtn->setTarget(this, menu_selector(ChatPanel::onPlayer));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn, 0, pid);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
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

				CCMenuItemFontEx *nameBtn = CCMenuItemFontEx::create(name.c_str());
				nameBtn->setExData(itemSID, playerID, itemID);
				nameBtn->setFontNameObj(fontName.c_str());
				nameBtn->setFontSizeObj(fontSize);
				nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "item"));
				nameBtn->setTarget(this, menu_selector(ChatPanel::onItem));
				nameBtn->setAnchorPoint(CCPointZero);
				nameBtn->setPosition(CCPointZero);
				CCMenu *menu = CCMenu::create();
				menu->setPosition(CCPointZero);
				menu->setContentSize(nameBtn->getContentSize());
				menu->addChild(nameBtn);
				mCurrentChat->addItem(new CPRichTextItemNode(menu));
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
					nameBtn->setTarget(this, menu_selector(ChatPanel::onScene));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn, 0, sceneID);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
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
					nameBtn->setTarget(this, menu_selector(ChatPanel::onNPC));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn, 0, npcID);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
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
					nameBtn->setTarget(this, menu_selector(ChatPanel::onMonster));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn, 0, monsterID);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
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
					nameBtn->setTarget(this, menu_selector(ChatPanel::onActivity));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn, 0, activityID);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
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
					CCMenuItemFontEx *nameBtn = CCMenuItemFontEx::create(text.c_str());
					nameBtn->setExData(px, py, 0);
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "position"));
					nameBtn->setTarget(this, menu_selector(ChatPanel::onPosition));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
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
					nameBtn->setTarget(this, menu_selector(ChatPanel::onTeam));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn, 0, pid);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
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
					const int gmID = CPEventHelper::getEventIntData(CPEventData::VALUE_4);

					CCMenuItemFont *nameBtn = CCMenuItemFont::create(content.c_str());
					nameBtn->setFontNameObj(fontName.c_str());
					nameBtn->setFontSizeObj(fontSize);
					nameBtn->setColor(LayoutData::getColor3(CPModuleName::CHAT, "gm"));
					nameBtn->setTarget(this, menu_selector(ChatPanel::onGM));
					nameBtn->setAnchorPoint(CCPointZero);
					nameBtn->setPosition(CCPointZero);
					CCMenu *menu = CCMenu::create();
					menu->setPosition(CCPointZero);
					menu->setContentSize(nameBtn->getContentSize());
					menu->addChild(nameBtn, 0, gmID);
					mCurrentChat->addItem(new CPRichTextItemNode(menu));
				}
			}
			break;
		}
	default:
		{
			CCLog(">>>Error:ChatPanel::buildChatMsg, unknown buildType: %d!", buildType);
			break;
		}
	}		
}

void ChatPanel::addHornChatMsg( int index )
{
	IDVector vect;
	SubModuleData::init(CPModuleName::CHAT, CPChatData::HORN_CHAT_LIST);
	SubModuleData::getIDVector(vect);
	if (0 <= index && index < (int)vect.size())
	{
		ChatPanelHelper::addChatMsg(CPChatData::HORN_CHAT_LIST, vect[index]);
	}
}

void ChatPanel::addHornChatFinish()
{
	mHornChatState = ChatState::horn_ready;
}

void ChatPanel::addNormChatMsg( int index )
{
	IDVector vect;
	SubModuleData::init(CPModuleName::CHAT, CPChatData::NORM_CHAT_LIST);
	SubModuleData::getIDVector(vect);
	if (0 <= index && index < (int)vect.size())
	{
		if (needShow(ChatPanelHelper::getTypeByNormChatID(vect[index])))
		{
			ChatPanelHelper::addChatMsg(CPChatData::NORM_CHAT_LIST, vect[index]);
		}
	}
}

void ChatPanel::addNormChatFinish()
{
	mNormChatState = ChatState::norm_ready;
}

void ChatPanel::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (evtSource == "HandleMessageChatNotify")
		{
			if (mHornChatState == ChatState::horn_ready &&
				mNormChatState == ChatState::norm_ready)
			{
				const int lastChatType = ChatPanelHelper::getLastChatType();
				if (needShow(lastChatType))
				{
					ChatPanelHelper::addChatMsg();
					refreshIfNeed();
				}
			}
		}
	}
	else if (eventName == CPEventName::MSG_FINISH)
	{
		if (evtSource == "HandleMessageChatResponse"
			|| evtSource == "HandleMessageTeamJoinResponse")
		{
			mChecker->stop();
		}
		else if (evtSource == "HandleMessageItemInfoDataGetResponse")
		{
			mChecker->stop();
			if (CPEventHelper::isRequestSuccess()
				&& isVisible())
			{
				showItemTips();
			}
		}
	}
	else if(eventName == CPEventName::LUA_CHANGE)
	{
		if (evtSource == "cb_build_chat_msg")
		{
			buildChatMsg();
		}
	}
	else if (eventName == CPEventName::UI_NOTIFY)
	{
		if (evtSource == "ItemTooltip|ShowItem")
		{
			const int iid = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			UserItemData *userItems = GameData::getUserItemData();
			if (userItems)
			{
				UserItem *item = userItems->getItemByIid(iid);
				if (item)
				{
					std::string text = mInputText->getText();
					text += "[item:";
					text += StringUtils::toString(item->sid);
					text += "," + StringUtils::toString(HeroData::getPID());
					text += "," + StringUtils::toString(item->iid);
					text += "]";
					mInputText->setText(text.c_str());
				}
			}
		}
		else if (evtSource == "ChatPanelHelper::clearChat")
		{
			clearChat();
		}
	}
}

///////////PlayerOperationPanel////////////////////////////////////////
PlayerOperationPanel::PlayerOperationPanel()
	:mPlayerID(0)
	,mOpened(false)
{

}

PlayerOperationPanel::~PlayerOperationPanel()
{

}

void PlayerOperationPanel::setPlayerID( int pid )
{
	mPlayerID = pid;
	if (mPlayerID < 0)
	{
		mPlayerID = -mPlayerID;
	}
}

void PlayerOperationPanel::setPlayerName( const std::string &name )
{
	mPlayerName = name;
}

void PlayerOperationPanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool PlayerOperationPanel::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pEvent);
	const CCRect &rect = CCRectMake(0, 0, getContentSize().width, getContentSize().height);
	const CCPoint &pt = convertTouchToNodeSpace(pTouch);
	if (rect.containsPoint(pt))
	{
		return false;
	}
	close();
	return true;
}

bool PlayerOperationPanel::init()//聊天点击名字ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	

	setTouchEnabled(true);

	initUI();
	setPosition(LayoutData::getPoint(CPModuleName::CHAT, "operation"));

	return true;
}

void PlayerOperationPanel::initUI()
{
	// board
	CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::CHAT, "operationBoard");
	board->setAnchorPoint(CCPointZero);
	addChild(board);
	setContentSize(board->getContentSize());

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *lookBtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "opLook");
	lookBtn->setTarget(this, menu_selector(PlayerOperationPanel::onLook));
	menu->addChild(lookBtn);

	CCMenuItemImage *friendBtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "opFriend");
	friendBtn->setTarget(this, menu_selector(PlayerOperationPanel::onFriend));
	menu->addChild(friendBtn);

	CCMenuItemImage *teamBtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "opTeam");
	teamBtn->setTarget(this, menu_selector(PlayerOperationPanel::onTeam));
	menu->addChild(teamBtn);

	CCMenuItemImage *guildBtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "opGuild");
	guildBtn->setTarget(this, menu_selector(PlayerOperationPanel::onGuild));
	menu->addChild(guildBtn);

	CCMenuItemImage *privatebtn = LayoutData::getMenuItemLabelImage(CPModuleName::CHAT, "opPrivate");
	privatebtn->setTarget(this, menu_selector(PlayerOperationPanel::onPrivate));
	menu->addChild(privatebtn);
}

void PlayerOperationPanel::onEnter()
{
	if (!mOpened)
	{
		CCLayer::onEnter();
		mOpened = true;
		open();
	}
	else
	{
		removeFromParentAndCleanup(true);
	}
}

void PlayerOperationPanel::open()//聊天点击名字弹出ui
{
	//setPositionX(SystemData::size_x);
	// 用配置文件的位置
    CCPoint configPos = LayoutData::getPoint(CPModuleName::CHAT, "operation");
	CCMoveBy *mb1 = CCMoveBy::create(0.2f, ccp(-getContentSize().width - 10, 0));
	CCMoveBy *mb2 = CCMoveBy::create(0.2f, ccp(15, 0));
	CCMoveBy *mb3 = CCMoveBy::create(0.2f, ccp(-5, 0));
	CCAction *action = CCSequence::create(mb1, mb2, mb3, NULL);
	runAction(action);
}

void PlayerOperationPanel::close()
{
	CCMoveBy *mb1 = CCMoveBy::create(0.1f, ccp(5, 0));
	CCMoveBy *mb2 = CCMoveBy::create(0.1f, ccp(-15, 0));
	CCMoveBy *mb3 = CCMoveBy::create(0.1f, ccp(getContentSize().width + 10, 0));
	CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
	CCAction *action = CCSequence::create(mb1, mb2, mb3, rmv, NULL);
	runAction(action);
}

void PlayerOperationPanel::onLook( CCObject *target )
{
	MsgGetOtherPlayerDataRequest* msg=new MsgGetOtherPlayerDataRequest;
	msg->pid = mPlayerID;
	HandleMessage::sendMessage(msg);
	close();
}

void PlayerOperationPanel::onFriend( CCObject *target )
{
	SocialHelper::requestAddFriend(mPlayerID, mPlayerName);
	close();
}

void PlayerOperationPanel::onTeam( CCObject *target )
{
	TeamMsgSender::Invite(mPlayerID);
	close();
}

void PlayerOperationPanel::onGuild( CCObject *target )
{
	MsgGuildInviteRequestEx *msg = new MsgGuildInviteRequestEx;
	msg->pid = mPlayerID;
	HandleMessage::sendMessage(msg);
	close();
}

void PlayerOperationPanel::onPrivate( CCObject *target )
{
	ChatPanelHelper::openChatWithPartner(mPlayerID, mPlayerName);
	close();
}

///////////EmoticonPanel//////////////////////////////////////////////
EmoticonsPanel::EmoticonsPanel()
	:mHandler(NULL)
	,mHandleFunc(NULL)
	,mBoard(NULL)
	,mOpened(false)
{

}

EmoticonsPanel::~EmoticonsPanel()
{

}

void EmoticonsPanel::setHandler( CCObject *handler, SEL_Emoticons func )
{
	mHandler = handler;
	mHandleFunc = func;
}

void EmoticonsPanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool EmoticonsPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CC_UNUSED_PARAM(pEvent);
	const CCRect &rect = CCRectMake(0, 0, mBoard->getContentSize().width, mBoard->getContentSize().height);
	const CCPoint &pt = mBoard->convertTouchToNodeSpace(pTouch);
	if (rect.containsPoint(pt))
	{
		return false;
	}
	close();
	return true;
}

bool EmoticonsPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	setTouchEnabled(true);

	initUI();

	return true;
}

void EmoticonsPanel::onEnter()
{
	if (!mOpened)
	{
		CCLayer::onEnter();
		mOpened = true;
		open();
	}
	else
	{
		removeFromParentAndCleanup(true);
	}
}

void EmoticonsPanel::initUI()
{
	// board
	mBoard = LayoutData::getScale9Sprite(CPModuleName::CHAT, "emoticonsBoard");
	addChild(mBoard);

	// emoticons
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	mBoard->addChild(menu);

	const CCPoint &firstPt = LayoutData::getPoint(CPModuleName::CHAT, "emoticonsFirst");
	const CCSize &size = LayoutData::getSize(CPModuleName::CHAT, "emoticons");
	const int perLine = LayoutData::getInt(CPModuleName::CHAT, "emoticonsPerLine");
	const int cnt = LayoutData::getInt(CPModuleName::CHAT, "emoticonsCnt");
	for (int i = 0; i < cnt; i++)
	{
		const int ox = size.width * (i%perLine);
		const int oy = -size.height * (i/perLine);
		CCMenuItem *btn = CCMenuItem::create();
		btn->setTarget(this, menu_selector(EmoticonsPanel::onClick));
		btn->setPosition(ccp(firstPt.x + ox, firstPt.y + oy));
		menu->addChild(btn, 0, i + 1);

		const std::string &key = "emoticons" + StringUtils::toString(i + 1);
		CCSprite *emoticons = LayoutData::getSprite(CPModuleName::CHAT, key);
		emoticons->setAnchorPoint(CCPointZero);
		btn->addChild(emoticons);

		btn->setContentSize(emoticons->getContentSize());
	}
}

void EmoticonsPanel::open()
{
	setAnchorPoint(LayoutData::getPoint(CPModuleName::CHAT, "emoticonsAnchor"));
	setScale(0);
	CCScaleTo *st = CCScaleTo::create(0.2f, 1.0f);
	runAction(st);
}

void EmoticonsPanel::close()
{
	CCScaleTo *st = CCScaleTo::create(0.2f, 0);
	CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
	CCAction *action = CCSequence::create(st, rmv, NULL);
	runAction(action);
}

void EmoticonsPanel::onClick( CCObject *target )
{
	if (mHandler && mHandleFunc)
	{
		CCNode *node = dynamic_cast<CCNode *>(target);
		if (node)
		{
			(mHandler->*mHandleFunc)(node->getTag());
		}
	}
	close();
}

//////////CCMenuItemFontEx//////////////////////////////////////
CCMenuItemFontEx::CCMenuItemFontEx()
	:mDataX(0)
	,mDataY(0)
	,mDataZ(0)
{

}

CCMenuItemFontEx::~CCMenuItemFontEx()
{

}

CCMenuItemFontEx * CCMenuItemFontEx::create( const std::string &text )
{
	CCMenuItemFontEx *ret = new CCMenuItemFontEx;
	if (ret && ret->initWithString(text.c_str(), NULL, NULL))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return ret;
}

void CCMenuItemFontEx::setExData( int dataX, int dataY, int dataZ )
{
	mDataX = dataX;
	mDataY = dataY;
	mDataZ = dataZ;
}

int CCMenuItemFontEx::getDataX()
{
	return mDataX;
}

int CCMenuItemFontEx::getDataY()
{
	return mDataY;
}

int CCMenuItemFontEx::getDataZ()
{
	return mDataZ;
}

////////ChatPanelHelper////////////////////////////////////////////////
void ChatPanelHelper::openChatWithPartner( int partnerID, const std::string &partnerName )
{
	openChatWithPartner(partnerID, partnerName, false);
}

void ChatPanelHelper::openChatWithPartner( int partnerID, const std::string &partnerName, bool toGM )
{
	setToGM(toGM);
	ModuleData::setInt(CPModuleName::CHAT, CPChatData::CHAT_PARTNER_PID, partnerID);
	ModuleData::setString(CPModuleName::CHAT, CPChatData::CHAT_PARTNER_NAME, partnerName);
	CPEventHelper::openPanel("ChatPanel", ChatDefinition::type_private, 0, 0, 0);
}

int ChatPanelHelper::getChatPartnerID()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::CHAT, CPChatData::CHAT_PARTNER_PID, ret);
	return ret;
}

std::string ChatPanelHelper::getChatPartnerName()
{
	std::string ret;
	ModuleData::getString(CPModuleName::CHAT, CPChatData::CHAT_PARTNER_NAME, ret);
	return ret;
}

void ChatPanelHelper::clearChat()
{
	ModuleData::clearModule(CPModuleName::CHAT);
	CPEventHelper::dispatcher(CPEventName::UI_NOTIFY, "ChatPanelHelper::clearChat", "");
}

int ChatPanelHelper::getTypeByNormChatID( int chatID )
{
	int chatType = ChatDefinition::type_nearby;
	SubModuleData::init(CPModuleName::CHAT, CPChatData::NORM_CHAT_LIST);
	SubModuleData::getInt(chatID, CPChatData::CHAT_TYPE, chatType);
	return chatType;
}

int ChatPanelHelper::getLastChatType()
{
	int chatType = ChatDefinition::type_nearby;
	ModuleData::getInt(CPModuleName::CHAT, CPChatData::LAST_CHAT_TYPE, chatType);
	return chatType;
}

int ChatPanelHelper::getIndexByType( int chatType )
{
	switch (chatType)
	{
	case ChatDefinition::type_world:
		return ChatFilter::index_world;
	case ChatDefinition::type_nearby:
		return ChatFilter::index_nearby;
	case ChatDefinition::type_group:
		return ChatFilter::index_group;
	case ChatDefinition::type_guild:
		return ChatFilter::index_guild;
	case ChatDefinition::type_private:
		return ChatFilter::index_private;
	}
	return -1;
}

void ChatPanelHelper::addChatMsg( int chatType, int pid, const std::string &playerName, int gender, int vipLevel, const std::string &chatText )
{
	std::string name = playerName;
	std::string text = chatText;
	Lua::instance()->push(chatType);
	Lua::instance()->push(pid);
	Lua::instance()->push_utf8(name);
	Lua::instance()->push(gender);
	Lua::instance()->push(vipLevel);
	Lua::instance()->push_utf8(text);
	Lua::instance()->call("cb_build_chat_msg", 6, 0);
}

void ChatPanelHelper::addChatMsg( const std::string &recordType, int chatID )
{
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
}

void ChatPanelHelper::addChatMsg()
{
	std::string recordType = CPChatData::NORM_CHAT_LIST;
	int chatType = getLastChatType();
	if (chatType == ChatDefinition::type_horn)
	{
		recordType = CPChatData::HORN_CHAT_LIST;
	}
	IDVector vect;
	SubModuleData::init(CPModuleName::CHAT, recordType);
	SubModuleData::getIDVector(vect);
	if (!vect.empty())
	{
		addChatMsg(recordType, vect[vect.size() - 1]);
	}
}

void ChatPanelHelper::addSystemMsg( const std::string &chatText )
{
	// last chat type
	ModuleData::setInt(CPModuleName::CHAT, CPChatData::LAST_CHAT_TYPE, ChatDefinition::type_system);

	// chat record list
	int lastChatID = 0;
	ModuleData::getInt(CPModuleName::CHAT, CPChatData::LAST_CHAT_ID, lastChatID);
	lastChatID++;
	SubModuleData::init(CPModuleName::CHAT, CPChatData::NORM_CHAT_LIST);
	SubModuleData::setInt(lastChatID, CPChatData::CHAT_TYPE, ChatDefinition::type_system);
	SubModuleData::setInt(lastChatID, CPChatData::PID, 0);
	SubModuleData::setString(lastChatID, CPChatData::PLAYER_NAME, "");
	SubModuleData::setInt(lastChatID, CPChatData::GENDER, 0);
	SubModuleData::setInt(lastChatID, CPChatData::VIP_LEVEL, 0);
	SubModuleData::setString(lastChatID, CPChatData::CHAT_TEXT, chatText);
	ModuleData::setInt(CPModuleName::CHAT, CPChatData::LAST_CHAT_ID, lastChatID);

	IDVector vect;
	SubModuleData::getIDVector(vect);
	const int maxCnt = LayoutData::getInt(CPModuleName::CHAT, "normRecord");
	if ((int)vect.size() > maxCnt && maxCnt > 0)
	{
		SubModuleData::clearData(vect[0]);
	}

	//
	addChatMsg();
}

bool ChatPanelHelper::testChatText( const std::string &chatText )
{
	if (chatText.empty())
	{
		CPEventHelper::uiNotify("ChatPanelHelper::testChatText", "", Error::PlayerSpeakNothing);
		return false;
	}

	std::string temp;
	if (!StringUtils::filterString(chatText, temp))
	{
		CPEventHelper::uiNotify("LoginHelper", "", Error::Contains_Sensitive_Words);
		return false;
	}

	//
	int sendItemTest = 0;
	CPLua->push_utf8(chatText);
	CPLua->call("cb_test_chat_send_item", 1, 1);
	CPLua->pop(sendItemTest);
	if (sendItemTest != 0)
	{
		CPEventHelper::uiNotify("ChatPanelHelper::testChatText", "", Error::InvalidItem);
		return false;
	}
	return true;
}

void ChatPanelHelper::clearItemData()
{
	SubModuleData::init(CPModuleName::CHAT, CPChatData::CHAT_ITEM_DATA_LIST);
	SubModuleData::clearAll();
}

void ChatPanelHelper::initItemData( UserItem &itemData )
{
	SubModuleData::init(CPModuleName::CHAT, CPChatData::CHAT_ITEM_DATA_LIST);
	IDVector vect;
	SubModuleData::getIDVector(vect);
	int data = 0;
	for (int i = 0; i < (int)vect.size(); i++)
	{
		if (vect[i] < ItemEquip::Item_Max)
		{
			data = 0;
			SubModuleData::getInt(vect[i], CPChatData::CHAT_ITEM_DATA, data);
			itemData.data[vect[i]] = data;
		}
	}
}

void ChatPanelHelper::sendChatRequest( int chatType, int partnerPid, const std::string &chatText )
{
	MsgChatRequest *msg = new MsgChatRequest;
	msg->chatType = chatType;
	msg->partnerPid = partnerPid;
	msg->chatText = chatText;
	HandleMessage::sendMessage(msg);

	// for test
	if (CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) == ChannelID::test)
	{
		MsgGMCommand *command = new MsgGMCommand;
		command->cmd = chatText;
		HandleMessage::sendMessage(command);
	}
}

void ChatPanelHelper::itemInfoRequest( int pid, int iid )
{
	SubModuleData::init(CPModuleName::CHAT, CPChatData::CHAT_ITEM_DATA_LIST);
	SubModuleData::clearAll();

	ModuleData::setInt(CPModuleName::CHAT, CPChatData::CHAT_ITEM_PID, pid);
	ModuleData::setInt(CPModuleName::CHAT, CPChatData::CHAT_ITEM_ID, iid);

	MsgItemInfoDataGetRequest *msg = new MsgItemInfoDataGetRequest;
	msg->pid = pid;
	msg->iid = iid;
	HandleMessage::sendMessage(msg);
}

bool ChatPanelHelper::isToGM()
{
	int flag = 0;
	ModuleData::getInt(CPModuleName::CHAT, CPChatData::CHAT_TO_GM, flag);
	return (flag != 0);
}

void ChatPanelHelper::setToGM( bool toGM )
{
	const int flag = (toGM ? 1 : 0);
	ModuleData::setInt(CPModuleName::CHAT, CPChatData::CHAT_TO_GM, flag);
}
