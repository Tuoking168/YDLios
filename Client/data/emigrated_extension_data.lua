if not gdEmigratedExtension then
	gdEmigratedExtension = {}
end

local EP = EntityProp
local SP = SceneProp
local WP = WorldProp

local function doAddItemByTable(entity, itable, count)
	count = count or 1
	--print("doAddItmeByTable", count)

	local omap = {}
	local type_cnt = 0

	for i = 1, count do
		local id = itable[math.random(table.getn(itable))]
		if id then
			if omap[id] then
				omap[id] = omap[id] + 1
			else
				omap[id] = 1
				type_cnt = type_cnt + 1
			end
		end
	end

	--print("doAddItmeByTable, Type", type_cnt)

	if entity:getBagEmptyCnt()<type_cnt then
		return Error.Item_BagisFull
	end

	for id, cnt in pairs(omap) do
		--print("doAddItmeByTable, Add", id, cnt)
		if id>0 and cnt > 0 then
			entity:addItem(id, cnt)
		end
	end

	return Error.Success
end

gdEmigratedExtension[1] = {
	[1] = function (entity)--领取经验任务
		entity:addQuest(6, 999)
		return Error.Success
	end
}

gdEmigratedExtension[2] = {
	[1] = function (entity)--金币
		local mon = math.random(1000) + 1000
		entity:addMoney(mon)
		return Error.Success
	end,

	[2] = function(entity)--朱雀神翎*1
		entity:addItem(40077, 1)
		return Error.Success
	end,
	[3] = function(entity)--囧神（特殊头衔）
		entity:addItem(30294, 1)
		return Error.Success
	end,
	[4] = function(entity)--金条*1
		entity:addItem(30060, 1)
		return Error.Success
	end
}

gdEmigratedExtension[3] = {
	[1] = function (entity)--双倍经验BUFF：打怪经验增加100%（30分钟）
		--entity:addItem(38000, 1)
		return Error.Success
	end,
	[2] = function(entity)--强健体魄BUFF:生命上限增加10%（10分钟）
		--entity:addItem(38001, 1)
		return Error.Success
	end,
	[3] = function(entity)--清晰思维BUFF：魔法上限增加10%（10分钟）
		--entity:addItem(38001, 1)
		return Error.Success
	end,
	[4] = function(entity)--精神力战法BUFF：最大魔法防御增加100（10分钟）
		--entity:addItem(38001, 1)
		return Error.Success
	end,
	[5] = function(entity)--神圣战甲术BUFF：最大物理防御增加100（10分钟）
		--entity:addItem(38001, 1)
		return Error.Success
	end,
	[6] = function(entity)--仙女卡*20
		--entity:addItem(30246, 1)
		entity:addGene(39075)
		return Error.Success
	end,
	[7] = function(entity)--斗士卡*20
		--entity:addItem(30247, 1)
		entity:addGene(39076)
		return Error.Success
	end,

}

gdEmigratedExtension[4] = {
	[1] = function (entity)--礼券68
		entity:addCoupon(68)
		return Error.Success
	end,
	[2] = function(entity)--仙玉388
		entity:addCoupon(388)
		return Error.Success
	end,
	[3] = function(entity)--仙玉688
		entity:addCoupon(688)
		return Error.Success
	end,
	[4] = function(entity)--仙玉1688
		entity:addCoupon(1688)
		return Error.Success
	end,
	[5] = function(entity)--金币38888
		entity:addMoney(38888)
		return Error.Success
	end,
	[6] = function(entity)--金币88888
		entity:addMoney(88888)
		return Error.Success
	end,
	[7] = function(entity)--金币888888
		entity:addMoney(888888)
		return Error.Success
	end,
	[8] = function(entity)--金币8888888
		entity:addMoney(8888888)
		return Error.Success
	end,
	[9] = function(entity)--荣誉3888
		entity:addHonor(3888)
		return Error.Success
	end,
	[10] = function(entity)--荣誉6888
		entity:addHonor(6888)
		return Error.Success
	end,
	[11] = function(entity)--荣誉8888
		entity:addHonor(8888)
		return Error.Success
	end,
	[12] = function(entity)--荣誉88888
		entity:addHonor(88888)
		return Error.Success
	end
}

gdEmigratedExtension[5] = {
	[1] = function (entity)--进行战斗
		--随机一个 rank  和 pid (rank 是entity的rank正负10)
		local selfrank = entity:getProps(EntityProp.attr_arena_rank)
		local pid = entity:getGlobalID()
		local rank = selfrank
		local startRank = selfrank-10
		if startRank<=0 then
			startRank = 1
		end
		local endRank = selfrank+10
		local allRank = _G.getArearankLength()
		if endRank>allRank then
			endRank = allRank
		end
		while pid==entity:getGlobalID() do
			rank = math.random(startRank,endRank)
			pid = _G.getArearankPid(rank)
		end

		if pid == 0 then
			pid = entity:getGlobalID()
		end
		entity:sendFuncMsg(FuncProp.CaiShenLanLu,pid,-rank)
		return Error.Success
	end
}

gdEmigratedExtension[6] = {
	[1] = function (entity)--1级灵珠*1
		entity:addItem(40000, 1)
		return Error.Success
	end,
	[2] = function(entity)--红玫瑰*1
		entity:addItem(39029, 1)
		return Error.Success
	end,
	[3] = function(entity)--高级怒气丹*1             游戏中没有这个道具 换成 攻击药水（中）
		entity:addItem(39024, 1)
		return Error.Success
	end,
	[4] = function(entity)--黄金雷锤碎片*1
		entity:addItem(30288, 1)
		return Error.Success
	end,
	[5] = function(entity)--如意金箍棒碎片*1
		entity:addItem(30289, 1)
		return Error.Success
	end,
	[6] = function(entity)--死神之镰碎片*1
		entity:addItem(30290, 1)
		return Error.Success
	end,
	[7] = function(entity)--生花妙笔碎片*1
		entity:addItem(30291, 1)
		return Error.Success
	end,
	[8] = function(entity)--黄金雷锤*1
		entity:addItem(82000, 1)
		return Error.Success
	end,
	[9] = function(entity)--雪莲王*1
		entity:addItem(39022, 1)
		return Error.Success
	end,
	[10] = function(entity)--人参王*1
		entity:addItem(39018, 1)
		return Error.Success
	end,
	[11] = function(entity)--随机3级魂石*1
		return doAddItemByTable(entity, {10021,10022, 10023, 10024, 10025,10026,10027})
	end,
	[12] = function(entity)--随机4级魂石*1
		return doAddItemByTable(entity, {10028,10029, 10030, 10031, 10032,10033,10034})
	end,
	[13] = function(entity)--随机5级魂石*1
		return doAddItemByTable(entity, {10035,10036,10037, 10038, 10039,10040,10041})
	end,
}


gdEmigratedExtension[7] = {
	[1] = function (entity)--前进1格
		Event.walkstep(entity,1)
		return Error.Success
	end,
	[2] = function(entity)--前进2格
		Event.walkstep(entity,2)
		return Error.Success
	end,
	[3] = function(entity)--前进3格
		Event.walkstep(entity,3)
		return Error.Success
	end,
	[4] = function(entity)--前进4格
		Event.walkstep(entity,4)
		return Error.Success
	end,
	[5] = function(entity)--前进5格
		Event.walkstep(entity,5)
		return Error.Success
	end
}

gdEmigratedExtension[8] = {
	[1] = function (entity)--后退1格
		Event.walkstep(entity,-1)
		return Error.Success
	end,
	[2] = function(entity)--后退2格
		Event.walkstep(entity,-2)
		return Error.Success
	end,
	[3] = function(entity)--后退3格
		Event.walkstep(entity,-3)
		return Error.Success
	end,
	[4] = function(entity)--后退4格
		Event.walkstep(entity,-4)
		return Error.Success
	end,
	[5] = function(entity)--后退5格
		Event.walkstep(entity,-5)
		return Error.Success
	end
}

gdEmigratedExtension[9] = {
	[1] = function (entity)--重置本关所有随机事件
		Event.rollRandomSeed(entity)
		return Error.Success
	end
}

gdEmigratedExtension[10] = {
	[1] = function (entity)--最终奖励1
		Event.rollRandomSeed(entity)
		entity:addBindItem(39029, 2) --红玫瑰
		entity:addBindItem(40001, 2) --二级灵珠

		local roleexp = math.random(20000, 500000)+entity:getLevel()*1000
		entity:addExp(roleexp)
		return Error.Success
	end
}

gdEmigratedExtension[11] = {
	[1] = function (entity)--最终奖励2
		Event.rollRandomSeed(entity)
		entity:addBindItem(39029, 4) --红玫瑰
		entity:addBindItem(40001, 5) --二级灵珠

		local roleexp = math.random(45000, 1000000)+entity:getLevel()*1000
		entity:addExp(roleexp)
		return Error.Success
	end
}
gdEmigratedExtension[12] = {
	[1] = function (entity)--最终奖励3
		Event.rollRandomSeed(entity)
		entity:addBindItem(39029, 6) --红玫瑰
		entity:addBindItem(40001, 8) --二级灵珠

		local roleexp = math.random(70000, 3000000)+entity:getLevel()*1000
		entity:addExp(roleexp)
		return Error.Success
	end
}









