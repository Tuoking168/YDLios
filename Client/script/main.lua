
gdServer = false
gdQuestLineBegin ={}

function disableTableNewIndexing(t)
	local mt = {
		__index = function(t, k)
			print("###try to access index: ", k)
			index_forbidden()
		end,

		__newindex  = function(t, k, v)
			print("###try to add new index: ", k)
			index_forbidden()
		end,
	}

	setmetatable(t, mt)
end

init_table_safely = function(inTable)
	if not(type(inTable) == "table") then
		inTable = {}
	end
	return inTable
end

--
--	data_list 用全局变量是为了客户端数据脚本编译用的
--
data_list =
{
	'definition',
	'script_definition',
	'area_checker',
	'event_data',
	'item_data',
	'item_data_ex',
	'gene_data',
	'skill_data',
	'loot_data',
	'monster_data',
	'npc_data',
	'quest_data',
	'quest_data_ex',
	'maps_data',
	'shops_data',
	'pet_data',
	'tips_data',
	'attribute_data',
	'guild_data',
	'honor_data',
	'emigrated_data',
	'global_game_data',
	'sprider_data',
	'options_data',
	'bigcontent_data',
	'smallsecretary_data',
	'activitygift_data',
	'giftpacks_data',
	'monstermap_data',
	'effect_data',
	'random_tips',
	'rewardex_data',
	'rubish_data',
	'vip_data',
	'anim_order_data',
	'headtitile_data',
	'special_reborn_item',
	'copynotify_data',
	'mini_pkg_res_map',
	'combinedserver_data',
	'ActivityCfgVer',
}

local script_list =
{
	'name_data',
	'plist_loader',
	'common_fun',
	'parse_prop',
	'npc_fun',
	'notification',
	'tasktips',
	'layer_data',
	'pet_data_fun',
	'game_module_fun',
	'guide_fun',
	'event_listener',
	'layout_fun',
	'minimap',
	'activity_func',
	'chat_func',
	'sound_loader',
	'init_data',
	'filter_data',
	'func_data',
	'itemspecial_data',
	'__record', --- Test Msg Net Work using need remove !
}

-- layout
local layout_list = {
	"layout",
	"layout_activity",
	"layout_chat",
	"layout_common",
	"layout_guide",
	"layout_guild",
	"layout_loading",
	"layout_login",
	"layout_main_ui",
	"layout_map",
	"layout_notification",
	"layout_social",
	"layout_task",
	"layout_team",
	"layout_vip",
	"layout_design",
}

local load_layout = function()
	for k,v in pairs(layout_list) do
		require("layout/" .. v)
		log.info("Success to load " .. v .. "<layout>")
	end
end

local load_game_conf = function()
	require("data-a/gameconf")
	log.info("Success to load game config data")
end

local load_anim_frames = function()
	require("data-a/animframes_data")
	log.info("Success to load anim images cnt data")
end

local load_client_data = function()
	for i=1,#data_list do
		require ("data/" .. data_list[i])
		log.info("Success to load " .. data_list[i])
	end

	for k,v in pairs(script_list) do
		require("script/" .. v)
		log.info("Success to load " .. v .. "<functions>")
	end
end


--
-- reload
--
reload_script_data = function(path)
	if type(path) == "string" then
		package.loaded[path] = false
		require(path)
	end
end

reload_client_data = function()
	for k,v in pairs(layout_list) do
		reload_script_data("layout/" .. v)
		log.info("Success to reload " .. v .. "<layout>")
	end

	for k, v in pairs(data_list) do
		reload_script_data("data/" .. v)
		log.info("Success to reload " .. v)
	end

	for k,v in pairs(script_list) do
		reload_script_data("script/" .. v)
		log.info("Success to reload " .. v .. "<functions>")
	end
end

--
-- init
--
main_initialize = function()
	--
	-- Begin to load data
	--
	load_layout()
	load_game_conf()
	load_anim_frames()
	load_client_data()

	--
	-- Begin to init random seed
	--
	math.randomseed(os.time())
end
