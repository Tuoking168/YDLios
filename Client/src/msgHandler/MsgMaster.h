#ifndef  ___MSG_MASTER__H___
#define  ___MSG_MASTER__H___

#include "Message/MsgIf.h"
#include "MsgAuth.h"
#include "MsgItem.h"
#include "MsgLogin.h"
#include "MsgScene.h"
#include "MsgPlayer.h"
#include "MsgQuest.h"
#include "MsgGuild.h"
#include "MsgPet.h"
#include "MsgShop.h"
#include "MsgTrade.h"
#include "MsgTeam.h"
#include "MsgActivity.h"
#include "MsgRelationship.h"
#include "MsgWorld.h"
#include "MsgDownload.h"

#include "utils/MacroUtils.h"

class IMsg;
class MsgMaster
{
public:
	MsgMaster();
	virtual void updateMessage(IMsg*);

	//
	// AuthHandler
	//
	static void HandleMessageAuthServerListNotify(IMsg *pMsg);
	static void HandleMessageAuthResponse(IMsg *pMsg);
	static void HandleMessageAuthResponseEx(IMsg *pMsg);
	static void HandleMessageRegisterResponse(IMsg *pMsg);
	static void HandleMessageAuthCheckVersionStrongResponse(IMsg *pMsg);
	static void HandleMessageAuthMiniStrongUpdateResponse(IMsg *pMsg);
	static void HandleMessageAccessTokenResponse(IMsg *pMsg);
	static void HandleMessageAuthCheckVersionOptionalResponse(IMsg *pMsg);
	static void HandleMessageAuthBindByChannelResponse( IMsg *pMsg );
	static void HandleAuthServerListNotifyEx( IMsg *pMsg );
	static void HandleMessageAuthServerListNotifyEnd( IMsg *pMsg );
	static void HandleMessageAuthCheckVersionStrongUpdateResponse( IMsg *pMsg );

	//
	// LoginHandler
	//
	static void HandleMessageEnterServerResponse(IMsg *pMsg);
	static void HandleMessageRandomANameResponse(IMsg *pMsg);
	static void HandleMessageCreatePlayerResponse(IMsg *pMsg);
	static void HandleMessageEnterGameResponse(IMsg *pMsg);
	static void HandleMessageDeletePlayerResponse(IMsg *pMsg);
	static void HandleMessagePlayerReconnectResponse(IMsg *pMsg);
	static void HandleMessageBeKicked(IMsg *pMsg);
	static void HandleMsgServerQueueNotify(IMsg *pMsg);

	//
	// SceneHandler
	//
	static void HandleMessageEnterSceneResponse(IMsg *pMsg);
	static void HandleMessageMapSelfLeaveNotify(IMsg* pMsg);
	static void HandleMessageMapSelfEnterVirtalSceneNotify(IMsg *pMsg);

	static void HandleMessageSceneMonstersCleanNotify(IMsg* pMsg);

	static void HandleMessagePlayerMoveNotify(IMsg *pMsg);

	static void HandleMessageMapMeetNotify(IMsg *pMsg);
	static void HandleMessageMapByeNotify(IMsg *pMsg);
	static void HandleMessageEntityMoveNotify(IMsg *pMsg);
	static void HandleMessageEntityTurnNotify(IMsg *pMsg);

	static void HandleMessageMeetEntityExDataNotify(IMsg *pMsg);
	static void HandleMessageMeetEntityExStrNotify(IMsg *pMsg);

	static void HandleMessageMapMeetPlayerNotify(IMsg *pMsg);
	static void HandleMessageMapMeetMonsterNotify(IMsg *pMsg);
	static void HandleMessageMapMeetNPCNotify(IMsg *pMsg);
	static void HandleMessageMapMeetItemNotify(IMsg *pMsg);
	static void HandleMessageMapMeetDogNotify(IMsg *pMsg);
	static void HandleMessageMapMeetPetNotify(IMsg *pMsg);
	static void HandleMessageMapMeetSkillNotify(IMsg *pMsg);
	static void HandleMessageMapMeetMarketNotify(IMsg *pMsg);
	static void HandleMessageEntityEffectNotify(IMsg *pMsg);
	static void HandleMessageSyncEntityLevelupNotify(IMsg *pMsg);

	static void HandleMessageEntityUseSkillNotify(IMsg *pMsg);
	static void HandleMessageEntityBeUsedSkillNotify(IMsg *pMsg);

	static void HandleMessageEntityHpChangeNotify(IMsg *pMsg);
	static void HandleMessageEntityMaxHPChangeNotify(IMsg *pMsg);

	static void HandleMessageEntityHpChangeDelayNotify(IMsg *pMsg);
	static void HandleMessageEntityMpChangeNotify(IMsg *pMsg);
	static void HandleMessageEntityBeAttackedDelayNotify(IMsg *pMsg);
	static void HandleMessageImBeAttackedDelayNotify(IMsg *pMsg);

	static void HandleMessageEntityEquipChangeNotify(IMsg *pMsg);

	static void HandleMessageFetchItemResponse(IMsg *pMsg);
	static void HandleMessageAbandonItemResponse(IMsg *pMsg);
	static void HandleMessagePickPlantResponse(IMsg *pMsg);

	static void HandleMessageEntityPlayerInfoNotify(IMsg *pMsg);

	static void HandleMessageUpdScenePropsNotify(IMsg *pMsg);
	static void HandleMessageUpdSceneStringNotify(IMsg *pMsg);
	
	static void HandleMessageSyncEntitySpeedNotify(IMsg *pMsg);

	static void HandleMessagePlayerMineonPosResponse(IMsg *pMsg);


	//
	// PlayerHandler
	//  
	static void HandleMessageAddSkillNotify(IMsg *pMsg); 
	static void HandleMessageRmvSkillNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerSkillDataNotify(IMsg *pMsg);
	static void HandleMessageUpdSkillCoolDownNotify(IMsg *pMsg);
	static void HandleMessagePlayerUseSkillResponse(IMsg *pMsg);
	static void HandleMessageUpdSkillExpNotify(IMsg *pMsg);

	static void HandleMessageUpdPlayerBaseNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerLevelNotify(IMsg *pMsg);

	static void HandleMessageUpdPlayerCombatAllNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerCombatDataExNotify(IMsg *pMsg);


	static void HandleMessagePlayerUpdGeneNotify(IMsg *pMsg);
	static void HandleMessagePlayerRmvGeneNotify(IMsg *pMsg);

	static void HandleMessageMapSelfEnterNotify(IMsg *pMsg);

	static void HandleMessageUpdPlayerDetailNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerVcoinNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerGoldNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerCouponNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerLvlExpNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerHonorNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerReputationNotify(IMsg *pMsg);
	static void HandleMessageUpdPlayerMeritoriousNotify(IMsg *pMsg);

	static void HandleMessageUpdBaseCoolDownNotify(IMsg *pMsg);
	static void HandleMessageCleanCoolDownResponse(IMsg *pMsg);

	static void HandleMessageUpdPlayerPropsDataNotify(IMsg *pMsg);

	static void HandleMessageReviveEntityResponse(IMsg *pMsg);
	static void HandleMessageSpecialQuestCountResponse(IMsg *pMsg);
	static void HandleMessageEntityMarketInfoNotify(IMsg *pMsg);

	static void HandleMessageSetPlayerPkModeResponse(IMsg *pMsg);

	static void HandleMessageChatNotify(IMsg *pMsg);
	static void HandleMessageChatResponse(IMsg *pMsg);

	static void HandleMessageUnlockBagSlotResponse(IMsg *pMsg);
	static void HandleMessageOpenHonorResponse(IMsg *pMsg);
	static void HandleMessageOpenHonorByGoldResponse(IMsg *pMsg);
	static void HandleMessageUpgradeHonorResponse(IMsg *pMsg);
	static void HandleMessageUpgradeHonorByGoldResponse(IMsg *pMsg);
	static void HandleMessageCloseHonorNotify(IMsg *pMsg);

	static void HandleMessageReBornResponse(IMsg *pMsg);

	static void HandleMessageSyncPlayerEventDataNotify(IMsg *pMsg);
	static void HandleMessageSyncPlayerLimitTimeRewardNotify(IMsg *pMsg);
	static void HandleMessageGetPlayerLimitTimeRewardResponse(IMsg *pMsg);

	static void HandleMesssagePlayerDeadInfoNotify( IMsg *pMsg );

	static void HandleMessageGetGiftResponse(IMsg *pMsg);
	static void HandleMessageSyncWorldTimeNotify(IMsg *pMsg);

	static void HandleMessageReSignDayResponse(IMsg *pMsg);

	static void HandleMessageFuncDataNotify(IMsg *pMsg);
	static void HandleMessageFuncDataOperatorResponse(IMsg *pMsg);

	static void HandleMessageHeadTitleOperationResponse(IMsg *pMsg);
	static void HandleMessageReNameResponse(IMsg *pMsg);
	static void HandleMessageCommonResponse(IMsg *pMsg);
	static void HandleMessageFloatPanelNotify(IMsg *pMsg);

	//
	// ItemHandler
	//
	static void HandleMessageItemInfoNotify(IMsg *pMsg);
	static void HandlemessageItemUpdExDataNotify(IMsg *pMsg);
	static void HandleMessageItemAddNotify(IMsg *pMsg);
	static void HandleMessageItemAddNotifyEx(IMsg *pMsg);
	static void HandleMessageItemRmvNotify(IMsg *pMsg);
	static void HandleMessageItemUpdCountNotify(IMsg *pMsg);
	static void HandleMessageItemUpdPositionNotify(IMsg *pMsg);
	static void HandleMessageItemUpdElvlNotify(IMsg *pMsg);
	static void HandleMessageItemUpdSlotNotify(IMsg *pMsg);
	static void HandleMessageItemUpdDataComboNotify(IMsg *pMsg);
	static void HandleMessageItemUpdSidNotify(IMsg* pMsg);
	static void HandleMessageItemUpdSkillNotify(IMsg *pMsg);
	static void HandleMessageItemOperationNotify(IMsg *pMsg);
	static void HandleMessageBuyItemResponse(IMsg *pMsg);
	static void HandleMessageBagisFull(IMsg *pMsg);

	static void HandleMessageItemUpdData(IMsg *pMsg);
	static void HandleMessageItemFailorSuccess(IMsg *pMsg);
	static void HandleMessageMarketSetItemResponse(IMsg *pMsg);
	static void HandleMessageItemInfoDataGetResponse(IMsg *pMsg);
	static void HandleMessageMsgItemOperationResponsePile(IMsg *pMsg);
	static void HandleMessageItemOperationResponseRepair(IMsg *pMsg);
	
	//
	// QuestHandler
	//
	static void HandleMessageQuestUpdateList(IMsg *pMsg);
	static void HandleMessageQuestUpdate(IMsg *pMsg);
	static void HandleMessageQuestAcceptResponse(IMsg *pMsg);
	static void HandleMessageQuestSubmitResponse(IMsg *pMsg);
	static void HandleMessageQuestRemoveResponse(IMsg *pMsg);
	static void HandleMessageClickNPCResponse(IMsg *pMsg);
	static void HandleMessageClickNPCFunctionScriptResponse(IMsg *pMsg);
	static void HandleMessageCrossServerResponse(IMsg *pMsg);

	//
	// Chart
	//
	static void HandleMessageChartInfoResponse(IMsg *pMsg);
	static void HandleMessageGetWorldChartResponse(IMsg *pMsg);
	static void HandleMessageGetWorldChartNotify(IMsg *pMsg);

	//
	// RobotPlay
	//
	static void HandleMessageRobotPlayResponse(IMsg *pMsg);
	static void HandleMessageRobotPlayEndResponse(IMsg *pMsg);
	static void HandleMessageRobotPlayNotify(IMsg *pMsg);
	static void HandleMessageRobotRewardResponse(IMsg *pMsg);
	static void HandleMessageRobotPlaySpeedUpResponse(IMsg *pMsg);


	// guild
	static void HandleMessageGuildsInfoResponse(IMsg *pMsg);
	static void HandleMessageDeleteGuildMemberResponse(IMsg *pMsg);
	static void HandleMessageGuildRewardResponse(IMsg *pMsg);
	static void HandleMessageGuildMemberInfoByPidResponse(IMsg *pMsg);
	static void HandleMessageGuildMoneyUpdateNotify(IMsg *pMsg);
	static void HandleMessageCreateGuildResponse(IMsg *pMsg);
	static void HandleMessageGuildMemberInfoResponse(IMsg *pMsg);
	static void HandleMessageApplicationResultResponse(IMsg *pMsg);
	static void HandleMessageGuildMemberChangeNotify(IMsg *pMsg);
	static void HandleMessageApplicationToGuildResponse(IMsg *pMsg);
	static void HandleMessageGuildMemberInfoNotify(IMsg *pMsg);
	static void HandleMessageGuildApplicationInfoNotify(IMsg *pMsg);
	static void HandleMessageRefreshMyGuildInfoNotify(IMsg *pMsg);
	static void HandleMessageGuildPlacardNotify(IMsg *pMsg);
	static void HandleMessageGuildPublicNoticeNotify(IMsg *pMsg);
	static void HandleMessageMyGuildInfoNotify(IMsg *pMsg);
	static void HandleMessageGuildApplicationChangeNotify(IMsg *pMsg);
	static void HandleMessageGuildDonateResponse(IMsg *pMsg);
	static void HandleMessageLeaveGuildResponse(IMsg *pMsg);
	static void HandleMessageGuildPlacardChangeResponse(IMsg *pMsg);
	static void HandleMessageGuildApplicationListNotify(IMsg *pMsg);
	static void HandleMessageGuildMasterResetResponse(IMsg *pMsg);
	static void HandleMessageGuildStoreDataResponse(IMsg *pMsg);
	static void HandleMessageGuildAssignItemResponse(IMsg *pMsg);
	static void HandleMessageGuildStoreDataUpdNotify(IMsg *pMsg);
	static void HandleMessageGuildRecordsNotify(IMsg *pMsg);
	static void HandleMessageGuildRecordChangeNotify(IMsg *pMsg);
	static void HandleMessageGuildBossCallResponse(IMsg *pMsg);
	static void HandleMessageGuildBossEnterResponse(IMsg *pMsg);
	static void HandleMessageGuildBossBeginNotify(IMsg *pMsg);
	static void HandleMessageGuildBossMadNessNotify(IMsg *pMsg);
	static void HandleMessageGuildBossEndNotify(IMsg *pMsg);
	static void HandleMessageGuildChampionShipSignUpResponse(IMsg *pMsg);
	static void HandleMessageGuildChampionMySignUpStateNotify(IMsg *pMsg);
	static void HandleMessageGuildChampionShipStateNotify(IMsg *pMsg);
	static void HandleMessageGuildChampionShipGuildFightListNotify(IMsg *pMsg);
	static void HandleMessageMyGuildWinCntNotify(IMsg *pMsg);
	static void HandleMessageTotalFightWinCntNotify(IMsg *pMsg);
	static void HandleMessageGuildChampionShipCombatDataResponse(IMsg *pMsg);
	static void HandleMessageGuildChampionShipSimpleDataResponse(IMsg *pMsg);
	static void HandleMessageGuildChampionShipRankResponse(IMsg *pMsg);
	static void HandleMessageGuildNicknameLoadNotify(IMsg *pMsg);
	static void HandleMessageGuildNicknameUpdateResponse(IMsg *pMsg);
	static void HandleMessageGuildMemberNicknameChangeResponse(IMsg *pMsg);
	static void HandleMessageGuildApplyGCZResponse(IMsg *pMsg);
	static void HandleMessageGuildInviteResponse(IMsg *pMsg);
	static void HandleMessageGuildInviteResultResponse(IMsg *pMsg);
	static void HandleMessageGuildInviteNotify(IMsg *pMsg);
	static void HandleMessageGuildInviteResultNotify(IMsg *pMsg);
	static void HandleMessageGuildAllMemberInfoResponse(IMsg *pMsg);
	static void HandleMessageGuildGCZAttackListResponse(IMsg *pMsg);
	static void HandleMessageGuildGCZSetJobResponse(IMsg *pMsg);
	static void HandleMessageGuildGCZGetJobRewardResponse(IMsg *pMsg);
	static void HandleMessageSyncGuildExDataNotify(IMsg *pMsg);
	static void HandleMessageSyncGuildExStringDataNotify(IMsg *pMsg);
	static void HandleMessageGuildAllNicknameNotify(IMsg *pMsg);
	static void HandleMessageGuildBuildResponse(IMsg *pMsg);
	static void HandleMessageGuildFinishBuildingResponse(IMsg *pMsg);
	static void HandleMessageSyncGuildBuildingLevelNotify(IMsg *pMsg);
	static void HandleMessageGuildGuanGongWorshipResponse(IMsg *pMsg);
	static void HandleMessageGuildGuanGongAddCountResponse(IMsg *pMsg);
	static void HandleMessageGuildGuanGongGetRewardResponse(IMsg *pMsg);
	static void HandleMessageGuildShopItemBuyResponse(IMsg *pMsg);
	static void HandleMessageGuildListVersionNotify(IMsg *pMsg);
	static void HandleMessageGuildPublicNoticeChangeResponse(IMsg *pMsg);
	static void HandleMessageGuildGetIntDataResponse(IMsg *pMsg);
	static void HandleMessageGuildGetStringDataResponse(IMsg *pMsg);
	static void HandleMessageCancelApplicationToGuildResponse(IMsg *pMsg);
	static void HandleMessageGuildExploreInitResponse(IMsg *pMsg);
	static void HandleMessageGuildExploreResponse(IMsg *pMsg);
	static void HandleMessageGuildOpenBuffResponse(IMsg *pMsg);
	static void HandleMessageGuildOpenWelfareResponse(IMsg *pMsg);
	static void HandleMessageGuildGetWelfareResponse(IMsg *pMsg);
	static void HandleMessageGuildWelfareStatusResponse(IMsg *pMsg);
	static void HandleMessageGuildGczOccupyRewardResponse(IMsg *pMsg);

	//chat
	static void HandleMessagerecvChatMessage(IMsg *pMsg);
	static void HandleMessageSendPrivateChatMessageResponse(IMsg *pMsg);

	// pet 
	static void HandleMessageUpdPetInfoBaseNotify(IMsg *pMsg);
	static void HandleMessageUpdPetCombatNotify(IMsg *pMsg);
	static void HandleMessageRmvPetResponse(IMsg *pMsg);
	static void HandleMessageActivePetStateResponse(IMsg *pMsg);
	static void HandleMessagePetStateNotify(IMsg *pMsg);
	static void HandleMessageRelivePetResponse(IMsg *pMsg);
	static void HandleMessageFeedPetResponse(IMsg* pMsg);
	static void HandleMessageUpdPetLvlExpNotify(IMsg *pMsg);
	static void HandleMessageAddPetNotify(IMsg *pMsg);
	static void HandleMessageSetPetPickStateResponse(IMsg *pMsg);
	static void HandleMessageOpenMarketResponse(IMsg *pMsg);
	static void HandleMessageCloseMarketResponse(IMsg *pMsg);
	static void HandleMessageImprisonPetResponse( IMsg *pMsg );
	static void HandleMessageSyncPetExPropDataNotify( IMsg *pMsg );
	static void HandleMessageAddPetEggNotify( IMsg *pMsg );
	static void HandleMessageAddPetEggExNotify( IMsg *pMsg );
	static void HandleMessageDogOptionResponse( IMsg *pMsg);
	static void HandleMessageImprovePetAdvanceResponse( IMsg *pMsg );
	static void HandleMessageChangePetBestAttrResponse( IMsg *pMsg );
	static void HandleMessageSleepPetStateResponse(IMsg *pMsg);
	static void HandleMessageBuyEntityMarketThingResponse(IMsg *pMsg);
	static void HandleMessageSetPetPickSettingResponse(IMsg *pMsg);
	static void HandleMessagePetRebornResponse(IMsg *pMsg);

	static void HandleMessageAddMarketWordsResponse(IMsg *pMsg);
	static void HandleMessageGetMarketWordsResponse(IMsg *pMsg);

	// shop
	static void HandleMessageOpenShopResponse(IMsg *pMsg);
	static void HandleMessageOpenShopResponseEx(IMsg *pMsg);
	static void HandleMessageShopItemListNotify(IMsg *pMsg);
	static void HandleMessageShopBackBuyNotify(IMsg *pMsg);
	static void HandleMessageShopBackBuyRmvNotify(IMsg *pMsg);
	static void HandleMessageShopBackBuyAddNotify(IMsg *pMsg);
	static void HandleMessageShopBackItemResponse(IMsg *pMsg);
	static void HandleMessageBuyItemInShopResponse(IMsg *pMsg);
	static void HandleMessageCloseShopResponse(IMsg *pMsg);
	static void HandleMessageRmvPetNotify(IMsg *pMsg);

	//trade
	static void HandleMessageItemTradeOperationNotifiy(IMsg *pMsg);
	static void HandleMessageItemTradeOtherChangeItem(IMsg *pMsg);
	static void HandleMessageItemTradeChangeResponse(IMsg *pMsg);
	static void HandleMessageItemTradeLockInfo(IMsg *pMsg);
	static void HandleMessageItemTradeOverInfo(IMsg *pMsg);
	static void HandleMessageItemTradeChangeMoney(IMsg *pMsg);

	//team
	static void HandleMessageTeamInviteResponse(IMsg *pMsg);
	static void HandleMessageTeamJoinResponse(IMsg *pMsg);
	static void HandleMessageTeamQuitResponse(IMsg *pMsg);
	static void HandleMessageTeamMakeOperation(IMsg *pMsg);
	static void HandleMessageTeamMakeOperationReply(IMsg *pMsg);
	static void HandleMessageTeamMakeDecisionResponse(IMsg *pMsg);
	static void HandleMessageTeamInfoNotify(IMsg *pMsg);
	static void HandleMessageTeamInfoRmvNotify(IMsg *pMsg);
	static void HandleMessageTeamInfoUpdNotify(IMsg *pMsg);
	static void HandleMessageTeamKickPlayerResponse(IMsg *pMsg);
	static void HandleMessageTeamSetLeaderResponse(IMsg *pMsg);

	//activity
	static void HandleMessageSyncNotImportantActivityNotify(IMsg *pMsg);

	static void HandleMessageMobaiDataResponse(IMsg *pMsg);
	static void HandleMessageUpdMyMobaiDataNotify(IMsg *pMsg);
	static void HandleMessageRefreshMobaiPerResponse(IMsg *pMsg);
	static void HandleMessageMobaiBishiResponse(IMsg *pMsg);
	static void HandleMessageAddMobaiCntResponse(IMsg *pMsg);

	static void HandleMessageUpdCaiShenChuangGuanDataNotify(IMsg *pMsg);
	static void HandleMessageCaiShenChuangGuanDataResponse(IMsg *pMsg);
	static void HandleMessageCaiShenChuangGuanMissionUp(IMsg *pMsg);
	static void HandleMessageCaiShenChuangGuanfreshtimeResponse(IMsg *pMsg);
	static void HandleMessageCaiShenChuangGuanCaseOver(IMsg *pMsg);
	static void HandleMessageCaiShenChuangGuanMeetCaseResponse(IMsg *pMsg);

	static void HandleMessageCaiShenChuangGuanRestartResponse(IMsg *pMsg);
	
	static void HandleMessageUpdMeiNvHuSongDataNotify(IMsg *pMsg);
	static void HandleMessageMeiNvHuSongEnterResponse(IMsg *pMsg);
	static void HandleMessageMeiNvHuSongStartResponse(IMsg *pMsg);
	static void HandleMessageMeiNvHuSongRefreshResponse(IMsg *pMsg);

	static void HandleMessageListTreasureResponse(IMsg *pMsg);
	static void HandleMessageHuntTreasureResponse(IMsg *pMsg);
	static void HandleMessageGetHuntTreasureRewardResponse(IMsg *pMsg);
	static void HandleMessageSyncTreasureHuntRecordNotify(IMsg *pMsg);

	static void HandleMessageSyncEventStateNotify(IMsg *pMsg);
	static void HandleMessageSyncEventNotFinishCountNotify(IMsg *pMsg);
	static void HandleMessageSyncActivityBossStateNotify(IMsg *pMsg);

	static void HandleMessageSpiderThorwItemResponse(IMsg *pMsg);

	static void HandleMessageOpenArenaResponse(IMsg *pMsg);
	static void HandleMessageArenaListNotify(IMsg *pMsg);
	static void HandleMessageRefreshArenaBuffResponse(IMsg *pMsg);
	static void HandleMessageArenaFightResponse(IMsg *pMsg);
	static void HandleMessageArenaFightNotify(IMsg *pMsg);
	static void HandleMessageBuyArenaFightCntResponse(IMsg *pMsg);
	static void HandleMessageGetPlayerArenaFightRecordResponse(IMsg *pMsg);
	static void HandleMessageGetArenaHeroResponse(IMsg *pMsg);

	static void HandleMessageGetInstanceCntResponse(IMsg *pMsg);

	static void HandleMessageGetGiftByCodeResponse(IMsg *pMsg);

	static void HandleMessageHideActivityListNotify(IMsg *pMsg);


	//relationship
	static void HandleMessageRelationListResponse(IMsg *pMsg);
	static void HandleMessageRelationOperateResponse(IMsg *pMsg);
	static void HandleMessageRelationFindingResponse(IMsg *pMsg);

	//worldData
	static void HandleMessageWorldDataNotify(IMsg* pMsg);
	static void HandleMessageSyncWorldDataExNotify(IMsg *pMsg);
	static void HandleMessageSyncFloatNoticeNotify(IMsg *pMsg);
	static void HandleMessageSyncWorldBossNotify(IMsg *pMsg);
	static void HandleMessageSyncWorldBeginTimeNotify(IMsg *pMsg);
	static void HandleMessageSyncWorldDataResponse(IMsg *pMsg);
	static void HandleMessageSyncWorldDataStringResponse(IMsg *pMsg);
	static void HandleMessageScriptDataResponse(IMsg* pMsg);
	static void HandleMessageScriptPatchNotify(IMsg* pMsg);

	//otherRole
	static void HandleMessageGetOtherPlayerDataResponse(IMsg* pMsg);
	static void HandleMessageSyncOtherPlayerDataNotify(IMsg* pMsg);
	static void HandleMessageSyncOtherPlayerEquipNotify(IMsg* pMsg);


	// download
	static void HandleMessageDownload(IMsg *pMsg);
	static void HandleMessageDownloadProgress(IMsg *pMsg);

	// horse
	static void HandleHorsePeiYangAck(IMsg *pMsg);
	static void HandleHorseJinJieAck(IMsg *pMsg);
	static void HandleHorseEquipQiangHuaAck(IMsg *pMsg);
	static void HandleHorseEquipJinJieAck(IMsg *pMsg);

	static void HandleSyncEntityRideStateNotify(IMsg *pMsg);

};

#define CP_TEST_NULL_MSG(_class_, _target_) \
	_class_ *msg = NULL; \
	CP_DYNAMIC_CAST_RETURN(_class_, _target_, msg);

#endif //___MSG_MASTER__H___