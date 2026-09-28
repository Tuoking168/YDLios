#ifndef __ActivityModule_h__
#define __ActivityModule_h__

#include <string>

namespace CPModuleName
{
	static const std::string ACTIVITY = "activity";
}

namespace CPActivityData
{
	// common data
	static const std::string STATE_ = "state_";
	static const std::string UNSTART_ID = "unstart_id";

	static const std::string NOT_FINISH_CNT_ = "not_finish_cnt_";

	static const std::string WORLD_TIME = "world_time";

	static const std::string WORLD_BEGIN_TIME = "world_begin_time";

	static const std::string HIDE_LIST = "hide_list";
	static const std::string HIDE_STATE = "hide_state";

	// world data
	static const std::string WORLD_INT_PROP_ = "world_int_prop_";
	static const std::string WORLD_STRING_PROP_ = "world_string_prop_";

	static const std::string WORLD_PROP = "world_prop";
	static const std::string WORLD_PROP_VERSION = "world_prop_version";

	// ex data list
	static const std::string EX_DATA_LIST = "ex_data_list";
	static const std::string EX_DATA_X = "ex_data_x";
	static const std::string EX_DATA_Y = "ex_data_y";
	static const std::string EX_DATA_Z = "ex_data_z";

	// mo bai
	static const std::string MO_BAI_ = "mo_bai_";

	// cai shen chuang guan
	static const std::string CAI_SHEN_CHUANG_GUAN_ = "cai_shen_chuang_guan_";

	// mei nv hu song
	static const std::string MEI_NV_HU_SONG_ = "mei_nv_hu_song_";

	//qi fu shu
	static const std::string QI_FU_SHU_ = "qi_fu_shu_";

	//zhu mo jie zhen
	static const std::string ZHU_MO_JIE_ZHEN_ = "zhu_mo_jie_zhen_";

	// arena
	static const std::string COMPETITOR_LIST = "competitor_list";

	static const std::string COMPETITOR_PID = "competitor_pid";
	static const std::string COMPETITOR_LEVEL = "competitor_level";
	static const std::string COMPETITOR_NAME = "competitor_name";
	static const std::string COMPETITOR_REBORN = "competitor_reborn";
	static const std::string COMPETITOR_JOB = "competitor_job";
	static const std::string COMPETITOR_GENDER = "competitor_gender";
	static const std::string COMPETITOR_CLOTH = "competitor_cloth";
	static const std::string COMPETITOR_WEAPON= "competitor_weapon";
	static const std::string COMPETITOR_WINGS = "competitor_wings";
	static const std::string COMPETITOR_GUILD_NAME = "competitor_guild_name";

	static const std::string FIGHT_BEGIN_LIST = "fight_begin_list";

	static const std::string FIGHT_BEGIN_ID = "fight_begin_id";
	static const std::string FIGHT_BEGIN_LEVEL = "fight_begin_level";
	static const std::string FIGHT_BEGIN_NAME = "fight_begin_name";
	static const std::string FIGHT_BEGIN_REBORN = "fight_begin_reborn";
	static const std::string FIGHT_BEGIN_JOB = "fight_begin_job";
	static const std::string FIGHT_BEGIN_GENDER = "fight_begin_gender";
	static const std::string FIGHT_BEGIN_CLOTH = "fight_begin_cloth";
	static const std::string FIGHT_BEGIN_WEAPON = "fight_begin_weapon";
	static const std::string FIGHT_BEGIN_WINGS = "fight_begin_wings";
	static const std::string FIGHT_BEGIN_MAX_HP = "fight_begin_max_hp";

	static const std::string FIGHT_LIST = "fight_list";

	static const std::string FIGHT_ID = "fight_id";
	static const std::string FIGHT_DAMAGE = "fight_damage";

	static const std::string FIGHT_WINNER = "fight_winner";

	static const std::string FIGHT_RECORD_LIST = "fight_record_list";

	static const std::string FIGHT_RECORD_NAME = "fight_record_name";
	static const std::string FIGHT_RECORD_CHALLENGER_FLAG = "fight_record_challenger_flag";
	static const std::string FIGHT_RECORD_WIN_FLAG = "fight_record_win_flag";

	static const std::string COMPETITOR_RANK_LIST = "competitor_rank_list";

	static const std::string COMPETITOR_RANK_RANK = "competitor_rank_rank";
	static const std::string COMPETITOR_RANK_PID = "competitor_rank_pid";
	static const std::string COMPETITOR_RANK_NAME = "competitor_rank_name";
	static const std::string COMPETITOR_RANK_JOB = "competitor_rank_job";
	static const std::string COMPETITOR_RANK_FIGHT_POINT = "competitor_rank_fight_point";

	// world boss and map boss
	static const std::string WORLD_BOSS_LIST = "world_boss_list";

	static const std::string WORLD_BOSS_SID = "world_boss_sid";
	static const std::string WORLD_BOSS_EXP = "world_boss_exp";
	static const std::string WORLD_BOSS_STATE = "world_boss_state";
	static const std::string WORLD_BOSS_KILLER_PID = "world_boss_killer_pid";
	static const std::string WORLD_BOSS_KILLER_NAME = "world_boss_killer_name";

	// instance data
	static const std::string INSTANCE_LIST = "instance_list";

	static const std::string INSTANCE_ENTER_COUNT = "instance_enter_count";
	static const std::string INSTANCE_ENTER_ALLCOUNT = "instance_enter_allcount";

	// treasure hunt
	static const std::string TREASURE_MY_RECORD_LIST = "treasure_my_record_list";
	static const std::string TREASURE_ALL_RECORD_LIST = "treasure_all_record_list";

	static const std::string TREASURE_RECORD_NAME = "treasure_record_name";
	static const std::string TREASURE_RECORD_SID = "treasure_record_sid";
	static const std::string TREASURE_RECORD_STRONG = "treasure_record_strong";
	static const std::string TREASURE_RECORD_REBORN = "treasure_record_reborn";

	//¹¥³ÇÕ½
	static const std::string GONG_CHENG_ZHAN = "gong_cheng_zhan";
	static const std::string GCZ_MASTER_GUILD_NAME = "gcz_master_guild_name";
	static const std::string GCZ_OCCUPY_REWARD_GAINER = "gcz_occupy_reward_gainer";

	// single recharge
	static const std::string SINGLE_RECHARGE_REWARD_ = "single_recharge_reward_";
}
#endif //__ActivityModule_h__