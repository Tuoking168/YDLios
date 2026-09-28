#ifndef __GROUP_DATA_H__
#define __GROUP_DATA_H__

#include <vector>
#include <string>

//global team data for main role

class TeamData
{
public:
	struct TeamMember
	{
		int pid;
		std::string name;
		int state;
		int teamleader;	
		TeamMember():pid(0),state(100),teamleader(0){}
	};
	struct TeamOperation
	{
		int pid;
		int type;
		int opid;
		std::string name;
	};
	static std::vector<TeamMember> mTeamMembers;
	static TeamOperation mTeamOperation;
};

#endif//__GROUP_DATA_H__