#include "TeamMsgSender.h"
#include "MsgTeam.h"
#include "network/HandleMessage.h"

void TeamMsgSender::Invite( int pid )
{
	MsgTeamInviteRequest* msg = new MsgTeamInviteRequest;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
}

void TeamMsgSender::Join( int pid )
{
	MsgTeamJoinRequest* msg = new MsgTeamJoinRequest;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
}

void TeamMsgSender::Quit()
{
	MsgTeamQuitRequest* msg = new MsgTeamQuitRequest;
	HandleMessage::sendMessage(msg);
}

void TeamMsgSender::MakeDecision( int opid, int decide)
{
	MsgTeamMakeDecisionRequest* msg = new MsgTeamMakeDecisionRequest;
	msg->opid = opid;
	msg->decide = decide;
	HandleMessage::sendMessage(msg);
}

void TeamMsgSender::kickPlayer( int pid )
{
	MsgTeamKickPlayerRequest *msg = new MsgTeamKickPlayerRequest;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
}

void TeamMsgSender::setLeader( int pid )
{
	MsgTeamSetLeaderRequest *msg = new MsgTeamSetLeaderRequest;
	msg->pid = pid;
	HandleMessage::sendMessage(msg);
}

