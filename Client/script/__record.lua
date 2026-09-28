require 'string'
require 'table'

--
-- a customized compare function for sorting table that to be ouputed
--
function compare_func(a, b, w_tbl)
	w_tbl = w_tbl or {}
	w_tbl.id = w_tbl.id or -999
	w_tbl.name = w_tbl.name or -998

	local va = a
	local vb = b
	if type(a) ~= "number" then
		va = w_tbl[a] or 0
	end
	if type(b) ~= "number" then
		vb = w_tbl[b] or 0
	end

	if va == vb then
		return a<b
	else
		return va<vb
	end
end

--
--	output a table to file in a cutomized format
--	talbe:t
--	file:f
--
function output_table(t, f, tabs, comma, w_tbl)
	if not (type(t)=="table") then
		print("Invalid table to output!")
		return
	end

	tabs = tabs or ""
	local connector = ""
	local k_tbl = {}
	local has_tbl = false
	for k, v in pairs(t) do
		table.insert(k_tbl, k)
		if type(v)=="table" then
			has_tbl = true
		end
	end

	table.sort(k_tbl, function (a,b) return compare_func(a, b, w_tbl) end )

	--
	--	Note that:	getn is only for table with numberic index
	--			not available for table with string index
	--	so we use getn(k_tbl) instead of getn(t), as we know that
	--	k_tbl and t has the same number of k-v pairs
	if table.getn(k_tbl)<12 and not has_tbl then
		connector = ""
		tabs = ""
	else
		connector = "\n"
		tabs = tabs .. "	"
	end

	f:write("{" .. connector)
	for _, k in ipairs(k_tbl) do
		local v = t[k]

		if type(k)=="number" then
			k = "[" .. k .. "]"
		end
		local tv = type(v)
		if tv=="table" then
			f:write(tabs, k, "= ")
			output_table(v, f, tabs .. "	", true)
		elseif tv=="string" then
			if v:sub(1,1)=="\"" and v:sub(-1)=="" then
				f:write(tabs, k, "=", v, ","..connector)
			else
				f:write(tabs, k, "=", "\""..v.."\","..connector)
			end
		elseif tv=="boolean" then
			f:write(tabs, k, "=", tostring(v), ","..connector)
		else
			f:write(tabs, k, "=", v or 0, ","..connector)
		end
	end
	if not (tabs=="")then
		tabs = tabs:sub(1,-2)
	end
	if comma then
		f:write(tabs .. "},\n")
	else
		f:write(tabs .. "}\n")
	end
end

record = {}

msgusingsize = {}
msgusingsize._size = 0
msgusingsize._begintime = os.time()
msgusingsize._cnt = 0

function record.saveRecord()
	local use_time = os.time() - msgusingsize._begintime
--	local sizeperminute = msgusingsize._size / (msgusingsize._time / 60) / 1024
	local sizeall = msgusingsize._size
	local cntall = msgusingsize._cnt



	local cnt = 0
	local cntmaxmsg = ""
	local size = 0
	local sizemaxmsg = ""
	for k,v in pairs(msgusingsize) do
		print(k)
		if type(v) == "table" then
			if v.cnt and v.cnt > cnt then
				cnt = v.cnt
				cntmaxmsg = v.name
			end
			if v.size and v.size > size then
				size = v.size
				sizemaxmsg = v.name
			end
		end
	end
	msgusingsize = {}
	msgusingsize._begintime = os.time()
	msgusingsize._size = 0
	msgusingsize._cnt = 0

	local url = "http://42.120.51.226/fire-gm/test/traffic"
	url = url.."?recordtime="..use_time.."&sizeall="..sizeall.."&cntall="..cntall
	url = url.."&maxsizemsgname="..sizemaxmsg.."&size="..size.."&maxcntmsgname="..cntmaxmsg.."&cnt="..cnt

	return url
--	local of_lvl = io.open("msgusingsize.lua", "w")
--	if not of_lvl then
--		print("Failed to open output file: msgusingsize.lua")
--	else
--		of_lvl:write([[
--if not (type(msgusingsize)=="table") then
--	msgusingsize = {}
--end

--msgusingsize =]])
--		output_table(msgusingsize, of_lvl)
--	end
--	of_lvl:close()
end

function record.msgsizerecord(name,size)
	local msg = msgusingsize[name]
	if not msg then
		msgusingsize[name] = {}
		msg = msgusingsize[name]
		msg.cnt = 1
		msg.size = size
		msg.name = name
	else
		msg.cnt = msg.cnt + 1
		msg.size = msg.size + size
	end
	msgusingsize._size = msgusingsize._size + size
	msgusingsize._cnt = msgusingsize._cnt + 1
end
