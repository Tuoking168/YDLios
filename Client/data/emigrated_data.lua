if not (type(gdEmigrated)=="table") then
	gdEmigrated = {}
end

 gdEmigrated[1] = {
	name="财神任务",
	content="随机获得一个任务，完成任务后方可继续摇骰子。",
	[1]= {probability=100,reward="经验（跟等级有关）,金钱*38888",},
}
gdEmigrated[2] = {
	name="财神降临",
	content="随机获得如下奖励之一：\n1、金币 \n2、朱雀神翎 \n3、囧神（特殊头衔）\n4、金条",
	[1]= {probability=50,reward="金币奖励",},
	[2]= {probability=40,reward="朱雀神翎*1",},
	[3]= {probability=8,reward="囧神（特殊头衔）",},
	[4]= {probability=2,reward="金条*1",},
}
gdEmigrated[3] = {
	name="财神祝福",
	content="随机获得如下BUFF奖励之一：\n1、打怪经验增加100%（30分钟） \n2、生命上限增加10%（10分钟） \n3、魔法上限增加10%（10分钟） \n4、最大魔法防御增加100（10分钟） \n5、最大物理防御增加100（10分钟）",
	[1]= {probability=15,reward="双倍经验BUFF：打怪经验增加100%（30分钟）",},
	[2]= {probability=15,reward="强健体魄BUFF:生命上限增加10%（10分钟）",},
	[3]= {probability=15,reward="清晰思维BUFF：魔法上限增加10%（10分钟）",},
	[4]= {probability=15,reward="精神力战法BUFF：最大魔法防御增加100（10分钟）",},
	[5]= {probability=20,reward="神圣战甲术BUFF：最大物理防御增加100（10分钟）",},
	[6]= {probability=10,reward="仙女祝福BUFF：最大防御各增加50(10分钟)",},
	[7]= {probability=10,reward="斗士战神BUFF：造成伤害增加60(10分钟)",},
}
gdEmigrated[4] = {
	name="财神馈赠",
	content="随机获得如下奖励之一：\n1、获得一定数量的仙玉 \n2、获得一定数量的金币 \n3、获得一定数量的荣誉",
	[1]= {probability=4,reward="仙玉68",},
	[2]= {probability=3,reward="仙玉388",},
	[3]= {probability=2,reward="仙玉688",},
	[4]= {probability=1,reward="仙玉1688",},
	[5]= {probability=17,reward="金币38888",},
	[6]= {probability=10,reward="金币88888",},
	[7]= {probability=5,reward="金币888888",},
	[8]= {probability=1,reward="金币8888888",},
	[9]= {probability=18,reward="荣誉3888",},
	[10]= {probability=10,reward="荣誉6888",},
	[11]= {probability=5,reward="荣誉8888",},
	[12]= {probability=6,reward="荣誉88888",},
}
gdEmigrated[5] = {
	name="财神拦路",
	content="从战力榜中随机抽选一名玩家与您进行战力竞技，如果失败将回到本关的起点，如果成功则可继续摇骰子前行",
	[1]= {probability=100,reward="成功：获得与战力竞技胜利相同的经验+与等级挂钩的经验 \n失败：获得与战力竞技失败相同的经验并退回本关起点",},
}
gdEmigrated[6] = {
	name="财神福袋",
	content="随机获得如下物品奖励：\n1、1级灵珠 \n2、红玫瑰 \n3、幻武碎片 \n4、雪莲王 \n5、人参王 \n6、3-4级魂石",
	[1]= {probability=15,reward="1级灵珠*1",},
	[2]= {probability=16,reward="红玫瑰*1",},
	[3]= {probability=16,reward="攻击药水(中)*1",},
	[4]= {probability=1,reward="黄金雷锤碎片*1",},
	[5]= {probability=1,reward="如意金箍棒碎片*1",},
	[6]= {probability=1,reward="死神之镰碎片*1",},
	[7]= {probability=1,reward="生花妙笔碎片*1",},
	[8]= {probability=1,reward="黄金雷锤*1",},
	[9]= {probability=16,reward="雪莲王*1",},
	[10]= {probability=16,reward="人参王*1",},
	[11]= {probability=13,reward="随机3级魂石*1",},
	[12]= {probability=3,reward="随机4级魂石*1",},
	[13]= {probability=0,reward="随机5级魂石*1",},
}
gdEmigrated[7] = {
	name="筋斗云",
	content="随机向前前进一定的格数",
	[1]= {probability=30,reward="前进1格",},
	[2]= {probability=30,reward="前进2格",},
	[3]= {probability=20,reward="前进3格",},
	[4]= {probability=15,reward="前进4格",},
	[5]= {probability=5,reward="前进5格",},
}
gdEmigrated[8] = {
	name="打道回府",
	content="随机后退一定的格数",
	[1]= {probability=30,reward="后退1格",},
	[2]= {probability=30,reward="后退2格",},
	[3]= {probability=20,reward="后退3格",},
	[4]= {probability=15,reward="后退4格",},
	[5]= {probability=5,reward="后退5格",},
}
gdEmigrated[9] = {
	name="翻天覆地",
	content="重置本关所有随机事件",
	[1]= {probability=100,reward="重置所有格子的随机事件（不会重新触发当前格子的事件）",},
}
gdEmigrated[10] = {
	name="通关奖励一",
	content="通关后的奖励",
	[1]= {probability=100,reward="经验（跟等级挂钩）",},
	[2]= {probability=0,reward="红玫瑰*2",},
	[3]= {probability=0,reward="二级灵珠*2",},
}
gdEmigrated[11] = {
	name="通关奖励二",
	content="通关后的奖励",
	[1]= {probability=100,reward="经验（跟等级挂钩）",},
	[2]= {probability=0,reward="红玫瑰*4",},
	[3]= {probability=0,reward="二级灵珠*4",},
}
gdEmigrated[12] = {
	name="通关奖励三",
	content="通关后的奖励",
	[1]= {probability=100,reward="经验（跟等级挂钩）",},
	[2]= {probability=0,reward="红玫瑰*6",},
	[3]= {probability=0,reward="二级灵珠*8",},
}
