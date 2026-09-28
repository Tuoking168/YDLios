
local toIDTable = function(idString)
	local t = {}
	local onMatch = function(id)
		t[#t + 1] = tonumber(id)
	end
	string.gsub(idString, "(%d+)", onMatch)
	return t
end

gdChatBuilderHelper = {
	start = function(dispatcher)
		dispatcher(1)
	end,

	stop = function(dispatcher, chatType)
		dispatcher(2, chatType)
	end,

	sendLabel = function(dispatcher, chatType, text)
		if string.len(text) > 0 then
			dispatcher(3, chatType, text)
		end
	end,

	sendChatText = function(dispatcher, chatType, chatText)
		chatText = chatText or ""

		local chatModule = "chat"
		local commonModule = "common"
		local analysisHandler = {
			emoticons = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(4, chatType, "emoticons" .. id, chatModule)
			end,

			item = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(7, chatType, idTable[1], idTable[2], idTable[3])
			end,

			scene = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(8, chatType, idTable[1], idTable[2], idTable[3])
			end,

			npc = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(9, chatType, idTable[1], idTable[2], idTable[3])
			end,

			monster = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(10, chatType, idTable[1], idTable[2], idTable[3])
			end,

			activity = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(11, chatType, idTable[1], idTable[2], idTable[3])
			end,

			position = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(12, chatType, idTable[1], idTable[2], idTable[3])
			end,

			player = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(5, chatType, s, idTable[1])
			end,

			team = function(id, s)
				local idTable = toIDTable(id)
				dispatcher(13, chatType, "“同意”", idTable[1])
			end,
		}

		--
		local index = 1
		local onMatch = function(k1, key, id, s, k2)
			if k1 > 1 then
				gdChatBuilderHelper.sendLabel(dispatcher, chatType, string.sub(chatText, index, k1 - 1))
			end

			local handler = analysisHandler[key]
			if handler then
				handler(id, s)
			end

			index = k2
		end
		string.gsub(chatText, "()%[%s*(%a+)%s*:%s*([%d, ]+)(.-)%s*%]()", onMatch)
		gdChatBuilderHelper.sendLabel(dispatcher, chatType, string.sub(chatText, index, -1))
	end,
}

cb_build_chat_msg = function(chatType, pid, playerName, gender, vipLevel, chatText, dispatcher)
	chatType = chatType or 0
	local chatModule = "chat"
	local commonModule = "common"
	local T = gdChatBuilderHelper

	dispatcher = dispatcher or function(value1, value2, value3, value4, value5)
		g_dispatcherEvent("lua_change", "cb_build_chat_msg", "", value1, value2, value3, value4, value5)
	end

	-- start
	T.start(dispatcher)

	-- channel
	local channel = get_layout_string(chatModule, "channelHead") .. get_layout_string(chatModule, "channel" .. chatType) .. get_layout_string(chatModule, "channelTail")
	dispatcher(3, chatType, channel)

	-- player info
	if (chatType == 6) or (chatType == 8) then
		if (pid < 0) then
			T.sendLabel(dispatcher, chatType, "您对")
		end
	end

	if (chatType ~= 1) and string.len(playerName) > 0 then
		if (chatType == 8) then
			dispatcher(4, chatType, "logo", "chat")

			-- player name
			dispatcher(20, chatType, playerName, pid)
		else
			-- player name
			dispatcher(5, chatType, playerName, pid)

			-- player gender
			local genderIcon = get_layout_string(chatModule, "boy")
			if (gender == 2) then
				genderIcon = get_layout_string(chatModule, "girl")
			end
			dispatcher(6, chatType, genderIcon)

			-- vip level
			if vipLevel > 0 then
				dispatcher(4, chatType, "vip" .. vipLevel, commonModule)
			end
		end
	end

	if (chatType == 6) or (chatType == 8) then
		if (pid < 0) then
			T.sendLabel(dispatcher, chatType, "说")
		else
			T.sendLabel(dispatcher, chatType, "对您说")
		end
	end

	-- text
	chatText = chatText or ""
	T.sendChatText(dispatcher, chatType, ": " .. chatText)

	-- stop
	T.stop(dispatcher, chatType)
end

cb_build_mini_chat_msg = function(chatType, pid, playerName, gender, vipLevel, chatText)
	local dispatcher = function(value1, value2, value3, value4, value5)
		g_dispatcherEvent("lua_change", "cb_build_mini_chat_msg", "", value1, value2, value3, value4, value5)
	end
	cb_build_chat_msg(chatType, pid, playerName, gender, vipLevel, chatText, dispatcher)
end

cb_test_chat_send_item = function(chatText)
	local errcode = 0
	local dispatcher = function(value1, value2, value3, value4, value5)
		if (value1 == 7) then
			local sid = Items.getItemSID(value5) or 0
			if (sid <= 0) or (sid ~= value3) then
				errcode = 1
			end
		end
	end
	gdChatBuilderHelper.sendChatText(dispatcher, 0, chatText)
	return errcode
end

-------------------------------------------------------------------------
-- top note msg

local topNoteMsgBuilder = {
	[3] = function(unused, data1, data2, data3)
		return "{y" .. data1 .. "}"
	end,

	[5] = function(unused, data1, data2, data3)
		return "{b" .. data1 .. "}"
	end,

	[7] = function(unused, data1, data2, data3)
		local name = g_get_item_name(data1)
		return "{y[" .. name .. "]}"
	end,

	[8] = function(unused, data1, data2, data3)
		local name = cb_get_scene_name(data1)
		return "{b" .. name .. "}"
	end,

	[9] = function(unused, data1, data2, data3)
		local name = cb_get_npc_name(data1)
		return "{y" .. name .. "}"
	end,

	[10] = function(unused, data1, data2, data3)
		local name = g_get_monster_name(data1)
		return "{g" .. name .. "}"
	end,

	[11] = function(unused, data1, data2, data3)
		local name = get_activity_name(data1)
		return "{y" .. name .. "}"
	end,

	[12] = function(unused, data1, data2, data3)
		return "{w(" .. data1 .. "," .. data2 .. ")}"
	end,
}
cb_convert_top_note_msg = function(baseString)
	local ret = ""
	local dispatcher = function(value1, value2, value3, value4, value5)
		local func = topNoteMsgBuilder[value1]
		if func then
			ret = ret .. func(value2, value3, value4, value5)
		end
	end
	gdChatBuilderHelper.sendChatText(dispatcher, 0, baseString)
	return ret
end

-------------------------------------------------------------------------
