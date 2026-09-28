#include "MsgMaster.h"
#include "MsgHandler.h"
#include "cocos2d.h"

MsgMaster::MsgMaster()
{
	InitMsgHandler();
}

void MsgMaster::updateMessage(IMsg* pMsg)
{
	uint32 id = pMsg->getMsgCate() << 16 | pMsg->getMsgID();
	MsgHandlerMap::iterator iter = msgTable.find(id);
	if (iter != msgTable.end())
	{
		cocos2d::CCLog("***Handle: %s", pMsg->getMsgName());
		(iter->second.handler)(pMsg);

	}
	else
	{
		cocos2d::CCLog("Failed to handler Msg  message: %s!", pMsg->getMsgName());
	}

}
