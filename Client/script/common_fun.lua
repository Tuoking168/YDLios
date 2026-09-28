--[[
namespace CPEventName
{
	// event from lua
	static const std::string LUA_CHANGE = "lua_change";
	static const std::string LUA_FINISH = "lua_finish";
}

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
--]]
g_dispatcherEvent = function(name, source, target, value1, value2, value3, value4, value5)
	name = name or "event"
	gdceapon.set_sub_data("event", name, 1, "source", source)
	gdceapon.set_sub_data("event", name, 1, "target", target)
	gdceapon.set_sub_data("event", name, 1, "value_1", value1)
	gdceapon.set_sub_data("event", name, 1, "value_2", value2)
	gdceapon.set_sub_data("event", name, 1, "value_3", value3)
	gdceapon.set_sub_data("event", name, 1, "value_4", value4)
	gdceapon.set_sub_data("event", name, 1, "value_5", value5)
	CPEvtDispatcher.dispatcher(name)
end

--------------------------------------------------------------------------------------------
-- send msg

g_sendMessage = function(name, value1, value2, value3, value4, value5)
	CPMsgHandler.send(value5, value4, value3, value2, value1, name)
end
-----------------------------------------------------------------------
-- filter

local getPermitStar = function(str)
	local len = str:len()
	local chineChar = 0
	local abc = 0
	local charValue
	for i = 1, len, 1 do
		charValue = string.byte(str, i, i)
		if charValue > 128 then
			abc = abc + 1
			if abc == 3 then--here is wchar_t
				chineChar = chineChar + 1
				abc = 0
			end
		elseif  charValue > 0 and charValue <= 128 then
			if abc ~= 0 then
				chineChar = chineChar + 1
				abc = 0
			end
		end
	end
	return string.rep("*", str:len() - chineChar * 2)--newValue--
end
g_get_string_permit = function(str)
	local permitStr = str
	local isPermit = true
	local len = 0
	for k, v in pairs(gdFilter) do
		if (v:len() > 0) then
			permitStr, len = string.gsub(permitStr, v, getPermitStar(v))
			if len > 0 then
				isPermit = false
			end
		end
	end
	return permitStr, isPermit
end

---------------------------------------------
--[[
const static int SEX_MALE	= 1;
const static int SEX_FEMALE	= 2;
--]]
cb_get_random_name = function(gender)
	local A = gdNames.nameA
	local B = gdNames.nameB
	local C = gdNames.nameC

	math.random()

	local s1 = A[math.random(#A)] or "李"
	local s2
	if gender == 1 then
		s2 = B[math.random(#B)]
	else
		s2 = C[math.random(#C)]
	end
	s2 = s2 or "明"
	return s1 .. s2
end


g_get_random_tips = function()
	math.random()
	return gdRandomTips[math.random(#gdRandomTips)] or ""
end
-------------------------------------------
g_init_default_setting = function(pid)
	local subModu = gdceapon.get_data("userData", "data_depend_pid")
	subModu = init_table_safely(subModu)
	subModu[pid] = init_table_safely(subModu[pid])
	for k, v in pairs(gdgameinit_data) do
		subModu[pid][k] = v
	end
	gdceapon.set_data("userData", "data_depend_pid", subModu)
end

-----------------------------------------------
-- player
local rebornColor = {
	[1] = {
		r = 0,
		g = 255,
		b = 0,
	},

	[2] = {
		r = 0,
		g = 128,
		b = 255,
	},

	[3] = {
		r = 242,
		g = 0,
		b = 193,
	},

	[4] = {
		r = 255,
		g = 102,
		b = 0,
	},

	[5] = {
		r = 255,
		g = 0,
		b = 0,
	},

	[6] = {
		r = 0,
		g = 255,
		b = 255,
	},

	[7] = {
		r = 128,
		g = 128,
		b = 0,
	},

	[8] = {
		r = 128,
		g = 0,
		b = 255,
	},

	[9] = {
		r = 255,
		g = 204,
		b = 0,
	},
	[63] = {
		r = 255,
		g = 0,
		b = 0,
	},
	[64] = {
		r = 242,
		g = 0,
		b = 193,
	},
	[65] = {
		r = 128,
		g = 0,
		b = 255,
	},
}
g_get_reborn_str_and_color = function(reborn)
    reborn = reborn or 0
    if (reborn <= 0) then
        return "", 255, 255, 255
    end
	
    local str
    if reborn <= 25 then
        -- 1-25转
        str = "[" .. reborn .. "转]"
    elseif reborn <= 40 then
        -- 26-40转：凝气1-15
        str = "[凝气" .. (reborn - 25) .. "]" 
    elseif reborn == 41 then
        str = "[筑基]"
    elseif reborn == 42 then
        str = "[结丹]"
    elseif reborn == 43 then
        str = "[元婴]"
    elseif reborn == 44 then
        str = "[化神]"
    elseif reborn == 45 then
        str = "[婴变]"
    elseif reborn == 46 then
        str = "[问鼎]"
    elseif reborn == 47 then
        str = "[阴虚]"
    elseif reborn == 48 then
        str = "[阳实]"
    elseif reborn == 49 then
        str = "[窥涅]"
    elseif reborn == 50 then
        str = "[净涅]"
    elseif reborn == 51 then
        str = "[碎涅]"
    elseif reborn == 52 then
        str = "[天人五衰]"
    elseif reborn == 53 then
        str = "[空涅]"
    elseif reborn == 54 then
        str = "[空灵]"
    elseif reborn == 55 then
        str = "[空玄]"
    elseif reborn == 56 then
        str = "[空劫]"
    elseif reborn == 57 then
        str = "[大尊]"
    elseif reborn == 58 then
        str = "[金尊]"
    elseif reborn == 59 then
        str = "[天尊]"
    elseif reborn == 60 then
        str = "[跃天尊]"
    elseif reborn == 61 then
        str = "[大天尊]"
    elseif reborn == 62 then
        str = "[踏天]"
	elseif reborn == 63 then
        str = "[煌天]"
	elseif reborn == 64 then
        str = "[煌天中期]"
	elseif reborn == 65 then
        str = "[煌天大圆满]"
	elseif reborn == 66 then
        str = "[道成]"
	elseif reborn == 67 then
        str = "[道果]"
	elseif reborn == 68 then
        str = "[道蚀]"
	elseif reborn == 69 then
        str = "[道涅]"
	elseif reborn == 70 then
        str = "[道源]"
	elseif reborn == 71 then
        str = "[大罗]"
	elseif reborn == 72 then
        str = "[法则]"
	elseif reborn == 73 then
        str = "[无相]"
	elseif reborn == 74 then
        str = "[本源]"
	elseif reborn == 75 then
        str = "[归墟]"
	elseif reborn == 76 then
        str = "[天道]"
	elseif reborn == 77 then
        str = "[因果]"
	elseif reborn == 78 then
        str = "[概念]"
	elseif reborn == 79 then
        str = "[彼岸]"
	elseif reborn == 80 then
        str = "[灭天]"
	
    else
	
       
        str = "[灭天]"
    end
    
    -- 获取颜色
    local color
    if rebornColor[reborn] then
        -- 如果当前转生有对应的颜色，直接使用
        color = rebornColor[reborn]
    else
        -- 如果当前转生没有定义颜色，使用回绕机制
        local colorid = (reborn - 1) % 9 + 1
        color = rebornColor[colorid]
    end
    
    if color then
        return str, color.r or 255, color.g or 255, color.b or 255
    end
    
    return str, 255, 255, 255
end

g_get_anim_order_data = function(direction, action, animType)
	local dirData = gdAnimOrder[direction]
	if dirData then
		local actionData = dirData[action]
		if actionData then
			return actionData[animType] or 3
		end
	end
	return 0
end
-----------------------------------
-- item
cb_get_item_data = function(sid)
	local data = gdItems[sid]
	if not(data) then
		log.error("cb_get_item_data, unknown sid:", sid)
	end
	return data
end

cb_get_item_icon = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.icon or ""
	end
	return ""
end

cb_get_item_icon_with_count = function(sid, count)
	local data = cb_get_item_data(sid)
	if data then
		-- 如果是金币，则按照数量选择icon
		if sid == 2 then
			if (100 <= count) and (count <= 999) then
				return cb_get_item_icon(10)
			elseif (count >= 1000) then
				return cb_get_item_icon(11)
			else
				return cb_get_item_icon(9)
			end
		end
		return cb_get_item_icon(sid)
	end
	return ""
end

g_get_item_name = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.name or ""
	end
	return ""
end

g_get_item_cate = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.cate or 0
	end
	return 0
end

g_get_item_type = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.type or 0
	end
	return 0
end

g_get_item_mining_flag = function(sid)
	if 70167 <= sid and sid <= 70174 then
		return 1
	end
	return 0
end

g_get_item_skill_id = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.skillid or 0
	end
	return 0
end

g_get_item_suit_weapon_id = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.exweapon or 0
	end
	return 0
end

g_get_item_require_level = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.rebornlvl or 0, data.req_level or 0
	end
	return 0, 0
end

g_get_item_require_job = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.class or 0
	end
	return 0
end

g_get_item_require_gender = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.gender or 0
	end
	return 0
end

g_get_item_data_ex = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.datax or 0, data.datay or 0
	end
	return 0, 0
end

g_get_item_data_str = function(sid)
	local data = cb_get_item_data(sid)
	if data then
		return data.datas or ""
	end
	return ""
end

g_get_guan_gong_cloth = function(gender)
	if (gender == 2) then
		return 81167
	end
	return 81156
end

g_get_guild_fu_li_item = function(index)
	local items = {
		[1] = 40081,
		[2] = 30046,
		[3] = 30003,
		[4] = 30042,
	}
	index = index or 1
	if (index <= 0) then
		index = 1
	elseif (index > #items) then
		index = #items
	end
	return items[index] or 0
end

g_get_city_master_cloth_item_id = function(gender)
	if (gender == 1) then
		return 81178
	end
	return 81189
end

g_get_default_equip = function(level, gender)
	if (gender == 2) then
		return 60183, 60180, 80003
	else
		return 60182, 60180, 80003
	end
end

local npcDefaultEquipFilter = {
	[113] = 1,
	[118] = 1,
	[139] = 1,
	[140] = 1,
	[141] = 1,
	[143] = 1,
	[144] = 1,
	[145] = 1,
	[146] = 1,
	[147] = 1,
	[148] = 1,
	[149] = 1,
	[165] = 1,
	[184] = 1,
	[186] = 1,
	[187] = 1,
	[188] = 1,
	[206] = 1,
	[209] = 1,
	[220] = 1,
	[260] = 1,
	[261] = 1,
	[262] = 1,
}
g_get_npc_default_equip = function(npcID)
	local data = npcDefaultEquipFilter[npcID]
	if data then
		return npcID
	end
	return 154
end

g_get_cheng_ba_tian_xia_equip = function(gender)
	if (gender == 2) then
		return 81076, 0, 0
	end
	return 81066, 0, 0
end

get_item_anim = function(itemID)
    local data = cb_get_item_data(itemID)
	if data then
	  return data.anim or ""
	end

	return ""
end
--------------------------------------------
-- pet
cb_get_pet_data = function(petid)
	local data = gdPets[petid]
	if not(data) then
		log.error("cb_get_pet_data, unknown petid:", petid)
	end
	return data
end

g_get_pet_anim_name = function(petid, reborn)
	local data = cb_get_pet_data(petid)
	if data then
		local anim = data.anim
		if anim then
			if reborn > 0 then
				return anim.s or ""
			end
			return anim.n or ""
		end
	end
	return ""
end

----------------------------------------------
-- monster
cb_get_monster_data = function(mid)
	local data = gdMonsters[mid]
	if not(data) then
		log.error("cb_get_monster_data, unknown mid:", mid)
	end
	return data
end

g_get_monster_name = function(mid)
	local data = cb_get_monster_data(mid)
	if data then
		return data.name or ""
	end
	return ""
end

g_get_monster_level = function(mid)
	local data = cb_get_monster_data(mid)
	if data then
		return data.lvl or 0
	end
	return 0
end

g_get_monster_scale = function(mid)
	local data = cb_get_monster_data(mid)
	if data then
		return data.scale or 1
	end
	return 1
end

g_get_monster_reward_id = function(mid)
	local data = cb_get_monster_data(mid)
	if data then
		if data.rewardid then
			return data.rewardid
		end
		if data.reward and gdLootnametoID then
			return gdLootnametoID[data.reward] or 0
		end
	end
	return 0
end

g_get_monster_plant_flag = function(mid)
	local data = cb_get_monster_data(mid)
	if data then
		return data.isplant or 0
	end
	return 0
end

g_get_monster_boss_flag = function(mid)
	local data = cb_get_monster_data(mid)
	if data then
		return data.isBoss or 0
	end
	return 0
end

g_get_monster_sel_flag = function(mid)
	local data = cb_get_monster_data(mid)
	if data then
		return data.aselectfail or 0
	end
	return 0
end

-----------------------------------------------
-- skill
cb_get_skill_data = function(skillID)
	local data = gdSkills[skillID]
	if not(data) and (skillID ~= 6020) then
		log.error("cb_get_skill_data, unknown skillID:", skillID)
	end
	return data
end

g_get_skill_name = function(skillID)
	local data = cb_get_skill_data(skillID)
	if data then
		return data.name or ""
	end
	return ""
end

g_get_skill_need_mana = function(skillID)
	local data = cb_get_skill_data(skillID)
	if data then
		return data.mana or 0
	end
	return 0
end

g_get_skill_cd = function(skillID)
	local data = cb_get_skill_data(skillID)
	if data then
		return data.cooldown or 0
	end
	return 0
end

g_get_skill_sound = function(skillID)
	local data = cb_get_skill_data(skillID)
	if data then
		local sound = data.sound or ""
		sound = sound .. ""
		if string.len(sound) > 1 then
			return "data-a/sound/" .. sound .. ".mp3"
		end
	end
	return ""
end

g_get_sai_ma_chang_first_skill = function()
	return 2031
end

----------------------------------------------
-- npc
cb_get_npc_data = function(nid)
	local data = gdNPC[nid]
	if not(data) then
		log.error("cb_get_npc_data, unknown nid:", nid)
	end
	return data
end

cb_get_npc_name = function(nid)
	local data = cb_get_npc_data(nid)
	if data then
		return data.name or ""
	end
	return ""
end

g_get_first_rank_job_test = function(nid)
	if (nid == 144) then -- 战士男
		return 1, 1
	elseif (nid) == 145 then -- 法师男
		return 2, 1
	elseif (nid == 146) then -- 道士男
		return 3, 1
	elseif (nid == 186) then -- 战士女
		return 1, 2
	elseif (nid == 187) then -- 法师女
		return 2, 2
	elseif (nid == 188) then -- 道士女
		return 3, 2
	end
	return 0, 0
end

g_get_city_master_flag = function(nid)
	if (nid == 143) then
		return 1
	end
	return 0
end

g_get_city_master_cloth = function(job, gender)
	if (job == 1) and (gender == 1) then
		return 144
	elseif (job == 2) and (gender == 1) then
		return 145
	elseif (job == 3) and (gender == 1) then
		return 146
	elseif (job == 1) and (gender == 2) then
		return 186
	elseif (job == 2) and (gender == 2) then
		return 187
	elseif (job == 3) and (gender == 2) then
		return 188
	end
	return 144
end

g_get_portal_npc_flag = function(nid)
	local name = cb_get_npc_name(nid)
	
	-- 传送石
	if (name == "传送石"or name == "修仙指引人") then
		return 1
	end

	return 0
end

g_get_npc_function_count = function(nid)
	local data = cb_get_npc_data(nid)
	if data then
		local funcs = data.nFunction
		if (type(funcs) == "table") then
			return #funcs
		end
	end
	return 0
end

g_get_npc_function_caption = function(nid, funcID)
	local data = cb_get_npc_data(nid)
	if data then
		local funcs = data.nFunction
		if funcs then
			local func = funcs[funcID]
			if func then
				return func.caption or ""
			end
		end
	end
	return ""
end

g_get_npc_hide_in_world_map_flag = function(nid)
	local data = cb_get_npc_data(nid)
	if data then
		return data.hideInWorldMap or 0
	end
	return 0
end

g_get_guild_convoy_npc = function()
	return 177
end
---------------------------------------
-- quest
cb_get_quest_data = function(qid)
	local data = gdQuests[qid]
	if not(data) then
		log.error("cb_get_quest_data, unknown qid:", qid)
	end
	return data
end

cb_get_quest_name = function(qid)
	local data = cb_get_quest_data(qid)
	if data then
		return data.name or ""
	end
	return ""
end

cb_get_quest_desc = function(qid)
	local data = cb_get_quest_data(qid)
	if data then
		return data.des or ""
	end
	return ""
end

cb_get_quest_tgt_desc = function(qid)
	local data = cb_get_quest_data(qid)
	if data then
		return data.target_content or ""
	end
	return ""
end

cb_get_quest_src_npc = function(qid)
	local data = cb_get_quest_data(qid)
	if data then
		return data.npc_src or 0
	end
	return 0
end

cb_get_quest_tgt_npc = function(qid)
	local data = cb_get_quest_data(qid)
	if data then
		return data.npc_tgt or 0
	end
	return 0
end

cb_get_quest_tgt_data_y = function(qid)
	local data = cb_get_quest_data(qid)
	if data then
		return data.target_datay or 0
	end
	return 0
end

g_get_quest_require_level = function(qid)
	local data = cb_get_quest_data(qid)
	if data then
		return data.req_lvl or 0
	end
	return 0
end

--[[
namespace TaskTipsBuilder
{
	enum
	{
		start = 1,
		doing = 2,
		stop = 3,
	};
}

enum QuestLine
{
	line_Invalid = 0,
	line_Main = 1,
	line_Daily = 2,
	line_Honor = 3,
	line_Exp = 4,
	line_Money = 5,
	line_Max,
};

enum QuestState
{
	state_Submited		= 0,
	state_Available		= 1,
	state_Finished		= 2,
	state_NotFinished	= 3,
};
--]]
local taskDescBuilder = {
	start = function(isNewTask)
		g_dispatcherEvent("lua_change", "cb_build_task_desc", "", 1, isNewTask)
	end,

	add = function(text, fontSize, colorID)
		g_dispatcherEvent("lua_change", "cb_build_task_desc", "", 2, text, fontSize, colorID)
	end,

	stop = function(isFinish, index)
		g_dispatcherEvent("lua_change", "cb_build_task_desc", "", 3, isFinish, index)
	end,

	getTaskLine = function(lineID)
		local lineTable = {
			[1] = "[主线]",
			[2] = "[每日]",
			[3] = "[荣誉]",
			[4] = "[经验]",
			[5] = "[财富]",
		}
		return lineTable[lineID] or ""
	end,

	getTaskState = function(state, qid)
		local stateTable = {
			[1] = "(可接)",
			[2] = "(可交)",
			[3] = "(进行中)",
		}
		if (state == 1) then
			local levelRequire = g_get_quest_require_level(qid)
			local level = gdceapon.get_data("hero", "level")
			local rebornID = 110
			local reborn = gdceapon.get_data("hero", "prop_" .. rebornID) or 0
			if (reborn <= 0) then
				if (level < levelRequire) then
					return "(" .. levelRequire .. "级可接)"
				end
			end
		end
		return stateTable[state] or ""
	end,

	getTaskSrcNPC = function(qid)
		local nid = cb_get_quest_src_npc(qid)
		return cb_get_npc_name(nid)
	end,

	getTaskTgtNPC = function(qid)
		local nid = cb_get_quest_tgt_npc(qid)
		return cb_get_npc_name(nid)
	end,
}

cb_build_task_desc = function(lineID, qid, state, datax, datay, dataz, index)
	local fontSize = 16
	local white = 0
	local green = 1
	local yellow = 2
	local T = taskDescBuilder

	if qid == 0 then
		T.start(1)
		T.add("任务内容为空。", fontSize, white)
		T.stop(1, index)
	else
		T.start(1)
		T.add(T.getTaskLine(lineID), fontSize, white)
		T.add(cb_get_quest_name(qid), fontSize, yellow)
		if state == 2 then
			T.add(T.getTaskState(state, qid), fontSize, green)
		else
			T.add(T.getTaskState(state, qid), fontSize, yellow)
		end
		T.stop()

		T.start()
		if state == 1 then
			T.add("接取NPC：", fontSize, white)
			T.add(T.getTaskSrcNPC(qid), fontSize, yellow)
		elseif state == 2 then
			T.add("提交NPC：", fontSize, white)
			T.add(T.getTaskTgtNPC(qid), fontSize, yellow)
		else
			T.add(cb_get_quest_tgt_desc(qid), fontSize, green)

			datay = datay or 0
			local total = cb_get_quest_tgt_data_y(qid)
			if total > 0 then
				T.add("(" .. datay .. "/" .. total .. ")", fontSize, yellow)
			end
		end
		T.stop(1, index)
	end
end
----------------------------------------------
-- scene
cb_get_map_data = function(mapID)
	local data = gdMaps[mapID]
	if not(data) then
		log.error("cb_get_map_data, unknown mapID:", mapID)
	end
	return data
end

cb_get_scene_type = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		return data.type or 0
	end
	return 0
end

cb_get_scene_name = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		return data.name or ""
	end
	return ""
end

g_get_map_mining_flag = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		return data.mine or 0
	end
	return 0
end

g_get_scene_music = function(sceneID)
	local pathHead = "data-a/sound/"
	local pathTail

	local data = cb_get_map_data(sceneID)
	if data then
		pathTail = data.sound
	end

	if (pathTail == nil) or (pathTail == "") or (pathTail == 0) or (pathTail == "0") then
		pathTail = "music_other"
	end

	pathTail = pathTail .. ".mp3"
	return pathHead .. pathTail
end

g_get_scene_pk_red_flag = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		return data.pkred or 1
	end
	return 1
end

g_get_map_sai_ma_chang_flag = function(sceneID)
	if (sceneID == 270) or (sceneID == 271) then
		return 1
	end
	return 0
end

g_get_map_peace_area_cnt = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		local area = data.area
		if (type(area) == "table") then
			return #area
		end
	end
	return 0
end

g_get_map_peace_area_id = function(sceneID, index)
	local data = cb_get_map_data(sceneID)
	if data then
		local area = data.area
		if (type(area) == "table") then
			return area[index] or 0
		end
	end
	return 0
end

g_get_map_hide_in_world_map_flag = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		return data.hideInWorldMap or 0
	end
	return 0
end

g_get_map_monster_count = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		local monsters = data.monsters
		if type(monsters) == "table" then
			return #monsters
		end
	end
	return 0
end

g_get_map_monster_data = function(sceneID, index)
	local data = cb_get_map_data(sceneID)
	if data then
		local monsters = data.monsters
		if type(monsters) == "table" then
			local monster = monsters[index]
			if monster then
				return monster.id or 0, monster.posx or 0, monster.posy or 0
			end
		end
	end
	return 0, 0, 0
end

g_get_map_event_monster_count = function(sceneID)
	local data = gdBossInMap[sceneID]
	if data then
		if type(data) == "table" then
			return #data
		end
	end
	return 0
end

g_get_map_event_monster_data = function(sceneID, index)
	local data = gdBossInMap[sceneID]
	if data then
		if type(data) == "table" then
			local monster = data[index]
			if monster then
				return monster.id or 0, monster.x or 0, monster.y or 0
			end
		end
	end
	return 0, 0, 0
end

g_get_map_cheng_ba_tian_xia_flag = function(sceneID)
	if (sceneID == 220) then
		return 1
	end
	return 0
end

cb_get_scene_prop_key = function(keyName)
	local key = SceneProp[keyName]
	if not(key) then
		key = 0
		log.error("cb_get_scene_prop_key, unknown keyName:", keyName)
	end
	return key
end

cb_get_scene_event_id = function(sceneID)
	local data = cb_get_map_data(sceneID)
	if data then
		return data.eventid or 0
	end
	return 0
end

--[[
namespace CPModuleName
{
	static const std::string SCENE = "scene";
}

namespace CPSceneData
{
	static const std::string PROP_ = "prop_";
}
--]]
cb_get_scene_prop = function(key)
	key = key or 0
	return gdceapon.get_data("scene", "prop_" .. key) or 0
end
--------------------------------------------
-- entity
--[[
namespace CPModuleName
{
	static const std::string HERO = "hero";
}

namespace CPHeroData
{
	// property prefix
	static const std::string PROP_ = "prop_";
}
--]]
cb_get_entity_prop = function(key)
	key = key or 0
	return gdceapon.get_data("hero", "prop_" .. key) or 0
end

-------------------------------------------
-- anim
--[[
namespace AnimType
{
	enum
	{
		null = 0,

		cloth = 1,
		weapon = 2,

		pet = 10,
		npc = 11,
		monster = 12,
		slave = 13,

		effect = 20,
	};
}

namespace AnimState
{
	enum
	{
		idle = 0,
		walk = 1,
		run = 2,
		attack = 4,
		die = 7,

		source = 0,
		middle = 1,
		target = 2,
	};
}

const static int SEX_MALE	= 1;
const static int SEX_FEMALE	= 2;
--]]
local getHorseAnimFolderAndName = {
	[1] = function(id, animState)
		local horseanim = "zm_002"
		if id > 0 then
			local data = cb_get_item_data(id)
			if data then
				horseanim = data.horseanim or horseanim
			end
		elseif id == -2 then
			horseanim = "zf_001"
		end
		return "horse/", horseanim .. "_" .. animState
	end,

}
local getAnimFolderAndName = {
	[1] = function(id, animState)
		local anim = "m_000"
		if id > 0 then
			local data = cb_get_item_data(id)
			if data then
				anim = data.anim or anim
			end
		elseif (-id) == 2 then
			anim = "f_000"
		end
		return "cloth/", anim .. "_" .. animState
	end,

	[2] = function(id, animState)
		local anim = "w_001"
		local data = cb_get_item_data(id)
		if data then
			anim = data.anim or anim
		end
		return "weapon/", anim .. "_" .. animState
	end,
	
	[4] = function(id, animState)-----元神外观
		local anim = "ys1_0"
		local data = cb_get_item_data(id)
		if data then
			anim = data.anim or anim
		end
		return "yuanshen/", anim .. "_" .. animState
	end,

	[10] = function(id, animState)
		local anim = "p_001"
		local data = cb_get_pet_data(id)
		if data then
			anim = data.anim.n or anim
		end
		return "pet/", anim .. "_" .. animState
	end,

	[11] = function(id, animState)
		local anim = "npc_001"
		local data = cb_get_npc_data(id)
		if data then
			anim = data.anim or anim
		end
		return "cloth/", anim
	end,

	[12] = function(id, animState)
		local anim = "g_000"
		local data = cb_get_monster_data(id)
		if data then
			anim = data.anim or anim
		end
		return "cloth/", anim .. "_" .. animState
	end,

	[13] = function(id, animState)
		local anim = "b_00"..(id - 1)
		return "cloth/", anim .. "_" .. animState
	end,

	[20] = function(id, animState)
		local anim = "e_000"
		local data = cb_get_skill_data(id)
		if data then
			local key = "effect_src"
			if animState == 1 then
				key = "effect_mid"
			elseif animState == 2 then
				key = "effect_tgt"
			end
			anim = data[key] or anim
		end
		return "effect/", anim
	end,
}

local getMiniPkgAnimName = function(name)
	name = name or ""
	local head = string.sub(name, 1, -3)
	local tail = string.sub(name, -2)
	for k, v in pairs(gdMiniPkgResMap) do
		if v[head] then
			return v[head] .. tail
		end
	end
	return name
end

g_get_horse_anim_path = function(animType, id, animState)
	animType = animType or 0
	id = id or 0
	animState = animState or 0

	-- mini test
	if gameconf.mini and (gameconf.mini ~= 0) and (animType == 11) then
		id = g_get_npc_default_equip(id)
	end

	local key = animType .. "_" .. id .. "_" .. animState
	local path = getHorseAnimFolderAndName[key]
	if not(path) then
		local pathHead = "data-a/animation/"
		local getFunc = getHorseAnimFolderAndName[animType]
		if getFunc then
			local folder, name = getFunc(id, animState)

			-- mini test
			if gameconf.mini and (gameconf.mini ~= 0) then
				name = getMiniPkgAnimName(name)
			end
			path = pathHead .. folder .. name
			getHorseAnimFolderAndName[key] = path
		else
			log.error("g_get_anim_path, unknown animType:", animType)
			path = ""
		end
	end
	return path
end

g_get_anim_path = function(animType, id, animState)
	animType = animType or 0
	id = id or 0
	animState = animState or 0

	-- mini test
	if gameconf.mini and (gameconf.mini ~= 0) and (animType == 11) then
		id = g_get_npc_default_equip(id)
	end

	local key = animType .. "_" .. id .. "_" .. animState
	local path = getAnimFolderAndName[key]
	if not(path) then
		local pathHead = "data-a/animation/"
		local getFunc = getAnimFolderAndName[animType]
		if getFunc then
			local folder, name = getFunc(id, animState)

			-- mini test
			if gameconf.mini and (gameconf.mini ~= 0) then
				name = getMiniPkgAnimName(name)
			end
			path = pathHead .. folder .. name
			getAnimFolderAndName[key] = path
		else
			log.error("g_get_anim_path, unknown animType:", animType)
			path = ""
		end
	end
	return path
end
------------------------------------------------
-- gene
g_get_gene_data = function(geneID)
	local data = gdGenes[geneID]
	if not(data) then
		log.error("g_get_gene_data, unknown geneID:", geneID)
	end
	return data
end

g_get_gene_icon = function(geneID)
	local data = g_get_gene_data(geneID)
	if data then
		return data.icon or ""
	end
	return ""
end

------------------------------------------------
-- global
g_get_global_game_data = function(key)
	return gdGame[key] or 0
end

------------------------------------------------
-- rich text
local richStringTemp = {}
local colorData = {
	r = {
		r = 255,
		g = 0,
		b = 0,
	},

	g = {
		r = 0,
		g = 255,
		b = 0,
	},

	b = {
		r = 0,
		g = 138,
		b = 232,
	},

	-- 橘红色
	j = {
		r = 253,
		g = 168,
		b = 35,
	},

	y = {
		r = 246,
		g = 255,
		b = 0,
	},

	o = {
		r = 255,
		g = 127,
		b = 0,
	},

	w = {
		r = 255,
		g = 255,
		b = 255,
	},
}

local addRichStringData = function(colorKey, text)
	colorKey = colorKey or "w"
	text = text or ""
	local color = colorData[colorKey]
	if not(color) then
		color = colorData.w
	end

	local data = {}
	data.text = text
	data.color = color
	richStringTemp[#richStringTemp + 1] = data
end

g_init_rich_string_count = function(richString, delimiterL, delimiterR)
	richStringTemp = {}

	local index = 1
	local onMatch = function(k1, key, text, k2)
		if k1 > 1 then
			addRichStringData(w, string.sub(richString, index, k1 - 1))
		end
		addRichStringData(key, text)

		index = k2
	end
	local modeString = "()" .. delimiterL .. "(%a)(.-)" .. delimiterR .. "()"
	string.gsub(richString, modeString, onMatch)
	addRichStringData(nil, string.sub(richString, index, -1))

	return #richStringTemp
end

g_get_rich_string_data = function(index)
	local data = richStringTemp[index]
	if (data and data.color) then
		return data.text or "", data.color.r or 255, data.color.g or 255, data.color.b or 255
	end
	return "", 255, 255, 255
end

-----------------------------------------------
-- dog

local dogNameColor = {
	[1] = {
		r = 0,
		g = 255,
		b = 255,
	},

	[2] = {
		r = 0,
		g = 128,
		b = 255,
	},

	[3] = {
		r = 138,
		g = 215,
		b = 245,
	},

	[4] = {
		r = 60,
		g = 180,
		b = 240,
	},

	[5] = {
		r = 120,
		g = 140,
		b = 250,
	},

	[6] = {
		r = 0,
		g = 120,
		b = 215,
	},

	[7] = {
		r = 20,
		g = 70,
		b = 220,
	},
}
g_get_dog_name_color = function(level)
	local color = dogNameColor[level]
	if color then
		return color.r or 255, color.g or 255, color.b or 255
	end
	return 255, 255, 255
end

-----------------------------------------------
-- shop
g_get_shop_data = function(shopID)
	local data = gdShops[shopID]
	if not(data) then
		log.error("g_get_shop_data, unknown shopID:", shopID)
	end
	return data
end

g_get_guild_shop_item_count = function()
	local data = g_get_shop_data(17)
	if data then
		return data.itemcnt or 0
	end
	return 0
end

g_get_guild_shop_item_data = function(index)
	local data = g_get_shop_data(17)
	if data then
		local items = data.items
		if items then
			local item = items[index]
			if item then
				local price = item.price
				if price then
					return item.sid or 0, price.new or 0, item.level or 0
				end
			end
		end
	end
	return 0, 0, 0
end

g_get_shop_item_price_by_sid = function(sid, buyType)
	local items
	for k, v in pairs(gdShops) do
		if type(v.items) == "table" then
			for kk, vv in pairs(v.items) do
				if (vv.sid == sid) and (vv.buytype == buyType) then
					if (vv.price) then
						return vv.price.new or 0
					end
				end
			end
		end
	end
	return 0
end

--------------------------------------------------
-- gift
g_get_gift_data = function(giftID)
	local data = gdGiftPacks[giftID]
	if not(data) then
		log.error("g_get_gift_data, unknown giftID:", giftID)
	end
	return data
end

g_get_activity_gift_data = function(giftID)
	local data = gdActivityGift[giftID]
	if not(data) then
		log.error("g_get_activity_gift_data, unknown giftID:", giftID)
	end
	return data
end

g_get_activation_gift_item_count = function()
	local data = g_get_gift_data(43)
	if data then
		local items = data.items
		if type(items) == "table" then
			return #items
		end
	end
	return 0
end

g_get_activation_gift_item_data = function(index)
	local data = g_get_gift_data(43)
	if data then
		local items = data.items
		if items then
			local item = items[index]
			if item then
				return item.iid or 0, item.count or 0
			end
		end
	end
	return 0, 0
end

g_get_level_sport_gift_data = function(index)
	local data = g_get_activity_gift_data(10)
	if data then
		local rewards = data.rewards
		if rewards then
			local reward = rewards[index]
			if reward then
				return reward.datax or 0, reward.datay or 0, reward.reborn or 0
			end
		end
	end
	return 0, 0, 0
end

g_get_mount_sport_gift_data = function(index)
	local data = g_get_activity_gift_data(11)
	if data then
		local rewards = data.rewards
		if rewards then
			local reward = rewards[index]
			if reward then
				return reward.datax or 0, reward.datay or 0
			end
		end
	end
	return 0, 0
end

g_get_stone_sport_gift_data = function(index)
	local data = g_get_activity_gift_data(12)
	if data then
		local rewards = data.rewards
		if rewards then
			local reward = rewards[index]
			if reward then
				return reward.datax or 0, reward.datay or 0
			end
		end
	end
	return 0, 0
end

--------------------------------------------------
-- guild
g_get_guild_pray_count = function(gongDianLevel)
	local data = gdGuilddata[gongDianLevel]
	if data then
		return data.praycnt or 0
	end
	return 0
end

g_get_guild_pray_exp = function(level, prayType)
	if level > 70 then
		level = 70
	end
	local data = gdGuildPrayExp[level]
	if data then
		if (prayType == 0) then
			return data.moneyexp or 0
		elseif (prayType == 1) then
			return data.honorexp or 0
		else
			return data.goldexp or 0
		end
	end
	return 0
end

g_get_guild_building_guang_huan = function(IndexID)
    local data = gdGuildGuanghuan[IndexID]
	if not(data) then
	   log.error("g_get_guild_building_guang_huan,unknown IndexID::",IndexID)
	end
	return data.buffdesc,data.time,data.cost,data.name or "errordesc",0,0,"errorname"
end

g_get_guild_building_guang_huan_float_panel = function(IndexID)
    local data = gdGuildGuanghuan[IndexID]
	if not(data) then
	   log.error("g_get_guild_building_guang_huan_float_panel,unknown IndexID::",IndexID)
	end
	return data.time,data.cost,data.name or 0,0,"errorname"
end

g_get_guild_building_guang_huan_item_count = function()
    local data = gdGuildGuanghuan
	if data then
	    return 6
	end
	return 0
end

g_get_guild_building_shen_shou = function()
    local data = 0
		if not(data) then
	    log.error("g_get_guild_building_shen_shou")
	end
	return 3000,40,1,230,1,500000
end

g_get_guild_building_data = function(buildingID)
	local data = gdGuildBuild[buildingID]
	if not(data) then
		log.error("g_get_guild_building_data, unknown buildingID:", buildingID)
	end
	return data
end

g_get_guild_building_name = function(buildingID)
	local data = g_get_guild_building_data(buildingID)
	if data then
		return data.name or ""
	end
	return ""
end

g_get_guild_building_open_level = function(buildingID)
	local data = g_get_guild_building_data(buildingID)
	if data then
		return data.openlvl or 0
	end
	return 0
end

g_get_guild_building_max_level = function(buildingID)
	local data = g_get_guild_building_data(buildingID)
	if data then
		return data.maxlvl or 0
	end
	return 0
end

g_get_guild_building_level_up_data = function(buildingID, level)
	local data = g_get_guild_building_data(buildingID)
	if data then
		local lvlup = data.lvlup
		if lvlup then
			local lvl = lvlup[level]
			if lvl then
				return lvl.upmoney or 0, lvl.uptime or 0
			end
		end
	end
	return 0, 0
end

--------------------------------------------------
-- vip
g_get_vip_data = function(vipLevel, key)
	local data = gdVIP[vipLevel]
	if not(data) then
		log.error("g_get_vip_data, unknown vipLevel:", vipLevel)
		return 0
	end

	return data[key] or 0
end

g_get_vip_desc = function(vipLevel)
	return gdVIPDesc[vipLevel] or ""
end
-------------------------------------------------
-- cd
g_get_clear_cd_cost = function(cdID)
	local data = gdCoolDownData[cdID]
	if data then
		return data.cleangold or 0
	end
	return 0
end

--------------------------------------------------
-- head names
g_get_head_names_data = function(id)
	local data = gdHeadTitle[id]
	if not(data) then
		log.error("g_get_head_names_data, unknown id:", id)
		return 0
	end
	return data
end

g_get_head_names_int_data = function(id, key)
	local data = g_get_head_names_data(id)
	if data then
		return data[key] or 0
	end
	return 0
end

g_get_head_names_str_data = function(id, key)
	local data = g_get_head_names_data(id)
	if data then
		return data[key] or ""
	end
	return ""
end

g_get_head_names_title = function(id, job, gender)
	local data = g_get_head_names_data(id)
	if data then
		local titles = data.title
		if titles then
			if job == 4 then job = 1 end
			local index = 2 * (job - 1) + gender
			return titles[index] or ""
		end
	end
end

g_get_head_names_geneid = function(id, job, gender)
	local data = g_get_head_names_data(id)
	if data then
		local geneids = data.geneid
		if geneids then
			if job == 4 then job = 1 end
			local index = 2 * (job - 1) + gender
			return geneids[index] or 0
		end
	end
end

g_get_head_names_attrstring = function(id,key)
	local data = g_get_head_names_data(id)
	if data then
		local attrstrings = data.attrstring
		if attrstrings then
			return attrstrings[key] or ""
		end
	end
end

g_get_head_names_show_title = function(id, job, gender)
	local data = g_get_head_names_data(id)
	if data then
		local titles = data.showtitle
		if titles then
			if job == 4 then job = 1 end
			local index = 2 * (job - 1) + gender
			return titles[index] or ""
		end
	end
end


g_get_head_names_add_prop_count = function(id)
	local data = g_get_head_names_data(id)
	if data then
		local props = data.attrstring
		if props then
			return #props
		end
	end
	return 0
end

g_get_head_names_count = function()
	return #gdHeadTitle
end


--------------------------------------------------
g_guild_building_tan_xian_count = function(buildingLevel)
    local data = gdGuildTanxian
	if data then
	    local cnt =data.count
		if cnt then
		   local targetcnt = cnt[buildingLevel]
		   if targetcnt then
		       return targetcnt
			end
		end
	end
	return 0
end

--~ get_shop_item_sid = function(IndexID)
--~     local data = gdShops[1]
--~ 	if data then
--~ 	   local items = data.items
--~ 		if items then
--~ 			local item = items[IndexID]
--~ 			if item then
--~ 			    return item.sid
--~ 			end
--~ 		end
--~ 		return 0
--~ 	end
--~ end


g_activity_gift_count = function (n)
		local count = 0
	for k,_ in pairs(gdRepayReward) do
		if k > n and k< n+1000 then
			count = count +1
		end
	end
	return count
end

g_check_username = function(username)
    local x,y = string.find(username,"[A-Za-z0-9%.%%%+%-%@]+")
    if x==1 and y==#username then
        return 1
    end
    return 0
end

g_get_bosslvl_byname = function(bossname)
	if not bossname then
		return Error.Success
	end
	local id
	for _,v in pairs(gdMonsters) do
		if v.name == bossname then
			id = v.id
			break
		end
	end
	local gu = gdMonsters[id]
	if gu then
		return gu.lvl
	end
end

g_get_enhance_attribute_size = function()
	return #gdEnhanceAttribute
end

