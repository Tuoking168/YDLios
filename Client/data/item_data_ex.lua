-- 全局配置表初始化
-- 初始化游戏中的各种配置表，防止在访问未定义的全局变量时报错

-- 属性名称配置表
if not (type(gdAttrName) == "table") then
    gdAttrName = {}
end

-- 属性是否为百分比标识表
if not (type(gdAttrIsPercent) == "table") then
    gdAttrIsPercent = {}
end

-- 装备升级配置表
if not (type(gdEquipUpgrade) == "table") then
    gdEquipUpgrade = {}
end

-- 装备强化配置表
if not (type(gdEquipEnhance) == "table") then
    gdEquipEnhance = {}
end

-- 装备鉴定（评估）配置表
if not (type(gdEquipEvaluate) == "table") then
    gdEquipEvaluate = {}
end

-- 物品合成配置表
if not (type(gdItemMerge) == "table") then
    gdItemMerge = {}
end

-- 宝石转换配置表
if not (type(gdItemStoneTransform) == "table") then
    gdItemStoneTransform = {}
end

-- 装备转生配置表
if not (type(gdItemReBorn) == "table") then
    gdItemReBorn = {}
end

-- 目标物品合成类型配置表
if not (type(gdtgtItemMergeType) == "table") then
    gdtgtItemMergeType = {}
end

-- 源物品合成类型配置表
if not (type(gdsrcItemMergeType) == "table") then
    gdsrcItemMergeType = {}
end

-- 描述信息配置表
if not (type(gddescription) == "table") then
    gddescription = {}
end

-- 物品修理配置表
if not (type(gdItemRepair) == "table") then
    gdItemRepair = {}
end

-- 翅膀强化配置表
if not (type(gdWingEnhance) == "table") then
    gdWingEnhance = {}
end

-- 极品评估（特殊属性）配置表
if not (type(gdBestEvaluate) == "table") then
    gdBestEvaluate = {}
end

-- 开光神兵（启灵）配置表
if not (type(gdOpenMagicWeapon) == "table") then
    gdOpenMagicWeapon = {}
end

-- 战足升级配置表
if not (type(gdFootUp) == "table") then
    gdFootUp = {}
end

-- 附魔随机属性列表
if not (type(gdFuMo)=="table") then
	gdFuMo = {}
end

-- 附魔强化表
if not (type(gdFuMoEnhance)=="table") then
	gdFuMoEnhance = {}
end

-- 坐骑基础属性
if not (type(gdHorseBaseStats)=="table") then
	gdHorseBaseStats = {}
end

-- 坐骑培养
if not (type(gdHorsePeiYang)=="table") then
	gdHorsePeiYang = {}
end

-- 坐骑进阶
if not (type(gdHorseJinJie)=="table") then
	gdHorseJinJie = {}
end

-- 坐骑装备基础属性
if not (type(gdHorseEquipBaseStats)=="table") then
	gdHorseEquipBaseStats = {}
end

-- 坐骑装备强化属性
if not (type(gdHorseEquipQiangHua)=="table") then
	gdHorseEquipQiangHua = {}
end

-- 坐骑装备强化属性
if not (type(gdHorseEquipJinJie)=="table") then
	gdHorseEquipJinJie = {}
end

-- 装备投保配置表
if not (type(gdEquipToubao)=="table") then
	gdEquipToubao = {}
end
 

gdAttrName = {
	[1]="生命上限",
	[2]="魔法上限",
	[3]="生命",
	[4]="魔法",
	[5]="物理攻击下限",
	[6]="物理攻击上限",
	[7]="法攻",
	[8]="魔法攻击上限",
	[9]="道攻",
	[10]="最大道攻",
	[11]="最小物理防御",
	[12]="最大物理防御",
	[13]="魔防",
	[14]="最大魔法防御",
	[15]="生命恢复",
	[16]="魔法恢复",
	[17]="物理命中",
	[18]="敏捷",
	[19]="魔法命中",
	[20]="魔法闪避",
	[21]="毒物闪避",
	[22]="毒物恢复",
	[23]="麻痹",
	[24]="死亡恢复",
	[25]="幸运",
	[26]="诅咒",
	[27]="神圣",
	[28]="魔法值抵消伤害",
	[29]="移速",
	[30]="攻速",
	[31]="穿透",
	[32]="暴击",
	[33]="防爆",
	[34]="反弹",
	[35]="Buff持续时间增加",
	[36]="吸血",
	[37]="吸蓝",
	[38]="处决",
	
	
	[40]="生命上限%",
	[41]="魔法上限%",
	[51]="魂石最大物理防御%",
	[53]="魂石最大魔法防御%",
	[700]="经验玉",
	[701]="杀怪经验额外",
	[705]="基础怪物金币掉落",
	[710]="特殊攻击",
	[730]="对玩家造成伤害",
	[800]="道士毒",
}
gdAttrIsPercent = {
	[1]=false,
	[2]=false,
	[3]=false,
	[4]=false,
	[5]=false,
	[6]=false,
	[7]=false,
	[8]=false,
	[9]=false,
	[10]=false,
	[11]=false,
	[12]=false,
	[13]=false,
	[14]=false,
	[15]=true,
	[16]=true,
	[17]=true,
	[18]=false,
	[19]=true,
	[20]=true,
	[21]=true,
	[22]=true,
	[23]=false,
	[24]=true,
	[25]=false,
	[26]=false,
	[27]=false,
	[28]=true,
	[29]=true,
	[30]=true,
	[31]=true,
	[32]=true,
	[33]=true,
	[34]=true,
	[35]=true,
	[36]=true,
	[37]=true,
	[38]=true,
	[700]=true,
	[701]=true,
	[705]=true,
	[710]=false,
	[730]=true,
	[800]=true,
}


--装备升级
--战士3-4 41003
gdEquipUpgrade[20080] = {dstEquipId=20090,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20081] = {dstEquipId=20091,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20082] = {dstEquipId=20092,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20083] = {dstEquipId=20093,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20084] = {dstEquipId=20094,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20085] = {dstEquipId=20095,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20086] = {dstEquipId=20096,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20087] = {dstEquipId=20097,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20088] = {dstEquipId=20098,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}

--战士4-5
gdEquipUpgrade[20090] = {dstEquipId=20100,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20091] = {dstEquipId=20101,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20092] = {dstEquipId=20102,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20093] = {dstEquipId=20103,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20094] = {dstEquipId=20104,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20095] = {dstEquipId=20105,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20096] = {dstEquipId=20106,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20097] = {dstEquipId=20107,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20098] = {dstEquipId=20108,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}

--战士5-6
gdEquipUpgrade[20100] = {dstEquipId=20110,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20101] = {dstEquipId=20111,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20102] = {dstEquipId=20112,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20103] = {dstEquipId=20113,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20104] = {dstEquipId=20114,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20105] = {dstEquipId=20115,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20106] = {dstEquipId=20116,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20107] = {dstEquipId=20117,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20108] = {dstEquipId=20118,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}

--战士6-7
gdEquipUpgrade[20110] = {dstEquipId=20180,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20111] = {dstEquipId=20181,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20112] = {dstEquipId=20182,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20113] = {dstEquipId=20183,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20114] = {dstEquipId=20184,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20115] = {dstEquipId=20185,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20116] = {dstEquipId=20186,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20117] = {dstEquipId=20187,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20118] = {dstEquipId=20188,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}

--战士7-8
gdEquipUpgrade[20180] = {dstEquipId=20300,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20181] = {dstEquipId=20301,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20182] = {dstEquipId=20302,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20183] = {dstEquipId=20303,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20184] = {dstEquipId=20304,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20185] = {dstEquipId=20305,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20186] = {dstEquipId=20306,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20187] = {dstEquipId=20307,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20188] = {dstEquipId=20308,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}

-------------------------------------------------------------------------------------------------

--法师3-4
gdEquipUpgrade[20140] = {dstEquipId=20150,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20141] = {dstEquipId=20151,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20142] = {dstEquipId=20152,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20143] = {dstEquipId=20153,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20144] = {dstEquipId=20154,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20145] = {dstEquipId=20155,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20146] = {dstEquipId=20156,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20147] = {dstEquipId=20157,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20148] = {dstEquipId=20158,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}

--法师4-5
gdEquipUpgrade[20150] = {dstEquipId=20160,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20151] = {dstEquipId=20161,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20152] = {dstEquipId=20162,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20153] = {dstEquipId=20163,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20154] = {dstEquipId=20164,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20155] = {dstEquipId=20165,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20156] = {dstEquipId=20166,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20157] = {dstEquipId=20167,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20158] = {dstEquipId=20168,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}

--法师5-6
gdEquipUpgrade[20160] = {dstEquipId=20170,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20161] = {dstEquipId=20171,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20162] = {dstEquipId=20172,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20163] = {dstEquipId=20173,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20164] = {dstEquipId=20174,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20165] = {dstEquipId=20175,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20166] = {dstEquipId=20176,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20167] = {dstEquipId=20177,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20168] = {dstEquipId=20178,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}

--法师6-7
gdEquipUpgrade[20170] = {dstEquipId=20190,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20171] = {dstEquipId=20191,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20172] = {dstEquipId=20192,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20173] = {dstEquipId=20193,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20174] = {dstEquipId=20194,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20175] = {dstEquipId=20195,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20176] = {dstEquipId=20196,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20177] = {dstEquipId=20197,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20178] = {dstEquipId=20198,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}

--法师7-8
gdEquipUpgrade[20190] = {dstEquipId=20310,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20191] = {dstEquipId=20311,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20192] = {dstEquipId=20312,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20193] = {dstEquipId=20313,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20194] = {dstEquipId=20314,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20195] = {dstEquipId=20315,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20196] = {dstEquipId=20316,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20197] = {dstEquipId=20317,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20198] = {dstEquipId=20318,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}

---------------------------------------------------------------------------------------------------------
--道士3-4
gdEquipUpgrade[20020] = {dstEquipId=20030,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20021] = {dstEquipId=20031,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20022] = {dstEquipId=20032,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20023] = {dstEquipId=20033,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20024] = {dstEquipId=20034,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20025] = {dstEquipId=20035,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20026] = {dstEquipId=20036,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20027] = {dstEquipId=20037,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}
gdEquipUpgrade[20028] = {dstEquipId=20038,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=41003,}

--道士4-5
gdEquipUpgrade[20030] = {dstEquipId=20040,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20031] = {dstEquipId=20041,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20032] = {dstEquipId=20042,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20033] = {dstEquipId=20043,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20034] = {dstEquipId=20044,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20035] = {dstEquipId=20045,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20036] = {dstEquipId=20046,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20037] = {dstEquipId=20047,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}
gdEquipUpgrade[20038] = {dstEquipId=20048,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=30,reqItemId=41003,}

--道士5-6
gdEquipUpgrade[20040] = {dstEquipId=20050,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20041] = {dstEquipId=20051,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20042] = {dstEquipId=20052,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20043] = {dstEquipId=20053,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20044] = {dstEquipId=20054,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20045] = {dstEquipId=20055,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20046] = {dstEquipId=20056,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20047] = {dstEquipId=20057,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}
gdEquipUpgrade[20048] = {dstEquipId=20058,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=41003,}

--道士6-7
gdEquipUpgrade[20050] = {dstEquipId=20200,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20051] = {dstEquipId=20201,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20052] = {dstEquipId=20202,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20053] = {dstEquipId=20203,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20054] = {dstEquipId=20204,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20055] = {dstEquipId=20205,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20056] = {dstEquipId=20206,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20057] = {dstEquipId=20207,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[20058] = {dstEquipId=20208,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}

--道士7-8
gdEquipUpgrade[20200] = {dstEquipId=20320,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20201] = {dstEquipId=20321,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20202] = {dstEquipId=20322,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20203] = {dstEquipId=20323,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20204] = {dstEquipId=20324,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20205] = {dstEquipId=20325,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20206] = {dstEquipId=20326,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20207] = {dstEquipId=20327,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[20208] = {dstEquipId=20328,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}



---------------------------------------------------------------------------------------------------------------------------------------------------------
-----战士9-10
gdEquipUpgrade[20329] = {dstEquipId=20500,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20330] = {dstEquipId=20501,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20331] = {dstEquipId=20502,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20332] = {dstEquipId=20503,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20333] = {dstEquipId=20504,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20334] = {dstEquipId=20505,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20335] = {dstEquipId=20506,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20336] = {dstEquipId=20507,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20337] = {dstEquipId=20508,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
-----战士10-11
gdEquipUpgrade[20500] = {dstEquipId=20530,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20501] = {dstEquipId=20531,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20502] = {dstEquipId=20532,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20503] = {dstEquipId=20533,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20504] = {dstEquipId=20534,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20505] = {dstEquipId=20535,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20506] = {dstEquipId=20536,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20507] = {dstEquipId=20537,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20508] = {dstEquipId=20538,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
--------------------------------------------------------------------------------------------------------
-----法师9-10
gdEquipUpgrade[20338] = {dstEquipId=20510,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20339] = {dstEquipId=20511,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20340] = {dstEquipId=20512,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20341] = {dstEquipId=20513,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20342] = {dstEquipId=20514,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20343] = {dstEquipId=20515,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20344] = {dstEquipId=20516,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20345] = {dstEquipId=20517,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20346] = {dstEquipId=20518,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
-----法师10-11
gdEquipUpgrade[20510] = {dstEquipId=20540,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20511] = {dstEquipId=20541,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20512] = {dstEquipId=20542,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20513] = {dstEquipId=20543,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20514] = {dstEquipId=20544,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20515] = {dstEquipId=20545,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20516] = {dstEquipId=20546,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20517] = {dstEquipId=20547,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20518] = {dstEquipId=20548,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
--------------------------------------------------------------------------------------------------------
-----道士9-10
gdEquipUpgrade[20347] = {dstEquipId=20520,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20348] = {dstEquipId=20521,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20349] = {dstEquipId=20522,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20350] = {dstEquipId=20523,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20351] = {dstEquipId=20524,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20352] = {dstEquipId=20525,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20353] = {dstEquipId=20526,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20354] = {dstEquipId=20527,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[20355] = {dstEquipId=20528,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
-----道士10-11
gdEquipUpgrade[20520] = {dstEquipId=20550,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20521] = {dstEquipId=20551,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20522] = {dstEquipId=20552,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20523] = {dstEquipId=20553,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20524] = {dstEquipId=20554,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20525] = {dstEquipId=20555,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20526] = {dstEquipId=20556,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20527] = {dstEquipId=20557,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}
gdEquipUpgrade[20528] = {dstEquipId=20558,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=88,reqItemId=41003,}








gdEquipUpgrade[60001] = {dstEquipId=60011,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=18,reqItemId=40000,}
gdEquipUpgrade[60011] = {dstEquipId=60021,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=18,reqItemId=40001,}
gdEquipUpgrade[60021] = {dstEquipId=60031,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=18,reqItemId=40002,}
gdEquipUpgrade[60031] = {dstEquipId=60041,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=18,reqItemId=40003,}
gdEquipUpgrade[60041] = {dstEquipId=60051,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=18,reqItemId=40004,}
gdEquipUpgrade[60000] = {dstEquipId=60010,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40000,}
gdEquipUpgrade[60010] = {dstEquipId=60020,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[60020] = {dstEquipId=60030,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=40,reqItemId=40002,}
gdEquipUpgrade[60030] = {dstEquipId=60040,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=40,reqItemId=40003,}
gdEquipUpgrade[60040] = {dstEquipId=60050,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=40,reqItemId=40004,}
gdEquipUpgrade[60002] = {dstEquipId=60012,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=22,reqItemId=40000,}
gdEquipUpgrade[60012] = {dstEquipId=60022,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=22,reqItemId=40001,}
gdEquipUpgrade[60022] = {dstEquipId=60032,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=22,reqItemId=40002,}
gdEquipUpgrade[60032] = {dstEquipId=60042,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=22,reqItemId=40003,}
gdEquipUpgrade[60042] = {dstEquipId=60052,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=22,reqItemId=40004,}
gdEquipUpgrade[60003] = {dstEquipId=60013,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=22,reqItemId=40000,}
gdEquipUpgrade[60013] = {dstEquipId=60023,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=22,reqItemId=40001,}
gdEquipUpgrade[60023] = {dstEquipId=60033,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=22,reqItemId=40002,}
gdEquipUpgrade[60033] = {dstEquipId=60043,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=22,reqItemId=40003,}
gdEquipUpgrade[60043] = {dstEquipId=60053,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=22,reqItemId=40004,}
gdEquipUpgrade[60004] = {dstEquipId=60014,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60014] = {dstEquipId=60024,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=10,reqItemId=40001,}
gdEquipUpgrade[60024] = {dstEquipId=60034,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=10,reqItemId=40002,}
gdEquipUpgrade[60034] = {dstEquipId=60044,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=10,reqItemId=40003,}
gdEquipUpgrade[60044] = {dstEquipId=60054,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=10,reqItemId=40004,}
gdEquipUpgrade[60005] = {dstEquipId=60015,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60015] = {dstEquipId=60025,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60025] = {dstEquipId=60035,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60035] = {dstEquipId=60045,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60045] = {dstEquipId=60055,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60006] = {dstEquipId=60016,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60016] = {dstEquipId=60026,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=10,reqItemId=40001,}
gdEquipUpgrade[60026] = {dstEquipId=60036,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=10,reqItemId=40002,}
gdEquipUpgrade[60036] = {dstEquipId=60046,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=10,reqItemId=40003,}
gdEquipUpgrade[60046] = {dstEquipId=60056,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=10,reqItemId=40004,}
gdEquipUpgrade[60007] = {dstEquipId=60017,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60017] = {dstEquipId=60027,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60027] = {dstEquipId=60037,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60037] = {dstEquipId=60047,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60047] = {dstEquipId=60057,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60008] = {dstEquipId=60018,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60018] = {dstEquipId=60028,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60028] = {dstEquipId=60038,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60038] = {dstEquipId=60048,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60048] = {dstEquipId=60058,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60060] = {dstEquipId=60070,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40000,}
gdEquipUpgrade[60070] = {dstEquipId=60080,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[60080] = {dstEquipId=60090,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=40,reqItemId=40002,}
gdEquipUpgrade[60090] = {dstEquipId=60100,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=40,reqItemId=40003,}
gdEquipUpgrade[60100] = {dstEquipId=60110,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=40,reqItemId=40004,}
gdEquipUpgrade[60061] = {dstEquipId=60071,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=18,reqItemId=40000,}
gdEquipUpgrade[60071] = {dstEquipId=60081,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=18,reqItemId=40001,}
gdEquipUpgrade[60081] = {dstEquipId=60091,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=18,reqItemId=40002,}
gdEquipUpgrade[60091] = {dstEquipId=60101,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=18,reqItemId=40003,}
gdEquipUpgrade[60101] = {dstEquipId=60111,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=18,reqItemId=40004,}
gdEquipUpgrade[60062] = {dstEquipId=60072,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=22,reqItemId=40000,}
gdEquipUpgrade[60072] = {dstEquipId=60082,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=22,reqItemId=40001,}
gdEquipUpgrade[60082] = {dstEquipId=60092,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=22,reqItemId=40002,}
gdEquipUpgrade[60092] = {dstEquipId=60102,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=22,reqItemId=40003,}
gdEquipUpgrade[60102] = {dstEquipId=60112,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=22,reqItemId=40004,}
gdEquipUpgrade[60063] = {dstEquipId=60073,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=22,reqItemId=40000,}
gdEquipUpgrade[60073] = {dstEquipId=60083,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=22,reqItemId=40001,}
gdEquipUpgrade[60083] = {dstEquipId=60093,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=22,reqItemId=40002,}
gdEquipUpgrade[60093] = {dstEquipId=60103,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=22,reqItemId=40003,}
gdEquipUpgrade[60103] = {dstEquipId=60113,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=22,reqItemId=40004,}
gdEquipUpgrade[60064] = {dstEquipId=60074,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60074] = {dstEquipId=60084,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=10,reqItemId=40001,}
gdEquipUpgrade[60084] = {dstEquipId=60094,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=10,reqItemId=40002,}
gdEquipUpgrade[60094] = {dstEquipId=60104,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=10,reqItemId=40003,}
gdEquipUpgrade[60104] = {dstEquipId=60114,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=10,reqItemId=40004,}
gdEquipUpgrade[60065] = {dstEquipId=60075,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60075] = {dstEquipId=60085,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60085] = {dstEquipId=60095,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60095] = {dstEquipId=60105,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60105] = {dstEquipId=60115,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60066] = {dstEquipId=60076,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60076] = {dstEquipId=60086,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=10,reqItemId=40001,}
gdEquipUpgrade[60086] = {dstEquipId=60096,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=10,reqItemId=40002,}
gdEquipUpgrade[60096] = {dstEquipId=60106,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=10,reqItemId=40003,}
gdEquipUpgrade[60106] = {dstEquipId=60116,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=10,reqItemId=40004,}
gdEquipUpgrade[60067] = {dstEquipId=60077,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60077] = {dstEquipId=60087,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60087] = {dstEquipId=60097,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60097] = {dstEquipId=60107,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60107] = {dstEquipId=60117,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60068] = {dstEquipId=60078,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60078] = {dstEquipId=60088,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60088] = {dstEquipId=60098,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60098] = {dstEquipId=60108,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60108] = {dstEquipId=60118,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60120] = {dstEquipId=60130,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40000,}
gdEquipUpgrade[60130] = {dstEquipId=60140,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[60140] = {dstEquipId=60150,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=40,reqItemId=40002,}
gdEquipUpgrade[60150] = {dstEquipId=60160,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=40,reqItemId=40003,}
gdEquipUpgrade[60160] = {dstEquipId=60170,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=40,reqItemId=40004,}
gdEquipUpgrade[60121] = {dstEquipId=60131,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=18,reqItemId=40000,}
gdEquipUpgrade[60131] = {dstEquipId=60141,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=18,reqItemId=40001,}
gdEquipUpgrade[60141] = {dstEquipId=60151,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=18,reqItemId=40002,}
gdEquipUpgrade[60151] = {dstEquipId=60161,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=18,reqItemId=40003,}
gdEquipUpgrade[60161] = {dstEquipId=60171,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=18,reqItemId=40004,}
gdEquipUpgrade[60122] = {dstEquipId=60132,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=22,reqItemId=40000,}
gdEquipUpgrade[60132] = {dstEquipId=60142,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=22,reqItemId=40001,}
gdEquipUpgrade[60142] = {dstEquipId=60152,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=22,reqItemId=40002,}
gdEquipUpgrade[60152] = {dstEquipId=60162,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=22,reqItemId=40003,}
gdEquipUpgrade[60162] = {dstEquipId=60172,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=22,reqItemId=40004,}
gdEquipUpgrade[60123] = {dstEquipId=60133,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=22,reqItemId=40000,}
gdEquipUpgrade[60133] = {dstEquipId=60143,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=22,reqItemId=40001,}
gdEquipUpgrade[60143] = {dstEquipId=60153,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=22,reqItemId=40002,}
gdEquipUpgrade[60153] = {dstEquipId=60163,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=22,reqItemId=40003,}
gdEquipUpgrade[60163] = {dstEquipId=60173,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=22,reqItemId=40004,}
gdEquipUpgrade[60124] = {dstEquipId=60134,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60134] = {dstEquipId=60144,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=10,reqItemId=40001,}
gdEquipUpgrade[60144] = {dstEquipId=60154,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=10,reqItemId=40002,}
gdEquipUpgrade[60154] = {dstEquipId=60164,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=10,reqItemId=40003,}
gdEquipUpgrade[60164] = {dstEquipId=60174,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=10,reqItemId=40004,}
gdEquipUpgrade[60125] = {dstEquipId=60135,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60135] = {dstEquipId=60145,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60145] = {dstEquipId=60155,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60155] = {dstEquipId=60165,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60165] = {dstEquipId=60175,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60126] = {dstEquipId=60136,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60136] = {dstEquipId=60146,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=10,reqItemId=40001,}
gdEquipUpgrade[60146] = {dstEquipId=60156,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=10,reqItemId=40002,}
gdEquipUpgrade[60156] = {dstEquipId=60166,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=10,reqItemId=40003,}
gdEquipUpgrade[60166] = {dstEquipId=60176,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=10,reqItemId=40004,}
gdEquipUpgrade[60127] = {dstEquipId=60137,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60137] = {dstEquipId=60147,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60147] = {dstEquipId=60157,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60157] = {dstEquipId=60167,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60167] = {dstEquipId=60177,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60128] = {dstEquipId=60138,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60138] = {dstEquipId=60148,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60148] = {dstEquipId=60158,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60158] = {dstEquipId=60168,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60168] = {dstEquipId=60178,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60202] = {dstEquipId=60203,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60203] = {dstEquipId=60204,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60204] = {dstEquipId=60205,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60205] = {dstEquipId=60206,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60206] = {dstEquipId=60207,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60209] = {dstEquipId=60210,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60210] = {dstEquipId=60211,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60211] = {dstEquipId=60212,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60212] = {dstEquipId=60213,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60213] = {dstEquipId=60214,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60216] = {dstEquipId=60217,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=6,reqItemId=40000,}
gdEquipUpgrade[60217] = {dstEquipId=60218,reborncnt=18,rebornreq=40014,reqEhLevel=4,reqGold=20000,reqItemCnt=6,reqItemId=40001,}
gdEquipUpgrade[60218] = {dstEquipId=60219,reborncnt=20,rebornreq=40014,reqEhLevel=5,reqGold=30000,reqItemCnt=6,reqItemId=40002,}
gdEquipUpgrade[60219] = {dstEquipId=60220,reborncnt=22,rebornreq=40014,reqEhLevel=6,reqGold=40000,reqItemCnt=6,reqItemId=40003,}
gdEquipUpgrade[60220] = {dstEquipId=60221,reborncnt=24,rebornreq=40014,reqEhLevel=8,reqGold=50000,reqItemCnt=6,reqItemId=40004,}
gdEquipUpgrade[60223] = {dstEquipId=60224,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=60223,}
gdEquipUpgrade[60224] = {dstEquipId=60225,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=20000,reqItemCnt=2,reqItemId=60224,}
gdEquipUpgrade[60225] = {dstEquipId=60226,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=30000,reqItemCnt=2,reqItemId=60225,}
gdEquipUpgrade[60226] = {dstEquipId=60227,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=40000,reqItemCnt=2,reqItemId=60226,}
gdEquipUpgrade[60227] = {dstEquipId=60228,reborncnt=24,rebornreq=40014,reqEhLevel=0,reqGold=50000,reqItemCnt=2,reqItemId=60227,}
gdEquipUpgrade[60228] = {dstEquipId=60229,reborncnt=26,rebornreq=40014,reqEhLevel=0,reqGold=60000,reqItemCnt=2,reqItemId=60228,}
--暗影猩红复生戒指
gdEquipUpgrade[60229] = {dstEquipId=60230,reborncnt=26,rebornreq=40014,reqEhLevel=0,reqGold=60000,reqItemCnt=3,reqItemId=60229,}

gdEquipUpgrade[60231] = {dstEquipId=60232,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=60231,}
gdEquipUpgrade[60232] = {dstEquipId=60233,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=20000,reqItemCnt=2,reqItemId=60232,}
gdEquipUpgrade[60233] = {dstEquipId=60234,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=30000,reqItemCnt=2,reqItemId=60233,}
gdEquipUpgrade[60234] = {dstEquipId=60235,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=40000,reqItemCnt=2,reqItemId=60234,}
gdEquipUpgrade[60235] = {dstEquipId=60236,reborncnt=24,rebornreq=40014,reqEhLevel=0,reqGold=50000,reqItemCnt=2,reqItemId=60235,}
gdEquipUpgrade[60236] = {dstEquipId=60237,reborncnt=26,rebornreq=40014,reqEhLevel=0,reqGold=60000,reqItemCnt=2,reqItemId=60236,}
--
gdEquipUpgrade[60237] = {dstEquipId=60238,reborncnt=26,rebornreq=40014,reqEhLevel=0,reqGold=60000,reqItemCnt=3,reqItemId=60237,}


gdEquipUpgrade[60239] = {dstEquipId=60240,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=60239,}
gdEquipUpgrade[60240] = {dstEquipId=60241,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=20000,reqItemCnt=2,reqItemId=60240,}
gdEquipUpgrade[60241] = {dstEquipId=60242,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=30000,reqItemCnt=2,reqItemId=60241,}
gdEquipUpgrade[60242] = {dstEquipId=60243,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=40000,reqItemCnt=2,reqItemId=60242,}
gdEquipUpgrade[60243] = {dstEquipId=60244,reborncnt=24,rebornreq=40014,reqEhLevel=0,reqGold=50000,reqItemCnt=2,reqItemId=60243,}
gdEquipUpgrade[60244] = {dstEquipId=60245,reborncnt=26,rebornreq=40014,reqEhLevel=0,reqGold=60000,reqItemCnt=2,reqItemId=60244,}
--暗影猩蓝护法戒指
gdEquipUpgrade[60245] = {dstEquipId=60246,reborncnt=26,rebornreq=40014,reqEhLevel=0,reqGold=60000,reqItemCnt=3,reqItemId=60245,}


gdEquipUpgrade[60180] = {dstEquipId=60337,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[60181] = {dstEquipId=60338,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=27,reqItemId=40004,}
gdEquipUpgrade[60182] = {dstEquipId=60339,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=33,reqItemId=40004,}
gdEquipUpgrade[60183] = {dstEquipId=60340,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=33,reqItemId=40004,}
gdEquipUpgrade[60184] = {dstEquipId=60341,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=15,reqItemId=40004,}
gdEquipUpgrade[60185] = {dstEquipId=60342,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=9,reqItemId=40004,}
gdEquipUpgrade[60186] = {dstEquipId=60343,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=15,reqItemId=40004,}
gdEquipUpgrade[60187] = {dstEquipId=60344,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=9,reqItemId=40004,}
gdEquipUpgrade[60188] = {dstEquipId=60345,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=9,reqItemId=40004,}
gdEquipUpgrade[60189] = {dstEquipId=60346,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=50000,reqItemCnt=12,reqItemId=40004,}
gdEquipUpgrade[60191] = {dstEquipId=60349,reborncnt=10,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[60192] = {dstEquipId=60350,reborncnt=4,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=27,reqItemId=40004,}
gdEquipUpgrade[60193] = {dstEquipId=60351,reborncnt=5,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=33,reqItemId=40004,}
gdEquipUpgrade[60194] = {dstEquipId=60352,reborncnt=5,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=33,reqItemId=40004,}
gdEquipUpgrade[60195] = {dstEquipId=60353,reborncnt=3,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=15,reqItemId=40004,}
gdEquipUpgrade[60196] = {dstEquipId=60354,reborncnt=2,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=9,reqItemId=40004,}
gdEquipUpgrade[60197] = {dstEquipId=60355,reborncnt=3,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=15,reqItemId=40004,}
gdEquipUpgrade[60198] = {dstEquipId=60356,reborncnt=2,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=9,reqItemId=40004,}
gdEquipUpgrade[60199] = {dstEquipId=60357,reborncnt=2,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=9,reqItemId=40004,}
gdEquipUpgrade[60200] = {dstEquipId=60358,reborncnt=2,rebornreq=40015,reqEhLevel=0,reqGold=50000,reqItemCnt=12,reqItemId=40004,}
gdEquipUpgrade[60259] = {dstEquipId=60260,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60260] = {dstEquipId=60261,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60261] = {dstEquipId=60262,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40000,}
gdEquipUpgrade[60262] = {dstEquipId=60263,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40001,}
gdEquipUpgrade[60263] = {dstEquipId=60264,reborncnt=24,rebornreq=40014,reqEhLevel=0,reqGold=5000,reqItemCnt=40,reqItemId=40002,}
gdEquipUpgrade[60266] = {dstEquipId=60267,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=3,reqItemId=60266,}
gdEquipUpgrade[60267] = {dstEquipId=60268,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=3,reqItemId=60267,}
gdEquipUpgrade[60268] = {dstEquipId=60269,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=3,reqItemId=60268,}
gdEquipUpgrade[60269] = {dstEquipId=60270,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=3,reqItemId=60269,}
gdEquipUpgrade[60270] = {dstEquipId=60271,reborncnt=24,rebornreq=40014,reqEhLevel=0,reqGold=5000,reqItemCnt=3,reqItemId=60270,}
gdEquipUpgrade[60271] = {dstEquipId=60272,reborncnt=26,rebornreq=40014,reqEhLevel=0,reqGold=6000,reqItemCnt=3,reqItemId=60271,}
gdEquipUpgrade[60272] = {dstEquipId=60273,reborncnt=28,rebornreq=40014,reqEhLevel=0,reqGold=7000,reqItemCnt=3,reqItemId=60272,}
gdEquipUpgrade[60287] = {dstEquipId=60288,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60288] = {dstEquipId=60289,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=15,reqItemId=40001,}
gdEquipUpgrade[60289] = {dstEquipId=60290,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40002,}
gdEquipUpgrade[60290] = {dstEquipId=60291,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40003,}
gdEquipUpgrade[60294] = {dstEquipId=60295,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60295] = {dstEquipId=60296,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=15,reqItemId=40001,}
gdEquipUpgrade[60296] = {dstEquipId=60297,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40002,}
gdEquipUpgrade[60297] = {dstEquipId=60298,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40003,}
gdEquipUpgrade[60301] = {dstEquipId=60302,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60302] = {dstEquipId=60303,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=15,reqItemId=40001,}
gdEquipUpgrade[60303] = {dstEquipId=60304,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40002,}
gdEquipUpgrade[60304] = {dstEquipId=60305,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40003,}
gdEquipUpgrade[60308] = {dstEquipId=60309,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60309] = {dstEquipId=60310,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=15,reqItemId=40001,}
gdEquipUpgrade[60310] = {dstEquipId=60311,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40002,}
gdEquipUpgrade[60311] = {dstEquipId=60312,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40003,}
gdEquipUpgrade[60315] = {dstEquipId=60316,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60316] = {dstEquipId=60317,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=15,reqItemId=40001,}
gdEquipUpgrade[60317] = {dstEquipId=60318,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40002,}
gdEquipUpgrade[60318] = {dstEquipId=60319,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40003,}
gdEquipUpgrade[60322] = {dstEquipId=60323,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60323] = {dstEquipId=60324,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=15,reqItemId=40001,}
gdEquipUpgrade[60324] = {dstEquipId=60325,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40002,}
gdEquipUpgrade[60325] = {dstEquipId=60326,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40003,}
gdEquipUpgrade[60329] = {dstEquipId=60330,reborncnt=16,rebornreq=40014,reqEhLevel=0,reqGold=1000,reqItemCnt=10,reqItemId=40000,}
gdEquipUpgrade[60330] = {dstEquipId=60331,reborncnt=18,rebornreq=40014,reqEhLevel=0,reqGold=2000,reqItemCnt=15,reqItemId=40001,}
gdEquipUpgrade[60331] = {dstEquipId=60332,reborncnt=20,rebornreq=40014,reqEhLevel=0,reqGold=3000,reqItemCnt=20,reqItemId=40002,}
gdEquipUpgrade[60332] = {dstEquipId=60333,reborncnt=22,rebornreq=40014,reqEhLevel=0,reqGold=4000,reqItemCnt=30,reqItemId=40003,}
gdEquipUpgrade[81000] = {dstEquipId=81001,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81001] = {dstEquipId=81002,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81002] = {dstEquipId=81003,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81003] = {dstEquipId=81004,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81004] = {dstEquipId=81005,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81005] = {dstEquipId=81006,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81006] = {dstEquipId=81007,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81007] = {dstEquipId=81008,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81008] = {dstEquipId=81009,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81033] = {dstEquipId=81034,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81034] = {dstEquipId=81035,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81035] = {dstEquipId=81036,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81036] = {dstEquipId=81037,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81037] = {dstEquipId=81038,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81038] = {dstEquipId=81039,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81039] = {dstEquipId=81040,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81040] = {dstEquipId=81041,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81041] = {dstEquipId=81042,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81044] = {dstEquipId=81045,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81045] = {dstEquipId=81046,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81046] = {dstEquipId=81047,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81047] = {dstEquipId=81048,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81048] = {dstEquipId=81049,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81049] = {dstEquipId=81050,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81050] = {dstEquipId=81051,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81051] = {dstEquipId=81052,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81052] = {dstEquipId=81053,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81055] = {dstEquipId=81056,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81056] = {dstEquipId=81057,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81057] = {dstEquipId=81058,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81058] = {dstEquipId=81059,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81059] = {dstEquipId=81060,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81060] = {dstEquipId=81061,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81061] = {dstEquipId=81062,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81062] = {dstEquipId=81063,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81063] = {dstEquipId=81064,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81066] = {dstEquipId=81067,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81067] = {dstEquipId=81068,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81068] = {dstEquipId=81069,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81069] = {dstEquipId=81070,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81070] = {dstEquipId=81071,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81071] = {dstEquipId=81072,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81072] = {dstEquipId=81073,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81073] = {dstEquipId=81074,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81076] = {dstEquipId=81077,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81077] = {dstEquipId=81078,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81078] = {dstEquipId=81079,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81079] = {dstEquipId=81080,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81080] = {dstEquipId=81081,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81081] = {dstEquipId=81082,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81082] = {dstEquipId=81083,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81083] = {dstEquipId=81084,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81086] = {dstEquipId=81087,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81087] = {dstEquipId=81088,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81088] = {dstEquipId=81089,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81089] = {dstEquipId=81090,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81092] = {dstEquipId=81093,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81093] = {dstEquipId=81094,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81094] = {dstEquipId=81095,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81095] = {dstEquipId=81096,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81109] = {dstEquipId=81110,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81110] = {dstEquipId=81111,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81111] = {dstEquipId=81112,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81112] = {dstEquipId=81113,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81113] = {dstEquipId=81114,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81114] = {dstEquipId=81115,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81115] = {dstEquipId=81116,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81116] = {dstEquipId=81117,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81119] = {dstEquipId=81120,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81120] = {dstEquipId=81121,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81121] = {dstEquipId=81122,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81122] = {dstEquipId=81123,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81123] = {dstEquipId=81124,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81124] = {dstEquipId=81125,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81125] = {dstEquipId=81126,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81126] = {dstEquipId=81127,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81140] = {dstEquipId=81141,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81141] = {dstEquipId=81142,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81142] = {dstEquipId=81143,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81143] = {dstEquipId=81144,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81144] = {dstEquipId=81145,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81145] = {dstEquipId=81146,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81146] = {dstEquipId=81147,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81147] = {dstEquipId=81148,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81148] = {dstEquipId=81149,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[82000] = {dstEquipId=82001,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82000,}
gdEquipUpgrade[82001] = {dstEquipId=82002,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82001,}
gdEquipUpgrade[82002] = {dstEquipId=82003,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82002,}
gdEquipUpgrade[82003] = {dstEquipId=82004,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82003,}
gdEquipUpgrade[82004] = {dstEquipId=82005,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82004,}
gdEquipUpgrade[82005] = {dstEquipId=82006,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82005,}
gdEquipUpgrade[82006] = {dstEquipId=82007,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82006,}
gdEquipUpgrade[82007] = {dstEquipId=82008,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82007,}
gdEquipUpgrade[82008] = {dstEquipId=82009,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82008,}
gdEquipUpgrade[82012] = {dstEquipId=82013,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82012,}
gdEquipUpgrade[82013] = {dstEquipId=82014,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82013,}
gdEquipUpgrade[82014] = {dstEquipId=82015,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82014,}
gdEquipUpgrade[82015] = {dstEquipId=82016,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82015,}
gdEquipUpgrade[82016] = {dstEquipId=82017,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82016,}
gdEquipUpgrade[82017] = {dstEquipId=82018,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82017,}
gdEquipUpgrade[82018] = {dstEquipId=82019,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82018,}
gdEquipUpgrade[82019] = {dstEquipId=82020,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82019,}
gdEquipUpgrade[82020] = {dstEquipId=82021,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82020,}
gdEquipUpgrade[82024] = {dstEquipId=82025,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82024,}
gdEquipUpgrade[82025] = {dstEquipId=82026,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82025,}
gdEquipUpgrade[82026] = {dstEquipId=82027,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82026,}
gdEquipUpgrade[82027] = {dstEquipId=82028,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82027,}
gdEquipUpgrade[82028] = {dstEquipId=82029,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82028,}
gdEquipUpgrade[82029] = {dstEquipId=82030,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82029,}
gdEquipUpgrade[82030] = {dstEquipId=82031,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82030,}
gdEquipUpgrade[82031] = {dstEquipId=82032,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82031,}
gdEquipUpgrade[82032] = {dstEquipId=82033,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82032,}
gdEquipUpgrade[82036] = {dstEquipId=82037,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82036,}
gdEquipUpgrade[82037] = {dstEquipId=82038,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82037,}
gdEquipUpgrade[82038] = {dstEquipId=82039,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82038,}
gdEquipUpgrade[82039] = {dstEquipId=82040,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82039,}
gdEquipUpgrade[82040] = {dstEquipId=82041,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82040,}
gdEquipUpgrade[82041] = {dstEquipId=82042,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82041,}
gdEquipUpgrade[82042] = {dstEquipId=82043,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82042,}
gdEquipUpgrade[82043] = {dstEquipId=82044,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82043,}
gdEquipUpgrade[82044] = {dstEquipId=82045,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=2,reqItemId=82044,}
gdEquipUpgrade[81156] = {dstEquipId=81157,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81157] = {dstEquipId=81158,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81158] = {dstEquipId=81159,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81159] = {dstEquipId=81160,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81160] = {dstEquipId=81161,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81161] = {dstEquipId=81162,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81162] = {dstEquipId=81163,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81163] = {dstEquipId=81164,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81164] = {dstEquipId=81165,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81167] = {dstEquipId=81168,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81168] = {dstEquipId=81169,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81169] = {dstEquipId=81170,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81170] = {dstEquipId=81171,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81171] = {dstEquipId=81172,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81172] = {dstEquipId=81173,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81173] = {dstEquipId=81174,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81174] = {dstEquipId=81175,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81175] = {dstEquipId=81176,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81222] = {dstEquipId=81223,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81223] = {dstEquipId=81224,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81224] = {dstEquipId=81225,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81225] = {dstEquipId=81226,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81226] = {dstEquipId=81227,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81227] = {dstEquipId=81228,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81228] = {dstEquipId=81229,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81229] = {dstEquipId=81230,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81230] = {dstEquipId=81231,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81233] = {dstEquipId=81234,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81234] = {dstEquipId=81235,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81235] = {dstEquipId=81236,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81236] = {dstEquipId=81237,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81237] = {dstEquipId=81238,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81238] = {dstEquipId=81239,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81239] = {dstEquipId=81240,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81240] = {dstEquipId=81241,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81241] = {dstEquipId=81242,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81244] = {dstEquipId=81245,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81245] = {dstEquipId=81246,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81246] = {dstEquipId=81247,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81247] = {dstEquipId=81248,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81248] = {dstEquipId=81249,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81249] = {dstEquipId=81250,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81250] = {dstEquipId=81251,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81251] = {dstEquipId=81252,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81252] = {dstEquipId=81253,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81255] = {dstEquipId=81256,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81256] = {dstEquipId=81257,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81257] = {dstEquipId=81258,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81258] = {dstEquipId=81259,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81259] = {dstEquipId=81260,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81260] = {dstEquipId=81261,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81261] = {dstEquipId=81262,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81262] = {dstEquipId=81263,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81263] = {dstEquipId=81264,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81266] = {dstEquipId=81267,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81267] = {dstEquipId=81268,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81268] = {dstEquipId=81269,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81269] = {dstEquipId=81270,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81270] = {dstEquipId=81271,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81271] = {dstEquipId=81272,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81272] = {dstEquipId=81273,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81273] = {dstEquipId=81274,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81274] = {dstEquipId=81275,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81277] = {dstEquipId=81278,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81278] = {dstEquipId=81279,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81279] = {dstEquipId=81280,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81280] = {dstEquipId=81281,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81281] = {dstEquipId=81282,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81282] = {dstEquipId=81283,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81283] = {dstEquipId=81284,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81284] = {dstEquipId=81285,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81285] = {dstEquipId=81286,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
--风华正茂(男)
gdEquipUpgrade[81294] = {dstEquipId=81295,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81295] = {dstEquipId=81296,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81296] = {dstEquipId=81297,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81297] = {dstEquipId=81298,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81298] = {dstEquipId=81299,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81299] = {dstEquipId=81300,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81300] = {dstEquipId=81301,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81301] = {dstEquipId=81302,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81302] = {dstEquipId=81303,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81303] = {dstEquipId=81304,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
--风华正茂(女)
gdEquipUpgrade[81305] = {dstEquipId=81306,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81306] = {dstEquipId=81307,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81307] = {dstEquipId=81308,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81308] = {dstEquipId=81309,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81309] = {dstEquipId=81310,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81310] = {dstEquipId=81311,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81311] = {dstEquipId=81312,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81312] = {dstEquipId=81313,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81313] = {dstEquipId=81314,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
gdEquipUpgrade[81314] = {dstEquipId=82315,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
--爱之火焰(男)
gdEquipUpgrade[81315] = {dstEquipId=81316,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81316] = {dstEquipId=81317,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81317] = {dstEquipId=81318,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81318] = {dstEquipId=81319,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81319] = {dstEquipId=81320,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81320] = {dstEquipId=81321,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81321] = {dstEquipId=81322,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81322] = {dstEquipId=81323,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81323] = {dstEquipId=81324,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}
--爱之火焰(女)
gdEquipUpgrade[81326] = {dstEquipId=81327,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=35,reqItemId=40000,}
gdEquipUpgrade[81327] = {dstEquipId=81328,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=20,reqItemId=40001,}
gdEquipUpgrade[81328] = {dstEquipId=81329,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=40,reqItemId=40001,}
gdEquipUpgrade[81329] = {dstEquipId=81330,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40001,}
gdEquipUpgrade[81330] = {dstEquipId=81331,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=40002,}
gdEquipUpgrade[81331] = {dstEquipId=81332,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40002,}
gdEquipUpgrade[81332] = {dstEquipId=81333,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40002,}
gdEquipUpgrade[81333] = {dstEquipId=81334,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=40003,}
gdEquipUpgrade[81334] = {dstEquipId=81335,reborncnt=0,rebornreq=0,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=40004,}






-- 装备投保配置数据
-- 格式: gdEquipToubao[装备SID] = {gold = 投保费用(仙玉)}
gdEquipToubao[60180] = {gold = 1000}  --浑天套投保
gdEquipToubao[60181] = {gold = 1000}  
gdEquipToubao[60182] = {gold = 1000} 
gdEquipToubao[60183] = {gold = 1000} 
gdEquipToubao[60184] = {gold = 1000} 
gdEquipToubao[60185] = {gold = 1000} 
gdEquipToubao[60186] = {gold = 1000} 
gdEquipToubao[60187] = {gold = 1000} 
gdEquipToubao[60188] = {gold = 1000} 
gdEquipToubao[60189] = {gold = 1000} 
--战士3套投保
gdEquipToubao[20080] = {gold = 1000} 
gdEquipToubao[20081] = {gold = 1000} 
gdEquipToubao[20082] = {gold = 1000} 
gdEquipToubao[20083] = {gold = 1000} 
gdEquipToubao[20084] = {gold = 1000} 
gdEquipToubao[20085] = {gold = 1000} 
gdEquipToubao[20086] = {gold = 1000} 
gdEquipToubao[20087] = {gold = 1000} 
gdEquipToubao[20088] = {gold = 1000} 
--战士4套投保
gdEquipToubao[20090] = {gold = 10000} 
gdEquipToubao[20091] = {gold = 10000} 
gdEquipToubao[20092] = {gold = 10000} 
gdEquipToubao[20093] = {gold = 10000} 
gdEquipToubao[20094] = {gold = 10000} 
gdEquipToubao[20095] = {gold = 10000} 
gdEquipToubao[20096] = {gold = 10000} 
gdEquipToubao[20097] = {gold = 10000} 
gdEquipToubao[20098] = {gold = 10000} 
--战士5套投保
gdEquipToubao[20100] = {gold = 20000} 
gdEquipToubao[20101] = {gold = 20000} 
gdEquipToubao[20102] = {gold = 20000} 
gdEquipToubao[20103] = {gold = 20000} 
gdEquipToubao[20104] = {gold = 20000} 
gdEquipToubao[20105] = {gold = 20000} 
gdEquipToubao[20106] = {gold = 20000} 
gdEquipToubao[20107] = {gold = 20000} 
gdEquipToubao[20108] = {gold = 20000} 
--战士6套投保
gdEquipToubao[20110] = {gold = 40000} 
gdEquipToubao[20111] = {gold = 40000} 
gdEquipToubao[20112] = {gold = 40000} 
gdEquipToubao[20113] = {gold = 40000} 
gdEquipToubao[20114] = {gold = 40000} 
gdEquipToubao[20115] = {gold = 40000} 
gdEquipToubao[20116] = {gold = 40000} 
gdEquipToubao[20117] = {gold = 40000} 
gdEquipToubao[20118] = {gold = 40000}
--战士7套投保
gdEquipToubao[20180] = {gold = 60000} 
gdEquipToubao[20181] = {gold = 60000} 
gdEquipToubao[20182] = {gold = 60000} 
gdEquipToubao[20183] = {gold = 60000} 
gdEquipToubao[20184] = {gold = 60000} 
gdEquipToubao[20185] = {gold = 60000} 
gdEquipToubao[20186] = {gold = 60000} 
gdEquipToubao[20187] = {gold = 60000} 
gdEquipToubao[20188] = {gold = 60000}
--战士8套投保
gdEquipToubao[20300] = {gold = 80000} 
gdEquipToubao[20301] = {gold = 80000} 
gdEquipToubao[20302] = {gold = 80000} 
gdEquipToubao[20303] = {gold = 80000} 
gdEquipToubao[20304] = {gold = 80000} 
gdEquipToubao[20305] = {gold = 80000} 
gdEquipToubao[20306] = {gold = 80000} 
gdEquipToubao[20307] = {gold = 80000} 
gdEquipToubao[20308] = {gold = 80000}
--战士9套投保
gdEquipToubao[20329] = {gold = 100000}
gdEquipToubao[20330] = {gold = 100000}
gdEquipToubao[20331] = {gold = 100000}
gdEquipToubao[20332] = {gold = 100000}
gdEquipToubao[20333] = {gold = 100000}
gdEquipToubao[20334] = {gold = 100000}
gdEquipToubao[20335] = {gold = 100000}
gdEquipToubao[20336] = {gold = 100000}
gdEquipToubao[20337] = {gold = 100000}
--战士10套投保
gdEquipToubao[20500] = {gold = 200000}
gdEquipToubao[20501] = {gold = 200000}
gdEquipToubao[20502] = {gold = 200000}
gdEquipToubao[20503] = {gold = 200000}
gdEquipToubao[20504] = {gold = 200000}
gdEquipToubao[20505] = {gold = 200000}
gdEquipToubao[20506] = {gold = 200000}
gdEquipToubao[20507] = {gold = 200000}
--战士11套投保
gdEquipToubao[20530] = {gold = 500000}
gdEquipToubao[20531] = {gold = 500000}
gdEquipToubao[20532] = {gold = 500000}
gdEquipToubao[20533] = {gold = 500000}
gdEquipToubao[20534] = {gold = 500000}
gdEquipToubao[20535] = {gold = 500000}
gdEquipToubao[20536] = {gold = 500000}
gdEquipToubao[20537] = {gold = 500000}
--暗影猩红战士套投保
gdEquipToubao[20640] = {gold = 1000000}
gdEquipToubao[20641] = {gold = 1000000}
gdEquipToubao[20642] = {gold = 1000000}
gdEquipToubao[20643] = {gold = 1000000}
gdEquipToubao[20644] = {gold = 1000000}
gdEquipToubao[20645] = {gold = 1000000}
gdEquipToubao[20646] = {gold = 1000000}
gdEquipToubao[20647] = {gold = 1000000}
gdEquipToubao[20648] = {gold = 1000000}

--法师3套投保
gdEquipToubao[20140] = {gold = 1000} 
gdEquipToubao[20141] = {gold = 1000} 
gdEquipToubao[20142] = {gold = 1000} 
gdEquipToubao[20143] = {gold = 1000} 
gdEquipToubao[20144] = {gold = 1000} 
gdEquipToubao[20145] = {gold = 1000} 
gdEquipToubao[20146] = {gold = 1000} 
gdEquipToubao[20147] = {gold = 1000} 
gdEquipToubao[20148] = {gold = 1000} 
--法师4套投保
gdEquipToubao[20150] = {gold = 10000} 
gdEquipToubao[20151] = {gold = 10000} 
gdEquipToubao[20152] = {gold = 10000} 
gdEquipToubao[20153] = {gold = 10000} 
gdEquipToubao[20154] = {gold = 10000} 
gdEquipToubao[20155] = {gold = 10000} 
gdEquipToubao[20156] = {gold = 10000} 
gdEquipToubao[20157] = {gold = 10000} 
gdEquipToubao[20158] = {gold = 10000} 
--法师5套投保
gdEquipToubao[20160] = {gold = 20000}
gdEquipToubao[20161] = {gold = 20000}
gdEquipToubao[20162] = {gold = 20000}
gdEquipToubao[20163] = {gold = 20000}
gdEquipToubao[20164] = {gold = 20000}
gdEquipToubao[20165] = {gold = 20000}
gdEquipToubao[20166] = {gold = 20000}
gdEquipToubao[20167] = {gold = 20000}
gdEquipToubao[20168] = {gold = 20000}
--法师6套投保
gdEquipToubao[20170] = {gold = 40000}
gdEquipToubao[20171] = {gold = 40000}
gdEquipToubao[20172] = {gold = 40000}
gdEquipToubao[20173] = {gold = 40000}
gdEquipToubao[20174] = {gold = 40000}
gdEquipToubao[20175] = {gold = 40000}
gdEquipToubao[20176] = {gold = 40000}
gdEquipToubao[20177] = {gold = 40000}
gdEquipToubao[20178] = {gold = 40000}
--法师7套投保
gdEquipToubao[20190] = {gold = 60000}
gdEquipToubao[20191] = {gold = 60000}
gdEquipToubao[20192] = {gold = 60000}
gdEquipToubao[20193] = {gold = 60000}
gdEquipToubao[20194] = {gold = 60000}
gdEquipToubao[20195] = {gold = 60000}
gdEquipToubao[20196] = {gold = 60000}
gdEquipToubao[20197] = {gold = 60000}
gdEquipToubao[20198] = {gold = 60000}
--法师8套投保
gdEquipToubao[20310] = {gold = 80000}
gdEquipToubao[20311] = {gold = 80000}
gdEquipToubao[20312] = {gold = 80000}
gdEquipToubao[20313] = {gold = 80000}
gdEquipToubao[20314] = {gold = 80000}
gdEquipToubao[20315] = {gold = 80000}
gdEquipToubao[20316] = {gold = 80000}
gdEquipToubao[20317] = {gold = 80000}
gdEquipToubao[20318] = {gold = 80000}
--法师9套投保 
gdEquipToubao[20338] = {gold = 100000}
gdEquipToubao[20339] = {gold = 100000}
gdEquipToubao[20340] = {gold = 100000}
gdEquipToubao[20341] = {gold = 100000}
gdEquipToubao[20342] = {gold = 100000}
gdEquipToubao[20343] = {gold = 100000}
gdEquipToubao[20344] = {gold = 100000}
gdEquipToubao[20345] = {gold = 100000}
gdEquipToubao[20346] = {gold = 100000}
--法师10套投保 
gdEquipToubao[20510] = {gold = 200000}
gdEquipToubao[20511] = {gold = 200000}
gdEquipToubao[20512] = {gold = 200000}
gdEquipToubao[20513] = {gold = 200000}
gdEquipToubao[20514] = {gold = 200000}
gdEquipToubao[20515] = {gold = 200000}
gdEquipToubao[20516] = {gold = 200000}
gdEquipToubao[20517] = {gold = 200000}
gdEquipToubao[20518] = {gold = 200000}
--法师11套投保 
gdEquipToubao[20540] = {gold = 500000}
gdEquipToubao[20541] = {gold = 500000}
gdEquipToubao[20542] = {gold = 500000}
gdEquipToubao[20543] = {gold = 500000}
gdEquipToubao[20544] = {gold = 500000}
gdEquipToubao[20545] = {gold = 500000}
gdEquipToubao[20546] = {gold = 500000}
gdEquipToubao[20547] = {gold = 500000}
gdEquipToubao[20548] = {gold = 500000}
--暗影猩蓝法师套投保
gdEquipToubao[20670] = {gold = 1000000}
gdEquipToubao[20671] = {gold = 1000000}
gdEquipToubao[20672] = {gold = 1000000}
gdEquipToubao[20673] = {gold = 1000000}
gdEquipToubao[20674] = {gold = 1000000}
gdEquipToubao[20675] = {gold = 1000000}
gdEquipToubao[20676] = {gold = 1000000}
gdEquipToubao[20677] = {gold = 1000000}
gdEquipToubao[20678] = {gold = 1000000}

--道士3套投保
gdEquipToubao[20020] = {gold = 1000} 
gdEquipToubao[20021] = {gold = 1000} 
gdEquipToubao[20022] = {gold = 1000} 
gdEquipToubao[20023] = {gold = 1000} 
gdEquipToubao[20024] = {gold = 1000} 
gdEquipToubao[20025] = {gold = 1000} 
gdEquipToubao[20026] = {gold = 1000} 
gdEquipToubao[20027] = {gold = 1000} 
gdEquipToubao[20028] = {gold = 1000} 
--道士4套投保
gdEquipToubao[20030] = {gold = 10000} 
gdEquipToubao[20031] = {gold = 10000}
gdEquipToubao[20032] = {gold = 10000}
gdEquipToubao[20033] = {gold = 10000}
gdEquipToubao[20034] = {gold = 10000}
gdEquipToubao[20035] = {gold = 10000}
gdEquipToubao[20036] = {gold = 10000}
gdEquipToubao[20037] = {gold = 10000}
gdEquipToubao[20038] = {gold = 10000}
--道士5套投保
gdEquipToubao[20040] = {gold = 20000}
gdEquipToubao[20041] = {gold = 20000}
gdEquipToubao[20042] = {gold = 20000}
gdEquipToubao[20043] = {gold = 20000}
gdEquipToubao[20044] = {gold = 20000}
gdEquipToubao[20045] = {gold = 20000}
gdEquipToubao[20046] = {gold = 20000}
gdEquipToubao[20047] = {gold = 20000}
gdEquipToubao[20048] = {gold = 20000}
--道士6套投保
gdEquipToubao[20050] = {gold = 40000}
gdEquipToubao[20051] = {gold = 40000}
gdEquipToubao[20052] = {gold = 40000}
gdEquipToubao[20053] = {gold = 40000}
gdEquipToubao[20054] = {gold = 40000}
gdEquipToubao[20055] = {gold = 40000}
gdEquipToubao[20056] = {gold = 40000}
gdEquipToubao[20057] = {gold = 40000}
gdEquipToubao[20058] = {gold = 40000}
--道士7套投保
gdEquipToubao[20200] = {gold = 60000}
gdEquipToubao[20201] = {gold = 60000}
gdEquipToubao[20202] = {gold = 60000}
gdEquipToubao[20203] = {gold = 60000}
gdEquipToubao[20204] = {gold = 60000}
gdEquipToubao[20205] = {gold = 60000}
gdEquipToubao[20206] = {gold = 60000}
gdEquipToubao[20207] = {gold = 60000}
gdEquipToubao[20208] = {gold = 60000}
--道士8套投保
gdEquipToubao[20320] = {gold = 80000}
gdEquipToubao[20321] = {gold = 80000}
gdEquipToubao[20322] = {gold = 80000}
gdEquipToubao[20323] = {gold = 80000}
gdEquipToubao[20324] = {gold = 80000}
gdEquipToubao[20325] = {gold = 80000}
gdEquipToubao[20326] = {gold = 80000}
gdEquipToubao[20327] = {gold = 80000}
gdEquipToubao[20328] = {gold = 80000}
--道士9套投保
gdEquipToubao[20347] = {gold = 100000}
gdEquipToubao[20348] = {gold = 100000}
gdEquipToubao[20349] = {gold = 100000}
gdEquipToubao[20350] = {gold = 100000}
gdEquipToubao[20351] = {gold = 100000}
gdEquipToubao[20352] = {gold = 100000}
gdEquipToubao[20353] = {gold = 100000}
gdEquipToubao[20354] = {gold = 100000}
gdEquipToubao[20355] = {gold = 100000}
--道士10套投保
gdEquipToubao[20520] = {gold = 200000}
gdEquipToubao[20521] = {gold = 200000}
gdEquipToubao[20522] = {gold = 200000}
gdEquipToubao[20523] = {gold = 200000}
gdEquipToubao[20524] = {gold = 200000}
gdEquipToubao[20525] = {gold = 200000}
gdEquipToubao[20526] = {gold = 200000}
gdEquipToubao[20527] = {gold = 200000}
gdEquipToubao[20528] = {gold = 200000}
--道士11套投保
gdEquipToubao[20550] = {gold = 500000}
gdEquipToubao[20551] = {gold = 500000}
gdEquipToubao[20552] = {gold = 500000}
gdEquipToubao[20553] = {gold = 500000}
gdEquipToubao[20554] = {gold = 500000}
gdEquipToubao[20555] = {gold = 500000}
gdEquipToubao[20556] = {gold = 500000}
gdEquipToubao[20557] = {gold = 500000}
gdEquipToubao[20558] = {gold = 500000}
--暗影猩红道士套投保
gdEquipToubao[20660] = {gold = 1000000}
gdEquipToubao[20661] = {gold = 1000000}
gdEquipToubao[20662] = {gold = 1000000}
gdEquipToubao[20663] = {gold = 1000000}
gdEquipToubao[20664] = {gold = 1000000}
gdEquipToubao[20665] = {gold = 1000000}
gdEquipToubao[20666] = {gold = 1000000}
gdEquipToubao[20667] = {gold = 1000000}
gdEquipToubao[20668] = {gold = 1000000}
--暗影散装投保
gdEquipToubao[60230] = {gold = 1000000}
gdEquipToubao[60238] = {gold = 1000000}
gdEquipToubao[60246] = {gold = 1000000}
gdEquipToubao[20559] = {gold = 1000000}

gdEquipEnhance[0] = {
	bestPropRate=0,
	dstLevel=1,
	enhanceValue=2,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=500,
	reqItemCnt=2,
	reqItemId=40008,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[1] = {
	bestPropRate=0,
	dstLevel=2,
	enhanceValue=4,
	levelup=0,
	lvDownMax=1,
	lvDownMin=1,
	reqGold=500,
	reqItemCnt=4,
	reqItemId=40008,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=1,
	successRate=80,
}
gdEquipEnhance[2] = {
	bestPropRate=0,
	dstLevel=3,
	enhanceValue=7,
	levelup=0,
	lvDownMax=2,
	lvDownMin=1,
	reqGold=500,
	reqItemCnt=6,
	reqItemId=40008,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=3,
	successRate=70,
}
gdEquipEnhance[3] = {
	bestPropRate=0,
	dstLevel=4,
	enhanceValue=11,
	levelup=0,
	lvDownMax=3,
	lvDownMin=1,
	reqGold=1500,
	reqItemCnt=4,
	reqItemId=40009,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=6,
	successRate=60,
}
gdEquipEnhance[4] = {
	bestPropRate=0,
	dstLevel=5,
	enhanceValue=16,
	levelup=0,
	lvDownMax=3,
	lvDownMin=1,
	reqGold=1500,
	reqItemCnt=6,
	reqItemId=40009,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=10,
	successRate=60,
}
gdEquipEnhance[5] = {
	bestPropRate=0,
	dstLevel=6,
	enhanceValue=22,
	levelup=0,
	lvDownMax=3,
	lvDownMin=1,
	reqGold=1500,
	reqItemCnt=8,
	reqItemId=40009,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=15,
	successRate=55,
}
gdEquipEnhance[6] = {
	bestPropRate=0,
	dstLevel=7,
	enhanceValue=29,
	levelup=0,
	lvDownMax=3,
	lvDownMin=1,
	reqGold=1500,
	reqItemCnt=10,
	reqItemId=40009,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=20,
	successRate=55,
}
gdEquipEnhance[7] = {
	bestPropRate=10,
	dstLevel=8,
	enhanceValue=37,
	levelup=0,
	lvDownMax=3,
	lvDownMin=1,
	reqGold=3000,
	reqItemCnt=6,
	reqItemId=40010,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=25,
	successRate=50,
}
gdEquipEnhance[8] = {
	bestPropRate=10,
	dstLevel=9,
	enhanceValue=55,
	levelup=0,
	lvDownMax=3,
	lvDownMin=1,
	reqGold=3000,
	reqItemCnt=8,
	reqItemId=40010,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=30,
	successRate=50,
}
gdEquipEnhance[9] = {
	bestPropRate=10,
	dstLevel=10,
	enhanceValue=75,
	levelup=0,
	lvDownMax=3,
	lvDownMin=1,
	reqGold=3000,
	reqItemCnt=10,
	reqItemId=40010,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=35,
	successRate=50,
}
gdEquipEnhance[10] = {
	bestPropRate=11,
	dstLevel=11,
	enhanceValue=100,
	levelup=20,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=40,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[11] = {
	bestPropRate=12,
	dstLevel=12,
	enhanceValue=130,
	levelup=10,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=70,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[12] = {
	bestPropRate=13,
	dstLevel=13,
	enhanceValue=165,
	levelup=5,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=100,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[13] = {
	bestPropRate=14,
	dstLevel=14,
	enhanceValue=205,
	levelup=3,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=130,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[14] = {
	bestPropRate=15,
	dstLevel=15,
	enhanceValue=250,
	levelup=1,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=160,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[15] = {
	bestPropRate=16,
	dstLevel=16,
	enhanceValue=300,
	levelup=1,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=180,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[16] = {
	bestPropRate=17,
	dstLevel=17,
	enhanceValue=370,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=210,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[17] = {
	bestPropRate=18,
	dstLevel=18,
	enhanceValue=450,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=240,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[18] = {
	bestPropRate=19,
	dstLevel=19,
	enhanceValue=540,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=270,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[19] = {
	bestPropRate=20,
	dstLevel=20,
	enhanceValue=650,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=300,
	reqItemId=40011,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[20] = {
	bestPropRate=21,
	dstLevel=21,
	enhanceValue=740,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=40,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[21] = {
	bestPropRate=22,
	dstLevel=22,
	enhanceValue=850,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=70,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[22] = {
	bestPropRate=23,
	dstLevel=23,
	enhanceValue=940,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=100,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[23] = {
	bestPropRate=24,
	dstLevel=24,
	enhanceValue=1050,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=130,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[24] = {
	bestPropRate=25,
	dstLevel=25,
	enhanceValue=1140,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=160,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[25] = {
	bestPropRate=26,
	dstLevel=26,
	enhanceValue=1250,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=180,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[26] = {
	bestPropRate=27,
	dstLevel=27,
	enhanceValue=1340,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=210,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[27] = {
	bestPropRate=28,
	dstLevel=28,
	enhanceValue=1450,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=240,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[28] = {
	bestPropRate=29,
	dstLevel=29,
	enhanceValue=1540,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=270,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[29] = {
	bestPropRate=30,
	dstLevel=30,
	enhanceValue=1650,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=300,
	reqItemId=41110,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
} 
gdEquipEnhance[30] = {
	bestPropRate=31,
	dstLevel=31,
	enhanceValue=1740,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=40,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[31] = {
	bestPropRate=32,
	dstLevel=32,
	enhanceValue=1850,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=70,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[32] = {
	bestPropRate=33,
	dstLevel=33,
	enhanceValue=1940,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=100,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[33] = {
	bestPropRate=34,
	dstLevel=34,
	enhanceValue=2050,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=130,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[34] = {
	bestPropRate=35,
	dstLevel=35,
	enhanceValue=2140,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=160,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[35] = {
	bestPropRate=36,
	dstLevel=36,
	enhanceValue=2250,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=180,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[36] = {
	bestPropRate=37,
	dstLevel=37,
	enhanceValue=2340,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=210,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[37] = {
	bestPropRate=38,
	dstLevel=38,
	enhanceValue=2450,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=240,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[38] = {
	bestPropRate=39,
	dstLevel=39,
	enhanceValue=2540,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=270,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[39] = {
	bestPropRate=40,
	dstLevel=40,
	enhanceValue=2650,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=300,
	reqItemId=41111,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
} 
gdEquipEnhance[40] = {
	bestPropRate=41,
	dstLevel=41,
	enhanceValue=2740,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=40,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[41] = {
	bestPropRate=42,
	dstLevel=42,
	enhanceValue=2850,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=70,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[42] = {
	bestPropRate=43,
	dstLevel=43,
	enhanceValue=2940,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=100,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[43] = {
	bestPropRate=44,
	dstLevel=44,
	enhanceValue=3050,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=130,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[44] = {
	bestPropRate=45,
	dstLevel=45,
	enhanceValue=3140,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=160,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[45] = {
	bestPropRate=46,
	dstLevel=46,
	enhanceValue=3250,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=180,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[46] = {
	bestPropRate=47,
	dstLevel=47,
	enhanceValue=3340,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=210,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[47] = {
	bestPropRate=48,
	dstLevel=48,
	enhanceValue=3450,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=240,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[48] = {
	bestPropRate=49,
	dstLevel=49,
	enhanceValue=3540,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=270,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
}
gdEquipEnhance[49] = {
	bestPropRate=50,
	dstLevel=50,
	enhanceValue=3650,
	levelup=0,
	lvDownMax=0,
	lvDownMin=0,
	reqGold=3000,
	reqItemCnt=300,
	reqItemId=41112,
	reqItemLv=0,
	reqPoints=0,
	reqProtect=0,
	successRate=100,
} 
gdEquipEvaluate[1] = {
	name="最小物理攻击",
	attr= {
			[1]= {maxValue=11,maxlimit=20,minValue=3,minlimit=0,},
			[2]= {maxValue=18,maxlimit=40,minValue=4,minlimit=21,},
			[3]= {maxValue=25,maxlimit=60,minValue=5,minlimit=41,},
			[4]= {maxValue=30,maxlimit=80,minValue=7,minlimit=61,},
			[5]= {maxValue=30,maxlimit=100,minValue=9,minlimit=81,},
			[6]= {maxValue=30,maxlimit=120,minValue=11,minlimit=101,},
			[7]= {maxValue=30,maxlimit=140,minValue=13,minlimit=121,},
			[8]= {maxValue=30,maxlimit=160,minValue=15,minlimit=141,},
			[9]= {maxValue=30,maxlimit=180,minValue=18,minlimit=161,},
			[10]= {maxValue=30,maxlimit=200,minValue=21,minlimit=181,},
			[11]= {maxValue=30,maxlimit=-1,minValue=24,minlimit=201,},
		},
	attrtype=5,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[2] = {
	name="最小道术攻击",
	attr= {
			[1]= {maxValue=11,maxlimit=20,minValue=3,minlimit=0,},
			[2]= {maxValue=18,maxlimit=40,minValue=4,minlimit=21,},
			[3]= {maxValue=25,maxlimit=60,minValue=5,minlimit=41,},
			[4]= {maxValue=30,maxlimit=80,minValue=7,minlimit=61,},
			[5]= {maxValue=30,maxlimit=100,minValue=9,minlimit=81,},
			[6]= {maxValue=30,maxlimit=120,minValue=11,minlimit=101,},
			[7]= {maxValue=30,maxlimit=140,minValue=13,minlimit=121,},
			[8]= {maxValue=30,maxlimit=160,minValue=15,minlimit=141,},
			[9]= {maxValue=30,maxlimit=180,minValue=18,minlimit=161,},
			[10]= {maxValue=30,maxlimit=200,minValue=21,minlimit=181,},
			[11]= {maxValue=30,maxlimit=-1,minValue=24,minlimit=201,},
		},
	attrtype=9,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[3] = {
	name="最小魔法攻击",
	attr= {
			[1]= {maxValue=11,maxlimit=20,minValue=3,minlimit=0,},
			[2]= {maxValue=18,maxlimit=40,minValue=4,minlimit=21,},
			[3]= {maxValue=25,maxlimit=60,minValue=5,minlimit=41,},
			[4]= {maxValue=30,maxlimit=80,minValue=7,minlimit=61,},
			[5]= {maxValue=30,maxlimit=100,minValue=9,minlimit=81,},
			[6]= {maxValue=30,maxlimit=120,minValue=11,minlimit=101,},
			[7]= {maxValue=30,maxlimit=140,minValue=13,minlimit=121,},
			[8]= {maxValue=30,maxlimit=160,minValue=15,minlimit=141,},
			[9]= {maxValue=30,maxlimit=180,minValue=18,minlimit=161,},
			[10]= {maxValue=30,maxlimit=200,minValue=21,minlimit=181,},
			[11]= {maxValue=30,maxlimit=-1,minValue=24,minlimit=201,},
		},
	attrtype=7,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[4] = {
	name="最大物理攻击",
	attr= {
			[1]= {maxValue=11,maxlimit=20,minValue=3,minlimit=0,},
			[2]= {maxValue=18,maxlimit=40,minValue=4,minlimit=21,},
			[3]= {maxValue=25,maxlimit=60,minValue=5,minlimit=41,},
			[4]= {maxValue=30,maxlimit=80,minValue=7,minlimit=61,},
			[5]= {maxValue=30,maxlimit=100,minValue=9,minlimit=81,},
			[6]= {maxValue=30,maxlimit=120,minValue=11,minlimit=101,},
			[7]= {maxValue=30,maxlimit=140,minValue=13,minlimit=121,},
			[8]= {maxValue=30,maxlimit=160,minValue=15,minlimit=141,},
			[9]= {maxValue=30,maxlimit=180,minValue=18,minlimit=161,},
			[10]= {maxValue=30,maxlimit=200,minValue=21,minlimit=181,},
			[11]= {maxValue=30,maxlimit=-1,minValue=24,minlimit=201,},
		},
	attrtype=6,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[5] = {
	name="最大道术攻击",
	attr= {
			[1]= {maxValue=11,maxlimit=20,minValue=3,minlimit=0,},
			[2]= {maxValue=18,maxlimit=40,minValue=4,minlimit=21,},
			[3]= {maxValue=25,maxlimit=60,minValue=5,minlimit=41,},
			[4]= {maxValue=30,maxlimit=80,minValue=7,minlimit=61,},
			[5]= {maxValue=30,maxlimit=100,minValue=9,minlimit=81,},
			[6]= {maxValue=30,maxlimit=120,minValue=11,minlimit=101,},
			[7]= {maxValue=30,maxlimit=140,minValue=13,minlimit=121,},
			[8]= {maxValue=30,maxlimit=160,minValue=15,minlimit=141,},
			[9]= {maxValue=30,maxlimit=180,minValue=18,minlimit=161,},
			[10]= {maxValue=30,maxlimit=200,minValue=21,minlimit=181,},
			[11]= {maxValue=30,maxlimit=-1,minValue=24,minlimit=201,},
		},
	attrtype=10,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[6] = {
	name="最大魔法攻击",
	attr= {
			[1]= {maxValue=11,maxlimit=20,minValue=3,minlimit=0,},
			[2]= {maxValue=18,maxlimit=40,minValue=4,minlimit=21,},
			[3]= {maxValue=25,maxlimit=60,minValue=5,minlimit=41,},
			[4]= {maxValue=30,maxlimit=80,minValue=7,minlimit=61,},
			[5]= {maxValue=30,maxlimit=100,minValue=9,minlimit=81,},
			[6]= {maxValue=30,maxlimit=120,minValue=11,minlimit=101,},
			[7]= {maxValue=30,maxlimit=140,minValue=13,minlimit=121,},
			[8]= {maxValue=30,maxlimit=160,minValue=15,minlimit=141,},
			[9]= {maxValue=30,maxlimit=180,minValue=18,minlimit=161,},
			[10]= {maxValue=30,maxlimit=200,minValue=21,minlimit=181,},
			[11]= {maxValue=30,maxlimit=-1,minValue=24,minlimit=201,},
		},
	attrtype=8,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[7] = {
	name="最小物理防御",
	attr= {
			[1]= {maxValue=6,maxlimit=20,minValue=2,minlimit=0,},
			[2]= {maxValue=8,maxlimit=40,minValue=2,minlimit=21,},
			[3]= {maxValue=12,maxlimit=60,minValue=3,minlimit=41,},
			[4]= {maxValue=15,maxlimit=80,minValue=4,minlimit=61,},
			[5]= {maxValue=15,maxlimit=100,minValue=5,minlimit=81,},
			[6]= {maxValue=15,maxlimit=120,minValue=6,minlimit=101,},
			[7]= {maxValue=15,maxlimit=140,minValue=7,minlimit=121,},
			[8]= {maxValue=15,maxlimit=160,minValue=8,minlimit=141,},
			[9]= {maxValue=15,maxlimit=180,minValue=9,minlimit=161,},
			[10]= {maxValue=15,maxlimit=200,minValue=10,minlimit=181,},
			[11]= {maxValue=15,maxlimit=-1,minValue=11,minlimit=201,},
		},
	attrtype=11,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[8] = {
	name="最大物理防御",
	attr= {
			[1]= {maxValue=6,maxlimit=20,minValue=2,minlimit=0,},
			[2]= {maxValue=8,maxlimit=40,minValue=2,minlimit=21,},
			[3]= {maxValue=12,maxlimit=60,minValue=3,minlimit=41,},
			[4]= {maxValue=15,maxlimit=80,minValue=4,minlimit=61,},
			[5]= {maxValue=15,maxlimit=100,minValue=5,minlimit=81,},
			[6]= {maxValue=15,maxlimit=120,minValue=6,minlimit=101,},
			[7]= {maxValue=15,maxlimit=140,minValue=7,minlimit=121,},
			[8]= {maxValue=15,maxlimit=160,minValue=8,minlimit=141,},
			[9]= {maxValue=15,maxlimit=180,minValue=9,minlimit=161,},
			[10]= {maxValue=15,maxlimit=200,minValue=10,minlimit=181,},
			[11]= {maxValue=15,maxlimit=-1,minValue=11,minlimit=201,},
		},
	attrtype=12,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[9] = {
	name="最小魔法防御",
	attr= {
			[1]= {maxValue=6,maxlimit=20,minValue=2,minlimit=0,},
			[2]= {maxValue=8,maxlimit=40,minValue=2,minlimit=21,},
			[3]= {maxValue=12,maxlimit=60,minValue=3,minlimit=41,},
			[4]= {maxValue=15,maxlimit=80,minValue=4,minlimit=61,},
			[5]= {maxValue=15,maxlimit=100,minValue=5,minlimit=81,},
			[6]= {maxValue=15,maxlimit=120,minValue=6,minlimit=101,},
			[7]= {maxValue=15,maxlimit=140,minValue=7,minlimit=121,},
			[8]= {maxValue=15,maxlimit=160,minValue=8,minlimit=141,},
			[9]= {maxValue=15,maxlimit=180,minValue=9,minlimit=161,},
			[10]= {maxValue=15,maxlimit=200,minValue=10,minlimit=181,},
			[11]= {maxValue=15,maxlimit=-1,minValue=11,minlimit=201,},
		},
	attrtype=13,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[10] = {
	name="最大魔法防御",
	attr= {
			[1]= {maxValue=6,maxlimit=20,minValue=2,minlimit=0,},
			[2]= {maxValue=8,maxlimit=40,minValue=2,minlimit=21,},
			[3]= {maxValue=12,maxlimit=60,minValue=3,minlimit=41,},
			[4]= {maxValue=15,maxlimit=80,minValue=4,minlimit=61,},
			[5]= {maxValue=15,maxlimit=100,minValue=5,minlimit=81,},
			[6]= {maxValue=15,maxlimit=120,minValue=6,minlimit=101,},
			[7]= {maxValue=15,maxlimit=140,minValue=7,minlimit=121,},
			[8]= {maxValue=15,maxlimit=160,minValue=8,minlimit=141,},
			[9]= {maxValue=15,maxlimit=180,minValue=9,minlimit=161,},
			[10]= {maxValue=15,maxlimit=200,minValue=10,minlimit=181,},
			[11]= {maxValue=15,maxlimit=-1,minValue=11,minlimit=201,},
		},
	attrtype=14,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[11] = {
	name="毒物恢复",
	attr= {
			[1]= {maxValue=180,maxlimit=20,minValue=50,minlimit=0,},
			[2]= {maxValue=250,maxlimit=40,minValue=60,minlimit=21,},
			[3]= {maxValue=360,maxlimit=60,minValue=80,minlimit=41,},
			[4]= {maxValue=500,maxlimit=80,minValue=100,minlimit=61,},
			[5]= {maxValue=500,maxlimit=100,minValue=120,minlimit=81,},
			[6]= {maxValue=500,maxlimit=120,minValue=140,minlimit=101,},
			[7]= {maxValue=500,maxlimit=140,minValue=170,minlimit=121,},
			[8]= {maxValue=500,maxlimit=160,minValue=210,minlimit=141,},
			[9]= {maxValue=500,maxlimit=180,minValue=250,minlimit=161,},
			[10]= {maxValue=500,maxlimit=200,minValue=300,minlimit=181,},
			[11]= {maxValue=500,maxlimit=-1,minValue=350,minlimit=201,},
		},
	attrtype=22,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[12] = {
	name="生命恢复",
	attr= {
			[1]= {maxValue=400,maxlimit=20,minValue=70,minlimit=0,},
			[2]= {maxValue=600,maxlimit=40,minValue=100,minlimit=21,},
			[3]= {maxValue=730,maxlimit=60,minValue=130,minlimit=41,},
			[4]= {maxValue=1000,maxlimit=80,minValue=160,minlimit=61,},
			[5]= {maxValue=1000,maxlimit=100,minValue=200,minlimit=81,},
			[6]= {maxValue=1000,maxlimit=120,minValue=250,minlimit=101,},
			[7]= {maxValue=1000,maxlimit=140,minValue=320,minlimit=121,},
			[8]= {maxValue=1000,maxlimit=160,minValue=400,minlimit=141,},
			[9]= {maxValue=1000,maxlimit=180,minValue=500,minlimit=161,},
			[10]= {maxValue=1000,maxlimit=200,minValue=600,minlimit=181,},
			[11]= {maxValue=1000,maxlimit=-1,minValue=700,minlimit=201,},
		},
	attrtype=15,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[14] = {
	name="魔法恢复",
	attr= {
			[1]= {maxValue=400,maxlimit=20,minValue=70,minlimit=0,},
			[2]= {maxValue=600,maxlimit=40,minValue=100,minlimit=21,},
			[3]= {maxValue=730,maxlimit=60,minValue=130,minlimit=41,},
			[4]= {maxValue=1000,maxlimit=80,minValue=160,minlimit=61,},
			[5]= {maxValue=1000,maxlimit=100,minValue=200,minlimit=81,},
			[6]= {maxValue=1000,maxlimit=120,minValue=250,minlimit=101,},
			[7]= {maxValue=1000,maxlimit=140,minValue=320,minlimit=121,},
			[8]= {maxValue=1000,maxlimit=160,minValue=400,minlimit=141,},
			[9]= {maxValue=1000,maxlimit=180,minValue=500,minlimit=161,},
			[10]= {maxValue=1000,maxlimit=200,minValue=600,minlimit=181,},
			[11]= {maxValue=1000,maxlimit=-1,minValue=700,minlimit=201,},
		},
	attrtype=16,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[13] = {
	name="魔法命中",
	attr= {
			[1]= {maxValue=180,maxlimit=20,minValue=50,minlimit=0,},
			[2]= {maxValue=250,maxlimit=40,minValue=60,minlimit=21,},
			[3]= {maxValue=360,maxlimit=60,minValue=80,minlimit=41,},
			[4]= {maxValue=500,maxlimit=80,minValue=100,minlimit=61,},
			[5]= {maxValue=500,maxlimit=100,minValue=120,minlimit=81,},
			[6]= {maxValue=500,maxlimit=120,minValue=140,minlimit=101,},
			[7]= {maxValue=500,maxlimit=140,minValue=170,minlimit=121,},
			[8]= {maxValue=500,maxlimit=160,minValue=210,minlimit=141,},
			[9]= {maxValue=500,maxlimit=180,minValue=250,minlimit=161,},
			[10]= {maxValue=500,maxlimit=200,minValue=300,minlimit=181,},
			[11]= {maxValue=500,maxlimit=-1,minValue=350,minlimit=201,},
		},
	attrtype=19,
	canSame=0,
	reqGold=1000,
}
gdEquipEvaluate[15] = {
	name="魔法闪避",
	attr= {
			[1]= {maxValue=180,maxlimit=20,minValue=50,minlimit=0,},
			[2]= {maxValue=250,maxlimit=40,minValue=60,minlimit=21,},
			[3]= {maxValue=360,maxlimit=60,minValue=80,minlimit=41,},
			[4]= {maxValue=500,maxlimit=80,minValue=100,minlimit=61,},
			[5]= {maxValue=500,maxlimit=100,minValue=120,minlimit=81,},
			[6]= {maxValue=500,maxlimit=120,minValue=140,minlimit=101,},
			[7]= {maxValue=500,maxlimit=140,minValue=170,minlimit=121,},
			[8]= {maxValue=500,maxlimit=160,minValue=210,minlimit=141,},
			[9]= {maxValue=500,maxlimit=180,minValue=250,minlimit=161,},
			[10]= {maxValue=500,maxlimit=200,minValue=300,minlimit=181,},
			[11]= {maxValue=500,maxlimit=-1,minValue=350,minlimit=201,},
		},
	attrtype=20,
	canSame=0,
	reqGold=1000,
}
gdEquipEvaluate[16] = {
	name="毒物闪避",
	attr= {
			[1]= {maxValue=180,maxlimit=20,minValue=50,minlimit=0,},
			[2]= {maxValue=250,maxlimit=40,minValue=60,minlimit=21,},
			[3]= {maxValue=360,maxlimit=60,minValue=80,minlimit=41,},
			[4]= {maxValue=500,maxlimit=80,minValue=100,minlimit=61,},
			[5]= {maxValue=500,maxlimit=100,minValue=120,minlimit=81,},
			[6]= {maxValue=500,maxlimit=120,minValue=140,minlimit=101,},
			[7]= {maxValue=500,maxlimit=140,minValue=170,minlimit=121,},
			[8]= {maxValue=500,maxlimit=160,minValue=210,minlimit=141,},
			[9]= {maxValue=500,maxlimit=180,minValue=250,minlimit=161,},
			[10]= {maxValue=500,maxlimit=200,minValue=300,minlimit=181,},
			[11]= {maxValue=500,maxlimit=-1,minValue=350,minlimit=201,},
		},
	attrtype=21,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[17] = {
	name="神圣",
	attr= {
			[1]= {maxValue=18,maxlimit=20,minValue=5,minlimit=0,},
			[2]= {maxValue=24,maxlimit=40,minValue=7,minlimit=21,},
			[3]= {maxValue=36,maxlimit=60,minValue=9,minlimit=41,},
			[4]= {maxValue=50,maxlimit=80,minValue=12,minlimit=61,},
			[5]= {maxValue=50,maxlimit=100,minValue=15,minlimit=81,},
			[6]= {maxValue=50,maxlimit=120,minValue=18,minlimit=101,},
			[7]= {maxValue=50,maxlimit=140,minValue=21,minlimit=121,},
			[8]= {maxValue=50,maxlimit=160,minValue=25,minlimit=141,},
			[9]= {maxValue=50,maxlimit=180,minValue=29,minlimit=161,},
			[10]= {maxValue=50,maxlimit=200,minValue=33,minlimit=181,},
			[11]= {maxValue=50,maxlimit=-1,minValue=38,minlimit=201,},
		},
	attrtype=27,
	canSame=1,
	reqGold=1000,
}
gdEquipEvaluate[18] = {
	name="准确",
	attr= {
			[1]= {maxValue=1,maxlimit=20,minValue=1,minlimit=0,},
			[2]= {maxValue=1,maxlimit=40,minValue=1,minlimit=21,},
			[3]= {maxValue=1,maxlimit=60,minValue=1,minlimit=41,},
			[4]= {maxValue=2,maxlimit=80,minValue=1,minlimit=61,},
			[5]= {maxValue=2,maxlimit=100,minValue=1,minlimit=81,},
			[6]= {maxValue=2,maxlimit=120,minValue=1,minlimit=101,},
			[7]= {maxValue=2,maxlimit=140,minValue=1,minlimit=121,},
			[8]= {maxValue=2,maxlimit=160,minValue=1,minlimit=141,},
			[9]= {maxValue=2,maxlimit=180,minValue=1,minlimit=161,},
			[10]= {maxValue=2,maxlimit=200,minValue=1,minlimit=181,},
			[11]= {maxValue=2,maxlimit=-1,minValue=2,minlimit=201,},
		},
	attrtype=17,
	canSame=0,
	reqGold=1000,
}
gdEquipEvaluate[19] = {
	name="敏捷",
	attr= {
			[1]= {maxValue=0,maxlimit=20,minValue=0,minlimit=0,},
			[2]= {maxValue=0,maxlimit=40,minValue=0,minlimit=21,},
			[3]= {maxValue=0,maxlimit=60,minValue=0,minlimit=41,},
			[4]= {maxValue=0,maxlimit=80,minValue=0,minlimit=61,},
			[5]= {maxValue=0,maxlimit=100,minValue=0,minlimit=81,},
			[6]= {maxValue=1,maxlimit=120,minValue=1,minlimit=101,},
			[7]= {maxValue=1,maxlimit=140,minValue=1,minlimit=121,},
			[8]= {maxValue=1,maxlimit=160,minValue=1,minlimit=141,},
			[9]= {maxValue=1,maxlimit=180,minValue=1,minlimit=161,},
			[10]= {maxValue=1,maxlimit=200,minValue=1,minlimit=181,},
			[11]= {maxValue=1,maxlimit=-1,minValue=1,minlimit=201,},
		},
	attrtype=18,
	canSame=0,
	reqGold=1000,
}
gdEquipEvaluate[20] = {
	name="幸运",
	attr= {
			[1]= {maxValue=0,maxlimit=20,minValue=0,minlimit=0,},
			[2]= {maxValue=0,maxlimit=40,minValue=0,minlimit=21,},
			[3]= {maxValue=0,maxlimit=60,minValue=0,minlimit=41,},
			[4]= {maxValue=0,maxlimit=80,minValue=0,minlimit=61,},
			[5]= {maxValue=0,maxlimit=100,minValue=0,minlimit=81,},
			[6]= {maxValue=0,maxlimit=120,minValue=0,minlimit=101,},
			[7]= {maxValue=0,maxlimit=140,minValue=0,minlimit=121,},
			[8]= {maxValue=0,maxlimit=160,minValue=0,minlimit=141,},
			[9]= {maxValue=0,maxlimit=180,minValue=0,minlimit=161,},
			[10]= {maxValue=0,maxlimit=200,minValue=0,minlimit=181,},
			[11]= {maxValue=1,maxlimit=-1,minValue=1,minlimit=201,},
		},
	attrtype=25,
	canSame=0,
	reqGold=1000,
}
gdItemMerge[40001] = {
	cate=1,
	probability=100,
	reqGold=5000,
	[1]= {id=40000,cnt=4,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[40002] = {
	cate=1,
	probability=100,
	reqGold=5000,
	[1]= {id=40001,cnt=4,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[40003] = {
	cate=1,
	probability=100,
	reqGold=5000,
	[1]= {id=40002,cnt=4,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}

--------------------------------------初级灵石--------------------------------
gdItemMerge[41000] = {--初级灵石
	cate=1,
	probability=100,
	reqGold=5000,
	[1]= {id=40004,cnt=8,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[41001] = {--中级灵石
	cate=1,
	probability=100,
	reqGold=5000,
	[1]= {id=41000,cnt=8,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[41002] = {--极品灵石
	cate=1,
	probability=100,
	reqGold=5000,
	[1]= {id=41001,cnt=8,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[60266] = {--装备
	cate=2,
	probability=50,
	reqGold=1000,
	[1]= {id=40005,cnt=4,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[20560] = {     
	cate=2,
	probability=100,
	reqGold=1000,
	[1]= {id=41002,cnt=100,},
	[2]= {id=41004,cnt=100,},
	[3]= {id=60264,cnt=1,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[87410] = {     
	cate=2,
	probability=100,
	reqGold=1000,
	[1]= {id=41002,cnt=100,},
	[2]= {id=41004,cnt=100,},
	[3]= {id=87409,cnt=1,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[83083] = {     
	cate=2,
	probability=100,
	reqGold=1000,
	[1]= {id=41002,cnt=150,},
	[2]= {id=41004,cnt=150,},
	[3]= {id=83082,cnt=1,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80031] = {     
	cate=2,
	probability=100,
	reqGold=1000,
	[1]= {id=41002,cnt=150,},
	[2]= {id=41004,cnt=150,},
	[3]= {id=80030,cnt=1,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[20559] = {     
	cate=2,
	probability=100,
	reqGold=1000,
	[1]= {id=41002,cnt=300,},
	[2]= {id=41004,cnt=300,},
	[3]= {id=60273,cnt=1,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}

gdItemMerge[30059] = {-------------------物品合成
	cate=3,
	probability=95,
	reqGold=1000,
	[1]= {id=41000,cnt=3,},
	[2]= {id=40005,cnt=88,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[5558] = {-------------------物品合成
	cate=3,
	probability=95,
	reqGold=1000,
	[1]= {id=41002,cnt=5,},
	[2]= {id=41005,cnt=188,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}

----------------------------------------------------------------------------------
gdItemMerge[40055] = {
	cate=5,
	probability=100,
	reqGold=1000,
	[1]= {id=40054,cnt=10,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[40056] = {
	cate=5,
	probability=100,
	reqGold=1000,
	[1]= {id=40055,cnt=10,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80001] = {
	cate=4,
	probability=100,
	reqGold=100000,
	[1]= {id=40007,cnt=1,},
	[2]= {id=80000,cnt=1,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80002] = {
	cate=4,
	probability=100,
	reqGold=200000,
	[1]= {id=80001,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80003] = {
	cate=4,
	probability=100,
	reqGold=400000,
	[1]= {id=80002,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80004] = {
	cate=4,
	probability=100,
	reqGold=800000,
	[1]= {id=80003,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80005] = {
	cate=4,
	probability=100,
	reqGold=1600000,
	[1]= {id=80004,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80006] = {
	cate=4,
	probability=100,
	reqGold=3200000,
	[1]= {id=80005,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80007] = {
	cate=4,
	probability=100,
	reqGold=6400000,
	[1]= {id=80006,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80008] = {
	cate=4,
	probability=100,
	reqGold=12800000,
	[1]= {id=80007,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80009] = {
	cate=4,
	probability=100,
	reqGold=12800000,
	[1]= {id=80008,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80010] = {
	cate=4,
	probability=100,
	reqGold=12800000,
	[1]= {id=80009,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80011] = {
	cate=4,
	probability=100,
	reqGold=12800000,
	[1]= {id=80010,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80025] = {
	cate=4,
	probability=100,
	reqGold=20000000,
	[1]= {id=80011,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80026] = {
	cate=4,
	probability=100,
	reqGold=25000000,
	[1]= {id=80025,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80027] = {
	cate=4,
	probability=100,
	reqGold=30000000,
	[1]= {id=80026,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80028] = {
	cate=4,
	probability=100,
	reqGold=35000000,
	[1]= {id=80027,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80029] = {
	cate=4,
	probability=100,
	reqGold=40000000,
	[1]= {id=80028,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[80030] = {
	cate=4,
	probability=100,
	reqGold=45000000,
	[1]= {id=80029,cnt=2,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[86000] = {-------------------神器合成
	cate=6,
	probability=70,
	reqGold=1000,
	[1]= {id=41000,cnt=10,},
	[2]= {id=41003,cnt=10,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[86001] = {
	cate=6,
	probability=70,
	reqGold=1000,
	[1]= {id=41000,cnt=10,},
	[2]= {id=41003,cnt=10,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[86002] = {
	cate=6,
	probability=70,
	reqGold=1000,
	[1]= {id=41000,cnt=10,},
	[2]= {id=41003,cnt=10,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[86003] = {
	cate=6,
	probability=60,
	reqGold=1000,
	[1]= {id=41000,cnt=10,},
	[2]= {id=41003,cnt=5,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[86004] = {
	cate=6,
	probability=60,
	reqGold=1000,
	[1]= {id=41000,cnt=10,},
	[2]= {id=41003,cnt=5,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[86005] = {
	cate=6,
	probability=60,
	reqGold=1000,
	[1]= {id=41000,cnt=10,},
	[2]= {id=41003,cnt=5,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}

gdItemMerge[10014] = {----------------------魂石合成
	cate=7,
	probability=100,
	reqGold=1000,
	[1]= {id=10007,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10015] = {
	cate=7,
	probability=100,
	reqGold=1000,
	[1]= {id=10008,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10016] = {
	cate=7,
	probability=100,
	reqGold=1000,
	[1]= {id=10009,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10017] = {
	cate=7,
	probability=100,
	reqGold=1000,
	[1]= {id=10010,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10018] = {
	cate=7,
	probability=100,
	reqGold=1000,
	[1]= {id=10011,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10019] = {
	cate=7,
	probability=100,
	reqGold=1000,
	[1]= {id=10012,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10020] = {
	cate=7,
	probability=100,
	reqGold=1000,
	[1]= {id=10013,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10021] = {
	cate=7,
	probability=100,
	reqGold=5000,
	[1]= {id=10014,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10022] = {
	cate=7,
	probability=100,
	reqGold=5000,
	[1]= {id=10015,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10023] = {
	cate=7,
	probability=100,
	reqGold=5000,
	[1]= {id=10016,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10024] = {
	cate=7,
	probability=100,
	reqGold=5000,
	[1]= {id=10017,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10025] = {
	cate=7,
	probability=100,
	reqGold=5000,
	[1]= {id=10018,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10026] = {
	cate=7,
	probability=100,
	reqGold=5000,
	[1]= {id=10019,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10027] = {
	cate=7,
	probability=100,
	reqGold=5000,
	[1]= {id=10020,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10028] = {
	cate=7,
	probability=100,
	reqGold=10000,
	[1]= {id=10021,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10029] = {
	cate=7,
	probability=100,
	reqGold=10000,
	[1]= {id=10022,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10030] = {
	cate=7,
	probability=100,
	reqGold=10000,
	[1]= {id=10023,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10031] = {
	cate=7,
	probability=100,
	reqGold=10000,
	[1]= {id=10024,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10032] = {
	cate=7,
	probability=100,
	reqGold=10000,
	[1]= {id=10025,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10033] = {
	cate=7,
	probability=100,
	reqGold=10000,
	[1]= {id=10026,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10034] = {
	cate=7,
	probability=100,
	reqGold=10000,
	[1]= {id=10027,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10035] = {
	cate=7,
	probability=100,
	reqGold=30000,
	[1]= {id=10028,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10036] = {
	cate=7,
	probability=100,
	reqGold=30000,
	[1]= {id=10029,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10037] = {
	cate=7,
	probability=100,
	reqGold=30000,
	[1]= {id=10030,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10038] = {
	cate=7,
	probability=100,
	reqGold=30000,
	[1]= {id=10031,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10039] = {
	cate=7,
	probability=100,
	reqGold=30000,
	[1]= {id=10032,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10040] = {
	cate=7,
	probability=100,
	reqGold=30000,
	[1]= {id=10033,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10041] = {
	cate=7,
	probability=100,
	reqGold=30000,
	[1]= {id=10034,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10042] = {
	cate=7,
	probability=100,
	reqGold=50000,
	[1]= {id=10035,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10043] = {
	cate=7,
	probability=100,
	reqGold=50000,
	[1]= {id=10036,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10044] = {
	cate=7,
	probability=100,
	reqGold=50000,
	[1]= {id=10037,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10045] = {
	cate=7,
	probability=100,
	reqGold=50000,
	[1]= {id=10038,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10046] = {
	cate=7,
	probability=100,
	reqGold=50000,
	[1]= {id=10039,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10047] = {
	cate=7,
	probability=100,
	reqGold=50000,
	[1]= {id=10040,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10048] = {
	cate=7,
	probability=100,
	reqGold=50000,
	[1]= {id=10041,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10049] = {
	cate=7,
	probability=100,
	reqGold=80000,
	[1]= {id=10042,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10050] = {
	cate=7,
	probability=100,
	reqGold=80000,
	[1]= {id=10043,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10051] = {
	cate=7,
	probability=100,
	reqGold=80000,
	[1]= {id=10044,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10052] = {
	cate=7,
	probability=100,
	reqGold=80000,
	[1]= {id=10045,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10053] = {
	cate=7,
	probability=100,
	reqGold=80000,
	[1]= {id=10046,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10054] = {
	cate=7,
	probability=100,
	reqGold=80000,
	[1]= {id=10047,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10055] = {
	cate=7,
	probability=100,
	reqGold=80000,
	[1]= {id=10048,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10056] = {
	cate=7,
	probability=100,
	reqGold=100000,
	[1]= {id=10049,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10057] = {
	cate=7,
	probability=100,
	reqGold=100000,
	[1]= {id=10050,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10058] = {
	cate=7,
	probability=100,
	reqGold=100000,
	[1]= {id=10051,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10059] = {
	cate=7,
	probability=100,
	reqGold=100000,
	[1]= {id=10052,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10060] = {
	cate=7,
	probability=100,
	reqGold=100000,
	[1]= {id=10053,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10061] = {
	cate=7,
	probability=100,
	reqGold=100000,
	[1]= {id=10054,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10062] = {
	cate=7,
	probability=100,
	reqGold=100000,
	[1]= {id=10055,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10063] = {
	cate=7,
	probability=100,
	reqGold=300000,
	[1]= {id=10056,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10064] = {
	cate=7,
	probability=100,
	reqGold=300000,
	[1]= {id=10057,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10065] = {
	cate=7,
	probability=100,
	reqGold=300000,
	[1]= {id=10058,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10066] = {
	cate=7,
	probability=100,
	reqGold=300000,
	[1]= {id=10059,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10067] = {
	cate=7,
	probability=100,
	reqGold=300000,
	[1]= {id=10060,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10068] = {
	cate=7,
	probability=100,
	reqGold=300000,
	[1]= {id=10061,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10069] = {
	cate=7,
	probability=100,
	reqGold=300000,
	[1]= {id=10062,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10070] = {
	cate=7,
	probability=100,
	reqGold=500000,
	[1]= {id=10063,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10071] = {
	cate=7,
	probability=100,
	reqGold=500000,
	[1]= {id=10064,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10072] = {
	cate=7,
	probability=100,
	reqGold=500000,
	[1]= {id=10065,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10073] = {
	cate=7,
	probability=100,
	reqGold=500000,
	[1]= {id=10066,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10074] = {
	cate=7,
	probability=100,
	reqGold=500000,
	[1]= {id=10067,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10075] = {
	cate=7,
	probability=100,
	reqGold=500000,
	[1]= {id=10068,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10076] = {
	cate=7,
	probability=100,
	reqGold=500000,
	[1]= {id=10069,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10077] = {
	cate=7,
	probability=100,
	reqGold=1000000,
	[1]= {id=10070,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10078] = {
	cate=7,
	probability=100,
	reqGold=1000000,
	[1]= {id=10071,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10079] = {
	cate=7,
	probability=100,
	reqGold=1000000,
	[1]= {id=10072,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10080] = {
	cate=7,
	probability=100,
	reqGold=1000000,
	[1]= {id=10073,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10081] = {
	cate=7,
	probability=100,
	reqGold=1000000,
	[1]= {id=10074,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10082] = {
	cate=7,
	probability=100,
	reqGold=1000000,
	[1]= {id=10075,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10083] = {
	cate=7,
	probability=100,
	reqGold=1000000,
	[1]= {id=10076,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10084] = {
	cate=7,
	probability=100,
	reqGold=1500000,
	[1]= {id=10077,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10085] = {
	cate=7,
	probability=100,
	reqGold=1500000,
	[1]= {id=10078,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10086] = {
	cate=7,
	probability=100,
	reqGold=1500000,
	[1]= {id=10079,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10087] = {
	cate=7,
	probability=100,
	reqGold=1500000,
	[1]= {id=10080,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10088] = {
	cate=7,
	probability=100,
	reqGold=1500000,
	[1]= {id=10081,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10089] = {
	cate=7,
	probability=100,
	reqGold=1500000,
	[1]= {id=10082,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10090] = {
	cate=7,
	probability=100,
	reqGold=1500000,
	[1]= {id=10083,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10091] = {
	cate=7,
	probability=100,
	reqGold=2000000,
	[1]= {id=10084,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10092] = {
	cate=7,
	probability=100,
	reqGold=2000000,
	[1]= {id=10085,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10093] = {
	cate=7,
	probability=100,
	reqGold=2000000,
	[1]= {id=10086,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10094] = {
	cate=7,
	probability=100,
	reqGold=2000000,
	[1]= {id=10087,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10095] = {
	cate=7,
	probability=100,
	reqGold=2000000,
	[1]= {id=10088,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10096] = {
	cate=7,
	probability=100,
	reqGold=2000000,
	[1]= {id=10089,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10097] = {
	cate=7,
	probability=100,
	reqGold=2000000,
	[1]= {id=10090,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10098] = {
	cate=7,
	probability=100,
	reqGold=2500000,
	[1]= {id=10091,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10099] = {
	cate=7,
	probability=100,
	reqGold=2500000,
	[1]= {id=10092,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10100] = {
	cate=7,
	probability=100,
	reqGold=2500000,
	[1]= {id=10093,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10101] = {
	cate=7,
	probability=100,
	reqGold=2500000,
	[1]= {id=10094,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10102] = {
	cate=7,
	probability=100,
	reqGold=2500000,
	[1]= {id=10095,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10103] = {
	cate=7,
	probability=100,
	reqGold=2500000,
	[1]= {id=10096,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10104] = {
	cate=7,
	probability=100,
	reqGold=2500000,
	[1]= {id=10097,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10105] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10098,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10106] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10099,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10107] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10100,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10108] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10101,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10109] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10102,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10110] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10103,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10111] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10104,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10112] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10105,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10113] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10106,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10114] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10107,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10115] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10108,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10116] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10109,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10117] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10110,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10118] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10111,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10119] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10112,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10120] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10113,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10121] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10114,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10122] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10115,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10123] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10116,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10124] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10117,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10125] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10118,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10126] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10119,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10127] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10120,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10128] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10121,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10129] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10122,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10130] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10123,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10131] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10124,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10132] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10125,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10133] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10126,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10134] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10127,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10135] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10128,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10136] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10129,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10137] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10130,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10138] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10131,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10139] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10132,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10140] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10133,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10141] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10134,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10142] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10135,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10143] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10136,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10144] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10137,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10145] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10138,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
gdItemMerge[10146] = {
	cate=7,
	probability=100,
	reqGold=3000000,
	[1]= {id=10139,cnt=3,},
	[2]= {id=0,cnt=0,},
	[3]= {id=0,cnt=0,},
	[4]= {id=0,cnt=0,},
	[5]= {id=0,cnt=0,},
}
-----------------------------------------------------------------------------------------------

gdItemStoneTransform[10011] = {firstItem=10012,reqGold=25000,secondItem=10013,}
gdItemStoneTransform[10012] = {firstItem=10011,reqGold=25000,secondItem=10013,}
gdItemStoneTransform[10013] = {firstItem=10011,reqGold=25000,secondItem=10012,}
gdItemStoneTransform[10018] = {firstItem=10019,reqGold=50000,secondItem=10020,}
gdItemStoneTransform[10019] = {firstItem=10020,reqGold=50000,secondItem=10018,}
gdItemStoneTransform[10020] = {firstItem=10018,reqGold=50000,secondItem=10019,}
gdItemStoneTransform[10025] = {firstItem=10026,reqGold=100000,secondItem=10027,}
gdItemStoneTransform[10026] = {firstItem=10027,reqGold=100000,secondItem=10025,}
gdItemStoneTransform[10027] = {firstItem=10025,reqGold=100000,secondItem=10026,}
gdItemStoneTransform[10032] = {firstItem=10033,reqGold=200000,secondItem=10034,}
gdItemStoneTransform[10033] = {firstItem=10034,reqGold=200000,secondItem=10032,}
gdItemStoneTransform[10034] = {firstItem=10032,reqGold=200000,secondItem=10033,}
gdItemStoneTransform[10039] = {firstItem=10040,reqGold=500000,secondItem=10041,}
gdItemStoneTransform[10040] = {firstItem=10041,reqGold=500000,secondItem=10039,}
gdItemStoneTransform[10041] = {firstItem=10039,reqGold=500000,secondItem=10040,}
gdItemStoneTransform[10046] = {firstItem=10047,reqGold=1000000,secondItem=10048,}
gdItemStoneTransform[10047] = {firstItem=10048,reqGold=1000000,secondItem=10046,}
gdItemStoneTransform[10048] = {firstItem=10046,reqGold=1000000,secondItem=10047,}
gdItemStoneTransform[10053] = {firstItem=10054,reqGold=1500000,secondItem=10055,}
gdItemStoneTransform[10054] = {firstItem=10053,reqGold=1500000,secondItem=10055,}
gdItemStoneTransform[10055] = {firstItem=10053,reqGold=1500000,secondItem=10054,}
gdItemStoneTransform[10060] = {firstItem=10061,reqGold=2000000,secondItem=10062,}
gdItemStoneTransform[10061] = {firstItem=10062,reqGold=2000000,secondItem=10060,}
gdItemStoneTransform[10062] = {firstItem=10060,reqGold=2000000,secondItem=10061,}
gdItemStoneTransform[10067] = {firstItem=10068,reqGold=2000000,secondItem=10069,}
gdItemStoneTransform[10068] = {firstItem=10067,reqGold=2000000,secondItem=10069,}
gdItemStoneTransform[10069] = {firstItem=10067,reqGold=2000000,secondItem=10068,}
gdItemStoneTransform[10074] = {firstItem=10075,reqGold=3000000,secondItem=10076,}
gdItemStoneTransform[10075] = {firstItem=10074,reqGold=3000000,secondItem=10076,}
gdItemStoneTransform[10076] = {firstItem=10074,reqGold=3000000,secondItem=10075,}
gdItemStoneTransform[10081] = {firstItem=10082,reqGold=4000000,secondItem=10083,}
gdItemStoneTransform[10082] = {firstItem=10081,reqGold=4000000,secondItem=10083,}
gdItemStoneTransform[10083] = {firstItem=10081,reqGold=4000000,secondItem=10082,}
gdItemStoneTransform[10088] = {firstItem=10089,reqGold=5000000,secondItem=10090,}
gdItemStoneTransform[10089] = {firstItem=10088,reqGold=5000000,secondItem=10090,}
gdItemStoneTransform[10090] = {firstItem=10088,reqGold=5000000,secondItem=10089,}
gdItemStoneTransform[10095] = {firstItem=10096,reqGold=6000000,secondItem=10097,}
gdItemStoneTransform[10096] = {firstItem=10095,reqGold=6000000,secondItem=10097,}
gdItemStoneTransform[10097] = {firstItem=10095,reqGold=6000000,secondItem=10096,}
gdItemStoneTransform[10102] = {firstItem=10103,reqGold=7000000,secondItem=10104,}
gdItemStoneTransform[10103] = {firstItem=10102,reqGold=7000000,secondItem=10104,}
gdItemStoneTransform[10104] = {firstItem=10102,reqGold=7000000,secondItem=10103,}
gdItemStoneTransform[10109] = {firstItem=10110,reqGold=8000000,secondItem=10111,}
gdItemStoneTransform[10110] = {firstItem=10109,reqGold=8000000,secondItem=10111,}
gdItemStoneTransform[10111] = {firstItem=10109,reqGold=8000000,secondItem=10110,}
--------------------------------------------------------------------------------------
gdItemStoneTransform[10116] = {firstItem=10117,reqGold=2000,secondItem=10118,}
gdItemStoneTransform[10117] = {firstItem=10116,reqGold=2000,secondItem=10118,}
gdItemStoneTransform[10118] = {firstItem=10116,reqGold=2000,secondItem=10117,}
gdItemStoneTransform[10123] = {firstItem=10124,reqGold=3000,secondItem=10125,}
gdItemStoneTransform[10124] = {firstItem=10123,reqGold=3000,secondItem=10125,}
gdItemStoneTransform[10125] = {firstItem=10123,reqGold=3000,secondItem=10124,}
gdItemStoneTransform[10130] = {firstItem=10131,reqGold=4000,secondItem=10132,}
gdItemStoneTransform[10131] = {firstItem=10130,reqGold=4000,secondItem=10132,}
gdItemStoneTransform[10132] = {firstItem=10130,reqGold=4000,secondItem=10131,}
gdItemStoneTransform[10137] = {firstItem=10138,reqGold=6000,secondItem=10139,}
gdItemStoneTransform[10138] = {firstItem=10137,reqGold=6000,secondItem=10139,}
gdItemStoneTransform[10139] = {firstItem=10137,reqGold=6000,secondItem=10138,}
gdItemStoneTransform[10144] = {firstItem=10145,reqGold=10000,secondItem=10146,}
gdItemStoneTransform[10145] = {firstItem=10144,reqGold=10000,secondItem=10146,}
gdItemStoneTransform[10146] = {firstItem=10144,reqGold=10000,secondItem=10145,}
-------------------------------------------------转换------------------------------------
--套装3.4.5.6.7.8.9衣服转换
gdItemStoneTransform[20082] = {firstItem=20083,reqGold=100,secondItem=20083,}
gdItemStoneTransform[20083] = {firstItem=20082,reqGold=100,secondItem=20082,}
gdItemStoneTransform[20142] = {firstItem=20143,reqGold=100,secondItem=20143,}
gdItemStoneTransform[20143] = {firstItem=20142,reqGold=200,secondItem=20142,}
gdItemStoneTransform[20022] = {firstItem=20023,reqGold=200,secondItem=20023,}
gdItemStoneTransform[20023] = {firstItem=20022,reqGold=200,secondItem=20022,}
-------------------------------------------------------------------------------
gdItemStoneTransform[20092] = {firstItem=20093,reqGold=300,secondItem=20093,}
gdItemStoneTransform[20093] = {firstItem=20092,reqGold=300,secondItem=20092,}
gdItemStoneTransform[20152] = {firstItem=20153,reqGold=300,secondItem=20153,}
gdItemStoneTransform[20153] = {firstItem=20152,reqGold=300,secondItem=20152,}
gdItemStoneTransform[20032] = {firstItem=20033,reqGold=300,secondItem=20033,}
gdItemStoneTransform[20033] = {firstItem=20032,reqGold=300,secondItem=20032,}
----------------------------------------------------------------------------------
gdItemStoneTransform[20102] = {firstItem=20103,reqGold=400,secondItem=20103,}
gdItemStoneTransform[20103] = {firstItem=20102,reqGold=400,secondItem=20102,}
gdItemStoneTransform[20162] = {firstItem=20163,reqGold=400,secondItem=20163,}
gdItemStoneTransform[20163] = {firstItem=20162,reqGold=400,secondItem=20162,}
gdItemStoneTransform[20042] = {firstItem=20043,reqGold=400,secondItem=20043,}
gdItemStoneTransform[20043] = {firstItem=20042,reqGold=400,secondItem=20042,}
---------------------------------------------------------------------------------
gdItemStoneTransform[20112] = {firstItem=20113,reqGold=500,secondItem=20113,}
gdItemStoneTransform[20113] = {firstItem=20112,reqGold=500,secondItem=20112,}
gdItemStoneTransform[20172] = {firstItem=20173,reqGold=500,secondItem=20173,}
gdItemStoneTransform[20173] = {firstItem=20172,reqGold=500,secondItem=20172,}
gdItemStoneTransform[20052] = {firstItem=20053,reqGold=500,secondItem=20053,}
gdItemStoneTransform[20053] = {firstItem=20052,reqGold=500,secondItem=20052,}
----------------------------------------------------------------------------------
gdItemStoneTransform[20182] = {firstItem=20183,reqGold=600,secondItem=20183,}
gdItemStoneTransform[20183] = {firstItem=20182,reqGold=600,secondItem=20182,}
gdItemStoneTransform[20192] = {firstItem=20193,reqGold=600,secondItem=20193,}
gdItemStoneTransform[20193] = {firstItem=20192,reqGold=600,secondItem=20192,}
gdItemStoneTransform[20202] = {firstItem=20203,reqGold=600,secondItem=20203,}
gdItemStoneTransform[20203] = {firstItem=20202,reqGold=600,secondItem=20202,}
---------------------------------------------------------------------------------------
gdItemStoneTransform[20302] = {firstItem=20303,reqGold=700,secondItem=20303,}
gdItemStoneTransform[20303] = {firstItem=20302,reqGold=700,secondItem=20302,}
gdItemStoneTransform[20312] = {firstItem=20313,reqGold=700,secondItem=20313,}
gdItemStoneTransform[20313] = {firstItem=20312,reqGold=700,secondItem=20312,}
gdItemStoneTransform[20322] = {firstItem=20323,reqGold=700,secondItem=20323,}
gdItemStoneTransform[20323] = {firstItem=20322,reqGold=700,secondItem=20322,}
-----------------------------------------------------------------------------------
gdItemStoneTransform[20331] = {firstItem=20332,reqGold=800,secondItem=20332,}
gdItemStoneTransform[20332] = {firstItem=20331,reqGold=800,secondItem=20331,}
gdItemStoneTransform[20340] = {firstItem=20341,reqGold=800,secondItem=20341,}
gdItemStoneTransform[20341] = {firstItem=20340,reqGold=800,secondItem=20340,}
gdItemStoneTransform[20349] = {firstItem=20350,reqGold=800,secondItem=20350,}
gdItemStoneTransform[20350] = {firstItem=20349,reqGold=800,secondItem=20349,}
-----------------------------------------------------------------------------------
--战士9转换
gdItemStoneTransform[20329] = {firstItem=20338,reqGold=1000,secondItem=20347,}
gdItemStoneTransform[20330] = {firstItem=20339,reqGold=1000,secondItem=20348,}
gdItemStoneTransform[20331] = {firstItem=20340,reqGold=1000,secondItem=20349,}
gdItemStoneTransform[20332] = {firstItem=20341,reqGold=1000,secondItem=20350,}
gdItemStoneTransform[20333] = {firstItem=20342,reqGold=1000,secondItem=20351,}
gdItemStoneTransform[20334] = {firstItem=20343,reqGold=1000,secondItem=20352,}
gdItemStoneTransform[20335] = {firstItem=20344,reqGold=1000,secondItem=20353,}
gdItemStoneTransform[20336] = {firstItem=20345,reqGold=1000,secondItem=20354,}
gdItemStoneTransform[20337] = {firstItem=20346,reqGold=1000,secondItem=20355,}
--法师9转换
gdItemStoneTransform[20338] = {firstItem=20329,reqGold=1000,secondItem=20347,}
gdItemStoneTransform[20339] = {firstItem=20330,reqGold=1000,secondItem=20348,}
gdItemStoneTransform[20340] = {firstItem=20331,reqGold=1000,secondItem=20349,}
gdItemStoneTransform[20341] = {firstItem=20332,reqGold=1000,secondItem=20350,}
gdItemStoneTransform[20342] = {firstItem=20333,reqGold=1000,secondItem=20351,}
gdItemStoneTransform[20343] = {firstItem=20334,reqGold=1000,secondItem=20352,}
gdItemStoneTransform[20344] = {firstItem=20335,reqGold=1000,secondItem=20353,}
gdItemStoneTransform[20345] = {firstItem=20336,reqGold=1000,secondItem=20354,}
gdItemStoneTransform[20346] = {firstItem=20337,reqGold=1000,secondItem=20355,}
--道士9转换
gdItemStoneTransform[20347] = {firstItem=20329,reqGold=1000,secondItem=20338,}
gdItemStoneTransform[20348] = {firstItem=20330,reqGold=1000,secondItem=20339,}
gdItemStoneTransform[20349] = {firstItem=20331,reqGold=1000,secondItem=20340,}
gdItemStoneTransform[20350] = {firstItem=20332,reqGold=1000,secondItem=20341,}
gdItemStoneTransform[20351] = {firstItem=20333,reqGold=1000,secondItem=20342,}
gdItemStoneTransform[20352] = {firstItem=20334,reqGold=1000,secondItem=20343,}
gdItemStoneTransform[20353] = {firstItem=20335,reqGold=1000,secondItem=20344,}
gdItemStoneTransform[20354] = {firstItem=20336,reqGold=1000,secondItem=20345,}
gdItemStoneTransform[20355] = {firstItem=20337,reqGold=1000,secondItem=20346,}
-- --战特戒转换
-- gdItemStoneTransform[60231] = {firstItem=60239,reqGold=20,secondItem=60223,}
-- gdItemStoneTransform[60232] = {firstItem=60240,reqGold=30,secondItem=60224,}
-- gdItemStoneTransform[60233] = {firstItem=60241,reqGold=40,secondItem=60225,}
-- gdItemStoneTransform[60234] = {firstItem=60242,reqGold=50,secondItem=60226,}
-- gdItemStoneTransform[60235] = {firstItem=60243,reqGold=60,secondItem=60227,}
-- gdItemStoneTransform[60236] = {firstItem=60244,reqGold=70,secondItem=60228,}
-- gdItemStoneTransform[60237] = {firstItem=60245,reqGold=80,secondItem=60229,}
-- --法特戒转换
-- gdItemStoneTransform[60239] = {firstItem=60231,reqGold=20,secondItem=60223,}
-- gdItemStoneTransform[60240] = {firstItem=60232,reqGold=30,secondItem=60224,}
-- gdItemStoneTransform[60241] = {firstItem=60233,reqGold=40,secondItem=60225,}
-- gdItemStoneTransform[60242] = {firstItem=60234,reqGold=50,secondItem=60226,}
-- gdItemStoneTransform[60243] = {firstItem=60235,reqGold=60,secondItem=60227,}
-- gdItemStoneTransform[60244] = {firstItem=60236,reqGold=70,secondItem=60228,}
-- gdItemStoneTransform[60245] = {firstItem=60237,reqGold=80,secondItem=60229,}
-- --道士特戒转换
-- gdItemStoneTransform[60223] = {firstItem=60231,reqGold=20,secondItem=60239,}
-- gdItemStoneTransform[60224] = {firstItem=60232,reqGold=30,secondItem=60240,}
-- gdItemStoneTransform[60225] = {firstItem=60233,reqGold=40,secondItem=60241,}
-- gdItemStoneTransform[60226] = {firstItem=60234,reqGold=50,secondItem=60242,}
-- gdItemStoneTransform[60227] = {firstItem=60235,reqGold=60,secondItem=60243,}
-- gdItemStoneTransform[60228] = {firstItem=60236,reqGold=70,secondItem=60244,}
-- gdItemStoneTransform[60229] = {firstItem=60237,reqGold=80,secondItem=60245,}



gddescription[1] = {name="强化-装备升级",content="1.只有[g40级或以上]的[g武器、套装或特殊装备]才能升级；\n2.升级时候，有一定的[g强化等级条件]；\n3.升级可以[g继承]原有的强化等级、鉴定属性；\n4.升级时，有[g一定几率]使装备获得一个[g随机的极品属性]；\n5.升级材料除击杀相应等级的BOSS获得外，还能在商城购买；",}
gddescription[2] = {name="强化-装备强化",content="1.[g20级或以上]的装备才能强化；[g强化+10]或以下所需矿石可以通过挖矿或者购买获得；\n2.灵魂可以在[g梵天星宫]获得；\n3.装备[g强化+8或者以上]成功时，有一定几率使装备获得一个随机的极品属性；\n4.[g强化+10或以下]的失败时强化等级会随机下降[g1~3级]，最低跌到0级，强化保护符可以使得[g+10或者以下]的强化成功率变成[g100%]；\n5.装备强化效果如下：\n[g+1] 攻击最大值[g+2]\n[g+2] 攻击最大值[g+4]\n[g+3] 攻击最大值[g+7]\n[g+4] 攻击最大值[g+11]\n[g+5] 攻击最大值[g+16]\n[g+6] 攻击最大值[g+22]\n[g+7] 攻击最大值[g+29]\n[g+8] 攻击最大值[g+37]\n[g+9] 攻击最大值[g+55]\n[g+10]  攻击最大值[g+75]\n",}
gddescription[3] = {name="强化-装备鉴定",content="1.[g20级或以上]的装备才能鉴定\n2.每次鉴定都会出现一条新的属性，同时不会对原有的鉴定属性产生影响\n3.鉴定次数越多，属性越容易取得最大值\n4.使用清洗可以移除所有没锁定的鉴定属性，但不会移除鉴定次数\n5.使用鉴定锁后，点击清洗视同将鉴定的属性鉴定一次，会累计鉴定次数。但是种类不会变化，数值会[g提高]或[g不变]\n6.在勾选了鉴定锁后，点击鉴定不会消耗鉴定锁",}
gddescription[4] = {name="强化-幻武替换",content="1.点击放入目标幻武后，再选择材料幻武点击放入；\n2.点击替换后，目标幻武与材料幻武的阶数将会互换，其它不变；\n3.幻武替换的成功率为100%。",}
gddescription[5] = {name="强化-极品转移",content="1.极品转移可以将一件装备的极品属性转移到指定装备上；\n2.目标装备如果已经带有极品属性，转移后原有的极品属性会[g覆盖]；\n3.材料装备在完成极品属性转移后，极品属性会消失；",}
gddescription[6] = {name="强化-强化转移",content="1.强化转移不掉强化等级\n2.强化等级必须在[g同部位]间进行\n3.转移成功后转移装备不消失强化等级归0，目标装备继承转移装备的强化等级\n4.若目标装备强化等级低于转移装备，则强化等级直接被覆盖\n5.转移装备的强化等级必须大于等于1级",}
gddescription[7] = {name="强化-鉴定转移",content="1.转移装备必须具有三条鉴定属性才能进行鉴定属性转移\n2.鉴定属性转移只限于同部位进行，转移成功后转移装备不消失\n3.转移成功后目标装备的鉴定属性变为转移装备的属性。若目标装备已有鉴定属性，则被转移属性覆盖，转移装备鉴定属性清零",}
gddescription[8] = {name="强化-极品清洗",content="1.使用极品清洗符可以清洗一件装备上的极品属性，对装备的其他属性不造成影响；",}
gddescription[9] = {name="强化-转生锻造",content="1.要提升普通装备的转生数需要一件相同转数的装备与一定数量的转生材料；\n2.转生锻造装备会保留装备的极品、强化、鉴定属性；\n3.作为材料的装备及其极品、强化、鉴定属性会消失；\n只有武器与套装才可以进行转生锻造。",}
gddescription[10] = {name="物品合成-灵珠合成",content="4个灵珠可以合成高一级的灵珠",}
gddescription[11] = {name="物品合成-技能书合成",content="多个低级技能书可以合成更高级的技能书",}
gddescription[12] = {name="物品合成-装备合成",content="[g陨铁勋章（1级）]可通过[g4块]光灵碎片合成。\n碎片来源：\n1、可通过消灭土城抗魔活动中的先锋煞翼、煞翼队长获得；\n2.在寻宝中获得对应的碎片包；",}
gddescription[13] = {name="物品合成-物品合成",content="[g鉴定图鉴]和[g清洗砂]可通过暗灵碎片、光灵碎片合成。\n碎片来源：\n1、可通过消灭土城抗魔活动中的先锋煞翼、煞翼队长获得；\n2.在寻宝中获得对应的碎片包；",}
gddescription[14] = {name="物品合成-翅膀合成",content="1.1档物品可从商城购买或由朱雀神翎和翅膀合成符合成获得。\n2、其他高档次的翅膀全由一定数量的低一档次翅膀合成获得。\n3、翅膀合成需要消耗一定数量的金币，合成成功率为100%.\n4、需要选择要合成的翅膀，然后点击合成。\n",}
gddescription[15] = {name="物品合成-魔晶石",content="[g10个]低级魔晶石可以合成更高级的魔晶石\n魔晶石可以在土城的装备兑换使者处兑换装备",}
gddescription[16] = {name="物品合成-魂石转换",content="1.特殊装备与魂石均可使用转换功能；\n2.可自由转换为任意其他类型的装备或魂石；\n3.转换魂石需要扣除金币[r装备转换扣除灵力]，具体所需数量会根据装备的强化等级或魂石的等级不同而改变；",}
gddescription[17] = {name="幻武启灵",content="1.所有幻武都可以启灵；\n2.每次启灵可增加[g1~5点]启灵值；\n3.启灵值满后，再次点击启灵可提升幻武启灵点击；\n4.每次点击启灵均有一定几率提升启灵等级",}
gddescription[18] = {name="强化-强化打磨",content="1.强化[g+10]之后需要进行打磨积累打磨点数才能增加强化等级，打磨过程中有几率直接升一级；\n2.灵魂石可以在[g梵天星宫]获得；\n3.\n[g+11] 攻击最大值[g+100]\n[g+12] 攻击最大值[g+130]\n[g+13] 攻击最大值[g+165]\n[g+14] 攻击最大值[g+205]\n[g+15] 攻击最大值[g+250]",}
gddescription[19] = {name="强化-完美强化",content="1.玩家消耗对应的[gN级]完美强化符可以将强化[g低于N]的装备直接强化到[g强化+N]；",}
gddescription[20] = {name="强化-翅膀羽化",content="1.[g5档或以上]的翅膀可以进行羽化；",}
gddescription[21] = {name="足迹升阶",content="1.所有足迹都可以升阶；\n2.每次升阶可增加[g1~5点]升阶值；\n3.升阶值满后，再次点击即可提升阶数；",}
gddescription[22] = {name="足迹替换",content="1.点击放入目标足迹后，再选择材料足迹点击放入；\n2.点击替换后，目标足迹与材料足迹的阶数将会互换，其它不变；\n3.足迹替换的成功率为100%。",}
gddescription[23] = {name=0,content="",}
gddescription[24] = {name=0,content="",}
gddescription[25] = {name="强化-物品附魔",content="1.每件装备仅可获得[g1种]附魔种类；\n2.对已有附魔属性的装备再次附魔，将会[g重置附魔属性与附魔强化点数]；\n3.每次附魔将会随机获得某种属性的一个随机值；\n4.附魔材料可在商城、副本、野外BOSS等处获得；",}
gddescription[26] = {name="强化-附魔强化",content="1.每种附魔可进行[g10次]固定属性强化；\n2.每次强化将会获得一个[g随机强化值]，并累计在装备上；\n3.玩家可使用[g极品附魔符]进行强化，并[g必定获得最大强化值]；\n4.[g极品附魔符]消耗量会根据当前强化点而变动；强化点越高，消耗的[g极品附魔符]越多；\n5.强化材料可在商城、副本、野外BOSS等处获得；",}

--转生
----战士3套
gdItemReBorn[20080] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20080,}
gdItemReBorn[20081] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20081,}
gdItemReBorn[20082] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20082,}
gdItemReBorn[20083] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20083,}
gdItemReBorn[20084] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20084,}
gdItemReBorn[20085] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20085,}
gdItemReBorn[20086] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20086,}
gdItemReBorn[20087] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20087,}
gdItemReBorn[20088] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20088,}
----战士4套
gdItemReBorn[20090] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20090,}
gdItemReBorn[20091] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20091,}
gdItemReBorn[20092] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20092,}
gdItemReBorn[20093] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20093,}
gdItemReBorn[20094] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20094,}
gdItemReBorn[20095] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20095,}
gdItemReBorn[20096] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20096,}
gdItemReBorn[20097] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20097,}
gdItemReBorn[20098] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20098,}
----战士5套
gdItemReBorn[20100] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20100,}
gdItemReBorn[20101] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20101,}
gdItemReBorn[20102] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20102,}
gdItemReBorn[20103] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20103,}
gdItemReBorn[20104] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20104,}
gdItemReBorn[20105] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20105,}
gdItemReBorn[20106] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20106,}
gdItemReBorn[20107] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20107,}
gdItemReBorn[20108] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20108,}
-----战士6套
gdItemReBorn[20110] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20110,}
gdItemReBorn[20111] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20111,}
gdItemReBorn[20112] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20112,}
gdItemReBorn[20113] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20113,}
gdItemReBorn[20114] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20114,}
gdItemReBorn[20115] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20115,}
gdItemReBorn[20116] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20116,}
gdItemReBorn[20117] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20117,}
gdItemReBorn[20118] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20118,}
-----战士7套
gdItemReBorn[20180] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20180,}
gdItemReBorn[20181] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20181,}
gdItemReBorn[20182] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20182,}
gdItemReBorn[20183] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20183,}
gdItemReBorn[20184] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20184,}
gdItemReBorn[20185] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20185,}
gdItemReBorn[20186] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20186,}
gdItemReBorn[20187] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20187,}
gdItemReBorn[20188] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20188,}
-----战士8套
gdItemReBorn[20300] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20300,}
gdItemReBorn[20301] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20301,}
gdItemReBorn[20302] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20302,}
gdItemReBorn[20303] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20303,}
gdItemReBorn[20304] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20304,}
gdItemReBorn[20305] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20305,}
gdItemReBorn[20306] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20306,}
gdItemReBorn[20307] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20307,}
gdItemReBorn[20308] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20308,}
-----战士9套
gdItemReBorn[20329] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20300,}
gdItemReBorn[20330] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20301,}
gdItemReBorn[20331] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20302,}
gdItemReBorn[20332] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20303,}
gdItemReBorn[20333] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20304,}
gdItemReBorn[20334] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20305,}
gdItemReBorn[20335] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20306,}
gdItemReBorn[20336] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20307,}
-----战10套
gdItemReBorn[20337] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20308,}
gdItemReBorn[20500] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20329,}
gdItemReBorn[20501] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20330,}
gdItemReBorn[20502] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20331,}
gdItemReBorn[20503] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20332,}
gdItemReBorn[20504] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20333,}
gdItemReBorn[20505] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20334,}
gdItemReBorn[20506] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20335,}
gdItemReBorn[20507] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20336,}
-----战士11套
gdItemReBorn[20508] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20337,}
gdItemReBorn[20530] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20500,}
gdItemReBorn[20531] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20501,}
gdItemReBorn[20532] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20502,}
gdItemReBorn[20533] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20503,}
gdItemReBorn[20534] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20504,}
gdItemReBorn[20535] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20505,}
gdItemReBorn[20536] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20506,}
gdItemReBorn[20537] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20507,}
gdItemReBorn[20538] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20508,}
--------------战士暗影猩红套
gdItemReBorn[20640] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20641] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20642] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20643] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20644] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20645] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20646] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20647] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20648] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
--------------道士暗影猩红套
gdItemReBorn[20660] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20661] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20662] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20663] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20664] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20665] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20666] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20667] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20668] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
--------------法师暗影猩蓝套
gdItemReBorn[20670] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20671] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20672] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20673] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20674] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20675] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20676] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20677] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[20678] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
-----暗影猩红 蓝 戒指
gdItemReBorn[60238] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[60246] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}
gdItemReBorn[60230] = {reqExtramoney=0,reqcnt=150,reqid=41004,reqmoney=1150000,second=0,}


---------------------------------------------------------------------------------------
--法师3套
gdItemReBorn[20140] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20140,}
gdItemReBorn[20141] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20141,}
gdItemReBorn[20142] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20142,}
gdItemReBorn[20143] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20143,}
gdItemReBorn[20144] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20144,}
gdItemReBorn[20145] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20145,}
gdItemReBorn[20146] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20146,}
gdItemReBorn[20147] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20147,}
gdItemReBorn[20148] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20148,}
----法师4套
gdItemReBorn[20150] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20150,}
gdItemReBorn[20151] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20151,}
gdItemReBorn[20152] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20152,}
gdItemReBorn[20153] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20153,}
gdItemReBorn[20154] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20154,}
gdItemReBorn[20155] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20155,}
gdItemReBorn[20156] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20156,}
gdItemReBorn[20157] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20157,}
gdItemReBorn[20158] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20158,}
-----法师5套
gdItemReBorn[20160] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20160,}
gdItemReBorn[20161] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20161,}
gdItemReBorn[20162] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20162,}
gdItemReBorn[20163] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20163,}
gdItemReBorn[20164] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20164,}
gdItemReBorn[20165] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20165,}
gdItemReBorn[20166] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20166,}
gdItemReBorn[20167] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20167,}
gdItemReBorn[20168] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20168,}
----法师6套
gdItemReBorn[20170] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20170,}
gdItemReBorn[20171] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20171,}
gdItemReBorn[20172] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20172,}
gdItemReBorn[20173] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20173,}
gdItemReBorn[20174] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20174,}
gdItemReBorn[20175] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20175,}
gdItemReBorn[20176] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20176,}
gdItemReBorn[20177] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20177,}
gdItemReBorn[20178] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20178,}
----法师7套
gdItemReBorn[20190] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20190,}
gdItemReBorn[20191] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20191,}
gdItemReBorn[20192] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20192,}
gdItemReBorn[20193] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20193,}
gdItemReBorn[20194] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20194,}
gdItemReBorn[20195] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20195,}
gdItemReBorn[20196] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20196,}
gdItemReBorn[20197] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20197,}
gdItemReBorn[20198] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20198,}
----法师8套
gdItemReBorn[20310] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20310,}
gdItemReBorn[20311] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20311,}
gdItemReBorn[20312] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20312,}
gdItemReBorn[20313] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20313,}
gdItemReBorn[20314] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20314,}
gdItemReBorn[20315] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20315,}
gdItemReBorn[20316] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20316,}
gdItemReBorn[20317] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20317,}
gdItemReBorn[20318] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20318,}
----法师9套
gdItemReBorn[20338] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20310,}
gdItemReBorn[20339] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20311,}
gdItemReBorn[20340] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20312,}
gdItemReBorn[20341] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20313,}
gdItemReBorn[20342] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20314,}
gdItemReBorn[20343] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20315,}
gdItemReBorn[20344] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20316,}
gdItemReBorn[20345] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20317,}
gdItemReBorn[20346] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20318,}

----法师10套
gdItemReBorn[20510] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20338,}
gdItemReBorn[20511] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20339,}
gdItemReBorn[20512] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20340,}
gdItemReBorn[20513] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20341,}
gdItemReBorn[20514] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20342,}
gdItemReBorn[20515] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20343,}
gdItemReBorn[20516] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20344,}
gdItemReBorn[20517] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20345,}
gdItemReBorn[20518] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20346,}

----法师11套
gdItemReBorn[20540] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20510,}
gdItemReBorn[20541] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20511,}
gdItemReBorn[20542] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20512,}
gdItemReBorn[20543] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20513,}
gdItemReBorn[20544] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20514,}
gdItemReBorn[20545] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20515,}
gdItemReBorn[20546] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20516,}
gdItemReBorn[20547] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20517,}
gdItemReBorn[20548] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20518,}

---------------------------------------------------------------------------------------
----道士3套
gdItemReBorn[20020] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20020,}
gdItemReBorn[20021] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20021,}
gdItemReBorn[20022] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20022,}
gdItemReBorn[20023] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20023,}
gdItemReBorn[20024] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20024,}
gdItemReBorn[20025] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20025,}
gdItemReBorn[20026] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20026,}
gdItemReBorn[20027] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20027,}
gdItemReBorn[20028] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20028,}
----道士4套
gdItemReBorn[20030] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20030,}
gdItemReBorn[20031] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20031,}
gdItemReBorn[20032] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20032,}
gdItemReBorn[20033] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20033,}
gdItemReBorn[20034] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20034,}
gdItemReBorn[20035] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20035,}
gdItemReBorn[20036] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20036,}
gdItemReBorn[20037] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20037,}
gdItemReBorn[20038] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20038,}
----道士5套
gdItemReBorn[20040] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20040,}
gdItemReBorn[20041] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20041,}
gdItemReBorn[20042] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20042,}
gdItemReBorn[20043] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20043,}
gdItemReBorn[20044] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20044,}
gdItemReBorn[20045] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20045,}
gdItemReBorn[20046] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20046,}
gdItemReBorn[20047] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20047,}
gdItemReBorn[20048] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20048,}
-----道士6套
gdItemReBorn[20050] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20050,}
gdItemReBorn[20051] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20051,}
gdItemReBorn[20052] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20052,}
gdItemReBorn[20053] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20053,}
gdItemReBorn[20054] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20054,}
gdItemReBorn[20055] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20055,}
gdItemReBorn[20056] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20056,}
gdItemReBorn[20057] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20057,}
gdItemReBorn[20058] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20058,}
-----道士7套
gdItemReBorn[20200] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20200,}
gdItemReBorn[20201] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20201,}
gdItemReBorn[20202] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20202,}
gdItemReBorn[20203] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20203,}
gdItemReBorn[20204] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20204,}
gdItemReBorn[20205] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20205,}
gdItemReBorn[20206] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20206,}
gdItemReBorn[20207] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20207,}
gdItemReBorn[20208] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20208,}
-----道士8套
gdItemReBorn[20320] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20320,}
gdItemReBorn[20321] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20321,}
gdItemReBorn[20322] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20322,}
gdItemReBorn[20323] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20323,}
gdItemReBorn[20324] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20324,}
gdItemReBorn[20325] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20325,}
gdItemReBorn[20326] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20326,}
gdItemReBorn[20327] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20327,}
gdItemReBorn[20328] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20328,}
-----道士9套
gdItemReBorn[20347] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20320,}
gdItemReBorn[20348] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20321,}
gdItemReBorn[20349] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20322,}
gdItemReBorn[20350] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20323,}
gdItemReBorn[20351] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20324,}
gdItemReBorn[20352] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20325,}
gdItemReBorn[20353] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20326,}
gdItemReBorn[20354] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20327,}
gdItemReBorn[20355] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20328,}
-----道士10套
gdItemReBorn[20520] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20347,}
gdItemReBorn[20521] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20348,}
gdItemReBorn[20522] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20349,}
gdItemReBorn[20523] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20350,}
gdItemReBorn[20524] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20351,}
gdItemReBorn[20525] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20352,}
gdItemReBorn[20526] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20353,}
gdItemReBorn[20527] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20354,}
gdItemReBorn[20528] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20355,}
-----道士11套
gdItemReBorn[20550] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20520,}
gdItemReBorn[20551] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20521,}
gdItemReBorn[20552] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20522,}
gdItemReBorn[20553] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20523,}
gdItemReBorn[20554] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20524,}
gdItemReBorn[20555] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20525,}
gdItemReBorn[20556] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20526,}
gdItemReBorn[20557] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20527,}
gdItemReBorn[20558] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=20528,}


-----------------------------------------------神器升级------------------------------------------------------
-----------------------------------------------神器升级------------------------------------------------------
-----------------------------------------------神器升级------------------------------------------------------
-----------------------------------------------神器升级------------------------------------------------------
gdEquipUpgrade[86000] = {dstEquipId=86006,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[86006] = {dstEquipId=86012,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[86012] = {dstEquipId=86018,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[86018] = {dstEquipId=86024,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}
gdEquipUpgrade[86024] = {dstEquipId=86030,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=50,reqItemId=41003,}

gdEquipUpgrade[86001] = {dstEquipId=86007,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[86002] = {dstEquipId=86008,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[86003] = {dstEquipId=86009,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[86004] = {dstEquipId=86010,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}
gdEquipUpgrade[86005] = {dstEquipId=86011,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=60,reqItemId=41003,}

gdEquipUpgrade[86007] = {dstEquipId=86013,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[86008] = {dstEquipId=86014,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[86009] = {dstEquipId=86015,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[86010] = {dstEquipId=86016,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}
gdEquipUpgrade[86011] = {dstEquipId=86017,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=70,reqItemId=41003,}

gdEquipUpgrade[86013] = {dstEquipId=86019,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=41003,}
gdEquipUpgrade[86014] = {dstEquipId=86020,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=41003,}
gdEquipUpgrade[86015] = {dstEquipId=86021,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=41003,}
gdEquipUpgrade[86016] = {dstEquipId=86022,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=41003,}
gdEquipUpgrade[86017] = {dstEquipId=86023,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=80,reqItemId=41003,}

gdEquipUpgrade[86019] = {dstEquipId=86025,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=90,reqItemId=41003,}
gdEquipUpgrade[86020] = {dstEquipId=86026,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=90,reqItemId=41003,}
gdEquipUpgrade[86021] = {dstEquipId=86027,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=90,reqItemId=41003,}
gdEquipUpgrade[86022] = {dstEquipId=86028,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=90,reqItemId=41003,}
gdEquipUpgrade[86023] = {dstEquipId=86029,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=90,reqItemId=41003,}

gdEquipUpgrade[86025] = {dstEquipId=86031,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=100,reqItemId=41003,}
gdEquipUpgrade[86026] = {dstEquipId=86032,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=100,reqItemId=41003,}
gdEquipUpgrade[86027] = {dstEquipId=86033,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=100,reqItemId=41003,}
gdEquipUpgrade[86028] = {dstEquipId=86034,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=100,reqItemId=41003,}
gdEquipUpgrade[86029] = {dstEquipId=86035,reborncnt=16,rebornreq=40015,reqEhLevel=0,reqGold=10000,reqItemCnt=100,reqItemId=41003,}
---------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------元神升级------------------------------------------
--------------------------------------------------------元神1-1-------------------------------------------------
gdEquipUpgrade[87000] = {dstEquipId=87001, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=10000, reqItemCnt=30, reqItemId=40004,}
gdEquipUpgrade[87001] = {dstEquipId=87002, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=10000, reqItemCnt=40, reqItemId=40004,}
gdEquipUpgrade[87002] = {dstEquipId=87003, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=10000, reqItemCnt=500, reqItemId=40004,}
gdEquipUpgrade[87003] = {dstEquipId=87004, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=10000, reqItemCnt=1000, reqItemId=40004,}
gdEquipUpgrade[87004] = {dstEquipId=87005, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=20000, reqItemCnt=1500, reqItemId=40004,}
gdEquipUpgrade[87005] = {dstEquipId=87006, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=20000, reqItemCnt=2000, reqItemId=40004,}
gdEquipUpgrade[87006] = {dstEquipId=87007, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=20000, reqItemCnt=2500, reqItemId=40004,}
gdEquipUpgrade[87007] = {dstEquipId=87008, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=20000, reqItemCnt=3000, reqItemId=40004,}
gdEquipUpgrade[87008] = {dstEquipId=87009, reborncnt=20, rebornreq=40015, reqEhLevel=0, reqGold=50000, reqItemCnt=5000, reqItemId=40004,}
--------------------------------------------------------元神2-1-------------------------------------------------
gdEquipUpgrade[87100] = {dstEquipId=87101, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=11000, reqItemCnt=35, reqItemId=40004,}
gdEquipUpgrade[87101] = {dstEquipId=87102, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=11000, reqItemCnt=45, reqItemId=40004,}
gdEquipUpgrade[87102] = {dstEquipId=87103, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=11000, reqItemCnt=550, reqItemId=40004,}
gdEquipUpgrade[87103] = {dstEquipId=87104, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=11000, reqItemCnt=1100, reqItemId=40004,}
gdEquipUpgrade[87104] = {dstEquipId=87105, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=22000, reqItemCnt=1650, reqItemId=40004,}
gdEquipUpgrade[87105] = {dstEquipId=87106, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=22000, reqItemCnt=2200, reqItemId=40004,}
gdEquipUpgrade[87106] = {dstEquipId=87107, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=22000, reqItemCnt=2750, reqItemId=40004,}
gdEquipUpgrade[87107] = {dstEquipId=87108, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=22000, reqItemCnt=3300, reqItemId=40004,}
gdEquipUpgrade[87108] = {dstEquipId=87109, reborncnt=20, rebornreq=40015, reqEhLevel=0, reqGold=55000, reqItemCnt=5500, reqItemId=40004,}
--------------------------------------------------------元神3-1-------------------------------------------------
gdEquipUpgrade[87200] = {dstEquipId=87201, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=12000, reqItemCnt=40, reqItemId=40004,}
gdEquipUpgrade[87201] = {dstEquipId=87202, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=12000, reqItemCnt=50, reqItemId=40004,}
gdEquipUpgrade[87202] = {dstEquipId=87203, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=12000, reqItemCnt=600, reqItemId=40004,}
gdEquipUpgrade[87203] = {dstEquipId=87204, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=12000, reqItemCnt=1200, reqItemId=40004,}
gdEquipUpgrade[87204] = {dstEquipId=87205, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=24000, reqItemCnt=1800, reqItemId=40004,}
gdEquipUpgrade[87205] = {dstEquipId=87206, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=24000, reqItemCnt=2400, reqItemId=40004,}
gdEquipUpgrade[87206] = {dstEquipId=87207, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=24000, reqItemCnt=3000, reqItemId=40004,}
gdEquipUpgrade[87207] = {dstEquipId=87208, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=24000, reqItemCnt=3600, reqItemId=40004,}
gdEquipUpgrade[87208] = {dstEquipId=87209, reborncnt=20, rebornreq=40015, reqEhLevel=0, reqGold=60000, reqItemCnt=6000, reqItemId=40004,}
--------------------------------------------------------元神4-1-------------------------------------------------
gdEquipUpgrade[87300] = {dstEquipId=87301, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=13000, reqItemCnt=45, reqItemId=40004,}
gdEquipUpgrade[87301] = {dstEquipId=87302, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=13000, reqItemCnt=55, reqItemId=40004,}
gdEquipUpgrade[87302] = {dstEquipId=87303, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=13000, reqItemCnt=650, reqItemId=40004,}
gdEquipUpgrade[87303] = {dstEquipId=87304, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=13000, reqItemCnt=1300, reqItemId=40004,}
gdEquipUpgrade[87304] = {dstEquipId=87305, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=26000, reqItemCnt=1950, reqItemId=40004,}
gdEquipUpgrade[87305] = {dstEquipId=87306, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=26000, reqItemCnt=2600, reqItemId=40004,}
gdEquipUpgrade[87306] = {dstEquipId=87307, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=26000, reqItemCnt=3250, reqItemId=40004,}
gdEquipUpgrade[87307] = {dstEquipId=87308, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=26000, reqItemCnt=3900, reqItemId=40004,}
gdEquipUpgrade[87308] = {dstEquipId=87309, reborncnt=20, rebornreq=40015, reqEhLevel=0, reqGold=65000, reqItemCnt=6500, reqItemId=40004,}
--------------------------------------------------------元神5-1-------------------------------------------------
gdEquipUpgrade[87400] = {dstEquipId=87401, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=14000, reqItemCnt=50, reqItemId=40004,}
gdEquipUpgrade[87401] = {dstEquipId=87402, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=14000, reqItemCnt=60, reqItemId=40004,}
gdEquipUpgrade[87402] = {dstEquipId=87403, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=14000, reqItemCnt=700, reqItemId=40004,}
gdEquipUpgrade[87403] = {dstEquipId=87404, reborncnt=16, rebornreq=40015, reqEhLevel=0, reqGold=14000, reqItemCnt=1400, reqItemId=40004,}
gdEquipUpgrade[87404] = {dstEquipId=87405, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=28000, reqItemCnt=2100, reqItemId=40004,}
gdEquipUpgrade[87405] = {dstEquipId=87406, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=28000, reqItemCnt=2800, reqItemId=40004,}
gdEquipUpgrade[87406] = {dstEquipId=87407, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=28000, reqItemCnt=3500, reqItemId=40004,}
gdEquipUpgrade[87407] = {dstEquipId=87408, reborncnt=18, rebornreq=40015, reqEhLevel=0, reqGold=28000, reqItemCnt=4200, reqItemId=40004,}
gdEquipUpgrade[87408] = {dstEquipId=87409, reborncnt=20, rebornreq=40015, reqEhLevel=0, reqGold=70000, reqItemCnt=7000, reqItemId=40004,}
---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------



gdItemReBorn[60001] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60001,}
gdItemReBorn[60011] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60011,}
gdItemReBorn[60021] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60021,}
gdItemReBorn[60031] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60031,}
gdItemReBorn[60041] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60041,}
gdItemReBorn[60051] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60051,}
gdItemReBorn[60000] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60000,}
gdItemReBorn[60010] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60010,}
gdItemReBorn[60020] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60020,}
gdItemReBorn[60030] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60030,}
gdItemReBorn[60040] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60040,}
gdItemReBorn[60050] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60050,}
gdItemReBorn[60002] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60002,}
gdItemReBorn[60012] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60012,}
gdItemReBorn[60022] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60022,}
gdItemReBorn[60032] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60032,}
gdItemReBorn[60042] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60042,}
gdItemReBorn[60052] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60052,}
gdItemReBorn[60003] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60003,}
gdItemReBorn[60013] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60013,}
gdItemReBorn[60023] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60023,}
gdItemReBorn[60033] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60033,}
gdItemReBorn[60043] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60043,}
gdItemReBorn[60053] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60053,}
gdItemReBorn[60004] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60004,}
gdItemReBorn[60014] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60014,}
gdItemReBorn[60024] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60024,}
gdItemReBorn[60034] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60034,}
gdItemReBorn[60044] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60044,}
gdItemReBorn[60054] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60054,}
gdItemReBorn[60005] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60005,}
gdItemReBorn[60015] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60015,}
gdItemReBorn[60025] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60025,}
gdItemReBorn[60035] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60035,}
gdItemReBorn[60045] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60045,}
gdItemReBorn[60055] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60055,}
gdItemReBorn[60006] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60006,}
gdItemReBorn[60016] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60016,}
gdItemReBorn[60026] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60026,}
gdItemReBorn[60036] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60036,}
gdItemReBorn[60046] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60046,}
gdItemReBorn[60056] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60056,}
gdItemReBorn[60007] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60007,}
gdItemReBorn[60017] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60017,}
gdItemReBorn[60027] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60027,}
gdItemReBorn[60037] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60037,}
gdItemReBorn[60047] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60047,}
gdItemReBorn[60057] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60057,}
gdItemReBorn[60008] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60008,}
gdItemReBorn[60018] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60018,}
gdItemReBorn[60028] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60028,}
gdItemReBorn[60038] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60038,}
gdItemReBorn[60048] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60048,}
gdItemReBorn[60058] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60058,}
gdItemReBorn[60060] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60060,}
gdItemReBorn[60070] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60070,}
gdItemReBorn[60080] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60080,}
gdItemReBorn[60090] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60090,}
gdItemReBorn[60100] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60100,}
gdItemReBorn[60110] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60110,}
gdItemReBorn[60061] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60061,}
gdItemReBorn[60071] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60071,}
gdItemReBorn[60081] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60081,}
gdItemReBorn[60091] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60091,}
gdItemReBorn[60101] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60101,}
gdItemReBorn[60111] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60111,}
gdItemReBorn[60062] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60062,}
gdItemReBorn[60072] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60072,}
gdItemReBorn[60082] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60082,}
gdItemReBorn[60092] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60092,}
gdItemReBorn[60102] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60102,}
gdItemReBorn[60112] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60112,}
gdItemReBorn[60063] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60063,}
gdItemReBorn[60073] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60073,}
gdItemReBorn[60083] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60083,}
gdItemReBorn[60093] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60093,}
gdItemReBorn[60103] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60103,}
gdItemReBorn[60113] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60113,}
gdItemReBorn[60064] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60064,}
gdItemReBorn[60074] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60074,}
gdItemReBorn[60084] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60084,}
gdItemReBorn[60094] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60094,}
gdItemReBorn[60104] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60104,}
gdItemReBorn[60114] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60114,}
gdItemReBorn[60065] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60065,}
gdItemReBorn[60075] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60075,}
gdItemReBorn[60085] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60085,}
gdItemReBorn[60095] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60095,}
gdItemReBorn[60105] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60105,}
gdItemReBorn[60115] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60115,}
gdItemReBorn[60066] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60066,}
gdItemReBorn[60076] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60076,}
gdItemReBorn[60086] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60086,}
gdItemReBorn[60096] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60096,}
gdItemReBorn[60106] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60106,}
gdItemReBorn[60116] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60116,}
gdItemReBorn[60067] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60067,}
gdItemReBorn[60077] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60077,}
gdItemReBorn[60087] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60087,}
gdItemReBorn[60097] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60097,}
gdItemReBorn[60107] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60107,}
gdItemReBorn[60117] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60117,}
gdItemReBorn[60068] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60068,}
gdItemReBorn[60078] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60078,}
gdItemReBorn[60088] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60088,}
gdItemReBorn[60098] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60098,}
gdItemReBorn[60108] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60108,}
gdItemReBorn[60118] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60118,}
gdItemReBorn[60120] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60120,}
gdItemReBorn[60130] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60130,}
gdItemReBorn[60140] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60140,}
gdItemReBorn[60150] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60150,}
gdItemReBorn[60160] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60160,}
gdItemReBorn[60170] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60170,}
gdItemReBorn[60121] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60121,}
gdItemReBorn[60131] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60131,}
gdItemReBorn[60141] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60141,}
gdItemReBorn[60151] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60151,}
gdItemReBorn[60161] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60161,}
gdItemReBorn[60171] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60171,}
gdItemReBorn[60122] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60122,}
gdItemReBorn[60132] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60132,}
gdItemReBorn[60142] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60142,}
gdItemReBorn[60152] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60152,}
gdItemReBorn[60162] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60162,}
gdItemReBorn[60172] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60172,}
gdItemReBorn[60123] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60123,}
gdItemReBorn[60133] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60133,}
gdItemReBorn[60143] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60143,}
gdItemReBorn[60153] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60153,}
gdItemReBorn[60163] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60163,}
gdItemReBorn[60173] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60173,}
gdItemReBorn[60124] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60124,}
gdItemReBorn[60134] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60134,}
gdItemReBorn[60144] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60144,}
gdItemReBorn[60154] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60154,}
gdItemReBorn[60164] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60164,}
gdItemReBorn[60174] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60174,}
gdItemReBorn[60125] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60125,}
gdItemReBorn[60135] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60135,}
gdItemReBorn[60145] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60145,}
gdItemReBorn[60155] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60155,}
gdItemReBorn[60165] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60165,}
gdItemReBorn[60175] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60175,}
gdItemReBorn[60126] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60126,}
gdItemReBorn[60136] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60136,}
gdItemReBorn[60146] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60146,}
gdItemReBorn[60156] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60156,}
gdItemReBorn[60166] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60166,}
gdItemReBorn[60176] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60176,}
gdItemReBorn[60127] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60127,}
gdItemReBorn[60137] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60137,}
gdItemReBorn[60147] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60147,}
gdItemReBorn[60157] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60157,}
gdItemReBorn[60167] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60167,}
gdItemReBorn[60177] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60177,}
gdItemReBorn[60128] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60128,}
gdItemReBorn[60138] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60138,}
gdItemReBorn[60148] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60148,}
gdItemReBorn[60158] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60158,}
gdItemReBorn[60168] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60168,}
gdItemReBorn[60178] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60178,}
gdItemReBorn[60202] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60202,}
gdItemReBorn[60203] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60203,}
gdItemReBorn[60204] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60204,}
gdItemReBorn[60205] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60205,}
gdItemReBorn[60206] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60206,}
gdItemReBorn[60207] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60207,}
gdItemReBorn[60209] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60209,}
gdItemReBorn[60210] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60210,}
gdItemReBorn[60211] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60211,}
gdItemReBorn[60212] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60212,}
gdItemReBorn[60213] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60213,}
gdItemReBorn[60214] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60214,}
gdItemReBorn[60216] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60216,}
gdItemReBorn[60217] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60217,}
gdItemReBorn[60218] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60218,}
gdItemReBorn[60219] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60219,}
gdItemReBorn[60220] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60220,}
gdItemReBorn[60221] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60221,}
gdItemReBorn[60180] = {reqExtramoney=0,reqcnt=10,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60181] = {reqExtramoney=0,reqcnt=4,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60182] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60183] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60184] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60185] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60186] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60187] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60188] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60189] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60191] = {reqExtramoney=0,reqcnt=10,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60192] = {reqExtramoney=0,reqcnt=4,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60193] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60194] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60195] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60196] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60197] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60198] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60199] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60200] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60276] = {reqExtramoney=0,reqcnt=30,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60277] = {reqExtramoney=0,reqcnt=15,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60278] = {reqExtramoney=0,reqcnt=15,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60279] = {reqExtramoney=0,reqcnt=12,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60280] = {reqExtramoney=0,reqcnt=6,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60281] = {reqExtramoney=0,reqcnt=6,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60282] = {reqExtramoney=0,reqcnt=9,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60283] = {reqExtramoney=0,reqcnt=6,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60284] = {reqExtramoney=0,reqcnt=9,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60337] = {reqExtramoney=0,reqcnt=10,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60338] = {reqExtramoney=0,reqcnt=4,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60339] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60340] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60341] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60342] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60343] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60344] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60345] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60346] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60349] = {reqExtramoney=0,reqcnt=10,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60350] = {reqExtramoney=0,reqcnt=4,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60351] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60352] = {reqExtramoney=0,reqcnt=5,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60353] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60354] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60355] = {reqExtramoney=0,reqcnt=3,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60356] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60357] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[60358] = {reqExtramoney=0,reqcnt=2,reqid=40015,reqmoney=1150000,second=0,}
gdItemReBorn[81000] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81000,}
gdItemReBorn[81001] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81001,}
gdItemReBorn[81002] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81002,}
gdItemReBorn[81003] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81003,}
gdItemReBorn[81004] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81004,}
gdItemReBorn[81005] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81005,}
gdItemReBorn[81006] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81006,}
gdItemReBorn[81007] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81007,}
gdItemReBorn[81008] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81008,}
gdItemReBorn[81009] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81009,}
gdItemReBorn[81033] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81033,}
gdItemReBorn[81034] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81034,}
gdItemReBorn[81035] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81035,}
gdItemReBorn[81036] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81036,}
gdItemReBorn[81037] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81037,}
gdItemReBorn[81038] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81038,}
gdItemReBorn[81039] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81039,}
gdItemReBorn[81040] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81040,}
gdItemReBorn[81041] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81041,}
gdItemReBorn[81042] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81042,}
gdItemReBorn[81044] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81044,}
gdItemReBorn[81045] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81045,}
gdItemReBorn[81046] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81046,}
gdItemReBorn[81047] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81047,}
gdItemReBorn[81048] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81048,}
gdItemReBorn[81049] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81049,}
gdItemReBorn[81050] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81050,}
gdItemReBorn[81051] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81051,}
gdItemReBorn[81052] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81052,}
gdItemReBorn[81053] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81053,}
gdItemReBorn[81055] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81055,}
gdItemReBorn[81056] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81056,}
gdItemReBorn[81057] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81057,}
gdItemReBorn[81058] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81058,}
gdItemReBorn[81059] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81059,}
gdItemReBorn[81060] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81060,}
gdItemReBorn[81061] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81061,}
gdItemReBorn[81062] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81062,}
gdItemReBorn[81063] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81063,}
gdItemReBorn[81064] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81064,}
gdItemReBorn[81066] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81066,}
gdItemReBorn[81067] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81067,}
gdItemReBorn[81068] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81068,}
gdItemReBorn[81069] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81069,}
gdItemReBorn[81070] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81070,}
gdItemReBorn[81071] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81071,}
gdItemReBorn[81072] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81072,}
gdItemReBorn[81073] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81073,}
gdItemReBorn[81074] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81074,}
gdItemReBorn[81076] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81076,}
gdItemReBorn[81077] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81077,}
gdItemReBorn[81078] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81078,}
gdItemReBorn[81079] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81079,}
gdItemReBorn[81080] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81080,}
gdItemReBorn[81081] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81081,}
gdItemReBorn[81082] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81082,}
gdItemReBorn[81083] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81083,}
gdItemReBorn[81084] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81084,}
gdItemReBorn[81086] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81086,}
gdItemReBorn[81087] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81087,}
gdItemReBorn[81088] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81088,}
gdItemReBorn[81089] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81089,}
gdItemReBorn[81090] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81090,}
gdItemReBorn[81092] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81092,}
gdItemReBorn[81093] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81093,}
gdItemReBorn[81094] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81094,}
gdItemReBorn[81095] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81095,}
gdItemReBorn[81096] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81096,}
gdItemReBorn[0] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=0,}
gdItemReBorn[60223] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60223,}
gdItemReBorn[60224] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60224,}
gdItemReBorn[60225] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60225,}
gdItemReBorn[60226] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60226,}
gdItemReBorn[60227] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60227,}
gdItemReBorn[60228] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60228,}
gdItemReBorn[60229] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60229,}
gdItemReBorn[0] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=0,}
gdItemReBorn[60231] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60231,}
gdItemReBorn[60232] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60232,}
gdItemReBorn[60233] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60233,}
gdItemReBorn[60234] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60234,}
gdItemReBorn[60235] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60235,}
gdItemReBorn[60236] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60236,}
gdItemReBorn[60237] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60237,}
gdItemReBorn[0] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=0,}
gdItemReBorn[60239] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60239,}
gdItemReBorn[60240] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60240,}
gdItemReBorn[60241] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60241,}
gdItemReBorn[60242] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60242,}
gdItemReBorn[60243] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60243,}
gdItemReBorn[60244] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60244,}
gdItemReBorn[60245] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=1150000,second=60245,}
gdItemReBorn[0] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=0,}
gdItemReBorn[81140] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81140,}
gdItemReBorn[81141] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81141,}
gdItemReBorn[81142] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81142,}
gdItemReBorn[81143] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81143,}
gdItemReBorn[81144] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81144,}
gdItemReBorn[81145] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81145,}
gdItemReBorn[81146] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81146,}
gdItemReBorn[81147] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81147,}
gdItemReBorn[81148] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81148,}
gdItemReBorn[81149] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81149,}
gdItemReBorn[0] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=0,}
gdItemReBorn[81222] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81222,}
gdItemReBorn[81223] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81223,}
gdItemReBorn[81224] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81224,}
gdItemReBorn[81225] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81225,}
gdItemReBorn[81226] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81226,}
gdItemReBorn[81227] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81227,}
gdItemReBorn[81228] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81228,}
gdItemReBorn[81229] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81229,}
gdItemReBorn[81230] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81230,}
gdItemReBorn[81231] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81231,}
gdItemReBorn[81232] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81232,}
gdItemReBorn[81233] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81233,}
gdItemReBorn[81234] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81234,}
gdItemReBorn[81235] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81235,}
gdItemReBorn[81236] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81236,}
gdItemReBorn[81237] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81237,}
gdItemReBorn[81238] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81238,}
gdItemReBorn[81239] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81239,}
gdItemReBorn[81240] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81240,}
gdItemReBorn[81241] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81241,}
gdItemReBorn[81242] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81242,}
gdItemReBorn[81243] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81243,}
gdItemReBorn[81244] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81244,}
gdItemReBorn[81245] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81245,}
gdItemReBorn[81246] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81246,}
gdItemReBorn[81247] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81247,}
gdItemReBorn[81248] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81248,}
gdItemReBorn[81249] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81249,}
gdItemReBorn[81250] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81250,}
gdItemReBorn[81251] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81251,}
gdItemReBorn[81252] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81252,}
gdItemReBorn[81253] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81253,}
gdItemReBorn[81254] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81254,}
gdItemReBorn[81255] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81255,}
gdItemReBorn[81256] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81256,}
gdItemReBorn[81257] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81257,}
gdItemReBorn[81258] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81258,}
gdItemReBorn[81259] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81259,}
gdItemReBorn[81260] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81260,}
gdItemReBorn[81261] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81261,}
gdItemReBorn[81262] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81262,}
gdItemReBorn[81263] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81263,}
gdItemReBorn[81264] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81264,}
gdItemReBorn[81265] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81265,}
gdItemReBorn[81266] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81266,}
gdItemReBorn[81267] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81267,}
gdItemReBorn[81268] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81268,}
gdItemReBorn[81269] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81269,}
gdItemReBorn[81270] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81270,}
gdItemReBorn[81271] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81271,}
gdItemReBorn[81272] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81272,}
gdItemReBorn[81273] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81273,}
gdItemReBorn[81274] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81274,}
gdItemReBorn[81275] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81275,}
gdItemReBorn[81276] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81276,}
gdItemReBorn[81277] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81277,}
gdItemReBorn[81278] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81278,}
gdItemReBorn[81279] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81279,}
gdItemReBorn[81280] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81280,}
gdItemReBorn[81281] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81281,}
gdItemReBorn[81282] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81282,}
gdItemReBorn[81283] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81283,}
gdItemReBorn[81284] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81284,}
gdItemReBorn[81285] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81285,}
gdItemReBorn[81286] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81286,}
gdItemReBorn[0] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=0,}
gdItemReBorn[81109] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81109,}
gdItemReBorn[81110] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81110,}
gdItemReBorn[81111] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81111,}
gdItemReBorn[81112] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81112,}
gdItemReBorn[81113] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81113,}
gdItemReBorn[81114] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81114,}
gdItemReBorn[81115] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81115,}
gdItemReBorn[81116] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81116,}
gdItemReBorn[81117] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81117,}
gdItemReBorn[81118] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81118,}
gdItemReBorn[81119] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81119,}
gdItemReBorn[81120] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81120,}
gdItemReBorn[81121] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81121,}
gdItemReBorn[81122] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81122,}
gdItemReBorn[81123] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81123,}
gdItemReBorn[81124] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81124,}
gdItemReBorn[81125] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81125,}
gdItemReBorn[81126] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81126,}
gdItemReBorn[81127] = {reqExtramoney=0,reqcnt=0,reqid=0,reqmoney=0,second=81127,}

----------------------------------------暗影装备转身-----------------------------------
gdItemReBorn[20560] = {reqExtramoney=0,reqcnt=300,reqid=30092,reqmoney=1150000,second=0,}
gdItemReBorn[82085] = {reqExtramoney=0,reqcnt=300,reqid=30092,reqmoney=1150000,second=0,}
gdItemReBorn[20559] = {reqExtramoney=0,reqcnt=300,reqid=30092,reqmoney=1150000,second=0,}
gdItemReBorn[80031] = {reqExtramoney=0,reqcnt=300,reqid=30092,reqmoney=1150000,second=0,}
gdItemReBorn[83083] = {reqExtramoney=0,reqcnt=300,reqid=30092,reqmoney=1150000,second=0,}

--暗影元神转身
gdItemReBorn[87410] = {reqExtramoney=0,reqcnt=300,reqid=30092,reqmoney=1150000,second=0,}





---------------------------------------------------------------------------------------
gdItemRepair[0] = {lvl=0,money=15,}
gdItemRepair[1] = {lvl=1,money=15,}
gdItemRepair[2] = {lvl=2,money=15,}
gdItemRepair[3] = {lvl=3,money=15,}
gdItemRepair[4] = {lvl=4,money=15,}
gdItemRepair[5] = {lvl=5,money=15,}
gdItemRepair[6] = {lvl=6,money=15,}
gdItemRepair[7] = {lvl=7,money=15,}
gdItemRepair[8] = {lvl=8,money=15,}
gdItemRepair[9] = {lvl=9,money=15,}
gdItemRepair[10] = {lvl=10,money=15,}
gdItemRepair[11] = {lvl=11,money=15,}
gdItemRepair[12] = {lvl=12,money=15,}
gdItemRepair[13] = {lvl=13,money=15,}
gdItemRepair[14] = {lvl=14,money=15,}
gdItemRepair[15] = {lvl=15,money=15,}
gdItemRepair[16] = {lvl=16,money=15,}
gdItemRepair[17] = {lvl=17,money=15,}
gdItemRepair[18] = {lvl=18,money=15,}
gdItemRepair[19] = {lvl=19,money=15,}
gdItemRepair[20] = {lvl=20,money=15,}
gdItemRepair[21] = {lvl=21,money=15,}
gdItemRepair[22] = {lvl=22,money=15,}
gdItemRepair[23] = {lvl=23,money=15,}
gdItemRepair[24] = {lvl=24,money=15,}
gdItemRepair[25] = {lvl=25,money=15,}
gdItemRepair[26] = {lvl=26,money=15,}
gdItemRepair[27] = {lvl=27,money=15,}
gdItemRepair[28] = {lvl=28,money=15,}
gdItemRepair[29] = {lvl=29,money=15,}
gdItemRepair[30] = {lvl=30,money=15,}
gdItemRepair[31] = {lvl=31,money=15,}
gdItemRepair[32] = {lvl=32,money=15,}
gdItemRepair[33] = {lvl=33,money=15,}
gdItemRepair[34] = {lvl=34,money=15,}
gdItemRepair[35] = {lvl=35,money=15,}
gdItemRepair[36] = {lvl=36,money=15,}
gdItemRepair[37] = {lvl=37,money=15,}
gdItemRepair[38] = {lvl=38,money=15,}
gdItemRepair[39] = {lvl=39,money=15,}
gdItemRepair[40] = {lvl=40,money=45,}
gdItemRepair[41] = {lvl=41,money=45,}
gdItemRepair[42] = {lvl=42,money=45,}
gdItemRepair[43] = {lvl=43,money=45,}
gdItemRepair[44] = {lvl=44,money=45,}
gdItemRepair[45] = {lvl=45,money=65,}
gdItemRepair[46] = {lvl=46,money=65,}
gdItemRepair[47] = {lvl=47,money=65,}
gdItemRepair[48] = {lvl=48,money=65,}
gdItemRepair[49] = {lvl=49,money=65,}
gdItemRepair[50] = {lvl=50,money=250,}
gdItemRepair[51] = {lvl=51,money=250,}
gdItemRepair[52] = {lvl=52,money=250,}
gdItemRepair[53] = {lvl=53,money=250,}
gdItemRepair[54] = {lvl=54,money=250,}
gdItemRepair[55] = {lvl=55,money=350,}
gdItemRepair[56] = {lvl=56,money=350,}
gdItemRepair[57] = {lvl=57,money=350,}
gdItemRepair[58] = {lvl=58,money=350,}
gdItemRepair[59] = {lvl=59,money=350,}
gdItemRepair[60] = {lvl=60,money=500,}
gdItemRepair[61] = {lvl=61,money=500,}
gdItemRepair[62] = {lvl=62,money=500,}
gdItemRepair[63] = {lvl=63,money=500,}
gdItemRepair[64] = {lvl=64,money=500,}
gdItemRepair[65] = {lvl=65,money=500,}
gdItemRepair[66] = {lvl=66,money=500,}
gdItemRepair[67] = {lvl=67,money=500,}
gdItemRepair[68] = {lvl=68,money=500,}
gdItemRepair[69] = {lvl=69,money=500,}
gdItemRepair[70] = {lvl=70,money=600,}
gdWingEnhance[0] = {attackvalue=1,defenceM=1,defenceP=5,firstCnt=2,firstItem=40077,probability=90,reqGold=10000,secondCnt=0,secondItem=0,shouldbesucceed=1,}
gdWingEnhance[1] = {attackvalue=3,defenceM=5,defenceP=10,firstCnt=4,firstItem=40077,probability=80,reqGold=10000,secondCnt=0,secondItem=0,shouldbesucceed=2,}
gdWingEnhance[2] = {attackvalue=5,defenceM=10,defenceP=15,firstCnt=7,firstItem=40077,probability=70,reqGold=10000,secondCnt=0,secondItem=0,shouldbesucceed=3,}
gdWingEnhance[3] = {attackvalue=7,defenceM=15,defenceP=20,firstCnt=11,firstItem=40077,probability=65,reqGold=10000,secondCnt=0,secondItem=0,shouldbesucceed=4,}
gdWingEnhance[4] = {attackvalue=10,defenceM=20,defenceP=25,firstCnt=15,firstItem=40077,probability=60,reqGold=10000,secondCnt=0,secondItem=0,shouldbesucceed=5,}
gdWingEnhance[5] = {attackvalue=15,defenceM=25,defenceP=35,firstCnt=20,firstItem=40077,probability=55,reqGold=10000,secondCnt=10,secondItem=40011,shouldbesucceed=6,}
gdWingEnhance[6] = {attackvalue=20,defenceM=35,defenceP=50,firstCnt=25,firstItem=40077,probability=50,reqGold=10000,secondCnt=20,secondItem=40011,shouldbesucceed=7,}
gdWingEnhance[7] = {attackvalue=30,defenceM=55,defenceP=80,firstCnt=30,firstItem=40077,probability=45,reqGold=10000,secondCnt=30,secondItem=40011,shouldbesucceed=8,}
gdWingEnhance[8] = {attackvalue=45,defenceM=80,defenceP=110,firstCnt=35,firstItem=40077,probability=40,reqGold=10000,secondCnt=40,secondItem=40011,shouldbesucceed=9,}
gdWingEnhance[9] = {attackvalue=80,defenceM=135,defenceP=190,firstCnt=40,firstItem=40077,probability=35,reqGold=10000,secondCnt=50,secondItem=40011,shouldbesucceed=10,}
gdWingEnhance[10] = {attackvalue=105,defenceM=190,defenceP=270,firstCnt=45,firstItem=40077,probability=30,reqGold=10000,secondCnt=60,secondItem=40011,shouldbesucceed=11,}
gdWingEnhance[11] = {attackvalue=135,defenceM=245,defenceP=350,firstCnt=50,firstItem=40077,probability=25,reqGold=10000,secondCnt=70,secondItem=40011,shouldbesucceed=12,}
gdWingEnhance[12] = {attackvalue=170,defenceM=300,defenceP=430,firstCnt=55,firstItem=40077,probability=20,reqGold=10000,secondCnt=80,secondItem=40011,shouldbesucceed=13,}
gdWingEnhance[13] = {attackvalue=203,defenceM=360,defenceP=505,firstCnt=60,firstItem=40077,probability=15,reqGold=10000,secondCnt=90,secondItem=40011,shouldbesucceed=14,}
gdWingEnhance[14] = {attackvalue=304,defenceM=545,defenceP=755,firstCnt=65,firstItem=40077,probability=10,reqGold=10000,secondCnt=100,secondItem=40011,shouldbesucceed=15,}
gdBestEvaluate[1] = {name="最小物理攻击",attrtype=5,maxValue=50,minValue=10,}
gdBestEvaluate[2] = {name="最小道术攻击",attrtype=9,maxValue=50,minValue=10,}
gdBestEvaluate[3] = {name="最小魔法攻击",attrtype=7,maxValue=50,minValue=10,}
gdBestEvaluate[4] = {name="最大物理攻击",attrtype=6,maxValue=30,minValue=5,}
gdBestEvaluate[5] = {name="最大道术攻击",attrtype=10,maxValue=30,minValue=5,}
gdBestEvaluate[6] = {name="最大魔法攻击",attrtype=8,maxValue=30,minValue=5,}
gdBestEvaluate[7] = {name="最小物理防御",attrtype=11,maxValue=35,minValue=5,}
gdBestEvaluate[8] = {name="最大物理防御",attrtype=12,maxValue=30,minValue=5,}
gdBestEvaluate[9] = {name="最小魔法防御",attrtype=13,maxValue=35,minValue=5,}
gdBestEvaluate[10] = {name="最大魔法防御",attrtype=14,maxValue=30,minValue=5,}
gdBestEvaluate[11] = {name="生命值上限",attrtype=1,maxValue=299,minValue=99,}
gdBestEvaluate[12] = {name="魔法值上限",attrtype=2,maxValue=299,minValue=99,}
gdOpenMagicWeapon[0] = {lvlcnt=50,lvluppro=200,qilingValue=9,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=1,}
gdOpenMagicWeapon[1] = {lvlcnt=70,lvluppro=150,qilingValue=12,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=2,}
gdOpenMagicWeapon[2] = {lvlcnt=90,lvluppro=100,qilingValue=18,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=3,}
gdOpenMagicWeapon[3] = {lvlcnt=110,lvluppro=100,qilingValue=25,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=4,}
gdOpenMagicWeapon[4] = {lvlcnt=130,lvluppro=75,qilingValue=34,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=5,}
gdOpenMagicWeapon[5] = {lvlcnt=150,lvluppro=60,qilingValue=49,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=6,}
gdOpenMagicWeapon[6] = {lvlcnt=170,lvluppro=40,qilingValue=68,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=7,}
gdOpenMagicWeapon[7] = {lvlcnt=190,lvluppro=35,qilingValue=102,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=8,}
gdOpenMagicWeapon[8] = {lvlcnt=210,lvluppro=30,qilingValue=153,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=9,}
gdOpenMagicWeapon[9] = {lvlcnt=230,lvluppro=25,qilingValue=208,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=10,}
gdOpenMagicWeapon[10] = {lvlcnt=250,lvluppro=20,qilingValue=288,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=11,}
gdOpenMagicWeapon[11] = {lvlcnt=270,lvluppro=10,qilingValue=368,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=12,}
gdOpenMagicWeapon[12] = {lvlcnt=290,lvluppro=35,qilingValue=490,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=13,}
gdOpenMagicWeapon[13] = {lvlcnt=310,lvluppro=30,qilingValue=684,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=14,}
gdOpenMagicWeapon[14] = {lvlcnt=330,lvluppro=10,qilingValue=888,reqCnt=2,reqGold=10000,reqId=40071,tgtlvl=15,}
gdFootUp[83000] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83001,upValue=50,}
gdFootUp[83001] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83002,upValue=70,}
gdFootUp[83002] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83003,upValue=90,}
gdFootUp[83003] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83004,upValue=110,}
gdFootUp[83004] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83005,upValue=130,}
gdFootUp[83005] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83006,upValue=150,}
gdFootUp[83006] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83007,upValue=170,}
gdFootUp[83007] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83008,upValue=190,}
gdFootUp[83008] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83009,upValue=210,}
gdFootUp[83009] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83010,upValue=230,}
gdFootUp[83010] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83011,upValue=250,}
gdFootUp[83011] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83012,upValue=270,}
gdFootUp[83012] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83013,upValue=290,}
gdFootUp[83013] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83014,upValue=310,}
gdFootUp[83014] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83015,upValue=330,}
gdFootUp[83015] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83016,upValue=350,}
gdFootUp[83016] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83017,upValue=370,}
gdFootUp[83017] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83018,upValue=390,}
gdFootUp[83018] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83019,upValue=410,}
gdFootUp[83021] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83022,upValue=50,}
gdFootUp[83022] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83023,upValue=70,}
gdFootUp[83023] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83024,upValue=90,}
gdFootUp[83024] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83025,upValue=110,}
gdFootUp[83025] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83026,upValue=130,}
gdFootUp[83026] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83027,upValue=150,}
gdFootUp[83027] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83028,upValue=170,}
gdFootUp[83028] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83029,upValue=190,}
gdFootUp[83029] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83030,upValue=210,}
gdFootUp[83030] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83031,upValue=230,}
gdFootUp[83031] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83032,upValue=250,}
gdFootUp[83032] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83033,upValue=270,}
gdFootUp[83033] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83034,upValue=290,}
gdFootUp[83034] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83035,upValue=310,}
gdFootUp[83035] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83036,upValue=330,}
gdFootUp[83036] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83037,upValue=350,}
gdFootUp[83037] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83038,upValue=370,}
gdFootUp[83038] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83039,upValue=390,}
gdFootUp[83039] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83040,upValue=410,}
gdFootUp[83042] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83043,upValue=50,}
gdFootUp[83043] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83044,upValue=70,}
gdFootUp[83044] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83045,upValue=90,}
gdFootUp[83045] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83046,upValue=110,}
gdFootUp[83046] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83047,upValue=130,}
gdFootUp[83047] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83048,upValue=150,}
gdFootUp[83048] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83049,upValue=170,}
gdFootUp[83049] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83050,upValue=190,}
gdFootUp[83050] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83051,upValue=210,}
gdFootUp[83051] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83052,upValue=230,}
gdFootUp[83052] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83053,upValue=250,}
gdFootUp[83053] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83054,upValue=270,}
gdFootUp[83054] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83055,upValue=290,}
gdFootUp[83055] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83056,upValue=310,}
gdFootUp[83056] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83057,upValue=330,}
gdFootUp[83057] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83058,upValue=350,}
gdFootUp[83058] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83059,upValue=370,}
gdFootUp[83059] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83060,upValue=390,}
gdFootUp[83060] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83061,upValue=410,}
gdFootUp[83063] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83064,upValue=50,}
gdFootUp[83064] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83065,upValue=70,}
gdFootUp[83065] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83066,upValue=90,}
gdFootUp[83066] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83067,upValue=110,}
gdFootUp[83067] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83068,upValue=130,}
gdFootUp[83068] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83069,upValue=150,}
gdFootUp[83069] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83070,upValue=170,}
gdFootUp[83070] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83071,upValue=190,}
gdFootUp[83071] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83072,upValue=210,}
gdFootUp[83072] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83073,upValue=230,}
gdFootUp[83073] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83074,upValue=250,}
gdFootUp[83074] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83075,upValue=270,}
gdFootUp[83075] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83076,upValue=290,}
gdFootUp[83076] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83077,upValue=310,}
gdFootUp[83077] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83078,upValue=330,}
gdFootUp[83078] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83079,upValue=350,}
gdFootUp[83079] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83080,upValue=370,}
gdFootUp[83080] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83081,upValue=390,}
gdFootUp[83081] = {reqCnt=4,reqGold=10000,reqId=40016,tgtlvl=83082,upValue=410,}
gdFuMo = {
	itemCfgID=40148,
	itemCount=1,
	money=1000,
	prop= {
			[1]= {id=1,attrname="最小物理攻击",attrtype=5,maxValue=20,minValue=10,},
			[2]= {id=2,attrname="最小道术攻击",attrtype=9,maxValue=20,minValue=10,},
			[3]= {id=3,attrname="最小魔法攻击",attrtype=7,maxValue=20,minValue=10,},
			[4]= {id=4,attrname="最大物理攻击",attrtype=6,maxValue=20,minValue=10,},
			[5]= {id=5,attrname="最大道术攻击",attrtype=10,maxValue=20,minValue=10,},
			[6]= {id=6,attrname="最大魔法攻击",attrtype=8,maxValue=20,minValue=10,},
			[7]= {id=7,attrname="最小物理防御",attrtype=11,maxValue=20,minValue=10,},
			[8]= {id=8,attrname="最大物理防御",attrtype=12,maxValue=20,minValue=10,},
			[9]= {id=9,attrname="最小魔法防御",attrtype=13,maxValue=20,minValue=10,},
			[10]= {id=10,attrname="最大魔法防御",attrtype=14,maxValue=20,minValue=10,},
			[11]= {id=11,attrname="毒物恢复",attrtype=22,maxValue=5,minValue=2,},
			[12]= {id=12,attrname="生命恢复",attrtype=15,maxValue=5,minValue=2,},
			[13]= {id=13,attrname="魔法恢复",attrtype=16,maxValue=5,minValue=2,},
			[14]= {id=14,attrname="神圣",attrtype=27,maxValue=20,minValue=10,},
		},
}
gdFuMoEnhance = {
	MaxEnhanceCount=10,
	[1]= {
			id=1,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=1,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[2]= {
			id=2,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=2,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[3]= {
			id=3,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=3,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[4]= {
			id=4,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=4,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[5]= {
			id=5,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=5,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[6]= {
			id=6,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=6,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[7]= {
			id=7,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=7,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[8]= {
			id=8,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=8,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[9]= {
			id=9,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=9,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
	[10]= {
			id=10,
			itemCfgID=40149,
			itemCount=1,
			money=1000,
			perfectItemCfgID=40150,
			perfectItemCount=10,
			prop= {
					[5]= {id=5,name="最小物理攻击",maxValue=20,minValue=10,},
					[6]= {id=6,name="最大物理攻击",maxValue=20,minValue=10,},
					[7]= {id=7,name="最小魔法攻击",maxValue=20,minValue=10,},
					[8]= {id=8,name="最大魔法攻击",maxValue=20,minValue=10,},
					[9]= {id=9,name="最小道术攻击",maxValue=20,minValue=10,},
					[10]= {id=10,name="最大道术攻击",maxValue=20,minValue=10,},
					[11]= {id=11,name="最小物理防御",maxValue=20,minValue=10,},
					[12]= {id=12,name="最大物理防御",maxValue=20,minValue=10,},
					[13]= {id=13,name="最小魔法防御",maxValue=20,minValue=10,},
					[14]= {id=14,name="最大魔法防御",maxValue=20,minValue=10,},
					[15]= {id=15,name="生命恢复",maxValue=5,minValue=2,},
					[16]= {id=16,name="魔法恢复",maxValue=5,minValue=2,},
					[22]= {id=22,name="毒物恢复",maxValue=5,minValue=2,},
					[27]= {id=27,name="神圣",maxValue=20,minValue=10,},
				},
		},
}
gdtgtItemMergeType[1] = {--灵石合成
	[1]= {sid=40001,},
	[2]= {sid=40002,},
	[3]= {sid=40003,},
	
	[4]= {sid=41000,},
	[5]= {sid=41001,},
	[6]= {sid=41002,},
}
gdtgtItemMergeType[2] = {--装备合成
    [1]= {sid=60266,},
	----------------------------
	[2]= {sid=20560,},
	[3]= {sid=87410,},
	[4]= {sid=83083,},
	[5]= {sid=80031,},
	[6]= {sid=20559,},
}
gdtgtItemMergeType[3] = {--物品合成
	[1]= {sid=30059,},
	[2]= {sid=5558,},
	
}
gdtgtItemMergeType[4] = {
	[1]= {sid=80001,},
	[2]= {sid=80002,},
	[3]= {sid=80003,},
	[4]= {sid=80004,},
	[5]= {sid=80005,},
	[6]= {sid=80006,},
	[7]= {sid=80007,},
	[8]= {sid=80008,},
	[9]= {sid=80009,},
	[10]= {sid=80010,},
	[11]= {sid=80011,},
	[12]= {sid=80025,},
	[13]= {sid=80026,},
	[14]= {sid=80027,},
	[15]= {sid=80028,},
	[16]= {sid=80029,},
	[17]= {sid=80030,},
}
gdtgtItemMergeType[5] = {
	[1]= {sid=40055,},
	[2]= {sid=40056,},
}
gdtgtItemMergeType[6] = {--技能书改神器合成
	[1]= {sid=86000,},
	[2]= {sid=86001,},
	[3]= {sid=86002,},
	[4]= {sid=86003,},
	[5]= {sid=86004,},
	[6]= {sid=86005,},
	
}
gdtgtItemMergeType[7] = {
	[1]= {sid=10014,},
	[2]= {sid=10015,},
	[3]= {sid=10016,},
	[4]= {sid=10017,},
	[5]= {sid=10018,},
	[6]= {sid=10019,},
	[7]= {sid=10020,},
	[8]= {sid=10021,},
	[9]= {sid=10022,},
	[10]= {sid=10023,},
	[11]= {sid=10024,},
	[12]= {sid=10025,},
	[13]= {sid=10026,},
	[14]= {sid=10027,},
	[15]= {sid=10028,},
	[16]= {sid=10029,},
	[17]= {sid=10030,},
	[18]= {sid=10031,},
	[19]= {sid=10032,},
	[20]= {sid=10033,},
	[21]= {sid=10034,},
	[22]= {sid=10035,},
	[23]= {sid=10036,},
	[24]= {sid=10037,},
	[25]= {sid=10038,},
	[26]= {sid=10039,},
	[27]= {sid=10040,},
	[28]= {sid=10041,},
	[29]= {sid=10042,},
	[30]= {sid=10043,},
	[31]= {sid=10044,},
	[32]= {sid=10045,},
	[33]= {sid=10046,},
	[34]= {sid=10047,},
	[35]= {sid=10048,},
	[36]= {sid=10049,},
	[37]= {sid=10050,},
	[38]= {sid=10051,},
	[39]= {sid=10052,},
	[40]= {sid=10053,},
	[41]= {sid=10054,},
	[42]= {sid=10055,},
	[43]= {sid=10056,},
	[44]= {sid=10057,},
	[45]= {sid=10058,},
	[46]= {sid=10059,},
	[47]= {sid=10060,},
	[48]= {sid=10061,},
	[49]= {sid=10062,},
	[50]= {sid=10063,},
	[51]= {sid=10064,},
	[52]= {sid=10065,},
	[53]= {sid=10066,},
	[54]= {sid=10067,},
	[55]= {sid=10068,},
	[56]= {sid=10069,},
	[57]= {sid=10070,},
	[58]= {sid=10071,},
	[59]= {sid=10072,},
	[60]= {sid=10073,},
	[61]= {sid=10074,},
	[62]= {sid=10075,},
	[63]= {sid=10076,},
	[64]= {sid=10077,},
	[65]= {sid=10078,},
	[66]= {sid=10079,},
	[67]= {sid=10080,},
	[68]= {sid=10081,},
	[69]= {sid=10082,},
	[70]= {sid=10083,},
	[71]= {sid=10084,},
	[72]= {sid=10085,},
	[73]= {sid=10086,},
	[74]= {sid=10087,},
	[75]= {sid=10088,},
	[76]= {sid=10089,},
	[77]= {sid=10090,},
	[78]= {sid=10091,},
	[79]= {sid=10092,},
	[80]= {sid=10093,},
	[81]= {sid=10094,},
	[82]= {sid=10095,},
	[83]= {sid=10096,},
	[84]= {sid=10097,},
	[85]= {sid=10098,},
	[86]= {sid=10099,},
	[87]= {sid=10100,},
	[88]= {sid=10101,},
	[89]= {sid=10102,},
	[90]= {sid=10103,},
	[91]= {sid=10104,},
	[92]= {sid=10105,},
	[93]= {sid=10106,},
	[94]= {sid=10107,},
	[95]= {sid=10108,},
	[96]= {sid=10109,},
	[97]= {sid=10110,},
	[98]= {sid=10111,},
	[99]= {sid=10112,},
	[100]= {sid=10113,},
	[101]= {sid=10114,},
	[102]= {sid=10115,},
	[103]= {sid=10116,},
	[104]= {sid=10117,},
	[105]= {sid=10118,},
	[106]= {sid=10119,},
	[107]= {sid=10120,},
	[108]= {sid=10121,},
	[109]= {sid=10122,},
	[110]= {sid=10123,},
	[111]= {sid=10124,},
	[112]= {sid=10125,},
	[113]= {sid=10126,},
	[114]= {sid=10127,},
	[115]= {sid=10128,},
	[116]= {sid=10129,},
	[117]= {sid=10130,},
	[118]= {sid=10131,},
	[119]= {sid=10132,},
	[120]= {sid=10133,},
	[121]= {sid=10134,},
	[122]= {sid=10135,},
	[123]= {sid=10136,},
	[124]= {sid=10137,},
	[125]= {sid=10138,},
	[126]= {sid=10139,},
	[127]= {sid=10140,},
	[128]= {sid=10141,},
	[129]= {sid=10142,},
	[130]= {sid=10143,},
	[131]= {sid=10144,},
	[132]= {sid=10145,},
	[133]= {sid=10146,},
}
gdsrcItemMergeType[1] = {
	[1]= {sid=40000,},
	[2]= {sid=40001,},
	[3]= {sid=40002,},
}
gdsrcItemMergeType[2] = {
	[1]= {sid=40005,},
}
gdsrcItemMergeType[3] = {
	[1]= {sid=40005,},
	[2]= {sid=40006,},
	[3]= {sid=40077,},
	[4]= {sid=40013,},
	[5]= {sid=30377,},
	[6]= {sid=81151,},
	[7]= {sid=81153,},
}
gdsrcItemMergeType[4] = {
	[1]= {sid=40007,},
	[2]= {sid=80000,},
	[3]= {sid=80001,},
	[4]= {sid=80002,},
	[5]= {sid=80003,},
	[6]= {sid=80004,},
	[7]= {sid=80005,},
	[8]= {sid=80006,},
	[9]= {sid=80007,},
	[10]= {sid=80008,},
	[11]= {sid=80009,},
	[12]= {sid=80010,},
	[13]= {sid=80011,},
	[14]= {sid=80025,},
	[15]= {sid=80026,},
	[16]= {sid=80027,},
}
gdsrcItemMergeType[5] = {
	[1]= {sid=40054,},
	[2]= {sid=40055,},
}
gdsrcItemMergeType[6] = {
	[1]= {sid=30073,},
	[2]= {sid=30074,},
	[3]= {sid=30075,},
	[4]= {sid=30076,},
	[5]= {sid=30078,},
	[6]= {sid=30079,},
	[7]= {sid=30080,},
	[8]= {sid=30081,},
	[9]= {sid=30083,},
	[10]= {sid=30084,},
	[11]= {sid=30085,},
	[12]= {sid=30086,},
}
gdsrcItemMergeType[7] = {
	[1]= {sid=10007,},
	[2]= {sid=10008,},
	[3]= {sid=10009,},
	[4]= {sid=10010,},
	[5]= {sid=10011,},
	[6]= {sid=10012,},
	[7]= {sid=10013,},
	[8]= {sid=10014,},
	[9]= {sid=10015,},
	[10]= {sid=10016,},
	[11]= {sid=10017,},
	[12]= {sid=10018,},
	[13]= {sid=10019,},
	[14]= {sid=10020,},
	[15]= {sid=10021,},
	[16]= {sid=10022,},
	[17]= {sid=10023,},
	[18]= {sid=10024,},
	[19]= {sid=10025,},
	[20]= {sid=10026,},
	[21]= {sid=10027,},
	[22]= {sid=10028,},
	[23]= {sid=10029,},
	[24]= {sid=10030,},
	[25]= {sid=10031,},
	[26]= {sid=10032,},
	[27]= {sid=10033,},
	[28]= {sid=10034,},
	[29]= {sid=10035,},
	[30]= {sid=10036,},
	[31]= {sid=10037,},
	[32]= {sid=10038,},
	[33]= {sid=10039,},
	[34]= {sid=10040,},
	[35]= {sid=10041,},
	[36]= {sid=10042,},
	[37]= {sid=10043,},
	[38]= {sid=10044,},
	[39]= {sid=10045,},
	[40]= {sid=10046,},
	[41]= {sid=10047,},
	[42]= {sid=10048,},
	[43]= {sid=10049,},
	[44]= {sid=10050,},
	[45]= {sid=10051,},
	[46]= {sid=10052,},
	[47]= {sid=10053,},
	[48]= {sid=10054,},
	[49]= {sid=10055,},
	[50]= {sid=10056,},
	[51]= {sid=10057,},
	[52]= {sid=10058,},
	[53]= {sid=10059,},
	[54]= {sid=10060,},
	[55]= {sid=10061,},
	[56]= {sid=10062,},
	[57]= {sid=10063,},
	[58]= {sid=10064,},
	[59]= {sid=10065,},
	[60]= {sid=10066,},
	[61]= {sid=10067,},
	[62]= {sid=10068,},
	[63]= {sid=10069,},
	[64]= {sid=10070,},
	[65]= {sid=10071,},
	[66]= {sid=10072,},
	[67]= {sid=10073,},
	[68]= {sid=10074,},
	[69]= {sid=10075,},
	[70]= {sid=10076,},
	[71]= {sid=10077,},
	[72]= {sid=10078,},
	[73]= {sid=10079,},
	[74]= {sid=10080,},
	[75]= {sid=10081,},
	[76]= {sid=10082,},
	[77]= {sid=10083,},
	[78]= {sid=10084,},
	[79]= {sid=10085,},
	[80]= {sid=10086,},
	[81]= {sid=10087,},
	[82]= {sid=10088,},
	[83]= {sid=10089,},
	[84]= {sid=10090,},
	[85]= {sid=10091,},
	[86]= {sid=10092,},
	[87]= {sid=10093,},
	[88]= {sid=10094,},
	[89]= {sid=10095,},
	[90]= {sid=10096,},
	[91]= {sid=10097,},
	[92]= {sid=10098,},
	[93]= {sid=10099,},
	[94]= {sid=10100,},
	[95]= {sid=10101,},
	[96]= {sid=10102,},
	[97]= {sid=10103,},
	[98]= {sid=10104,},
}
-- 坐骑基础属性
gdHorseBaseStats = {
	MaxLevel=11,
	[1]= {
			AppearanceImage="zb_003",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=150,},
					[2]= {AttrID=10,AttrValue=150,},
					[3]= {AttrID=8,AttrValue=150,},
					[4]= {AttrID=12,AttrValue=100,},
					[5]= {AttrID=14,AttrValue=100,},
					[6]= {AttrID=1,AttrValue=300,},
					[7]= {AttrID=2,AttrValue=300,},
				},
			GeneCfgID=0,
			HeadImage="zh_003",
			HeadPortraitImage="zh_003.png",
			Level=1,
			Name="的卢(1阶）",
			UnlockHorseEquip=1,
			UpLevelExp=100,
		},
	[2]= {
			AppearanceImage="zb_004",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=220,},
					[2]= {AttrID=10,AttrValue=220,},
					[3]= {AttrID=8,AttrValue=220,},
					[4]= {AttrID=12,AttrValue=120,},
					[5]= {AttrID=14,AttrValue=120,},
					[6]= {AttrID=1,AttrValue=320,},
					[7]= {AttrID=2,AttrValue=320,},
				},
			GeneCfgID=10101,
			HeadImage="zh_004",
			HeadPortraitImage="zh_004.png",
			Level=2,
			Name="辛巴(2阶）",
			UnlockHorseEquip=0,
			UpLevelExp=2000,
		},
	[3]= {
			AppearanceImage="zb_015",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=300,},
					[2]= {AttrID=10,AttrValue=300,},
					[3]= {AttrID=8,AttrValue=300,},
					[4]= {AttrID=12,AttrValue=150,},
					[5]= {AttrID=14,AttrValue=150,},
					[6]= {AttrID=1,AttrValue=340,},
					[7]= {AttrID=2,AttrValue=340,},
				},
			GeneCfgID=0,
			HeadImage="zh_015",
			HeadPortraitImage="zh_015.png",
			Level=3,
			Name="花虎(3阶）",
			UnlockHorseEquip=2,
			UpLevelExp=4800,
		},
	[4]= {
			AppearanceImage="zb_005",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=500,},
					[2]= {AttrID=10,AttrValue=500,},
					[3]= {AttrID=8,AttrValue=500,},
					[4]= {AttrID=12,AttrValue=180,},
					[5]= {AttrID=14,AttrValue=180,},
					[6]= {AttrID=1,AttrValue=380,},
					[7]= {AttrID=2,AttrValue=380,},
				},
			GeneCfgID=10102,
			HeadImage="zh_005",
			HeadPortraitImage="zh_005.png",
			Level=4,
			Name="三尾(4阶）",
			UnlockHorseEquip=0,
			UpLevelExp=8000,
		},
	[5]= {
			AppearanceImage="zb_006",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=500,},
					[2]= {AttrID=10,AttrValue=500,},
					[3]= {AttrID=8,AttrValue=500,},
					[4]= {AttrID=12,AttrValue=180,},
					[5]= {AttrID=14,AttrValue=180,},
					[6]= {AttrID=1,AttrValue=380,},
					[7]= {AttrID=2,AttrValue=380,},
				},
			GeneCfgID=10102,
			HeadImage="zh_006",
			HeadPortraitImage="zh_006.png",
			Level=5,
			Name="狂狼(5阶）",
			UnlockHorseEquip=0,
			UpLevelExp=30000,
		},
	[6]= {
			AppearanceImage="zb_007",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=800,},
					[2]= {AttrID=10,AttrValue=800,},
					[3]= {AttrID=8,AttrValue=800,},
					[4]= {AttrID=12,AttrValue=230,},
					[5]= {AttrID=14,AttrValue=230,},
					[6]= {AttrID=1,AttrValue=420,},
					[7]= {AttrID=2,AttrValue=420,},
				},
			GeneCfgID=0,
			HeadImage="zh_007",
			HeadPortraitImage="zh_007.png",
			Level=6,
			Name="战鹿(6阶）",
			UnlockHorseEquip=3,
			UpLevelExp=46800,
		},
	[7]= {
			AppearanceImage="zb_013",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=1200,},
					[2]= {AttrID=10,AttrValue=1200,},
					[3]= {AttrID=8,AttrValue=1200,},
					[4]= {AttrID=12,AttrValue=280,},
					[5]= {AttrID=14,AttrValue=280,},
					[6]= {AttrID=1,AttrValue=460,},
					[7]= {AttrID=2,AttrValue=460,},
				},
			GeneCfgID=10103,
			HeadImage="zh_013",
			HeadPortraitImage="zh_013.png",
			Level=7,
			Name="狂龙(7阶）",
			UnlockHorseEquip=0,
			UpLevelExp=54900,
		},
	[8]= {
			AppearanceImage="zb_014",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=1700,},
					[2]= {AttrID=10,AttrValue=1700,},
					[3]= {AttrID=8,AttrValue=1700,},
					[4]= {AttrID=12,AttrValue=350,},
					[5]= {AttrID=14,AttrValue=350,},
					[6]= {AttrID=1,AttrValue=500,},
					[7]= {AttrID=2,AttrValue=500,},
				},
			GeneCfgID=0,
			HeadImage="zh_014",
			HeadPortraitImage="zh_014.png",
			Level=8,
			Name="花麓(8阶）",
			UnlockHorseEquip=4,
			UpLevelExp=77300,
		},
	[9]= {
			AppearanceImage="zb_016",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=2600,},
					[2]= {AttrID=10,AttrValue=2600,},
					[3]= {AttrID=8,AttrValue=2600,},
					[4]= {AttrID=12,AttrValue=550,},
					[5]= {AttrID=14,AttrValue=550,},
					[6]= {AttrID=1,AttrValue=600,},
					[7]= {AttrID=2,AttrValue=600,},
				},
			GeneCfgID=0,
			HeadImage="zh_016",
			HeadPortraitImage="zh_016.png",
			Level=9,
			Name="凤凰(9阶）",
			UnlockHorseEquip=0,
			UpLevelExp=93700,
		},
	[10]= {
			AppearanceImage="zb_020",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=2850,},
					[2]= {AttrID=10,AttrValue=2850,},
					[3]= {AttrID=8,AttrValue=2850,},
					[4]= {AttrID=12,AttrValue=650,},
					[5]= {AttrID=14,AttrValue=650,},
					[6]= {AttrID=1,AttrValue=650,},
					[7]= {AttrID=2,AttrValue=650,},
				},
			GeneCfgID=10105,
			HeadImage="",
			HeadPortraitImage="zh_020.png",
			Level=10,
			Name="法拉利(10阶）",
			UnlockHorseEquip=0,
			UpLevelExp=200000,
		},
	[11]= {
			AppearanceImage="zb_021",
			AttrAdd= {
					[1]= {AttrID=6,AttrValue=3050,},
					[2]= {AttrID=10,AttrValue=3050,},
					[3]= {AttrID=8,AttrValue=3050,},
					[4]= {AttrID=12,AttrValue=750,},
					[5]= {AttrID=14,AttrValue=750,},
					[6]= {AttrID=1,AttrValue=750,},
					[7]= {AttrID=2,AttrValue=750,},
				},
			GeneCfgID=10105,
			HeadImage="",
			HeadPortraitImage="zh_021.png",
			Level=11,
			Name="骷髅鬼火(11阶）",
			UnlockHorseEquip=0,
			UpLevelExp=300000,
		},
	
}
-- 坐骑培养
gdHorsePeiYang = {
	[1]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=1,Money=1000,},
	[2]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=2,Money=1000,},
	[3]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=3,Money=1000,},
	[4]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=4,Money=1000,},
	[5]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=5,Money=1000,},
	[6]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=6,Money=1000,},
	[7]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=7,Money=1000,},
	[8]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=8,Money=1000,},
	[9]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=9,Money=1000,},
	[10]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=10,Money=1000,},
	[11]= {ItemCfgID=40151,ItemCount=1,ItemExp=1,Level=11,Money=1000,},
	
}
-- 坐骑进阶
gdHorseJinJie = {
	[1]= {ItemCfgID=40152,ItemCount=10,Level=1,Money=1000000,},
	[2]= {ItemCfgID=40152,ItemCount=15,Level=2,Money=1000000,},
	[3]= {ItemCfgID=40152,ItemCount=40,Level=3,Money=1000000,},
	[4]= {ItemCfgID=40152,ItemCount=90,Level=4,Money=1000000,},
	[5]= {ItemCfgID=40152,ItemCount=120,Level=5,Money=1000000,},
	[6]= {ItemCfgID=40152,ItemCount=180,Level=6,Money=1000000,},
	[7]= {ItemCfgID=40152,ItemCount=250,Level=7,Money=1000000,},
	[8]= {ItemCfgID=40152,ItemCount=300,Level=8,Money=1000000,},
	[9]= {ItemCfgID=40152,ItemCount=400,Level=9,Money=1000000,},
	[10]= {ItemCfgID=40152,ItemCount=800,Level=10,Money=1000000,},
	[11]= {ItemCfgID=40152,ItemCount=1000,Level=11,Money=1000000,},
	
}
-- 坐骑装备基础属性
gdHorseEquipBaseStats = {
	[1]= {
			MaxLevel=6,
			[1]= {
					AttrAdd= {
							[1]= {AttrID=1,AttrValue=300,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=0,
					Image="i_horseequip_01.png",
					Level=1,
					UpLevelExp=200,
				},
			[2]= {
					AttrAdd= {
							[1]= {AttrID=1,AttrValue=350,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=1,
					Image="i_horseequip_01.png",
					Level=2,
					UpLevelExp=400,
				},
			[3]= {
					AttrAdd= {
							[1]= {AttrID=1,AttrValue=400,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=2,
					Image="i_horseequip_01.png",
					Level=3,
					UpLevelExp=700,
				},
			[4]= {
					AttrAdd= {
							[1]= {AttrID=1,AttrValue=470,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=3,
					Image="i_horseequip_01.png",
					Level=4,
					UpLevelExp=1100,
				},
			[5]= {
					AttrAdd= {
							[1]= {AttrID=1,AttrValue=550,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=4,
					Image="i_horseequip_01.png",
					Level=5,
					UpLevelExp=1500,
				},
			[6]= {
					AttrAdd= {
							[1]= {AttrID=1,AttrValue=650,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=5,
					Image="i_horseequip_01.png",
					Level=6,
					UpLevelExp=0,
				},
		},
	[2]= {
			MaxLevel=6,
			[1]= {
					AttrAdd= {
							[1]= {AttrID=12,AttrValue=200,},
							[2]= {AttrID=14,AttrValue=200,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=0,
					Image="i_horseequip_02.png",
					Level=1,
					UpLevelExp=200,
				},
			[2]= {
					AttrAdd= {
							[1]= {AttrID=12,AttrValue=250,},
							[2]= {AttrID=14,AttrValue=250,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=1,
					Image="i_horseequip_02.png",
					Level=2,
					UpLevelExp=400,
				},
			[3]= {
					AttrAdd= {
							[1]= {AttrID=12,AttrValue=300,},
							[2]= {AttrID=14,AttrValue=300,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=2,
					Image="i_horseequip_02.png",
					Level=3,
					UpLevelExp=700,
				},
			[4]= {
					AttrAdd= {
							[1]= {AttrID=12,AttrValue=370,},
							[2]= {AttrID=14,AttrValue=370,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=3,
					Image="i_horseequip_02.png",
					Level=4,
					UpLevelExp=1100,
				},
			[5]= {
					AttrAdd= {
							[1]= {AttrID=12,AttrValue=450,},
							[2]= {AttrID=14,AttrValue=450,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=4,
					Image="i_horseequip_02.png",
					Level=5,
					UpLevelExp=1500,
				},
			[6]= {
					AttrAdd= {
							[1]= {AttrID=12,AttrValue=550,},
							[2]= {AttrID=14,AttrValue=550,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=5,
					Image="i_horseequip_02.png",
					Level=6,
					UpLevelExp=0,
				},
		},
	[3]= {
			MaxLevel=6,
			[1]= {
					AttrAdd= {
							[1]= {AttrID=2,AttrValue=300,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=0,
					Image="i_horseequip_03.png",
					Level=1,
					UpLevelExp=200,
				},
			[2]= {
					AttrAdd= {
							[1]= {AttrID=2,AttrValue=350,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=1,
					Image="i_horseequip_03.png",
					Level=2,
					UpLevelExp=400,
				},
			[3]= {
					AttrAdd= {
							[1]= {AttrID=2,AttrValue=400,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=2,
					Image="i_horseequip_03.png",
					Level=3,
					UpLevelExp=700,
				},
			[4]= {
					AttrAdd= {
							[1]= {AttrID=2,AttrValue=470,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=3,
					Image="i_horseequip_03.png",
					Level=4,
					UpLevelExp=1100,
				},
			[5]= {
					AttrAdd= {
							[1]= {AttrID=2,AttrValue=550,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=4,
					Image="i_horseequip_03.png",
					Level=5,
					UpLevelExp=1500,
				},
			[6]= {
					AttrAdd= {
							[1]= {AttrID=2,AttrValue=650,},
							[2]= {AttrID=0,AttrValue=0,},
							[3]= {AttrID=0,AttrValue=0,},
						},
					Color=5,
					Image="i_horseequip_03.png",
					Level=6,
					UpLevelExp=0,
				},
		},
	[4]= {
			MaxLevel=6,
			[1]= {
					AttrAdd= {
							[1]= {AttrID=6,AttrValue=150,},
							[2]= {AttrID=8,AttrValue=150,},
							[3]= {AttrID=10,AttrValue=150,},
						},
					Color=0,
					Image="i_horseequip_04.png",
					Level=1,
					UpLevelExp=200,
				},
			[2]= {
					AttrAdd= {
							[1]= {AttrID=6,AttrValue=450,},
							[2]= {AttrID=8,AttrValue=450,},
							[3]= {AttrID=10,AttrValue=450,},
						},
					Color=1,
					Image="i_horseequip_04.png",
					Level=2,
					UpLevelExp=400,
				},
			[3]= {
					AttrAdd= {
							[1]= {AttrID=6,AttrValue=850,},
							[2]= {AttrID=8,AttrValue=850,},
							[3]= {AttrID=10,AttrValue=850,},
						},
					Color=2,
					Image="i_horseequip_04.png",
					Level=3,
					UpLevelExp=700,
				},
			[4]= {
					AttrAdd= {
							[1]= {AttrID=6,AttrValue=1350,},
							[2]= {AttrID=8,AttrValue=1350,},
							[3]= {AttrID=10,AttrValue=1350,},
						},
					Color=3,
					Image="i_horseequip_04.png",
					Level=4,
					UpLevelExp=1100,
				},
			[5]= {
					AttrAdd= {
							[1]= {AttrID=6,AttrValue=1800,},
							[2]= {AttrID=8,AttrValue=1800,},
							[3]= {AttrID=10,AttrValue=1800,},
						},
					Color=4,
					Image="i_horseequip_04.png",
					Level=5,
					UpLevelExp=1500,
				},
			[6]= {
					AttrAdd= {
							[1]= {AttrID=6,AttrValue=2400,},
							[2]= {AttrID=8,AttrValue=2400,},
							[3]= {AttrID=10,AttrValue=2400,},
						},
					Color=5,
					Image="i_horseequip_04.png",
					Level=6,
					UpLevelExp=0,
				},
		},
}
-- 坐骑装备强化
gdHorseEquipQiangHua = {
	[1]= {ItemCfgID=40153,ItemCount=1,ItemExp=5,Level=1,Money=5000,},
	[2]= {ItemCfgID=40153,ItemCount=1,ItemExp=5,Level=2,Money=5000,},
	[3]= {ItemCfgID=40153,ItemCount=1,ItemExp=5,Level=3,Money=5000,},
	[4]= {ItemCfgID=40153,ItemCount=1,ItemExp=5,Level=4,Money=5000,},
	[5]= {ItemCfgID=40153,ItemCount=1,ItemExp=5,Level=5,Money=5000,},
}
-- 坐骑装备进阶
gdHorseEquipJinJie = {
	[1]= {ItemCfgID=40154,ItemCount=10,Level=1,Money=10000000,},
	[2]= {ItemCfgID=40154,ItemCount=15,Level=2,Money=10000000,},
	[3]= {ItemCfgID=40154,ItemCount=20,Level=3,Money=10000000,},
	[4]= {ItemCfgID=40154,ItemCount=25,Level=4,Money=10000000,},
	[5]= {ItemCfgID=40154,ItemCount=30,Level=5,Money=10000000,},
}
