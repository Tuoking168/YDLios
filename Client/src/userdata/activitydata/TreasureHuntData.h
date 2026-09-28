#ifndef __TREASURE_HUNT_DATA_H__
#define __TREASURE_HUNT_DATA_H__

#include <vector>
#include <string>
#include "MsgActivity.h"

class TreasureHuntData
{
public:
	static	std::vector<Treasuredata> _s_treasure_hunt_list;
	static	int	_s_happiness_value;
	static	int	_s_happiness_grade;
	static	std::string	_s_my_hunt_log;
	static	std::string	_s_all_hunt_log;
};


#endif//__TREASURE_HUNT_DATA_H__