require 'math'

gdItemExtension = {}

local FP = FuncProp
local WP = WorldProp
local EP = EntityProp
local SP = SceneProp
local IP = ItemProp
--	local lvl = entity:getLevel()
--[[

enum ItemErrorCode
{
	ItemErr_Success					= 0,

	ItemErr_Unknow					= 1,
	ItemErr_InCoolDown				= 2,
	ItemErr_Script					= 3,

	ItemErr_InvalidCate				= 10,
	ItemErr_InvalidType				= 11,
	ItemErr_InvalidItem				= 12,
	ItemErr_InvalidParam			= 13,
	ItemErr_InvalidEntity			= 14,

	ItemErr_DestinationNotFound		= 20,
	ItemErr_PlayerLvlNotEnough		= 21,
	ItemErr_NoEnoughItem			= 22,
	ItemErr_NoEnoughMoney			= 23,
	ItemErr_NoEnoughGold			= 24,

	ItemErr_CanNotSell				= 30,
	ItemErr_CanNotDelete			= 31,
	ItemErr_CanNotMerge				= 32,
	ItemErr_CanNotForge				= 33,
	Item.ItemErr_BagisFull
};
--]]
--

--local PropsGender = 102

local function addRandomReward(entity, rid, count)
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local lvl = 20--entity:getLevel()
		local lvlidx = 0
		for k,v in pairs(gdTreasureHuntData) do
			if k <= lvl and k >= lvlidx then
				lvlidx = k
			end
		end
		local lucky = 0 -- 5000
		local  thdata = gdTreasureHuntData[lvlidx]
		if thdata then
			local lvldata = thdata.luckyloot
			if not lvldata then
				log.info("Treasure hunt no lvlidx for lvl = "..lvlidx)
			else
				local luckyidx = 0
				local lootid = 0
				for k,v in pairs(lvldata) do
					if k <= lucky and k >= luckyidx then
						luckyidx = k
						lootid = v
					end
				end
				if lootid then
					Loot.callReward(nil,entity,lootid,Opcode.Op_UseItem)
					return Error.Success
				end
			end
		end
		return Error.Script
end

local function makeTable(datas, datae)
	local map = {}
	for d = datas, datae do
		table.insert(map, d)
	end
	return map
end

local function doAddItemByWeight(entity, imap, count, bind) --按权重随机
	count = count or 1
	--print("doAddItmeByWeight", count)

	local omap = {}
	local type_cnt = 0

	local total_weight = 0
	for id, weight in pairs(imap) do
		total_weight = total_weight + weight
	end

	for i = 1, count do
		local n = math.random(total_weight)
		for id, weight in pairs(imap) do
			if n<= weight then
				if omap[id] then
					omap[id] = omap[id] + 1
				else
					omap[id] = 1
					type_cnt = type_cnt + 1
				end
				break
			else
				n = n - weight
			end
		end
	end

	--print("doAddItmeByWeight, Type", type_cnt)

	if entity:getBagEmptyCnt()<type_cnt then
		return Error.Item_BagisFull
	end

	for id, cnt in pairs(omap) do
		--print("doAddItmeByWeight, Add", id, cnt)
		if id>0 and cnt > 0 then
			if bind then
				entity:addBindItem(id, cnt)
			else
				entity:addItem(id, cnt)
			end
		end
	end

	return Error.Success
end

function erxiangfub(nmin,nmax,n)                --获得正态分布
	local result = 0
	for i = 1,n do
		result = result + math.random(nmax - nmin)
	end
	result = math.floor(result / n) + nmin
	return result
end

local function doAddItemByTable(entity, itable, count, bind) --随机获得
	count = count or 1
	--print("doAddItmeByTable", count)

	local omap = {}
	local type_cnt = 0

	for i = 1, count do
		local reward = itable[math.random(table.getn(itable))]
		if reward then
--			if omap[id] then
--				omap[id] = omap[id] + 1
--			else
--				omap[id] = 1
--				type_cnt = type_cnt + 1
--			end
            table.insert(omap,reward)
		end
	end

	--print("doAddItmeByTable, Type", type_cnt)
	if entity:getBagEmptyCnt()<#omap then
		return Error.Item_BagisFull
	end
	--if entity:getBagEmptyCnt()<type_cnt then
	--	return Error.Item_BagisFull
	--end

	for __, reward in pairs(omap) do
		--print("doAddItmeByTable, Add", id, cnt)
		if reward then
            local rew = reward
            if type(reward) == "table" then
                rew = reward[math.random(table.getn(reward))]
            end
			if bind then
				entity:addBindItem(rew, 1)
			else
				entity:addItem(rew, 1)
            end
        end
	end

	return Error.Success
end

local function checkMedicineCD(entity)
	local oldtime = entity:getProps(EP.attr_usemedicine_cd)
	local oldtime = entity:getProps(EP.attr_usemedicine_cd)
	local nowtime = os.time()
	if (nowtime-oldtime)>1 then
		return true
	end
	return false
end


--[[local function doAddExp(entity, rid, expcnt)
	if rid ~= 1 then
		local subentity = entity:getSubEntity(rid)
		if subentity then
			local canadd = subentity:addExp(expcnt)
			if canadd == 26 then
				return 38
			elseif canadd == 33 then
				return 41
			elseif canadd == 0 then
				return Error.Success
			end
			return 1
		end
		return 14
	else
		return 36 -- 36:主人物不可使用 37:副将不可使用
	end
end]]

--
--	新手礼包类
--

--10级新手礼包，包括20级新手礼包X1，10级武器,衣服X1，手镯X1，戒指X1，飞天鞋X5
gdItemExtension[30006] = {
	onUse = function(entity, rid, count)
	    local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local gender = entity:getGender()  -- 性别 男= 1 女= 2
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 7) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			if (gender == 1) then
				entity:addItem(70003,1 )
			elseif(gender == 2)then
				entity:addItem(70004, 1)
			end
		elseif (career == 2) then
			if (gender == 1) then
				entity:addItem(70209,1 )
			elseif(gender == 2)then
				entity:addItem(70210, 1)
			end
		elseif (career == 3) then
			if (gender == 1) then
				entity:addItem(70207,1 )
			elseif(gender == 2)then
				entity:addItem(70208, 1)
			end
		else
			log.error("item extenstion 30006, invalid static id")
		end

		entity:addItem(70026, 1)
		entity:addItem(70027, 1)
		entity:addItem(40046, 5)
		entity:addItem(38000, 1)
		entity:addItem(30007, 1)
		entity:addItem(70005, 1)
		return Error.Success
	end
}
--20级新手礼包，包括20级本职业的武器、衣服、头盔、项链、飞天鞋X10，30级新手礼包
gdItemExtension[30007] = {
	onUse = function(entity, rid, count)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local gender = entity:getGender()  -- 性别 男= 1 女= 2
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 6) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			entity:addItem(70006,1 )
			entity:addItem(70018,1 )
			entity:addItem(70019,1 )
			if (gender == 1) then
				entity:addItem(70011,1 )
			elseif(gender == 2)then
				entity:addItem(70012, 1)
			end
		elseif (career == 2) then
			entity:addItem(70175,1 )
			entity:addItem(70022,1 )
			entity:addItem(70176,1 )
			if (gender == 1) then
				entity:addItem(70013,1 )
			elseif(gender == 2)then
				entity:addItem(70014, 1)
			end
		elseif (career == 3) then
			entity:addItem(70017,1 )
			entity:addItem(70007,1 )
			entity:addItem(70008,1 )
			if (gender == 1) then
				entity:addItem(70015,1 )
			elseif(gender == 2)then
				entity:addItem(70016, 1)
			end
		end
		entity:addItem(40046, 10)
		entity:addItem(30008, 1)
		return Error.Success
	end
}
--30级新手礼包，包括30级本职业的武器、衣服、头盔、项链、飞天鞋X15、续命丹，35级新手礼包
gdItemExtension[30008] = {
	onUse = function(entity, rid, count)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local gender =  entity:getGender()  -- 性别 男= 1 女= 2
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 8) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			entity:addItem(70033,1 )
			entity:addItem(70037,1 )
			entity:addItem(70038,1 )
			if (gender == 1) then
				entity:addItem(70034,1 )
			elseif(gender == 2)then
				entity:addItem(70035, 1)
			end
		elseif (career == 2) then
			entity:addItem(70041,1 )
			entity:addItem(70043,1 )
			entity:addItem(70046,1 )
			if (gender == 1) then
				entity:addItem(70042,1 )
			elseif(gender == 2)then
				entity:addItem(70045, 1)
			end
		elseif (career == 3) then
			entity:addItem(70048,1 )
			entity:addItem(70051,1 )
			entity:addItem(70052,1 )
			if (gender == 1) then
				entity:addItem(70049,1 )
			elseif(gender == 2)then
				entity:addItem(70050, 1)
			end
		end
		entity:addItem(40046, 15)
		entity:addItem(40049, 1)
		entity:addItem(30009, 1)
		entity:addItem(40060, 2)
		return Error.Success
	end
}
--35级新手礼包，包括35级本职业的戒指、手镯、百年人参X1、百年雪莲X1、飞天鞋X20、百花争艳图X3、40级新手礼包
gdItemExtension[30009] = {
	onUse = function(entity, rid, count)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 7) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			entity:addItem(70073,1 )
			entity:addItem(70074,1 )
		elseif (career == 2) then
			entity:addItem(70060,1 )
			entity:addItem(70197,1 )
		elseif (career == 3) then
			entity:addItem(70064,1 )
			entity:addItem(70065,1 )
		end
		entity:addItem(40046, 20)
		entity:addItem(39015, 1)
		entity:addItem(39019, 1)
		entity:addItem(40050, 3)
		entity:addItem(30010, 1)
		return Error.Success
	end
}
--40级新手礼包，包括40级本职业套装手镯、黑铁矿X12、鉴定图X12、清洗砂X2、飞天鞋X20、斑斓石X3、战神油X1、45级新手礼包
gdItemExtension[30010] = {
	onUse = function(entity, rid, count)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 9) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			entity:addItem(60065,1 )
		elseif (career == 2) then
			entity:addItem(60125,1 )
		elseif (career == 3) then
			entity:addItem(60005,1 )
		end
		entity:addItem(40008, 12)
		entity:addItem(40060, 12)
		entity:addItem(40041, 2)
		entity:addItem(40046, 20)
		entity:addItem(30017, 1)
		entity:addItem(30011, 1)
		return Error.Success
	end
}
--45新手礼包，包括40级本职业戒指、仙玉X30、懒人令牌X2、副本通行证X2、宠物消费礼包、50级新手礼包
gdItemExtension[30011] = {
	onUse = function(entity, rid, count)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 5) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			entity:addItem(60209,1 )
		elseif (career == 2) then
			entity:addItem(60216,1 )
		elseif (career == 3) then
			entity:addItem(60202,1 )
		end
		entity:addItem(40047, 2)
		entity:addItem(40051, 2)
		entity:addItem(30279, 1)
		entity:addCoupon(30)
		entity:addItem(30012, 1)

		return Error.Success
	end
}
--50级新手礼包，包括陨铁勋章（1级）、50仙玉、飞天鞋X20、懒人令牌X3、副本通行证X3、魂石消费礼包、55级晋级礼包
gdItemExtension[30012] = {
	onUse = function(entity, rid, count)
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 6) then
			return Error.Item_BagisFull
	end
		entity:addItem(60266, 1)
		entity:addItem(40046, 20)
		entity:addItem(40047, 3)
		entity:addCoupon(50)
		entity:addItem(40051, 3)
		entity:addItem(30278, 1)
		entity:addItem(30013, 1)
		return Error.Success
	end
}
--55级晋级礼包，包括烈火令X2、50仙玉、3倍经验神符X1、5倍离线经验丹X2、懒人令牌X3、立即完成符X3、60级晋级礼包
gdItemExtension[30013] = {
	onUse = function(entity, rid, count)
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 6) then
			return Error.Item_BagisFull
	end
		entity:addItem(40037, 2)
		entity:addItem(30002, 1)
	--	entity:addBindItem(40067, 2)
		entity:addItem(40047, 3)
		entity:addCoupon(50)
	--	entity:addBindItem(40045, 3)
		entity:addItem(30014, 1)

		return Error.Success
	end
}
--60级晋级礼包，包括命运魔方、50仙玉、4倍经验神符、5倍离线经验丹、千年玄参X2、千年冰莲X2
gdItemExtension[30014] = {
	onUse = function(entity, rid, count)
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 5) then
			return Error.Item_BagisFull
	end
		entity:addItem(60259, 1)
		entity:addItem(30003, 1)
	--	entity:addBindItem(40067, 1)
		entity:addCoupon(50)
		entity:addItem(39016, 2)
		entity:addItem(39020, 2)

		return Error.Success
	end
}

--
--	烟花
--
gdItemExtension[30144] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30144)
		end
		return Error.Success
	end
}

gdItemExtension[30145] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30145)
		end
		return Error.Success
	end
}

gdItemExtension[30146] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30146)
		end
		return Error.Success
	end
}

gdItemExtension[30147] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30147)
		end
		return Error.Success
	end
}

gdItemExtension[30148] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30148)
		end
		return Error.Success
	end
}

gdItemExtension[30149] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30149)
		end
		return Error.Success
	end
}

gdItemExtension[30150] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30150)
		end
		return Error.Success
	end
}

gdItemExtension[30151] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30151)
		end
		return Error.Success
	end
}

gdItemExtension[30152] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30152)
		end
		return Error.Success
	end
}

gdItemExtension[30153] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30153)
		end
		return Error.Success
	end
}

gdItemExtension[30154] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30154)
		end
		return Error.Success
	end
}

gdItemExtension[30155] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30155)
		end
		return Error.Success
	end
}
gdItemExtension[30156] = {
	onUse = function(entity, rid, count)
		if entity:getLevel()<40 then
			return Error.NotEnoughLevel
		end
		--判断是否在土城
		local scene=entity:getScene()
		if scene then
			if scene:getStaticID()==3 then
				Event.useBlessTreeItem(entity,1)
			end
			gdFuncExtension[FP.item_use].ClientRequest(entity,30156)
		end
		return Error.Success
	end
}

local function gcz_check_tower(entity)	--攻城战根据箭塔数量降低吃药效果
	local scene = entity:getScene()
	if not scene then
		return 1
	end
	if scene:getID()~=180 then		--如果不是在沙皇宫
		if scene:getID() ~= 3 then	--如果也不是在土城
			return 1
		else
				--如果不在城墙内 return 1
		end
	end
	local guild = entity:getGuild()
	if not guild then
		return 1
	end
	if not guild:hasApplyGcz() then
		return 1		--如果没有报名攻城战
	end
	local mguildid = _G.getWorldDataX(EID.gcz)
	if not mguildid or mguildid<=0 then
		return 1		--如果沙城没有城主,或者攻城战没有开始
	end
	if mguildid==guild:getID() then
		return 1		--如果该玩家属于攻城方
	end
	--根据塔的数量计算系数
	local towercnt = scene:setProps(SP.gcz_tower_group_count)
	if not towercnt or towercnt<0 then
		towercnt=0
	end
	return (towercnt+1)/(6+1)
end
--
--	红瓶子
--
gdItemExtension[39000] = {
	onUse = function(entity, rid, count)
		entity:addGene(39000)
		return Error.Success
	end
}

gdItemExtension[39001] = {
	onUse = function(entity, rid, count)
		entity:addGene(39001)
		return Error.Success
	end
}

gdItemExtension[39002] = {
	onUse = function(entity, rid, count)
		entity:addGene(39002)
		return Error.Success
	end
}

gdItemExtension[39003] = {
	onUse = function(entity, rid, count)
		entity:addGene(39003)
		return Error.Success
	end
}
--
--人参
--
gdItemExtension[39015] = {
	onUse = function(entity, rid, count)
		entity:addGene(39004)
		return Error.Success
	end
}

gdItemExtension[39016] = {
	onUse = function(entity, rid, count)
		entity:addGene(39005)
		return Error.Success
	end
}

gdItemExtension[39017] = {
	onUse = function(entity, rid, count)
		entity:addGene(39006)
		return Error.Success
	end
}

gdItemExtension[39018] = {
	onUse = function(entity, rid, count)
		entity:addGene(39007)
		return Error.Success
	end
}

--玄武丹
gdItemExtension[39036] = {
	onUse = function(entity, rid, count)
		entity:addGene(39008)
		return Error.Success
	end
}
--
--	蓝瓶子
--
gdItemExtension[39004] = {
	onUse = function(entity, rid, count)
		entity:addGene(39010)
		return Error.Success
	end
}

gdItemExtension[39005] = {
	onUse = function(entity, rid, count)
		entity:addGene(39011)
		return Error.Success
	end
}

gdItemExtension[39006] = {
	onUse = function(entity, rid, count)
		entity:addGene(39012)
		return Error.Success
	end
}

gdItemExtension[39007] = {
	onUse = function(entity, rid, count)
		entity:addGene(39013)
		return Error.Success
	end
}
--
--雪莲
--
gdItemExtension[39019] = {
	onUse = function(entity, rid, count)
		entity:addGene(39014)
		return Error.Success
	end
}

gdItemExtension[39020] = {
	onUse = function(entity, rid, count)
		entity:addGene(39015)
		return Error.Success
	end
}

gdItemExtension[39021] = {
	onUse = function(entity, rid, count)
		entity:addGene(39016)
		return Error.Success
	end
}

gdItemExtension[39022] = {
	onUse = function(entity, rid, count)
		entity:addGene(39017)
		return Error.Success
	end
}

--
-- 青龙丹
gdItemExtension[39037] = {
	onUse = function(entity, rid, count)
		entity:addGene(39018)
		return Error.Success
	end
}
--
--	太阳药水
--
gdItemExtension[39008] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(720)
				cbt:updateMP(960)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
gdItemExtension[39009] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(1200)
				cbt:updateMP(1920)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
gdItemExtension[39040] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(1200)
				cbt:updateMP(3840)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
--
--雪霜膏
--
gdItemExtension[39013] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(960)
				cbt:updateMP(720)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
gdItemExtension[39014] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(1920)
				cbt:updateMP(1200)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
gdItemExtension[39041] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(3840)
				cbt:updateMP(1200)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
--
--红玫瑰
--
gdItemExtension[39029] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(7200)
				cbt:updateMP(11520)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
gdItemExtension[39043] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(28600)
				cbt:updateMP(28600)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
gdItemExtension[39042] = {
	onUse = function(entity, rid, count)
		if checkMedicineCD(entity) then
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(18600)
				cbt:updateMP(18600)
				entity:setProps(EP.attr_usemedicine_cd,os.time())
				return Error.Success
			end
			return Error.InvalidEntity
		end
		return Error.Item_MedicineCDLocked
	end
}
---
---	  宠物
---
gdItemExtension[38000] = {
	onUse = function(entity,rid,count)
		return entity:addPet(10000,"")
	--	return Error.Success
	end
}

gdItemExtension[38001] = {
	onUse = function(entity,rid,count)
		return entity:addPet(10001,"")
	--	return Error.Success
	end
}

gdItemExtension[38002] = {
	onUse = function(entity,rid,count)
		--entity:addPet(rid,"")
		-- to do
		-- unimprison pet !
		return entity:releaseImprisonPet(rid)
	end
}


gdItemExtension[38003] = {
	onUse = function(entity,rid,count)
		return entity:addPet(10003,"")
	--	return Error.Success
	end
}
gdItemExtension[38004] = {              --悟空
	onUse = function(entity,rid,count)
		return entity:addPet(10004,"")
	--	return Error.Success
	end
}
gdItemExtension[38005] = {              --八戒
	onUse = function(entity,rid,count)
		return entity:addPet(10005,"")
	--	return Error.Success
	end
}
--
--     经验神符
--
gdItemExtension[30000] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39020) --加上杀怪额外获得原经验的50%
		return Error.Success
	end
}

gdItemExtension[30001] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39021) --加上杀怪额外获得原经验的100%
		return Error.Success
	end
}

gdItemExtension[30002] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39022) --加上杀怪额外获得原经验的200%
		return Error.Success
	end
}

gdItemExtension[30003] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39023) --加上杀怪额外获得原经验的300%
		return Error.Success
	end
}

gdItemExtension[30005] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39024) --加上杀怪额外获得原经验的400%
		return Error.Success
	end
}

gdItemExtension[30054] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39025) --加上杀怪额外获得原经验的500%
		return Error.Success
	end
}

gdItemExtension[30004] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39026) --加上杀怪额外获得原经验的700%
		return Error.Success
	end
}

gdItemExtension[30055] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39027) --加上杀怪额外获得原经验的900%
		return Error.Success
	end
}

--8小时经验神符
--
gdItemExtension[30158] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39028) --加上杀怪额外获得原经验的50%
		return Error.Success
	end
}

gdItemExtension[30159] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39029) --加上杀怪额外获得原经验的100%
		return Error.Success
	end
}



gdItemExtension[30160] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39030) --加上杀怪额外获得原经验的200%
		return Error.Success
	end
}

gdItemExtension[30161] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39031) --加上杀怪额外获得原经验的300%
		return Error.Success
	end
}

gdItemExtension[30165] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39032) --加上杀怪额外获得原经验的400%
		return Error.Success
	end
}

gdItemExtension[30162] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39033) --加上杀怪额外获得原经验的500%
		return Error.Success
	end
}

gdItemExtension[30163] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39034) --加上杀怪额外获得原经验的700%
		return Error.Success
	end
}

gdItemExtension[30164] = {
	onUse = function(entity, rid, count)
		local gene = gdGenes[100]		-- 杀怪经验buff Gene
		entity:addGene(39035) --加上杀怪额外获得原经验的900%
		return Error.Success
	end
}



--
--		篝火经验
--
gdItemExtension[30052] = {
	onUse = function(entity,rid, count)
		local event = gdEventData[2]   -- 获取篝火活动
		if event and Event.isActive(2) then  -- 检查篝火活动是否开始

			--
			--	计算篝火活动剩余时间确定 buff的持续时间
			--
			local timetable = os.date("*t")
			timetable.sec = 0
			local now = os.time(timetable)
			duration = Event.getStopTime(2) - now

			-- local gene = gdGenes[101] -- 篝火经验buff Gene
			entity:addGene(39037) -- 加上篝火额外获得原经验的100% buff
			return Error.Success
		end
		return Error.InvalidEntity
	end
}

gdItemExtension[30053] = {
	onUse = function(entity,rid, count)
		local event = gdEventData[2]   -- 获取篝火活动
		if event and Event.isActive(2) then  -- 检查篝火活动是否开始

			--
			--	计算篝火活动剩余时间确定 buff的持续时间
			--
			local timetable = os.date("*t")
			timetable.sec = 0
			local now = os.time(timetable)
			duration = Event.getStopTime(2) - now

			-- local gene = gdGenes[101] -- 篝火经验buff Gene
			entity:addGene(39038) -- 加上篝火额外获得原经验的50% buff
			return Error.Success
		end
		return Error.InvalidEntity
	end
}
gdItemExtension[123123] = {
	onUse = function(entity,rid, count)
		local event = gdEventData[2]   -- 获取篝火活动
		if event and Event.isActive(2) then  -- 检查篝火活动是否开始

			--
			--	计算篝火活动剩余时间确定 buff的持续时间
			--
			local timetable = os.date("*t")
			timetable.sec = 0
			local now = os.time(timetable)
			duration = Event.getStopTime(2) - now

			-- local gene = gdGenes[101] -- 篝火经验buff Gene
			entity:addGene(39039) -- 加上篝火额外获得原经验的50% buff
			return Error.Success
		end
		return Error.InvalidEntity
	end
}
---
---	生命药水
gdItemExtension[39030] =
{
	onUse =  function(entity,rid,count)
		entity:addGene(39040)
		return Error.Success
	end
}
gdItemExtension[39031] =
{
	onUse =  function(entity,rid,count)
		entity:addGene(39041)
		return Error.Success
	end
}
gdItemExtension[39032] =
{
	onUse =  function(entity,rid,count)
		entity:addGene(39042)
		return Error.Success
	end
}
--- 魔法药水
gdItemExtension[39033] =
{
	onUse =  function(entity,rid,count)
		entity:addGene(39044)
		return Error.Success
	end
}
gdItemExtension[39034] =
{
	onUse =  function(entity,rid,count)
		entity:addGene(39045)
		return Error.Success
	end
}
gdItemExtension[39035] =
{
	onUse =  function(entity,rid,count)
		entity:addGene(39046)
		return Error.Success
	end
}
--- 攻击药水
gdItemExtension[39023] =
{
	onUse = function(entity,rid,count)
		entity:addGene(39048)
		return Error.Success
	end
}
gdItemExtension[39024] =
{
	onUse = function(entity,rid,count)
		entity:addGene(39049)
		return Error.Success
	end
}
gdItemExtension[39038] =
{
	onUse = function(entity,rid,count)
		entity:addGene(39050)
		return Error.Success
	end
}
---防御药水
gdItemExtension[39025] =
{
	onUse = function(entity,rid,count)
		entity:addGene(39052)
		return Error.Success
	end
}
gdItemExtension[39026] =
{
	onUse = function(entity,rid,count)
		entity:addGene(39053)
		return Error.Success
	end
}
gdItemExtension[39027] =
{
	onUse = function(entity,rid,count)
		entity:addGene(39054)
		return Error.Success
	end
}
---
---行会资金
---
-- gdItemExtension[30028] =
-- {
	-- onUse = function(entity,rid,count)
		-- local scene = entity:getScene()
		-- local sd = gdMaps[scene:getStaticID()]
		-- if sd.type == 1 then
			-- local eu = gdFuncExtension[FuncProp.guild_call]
			-- if eu and eu.ClientRequest then
				 -- return eu.ClientRequest(entity)
			-- end
		-- else
			-- return Error.InvalidScene
		-- end
		-- return Error.Unknown
	-- end
-- }
gdItemExtension[30028] =
{
	onUse = function(entity, rid, count)
		local scene = entity:getScene()
		local mapId = scene:getStaticID()

		if gdGuildCallForbiddenMaps and gdGuildCallForbiddenMaps[mapId] then
			return Error.InvalidScene
		end

		local sd = gdMaps[mapId]
		if sd.type == 1 then
			local eu = gdFuncExtension[FuncProp.guild_call]
			if eu and eu.ClientRequest then
				return eu.ClientRequest(entity)
			end
		else
			return Error.InvalidScene
		end
		return Error.Unknown
	end
}
gdItemExtension[30033] =
{
	onUse = function(entity,rid,count)
		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		entity:addGuildContribution(1, true)
		local money = guild:getProps(GuildProp.guild_money)
		guild:setProps(GuildProp.guild_money, money + 10000)
		guild:syncProps(GuildProp.guild_money)
		guild:saveProps(GuildProp.guild_money)
		return Error.Success
	end
}
gdItemExtension[30034] =
{
	onUse = function(entity,rid,count)
		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		entity:addGuildContribution(5, true)
		local money = guild:getProps(GuildProp.guild_money)
		guild:setProps(GuildProp.guild_money, money + 50000)
		guild:syncProps(GuildProp.guild_money)
		guild:saveProps(GuildProp.guild_money)
		return Error.Success
	end
}
gdItemExtension[30171] =
{
	onUse = function(entity,rid,count)
		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		entity:addGuildContribution(50, true)
		local money = guild:getProps(GuildProp.guild_money)
		guild:setProps(GuildProp.guild_money, money + 500000)
		guild:syncProps(GuildProp.guild_money)
		guild:saveProps(GuildProp.guild_money)

		return Error.Success
	end
}
gdItemExtension[30062] =
{
	onUse = function(entity,rid,count)
		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		entity:addGuildContribution(10, true)
		local money = guild:getProps(GuildProp.guild_money)
		guild:setProps(GuildProp.guild_money, money + 100000)
		guild:syncProps(GuildProp.guild_money)
		guild:saveProps(GuildProp.guild_money)
		return Error.Success
	end
}
---
---各种物品包
---
gdItemExtension[30057] = {					--黑铁包
	onUse = function(entity, rid, count)
	local ItemCnt = 10
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(40008, 99)
		return Error.Success
	end
}
gdItemExtension[30070] = {					--绿宝石包
	onUse = function(entity, rid, count)
	local	ItemCnt = 2
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(40009, 99)
		return Error.Success
	end
}
gdItemExtension[30071] = {					--紫水晶包
	onUse = function(entity, rid, count)
	local ItemCnt = 10
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(40010, 99)
		return Error.Success
	end
}
gdItemExtension[30167] = {					--开天之翼包
	onUse = function(entity, rid, count)
	local ItemCnt = 10
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(80001, 10)
		return Error.Success
	end
}
gdItemExtension[30168] = {					--影魅之翼包
	onUse = function(entity, rid, count)
	local ItemCnt = 10
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(80004, 10)
		return Error.Success
	end
}
gdItemExtension[30193] = {					--每日首冲礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 10
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(80001, 10)
		return Error.Success
	end
}
gdItemExtension[30223] = {					--冠军猎手礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(40053, 15)
		entity:addBindItem(30163, 1)
		entity:addBindItem(40011,8)
		entity:addBindItem(40012, 8)
		entity:addBindItem(40116,6)
		return Error.Success
	end
}
gdItemExtension[30224] = {					--精英猎手礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 4
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(40053, 10)
		entity:addBindItem(30162, 1)
		entity:addBindItem(40011, 4)
		entity:addBindItem(40012, 4)
		return Error.Success
	end
}
gdItemExtension[30225] = {					--猎手大礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 3
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(40053, 5)
		entity:addBindItem(30161, 1)
		entity:addBindItem(40011, 2)
		return Error.Success
	end
}
gdItemExtension[30227] = {					--装备小强包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		doAddItemByTable(entity,{40009,40010,40012,40041,40042,40054,40055,40056})
		return Error.Success
	end
}
gdItemExtension[30228] = {					--日常药水包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		doAddItemByTable(entity,{30017,40049,39015,39019,39031,39026})
		return Error.Success
	end
}
gdItemExtension[30031] = {					--翅膀礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(80001)
		return Error.Success
	end
}

gdItemExtension[30169] = {					--魂石玉盒
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			entity:addBindItem(10018,9)
		elseif (career == 2) then
			entity:addBindItem(10019,9)
		elseif (career == 3) then
			entity:addBindItem(10020,9)
	end
		return Error.Success
	end
}

gdItemExtension[30170] = {					--便携挂机包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addBindItem(30161,1)
	entity:addBindItem(39016,8)
	entity:addBindItem(39020,8)
	entity:addBindItem(39027,8)
	entity:addBindItem(30017,8)
		return Error.Success
	end
}

gdItemExtension[30180] = {					--天宫结婚礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addItem(70179,2)
	entity:addItem(81086,1)
	entity:addItem(81092,1)
	entity:addItem(30144,20)
	entity:addItem(30156,20)
		return Error.Success
	end
}

gdItemExtension[30181] = {					--中式结婚礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addItem(70179,2)
	entity:addItem(81066,1)
	entity:addItem(81076,1)
	entity:addItem(30144,9)
	entity:addItem(30155,9)
		return Error.Success
	end
}

gdItemExtension[30182] = {					--西式结婚礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addItem(70179,2)
	entity:addItem(81109,1)
	entity:addItem(81119,1)
	entity:addItem(30144,9)
	entity:addItem(30155,9)
		return Error.Success
	end
}

gdItemExtension[30186] = {					--战士5级魂石包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addItem(10039,1)
	entity:addItem(10037,1)
	entity:addItem(10038,1)
	entity:addItem(10035,1)
	entity:addItem(10036,1)
		return Error.Success
	end
}

gdItemExtension[30187] = {					--法师5级魂石包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addItem(10040,1)
	entity:addItem(10037,1)
	entity:addItem(10038,1)
	entity:addItem(10035,1)
	entity:addItem(10036,1)
		return Error.Success
	end
}
gdItemExtension[30188] = {					--道士5级魂石包
	onUse = function(entity, rid, count)
	local ItemCnt = 5
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addItem(10041,1)
	entity:addItem(10037,1)
	entity:addItem(10038,1)
	entity:addItem(10035,1)
	entity:addItem(10036,1)
		return Error.Success
	end
}
gdItemExtension[30193] = {					--每日首冲礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 4
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addBindItem(40037,2)
	entity:addBindItem(30054,1)
	entity:addBindItem(30046,2)
	entity:addItem(39029,3)
		return Error.Success
	end
}

gdItemExtension[30194] = {					--每日千元礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 4
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	entity:addItem(39043,3)
	entity:addBindItem(30004,3)
	entity:addBindItem(30191,1)
	entity:addBindItem(40037,2)
		return Error.Success
	end
}

gdItemExtension[30195] = {					--神秘奖励礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
	doAddItemByTable(entity, {30018,30064,40051,40047,39029}, 1)
		return Error.Success
	end
}

gdItemExtension[30196] = {					--超级药水包
	onUse = function(entity, rid, count)
	local ItemCnt = 3
	local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
	local embag  = entity:getBagEmptyCnt()
	if (embag < ItemCnt) then
			return Error.Item_BagisFull
		elseif (career == 1) then
			entity:addItem(39014,10)
		elseif (career == 2) then
			entity:addItem(39009,10)
		elseif (career == 3) then
			entity:addItem(39009,10)
	end
	entity:addItem(39003,20)
	entity:addItem(39007,20)
		return Error.Success
	end
}

gdItemExtension[30259] = {					--60级套装礼包
	onUse = function(entity, rid, count)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local gender = entity:getGender()  -- 性别 男= 1 女= 2
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local imap = {}
		if (career == 1) then
			if (gender == 1) then
				imap = {
					[60100] = 1;
					[60101] = 1;
					[60104] = 1;
					[60105] = 1;
					[60106] = 1;
					[60107] = 1;
					[60108] = 1;
					[60102] = 1;
				}
			elseif(gender == 2)then
				imap = {
					[60100] = 1;
					[60101] = 1;
					[60104] = 1;
					[60105] = 1;
					[60106] = 1;
					[60107] = 1;
					[60108] = 1;
					[60103] = 1;
				}
			end
			doAddItemByWeight(entity, imap)
		elseif (career == 2) then
			if (gender == 1) then
				imap = {
					[60160] = 1;
					[60161] = 1;
					[60164] = 1;
					[60165] = 1;
					[60166] = 1;
					[60167] = 1;
					[60168] = 1;
					[60162] = 1;
				}
			elseif(gender == 2)then
				imap = {
					[60160] = 1;
					[60161] = 1;
					[60164] = 1;
					[60165] = 1;
					[60166] = 1;
					[60167] = 1;
					[60168] = 1;
					[60163] = 1;
				}
			end
			doAddItemByWeight(entity, imap)
		elseif (career == 3) then
			if (gender == 1) then
				imap = {
					[60040] = 1;
					[60041] = 1;
					[60044] = 1;
					[60045] = 1;
					[60046] = 1;
					[60047] = 1;
					[60048] = 1;
					[60042] = 1;
				}
			elseif(gender == 2)then
				imap = {
					[60040] = 1;
					[60041] = 1;
					[60044] = 1;
					[60045] = 1;
					[60046] = 1;
					[60047] = 1;
					[60048] = 1;
					[60043] = 1;
				}
			end
			doAddItemByWeight(entity, imap)
		end
		return Error.Success
	end,
}

gdItemExtension[30260] = {					--70级套装礼包
	onUse = function(entity, rid, count)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local gender = entity:getGender()  -- 性别 男= 1 女= 2
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local imap = {}
		if (career == 1) then
			if (gender == 1) then
				imap = {
				[60110] = 1;
				[60111] = 1;
				[60114] = 1;
				[60115] = 1;
				[60116] = 1;
				[60117] = 1;
				[60118] = 1;
				[60112] = 1;
				}
			elseif(gender == 2)then
				imap = {
				[60110] = 1;
				[60111] = 1;
				[60114] = 1;
				[60115] = 1;
				[60116] = 1;
				[60117] = 1;
				[60118] = 1;
				[60113] = 1;
				}
			end
		doAddItemByWeight(entity, imap)
		elseif (career == 2) then
			if (gender == 1) then
				imap = {
				[60170] = 1;
				[60171] = 1;
				[60174] = 1;
				[60175] = 1;
				[60176] = 1;
				[60177] = 1;
				[60178] = 1;
				[60172] = 1;
				}
			elseif(gender == 2)then
				imap = {
				[60170] = 1;
				[60171] = 1;
				[60174] = 1;
				[60175] = 1;
				[60176] = 1;
				[60177] = 1;
				[60178] = 1;
				[60173] = 1;
				}
			end
		doAddItemByWeight(entity, imap)
		elseif (career == 3) then
			if (gender == 1) then
				imap = {
				[60050] = 1;
				[60051] = 1;
				[60054] = 1;
				[60055] = 1;
				[60056] = 1;
				[60057] = 1;
				[60058] = 1;
				[60052] = 1;
				}
			elseif(gender == 2)then
				imap = {
				[60050] = 1;
				[60051] = 1;
				[60054] = 1;
				[60055] = 1;
				[60056] = 1;
				[60057] = 1;
				[60058] = 1;
				[60053] = 1;
				}
			end
		doAddItemByWeight(entity, imap)
		end
		return Error.Success
	end
}

gdItemExtension[30262] = {					--翅膀礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(80001)
		return Error.Success
	end
}

gdItemExtension[30237] = {					--寻宝1
	onUse = function(entity, rid, count)
	local ItemCnt = 2
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(30199, 1)
		entity:addBindItem(30005, 1)
		return Error.Success
	end
}

gdItemExtension[30238] = {					--寻宝2
	onUse = function(entity, rid, count)
	local ItemCnt = 2
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(30054, 1)
		entity:addBindItem(30191, 1)
		return Error.Success
	end
}

gdItemExtension[30239] = {					--寻宝3
	onUse = function(entity, rid, count)
	local ItemCnt = 2
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(30004, 1)
		entity:addBindItem(30192, 1)
		return Error.Success
	end
}

gdItemExtension[30240] = {					--寻宝4
	onUse = function(entity, rid, count)
	local ItemCnt = 2
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(30055, 1)
		entity:addBindItem(30192, 2)
		return Error.Success
	end
}

gdItemExtension[30241] = {					--寻宝5
	onUse = function(entity, rid, count)
	local ItemCnt = 2
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(30055, 2)
		entity:addBindItem(30005, 4)
		return Error.Success
	end
}
gdItemExtension[30262] = {					--宠物跃升大礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addHonor(20000)
		entity:addBindItem(40053, 4)
		return Error.Success
	end
}

gdItemExtension[30263] = {					--代金卡大礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 3
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(40000, 10)
		entity:addItem(40072, 5)
		entity:addItem(40074, 3)
		return Error.Success
	end
}

gdItemExtension[30264] = {					--消费回馈礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 4
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(40007, 1)
		entity:addItem(10030, 1)
		entity:addItem(10031, 1)
		entity:addItem(40074, 6)
		return Error.Success
	end
}

gdItemExtension[30265] = {					--zhanlihuoyue礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addCoupon(100)
		entity:addBindItem(40012, 20)
		return Error.Success
	end
}

gdItemExtension[30266] = {					--qianghua礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addCoupon(200)
		entity:addBindItem(40012, 3)
		return Error.Success
	end
}

gdItemExtension[30267] = {					--5jihunshi礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 2
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(10035, 1)
		entity:addBindItem(10036, 1)
		return Error.Success
	end
}

gdItemExtension[30268] = {					--lingshi礼包
	onUse = function(entity, rid, count)
	local ItemCnt = 3
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addBindItem(40000, 10)
		entity:addBindItem(40001, 10)
		entity:addBindItem(40072, 1)
		return Error.Success
	end
}

gdItemExtension[30275] = {					--facai礼包1
	onUse = function(entity, rid, count)
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local lootid = gdLootnametoID["发财礼包1级"]
		if lootid then
			Loot.callReward(nil,entity,lootid,Opcode.LootItemBind)
			return Error.Success
		end
		return Error.Script
	end
}

gdItemExtension[30276] = {					--facai礼包2
	onUse = function(entity, rid, count)
		local lootid = gdLootnametoID["发财礼包2级"]
		if lootid then
			Loot.callReward(nil,entity,lootid,Opcode.LootItemBind)
			return Error.Success
		end
		return Error.Script
	end
}

gdItemExtension[30277] = {					--facai礼包3
	onUse = function(entity, rid, count)
		local lootid = gdLootnametoID["发财礼包3级"]
		if lootid then
			Loot.callReward(nil,entity,lootid,Opcode.LootItemBind)
			return Error.Success
		end
		return Error.Script
	end,
}

gdItemExtension[30176] = {					--行会宝印
	onUse = function(entity, rid, count)
		local ItemCnt = 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		local m = math.random(4)
		entity:addHonor(10000)
		entity:addItem(39015,1)
		entity:addItem(39019,1)
		if (m <= 1) then
		entity:addBindItem(39038, 1)
		elseif (m <= 2) then
		entity:addBindItem(39027, 1)
		elseif (m <= 2) then
		entity:addBindItem(39030, 1)
		else
		entity:addBindItem(39033, 1)
		end
		return Error.Success
	end,
}

gdItemExtension[30172] = {					--小红包
	onUse = function(entity, rid, count)
	entity:addMoney(100000)
		return Error.Success
	end
}

gdItemExtension[30173] = {					--红包
	onUse = function(entity, rid, count)
	entity:addMoney(500000)
		return Error.Success
	end
}

gdItemExtension[30174] = {					--大红包
	onUse = function(entity, rid, count)
	entity:addMoney(1000000)
		return Error.Success
	end
}
--消耗型物品包
gdItemExtension[30274] = {					--新服经验大礼包
	onUse = function(entity, rid, count)
		local ItemCnt = 4
		local embag  = entity:getBagEmptyCnt()
		if entity:getGold()<68 then
			return Error.NotEnoughGold
		elseif (embag < ItemCnt) then
			return Error.Item_BagisFull
			else
				entity:useGold(68, Opcode.use_xinfu_jingyanx_dalibao)
				entity:addBindItem(30199,1)
				entity:addBindItem(30060,1)
				entity:addBindItem(30004,1)
				entity:addBindItem(30206,1)
			return Error.Success
		end
	end,
}
--代金卡、在弹出确认框之后使用
gdItemExtension[30270] = -- 灵石代金卡
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
	if entity:getGold()<130 then
		return Error.NotEnoughGold
	elseif (embag < ItemCnt) then
		return Error.Item_BagisFull
		else
			entity:useGold(130, Opcode.use_lingshi_daijing_card)
			entity:addItem(40000,10)
		return Error.Success
	end
	end,
}

gdItemExtension[30272] = -- 魂石代金卡
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
	local embag  = entity:getBagEmptyCnt()
	if entity:getGold()<173 then
		return Error.NotEnoughGold
	elseif (embag < ItemCnt) then
		return Error.Item_BagisFull
		elseif (career == 1) then
			entity:useGold(173, Opcode.use_hunshi_daijin_card)
			entity:addItem(10039,1)
			elseif (career ==2) then
			entity:useGold(173, Opcode.use_hunshi_daijin_card)
			entity:addItem(10040,1)
			else
			entity:useGold(173, Opcode.use_hunshi_daijin_card)
			entity:addItem(10041,1)
	end
	return Error.Success
	end,
}

gdItemExtension[30271] = -- 宠物代金卡
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
	if entity:getGold()<690 then
		return Error.NotEnoughGold
	elseif (embag < ItemCnt) then
		return Error.Item_BagisFull
		else
			entity:useGold(690, Opcode.use_pet_daijin_card)
			entity:addItem(40053,99)
		return Error.Success
	end
	end,
}

gdItemExtension[30273] = -- 时装代金卡
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local gender = entity:getGender()  -- 性别 男= 1 女= 2
	local embag  = entity:getBagEmptyCnt()
	if entity:getGold()<208 then
		return Error.NotEnoughGold
	elseif (embag < ItemCnt) then
		return Error.Item_BagisFull
	end
	if (gender == 1) then
		entity:useGold(208, Opcode.use_fashion_daijin_card)
		entity:addItem(81044,1)
	elseif (gender == 2) then
		entity:useGold(208, Opcode.use_fashion_daijin_card)
		entity:addItem(81055,1)
	end
	return Error.Success
	end,
}

gdItemExtension[30278] = -- 魂石消费礼包
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
	local embag  = entity:getBagEmptyCnt()
	if entity:getCoupon()<168 then
		return Error.NotEnoughDiamond
	elseif (embag < ItemCnt) then
		return Error.Item_BagisFull
	elseif (career == 1) then
		entity:useCoupon(168)
		entity:addBindItem(10025,3)
	elseif (career ==2) then
		entity:useCoupon(168)
		entity:addBindItem(10026,3)
	else
		entity:useCoupon(168)
		entity:addBindItem(10027,3)
	end
	return Error.Success
	end,
}

gdItemExtension[30279] = -- 宠物消费礼包
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()
	if entity:getCoupon()<88 then
		return Error.NotEnoughDiamond
	elseif (embag < ItemCnt) then
			return Error.Item_BagisFull
		else
			entity:useCoupon(88)
			entity:addBindItem(40053,6)
	end
	return Error.Success
	end,
}
---技能书
gdItemExtension[30097] = {					--基础剑法
	onUse = function(entity, rid, count)
		return entity:studySkill(101)
	end,
}
gdItemExtension[30098] = {					--基础剑法4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(103) == 1) then
			return entity:studySkill(104)
		end
		return Error.Combat_Skill_LevelNotEnough
	end,
}
gdItemExtension[30101] = {					--烈焰剑法
	onUse = function(entity, rid, count)
			return entity:studySkill(111)
	end,
}
gdItemExtension[30102] = {					--烈焰剑法4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(113) == 1) then
			return entity:studySkill(114)
		end
		return Error.Combat_Skill_LevelNotEnough
	end,
}
gdItemExtension[30103] = {					--烈焰剑法5
	onUse = function(entity, rid, count)
		if (entity:hasSkill(114) == 1) then
			return entity:studySkill(115)
		end
		return Error.Combat_Skill_LevelNotEnough
	end,
}
gdItemExtension[31111] = {					--火焰斩化神
	onUse = function(entity, rid, count)
		if (entity:hasSkill(115) == 1) then
			return entity:studySkill(116)
		end
		return Error.Combat_Skill_LevelNotEnough
	end,
}
gdItemExtension[30104] = {					--弦月剑法
	onUse = function(entity, rid, count)
		return entity:studySkill(121)
	end,
}
gdItemExtension[30105] = {					--弦月剑法4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(123) == 1) then
			return entity:studySkill(124)
		end
		return Error.Combat_Skill_LevelNotEnough
	end,
}
gdItemExtension[30106] = {					--刺杀秘剑
	onUse = function(entity, rid, count)
		return entity:studySkill(131)
	end
}
gdItemExtension[30107] = {					--刺杀秘剑4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(133) == 1) then
			return entity:studySkill(134)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30138] = {					--战神冲撞
	onUse = function(entity, rid, count)
		return entity:studySkill(141)
	end
}
gdItemExtension[30139] = {					--战神冲撞4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(143) == 1) then
			return entity:studySkill(144)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30140] = {					--战神冲撞筑基
	onUse = function(entity, rid, count)
		if (entity:hasSkill(144) == 1) then
			return entity:studySkill(145)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30110] = {					--火墙术
	onUse = function(entity, rid, count)
		return entity:studySkill(201)
	end
}
gdItemExtension[30111] = {					--火墙术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(203) == 1) then
			return entity:studySkill(204)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[31113] = {					--火墙术化神
	onUse = function(entity, rid, count)
		if (entity:hasSkill(204) == 1) then
			return entity:studySkill(205)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30112] = {					--火球术
	onUse = function(entity, rid, count)
		return entity:studySkill(211)
	end
}
gdItemExtension[30113] = {					--火球术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(213) == 1) then
			return entity:studySkill(214)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30114] = {					--天雷术
	onUse = function(entity, rid, count)
		return entity:studySkill(221)
	end
}
gdItemExtension[30115] = {					--天雷术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(223) == 1) then
			return entity:studySkill(224)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30116] = {					--法术抗拒
	onUse = function(entity, rid, count)
		return entity:studySkill(231)
	end
}
gdItemExtension[30117] = {					--法术抗拒4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(233) == 1) then
			return entity:studySkill(234)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30118] = {					--穿透闪电
	onUse = function(entity, rid, count)
		return entity:studySkill(241)
	end
}
gdItemExtension[30119] = {					--穿透闪电4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(243) == 1) then
			return entity:studySkill(244)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30120] = {					--冰风暴
	onUse = function(entity, rid, count)
		return entity:studySkill(261)
	end
}
gdItemExtension[30121] = {					--冰风暴4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(263) == 1) then
			return entity:studySkill(264)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30122] = {					--冰风暴5
	onUse = function(entity, rid, count)
		if (entity:hasSkill(264) == 1) then
			return entity:studySkill(265)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30123] = {					--魔法护盾
	onUse = function(entity, rid, count)
		return entity:studySkill(271)
	end
}
gdItemExtension[30124] = {					--魔法护盾4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(273) == 1) then
			return entity:studySkill(274)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30125] = {					--群体恢复术
	onUse = function(entity, rid, count)
		return entity:studySkill(301)
	end
}
gdItemExtension[30126] = {					--群体恢复术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(303) == 1) then
			return entity:studySkill(304)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30127] = {					--符咒术
	onUse = function(entity, rid, count)
		return entity:studySkill(311)
	end
}
gdItemExtension[30128] = {					--符咒术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(313) == 1) then
			return entity:studySkill(314)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30129] = {					--符咒术5
	onUse = function(entity, rid, count)
		if (entity:hasSkill(314) == 1) then
			return entity:studySkill(315)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30137] = {					--群体恢复术筑基
onUse = function(entity, rid, count)
		if (entity:hasSkill(304) == 1) then
			return entity:studySkill(305)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30099] = {					--毒药术
	onUse = function(entity, rid, count)
		return entity:studySkill(321)
	end
}
gdItemExtension[30100] = {					--毒药术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(323) == 1) then
			return entity:studySkill(324)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[31116] = {					--毒药术化神
	onUse = function(entity, rid, count)
		if (entity:hasSkill(324) == 1) then
			return entity:studySkill(325)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30130] = {					--群体隐遁术
	onUse = function(entity, rid, count)
		return entity:studySkill(331)
	end
}
gdItemExtension[30131] = {					--群体隐遁术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(333) == 1) then
			return entity:studySkill(334)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30132] = {					--灵魂锻炼术
	onUse = function(entity, rid, count)
		return entity:studySkill(341)
	end
}
gdItemExtension[30133] = {					--灵魂锻炼术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(343) == 1) then
			return entity:studySkill(344)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30134] = {					--神圣幽灵护盾术
	onUse = function(entity, rid, count)
		return entity:studySkill(351)
	end
}
gdItemExtension[30135] = {					--神圣幽灵护盾术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(353) == 1) then
			return entity:studySkill(354)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30136] = {					--召唤术
	onUse = function(entity, rid, count)
		return entity:studySkill(361)
	end
}
gdItemExtension[30366] = {					--召唤术4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(363) == 1) then
			return entity:studySkill(364)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30367] = {					--召唤术5
	onUse = function(entity, rid, count)
		if (entity:hasSkill(364) == 1) then
			return entity:studySkill(365)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}

gdItemExtension[30073] = {					--烈焰重生1
	onUse = function(entity, rid, count)
		return entity:studySkill(151)
	end
}

gdItemExtension[30074] = {					--烈焰重生2
	onUse = function(entity, rid, count)
		if (entity:hasSkill(151) == 1) then
			return entity:studySkill(152)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30075] = {					--烈焰重生3
	onUse = function(entity, rid, count)
		if (entity:hasSkill(152) == 1) then
			return entity:studySkill(153)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30076] = {					--烈焰重生4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(153) == 1) then
			return entity:studySkill(154)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30077] = {					--烈焰重生5
	onUse = function(entity, rid, count)
		if (entity:hasSkill(154) == 1) then
			return entity:studySkill(155)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}

gdItemExtension[30078] = {					--瞬移1
	onUse = function(entity, rid, count)
		return entity:studySkill(281)
	end
}
gdItemExtension[30079] = {					--瞬移2
	onUse = function(entity, rid, count)
		if (entity:hasSkill(281) == 1) then
			return entity:studySkill(282)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30080] = {					--瞬移3
	onUse = function(entity, rid, count)
		if (entity:hasSkill(282) == 1) then
			return entity:studySkill(283)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30081] = {					--瞬移4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(283) == 1) then
			return entity:studySkill(284)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30082] = {					--瞬移5
	onUse = function(entity, rid, count)
		if (entity:hasSkill(284) == 1) then
			return entity:studySkill(285)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}

gdItemExtension[30083] = {					--大隐于市1
	onUse = function(entity, rid, count)
		return entity:studySkill(371)
	end
}
gdItemExtension[30084] = {					--大隐于市2
	onUse = function(entity, rid, count)
		if (entity:hasSkill(371) == 1) then
			return entity:studySkill(372)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30085] = {					--大隐于市3
	onUse = function(entity, rid, count)
		if (entity:hasSkill(372) == 1) then
			return entity:studySkill(373)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30086] = {					--大隐于市4
	onUse = function(entity, rid, count)
		if (entity:hasSkill(373) == 1) then
			return entity:studySkill(374)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
gdItemExtension[30087] = {					--大隐于市5
	onUse = function(entity, rid, count)
		if (entity:hasSkill(374) == 1) then
			return entity:studySkill(375)
		end
		return Error.Combat_Skill_LevelNotEnough
	end
}
---鹤嘴锄 挖矿活动
local getItemskillid = function(sid)
	local item = gdItems[sid]
	local skillid = 0
	if item then
		skillid = item.skillid
	else
		log.error("item not find")
	end
	if not skillid or skillid == 0 then
		log.error("item put on not find skill id ")
	end
	return skillid
end
gdItemExtension[70167] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70167)
		log.info("put on item 70167 "..skillid)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70167)
		return entity:rmvSkill(skillid)
	end,
	onDetach = function (entity)
		local skillid = getItemskillid(70167)
		return entity:rmvSkill(skillid)
	end,

}
gdItemExtension[70168] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70168)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70168)
		return entity:rmvSkill(skillid)
	end,
	onDetach = function (entity)
		local skillid = getItemskillid(70168)
		return entity:rmvSkill(skillid)
	end,

}
gdItemExtension[70169] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70169)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70169)
		return entity:rmvSkill(skillid)
	end,

}
gdItemExtension[70170] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70170)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70170)
		return entity:rmvSkill(skillid)
	end,

}
gdItemExtension[70171] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70171)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70171)
		return entity:rmvSkill(skillid)
	end,

}
gdItemExtension[70172] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70172)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70172)
		return entity:rmvSkill(skillid)
	end,
	onDetach = function (entity)
		local skillid = getItemskillid(70172)
		return entity:rmvSkill(skillid)
	end,

}
gdItemExtension[70173] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70173)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70173)
		return entity:rmvSkill(skillid)
	end,
	onDetach = function (entity)
		local skillid = getItemskillid(70173)
		return entity:rmvSkill(skillid)
	end,

}
gdItemExtension[70174] =
{
	onPutOn = function(entity,rid,count)
		local skillid = getItemskillid(70174)
		return entity:addSkill(skillid)
	end,
	onPutOff = function(entity,rid,count)
		local skillid = getItemskillid(70174)
		return entity:rmvSkill(skillid)
	end,

}

--
--	催泪弹 用于活动: 采花大盗
--
gdItemExtension[30220] =
{
	onUse = function(entity,rid,count)
		-- 催泪弹只在王城才能用
		local Scene = entity:getScene()
		if Scene then
			if Scene:getStaticID() ~= EnumSceneID.WangCheng then
				return Error.InvalidScene
			end
		end

		entity:useItemSkill(2020, entity:getID())
		return Error.Success
	end,
}

gdItemExtension[30221] =
{
	onUse = function(entity,rid,count)
		-- 催泪弹只在王城才能用
		local Scene = entity:getScene()
		if Scene then
			if Scene:getStaticID() ~= EnumSceneID.WangCheng then
				return Error.InvalidScene
			end
		end

		entity:useItemSkill(2021, entity:getID())
		return Error.Success
	end,
}

--
--	植物种子包
--
gdItemExtension[30230] =
{
	onUse = function(entity,rid,count)
		return doAddItemByTable(entity, {39029, 30048, 30047})
	end,
}

gdItemExtension[30231] =
{
	onUse = function(entity,rid,count)
		return doAddItemByTable(entity, {39029, 30048, 30049, 30047})
	end,
}

--
--	植物种子
--
gdItemExtension[30232] =	--玫瑰种子
{
	onUse = function(entity,rid,count)
	entity:addItem(39029, 1)
		return Error.Success
	end,
}

gdItemExtension[30233] =	--奇异种子
{
	onUse = function(entity,rid,count)
		entity:addItem(30048, 1)
		return Error.Success
	end,
}

gdItemExtension[30234] =	--摇钱种子
{
	onUse = function(entity,rid,count)
		entity:addItem(30049, 1)
		return Error.Success
	end,
}

gdItemExtension[30235] =	--血菩提种子
{
	onUse = function(entity,rid,count)
		entity:addItem(30047, 1)
		return Error.Success
	end,
}
--
--	植物果实
--
gdItemExtension[30046] = 	--苹果
{
	onUse = function(entity,rid,count)
		entity:addGene(39043)
		entity:addGene(39047)
		entity:addGene(39051)
		entity:addGene(39055)
		return Error.Success
	end,
--[[	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MPMax,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_PDEF_Max, 120)
		cbt:addProps(Combat.prop_MDEF_Max, 120)
		entity:addProps(EntityProp.attr_gene_damage,50)
	end,
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax, -10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MPMax, -10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_PDEF_Max, -120)
		cbt:addProps(Combat.prop_MDEF_Max, -120)
		entity:addProps(EntityProp.attr_gene_damage,-50)
	end,]]
}

gdItemExtension[30051] = 	--超级苹果
{
	onUse = function(entity,rid,count)
		--entity:addGene(39058)
		entity:addGene(40201)
		entity:addGene(40202)
		entity:addGene(40200)
		entity:addGene(40203)
		return Error.Success
	end,
--[[	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MPMax,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_PDEF_Max, 600)
		cbt:addProps(Combat.prop_MDEF_Max, 600)
		entity:addProps(EntityProp.attr_gene_damage,65)
	end,
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax, -15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MPMax, -15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_PDEF_Max, -600)
		cbt:addProps(Combat.prop_MDEF_Max, -600)
		entity:addProps(EntityProp.attr_gene_damage,-65)
	end,]]
}
gdItemExtension[30047] =	--血菩提
{
	onUse = function(entity,rid,count)
		--entity:addGene(39057)
		entity:addGene(40204)
		entity:addGene(40205)
		entity:addGene(40206)
		return Error.Success
	end,
	--[[onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,12 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MPMax,12 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_PDEF_Max, 150)
		cbt:addProps(Combat.prop_MDEF_Max, 150)
	end,
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax, -12 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MPMax, -12 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_PDEF_Max, -150)
		cbt:addProps(Combat.prop_MDEF_Max, -150)
	end,]]
}
gdItemExtension[30048] =	--奇异果
{
	onUse = function(entity,rid,count)
	return doAddItemByTable(entity, {40011,10013,10011,10012,40053 })
	end,
}
gdItemExtension[30049] =	--金钱果
{
	onUse = function(entity,rid,count)
	local mon = erxiangfub(1000,60000,10)
	entity:addMoney(mon)
	end,
}
--幸运药水
gdItemExtension[30020] = 	--幸运药水
{
	onUse = function(entity,rid,count)
		entity:addGene(39059)
		return Error.Success
	end,
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_Luck,1)
	end,
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_Luck,-1)
	end,
}
gdItemExtension[30026] = 	--幸运药水
{
	onUse = function(entity,rid,count)
		entity:addGene(39060)
		return Error.Success
	end,
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_Luck,5)
	end,
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_Luck,-5)
	end,
}
-- VIP 卡
gdItemExtension[30039] = 	--至尊VIP卡
{
	onUse = function(entity,rid,count)
		--entity:addGene(39060)
		return Error.Success
	end,

}

gdItemExtension[30040] = 	--黄金VIP卡
{
	onUse = function(entity,rid,count)
		--entity:addGene(39060)
		return Error.Success
	end,

}

gdItemExtension[30041] = 	--白银VIP卡
{
	onUse = function(entity,rid,count)
		--entity:addGene(39060)
		Gift.onRecharge(entity,10000)
		return Error.Success
	end,

}

gdItemExtension[30044] = 	--VIP体验卡
{
	onUse = function(entity,rid,count)
		--entity:addGene(39060)
		return Error.Success
	end,

}

local function isProtectGirl(entity)

	return false
end

--
-- 	回城卷
--
local function gcz_check_convey(entity)
	local scene = entity:getScene()
	if not scene then
		return true
	end
	if scene:getID()~=180 then
		return true		--如果不是在沙皇宫
	end
	local guild = entity:getGuild()
	if not guild then
		return true
	end
	if not guild:hasApplyGcz() then
		return true		--如果没有报名攻城战
	end
	local mguildid = _G.getWorldDataX(EID.gcz)
	if not mguildid or mguildid<=0 then
		return true		--如果沙城没有城主,或者攻城战没有开始
	end
	if mguildid==guild:getID() then
		return true		--如果该玩家属于守城方
	end

	return false
end

local function conveycheck(entity)
	local isgirlprotect = entity:getProps(EntityProp.attr_meinvhusong_monstergid)
	if isgirlprotect ~= 0 then
		return Error.Meinvhusong_is_begin
	end
	local scene = entity:getScene()
	if not scene then
		return Error.Success
	end
	local sd =  gdMaps[scene:getStaticID()]
	if sd and sd.type ~= 1 then
		return Error.Scene_Not_Allow
	end
	return Error.Success

end


gdItemExtension[30021] =
{
	onUse = function(entity,rid,count)
		if not gcz_check_convey(entity) then
			return Error.Script
		end
		local rtv = conveycheck(entity)
		if rtv == Error.Success then
		--log.info("huicheng Use It !!!")
			return Scene.conveytoSafeArea(entity) -- 第二个参数不填写为回到上次的所在的安全区
		end
		return rtv
	end,
}
-- 王城回城卷
gdItemExtension[30022] =
{
	onUse = function(entity,rid,count)
		if not gcz_check_convey(entity) then
			return Error.Script
		end
		local rtv = conveycheck(entity)
		if rtv == Error.Success then
			return Scene.conveytoSafeArea(entity,2)
		end
		return rtv
	end,
}
--  土城回城卷
gdItemExtension[30023] =
{
	onUse = function(entity,rid,count)
		if not gcz_check_convey(entity) then
			return Error.Script
		end
		local rtv = conveycheck(entity)
		if rtv == Error.Success then
			return Scene.conveytoSafeArea(entity,4)
		end
		return rtv
	end,
}
-- 随机传送卷
gdItemExtension[30024] =
{
	onUse = function(entity,rid,count)
		if not gcz_check_convey(entity) then
			return Error.Script
		end
		local rtv = conveycheck(entity)
		if rtv == Error.Success then
			return Scene.conveytoRandomPos(entity)
		end
		return rtv
	end,
}
-- 行会回城卷
gdItemExtension[30025] =
{
	onUse = function(entity,rid,count)
		local rtv = conveycheck(entity)
		if rtv ~= Error.Success then
			return rtv
		end

		if _G.getWorldDataX(WP.city_master_guild) ~= entity:getProps(EP.attr_guild_id) then
			return Error.err_guild_NotCityMasterGuild
		end

		if Event.isActive(EID.gcz) then
			Scene.conveyentitytoAnywhere(entity, MapID.sc, 294, 146)
		else
			Scene.conveyentitytoAnywhere(entity, MapID.tc, 294, 146)
		end

		return Error.Success
	end,
}
--超级传送卷
gdItemExtension[30016] =
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		entity:addItem(30021, 50)
		return Error.Success
	end
}
gdItemExtension[30015] =
{
	onUse = function(entity, rid, count)
	local ItemCnt = 1
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
	end
		entity:addItem(30024, 50)
		return Error.Success
	end
}
--
--点击增加金币、元宝、仙玉、荣誉
gdItemExtension[1] =
{
	onUse = function(entity,rid,count)
		count = count or 1
		entity:addExp(count)
		return Error.Success
	end,
}
gdItemExtension[2] =
{
	onUse = function(entity,rid,count)
		count = count or 1
		entity:addMoney(count)
		return Error.Success
	end,
}
gdItemExtension[3] =
{
	onUse = function(entity,rid,count)
		count = count or 1
		entity:addGold(count)
		return Error.Success
	end,
}
gdItemExtension[4] =
{
	onUse = function(entity,rid,count)
		count = count or 1
		entity:addCoupon(count)
		return Error.Success
	end,
}
gdItemExtension[6] =
{
	onUse = function(entity,rid,count)
		count = count or 1
		entity:addHonor(count)
		return Error.Success
	end,
}
gdItemExtension[30056] =
{
	onUse = function(entity,rid,count)
		entity:addMoney(10000000)
		return Error.Success
	end,
}
gdItemExtension[30058] =
{
	onUse = function(entity,rid,count)
		local n = math.random(4)
		if n then
			if n == 1 then
			entity:addMoney(100000)
			elseif n == 2 then
			entity:addMoney(50000)
			elseif n == 3 then
			entity:addMoney(30000)
			elseif n == 4 then
			entity:addMoney(10000)
			end
		end
		return Error.Success
	end,
}
gdItemExtension[30060] =
{
	onUse = function(entity,rid,count)
		entity:addMoney(1000000)
		return Error.Success
	end,
}
gdItemExtension[30061] =
{
	onUse = function(entity,rid,count)
		entity:addMoney(5000000)
		return Error.Success
	end,
}
gdItemExtension[30166] =
{
	onUse = function(entity,rid,count)
		entity:addCoupon(1)--100
		return Error.Success
	end,
}
gdItemExtension[30214] =
{
	onUse = function(entity,rid,count)
		math.randomseed(tostring(os.time()):reverse():sub(1, 6))
		local n = math.random(4)
		if n then
			if (n == 1) then
			entity:addHonor(10000)
			elseif (n == 2) then
			entity:addHonor(5000)
			elseif (n == 3) then
			entity:addHonor(3000)
			elseif (n == 4) then
			entity:addHonor(1000)
			end
		end
		return Error.Success
	end,
}
gdItemExtension[30215] =--仙玉票
{
	onUse = function(entity,rid,count)
		math.randomseed(tostring(os.time()):reverse():sub(1, 6))
		local n = math.random(4)
		if n then
			if n == 1 then
			entity:addCoupon(100)
			elseif n == 2 then
			entity:addCoupon(50)
			elseif n == 3 then
			entity:addCoupon(30)
			elseif n == 4 then
			entity:addCoupon(15)
			end
		end
		return Error.Success
	end,
}
--荣誉
gdItemExtension[30206] =
{
	onUse = function(entity,rid,count)
		entity:addHonor(10000)
		return Error.Success
	end,
}
gdItemExtension[30207] =
{
	onUse = function(entity,rid,count)
		entity:addHonor(5000)
		return Error.Success
	end,
}
gdItemExtension[30208] =
{
	onUse = function(entity,rid,count)
		entity:addHonor(1000)
		return Error.Success
	end,
}
gdItemExtension[30209] =
{
	onUse = function(entity,rid,count)
		entity:addHonor(50000)
		return Error.Success
	end,
}
gdItemExtension[30210] =
{
	onUse = function(entity,rid,count)
		entity:addHonor(3000)
		return Error.Success
	end,
}
gdItemExtension[30250] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(56000)
		entity:addMoney(n+20000)
		return Error.Success
	end,
}
gdItemExtension[30251] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(58000)
		entity:addMoney(n+23000)
		return Error.Success
	end,
}
gdItemExtension[30252] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(64000)
		entity:addMoney(n+26500)
		return Error.Success
	end,
}
gdItemExtension[30253] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(71700)
		entity:addMoney(n+29100)
		return Error.Success
	end,
}
gdItemExtension[30254] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(85800)
		entity:addMoney(n+33700)
		return Error.Success
	end,
}
gdItemExtension[30255] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(108050)
		entity:addMoney(n+37150)
		return Error.Success
	end,
}
gdItemExtension[30256] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(125050)
		entity:addMoney(n+49800)
		return Error.Success
	end,
}
gdItemExtension[30257] =                        --天地宝箱
{
	onUse = function(entity,rid,count)
		local n = math.random(152150)
		entity:addMoney(n+67850)
		return Error.Success
	end,
}
--经验灵符
--
gdItemExtension[30064] =          			--临时的
{
	onUse = function(entity,rid,count)
		local lvl = entity:getLevel()
		local m = math.random(100000)
		local n = lvl * 5000 + 100000 +m
		entity:addExp(n)
		return Error.Success
	end,
}


gdItemExtension[30189] =
{
	onUse = function(entity,rid,count)
		if  Entity.checkEntityMaxLevel(entity) then
			return Error.LevelMax
		else
			entity:addExp(1000000)
		end
		return Error.Success
	end,
}
gdItemExtension[30190] =
{
	onUse = function(entity,rid,count)
		if  Entity.checkEntityMaxLevel(entity) then
			return Error.LevelMax
		else
			entity:addExp(50000)
		end
		return Error.Success
	end,
}
gdItemExtension[30191] =
{
	onUse = function(entity,rid,count)
		if  Entity.checkEntityMaxLevel(entity) then
			return Error.LevelMax
		else
			entity:addExp(10000000)
		end
		return Error.Success
	end,
}
gdItemExtension[30192] =
{
	onUse = function(entity,rid,count)
		if  Entity.checkEntityMaxLevel(entity) then
			return Error.LevelMax
		else
			entity:addExp(100000000)
		end
		return Error.Success
	end,
}
gdItemExtension[30199] =
{
	onUse = function(entity,rid,count)
		if  Entity.checkEntityMaxLevel(entity) then
			return Error.LevelMax
		else
			entity:addExp(5000000)
		end
		return Error.Success
	end,
}
--
--	避水丹
gdItemExtension[39050] =
{
	onUse = function(entity,rid,count)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		local sid = scene:getStaticID()
		if sid==MapID.gjd or sid==MapID.wzsx or sid==MapID.sz then
			--
			-- ToDo:
			--
			entity:addGene(60000)
			return Error.Success
		else
			return Error.InvalidScene
		end
	end,
}
--
--	攻击丹
gdItemExtension[39051] =
{
	onUse = function(entity,rid,count)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		local sid = scene:getStaticID()
		if sid==MapID.gjd or sid==MapID.wzsx or sid==MapID.sz then
			--
			-- ToDo:
			--
			entity:addGene(60001)
			return Error.Success
		else
			return Error.InvalidScene
		end
	end,
}
--
--	防御丹
gdItemExtension[39052] =
{
	onUse = function(entity,rid,count)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		local sid = scene:getStaticID()
		if sid==MapID.gjd or sid==MapID.wzsx or sid==MapID.sz then
			--
			-- ToDo:
			--
			entity:addGene(60002)
			return Error.Success
		else
			return Error.InvalidScene
		end
	end,
}
--[[
--
--	毒物丹
gdItemExtension[39053] =
{
	onUse = function(entity,rid,count)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		local sid = scene:getStaticID()
		if sid==MapID.gjd or sid==MapID.wzsx or sid==MapID.sz then
			--
			-- ToDo:
			--
			return Error.Success
		else
			return Error.InvalidScene
		end
	end,
}
--]]

--集齐N个有惊喜
gdItemExtension[30217] =				--战神板木
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30217,7) then
		return doAddItemByTable(entity,{82000,82012,82024,82036})
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30217,7)
		return Error.Success
	end
}
gdItemExtension[30288] =				--黄金雷锤碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30288,7) then
			entity:addItem(82000)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30288,7)
		return Error.Success
	end
}

gdItemExtension[30289] =				--如意金箍棒碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30289,7) then
			entity:addItem(82012)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30289,7)
		return Error.Success
	end
}

gdItemExtension[30290] =				--死神之镰
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30290,7) then
			entity:addItem(82024)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30290,7)
		return Error.Success
	end
}

gdItemExtension[30291] =				--生花妙笔
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30291,7) then
			entity:addItem(82036)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30291,7)
		return Error.Success
	end
}
gdItemExtension[30032] =				--翅膀羽毛
{
	onUse = function(entity,rid,count)
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30032,25) then
			entity:addItem(80000)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30032,25)
		return Error.Success
	end
}

gdItemExtension[30109] =				--高级技能书残页
{
	onUse = function(entity,rid,count)
	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30109,20) then
			local n = math.random(100)
			if n<= 10 then
			entity:addItem(30103)
			elseif n <= 40 then
			entity:addItem(30102)
			elseif n <= 70 then
			entity:addItem(30111)
			else
			entity:addItem(30126)
			return Error.Success
			end
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30109,20)
		return Error.Success
	end
}
gdItemExtension[30280] =				--生命魂石碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30280,3) then
			entity:addItem(10007)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30280,3)
		return Error.Success
	end
}

gdItemExtension[30281] =				--魔法魂石碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30281,3) then
			entity:addItem(10008)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30281,3)
		return Error.Success
	end
}

gdItemExtension[30282] =				--物防碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30282,3) then
			entity:addItem(10009)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30282,3)
		return Error.Success
	end
}
gdItemExtension[30283] =				--魔防碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30283,3) then
			entity:addItem(10010)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30283,3)
		return Error.Success
	end
}
gdItemExtension[30284] =				--物攻碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30284,3) then
			entity:addItem(10011)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30284,3)
		return Error.Success
	end
}
gdItemExtension[30285] =				--魔攻碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30285,3) then
			entity:addItem(10012)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30285,3)
		return Error.Success
	end
}

gdItemExtension[30286] =				--道攻碎片
{
	onUse = function(entity,rid,count)

	local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if entity:hasItem(30286,3) then
			entity:addItem(10013)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	onUsed = function(entity,item)
		entity:rmvItem(30286,3)
		return Error.Success
	end
}
--金蚕王
gdItemExtension[30059] = {  -- 金蚕王
	onUse = function(entity, rid, count)
		-- 新增限制：只能在土城使用
		local scene = entity:getScene()
		if scene:getStaticID() ~= MapID.tc then
			return Error.InvalidScene
		end

		local rebornlvl = entity:getProps(EntityProp.attr_reborn)
		local evocon = gdEvolutionCondition[rebornlvl]
		local maxlevel = 70
		if evocon then
			maxlevel = evocon.maxlvl
		end
		
		local curlvl = entity:getLevel()
		
		-- 新增限制：只能在500级前使用
		if curlvl >= 500 then
			return Error.LevelMax
		end
		
		if (curlvl + 1) > maxlevel then
			return Error.LevelMax
		end

		local curexp = entity:getExp()
		local tgtexp = gdlevelupexp[curlvl] -  (gdlevelupexp[curlvl - 1] or 0)
		if not tgtexp then
			return Error.Unknown
		end
		
		entity:addExp(tgtexp - curexp)
		return Error.Success
	end
}
-- 宠物金蚕王
gdItemExtension[30211] =
{
	onUse = function(entity,rid,count)
		local petid = entity:getProps(EntityProp.attr_pet_on)
		if petid ~= 0 then
			local pet = entity:getSubEntity(petid)
			if pet and pet:getType() == EntityProp.ett_Pet then
				local petlevel = pet:getLevel()
				local petlight = pet:getProps(EntityProp.attr_pet_reach_ten)
				--if (petlight == 0 and petlevel >= 10) then
				--	return Error.PetNeedLight
				--end
				if gdPetGrow[petlevel + 1] then
					addexp = gdPetGrow[petlevel].exp - pet:getExp()
					pet:addExp(addexp)
					return Error.Success
				else
					return Error.LevelMax
				end
			else
				return Error.InvalidEntity
			end
		else
			return Error.PetnotOn
		end
	end
}
-- 祝福油
gdItemExtension[30018] =
{
	onUse = function(entity,rid,count)
		local item = entity:getItemByPosition(ItemProp.ItemPosition_Equip_Weapon)
		if item then
			local lucky = item:getProps(ItemProp.Item_Lucky)
			if lucky <= 0 then
				Item.onPutOff(entity, item)
				local m = math.random(100)
				if m <= 80 then
					lucky = lucky + 1
				end
				log.info(m, lucky)
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			elseif lucky == 1 then
				Item.onPutOff(entity, item)
				local m = math.random(100)
				log.info(m, lucky)
				if m <= 30 then
					lucky = lucky + 1
				elseif m <= 45 then
					lucky = lucky - 1
				end
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			elseif lucky == 2 then
				Item.onPutOff(entity, item)
				local m = math.random(100)
				log.info(m, lucky)
				if m <= 20 then
					lucky = lucky + 1
				elseif m <= 32 then
					lucky = lucky - 1
				end
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			elseif lucky == 3 then
				Item.onPutOff(entity, item)
				local m = math.random(100)
				log.info(m, lucky)
				if m <= 12 then
					lucky = lucky + 1
				elseif m <= 22 then
					lucky = lucky - 1
				end
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			elseif lucky == 4 then
				Item.onPutOff(entity, item)
				local m = math.random(100)
				log.info(m, lucky)
				if m <= 10 then
					lucky = lucky + 1
				elseif m <= 18 then
					lucky = lucky - 1
				end
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			elseif lucky == 5 then
				Item.onPutOff(entity, item)
				local m = math.random(100)
				log.info(m, lucky)
				if m <= 8 then
					lucky = lucky + 1
				elseif m <= 15 then
					lucky = lucky - 1
				end
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			elseif lucky == 6 then
				Item.onPutOff(entity, item)
				local m = math.random(100)
				log.info(m, lucky)
				if m <= 6 then
					lucky = lucky + 1
				elseif m <= 12 then
					lucky = lucky - 1
				end
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			else
				Item.onPutOff(entity, item)
				local m = math.random(100)
				log.info(m, lucky)
				if m <= 5 then
					lucky = lucky + 1
				elseif m <= 10 then
					lucky = lucky - 1
				end
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
			end
			return Error.Success
		else
			return Error.InvalidItem
		end
	end
}

-- 超级祝福油
gdItemExtension[30019] =
{
	onUse = function(entity,rid,count)
		local item = entity:getItemByPosition(ItemProp.ItemPosition_Equip_Weapon)
		if item then
			local lucky = item:getProps(ItemProp.Item_Lucky)
			if lucky < 7 then
				Item.onPutOff(entity, item)
				lucky = lucky + 1
				item:setProps(ItemProp.Item_Lucky,lucky)
				entity:saveItemProps(item,ItemProp.Item_Lucky)
				entity:syncItemProps(item,ItemProp.Item_Lucky)
				Item.onPutOn(entity, item)
				entity:syncPlayerCombatCombo()
				return Error.Success
			else
				return Error.Item_CantLuckyUp
			end
			return Error.InvalidItem
		else
			return Error.InvalidItem
		end
	end
}

--转生灵魄
gdItemExtension[30091] =
{
	onUse = function(entity,rid,count)
		local rebornitem = entity:getProps(EntityProp.attr_rebornrqeitem)
		entity:setProps(EntityProp.attr_rebornrqeitem,1500 + rebornitem)
		entity:syncProps(EntityProp.attr_rebornrqeitem)
		entity:saveProps(EntityProp.attr_rebornrqeitem)
		return Error.Success
	end
}
gdItemExtension[30094] =
{
	onUse = function(entity,rid,count)
		local rebornitem = entity:getProps(EntityProp.attr_rebornrqeitem)
		entity:setProps(EntityProp.attr_rebornrqeitem,100 + rebornitem)
		entity:syncProps(EntityProp.attr_rebornrqeitem)
		entity:saveProps(EntityProp.attr_rebornrqeitem)
		return Error.Success
	end
}
----------------------------------灵力-------------------------------------
gdItemExtension[30092] =
{
	onUse = function(entity,rid,count)
	
		local lingliitem = entity:getProps(EntityProp.attr_lingliqeitem)
		local newValue = 1000 + (lingliitem or 0)
		
		entity:setProps(EntityProp.attr_lingliqeitem, newValue)
		entity:syncProps(EntityProp.attr_lingliqeitem)
		entity:saveProps(EntityProp.attr_lingliqeitem)
		local checkValue = entity:getProps(EntityProp.attr_lingliqeitem)
		
		return Error.Success
	end
}
--毙毒符咒
gdItemExtension[60287] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,0)
		return Error.Success
	end,
}


gdItemExtension[60288] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60289] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60290] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60291] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_ds_cl_damage,0)
		return Error.Success
	end,
}

--赤炎章
gdItemExtension[60308] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,0)
		return Error.Success
	end,
}


gdItemExtension[60309] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60310] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60311] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60312] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_zs_cl_damage,0)
		return Error.Success
	end,
}

--暴雷石
gdItemExtension[60315] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,0)
		return Error.Success
	end,
}


gdItemExtension[60316] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60317] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60318] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,0)
		return Error.Success
	end,
}

gdItemExtension[60319] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,1)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_fs_cl_damage,0)
		return Error.Success
	end,
}


-- 烈火符咒
gdItemExtension[60294] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}


gdItemExtension[60295] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

gdItemExtension[60296] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

gdItemExtension[60297] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}
gdItemExtension[60298] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

---缓慢符咒

gdItemExtension[60301] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}


gdItemExtension[60302]  =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

gdItemExtension[60303] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

gdItemExtension[60304] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}
gdItemExtension[60305] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

--- 缓雷石

gdItemExtension[60322] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}


gdItemExtension[60323] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

gdItemExtension[60324] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

gdItemExtension[60325] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}
gdItemExtension[60326] =
{
	onPutOn = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,10210)
		return Error.Success
	end,
	onPutOff = function(entity,rid,count)
		entity:setProps(EntityProp.attr_cl_speed,0)
		return Error.Success
	end,
}

--- 经验玉
local function expjadeaddexp(item,exp,storeper,storemax)
	local storeexp = item:getProps(ItemProp.Item_ExpStore)
	storeexp = exp * storeper + storeexp
	if storeexp <= storemax then
		item:setProps(ItemProp.Item_ExpStore,storeexp)
		--log.info("exp jade pos = "..item:getPosition().. " storeexp = "..storeexp)
		return 0
	else
		item:setProps(ItemProp.Item_ExpStore,storemax)
		return (storeexp - storemax)/storeper
	end
end

local function expjadeuse(entity,exp,id,goldbase)
	local cnt = entity:getEventDataX(id)
	local daymax = 5
	if daymax > cnt then
		goldbase = goldbase / (2 ^ (cnt))
	else
		return Error.TooManyTimes
	end
	local rtv = entity:useGold(goldbase,Opcode.Op_Item_UseExpJade)
	if rtv == Error.Success then
		entity:addExp(exp,Opcode.Op_Item_UseExpJade)
		entity:addEventDataX(id,1)
	end
	return rtv

end

local function expjadeuseCoupon(entity,exp,id,couponbase)
	local cnt = entity:getEventDataX(id)
	local daymax = 5
	if daymax > cnt then
		couponbase = couponbase / (2 ^ (cnt))
	else
		return Error.TooManyTimes
	end
	local rtv = entity:useCoupon(couponbase,Opcode.Op_Item_UseExpJade)
	if rtv == Error.Success then
		entity:addExp(exp,Opcode.Op_Item_UseExpJade)
		entity:addEventDataX(id,1)
	end
	return rtv

end
gdItemExtension[30072] = --体验经验玉
{
	onAddExp = function(item,exp)
		local storeper = 3
		local storemax = 100000
		return expjadeaddexp(item,exp,storeper,storemax)
	end,
	onUse = function(entity,rid,count)
		local basegold = 6
		local storemax = 100000
		if (rid < storemax) then
			return Error.Item_ExpJadeNotFull
		else
			return expjadeuseCoupon(entity,rid,EID.itjyyz,basegold)
		end
	end,
}
gdItemExtension[30036] = --经验玉 中
{
	onAddExp = function(item,exp)
		local storeper = 3
		local storemax = 2000000
		return expjadeaddexp(item,exp,storeper,storemax)
	end,
	onUse = function(entity,rid,count)
		local basegold = 80
		local storemax = 2000000
		if (rid < storemax) then
			return Error.Item_ExpJadeNotFull
		else
			if  Entity.checkEntityMaxLevel(entity) then
				return Error.LevelMax
			else
				return expjadeuseCoupon(entity,rid,EID.itjyyz,basegold)
			end
		end
	end,
}

gdItemExtension[30037] =  --经验玉 小
{
	onAddExp = function(item,exp)
		local storeper = 2
		local storemax = 400000
		return expjadeaddexp(item,exp,storeper,storemax)
	end,
	onUse = function(entity,rid,count)
		local basegold = 16
		local storemax = 400000
		if (rid < storemax) then
			return Error.Item_ExpJadeNotFull
		else
			if  Entity.checkEntityMaxLevel(entity) then
				return Error.LevelMax
			else
				return expjadeuseCoupon(entity,rid,EID.itjyyx,basegold)
			end
		end
	end,
}
gdItemExtension[30050] = --  --经验玉 大
{
	onAddExp = function(item,exp)
		local storeper = 3
		local storemax = 4000000
		return expjadeaddexp(item,exp,storeper,storemax)
	end,
	onUse = function(entity,rid,count)
		local basegold = 96
		local storemax = 4000000
		if (rid < storemax) then
			return Error.Item_ExpJadeNotFull
		else
			if  Entity.checkEntityMaxLevel(entity) then
				return Error.LevelMax
			else
				return expjadeuse(entity,rid,EID.itjyyd,basegold)
			end
		end
	end,
}
gdItemExtension[30066] = -- 经验灵石 大
{
	onAddExp = function(item,exp)
		local storeper = 2
		local storemax = 10000000
		return expjadeaddexp(item,exp,storeper,storemax)
	end,
	onUse = function(entity,rid,count)
		local basegold = 200
		local storemax = 10000000
		if (rid < storemax) then
			return Error.Item_ExpJadeNotFull
		else
			if  Entity.checkEntityMaxLevel(entity) then
				return Error.LevelMax
			else
				return expjadeuse(entity,rid,EID.itjylsd,basegold)
			end
		end
	end,
}
gdItemExtension[30067] = -- 经验灵石 中
{
	onAddExp = function(item,exp)
		local storeper = 1.5
		local storemax = 6000000
		return expjadeaddexp(item,exp,storeper,storemax)
	end,
	onUse = function(entity,rid,count)
		local basegold = 120
		local storemax = 6000000
		if (rid < storemax) then
			return Error.Item_ExpJadeNotFull
		else
			if  Entity.checkEntityMaxLevel(entity) then
				return Error.LevelMax
			else
				return expjadeuse(entity,rid,EID.itjylsz,basegold)
			end
		end
	end,
}
gdItemExtension[30068] = -- 经验灵石 小
{
	onAddExp = function(item,exp)
		local storeper = 1
		local storemax = 3000000
		return expjadeaddexp(item,exp,storeper,storemax)
	end,
	onUse = function(entity,rid,count)
		local basegold = 60
		local storemax = 3000000
		if (rid < storemax) then
			return Error.Item_ExpJadeNotFull
		else
			if  Entity.checkEntityMaxLevel(entity) then
				return Error.LevelMax
			else
				return expjadeuse(entity,rid,EID.itjylsx,basegold)
			end
		end
	end,
}

--日常礼盒
gdItemExtension[30027] =
{
	onUse = function(entity,rid,count)
		--math.randomseed(tostring(os.time()):reverse():sub(1, 6))
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local n = math.random(100)
		if n then
			if n <= 10 then
			local imap ={
			[30144] = 1;
			[30145] = 1;
			}
			doAddItemByWeight(entity, imap)
			elseif n <= 25 then
			entity:addItem(40046)
			elseif n <= 40 then
			entity:addItem(40060)
			elseif n <= 55 then
			entity:addItem(30000)
			elseif n <= 70 then
			entity:addItem(30052)
			elseif n <= 85 then
			entity:addItem(30052)
			elseif n <= 90 then
			entity:addItem(40050)
			elseif n <= 96 then
			entity:addItem(40116)
			else
			entity:addItem(30017)
			end
		end
		return Error.Success
	end,
}

gdItemExtension[30299] =-- 元宝?
{
	onUse = function(entity,rid,count)
		entity:addGold(5)
		return Error.Success
	end
}

gdItemExtension[30175] = -- 活跃礼盒
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local lootid = gdLootnametoID["活跃礼包的数据"]
		if lootid then
			Loot.callReward(nil,entity,lootid,Opcode.Op_UseItem)
			return Error.Success
		else
			return Error.Script
		end
	end,
}

gdItemExtension[30017] = --战神油
{
	onUse = function(entity,rid,count)
		--for i=-17,-1 do
		--	local pItem=entity:getItemByPosition(i)
		--	if pItem then
		--		if gdItems[pItem:getSID()].durable then
		--			print("item Item_Durable="..gdItems[pItem:getSID()].durable)
		--			pItem:setProps(ItemProp.Item_Durable,0)
		--			entity:saveItemProps(pItem,ItemProp.Item_Durable)
		--			entity:syncItemProps(pItem,ItemProp.Item_Durable)
		--		end
		--	end
		--end
		return Item.RepairAllItem(entity)--Error.Success
	end,
}
gdItemExtension[30042] = -- 神秘彩蛋
{
	onUse = function(entity,rid,count)
		return addRandomReward(entity, rid, count)
	end
}


gdItemExtension[30300] =
{
	onUse = function(entity,rid,count)
		if entity:hasItem(30300, 1) and entity:hasItem(30301, 1) and entity:hasItem(39008, 1) then
			entity:rmvItem(30301, 1)
			entity:rmvItem(39008, 1)
			entity:addItem(30302, 1)
			return Error.Success
		end
		return Error.NotEnoughItem
	end,
}

gdItemExtension[30301] =
{
	onUse = function(entity,rid,count)
		if entity:hasItem(30300, 1) and entity:hasItem(30301, 1) and entity:hasItem(39008, 1) then
			entity:rmvItem(30300, 1)
			entity:rmvItem(39008, 1)
			entity:addItem(30302, 1)
			return Error.Success
		end
		return Error.NotEnoughItem
	end,
}

gdItemExtension[30302] = --同 30042
{
	onUse = function(entity,rid,count)
		return addRandomReward(entity, rid, count)
	end
}



-- 小聚宝盆
gdItemExtension[30304] =
{
	onUse = function(entity,rid,count)
		local maxidx = ServerData.beginday
		local minidx = entity:getEventDataX(EID.smallgold)
		local cnt = entity:getEventDataY(EID.smallgold)

		log.info("小聚宝盆 cnt = "..cnt.."! max - min = "..maxidx - minidx)
		if cnt == 0 then
			entity:addGold(1888888)
			entity:addEventDataY(EID.smallgold)
			entity:saveEventData(EID.smallgold)
		elseif cnt < 5 and cnt <= (maxidx - minidx) then
			entity:addGold(98888)
			entity:addEventDataY(EID.smallgold)
			entity:saveEventData(EID.smallgold)
		else
			return Error.goldbowltodayhasget
		end



		if cnt + 1 >= 5 then
			return Error.Success
		else
			return Error.bowlnoneedrmv
		end
	end,
}

-- 大聚宝盆
gdItemExtension[30305] =
{
	onUse = function(entity,rid,count)
		local maxidx = ServerData.beginday
		local minidx = entity:getEventDataX(EID.biggold)
		local cnt = entity:getEventDataY(EID.biggold)

		log.info("大聚宝盆 cnt = "..cnt.."! max - min = "..maxidx - minidx)
		if cnt == 0 then
			entity:addGold(8888888)
			entity:addEventDataY(EID.biggold)
			entity:saveEventData(EID.biggold)
		elseif cnt < 10 and cnt <= (maxidx - minidx) then
			entity:addGold(188888)
			entity:addEventDataY(EID.biggold)
			entity:saveEventData(EID.biggold)
		else
			return Error.goldbowltodayhasget
		end


		if cnt + 1 >= 10 then
			return Error.Success
		else
			return Error.bowlnoneedrmv
		end
	end,

}

-- 磐龙宝箱
gdItemExtension[30306] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local usecnt = entity:getProps(EntityProp.attr_plbx_data)
		local ran = math.random()
		if usecnt < 10 then
			while (ran >= 0.985) do
				ran = math.random()
			end
		elseif usecnt >= 89 then
			ran = 1
		end
		if ran < 0.4 then
			entity:addBindItem(30161) --四倍经验神符
			entity:addProps(EntityProp.attr_plbx_data)
		elseif ran < 0.8 then
			entity:addBindItem(10028) --四级生命魂石
			entity:addProps(EntityProp.attr_plbx_data)
		elseif ran < 0.985 then
			entity:addBindItem(40126) --8级完美强化符
			entity:addProps(EntityProp.attr_plbx_data)
		elseif ran <= 1 then
			entity:addBindItem(40143) -- 磐龙许愿盒
			entity:setProps(EntityProp.attr_plbx_data,0)
		end
		entity:saveProps(EntityProp.attr_plbx_data)
		return Error.Success
	end
}


-- 磐龙许愿盒
gdItemExtension[40143] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		if rid == 60180 then
			entity:addBindItem(60180)
		elseif rid == 60181 then
			entity:addBindItem(60181)
		elseif rid == 60182 then
			entity:addBindItem(60182)
		elseif rid == 60183 then
			entity:addBindItem(60183)
		elseif rid == 60184 then
			entity:addBindItem(60184)
		elseif rid == 60185 then
			entity:addBindItem(60185)
		elseif rid == 60186 then
			entity:addBindItem(60186)
		elseif rid == 60187 then
			entity:addBindItem(60187)
		elseif rid == 60188 then
			entity:addBindItem(60188)
		elseif rid == 60189 then
			entity:addBindItem(60189)
		end
		return Error.Success
	end
}


gdItemExtension[30293] = -- 血蛊虫
{
	onUse = function(entity,rid,count)
		local pkvalue = entity:getProps(EntityProp.attr_pkvalue)
		if pkvalue < 50 then
			return Error.NeedUseIt
		end
		entity:setProps(EntityProp.attr_pkvalue,pkvalue - 50)
		entity:syncProps(EntityProp.attr_pkvalue)
		entity:saveProps(EntityProp.attr_pkvalue)
		return Error.Success

	end,
}

--称号物品

gdItemExtension[30294] =
{
	onUse = function(entity,rid,count)--?神
		local err = HeadTitle.entityGetHeadTitle(entity,12)
		HeadTitle.syncAndSaveHas(entity)
		return err
	end
}

gdItemExtension[30295] =
{
	onUse = function(entity,rid,count)--高帅富
		if entity:getGender()==1 then
			local err = HeadTitle.entityGetHeadTitle(entity,13)
			HeadTitle.syncAndSaveHas(entity)
			return err
		else
			return Error.Item_NoMatchGender
		end
	end
}

gdItemExtension[30296] =
{
	onUse = function(entity,rid,count)--真高帅富
		if entity:getGender()==1 then
			local err = HeadTitle.entityGetHeadTitle(entity,14)
			HeadTitle.syncAndSaveHas(entity)
			return err
		else
			return Error.Item_NoMatchGender
		end
	end
}

gdItemExtension[30297] =
{
	onUse = function(entity,rid,count)--白富美
		if entity:getGender()==2 then
			local err = HeadTitle.entityGetHeadTitle(entity,13)
			HeadTitle.syncAndSaveHas(entity)
			return err
		else
			return	Error.Item_NoMatchGender
		end
	end
}

gdItemExtension[30298] =
{
	onUse = function(entity,rid,count)--真白富美
		if entity:getGender()==2 then
			local err = HeadTitle.entityGetHeadTitle(entity,14)
			HeadTitle.syncAndSaveHas(entity)
			return err
		else
			return Error.Item_NoMatchGender
		end
	end
}


------------------------------------装备特殊判定

local function checkCityMaster(entity,rid,count,gender)
	local err = Error.Script
	if entity:getGender()==gender then
		local city_master = _G.getWorldDataX(WP.city_master_player)
		if city_master and city_master == entity:getGlobalID() then
			err = Error.Success
		else
			err = Error.Not_Match_CityMaster
		end
		return err
	else
		return Error.Item_NoMatchGender
	end
end

gdItemExtension[81178] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81179] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81180] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81181] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81182] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81183] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81184] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81185] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81186] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}
gdItemExtension[81187] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,1)
	end
}

gdItemExtension[81189] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81190] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81191] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81192] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81193] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81194] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81195] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81196] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81197] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}
gdItemExtension[81198] =
{
	onPuton = function(entity,rid,count)
		return checkCityMaster(entity,rid,count,2)
	end
}

gdItemExtension[30307] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10007, 10008, 10009, 10010, {10011, 10012, 10013}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30308] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10014,10015,10016,10017,{10018,10019,10020}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30309] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10021,10022,10023,10024,{10025,10026,10027}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30310] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10028,10029,10030,10031,{10032,10033,10034}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30311] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10035,10036,10037,10038,{10039,10040,10041}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30312] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10042,10043,10044,10045,{10046,10047,10048}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30313] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10049,10050,10051,10052,{10053,10054,10055}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30314] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10056,10057,10058,10059,{10060,10061,10062}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}


gdItemExtension[30315] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10063,10064,10065,10066,{10067,10068,10069}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}


gdItemExtension[30316] =
{
	onUse = function(entity,rid,count)--一级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10070,10071,10072,10073,{10074,10075,10076}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30317] =
{
	onUse = function(entity,rid,count)--11级魂石包
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10077,10078,10079,10080,{10081,10082,10083}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

--------------------------------------------------扩展魂石袋----------------------------------------------------------------
--------------------------------------------30345，30346，30347，30348------------------------------------------------------

gdItemExtension[30345] =
{
	onUse = function(entity,rid,count)--12级魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10084,10085,10086,10087,{10088,10089,10090}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30346] =
{
	onUse = function(entity,rid,count)--13级魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10091,10092,10093,10094,{10095,10096,10097}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30347] =
{
	onUse = function(entity,rid,count)--14级魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10098,10099,10100,10101,{10102,10103,10104}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

gdItemExtension[30348] =
{
	onUse = function(entity,rid,count)--15级魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10105,10106,10107,10108,{10109,10110,10111}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}

----------------------------------------------------------------------------------------------------------------------------
--夏日雪花
gdItemExtension[30318] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local n = math.random(100)
        if n and n <=35 then
            entity:addBindItem(30319, 1,Opcode.op_summer)
        elseif n > 35 and n <= 50 then
            entity:addBindItem(30309, 1,Opcode.op_summer)
        elseif n > 50 and n <= 80 then
            entity:addBindItem(40053, 1,Opcode.op_summer)
        elseif n > 80 and n <= 100 then
            entity:addBindItem(30321, 1,Opcode.op_summer)
        end
    end
}
--夏日冰晶
gdItemExtension[30319] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local n = math.random(100)
        if n and n <=35 then
            entity:addBindItem(30320, 1,Opcode.op_summer)
        elseif n > 35 and n <= 78 then
            entity:addBindItem(30309, 1,Opcode.op_summer)
        elseif n > 78 and n <= 80 then
            entity:addBindItem(40126, 1,Opcode.op_summer)
        elseif n > 80 and n <= 100 then
            entity:addBindItem(30321, 1,Opcode.op_summer)
        end
    end
}
--雪人秘宝
gdItemExtension[30320] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local n = math.random(100)
        if n and n <=2 then
            entity:addBindItem(40004, 1,Opcode.op_summer)
            _G.syncFloatMessage("玩家" .. entity:getName() .. "通过开启雪人秘宝获得：" .. gdItems[40004].name .. "*1")
        elseif n > 2 and n <= 62 then
            entity:addBindItem(40011, 1,Opcode.op_summer)
        elseif n > 62 and n <= 80 then
            entity:addBindItem(30311, 1,Opcode.op_summer)
        elseif n > 80 and n <= 100 then
            entity:addBindItem(30321, 1,Opcode.op_summer)
        end
    end
}
--夏日冰渣
gdItemExtension[30321] =
{
    onUse = function(entity,rid,count)
        entity:addMoney(20000,Opcode.op_summer)
    end
}
--夏日清凉小礼包
gdItemExtension[30322] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30318, 6,Opcode.op_summer)
        entity:addBindItem(30319, 1,Opcode.op_summer)
    end
}
--夏日清凉大礼包
gdItemExtension[30323] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30319, 5,Opcode.op_summer)
        entity:addBindItem(30320, 1,Opcode.op_summer)
    end
}

--荣耀战魂礼包
gdItemExtension[30325] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 4) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(40125, 1,Opcode.QQ_gift)
        entity:addBindItem(80001, 1,Opcode.QQ_gift)
        entity:addBindItem(10021, 3,Opcode.QQ_gift)
    end
}
--龙影圣翼礼包
gdItemExtension[30326] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 4) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(40126, 1,Opcode.QQ_gift)
        entity:addBindItem(83022, 1,Opcode.QQ_gift)
        entity:addBindItem(40000, 8,Opcode.QQ_gift)
    end
}
--创世煅刃礼包
gdItemExtension[30327] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 3) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(40127, 1,Opcode.QQ_gift)
        entity:addBindItem(40011, 4,Opcode.QQ_gift)
    end
}
--月饼
gdItemExtension[30328] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local n = math.random(1000)
        if n <= 500 then
            entity:addBindItem(40053, 1)
        elseif  n >500 and n <= 950 then
            entity:addBindItem(30309, 1)
        elseif n >950 and n <=965 then
            entity:addBindItem(30311, 1)
        elseif n > 965 and n <= 985 then
            entity:addBindItem(40002, 1)
        elseif n > 985 and n <= 990 then
            entity:addBindItem(40004, 1)
        elseif n > 990 and n <= 995 then
            entity:addBindItem(40126, 1)
        elseif n > 995 and n <= 998 then
            entity:addBindItem(40127, 1)
        elseif n > 998 and n <= 1000 then
            entity:addBindItem(80004, 1)
        end
    end
}
--中秋月饼礼盒
gdItemExtension[30329] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30328, 8)
    end
}
--中秋至尊礼盒
gdItemExtension[30330] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 2) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30328, 12)
        entity:addBindItem(30306, 2)
    end
}
--日常大礼包
gdItemExtension[30331] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 11) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30051, 3)
        entity:addBindItem(39043, 68)
        entity:addBindItem(39018, 1)
        entity:addBindItem(39022, 1)
    end
}
--日常礼包
gdItemExtension[30332] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 4) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30046, 3)
        entity:addBindItem(39043, 9)
        entity:addBindItem(39017, 1)
        entity:addBindItem(39021, 1)
    end
}
--小经验礼包
gdItemExtension[30333] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30162, 1)
    end
}
--大经验礼包
gdItemExtension[30334] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(30163, 1)
    end
}
--宠物进阶礼包
gdItemExtension[30335] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 2) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(40053, 150)
        entity:addBindItem(30271, 1)
    end
}
--豪华强化礼包
gdItemExtension[30336] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 2) then
            return Error.Item_BagisFull
        end
        entity:addBindItem(40127, 1)
        entity:addBindItem(40011, 3)
    end
}
--国庆宝箱
gdItemExtension[30337] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local usecnt = entity:getProps(EntityProp.gqbx_get_count)
        local  nProbability =  math.random(1000)
        if usecnt <= 50 then
            while nProbability >= 997 do
                nProbability = math.random(1000)
            end
        elseif usecnt == 400 then
            nProbability = 1000
        end
        entity:addProps(EntityProp.gqbx_get_count,1)
        if nProbability <= 300 then
            entity:addBindItem(40053, 1)
        elseif nProbability > 300 and nProbability <= 600 then
            entity:addBindItem(30309, 1)
        elseif nProbability > 600 and nProbability <= 900 then
            entity:addBindItem(40011, 1)
        elseif nProbability > 900 and nProbability <= 996 then
            entity:addBindItem(80001, 1)
        elseif nProbability > 996  and nProbability <= 1000 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过国庆宝箱开出10000元宝！")
            entity:addBindItem(3, 10000)
            entity:setProps(EntityProp.gqbx_get_count,1)
        end
        entity:saveProps(EntityProp.gqbx_get_count)
    end
}
--国庆小福袋
gdItemExtension[30338] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 4 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过国庆小福袋开出百鸟朝凤(1档)*1！")
            entity:addBindItem(80001, 1)
        elseif nProbability >4 and nProbability <= 39 then
            entity:addBindItem(40053, 1)
        elseif nProbability > 39 and nProbability <= 69 then
            entity:addBindItem(40011, 1)
        elseif nProbability > 69 and nProbability <=99 then
            entity:addBindItem(30309, 1)
        elseif nProbability> 99 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过国庆小福袋开出国庆至尊礼包*1！")
            entity:addBindItem(30339, 1)
        end
    end
}
--国庆至尊礼包
gdItemExtension[30339] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 90 then
            entity:addBindItem(40011, 2)
        elseif nProbability == 91 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过国庆至尊礼包开出战神晶魄*1！")
            entity:addBindItem(40015, 1)
        elseif nProbability > 91 and nProbability <= 93 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过国庆至尊礼包开出五级灵石*1！")
            entity:addBindItem(40004, 1)
        elseif nProbability > 93 and nProbability <=95 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过国庆至尊礼包开出粉翼彩蝶(4档)*1！")
            entity:addBindItem(80004, 1)
        elseif nProbability> 95 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过国庆至尊礼包开出5级魂石袋*1！")
            entity:addBindItem(30311, 1)
        end
    end
}
--宠物小福袋
gdItemExtension[30340] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 95 then
            entity:addBindItem(40053, 1)
        elseif nProbability > 95 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过宠物小福袋开出宠物项圈*10！")
            entity:addBindItem(40053, 10)
        end
    end
}
--宠物大福袋
gdItemExtension[30341] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 90 then
            entity:addBindItem(40053, 50)
        elseif nProbability > 90 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过宠物大福袋开出宠物项圈*100！")
            entity:addBindItem(40053, 100)
        end
    end
}
--灵魂石小福袋
gdItemExtension[30342] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 94 then
            entity:addBindItem(40011, 1)
        elseif nProbability > 94 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过灵魂石小福袋开出灵魂石*10！")
            entity:addBindItem(40011, 10)
        end
    end
}
--灵魂石大福袋
gdItemExtension[30343] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 99 then
            entity:addBindItem(40011, 20)
        elseif nProbability > 99 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过灵魂石大福袋开出灵魂石*40！")
            entity:addBindItem(40011, 40)
        end
    end
}
-- 宠物福袋
gdItemExtension[30344] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 99 then
            entity:addBindItem(40053, 1)
        elseif nProbability >99 then
            _G.syncFloatMessage(tostring(entity:getName()) .. "通过宠物福袋开出宠物金蚕王*1！")
            entity:addBindItem(30211, 1)
        end
    end
}
--动感时尚礼包
gdItemExtension[30350] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local gender = entity:getGender()
        if gender == 1 then
            entity:addBindItem(81222, 1)
        else
            entity:addBindItem(81233, 1)
        end
    end
}
--苗疆风情礼包
gdItemExtension[30351] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local gender = entity:getGender()
        if gender == 1 then
            entity:addBindItem(81244, 1)
        else
            entity:addBindItem(81255, 1)
        end
    end
}
--青涩校园礼包
gdItemExtension[30352] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local gender = entity:getGender()
        if gender == 1 then
            entity:addBindItem(81266, 1)
        else
            entity:addBindItem(81277, 1)
        end
    end
}
--灵魂石福袋
gdItemExtension[30349] =
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local nProbability = math.random(100)
        if nProbability <= 95 then
            entity:addBindItem(40011, 1)
        elseif nProbability > 95 then
            entity:addBindItem(40011, 2)
        end
    end
}
--翅膀小福袋
gdItemExtension[30353] =
{
    onUse = function(entity,rid,count)
	local embag  = entity:getBagEmptyCnt()
	if (embag < 1) then
	    return Error.Item_BagisFull
	end
	local nProbability = math.random(100)
	if nProbability <= 85 then
	    entity:addBindItem(80001, 1)
	elseif nProbability > 85 then
	    entity:addBindItem(80001, 2)
	end
    end
}
--翅膀福袋
gdItemExtension[30354] =
{
    onUse = function(entity,rid,count)
	local embag  = entity:getBagEmptyCnt()
	if (embag < 1) then
	    return Error.Item_BagisFull
	end
	local nProbability = math.random(100)
	if nProbability <= 90 then
	    entity:addBindItem(80002, 1)
	elseif nProbability > 90 then
	    entity:addBindItem(80002, 2)
	end
    end
}
--翅膀大福袋
gdItemExtension[30355] =
{
    onUse = function(entity,rid,count)
	local embag  = entity:getBagEmptyCnt()
	if (embag < 1) then
	    return Error.Item_BagisFull
	end
	local nProbability = math.random(100)
	if nProbability <= 90 then
	    entity:addBindItem(80004, 1)
	elseif nProbability > 90 then
	    entity:addBindItem(80004, 2)
	end
    end
}
--冲级至尊大礼包
gdItemExtension[30356] =
{
    onUse = function(entity,rid,count)
	local embag  = entity:getBagEmptyCnt()
	if (embag < 1) then
	    return Error.Item_BagisFull
	end
	local usecnt = entity:getProps(EntityProp.cjzzlb_get_count)
	local  nProbability =  math.random(1000)
	if usecnt <= 300 then
	    while nProbability >= 999 do
		nProbability = math.random(1000)
	    end
	end
	entity:addProps(EntityProp.gqbx_get_count,1)
	if nProbability <= 500 then
	    entity:addBindItem(30161, 1)
	elseif nProbability > 500 and nProbability <= 960 then
	    entity:addBindItem(30162, 1)
	elseif nProbability > 960 and nProbability <= 996 then
	    entity:addBindItem(30163, 1)
	    _G.syncFloatMessage(tostring(entity:getName()) .. "通过冲级至尊大礼包开出8倍经验神符(8小时)*1!")
	elseif nProbability > 996 and nProbability <= 998 then
	    entity:addBindItem(30164, 1)
	    _G.syncFloatMessage(tostring(entity:getName()) .. "通过冲级至尊大礼包开出10倍经验神符(8小时)*1!")
	elseif nProbability > 998  and nProbability <= 1000 then
	    _G.syncFloatMessage(tostring(entity:getName()) .. "通过冲级至尊大礼包开出10000元宝!")
	    entity:addBindItem(3, 10000)
	    entity:setProps(EntityProp.cjzzlb_get_count,1)
	end
	entity:saveProps(EntityProp.cjzzlb_get_count)
    end
}
--元宝开开乐礼包
gdItemExtension[30357] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local nProbability = math.random(100)
		if nProbability <= 26 then
			entity:addBindItem(3, 10)
		elseif nProbability > 26 and nProbability<=31 then
			entity:addBindItem(3, 20)
--			_G.syncFloatMessage(tostring(entity:getName()) .. "通过元宝开开乐礼包开出20元宝!")
		elseif nProbability > 31 and nProbability<=32 then
			entity:addBindItem(3, 88)
			_G.syncFloatMessage(tostring(entity:getName()) .. "通过元宝开开乐礼包开出88元宝!")
		elseif nProbability > 32 and nProbability<=99 then
			entity:addBindItem(3, 1)
		elseif nProbability > 99 then
			entity:addBindItem(30358, 1)
			_G.syncFloatMessage(tostring(entity:getName()) .. "通过元宝开开乐礼包开出元宝开开乐大礼包!")
		end
	end
}
--元宝开开乐大礼包
gdItemExtension[30358] =
{
	onUse = function(entity,rid,count)
--		local embag  = entity:getBagEmptyCnt()
--		if (embag < 1) then
--			return Error.Item_BagisFull
--		end
		local nProbability = math.random(100)
		if nProbability <= 22 then
			entity:addBindItem(3, 100)
		elseif nProbability > 22 and nProbability<=32 then
			entity:addBindItem(3, 200)
--			_G.syncFloatMessage(tostring(entity:getName()) .. "通过元宝开开乐大礼包礼包开出200元宝!")
		elseif nProbability > 32 and nProbability<=99 then
			entity:addBindItem(3, 10)
		elseif nProbability > 99 then
			entity:addBindItem(3, 500)
			_G.syncFloatMessage(tostring(entity:getName()) .. "通过元宝开开乐大礼包礼包开出500元宝!")
--		elseif nProbability > 999 then
--			entity:addBindItem(3, 10000)
--			_G.syncFloatMessage(tostring(entity:getName()) .. "通过元宝开开乐大礼包礼包开出10000元宝!")
		end
	end
}
--70级装备包
gdItemExtension[30359] =
{
	onUse = function(entity,rid,count)
		local level = entity:getLevel()
		local reborn = entity:getProps(EntityProp.attr_reborn)
		if level < 60 and tonumber(reborn) < 1 then
			return Error.NotEnoughLevel
		end
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local career = tonumber(entity:getStaticID())			--获取职业 战士 1 法师 2 道士 3
		local gender = tonumber(entity:getGender())  -- 性别 男= 1 女= 2
		local nProbability = math.random(8)
		local t_equip = {
			[1] = {
				[1] = {60110,60111,60112,60114,60115,60116,60117,60118},
				[2] = {60170,60171,60172,60174,60175,60176,60177,60178},
				[3] = {60050,60051,60052,60054,60055,60056,60057,60058},
			},
			[2] = {
				[1] = {60110,60111,60113,60114,60115,60116,60117,60118},
				[2] = {60170,60171,60173,60174,60175,60176,60177,60178},
				[3] = {60050,60051,60053,60054,60055,60056,60057,60058},
			},
		}
		local item_id = t_equip[gender][career][nProbability]
		if item_id then
			entity:addItem(item_id, 1)
		else
			return Error.Unknown
		end
	end
}
------------------------------------------------------------------------------------
--腾讯新增物品
------------------------------------------------------------------------------------
--黄金雷锤礼包
gdItemExtension[30360] =
{
	onUse = function(entity,rid,count)
		if entity:getLevel()<30 then
			return Error.NotEnoughLevel
		end
		local embag  = entity:getBagEmptyCnt()
		if (embag < 10) then
			return Error.Item_BagisFull
		end
		entity:addItem(82000,10)
	end
}
--生花妙笔礼包
gdItemExtension[30361] =
{
	onUse = function(entity,rid,count)
		if entity:getLevel()<30 then
			return Error.NotEnoughLevel
		end
		local embag  = entity:getBagEmptyCnt()
		if (embag < 10) then
			return Error.Item_BagisFull
		end
		entity:addItem(82036,10)
	end
}
--如意金箍棒礼包
gdItemExtension[30362] =
{
	onUse = function(entity,rid,count)
		if entity:getLevel()<30 then
			return Error.NotEnoughLevel
		end
		local embag  = entity:getBagEmptyCnt()
		if (embag < 10) then
			return Error.Item_BagisFull
		end
		entity:addItem(82012,10)
	end
}
--黄金雷锤礼包
gdItemExtension[30363] =
{
	onUse = function(entity,rid,count)
		if entity:getLevel()<30 then
			return Error.NotEnoughLevel
		end
		local embag  = entity:getBagEmptyCnt()
		if (embag < 10) then
			return Error.Item_BagisFull
		end
		entity:addItem(82024,10)
	end
}
--魂石福袋
gdItemExtension[30364] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local nProbability = math.random(1000)
		if nProbability <= 330 then
			entity:addItem(30310,1)
		elseif nProbability >330 and nProbability <=930  then
			entity:addItem(30311,1)
		elseif nProbability > 930 and nProbability <= 990 then
			entity:addItem(30312,1)
			_G.syncFloatMessage(tostring(entity:getName()) .. "通过魂石福袋开出6级魂石袋*1!")
		elseif nProbability > 990 and nProbability <= 999 then
			entity:addItem(30313,1)
			_G.syncFloatMessage(tostring(entity:getName()) .. "通过魂石福袋开出7级魂石袋*1!")
		else
			entity:addItem(30314,1)
			_G.syncFloatMessage(tostring(entity:getName()) .. "通过魂石福袋开出8级魂石袋*1!")
		end
	end
}
--金蛋
gdItemExtension[30438] = {					--金蛋
	onUse = function(entity, rid, count)
        local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local n = math.random(970)
        if n <= 1 then
            entity:addBindItem(40143, 1)
			_G.syncFloatMessage("玩家" .. entity:getName() .. "通过开启金蛋箱获得：" .. gdItems[40143].name .. "*1")
        elseif n > 1 and n <=90 then
            entity:addBindItem(30166, 1)
		elseif n > 90 and n <=160 then
			entity:addBindItem(30051, 1)
		elseif n > 160 and n <=230 then
			entity:addBindItem(39043, 1)
		elseif n > 230 and n <=300 then
			entity:addBindItem(40012, 1)
		elseif n > 300 and n <=370 then
			entity:addBindItem(40042, 1)
		elseif n > 370 and n <=440 then
			entity:addBindItem(30206, 1)
		elseif n > 440 and n <=530 then
			entity:addBindItem(30060, 1)
		elseif n > 530 and n <=580 then
			entity:addBindItem(40077, 1)
		elseif n > 580 and n <=650 then
			entity:addBindItem(40011, 1)
		elseif n > 650 and n <=720 then
			entity:addBindItem(40053, 1)
		elseif n > 720 and n <=810 then
			entity:addBindItem(40016, 1)
		elseif n > 810 and n <=860 then
			entity:addBindItem(40071, 1)
		elseif n > 860 and n <=940 then
			entity:addBindItem(30094, 1)
--[[		elseif n > 930 and n <=935 then
			entity:addBindItem(30350, 1)
			_G.syncFloatMessage("玩家" .. entity:getName() .. "通过开启金蛋获得：" .. gdItems[30350].name .. "*1")
		elseif n > 935 and n <=940 then
			entity:addItem(30429, 1)
			_G.syncFloatMessage("玩家" .. entity:getName() .. "通过开启金蛋获得：" .. gdItems[30429].name .. "*1")]]--
		elseif n > 940 and n <=970 then
			entity:addBindItem(40004, 1)
			_G.syncFloatMessage("玩家" .. entity:getName() .. "通过开启金蛋获得：" .. gdItems[40004].name .. "*1")
        end
	end
}
--圣诞装饰礼盒
gdItemExtension[30378] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local gender = entity:getGender()  -- 性别 男= 1 女= 2
		if gender == 1 then
			entity:addBindItem(81151,1)
		else
			entity:addBindItem(81153,1)
		end
	end
}
--百宝箱
gdItemExtension[30377] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local t_item = {
			{60231,10,true},
			{60239,10,true},
			{60223,20,true},
			{30078,1,true},
			{30073,1,true},
			{30083,1,true},
			{80006,1,true},
			{30059,10,true},
			{30364,70},
			{30355,40},
			{30349,90},
			{30350,10,true,true},
			{30351,10,true,true},
			{30352,10,true,true},
			{30311,70},
			{30091,30,true},
			{40015,30,true},
			{40136,50},
			{30359,50},
			{40077,70},
			{40071,70},
			{30004,70},
			{40016,70},
			{30060,70},
			{40004,70},
			{30094,70},
		}
		local n = 0
		local t_probability = {}
		for key,value in ipairs(t_item) do
			n = n + value[2]
			table.insert(t_probability,n)
		end
		local nProbability = math.random(n)
		for k,v in ipairs(t_probability) do
			if nProbability <= v then
				if t_item[k][4] then
					entity:addBindItem(t_item[k][1],1)
				else
					entity:addItem(t_item[k][1],1)
				end
				if t_item[k][3] then
					_G.syncFloatMessage("玩家" .. entity:getName() .. "通过开启圣诞百宝箱获得：" .. gdItems[t_item[k][1]].name .. "*1")
				end
				break
			end
		end
	end
}
--新年超值礼包 
gdItemExtension[30379] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local nProbability = math.random(100)
		if nProbability <= 60 then
			entity:addBindItem(40053,2)
		elseif nProbability >60 and nProbability <=80  then
			entity:addBindItem(40011,2)
		elseif nProbability > 80 and nProbability <= 95 then
			entity:addBindItem(30309,1)
		else
			entity:addBindItem(30162,1)
		end
	end
}
gdItemExtension[30380] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local nProbability = math.random(100)
		if nProbability <= 9 then
			entity:addBindItem(30350,1)
		elseif nProbability == 10  then
			entity:addBindItem(80004,1)
		elseif nProbability > 10 and nProbability <= 40 then
			entity:addBindItem(30310,1)
		elseif nProbability > 40 and nProbability <= 80 then
			entity:addBindItem(40011,5)
		else
			entity:addBindItem(30163,1)
		end
	end
}
gdItemExtension[30381] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local nProbability = math.random(100)
		if nProbability <= 10 then
			entity:addBindItem(30004,1)
		elseif nProbability > 10 and nProbability <= 25 then
			entity:addBindItem(40004,2)
		elseif nProbability > 25 and nProbability <= 40 then
			entity:addBindItem(40011,10)
		elseif nProbability > 40 and nProbability <= 60 then
			entity:addBindItem(30311,1)
		elseif nProbability > 60 and nProbability <= 80 then
			entity:addBindItem(40053,20)
		elseif nProbability > 80 and nProbability <= 99 then
			entity:addBindItem(30351,1)
		else
			entity:addBindItem(40015,1)
		end
	end
}
gdItemExtension[30382] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		entity:addBindItem(30352,1)
		local nProbability = math.random(100)
		if nProbability <= 18 then
			entity:addBindItem(40015,1)
		elseif nProbability > 18 and nProbability <= 20 then
			entity:addBindItem(80007,1)
		elseif nProbability > 20 and nProbability <= 40 then
			entity:addBindItem(40136,5)
		elseif nProbability > 40 and nProbability <= 70 then
			entity:addBindItem(40011,100)
		else
			entity:addBindItem(40004,10)
		end
	end
}
--风华正茂礼包
gdItemExtension[30383] =
{
	onUse = function(entity,rid,count)
		local embag  = entity:getBagEmptyCnt()
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local gender = entity:getGender()
		if gender == 1 then
			entity:addBindItem(81294,1)
		else
			entity:addBindItem(81305,1)
		end
	end
}
--------------------------------------------特殊物品---------------------------------------
--秒杀
gdItemExtension[4444] =--全图秒杀
{
	onUse = function(entity,rid,count)
		local scene = entity:getScene()
		if scene then
			-- 秒杀所有怪物
			scene:forEachEntityM(function(mentity)
				local cbt = mentity:getCombatSys()
				if cbt then
					local damage = cbt:getMaxHP()
					cbt:updateHP(-damage,1)
					mentity:setProps(EntityProp.attr_last_attacker,entity:getID())
				else
					log.error("damage entity Find no entity by eid!")
				end
			end)
			
			-- 秒杀所有玩家（自己除外，不增加PK值）
			scene:forEachEntityP(function(pentity)
				-- 排除使用道具的玩家自己
				if pentity:getID() == entity:getID() then
					return
				end
				
				local cbt = pentity:getCombatSys()
				if cbt then
					local damage = cbt:getMaxHP()
					cbt:updateHP(-damage, 1)
					-- 不设置last_attacker来避免增加PK值
				else
					log.error("damage player Find no entity by eid!")
				end
			end)
		end
		
		-- 返回Error.bowlnoneedrmv表示不消耗道具
		return Error.bowlnoneedrmv
	end
}
gdItemExtension[5555] =             ---突破蛋
{
	onUse = function(entity,rid,count)
	if entity:getLevel()<500 then
			return Error.NotEnoughLevel
		end
		local rebornlvl = entity:getProps(EntityProp.attr_reborn)
		local evocon = gdEvolutionCondition[rebornlvl]
		local maxlevel = 500
		if evocon then
			maxlevel = evocon.maxlvl
		end
		local curlvl = entity:getLevel()
		if curlvl >= 1000 then
			return Error.LevelMax
		end 	

		local Scene = entity:getScene()
		--local maxlevel = entity:getProps(gdEvolutionCondition[rebornlvl].maxlvl)
		if (curlvl + 5) > maxlevel then
			log.error("failed to addlevel,have reached the top level")
			return Error.LevelMax
		end

		local curexp = entity:getExp()
		local tgtexp = gdlevelupexp[curlvl] -  (gdlevelupexp[curlvl - 5] or 0)
		log.info("tgtexp, curexp "..tgtexp,curexp)
		if not tgtexp then
			log.error("failed to addlevel,error input level")
			return Error.Unknown
		end
		if tgtexp < curexp then
			log.error("failed to addlevel,error input level")
		end
		entity:addExp(tgtexp-curexp)
		return Error.Success
	end
}
-- 转身石（ID: 5556）
gdItemExtension[5556] = {
    onUse = function(entity, rid, count)
        local reborn = entity:getProps(EP.attr_reborn)
        local nextReborn = reborn + 1
        local condition = gdEvolutionCondition[nextReborn]
        
        -- 检查下一转是否需要渡劫
        if condition and condition.needrobbery == 1 then
            local robberySuccess = entity:getEventDataX(EID.robbery)
            if robberySuccess ~= 1 then
                return Error.NotEnoughCondition
            end
        end
        
        -- 保存当前转生次数，用于判断转身是否成功
        local currentRebornBefore = entity:getProps(EP.attr_reborn)
        
        -- 执行转身操作
        entity:reborn()
        
        -- 检查转身后转生次数是否增加
        local currentRebornAfter = entity:getProps(EP.attr_reborn)
        local isSuccess = (currentRebornAfter > currentRebornBefore)
        
        if isSuccess then
            -- 转身成功
            if condition and condition.needrobbery == 1 then
                -- 只有需要渡劫的转身成功后才清除印记
                entity:setEventDataX(EID.robbery, 0)
                entity:syncEventData(EID.robbery)
            end
            -- 成功时不消耗物品，返回特殊错误码
            return Error.bowlnoneedrmv
        else
            -- 转身失败，不消耗物品
            return Error.NotEnoughCondition
        end
    end
}


gdItemExtension[5557] = {      --渡劫丹
    onUse = function(entity, rid, count)
        -- 判断等级是否达到1000级
        local currentLevel = entity:getLevel()
        if currentLevel < 1000 then
            return Error.NotEnoughLevel  
        end
        
        local reborn = entity:getProps(EP.attr_reborn)
        local nextReborn = reborn + 1
        local condition = gdEvolutionCondition[nextReborn]
        
        if condition and condition.needrobbery == 1 then
            local random = math.random(1, 100)
            if random <= 25 then
                -- 成功：获得天劫印记
                entity:setEventDataX(EID.robbery, 1)
                entity:syncEventData(EID.robbery)
                _G.syncFloatMessage(tostring(entity:getName()) .. "使用渡劫丹，成功获得天劫印记！")
            else
                -- 失败：将等级设为34级
                entity:setLevel(34)
                
                -- 使用金蚕王同样的升级逻辑来升到35级
                local curlvl = 34
                local curexp = entity:getExp()
                
                -- 计算从34级升到35级所需的经验
                if gdlevelupexp and gdlevelupexp[curlvl] then
                    local tgtexp = gdlevelupexp[curlvl] - (gdlevelupexp[curlvl - 1] or 0)
                    if tgtexp and tgtexp > 0 then
                        -- 给予足够从34级升到35级的经验
                        entity:addExp(tgtexp - curexp)
                    end
                end
                
                _G.syncFloatMessage(tostring(entity:getName()) .. "使用渡劫丹，渡劫失败！等级降至35级！")
            end
        end
        return Error.Success
    end
}




gdItemExtension[5558] = {  -- 大乱斗令牌
    onUse = function(entity, rid, count)
        local playerName = entity:getName()
        local centerX, centerY, dir = entity:getPosition()
        local scene = entity:getScene()
        
        if not scene then
            return 1
        end
        
        -- 新增限制：只能在冰与火使用
        if scene:getStaticID() ~= MapID.byh then
            return Error.InvalidScene
        end
        
        -- 召唤配置：{怪物ID, 数量, 怪物名称}
        local SUMMON_CONFIG = {
            {5403, 10, "地狱男爵"},
            {5404, 10, "暗夜守护"}, 
            {5405, 10, "暗夜驯兽"},
            {5406, 10, "暗夜巡查"},
        }
        
        -- 生成召唤位置（5x5范围）
        local radius = 2
        local positions = {}
        for dx = -radius, radius do
            for dy = -radius, radius do
                table.insert(positions, {centerX + dx, centerY + dy})
            end
        end
        
        math.randomseed(os.time())
        
        -- 按配置召唤
        for _, config in ipairs(SUMMON_CONFIG) do
            local monsterId, monsterCount, monsterName = config[1], config[2], config[3]
            
            for i = 1, monsterCount do
                local randomPos = positions[math.random(#positions)]
                scene:addM(monsterId, randomPos[1], randomPos[2])
            end
        end
        
        -- 公告
        if _G.syncFloatMessage then
            _G.syncFloatMessage(playerName .. " 开启BOSS大乱斗！")
        end
        
        return 0
    end
}





--充值
gdItemExtension[101] = 	--1元充值卷
{
	onUse = function(entity,rid,count)
	Gift.onRecharge(entity,10000)
	             entity:addGold(10000)
			return Error.Success
	end,
}
gdItemExtension[505] = 	--5元充值卷
{
	onUse = function(entity,rid,count)
	Gift.onRecharge(entity,50000)
	             entity:addGold(50000)
			return Error.Success
	end,
}
gdItemExtension[1010] = 	--10元充值卷
{
	onUse = function(entity,rid,count)
	Gift.onRecharge(entity,100000)
	             entity:addGold(100000)
			return Error.Success
	end,
}
gdItemExtension[5050] = 	--50元充值卷
{
	onUse = function(entity,rid,count)
	Gift.onRecharge(entity,500000)
	             entity:addGold(500000)
			return Error.Success
	end,
}
gdItemExtension[100100] = 	--100元充值卷
{
	onUse = function(entity,rid,count)
	Gift.onRecharge(entity,1000000)
	             entity:addGold(1000000)
			return Error.Success
	end,
}
gdItemExtension[40144] =----------------新手盒子
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 17) then
            return Error.Item_BagisFull
        end
        entity:addItem(60180, 1)
        entity:addItem(60181, 1)
        entity:addItem(60182, 1)
        entity:addItem(60183, 1)
		entity:addItem(60184, 1)
		entity:addItem(60185, 2)
		entity:addItem(60186, 1)
		entity:addItem(60187, 1)
		entity:addItem(60188, 1)
		entity:addItem(60189, 1)
		entity:addBindItem(10070, 12)
		entity:addBindItem(10071, 12)
		entity:addBindItem(10072, 12)
		entity:addBindItem(10073, 12)
		entity:addBindItem(10074, 12)
		entity:addBindItem(10075, 12)
		entity:addBindItem(10076, 12)
		
    end
}
gdItemExtension[50999] = {       -------超级盒子
    onUse = function(entity, rid, count)
        local embag = entity:getBagEmptyCnt()
        if (embag < 1) then
            return Error.Item_BagisFull
        end
        local n = math.random(100)
        if n and n <= 1 then
            -- 概率：2% (1-2)
            entity:addItem(4, 888, Opcode.op_summer)  --仙玉
        elseif n > 1 and n <= 62 then
            -- 概率：60% (3-62)
			entity:addItem(41112, 20, Opcode.op_summer)  -- 橙钻石
        elseif n > 62 and n <= 80 then
            -- 概率：18% (63-80)
            entity:addItem(40004, 20, Opcode.op_summer)  -- 5级灵石
        elseif n > 80 and n <= 100 then
            -- 概率：20% (81-100)
            entity:addItem(40004, 10, Opcode.op_summer)  -- 5级灵石
        end
    end
}



gdItemExtension[51000] = {       -------四季盒子
    onUse = function(entity, rid, count)
        local embag = entity:getBagEmptyCnt()
        if (embag < 5) then
            return Error.Item_BagisFull
        end
        local n = math.random(100)
        if n and n <= 2 then
            -- 最低概率（2%）：获得最多物品
            entity:addItem(51115, 1, Opcode.op_summer)  -- 17级魂石袋
            entity:addItem(40004, 150, Opcode.op_summer)  -- 5级灵石
            entity:addItem(41111, 500, Opcode.op_summer)  -- 紫钻石
            entity:addItem(41112, 300, Opcode.op_summer)  -- 橙钻石
			entity:addBindItem(5555, 7, Opcode.op_summer)  -- 突破蛋
        elseif n > 2 and n <= 62 then
            -- 中等概率（60%）：获得中等数量物品
            entity:addItem(51114, 2, Opcode.op_summer)  -- 16级魂石袋
            entity:addItem(40004, 120, Opcode.op_summer)  -- 5级灵石
            entity:addItem(41111, 450, Opcode.op_summer)  -- 紫钻石
            entity:addItem(41112, 250, Opcode.op_summer)  -- 橙钻石
			entity:addBindItem(5555, 5, Opcode.op_summer)  -- 突破蛋
        elseif n > 62 and n <= 80 then
            -- 较高概率（18%）：获得较少数量物品
            entity:addItem(51114, 1, Opcode.op_summer)  -- 16级魂石袋
            entity:addItem(40004, 100, Opcode.op_summer)  -- 5级灵石
            entity:addItem(41111, 400, Opcode.op_summer)  -- 紫钻石
            entity:addItem(41112, 200, Opcode.op_summer)  -- 橙钻石
			entity:addBindItem(5555, 4, Opcode.op_summer)  -- 突破蛋
        elseif n > 80 and n <= 100 then
            -- 最高概率（20%）：获得最少数量物品
            entity:addItem(51114, 1, Opcode.op_summer)  -- 16级魂石袋
            entity:addItem(40004, 80, Opcode.op_summer)  -- 5级灵石
            entity:addItem(41111, 350, Opcode.op_summer)  -- 紫钻石
            entity:addItem(41112, 150, Opcode.op_summer)  -- 橙钻石
			entity:addBindItem(5555, 3, Opcode.op_summer)  -- 突破蛋
        end
    end
}
gdItemExtension[51001] = {       -------五行盒子
    onUse = function(entity, rid, count)
        local embag = entity:getBagEmptyCnt()
        if (embag < 5) then
            return Error.Item_BagisFull
        end
        local n = math.random(100)
        if n and n <= 2 then
            -- 最低概率（2%）：获得最多物品
            entity:addItem(51116, 1, Opcode.op_summer)  -- 18级魂石袋
            entity:addItem(40004, 250, Opcode.op_summer)  -- 5级灵石
			entity:addBindItem(5555, 10, Opcode.op_summer)  -- 突破蛋
            
        elseif n > 2 and n <= 62 then
            -- 中等概率（60%）：获得中等数量物品
            entity:addItem(51115, 2, Opcode.op_summer)  -- 17级魂石袋
            entity:addItem(40004, 220, Opcode.op_summer)  -- 5级灵石
			entity:addBindItem(5555, 10, Opcode.op_summer)  -- 突破蛋
            
        elseif n > 62 and n <= 80 then
            -- 较高概率（18%）：获得较少数量物品
            entity:addItem(51114, 2, Opcode.op_summer)  -- 16级魂石袋
            entity:addItem(40004, 200, Opcode.op_summer)  -- 5级灵石
			entity:addBindItem(5555, 8, Opcode.op_summer)  -- 突破蛋
            
        elseif n > 80 and n <= 100 then
            -- 最高概率（20%）：获得最少数量物品
            entity:addItem(51114, 1, Opcode.op_summer)  -- 16级魂石袋
            entity:addItem(40004, 120, Opcode.op_summer)  -- 5级灵石
			entity:addBindItem(5555, 5, Opcode.op_summer)  -- 突破蛋
            
        end
    end
}
gdItemExtension[51113] =----------------神器盒子
{
    onUse = function(entity,rid,count)
        local embag  = entity:getBagEmptyCnt()
        if (embag < 6) then
            return Error.Item_BagisFull
        end
        entity:addItem(86000, 1)
        entity:addItem(86001, 1)
        entity:addItem(86002, 1)
        entity:addItem(86003, 1)
		entity:addItem(86004, 1)
		entity:addItem(86005, 1)
		
    end
}
------------------------------------魂石袋16-20-------------------------------
gdItemExtension[51114] =
{
	onUse = function(entity,rid,count)--16级魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10112,10113,10114,10115,{10116,10117,10118}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}
gdItemExtension[51115] =
{
	onUse = function(entity,rid,count)--17级魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10119,10120,10121,10122,{10123,10124,10125}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}
gdItemExtension[51116] =
{
	onUse = function(entity,rid,count)--18级魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10126,10127,10128,10129,{10130,10131,10132}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}
gdItemExtension[51117] =
{
	onUse = function(entity,rid,count)--19魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10133,10134,10135,10136,{10137,10138,10139}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}
gdItemExtension[51118] =
{
	onUse = function(entity,rid,count)--20魂石袋
		local ItemCnt = 1
		local embag  = entity:getBagEmptyCnt()
		if (embag < ItemCnt) then
			return Error.Item_BagisFull
		end
		return Error.Success
	end,
	onUsed = function(entity,item)
		doAddItemByTable(entity,{10140,10141,10142,10143,{10144,10145,10146}}, 1, item:getProps(IP.Item_Bind)>0 or false)
		entity:rmvItemExactly(item:getIID(), 1)
		return Error.Success
	end
}
------------------------------------------------------------------------
gdItemExtension[676545075] =--------无限元宝
{
	
	onUse = function(entity,rid,count)
		entity:addGold(100000000)
		-- 返回Error.bowlnoneedrmv表示不消耗道具
		return Error.bowlnoneedrmv
	end,


}