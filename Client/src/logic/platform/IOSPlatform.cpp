#include "IOSPlatform.h"

#include "ItemDefinition.h"
#include "MsgGMaster.h"
#include "VIPModule.h"

#include "scene/LoginHelper.h"

#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"

#include "event/CPEventHelper.h"

#include "network/HandleMessage.h"

#include "ext/../../ios/channel/common/ChannelHelper.h"

#include "cocos-ext.h"

IOSPlatform::IOSPlatform()
{

}

IOSPlatform::~IOSPlatform()
{

}

void IOSPlatform::login()
{
    
    CHANNELHELPER->showLogin();
	//IOSHELPER->showLogin();
}

void IOSPlatform::pay( int yuan )
{
    CHANNELHELPER->pay("", (float)yuan, "", yuan*10);
    return;
    
    
    const char *postdata = "";
    unsigned int len = strlen(postdata);
    const char *httpurl = "http://admin.yidaoliu.cn/fire-ams/payment/callback/kuaiyongcreate";
    
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(httpurl);
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(CHANNELHELPER, httpresponse_selector(ChannelHelper::orderCallBack));
    request->setRequestData(postdata, len);
    //request->setHeaders(pHeaders);
    
    request->setTag("postRequest");
    CCHttpClient::getInstance()->send(request);
    request->release();
    

//	const int goldPerYuan = LayoutData::getInt(CPModuleName::VIP, "goldPerYuan");
//    
//    MsgRechargeRequest *msg = new MsgRechargeRequest;
//    msg->pid = HeroData::getPID();
//    msg->cnt = goldPerYuan * yuan;
//    msg->sid = ItemSid_Gold;
//    HandleMessage::sendMessage(msg);
}

void IOSPlatform::operate( int opID )
{
    if(opID == PlatformOpID::lianxiGM)
    {
        CHANNELHELPER->connectGM();
    }
    
    CPEventHelper::setEventIntData(CPEventName::LGC_PLATFORM, CPEventData::VALUE_1, opID);
    CPEventHelper::dispatcher(CPEventName::LGC_PLATFORM, "Win32Platform::operate", "");
}

std::string IOSPlatform::convert( const std::string &data )
{
	return data;
}

void IOSPlatform::selectGameSever(int selectedserver)
{
	//should do something

}