require 'math'


gdSkillExtension = {}

local EP = EntityProp


gdSkillTag =
{
	Skill_Tag_None		= -10,
	Skill_Tag_Main		= -1,
	Skill_Tag_splash	= -2,
	Skill_Tag_Self		= -3,
}

local ST = gdSkillTag

local LuckyData =
{
	[9] = {min = 0 ,max = 1},
	[8] = {min = 0.05, max = 0.50},
	[7] = {min = 0.05, max = 0.45},
	[6] = {min = 0.05, max = 0.40},
	[5] = {min = 0.05, max = 0.35},
	[4] = {min = 0.05, max = 0.30},
	[3] = {min = 0.05, max = 0.25},
	[2] = {min = 0.05, max = 0.20},
	[1] = {min = 0.05, max = 0.15},
	[0] = {min = 0.05, max = 0.10},
	[-9] = {min = 1 ,max = 0},
	[-8] = {min = 0.45, max = 0.50},
	[-7] = {min = 0.40, max = 0.45},
	[-6] = {min = 0.35, max = 0.40},
	[-5] = {min = 0.30, max = 0.35},
	[-4] = {min = 0.25, max = 0.30},
	[-3] = {min = 0.20, max = 0.25},
	[-2] = {min = 0.15, max = 0.20},
	[-1] = {min = 0.10, max = 0.15},
}

local DamageType =
{
	dm_physical = 1,
	dm_magical	= 2,
	dm_taosim	= 3,
}
local DT = DamageType

for k,v in pairs(LuckyData) do
	_G.onInitLuckyPercent(k,v.min,v.max)
end

local function getAttackP(srccbt,data)
	if not data then
		data = 1
	end
	local dmg_min = srccbt:getProps(Combat.prop_PATK_Min) * data
	local dmg_max = srccbt:getProps(Combat.prop_PATK_Max) * data
	if dmg_max - dmg_min  >  1 then

		local lucky = srccbt:getProps(Combat.prop_Luck) - srccbt:getProps(Combat.prop_Curse)
		if lucky > 9 then
			lucky = 9
		elseif lucky < -9 then
			lucky = -9
		end
		local ld = LuckyData[lucky]
		if not ld then
			ld = LuckyData[0]
	--		log.info("Lucky data caclulate Error Lucky = "..lucky)
		end

		local lpercnt = math.random()
		if lpercnt < ld.min then
			return dmg_min
		elseif lpercnt < ld.max then
			return dmg_max
		else
			return math.random(dmg_min ,dmg_max - 1)
		end
	else
	--	log.info("dmg max "..dmg_max)
	--	log.info("dmg mim "..dmg_min,data)
		return math.random(dmg_max - 1,dmg_min)
	end

end

local function getAttackM(srccbt,data)
	if not data then
		data = 1
	end
	local dmg_min = srccbt:getProps(Combat.prop_MATK_Min) * data
	local dmg_max = srccbt:getProps(Combat.prop_MATK_Max) * data
	if dmg_max - dmg_min  >  1 then

		local lucky = srccbt:getProps(Combat.prop_Luck) - srccbt:getProps(Combat.prop_Curse)
		if lucky > 9 then
			lucky = 9
		elseif lucky < -9 then
			lucky = -9
		end
		local ld = LuckyData[lucky]
		if not ld then
			ld = LuckyData[0]
	--		log.info("Lucky data caclulate Error Lucky = "..lucky)
		end

		local lpercnt = math.random()
		if lpercnt < ld.min then
			return dmg_min
		elseif lpercnt < ld.max then
			return dmg_max
		else
			return math.random(dmg_min ,dmg_max - 1)
		end
	else
		return math.random(dmg_max- 1,dmg_min)
	end

end
local function getAttackT(srccbt,data)
	if not data then
		data = 1
	end
	local dmg_min = srccbt:getProps(Combat.prop_TATK_Min) * data
	local dmg_max = srccbt:getProps(Combat.prop_TATK_Max) * data
	if dmg_max - dmg_min  >  1 then

		local lucky = srccbt:getProps(Combat.prop_Luck) - srccbt:getProps(Combat.prop_Curse)
		if lucky > 9 then
			lucky = 9
		elseif lucky < -9 then
			lucky = -9
		end
		local ld = LuckyData[lucky]
		if not ld then
			ld = LuckyData[0]
	--		log.info("Lucky data caclulate Error Lucky = "..lucky)
		end

		local lpercnt = math.random()
		if lpercnt < ld.min then
			return dmg_min
		elseif lpercnt < ld.max then
			return dmg_max
		else
			return math.random(dmg_min ,dmg_max - 1)
		end
	else
		return math.random(dmg_max- 1,dmg_min)
	end

end


local function getDefendP(tgtcbt)
	local def_min = tgtcbt:getProps(Combat.prop_PDEF_Min)
	local def_max = tgtcbt:getProps(Combat.prop_PDEF_Max)

	if def_min > def_max then
		def_min, def_max = def_max, def_min
	end
	return math.random(def_min,def_max)
end


local function getDefendM(tgtcbt)
	local def_min = tgtcbt:getProps(Combat.prop_MDEF_Min)
	local def_max = tgtcbt:getProps(Combat.prop_MDEF_Max)
	if def_min > def_max then
		def_min, def_max = def_max, def_min
	end
	return math.random(def_min,def_max)
end

local function isAttackMiss(srccbt, tgtcbt,sd)
	local s = tgtcbt:getProps(Combat.prop_Dodge) - srccbt:getProps(Combat.prop_Hit)
	if s <= 0 then
		return false
	else
		local dodgedata = math.random(100)
	--	log.info("P dodge data = "..dodgedata.." s = "..s)
		if (dodgedata < s) then
			tgtcbt:syncHpnoChangeReason(CombatProp.batt_miss,sd.delay)
			return true
		else
			return false
		end
	end
end

local function isMagicAttackMiss(srccbt, tgtcbt,sd)
	local s = tgtcbt:getProps(Combat.prop_Magic_Dodge) - srccbt:getProps(Combat.prop_Magic_Hit)
	if s <= 0 then
		return false
	else
		local dodgedata = math.random(100 * Combat.PercentToInt)
	--	log.info("M dodge data = "..dodgedata.." s = "..s)
		if (dodgedata < s) then
			tgtcbt:syncHpnoChangeReason(CombatProp.batt_miss,sd.delay)
			return true
		else
			return false
		end
	end
end

local function isPoisonMiss(srccbt,tgtcbt, sd)
	local s = tgtcbt:getProps(Combat.prop_Posion_Dodge)
	if s <= 0 then
		return false
	else
		local dodgedata = math.random(100 * Combat.PercentToInt)
	--	log.info("M dodge data = "..dodgedata.." s = "..s)
		if (dodgedata < s) then
			tgtcbt:syncHpnoChangeReason(CombatProp.batt_miss,1)
			return true
		else
			return false
		end
	end
end

local function checkMiss(srccbt,tgtcbt,sd,ismagic)
	if (isAttackMiss(srccbt,tgtcbt,sd)) then
		return true
	end

	if not ismagic then
		return false
	else
		return isMagicAttackMiss(srccbt, tgtcbt, sd)
	end
end

local function checkPalsy(src,tgt)
	local srccbt = src:getCombatSys()
	local s = srccbt:getProps(Combat.prop_Palsy)

	if (s > 0) then
		local dodgedata = math.random(100)-- * Combat.PercentToInt)
		if (dodgedata < s) then
			tgt:addGene(10214)
		end
	end

end


local function damagelastchange(damage,src,tgt,sd)
	if (src:isP() and src:getProps(EntityProp.attr_is_safe) ~= 0) then
		return Error.Success
	end
	if damage < 1 then
		damage = 1
	end
	local srccbt = src:getCombatSys()
	local tgtcbt = tgt:getCombatSys()

	checkPalsy(src,tgt) -- 麻痹属性测试

	if sd.attr then
		if sd.attr < 100 then -- 属性伤害免疫
			local data = tgtcbt:getImmunity(sd.attr)
			if data ~= 0 then
			--	log.info(sd.attr,data)
				if (data == 100) then
					tgtcbt:syncHpnoChangeReason(CombatProp.batt_immunity,sd.delay)
					return Error.Success
				end
				damage =  damage * (1 - data / 100)
			end
		elseif sd.attr == 100 then -- 采花贼
			local id = tgt:getStaticID()
			if id ~= 2016 and id ~= 2017 then
				return Error.Success
			end
		end
	end


	-- 检查战士的基础剑法额外伤害
	if (src:isP() and src:getStaticID() == 1) then
		local baseP = src:getProps(EntityProp.attr_zs_jichu_percent)
		if baseP > 0 then
			if (math.random(100) < baseP) then
				damage = damage + src:getProps(EntityProp.attr_zs_jichu_exdamage)
				--log.info("额外造成伤害 "..damage,src:getProps(EntityProp.attr_zs_jichu_exdamage))
			end
		end
	end

	-- 采花贼
	if tgt:isM() then
		local id = tgt:getStaticID()
		if id == 2016 or id == 2017 then
			damage = 1 + srccbt:getProps(Combat.prop_Holy_Damage)
			--log.info("damage = "..damage)
			tgtcbt:updateHP(-damage,sd.delay)
			tgt:onEvent(EventProp.GT_Combat,EventProp.EID_Be_Attacked,-damage,0,0,src)
			return Error.Success
		end
	end


	local exdamage = src:getProps(EntityProp.attr_gene_damage) / 100 + 1
	if (exdamage < 0) then
		log.error("exdamage = "..exdamage)
	end
	local mitigate = 1 - tgt:getProps(EntityProp.attr_gene_mitigate) / 100
	if (mitigate < 0) then
		log.error("mitigate = "..exdamage)
	end



	damage = damage * exdamage * mitigate

	if tgt:isM() then
		damage = damage + src:getProps(EP.attr_gene_damage_last_add) + srccbt:getProps(Combat.prop_Holy_Damage)
	end

	if tgt:isP() then
		damage = damage + src:getProps(EP.attr_attack_other_ex) /100 * damage
	end

	if damage <= 1  and damage > 0 then
		damage = 0
	end
	if damage ~= 0 then
		local damagetomagic = tgtcbt:getProps(Combat.prop_Damage_to_Magic) / 100 / Combat.PercentToInt
		local magicdown = math.floor(damage * damagetomagic)
		if damage > 0 then
			if magicdown >= 1 then
				local nowmp =tgtcbt:getProps(Combat.prop_MP)
				if nowmp < magicdown then
					magicdown = nowmp
				end
				if magicdown > 0 then
					tgtcbt:updateMP(-magicdown)
				end
			else
				magicdown = 0
			end
		else
			magicdown = 0
		end

		tgtcbt:updateHP(-(damage - magicdown) ,sd.delay)
	end
	local killsheildtime = sd.killsheild or 0
	tgt:onEvent(EventProp.GT_Combat,EventProp.EID_Be_Attacked,-damage,killsheildtime,0,src)
	return Error.Success
end

local function PlayerGrayName(src,tgt)
	if src:isP() then
		local scene = src:getScene()
		if scene then
			local sd = gdMaps[scene:getStaticID()]
			if sd and sd.pkred == 1 then -- 只在普通场景内pk改变pk值
				local etype = tgt:getType()
				if (etype == EntityProp.ett_Player or
					etype == EntityProp.ett_Pet) then
					local tgtpkstate = tgt:getProps(EntityProp.attr_pkstate)
					if tgtpkstate == Pkstate.pks_white or
						tgtpkstate == Pkstate.pks_yellow then
						src:setProps(EntityProp.attr_pkstate,Pkstate.pks_gray)
					end
				end
			end
		end
	end
end



gdSkillExtension.fakeSkillData = {
	datax = 100,
	datay = 0,
	dataz = 0,
	mana = 1,
}

gdSkillExtension.BaseAttack =
{
	onLoad = function(skill,sd)
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_physical,1)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)

		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_physical,1)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_splash,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
		skill:setSkillExeGrayName(ST.Skill_Tag_splash)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,false) then
	--		log.info("attack is miss!!!")
			return Error.Success
		end

		local attack = getAttackP(srccbt)
		local defend = getDefendP(tgtcbt)

		local dmg = attack - defend
		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
		--dmg = damagelastchange(dmg,srcentity,tgtentity,sd)
	end
}

gdSkillExtension.MagicBaseAttack =
{
	onLoad = function(skill,sd)
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_magical,1)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)

		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_magical,1)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
		skill:setSkillExeGrayName(ST.Skill_Tag_splash)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,true) then
	--		log.info("attack is miss!!!")
			return Error.Success
		end

		local attack = getAttackM(srccbt)
		local defend = getDefendM(tgtcbt)

		local dmg = attack - defend
		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
		--dmg = damagelastchange(dmg,srcentity,tgtentity,sd)
	end
}


gdSkillExtension.zsBase = {

	onLoad = function(skill,sd)
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_physical,1)
		skill:setSkillExeDamageZSBase(ST.Skill_Tag_Main)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)
	end,
	onAttach = function(entity, sd)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_Hit, sd.datau)
		end
		entity:setProps(EntityProp.attr_zs_jichu_percent,sd.datax)
		entity:setProps(EntityProp.attr_zs_jichu_exdamage,sd.datay)
	end,
	onDetach = function(entity,sd)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_Hit, -sd.datau)
		end
		entity:setProps(EntityProp.attr_zs_jichu_percent,0)
		entity:setProps(EntityProp.attr_zs_jichu_exdamage,0)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,false) then
		--	log.info("attack is miss!!!")
			return Error.Success
		end

		local attack = getAttackP(srccbt)
		local defend = getDefendP(tgtcbt)

		local dmg = attack - defend

		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
	end
}

gdSkillExtension.zsDamage = {
	onLoad = function(skill,sd)

		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_physical,sd.datax/100)
		skill:setSkillExeDamageStable(ST.Skill_Tag_Main,sd.datay,sd.datay)
		skill:setSkillExeDamageZSBase(ST.Skill_Tag_Main)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)
		if sd.lvl >= 3 then
			skill:setSkillExeSpeedSlow(ST.Skill_Tag_Main)
		end

		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_physical,1.8)
		skill:setSkillExeDamageZSBase(ST.Skill_Tag_splash)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_splash,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
		skill:setSkillExeGrayName(ST.Skill_Tag_splash)
		if sd.lvl >= 3 then
			skill:setSkillExeSpeedSlow(ST.Skill_Tag_splash)
		end

		skill:setSkillExeScript(ST.Skill_Tag_Self)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		srcentity:onEvent(EventProp.GT_Combat,EventProp.EID_EffectRmv,Effect.effect_firereborn)
	end
}

gdSkillExtension.zsCollide = {
	onLoad = function(skill,sd)
		skill:setSkillExeCollide(gdSkillTag.Skill_Tag_Main,sd.distance)
		
		-- 根据技能等级应用不同效果
		if sd.id == 144 then
			-- 原版技能（4级）：只有硬直
			if sd.lvl >= 4 then
				skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Target, 17)
			end
		elseif sd.id == 145 then
			-- 筑基版本（5级）：硬直+加速
			if sd.lvl >= 5 then
				skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Target, 17)  -- 目标硬直
				skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Self, 10215)  -- 自身加速
			end
		end
	end,
}

gdSkillExtension.zsDamageAround = {
	onLoad = function(skill,sd)

		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_physical,sd.datax/100)
		skill:setSkillExeDamageZSBase(ST.Skill_Tag_Main)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)

		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_physical,sd.datay/100)
		skill:setSkillExeDamageZSBase(ST.Skill_Tag_splash)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_splash,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
		skill:setSkillExeGrayName(ST.Skill_Tag_splash)

	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,false) then
		--	log.info("attack is miss!!!")
			return Error.Success
		end

		local data = 1

		if tag == gdSkillTag.Skill_Tag_Main then
			if (sd.datax) then
				data = sd.datax / 100
			end
		elseif tag ==gdSkillTag.Skill_Tag_splash then
			if (sd.datay) then
				data = sd.datay / 100
			end
		end

		local attack = getAttackP(srccbt,data)
		local defend = getDefendP(tgtcbt)


		local dmg = attack - defend

		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)

	end
}

gdSkillExtension.zsDamageTwoInFront = {
	onLoad = function(skill,sd)
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_physical,sd.datax/100)
		skill:setSkillExeDamageZSBase(ST.Skill_Tag_Main)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_physical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)

		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_physical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_physical,sd.datay/100)
		skill:setSkillExeDamageZSBase(ST.Skill_Tag_splash)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
		skill:setSkillExeGrayName(ST.Skill_Tag_splash)
	end,

	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,false) then
		--	log.info("attack is miss!!!")
			return Error.Success
		end

		local data = 1
		local attack = 1
		local defend = 0

		if tag == gdSkillTag.Skill_Tag_Main then
			if (sd.datax) then
				data = sd.datax / 100
				attack = getAttackP(srccbt,data)
				defend = getDefendP(tgtcbt)
			end
		elseif tag ==gdSkillTag.Skill_Tag_splash then
			if (sd.datay) then
				data = sd.datay / 100
				attack = getAttackP(srccbt,data)
			end
		end


		local dmg = attack - defend

		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)

	end
}
--烈焰重生
gdSkillExtension.zsFireReLive = {

	onLoad = function(skill,sd)
		skill:setSkillExeDamageLifePercent(gdSkillTag.Skill_Tag_Self,sd.datax/100)
		skill:setSkillExeDamageEnd(gdSkillTag.Skill_Tag_Self)
		skill:setSkillExeCleanCD(gdSkillTag.Skill_Tag_Self,111)
		skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Self,20120)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
	end
}





gdSkillExtension.fsDamage = {
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()
		local dmg_min = srccbt:getProps(Combat.prop_MATK_Min) * sd.datax/100 + sd.datay
		local dmg_max = srccbt:getProps(Combat.prop_MATK_Max) * sd.datax/100 + sd.datay

		local dmg = math.random(dmg_min, dmg_max)

		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
	end
}


gdSkillExtension.fsFireWall = {
	onExecuteArea = function(entity, scene, posx, posy, sd, tag)
		local srccbt = entity:getCombatSys()

		local entityS = scene:addS(sd.datax,posx,posy)
		entityS:setProps(EntityProp.attr_time_to_live,sd.datay)
		--entityS:setProps(EntityProp.attr_s_script_duration,1)
		entity:addRmvCleanEntity(entityS)
		return Error.Success
	end,

	onDamage = function(srcentity, tgtentity, basedamage, percentdamage)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if srcentity:isP() and tgtentity:isP() then
			local reborn = tgtentity:getProps(EntityProp.attr_reborn)
			local lvl = tgtentity:getLevel()
			if (reborn < 1 and lvl < 30) then
				return Error.Success
			end
		end

			-- 需要EntitySkill传入一个参数
		local sd = gdSkills[201]

		if checkMiss(srccbt,tgtcbt,sd,true) then
		--	log.info("attack is miss!!!")
			return Error.Success
		end

		local data = percentdamage / 100
		local attack = 1
		local defend = 0


		attack = getAttackM(srccbt,data) + basedamage
		defend = getDefendM(tgtcbt)

		local dmg = attack - defend

		tgtentity:setProps(EntityProp.attr_last_attacker,srcentity:getID())

		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
	end

}



gdSkillExtension.fsFireBall = {
	onAttach = function(entity, sd)
		if sd.datau and sd.datau ~= 0 then
			local cbt = entity:getCombatSys()
			cbt:addProps(Combat.prop_Hit, sd.datau)
		end
	end,
	onDetach = function(entity, sd)
		if sd.datau and sd.datau ~= 0 then
			local cbt = entity:getCombatSys()
			cbt:addProps(Combat.prop_Hit, -sd.datau)
		end
	end,
	onLoad = function(skill,sd)
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_magical,sd.datax/100)
		skill:setSkillExeDamageStable(ST.Skill_Tag_Main,sd.datay,sd.datay)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)


		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_magical,sd.datax/100)
		skill:setSkillExeDamageStable(ST.Skill_Tag_splash,sd.datay,sd.datay)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
		skill:setSkillExeGrayName(ST.Skill_Tag_splash)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,true) then
		--	log.info("attack is miss!!!")
			return Error.Success
		end

		local data = 1
		if (sd.datax) then
			data = sd.datax / 100
		end

		local attack = getAttackM(srccbt,data)
		local defend = getDefendM(tgtcbt)

		attack = attack + sd.datay

		local dmg = attack - defend
		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)

	end
}

gdSkillExtension.fsThunder = {
	onLoad = function(skill,sd)
		local data = 1
		if (sd.datax) then
			data = sd.datax / 100
		end
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_magical,sd.datax/100)
		skill:setSkillExeDamageStable(ST.Skill_Tag_Main,sd.datay,sd.dataz)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)
		if sd.lvl >= 3 then
			skill:setSkillExeSpeedSlow(ST.Skill_Tag_Main)
		end

		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_magical,0.33)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
		skill:setSkillExeGrayName(ST.Skill_Tag_splash)
		if sd.lvl >= 3 then
			skill:setSkillExeSpeedSlow(ST.Skill_Tag_splash)
		end
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)

		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,true) then
		--	log.info("attack is miss!!!")
			return Error.Success
		end

		local data = 1
		if (sd.datax) then
			data = sd.datax / 100
		end

		local attack = 0

		if tag == gdSkillTag.Skill_Tag_Main then
			attack = getAttackM(srccbt,data) + math.random(sd.datay,sd.dataz)
		--	log.info("main",attack,defend)
		elseif tag ==gdSkillTag.Skill_Tag_splash then
			attack = getAttackM(srccbt,0.33)
		--	log.info("splash",attack,defend)
		end

		local defend = getDefendM(tgtcbt)

		local dmg = attack - defend


		local speedslow = srcentity:getProps(EntityProp.attr_cl_speed)
		--log.info("slow ",speedslow)
		if sd.lvl >= 3 and speedslow ~= 0 then
			tgtentity:addGene(speedslow)
		end


		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)

	end
}



gdSkillExtension.fsCollide = {
	onExecute = function(srcentity, tgtentity, sd ,tag)
		log.info(sd.distance,tag)
		if tgtentity:isM() then
			local md = gdMonsters[tgtentity:getStaticID()]
			if md and md.isBoss == 1 then
				return Error.Success
			end
		end

		local srclvl = srcentity:getLevel()
		local tgtlvl = tgtentity:getLevel()
		if tgtlvl < 98 then
			local srcreborn = srcentity:getProps(EntityProp.attr_reborn)
			local tgtreborn = tgtentity:getProps(EntityProp.attr_reborn)

			if (srcreborn > tgtreborn) or (srcreborn == tgtreborn and srclvl > tgtlvl) then
					tgtentity:onEvent(EventProp.GT_Combat,
								EventProp.EID_Be_Collided,
								tag,
								sd.distance,
								srcentity:getID())
			end
		end
		return Error.Success
	end
}

gdSkillExtension.fsShield = {
	onAttach = function(entity,sd)
		entity:setProps(EntityProp.attr_gene_mitigateskill,sd.id)
	end,
	onDetach = function(entity,sd)
		entity:setProps(EntityProp.attr_gene_mitigateskill,0)
	end,

	onExecute = function(srcentity, tgtentity, sd ,tag)
		local gd = gdGenes[200]
		-- duration , percent, speed up time , cd time
		local srccbt = srcentity:getCombatSys()

		local attack = getAttackM(srccbt)
		local dur = 30
		dur = math.floor(11 + attack / 10)
	--	log.info("Shield duration = "..dur)
		srcentity:addGeneEx(gd.id, gd.groupid,gd.class,dur,true,sd.datax,3,3)
		return Error.Success
	end
}

--瞬移
gdSkillExtension.fsBlink = {
	onLoad = function(skill,sd)
		skill:setSkillExeBlink(gdSkillTag.Skill_Tag_Main,sd.distance)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		srcentity:onEvent(EventProp.GT_Combat,
								EventProp.EID_Fly,
								tag,
								sd.datax,
								srcentity:getID())
		return Error.Success
	end
}

gdSkillExtension.dsDamage = {
	onLoad = function(skill,sd)
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DamageType.dm_taosim)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_taosim,sd.datax/100)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_taosim)
		skill:setSkillExeHideDamage(ST.Skill_Tag_Main)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)
		skill:setSkillExeGrayName(ST.Skill_Tag_Main)
		skill:setSkillExeSpeedSlow(ST.Skill_Tag_Main)
		if sd.lvl >= 3 then
			skill:setSkillExeScript(ST.Skill_Tag_Main)
			skill:setSkillExeSpeedSlow(ST.Skill_Tag_Main)
		end
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
	

		local exds = srcentity:getProps(EntityProp.attr_ds_cl_damage)
		if exds ~= 0 then
			gdSkillExtension.dsPoison.onExecute(srcentity, tgtentity, sd ,tag)
		end
		
		return Error.Success
	end
}

gdSkillExtension.dsHealAround = {
	onExecute = function(srcentity, tgtentity, sd ,tag)

		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()
		local dmg_min = srccbt:getProps(Combat.prop_TATK_Min) * sd.datax/100 + sd.datay
		local dmg_max = srccbt:getProps(Combat.prop_TATK_Max) * sd.datax/100 + sd.dataz

		local dmg = math.random(dmg_min, dmg_max)
		local gd = gdGenes[12]
		tgtentity:addGeneEx(gd.id,gd.groupid,gd.class,5,true,sd.datax,gd.data.y,gd.data.z)
		return Error.Success
	end
}



gdSkillExtension.dsPoison = {
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local gd = gdGenes[201]
		--log.info("addGene 201")
		if srcentity:isP() then
			local class = srcentity:getStaticID()
			if class ~= 4 then  -- 天机跳过毒药属性检查
				local poison = srcentity:getProps(EntityProp.attr_ds_poison)
			--	print("poison = "..poison)
				if not poison or poison == 0 then
					return Error.Success
				end
			end
		end

		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		-- 等级5时只有35%命中率
		if sd.lvl == 5 then
			local hitChance = 50
			local hitRoll = math.random(1, 100)
			if hitRoll > hitChance then
				log.info("毒药术等级5未命中，掷点" .. hitRoll .. " > " .. hitChance)
				return Error.Success
			end
			log.info("毒药术等级5命中，掷点" .. hitRoll .. " <= " .. hitChance)
		end
		
		-- 其他等级使用原有判断逻辑
		if sd.lvl ~= 5 then
			if isPoisonMiss(srccbt,tgtcbt, sd) then
				return Error.Success
			end
		end

		PlayerGrayName(srcentity,tgtentity)

		local attack = getAttackT(srccbt)
		local dur = 10
		local datax = 0 -- 每秒掉血
		local datay = 0 -- 魔法防御
		local dataz = 0 -- 物理防御

		if sd.lvl == 1 then
			dur = math.floor(10 + attack / 28)
			datax = math.floor(25 + attack / 10)
		elseif sd.lvl == 2 then
			dur = math.floor(15 + attack / 27)
			datax = math.floor(35 + attack / 9)
			datay = math.floor(15 + attack / 25)
			dataz = math.floor(15 + attack / 25)
		elseif sd.lvl == 3 then
			dur = math.floor(20 + attack / 26)
			datax = math.floor(45 + attack / 8)
			datay = math.floor(25 + attack / 25)
			dataz = math.floor(20 + attack / 26)
		elseif sd.lvl == 4 then
			dur = math.floor(25 + attack / 25)
			datax = math.floor(55 + attack / 7)
			datay = math.floor(35 + attack / 25)
			dataz = math.floor(25 + attack / 27)
		elseif sd.lvl == 5 then
			dur = math.floor(30 + attack / 30)
			datax = math.floor(1500 + attack / 3.5)  -- 大幅提升！基础1500，系数1/3.5
			datay = math.floor(1000 + attack / 25)
			dataz = math.floor(575 + attack / 27)
			tgtentity:addGene(19)
		end

		log.info("dur, datax, ",dur,datax)
		if tgtentity:isM() then
			local id = tgtentity:getStaticID()
			if id == 2016 or id == 2017 then
				datax = 1
			end
		end

		-- 等级5时无视毒抗，其他等级受毒抗影响
		if sd.lvl ~= 5 then
			local poisondown = tgtcbt:getProps(Combat.prop_Posion_Recovery_Point)
			dur = math.floor(dur * (1 - poisondown / (100 * Combat.PercentToInt)))
			log.info("等级" .. sd.lvl .. "受毒抗影响，调整后持续时间：" .. dur)
		else
			log.info("等级5无视毒抗，持续时间：" .. dur)
		end
--		log.info("毒药术 持续 = "..dur..",hpdown/s = "..datax..",mdefdown = "..datay..",pdefdown = "..dataz)

		tgtentity:addGeneEx(gd.id,gd.groupid,gd.class,dur,true,datax,datay,dataz)
		return Error.Success
	end
}

gdSkillExtension.dsVisable = {
	onExecute = function(srcentity,tgtentity, sd, tag)
		local gd = gdGenes[20]
		local srccbt = srcentity:getCombatSys()
		tgtentity:addGeneEx(gd.id,gd.groupid,gd.class,gd.duration,gd.dead,gd.data.x,gd.data.y,gd.data.z)
		return Error.Success
	end
}

gdSkillExtension.dsExercise = {
	onAttach = function(entity,sd)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_Hit,sd.datax)
		if sd.datau and sd.datau ~= 0 then
			cbt:addProps(Combat.prop_Magic_Hit, sd.datau * Combat.PercentToInt)
		end
	end,
	onDetach = function(entity,sd)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_Hit,-sd.datax)
		if sd.datau and sd.datau ~= 0 then
			cbt:addProps(Combat.prop_Magic_Hit, -sd.datau * Combat.PercentToInt)
		end
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		return Error.Success
	end
}


gdSkillExtension.dsGhost = {
	onAttach = function(entity,sd)
		entity:setProps(EntityProp.attr_ds_ghost,sd.datax)
		entity:addGene(36)
	end,
	onDetach = function(entity,sd)
		local cbt = entity:getCombatSys()
		entity:setProps(EntityProp.attr_ds_ghost,0)
		entity:rmvGene(36)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)
		return Error.Success
	end
}

gdSkillExtension.dsSummon = {
	onAttach = function(entity,sd)
--		entity:setProps(EntityProp.attr_dog_max,2)
		entity:syncProps(EntityProp.attr_dog_max)
		entity:syncProps(EntityProp.attr_dog_cnt)
	end,
	onExecuteArea = function(entity, scene, posx, posy, sd, tag)
		local srccbt = entity:getCombatSys()
		local posx,posy,posz = entity:getPosition()
		-- 检查当前已有召唤兽数量
		local oldCnt = entity:getProps(EntityProp.attr_dog_cnt) or 0
		if sd.lvl <= 3 then
			entity:summonDog(sd.datax)
		else
			entity:summonDogEx(sd.datax, sd.datay, sd.dataz)
		end
		-- 如果召唤后数量没变且为0，说明没有宠物实体，创建一个再召唤（天机专属）
		local newCnt = entity:getProps(EntityProp.attr_dog_cnt) or 0
		if newCnt == oldCnt and oldCnt == 0 and entity:getStaticID() == 4 then
			entity:addDog(sd.datax)
			if sd.lvl <= 3 then
				entity:summonDog(sd.datax)
			else
				entity:summonDogEx(sd.datax, sd.datay, sd.dataz)
			end
		end
		return Error.Success
	end,

}

--大隐于市
gdSkillExtension.dsHide = {
	onLoad = function(skill,sd)
		skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Self,sd.datax)
	end,

}

gdSkillExtension.monsterSummon = {
	onAttach = function(entity,sd)

	end,
	onDetach = function(entity,sd)

	end,
	onExecuteArea = function(entity, scene, posx, posy, sd, tag)
		--log.info("____________droid____monsterSummon______")
		--local srccbt = entity:getCombatSys()
		local posx,posy,posz = entity:getPosition()
		local rvt = scene:addM(sd.datax,posx,posy)
		if rvt ~= Error.Success then
			return rvt
		end
		return Error.Success
	end
}

gdSkillExtension.Mining= {
	onAttach = function(entity,sd)

	end,
	onDetach = function(entity,sd)

	end,
	onExecuteArea = function(entity, scene, posx, posy, sd, tag)
		local id = gdLootnametoID[sd.desc_before_learn]
		if scene:getStaticID() ~= MapID.kd then
		--	log.info("now map id =",scene:getStaticID(),"should ",MapID.kd,"item id =",sd.id)
			return Error.Item_CantDoIt
		end
		-- set Player to Mining state
		Loot.callReward(nil,entity,id,Opcode.Op_Mine)
		return Error.Success
	end
}

gdSkillExtension.DiamondMining= {
	onAttach = function(entity,sd)

	end,
	onDetach = function(entity,sd)

	end,
	onExecuteArea = function(entity, scene, posx, posy, sd, tag)
		local id = gdLootnametoID[sd.desc_before_learn]

		if scene:getStaticID() ~= MapID.bkdk then
			log.info("now map id =",scene:getStaticID(),"should ",MapID.kd,"item id =",sd.id)
			return Error.Item_CantDoIt
		end
		-- set Player to Mining state
		Loot.callReward(nil,entity,id,Opcode.Op_Mine)
		return Error.Success
	end
}

gdSkillExtension.Bomb = {
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()
		local dmg = srccbt:getProps(Combat.prop_Holy_Damage) + sd.datax

		tgtentity:syncEntityBeUsedSkill(sd.id)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
	end
}

gdSkillExtension.addBuff = {
	onExecute = function(srcentity, tgtentity, sd ,tag)
		if sd.datax and sd.datax ~= 0 then
			tgtentity:addGene(sd.datax)
		else
			log.info("add Gene Skill Find datax !")
		end
		if sd.datay and sd.datay ~= 0 then
			srcentity:addGene(sd.datay)
		else
		--	log.info("add Gene Skill Find datay !")
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end
}

gdSkillExtension.MonkillLong = {
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,false) then
	--		log.info("attack is miss!!!")
			return Error.Success
		end

		local data = 1
		if (sd.datax) then
			data = sd.datax / 100
		end

		local attack = getAttackP(srccbt,data)
		local defend = getDefendP(tgtcbt)

		local dmg = attack - defend


		tgtentity:addGene(sd.datay)
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
	end
}

gdSkillExtension.posioncloud = function(entity,percent)
	local cbt = entity:getCombatSys()
	if cbt then
		local defend = getDefendM(cbt)
		local attack = cbt:getMaxHP() * percent
		local dmg = attack - defend
		if dmg <= 0 then
			dmg = 1
		end
		--dmg = damagelastchange(dmg,srcentity,tgtentity)
		cbt:updateHP(-dmg,1)
		--entity:syncEntityBeUsedSkill(sd.id)
	end
end


gdSkillExtension.IronWall =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		if sd.datay ~=0 then
			tgtentity:addGene(sd.datay)
		end
		return Error.Success
	end,
	onExecuteSelf = function(srcentity, sd)
		srcentity:addGene(sd.datax)
		srcentity:syncEntityBeUsedSkill(sd.id)
	end
}

gdSkillExtension.magicandgene =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if (sd.datax and sd.datax ~= 0 ) then
			if checkMiss(srccbt,tgtcbt,sd,true) then
	--			log.info("attack is miss!!!")
				return Error.Success
			end

			local data = sd.datax / 100

			local attack = getAttackM(srccbt,data)
			local defend = getDefendM(tgtcbt)

			local dmg = attack - defend

			return damagelastchange(dmg,srcentity,tgtentity,sd)
		end
		if (sd.datay) and sd.datay ~= 0 then
			tgtentity:addGene(sd.datay)
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end,
}

gdSkillExtension.PercentBigDamage =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if (sd.datax and sd.datax ~= 0 ) then
			if checkMiss(srccbt,tgtcbt,sd,false) then
	--			log.info("attack is miss!!!")
				return Error.Success
			end

			local data = 1
			if (math.random(100) < sd.datay) then
				data = sd.datax / 100
			end

			local attack = getAttackM(srccbt,data)
			local defend = getDefendM(tgtcbt)

			local dmg = attack - defend
			return damagelastchange(dmg,srcentity,tgtentity,sd)
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end,
}

gdSkillExtension.DeadDamage =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if (sd.datax and sd.datay ) then
			--if checkMiss(srccbt,tgtcbt,false) then
			--	log.info("attack is miss!!!")
			--	return Error.Success
			--end

			local srchp = srccbt:getMaxHP()
			srccbt:updateHP(-srchp * sd.datax / 100,srcentity)

			local tgthp = tgtcbt:getMaxHP()
			local attack = tgthp * sd.datay / 100
			local defend = getDefendM(tgtcbt)

			local dmg = attack - defend

			return damagelastchange(dmg,srcentity,tgtentity,sd)
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end,
}

gdSkillExtension.SoundAround =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		if sd.datax and sd.datax ~= 0 then
			tgtentity:addGene(sd.datax)
		else
	--		log.info("add Gene Skill Find datax !")
		end
		if sd.datay and sd.datay ~= 0 then
			if sd.dataz then
				if (math.random(100)< sd.dataz) then
					srcentity:addGene(sd.datay)
				end
			end
		else
	--		log.info("add Gene Skill Find datay !")
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end,
}

gdSkillExtension.AttractPlayer =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		if sd.datax and sd.datax ~= 0 then
			tgtentity:addGene(sd.datax)
		end
		local srcposx,srcposy,_ = srcentity:getPosition()

		local scene = tgtentity:getScene()

		if (scene) then
			scene:flyEntity(tgtentity,srcposx,srcposy)
		end

		tgtentity:syncEntityBeUsedSkill(sd.id)
--		log.info("src posx ,posy ",srcposx,srcposy)
--		tgtentity:setPostion(srcposx,srcposy,0)
 --		srcentity
		return Error.Success
	end,
}

gdSkillExtension.beEaten =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		local posion = srcentity:getProps(EntityProp.attr_posion)

		if (sd.datax and sd.datay ) then
			local srchp = srccbt:getMaxHP()
			srccbt:updateHP(-srchp,srcentity)

			if posion == 1 then
				tgtcbt:updateHP(-sd.datax,sd.delay)
			else
				tgtcbt:updateHP(sd.datay,sd.delay)
			end
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end,
}
gdSkillExtension.TotemDamage =
{
	onExecute = function(srcentity,tgtentity, sd, tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()
		local dmg = sd.datax

		damagelastchange(dmg,srcentity,tgtentity,sd)

		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end
}

gdSkillExtension.TotemaddBuff =
{
	onExecute = function(srcentity,tgtentity, sd, tag)
		if sd.datax and sd.datax ~= 0 then
			tgtentity:addGene(sd.datax)
		else
			log.info("add Gene Skill Find datax !")
		end
		if sd.datay and sd.datay ~= 0 then
			srcentity:addGene(sd.datay)
		else
		--	log.info("add Gene Skill Find datay !")
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end
}

gdSkillExtension.raceattack =
{
	onExecute = function(srcentity,tgtentity, sd, tag)
		if sd.datax and sd.datax ~= 0 then
			if tag == gdSkillTag.Skill_Tag_Main then
				damagelastchange(sd.datax,srcentity,tgtentity,sd)
			end
		end
		if sd.datay and sd.datay ~= 0 then
			tgtentity:addGene(sd.datay)
		else
			log.info("add Gene Skill Find datax !")
		end
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end
}

-- 冲刺技能
gdSkillExtension[2031] =
{
	onExecute = true,
	onLoad = function(skill,sd)
		skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Self,10215)
	end,
}

-- 减速他人
gdSkillExtension[2032] =
{
	onExecute = true,
	onLoad = function(skill,sd)
		skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Main,10216)
		skill:setSkillExeBuff(gdSkillTag.Skill_Tag_splash,10216)
	end,
}

-- 隐身
gdSkillExtension[2033] =
{
	onExecute = true,
	onLoad = function(skill,sd)
		skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Self,10217)
	end,
}

-- 顺劈
gdSkillExtension.spDamage =
{
	onExecute = function (srcentity,tgtentity, sd, tag)
		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if checkMiss(srccbt,tgtcbt,sd,false) then
		--	log.info("attack is miss!!!")
			return Error.Success
		end

		local data = 1

		local attack = getAttackP(srccbt,data)
		local defend = getDefendP(tgtcbt)


		local dmg = attack - defend

		PlayerGrayName(srcentity,tgtentity)
		return damagelastchange(dmg,srcentity,tgtentity,sd)
	end,
}

-- 陨石标记
gdSkillExtension[5081] =
{
	onExecute = function(srcentity, tgtentity, sd, tag)
		log.info("skill 5081 onExecute")
		if tgtentity then
			local srcgene = gdGenes[sd.datay]
			srcentity:addGeneEx(srcgene.id, srcgene.groupid, srcgene.class,
				srcgene.duration,srcgene.dead,tgtentity:getID(),3,3)

			local tgtgene = gdGenes[sd.datax]
			tgtentity:addGeneEx(tgtgene.id, tgtgene.groupid, tgtgene.class,
				tgtgene.duration,tgtgene.dead,tgtentity:getID(),3,3)

			local scene = tgtentity:getScene()
			if scene then
			--	scene:syncFloatMessage("你们都去死吧!")
			end
		end

		srcentity:addTimerEvent(1, 3000, 1)	-- 3S后陨石
		return Error.Success
	end,
}


gdSkillExtension[5084] =
{
	onExecute = function(srcentity, tgtentity, sd, tag)
	end,
}

-- 冰冻陷阱
gdSkillExtension.iceTrap =
{
	onExecuteArea = function(entity, scene, posx, posy, sd, tag)
		if tag ~= ST.Skill_Tag_Main then
			return Error.Success
		end
		local count = 0
		local nums = 1
		local range = 5
		local maximumTries = (range * 2) * (range * 2) * 2
		local tries = 1
		local filled = {}
		local entityPos = {}
		scene:forEachEntity(function (entity)
					if (entity:isP() or entity:isDog())  and entity:isAlive() then
						count = count + 1
						local pos = entity:getPositionX() * 10000 + entity:getPositionY()
						entityPos[pos] = 1
					end
				end)
		count = count + 1
		while nums <= count and tries <= maximumTries do
			tries = tries + 1
			-- log.info("tries="..tries)
			local x = math.random(-range, range)
			local y = math.random(-range, range)
			if x ~= 0 and y ~= 0 then
				x = posx + x
				y = posy + y
				local index = x * 10000 + y
				if (filled[index] ~= 1) and (entityPos[index] ~= 1) and (not scene:hasBlock(x, y)) then
					filled[index] = 1
					log.info("########x="..x..",y="..y)
					local entityS = scene:addS(202,x,y)
					entityS:setProps(EntityProp.attr_time_to_live, sd.datax)
					entityS:setProps(EntityProp.attr_s_script_duration, 0)
					nums = nums + 1
					--entity:addRmvCleanEntity(entityS)
				end
			end
		end
		entity:addTimerEvent(1, 4000, 1)	--4秒后喊话
		entity:addTimerEvent(2, 7000, 1)	--7秒后群攻
		return Error.Success
	end,
}

--群攻
gdSkillExtension.allAttack =
{
	onExecute = function(srcentity,tgtentity, sd, tag)
		local damage = sd.datax
		damagelastchange(damage,srcentity,tgtentity,sd)
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end
}

gdSkillExtension.ysDamage =
{
	onExecute = function(srcentity,tgtentity, sd, tag)
		local damage = sd.datax / _G.getSkillTargetCnt()
		damagelastchange(damage,srcentity,tgtentity,sd)
		tgtentity:syncEntityBeUsedSkill(sd.id)
		return Error.Success
	end
}

-- 群体火球
gdSkillExtension[5067] =
{
	onLoad = function(skill,sd)
		skill:setSkillExeCheck(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_Main,DT.dm_magical,sd.datax/100)
		skill:setSkillExeDamageStable(ST.Skill_Tag_Main,sd.datay,sd.datay)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_Main,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_Main)

		skill:setSkillExeCheck(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageAttack(ST.Skill_Tag_splash,DT.dm_magical,sd.datax/100)
		skill:setSkillExeDamageStable(ST.Skill_Tag_splash,sd.datay,sd.datay)
		skill:setSkillExeDamageDefend(ST.Skill_Tag_splash,DT.dm_magical)
		skill:setSkillExeDamageEnd(ST.Skill_Tag_splash)
	end,
	onExecute = function (srcentity,tgtentity, sd, tag)
		-- body
	end,
}

-- 爆炸火焰
gdSkillExtension[5068] =
{
	onExecuteArea = function(entity, scene, posx, posy, sd, tag)
		local entityS = scene:addS(201,posx,posy)
		entityS:setProps(EntityProp.attr_time_to_live,4)
		return Error.Success
	end,
}


-- 捆绑
gdSkillExtension[5069] =
{
	onLoad = function(skill, sd)
		skill:setSkillExeBuff(gdSkillTag.Skill_Tag_Self,20044)
	end,
	onExecute = function (srcentity,tgtentity, sd, tag)
		-- body
	end,
}

-- 剧毒 (群体)
gdSkillExtension[5070] =
{
	onExecute = function(srcentity, tgtentity, sd ,tag)
		local gd = gdGenes[201]

		local srccbt = srcentity:getCombatSys()
		local tgtcbt = tgtentity:getCombatSys()

		if isPoisonMiss(srccbt,tgtcbt, sd) then
			return Error.Success
		end

		local attack = getAttackT(srccbt)
		local dur = 60
		local datax = 2000 -- 每秒掉血
		local datay = 1000 -- 魔法防御
		local dataz = 1000 -- 物理防御


		local poisondown = tgtcbt:getProps(Combat.prop_Posion_Recovery_Point)
		dur = math.floor(dur * (1 - poisondown / (100 * Combat.PercentToInt)))
--		log.info("毒药术 持续 = "..dur..",hpdown/s = "..datax..",mdefdown = "..datay..",pdefdown = "..dataz)

		tgtentity:addGeneEx(gd.id,gd.groupid,gd.class,dur,true,datax,datay,dataz)
		return Error.Success
	end
}


-- 吸收武器
gdSkillExtension[5075] =
{
	onLoad = function(skill, sd)
		skill:setSkillExeScript(gdSkillTag.Skill_Tag_Main)
		skill:setSkillExeScript(gdSkillTag.Skill_Tag_splash)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)


		srcentity:rmvGene(20303)
		local item = tgtentity:getItemByPosition(ItemProp.ItemPosition_Equip_Weapon)
		if item then
			srcentity:setProps(EntityProp.attr_m_absorb_weapon_sid,item:getSID())
			srcentity:setProps(EntityProp.attr_m_absorb_weapon_lvl,item:getProps(ItemProp.Item_EnhanceLevel))
			srcentity:addGene(20303)
			local scene = srcentity:getScene()
			if scene then
				scene:syncFloatMessage(tgtentity:getName().."的武器被"..srcentity:getName().."吸收了!")
			end
			tgtentity:addGene(20300)
		end

		return Error.Success
	end,
}

-- 偷取装备
gdSkillExtension[5076] =
{
	onLoad = function(skill, sd)
		skill:setSkillExeScript(gdSkillTag.Skill_Tag_Main)
		skill:setSkillExeScript(gdSkillTag.Skill_Tag_splash)
	end,
	onExecute = function(srcentity, tgtentity, sd ,tag)

		srcentity:rmvGene(20304)
		local item1 = tgtentity:getItemByPosition(ItemProp.ItemPosition_Equip_Cloth)
		if item1 then
			srcentity:setProps(EntityProp.attr_m_absorb_cloth_sid,item1:getSID())
			srcentity:setProps(EntityProp.attr_m_absorb_cloth_lvl,item1:getProps(ItemProp.Item_EnhanceLevel))
			tgtentity:addGene(20301)
		end
		if item2 then
			local item2 = tgtentity:getItemByPosition(ItemProp.ItemPosition_Equip_Fashion)
			srcentity:setProps(EntityProp.attr_m_absorb_fasion_sid,item2:getSID())
			srcentity:setProps(EntityProp.attr_m_absorb_fasion_lvl,item2:getProps(ItemProp.Item_EnhanceLevel))
			tgtentity:addGene(20302)

		end
		if item1 or item2 then
			srcentity:addGene(20304)

			local scene = srcentity:getScene()
			if scene then
				scene:syncFloatMessage(tgtentity:getName().."的衣服和时装被"..srcentity:getName().."吸收了!")
			end
		end


		return Error.Success
	end,
}
