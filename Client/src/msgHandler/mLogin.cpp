#include "MsgMaster.h"
#include "LoginModule.h"
#include "ModuleData.h"
#include "ErrorDefinition.h"

#include "scene/SceneManager.h"

#include "event/CPEventHelper.h"


typedef std::vector< PlayerInfo > PlayerInfoList;
static void setPlayerList( const PlayerInfoList &playerList )
{
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
	SubModuleData::clearAll();
	int pid = 0;
	for (int i = 0; i < (int)playerList.size(); i++)
	{
		pid = playerList[i].pid;
		SubModuleData::setInt(pid, CPLoginData::PLAYER_ID, pid);
		SubModuleData::setString(pid, CPLoginData::PLAYER_NAME, playerList[i].PlayerName);
		SubModuleData::setInt(pid, CPLoginData::PLAYER_GENDER, playerList[i].Gender);
		SubModuleData::setInt(pid, CPLoginData::PLAYER_JOB, playerList[i].mclass);
		SubModuleData::setInt(pid, CPLoginData::PLAYER_LEVEL, playerList[i].level);
		SubModuleData::setInt(pid, CPLoginData::PLAYER_CLOTH, playerList[i].cloth);
		SubModuleData::setInt(pid, CPLoginData::PLAYER_WEAPON, playerList[i].weapon);
	}
}

void MsgMaster::HandleMessageEnterServerResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgEnterServerResponse, pMsg);

	if(msg->errcode == Error::Success)
	{
		setPlayerList(msg->PlayerList);
	}
	CPEventHelper::msgResponse("HandleMessageEnterServerResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageRandomANameResponse(IMsg *pMsg)
{
	//
}

void MsgMaster::HandleMessageCreatePlayerResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgCreatePlayerResponse, pMsg);

	if (msg->errcode == Error::Success)
	{
		CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->pid);
	}

	CPEventHelper::msgResponse("MsgCreatePlayerResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageEnterGameResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgEnterGameResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageEnterGameResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageDeletePlayerResponse(IMsg *pMsg)
{	
	MsgDeletePlayerResponse* msg = dynamic_cast<MsgDeletePlayerResponse*>(pMsg);
	if (!msg) return;

	if (msg->errcode == Error::Success)
	{
		SubModuleData::init(CPModuleName::LOGIN, CPLoginData::PLAYER_LIST);
		SubModuleData::clearData(msg->pid);
	}
	CPEventHelper::msgResponse("HandleMessageDeletePlayerResponse", "", msg->errcode);
}

void MsgMaster::HandleMessagePlayerReconnectResponse(IMsg *pMsg)
{
	//
}

void MsgMaster::HandleMessageBeKicked(IMsg *pMsg)
{
	CPUnused(pMsg);
//	LOG_ERROR("I am be kicked!");
	SceneManager::switchToLogin();
	CPEventHelper::msgResponse("HandleMessageBeKicked", "", Error::You_have_be_kicked);
}

void MsgMaster::HandleMsgServerQueueNotify(IMsg *pMsg)
{
	MsgServerQueueNotify* msg = dynamic_cast<MsgServerQueueNotify*>(pMsg);
	if (!msg) return;

	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SEVERQUEUE, msg->queueposition);

	CPEventHelper::msgResponse("HandleMsgServerQueueNotify", "", Error::Success);
}
