----------------------------------------------------------
-- noteType，addNote
--

attr_type_to_name = {
	[1] = "生命上限",
	[2] = "魔法上限",
	[3] = "当前生命",
	[4] = "当前魔法",
	[5] = "物理攻击",
	[6] = "最大物理攻击",
	[7] = "魔法攻击",
	[8] = "最大魔法攻击",
	[9] = "道术攻击",
	[10] = "最大道术攻击",
	[11] = "物理防御",
	[12] = "最大物理防御",
	[13] = "魔法防御",
	[14] = "最大魔法防御",
	[15] = "生命恢复",
	[16] = "魔法恢复",
	[17] = "准确",
	[18] = "敏捷",
	[19] = "魔法命中",
	[20] = "魔法闪避",
	[21] = "毒物闪避",
	[22] = "毒物恢复",
	[23] = "增加麻痹几率",
	[24] = "死亡恢复",
	[25] = "幸运",
	[26] = "诅咒",
	[27] = "神圣",
	[28] = "魔法值抵消伤害",
	[29]="移速",
	[30]="攻速",
	[31]="穿透",
	[32]="暴击",
	[33]="防爆",
	[34]="反弹",
	[35]="Buff持续时间增加",
	[36]="吸血",
	[37]="吸蓝",
	[38]="处决",
	
	
	[40]="生命上限%",
	[41]="魔法上限%",
	[51]="魂石最大物理防御%",
	[53]="魂石最大魔法防御%",
	[700]="经验玉",
	[701]="杀怪经验额外",
	[705]="基础怪物金币掉落",
	[710]="特殊攻击",
	[730]="对玩家造成伤害",
	[800]="道士毒",
}

fm_attr_type_to_name = {
	[1] = "生命上限",
	[2] = "魔法上限",
	[3] = "当前生命",
	[4] = "当前魔法",
	[5] = "最小物理攻击",
	[6] = "最大物理攻击",
	[7] = "最小魔法攻击",
	[8] = "最大魔法攻击",
	[9] = "最小道术攻击",
	[10] = "最大道术攻击",
	[11] = "最小物理防御",
	[12] = "最大物理防御",
	[13] = "最小魔法防御",
	[14] = "最大魔法防御",
	[15] = "生命恢复",
	[16] = "魔法恢复",
	[17] = "准确",
	[18] = "敏捷",
	[19] = "魔法命中",
	[20] = "魔法闪避",
	[21] = "毒物闪避",
	[22] = "毒物恢复",
	[23] = "增加麻痹几率",
	[24] = "死亡恢复",
	[25] = "幸运",
	[26] = "诅咒",
	[27] = "神圣",
	[28] = "魔法值抵消伤害",
	[29]="移速",
	[30]="攻速",
	[31]="穿透",
	[32]="暴击",
	[33]="防爆",
	[34]="反弹",
	[35]="Buff持续时间增加",
	[36]="吸血",
	[37]="吸蓝",
	[38]="处决",
	
	
	[40]="生命上限%",
	[41]="魔法上限%",
	[51]="魂石最大物理防御%",
	[53]="魂石最大魔法防御%",
	[700]="经验玉",
	[701]="杀怪经验额外",
	[705]="基础怪物金币掉落",
	[710]="特殊攻击",
	[730]="对玩家造成伤害",
	[800]="道士毒",
}

local noteType = {
	DEBUG = 0,
	NORMAL = 1,
	TRIVIAL = 2,
	NORMAL_RED = 3,
	TRIVIAL_RED = 4,
	TOP = 5,
}

local addNote = function(note, ntType)
	ntType = ntType or noteType.NORMAL
	if note then
		cpnotification.addNote(note, ntType)
	end
end
-----------------------------------------------------------
--[[
namespace Error
{
	enum
	{
		Success			= 0,

		//
		//	General Error 1-99
		Unknown					=1,
		Script					=2,


		InvalidParam				=10,
		InvalidEntity				=11,
		InvalidCate				=12,
		InvalidType				=13,
		InvalidItem				=14,
		InvalidMgr				=15,
		InvalidScene				=16,
		InvalidStaticID				=17,
		InvalidStaticData			=18,

		NotEnoughEnhanceLevel		=21,
		NotEnoughLevel				=22,
		NotEnoughScrap				=23,
		NotEnoughItem				=24,
		NotEnoughSoul				=25,
		NotEnoughPower				=27,
		NotEnoughEquivalent		= 30,
		NotEnoughReq			= 31,
		NotEnoughMoney			= 32,
		NotEnoughGold			= 33,
		NotEnoughDiamond		= 34,
		NotEnoughReputation		= 35,
		NotEnoughHonor			= 36,
		NotEnoughBeauty			= 37,
		NotEnoughIntergration	= 38,
		NotEquip				= 39,

		StillInCD				=40,
		UpToLimit				=41,

		CanNotRemove				=50,
		CanNotReplace				=51,
		CanNotSameItem			=60,


		BoothDownSuccess		=95,  //下架成功
		BoothUpSuccess			=96,  //上架成功
		MarketSuccess			=97,  //摆摊成功
		ItemSuccess				=98,
		ItemFaild				=99,
	}

	enum EntityError
	{
		//
		//	Entity Error  100- 199
		RoleTooMuch		=	100,
		PetTooMuch		=	101,
		DogTooMuch		=	102,
		ItemTooMuch		=	103,

		MarketisOpen	=	110,
		MarketNotOpen	=	111,
		MarketNoItem	=   112,

		PetnotSleep		=	120,
		PetnotDead		=	121,
		PetnotOn		=	122,
	};

	enum ItemErrorCode
	{
		//
		//	Item   Error 200-299
		NotSuchSlot				= 200,

		Item_BagisFull				=204,
		Item_SuccessBagFull			=205,
		Item_AlreadyInlay			=215,
		Item_NoMatchClass = 216,
		Item_NoMatchGender = 217,

		Item_DestinationNotFound		=220,
	//	Item_PlayerLvlNotEnough			=221,


		Item_CDLocked				=226,
		Item_NotEnoughSlot			=227,
		Item_PlayerTypeErr			=228,

		Item_CanNotSell				=230,
		Item_CanNotDelete			=231,
		Item_CanNotMerge				=232,
		Item_CanNotForge				=233,

		Item_CanNotModifSysTime			=234,
		Item_CanNotBuy				=235,

		Item_CanNotUseOnMainRole		=236,
		Item_CanNotUseOnSubRole			=237,
		Item_SubRoleLvlLarger			=238,

		Item_InheritSlotCntErr			=239,
		Item_InheritNotEnough			=240,

		Item_MaxLvl					=241,
		Item_VipNotEnought			=242,

		Item_Failed					=243,

		Item_Same_Position			=250,

		Item_UnlockReqNotEnough		=260,
	};

	enum CombatErrorCode
	{
		//
		//	Combat Error 300-399
		Combat_Failed		= 300,
		Combat_OutOfMana	= 301,
		Combat_NotInRange	= 302,
		Combat_InvalidSkill	= 303,
		Combat_InCoolDown	= 305,
		Combat_PlayerIsDaze = 306,


		Combat_Skill_duplicate  = 310,
		Combat_Skill_LevelNotEnough = 311,
	};

	enum SceneErrorCode
	{
		//
		//	Scene Error  400-499
		NotInRegion		= 401,

		TeamMemberNotNear	= 410,
		TooManyTimes		= 411,
		EntranceClosed		= 412,

		Scene_Not_Allow		= 413,

		Scene_Not_Finish	= 414,

		Scene_Peace_Area	= 415,
	};

	enum
	{
	//	Quest Error  500-599
		InvalidQuestID		= 500,
		InvalidQuestState	= 501,
	};
}
--]]
-- 这个表的key代表errcode，source和target分别是event的来源和目标，返回值是提示信息和提示类型。
local getErrorMsg = {
	[0] = function(source, target)
		local note = ""
		local nType = noteType.NORMAL
		if source == "HandleMessageLoginResponse" then
			note = "登录成功！"
			nType = noteType.NORMAL
		elseif source == "ProposalRequestSent" then
			note = "求婚请求已发送，等待对方回应！"
			nType = noteType.NORMAL
		elseif source == "" then
		end
		return note, nType
	end,
	[1] = function(source, target)
		return "未知错误!", noteType.NORMAL
	end,
	[2] = function(source, target)
		return "脚本错误!", noteType.NORMAL
	end,
	[3] = function(source, target)
		return "功能尚未实现!", noteType.NORMAL
	end,
	[4] = function(source, target)
		return "目标不在线!", noteType.NORMAL
	end,
	[5] = function(source, target)
		return "该名字已存在!", noteType.NORMAL
	end,
	[6] = function(source, target)
		return "密码错误!", noteType.NORMAL
	end,
	[7] = function(source, target)
		return "账号不存在!", noteType.NORMAL
	end,
	[8] = function(source, target)
		return "账号已被封禁!", noteType.NORMAL
	end,
    [9] = function(source, target)
		return "登入失败!", noteType.NORMAL
	end,

	[10] = function(source, target)
		return "无效参数!", noteType.NORMAL
	end,
	[11] = function(source, target)
		--return "无效的实体!", noteType.NORMAL
		return "", noteType.NORMAL
	end,
	[12] = function(source, target)
		return "无效的消息分类!", noteType.NORMAL
	end,
	[13] = function(source, target)
		return "无效的消息类型!", noteType.NORMAL
	end,
	[14] = function(source, target)
		return "无效的物品!", noteType.NORMAL
	end,
	[15] = function(source, target)
		return "无效的管理器!", noteType.NORMAL
	end,
	[16] = function(source, target)
		return "无效的场景!", noteType.NORMAL
	end,
	[17] = function(source, target)
		return "无效的静态数据!", noteType.NORMAL
	end,
	[18] = function(source, target)
		return "无效的静态数据!", noteType.NORMAL
	end,
	[19] = function(source, target)
		return "无效的物品管理器!", noteType.NORMAL
	end,

	[20] = function(source, target)
		return "你的条件不满足!", noteType.NORMAL
	end,
	[22] = function(source, target)
		return "你的等级不够!", noteType.NORMAL
	end,

	[24] = function(source, target)
		return "缺少必须的物品!", noteType.NORMAL
	end,

	[25] = function(source, target)
		return "你的灵魂不足!", noteType.NORMAL
	end,

	[27] = function(source, target)
		return "你的战力不足!", noteType.NORMAL
	end,

	[28] = function(source, target)
		return "你的积分不够!", noteType.NORMAL
	end,

	[29] = function(source, target)
		return "你的转生等级不够!", noteType.NORMAL
	end,

	[31] = function(source, target)
		return "你的材料不足!", noteType.NORMAL
	end,

	[32] = function(source, target)
		return "你的金币不足!", noteType.NORMAL
	end,

	[33] = function(source, target)
		return "你的元宝不足!", noteType.NORMAL
	end,

	[34] = function(source, target)
		return "你的仙玉不足!", noteType.NORMAL--仙玉
	end,

	[36] = function(source, target)
		return "你的荣誉不足!", noteType.NORMAL
	end,

	[39] = function(source, target)
		return "请放入装备!", noteType.NORMAL
	end,

	[40] = function(source, target)
		return "天数不足", noteType.NORMAL
	end,

	[41] = function(source, target)
		return "宠物等级不足", noteType.NORMAL
	end,

	[42] = function(source, target)
		return "魂石评分不足", noteType.NORMAL
	end,

	[43] = function(source, target)
		return "转生灵魄不足", noteType.NORMAL
	end,

	[44] = function(source, target)
		return "功能尚未开启", noteType.NORMAL
	end,

	[45] = function(source, target)
		return "没有学习此技能!", noteType.NORMAL
	end,

	[46] = function(source, target)
		return "背包里没有战神油!", noteType.NORMAL
	end,

	[49] = function(source, target)
		return "已经使用过了!", noteType.NORMAL
	end,
	[50] = function(source, target)
		return "冷却中!", noteType.NORMAL
	end,
	[51] = function(source, target)
		return "已到上限!", noteType.NORMAL
	end,
	[52] = function(source, target)
		return "人物等级达到上限!", noteType.NORMAL
	end,

	[53] = function(source, target)
		return "已经领取！", noteType.NORMAL
	end,
	[54] = function(source, target)
		return "活动尚未结束！", noteType.NORMAL
	end,

	[55] = function(source, target)
		return "已经被领取完！", noteType.NORMAL
	end,

	[56] = function(source, target)
		return "领取成功！", noteType.NORMAL
	end,

	[57] = function(source, target)
		return "已经设置过！", noteType.NORMAL
	end,
	[58] = function(source, target)
		return "已经过期！", noteType.NORMAL
	end,
	[61] = function(source, target)
		return "材料无法用元宝代替!", noteType.NORMAL
	end,

	[62] = function(source, target)
		return "不能放入同一件装备!", noteType.NORMAL
	end,

	[63] = function(source, target)
		return "替换的足迹已是同阶!", noteType.NORMAL
	end,

	[72] = function(source, target)
		return "当前场景没有怪物，无法自动战斗!", noteType.NORMAL
	end,

	[70] = function(source, target)
		return "伴侣必须为异性!", noteType.NORMAL
	end,

	[73] = function(source, target)
		return "您还不是城主!", noteType.NORMAL
	end,

	[75] = function(source, target)
		return "快捷键设置已满!", noteType.NORMAL
	end,

	[76] = function(source, target)
		return "你没有这个礼包！", noteType.NORMAL
	end,

	[80] = function(source, target)
		return "内容含有敏感词，请重新输入！", noteType.NORMAL
	end,

	[81] = function(source, target)
		return "内容含有不支持字符，请重新输入！", noteType.NORMAL
	end,

	[82] = function(source, target)
		return "名称中不能含有空白字符，请重新输入！", noteType.NORMAL
	end,

	[85] = function(source, target)
		return "不能对自己进行此操作！", noteType.NORMAL
	end,

	[90] = function(source, target, data1, data2, data3)
		return "功能暂未开放！", noteType.NORMAL
	end,
	[91] = function(source, target, data1, data2, data3)
		return "服务器已满！", noteType.NORMAL
	end,

	[95] = function(source, target, data1, data2, data3)
		return "该帐号在别处登录，您已被迫下线。", noteType.NORMAL_RED
	end,

	[96] = function(source, target)
		return "等级不够boss等级，前去太危险，\n不能传送", noteType.NORMAL
	end,

	[97] = function(source, target)
		return "跨服中不能进行此操作", noteType.NORMAL
	end,

	[100] = function(source, target)
		return "您的角色已达上限!", noteType.NORMAL
	end,
	[101] = function(source, target)
		return "您的宠物已达上限!", noteType.NORMAL
	end,
	[102] = function(source, target)
		return "您的神兽已达上限!", noteType.NORMAL
	end,
	[103] = function(source, target)
		return "你的物品已达上限!", noteType.NORMAL
	end,

	[104] = function(source, target)
		return "你不在行会中！", noteType.NORMAL
	end,

	[105] = function(source, target)
		return "你不在队伍中！", noteType.NORMAL
	end,

	[106] = function(source, target)
		return "该玩家不在线！", noteType.NORMAL
	end,

	[107] = function(source, target)
		return "您还没有召唤兽！", noteType.NORMAL
	end,

	[108] = function(source, target)
		return "没有足够的VIP等级！", noteType.NORMAL
	end,

	[109] = function(source, target)
		return "没有足够的次数！", noteType.NORMAL
	end,

	[110] = function(source, target)
		return "你已经在摆摊!", noteType.NORMAL
	end,
	[111] = function(source, target)
		return "你摊位为开启!", noteType.NORMAL
	end,
	[112] = function(source, target)
		return "目标摊位没有物品!", noteType.NORMAL
	end,
	[113] = function(source, target)
		return "你不能购买你自己的东西!", noteType.NORMAL
	end,

	[120] = function(source, target)
		return "宠物没有在休息!", noteType.NORMAL
	end,
	[121] = function(source, target)
		return "宠物没有死亡!", noteType.NORMAL
	end,
	[122] = function(source, target)
		return "宠物在休息中!", noteType.NORMAL
	end,
	[123] = function(source, target)
		return "宠物不在休息状态,不能封印!", noteType.NORMAL
	end,
	[124] = function(source, target)
		return "宠物需要开光!", noteType.NORMAL
	end,
	[125] = function(source, target)
		return "没有可以提升的进阶属性!", noteType.NORMAL
	end,
	[126] = function(source, target)
		return "没有可以替换的极品属性!", noteType.NORMAL
	end,
	[127] = function(source, target)
		return "有进阶属性已经达到最大值!", noteType.NORMAL
	end,
	[128] = function(source, target)
		return "宠物数量不足！", noteType.NORMAL
	end,
	[130] = function(source, target)
		return "目标已死亡!", noteType.NORMAL
	end,
	[131] = function(source, target)
		return "目标未死亡!", noteType.NORMAL
	end,
	[132] = function(source, target)
		return "不允许复活!", noteType.NORMAL
	end,

	[133] = function(source, target)
		return "玩家不在线。", noteType.NORMAL
	end,

	[134] = function(source, target)
		return "您已经被禁止发言!", noteType.NORMAL
	end,

	[135] = function(source, target)
		return "说话速率过快，请休息一下", noteType.NORMAL
	end,

	[136] = function(source, target)
		return "你张了张嘴，什么也没说...", noteType.NORMAL
	end,

	[137] = function(source, target)
		return "您的身上没有装备合成物品!...", noteType.NORMAL
	end,

	[140] = function(source, target)
		return "冷却类型无效!", noteType.NORMAL
	end,
	[141] = function(source, target)
		return "冷却已清除!", noteType.NORMAL
	end,
	[142] = function(source, target)
		return "还在冷却中!", noteType.NORMAL
	end,
	[143] = function(source, target)
		return "无需消除冷却!", noteType.NORMAL
	end,
	[150] = function(source, target)
		return "你已领取该奖励!", noteType.NORMAL
	end,
	[151] = function(source, target)
		return "没有可领取的奖励!", noteType.NORMAL
	end,

	[160] = function(source, target)
		return "充值额度不足!", noteType.NORMAL
	end,

	[161] = function(source, target)
		return "背包格子已达到上限!", noteType.NORMAL
	end,

	[162] = function(source, target)
		return "30秒内只能叫卖一次!", noteType.NORMAL
	end,

	[163] = function(source, target)
		return "3秒内只能操作一次!", noteType.NORMAL
	end,

	[164] = function(source, target)
		return "30秒内只能留言一次!", noteType.NORMAL
	end,

	[165] = function(source, target)
		return "10秒之内只能抽奖一次!", noteType.NORMAL
	end,

	[170] = function(source, target)
		return "已达上限!", noteType.NORMAL
	end,

	[175] = function(source, target)
		return "该称号已经佩戴!", noteType.NORMAL
	end,

	[176] = function(source, target)
		return "该称号已经取消佩戴!", noteType.NORMAL
	end,

	[177] = function(source, target)
		return "未拥有该称号!", noteType.NORMAL
	end,

	[178] = function(source, target)
		return "已拥有该称号!", noteType.NORMAL
	end,

	[179] = function(source, target)
		return "摆摊类型限制!", noteType.NORMAL
	end,

	[180] = function(source, target)
		return "没有离线经验!", noteType.NORMAL
	end,
	[181] = function(source, target)
		return "坐骑没有开放!", noteType.NORMAL
	end,

	[182] = function(source, target)
		return "坐骑已到顶级!", noteType.NORMAL
	end,

	[183] = function(source, target)
		return "坐骑经验条已满!", noteType.NORMAL
	end,

	[184] = function(source, target)
		return "无效的坐骑培养类型!", noteType.NORMAL
	end,

	[185] = function(source, target)
		return "坐骑装备未开放!", noteType.NORMAL
	end,

	[186] = function(source, target)
		return "坐骑装备已到顶级!", noteType.NORMAL
	end,
	
	[187] = function(source, target)
		return "坐骑装备经验条已满!", noteType.NORMAL
	end,
	
	[188] = function(source, target)
		return "当前状态下,不能上马!", noteType.NORMAL
	end,
	
	[189] = function(source, target)
		return "坐骑经验条未满!", noteType.NORMAL
	end,
	
	[190] = function(source, target)
		return "坐骑装备经验条未满!", noteType.NORMAL
	end,
	
	[191] = function(source, target)
		return "无效的坐骑装备!", noteType.NORMAL
	end,
	[200] = function(source, target)
		return "槽位不够!", noteType.NORMAL
	end,

	[204] = function(source, target)
		return "背包空格不够!", noteType.NORMAL
	end,

	[216] = function(source, target)
		return "你的职业不合适!", noteType.NORMAL
	end,
	[217] = function(source, target)
		return "你的性别不合适!", noteType.NORMAL
	end,
	[220] = function(source, target)
		return "目标没有找到!", noteType.NORMAL
	end,

	[226] = function(source, target)
		return "正在冷却中!", noteType.NORMAL
	end,
	[227] = function(source, target)
		return "不能再放入此类魂石!", noteType.NORMAL
	end,

	[229] = function(source, target)
		return "", noteType.NORMAL
	end,

	[230] = function(source, target)
		return "物品不能出售!", noteType.NORMAL
	end,

	[231] = function(source, target)
		return "物品不能删除!", noteType.NORMAL
	end,

	[232] = function(source, target)
		return "物品不能合成!", noteType.NORMAL
	end,

	[244] = function(source, target)
		return "材料无法用元宝代替!", noteType.NORMAL
	end,

	[245] = function(source, target)
		return "装备耐久不够!", noteType.NORMAL
	end,

	[246] = function(source, target)
		return "该物品无法丢弃!", noteType.NORMAL
	end,

	[247] = function(source, target)
		return "该物品无法交易!", noteType.NORMAL
	end,

	[248] = function(source, target)
		return "该物品无法摆摊!", noteType.NORMAL
	end,

	[251] = function(source, target)
		return "背包已满!", noteType.NORMAL
	end,

	[252] = function(source, target)
		return "宠物背包已满!", noteType.NORMAL
	end,

	[253] = function(source, target)
		return "仓库背包已满!", noteType.NORMAL
	end,

	[254] = function(source, target)
		return "摆摊物品已满!", noteType.NORMAL
	end,

	[260] = function(source, target)
		return "背包解锁材料或元宝不足!", noteType.NORMAL
	end,

	[262] = function(source, target)
		return "物品已达到转生上限!", noteType.NORMAL
	end,

	[216] = function(source, target)
		return "职业不符，无法装备!", noteType.NORMAL
	end,

	[217] = function(source, target)
		return "性别不符，无法装备!", noteType.NORMAL
	end,

	[241] = function(source, target)
		return "装备已达到最高级!", noteType.NORMAL
	end,

	[243] = function(source, target)
		return "该物品无法这样操作!", noteType.NORMAL
	end,

	[249] = function(source, target)
		return "该物品无法使用!", noteType.NORMAL
	end,

	[250] = function(source, target)
		return "不能将物品调换到原来的位置！",noteType.NORMAL
	end,
	[251] = function(source, target)
		return "玩家背包已满！",noteType.NORMAL
	end,
	[252] = function(source, target)
		return "宠物背包已满！",noteType.NORMAL
	end,
	[253] = function(source, target)
		return "寻宝仓库已满！",noteType.NORMAL
	end,
	[254] = function(source, target)
		return "摊位已满！",noteType.NORMAL
	end,
	[255] = function(source, target)
		return "仓库已满！",noteType.NORMAL
	end,

	[260] = function(source, target)
		return "背包扩展符或元宝数量不足!", noteType.NORMAL
	end,

	[261] = function(source, target)
		return "强化等级不够!", noteType.NORMAL
	end,

	[265] = function(source, target)
		return "经验玉经验未满，不可使用！", noteType.NORMAL
	end,

	[266] = function(source, target)
		return "物品未消耗耐久，不需要修理！", noteType.NORMAL
	end,


	[280] = function(source, target)
		local sid=tonumber(target)
		local eu=gdItems[sid]
		if	eu then
			local name=eu.name
			return "获得"..name, noteType.NORMAL
		end
		return "获得了一个未知物品!", noteType.NORMAL
	end,

	[281] = function(source, target)
		local sid=tonumber(target)
		local eu=gdItems[sid]
		if	eu then
			local name=eu.name
			return "丢弃"..name, noteType.NORMAL
		end
		return "丢弃了一个未知物品!", noteType.NORMAL
	end,

	[283] = function(source, target)
		return "不能再次使用 !", noteType.NORMAL
	end,

	[284] = function(source, target)
		return "装备未附魔 !"
	end,

	[285] = function(source, target)
		return "已达到最大附魔次数 !", noteType.NORMAL
	end,

	[286] = function(source, target)
		return "摊位里的物品的价格已经被修改过了 !", noteType.NORMAL
	end,

	[287] = function(source, target)
		return "坐骑等级太低!", noteType.NORMAL
	end,
	[288] = function(source, target)
		return "上马状态不能切换!", noteType.NORMAL
	end,

	[290] = function(source, target)
		return "身上没有可以绑定的装备 !", noteType.NORMAL
	end,

	[300] = function(source, target)
		return "使用技能失败！", noteType.NORMAL
	end,

	[301] = function(source, target)
		return "魔法值不足！", noteType.NORMAL
	end,

	[302] = function(source, target)
		return "距离太远！", noteType.NORMAL
	end,

	[303] = function(source, target)
		return "无效的技能！", noteType.NORMAL
	end,

	[305] = function(source, target)
		--return "技能冷却中！", noteType.NORMAL
		return "", noteType.NORMAL
	end,

	[306] = function(source, target)
		return "你已被眩晕了！", noteType.NORMAL
	end,

	[310] = function(source, target)
		return "已学会该技能！", noteType.NORMAL
	end,

	[311] = function(source, target)
		return "技能等级不够！", noteType.NORMAL
	end,

	[401] = function(source, target)
		return "不在区域内！", noteType.NORMAL
	end,
	[410] = function(source, target)
		return "队友距离太远！", noteType.NORMAL
	end,
	[411] = function(source, target)
		return "已经没有可用的次数了！", noteType.NORMAL
	end,
	[412] = function(source, target)
		return "副本入口已关闭", noteType.NORMAL
	end,
	[413] = function(source, target)
		return "场景不允许", noteType.NORMAL
	end,
	[414] = function(source, target)
		return "场景未完成", noteType.NORMAL
	end,
	[415] = function(source, target)
		return "安全区无法这样做！", noteType.NORMAL
	end,

	[416] = function(source, target)
		return "多人副本中，不能退出队伍", noteType.NORMAL
	end,

	[417] = function(source, target)
		return "停止挖矿", noteType.NORMAL
	end,

	[420] = function(source, target)
		return "这件物品不属于你！", noteType.NORMAL
	end,


	[450] = function(source, target)
		return "当前地图无法使用飞鞋！", noteType.NORMAL
	end,

	[451] = function(source, target)
		return "没有足够的飞鞋！", noteType.NORMAL
	end,

	[460] = function(source, target)
		return "该区域无法摆摊!", noteType.NORMAL
	end,

	[500] = function(source, target)
		return "无效任务！", noteType.NORMAL
	end,
	[501] = function(source, target)
		return "该任务状态异常！", noteType.NORMAL
	end,
	[502] = function(source, target)
		return "该任务无法放弃！", noteType.NORMAL
	end,

	[510] = function(source, target)
		return "已经获得了足够多的任务物品！", noteType.NORMAL
	end,
	[511] = function(source, target)
		return "非当前任务目标物品！", noteType.NORMAL
	end,

	[603] = function(source, target)
		return "该场景无法交易！", noteType.NORMAL
	end,

	[604] = function(source, target)
		return "已经锁定交易，无法变更！", noteType.NORMAL
	end,

	[605] = function(source, target)
		return "您已锁定交易！", noteType.NORMAL
	end,

	[606] = function(source, target)
		return "对方物品变更，交易解锁！", noteType.NORMAL
	end,

	[607] = function(source, target)
		return "对方交易已解锁！", noteType.NORMAL
	end,

	[608] = function(source, target)
		return "对方交易已锁定！", noteType.NORMAL
	end,

	[700] = function(source, target)
		return "无效功能！", noteType.NORMAL
	end,
	[701] = function(source, target)
		return "活动尚未开启！", noteType.NORMAL
	end,
	[702] = function(source, target)
		return "活动尚未结束! ", noteType.NORMAL
	end,
	[703] = function(source, target)
		return "缺少副本神符! ", noteType.NORMAL
	end,

	[800] = function(source, target)
		return "该玩家和你已在同一队伍！", noteType.NORMAL
	end,
	[801] = function(source, target)
		return "组队操作超时！", noteType.NORMAL
	end,
	[802] = function(source, target)
		return "该玩家没有队伍！", noteType.NORMAL
	end,
	[803] = function(source, target)
		return "该玩家已有队伍！", noteType.NORMAL
	end,
	[804] = function(source, target)
		return "队伍人数超过上限！", noteType.NORMAL
	end,
	[805] = function(source, target)
		return "你已经有一个队伍！", noteType.NORMAL
	end,
	[806] = function(source, target)
		return "你不是队长！", noteType.NORMAL
	end,
	[807] = function(source, target)
		return "监狱中的玩家不能组队！", noteType.NORMAL
	end,
    [808] = function(source, target)
		return "仙玉不足", noteType.NORMAL---仙玉
	end,
	 [888] = function(source, target)
		return "灵力不足", noteType.NORMAL---灵力
	end,
	[902] = function(source, target)
		return "重复申请！", noteType.NORMAL
	end,
	[903] = function(source, target)
		return "你没有权限执行该操作！", noteType.NORMAL
	end,
	[904] = function(source, target)
		return "申请列表为空！", noteType.NORMAL
	end,
	[905] = function(source, target)
		return "目标已经有行会！", noteType.NORMAL
	end,
	[906] = function(source, target)
		return "没有足够的行会资金！", noteType.NORMAL
	end,
	[907] = function(source, target)
		return "没有这个行会！", noteType.NORMAL
	end,
	[908] = function(source, target)
		return "没有行会！", noteType.NORMAL
	end,
	[911] = function(source, target)
		return "行会名字已经被使用！", noteType.NORMAL
	end,
	[912] = function(source, target)
		return "正在创建中！", noteType.NORMAL
	end,
	[913] = function(source, target)
		return "你没有权限执行该操作！", noteType.NORMAL
	end,
	[914] = function(source, target)
		return "所需物品不足！", noteType.NORMAL
	end,
	[915] = function(source, target)
		return "无效工会成员！", noteType.NORMAL
	end,
	[916] = function(source, target)
		return "名字太长！", noteType.NORMAL
	end,
	[917] = function(source, target)
		return "不能把自己踢出行会！", noteType.NORMAL
	end,
	[919] = function(source, target)
		return "行会成员达到上限！", noteType.NORMAL
	end,
	[930] = function(source, target)
		return "已经领取过奖励！", noteType.NORMAL
	end,
	[931] = function(source, target)
		return "无效的称号！", noteType.NORMAL
	end,
	[932] = function(source, target)
		return "无效的职位！", noteType.NORMAL
	end,
	[933] = function(source, target)
		return "你不是沙城占领行会成员。", noteType.NORMAL
	end,
	[934] = function(source, target)
		return "被邀请者已经在申请列表中。", noteType.NORMAL
	end,
	[935] = function(source, target)
		return "申请成功，请耐心等待回复。", noteType.NORMAL
	end,
	[936] = function(source, target)
		return "领取福利成功", noteType.NORMAL
	end,

	[938] = function(source, target)
		return "申请的行会数量过多。", noteType.NORMAL
	end,

	[940] = function(source, target)
		return "您的行会贡献不足！", noteType.NORMAL
	end,

	[941] = function(source, target)
		return "您已成功撤销申请", noteType.NORMAL
	end,

	[942] = function(source, target)
		return "您未申请该行会", noteType.NORMAL
	end,

	[943] = function(source, target)
		return "退离行会1小时之内不能加入行会", noteType.NORMAL
	end,

	[944] = function(source, target)
		return "每个官职每天只能修改一次", noteType.NORMAL
	end,
	[945] = function(source, target)
		return "领取成功，您的行会资金增加了!", noteType.NORMAL
	end,
	[946] = function(source, target)
		return "只有周五晚上22:00-22:30期间才能领取!", noteType.NORMAL
	end,
	[950] = function(source, target)
		return "您的行会中还有其他成员，请先禅让首领后再退出行会！", noteType.NORMAL
	end,
	[952] = function(source, target)
		return "主建筑等级不足!", noteType.NORMAL
	end,
	[953] = function(source, target)
		return "今日的探险次数已达上限!", noteType.NORMAL
	end,
	[954] = function(source, target)
		return "该福利今日已经开启!", noteType.NORMAL
	end,
	[955] = function(source, target)
		return "该福利今日尚未开启!", noteType.NORMAL
	end,
	[956] = function(source, target)
		return "该福利今日已经获得!", noteType.NORMAL
	end,
	[957] = function(source, target)
		return "建筑等级不足!", noteType.NORMAL
	end,
	[958] = function(source, target)
		return "尚无行会连续占领4天!", noteType.NORMAL
	end,
	[959] = function(source, target)
		return "对方已同意加入工会!", noteType.NORMAL
	end,
	[960] = function(source, target)
		return "本服没有公会可以参加跨服攻城战!", noteType.NORMAL
	end,
	[961] = function(source, target)
		return "你没有加入任何公会!", noteType.NORMAL
	end,
	[962] = function(source, target)
		return "你所在的公会不能参加跨服战!", noteType.NORMAL
	end,
	[963] = function(source, target)
		return "只有周四晚上20点到22点之间才能参加跨服战!", noteType.NORMAL
	end,


	[1001] = function(source, target)
		return "可用次数不足！", noteType.NORMAL
	end,

	[1002] = function(source, target)
		return "已到达最大倍率！", noteType.NORMAL
	end,

	[1003] = function(source, target)
		return "不能刷出更小的倍率！", noteType.NORMAL
	end,

	[1004] = function(source, target)
		return "可购买次数不足！", noteType.NORMAL
	end,

	[1005] = function(source, target)
		return "可用次数已达到最大！", noteType.NORMAL
	end,


	[1010] = function(source, target)
		return "使用次数达到上限！", noteType.NORMAL
	end,

	[1011] = function(source, target)
		return "今日已全部通关！", noteType.NORMAL
	end,

	[1013] = function(source, target)
		return "当前有未完成的财神任务！", noteType.NORMAL
	end,

	[1020] = function(source, target)
		return "今日护送次数已用完！", noteType.NORMAL
	end,
	[1021] = function(source, target)
		return "并未护送美女！", noteType.NORMAL
	end,
	[1022] = function(source, target)
		return "正在护送美女！", noteType.NORMAL
	end,

	[1023] = function(source, target)
		return "队伍中有人正在护送美女！", noteType.NORMAL
	end,

	[1040] = function(source, target)
		return "你不是公会首领！", noteType.NORMAL
	end,

	[1041] = function(source, target)
		return "公会没有足够资金！", noteType.NORMAL
	end,

	[1042] = function(source, target)
		return "场景错误！", noteType.NORMAL
	end,

	[1043] = function(source, target)
		return "你还没有公会！", noteType.NORMAL
	end,

	[1050] = function(source, target)
		return "金币刷新已经到达今日上限",noteType.NORMAL
	end,

	[1051] = function(source, target)
		return "已经到达今日挑战次数上限", noteType.NORMAL
	end,

	[1052] = function(source, target)
		return "今日挑战次数还未使用",noteType.NORMAL
	end,

	[1053] = function(source, target)
		return "已是最高等级BUFF",noteType.NORMAL
	end,

	[1060] = function(source, target)
		return "当日已经签到过",noteType.NORMAL
	end,

	[1061] = function(source, target)
		return "不能补签还未到达的日期",noteType.NORMAL
	end,

	[1062] = function(source, target)
		return "只能补签本周的日期。",noteType.NORMAL
	end,

	[1071] = function(source, target)
		return "未达到在线所需时间!", noteType.NORMAL
	end,

	[1080] = function(source, target)
		return "守城方无法使用！", noteType.NORMAL
	end,
	[1081] = function(source, target)
		return "攻城战还未开始!", noteType.NORMAL
	end,
	[1082] = function(source, target)
		return "攻城战击杀最多的玩家并不是你!", noteType.NORMAL
	end,
	[1083] = function(souce, target)
		return "当前没有城主!", noteType.NORMAL
	end,

	[1102] = function(source, target)
		return "当前没有宠物!", noteType.NORMAL
	end,

	[1104] = function(source, target)
		return "你的金币不足!", noteType.NORMAL
	end,

	[1107] = function(source, target)
		return "没有10级以上的宠物!", noteType.NORMAL
	end,

	[1108] = function(source, target)
		return "出战中宠物无法摆摊!", noteType.NORMAL
	end,
	[1109] = function(source, target)
		return "宠物已经满级!", noteType.NORMAL
	end,

	[1111] = function(source, target)
		return "下架成功!", noteType.NORMAL
	end,

	[1111] = function(source, target)
		return "上架成功!", noteType.NORMAL
	end,

	[1112] = function(source, target)
		return "摆摊成功!", noteType.NORMAL
	end,

	[1113] = function(source, target)
		return "摆摊必须出售物品!", noteType.NORMAL
	end,

	[1114] = function(source, target)
		return "没有可提升的进阶属性！", noteType.NORMAL
	end,

	[1115] = function(source, target)
		return "找不到该宠物！", noteType.NORMAL
	end,

	[1116] = function(source, target)
		return "宠物需要先休息！", noteType.NORMAL
	end,

	[1117] = function(source, target)
		return "宠物需要先休息！", noteType.NORMAL
	end,

	[1118] = function(source, target)
		return "转生等级不够！", noteType.NORMAL
	end,

	[1119] = function(source, target)
		return "被吞噬等级不够！", noteType.NORMAL
	end,

	[1120] = function(source, target)
		return "已达最大转生次数！", noteType.NORMAL
	end,

	[1121] = function(source, target)
		return "相同宠物不能转生！", noteType.NORMAL
	end,

	[1122] = function(source, target)
		return "已转生宠物不能被吞噬！", noteType.NORMAL
	end,

	[1202] = function(source, target)
		return "没有该名字的玩家！", noteType.NORMAL
	end,

	[1210] = function(source, target)
		return "该玩家已经是你的好友了！", noteType.NORMAL
	end,

	[1211] = function(source, target)
		return "该玩家已经是你的师父了！", noteType.NORMAL
	end,

	[1212] = function(source, target)
		return "该玩家已经是你的徒弟了！", noteType.NORMAL
	end,

	[1213] = function(source, target)
		return "伴侣数量达到上限！", noteType.NORMAL
	end,

	[1214] = function(source, target)
		return "该玩家已经是你的仇人了！", noteType.NORMAL
	end,

	[1220] = function(source, target)
		return "师傅数量达到上限！", noteType.NORMAL
	end,

	[1221] = function(source, target)
		return "徒弟数量达到上限！", noteType.NORMAL
	end,

	[1230] = function(source, target)
		return "该玩家等级不符合！", noteType.NORMAL
	end,

	[1231] = function(source, target)
		return "超过了条件等级！", noteType.NORMAL
	end,
	
	[1240] = function(source, target)
		return "离婚未满7天，暂时不能再次结婚！", noteType.NORMAL
	end,

	[1241] = function(source, target)
		return "解除师徒关系未满7天，暂时不能再次拜师/收徒！", noteType.NORMAL
	end,

	[1310] = function(source, target)
		return "兑换异常，请联系运营商！", noteType.NORMAL
	end,

	[1311] = function(source, target)
		return "无效的激活码！", noteType.NORMAL
	end,
	[1312] = function(source, target)
		return "激活码已经被使用！", noteType.NORMAL
	end,
	[1315] = function(source, target)
		return "您已使用过该类型的激活码!",noteType.NORMAL
	end,
	
	[1317] = function(source, target)
		return "必须有队伍",noteType.NORMAL
	end,
    [1318] = function(source, target)
		return "没有结婚",noteType.NORMAL
	end,
	[1319] = function(source, target)
		return "队友不是你的伴侣",noteType.NORMAL
	end,
	[1320] = function(source, target)
		return "情侣副本必须2人",noteType.NORMAL
	end,
	
	
	
	
	
	
	

	[10000] = function(source, target)
		return "行会并未进行美女护送!", noteType.NORMAL
	end,
	[10001] = function(source, target)
		return "行会护送目标还未到达!", noteType.NORMAL
	end,
	[10002] = function(source, target)
		return "行会护送已经开启！", noteType.NORMAL
	end,

	[10010] = function(source, target)
		return "无效的建筑类型！", noteType.NORMAL
	end,
	[10011] = function(source, target)
		return "行会当前正在建造其他建筑！", noteType.NORMAL
	end,
	[10012] = function(source, target)
		return "建筑尚未开放！", noteType.NORMAL
	end,
	[10013] = function(source, target)
		return "建筑已经满级!", noteType.NORMAL
	end,
	[10014] = function(source, target)
		return "行会资金不足!", noteType.NORMAL
	end,
	[10015] = function(source, target)
		return "已经在攻城战名单中，不要重复申请!", noteType.NORMAL
	end,
	[10016] = function(source, target)
		return "战神之力Buff已经开启!", noteType.NORMAL
	end,
	[10017] = function(source, target)
		return "行会没有报名参加攻城战!", noteType.NORMAL
	end,
	[10018] = function(source, target)
		return "行会关公祭拜次数已达上限!", noteType.NORMAL
	end,
	[10019] = function(source, target)
		return "只能在周四进行报名!", noteType.NORMAL
	end,

	[10100] = function(source, target)
		return "等级不足，需求等级40!", noteType.NORMAL
	end,
	[10101] = function(source, target)
		return "等级不足，需求等级42!", noteType.NORMAL
	end,
	[10102] = function(source, target)
		return "等级不足，需求等级44", noteType.NORMAL
	end,
	[10103] = function(source, target)
		return "等级不足，需求等级46", noteType.NORMAL
	end,
	[10104] = function(source, target)
		return "等级不足，需求等级48!", noteType.NORMAL
	end,
	[10105] = function(source, target)
		return "等级不足，需求等级49!", noteType.NORMAL
	end,
	[10106] = function(source, target)
		return "等级不足，需求等级50!", noteType.NORMAL
	end,


	[11001] = function(source, target)
		return "状态已满！", noteType.NORMAL
	end,
	[11002] = function(source, target)
		return "金钱不足，只修理了部分物品！", noteType.NORMAL
	end,
	[11003] = function(source, target)
		return "你无须使用此物品!", noteType.NORMAL
	end,

	[11010] = function(source, target)
		return "此类聚宝盆只能购买一次。", noteType.NORMAL
	end,

	[11011] = function(source, target)
		return "", noteType.NORMAL
	end,

	[11012] = function(source, target)
		return "已经领取过今天返还元宝", noteType.NORMAL
	end,

	[-997] =  function(source, target)
		return "您已重新登录！", noteType.NORMAL
	end,
	[-998] =  function(source, target)
		return "您长时间没有操作，请重新登录！", noteType.NORMAL
	end,

	[-999] =  function(source, target)
		return "您有一笔订单正在处理中，请稍后！", noteType.NORMAL
	end,

	[-1000] =  function(source, target)
		return "注册成功！", noteType.NORMAL
	end,

	[-1001] =  function(source, target)
		return "参数不完整！", noteType.NORMAL
	end,

	[-1002] =  function(source, target)
		return "未配置游戏参数！", noteType.NORMAL
	end,

	[-1003] =  function(source, target)
		return "注册失败！", noteType.NORMAL
	end,

	[-1004] =  function(source, target)
		return "用户名长度不合适！", noteType.NORMAL
	end,

	[-1006] =  function(source, target)
		return "用户名已经存在！", noteType.NORMAL
	end,

	[-10007] =  function(source, target)
		return "注册失败！", noteType.NORMAL
	end,

	[-2001] =  function(source, target)
		return "用户名长度不合适！", noteType.NORMAL
	end,

	[-2002] =  function(source, target)
		return "注册失败！", noteType.NORMAL
	end,

	[-2003] =  function(source, target)
		return "用户名不可注册！", noteType.NORMAL
	end,

	[-2004] =  function(source, target)
		return "两次输入的密码不一致！", noteType.NORMAL
	end,

	[-4000] =  function(source, target)
		return "登录成功！", noteType.NORMAL
	end,

	[-4001] =  function(source, target)
		return "未配置游戏参数！", noteType.NORMAL
	end,

	[-4002] =  function(source, target)
		return "加密验证串不正确！", noteType.NORMAL
	end,

	[-4003] =  function(source, target)
		return "用户名长度不合适！", noteType.NORMAL
	end,

	[-4004] =  function(source, target)
		return "用户名或密码错误！", noteType.NORMAL
	end,

	[-4005] =  function(source, target)
		return "用户名或密码不能为空！", noteType.NORMAL
	end,

	[-4010] =  function(source, target)
		return "登录失败！", noteType.NORMAL
	end,

	[-5000] =  function(source, target)
		return "登录成功！", noteType.NORMAL
	end,

	[-5001] =  function(source, target)
		return "未配置游戏参数！", noteType.NORMAL
	end,

	[-5002] =  function(source, target)
		return "加密验证串不正确！", noteType.NORMAL
	end,

	[-5003] =  function(source, target)
		return "用户不存在！", noteType.NORMAL
	end,

	[-5004] =  function(source, target)
		return "登录失败！", noteType.NORMAL
	end,
	[-5005] =  function(source, target)
		return "用户名中存在非法字符！", noteType.NORMAL
	end,
	[-9000] =  function(source, target)
		return "修改成功!", noteType.NORMAL
	end,
	[-9001] =  function(source, target)
		return "参数不完整!", noteType.NORMAL
	end,
	[-9002] =  function(source, target)
		return "未配置游戏参数!", noteType.NORMAL
	end,
	[-9003] =  function(source, target)
		return "加密验证串不正确!", noteType.NORMAL
	end,
	[-9004] =  function(source, target)
		return "用户名长度不合适!", noteType.NORMAL
	end,
	[-9006] =  function(source, target)
		return "用户名已经存在!", noteType.NORMAL
	end,
	[-90007] =  function(source, target)
		return "修改失败!", noteType.NORMAL
	end,
}

---------------------------------------------------------
--[[

--]]
-- 这个表的key代表opcode，source和target同上，data1，data2，data3是扩展整型数据，返回同上。
local getOperationMsg = {
	[0] = function(source, target, data1, data2, data3)
		return "", noteType.NORMAL
	end,

	[1] = function(source, target, data1, data2, data3)
		log.error("getOperationMsg: " .. source .. target .. data1 .. data2 .. data3)
		return "", noteType.NORMAL
	end,

	[107] = function(source, target, data1, data2, data3)
		log.info("source"..source)
		log.info("target"..target)
		log.info("data1"..data1)
		log.info("data2"..data2)
		log.info("data3"..data3)
		local sid=tonumber(data1)
		local reason=tonumber(data3)
		local count=tonumber(data2)
		local item=gdItems[sid]
		local reasonstr = "reason = "..reason
		if reason==0 then
			reasonstr = ""
		end
		local notetype = noteType.NORMAL
		if data3==Opcode.Op_Loot  or data3==Opcode.Op_pet_pick_up then
			--
			--	战利品(物品, 经验)在3号提示区域
			notetype = noteType.TRIVIAL
		end
		if item then
			local name=item.name
			if count>0 then
				return "获得：" .. count ..name, notetype
			else
				return "花费：" .. -count ..name, notetype
			end
		else
			if count>0 then
				return "获得：" .. count .."个"..sid, notetype
			else
				return "花费：" .. -count .."个"..sid, notetype
			end
		end

	end,

	--
	--	获得经验
	[204] = function(source, target, data1, data2, data3)
		local notetype = noteType.NORMAL
		if data1<=0 then
			--
			--notetype = noteType.TRIVIAL
			return "宠物升级", notetype
		else
			return "宠物获得经验".."x".. data1, notetype
		end
	end,

	--
	--	获得经验
	[205] = function(source, target, data1, data2, data3)
		local notetype = noteType.NORMAL
		local diffExp = data2 or 0
		if (diffExp <= 0) then
			return "", notetype
		end

		if (data3 == Opcode.Op_Loot) or (data3 == Opcode.Op_pet_pick_up) then
			--
			--	战利品(物品, 经验)在3号提示区域
			notetype = noteType.TRIVIAL
		end
		return "获得经验".."x".. data2, notetype
	end,

	--
	--	宠物死亡
	[206] = function(source, target, data1, data2, data3)
		local notetype = noteType.NORMAL
		if source =="HandleMessageUpdPetLvlExpNotify" then
			if data1==0 then
				return "宠物死亡了,回到休息状态", notetype
			else
				return "宠物死亡了，损失经验".. data1..",回到休息状态", notetype
			end
		end
	end,

	--
	-- entity prop update
	[210] = function(source, target, data1, data2, data3, data4)
		local propID = data1 or 0
		local propTable = {
			[111] = "转生灵魂",
			[117] = "战力",
			[115] = "pk值",
			[888] = "灵力",
		}

		local msg = propTable[propID]
		if msg then
			local diff = data3 or 0
			if (diff > 0) then
				return msg .. "增加" .. diff, noteType.NORMAL
			elseif (diff < 0) then
				return msg .. "减少" .. -diff, noteType.NORMAL_RED
			end
		end
		return "", noteType.NORMAL
	end,

	--
	--宠物获得经验
	[212] = function(source, target, data1, data2, data3)
		local notetype = noteType.NORMAL
		if source =="HandleMessageUpdPetLvlExpNotify" then
			if data1==0 then
				return "", notetype
			else
				return "宠物获得经验".. data1, notetype
			end
		end
	end,

	[220] = function(source, target, data1, data2, data3)-- 开启荣誉
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		elseif attr_type_to_name[data1] and attr_type_to_name[data1] ~="" then
			if count>0 then
				return (attr_type_to_name[data1] or "") .. "+"..count, noteType.NORMAL
			elseif count<0 then
				return (attr_type_to_name[data1] or "") .. count, noteType.NORMAL
			end
		end
	end,

	[230] = function(source, target, data1, data2, data3) -- 技能获得
		if (data1 > 0) then
			local name = g_get_skill_name(data1)
			if (name ~= "") then
				return "学会新技能：" .. name, noteType.NORMAL
			end
		end
	end,

	[231] = function(source, target, data1, data2, data3) -- 技能升级
		if (data1 > 0) then
			local name = g_get_skill_name(data1)
			if (name ~= "") then
				return  name .. "升级" , noteType.NORMAL
			end
		end
	end,



	[250] = function(source, target, data1, data2, data3)--装备穿上 脱下
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
		return "", noteType.NORMAL
	end,

	[261] = function(source, target, data1, data2, data3)
		return "进入攻击状态", noteType.NORMAL
	end,
	[262] = function(source, target, data1, data2, data3)
		return "进入防御状态", noteType.NORMAL
	end,


	[405] = function(source, target, data1, data2, data3)--装备升级
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[406] = function(source, target, data1, data2, data3)--装备转生
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[407] = function(source, target, data1, data2, data3)--装备强化
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[408] = function(source, target, data1, data2, data3)--装备鉴定
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[409] = function(source, target, data1, data2, data3)--装备清洗
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[412] = function(source, target, data1, data2, data3)--极品属性转移
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[415] = function(source, target, data1, data2, data3)--装备打磨
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[416] = function(source, target, data1, data2, data3)--装备完美强化
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[422] = function(source, target, data1, data2, data3)--鉴定转移
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[421] = function(source, target, data1, data2, data3)--强化转移
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[423] = function(source, target, data1, data2, data3)--极品清洗
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
	end,

	[418] = function(source, target, data1, data2, data3, data4)
		local iid = tonumber(data3)
		local item=gdItems[tonumber(data1)]
		local notetype = noteType.NORMAL

		if data4==503 then
			return "", notetype
		end

		if data4==Opcode.Op_Loot  or data4==Opcode.Op_pet_pick_up then
			--
			--	战利品(物品, 经验)在3号提示区域
			notetype = noteType.TRIVIAL
		end

		if item then
			return "获得"..item.name.."x" .. data2, notetype
		else
			return "获得无效物品!"
		end
	end,

	[419] = function(source, target, data1, data2, data3)
		local reason = tonumber(data3)
		local reasonTable = {
			[110] = "卖出",
			[500] = "卖出",
			[502] = "使用",
			[504] = "丢弃",
		}

		local ntType = noteType.TRIVIAL_RED

		if reason==503 then
			return "", ntType
		elseif reason==500 then
			ntType = noteType.NORMAL
		end

		local reasonStr = reasonTable[reason]
		if not(reasonStr) then
			reasonStr = "使用"
			ntType = noteType.TRIVIAL_RED
		end
		local item=gdItems[tonumber(data1)]
		if item then
			return reasonStr .. item.name .. "x" .. data2, ntType
		end
		return reasonStr .. data1 .. "x" .. data2, ntType
	end,

	[465] = function(source, target, data1, data2, data3)--装备耐久恢复
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
		return "", noteType.NORMAL
	end,
	[466] = function(source, target, data1, data2, data3)--装备耐久变为0
		local count=tonumber(data2)
		if data1==117 then
			if count>0 then
				return "战力增加"..count, noteType.NORMAL
			elseif count<0 then
				return "战力减少"..-count, noteType.NORMAL_RED
			end
		end
		return "", noteType.NORMAL
	end,

	[502] = function(source, target, data1, data2, data3, data4)--物品使用
		local count=tonumber(data2)
		local nowdata=tonumber(data3)
		if source == "HandleMessageItemUpdData" then
			if data1==14 then
				local itemSID = tonumber(data4)
				if count>0 then
					return "武器被加幸运了...", noteType.NORMAL
				elseif count<0 then
					return "武器被诅咒了..", noteType.NORMAL_RED
				elseif count==0 then
					return "很遗憾，你没能获得武神的祝福。", noteType.NORMAL_RED
				end
			end
		end
		return "", noteType.NORMAL
	end,

	[601] = function(source, target, data1, data2, data3)
		local quest=gdQuests[data1]
		if quest then
			return "接受任务：" .. quest.name , noteType.NORMAL
		end
		return "" , noteType.NORMAL
	end,

	[602] = function(source, target, data1, data2, data3)
		local quest=gdQuests[data1]
		if quest then
			local targetdata = quest.target_datay
			local nowdata = gdceapon.get_sub_data("task","current_task_list",data1,"data_2") or 0
			if targetdata==0 then
				return "" , noteType.NORMAL
			end
			return quest.name..":" .. nowdata .."/".. targetdata  , noteType.NORMAL
		end
		return "" , noteType.NORMAL
	end,

	[603] = function(source, target, data1, data2, data3)
		local quest=gdQuests[data1]
		if quest and data2==2 then
			return "完成任务：" .. quest.name , noteType.NORMAL
		end
		return ""  , noteType.NORMAL
	end,

	[604] = function(source, target, data1, data2, data3)
		local quest=gdQuests[data1]
		if quest and data2==1 then
			return "放弃任务：" .. quest.name , noteType.NORMAL
		end
		return ""  , noteType.NORMAL
	end,

	[605] = function(source, target, data1, data2, data3)
		local quest=gdQuests[data1]
		if quest and data2==0 then
			return "提交任务：" .. quest.name , noteType.NORMAL
		end
		return ""  , noteType.NORMAL
	end,
	[803] = function(source, target, data1, data2, data3)
		if data1==1 then	-- is Activity
			if data3==1 then -- Will Begin
				local ed = gdEventData[data2]
				if ed and ed.hidetip ~= 1 then
					local who = ""
					local lvl = ed.requirelvl or 0
					local rb = ed.reborn or 0
					if rb==0 and lvl==1 then
						who = "所有玩家"
					else
						if rb>1 then
							who = rb.."转"
						end
						if lvl>1 then
							who = who .. lvl .."级以上的玩家"
						end
					end

					return ed.name.."将于5分钟后开启，请"..who.."做好准备!", noteType.TOP
				end
			elseif data3==2 then
				local ed = gdEventData[data2]
				if ed and ed.hidetip ~= 1 then
					return ed.name.."正式开始!", noteType.TOP
				end
			elseif data3==0 then
				local ed = gdEventData[data2]
				if ed and ed.hidetip ~= 1 then
					return ed.name.."已结束!", noteType.TOP
				end
			end
		end
		return "", noteType.DEBUG
	end,

	[812] = function(source, target, data1, data2, data3)
		local emigdata = gdEmigrated[data1]
		if emigdata then
			local name = emigdata.name or ""
			return "触发了" .. name .."事件！" , noteType.NORMAL
		end
		return "", noteType.NORMAL
	end,

	[1026] = function(source, target, data1, data2, data3)
		return "添加"..data1.."仇人成功" , noteType.NORMAL
	end,

	[2000] = function(source, target, data1, data2, data3)
		return "请先加入一个行会", noteType.NORMAL
	end,

	[2008] = function(source, target, data1, data2, data3)
		return  "您已开启"..data1, noteType.NORMAL
	end,

	[5000] = function(source, target, data1, data2, data3)
		local name = data1 or "玩家"
		local pid = data2 or 0
		if (pid == gdceapon.get_data("hero", "pid")) then
			name = "你"
		end
		return name .. "进入了队伍", noteType.NORMAL
	end,

	[5001] = function(source, target, data1, data2, data3)
		local name = data1 or "玩家"
		local pid = data2 or 0
		if (pid == gdceapon.get_data("hero", "pid")) then
			name = "你"
		end
		return name .. "离开了队伍", noteType.NORMAL
	end,

	[5002] = function(source, target, data1, data2, data3)
		return "你已退出了当前队伍", noteType.NORMAL
	end,

	[5003] = function(source, target, data1, data2, data3)
		local name = data1 or "玩家"
		local pid = data2 or 0
		if (pid == gdceapon.get_data("hero", "pid")) then
			name = "你"
		end
		return name .. "已提升为队长！", noteType.NORMAL
	end,

	
}

---------------------------------------------------------
--[[
namespace CPModuleName
{
	static const std::string EVENT = "event";
}

namespace CPEventData
{
	static const std::string SOURCE = "source";
	static const std::string TARGET = "target";

	// data
	static const std::string VALUE_1 = "value_1";
	static const std::string VALUE_2 = "value_2";
	static const std::string VALUE_3 = "value_3";
	static const std::string VALUE_4 = "value_4";
	static const std::string VALUE_5 = "value_5";
}

namespace CPEventName
{
	// event from msg
	static const std::string MSG_CHANGE = "msg_change";
	static const std::string MSG_FINISH = "msg_finish";

	static const std::string UI_NOTIFY = "ui_notify";
}
--]]
cpnotification = init_table_safely(cpnotification)
cpnotification.on_cp_event = function(eventName)
	if (eventName == "msg_finish") or (eventName == "ui_notify") then
		local errcode = gdceapon.get_sub_data("event", eventName, 1, "value_1")
		if errcode then
			local getMsg = getErrorMsg[errcode]
			if getMsg then
				local source = gdceapon.get_sub_data("event", eventName, 1, "source") or ""
				local target = gdceapon.get_sub_data("event", eventName, 1, "target") or ""
				local note, noteType = getMsg(source, target)
				addNote(note, noteType)
			else
				addNote("错误 errorcode = "..tostring(errcode), noteType.NORMAL)
			end
		end
	elseif (eventName == "msg_change") then
		local hasEnterScene = gdceapon.get_data("scene", "has_enter_scene")
		if (hasEnterScene ~= 1) then
			return
		end

		local opcode = gdceapon.get_sub_data("event", eventName, 1, "value_1")
		if opcode then
			local getMsg = getOperationMsg[opcode]
			if getMsg then
				local source = gdceapon.get_sub_data("event", eventName, 1, "source") or ""
				local target = gdceapon.get_sub_data("event", eventName, 1, "target") or ""
				local data1 = gdceapon.get_sub_data("event", eventName, 1, "value_2") or 0
				local data2 = gdceapon.get_sub_data("event", eventName, 1, "value_3") or 0
				local data3 = gdceapon.get_sub_data("event", eventName, 1, "value_4") or 0
				local data4 = gdceapon.get_sub_data("event", eventName, 1, "value_5") or 0
				local note, noteType = getMsg(source, target, data1, data2, data3, data4)
				if (type(noteType) == "number") and (noteType > 0) then
					addNote(note, noteType)
				else
					log.error("cpnotification.on_cp_event, msg_change, invalid noteType. opcode = " .. opcode)
				end
			else
				--addNote("opcode = "..tostring(opcode), noteType.NORMAL)
			end
		end
	end
end

------------------------------------------------------



















