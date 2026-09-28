//
//  MyObserver.cpp
//  WGFrameworkDemo
//
//  Created by fly chen on 2/22/13.
//  Copyright (c) 2013 tencent.com. All rights reserved.
//

#include "MyObserver.h"

#ifdef FRAMEWORK_RESOURCE
#import "WGPublicDefine.h"
#import "WGPlatform.h"
#import "WGCommon.h"
#else
#import <WGPlatform/WGPublicDefine.h>
#import <WGPlatform/WGPlatform.h>
#import <WGPlatform/WGCommon.h>
#endif
#import "ChannelHelper.h"
#import "ChannelCallBack.h"

void MyObserver::OnLoginNotify(LoginRet& loginRet)
{
    NSString *string = [NSString stringWithCString:(const char*)loginRet.desc.c_str() encoding:NSUTF8StringEncoding];
    NSLog(@"string == %@",string);
    NSLog(@"MyObserver  OnLoginNotify loginRet.flag = %d,loginRet.desc = %s",loginRet.flag,loginRet.desc.c_str());
    
    WGPlatform* plat = WGPlatform::GetInstance();
    LoginRet ret;
    std::string registerId = plat->WGGetRegisterChannelId();
    int retCode = plat->WGGetLoginRecord(ret);
    
    if(loginRet.flag==eFlag_Succ){ //登录成功
        
        NSLog(@"MyObserver  OnLoginNotify  eFlag_Succ loginRet.openid= %s",loginRet.open_id.c_str());
        
        std::string openId = loginRet.open_id;
        std::string refreshToken;
        std::string accessToken;
        std::string paytoken;
        if(ePlatform_Weixin == retCode)
        {
            for(int i=0;i< loginRet.token.size();i++)
            {
                TokenRet* pToken = & loginRet.token[i];
                if(eToken_WX_Access == pToken->type)
                {
                    accessToken = pToken->value;
                }
                else if (eToken_WX_Refresh == pToken->type)
                {
                    refreshToken = pToken->value;
                }
            }
        }
        else if(ePlatform_QQ == retCode)
        {
            for(int i=0;i< loginRet.token.size();i++)
            {
                TokenRet* pToken = & loginRet.token[i];
                if(eToken_QQ_Pay == pToken->type)
                {
                    paytoken = pToken->value;
                }
                else if (eToken_QQ_Access == pToken->type)
                {
                    accessToken = pToken->value;
                }
            }
        }
        CHANNELCALLBACK.user_ID = [NSString stringWithUTF8String:openId.c_str()];
        CHANNELCALLBACK.token_Key = [NSString stringWithUTF8String:openId.c_str()];
        CHANNELHELPER->loginVerifyRequest();
    }
    
    
    //[view1Controller setLogInfo:@"登录成功"];
}

void MyObserver::OnShareNotify(ShareRet& shareRet)
{
    
    NSLog(@"MyObserver  OnShareNotify shareRet.erroCode = %d,shareRet.desc = %s",shareRet.flag,shareRet.desc.c_str());
    if (eFlag_Succ == shareRet.flag)
    {
        //[view1Controller setLogInfo:@"分享成功"];
    }
    else if(eFlag_WX_UserCancel == shareRet.flag || eFlag_QQ_UserCancel == shareRet.flag)
    {
        //[view1Controller setLogInfo:@"用户取消分享"];
    }
    
}

void MyObserver::OnWakeupNotify(WakeupRet& wakeupRet)
{
    switch (wakeupRet.flag) {
        case eFlag_Succ:
            //[view1Controller setLogInfo:@"唤醒成功"];
            break;
        case eFlag_NeedLogin:
            //[view1Controller setLogInfo:@"异帐号发生，需要进入登录页"];
            break;
        case eFlag_UrlLogin:
            //[view1Controller setLogInfo:@"异帐号发生，通过外部拉起登录成功"];
            
            break;
        case eFlag_NeedSelectAccount:
        {
            //[view1Controller setLogInfo:@"异帐号发生，需要提示用户选择"];
            //UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"异帐号" message:@"发现异帐号，请选择使用哪个帐号登录" delegate:view1Controller cancelButtonTitle:@"不切换，使用原帐号" otherButtonTitles:@"切换外部帐号登录", nil] autorelease];
            //[alert show];
        }
            break;
        case eFlag_AccountRefresh:
            //[view1Controller setLogInfo:@"外部帐号和已登录帐号相同，使用外部票据更新本地票据"];
            break;
        default:
            break;
    }
    if(eFlag_Succ == wakeupRet.flag ||
       eFlag_NeedLogin == wakeupRet.flag ||
       eFlag_UrlLogin == wakeupRet.flag ||
       eFlag_NeedSelectAccount == wakeupRet.flag ||
       eFlag_AccountRefresh == wakeupRet.flag)
    {
        //[view1Controller setLogInfo:@"唤醒成功"];
    }
    else
    {
        //[view1Controller setLogInfo:@"唤醒失败"];
    }
    NSLog(@"MyObserver  OnShareNotify wakeupRet.errCode = %d,wakeupRet.desc = %s",wakeupRet.flag,wakeupRet.desc.c_str());
    NSLog(@"MyObserver  OnShareNotify wakeupRet.platform = %d,wakeupRet.open_id = %s",wakeupRet.platform,wakeupRet.open_id.c_str());
    
}

void MyObserver::OnRelationNotify(RelationRet &relationRet)
{
    NSLog(@"relation callback");
    NSLog(@"count == %lu",relationRet.persons.size());
    for (int i = 0; i < relationRet.persons.size(); i++)
    {
        PersonInfo logInfo = relationRet.persons[i];
        NSLog(@"nikename == %@",[NSString stringWithCString:(const char*)logInfo.nickName.c_str() encoding:NSUTF8StringEncoding]);
        NSLog(@"openid==%@",[NSString stringWithCString:(const char*)logInfo.openId.c_str() encoding:NSUTF8StringEncoding]);
        NSLog(@"gpsCity==%@",[NSString stringWithCString:(const char*)logInfo.gpsCity.c_str() encoding:NSUTF8StringEncoding]);
    }
}


//下单回调
void MyObserver::onOrderFinish(const char *billno,IAPPayRequestInfo &IAPRequestInfo)
{
    
}
void MyObserver::onOrderFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorMessage ,int code)
{
}

//苹果支付回调
void MyObserver::onIAPPayFinish(IAPPayRequestInfo &IAPRequestInfo)
{
}
void MyObserver::onIAPPayFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorString)
{
}

//发货回调
void MyObserver::onDistributeGoodsFinish(IAPPayRequestInfo &IAPRequestInfo)
{
}
void MyObserver::onDistributeGoodsFailue(IAPPayRequestInfo &IAPRequestInfo,const char *errorMessage,int code)
{
}

////补发货的数目回调
//void MyObserver::OnDistributeGoodsWithCount(int code)
//{
//}
void MyObserver::onRestorNon_ConsumableFinish(IAPPayRequestInfo &IAPRequestInfo)
{
}
void MyObserver::onRestorNon_ConsumableFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorMessage,int code)
{
}
void MyObserver::getrestoreInfoFailue(const char* errorString)
{
}

//拉取营销活动回调
void MyObserver::onLaunMpFinish(IAPPayRequestInfo &IAPRequestInfo,IAPMpInfo &mapinfo)
{
    NSLog(@"rate == %s",mapinfo.rate.c_str());
    for (int i = 0; i < mapinfo.mpValueList.size(); i++)
    {
        std::string  key = mapinfo.mpValueList[i];
        NSLog(@"mapinfo key = %s",key.c_str());
    }
    for (int i = 0; i < mapinfo.mpPresentList.size(); i++)
    {
        std::string value = mapinfo.mpPresentList[i];
        NSLog(@"mapinfo value = %s",value.c_str());
    }
    NSLog(@"first_present_count = %s",mapinfo.first_present_count.c_str());
    NSLog(@"begintime = %s",mapinfo.beginTime.c_str());
    NSLog(@"endtime = %s",mapinfo.endTime.c_str());
}
void MyObserver::onLaunMpFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorMessage,int code)
{
}

void MyObserver::onGetProductInfoFailue(IAPPayRequestInfo &IAPRequestInfo)
{
    NSLog(@"come in onGetProductInfoFailue");
}

//网络错误，参数：具体在进行哪一步的时候发生网络错误
//1.下单 2 苹果支付 3 发货
void MyObserver::onNetWorkEorror(int state,IAPPayRequestInfo &IAPRequestInfo)
{
    
}

//登陆态失效回调
void MyObserver::onLoginExpiry(IAPPayRequestInfo &info)
{
    
}
void MyObserver::setViewcontroller(UIViewController *controller)
{
    //viewController = controller;
}

void MyObserver::OnLocationNotify(RelationRet &relationRet) {
    NSLog(@"relation callback");
    NSLog(@"count == %lu",relationRet.persons.size());
    for (int i = 0; i < relationRet.persons.size(); i++)
    {
        PersonInfo logInfo = relationRet.persons[i];
        NSLog(@"nikename == %@",[NSString stringWithCString:(const char*)logInfo.nickName.c_str() encoding:NSUTF8StringEncoding]);
        NSLog(@"openid==%@",[NSString stringWithCString:(const char*)logInfo.openId.c_str() encoding:NSUTF8StringEncoding]);
    }
}

void MyObserver::OnFeedbackNotify(int flag,std::string desc)
{
    NSLog(@"feedback callback:%d, desc:%@",flag, [NSString stringWithCString:(const char*)desc.c_str() encoding:NSUTF8StringEncoding]);
}

std::string MyObserver::OnCrashExtMessageNotify()
{
    return "dsafdasfsafdasdfasdf";
}