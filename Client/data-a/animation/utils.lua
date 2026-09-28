function load_points_from_physical(filename)
	local file = io.open(filename, "r")
	if not file then
		print("Failed to load phyical, invalid sprite file: ", filename)
		return
	end

	local source = file:read("*all")
	if not source then
		print("Failed to load phyical, not data: ", filename)
		return
	end
	file:close()
	local sizex, sizey

	_, _, sizex, sizey = source:find([[MAP_SIZE%s+(%d+)%s+(%d+)]])
	if not sizex or not sizey then
		print("Failed to load phyical, not map size: ", filename)
		return
	end
	sizex = tonumber(sizex)
	sizey = tonumber(sizey)
	--print(sizex, sizey)

	_,_, source = source:find([[MAP_TILES(.-)MAP_FLAGS]])
	if not source then
		print("Failed to load phyical, not data: ", filename)
		return
	end
	local res = {}
	local tbl = {
		["00010000"] = 1,
		["00020000"] = 2,
		["00030000"] = 3,
		["00040000"] = 4,
		["00050000"] = 5,
		["00060000"] = 6,
		["00070000"] = 7,
		["00080000"] = 8,
		["00090000"] = 9,
	}

	local x ,y = 0, 0
	for mapitem in source:gfind([[%w+]]) do
		local seq = tbl[mapitem]
		if seq then
			res[seq] = {x=x, y=y}
		end
		x = x + 1
		if x>=sizex then
			x = 0
			y = y + 1
		end
	end

	print("success to parse phyical layer: ", filename)

	return res, sizex, sizey
end


