#ifndef __LoginModule_h__
#define __LoginModule_h__

#include <string>

namespace CPModuleName
{
	static const std::string LOGIN = "login";
}

namespace CPLoginData
{
	static const std::string AID = "aid";
	static const std::string SEVERQUEUE = "svrqueue";
	static const std::string SERVER_GAME_VERSION = "server_game_version";
	static const std::string SERVER_DATA_VERSION = "server_data_version";
	static const std::string SERVER_SVN_VERSION = "server_svn_version";
	static const std::string DOWNLOAD_URL = "download_url";
	static const std::string ANNOUNCEMENT = "announcement";
	static const std::string PATCH_FILE_NAME = "patch_file_name";

	// server list
	static const std::string SERVER_LIST = "server_list";

	static const std::string SERVER_ID = "server_id";
	static const std::string SERVER_NAME = "server_name";
	static const std::string SERVER_IP = "server_ip";
	static const std::string SERVER_PORT = "server_port";
	static const std::string SERVER_STATE = "server_state";
	static const std::string SERVER_REGION = "server_region";
	static const std::string SERVER_PLAYER_CNT = "server_player_cnt";

	// player list
	static const std::string PLAYER_LIST = "player_list";

	static const std::string PLAYER_ID = "player_id";
	static const std::string PLAYER_NAME = "player_name";
	static const std::string PLAYER_GENDER = "player_gender";
	static const std::string PLAYER_JOB = "player_job";
	static const std::string PLAYER_LEVEL = "player_level";
	static const std::string PLAYER_CLOTH = "player_cloth";
	static const std::string PLAYER_WEAPON = "player_weapon";
}
#endif //__LoginModule_h__