require('LuaXml')
require('engine')
require('utils')

local dir_table =
{
	"./cloth/",
	"./weapon/",
	"./yuanshen/",
	"./effect/",
	"./pet/",
	
}

function get_dir_file(dirpath,func)
	for _,v in ipairs(dir_table) do
		local cmd = 'dir "'..v..'" /b'
		local popen = io.popen(cmd)
		for filename in popen:lines() do
			if string.sub(filename,-6,-1) == ".plist" then
				func(v,filename)
			end
		end
		print(">" .. v)
	end
end

local base = _G
local xml = xml

function cnt(var, tag, attributeKey,attributeValue)
  -- check input:
  if base.type(var)~="table" then return end
  if base.type(tag)=="string" and #tag==0 then tag=nil end
  if base.type(attributeKey)~="string" or #attributeKey==0 then attributeKey=nil end
  if base.type(attributeValue)=="string" and #attributeValue==0 then attributeValue=nil end
  local count = 0
  -- compare this table:
  for k,v in pairs(var) do
	--print(k,v)
	if tag~=nil then
		if v[0]==tag and ( attributeValue == nil or var[attributeKey]==attributeValue ) then
			base.setmetatable(var,{__index=xml, __tostring=xml.str})
			count = count + 1
		end
	else
		if attributeValue == nil or var[attributeKey]==attributeValue then
			base.setmetatable(var,{__index=xml, __tostring=xml.str})
			count = count + 1
		end
	end
  end
  return count
end

animframes = {}

function checkplistframe(dirname,name)
	local url = dirname.."/"..name
	local xfile = xml.load(url)
	local xframes = xfile:find("dict")
	local xframes = xframes[2]
	local c = cnt(xframes,"key")
	animframes[string.sub(name,0,-7)] = c
end


get_dir_file('.',checkplistframe)

local of_lvl = io.open("..\\animframes_data.lua", "w")
of_lvl:write([[animframes = ]])
output_table(animframes , of_lvl, nil, nil, weight_tbl)
