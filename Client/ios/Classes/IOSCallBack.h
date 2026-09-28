//
//  IOSCallBack.h
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import <PPAppPlatformKit/PPAppPlatformKit.h>
#import <TBPlatform/TBPlatform.h>

#import <NdComPlatform/NdComPlatform.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>
#import <NdComPlatform/NdCPNotifications.h>

@interface IOSCallBack : NSObject//<PPAppPlatformKitDelegate>
{
       
}

+(IOSCallBack *) sharedCallBack;
+ (void)messageBox:(NSString*)stringTip;

-(void)startListen;

#define IOSCALLBACK [IOSCallBack sharedCallBack]
@end
