#ifndef __UserDataModule_h__
#define __UserDataModule_h__

#include <string>
#include "logic/CPUpdateFunctor/CPUpdateFunctorDefination.h"

namespace CPModuleName
{
	static const std::string USER_DATA = "userData";
}

namespace CPUserData
{
	static const std::string DATA_VERSION = "data_version";
	static const std::string SVN_VERSION = "svn_version";

	static const std::string ACCOUNT = "account";
	static const std::string PASSWORD = "password";

	static const std::string SERVER_INDEX = "server_index";
	static const std::string REGION_INDEX = "region_index";
	static const std::string SERVER_ID = "server_id";

	static const std::string ROLE_INDEX = "player_index";

	static const std::string BGM_OFF = "bgm_off";
	static const std::string EFFECT_OFF = "effect_off";
	static const std::string CONTROL_OFF = "control_off"; 

	// data depend pid
	static const std::string DATA_DEPEND_PID = "data_depend_pid";

	static const std::string ALREADY_ENTER_GAME = "already_enter_game";

	static const std::string REFUSE_ADDFRIEND = "refuse_addfriend";
	static const std::string REFUSE_TRADE = "refuse_trade";
	static const std::string HIDE_WING = "hide_wing";
	static const std::string HIDE_HEADNAME = "hide_headname";
	static const std::string HIDE_FASHION = "hide_fashion";
	static const std::string HIDE_WEAPON = "hide_weapon";

	static const std::string HIDE_SETTING = "hide_setting";
	static const std::string HIDE_PET = "hide_pet";
	static const std::string HIDE_DOG = "hide_dog";
	static const std::string SHOW_MY_GUILD_PLAYER = "show_my_guild_player";
	static const std::string SHOW_MY_SOCIAL_PLAYER = "show_my_social_player";
	static const std::string USE_DEFAULT_EQUIP = "use_default_equip";
	static const std::string NPC_DEFAULT_EQUIP = "npc_default_equip";

	static const std::string SHOW_ALLINFO = "show_allinfo";
	static const std::string SHOW_ONLYNAME = "show_onlyname";
	static const std::string SHOW_MONSTERNAME = "show_monstername";
	static const std::string SHOW_ITEMNAME = "show_itemname";
	static const std::string SHOW_BAGWARM = "show_bagwarm";
	static const std::string SHOW_RELATHION = "show_relation";

	static const std::string LAST_BOOTHPET = "last_boothpet";

	static const std::string BEATTACK_EFFECT_OFF = "beattack_effect_off";

	static const std::string AUTO_ATTACK_ON = "auto_attack_on";

	static const std::string AUTO_FS_ZIDONGKAIDUN = "auto_fs_zidongkaidun";
	static const std::string AUTO_FS_ZIDONGBINGFENGBAO = "auto_fs_zidongbingfengbao";

	static const std::string AUTO_DS_ZIDONGZHAOHUANBAOBAO = "auto_ds_zidongzhaohuanbaobao";

	static const std::string PICKITEM_1_35_ON = "pickitem_1_35_on";
	static const std::string PICKITEM_35_40_ON = "pickitem_35_40_on";
	static const std::string PICKITEM_40_45_ON = "pickitem_40_45_on";
	static const std::string PICKITEM_45_50_ON = "pickitem_45_50_on";
	static const std::string PICKITEM_50_55_ON = "pickitem_50_55_on";
	static const std::string PICKITEM_55__ON = "pickitem_55__on";

	static const std::string PICKITEM_CAILIAO_ON = "pickitem_cailiao_on";
	static const std::string PICKITEM_SHIYONG_ON = "pickitem_shiyong_on";

	static const std::string PICKITEM_CHIXUYAO_ON = "pickitem_chixuyao_on";
	static const std::string PICKITEM_SHUNHUIYAO_ON = "pickitem_shunhuiyao_on";

	static const std::string PICKITEM_PICKMONEY_ON = "pickitem_pickmoney_on";

	static const std::string PICKITEM_AUTOPICK_ON = "pickitem_autopick_on";
	static const std::string PICKITEM_TIPS_ON = "pickitem_tips_on";

	static const std::string SKILL_CI_SHA_OFF = "skill_ci_sha_off";
	static const std::string SKILL_LIE_HUO_OFF = "skill_lie_huo_off";
	static const std::string SKILL_BAN_YUE_OFF = "skill_ban_yue_off";

	static const std::string SET_FAST = "set_fast";
	static const std::string FAST_NUM_ = "fast_num_";
	static const std::string FAST_TYPE_ = "fast_type_";

	// update functor lua data

	static const std::string UPDATE_FUNCTOR_ID = "update_functor_";

}

#endif //__UserDataModule_h__