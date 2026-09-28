//
//  OC2CPP.h
//  longcheng
//
//  Created by ceapon on 13-5-22.
//
//

#import <Foundation/Foundation.h>
#import "Login.h"

@interface OC2CPP : NSObject

+(OC2CPP *) sharedInstance;

@property(nonatomic, assign)Login *objlogin;
@property(nonatomic, retain)NSDictionary *dic;
@end
