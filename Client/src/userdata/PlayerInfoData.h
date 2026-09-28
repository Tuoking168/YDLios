#ifndef __PLAYER_INFO_DATA_H__
#define __PLAYER_INFO_DATA_H__

#include <string>

class PlayerInfoData
{
public:
	struct PlayerInfo
	{
		int eid;
		int pid;
		std::string name;
		int maxhp;
		int hp;
		int maxmp;
		int mp;
		int lvl;
		int staticid;
		int gender;
	};
	static PlayerInfo _target_player_info;
};


#endif//__PLAYER_INFO_DATA_H__