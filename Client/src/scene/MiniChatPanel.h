#ifndef __MiniChatPanel_h__
#define __MiniChatPanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"
#include "utils/MacroUtils.h"

using namespace cocos2d;

class CPItemComponents;
class CPRichText;
class MiniChatPanel : public CCLayer, public IEventListener
{
public:
	MiniChatPanel();
	~MiniChatPanel();
	CREATE_FUNC(MiniChatPanel);

	bool init();

private:
	void initUI();
	void buildChatMsg();
	void show();
	void hide();

	void showPrivateChatNote();
	void hidePrivateChatNote(bool clean);

	void onChat(CCObject *target);
	void openChat();
	void openChat(bool isPrivate);
	void clearIfNeed();

	void onCPEvent(const std::string &eventName);

private:
	CCLayer *mChatContainer;
	CPItemComponents *mChatList;
	CPRichText *mCurrentChat;
	CCMenuItemImage *mChatBtn;

	int mPlayerID;
	std::string mPlayerName;
};

////////MiniChatPanelHelper//////////////////////////////////////////////////
class MiniChatPanelHelper
{
public:
	static void addChatMsg(int &partnerID, std::string &partnerName);
	static void addChatMsg(int chatType, int pid, const std::string &playerName, int gender, int vipLevel, const std::string &chatText);

private:
	CP_MAKE_STATIC_CLASS(MiniChatPanelHelper);
};
#endif //__MiniChatPanel_h__