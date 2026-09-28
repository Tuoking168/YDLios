#include "MsgHandler.h"
#include "MsgMaster.h"

MsgHandlerMap msgTable;
int testInt;

#define REGISTERMSGHANDLER(MSG, HANDLER)	\
	msghandler.name = #MSG;					\
	msghandler.handler = HANDLER;			\
	msgTable.insert(MsgHandlerMap::value_type(MSG::Category << 16 | MSG::Id, msghandler));

bool InitMsgHandler()
{
	MsgHandler msghandler;
	// Auth
	REGISTERMSGHANDLER(MsgAuthServerListNotify, MsgMaster::HandleMessageAuthServerListNotify);
	REGISTERMSGHANDLER(MsgAuthResponse		, MsgMaster::HandleMessageAuthResponse);
	REGISTERMSGHANDLER(MsgAuthResponseEx		, MsgMaster::HandleMessageAuthResponseEx);
	REGISTERMSGHANDLER(MsgAuthRegisterResponse	, MsgMaster::HandleMessageRegisterResponse);
	REGISTERMSGHANDLER(MsgAuthCheckVersionStrongResponse, MsgMaster::HandleMessageAuthCheckVersionStrongResponse);
	REGISTERMSGHANDLER(MsgAccessTokenResponse, MsgMaster::HandleMessageAccessTokenResponse);
	REGISTERMSGHANDLER(MsgAuthCheckVersionOptionalResponse, MsgMaster::HandleMessageAuthCheckVersionOptionalResponse);
	REGISTERMSGHANDLER(MsgAuthServerListNotifyEnd, MsgMaster::HandleMessageAuthServerListNotifyEnd);
	REGISTERMSGHANDLER(MsgAuthCheckVersionStrongUpdateResponse, MsgMaster::HandleMessageAuthCheckVersionStrongUpdateResponse);
	REGISTERMSGHANDLER(MsgAuthMiniStrongUpdateResponse, MsgMaster::HandleMessageAuthMiniStrongUpdateResponse);

	// Login
	REGISTERMSGHANDLER(MsgEnterServerResponse	, MsgMaster::HandleMessageEnterServerResponse);
	REGISTERMSGHANDLER(MsgEnterGameResponse		, MsgMaster::HandleMessageEnterGameResponse);
	REGISTERMSGHANDLER(MsgCreatePlayerResponse	, MsgMaster::HandleMessageCreatePlayerResponse);
	REGISTERMSGHANDLER(MsgDeletePlayerResponse	, MsgMaster::HandleMessageDeletePlayerResponse);
	REGISTERMSGHANDLER(MsgPlayerReconnectResponse,MsgMaster::HandleMessagePlayerReconnectResponse);
	REGISTERMSGHANDLER(MsgBeKicked,				  MsgMaster::HandleMessageBeKicked);
	REGISTERMSGHANDLER(MsgServerQueueNotify,		MsgMaster::HandleMsgServerQueueNotify);
	REGISTERMSGHANDLER(MsgDeletePlayerResponse,	  MsgMaster::HandleMessageDeletePlayerResponse);
	
	// Scene
	REGISTERMSGHANDLER(MsgEnterSceneResponse		, MsgMaster::HandleMessageEnterSceneResponse);
	REGISTERMSGHANDLER(MsgPlayerMoveNotify			, MsgMaster::HandleMessagePlayerMoveNotify);
	REGISTERMSGHANDLER(MsgMapSelfEnterVirtalSceneNotify, MsgMaster::HandleMessageMapSelfEnterVirtalSceneNotify);
	REGISTERMSGHANDLER(MsgSyncSceneMonstersCleanNotify, MsgMaster::HandleMessageSceneMonstersCleanNotify);

	REGISTERMSGHANDLER(MsgMapByeNotify				, MsgMaster::HandleMessageMapByeNotify);
	REGISTERMSGHANDLER(MsgEntityMoveNotify			, MsgMaster::HandleMessageEntityMoveNotify);
	REGISTERMSGHANDLER(MsgEntityTurnNotify			, MsgMaster::HandleMessageEntityTurnNotify);
	
	REGISTERMSGHANDLER(MsgMeetEntityExDataNotify	, MsgMaster::HandleMessageMeetEntityExDataNotify);
	REGISTERMSGHANDLER(MsgMeetEntityExStrNotify, MsgMaster::HandleMessageMeetEntityExStrNotify);

	REGISTERMSGHANDLER(MsgMapMeetPlayerNotify		, MsgMaster::HandleMessageMapMeetPlayerNotify);
	REGISTERMSGHANDLER(MsgMapMeetMonsterNotify		, MsgMaster::HandleMessageMapMeetMonsterNotify);
	REGISTERMSGHANDLER(MsgMapMeetNPCNotify			, MsgMaster::HandleMessageMapMeetNPCNotify);
	REGISTERMSGHANDLER(MsgMapMeetItemNotify			, MsgMaster::HandleMessageMapMeetItemNotify);
	REGISTERMSGHANDLER(MsgMapMeetDogNotify			, MsgMaster::HandleMessageMapMeetDogNotify);
	REGISTERMSGHANDLER(MsgMapMeetSkillNotify		, MsgMaster::HandleMessageMapMeetSkillNotify);
	REGISTERMSGHANDLER(MsgMapMeetPetNotify			, MsgMaster::HandleMessageMapMeetPetNotify);
	REGISTERMSGHANDLER(MsgMapMeetMarketNotify		, MsgMaster::HandleMessageMapMeetMarketNotify);
	REGISTERMSGHANDLER(MsgEntityEffectNotify		, MsgMaster::HandleMessageEntityEffectNotify);
	REGISTERMSGHANDLER(MsgSyncEntityLevelupNotify	, MsgMaster::HandleMessageSyncEntityLevelupNotify);

	REGISTERMSGHANDLER(MsgEntityUseSkillNotify		, MsgMaster::HandleMessageEntityUseSkillNotify);
	REGISTERMSGHANDLER(MsgEntityBeUsedSkillNotify, MsgMaster::HandleMessageEntityBeUsedSkillNotify);

	REGISTERMSGHANDLER(MsgEntityMaxHPChangeNotify, MsgMaster::HandleMessageEntityMaxHPChangeNotify);
	REGISTERMSGHANDLER(MsgEntityHpChangeNotify		, MsgMaster::HandleMessageEntityHpChangeNotify);
	REGISTERMSGHANDLER(MsgEntityHpChangeDelayNotify , MsgMaster::HandleMessageEntityHpChangeDelayNotify);
	REGISTERMSGHANDLER(MsgEntityMpChangeNotify		, MsgMaster::HandleMessageEntityMpChangeNotify);
	REGISTERMSGHANDLER(MsgEntityBeAttackedDelayNotify,MsgMaster::HandleMessageEntityBeAttackedDelayNotify);
	REGISTERMSGHANDLER(MsgImBeAttackedDelayNotify, MsgMaster::HandleMessageImBeAttackedDelayNotify);

	REGISTERMSGHANDLER(MsgEntityEquipChangeNotify	, MsgMaster::HandleMessageEntityEquipChangeNotify);
	REGISTERMSGHANDLER(MsgFetchItemResponse		    , MsgMaster::HandleMessageFetchItemResponse);
	REGISTERMSGHANDLER(MsgAbandonItemResponse		, MsgMaster::HandleMessageAbandonItemResponse);
	REGISTERMSGHANDLER(MsgPickPlantResponse			, MsgMaster::HandleMessagePickPlantResponse);
	REGISTERMSGHANDLER(MsgMapSelfLeaveNotify		, MsgMaster::HandleMessageMapSelfLeaveNotify);
	REGISTERMSGHANDLER(MsgEntityPlayerInfoNotify	, MsgMaster::HandleMessageEntityPlayerInfoNotify);

	REGISTERMSGHANDLER(MsgUpdScenePropsNotify,		MsgMaster::HandleMessageUpdScenePropsNotify);
	REGISTERMSGHANDLER(MsgUpdSceneStringNotify,		MsgMaster::HandleMessageUpdSceneStringNotify);
	REGISTERMSGHANDLER(MsgsyncEntitySpeedNotify,	MsgMaster::HandleMessageSyncEntitySpeedNotify);

	REGISTERMSGHANDLER(MsgPlayerMineonPosResponse		, MsgMaster::HandleMessagePlayerMineonPosResponse);
 
	// Player
	REGISTERMSGHANDLER(MsgAddSkillNotify				, MsgMaster::HandleMessageAddSkillNotify);
	REGISTERMSGHANDLER(MsgRmvSkillNotify				, MsgMaster::HandleMessageRmvSkillNotify);
	REGISTERMSGHANDLER(MsgUpdPlayerSkillDataNotify			, MsgMaster::HandleMessageUpdPlayerSkillDataNotify);
	REGISTERMSGHANDLER(MsgUpdSkillExpNotify					, MsgMaster::HandleMessageUpdSkillExpNotify);
	REGISTERMSGHANDLER(MsgUpdSkillCoolDownNotify			, MsgMaster::HandleMessageUpdSkillCoolDownNotify);

	REGISTERMSGHANDLER(MsgUpdPlayerBaseNotify				, MsgMaster::HandleMessageUpdPlayerBaseNotify);

	REGISTERMSGHANDLER(MsgUpdPlayerCombatDataAllNotify		, MsgMaster::HandleMessageUpdPlayerCombatAllNotify);
	REGISTERMSGHANDLER(MsgUpdPlayerCombatDataExNotify		, MsgMaster::HandleMessageUpdPlayerCombatDataExNotify);

	REGISTERMSGHANDLER(MsgPlayerUpdGeneNotify				, MsgMaster::HandleMessagePlayerUpdGeneNotify);
	REGISTERMSGHANDLER(MsgPlayerRmvGeneNotify				, MsgMaster::HandleMessagePlayerRmvGeneNotify);

	REGISTERMSGHANDLER(MsgPlayerUseSkillResponse		, MsgMaster::HandleMessagePlayerUseSkillResponse);
	REGISTERMSGHANDLER(MsgMapSelfEnterNotify			, MsgMaster::HandleMessageMapSelfEnterNotify);

	REGISTERMSGHANDLER(MsgUpdPlayerDetailNotify			, MsgMaster::HandleMessageUpdPlayerDetailNotify);

	REGISTERMSGHANDLER(MsgUpdPlayerVcoinNotify			, MsgMaster::HandleMessageUpdPlayerVcoinNotify);
	REGISTERMSGHANDLER(MsgUpdPlayerCouponNotify			, MsgMaster::HandleMessageUpdPlayerCouponNotify);
	REGISTERMSGHANDLER(MsgUpdPlayerGoldNotify			, MsgMaster::HandleMessageUpdPlayerGoldNotify);
	REGISTERMSGHANDLER(MsgUpdPlayerHonorNotify			, MsgMaster::HandleMessageUpdPlayerHonorNotify);

	REGISTERMSGHANDLER(MsgUpdPlayerLvlExpNotify			, MsgMaster::HandleMessageUpdPlayerLvlExpNotify);
	REGISTERMSGHANDLER(MsgUpdPlayerReputationNotify		, MsgMaster::HandleMessageUpdPlayerReputationNotify);
	REGISTERMSGHANDLER(MsgUpdPlayerMeritoriousNotify	, MsgMaster::HandleMessageUpdPlayerMeritoriousNotify);

	REGISTERMSGHANDLER(MsgUpdBaseCoolDownNotify			, MsgMaster::HandleMessageUpdBaseCoolDownNotify);
	REGISTERMSGHANDLER(MsgCleanCoolDownResponse			, MsgMaster::HandleMessageCleanCoolDownResponse);

	REGISTERMSGHANDLER(MsgUpdPlayerPropsDataNotify		, MsgMaster::HandleMessageUpdPlayerPropsDataNotify);

	REGISTERMSGHANDLER(MsgReviveEntityResponse			, MsgMaster::HandleMessageReviveEntityResponse);
	REGISTERMSGHANDLER(MsgSpecialQuestCountResponse		, MsgMaster::HandleMessageSpecialQuestCountResponse);
	REGISTERMSGHANDLER(MsgEntityMarketInfoNotify		, MsgMaster::HandleMessageEntityMarketInfoNotify);

	REGISTERMSGHANDLER(MsgSetPlayerPkModeResponse		, MsgMaster::HandleMessageSetPlayerPkModeResponse);

	REGISTERMSGHANDLER(MsgChatNotify					, MsgMaster::HandleMessageChatNotify);
	REGISTERMSGHANDLER(MsgChatResponse					, MsgMaster::HandleMessageChatResponse);

	REGISTERMSGHANDLER(MsgUnlockBagSlotResponse			, MsgMaster::HandleMessageUnlockBagSlotResponse);
	REGISTERMSGHANDLER(MsgOpenHonorResponse				, MsgMaster::HandleMessageOpenHonorResponse);
	REGISTERMSGHANDLER(MsgOpenHonorByGoldResponse				, MsgMaster::HandleMessageOpenHonorByGoldResponse);
	REGISTERMSGHANDLER(MsgUpgradeHonorResponse			, MsgMaster::HandleMessageUpgradeHonorResponse);
	REGISTERMSGHANDLER(MsgUpgradeHonorByGoldResponse			, MsgMaster::HandleMessageUpgradeHonorByGoldResponse);
	REGISTERMSGHANDLER(MsgCloseHonorNotify				, MsgMaster::HandleMessageCloseHonorNotify);
	REGISTERMSGHANDLER(MsgReBornResponse				, MsgMaster::HandleMessageReBornResponse);
	REGISTERMSGHANDLER(MsgSyncPlayerEventDataNotify		, MsgMaster::HandleMessageSyncPlayerEventDataNotify);
	REGISTERMSGHANDLER(MsgSyncPlayerLimitTimeRewardNotify, MsgMaster::HandleMessageSyncPlayerLimitTimeRewardNotify);
	REGISTERMSGHANDLER(MsgGetPlayerLimitTimeRewardResponse, MsgMaster::HandleMessageGetPlayerLimitTimeRewardResponse);
	REGISTERMSGHANDLER(MsgPlayerDeadInfoNotify			, MsgMaster::HandleMesssagePlayerDeadInfoNotify);
	REGISTERMSGHANDLER(MsgGetGiftResponse				, MsgMaster::HandleMessageGetGiftResponse);
	REGISTERMSGHANDLER(MsgSyncWorldTimeNotify			, MsgMaster::HandleMessageSyncWorldTimeNotify);
	REGISTERMSGHANDLER(MsgReSignDayResponse				, MsgMaster::HandleMessageReSignDayResponse);
	REGISTERMSGHANDLER(MsgFuncDataNotify				, MsgMaster::HandleMessageFuncDataNotify);
	REGISTERMSGHANDLER(MsgFuncDataOperatorResponse		, MsgMaster::HandleMessageFuncDataOperatorResponse);
	REGISTERMSGHANDLER(MsgFloatPanelNotify				, MsgMaster::HandleMessageFloatPanelNotify);
	
	REGISTERMSGHANDLER(MsgHeadTitleOperationResponse        ,MsgMaster::HandleMessageHeadTitleOperationResponse);
	REGISTERMSGHANDLER(MsgReNameResponse        ,MsgMaster::HandleMessageReNameResponse);
	REGISTERMSGHANDLER(MsgCommonResponse        ,MsgMaster::HandleMessageCommonResponse);

	// Item
	REGISTERMSGHANDLER(MsgItemInfoNotify		, MsgMaster::HandleMessageItemInfoNotify);
	REGISTERMSGHANDLER(MsgItemAddNotify			, MsgMaster::HandleMessageItemAddNotify);
	REGISTERMSGHANDLER(MsgItemAddNotifyEx		, MsgMaster::HandleMessageItemAddNotifyEx);
	REGISTERMSGHANDLER(MsgItemRmvNotify			, MsgMaster::HandleMessageItemRmvNotify);
	REGISTERMSGHANDLER(MsgItemUpdCountNotify	, MsgMaster::HandleMessageItemUpdCountNotify);
	REGISTERMSGHANDLER(MsgItemUpdPositionNotify	, MsgMaster::HandleMessageItemUpdPositionNotify);
	REGISTERMSGHANDLER(MsgItemUpdSidNotify		, MsgMaster::HandleMessageItemUpdSidNotify);	
	REGISTERMSGHANDLER(MsgItemOperationNotify	, MsgMaster::HandleMessageItemOperationNotify);
	REGISTERMSGHANDLER(MsgItemUpdDataNotify			, MsgMaster::HandleMessageItemUpdData);
	REGISTERMSGHANDLER(MsgItemUpdExDataNotify		, MsgMaster::HandlemessageItemUpdExDataNotify);
	REGISTERMSGHANDLER(MsgItemFailorSuccessNotify	, MsgMaster::HandleMessageItemFailorSuccess);
	REGISTERMSGHANDLER(MsgMarketSetItemResponse		, MsgMaster::HandleMessageMarketSetItemResponse);
	REGISTERMSGHANDLER(MsgItemInfoDataGetResponse		, MsgMaster::HandleMessageItemInfoDataGetResponse);
	REGISTERMSGHANDLER(MsgItemOperationResponsePile		, MsgMaster::HandleMessageMsgItemOperationResponsePile);
	REGISTERMSGHANDLER(MsgItemOperationResponseRepair		, MsgMaster::HandleMessageItemOperationResponseRepair);


	// Quest
	REGISTERMSGHANDLER(MsgQuestUpdateListNotify			, MsgMaster::HandleMessageQuestUpdateList);
	REGISTERMSGHANDLER(MsgQuestUpdateNotify				, MsgMaster::HandleMessageQuestUpdate);
	REGISTERMSGHANDLER(MsgQuestAcceptResponse					, MsgMaster::HandleMessageQuestAcceptResponse);
	REGISTERMSGHANDLER(MsgQuestSubmitResponse   	        , MsgMaster::HandleMessageQuestSubmitResponse);
	REGISTERMSGHANDLER(MsgQuestRemoveResponse				, MsgMaster::HandleMessageQuestRemoveResponse);
	REGISTERMSGHANDLER(MsgClickNPCResponse				, MsgMaster::HandleMessageClickNPCResponse);
	REGISTERMSGHANDLER(MsgClickNPCFunctionScriptResponse				, MsgMaster::HandleMessageClickNPCFunctionScriptResponse);
	REGISTERMSGHANDLER(MsgCrossServerResponse				, MsgMaster::HandleMessageCrossServerResponse);
	
	// pet 
	REGISTERMSGHANDLER(MsgUpdPetInfoBaseNotify ,		MsgMaster::HandleMessageUpdPetInfoBaseNotify);
	REGISTERMSGHANDLER(MsgUpdPetCombatNotify,			MsgMaster::HandleMessageUpdPetCombatNotify);
	REGISTERMSGHANDLER(MsgRmvPetResponse,				MsgMaster::HandleMessageRmvPetResponse);
	REGISTERMSGHANDLER(MsgActivePetStateResponse ,		MsgMaster::HandleMessageActivePetStateResponse);
	REGISTERMSGHANDLER(MsgPetStateNotify,				MsgMaster::HandleMessagePetStateNotify);
	REGISTERMSGHANDLER(MsgRelivePetResponse,			MsgMaster::HandleMessageRelivePetResponse);
	REGISTERMSGHANDLER(MsgFeedPetResponse ,				MsgMaster::HandleMessageFeedPetResponse);
	REGISTERMSGHANDLER(MsgUpdPetLvlExpNotify,			MsgMaster::HandleMessageUpdPetLvlExpNotify);
	REGISTERMSGHANDLER(MsgAddPetNotify,					MsgMaster::HandleMessageAddPetNotify);
	REGISTERMSGHANDLER(MsgSetPetPickStateResponse,	    MsgMaster::HandleMessageSetPetPickStateResponse);
	REGISTERMSGHANDLER(MsgOpenMarketResponse,			MsgMaster::HandleMessageOpenMarketResponse);
	REGISTERMSGHANDLER(MsgCloseMarketResponse,			MsgMaster::HandleMessageCloseMarketResponse);
	REGISTERMSGHANDLER(MsgImprisonPetResponse,			MsgMaster::HandleMessageImprisonPetResponse);
	REGISTERMSGHANDLER(MsgRmvPetNotify,			MsgMaster::HandleMessageRmvPetNotify);
	REGISTERMSGHANDLER(MsgSyncPetExPropDataNotify,			MsgMaster::HandleMessageSyncPetExPropDataNotify);
	REGISTERMSGHANDLER(MsgAddPetEggNotify,			MsgMaster::HandleMessageAddPetEggNotify);
	REGISTERMSGHANDLER(MsgAddPetEggExNotify,			MsgMaster::HandleMessageAddPetEggExNotify);
	REGISTERMSGHANDLER(MsgDogOptionResponse,			MsgMaster::HandleMessageDogOptionResponse);
	REGISTERMSGHANDLER(MsgImprovePetAdvanceResponse,			MsgMaster::HandleMessageImprovePetAdvanceResponse);
	REGISTERMSGHANDLER(MsgChangePetBestAttrResponse,			MsgMaster::HandleMessageChangePetBestAttrResponse);
	REGISTERMSGHANDLER(MsgSleepPetStateResponse, MsgMaster::HandleMessageSleepPetStateResponse);
	REGISTERMSGHANDLER(MsgBuyEntityMarketThingResponse, MsgMaster::HandleMessageBuyEntityMarketThingResponse);
	REGISTERMSGHANDLER(MsgSetPetPickSettingResponse,	    MsgMaster::HandleMessageSetPetPickSettingResponse);
	REGISTERMSGHANDLER(MsgpetRebornResponse,	MsgMaster::HandleMessagePetRebornResponse);

	REGISTERMSGHANDLER(MsgaddMarketWordsResponse,       MsgMaster::HandleMessageAddMarketWordsResponse);
	REGISTERMSGHANDLER(MsggetMarketWordsResponse,       MsgMaster::HandleMessageGetMarketWordsResponse);
	

	//shop
	REGISTERMSGHANDLER(MsgOpenShopResponse,				MsgMaster::HandleMessageOpenShopResponse);
	REGISTERMSGHANDLER(MsgShopItemListNotify,			MsgMaster::HandleMessageShopItemListNotify);
	REGISTERMSGHANDLER(MsgShopBackBuyNotify,			MsgMaster::HandleMessageShopBackBuyNotify);
	REGISTERMSGHANDLER(MsgShopBackBuyRmvNotify,			MsgMaster::HandleMessageShopBackBuyRmvNotify);
	REGISTERMSGHANDLER(MsgShopBackBuyAddNotify,			MsgMaster::HandleMessageShopBackBuyAddNotify);
	REGISTERMSGHANDLER(MsgShopBackBuyItemResponse,		MsgMaster::HandleMessageShopBackItemResponse);
	REGISTERMSGHANDLER(MsgBuyItemInShopResponse,		MsgMaster::HandleMessageBuyItemInShopResponse);
	REGISTERMSGHANDLER(MsgCloseShopResponse,			MsgMaster::HandleMessageCloseShopResponse);

	//trade
	REGISTERMSGHANDLER(MsgItemTradeOperationNotifiy,			MsgMaster::HandleMessageItemTradeOperationNotifiy);
	REGISTERMSGHANDLER(MsgItemTradeOtherChangeItem,			MsgMaster::HandleMessageItemTradeOtherChangeItem);
	REGISTERMSGHANDLER(MsgItemTradeChangeResponse,			MsgMaster::HandleMessageItemTradeChangeResponse);
	REGISTERMSGHANDLER(MsgItemTradeLockInfo,			MsgMaster::HandleMessageItemTradeLockInfo);
	REGISTERMSGHANDLER(MsgItemTradeOverInfo,			MsgMaster::HandleMessageItemTradeOverInfo);
	REGISTERMSGHANDLER(MsgItemTradeChangeMoney,			MsgMaster::HandleMessageItemTradeChangeMoney);

	//guild
	REGISTERMSGHANDLER(MsgCreateGuildResponse,			MsgMaster::HandleMessageCreateGuildResponse);
	REGISTERMSGHANDLER(MsgGuildsInfoResponse,			MsgMaster::HandleMessageGuildsInfoResponse);
	REGISTERMSGHANDLER(MsgGuildsInfoResponse,			MsgMaster::HandleMessageGuildsInfoResponse);
	REGISTERMSGHANDLER(MsgMyGuildInfoNotify,			MsgMaster::HandleMessageMyGuildInfoNotify);
	REGISTERMSGHANDLER(MsgGuildMemberInfoNotify,			MsgMaster::HandleMessageGuildMemberInfoNotify);
	REGISTERMSGHANDLER(MsgLeaveGuildResponse,			MsgMaster::HandleMessageLeaveGuildResponse);
	REGISTERMSGHANDLER(MsgGuildPlacardChangeResponse, MsgMaster::HandleMessageGuildPlacardChangeResponse);
	REGISTERMSGHANDLER(MsgGuildApplicationInfoNotify,			MsgMaster::HandleMessageGuildApplicationInfoNotify);
	REGISTERMSGHANDLER(MsgGuildApplicationChangeNotify,			MsgMaster::HandleMessageGuildApplicationChangeNotify);
	REGISTERMSGHANDLER(MsgApplicationResultResponse,			MsgMaster::HandleMessageApplicationResultResponse);
	REGISTERMSGHANDLER(MsgGuildMemberInfoByPidResponse,			MsgMaster::HandleMessageGuildMemberInfoByPidResponse);
	REGISTERMSGHANDLER(MsgGuildMoneyUpdateNotify,			MsgMaster::HandleMessageGuildMoneyUpdateNotify);
	REGISTERMSGHANDLER(MsgDeleteGuildMemberResponse,			MsgMaster::HandleMessageDeleteGuildMemberResponse);
	REGISTERMSGHANDLER(MsgGuildRewardResponse,			MsgMaster::HandleMessageGuildRewardResponse);
	REGISTERMSGHANDLER(MsgGuildMasterResetResponse,			MsgMaster::HandleMessageGuildMasterResetResponse);
	REGISTERMSGHANDLER(MsgGuildMemberChangeNotify,			MsgMaster::HandleMessageGuildMemberChangeNotify);
	REGISTERMSGHANDLER(MsgGuildNicknameLoadNotify,			MsgMaster::HandleMessageGuildNicknameLoadNotify);
	REGISTERMSGHANDLER(MsgGuildNicknameUpdateResponse,			MsgMaster::HandleMessageGuildNicknameUpdateResponse);
	REGISTERMSGHANDLER(MsgGuildPlacardNotify,			MsgMaster::HandleMessageGuildPlacardNotify);
	REGISTERMSGHANDLER(MsgGuildPublicNoticeNotify,			MsgMaster::HandleMessageGuildPublicNoticeNotify);
	REGISTERMSGHANDLER(MsgGuildMemberNicknameChangeResponse,			MsgMaster::HandleMessageGuildMemberNicknameChangeResponse);
	REGISTERMSGHANDLER(MsgGuildApplyGCZResponse,			MsgMaster::HandleMessageGuildApplyGCZResponse);
	REGISTERMSGHANDLER(MsgGuildInviteResponse,			MsgMaster::HandleMessageGuildInviteResponse);
	REGISTERMSGHANDLER(MsgGuildInviteResultResponse,			MsgMaster::HandleMessageGuildInviteResultResponse);
	REGISTERMSGHANDLER(MsgGuildInviteNotifyEx,			MsgMaster::HandleMessageGuildInviteNotify);
	REGISTERMSGHANDLER(MsgGuildInviteResultNotify,			MsgMaster::HandleMessageGuildInviteResultNotify);
	REGISTERMSGHANDLER(MsgGuildDonateResponse,			MsgMaster::HandleMessageGuildDonateResponse);
	REGISTERMSGHANDLER(MsgGuildAllMemberInfoResponse,			MsgMaster::HandleMessageGuildAllMemberInfoResponse);
	REGISTERMSGHANDLER(MsgGuildGCZAttackListResponse,			MsgMaster::HandleMessageGuildGCZAttackListResponse);
	REGISTERMSGHANDLER(MsgGuildGCZSetJobResponse,			MsgMaster::HandleMessageGuildGCZSetJobResponse);
	REGISTERMSGHANDLER(MsgGuildGCZGetJobRewardResponse,			MsgMaster::HandleMessageGuildGCZGetJobRewardResponse);
	REGISTERMSGHANDLER(MsgApplicationToGuildResponse,			MsgMaster::HandleMessageApplicationToGuildResponse);
	REGISTERMSGHANDLER(MsgsyncGuildExDataNotify,			MsgMaster::HandleMessageSyncGuildExDataNotify);
	REGISTERMSGHANDLER(MsgGuildAllNicknameNotify,			MsgMaster::HandleMessageGuildAllNicknameNotify);
	REGISTERMSGHANDLER(MsgsyncGuildExStringDataNotify,			MsgMaster::HandleMessageSyncGuildExStringDataNotify);
	REGISTERMSGHANDLER(MsgGuildBuildResponse, MsgMaster::HandleMessageGuildBuildResponse);
	REGISTERMSGHANDLER(MsgGuildFinishBuildingResponse, MsgMaster::HandleMessageGuildFinishBuildingResponse);
	REGISTERMSGHANDLER(MsgSyncGuildBuildingLevelNotify, MsgMaster::HandleMessageSyncGuildBuildingLevelNotify);
	REGISTERMSGHANDLER(MsgGuildGuanGongWorshipResponse, MsgMaster::HandleMessageGuildGuanGongWorshipResponse);
	REGISTERMSGHANDLER(MsgGuildGuanGongAddCountResponse, MsgMaster::HandleMessageGuildGuanGongAddCountResponse);
	REGISTERMSGHANDLER(MsgGuildGuanGongGetRewardResponse, MsgMaster::HandleMessageGuildGuanGongGetRewardResponse);
	REGISTERMSGHANDLER(MsgGuildShopItemBuyResponse, MsgMaster::HandleMessageGuildShopItemBuyResponse);
	REGISTERMSGHANDLER(MsgGuildListVersionNotify, MsgMaster::HandleMessageGuildListVersionNotify);
	REGISTERMSGHANDLER(MsgGuildPublicNoticeChangeResponse, MsgMaster::HandleMessageGuildPublicNoticeChangeResponse);
	REGISTERMSGHANDLER(MsgGuildGetIntDataResponse, MsgMaster::HandleMessageGuildGetIntDataResponse);
	REGISTERMSGHANDLER(MsgGuildGetStringDataResponse, MsgMaster::HandleMessageGuildGetStringDataResponse);
	REGISTERMSGHANDLER(MsgCancelApplicationToGuildResponse, MsgMaster::HandleMessageCancelApplicationToGuildResponse);
	REGISTERMSGHANDLER(MsgGuildExploreInitResponse, MsgMaster::HandleMessageGuildExploreInitResponse);
	REGISTERMSGHANDLER(MsgGuildExploreResponse, MsgMaster::HandleMessageGuildExploreResponse);
	REGISTERMSGHANDLER(MsgGuildOpenBuffResponse, MsgMaster::HandleMessageGuildOpenBuffResponse);
	REGISTERMSGHANDLER(MsgGuildOpenWelfareResponse, MsgMaster::HandleMessageGuildOpenWelfareResponse);
	REGISTERMSGHANDLER(MsgGuildGetWelfareResponse, MsgMaster::HandleMessageGuildGetWelfareResponse);
	REGISTERMSGHANDLER(MsgGuildWelfareStatusResponse, MsgMaster::HandleMessageGuildWelfareStatusResponse);
	REGISTERMSGHANDLER(MsgGuildGczOccupyRewardResponse, MsgMaster::HandleMessageGuildGczOccupyRewardResponse);

	//team
	REGISTERMSGHANDLER(MsgTeamInviteRespose,			MsgMaster::HandleMessageTeamInviteResponse);
	REGISTERMSGHANDLER(MsgTeamJoinRespose,				MsgMaster::HandleMessageTeamJoinResponse);
	REGISTERMSGHANDLER(MsgTeamQuitRespose,				MsgMaster::HandleMessageTeamQuitResponse);
	REGISTERMSGHANDLER(MsgTeamMakeOpration,				MsgMaster::HandleMessageTeamMakeOperation);
	REGISTERMSGHANDLER(MsgTeamMakeOprationReply,		MsgMaster::HandleMessageTeamMakeOperationReply);
	REGISTERMSGHANDLER(MsgTeamMakeDecisionResponse,		MsgMaster::HandleMessageTeamMakeDecisionResponse);
	REGISTERMSGHANDLER(MsgTeamInfoNotify,				MsgMaster::HandleMessageTeamInfoNotify);
	REGISTERMSGHANDLER(MsgTeamInfoUpdNotify,			MsgMaster::HandleMessageTeamInfoUpdNotify);
	REGISTERMSGHANDLER(MsgTeamInfoRmvNotify,			MsgMaster::HandleMessageTeamInfoRmvNotify);
	REGISTERMSGHANDLER(MsgTeamKickPlayerResponse, MsgMaster::HandleMessageTeamKickPlayerResponse);
	REGISTERMSGHANDLER(MsgTeamSetLeaderResponse, MsgMaster::HandleMessageTeamSetLeaderResponse);

	//activity
	REGISTERMSGHANDLER(MsgSyncNotImportantActivityNotify,			MsgMaster::HandleMessageSyncNotImportantActivityNotify);

	REGISTERMSGHANDLER(MsgMobaiDataResponse,			MsgMaster::HandleMessageMobaiDataResponse);
	REGISTERMSGHANDLER(MsgAddMobaiCntResponse,			MsgMaster::HandleMessageAddMobaiCntResponse);
	REGISTERMSGHANDLER(MsgRefreshMobaiPerResponse,		MsgMaster::HandleMessageRefreshMobaiPerResponse);
	REGISTERMSGHANDLER(MsgUpdMyMobaiDataNotify,			MsgMaster::HandleMessageUpdMyMobaiDataNotify);
	REGISTERMSGHANDLER(MsgMobaiBishiResponse,			MsgMaster::HandleMessageMobaiBishiResponse);


	REGISTERMSGHANDLER(MsgUpdCaiShenChuangGuanDataNotify,		MsgMaster::HandleMessageUpdCaiShenChuangGuanDataNotify);
	REGISTERMSGHANDLER(MsgCaiShenChuangGuanDataResponse,		MsgMaster::HandleMessageCaiShenChuangGuanDataResponse);
	REGISTERMSGHANDLER(MsgCaiShenChuangGuanMissionUpNotify,		MsgMaster::HandleMessageCaiShenChuangGuanMissionUp);
	REGISTERMSGHANDLER(MsgCaiShenChuangGuanfreshtimeResponse,			MsgMaster::HandleMessageCaiShenChuangGuanfreshtimeResponse);;
	REGISTERMSGHANDLER(MsgCaiShenChuangGuanCaseOverResponse,		MsgMaster::HandleMessageCaiShenChuangGuanCaseOver);

	REGISTERMSGHANDLER(MsgCaiShenChuangGuanReStartResponse,          MsgMaster::HandleMessageCaiShenChuangGuanRestartResponse);

	REGISTERMSGHANDLER(MsgUpdMeiNvHuSongDataNotify, MsgMaster::HandleMessageUpdMeiNvHuSongDataNotify);
	REGISTERMSGHANDLER(MsgMeiNvHuSongEnterResponse, MsgMaster::HandleMessageMeiNvHuSongEnterResponse);
	REGISTERMSGHANDLER(MsgMeiNvHuSongStartResponse, MsgMaster::HandleMessageMeiNvHuSongStartResponse);
	REGISTERMSGHANDLER(MsgMeiNvHuSongRefreshResponse, MsgMaster::HandleMessageMeiNvHuSongRefreshResponse);

	REGISTERMSGHANDLER(MsgListTreasureResponse,				MsgMaster::HandleMessageListTreasureResponse);
	REGISTERMSGHANDLER(MsgHuntTreasureResponse,				MsgMaster::HandleMessageHuntTreasureResponse);
	REGISTERMSGHANDLER(MsgGetHuntTreasureRewardResponse,	MsgMaster::HandleMessageGetHuntTreasureRewardResponse);
	REGISTERMSGHANDLER(MsgSyncTreasureHuntRecordNotify, MsgMaster::HandleMessageSyncTreasureHuntRecordNotify);

	REGISTERMSGHANDLER(MsgSyncEventStateNotify,	MsgMaster::HandleMessageSyncEventStateNotify);
	REGISTERMSGHANDLER(MsgSyncEventNotFinishCountNotify, MsgMaster::HandleMessageSyncEventNotFinishCountNotify);
	REGISTERMSGHANDLER(MsgSyncActivityBossStateNotify, MsgMaster::HandleMessageSyncActivityBossStateNotify);

	REGISTERMSGHANDLER(MsgSpiderThorwItemResponse,	MsgMaster::HandleMessageSpiderThorwItemResponse);

	REGISTERMSGHANDLER(MsgOpenArenaResponse, MsgMaster::HandleMessageOpenArenaResponse);
	REGISTERMSGHANDLER(MsgArenaListNotify, MsgMaster::HandleMessageArenaListNotify);
	REGISTERMSGHANDLER(MsgRefreshArenaBuffResponse, MsgMaster::HandleMessageRefreshArenaBuffResponse);
	REGISTERMSGHANDLER(MsgArenaFightResponse, MsgMaster::HandleMessageArenaFightResponse);
	REGISTERMSGHANDLER(MsgArenaFightNotify, MsgMaster::HandleMessageArenaFightNotify);
	REGISTERMSGHANDLER(MsgBuyArenaFightCntResponse, MsgMaster::HandleMessageBuyArenaFightCntResponse);
	REGISTERMSGHANDLER(MsgGetPlayerArenaFightRecordResponse, MsgMaster::HandleMessageGetPlayerArenaFightRecordResponse);
	REGISTERMSGHANDLER(MsgGetArenaHeroResponse, MsgMaster::HandleMessageGetArenaHeroResponse);

	REGISTERMSGHANDLER(MsgGetInstanceCntResponse, MsgMaster::HandleMessageGetInstanceCntResponse);

	REGISTERMSGHANDLER(MsgGetGiftByCodeResponse, MsgMaster::HandleMessageGetGiftByCodeResponse);

	REGISTERMSGHANDLER(MsgHideActivityListNotify, MsgMaster::HandleMessageHideActivityListNotify);


	//relationship
	REGISTERMSGHANDLER(MsgRelationListResponse,			MsgMaster::HandleMessageRelationListResponse);
	REGISTERMSGHANDLER(MsgRelationOperateResponse,		MsgMaster::HandleMessageRelationOperateResponse);
	REGISTERMSGHANDLER(MsgRelationFindingResponse,		MsgMaster::HandleMessageRelationFindingResponse);

	//worldData
	REGISTERMSGHANDLER(MsgSyncWorldDataNotify,		MsgMaster::HandleMessageWorldDataNotify);
	REGISTERMSGHANDLER(MsgSyncWorldDataExNotify,	MsgMaster::HandleMessageSyncWorldDataExNotify);
	REGISTERMSGHANDLER(MsgSyncFloatNoticeNotify,	MsgMaster::HandleMessageSyncFloatNoticeNotify);
	REGISTERMSGHANDLER(MsgSyncWorldBossNotify,		MsgMaster::HandleMessageSyncWorldBossNotify);
	REGISTERMSGHANDLER(MsgSyncWorldBeginTimeNotify,	MsgMaster::HandleMessageSyncWorldBeginTimeNotify);
	REGISTERMSGHANDLER(MsgScriptDataResponse,	MsgMaster::HandleMessageScriptDataResponse);
	REGISTERMSGHANDLER(MsgScriptPatchNotify,	MsgMaster::HandleMessageScriptPatchNotify);

	REGISTERMSGHANDLER(MsgGetWorldChartResponse,		MsgMaster::HandleMessageGetWorldChartResponse);
	REGISTERMSGHANDLER(MsgGetWorldChartNotify,		MsgMaster::HandleMessageGetWorldChartNotify);
	REGISTERMSGHANDLER(MsgSyncWorldDataResponse,		MsgMaster::HandleMessageSyncWorldDataResponse);
	REGISTERMSGHANDLER(MsgSyncWorldDataStringResponse,		MsgMaster::HandleMessageSyncWorldDataStringResponse);

	//otherRole
	REGISTERMSGHANDLER(MsgGetOtherPlayerDataResponse, MsgMaster::HandleMessageGetOtherPlayerDataResponse);
	REGISTERMSGHANDLER(MsgSyncOtherPlayerDataNotify, MsgMaster::HandleMessageSyncOtherPlayerDataNotify);
	REGISTERMSGHANDLER(MsgSyncOtherPlayerEquipNotify, MsgMaster::HandleMessageSyncOtherPlayerEquipNotify);

	// download
	REGISTERMSGHANDLER(MsgDownload, MsgMaster::HandleMessageDownload);
	REGISTERMSGHANDLER(MsgDownloadProgress, MsgMaster::HandleMessageDownloadProgress);

	// horse
	REGISTERMSGHANDLER(MsgHorsePeiYangAck, MsgMaster::HandleHorsePeiYangAck);
	REGISTERMSGHANDLER(MsgHorseJinJieAck, MsgMaster::HandleHorseJinJieAck);
	REGISTERMSGHANDLER(MsgHorseEquipQiangHuaAck, MsgMaster::HandleHorseEquipQiangHuaAck);
	REGISTERMSGHANDLER(MsgHorseEquipJinJieAck, MsgMaster::HandleHorseEquipJinJieAck);

	REGISTERMSGHANDLER(MsgSyncEntityRideStateNotify, MsgMaster::HandleSyncEntityRideStateNotify);


	return true;
}