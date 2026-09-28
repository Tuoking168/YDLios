--[[
服装、武器、翅膀效果测试
使用说明：
1.创建新角色。

2.替换对应资源文件，其中，
衣服：data-a\animation\cloth
武器：data-a\animation\weapon
翅膀：data-a\animation\weapon

3.修改以下相应动画名称，保存后，在游戏中执行命令：
load

4.穿上装备。
----------------------------------------------------]]
-- 动画名称修改处

-- 衣服
local cloth = "m_001"

-- 武器
local weapon = "w_001"

-- 翅膀
local wings = "c_000"


-------------------------------------------------------
-------------------------------------------------------
gdItems[70000].anim = cloth
gdItems[70001].anim = cloth
gdItems[70002].anim = weapon
gdItems[80000].anim = wings

-------------------------------------------------------
-------------------------------------------------------
local send_cmd = function(cmdTable)
	if type(cmdTable) == "table" then
		for k, v in pairs(cmdTable) do
			g_dispatcherEvent("lua_change", "send_cmd", "CommandPanel", v)
		end
	end
end

local reload_layout = function()
	reload_script_data("data-a/layout")
end

local cmdTable = {
	"al 30",
	"ai 70000",
	"ai 70001",
	"ai 70002",
	"ai 80000",
}

--send_cmd(cmdTable)
--reload_layout()
