
local itemCanFastUse = {
	30021,
	30023,
	30022,
	30025,
	30024,
	30046,	-- apple
	30020,	-- lucky water
}

ItemCheckCanFastUse = function(sid)
	for k,v in pairs(itemCanFastUse) do
		if v==sid then
			return true
		end
	end

	return false
end


------------------------------------------------------------转生锻造特殊


local itemSpecialReborn = {
	60276,
	60277,
	60278,
	60279,
	60280,
	60281,
	60282,
	60283,
	60284,

}

ItemCheckSpecialReborn = function(sid)
	for k,v in pairs(itemSpecialReborn) do
		if v==sid then
			return true
		end
	end

	return false
end


-------------------------------------------------------垃圾装备

ItemCheckRubish = function(sid)
	for k,v in pairs(gdRubishEquipResList) do
		if v and v==sid then
			return true
		end
	end

	return false
end


-------------------------------------------------------------装备升级

local itemSpecialUpgrade = {
	60180,
    60181,
    60182,
    60183,
    60184,
    60185,
    60186,
    60187,
    60188,
    60189,

}

ItemCheckSpecialUpgrade = function(sid)
	for k,v in pairs(itemSpecialUpgrade) do
		if v==sid then
			return true
		end
	end

	return false
end


----------------------------------------------------------------宠物蛋信息

local itemPetDesc = {
	[38000] = -1,
	[38001] = -2,
	[38003] = -3,

}

ItemCheckPetDesc = function(sid)
	if itemPetDesc[sid] then
		return itemPetDesc[sid]
	end
	return 0
end

local itemPetSid = {
	[-1] = 10000,
	[-2] = 10001,
	[-3] = 10003,

}
ItemCheckPetSid = function(sid)
	if itemPetSid[sid] then
		return itemPetSid[sid]
	end
	return 0
end



---------------------------------------------------------------批量使用功能的物品


local itemSpecialBatchedUsing = {

	30000,
	30001,
	30002,
	30003,
	30004,
	30005,
	30054,
	30055,
	30056,
	30057,
	30058,
	30059,
	30060,
	30061,
	30070,
	30071,
	30158,
	30160,
	30161,
	30162,
	30163,
	30164,
	30165,
	30166,
	30189,
	30190,
	30191,
	30192,
	30206,
	30207,
	30208,
	30209,
	30210,
	30299,
	30091,
	30094,
	30250,
	30251,
	30252,
	30253,
	30254,
	30255,
	30256,
	30257,
	30092,--灵爵
}

ItemCheckSpecialBatchedUsing = function(sid)
	for k,v in pairs(itemSpecialBatchedUsing) do
		if v==sid then
			return true
		end
	end

	return false
end

------------------------------------------------------------几件特殊的翅膀合成

itemSpecialMerged = {
	80012,
	80013,
	80000,
}

ItemCheckSpecialMerge = function(sid)
	for k,v in pairs(itemSpecialMerged) do
		if v==sid then
			return true
		end
	end

	return false
end

getitemspecialMergeLength = function()
return #itemSpecialMerged
end

-----------------------------------------------------------套装 百搭加成
checkBaiDa = function(suitid,itemtype)
	if not suitid or not itemtype then
		return false
	end
	local t_suit = {}
    for k,v in pairs(gdItems) do
--[[		if v.suite_id and v.suite_id == suitid  then
			if v.type and v.type == itemtype then
				log.info("==============================",v.type,itemtype)
				return true
			else
				return false
			end
		end]]--
		if v.suite_id and v.suite_id >0 and v.suite_id < 99 then
			if v.type and v.type >0 then
				local t = {v.suite_id,v.type }
				table.insert(t_suit,t)
			end
		end
    end
	for k,v in ipairs(t_suit) do
		if v[1] == suitid and v[2] == itemtype then
			return true
		end
	end
	return false
end

