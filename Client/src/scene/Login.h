#ifndef __USER_LOGIN_LAYER_H__
#define __USER_LOGIN_LAYER_H__

#include "cocos2d.h"
#include "event/IEventListener.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include <map>
#include "controls/CPTips.h"
#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "controls/CPTouchTip.h"

using namespace cocos2d;
USING_NS_CC_EXT;

class Login : public CCLayer
{
public:
	Login();
	virtual ~Login();

	static Login *create();
	static Login *create(int viewID);

private:
	bool initWithData(int viewID);
	void initUI();

	void scheduleLight();
	void showLight();
	void hideLight();

    void swordAnimationEnd();
private:
	CCSprite*		_light;
	CCLayerColor*		_light_screen;
public:
    static bool s_swordAnimationEnd;
};

/////////LoginFace//////////////////////////////////////////////////
class CPChecker;
class CPItemComponents;
class ScrollLabel;
class LoginFace : public CCLayer, public IEventListener
{
public:
	LoginFace();
	~LoginFace();

	bool init();
	void onEnter();

	CREATE_FUNC(LoginFace);

private:
	void initUI();
	void initBtns();
	void showStrongUpdateNote();
	void showScriptUpdateNote();
	void showStrongUpdateNoteEx();
	void showOptionalUpdateNoteEx();
	void showOptionalUpdateNote();
	void refreshAnnouncement();
	void hideAnnouncement();
	void checkVersion4Appstore();
	void onDownload4Appstore(int btnType);

	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	void onVersionUpdate(int code);
	void onScriptUpdate(int code);
	void onOptionalVersionUpdate(int code);
	void onOptionalScriptUpdate(int code);
	void onExitGame(int code);

	void keyBackClicked();
	void checkVersion();
	void checkSVNVersion();
	void checkVersionUpdate();

	void onCheckVersionManual(CCObject *target);
	void onLoginQQorWeinxin(CCObject *target);

	void onCPEvent(const std::string &eventName);

	void sendMsgTo3737();//向3737后台发送统计数据
	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);

    void showTouchTip(std::string note);
    void hideTouchTip();
private:
	CPChecker *mChecker;
	CCLabelTTF *mVersionLabel;
	CCLabelTTF *mEnterLabel;
	ScrollLabel	*m_moveLabel;
	CCLayer *mAnnouncementLayer;
	CPItemComponents *mAnnouncement;
    CPTouchTip* mTouchTip;

    int mNeedUpdate;
    enum {
        TypeLoading = -1,
        TypeNull = 0,
        TypeOnScriptUpdate = 1,
        //TypeShowStrongUpdateNoteEx = 2,
		Tag_weixin = 3,
		Tag_qqphone = 4,
    };
public:
	static int s_mini ;//小包40集强制更新标志
};



typedef void (CCObject::*SEL_NotePanel)(int);
#define notepanel_selector(_SELECTOR) (SEL_NotePanel)(&_SELECTOR)
class NotePanel : public CPTipsSub
{
public:
	enum
	{
		confirm = 0,
		cancel = 1,
	};

	enum
	{
		normal = 0,
		confirm_only = 1,
	};

	enum
	{
		updatetype_gameVersion = 1,
		updatetype_svnVersion = 2,
		updatetype_dataVersion = 4,
	};
public:
	NotePanel();
	~NotePanel();
	static NotePanel *create(int type);
	static NotePanel *create(int type, int priority);

public:
	void setTitle(const std::string &title);
	void setContent(const std::string &content);

	void setHandler(CCObject *target, SEL_NotePanel func);

private:
	bool initWithData(int type, int priority);
	void initUI();

	void onClick(CCObject *target);

private:
	CCLabelTTF *mTitleLabel;
	CCLabelTTF *mContentLabel;
	CCObject *mHander;
	SEL_NotePanel mHandleFunc;

	int mType;
	int mPriority;
};

/////////////LoginBody////////////////////////////////////////////////
class  LoginBody : public CCLayer, public IEventListener
{
public:
	 LoginBody();
	~LoginBody();

	bool init();
	void onEnter();
	CREATE_FUNC(LoginBody);

private:
	void initUI();

	void onLogin(CCObject *target);

	void keyBackClicked();

	void onCPEvent(const std::string &eventName);

private:
	extension::CCEditBox *userNameBox;
	extension::CCEditBox *passwordBox;
	CPChecker *mChecker;
};

//////////////////////////////3737登录注册///////////////////////////////
class Login_3737 : public CCLayer , public IEventListener
{
public:
	Login_3737();
	~Login_3737();

	CREATE_FUNC(Login_3737);
	bool init();
	void onEnter();
private:
	void initUI();
	void initButtons();
	void onCPEvent(const std::string &eventName);
	void onRegister(CCObject* pSender);
	void onLogin(CCObject* pSender);
	void onQuickPlay(CCObject* pSender);
    void goLogin();
    void onQuickLoginAlert( int btnType );
	void onLoginQQorWeinxin(CCObject* target);

	CCLabelTTF* m_labelStatusCode;
	extension::CCEditBox *userNameBox;
	extension::CCEditBox *passwordBox;
	CPChecker *mChecker;
	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    void onQuickPlayCompleted(CCHttpClient* client, CCHttpResponse* response);
    void onQuickPlayAlert( int btnType );

private:
	enum MyLogin
	{
		Tag_weixin = 1,
		Tag_qqphone = 2,
	};
};


class Register_3737 : public CCLayer , public IEventListener
{
public:
	Register_3737();
	~Register_3737();

	CREATE_FUNC(Register_3737);
	bool init();
private:
	void initUI();
	void initButtons();

	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    void onQuickBindCompleted( CCHttpClient* client, CCHttpResponse* response );

	void onCPEvent(const std::string &eventName);
	void onQxRegister(CCObject* pSender);
	void onRegister(CCObject* pSender);
	bool checkUsername(std::string username);

	CCLabelTTF* m_labelStatusCode;
	extension::CCEditBox *userNameBox;
	extension::CCEditBox *passwordBox;
	extension::CCEditBox *passwordBox01;

};

//////////////////////////////end///////////////////////////////////////

///////////LoginFeet////////////////////////////////////////////////////
class LoginFeet : public CCLayer , public IEventListener
{
public:
	LoginFeet();
	~LoginFeet();

	CREATE_FUNC(LoginFeet);
	bool init();
	void initUI();
	void onEnter();
	void menuCallBack(CCObject* target);
	void onCPEvent(const std::string &eventName);
	void onReturn(CCObject* target);
	bool checkPlayerOld();
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
private:
	CCLabelTTF* label_login;
	CCLabelTTF* serverName;
	CCLabelTTF* mEnterLabel;
	CCMenuItemFont *choseServer;

	int index;

	enum loginf
	{
		bgtag,
		chose,
		enter,
	};
};

/////////ServerList////////////////////////////////////////////////////
class BasePanel;
class ServerList : public CCLayer, public IEventListener
{
public:
	ServerList();
	~ServerList();
	CREATE_FUNC(ServerList);

	bool init();
	static int initIndex();

private:
	void initUI();
	void initUI_I();
	void initUI_II();
	void buildSwitchMenu();
	void refreshList();

	void onReturn(CCObject *target);
	void onEnterServer(CCObject *target);
	void onEnterRecServer(CCObject *target);
	void onSwitch(CCObject *target);
	void onList(CCObject *target);
	void onLatelyOrRecommendEnter(CCObject *target);
	void addState(CCMenuItemSprite* btnsprite,int tag);

	void selSection(int index);

	void keyBackClicked();

	void onCPEvent(const std::string &eventName);
	bool isDoubleClickItem( int tag );
	void singleClickCallback(float dt);

private:
	CCLayer *listLayer;
	CPItemComponents *switchMenu;
	CPItemComponents *itemList;
	CPChecker *mChecker;
	CCMenu* pMenu;
	CCMenu* svrListMenu;
	CCLabelTTF* lastLabel;
	CCLabelTTF* recommend;
	CCMenuItemSprite *latelyLogin;
	CCMenuItemSprite *deepRecommend;

	int mRegionIndex;
	static int index;
	int mLatelyIndex;

	int				m_nPreTag;
	float			m_nPreTime;
	bool			m_bDoubleClick;
	bool            m_bisOver;
	CCLabelTTF*     m_CurrentChoseServer;

	enum TAG_num
	{
		TAG_State_tuijian = 0,
		TAG_State_zhengchang = 1,
		TAG_State_yongji = 2,
		TAG_State_baoman = 3,
		TAG_State_weihu = 4,
		TAG_State_deeptuijian = 5,
		TAG_State_MAX = TAG_State_deeptuijian,

		Tag_late = 100,
		Tag_recommend,
		Tag_three,
		Tag_four,
		Tag_five,
		Tag_six,
	};
};

/////////CreateRole///////////////////////////////////////////////////
class CreateRole : public CCLayer, public IEventListener, public extension::CCEditBoxDelegate
{
public:
	CreateRole();
	~CreateRole();
	CREATE_FUNC(CreateRole);

	bool init();
	void onEnter();

private:
	void initUI();
	void refresh();

	void editBoxEditingDidBegin(extension::CCEditBox *editBox);
	void editBoxReturn(extension::CCEditBox *editBox);

	void onList(CCObject *target);
	void onRandom(CCObject *target);
	void onCreate(CCObject *target);
	void onReturn(CCObject *target);

	void onCPEvent(const std::string &eventName);

private:
	CPItemComponents *roleList;
	extension::CCEditBox *userNameBox;
	CPChecker *mChecker;
	CCLayer *mRefreshLayer;

	std::string mUserNameBeforeEdit;
	std::string mLastCreateName;
};

////////////////CCMenuR//////////////////////////
class CCMenuR : public CCMenu
{
public:
	CCMenuR();
	//this memeber function must be overwrite to create the object of the CCMenuEx type
	//the static function will be used like a global function
	//if we use its parent class's static init function we will creates one object of its parent 
	static CCMenuR* create();
	static CCMenuR* create(CCMenuItem* item);
	static CCMenuR* create(CCMenuItem* item, ...);
	static CCMenuR* createWithItems(CCMenuItem *firstItem, va_list args);
	static CCMenuR* createWithArray(CCArray* pArrayOfItems);
	void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	int getDir();
private:
	CCPoint m_TouchPos;
	short m_nMoveddir;
	int m_nPriority;
};
///////////SelectRole///////////////////////////////////////////////////
class SelectRole : public CCLayer, public IEventListener
{
public:
	SelectRole();
	~SelectRole();
	CREATE_FUNC(SelectRole);

	bool init();
	void onEnter();

private:
	void initIndexAndPage();
	void initUI();
	void refreshButtonStateAndPage();
	void refreshList(bool withAnim);
	void clearListMenu();

	CCNode *createRoleNode(int index, const CCSize &nodeSize);
	void selectRole(int pos, bool withAnim);
	void moveTo(int index, int targetPos, bool withAnim);
	int getIndexByPos(int pos);

	void onBackServer(CCObject *target);
	void onEnterGame(CCObject *target);
	void onList(CCObject *target);
	void onDelete(CCObject *target);
	void onPrePage(CCObject *target);
	void onNextPage(CCObject *target);

	void onDeleteSelect(int btnTag);

	void onMoveEnd();

	void updateWaitingLabel();

	int getCurrentFirstIndex();
	
	void onCPEvent(const std::string &eventName);
	
private:
	enum
	{
		pos_left = 0,
		pos_middle = 1,
		pos_right = 2,
	};

	CCMenuR *mListMenu;
	CCMenuItemImage *mDelBtn;
	CPChecker *mChecker;
	CCMenuItemImage *mPrePageBtn;
	CCMenuItemImage *mNextPagebtn;
	CCLabelTTF *mPageLabel;

	int mCurrentIndex;
	int mCurrentPage;
	int mMaxPage;

	typedef std::map<int, int> IndexToPos;
	IndexToPos mIndexToPos;

	int	mCurWaitingPos;
	CCLabelTTF *mWaitingLable;
};

///////////GameNotifition///////////////////////////////////////////////////
class ScrollLabel:public CCNode
{
public:
	ScrollLabel();
	~ScrollLabel();
	CREATE_FUNC(ScrollLabel);
	bool init();
	void initUI();

	void scheduleScroll();

	void fadeFirstLine();

	void moveLine();

private:
	CCArray *m_labelList;

};
#endif  // __USER_LOGIN_LAYER_H__