#include "MsgMaster.h"
#include "ModuleData.h"
#include "LoginModule.h"
#include "PlatformModule.h"
#include "ErrorDefinition.h"
#include "CCCommon.h"

#include "logic/platform/IPlatform.h"

#include "event/CPEventHelper.h"

using namespace cocos2d;

typedef std::vector< SvrInfo > SvrInfoList;


static void setServerList( const SvrInfoList &serverList )
{
	SubModuleData::init(CPModuleName::LOGIN, CPLoginData::SERVER_LIST);
	int curCnt = 0;
//	SubModuleData::clearAll();
	SubModuleData::getSize(curCnt);
	int predataCnt = curCnt;
	int i = 0;
	for (int k = 0; k < (int)serverList.size(); k++)
	{
		bool bdulsever = false;
		for (int j=0; j<predataCnt; j++)
		{
			int serverid = -1;
			if (SubModuleData::getInt(j, CPLoginData::SERVER_ID, serverid))
			{
				if (serverid == serverList[i].SvrID)
				{
					bdulsever = true;
					break;
				}
			}
		}
		if (bdulsever)
			break;
		SubModuleData::setInt(curCnt + i, CPLoginData::SERVER_ID, serverList[i].SvrID);
		SubModuleData::setString(curCnt + i, CPLoginData::SERVER_NAME, serverList[i].SvrName);
		SubModuleData::setString(curCnt + i, CPLoginData::SERVER_IP, serverList[i].SvrIP);
		SubModuleData::setInt(curCnt + i, CPLoginData::SERVER_PORT, serverList[i].SvrPort);
		SubModuleData::setInt(curCnt + i, CPLoginData::SERVER_STATE, serverList[i].SvrState);
		SubModuleData::setInt(curCnt + i, CPLoginData::SERVER_REGION, serverList[i].Region);
		SubModuleData::setInt(curCnt + i, CPLoginData::SERVER_PLAYER_CNT, serverList[i].m_PlayerCount);
		i++;
	}
}

static void setServerList(const SvrInfo& server)
{
	SvrInfoList list;
	list.push_back(server);
	setServerList(list);
}

void MsgMaster::HandleMessageAuthServerListNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAuthServerListNotify, pMsg);

	setServerList(msg->SvrList);
	CPEventHelper::msgNotify("HandleMessageAuthServerListNotify", "");
}

void MsgMaster::HandleMessageAuthResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgAuthResponse, pMsg);

	if(msg->errcode == Error::Success)
	{
		ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::AID, msg->aid);
		setServerList(msg->SvrList);
 	}
	CPEventHelper::msgResponse("HandleMessageLoginResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageAuthResponseEx(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgAuthResponseEx, pMsg);

	if(msg->errcode == Error::Success)
	{
		ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::AID, msg->aid);
		setServerList(msg->server);
		CPPlatformMnger.setIntData(CPPlatformData::LOGIN_TOKEN, msg->token);
 	}
	CPEventHelper::msgResponse("HandleMessageLoginResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageRegisterResponse( IMsg *pMsg )
{
	// @deprecated
}

void MsgMaster::HandleMessageAuthCheckVersionStrongResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAuthCheckVersionStrongResponse, pMsg);
    
	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SERVER_GAME_VERSION, msg->gameVersion);
	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SERVER_DATA_VERSION, msg->dataVersion);
	ModuleData::setString(CPModuleName::LOGIN, CPLoginData::DOWNLOAD_URL, msg->downloadURL);
	ModuleData::setString(CPModuleName::LOGIN, CPLoginData::ANNOUNCEMENT, msg->announcement);
	CPEventHelper::msgResponse("HandleMessageAuthCheckVersionStrongResponse", "", 0);
}

void MsgMaster::HandleMessageAuthMiniStrongUpdateResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAuthMiniStrongUpdateResponse, pMsg);
	ModuleData::setString(CPModuleName::LOGIN, CPLoginData::DOWNLOAD_URL, msg->downloadURL);
	CPEventHelper::msgResponse("HandleMessageAuthMiniStrongResponse", "", 0);
}

void MsgMaster::HandleMessageAuthCheckVersionStrongUpdateResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAuthCheckVersionStrongUpdateResponse, pMsg);

	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SERVER_GAME_VERSION, msg->gameVersion);
	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SERVER_SVN_VERSION, msg->svnVersion);
	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SERVER_DATA_VERSION, msg->dataVersion);
	ModuleData::setString(CPModuleName::LOGIN, CPLoginData::DOWNLOAD_URL, msg->downloadURL);
	ModuleData::setString(CPModuleName::LOGIN, CPLoginData::ANNOUNCEMENT, msg->announcement);
	CPEventHelper::msgNotify("HandleMessageAuthCheckVersionStrongUpdateResponse", "", 0, msg->downloadURL, msg->strong, msg->type);
}

void MsgMaster::HandleMessageAccessTokenResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAccessTokenResponse, pMsg);

	CPUnused(msg->errcode);
	CPPlatformMnger.setStringData(CPPlatformData::UIN, msg->userId);
	CPPlatformMnger.setStringData(CPPlatformData::USER_NAME, msg->userName);
	CPPlatformMnger.setStringData(CPPlatformData::TOKEN, msg->accessToken);
}

void MsgMaster::HandleMessageAuthCheckVersionOptionalResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAuthCheckVersionOptionalResponse, pMsg);
	ModuleData::setInt(CPModuleName::LOGIN, CPLoginData::SERVER_SVN_VERSION, msg->svnVersion);
	ModuleData::setString(CPModuleName::LOGIN, CPLoginData::DOWNLOAD_URL, msg->downloadURL);
	CPEventHelper::msgResponse("HandleMessageAuthCheckVersionOptionalResponse", "", 0);
}

void MsgMaster::HandleMessageAuthServerListNotifyEnd( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgAuthServerListNotifyEnd, pMsg);
	setServerList(msg->SvrList);
	CPEventHelper::msgResponse("HandleMessageAuthServerListNotifyEnd", "", 0);
}
