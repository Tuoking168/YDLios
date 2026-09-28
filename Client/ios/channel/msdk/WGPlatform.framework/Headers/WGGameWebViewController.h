/*!
 @header WGGameWebViewController.h
 @abstract 内置浏览器
 @author haywoodfu
 @version 1.00 2013/10/20 Creation
 */

#import <UIKit/UIKit.h>
#import "WGPlatformObserver.h"

/*!
 @class
 @abstract 内置浏览器
 */
@interface WGGameWebViewController : UIViewController<UIWebViewDelegate>

/*!
 @property
 @abstract 浏览器视图
 */
@property (nonatomic, strong)IBOutlet UIWebView *webView;
/*!
 @property
 @abstract  标题栏
 */
@property (nonatomic, strong)IBOutlet UINavigationBar *titleBar;

/*!
 @property
 @abstract  网页标题
 */
@property (nonatomic, strong)IBOutlet UILabel *titleLbl;

/*!
 @property
 @abstract 下部工具栏
 */
@property (nonatomic, strong)IBOutlet UIToolbar *toolBar;
/*!
 @property
 @abstract 后退按钮
 */
@property (nonatomic, strong)IBOutlet UIBarButtonItem *backBtn;
/*!
 @property
 @abstract 前进按钮
 */
@property (nonatomic, strong)IBOutlet UIBarButtonItem *forwardBtn;
/*!
 @property
 @abstract 首页按钮
 */
@property (nonatomic, strong)IBOutlet UIBarButtonItem *homeBtn;
/*!
 @property
 @abstract 刷新按钮
 */
@property (nonatomic, strong)IBOutlet UIBarButtonItem *refreshBtn;

/*! 
 * @method
 * @abstract 初始化内置浏览器
 * @param homeUrl 首页url
 * @param lUrl 登陆Url
 * @param openID 登陆后用户ID，可为空
 * @return void
 */
- (id)initWithHome:(NSString *)homeUrl observer:(WGPlatformObserver *)ob openID:(NSString *)openID;

/*! 
 * @method
 * @abstract 设置首页和登录页url
 * @param homeUrl 首页url
 * @param lUrl 登陆Url
 * @param openID 登陆后用户ID，可为空
 * @return void
 */
- (void)setHome:(NSString *)homeUrl observer:(WGPlatformObserver *)ob openID:(NSString *)openID;

/*! 
 * @method
 * @abstract 首页
 * @return void
 */
- (IBAction)home:(id)sender;

/*!
 * @method
 * @abstract 退回上一页
 * @return void
 */
- (IBAction)back:(id)sender;

/*! @method
 * @abstract 前进
 * @return void
 */
- (IBAction)forward:(id)sender;

/*! @method
 * @abstract 刷新
 * @return void
 */
- (IBAction)refresh:(id)sender;

/*! @method
 * @abstract 关闭webview
 * @return void
 */
- (IBAction)close:(id)sender;

/*! @method
 * @abstract 显示更多视图
 * @return void
 */
- (IBAction)showMore:(id)sender;

/*! @method
 * @abstract 测试公告界面
 * @return void
 */
+ (void)showAlert;

/**
 *  展示内置浏览器
 */
- (void)show;

/**
 *  隐藏内置浏览器
 */
- (void)dismiss;

/**
 *  显示提示消息
 */
- (void)showTips:(NSString *)tips;
@end
