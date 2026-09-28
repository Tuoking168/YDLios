
if not gdEventExtension then
	gdEventExtension = {}
end

local EP = EntityProp
local SP = SceneProp
local WP = WorldProp
local EID = EID

if not gdfirePos then
	gdfirePos =
	{
		center = {x = 65, y = 87},
		exppos =
		{
			[1] = {x = 2,y = 2},
			[2] = {x = -2,y = -2},
			[3] = {x = 2,y = -2},
			[4] = {x = -2,y = 2},
			[5] = {x = 0,y = 2},
			[6] = {x = 0,y = -2},
			[7] = {x = 2,y = 0},
			[8] = {x = -2,y = 0},
		},
	}
end

--
--	土城抗魔	tckm
--
gdEventExtension[EID.tckm] = {
	onStart =  function(eventid,et)
		-- 获取场景
		local scene = gdScnMgr:getSceneBySid(MapID.tc)
		if not scene then
			sceneid = Scene.onCreate(MapID.tc)
			scene = gdScnMgr:getScene(sceneid)
		end
		-- 加入怪物组
		local entity = scene:addMG(1, 137, 117) --刷怪点
		if entity then
			-- 设置怪物组属性
			entity:setProps(EP.attr_mg_refresh_interval, 1000)  -- interval	刷新间隔
			entity:setProps(EP.attr_mg_refresh_range, 15)    -- 刷怪范围
			entity:setProps(EP.attr_mg_refresh_type, 1)		--- 刷新类型 0是普通刷新 1 代表怪物组内怪物全死亡后统一刷新
			entity:setProps(EP.attr_mg_monster_type_cnt, 1)  	--- 怪物种类数
			entity:setProps(EP.attr_mg_refresh_sid_begin, 19)    --- 怪物sid 从230 - 249 共20个
			entity:setProps(EP.attr_mg_refresh_limit_begin, 10)    -- 当前刷新模式（1）可以不填写上面的每次刷新数量
		else
			print("failed to add monster generators on Event Tu cheng Kang Mo!!")
		--	return false
		end

		local entity2 = scene:addMG(1, 137, 117) --刷怪点
		if entity2 then
			-- 设置怪物组属性
			entity2:setProps(EP.attr_mg_refresh_interval, 1000)  -- interval	刷新间隔
			entity2:setProps(EP.attr_mg_refresh_range, 15)    -- 刷怪范围
			entity2:setProps(EP.attr_mg_refresh_type, 1)		--- 刷新类型 0是普通刷新 1 代表怪物组内怪物全死亡后统一刷新
			entity2:setProps(EP.attr_mg_monster_type_cnt, 1)  	--- 怪物种类数

			entity2:setProps(EP.attr_mg_refresh_sid_begin, 20)
			entity2:setProps(EP.attr_mg_refresh_limit_begin, 6)

		else
			print("failed to add monster generators on Event Tu cheng Kang Mo!!")
		--	return false
		end

		local entity3 = scene:addMG(1, 137, 117) --刷怪点
		if entity3 then
			-- 设置怪物组属性
			entity3:setProps(EP.attr_mg_refresh_interval, 1000)  -- interval	刷新间隔
			entity3:setProps(EP.attr_mg_refresh_range, 15)    -- 刷怪范围
			entity3:setProps(EP.attr_mg_refresh_type, 1)		--- 刷新类型 0是普通刷新 1 代表怪物组内怪物全死亡后统一刷新
			entity3:setProps(EP.attr_mg_monster_type_cnt, 1)  	--- 怪物种类数
			entity3:setProps(EP.attr_mg_refresh_sid_begin, 21)
			entity3:setProps(EP.attr_mg_refresh_limit_begin, 3)
		else
			print("failed to add monster generators on Event Tu cheng Kang Mo!!")
		end
		--_G.syncFloatMessage("土城抗魔正式开始！")

		Event.setEventDataX(EID.tckm,entity:getID())
		Event.setEventDataY(EID.tckm,entity2:getID())
		Event.setEventDataZ(EID.tckm,entity3:getID())
		return true
	end,

	onStop = function(eventid)

		local mgid = Event.getEventDataX(EID.tckm)
		local mgid2 = Event.getEventDataY(EID.tckm)
		local mgid3 = Event.getEventDataZ(EID.tckm)
		local scene = gdScnMgr:getSceneBySid(MapID.tc)
		if scene then
			if mgid then
				scene:rmvEntity(mgid) -- 移除怪物组
			end
			if mgid2 then
				scene:rmvEntity(mgid2) -- 移除怪物组
			end
			if mgid3 then
				scene:rmvEntity(mgid3) -- 移除怪物组
			end
		end
		--_G.syncFloatMessage("土城抗魔结束！")

		return true
	end,
}
-- 篝火位置配置
gdfirePos = gdfirePos or {
    center = {x = 65, y = 87, id = 0},
    exppos = {
        {x = 2, y = 2, id = 0},
        {x = 0, y = 2, id = 0},
        {x = -2, y = 2, id = 0},
        {x = 2, y = 0, id = 0},
        {x = -2, y = 0, id = 0},
        {x = 2, y = -2, id = 0},
        {x = 0, y = -2, id = 0},
        {x = -2, y = -2, id = 0},
    }
}

-- VIP奖励组定义
local vipRewardGroups = {
    {minVip = 10, maxVip = 10, itemId = 30059, itemCount = 2, gold = 9999, pk = 200},
}

-- 亢金龙残影位置配置
local xrbossPositions = {
    {110, 112},
    {205, 205},
    {221, 151},
    {259, 107},
    {378, 128},
    {350, 190},
    {168, 294},
    {102, 288},
    {62, 232},
    {58, 180},
    {24, 146},
    {12, 114},
    {10, 58},
    {50, 20},
    {98, 7},
    {132, 10},
    {150, 42},
}

-- 给实体添加PK值的函数
local function addPkValue(entity, pkValue)
    if not entity or not entity.setProps then
        return false
    end
    
    local success, err = pcall(function()
        local currentPk = entity:getProps(EP.attr_pkvalue) or 0
        local newPk = currentPk + pkValue
        
        local setSuccess = entity:setProps(EP.attr_pkvalue, newPk)
        
        if setSuccess then
            entity:syncProps(EP.attr_pkvalue)
            return true
        else
            return false
        end
    end)
    
    if not success then
        return false
    end
    
    return err
end

-- VIP奖励处理函数
local function processVipRewards(scene)
    if not scene then
        return
    end
    
    local rewardCount = 0
    
    scene:forEachEntityP(function(entity)
        if not entity then
            return
        end
        
        local entityId = entity:getID()
        if not entityId or entityId == 0 then
            return
        end
        
        local posX, posY = entity:getPosition()
        local isAtFire = false
        
        if math.abs(posX - gdfirePos.center.x) < 0.1 and math.abs(posY - gdfirePos.center.y) < 0.1 then
            isAtFire = true
        end
        
        if not isAtFire then
            for _, v in ipairs(gdfirePos.exppos) do
                local targetX = gdfirePos.center.x + v.x
                local targetY = gdfirePos.center.y + v.y
                
                if math.abs(posX - targetX) < 0.1 and math.abs(posY - targetY) < 0.1 then
                    isAtFire = true
                    break
                end
            end
        end
        
        if isAtFire then
            local vipLevel = Vip.getVipLevel(entity)
            if vipLevel then
                for _, group in ipairs(vipRewardGroups) do
                    if vipLevel >= group.minVip and vipLevel <= group.maxVip then
                        local success1 = entity:addItem(group.itemId, group.itemCount)
                        local success2 = entity:addGold(group.gold)
                        local success3 = addPkValue(entity, group.pk)
                        
                        if success1 and success2 and success3 then
                            rewardCount = rewardCount + 1
                        end
                        break
                    end
                end
            end
        end
    end)
    
    return rewardCount
end

-- 篝火事件处理
gdEventExtension[EID.gh] = {
    onStart = function(eventid, et)
        local scene = gdScnMgr:getSceneBySid(MapID.tc)
        if not scene then
            local sceneid = Scene.onCreate(MapID.tc)
            scene = gdScnMgr:getScene(sceneid)
        end
        
        if not scene then
            return false
        end
        
        local ep = 1
        if et.otherdata and et.otherdata[1] then
            ep = et.otherdata[1]
        end
        
        for k, v in ipairs(gdfirePos.exppos) do
            if v.id and v.id ~= 0 then
                scene:rmvEntity(v.id)
                v.id = 0
                scene:rmvBlock(gdfirePos.center.x + v.x, gdfirePos.center.y + v.y, 16384)
            end
        end
        
        if gdfirePos.center.id and gdfirePos.center.id ~= 0 then
            scene:rmvEntity(gdfirePos.center.id)
            gdfirePos.center.id = 0
        end
        
        for k, v in ipairs(gdfirePos.exppos) do
            local targetX = gdfirePos.center.x + v.x
            local targetY = gdfirePos.center.y + v.y
            local entity = scene:addS(100, targetX, targetY)
            
            if entity then
                v.id = entity:getID()
                
                scene:addBlock(targetX, targetY, 16384)
                
                local stopTime = Event.getStopTime(eventid)
                if stopTime and et.starttime then
                    entity:setProps(EntityProp.attr_time_to_live, stopTime - et.starttime)
                end
                
                entity:setProps(EntityProp.attr_s_script_duration, 7)
                entity:setProps(EntityProp.attr_s_skill_ex_data, ep)
            end
        end
        
        local centerEntity = scene:addS(101, gdfirePos.center.x, gdfirePos.center.y)
        if centerEntity then
            gdfirePos.center.id = centerEntity:getID()
        end
        
        if not gdMapExtension[MapID.tc] then
            gdMapExtension[MapID.tc] = {}
        end
        
        if not gdMapExtension[MapID.tc].onTimerEvent then
            gdMapExtension[MapID.tc].onTimerEvent = {}
        end
        
        gdMapExtension[MapID.tc].onTimerEvent[2] = function(scene)
            processVipRewards(scene)
        end
        
        scene:addTimerEvent(2, 60000, -1)
        
        processVipRewards(scene)
        
        return true
    end,
    
    onStop = function(eventid)
        local scene = gdScnMgr:getSceneBySid(MapID.tc)
        if not scene then
            return
        end
        
        for k, v in ipairs(gdfirePos.exppos) do
            if v.id and v.id ~= 0 then
                scene:rmvEntity(v.id)
                v.id = 0
                scene:rmvBlock(gdfirePos.center.x + v.x, gdfirePos.center.y + v.y, 16384)
            end
        end
        
        if gdfirePos.center.id and gdfirePos.center.id ~= 0 then
            scene:rmvEntity(gdfirePos.center.id)
            gdfirePos.center.id = 0
        end
        
        if gdMapExtension[MapID.tc] and gdMapExtension[MapID.tc].onTimerEvent then
            gdMapExtension[MapID.tc].onTimerEvent[2] = nil
        end
        
        if scene then
            local count = 0
            scene:forEachEntityM(function(ettm)
                local ssid = ettm:getStaticID()
                if ssid == 5294 and ettm:isAlive() then
                    count = count + 1
                end
            end)
            
            if count >= 30 then
                _G.syncFloatMessage("还有" .. count .. "只亢金龙藏在土城野外， 大家快去寻找！")
            else
                _G.syncFloatMessage("亢金龙已在土城多个位置刷新，各位勇士速速前往消灭")
                
                local removedCount = 0
                scene:forEachEntityM(function(ettm)
                    local ssid = ettm:getStaticID()
                    if ssid == 5294 then
                        scene:rmvEntity(ettm:getID())
                        removedCount = removedCount + 1
                    end
                end)
                
                for i = 1, 30 do
                    local posIndex = math.random(1, 17)
                    local pos = xrbossPositions[posIndex]
                    if not pos then
                        pos = {150, 42}
                    end
                    
                    scene:addM(5294, pos[1], pos[2])
                end
                
                _G.syncFloatMessage("已刷新30只亢金龙，请前往击杀！")
            end
        end
        
        return true
    end
}















--
--	采花大盗	chdd
--
gdEventExtension[EID.chdd] = {
	onStart = function(eventid,et)
		log.info("*****************chdd****************************start")
		local scene = gdScnMgr:getSceneBySid(MapID.wc)
		if scene then
			--检测当前是否是否有怪,避免出现 空指针
			local x,y,z = Event.getEventData(EID.chdd)
			if  x and x ~= 0  then
				scene:rmvEntity(x)
			end
			if  y and y ~= 0 then
				scene:rmvEntity(y)
			end
			if  z and z ~= 0 then
				scene:rmvEntity(z)
			end

			local entity = scene:addMG(10, 230, 200) --刷怪点
			if entity then
				-- 设置怪物组属性
				entity:setProps(EP.attr_mg_refresh_interval, 2000)  -- interval	刷新间隔
				entity:setProps(EP.attr_mg_refresh_range, 18)    -- 刷怪范围

				entity:setProps(EP.attr_mg_refresh_type, 2)		--- 刷新类型 1是普通刷新 2 副本刷新
				entity:setProps(EP.attr_mg_monster_type_cnt, 1)  	--- 怪物种类数

				entity:setProps(EP.attr_mg_refresh_sid_begin, 2016)    --- 要刷新怪物配置ID
				entity:setProps(EP.attr_mg_refresh_count_begin, 3)
				entity:setProps(EP.attr_mg_refresh_limit_begin, 10)
			else
				print("failed to add monster generators on Event Tu cheng Kang Mo!!")
				return false
			end
			Event.setEventDataX(EID.chdd, entity:getID())
			
			entity2 = scene:addMG(10, 230, 200) --刷怪点
			if entity2 then
				-- 设置怪物组属性
				entity2:setProps(EP.attr_mg_refresh_interval, 2000)  -- interval	刷新间隔
				entity2:setProps(EP.attr_mg_refresh_range, 18)    -- 刷怪范围
				entity2:setProps(EP.attr_mg_refresh_type, 2)		--- 刷新类型 0是普通刷新 1 代表怪物组内怪物全死亡后统一刷新
				entity2:setProps(EP.attr_mg_monster_type_cnt, 1)  	--- 怪物种类数
				entity2:setProps(EP.attr_mg_refresh_sid_begin, 2017)
				entity2:setProps(EP.attr_mg_refresh_count_begin, 1)    -- 当前刷新模式（1）可以不填写上面的每次刷新数量
				entity2:setProps(EP.attr_mg_refresh_limit_begin, 1)
			else
				print("failed to add monster generators on Event Tu cheng Kang Mo!!")
				return false
			end
			--_G.syncFloatMessage("采花大盗开始！")

			Event.setEventDataY(EID.chdd, entity2:getID())
			
			-- 第三个刷新点
			local entity3 = scene:addMG(10, 230, 200) --刷怪点
			if entity3 then
				-- 设置怪物组属性
				entity3:setProps(EP.attr_mg_refresh_interval, 2000)  -- interval	刷新间隔
				entity3:setProps(EP.attr_mg_refresh_range, 18)    -- 刷怪范围

				entity3:setProps(EP.attr_mg_refresh_type, 1)		--- 刷新类型 1是普通刷新 2 副本刷新
				entity3:setProps(EP.attr_mg_monster_type_cnt, 1)  	--- 怪物种类数

				entity3:setProps(EP.attr_mg_refresh_sid_begin, 2016)    --- 要刷新怪物配置ID
				entity3:setProps(EP.attr_mg_refresh_count_begin, 3)
				entity3:setProps(EP.attr_mg_refresh_limit_begin, 10)
			else
				print("failed to add monster generators on Event cai hua da dao!!")
				return false
			end
			Event.setEventDataZ(EID.chdd, entity3:getID())

		end
		return true
	end,

	onStop = function(eventid)
		log.info("*****************chdd****************************end")
		local scene = gdScnMgr:getSceneBySid(MapID.wc)
		if scene then
			--删除怪物组
			local chddid = Event.getEventDataX(EID.chdd)
			if chddid then
				scene:rmvEntity(chddid)
			end
			
			local chddid2 = Event.getEventDataY(EID.chdd)
			if chddid2 then
				scene:rmvEntity(chddid2)
			end

			local chddid3 = Event.getEventDataZ(EID.chdd)
			if chddid3 then
				scene:rmvEntity(chddid3)
			end
			--_G.syncFloatMessage("采花大盗结束！")
		end
	end,
}
--
--	行会争夺战	hhzdz
--
gdEventExtension[EID.hhzdz] = {
	onStart = function(eventid,et)
		local ed = gdEventData[EID.hhzdz]
		Scene.onCreate(MapID.hhzdz,nil,Event.getStopTime(eventid))
		log.info("On Create ed.stoptime "..Event.getStopTime(eventid))
		return true
	end,

	onStop = function(eventid)
		local scene = gdScnMgr:getSceneBySid(MapID.hhzdz)
		if scene then
			scene:close()
		end
	end,
}
--
--	魔幻星宫	mhxg	sexg
--
gdEventExtension[EID.mhxg] = {
	onStart = function(eventid,et)
		local sceneid
		local scene
		for layer = 1, 12 do
			sceneid = Scene.onCreate(MapID.mhxg+layer-1)
			scene = gdScnMgr:getScene(sceneid)
			if scene then
				scene:setProps(SP.mhxg_layer, layer)
			end
		end
		return false
	end,

	onStop = function(eventid)
		for layer = 1, 12 do
			local scene = gdScnMgr:getSceneBySid(MapID.mhxg+layer-1)
			if scene then
				scene:close()
			end
		end
	end,
}
--
--	狩猎活动	slhd		降妖除魔	xycm
--
gdEventExtension[EID.slhd] = {
	onStart = function(eventid,et)
		Event.setEventDataX(EID.slhd, os.time())
		local ed = gdEventData[EID.slhd]
		local sceneid
		local scene
		for layer = 1, 4 do
			sceneid = Scene.onCreate(MapID.slc+layer-1, nil,Event.getStopTime(eventid))
			scene = gdScnMgr:getScene(sceneid)
			if scene then
				scene:setProps(SP.slhd_layer, layer)
			end
		end
		return true
	end,

	onStop = function(eventid)
		for layer = 1, 4 do
			scene = gdScnMgr:getSceneBySid(MapID.slc+layer-1)
			if scene then
				scene:close()
			end
		end
	end,
}
--
-- 城主双倍膜拜		czmb
--
gdEventExtension[EID.czmb] = {
	onStart = function(eventid,et)
		Event.setEventDataX(EID.czmb,1)
		return true
	end,

	onStop = function(eventid)
		Event.setEventDataX(EID.czmb, 0)
	end,
}
--
-- 祈福树		qfs
--
gdEventExtension[EID.qfs] = {
	onStart = function(eventid,et)
		Event.setEventDataZ(EID.qfs,1)
		return true
	end,

	onStop = function(eventid)
		Event.setEventDataZ(EID.qfs, 0)
	end,
}
--
-- 美女护送		mnhs
--
gdEventExtension[EID.mnhs] = {
	onStart = function(eventid,et)
		log.info("==============mnhs=============")
		Event.setEventDataX(EID.mnhs,1)
		return true
	end,

	onStop = function(eventid)
		Event.setEventDataX(EID.mnhs, 0)
	end,
}

--
--	武易战场	wyzc
--
gdEventExtension[EID.wyzc] = {
	onStart = function(eventid,et)
		log.info("==============wyzc onstart=============")
		local ed = gdEventData[EID.wyzc]
		Scene.onCreate(MapID.wyzc,nil,Event.getStopTime(eventid))
		return true
	end,

	onStop = function(eventid)
		log.info("==============wyzc onstop=============")
		local scene = gdScnMgr:getSceneBySid(MapID.wyzc)
		if scene then
			scene:close()
		end
	end,
}

--
--	战神争霸	zszb
--
gdEventExtension[EID.zszb] = {
	onStart = function(eventid,et)
		local ed = gdEventData[EID.zszb]
		Scene.onCreate(MapID.zszb,nil,Event.getStopTime(eventid))
		_G.setWorldDataX(EID.zszb,0)
		_G.setWorldDataY(EID.zszb,0)
		--记住开启的时间,用于十分钟之后禁止玩家进入
		Event.setEventDataX(EID.zszb, os.time())
		return true
	end,

	onStop = function(eventid)
		local scene = gdScnMgr:getSceneBySid(MapID.zszb)
		if scene then
			scene:close()
		end
	end,
}

--
--	勇士角斗场  ysjdc
gdEventExtension[EID.ysjdc] = {
	onStart = function(eventid,et)
		local ed = gdEventData[EID.ysjdc]
		Scene.onCreate(MapID.ysjdc,nil,Event.getStopTime(eventid))
		return true
	end,

	onStop = function(eventid)
		local scene = gdScnMgr:getSceneBySid(MapID.ysjdc)
		if scene then
			scene:close()
		end
	end,
}


--
--  马拉松	mls sm
gdEventExtension[EID.mls] = {
	onStart = function(eventid,et)
		local ed = gdEventData[EID.mls]
		Scene.onCreate(MapID.qssmc,nil,Event.getStopTime(eventid))
		Scene.onCreate(MapID.zdsmc,nil,Event.getStopTime(eventid))
		Event.setEventDataX(EID.mls,0)

		return true
	end,

	onStop = function(eventid)
		local scene = gdScnMgr:getSceneBySid(MapID.qssmc)
		if scene then
			scene:close()
		end
		local scene = gdScnMgr:getSceneBySid(MapID.zdsmc)
		if scene then
			scene:close()
		end
	end,
}

gdEventExtension[EID.xrboss] = {
	onStart = function(eventid,et)
--		_G.syncFloatMessage("亢金龙残影5分钟后在土城随机地点刷新，各位勇士做好准备！")
		return false
	end,

	onStop = function(eventid)
		local positions = {
			{110, 112},
			{205, 205},
			{221, 151},
			{259, 107},
			{378, 128},
			{350, 190},
			{168, 294},
			{102, 288},
			{62, 232},
			{58, 180},
			{24, 146},
			{12, 114},
			{10, 58},
			{50, 20},
			{98, 7},
			{132, 10},
			{150, 42},
		}
		local scene = gdScnMgr:getSceneBySid(MapID.tc)
		if scene then
			local count = 0
			scene:forEachEntityM(function (ettm)
					local ssid = ettm:getStaticID()
					if ssid==5315  and ettm:isAlive() then
						count = count+1
					end
				end)
			if count>=10 then
				_G.syncFloatMessage("还有".. count .. "只亢金龙残影藏在土城野外， 大家快去寻找！")
			else
				_G.syncFloatMessage("亢金龙残影已在土城多出刷新,各位勇士速速前往消灭")

				for i = count, 10 do
					local pos = positions[math.random(17)]
					if not pos then
						pos = {150, 42}
					end
					scene:addM(5315,  pos[1], pos[2])
				end
			end
		end

		return true
	end,
}
--
--	火龙熔岩	hlry
--
--[[	[EID.hlry] = {
onStart = function(eventid,et)
	local ed = gdEventData[EID.hlry]
	Scene.onCreate(MapID.hlry,nil,Event.getStopTime(eventid))
	--记住开启的时间,用于一分钟之后禁止玩家进入
	Event.setEventDataX(EID.hlry, os.time())
end,
onStop = function(eventid)
	local scene = gdScnMgr:getSceneBySid(MapID.hlry)
	if scene then
		scene:close()
	end
	Event.setEventDataX(EID.hlry, 0)
end,
},]]

local gcz_blocks =
{
	[1] = {x= 317,y = 160},
	[2] = {x= 316,y = 161},
	[3] = {x= 315,y = 162},
	[4] = {x= 315,y = 163},
	[5] = {x= 316,y = 162},
	[6] = {x= 317,y = 161},
	[7] = {x= 314,y = 161},
	[8] = {x= 315,y = 160},
	[9] = {x= 316,y = 159},
	[10] ={x= 316,y = 160},
	[11] ={x= 316,y = 160},
	[10] ={x= 315,y = 161},
}

--
--	攻城战	gcz
--
gdEventExtension[EID.gcz] = {
	onStart = function(eventid,et)

		-- 如果是跨服沙城战,
		if _G.isCrossServer() then
			local weekday = os.date("%w", os.time())
			if tonumber(weekday) ~= 4 then
				return false
			end
			
		else
			-- 普通服务器,周四晚上20点通知玩家去参加跨服战
			if tonumber(os.date("%w", os.time())) == 4 then
				_G.syncFloatMessage("跨服战已经开启,请大家到[土城:护国将军],参加跨服战!")
			end
			
		
			-- 开服不到三天
			if (ServerData.beginday < 3) then
				return false
			end

			-- 只有当某行会连续占领沙城4天后, 才会在周四时收回沙皇宫
			local own_4_days_flag = _G.getWorldDataX(WP.city_own4days_reward)
			local weekday = os.date("%w", os.time())
			if tonumber(weekday) == 4 and own_4_days_flag > 0 then
				return false
			end

			-- 不是周五或者没有公会连续四天占领沙城,则给所有公会自动报名
			if tonumber(weekday)~=5 or own_4_days_flag == 0 then
				_G.forEachGuild(function(guild)
					guild:setProps(GuildProp.guild_apply_gcz, 1)
					guild:saveProps(GuildProp.guild_apply_gcz)
				end)
			end
		
		end
		

		-- 配置
		local ed = gdEventData[EID.gcz]

		--
		--	创建攻城战沙皇宫
		--
		Scene.onCreate(MapID.gczshg)

		--
		--	创建沙城
		--
		Scene.onCreate(MapID.sc)

		--
		--	清除土城里面的沙城中的人物
		--
		local scene = gdScnMgr:getSceneBySid(MapID.tc)
		if scene then
			scene:forEachEntityP(function(entity)
				if entity:getProps(EntityProp.attr_is_insand) ~= 0 then
					local lvl = entity:getLevel()
					if lvl >= 35 then
						Scene.conveyentitytoAnywhere(entity,MapID.sc, entity:getPositionX(), entity:getPositionY())
					else
						Scene.conveyentitytoscene(entity,MapID.tc)
					end
				end
			end)

			--堵住普通沙城入口
			for k,v in ipairs(gcz_blocks) do
				scene:addBlock(v.x, v.y, 0x8000)
			end
		end

		--
		--	清除普通沙皇宫里面的玩家到土城
		--
		local shg = gdScnMgr:getSceneBySid(MapID.shg)
		if shg then
			shg:forEachEntityP(function(entity)
				Scene.conveyentitytoscene(entity,MapID.tc)
				end)
		end

		--重置攻城战击杀数据
		_G.setWorldDataX(WP.prop_gcz_kill_most,0)
		_G.setWorldDataY(WP.prop_gcz_kill_most,0)
		_G.setWorldDataZ(WP.prop_gcz_kill_most,0)

		_G.setWorldDataY(WP.city_master_guild, _G.getWorldDataX(WP.city_master_guild))
		return true
	end,
	
	onStop = function(eventid)
		_G.cleanLastGCZData()
		local shgscene = gdScnMgr:getSceneBySid(MapID.gczshg)
		if shgscene then
			log.info("get scene shg!")
			shgscene:close()
		end

		local scscene = gdScnMgr:getSceneBySid(MapID.sc)
		if scscene then
			log.info("get scene shg!")
			scscene:close()
		end

		local scene = gdScnMgr:getSceneBySid(MapID.tc)
		if scene then
			for k,v in ipairs(gcz_blocks) do
				scene:rmvBlock(v.x, v.y, 0x8000)
			end
		end
	end,
}

gdEventExtension[EID.gczzs] = {
	onStart = function(eventid, et)
		-- 若没有行会连续4天占领沙城, 则此时攻城战为开服活动, 需要一直开启
		local own_4_days_flag = _G.getWorldDataX(WP.city_own4days_reward)
		if own_4_days_flag == 0 then
			return false
		end

		_G.resetWorldData(WP.city_master_guild)

		_G.resetWorldData(WP.city_master_player)

		--
		--	城主元宝奖励仅仅是每周五22-23点可领取, 每周四凌晨重置
		--
		_G.resetWorldData(WP.city_master_get_gold)

		--
		--	周四早上需要清空攻城战申请数据
		--
		_G.forEachGuild(function(guild)
			guild:setProps(GuildProp.guild_apply_gcz, 0)
			guild:saveProps(GuildProp.guild_apply_gcz)
		end)
		return true
	end,
	onStop = function(eventid, et)
	end,
}

-- 沙城守卫军
gdEventExtension[EID.scswj] = {
	onStart =  function(eventid,et)
		-- 获取场景

		if _G.isCrossServer() then
			local weekday = os.date("%w", os.time())
			if tonumber(weekday) ~= 4 then
				return false
			end
		else
			if (ServerData.beginday < 3) then
				return false
			end
		end

		local scscene = gdScnMgr:getSceneBySid(MapID.sc)
		if scscene then
			local entity = scscene:addMG(1, 299, 148)
			if entity then
				entity:setProps(EntityProp.attr_mg_refresh_interval, 300 * 1000)
				entity:setProps(EntityProp.attr_mg_refresh_range, 14)
				entity:setProps(EntityProp.attr_mg_refresh_wave, 6)
				entity:setProps(EntityProp.attr_mg_refresh_type, 5)

				entity:setProps(EntityProp.attr_mg_monster_type_cnt, 1)  	---generators only create 1 type Monster
				entity:setProps(EntityProp.attr_mg_refresh_sid_begin, 2111)
				entity:setProps(EntityProp.attr_mg_refresh_count_begin, 12)
				entity:setProps(EntityProp.attr_mg_refresh_limit_begin, 12 * 6)
			else
				log.error("failed to add monster generators")
			end
			Event.setEventDataX(EID.scswj,entity:getID())
		end

		local shgscene = gdScnMgr:getSceneBySid(MapID.gczshg)
		if shgscene then
			local entity = shgscene:addMG(1, 12, 15)
			if entity then
				entity:setProps(EntityProp.attr_mg_refresh_interval, 600 * 1000)
				entity:setProps(EntityProp.attr_mg_refresh_range, 1)
				entity:setProps(EntityProp.attr_mg_refresh_wave, 3)
				entity:setProps(EntityProp.attr_mg_refresh_type, 5)

				entity:setProps(EntityProp.attr_mg_monster_type_cnt, 1)  	---generators only create 1 type Monster
				entity:setProps(EntityProp.attr_mg_refresh_sid_begin, 2112)
				entity:setProps(EntityProp.attr_mg_refresh_count_begin, 1)
				entity:setProps(EntityProp.attr_mg_refresh_limit_begin, 3)
			else
				log.error("failed to add monster generators")
			end
			Event.setEventDataY(EID.scswj,entity:getID())
		end

		_G.syncFloatMessage("沙城守卫军即将出现！")
		-- 加入怪物组

		return true
	end,
	onStop = function(eventid)

		local mgid = Event.getEventDataX(EID.scswj)
		if mgid then
			local scene = gdScnMgr:getSceneBySid(MapID.sc)
			if scene then
				scene:rmvEntity(mgid) -- 移除怪物组
			end
		end


		mgid = Event.getEventDataY(EID.scswj)
		if mgid then
			local scene = gdScnMgr:getSceneBySid(MapID.gczshg)
			if scene then
				scene:rmvEntity(mgid) -- 移除怪物组
			end
		end

		return true
	end,
}

gdEventExtension[EID.tc] = {
	onStart = function(eventid, et)
		local scene = gdScnMgr:getSceneBySid(MapID.tc)
		if not scene then
			local sceneid = Scene.onCreate(MapID.tc)
			scene = gdScnMgr:getScene(sceneid)
		end
		
		if not scene then
			log.error("failed to create or get scene for monster city attack event")
			return false
		end
		
		if scene.getProps then
			local active = scene:getProps(SP.siege_active)
			if active == 1 then
				return true
			end
		end
		
		startSiege(scene)
		return true
	end,
	onStop = function(eventid, et)
		local scene = gdScnMgr:getSceneBySid(MapID.tc)
		if scene then
			if scene.getProps then
				local active = scene:getProps(SP.siege_active)
				if active == 1 then
					endSiege(scene, false)
				end
			end
		end
		return true
	end,
}

