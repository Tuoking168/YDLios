//
//  IOSHelper.cpp
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#include "IOSHelper.h"
//#import <PPAppPlatformKit/PPAppPlatformKit.h>
//#import <TBPlatform/TBPlatform.h>
//#import <NdComPlatform/NdComPlatform.h>
//#import "TBAdapter.h"
#import "IOSCallBack.h"


IOSHelper::IOSHelper()
: m_Platform(SDK_None)
{
    
}
IOSHelper::~IOSHelper()
{
    delete instance;
}
IOSHelper* IOSHelper::instance=new IOSHelper();
IOSHelper* IOSHelper::GetInstance()
{
    return instance;
}
void IOSHelper::messageBox(const char* str)
{

}

int IOSHelper::getPlatform()
{
    return this->m_Platform;
}
void IOSHelper::setPlatform(int vPlatform)
{
    this->m_Platform = vPlatform;
}

void IOSHelper::initSDK()
{
    [[IOSCallBack sharedCallBack]startListen];
    switch (getPlatform()) {
        case SDK_PP:
        {
//            [[PPAppPlatformKit sharedInstance] setAppId:76 AppKey:@"04569029582680d7602989feb0a0a7e2"];
//            [[PPAppPlatformKit sharedInstance] setIsNSlogData:NO];
//            [[PPAppPlatformKit sharedInstance] setRechargeAmount:10];
//            [[PPAppPlatformKit sharedInstance] setIsLongComet:YES];
//            [[PPAppPlatformKit sharedInstance] setIsLogOutPushLoginView:YES];
//            [[PPAppPlatformKit sharedInstance] setIsOpenRecharge:YES];
//            [[PPAppPlatformKit sharedInstance] setCloseRechargeAlertMessage:@"关闭充值提示语"];
//            [PPUIKit sharedInstance];
//            
//            [PPUIKit setIsDeviceOrientationLandscapeLeft:YES];
//            [PPUIKit setIsDeviceOrientationLandscapeRight:YES];
//            [PPUIKit setIsDeviceOrientationPortrait:YES];
//            [PPUIKit setIsDeviceOrientationPortraitUpsideDown:YES];
            
            break;
        }
        
        case SDK_91:
        {
  //          NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
  //          cfg.appid = 100010;
  //          cfg.appKey = @"C28454605B9312157C2F76F27A9BCA2349434E546A6E9C75";
   //         //cfg.orientation = UIDeviceOrientationLandscapeRight;
     //       [[NdComPlatform defaultPlatform] NdInit:cfg];
            break;
        }
        case SDK_TB:
        {
            /*开启调试模式，用以调试检查更新流程（测试充值无需开启），正式发布前需要注释该行代码*/
            //[[TBPlatform defaultPlatform] TBSetDebugMode:0];
        //    [[TBPlatform defaultPlatform] TBInitPlatformWithAppID:100000 screenOrientation:UIInterfaceOrientationLandscapeLeft isContinueWhenCheckUpdateFailed:NO];
            break;
        }
            
        default:
            break;
    }
}

void IOSHelper::showLogin()
{
    switch (getPlatform()) {
        case SDK_PP:
        {
            //[[PPAppPlatformKit sharedInstance] showLogin];
            break;
        }
        case SDK_91:
        {
            [[NdComPlatform defaultPlatform] NdLogin:0];
            break;
        }
        case SDK_TB:
        {
            [[TBPlatform defaultPlatform] TBLogin:0];
            break;
        }
            
        default:
            break;
    }

}
/*
void IOSHelper::showRecharge()
{
    switch (getPlatform()) {
        case SDK_PP:
        {
            //[[PPAppPlatformKit sharedInstance] showLogin];
            buy(2);
            break;
            
        }
            
        default:
            break;
    }
}
 */
void IOSHelper::ppShowCenter()
{
    //[[PPAppPlatformKit sharedInstance] showCenter];
}


void IOSHelper::buy(int tag)
{
    //double prices[] = {1, 2, 3, 4};
    //int index = tag;
    //_name = [[NSString alloc] initWithFormat:@"%@",[[arrayName objectAtIndex:index] substringToIndex:3]];
    //[self exchangeGoods:prices[index]];
    //this->exchangeGoods(prices[index]);
    
    this->exchangeGoods(tag);
}

void IOSHelper::exchangeGoods(double price)
{
    int time = [[NSDate date] timeIntervalSince1970];
    NSString *billNO = [NSString stringWithFormat:@"%d",time];
    NSString *_name = [NSString stringWithFormat:@"%d",time];
    //[[PPAppPlatformKit sharedInstance] exchangeGoods:price BillNo:billNO BillTitle:_name RoleId:@"0" ZoneId:0];
}


