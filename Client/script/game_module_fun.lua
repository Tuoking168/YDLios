
gdceapon = init_table_safely(gdceapon)

--------------------------------------------
--[[
>工具模块
--]]
gdceapon.pairs_by_keys = function(inTable)
	local temp = {}
	for k, v in pairs(inTable) do
		temp[#temp + 1] = k
	end

	local compare = function(a, b)
		if type(a) == type(b) then
			return a < b
		elseif type(a) == "number" then
			return true
		else
			return false
		end
	end

	table.sort(temp, compare)

	local i = 0
	return function()
		i = i + 1
		return temp[i], inTable[temp[i]]
	end
end

gdceapon.get_space_string = function(n)
	n = n or 0
	local space = ""
	for i = 1, n do
		space = space .. "	"
	end
	return space
end
-----------------------------------------------------

-----------------------------------------------------
--[[
>实现模块
--]]
gdceapon.write_table_head = function(tableName, inFile)
	if inFile then
		tableName = tableName or "gdTable"
		inFile:write(tableName .. " = init_table_safely(" .. tableName .. ")\n")
	end
end


gdceapon.write_table_body = function(tableName, inTable, inFile, deep)
	if inTable and inFile then
		tableName = tableName or "gdTable"
		deep = deep or 0

		local space = gdceapon.get_space_string(deep)

		-- head
		inFile:write(space .. tableName .. " = {\n")

		-- body
		local spaceEx = gdceapon.get_space_string(deep + 1)
		for k, v in gdceapon.pairs_by_keys(inTable) do
			if type(k) == "number" then
				k = "[" .. k .. "]"
			elseif type(k) == "string" and string.find(k, "%.") ~= nil then
				k = string.gsub(k, "%.", "_")
			end

			if type(v) == "table" then
				gdceapon.write_table_body(k, v, inFile, deep + 1)
			elseif type(v) == "string" then
				inFile:write(spaceEx .. k .. " = \"" .. v .. "\",\n")
			else
				inFile:write(spaceEx .. k .. " = " .. tostring(v) .. ",\n")
			end
		end

		-- tail
		if deep > 0 then
			inFile:write(space .. "},\n")
		else
			inFile:write(space .. "}\n")
		end
	end
end

gdceapon.write_table = function(tableName, inTable, filePath)
	local file = io.open(filePath, "w")

	gdceapon.write_table_head(tableName, file)
	gdceapon.write_table_body(tableName, inTable, file)

	file:close()
end
----------------------------------------------------------

----------------------------------------------------------
--[[
>接口模块
--]]

gdceapon.set_data = function(moduleName, key, value)
	if moduleName and key and value then
		gdceapon[moduleName] = init_table_safely(gdceapon[moduleName])
		local modu = gdceapon[moduleName]
		if type(key) == "string" and string.find(key, "%.") ~= nil then
			key = string.gsub(key, "%.", "_")
		end
		modu[key] = value
	end
end

gdceapon.get_data = function(moduleName, key)
	if moduleName and key then
		local modu = gdceapon[moduleName]
		if modu then
			if type(key) == "string" and string.find(key, "%.") ~= nil then
				key = string.gsub(key, "%.", "_")
			end
			return modu[key]
		end
	end
	return nil
end

gdceapon.get_size = function(moduleName)
	local n = 0
	local modu = gdceapon[moduleName]
	if type(modu) == "table" then
		for k, v in pairs(modu) do
			n = n + 1
		end
	end
	return n
end

gdceapon.load_module = function(moduleName)
	local code = "if type(" .. moduleName .. ") == \"table\" then\n"
	code = code .. "gdceapon." .. moduleName .. " = " .. moduleName .. "\n"
	code = code .. "end"

	local fun = loadstring(code)
	if fun then
		fun()
	end
end

gdceapon.save_module = function(moduleName, filePath)
	gdceapon.write_table(moduleName, gdceapon[moduleName], filePath)
end

gdceapon.clear_module = function(moduleName)
	gdceapon[moduleName] = nil
end

gdceapon.clear_all = function()
	gdceapon = nil
end

--
-- sub module
--
gdceapon.set_sub_data = function(moduleName, subModuleName, id, key, value)
	if moduleName and subModuleName and id and key and value then
		if type(id) == "string" then
			id = string.gsub(id, "%.", "_")
		end
		if type(key) == "string" then
			key = string.gsub(key, "%.", "_")
		end
		local subModu = gdceapon.get_data(moduleName, subModuleName)
		subModu = init_table_safely(subModu)
		local idModu = subModu[id]
		idModu = init_table_safely(idModu)
		idModu[key] = value

		subModu[id] = idModu
		gdceapon.set_data(moduleName, subModuleName, subModu)
	end
end

gdceapon.get_sub_data = function(moduleName, subModuleName, id, key)
	if moduleName and subModuleName and id and key then
		if type(id) == "string" then
			id = string.gsub(id, "%.", "_")
		end
		if type(key) == "string" then
			key = string.gsub(key, "%.", "_")
		end
		local subModu = gdceapon.get_data(moduleName, subModuleName)
		if type(subModu) == "table" then
			local idModu = subModu[id]
			if type(idModu) == "table" then
				return idModu[key]
			end
		end
	end
	return nil
end

gdceapon.get_sub_size = function(moduleName, subModuleName)
	local n = 0
	if moduleName and subModuleName then
		local subModu = gdceapon.get_data(moduleName, subModuleName)
		if type(subModu) == "table" then
			for k, v in pairs(subModu) do
				n = n + 1
			end
		end
	end
	return n
end

gdceapon.get_sub_id_vector = function(moduleName, subModuleName)
	local ret = ""
	if moduleName and subModuleName then
		local subModu = gdceapon.get_data(moduleName, subModuleName)
		if type(subModu) == "table" then
			for k, v in gdceapon.pairs_by_keys(subModu) do
				ret = ret .. k .. "|"
			end
		end
	end
	return ret
end

gdceapon.clear_sub_data = function(moduleName, subModuleName, id)
	if moduleName and subModuleName then
		local subModu = gdceapon.get_data(moduleName, subModuleName)
		if type(subModu) == "table" then
			subModu[id] = nil
		end
	end
end

gdceapon.clear_sub_all = function(moduleName, subModuleName)
	local modu = gdceapon[moduleName]
	if type(modu) == "table" then
		modu[subModuleName] = nil
	end
end

gdceapon.event_listener_in_lua = init_table_safely(gdceapon.event_listener_in_lua)
gdceapon.dispatcher_event = function(eventName)
	local listener = gdceapon.event_listener_in_lua
	if listener then
		local func = listener.on_cp_event
		if type(func) == "function" then
			func(eventName)
		end
	end
end






















