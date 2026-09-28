//
//  WGApnsInterface.h
//  WGPlatform
//  MSDK Push相关功能函数
//  Created by fu chunhui on 14-9-14.
//  Copyright (c) 2014年 tencent.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface WGApnsInterface : NSObject

+ (void)WGRegisterAPNSPushNotification:(NSDictionary*)dict;
+ (void)WGSuccessedRegisterdAPNSWithToken:(NSData *)data;
+ (void)WGFailedRegisteredAPNS;
+ (void)WGCleanBadgeNumber;
+ (void)WGReceivedMSGFromAPNSWithDict:(NSDictionary*) userInfo;
@end
