#ifndef	___NET_PROTOCOL___
#define ___NET_PROTOCOL___


namespace NetProtocol
{
//public:
	static const short cReqAuthenticate = 0x7000;
	static const short cResAuthenticate = 0x7001;
	static const short cResAuthenticateResultSucc = 100;
	static const short cResAuthenticateResultErrorSystem = 101;
	static const short cResAuthenticateResultErrorSessionIDError = 102;
	static const short cResAuthenticateResultErrorReqError = 103;
	static const short cResAuthenticateResultErrorAuthTypeError = 104;
	static const short cReqAuthenticateResultErrorSessionTimeOut = 105;

	static const short cNotifyCharacterLoad = 0x7003;

	static const short cReqMapChat = 0x7010;
	static const short cResMapChat = 0x7011;
	static const short cNotifyMapChat = 0x7012;

	static const short cReqPrivateChat = 0x7020;
	static const short cResPrivateChat = 0x7021;
	static const short cNotifyPrivateChat = 0x7022;

	static const short cReqWalk = 0x7030;
	static const short cResWalk = 0x7031;
	static const short cNotifyWalk = 0x7032;

	static const short cReqRun = 0x7040;
	static const short cResRun = 0x7041;
	static const short cNotifyRun = 0x7042;

	static const short cReqNPCTalk = 0x7050;
	static const short cResNPCTalk = 0x7051;

	static const short cReqTurn = 0x7060;
	static const short cResTurn = 0x7061;
	static const short cNotifyTurn = 0x7062;

	static const short cReqAttack = 0x7070;
	static const short cResAttack = 0x7071;
	static const short cNotifyAttack = 0x7072;

	static const short cReqPickUp = 0x7080;
	static const short cResPickUp = 0x7081;

	static const short cReqBagUseItem = 0x7090;
	static const short cResBaguseItem = 0x7091;

	static const short cReqUndressItem = 0x70A0;
	static const short cResUndressItem = 0x70A1;

	static const short cReqItemPositionExchange = 0x70B0;
	static const short cResItemPositionExchange = 0x70B1;

	static const short cReqUseSkill = 0x70C0;
	static const short cResUseSkill = 0x70C1;
	static const short cNotifyUseSkill = 0x70C2;

	static const short cReqNPCShop = 0x70D0;
	static const short cResNPCShop = 0x70D1;

	static const short cReqNPCBuy = 0x70E0;
	static const short cResNPCBuy = 0x70E1;

	static const short cReqCancelTask = 0x70F0;

	static const short cReqForceMove = 0x7100;
	static const short cReqChangeCloth = 0x7110;

	static const short cReqListCharacter = 0x7120;
	static const short cResListCharacter = 0x7121;

	static const short cReqCreateCharacter = 0x7130;
	static const short cResCreateCharacter = 0x7131;

	static const short cReqEnterGame = 0x7140;
	static const short cResEnterGame = 0x7141;

	static const short cReqDeleteCharacter = 0x7150;
	static const short cResDeleteCharacter = 0x7151;

	static const short cReqNPCSell = 0x7160;
	static const short cResNPCSell = 0x7161;

	static const short cReqDestroyItem = 0x7170;
	static const short cResDestroyItem = 0x7171;

	static const short cReqListGuild = 0x7180;
	static const short cResListGuild = 0x7181;

	static const short cReqGetGuildInfo = 0x7190;
	static const short cResGetGuildInfo = 0x7191;

	static const short cReqSaveShortcut = 0x71A0;
	static const short cNotLoadShortcut = 0x71A2;

	static const short cReqCreateGuild = 0x71B0;
	static const short cResCreateGuild = 0x71B1;

	static const short cReqJoinGuild = 0x71C0;
	static const short cResJoinGuild = 0x71C1;

	static const short cReqSetGuildInfo = 0x71D0;
	static const short cResSetGuildInfo = 0x71D1;

	static const short cReqListGuildMember = 0x71E0;
	static const short cResListGuildMember = 0x71E1;

	static const short cReqListGuildEnemy = 0x71F0;
	static const short cResListGuildEnemy = 0x71F1;

	static const short cReqListGuildFriend = 0x7200;
	static const short cResListGuildFriend = 0x7201;

	static const short cReqChangeGuildMemberTitle = 0x7210;
	static const short cReqChangeEnemyGuild = 0x7220;
	static const short cReqChangeFriendGuild = 0x7230;

	static const short cReqGuildChat = 0x7240;
	static const short cResGuildChat = 0x7241;
	static const short cNotifyGuildChat = 0x7242;

	static const short cReqChangeAttackMode = 0x7250;
	static const short cResChangeAttackMode = 0x7251;

	static const short cReqVcoinShopList = 0x7260;
	static const short cResVcoinShopList = 0x7261;

	static const short cReqNPCRepair = 0x7280;
	static const short cResNPCRepair = 0x7281;

	static const short cReqRelive = 0x7290;
	static const short cResRelive = 0x7291;

	static const short cReqTaskDesp = 0x7300;
	static const short cResTaskDesp = 0x7301;

	static const short cReqInfoPlayer = 0x7310;
	static const short cResInfoPlayer = 0x7311;

	static const short cReqCreateTeam = 0x7320;
	static const short cResCreateTeam = 0x7321;

	static const short cReqLeaveTeam = 0x7330;
	static const short cResLeaveTeam = 0x7331;

	static const short cReqJoinTeam = 0x7340;
	static const short cResJoinTeam = 0x7341;

	static const short cReqAgreeJoinTeam = 0x7350;
	static const short cResAgreeJoinTeam = 0x7351;

	static const short cReqInviteTeam = 0x7360;
	static const short cResInviteTeam = 0x7361;

	static const short cReqAgreeInviteTeam = 0x7370;
	static const short cResAgreeInviteTeam = 0x7371;

	static const short cReqTaskClick = 0x7380;

	static const short cReqTeamChat = 0x7390;
	static const short cResTeamChat = 0x7391;

	static const short cReqNormalChat = 0x7400;
	static const short cResNormalChat = 0x7401;

	static const short cReqTradeInvite = 0x7410;

	static const short cReqAgreeTradeInvite = 0x7420;

	static const short cReqCloseTrade = 0x7430;

	static const short cReqTradeAddGameMoney = 0x7440;

	static const short cReqTradeAddVcoin = 0x7450;

	static const short cReqTradeSubmit = 0x7460;

	static const short cReqTeamSetLeader = 0x7470;

	static const short cReqTradeAddItem = 0x7480;

	static const short cReqDestoryItem = 0x7490;

	static const short cReqSortItem = 0x7500;

	static const short cReqItemTalk = 0x7510;

	static const short cReqMergeSteel = 0x7520;
	static const short cResMergeSteel = 0x7521;

	static const short cReqUpgradeEquip = 0x7530;
	static const short cResUpgradeEquip = 0x7531;

	static const short cReqWorldChat = 0x7540;
	static const short cResWorldChat = 0x7541;

	static const short cReqFreshVcoin = 0x7550;

	static const short cReqLeaveGuild = 0x7560;

	static const short cReqAddDepotSlot = 0x7570;

	static const short cReqTeamPickMode = 0x7580;

	static const short cReqSwithSlaveAIMode = 0x7590;

	static const short cReqAddBagSlot = 0x75A0;

	static const short cReqPing = 0x7600;
	static const short cResPing = 0x7601;

	static const short cReqFreshHPMP = 0x7610;

	static const short cReqUpdateTicket = 0x7620;
	static const short cResUpdateTicket = 0x7621;

	static const short cReqUpdateChinaLimit = 0x7630;

	static const short cReqBuyOfflineExp = 0x7640;

	static const short cReqSteelEquip = 0x7650;

	static const short cReqPlayerTalk = 0x7660;

	static const short cReqGetChartInfo = 0x7670;
	static const short cResGetChartInfo = 0x7671;

	static const short cReqInfoItemExchange = 0x7680;
	static const short cResInfoItemExchange = 0x7681;

	static const short cReqItemExchange = 0x7690;
	static const short cResItemExchange = 0x7691;

	static const short cReqGetItemDesp = 0x7700;
	//zhel
	static const short cReqHornChat = 0x7710;
	static const short cResHornChat = 0x7711;
	static const short cNotifyHornChat = 0x7712;

	static const short cCountDownFinish = 0x7720;

	static const short cReqFriendChange = 0x7730;
	static const short cResFriendChange = 0x7731;

	static const short cReqFriendFresh = 0x7740;
	static const short cResFriendFresh = 0x7741;

	static const short cReqEquipReRandAdd = 0x7750;
	static const short cResEquipReRandAdd = 0x7751;

	static const short cReqEquipExchangeUpgrade = 0x7760;
	static const short cResEquipExchangeUpgrade = 0x7761;

	static const short cReqServerScript = 0x7770;

	static const short cReqOpenRong = 0x7780;

	static const short cReqProtectItem = 0x7790;
	static const short cResProtectItem = 0x7791;

	static const short cReqTeamKickMember = 0x7800;

	static const short cReqFreshGift = 0x7810;

	static const short cReqMergeEquip = 0x7820;

	static const short cReqOpenAchieve = 0x7850;

	static const short cReqDirectFly = 0x7860;

	static const short cReqMarryInvite = 0x7870;
	static const short cNotifyMarryInvite = 0x7872;
	static const short cReqAgreeOrNotMarryInvite = 0x7880;
	static const short cReqDivorceInvite = 0x7890;
	static const short cReqAgreeOrNotDivorceInvite = 0x7900;
	static const short cReqConsign = 0x7901;
	static const short cResConsignLIst = 0x7902;
	static const short cReqSetConsign = 0x7904;
	static const short cReqConsignBuy = 0x7905;
	static const short cReqCancelConsign = 0x7906;
	static const short cReqCollectStart = 0x7874;
	static const short cReqCollectEnd = 0x7876;

	static const short cReqOpenChinaPKlimit = 0x7910;
	static const short cReqLotteryList = 0x7911;
	static const short cReqLotteryTimes = 0x7912;
	static const short cReqLotterydepot_To_Bag = 0x7913;
	static const short cReqGetItemAll_From_LotteryDepot = 0x7914;

	static const short cReqSetSecondPassword = 0x7920;
	static const short cResSetSecondPassword = 0x7921;

	static const short cReqLoginFormAward = 0x7930;

	static const short cReqOnSaleList = 0x7940;
	static const short cResOnSaleList = 0x7941;

	static const short cReqBuyOnSaleItem = 0x7950;

	static const short cReqPutOnSaleItem = 0x7960;

	static const short cReqUpLevelXinfa = 0x7970;
	static const short cReqOpenXinfa = 0x7971;

	static const short cNotifyMapEnter = 0x7F00;
	static const short cNotifyMapMeet = 0x7F01;
	static const short cNotifyMapLeave = 0x7F02;
	static const short cNotifyMapBye = 0x7F03;
	static const short cNotifyInjury = 0x7F04;
	static const short cNotifyDie = 0x7F05;
	static const short cNotifyItemChange = 0x7F06;
	static const short cNotifyAvatarChange = 0x7F07;
	static const short cNotifySkillChange = 0x7F08;
	static const short cNotifyAttributeChange = 0x7F09;
	static const short cNotifyGameMoneyChange = 0x7F10;
	static const short cNotifyHPMPChange = 0x7F11;
	static const short cNotifyTaskChange = 0x7F12;
	static const short cNotifyExpChange = 0x7F13;
	static const short cNotifyLevelChange = 0x7F14;
	static const short cNotifyForceMove = 0x7F15;
	static const short cNotifyItemDesp = 0x7F17;
	static const short cNotifyGuildInfo = 0x7F18;
	static const short cNotifyGhostGuildInfo = 0x7F19;
	static const short cNotifyGhostMode = 0x7F20;
	static const short cNotifyAlert = 0x7F21;
	static const short cNotifyRelive = 0x7F22;
	static const short cNotifyTeamInfoChange = 0x7F23;
	static const short cNotifyTeamState = 0x7F24;
	static const short cNotifyTeamInfo = 0x7F25;
	static const short cNotifySkillDesp = 0x7F26;
	static const short cNotifyYouKeSessionID = 0x7F27;
	static const short cNotifyMapConn = 0x7F28;
	static const short cNotifyMapSafeArea = 0x7F29;
	static const short cNotifyNpcShowFlags = 0x7F30;
	static const short cNotifyJoinTeamToLeader = 0x7F31;
	static const short cNotifyInviteTeamToMember = 0x7F32;
	static const short cNotifyFindRoadGotoNotify = 0x7F33;
	static const short cNotifyTeamChat = 0x7F34;
	static const short cNotifyNoramlChat = 0x7F35;
	static const short cNotifyTradeInvite = 0x7F36;
	static const short cNotifyTradeInfo = 0x7F37;
	static const short cNotifyTradeItemChange = 0x7F38;
	static const short cNotifyMapItemOwner = 0x7F39;
	static const short cNotifyPKStateChange = 0x7F40;
	static const short cNotifyMonsterAddInfo = 0x7F41;
	static const short cNotifyStatusChange = 0x7F42;
	static const short cNotifyItemTalk = 0x7F43;
	static const short cNotifyPlayerAddInfo = 0x7F44;
	static const short cNotifyCountDown = 0x7F45;
	static const short cNotifyMiniMapConn = 0x7F46;
	static const short cNotifyPlayEffect = 0x7F47;
	static const short cNotifyGameParam = 0x7F48;
	static const short cNotifyInfoItemChange = 0x7F49;
	static const short cNotifyWorldChat = 0x7F50;
	static const short cNotifySessionClosed = 0x7F51;
	static const short cNotifySessionDelayReauth = 0x7F52;
	static const short cNotifyWarInfo = 0x7F53;
	static const short cNotifyMapOption = 0x7F54;
	static const short cNotifyGuildCondition = 0x7F55;
	static const short cNotifySlotAdd = 0x7F56;
	static const short cNotifyNameAdd = 0x7F57;
	static const short cNotifyURL = 0x7F58;
	static const short cNotifyFreeReliveLevel = 0x7F59;
	static const short cNotifyGUIShowTag = 0x7F60;
	static const short cNotifySetModel = 0x7F61;
	static const short cNotifyChinaLimitLv = 0x7F62;
	static const short cNotifyMonsterChat = 0x7F63;
	static const short cNotifyMapMiniNpc = 0x7F64;
	static const short cNotifyOfflineExpInfo = 0x7F65;
	static const short cNotifyPlayerTalk = 0x7F67;
	static const short cNotifyProsperityChange = 0x7F68;
	static const short cNotifyGUIOpenPanel = 0x7F69;
	static const short cNotifyBlackBoard = 0x7F70;
	static const short cNotifyListGuildBegin = 0x7F71;
	static const short cNotifyListGuildEnd = 0x7F72;
	static const short cNotifyListGuildItem = 0x7F73;
	static const short cNotifyItemPlusDesp = 0x7F74;
	static const short cNotifyHighFocus = 0x7F75;
	static const short cNotifyGuiShowMergeEquip = 0x7F76;
	static const short cNotifyListTalkList = 0x7F77;
	static const short cNotifyListTalkContent = 0x7F78;
	static const short cNotifyListTalkTitle = 0x7F79;
	static const short cNotifyAchieveDone = 0x7F80;
	static const short cNotifyFreeDirectFly = 0x7F81;
	static const short cNotifyGotoEnd = 0x7F82;
	static const short cNotifyEnterMarryInvite = 0x7F83;
	static const short cNotifyDivorceInvite = 0x7F84;
	static const short cNotifyMarrySuc = 0x7F85;
	static const short cNotifySlave = 0x7F86;
	static const short cNotifyGiftList = 0x7F87;
	static const short cNotifyAward = 0x7F88;
	static const short cNotifyLotteryList = 0x7F89;
	static const short cNotifyLotteryTimesList = 0x7F90;
	static const short cNotifyOnSaleItemChange = 0x7F91;
	static const short cNotifyXinFaList = 0x7F92;
	static const short cNotifyXinFaData = 0x7F93;

	static const short cResConnectServer = 0x1000; //one short:success=0,failed=!0.
};


#endif //___NET_PROTOCOL___