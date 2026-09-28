#ifndef __HeroModule_h__
#define __HeroModule_h__


#include <string>

namespace CPModuleName
{
	static const std::string HERO = "hero";
}

namespace CPHeroData
{
	// base data
	static const std::string PID = "pid";
	static const std::string LEVEL = "level";
	static const std::string JOB = "job";
	static const std::string GENDER = "gender";

	// property prefix
	static const std::string PROP_ = "prop_";

	// buff list
	static const std::string BUFF_LIST = "buff_list";

	static const std::string DURATION = "duration";
	static const std::string STARTTIME = "starttime";

	// global cd
	static const std::string GLOBAL_CD = "global_cd";

	// common cd list
	static const std::string COMMON_CD_LIST = "common_cd_list";

	static const std::string COMMON_CD = "common_cd";
	static const std::string COMMON_CD_EX = "common_cd_ex";

	// skill data list
	static const std::string SKILL_LIST = "skill_list";

	static const std::string SKILL_EXP = "skill_exp";
	static const std::string SKILL_CD = "skill_cd";
	
	// reward time list
	static const std::string REWARD_TIME_LIST = "reward_time_list";

	static const std::string REWARD_TIME = "reward_time";
	static const std::string REWARD_TIME_EX_DATA_X = "reward_time_ex_data_x";
	static const std::string REWARD_TIME_EX_DATA_Y = "reward_time_ex_data_y";
	static const std::string REWARD_TIME_EX_DATA_Z = "reward_time_ex_data_z";

}

#endif //__HeroModule_h__