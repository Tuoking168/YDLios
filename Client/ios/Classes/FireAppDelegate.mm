//
//  iphoneAppDelegate.m
//  iphone
//
//  Created by Walzer on 10-11-16.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "FireAppDelegate.h"

#import "EAGLView.h"
#import "cocos2d.h"
#import "entry/AppDelegate.h"
#import "RootViewController.h"

//#import "IOSHelper.h"
#include "../channel/common/ChannelHelper.h"
#import "ChannelCallBack.h"
#include "logic/platform/IPlatform.h"
#include "PlatformDefinition.h"
#ifdef APPSTORE_VERSION
#import  "BaiduMobStat.h"
//#import <libkern/OSMemoryNotification.h>
#endif
#import "ACTReporter.h"
#import "InMobi.h"
#import "IMConstants.h"
#if defined XY_VERSION
#import <XYPlatform/XYPlatform.h>
#elif defined VTCID_VERSION
#import "LibVTCid.h"
#import <FacebookSDK/FacebookSDK.h>
#import <GooglePlus/GooglePlus.h>
#elif defined IIAPPLE_VERSION
#import "IIApple.h"
#endif

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
#ifndef VTCID_VERSION
    [ACTConversionReporter reportWithConversionID:@"974478502" label:@"z50PCN6ruFYQprnV0AM" value:@"1.00" isRepeatable:NO];
    [InMobi initialize:@"84416cc73cf142c28e9271db0bc9d7a6"];
#endif
    //[Crashlytics startWithAPIKey:@"c58e9a754c1bf8d37273600cadc954857c22bb4b"];
    // Override point for customization after application launch.
   
    CHANNELHELPER->initSDK();
    CPPlatformMnger.setIntData(CPPlatformData::PLATFORM_ID,PlatformID::ios);
    
    // Add the view controller's view to the window and display.
    _window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the EAGLView
    EAGLView *__glView = [EAGLView viewWithFrame: [_window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES//GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];
    [__glView setMultipleTouchEnabled:YES];

    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [_window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [_window setRootViewController:viewController];
    }
    
    [_window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    //fix ios8 clippingnode bug
    [__glView layoutSubviews];
    
    cocos2d::CCApplication::sharedApplication()->run();
    
#ifdef APPSTORE_VERSION
    BaiduMobStat* statTracker = [BaiduMobStat defaultStat];
    statTracker.enableExceptionLog = YES; // 是否允许截获并发送崩溃信息，请设置YES或者NO
    statTracker.channelId = @"ios_appstore";//设置您的app的发布渠道
    statTracker.logStrategy = BaiduMobStatLogStrategyAppLaunch;//根据开发者设定的发送策略,发送日志
    statTracker.logSendInterval = 1;  //为1时表示发送日志的时间间隔为1小时,当logStrategy设置为BaiduMobStatLogStrategyCustom时生效
    statTracker.logSendWifiOnly = YES; //是否仅在WIfi情况下发送日志数据
    statTracker.sessionResumeInterval = 10;//设置应用进入后台再回到前台为同一次session的间隔时间[0~600s],超过600s则设为600s，默认为30s
    //statTracker.shortAppVersion  = IosAppVersion; //参数为NSString * 类型,自定义app版本信息，如果不设置，默认从CFBundleVersion里取
    statTracker.enableDebugOn = NO; //调试的时候打开，会有log打印，发布时候关闭
    /*如果有需要，可自行传入adid
     NSString *adId = @"";
     if([[[UIDevice currentDevice] systemVersion] floatValue] >= 6.0f){
     adId = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
     }
     statTracker.adid = adId;
     */
    [statTracker startWithAppId:@"76adbadeec"];//设置您在mtj网站上添加的app的appkey,此处AppId即为应用的appKey
#endif
    return YES;
}
-(UIViewController*)getRootViewController;
{
    return viewController;
}
//支付宝回调
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
	//[[PPAppPlatformKit sharedInstance] alixPayResult:url];
    //91
    //i4
    return [CHANNELCALLBACK aliPay:url];
	//return YES;
}
#if defined APPSTORE_VERSION
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation {
    
    WGPlatform* plat = WGPlatform::GetInstance();
    WGPlatformObserver *ob = plat->GetObserver();
    if (!ob) {
        MyObserver* ob = new MyObserver();
        plat->WGSetObserver(ob);
    }
    return  [WGInterface  HandleOpenURL:url];

}
#endif
#if defined IIAPPLE_VERSION
-(BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    [IIApple application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
    
    return YES;
    
}
#endif
#if defined VTCID_VERSION
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation {
    
    // Call FBAppCall's handleOpenURL:sourceApplication to handle Facebook app responses
    BOOL wasHandled = [FBAppCall handleOpenURL:url sourceApplication:sourceApplication];
    
    // You can add your app-specific url handling code here if needed
    BOOL googleHandle = [GPPURLHandler handleURL:url
                               sourceApplication:sourceApplication
                                      annotation:annotation];
    
    return wasHandled || googleHandle;
}
#endif
- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
    CHANNELHELPER->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */

     if (CCDirector::sharedDirector()->getOpenGLView())
	{
		CCApplication *app = CCApplication::sharedApplication();
		if (app)
		{
			app->applicationDidEnterBackground();
			CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_BACKGROUND, NULL);
			return;
		}
	}
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
       if (CCDirector::sharedDirector()->getOpenGLView()) 
	{
		CCApplication *app = CCApplication::sharedApplication();
		if (app)
		{
			app->applicationWillEnterForeground();
			return;
		}
       }
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

#if defined XY_VERSION
// 该方法用于 银联支付 屏幕适配，Landscape方向游戏必须调用  Portrait方向可不调用
- (NSUInteger) application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
    return [[XYPlatform defaultPlatform] application:application supportedInterfaceOrientationsForWindow:window];
}
#endif
#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
    //NSLog(@"---------------level---------------%d", (int)OSMemoryNotificationCurrentLevel());
}


- (void)dealloc {
    [_window release];
    [super dealloc];
}


@end
