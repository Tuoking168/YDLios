//
//  ChannelCallBack.h
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <functional>

@interface BDWebView : NSObject <UIWebViewDelegate>
{
    UIWebView* m_webview;
}
+(BDWebView *) instance;


- (void)showWebViewWithx:(float)x y:(float)y width:(float) widht height:(float)height;

- (void)updateURL:(const char*)url;

- (void)ButtonClicked:(id)sender;

- (void)showWebView;

- (void)removeWebView;

@end