#ifndef __ChatModule_h__
#define __ChatModule_h__


#include <string>

namespace CPModuleName
{
	static const std::string CHAT = "chat";
}

namespace CPChatData
{
	static const std::string LAST_CHAT_TYPE = "last_chat_type";
	static const std::string LAST_CHAT_ID = "last_chat_id";

	// chat record list
	static const std::string HORN_CHAT_LIST = "horn_chat_list";
	static const std::string NORM_CHAT_LIST = "norm_chat_list";

	static const std::string CHAT_TYPE = "chat_type";
	static const std::string PID = "pid";
	static const std::string PLAYER_NAME = "player_name";
	static const std::string GENDER = "gender";
	static const std::string VIP_LEVEL = "vip_level";
	static const std::string CHAT_TEXT = "chat_text";

	// chat partner
	static const std::string CHAT_PARTNER_PID = "chat_partner_pid";
	static const std::string CHAT_PARTNER_NAME = "chat_partner_name";

	// chat item data
	static const std::string CHAT_ITEM_PID = "chat_item_pid";
	static const std::string CHAT_ITEM_ID = "chat_item_id";

	static const std::string CHAT_ITEM_DATA_LIST = "chat_item_data_list";

	static const std::string CHAT_ITEM_DATA = "chat_item_data";

	// gm flag
	static const std::string CHAT_TO_GM = "chat_to_gm";
}

#endif //__ChatModule_h__