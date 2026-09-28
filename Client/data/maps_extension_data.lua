require 'math'

local EP = EntityProp
local SP = SceneProp
local WP = WorldProp
local IP = ItemProp
local GP = GuildProp

gdMapExtension = {}

----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
--				公用函数						   ---
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------



----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
--				活动							   ---
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
--
--	活动: 九天冰宫	jtbg
--

local jtbg_time_sync = function(entity)
	local spendtime = os.time() - entity:getProps(EP.attr_jtbg_time_start)
	local usetime = entity:getEventDataX(EID.jtbg)
	local ed = gdEventData[EID.jtbg]
	local remaintime = ed.datax
	if ed then
		remaintime = remaintime - usetime - spendtime
	--	print(remaintime)
	end
	local scene = entity:getScene()
	--print(SP.scene_time_remain)
	scene:setProps(SP.scene_time_remain,remaintime)
	entity:syncSceneProps(SP.scene_time_remain)

	if remaintime <= 0 then
		Scene.conveyentitytoNPC(entity,190)
	end
end

local jtbg_me = {
	onLoad = function(scene)
		scene:addTimerEvent(1, 60000, 480)
		scene:addTimerEvent(2, 3000)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			scene:forEachEntityP(jtbg_time_sync)
		end,
		[2] = function(scene)
			scene:syncProps(SP.max_monster)
			scene:syncProps(SP.now_monster)
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_jtbg_time_start, os.time())

			jtbg_time_sync(entity)

			entity:syncSceneProps(SP.max_monster)
			entity:syncSceneProps(SP.now_monster)
		elseif entity:isM() then
			scene:addProps(SP.max_monster)
			scene:addProps(SP.now_monster)
		end
	end,
	onEntityLeave	= function(scene, entity)
		if entity:isP() then
			local spendtime = os.time() - entity:getProps(EP.attr_jtbg_time_start)
			entity:addEventDataX(EID.jtbg, spendtime)
			entity:saveEventData(EID.jtbg)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			--local monstercnt = scene:getEntityCount(EP.ett_Monster)
			scene:addProps(SP.now_monster, -1)
			scene:syncProps(SP.now_monster)
			log.info("jtbg monster cnt = "..scene:getProps(SP.now_monster))
			local monstercnt = scene:getProps(SP.now_monster)
			if (monstercnt == 0) then
				-- to do reward Player

			end
		end
	end
}

gdMapExtension[MapID.jtbg] = jtbg_me
gdMapExtension[MapID.jtbg2] = jtbg_me
gdMapExtension[MapID.jtbg3] =
{
	onLoad = function(scene)
		scene:addTimerEvent(1, 60000, 480)
		scene:setProps(SP.max_monster,6)
		scene:setProps(SP.now_monster,6)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			scene:forEachEntityP(jtbg_time_sync)
		end,

	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_jtbg_time_start, os.time())

			jtbg_time_sync(entity)

			entity:syncSceneProps(SP.max_monster)
			entity:syncSceneProps(SP.now_monster)
		end
	end,
	onEntityLeave	= function(scene, entity)
		if entity:isP() then
			local spendtime = os.time() - entity:getProps(EP.attr_jtbg_time_start)
			entity:addEventDataX(EID.jtbg, spendtime)
			entity:saveEventData(EID.jtbg)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			--local monstercnt = scene:getEntityCount(EP.ett_Monster)
			scene:addProps(SP.now_monster, -1)
			scene:syncProps(SP.now_monster)
			log.info("jtbg monster cnt = "..scene:getProps(SP.now_monster))
			local monstercnt = scene:getProps(SP.now_monster)
			if (monstercnt == 2) then
				-- show remain Monster!;
				scene:addM(2109,38,62)
				scene:addM(2110,52,62)
			end
		end
	end,
}


--
--	活动:魔幻星宫	mhxg	sexg
--
--
local mhxg_factor =
{
	{300, 480},
	{400, 584},
	{500, 688},
	{600, 792},
	{700, 896},
	{800, 1000},
	{968, 1164},
	{1027, 1213},
	{1087, 1262},
	{1146, 1312},
	{1206, 1361},
	{1265, 1410},
}

local mhxg_exp_small = function(entity, layer)
	entity:addExp(mhxg_factor[layer][1] * entity:getLevel() + mhxg_factor[layer][2], 0)
end

local mhxg_exp_big = function(entity, layer)
	entity:addExp(mhxg_factor[layer][1] * entity:getLevel() * 10 + mhxg_factor[layer][2] * 11, 0)
end

local mhxg_exp_rank = function(entity, layer, rank)
	local exp = 1
	if rank == 1 then
		exp = layer * 1235 +6000
	elseif rank == 2 then
		exp = layer * 800 + 4000
	elseif rank == 3 then
		exp = layer * 300 + 3000
	else
		exp = layer * 100 + 2000
	end

	entity:addExp(exp,Opcode.mhxglayerreward,layer)
end

--local mhxg_debuff = function(entity, layer)
--	local cbt = entity:getCombatSys()
--	if cbt then
--		cbt:updateHP(-mhxg_factor[layer][1])
--		cbt:updateMP(-mhxg_factor[layer][2])
--	end
--end

gdMapExtension[MapID.mhxg] =
{
	onLoad = function(scene)
		scene:addTimerEvent(1, 10000, -1)	-- 10秒获得一次小经验
		scene:addTimerEvent(2, 600000, -1)	-- 10分钟获得一次大经验
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			local layer = scene:getProps(SP.mhxg_layer) or 1
			scene:forEachEntityP(function(entity)
				mhxg_exp_small(entity, layer)
		--		mhxg_debuff(entity, layer)
				end)
		end,
		[2] = function(scene)
			local layer = scene:getProps(SP.mhxg_layer) or 1
			scene:forEachEntityP(function(entity)
				mhxg_exp_big(entity, layer)
				end)
		end,

	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			local rank = scene:addProps(SP.mhxg_player_index) or 4
			local layer = scene:getProps(SP.mhxg_layer)
			mhxg_exp_rank(entity, layer, rank)

			if rank<4 and math.mod(layer, 3)==0 then
				local msg = "玩家["..entity:getName().."]第"..rank.."个抵达第"..layer.."层,获得额外奖励!!!"
				for lidx = 1, 12 do
					local scene = gdScnMgr:getSceneBySid(MapID.mhxg + lidx - 1)
					if scene then
						scene:syncFloatMessage(msg)
					end
				end
			end
		end
	end,
}

for lidx = 1, 11 do
	gdMapExtension[MapID.mhxg+lidx] = gdMapExtension[MapID.mhxg]
end



--
--	活动:龙影潭	lyt
--
local lyt_monster = {
	[1] = 1099,
	[2] = 1100,
	[3] = 1101,
	[4] = 1102,
	[5] = 1103,
	[6] = 1104,
	[7] = 1105,
	[8] = 1106,
	[9] = 1107,
	[10] = 1108,
}
local lyt_boss = {
	[1] = 1109,
	[2] = 1110,
	[3] = 1111,
	[4] = 1112,
	[5] = 1113,
	[6] = 1114,
	[7] = 1115,
	[8] = 1116,
	[9] = 1117,
	[10] = 1118,
}

local lyt_bg = {
	{10, 8, 5},
	{13, 10, 7},
	{17, 13, 9},
	{24, 18, 12},
	{37, 27, 20},
}
local lyt_refresh_boss = function(scene)
	local posx = 37
	local posy = 27 --刷怪中心
	local range = 5 --刷怪范围

	local wave = scene:getProps(SP.lyt_wave)
	if wave>10 then --end
		scene:syncFloatMessage("龙影坛即将在5s内关闭! ")
		scene:addTimerEvent(1, 5000)
		return
	end

	local entityBoss = scene:addM(lyt_boss[wave], posx, posy)--boss
	if entityBoss then
		scene:syncFloatMessage("龙影坛统领已经出现，勇士们速速前去击杀! ")
	end
end

local lyt_refresh_monster = function(scene)
	local posx = 30
	local posy = 30 --刷怪中心
	local range = 12 --刷怪范围

	local wave = scene:getProps(SP.lyt_wave)
	scene:setProps(SceneProp.max_monster,30+(wave-1)*5)--根据波数设置小怪上限

	local mmax = scene:getProps(SceneProp.max_monster)
	for i=1,mmax,1 do
		local dx = math.random(-range,range)
		local dy = math.random(-range,range)
		local monster = scene:addM(lyt_monster[wave], posx+dx, posy+dy)
	end
end

local lyt_next_wave = function(scene)
	local wave = scene:getProps(SP.lyt_wave)
	if not wave or wave<0 or wave>10 then
		wave = 0
	end
	wave = wave+1
	scene:setProps(SP.lyt_wave,wave)
	scene:setProps(SP.lyt_monster_kill,0)
	if wave>= 10 then --end
		scene:syncFloatMessage("龙影坛即将在5s内关闭! ")
		scene:addTimerEvent(1, 5000)
		return
	end
	lyt_refresh_monster(scene)
end

gdMapExtension[MapID.lyt] = {
	onLoad = function(scene)
		lyt_next_wave(scene)
	end,
	onTimerEvent =
	{
		[1] = function(scene)
			scene:close()
		end,
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, 100)
			entity:syncProps(EP.attr_faction_id)
			entity:syncProps(EP.attr_pkmode)

			scene:addProps(SP.lyt_player_cnt)
		elseif entity:isM() then
			entity:setProps(EP.attr_owner_type, EP.eot_Faction)
			entity:setProps(EP.attr_owner_data, 100)
			entity:setProps(EP.attr_m_time_to_own, -1)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local wave = scene:getProps(SP.lyt_wave)
			local sid = entity:getStaticID()
			if sid==lyt_boss[wave] then --如果boss死了
				lyt_next_wave(scene)
			else
				local cnt = scene:getProps(SP.lyt_monster_kill)
				if not cnt or cnt<0 or cnt>30 then
					cnt = 0
				end
				cnt = cnt+1
				scene:setProps(SP.lyt_monster_kill,cnt)
				if cnt>=30 then
					scene:setProps(SP.lyt_monster_kill,0)
					lyt_refresh_boss(scene)
				end
				local realcnt = scene:getProps(SP.lyt_monster_realkill)
				realcnt = realcnt + 1
				scene:setProps(SP.lyt_monster_realkill,cnt)
			end
		end
	end,
	onEntityLeave = function(scene, entity)
		if entity:isP() then
			scene:addProps(SP.lyt_player_cnt, -1)
		end
	end,
	---[[--龙影谭副本经验符起作用
	onEntityReward = function(scene, entity)
		local sd = gdMonsters[entity:getStaticID()]

		local playercnt = scene:getProps(SP.lyt_player_cnt)
		local rate = 1
		if playercnt<2 then
			rate = 1
		elseif playercnt<5 then
			rate = 1.1
		elseif playercnt<9 then
			rate = 1.2
		elseif playercnt<12 then
			rate = 1.3
		else
			rate = 1.4
		end

		local  killerid = entity:getProps(EP.attr_last_attacker)
		local  killer = scene:getEntity(killerid)
		local  geneExp = killer:getProps(EP.attr_gene_loot_exp)
		geneExp = geneExp/100 +1 --经验神符倍数
		scene:forEachEntityP(function(ett)
			ett:addExp(sd.exp * rate * geneExp, Opcode.lyt_monster_exp)
		end)

		return true
	end,
	--]]
	onSceneClose = function(scene)
		local guild = _G.getGuild(scene:getProps(SceneProp.ownerguildid))
		if guild then
			local nowlytkill = scene:getProps(SP.lyt_monster_realkill)
			guild:setProps(GuildProp.lyt_kill_count,guild:getProps(GuildProp.lyt_kill_count) + nowlytkill)
			guild:saveProps(GuildProp.lyt_kill_count)
			guild:syncProps(GuildProp.lyt_kill_count)

			local nowlytwave = scene:getProps(SP.lyt_wave)
			guild:setProps(GuildProp.lyt_kill_wave_count,guild:getProps(GuildProp.lyt_kill_wave_count) + nowlytwave)
			guild:saveProps(GuildProp.lyt_kill_wave_count)
			guild:syncProps(GuildProp.lyt_kill_wave_count)

			local opencount =  guild:getProps(GuildProp.lyt_open_count) or 1
			local bg = lyt_bg[opencount]
			if bg then
				scene:forEachEntityP(function(entity)
					local gpost = entity:getProps(EP.attr_guild_post)
					if gpost == GuildProp.post_master then
						entity:addProps(EP.attr_guild_contribution, bg[1])
						entity:saveProps(EP.attr_guild_contribution)
						entity:syncProps(EP.attr_guild_contribution)
					elseif gpost==GuildProp.post_second_master then
						entity:addProps(EP.attr_guild_contribution, bg[2])
						entity:saveProps(EP.attr_guild_contribution)
						entity:syncProps(EP.attr_guild_contribution)
					else
						entity:addProps(EP.attr_guild_contribution, bg[3])
						entity:saveProps(EP.attr_guild_contribution)
						entity:syncProps(EP.attr_guild_contribution)
					end
				end)
			end
		end
	end
}
--
--	活动: 荣誉神殿	rysd
--
gdMapExtension[MapID.rysd] = {
	onLoad = function(scene)
		scene:addTimerEvent(1, 30000, -1)
		scene:addTimerEvent(2, 5000)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			scene:forEachEntityP(function(entity)
					entity:addExp(50000000,Opcode.Op_Activity,EID.rysd)
					entity:addHonor(250,Opcode.Op_Activity,EID.rysd)
					entity:addBindItem(30059,Opcode.Op_Activity,EID.rysd)
				end)
		end,
		[2] = function(scene)
			scene:addM(2014, 50, 50)
		end,
	},

	onEntityEnter	= function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:syncProps(EP.attr_pkmode)
			entity:setProps(EP.attr_faction_id, 100)
			entity:syncProps(EP.attr_faction_id)
		elseif entity:isM() then
			entity:setProps(EP.attr_owner_type, EP.eot_Faction)
			entity:setProps(EP.attr_owner_data, 100)
			entity:setProps(EP.attr_m_time_to_own, -1)
		end
	end,

	onEntityDie = function(scene, entity)
		if entity:isP() then
			Scene.conveyBack(entity)
		end
	end
}


--
--	活动: 行会争夺战	hhzdz
--

local hhzdz_flag_x = 55
local hhzdz_flag_y = 41

local hhzdz_refreshFlag = function(scene, entity)
	local boss = scene:addM(500, hhzdz_flag_x, hhzdz_flag_y)
	if not boss then
		log.error("Failed to refresh flag in hhzdz")
		return
	end
	if not entity then
		return
	end

	local guild = entity:getGuild()
	if not guild then
		return
	end

	local guildid = guild:getID()
	local guildname = guild:getGuildName()

	boss:setProps(EP.attr_guild_id,guildid)
	scene:setProps(SP.hhzdz_flag_eid,boss:getID())

	scene:setProps(SP.hhzdz_defend_guild,guildid)
	scene:setString(SP.hhzdz_guild_name,guildname)
	scene:syncFloatMessage(guildname.."行会夺取了旗帜！")
end

local function hhzdz_exp(lvl)
	local baseexp = gdFireExp[lvl]
	if baseexp then
		return baseexp
	else
		log.error("invalid hhzdz exp lvl! lvl = "..lvl)
		return 100
	end
end

gdMapExtension[MapID.hhzdz] = {
	onLoad = function(scene)
		hhzdz_refreshFlag(scene)

		scene:addTimerEvent(1, 30000)
		scene:addTimerEvent(2, 10000, -1)
		for x = 40, 52 do
			scene:addBlock(x, 	x+12, 0x8000)
			scene:addBlock(x+1, 	x+11, 0x8000)
		end
	end,
	onTimerEvent =
	{
		[1] = function(scene)
			for x = 40, 52 do
				scene:rmvBlock(x, 	x+12, 0x8000)
				scene:rmvBlock(x+1, 	x+11, 0x8000)
			end
			scene:syncFloatMessage("战斗开始!")
		end,
		[2] = function(scene)
			scene:forEachEntityP(function(entity)
				local x, y = entity:getPosition()
				x = x-hhzdz_flag_x
				y = y-hhzdz_flag_y
				if x>=-4 and x<=4 and y>=-4 and y <=4 then
					local dgid = scene:getProps(SP.hhzdz_defend_guild)
					local mgid = entity:getProps(EP.attr_guild_id)
					if dgid==mgid then
						entity:addExp(hhzdz_exp(entity:getLevel())*2,Opcode.Op_Activity,EID.hhzdz)
					else
						entity:addExp(hhzdz_exp(entity:getLevel()),Opcode.Op_Activity,EID.hhzdz)
					end
				end
			end)
		end,
		[3] = function(scene)
			local guildid = scene:getProps(SP.hhzdz_defend_guild)
			local guildname = scene:getString(SP.hhzdz_guild_name)
			scene:setProps(SP.hhzdz_finish, 1)
			if guildid and guildid ~= 0 then
				scene:close()
			end
			_G.syncFloatMessage(guildname.."行会成功守住了旗子！")
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Guild)
			entity:syncProps(EP.attr_pkmode)
			entity:syncSceneProps(SP.hhzdz_defend_guild)
			entity:syncSceneString(SP.hhzdz_guild_name)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() and entity:getStaticID() == 500 then
			hhzdz_refreshFlag(scene,entity:getCombatKiller())
			scene:addTimerEvent(3, 600000)
		end
		scene:syncProps(SP.hhzdz_defend_guild)
		scene:syncString(SP.hhzdz_guild_name)
	end,

	onSceneClose = function(scene)
		local guildid = scene:getProps(SP.hhzdz_defend_guild)
		local guildname = scene:getString(SP.hhzdz_guild_name)
		if guildid and guildid ~= 0 then
			local guild = _G.getGuild(guildid)
			if guild then
				guild:addProps(GP.guild_money, 1000000)
				guild:syncProps(GP.guild_money)
			end
			_G.syncFloatMessage(guildname.."行会成为了本次行会争夺战的霸主！")
		else
			_G.syncFloatMessage("本次行会争夺战没有胜利者！")
		end
	end
}

--
--	活动: 狩猎活动	slhd	降妖除魔	xycm
--
--

local slhd_onLoad = function(scene)
	scene:addTimerEvent(1, 20000, -1)
end
local slhd_onEntityEnter   = function(scene, entity)
	if entity:isP() then
		entity:setProps(EP.attr_slhd_score, 0)
		entity:syncProps(EP.attr_slhd_score)
		entity:setProps(EP.attr_pkmode,EP.pk_Any)
		entity:syncProps(EP.attr_pkmode)
	end
end

local slhd_scene_msg = function(msg)
	for lidx = 1, 4 do
		local scene = gdScnMgr:getSceneBySid(MapID.slc + lidx - 1)
		if scene then
			scene:syncFloatMessage(msg)
		end
	end
end
local slhd_onEntityDie = function(scene, entity)
	local entitykiller = entity:getCombatKiller()

	if entitykiller and entitykiller:isP() and entitykiller:getID()~=entity:getID() then
		if entity:isP() then
			entitykiller:addProps(EP.attr_slhd_score, 5)
			entitykiller:syncProps(EP.attr_slhd_score)
			entity:setProps(EP.attr_slhd_score,0)
			entity:syncProps(EP.attr_slhd_score)
			scene:syncFloatMessage(entity:getName().."  被  "..entitykiller:getName().." 击杀了!")
		elseif entity:getStaticID() == 2127 then
			entitykiller:addProps(EP.attr_slhd_score, 5)
			entitykiller:syncProps(EP.attr_slhd_score)
			scene:syncFloatMessage(entitykiller:getName().."  击杀了BOSS获得大量的奖励！")
		else
			entitykiller:addProps(EP.attr_slhd_score, 1)
			entitykiller:syncProps(EP.attr_slhd_score)
		end
	end

	if scene:getStaticID()==MapID.slc4 then
		entity:setProps(EP.attr_slhd_score,0)
		entity:syncProps(EP.attr_slhd_score)
	end
end
local slhd_onSafeRevive = function(entity,scene,scenedata)

	local sid = scene:getStaticID()
	local md = gdMaps[MapID.slc1]

	if (sid ~= MapID.slc1) then
		gdScnMgr:enterScene(entity,MapID.slc1,1,1)
	end

	Scene.conveytoRandomPos(entity)

	local cbt = entity:getCombatSys()
	if cbt then
		cbt:updateHP(cbt:getMaxHP() * 0.1,0)
		cbt:setMP(0)
		cbt:updateMP(cbt:getMaxMP() * 0.1)
		entity:addGene(1)
		entity:setState(EP.gst_Idle)
	end
	return Error.Success
end

gdMapExtension[MapID.slc] =
{
	onLoad = function(scene)
		scene:addTimerEvent(1, 20000, -1)
		--scene:addTimerEvent(2, 60000)
		--_G.syncFloatMessage("降妖除魔正式开始！")
	end,
	onTimerEvent = {
		[1] = function(scene)
			scene:forEachEntityP(function(entity)
				entity:addExp(400000,Opcode.Op_Activity,EID.slhd)
			end)
		end,
		--[2] = function(scene)
		--	_G.syncFloatMessage("降妖除魔入口已经关闭！")
		--end,
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_slhd_score, 0)
			entity:syncProps(EP.attr_slhd_score)
			entity:setProps(EP.attr_pkmode,EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)
		end
	end,
	onEntityDie = slhd_onEntityDie,
	onSafeRevive= slhd_onSafeRevive,
}
gdMapExtension[MapID.slc2] =
{
	onLoad = slhd_onLoad,
	onTimerEvent = {
		[1] = function(scene)
			scene:forEachEntityP(function(entity)
				entity:addExp(600000,Opcode.Op_Activity,EID.slhd)
			end)
		end,
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_slhd_score, 0)
			entity:syncProps(EP.attr_slhd_score)
			entity:setProps(EP.attr_pkmode,EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)
			slhd_scene_msg(entity:getName().."  已经进入第二层！")
		end
	end,
	onEntityDie = slhd_onEntityDie,
	onSafeRevive= slhd_onSafeRevive,
}
gdMapExtension[MapID.slc3] =
{
	onLoad = slhd_onLoad,
	onTimerEvent = {
		[1] = function(scene)
			scene:forEachEntityP(function(entity)
				entity:addExp(900000,Opcode.Op_Activity,EID.slhd)
			end)
		end,
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_slhd_score, 0)
			entity:syncProps(EP.attr_slhd_score)
			entity:setProps(EP.attr_pkmode,EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)
			slhd_scene_msg(entity:getName().."  已经进入第三层！")
		end
	end,
	onEntityDie = slhd_onEntityDie,
	onSafeRevive= slhd_onSafeRevive,
}
gdMapExtension[MapID.slc4] =
{
	onLoad = function(scene)
		scene:addM(2127, 26, 32) -- boss
		scene:addTimerEvent(1, 20000, -1)
	end,
	onTimerEvent = {
		[1] = function(scene)
			scene:forEachEntityP(function(entity)
				entity:addExp(2000000,Opcode.Op_Activity,EID.slhd)
			end)
		end,
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_slhd_score, 0)
			entity:syncProps(EP.attr_slhd_score)
			entity:setProps(EP.attr_pkmode,EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)
			slhd_scene_msg(entity:getName().."  已经进入第四层！")
		end
	end,
	onEntityDie = slhd_onEntityDie,

	onSceneClose = function(scene)
		--玩家积分排名
		local e1, e2, e3
		local s1 = 0
		local s2 = 0
		local s3 = 0
		scene:forEachEntityP(function(entity)
				local s = entity:getProps(EP.attr_slhd_score)
				if s>s3 then
					s3 = s
					e3 = entity
					if s3>s2 then
						s2, s3 = s3, s2
						e2, e3 = e3, e2
						if s2>s1 then
							s1, s2 = s2, s1
							e1, e2 = e2, e1
						end
					end
				end
				entity:setEventDataY(EID.slhd, 4)
				entity:saveEventData(EID.slhd)
			end)

		local best = ""
		if e1 then
			e1:setEventDataY(EID.slhd, 1)
			e1:saveEventData(EID.slhd)

			best = best..e1:getName()..","
		end
		if e2 then
			e2:setEventDataY(EID.slhd, 2)
			e2:saveEventData(EID.slhd)
			best = best..e2:getName()..","
		end
		if e3 then
			e3:setEventDataY(EID.slhd, 3)
			e3:saveEventData(EID.slhd)
			best = best..e3:getName()..","
		end
		_G.syncFloatMessage("本次降妖除魔活动，获得前三名的是："..best.." 他们获得了额外的活动大礼包")
	end,
	onSafeRevive= function(entity,scene,scenedata)
		Scene.conveytoRandomPos(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:updateHP(cbt:getMaxHP() * 0.1,0)
			cbt:setMP(0)
			cbt:updateMP(cbt:getMaxMP() * 0.1)
			entity:addGene(1)
			entity:setState(EP.gst_Idle)
		end
		return Error.Success
	end,
}

--
--	活动: 火龙熔岩	hlry
--
--gdMapExtension[MapID.hlry] = {
--}


--
--	活动: 武易战场	wyzc
--
--

gdMapExtension[MapID.wyzc] = {
	onLoad = function(scene)
		scene:setProps(SP.wyzc_faction_a, 0)
		scene:setProps(SP.wyzc_faction_b, 0)
		scene:setProps(SP.wyzc_score_a, 0)
		scene:setProps(SP.wyzc_score_b, 0)

		scene:addTimerEvent(4, 30000)	--30seconds

		local m = scene:addM(196, 85, 86)
		if m then
			scene:setProps(SP.wyzc_flag_id, m:getID())
		end

		for x = 128, 141 do
			scene:addBlock(x, 268-x, 0x8000)
			scene:addBlock(x, 267-x, 0x8000)
		end
		for x = 33, 45 do
			scene:addBlock(x, 88-x, 0x8000)
			scene:addBlock(x, 87-x, 0x8000)
		end

		local guard = scene:addM(2142, 34, 28)
		if guard then
			guard:setProps(EP.attr_faction_id, 2)
			guard:setProps(EP.attr_pkmode, EP.pk_FactionPOnly)
		end
		local guard = scene:addM(2142, 28, 34)
		if guard then
			guard:setProps(EP.attr_faction_id, 2)
			guard:setProps(EP.attr_pkmode, EP.pk_FactionPOnly)
		end

		local guard = scene:addM(2142, 140, 145)
		if guard then
			guard:setProps(EP.attr_faction_id, 1)
			guard:setProps(EP.attr_pkmode, EP.pk_FactionPOnly)
		end
		local guard = scene:addM(2142, 145, 140)
		if guard then
			guard:setProps(EP.attr_faction_id, 1)
			guard:setProps(EP.attr_pkmode, EP.pk_FactionPOnly)
		end
	end,

	onTimerEvent =
	{
		[4] = function(scene)
			for x = 128, 141 do
				scene:rmvBlock(x, 268-x, 0x8000)
				scene:rmvBlock(x, 267-x, 0x8000)
			end
			for x = 33, 45 do
				scene:rmvBlock(x, 88-x, 0x8000)
				scene:rmvBlock(x, 87-x, 0x8000)
			end
			scene:syncFloatMessage("战斗开始!")
		end,

		[5] = function(scene)
			--超时,移除未被击杀的boss
			scene:rmvEntity(scene:getProps(SP.wyzc_boss_id))
			scene:addM(196, 85, 86)
			scene:syncFloatMessage("Boss已经逃跑了，旗帜重新出现了。")
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:syncProps(EP.attr_pkmode)

			local score = entity:getEventDataX(EID.wyzc, score)

			local cnta = scene:getProps(SP.wyzc_faction_a)
			local cntb = scene:getProps(SP.wyzc_faction_b)
			if cnta>cntb then
				scene:setProps(SP.wyzc_faction_b, cntb+1)
				entity:setProps(EP.attr_faction_id, 2)
				entity:syncProps(EP.attr_faction_id)
				scene:flyEntity(entity, 29, 29)
			else
				scene:setProps(SP.wyzc_faction_a, cnta+1)
				entity:setProps(EP.attr_faction_id, 1)
				entity:syncProps(EP.attr_faction_id)
				scene:flyEntity(entity, 144, 144)
			end

			scene:syncProps(SP.wyzc_faction_a)
			scene:syncProps(SP.wyzc_faction_b)
			entity:syncSceneProps(SP.wyzc_score_a)
			entity:syncSceneProps(SP.wyzc_score_b)

			entity:setEventDataX(EID.wyzc, 0)
			entity:syncEventData(EID.wyzc)
		elseif entity:isM() then
			local sid = entity:getStaticID()
			if sid==196 then
				--boss刷新在第三阵营里面, 只会攻击人类
				entity:setProps(EP.attr_faction_id, 3)
				entity:setProps(EP.attr_pkmode, EP.pk_FactionPOnly)
			end
		end
	end,
	onEntityLeave	= function(scene, entity)
		if entity:isP() then
			local faction_id = entity:getProps(EP.attr_faction_id)
			local point = entity:getEventDataX(EID.wyzc)
			if faction_id==1 then
				scene:addProps(SP.wyzc_faction_a, -1)
				scene:syncProps(SP.wyzc_faction_a)
			elseif faction_id==2 then
				scene:addProps(SP.wyzc_faction_b, -1)
				scene:syncProps(SP.wyzc_faction_b)
			end
		end
	end,
	onEntityDie = function(scene, entity)
		log.info("wyzc die!!")
		local entitykiller = entity:getCombatKiller()
		if entitykiller then
			log.info("is entity killer!")
		end
		if entity:isP() then
			local s = entity:getEventDataX(EID.wyzc)
			s = s - 5
			if s<0 then
				s = 0
			end
			entity:setEventDataX(EID.wyzc, s)
			entity:syncEventData(EID.wyzc)
		end
		if entitykiller and entitykiller:isP() then
			local score = 0
			if entity:isP() then
				score = 10	-- 10 score for player killing
			elseif entity:isM() then
				log.info(" entity monster dead !")
				if entity:getStaticID() == 196 then
					scene:setProps(SP.wyzc_flag_id, 0)

					local faction_id = entitykiller:getProps(EP.attr_faction_id)
					local mb
					if faction_id==1 then
						mb = scene:addM(2138, 126, 126)
						scene:syncFloatMessage("人方拿下了旗帜，BOSS已出现在人方的阵营中")
					elseif faction_id==2 then
						mb = scene:addM(2138, 48, 48)
						scene:syncFloatMessage("魔方拿下了旗帜，BOSS已出现在魔方的阵营中")
					end
					if mb then
						scene:setProps(SP.wyzc_boss_id, mb:getID())
					end
					scene:addTimerEvent(5, 300000)	--5分钟后boss不死则消失, 并重新刷新旗子
				elseif entity:getStaticID() == 2138 then
					scene:setProps(SP.wyzc_boss_id, 0)

					score = 500 -- 500 score for monster killing
					if scene:getProps(SP.wyzc_flag_id)==0 then
						local m = scene:addM(196, 85, 86)
						if m then
							scene:setProps(SP.wyzc_flag_id, m:getID())
						end
						scene:syncFloatMessage("Boss已经被击杀，旗帜重新出现了。")
					end
				end
			end
			entitykiller:addEventDataX(EID.wyzc, score)
			entitykiller:syncEventData(EID.wyzc)

			if entitykiller:getProps(EP.attr_faction_id)==1 then
				scene:addProps(SP.wyzc_score_a, score)
				scene:syncProps(SP.wyzc_score_a)
			else
				scene:addProps(SP.wyzc_score_b, score)
				scene:syncProps(SP.wyzc_score_b)
			end
		end
	end,

	onSceneClose = function(scene)
		local faction_win = 2
		if scene:getProps(SP.wyzc_score_a) > scene:getProps(SP.wyzc_score_b) then
			faction_win = 1
		end

		--表现最优异的全三名
		local e1, e2, e3
		local s1 = 0
		local s2 = 0
		local s3 = 0
		scene:forEachEntityP(function(entity)

			if entity:getProps(EP.attr_faction_id)==faction_win then
				local s = entity:getEventDataX(EID.wyzc)
				if s>s3 then
					s3 = s
					e3 = entity
					if s3>s2 then
						s2, s3 = s3, s2
						e2, e3 = e3, e2
						if s2>s1 then
							s1, s2 = s2, s1
							e1, e2 = e2, e1
						end
					end
				end
				entity:setEventDataY(EID.wyzc, 1)
				entity:saveEventData(EID.wyzc)
			else
				entity:setEventDataY(EID.wyzc, 2)
				entity:saveEventData(EID.wyzc)
			end
		end)

		local best = ""
		if e3 then
			best = " "..e3:getName()..best
		end
		if e2 then
			best = " "..e2:getName()..best
		end
		if e1 then
			best = " "..e1:getName()..best
		end

		if best~="" then
			best = ", 其中" ..best .. " 表现优异!"
		else
			best = "."
		end

		if scene:getProps(SP.wyzc_score_a)>scene:getProps(SP.wyzc_score_b) then
			_G.syncFloatMessage("本次群雄逐鹿活动人方获胜"..best)
		else
			_G.syncFloatMessage("本次群雄逐鹿活动魔方获胜"..best)
		end
	end,

	onSafeRevive= function(entity,scene,scenedata)
		local faction = entity:getProps(EP.attr_faction_id)
		if faction == 1 then
			scene:flyEntity(entity, 144, 144)
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(cbt:getMaxHP() * 0.1,0)
				cbt:setMP(0)
				cbt:updateMP(cbt:getMaxMP() * 0.1)
				entity:addGene(1)
				entity:setState(EP.gst_Idle)
			end
		else
			scene:flyEntity(entity, 29, 29)
			local cbt = entity:getCombatSys()
			if cbt then
				cbt:updateHP(cbt:getMaxHP() * 0.1,0)
				cbt:setMP(0)
				cbt:updateMP(cbt:getMaxMP() * 0.1)
				entity:addGene(1)
				entity:setState(EP.gst_Idle)
			end
		end
		return Error.Success
	end
}


--
--	活动: 战神争霸	zszb	cbtx
--

local function zszbrewardtime(entity,liquan,honor)
	if entity:isAlive() then
		entity:addCoupon(liquan,Opcode.Op_Activity,EID.zszb)
		entity:addHonor(honor,Opcode.Op_Activity,EID.zszb)
	end
end

local function zszbcheck(scene)
	local zszbwinner = _G.getWorldDataX(EID.zszb)
	if scene:getProps(SP.prop_scene_enter_disable) == 1 and zszbwinner == 0 then
		local zszbcnt = scene:getProps(SP.zszb_player_cnt)
		if zszbcnt == 1 then
			scene:forEachEntityP(function(entity)
				if entity:isAlive() then
					_G.setWorldDataX(WP.zszb,entity:getGlobalID())
					_G.setWorldDataY(WP.zszb,0)
					_G.setWorldDataStr(WP.zszb,entity:getName())
					_G.saveWorldData(WP.zszb)
					_G.updateHeadTitle(WP.zszb)
					_G.syncFloatMessage(entity:getName().."成为了新一届霸主")
				end
			end)
			scene:rmvTimerEvent(2)
			scene:rmvTimerEvent(3)
		elseif zszbcnt < 1 then
			_G.syncFloatMessage("无人成为新一届霸主")
			scene:rmvTimerEvent(2)
			scene:rmvTimerEvent(3)
		end
	end
end

local function zszbplayercheck(scene)
	local cnt = 0
	scene:forEachEntityP(function(entity)
					if entity:isAlive() then
						log.info("entity id = "..entity:getGlobalID())
						cnt = cnt + 1
					end
				end)
	scene:setProps(SP.zszb_player_cnt,cnt)
	scene:syncProps(SP.zszb_player_cnt)

end



gdMapExtension[MapID.zszb] = {
	onLoad = function(scene)
		scene:setProps(SP.zszb_player_cnt,0)

		_G.setWorldDataX(EID.zszb,0)
		_G.setWorldDataY(EID.zszb,0)
		_G.setWorldDataStr(EID.zszb,"")
		_G.saveWorldData(EID.zszb)

		--_G.syncFloatMessage("称霸天下活动已经开启，大量奖励等你来拿！")
	--	log.info("zszb player cnt" ,scene:getProps(SP.zszb_player_cnt))
		scene:addTimerEvent(1, 600000)	--10min后禁止?入
		scene:addTimerEvent(2, 180000 , 10)
		scene:addTimerEvent(3, 2000)
		scene:addTimerEvent(4, 20000)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			scene:setProps(SP.prop_scene_enter_disable,1)
			_G.syncFloatMessage("称霸天下入口已经关闭！")
			zszbcheck(scene)
			--local playercnt = scene:getEntityPCount()
			--scene:setProps(SP.zszb_player_cnt,playercnt)
		end,
		[2] = function(scene) --- 根据场景内人数发放礼券和荣誉
			local liquan = 140
			local honor = 10000
			local playercnt = scene:getEntityPCount()
			liquan = math.floor(liquan / playercnt)
			honor = math.floor(honor / playercnt)
			scene:forEachEntityP(function(entity) return zszbrewardtime(entity,liquan,honor) end)
		end,
		[3] = function(scene)
			scene:forEachEntityP(function(entity)
				if entity:isAlive() then
					local x = entity:getPositionX()
					local y = entity:getPositionY()
					local dis = math.max(math.abs(x - 24),math.abs(y - 28))
					local cbt = entity:getCombatSys()
					if cbt then
						if dis <5 then
							cbt:updateHP(-400,1)
						elseif dis < 10 then
							cbt:updateHP(-800,1)
						else
							cbt:updateHP(-1250,1)
						end
					end
				end
				end)
			local zszbcnt = scene:getProps(SP.zszb_player_cnt)
			local disable = scene:getProps(SP.prop_scene_enter_disable)
			if disable == 0 then
				scene:addTimerEvent(3, 2000)
			elseif zszbcnt > 1 then
				scene:addTimerEvent(3, 2000)
			end
		end,
		[4] = function(scene)
			scene:forEachEntityP(function(entity)
				if entity:isAlive() then
					entity:addGene(10211)
					entity:syncEntityBeUsedSkill(2041)
				end
				end)
			local zszbcnt = scene:getProps(SP.zszb_player_cnt)
			local disable = scene:getProps(SP.prop_scene_enter_disable)
			if disable == 0 then
				scene:addTimerEvent(4, 20000)
			elseif zszbcnt > 1 then
				scene:addTimerEvent(4, 20000)
			end
		end,
		[5] = function(scene)
			zszbplayercheck(scene)
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)
			--scene:addProps(SP.zszb_player_cnt)
			scene:syncProps(SP.zszb_player_cnt)
			zszbplayercheck(scene)
	--		log.info("zszb player cnt" ,scene:getProps(SP.zszb_player_cnt))
			DailyAct.AddTargetCnt(entity,EID.mrmrzs)
		end
	end,
	onEntityLeave	= function(scene, entity)
		if entity:isP() then
			scene:addTimerEvent(5, 500)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isP() then
			zszbcheck(scene)
			zszbplayercheck(scene)
		end
	end,
	onSceneClose= function(scene)
		zszbcheck(scene)
	end,
	onSafeRevive= function(entity,scene,scenedata)
		Scene.conveyentitytoNPC(entity,131)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:updateHP(cbt:getMaxHP() ,0)
			cbt:updateMP(cbt:getMaxMP() )
			entity:addGene(1)
			entity:setState(EP.gst_Idle)
		end
		return Error.Success
	end
}


--
--	活动: 勇士角斗场	ysjdc
--
--

local ysjdc_comp = function(v1, v2)
	if v1.s>v2.s then
		return true
	end
end

local ysjdc_rank = {
	"第一名: ",
	"第二名: ",
	"第三名: ",
	"第四名: ",
	"第五名: ",
	"第六名: ",
	"第七名: ",
	"第八名: ",
	"第九名: ",
	"第十名: ",
}

local ysjdc_rate = {
	100,
	80,
	75,
	70,
	65,
	60,
	55,
	50,
	45,
	40,
}

gdMapExtension[MapID.ysjdc] = {
	onLoad = function(scene)
		scene:addTimerEvent(1, 25000 , 400)
		scene:addTimerEvent(2, 240000 , 20)
		--_G.syncFloatMessage("勇士竞技场正式开始!")
	end,

	onTimerEvent =
	{
		[1] = function(scene) -- 每二十五秒发一次经验
			scene:forEachEntityP(function(entity) entity:addExp(10,Opcode.Op_Activity,EID.ysjdc) end)
		end,
		[2] = function(scene) -- 每4分钟随机给3个玩家发送50积分
			local maxcnt = scene:getEntityPCount()
			if (maxcnt > 3) then
				local s = {}
				local end1 = math.floor(maxcnt/3)
				local end2 = math.floor(maxcnt/3) *2
				s[1] = math.random(1,end1)
				s[2] = math.random(end1 + 1, end2)
				s[3] = math.random(end2 + 1, maxcnt)
				local c = 1
				local i = 1
				scene:forEachEntityP(function(entity)
										if c == s[i] then
											entity:addEventDataX(EID.ysjdc,50)
											entity:syncEventData(EID.ysjdc)
											i = i + 1
										end
										c = c + 1
									end)
			else
				scene:forEachEntityP(function(entity)
										entity:addEventDataX(EID.ysjdc,50)
										entity:syncEventData(EID.ysjdc)
									end)
			end
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)

			entity:setEventDataX(EID.ysjdc, 0)

			entity:syncEventData(EID.ysjdc)
		end
	end,
	onEntityDie = function(scene, entity)
		local entitykiller = entity:getCombatKiller()
		if entitykiller and entitykiller:isP() then
			local score = 0
			if entity:isP() then
				-- 杀死其他玩家获得他积分的 80%
				local deadpoint = entity:getEventDataX(EID.ysjdc)
				if deadpoint > 5 then
					local deadpointmins =  math.floor(deadpoint * 0.8)
					entity:addEventDataX(EID.ysjdc,-deadpointmins)
					entitykiller:addEventDataX(EID.ysjdc,deadpointmins)
					entity:syncEventData(EID.ysjdc)
					entitykiller:syncEventData(EID.ysjdc)
				end
			elseif entity:isM() then
				local mid = entity:getStaticID()
				if mid == 2041 then  -- 杀死勇士获得积分 10
					entitykiller:addEventDataX(EID.ysjdc,10)
					entitykiller:syncEventData(EID.ysjdc)
				elseif mid == 2042 then -- 杀死决斗之王获得积分 200
					entitykiller:addEventDataX(EID.ysjdc,200)
					entitykiller:syncEventData(EID.ysjdc)

					scene:syncFloatMessage("角斗之王被["..entitykiller:getName().."]击杀!!!")
				end
			end
		end
	end,
	onSceneClose = function(scene)
		--玩家积分排名
		local em = {}
		local ems = 9999999
		scene:forEachEntityP(function(entity)
				local cs = entity:getEventDataX(EID.ysjdc)
				if #em>=10 then
					if cs>ems then
						ems = cs
						em[10].e:setEventDataY(EID.ysjdc, 11)
						em[10].e:saveEventData(EID.ysjdc)
						em[10] = {s = cs, e = entity}
						table.sort(em, ysjdc_comp)
					else
						entity:setEventDataY(EID.ysjdc, 11)
						entity:saveEventData(EID.ysjdc)
					end
				else
					if cs<ems then
						ems = cs
					end
					table.insert(em, {s = cs, e = entity})
					table.sort(em, ysjdc_comp)
				end
			end)

		local rank = ""
		local exp = 0
		for k, v in ipairs(em) do
			if exp==0 then
				exp = v.e:getLevel()
				exp = exp * exp * exp
			end

			v.e:setEventDataY(EID.ysjdc, k)
			v.e:setEventDataZ(EID.ysjdc, ysjdc_rate[k] * exp)
			v.e:saveEventData(EID.ysjdc)

			rank = rank .. ysjdc_rank[k] .. v.e:getName() .." 积分: " .. v.s .. "\n"
		end

		_G.syncFloatMessage("本次勇士竞技场活动已经结束!")

		_G.setWorldDataStr(WorldProp.ysjdc_rank, rank)
		_G.saveWorldData(WorldProp.ysjdc_rank)

	end,
	onSafeRevive= function(entity,scene,scenedata)
		Scene.conveytoRandomPos(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:updateHP(cbt:getMaxHP() * 0.1,0)
			cbt:setMP(0)
			cbt:updateMP(cbt:getMaxMP() * 0.1)
			entity:addGene(1)
			entity:setState(EP.gst_Idle)
		end
		return Error.Success
	end,
}

--
--	活动: 烈火宫	lhg
--
--
local function lhg_exp(n, le)    --烈火宫经验
	local fexp = 4854465
	local nexp = fexp
	if n == 1 then
		return fexp
	else
		for i = 2,n	 do
			local ma = math.floor(i/2)
			local mb = (101-i)/200
			local mc = math.pow(-1,ma)*(1+math.pow(-1,i))/600
			local md = math.floor((mb + mc)*fexp)
			nexp = nexp + md
		end
		return nexp
	end
end


local function lhg_gold(n)
	return (n+1) * 10
end

local function lhg_diamond(n)
	return (n+1) * 30
end

local function lhg_honor(n)
	return n * 7500 + 15000
end

local function lhg_move_on(scene)
	local n = scene:addProps(SP.lhg_layer)
	scene:setProps(SP.lhg_exp, lhg_exp(n, scene:getProps(SP.lhg_owner_level)))
	scene:setProps(SP.lhg_liehuolin_to_next_layer, n+1)
	scene:setProps(SP.lhg_gold_to_next_layer, lhg_gold(n))
	scene:setProps(SP.lhg_diamond_to_next_layer, lhg_diamond(n))
	scene:setProps(SP.lhg_honor_to_next_layer, lhg_honor(n))

	scene:setProps(SP.lhg_layer_reward, 0)
	scene:syncProps(SP.lhg_layer)
	scene:syncProps(SP.lhg_liehuolin_to_next_layer)
	scene:syncProps(SP.lhg_gold_to_next_layer)
	scene:syncProps(SP.lhg_diamond_to_next_layer)
	scene:syncProps(SP.lhg_honor_to_next_layer)
end

gdMapExtension[MapID.lhg] = {
	onLoad = function(scene)
		scene:addTimerEvent(1, 1000)
	end,
	onTimerEvent =
	{
		[1] = function(scene)
			for i = 1, 5 do
				scene:addM(2021, math.random(14, 22), math.random(14, 22))
			end

			lhg_move_on(scene)
		end,
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			scene:setProps(SP.lhg_owner_level, entity:getLevel())
		end
	end,
}

--
--	活动: 马拉松	sm   mls  smc
--


local mls_time_sync = function(scene,entity)
	local ed = gdEventData[EID.mls]
	local mlsstate = scene:getProps(SP.mls_begin_state)
	if mlsstate ~= 0 then
		local remaintime = 0
		local stoptime = Event.getStopTime(EID.mls)
		if  stoptime then
			remaintime = stoptime - os.time()
		end
		scene:setProps(SP.scene_time_remain,remaintime)
	else
		local remaintime = scene:getProps(SP.mls_wait_end_time) - os.time()
		scene:setProps(SP.scene_time_remain,remaintime)
	end
	if not entity then
		scene:syncProps(SP.scene_time_remain)
	else
		entity:syncSceneProps(SP.scene_time_remain)
	end
end


local mlsskill =
{
	[2031] = true,
	[2032] = true,
	[2033] = true,
	[2040] = true,
	[2041] = true,
	[2042] = true,
	[2043] = true,
	[2044] = true,
	[2045] = true,
}



gdMapExtension[MapID.qssmc] = {
	onLoad = function(scene)
		scene:setProps(SP.prop_scene_skill_limit,EID.mls)

		scene:setProps(SP.prop_scene_dog_limit_in,1)
		scene:setProps(SP.prop_scene_pet_limit_in,1)
		local startwait = 3 * 60
		scene:setProps(SP.mls_wait_end_time,os.time() + startwait)
		scene:addTimerEvent(1, 180 * 1000)
		scene:addTimerEvent(2, 60*1000)
		scene:addTimerEvent(3, 120*1000)
		scene:addTimerEvent(4, 150*1000)
		scene:addTimerEvent(5, 160*1000)
		scene:addTimerEvent(6, 170*1000)
		for x =  30,58 do
			scene:addBlock(x, 66, 0x8000)
			scene:addBlock(x, 67, 0x8000)
		end
	end,

	isskillallow = function(skillid)
		if mlsskill[skillid] then
			return Error.Success
		end
		return Error.Combat_InvalidSkill
	end,
	onTimerEvent =
	{
		[1] = function(scene)
			-- set saima begin
			scene:setProps(SP.mls_begin_state,1)
			scene:syncProps(SP.mls_begin_state)
			mls_time_sync(scene)
			-- rmv block
			for x = 30 ,58 do
				scene:rmvBlock(x, 66, 0x8000)
				scene:rmvBlock(x, 67, 0x8000)
			end

			scene:syncFloatMessage("比赛开始!!!")
		end,
		[2] = function(scene)
			scene:syncFloatMessage("比赛将在两分钟后开始!!!")
		end,
		[3] = function(scene)
			scene:syncFloatMessage("比赛将在一分钟后开始!!!")
		end,
		[4] = function(scene)
			scene:syncFloatMessage("比赛将在30秒后开始!!!")
		end,
		[5] = function(scene)
			scene:syncFloatMessage("比赛将在20秒后开始!!!")
		end,
		[6] = function(scene)
			scene:syncFloatMessage("比赛将在10秒后开始!!!")
		end,
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode,EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)

			-- addskill

			scene:syncProps(SP.mls_begin_state)
			mls_time_sync(scene,entity)
		end
	end,

	onEntityLeave = function(scene, entity)
	end,
}

gdMapExtension[MapID.zdsmc] = {
	onLoad = function(scene)
		scene:setProps(SP.prop_scene_skill_limit,EID.mls)
		scene:setProps(SP.mls_begin_state,1)
		scene:setProps(SP.prop_scene_dog_limit_in,1)
		scene:setProps(SP.prop_scene_pet_limit_in,1)
	end,
	isskillallow = function(skillid)
		if mlsskill[skillid] then
			return Error.Success
		end
		return Error.Combat_InvalidSkill
	end,

	onTimerEvent =
	{
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode,EP.pk_Any)
			entity:syncProps(EP.attr_pkmode)
			mls_time_sync(scene,entity)
		end
	end,

	onSafeRevive= function(entity,scene,scenedata)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:updateHP(cbt:getMaxHP() * 0.1,0)
			cbt:setMP(0)
			cbt:updateMP(cbt:getMaxMP() * 0.1)
			entity:addGene(1)
			entity:setState(EP.gst_Idle)
		end
		Scene.conveyentitytoscene(entity,MapID.qssmc)

		return Error.Success
	end,
}


--
--	镜像沙皇宫  yxshg
--
gdMapExtension[MapID.yxshg] = {
	onTimerEvent =
	{
		[1] = function(scene)
			scene:forEachEntityP(function(entity)
						if entity:isP() then
							local quest = entity:getQuest(Quest.line_Main)
							quest:setState(Quest.state_Finished)
							Scene.conveyBack(entity)
							entity:updateQuest(quest)
						end
					end)
		end
	},
	onEntityEnter = function(scene, entity)
		if entity:isP() then

		end
	end,
	onEntityLeave = function(scene, entity)
		if entity:isP() then
			local cnt = 0
				scene:forEachEntityM(function(entity)
						if entity:isM() and entity:isAlive() then
							cnt=cnt+1
						end
					end)
			if cnt~=0 then
				entity:rmvItemAllBySid(84024,10)
				local quest = entity:getQuest(Quest.line_Main)
				entity:deleteQuest(quest)
				quest:setState(Quest.state_Available)
				--Scene.conveyentitytoNewInstance(entity,3,68,83)
				entity:updateQuest(quest)
			end
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local cnt = 0
				scene:forEachEntityM(function(entity)
						if entity:isM() and entity:isAlive() then
							cnt=cnt+1
						end
					end)
			if cnt==0 then
				scene:forEachEntityP(function(entity)
						if entity:isP() then
							entity:rmvItemAllBySid(84024,10)
							scene:addTimerEvent(1, 2000)
						end
					end)
			end
		elseif entity:isP() then
			entity:rmvItemAllBySid(84024,10)
			local quest = entity:getQuest(Quest.line_Main)
			entity:deleteQuest(quest)
			quest:setState(Quest.state_Available)
			Scene.conveyBack(entity)
			entity:updateQuest(quest)
		end
	end
}

--
--	测试地图	csdt
--
gdMapExtension[9999] = {
	onLoad = function(scene)
		scene:addProps(1005)
		scene:addTimerEvent(1, 500, -1)
	end,
	onTimerEvent =
	{
		[1] = function(scene)
			local cnt =  scene:getEntityMCount()
			if cnt<800 then
				scene:addM(6, math.random(1, 80), math.random(1, 120))
			end
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isM() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, scene:addProps(1005))
		end
	end,
}



----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
--				副本							   ---
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------


--
--
--	副本: 万年古墓	wngm
--



gdMapExtension[MapID.wngm] = {
}
--
--	副本: 赤月峡谷
--
gdMapExtension[MapID.cyxg] = {
	onEntityLeave = function(scene, entity)
		if entity:isP() then
			entity:rmvGene(10100)	--出了副本必须清除的强力经验buff
		end
	end,
}

--
--	副本: 赤月魔域	cymy
--
gdMapExtension[MapID.cymy] = {
	onEntityLeave = function(scene, entity)
		if entity:isP() then
			entity:rmvGene(10100)	--出了副本必须清除的强力经验buff
		end
	end,
}

--
--	副本: 宝矿洞窟	bkdk
--
gdMapExtension[MapID.bkdk] = {
	onLoad = function(scene)
		scene:addTimerEvent(1, 900000)
	end,
	onEntityLeave	= function(scene, entity)
		entity:rmvItemAllBySid(70174,10)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			scene:close()
		end,
	},
	--onEntityDie = function(scene, entity)
	--	if entity:isM() then
	--		--local entityowner = entity:getCombatOwner()
			--entityowner:addItem(70169)
	--	end
	--end
}


--
--	副本: 天地宝窟	tdbk
--	贪财鬼: 1016
--	鬼财神: 1017


local function tdbk_refresh(scene)

		local boss = scene:addM(1017, 42, 26)
		if boss then
			--boss属性随着怪物波数增加而递增
			local idx =  scene:getProps(SP.tdbk_boss_idx) - 1
			local cbt = boss:getCombatSys()
			if not idx or not cbt then
				return
			end
			cbt:setProps(Combat.prop_PDEF_Min, math.pow(1.15, idx) * cbt:getProps(Combat.prop_PDEF_Min))
			cbt:setProps(Combat.prop_PDEF_Max, math.pow(1.15, idx) * cbt:getProps(Combat.prop_PDEF_Max))
			cbt:setProps(Combat.prop_MDEF_Min, math.pow(1.15, idx) * cbt:getProps(Combat.prop_MDEF_Min))
			cbt:setProps(Combat.prop_MDEF_Max, math.pow(1.15, idx) * cbt:getProps(Combat.prop_MDEF_Max))

			cbt:setProps(Combat.prop_PATK_Min, math.pow(1.2, idx) * cbt:getProps(Combat.prop_PATK_Min))
			cbt:setProps(Combat.prop_PATK_Max, math.pow(1.2, idx) * cbt:getProps(Combat.prop_PATK_Max))

			cbt:setProps(Combat.prop_HPMax, math.pow(1.25, idx) * cbt:getProps(Combat.prop_HPMax))
			cbt:setProps(Combat.prop_HP, cbt:getProps(Combat.prop_HPMax))

			boss:syncEntityMaxHpChange()
			local rewardid = gdLootnametoID["天地宝库一号BOSS"] + idx
			--log.info("reward id = "..rewardid)
			boss:setProps(EP.attr_m_reward_id, rewardid)
		end
		local entity = scene:addMG(10, 36, 32) --刷怪点
		if entity then
			entity:setProps(EP.attr_mg_refresh_interval, 2000)
			entity:setProps(EP.attr_mg_refresh_range, 20)

			entity:setProps(EP.attr_mg_refresh_type, 1)
			entity:setProps(EP.attr_mg_monster_type_cnt, 1)
			entity:setProps(EP.attr_mg_refresh_sid_begin, 1016)

			entity:setProps(EP.attr_mg_refresh_count_begin, 20)
			entity:setProps(EP.attr_mg_refresh_limit_begin, 20)
			scene:setProps(SP.tdbk_mg_id, entity:getID())
		else
			print("failed to add mg in tdbk!!")
			scene:setProps(SP.tdbk_mg_id, 0)
		end
end


local tdbk_buff = {
	[10] = 39100,
	[50] = 39101,
	[100] = 39102,
	[200] = 39103,
	[300] = 39104,
	[400] = 39105,
	[500] = 39106,
	[600] = 39107,
	[700] = 39108,
	[800] = 39109,
	[900] = 39110,
	[1000] = 39111,
}

local function tdbk_refresh_kill_count(scene, entity)
	local kill_count = scene:getProps(SP.tdbk_kill_count)
	kill_count = kill_count + 1
	local gid = tdbk_buff[kill_count]
	if gid then
		local entityowner = entity:getCombatOwner()
		if entityowner then
			entityowner:addGene(gid)
			entityowner:setProps(EP.attr_tdbk_gene,gid)
		end
		local gd = gdGenes[gid]
		if gd then
			scene:setProps(SP.tdbk_buff_data, gd.data.x)
			scene:syncProps(SP.tdbk_buff_data)
		end
	end
	scene:setProps(SP.tdbk_kill_count, kill_count)
	scene:syncProps(SP.tdbk_kill_count)
end

gdMapExtension[MapID.tdbk] = {
	onLoad = function(scene)
		scene:setProps(SP.tdbk_boss_idx, 1)
		scene:addTimerEvent(1, 60000, 30)
		tdbk_refresh(scene)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			scene:setProps(SP.tdbk_kill_count, 0)
			scene:syncProps(SP.tdbk_kill_count)
		end,

		[2] = function(scene)
			local idx = scene:getProps(SP.tdbk_boss_idx)
			if idx < 10 then
				scene:addProps(SP.tdbk_boss_idx)
				tdbk_refresh(scene)
				scene:syncProps(SP.tdbk_boss_idx)
			end
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:syncSceneProps(SP.tdbk_kill_count)
			entity:syncSceneProps(SP.tdbk_boss_idx)
		end
	end,
	onEntityLeave	= function(scene, entity)
		if entity:isP() then
			--删除暴力的buffer
			local gid = entity:getProps(EP.attr_tdbk_gene)
			if gid>0 then
				entity:rmvGene(gid)
			end
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1016 then
				tdbk_refresh_kill_count(scene, entity)
			elseif sid==1017 then
				--local mg = scene:getEntity(scene:getProps(SP.tdbk_mg_id))
				--if mg then
				--	for i = 1, mg:getSubEntityCount() do
				--		tdbk_refresh_kill_count(scene, entity)
				--	end
				--end
				--print("##############", scene:getProps(SP.tdbk_mg_id))
				scene:rmvEntity(scene:getProps(SP.tdbk_mg_id))
				scene:addTimerEvent(2, 60000)
			end
			local kill_count = scene:getProps(SP.tdbk_kill_count)
			local count_down = 0
			if kill_count<200 then
				count_down = 45
			elseif kill_count<500 then
				count_down = 30
			elseif kill_count<800 then
				count_down = 15
			else
				count_down = 10
			end
			scene:setProps(SP.tdbk_kill_count_down, count_down)
			scene:syncProps(SP.tdbk_kill_count_down)
			scene:addTimerEvent(1, count_down * 1000)
		end
	end,
}

--
--	副本: 水域龙都	syld
--
gdMapExtension[MapID.syld] = {

	onTimerEvent =
	{
		[1] = function(scene)
			local entity = scene:addM(1121, scene:getProps(SP.syld_longnv_posx), scene:getProps(SP.syld_longnv_posy))
			if entity then
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 100)
				entity:setProps(EP.attr_m_center_x, 99)
				entity:setProps(EP.attr_m_center_y, 36)
				entity:setProps(EP.attr_mode, EP.emm_Marching)
				scene:syncFloatMessage("龙女复活了, 向龙王王宫方向逃去了!")
			end
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, 100)
			entity:syncProps(EP.attr_pkmode)
			entity:syncProps(EP.attr_faction_id)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1024 then	--水域龙王
				if math.random()<=0.08 then
					scene:syncFloatMessage("发现水域龙王魂魄......")
					scene:addM(1058, entity:getPositionX(), entity:getPositionY())
				end
			elseif sid==1058 then	--水域龙王魂魄
				if math.random()<=0.04 then
					scene:syncFloatMessage("沉睡几千年的真龙王慢慢苏醒过来了......")
					scene:addM(1025, entity:getPositionX(), entity:getPositionY())
				end
			elseif sid==1023 then	--龙女
				scene:setProps(SP.syld_longnv_posx, entity:getPositionX())
				scene:setProps(SP.syld_longnv_posy, entity:getPositionY())
				-- 4s之后召唤一个同阵营的新龙女
				scene:addTimerEvent(1, 4000)
			end
		end
	end,
}



--
--	副本: 绝望沙漠	jwsm
--
gdMapExtension[MapID.jwsm] = {
	onEntityDie = function(scene, entity)
		--神灯神魔
		if entity:isM() and entity:getStaticID()==1034 then
			-- 有概率刷: 灯芯沉香
			if math.random()<=0.0151 then
				local x, y = entity:getPosition()
				scene:syncFloatMessage("发现灯芯沉香......")
				scene:addM(1059, x+2, y+2)
			end
		end
	end
}


--
--	副本: 魔龙神殿	mlsd
--
local mlsd_monsters = {
--    血宠 血鬼 神 精英 守护神
--    1035 1039 1037 1060 1038
	{30},
	{28, 8},
	{26, 4},
	{24, 6},
	{22, 8},
	{20, 10},
	{19, 10, 1},
	{17, 12, 1},
	{15, 14, 1},
	{10, 16, 2, 2},
	{8, 17, 2, 3},
	{6, 17, 2, 5},
	{3, 18, 2, 7},
	{1, 20, 2, 7},
	{0, 19, 3, 8},
	{0, 16, 4, 10},
	{0, 13, 5, 12},
	{0, 10, 5, 15},
	{0, 5, 7, 17, 1},
	{0, 0, 15, 10, 5},
}

local mlsd_monster_id = {1035, 1039, 1037, 1060, 1038}

local mlsd_positions = {
	{16, 61},
	{37, 39},
	{59, 17},
}

local mlsd_check_guard = function(scene, idx)
	local eid = scene:getProps(idx)
	if eid==0 then
		return
	end
	local m = scene:getEntity(eid)
	if not m then
		return
	end
	local cbt = m:getCombatSys()
	if not cbt then
		return
	end
	local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
	if percent<25 then
		scene:syncFloatMessage("守卫生命值低于25%了，请速速前去保护!")
		scene:setProps(idx, 0)
	end
end

gdMapExtension[MapID.mlsd] = {
	onLoad = function(scene)
		scene:setProps(SP.mlsd_defencer_count, 3)
		scene:addTimerEvent(1, 5000)

		local m =  scene:addM(1036, 54, 65)
		if m then
			scene:setProps(SP.mlsd_guard1, m:getID())
		end
		local m =  scene:addM(1036, 61, 57)
		if m then
			scene:setProps(SP.mlsd_guard2, m:getID())
		end
		local m =  scene:addM(1036, 61, 64)
		if m then
			scene:setProps(SP.mlsd_guard3, m:getID())
		end

		scene:addTimerEvent(2, 2000, -1)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			local wave = scene:addProps(SP.mlsd_monster_wave)
			scene:syncProps(SP.mlsd_monster_wave)
			local md = nil
			if wave>#mlsd_monsters then
				return
				--md = mlsd_monsters[#mlsd_monsters]
			else
				md = mlsd_monsters[wave]
			end

			for k, cnt in ipairs(md) do
				for i = 1, cnt do
					local pos = mlsd_positions[math.random(1, 3)]
					scene:addM(mlsd_monster_id[k], pos[1], pos[2])
				end
			end
			scene:syncFloatMessage("第".. wave.. "波怪物开始进攻了!")
			-- refresh 90s later
			scene:addTimerEvent(1, 60000)
		end,
		[2] = function(scene)
			mlsd_check_guard(scene, SP.mlsd_guard1)
			mlsd_check_guard(scene, SP.mlsd_guard2)
			mlsd_check_guard(scene, SP.mlsd_guard3)
		end,
		[3] = function(scene)
			scene:close()
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1036 or sid==1066 or sid==1067 then
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 100)
			else
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 101)
				entity:setProps(EP.attr_m_center_x, math.random(58, 60))
				entity:setProps(EP.attr_m_center_y, math.random(58, 62))
				entity:setProps(EP.attr_mode, EP.emm_MarchingAggressive)
			end
		elseif entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, 100)
			scene:syncProps(SP.mlsd_monster_wave)
			scene:syncProps(SP.mlsd_defencer_count)
			entity:syncProps(EP.attr_pkmode)
			entity:syncProps(EP.attr_faction_id)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1036 then
				local death_cnt = scene:getProps(SP.mlsd_defencer_count)
				death_cnt = death_cnt - 1
				if death_cnt <=0 then
					scene:syncFloatMessage("守卫全部被杀死, 行动失败, 神殿将在5秒之后被摧毁!")
					scene:addTimerEvent(3, 5000)
				else
					scene:syncFloatMessage("又一个守卫倒下了...注意保护守卫!")
					scene:setProps(SP.mlsd_defencer_count, death_cnt)
					scene:syncProps(SP.mlsd_defencer_count)
				end
			elseif sid==1037 then	--分裂
				local x, y = entity:getPosition()
				scene:addM(1035, x+1, y)
				scene:addM(1035, x+2, y)
				scene:addM(1035, x+3, y)
				scene:addM(1035, x-1, y)
				scene:addM(1035, x-2, y)
				scene:addM(1035, x-3, y)
			elseif sid ==1066 then
				scene:addProps(SceneProp.mlsd_lowpowcnt,-1)
			elseif sid ==1067 then
				scene:addProps(SceneProp.mlsd_highpowcnt,-1)
			end
		end
	end
}



--
--	副本: 魔剑封印	mjfy
--
gdMapExtension[MapID.mjfy] = {
	onLoad = function(scene)
		local btbl = {1040, 1041, 1042}
		local bossid = btbl[math.random(1,3)]
		scene:addM(bossid, 60, 71)
		scene:setProps(SP.mjfy_now_bossid,bossid)
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			if entity:getStaticID() ~= 1043 then
				scene:addM(1043, 90, 41)
				scene:setProps(SP.mjfy_now_bossid,1043)
			end
		end
	end,
}

--
--	副本: 魔神封印	msfy
--
gdMapExtension[MapID.msfy] = {
	onLoad = function(scene)
		local positions = {{26,37},{27,102},{92,103},{96,33}}
		local mids = {1079,1080,1081,1083}
		for k = 1, 4 do
			local k1 = math.random(1, 4)
			local k2 = math.random(1, 4)
			if k1~=k2 then
				mids[k1], mids[k2] = mids[k2], mids[k1]
			end
		end

		for k = 1, 4 do
			scene:addM(mids[k], positions[k][1], positions[k][2])
		end
	end,
}



--
--	副本: 地狱结界	dyjj
--
--gdMapExtension[MapID.dyjj] = {
--	onLoad = function(scene)
--		scene:addM(1044, 38, 61)
--		scene:addM(1044, 50, 51)
--		scene:addM(1044, 64, 65)
--		scene:addM(1044, 51, 74)
--		scene:addTimerEvent(1, 3000)
--		scene:setProps(SP.dyjj_defencer_count, 4)
--	end,

--	onTimerEvent =
--	{
--		[1] = function(scene)
--			scene:addProps(SP.dyjj_monster_wave)
--			scene:syncProps(SP.dyjj_monster_wave)
--			scene:addM(1047, 42, 51)
--			scene:addM(1048, 57, 50)
--			scene:addM(1047, 60, 68)
--			scene:addM(1048, 42, 68)
--			scene:addTimerEvent(1, 30000)
--		end,
--	},
--	onEntityEnter   = function(scene, entity)
--		if entity:isM() then
--			local sid = entity:getStaticID()
--			if sid==1044 or sid==1066 or sid==1067 then
--				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
--				entity:setProps(EP.attr_faction_id, 100)
--			else
--				entity:setProps(EP.attr_pkmode, EP.pk_FactionMOnly)
--				entity:setProps(EP.attr_faction_id, 101)
--				entity:setProps(EP.attr_m_center_x, math.random(40, 60))
--				entity:setProps(EP.attr_m_center_y, math.random(50, 70))
--				entity:setProps(EP.attr_mode, EP.emm_MarchingAggressive)
--			end
--		elseif entity:isP() then
--			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
--			entity:setProps(EP.attr_faction_id, 100)
--			scene:syncProps(SP.dyjj_defencer_count)
--			scene:syncProps(SP.dyjj_monster_wave)
--			entity:syncProps(EP.attr_pkmode)
--			entity:syncProps(EP.attr_faction_id)
--		end
--	end,
--	onEntityDie = function(scene, entity)
--		if entity:isM() and entity:getStaticID()==1044 then
--			local death_cnt = scene:getProps(SP.dyjj_defencer_count)
--			death_cnt = death_cnt - 1
--			if death_cnt<=0 then
--				scene:close()
--			else
--				scene:setProps(SP.dyjj_defencer_count, death_cnt)
--				scene:syncProps(SP.dyjj_defencer_count)
--			end
--		end
--	end,
--}


--
--	副本: 水寨	sz
--
gdMapExtension[MapID.sz] = {
	onLoad = function(scene)
		local m = scene:addM(1084, 78, 44)
		if m then
			scene:setProps(SP.xmfb_bossid, m:getID())
		end
		scene:addTimerEvent(1, 45000, -1)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=99 and percent~=0 then
				scene:forEachEntityP(function(entity)
					if entity:getProps(EP.attr_xmfb_buff)==0 then
						entity:addGene(60003)
						entity:setProps(EP.attr_xmfb_buff,2)
					end
				end)
			end
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1087 or sid==1088 or sid==1089 then
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 100)
			else
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 101)
			end
		elseif entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, 100)
			entity:syncProps(EP.attr_pkmode)
			entity:syncProps(EP.attr_faction_id)
			entity:addGene(50900)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() and entity:getStaticID()==1084 then
			scene:setProps(SP.xmfb_already_killed_boss, 1)
		end
		if entity:isM() and entity:getStaticID()==1088 then
			scene:addProps(SP.xmfb_already_summon_liemo, -1)
		end
	end
}

--
--	副本: 高家店	gjd
--

local gjd_boss_position = {68, 31}

gdMapExtension[MapID.gjd] = {
	onLoad = function(scene)
		--怪物默认数据配置为镇守模式, 不能移动, 远程搜索攻击
		local m = scene:addM(1085, gjd_boss_position[1], gjd_boss_position[2])
		if m then
			scene:setProps(SP.xmfb_bossid, m:getID())
		end
		scene:addTimerEvent(1, 2000, -1)
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=99 then
				scene:syncFloatMessage("当心, 不要被Boss抓住!")
				--log.info("###################### stage 1 ##########################")
				scene:rmvTimerEvent(1)
				scene:addTimerEvent(2, 2000, -1)
			end
		end,
		[2] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=90 then
				scene:syncFloatMessage("Boss开始召唤小乳猪了!")
				--log.info("###################### stage 2 ##########################")
				scene:rmvTimerEvent(2)
				--开始周期性召唤小乳猪
				scene:addTimerEvent(3, 2000, -1)
				scene:addTimerEvent(20, 5000, -1)
			end
		end,
		[3] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=10 then
				scene:syncFloatMessage("Boss进入疯狂状态了, 不要被他追上!")
				--log.info("###################### stage 3 ##########################")
				scene:rmvTimerEvent(3)
				scene:rmvTimerEvent(20)
				--变身可移动可攻击的模式
				m:setProps(EP.attr_mode, EP.emm_Aggressive)
				--默认技能为近战普通攻击
				m:setProps(EP.attr_m_default_skill, 1001)
				m:setProps(EP.attr_m_default_skill_distance, 1)
				m:addEffect(Effect.effect_violent)
			end
		end,
		[20] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local distance = 10
			for i = 1, 8 do
				local x = gjd_boss_position[1] + distance * math.sin(math.rad(22.5 + 45 * i))
				local y = gjd_boss_position[2] + distance * math.cos(math.rad(22.5 + 45 * i))
				local mrz = scene:addM(1097, x, y)
				if mrz then
					mrz:setProps(EP.attr_target_eid, m:getID())
					mrz:setState(EP.gst_Tracking)
				end
			end
			scene:resetTimerEvent(20, 60000, -1)
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1087 or sid==1088 or sid==1089 then
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 100)
			elseif sid==1097 then	--烤乳猪为独立的阵营
				entity:setProps(EP.attr_pkmode, EP.pk_FactionMOnly)
				entity:setProps(EP.attr_faction_id, 102)
			else
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 101)
			end
		elseif entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, 100)
			entity:syncProps(EP.attr_pkmode)
			entity:syncProps(EP.attr_faction_id)
			entity:addGene(50900)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() and entity:getStaticID()==1085 then
			scene:setProps(SP.xmfb_already_killed_boss, 1)
		end
		if entity:isM() and entity:getStaticID()==1088 then
			scene:addProps(SP.xmfb_already_summon_liemo, -1)
		end
	end
}

--
--	副本: 五指山下	wzsx
--

gdMapExtension[MapID.wzsx] = {
	onLoad = function(scene)
		local m = scene:addM(1086, 62, 61)
		if m then
			scene:setProps(SP.xmfb_bossid, m:getID())
		end
		scene:addTimerEvent(1, 2000, -1)
		--log.info("###################### stage 1 ##########################")
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=99 then
				scene:syncFloatMessage("Boss身上似乎存在防御结界!")
				--log.info("###################### stage 1 ##########################")
				scene:rmvTimerEvent(1)
				scene:addTimerEvent(2, 2000, -1)
			end
		end,
		[2] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=80 then
				scene:syncFloatMessage("Boss的防御结界被打破了, 开始召唤分身!")
				--log.info("###################### stage 2 ##########################")
				scene:rmvTimerEvent(2)
				scene:addTimerEvent(3, 2000, -1)
				scene:addTimerEvent(20, 3000, -1)
				--减去第一阶段的两防
				cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Min, -26 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max, -26 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Min, -26 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max, -26 * Combat.PercentToInt)
			end
		end,
		[3] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=50 then
				scene:syncFloatMessage("Boss从沉睡中苏醒过来了!")
				--log.info("###################### stage 3 ##########################")
				scene:rmvTimerEvent(3)
				scene:rmvTimerEvent(20)
				scene:addTimerEvent(4, 2000, -1)
				--变身可移动可攻击的模式
				m:setProps(EP.attr_mode, EP.emm_Aggressive)
			end
		end,
		[4] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=10 then
				scene:syncFloatMessage("Boss进入狂暴状态了!")
				--log.info("###################### stage 4 ##########################")
				scene:rmvTimerEvent(4)
				cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,300 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_PATK_Min,300 * Combat.PercentToInt)
				m:addEffect(Effect.effect_violent)
			end
		end,
		[20] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local x, y = m:getPosition()
			scene:addM(1096, x + 3, y)
			scene:addM(1096, x - 3, y)
			scene:addM(1096, x - 2, y - 2)
			scene:addM(1096, x - 2, y + 2)
			scene:addM(1096, x + 2, y - 2)
			scene:addM(1096, x + 2, y + 2)
			scene:resetTimerEvent(20, 30000, -1)
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1087 or sid==1088 or sid==1089 then
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 100)
			else
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 101)
			end
		elseif entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, 100)
			entity:syncProps(EP.attr_pkmode)
			entity:syncProps(EP.attr_faction_id)
			entity:addGene(50900)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1096 then
				local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
				if not m then
					return
				end
				local cbt = m:getCombatSys()
				if not cbt then
					return
				end
				cbt:updateHP(-90000)
			elseif sid==1086 then
				--石猴死后一定的几率召唤隐藏boss
				if math.random(1, 100)<=100 then
					scene:syncFloatMessage("小心, 石猴的真身正慢慢苏醒过来......")
					scene:addM(1098, entity:getPositionX(), entity:getPositionY())
				end
			end
		end
		if entity:isM() and entity:getStaticID()==1088 then
			scene:addProps(SP.xmfb_already_summon_liemo, -1)
		end
		if entity:isM() and entity:getStaticID()==1089 then
			scene:addProps(SP.xmfb_already_summon_liemohead, -1)
		end
	end
}


---
--- 	tdfb
---

gdMapExtension[9999] = {
	onLoad = function(scene)
		local m = scene:addM(2200, 30, 61)
		if m then
			scene:setProps(SP.tdfb_boss1id, m:getID())
		end
		local m2 = scene:addM(2200, 62, 61)
		if m2 then
			scene:setProps(SP.tdfb_boss2id, m2:getID())
		end

		m:setProps(EntityProp.attr_link_entity,m2:getID())
		m2:setProps(EntityProp.attr_link_entity,m:getID())

		m:addGene(20200)
		m2:addGene(20200)

		scene:addTimerEvent(1, 2000, -1)
		--log.info("###################### stage 1 ##########################")
	end,

	onTimerEvent =
	{
		[1] = function(scene) -- 检测boss血量，然后召唤
			local m = scene:getEntity(scene:getProps(SP.tdfb_boss1id))
			if not m then
				scene:rmvTimerEvent(1)
				return
			end

			local m2 = scene:getEntity(scene:getProps(SP.tdfb_boss2id))
			if not m2 then
				scene:rmvTimerEvent(1)
				return
			end

			local cbt1 = m:getCombatSys()
			if not cbt1 then
				scene:rmvTimerEvent(1)
				return
			end
			local hp1 = cbt1:getHP()
			local percent1 = cbt1:getProps(Combat.prop_HP) * 100 / cbt1:getProps(Combat.prop_HPMax)

			local cbt2 = m2:getCombatSys()
			if not cbt2 then
				scene:rmvTimerEvent(1)
				return
			end
			local hp2 = cbt2:getHP()
			local percent2 = cbt2:getProps(Combat.prop_HP) * 100 / cbt2:getProps(Combat.prop_HPMax)

			local is70 = scene:getProps(SP.tdfb_has70per)
			if is70 == 0 then
				if percent1 < 70 or percent2 < 70 then
					scene:setProps(SP.tdfb_has70per,1)

					if hp1 < hp2 then
						local posx,posy,posz = m2:getPosition()
						m:setProps(EntityProp.attr_m_last_patrol_x,posx + math.random(-3,3))
						m:setProps(EntityProp.attr_m_last_patrol_y,posy + math.random(-3,3))
						scene:flyEntity(m,posx + math.random(-1,1),posy + math.random(-1,1))
						scene:syncFloatMessage(m2:getName().."召唤了"..m:getName())
					else
						local posx,posy,posz = m:getPosition()
						m2:setProps(EntityProp.attr_m_last_patrol_x,posx + math.random(-3,3))
						m2:setProps(EntityProp.attr_m_last_patrol_y,posy + math.random(-3,3))
						scene:flyEntity(m2,posx + math.random(-1,1),posy + math.random(-1,1))
						scene:syncFloatMessage(m:getName().."召唤了"..m2:getName())
					end
					scene:rmvTimerEvent(1)
					scene:addTimerEvent(2, 10000, 1)
					-- summon life down boss
				end

				return
			end

			local is50 = scene:getProps(SP.tdfb_has50per)
			if is50 == 0 then
				if percent1 < 50 or percent2 < 50 then
					scene:setProps(SP.tdfb_has70per,1)
					scene:setProps(SP.tdfb_has50per,1)


					if hp1 < hp2 then
						local posx,posy,posz = m2:getPosition()
						m:setProps(EntityProp.attr_m_last_patrol_x,posx + math.random(-3,3))
						m:setProps(EntityProp.attr_m_last_patrol_y,posy + math.random(-3,3))
						scene:flyEntity(m,posx + math.random(-1,1),posy + math.random(-1,1))
						scene:syncFloatMessage(m2:getName().."召唤了"..m:getName())
					else
						local posx,posy,posz = m:getPosition()
						m2:setProps(EntityProp.attr_m_last_patrol_x,posx + math.random(-3,3))
						m2:setProps(EntityProp.attr_m_last_patrol_y,posy + math.random(-3,3))
						scene:flyEntity(m2,posx + math.random(-1,1),posy + math.random(-1,1))
						scene:syncFloatMessage(m:getName().."召唤了"..m2:getName())
					end
					scene:rmvTimerEvent(1)
					scene:addTimerEvent(2, 10000, 1)

				end

				return
			end

			local is25 = scene:getProps(SP.tdfb_has25per)
			if is25 == 0 then
				if percent1 < 25 or percent2 < 25 then
					scene:setProps(SP.tdfb_has25per,1)
					scene:setProps(SP.tdfb_has70per,1)
					scene:setProps(SP.tdfb_has50per,1)

					if hp1 < hp2 then
						local posx,posy,posz = m2:getPosition()
						m:setProps(EntityProp.attr_m_last_patrol_x,posx + math.random(-3,3))
						m:setProps(EntityProp.attr_m_last_patrol_y,posy + math.random(-3,3))
						scene:flyEntity(m,posx + math.random(-1,1),posy + math.random(-1,1))
						scene:syncFloatMessage(m2:getName().."召唤了"..m:getName())
					else
						local posx,posy,posz = m:getPosition()
						m2:setProps(EntityProp.attr_m_last_patrol_x,posx + math.random(-3,3))
						m2:setProps(EntityProp.attr_m_last_patrol_y,posy + math.random(-3,3))
						scene:flyEntity(m2,posx + math.random(-1,1),posy + math.random(-1,1))
						scene:syncFloatMessage(m:getName().."召唤了"..m2:getName())
					end
					scene:rmvTimerEvent(1)
					scene:addTimerEvent(2, 10000, 1)
				end

				return
			end

		end,

		[2] = function(scene) -- 10s内boss没有离开3个tile boss融合
			local m = scene:getEntity(scene:getProps(SP.tdfb_boss1id))
			if not m then
				return
			end

			local m2 = scene:getEntity(scene:getProps(SP.tdfb_boss2id))
			if not m2 then
				return
			end

			local posx1,posy1,posz1 = m:getPosition()
			local posx2,posy2,posz2 = m2:getPosition()

			if math.abs(posx1 - posx2) <= 3 and math.abs(posy1- posy2) <= 3 then
				scene:rmvEntity(m:getID())
				scene:rmvEntity(m2:getID())

				local m3 = scene:addM(2201, posx1, posy1)
				scene:syncFloatMessage(m:getName().."和"..m2:getName().."融合了！")

			else
				scene:addTimerEvent(1, 2000, -1)
			end

		end,

	},
	onEntityEnter   = function(scene, entity)

	end,
	onEntityDie = function(scene, entity)

	end
}

--
--	活动: 五行炼狱	wxly
--
local wxly_element_monster = {
	[1] = 1068, --金
	[2] = 1069, --木
	[3] = 1070, --水
	[4] = 1071, --火
	[5] = 1072, --土
}

local wxly_monster_element = {}
for k, v in pairs(wxly_element_monster) do
	wxly_monster_element[v] = k
end

local wxly_element_boss = {
	[1] = 1073, --金
	[2] = 1074, --木
	[3] = 1075, --水
	[4] = 1076, --火
	[5] = 1077, --土
}
local wxly_boss_element = {}
for k, v in pairs(wxly_element_boss) do
	wxly_boss_element[v] = k
end

local function wxly_refresh_next_monster(scene,entity)
	local msid = wxly_element_monster[math.random(1,5)]
	if entity then
		msid = entity:getStaticID()
		local melem = wxly_monster_element[msid]
		if melem then
			melem = melem+1
			if melem>5 then
				melem = 1
			end
			msid = wxly_element_monster[melem]
		end
	end

	scene:addM(msid, entity:getPositionX(), entity:getPositionY())
	scene:rmvEntity(entity:getID())

	--检查是否符合削弱条件
	local boss
	local mElement = 0
	local mCnt = 0
	scene:forEachEntityM(function(entity)
					if entity:isM() then
						local sid = entity:getStaticID()
						if wxly_boss_element[sid] then--boss
							boss = entity
						elseif wxly_monster_element[sid] then --护卫
							local ele = wxly_monster_element[sid]
							if mElement == ele then
								mCnt = mCnt+1
							else
								mElement = ele
								mCnt = 1
							end
						end
					end
				end)
	if mCnt>=5 and boss then
		mElement = mElement+1
		if mElement>5 then
			mElement = 1
		end
		if mElement == wxly_boss_element[boss:getStaticID()] then
			local cbt = boss:getCombatSys()
			if cbt then
				scene:syncFloatMessage("五行克制被成功激活, 炼狱魔王被大大削弱!")
				--削弱boss攻击力到原来的20%
				cbt:setProps(Combat.prop_PATK_Min, 0.2 * cbt:getProps(Combat.prop_PATK_Min))
				cbt:setProps(Combat.prop_PATK_Max, 0.2 * cbt:getProps(Combat.prop_PATK_Max))
				cbt:setProps(Combat.prop_MATK_Min, 0.2 * cbt:getProps(Combat.prop_MATK_Min))
				cbt:setProps(Combat.prop_MATK_Max, 0.2 * cbt:getProps(Combat.prop_MATK_Max))
			end
		end
	end
end

local function wxly_refresh_next_boss(scene,entity)
	--删除所有的守卫
	scene:forEachEntityM(function(entity)
					if entity:isM() then
						if wxly_monster_element[entity:getStaticID()] then
							scene:rmvEntity(entity:getID())
						end
					end
				end)

	local msid = wxly_element_boss[math.random(1,5)]
	if entity then
		msid = entity:getStaticID()
		local melem = wxly_boss_element[msid]
		if melem then
			melem = melem+1
			if melem>5 then
				melem = 1
			end
			msid = wxly_element_boss[melem]
		end
	end
	local boss = scene:addM(msid,29,45)

	local postbl = {{29,18}, {45,37}, {43,64}, {14,64}, {14,37}}
	for k = 1, 5 do
		local k1 = math.random(1, 5)
		local k2 = math.random(1, 5)
		if k1~=k2 then
			postbl[k1], postbl[k2] = postbl[k2], postbl[k1]
		end
	end

	for k, pos in ipairs(postbl) do
		scene:addM(wxly_element_monster[k], pos[1], pos[2])
	end
end

gdMapExtension[MapID.wxly] = {
	onLoad = function(scene)
		wxly_refresh_next_boss(scene)
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if wxly_boss_element[sid] then
				local cnt = scene:getProps(SceneProp.wxly_boss_kill_cnt)
				cnt = cnt+1
				scene:setProps(SceneProp.wxly_boss_kill_cnt,cnt)
				scene:syncProps(SceneProp.wxly_boss_kill_cnt)
				if cnt == 5 then--胜利
					if math.random(1,100)<=100 then--出现魔尊
						scene:syncFloatMessage("沉睡几千年的魔尊慢慢苏醒过来......")
						local boss = scene:addM(1078,entity:getPositionX(),entity:getPositionY())
					end
				elseif cnt<5 then
					wxly_refresh_next_boss(scene,entity)
				end
			elseif wxly_monster_element[sid] then
				wxly_refresh_next_monster(scene,entity)
			end
		end
	end
}

--
--	副本: 转生神殿	zssd
--

local function zssd_refresh(scene)
	for i= 1, 10 do -- 24 34
		scene:addM(1061, math.random(19, 28),  math.random(31, 37))
	end
end

local function zssd_refresh_next(scene)
	log.info("wave = "..scene:getProps(SP.zssd_monster_wave))
	scene:addProps(SP.zssd_monster_wave)
	scene:syncProps(SP.zssd_monster_wave)
	if scene:getProps(SP.zssd_monster_wave) >= 2 then
		scene:rmvTimerEvent(1)
		scene:rmvTimerEvent(2)
		scene:syncFloatMessage("最后一波怪物刷新了")
	else
		scene:syncFloatMessage("又一大波怪物刷新了")
	end

	zssd_refresh(scene)
end

gdMapExtension[MapID.zssd] = {
	onLoad = function(scene)
		zssd_refresh(scene)
		scene:addTimerEvent(1, 300000, 5)	--5分钟
		scene:addTimerEvent(2, 2000, -1)	--5分钟
	end,
	onTimerEvent =
	{
		[1] = function(scene)
			zssd_refresh_next(scene)
		end,
		[2] = function(scene)
			if scene:getEntityMCount()<1 then
				zssd_refresh_next(scene)
			end
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isP() then
			scene:syncProps(SP.zssd_monster_wave)
			scene:syncProps(SP.zssd_kill_count)
		end
	end,
	onEntityLeave   = function(scene, entity)
		if entity:isP() then
			entity:saveProps(EP.attr_rebornrqeitem)
			entity:syncProps(EP.attr_rebornrqeitem)
		end
	end,
	onEntityDie   = function(scene, entity)
		if entity:isM() then
			local entitykiller = entity:getCombatKiller()
			
			-- 如果是道士狗或宠物,则找到最终的玩家
			if entitykiller and (entitykiller:isDog() or entitykiller:isPet()) then
				entitykiller = entitykiller:getOwner()
			end
			
			if entitykiller and entitykiller:isP() then
				local kc = scene:getProps(SP.zssd_kill_count)
				kc = kc + 1
				entitykiller:addProps(EP.attr_rebornrqeitem,5)
				--if kc==40 then
				--	entitykiller:addProps(EP.attr_rebornrqeitem, 50)
				--elseif kc==50 then
				--	entitykiller:addProps(EP.attr_rebornrqeitem, 75)
				--elseif kc==60 then
				--	entitykiller:addProps(EP.attr_rebornrqeitem, 100)
				--end
				scene:setProps(SP.zssd_kill_count, kc)
				scene:syncProps(SP.zssd_kill_count)
				entitykiller:syncProps(EP.attr_rebornrqeitem)
			end
		end
	end,
}

--
--	活动: 攻城战	gcz
--
--WP.city_master_guild WorldDataX 临时守城行会ID
--WP.city_master_guild WorldDataY 上届守城行会ID
--WP.city_master_guild WorldDataZ 连续守城成功次数

-- EventData  X  击杀数
-- EventData  Y  是否领取过奖励
-- EventData


--战车出场
function Scene.gcz_add_chariot(scene,entity,lvl)
	local gcz_chariot_id = {
		1066,
		1066,
		1067,
		1067,
	}
	local sid = gcz_chariot_id[lvl]
	if not sid or sid<=0 then
		return
	end
	local chariot = scene:addM(sid, 321, 167)
	chariot:setProps(EP.attr_pkmode, EP.pk_Guild)
	chariot:setProps(EP.attr_m_center_x, 288)
	chariot:setProps(EP.attr_m_center_y, 142)
	chariot:setProps(EP.attr_mode, EP.emm_MarchingAggressive)
	local guild = entity:getGuild()
	local gid = guild:getID()
	if guild and gid>0 then
		chariot:setProps(EP.attr_guild_id,gid)
	end
end
--箭塔
local gcz_tower_id = {
		2141, 	2141,
		2141, 	2141,
		2141, 	2141,
	}
local gcz_tower_positions = {
		{309, 153}, 	{305, 157},
		{295, 150}, 	{300, 146},
		{286, 143}, 	{290, 140},
	}

local function gcz_add_tower(scene)
	local mguild = _G.getWorldDataX(WP.city_master_guild) --守城方行会ID
	local towercnt = 6
	scene:setProps(SP.gcz_tower_group_count,towercnt/2)
	for i=1,towercnt,1 do
		local sid = gcz_tower_id[i]
		local pos = gcz_tower_positions[i]
		local tower = scene:addM(sid, pos[1], pos[2])
		tower:setProps(EP.attr_pkmode, EP.pk_Guild)
		tower:setProps(EP.attr_guild_id,mguild)
	end
end
--攻城战期间 Monster消失 守卫死亡，箭塔摧毁，神兽死亡
local function gcz_monster_destroy(scene,entity)
	if entity:getStaticID()==500 then --墙倒了
		local posx,posy = entity:getPosition()
		scene:addS(307,posx,posy)
		_G.syncFloatMessage("沙皇宫城墙倒塌，大家冲进去啊！")
	elseif entity:getStaticID()==2141 then --箭塔毁坏
		local towercnt = scene:getProps(SP.gcz_tower_group_count)
		towercnt = towercnt-1
		if towercnt<0 then
			towercnt = 0
		end
		scene:setProps(SP.gcz_tower_group_count,towercnt)
		_G.syncFloatMessage("又一个箭楼被攻占了！")
	end
end
--城墙
local function gcz_add_wall(scene)
	local mguild = _G.getWorldDataX(WP.city_master_guild) --守城方行会ID
	local leftwall = scene:addM(500,283,143)
	local rightwall = scene:addM(500,290,138)
	leftwall:setProps(EP.attr_guild_id,mguild)
	rightwall:setProps(EP.attr_guild_id,mguild)
end

--累计停留时间
--皇宫 进 sc 保持不变 shg 开始计时
--皇宫 出 sc 保持不变 shg 计时清零
--皇宫 死 sc 计时清零 shg 计时清零
--沙城 进 sc 开始计时 shg 计时清零 未考虑城区范围
--沙城 出 sc 计时清零 shg 计时清零 无需考虑城区范围
--沙城 死 sc 计时清零 shg 计时清零 无需考虑城区范围

--检查停留时间
local function gcz_check_holdtime(entity)
	if not entity:isP() then
		return
	end
	local sc_time = entity:getProps(EP.gcz_sc_holdtime)
	local sc_hasreward = entity:getProps(EP.gcz_sc_hasreward)
	local shg_time = entity:getProps(EP.gcz_shg_holdtime)
	local shg_hasreward = entity:getProps(EP.gcz_shg_hasreward)
	if not sc_time or not sc_hasreward or not shg_time or not shg_hasreward then
		return
	end
	local curtime = os.time()
	log.info("_________gcz_check_holdtime__os time",curtime)
	if sc_hasreward<=0 then--沙城没有发过奖
		local dur = curtime-sc_time
		if dur>=20*60*1000 then
			--do reward
			entity:setProps(EP.gcz_sc_hasreward,1)
		end
	end
	if shg_hasreward<=0 then--沙皇宫没有发过奖
		local dur = curtime-shg_time
		if dur>=10*60*1000 then
			--do reward
			entity:setProps(EP.gcz_shg_hasreward,1)
		end
	end
end

local function gcz_sc_holdtime_update(entity,option)
end
local function gcz_shg_holdtime_update(entity,option)
end
--玛法神力 mafa=0去掉玛法神力buff mafa=1增加玛法神力buff
local function gcz_mafa_buff(entity,mafa)
--[[	local curstatus = entity:getProps(EP.gcz_mafa_buff)
	local cbt = entity:getCombatSys()
	if not cbt then
		return
	end
	local curgid = _G.getWorldDataX(WP.city_master_guild)
	local lastgid = _G.getWorldDataY(WP.city_master_guild)
	if curgid~=lastgid then
		return
	end
	local guild = entity:getGuild()
	if not guild then
		return
	end
	if guild:getID()==lastgid then
		return
	end
	local curcnt = _G.getWorldDataZ(EID.gcz)
	local increase = 1+curcnt/10
	if mafa == 0 then
		if curstatus == 0 then

		else
			for i=5,10,1 do
				cbt:setProps(i,cbt:getProps(i)*increase)
			end
		end
	else
		if curstatus == 0 then
			for i=5,10,1 do
				cbt:setProps(i,cbt:getProps(i)/increase)
			end
		else

		end
	end
	entity:setProps(EP.gcz_mafa_buff,mafa)]]
end
--复仇之怒 defense=0去掉复仇之怒buff mafa=1增加复仇之怒buff
local function gcz_defense_buff(entity,defense)
--[[	local curstatus = entity:getProps(EP.gcz_defense_buff)
	local cbt = entity:getCombatSys()
	if not cbt then
		return
	end
	local curcnt = entity:getProps(EP.gcz_dead_count)
	local increase = 1+curcnt/10
	if mafa == 0 then
		if curstatus == 0 then

		else
			for i=11,14,1 do
				cbt:setProps(i,cbt:getProps(i)*increase)
			end
		end
	else
		if curstatus == 0 then
			for i=11,14,1 do
				cbt:setProps(i,cbt:getProps(i)/increase)
			end
		else

		end
	end
	entity:setProps(EP.gcz_defense_buff,defense)]]
end

local function gcz_kill_broadcast(killer, dead, cnt)
	local post = killer:getProps(EP.attr_guild_post)
	local role = nil
	if post == GuildProp.post_master then
		role = "会长"
	elseif post == GuildProp.post_second_master then
		role = "副会长"
	else
		return
	end
	local guild = killer:getGuild()
	if not guild then
		return
	end
	local praise = ""
	if cnt<2 then
		praise = "一刀毙命"
	elseif cnt<4 then
		praise = "连战连捷"
	elseif cnt<7 then
		praise = "大杀四方"
	elseif cnt<10 then
		praise = "人挡杀人"
	else
		praise = "神档杀神"
	end
	_G.syncFloatMessage(guild:getGuildName().."公会"..role..killer:getName().."击杀了"..dead:getName()..","..praise)
end

--更新杀敌数和勇气值
local function gcz_kill_count_update(scene,entity)

	local entitykiller = entity:getCombatKiller()
	if entitykiller and entitykiller:isP() then
		--杀敌数
		-- TODO check entity's guild is in gcz

		local guildid = entity:getProps(EP.attr_guild_id)

		local reborn = entity:getProps(EP.attr_reborn)
		local deadlvl = entity:getLevel()
		local killerlvl = entitykiller:getLevel()
		if (reborn > 0) or (deadlvl >= 50 and killerlvl - deadlvl < 10)then
			entitykiller:addEventDataX(EID.gcz)
			entitykiller:setEventDataY(EID.gcz,0)
			entitykiller:saveEventData(EID.gcz)
			entitykiller:syncEventData(EID.gcz)

			gcz_kill_broadcast(entitykiller, entity, entitykiller:getEventDataX(EID.gcz))

			local killerkill = entitykiller:getEventDataX(EID.gcz)

			local killmost = _G.getWorldDataY(WorldProp.prop_gcz_kill_most)
			if (killmost < killerkill) then
				_G.setWorldDataX(WorldProp.prop_gcz_kill_most,entitykiller:getGlobalID())
				_G.setWorldDataY(WorldProp.prop_gcz_kill_most,killerkill)
				_G.setWorldDataZ(WorldProp.prop_gcz_kill_most,0)
				_G.setWorldDataStr(WorldProp.prop_gcz_kill_most,entitykiller:getName())
				_G.saveWorldData(WorldProp.prop_gcz_kill_most)
				_G.syncFloatMessage(entitykiller:getName().."在攻城战中目前杀敌数第一! 杀敌数为："..killerkill)
			end
		end
		gcz_defense_buff(entitykiller,0)
	end


	--勇气值

	entity:addEventDataY(EID.gcz)
	entity:saveEventData(EID.gcz)

	gcz_defense_buff(entity,1)

end



-- 土城系统
gdMapExtension[MapID.tc] = {
	onLoad = function(scene)
		-- 怪物攻城状态初始化
		scene:setProps(SP.siege_active, 0)
		scene:setProps(SP.siege_wave, 0)
		scene:setProps(SP.siege_start_time, 0)
		scene:setProps(SP.siege_monster_count, 0)
		scene:setProps(SP.siege_last_9pm_hour, 0)
		scene:setProps(SP.siege_last_9pm_minute, 0)
	end,
	
	onTimerEvent = {
		-- 全服祈福回调
		[100] = function(scene)
			local tcnt = scene:getProps(SP.qfxz_scene_data)
			if tcnt>0 then
				scene:setProps(SP.qfxz_scene_data, 0)
				
				local pcnt = 0
				scene:forEachEntityP(function(entity)
					if entity:getProps(EP.attr_is_safe)>0 then
						pcnt = pcnt + 1
					end
				end)
				if pcnt<=0 then
					pcnt = 1
				end
				tcnt = math.ceil(tcnt/pcnt)
				scene:forEachEntityP(function(entity)
					if entity:getProps(EP.attr_is_safe)>0 then
						entity:addCoupon(tcnt,Opcode.qifuxianziscene)
					end
				end)
			end
		end,
		-- 行会祈福回调
		[101] = function(scene)
			local tcnt = scene:getProps(SP.qfxz_guild_data)
			if tcnt>0 then
				local guild = _G.getGuild(scene:getProps(SP.qfxz_guild_id))
				if not guild then
					return
				end
				scene:setProps(SP.qfxz_guild_data, 0)
				scene:setProps(SP.qfxz_guild_id, 0)
				
				local pcnt = 0
				guild:forEach(function(entity)
					pcnt = pcnt + 1
				end)
				if pcnt<=0 then
					pcnt = 1
				end
				tcnt = math.ceil(tcnt/pcnt)
				guild:forEach(function(entity)
					entity:addCoupon(tcnt,Opcode.qifuxianziguild)
				end)
			end
		end,
	},
	
	onTeleport = function(scene, entity, portal)
		if portal.tag==1 then
			local cmgid = _G.getWorldDataX(WP.city_master_guild)
			if entity:getProps(EP.attr_guild_id) == cmgid then
				if Event.isActive(EID.gcz) then
					gdScnMgr:enterScene(entity,MapID.gczshg,portal.tgtx,portal.tgty)
				else
					gdScnMgr:enterScene(entity,portal.id,portal.tgtx,portal.tgty)
				end
				return Error.Success
			else
				return Error.err_guild_NotCityMasterGuild
			end
		elseif portal.tag==2 then
			local lvl = entity:getLevel()
			if lvl >= 40 then
				if Event.isActive(EID.gcz) then
					gdScnMgr:enterScene(entity,portal.id,portal.tgtx,portal.tgty)
				end
			end
			return Error.Success
		end
		return Error.Unknown
	end,
	
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			
			-- 亢金龙残影处理
			if sid==5315 then
				local count = 0
				scene:forEachEntityM(function (ettm)
					local ssid = ettm:getStaticID()
					if ssid==5315 and ettm:isAlive() then
						count = count+1
					end
				end)
				if count>0 then
					_G.syncFloatMessage("亢金龙残影被击杀， 还有".. count .. "只亢金龙残影藏在土城野外， 大家快去寻找！")
				else
					_G.syncFloatMessage("亢金龙残影已经全部被击杀!")
				end
				return
			end
			
			-- 怪物攻城怪物处理
			if sid >= 5600 and sid <= 5604 then
				if scene:getProps(SP.siege_active) == 1 then
					-- 获取击杀者
					local killer = entity:getCombatKiller()
					local wave = scene:getProps(SP.siege_wave) or 0
					
					-- 计算基础奖励
					local baseExp = wave * 1000000000
					local baseGold = wave * 500
					
					-- 混合奖励机制
					local attackers = {}
					local canGetAttackers = false
					
					-- 尝试获取所有攻击者
					if entity.forEachAttacker then
						entity:forEachAttacker(function(attacker, damage)
							if attacker:isP() then
								table.insert(attackers, attacker)
							end
						end)
						canGetAttackers = true
					end
					
					-- 如果无法获取攻击者列表或只有击杀者
					if not canGetAttackers or (#attackers == 0 and killer) then
						-- 只有击杀者获得奖励
						if killer and killer:isP() then
							killer:addExp(baseExp)
							killer:addGold(baseGold)
							killer:syncFloatMessage(string.format("击杀第%d波怪物！获得经验%s，元宝%s", 
								wave, baseExp, baseGold))
							
							-- 10%几率掉落中级灵石
							if math.random(1, 100) <= 10 then
								killer:addItem(41001, 1)
								killer:syncFloatMessage("幸运掉落中级灵石")
							end
						end
					else
						-- 有多个攻击者，使用平均分配
						local allAttackers = {}
						
						-- 收集所有攻击者
						for _, attacker in ipairs(attackers) do
							if attacker:isP() then
								allAttackers[attacker] = true
							end
						end
						
						-- 确保击杀者也在列表中
						if killer and killer:isP() then
							allAttackers[killer] = true
						end
						
						-- 计算参与者数量
						local participantCount = 0
						for _ in pairs(allAttackers) do
							participantCount = participantCount + 1
						end
						
						if participantCount > 0 then
							-- 计算每人获得的奖励
							local expPerPlayer = math.floor(baseExp / participantCount)
							local goldPerPlayer = math.floor(baseGold / participantCount)
							
							-- 给所有参与者发放奖励
							for player, _ in pairs(allAttackers) do
								if player:isP() then
									player:addExp(expPerPlayer)
									player:addGold(goldPerPlayer)
									
									if player == killer then
										player:syncFloatMessage(string.format("成功击杀第%d波怪物！获得经验%s，元宝%s", 
											wave, expPerPlayer, goldPerPlayer))
										
										-- 只有击杀者有几率获得中级灵石
										if math.random(1, 100) <= 10 then
											player:addItem(41001, 1)
											player:syncFloatMessage("幸运掉落中级灵石")
										end
									else
										player:syncFloatMessage(string.format("参与击杀第%d波怪物获得经验%s，元宝%s", 
											wave, expPerPlayer, goldPerPlayer))
									end
								end
							end
						end
					end
					
					-- 减少剩余怪物计数
					local count = scene:getProps(SP.siege_monster_count) or 0
					if count > 0 then
						scene:setProps(SP.siege_monster_count, count - 1)
						
						-- 如果本波怪物全部死亡，检查是否进入下一波
						if count - 1 <= 0 then
							local currentWave = scene:getProps(SP.siege_wave) or 0
							
							-- 如果还有下一波，立即生成
							if currentWave < 5 then
								local nextWave = currentWave + 1
								spawnNextWave(scene, nextWave)
							else
								-- 最终波被击杀，攻城成功
								_G.syncFloatMessage("★★★ 最终BOSS被击杀，怪物攻城防守成功！ ★★★")

								-- 发放成功奖励（VIP10限制）
								_G.syncFloatMessage("★★★ 攻城成功！只有VIP10玩家可领取完整奖励 ★★★")

								scene:forEachEntityP(function(player)
									-- 使用VIP检查代码
									if Vip.getVipLevel(player) < 10 then
										-- 非VIP10玩家获得基础安慰奖
										player:addItem(41001, 5)
										player:addExp(100000000)
										player:addGold(50000)
										player:syncFloatMessage("获得：基础安慰奖（非VIP10玩家）")
									else
										-- VIP10及以上玩家获得完整奖励
										player:addItem(41001, 50)
										player:addExp(100000000000)
										player:addGold(880000)
										player:syncFloatMessage("获得：中品灵石×50 + 经验1000亿 + 元宝88万")
									end
								end)
								
								-- 结束攻城
								endSiege(scene, true)
							end
						end
					end
				end
			end
		end
	end
}

-- ======================== 怪物攻城核心函数 ========================

-- 开始怪物攻城
function startSiege(scene)
	-- 设置攻城状态
	scene:setProps(SP.siege_active, 1)
	scene:setProps(SP.siege_start_time, os.time())
	scene:setProps(SP.siege_wave, 1)
	
	-- 立即生成第1波
	spawnNextWave(scene, 1, nil)
	
	-- 设置20分钟总时间限制
	scene:addTimerEvent(500, 1200000, 1, function()
		if scene:getProps(SP.siege_active) == 1 then
			_G.syncFloatMessage("★★★ 20分钟时间到，怪物攻城结束！ ★★★")
			endSiege(scene, false)
		end
	end)
end

-- 生成下一波怪物
function spawnNextWave(scene, waveNum, guildname)
	scene:setProps(SP.siege_wave, waveNum)
	
	local monsterId = 5600
	local count = 80
	local name = "怪物"
	
	if waveNum == 1 then
		monsterId = 5600
		count = 80
		name = "怪物"
	elseif waveNum == 2 then
		monsterId = 5601
		count = 60
		name = "怪物"
	elseif waveNum == 3 then
		monsterId = 5602
		count = 50
		name = "怪物小boos"
	elseif waveNum == 4 then
		monsterId = 5603
		count = 40
		name = "攻城小boos"
	elseif waveNum == 5 then
		monsterId = 5604
		count = 30
		name = "攻城boos"
	else
		return
	end
	
	scene:setProps(SP.siege_monster_count, count)
	
	-- 全服公告
	if guildname then
		if waveNum == 1 then
			_G.syncFloatMessage("★★★ 怪物攻城开始！" .. guildname .. "行会请立即回防土城！ ★★★")
			_G.syncFloatMessage(string.format("★★★ 第1波：%s × %d 目标：%s行会 ★★★", name, count, guildname))
		else
			_G.syncFloatMessage(string.format("★★★ 第%d波：%s × %d 目标：%s行会 ★★★", waveNum, name, count, guildname))
		end
	else
		if waveNum == 1 then
			_G.syncFloatMessage("★★★ 怪物攻城开始！全体玩家到土城防守！ ★★★")
			_G.syncFloatMessage(string.format("★★★ 第1波：%s × %d ★★★", name, count))
		else
			_G.syncFloatMessage(string.format("★★★ 第%d波：%s × %d ★★★", waveNum, name, count))
		end
	end
	
	-- 使用指定坐标
	local positions = {
		{x=56, y=78},
		{x=101, y=88},
		{x=73, y=61},
		{x=86, y=101}
	}
	
	local spawned = 0
	
	for i = 1, count do
		local posIndex = ((i-1) % 4) + 1
		local pos = positions[posIndex]
		
		local monster = scene:addM(monsterId, pos.x, pos.y)
		if monster then
			if guildname then
				monster:setProps(EP.attr_name, "入侵怪-" .. name .. "-" .. guildname)
			else
				monster:setProps(EP.attr_name, "攻城怪物-" .. name)
			end
			spawned = spawned + 1
		end
	end
	
	if guildname then
		_G.syncFloatMessage(string.format("第%d波怪物生成完成：%d只，目标：%s行会", waveNum, spawned, guildname))
	else
		_G.syncFloatMessage(string.format("第%d波怪物生成完成：%d只", waveNum, spawned))
	end
	
	if waveNum == 5 then
		if guildname then
			_G.syncFloatMessage("★★★ 最终BOSS降临！" .. guildname .. "行会集中火力！ ★★★")
		else
			_G.syncFloatMessage("★★★ 最终BOSS降临！全体玩家集中火力！ ★★★")
		end
	else
		local nextWave = waveNum + 1
		if guildname then
			_G.syncFloatMessage(string.format("第%d波将在2分钟后到达！目标：%s行会", nextWave, guildname))
		else
			_G.syncFloatMessage(string.format("第%d波将在2分钟后到达！", nextWave))
		end
		
		scene:addTimerEvent(500 + waveNum, 120000, 1, function()
			if scene:getProps(SP.siege_active) == 1 and scene:getProps(SP.siege_wave) == waveNum then
				spawnNextWave(scene, nextWave, guildname)
			end
		end)
	end
end

-- 结束怪物攻城
function endSiege(scene, success)
	-- 重置状态
	scene:setProps(SP.siege_active, 0)
	scene:setProps(SP.siege_wave, 0)
	scene:setProps(SP.siege_monster_count, 0)
	scene:setProps(SP.siege_start_time, 0)
	scene:setProps(SP.siege_trigger_guild, "")
	
	if success then
		_G.syncFloatMessage("★★★ 怪物攻城结束！防守成功！ ★★★")
	else
		_G.syncFloatMessage("★★★ 怪物攻城结束！时间到！ ★★★")
	end
end

















local function gcz_exp_sc(entity)
	local lvl = entity:getLevel()
	if not entity:isAlive() or lvl<40  then
		return
	end
	entity:addExp( gdGame.getGirlExp(0, lvl), Opcode.gcz_period_exp)
end

local function gcz_exp_shg_small(entity)
	local lvl = entity:getLevel()
	if not entity:isAlive() or lvl<40 then
		return
	end
	local baseexp = gdFireExp[lvl]
	if not baseexp then
		baseexp = 100
	end

	entity:addExp(baseexp*10, Opcode.gcz_period_exp)
end

local function gcz_exp_shg_big(entity)
	local lvl = entity:getLevel()
	if not entity:isAlive() or lvl<40  then
		return
	end
	entity:addExp( gdGame.getGirlExp(2, lvl), Opcode.gcz_period_exp)
end

local function gcz_insist_time_update(entity)
	if entity:getProps(EP.gcz_insist_time) >= 20 then
		DailyAct.AddTargetCnt(entity, EID.mrmrsc)
		return
	end

	entity:addProps(EP.gcz_insist_time, 1)
end

--
--	沙城秘道	scmd
--
gdMapExtension[MapID.scmd] =
{
	onTeleport = function(scene, entity, portal)
		if Event.isActive(EID.gcz) then
			local lvl = entity:getLevel()
			if lvl >= 35 then
				gdScnMgr:enterScene(entity,portal.id,portal.tgtx,portal.tgty)
			end
		else
			gdScnMgr:enterScene(entity,MapID.tc,portal.tgtx,portal.tgty)
		end
		return Error.Success
	end,
}


--
--	攻城战沙城	gczsc
--
gdMapExtension[MapID.sc] =
{
	onLoad = function(scene)
		scene:setProps(SP.prop_block_player, 1)
		_G.syncFloatMessage("请报名的行会速速前往沙城！")
		gcz_add_wall(scene)
		gcz_add_tower(scene)
		scene:addTimerEvent(1010, 600000, -1)
	end,
	onTimerEvent =
	{
		[1] = function(scene)--检查停留时间发放奖励
		end,
		[1010] = function(scene)	--十分钟一次经验
			scene:forEachEntityP(gcz_exp_sc)
		end,
	},
	onEntityEnter   = function(scene, entity)
		entity:setProps(EP.attr_pkmode, EP.pk_Guild)
		entity:syncProps(EP.attr_pkmode)
		if entity:isP() then
			gcz_mafa_buff(entity,1)
		end
	end,
	onEntityLeave	= function(scene, entity)
		if entity:isP() then
			gcz_mafa_buff(entity,0)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			gcz_monster_destroy(scene,entity)
		elseif entity:isP() then
			gcz_kill_count_update(scene, entity)
			gcz_mafa_buff(entity,0)
		end
	end,
	onSceneClose= function(scene)
	end,
	onTeleport = function(scene, entity, portal)
		local cmgid = _G.getWorldDataX(WP.city_master_guild)
		if entity:getProps(EP.attr_guild_id) == cmgid then
			gdScnMgr:enterScene(entity,portal.id,portal.tgtx,portal.tgty)
			return Error.Success
		else
			return Error.err_guild_NotCityMasterGuild
		end
	end,
}

--
--	普通沙皇宫	shg
--

gdMapExtension[MapID.shg] =
{
	onTeleport = function(scene, entity, portal)
		if Event.isActive(EID.gcz) then
			local lvl = entity:getLevel()
			if lvl >= 35 then
				gdScnMgr:enterScene(entity,MapID.sc,portal.tgtx,portal.tgty)
				return Error.Success
			end
		else
			gdScnMgr:enterScene(entity,portal.id,portal.tgtx,portal.tgty)
			return Error.Success
		end
	end,
}

--
--	攻城战沙城	gczsc
--
gdMapExtension[MapID.sc] =
{
	onLoad = function(scene)
		scene:setProps(SP.prop_block_player, 1)
		_G.syncFloatMessage("请报名的行会速速前往沙城！")
		gcz_add_wall(scene)
		gcz_add_tower(scene)
		scene:addTimerEvent(1010, 600000, -1)
	end,
	onTimerEvent =
	{
		[1] = function(scene)--检查停留时间发放奖励
		end,
		[1010] = function(scene)	--十分钟一次经验
			scene:forEachEntityP(gcz_exp_sc)
		end,
	},
	onEntityEnter   = function(scene, entity)
		entity:setProps(EP.attr_pkmode, EP.pk_Guild)
		entity:syncProps(EP.attr_pkmode)
		if entity:isP() then
			gcz_mafa_buff(entity,1)
		end
	end,
	onEntityLeave	= function(scene, entity)
		if entity:isP() then
			gcz_mafa_buff(entity,0)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			gcz_monster_destroy(scene,entity)
		elseif entity:isP() then
			gcz_kill_count_update(scene, entity)
			gcz_mafa_buff(entity,0)
		end
	end,
	onSceneClose= function(scene)
	end,
	onTeleport = function(scene, entity, portal)
		local cmgid = _G.getWorldDataX(WP.city_master_guild)
		if entity:getProps(EP.attr_guild_id) == cmgid then
			gdScnMgr:enterScene(entity,portal.id,portal.tgtx,portal.tgty)
			return Error.Success
		else
			return Error.err_guild_NotCityMasterGuild
		end
	end,
}

--
--	普通沙皇宫	shg
--

gdMapExtension[MapID.shg] =
{
	onTeleport = function(scene, entity, portal)
		if Event.isActive(EID.gcz) then
			local lvl = entity:getLevel()
			if lvl >= 35 then
				gdScnMgr:enterScene(entity,MapID.sc,portal.tgtx,portal.tgty)
				return Error.Success
			end
		else
			gdScnMgr:enterScene(entity,portal.id,portal.tgtx,portal.tgty)
			return Error.Success
		end
	end,
}

--
--	攻城战沙皇宫	gczshg
--
gdMapExtension[MapID.gczshg] =
{
	onLoad = function(scene)
		scene:setProps(SP.prop_block_player, 1)
		scene:addTimerEvent(1, 600000)
		scene:addTimerEvent(1001, 60000, -1)
		scene:addTimerEvent(1010, 600000, -1)
	end,
	
	onTimerEvent =
	{
		[1] = function(scene)  -- 开始检测占领行会
			_G.syncFloatMessage("开始检测占领行会")
			scene:addTimerEvent(2, 5000, -1)
		end,
		
		[2] = function(scene)	-- 定期检查占领行会
			local ownerguild = nil
			local ownerguildid = 0
			local cnt_ownerguild = 0
			local cnt_allguild = 0
			
			local weekday = tonumber(os.date("%w", os.time()))

			scene:forEachEntityP(function(entity)
				-- 玩家必须是活的
				if not entity:isAlive() then
					return
				end
				
				-- 统计沙皇宫里每个玩家的公会信息,只有将公会里所有其它公会的人都清出去才算占领沙皇宫
				if cnt_ownerguild==cnt_allguild then
					local guild = entity:getGuild()
					
					-- 检查公会有没有攻城战申请
					local CheckGCZApply = true
					if weekday ~= 4 and guild and guild:getProps(GuildProp.guild_apply_gcz) == 0 then
						CheckGCZApply = false
					end
					
					if guild and CheckGCZApply then
						if ownerguildid==0 then
							ownerguild = guild
							ownerguildid = guild:getID()
						elseif ownerguildid~=guild:getID() then
							cnt_allguild = cnt_allguild + 1
							return
						end
						cnt_ownerguild = cnt_ownerguild+1
					else
						return
					end
				end
				
				-- 
				cnt_allguild = cnt_allguild + 1
			end)

			log.info("######:", cnt_ownerguild,"/", cnt_allguild)

			if cnt_ownerguild==cnt_allguild and ownerguild then
				local oldguildid = _G.getWorldDataX(WP.city_master_guild)
				if oldguildid ~= ownerguild:getID() then
					if oldguildid ~= 0 then
						local oldguild = _G.getGuild(oldguildid)
						if oldguild then
							_G.syncFloatMessage("占领行会"..oldguild:getGuildName().."被赶出了沙皇宫")
						end
					end
					_G.setWorldDataX(WP.city_master_guild, ownerguild:getID())
					_G.setWorldDataX(WP.cross_server_guild, ownerguild:getID())
					_G.syncFloatMessage(ownerguild:getGuildName().."行会临时占领了沙皇宫")

					--
					--	守城方更新
					--
					scene:forEachEntityM(function(entity)
						entity:setProps(EP.attr_guild_id, ownerguildid)
					end)
				end
			end
		end,
		
		[1010] = function(scene)	--十分钟一次经验
			scene:forEachEntityP(gcz_exp_shg_big)
		end,
		
		[1001] = function(scene)	--一分钟一次经验
			scene:forEachEntityP(gcz_exp_shg_small)
			scene:forEachEntityP(gcz_insist_time_update)
		end,
	},
	
	onEntityEnter   = function(scene, entity)
		entity:setProps(EP.attr_pkmode, EP.pk_Guild)
		entity:syncProps(EP.attr_pkmode)

		entity:setProps(EP.gcz_insist_time, 0)
	end,
	
	onEntityLeave	= function(scene, entity)
	end,
	
	onEntityDie = function(scene, entity)
		if entity:isP() then
			gcz_kill_count_update(scene, entity)
		end
	end,
	
	onSceneClose= function(scene)
		local nowgid = _G.getWorldDataX(WP.city_master_guild)
		local lastgid = _G.getWorldDataY(WP.city_master_guild)
		local curcnt = _G.getWorldDataZ(WP.city_master_guild)
		log.info("攻城战结果！ now，cur",nowgid,lastgid)
		local guild = _G.getGuild(nowgid)
		local guildname = nil
		if guild then

			guildname = guild:getGuildName()
			_G.setWorldDataStr(WP.city_master_guild,guildname)
			_G.syncFloatMessage(guildname.."行会获得了本次攻城战的胜利！")

			-- 如果是跨服战,则将最终战斗结果发回该公会原来的服务器
			if _G.isCrossServer() then
				local weekday = os.date("%w", os.time())
				if tonumber(weekday) == 4 then
					log.info("wxl ----> corss gcz on secene close, recordCrossGCZResult, wingid=" .. nowgid)
					_G.recordCrossGCZResult(nowgid)
					_G.syncFloatMessage("跨服战即将结束, 请大家主动退出跨服服务器, 回到自己原来的服务器领取跨服战奖励, 跨服服务器会在十分钟后关闭")
				end
			end
			
			-- 如果不是跨服战且是周三,则记录周四要参加跨服战的公会ID
			if not _G.isCrossServer() then
				local weekday = os.date("%w", os.time())
				if tonumber(weekday) == 3 then
					_G.setWorldDataX(WP.cross_server_guild, nowgid)
					_G.saveWorldData(WP.cross_server_guild)
				end
			end
			
			
			if lastgid == nowgid then--卫冕成功
				curcnt=curcnt+1
			else
				curcnt=1
			end

			_G.setWorldDataX(WP.city_master_guild,nowgid)
			_G.setWorldDataX(WP.cross_server_guild,nowgid)
			_G.setWorldDataY(WP.city_master_guild,lastgid)
			_G.setWorldDataZ(WP.city_master_guild,curcnt)
			_G.syncWorldData(WP.city_master_guild)
			_G.saveWorldData(WP.city_master_guild)

			_G.updateHeadTitle(WP.city_master_guild)

			local gender,job = guild:getGuildMasterGenderJob()
			_G.setWorldDataX(WP.city_master_player, guild:getProps(GuildProp.guild_masterid))
			_G.setWorldDataY(WP.city_master_player, gender)
			_G.setWorldDataZ(WP.city_master_player, job)
			_G.setWorldDataS(WP.city_master_player, guild:getStringProps(GuildProp.guild_mastername))
			_G.syncWorldData(WP.city_master_player)
			_G.saveWorldData(WP.city_master_player)

			_G.updateHeadTitle(WP.city_master_player)

			_G.setWorldDataX(WP.prop_gcz_job_master,guild:getProps(GuildProp.guild_masterid))
			_G.setWorldDataY(WP.prop_gcz_job_master,0)
			_G.setWorldDataStr(WP.prop_gcz_job_master,guild:getStringProps(GuildProp.guild_mastername))
			_G.syncWorldData(WP.prop_gcz_job_master)
			_G.saveWorldData(WP.prop_gcz_job_master)

			if curcnt>=4 then--守住沙城四天
				if guildname then
					_G.syncFloatMessage(guildname.."行会连续"..curcnt.."天守住了沙城！")
				end

				local meetcondition = _G.getWorldDataX(WP.city_own4days_reward)
				local rewarded = _G.getWorldDataY(WP.city_own4days_reward)
				if meetcondition < 1 and rewarded < 1 then
					_G.setWorldDataX(WP.city_own4days_reward, 1)
					_G.setWorldDataY(WP.city_own4days_reward, 0)
					_G.setWorldDataZ(WP.city_own4days_reward, nowgid)
					_G.saveWorldData(WP.city_own4days_reward)
					_G.syncWorldData(WP.city_own4days_reward)
				end
			end

			-- 重置膜拜鄙视数量，膜拜悬赏记录，膜拜行会buff记录，膜拜行会的首领奖励是否被领取
			_G.resetWorldData(WP.mobai_bishi_count)
			_G.resetWorldData(WP.mobai_money_count)
			_G.resetWorldData(WP.mobai_guild_buff)
			_G.resetWorldData(WP.mobai_guild_master_reward)

			-- 重置沙城官职
			_G.resetWorldData(WP.prop_gcz_job_deputy)
			_G.resetWorldData(WP.prop_gcz_job_general)
			_G.resetWorldData(WP.prop_gcz_job_decree)
			_G.resetWorldData(WP.prop_gcz_job_manager)
			-- 重置元宝领取
			_G.resetWorldData(WP.city_master_get_gold)
			--
			--	重置是否领取过城主奖励
			guild:setProps(GP.daily_suite, 0)
			guild:saveProps(GP.daily_suite)

			guild:setProps(GP.daily_tax, 0)
			guild:saveProps(GP.daily_tax)
			
			-- 检查服务器是否有人之前成为过城主，没有则把第一个城主设置好 ,并发送奖励
			local firstcm = _G.getWorldDataX(WP.prop_world_first_city_master)
			if (firstcm == 0) then
				_G.setWorldDataX(WP.prop_world_first_city_master, guild:getProps(GuildProp.guild_masterid))
				_G.setWorldDataY(WP.prop_world_first_city_master, gender)
				_G.setWorldDataZ(WP.prop_world_first_city_master, job)
				_G.setWorldDataS(WP.prop_world_first_city_master, guild:getStringProps(GuildProp.guild_mastername))
				_G.saveWorldData(WP.prop_world_first_city_master)

				gNewServer.rewardBest(3)
			end

			_G.gczRecord(nowgid, lastgid, guildname, guild:getStringProps(GuildProp.guild_mastername))
		else
			_G.syncFloatMessage("最终没有行会占领沙皇宫，沙城被收回")
			_G.gczRecord(0, lastgid, "", "")
		end

		-- 沙城战结束时,胜利公会自动报名下周的沙城战(免费的哦),其它公会清除报名信息,要手动花钱报名
		_G.forEachGuild(function(mg)
				local applydata = mg:getProps(GuildProp.guild_apply_gcz)
				if mg:getID() == nowgid then
					if applydata == 0 then
						mg:setProps(GuildProp.guild_apply_gcz,1)
						mg:syncProps(GuildProp.guild_apply_gcz)
						mg:saveProps(GuildProp.guild_apply_gcz)
						_G.setGCZApply(nowgid)
					end
				else
					if applydata ~= 0 then
						mg:setProps(GuildProp.guild_apply_gcz,0)
						mg:syncProps(GuildProp.guild_apply_gcz)
						mg:saveProps(GuildProp.guild_apply_gcz)
					end
				end
			end)
	end,
}

gdMapExtension[MapID.wjdsy] = {
	onLoad = function(scene)
		local m = scene:addM(5504, 42, 26)--boss定点
		if m then
			scene:setProps(SP.xmfb_bossid, m:getID())
		end
		scene:addTimerEvent(1, 2000, -1)
		
		--log.info("###################### stage 1 ##########################")
	end,

	onTimerEvent =
	{
		[1] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=99 then
				scene:syncFloatMessage("无尽的深渊进入防御状态")
				--log.info("###################### stage 1 ##########################")
				scene:rmvTimerEvent(1)
				scene:addTimerEvent(2, 2000, -1)
			end
		end,
		[2] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=80 then
				scene:syncFloatMessage("开始召唤深渊boss*假")
				--log.info("###################### stage 2 ##########################")
				scene:rmvTimerEvent(2)
				scene:addTimerEvent(3, 2000, -1)
				scene:addTimerEvent(20, 3000, -1)
				--减去第一阶段的两防
				cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Min, -26 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max, -26 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Min, -26 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max, -26 * Combat.PercentToInt)
			end
		end,
		[3] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=70 then
				scene:syncFloatMessage("无尽的深渊进入攻击状态")
				--log.info("###################### stage 3 ##########################")
				scene:rmvTimerEvent(3)
				scene:rmvTimerEvent(20)
				scene:addTimerEvent(4, 2000, -1)
				--变身可移动可攻击的模式
				m:setProps(EP.attr_mode, EP.emm_Aggressive)
			end
		end,
		[4] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local cbt = m:getCombatSys()
			if not cbt then
				return
			end
			local percent = cbt:getProps(Combat.prop_HP) * 100 / cbt:getProps(Combat.prop_HPMax)
			if percent<=60 then
				scene:syncFloatMessage("无尽的深渊疯狂模式已开启!")
				--log.info("###################### stage 4 ##########################")
				scene:rmvTimerEvent(4)
				cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,400 * Combat.PercentToInt)
				cbt:addProps(Combat.prop_End + Combat.prop_PATK_Min,400 * Combat.PercentToInt)
				m:addEffect(Effect.effect_violent)
			end
		end,
		[20] = function(scene)
			local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
			if not m then
				return
			end
			local x, y = m:getPosition()
			scene:addM(5505, x + 3, y)
			scene:addM(5506, x - 3, y)
			scene:addM(5507, x - 2, y - 2)
			scene:addM(5508, x - 2, y + 2)
			scene:addM(5509, x + 2, y - 2)
			scene:addM(5509, x + 2, y + 2)
			scene:addM(5507, x - 5, y - 2)--
			scene:addM(5508, x - 5, y + 2)
			scene:addM(5509, x + 6, y - 2)
			scene:addM(5509, x + 6, y + 2)
			scene:resetTimerEvent(20, 30000, -1)
			
		end,
	},
	onEntityEnter   = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==1087 or sid==1088 or sid==1089 then
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 100)
			else
				entity:setProps(EP.attr_pkmode, EP.pk_Faction)
				entity:setProps(EP.attr_faction_id, 101)
			end
		elseif entity:isP() then
			entity:setProps(EP.attr_pkmode, EP.pk_Faction)
			entity:setProps(EP.attr_faction_id, 100)
			entity:syncProps(EP.attr_pkmode)
			entity:syncProps(EP.attr_faction_id)
			entity:addGene(50900)
		end
	end,
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			if sid==5505 then
				local m = scene:getEntity(scene:getProps(SP.xmfb_bossid))
				if not m then
					return
				end
				local cbt = m:getCombatSys()
				if not cbt then
					return
				end
				cbt:updateHP(-90000)
			elseif sid==5504 then
				--有几率出深渊boss
				if math.random(1, 100)<=100 then
					scene:syncFloatMessage("无尽的深渊BOSS, 来临")
					scene:addM(5505, entity:getPositionX(), entity:getPositionY())
					scene:addM(5506, entity:getPositionX(), entity:getPositionY())
					scene:addM(5507, entity:getPositionX(), entity:getPositionY())
					scene:addM(5508, entity:getPositionX(), entity:getPositionY())
					scene:addM(5509, entity:getPositionX(), entity:getPositionY())
					scene:addM(5510, entity:getPositionX(), entity:getPositionY())--深渊boss
				end
			end
		end
		if entity:isM() and entity:getStaticID()==1088 then
			scene:addProps(SP.xmfb_already_summon_liemo, -1)
		end
		if entity:isM() and entity:getStaticID()==1089 then
			scene:addProps(SP.xmfb_already_summon_liemohead, -1)
		end
	end
}
-- -- PK场地图211 - 最简单稳定版
gdMapExtension[MapID.pkc] = {
    
    onLoad = function(scene)
        scene:setProps(SP.pkc_team_a, 0)
        scene:setProps(SP.pkc_team_b, 0)
        
        -- 地图边界阻挡
        for x = 0, 63 do
            scene:addBlock(x, 0, 0x8000)
            scene:addBlock(x, 61, 0x8000)
        end
        for y = 0, 61 do
            scene:addBlock(0, y, 0x8000)
            scene:addBlock(63, y, 0x8000)
        end
    end,
    
    onEntityEnter = function(scene, entity)
        if entity:isP() then
            local cnta = scene:getProps(SP.pkc_team_a) or 0
            local cntb = scene:getProps(SP.pkc_team_b) or 0
            
            if cnta + cntb >= 2 then
                entity:syncFloatMessage("PK场已满")
                scene:leaveScene(entity)
                return
            end
            
            -- 清除标记
            entity:setProps(EP.custom_pkc_dead, 0)
            entity:setProps(EP.custom_pkc_winner, 0)
            
            if cnta == 0 then
                scene:setProps(SP.pkc_team_a, 1)
                entity:setProps(EP.attr_faction_id, 1)
                entity:setProps(EP.attr_pkmode, EP.pk_Peace)
                scene:flyEntity(entity, 13, 29)
				_G.syncFloatMessage("有人发起PK欢迎来战")
                entity:syncFloatMessage("等待对手...")
				
            else
                scene:setProps(SP.pkc_team_b, 1)
                entity:setProps(EP.attr_faction_id, 2)
                entity:setProps(EP.attr_pkmode, EP.pk_Faction)
                scene:flyEntity(entity, 45, 25)
                entity:syncFloatMessage("战斗开始！")
                
                scene:forEachEntityP(function(p)
                    if p:getProps(EP.attr_faction_id) == 1 then
                        p:setProps(EP.attr_pkmode, EP.pk_Faction)
                        p:syncFloatMessage("战斗开始！")
                    end
                end)
            end
        end
    end,
    
    onEntityLeave = function(scene, entity)
        if entity:isP() then
            local fid = entity:getProps(EP.attr_faction_id) or 0
            local is_dead = entity:getProps(EP.custom_pkc_dead) or 0
            local is_winner = entity:getProps(EP.custom_pkc_winner) or 0
            
            -- 只有活着离开且不是胜利者才算逃跑
            if fid > 0 and is_dead == 0 and is_winner == 0 then
                scene:forEachEntityP(function(p)
                    local pfid = p:getProps(EP.attr_faction_id) or 0
                    if pfid > 0 and pfid ~= fid then
                        p:addCoupon(2000)
                        p:syncFloatMessage("对方逃跑，你获得2000仙玉")
                        scene:addTimerEvent(1, 5000)
                    end
                end)
            end
        end
    end,
    
    onEntityDie = function(scene, entity)
        if entity:isP() then
            local killer = entity:getCombatKiller()
            
            -- 标记为死亡
            entity:setProps(EP.custom_pkc_dead, 1)
            
            if killer and killer:isP() then
                -- 标记为胜利者
                killer:setProps(EP.custom_pkc_winner, 1)
                killer:addCoupon(2000)
                killer:syncFloatMessage("胜利！获得2000仙玉")
                scene:addTimerEvent(1, 5000)
            end
            
            -- 死亡者离开
            entity:setState(EP.gst_Dead)
            scene:leaveScene(entity)
            scene:addTimerEvent(2, 1000, entity:getID())
        end
    end,
    
    onTimerEvent = {
        [1] = function(scene)
            scene:forEachEntityP(function(player)
                Scene.conveyentitytoscene(player, 0)
                local cbt = player:getCombatSys()
                if cbt then
                    cbt:updateHP(cbt:getMaxHP(), 0)
                    cbt:updateMP(cbt:getMaxMP())
                end
                player:syncFloatMessage("PK结束")
            end)
            scene:close()
        end,
        
        [2] = function(scene, player_id)
            local entity = gdEntityMgr:getEntity(player_id)
            if entity and entity:isP() then
                Scene.conveyentitytoscene(entity, 0)
                local cbt = entity:getCombatSys()
                if cbt then
                    cbt:updateHP(cbt:getMaxHP(), 0)
                    cbt:updateMP(cbt:getMaxMP())
                end
                entity:setState(EP.gst_Idle)
                entity:syncFloatMessage("你被击败")
            end
        end
    }
}





-- 副本四季轮回镜地图 
gdMapExtension[MapID.sjlhj] = {
	onLoad = function(scene)
		-- 生成四个季节BOSS
		local boss1 = scene:addM(5390, 11, 46)  -- 春
		local boss2 = scene:addM(5391, 10, 15)  -- 夏  
		local boss3 = scene:addM(5392, 48, 15)  -- 秋
		local boss4 = scene:addM(5393, 48, 46)  -- 冬
		
		-- 记录BOSS ID
		if boss1 then
			scene:setProps(SP.sj_boss1, boss1:getID())
		end
		if boss2 then
			scene:setProps(SP.sj_boss2, boss2:getID())
		end
		if boss3 then
			scene:setProps(SP.sj_boss3, boss3:getID())
		end
		if boss4 then
			scene:setProps(SP.sj_boss4, boss4:getID())
		end
		
		-- 记录存活BOSS数
		scene:setProps(SP.sj_alive, 4)
		
		scene:syncFloatMessage("四季轮回镜开启！击败四个季节守护者")
	end,
	
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			
			-- 检查是哪个季节BOSS
			if sid == 5390 then
				scene:syncFloatMessage("春之灵已被击败")
				scene:setProps(SP.sj_boss1, 0)
			elseif sid == 5391 then
				scene:syncFloatMessage("夏之炎已被击败")  
				scene:setProps(SP.sj_boss2, 0)
			elseif sid == 5392 then
				scene:syncFloatMessage("秋之叶已被击败")
				scene:setProps(SP.sj_boss3, 0)
			elseif sid == 5393 then
				scene:syncFloatMessage("冬之雪已被击败")
				scene:setProps(SP.sj_boss4, 0)
			end
			
			-- 如果是四季BOSS之一
			if sid >= 5390 and sid <= 5393 then
				local alive = (scene:getProps(SP.sj_alive) or 4) - 1
				scene:setProps(SP.sj_alive, alive)
				
				if alive > 0 then
					scene:syncFloatMessage("剩余BOOS："..alive.."/4")
				else
					-- 全部击败，通关
					scene:syncFloatMessage("★★★ 通关四季轮回镜！ ★★★")
					
					-- 发奖励
					scene:forEachEntityP(function(player)
						-- 发物品
						player:addItem(51000, 1)
						player:syncFloatMessage("获得四季盒子x1")
						
						-- 发经验
						player:addExp(50000000)
						
						-- 可以在这里添加更多奖励
					end)
					
					-- 5秒后关闭地图
					scene:setTimeToLive(5)
				end
			end
		end
	end,
	
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			-- 传送玩家到地图中心
			scene:flyEntity(entity, 30, 33)
			
			-- 设置PK模式为和平
			entity:setProps(EP.attr_pkmode, EP.pk_Peace)
			entity:syncProps(EP.attr_pkmode)
		end
	end
}

---------------------------------------------------------------------------------------



-- 五行试炼阵 - 完整版（含随机奖励）
gdMapExtension[MapID.wxslz] = {
	onLoad = function(scene)
		-- 生成五个BOSS
		local boss1 = scene:addM(5394, 10, 14)  -- 金
		local boss2 = scene:addM(5395, 50, 40)  -- 木
		local boss3 = scene:addM(5396, 29, 33)  -- 水
		local boss4 = scene:addM(5397, 50, 20)  -- 火
		local boss5 = scene:addM(5398, 10, 50)  -- 土
		
		-- 记录BOSS ID
		if boss1 then scene:setProps(SP.wx_boss1, boss1:getID()) end
		if boss2 then scene:setProps(SP.wx_boss2, boss2:getID()) end
		if boss3 then scene:setProps(SP.wx_boss3, boss3:getID()) end
		if boss4 then scene:setProps(SP.wx_boss4, boss4:getID()) end
		if boss5 then scene:setProps(SP.wx_boss5, boss5:getID()) end
		
		-- 初始化状态
		scene:setProps(SP.wx_alive, 5)  -- 存活BOSS数
		scene:setProps(SP.wx_step, 1)   -- 当前步骤
		
		-- 初始化随机种子
		math.randomseed(os.time())
		
		--scene:syncFloatMessage("五行试炼阵开启")
		--scene:syncFloatMessage("击杀顺序：金→水→木→火→土")
	end,
	
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			
			-- 检查是哪个BOSS
			local isWuxing = false
			local bossIndex = 0
			local elementName = ""
			
			if sid == 5394 then
				scene:setProps(SP.wx_boss1, 0)
				isWuxing = true
				bossIndex = 1
				elementName = "金"
			elseif sid == 5395 then
				scene:setProps(SP.wx_boss2, 0)
				isWuxing = true
				bossIndex = 2
				elementName = "木"
			elseif sid == 5396 then
				scene:setProps(SP.wx_boss3, 0)
				isWuxing = true
				bossIndex = 3
				elementName = "水"
			elseif sid == 5397 then
				scene:setProps(SP.wx_boss4, 0)
				isWuxing = true
				bossIndex = 4
				elementName = "火"
			elseif sid == 5398 then
				scene:setProps(SP.wx_boss5, 0)
				isWuxing = true
				bossIndex = 5
				elementName = "土"
			end
			
			if not isWuxing then return end
			
			-- 获取当前状态
			local currentStep = scene:getProps(SP.wx_step) or 1
			local alive = scene:getProps(SP.wx_alive) or 5
			
			-- 五行相生顺序：金(5394)→水(5396)→木(5395)→火(5397)→土(5398)
			local correctOrder = {5394, 5396, 5395, 5397, 5398}
			local shouldKill = correctOrder[currentStep] or 0
			
			-- 应该杀的元素名
			local shouldName = ""
			if shouldKill == 5394 then shouldName = "金"
			elseif shouldKill == 5395 then shouldName = "木"
			elseif shouldKill == 5396 then shouldName = "水"
			elseif shouldKill == 5397 then shouldName = "火"
			elseif shouldKill == 5398 then shouldName = "土" end
			
			--scene:syncFloatMessage("击杀：" .. elementName)
			--scene:syncFloatMessage("应杀：" .. shouldName)
			
			if sid == shouldKill then
				-- 正确击杀
				scene:setProps(SP.wx_step, currentStep + 1)
				scene:setProps(SP.wx_alive, alive - 1)
				
				--scene:syncFloatMessage("√ 顺序正确")
				
				-- 检查是否通关
				local newAlive = alive - 1
				if newAlive <= 0 then
					scene:syncFloatMessage("★★★ 正确通关五行试炼阵 ★★★")
					
					-- 发放随机奖励
					scene:forEachEntityP(function(player)
						-- 基础奖励
						player:addItem(51001, 1)
						player:addExp(100000000000)
						
						-- 随机额外奖励（50%几率）
						if math.random(1, 100) <= 50 then
							local rewardType = math.random(1, 3)
							
							if rewardType == 1 then
								-- 额外宝箱
								player:addItem(51001, 1)
								player:syncFloatMessage("幸运！额外获得五行盒子×1")
								
							elseif rewardType == 2 then
								-- 大量仙玉
								local coupon = math.random(10000, 20000)
								player:addCoupon(coupon)
								
								player:syncFloatMessage("幸运！获得额外仙玉+" .. coupon)
								
							elseif rewardType == 3 then
								-- 元宝
								local gold = math.random(1000000, 3000000)
								player:addGold(gold)
								player:syncFloatMessage("幸运！获得元宝+" .. gold)
							end
						end
						
						player:syncFloatMessage("获得：五行盒子×1 + 经验1000亿")
					end)
					
					-- 5秒后关闭地图
					scene:setTimeToLive(5)
				end
			else
				-- 错误击杀
			--	scene:syncFloatMessage("× 顺序错误")
				
				-- 检查是否所有BOSS都死了
				local allDead = true
				for i = 1, 5 do
					local bossId = scene:getProps(SP["wx_boss" .. i]) or 0
					if bossId > 0 then
						allDead = false
						break
					end
				end
				
				-- 如果所有BOSS都死了，提示错误通关
				if allDead then
				
					scene:syncFloatMessage("挑战失败")
					scene:setTimeToLive(5)
				else
					-- 3秒后复活BOSS
					scene:addTimerEvent(1, 3000, 1, function()
						local x, y = entity:getX(), entity:getY()
						local newBoss = scene:addM(sid, x, y)
						if newBoss then
							-- 重新记录BOSS ID
							if bossIndex == 1 then scene:setProps(SP.wx_boss1, newBoss:getID()) end
							if bossIndex == 2 then scene:setProps(SP.wx_boss2, newBoss:getID()) end
							if bossIndex == 3 then scene:setProps(SP.wx_boss3, newBoss:getID()) end
							if bossIndex == 4 then scene:setProps(SP.wx_boss4, newBoss:getID()) end
							if bossIndex == 5 then scene:setProps(SP.wx_boss5, newBoss:getID()) end
							scene:syncFloatMessage(elementName .. "之守护已复活")
						end
					end)
				end
				
				-- 错误击杀不减存活数，直接返回
				return
			end
		end
	end,
	
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			-- 传送玩家到中心
			scene:flyEntity(entity, 29, 33)
			
			-- 设置和平模式
			entity:setProps(EP.attr_pkmode, EP.pk_Peace)
		end
	end
}


-- 渡劫副本地图 
gdMapExtension[MapID.djfb] = {
	onLoad = function(scene)
		-- 生成四个季节BOSS
		local boss1 = scene:addM(5610, 24, 25)  
		local boss2 = scene:addM(5611, 24, 25)    
		local boss3 = scene:addM(5612, 24, 25)  
		local boss4 = scene:addM(5613, 24, 25)  
		
		-- 记录BOSS ID
		if boss1 then
			scene:setProps(SP.djfb_boss1, boss1:getID())
		end
		if boss2 then
			scene:setProps(SP.djfb_boss2, boss2:getID())
		end
		if boss3 then
			scene:setProps(SP.djfb_boss3, boss3:getID())
		end
		if boss4 then
			scene:setProps(SP.djfb_boss4, boss4:getID())
		end
		
		-- 记录存活BOSS数
		scene:setProps(SP.djfb_alive, 4)
		
		-- 修改为带玩家名的广播
		scene:forEachEntityP(function(player)
			_G.syncFloatMessage(tostring(player:getName()) .. "渡劫开启！击败四个渡劫天罚！")
		end)
	end,
	
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			
			if sid == 5610 then
				scene:syncFloatMessage("渡劫天罚已被击败")
				scene:setProps(SP.djfb_boss1, 0)
			elseif sid == 5611 then
				scene:syncFloatMessage("渡劫天罚已被击败")  
				scene:setProps(SP.djfb_boss2, 0)
			elseif sid == 5612 then
				scene:syncFloatMessage("渡劫天罚已被击败")
				scene:setProps(SP.djfb_boss3, 0)
			elseif sid == 5613 then
				scene:syncFloatMessage("渡劫天罚已被击败")
				scene:setProps(SP.djfb_boss4, 0)
			end
			
			-- 如果是四季BOSS之一
			if sid >= 5610 and sid <= 5613 then
				local alive = (scene:getProps(SP.djfb_alive) or 4) - 1
				scene:setProps(SP.djfb_alive, alive)
				
				if alive > 0 then
					scene:syncFloatMessage("剩余BOOS："..alive.."/4")
				else
					-- 全部击败，通关
					-- 修改为带玩家名的广播
					scene:forEachEntityP(function(player)
						_G.syncFloatMessage(tostring(player:getName()) .. "完成渡劫！")
					end)
					
					-- 发奖励
					scene:forEachEntityP(function(player)
						-- 发物品
						player:addItem(5557, 1)
						player:syncFloatMessage("获得渡劫丹")
					end)
					
					-- 5秒后关闭地图
					scene:setTimeToLive(5)
				end
			end
		end
	end,
	
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			-- 传送玩家到地图中心
			scene:flyEntity(entity, 24, 25)
			
			-- 设置PK模式为和平
			entity:setProps(EP.attr_pkmode, EP.pk_Peace)
			entity:syncProps(EP.attr_pkmode)
		end
	end
}

-- 副本情侣望月岛地图 
gdMapExtension[MapID.qlwyd] = {
	onLoad = function(scene)
		-- 生成四个季节BOSS
		local boss1 = scene:addM(5403, 23, 28)  
		local boss2 = scene:addM(5404, 23, 28)    
		local boss3 = scene:addM(5405, 23, 28)  
		local boss4 = scene:addM(5406, 23, 28)  
		
		-- 记录BOSS ID
		if boss1 then
			scene:setProps(SP.ql_boss1, boss1:getID())
		end
		if boss2 then
			scene:setProps(SP.ql_boss2, boss2:getID())
		end
		if boss3 then
			scene:setProps(SP.ql_boss3, boss3:getID())
		end
		if boss4 then
			scene:setProps(SP.ql_boss4, boss4:getID())
		end
		
		-- 记录存活BOSS数
		scene:setProps(SP.ql_alive, 4)
		
		scene:syncFloatMessage("情侣望月岛开启！")
	end,
	
	onEntityDie = function(scene, entity)
		if entity:isM() then
			local sid = entity:getStaticID()
			
			-- 检查是哪个BOSS
			if sid == 5403 then
				scene:setProps(SP.ql_boss1, 0)
			elseif sid == 5404 then 
				scene:setProps(SP.ql_boss2, 0)
			elseif sid == 5405 then
				scene:setProps(SP.ql_boss3, 0)
			elseif sid == 5406 then
				scene:setProps(SP.ql_boss4, 0)
			end
			
			-- 如果是四季BOSS之一
			if sid >= 5403 and sid <= 5406 then
				local alive = (scene:getProps(SP.ql_alive) or 4) - 1
				scene:setProps(SP.ql_alive, alive)
				
				if alive > 0 then
					scene:syncFloatMessage("剩余BOOS："..alive.."/4")
				else
					-- 全部击败，通关
					scene:syncFloatMessage("★★★ 通关情侣望月岛！ ★★★")
					
					-- 发奖励
					scene:forEachEntityP(function(player)
						-- 发物品
						player:addItem(41001, 30)
						player:syncFloatMessage("获得通关奖励")
						
						-- 发经验
						player:addExp(800000000)
						
						-- 可以在这里添加更多奖励
					end)
					
					-- 5秒后关闭地图
					scene:setTimeToLive(5)
				end
			end
		end
	end,
	
	onEntityEnter = function(scene, entity)
		if entity:isP() then
			-- 传送玩家到地图中心
			scene:flyEntity(entity, 23, 28)
			
			-- 设置PK模式为和平
			entity:setProps(EP.attr_pkmode, EP.pk_Peace)
			entity:syncProps(EP.attr_pkmode)
		end
	end
}







-- 协作站位挑战地图
-- 地图ID: byh (303)
-- 功能：进入即开始，1个位置有人就刷BOSS，40秒换位置，无人无奖励

-- 站位点配置
local STAND_POSITIONS = {
    {x = 21, y = 10, id = 1, markerId = 0},  -- 位置1
    {x = 14, y = 22, id = 2, markerId = 0},  -- 位置2
    {x = 17, y = 24, id = 3, markerId = 0},  -- 位置3
    {x = 20, y = 24, id = 4, markerId = 0},  -- 位置4
    {x = 27, y = 29, id = 5, markerId = 0},  -- 位置5
    {x = 19, y = 32, id = 6, markerId = 0},  -- 位置6
    {x = 18, y = 46, id = 7, markerId = 0},  -- 位置7
    {x = 7, y = 21, id = 8, markerId = 0}    -- 位置8
}

-- 奖励配置（概率分布，从大到小）
-- type: coupon=仙玉, item=物品
local REWARDS = {
    {min = 1, max = 25, type = "item", itemId = 41112, count = 10, desc = "橙钻石x10"},   -- 25%
    {min = 26, max = 40, type = "item", itemId = 40004, count = 10, desc = "5级灵石x8"},  -- 15%
    {min = 41, max = 52, type = "item", itemId = 30059, count = 5, desc = "金蚕王"},                 -- 12%
    {min = 53, max = 63, type = "coupon", amount = 1680, desc = "1680仙玉"},                -- 11%
    {min = 64, max = 73, type = "item", itemId = 41001, count = 5, desc = "中级灵石"},       -- 10%
    {min = 74, max = 82, type = "item", itemId = 30092, count = 5, desc = "灵爵"},                 -- 9%
    {min = 83, max = 89, type = "item", itemId = 41003, count = 8, desc = "装备残魂"},      -- 7%
    {min = 90, max = 94, type = "item", itemId = 30092, count = 8, desc = "灵爵"},          -- 5%
    {min = 95, max = 97, type = "item", itemId = 30059, count = 8, desc = "金蚕王"},         -- 3%
    {min = 98, max = 99, type = "item", itemId = 5555, count = 3, desc = "突破蛋"},          -- 2%
    {min = 100, max = 100, type = "item", itemId = 41004, count = 2, desc = "暗影玫瑰"}      -- 1%
}

-- 获取随机奖励（按概率）
local function getRandomReward()
    local n = math.random(100)
    for _, reward in ipairs(REWARDS) do
        if n >= reward.min and n <= reward.max then
            return reward
        end
    end
    return REWARDS[1]
end

-- 获取多个随机奖励
local function getMultipleRewards(count)
    local rewards = {}
    for i = 1, count do
        table.insert(rewards, getRandomReward())
    end
    return rewards
end

-- 获取玩家坐标
local function getPlayerPosition(player)
    if not player or not player:isP() then
        return 0, 0
    end
    
    local x, y = 0, 0
    
    if player.getPosition then
        x = player:getPosition() or 0
    end
    
    if player.getPositionY then
        y = player:getPositionY() or 0
    end
    
    return x, y
end

-- 刷新位置标记
local function refreshPositionMarkers(scene, currentPos)
    for i, pos in ipairs(STAND_POSITIONS) do
        -- 删除旧的标记
        if pos.markerId and pos.markerId ~= 0 then
            local oldMarker = scene:getEntity(pos.markerId)
            if oldMarker then
                scene:rmvEntity(pos.markerId)
            end
            pos.markerId = 0
        end
        
        -- 如果是当前需要站位的位置，添加新标记
        if i == currentPos then
            local marker = scene:addS(100, pos.x, pos.y)
            if marker then
                pos.markerId = marker:getID()
                -- 设置标记持续时间
                marker:setProps(EntityProp.attr_time_to_live, 40)
            end
        end
    end
end

-- 刷新BOSS
local function refreshBoss(scene)
    local oldBossId = scene:getProps(SP.coop_boss) or 0
    if oldBossId > 0 then
        local oldBoss = scene:getEntity(oldBossId)
        if oldBoss then
            scene:removeEntity(oldBoss)
        end
    end
    
    local boss = scene:addM(5615, 45, 27)  -- BOSS ID
    if boss then
        scene:setProps(SP.coop_boss, boss:getID())
        scene:setProps(SP.coop_boss_active, 1)
       -- scene:syncFloatMessage("★★★ BOSS已刷新！站在位置并击败可获得奖励 ★★★")
    end
    
    return boss
end

-- 检查是否有人站在指定位置
local function checkPosition(scene)
    local needPos = scene:getProps(SP.coop_need_pos) or 0
    
    if needPos > 0 then
        local targetPos = STAND_POSITIONS[needPos]
        if not targetPos then
            return
        end
        
        local targetX = targetPos.x
        local targetY = targetPos.y
        
        local someoneOnPos = false
        
        scene:forEachEntityP(function(player)
            if player and player:isP() then
                local x, y = getPlayerPosition(player)
                
                if x == targetX and y == targetY then
                    someoneOnPos = true
                end
            end
        end)
        
        if someoneOnPos then
            local bossId = scene:getProps(SP.coop_boss) or 0
            if bossId == 0 then
                refreshBoss(scene)
            end
        end
    end
end

-- 更换下一个位置
local function changePosition(scene)
    -- 如果当前有BOSS没被打死，移除BOSS且无奖励
    local oldBossId = scene:getProps(SP.coop_boss) or 0
    if oldBossId > 0 then
        local oldBoss = scene:getEntity(oldBossId)
        if oldBoss then
            scene:rmvEntity(oldBossId)
          --  scene:syncFloatMessage("★★ BOSS超时未击败，本轮无奖励 ★★")
        end
        scene:setProps(SP.coop_boss, 0)
        scene:setProps(SP.coop_boss_active, 0)
    end
    
    local totalPositions = #STAND_POSITIONS
    local newPos = math.random(1, totalPositions)
    
    scene:setProps(SP.coop_need_pos, newPos)

    scene:syncFloatMessage("★★ 新位置已刷新：位置" .. newPos .. " ★★")
    
    scene:setProps(SP.coop_timer, os.time() + 40)
    
    -- 刷新位置标记
    refreshPositionMarkers(scene, newPos)
    
    checkPosition(scene)
end

-- 启动检查循环
local function startCheckLoop(scene)
    local now = os.time()
    
    local timerEnd = scene:getProps(SP.coop_timer) or 0
    if timerEnd > 0 and now >= timerEnd then
        changePosition(scene)
    end
    
    checkPosition(scene)
    
    -- 定时刷新玩家的 buff（每5秒刷新一次，确保在地图内持续拥有）
    scene:forEachEntityP(function(player)
        if player and player:isP() then
            player:addGene(20007)
        end
    end)
    
    scene:addTimerEvent(1, 1000, 1, function()
        startCheckLoop(scene)
    end)
end

-- 主地图扩展
gdMapExtension[MapID.byh] = {
    
    onLoad = function(scene)
        -- 检查地图是否已经加载过
        local mapLoaded = scene:getProps(SP.coop_map_loaded) or 0
        if mapLoaded == 1 then
            return
        end
        
        -- 标记地图已加载
        scene:setProps(SP.coop_map_loaded, 1)
        
        -- 初始化状态
        scene:setProps(SP.coop_need_pos, 0)
        scene:setProps(SP.coop_timer, 0)
        scene:setProps(SP.coop_player_count, 0)
        scene:setProps(SP.coop_boss, 0)
        scene:setProps(SP.coop_boss_active, 0)
        scene:setProps(SP.coop_check_counter, 0)
        scene:setProps(SP.coop_challenge_started, 0)
        
        local playerCount = 0
        scene:forEachEntityP(function(player)
            if player and player:isP() then
                playerCount = playerCount + 1
            end
        end)
        scene:setProps(SP.coop_player_count, playerCount)
        
        scene:syncFloatMessage("协作站位挑战区域")
        scene:syncFloatMessage("进入地图自动开始挑战")
        scene:syncFloatMessage("规则：站在指定位置会刷新BOSS，40秒换位置")
        scene:syncFloatMessage("无人站在位置，击败BOSS无奖励")
        scene:syncFloatMessage("站位点：位置1 位置2 位置3 位置4 位置5 位置6 位置7 位置8")
        scene:syncFloatMessage("BOSS刷新在中央")
        scene:syncFloatMessage("死亡后返回主城")

        -- 设置地图为强制回城复活模式，禁止原地复活
        scene:setProps(SP.prop_relive_type, 1)
        
        scene:addTimerEvent(1, 1000, 1, function()
            startCheckLoop(scene)
        end)
        
        if playerCount > 0 then
            changePosition(scene)
        end
    end,
    
    onEntityEnter = function(scene, entity)
        if entity:isP() then
            entity:setProps(EP.attr_pkmode, EP.pk_Peace)
            
            local count = (scene:getProps(SP.coop_player_count) or 0) + 1
            scene:setProps(SP.coop_player_count, count)
            
            local needPos = scene:getProps(SP.coop_need_pos) or 0
            
            -- 如果没有站位位置，开始挑战
            if needPos == 0 then
                scene:setProps(SP.coop_challenge_started, 1)
                changePosition(scene)
            else
                -- 有站位位置时，刷新位置标记
                refreshPositionMarkers(scene, needPos)
            end
            
            entity:setProps(EP.custom_hit_boss, 0)
            
            -- 进入地图获得 buff（gene_id: 20007）
            entity:addGene(20007)
        end
    end,
    
    onEntityLeave = function(scene, entity)
        if entity:isP() then
            local count = (scene:getProps(SP.coop_player_count) or 0) - 1
            if count < 0 then count = 0 end
            scene:setProps(SP.coop_player_count, count)
            
            -- 退出地图移除 buff（gene_id: 20007）
            entity:rmvGene(20007)
        end
    end,
    
    onEntityDie = function(scene, entity)
        if entity:isP() then
            -- 立即减少玩家计数
            local count = (scene:getProps(SP.coop_player_count) or 0) - 1
            if count < 0 then count = 0 end
            scene:setProps(SP.coop_player_count, count)
            
            -- 立即回城复活，不能停留在此地图
            Scene.conveyentitytoNPC(entity, 5200)
        elseif entity:isM() then
            local bossId = scene:getProps(SP.coop_boss) or 0
            if entity:getID() == bossId then
                local needPos = scene:getProps(SP.coop_need_pos) or 0
                local positionManned = false
                local targetPos = STAND_POSITIONS[needPos]
                
                scene:forEachEntityP(function(player)
                    if player and player:isP() and targetPos then
                        local x, y = getPlayerPosition(player)
                        if x == targetPos.x and y == targetPos.y then
                            positionManned = true
                        end
                    end
                end)
                
                -- 获取击杀BOSS的玩家
                local killer = entity:getCombatKiller()
                if killer and killer:isP() then
                    -- 击杀BOSS增加50PK值
                    local pkValue = (killer:getProps(EP.attr_pkvalue) or 0) + 50
                    killer:setProps(EP.attr_pkvalue, pkValue)
                    killer:syncProps(EP.attr_pkvalue)
                end
                
                if positionManned then
                    scene:forEachEntityP(function(player)
                        if player and player:isP() and targetPos then
                            local x, y = getPlayerPosition(player)
                            if x == targetPos.x and y == targetPos.y then
                                local rewards = getMultipleRewards(3)
                                for _, reward in ipairs(rewards) do
                                    if reward.type == "coupon" then
                                        player:addCoupon(reward.amount)
                                    elseif reward.type == "item" then
                                        player:addItem(reward.itemId, reward.count, Opcode.op_summer)
                                    end
                                end
                            end
                        end
                    end)
                   -- scene:syncFloatMessage("★★ BOSS已击败，获得奖励！ ★★")
                end
                
                scene:setProps(SP.coop_boss, 0)
                scene:setProps(SP.coop_boss_active, 0)
                
                -- BOSS死亡后立即更换位置，开始下一轮
                changePosition(scene)
            end
        end
    end,
    
    onAttack = function(scene, attacker, target)
        if attacker:isP() and target:isM() then
            local bossId = scene:getProps(SP.coop_boss) or 0
            local targetId = target:getID()
            
            if targetId == bossId then
                attacker:setProps(EP.custom_hit_boss, 1)
            end
        end
        return true
    end,
    
    onSafeRevive = function(entity, scene, scenedata)
        -- 复活时移除buff
        entity:rmvGene(20007)
        
        -- 强制回城复活，不能停留在此地图
        Scene.conveyentitytoNPC(entity, 5200)
        local cbt = entity:getCombatSys()
        if cbt then
            cbt:updateHP(cbt:getMaxHP(), 0)
            cbt:updateMP(cbt:getMaxMP())
            entity:addGene(1)
            entity:setState(EP.gst_Idle)
        end
        return Error.Success
    end,
    
    onTimerEvent = {
        [1] = function(scene)  -- 每秒检查循环
            startCheckLoop(scene)
        end
    }
}