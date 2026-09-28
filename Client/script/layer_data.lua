local _G=_G

module("layer_data")

local NodeUnitName=
{
	[12]="NodePetDesc",
}
function get_node_unit_name(id)
	return NodeUnitName[id] or ""
end
