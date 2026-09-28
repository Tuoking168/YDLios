layout_guild = init_table_safely(layout_guild)
layout_guild = {
	int = {
		bdGongDianBoardCnt = 5,
		bdGongDianLabelCnt = 8,

		bdGuanGongBoardCnt = 4,
		bdGuanGongPilgrimageCnt = 3,

		bdShenShouBoardCnt = 3,
		bdShenShouLeftBianKuangCnt = 3,
		bdShenShouRightBianKuangCnt = 8,
		bdShenShouBianKuangInterval = 85,
		bdShenShouPerLine = 4,
		bdShenShouImgLineCnt = 2,
		bdShenShouImgLineInterval = 47,


		bdTanXianBoardCnt = 3,
		bdTanXianImgCnt = 10,
		bdTanXianNorm = 5,
		bdTanXianIncrease = 70,
		bdTanXianReduces = 217,
		bdTanXianLineCnt = 2,
		bdTanXianLineReduce = 200,
		bdTanXianFontSize = 18,
		bdTanXianTextWidth = 280,



		bdFuLiPerLine = 2,
		bdFuLiCnt = 4,

		bdShangDianPerLine = 3,
		bdShangDianPerPage = 9,

		bdGuangHuanPerLine = 2,
		bdGuangHuanPerPage = 6,
		bdGuangHuanBoardCnt = 2,
	},

	str =  {
	    strText = "分钟",
		vipText = "【VIP】",

		gczNotOpen = "明日20:00至22:00",
		gczTime = "今日20:00至22:00",
		hasApply = "已申请",
		notApply = "未申请",
		guildTanXianText ="每次消耗10点行会贡献获得一次抽奖的机会\n每次刷新有一定几率刷出极品物品",
		FuLiStatusOpenStr = "已开启",
	},

	point = {
		bdGongDianList = {
			x = 317,
			y = 243,
		},

		bdGuanGongNote = {
			x = 570,
			y = 350,
		},

		bdGuanGongPilgrimage = {
			x = 566,
			y = 203,
		},

		bdGuanGongTips = {
			x = 20,
			y = 0,
		},

		bdFuLiList = {
			x = 404,
			y = 178,
		},

		bdShangDianList = {
			x = 400,
			y = 240,
		},

		bdShangDianTips = {
			x = 20,
			y = 0,
		},

		bdShangDianNumberBoard = {
			x = 220,
			y = 80,
		},

		bdGuangHuanList = {
		    x = 400,
			y = 245,
		},

		bdShenShouList = {
		    x = 228,
			y = 75,
		},

		bdShenShouLeftBianKuangPoint = {
		    x = 143,
			y = 75,
		},

		bdShenShouRightBianKuangPoint = {
		    x = 443,
			y = 315,
		},

		bdShenShouNumberPoint = {
		    x = 596,
			y = 152,
		},

		bdShenShouNumbersPoint = {
		    x = 580,
			y = 105,
		},

		bdTanXianList = {
		   x = 590,
		   y = 220,
		},

		bdTanXianGetPoint = {
		   x = 110,
		   y = 305,
		},

		bdTanXianSelectPoint = {
		   x = -149,
		   y = -10,
		},
	},

	size = {
		bdGuangHuanList = {
		    w = 756,
			h = 351,
		},

		bdShenShouList = {
		    w = 237,
			h = 68,
		},

		bdShenShouRightBianKuangInterval = {
		    w = 85,
			h = 70,
		},

		bdTanXianList = {
		    w = 280,
		    h = 190,
		},

		bdTanXianItemScroll = {
		    w = 10,
			h = 188,
		},

		bdGuangHuanItemImage = {
			w = 393,
			h = 117,
		},

		bdGongDianList = {
			w = 608,
			h = 294,
		},

		bdGuanGongNote = {
			w = 332,
			h = 66,
		},

		bdGuanGongNoteBar = {
			w = 6,
			h = 66,
		},

		bdGuanGongPilgrimage = {
			w = 312,
			h = 219,
		},

		bdGuanGongPilgrimageItem = {
			w = 312,
			h = 73,
		},

		bdFuLiList = {
			w = 680,
			h = 290,
		},

		bdFuLiItem = {
			w = 340,
			h = 145,
		},

		bdShangDianList = {
			w = 681,
			h = 276,
		},

		bdShangDianItem = {
			w = 227,
			h = 92,
		},
	},

	label = {
		buildingMoney = {
			text = "行会资金：",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0,
			x = 20,
			y = 40,
		},

		buildingNote = {
			text = "（每周日0:00扣除行会资金作为作为维护费用，费用=主殿等级x5000，行会资金为0即解散行会）",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0,
			x = 20,
			y = 20,
		},

		bdGuangHuanFloatPanelLabel = {
			text = "注：行会光环不可叠加，相同光环会直接覆盖",
			font = "Arial",
			size =  16,
			r = 255,
			g = 0,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 49,
			y = 127,
		},

		bdGuangHuanLabelHurt = {
		    text = "伤害输出提高",
			font = "Arial",
			size =  14,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
            ay = 0.5,
			x = 121,
			y = 96,
		},

		bdGuangHuanLabelTime={
		    text = "持续时间：",
			font = "Arial",
			size =  14,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 121,
			y = 74,
		},

		bdGuangHuanLabelMoney={
		    text = "消耗行会资金：",
			font = "Arial",
			size =  14,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
            ay = 0.5,
			x = 121,
			y = 52,
		},

		bdGuangHuanLabelHorse={
			font = "Arial",
			size =  20,
			r = 255,
			g = 255,
			b = 0,
			x = 63,
			y = 27,
		},

        bdGuangHuanTitle ={
		    text = "行会光环",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 400,
			y = 460,
		},

		bdGuanHuanGuildMoney = {
		    text = "行会资金：",
			font = "Arial",
			size = 14,
			r = 255,
			g = 255,
			b = 255,
			x = 705,
			y = 35,
		},

		bdGongDianTitle = {
			text = "行会主殿",
			font = "Arila",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 400,
			y = 460,
		},

		bdGongDianLabel0 = {
			text = "建筑名称",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 75,
			y = 410,
		},

		bdGongDianLabel1 = {
			text = "建筑等级",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 195,
			y = 410,
		},

		bdGongDianLabel2 = {
			text = "最大等级",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 315,
			y = 410,
		},

		bdGongDianLabel3 = {
			text = "升级消耗",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 435,
			y = 410,
		},

		bdGongDianLabel4 = {
			text = "升级时间",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 555,
			y = 410,
		},

		bdGongDianLabel5 = {
			text = "当前行会资金：",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 90,
			y = 65,
		},

		bdGongDianLabel6 = {
			text = "当前冷却时间：",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 90,
			y = 35,
		},

		bdGongDianLabel7 = {
			text = "行会建筑介绍：\n1.所有其他行会建筑等级不得高于主殿等级；\n2.建筑等级越高，可使用的功能越多；\n3.升级行会建筑需要消耗一定的行会资金和时间；\n4.同一时间只能升级一种建筑。",
			font = "Arial",
			size = 16,
			align = 0,
			r = 255,
			g = 255,
			b = 255,
			w = 154,
			h = 240,
			x = 713,
			y = 140,
		},

		bdGongDianBuildingName = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 60,
			y = 0,
		},

		bdGongDianBuildingLevel = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 180,
			y = 0,
		},

		bdGongDianBuildingMaxLevel = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 300,
			y = 0,
		},

		bdGongDianBuildingUpgradeCost = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 420,
			y = 0,
		},

		bdGongDianBuildingUpgradeTime = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 540,
			y = 0,
		},

		bdGongDianGuildMoney = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0.5,
			x = 145,
			y = 65,
		},

		bdGongDianCDTime = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 0,
			b = 0,
			ax = 0,
			ay = 0.5,
			x = 145,
			y = 35,
		},

		bdTanXianTitle = {
		    text = "行会探险",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 400,
			y = 400,
		},

		bdTanXianExploreLabel = {
		    text = "探险事件",
			font = "Arial",
			size = 22,
			r = 255,
			g = 255,
			b = 255,
			x = 591,
			y = 343,
		},

		bdTanXianCiShuLabel = {
		    text = "剩余次数：",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0.5,
			x = 468,
			y = 100,
		},

		bdTanXianXiaoHaoLabel = {
		    text = "每次消耗贡献：",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0.5,
			x = 468,
			y = 80,
		},

		bdTanXianDangQianLabel = {
		    text = "当前贡献：",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0.5,
			x = 468,
			y = 60
		},

		bdShenShouTitle = {
		    text = "行会神兽",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 400,
			y = 400,
		},

		bdShenShouRecommendLabel = {
			text = "推荐个人战力：",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 425,
			y = 199,
		},

		bdShenShouLevelLabel = {
			text = "等级需求：",
			font = "Arial",
			size = 14,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 425,
			y = 181,
		},

		bdShenShouChallengeLabel = {
			text = "今日剩余个人挑战次数：",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
            ay = 0.5,
			x = 425,
			y = 152,
		},

		bdShenShouNumberLabel = {
		    font = "Arial",
			size = 14,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 597,
			y = 152,
		},

		bdShenShouConsumeLabel = {
			text = "消耗贡献：",
			font = "Arial",
			size = 14,
			r = 255,
			g = 0,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 425,
			y = 134,
		},

		bdShenShouChallengesLabel = {
			text = "行会今日剩余挑战次数：",
			font = "Arial",
			size = 14,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 425,
			y = 105,
		},

		bdShenShouGuildMoneyLabel = {
			text = "消耗行会资金：",
			font = "Arial",
			size = 14,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
            ay = 0.5,
			x = 425,
			y = 87,
		},

		bdShenShouArticleLabel = {
		    text = "物品掉落",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 570,
			y = 363,
		},

		bdShenShouNameLabel = {
		    text = "墨云麒麟一星",
			font = "Arial",
			size = 20,
			r = 0,
			g = 255,
			b = 0,
			x = 227,
			y = 359,
		},

		bdGuanGongTitle = {
			text = "拜关公",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 400,
			y = 400,
		},

		bdGuanGongClothNote = {
			text = "贡献达到5000后将获得全服属性最高的永久时装！",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 0,
			w = 220,
			h = 40,
			x = 226,
			y = 54,
		},

		bdGuanGongPilgrimageNote = {
			text = "行会成员每天累计贡献，每达到一定阶段都将获得奖励！(VIP6级后享有额外的免费上香次数)\n1.200贡献可获得1阶特效关羽时装1天；\n2.500贡献可获得3阶特效关羽时装3天；\n3.1000贡献可获得5阶特效关羽时装5天；\n4.1800贡献可获得7阶特效关羽时装7天；\n5.2600贡献可获得8阶特效关羽时装15天；\n6.5000贡献可获得永久3阶特效关羽时装。",
			font = "Arial",
			size = 14,
			r = 0,
			g = 255,
			b = 0,
			align = 0,
			w = 332,
		},

		bdGuanGongPilgrimageRewardContribution = {
			text = "贡献+",
			font = "Arial",
			size = 14,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0,
			x = 72,
			y = 50,
		},

		bdGuanGongPilgrimageRewardExp = {
			text = "经验：",
			font = "Arial",
			size = 14,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0,
			x = 72,
			y = 30,
		},

		bdGuanGongPilgrimageCost = {
			text = "消耗：",
			font = "Arial",
			size = 14,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0,
			x = 72,
			y = 10,
		},

		bdGuanGongPilgrimagePoint = {
			text = "今日上香累计贡献:",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 0,
			ax = 1,
			ay = 0,
			x = 380,
			y = 360,
		},

		bdGuanGongPilgrimagePointValue = {
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 0,
			ax = 1,
			ay = 0,
			x = 370,
			y = 342,
		},

		bdGuanGongPilgrimageCnt = {
			text = "今日剩余上香次数:",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 0,
			ax = 1,
			ay = 0,
			x = 730,
			y = 35,
		},

		bdFuLiTitle = {
			text = "行会福利",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 400,
			y = 400,
		},

		bdFuLiNote = {
			text = "行会福利可由会长控制开启，开启后本行会成员可消耗一定贡献进行领取\n福利的领取次数有限，请本行会成员尽早领取",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 255,
			w = 520,
			h = 40,
			x = 400,
			y = 353,
		},

		bdFuLiItemName = {
			text = "九朵红玫瑰",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0,
			x = 86,
			y = 106,
		},

		bdFuLiItemState = {
			text = "未开启",
			font = "Arial",
			size = 18,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0,
			x = 86,
			y = 86,
		},

		bdFuLiItemCost0 = {
			text = "领取本福利需消耗25贡献",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0,
			x = 86,
			y = 68,
		},

		bdFuLiItemCost1 = {
			text = "领取本福利需消耗25贡献",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0,
			x = 86,
			y = 68,
		},

		bdFuLiItemCost2 = {
			text = "领取本福利需消耗25贡献",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0,
			x = 86,
			y = 68,
		},

		bdFuLiItemCost3 = {
			text = "领取本福利需消耗50贡献",
			font = "Arial",
			size = 15,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0,
			x = 86,
			y = 68,
		},

		bdFuLiItemNote = {
			text = "每人每天只能领取一次",
			font = "Arial",
			size = 15,
			r = 0,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0,
			x = 86,
			y = 52,
		},

		bdShangDianTitle = {
			text = "行会商店",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 400,
			y = 400,
		},

		bdShangDianItemName = {
			font = "Arial",
			size = 16,
			r = 70,
			g = 255,
			b = 70,
			x = 150,
			y = 60,
		},

		bdShangDianCost = {
			text = "贡献",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 150,
			y = 20,
		},

		bdShangDianLevelNote = {
			text = "需要商店等级达到:",
			font = "Arial",
			size = 12,
			r = 255,
			g = 0,
			b = 0,
			x = 150,
			y = 20,
		},

		bdShangDianPage = {
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			x = 400,
			y = 85,
		},

		bdShangDianState = {
			text = "行会贡献：",
			font = "Arial",
			size = 18,
			r = 255,
			g = 200,
			b = 150,
			ax = 1,
			ay = 0,
			x = 720,
			y = 34,
		},

		bdGuangHuanPage = {
		    font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			x = 400,
			y = 35,
		},

		bdGczOccupyRewardGainer = {
		    text = "获得者: ",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			x = 190,
			y = 50,
			ax = 0,
			ay = 0,
		},
	},

	sprite = {
		combatShiZhuang = {
			path = "bg_hanghui_shachengshizhuang.jpg",
			x = 157,
			y = 302,
		},

		combatHuanWu = {
			path = "bg_hanghui_shachengwuqi.jpg",
			x = 100,
			y = 97,
		},

		buildingTitle = {
			path = "word_hanghuijianzhu.png",
			x = 400,
			y = 460,
		},

		buildingImg = {
			path = "data-a/ui/unplist/bg_hanghuijianzhuditu.jpg",
			x = 400,
			y = 250,
		},

		bdGuangHuanItemImg0 = {
		   path = "bg_hanghui_shixueguanghuan.png",
		},

		bdGuangHuanItemImg1 = {
		   path = "bg_hanghui_shengdunguanghuan.png",
		},

		bdGuangHuanItemImg2 = {
		   path = "bg_hanghui_shenciguanghuan.png",
		},

		bdGuangHuanItemImg3 = {
		   path = "bg_hanghui_yonghengguanghuan.png",
		},

		bdGuangHuanItemImg4 = {
		   path = "bg_hanghui_mifaguanghuan.png",
		},

		bdGuangHuanItemImg5 = {
		   path = "bg_hanghui_xianzuguanghuan.png",
		},

		bdTanXianHengXianImg = {
		   path = "label_getiao3.png",
		   ax = 0,
		   ay = 0.5,
		   x = 438,
		   y = 320,
		},

		bdShenShou = {
		   path = "item_bg_kuang01.png",
		},

		bdShenShouHengXianImg = {
		    path = "label_getiao3.png",
			ax = 0,
			ay = 0.5,
			x = 420,
			y = 167,
		},

		bdGuanGong = {
			path = "bg_hanghuiguangong.png",
			x = 174,
			y = 234,
		},

		bdGuanGongPilgrimageIconBoard = {
			path = "item_bg_kuang01.png",
			ax = 0,
			ay = 1,
			x = 0,
			y = 73,
		},

		bdGuanGongPilgrimageIcon0 = {
			path = "bg_hanghui_shangxiang1.png",
		},

		bdGuanGongPilgrimageIcon1 = {
			path = "bg_hanghui_shangxiang2.png",
		},

		bdGuanGongPilgrimageIcon2 = {
			path = "bg_hanghui_shangxiang3.png",
		},
	},

	menuItemImg = {
	    bdTanXianItem = {
		   norm = "item_bg_kuang01.png",
		   sel = "item_bg_kuang01.png",
		},

		bdShenShouAddBtn = {
		    norm = "btn_n3_jia.png",
			sel = "btn_n3_jia_sel.png",
			x = 700,
			y = 144,
		},

		bdShenShouDoubleLeftBtn = {
			norm = "btn_jiantou3.png",
			sel = "btn_jiantou3_sel.png",
			fx = 1,
			x = 90,
			y = 355,
		},

		bdShenShouDoubleRightBtn = {
		    norm = "btn_jiantou3.png",
			sel = "btn_jiantou3_sel.png",
			x = 364,
			y = 355,
		},

		bdShenShouLeftBtn = {
		    norm = "btn_jiantou4.png",
			sel = "btn_jiantou4_sel.png",
			fx = 1,
			x = 90,
			y = 75,
		},

		bdShenShouRightBtn = {
		    norm = "btn_jiantou4.png",
			sel = "btn_jiantou4_sel.png",
			x = 364,
			y = 75,
		},

		bdGuangHuanItemIcon ={
		   norm = "item_bg_kuang06.png",
		   sel = "item_bg_kuang06.png",
		},

		bdGuanGongItem = {
			norm = "item_bg_kuang01.png",
			sel = "item_bg_kuang01.png",
			x = 346,
			y = 127,
		},

		bdFuLiItem = {
			norm = "item_bg_kuang01.png",
			sel = "item_bg_kuang01.png",
			x = 42,
			y = 94,
		},

		bdShangDianItem = {
			norm = "item_bg_dakuang02.png",
			sel = "item_bg_dakuang02_sel.png",
		},

		bdShangDianItemIcon = {
			norm = "item_bg_kuang06.png",
			sel = "item_bg_kuang06_sel.png",
			x = 42,
			y = 40,
		},
	},

	menuItemLabelImg = {
		building0 = {
			norm = "bg_02.png",
			sel = "bg_02_sel.png",
			text = "行会宫殿",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			w = 178,
			h = 34,
			x = 605,
			y = 380,
		},

		building1 = {
			norm = "bg_02.png",
			sel = "bg_02_sel.png",
			text = "行会关公",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			w = 178,
			h = 34,
			x = 335,
			y = 380,
		},

		building2 = {
			norm = "bg_02.png",
			sel = "bg_02_sel.png",
			text = "行会福利",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			w = 178,
			h = 34,
			x = 458,
			y = 235,
		},

		building3 = {
			norm = "bg_02.png",
			sel = "bg_02_sel.png",
			text = "行会冒险",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			w = 178,
			h = 34,
			x = 108,
			y = 384,
		},

		building4 = {
			norm = "bg_02.png",
			sel = "bg_02_sel.png",
			text = "行会神兽",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			w = 178,
			h = 34,
			x = 210,
			y = 185,
		},

		building5 = {
			norm = "bg_02.png",
			sel = "bg_02_sel.png",
			text = "行会商店",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			w = 178,
			h = 34,
			x = 460,
			y = 100,
		},

		building6 = {
			norm = "bg_02.png",
			sel = "bg_02_sel.png",
			text = "行会光环",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			w = 178,
			h = 34,
			x = 695,
			y = 195,
		},

		bdGongDianUpgrade = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "升级建筑",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 42,
			x = 707,
			y = 370,
		},

		bdGongDianOpen = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "打开建筑",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 42,
			x = 707,
			y = 305,
		},

		bdGongDianFinish = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "结束冷却",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 42,
			x = 550,
			y = 50,
		},

		bdGuanGongPilgrimage = {
			norm = "btn_n1_03_.png",
			sel = "btn_n1_03_sel.png",
			text = "上 香",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 80,
			h = 40,
			x = 270,
			y = 38,
		},

		bdGuanGongVIP = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "购买VIP",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 40,
			x = 455,
			y = 75,
		},

		bdGuanGongAdd = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "增加次数",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 40,
			x = 565,
			y = 75,
		},

		bdGuanGongReward = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "领取奖励",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 40,
			x = 675,
			y = 75,
		},

		bdFuLiOpen = {
			norm = "btn_n1_03_.png",
			sel = "btn_n1_03_sel.png",
			text = "开启福利",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 86,
			h = 32,
			x = 52,
			y = 25,
		},

		bdFuLiReward = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "领取福利",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 90,
			h = 34,
			x = 278,
			y = 25,
		},

		bdGuangHuanOpen = {
		    norm = "btn_n1_03_.png",
			sel = "btn_n1_03_sel.png",
			text = "开    启",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 86,
			h = 32,
			x = 310,
			y = 30,
		},

        bdGuangHuanFirstPage = {
		    norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "首页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 60,
			h = 40,
			x = 200,
			y = 35,
		},

		bdGuangHuanLastPage = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "末页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 60,
			h = 40,
			x = 600,
			y = 35,
		},

		bdGuangHuanPrePage = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "上一页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 80,
			h = 40,
			x = 300,
			y = 35,
		},

		bdGuangHuanNextPage = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "下一页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 80,
			h = 40,
			x = 500,
			y = 35,
		},

		bdTanXianBtn = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "探   险",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 255,
			w = 80,
			h = 40,
			x = 250,
			y = 159,
		},

		bdShenShouChallengeBtn = {
		    norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "个人挑战",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 90,
			h = 40,
			x = 460,
			y = 58,
		},

		bdShenShouChallengesBtn = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "行会挑战",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 90,
			h = 40,
			x = 570,
			y = 58,
		},

		bdShenShouEnterChallengeBtn = {
		    norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "进入挑战",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 90,
			h = 40,
			x = 680,
			y = 58,
		},

		bdShangDianFirstPage = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "首页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 60,
			h = 40,
			x = 200,
			y = 85,
		},

		bdShangDianLastPage = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "末页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 60,
			h = 40,
			x = 600,
			y = 85,
		},

		bdShangDianPrePage = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "上一页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 80,
			h = 40,
			x = 300,
			y = 85,
		},

		bdShangDianNextPage = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "下一页",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 80,
			h = 40,
			x = 500,
			y = 85,
		},

		cancelApply = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "取消申请",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 45,
			x = 647,
			y = 250,
		},

		refuseAllApplication = {
			norm = "btn_n1_03_.png",
			sel = "btn_n1_03_sel.png",
			dis = "btn_n1_03_huise.png",
			text = "拒绝所有",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 45,
			x = 0,
			y = -80,
		},
		
		getGczOccupyReward = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "领取奖励",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 100,
			h = 35,
			x = 250,
			y = 30,
		},
	},

	scaleSprite = {
		listSelFlag = {
			path = "btn_n1_06_sel.png",
		},

		buildingBoard = {
			path = "bg_gongneng_02.png",
			w = 792,
			h = 430,
			x = 400,
			y = 220,
		},

		buildingTopSubBoard = {
			path = "bg_gongneng_04.png",
			w = 782,
			h = 358,
			x = 400,
			y = 250,
		},

		buildingBottomSubBoard = {
			path = "bg_gongneng_04.png",
			w = 782,
			h = 56,
			x = 400,
			y = 39,
		},

		bdGongDianBoard0 = {
			path = "bg_gongneng_02.png",
			w = 792,
			h = 430,
			x = 400,
			y = 220,
		},

		bdGongDianBoard1 = {
			path = "bg_gongneng_04.png",
			w = 616,
			h = 36,
			x = 318,
			y = 411,
		},

		bdGongDianBoard2 = {
			path = "bg_gongneng_04.png",
			w = 616,
			h = 304,
			x = 318,
			y = 242,
		},

		bdGongDianBoard3 = {
			path = "bg_gongneng_04.png",
			w = 616,
			h = 82,
			x = 318,
			y = 52,
		},

		bdGongDianBoard4 = {
			path = "bg_gongneng_04.png",
			w = 166,
			h = 418,
			x = 707,
			y = 220,
		},

		bdGongDianItemSel = {
			path = "btn_n1_06_sel.png",
			w = 608,
			h = 42,
		},

		bdTanXianBoard0 ={
		    path = "bg_gongneng_04.png",
			w = 370,
			h = 330,
			x = 250,
			y = 204,
		},

		bdTanXianBoard1 = {
		    path = "bg_gongneng_04.png",
			w = 290,
			h = 51,
			x = 590,
			y = 343,
		},

		bdTanXianBoard2 = {
			path = "bg_gongneng_04.png",
			w = 290,
			h = 280,
			x = 590,
			y = 179,
		},

		bdShenShouBoard0 = {
		    path = "bg_gongneng_04.png",
			w = 340,
			h = 50,
			x = 227,
			y = 358,
		},

		bdShenShouBoard1 = {
			path = "bg_gongneng_04.png",
			w = 340,
			h = 304,
			x = 227,
			y = 187,
		},

		bdShenShouBoard2 = {
			path = "bg_gongneng_04.png",
			w = 348,
			h = 348,
			x = 570,
			y = 209,
		},


		bdGuanGongBoard0 = {
			path = "bg_gongneng_04.png",
			w = 320,
			h = 306,
			x = 226,
			y = 231,
		},

		bdGuanGongBoard1 = {
			path = "bg_gongneng_04.png",
			w = 320,
			h = 44,
			x = 226,
			y = 57,
		},

		bdGuanGongBoard2 = {
			path = "bg_gongneng_04.png",
			w = 344,
			h = 72,
			x = 564,
			y = 348,
		},

		bdGuanGongBoard3 = {
			path = "bg_gongneng_04.png",
			w = 344,
			h = 280,
			x = 564,
			y = 175,
		},

		bdFuLiTopBoard = {
			path = "bg_gongneng_04.png",
			w = 674,
			h = 52,
			x = 400,
			y = 357,
		},

		bdFuLiItemBoard = {
			path = "bg_gongneng_04.png",
			w = 332,
			h = 136,
		},

		bdShangDianBoard = {
			path = "bg_gongneng_04.png",
			w = 682,
			h = 326,
			x = 400,
			y = 221,
		},

		bdGuangHuanBoard0 ={
		    path = "bg_gongneng_02.png",
			w = 792,
			h = 430,
			x = 400,
			y = 220,
		},


		bdGuangHuanBoard1 = {
			path = "bg_gongneng_04.png",
			w = 778,
			h = 418,
			x = 400,
			y = 220,
		},

		bdGuangHuanItem = {
            path  = "bg_gongneng_04.png",
			w = 362,
			h = 108,
		},

		bdGuangHuanItemBoard = {
		   path = "item_bg_kuang01.png",
		   w = 65,
		   h = 65,
		   x = 63,
		   y = 76,
		},

	},
}
