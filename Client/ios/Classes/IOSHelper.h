//
//  IOSHelper.h
//  Fire
//
//  Created by ceapon on 14-2-21.
//  Copyright (c) 2014年 ceapon. All rights reserved.
//

#ifndef __Fire__IOSHelper__
#define __Fire__IOSHelper__

#include <iostream>

class IOSHelper
{
public:
    enum SDK
    {
        SDK_None = 0,
        SDK_PP = 1,
        SDK_91 = 2,
        SDK_TB = 3,
    };
private:
    IOSHelper();
    virtual ~IOSHelper();
    static IOSHelper* instance;
    int m_Platform;
public:
    static void messageBox(const char* str);
public: //common
    static IOSHelper* GetInstance();
    
    int getPlatform();
    void setPlatform(int);
    
    void initSDK();
    void showLogin();
    //void showRecharge();
public: //pp
    //void alixPayResult();
    void ppShowCenter();
    void buy(int tag);
    void exchangeGoods(double price);
    
};

#define IOSHELPER IOSHelper::GetInstance()

#endif /* defined(__Fire__IOSHelper__) */
