//
//  ECPurchase.m
//  myPurchase
//
//  Created by ris on 10-4-23.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ECPurchase.h"
#import "SBJSON.h"
#import "GTMBase64.h"
#import "ChannelCallBack.h"

/*
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "ext/json/json.h"
USING_NS_CC_EXT;
static void didFinishVerifyWithServer_cpp( CCHttpClient* client, CCHttpResponse* response )
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())//
	{
		return ;
	}
    
	std::vector<char> *buffer = response->getResponseData();//
    std::string recieveData;
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		recieveData += (*buffer)[i];
	}
    
	Json::Reader reader;
	Json::Value root;
	reader.parse(recieveData,root);
	Json::Value errorvalue = root.get("errorcode",-1);
    Json::Value transactionvalue = root.get("transaction_id",-1);
    
    if (errorvalue.isNumeric()) {
        int errorcode = errorvalue.asInt();
        if (errorcode&&errorcode == 0) {
            NSLog(@"－－－－－－－支付成功－－－－－－－");
            UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"成功" message:@"兑换商品成功"
                                                               delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
            [alerView show];
            [alerView release];
            if (transactionvalue.isString()) {
                std::string transaction_id = transactionvalue.asString();
                [ECPurchase removeLocalTransaction:[NSString stringWithUTF8String:transaction_id.c_str()]];
            }
        }
        else {
            NSLog(@"－－－－－－－支付失败－－－－－－－");
            UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"出错了" message:@"兑换商品失败，"
                                                               delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
            [alerView show];
            [alerView release];
        }
    }
}
*/
/******************************
 SKProduct extend
 *****************************/
@implementation SKProduct (LocalizedPrice)

- (NSString *)localizedPrice{
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:self.priceLocale];
    NSString *formattedString = [numberFormatter stringFromNumber:self.price];
    [numberFormatter release];
    return formattedString;
}

@end

/***********************************
 ECPurchaseHTTPRequest
 ***********************************/
@implementation ECPurchaseHTTPRequest
@synthesize productIdentifier = _productIdentifier;

@end

/******************************
 ECPurchase
 ******************************/
@implementation ECPurchase
@synthesize productDelegate = _productDelegate;
@synthesize transactionDelegate =_transactionDelegate;
@synthesize verifyRecepitMode = _verifyRecepitMode;

SINGLETON_IMPLEMENTATION(ECPurchase);

//you can init the object here as the object init is in SINGLETON_IMPLEMENTATION
-(void)postInit
{
	_verifyRecepitMode = ECVerifyRecepitModeServer;
    _orderID = @"";
	[self registerNotifications];
}

- (void)requestProductData:(NSArray *)proIdentifiers{
    NSArray* remainTransactions = [SKPaymentQueue defaultQueue].transactions;
    if (remainTransactions.count > 0) {
        //检测是否有未完成的交易
        SKPaymentTransaction* remainTransaction = [remainTransactions firstObject];
        if (remainTransaction.transactionState == SKPaymentTransactionStatePurchased) {
            [_storeObserver completeTransaction:remainTransaction];
            [[SKPaymentQueue defaultQueue] finishTransaction:remainTransaction];
            return;
        }
    }
//start
    
	NSSet *sets = [NSSet setWithArray:proIdentifiers];
    _productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:sets];
    _productsRequest.delegate = self;
    [_productsRequest start];
    [_productsRequest release];
}

#pragma mark -
#pragma mark SKProductsRequestDelegate methods
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    NSArray *products = response.products;
    /*
#ifdef ECPURCHASE_TEST_MODE	
	NSMutableString *result = [[NSMutableString alloc] init];
	for (int i = 0; i < [products count]; ++i) {
		SKProduct *proUpgradeProduct = [products objectAtIndex:i];
		[result appendFormat:@"%@,%@,%@,%@\n",
		 proUpgradeProduct.localizedTitle,proUpgradeProduct.localizedDescription,proUpgradeProduct.price,proUpgradeProduct.productIdentifier];
	}
    
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
		[result appendFormat:@"Invalid product id: %@",invalidProductId];
    }
	
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"iap" message:result
										delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
	[_productDelegate didReceivedProducts:products];
#else
     */
    _orderID = [[_productDelegate getNewOrderID]copy];
    if (!_orderID||[_orderID isEqual:@""]) {
        return;
    }
    
    if (products&&products.count>0) {
        [[ECPurchase shared] addPayment:[products lastObject]];
    }

//#endif
    NSLog(@"-----------收到产品反馈信息--------------");
    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
    NSLog(@"产品付费数量: %d", [products count]);
    //test
    if([products count]<=0)
    {
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"出错了"
                                                            message:[NSString stringWithFormat:@"获取商品信息失败：%d",[products count]]
                                                           delegate:nil cancelButtonTitle:@"确认" otherButtonTitles:nil];
        
        [alerView show];
        [alerView release];
        [CHANNELCALLBACK endPay];
        return;
    }
    //test end
    
    // populate UI
    for(SKProduct *product in products){
        NSLog(@"product info");
        NSLog(@"SKProduct 描述信息%@", [product description]);
        NSLog(@"产品标题 %@" , product.localizedTitle);
        NSLog(@"产品描述信息: %@" , product.localizedDescription);
        NSLog(@"价格: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
    }
    
    [_productDelegate didReceivedProducts:products];
	//[_productsRequest release];
    //dismiss
}

-(void)addTransactionObserver{
	_storeObserver = [[ECStoreObserver alloc] init];
	[[SKPaymentQueue defaultQueue] addTransactionObserver:_storeObserver];
}

-(void)removeTransactionObserver{
	[[SKPaymentQueue defaultQueue] removeTransactionObserver:_storeObserver];
}

- (BOOL)isJailbroken {
    BOOL jailbroken = NO;
    NSString *cydiaPath = @"/Applications/Cydia.app";
    NSString *aptPath = @"/private/var/lib/apt/";
    if ([[NSFileManager defaultManager] fileExistsAtPath:cydiaPath]) {
        jailbroken = YES;
    }
    if ([[NSFileManager defaultManager] fileExistsAtPath:aptPath]) {
        jailbroken = YES;
    }
    return jailbroken;
}

-(void)addPayment:(SKProduct *)product{
    if ([[_productDelegate getRechargeVerifyURL] length]<=0) {
        [_transactionDelegate didCompleteTransactionAndVerifyFailed:product.productIdentifier withError:@"invalid recharge verify URL"];
        return;
    }
    if (![SKPaymentQueue canMakePayments]) {
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"出错了"
                                                            message:@"应用程序内购买被禁用"
                                                           delegate:nil cancelButtonTitle:@"关闭" otherButtonTitles:nil];
        
        [alerView show];
        [alerView release];
        [CHANNELCALLBACK endPay];
        return;
    }
    /*
    if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"cydia://"]]||[self isJailbroken]) {
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"出错了"
                                                            message:@"越狱设备无法进行appstore支付"
                                                           delegate:nil cancelButtonTitle:@"关闭" otherButtonTitles:nil];
        
        [alerView show];
        [alerView release];
        [CHANNELCALLBACK endPay];
        return;
    }
    */

    //SKPayment *payment = [SKPayment paymentWithProduct:product];
    
	SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
    //payment.quantity = 10;
    //payment.applicationUsername = orderID;
    //NSLog(@"----%@",payment.applicationUsername);
	[[SKPaymentQueue defaultQueue] addPayment:payment];
}

#pragma mark -
#pragma mark NSNotificationCenter Methods
-(void)completeTransaction:(NSNotification *)note{
	SKPaymentTransaction *trans = [[note userInfo] objectForKey:@"transaction"];
	if (_verifyRecepitMode == ECVerifyRecepitModeNone) {
		[_transactionDelegate didCompleteTransaction:trans.payment.productIdentifier];
	}
	else if(_verifyRecepitMode == ECVerifyRecepitModeiPhone){
		[self verifyReceipt:trans];
	}
	else if(_verifyRecepitMode == ECVerifyRecepitModeServer){
		[self verifyReceiptWithServer:trans];
	}
	
}

-(void)failedTransaction:(NSNotification *)note{
    NSLog(@"___failedTransaction_%@",note);
	SKPaymentTransaction *trans = [[note userInfo] objectForKey:@"transaction"];
	[_transactionDelegate didFailedTransaction:trans.payment.productIdentifier];
}

-(void)restoreTransaction:(NSNotification *)note{
	SKPaymentTransaction *trans = [[note userInfo] objectForKey:@"transaction"];
	[_transactionDelegate didRestoreTransaction:trans.payment.productIdentifier];
}

-(void)registerNotifications{
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(completeTransaction:) name:@"completeTransaction" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(failedTransaction:) name:@"failedTransaction" object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(restoreTransaction:) name:@"restoreTransaction" object:nil];
}

-(void)verifyReceipt:(SKPaymentTransaction *)transaction
{
	_networkQueue = [ASINetworkQueue queue];
	[_networkQueue retain];
	NSURL *verifyURL = [NSURL URLWithString:VAILDATING_RECEIPTS_URL];
	ECPurchaseHTTPRequest *request = [[ECPurchaseHTTPRequest alloc] initWithURL:verifyURL];
	[request setProductIdentifier:transaction.payment.productIdentifier];
	[request setRequestMethod: @"POST"];
	[request setDelegate:self];
	[request setDidFinishSelector:@selector(didFinishVerify:)];
	//[request setShouldRedirect: NO];
	[request addRequestHeader: @"Content-Type" value: @"application/json"];
	
	//NSString *recepit = [[NSString alloc] initWithData:transaction.transactionReceipt encoding:NSUTF8StringEncoding];
	NSString *recepit = [GTMBase64 stringByEncodingData:transaction.transactionReceipt];
	//NSString * encodedString = (NSString *)CFURLCreateStringByAddingPercentEscapes(
//																				   NULL,
//																				   (CFStringRef)recepit,
//																				   NULL,
//																				   (CFStringRef)@"!*'();:@&=+$,/?%#[]",
//																				   kCFStringEncodingUTF8 );
//	NSString * encodedString =  [recepit stringByReplacingOccurrencesOfString:@"+" withString:@"%2B"];  
	NSDictionary* data = [NSDictionary dictionaryWithObjectsAndKeys:recepit, @"receipt-data", nil];
	SBJsonWriter *writer = [SBJsonWriter new];
	[request appendPostData: [[writer stringWithObject:data] dataUsingEncoding: NSUTF8StringEncoding]];
	[writer release];
	[_networkQueue addOperation: request];
	[_networkQueue go];
}

-(void)didFinishVerify:(ECPurchaseHTTPRequest *)request
{
	NSString *response = [request responseString];
	SBJsonParser *parser = [SBJsonParser new];
	NSDictionary* jsonData = [parser objectWithString: response];
	[parser release];
	NSString *status = [jsonData objectForKey: @"status"];
	if ([status intValue] == 0) {
		NSDictionary *receipt = [jsonData objectForKey: @"receipt"];
		NSString *productIdentifier = [receipt objectForKey: @"product_id"];
		[_transactionDelegate didCompleteTransactionAndVerifySucceed:productIdentifier];
	}
	else {
		NSString *exception = [jsonData objectForKey: @"exception"];
		[_transactionDelegate didCompleteTransactionAndVerifyFailed:request.productIdentifier withError:exception];
	}

}
+(void)removeLocalTransaction:(NSString*)transaction_id
{
    if (!transaction_id||transaction_id.length<=0) {
        return;
    }
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    NSDictionary* user_dic = [userdefault objectForKey:@"yidaoliu_iap_transaction"];
    NSMutableDictionary* dic = nil;
    if (!user_dic) {
        return;
    }else{
        dic = [[[NSMutableDictionary alloc]initWithDictionary:user_dic]autorelease];
    }
    NSMutableDictionary* orderDic = [dic objectForKey:transaction_id];
    if (orderDic) {
        [dic removeObjectForKey:transaction_id];
        [userdefault setObject:dic forKey:@"yidaoliu_iap_transaction"];
        [userdefault synchronize];
    }
}
-(void)verifyReceiptWithServer:(SKPaymentTransaction *)transaction
{
	NSString *recepit = [GTMBase64 stringByEncodingData:transaction.transactionReceipt];
    
    //NSString* orderID = [[transaction payment] applicationUsername];
    //NSLog(@"applicationUsername:%@",orderID);
    NSString* transactionIdentifier = transaction.transactionIdentifier;
    
    NSUserDefaults* userdefault = [NSUserDefaults standardUserDefaults];
    NSDictionary* user_dic = [userdefault objectForKey:@"yidaoliu_iap_transaction"];
    NSMutableDictionary* dic = nil;
    if (!user_dic) {
        dic = [NSMutableDictionary dictionaryWithCapacity:1];
    }else{
        dic = [[[NSMutableDictionary alloc]initWithDictionary:user_dic]autorelease];
    }
    NSDictionary* user_orderDic = [dic objectForKey:transactionIdentifier];
    NSMutableDictionary* orderDic = nil;
    if (!user_orderDic) {
        orderDic = [NSMutableDictionary dictionaryWithCapacity:4];
    }else{
        orderDic = [[[NSMutableDictionary alloc]initWithDictionary:user_orderDic]autorelease];
    }
    NSString* orderID = [orderDic objectForKey:@"order_id"];
    if (!orderID||orderID.length<=0) {
        orderID = _orderID;//[_productDelegate getNewOrderID];
        if (!orderID||[orderID isEqual:@""]) {
            orderID = [_productDelegate getNewOrderID];
            if (!orderID||[orderID isEqual:@""]) return;
        }
        [orderDic setObject:orderID forKey:@"order_id"];
        [orderDic setObject:recepit forKey:@"recepit"];
        [orderDic setObject:transactionIdentifier forKey:@"transactionIdentifier"];
        [orderDic setObject:transaction.payment.productIdentifier forKey:@"productIdentifier"];
        [dic setObject:orderDic forKey:transactionIdentifier];
        [userdefault setObject:dic forKey:@"yidaoliu_iap_transaction"];
        [userdefault synchronize];
    }
   
	
    [self sendReceiptToServer:orderID andTransactionIdentifier:transactionIdentifier andRecepit:recepit andProductIdentifier:transaction.payment.productIdentifier];
    
    [CHANNELCALLBACK showAlert:@"正在验证本次交易，请勿关闭游戏"];
    //[CHANNELCALLBACK endPay];
//    _verifyAlert = [[UIAlertView alloc]initWithTitle:nil message:@"正在验证交易，请不要关闭游戏" delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
//    [_verifyAlert show];
//    [_verifyAlert release];
}
-(void)sendReceiptToServer:(NSString *)orderID andTransactionIdentifier:(NSString *)transactionIdentifier andRecepit:(NSString *)recepit andProductIdentifier:(NSString *)productIdentifier
{
    if(!orderID||!recepit||!transactionIdentifier||!productIdentifier){
        NSLog(@"sendReceiptToServer Error :invalid args");
        return;
    }
    NSDictionary* data = [NSDictionary dictionaryWithObjectsAndKeys:orderID,@"orderid",transactionIdentifier,@"transaction_id",recepit, @"receipt", nil];
    //NSDictionary* data = [NSDictionary dictionaryWithObjectsAndKeys:recepit, @"receipt-data", nil];
    
    _networkQueue = [ASINetworkQueue queue];
	[_networkQueue retain];
    NSURL *verifyURL = [NSURL URLWithString:[_productDelegate getRechargeVerifyURL]];
	ECPurchaseHTTPRequest *request = [[ECPurchaseHTTPRequest alloc] initWithURL:verifyURL];
	[request setProductIdentifier:productIdentifier/*transaction.payment.productIdentifier*/];
	[request setRequestMethod: @"POST"];
	[request setDelegate:self];
	[request setDidFinishSelector:@selector(didFinishVerifyWithServer:)];
    [request setDidFailSelector:@selector(didFailedVerifyWithServer:)];
	//[request setShouldRedirect: NO];
	[request addRequestHeader: @"Content-Type" value: @"application/json"];
    
	SBJsonWriter *writer = [SBJsonWriter new];
	[request appendPostData: [[writer stringWithObject:data] dataUsingEncoding: NSUTF8StringEncoding]];
    //[request buildPostBody];
    NSLog(@"data:%@",[writer stringWithObject:data]);
	[writer release];
	[_networkQueue addOperation: request];
	[_networkQueue go];
    
    //[CHANNELCALLBACK endPay];
}
-(void)didFinishVerifyWithServer:(ECPurchaseHTTPRequest *)request
{
    [CHANNELCALLBACK hideAlert];
    [CHANNELCALLBACK endPay];
    
	NSString *response = [request responseString];
    NSLog(@"didFinishVerifyWithServer：%@",response);
    
    SBJsonParser *parser = [SBJsonParser new];
	NSDictionary* jsonData = [parser objectWithString: response];
	[parser release];
	NSString *status = [jsonData objectForKey: @"errorcode"];
	if (status&&[status intValue] == 0) {
		NSLog(@"－－－－－－－支付成功－－－－－－－");
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"成功" message:@"兑换商品成功"
                                                           delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [alerView show];
        [alerView release];
        NSString *transaction_id = [jsonData objectForKey: @"transaction_id"];
        [ECPurchase removeLocalTransaction:transaction_id];
	}
    else if (status&&[status intValue] == -200){
        NSLog(@"－－－－－－－已经兑换过－－－－－－－");
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"提示" message:@"该订单已经兑换成功"
                                                           delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [alerView show];
        [alerView release];
        NSString *transaction_id = [jsonData objectForKey: @"transaction_id"];
        [ECPurchase removeLocalTransaction:transaction_id];
    }
    else if (status&&[status intValue] == -201){
        NSLog(@"－－－－－－－无效订单－－－－－－－");
        NSString *transaction_id = [jsonData objectForKey: @"transaction_id"];
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"出错了" message:[NSString stringWithFormat:@"无效的订单:%@",transaction_id]
                                                           delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [alerView show];
        [alerView release];
        [ECPurchase removeLocalTransaction:transaction_id];
    }
	else {
		NSLog(@"－－－－－－－支付失败－－－－－－－");
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"出错了" message:[NSString stringWithFormat: @"兑换商品失败:%@",status]
                                                           delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
        [alerView show];
        [alerView release];
        
	}
}
-(void)didFailedVerifyWithServer:(ECPurchaseHTTPRequest *)request
{
    NSLog(@"%s,timeout",__FUNCTION__);
    //[CHANNELCALLBACK hideAlert];
    //[CHANNELCALLBACK endPay];
    NSString* productid = request.productIdentifier;
    ECPurchaseHTTPRequest * newRequest = [request copy];
    [newRequest setProductIdentifier:productid];
    //NSLog(@"%s,%@,%@,%@",__FUNCTION__,[newRequest url],newRequest.productIdentifier,request.productIdentifier);
    [_networkQueue addOperation: newRequest];
    [_networkQueue go];
    [newRequest release];
    
    //_verifyAlert
//    UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"出错了" message:@"交易验证失败！" delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
//    [alert show];
//    [alert release];
}


//弹出错误信息
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{
    [_transactionDelegate request:request didFailWithError:error];
}
 
#pragma mark -
#pragma mark Get Property From ECStoreObserver
-(NSMutableArray *)getCompleteTrans{
	return _storeObserver.completeTrans;
}

-(NSMutableArray *)getRestoreTrans{
	return _storeObserver.restoreTrans;
}

-(NSMutableArray *)getFailedTrans{
	return _storeObserver.failedTrans;
}

-(void)dealloc
{
	RELEASE_SAFELY(_networkQueue);
	RELEASE_SAFELY(_storeObserver);
	[super dealloc];
}

@end