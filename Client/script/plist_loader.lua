local plistData = {
	common = {
		"ui/common/common.plist",
	},

	welcome = {
		"ui/login/channel.plist",
	},

	login = {
		"ui/login/login1.plist",
		"ui/login/login2.plist",
	},

	loading = {
		"ui/login/loading.plist",
	},

	main = {
		"ui/gameui/bgimg1.plist",
		"ui/gameui/bgimg2.plist",
		"ui/gameui/bgimg3.plist",
		"ui/gameui/btnimg1.plist",
		"ui/gameui/btnimg2.plist",
		"ui/gameui/labelimg.plist",
		"ui/gameui/skill_icon.plist",
		"ui/gameui/wordimg.plist",
	},
}

get_plist_data = function(key)
	key = key or ""
	local data = plistData[key]
	if not(data) then
		log.error("get_plist_data failed, unknown key:", key)
	end
	return data
end

get_plist_cnt = function(key)
	local data = get_plist_data(key)
	if data then
		return #data
	end
	return 0
end

get_plist_file = function(key, index)
	local data = get_plist_data(key)
	if data then
		return data[index] or ""
	end
	return ""
end
