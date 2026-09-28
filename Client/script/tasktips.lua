local _G=_G
module("tasktips")

local notColor=
{
	[0]={r=255	,g=0	,b=0	,},--Red
	[1]={r=0	,g=0	,b=255	,},--BLUE
	[2]={r=0	,g=255	,b=0	,},--Green
	[3]={r=255	,g=255	,b=255	,},--White
}

local notfontsize=
{
	[0]={s=14	,},
	[1]={s=14	,},
	[2]={s=12	,},
	[3]={s=12	,},
}

function get_tasktips_color(id)
	local c=notColor[id]
	if c then
		return c.r,c.g,c.b
	end
	return 255,255,255
end

function get_tasktips_fontsize(id)
	local c=notfontsize[id]
	if c then
		return c.s
	end
	return 50
end	