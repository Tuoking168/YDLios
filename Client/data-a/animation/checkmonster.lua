require 'lfs'

dofile("../data/monster_data.lua")

usage = {}

for k, m in pairs(gdMonsters) do
	local data = usage[m.anim]
	if data then
		data.used = data.used + 1
	else
		usage[m.anim] = { used = 1, size = 0 }
	end
end

for filename in lfs.dir("./cloth") do
	local a, b, c, d = filename:find("(g_%d+)_(%d).png")
	if a then
		local data = usage[c]
		if data then
			--print(filename, a, b, c, d)filename
			filename = "./cloth/"..filename
			local attr = lfs.attributes(filename)
			if attr then
				data.size = data.size or 0
				data.size = data.size + attr.size
			else
				print(filename , "no attrbutes")
			end
		else
			print("file not used in monster: ", filename, c)
		end
	end
end

print("##########################################")

local result = {}

for k, v in pairs(usage) do
	table.insert(result, {name = k, used = v.used, size = v.size})
end

table.sort(result, function(v1, v2)
	if v1.name<v2.name then
		return true
	else
		return false
	end
end)

for k, v in pairs(result) do
	print(v.name, v.used, v.size)
end




