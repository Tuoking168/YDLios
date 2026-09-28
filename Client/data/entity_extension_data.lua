
local EP = EntityProp
local WP = WorldProp
local SP = SceneProp
local IP = ItemProp

if not gdEntitySEx then
	gdEntitySEx = {}
end


local function fireexpget(lvl)
	local baseexp = gdFireExp[lvl]
	if baseexp then
		return baseexp
	else
		log.error("invalid fire exp lvl! lvl = "..lvl)
		return 100
	end
end


gdEntitySEx =
{
	[100] = {
		onUpdate = function(entity,meetentity)
			local base = 100
			if (meetentity:isP()) then
				meetentity:addExp(fireexpget(meetentity:getLevel()), Opcode.Op_fire)
			end
		end,
	},

	[101] = {
		onLoad = function(entity)
			entity:setProps(EntityProp.attr_s_ignore_block,1)
		end,
	},
	-- ±ù¿é
	[200] = { -- ±ù¶³ÏÝÚå
		onUpdate = function(entity,meetentity)
			-- if meetentity:isP() or meetentity:isDog() then
			-- 	meetentity:addGene(20307)
			-- 	meetentity:addGene(20308)
			-- end
		end,
	},

	[201] = { -- ±¬Õ¨»ðÑæ
		onUpdate = function(entity,meetentity)
			if meetentity:isP() or meetentity:isDog() then
				local cbt = meetentity:getCombatSys()
				if cbt then
					cbt:updateHP(-3000,3)
				end
			end
		end,

	},

	[202] = { -- ÏÝÚå
		onUpdate = function(entity,meetentity)
			if meetentity:isP() then
				local scene = meetentity:getScene()
				if scene then
					scene:rmvEntity(entity:getID())
					meetentity:addGene(20307)
					meetentity:addGene(20308)
					meetentity:addGene(20309)
				end
			end
		end,

	},

	[300] = {
		onUpdate = function(entity,meetentity)
--
		end,
	},
	[305] = {
		onUpdate = function(entity,meetentity)
			if (meetentity:isP()) then
				if Event.isActive(EID.gcz) then
					local level = meetentity:getLevel()
					if level >= 35 then
						Scene.conveyentitytoAnywhere(meetentity,MapID.sc,305,154)
					end
				end
			end
		end,
	},
	[306] = {
		onUpdate = function(entity,meetentity)
			if (meetentity:isP()) then
				local mapid = MapID.shg
				if Event.isActive(EID.gcz) then
					mapid = MapID.gczshg
				end

				if meetentity:getProps(EntityProp.attr_guild_id) == _G.getWorldDataX(WP.city_master_guild) then
					Scene.conveyentitytoscene(meetentity,mapid)
				end
			end
		end,
	},
	[307] = {
		onUpdate = function(entity,meetentity)
			if meetentity:isP() and Event.isActive(EID.gcz) then
				local level = meetentity:getLevel()
				if level >= 35 then
					Scene.conveyentitytoscene(meetentity,MapID.gczshg)
				end
			end
		end,
	},

}
