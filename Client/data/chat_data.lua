if not (type(gdChatRules)=="table") then
	gdChatRules = {}
end

local EP = EntityProp

gdChatRules = {
	-- system
	[1] = {

	},
	-- world
	[2] = {
		--针对小于这个级别的玩家
		level = 42,
		--记录最后发言的语句数
		datax = 5,
		--多少次相同即梦游言
		datay = 7,
		dataz = 0,
		chatIsAllowed = function(entity, data, extra, datax, datay, dataz)
			local same = entity:getChatStatistics(2, datax)
			if same and same >= datay then
				return Error.PlayerNotAllowChat
			end
			return Error.Success
		end,
	},
	-- bearby
	[3] = {
		--针对小于这个级别的玩家
		level = 42,
		--记录最后发言的语句数
		datax = 5,
		--多少次相同即梦游言
		datay = 7,
		dataz = 0,
		chatIsAllowed = function(entity, data, extra, datax, datay, dataz)
			local same = entity:getChatStatistics(3, datax)
			if same and same >= datay then
				return Error.PlayerNotAllowChat
			end
			return Error.Success
		end,
	},
	-- group
	[4] = {

	},
	-- guild
	[5] = {

	},
	-- private
	[6] = {
		--针对小于这个级别的玩家
		level = 32,
		--在多少秒内计算
		datax = 60,
		--在上述时间内与超过这个数量的人私聊即梦游言
		datay = 6,
		dataz = 0,
		chatIsAllowed = function(entity, data, extra, datax, datay, dataz)
			local count = entity:getPrivateChatPartnerCount(datax)
			if count and count >= datay then
				return Error.PlayerNotAllowChat
			end
			return Error.Success
		end,
	},
	-- horn
	[7] = {

	},
	-- gm
	[8] = {

	},
}

function gdChatRules.chatIsAllowed(entity, channel, data, extra)
	local rule = gdChatRules[channel]
	if rule and type(rule) == "table" and rule.level then
		local level = entity:getLevel()
		if level >= rule.level then
			return Error.Success
		end
		local now = os.time()
		local lastUpgradeTime = entity:getProps(EP.attr_level_change_time)
		local duration = now - lastUpgradeTime
		if (level >= 15 and level < 20 and duration >= 120) or (level >= 20 and level < 30 and duration >= 240) then
			if entity:getLastChatAmount(2, 60) >= 2 or entity:getLastChatAmount(3, 60) >= 40 then
				return Error.PlayerNotAllowChat
			end
		end
		if rule.chatIsAllowed then
			return rule.chatIsAllowed(entity, data, extra, rule.datax, rule.datay, rule.dataz)
		end
	end
	-- Default set to success
	return Error.Success
end
