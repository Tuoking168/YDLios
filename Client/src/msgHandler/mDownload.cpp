#include "MsgMaster.h"

#include "event/CPEventHelper.h"

void MsgMaster::HandleMessageDownload( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgDownload, pMsg);

	CPEventHelper::setEventStringData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->key);
	CPEventHelper::msgResponse("HandleMessageDownload", "", 0);
}

void MsgMaster::HandleMessageDownloadProgress( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgDownloadProgress, pMsg);

	CPEventHelper::msgNotify("HandleMessageDownloadProgress", "", 0, msg->key, msg->percent * 100, 0);
}
