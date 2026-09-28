--------------------------------------------------
--[[
实现模块
--]]
local get_layout_data = function(moduleName, pathTable)
	local data = nil
	if type(pathTable) == "table" then
		data = _G["layout_" .. moduleName]
		for k, v in ipairs(pathTable) do
			if data then
				data = data[v]
			else
				break;
			end
		end
	end
	return data
end
-------------------------------------------------
-------------------------------------------------
--[[
接口模块
--]]

get_layout_int = function(moduleName, key)
	local int = get_layout_data(moduleName, { "int", key})
	return int or 0
end

get_layout_float = function(moduleName, key)
	local float = get_layout_data(moduleName, { "float", key})
	return float or 0
end

get_layout_string = function(moduleName, key)
	local str = get_layout_data(moduleName, { "str", key})
	return str or ""
end

get_layout_point = function(moduleName, key)
	local x = get_layout_data(moduleName, { "point", key, "x"})
	local y = get_layout_data(moduleName, { "point", key, "y"})
	return x or 0, y or 0
end

get_layout_size = function(moduleName, key)
	local x = get_layout_data(moduleName, { "size", key, "w"})
	local y = get_layout_data(moduleName, { "size", key, "h"})
	return x or 0, y or 0
end

get_layout_color = function(moduleName, key)
	local r = get_layout_data(moduleName, { "color", key, "r"})
	local g = get_layout_data(moduleName, { "color", key, "g"})
	local b = get_layout_data(moduleName, { "color", key, "b"})
	return r or 255, g or 255, b or 255
end

get_layout_rect = function(moduleName, key)
	local x = get_layout_data(moduleName, { "rect", key, "x"})
	local y = get_layout_data(moduleName, { "rect", key, "y"})
	local w = get_layout_data(moduleName, { "rect", key, "w"})
	local h = get_layout_data(moduleName, { "rect", key, "h"})
	return x or 0, y or 0, w or 0, h or 0
end

get_layout_sprite = function(moduleName, key)
	local path = get_layout_data(moduleName, { "sprite", key, "path"})
	local fx = get_layout_data(moduleName, { "sprite", key, "fx"})
	local fy = get_layout_data(moduleName, { "sprite", key, "fy"})
	local ax = get_layout_data(moduleName, { "sprite", key, "ax"})
	local ay = get_layout_data(moduleName, { "sprite", key, "ay"})
	local x = get_layout_data(moduleName, { "sprite", key, "x"})
	local y = get_layout_data(moduleName, { "sprite", key, "y"})
	return path or "", fx or 0, fy or 0, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_menu_item_img = function(moduleName, key)
	local norm = get_layout_data(moduleName, { "menuItemImg", key, "norm"})
	local sel = get_layout_data(moduleName, { "menuItemImg", key, "sel"})
	local dis = get_layout_data(moduleName, { "menuItemImg", key, "dis"})
	local fx = get_layout_data(moduleName, { "menuItemImg", key, "fx"})
	local fy = get_layout_data(moduleName, { "menuItemImg", key, "fy"})
	local ax = get_layout_data(moduleName, { "menuItemImg", key, "ax"})
	local ay = get_layout_data(moduleName, { "menuItemImg", key, "ay"})
	local x = get_layout_data(moduleName, { "menuItemImg", key, "x"})
	local y = get_layout_data(moduleName, { "menuItemImg", key, "y"})
	return norm or "", sel or "", dis or "", fx or 0, fy or 0, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_menu_item_font = function(moduleName, key)
	local text = get_layout_data(moduleName, { "menuItemFont", key, "text"})
	local font = get_layout_data(moduleName, { "menuItemFont", key, "font"})
	local size = get_layout_data(moduleName, { "menuItemFont", key, "size"})
	local r = get_layout_data(moduleName, { "menuItemFont", key, "r"})
	local g = get_layout_data(moduleName, { "menuItemFont", key, "g"})
	local b = get_layout_data(moduleName, { "menuItemFont", key, "b"})
	local ax = get_layout_data(moduleName, { "menuItemFont", key, "ax"})
	local ay = get_layout_data(moduleName, { "menuItemFont", key, "ay"})
	local x = get_layout_data(moduleName, { "menuItemFont", key, "x"})
	local y = get_layout_data(moduleName, { "menuItemFont", key, "y"})
	return text or "", font or "", size or 0, r or 255, g or 255, b or 255, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_label = function(moduleName, key)
	local text = get_layout_data(moduleName, { "label", key, "text"})
	local font = get_layout_data(moduleName, { "label", key, "font"})
	local size = get_layout_data(moduleName, { "label", key, "size"})
	local align = get_layout_data(moduleName, { "label", key, "align"})
	local w = get_layout_data(moduleName, { "label", key, "w"})
	local h = get_layout_data(moduleName, { "label", key, "h"})
	local r = get_layout_data(moduleName, { "label", key, "r"})
	local g = get_layout_data(moduleName, { "label", key, "g"})
	local b = get_layout_data(moduleName, { "label", key, "b"})
	local ax = get_layout_data(moduleName, { "label", key, "ax"})
	local ay = get_layout_data(moduleName, { "label", key, "ay"})
	local x = get_layout_data(moduleName, { "label", key, "x"})
	local y = get_layout_data(moduleName, { "label", key, "y"})
	return text or "", font or "", size or 0, align or 1, w or 0, h or 0, r or 255, g or 255, b or 255, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_scale_sprite = function(moduleName, key)
	local path = get_layout_data(moduleName, { "scaleSprite", key, "path"})
	local w = get_layout_data(moduleName, { "scaleSprite", key, "w"})
	local h = get_layout_data(moduleName, { "scaleSprite", key, "h"})
	local ax = get_layout_data(moduleName, { "scaleSprite", key, "ax"})
	local ay = get_layout_data(moduleName, { "scaleSprite", key, "ay"})
	local x = get_layout_data(moduleName, { "scaleSprite", key, "x"})
	local y = get_layout_data(moduleName, { "scaleSprite", key, "y"})
	return path or "", w or 0, h or 0, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_edit_box = function(moduleName, key)
	local path = get_layout_data(moduleName, { "editBox", key, "path"})
	local lenmax = get_layout_data(moduleName, { "editBox", key, "lenmax"})
	local text = get_layout_data(moduleName, { "editBox", key, "text"})
	local font = get_layout_data(moduleName, { "editBox", key, "font"})
	local size = get_layout_data(moduleName, { "editBox", key, "size"})
	local r = get_layout_data(moduleName, { "editBox", key, "r"})
	local g = get_layout_data(moduleName, { "editBox", key, "g"})
	local b = get_layout_data(moduleName, { "editBox", key, "b"})
	local w = get_layout_data(moduleName, { "editBox", key, "w"})
	local h = get_layout_data(moduleName, { "editBox", key, "h"})
	local ax = get_layout_data(moduleName, { "editBox", key, "ax"})
	local ay = get_layout_data(moduleName, { "editBox", key, "ay"})
	local x = get_layout_data(moduleName, { "editBox", key, "x"})
	local y = get_layout_data(moduleName, { "editBox", key, "y"})
	return path or "", lenmax or 0, text or "", font or "", size or 0, r or 255, g or 255, b or 255, w or 0, h or 0, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_menu_item_label_image = function(moduleName, key)
	local norm = get_layout_data(moduleName, { "menuItemLabelImg", key, "norm"})
	local sel = get_layout_data(moduleName, { "menuItemLabelImg", key, "sel"})
	local dis = get_layout_data(moduleName, { "menuItemLabelImg", key, "dis"})
	local text = get_layout_data(moduleName, { "menuItemLabelImg", key, "text"})
	local font = get_layout_data(moduleName, { "menuItemLabelImg", key, "font"})
	local size = get_layout_data(moduleName, { "menuItemLabelImg", key, "size"})
	local r = get_layout_data(moduleName, { "menuItemLabelImg", key, "r"})
	local g = get_layout_data(moduleName, { "menuItemLabelImg", key, "g"})
	local b = get_layout_data(moduleName, { "menuItemLabelImg", key, "b"})
	local w = get_layout_data(moduleName, { "menuItemLabelImg", key, "w"})
	local h = get_layout_data(moduleName, { "menuItemLabelImg", key, "h"})
	local ax = get_layout_data(moduleName, { "menuItemLabelImg", key, "ax"})
	local ay = get_layout_data(moduleName, { "menuItemLabelImg", key, "ay"})
	local x = get_layout_data(moduleName, { "menuItemLabelImg", key, "x"})
	local y = get_layout_data(moduleName, { "menuItemLabelImg", key, "y"})
	return norm or "", sel or "", dis or "", text or "", font or "", size or 0, r or 255, g or 255, b or 255, w or 0, h or 0, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_check_box = function(moduleName, key)
	local norm = get_layout_data(moduleName, { "checkBox", key, "norm"})
	local sel = get_layout_data(moduleName, { "checkBox", key, "sel"})
	local dis = get_layout_data(moduleName, { "checkBox", key, "dis"})
	local flag = get_layout_data(moduleName, { "checkBox", key, "flag"})
	local text = get_layout_data(moduleName, { "checkBox", key, "text"})
	local font = get_layout_data(moduleName, { "checkBox", key, "font"})
	local size = get_layout_data(moduleName, { "checkBox", key, "size"})
	local r = get_layout_data(moduleName, { "checkBox", key, "r"})
	local g = get_layout_data(moduleName, { "checkBox", key, "g"})
	local b = get_layout_data(moduleName, { "checkBox", key, "b"})
	local ax = get_layout_data(moduleName, { "checkBox", key, "ax"})
	local ay = get_layout_data(moduleName, { "checkBox", key, "ay"})
	local x = get_layout_data(moduleName, { "checkBox", key, "x"})
	local y = get_layout_data(moduleName, { "checkBox", key, "y"})
	return norm or "", sel or "", dis or "", flag or "", text or "", font or "", size or 0, r or 255, g or 255, b or 255, ax or 0.5, ay or 0.5, x or 0, y or 0
end

get_layout_combo_box = function(moduleName, key)
	local norm = get_layout_data(moduleName, { "comboBox", key, "norm"})
	local sel = get_layout_data(moduleName, { "comboBox", key, "sel"})
	local flag = get_layout_data(moduleName, { "comboBox", key, "flag"})
	local font = get_layout_data(moduleName, { "comboBox", key, "font"})
	local size = get_layout_data(moduleName, { "comboBox", key, "size"})
	local r = get_layout_data(moduleName, { "comboBox", key, "r"})
	local g = get_layout_data(moduleName, { "comboBox", key, "g"})
	local b = get_layout_data(moduleName, { "comboBox", key, "b"})
	local ax = get_layout_data(moduleName, { "comboBox", key, "ax"})
	local ay = get_layout_data(moduleName, { "comboBox", key, "ay"})
	local x = get_layout_data(moduleName, { "comboBox", key, "x"})
	local y = get_layout_data(moduleName, { "comboBox", key, "y"})
	return norm or "", sel or "", flag or "", font or "", size or 0, r or 255, g or 255, b or 255, ax or 0.5, ay or 0.5, x or 0, y or 0
end
----------------------------------------------------
