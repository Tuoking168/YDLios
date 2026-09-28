//
//  IOSCallBack.m
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#import "IOSCallBack.h"
#import "IOSHelper.h"
#import "LoginHelper.h"


@implementation IOSCallBack

static IOSCallBack *sharedCallBack = nil;
+(IOSCallBack *) sharedCallBack{
    
    @synchronized(self)
    {
        if (sharedCallBack == nil)
        {
            sharedCallBack = [[[self alloc] init] autorelease];
        }
    }
    return sharedCallBack;
}
+(id) allocWithZone:(NSZone *)zone
{
    @synchronized(self)
    {
        if (sharedCallBack == nil)
        {
            sharedCallBack = [super allocWithZone:zone];
            return sharedCallBack;
        }
    }
    return nil;
}

- (void)dealloc{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	[super dealloc];
}

+ (void)messageBox:(NSString*)stringTip
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:stringTip
													message:nil
												   delegate:nil
										  cancelButtonTitle:nil
										  otherButtonTitles:@"确定", nil];
	[alert show];
	[alert release];
}

-(void)startListen
{
    switch (IOSHELPER->getPlatform()) {
        case IOSHelper::SDK_PP:
        {
            //[[PPAppPlatformKit sharedInstance] setDelegate:self];
            break;
        }
        case IOSHelper::SDK_91:
        {
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSInitResult:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLoginResult:) name:(NSString *)kNdCPLoginNotification object:nil];
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSSessionInvalid:) name:(NSString *)kNdCPSessionInvalidNotification object:nil];
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSleavePlatform:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSPauseExist:) name:(NSString *)kNdCPPauseDidExitNotification object:nil];
            break;
        }
        case IOSHelper::SDK_TB:
        {
            /*监听初始化结果通知（3.0.1新增），该通知userInfo字典中带有检查更新结果*/
            [[NSNotificationCenter defaultCenter] addObserver:self
                                                     selector:@selector(tbInitFinished:)
                                                         name:kTBInitDidFinishNotification
                                                       object:nil];
            /*监听登录成功通知（3.0.1版本开始，失败不再发送该通知*/
            [[NSNotificationCenter defaultCenter] addObserver:self
                                                     selector:@selector(loginResult:)
                                                         name:(NSString *)kTBLoginNotification
                                                       object:nil];
            /* 监听离开平台通知（3.0.1版本开始，该通知userInfo字典中带有离开的类型及订单号 */
            [[NSNotificationCenter defaultCenter] addObserver:self
                                                     selector:@selector(leavePlatform:)
                                                         name:(NSString *)kTBLeavePlatformNotification
                                                       object:nil];
            break;
        }
            
            
        default:
            break;
    }
    

}

#pragma mark    ---------------PP助手 CALLBACK---------------
/*
//字符串登录成功回调【实现其中一个就可以】
- (void)ppLoginStrCallBack:(NSString *)paramStrToKenKey{
    //字符串token验证方式
    MSG_GAME_SERVER_STR mgs_s = {};
    mgs_s.len_str =  41;
    mgs_s.commmand_str = 0xAA000022;
    memcpy(mgs_s.token_key_str, [paramStrToKenKey UTF8String], 33);
    
    NSLog(@"____droid______pp_login_callback_____%@",paramStrToKenKey);
    //下面请注意，登录验证分两种情况e
    //1. 如果您没有业务服务器则在此处直接跳入游戏界面
    //2. 如果您有游戏服务器，请在这里验证登录信息，然后跳转到游戏界面
    //下面代码为内部服务器测试代码
    
}

//2进制登录成功回调【实现其中一个就可以】
//- (void)ppLoginHexCallBack:(char *)paramHexToKen{
//
//    MSG_GAME_SERVER mgs = {};
//    mgs.len =  24;
//    mgs.commmand = 0xAA000021;
//    memcpy(mgs.token_key, paramHexToKen, 16);
//
//    //下面请注意，登录验证分两种情况e
//    //1. 如果您没有业务服务器则在此处直接跳入游戏界面
//    //2. 如果您有游戏服务器，请在这里验证登录信息，然后跳转到游戏界面
//    //下面代码为内部服务器测试代码
//    int fd = socket( AF_INET , SOCK_STREAM , 0 ) ;
//    if(fd == -1)
//        printf("socket err : %m\n"),exit(1);
//    struct sockaddr_in addr;
//    addr.sin_family = AF_INET;
//    addr.sin_port = htons([GAMESERVER_PORT_TEST intValue]);
//    addr.sin_addr.s_addr = inet_addr(GAMESERVER_IP_TEST);
//    int r = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
//    if(r == -1)
//        printf("connect err : %m\n"),exit(-1);
//    //发送验证
//    send(fd, &mgs, sizeof(MSG_GAME_SERVER), 0);
//    MSG_GAME_SERVER_RESPONSE mgsr;
//    recv(fd, &mgsr, 12, 0);
//    NSLog(@"%02X",mgsr.status);
//    if(mgsr.status == 0){
//        //跳入游戏界面
//        [bgGanmeCenterImageView setHidden:NO];
//        [bgloginImageView setHidden:YES];
//        [[PPAppPlatformKit sharedInstance] getUserInfoSecurity];
//    }
//}

//关闭客户端页面回调方法
-(void)ppClosePageViewCallBack:(PPPageCode)paramPPPageCode{
    //可根据关闭的VIEW页面做你需要的业务处理
    NSLog(@"当前关闭的VIEW页面回调是%d", paramPPPageCode);
}



//关闭WEB页面回调方法
- (void)ppCloseWebViewCallBack:(PPWebViewCode)paramPPWebViewCode{
    //可根据关闭的WEB页面做你需要的业务处理
    NSLog(@"当前关闭的WEB页面回调是%d", paramPPWebViewCode);
}

//注销回调方法
- (void)ppLogOffCallBack{
    NSLog(@"注销的回调");
    //[bgGanmeCenterImageView setHidden:YES];
    //[bgloginImageView setHidden:NO];
}

//兑换回调接口【只有兑换会执行此回调】
- (void)ppPayResultCallBack:(PPPayResultCode)paramPPPayResultCode{
    NSLog(@"兑换回调返回编码%d",paramPPPayResultCode);
    //回调购买成功。其余都是失败
    if(paramPPPayResultCode == PPPayResultCodeSucceed){
        //购买成功发放道具
        
    }else{
        
    }
}

-(void)ppVerifyingUpdatePassCallBack{
    NSLog(@"验证游戏版本完毕回调");
    [[PPAppPlatformKit sharedInstance] showLogin];
}
*/

#pragma mark    ---------------91助手 CALLBACK---------------
- (void)SNSInitResult:(NSNotification *)notify
{
	//[self showStartView];
    [[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtTopLeft];
}

//登录
- (void)SNSLoginResult:(NSNotification *)notify
{
	NSDictionary *dict = [notify userInfo];
	BOOL success = [[dict objectForKey:@"result"] boolValue];
	NdGuestAccountStatus* guestStatus = (NdGuestAccountStatus*)[dict objectForKey:@"NdGuestAccountStatus"];
	
	//登录成功后处理
	if([[NdComPlatform defaultPlatform] isLogined] && success) {
		
		//也可以通过[[NdComPlatform defaultPlatform] getCurrentLoginState]判断是否游客登录状态
		if (guestStatus) {
			NSString* strUin = [[NdComPlatform defaultPlatform] loginUin];
			NSString* strTip = nil;
			if ([guestStatus isGuestLogined]) {
				strTip = [NSString stringWithFormat:@"游客账号登录成功,\n uin = %@", strUin];
			}
			else if ([guestStatus isGuestRegistered]) {
				strTip = [NSString stringWithFormat:@"游客成功注册为普通账号,\n uin = %@", strUin];
			}
			
			if ([strTip length] > 0) {
				[IOSCALLBACK messageBox: strTip];
			}
		}
		else {
			// 普通账号登录成功!
		}
		
		//[self updateView];
		//[self dismissModalViewControllerAnimated:YES];
	}
	//登录失败处理和相应提示
	else {
		int error = [[dict objectForKey:@"error"] intValue];
		NSString* strTip = [NSString stringWithFormat:@"登录失败, error=%d", error];
		switch (error) {
			case ND_COM_PLATFORM_ERROR_USER_CANCEL://用户取消登录
				if (([[NdComPlatform defaultPlatform] getCurrentLoginState] == ND_LOGIN_STATE_GUEST_LOGIN)) {
					strTip =  @"当前仍处于游客登录状态";
				}
				else {
					strTip = @"用户未登录";
				}
				break;
				
				// {{ for demo tip
			case ND_COM_PLATFORM_ERROR_APP_KEY_INVALID://appId未授权接入, 或appKey 无效
				strTip = @"登录失败, 请检查appId/appKey";
				break;
			case ND_COM_PLATFORM_ERROR_CLIENT_APP_ID_INVALID://无效的应用ID
				strTip = @"登录失败, 无效的应用ID";
				break;
			case ND_COM_PLATFORM_ERROR_HAS_ASSOCIATE_91:
				strTip = @"有关联的91账号，不能以游客方式登录";
				break;
				
				// }}
			default:
				break;
		}
		[IOSCALLBACK messageBox:strTip];
	}
}

//会话失效
- (void)SNSSessionInvalid:(NSNotification *)notify
{
	[self performSelector:@selector(dismissModalViewControllerAnimated:) withObject:nil afterDelay:0.5];
	[self performSelector:@selector(showStartView) withObject:nil afterDelay:0.6];
}

//离开平台
- (void)SNSleavePlatform:(NSNotification *)notify
{
	int loginState = [[NdComPlatform defaultPlatform] getCurrentLoginState];
	if (loginState == ND_LOGIN_STATE_NOT_LOGIN) {
		//[self showStartView];
	}
	//更新虚拟币
	//[self updateCoin];
}

- (void)SNSPauseExist:(NSNotification *)notify
{
    NSLog(@"游戏暂停页已关闭，可以继续游戏了");
}


#pragma mark    ---------------同步推 CALLBACK---------------
#pragma mark - 通用方法
/**
 *	@brief	消息显示方法
 */
- (void)showMessage:(NSString*)msg
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"" message:[msg stringByAppendingString:@"（Demo提示，正式游戏环境请根据游戏需求修改）"]
												   delegate:nil
										  cancelButtonTitle:@"好的"
										  otherButtonTitles: nil];
	[alert show];
	[alert release];
}

/**
 *	@brief	更新玩家信息
 */
- (void)updatePlayerInfo
{
	//nickNameLabel.text = [NSString stringWithFormat:@"%@,欢迎回来",[TBPlatform defaultPlatform].nickName];
    
}
/**
 *	@brief	进入用户中心
 */
- (IBAction)enterUserCenter:(id)sender{
    /*
     旧接口：
     [[TBPlatform defaultPlatform] enterPlatform];*/
	[[TBPlatform defaultPlatform] TBEnterUserCenter:0];
}

/**
 *	@brief	进入论坛（论坛需要联系客服配置)
 */
- (IBAction)enterBBS:(id)sender
{
    /*
     旧接口：（在进入用户中心后，有配置论坛的情况下可以选择）
     [[TBPlatform defaultPlatform] enterPlatform];*/
	int bbsResult = [[TBPlatform defaultPlatform] TBEnterAppBBS:0];
	if (bbsResult == TB_PLATFORM_NO_BBS) {
		[self showMessage:@"该游戏未配置论坛"];
	}
}

/**
 *	@brief	进入游戏推荐中心
 */
- (IBAction)enterGamesCenter:(id)sender
{
    /*
     旧接口：（在进入用户中心后可以选择进入）
     [[TBPlatform defaultPlatform] enterPlatform];*/
	[[TBPlatform defaultPlatform] TBEnterAppCenter:0];
}

/**
 *	@brief	检查更新
 */
- (IBAction)enterUpdate:(id)sender
{
    /*新接口*/
    [[TBPlatform defaultPlatform] TBAppVersionUpdate:0 delegate:self];
}

/**
 * @brief 检查Session
 */
- (IBAction)enterCheckSession:(id)sender{
    NSString *urlString = [NSString stringWithFormat:@"http://tgi.tongbu.com/check.aspx?k=%@",
                           [[TBPlatform defaultPlatform] sessionId]];
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url
                                                           cachePolicy:NSURLRequestReloadIgnoringCacheData
                                                       timeoutInterval:15.f];
    NSURLConnection *conn = [NSURLConnection connectionWithRequest:request delegate:self];
    if (!conn) {
        [self showMessage:@"核对Session失败，请检查网络"];
    }
}

#pragma mark - 监听通知方法
- (void)tbInitFinished:(NSNotification *)notification{
    int updateResult = [[notification.userInfo objectForKey:@"updateResult"] intValue];
    NSLog(@"平台初始化结果（即检查更新结果）：%d",updateResult);
    [[TBPlatform defaultPlatform] TBLogin:0];
}
/**
 *	@brief	登录通知监听方法，登录成功、失败都在这个方法处理
 *
 *	@param 	notification 	通知的userInfo包含登录结果信息
 */
- (void)loginResult:(NSNotification *)notification
{
	NSDictionary *dict = [notification userInfo];
	BOOL success = [[dict objectForKey:@"result"] boolValue];
    
    
	/*登录成功后处理*/
	if([[TBPlatform defaultPlatform] isLogined] && success) {
		/*进行玩家信息的更新，或转入游戏界面等*/
		[self updatePlayerInfo];
		//[self dismissModalViewControllerAnimated:YES];
	}
	/*登录失败处理和相应提示*/
	else {
		int error = [[dict objectForKey:@"error"] intValue];
		NSString* errNotice = [NSString stringWithFormat:@"登录失败, error=%d", error];
		switch (error) {
			case TB_PLATFORM_LOGIN_INCORRECT_ACCOUNT_OR_PASSWORD_ERROR:
				errNotice = @"帐号或密码错误，请重试";
				break;
			case TB_PLATFORM_LOGIN_INVALID_ACCOUNT_ERROR:
				errNotice = @"帐号被禁用，请与管理员联系";
				break;
			case TB_PLATFORM_LOGIN_SYNC_FAILED_ERROR:
				errNotice = @"同步帐号失败，请重试";
				break;
			case TB_PLATFORM_LOGIN_REQUEST_FAILED_ERROR:
				errNotice = @"登录请求失败，请检查网络";
				break;
			default:
				break;
		}
        /*SDK已通知，无需再通知*/
		//[self showMessage:errNotice];
	}
}

/**
 *	@brief	平台关闭通知，监听离开平台通知以对游戏界面进行重新调整
 */
- (void)leavePlatform:(NSNotification *)notification
{
    int leavedType = [[notification.userInfo objectForKey:TBLeavedPlatformTypeKey] intValue];
    switch (leavedType) {
            //从登录界面手动关闭（登录成功关闭时不发送离开通知）
        case TBPlatformLeavedFromLogin:
            if (![[TBPlatform defaultPlatform] isLogined])
            {
                [self showMessage:@"玩家未登录"];
                
                //[self dismissModalViewControllerAnimated:YES];
                //GameStartViewController *startController = [[GameStartViewController alloc]
                //                                            initWithNibName:@"GameStartViewController"
                //                                            bundle:[NSBundle mainBundle]];
                //[self presentModalViewController:startController animated:YES];
                //[startController release];
            }
            break;
            //从个人中心页关闭（包括游戏推荐、论坛页）
        case TBPlatformLeavedFromUserCenter:
            [self showMessage:@"从个人中心离开"];
            break;
            //从充值页面退出（包含一个订单号字段）
        case TBPlatformLeavedFromUserPay:
        {
            NSString *order = [notification.userInfo objectForKey:TBLeavedPlatformOrderKey];
            //在GamePayViewController中处理，此处忽略
            //            [self showMessage:[NSString stringWithFormat:@"订单号:%@",order]];
        }
            break;
        default:
            break;
    }
}

#pragma mark - Delegate Method
/**
 *	@brief	检查更新完成后回调
 *
 *	@param 	updateResult 	结果标识
 */
- (void)appVersionUpdateDidFinish:(TB_APP_UPDATE_RESULT)updateResult
{
    NSString *title = nil;
    NSLog(@"update result:%d", updateResult);
    switch (updateResult) {
        case TB_APP_UPDATE_NO_NEW_VERSION:
            title = @"无可用更新";//正常进入游戏
            break;
        case TB_APP_UPDATE_NEW_VERSION_DOWNLOAD_FAIL:
            title = @"下载新版本失败";//可以正常进入游戏，强制更新可由服务端限制登录
            break;
        case TB_APP_UPDATE_CHECK_NEW_VERSION_FAIL:
            title = @"检测新版本信息失败"; /*可能是网络问题，那么建议检查下网络，也可以直接进入游戏，
                                   这边的风险在于如果是客户端与服务器版本不兼容，容易引起客户端异常*/
            break;
        case TB_APP_UPDATE_UPDATE_CANCEL_BY_USER:
            title = @"用户取消更新"; //进入游戏，需要的话，可以提示进一步提示玩家更新的好处和目的
            break;
        default:
            break;
    }
    [self showMessage:title];
}
#pragma mark - Connection Delegate
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error{
    [self showMessage:@"核对Session失败，请检查网络"];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data{
    NSString *string = [[[NSString alloc ]initWithData:data encoding:NSUTF8StringEncoding] autorelease];
    NSString *notice = [NSString stringWithFormat:@"检查Session有效性返回结果：%@",string];
    [self showMessage:notice];
}
@end
