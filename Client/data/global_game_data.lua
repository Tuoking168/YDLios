if not (type(gdGame)=="table") then
	gdGame = {}
end

local GD = gdGame

gdGame.getValueByKey = function(key)
	return gdGame[key]
end

--- 人物基础走路速度(Tile数/秒)
gdGame.roleBaseSpeed = 2.4

--- 角色名称最大长度
GD.roleNameMaxLen = 7

-- 行会名称最大长度
GD.guildNameMaxLen = 12

------------------------------------
--- 背包初始值
gdGame.playerBagslot = 40
gdGame.petBagslot = 15
gdGame.houseBagslot = 360
gdGame.npcBagslot = 30     --npc仓库数30
--背包上限
gdGame.playerBagslotmax = 320   --角色背包最大格子数80
gdGame.petBagslotmax = 525       --宠物背包最大格子数75
gdGame.houseBagslotmax = 360
gdGame.npcBagslotmax = 120      --npc仓库最大格子数120

--传送门检测半径
gdGame.portalssize = 2

--控制渠道充值
gdGame.canRecharge = 1


--宠物培养数据
gdGame.PetFeedHonor = 1000
gdGame.PetFeedGold = 10
gdGame.PetFeedItem = 40053
gdGame.PetFeedexp = {
	honor = {
		addexp = 10,
		tenexp = 0.1,
		lvlup = 0.001,
	},
	gold = {
		addexp = 30,
		tenexp = 0.1,
		[1] = { minlvl = 1, maxlvl = 10, lvlup = 0.012},
		[2] = { minlvl = 11, maxlvl = 20, lvlup = 0.011},
		[3] = { minlvl = 21, maxlvl = 30, lvlup = 0.010},
		[4] = { minlvl = 31, maxlvl = 40, lvlup = 0.009},
		[5] = { minlvl = 41, maxlvl = 50, lvlup = 0.008},
		[6] = { minlvl = 51, maxlvl = 60, lvlup = 0.007},
		[7] = { minlvl = 61, maxlvl = 70, lvlup = 0.006},
		[8] = { minlvl = 71, maxlvl = 80, lvlup = 0.005},
		[9] = { minlvl = 81, maxlvl = 90, lvlup = 0.004},
		[10] = { minlvl = 91, maxlvl = 100, lvlup = 0.003},
		[11] = { minlvl = 101, maxlvl = 110, lvlup = 0.002},
		[12] = { minlvl = 111, maxlvl = 120, lvlup = 0.001},
		[13] = { minlvl = 121, maxlvl = 0, lvlup = 0.001},
	}
}

--宠物封印物品id
gdGame.Imprison = 40040
gdGame.ImprisonEgg = 38002

--世界第一NPCID
gdGame.firstzs = 144
gdGame.firstfs = 145
gdGame.firstds = 146

--元宝代替价格
gdGame.ItemOfVcoin={
	[40046]=1,
}

--判断是否能丢弃
gdGame.isCanAbandon = function(sid)
	local NotAbandonList = {
		[30006] = {},
		[30007] = {},
		[30008] = {},
		[30009] = {},
		[30010] = {},
		[30011] = {},
		[30012] = {},
		[30013] = {}
		}
	if NotAbandonList[sid] then
		return Error.Item_CanNotAbandon
	end
	return Error.Success
end

--队伍经验分配
gdGame.getTeamRewardExp = function(size,exp)
	if size == 1 then
		return exp
	elseif size == 2 then
		return exp * 0.55
	elseif size == 3 then
		return exp * 0.4
	elseif size == 4 then
		return exp * 0.35
	else
		return exp * 0.3
	end
end

--------------------------------------------------
--美女护送
--奖励
function gdGame.getGirlExp(idx,level)
	local expbase = 55858
	local expspain = 5714
	if level > 35 then
		expbase = expbase + expspain * (level - 35) * (level - 35)
	end
	if idx == 0 then
		return expbase * 1
	elseif idx== 1 then
		return expbase * 1.2
	elseif idx == 2 then
		return expbase * 1.5
	elseif idx == 3 then
		return expbase * 2
	elseif idx == 4 then
		return expbase * 3
	else
		log.error("Unknow idx For Girl Exp ! idx = "..idx)
		return expbase * 1
	end
end
gdGame.girlMoneyReward = 10000

-- 提交NPC
gdGame.girlSubmitNPC = 154

-- 刷新护送对象花费（仙玉/元宝）
gdGame.girlRefreshCost = 3

--------------------------------------------------
-- 聚宝盆购买元宝花费
gdGame.juBaoPenCost1 = 288
gdGame.juBaoPenCost2 = 1288

--------------------------------------------------
-- 新功能开启
local functionOpenList = {
	ji_neng = {
		needLevel = 0,
		needQuest = 0,
		nextFunction = "chong_wu",
		needGuide = true,
	},

	chong_wu = {
		needLevel = 11,
		needQuest = 0,
		nextFunction = "zhuang_bei_qiang_hua",
		needGuide = true,
	},

	zhuang_bei_qiang_hua = {
		needLevel = 21,
		needQuest = 0,
		nextFunction = "rong_yv",
		needGuide = true,
	},

	rong_yv = {
		needLevel = 27,
		needQuest = 0,
		nextFunction = "gong_ji_mo_shi",
		needGuide = true,
	},

	gong_ji_mo_shi = {
		needLevel = 30,
		needQuest = 0,
		nextFunction = "zhuang_bei_jian_ding",
		needGuide = true,
	},

	zhuang_bei_jian_ding = {
		needLevel = 31,
		needQuest = 0,
		nextFunction = "shi_tu",
		needGuide = true,
	},

	shi_tu = {
		needLevel = 34,
		needQuest = 0,
		nextFunction = "hang_hui",
		needGuide = true,
	},

	hang_hui = {
		needLevel = 35,
		needQuest = 0,
		nextFunction = "ban_lv",
		needGuide = true,
	},

	ban_lv = {
		needLevel = 36,
		needQuest = 0,
		nextFunction = "zhuang_bei_sheng_ji",
		needGuide = true,
	},

	zhuang_bei_sheng_ji = {
		needLevel = 40,
		needQuest = 0,
		nextFunction = "hun_shi",
		needGuide = true,
	},

	hun_shi = {
		needLevel = 42,
		needQuest = 0,
		nextFunction = "huan_wu_qi_ling",
		needGuide = true,
	},

	huan_wu_qi_ling = {
		needLevel = 44,
		needQuest = 0,
		nextFunction = "he_cheng",
		needGuide = true,
	},

	he_cheng = {
		needLevel = 45,
		needQuest = 0,
		nextFunction = "shu_xing_zhuan_yi",
		needGuide = true,
	},

	shu_xing_zhuan_yi = {
		needLevel = 47,
		needQuest = 0,
		nextFunction = "zhuan_sheng",
		needGuide = true,
	},

	zhuan_sheng = {
		needLevel = 70,
		needQuest = 0,
		needGuide = true,
	},

	zhuan_sheng_duan_zao = {
		needLevel = 0,
		needQuest = 0,
		needReborn = 1,
	},


	cai_shen_chuang_guan = {
		needLevel = 50,
		needQuest = 0,
	},

	wu_yi_zhan_chang = {
		needLevel = 40,
		needQuest = 0,
	},

	zhan_shen_shi_ce = {
		needLevel = 45,
		needQuest = 0,
	},

	zhan_shen_zheng_ba = {
		needLevel = 30,
		needQuest = 0,
	},

	zhan_li_jing_ji = {
		needLevel = 30,
		needQuest = 0,
	},

	yong_shi_jiao_dou_chang = {
		needLevel = 30,
		needQuest = 0,
	},

	xun_bao = {
		needLevel = 40,
		needQuest = 0,
	},

	hang_hui_zheng_duo_zhan	 = {
		needLevel = 35,
		needQuest = 0,
	},

	mei_ri_gong_zi = {
		needLevel = 20,
		needQuest = 0,
	},

	pai_hang_bang = {
		needLevel = 40,
		needQuest = 0,
		hide = 1,--hide = 1,排行榜关闭
	},

	zuo_qi = {
		needLevel = 40,
		needQuest = 0,
	},
}

gdGame.getFunctionOpenNeed = function(funcName)
	local data = functionOpenList[funcName]
	if data then
		return data.needReborn or 0, data.needLevel or 0, data.needQuest or 0, data.hide or 0, data.openDays or 0
	end
	return 0, 0 , 0, 0, 0
end

gdGame.getNextOpenFunction = function(funcName)
	local data = functionOpenList[funcName]
	if data then
		return data.nextFunction or ""
	end
	return ""
end

gdGame.getOpenFunctionName = function(level)
	level = level or 0
	if (level > 0) then
		for k, v in pairs(functionOpenList) do
			if (v.needGuide) and (v.needLevel == level) then
				return k
			end
		end
	end
	return ""
end

---------------------------------------------------------
--- 战力竞技

-- BUFF加成
GD.challengebuff =
{
	[0] = 1.01,
	[1] = 1.02,
	[2] = 1.03,
	[3] = 1.05,
	[4] = 1.1,
	[5] = 1.2,
}

GD.getChallengeBuff = function(buffID)
	return GD.challengebuff[buffID] or 1
end

-- 增加次数元宝花费
GD.arenaAddCountCost = 10

-- 刷新BUFF花费
GD.arenaRefreshBuffByMoney = 5000
GD.arenaRefreshBuffByGold = 2
GD.arenaRefreshBuffByOneKey = 30

-- 奖励
GD.arenaRankReward = function(level, rank)
	if (level <= 35) then
		return 0, 0
	end

	if (level > 70 ) then
		level = 70
	end

	local key = 1000
	for k,v in pairs(gdArenaTimeReward) do
		if rank <= k then
			if k < key then
				key = k
			end
		end
	end

	local data = gdArenaTimeReward[key]
	if data then
		return (55858 + 100 * (level - 35) ^ 4) * (data.expper or 0), data.honor or 0
	end
	return 0, 0
end

-----------------------------------------------------------
-- 行会建筑

-- 每日上香累计最大贡献值
GD.guildPrayMaxContribution = 5000

-- 上香获得贡献值
GD.guildMoneyPrayContribution = 4
GD.guildHonorPrayContribution = 7
GD.guildGoldPrayContribution = 10

-- 上香花费值
GD.guildMoneyPrayCost = 100000
GD.guildHonorPrayCost = 10000
GD.guildGoldPrayCost = 25

-- 增加上香次数花费元宝数
GD.guildAddPrayCost = 5

-- 清除行会建筑升级时间的元宝消耗单位
GD.guildFinishBuildingCost = 10


-- 行会探险花费贡献值
GD.guildTanxianCost = 10

-----------------------------------------------------------


-----------------------------------------------------------

-- 修理耐久
GD.getItemRepairMoney = function(sid,nowdurable)
	local sd = gdItems[sid]
	--log.info("repair item + 1")
	if sd then
		local dpdata = gdItemRepair[sd.req_level]
		if dpdata then
			return dpdata.money * nowdurable
		end
	end
	return 0
end

--------------------------------------------------------------
-- 城主膜拜

-- 增加次数花费元宝数
GD.worshipAddCost = 3

-- 刷新倍率花费礼券/元宝数，优先使用礼券
GD.worshipRefreshCost = 3

-------------------------------------------------------------
-- 基础攻击间隔
GD.playerattackinterval = 500

-------------------------------------------------------------
-- 攻击速度加成(百分比): 0=原始 100=2倍速 400=5倍速
GD.playerattackspeed = 0

-------------------------------------------------------------
-- 聊天

-- 世界聊天等级限制
GD.chatWorldChannelLevel = 35

-- 世界聊天无等级限制时间(s)
GD.chatWorldChannelFreeTime = 86400
-------------------------------------------------------------

-- 每周工资数据
GD.weekflee =
{
	[1] =
	{
		timestr = "1-21天",
		opentime = 21,
		coupon = 4,
		honor = 200,
	},
	[2] =
	{
		timestr = "22-42天",
		opentime = 42,
		coupon = 5,
		honor = 250,
	},
	[3] =
	{
		timestr = "43天后",
		opentime = 43,
		coupon = 6,
		honor = 300,
	},
}
GD.getWeekfleeData = function(openDays)
	if (openDays <= 0) then
		return 0, 0, 1
	end

	for k, v in ipairs(GD.weekflee) do
		if (openDays <= v.opentime) then
			return v.coupon or 0, v.honor or 0, k
		end
	end

	local data = GD.weekflee[3]
	if data then
		return data.coupon or 0, data.honor or 0, 3
	end
	log.error("GD.getWeekfleeData, unknown openDays: " .. openDays)
	return 0, 0, 1
end

----------------------------------------------------------------------
--财神闯关

-- 增加次数花费元宝数
GD.emigrateAddCountCost = 5

----------------------------------------------------------------------

