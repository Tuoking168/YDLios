#include "MsgMaster.h"
#include "TeamDefinition.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/teamdata/TeamData.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"


void MsgMaster::HandleMessageTeamInviteResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamInviteRespose, pMsg);
	CPEventHelper::msgResponse("HandleMessageTeamInviteResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageTeamJoinResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamJoinRespose, pMsg);
	CPEventHelper::msgResponse("HandleMessageTeamJoinResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageTeamQuitResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamQuitRespose, pMsg);
	CPEventHelper::msgResponse("HandleMessageTeamQuitResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageTeamMakeOperationReply( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamMakeOprationReply, pMsg);
	CPEventHelper::msgNotify("HandleMessageTeamMakeOperationReply", "", msg->opid, msg->result, 0, 0);
}

void MsgMaster::HandleMessageTeamMakeDecisionResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamMakeDecisionResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageTeamMakeDecisionResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageTeamInfoNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamInfoNotify, pMsg);

	int opcode = 0;
	if (!TeamData::mTeamMembers.empty() &&
		msg->teammates.empty())
	{
		opcode = Opcode::team_exit;
	}

	TeamData::mTeamMembers.clear();
	for(int i = 0; i < msg->teammates.size(); i++)	
	{
		TeamData::TeamMember member;
		member.pid = msg->teammates[i].pid;
		member.name = msg->teammates[i].name;
		member.state = msg->teammates[i].playerstate;
		member.teamleader = msg->teammates[i].teamleader;
		TeamData::mTeamMembers.push_back(member);
	}
	CPEventHelper::msgNotify("HandleMessageTeamInfoNotify", "", opcode, 0, 0, 0);
}

 void MsgMaster::HandleMessageTeamInfoRmvNotify( IMsg *pMsg )
 {
	CP_TEST_NULL_MSG(MsgTeamInfoRmvNotify, pMsg);

	// check remove one team member according to its pid
	std::string name;
	for(int i=0; i<TeamData::mTeamMembers.size(); i++)	
	{
		if(msg->pid == TeamData::mTeamMembers[i].pid)
		{
			name = TeamData::mTeamMembers[i].name;
			TeamData::mTeamMembers.erase(TeamData::mTeamMembers.begin()+i);
			break;
		}
	}
	CPEventHelper::msgNotify("HandleMessageTeamInfoRmvNotify", "", Opcode::team_del_member, name, msg->pid, 0);
 }
 
 void MsgMaster::HandleMessageTeamInfoUpdNotify( IMsg *pMsg )
 {
	CP_TEST_NULL_MSG(MsgTeamInfoUpdNotify, pMsg);
	
	bool isAdd = true;
	for(int i=0; i<TeamData::mTeamMembers.size(); i++)	
	{
		TeamData::TeamMember &member = TeamData::mTeamMembers[i];
		if(msg->mate.pid == TeamData::mTeamMembers[i].pid)
		{
			member.name = msg->mate.name;
			member.state = msg->mate.playerstate;
			member.teamleader = msg->mate.teamleader;
			isAdd = false;
		}
		else if (msg->mate.teamleader != 0)
		{
			member.teamleader = 0;
		}
	}

	int opcode = 0;
	if (isAdd)
	{
		TeamData::TeamMember member;
		member.pid = msg->mate.pid;
		member.name = msg->mate.name;
		member.state = msg->mate.playerstate;
		member.teamleader = msg->mate.teamleader;
		TeamData::mTeamMembers.push_back(member);
		opcode = Opcode::team_add_member;
	}
	else if (msg->mate.teamleader != 0)
	{
		opcode = Opcode::team_set_leader;
	}

	CPEventHelper::msgNotify("HandleMessageTeamInfoUpdNotify", "", opcode, msg->mate.name, msg->mate.pid, 0);
 }

void MsgMaster::HandleMessageTeamMakeOperation( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamMakeOpration, pMsg);

	TeamData::mTeamOperation.opid = msg->opid;
	TeamData::mTeamOperation.name = msg->name;
	TeamData::mTeamOperation.pid = msg->pid;
	TeamData::mTeamOperation.type = msg->type;
	///TODO: dispatch event to show team flag 
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TEAM_OPERATION);
}

void MsgMaster::HandleMessageTeamKickPlayerResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamKickPlayerResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageTeamKickPlayerResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageTeamSetLeaderResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgTeamSetLeaderResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageTeamSetLeaderResponse", "", msg->errcode);
}

