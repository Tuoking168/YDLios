//
//  OC2CPP.m
//  longcheng
//
//  Created by ceapon on 13-5-22.
//
//

#import "OC2CPP.h"

@implementation OC2CPP

static OC2CPP *sharedInstance= nil;

+(OC2CPP *) sharedInstance
{
    if(!sharedInstance)
    {
        sharedInstance = [[self alloc] init];
    }
    return sharedInstance;
}
+(id)allocWithZone:(NSZone *) zone
{
    @synchronized(self)
    {
        if(sharedInstance == nil)
        {
            sharedInstance = [super allocWithZone:zone];
            return sharedInstance;
        }
    }
    return sharedInstance;
}
@end
