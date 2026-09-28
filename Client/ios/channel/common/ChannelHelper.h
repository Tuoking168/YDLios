//
//  ChannelHelper.h
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#ifndef __Fire__ChannelHelper__
#define __Fire__ChannelHelper__

#include "cocos2d.h"
#include <vector>
#include "cocos-ext.h"
#include "controls/CPTouchTip.h"

USING_NS_CC;
using namespace std;

/*屏幕方向枚举，等同于iOS原生方向*/
typedef enum {
    SDKInterfaceOrientationPortrait = 1,
    SDKInterfaceOrientationPortraitUpsideDown,
    SDKInterfaceOrientationLandscapeLeft,
    SDKInterfaceOrientationLandscapeRight
}SDKOrientation;
/*callback 枚举*/
typedef enum {
    CallBack_Null = 0,
    CallBack_EnterGame,
    CallBack_ShowRegister,
    CallBack_Retry,
    CallBack_Upload,
}CHANNELHELPER_CALL_BACK;

#define CP_NETWORK_VERSION

#define ChannelOrderDataLocal "ChannelOrderDataLocal"

typedef void (CCObject::*CHANNEL_CALLBACK)(int);
#define channel_selector(_SELECTOR) (CHANNEL_CALLBACK)(&_SELECTOR)

class ChannelHelper
{
public:
    
private:
    ChannelHelper();
    virtual ~ChannelHelper();
    static ChannelHelper* instance;
private:
    CCObject *m_pListener;
    CHANNEL_CALLBACK m_pfnSelector;
    
    int m_serverid;
    
    CPTouchTip* m_tip;
    string m_productID;
public:
    static void messageBox(const char* str);
#pragma mark -------------------------------common---------------------------------------------
public: //common
    static ChannelHelper* GetInstance();
    
    void setServerID(int sid){m_serverid=sid;};
    
    int getPlatform();
    //const char* getProductID(int index);
    void setCallBack(CCObject *rec, CHANNEL_CALLBACK selector);
    void handleCallBack(int type);
    const char* getUserID();
    const char* getChannelToken();
    
    const char* getDeviceID();
    const char* getIPAddress();
    
    void initSDK();
    void showLogin();
    void showUserCenter();
    bool isLogin();
    void logout();
    std::string goldString(std::string gold);
    void pause();
    void getOrderIdRequest(const char* product_id,float amount,int count);
    void loginVerifyRequest();
    
    void loginFailed();
    void loginFailedWithError(const char* errorInfo);
    
    void showToolBar();
    void hideToolBar();
    
    void orderCallBack(cocos2d::extension::CCHttpClient* client, cocos2d::extension::CCHttpResponse* response);
    void orderCallBack(CCNode* client, void* response);
    
    void connectGM();
private:
    typedef std::map<std::string, int> OrderMap;
    std::string mergeOrderID(OrderMap mOrders);
    OrderMap loadOrderID();
    std::vector<std::string> split(std::string str,std::string pattern);

public:
    void pay(const char* orderID,float amount,const char* productID,int count);
    void payFailedWithError(const char* orderID,int errorCode);
    void createOrderFailedWithError(const char* errorInfo);
#pragma mark -------------------------------quick play---------------------------------------------
public:
    void appInit();
    void setQuickUser(std::string username,std::string password,std::string uid);
    bool isQuickPlay(std::string uname = "");
    std::string getQuickUserName();
    std::string getQuickPassword();
    std::string getQuickUid();
    bool isBindInGame();
    void rmvQuickUser();
    void setInLogin(bool inLogin);
    
private:
    bool mIsInLogin;
    //    bool mIsQuickPlay;
    //    std::string mQuickUserName;
    //    std::string mQuickPassword;
    //    std::string mQuickUid;
#pragma mark -------------------------------msdk---------------------------------------------
public:
    void QQAuth();
    void WXAuth();
#pragma mark -------------------------------appstore helper---------------------------------------------
public:
    bool checkOrder();
    void endPay();
    void IAPpay(const char* product_id);
    void showTip(std::string note);
    void hideTip();
    
    void goBuy(int index);
    std::string getCurProductID(){return m_productID;};
    std::string getAppStoreVersion();
    void onDownload4AppStore();
    bool needGoAppStore();
   
#pragma mark -------------------------------PP helper---------------------------------------------
public:
    void PPInitSDK(int appID,const char* appKey);
    void PPShowLogin();
    bool PPIsLogin();
    void PPShowCenter();
    void PPPay(float amount,const char* orderID,const char* paydes);
    void PPAlixPayResult(const char* vUrl);
#pragma mark -------------------------------tongbu helper---------------------------------------------
private:
    /* 初始化平台
     * appid：应用ID，由后台获取
     * orientation：平台初始方向
     * isAcceptWhenFailed：检查更新失败后是否允许进入游戏
     */
    void TBInitSDK(int appID,bool isAcceptWhenFailed);
    /*登录*/
    int TBLogin(int tag);
    /*注销 tag:0,表示注销但保存本地信息；1，表示注销，并清除自动登录*/
    int TBLogout(int tag);
    /*切换帐号*/
    int TBSwitchAccount();
    /*是否已登录*/
    bool TBIsLogined();
    /*开启调试模式*/
    void TBSetDebug();
    /*获取会话ID*/
    const char* TBSessionID();
    /*获取用户ID*/
    const char* TBUserID();
    /*获取用户昵称*/
    const char* TBNickName();
    /*检查更新*/
    int TBCheckUpdate();
    /*支付（指定金额）*/
    int TBUnipayForCoinWithOrder(const char *order,float amount,const char *paydes);
    /*支付（玩家自选金额）*/
    int TBUnipayForCoinWhthOrder(const char *order,const char *paydes);
    /*查询订单结果*/
    int TBCheckOrder(const char *order);
    /*进入个人中心*/
    int TBEnterUserCenter(int tag);
    /*进入游戏推荐中心*/
    int TBEnterGameCenter(int tag);
    /*进入论坛*/
    int TBEnterBBS(int tag);
#pragma mark -------------------------------91 helper---------------------------------------------
private:
    void NDInitSDK(int appID,const char* appKey);
    void NDLogin(int type);
    bool NDIsLogin();
    void NDLogout(int type);
    void NDPause();
    void NDPayForGoods(float amount,const char* orderID,const char* productID,int count);
    void NDPayForCoin(float amount,const char* orderID);
    //好友
    void NDEnterFriendsCenter();
    //社区
    void NDEnterPlatform();
    //论坛
    void NDEnterBBS();
    //赚金币
    void NDEnterEarnGold();
    //意见反馈
    void NDEnterFeedback();
#pragma mark -------------------------------kuaiyong helper---------------------------------------------
private:
    void KYInitSDK(int appID,const char* appKey);
    void KYShowLogin();
    bool KYIsLogin();
    void KYLogout();
    void KYShowLogout();
    void KYAutoLogin();
    void KYShowUserView();
    /*
     显示支付
     dealseq:订单号，无论失败还是成功的订单号必须不同，否则会报1007错误
     fee:金额，建议保留两位小数点
     game:http://payquery.bppstore.com上面对应ID，一般为四位数字
     gamesvr:多个通告地址的选择设置
     subject:物品名称
     md5Key:http://payquery.bppstore.com该网址对应的签名秘钥
     appScheme:支付宝快捷支付对应的回调应用名称
     */
    void KYShowPay(const char* dealseq,const char* fee, const char *subject);
#pragma mark -------------------------------itools helper---------------------------------------------
private:
    void itoolsInitSDK(int appID,const char* appKey);
    void itoolsShowLogin();
    bool itoolsIsLogin();
    void itoolsShowPlatformView();
    //void IToolsShowRecharge();
    //支付, 使用支付平台用户系统调用这个
    void itoolsPay(float amount,const char* orderID,const char* paydes);
    //直接支付(不使用支付平台用户系统, 直接调用支付)//SDK1.4去掉此方法
    //void itoolsDirectPay(const char* account,float amount,const char* orderID);
#pragma mark -------------------------------i4 helper---------------------------------------------
private:
    void asInitSDK(int appID,const char* appKey);
    void asShowLogin();
    void asLogout();
    bool asIsLogin();
    void asShowUserCenter();
    void asPay(float amount,const char* orderID);
#pragma mark -------------------------------hm helper---------------------------------------------
private:
    void hmInitSDK(int appID,const char* appKey);
    void hmShowLogin();
    void hmLogout();
    bool hmIsLogin();
    void hmShowUserCenter();
    void hmPay(float amount,const char* orderID);
#pragma mark -------------------------------3737 helper---------------------------------------------
private:
    void c3737InitSDK(int appID,const char* appKey);
    void c3737ShowLogin();
    void c3737Logout();
    bool c3737IsLogin();
    void c3737ShowUserCenter();
    void c3737Pay(float amount,const char* orderID);
#pragma mark -------------------------------xy helper---------------------------------------------
private:
    void xyInitSDK(int appID,const char* appKey);
    void xyShowLogin();
    void xyLogout();
    bool xyIsLogin();
    void xyShowUserCenter();
    void xyPay(float amount,const char* orderID);
#pragma mark -------------------------------VTCid helper---------------------------------------------
private:
    void vtcidInitSDK(int appID,const char* appKey);
    void vtcidShowLogin();
    void vtcidLogout();
    bool vtcidIsLogin();
    void vtcidShowUserCenter();
    void vtcidPay(float amount,const char* orderID);
#pragma mark -------------------------------IIAPPLE helper---------------------------------------------
private:
    void iiappleInitSDK(int appID,const char* appKey);
    void iiappleShowLogin();
    void iiappleLogout();
    bool iiappleIsLogin();
    void iiappleShowUserCenter();
    void iiapplePay(float amount,const char* orderID);
};


#define CHANNELHELPER ChannelHelper::GetInstance()

#endif /* defined(__Fire__ChannelHelper__) */
