if not (type(AreaChecker)=="table") then
	AreaChecker = {}
end


function AreaChecker.getAreaCnt()
	return #gdAreaToMap
end


function AreaChecker.getPointCnt(id)
	local area = gdAreaToMap[id]
	if area then
		return #area.point
	end
	print("Area Checker Unknow id = "..id)
	return 0
end


function AreaChecker.getPoint(id, pointid)
	local area = gdAreaToMap[id]
	if area then
		local point = area.point[pointid]
		return point.x,point.y
	end
end

function AreaChecker.getType(id)
	local area = gdAreaToMap[id]
	if area then
		return area.type
	end
end

function AreaChecker.isinArea(id,x,y)
	local isin = false
	local areadata = gdAreaToMap[id]
	if areadata then
		for i,j in ipairs (areadata.point) do
			local p1 = j;
			local p2 = areadata.point[i + 1]
			if not p2 then
				p2 = areadata.point[1]
			end
			if p1.x == x and p1.y == y then
				isin = true
				break
			end
			if (p1.x ~= p2.x ) then
				local k =  (p2.y- p1.y)/(p2.x-p1.x);
				local b =  (p2.y*p1.x - p2.x*p1.y)/(p1.x-p2.x)
				local ly = 0
				local hy = 0
				if (p1.y > p2.y) then
					ly = p2.y
					hy = p1.y
				else
					ly = p1.y
					hy = p2.y
				end
				if (y > ly and y <= hy) then
					local dx = (y - b)/ k
					if (dx >= x) then
						isin = not isin
					end
				end
			else
				local ly = 0
				local hy = 0
				if (p1.y > p2.y) then
					ly = p2.y
					hy = p1.y
				else
					ly = p1.y
					hy = p2.y
				end
				if (y > ly and y <= hy) then
					if (p1.x >= x) then
						isin = not isin
					end
				end
			end
		end
	end
	return isin
end

