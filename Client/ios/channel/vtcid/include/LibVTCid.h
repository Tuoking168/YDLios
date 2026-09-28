//
//  VTCid.h
//  VTCid
//
//  Created by Duy Anh on 3/1/13.
//
//

#import <Foundation/Foundation.h>

#define  ENV_SANDBOX        1
#define  ENV_LIVE           0

#define LOGIN_MODE_FULL                            0 //Login full
#define LOGIN_MODE_ID                              1 //Chi co ID
#define LOGIN_MODE_FACEBOOK                        2 //Chi co Facebook
#define LOGIN_MODE_GOOGLEPLUS                      3 //Chi co Google plus

@protocol VTCIDDelegate;

@interface LibVTCid : NSObject
{
    BOOL _islogin;
}

@property (retain, nonatomic) UIViewController *libRootController;
@property (assign, nonatomic) id <VTCIDDelegate> delegate;
@property (copy, nonatomic) NSString *mPartnerID;
@property (copy, nonatomic) NSString *mPrivateKey;
@property (copy, nonatomic) NSString *mGoogleID;
@property (assign, nonatomic) int mEnv;
@property (assign, nonatomic) long long mAccountID;
@property (copy, nonatomic) NSString *mGameToken;
@property (assign, nonatomic) long long mAddr;

+ (LibVTCid *)shareInstance;
+ (LibVTCid *)initWithEnvironment:(int)env;

- (void)sendLoginMessage:(NSString *)account AccessToken:(NSString*)accesstoken AccountID:(long long)aid;
- (void)setAccountID:(long long)accountid;
- (void)setGameToken:(NSString *)gametoken;
- (void)setAddr:(long long)addr;
- (void)setGoogleID:(NSString *)googleid;
- (NSString *)getGoogleID;
- (long long)getAccountID;
- (NSString *)getGameToken;
- (long long)getAddr;
- (void)logout;
- (BOOL)isLogin;
- (int)getEnv;
- (NSString *)getPartnerID;
- (NSString *)getPrivateKey;
- (NSString *)getLinkDownload;  // Link download game
- (NSString *)getVersion;       // version app tương ứng với Link của hàm getLinkDownload()
- (void)showLoginView:(BOOL)hasBack LoginMode:(int)loginmode;
- (void)showTopupView;
- (void)showChangePassword;
- (void)closePaymentView;
- (void)closeTopupView;
- (void)showAssitView;

//OpenID
- (NSString *)getPartnerAccountId;
- (NSString *)getPartnerAccount;
- (NSString *)getPartnerToken;
- (NSString *)getPartnerEmail;
- (NSString *)getPartnerDisplayName;

@end

//VTCID Delegate
@protocol VTCIDDelegate <NSObject>
@optional
- (void)vtcidLogin:(NSString *)account AccessToken:(NSString*)accesstoken AccountID:(long long)aid;
- (void)topupClosed;
@end


