cpguide = init_table_safely(cpguide)

--[[
namespace CPModuleName
{
	static const std::string GUIDE = "guide";
}

namespace CPGuideData
{
	static const std::string GUIDE_TYPE = "guide_type";

	static const std::string FUNCTION_AREA_X = "function_area_x";
	static const std::string FUNCTION_AREA_Y = "function_area_y";
	static const std::string FUNCTION_AREA_W = "function_area_w";
	static const std::string FUNCTION_AREA_H = "function_area_h";

	static const std::string ARROW_DIRECTION = "arrow_direction";
	static const std::string ARROW_BOARD_W = "arrow_board_w";
	static const std::string ARROW_BOARD_H = "arrow_board_h";
	static const std::string ARROW_BOARD_X = "arrow_board_x";
	static const std::string ARROW_BOARD_Y = "arrow_board_y";
	static const std::string ARROW_NOTE = "arrow_note";

	static const std::string VALUE_1 = "value_1";
	static const std::string VALUE_2 = "value_2";
	static const std::string VALUE_3 = "value_3";
}
--]]

local GDCP = gdceapon

local setGuideData = function(key, data)
	GDCP.set_data("guide", key, data)
end

local getGuideData = function(key)
	return GDCP.get_data("guide", key)
end

local clearGuideData = function()
	GDCP.clear_module("guide")
end

local setGuideType = function(guideType)
	setGuideData("guide_type", guideType)
end

local setFunctionArea = function(x, y, w, h)
	setGuideData("function_area_x", x)
	setGuideData("function_area_y", y)
	setGuideData("function_area_w", w)
	setGuideData("function_area_h", h)
end

local setArrowData = function(direction, w, h, x, y, note)
	setGuideData("arrow_direction", direction)
	setGuideData("arrow_board_w", w)
	setGuideData("arrow_board_h", h)
	setGuideData("arrow_board_x", x)
	setGuideData("arrow_board_y", y)
	setGuideData("arrow_note", note)
end

local setGuideExData = function(data1, data2, data3)
	setGuideData("value_1", data1)
	setGuideData("value_2", data2)
	setGuideData("value_3", data3)
end

local show = function(guideType)
	setGuideType(guideType)
	g_dispatcherEvent("lgc_guide", "cpguide", "GuidePanel", "show")
end

local hide = function(needClear)
	if needClear == nil then
		needClear = true
	end

	if needClear then
		clearGuideData()
	end
	g_dispatcherEvent("lgc_guide", "cpguide", "GuidePanel", "hide")
end

local getMainLineQuest = function()
	local subModu1 = gdceapon.get_data("task", "current_task_list")
	if type(subModu1) == "table" then
		for k, v in gdceapon.pairs_by_keys(subModu1) do
			if v.line == 1 then
				return k, v
			end
		end
	end

	local subModu2 = gdceapon.get_data("task", "access_task_list")
	if type(subModu2) == "table" then
		for k, v in gdceapon.pairs_by_keys(subModu2) do
			if v.line == 1 then
				return k, v
			end
		end
	end
	return 0, nil
end

-----------------------------------------------------------------------
--[[
enum QuestState
{
	state_Submited		= 0,
	state_Available		= 1,
	state_Finished		= 2,
	state_NotFinished	= 3,
};

namespace GuideType
{
	enum
	{
		null = 0,

		welcome = 1,
		to_npc = 2,

		arrow_black = 10,
		arrow_normal = 20,
		arrow_normal_time = 30,
	};
}

namespace GuideArrow
{
	enum
	{
		dir_up = 0,
		dir_left = 1,
		dir_down = 2,
		dir_right = 3,
	};
}
--]]
cpguide.onCPEvent = {}
local GOE = cpguide.onCPEvent
local currentOnCPEvent

local hideAndReset = function(needClear)
	hide(needClear)
	currentOnCPEvent = GOE.normal
end

local showWelcome = function()
	show(1)
	currentOnCPEvent = GOE.welcome
end

local showExitAutoAttack = function()
	setFunctionArea(0, 320, 50, 20)
	setArrowData(1, 120, 60, 160, 330, "点击退出副本")
	show(10)
	currentOnCPEvent = GOE.funcGuide
end

local showToNPC = function()
	show(2)
	currentOnCPEvent = GOE.normal
end

local showStopAutoMove = function()
	show(3)
	currentOnCPEvent = GOE.normal
end

local showTask = function()
	setFunctionArea(4, 254, 185, 56)
	setArrowData(1, 120, 60, 300, 277, "点击接取任务")
	show(10)
	g_dispatcherEvent("ui_open", "guide:showTask", "LeftTipsPanel", 0)
	currentOnCPEvent = GOE.task
end

local showTaskNormal = function()
	setFunctionArea(0, 0, 800, 480)
	setArrowData(1, 120, 60, 300, 277, "点击自动任务")
	show(20)
	g_dispatcherEvent("ui_open", "guide:showTaskNormal", "LeftTipsPanel", 0)
	currentOnCPEvent = GOE.task
end

local showAutoFight = function()
	setGuideExData()
	setFunctionArea(310, 420, 70, 60)
	setArrowData(0, 120, 60, 310, 340, "点击自动战斗")
	show(30)
	currentOnCPEvent = GOE.funcGuide
end

local showNPCTalk = function(state)
	setFunctionArea(543, 74, 90, 42)

	local note = "点击接受任务"
	if state == 2 then
		note = "点击完成任务"
	end
	setArrowData(2, 120, 60, 587, 200, note)
	show(10)
	currentOnCPEvent = GOE.task
end

local showNewEquip = function(itemSID, itemID)
	setGuideExData(itemSID, itemID)
	g_dispatcherEvent("ui_open", "guide:showNewEquip", "GameUI", "NewEquipPanel")
	local qid = getMainLineQuest()
	local level = GDCP.get_data("hero", "level")
	if (itemSID == 70002) and (0 < qid) and (qid <= 20) and (level < 10) then
		setFunctionArea(185, 100, 430, 250)
		setArrowData(3, 120, 60, 225, 126, "点击一键换装")
		show(10)
		currentOnCPEvent = GOE.equip
	end
end

local showNewSkill = function(itemSID)
	local skillID, datay = g_get_item_data_ex(itemSID)
	local data = gdceapon.get_data("hero", "skill_list")
	if type(data) == "table" then
		for k, v in pairs(data) do
			if (k/10 == skillID/10) and (skillID <= k) then
				return
			end
		end
	end

	setGuideExData(itemSID)
	g_dispatcherEvent("ui_open", "guide:showNewEquip", "GameUI", "NewSkillPanel")
	local qid = getMainLineQuest()
	if (0 < qid) and (qid <= 50) then
		setFunctionArea(185, 100, 430, 250)
		setArrowData(3, 120, 60, 225, 126, "点击一键学习")
		show(10)
		currentOnCPEvent = GOE.skill
	end
end

local showNewFuncPre = function(funcName)
	hideAndReset()

	setGuideExData(funcName)
	g_dispatcherEvent("ui_open", "guide:showNewFuncPre", "GameUI", "NewFunctionPanel")

	currentOnCPEvent = GOE.funcPre
end

local showNewFuncConfirm = function()
	setFunctionArea(120, 66, 560, 358)
	setArrowData(3, 100, 60, 235, 95, "点击确定")
	show(10)
	currentOnCPEvent = GOE.funcConfirm
end

local showOpenMainMenu = function()
	setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
	setFunctionArea(0, 406, 88, 74)
	show(10)
	currentOnCPEvent = GOE.openMainMenu
end

local showNewFuncGuide = {
	ji_neng = {
		[1] = function()
			setFunctionArea(608, 440, 50, 30)
			setArrowData(3, 120, 60, 490, 447, "点击开启技能")
			show(10)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(495, 301, 294, 78)
			setArrowData(3, 120, 60, 370, 340, "点击查看技能")
			show(10)
			currentOnCPEvent = GOE.funcGuideEnd
		end,
	},

	chong_wu = {
		[1] = function()
			local step = getGuideData("value_2")
			setGuideExData("chong_wu", step, 38000)
			setFunctionArea(505, 370, 55, 55)
			setArrowData(3, 140, 60, 372, 398, "点击查看宠物蛋")
			show(11)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(272, 22, 78, 32)
			setArrowData(2, 140, 60, 310, 130, "点击使用宠物蛋")
			show(10)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(210, 440, 50, 30)
			setArrowData(0, 160, 60, 235, 350, "点击打开宠物界面")
			show(10)
			currentOnCPEvent = GOE.funcGuide
		end,

		[4] = function()
			setFunctionArea(110, 376, 60, 32)
			setArrowData(0, 140, 60, 143, 286, "点击让宠物出战")
			show(10)
			currentOnCPEvent = GOE.funcGuideEnd
		end,
	},

	zhuang_bei_qiang_hua = {
		[1] = function()
			setFunctionArea(10, 232, 70, 52)
			setArrowData(1, 160, 60, 210, 258, "点击打开强化界面")
			show(10)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(500, 318, 55, 55)
			setArrowData(3, 120, 60, 380, 346, "点击选择装备")
			show(10)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(260, 105, 72, 40)
			setArrowData(3, 120, 60, 140, 125, "点击进行强化")
			show(10)
			currentOnCPEvent = GOE.funcGuideEnd
		end,
	},

	rong_yv = {
		[1] = function()
			setFunctionArea(10, 175, 70, 52)
			setArrowData(1, 160, 60, 210, 201, "点击打开荣誉界面")
			show(10)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(290, 10, 78, 40)
			setArrowData(2, 120, 60, 329, 130, "点击开启祝福")
			show(10)
			currentOnCPEvent = GOE.funcGuideEnd
		end,
	},

	gong_ji_mo_shi = {
		[1] = function()
			setFunctionArea(214, 425, 44, 44)
			setArrowData(0, 160, 60, 236, 330, "点击查看攻击模式")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	zhuang_bei_jian_ding = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 232, 70, 52)
			setArrowData(1, 160, 60, 210, 261, "点击打开强化界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(200, 442, 90, 30)
			setArrowData(0, 160, 60, 245, 353, "点击打开鉴定界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	shi_tu = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 115, 70, 52)
			setArrowData(1, 160, 60, 210, 141, "点击打开社交界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(20, 267, 85, 38)
			setArrowData(1, 160, 60, 235, 285, "点击打开师徒界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	hang_hui = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 58, 70, 52)
			setArrowData(1, 160, 60, 210, 84, "点击打开行会界面")
			show(30)
			currentOnCPEvent = GOE.funcGuideNext
		end,
	},

	mei_ri_hu_song = {
		[1] = function()
			setFunctionArea(470, 420, 60, 58)
			setArrowData(0, 160, 60, 500, 340, "点击打开活动菜单")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(482, 334, 74, 52)
			setArrowData(0, 160, 60, 520, 250, "点击打开每日活跃界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(223, 130, 130, 32)
			setArrowData(2, 160, 60, 270, 235, "点击执行每日护送")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	ban_lv = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 115, 70, 52)
			setArrowData(1, 160, 60, 210, 141, "点击打开社交界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(20, 172, 85, 38)
			setArrowData(1, 160, 60, 235, 190, "点击打开伴侣界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	zhuang_bei_sheng_ji = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 235, 70, 52)
			setArrowData(1, 160, 60, 210, 261, "点击打开强化界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(305, 442, 90, 30)
			setArrowData(0, 160, 60, 350, 353, "点击打开升级界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	hun_shi = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(150, 440, 50, 30)
			setArrowData(0, 160, 60, 175, 350, "点击打开魂石界面")
			show(30)
			currentOnCPEvent = GOE.funcGuideEnd
		end,
	},

	huan_wu_qi_ling = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 235, 70, 52)
			setArrowData(1, 160, 60, 210, 261, "点击打开强化界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(410, 442, 90, 30)
			setArrowData(0, 160, 60, 455, 353, "点击打开启灵界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	he_cheng = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 235, 70, 52)
			setArrowData(1, 160, 60, 210, 261, "点击打开合成界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	shu_xing_zhuan_yi = {
		[1] = function()
			setFunctionArea(0, 406, 88, 74)
			setArrowData(1, 160, 60, 215, 443, "点击打开功能界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[2] = function()
			setFunctionArea(10, 175, 70, 52)
			setArrowData(1, 160, 60, 210, 201, "点击打开强化界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,

		[3] = function()
			setFunctionArea(515, 442, 90, 30)
			setArrowData(0, 160, 60, 560, 353, "点击打开转移界面")
			show(30)
			currentOnCPEvent = GOE.funcGuide
		end,
	},

	zhuan_sheng = nil,
}

local showNewFuncGuideStart = function(funcName)
	local guideList = showNewFuncGuide[funcName]
	if guideList then
		local guide = guideList[1]
		if guide then
			setGuideData("value_2", 1)
			guide()
			return
		end
	end
	hideAndReset()
end

local showContinuesNewFuncGuide = function(funcName)
	hideAndReset()

	setGuideExData(funcName)
	showNewFuncGuideStart(funcName)
end

local showNewGift = function(itemSID)
	local sid = itemSID
	if (sid < 0) then
		sid = -sid
	end
	setGuideExData(sid)
	g_dispatcherEvent("ui_open", "guide:showNewGift", "GameUI", "NewGiftPanel")

	if (itemSID < 0) then
		setFunctionArea(380, 215, 40, 50)
		setArrowData(3, 120, 60, 260, 240, "点击打开礼包")
		show(10)
		currentOnCPEvent = GOE.gift
	end
end

local showNewItemUse = function(itemSID)
	setGuideExData(itemSID)
	g_dispatcherEvent("ui_open", "guide:showNewItemUse", "GameUI", "NewItemUsePanel")
end

local showDungeonNoteIfNeed = function(level)
	for k, v in pairs(gdCopyNotify) do
		if (v.notify_lvl == level) then
			g_dispatcherEvent("ui_open", "guide:showDungeonNoteIfNeed", "GameUI", "CopyNotifyTipPanel", k)
			return
		end
	end
end

--[[
namespace CPEventName
{
	// event from msg
	static const std::string MSG_CHANGE = "msg_change";
	static const std::string MSG_FINISH = "msg_finish";

	// event from ui
	static const std::string UI_CHANGE = "ui_change";
	static const std::string UI_FINISH = "ui_finish";
	static const std::string UI_OPEN = "ui_open";
	static const std::string UI_CLOSE = "ui_close";
	static const std::string UI_NOTIFY = "ui_notify";

	// event from logic
	static const std::string LGC_CHANGE = "lgc_change";
	static const std::string LGC_FINISH = "lgc_finish";
	static const std::string LGC_TIMER = "lgc_timer";
	static const std::string LGC_GUIDE = "lgc_guide";

	// event from lua
	static const std::string LUA_CHANGE = "lua_change";
	static const std::string LUA_FINISH = "lua_finish";
}
--]]

local newGiftBag = {
	[10] = -30006,
	[20] = -30007,
	[30] = 30008,
	[35] = 30009,
	[40] = 30010,
	[45] = 30011,
	[50] = 30012,
	[55] = 30013,
	[60] = 30014,
}
GOE.normal = {
	ui_open = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			local pid = GDCP.get_data("hero", "pid")
			local alreadyEnterGame = GDCP.get_sub_data("userData", "data_depend_pid", pid, "already_enter_game")
			if alreadyEnterGame == 1 then
				local state = GDCP.get_sub_data("task", "access_task_list", 10, "state")
				if (state == 1) then
					showTask()
				else
					local rebornID = 110
					local reborn = GDCP.get_data("hero", "prop_" .. rebornID) or 0
					local level = GDCP.get_data("hero", "level")
					if (reborn == 0) and (level <= 15) then
						local qid = getMainLineQuest()
						if qid > 0 then
							showTaskNormal()
						end
					end
				end

				-- 印象沙皇宫 自动战斗
				local sceneID = tonumber(data1) or 0
				if (sceneID == 1035) then
					showAutoFight()
				end
			else
				g_init_default_setting(pid)
				GDCP.set_sub_data("userData", "data_depend_pid", pid, "already_enter_game", 1)
				local rebornID = 110
				local reborn = GDCP.get_data("hero", "prop_" .. rebornID) or 0
				local level = GDCP.get_data("hero", "level")
				if (reborn == 0) and (level == 1) then
					showWelcome()
				end
			end
		elseif (source == "NPCTalkPanel") then
			local npcID1 = 107
			local npcID2 = 110
			local state1 = GDCP.get_sub_data("task", "access_task_list", 10, "state")
			local state2 = GDCP.get_sub_data("task", "current_task_list", 10, "state")
			if (data1 == npcID1) and (state1 == 1) then
				showNPCTalk(state1)
			elseif (data1 == npcID2) and (state2 == 2) then
				showNPCTalk(state2)
			end
		elseif (source == "GameRole::ExitAutoAttack") then
			showExitAutoAttack()
		end
	end,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,

	ui_change = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GameRole::touchScreenBegin") then
			local rebornID = 110
			local reborn = GDCP.get_data("hero", "prop_" .. rebornID) or 0
			local level = GDCP.get_data("hero", "level") or 1
			if (reborn == 0) and (level <= 15) then
				local qid = getMainLineQuest()
				if qid > 0 then
					showTaskNormal()
				end
			end
		end
	end,

	msg_change = function(source, target, data1, data2, data3, data4, data5)
		if (source == "HandleMessageItemAddNotifyEx") then
			if (target == "pet") or (target == "hunt") then
				return
			end

			local itemSid = data2
			local itemID = data4
			local itemCate = g_get_item_cate(itemSid)
			if itemCate == 1 then
				showNewEquip(itemSid, itemID)
			elseif itemCate == 3 then
				local itemType = g_get_item_type(itemSid)
				if (itemType == 4) then
					local rebornID = 110
					local reborn = GDCP.get_data("hero", "prop_" .. rebornID) or 0
					local level = GDCP.get_data("hero", "level") or 0
					local job = GDCP.get_data("hero", "job") or 0
					local requireReborn, requireLvl = g_get_item_require_level(itemSid)
					local requireJob = g_get_item_require_job(itemSid)
					if ((reborn > requireReborn) or ((reborn == requireReborn) and (level >= requireLvl))) and (job == requireJob) then
						showNewSkill(itemSid)
					end
				end
			end
		elseif (source == "HandleMessageUpdPlayerLvlExpNotify") then
			local rebornID = 110
			local reborn = GDCP.get_data("hero", "prop_" .. rebornID) or 0
			if reborn > 0 then
				return
			end

			local dLevel = data2
			if dLevel > 0 then
				local level = GDCP.get_data("hero", "level")

				local qid = getMainLineQuest()
				if qid > 40 then
					local sid = newGiftBag[level]
					if sid then
						showNewGift(sid)
					end
				end

				local funcName = gdGame.getOpenFunctionName(level)
				if not(funcName == "") then
					showNewFuncPre(funcName)
					-- Save the data for showing next guide
					if (funcName == "hang_hui") then
						local level = GDCP.get_data("hero", "level")
						if (level == 35) then
							nextGuideFunc = "mei_ri_hu_song"
						end
					end
				end

				showDungeonNoteIfNeed(level)

				if (level == 15) then
					g_dispatcherEvent("ui_open", "FuncHandler", "GameUI", "TopWelfarePanel", 1, 0, 0, 1)
				end
			end
		end
	end,
}
currentOnCPEvent = GOE.normal

GOE.welcome = {
	lgc_guide = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GuidePanel::ccTouchBegan") then
			showToNPC()
		end
	end,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,
}

GOE.task = {
	lgc_guide = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GuidePanel::ccTouchBegan") then
			if (data1 == "Yes") then
				hideAndReset()
			end
		end
	end,

	ui_open = function(source, target, data1, data2, data3, data4, data5)
		if (source == "NPCTalkPanel") then
			hideAndReset()
		end
	end,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,

	msg_change = GOE.normal.msg_change,
}

GOE.equip = {
	msg_change = GOE.normal.msg_change,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		elseif (source == "NewEquipPanel::close") then
			showTaskNormal()
		end
	end,
}

GOE.skill = {
	msg_change = GOE.normal.msg_change,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		elseif (source == "NewSkillPanel::close") then
			showNewFuncPre("ji_neng")
		end
	end,
}

GOE.funcPre = {
	ui_open = function(source, target, data1, data2, data3, data4, data5)
		if (source == "NewFunctionPanel::onShowNext") then
			local strongGuide = {
				ji_neng = 1,
				zhuang_bei_qiang_hua = 1,
				rong_yv = 1,
				chong_wu = 1,
			}
			local funcName = getGuideData("value_1")
			local flag = strongGuide[funcName]
			if flag then
				showNewFuncConfirm()
			else
				showNewFuncGuideStart(funcName)
			end
		end
	end,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,
}

GOE.funcConfirm = {
	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		elseif (source == "NewFunctionPanel::close") then
			showOpenMainMenu()
		end
	end,
}

GOE.openMainMenu = {
	lgc_guide = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GuidePanel::ccTouchBegan") then
			if (data1 == "Yes") then
				hide(false)
			end
		end
	end,

	ui_finish = function(source, target, data1, data2, data3, data4, data5)
		if (source == "MainPanel|onEnter") then
			local funcName = getGuideData("value_1")
			showNewFuncGuideStart(funcName)
		end
	end,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,
}

GOE.funcGuide = {
	lgc_guide = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GuidePanel::ccTouchBegan") then
			if (data1 == "Yes") then
				local funcName = getGuideData("value_1")
				local guideList = showNewFuncGuide[funcName]
				if guideList then
					local step = getGuideData("value_2") + 1
					local guide = guideList[step]
					if guide then
						setGuideData("value_2", step)
						guide()
						return
					end
				end
				hideAndReset()
			end
		elseif (source == "GuidePanel::onTimeOut") then
			hideAndReset()
			if nextGuideFunc then
				showContinuesNewFuncGuide(nextGuideFunc)
				nextGuideFunc = nil
			end
		end
	end,

	msg_change = GOE.normal.msg_change,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,

	ui_finish = function(source, target, data1, data2, data3, data4, data5)
		if (source == "MainPanel|onExit") or (source == "GuildPanel::onExit") then
			if nextGuideFunc then
				local level = GDCP.get_data("hero", "level")
				if level == 35 then
					showContinuesNewFuncGuide(nextGuideFunc)
					nextGuideFunc = nil
				end
			end
		end
	end
}

GOE.funcGuideNext = {
	lgc_guide = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GuidePanel::onTimeOut") or ((source == "GuidePanel::ccTouchBegan") and (data1 == "Yes")) then
			hide(false)
		end
	end,
	ui_close = GOE.funcGuide.ui_close,
	ui_finish = GOE.funcGuide.ui_finish,
	msg_change = GOE.funcGuide.msg_change,
}


GOE.funcGuideEnd = {
	lgc_guide = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GuidePanel::ccTouchBegan") then
			if (data1 == "Yes") then
				hide()
			end
		end
	end,

	ui_finish = function(source, target, data1, data2, data3, data4, data5)
		if (source == "MainPanel|onExit") then
			local level = GDCP.get_data("hero", "level")
			if level <= 15 then
				local qid = getMainLineQuest()
				if qid > 0 then
					showTaskNormal()
					return
				end
			end
			hideAndReset()
		end
	end,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,
}

GOE.gift = {
	lgc_guide = function(source, target, data1, data2, data3, data4, data5)
		if (source == "GuidePanel::ccTouchBegan") then
			if (data1 == "Yes") then
				hide()
			end
		end
	end,

	msg_change = GOE.normal.msg_change,

	ui_close = function(source, target, data1, data2, data3, data4, data5)
		if (source == "Game") then
			hideAndReset()
		end
	end,
}

----------------------------------------------------------
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
--]]
cpguide.on_cp_event = function(eventName)
	local handler = currentOnCPEvent[eventName]
	if handler then
		local source = GDCP.get_sub_data("event", eventName, 1, "source") or ""
		local target = GDCP.get_sub_data("event", eventName, 1, "target") or ""
		local data1 = GDCP.get_sub_data("event", eventName, 1, "value_1") or 0
		local data2 = GDCP.get_sub_data("event", eventName, 1, "value_2") or 0
		local data3 = GDCP.get_sub_data("event", eventName, 1, "value_3") or 0
		local data4 = GDCP.get_sub_data("event", eventName, 1, "value_4") or 0
		local data5 = GDCP.get_sub_data("event", eventName, 1, "value_5") or 0
		handler(source, target, data1, data2, data3, data4, data5)
	end
end
-------------------------------------------------------------



















































