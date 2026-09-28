//
//  ChannelHelper.cpp
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#include "ChannelHelper.h"
#import "ChannelCallBack.h"
#include "cocos2d.h"

#include <ifaddrs.h>
#include <arpa/inet.h>

#include "scene/panel/FloatPanel.h"

#include "BDWebView.h"
//#include "userdata/GameData.h"
//#include "userdata/HeroData.h"
//#include "userdata/netdata/GameRole.h"
#include "ext/md5.h"

USING_NS_CC;


#include <iostream>

ChannelHelper::ChannelHelper()
: m_pListener(NULL)
, m_pfnSelector(NULL)
, m_serverid(0)
, m_tip(NULL)
, m_productID("")
{
   
}
ChannelHelper::~ChannelHelper()
{
    delete instance;
}
ChannelHelper* ChannelHelper::instance=new ChannelHelper();
ChannelHelper* ChannelHelper::GetInstance()
{
    return instance;
}
void ChannelHelper::messageBox(const char* str)
{

}
void ChannelHelper::setCallBack(CCObject *rec, CHANNEL_CALLBACK selector)
{
    m_pListener = rec;
	m_pfnSelector = selector;
}
void ChannelHelper::handleCallBack(int type)
{
    if (m_pListener && m_pfnSelector)
	{
		(m_pListener->*m_pfnSelector)(type);
	}
}
const char* ChannelHelper::getUserID()
{
    const char* str = [CHANNELCALLBACK.user_ID UTF8String];
    if (str) {
        return str;
    }
    return "";
}

const char* ChannelHelper::getChannelToken()
{
    const char* str = [CHANNELCALLBACK.token_Key UTF8String];
    if (str) {
        return str;
    }
    return "";
}
const char* ChannelHelper::getDeviceID()
{
#if defined VTCID_VERSION
    return "";
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSString* deviceid = @"";
    if ( [[UIDevice currentDevice].systemVersion floatValue] >= 6)
    {
        NSString *idfa = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
        deviceid = [idfa stringByReplacingOccurrencesOfString:@"-" withString:@""];
    }
    else
    {
        deviceid = [CHANNELCALLBACK macAddress];
    }
    return [deviceid UTF8String];
#else
    return "";
#endif
}
const char *ChannelHelper::getIPAddress()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSString *address = @"error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while (temp_addr != NULL) {
            if( temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if ([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
            }
            
            temp_addr = temp_addr->ifa_next;
        }
    }
    
    // Free memory
    freeifaddrs(interfaces);
    
    return address.UTF8String;
#else
    return "";
#endif
}
int ChannelHelper::getPlatform()
{
    int vPlatform = 0;
#if defined APPSTORE_VERSION
    vPlatform = ChannelID::ios_appstore;
#elif defined C91_VERSION
    vPlatform = ChannelID::ios_91;
#elif defined PP_VERSION
    vPlatform = ChannelID::ios_pp;
#elif defined TB_VERSION
    vPlatform = ChannelID::ios_tongbu;
#elif defined KY_VERSION
    vPlatform = ChannelID::ios_kuaiyong;
#elif defined IT_VERSION
    vPlatform = ChannelID::ios_itools;
#elif defined I4_VERSION
    vPlatform = ChannelID::ios_i4;
#elif defined HM_VERSION
    vPlatform = ChannelID::ios_haima;
#elif defined C3737_VERSION
    #if defined C3737_PGY_VERSION
        vPlatform = ChannelID::ios_3737_pgy;
    #elif defined C3737_HL_VERSION
        vPlatform = ChannelID::ios_3737_hl;
    #else
        vPlatform = ChannelID::ios_3737;
    #endif
#elif defined XY_VERSION
    vPlatform = ChannelID::ios_xy;
#elif defined VTCID_VERSION
    vPlatform = ChannelID::ios_vtcid;
#elif defined IIAPPLE_VERSION
    vPlatform = ChannelID::ios_iiapple;
#endif
    return vPlatform;
}

void ChannelHelper::initSDK()
{
    //CHANNELHELPER->connectGM();
//    string key = "appstore_rechargeid" + StringUtils::toString(6);
//    string str = LayoutData::getString(CPModuleName::VIP, "appstore_rechargeid6");
    CHANNELHELPER->appInit();
    [CHANNELCALLBACK startListen];
    CPPlatformMnger.setIntData(CPPlatformData::CHANNEL_ID,getPlatform());
#if defined APPSTORE_VERSION
    [[ECPurchase shared] addTransactionObserver];
    [[ECPurchase shared] setVerifyRecepitMode:ECVerifyRecepitModeServer];
    string url = SystemData::getConfigString("appstore_rechargeVerifyURL");
    CHANNELCALLBACK.rechargeVerifyURL = [NSString stringWithUTF8String:url.c_str()];
    m_tip = NULL;
    m_productID = "";
#elif defined C91_VERSION
    const int appID = 115260;
    const char* appKey = "5ab4420652fb3e9671c9d2ac76c4ca05132c44e933ef075d";
    CHANNELHELPER->NDInitSDK(appID, appKey);
#elif defined PP_VERSION
    const int appID = 3921;
    const char* appKey = "0a7fb33cc79876a60302b69f30b0701d";
    CHANNELHELPER->PPInitSDK(appID, appKey);
#elif defined TB_VERSION
    const int appID = 140741;
    const char* appKey = "XMZwH0Jg4D6Qn1p*MjZw0TIgsD6nczpX";
    CHANNELHELPER->TBInitSDK(appID, NO);
#elif defined KY_VERSION
    const int appID = 0;
    const char* appKey = "";
    CHANNELHELPER->KYInitSDK(appID, appKey);
#elif defined IT_VERSION
    const int appID = 338;
    const char* appKey = "972F958402F2228646F0212FC9EAA41C";
    CHANNELHELPER->itoolsInitSDK(appID, appKey);
#elif defined I4_VERSION
    const int appID = 147;
    const char* appKey = "066f9fd797114661bd75b137c5dcdf63";
    CHANNELHELPER->asInitSDK(appID, appKey);
#elif defined HM_VERSION
    const int appID = 3000766136;//以init方法内的为准
    const char* appKey = "MIICXAIBAAKBgQCQkZslK16iz8Pla/frI1gVoIBqVtFsYtg/iDJ0fwwXv7G6PRkwHbdkNrlnfoNnTy6Jq58/Y5HJ6VFBIbhyP43aTIv0Uq3pLJ6v/4eJtQCj5DUWTO4uZrU0rgjma5YkpQ+nCfzq64zXxdz3Xs1Welbm6+KetTFhAGCGVYjLrWcKlQIDAQABAoGAIKZRxJ473EdR9bFhp2AvF4tNFTcQSwszzX1j7711rLNlXytHUf+UGHTngIEpCh7u4ra422cQWOpxqGUGM/84eNkYvpdwLxxBwyTRYTHTE9qSFsa7jtNvAJhPSk7fc0dbUAOOp9zh0HmBci+Vsrckm0bkxZJ5o7J7iwkNV5NpEKECQQDruJMlY0Goe2DxBbcOxP9Y2cwhQ3XnMEIZj2s/Lp+cD4jqFcotcEoMG/G8LMfCMLJ1gLrrL/aHo2nWJRatnWddAkEAnQGH86FVQ/RGEefIhw+GoM4GuAB7h4fInTp17g5WlMKfn3wcB13A/Fzdj0Hs2P0wRKNLszAy7oD/kXUYmDUUmQJADQyOuMch313VJAKY+6xUJmsILd86K640Oo4B9eFy3ITPo4XJR3Kr5re1TiF8fXeMqYySzGo/T4rwVPaApuPL0QJAay9xZcS9Vg/8ihrHjlTuHveoJJPHwWXUcmpHukY1m4cmvBVZeTnrFx4676MdE6H+As3MTz9XdfXBA8eCC98o+QJBALZW3W71Tm7YE9LIlx0rlvQKq21Bhg+EHRH4LrQ77CSBNG4Rojdng5ltS97CemsLMjTq3kBR02PB3iDO8EKGaqE=";
    CHANNELHELPER->hmInitSDK(appID, appKey);
#elif defined C3737_VERSION
    const int appID = 3000811347;//以init方法内的为准
    const char* appKey = "RERDRTExMTExMDBCNTQxRTFBNEIxNDk1NDNFNjlEOTMwQzUwODNCN01UUTVNVGs0TXpBeU16QXdOVE0yTVRZNE5ERXJNVFE0T1RJeU9ETXlPVFUxTkRBek9UVXpNVFl4TWpZM05qVTBNemcwT1RFNE16QXlPVGcz";
    CHANNELHELPER->c3737InitSDK(appID, appKey);
#elif defined XY_VERSION
    const int appID = 100001952;
    const char* appKey = "3BBqXBW8Gd1hQk3wOmTwcAmiEaffvZs0";
    CHANNELHELPER->xyInitSDK(appID, appKey);
#elif defined VTCID_VERSION
    const int appID = 3000811347;
    const char* appKey = "RERDRTExMTExMDBCNTQxRTFBNEIxNDk1NDNFNjlEOTMwQzUwODNCN01UUTVNVGs0TXpBeU16QXdOVE0yTVRZNE5ERXJNVFE0T1RJeU9ETXlPVFUxTkRBek9UVXpNVFl4TWpZM05qVTBNemcwT1RFNE16QXlPVGcz";
    CHANNELHELPER->vtcidInitSDK(appID, appKey);
#elif defined IIAPPLE_VERSION
    const int appID = 3000811347;
    const char* appKey = "RERDRTExMTExMDBCNTQxRTFBNEIxNDk1NDNFNjlEOTMwQzUwODNCN01UUTVNVGs0TXpBeU16QXdOVE0yTVRZNE5ERXJNVFE0T1RJeU9ETXlPVFUxTkRBek9UVXpNVFl4TWpZM05qVTBNemcwT1RFNE16QXlPVGcz";
    CHANNELHELPER->iiappleInitSDK(appID, appKey);
#endif
}

void ChannelHelper::showLogin()
{
//    if(CHANNELHELPER->isLogin())
//        return;
#if defined APPSTORE_VERSION
    //LoginHelper::switchView(LoginView::loginbody);
    LoginHelper::switchView(LoginView::ios_3737_login);
#elif defined C91_VERSION
    CHANNELHELPER->NDLogin(0);
#elif defined PP_VERSION
    CHANNELHELPER->PPShowLogin();
#elif defined TB_VERSION
    CHANNELHELPER->TBLogin(0);
#elif defined KY_VERSION
    CHANNELHELPER->KYShowLogin();
#elif defined IT_VERSION
    CHANNELHELPER->itoolsShowLogin();
#elif defined I4_VERSION
    CHANNELHELPER->asShowLogin();
#elif defined HM_VERSION
    CHANNELHELPER->hmShowLogin();
#elif defined C3737_VERSION
    CHANNELHELPER->c3737ShowLogin();
#elif defined XY_VERSION
    CHANNELHELPER->xyShowLogin();
#elif defined VTCID_VERSION
    CHANNELHELPER->vtcidShowLogin();
#elif defined IIAPPLE_VERSION
    CHANNELHELPER->iiappleShowLogin();
#endif
}
void ChannelHelper::showUserCenter()
{
    if (!CHANNELHELPER->isLogin()) {
        CCLOG("no login");
        return;
    }
#if defined APPSTORE_VERSION
    
#elif defined C91_VERSION
    CHANNELHELPER->NDEnterPlatform();
#elif defined PP_VERSION
    CHANNELHELPER->PPShowCenter();
#elif defined TB_VERSION
    CHANNELHELPER->TBEnterUserCenter(0);
#elif defined KY_VERSION
    CHANNELHELPER->KYShowUserView();
#elif defined IT_VERSION
    CHANNELHELPER->itoolsShowPlatformView();
#elif defined I4_VERSION
    CHANNELHELPER->asShowUserCenter();
#elif defined HM_VERSION
    CHANNELHELPER->hmShowUserCenter();
#elif defined C3737_VERSION
    CHANNELHELPER->c3737ShowUserCenter();
#elif defined XY_VERSION
    CHANNELHELPER->xyShowUserCenter();
#elif defined VTCID_VERSION
    CHANNELHELPER->vtcidShowUserCenter();
#elif defined IIAPPLE_VERSION
    CHANNELHELPER->iiappleShowUserCenter();
#endif
}
bool ChannelHelper::isLogin()
{
#if defined APPSTORE_VERSION
    
#elif defined C91_VERSION
    return CHANNELHELPER->NDIsLogin();
#elif defined PP_VERSION
    return CHANNELHELPER->PPIsLogin();
#elif defined TB_VERSION
    return CHANNELHELPER->TBIsLogined();
#elif defined KY_VERSION
    return CHANNELHELPER->KYIsLogin();
#elif defined IT_VERSION
    return CHANNELHELPER->itoolsIsLogin();
#elif defined I4_VERSION
    return CHANNELHELPER->asIsLogin();
#elif defined HM_VERSION
    return CHANNELHELPER->hmIsLogin();
#elif defined C3737_VERSION
    return CHANNELHELPER->c3737IsLogin();
#elif defined XY_VERSION
    return CHANNELHELPER->xyIsLogin();
#elif defined VTCID_VERSION
    return CHANNELHELPER->vtcidIsLogin();
#elif defined IIAPPLE_VERSION
    return CHANNELHELPER->iiappleIsLogin();
#endif
    return false;
}
void ChannelHelper::logout()
{
#if defined APPSTORE_VERSION
    
#elif defined C91_VERSION
    CHANNELHELPER->NDLogout(1);
#elif defined PP_VERSION
    
#elif defined TB_VERSION
    CHANNELHELPER->TBLogout(1);
#elif defined KY_VERSION
    CHANNELHELPER->KYLogout();
#elif defined IT_VERSION
#elif defined I4_VERSION
    CHANNELHELPER->asLogout();
#elif defined HM_VERSION
    CHANNELHELPER->hmLogout();
#elif defined C3737_VERSION
    CHANNELHELPER->c3737Logout();
#elif defined XY_VERSION
    CHANNELHELPER->xyLogout();
#elif defined VTCID_VERSION
    CHANNELHELPER->vtcidLogout();
#elif defined IIAPPLE_VERSION
    CHANNELHELPER->iiappleLogout();
#endif
}

void ChannelHelper::showToolBar()
{
#if defined APPSTORE_VERSION
    
#elif defined C91_VERSION
    [[NdComPlatform defaultPlatform]NdShowToolBar:NdToolBarAtMiddleLeft];
#elif defined PP_VERSION
    
#elif defined TB_VERSION
    [[TBPlatform defaultPlatform]TBShowToolBar:TBToolBarAtMiddleLeft isUseOldPlace:NO];
#elif defined KY_VERSION
    
#elif defined IT_VERSION
    
#elif defined I4_VERSION
    
#elif defined HM_VERSION

#elif defined C3737_VERSION
    
#elif defined XY_VERSION
    
#elif defined VTCID_VERSION
    
#elif defined IIAPPLE_VERSION
    
#endif
}
void ChannelHelper::hideToolBar()
{
#if defined APPSTORE_VERSION
    
#elif defined C91_VERSION
    [[NdComPlatform defaultPlatform]NdHideToolBar];
#elif defined PP_VERSION
    
#elif defined TB_VERSION
    [[TBPlatform defaultPlatform]TBHideToolBar];
#elif defined KY_VERSION
    
#elif defined IT_VERSION
    
#elif defined I4_VERSION

#elif defined HM_VERSION
    
#elif defined C3737_VERSION
    
#elif defined XY_VERSION
    
#elif defined VTCID_VERSION
    
#elif defined IIAPPLE_VERSION
    
#endif
}
void ChannelHelper::orderCallBack(cocos2d::extension::CCHttpClient* client, cocos2d::extension::CCHttpResponse* response)
{

}
void ChannelHelper::orderCallBack(CCNode* client, void* response)
{

}

void ChannelHelper::pay(const char* orderID,float amount,const char* productID,int count)
{
    NSString* order_str = [CHANNELCALLBACK getOrderID];
    if ([order_str isEqual:@""]) {
        return;
    }
    orderID = [order_str UTF8String];
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    amount = 1;
#endif
    productID = "gold";
    
    NSLog(@"%s,amount = %f, count = %d,order_id = %s",__FUNCTION__,amount,count,orderID);
#if defined APPSTORE_VERSION
    NSLog(@"appstore amount = %f",amount);
    //m_amount = amount;
    string key = "appstore_rechargeid" + StringUtils::toString(amount);
    string product_id = LayoutData::getString(CPModuleName::VIP, key);
    switch ((int)amount) {
        case 6:
            product_id = "YB1";
            break;
        case 12:
            product_id = "YB2";
            break;
        case 30:
            product_id = "YB3";
            break;
        case 50:
            product_id = "YB4";
            break;
        case 108:
            product_id = "YB5";
            break;
        case 208:
            product_id = "YB6";
            break;
        case 308:
            product_id = "YB7";
            break;
        case 388:
            product_id = "YB8";
            break;
        case 648:
            product_id = "YB9";
            break;
            
        default:
            product_id = "";
            break;
    }
    m_productID = product_id;
    
    StrVector vect;
    vect.push_back(StringUtils::toString(amount));
    vect.push_back(StringUtils::toString(count));
    FloatPanel::show(FloatPanelType::Appstore_IAP_Confirm, vect, CCDirector::sharedDirector()->getNotificationNode(), floatpanel_selector(ChannelHelper::goBuy));
#elif defined C91_VERSION
    CHANNELHELPER->NDPayForGoods(amount, orderID, productID,count);
#elif defined PP_VERSION
    string title = StringUtils::toString(count)+"元宝";
    CHANNELHELPER->PPPay(amount,orderID,title.c_str());
#elif defined TB_VERSION
    CHANNELHELPER->TBUnipayForCoinWithOrder(orderID, amount, "");
#elif defined KY_VERSION
    char* buf = (char*)malloc(32);
    sprintf(buf, "%.02f",amount);
    CHANNELHELPER->KYShowPay(orderID, buf, "元宝");
#elif defined IT_VERSION
    CHANNELHELPER->itoolsPay(amount, orderID,"元宝");
#elif defined I4_VERSION
    CHANNELHELPER->asPay(amount, orderID);
#elif defined HM_VERSION
    CHANNELHELPER->hmPay(amount, orderID);
#elif defined C3737_VERSION
    CHANNELHELPER->c3737Pay(amount, orderID);
#elif defined XY_VERSION
    CHANNELHELPER->xyPay(amount, orderID);
#elif defined VTCID_VERSION
    CHANNELHELPER->vtcidPay(amount, orderID);
#elif defined IIAPPLE_VERSION
    CHANNELHELPER->iiapplePay(amount, orderID);
#endif

}
std::string ChannelHelper::goldString(std::string gold)
{
#ifdef C91_VERSION
    gold=gold+"个91豆";
#else
    gold="￥"+gold;
#endif
    
    return gold;
}
void ChannelHelper::pause()
{
    if (!CHANNELHELPER->isLogin())
        return;
    
#if defined APPSTORE_VERSION
    
#elif defined C91_VERSION
    CHANNELHELPER->NDPause();
#elif defined PP_VERSION
    
#elif defined TB_VERSION
    
#elif defined KY_VERSION
    
#elif defined IT_VERSION
    
#elif defined HM_VERSION
    
#elif defined C3737_VERSION
    
#elif defined XY_VERSION
    
#elif defined VTCID_VERSION
    
#elif defined IIAPPLE_VERSION
    
#endif
}

void ChannelHelper::loginVerifyRequest()
{
    CHANNELCALLBACK.isLogin = true;
    //do verify
    string user_id = "";
    string token_key = "";
    if (CHANNELCALLBACK.user_ID)
        user_id = [CHANNELCALLBACK.user_ID UTF8String];
    
    if (CHANNELCALLBACK.token_Key)
        token_key = [CHANNELCALLBACK.token_Key UTF8String];
    
    CPPlatformMnger.setStringData(CPPlatformData::UIN, user_id);
    CPPlatformMnger.setStringData(CPPlatformData::SESSION_ID, token_key);
    CPPlatformMnger.setStringData(CPPlatformData::DEVICE_ID,CHANNELHELPER->getDeviceID());
    LoginHelper::loginRequest();
    
    showToolBar();
}
void ChannelHelper::getOrderIdRequest(const char* product_id,float amount,int count)
{
    CHANNELCALLBACK.product_ID = [NSString stringWithUTF8String:product_id];
    CHANNELCALLBACK.price = amount;
    //get order
}

void ChannelHelper::payFailedWithError(const char* orderID,int errorCode)
{
    NSString* oID = @"";
    if (orderID) {
        oID = [NSString stringWithFormat:@"订单号:%s",orderID];
    }
    NSString* msg = [NSString stringWithFormat:@"%@ %@ Error=%d",NSLocalizedStringFromTable(@"failedToBuy", @"Local", nil),oID,errorCode];
    UIAlertView *alert = [[UIAlertView alloc]initWithTitle:nil message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
    [alert show];
    [alert release];
}
void ChannelHelper::createOrderFailedWithError(const char* errorInfo)
{
    NSString* errInfo = @"";
    if (errorInfo) {
        errInfo = [NSString stringWithFormat:@"%@",[NSString stringWithUTF8String:errorInfo]];
    }
#ifndef TB_VERSION
    NSString* msg = [NSString stringWithFormat:@"创建订单失败 %@",errInfo];
    UIAlertView *alert = [[UIAlertView alloc]initWithTitle:nil message:msg delegate:nil cancelButtonTitle:NSLocalizedStringFromTable(@"OK", @"Local", nil) otherButtonTitles: nil];
    [alert show];
    [alert release];
#endif
}
void ChannelHelper::loginFailedWithError(const char* errorInfo)
{
#if defined (C91_VERSION)||defined (PP_VERSION)||defined (TB_VERSION)
        CHANNELHELPER->logout();
        
        CHANNELCALLBACK.isLogin = false;
        /*
#ifdef CP_NETWORK_VERSION
        NSString* errMsg = @"登录验证失败，";
#else
        NSString* errMsg = @"登录验证失败，您可以继续游戏，但使用部分功能时可能需要重新登录";
#endif
        
        NSString* errInfo = @"";
        if (errorInfo) {
            errInfo = [NSString stringWithFormat:@"%@",[NSString stringWithUTF8String:errorInfo]];
        }
        NSString* msg = [NSString stringWithFormat:@"%@ %@",errMsg,errInfo];
        UIAlertView *alert = [[UIAlertView alloc]initWithTitle:nil message:msg delegate:nil cancelButtonTitle:NSLocalizedStringFromTable(@"OK", @"Local", nil) otherButtonTitles: nil];
        [alert show];
        [alert release];
    */
#endif
}
void ChannelHelper::loginFailed(){
//    CHANNELHELPER->logout();
    CHANNELCALLBACK.isLogin = false;
}
void ChannelHelper::connectGM()
{
    NSLog(@"%s",__FUNCTION__);
    
    //GameRole *myRole = GameData::getMyRole();
    
    int cur_time = ActivityData::getWorldTime();
    int aid,pid,svr = 0;
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
    pid = HeroData::getPID();
    svr = LoginHelper::getSavedServerId();
    if (aid<0) aid=0;
    if (pid<0) pid=0;
    if (svr<0) svr=0;
    int channelid = CHANNELHELPER->getPlatform();
    
    std::string playName;
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::getString(pid, CPLoginData::PLAYER_NAME, playName);
    
    std::string url = "http://ydl.kf.3737.com/ydl_client.index.php";
    std::string tuname = "?uname=";
    std::string tsid = "&sid=";
    std::string ttime = "&time=";
    std::string tuid = "&uid=";
    std::string topenid = "&openid=";
    std::string tac = "&ac=";
    std::string tcid = "&cid=";
    std::string tsign = "&sign=";
    
    NSString* namestr = [NSString stringWithUTF8String:playName.c_str()];
    NSString *result = (NSString *)CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,(CFStringRef)namestr,NULL,CFSTR("!*'();:@&=+$,/?%#[]"),kCFStringEncodingUTF8);
    [result autorelease];
    
    std::string uname = [result UTF8String];
    std::string sid = StringUtils::toString(svr);
    std::string time = StringUtils::toString(cur_time);
    std::string uid = StringUtils::toString(pid);
    std::string openid = StringUtils::toString(aid);
    std::string ac = StringUtils::toString(1);
    std::string cid = StringUtils::toString(channelid);
    std::string str_md5 = "";
    std::string key = "ydl_fdsfkl23ds43243lkydl";
    if (channelid==1)
    {
        str_md5 = playName+openid+uid+sid+time+key ;
    }
    else
    {
        str_md5 = playName+openid+uid+sid+time+cid+key ;
    }
    
    std::string sign = MD5::MD5(str_md5).toString();
    url = url+tuname+uname+tsid+sid+ttime+time+tuid+uid+topenid+openid+tac+ac+tcid+cid+tsign+sign;
    NSLog(@"___gm url:%s",url.c_str());
    
    BDWebView* m_webView = [BDWebView instance] ;
    [m_webView showWebView];
    [m_webView updateURL:url.c_str()];
}
#pragma mark -------------------------------quick play---------------------------------------------
void ChannelHelper::appInit()
{
    mIsInLogin = false;
    //    mIsQuickPlay = CHANNELHELPER->isQuickPlay();
    //    mQuickUserName = CHANNELHELPER->getQuickUserName();
    //    mQuickPassword = CHANNELHELPER->getQuickPassword();
    //    mQuickUid = CHANNELHELPER->getQuickUid();
#if defined APPSTORE_VERSION
    /*
    WGPlatform *plat = WGPlatform::GetInstance();
    MyObserver  *pObserver =(MyObserver  *)plat->GetObserver();
    if(!pObserver){
        pObserver = new MyObserver();
        plat -> WGSetObserver(pObserver);
    }
     */
#endif
}
void ChannelHelper::rmvQuickUser()
{
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    [userdefault setBool:NO forKey:@"IsQuickPlay"];
    [userdefault removeObjectForKey:@"QuickUserName"];
    [userdefault removeObjectForKey:@"QuickPassword"];
    [userdefault removeObjectForKey:@"QuickUid"];
    [userdefault synchronize];
}
void ChannelHelper::setQuickUser(std::string username,std::string password,std::string uid)
{
    if(username.empty()||password.empty()||uid.empty())
    {
        username = "";
        password = "";
        uid = "";
    }
    bool mIsQuickPlay = true;
    std::string mQuickUserName = username;
    std::string mQuickPassword = password;
    std::string mQuickUid = uid;
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    [userdefault setBool:mIsQuickPlay forKey:@"IsQuickPlay"];
    [userdefault setObject:[NSString stringWithUTF8String:mQuickUserName.c_str()] forKey:@"QuickUserName"];
    [userdefault setObject:[NSString stringWithUTF8String:mQuickPassword.c_str()] forKey:@"QuickPassword"];
    [userdefault setObject:[NSString stringWithUTF8String:mQuickUid.c_str()] forKey:@"QuickUid"];
    [userdefault synchronize];
}
bool ChannelHelper::isQuickPlay(std::string uname)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    BOOL isQuickPlay = [userdefault boolForKey:@"IsQuickPlay"];
    if (!isQuickPlay) {
        isQuickPlay = false;
    }
    if (uname.empty()||uname.length()<=0) {
        return isQuickPlay;
    }
    std::string quickName = getQuickUserName();
    if (quickName==uname&&isQuickPlay) {
        return isQuickPlay;
    }
#endif
    return false;
}
std::string ChannelHelper::getQuickUserName()
{
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    NSString* username = [userdefault objectForKey:@"QuickUserName"];
    if (!username||username.length<=0) {
        username = @"";
    }
    std::string mQuickUserName = [username UTF8String];
    return mQuickUserName;
}
std::string ChannelHelper::getQuickPassword()
{
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    NSString* password = [userdefault objectForKey:@"QuickPassword"];
    if (!password||password.length<=0) {
        password = @"";
    }
    std::string mQuickPassword = [password UTF8String];
    return mQuickPassword;
}
std::string ChannelHelper::getQuickUid()
{
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    NSString* uid = [userdefault objectForKey:@"QuickUid"];
    if (!uid||uid.length<=0) {
        uid = @"";
    }
    std::string mQuickUid = [uid UTF8String];
    return mQuickUid;
}
bool ChannelHelper::isBindInGame()
{
    //    int svr = LoginHelper::getSavedServerId();
    //    if (svr<0) svr=0;
    //    return (svr!=0);
    return !mIsInLogin;
}
void ChannelHelper::setInLogin(bool inLogin)
{
    mIsInLogin = inLogin;
}
#pragma mark -------------------------------msdk---------------------------------------------
#if defined APPSTORE_VERSION
void ChannelHelper::QQAuth()
{
    WGPlatform* plat = WGPlatform::GetInstance();
    //拉起平台选择
    //MyObserver* ob = new MyObserver();
    //ob->setViewcontroller(self);
    //plat->WGSetObserver(ob);
    plat->WGSetPermission(eOPEN_ALL);
    plat->WGLogin(ePlatform_QQ);
    
}
void ChannelHelper::WXAuth()
{
    WGPlatform* plat = WGPlatform::GetInstance();
    //MyObserver* ob = new MyObserver();
    //plat->WGSetObserver(ob);
    plat->WGLogin(ePlatform_Weixin);
}
#endif
#pragma mark -------------------------------appstore helper---------------------------------------------
void ChannelHelper::onDownload4AppStore()
{
#if defined APPSTORE_VERSION
    NSString* str = [NSString stringWithFormat:@"http://itunes.apple.com/us/app/id%@",@"907368979"];
    [[UIApplication sharedApplication]openURL:[NSURL URLWithString:str]];
#elif defined C3737_VERSION
    NSString* str = @"http://fir.im/7hy6";
    [[UIApplication sharedApplication]openURL:[NSURL URLWithString:str]];
#endif
}
#if defined APPSTORE_VERSION
bool ChannelHelper::checkOrder()
{
    return [CHANNELCALLBACK checkOrder];
}
void ChannelHelper::endPay()
{
    [CHANNELCALLBACK endPay];
}
void ChannelHelper::goBuy(int index)
{
    if (index == Button_QD)
    {
        if(![CHANNELCALLBACK startPay])return;
        CHANNELHELPER->IAPpay(CHANNELHELPER->getCurProductID().c_str());
    }
}
void ChannelHelper::IAPpay(const char* product_id)
{
    if (!product_id) {
        CCLog("appstore pay error: invalid product_id");
        [CHANNELCALLBACK endPay];
        return;
    }
    NSArray *products = @[[NSString stringWithUTF8String:product_id]];
    [[ECPurchase shared] requestProductData:products];
    //[[ECPurchase shared] addPayment:[NSString stringWithUTF8String:product_id.c_str()]];
    //[CHANNELCALLBACK showAlert:@"正在获取商品信息，请勿关闭游戏！"];
}
void ChannelHelper::showTip(std::string note)
{
    if (m_tip==NULL) {
        m_tip = CPTouchTip::create();
        if (m_tip) {
            //            m_tip->setAnchorPoint(ccp(0.5, 0.5));
            //            m_tip->setPosition(ccp(0, 0));
            m_tip->setString(note);
            
            CCDirector::sharedDirector()->getNotificationNode()->addChild(m_tip);
        }else{
            m_tip = NULL;
        }
    }
}
void ChannelHelper::hideTip()
{
    if (m_tip) {
        m_tip->removeFromParent();
        m_tip = NULL;
    }
}
std::string ChannelHelper::getAppStoreVersion()
{
    string url = "https://itunes.apple.com/lookup?id=907368979";
    return "123";
    
    CCHttpRequest* request = new CCHttpRequest();//
    request->setUrl(url.c_str());//
    request->setRequestType(CCHttpRequest::kHttpGet);//
    //request->setResponseCallback(this, httpresponse_selector(Register_3737::onHttpRequestCompleted));//
    CCHttpClient::getInstance()->send(request);//
    request->release();//
}

bool ChannelHelper::needGoAppStore()
{
    return true;
}
#endif
#pragma mark -------------------------------PP helper---------------------------------------------
#if defined PP_VERSION
void ChannelHelper::PPInitSDK(int appID,const char* appKey)
{
    /**
     *必须写在程序window初始化之后。详情请commad + 鼠标左键 点击查看接口注释
     *初始化应用的AppId和AppKey。从开发者中心游戏列表获取（https://pay.25pp.com）
     *设置是否打印日志在控制台,[发布时请务必改为NO]
     *设置充值页面初始化金额,[必须为大于等于1的整数类型]
     *设置游戏客户端与游戏服务端链接方式是否为长连接【如果游戏服务端能主动与游戏客户端交互。例如发放道具则为长连接。此处设置影响充值并兑换的方式】
     *用户注销后是否自动push出登陆界面
     *是否开放充值页面【操作在按钮被弹窗】
     *若关闭充值响应的提示语
     *初始化SDK界面代码
     */
    
    
    [[PPAppPlatformKit sharedInstance] setAppId:appID AppKey:[NSString stringWithUTF8String:appKey]];
    [[PPAppPlatformKit sharedInstance] setIsNSlogData:NO];
    [[PPAppPlatformKit sharedInstance] setRechargeAmount:10];
    [[PPAppPlatformKit sharedInstance] setIsLongComet:YES];
    [[PPAppPlatformKit sharedInstance] setIsLogOutPushLoginView:YES];
    [[PPAppPlatformKit sharedInstance] setIsOpenRecharge:YES];
    //[[PPAppPlatformKit sharedInstance] setCloseRechargeAlertMessage:@"关闭充值提示语"];
    [PPUIKit sharedInstance];
    
    
    [PPUIKit setIsDeviceOrientationLandscapeLeft:YES];
    [PPUIKit setIsDeviceOrientationLandscapeRight:YES];
    [PPUIKit setIsDeviceOrientationPortrait:NO];
    [PPUIKit setIsDeviceOrientationPortraitUpsideDown:NO];
}
void ChannelHelper::PPShowLogin()
{
    [[PPAppPlatformKit sharedInstance] showLogin];
}
bool ChannelHelper::PPIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::PPShowCenter()
{
    [[PPAppPlatformKit sharedInstance] showCenter];
}
void ChannelHelper::PPPay(float amount,const char* orderID,const char* paydes)
{
    //int time = [[NSDate date] timeIntervalSince1970];
    //NSString *billNO = [NSString stringWithFormat:@"%d",time];
    NSString *billNO = [NSString stringWithUTF8String:orderID];
    [[PPAppPlatformKit sharedInstance] exchangeGoods:amount BillNo:billNO BillTitle:[NSString stringWithUTF8String:paydes] RoleId:@"0" ZoneId:0];
}

void ChannelHelper::PPAlixPayResult(const char* vUrl)
{
    NSURL*url = [NSURL URLWithString:[NSString stringWithUTF8String:vUrl]];
    [[PPAppPlatformKit sharedInstance] alixPayResult:url];
}
#endif

#pragma mark -------------------------------tongbu helper---------------------------------------------
#if defined TB_VERSION
/* 初始化平台
 * appid：应用ID，由后台获取
 * orientation：平台初始方向
 * isAcceptWhenFailed：检查更新失败后是否允许进入游戏
 */
void ChannelHelper::TBInitSDK(int appID,bool isAcceptWhenFailed){
    /*开启调试模式，用以调试检查更新流程（测试充值无需开启），正式发布前需要注释该行代码*/
    //[[TBPlatform defaultPlatform] TBSetDebugMode:0];

    [[TBPlatform defaultPlatform] TBInitPlatformWithAppID:appID
                                        screenOrientation:UIInterfaceOrientationLandscapeLeft
                          isContinueWhenCheckUpdateFailed:NO];
    [[TBPlatform defaultPlatform] TBSetAutoRotation:false];
}
/*登录*/
int ChannelHelper::TBLogin(int tag){
    return [[TBPlatform defaultPlatform] TBLogin:0];
}
/*注销*/
int ChannelHelper::TBLogout(int tag){
    return [[TBPlatform defaultPlatform] TBLogout:tag];
}
/*切换帐号*/
int ChannelHelper::TBSwitchAccount(){
    [[TBPlatform defaultPlatform] TBSwitchAccount];
    return 1;
}
/*是否已登录*/
bool ChannelHelper::TBIsLogined(){
    return [[TBPlatform defaultPlatform] TBIsLogined];
}
/*开启调试模式*/
void ChannelHelper::TBSetDebug(){
    [[TBPlatform defaultPlatform] TBSetUpdateDebugMode:0];
}
/*获取会话ID*/
const char* ChannelHelper::TBSessionID(){
    return [[TBPlatform defaultPlatform] sessionID].UTF8String;
}
/*获取用户ID*/
const char* ChannelHelper::TBUserID(){
    return [[TBPlatform defaultPlatform] userID].UTF8String;
}
/*获取用户昵称*/
const char* ChannelHelper::TBNickName(){
    return [[TBPlatform defaultPlatform] nickName].UTF8String;
}
/*检查更新*/
int ChannelHelper::TBCheckUpdate(){
    return 0;//[[TBPlatform defaultPlatform] TBAppVersionUpdate:0 delegate:CHANNELCALLBACK];
}
/*支付（指定金额）*/
int ChannelHelper::TBUnipayForCoinWithOrder(const char *order,float amount,const char *paydes){
    return [[TBPlatform defaultPlatform] TBUniPayForCoin:[NSString stringWithUTF8String:order]
                                              needPayRMB:amount
                                          payDescription:[NSString stringWithUTF8String:paydes]
                                                delegate:CHANNELCALLBACK];
}
/*支付（玩家自选金额）*/
int ChannelHelper::TBUnipayForCoinWhthOrder(const char *order,const char *paydes){
    return [[TBPlatform defaultPlatform] TBUniPayForCoin:[NSString stringWithUTF8String:order]
                                          payDescription:[NSString stringWithUTF8String:paydes]];
}
/*查询订单结果*/
int ChannelHelper::TBCheckOrder(const char *order){
    return [[TBPlatform defaultPlatform] TBCheckPaySuccess:[NSString stringWithUTF8String:order]
                                                  delegate:CHANNELCALLBACK];
}
/*进入个人中心*/
int ChannelHelper::TBEnterUserCenter(int tag){
    [[TBPlatform defaultPlatform] TBEnterUserCenter:0];
    return 1;
}
/*进入游戏推荐中心*/
int ChannelHelper::TBEnterGameCenter(int tag){
    [[TBPlatform defaultPlatform] TBEnterAppCenter:0];
    return 1;
}
/*进入论坛*/
int ChannelHelper::TBEnterBBS(int tag){
    return [[TBPlatform defaultPlatform] TBEnterAppBBS:0];
}
#endif
#pragma mark -------------------------------91 helper---------------------------------------------
#if defined C91_VERSION
void ChannelHelper::NDInitSDK(int appID,const char* appKey)
{
    //初始化
    NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
	cfg.appid = appID;
	cfg.appKey = [NSString stringWithUTF8String:appKey];
    //这里以竖屏演示下orientation的设置，默认的为空表示不设置
    cfg.orientation = UIDeviceOrientationLandscapeRight;
    cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_NORMAL;
	[[NdComPlatform defaultPlatform] NdInit:cfg];
    
    //设定平台为横屏或者竖屏
	[[NdComPlatform defaultPlatform] NdSetScreenOrientation:UIInterfaceOrientationLandscapeLeft];
	//设置是否自动旋转
	[[NdComPlatform defaultPlatform] NdSetAutoRotation:NO];
    
    //[[NdComPlatform defaultPlatform] NdSetScreenOrientation:UIInterfaceOrientationLandscapeLeft];
    //[[NdComPlatform defaultPlatform] NdSetAutoRotation:NO];
    
#if defined DEBUG
    //[[NdComPlatform defaultPlatform] NdSetDebugMode:1];
#endif
}
void ChannelHelper::NDLogin(int type)
{
    //[[NdComPlatform defaultPlatform] NdLogin:type];
    //if (![[NdComPlatform defaultPlatform]isLogined]) {
        [[NdComPlatform defaultPlatform] NdLogin:type];
    //}
}
bool ChannelHelper::NDIsLogin()
{
    return [[NdComPlatform defaultPlatform]isLogined];
}
void ChannelHelper::NDLogout(int type)
{
    [[NdComPlatform defaultPlatform] NdLogout:type];
}
void ChannelHelper::NDPause()
{
    [[NdComPlatform defaultPlatform] NdPause];
}

void ChannelHelper::NDPayForGoods(float amount,const char* orderID,const char* productID,int count)
{
        
    if (![[NdComPlatform defaultPlatform]isLogined]) {
        [[NdComPlatform defaultPlatform] NdLogin:0];
        return;
    }
    string proStr = productID;
    NSString* proName  = @"元宝";//[NSString stringWithFormat:@"%d元宝",count];
  
    NdBuyInfo *buyInfo = [[NdBuyInfo new] autorelease];
    buyInfo.cooOrderSerial = [NSString stringWithUTF8String:orderID];
    buyInfo.productPrice = (float)amount/count;
    buyInfo.productOrignalPrice = (float)amount/count;
    buyInfo.productCount = count;
    buyInfo.productId = [NSString stringWithUTF8String:productID];
    buyInfo.productName = proName;
    buyInfo.payDescription = @"91";
        
    int res = [[NdComPlatform defaultPlatform] NdUniPayAsyn:buyInfo];
    if (res < 0)
    {
        CCLOG("输入参数有错!无法提交购买请求 res=%d",res);
        //输入参数有错!无法提交购买请求
        //connectFailed = YES;
        //[self connectFailed];
    }
    else {
        //[self addRecord:buyInfo.cooOrderSerial];
    }
        
}
void ChannelHelper::NDPayForCoin(float amount,const char* orderID)
{
    [[NdComPlatform defaultPlatform] NdUniPayForCoin:[NSString stringWithUTF8String:orderID] needPayCoins:amount payDescription:@""];
}
//好友
void ChannelHelper::NDEnterFriendsCenter()
{
    [[NdComPlatform defaultPlatform] NdEnterFriendCenter:0];
}
//社区
void ChannelHelper::NDEnterPlatform()
{
    [[NdComPlatform defaultPlatform] NdEnterPlatform:0];
}
//论坛
void ChannelHelper::NDEnterBBS()
{
    [[NdComPlatform defaultPlatform] NdEnterAppBBS:0];
}
//赚金币
void ChannelHelper::NDEnterEarnGold()
{
    //[[NdComPlatform defaultPlatform] NdEnterAppPromotionList:0];
}
//意见反馈
void ChannelHelper::NDEnterFeedback()
{
    [[NdComPlatform defaultPlatform] NdUserFeedBack];
}
#endif
#pragma mark -------------------------------kuaiyong helper---------------------------------------------
#if defined KY_VERSION
void ChannelHelper::KYInitSDK(int appID,const char* appKey)
{
    [KYSDK instance];
}
void ChannelHelper::KYShowLogin()
{
    //if(CHANNELHELPER->isLogin())
    //    return;
    [[KYSDK instance] changeLogOption:KYLOG_OFFGAMENAME];
    [[KYSDK instance] showUserView];
}
void ChannelHelper::KYShowUserView()
{
    [[KYSDK instance] setUpUser];
}
bool ChannelHelper::KYIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::KYShowLogout()
{
    [[KYSDK instance] userLogOut];
    [[KYSDK instance] userBackToLog];
}
void ChannelHelper::KYLogout()
{
    [[KYSDK instance] userLogOut];
}
void ChannelHelper::KYAutoLogin()
{
    [[KYSDK instance] logWithLastUser];
}
void ChannelHelper::KYShowPay(const char *dealseq, const char *fee, const char *subject)
{
    //demo
    //[[KYSDK instance] showPayWith:randomStr fee:[money text] game:@"957" gamesvr:@"" subject:@"大礼包" md5Key:@"3PXupxWAJoR5ULbgU6J82FLZxamxYJwi" appScheme:@"kytestappscheme"];
    NSString* gameStr = @"5493";
    NSString* md5Key = @"dECb7DmHiiqTfy9lCLv4F3FrRj6hutmH";
    NSString* appScheme = @"com.ceapon.fire.ky";

    [[KYSDK instance]showPayWith:[NSString stringWithUTF8String:dealseq]
                             fee:[NSString stringWithUTF8String:fee]
                            game:gameStr
                         gamesvr:@""
                         subject:[NSString stringWithUTF8String:subject]
                          md5Key:md5Key
                          userId:@""
                       appScheme:appScheme];
    
//    [[KYSDK instance] showPayWith:[NSString stringWithUTF8String:dealseq]
//                              fee:[NSString stringWithUTF8String:fee]
//                             game:gameStr//kuaiyong获取
//                          gamesvr:@""
//                          subject:[NSString stringWithUTF8String:subject]
//                           md5Key:md5Key//kuaiyong获取
//                           userId:@""];
}
#endif
#pragma mark -------------------------------itools helper---------------------------------------------
#if defined IT_VERSION
void ChannelHelper::itoolsInitSDK(int appID,const char* appKey)
{
    //设置充值平台分配的appid和appkey
    [HXAppPlatformKitPro setAppId:appID appKey:[NSString stringWithUTF8String:appKey]];
    //设置支持的方向，根据自己App支持的方向做设置。
    [HXAppPlatformKitPro setSupportOrientationPortrait:NO portraitUpsideDown:NO landscapeLeft:YES landscapeRight:YES];
    //设置自动更新，默认NO，不检查
    //[HXAppPlatformKitPro setAutoCheckAppUpdateEnabled:YES force:true];
}
void ChannelHelper::itoolsShowLogin()
{
    [HXAppPlatformKitPro showLoginView];
}
void ChannelHelper::itoolsShowPlatformView()
{
    [HXAppPlatformKitPro showPlatformView];
}
bool ChannelHelper::itoolsIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::itoolsPay(float amount,const char* orderID,const char* paydes)
{
    //[HXAppPlatformKitPro setPayViewAmount:amount orderIdCom:[NSString stringWithUTF8String:orderID]];
    [HXAppPlatformKitPro payProductWithProductName:[NSString stringWithFormat:[NSString stringWithUTF8String:paydes]] Amount:amount OrderIdCom:[NSString stringWithUTF8String:orderID]];
    CHANNELCALLBACK.payViewOpened = true;
}
/*
 void ChannelHelper::itoolsDirectPay(const char* account,float amount,const char* orderID)
 {
 [HXAppPlatformKitPro setPayViewAccount:[NSString stringWithUTF8String:account] amount:1.0 orderIdCom:[NSString stringWithUTF8String:orderID]];
 }
 */
#endif
#pragma mark -------------------------------i4 helper---------------------------------------------
#if defined I4_VERSION
void ChannelHelper::asInitSDK(int appID,const char* appKey)
{
    [[AsInfoKit sharedInstance] setAppId:appID];
    [[AsInfoKit sharedInstance] setAppKey:[NSString stringWithUTF8String:appKey]];
    [[AsInfoKit sharedInstance] setLogData:NO];// 正式上线必须NO
    [[AsInfoKit sharedInstance] setCloseRecharge:NO];
    [[AsInfoKit sharedInstance] setCloseRechargeAlertMessage:@"充值功能暂时不开放"];
    // 接入sdk时，根据使用的Xcode版本 与 游戏画面的方向更改此处，使用Xcode 6.x.x设置为YES，使用Xcode 5.x.x 设置为NO；游戏画面方向为 横屏 ，设置为 UIInterfaceOrientationMaskLandscape；竖屏，设置为UIInterfaceOrientationMaskPortrait
    [[AsInfoKit sharedInstance] updateSDKOperatingEnvironment:NO andOrientationOfGame:UIInterfaceOrientationMaskLandscape];
    /* @noti  只有余额大于道具金额时候才有客户端回调。余额不足的情况取决与LongComet参数，LongComet = YES，则为充值兑换。
     回调给服务端，LongComet = NO ，则只是打开充值界面
     */
    [[AsInfoKit sharedInstance] setLongComet:YES];
    /*
     解决游戏在iOS 5 上 无法显示爱思充值/支付页面、银联支付页面
     若游戏有根视图控制器（RootViewController），则设置为 self.asViewController(为自己的根视图控制器名称)
     若无根视图控制器，则设置为 nil
     */
    //[[[UIApplication sharedApplication] keyWindow] rootViewController];
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        //[window addSubview: viewController.view];
        AppController* app = (AppController*)[[UIApplication sharedApplication] delegate];
        if (app) {
            //RootViewController* root = (RootViewController*)[app getRootViewController];
            [[AsInfoKit sharedInstance] setRootViewController:[app getRootViewController]];
        }
    }
    else
    {
        // use this method on ios6
        [[AsInfoKit sharedInstance] setRootViewController:[[[UIApplication sharedApplication] keyWindow] rootViewController]];
    }
    [[AsPlatformSDK sharedInstance] checkGameUpdate];
}
void ChannelHelper::asShowLogin()
{
    [[AsPlatformSDK sharedInstance] showLogin];
}
void ChannelHelper::asLogout()
{
    //[[AsPlatformSDK sharedInstance] PPlogout];
}
bool ChannelHelper::asIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::asShowUserCenter()
{
    [[AsPlatformSDK sharedInstance] showCenter];
}
void ChannelHelper::asPay(float amount,const char* orderID)
{
    [[AsPlatformSDK sharedInstance] exchangeGoods:amount BillNo:[NSString stringWithUTF8String:orderID] BillTitle:@"元宝" RoleId:@"" ZoneId:0];
}
#endif
#pragma mark -------------------------------hm helper---------------------------------------------
#if defined HM_VERSION
void ChannelHelper::hmInitSDK(int appID,const char* appKey)
{
    /*
    [[IPAYiAppPay sharediAppPay] initializeWithAppKey: [NSString stringWithUTF8String:appKey]
                                             andAppID: @"3000766136"//[NSString stringWithFormat:@"%d",appID]
                                           andWaresID: 1
                                     andUIOrientation: UIInterfaceOrientationLandscapeRight
                                        andCPDelegate: CHANNELCALLBACK];
    [[HmcpUpdate sharedUpdate]checkUpdateForTest:NO delegate:CHANNELCALLBACK];
     */
    AppController* app = (AppController*)[[UIApplication sharedApplication] delegate];
    if (app) {
        //RootViewController* root = (RootViewController*)[app getRootViewController];
        UINavigationController* na = [[[UINavigationController alloc]initWithRootViewController:[app getRootViewController]]autorelease];
        if (![[IPAYKit sharedInstance]checkSetOK])
        {
            [[IPAYKit sharedInstance]setAppId:@"3000766136" channel:nil navigation:na];
            [[IPAYKit sharedInstance]setPayDelegate:CHANNELCALLBACK];
            [[IPAYKit sharedInstance]setPrivateKey:[NSString stringWithUTF8String:appKey]];
        }
    }
    
    [[HmcpUpdate sharedUpdate]checkUpdateForTest:NO delegate:CHANNELCALLBACK];
}
void ChannelHelper::hmShowLogin()
{
    /*
    IPAYiAppPay *appPay = [IPAYiAppPay sharediAppPay];
    //[appPay showLoginViewWithLoginDelegate:CHANNELCALLBACK];
    [appPay showLoginViewWithIsForced: YES andLoginDelegate: CHANNELCALLBACK];
    */
    AppController* app = (AppController*)[[UIApplication sharedApplication] delegate];
    if (app) {
        if ([[IPAYKit sharedInstance]checkSetOK])
        {
            [[IPAYKit sharedInstance]makeLoginWithDelegate:CHANNELCALLBACK
                            withCurrentViewControllerClass:NSStringFromClass([[app getRootViewController] class])];
            NSLog(@"_____hmShowLogin success");
        }
    }
    
}
void ChannelHelper::hmLogout()
{
    
}
bool ChannelHelper::hmIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::hmShowUserCenter()
{
    
}
void ChannelHelper::hmPay(float amount,const char* orderID)
{
    /*
    IPAYiAppPayOrder* iAppPayOrder = [[IPAYiAppPayOrder alloc] init];
    iAppPayOrder.exorderno = [NSString stringWithUTF8String:orderID];
    iAppPayOrder.waresid = 1;
    iAppPayOrder.notifyurl = nil;
    iAppPayOrder.price = amount*100;
    iAppPayOrder.cppprivateinfo = nil;
    
    NSString * orderSignature = [[IPAYiAppPay sharediAppPay] getOrderSignature: iAppPayOrder
                                                                     withAppID: nil
                                                                     andAppKey: nil];
    
    [[IPAYiAppPay sharediAppPay] checkoutWithOrder:iAppPayOrder andOrderSignature:orderSignature andPaymentDelegate:CHANNELCALLBACK];
     */
    //long  time=  [[NSDate date]timeIntervalSince1970];
    NSString* appUserId = @"";//[NSString stringWithFormat:@"abcdefg%ld",time];
    NSString* cpPrivateInfo= @"";
    NSString* cpOrderId = [NSString stringWithUTF8String:orderID];
    NSString* notifyUrl = nil;
    int price = amount*100;
    NSInteger wareId = 1;
    
    if ([[IPAYKit sharedInstance]checkSetOK])
    {
        [[IPAYKit sharedInstance] makePayForPrice:price orderId:cpOrderId waresId:wareId notifyUrl:notifyUrl appUserId:appUserId cpPrivate:cpPrivateInfo];
    }
    else
    {
        
    }
}
#endif
#pragma mark -------------------------------3737 helper---------------------------------------------
#if defined C3737_VERSION
void ChannelHelper::c3737InitSDK(int appID,const char* appKey)
{
    [[IPAYiAppPay sharediAppPay] initializeWithAppKey:@"3000811347"
                                             andAppID: @"RERDRTExMTExMDBCNTQxRTFBNEIxNDk1NDNFNjlEOTMwQzUwODNCN01UUTVNVGs0TXpBeU16QXdOVE0yTVRZNE5ERXJNVFE0T1RJeU9ETXlPVFUxTkRBek9UVXpNVFl4TWpZM05qVTBNemcwT1RFNE16QXlPVGcz"
                                           andWaresID: 1
                                     andUIOrientation: UIInterfaceOrientationLandscapeRight
                                        andCPDelegate: CHANNELCALLBACK];
}
void ChannelHelper::c3737ShowLogin()
{
    LoginHelper::switchView(LoginView::ios_3737_login);
}
void ChannelHelper::c3737Logout()
{
    
}
bool ChannelHelper::c3737IsLogin()
{
    int aid,pid,svr = 0;
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
    pid = HeroData::getPID();
    svr = LoginHelper::getSavedServerId();
    if (aid<0) aid=0;
    if (pid<0) pid=0;
    if (svr<0) svr=0;
    if (aid==0||pid==0||svr==0) {
        return false;
    }
    return true;
}
void ChannelHelper::c3737ShowUserCenter()
{
    
}
void ChannelHelper::c3737Pay(float amount,const char* orderID)
{
    IPAYiAppPayOrder* iAppPayOrder = [[[IPAYiAppPayOrder alloc] init]autorelease];
    iAppPayOrder.exorderno = [NSString stringWithUTF8String:orderID];
    iAppPayOrder.waresid = 1;
    iAppPayOrder.notifyurl = nil;
    iAppPayOrder.price = amount*100;
    iAppPayOrder.cppprivateinfo = nil;
    
    NSString * orderSignature = [[IPAYiAppPay sharediAppPay] getOrderSignature: iAppPayOrder
                                                                     withAppID: @"3000811347"
                                                                     andAppKey: @"RERDRTExMTExMDBCNTQxRTFBNEIxNDk1NDNFNjlEOTMwQzUwODNCN01UUTVNVGs0TXpBeU16QXdOVE0yTVRZNE5ERXJNVFE0T1RJeU9ETXlPVFUxTkRBek9UVXpNVFl4TWpZM05qVTBNemcwT1RFNE16QXlPVGcz"];
    
    [[IPAYiAppPay sharediAppPay] checkoutWithOrder:iAppPayOrder
                                 andOrderSignature:orderSignature
                                andPaymentDelegate:CHANNELCALLBACK];
}
#endif
#pragma mark -------------------------------xy helper---------------------------------------------
#if defined XY_VERSION
void ChannelHelper::xyInitSDK(int appID,const char* appKey)
{
    // SDK初始化, 务必放在SDK其他接口调用之前
    // isContinueWhenCheckUpdateFailed 传YES, 因网络错误获取更新信息失败情况下，强制更新可能失败。 传NO则必须强制更新之后才会开始游戏
    [[XYPlatform defaultPlatform] initializeWithAppId:[NSString stringWithFormat:@"%d",appID]
                                               appKey:[NSString stringWithUTF8String:appKey] isContinueWhenCheckUpdateFailed:YES];
    [XYPlatform defaultPlatform].appScheme = @"com.ceapon.fire.xy";
    
    // 设置 平台页面 屏幕方向，
    // 1、其中设置的方向需要在 app plist文件Supported interface orientations 中支持，否则会Assert
    // 2、UIInterfaceOrientation, 设置 UIInterfaceOrientationLandscapeLeft 或者 UIInterfaceOrientationLandscapeRight，平台页面仅支持横屏幕。
    // 3、设置 UIInterfaceOrientationPortrait ，平台仅支持Portrait方向
    // 4、可不设置，平台页面会根据设备方向自适应
    //    [[XYPlatform defaultPlatform] XYSetScreenOrientation:UIInterfaceOrientationLandscapeLeft];
    
    // 默认为正式环境, 即为NO, 测试环境为 YES
    //[[XYPlatform defaultPlatform] XYSetDebugModel:YES];
    
    //打印log到控制台， 设置方便查看日志，可不设置
    //[[XYPlatform defaultPlatform] XYSetShowSDKLog:YES];
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
}
void ChannelHelper::xyShowLogin()
{
    [[XYPlatform defaultPlatform] XYUserLogin:0];
}
void ChannelHelper::xyLogout()
{
    [[XYPlatform defaultPlatform] XYLogout:0];
}
bool ChannelHelper::xyIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::xyShowUserCenter()
{
    [[XYPlatform defaultPlatform] XYEnterUserCenter:0];
}
void ChannelHelper::xyPay(float amount,const char* orderID)
{
    [[XYPlatform defaultPlatform] XYPayWithAmount:[NSString stringWithFormat:@"%.02f",amount] appServerId:@"0" appExtra:[NSString stringWithUTF8String:orderID] delegate:CHANNELCALLBACK];
}
#endif
#pragma mark -------------------------------VTCid helper---------------------------------------------
#if defined VTCID_VERSION
void ChannelHelper::vtcidInitSDK(int appID,const char* appKey)
{
    [LibVTCid initWithEnvironment:ENV_LIVE];
    [[LibVTCid shareInstance] setDelegate:CHANNELCALLBACK];
    [[LibVTCid shareInstance] setGoogleID:@"722383700035-8go8k5h3q81snfuj5fjqnk51v2o50ukj.apps.googleusercontent.com"];
}
void ChannelHelper::vtcidShowLogin()
{
    [[LibVTCid shareInstance] showLoginView:YES LoginMode:LOGIN_MODE_FULL];
}
void ChannelHelper::vtcidLogout()
{
    [[LibVTCid shareInstance] logout];
}
bool ChannelHelper::vtcidIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::vtcidShowUserCenter()
{
    
}
void ChannelHelper::vtcidPay(float amount,const char* orderID)
{
    [[LibVTCid shareInstance] setAccountID:[CHANNELCALLBACK.user_ID longLongValue]];
    [[LibVTCid shareInstance] setGameToken:[CHANNELCALLBACK getOrderID]];
    //[[LibVTCid shareInstance] setAddr:123456];
    
    [[LibVTCid shareInstance] showTopupView];
}
#endif
#pragma mark -------------------------------IIAPPLE callback---------------------------------------------
#if defined IIAPPLE_VERSION
void ChannelHelper::iiappleInitSDK(int appID,const char* appKey)
{
    NSDictionary* infoDic = [[NSBundle mainBundle] infoDictionary];
    NSString* appVersion = [infoDic objectForKey:@"CFBundleShortVersionString"];
    NSDictionary* dic=[NSDictionary dictionaryWithObjectsAndKeys:
                       @"c46ed9f6037888699f4dde6698ebeae3",@"gameKey",
                       @"1001000101",@"channelId",
                       @"0",@"isVer",
                       @"0",@"isShowATView",
                       @"com.ceapon.fire-iapple",@"alipayScheme",
                       @"e08e76fa335e1e2113a1fea8b074d441",@"cuKey",
                       appVersion,@"gameVersion",
                       @"0",@"isRepeatPay",
                       nil];
    [IIApple initIiappleWithDic:dic];//sdk初始化
    [IIApple checkUpdate];//检查版本更新
}
void ChannelHelper::iiappleShowLogin()
{
    [IIApple doLogin];
}
void ChannelHelper::iiappleLogout()
{
    [IIApple logout];
}
bool ChannelHelper::iiappleIsLogin()
{
    return CHANNELCALLBACK.isLogin;
}
void ChannelHelper::iiappleShowUserCenter()
{
    [IIApple pushUserCenterView];
}
void ChannelHelper::iiapplePay(float amount,const char* orderID)
{
    [IIApple doPayWithAmount:amount
                 productName:@""
                      extend:[NSString stringWithUTF8String:orderID]];
}
#endif