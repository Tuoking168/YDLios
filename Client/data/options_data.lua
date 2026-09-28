if not (type(gdActivityOptions)=="table") then
	gdActivityOptions = {}
end

gdActivityOptions =
{
	[1]= {
			id=1,
			name="投资计划",
			ctrlid=0,
			elems= {},
			owner=0,
			res="label_btn_huodong_touzijihua",
		},
}
if not (type(gdWelfareOptions)=="table") then
	gdWelfareOptions = {}
end

gdWelfareOptions =
{
	[1]= {
			id=1,
			name="首充礼包",
			ctrlid=20101,
			elems= {},
			owner=0,
			res="label_btn_shouchonglibao",
			tag=0,
		},
	[2]= {
			id=2,
			name="每日首充",
			ctrlid=20102,
			elems= {},
			owner=0,
			res="label_btn_meirishouchong",
			tag=1,
		},
	[3]= {
			id=3,
			name="累计充值",
			ctrlid=20103,
			elems= {},
			owner=0,
			res="label_btn_leijichongzhi",
			tag=2,
		},
	[4]= {
			id=4,
			name="在线奖励",
			ctrlid=20104,
			elems= {},
			owner=0,
			res="label_btn_libao_zaixianjiangli",
			tag=5,
		},
	[5]= {
			id=5,
			name="单笔充值",
			ctrlid=20105,
			elems= {},
			owner=0,
			res="label_btn_huodong_danbichongzhi",
			tag=7,
		},
}
if not (type(gdSportsOptions)=="table") then
	gdSportsOptions = {}
end

gdSportsOptions =
{
	[1]= {
			id=1,
			name="开服竞技",
			ctrlid=20301,
			elems= {},
			owner=0,
			res="label_btn_huodong_kaifujingji",
		},
}
if not (type(gdCombinedSvrOptions)=="table") then
	gdCombinedSvrOptions = {}
end

gdCombinedSvrOptions =
{
	[1]= {
			id=1,
			name="充值大回馈",
			ctrlid=0,
			elems= {},
			owner=0,
			res="label_btn_czhk_chongzhidahuikui",
			tag=1,
		},
	[2]= {
			id=2,
			name="充值大比拼",
			ctrlid=0,
			elems= {},
			owner=0,
			res="label_btn_czhk_chongzhidabiping",
			tag=2,
		},
	[3]= {
			id=3,
			name="等级大比拼",
			ctrlid=0,
			elems= {},
			owner=0,
			res="label_btn_czhk_dengjidabiping",
			tag=3,
		},
	[4]= {
			id=4,
			name="战力大比拼",
			ctrlid=0,
			elems= {},
			owner=0,
			res="label_btn_czhk_zhanlidabiping",
			tag=4,
		},
	[5]= {
			id=5,
			name="英雄城争霸",
			ctrlid=0,
			elems= {},
			owner=0,
			res="label_btn_czhk_shachengzhengba",
			tag=5,
		},
	[6]= {
			id=6,
			name="神秘商店",
			ctrlid=0,
			elems= {},
			owner=0,
			res="label_btn_czhk_shenmishangdian",
			tag=6,
		},
}
if not (type(gdCombinedSvrOptions2)=="table") then
	gdCombinedSvrOptions2 = {}
end

gdCombinedSvrOptions2 =
{
	[1]= {
			id=1,
			name="活动首冲",
			ctrlid=20416,
			elems= {},
			owner=0,
			res="label_btn_huodong_hongdongchongzhi",
			tag=1,
		},
	[2]= {
			id=2,
			name="累计充值",
			ctrlid=20413,
			elems= {},
			owner=0,
			res="label_btn_huodong_leijichongzhi",
			tag=2,
		},
	[3]= {
			id=3,
			name="重复充值",
			ctrlid=20414,
			elems= {},
			owner=0,
			res="label_btn_huodong_chongfuchongzhi",
			tag=3,
		},
	[4]= {
			id=4,
			name="单笔充值",
			ctrlid=20415,
			elems= {},
			owner=0,
			res="label_btn_huodong_danbichongzhi",
			tag=4,
		},
	[5]= {
			id=5,
			name="活动商店",
			ctrlid=20402,
			elems= {},
			owner=0,
			res="label_btn_huodong_huodongshangdian",
			tag=5,
		},
	[6]= {
			id=6,
			name="兑换商店",
			ctrlid=20403,
			elems= {},
			owner=0,
			res="label_btn_huodong_duihuanshangdian",
			tag=6,
		},
	[7]= {
			id=7,
			name="每日回馈",
			ctrlid=20404,
			elems= {},
			owner=0,
			res="label_btn_huodong_meirihuikui",
			tag=7,
		},
	[8]= {
			id=8,
			name="元宝回馈",
			ctrlid=20412,
			elems= {},
			owner=0,
			res="label_btn_huodong_yuanbaohuikui",
			tag=8,
		},
	[9]= {
			id=9,
			name="宠物回馈",
			ctrlid=20406,
			elems= {},
			owner=0,
			res="label_btn_huodong_chongwuhuikui",
			tag=9,
		},
	[10]= {
			id=10,
			name="魂石回馈",
			ctrlid=20407,
			elems= {},
			owner=0,
			res="label_btn_huodong_hunshihuikui",
			tag=10,
		},
	[11]= {
			id=11,
			name="翅膀回馈",
			ctrlid=20408,
			elems= {},
			owner=0,
			res="label_btn_huodong_chibanghuikui",
			tag=11,
		},
	[12]= {
			id=12,
			name="寻宝回馈",
			ctrlid=20409,
			elems= {},
			owner=0,
			res="label_btn_huodong_xunbaohuikui",
			tag=12,
		},
	[13]= {
			id=13,
			name="时装回馈",
			ctrlid=20410,
			elems= {},
			owner=0,
			res="label_btn_huodong_shizhuanghuikui",
			tag=13,
		},
	[14]= {
			id=14,
			name="幻武回馈",
			ctrlid=20411,
			elems= {},
			owner=0,
			res="label_btn_huodong_huanwuhuikui",
			tag=14,
		},
	[15]= {
			id=15,
			name="强化回馈",
			ctrlid=20405,
			elems= {},
			owner=0,
			res="label_btn_huodong_qianghuahuikui",
			tag=15,
		},
	[16]= {
			id=16,
			name="马上抢购",
			ctrlid=20418,
			elems= {},
			owner=0,
			res="label_btn_huodong_mashangqianggou",
			tag=16,
		},
	[17]= {
			id=17,
			name="疯狂抢购",
			ctrlid=20419,
			elems= {},
			owner=0,
			res="label_btn_huodong_fengkuangqianggou",
			tag=17,
		},
}
