//
//  ChannelCallBack.h
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#import <Foundation/Foundation.h>
//#include <iostream>
#include "logic/platform/IPlatform.h"
#include "PlatformDefinition.h"
#include "scene/LoginHelper.h"
#import <AdSupport/AdSupport.h>

#include "ActivityData.h"
#include "ModuleData.h"
#include "HeroData.h"
#include "StringUtils.h"

#import "FireAppDelegate.h"
#import "RootViewController.h"
#include "userdata/LayoutData.h"
#include "VIPModule.h"
#include "SystemData.h"

#if defined APPSTORE_VERSION
#import "ECPurchase.h"

#import <WGPlatform/WGInterface.h>
#import <WGPlatform/WGPlatform.h>
#import <WGPlatform/WGPublicDefine.h>
#import <WGPlatform/WGGameWebViewController.h>
#import "MyObserver.h"
#elif defined C91_VERSION
#import <NdComPlatform/NDComPlatform.h>
#elif defined PP_VERSION
#import <PPAppPlatformKit/PPAppPlatformKit.h>
#elif defined TB_VERSION
#import <TBPlatform/TBPlatform.h>
#elif defined KY_VERSION
#import "KYMobilePay.h"
#import "KYSDK.h"
#import <AlipaySDK/AlipaySDK.h>
#elif defined IT_VERSION
#import "HXAppPlatformKitPro.h"
#elif defined I4_VERSION
#import "AsInfoKit.h"
#import "AsPlatformSDK.h"
#elif defined HM_VERSION
//#import "IPAYiAppPay.h"
#import <AiBeiFramework/AiBeiFramework.h>
#import <AiBeiFramework/IPAYKit.h>
#import "hmcpupdate.h"
#elif defined C3737_VERSION
#import "IPAYiAppPay.h"
#import "hmcpupdate.h"
#elif defined XY_VERSION
#import <XYPlatform/XYPlatform.h>
#elif defined VTCID_VERSION
#import "LibVTCid.h"
#import <FacebookSDK/FacebookSDK.h>
#import <GooglePlus/GooglePlus.h>
#elif defined IIAPPLE_VERSION
#import "IIApple.h"
#endif

@interface ChannelCallBack : NSObject
#if defined APPSTORE_VERSION
<ECPurchaseProductDelegate,ECPurchaseTransactionDelegate>
#elif defined C91_VERSION
<NdComPlatformUIProtocol_PayAndRecharge>
#elif defined PP_VERSION
<PPAppPlatformKitDelegate>
#elif defined TB_VERSION
<TBCheckOrderDelegate,TBBuyGoodsProtocol>
#elif defined KY_VERSION
<KYSDKDelegate,KYMobilePayDelegate>
#elif defined I4_VERSION
<AsPlatformSDKDelegate>
#elif defined HM_VERSION
<IPAYKitLoginDelegate,IPAYKitPaymentDelegate,HmcpUpdateDelegate,HmcpUpdateDelegate>
#elif defined C3737_VERSION 
<IPAYiAppPayPaymentDelegate, IPAYiAppPayLoginDelegate,IPAYiAppPayContentProviderDelegate>
#elif defined XY_VERSION
<XYCheckPayOrderDelegate, XYPayDelegate>
#elif defined VTCID_VERSION
<VTCIDDelegate>
#elif defined IIAPPLE_VERSION

#endif
{
    
}
@property (nonatomic, copy) NSString *user_ID;
@property (nonatomic, copy) NSString *token_Key;
@property (nonatomic, copy) NSString *product_ID;
@property (nonatomic, assign) float price;
@property (nonatomic, copy) NSString *order_ID;

@property (nonatomic, assign) bool isLogin;
@property (nonatomic, assign) bool payViewOpened;

@property (nonatomic, copy) NSString *rechargeVerifyURL;

@property (nonatomic, retain) UIAlertView *rechargeAlert;
@property (nonatomic, assign) bool isPaying;

+(ChannelCallBack *) sharedCallBack;
- (void)messageBox:(NSString*)stringTip;

- (NSString*)macAddress;

-(void)startListen;

-(void)cleanData;

-(bool)aliPay:(NSURL *)url;
//void aliPay(const char* url);
-(NSString*)getOrderID;

#ifdef APPSTORE_VERSION
-(BOOL)checkOrder;
-(BOOL)startPay;
-(void)endPay;
-(void)showAlert:(NSString*)stringTip;
-(void)hideAlert;
#endif

#define CHANNELCALLBACK [ChannelCallBack sharedCallBack]
@end