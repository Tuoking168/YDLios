require 'math'

gdHeadTitleExtension = {}

local FP = FuncProp
local WP = WorldProp
local EP = EntityProp
local SP = SceneProp

gdHeadTitleExtension[50100] = 	--第一战士
{
	onAttach = function(entity)
		local damage = 5
		entity:addProps(EP.attr_gene_damage,damage)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local damage = 5
		entity:addProps(EP.attr_gene_damage,-damage)
		return Error.Success
	end,
}

gdHeadTitleExtension[50101] = 	--第一法师
{
	onAttach = function(entity)
		local damage = 5
		entity:addProps(EP.attr_gene_damage,damage)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local damage = 5
		entity:addProps(EP.attr_gene_damage,-damage)
		return Error.Success
	end,
}

gdHeadTitleExtension[50102] = 	--第一道士
{
	onAttach = function(entity)
		local damage = 5
		entity:addProps(EP.attr_gene_damage,damage)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local damage = 5
		entity:addProps(EP.attr_gene_damage,-damage)
		return Error.Success
	end,
}

gdHeadTitleExtension[50103] = 	--天下无敌
{
	onAttach = function(entity)
		local killmonster = 1
		entity:addProps(EP.attr_gene_loot_exp,killmonster)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local killmonster = 1
		entity:addProps(EP.attr_gene_loot_exp,-killmonster)
		return Error.Success
	end,
}

gdHeadTitleExtension[50104] = 	--囧神
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,200)
			cbt:addProps(Combat.prop_MDEF_Max,200)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,10*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,10*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
	
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,-200)
			cbt:addProps(Combat.prop_MDEF_Max,-200)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-10*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,-10*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
}

gdHeadTitleExtension[50105] = 	--高帅富
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,20)
			cbt:addProps(Combat.prop_MDEF_Max,20)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,5*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,5*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
	
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,-20)
			cbt:addProps(Combat.prop_MDEF_Max,-20)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-5*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,-5*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
}

gdHeadTitleExtension[50106] = 	--白富美
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,20)
			cbt:addProps(Combat.prop_MDEF_Max,20)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,5*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,5*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
	
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,-20)
			cbt:addProps(Combat.prop_MDEF_Max,-20)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-5*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,-5*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
}

gdHeadTitleExtension[50107] = 	--真高帅富
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,75)
			cbt:addProps(Combat.prop_MDEF_Max,75)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,12*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,12*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
	
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,-75)
			cbt:addProps(Combat.prop_MDEF_Max,-75)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-12*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,-12*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
}

gdHeadTitleExtension[50108] = 	--真白富美
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,75)
			cbt:addProps(Combat.prop_MDEF_Max,75)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,12*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,12*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
	
	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		if cbt then
			cbt:addProps(Combat.prop_PDEF_Max,-75)
			cbt:addProps(Combat.prop_MDEF_Max,-75)
			cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-12*100)
			cbt:addProps(Combat.prop_End + Combat.prop_MPMax,-12*100)
			entity:syncPlayerCombatCombo()
		end
		return Error.Success
	end,
}

gdHeadTitleExtension[50109] = 	--小有影响
{
	onAttach = function(entity)
		local value = 5
		entity:addProps(EP.attr_gene_money_cnt,value)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local value = 5
		entity:addProps(EP.attr_gene_money_cnt,-value)
		return Error.Success
	end,
}

gdHeadTitleExtension[50110] = 	--慈善大使
{
	onAttach = function(entity)
		local value = 15
		entity:addProps(EP.attr_gene_money_cnt,value)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local value = 15
		entity:addProps(EP.attr_gene_money_cnt,-value)
		return Error.Success
	end,
}

gdHeadTitleExtension[50111] = 	--竞技之王
{
	onAttach = function(entity)
		local damage = 3
		entity:addProps(EP.attr_gene_damage,damage)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local damage = 3
		entity:addProps(EP.attr_gene_damage,-damage)
		return Error.Success
	end,
}

gdHeadTitleExtension[50112] = 	--杀戮之王
{
	onAttach = function(entity)
		local damage = 2
		entity:addProps(EP.attr_gene_damage,damage)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local damage = 2
		entity:addProps(EP.attr_gene_damage,-damage)
		return Error.Success
	end,
}

gdHeadTitleExtension[50113] = 	--决斗之王
{
	onAttach = function(entity)
		local damage = 1
		entity:addProps(EP.attr_gene_damage,damage)
		return Error.Success
	end,
	
	onDetach = function(entity)
		local damage = 1
		entity:addProps(EP.attr_gene_damage,-damage)
		return Error.Success
	end,
}

gdHeadTitleExtension[50200] = 	
{
	onAttach = function(entity)
	
		return Error.Success
	end,
	onDetach = function(entity)--移除天下无敌
		HeadTitle.entityRmvHeadTitle(entity,8)
		return Error.Success
	end,
}

gdHeadTitleExtension[50201] = 	
{
	onAttach = function(entity)
	
		return Error.Success
	end,
	onDetach = function(entity)--移除囧神
		HeadTitle.entityRmvHeadTitle(entity,12)
		return Error.Success
	end,
}