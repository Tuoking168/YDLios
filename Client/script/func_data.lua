if not gdFuncData then
	gdFuncData = {}
end

local FP = FuncProp

local openPanel = function(panelName,paneltype,datax,datay,dataz)
	g_dispatcherEvent("ui_open", "FuncHandler", "GameUI", panelName,paneltype,datax,datay,dataz)
end

gdFuncData[FP.team_call] = function(datax,datay,dataz,datas)
	openPanel("FloatPanel",37,FP.team_call,0,0)
end

local useFireworks = function(itemSid)
	g_dispatcherEvent("ui_notify", "useFireworks", "GameUI", 0, itemSid)
end

local itemSwitch = {
	[30144] = function(datay, dataz)
		useFireworks(30144)
	end,
	[30145] = function(datay, dataz)
		useFireworks(30145)
	end,
	[30146] = function(datay, dataz)
		useFireworks(30146)
	end,
	[30147] = function(datay, dataz)
		useFireworks(30147)
	end,
	[30148] = function(datay, dataz)
		useFireworks(30148)
	end,
	[30149] = function(datay, dataz)
		useFireworks(30149)
	end,
	[30150] = function(datay, dataz)
		useFireworks(30150)
	end,
	[30151] = function(datay, dataz)
		useFireworks(30151)
	end,
	[30152] = function(datay, dataz)
		useFireworks(30152)
	end,
	[30153] = function(datay, dataz)
		useFireworks(30153)
	end,
	[30154] = function(datay, dataz)
		useFireworks(30154)
	end,
	[30155] = function(datay, dataz)
		useFireworks(30155)
	end,
	[30156] = function(datay, dataz)
		useFireworks(30156)
	end,


	[40000] = function(datay,dataz)--一级灵石
		 openPanel("MainPanel",4,50,0,0)
	end,
	[40001] = function(datay,dataz)--二级灵石
		 openPanel("MainPanel",4,50,0,0)
	end,
	[40002] = function(datay,dataz)--三级灵石
		 openPanel("MainPanel",4,50,0,0)
	end,
	[40003] = function(datay,dataz)--四级灵石
		 openPanel("MainPanel",4,50,0,0)
	end,
	[40004] = function(datay,dataz)--五级灵石
		 openPanel("MainPanel",4,50,0,0)
	end,
	[40005] = function(datay,dataz)--灵光碎片
		 openPanel("MainPanel",4,53,1,0)
	end,
	[40006] = function(datay,dataz)--清洗碎片
		 openPanel("MainPanel",4,53,1,0)
	end,
	[40007] = function(datay,dataz)--白色羽毛
		 openPanel("MainPanel",4,54,2,0)
	end,
	[40008] = function(datay,dataz)--黑铁
		 openPanel("MainPanel",3,1,1,0)
	end,
	[40009] = function(datay,dataz)--绿宝石
		 openPanel("MainPanel",3,1,1,0)
	end,
	[40010] = function(datay,dataz)--紫晶钻
		 openPanel("MainPanel",3,1,1,0)
	end,
	[40011] = function(datay,dataz)--灵魂石
		 openPanel("MainPanel",3,1,1,0)
	end,
	[41110] = function(datay,dataz)--蓝钻石
		 openPanel("MainPanel",3,1,1,0)
	end,
	[41111] = function(datay,dataz)--紫钻石
		 openPanel("MainPanel",3,1,1,0)
	end,
	[41112] = function(datay,dataz)--橙钻石
		 openPanel("MainPanel",3,1,1,0)
	end,
	[40012] = function(datay,dataz)--保护强化符
		 openPanel("MainPanel",3,1,1,0)
	end,
	[40013] = function(datay,dataz)--翅膀合成符
		 openPanel("MainPanel",4,53,2,0)
	end,
	[40014] = function(datay,dataz)--淬炼晶魄
		 openPanel("MainPanel",3,3,0,0)
	end,
	[40015] = function(datay,dataz)--战神晶魄
		 openPanel("MainPanel",3,3,0,0)
	end,
	[40016] = function(datay,dataz)--足迹晶魄
		 openPanel("MainPanel",3,5,16,0)
	end,
	[40022] = function(datay,dataz)--极品属性清洗符
		 openPanel("MainPanel",3,4,10,0)
	end,
	[40040] = function(datay,dataz)--宠物封印符
		 openPanel("MainPanel",0,12,0,0)
	end,
	[40041] = function(datay,dataz)--清洗丹
		 openPanel("MainPanel",3,2,0,0)
	end,
	[40042] = function(datay,dataz)--鉴定锁
		 openPanel("MainPanel",3,2,0,0)
	end,
	[40043] = function(datay,dataz)--转移神符
		 openPanel("MainPanel",3,4,7,0)
	end,
	[40044] = function(datay,dataz)--极品属性转移符
		 openPanel("MainPanel",3,4,0,0)
	end,
	[40045] = function(datay,dataz)--任务完成符
		 openPanel("MainPanel",1,0,0,0)
	end,
	[40053] = function(datay,dataz)--宠物项圈
		 openPanel("MainPanel",0,12,0,0)
	end,
	[40060] = function(datay,dataz)--鉴定图鉴
		 openPanel("MainPanel",3,2,0,0)
	end,
	[40068] = function(datay,dataz)--背包扩展符
		 openPanel("BagUnlock")
	end,
	[40077] = function(datay,dataz)--凤凰翎
		 openPanel("MainPanel",3,1,14,0)
	end,
	[40132] = function(datay,dataz)--追踪令
		 openPanel("SocialPanel",0,4)
	end,
	[40113] = function(datay,dataz)--召唤兽灵魄
		local job = gdceapon.get_data("hero", "job")
		if (job == 3) then
			local dogCntKey = 291
			local dogCnt = gdceapon.get_data("hero", "prop_" .. dogCntKey)
			if (dogCnt > 0) then
				openPanel("FloatPanel", 12, "3", 0, 0)
				return
			end
		end
		cpnotification.addNote("您还没有召唤兽！", 0)
	end,
	[40116] = function(datay,dataz)--藏宝图
		 openPanel("TreasureHuntPanel")
	end,
	[40125] = function(datay,dataz)--5级完美强化符
		 openPanel("MainPanel",3,1,11,40125)
	end,
	[40126] = function(datay,dataz)--8级完美强化符
		 openPanel("MainPanel",3,1,11,40126)
	end,
	[40127] = function(datay,dataz)--10级完美强化符
		 openPanel("MainPanel",3,1,11,40127)
	end,
	[40138] = function(datay,dataz)--传音喇叭
		openPanel("ChatPanel", 7)
	end,
	[40140] = function(datay,dataz)--宠物进阶属性符
		 openPanel("MainPanel",0,12,0,0)
	end,
	[40141] = function(datay,dataz)--宠物极品属性符
		 openPanel("MainPanel",0,12,0,0)
	end,
	[40143] = function(datay,dataz)--磐龙许愿盒
		 openPanel("PanLongEquipPanel")
	end,
	[40144] = function(datay,dataz)--客服名片
		 cpnotification.addNote("请联系vip客服", 1)
	end,
    [40146] = function(datay,dataz)--客服名片
        cpnotification.addNote("请联系腾讯vip客服", 1)
    end,
    [40147] = function (datay,dataz)--装备绑定符
    	openPanel("ItemBindListPanel")
    end,
	[40148] = function(datay,dataz)--附魔卷
		 openPanel("MainPanel",3,6,18,0)
	end,
	[40149] = function(datay,dataz)--附魔强化符
		 openPanel("MainPanel",3,6,19,0)
	end,
	[40150] = function(datay,dataz)--极品附魔符
		 openPanel("MainPanel",3,6,19,0)
	end,

	[40133] = function(datay,dataz)--角色改名卡
		 openPanel("CPTips", "RenamePanel")
	end,

	[40134] = function(datay,dataz)--行会改名
		local guildIDProp = 10
		local guildID = gdceapon.get_data("hero", "prop_" .. guildIDProp) or 0
		if (guildID > 0) then
			local pid = gdceapon.get_data("hero", "pid")
			local guildMasterID = gdceapon.get_data("guild", "guild_masterid")
			if (pid == guildMasterID) then
				openPanel("CPTips", "RenamePanel", 1)
				return
			end
		end
		cpnotification.addNote("只有行会会长才能更改行会名称。", 1)
	end,
}
gdFuncData[FP.item_use] = function(datax,datay,dataz,datas)
	if itemSwitch[datax] then
		itemSwitch[datax](datay, dataz)
	end
end

gdFuncData[FP.player_relive] = function(datax,datay,dataz,datas)
	openPanel("ReliveAlertPanel",datas,datay,dataz,datax)
end

gdFuncData[FP.kick_from_guild] = function(datax, datay, dataz, datas)
	openPanel("FloatPanel", 38)
end

gdFuncData[FP.NSLogin] = function(datax, datay, dataz, datas)
	if datay==1 then
		openPanel("LoginRewardPanel")
	end
end

gdFuncData[FP.guild_call] = function(datax, datay, dataz, datas)
	openPanel("FloatPanel", 48,datas)
end

gdFuncData[FP.recharge_once] = function(datax, datay, dataz, datas)
	local giftID = datay or 0
	local index = dataz or 0
	local moduleName = "activity"
	local subModule = "single_recharge_reward_" .. index
	if (datax == 0) then
		gdceapon.clear_sub_data(moduleName, subModule, giftID)
	else
		gdceapon.set_sub_data(moduleName, subModule, giftID, "data", 1)
	end
end

gdFuncData[FP.CaiShenLanLu] = function(datax, datay, dataz, datas)
	openPanel("ArenaFightPanel", datax, datay)
end
-----------------------------------------------------------
FuncHandler = function(funcid,datax,datay,dataz,datas)
	local func = gdFuncData[funcid]
	if func then
		func(datax,datay,dataz,datas)
	end
end

showIconTips = function(funcid)
	if funcid == FuncProp.gift_reward or funcid == FuncProp.maildata then
		return 1
	end
	return 0
end

translateMail = function(mystr)
	local a1,a2 = string.find(mystr,"@title:")
	local b1,b2 = string.find(mystr,"@issue:")
	local c1,c2 = string.find(mystr,"@gift:")
	local title = ""
	local issue = ""
	local gift = ""
	if a2 and b1 then
		title = string.sub(mystr,a2+1,b1-1)
	end

	if b2 and c1 then
		issue = string.sub(mystr,b2+1,c1-1)
	end

	if c2 then
		gift = string.sub(mystr,c2+1,-1)
	end

	return title,issue,gift
end

getNowMemory = function()
	local str = gdceapon.get_data("platform", "phone_info")
	local normal = 400
	local bad = 200
	local per = 1024
	local now = 0
	local _,_,a = str:find("availmemory=([^*]+)GB")
	local _,_,b = str:find("availmemory=([^*]+)MB")
	if a then
		now = tonumber(a)
		if now*per<=bad then
			return 2
		elseif now*per>bad and now*per<=normal then
			return 1
		end
	else
		print("error,not found memory GB")
	end
	if b then
		now = tonumber(b)
		if now<=bad then
			return 2
		elseif now>bad and now<=normal then
			return 1
		end
	else
		print("error,not found memory MB")
	end
	return 0
end
