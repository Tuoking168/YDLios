local _G=_G

module("minimap")
local print = _G.log.info

function ordered_pairs(t)
	local lt = {}
	for k,v in _G.pairs(t) do
		local i = #lt+1
		lt[i] = {}
		lt[i].k=k
		lt[i].v=v
	end
	_G.table.sort(lt,function(a,b) return a.k<b.k end)
	local i = 0
	local function it()
		i = i + 1
		local x = lt[i]
		if x then
			return x.k,x.v
		end
	end
	return it
end

function getMapList()
	local t = _G.gdMaps
	if t then
		for k,v in ordered_pairs(t) do
			setMapInfo(k,v.name,v.resource)
		end
	end
end

function getMapIconList()
	local t = _G.gdWorldMap
	if t then
		for k,v in ordered_pairs(t) do
			setMapIcon(k,v.name,v.btn,v.x,v.y)
		end
	end
end

function getMapPortals()
	local t = _G.gdMaps
	--[[
	if t then
		for i,map in _G.pairs(t) do
			local portals = map.portals
			if portals then
				for k,v in _G.pairs(portals) do
					print(i,v.id,v.srcx,v.srcy,v.tgtx,v.tgty)
				end
			end
		end
	end
	--]]
	if t then
		for i,map in _G.pairs(t) do
			local portals = map.portals
			if portals then
				for k,v in _G.pairs(portals) do
					local name = _G.gdMaps[v.id].name
					setMapPortal(k,i,v.id,v.srcx,v.srcy,v.tgtx,v.tgty,name)
				end
			end
		end
	end
end

function getNPCList(mapid)
	local t = _G.gdMaps[mapid]
	--[[
	if t then
		local st = t.npcs
		if st then
			for k,v in ordered_pairs(st) do
				print(v.id, _G.gdNPC[v.id].name,v.posx,v.posy)
			end
		end
	end
	--]]
	if t then
		local st = t.npcs
		if st then
			for k,v in ordered_pairs(st) do
				setNPCInfo(v.id, _G.gdNPC[v.id].name, v.posx,v.posy)
			end
		end
	end
end

