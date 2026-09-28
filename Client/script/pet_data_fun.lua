local _G=_G

module("pet_data_fun")
local NodePetSkill=
{
	[0]={res="data-a/ui/ui_pet/pet_pickup_skill.png",name="Ê°È¡"},
	[1]={res="data-a/ui/ui_pet/pet_bag_skill.png"	,name="±³°ü"},
	[2]={res="data-a/ui/ui_pet/pet_flag.png"		,name="°ÚÌ¯"},
}
function get_pet_skill(id,key)
	local unit=NodePetSkill[id]
	if unit then
		return unit[key] or ""
	end
	return ""
end

function get_all_pet_skill()
	for k, v in _G.pairs(NodePetSkill) do
		addPetSkill(k,v.res,v.name)
	end
end
