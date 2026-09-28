//
//  ChannelCallBack.m
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#import "ChannelCallBack.h"
#import "ChannelHelper.h"
#include "scene/SceneManager.h"
#include "event/CPEventHelper.h"

#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>

@implementation ChannelCallBack

static ChannelCallBack *sharedCallBack = nil;
+(ChannelCallBack *) sharedCallBack{
    
    @synchronized(self)
    {
        if (sharedCallBack == nil)
        {
            sharedCallBack = [[self alloc] init] ;
            
            [sharedCallBack cleanData];
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

- (void)messageBox:(NSString*)stringTip
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:stringTip
													message:nil
												   delegate:nil
										  cancelButtonTitle:nil
										  otherButtonTitles:@"确定", nil];
	[alert show];
	[alert release];
}
-(NSString *) macAddress
{
    int					mib[6];
	size_t				len;
	char				*buf;
	unsigned char		*ptr;
	struct if_msghdr	*ifm;
	struct sockaddr_dl	*sdl;
	
	mib[0] = CTL_NET;
	mib[1] = AF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_LINK;
	mib[4] = NET_RT_IFLIST;
	
	if ((mib[5] = if_nametoindex("en0")) == 0) {
		printf("Error: if_nametoindex error\n");
		return NULL;
	}
	
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 1\n");
		return NULL;
	}
	
	if ((buf = (char*)malloc(len)) == NULL) {
		printf("Could not allocate memory. error!\n");
		return NULL;
	}
	
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 2");
		return NULL;
	}
	
	ifm = (struct if_msghdr *)buf;
	sdl = (struct sockaddr_dl *)(ifm + 1);
	ptr = (unsigned char *)LLADDR(sdl);
	// NSString *outstring = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
	NSString *outstring = [NSString stringWithFormat:@"%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
	free(buf);
	return [outstring uppercaseString];
}

-(void)closeView
{

}
-(void)cleanData
{
    //CHANNELCALLBACK.user_ID = @"";
    CHANNELCALLBACK.token_Key = @"";
    CHANNELCALLBACK.product_ID = @"";
    CHANNELCALLBACK.price = 0.0f;
    CHANNELCALLBACK.order_ID = @"";
    
    //CHANNELCALLBACK.isLogin = false;
    
    CHANNELCALLBACK.payViewOpened = false;
    CHANNELCALLBACK.rechargeVerifyURL = @"";
    
    CHANNELCALLBACK.rechargeAlert = nil;
    CHANNELCALLBACK.isPaying = NO;
}
-(void)startListen
{
#if defined APPSTORE_VERSION
    //[CHANNELCALLBACK buy:1];
    [[ECPurchase shared] setProductDelegate:CHANNELCALLBACK];
    [[ECPurchase shared] setTransactionDelegate:CHANNELCALLBACK];
#elif defined C91_VERSION
    [CHANNELCALLBACK NDStartListen];
#elif defined PP_VERSION
    [CHANNELCALLBACK PPStartListen];
#elif defined TB_VERSION
    [CHANNELCALLBACK TBStartListen];
#elif defined KY_VERSION
    [CHANNELCALLBACK KYStartListen];
#elif defined IT_VERSION
    [CHANNELCALLBACK itoolsStartListen];
#elif defined I4_VERSION
    [CHANNELCALLBACK asStartListen];
#elif defined HM_VERSION
    [CHANNELCALLBACK hmStartListen];
#elif defined C3737_VERSION
    [CHANNELCALLBACK c3737StartListen];
#elif defined XY_VERSION
    [CHANNELCALLBACK xyStartListen];
#elif defined VTCID_VERSION
    [CHANNELCALLBACK vtcidStartListen];
#elif defined IIAPPLE_VERSION
    [CHANNELCALLBACK iiappleStartListen];
#endif
}
-(bool)aliPay:(NSURL *)url
{
#if defined APPSTORE_VERSION
//    WGPlatform* plat = WGPlatform::GetInstance();
//    MyObserver* ob =(MyObserver *) plat->GetObserver();
//    if (!ob) {
//        ob = new MyObserver();
//        plat->WGSetObserver(ob);
//    }
//    return  [WGInterface  HandleOpenURL:url];
#elif defined C91_VERSION
   //[[NdComPlatform defaultPlatform]isLogined];
#elif defined PP_VERSION
   [[PPAppPlatformKit sharedInstance] alixPayResult:url];
#elif defined TB_VERSION
 
#elif defined KY_VERSION
    if ([url.host isEqualToString:@"safepay"]) {
        [[AlipaySDK defaultService] processOderWithPaymentResult:url];
    }
#elif defined IT_VERSION
    
#elif defined I4_VERSION
    [[AsInfoKit sharedInstance] alixPayResult:url];
#elif defined HM_VERSION
    //[[IPAYiAppPay sharediAppPay] handleOpenurl:url];
    [[IPAYKit sharedInstance]handleOpenurl:url];
#elif defined C3737_VERSION
    
#elif defined XY_VERSION
    [[XYPlatform defaultPlatform] XYHandleOpenURL:url];
#elif defined VTCID_VERSION
    
#elif defined IIAPPLE_VERSION
    
#endif
    return true;
}
-(void)logout
{
    SceneManager::switchToLogin();
    CHANNELHELPER->hideToolBar();
}
-(NSString*)getOrderID
{
    int cur_time = ActivityData::getWorldTime();
    int aid,pid,svr = 0;
	ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
    pid = HeroData::getPID();
    svr = LoginHelper::getSavedServerId();
    if (aid<0) aid=0;
    if (pid<0) pid=0;
    if (svr<0) svr=0;
    if (aid==0||pid==0||svr==0) {
        UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"出错了" message:@"生成订单号失败，请尝试重新登录游戏继续支付。" delegate:nil cancelButtonTitle:nil otherButtonTitles:@"确定", nil];
        [alert show];
        [alert release];
        return @"";
    }
    
    char order[50];
    //aid-pid-svr-time
    sprintf(order, "%d-%d-%d-%d",aid,pid,svr,cur_time);
    //string orderID = order;
    return [NSString stringWithUTF8String:order];
}

#pragma mark -------------------------------PP callback---------------------------------------------
#if defined PP_VERSION
- (void)PPStartListen
{
    [[PPAppPlatformKit sharedInstance] setDelegate:CHANNELCALLBACK];
}
//字符串登录成功回调【实现其中一个就可以】
- (void)ppLoginStrCallBack:(NSString *)paramStrToKenKey{
    
    //CHANNELCALLBACK.user_ID = [NSString stringWithFormat:@"%lld",[[PPAppPlatformKit sharedInstance] currentUserId]];//[notification.object objectForKey:@"userId"];
    CHANNELCALLBACK.token_Key =paramStrToKenKey;
    CHANNELHELPER->loginVerifyRequest();
    
    NSLog(@"登录成功 token=%@", paramStrToKenKey);
}

//关闭客户端页面回调方法
-(void)ppClosePageViewCallBack:(PPPageCode)paramPPPageCode{
    //可根据关闭的VIEW页面做你需要的业务处理
    NSLog(@"当前关闭的VIEW页面回调是%d", paramPPPageCode);
    [CHANNELCALLBACK closeView];
}

//关闭WEB页面回调方法
- (void)ppCloseWebViewCallBack:(PPWebViewCode)paramPPWebViewCode{
    //可根据关闭的WEB页面做你需要的业务处理
    NSLog(@"当前关闭的WEB页面回调是%d", paramPPWebViewCode);
    if (paramPPWebViewCode==PPWebViewCodeRechargeAndExchange) {
       
    }else if (paramPPWebViewCode==PPWebViewCodeRecharge){
        
    }
    [CHANNELCALLBACK closeView];
}

//注销回调方法
- (void)ppLogOffCallBack{
    NSLog(@"注销的回调");
    
    CHANNELCALLBACK.isLogin = false;
    
    [CHANNELCALLBACK logout];
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
#endif

#pragma mark -------------------------------tongbu callback---------------------------------------------
#if defined TB_VERSION
- (void)TBStartListen
{
    /*初始化结束通知，登录等操作务必在收到该通知后调用！！*/
    [[NSNotificationCenter defaultCenter] addObserver:CHANNELCALLBACK
                                             selector:@selector(TBInitFinished)
                                                 name:kTBInitDidFinishNotification
                                               object:Nil];
    /*登录成功通知*/
    [[NSNotificationCenter defaultCenter] addObserver:CHANNELCALLBACK
                                             selector:@selector(TBLoginResult)
                                                 name:kTBLoginNotification
                                               object:nil];
    /*注销通知（个人中心页面的注销也会触发该通知，注意处理*/
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(TBLogoutPlatform)
                                                 name:kTBUserLogoutNotification
                                               object:nil];
    /*离开平台通知（包括登录页面、个人中心页面、web充值页等*/
    [[NSNotificationCenter defaultCenter] addObserver:CHANNELCALLBACK
                                             selector:@selector(TBLeavePlatform:)
                                                 name:kTBLeavePlatformNotification
                                               object:nil];
}
#pragma mark - 监听通知方法
- (void)TBInitFinished{
    //[[TBPlatform defaultPlatform] TBLogin:0];
}
/**
 *	@brief	登录通知监听方法，登录成功、失败都在这个方法处理
 *
 *	@param 	notification 	通知的userInfo包含登录结果信息
 */
- (void)TBLoginResult
{
    /*登录成功后处理*/
    if ([[TBPlatform defaultPlatform] TBIsLogined]) {
        TBPlatformUserInfo *userInfo = [[TBPlatform defaultPlatform] TBGetMyInfo];
        CHANNELCALLBACK.user_ID = [userInfo userID];
        CHANNELCALLBACK.token_Key = [userInfo sessionID];
        CHANNELHELPER->loginVerifyRequest();
        NSLog(@"____TB____uid=%@,session=%@",CHANNELCALLBACK.user_ID,CHANNELCALLBACK.token_Key);
        //显示浮动工具条
        //[[TBPlatform defaultPlatform] TBShowToolBar:TBToolBarAtMiddleLeft isUseOldPlace:NO];
    }
}

/**
 *	@brief	平台关闭通知，监听离开平台通知以对游戏界面进行重新调整
 */
- (void)TBLeavePlatform:(NSNotification *)notification
{
    [CHANNELCALLBACK closeView];
    NSDictionary *notifyUserInfo = notification.userInfo;
    TBPlatformLeavedType leavedFromType = (TBPlatformLeavedType)[[notifyUserInfo objectForKey:
                                                                  TBLeavedPlatformTypeKey] intValue];
    switch (leavedFromType) {
            //从登录页离开
        case TBPlatformLeavedFromLogin:{
        }
            break;
            //从个人中心离开
        case TBPlatformLeavedFromUserCenter:{
        }
            break;
            //从充值页面离开
        case TBPlatformLeavedFromUserPay:{
            NSString *orderString = [notifyUserInfo objectForKey:TBLeavedPlatformOrderKey];
            [[TBPlatform defaultPlatform] TBCheckPaySuccess:orderString
                                                   delegate:self];
        }
            break;
        default:
            break;
    }
}
- (void)TBLogoutPlatform
{
    CHANNELCALLBACK.isLogin = false;
    
    [CHANNELCALLBACK logout];
    
    //[[TBPlatform defaultPlatform] TBHideToolBar];
}

#pragma mark - Delegate Method
/**
 *	@brief	检查更新完成后回调
 *
 *	@param 	updateResult 	结果标识
 */
//- (void)appVersionUpdateDidFinish:(TB_APP_UPDATE_RESULT)updateResult
//{
//    NSString *title = nil;
//    NSLog(@"update result:%d", updateResult);
//    switch (updateResult) {
//        case TB_APP_UPDATE_NO_NEW_VERSION:
//            title = @"无可用更新";//正常进入游戏
//            break;
//        case TB_APP_UPDATE_NEW_VERSION_DOWNLOAD_FAIL:
//            title = @"下载新版本失败";//可以正常进入游戏，强制更新可由服务端限制登录
//            break;
//        case TB_APP_UPDATE_CHECK_NEW_VERSION_FAIL:
//            title = @"检测新版本信息失败"; /*可能是网络问题，那么建议检查下网络，也可以直接进入游戏，
//                                   这边的风险在于如果是客户端与服务器版本不兼容，容易引起客户端异常*/
//            break;
//        case TB_APP_UPDATE_UPDATE_CANCEL_BY_USER:
//            title = @"用户取消更新"; //进入游戏，需要的话，可以提示进一步提示玩家更新的好处和目的
//            break;
//        default:
//            break;
//    }
//    [CHANNELCALLBACK messageBox:title];
//}
#pragma mark - BuyGoods Delegate
- (void)TBBuyGoodsDidSuccessWithOrder:(NSString*)order{
    [CHANNELCALLBACK messageBox:@"购买成功"];
}
- (void)TBBuyGoodsDidFailedWithOrder:(NSString *)order resultCode:(TB_BUYGOODS_ERROR)errorType;{
    switch (errorType) {
        case kBuyGoodsOrderEmpty:
            NSLog(@"订单号为空");
            break;
        case kBuyGoodsBalanceNotEnough:
            NSLog(@"推币余额不足");
            break;
        case kBuyGoodsServerError:
            NSLog(@"服务器错误");
            break;
        case kBuyGoodsOtherError:
            NSLog(@"其他错误");
            break;
        default:
            break;
    }
}
- (void)TBBuyGoodsDidStartRechargeWithOrder:(NSString *)order{
    NSLog(@"开始订单:%@",order);
}
- (void)TBBuyGoodsDidCancelByUser:(NSString *)order{
    //[CHANNELCALLBACK messageBox:@"取消支付"];
}
#pragma mark - CheckOrder Delegate
- (void)TBCheckOrderFinishedWithOrder:(NSString *)orderString
                               amount:(int)amount
                               status:(TBCheckOrderStatusType)statusType{
    if (statusType==TBCheckOrderStatusSuccess) {
        
    }else if (statusType==TBCheckOrderStatusPaying){
        
    }
    
}

- (void)TBCheckOrderSuccessWithResult:(NSDictionary *)dict{
    NSLog(@"Check Result:%@",dict);
}
- (void)TBCheckOrderDidFailed:(NSString *)order{
    /*检查订单失败*/
    NSLog(@"Check Failed:%@",order);
}
#endif
#pragma mark -------------------------------91 callback---------------------------------------------
#if defined C91_VERSION
-(void)NDStartListen
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSInitResult:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLoginResult:) name:(NSString *)kNdCPLoginNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSSessionInvalid:) name:(NSString *)kNdCPSessionInvalidNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSleavePlatform:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSPauseExist:) name:(NSString *)kNdCPPauseDidExitNotification object:nil];
    
     [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdCPBuyResultNotification:) name:(NSString *)kNdCPBuyResultNotification object:nil];
     [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdCPAsynPaySMSSentNotification:) name:(NSString *)kNdCPAsynPaySMSSentNotification object:nil];
}
//91启动完成
- (void)SNSInitResult:(NSNotification *)notify {
    //...执行应用的逻辑,例如显示工具条、登录
    //    cocos2d::CCApplication::sharedApplication()->run();
    //    [[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtTopLeft];
    
//    if ([[NdComPlatform defaultPlatform] isAutoLogin]) {
//        [[NdComPlatform defaultPlatform] NdLogin:0];
//    }
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
				//[CHANNELCALLBACK messageBox:strTip];
			}
		}
		else {
			// 普通账号登录成功!
            NSString* sessionID = [[NdComPlatform defaultPlatform] sessionId];
            NSString* uID = [[NdComPlatform defaultPlatform] loginUin];
            NSLog(@"91____%@,session = %@",notify,sessionID);
            CHANNELCALLBACK.user_ID = uID;
            CHANNELCALLBACK.token_Key = sessionID;
            CHANNELHELPER->loginVerifyRequest();
		}
		
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
        //[CHANNELCALLBACK messageBox:strTip];
        [CHANNELCALLBACK logout];
	}
}

//会话失效
- (void)SNSSessionInvalid:(NSNotification *)notify
{
	//[self performSelector:@selector(dismissModalViewControllerAnimated:) withObject:nil afterDelay:0.5];
	//[self performSelector:@selector(showStartView) withObject:nil afterDelay:0.6];
}

//离开平台
- (void)SNSleavePlatform:(NSNotification *)notify
{
    [CHANNELCALLBACK closeView];
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

- (void)NdUniPayAsynResult:(NSNotification *)notify
{
    NSLog(@"_____%s,%@",__FUNCTION__,notify);
}
- (void)NdCPBuyResultNotification:(NSNotification *)notify
{
    NSLog(@"_____%s,%@",__FUNCTION__,notify);
    
     NSDictionary *dic = [notify userInfo];
     BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
     NSString* str = bSuccess ? @"购买成功" : @"购买失败";
     NdBuyInfo* buyInfo = (NdBuyInfo*)[dic objectForKey:@"buyInfo"];
     str = [str stringByAppendingFormat:@"\n<productId = %@, productCount = %d,cooOrderSerial = %@>",
     buyInfo.productId, buyInfo.productCount, buyInfo.cooOrderSerial];
     NSLog(@"NdUiPayResult: %@", str);
     if (!bSuccess) {
         //TODO: 购买失败处理
         NSString* strError = nil;
         int nErrorCode = [[dic objectForKey:@"error"] intValue];
         switch (nErrorCode) {
             case ND_COM_PLATFORM_ERROR_USER_CANCEL: strError = @"用户取消操作";
                 break;
             case ND_COM_PLATFORM_ERROR_NETWORK_FAIL: strError = @"网络连接错误";
                 break;
             case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR: strError = @"服务端处理失败";
                 break;
             default:
                 strError = [NSString stringWithFormat:@"购买过程发生错误:%d",nErrorCode];
                 break;
         }
         str = [str stringByAppendingFormat:@"\n%@", strError];
         if (nErrorCode!=ND_COM_PLATFORM_ERROR_USER_CANCEL&&nErrorCode!=ND_COM_PLATFORM_ERROR_ORDER_SERIAL_SUBMITTED) {
             [CHANNELCALLBACK messageBox:strError];
         }
        
     }
     else {
     //TODO: 购买成功处理
     }
}
- (void)NdCPAsynPaySMSSentNotification:(NSNotification *)notify
{
    NSLog(@"_____%s,%@",__FUNCTION__,notify);
}
#endif
#pragma mark -------------------------------kuaiyong callback---------------------------------------------
#ifdef KY_VERSION
- (void)KYStartListen
{
    [[KYSDK instance] setSdkdelegate:CHANNELCALLBACK];
    //注册支付宝通知接收
    //[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(KYPayResult:) name:@"KY_NOTIFICATION" object:nil];
}

//-(void)KYCheckCode:(CHECK)result
//{
//    //    SERVICE_CHECK = -1,     //等待服务器验证
//    //    PAY_SUCCESS = 0,        //结果正确
//    //    PAY_FAILE = 1,          //结果错误
//    //    PAY_ERROR = 2          //验证失败
//    //根据不同结果判断
//    
//}

//--KyUserSDKDelegate--
//登录成功回调
-(void)loginCallBack:(NSString *)tokenKey{
    
    //CHANNELCALLBACK.user_ID = [notification.object objectForKey:@"userId"];
    CHANNELCALLBACK.token_Key =tokenKey;
    CHANNELHELPER->loginVerifyRequest();
    
    NSLog(@"log  log log!!!");
}
//快速试玩登录成功回调
-(void)quickLogCallBack:(NSString *)tokenKey{
    
    //CHANNELCALLBACK.user_ID = [notification.object objectForKey:@"userId"];
    CHANNELCALLBACK.token_Key =tokenKey;
    CHANNELHELPER->loginVerifyRequest();
}

//游戏张后登录后回调(可选，有老用户的开发商接入)
-(void)gameLogBack:(NSString *)username passWord:(NSString *)password
{
    /*
     UIAlertView * tip2 = [[UIAlertView alloc]initWithTitle:@"游戏账号登录成功" message:[NSString stringWithFormat:@"登录名：%@  密码：%@",username,password] delegate:nil cancelButtonTitle:@"ok" otherButtonTitles:nil];
     [tip2 show];
     [tip2 release];
     
     //游戏判断返回用户名密码是否正确，如果错误，将错误信息和类型传入sdk
     [[KYSDK instance]gameLogMes:@"错误信息" state:KYLOG_ERROR];
     */
}

//用户注销后回调
-(void)logOutCallBack:(NSString *)guid
{
    CHANNELCALLBACK.isLogin = false;
    
    [CHANNELCALLBACK logout];
}
-(void)returnKeyDidClick
{
    CCLOG("____%s___",__FUNCTION__);
}

//查看订单返回结果
/**
 result: code为0时，成功 其他失败
 deal：订单信息 orderid：sdk内部订单信息 dealSeq：游戏订单信息 dealSeq
 payresult = 0支付成功，1支付失败
 **/
-(void)backCheckDel:(NSMutableDictionary *)map
{
    NSLog(@"____%s___kind = %@",__FUNCTION__,map);
}
/**
 *  银联支付回调函数
 */
-(void)UPPayPluginResult:(UNIPAYTYPE)result
{
    if (result==USER_UNIPAY_SUCCESS) {
        
    }
}
/**
 *  关闭支付界面"关闭"按钮的回调
 */
-(void)closePayCallback
{
    
}
#pragma mark --KYMobilePayDelegate--
-(void)onBillingResult:(BillingResultType)resultCode billingIndex:(NSString *)index message:(NSString *)message
{
    if (resultCode==BillingResultSucceed) {
        
    }else if (resultCode==BillingResultFailed){
        
    }
    
}
//支付宝回调
-(void)alipayCallBack:(ALIPAYRESULT)alipayresult
{
    if (alipayresult==PAY_DONE) {
        
    }
}
#endif
#pragma mark -------------------------------itools callback---------------------------------------------
#ifdef IT_VERSION
- (void)itoolsStartListen
{
    //监听注册通知
    [[NSNotificationCenter defaultCenter] addObserver:CHANNELCALLBACK selector:@selector(itoolsRegisterNotification:) name:HX_NOTIFICATION_REGISTER object:nil];
    
    //监听登录通知
    [[NSNotificationCenter defaultCenter] addObserver:CHANNELCALLBACK selector:@selector(itoolsLoginNotification:) name:HX_NOTIFICATION_LOGIN object:nil];
    
    //视图关闭通知
    [[NSNotificationCenter defaultCenter] addObserver:CHANNELCALLBACK selector:@selector(itoolsCloseViewNotification:) name:HX_NOTIFICATION_CLOSEVIEW object:nil];
    
    //注销通知
    [[NSNotificationCenter defaultCenter] addObserver:CHANNELCALLBACK selector:@selector(itoolsLogoutNotification:) name:HX_NOTIFICATION_LOGOUT object:nil];
}

//注册通知处理
- (void)itoolsRegisterNotification:(NSNotification *)notification
{
    NSLog(@"userId: %@", [notification.object objectForKey:@"userId"]);
    NSLog(@"userName: %@", [notification.object objectForKey:@"userName"]);
    NSLog(@"sessionId: %@", [notification.object objectForKey:@"sessionId"]);
}

//登录通知处理
- (void)itoolsLoginNotification:(NSNotification *)notification
{
    CHANNELCALLBACK.user_ID = [notification.object objectForKey:@"userId"];
    CHANNELCALLBACK.token_Key =[notification.object objectForKey:@"sessionId"];
    CHANNELHELPER->loginVerifyRequest();
    
	NSLog(@"userId: %@", [notification.object objectForKey:@"userId"]);
    NSLog(@"userName: %@", [notification.object objectForKey:@"userName"]);
    NSLog(@"sessionId: %@", [notification.object objectForKey:@"sessionId"]);
}

//关闭窗口通知处理
- (void)itoolsCloseViewNotification:(NSNotification *)notification
{
    [CHANNELCALLBACK closeView];
    NSLog(@"SDK View Closed,%@ ",notification);
    if (CHANNELCALLBACK.payViewOpened) {
        //itools check order
    }
    CHANNELCALLBACK.payViewOpened = false;
}

//注销通知处理
- (void)itoolsLogoutNotification:(NSNotificationCenter *)notification
{
    NSLog(@"Logout");
    CHANNELCALLBACK.isLogin = false;
    
    [CHANNELCALLBACK logout];
}
#endif
#pragma mark -------------------------------i4 callback---------------------------------------------
#ifdef I4_VERSION
- (void)asStartListen
{
   [[AsPlatformSDK sharedInstance] setDelegate:CHANNELCALLBACK];
}
- (void)asPayResultCallBack:(AsPayResultCode)paramPPPayResultCode
{
    
}

- (void)asVerifyingUpdatePassCallBack
{
    //[[AsPlatformSDK sharedInstance] showLogin];
}

- (void)asLoginCallBack:(NSString *)paramToken
{
    [[AsPlatformSDK sharedInstance] currentUserName];
    [[AsPlatformSDK sharedInstance] currentUserId];
    NSLog(@"登陆回调 - %@",paramToken);
    
    CHANNELCALLBACK.user_ID = [NSString stringWithFormat:@"%llu",[[AsPlatformSDK sharedInstance] currentUserId]];
    CHANNELCALLBACK.token_Key =paramToken;
    CHANNELHELPER->loginVerifyRequest();
}

- (void)asLogOffCallBack
{
    NSLog(@"注销回调");
    
    CHANNELCALLBACK.isLogin = false;
    [CHANNELCALLBACK logout];
    
    static BOOL isPad;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken,^{
        isPad = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad);
    });
    float delay = isPad ? 1.2 : 0.6;
    //[[AsPlatformSDK sharedInstance] performSelector:@selector(showLogin) withObject:nil afterDelay:delay];
    
    //    NSURLErrorNetworkConnectionLost
}

- (void)asClosePageViewCallBack:(AsPageCode)paramPPPageCode
{
    NSLog(@"关闭页面的回调%d",paramPPPageCode);
}


- (void)asCloseWebViewCallBack:(AsWebViewCode)paramWebViewCode
{
    NSLog(@"关闭网页是%d",paramWebViewCode);
}

- (void)asClosedCenterViewCallBack
{
    // 点击按钮关闭用户中心的回调
    NSLog(@"点击按钮关闭用户中心的回调");
}
#endif
#pragma mark -------------------------------hm callback---------------------------------------------
#ifdef HM_VERSION
- (void)loginDidSuccessWithUserName:(NSString *)userName andTempToken:(NSString *)tempToken
{
    NSLog(@"%s:%@,%@",__FUNCTION__,userName,tempToken);
    //NSString* str = [NSString stringWithFormat:@"SDK回调-登陆成功%@,Token:%@",userName,tempToken];
    CHANNELCALLBACK.user_ID = userName;
    CHANNELCALLBACK.token_Key = tempToken;
    CHANNELHELPER->loginVerifyRequest();
}
- (void)loginDidFail
{
    NSLog(@"%s",__FUNCTION__);
}
- (void)loginDidCancel
{
    NSLog(@"%s",__FUNCTION__);
}


- (void)hmStartListen
{
   
}
- (void)checkUpdateFinish:(BOOL)isSuccess shouldUpdate:(BOOL)update isForceUpdate:(BOOL)force
{
    NSLog(@"更新检查是否成功：%d 是否有新版本：%d 是否强更：%d",isSuccess,update,force);
}

- (void)getStatusInitialized
{

}
-(void)paymentStatusCode:(IPAYKITPaymentStatusCodeType)statusCode signature:(NSString *)signature resultInfo:(NSString *)resultInfo
{
    NSLog(@"DEMO执行SDK的回调=%d",statusCode);
    
    if (statusCode==IPAY_PAYMENT_SUCCESS)
    {
        //[SVProgressHUD showSuccessWithStatus:@"SDK回调-支付成功" duration:5.0f];
        
    }
    else if (statusCode == IPAY_PAYMENT_FAILED)
    {
        //[SVProgressHUD showErrorWithStatus:@"SDK回调-支付失败" duration:5.0f];
    }
    else
    {
        // NSTimeInterval duration = 0.5;
        
        //[SVProgressHUD showErrorWithStatus:@"SDK回调-支付取消" duration:5.0f];
        
        //[SVProgressHUD showErrorWithStatus:@"SDK回调-支付取消" duration:5.0f];
    }
}
/*
- (void)loginDidSuccessWithUserName: (NSString *)userName
{
    CHANNELCALLBACK.user_ID = userName;
    CHANNELCALLBACK.token_Key =@"";
    CHANNELHELPER->loginVerifyRequest();
}
- (void)loginDidFail
{
    
}
- (void)loginDidCancel // 游戏自行根据用户登录返回状态，确定强制用户登录的逻辑和UI。
{

}
- (void)paymentStatusCode: (IPAYiAppPayPaymentStatusCodeType)statusCode
                signature: (NSString *)signature
               resultInfo: (NSString *)resultInfo
{
    if(statusCode == IPAY_PAYMENT_SUCCESS)
    {
        if([[IPAYiAppPay sharediAppPay] verifyPaymentSignature:signature withAppKey:nil])
        {
//            UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
//                                                                 message:@"支付成功！"
//                                                                delegate:nil
//                                                       cancelButtonTitle:@"确定"
//                                                       otherButtonTitles:nil];
//            [alertView show];
        }
        else
        {
//            UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
//                                                                 message:@"支付成功,验签失败！"
//                                                                delegate:nil
//                                                       cancelButtonTitle:@"确定"
//                                                       otherButtonTitles:nil];
//            [alertView show];
        }
    }
    else if(statusCode == IPAY_PAYMENT_CANCELED)
    {
//        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
//                                                             message:@"支付失败，用户取消支付！"
//                                                            delegate:nil
//                                                   cancelButtonTitle:@"确定"
//                                                   otherButtonTitles:nil];
//        [alertView show];
    }
    else
    {
        //        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
        //                                                             message:@"支付失败！"
        //                                                            delegate:nil
        //                                                   cancelButtonTitle:@"确定"
        //                                                   otherButtonTitles:nil];
        //        [alertView show];
    }
}
 */
#endif
#pragma mark -------------------------------appstore callback---------------------------------------------
#ifdef APPSTORE_VERSION
//-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
//{
//
//}
-(BOOL)checkOrder
{
    if ([CHANNELCALLBACK visitOrder]) {
        [CHANNELCALLBACK showAlert:@"检查到您有未处理完成的订单，正在为您重新处理..."];
        return YES;
    }
    return NO;
}
-(BOOL)visitOrder
{
    BOOL ret = NO;
    int aid,pid,svr = 0;
    ModuleData::getInt(CPModuleName::LOGIN, CPLoginData::AID, aid);
    pid = HeroData::getPID();
    svr = LoginHelper::getSavedServerId();
    if (aid<0) aid=0;
    if (pid<0) pid=0;
    if (svr<0) svr=0;
    if (aid==0||pid==0||svr==0) {
        return NO;
    }
    
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    NSDictionary* user_dic = [userdefault objectForKey:@"yidaoliu_iap_transaction"];
    
    NSArray* array = [user_dic allKeys];
    //for (NSDictionary *object in user_dic) {
    for(NSString* str in array){
        NSDictionary* dic = [user_dic objectForKey:str];
        NSLog(@"_++++%@_%@",str,dic);
        if (dic) {
            NSString* orderID = [dic objectForKey:@"order_id"];
            NSString* recepit = [dic objectForKey:@"recepit"];
            NSString* transactionIdentifier = [dic objectForKey:@"transactionIdentifier"];
            NSString* productIdentifier = [dic objectForKey:@"productIdentifier"];
            
            NSArray* array = [orderID componentsSeparatedByString:@"-"];
            //sprintf(order, "%d-%d-%d-%d",aid,pid,svr,cur_time);
            if ([array count]==4) {
                int o_aid = [[array objectAtIndex:0]intValue];
                int o_pid = [[array objectAtIndex:1]intValue];
                int o_svr = [[array objectAtIndex:2]intValue];
                if (aid==o_aid&&pid==o_pid&&svr==o_svr) {
                    ret = YES;
                    if(orderID&&recepit&&transactionIdentifier&&productIdentifier){
                        [[ECPurchase shared] sendReceiptToServer:orderID andTransactionIdentifier:transactionIdentifier andRecepit:recepit andProductIdentifier:productIdentifier];
                    }
                }
            }
            
        }
        
    }
    return ret;
}
-(BOOL)startPay
{
    if(!CHANNELCALLBACK.isPaying)
    {
        CHANNELCALLBACK.isPaying = YES;
        string note = SystemData::getLayoutString("appstore_paying");//LayoutData::getString(CPModuleName::VIP, "appstore_paying");
        CHANNELHELPER->showTip(note);
        //[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(endPay) object:nil];
        //[CHANNELCALLBACK performSelector:@selector(endPay) withObject:nil afterDelay:60.0f];
        return YES;
    }
    else{
        CPEventHelper::uiNotify("","",-999);
        return NO;
    }
    return NO;
}
-(void)endPay
{
    CHANNELCALLBACK.isPaying = NO;
    CHANNELHELPER->hideTip();
    //[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(endPay) object:nil];
}

-(void)showAlert:(NSString*)stringTip
{
    if (!CHANNELCALLBACK.rechargeAlert) {
        CHANNELCALLBACK.rechargeAlert = [[[UIAlertView alloc]initWithTitle:nil message:stringTip delegate:nil cancelButtonTitle:nil otherButtonTitles: nil]autorelease];
        [CHANNELCALLBACK.rechargeAlert show];
        //[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(hideAlert) object:nil];
        //[CHANNELCALLBACK performSelector:@selector(hideAlert) withObject:nil afterDelay:30.0f];
    }
}
-(void)hideAlert
{
    if (CHANNELCALLBACK.rechargeAlert) {
        [CHANNELCALLBACK.rechargeAlert dismissWithClickedButtonIndex:-1 animated:YES];
        CHANNELCALLBACK.rechargeAlert = nil;
        //[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(hideAlert) object:nil];
    }
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    [CHANNELCALLBACK hideAlert];
    [CHANNELCALLBACK endPay];
    
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"失败" message:[error localizedDescription]
                                                       delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
    [alerView show];
    [alerView release];
}
-(void)didFailedTransaction:(NSString *)proIdentifier
{
    NSLog(@"%s,%@",__FUNCTION__,proIdentifier);
    [CHANNELCALLBACK hideAlert];
    [CHANNELCALLBACK endPay];
    
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"出错了",NULL) message:@"交易失败！"
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"确定",nil) otherButtonTitles:nil];
    [alerView show];
    [alerView release];
}
-(void)didRestoreTransaction:(NSString *)proIdentifier
{
    NSLog(@"%s,%@",__FUNCTION__,proIdentifier);
}
-(void)didCompleteTransaction:(NSString *)proIdentifier
{
    NSLog(@"%s,%@",__FUNCTION__,proIdentifier);
}
-(void)didCompleteTransactionAndVerifySucceed:(NSString *)proIdentifier
{
    [CHANNELCALLBACK hideAlert];
    [CHANNELCALLBACK endPay];
    NSLog(@"%s,%@",__FUNCTION__,proIdentifier);
}
-(void)didCompleteTransactionAndVerifyFailed:(NSString *)proIdentifier withError:(NSString *)error
{
    [CHANNELCALLBACK hideAlert];
    [CHANNELCALLBACK endPay];
    NSLog(@"%s,%@,%@",__FUNCTION__,proIdentifier,error);
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"交易失败",NULL) message:error
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"确定",nil) otherButtonTitles:nil];
    [alerView show];
    [alerView release];
}
-(void)didReceivedProducts:(NSArray *)products
{
    [CHANNELCALLBACK hideAlert];
}
-(NSString*)getRechargeVerifyURL
{
    string url = SystemData::getConfigString("appstore_rechargeVerifyURL");
    CHANNELCALLBACK.rechargeVerifyURL = [NSString stringWithUTF8String:url.c_str()];
    NSLog(@"___CHANNELCALLBACK.rechargeVerifyURL=%@",CHANNELCALLBACK.rechargeVerifyURL);
    return CHANNELCALLBACK.rechargeVerifyURL;
}
-(NSString*)getNewOrderID
{
    NSString* ret = [CHANNELCALLBACK getOrderID];
    if (!ret||[ret isEqualToString:@""]||ret.length<=0) {
        [CHANNELCALLBACK endPay];
    }
    return ret;
}
#endif
#pragma mark -------------------------------3737 callback---------------------------------------------
#ifdef C3737_VERSION
- (void)c3737StartListen
{
    
}
- (void)getInitStatus: (BOOL)isSucceeded
{

}
- (void)loginDidSuccessWithUserName: (NSString *)userName
{
    CHANNELCALLBACK.user_ID = userName;
    CHANNELCALLBACK.token_Key =@"";
    CHANNELHELPER->loginVerifyRequest();
}
- (void)loginDidFail
{
    
}
- (void)loginDidCancel // 游戏自行根据用户登录返回状态，确定强制用户登录的逻辑和UI。
{
    
}

- (void)paymentStatusCode: (IPAYiAppPayPaymentStatusCodeType)statusCode
                signature: (NSString *)signature
               resultInfo: (NSString *)resultInfo
{
    if(statusCode == IPAY_PAYMENT_SUCCESS)
    {
        if([[IPAYiAppPay sharediAppPay] verifyPaymentSignature:signature withAppKey:nil])
        {
            //            UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
            //                                                                 message:@"支付成功！"
            //                                                                delegate:nil
            //                                                       cancelButtonTitle:@"确定"
            //                                                       otherButtonTitles:nil];
            //            [alertView show];
        }
        else
        {
            //            UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
            //                                                                 message:@"支付成功,验签失败！"
            //                                                                delegate:nil
            //                                                       cancelButtonTitle:@"确定"
            //                                                       otherButtonTitles:nil];
            //            [alertView show];
        }
    }
    else if(statusCode == IPAY_PAYMENT_CANCELED)
    {
        //        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
        //                                                             message:@"支付失败，用户取消支付！"
        //                                                            delegate:nil
        //                                                   cancelButtonTitle:@"确定"
        //                                                   otherButtonTitles:nil];
        //        [alertView show];
    }
    else
    {
        //        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
        //                                                             message:@"支付失败！"
        //                                                            delegate:nil
        //                                                   cancelButtonTitle:@"确定"
        //                                                   otherButtonTitles:nil];
        //        [alertView show];
    }
}
#endif
#pragma mark -------------------------------xy callback---------------------------------------------
#ifdef XY_VERSION
- (void)xyStartListen
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(xyplatformInitFinished:)
                                                 name:kXYPlatformInitDidFinishedNotification
                                               object:nil];
    //添加XYPlatform 各类通知的观察者
    
    /*初始化结束通知, 登录等操作务必在收到该通知后调用*/
    
    /*登录通知*/
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(xyplatformLoginNoti:)
                                                 name:kXYPlatformLoginNotification
                                               object:nil];
    
    /* 注销登录通知 */
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(xyplatformLogoutFinished:)
                                                 name:kXYPlatformLogoutNotification
                                               object:nil];
    
    /*离开平台通知*/
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(xyplatformLeavedPlatform:)
                                                 name:kXYPlatformLeavedNotification
                                               object:nil];
}
- (void)xyplatformInitFinished:(NSNotification*)notification
{
    //[[XYPlatform defaultPlatform] XYAutoLogin:0];
}
#pragma mark-- 登录注册 回调通知
- (void)xyplatformLoginNoti:(NSNotification*)notification
{
    // 登录完成, 提供token 以及 openuid 给游戏校验
    NSDictionary *userInfo = notification.userInfo;
    if ([userInfo[kXYPlatformErrorKey] intValue] == XY_PLATFORM_NO_ERROR) {
        [self doSomeThingAfterLoginOrRegister:0];
    }
}

- (void) doSomeThingAfterLoginOrRegister:(int) lr
{
    // 登录成功，开发者可继续游戏逻辑
    
    NSString* token = [[XYPlatform defaultPlatform] XYToken];       // token
    NSString* openuid = [[XYPlatform defaultPlatform] XYOpenUID];   // uid
    CHANNELCALLBACK.user_ID = openuid;
    CHANNELCALLBACK.token_Key =token;
    CHANNELHELPER->loginVerifyRequest();
}
#pragma mark-- 注销
- (void)xyplatformLogoutFinished:(NSNotification*)notification
{
    NSLog(@"logout finished.");
}
#pragma mark-- 充值回调 XYPayDelegate
- (void) XYPayFailedWithOrder:(NSString *)orderId
{
    //  支付失败
    NSLog(@"支付失败  orderID＝ %@", orderId);
}

- (void) XYPaySuccessWithOrder:(NSString *)orderId
{
    // 支付成功
    NSLog(@"支付成功  orderID＝ %@", orderId);
    [self doSomeThingAfterPayActionWithOrder:orderId];
}

- (void) XYPayDidCancelByUser:(NSString *)orderId
{
    // 用户取消操作，若orderId为空则是用户取消充值， 若orderId不为空则不确定支付成功或失败
    
    NSLog(@"用户取消支付 orderID＝ %@", orderId);
    if ([orderId length] == 0) {
        // here 用户取消充值
    }else{
        [self doSomeThingAfterPayActionWithOrder:orderId];
    }
}

- (void) doSomeThingAfterPayActionWithOrder:(NSString *) orderId
{
    NSLog(@"此处可查询订单情况");
    
    //  若需要查询订单情况，可访问游戏服务器查看订单支付情况 或者调用 sdk 接口 XYCheckPayOrderInfo:delegate: 查看
    [self doCheckOrderAction:orderId];
}


#pragma mark-- 查询订单


- (void) doCheckOrderAction:(NSString *) orderId
{
    //    NSString *orderId = [[XYPlatform defaultPlatform] XYGetLastPayOrder];
    NSLog(@"查询订单 orderID ＝ %@", orderId);
    int ret =  [[XYPlatform defaultPlatform] XYCheckPayOrderInfo:orderId delegate:self];
    if (ret == XY_PLATFORM_ERROR_PAY_ORDERID_NIL) {
        //[[[UIAlertView alloc] initWithTitle:nil message:@"订单为空" delegate:nil cancelButtonTitle:@"好" otherButtonTitles:nil, nil] show];
    }
}

// 查看订单回调
- (void) XYCheckedOrderFinishedWithOrder:(NSString *) orderId
                                  amount:(NSString *) amount
                                  status:(XYCheckPayOrderStatus) orderStatus
{
    /*
     XYPayOrderStatus_NoPay              = 0,  // 未支付
     XYPayOrderStatus_Shipping           = 1,  // 正在发货
     XYPayOrderStatus_Success            = 2,  // 支付成功，发货成功
     XYPayOrderStatus_PayFailed          = 3,  // 支付失败
     XYPayOrderStatus_Repairing          = 4,  // 补单中
     XYPayOrderStatus_Repaired           = 5,  // 补单完成，发货成功
     XYPayOrderStatus_ShipInvalid        = 8,  // 发货无返回或返回无法解析
     XYPayOrderStatus_Payed_ShipFailed   = 9   // 支付成功，发货失败
     */
    NSString *status;
    if (orderStatus == XYPayOrderStatus_NoPay) {
        status = @"未支付";
    }else if (orderStatus == XYPayOrderStatus_Shipping){
        status = @"正在发货";
    }else if (orderStatus == XYPayOrderStatus_Success){
        status = @"支付成功，发货成功";
        
        // 支付发货成功，发放游戏道具等
        
    }else if (orderStatus == XYPayOrderStatus_PayFailed){
        status = @"支付失败";
    }else if (orderStatus == XYPayOrderStatus_Payed_ShipFailed){
        status = @"支付成功，发货失败";
    }else
        status = [NSString stringWithFormat:@"%d", orderStatus];
    
    // demo
    NSString *msg = [NSString stringWithFormat:@"订单：%@ 金额：%@ 支付状态: %@", orderId, amount, status];
    NSLog(@"查询订单：%@", msg);
//    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil message:msg delegate:nil cancelButtonTitle:@"好" otherButtonTitles:nil, nil];
//    [alertView show];
    
}

- (void) XYCkeckOrderDidFailed:(NSString *) orderId
                     errorCode:(XY_PAY_ERROR) etc
                      errorMsg:(NSString *) errMsg
{
    // 查询订单失败，
    // demo
//    NSString *msg = [NSString stringWithFormat:@"查询失败 订单：%@  错误码：%d errMsg: %@", orderId, etc, errMsg];
//    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil message:msg delegate:nil cancelButtonTitle:@"好" otherButtonTitles:nil, nil];
//    [alertView show];
}



#pragma mark-- LevedPlatform Notification

- (void)xyplatformLeavedPlatform:(NSNotification*)notification
{
    NSNumber* leavedType = (NSNumber*)notification.object;
    
    switch ([leavedType integerValue]) {
        case XYPlatformLeavedDefault: {
            //TTDEBUGLOG(@"用户离开平台－－> XYPlatformLeavedDefault");
            break;
        }
        case XYPlatformLeavedFromLogin: {
            //TTDEBUGLOG(@"用户离开平台－－> XYPlatformLeavedFromLogin");
            
            [[XYPlatform defaultPlatform] XYIsLogined:^(BOOL isLogined) {
                if (!isLogined) {
                    [[XYPlatform defaultPlatform] XYUserLogin:0];
                }
            }];
            
            break;
        }
        case XYPlatformLeavedFromRegister: {
            //TTDEBUGLOG(@"用户离开平台－－> XYPlatformLeavedFromRegister");
            
            [[XYPlatform defaultPlatform] XYIsLogined:^(BOOL isLogined) {
                if (!isLogined) {
                    [[XYPlatform defaultPlatform] XYUserLogin:0];
                }
            }];
            
            break;
        }
        case XYPlatformLeavedFromPayment: {
            //TTDEBUGLOG(@"用户离开平台－－> XYPlatformLeavedFromPayment");
            break;
        }
        case XYPlatformLeavedFromSNSCenter:{
            //TTDEBUGLOG(@"用户离开平台－－> XYPlatformLeavedFromUserCenter");
            break;
        }
            
        default:
            //TTDEBUGLOG(@"用户离开平台－－> NULL");
            break;
    }
}

#endif
#pragma mark -------------------------------VTCid callback---------------------------------------------
#ifdef VTCID_VERSION
- (void)vtcidStartListen
{
    
}
- (void)vtcidLogin:(NSString *)account AccessToken:(NSString *)accesstoken AccountID:(long long)aid
{
//    account_id = aid;
//    account_name = [account copy];
//    gameToken = [accesstoken copy];
//    
//    _lblResult.text = [NSString stringWithFormat:@"AccountName:%@, AcountID:%lld Token:%@", account, aid, accesstoken];

    //[[LibVTCid shareInstance]  setAccountID:aid];
    //[[LibVTCid shareInstance]  setGameToken:accesstoken];
    CHANNELCALLBACK.user_ID = [NSString stringWithFormat:@"%llu",aid];
    CHANNELCALLBACK.token_Key =accesstoken;
    CHANNELHELPER->loginVerifyRequest();
    
    //NSLog(@"_____uid=%llu,%llu",[CHANNELCALLBACK.user_ID longLongValue],aid);
}

- (void)topupClosed
{
    NSLog(@"%s",__FUNCTION__);
}

#endif
#pragma mark -------------------------------IIAPPLE callback---------------------------------------------
#if defined IIAPPLE_VERSION
- (void)iiappleStartListen
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(iiappleLoginNoti:)
                                                 name:IALOGINSUCCEED
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(iiappleLoginOut:)
                                                 name:IALOGOUTSUCCEED
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(iiapplePayCallback:)
                                                 name:IAPAYSUCCEED
                                               object:nil];
}
- (void)iiappleLoginNoti:(NSNotification*)notification
{
    // 登录完成, 提供token 以及 openuid 给游戏校验
    NSDictionary *userInfo = notification.object;
    NSString* session = [userInfo objectForKey:@"session"];
    NSString* userid = [userInfo objectForKey:@"userid"];
    CHANNELCALLBACK.user_ID = userid;
    CHANNELCALLBACK.token_Key = session;
    CHANNELHELPER->loginVerifyRequest();
}
- (void)iiappleLoginOut:(NSNotification*)notification
{
    NSLog(@"注销的回调");
    
    CHANNELCALLBACK.isLogin = false;
    [CHANNELCALLBACK logout];
}
- (void)iiapplePayCallback:(NSNotification*)notification
{
    NSLog(@"购买的回调");
}
#endif
@end
