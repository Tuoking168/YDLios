if not (type(gdTips)=="table") then
	gdTips = {}
end

 gdTips[1] = {
	id=1,
	button= {
			[1]= {name="同意",},
			[2]= {name="拒绝",},
		},
	content="%s请求与您交易",
	select= {},
	title="交易请求",
}
gdTips[2] = {
	id=2,
	button= {
			[1]= {name="确定",},
		},
	content="%s拒绝与您交易",
	select= {},
	title="交易结果",
}
gdTips[3] = {
	id=3,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否与%s中断交易",
	select= {},
	title="交易操作",
}
gdTips[4] = {
	id=4,
	button= {
			[1]= {name="确定",},
		},
	content="交易失败",
	select= {},
	title="交易结果",
}
gdTips[5] = {
	id=5,
	button= {
			[1]= {name="确定",},
		},
	content="交易成功",
	select= {},
	title="交易结果",
}
gdTips[6] = {
	id=6,
	button= {
			[1]= {name="前往设置",},
			[2]= {name="取消",},
		},
	content="宠物可以帮您拾取金币",
	select= {},
	title="拾取金钱",
}
gdTips[7] = {
	id=7,
	button= {
			[1]= {name="前往设置",},
			[2]= {name="取消",},
		},
	content="宠物2级之后可以帮您拾取物品，可在系统设置界面设置详细的拾取选项。",
	select= {},
	title="拾取物品",
}
gdTips[8] = {
	id=8,
	button= {
			[1]= {name="开始摆摊",},
		},
	content="宠物10级之后可以开启摆摊，共有5个格子，40级可以开启高级摆摊。宠物等级越高可离线摆摊时间越长。",
	select= {},
	title="摆摊",
}
gdTips[9] = {
	id=9,
	button= {
			[1]= {name="开始摆摊",},
		},
	content="宠物40级可以开启高级摆摊，共有10个格子。宠物等级越高可离线摆摊时间越长。",
	select= {},
	title="高级摆摊",
}
gdTips[10] = {
	id=10,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="你确定要删除这个角色吗？",
	select= {},
	title="角色删除",
}
gdTips[11] = {
	id=11,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="你确定要丢弃这个物品吗？",
	select= {},
	title="物品丢弃",
}
gdTips[12] = {
	id=12,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否使用召唤兽灵魄或%s元宝使召唤兽直接升至满级？",
	select= {},
	title="召唤兽升级",
}
gdTips[13] = {
	id=13,
	button= {
			[1]= {name="是",},
			[2]= {name="否",},
		},
	content="是否花费%s元宝或一个续命丹原地复活？（优先使用续命丹）",
	select= {},
	title="原地复活",
}
gdTips[14] = {
	id=14,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否清洗当前鉴定属性？",
	select= {},
	title="是否清洗",
}
gdTips[15] = {
	id=15,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="背包中飞鞋数量不足，是否前往商城购买飞鞋？",
	select= {
			[1]= {str="不显示",},
		},
	title="购买飞鞋",
}
gdTips[16] = {
	id=16,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您将花费10元宝对宠物进行培养，若背包中有宠物项圈则优先使用宠物项圈；元宝培养每次增加30点成长值。",
	select= {
			[1]= {str="不再显示",},
		},
	title="元宝培养",
}
gdTips[17] = {
	id=17,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您将花费1000荣誉对宠物进行培养；荣誉培养每次增加10点成长值。",
	select= {
			[1]= {str="不再显示",},
		},
	title="荣誉培养",
}
gdTips[18] = {
	id=18,
	button= {
			[1]= {name="购买",},
			[2]= {name="取消",},
		},
	content="是否花费%s元宝来购买%s？",
	select= {},
	title="确认购买",
}
gdTips[19] = {
	id=19,
	button= {
			[1]= {name="充值",},
			[2]= {name="取消",},
		},
	content="您的背包没有续命丹或者%s元宝，是否充值？",
	select= {},
	title="续命丹不足",
}
gdTips[20] = {
	id=20,
	button= {
			[1]= {name="充值",},
		},
	content="您的元宝不足，点击充值",
	select= {},
	title="元宝不足",
}
gdTips[21] = {
	id=21,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="%s邀请你组队，是否同意组队？",
	select= {},
	title="邀请组队",
}
gdTips[22] = {
	id=22,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="%s已有队伍，是否加入该队伍？",
	select= {},
	title="已有队伍",
}
gdTips[23] = {
	id=23,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="%s要求入队，是否同意其加入该队伍？",
	select= {},
	title="申请组队",
}
gdTips[24] = {
	id=24,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否消耗%s元宝封印该宠物，封印后的宠物蛋可以交易",
	select= {},
	title="宠物封印",
}
gdTips[25] = {
	id=25,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="你确定要退出行会吗？",
	select= {},
	title="退出行会",
}
gdTips[26] = {
	id=26,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="你确定将行会首领之位禅让给%s吗？",
	select= {},
	title="禅让首领",
}
gdTips[27] = {
	id=27,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="你确定将%s踢出行会吗？",
	select= {},
	title="踢除成员",
}
gdTips[28] = {
	id=28,
	button= {
			[1]= {name="确定",},
		},
	content="%s正在与他人进行交易",
	select= {},
	title="交易回复",
}
gdTips[29] = {
	id=29,
	button= {
			[1]= {name="确定",},
		},
	content="%s并未响应您的交易请求",
	select= {},
	title="交易回复",
}
gdTips[30] = {
	id=30,
	button= {
			[1]= {name="确定",},
		},
	content="当前不允许交易",
	select= {},
	title="交易回复",
}
gdTips[31] = {
	id=31,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="%s邀请你进入行会：%s，是否同意？",
	select= {},
	title="邀请入会",
}
gdTips[32] = {
	id=32,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s元宝，增加挑战次数？",
	select= {
			[1]= {str="不再提示",},
		},
	title="购买次数",
}
gdTips[33] = {
	id=33,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s元宝，刷新竞技BUFF？",
	select= {
			[1]= {str="不再提示",},
		},
	title="元宝刷新",
}
gdTips[34] = {
	id=34,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s元宝，一键天军？",
	select= {
			[1]= {str="不再提示",},
		},
	title="一键天军",
}
gdTips[35] = {
	id=35,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s元宝，清除冷却时间？",
	select= {
			[1]= {str="不再提示",},
		},
	title="清除冷却",
}
gdTips[36] = {
	id=36,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s元宝，增加上香次数？",
	select= {
			[1]= {str="不再提示",},
		},
	title="购买次数",
}
gdTips[37] = {
	id=37,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您是否要现在进入副本？",
	select= {},
	title="队伍集结",
}
gdTips[38] = {
	id=38,
	button= {
			[1]= {name="确定",},
		},
	content="您已经被行会请离。",
	select= {},
	title="行会通知",
}
gdTips[39] = {
	id=39,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s仙玉/元宝（优先使用仙玉），刷新奖励倍率？",
	select= {
			[1]= {str="不再提示",},
		},
	title="刷新倍率",
}
gdTips[40] = {
	id=40,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s元宝，增加膜拜/鄙视次数？",
	select= {
			[1]= {str="不再提示",},
		},
	title="购买次数",
}
gdTips[41] = {
	id=41,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="每次消耗一个任务完成符，是否立即完成",
	select= {},
	title="任务立即完成",
}
gdTips[42] = {
	id=42,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否使用3仙玉/元宝，消除冷却时间?\n（优先使用仙玉）",
	select= {},
	title="消除等待时间",
}
gdTips[43] = {
	id=43,
	button= {
			[1]= {name="立即修理",},
			[2]= {name="前往修理",},
		},
	content="您的装备耐久不足或已损坏，请立即修理。",
	select= {},
	title="装备耐久不足",
}
gdTips[44] = {
	id=44,
	button= {
			[1]= {name="确定",},
		},
	content="您的仙玉不足，购买取消",
	select= {},
	title="仙玉不足",
}
gdTips[45] = {
	id=45,
	button= {
			[1]= {name="确定",},
		},
	content="您的积分不足，购买取消",
	select= {},
	title="积分不足",
}
gdTips[46] = {
	id=46,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您现在需要寻找转生NPC进行转生么？",
	select= {},
	title="转生指引",
}
gdTips[47] = {
	id=47,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="你确定要消耗行会资金：%s元来开启%s吗?效果持续：%s分钟",
	select= {
			[1]= {str="不再提示",},
		},
	title="开启光环",
}
gdTips[48] = {
	id=48,
	button= {
			[1]= {name="同意",},
			[2]= {name="取消",},
		},
	content="%s使用了行会集结令，您是否同意传送致他的旁边",
	select= {},
	title="行会召集",
}
gdTips[49] = {
	id=49,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否重置财神闯关？\n(重置后将回到起始点)",
	select= {},
	title="重置闯关",
}
gdTips[50] = {
	id=50,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您要退出这个场景吗？",
	select= {},
	title="退出场景",
}
gdTips[51] = {
	id=51,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s礼券，刷新美女？",
	select= {
			[1]= {str="不再提示",},
		},
	title="刷新美女",
}
gdTips[52] = {
	id=52,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费%s礼券/元宝，增加闯关次数？\n(优先消耗礼券)",
	select= {
			[1]= {str="不再提示",},
		},
	title="购买次数",
}
gdTips[53] = {
	id=53,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="背包中追踪令数量不足，是否前往商城购买？",
	select= {},
	title="购买追踪令",
}
gdTips[54] = {
	id=54,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费一定数量元宝，提升宠物等级1级？",
	select= {},
	title="一键升级",
}
gdTips[55] = {
	id=55,
	button= {},
	content="1转时可获得被吞噬宠物的 60% 基础属性\n2转时可获得被吞噬宠物的 50% 基础属性\n3转时可获得被吞噬宠物的 40% 基础属性\n4转时可获得被吞噬宠物的 30% 基础属性\n5转及5转以后时可获得被吞噬宠物的 20% 基础属性\n进阶属性和极品属性不会获得，被吞噬宠物消失",
	select= {},
	title="120级可转生",
}
gdTips[56] = {
	id=56,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="确定要花费%s购买%s元宝吗？",
	select= {},
	title=0,
}
gdTips[57] = {
	id=57,
	button= {
			[1]= {name="注册帐号",},
			[2]= {name="继续试玩",},
		},
	content="将以试玩帐号进入游戏，为确保安全，请尽快升级为正式帐号。\n升级操作可在游戏内系统下的帐号信息里设置。\n ===如果不绑定帐号，删除客户端后，数据可能会丢失===",
	select= {},
	title="Tips提醒",
}
gdTips[58] = {
	id=58,
	button= {
			[1]= {name="绑定试玩帐号",},
			[2]= {name="继续登陆",},
		},
	content="发现您有未绑定的试玩帐号，如果继续使用当前帐号登陆，试玩帐号数据将被抹掉，建议先绑定试玩帐号，以免造成不必要的损失。",
	select= {},
	title=0,
}
gdTips[59] = {
	id=59,
	button= {
			[1]= {name="确定",},
		},
	content="已经成功为您将试玩帐号与%s进行绑定，请牢记帐号密码。",
	select= {},
	title=0,
}
gdTips[60] = {
	id=60,
	button= {
			[1]= {name="确定",},
		},
	content="检测到新版本，为了您更好的游戏体验，请立即前往苹果商店下载最新游戏版本。",
	select= {},
	title=0,
}
gdTips[61] = {
	id=61,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否确定清除并重新附魔？",
	select= {
			[1]= {str="不再提示",},
		},
	title="附魔重置",
}
gdTips[62] = {
	id=62,
	button= {
			[1]= {name="确定",},
		},
	content="%s",
	select= {},
	title="提示",
}
gdTips[63] = {
	id=63,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您将花费1个马鞭对坐骑进行培养；\n马鞭培养每次增加5点成长值。",
	select= {
			[1]= {str="不再提示",},
		},
	title="马鞭培养",
}
gdTips[64] = {
	id=64,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您将花费10元宝对坐骑进行培养；\n元宝培养每次增加5点成长值。",
	select= {
			[1]= {str="不再提示",},
		},
	title="元宝培养",
}
gdTips[65] = {
	id=65,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="是否花费一定数量的元宝，提升满坐骑经验？",
	select= {},
	title="一键升级",
}
gdTips[66] = {
	id=66,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="进阶总共需要消耗%s进阶丹药或%s元宝；\n是否进行坐骑升阶？材料不足将由元宝代替\n（您现在有%s进阶丹药）",
	select= {},
	title="坐骑进阶",
}
gdTips[67] = {
	id=67,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="您将花费1个盘古碎片对坐骑进行强化；",
	select= {
			[1]= {str="不再提示",},
		},
	title="装备强化",
}
gdTips[68] = {
	id=68,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="进阶总共需要消耗%s开天玉或%s元宝；\n是否进行装备升阶？材料不足将由元宝代替\n（您现在有%s开天玉）",
	select= {},
	title="装备进阶",
}
gdTips[69] = {
	id=69,
	button= {
			[1]= {name="确定",},
			[2]= {name="取消",},
		},
	content="直接花费200元宝，可以直接刷新神秘女子！！！！",
	select= {
			[1]= {str="不再提示",},
		},
	title="刷新美女",
}
