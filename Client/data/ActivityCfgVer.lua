-- 管理所有活动的配置数据版本号,
-- 修改完活动配置后,将本表的对应的活动的IsChanged字段改为1,然后执行do_activitycfgdatapatch.lua
-- 就可以生成最新的patch文件
if not tActivityCfgVer then
	tActivityCfgVer = {}
end

-- ID = openID或其它什么意思
-- Name = 活动名字,对应combinedserver_data.lua里的活动描述文本,不能乱改
tActivityCfgVer =
	{
	[20404]= {ID=20404,IsChanged=0,Name="每日回馈",Ver=1,},
	[20405]= {ID=20405,IsChanged=0,Name="强化回馈",Ver=1,},
	[20406]= {ID=20406,IsChanged=0,Name="宠物回馈",Ver=1,},
	[20407]= {ID=20407,IsChanged=0,Name="魂石回馈",Ver=1,},
	[20408]= {ID=20408,IsChanged=0,Name="翅膀回馈",Ver=1,},
	[20409]= {ID=20409,IsChanged=0,Name="寻宝回馈",Ver=1,},
	[20410]= {ID=20410,IsChanged=0,Name="时装回馈",Ver=1,},
	[20411]= {ID=20411,IsChanged=0,Name="幻武回馈",Ver=1,},
	[20412]= {ID=20412,IsChanged=0,Name="元宝回馈",Ver=1,},
	[20413]= {ID=20413,IsChanged=0,Name="累计充值",Ver=1,},
	[20414]= {ID=20414,IsChanged=0,Name="重复充值",Ver=1,},
	[20415]= {ID=20415,IsChanged=0,Name="单笔充值",Ver=1,},
	[20416]= {ID=20416,IsChanged=0,Name="活动首充",Ver=1,},
	[20417]= {ID=20417,IsChanged=0,Name="幸运大转盘",Ver=1,},
	[20418]= {ID=20418,IsChanged=0,Name="马上抢购",Ver=3,},
	[20419]= {ID=20419,IsChanged=0,Name="疯狂抢购",Ver=3,},
}

tActivityCfgVer["GetActivityCfgVer"] = function (ID)
	if tActivityCfgVer[ID] then
		return tActivityCfgVer[ID].Ver
	else
		return 1
	end
end
