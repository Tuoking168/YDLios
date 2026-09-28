#include "MsgMaster.h"
#include "ModuleData.h"
#include "GuildModule.h"
#include "event/CPEventHelper.h"
#include "userdata/GameData.h"
#include "GuildDefinition.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "ErrorDefinition.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/GuildData.h"


typedef std::vector< GuildInfo > GuildInfoList;
typedef std::vector< GuildMemberInfo > GuildMemberInfoList;
typedef std::vector< GuildApplicationInfo > GuildApplicationInfoList;

static void setGuildList( const GuildInfoList &guildList ,int page,int maxPage)
{
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_PAGE, page);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MAXPAGE, maxPage);
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_LIST);
	SubModuleData::clearAll();
	int rank = 0;
	for (int i = 0; i < (int)guildList.size(); i++)
	{
		rank = guildList[i].rank;
		SubModuleData::setInt(rank, CPGuildData::GUILD_ID, guildList[i].GuildID);
		SubModuleData::setInt(rank, CPGuildData::GUILD_RANK, guildList[i].rank);
		SubModuleData::setString(rank, CPGuildData::GUILD_NAME, guildList[i].GuildName);
		SubModuleData::setInt(rank, CPGuildData::GUILD_LEVEL, guildList[i].level);
		SubModuleData::setString(rank, CPGuildData::GUILD_MASTERNAME, guildList[i].MasterName);
		SubModuleData::setInt(rank, CPGuildData::GUILD_MASTERID, guildList[i].MasterID);
		SubModuleData::setInt(rank, CPGuildData::GUILD_MEMBERCOUNT, guildList[i].MemberCount);
		SubModuleData::setInt(rank, CPGuildData::GUILD_MAXMEMBER, guildList[i].MaxMember);
		SubModuleData::setInt(rank, CPGuildData::GUILD_STATE, guildList[i].state);
	}
}

static void setGuildMemberList( const GuildMemberInfoList &guildMemberList, int page, int maxPage)
{
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_PAGE, page);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_MAXPAGE, maxPage);
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	SubModuleData::clearAll();
	int pid = 0;
	for (int i = 0; i < (int)guildMemberList.size(); i++)
	{
		pid = guildMemberList[i].pid;
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_PID, pid);
		SubModuleData::setString(pid, CPGuildData::GUILD_MEMBER_NAME, guildMemberList[i].name);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_LEVEL, guildMemberList[i].level);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_JOB, guildMemberList[i].job);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_NICKNAME, guildMemberList[i].post);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_CONTRIBUTION, guildMemberList[i].contribution);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_TODAYCONTRIBUTION, guildMemberList[i].todaycontribution);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_LASTONLINE, guildMemberList[i].lastonline);
	}
}

static void setGuildApplicationList( const GuildApplicationInfoList &guildApplicationInfoList)
{
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
	SubModuleData::clearAll();
	int pid = 0;
	for (int i = 0; i < (int)guildApplicationInfoList.size(); i++)
	{
		pid = guildApplicationInfoList[i].pid;
		SubModuleData::setInt(pid, CPGuildData::GUILD_APPLICATION_PID, pid);
		SubModuleData::setString(pid, CPGuildData::GUILD_APPLICATION_NAME, guildApplicationInfoList[i].name);
		SubModuleData::setInt(pid, CPGuildData::GUILD_APPLICATION_LEVEL, guildApplicationInfoList[i].lvl);
	}
}

static void setAllGuildMemberList( const GuildMemberInfoList &guildMemberList)
{
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_ALL_MEMBER_LIST);
	SubModuleData::clearAll();
	int pid = 0;
	for (int i = 0; i < (int)guildMemberList.size(); i++)
	{
		pid = guildMemberList[i].pid;
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_PID, pid);
		SubModuleData::setString(pid, CPGuildData::GUILD_MEMBER_NAME, guildMemberList[i].name);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_LEVEL, guildMemberList[i].level);
	}
}

void MsgMaster::HandleMessageCreateGuildResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgCreateGuildResponse, pMsg);
	
	CPEventHelper::msgResponse("HandleMessageCreateGuildResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildsInfoResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildsInfoResponse, pMsg);

	if(msg->errcode == Error::Success)
	{
		setGuildList(msg->Guilds,msg->page,msg->maxpage);
 	}
	CPEventHelper::msgResponse("HandleMessageGuildsInfoResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildMemberInfoNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildMemberInfoNotify, pMsg);
	
	setGuildMemberList(msg->members, 1, 1);
}

void MsgMaster::HandleMessageMyGuildInfoNotify(IMsg *pMsg)
{
	MsgMyGuildInfoNotify *msg = dynamic_cast<MsgMyGuildInfoNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_CONTRIBUTION, msg->myGuildContribution);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MONEY, msg->myGuildmoney);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_RANK, msg->myGuildinfo.rank);
	ModuleData::setString(CPModuleName::GUILD, CPGuildData::GUILD_NAME, msg->myGuildinfo.GuildName);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_LEVEL, msg->myGuildinfo.level);
	ModuleData::setString(CPModuleName::GUILD, CPGuildData::GUILD_MASTERNAME, msg->myGuildinfo.MasterName);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MASTERID, msg->myGuildinfo.MasterID);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBERCOUNT, msg->myGuildinfo.MemberCount);
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MAXMEMBER, msg->myGuildinfo.MaxMember);

	GuildData::setGuildProp(GuildType::guild_contribution,msg->myGuildContribution);
	GuildData::setGuildProp(GuildType::guild_money,msg->myGuildmoney);
	GuildData::setGuildProp(GuildType::guild_rank,msg->myGuildinfo.rank);
	GuildData::setGuildProp(GuildType::guild_level,msg->myGuildinfo.level);
	GuildData::setGuildStringProp(GuildType::guild_mastername,msg->myGuildinfo.MasterName);
	GuildData::setGuildProp(GuildType::guild_masterid,msg->myGuildinfo.MasterID);

	GameRole* myRole = GameData::getMyRole();
	if (myRole) myRole->setExStr(Entity::attr_guild_id, msg->myGuildinfo.GuildName);

	CPEventHelper::msgResponse("HandleMessageMyGuildInfoNotify", "", 0);
}
void MsgMaster::HandleMessageLeaveGuildResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgLeaveGuildResponse, pMsg);
	
	CPEventHelper::msgResponse("HandleMessageLeaveGuildResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildApplicationInfoNotify(IMsg *pMsg)
{
	MsgGuildApplicationInfoNotify *msg = dynamic_cast<MsgGuildApplicationInfoNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	setGuildApplicationList(msg->apps);
	CPEventHelper::msgResponse("HandleMessageGuildApplicationInfoNotify", "", 0);
}
void MsgMaster::HandleMessageGuildApplicationChangeNotify(IMsg *pMsg)
{
	MsgGuildApplicationChangeNotify *msg = dynamic_cast<MsgGuildApplicationChangeNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
	if (msg->reason == GuildType::reason_addapp)
	{
		int pid = msg->app.pid;
		SubModuleData::setInt(pid, CPGuildData::GUILD_APPLICATION_PID, pid);
		SubModuleData::setString(pid, CPGuildData::GUILD_APPLICATION_NAME, msg->app.name);
		SubModuleData::setInt(pid, CPGuildData::GUILD_APPLICATION_LEVEL, msg->app.lvl);
	}
	else if (msg->reason == GuildType::reason_deleteapp)
	{
		int pid = msg->app.pid;
		SubModuleData::clearData(pid);
	}
	CPEventHelper::msgResponse("HandleMessageGuildApplicationChangeNotify", "", 0);

}
void MsgMaster::HandleMessageApplicationResultResponse(IMsg *pMsg)
{
	MsgApplicationResultResponse *msg = dynamic_cast<MsgApplicationResultResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	
	CPEventHelper::msgResponse("HandleMessageApplicationResultResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildMemberInfoByPidResponse(IMsg *pMsg)
{
	MsgGuildMemberInfoByPidResponse *msg = dynamic_cast<MsgGuildMemberInfoByPidResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	if(msg->errcode == Error::Success)
	{
		ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_PID, msg->myGuildInfo.pid);
		ModuleData::setString(CPModuleName::GUILD, CPGuildData::GUILD_NAME, msg->myGuildInfo.name);
		ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_LEVEL, msg->myGuildInfo.level);
		ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_JOB, msg->myGuildInfo.job);
		ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_NICKNAME, msg->myGuildInfo.post);
		ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_CONTRIBUTION, msg->myGuildInfo.contribution);
		ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_TODAYCONTRIBUTION, msg->myGuildInfo.todaycontribution);
		ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LASTONLINE, msg->myGuildInfo.lastonline);
 	}
	CPEventHelper::msgResponse("HandleMessageGuildMemberInfoByPidResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildMoneyUpdateNotify(IMsg *pMsg)
{
	MsgGuildMoneyUpdateNotify *msg = dynamic_cast<MsgGuildMoneyUpdateNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	ModuleData::setInt(CPModuleName::GUILD, CPGuildData::GUILD_MONEY, msg->gold);
	CPEventHelper::msgResponse("HandleMessageGuildMoneyUpdateNotify", "", 0);
}
void MsgMaster::HandleMessageDeleteGuildMemberResponse(IMsg *pMsg)
{
	MsgDeleteGuildMemberResponse *msg = dynamic_cast<MsgDeleteGuildMemberResponse*>(pMsg);
	if (!msg)
	{
		return;
	}

	CPEventHelper::msgResponse("HandleMessageDeleteGuildMemberResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildRewardResponse(IMsg *pMsg)
{
	MsgGuildRewardResponse *msg = dynamic_cast<MsgGuildRewardResponse*>(pMsg);
	if (!msg)
	{
		return;
	}

	CPEventHelper::msgResponse("HandleMessageGuildRewardResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildMasterResetResponse(IMsg *pMsg)
{
	MsgGuildMasterResetResponse *msg = dynamic_cast<MsgGuildMasterResetResponse*>(pMsg);
	if (!msg)
	{
		return;
	}

	CPEventHelper::msgResponse("HandleMessageGuildMasterResetResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildMemberChangeNotify(IMsg *pMsg)
{
	MsgGuildMemberChangeNotify *msg = dynamic_cast<MsgGuildMemberChangeNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_MEMBER_LIST);
	if (msg->reason == GuildType::reason_addmember)
	{
		int pid = msg->player.pid;
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_PID, pid);
		SubModuleData::setString(pid, CPGuildData::GUILD_MEMBER_NAME, msg->player.name);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_LEVEL, msg->player.level);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_JOB, msg->player.job);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_NICKNAME, msg->player.post);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_CONTRIBUTION, msg->player.contribution);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_TODAYCONTRIBUTION, msg->player.todaycontribution);
		SubModuleData::setInt(pid, CPGuildData::GUILD_MEMBER_LASTONLINE, msg->player.lastonline);

		SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
		SubModuleData::clearData(pid);
	}
	else if (msg->reason == GuildType::reason_deleteapp)
	{
		int pid = msg->player.pid;
		SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_APPLICATION_LIST);
		SubModuleData::clearData(pid);
	}
	else if(msg->reason == GuildType::reason_deletemember)
	{
		int pid = msg->player.pid;
		SubModuleData::clearData(pid);
	}
	CPEventHelper::msgNotify("HandleMessageGuildMemberChangeNotify","",0,0,0,0);
}
void MsgMaster::HandleMessageGuildNicknameLoadNotify(IMsg *pMsg)
{
	MsgGuildNicknameLoadNotify *msg = dynamic_cast<MsgGuildNicknameLoadNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_LIST);
	int nid = msg->job;

	std::string nickname = msg->nickname;
	if (msg->nickname.length()<=0)
	{
		if (LuaData::getProp(LuaData::GUILD_JOB_REWARD,nid,"nickname",nickname))
		{
			if (nickname.empty()||nickname.length()<=0||nickname=="0")
			{
				LuaData::getProp(LuaData::GUILD_JOB_REWARD,GuildType::post_normal,"nickname",nickname);
			}
		}
	}

	SubModuleData::setInt(nid, CPGuildData::GUILD_NICKNAME_JOB, nid);
	SubModuleData::setString(nid, CPGuildData::GUILD_NICKNAME_NAME, nickname);
	
	CPEventHelper::msgResponse("HandleMessageGuildNicknameLoadNotify", "", 0);
}
void MsgMaster::HandleMessageGuildNicknameUpdateResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildNicknameUpdateResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageGuildNicknameUpdateResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildPlacardNotify(IMsg *pMsg)
{
	// deprecated
}

void MsgMaster::HandleMessageGuildPlacardChangeResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildPlacardChangeResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGuildPlacardChangeResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildPublicNoticeNotify(IMsg *pMsg)
{
	// deprecated
}

void MsgMaster::HandleMessageGuildMemberNicknameChangeResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildMemberNicknameChangeResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageGuildMemberNicknameChangeResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildApplyGCZResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildApplyGCZResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageGuildApplyGCZResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildInviteResponse(IMsg *pMsg)
{
	MsgGuildInviteResponse *msg = dynamic_cast<MsgGuildInviteResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageGuildInviteResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildInviteResultResponse(IMsg *pMsg)
{
	MsgGuildInviteResultResponse *msg = dynamic_cast<MsgGuildInviteResultResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageGuildInviteResultResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildInviteNotify(IMsg *pMsg)
{
	MsgGuildInviteNotifyEx *msg = dynamic_cast<MsgGuildInviteNotifyEx*>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgNotify("HandleMessageGuildInviteNotify","",0,msg->name,msg->guildname,msg->pid,msg->gid);
}
void MsgMaster::HandleMessageGuildInviteResultNotify(IMsg *pMsg)
{
	MsgGuildInviteResultNotify *msg = dynamic_cast<MsgGuildInviteResultNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::uiNotify("HandleMessageGuildInviteResultNotify","",Error::TargetAgreeToJoinGuild);
}
void MsgMaster::HandleMessageGuildDonateResponse(IMsg *pMsg)
{
	MsgGuildDonateResponse *msg = dynamic_cast<MsgGuildDonateResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageGuildDonateResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildAllMemberInfoResponse(IMsg *pMsg)
{
	MsgGuildAllMemberInfoResponse *msg = dynamic_cast<MsgGuildAllMemberInfoResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	if(msg->errcode == Error::Success)
	{
		setAllGuildMemberList(msg->GuildMember);
	}
	CPEventHelper::msgResponse("HandleMessageGuildAllMemberInfoResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildGCZAttackListResponse(IMsg *pMsg)
{
	MsgGuildGCZAttackListResponse *msg = dynamic_cast<MsgGuildGCZAttackListResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GCZ_ATTACK_GUILD_LIST);
	SubModuleData::clearAll();
	int pid = 0;
	for (int i = 0; i < (int)msg->guilds.size(); i++)
	{
		SubModuleData::setString(i, CPGuildData::GUILD_NAME, msg->guilds[i]);
	}

	CPEventHelper::msgResponse("HandleMessageGuildGCZAttackListResponse", "", 0);
}

void MsgMaster::HandleMessageGuildGCZSetJobResponse(IMsg *pMsg)
{
	MsgGuildGCZSetJobResponse *msg = dynamic_cast<MsgGuildGCZSetJobResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageGuildGCZSetJobResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageGuildGCZGetJobRewardResponse(IMsg *pMsg)
{
	MsgGuildGCZGetJobRewardResponse *msg = dynamic_cast<MsgGuildGCZGetJobRewardResponse*>(pMsg);
	if (!msg)
	{
		return;
	}
	CPEventHelper::msgResponse("HandleMessageGuildGCZGetJobRewardResponse", "", msg->errcode);
}
void MsgMaster::HandleMessageApplicationToGuildResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgApplicationToGuildResponse, pMsg);

	int errcode = msg->errcode;
	if (msg->errcode == Error::Success)
	{
		errcode = Error::err_guild_app_success;
	}
	CPEventHelper::msgResponse("HandleMessageApplicationToGuildResponse", "", errcode);
}
void MsgMaster::HandleMessageSyncGuildExDataNotify(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgsyncGuildExDataNotify, pMsg);
	
	GuildData::setGuildProp(msg->idx,msg->data);
	CPEventHelper::msgNotify("HandleMessageSyncGuildExDataNotify", "", 0 , msg->idx, msg->data, 0);
}
void MsgMaster::HandleMessageSyncGuildExStringDataNotify(IMsg *pMsg)
{
	MsgsyncGuildExStringDataNotify *msg = dynamic_cast<MsgsyncGuildExStringDataNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	
	GuildData::setGuildStringProp(msg->idx,msg->data);
	CPEventHelper::msgNotify("HandleMessageSyncGuildExStringDataNotify", "", 0 , msg->idx, 0, 0);
}
void MsgMaster::HandleMessageGuildAllNicknameNotify(IMsg *pMsg)
{
	MsgGuildAllNicknameNotify *msg = dynamic_cast<MsgGuildAllNicknameNotify*>(pMsg);
	if (!msg)
	{
		return;
	}
	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GUILD_NICKNAME_LIST);
	std::vector<string> vec = msg->nickname;
	int i=0;
	for (std::vector<string>::iterator it=vec.begin(); it != vec.end(); it++,i++)
	{
		int index = i+GuildType::guild_nick_normal;
		std::string nickname = *it;
		if (nickname.length()<=0)
		{
			if (LuaData::getProp(LuaData::GUILD_JOB_REWARD,i,"nickname",nickname))
			{
				if (nickname.empty()||nickname.length()<=0||nickname=="0")
				{
					LuaData::getProp(LuaData::GUILD_JOB_REWARD,index,"nickname",nickname);
				}
			}
		}

		GuildData::setGuildStringProp(index,nickname);

		CCLog("_droid_________________%d______%s",i,nickname.c_str());
	}

	CPEventHelper::msgResponse("HandleMessageGuildNicknameLoadNotify", "", 0);
}

void MsgMaster::HandleMessageGuildBuildResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildBuildResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGuildBuildResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildFinishBuildingResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildFinishBuildingResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGuildFinishBuildingResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageSyncGuildBuildingLevelNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgSyncGuildBuildingLevelNotify, pMsg);

	GuildData::setGuildProp(GuildType::guild_building_build_time, msg->buildingendtime);
	GuildData::setGuildProp(GuildType::guild_building_id, msg->isbuildid);
	GuildData::setGuildProp(GuildType::guild_building_guan_gong_level, msg->guangong);
	GuildData::setGuildProp(GuildType::guild_building_fu_li_level, msg->fuli);
	GuildData::setGuildProp(GuildType::guild_building_mao_xian_level, msg->maoxian);
	GuildData::setGuildProp(GuildType::guild_building_shen_shou_level, msg->shenshou);
	GuildData::setGuildProp(GuildType::guild_building_shang_dian_level, msg->shop);
	GuildData::setGuildProp(GuildType::guild_building_guang_huan_level, msg->guanghuan);
	CPEventHelper::msgNotify("HandleMessageSyncGuildBuildingLevelNotify", "");
}

void MsgMaster::HandleMessageGuildGuanGongWorshipResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildGuanGongWorshipResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGuildGuanGongWorshipResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildGuanGongAddCountResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildGuanGongAddCountResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGuildGuanGongAddCountResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildGuanGongGetRewardResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildGuanGongGetRewardResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGuildGuanGongGetRewardResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildShopItemBuyResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildShopItemBuyResponse, pMsg);

	CPEventHelper::msgResponse("HandleMessageGuildShopItemBuyResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildListVersionNotify( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildListVersionNotify, pMsg);

	CPUnused(msg->version);
	CPUnused(msg->maxpage);
	CPEventHelper::msgNotify("HandleMessageGuildListVersionNotify", "");
}

void MsgMaster::HandleMessageGuildPublicNoticeChangeResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildPublicNoticeChangeResponse, pMsg);
	CPEventHelper::msgResponse("HandleMessageGuildPublicNoticeChangeResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildGetIntDataResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildGetIntDataResponse, pMsg);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->guildID);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_3, msg->key);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_4, msg->data);
	CPEventHelper::msgResponse("HandleMessageGuildGetIntDataResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildGetStringDataResponse( IMsg *pMsg )
{
	CP_TEST_NULL_MSG(MsgGuildGetStringDataResponse, pMsg);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2, msg->guildID);
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_3, msg->key);
	CPEventHelper::setEventStringData(CPEventName::MSG_FINISH, CPEventData::VALUE_4, msg->data);
	CPEventHelper::msgResponse("HandleMessageGuildGetStringDataResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageCancelApplicationToGuildResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgCancelApplicationToGuildResponse, pMsg);
	
	CPEventHelper::msgResponse("HandleMessageCancelApplicationToGuildResponse",
		"", msg->errcode);
}

void MsgMaster::HandleMessageGuildExploreInitResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildExploreInitResponse, pMsg );
	
	GuildData::clearGuildTanXianData();
	for (int i = 0; i < (int)msg->items.size(); i++ )
	{		
		GuildData::setGuildTanXianData(i, msg->items[i] );
	}		
	CPEventHelper::msgResponse("HandleMessageGuildExploreInitResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildExploreResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildExploreResponse, pMsg );
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_2,msg->item);
	CPEventHelper::msgResponse("HandleMessageGuildExploreResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildOpenBuffResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildOpenBuffResponse, pMsg );	
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH,CPEventData::VALUE_2,msg->buffID);
	CPEventHelper::msgResponse("HandleMessageGuildOpenBuffResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildOpenWelfareResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildOpenWelfareResponse, pMsg );	
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH,CPEventData::VALUE_2,msg->welfareID);
	CPEventHelper::msgResponse("HandleMessageGuildOpenWelfareResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildGetWelfareResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildGetWelfareResponse, pMsg );
	CPEventHelper::msgResponse("HandleMessageGuildGetWelfareResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildWelfareStatusResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildWelfareStatusResponse, pMsg );
	CPEventHelper::setEventIntData(CPEventName::MSG_FINISH,CPEventData::VALUE_2,msg->welfareStatus);
	CPEventHelper::msgResponse("HandleMessageGuildWelfareStatusResponse", "", msg->errcode);
}

void MsgMaster::HandleMessageGuildGczOccupyRewardResponse(IMsg *pMsg)
{
	CP_TEST_NULL_MSG(MsgGuildGczOccupyRewardResponse, pMsg );
	CPEventHelper::msgResponse("HandleMessageGuildWelfareStatusResponse", "", msg->errcode);
}