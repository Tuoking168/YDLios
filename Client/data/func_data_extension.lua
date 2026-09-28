if not gdFuncExtension then
	gdFuncExtension = {}
end

local EP = EntityProp
local SP = SceneProp
local WP = WorldProp
local IP = ItemProp
local FP = FuncProp

--副本提示(队伍集结)
gdFuncExtension[FP.team_call] =
{
	ClientRequest = function(entity)
		local leader = entity:getTeamLeader()
		if leader then
			if entity:getGlobalID()==leader:getGlobalID() then
				local lasttime = entity:getProps(EP.attr_teamcall_cd)
				local nowtime = os.time()
				if lasttime == 0 or nowtime - lasttime>30 then
					entity:setProps(EP.attr_teamcall_cd,nowtime)
					entity:forEachTeamMember(function(entity)
						if leader and entity:getGlobalID()~=leader:getGlobalID() then
							entity:sendFuncMsg(FP.team_call)
						end
					end)
					return Error.Success
				else
					return Error.StillInCD
				end
			else
				return Error.Not_Team_Leader
			end
		end
		return Error.Player_GetNoTeam
	end,

	ClientResponse = function(entity, datax, datay, dataz)
		--datax 玩家决定
		if datax == 1 then--同意
			--获取队长坐标，传送过去
			local leader = entity:getTeamLeader()
			if leader then
				local leaderscene = leader:getScene()
				local sceneid = leaderscene:getStaticID()
				local sd = gdMaps[sceneid]
				if sd and sd.type==1 then
					Scene.conveyentitytoAnywhere(entity,sceneid,leader:getPositionX(),leader:getPositionY())
				else
					Scene.conveyentitytoAnywhere(entity,MapID.wc, 147, 130)
				end
			end
			return Error.Success
		elseif datax == 0 then--拒绝
			return Error.Success
		end
	end
}

--人物设置
gdFuncExtension[FP.player_setting] =
{
	ClientResponse = function(entity, datax, datay, dataz)
			--datax 表示需要改变的ExIndex
			--datay 表示改变后的值
		if datax == EP.attr_refuse_addfriend or datax == EP.attr_refuse_trade then
			entity:setProps(datax,datay)
			entity:saveProps(datax)
			entity:syncProps(datax)
		elseif datax == EP.attr_hideFashion or datax == EP.attr_hideWeapon then

			entity:setProps(datax,datay)
			entity:saveProps(datax)
			entity:syncProps(datax)
			entity:WeaponFashionSettingChange(datax)
		end
		return Error.Success
	end
}

--物品使用
gdFuncExtension[FP.item_use] =
{
	ClientRequest = function(entity, datax, datay, dataz)
			--datax 表示物品sid
		entity:sendFuncMsg(FP.item_use,datax)
		--entity:syncFuncRegionMessage(FP.item_use,datax)
		return Error.Success
	end
}


--人物复活
gdFuncExtension[FP.player_relive] =
{
	ClientResponse = function(entity, datax, datay, dataz)
		return Entity.revive(entity,datax)
	end
}

gdFuncExtension[FP.gift_reward] =
{

--datax 表示礼包idx
	ClientResponse = function(entity, datax, datay, dataz)
		return Gift.getPlayerGift(entity,datax)
	end
}


gdFuncExtension[FP.maildata] =
{
--datax 表示礼包idx
	ClientResponse = function(entity, datax, datay, dataz)
		return Gift.getPlayerGift(entity,datax)
	end
}



gdFuncExtension[FP.NSLogin] =
{
	ClientResponse = function(entity, datax, datay, dataz)
		return Gift.getNSLoginGift(entity)
	end
}

gdFuncExtension[FP.findback_item] =
{
	--datax 物品iid
	ClientResponse = function(entity, datax, datay, dataz)
		return Item.findHollowItem(entity,datax)
	end
}
--行会召集令禁用地图
gdGuildCallForbiddenMaps = gdGuildCallForbiddenMaps or {
	[MapID.pkc] = true,
	[MapID.jjl] = true,
	[MapID.jjl2] = true,
	[MapID.ayd] = true,
	[MapID.byh] = true,
	[MapID.hmjy] = true,
	[MapID.glxg] = true,
	[MapID.xjql] = true,
	[MapID.yglg] = true,
}
--行会召集
gdFuncExtension[FP.guild_call] =
{
	ClientRequest = function(entity, datax, datay, dataz)
		local lasttime = entity:getProps(EP.attr_teamcall_cd)
		local nowtime = os.time()
		if lasttime == 0 or nowtime - lasttime>30 then
			entity:setProps(EP.attr_teamcall_cd,nowtime)
			local guild = entity:getGuild()
			if guild then
				guild:forEach(function(guildentity)
					if guildentity and entity:getGlobalID()~=guildentity:getGlobalID() then
						guildentity:sendFuncMsg(FP.guild_call,entity:getGlobalID(),datay,dataz,entity:getName())
					end
				end)
			else
				return Error.err_guild_noguild
			end
			return Error.Success
		else
			return Error.StillInCD
		end
		--entity:syncFuncRegionMessage(FP.guild_call,entity:getID(), datay, dataz,entity:getName())
		return Error.Success
	end,

--datax 邀请玩家pid  datay表示同意
	ClientResponse = function(entity, datax, datay, dataz)
		local ret = Error.Success
		if datay == 1 then--同意
			local guild = entity:getGuild()
			local self = entity
			if guild then
				log.info("has guild",datax)
				guild:forEach(function(guildentity)
					if guildentity and guildentity:getGlobalID()==datax then
						local leaderscene = guildentity:getScene()
						if leaderscene then
							local sceneid = leaderscene:getStaticID()
							local sd = gdMaps[sceneid]
							if gdGuildCallForbiddenMaps[sceneid] then
								ret = Error.InvalidScene
							elseif sd.type == 1 then
								Scene.conveyentitytoAnywhere(self,sceneid,guildentity:getPositionX(),guildentity:getPositionY())
							else
								ret = Error.InvalidScene
							end
						end
					end
				end)
			else
				return Error.err_guild_noguild
			end
			return ret
		elseif datay == 0 then--拒绝
			return Error.Success
		end
	end
}

gdFuncExtension[FP.recharge_once] =
{

--datax 表示礼包idx
	ClientResponse = function(entity, datax, datay, dataz)
		return Gift.getPlayerGift(entity,datax)
	end
}

gdFuncExtension[FP.offlineExp] =
{
--datax 表示离线丹sid  datay 表示个数
	ClientResponse = function(entity, datax, datay, dataz)
		if datax~=0 and datax~=40065 and datax~=40066 and datax~=40067 then
			return Error.NotEnoughItem
		end
		local level = entity:getLevel()
		local offtime = entity:getProps(EntityProp.attr_ex_exp_time)
		local canusetime = math.ceil(offtime/3600-1)
		if canusetime>0 then
			if datax~=0 then
				local realcount = entity:getItemCount(datax)
				local count = 0
				if realcount>canusetime then
					count = canusetime
				else
					count = realcount
				end
				if entity:hasItem(datax,count) then
					entity:rmvItem(datax,count)
					local offexp = count * level * 100 * 5
					entity:addExp(offexp)
					canusetime = canusetime - count
				else
					return Error.NotEnoughItem
				end
			end
			--正常发放奖励
			local offexp = canusetime * level *100
			entity:addExp(offexp)

			entity:setProps(EntityProp.attr_ex_exp_time,0)
			entity:syncProps(EntityProp.attr_ex_exp_time)
			return Error.Success
		end
		return Error.HasNotOffExp
	end
}

gdFuncExtension[FP.dailyReward] =
{
--datax 表示idx  datay表示 0- 秒功能  1- 领取活跃奖励
	ClientResponse = function(entity, datax, datay, dataz)
		log.info("dailyReward ",datax,datay)
		if datay==0 then
			return DailyAct.Finish(entity,datax)
		elseif datay==1 then
			return DailyAct.GetReward(entity,datax)
		end
	end
}


gdFuncExtension[FP.goldbowl] =
{
	--datax = 1为小聚宝盆 2 为大聚宝盆
	ClientResponse = function(entity, datax, datay, dataz)
		log.info("player datax, datay,dataz"..datax)
		if (ServerData.beginday <= 3) then
			local isopen = _G.getWorldDataX(WorldProp.jv_bao_pen)
			if isopen == 1 then
				if entity:getBagEmptyCnt() <= 0 then
					return Error.Item_Player_BagisFull
				end

				local vip = entity:getProps(EntityProp.attr_vip_level)

				if (datax == 1) then

					log.info("jubaopen--------------------------" .. vip)
					if vip < 1 then
						return Error.NotEnoughVipLevel
					end
					if entity:hasItem(30304,1,ItemProp.Bag_All) then
						return Error.hasgetgoldbowl
					else
						if (entity:getEventDataY(EID.smallgold) == 0) then
							local cnt = _G.getWorldDataX(WorldProp.prop_world_xiaojubaopen_cnt)
							if cnt>=200 then
								return Error.TimeIsOver
							end
							local rtv = entity:useGold(2888888,Opcode.buyGoldBowl)
							if rtv == Error.Success then
								entity:setEventDataX(EID.smallgold,ServerData.beginday)
								entity:setEventDataY(EID.smallgold,0)
								entity:saveEventData(EID.smallgold)
								entity:addBindItem(30304)
								_G.addWorldDataX(WorldProp.prop_world_xiaojubaopen_cnt)
								_G.saveWorldData(WorldProp.prop_world_xiaojubaopen_cnt)
							end
							return rtv
						else
							return Error.hasgetgoldbowl
						end
					end
				elseif datax == 2 then
					log.info("jubaopen++++++++++++++++++++++" .. vip)
					if vip < 3 then
						return Error.NotEnoughVipLevel
					end
					if entity:hasItem(30305,1,ItemProp.Bag_All) then
						return Error.hasgetgoldbowl
					else
						if (entity:getEventDataY(EID.biggold) == 0) then
							local cnt = _G.getWorldDataX(WorldProp.prop_world_dajubaopen_cnt)
							if cnt>=100 then
								return Error.TimeIsOver
							end
							local rtv = entity:useGold(16888888,Opcode.buyGoldBowl)
							if rtv == Error.Success then
								entity:setEventDataX(EID.biggold,ServerData.beginday)
								entity:setEventDataY(EID.biggold,0)
								entity:saveEventData(EID.biggold)
								-- useGold
								-- resetEventData
								-- addItem
								entity:addBindItem(30305)
								_G.addWorldDataX(WorldProp.prop_world_dajubaopen_cnt)
								_G.saveWorldData(WorldProp.prop_world_dajubaopen_cnt)
							end
							return rtv
						else
							return Error.hasgetgoldbowl
						end
					end
				else
					return Error.Unknown
				end
			end
		end
		return Error.TimeIsOver
	end
}


gdFuncExtension[FP.changeItem] =
{
--datax 表示兑换物sid  datay表示要兑换的sid  dataz表示兑换个数(暂时不用)
	ClientResponse = function(entity, datax, datay, dataz)
		local embag  = entity:getBagEmptyCnt()  --获取背包剩余格子数
		if (embag < 1) then
			return Error.Item_BagisFull
		end
		local eu = gdExchangeList[datax]
		local usecnt = 0
		local itemsid = 0
		local itemcnt = 0
		local isbind = 0
		log.info("datax",datax)
		if eu then
			for k,v in pairs(eu) do
				if v and v.itemsid==datay then
					itemsid = v.itemsid
					usecnt = v.usecnt
					itemcnt = v.itemcnt
					isbind = v.isbind
				end
			end
		log.info("usecnt,itemsid,itemcnt",usecnt,itemsid,itemcnt)
			if usecnt==0 or itemsid==0 or itemcnt==0 then
				return Error.Script
			end

			if datax>=10000 then
				if entity:hasItem(datax,usecnt) then
					entity:rmvItem(datax,usecnt)
					if isbind==1 then
						entity:addBindItem(itemsid,itemcnt)
					else
						entity:addItem(itemsid,itemcnt)
					end
					return Error.Success
				else
					return Error.NotEnoughItem
				end
			end

			if datax==EntityProp.attr_ex_coin  then
				if _G.getWorldDataX(20403)==0 then
					return Error.TimeIsOver
				end
				local coin = entity:getProps(EntityProp.attr_ex_coin)
				log.info(coin,usecnt)
				if coin>=usecnt then
					entity:addProps(EntityProp.attr_ex_coin,-usecnt)
					entity:saveProps(EntityProp.attr_ex_coin)
					entity:syncProps(EntityProp.attr_ex_coin)
					if isbind==1 then
						entity:addBindItem(itemsid,itemcnt)
					else
						entity:addItem(itemsid,itemcnt)
					end
					return Error.Success
				else
					return Error.NotEnoughItem
				end
			end

		end
		return Error.Script
	end
}

local function getLuckyCircleRewards(entity)
	local cnt = 0
	local casetabel ={}
	local size=#gdLuckyCircleReward
	for i=1,size do
		local case=gdLuckyCircleReward[i]
		if case then
		cnt=cnt+case.probability
			local attr={}
			attr.id=i
			attr.cnt=cnt
			table.insert(casetabel, attr)
		else
			log.error("can't find gdLuckyCircleReward id = "..i)
		end
	end
	local x = math.random(1,cnt)
	local n=0
	for k,v in pairs(casetabel) do
		if x<=v.cnt then
			n=v.id
			break
		end
	end
	local eu = gdLuckyCircleReward[n]
	if eu then
		entity:sendFuncMsg(FP.luckycircle,n)
		entity:addBindItem(eu.itemID,eu.cnt,Opcode.useLuckyCircle)
	end
end

gdFuncExtension[FP.luckycircle] =
{
	ClientResponse = function(entity, datax, datay, dataz)
		if _G.getWorldDataX(20417)<1 then
			return Error.EventInactive
		end

		if entity:getBagEmptyCnt() <= 0 then
			return Error.Item_Player_BagisFull
		end

		--local usegold = entity:getProps(EntityProp.attr_circle_used_old)
		--local cancnt = usegold/500
		--local hascnt = entity:getProps(EntityProp.attr_used_free_cnt)
		--
		local usegold = entity:getEventDataX(EID.xydzp)
		local cancnt = math.floor(usegold/50000)
		local usedcnt = entity:getEventDataY(EID.xydzp)
		if usedcnt>=cancnt then
			return Error.NotEnoughScore
			--if entity:getGold()>=50 then
			--		entity:useGold(50)
			--	entity:addProps(EntityProp.attr_circle_used_old,50)
			--	getLuckyCircleRewards(entity)
			--else
			--	return Error.NotEnoughGold
			--end
		else
			entity:addEventDataY(EID.xydzp)
			getLuckyCircleRewards(entity)
		end
		--entity:syncProps(EntityProp.attr_used_free_cnt)
		--entity:saveProps(EntityProp.attr_used_free_cnt)
		--entity:syncProps(EntityProp.attr_circle_used_old)
		--entity:saveProps(EntityProp.attr_circle_used_old)
		entity:setEventDataZ(EID.xydzp, cancnt-usedcnt-1)
		entity:saveEventData(EID.xydzp)
		entity:syncEventData(EID.xydzp)
		log.info("*************************************/", EID.xydzp, entity:getEventData(EID.xydzp))
		return Error.Success
	end
}

gdFuncExtension[FP.repayreward] =
{
--datax表示回馈奖励编号
	ClientResponse = function(entity, datax, datay, dataz)
		if entity:getBagEmptyCnt() <= 0 then
			return Error.Item_Player_BagisFull
		end
		local eu = gdRepayReward[datax]
		if not eu then
			return Error.Script
		end

		local id = eu.eventid
		if not id then
			return Error.Unknown
		end
		local en = gdEventData[id]
		if not en then
			log.error("not found gdEventData id = "..id)
			return Error.Script
		end

		local req = en.req
		--local canrepeat = en.canrepeat
		local maxcnt = en.getcnt
			log.info("event id = "..id)
		local hascnt = entity:getEventDataX(id) - entity:getEventDataY(id)
			log.info("hascnt, usecnt = "..entity:getEventDataX(id) , entity:getEventDataY(id))
		if hascnt<=0 then
			return Error.NotEnoughCondition
		end

		for k,v in pairs(eu.reward) do
			if v then
				if v.itemID>0 then
					if v.itemIsBind then
						entity:addBindItem(v.itemID,v.itemcnt,Opcode.Op_Recharge)
					else
						entity:addItem(v.itemID,v.itemcnt,Opcode.Op_Recharge)
					end
				else
					local id=0
					if entity:getStaticID()==1 then
						id=1
					elseif entity:getStaticID()==2 then
						id=3
					elseif entity:getStaticID()==3 then
						id=5
					end
					if entity:getGender()==2 then
						id=id+1
					end
					local em=gdRewardEx[v.itemname]
					if em then
						if em.reward[id].type and em.reward[id].count then
							if em.reward[id].itemIsBind then
								entity:addItem(em.reward[id].type, em.reward[id].count * v.itemcnt)
							else
								entity:addItem(em.reward[id].type, em.reward[id].count * v.itemcnt)
							end
						end
					else
						log.error("Failed to do repay reward: ", v.itemname, datax)
					end
				end
			end
		end

		entity:addEventDataY(id)
		entity:saveEventData(id)
		entity:syncEventData(id)

		return Error.Success
	end
}

gdFuncExtension[FP.bind_item] =
{
	ClientResponse = function(entity, datax, datay, dataz)
		if (not entity) or (dataz ~= 1) then
			return Error.InvalidParam
		end
		if not entity:hasItem(datax, 1) then
			return Error.NotEnoughItem
		end
		if datay >= 0 then
			return Error.NotEnoughCondition
		end
		local item = entity:getItemByPosition(datay)
		if (not item) or
		   (item:getProps(IP.Item_Bind) == IP.Item_Has_bind) then
		   return Error.NotEnoughCondition
		end
		item:setProps(IP.Item_Bind, IP.Item_Has_bind)
		entity:saveItemProps(item,IP.Item_Bind)
		entity:syncItemProps(item,IP.Item_Bind)
		entity:rmvItem(datax, 1)
		return Error.Success
	end
}
--马上抢购
gdFuncExtension[FP.MSQG] =
{
	ClientResponse = function(entity, datax, datay, dataz)
		if not entity then
			return Error.InvalidParam
		end

		local eu = gdRepayReward[datax]
		if not eu then
			return Error.Script
		end

		local id = eu.eventid
		if not id then
			return Error.Unknown
		end
		local en = gdEventData[id]
		if not en then
			log.error("not found gdEventData id = "..id)
			return Error.Script
		end
		local nowcount = entity:getEventDataX(id)
		local limit = en.getcnt
		if nowcount and limit then
			if nowcount>=limit then
				return Error.NotEnoughCondition
			end
		end

		local req = en.req
		if not req then
			return Error.Script
		end
		if entity:getGold()<=tonumber(req) then
			return Error.NotEnoughGold
		end
		local reward = eu.reward
		if not reward then
			return Error.Script
		end
		entity:useGold(req)
		for k,v in pairs(reward) do
			if v.itemID and v.itemcnt then
				if v.itemIsBind then
					entity:addBindItem(v.itemID,v.itemcnt,Opcode.op_msqg)
				else
					entity:addItem(v.itemID,v.itemcnt,Opcode.op_msqg)
				end
			end
		end
		entity:addEventDataX(id)
		entity:saveEventData(id)
--		entity:syncEventData(id)
		return Error.Success
	end
}
--疯狂抢购
gdFuncExtension[FP.FKQG] =
{
	ClientResponse = function(entity, datax, datay, dataz)
		if not entity then
			return Error.InvalidParam
		end

		local eu = gdRepayReward[datax]
		if not eu then
			return Error.Script
		end

		local id = eu.eventid
		if not id then
			return Error.Unknown
		end

		local en = gdEventData[id]
		if not en then
			log.error("not found gdEventData id = "..id)
			return Error.Script
		end

		local wid = en.worldid
		local cnt,limit_world_cnt
		if wid then
			cnt = _G.getWorldDataX(wid)
			limit_world_cnt = en.limitcnt
			if limit_world_cnt and cnt >= limit_world_cnt then
				return Error.UpToLimit
			end
		else
			return Error.Script
		end

		local nowcount = entity:getEventDataX(id)
		local limit = en.getcnt
		if nowcount and limit then
			if nowcount>=limit then
				return Error.NotEnoughCondition
			end
		end

		local req = en.req
		if not req then
			return Error.Script
		end
		if entity:getGold()<=tonumber(req) then
			return Error.NotEnoughGold
		end
		local reward = eu.reward
		if not reward then
			return Error.Script
		end
		entity:useGold(req)
		for k,v in pairs(reward) do
			if v.itemID and v.itemcnt then
				if v.itemIsBind then
					entity:addBindItem(v.itemID,v.itemcnt,Opcode.op_fkqg)
				else
					entity:addItem(v.itemID,v.itemcnt,Opcode.op_fkqg)
				end
			end
		end
		--限制个人购买
		entity:addEventDataX(id)
		entity:saveEventData(id)
		--		entity:syncEventData(id)
		--限制全服购买
		_G.addWorldDataX(wid)
		_G.saveWorldData(wid)
		_G.syncWorldData(wid)
		return Error.Success
	end
}

