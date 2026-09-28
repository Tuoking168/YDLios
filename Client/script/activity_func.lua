------------------------------------------------------
--[[
enum
{
	time_activity = 0,
	daily_dungeon = 1,
	day_activity = 2,
	world_boss = 3,
	scene_boss = 4,
	week_activity = 5,
};
--]]

get_time_activity_data = function(index)
	local data = gdEventTime[index]
	if not(data) then
		log.error("get_time_activity_data, unknown index:", index)
	end
	return data
end

get_time_activity_visible = function(index)
	local data = get_time_activity_data(index)
	if data then
		local flag = data.visable
		if flag then
			if not(flag == 0) then
				return 0
			end
		end
		return 1
	end
	return 0
end

get_time_activity_visible_cnt = function()
	local cnt = 0
	for k, v in pairs(gdEventTime) do
		if (get_time_activity_visible(k) ~= 0) then
			cnt = cnt + 1
		end
	end
	return cnt
end

get_activity_id_by_id_name = function(idName)
	return gdEventAbbr[idName] or 0
end

get_activity_data = function(activityID, key)
	local data = gdEventData[activityID]
	if not(data) then
		log.error("get_activity_data, unknown activityID:", activityID)
	end

	if key then
		return data[key]
	end
	return data
end

get_activity_name = function(activityID)
	local data = get_activity_data(activityID)
	if data then
		return data.name or ""
	end
	return ""
end

get_activity_require_level = function(activityID)
	local data = get_activity_data(activityID)
	if data then
		return data.reborn or 0, data.requirelvl or 0
	end
	return 0, 0
end

get_activity_data_x = function(activityID)
	local data = get_activity_data(activityID)
	if data then
		return data.datax or 0
	end
	return 0
end

get_activity_desc = function(activityID)
	local data = get_activity_data(activityID)
	if data then
		return data.summary or ""
	end
	return ""
end

get_activity_npc_id = function(activityID)
	local data = get_activity_data(activityID)
	if data then
		return data.npc or 0
	end
	return 0
end

get_activity_reward_desc = function(activityID)
	local data = get_activity_data(activityID)
	if data then
		return data.mainreward or ""
	end
	return ""
end

get_activity_reward_id = function(activityID)
	local data = get_activity_data(activityID)
	if data then
		return data.loot or 0
	end
	return 0
end

get_world_boss_data = function(bossID)
	local data = gdWorldMonEvent[bossID]
	if not(data) then
		log.error("get_world_boss_data, unknown bossID:", bossID)
	end
	return data
end

activity_get_activity_cnt = function(viewType)
	if viewType == 0 then
		return #gdEventTime
	elseif viewType == 1 then
		return #gdEventInstance
	elseif viewType == 2 then
		return #gdEventAllDay
	elseif viewType == 3 then
		return #gdWorldBoss
	elseif viewType == 4 then
		return #gdMapBoss
	elseif viewType == 5 then
		return #gdEventWeek
	else
		log.error("activity_get_activity_cnt, unknown viewType:", viewType)
		return 0
	end
end

activity_get_activity_id = function(viewType, index)
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			return data.id or 0
		end
		return 0
	elseif viewType == 1 then
		return gdEventInstance[index] or 0
	elseif viewType == 2 then
		return gdEventAllDay[index] or 0
	elseif viewType == 3 then
		return gdWorldBoss[index] or 0
	elseif viewType == 4 then
		return gdMapBoss[index] or 0
	elseif viewType == 5 then
		return gdEventWeek[index].eid or 0
	else
		log.error("activity_get_activity_id, unknown viewType:", viewType)
		return 0
	end
end

activity_get_activity_index = function(viewType, activityID)
	local findIndex = function(tb, key)
		for k, v in pairs(tb) do
			if key then
				if (v[key] == activityID) then
					return k - 1
				end
			else
				if (v == activityID) then
					return k - 1
				end
			end
		end
	end

	if viewType == 0 then
		local doingIndex = 0
		local notStartIndex = 0
		local endIndex = 0
		local unstartID = gdceapon.get_data("activity", "unstart_id")
		for k, v in pairs(gdEventTime) do
			if (v.id == activityID) then
				if (k < unstartID) then
					local state = gdceapon.get_data("activity", "state_" .. k)
					if (state == 1) then
						doingIndex = k - 1
					else
						endIndex = k - 1
					end
				else
					notStartIndex = k - 1
				end
			end
		end

		if (doingIndex > 0) then
			return doingIndex
		elseif (notStartIndex > 0) then
			return notStartIndex
		else
			return endIndex
		end
	elseif viewType == 1 then
		return findIndex(gdEventInstance)
	elseif viewType == 2 then
		return findIndex(gdEventAllDay)
	elseif viewType == 3 then
		return findIndex(gdWorldBoss)
	elseif viewType == 4 then
		return findIndex(gdMapBoss)
	elseif viewType == 5 then
		return findIndex(gdEventWeek, "eid")
	else
		log.error("activity_get_activity_index, unknown viewType:", viewType)
		return 0
	end
end

activity_get_activity_type = function(activityID)
	local findType = function(tb, key)
		for k, v in pairs(tb) do
			if key then
				if (v[key] == activityID) then
					return true
				end
			else
				if (v == activityID) then
					return true
				end
			end
		end
		return false
	end

	if findType(gdEventTime, "id") then
		return 0
	elseif findType(gdEventInstance) then
		return 1
	elseif findType(gdEventAllDay) then
		return 2
	elseif findType(gdWorldBoss) then
		return 3
	elseif findType(gdMapBoss) then
		return 4
	elseif findType(gdEventWeek, "eid") then
		return 5
	end
	return 0
end

activity_get_activity_name = function(viewType, index)
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			local id = data.id
			if id then
				return get_activity_name(id)
			end
		end
		return ""
	elseif viewType == 1 then
		local id = gdEventInstance[index]
		if id then
			return get_activity_name(id)
		end
		return ""
	elseif viewType == 2 then
		local id = gdEventAllDay[index]
		if id then
			return get_activity_name(id)
		end
		return ""
	elseif viewType == 3 then
		local id = gdWorldBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				return data.name or ""
			end
		end
		return "Boss" .. index
	elseif viewType == 4 then
		local id = gdMapBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				return data.name or ""
			end
		end
		return "Boss" .. index
	elseif viewType == 5 then
		local id = gdEventWeek[index].eid
		if id then
			return get_activity_name(id)
		end
		return ""
	else
		log.error("activity_get_activity_name, unknown viewType:", viewType)
		return ""
	end
end

activity_get_activity_time = function(viewType, index)
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			return data.starttime or 0, data.stoptime or 0
		end
		return 0, 0
	elseif viewType == 5 then
		local data = gdEventWeek[index]
		if data then
			return data.starttime or 0, data.stoptime or 0
		end
		return 0, 0
	else
		log.error("activity_get_activity_time, unknown viewType:", viewType)
		return 0, 0
	end
end

activity_get_activity_reward = function(viewType, index)
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			local id = data.id
			if id then
				return get_activity_reward_desc(id)
			end
		end
		return ""
	elseif viewType == 1 then
		local id = gdEventInstance[index]
		if id then
			return get_activity_reward_desc(id)
		end
		return ""
	elseif viewType == 2 then
		local id = gdEventAllDay[index]
		if id then
			return get_activity_reward_desc(id)
		end
		return ""
	elseif viewType == 3 then
		local id = gdWorldBoss[index]
		if id then
			local data = gdLoots[id]
			if data and data.elems then
				local names = {}
				for k, v in pairs(data.elems) do
					if v.name then
						table.insert(names, v.name)
					end
				end
				return table.concat(names, "、")
			end
		end
		return ""
	elseif viewType == 4 then
		local id = gdMapBoss[index]
		if id then
			local data = gdLoots[id]
			if data and data.elems then
				local names = {}
				for k, v in pairs(data.elems) do
					if v.name then
						table.insert(names, v.name)
					end
				end
				return table.concat(names, "、")
			end
		end
		return ""
	elseif viewType == 5 then
		local id = gdEventWeek[index].eid
		if id then
			return get_activity_reward_desc(id)
		end
		return ""
	else
		log.error("activity_get_activity_reward, unknown viewType:", viewType)
		return ""
	end
end

activity_get_activity_level = function(viewType, index)
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			local id = data.id
			if id then
				return get_activity_require_level(id)
			end
		end
		return 0
	elseif viewType == 1 then
		local id = gdEventInstance[index]
		if id then
			return get_activity_require_level(id)
		end
		return 0
	elseif viewType == 2 then
		local id = gdEventAllDay[index]
		if id then
			return get_activity_require_level(id)
		end
		return 0
	elseif viewType == 5 then
		local id = gdEventWeek[index].eid
		if id then
			return get_activity_require_level(id)
		end
		return 0
	else
		log.error("activity_get_activity_level, unknown viewType:", viewType)
		return 0
	end
end

activity_get_activity_enter_max = function(viewType, index)
	if viewType == 1 then
		local id = gdEventInstance[index]
		if id then
			return get_activity_data_x(id)
		end
		return 0
	end
	log.error("activity_get_activity_enter_max, unknown viewType:", viewType)
	return 0
end

activity_get_boss_pos = function(eventid)
	local data = get_world_boss_data(eventid)
	if data then
		local refresh = data.refresh
		if refresh then
			local mapID = refresh.id
			if mapID then
				return mapID, refresh.x, refresh.y
			end
		end
	end
	return 0, 0, 0
end

activity_get_boss_id = function(viewType, index)
	if viewType == 3 then
		local id = gdWorldBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				local boss = data.boss
				if boss then
					return boss.min or 0
				end
			end
		end
		return 0
	elseif viewType == 4 then
		local id = gdMapBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				local boss = data.boss
				if boss then
					return boss.min or 0
				end
			end
		end
		return 0
	else
		log.error("activity_get_boss_id, unknown viewType:", viewType)
		return 0
	end
end

activity_get_boss_max_exp = function(viewType, index)
	if viewType == 3 then
		local id = gdWorldBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				local boss = data.boss
				if boss then
					return boss.exp or 0
				end
			end
		end
		return 0
	elseif viewType == 4 then
		local id = gdMapBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				local boss = data.boss
				if boss then
					return boss.exp or 0
				end
			end
		end
		return 0
	else
		log.error("activity_get_boss_max_exp, unknown viewType:", viewType)
		return 0
	end
end

activity_get_activity_npc = function(viewType, index)
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			local id = data.id
			if id then
				local npcID = get_activity_npc_id(id)
				if npcID > 0 then
					return npcID, cb_get_npc_name(npcID)
				end
			end
		end
		return 0, ""
	elseif viewType == 1 then
		local id = gdEventInstance[index]
		if id then
			local npcID = get_activity_npc_id(id)
			if npcID > 0 then
				return npcID, cb_get_npc_name(npcID)
			end
		end
		return 0, ""
	elseif viewType == 2 then
		local id = gdEventAllDay[index]
		if id then
			local npcID = get_activity_npc_id(id)
			if npcID > 0 then
				return npcID, cb_get_npc_name(npcID)
			end
		end
		return 0, ""
	elseif viewType == 5 then
		local id = gdEventWeek[index].eid
		if id then
			local npcID = get_activity_npc_id(id)
			if npcID > 0 then
				return npcID, cb_get_npc_name(npcID)
			end
		end
		return 0, ""
	else
		log.error("activity_get_activity_npc, unknown viewType:", viewType)
		return 0, ""
	end
end

activity_get_boss_map_id = function(viewType, index)
	if viewType == 3 then
		local id = gdWorldBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				local refresh = data.refresh
				if refresh then
					local mapID = refresh.id
					if mapID then
						return mapID, cb_get_scene_name(mapID), refresh.x, refresh.y
					end
				end
			end
		end
		return 0, "scene"
	elseif viewType == 4 then
		local id = gdMapBoss[index]
		if id then
			local data = get_world_boss_data(id)
			if data then
				local refresh = data.refresh
				if refresh then
					local mapID = refresh.id
					if mapID then
						return mapID, cb_get_scene_name(mapID), refresh.x, refresh.y
					end
				end
			end
		end
		return 0, "scene", 0, 0
	else
		log.error("activity_get_boss_map_id, unknown viewType:", viewType)
		return 0, ""
	end
end

activity_get_activity_desc = function(viewType, index)
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			local id = data.id
			if id then
				return get_activity_desc(id)
			end
		end
		return ""
	elseif viewType == 1 then
		local id = gdEventInstance[index]
		if id then
			return get_activity_desc(id)
		end
		return ""
	elseif viewType == 2 then
		local id = gdEventAllDay[index]
		if id then
			return get_activity_desc(id)
		end
		return ""
	elseif viewType == 3 then
		return ""
	elseif viewType == 4 then
		return ""
	elseif viewType == 5 then
		local id = gdEventWeek[index].eid
		if id then
			return get_activity_desc(id)
		end
		return ""
	else
		log.error("activity_get_activity_desc, unknown viewType:", viewType)
		return ""
	end
end

activity_get_reward_list = function(lootID, result, filter)
	result = result or {}
	filter = filter or {}
	local data = gdLoots[lootID]
	if data then
		local list = data.elems
		if list then
			for k, v in pairs(list) do
				if v.type == 1 then
					activity_get_reward_list(v.sid, result, filter)
				else
					local has = filter[v.sid]
					if not(has) then
						result[#result + 1] = v.sid
						filter[v.sid] = 1
					end
				end
			end
		end
	end
end

local currentRewardList = {}
activity_get_activity_reward_cnt = function(viewType, index)
	currentRewardList = {}
	if viewType == 0 then
		local data = get_time_activity_data(index)
		if data then
			local id = data.id
			if id then
				local lootID = get_activity_reward_id(id)
				activity_get_reward_list(lootID, currentRewardList)
				return #currentRewardList
			end
		end
		return 0
	elseif viewType == 1 then
		local id = gdEventInstance[index]
		if id then
			local lootID = get_activity_reward_id(id)
			activity_get_reward_list(lootID, currentRewardList)
			return #currentRewardList
		end
		return 0
	elseif viewType == 2 then
		local id = gdEventAllDay[index]
		if id then
			local lootID = get_activity_reward_id(id)
			activity_get_reward_list(lootID, currentRewardList)
			return #currentRewardList
		end
		return 0
	elseif viewType == 3 then
		local id = gdWorldBoss[index]
		local mid = gdceapon.get_sub_data("activity", "world_boss_list", id, "world_boss_sid")
		if mid then
			local lootID = g_get_monster_reward_id(mid)
			if lootID and lootID ~= 0 then
				activity_get_reward_list(lootID, currentRewardList)
				return #currentRewardList
			end
		end
		activity_get_reward_list(id, currentRewardList)
		return #currentRewardList
	elseif viewType == 4 then
		local id = gdMapBoss[index]
		local mid = gdceapon.get_sub_data("activity", "world_boss_list", id, "world_boss_sid")
		if mid then
			local lootID = g_get_monster_reward_id(mid)
			if lootID and lootID ~= 0 then
				activity_get_reward_list(lootID, currentRewardList)
				return #currentRewardList
			end
		end
		activity_get_reward_list(id, currentRewardList)
		return #currentRewardList
	elseif viewType == 5 then
		local id = gdEventWeek[index].eid
		if id then
			local lootID = get_activity_reward_id(id)
			activity_get_reward_list(lootID, currentRewardList)
			return #currentRewardList
		end
		return 0
	else
		log.error("activity_get_activity_reward_cnt, unknown viewType:", viewType)
		return 0
	end
end

activity_get_activity_reward_icon = function(viewType, index, rewardIndex)
	local sid = currentRewardList[rewardIndex]
	return sid or 0
end


--[[
namespace ActivityStateBuilder
{
	enum
	{
		start = 1,
		doing = 2,
		stop = 3,
	};
}
--]]
local activityStateBuilder = {
	start = function()
		g_dispatcherEvent("lua_change", "activity_build_activity_state", "", 1)
	end,

	add = function(text, fontSize, colorID)
		g_dispatcherEvent("lua_change", "activity_build_activity_state", "", 2, text, fontSize, colorID)
	end,

	stop = function(isTimeLabel)
		isTimeLabel = isTimeLabel or 0
		g_dispatcherEvent("lua_change", "activity_build_activity_state", "", 3, isTimeLabel)
	end,
}

activity_build_activity_state = function(activityID, dataX, dataY, dataZ)
	local fontSize = 14
	local white = 0
	local green = 1
	local yellow = 2
	local T = activityStateBuilder

	if activityID <= 0 then
		T.start()
		T.add("当前未参加任何活动。", fontSize, white)
		T.stop(index)
	else
		T.start()
		T.add("剩余时间：", fontSize, white)
		T.stop(1)

		local handleFunc = {
			[EID.jtbg] = function()
				local monster = cb_get_scene_prop(SceneProp.now_monster) .. "/" .. cb_get_scene_prop(SceneProp.max_monster)
				T.start()
				T.add("剩余怪物：", fontSize, white)
				T.add(monster, fontSize, yellow)
				T.stop()
			end,

			[EID.mnhs] = function()
				local targetID = cb_get_entity_prop(EntityProp.attr_meinvhusong_mid)
				local targetName = get_layout_string("activity", "convoyBeautyTarget" .. targetID)
				T.start()
				T.add("当前美女：", fontSize, white)
				T.add(targetName, fontSize, yellow)
				T.stop()

				local npcName = cb_get_npc_name(gdGame.girlSubmitNPC)
				T.start()
				T.add("提交NPC：", fontSize, white)
				T.add(npcName, fontSize, yellow)
				T.stop()

				T.start()
				T.add("（点击自动寻路）", fontSize, green)
				T.stop()
			end,

			[EID.hhzdz] = function()
				local guildName = cb_get_scene_prop(0)
				if (type(guildName) == "string") and (#guildName > 0) then
					T.start()
					T.add("当前守旗行会：", fontSize, white)
					T.add(guildName, fontSize, yellow)
					T.stop()
				end

				T.start()
				T.add("提示：", fontSize, white)
				T.add("成功消灭旗帜并守住10分钟以上的行会将获得胜利，可以获得丰富的活动奖励。", fontSize, green)
				T.stop()
			end,

			[EID.cyxg] = function()
				T.start()
				T.add("提示：", fontSize, white)
				T.add("拾取赤月魔图腾后，可获得10分钟双倍经验BUFF。", fontSize, green)
				T.stop()
			end,

			[EID.wyzc] = function()
				local faction = cb_get_entity_prop(EntityProp.attr_faction_id)
				local factionName = "人"
				local factionScore = cb_get_scene_prop(SceneProp.wyzc_score_a)
				if faction == 2 then
					factionName = "魔"
					factionScore = cb_get_scene_prop(SceneProp.wyzc_score_b)
				end

				T.start()
				T.add("你的阵营：", fontSize, white)
				T.add(factionName, fontSize, yellow)
				T.stop()

				T.start()
				T.add("个人积分：", fontSize, white)
				T.add(dataX, fontSize, yellow)
				T.stop()

				T.start()
				T.add("阵营积分：", fontSize, white)
				T.add(factionScore, fontSize, yellow)
				T.stop()
			end,

			[EID.tdbk] = function()
				T.start()
				T.add("当前波数：", fontSize, white)
				T.add(cb_get_scene_prop(SceneProp.tdbk_boss_idx), fontSize, yellow)
				T.stop()

				T.start()
				T.add("当前连击数：", fontSize, white)
				T.add(cb_get_scene_prop(SceneProp.tdbk_kill_count), fontSize, yellow)
				T.stop()


				T.start()
				T.add("当前攻击加成：", fontSize, white)
				T.add(cb_get_scene_prop(SceneProp.tdbk_buff_data) .. "%", fontSize, yellow)
				T.stop()

				T.start()
				T.add("提示：", fontSize, white)
				T.add("消灭怪物可以获得金币，消灭BOSS进入下一波，消灭怪物可以获得连斩攻击BUFF，攻击BUFF越高可以帮助你更轻松地杀怪！", fontSize, green)
				T.stop()
			end,

			[EID.zssd] = function()
				T.start()
				T.add("当前波数：", fontSize, white)
				T.add(cb_get_scene_prop(SceneProp.zssd_monster_wave)+1, fontSize, yellow)
				T.add("/6", fontSize, yellow)
				T.stop()

				T.start()
				T.add("当前击杀数：", fontSize, white)
				T.add(cb_get_scene_prop(SceneProp.zssd_kill_count), fontSize, yellow)
				T.stop()

				T.start()
				T.add("提示：", fontSize, white)
				T.add("消灭怪物可以获得转生灵魄。", fontSize, green)
				T.stop()
			end,

			[EID.ysjdc] = function()
				T.start()
				T.add("当前积分：", fontSize, white)
				T.add(dataX, fontSize, yellow)
				T.stop()

				T.start()
				T.add("提示：", fontSize, white)
				T.add("采集图腾获得1分；击杀勇士获得10分；击杀角斗之王获得200分；击杀其他玩家将夺取对方80%的积分。", fontSize, green)
				T.stop()
			end,

			[EID.zszb] = function()
				local cnt = cb_get_scene_prop(SceneProp.zszb_player_cnt)
				T.start()
				T.add("剩余玩家：", fontSize, white)
				T.add(cnt, fontSize, yellow)
				T.stop()

				T.start()
				T.add("提示：", fontSize, white)
				T.add("活动开始10分钟后，场景内唯一的玩家可以申请【霸王】称号。", fontSize, green)
				T.stop()
			end,

			[EID.mls] = function()
				local state = cb_get_scene_prop(SceneProp.mls_begin_state)
				T.start()
				if state == 0 then
					T.add("等待比赛开始", fontSize ,white)
				else
					T.add("比赛开始", fontSize ,white)
				end
				T.stop()
			end,

			--[[
			[EID.dyjj] = function()
				local npcCnt = cb_get_scene_prop(SceneProp.dyjj_defencer_count)
				T.start()
				T.add("剩余NPC数：", fontSize, white)
				T.add(npcCnt , fontSize, yellow)
				T.stop()

				local cnt = cb_get_scene_prop(SceneProp.dyjj_monster_wave)
				T.start()
				T.add("当前入侵者波数：", fontSize, white)
				T.add(cnt , fontSize, yellow)
				T.stop()
			end,
			--]]

			[EID.mlsd] = function()
				local npcCnt = cb_get_scene_prop(SceneProp.mlsd_defencer_count)
				T.start()
				T.add("剩余NPC数：", fontSize, white)
				T.add(npcCnt , fontSize, yellow)
				T.stop()

				local cnt = cb_get_scene_prop(SceneProp.mlsd_monster_wave)
				T.start()
				T.add("当前入侵者波数：", fontSize, white)
				T.add(cnt , fontSize, yellow)
				T.stop()
			end,

			[EID.lhg] = function()
				local layerCnt = cb_get_scene_prop(SceneProp.lhg_layer)
				T.start()
				T.add("当前层数：", fontSize, white)
				T.add(layerCnt , fontSize, yellow)
				T.stop()
				T.start()
				T.add("提示：", fontSize, white)
				T.add("进入水晶宫下一层需要:", fontSize, green)
				T.add(cb_get_scene_prop(SceneProp.lhg_liehuolin_to_next_layer), fontSize, yellow)
				T.add("个水晶令或者:", fontSize, green)
				T.add(cb_get_scene_prop(SceneProp.lhg_gold_to_next_layer), fontSize, yellow)
				T.add("个元宝或者:", fontSize, green)
				T.add(cb_get_scene_prop(SceneProp.lhg_diamond_to_next_layer), fontSize, yellow)
				T.add("个礼券或者:", fontSize, green)
				T.add(cb_get_scene_prop(SceneProp.lhg_honor_to_next_layer), fontSize, yellow)
				T.add("点荣誉", fontSize, green)
				T.stop()
			end,

			[EID.slhd] = function()
				local score = cb_get_entity_prop(EntityProp.attr_slhd_score)
				T.start()
				T.add("当前得分：", fontSize, white)
				T.add(score , fontSize, yellow)
				T.stop()
			end,

			[EID.wxly] = function()
				local cnt = cb_get_scene_prop(SceneProp.wxly_boss_kill_cnt)
				T.start()
				T.add("击败炼狱魔王：", fontSize, white)
				T.add(cnt , fontSize, yellow)
				T.stop()

				T.start()
				T.add("提示：", fontSize, white)
				T.add("击杀场景周边的守卫可变更守卫的五行，当五个守卫的五行都克制了炼狱魔王时，魔王的实力将被大幅削弱。", fontSize, green)
				T.stop()
			end,
		}
		local func = handleFunc[activityID]
		if func then
			func()
		end
	end
end

------------------------------------------------------------
-- arena
activity_get_arena_record = function(isNew, name, challengerFlag, winFlag)
	local msg = ""
	if (isNew ~= 0) then
		msg = "新战报："
	end

	if (challengerFlag == 0) then
		msg = msg .. "[g" .. name .. "]挑战你"
	else
		msg = msg .. "你挑战[g" .. name .. "]"
	end

	if (winFlag == 0) then
		msg = msg .. "，你失败了。"
	else
		msg = msg .. "，你胜利了！"
	end
	return msg
end
-----------------------------------------------------------
-- treasure
activity_get_treasure_record = function(name, sid, strong, reborn)
	local msg = "[b" .. name .. "]寻宝获得了"
	if (reborn > 0) then
		msg = msg .. "[r" .. reborn .. "转]"
	end

	msg = msg .. "[y" .. g_get_item_name(sid)
	if (strong > 0) then
		msg = msg .. " +" .. strong
	end
	msg = msg .. "]"

	return msg
end


-----------------------------------------------------------
get_single_recharge_table_length = function()
    local length = #(gdSingalRecharge)
	if length then
	   return length
	end

	return 0
end

get_single_recharge_article_id = function(indexID)
	local data = gdSingalRecharge[indexID]
	if data then
	   return data.sid
	end
    log.error("get_single_recharge_article_id,unknown indexID:",indexID)

	return 0
end

get_single_recharge_label_data = function(wingID)
	local data = gdSingalRecharge[wingID]
	if data then
	   return data.obtain
	end
	log.error("get_single_recharge_label_data,unknown wingID:",wingID)

    return  ""
end

get_single_recharge_label_desc = function(wingID)
    local data = gdSingalRecharge[wingID]
	if data then
	    return data.desc
	end
    log.error("get_single_recharge_label_desc,unknown wingID:",wingID)

	return ""
end

get_single_recharge_label_property = function(wingID)
    local data = gdSingalRecharge[wingID]
	if data then
	    return data.property
	end
    log.error("get_single_recharge_label_property,unknown wingID:",wingID)

	return ""
end

--------------------















