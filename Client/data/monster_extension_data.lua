if not gdMonsterExtension then
	gdMonsterExtension = {}
end

local function onLoadguard(entity)
	entity:setProps(EntityProp.attr_pkstate,Pkstate.pks_yellow)
end

local EP = EntityProp

gdMonsterExtension[17] =
{
	onLoad = onLoadguard,
}

gdMonsterExtension[18] =
{
	onLoad = onLoadguard,
}

gdMonsterExtension[285] = --龙影潭临时boss
{
	onEntityReward = function(scene, entity)
		local wave = scene:getProps(SceneProp.lyt_wave)
		--经验递增
		local sd = gdMonsters[entity:getStaticID()]
		if not sd then
			return
		end
		local rewardExp = sd.exp
		for i=1,wave,1 do
			rewardExp = rewardExp+rewardExp*0.013
		end
		entity:setProps(EntityProp.attr_m_reward_exp, rewardExp)
		--物品概率递增

	end,


	onUpdate = function(entity)
	end,
}

gdMonsterExtension[2131] = --- 勇士角斗场的花
{
	onPickit = function(entity)
		local scene = entity:getScene()
		local sid = scene:getStaticID()
		if sid == MapID.ysjdc then
			entity:addEventDataX(EID.ysjdc,1) -- 勇士角斗场采集一朵+1分
			entity:syncEventData(EID.ysjdc)
			entity:addGene(50000)
		end
		return Error.Success
	end
}

gdMonsterExtension[195] =  ---虫魔图腾
{
	onPickit = function(entity)
		local pickitem = 40036
		--local flag = false
		local reqcnt = 0
		for k = Quest.line_Main,Quest.line_Emigrated do
			local quest = entity:getQuest(k)
			if quest then
				local qid = quest:getStaticID()
				local qd = gdQuests[qid]
				if qd then
					if qd.type == Quest.type_ItemCollect and qd.target_datax == pickitem then
						reqcnt = reqcnt + qd.target_datay
						--[[if entity:hasItem(qd.target_datax,qd.target_datay) then
							flag = true
						else
							return entity:addItem(qd.target_datax)
						end
						--]]
					end
				end
			end
		end
		if entity:hasItem(pickitem,reqcnt) then
			return Error.QuestGetEnoughItem
		else
			if entity:getBagEmptyCnt()>0 then
				return entity:addItem(pickitem)
			else
				return Error.Item_BagisFull
			end
		end
		return Error.ItemNotThisQuest
	end
}


gdMonsterExtension[197] =  ---金刚石
{
	onPickit = function(entity)
		return entity:addItem(40130)
	end
}


gdMonsterExtension[198] =  ---赤血石
{
	onPickit = function(entity)
		return entity:addItem(40131)
	end
}

gdMonsterExtension[1120] = -- 赤月魔光
{
	onPickit = function(entity)
		local scene = entity:getScene()
		local sid = scene:getStaticID()
		if sid == MapID.cyxg or sid == MapID.cymy then
			entity:addGene(10100)
		end
		return Error.Success
	end
}

gdMonsterExtension[1124] = -- 火焰战将
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)

		entity:addSkill(5065)
		entity:addSkill(5082)
		return Error.Success
	end,
	onTimerEvent =
	{
		[1] = function(entity)
			entity:castSkill(5065)	--陨石
			entity:addTimerEvent(2, 1000, 3)
		end,
		[2] = function(entity)
			if (entity:getProps(EP.attr_m_next_cast_skill)~=5065) then
				entity:castSkill(5082)	--连续顺劈
			end
		end,
	}
}


gdMonsterExtension[1125] = -- 赤月魔光
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)
		return Error.Success
	end
}

gdMonsterExtension[1126] = -- 赤月魔光
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)
		return Error.Success
	end
}

gdMonsterExtension[1127] = -- 傀儡妖人
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)

		entity:addSkill(5080)
		return Error.Success
	end,
	onTimerEvent =
	{
		[1] = function(entity)
			local scene = entity:getScene()
			if scene then
			--	scene:syncFloatMessage("你们都去死吧！！！")
			end
		end,
		[2] = function(entity)
			entity:castSkill(5080) --群攻
		end,
	}
}

gdMonsterExtension[1128] = -- 赤月魔光
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)
		return Error.Success
	end
}

gdMonsterExtension[1129] = -- 赤月魔光
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)
		return Error.Success
	end
}

gdMonsterExtension[1130] = -- 赤月魔光
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)
		return Error.Success
	end
}

gdMonsterExtension[2112] =
{
	onMonsterDie = function(entity)
		local killer = entity:getCombatKiller()
		if killer then
			_G.syncFloatMessage("沙城统领被玩家 "..killer:getName().." 击杀")
		end
	end,
}

gdMonsterExtension[2150] = -- 行会护送美女
{
	onMonsterDie = function(entity)
		Event.HangHuiMeiNvHuSongDie(entity)
	end,
	onMonsterLeave = function(entity)
		local remaintime = entity:getProps(EntityProp.attr_time_to_live)
		log.info(remaintime)
		if (remaintime <= 0) then
			 Event.HangHuiMeiNvHuSongFailed(entity)
		end
	end
}
gdMonsterExtension[2151] = -- 被欺负的美女
{
	onMonsterLeave = function(entity)
		local remaintime = entity:getProps(EntityProp.attr_time_to_live)
		if (remaintime <= 0) then
			 Event.HangHuiMeiNvHuSongFailed(entity)
		end
	end
}

gdMonsterExtension[2016] =
{
	onAttacked = function(damage,lastdamage,holydamage)
		return 1 + holydamage
	end,
}

gdMonsterExtension[2017] =
{
	onAttacked = function(damage,lastdamage,holydamage)
		return 1 + holydamage
	end,
}

gdMonsterExtension[2200] =
{
	onLoad = function(entity)

	end,

	onEvent = function(entity, evtid, evtgid, datax,datay,datz, evtettx,evtetty)
		if evtid == EventProp.EID_Be_Poison and evtgid == EventProp.GT_Combat then
--			log.info("############去毒回血！！")
			entity:rmvGene(201)
			local srccbt = entity:getCombatSys()
			if srccbt then
				srccbt:updateHPPercent(15)
			end
			local scene = entity:getScene()
	--
--	活动:魔幻星宫	mhxg	sexg
--
--		scene:syncFloatMessage(entity:getName().."使用了驱毒回血！！")
		end
	end,
}


gdMonsterExtension[2201] =
{
	onLoad = function(entity)

	end,
	onEvent = function(entity, evtid, evtgid, datax,datay,datz, evtettx,evtetty)
	end,

}

gdMonsterExtension[5403] = -- 地狱男爵
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)

		entity:addSkill(5065)
		entity:addSkill(5082)
		return Error.Success
	end,
	onTimerEvent =
	{
		[1] = function(entity)
			entity:castSkill(5065)	--陨石
			entity:addTimerEvent(2, 1000, 5)
		end,
		[2] = function(entity)
			if (entity:getProps(EP.attr_m_next_cast_skill)~=5065) then
				entity:castSkill(5082)	--连续顺劈
			end
		end,
	}
}
gdMonsterExtension[5404] = -- 暗夜守护
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)

		entity:addSkill(5065)
		entity:addSkill(5082)
		return Error.Success
	end,
	onTimerEvent =
	{
		[1] = function(entity)
			entity:castSkill(5065)	--陨石
			entity:addTimerEvent(2, 1000, 8)
		end,
		[2] = function(entity)
			if (entity:getProps(EP.attr_m_next_cast_skill)~=5065) then
				entity:castSkill(5082)	--连续顺劈
			end
		end,
	}
}
gdMonsterExtension[5405] = -- 暗夜驯兽
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)

		entity:addSkill(5065)
		entity:addSkill(5082)
		return Error.Success
	end,
	onTimerEvent =
	{
		[1] = function(entity)
			entity:castSkill(5065)	--陨石
			entity:addTimerEvent(2, 1000, 8)
		end,
		[2] = function(entity)
			if (entity:getProps(EP.attr_m_next_cast_skill)~=5065) then
				entity:castSkill(5082)	--连续顺劈
			end
		end,
	}
}
gdMonsterExtension[5406] = -- 暗夜巡查
{
	onLoad = function(entity)
		entity:setProps(EP.attr_speed_gene_imm, 1)
		entity:setProps(EP.attr_visible_gene_imm, 1)

		entity:addSkill(5065)
		entity:addSkill(5082)
		return Error.Success
	end,
	onTimerEvent =
	{
		[1] = function(entity)
			entity:castSkill(5065)	--陨石
			entity:addTimerEvent(2, 1000, 8)
		end,
		[2] = function(entity)
			if (entity:getProps(EP.attr_m_next_cast_skill)~=5065) then
				entity:castSkill(5082)	--连续顺劈
			end
		end,
	}
}