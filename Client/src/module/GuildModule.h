#ifndef __GuildModule_h__
#define __GuildModule_h__

#include <string>

namespace CPModuleName
{
	static const std::string GUILD = "guild";
}

namespace CPGuildData
{
	// guild list
	static const std::string GUILD_PAGE = "guild_page";
	static const std::string GUILD_MAXPAGE = "guild_maxpage";

	static const std::string GUILD_LIST = "guild_list";

	static const std::string GUILD_ID = "guild_id";
	static const std::string GUILD_RANK = "guild_rank";
	static const std::string GUILD_NAME = "guild_name";
	static const std::string GUILD_LEVEL = "guild_level";
	static const std::string GUILD_MASTERNAME = "guild_mastername";
	static const std::string GUILD_MASTERID = "guild_masterid";
	static const std::string GUILD_MEMBERCOUNT = "guild_membercount";
	static const std::string GUILD_MAXMEMBER = "guild_maxmember";
	static const std::string GUILD_STATE = "guild_state";

	static const std::string GUILD_CONTRIBUTION = "guild_contribution";
	static const std::string GUILD_MONEY = "guild_money";

	// member list
	static const std::string GUILD_MEMBER_PAGE = "guild_member_page";
	static const std::string GUILD_MEMBER_MAXPAGE = "guild_member_maxpage";

	static const std::string GUILD_ALL_MEMBER_LIST = "guild_all_member_list";
	static const std::string GUILD_MEMBER_LIST = "guild_member_list";

	static const std::string GUILD_MEMBER_PID = "guild_member_pid";
	static const std::string GUILD_MEMBER_NAME = "guild_member_name";
	static const std::string GUILD_MEMBER_LEVEL = "guild_member_level";
	static const std::string GUILD_MEMBER_RANK = "guild_member_rank";
	static const std::string GUILD_MEMBER_ARENARANK = "guild_member_arenarank";
	static const std::string GUILD_MEMBER_JOB = "guild_member_job";
	static const std::string GUILD_MEMBER_NICKNAME = "guild_member_nickname";
	static const std::string GUILD_MEMBER_CONTRIBUTION = "guild_member_contribution";
	static const std::string GUILD_MEMBER_TODAYCONTRIBUTION = "guild_member_todaycontribution";
	static const std::string GUILD_MEMBER_LASTONLINE = "guild_member_lastonline";

	//Application List
	static const std::string GUILD_APPLICATION_LIST = "guild_application_list";

	static const std::string GUILD_APPLICATION_PID = "guild_application_pid";
	static const std::string GUILD_APPLICATION_NAME = "guild_application_name";
	static const std::string GUILD_APPLICATION_LEVEL = "guild_application_level";

	//Nickname List
	static const std::string GUILD_NICKNAME_LIST = "guild_nickname_list";

	static const std::string GUILD_NICKNAME_JOB = "guild_nickname_job";
	static const std::string GUILD_NICKNAME_NAME = "guild_nickname_name";

	//UI
	static const std::string GUILD_NICKNAME_TIP_X = "guild_nickname_tip_x";
	static const std::string GUILD_NICKNAME_TIP_Y = "guild_nickname_tip_y";
	static const std::string GUILD_NICKNAME_SELECT = "guild_nickname_select";

	//GCZ
	static const std::string GCZ_ATTACK_GUILD_LIST = "gcz_attack_guild_list";
	static const std::string GCZ_LAST_ATTACK_GUILD_LIST = "gcz_last_attack_guild_list";

	// property prefix
	static const std::string GUILD_PROP_ = "guild_prop_";
	static const std::string GUILD_STRING_PROP_ = "guild_string_prop_";

	//guildBuilding TanXian
	static const std::string GUILD_BUILDING_TANXIAN_ITEM_LIST = "guild_building_tanxian_item_list";
	static const std::string GUILD_BUILDING_TANXIAN_ITEM = "guild_building_tanxian_item";
}
#endif //__GuildModule_h__