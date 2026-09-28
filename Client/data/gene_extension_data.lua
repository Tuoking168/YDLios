require 'math'

if not gdGeneExtension then
	gdGeneExtension = {}
end


-- 坐骑buff,魔法防御提高10%
gdGeneExtension[10103] = 
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-10 * Combat.PercentToInt)
	end,
}


-- 坐骑buff,物理防御提高10%
gdGeneExtension[10104] = 
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-10 * Combat.PercentToInt)
	end,
}


--
--	剧毒乌云   	jdwy
--



gdGeneExtension[20004] =  --剧毒乌云 3级
{
	onAttach = function(entity)
	end,

	onDetach = function(entity)
	end,
	onUpdate = function(entity)
		gdSkillExtension.posioncloud(entity,0.02)
	end
}

gdGeneExtension[20005] =  --剧毒乌云 4级
{
	onAttach = function(entity)
	end,

	onDetach = function(entity)
	end,

	onUpdate = function(entity)
		gdSkillExtension.posioncloud(entity,0.025)
	end
}


gdGeneExtension[20006] =  --剧毒乌云 5级
{
	onAttach = function(entity)
	end,

	onDetach = function(entity)
	end,

	onUpdate = function(entity)
		gdSkillExtension.posioncloud(entity,0.04)
	end
}

gdGeneExtension[20007] =  --剧毒乌云 6级
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack,800)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack,-800)
	end,
	onUpdate = function(entity)
		gdSkillExtension.posioncloud(entity,0.03)--百分之8    0.03
	end

}


--
--  铜墙铁壁 	tqtb
--
gdGeneExtension[20008] =  --铜墙铁壁1级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-10 * Combat.PercentToInt)
	end,
}

gdGeneExtension[20009] =  --铜墙铁壁2级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,15 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-15 * Combat.PercentToInt)
	end,
}


gdGeneExtension[20010] =  --铜墙铁壁3级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,10 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,-5)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-10 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,5)
	end,
}

gdGeneExtension[20011] =  --铜墙铁壁4级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,15 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,-10)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-15 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,10)
	end,
}


--
--		一夫当关   yfdg
--

gdGeneExtension[20017] =  --一夫当关1级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,13 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,13 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,8 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-13 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-13 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-8 * Combat.PercentToInt)
	end,
}

gdGeneExtension[20018] =   --一夫当关2级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-10 * Combat.PercentToInt)
	end,
}

gdGeneExtension[20019] =   --一夫当关3级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,17 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,17 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,12 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-17 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-17 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-12 * Combat.PercentToInt)
	end,
}

gdGeneExtension[20020] =   --一夫当关4级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_HPMax,-10 * Combat.PercentToInt)
	end,
}


--
--		金刚伏魔   jgfm
--
gdGeneExtension[20021] =   --金刚伏魔1级
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, -500)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, 500)
	end,
}
gdGeneExtension[20022] =   --金刚伏魔2级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,5 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,5 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,5 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_interval_attack, -700)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-5 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-5 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-5 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_interval_attack, 700)
	end,
}
gdGeneExtension[20023] =   --金刚伏魔3级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-10 * Combat.PercentToInt)
	end,
}
gdGeneExtension[20024] =   --金刚伏魔4级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,15 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-15 * Combat.PercentToInt)
	end,
}

--
--		火烧天下  hstx
--
gdGeneExtension[20025] =   --火烧天下1级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,10 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,20)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-10 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,-20)
	end,
}
gdGeneExtension[20026] =   --火烧天下2级
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,15 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,15 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,35)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,10 * Combat.PercentToInt)
		entity:addProps(EntityProp.attr_gene_be_damage,-35)
	end,
}


--
--		霜冻天下  sdtx
--
gdGeneExtension[20028] =   --霜冻天下3级
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, 700)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, -700)
	end,
}
gdGeneExtension[20029] =   --霜冻天下4级
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, 1000)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, -1000)
	end,
}
gdGeneExtension[20030] =   --霜冻天下5级
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, 500)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, -500)
	end,
}
gdGeneExtension[20031] =   --霜冻天下6级
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, 1500)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, -1500)
	end,
}
gdGeneExtension[20032] =   --霜冻天下7级
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, 500)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-9 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_interval_attack, -500)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,9 * Combat.PercentToInt)
	end,
}


--
--		咆哮  px
--
gdGeneExtension[20034] =   --咆哮攻击下降buff 1  35%
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-35 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,35 * Combat.PercentToInt)
	end,
}

gdGeneExtension[20035] =   --咆哮攻击下降buff 2  10%
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,10 * Combat.PercentToInt)
	end,
}

gdGeneExtension[20036] =   --咆哮攻击上升Buff 2 10%
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-10 * Combat.PercentToInt)
	end,
}


gdGeneExtension[20037] =   --咆哮攻击下降Buff 3 10%
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-10 * Combat.PercentToInt)
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,10 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,10 * Combat.PercentToInt)
	end,
}

--
--		熔岩霸主  rybz
--
gdGeneExtension[20040] =   -- 降低20%魔法伤害
{
	onAttach = function(entity)
		entity:addProps(EntityProp.attr_gene_be_magic_damage, -20)
	end,

	onDetach = function(entity)
		entity:addProps(EntityProp.attr_gene_be_magic_damage, 20)
	end,
}


--
--		五指山下  wzsx
--

gdGeneExtension[60000] =   -- 免疫中毒伤害
{
	onAttach = function(entity)
		if entity:getProps(EntityProp.attr_xmfb_buff)==2 then
			log.info("add gene id 60003")
			entity:rmvGene(60003)
		end
		entity:setProps(EntityProp.attr_xmfb_buff,1)
		return Error.Success
	end,

	onDetach = function(entity)
		local scene = entity:getScene()
		if scene and scene:getStaticID()==1011 then
			scene:setProps(SP.xmfb_already_potion, 0)
		end
		entity:setProps(EntityProp.attr_xmfb_buff,0)
		return Error.Success
	end,
}

gdGeneExtension[60001] =   -- 提高全属性攻击35%
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Min,35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Min,35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Min,35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,35 * Combat.PercentToInt)
		return Error.Success
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Min,-35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Min,-35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Min,-35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_PATK_Max,-35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MATK_Max,-35 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_TATK_Max,-35 * Combat.PercentToInt)

		local scene = entity:getScene()
		if scene and scene:getStaticID()==1015 then
			scene:setProps(SP.xmfb_already_potion, 0)
		end
		return Error.Success
	end,
}

gdGeneExtension[60002] =   -- 提高全属性防御25%
{
	onAttach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Min,25 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,25 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Min,25 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,25 * Combat.PercentToInt)
		return Error.Success
	end,

	onDetach = function(entity)
		local cbt = entity:getCombatSys()
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Min,-25 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_PDEF_Max,-25 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Min,-25 * Combat.PercentToInt)
		cbt:addProps(Combat.prop_End + Combat.prop_MDEF_Max,-25 * Combat.PercentToInt)

		local scene = entity:getScene()
		if scene and scene:getStaticID()==1016 then
			scene:setProps(SP.xmfb_already_potion, 0)
		end
		return Error.Success
	end,
}

gdGeneExtension[60003] =   -- 中毒伤害
{
	onAttach = function(entity)
		return Error.Success
	end,

	onDetach = function(entity)
		entity:setProps(EntityProp.attr_xmfb_buff,0)
		return Error.Success
	end,
}


gdGeneExtension[50900] =   --  副本状态
{
	onAttach = function(entity)
		return Error.Success
	end,

	onDetach = function(entity)
		entity:rmvItemAllBySid(39050)
		entity:rmvItemAllBySid(39051)
		entity:rmvItemAllBySid(39052)
		return Error.Success
	end,
}

local function linkentitystrong(cbt,md,percent)
	for k,v in pairs(md.attr) do
		if v.type and v.type >= 5 and v.type <= 16 then
			if v.data then
				cbt:setProps(v.type, v.data * percent)
			else
				cbt:setProps(v.type, v.min * percent)
				cbt:setProps(v.type+1, v.max * percent)
			end
		end
	end
end

gdGeneExtension[20200] =  -- 灵魂链接
{
	onAttach = function(entity)
		return Error.Success
	end,

	onDetach = function(entity)
		return Error.Success
	end,

	onUpdate = function(entity)
		local scene = entity:getScene()
		if not scene then
			return Error.Unknown
		end
		--log.error("get Scene")
		local eid = entity:getProps(EntityProp.attr_link_entity)
		local oe = scene:getEntity(eid)
		if not oe then
			return Error.Unknown
		end
		--log.error("get linkentity")

		local posx1,posy1,posz1 = entity:getPosition()
		local posx2,posy2,posz2 = oe:getPosition()

		--log.error("posx1 = "..posx1)
		--log.error("posy1 = "..posy1)
		--log.error("posx2 = "..posx2)
		--log.error("posy2 = "..posy2)
		local dis = math.max(math.abs(posx1 - posx2),math.abs(posy1 - posy2))
		local cbt = entity:getCombatSys()
		local md  = gdMonsters[entity:getStaticID()]


		--log.error("dis = "..dis)
		if dis < 5 then
			linkentitystrong(cbt,md,2)
		elseif dis < 10 then
			linkentitystrong(cbt,md,1.5)
		elseif dis < 20 then
			linkentitystrong(cbt,md,1)
		else
			linkentitystrong(cbt,md,0.5)
		end

		return Error.Success
	end,
}

local function equipabsorb(entity,sid,elvl,per)
	local sd = gdItems[sid]
	local cbt = entity:getCombatSys()
	if sd and cbt and sd.attr then
		for _, v in pairs(sd.attr) do
			if v.type then
				if v.type <= Combat.prop_End * 2 then
					if v.data then
						log.info("add item data1")
						cbt:addProps(v.type, v.data*per)
					else
						log.info("add item data2",v.min*per, v.max*per)
						cbt:addProps(v.type, v.min*per)
						cbt:addProps(v.type + 1, v.max*per)
					end
				end
			end
		end
	end

	if elvl ~= 0 and cbt and sd then
		local sdEnhance = gdEquipEnhance[elvl-1]
		if sdEnhance and sd and sd.attr then
			for _, v in pairs(sd.attr) do
				if v.type then
					if v.type <= Combat.prop_End * 2 then
						if v.max then
							log.info("add strong data")
							cbt:addProps(v.type+1, sdEnhance.enhanceValue*per)
						end
					end
				end
			end
		end
	end
end


local function equipback(entity,sid,elvl,per)
	local sd = gdItems[sid]
	local cbt = entity:getCombatSys()
	if sd and cbt and sd.attr then
		for _, v in pairs(sd.attr) do
			if v.type then
				if v.type <= Combat.prop_End * 2 then
					if v.data then
						cbt:addProps(v.type, -v.data*per)
					else
						cbt:addProps(v.type, -v.min*per)
						cbt:addProps(v.type + 1, -v.max*per)
					end
				end
			end
		end
	end

	if elvl ~= 0 and cbt and sd then
		local sdEnhance = gdEquipEnhance[elvl-1]
		if sdEnhance and sd and sd.attr then
			for _, v in pairs(sd.attr) do
				if v.type then
					if v.type <= Combat.prop_End * 2 then
						if v.max then
							cbt:addProps(v.type+1, -sdEnhance.enhanceValue*per)
						end
					end
				end
			end
		end
	end
end

gdGeneExtension[20303] =  -- 吸收武器
{
	onAttach = function(entity)
		local sid = entity:getProps(EntityProp.attr_m_absorb_weapon_sid)
		local elvl = entity:getProps(EntityProp.attr_m_absorb_weapon_lvl)
		log.info("weapon sid = "..sid.." .lvl = "..elvl)

		equipabsorb(entity,sid,elvl,2)

		return Error.Success
	end,

	onDetach = function(entity)
		local sid = entity:getProps(EntityProp.attr_m_absorb_weapon_sid)
		local elvl = entity:getProps(EntityProp.attr_m_absorb_weapon_lvl)
		log.info("weapon sid = "..sid.." .lvl = "..elvl)
		equipback(entity,sid,elvl,2)

		return Error.Success
	end,
}


gdGeneExtension[20304] =  -- 偷取装备
{
	onAttach = function(entity)
		local sid = entity:getProps(EntityProp.attr_m_absorb_cloth_sid)
		local elvl = entity:getProps(EntityProp.attr_m_absorb_cloth_lvl)
		equipabsorb(entity,sid,elvl,2)

		sid = entity:getProps(EntityProp.attr_m_absorb_fasion_sid)
		elvl = entity:getProps(EntityProp.attr_m_absorb_fasion_lvl)
		equipabsorb(entity,sid,elvl,2)

		return Error.Success
	end,

	onDetach = function(entity)
		local sid = entity:getProps(EntityProp.attr_m_absorb_cloth_sid)
		local elvl = entity:getProps(EntityProp.attr_m_absorb_cloth_lvl)
		equipback(entity,sid,elvl,2)

		sid = entity:getProps(EntityProp.attr_m_absorb_fasion_sid)
		elvl = entity:getProps(EntityProp.attr_m_absorb_fasion_lvl)
		equipback(entity,sid,elvl,2)
		return Error.Success
	end,
}

gdGeneExtension[20305] =  -- 吸收武器
{

	onAttach = function(entity)
		entity:addEffect(Effect.effect_be_attacking)
		return Error.Success
	end,

	onDetach = function(entity)
		entity:rmvEffect(Effect.effect_be_attacking)
		return Error.Success
	end,
}

gdGeneExtension[20306] =  -- 吸收武器
{
	onAttach = function(entity)
		return Error.Success
	end,

	onDetach = function(entity)
		return Error.Success
	end,
}

gdGeneExtension[20307] =  -- 吸收武器
{
	onAttach = function(entity)

		return Error.Success
	end,

	onDetach = function(entity)

		return Error.Success
	end,
}

gdGeneExtension[20309] =  -- 冰冻
{
	onAttach = function(entity)
		entity:addEffect(Effect.effect_freezon_ice)
		log.info("`````````````````````gene id = 20309")
		return Error.Success
	end,

	onDetach = function(entity)
		entity:rmvEffect(Effect.effect_freezon_ice)
		log.info("`````````````````````aa gene id = 20309")
		return Error.Success
	end,
}
