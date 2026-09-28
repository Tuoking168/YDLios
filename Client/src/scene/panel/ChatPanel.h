#ifndef __ChatPanel_h__
#define __ChatPanel_h__

#include "FullScreenPanel.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "utils/MacroUtils.h"
#include "userdata/UserItemData.h"

namespace ChatBuilder
{
	enum
	{
		type_null = 0,

		type_start = 1,
		type_stop = 2,

		type_label = 3,
		type_icon = 4,
		type_player_name = 5,
		type_player_gender = 6,

		type_item_name = 7,
		type_scene_name = 8,
		type_npc_name = 9,
		type_monster_name = 10,
		type_activity_name = 11,
		type_position = 12,
		type_team = 13,

		type_gm = 20,
	};
}

class CPChecker;
class CPItemComponents;
class CPRichText;
class CPComboBox;
class ChatPanel : public FullScreenPanel
{
public:
	ChatPanel();
	~ChatPanel();
	
	static ChatPanel *instance();
	void show();
	void show(int channel);
	

private:
	bool init();
	void onExit();

	void initUI();
	void rebuildFilter();
	void rebuildChannel();

	void refreshHorn();
	void refreshNorm();
	void refreshIfNeed();
	void refreshInputPlaceHolder();
	void clearChat();

	void showItemTips();

	void onFilter(CCObject *target);
	void onEmoticons(CCObject *target);
	void onSend(CCObject *target);
	void onShowItem(CCObject *target);

	void onPlayer(CCObject *target);
	void onItem(CCObject *target);
	void onScene(CCObject *target);
	void onNPC(CCObject *target);
	void onMonster(CCObject *target);
	void onActivity(CCObject *target);
	void onPosition(CCObject *target);
	void onTeam(CCObject *target);
	void onGM(CCObject *target);

	void onChannelChange(CCNode *box);
	void onAddEmoticons(int eID);

	bool needShow(int chatType);
	void buildChatMsg();
	void addHornChatMsg(int index);
	void addHornChatFinish();
	void addNormChatMsg(int index);
	void addNormChatFinish();

	void onCPEvent(const std::string &eventName);

private:
	extension::CCEditBox *mInputText;
	CPChecker *mChecker;
	CPItemComponents *mFilter;
	CPItemComponents *mHornChats;
	CPItemComponents *mNormChats;
	CPRichText *mCurrentChat;
	CPComboBox *mChannelBox;

	int mCurrentFilter;
	int mHornChatState;
	int mNormChatState;
	UserItem mShowItemData;
};

//////////PlayerOperationPanel/////////////////////////////////////////
class PlayerOperationPanel : public CCLayer
{
public:
	PlayerOperationPanel();
	~PlayerOperationPanel();
	CREATE_FUNC(PlayerOperationPanel);


public:
	void setPlayerID(int pid);
	void setPlayerName(const std::string &name);


	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
	bool init();
	void onEnter();
	void initUI();
	void open();
	void close();

	void onLook(CCObject *target);
	void onFriend(CCObject *target);
	void onTeam(CCObject *target);
	void onGuild(CCObject *target);
	void onPrivate(CCObject *target);

private:
	int mPlayerID;
	bool mOpened;
	std::string mPlayerName;
};

/////////EmoticonPanel//////////////////////////////////////////////////
typedef void (CCObject::*SEL_Emoticons)(int);
#define emoticons_selector(_SELECTOR) (SEL_Emoticons)(&_SELECTOR)
class EmoticonsPanel : public CCLayer
{
public:
	EmoticonsPanel();
	~EmoticonsPanel();
	CREATE_FUNC(EmoticonsPanel);

public:
	void setHandler(CCObject *handler, SEL_Emoticons func);

	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
	bool init();
	void onEnter();
	void initUI();
	void open();
	void close();

	void onClick(CCObject *target);

private:
	CCObject *mHandler;
	SEL_Emoticons mHandleFunc;
	CCNode *mBoard;

	bool mOpened;
};

//////////CCMenuItemFontEx////////////////////////////////////
class CCMenuItemFontEx : public CCMenuItemFont
{
public:
	CCMenuItemFontEx();
	~CCMenuItemFontEx();

	static CCMenuItemFontEx *create(const std::string &text);

public:
	void setExData(int dataX, int dataY, int dataZ);
	int getDataX();
	int getDataY();
	int getDataZ();

private:
	int mDataX;
	int mDataY;
	int mDataZ;
};

////////////ChatPanelHelper/////////////////////////////////////////////
class ChatPanelHelper
{
public:
	static void openChatWithPartner(int partnerID, const std::string &partnerName);
	static void openChatWithPartner(int partnerID, const std::string &partnerName, bool toGM);
	static int getChatPartnerID();
	static std::string getChatPartnerName();
	static void clearChat();

	static int getTypeByNormChatID(int chatID);
	static int getLastChatType();
	static int getIndexByType(int chatType);

	static void addChatMsg(int chatType, int pid, const std::string &playerName, int gender, int vipLevel, const std::string &chatText);
	static void addChatMsg(const std::string &recordType, int chatID);
	static void addChatMsg();
	static void addSystemMsg(const std::string &chatText);

	static bool testChatText(const std::string &chatText);
	static void clearItemData();
	static void initItemData(UserItem &itemData);

	static void sendChatRequest(int chatType, int partnerPid, const std::string &chatText);
	static void itemInfoRequest(int pid, int iid);

	static bool isToGM();
	static void setToGM(bool toGM);

private:
	CP_MAKE_STATIC_CLASS(ChatPanelHelper);
};

#endif //__ChatPanel_h__