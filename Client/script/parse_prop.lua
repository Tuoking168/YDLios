local _G=_G
local table = require "table"
module("parse_prop")

function get_prop(tb, ...)
	local t = _G[tb]
	if not t then
		return 0
	end

	local arg = {...}
	local temptable = t[arg[1]]
	while temptable do
		t = temptable
		table.remove(arg, 1)
		if #arg == 0 then
			break
		end
		temptable = t[arg[1]]
	end

	if #arg ~= 0 then
		return 0
	end

	if (not t) then
		_G.print("no data")
		return 0
	end

	return t

end

function get_prop_by_key(tb,key)
	local t = _G[tb]
	if t then
		return t[key]
	end
	_G.print("no data")
	return nil
end

function get_sub_prop(tb,id,stb,sid,key)
	local gt = _G[tb]
	if gt then
		local t = gt[id]
		if t then
			st = t[stb]
			if st[sid] then
				return st[sid][key] or 0
			end
		end
	end
	_G.print("no data")
	return 0
end

function get_prop_merge(tb,id,sub_inx,key)
	local t = _G[tb]
	if t then
		local unit = t[id]
		if unit then
			local p=unit[sub_inx]
			if p then
				return p[key] or 0
			end
		end
	end
	_G.print("no data")
	return 0
end

function check_monsterinmap(tb,id,tb1,ghostid)
	local t = _G[tb]
	if t then
		local unit = t[id]
		if unit then
			local p=unit[tb1]
			if p then
				local size=#p
				while b<=size do
					local n=p[b]
					if ghostid==n.id then
						return 1
					end
					b=b+1
				end
			end
		end
	end
	return 0
end

function checkExist(tb,id)
	local t = _G[tb]
	if t then
		local unit = t[id]
		if unit then
			return 1
		end
	end
	return 0
end

function get_prop_size(tb, ...)
	local t = _G[tb]
	if not t then
		return 0
	end

	local arg = {...}
	local temptable = t[arg[1]]
	--_G.print("get_prop_size:")
	while temptable do
		t = temptable
		table.remove(arg, 1)
		temptable = t[arg[1]]
	end

	if (not t) then
		_G.print("no data")
		return 0
	end

	_G.print("get_prop_end:")
	local count=0
	for k,v in _G.pairs(t) do
		if v then
			count = count +1
		end
	end
	return count

end

function get_prop_subprop(tb,id,tb_1,id_sub,key1,key2)
	local t = _G[tb]
	local unit = t[id]
	if unit then
	    local child=unit[tb_1]
		if child then
			local n=child[id_sub]
		    if n then
		        return n[key1],n[key2]
			end
		end
	end
	_G.print("no data")
	return 0,0
end

function get_prop_pet(tb,id,tb_1,key)
	local t = _G[tb]
	local unit = t[id]
	if unit then
	    local child=unit[tb_1]
		if child then
		    return child[key]
		end
	end
	_G.print("no data")
	return 0,0
end

function get_prop_ItemInfo(tb,id,tb_1,sub_id,key1,key2,key3)
	local t = _G[tb]
	local unit = t[id]
	local count = 0
	if unit then
	    local child=unit[tb_1]
		if child then
		local m=_G.table.maxn(child)
			for i=1,m do
				local n=child[i]
				if n then
					count=count+1
					if count==sub_id then
						if n[key1] then
							return n[key1],n[key2],n[key3]
						else
							return n.data,n.data,n[key3]
						end
					end
				end
			end
		end
	end
	_G.print("no data")
	return 0,0,0
end

function getProp_GhostMapID(tb,id,tb1)
	local t = _G[tb]
	if t then
	local i=_G.table.maxn(t)
		for a=1,i do
			b=1
			local unit=t[a]
			if unit then
				local p=unit[tb1]
				if p then
					local size=#p
					while b<=size do
						local n=p[b]
						if id==n.id then
							return unit.id
						end
						b=b+1
					end
				end
			end
		end
	end
	_G.print("no data")
	return 0
end

function getProp_Ghostpos(tb,mapid,id,tb1)
	local t = _G[tb]
	if t then
		if mapid==0 then
		local i=_G.table.maxn(t)
		for a=1,i do
			b=1
			local unit=t[a]
			if unit then
				local p=unit[tb1]
				if p then
					local size=#p
					while b<=size do
						local n=p[b]
						if id==n.id then
							return n.posx,n.posy
						end
						b=b+1
					end
				end
			end
		end
		else
		local unit=t[mapid]
			if unit then
				local p=unit[tb1]
				if p then
					local size=#p
					while b<=size do
						local n=p[b]
						if id==n.id then
							return n.posx,n.posy
						end
						b=b+1
					end
				end
			end
		end

	--[[local i=_G.table.maxn(t)
		for a=1,i do
			b=1
			local unit=t[a]
			if unit then
				local p=unit[tb1]
				if p then
					local size=#p
					while b<=size do
						local n=p[b]
						if id==n.id then
							return n.posx,n.posy
						end
						b=b+1
					end
				end
			end
		end
		--]]
	end
	_G.print("no data")
	return 0,0
end


function getProp_MapConnCount(tb,id)
	local t = _G[tb]
	local count=0
	if t then
		local unit=t[id]
		if unit then
			local p=unit.portals
			if p then
				for i=1,_G.table.maxn(p) do
					if p[i]~=nil then
						count=count+1
					end
				end
				return count
			end
			_G.log.error("no portals count")
		end
		_G.log.error("no unit count")
	end
	_G.print("no data")
	return 0
end

function getProp_Map(tb,id,count)
	local t = _G[tb]
	local a=0
	if t then
		local unit=t[id]
		if unit then
			local p=unit.portals
			if p then
				for i=1,_G.table.maxn(p) do
					if p[i]~=nil then
						a=a+1
						if a==count then
							return p[i].id,p[i].srcx,p[i].srcy,p[i].tgtx,p[i].tgty
						end
					end
				end
			end
			_G.log.error("no portals data")
		end
		_G.log.error("no unit data")
	end
	_G.print("no data")
	return 0,0,0,0,0
end

function startSetId(tb)
	local t = _G[tb]
	if t then
		for k,v in _G.pairs(t) do
			setId(k)
		end
	end
	setIdEnd()
end

function getProp_merge(tb,id,sub_id,key1,key2)
	local t = _G[tb]
	local unit = t[id]
	local b=1
	if unit then
	   local size=#unit
		while b<=size do
			local n=unit[b]
			if n then
				if sub_id==b then
					return n[key1],n[key2]
				end
			end
			b=b+1
		end
	end
	_G.print("no data")
	return 0,0
end

function getProp_mergefindtgt(tb,typeid,tb_1,sid)
	-- 根据type确定区间
	local t = _G[tb]
	local t1 = _G[tb_1]
	local unit=t[typeid]
	for i=1,#unit do
		local m=unit[i].sid
		local n=t1[unit[i].sid]
		if n then
			local size=#n
			local b=1
			while b<=size do
				if n[b].id~=0 then
					if n[b].id==sid then
						return m
					end
				end
				b=b+1
			end
		end
	end
	return 0
end

function getProp_mergefindsrc(tb,typeid,sid)--判断该材料是否是当前类型
	-- 根据type确定区间
	local t = _G[tb]
	local unit=t[typeid]
	if unit then
		for i=1,#unit do
			if unit[i].sid==sid then
				return true
			end
		end
	end
	return false
end


function getProp_NPCfunc(tb,sid,tb_1,ntypeid,nfuncid)
	-- 根据type确定区间

	local t = _G[tb]
	local unit=t[sid]
	if unit then
		local eu=unit[tb_1]
		if eu then
			local size=#eu
			if size==0 then
				size=20
			end
			for i=1,size do
				if eu[i] then
					if eu[i].nfunc==nfuncid and eu[i].ntype==ntypeid then
						return eu[i].caption
					end
				end
			end
		end
	end
	return 0
end


function get_prop_tips(tb,id,tb_1,tb_1_id,tb_2)
	local t = _G[tb]
	local unit = t[id]
	if unit then
		local child = unit[tb_1]
		if child then
			local eu=child[tb_1_id]
			if eu then
				return eu[tb_2]
			end
		end
	end
	_G.print("no data")
	return 0
end

function get_prop_spider(sid)
	local eu = _G["gdItems"]
	local itemunit = eu[sid]
	local itemlvl =0
	local issuit =0
	if itemunit then
		issuit=itemunit["suite_id"]
		itemlvl=itemunit["req_level"]
	end

	local tbname
	if issuit==0 then
		tbname="gdSpiderParts"
	else
		tbname="gdSpiderPackages"
	end

	local t = _G[tbname]
	local allcnt = #t
	if allcnt<1 then
		_G.log.error("allcnt = ",allcnt)
		return 0
	end
	for i=1,allcnt do
		local unit = t[i]
		if unit then
			if itemlvl>=unit.minlvl and itemlvl<=unit.maxlvl then
				return unit.reqcnt
			end
		end
	end

	return 0
end


function getprop_getnearestPos(tb,id,mapid,num)
	local t = _G[tb]
	local unit = t[id]
	local x=0
	local y=0
	local distance=0
	if unit then
		local size=#unit
	    for i=1,size do
			local child=unit[i]
			if child and child.id==mapid then
				if distance~=0 then
					local newnum=child.posx*child.posx+child.posy*child.posy
					local newdistance=num-newnum
					if distance*distance>newdistance*newdistance then
						distance=newdistance
						x=child.posx
						y=child.posy
					end
				else
					local newnum=child.posx*child.posx+child.posy*child.posy
					distance=num-newnum
					x=child.posx
					y=child.posy
				end
			end
		end
	end
	_G.print("no data")
	return x,y
end






