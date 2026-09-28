#ifndef __GuidePanel_h__
#define __GuidePanel_h__

#include "cocos2d.h"
#include "event/IEventListener.h"
#include "ext/PartPanel.h"

using namespace cocos2d;

class GuidePanel : public CCLayer, public IEventListener
{
public:
	GuidePanel();
	~GuidePanel();
	CREATE_FUNC(GuidePanel);
	bool init();
	void onEnter();
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void skipCallBack( CCObject *pSender );
private:
	void show();
	void hide();
	void resetArea();

	void startTimer();
	void onTimeOut(float dt);

	void onCPEvent(const std::string &eventName);

private:
	CCLayer *mSubLayer;
	CCRect mFunctionArea;
	bool mHasBlackGuide;
};

////////GuideWelcomeLayer////////////////////////////////////////////////////
class GuideWelcomeLayer : public CCLayer
{
public:
	GuideWelcomeLayer();
	~GuideWelcomeLayer();
	CREATE_FUNC(GuideWelcomeLayer);
	bool init();
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

private:
	void initUI();
};

/////////BaseNotePanel////////////////////////////////////////////////
class BaseNotePanel : public CCLayer
{
public:
	BaseNotePanel();
	~BaseNotePanel();
	
	static BaseNotePanel *create();
	static BaseNotePanel *create(bool isBig);
	bool init();
	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

public:
	void setTitle(const std::string &title);
	void setDesc(const std::string &desc);
	void setCloseHandler(CCObject *handler, SEL_CallFunc func);
	void close();

private:
	bool init(bool isBig);
	void initUI();
	void onClose(CCObject *target);

private:
	CCSprite *mBoard;
	CCLabelTTF *mTitleLabel;
	CCLabelTTF *mDescLabel;
	CCObject *mHandler;
	SEL_CallFunc mHandleFunc;

	bool mIsBig;
};

///////NewEquipLayer/////////////////////////////////////////////////////
class NewEquipPanel : public BaseNotePanel
{
public:
	NewEquipPanel();
	~NewEquipPanel();
	CREATE_FUNC(NewEquipPanel);
	bool init();

private:
	void initUI();

	void onItem(CCObject *target);
	void onEquip(CCObject *target);

private:
	int mItemSID;
};

////////NewSkillPanel////////////////////////////////////////////////
class NewSkillPanel : public BaseNotePanel
{
public:
	NewSkillPanel();
	~NewSkillPanel();
	CREATE_FUNC(NewSkillPanel);
	bool init();

private:
	void initUI();

	void onItem(CCObject *target);
	void onLearn(CCObject *target);

private:
	int mItemSID;
};

////////NewFunctionPanel///////////////////////////////////////////////
class NewFunctionPanel : public CCLayer
{
public:
	NewFunctionPanel();
	~NewFunctionPanel();
	CREATE_FUNC(NewFunctionPanel);
	bool init();

private:
	void initUI();

	void onShowNext();

	void onConfirm(CCObject *target);

	void close();

private:
	BaseNotePanel *mNextFunctionLayer;
	std::string mFuncName;
};

//////////NewGiftPanel/////////////////////////////////////////////////////
class NewGiftPanel : public CCLayer
{
public:
	NewGiftPanel();
	~NewGiftPanel();
	CREATE_FUNC(NewGiftPanel);
	bool init();

private:
	void initUI();

	void onOpen(CCObject *target);
	void onItem(CCObject *target);
	void onGet(CCObject *target);

	void close();

private:
	int mItemSID;
};

////////NewItemUsePanel/////////////////////////////////////////////////
class NewItemUsePanel : public BaseNotePanel
{
public:
	NewItemUsePanel();
	~NewItemUsePanel();
	CREATE_FUNC(NewItemUsePanel);
	bool init();

private:
	void initUI();

	void onItem(CCObject *target);
	void onUse(CCObject *target);

private:
	int mItemSID;
};

//////////NewGiftPanel/////////////////////////////////////////////////////
class SystemGiftPanel : public PartPanel
{
public:
	SystemGiftPanel();
	~SystemGiftPanel();
	CREATE_FUNC(SystemGiftPanel);
	bool init();

private:
	void initUI();

	void onItem(CCObject *target);
	void onGet(CCObject *target);

	void close();

private:
	int mItemSID;
	int mData;
	std::string mString;
};

//////////HollowItemPanel/////////////////////////////////////////////////////
class HollowItemPanel : public PartPanel
{
public:
	HollowItemPanel();
	~HollowItemPanel();
	CREATE_FUNC(HollowItemPanel);
	bool init();

private:
	void initUI();

	void onItem(CCObject *target);
	void onGet(CCObject *target);

	void close();

private:
	int mItemIID;
	std::string mString;
};

//////////MailPanel/////////////////////////////////////////////////////
class MailPanel : public PartPanel
{
public:
	MailPanel();
	~MailPanel();
	CREATE_FUNC(MailPanel);
	bool init();

private:
	void initUI();

	void onGet(CCObject *target);

	void close();

private:
	int mData;
	std::string mTitle;
	std::string mContent;
	std::string mGift;
};

//////////NoticePanel/////////////////////////////////////////////////////
class NoticePanel : public CCLayer
{
public:
	NoticePanel();
	~NoticePanel();
	CREATE_FUNC(NoticePanel);
	bool init();

private:
	void initUI();

	void onGet(CCObject *target);

	void close();

private:
	int mSceneID;
	int mPosx;
	int mPosy;
	std::string mName;
};
#endif //__GuidePanel_h__