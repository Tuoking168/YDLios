//
//  MyObserver.h
//  WGFrameworkDemo
//
//  Created by fly chen on 2/22/13.
//  Copyright (c) 2013 tencent.com. All rights reserved.
//

#ifndef WGFrameworkDemo_MyObserver_h
#define WGFrameworkDemo_MyObserver_h


#ifdef FRAMEWORK_RESOURCE
#import "WGPlatformObserver.h"
#else
#import <WGPlatform/WGPlatformObserver.h>
#endif




//#import "QQViewController.h"

class MyObserver: public WGPlatformObserver
{
    
public:
    //QQViewController* view1Controller;
    void setViewcontroller(UIViewController *controller);
    void OnLoginNotify(LoginRet& loginRet) ;
    void OnShareNotify(ShareRet& shareRet);
    void OnWakeupNotify(WakeupRet& wakeupRet);
    void OnRelationNotify(RelationRet& relationRet);
    
    //下单回调
    void onOrderFinish(const char *billno,IAPPayRequestInfo &IAPRequestInfo);
    void onOrderFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorMessage ,int code);
    
    //苹果支付回调
    void onIAPPayFinish(IAPPayRequestInfo &IAPRequestInfo);
    void onIAPPayFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorString);
    
    //发货回调
    void onDistributeGoodsFinish(IAPPayRequestInfo &IAPRequestInfo);
    void onDistributeGoodsFailue(IAPPayRequestInfo &IAPRequestInfo,const char *errorMessage,int code);
    
    //补发货的数目回调
//    void OnDistributeGoodsWithCount(int code);
    void onRestorNon_ConsumableFinish(IAPPayRequestInfo &IAPRequestInfo);
    void onRestorNon_ConsumableFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorMessage,int code);
    void getrestoreInfoFailue(const char* errorString);
    
    //拉取营销活动回调
    void onLaunMpFinish(IAPPayRequestInfo &IAPRequestInfo,IAPMpInfo &mapinfo);
    void onLaunMpFailue(IAPPayRequestInfo &IAPRequestInfo,const char* errorMessage,int code);
    
    //网络错误，参数：具体在进行哪一步的时候发生网络错误
    //1.下单 2 苹果支付 3 发货
    void onNetWorkEorror(int state,IAPPayRequestInfo &IAPRequestInfo);
    
    //登陆态失效回调
    void onLoginExpiry(IAPPayRequestInfo &info);
    
    //支付时获取IAP产品列表失败时产生的回调
    void onGetProductInfoFailue(IAPPayRequestInfo &IAPRequestInfo);
    
    //定位相关回调
    void OnLocationNotify(RelationRet &relationRet);
    
    //反馈相关回调
    void OnFeedbackNotify(int flag,std::string desc);
    
    // crash时的处理
    std::string OnCrashExtMessageNotify();
};
#endif
