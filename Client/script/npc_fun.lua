--[[
namespace CPEventName
{
	// event from ui
	static const std::string UI_OPEN = "ui_open";
}
--]]

local openPanel = function(panelName)
	g_dispatcherEvent("ui_open", "npc_talk_handler", "GameUI", panelName)
end

local npcFunctions = {
	[53] = function(data)
		openPanel("EmigratedPanel")
	end,

	[107] = function(data)
		openPanel("ConvoyBeautyPanel")
	end,

	[106] = function(data)
		openPanel("NPCbagPanel")
	end,

	[117] = function(data)
		openPanel("NPCbagPanel")
	end,

	[144] = function(data) -- µ⁄“ªƒ–’Ω ø
		local pid1 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_zs_data, 0, "world_prop")
		if pid1 and (pid1 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_zs_data, 3, "world_prop")
			if (gender == 1) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid1)
				return
			end
		end

		local pid2 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_ds_data, 0, "world_prop")
		if pid2 and (pid2 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_ds_data, 3, "world_prop")
			if (gender == 1) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid2)
				return
			end
		end
		cpnotification.addNote("‘›Œﬁµ⁄“ªƒ–’Ω ø°£", 0)
	end,

	[145] = function(data) -- µ⁄“ªƒ–∑® ¶
		local pid1 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_fs_data, 0, "world_prop")
		if pid1 and (pid1 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_fs_data, 3, "world_prop")
			if (gender == 1) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid1)
				return
			end
		end

		local pid2 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_fs_data, 0, "world_prop")
		if pid2 and (pid2 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_fs_data, 3, "world_prop")
			if (gender == 1) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid2)
				return
			end
		end
		cpnotification.addNote("‘›Œﬁµ⁄“ªƒ–∑® ¶°£", 0)
	end,

	[146] = function(data) -- µ⁄“ªƒ–µ¿ ø
		local pid1 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_ds_data, 0, "world_prop")
		if pid1 and (pid1 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_ds_data, 3, "world_prop")
			if (gender == 1) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid1)
				return
			end
		end

		local pid2 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_ds_data, 0, "world_prop")
		if pid2 and (pid2 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_ds_data, 3, "world_prop")
			if (gender == 1) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid2)
				return
			end
		end
		cpnotification.addNote("‘›Œﬁµ⁄“ªƒ–µ¿ ø°£", 0)
	end,

	[164] = function(data)
		openPanel("NPCbagPanel")
	end,

	[178] = function(data)
		openPanel("SpiderPanel")
	end,

	[186] = function(data) -- µ⁄“ª≈Æ’Ω ø
		local pid1 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_zs_data, 0, "world_prop")
		if pid1 and (pid1 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_zs_data, 3, "world_prop")
			if (gender == 2) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid1)
				return
			end
		end

		local pid2 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_zs_data, 0, "world_prop")
		if pid2 and (pid2 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_zs_data, 3, "world_prop")
			if (gender == 2) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid2)
				return
			end
		end
		cpnotification.addNote("‘›Œﬁµ⁄“ª≈Æ’Ω ø°£", 0)
	end,

	[187] = function(data) -- µ⁄“ª≈Æ∑® ¶
		local pid1 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_fs_data, 0, "world_prop")
		if pid1 and (pid1 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_fs_data, 3, "world_prop")
			if (gender == 2) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid1)
				return
			end
		end

		local pid2 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_fs_data, 0, "world_prop")
		if pid2 and (pid2 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_fs_data, 3, "world_prop")
			if (gender == 2) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid2)
				return
			end
		end
		cpnotification.addNote("‘›Œﬁµ⁄“ª≈Æ∑® ¶°£", 0)
	end,

	[188] = function(data) -- µ⁄“ª≈Æµ¿ ø
		local pid1 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_ds_data, 0, "world_prop")
		if pid1 and (pid1 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_ds_data, 3, "world_prop")
			if (gender == 2) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid1)
				return
			end
		end

		local pid2 = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_ds_data, 0, "world_prop")
		if pid2 and (pid2 > 0) then
			local gender = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.prop_first_other_ds_data, 3, "world_prop")
			if (gender == 2) then
				g_sendMessage("MsgGetOtherPlayerDataRequest", pid2)
				return
			end
		end
		cpnotification.addNote("‘›Œﬁµ⁄“ª≈Æµ¿ ø°£", 0)
	end,

	[216] = function(data)
		openPanel("NPCbagPanel")
	end,

	[5301] = function(data)
		openPanel("NPCbagPanel")
	end,

	[1431] = function(data)
		openPanel("WorshipPanel")
	end,
}

npc_talk_handler = function(npcID, data)
	npcID = npcID or 0
	local func = npcFunctions[npcID]
	if func then
		func(data)
	end
end
----------------------------------------------------------------------------------------
--NPCÂ≠óÁ¨¶‰∏≤Êï¥Âêà

local npcRequestWorldData = function(wid)
	g_dispatcherEvent("npc_requestdata", "getdynamictabel", "server", wid , 0)
end

local npcRequestWorldDataS = function(wid)
	g_dispatcherEvent("npc_requestdata", "getdynamictabel", "server", wid , 1)
end

local npcRequestInstanceData = function()
	-- To Do BY Daiqi
	g_dispatcherEvent("npc_requestinstancedata", "getdynamictabel", "server")
	-- MsgGetInstanceCntRequest
end

local getInstanceTimesString = function(eid)
	local entertimes = gdceapon.get_sub_data("activity","instance_list", eid, "instance_enter_count") or 0
	local totaltimes = gdEventData[eid].datax
	local addtimes = gdceapon.get_sub_data("activity","instance_list", eid, "instance_enter_allcount") or 0
	totaltimes = totaltimes + addtimes
	local textcontent={}
	textcontent[1]=entertimes.."/"..totaltimes
	return textcontent
end

local getdynamictabel = {
	[53] = {
		replaceContent = function()
			local textcontent={}
			textcontent[1]=1
			textcontent[2]=2
			return textcontent
		end,
	},

	[13111] = {
		replaceContent = function()
			local textcontent={}
			textcontent[1]= gdceapon.get_sub_data("activity", "world_string_prop_" .. WorldProp.ysjdc_rank, 0, "world_prop") or "Œﬁ"
			return textcontent
		end,

		requestData = function()
			npcRequestWorldDataS(WorldProp.ysjdc_rank)
		end,
	},

	[133] = {
		replaceContent = function()
			local textcontent={}
			textcontent[1]=gdceapon.get_data("hero","prop_"..EntityProp.attr_reborn) or 0
			textcontent[2]=gdceapon.get_data("hero","prop_"..EntityProp.attr_rebornrqeitem) or 0
			return textcontent
		end,
	},

	[1332] = {
		replaceContent = function()
			local textcontent={}
			local rbl = gdceapon.get_data("hero","prop_"..EntityProp.attr_reborn) or 0
			textcontent[1]= (rbl+1) * 1000
			textcontent[2]= (rbl+1) * 1000000
			return textcontent
		end,
	},


	[1431] =
	{
		replaceContent = function()
			local textcontent={}
			local cntmobai = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.mobai_bishi_count, 0, "world_prop") or 0
			local cntbishi = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.mobai_bishi_count, 1, "world_prop") or 0
			textcontent[1]= cntmobai
			textcontent[2]= cntbishi
			textcontent[3]= gdceapon.get_sub_data("activity", "world_string_prop_" .. WorldProp.city_master_player, 0, "world_prop") or "Œﬁ"
			textcontent[4]= gdceapon.get_sub_data("activity", "world_string_prop_" .. WorldProp.city_master_guild, 0, "world_prop") or "Œﬁ"
			return textcontent
		end,

		requestData = function()
			npcRequestWorldData(WorldProp.mobai_bishi_count)
			npcRequestWorldDataS(WorldProp.city_master_guild)
			npcRequestWorldDataS(WorldProp.city_master_player)
		end,
	},

	[1433] =
	{
		replaceContent = function()
			local textcontent={}
			local cntmobai = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.mobai_bishi_count, 0, "world_prop") or 0
			local cntbishi = gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.mobai_bishi_count, 1, "world_prop") or 0
			textcontent[1]= cntmobai
			textcontent[2]= cntbishi
			return textcontent
		end,

		requestData = function()
			npcRequestWorldData(WorldProp.mobai_bishi_count)
		end,
	},

	[1434] =
	{
		replaceContent = function()
			local textcontent={}
			textcontent[1]= gdceapon.get_sub_data("activity", "world_int_prop_" .. WorldProp.mobai_money_count, 0, "world_prop") or 0
			return textcontent
		end,

		requestData = function()
			npcRequestWorldData(WorldProp.mobai_money_count)
		end,
	},

	[178] =  {
		replaceContent = function()
			local textcontent={}
			textcontent[1]=gdceapon.get_data("activity","zhu_mo_jie_zhen_0") or 0	--ÂÖ®ÊúçÁªìÈòµÊï∞
			textcontent[2]=gdceapon.get_data("activity","zhu_mo_jie_zhen_1") or "Œ¥À¢–¬"	--bossÂà∑Êñ∞Êó∂Èó¥
			textcontent[3]=gdceapon.get_sub_data("activity","ex_data_list",22,"ex_data_x") or 0	-- ‰∏™‰∫∫ÁªìÈòµÊï∞
			return textcontent
		end,
	},

	[1793] = {
		replaceContent = function()
			local textcontent={}
			textcontent[1]= gdceapon.get_sub_data("activity","ex_data_list", EID.qfxzqfz, "ex_data_x") or 0
			return textcontent
		end,
	},

	[1794] = {
		replaceContent = function()
			local textcontent={}
			textcontent[1]= gdceapon.get_sub_data("activity", "world_string_prop_" .. WorldProp.qfxz_rank, 0, "world_prop") or "Œﬁ"
			return textcontent
		end,

		requestData = function()
			npcRequestWorldDataS(WorldProp.qfxz_rank)
		end,
	},

	[5303] =  {
		replaceContent = function()
			local textcontent={}
			textcontent[1]=1
			textcontent[2]=2
			return textcontent
		end,
	},

	[126] = {
		requestData = function()
			npcRequestInstanceData()
		end,
	},

	[1261] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.jwxg)	end,
	},
	[1262] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.gzlm)	end,
	},
	[1263] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.mymy)	end,
	},
	[1264] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.ygkd)	end,
	},
	[1265] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.hscbd)	end,
	},

	[127] = {
		requestData = function()
			npcRequestInstanceData()
		end,
	},

	[1271] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.embhs)	end,
	},
	[1272] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.ymsm)	end,
	},
	[1273] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.hjhd)	end,
	},
	[1274] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.mjfy)	end,
	},
	[1275] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.syjj)	end,
	},


	[129] = {
		requestData = function()
            if gameconf and gameconf.gameVersion < 9 then
				gdNPC[1294] = {
					id=1294,
					name="[g(–¬)]⁄§ªÍ…ÒµÓ[y£®æ´”¢∏±±æ£©][g£®1◊™35º∂◊∞±∏∏±±æ£©] (X1)",
					anim=0,
					hideInWorldMap=1,
					lvl=20,
					nFunction= {
							[1]= nil,
							[2]= nil,
							[3]= nil,
							[4]= {nfunc="129",ntype=7,numid=4,show=1,},
						},
					text= {
							[1]= {color="w",content="øÕªß∂À∞Ê±æÃ´µÕ£¨Œﬁ∑®Ω¯»Î£¨«Î…˝º∂µΩ9∞Ê±æ",},
						},
					}	
			end
			npcRequestInstanceData()
		end,
	},

	[1291] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.bwlb)	end,
	},
	[1292] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.tdxm)	end,
	},
	[1293] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.sdmy)	end,
	},
	[1294] = {
		replaceTitleName = function()	return getInstanceTimesString(EID.mhsd)	end,
	},

	[1313] = {
		--	’Ω…Ò’˘∞‘ zszb ≥∆∞‘ÃÏœ¬ cbtx
		replaceContent = function()
			local textcontent={}
			textcontent[1]= gdceapon.get_sub_data("activity", "world_string_prop_" .. WorldProp.zszb, 0, "world_prop") or "Œﬁ"
			return textcontent
		end,

		requestData = function()
			npcRequestWorldDataS(WorldProp.zszb)
		end,
	},

	[184] =  {
		replaceContent = function()--Á•àÁ¶èÊ†ë
			local textcontent={}
			textcontent[1]=gdceapon.get_data("activity","qi_fu_shu_0") or 0	--Á•àÁ¶èÂÄº
			textcontent[2]=gdceapon.get_data("activity","qi_fu_shu_1") or 0	--Á•àÁ¶èÊ†ëÁ≠âÁ∫ß
			textcontent[3]=gdceapon.get_data("activity","qi_fu_shu_2") or 0	--ÁªèÈ™åÂä†Êàê
			return textcontent
		end,
	},

	[14301] =  {
		replaceContent = function()
			local textcontent={}
			textcontent[1]=1
			textcontent[2]=2
			return textcontent
		end,
	},

	[3271] =  {
		isclose = function(datax)
			local switch = {
				[1] = function()
					return false
				end,
				[2] = function()
					return false
				end
				}
			if switch[datax] then
				return switch[datax]()
			end
			return true
		end,
	},

	[153] = {
		replaceTitleName = function()
			local textcontent = {}
			local pk_value = gdceapon.get_data("hero", "prop_" .. EntityProp.attr_pkvalue)
			if pk_value > 99 then
				textcontent[1] = (pk_value - 99) * 10000
				textcontent[2] = (pk_value - 99) * 0.5
				if textcontent[2] > math.modf(textcontent[2]) then
					textcontent[2] = math.modf(textcontent[2]) + 1
				end
			else
				textcontent[1] = 0
				textcontent[2] = 0
			end

			--textcontent[3]=gdceapon.get_sub_data("activity","ex_data_list",EID.,"ex_data_x") or 0
			local usecnt = gdceapon.get_sub_data("activity","ex_data_list",EID.freeclearredname,"ex_data_x") or 0
			local allcnt = gdceapon.get_sub_data("activity","ex_data_list",EID.freeclearredname,"ex_data_y") or 0
			textcontent[3] = allcnt - usecnt

			--log.info("textcontent = ", "{" .. textcontent[1] .. "," .. textcontent[2] .. "," .. textcontent[3].."}")
			return textcontent
		end,
	},

	[101] = {
		replaceTitleName = function()
			local textcontent = {}
			local level = gdceapon.get_data("hero", "level")
			local reborn = gdceapon.get_data("hero", "prop_" .. EntityProp.attr_reborn) or 0
			textcontent[1] = reborn * 40000 + level * 500

			--log.info("textcontent = ", "{" .. textcontent[1] .. "," .. textcontent[2] .. "," .. textcontent[3].."}")
			return textcontent
		end,
	},

	[114] = {
		replaceTitleName = function()
			local textcontent = {}
			local level = gdceapon.get_data("hero", "level")
			local reborn = gdceapon.get_data("hero", "prop_" .. EntityProp.attr_reborn) or 0
			textcontent[1] = reborn * 40000 + level * 500
			log.info("reborn=",reborn)
			--log.info("textcontent = ", "{" .. textcontent[1] .. "," .. textcontent[2] .. "," .. textcontent[3].."}")
			return textcontent
		end,
	},

	[162] = {
		replaceTitleName = function()
			local textcontent = {}
			local level = gdceapon.get_data("hero", "level")
			local reborn = gdceapon.get_data("hero", "prop_" .. EntityProp.attr_reborn) or 0
			textcontent[1] = reborn * 40000 + level * 500

			--log.info("textcontent = ", "{" .. textcontent[1] .. "," .. textcontent[2] .. "," .. textcontent[3].."}")
			return textcontent
		end,
	},

	[215] = {
		replaceTitleName = function()
			local textcontent = {}
			local level = gdceapon.get_data("hero", "level")
			local reborn = gdceapon.get_data("hero", "prop_" .. EntityProp.attr_reborn) or 0
			textcontent[1] = reborn * 40000 + level * 500

			--log.info("textcontent = ", "{" .. textcontent[1] .. "," .. textcontent[2] .. "," .. textcontent[3].."}")
			return textcontent
		end,
	},
}
--[[
get_npc_requestwiddata = function(npcID)
	local dynamictable = getdynamictabel[npcID]
	if dynamictable and dynamictable.wid then
		local size = #dynamictable.wid
		for i=1,size do
			npcRequestData(dynamictable.wid[i].worldid,dynamictable.wid[i].type)
		end
	end
end
--]]

get_npc_requestwiddata = function(npcID)
	local dynamictable = getdynamictabel[npcID]
	if dynamictable and dynamictable.requestData then
		log.info(npcID)
		dynamictable.requestData()
	end
end


get_npc_talkcontent = function(npcID)
	npcID = npcID or 0
	local static = ""
	local eu = gdNPC[npcID]
	if eu then
		static = eu.text
	end
	local dynamic = getdynamictabel[npcID]
	if dynamic and dynamic.replaceContent then
		dynamic = getdynamictabel[npcID].replaceContent()
		local size=#dynamic
		log.info(size)
		--print(size)
		for i=1,size do
			static=string.gsub(static, "X"..i, dynamic[i])
		end
	end
	return static
end

get_npc_talkcontent_sub = function(npcID,content)
	local static = content
	local dynamic = getdynamictabel[npcID]
	if dynamic and dynamic.replaceContent then
		dynamic = getdynamictabel[npcID].replaceContent()
		local size=#dynamic
		for i=1,size do
			static=string.gsub(static, "X"..i, dynamic[i])
		end
	end
	--log.info("NPCcontent finish = ",static)
	return static
end

get_npc_talkfuncname_sub = function(npcID,content)
    if npcID == 1294 and gameconf and gameconf.gameVersion < 9 then
    	return (content == "0" and "") or content
    end
	local static = content
	--log.info("NPCcontent begin = ",static)
	local dynamic = getdynamictabel[npcID]
	if dynamic and dynamic.replaceTitleName then
		dynamic = getdynamictabel[npcID].replaceTitleName()
		local size=#dynamic
		for i=1,size do
			static=string.gsub(static, "X"..i, dynamic[i])
		end
	end
	--log.info("NPCcontent finish = ",static)
	return static
end

get_npc_panelcolse = function(npcID,datax)
	local dynamic = getdynamictabel[npcID]
	log.info(npcID,datax)
	if dynamic and dynamic.isclose then
		dynamic = getdynamictabel[npcID].isclose(datax)
		--log.info(dynamic)
		return dynamic
	end
	return true
end

itemdurablemoney = function(sid,durable)
	return gdGame.getItemRepairMoney(sid,durable)
end
