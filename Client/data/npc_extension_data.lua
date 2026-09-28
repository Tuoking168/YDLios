if not gdNPCExtension then
	gdNPCExtension = {}
end

if not gdNPCFuncShow then
	gdNPCFuncShow = {}
end

local EP = EntityProp
local SP = SceneProp
local WP = WorldProp
local IP = ItemProp
local FP = FuncProp
local GP = GuildProp

local function makeSuitTable(entity, datas)
	local gender = entity:getGender()  -- 性别 男= 1 女= 2
	local map = {}
	for d = 0,1 do
		table.insert(map, datas+d)
	end
	if gender == 1 then
		table.insert(map,datas+2)
	elseif gender == 2 then
		table.insert(map,datas+3)
	end
	for d = 4,8 do
		table.insert(map, datas+d)
	end
	table.insert(map, datas+5)
	return map
end

local function doAddItemByMap(entity, itable, count)
	count = count or 1
	for k,v in pairs(itable) do
		entity:addItem(v,1)
	end
	return 0
end

local function meetRequiredLvl(entity, lvl, reborn)
	reborn = reborn or 0
	local mreborn = entity:getProps(EP.attr_reborn)
	if mreborn==reborn then
		if entity:getLevel()>=lvl then
			return true
		end
	elseif mreborn>reborn then
		return true
	end
end

local function meetRequiredLvlEID(entity, eid)
	local ed = gdEventData[eid]
	if ed then
		log.info(ed.requirelvl)
		return meetRequiredLvl(entity, ed.requirelvl, ed.reborn)
	else
		log.error("###invalid event id: ", eid)
	end
end

local function isProtectGirl(entity)
	local isgirlprotect = entity:getProps(EntityProp.attr_meinvhusong_monstergid)
	if isgirlprotect ~= 0 then
		return true
	end
	return false
end

--[[gdNPCExtension[40] = {
	[1] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		else
			entity:addItem(40000,10)
			return Error.success
		end
	end,
	[2] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		else
			entity:addItem(40005,10)
			return Error.success
		end
	end,
}
gdNPCExtension[41] = {
	[1] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 2) then
			return Error.Item_BagisFull
		else
			entity:addItem(40008,20)
			return Error.success
		end
	end,
	[2] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 2) then
			return Error.Item_BagisFull
		else
			entity:addItem(40009,20)
			return Error.success
		end
	end,
	[3] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 2) then
			return Error.Item_BagisFull
		else
			entity:addItem(40010,20)
			return Error.success
		end
	end,
	[4] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 2) then
			return Error.Item_BagisFull
		else
			entity:addItem(40012,200)
			return Error.success
		end
	end,
}

gdNPCExtension[43] = {
	[1] = function(entity)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 9) then
			return Error.Item_BagisFull
		end
		local map1={}
		if career == 1 then
			map1 = makeSuitTable(entity, 60060)
		elseif career == 2 then
			map1 = makeSuitTable(entity, 60120)
		elseif career == 3 then
			map1 = makeSuitTable(entity, 60000)
		end
		return doAddItemByMap(entity,map1,9)
	end,
	[2] = function(entity)
		local career = entity:getStaticID()		--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 9) then
			return Error.Item_BagisFull
		end
		local map1={}
		if career == 1 then
			map1 = makeSuitTable(entity, 60070)
		elseif career == 2 then
			map1 = makeSuitTable(entity, 60130)
		elseif career == 3 then
			map1 = makeSuitTable(entity, 60010)
		end
		return doAddItemByMap(entity,map1,9)
	end,
	[3] = function(entity)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 9) then
			return Error.Item_BagisFull
		end
		local map1={}
		if career == 1 then
			map1 = makeSuitTable(entity, 60080)
		elseif career == 2 then
			map1 = makeSuitTable(entity, 60140)
		elseif career == 3 then
			map1 = makeSuitTable(entity, 60020)
		end
		return doAddItemByMap(entity,map1,9)
	end,
	[4] = function(entity)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 9) then
			return Error.Item_BagisFull
		end
		local map1={}
		if career == 1 then
			map1 = makeSuitTable(entity, 60090)
		elseif career == 2 then
			map1 = makeSuitTable(entity, 60150)
		elseif career == 3 then
			map1 = makeSuitTable(entity, 60030)
		end
		return doAddItemByMap(entity,map1,9)
	end,
	[5] = function(entity)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 9) then
			return Error.Item_BagisFull
		end
		local map1={}
		if career == 1 then
			map1 = makeSuitTable(entity, 60100)
		elseif career == 2 then
			map1 = makeSuitTable(entity, 60160)
		elseif career == 3 then
			map1 = makeSuitTable(entity, 60040)
		end
		return doAddItemByMap(entity,map1,9)
	end,
	[6] = function(entity)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 9) then
			return Error.Item_BagisFull
		end
		local map1={}
		if career == 1 then
			map1 = makeSuitTable(entity, 60110)
		elseif career == 2 then
			map1 = makeSuitTable(entity, 60170)
		elseif career == 3 then
			map1 = makeSuitTable(entity, 60050)
		end
		return doAddItemByMap(entity,map1,9)
	end,
	[7] = function(entity)
		local gender = entity:getGender()  -- 性别 男= 1 女= 2
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 10) then
			return Error.Item_BagisFull
		end
		local map1={60180,60181,60182,60183,60184,60185,60186,60187,60188,60189}
		return doAddItemByMap(entity,map1,10)
	end,
	[8] = function(entity)
		local career = entity:getStaticID()			--获取职业 战士 1 法师 2 道士 3
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 10) then
			return Error.Item_BagisFull
		end
		local map1={60191,60192,60193,60194,60195,60196,60197,60198,60199}
		return doAddItemByMap(entity,map1,10)
	end,
}


gdNPCExtension[50] = {
	[1] = function (entity)
		entity:addItem(38000, 1)
		return Error.Success
	end,
	[2] = function(entity)
		entity:addItem(38001, 1)
		return Error.Success
	end
}


--
-- 金币测试
gdNPCExtension[51] = {
	[1] = function (entity)
		entity:addMoney(100000,Opcode.Op_Test)
		return Error.Success
	end,
	[2] = function(entity)
		entity:addGold(100001,Opcode.Op_Test)
		return Error.Success
	end,
	[3] = function(entity)
		entity:addCoupon(100002,Opcode.Op_Test)
		return Error.Success
	end,
	[4] = function(entity)
		entity:addIntegration(1000003,Opcode.Op_Test)
		return Error.Success
	end,
	[5] = function(entity)
		entity:addHonor(1000,Opcode.Op_Test)
		return Error.Success
	end,
}
--
-- 转生测试
gdNPCExtension[52] = {
	[1] = function (entity)
		entity:reborn()
		return Error.Success
	end,
}

--副本测试
gdNPCExtension[54] = {
	[1] = function (entity)

		return Error.Success
	end,
}


--活动测试
gdNPCExtension[55] = {
	[1] = function (entity)

		return Error.Success
	end,
}

--时装测试
gdNPCExtension[58] = {
	[1] = function (entity)
		entity:addItem(81000, 1)
		return Error.Success
	end,
	[2] = function(entity)
		entity:addItem(81033, 1)
		return Error.Success
	end,
	[3] = function(entity)
		entity:addItem(81140, 1)
		return Error.Success
	end,
	[4] = function(entity)
		entity:addItem(81044, 1)
		return Error.Success
	end,
	[5] = function(entity)
		entity:addItem(81055, 1)
		return Error.Success
	end,
	[6] = function (entity)
		entity:addItem(80000, 1)
		return Error.Success
	end,
	[7] = function(entity)
		entity:addItem(80001, 1)
		return Error.Success
	end,
	[8] = function(entity)
		entity:addItem(80002, 1)
		return Error.Success
	end,
}

gdNPCExtension[5801] = {
	[1] = function (entity)
		entity:addItem(81066, 1)
		return Error.Success
	end,
	[2] = function(entity)
		entity:addItem(81076, 1)
		return Error.Success
	end,
	[3] = function(entity)
		entity:addItem(81086, 1)
		return Error.Success
	end,
	[4] = function(entity)
		entity:addItem(81092, 1)
		return Error.Success
	end,
	[5] = function(entity)
		entity:addItem(81109, 1)
		return Error.Success
	end,
	[6] = function(entity)
		entity:addItem(80003, 1)
		return Error.Success
	end,
	[7] = function(entity)
		entity:addItem(80004, 1)
		return Error.Success
	end,
	[8] = function (entity)
		entity:addItem(80005, 1)
		return Error.Success
	end,
}
gdNPCExtension[5802] = {
	[1] = function (entity)
		entity:addItem(81119, 1)
		return Error.Success
	end,
	[2] = function(entity)
		entity:addItem(81167, 1)
		return Error.Success
	end,
	[3] = function(entity)
		entity:addItem(81156, 1)
		return Error.Success
	end,
	[4] = function(entity)
		entity:addItem(80006, 1)
		return Error.Success
	end,
	[5] = function(entity)
		entity:addItem(80007, 1)
		return Error.Success
	end,
	[6] = function(entity)
		entity:addItem(80008, 1)
		return Error.Success
	end,
	[7] = function(entity)
		entity:addItem(80009, 1)
		return Error.Success
	end,
}

--翅膀测试
gdNPCExtension[46] = {
	[1] = function (entity)
		entity:addItem(80000, 1)
		return Error.Success
	end,
	[2] = function(entity)
		entity:addItem(80001, 1)
		return Error.Success
	end,
	[3] = function(entity)
		entity:addItem(80002, 1)
		return Error.Success
	end,
	[4] = function(entity)
		entity:addItem(80003, 1)
		return Error.Success
	end,
	[5] = function(entity)
		entity:addItem(80004, 1)
		return Error.Success
	end,
}
gdNPCExtension[5701] = {
	[1] = function (entity)
		entity:addItem(80005, 1)
		return Error.Success
	end,
	[2] = function(entity)
		entity:addItem(80006, 1)
		return Error.Success
	end,
	[3] = function(entity)
		entity:addItem(80007, 1)
		return Error.Success
	end,
	[4] = function(entity)
		entity:addItem(80008, 1)
		return Error.Success
	end,
	[5] = function(entity)
		entity:addItem(80009, 1)
		return Error.Success
	end,
}]]--
--
-- 	仓库管理员
--
gdNPCExtension[106]  = {
	[1] = function(entity)
		return Error.NotImplemented --to do
	end
}
--
-- 	美女护送 mnhs
--
gdNPCExtension[107] = {
	[1] = function (entity)
		--美女护送任务
		if(entity:getProps(EntityProp.attr_meinvhusong_remain)==0) then
			Event.MeiNvhuSongStart(entity)
		end
		return Error.Success
	end,
	[2] = function(entity)
		return Error.Success
	end
}
gdNPCExtension[154] = {
	[1] = function (entity)
		--美女护送任务完成
		local girlgid = entity:getProps(EntityProp.attr_meinvhusong_monstergid)
		return Event.MeiNvhuSongEnd(entity,girlgid,true)
	end,
}


--
--	烈火宫使者	lhg	水晶宫	sjg
--
gdNPCExtension[1302] = {

	[3] = function(entity)	--免费领取两个烈火令
		if entity:getEventDataZ(EID.lhg)<1 then	--今天是否领取过
			entity:setEventDataZ(EID.lhg, 1)
			entity:saveEventData(EID.lhg)
			entity:addBindItem(40037, 2)
			return Error.Success
		else
			return Error.AlreadyUsed
		end
	end,
}

gdNPCExtension[13021] = {
	[1] = function (entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=10 then
			entity:useGold(10,Opcode.Op_liehuodongbuyling)
			entity:addItem(40037, 1)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[2] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=100 then
			entity:useGold(100,Opcode.Op_liehuodongbuyling)
			entity:addItem(40037, 10)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[3] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=500 then
			entity:useGold(500,Opcode.Op_liehuodongbuyling)
			entity:addItem(40037, 50)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[4] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=1000 then
			entity:useGold(1000,Opcode.Op_liehuodongbuyling)
			entity:addItem(40037, 100)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end
}
gdNPCExtension[13022] = {	-- 烈火宫进入NPC
	[1] = function (entity)
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.lhg) then
			return Error.NotEnoughLevel
		end

		local entertimes = entity:getEventDataX(EID.lhg)
		if entertimes>=2 then
			return Error.TooManyTimes
		end
		entity:addEventDataX(EID.lhg)

		local scene = entity:getScene()
		if entity:hasItem(40037,2) then
			entity:rmvItem(40037, 2)
			--
			--	ToDo goto instance
			Scene.conveyentitytoNewInstance(entity,MapID.lhg)
			return Error.Success
		else
			return Error.NotEnoughCondition
		end
		return Error.Success
	end,
	[2] = function(entity)
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.lhg) then
			return Error.NotEnoughLevel
		end
		local entertimes = entity:getEventDataX(EID.lhg)
		if entertimes>=2 then
			return Error.TooManyTimes
		end
		entity:addEventDataX(EID.lhg)
		if entity:getGold()>=20 then
			entity:useGold(20,Opcode.Op_liehuodongbuyling)
			Scene.conveyentitytoNewInstance(entity,MapID.lhg)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[3] = function(entity)
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.lhg) then
			return Error.NotEnoughLevel
		end
		local entertimes = entity:getEventDataX(EID.lhg)
		if entertimes>=2 then
			return Error.TooManyTimes
		end
		entity:addEventDataX(EID.lhg)
		if entity:getCoupon()>=60 then
			entity:useCoupon(60,Opcode.Op_liehuodongbuyling)
			Scene.conveyentitytoNewInstance(entity,MapID.lhg)
			return Error.Success
		else
			return Error.NotEnoughDiamond
		end
	end,
	[4] = function(entity)
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.lhg) then
			return Error.NotEnoughLevel
		end
		local entertimes = entity:getEventDataX(EID.lhg)
		if entertimes>=2 then
			return Error.TooManyTimes
		end
		entity:addEventDataX(EID.lhg)
		if entity:getHonor() >=9000 then
			entity:useHonor(9000,Opcode.Op_liehuodongbuyling)
			Scene.conveyentitytoNewInstance(entity,MapID.lhg)
			return Error.Success
		else
			return Error.NotEnoughHonor
		end
	end
}

gdNPCExtension[300] = {		--	烈火宫	lhg 里面的npc
	[1] = function(entity)
		local scene = entity:getScene()
		if scene:getProps(SP.lhg_layer_reward) == 0 and scene:getEntityMCount() == 0 then
			entity:addExp(scene:getProps(SP.lhg_exp),Opcode.Op_liehuodonggonex)
			scene:setProps(SP.lhg_layer_reward, 1)
		end
		Scene.conveyentitytoNPC(entity,130)
		return Error.Success
	end,
	[2] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getEntityMCount()>0 then
			return Error.NotEnoughCondition
		end

		local cnt = scene:getProps(SP.lhg_liehuolin_to_next_layer)
		if entity:hasItem(40037, cnt) then
			if scene:getProps(SP.lhg_layer_reward) ==0 then
				entity:addExp(scene:getProps(SP.lhg_exp),Opcode.Op_liehuodonggonex)
				scene:setProps(SP.lhg_layer_reward, 1)
			end
			entity:rmvItem(40037, cnt)
			scene:addTimerEvent(1, 500)
			return Error.Success
		else
			return Error.NotEnoughCondition
		end
	end,
	[3] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getEntityMCount()>0 then
			return Error.NotEnoughCondition
		end

		local cnt = scene:getProps(SP.lhg_gold_to_next_layer)
		if entity:getGold()>=cnt then
			if scene:getProps(SP.lhg_layer_reward) ==0 then
				entity:addExp(scene:getProps(SP.lhg_exp),Opcode.Op_liehuodonggonex)
				scene:setProps(SP.lhg_layer_reward, 1)
			end
			entity:useGold(cnt,Opcode.Op_liehuodonggonex)
			scene:addTimerEvent(1, 500)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[4] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getEntityMCount()>0 then
			return Error.NotEnoughCondition
		end

		local cnt = scene:getProps(SP.lhg_diamond_to_next_layer)
		if entity:getCoupon()>=cnt then
			if scene:getProps(SP.lhg_layer_reward) ==0 then
				entity:addExp(scene:getProps(SP.lhg_exp),Opcode.Op_liehuodonggonex)
				scene:setProps(SP.lhg_layer_reward, 1)
			end
			entity:useCoupon(cnt,Opcode.Op_liehuodonggonex)
			scene:addTimerEvent(1, 500)
			return Error.Success
		else
			return Error.NotEnoughCondition
		end
	end,
	[5] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getEntityMCount()>0 then
			return Error.NotEnoughCondition
		end

		local cnt = scene:getProps(SP.lhg_honor_to_next_layer)
		if entity:getHonor() >=cnt then
			if scene:getProps(SP.lhg_layer_reward) ==0 then
				entity:addExp(scene:getProps(SP.lhg_exp),Opcode.Op_liehuodonggonex)
				scene:setProps(SP.lhg_layer_reward, 1)
			end
			entity:useHonor(cnt,Opcode.Op_liehuodonggonex)
			scene:addTimerEvent(1, 500)
			return Error.Success
		else
			return Error.NotEnoughHonor
		end
	end,
}

--
--	mhxg 魔幻星宫	sexg
--
gdNPCExtension[1303] = {
	[1] = function(entity)
		return Error.NotImplemented
		--[[
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.mhxg) then
			return Error.NotEnoughLevel
		end
		if Event.isActive(EID.mhxg) then
			Scene.conveyentitytoscene(entity, MapID.mhxg)
			return Error.Success
		else
			return Error.EventInactive
		end]]
	end
}

--	mhxg 1-11层
gdNPCExtension[313] =
{
	[1] = function(entity)
		local money = 10000
		if entity:getMoney()<money then
			return Error.NotEnoughMoney
		end
		entity:useMoney(money,Opcode.Op_Activity,EID.mhxg)

		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if scene:getStaticID()<280 or scene:getStaticID()>292 then
			return Error.Unknown
		end

		if math.random(1, 100) < 25 then
			Scene.conveyentitytoscene(entity, scene:getStaticID()+1)
		else
			Scene.conveytoRandomPos(entity)
		end
		return Error.Success
	end,
	[2] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		local money = 10 * (scene:getProps(SP.mhxg_layer) or 1)
		if entity:getGold()<money then
			return Error.NotEnoughGold
		end
		entity:useGold(money,Opcode.Op_Activity,EID.mhxg)

		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if scene:getStaticID()<280 or scene:getStaticID()>291 then
			return Error.Unknown
		end

		Scene.conveyentitytoscene(entity, scene:getStaticID()+1)
		return Error.Success
	end,
}

--	mhxg 12层
gdNPCExtension[314] =
{
	[2] = function(entity)	--任意一张星座卡兑换经验
		return Error.NotImplemented
	end,
	[3] = function(entity)	--一套星座卡兑换经验
		return Error.NotImplemented
	end,
}

--
--
gdNPCExtension[178] = {
	onClick = function(entity)
		entity:syncEventData(EID.zmjz)
		_G.syncWorldData(EID.zmjz)
		return Error.Success
	end
}

gdNPCExtension[184] = {
	onClick = function(entity)
		entity:syncEventData(EID.qfs)
--		_G.syncWorldData(EID.qfs)
		return Error.Success
	end
}


gdNPCExtension[1842] = {
	[1] = function(entity)
		local isget = entity:getEventDataZ(EID.qfs)
		if isget ~= 0 then
			return Error.AlreadyGet
		end
		local rank = _G.getPlayerRankInChart(WorldBlob.blob_fireworks_data,entity:getGlobalID())
		if rank ~= 0 then
			return Error.Success
		else
			return Error.NotEnoughScore
		end
	end
}


--
--	九天冰宫	jtbg
--
gdNPCExtension[135] = {
	[1] = function (entity)	--进入九天冰宫
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.jtbg) then
			return Error.NotEnoughLevel
		end
		if entity:getEventDataX(EID.jtbg) >= 3600*4 then
			return Error.TooManyTimes
		end
		if entity:hasItem(40039, 1) then
			if entity:getProps(EP.attr_team_id) == 0 then
				Scene.conveyTeamtoNewInstance(entity,MapID.jtbg)
			else
				local sceneself = entity:getScene()
				local sceneid = 0
				if sceneself then
					sceneid = sceneself:getID()
				end
				entity:forEachTeamMember(function(entity)
						local entityscene = entity:getScene()
						if entityscene and sceneid == entityscene:getID() then
							Scene.conveyTeamtoNewInstance(entity,MapID.jtbg)
						end
					end)
			end
			entity:rmvItem(40039, 1)

			--Scene.conveyTeamtoNewInstance(entity,MapID.jtbg)
			--Scene.enterInstanceTeam(entity,MapID.jtbg)
			--return enterInstanceTeam(entity, MapID.mlsd)
			return Error.Success
		else
			return Error.NotEnoughItem
		end
	end,
	[2] = function(entity)	--进入星落冰庭
		return Error.NotImplemented
	end
}

gdNPCExtension[13511] = { --七大天神神韵兑换
	[1] = function (entity)	--千钧手镯
		return Error.Success
	end,
	[2] = function(entity)	--千钧戒指
		return Error.Success
	end,
	[3] = function(entity)	--烈焰手镯
		return Error.Success
	end,
	[4] = function(entity)	--烈焰戒指
		return Error.Success
	end,
	[5] = function(entity)	--烈焰腰带
		return Error.Success
	end,
	[6] = function(entity)	--
		return Error.Success
	end,
	[7] = function(entity)	--
		return Error.Success
	end,
	[8] = function(entity)	--
		return Error.Success
	end,
	[9] = function(entity)	--
		return Error.Success
	end,
}
gdNPCExtension[13512] = {--六大妖神神韵兑换
	[1] = function (entity)	--
		return Error.Success
	end,
	[2] = function(entity)	--
		return Error.Success
	end,
	[3] = function(entity)	--
		return Error.Success
	end,
	[4] = function(entity)	--
		return Error.Success
	end,
	[5] = function(entity)	--
		return Error.Success
	end,
	[6] = function(entity)	--
		return Error.Success
	end,
	[7] = function(entity)	--
		return Error.Success
	end,
	[8] = function(entity)	--
		return Error.Success
	end,
	[9] = function(entity)	--
		return Error.Success
	end,
}
gdNPCExtension[13513] = {--四大天王神韵兑换
	[1] = function (entity)	--
		return Error.Success
	end,
	[2] = function(entity)	--
		return Error.Success
	end,
	[3] = function(entity)	--
		return Error.Success
	end,
	[4] = function(entity)	--
		return Error.Success
	end,
	[5] = function(entity)	--
		return Error.Success
	end,
	[6] = function(entity)	--
		return Error.Success
	end,
	[7] = function(entity)	--
		return Error.Success
	end,
	[8] = function(entity)	--
		return Error.Success
	end,
	[9] = function(entity)	--
		return Error.Success
	end,
	[10] = function(entity)	--
		return Error.Success
	end,
	[11] = function(entity)	--
		return Error.Success
	end,
	[12] = function(entity)	--
		return Error.Success
	end,
}
gdNPCExtension[13514] = { --冰霜皇廷玉玺兑换
	[1] = function (entity)	--
		return Error.Success
	end,
	[2] = function(entity)	--
		return Error.Success
	end,
	[3] = function(entity)	--
		return Error.Success
	end,
	[4] = function(entity)	--
		return Error.Success
	end,
	[5] = function(entity)	--
		return Error.Success
	end,
	[6] = function(entity)	--
		return Error.Success
	end,
	[7] = function(entity)	--
		return Error.Success
	end,
	[8] = function(entity)	--
		return Error.Success
	end,
	[9] = function(entity)	--
		return Error.Success
	end,
}


gdNPCExtension[301] = {
	[1] = function(entity)	--进入下一层
		local scene = entity:getScene()
		local mcnt = scene:getEntityMCount()
		if mcnt == 0 then
			if entity:hasItem(40039, 2) then
				entity:rmvItem(40039, 2)
				Scene.conveyentitytoNextScene(entity,MapID.jtbg2)
				return Error.Success
			else
				return Error.NotEnoughItem
			end
		else
			return Error.Scene_Not_Finish
		end
	end,
	[2] = function (entity)	--返回进入场景
		Scene.conveyentitytoNPC(entity,190)
		return Error.Success
	end,

}

gdNPCExtension[302] = {
	[1] = function(entity)	--进入下一层
		local scene = entity:getScene()
		local mcnt = scene:getEntityMCount()
		if mcnt == 0 then
			if entity:hasItem(40039, 3) then
				entity:rmvItem(40039, 3)
				Scene.conveyentitytoNextScene(entity,MapID.jtbg3)
				return Error.Success
			else
				return Error.NotEnoughItem
			end
		else
			return Error.Scene_Not_Finish
		end
	end,
	[2] = function (entity)	--返回进入场景
		Scene.conveyentitytoNPC(entity,190)
		return Error.Success
	end,

}


gdNPCExtension[303] = {
	[1] = function (entity)	--返回进入场景
		Scene.conveyentitytoNPC(entity,190)
		return Error.Success
	end,
}


--
--	狩猎活动	slhd	降妖除魔	xycm
--
--
gdNPCExtension[1314] = {
	[1] = function (entity) --进入狩猎场
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.slhd) then
			return Error.NotEnoughLevel
		end
		if not Event.isActive(EID.slhd) then
			return Error.EventInactive
		end
		--local elapse = os.time() - Event.getEventDataX(EID.slhd)
		--if elapse > 60 then
		--	return Error.EntranceClosed
		--end
		Scene.conveyentitytoscene( entity, MapID.slc)
		return Error.Success
	end,
	[2] = function(entity)	--领取奖励
		if Event.isActive(EID.slhd) then
			return Error.EventIsactive
		end
		local score, win = entity:getEventData(EID.slhd)
		if win==1 then	--第一名奖励
			entity:addBindItem(30223)	--冠军猎手礼包
			entity:addHonor(40000,Opcode.Op_slhd,win)	  --荣誉
		elseif win==2 then	--第二名奖励
			entity:addBindItem(30224)	--精英猎手礼包
			entity:addHonor(30000,Opcode.Op_slhd,win)	  --荣誉
		elseif win==3 then	--第三名奖励
			entity:addBindItem(30225)	--猎手礼包
			entity:addHonor(24500,Opcode.Op_slhd,win)	  --荣誉
		elseif win==4 then	--阳光普照奖
			entity:addHonor(20000,Opcode.Op_slhd,win)	  --荣誉
		else
			return Error.NotEnoughScore
		end
		entity:setEventData(EID.slhd, 0, 0, 0)
		entity:saveEventData(EID.slhd)
		return Error.Success
	end,
}

gdNPCExtension[307] = {
	[1] = function (entity)	--进入下一层
		local scene = entity:getScene()
		if not scene then
			return Error.InvalidScene
		end
		local layer = scene:getProps(SP.slhd_layer)
		local score = {10, 10, 15}
		score = score[layer] or 10
		if entity:getProps(EP.attr_slhd_score)>=score then
			Scene.conveyentitytoscene( entity, MapID.slc+layer)
			return Error.Success
		else
			return Error.NotEnoughScore
		end
	end,
}

--
--	马拉松		mls sm
--
-- 宠物项圈 40053
local function mls_reward(entity)
	local rank,reward,_ = entity:getEventData(EID.mls)
	if rank == 0 then
		return Error.NotEnoughScore
	end
	if reward == 0 then
		if rank == 1 then
			entity:addItem(41000,50)
			entity:addItem(4,88888)
		elseif rank == 2 then
			entity:addItem(41000,40)
			entity:addItem(4,58888)
		elseif rank == 3 then
			entity:addItem(41000,30)
			entity:addItem(4,48888)
		elseif rank >=4 and rank <= 20 then
			entity:addItem(41000,15)
		end
		entity:setEventDataY(EID.mls,1)
		entity:saveEventData(EID.mls)
		return Error.Success
	else
		return Error.AlreadyUsed
	end
end

gdNPCExtension[132] = {
	[1] = function(entity)
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.mls) then
			return Error.NotEnoughLevel
		end
		if Event.isActive(EID.mls) then
			Scene.conveyentitytoscene(entity, MapID.qssmc)
			return Error.Success
		else
			return Error.EventInactive
		end
	end,
}

gdNPCExtension[311] = {
	[1] = function(entity)
		return mls_reward(entity)
	end,
	[2] = function(entity)
		Scene.conveyentitytoNPC(entity,151)
		return Error.Success
	end,
}

--转生NPC
gdNPCExtension[133] = {
--	[1] = function (entity)
--		entity:reborn()
--		return Error.Success
--	end,
}

-- gdNPCExtension[1332] = {
	-- [1] = function (entity)
		-- local reborn = entity:getProps(EP.attr_reborn)
		-- local nextReborn = reborn + 1
		-- local condition = gdEvolutionCondition[nextReborn]
		-- if condition and condition.needrobbery == 1 then
			-- local robberySuccess = entity:getEventDataX(EID.robbery)
			-- if robberySuccess ~= 1 then
				-- return Error.NotEnoughCondition
			-- end
		----	转身成功后清除渡劫标志，确保下次需要渡劫时必须重新完成
			-- entity:setEventDataX(EID.robbery, 0)
		-- end
		-- entity:reborn()
		-- return Error.Success
	-- end,
-- }
gdNPCExtension[1332] = {
    [1] = function(entity)
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
        local result = entity:reborn()
        
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
        end
        -- 注意：转身失败的情况不在这里处理
        -- 如果转身失败(isSuccess为false)，代码不会进入上面的if块
        -- 因此天劫印记不会消失
        
        -- 返回结果
        if isSuccess then
            return Error.Success
        else
            return result or Error.NotEnoughCondition
        end
    end
}


local function springbrother(entity)
	local cbt = entity:getCombatSys()
	if cbt then
		if cbt:getMaxHP() == cbt:getHP()
			and cbt:getMaxMP() == cbt:getMP() then
			return Error.PlayerStateGood
		end
		local money=entity:getProps(EntityProp.attr_reborn)*40000+entity:getLevel()*500
		if entity:getMoney()<money then
			return Error.NotEnoughMoney
		end
		cbt:updateHP(cbt:getMaxHP(),0)
		cbt:updateMP(cbt:getMaxMP())
		entity:useMoney(money,Opcode.springbrother)
	end
	return Error.Success
end

gdNPCExtension[101] = {
	[2] = springbrother,
}

gdNPCExtension[114] = {
	[2] = springbrother,
}

gdNPCExtension[162] = {
	[2] = springbrother,
}

gdNPCExtension[215] = {
	[2] = springbrother,
}
--
--	攻城战	gc:w
--
--

-- 后宫守卫	hgsw
gdNPCExtension[197] = {
	[2] = function (entity)
		return Scene.conveyentitytoscene(entity, MapID.scmd)
	end,
}
-- 沙城密道	scmd
gdNPCExtension[152] = {
	[1] = function (entity)
		local ed = gdEventData[EID.gcz]
		if  Event.isActive(EID.gcz) then
			local gid = entity:getProps(EntityProp.attr_guild_id)
			local defgid = _G.getWorldDataX(WP.city_master_guild)
			if gid == defgid then
				return Error.Gcz_Not_Allow_Defend_in
			else
				local level = entity:getLevel()
				if level < 40 then
					return Error.NotEnoughLevel
				else
					return Scene.conveyentitytoscene(entity, MapID.gczshg)
				end
			end
		else
			return Error.Gcz_Not_Begin
		end
	end,
}
-- 攻城先锋	gcxf
gdNPCExtension[201] = {
	[1] = function(entity)  -- 领取斩敌数奖励
		local ed = gdEventData[EID.gcz]
		if not Event.isActive(EID.gcz) then
			local state = _G.getWorldDataZ(WorldProp.prop_gcz_kill_most)
			local killerid = _G.getWorldDataX(WorldProp.prop_gcz_kill_most)
			if (entity:getGlobalID() ~= killerid) then
				return Error.Gcz_Kill_Most_Not_You
			else
				if state == 0 then
					local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
					if (embag < 1) then
						return Error.Item_BagisFull
					else
--						entity:addBindItem(50042)
						_G.setWorldDataZ(WorldProp.prop_gcz_kill_most,1)
						_G.saveWorldData(WorldProp.prop_gcz_kill_most)
						return Error.Success
					end
				else
					return Error.AlreadyGet
				end
			end
		end
		return Error.EventNotOver
	end,
	[2] = function(entity) 	-- 开启战神之力
		if true then
			return Error.NotImplemented
		end
		if not Event.isActive(EID.gcz) then
			return Error.EventInactive
		end

		local guild = entity:getGuild()
		if guild then
			local isapp = guild:getProps(GuildProp.guild_apply_gcz)
			if isapp ~= 0 then

				local post = entity:getProps(EntityProp.attr_guild_post)
				if post == GuildProp.post_master or post == GuildProp.post_second_master then
					local gczbuffopen = guild:getProps(GuildProp.guild_open_gcz_buff)
					if gczbuffopen == 0 then
						local rtv = entity:useGold(200,Opcode.gcz_zszl_open)
						if rtv ~= Error.Success then
							return rtv
						end

						guild:forEach(function(entity)
							local gd = gdGenes[6]
							entity:addGeneEx(gd.id, gd.groupid,gd.class,60 * 10,gd.dead,gd.data.x,gd.data.y,MapID.gczshg)
						end)
						return Error.Success
					else
						return Error.guildGczBuffHasOn
					end
				else
					return Error.err_guild_authority
				end
			else
				return Error.guildGczNotApply
			end
		else
			return Error.NotInGuild
		end
	end,
}


--
--	武易战场		wyzc		群雄逐鹿	qxzl
--	活动场景内NPC为药店老板 * 2
--
gdNPCExtension[1312] = {
	[1] = function (entity) --进入武易战场
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.wyzc) then
			return Error.NotEnoughLevel
		end
		if Event.isActive(EID.wyzc) then
			Scene.conveyentitytoscene(entity, MapID.wyzc)
			return Error.Success
		else
			return Error.EventInactive
		end
	end,
	[2] = function(entity)	--领取奖励
		local score, win = entity:getEventData(EID.wyzc)
		if win==1 then
			if score>2000 then
				entity:addHonor(50000,Opcode.Op_wyzc,win)	  --荣誉
				entity:addBindItem(40041, 5) --清洗砂
				entity:addBindItem(40016, 10) --足迹精华
			elseif score>200 then
				entity:addBindItem(40041, 3) --清洗砂
				entity:addBindItem(40016, 6) --足迹精华
				entity:addHonor(20000,Opcode.Op_wyzc,win)	  --荣誉
			else
				entity:addHonor(5000,Opcode.Op_wyzc,win)	  --荣誉
				entity:addBindItem(40041, 1) --清洗砂
				entity:addBindItem(40016, 2) --足迹精华
			end
		elseif win==2 then
			if score>2000 then
				entity:addHonor(30000,Opcode.Op_wyzc,win)	  --荣誉
				entity:addBindItem(40041, 3) --清洗砂
				entity:addBindItem(40016, 7) --足迹精华
			elseif score>200 then
				entity:addHonor(5000,Opcode.Op_wyzc,win)	  --荣誉
				entity:addBindItem(40041, 1) --清洗砂
				entity:addBindItem(40016, 3) --足迹精华
			else
				entity:addHonor(3000,Opcode.Op_wyzc,win)	  --荣誉
			end
		else
			return Error.EventInactive
		end
		entity:setEventData(EID.wyzc, 0, 0, 0)
		entity:saveEventData(EID.wyzc)
		return Error.Success
	end,
}


--
--	火龙熔岩	hlry
--
--
gdNPCExtension[1301] = {
	[1] = function (entity) --进入火龙熔岩
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.hlry) then
			return Error.NotEnoughLevel
		end
		if not Event.isActive(EID.hlry) then
			return Error.EventInactive
		end
		local elapse = os.time() - Event.getEventDataX(EID.hlry)
		if elapse > 60 then
			return Error.EntranceClosed
		end
		Scene.conveyentitytoscene(entity, MapID.hlry)
		return Error.Success
	end,
	[2] = function(entity)	--准备兑换
		return Error.Success
	end,
	--
}


--
--	战神争霸	zszb
--
--
gdNPCExtension[1313] = {
	[1] = function (entity) --进入战神争霸
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.zszb) then
			return Error.NotEnoughLevel
		end

		if not Event.isActive(EID.zszb) then
			return Error.EventInactive
		end
		--十分钟后禁止玩家进入
		local elapse = os.time() - Event.getEventDataX(EID.zszb)
		if elapse > 600 then
			return Error.EntranceClosed
		end

		Scene.conveyentitytoscene(entity, MapID.zszb)
		return Error.Success
	end,
	[2] = function(entity)	--领取奖励
		local zszbwinner = _G.getWorldDataX(WP.zszb)
		local zszbisget  = _G.getWorldDataY(WP.zszb)
		if entity:getGlobalID() == zszbwinner then
			if zszbisget == 0 then
				_G.setWorldDataY(WP.zszb,1)
				_G.saveWorldData(WP.zszb)
				entity:addGold(100,Opcode.Op_zszb)
				--entity:addBindItem(70130,1)
				_G.syncFloatMessage(entity:getName().."成为了新一届霸主")
				return Error.Success
			else
				return Error.AlreadyGet
			end
		else
			return Error.NotEnoughCondition
		end
	end,
}


gdNPCExtension[312] = { --场景内NPC
	[2] = function (entity)	--申请成为霸王, 领取奖励, 并返回进入场景
		local zszbwinner = _G.getWorldDataX(WP.zszb)
		local zszbisget  = _G.getWorldDataY(WP.zszb)
		if entity:getGlobalID() == zszbwinner then
			if zszbisget == 0 then
				_G.setWorldDataY(WP.zszb,1)
				_G.saveWorldData(WP.zszb)
				entity:addGold(100,Opcode.Op_zszb)
			--	entity:addBindItem(70130,1)
				Scene.conveyBack(entity)
				_G.syncFloatMessage(entity:getName().."成为了新一届霸主")
				return Error.Success
			else
				return Error.AlreadyGet
			end
		else
			return Error.NotEnoughCondition
		end
	end,
}


--
--	采花大盗	chdd
--
gdNPCExtension[151] = {
	[1] = function(entity)--免费领取种子
		local used = entity:getEventDataX(EID.chdd)
		if used<3 then
            --添加物品
            local embag  = entity:getBagEmptyCnt()
            if (embag < 1) then
                return Error.Item_BagisFull
            end
			entity:setEventDataX(EID.chdd, used+1)
			entity:saveEventData(EID.chdd)
            math.randomseed(os.time())
            local n = math.random(100)
            if n then
                if n <=33 then
                    entity:addBindItem(39029, 1,Opcode.op_plant)
                elseif n > 33 and n <= 53 then
                    entity:addBindItem(30047, 1,Opcode.op_plant)
                elseif n > 53 and n <= 60 then
                    entity:addBindItem(40011, 1,Opcode.op_plant)
                elseif n > 60 and n <= 70 then
                    entity:addBindItem(30307, 1,Opcode.op_plant)
                elseif n > 70 and n <= 100 then
                    entity:addBindItem(40053, 1,Opcode.op_plant)
                end
            end

			return Error.Success
		else
			return Error.TooManyTimes
		end
	end,
	[2] = function(entity)--3元宝购买高级种子
		if entity:getGold()>=3 then
			entity:useGold(3,Opcode.Op_chdd_seed)
			entity:addItem(30231, 1)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[3] = function(entity)--购买催泪弹
		if entity:getMoney()>=10000 then
			entity:useMoney(10000,Opcode.Op_chdd_bomb)
			entity:addItem(30220, 1)
			return Error.Success
		else
			return Error.NotEnoughMoney
		end
	end,
	[4] = function(entity)--购买催泪弹*10
		if entity:getMoney()>=100000 then
			entity:useMoney(100000,Opcode.Op_chdd_bomb)
			entity:addItem(30220, 10)
			return Error.Success
		else
			return Error.NotEnoughMoney
		end
	end,
	[5] = function(entity)--购买强力催泪
		if entity:getGold()>=3 then
			entity:useGold(3,Opcode.Op_chdd_bomb)
			entity:addItem(30221, 1)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[6] = function(entity)--购买强力催泪*10
		if entity:getGold()>=30 then
			entity:useGold(30,Opcode.Op_chdd_bomb)
			entity:addItem(30221, 10)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
}

--
--	勇士角斗场	ysjdc
--
gdNPCExtension[1311] = {

	[1] = function(entity)	-- 进入副本
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.ysjdc) then
			return Error.NotEnoughLevel
		end
		if Event.isActive(EID.ysjdc) then
			Scene.conveyentitytoscene(entity, MapID.ysjdc)
			return Error.Success
		else
			return Error.EventInactive
		end
	end,
	[3] = function(entity) --领取奖励
		if Event.isActive(EID.ysjdc) then
			return Error.EventIsactive
		end
		local lvl = entity:getLevel()
		local score, win, exp = entity:getEventData(EID.ysjdc)
		if win>=1 and win<=10 then	--第一名奖励
			entity:addHonor(7370,Opcode.event_ysjdc,win)	  --荣誉
			entity:addMoney(171500,Opcode.event_ysjdc,win)
			entity:addExp(exp, Opcode.event_ysjdc,win)
			DailyAct.AddTargetCnt(entity,EID.mrmrjdc)
		elseif win==11 then
			entity:addHonor(7370,Opcode.event_ysjdc,win)	  --荣誉
			entity:addMoney(171500,Opcode.event_ysjdc,win)
			DailyAct.AddTargetCnt(entity,EID.mrmrjdc)
		else
			return Error.AlreadyUsed
		end
		entity:setEventData(EID.ysjdc, 0, 0, 0)
		entity:saveEventData(EID.ysjdc)

		return Error.Success
	end,
}

-----------------------------------------------
--	副本入口类NPC    ----------------------
-----------------------------------------------

local function getMapEventID(mid)
	local sd = gdMaps[mid]
	if sd then
		return sd.eventid
	else
		return 0
	end
end

--
--	进入单人副本
local function enterInstanceSelf(entity, mapid)
	local evtid = getMapEventID(mapid)
	if evtid==0 then
		return Error.InvalidStaticData
	end
	local ed = gdEventData[evtid]
	local maxentertimes = 1
	if ed then
		maxentertimes = ed.datax
	end

	if isProtectGirl(entity) then
		return Error.Meinvhusong_is_begin
	end

	local entertimes, boughtentertimes = entity:getEventData(evtid)
	if entertimes>=maxentertimes + boughtentertimes  then
		return Error.TooManyTimes
	end

	local rtv = Scene.conveyentitytoNewInstance(entity,mapid)
	if rtv == Error.Success then
		entity:onEvent(EventProp.GT_Quest,EventProp.EID_GoToInstance,mapid)
		entity:addEventDataX(evtid, 1)
		entity:saveEventData(evtid)
		DailyAct.AddTargetCnt(entity,EID.mrmrfb)
	end
	return rtv
end


--
--	进入组队副本
local function enterInstanceTeam(entity, mapid)
	-- change it entity to a team maybe useful
	--entity:addTeamEntity()
	local evtid = getMapEventID(mapid)
	if evtid==0 then
		return Error.InvalidStaticData
	end
	local ed = gdEventData[evtid]
	local maxentertimes = 1
	local name
	if ed then
		maxentertimes = ed.datax
		name = ed.name
	else
		log.error("failed to get event data, eid: ", evtid)
		name = "未知副本"
	end

	if isProtectGirl(entity) then
		return Error.Meinvhusong_is_begin
	end

	local entertimes, boughtentertimes = entity:getEventData(evtid)
	if entertimes>=maxentertimes + boughtentertimes  then
		return Error.TooManyTimes
	end

	local rtv = Scene.conveyTeamtoNewInstance(entity,mapid)
	--log.info("rtv = "..rtv)
	if rtv == Error.Success then
		entity:onEvent(EventProp.GT_Quest,EventProp.EID_GoToInstance,mapid)
		entity:syncTeamChatMsg("队伍中的 "..entity:getName().." 进入了副本:"..name)
		entity:addEventDataX(evtid, 1)
		entity:saveEventData(evtid)
		DailyAct.AddTargetCnt(entity,EID.mrmrfb)
	end
	return rtv
end


--
--	退出副本
local function exitInstance(entity)
	Scene.conveyentitytoscene( entity, 2)
	return Error.Success
end

--
--	增加进入次数
local function addInstanceEnterTimes(entity, mapid, passportcnt)
	local evtid = getMapEventID(mapid)
	if evtid==0 then
		return Error.InvalidStaticData
	end

	local boughtentertimes = entity:getEventDataY(evtid)
	if boughtentertimes>=1 then
		return Error.AlreadyUsed
	end

	if entity:hasItem(40051, passportcnt) then
		entity:rmvItem(40051, passportcnt)
	else
		return Error.NotEnoughInstancePassport
	end

	entity:addEventDataY(evtid, 1)
	return Error.Success
end
--用元宝增加进入次数
local function addInstanceEnterTimesByGold(entity, mapid, Goldcnt)
	local evtid = getMapEventID(mapid)
	if evtid==0 then
		return Error.InvalidStaticData
	end

	local boughtentertimes = entity:getEventDataY(evtid)
	if boughtentertimes >=1 then
		return Error.AlreadyUsed
	end
	local gcnt = entity:getGold()
	if (gcnt >= Goldcnt) then
		entity:useGold(Goldcnt,Opcode.InstanceCntAdd,mapid)
	else
		return Error.NotEnoughGold
	end

	entity:addEventDataY(evtid, 1)
	return Error.Success
end
--
--	召集队伍
local function rescuitTeam(entity,mapid)
	local lasttime = entity:getProps(EP.attr_teamcall_cd)
	local nowtime = os.time()
	if lasttime == 0 or nowtime - lasttime>30 then
		entity:setProps(EP.attr_teamcall_cd,nowtime)
		local msg = "玩家[player:"..entity:getGlobalID()..","..entity:getName().."]邀请您一同参加[scene:"..mapid.."]副本，是否同意邀请？[team:"..entity:getGlobalID().."]"
		_G.syncsysChatMsg(msg)

		if entity:getProps(EntityProp.attr_team_id) == 0 then
			entity:createTeam()
		end

		return Error.Success
	else
		return Error.StillInCD
	end


	return Error.Success
end

--
--	集合队伍
local function summonTeam(entity)
	--entity:summonMyTeam()
	--发送funcid给客户端提示队伍集合
	return gdFuncExtension[FP.team_call].ClientRequest(entity)
	--return Error.Success
end

--
--  退出场景
local function backScene(entity)
	return  Scene.conveyBack(entity)
end

--
--	妖月峡谷	yyxg
--
gdNPCExtension[1261] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.yyxg) then
			return Error.NotEnoughLevel
		end
		return enterInstanceSelf(entity, MapID.yyxg)
	end,
	--[2] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.yyxg, 1)
	--end,
}

-- gdNPCExtension[12611] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.yyxg, 1)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.yyxg, 10)
	-- end,
-- }
--
--	万年古墓	wngm
--
gdNPCExtension[1262] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.wngm) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.wngm)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.wngm)
	end,
	[3] = summonTeam,
	--[4] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.wngm, 2)
	--end,
}

-- gdNPCExtension[12621] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.wngm, 2)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.wngm, 20)
	-- end,
-- }
--
--	赤月峡谷 赤月魔域	cyxg	cymy
--
gdNPCExtension[1263] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.cyxg) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.cyxg)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.cyxg)
	end,
	[3] = summonTeam,
	--[4] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.cyxg, 2)
	--end,
}

-- gdNPCExtension[12631] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.cyxg, 2)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.cyxg, 20)
	-- end,
-- }
--
--	宝矿洞窟	bkdk
--
gdNPCExtension[1264] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.bkdk) then
			return Error.NotEnoughLevel
		end
		return enterInstanceSelf(entity, MapID.bkdk)
	end,
	--[2] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.bkdk, 2)
	--end,
}

-- gdNPCExtension[12641] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.bkdk, 2)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.bkdk, 20)
	-- end,
-- }

gdNPCExtension[323] =
{
	[2] = function(entity)
		Scene.conveyentitytoNPC(entity,132)
		return Error.Success
	end,
}


--
--	天地宝窟	tdbk
--
gdNPCExtension[1265] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.tdbk) then
			return Error.NotEnoughLevel
		end
		return enterInstanceSelf(entity, MapID.tdbk)
	end,
	--[2] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.tdbk, 2)
	--end,
}

-- gdNPCExtension[12651] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.tdbk, 2)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.tdbk, 20)
	-- end,
-- }

gdNPCExtension[324] =
{
	[2] = function(entity)
		Scene.conveyentitytoNPC(entity,130)
		return Error.Success
	end,
}


--
--	水域龙都	syld		hjhd
--
gdNPCExtension[1273] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.syld) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.syld)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.syld)
	end,
	[3] = summonTeam,
}

-- gdNPCExtension[12731] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.syld, 3)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.syld, 30)
	-- end,
-- }

gdNPCExtension[998] =
{
	[2] = function(entity)
		Scene.conveyentitytoNPC(entity,135)
		return Error.Success
	end,
}

gdNPCExtension[325] =
{
	[1] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		--龙王只能召唤一次
		if scene:getProps(SP.syld_longwang_summon)>0 then
			return Error.AlreadyUsed
		end

		--5个青龙珠召唤龙王
		if not entity:hasItem(40124, 5) then
			return Error.NotEnoughItem
		end

		scene:setProps(SP.syld_longwang_summon, 1)
		local m = scene:addM(1024, 108, 23)
		if m then
			scene:syncFloatMessage("小心! 龙王被召唤出来了!!!")
			entity:rmvItem(40124, 5)
		else
			log.error("failed to summon longwang in syld")
		end
		return Error.Success
	end,
	[2] = exitInstance,
}

--
--	神灯传奇	sdcq
--
gdNPCExtension[1272] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.sdcq) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.sdcq)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.sdcq)
	end,
	[3] = summonTeam,
	[4] = function(entity)
		return addInstanceEnterTimes(entity, MapID.sdcq, 3)
	end,
}

-- gdNPCExtension[12721] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.sdcq, 3)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.sdcq, 30)
	-- end,
-- }


--
--	魔龙神殿	mlsd
--
gdNPCExtension[1271] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.mlsd) then
			return Error.NotEnoughLevel
		end

		return enterInstanceTeam(entity, MapID.mlsd)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.mlsd)
	end,
	[3] = summonTeam,
	--[4] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.mlsd, 3)
	--end,
}

-- gdNPCExtension[12711] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.mlsd, 3)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.mlsd, 30)
	-- end,
-- }

gdNPCExtension[327] =
{
	[3] = function(entity)
		Scene.conveyentitytoNPC(entity,131)
		return Error.Success
	end,
}

gdNPCExtension[3271] =
{
	[1] = function(entity)
		if entity:getMoney()>1000000 then
			local scene = entity:getScene()
			if scene then
				local powcnt = scene:getProps(SceneProp.mlsd_lowpowcnt)
				--log.info("pow low cnt "..powcnt)
				if powcnt < 2 then
					entity:useMoney(1000000,Opcode.Op_mlsd,1066)
					scene:addM(1066, 57, 60)
					scene:addProps(SceneProp.mlsd_lowpowcnt)
					return Error.Success
				end
			end
			return Error.ThingsOverMax
		else
			return Error.NotEnoughMoney
		end
	end,
	[2] = function(entity)
		if entity:getGold()>10 then
			local scene = entity:getScene()
			if scene then
				local powcnt = scene:getProps(SceneProp.mlsd_highpowcnt)
				--log.info("pow high cnt "..powcnt)
				if powcnt < 20 then
					entity:useGold(10,Opcode.Op_mlsd,1067)
					scene:addM(1067, 57, 60)
					scene:addProps(SceneProp.mlsd_highpowcnt)
					return Error.Success
				end
			end
			return Error.ThingsOverMax
		else
			return Error.NotEnoughGold
		end
	end,
}

--
--	魔剑封印	mjfy
--
gdNPCExtension[1274] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.mjfy) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.mjfy)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.mjfy)
	end,
	[3] = summonTeam,
	--[4] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.mjfy, 4)
	--end,
}

-- gdNPCExtension[12741] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.mjfy, 4)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.mjfy, 40)
	-- end,
-- }

gdNPCExtension[808] =
{
	[2] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getProps(SP.mjfy_summon_boss1)>0 then
			return Error.AlreadyUsed
		end
		if not entity:hasItem(40130, 10) then
			return Error.NotEnoughItem
		end
		scene:setProps(SP.mjfy_summon_boss1, 1)
		entity:rmvItem(40130, 10)
		local btbl = {1040, 1041, 1042}
		local bossid = btbl[math.random(1,3)]
		scene:addM(bossid, 47, 52)
		scene:setProps(SP.mjfy_now_bossid,bossid)
		return Error.Success
	end,
	[3] = exitInstance,
}
gdNPCExtension[809] =
{
	[2] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getProps(SP.mjfy_summon_boss1) == 0 then
			return Error.AlreadyUsed
		end
		if scene:getProps(SP.mjfy_now_bossid) >0 then
			return Error.AlreadyUsed
		end
		if scene:getProps(SP.mjfy_summon_boss2)>0 then
			return Error.AlreadyUsed
		end

		if not entity:hasItem(40131, 10) then
			return Error.NotEnoughItem
		end
		scene:setProps(SP.mjfy_summon_boss2, 1)
		entity:rmvItem(40131, 10)
		scene:addM(1043, 73, 24)
		scene:setProps(SP.mjfy_now_bossid,1043)
		return Error.Success
	end,
	[3] = exitInstance,
}
--
--	地狱结界	dyjj
--
gdNPCExtension[1275] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.dyjj) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.dyjj)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.dyjj)
	end,
	[3] = summonTeam,
	[4] = function(entity)
		return addInstanceEnterTimes(entity, MapID.dyjj, 5)
	end,
}

-- gdNPCExtension[12751] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.dyjj, 5)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.dyjj, 50)
	-- end,
-- }

gdNPCExtension[810] =
{
	[3] = function(entity)
		Scene.conveyentitytoNPC(entity,137)
		return Error.Success
	end,
}

gdNPCExtension[81001] =
{
	[1] = function(entity)
		if entity:getMoney()>1000000 then
			entity:useMoney(1000000,Opcode.Op_dyjj,1066)
			local scene = entity:getScene()
			if scene then
				scene:addM(1066, 50, 59)
			end
			return Error.Success
		else
			return Error.NotEnoughMoney
		end
	end,
	[2] = function(entity)
		if entity:getGold()>10 then
			entity:useGold(10,Opcode.Op_dyjj,1067)
			local scene = entity:getScene()
			if scene then
				scene:addM(1067, 50, 59)
			end
			return Error.Success
		else
			return Error.NotEnoughMoney
		end
	end,
}




--
--	降魔副本	xmfb
--	水寨	sz
--
gdNPCExtension[1292] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.sz) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.sz)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.sz)
	end,
	[3] = summonTeam,
}

-- gdNPCExtension[12921] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.mjfy, 4)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.mjfy, 40)
	-- end,
-- }

local function xmfb_summon(entity)	--免费召唤段
	local scene = entity:getScene()
	if not scene then
		return Error.Unknown
	end

	if scene:getProps(SP.xmfb_already_summon)>0 then
		return Error.AlreadyUsed
	end
	scene:setProps(SP.xmfb_already_summon, 1)

	local m = scene:addM(1087, entity:getPositionX(), entity:getPositionY())
	if m then
		--entity:addRmvCleanEntity(m)
	end
	return Error.Success
end

local function xmfb_summon_liemo(entity)	--免费召唤里猎魔人
	local scene = entity:getScene()
	if not scene then
		return Error.Unknown
	end
	if scene:getProps(SP.xmfb_already_summon_liemo)>=8 then
		return Error.TooManyTimes
	end

	if entity:getMoney()<80000 then
		return Error.NotEnoughMoney
	end

	scene:addProps(SP.xmfb_already_summon_liemo)
	entity:useMoney(80000,Opcode.Op_xmfb_call)
	local m = scene:addM(1088, entity:getPositionX(), entity:getPositionY())
	if m then
		--entity:addRmvCleanEntity(m)
	end
	return Error.Success
end


gdNPCExtension[329] =
{
	[1] = xmfb_summon,
	--[[
	[2] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if scene:getProps(SP.xmfb_already_potion)>0 then
			return Error.AlreadyGet
		end
		scene:setProps(SP.xmfb_already_potion, 1)

		entity:addBindItem(39053, 1)
		return Error.Success
	end,
	--]]
	[2] = xmfb_summon_liemo,
	[4] = function(entity)	--去高家店	gjd
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if scene:getProps(SP.xmfb_already_killed_boss)==0 then
			return Error.NotEnoughCondition
		end
		local rtv = Scene.conveyTeamtoNewInstance(entity,MapID.gjd)

		if rtv == Error.Success then
			local newscene = entity:getScene()
			if not newscene then
				return Error.Unknown
			end
			newscene:setProps(SP.xmfb_already_summon_liemo, scene:getProps(SP.xmfb_already_summon_liemo))
			return Error.Success
		end
		return rtv
	end,
}

gdNPCExtension[330] =
{
	[1] = xmfb_summon,
	--[[
	[2] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if scene:getProps(SP.xmfb_already_potion)>0 then
			return Error.AlreadyUsed
		end
		scene:setProps(SP.xmfb_already_potion, 1)

		entity:addBindItem(39051, 1)
		return Error.Success
	end,
	--]]
	[2] = xmfb_summon_liemo,
	[4] = function(entity)	--去五指山下	wzsx
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if scene:getProps(SP.xmfb_already_killed_boss)==0 then
			return Error.NotEnoughCondition
		end
		local rtv = Scene.conveyTeamtoNewInstance(entity,MapID.wzsx)

		if rtv == Error.Success then
			local newscene = entity:getScene()
			if not newscene then
				return Error.Unknown
			end
			newscene:setProps(SP.xmfb_already_summon_liemo, scene:getProps(SP.xmfb_already_summon_liemo))
			return Error.Success
		end
		return rtv
	end,
}

gdNPCExtension[331] =
{
	[1] = xmfb_summon,
	--[[
	[2] = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if scene:getProps(SP.xmfb_already_potion)>0 then
			return Error.AlreadyUsed
		end
		scene:setProps(SP.xmfb_already_potion, 1)

		entity:addBindItem(39052, 1)
		return Error.Success
	end,
	--]]
	[2] = xmfb_summon_liemo,
	[4] = function(entity)	--使用888召唤如来
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end

		if entity:getGold()<888 then
			return Error.NotEnoughGold
		end

		if scene:getProps(SP.xmfb_already_summon_liemohead)>=1 then
			return Error.TooManyTimes
		end

		scene:addProps(SP.xmfb_already_summon_liemohead)
		entity:useGold(888,Opcode.Op_xmfb_call)
		local m = scene:addM(1089, entity:getPositionX(), entity:getPositionY())
		if m then
			--entity:addRmvCleanEntity(m)
		end
		return Error.Success
	end,
}

gdNPCExtension[3291] =
{
	[1] = function(entity)	--购买避水丹
		if entity:getGold()<10 then
			return Error.NotEnoughGold
		end

		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getProps(SP.xmfb_already_potion)>0 then
			return Error.AlreadyUsed
		end
		scene:setProps(SP.xmfb_already_potion, 1)
		entity:useGold(10,Opcode.Op_xmfb_buy,39050)
		entity:addBindItem(39050, 1)
		return Error.Success
	end,
}


gdNPCExtension[3301] =
{
	[1] = function(entity)	--购买攻击丹
		if entity:getGold()<10 then
			return Error.NotEnoughGold
		end
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getProps(SP.xmfb_already_potion)>0 then
			return Error.AlreadyUsed
		end
		scene:setProps(SP.xmfb_already_potion, 1)
		entity:useGold(10,Opcode.Op_xmfb_buy,39051)
		entity:addBindItem(39051, 1)
		return Error.Success
	end,
}

gdNPCExtension[3311] =
{
	[1] = function(entity)	--购买防御丹
		if entity:getGold()<10 then
			return Error.NotEnoughGold
		end
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getProps(SP.xmfb_already_potion)>0 then
			return Error.AlreadyUsed
		end
		scene:setProps(SP.xmfb_already_potion, 1)
		entity:useGold(10,Opcode.Op_xmfb_buy,39052)
		entity:addBindItem(39052, 1)
		return Error.Success
	end,
}
--
--
--	行会争夺战	hhzdz
gdNPCExtension[136] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.hhzdz) then
			return Error.NotEnoughLevel
		end

		if not Event.isActive(EID.hhzdz) then
			return Error.EventInactive
		end

		--
		--	行会争夺战已经提前结束, 事件本身还是active
		local scene = gdScnMgr:getSceneBySid(MapID.hhzdz)
		if not scene then
			return Error.EventInactive
		end

		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end

		if scene:getProps(SP.hhzdz_finish)>0 and mgid~=scene:getProps(SP.hhzdz_defend_guild) then
			return Error.EntranceClosed
		end

		Scene.conveyentitytoscene(entity, MapID.hhzdz)
		return Error.Success
	end,
}

--
--	保卫萝卜	bwlb
--
gdNPCExtension[1291] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.bwlb) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.bwlb)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.bwlb)
	end,
	[3] = summonTeam,
	--[4] = function(entity)
	--	return addInstanceEnterTimes(entity, MapID.bwlb, 10)
	--end,
}

-- gdNPCExtension[12911] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.bwlb, 10)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.bwlb, 100)
	-- end,
-- }
--
--	圣殿魔域	sdmy
--
gdNPCExtension[1293] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.sdmy) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.sdmy)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.sdmy)
	end,
	[3] = summonTeam,
}

--
--	冥魂神殿	mhsd
--
gdNPCExtension[1294] =
{

	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.mhsd) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.mhsd)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.mhsd)
	end,
	[3] = summonTeam,
	[4] = function(e)-----------------扫荡
	-- 条件检查: 是否达到副本所需的等级要求
	 if not meetRequiredLvlEID(e, EID.mhsd) then return Error.NotEnoughLevel end
	--条件检查战力是否达到
	if (e:getProps(117) or 0) < 180000 then return Error.NotEnoughPower end    
    -- 条件检查: 当天已参与次数不能超过1次
    if e:getEventDataX(EID.mhsd) >= 1 then return Error.TooManyTimes end
    -- 条件检查: 背包空位需要至少5个
    if e:getBagEmptyCnt() < 5 then return Error.Item_BagisFull end
    -- 记录参与次数 +1
    e:setEventDataX(EID.mhsd, (e:getEventDataX(EID.mhsd) or 0) + 1) e:saveEventData(EID.mhsd)
    -- 初始化随机数种子
    math.randomseed(os.time())
    local n = math.random(100)  -- 生成1-100的随机整数
    -- 奖励配置数组: 每个元素格式为 {最大随机数, 物品列表} 物品列表: 每个物品格式为 {物品ID, 数量}
    local configs = {
        {33, {{40004,5},{40053,20},{40148,5},{60223,1},{1,123450},{2,1016000}}},  -- 1-33概率: 33%
        {53, {{40004,6},{40053,10},{40148,11},{60231,1},{1,153450},{2,2300000}}},  -- 34-53概率: 20%
        {60, {{40004,8},{40053,15},{40148,20},{60239,2},{1,923450},{2,3500000}}},  -- 54-60概率: 7%
        {70, {{40004,7},{40053,16},{40148,12},{60223,1},{1,823450},{2,2080000}}},  -- 61-70概率: 10%
        {100,{{40004,3},{40053,8},{40148,13},{60231,1},{1,623450},{2,2012030}}}   -- 71-100概率: 30%
    }
    -- 遍历配置，根据随机数n决定发放哪个档位的奖励
   for _, cfg in ipairs(configs) do if n <= cfg[1] then
            -- 发放该档位的所有物品奖励
   for _, item in ipairs(cfg[2]) do  e:addItem(item[1], item[2], Opcode.op_plant) end  break end end
    return Error.Success
end
}

-- gdNPCExtension[12941] =
-- {
	-- [1] = function(entity)
		-- return addInstanceEnterTimes(entity, MapID.mhsd, 5)
	-- end,
	-- [2] = function(entity)
		-- return addInstanceEnterTimesByGold(entity, MapID.mhsd, 50)
	-- end,
-- }
--
--	转生神殿	zssd	转生地陵	zsdl
--
gdNPCExtension[1331] =
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.zssd) then
			return Error.NotEnoughLevel
		end

		return enterInstanceSelf(entity, MapID.zssd)
	end,
	[2] = function(entity)
		return addInstanceEnterTimes(entity, MapID.zssd, 1)
	end,
}

--
--	龙影潭		lyt
--
gdNPCExtension[1362] =
{
	[1] = function(entity)	--开启副本
		if not meetRequiredLvlEID(entity, EID.lyt) then
			return Error.NotEnoughLevel
		end

		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end

		local instanceid = guild:getProps(GuildProp.lyt_instance_id)
		local scene = gdScnMgr:getScene(instanceid)
		if scene then
			Scene.conveyentitytoSpecificInstance(entity, MapID.lyt, instanceid)
			return Error.Success
		end

		local opencount =  (guild:getProps(GuildProp.lyt_open_count) or 0) +1
		if opencount>6 then
			return Error.TooManyTimes
		end

		local reqmoney = opencount* 500000
		local money = guild:getProps(GuildProp.guild_money)
		if money<reqmoney then
			return Error.err_guild_notenoughgold
		end
		guild:setProps(GuildProp.guild_money, money-reqmoney)
		guild:syncProps(GuildProp.guild_money)
		guild:saveProps(GuildProp.guild_money)

		guild:setProps(GuildProp.lyt_open_count, opencount)
		guild:syncProps(GuildProp.lyt_open_count)
		guild:saveProps(GuildProp.lyt_open_count)

		guild:syncFloatMessage("龙影谭已经开启, 请行会的兄弟们速速前往!")

		local ec = Scene.conveyentitytoNewInstance(entity,MapID.lyt)
		if ec==Error.Success then
			scene = entity:getScene()
			if scene then
				scene:setProps(SceneProp.ownerguildid,guild:getID())
				entity:setProps(EntityProp.attr_instance_iid,0)
				guild:setProps(GuildProp.lyt_instance_id,scene:getID())
				guild:saveProps(GuildProp.lyt_instance_id)
			end
		end
		return ec
	end,
	[2] = function(entity)	--进入副本
		if not meetRequiredLvlEID(entity, EID.lyt) then
			return Error.NotEnoughLevel
		end

		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end

		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		local instanceid = guild:getProps(GuildProp.lyt_instance_id)
		local scene = gdScnMgr:getScene(instanceid)
		if scene then
			Scene.conveyentitytoSpecificInstance(entity, MapID.lyt, instanceid)
			entity:setProps(EntityProp.attr_instance_iid,0)
			return Error.Success
		else
			guild:setProps(GuildProp.lyt_instance_id, 0)
			guild:saveProps(GuildProp.lyt_instance_id)
			return Error.EventInactive
		end
	end,
}

local gcz_yuanbao =  function(entity)
	local mgid = entity:getProps(EP.attr_guild_id)
	if mgid==0 then
		return Error.err_guild_noguild
	end
	local ngid =  _G.getWorldDataX(WP.city_master_guild)
	if ngid~=mgid then
		return Error.err_guild_NotCityMasterGuild
	end
	local gpost = entity:getProps(EP.attr_guild_post)
	if gpost ~= GuildProp.post_master  then
		return Error.err_guild_NotMaster
	end

	local isget = _G.getWorldDataX(WorldProp.city_master_get_gold)
	if isget ~= 0 then
		return Error.AlreadyGet
	end

	local timetable = os.date("*t")
	local hour = timetable.hour
	local week = timetable.wday - 1
	if week == 5 and hour == 22 and timetable.min > 0 then
		_G.setWorldDataX(WorldProp.city_master_get_gold,1)
		_G.saveWorldData(WorldProp.city_master_get_gold)

		entity:addGold(1000,Opcode.gcz_week_gold)

		local guild = entity:getGuild()
		if guild then
			_G.syncFloatMessage(guild:getGuildName().."会的城主领取1000元宝沙城奖励,"..guild:getGuildName().."会笑傲沙城")
		end
		return Error.Success
	end
	return Error.err_guild_on_22_on_friday
end

--
--	沙皇宫 行政官
--
gdNPCExtension[174] =
{
	[2] = function(entity)	-- 收取税收
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end

		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end

		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		--
		--	在公会获得城主的时候会重置
		if guild:getProps(GuildProp.daily_tax)>0 then
			return Error.AlreadyUsed
		end
		guild:addProps(GuildProp.daily_tax)
		guild:saveProps(GuildProp.daily_tax)

		guild:addProps(GuildProp.guild_money, 1500000)
		guild:syncProps(GuildProp.guild_money)
		guild:saveProps(GuildProp.guild_money)

		return Error.err_guild_money_increased
	end,
	[3] = function(entity)	-- 领取时装和幻武
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end

		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master  then
			return Error.err_guild_NotMaster
		end

		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		--
		--	在公会获得城主的时候会重置
		if guild:getProps(GuildProp.daily_suite)>0 then
			return Error.AlreadyUsed
		end

		local ec = 0
		local gender = entity:getGender()  -- 性别 男= 1 女= 2
		if gender==1 then
			ec = entity:addBindItem(81178, 1)
			     entity:addItem(4, 25000)
				 entity:addItem(3, 2888888)
				 entity:addBindItem(1010, 1)
		else
			ec = entity:addBindItem(81189, 1)
			     entity:addItem(4, 25000)
				 entity:addItem(3, 2888888)
				 entity:addBindItem(1010, 1)
		end
		if ec==Error.Success then
			guild:addProps(GuildProp.daily_suite)
			guild:saveProps(GuildProp.daily_suite)
		end
		return ec
	end,
	[5] = gcz_yuanbao,
	[6] = gcz_yuanbao,
}

--
--	攻城战沙皇宫  攻城统领
--
gdNPCExtension[176] =
{
	[1] = function(entity)	-- 维修城墙 旗子
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end

		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		if entity:getGold()<100 then
			return Error.NotEnoughGold
		end

		local scene =  gdScnMgr:getSceneBySid(MapID.sc)
		if not scene then
			return Error.InvalidScene
		end

		local repaired = false
		scene:forEachEntityM(function(entity)
			if entity:getStaticID()==500 and entity:isAlive() then
				local cbt = entity:getCombatSys()
				if cbt then
					local hp = cbt:getHP()
					local maxhp = cbt:getMaxHP()
					if hp<maxhp then
						cbt:updateHP(maxhp*0.3,0)
						repaired = true
					end
				end
			end
		end)

		if repaired then
			entity:useGold(100, Opcode.gcz_repairewall)
			return Error.Success
		else
			return Error.PlayerStateGood
		end
	end,
}

--
--	荣誉神殿	rysd
--
gdNPCExtension[1741] =
{
	[1] = function(entity)	--开启副本
		if not meetRequiredLvlEID(entity, EID.rysd) then
			return Error.NotEnoughLevel
		end

		--攻城战开启期间不能参与荣誉神殿
		if Event.isActive(EID.gcz) then
			return Error.EventInactive
		end

		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end

		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end

		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		local scene = gdScnMgr:getSceneBySid(MapID.rysd)
		if scene then
			return Scene.conveyentitytoscene(entity, MapID.rysd)
		end

		local opencount =  (guild:getProps(GuildProp.rysd_open_count) or 0) + 1
		if opencount>2 then
			return Error.TooManyTimes
		end

		if opencount>1 then
			local money = guild:getProps(GuildProp.guild_money)
			if money<1500000000 then
				return Error.err_guild_notenoughgold
			end
			guild:setProps(GuildProp.guild_money, money-1500000000)
			guild:syncProps(GuildProp.guild_money)
			guild:saveProps(GuildProp.guild_money)
		end

		guild:setProps(GuildProp.rysd_open_count, opencount)
		guild:syncProps(GuildProp.rysd_open_count)
		guild:saveProps(GuildProp.rysd_open_count)

		guild:syncFloatMessage("荣誉神殿已经开启, 请兄弟们速速前往!")

		--创建场景
		Scene.onCreate(MapID.rysd)
		return Scene.conveyentitytoscene(entity, MapID.rysd)
	end,
	[2] = function(entity)	--进入副本
		if not meetRequiredLvlEID(entity, EID.rysd) then
			return Error.NotEnoughLevel
		end

		--攻城战开启期间不能参与荣誉神殿
		if Event.isActive(EID.gcz) then
			return Error.EventInactive
		end

		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end

		local scene = gdScnMgr:getSceneBySid(MapID.rysd)
		if not scene then
			return Error.EventInactive
		end

		return Scene.conveyentitytoscene(entity, MapID.rysd)
	end,
}
--
--	发财大家发	fcdjf
--

local function fcdjf_execute(entity, data)
	local mgid = entity:getProps(EP.attr_guild_id)
	if mgid==0 then
		return Error.err_guild_noguild
	end

	local gpost = entity:getProps(EP.attr_guild_post)
	if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
		return Error.err_guild_NotMaster
	end

	local scene = entity:getScene()
	if not scene then
		return Error.InvalidScene
	end

	local guild = entity:getGuild()
	if not guild then
		return Error.err_guild_noguild
	end

	local reward = {
		{1000000, 30275},
		{5000000, 30276},
		{10000000, 30277}}
	local reward = reward[data]
	if not reward then
		return Error.Unknown
	end

	local money = guild:getProps(GuildProp.guild_money)
	if money<reward[1] then
		return Error.err_guild_notenoughgold
	end
	guild:setProps(GuildProp.guild_money, money-reward[1])
	guild:syncProps(GuildProp.guild_money)
	guild:saveProps(GuildProp.guild_money)

	scene:forEachEntityP(function(ett)
			--当前场景的本行会所有成员都会获得礼包
			if ett:getProps(EP.attr_guild_id)==mgid then
				ett:addBindItem(reward[2], 1, Opcode.fcdjf)
			end
		end)
	return Error.Success
end

gdNPCExtension[1742] =
{
	[1] = function(entity)--100W
		return fcdjf_execute(entity, 1)
	end,
	[2] = function(entity)--500W
		return fcdjf_execute(entity, 2)
	end,
	[3] = function(entity)--1000W
		return fcdjf_execute(entity, 3)
	end
}

--
--	维修城墙	wxcq
--
gdNPCExtension[1743] =
{
	[1] = function(entity)--100W
		return Error.Success
	end,
}

--
--	祈福仙子		qfxz
--
local qfxz_update_qfz = function(entity, delta)	--祈福仙子 祈福值更新逻辑
	entity:addEventDataX(EID.qfxzqfz, delta)
	entity:syncEventData(EID.qfxzqfz)
	entity:saveEventData(EID.qfxzqfz)

--	local firstcnt = _G.getWorldDataY(WP.qfxz_rank)
--	if entity:getProps(EP.attr_worldpray_cnt)>firstcnt then
--		_G.setWorldDataX(WP.qfxz_rank, entity:getGlobalID())
--		_G.setWorldDataY(WP.qfxz_rank, firstcnt)
--		_G.setWorldDataS(WP.qfxz_rank, "第一名: "..entity:getName() )
--		_G.saveWorldData(WP.qfxz_rank)
--		_G.updateHeadTitle(WP.qfxz_rank)
--	end
end

-- local qfxz_scene = function(entity, cnt)
	-- local scene = entity:getScene()
	-- if not scene then
		-- return Error.InvalidScene
	-- end
	-- if entity:getGold()<=cnt then
		-- return Error.NotEnoughGold
	-- end
	-- entity:useGold(cnt,Opcode.qifuxianziscene)
	-- entity:addProps(EP.attr_worldpray_cnt,cnt)
	-- entity:saveProps(EP.attr_worldpray_cnt)
	-- qfxz_update_qfz(entity, cnt)
	-- HeadTitle.checkPrayCnt(entity)

	-- if entity:getProps(EP.attr_worldpray_cnt)>=50 then
		-- DailyAct.AddTargetCnt(entity,EID.mrmrqf)
	-- end

	-- scene:addProps(SP.qfxz_scene_data, cnt*2)
	-- scene:addTimerEvent(100, 120000)
	-- _G.syncFloatMessage(entity:getName().." 在祈福仙子处进行祈福，2分钟后，将会在土城安全区发放仙玉！")
	-- return Error.Success
-- end

-- local qfxz_guild = function(entity, cnt)
	-- local scene = entity:getScene()
	-- if not scene then
		-- return Error.InvalidScene
	-- end

	-- local guild = entity:getGuild()
	-- if not guild then
		-- return Error.err_guild_noguild
	-- end

	-- local gidold = scene:getProps(SP.qfxz_guild_id)
	-- if gidold~=0 and gidold~=guild:getID() then
		-- return Error.AlreadyUsed
	-- end

	-- if entity:getGold()<=cnt then
		-- return Error.NotEnoughGold
	-- end
	-- entity:useGold(cnt,Opcode.qifuxianziguild)
	-- qfxz_update_qfz(entity, cnt)


	-- scene:addProps(SP.qfxz_guild_data, cnt*2)
	-- scene:setProps(SP.qfxz_guild_id, guild:getID())
	-- scene:addTimerEvent(101, 120000)
	-- guild:syncFloatMessage(entity:getName().." 在祈福仙子处进行行会祈福，2分钟后, 所有在线的行会兄弟将会获得仙玉！")
	-- return Error.Success
-- end

-- gdNPCExtension[1791] =	--全服祈福
-- {
	-- [1] = function(entity)	return qfxz_scene(entity, 10)		end,
	-- [2] = function(entity)  return qfxz_scene(entity, 100)		end,
	-- [3] = function(entity)  return qfxz_scene(entity, 1000)		end,
	-- [4] = function(entity)  return qfxz_scene(entity, 10000)	end,
	-- [5] = function(entity)  return qfxz_scene(entity, 20000)	end,
-- }

-- gdNPCExtension[1792] =	--行会祈福
-- {
	-- [1] = function(entity)  return qfxz_guild(entity, 10)		end,
	-- [2] = function(entity)  return qfxz_guild(entity, 100)		end,
	-- [3] = function(entity)  return qfxz_guild(entity, 1000)		end,
	-- [4] = function(entity)  return qfxz_guild(entity, 10000)	end,
	-- [5] = function(entity)  return qfxz_guild(entity, 20000)	end,
-- }

-- gdNPCExtension[1793] =	--领取祈福奖励
-- {
	-- [1] = function(entity)
		-- local qfz = entity:getEventDataX(EID.qfxzqfz)
		-- if qfz<1000 then
			-- return Error.NotEnoughCondition
		-- end
		-- qfxz_update_qfz(entity, -1000)
		-- entity:addHonor(50000,Opcode.Op_Activity,EID.qfxzqfz)
		-- return Error.Success
	-- end,
-- }

-- gdNPCExtension[1794] =	--领取祈福奖励
-- {
-- }
--
--	土城抗魔	tckm xmdz
--
gdNPCExtension[183] =
{
	[1] = function(entity)
		Scene.conveyentitytoAnywhere(entity, MapID.tc, 127, 116)
		return Error.Success
	end,
}

---------------------------------------------------------------------------------------------------

--
--	用于判断NPC功能是否show       gdNPCFuncShow[NPCID][numid]
--
gdNPCFuncShow[107]=
{
	[1] = function(entity)
		if entity:getLevel()>=35 then
			if(entity:getProps(EntityProp.attr_meinvhusong_remain)==0) then
				return 1
			end
		end
		return 0
	end
}


--
--	打捆商人 	dksr
--

local dksr_merge = function(entity, src, cnt, cost, tgt)
	if entity:getMoney()<cost then
		return Error.NotEnoughMoney
	end
	if entity:hasItem(src, cnt) then
		entity:rmvItem(src, cnt)
		entity:useMoney(cost,Opcode.BundlingItem,tgt)
		entity:addBindItem(tgt, 1)
		return Error.Success
	else
		return Error.NotEnoughItem
	end
	return Error.Success
end

--	打捆红玫瑰
gdNPCExtension[1231] =
{
	[1] = function(entity)	--打捆9朵红玫瑰
		return dksr_merge(entity, 39029, 9, 10000, 40081)
	end,
	[2] = function(entity)	--打捆99朵红玫瑰
		return dksr_merge(entity, 40081, 10, 10000, 40082)
	end,
	[3] = function(entity)	--打捆999朵红玫瑰
		return dksr_merge(entity, 40082, 10, 10000, 40083)
	end,
}


local dksr_split = function(entity, src, tgt, cnt)
	if entity:hasItem(src, 1) then
		entity:rmvItem(src, 1)
		entity:addBindItem(tgt, cnt)
		return Error.Success
	else
		return Error.NotEnoughItem
	end
	return Error.Success
end

--	解捆红玫瑰
gdNPCExtension[1232] =
{
	[1] = function(entity)	--解捆9朵红玫瑰
		return dksr_split(entity, 40081, 39029, 9)
	end,
	[2] = function(entity)	--解捆99朵红玫瑰
		return dksr_split(entity, 40082, 40081, 10)
	end,
	[3] = function(entity)	--解捆999朵红玫瑰
		return dksr_split(entity, 40083, 40082, 10)
	end,
}

--
--	兑换经验神符	sdlb	jysf
--

local jysf_merge = function(entity, src, cnt, cost, tgt)
	if entity:getMoney()<cost then
		return Error.NotEnoughMoney
	end
	if entity:hasItem(src, cnt) then
		entity:rmvItem(src, cnt)
		entity:useMoney(cost,Opcode.Exchangejysf,tgt)
		entity:addBindItem(tgt, 1)
		return Error.Success
	else
		return Error.NotEnoughItem
	end
	return Error.Success
end

gdNPCExtension[1211] =
{
	[1] = function(entity)	--兑换2倍经验神符
		local rtv = jysf_merge(entity, 30000, 3, 10000, 30001)
		if rtv~=Error.Success then
			rtv = jysf_merge(entity, 30158, 3, 10000, 30159)
		end
		return rtv
	end,
	[2] = function(entity)	--兑换3倍经验神符
		local rtv = jysf_merge(entity, 30001, 3, 20000, 30002)
		if rtv~=Error.Success then
			rtv = jysf_merge(entity, 30159, 3, 20000, 30160)
		end
		return rtv
	end,
	[3] = function(entity)	--兑换4倍经验神符
		local rtv = jysf_merge(entity, 30002, 2, 30000, 30003)
		if rtv~=Error.Success then
			rtv = jysf_merge(entity, 30160, 2, 30000, 30161)
		end
		return rtv
	end,
	[4] = function(entity)	--兑换5倍经验神符
		local rtv = jysf_merge(entity, 30003, 2, 40000, 30005)
		if rtv~=Error.Success then
			rtv = jysf_merge(entity, 30161, 2, 40000, 30165)
		end
		return rtv
	end,
	[5] = function(entity)	--兑换6倍经验神符
		local rtv = jysf_merge(entity, 30005, 2, 50000, 30054)
		if rtv~=Error.Success then
			rtv = jysf_merge(entity, 30165, 2, 50000, 30162)
		end
		return rtv
	end,
}


--
--	玫瑰使 	mgs	购买红玫瑰
--

gdNPCExtension[1221] =
{
	[1] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=1 then
			entity:useGold(1,Opcode.buy_rose)
			entity:addItem(39029, 3)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[2] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=3 then
			entity:useGold(3,Opcode.buy_rose)
			entity:addItem(39029, 9)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[3] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=2 then
			entity:useGold(2,Opcode.buy_rose)
			entity:addItem(39042, 1)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
	[4] = function(entity)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		elseif entity:getGold()>=18 then
			entity:useGold(18,Opcode.buy_rose)
			entity:addItem(39042, 9)
			return Error.Success
		else
			return Error.NotEnoughGold
		end
	end,
}

gdNPCExtension[1711] = gdNPCExtension[1221]

--
--	玫瑰使 	mgs	灵石分解 lsfj
--

local lsfj_split = function (entity, srcsid, tgtsid, cnt)
	local money = 10000
	if entity:getMoney()<money then
		return Error.NotEnoughMoney
	end
	local item = entity:getItemBySid(srcsid)
	if not item then
		return Error.NotEnoughItem
	end

	local bind = item:getProps(IP.Item_Bind)

	entity:rmvItemExactly(item:getIID(), 1)
	entity:useMoney(money,Opcode.lingshi_split)
	if bind==1 then
		entity:addBindItem(tgtsid, 3, Opcode.lingshi_split)
	else
		entity:addItem(tgtsid, 3, Opcode.lingshi_split)
	end
	return Error.Success
end

gdNPCExtension[1222] = {
	[1] = function(entity)	return lsfj_split(entity, 40004, 40003, 3)	end,
	[2] = function(entity)	return lsfj_split(entity, 40003, 40002, 3)	end,
	[3] = function(entity)	return lsfj_split(entity, 40002, 40001, 3)	end,
	[4] = function(entity)	return lsfj_split(entity, 40001, 40000, 3)	end,
}

gdNPCExtension[1712] = gdNPCExtension[1222]

--
--	传送石	css
--
--

local function css_go(entity, mid, money)
	if isProtectGirl(entity) then
		return Error.Meinvhusong_is_begin
	end
	if entity:getMoney()<money then
		return Error.NotEnoughMoney
	end
	entity:useMoney(money,Opcode.teleport,mid)
	Scene.conveyentitytoscene(entity, mid)
	return Error.Success
end

local function css_goxy(entity, mid, money, posx, posy)
	if isProtectGirl(entity) then
		return Error.Meinvhusong_is_begin
	end
	if entity:getMoney()<money then
		return Error.NotEnoughMoney
	end
	entity:useMoney(money,Opcode.teleport,mid)
	Scene.conveyentitytoAnywhere(entity, mid, posx, posy)
	return Error.Success
end

local css_npc =
{
	[1] = function(entity) 	return	css_go(entity, MapID.wc, 1000) end,
	[2] = function(entity) 	return	css_go(entity, MapID.tc, 1000) end,
	[3] = function(entity) 	return	css_go(entity, MapID.ydc, 1000) end,
	[4] = function(entity) 	return	css_go(entity, MapID.kd, 5000) end,
	[5] = function(entity) 	return	css_go(entity, MapID.cd, 5000) end,
	[6] = function(entity) 	return	css_go(entity, MapID.zyd, 5000) end,
	[7] = function(entity) 	return	css_go(entity, MapID.jhsm, 5000) end,
	[8] = function(entity) 	return	css_go(entity, MapID.emdx, 5000) end,
	[9] = function(entity) 	return	css_go(entity, MapID.wlbhs, 5000) end,
	[10] = function(entity) return	css_go(entity, MapID.mh, 5000) end,
	[11] = function(entity) return	css_go(entity, MapID.hdsj, 5000) end,
	[12] = function(entity) return	css_go(entity, MapID.xy, 10000) end,
	[13] = function(entity) return	css_goxy(entity, MapID.tc, 1000, 304, 202) end,
	[14] = function(entity) return	css_goxy(entity, MapID.wc, 1000, 227, 198) end,
	[15] = function(entity) return	css_go(entity, MapID.fmg, 1000) end,
}

gdNPCExtension[113] = css_npc
gdNPCExtension[118] = css_npc
gdNPCExtension[165] = css_npc
gdNPCExtension[220] = css_npc
-----------------------------------------------------------------------------------------------



--
--	神兵溶合	sbrh
--

local	sbrh_getEquipedItem = function(entity, sid)
	local item = nil
	for pos = -17, -1 do
		item = entity:getItemByPosition(pos)
		if item and item:getSID()==sid then
			return item
		end
	end
end

local	sbrh_hasPackItems = function(entity, sid, rebornlvl, cnt)
	local item = nil
	rebornlvl = rebornlvl or 0
	cnt = cnt or 1
	for pos = 1, 80 do
		item = entity:getItemByPosition(pos)
		if item and item:getSID()==sid and item:getProps(IP.Item_RebornLvl)==rebornlvl then
			cnt = cnt-1
			if cnt<=0 then
				return true
			end
		end
	end
	return false
end

local	sbrh_rmvPackItems = function(entity, sid, rebornlvl, cnt)
	local item = nil
	rebornlvl = rebornlvl or 0
	cnt = cnt or 1
	for pos = 1, 80 do
		item = entity:getItemByPosition(pos)
		if item and item:getSID()==sid and item:getProps(IP.Item_RebornLvl)==rebornlvl then
			entity:rmvItemExactly(item:getIID())
			cnt = cnt-1
			if cnt<=0 then
				return true
			end
		end
	end
	return false
end

local sbrh_merge = function(entity, srcsid, cnt, tgtsid)
	local money = 100000
	if entity:getMoney()<money then
		return Error.NotEnoughMoney
	end

	local sd = gdItems[tgtsid]
	if not sd then
		return Error.InvalidItem
	end

	if entity:getProps(EP.attr_reborn)<1 and entity:getLevel()<sd.req_level then
		return Error.NotEnoughLevel
	end

	local item = sbrh_getEquipedItem(entity, srcsid)
	if not item then
		return Error.PlayerHasNotEquipThisItem
	end

	if not entity:hasItem(srcsid, cnt - 1) then
		return Error.NotEnoughItem
	end

	local ec = entity:addItem(tgtsid, 1)
	if ec==Error.Success then
		local itemattr = {}
		for idx = 1, IP.Item_Max do
			itemattr[idx] = item:getProps(idx)
		end

		entity:useMoney(money,Opcode.Op_Item_Merge,tgtsid)
		Item.onPutOff(entity, item)
		entity:rmvItemExactly(item:getIID())
		entity:rmvItem(srcsid, cnt-1)

		local nitem = entity:getItemLastAdd()
		if nitem then
			for idx = 1, IP.Item_Max do
				if itemattr[idx] and itemattr[idx]~=0 then
					nitem:setProps(idx, itemattr[idx])
					entity:saveItemProps(nitem,idx)
					entity:syncItemProps(nitem,idx)
				end
			end
		end
	end
	entity:syncPlayerCombatCombo()
	return ec
end

local sbrh_merge_with_reborn = function(entity, srcsid, cnt, rebornlvl, tgtsid, tgtrebornlvl)
	local money = 100000
	if entity:getMoney()<money then
		return Error.NotEnoughMoney
	end

	rebornlvl = rebornlvl or 0
	tgtrebornlvl = tgtrebornlvl or 0

	local sd = gdItems[tgtsid]
	if not sd then
		return Error.InvalidItem
	end
	if entity:getProps(EP.attr_reborn)<1 and entity:getLevel()<sd.req_level then
		return Error.NotEnoughLevel
	end

	local item = sbrh_getEquipedItem(entity, srcsid)
	if not item then
		return Error.PlayerHasNotEquipThisItem
	end

	if not sbrh_hasPackItems(entity, srcsid, rebornlvl, cnt - 1) then
		return Error.NotEnoughItem
	end

	local ec = entity:addItem(tgtsid, 1)
	if ec==Error.Success then
		local itemattr = {}
		for idx = 1, IP.Item_Max do
			itemattr[idx] = item:getProps(idx)
		end
		itemattr[IP.Item_RebornLvl] = tgtrebornlvl or 0

		entity:useMoney(money,Opcode.Op_Item_Merge,tgtsid)
		Item.onPutOff(entity, item)
		entity:rmvItemExactly(item:getIID())
		sbrh_rmvPackItems(entity, srcsid, rebornlvl, cnt-1)

		local nitem = entity:getItemLastAdd()
		if nitem then
			for idx = 1, IP.Item_Max do
				if itemattr[idx] and itemattr[idx]~=0 then
					nitem:setProps(idx, itemattr[idx])
					entity:saveItemProps(nitem,idx)
					entity:syncItemProps(nitem,idx)
				end
			end
		end
	end
	entity:syncPlayerCombatCombo()
	return ec
end

local sbrh_merge_with_mat = function(entity, srcsid, rebornlvl, matsid, cnt, tgtsid, tgtrebornlvl)
	local money = 100000
	if entity:getMoney()<money then
		return Error.NotEnoughMoney
	end

	tgtrebornlvl = tgtrebornlvl or 0
	if entity:getProps(EP.attr_reborn)<tgtrebornlvl then
		return Error.NotEnoughLevel
	end

	if not entity:hasItem(matsid, cnt) then
		return Error.NotEnoughItem
	end

	local item = nil
	if type(srcsid)=="table" then
		for _, v in pairs(srcsid) do
			item = sbrh_getEquipedItem(entity, v)
			if item then
				break
			end
		end
	else
		item = sbrh_getEquipedItem(entity, srcsid)
	end

	if not item then
		return Error.PlayerHasNotEquipThisItem
	end

	if item:getProps(IP.Item_RebornLvl)<rebornlvl then
		return Error.PlayerHasNotEquipThisItem
	end

	local ec = entity:addItem(tgtsid, 1)
	if ec==Error.Success then
		local itemattr = {}
		for idx = 1, IP.Item_Max do
			itemattr[idx] = item:getProps(idx)
		end
		itemattr[IP.Item_RebornLvl] = tgtrebornlvl or 0

		entity:useMoney(money,Opcode.Op_Item_Merge,tgtsid)
		Item.onPutOff(entity, item)
		entity:rmvItemExactly(item:getIID())
		entity:rmvItem(matsid, cnt)

		local nitem = entity:getItemLastAdd()
		if nitem then
			for idx = 1, IP.Item_Max do
				if itemattr[idx] and itemattr[idx]~=0 then
					nitem:setProps(idx, itemattr[idx])
					entity:saveItemProps(nitem,idx)
					entity:syncItemProps(nitem,idx)
				end
			end
		end
	end
	entity:syncPlayerCombatCombo()
	return ec
end

--
--	神兵溶合	sbrh	战士	45
--
gdNPCExtension[19611] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60064, 5, 60074) end,
	[2] = function(entity)	return sbrh_merge(entity, 60065, 3, 60075) end,
	[3] = function(entity)	return sbrh_merge(entity, 60068, 4, 60078) end,
	[4] = function(entity)	return sbrh_merge(entity, 60067, 4, 60077) end,
	[5] = function(entity)	return sbrh_merge(entity, 60066, 5, 60076) end,
}

--
--	神兵溶合	sbrh	战士	50
--
gdNPCExtension[19612] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60074, 5, 60084) end,
	[2] = function(entity)	return sbrh_merge(entity, 60075, 3, 60085) end,
	[3] = function(entity)	return sbrh_merge(entity, 60078, 4, 60088) end,
	[4] = function(entity)	return sbrh_merge(entity, 60077, 4, 60087) end,
	[5] = function(entity)	return sbrh_merge(entity, 60076, 5, 60086) end,
}

--
--	神兵溶合	sbrh	战士	55
--
gdNPCExtension[19613] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60084, 5, 60094) end,
	[2] = function(entity)	return sbrh_merge(entity, 60085, 3, 60095) end,
	[3] = function(entity)	return sbrh_merge(entity, 60088, 4, 60098) end,
	[4] = function(entity)	return sbrh_merge(entity, 60087, 4, 60097) end,
	[5] = function(entity)	return sbrh_merge(entity, 60086, 5, 60096) end,
}

--
--	神兵溶合	sbrh	战士	60
--
gdNPCExtension[19614] =
{
	[1] = function(entity)	return sbrh_merge_with_reborn(entity, 60094, 2, 5, 60104, 3) end,
	[2] = function(entity)	return sbrh_merge_with_reborn(entity, 60095, 2, 5, 60105, 3) end,
	[3] = function(entity)	return sbrh_merge_with_reborn(entity, 60098, 2, 5, 60108, 3) end,
	[4] = function(entity)	return sbrh_merge_with_reborn(entity, 60097, 2, 5, 60107, 3) end,
	[5] = function(entity)	return sbrh_merge_with_reborn(entity, 60096, 2, 5, 60106, 3) end,
}

--
--	神兵溶合	sbrh	法师	45
--
gdNPCExtension[19621] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60124, 5, 60134) end,
	[2] = function(entity)	return sbrh_merge(entity, 60125, 3, 60135) end,
	[3] = function(entity)	return sbrh_merge(entity, 60128, 4, 60138) end,
	[4] = function(entity)	return sbrh_merge(entity, 60127, 4, 60137) end,
	[5] = function(entity)	return sbrh_merge(entity, 60126, 5, 60136) end,
}

--
--	神兵溶合	sbrh	法师	50
--
gdNPCExtension[19622] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60134, 5, 60144) end,
	[2] = function(entity)	return sbrh_merge(entity, 60135, 3, 60145) end,
	[3] = function(entity)	return sbrh_merge(entity, 60138, 4, 60148) end,
	[4] = function(entity)	return sbrh_merge(entity, 60137, 4, 60147) end,
	[5] = function(entity)	return sbrh_merge(entity, 60136, 5, 60146) end,
}

--
--	神兵溶合	sbrh	法师	55
--
gdNPCExtension[19623] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60144, 5, 60154) end,
	[2] = function(entity)	return sbrh_merge(entity, 60145, 3, 60155) end,
	[3] = function(entity)	return sbrh_merge(entity, 60148, 4, 60158) end,
	[4] = function(entity)	return sbrh_merge(entity, 60147, 4, 60157) end,
	[5] = function(entity)	return sbrh_merge(entity, 60146, 5, 60156) end,
}

--
--	神兵溶合	sbrh	法师	60
--
gdNPCExtension[19624] =
{
	[1] = function(entity)	return sbrh_merge_with_reborn(entity, 60154, 2, 5, 60164, 3) end,
	[2] = function(entity)	return sbrh_merge_with_reborn(entity, 60155, 2, 5, 60165, 3) end,
	[3] = function(entity)	return sbrh_merge_with_reborn(entity, 60158, 2, 5, 60168, 3) end,
	[4] = function(entity)	return sbrh_merge_with_reborn(entity, 60157, 2, 5, 60167, 3) end,
	[5] = function(entity)	return sbrh_merge_with_reborn(entity, 60156, 2, 5, 60166, 3) end,
}

--
--	神兵溶合	sbrh	道士	45
--
gdNPCExtension[19631] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60004, 5, 60014) end,
	[2] = function(entity)	return sbrh_merge(entity, 60005, 3, 60015) end,
	[3] = function(entity)	return sbrh_merge(entity, 60008, 4, 60018) end,
	[4] = function(entity)	return sbrh_merge(entity, 60007, 4, 60017) end,
	[5] = function(entity)	return sbrh_merge(entity, 60006, 5, 60016) end,
}

--
--	神兵溶合	sbrh	道士	50
--
gdNPCExtension[19632] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60014, 5, 60024) end,
	[2] = function(entity)	return sbrh_merge(entity, 60015, 3, 60025) end,
	[3] = function(entity)	return sbrh_merge(entity, 60018, 4, 60028) end,
	[4] = function(entity)	return sbrh_merge(entity, 60017, 4, 60027) end,
	[5] = function(entity)	return sbrh_merge(entity, 60016, 5, 60026) end,
}

--
--	神兵溶合	sbrh	道士	55
--
gdNPCExtension[19633] =
{
	[1] = function(entity)	return sbrh_merge(entity, 60024, 5, 60034) end,
	[2] = function(entity)	return sbrh_merge(entity, 60025, 3, 60035) end,
	[3] = function(entity)	return sbrh_merge(entity, 60028, 4, 60038) end,
	[4] = function(entity)	return sbrh_merge(entity, 60027, 4, 60037) end,
	[5] = function(entity)	return sbrh_merge(entity, 60026, 5, 60036) end,
}

--
--	神兵溶合	sbrh	道士	60
--
gdNPCExtension[19634] =
{
	[1] = function(entity)	return sbrh_merge_with_reborn(entity, 60034, 2, 5, 60044, 3) end,
	[2] = function(entity)	return sbrh_merge_with_reborn(entity, 60035, 2, 5, 60045, 3) end,
	[3] = function(entity)	return sbrh_merge_with_reborn(entity, 60038, 2, 5, 60048, 3) end,
	[4] = function(entity)	return sbrh_merge_with_reborn(entity, 60037, 2, 5, 60047, 3) end,
	[5] = function(entity)	return sbrh_merge_with_reborn(entity, 60036, 2, 5, 60046, 3) end,
}

--
--	神兵溶合	sbrh	绝世无双<--5转70级
--
gdNPCExtension[19641] =
{
	[1] = function(entity)	return sbrh_merge_with_mat(entity, {60110, 60170, 60050}, 5, 40136, 65, 60276,3) end,
	[2] = function(entity)	return sbrh_merge_with_mat(entity, {60112, 60172, 60052}, 5, 40136, 35, 60277,3) end,
	[3] = function(entity)	return sbrh_merge_with_mat(entity, {60113, 60173, 60053}, 5, 40136, 35, 60278,3) end,
	[4] = function(entity)	return sbrh_merge_with_mat(entity, {60111, 60171, 60051}, 5, 40136, 30, 60279,3) end,
	[5] = function(entity)	return sbrh_merge_with_mat(entity, {60114, 60174, 60054}, 5, 40136, 15, 60282,3) end,
	[6] = function(entity)	return sbrh_merge_with_mat(entity, {60115, 60175, 60055}, 5, 40136, 10, 60283,3) end,
	[7] = function(entity)	return sbrh_merge_with_mat(entity, {60118, 60178, 60058}, 5, 40136, 10, 60280,3) end,
	[8] = function(entity)	return sbrh_merge_with_mat(entity, {60117, 60177, 60057}, 5, 40136, 10, 60281,3) end,
	[9] = function(entity)	return sbrh_merge_with_mat(entity, {60116, 60176, 60056}, 5, 40136, 15, 60284,3) end,
}

--
--	神兵溶合	sbrh	绝世无双<--2转极·浑天磐龙套
--
gdNPCExtension[19642] =
{
	[1] = function(entity)	return sbrh_merge_with_mat(entity, 60337, 2, 40136, 13, 60276) end,
	[2] = function(entity)	return sbrh_merge_with_mat(entity, 60339, 2, 40136, 7, 60277) end,
	[3] = function(entity)	return sbrh_merge_with_mat(entity, 60340, 2, 40136, 7, 60278) end,
	[4] = function(entity)	return sbrh_merge_with_mat(entity, 60338, 2, 40136, 6, 60279) end,
	[5] = function(entity)	return sbrh_merge_with_mat(entity, 60341, 2, 40136, 3, 60282) end,
	[6] = function(entity)	return sbrh_merge_with_mat(entity, 60342, 2, 40136, 2, 60283) end,
	[7] = function(entity)	return sbrh_merge_with_mat(entity, 60345, 2, 40136, 2, 60280) end,
	[8] = function(entity)	return sbrh_merge_with_mat(entity, 60344, 2, 40136, 2, 60281) end,
	[9] = function(entity)	return sbrh_merge_with_mat(entity, 60343, 2, 40136, 2, 60284) end,
}

--
--	神兵溶合	sbrh	绝世无双<--3转极·浑天磐龙套
--
gdNPCExtension[19643] =
{
	[1] = function(entity)	return sbrh_merge_with_mat(entity, 60337, 3, 40136, 13, 60276,1) end,
	[2] = function(entity)	return sbrh_merge_with_mat(entity, 60339, 3, 40136, 7, 60277,1) end,
	[3] = function(entity)	return sbrh_merge_with_mat(entity, 60340, 3, 40136, 7, 60278,1) end,
	[4] = function(entity)	return sbrh_merge_with_mat(entity, 60338, 3, 40136, 6, 60279,1) end,
	[5] = function(entity)	return sbrh_merge_with_mat(entity, 60341, 3, 40136, 3, 60282,1) end,
	[6] = function(entity)	return sbrh_merge_with_mat(entity, 60342, 3, 40136, 2, 60283,1) end,
	[7] = function(entity)	return sbrh_merge_with_mat(entity, 60345, 3, 40136, 2, 60280,1) end,
	[8] = function(entity)	return sbrh_merge_with_mat(entity, 60344, 3, 40136, 2, 60281,1) end,
	[9] = function(entity)	return sbrh_merge_with_mat(entity, 60343, 3, 40136, 3, 60284,1) end,
}

--
--	神兵溶合	sbrh	绝世无双<--4转极·浑天磐龙套
--
gdNPCExtension[19644] =
{
	[1] = function(entity)	return sbrh_merge_with_mat(entity, 60337, 4, 40136, 13, 60276,2) end,
	[2] = function(entity)	return sbrh_merge_with_mat(entity, 60339, 4, 40136, 7, 60277,2) end,
	[3] = function(entity)	return sbrh_merge_with_mat(entity, 60340, 4, 40136, 7, 60278,2) end,
	[4] = function(entity)	return sbrh_merge_with_mat(entity, 60338, 4, 40136, 6, 60279,2) end,
	[5] = function(entity)	return sbrh_merge_with_mat(entity, 60341, 4, 40136, 3, 60282,2) end,
	[6] = function(entity)	return sbrh_merge_with_mat(entity, 60342, 4, 40136, 2, 60283,2) end,
	[7] = function(entity)	return sbrh_merge_with_mat(entity, 60345, 4, 40136, 2, 60280,2) end,
	[8] = function(entity)	return sbrh_merge_with_mat(entity, 60344, 4, 40136, 2, 60281,2) end,
	[9] = function(entity)	return sbrh_merge_with_mat(entity, 60343, 4, 40136, 3, 60284,2) end,
}

--
--	神兵溶合	sbrh	绝世无双<--5转极·浑天磐龙套
--
gdNPCExtension[19645] =
{
	[1] = function(entity)	return sbrh_merge_with_mat(entity, 60337, 5, 40136, 13, 60276,3) end,
	[2] = function(entity)	return sbrh_merge_with_mat(entity, 60339, 5, 40136, 7, 60277,3) end,
	[3] = function(entity)	return sbrh_merge_with_mat(entity, 60340, 5, 40136, 7, 60278,3) end,
	[4] = function(entity)	return sbrh_merge_with_mat(entity, 60338, 5, 40136, 6, 60279,3) end,
	[5] = function(entity)	return sbrh_merge_with_mat(entity, 60341, 5, 40136, 3, 60282,3) end,
	[6] = function(entity)	return sbrh_merge_with_mat(entity, 60342, 5, 40136, 2, 60283,3) end,
	[7] = function(entity)	return sbrh_merge_with_mat(entity, 60345, 5, 40136, 2, 60280,3) end,
	[8] = function(entity)	return sbrh_merge_with_mat(entity, 60344, 5, 40136, 2, 60281,3) end,
	[9] = function(entity)	return sbrh_merge_with_mat(entity, 60343, 5, 40136, 3, 60284,3) end,
}


--
--	城主膜拜	czmb
--
gdNPCExtension[1432] = 	--	开启行会经验buff
{
	[1] = function(entity)
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end
		local guild = entity:getGuild()
		if not guild then
			return Error.err_guild_noguild
		end

		local cntmobai = _G.getWorldDataX(WorldProp.mobai_bishi_count)
		local cntbishi = _G.getWorldDataY(WorldProp.mobai_bishi_count)

		if cntmobai-cntbishi<100 then
			return Error.NotEnoughCondition
		end

		local geneid = 0
		local level = 1
		if cntmobai>=500 then
			geneid = 40105
			level = 5
		elseif cntmobai>=400 then
			geneid = 40104
			level = 4
		elseif cntmobai>=300 then
			geneid = 40103
			level = 3
		elseif cntmobai>=200 then
			geneid = 40102
			level = 2
		else
			geneid = 40101
			level = 1
		end
		if _G.getWorldDataX(WorldProp.mobai_guild_buff) == level then
			if _G.getWorldDataY(WorldProp.mobai_guild_buff)>0 then
				return Error.AlreadyUsed
			end
		end
		_G.setWorldDataX(WorldProp.mobai_guild_buff, level)
		_G.setWorldDataY(WorldProp.mobai_guild_buff, 1)
		_G.saveWorldData(WorldProp.mobai_guild_buff)

		guild:forEach(function(entity)
			entity:addGene(geneid)
		end)
		return Error.Success
	end,
}
gdNPCExtension[1433] = 	--	城主奖励
{
	[1] = function(entity)
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master then
			return Error.err_guild_NotMaster
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end


		local cntmobai = _G.getWorldDataX(WorldProp.mobai_bishi_count)
		local cntbishi = _G.getWorldDataY(WorldProp.mobai_bishi_count)

		if cntmobai-cntbishi<200 then
			return Error.NotEnoughCondition
		end

		if _G.getWorldDataX(WP.mobai_guild_master_reward)>0 then
			return Error.AlreadyUsed
		end
		_G.addWorldDataX(WP.mobai_guild_master_reward)
		_G.saveWorldData(WP.mobai_guild_master_reward)

		local base = 100000000
		local exp =  base + 5273 * entity:getLevel() * (cntmobai-cntbishi)
		if (exp > 200000000) then
			exp = 200000000
		end
		entity:addExp(exp,Opcode.mobaiczreward)
		return Error.Success
	end,
}
gdNPCExtension[1434] = 	--	悬赏膜拜
{
	[1] = function(entity)	--100元宝
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end


		local cnt = 100
		if entity:getGold()<cnt then
			return Error.NotEnoughGold
		end
		entity:useGold(cnt,Opcode.mobaixuanshang)
		_G.addWorldDataX(WorldProp.mobai_money_count, cnt*2)
		_G.saveWorldData(WorldProp.mobai_money_count)
		return Error.Success
	end,
	[2] = function(entity)	--200元宝
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end

		local cnt = 200
		if entity:getGold()<cnt then
			return Error.NotEnoughGold
		end
		entity:useGold(cnt,Opcode.mobaixuanshang)
		_G.setWorldDataX(WorldProp.mobai_money_count, cnt*2)
		_G.saveWorldData(WorldProp.mobai_money_count)
		return Error.Success
	end,
	[3] = function(entity)	--300元宝
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end

		local cnt = 300
		if entity:getGold()<cnt then
			return Error.NotEnoughGold
		end
		entity:useGold(cnt,Opcode.mobaixuanshang)
		_G.addWorldDataX(WorldProp.mobai_money_count, _G.getWorldDataX(WorldProp.mobai_money_count) + cnt*2)
		_G.saveWorldData(WorldProp.mobai_money_count)
		return Error.Success
	end,
	[4] = function(entity)	--400元宝
		local mgid = entity:getProps(EP.attr_guild_id)
		if mgid==0 then
			return Error.err_guild_noguild
		end
		local gpost = entity:getProps(EP.attr_guild_post)
		if gpost ~= GuildProp.post_master and gpost~=GuildProp.post_second_master then
			return Error.err_guild_NotMaster
		end
		local ngid =  _G.getWorldDataX(WP.city_master_guild)
		if ngid~=mgid then
			return Error.err_guild_NotCityMasterGuild
		end
		local cnt = 400
		if entity:getGold()<cnt then
			return Error.NotEnoughGold
		end
		entity:useGold(cnt,Opcode.mobaixuanshang)
		_G.addWorldDataX(WorldProp.mobai_money_count, cnt*2)
		_G.saveWorldData(WorldProp.mobai_money_count)
		return Error.Success
	end,
}

--
--	行会美女护送 	hhmnhs
--
-- 土城亲王
gdNPCExtension[1771] =
{
	[1] = function(entity)
		return  Event.HangHuiMeiNvHuSongStart(entity,false)
	end,
	[2] = function(entity)
		return  Event.HangHuiMeiNvHuSongStart(entity,true)
	end,
}

--
-- 	沙城总管
--
gdNPCExtension[181] =
{
	[1] = function(entity)
		return Event.HangHuiMeiNvHuSongEnd(entity)
	end,
}

--
--	红名监狱 狱卒	hmjy yz
--
gdNPCExtension[153] =
{
	[1] = function(entity)
		if entity:getProps(EP.attr_pkvalue)>=100 then
			return Error.NotEnoughCondition
		end

		Scene.conveyentitytoAnywhere(entity, MapID.wc, 140, 135)
		return Error.Success
	end,

	-- 消耗金币变成白名
	-- 消耗金币数算法：（玩家当前PK值-99）* 10000
	-- [2] = function(entity)
		-- local pk_value_goal = 99
		-- local pk_value = entity:getProps(EP.attr_pkvalue)
		-- if pk_value <= pk_value_goal then
			-- return Error.NotEnoughCondition
		-- end

		-- local need_money = (pk_value - pk_value_goal) * 10000
		-- if need_money > entity:getMoney() then
			-- return Error.NotEnoughMoney
		-- end

		-- entity:useMoney(need_money, Opcode.ClearRedName)
		-- entity:setProps(EP.attr_pkvalue, pk_value_goal)
		-- entity:syncProps(EP.attr_pkvalue)
		-- return Error.Success
	-- end,

	-- 消耗元宝变成白名
	-- 消耗元宝算法：（玩家当前PK值-99）* 0.5
	-- [3] = function(entity)
		-- local pk_value_goal = 99
		-- local pk_value = entity:getProps(EP.attr_pkvalue)
		-- if pk_value <= pk_value_goal then
			-- return Error.NotEnoughCondition
		-- end

		-- local need_gold = (pk_value - pk_value_goal) * 0.5
		-- if need_gold > math.modf(need_gold) then
			-- need_gold = math.modf(need_gold) + 1
		-- end

		-- if need_gold > entity:getGold() then
			-- return Error.NotEnoughGold
		-- end

		-- entity:useGold(need_gold, Opcode.ClearRedName)
		-- entity:setProps(EP.attr_pkvalue, pk_value_goal)
		-- entity:syncProps(EP.attr_pkvalue)
		-- return Error.Success
	-- end,

	-- VIP免费变为白名
	-- [4] = function(entity)
		-- local pk_value_goal = 99
		-- local pk_value = entity:getProps(EP.attr_pkvalue)
		-- if pk_value <= pk_value_goal then
			-- return Error.NotEnoughCondition
		-- end
		-- local err = Vip.useClearRedName(entity)
		-- if err~=Error.Success then
			-- return err
		-- end
		-- entity:setProps(EP.attr_pkvalue, pk_value_goal)
		-- entity:syncProps(EP.attr_pkvalue)
		-- return Error.Success
	-- end,
}

--
-- 	沙城总管
--
gdNPCExtension[181] =
{
	[1] = function(entity)
		return Event.HangHuiMeiNvHuSongEnd(entity)
	end,
}

--
-- 	护国将军
--
gdNPCExtension[2082] =
{
	[1] = function(entity)
		entity:jumpToCrossServer()
		return Error.Success
	end,
}
gdNPCExtension[150] = {--天机老人
	[1] = function(entity)
	if Vip.getVipLevel(entity) < 10 then
			return Error.NotEnoughVipLevel
		end
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		if scene:getProps(SP.syld_longwang_summon)>3 then
			return Error.AlreadyUsed
		end
		local used = entity:getEventDataX(EID.chdd)
			if used<3 then   --只能召唤三次
           -- 添加物品
            local embag  = entity:getBagEmptyCnt()
            if (embag < 1) then
                return Error.Item_BagisFull
            end
			entity:setEventDataX(EID.chdd, used+1)
			entity:saveEventData(EID.chdd)
		scene:setProps(SP.syld_longwang_summon, 1)
		math.randomseed(os.time())
            local n = math.random(100)
            if n then
                if n <=33 then
                   scene:addM(5403, 61, 75)
			_G.syncFloatMessage(entity:getName() .. "在土城61, 75召唤出世界BOSS地狱男爵")
                elseif n > 33 and n <= 53 then
                    scene:addM(5403, 61, 75)
			_G.syncFloatMessage(entity:getName() .. "在土城61, 75召唤出世界BOSS地狱男爵")
                elseif n > 53 and n <= 60 then
                    scene:addM(5403, 61, 75)
			_G.syncFloatMessage(entity:getName() .. "在土城61, 75召唤出世界BOSS地狱男爵")
                elseif n > 60 and n <= 70 then
                    scene:addM(5403, 61, 75)
			_G.syncFloatMessage(entity:getName() .. "在土城61, 75召唤出世界BOSS地狱男爵")
                elseif n > 70 and n <= 100 then
                    scene:addM(5403, 61, 75)
			_G.syncFloatMessage(entity:getName() .. "在土城61, 75召唤出世界BOSS地狱男爵")
                end
            end

			return Error.Success
		else
			return Error.TooManyTimes
		end
	end,
	
	 [2] = function(entity)
		-- 检查是否已是天机职业
		if entity:getStaticID() == 4 then
			return Error.AlreadyUsed
		end
		-- 检查转生等级是否达到80转
		local reborn = entity:getProps(EntityProp.attr_reborn)
		if reborn < 80 then
			return Error.NotEnoughRebornLevel
		end
		-- 执行转职：改为天机(职业4)
		entity:setStaticID(4)
		entity:setClass(4)
		-- 设置转生等级为26(凝气1)
		entity:setProps(EntityProp.attr_reborn, 26)
		entity:syncProps(EntityProp.attr_reborn)
		entity:saveProps(EntityProp.attr_reborn)
		-- 重新加载属性
		Entity.onLoadP(entity)
		_G.syncFloatMessage(entity:getName() .. "成功转职为天机！转生等级重置为凝气1重")
		return Error.Success
	end,
	[3] = dituBOSS,
}
gdNPCExtension[1150] = {----------------pk场
	
  [1] = function(entity)
		-- 检查是否在美女护送
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		
		-- 检查仙玉
		if entity:getCoupon()>=1000 then       
			entity:useCoupon(1000,Opcode.buy_rose)
			Scene.conveyentitytoAnywhere(entity, MapID.pkc)
			--Scene.conveyentitytoscene(entity, MapID.pkc)
			return Error.Success
		else

			return Error.NotEnoughCoupon
		end
	end,
	
}
--------------------------------------暗夜城------------------------------------------
gdNPCExtension[5200] =
{
	[1] = function(entity)--进入
		-- 转生等级限制：需要25转或以上             将军凌
		if entity:getProps(EP.attr_reborn) < 25 then
			return Error.NotEnoughRebornLevel
		end
		-- 检查灵力
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 10 then
			return Error.NotEnoughLingli
		end
		-- 消耗灵力
		local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
		entity:setProps(EP.attr_lingliqeitem, lingli - 10)
		entity:syncProps(EP.attr_lingliqeitem)
		entity:saveProps(EP.attr_lingliqeitem)
		
		
		-- 传送地图
		return Scene.conveyentitytoAnywhere(entity, MapID.jjl)
	end,
	[2] = function(entity)--进入
		-- 转生等级限制：需要25转或以上                将军陵
		if entity:getProps(EP.attr_reborn) < 25 then
			return Error.NotEnoughRebornLevel
		end
		-- 检查仙玉
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 10 then
			return Error.NotEnoughLingli
		end
		-- 消耗灵力
		local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
		entity:setProps(EP.attr_lingliqeitem, lingli - 10)
		entity:syncProps(EP.attr_lingliqeitem)
		entity:saveProps(EP.attr_lingliqeitem)
		
		-- 传送地图
		return Scene.conveyentitytoAnywhere(entity, MapID.jjl2)
	end,
	[3] = function(entity)--进入
		-- 转生等级限制：需要25转或以上                暗夜殿
		if entity:getProps(EP.attr_reborn) < 25 then
			return Error.NotEnoughRebornLevel
		end
		-- 检查灵力
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 50 then
			return Error.NotEnoughLingli
		end
		-- 消耗灵力
		local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
		entity:setProps(EP.attr_lingliqeitem, lingli - 50)
		entity:syncProps(EP.attr_lingliqeitem)
		entity:saveProps(EP.attr_lingliqeitem)
		
		-- 传送地图
		return Scene.conveyentitytoAnywhere(entity, MapID.ayd)
	end,
	[4] = function(entity)--进入
		-- 转生等级限制：需要25转或以上                冰与火
		if entity:getProps(EP.attr_reborn) < 25 then
			return Error.NotEnoughRebornLevel
		end
		-- 检查灵力
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 500 then
			return Error.NotEnoughLingli
		end
		-- 消耗灵力
		local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
		entity:setProps(EP.attr_lingliqeitem, lingli - 500)
		entity:syncProps(EP.attr_lingliqeitem)
		entity:saveProps(EP.attr_lingliqeitem)
		
		-- 传送地图
		return Scene.conveyentitytoAnywhere(entity, MapID.byh)
	end,
	[5] = function(entity)--进入
		-- 转生等级限制：需要25转或以上                古陵玄宫
		if entity:getProps(EP.attr_reborn) < 35 then
			return Error.NotEnoughRebornLevel
		end
		-- 检查灵力
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 1000 then
			return Error.NotEnoughLingli
		end
		-- 消耗灵力
		local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
		entity:setProps(EP.attr_lingliqeitem, lingli - 1000)
		entity:syncProps(EP.attr_lingliqeitem)
		entity:saveProps(EP.attr_lingliqeitem)
		
		-- 传送地图
		return Scene.conveyentitytoAnywhere(entity, MapID.glxg)
	end,
	[6] = function(entity)--进入
		-- 转生等级限制：需要35转或以上                星界囚笼
		if entity:getProps(EP.attr_reborn) < 35 then
			return Error.NotEnoughRebornLevel
		end
		-- 检查灵力
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 2000 then
			return Error.NotEnoughLingli
		end
		-- 消耗灵力
		local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
		entity:setProps(EP.attr_lingliqeitem, lingli - 2000)
		entity:syncProps(EP.attr_lingliqeitem)
		entity:saveProps(EP.attr_lingliqeitem)
		
		-- 传送地图
		return Scene.conveyentitytoAnywhere(entity, MapID.xjql)
	end,
	[7] = function(entity)--进入
		-- 转生等级限制：需要35转或以上                幽光裂谷
		if entity:getProps(EP.attr_reborn) < 44 then
			return Error.NotEnoughRebornLevel
		end
		-- 检查灵力
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 3000 then
			return Error.NotEnoughLingli
		end
		-- 消耗灵力
		local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
		entity:setProps(EP.attr_lingliqeitem, lingli - 3000)
		entity:syncProps(EP.attr_lingliqeitem)
		entity:saveProps(EP.attr_lingliqeitem)
		
		-- 传送地图
		return Scene.conveyentitytoAnywhere(entity, MapID.yglg)
	end,
	
}
-- gdNPCExtension[5201] =
-- {
	-- [1] = function(entity)--刷新大师
		
		-- _G.GMKickPlayer(entity:getGlobalID())
 -- end	

-- }



----------------------------------------------副本----------------------------------------
gdNPCExtension[52021] =   --四季轮回镜
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.sjlhj) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.sjlhj)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.sjlhj)
	end,
	[3] = summonTeam,
	
}
gdNPCExtension[52022] =   --五行试炼阵
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.wxslz) then
			return Error.NotEnoughLevel
		end
		return enterInstanceTeam(entity, MapID.wxslz)
	end,
	[2] = function(entity)
		return rescuitTeam(entity,MapID.wxslz)
	end,
	[3] = summonTeam,
	
}

---------------------------------------------------------------------------------------
gdNPCExtension[52051] =
{   [1] = function (entity)	--进入无尽的深渊
		if isProtectGirl(entity) then
			return Error.Meinvhusong_is_begin
		end
		if not meetRequiredLvlEID(entity, EID.wjdsy) then
			return Error.NotEnoughLevel
		end
		if entity:getEventDataX(EID.wjdsy) >= 5000000 * 4 then
			return Error.TooManyTimes
		end
		
		-- 检查灵力
		if (entity:getProps(EP.attr_lingliqeitem) or 0) < 50000 then
			return Error.NotEnoughLingli
		end
		
		if entity:getProps(EP.attr_team_id) == 0 then
			-- 单人进入，先消耗灵力
			local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
			entity:setProps(EP.attr_lingliqeitem, lingli - 50000)
			entity:syncProps(EP.attr_lingliqeitem)
			entity:saveProps(EP.attr_lingliqeitem)
			
			Scene.conveyTeamtoNewInstance(entity, MapID.wjdsy)
		else
			local sceneself = entity:getScene()
			local sceneid = 0
			if sceneself then
				sceneid = sceneself:getID()
			end
			
			-- 队伍进入，队长消耗灵力
			local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
			entity:setProps(EP.attr_lingliqeitem, lingli - 50000)
			entity:syncProps(EP.attr_lingliqeitem)
			entity:saveProps(EP.attr_lingliqeitem)
			
			entity:forEachTeamMember(function(entity)
				local entityscene = entity:getScene()
				if entityscene and sceneid == entityscene:getID() then
					Scene.conveyTeamtoNewInstance(entity, MapID.wjdsy)
				end
			end)
		end
		
		return Error.Success
	end,
    
    [2] = function(entity) --招募队友
		return rescuitTeam(entity, MapID.wjdsy)
	end,
    
	[3] = summonTeam, --队伍集结
}	
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
gdNPCExtension[52052] =
{
	-- 功能1：进入情侣副本（望月岛）
	[1] = function(entity)
		local ok, rtv = pcall(function()

			-- 检查是否处于护送美女状态，如果是则拒绝进入
			if isProtectGirl(entity) then
				return Error.Meinvhusong_is_begin
			end

			-- 检查副本所需任务/事件ID配置是否存在
			if not EID or not EID.qlwyd then
				return Error.InvalidStaticData
			end
			-- 检查玩家等级是否满足副本要求
			if not meetRequiredLvlEID(entity, EID.qlwyd) then
				return Error.NotEnoughLevel
			end

			-- 获取玩家队伍ID，检查是否在队伍中
			local team_id = entity:getProps(EP.attr_team_id)
			if not team_id or team_id == 0 then
				return Error.Must_In_Team
			end

			-- 检查是否有伴侣系统API
			if not entity.getPartnerPid then
				return Error.Script
			end
			-- 获取玩家的伴侣PID和自己的GID
			local myPartnerPid = entity:getPartnerPid()
			local myGid = entity:getGlobalID()
			if not myPartnerPid or myPartnerPid == 0 then
				return Error.Not_Couple
			end

			-- 遍历队伍成员，统计人数并记录队友信息
			local memberCount = 0
			local otherGid = 0
			local otherEntity = nil
			entity:forEachTeamMember(function(member)
				memberCount = memberCount + 1
				local mgid = member:getGlobalID()
				if mgid ~= myGid then
					otherGid = mgid
					otherEntity = member
				end
			end)

			-- 队伍必须恰好两人
			if memberCount ~= 2 then
				return Error.Couple_Dungeon_Need_Two
			end

			-- 正向校验：队友必须是自己的伴侣
			if otherGid ~= myPartnerPid then
				return Error.Not_Your_Couple
			end

			-- 安全检查
			if not otherEntity then
				return Error.Not_Your_Couple
			end
			-- 反向校验：自己的GID也必须是队友的伴侣
			local reversePartner = otherEntity:getPartnerPid()
			if reversePartner ~= myGid then
				return Error.Not_Your_Couple
			end

			-- 检查目标副本地图ID配置是否存在
			if not MapID or not MapID.qlwyd then
				return Error.InvalidStaticData
			end

			-- 检查所有队员是否在线（通过getScene判断）
			local allOnline = true
			entity:forEachTeamMember(function(member)
				local memberScene = member:getScene()
				if not memberScene then
					allOnline = false
				end
			end)
			if not allOnline then
				return Error.Player_is_OffLine
			end

			-- 次数限制：每人每日最多进入2次情侣望月岛副本，防止无限刷
			local qlwyd_evtid = getMapEventID(MapID.qlwyd)
			if qlwyd_evtid == 0 then
				return Error.InvalidStaticData
			end
			local max_times = 2
			local tooMany = false
			entity:forEachTeamMember(function(member)
				local used = member:getEventDataY(qlwyd_evtid) or 0
				if used >= max_times then
					tooMany = true
				end
			end)
			if tooMany then
				return Error.AlreadyUsed
			end

			-- 扣除次数并传送
			entity:forEachTeamMember(function(member)
				member:addEventDataY(qlwyd_evtid, 1)
				Scene.conveyTeamtoNewInstance(member, MapID.qlwyd)
			end)
			return Error.Success
		end)

		-- Lua脚本异常捕获
		if not ok then
			return Error.Script
		end
		return rtv
	end,

	-- 功能2：拉取队友到情缘问道副本（队长召集）
	[2] = function(entity)
		return rescuitTeam(entity, MapID.qlwyd)
	end,

	-- 功能3：召唤队友到自己身边（队员归队）
	[3] = function(entity)
		return summonTeam(entity)
	end,
}



















--------------------------------------------------------------------------------
--------------------------------------------------------------------------------












-- 批量范围检查与合成函数
local dksr_merge_range = function(entity, srcRange, cnt, lingliNeed, tgt)
    -- srcRange 可以是以下几种格式：
    -- 1. 单个物品ID: 10133
    -- 2. 范围字符串: "10133-10139" (包含两端)
    -- 3. 数组: {10133, 10134, 10135, 10136, 10137, 10138, 10139}
    
    -- 1. 检查灵力
    if (entity:getProps(EP.attr_lingliqeitem) or 0) < lingliNeed then
        return Error.NotEnoughLingli
    end
    
    -- 2. 解析物品范围
    local items = {}
    if type(srcRange) == "number" then
        -- 单个物品
        table.insert(items, srcRange)
    elseif type(srcRange) == "string" and string.find(srcRange, "-") then
        -- 范围字符串 "10133-10139"
        local startID, endID = string.match(srcRange, "(%d+)-(%d+)")
        startID = tonumber(startID)
        endID = tonumber(endID)
        if startID and endID and startID <= endID then
            for id = startID, endID do
                table.insert(items, id)
            end
        else
            return Error.InvalidRange
        end
    elseif type(srcRange) == "table" then
        -- 数组格式
        items = srcRange
    else
        return Error.InvalidParam
    end
    
    -- 3. 检查是否有足够的任意一个物品
    local foundItem = nil
    local foundCount = 0
    
    for _, itemID in ipairs(items) do
        if entity:hasItem(itemID, cnt) then
            foundItem = itemID
            foundCount = entity:getItemCount(itemID)
            break
        end
    end
    
    if not foundItem then
        return Error.NotEnoughItem
    end
    
    -- 4. 执行合成
    entity:rmvItem(foundItem, cnt)
    
    -- 扣除灵力 - 使用游戏中的标准方式
    local lingli = entity:getProps(EP.attr_lingliqeitem) or 0
    entity:setProps(EP.attr_lingliqeitem, lingli - lingliNeed)
    entity:syncProps(EP.attr_lingliqeitem)
    entity:saveProps(EP.attr_lingliqeitem)
    
    -- 记录操作
    entity:useMoney(0, Opcode.BundlingItem, tgt)
    
    entity:addBindItem(tgt, 1)
    
    return Error.Success, foundItem
end

gdNPCExtension[52061] = {
    [1] = function(entity)    -- 10133-10139任意一个，12个合成51118
        return dksr_merge_range(entity, "10133-10139", 12, 10000, 51118)
    end
}




gdNPCExtension[5207] =                       ------------渡劫副本
{
	[1] = function(entity)
		if not meetRequiredLvlEID(entity, EID.djfb) then
			return Error.NotEnoughLevel
		end
		return enterInstanceSelf(entity, MapID.djfb)
	end,
	
}



local sbrh_merge_with_mat = function(entity, srcsid, rebornlvl, matsid, cnt, tgtsid_warrior, tgtsid_mage, tgtsid_taoist, tgtrebornlvl)
	local money = 100000
	if entity:getMoney()<money then
		return Error.NotEnoughMoney
	end

	tgtrebornlvl = tgtrebornlvl or 0
	if entity:getProps(EP.attr_reborn)<tgtrebornlvl then
		return Error.NotEnoughLevel
	end

	if not entity:hasItem(matsid, cnt) then
		return Error.NotEnoughItem
	end

	-- 查找玩家装备了哪个源装备
	local foundItem = nil
	local foundSid = nil
	local targetSid = nil
	
	if type(srcsid)=="table" then
		for _, v in pairs(srcsid) do
			local item = sbrh_getEquipedItem(entity, v)
			if item then
				foundItem = item
				foundSid = v
				break
			end
		end
	else
		foundItem = sbrh_getEquipedItem(entity, srcsid)
		foundSid = srcsid
	end

	if not foundItem then
		return Error.PlayerHasNotEquipThisItem
	end

	if foundItem:getProps(IP.Item_RebornLvl)<rebornlvl then
		return Error.PlayerHasNotEquipThisItem
	end
	
	-- 判断目标装备ID（根据源装备映射）
	-- 这里需要你知道装备ID与职业的对应关系
	-- 假设：srcsid[1]=战士, srcsid[2]=法师, srcsid[3]=道士
	if type(srcsid) == "table" then
		-- 方法1：通过索引判断
		if foundSid == srcsid[1] then
			targetSid = tgtsid_warrior
		elseif foundSid == srcsid[2] then
			targetSid = tgtsid_mage
		elseif foundSid == srcsid[3] then
			targetSid = tgtsid_taoist
		end
	else
		-- 如果srcsid不是table，使用默认映射
		-- 这里需要你定义默认规则
		targetSid = tgtsid_warrior or tgtsid
	end
	
	-- 如果没有找到对应的目标装备，返回错误
	if not targetSid then
		return Error.InvalidTargetItem
	end

	local ec = entity:addItem(targetSid, 1)
	if ec==Error.Success then
		local itemattr = {}
		for idx = 1, IP.Item_Max do
			itemattr[idx] = foundItem:getProps(idx)
		end
		itemattr[IP.Item_RebornLvl] = tgtrebornlvl or 0

		entity:useMoney(money,Opcode.Op_Item_Merge,targetSid)
		Item.onPutOff(entity, foundItem)
		entity:rmvItemExactly(foundItem:getIID())
		entity:rmvItem(matsid, cnt)

		local nitem = entity:getItemLastAdd()
		if nitem then
			for idx = 1, IP.Item_Max do
				if itemattr[idx] and itemattr[idx]~=0 then
					nitem:setProps(idx, itemattr[idx])
					entity:saveItemProps(nitem,idx)
					entity:syncItemProps(nitem,idx)
				end
			end
		end
	end
	entity:syncPlayerCombatCombo()
	return ec
end







gdNPCExtension[52062] =
{
    -- 装备对应关系注释：
    -- 源装备索引1: 战士(20530) -> 目标战士装备(20640)
    -- 源装备索引2: 法师(20540) -> 目标法师装备(20670) 
    -- 源装备索引3: 道士(20550) -> 目标道士装备(20660)
    
    [1] = function(entity)return sbrh_merge_with_mat(entity,{20530,20540,20550},5,41004,50,20640,20670,20660,0)end,
    [2] = function(entity)return sbrh_merge_with_mat(entity,{20531,20541,20551},5,41004,50,20641,20671,20661,0)end,
    [3] = function(entity)return sbrh_merge_with_mat(entity,{20532,20542,20552},5,41004,50,20642,20672,20662,0)end,
    [4] = function(entity)return sbrh_merge_with_mat(entity,{20533,20543,20553},5,41004,50,20643,20673,20663,0)end,
    [5] = function(entity)return sbrh_merge_with_mat(entity,{20534,20544,20554},5,41004,50,20644,20674,20664,0)end,
    [6] = function(entity)return sbrh_merge_with_mat(entity,{20535,20545,20555},5,41004,50,20645,20675,20665,0)end,
    [7] = function(entity)return sbrh_merge_with_mat(entity,{20536,20546,20556},5,41004,50,20646,20676,20666,0)end,
    [8] = function(entity)return sbrh_merge_with_mat(entity,{20537,20547,20557},5,41004,50,20647,20677,20667,0)end,
    [9] = function(entity)return sbrh_merge_with_mat(entity,{20538,20548,20558},5,41004,50,20648,20678,20668,0)end,
}




--
--	情侣专属副本测试	NPC=52051  副本=qlwyd  带print调试
--
gdNPCExtension[88888888] =
{
	[1] = function(entity)
		local ok, rtv = pcall(function()
			print("[QZFB] ====== 进入情侣副本NPC 52051 ======")
			print("[QZFB] 玩家: "..tostring(entity:getName()).."  gid="..tostring(entity:getGlobalID()))

			if isProtectGirl(entity) then
				print("[QZFB] 护送美女中，返回 Meinvhusong_is_begin="..tostring(Error.Meinvhusong_is_begin))
				return Error.Meinvhusong_is_begin
			end
			print("[QZFB] 护送美女检查 通过")

			if not EID or not EID.qlwyd then
				print("[QZFB] EID.qlwyd = nil !!!! 检查EID配置")
				return Error.InvalidStaticData
			end
			if not meetRequiredLvlEID(entity, EID.qlwyd) then
				print("[QZFB] 等级不足，返回 NotEnoughLevel="..tostring(Error.NotEnoughLevel))
				return Error.NotEnoughLevel
			end
			print("[QZFB] 等级检查 通过 EID.qlwyd="..tostring(EID.qlwyd))

			local team_id = entity:getProps(EP.attr_team_id)
			print("[QZFB] 队伍ID attr_team_id="..tostring(team_id))
			if not team_id or team_id == 0 then
				print("[QZFB] 无队伍，返回 Must_In_Team="..tostring(Error.Must_In_Team))
				return Error.Must_In_Team
			end

			if not entity.getPartnerPid then
				print("[QZFB] entity.getPartnerPid 方法不存在！！C++没编译或没注册！")
				return Error.Script
			end
			local myPartnerPid = entity:getPartnerPid()
			local myGid = entity:getGlobalID()
			print("[QZFB] 玩家gid="..myGid.."  伴侣pid="..tostring(myPartnerPid))
			if not myPartnerPid or myPartnerPid == 0 then
				print("[QZFB] 没有伴侣，返回 Not_Couple="..tostring(Error.Not_Couple))
				return Error.Not_Couple
			end

			local memberCount = 0
			local otherGid = 0
			local otherEntity = nil
			entity:forEachTeamMember(function(member)
				memberCount = memberCount + 1
				local mgid = member:getGlobalID()
				print("[QZFB]   队员["..memberCount.."]: gid="..mgid.."  name="..tostring(member:getName()))
				if mgid ~= myGid then
					otherGid = mgid
					otherEntity = member
				end
			end)
			print("[QZFB] 队伍总人数="..memberCount.."  队友gid="..tostring(otherGid))

			if memberCount ~= 2 then
				print("[QZFB] 人数不是2，返回 Couple_Dungeon_Need_Two="..tostring(Error.Couple_Dungeon_Need_Two))
				return Error.Couple_Dungeon_Need_Two
			end

			if otherGid ~= myPartnerPid then
				print("[QZFB] 队友不是伴侣! 队友gid="..otherGid.."  伴侣pid="..myPartnerPid.."  返回 Not_Your_Couple="..tostring(Error.Not_Your_Couple))
				return Error.Not_Your_Couple
			end
			print("[QZFB] 队友是自己的伴侣(正向) 通过")

			if not otherEntity then
				print("[QZFB] otherEntity 为空，异常")
				return Error.Not_Your_Couple
			end
			local reversePartner = otherEntity:getPartnerPid()
			print("[QZFB] 队友的伴侣pid="..tostring(reversePartner).."  自己gid="..myGid)
			if reversePartner ~= myGid then
				print("[QZFB] 双向校验失败! 队友的伴侣="..reversePartner.." != 自己gid="..myGid)
				return Error.Not_Your_Couple
			end
			print("[QZFB] 双向校验 通过")

			if not MapID or not MapID.qlwyd then
				print("[QZFB] MapID.qlwyd = nil !!!! 检查MapID配置")
				return Error.InvalidStaticData
			end
			print("[QZFB] MapID.qlwyd="..tostring(MapID.qlwyd))

			local sceneself = entity:getScene()
			local sceneid = 0
			if sceneself then
				sceneid = sceneself:getID()
			end
			-- 先检查所有队员是否都在线（getScene()不为nil）
			local allOnline = true
			entity:forEachTeamMember(function(member)
				local memberScene = member:getScene()
				local mgid = member:getGlobalID()
				if not memberScene then
					print("[QZFB]   队员 gid="..mgid.." getScene()=nil  离线!")
					allOnline = false
				else
					print("[QZFB]   队员 gid="..mgid.." 场景ID="..memberScene:getID().." 在线")
				end
			end)
			if not allOnline then
				print("[QZFB] 有队员离线，返回 Player_is_OffLine="..tostring(Error.Player_is_OffLine))
				return Error.Player_is_OffLine
			end
			-- 全部在线，开始传送（允许跨场景）
			print("[QZFB] 全部在线，开始遍历传送队员(允许跨场景)")
			entity:forEachTeamMember(function(member)
				local memberScene = member:getScene()
				local mgid = member:getGlobalID()
				local msceneid = memberScene:getID()
				print("[QZFB]   队员 gid="..mgid.."  场景ID="..msceneid)
				local ctv = Scene.conveyTeamtoNewInstance(member, MapID.qlwyd)
				print("[QZFB]   队员 gid="..mgid.."  传送返回 ctv="..tostring(ctv).."  Success="..tostring(Error.Success))
			end)
			print("[QZFB] ====== 执行完毕返回 Success ======")
			return Error.Success
		end)

		if not ok then
			print("[QZFB] LUA异常: "..tostring(rtv))
			return Error.Script
		end
		return rtv
	end,
	[2] = function(entity)
		print("[QZFB] 功能2 rescuitTeam qlwyd")
		return rescuitTeam(entity, MapID.qlwyd)
	end,
	[3] = function(entity)
		print("[QZFB] 功能3 summonTeam")
		return summonTeam(entity)
	end,
}
