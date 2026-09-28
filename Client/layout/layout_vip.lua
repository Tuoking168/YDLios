layout_vip = init_table_safely(layout_vip)
layout_vip = {
	int = {
		goldPerYuan = 10,
		rechargeValue0 = 10,
		rechargeValue1 = 50,
		rechargeValue2 = 100,
		rechargeValue3 = 500,
		rechargeValue4 = 1000,
		rechargeValue5 = 2000,
		rechargeValue6 = 3000,
		rechargeValue7 = 5000,
		rechargeValue8 = 10000,
		rechargeValueCnt = 9,
		--如果渠道有特殊要求，在后面加上对应的渠道号
		rechargeValueCnt_6 = 9,--小米
		rechargeValueCnt_28 = 9,--oppo
		rechargeValueCnt_27 = 9,--聚乐htc
		rechargeValueCnt_35 = 9,--木蚂蚁
		rechargeValueCnt_9 = 9,--百度多酷
		rechargeValueCnt_7 = 9,--360
		rechargeValueCnt_11 = 9,--指点传媒
		rechargeValueCnt_4 = 9,--UC
		rechargeValueCnt_8 = 9,--当乐
		rechargeValueCnt_51 = 8,--ios快用
		rechargeValueCnt_9999 = 9,--local
		--end
		rechargeFirstLine = 5,

		vipPanelBoardCnt = 2,
		vipPanelTopLabelCnt = 2,
		vipPanelBottomCnt = 10,
		vipPanelCompareMaxLevel = 10,
		vipPanelFontSize = 18,
		vipPanelTextWidth = 500,

		appstore_rechargeValue0 = 6,
		appstore_rechargeValue1 = 12,
		appstore_rechargeValue2 = 30,
		appstore_rechargeValue3 = 50,
		appstore_rechargeValue4 = 108,
		appstore_rechargeValue5 = 208,
		appstore_rechargeValue6 = 308,
		appstore_rechargeValue7 = 388,
		appstore_rechargeValue8 = 648,
		appstore_rechargeid6 = "YB1",
		appstore_rechargeid12 = "YB2",
		appstore_rechargeid30 = "YB3",
		appstore_rechargeid50 = "YB4",
		appstore_rechargeid108 = "YB5",
		appstore_rechargeid208 = "YB6",
		appstore_rechargeid308 = "YB7",
		appstore_rechargeid388 = "YB8",
		appstore_rechargeid648 = "YB9",
		appstore_rechargeValueCnt = 9,
	},

	float = {
		vipPanelFullPercent = 100.0,
		vipPanelScaleNum = 0.5,
	},

	label = {
	    vipPanelTitleLabel = {
		    text = "会员特权",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 359,
			y = 460,
		},

		vipPanelTopLabel0 = {
		    text = "亲爱的玩家，您现在是尊贵的",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0.5,
			x = 165,
			y = 408,
		},

		vipPanelTopLabel1 = {
		    text = "级会员",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0.5,
			x = 450,
			y = 408,
		},

		vipPanelTopLabel2 = {
		    text = "亲爱的玩家，您现在还不是尊贵的VIP会员",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			ax = 0,
			ay = 0.5,
			x = 165,
			y = 408,
		},

		vipPanelVipService = {
		    text = "累计充值达到50000元宝，即可获得一对一VIP客户服务",
			font = "Arial",
			size = 16,
			r = 219,
			g = 162,
			b = 0,
			ax = 0,
			ay = 0.5,
			x = 165,
			y = 345,
		},

		vipPanelNumLabel = {
		    font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			x = 365,
			y = 371,
		},

		vipPanelWordInLine0 = {
			text = "VIP",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0.5,
			x = 292,
			y = 310,
		},

		vipPanelLevelInLine = {
		    font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0.5,
			x = 322,
			y = 310,
		},

		vipPanelWordInLine1 = {
			text = " 等级特权",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			ax = 0,
			ay = 0.5,
			x = 342,
			y = 310,
		},

        vipPanelPageLabel = {
		    font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			x = 359,
			y = 18,
		},

		rechargeChoose = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
			text = "选择金额：",
			x = 265,
			y = 355,
		},

		exarechargeChoose = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
			text = "其他金额：",
			x = 265,
			y = 245,
		},

		rechargeChoose_91 = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
			text = "选择91豆：",
			x = 265,
			y = 355,
		},

		rechargeGetGold = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
			text = "获得元宝：",
			x = 265,
			y = 145,
		},
		rechargeGetGoldNum = {
			ax = 0,
			ay = 0.5,
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 18,
			x = 360,
			y = 145,
		},
		rechargeType0 = {
			ax = 0,
			ay = 0.5,
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 20,
			text = "自定义充值",
			x = 290,
			y = 395,
		},
		rechargeType1 = {
			ax = 0,
			ay = 0.5,
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 20,
			text = "支付宝充值",
			x = 350,
			y = 400,
		},
		rechargeType2 = {
			ax = 0,
			ay = 0.5,
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 20,
			text = "移动充值卡",
			x = 350,
			y = 400,
		},
		rechargeType3 = {
			ax = 0,
			ay = 0.5,
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 20,
			text = "联通充值卡",
			x = 350,
			y = 400,
		},
		rechargeType4 = {
			ax = 0,
			ay = 0.5,
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 20,
			text = "电信充值卡",
			x = 350,
			y = 400,
		},
		rechargeTypeHead = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 20,
			text = "您已选择",
			x = 248,
			y = 395,
		},
		rechargeValue = {
			ax = 0,
			ay = 0.5,
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
			x = 35,
			y = 17,
		},
	},
	menuItemImg = {
	    vipPanelRechargeBtn = {
		    norm = "btn_n2_vipchongzhi.png",
			sel = "btn_n2_vipchongzhi_sel.png",
			x = 609,
			y = 372,
		},

		recharge = {
			norm = "btn_n2_chongzhi.png",
			sel = "btn_n2_chongzhi_sel.png",
			x = 713,
			y = 65,
		},

		vipPanelBottomLeftBtn = {
		    norm = "btn_jiantou.png",
			sel = "btn_jiantou_sel.png",
			fx=1,
			x = 60,
			y = 148,
		},

		vipPanelBottomRightBtn = {
		    norm = "btn_jiantou.png",
			sel = "btn_jiantou_sel.png",
			x = 655,
			y = 148,
		},
	},
	menuItemLabelImg = {
		recharge0 = {
			b = 0,
			font = "Arial",
			g = 255,
			norm = "bg_02.png",
			r = 246,
			sel = "bg_02_sel.png",
			size = 18,
			text = "自定义充值",
		},
		recharge1 = {
			b = 0,
			font = "Arial",
			g = 255,
			norm = "bg_02.png",
			r = 246,
			sel = "bg_02_sel.png",
			size = 18,
			text = "支付宝充值",
		},
		recharge2 = {
			b = 0,
			font = "Arial",
			g = 255,
			norm = "bg_02.png",
			r = 246,
			sel = "bg_02_sel.png",
			size = 18,
			text = "移动充值卡",
		},
		recharge3 = {
			b = 0,
			font = "Arial",
			g = 255,
			norm = "bg_02.png",
			r = 246,
			sel = "bg_02_sel.png",
			size = 18,
			text = "联通充值卡",
		},
		recharge4 = {
			b = 0,
			font = "Arial",
			g = 255,
			norm = "bg_02.png",
			r = 246,
			sel = "bg_02_sel.png",
			size = 18,
			text = "电信充值卡",
		},
	},
	point = {
	    vipPanelBarPoint = {
			x = 358,
			y = 371,
		},

		vipPanelList = {
		    x = 359,
			y = 163,
		},

		vipPanelTopPoint = {
		    x = 425,
			y = 408,
		},

		vipPanelBottomLeftPoint = {
		    x = 70,
			y = 189,
		},

		vipPanelBottomRightPoint = {
		    x = 648,
			y = 189,
		},

		normalRechargeList = {
			x = 489,
			y = 300,
		},

		rechargeList = {
			x = 93,
			y = 220,
		},
	},

	scaleSprite = {
		vipPanelBoard0 = {
		    path = "bg_gongneng_04.png",
			h = 104,
			w = 706,
			x = 359,
            y = 385,
		},

		vipPanelBoard1 = {
		    path = "bg_gongneng_04.png",
			h = 326,
			w = 706,
			x = 359,
			y = 166,
		},

	    vipPanelLineImg = {
		    path = "bg_01.png",
			h = 35,
			w = 640,
			ax = 0,
			ay = 0.5,
			x = 36,
			y = 310,
		},

		rechargeLeftBoard = {
			h = 430,
			path = "bg_gongneng_04.png",
			w = 172,
			x = 93,
			y = 220,
		},
		rechargeRightBoard = {
			h = 430,
			path = "bg_gongneng_04.png",
			w = 608,
			x = 489,
			y = 220,
		},
		rechargeRightSubBoard = {
			h = 252,
			path = "bg_tips_01_2.png",
			w = 560,
			x = 489,
			y = 250,
		},
	},
	size = {
	    vipPanelList = {
		    h = 255,
			w = 500,
		},

		vipPanelItemScroll = {
		    w = 10,
			h = 254,
		},

		normalRechargeList = {
			h = 72,
			w = 550,
		},
		normalRechargeListItem = {
			h = 36,
			w = 110,
		},
		rechargeList = {
			h = 420,
			w = 170,
		},
	},
	sprite = {
	    vipPanelVipLogo = {
		    path = "bg_viptubiao.png",
			x = 78,
			y = 387,
		},

		vipPanelBarImg = {
		    path = "bg_vipjindutiaoduse.png",
			ax = 0,
			ay = 0.5,
			x = 165,
			y = 370,
		},

		vipPanelChangeBarImg = {
		    path = "bg_vipjindutiao.png",
		},

		vipPanelBottomImg1 = {
		    path = "bg_vip_1.png",
		},

		vipPanelBottomImg2 = {
		    path = "bg_vip_2.png",
		},

		vipPanelBottomImg3 = {
		    path = "bg_vip_3.png",
		},

		vipPanelBottomImg4 = {
			path = "bg_vip_4.png",
		},

		vipPanelBottomImg5 = {
		    path = "bg_vip_5.png",
		},

		vipPanelBottomImg6 = {
		    path = "bg_vip_6.png",
		},

		vipPanelBottomImg7 = {
		    path = "bg_vip_7.png",
		},

		vipPanelBottomImg8 = {
		    path = "bg_vip_8.png",
		},

		vipPanelBottomImg9 = {
		    path = "bg_vip_9.png",
		},

		vipPanelBottomImg10 = {
		    path = "bg_vip_10.png",
		},

		rechargeGold = {
			path = "label_yuanbao.png",
			x = 330,
			y = 145,
		},
		rechargeTitle = {
			path = "word_chongzhi.png",
			x = 400,
			y = 460,
		},
		rechargeValueCheckedBoard = {
			path = "item_bg_kyuan.png",
		},
		rechargeValueCheckedFlag = {
			ax = 0,
			ay = 0.5,
			path = "label_gouxuan_.png",
			x = 0,
			y = 18,
		},
	},
	str = {
		yuan = "元",
		yuan_91 = "豆",
	},
	editBox = {
		extraGold = {
			path = "bg_liaotiankuang.png",
			w = 200,
			h = 50,
			x = 319,
			y = 199,
		},
	},


}
