//
//  ChannelCallBack.m
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#import "BDWebView.h"
#import "EAGLView.h"
#include <string>

@implementation BDWebView

static BDWebView *BDWebViewInstance = nil;
+(BDWebView *) instance{
    
    @synchronized(self)
    {
        if (BDWebViewInstance == nil)
        {
            BDWebViewInstance = [[self alloc] init] ;
        }
    }
    return BDWebViewInstance;
}
+(id) allocWithZone:(NSZone *)zone
{
    @synchronized(self)
    {
        if (BDWebViewInstance == nil)
        {
            BDWebViewInstance = [super allocWithZone:zone];
            return BDWebViewInstance;
        }
    }
    return nil;
}
- (void)showWebViewWithx:(float)x y:(float)y width:(float) widht height:(float)height;
{
    if (!m_webview)
    {
        short scale = [[EAGLView sharedEGLView] contentScaleFactor];
        //m_webview = [[UIWebView alloc] initWithFrame:CGRectMake(x/scale, y/scale, widht/scale , height/scale)];
        CGRect r = [[UIScreen mainScreen] bounds];
        
        r = CGRectMake(0, 0, MIN(r.size.width, r.size.height),MAX(r.size.width, r.size.height));
        
        m_webview = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, r.size.height , r.size.width)];
        [m_webview setDelegate:self];
        
        NSLog(@"showWebViewWithx:%d，%f,%f",scale,r.size.width , r.size.height);
        
        [[EAGLView sharedEGLView] addSubview:m_webview];
        [m_webview release];
        
        m_webview.backgroundColor = [UIColor whiteColor];
        m_webview.opaque = NO;
        
        for (UIView *aView in [m_webview subviews])
        {
            if ([aView isKindOfClass:[UIScrollView class]])
            {
                UIScrollView* scView = (UIScrollView *)aView;
                
                [(UIScrollView *)aView setShowsVerticalScrollIndicator:YES]; //右侧的滚动条 （水平的类似）
                [scView setShowsHorizontalScrollIndicator:YES];
                scView.bounces = YES;
                
                [scView setContentOffset:CGPointMake(-(scView.contentSize.width-r.size.height)/2, -(scView.contentSize.height-r.size.width)/2)];
                
                for (UIView *shadowView in aView.subviews)
                {
                    if ([shadowView isKindOfClass:[UIImageView class]])
                    {
                        shadowView.hidden = YES;  //上下滚动出边界时的黑色的图片 也就是拖拽后的上下阴影
                    }
                }
                
                UIButton *button = [[[UIButton alloc]initWithFrame:CGRectMake(scView.contentSize.width-50, 0, 50, 45)]autorelease];
                [button addTarget:self action:@selector(ButtonClicked:) forControlEvents:UIControlEventTouchUpInside];
                [button setBackgroundImage:[UIImage imageNamed:@"gm_webview_close_sel.png"] forState:UIControlStateHighlighted];
                [button setBackgroundImage:[UIImage imageNamed:@"gm_webview_close_.png"] forState:UIControlStateNormal];
                [scView addSubview:button];
                
                [scView bringSubviewToFront:button];
                /*
                UIImageView *bgView = [[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"login_webbg.png"]]autorelease];
                [scView insertSubview:bgView atIndex:0];
                [bgView setFrame:CGRectMake(0, 0, 530/scale, 488/scale)];
                [bgView setCenter:CGPointMake(scView.center.x, scView.center.y-10)];
                
                UILabel *label = [[[UILabel alloc]initWithFrame:CGRectMake(0, 10, bgView.frame.size.width, 50)]autorelease];
                [label setBackgroundColor:[UIColor clearColor]];
                [label setNumberOfLines:0];
                [label setFont:[UIFont boldSystemFontOfSize:10]];
                [label setTextAlignment:NSTextAlignmentCenter];
                [label setTextColor:[UIColor colorWithRed:68/255.0 green:98/255.0 blue:124/255.0 alpha:255/255.0]];
                NSString *registeraward = NSLocalizedStringFromTable(@"registeraward", @"Local", nil);
                [label setText:registeraward];
                [bgView addSubview:label];
                
                UILabel *bottomlabel = [[[UILabel alloc]initWithFrame:CGRectMake(0, bgView.frame.size.height-32, bgView.frame.size.width, 32)]autorelease];
                [bottomlabel setBackgroundColor:[UIColor clearColor]];
                [bottomlabel setNumberOfLines:0];
                [bottomlabel setFont:[UIFont boldSystemFontOfSize:10]];
                [bottomlabel setTextAlignment:NSTextAlignmentCenter];
                [bottomlabel setTextColor:[UIColor colorWithRed:68/255.0 green:98/255.0 blue:124/255.0 alpha:255/255.0]];
                NSString *registertips = NSLocalizedStringFromTable(@"registertips", @"Local", nil);
                [bottomlabel setText:registertips];
                
                [bgView addSubview:bottomlabel];
                
                UIButton *button = [[[UIButton alloc]initWithFrame:CGRectMake(scView.center.x+bgView.frame.size.width/2-42, scView.center.y-bgView.frame.size.height/2-10, 84/2, 84/2)]autorelease];
                [button addTarget:self action:@selector(ButtonClicked:) forControlEvents:UIControlEventTouchUpInside];
                [button setBackgroundImage:[UIImage imageNamed:@"login_close.png"] forState:UIControlStateSelected];
                [button setBackgroundImage:[UIImage imageNamed:@"login_close.png"] forState:UIControlStateNormal];
                [scView addSubview:button];
                
                [scView bringSubviewToFront:button];
                
#if defined (Pad_Version)
                [bgView setFrame:CGRectMake(0, 0, 530, 488)];
                [bgView setCenter:CGPointMake(scView.center.x, scView.center.y-20)];
                [label setFrame:CGRectMake(0, 20, bgView.frame.size.width, 100)];
                [label setFont:[UIFont boldSystemFontOfSize:20]];
                [bottomlabel setFrame:CGRectMake(0, bgView.frame.size.height-64, bgView.frame.size.width, 64)];
                [bottomlabel setFont:[UIFont boldSystemFontOfSize:20]];
                [button setFrame:CGRectMake(scView.center.x+bgView.frame.size.width/2-131/2-10, scView.center.y-bgView.frame.size.height/2-10, 131/2, 131/2)];
#endif
                 */
            }
        }
        //        [m_webview bringSubviewToFront:button];
    }
}

- (void)ButtonClicked:(id)sender{
    [self removeWebView];
}

- (void)updateURL:(const char*)url
{
    NSString *request = [NSString stringWithUTF8String:url];
    NSLog(@"updateURL: %@",request);
    [m_webview loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:request ]]];
    //[m_webview loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:request] cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData timeoutInterval:60]];
}
- (void)showWebView
{
    [self showWebViewWithx:0 y:0 width:0 height:0];
}
- (void)removeWebView
{
    [m_webview removeFromSuperview];
    m_webview = NULL;
}

#pragma mark - WebView
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return true;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
   
}

@end