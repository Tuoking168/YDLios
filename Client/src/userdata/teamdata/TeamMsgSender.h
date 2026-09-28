#ifndef __TEAM_MESSGE_SENDER__
#define __TEAM_MESSGE_SENDER__


class TeamMsgSender
{
public:
	static void Invite(int pid);
	static void Join(int pid);
	static void Quit();
	static void MakeDecision(int opid, int decide);
	static void kickPlayer(int pid);
	static void setLeader(int pid);
};


#endif//__TEAM_MESSGE_SENDER__