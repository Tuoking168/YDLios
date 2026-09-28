#include "Win32Platform.h"
#include "ItemDefinition.h"
#include "MsgGMaster.h"
#include "VIPModule.h"

#include "scene/LoginHelper.h"

#include "userdata/HeroData.h"
#include "userdata/LayoutData.h"

#include "event/CPEventHelper.h"

#include "network/HandleMessage.h"


Win32Platform::Win32Platform()
{

}

Win32Platform::~Win32Platform()
{

}

void Win32Platform::login()
{
	LoginHelper::switchView(LoginView::loginbody);//点击屏幕将进入哪个界面
}

void Win32Platform::pay( int yuan )
{
	const int goldPerYuan = LayoutData::getInt(CPModuleName::VIP, "goldPerYuan");

	MsgRechargeRequest *msg = new MsgRechargeRequest;
	msg->pid = HeroData::getPID();
	msg->cnt = goldPerYuan * yuan;
	msg->sid = ItemSid_Gold;
	HandleMessage::sendMessage(msg);
}

void Win32Platform::operate( int opID )
{
	CPEventHelper::setEventIntData(CPEventName::LGC_PLATFORM, CPEventData::VALUE_1, opID);
	CPEventHelper::dispatcher(CPEventName::LGC_PLATFORM, "Win32Platform::operate", "");
}

std::string Win32Platform::convert( const std::string &data )
{
	return data;
}

void Win32Platform::selectGameSever( int selectedserver )
{
	// should do nothing...
}