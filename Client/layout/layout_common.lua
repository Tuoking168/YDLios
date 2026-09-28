--[[
有效字段：
整数：
int

浮点数：
float

字符串；
str

点：
point{x, y}

尺寸：
size{w, h}

颜色：
color{r, g, b}

矩形：
rect{x, y, w, h}

精灵：
sprite{path, fx, fy, ax, ay, x, y}

图片按钮：
menuItemImg{norm, sel, dis, fx, fy, ax, ay, x, y}

标签按钮：
menuItemFont{text, font, size, align, w, h, r, g, b, ax, ay, x, y}

标签：
label{text, font, size, r, g, b, ax, ay, x, y}

九宫格精灵：
scaleSprite{path, w, h, ax, ay, x, y}

文本框：
editBox{path, lenmax, text, font, size, r, g, b, w, h, ax, ay, x, y}

带有标签的按钮：
menuItemLabelImg{norm, sel, dis, text, font, size, r, g, b, w, h, ax, ay, x, y}

复选框：
checkBox{norm, sel, dis, flag, text, font, size, r, g, b, ax, ay, x, y}

下拉框：
comboBox{norm, sel, flag, font, size, r, g, b, ax, ay, x, y}
--]]
layout_common = init_table_safely(layout_common)
layout_common = {
	color = {
		gold = {
			b = 100,
			g = 200,
			r = 255,
		},
		gray = {
			b = 150,
			g = 150,
			r = 150,
		},
		brown = {
			r = 115,
			g = 67,
			b = 19,
		},
		green = {
			b = 0,
			g = 255,
			r = 0,
		},
		red = {
			b = 0,
			g = 0,
			r = 255,
		},
		white = {
			b = 255,
			g = 255,
			r = 255,
		},
		yellow = {
			b = 0,
			g = 255,
			r = 255,
		},
	},
	comboBox = {
		normal = {
			b = 0,
			flag = "rim_01.png",
			font = "Arial",
			g = 255,
			norm = "btn_n1_06_.png",
			r = 255,
			sel = "btn_n1_06_sel.png",
			size = 16,
		},
	},
	float = {
		dangerousPercent = 1,
		itemIconScale = 0.5,
		skillYeManChongZhuangSpeed = 0.2,
	},
	int = {
		firstRankJobNameY = 100,
		ghostLifeBarOy = 0,
		ghostNameOy = 10,
		itemNameFontSize = 28,
		myRoleOy = -40,
	},
	label = {
		aliveGhostName = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
		},
		itemName = {
			ax = 0.5,
			ay = 0,
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
		},

		guildName = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
			ax = 0.5,
			ay = 1,
		},

		headNames = {
			font = "Arial",
			size = 16,
			r = 242,
			g = 108,
			b = 79,
		},

		normal = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 18,
		},
		noteBigPanelDesc = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 0,
			size = 20,
			x = 400,
			y = 330,
		},
		noteBigPanelTitle = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 255,
			size = 22,
			x = 400,
			y = 403,
		},
		notePanelDesc = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 0,
			size = 20,
			x = 400,
			y = 310,
		},
		notePanelTitle = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 255,
			size = 22,
			x = 400,
			y = 370,
		},
		waitNote = {
			ax = 0.5,
			ay = 0,
			b = 0,
			font = "Arial",
			g = 255,
			r = 0,
			size = 16,
			x = 400,
			y = 5,
		},

		floatTitle = {
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 219,
			y = 285,
		},

		floatContent = {
			font = "Arial",
			size = 18,
			w = 320,
			h = 100,
			align = 0,
			r = 255,
			g = 255,
			b = 255,
			x = 219,
			y = 180,
		},
	},
	menuItemImg = {
		bagGrid = {
			norm = "item_bg_kuang03.png",
			sel = "item_bg_kuang03.png",
		},
		bagGrid1 = {
			norm = "item_bg_kuang01.png",
			sel = "item_bg_kuang01.png",
		},
		close = {
			ax = 1,
			ay = 1,
			norm = "btn_n3_tuichu_.png",
			sel = "btn_n3_tuichu_sel.png",
			x = 800,
			y = 480,
		},
		floatClose = {
			ax = 1,
			ay = 1,
			norm = "btn_n3_tuichu_.png",
			sel = "btn_n3_tuichu_sel.png",
			x = 438,
			y = 310,
		},
		midClose = {
			ax = 1,
			ay = 1,
			norm = "btn_n3_tuichu_.png",
			sel = "btn_n3_tuichu_sel.png",
			x = 754,
			y = 424,
		},
		notePanelClose = {
			norm = "btn_n3_tuichu_.png",
			sel = "btn_n3_tuichu_sel.png",
			x = 596,
			y = 373,
		},
	},
	point = {
		center = {
			x = 400,
			y = 240,
		},
		leftTop = {
			x = 0,
			y = 480,
		},
		rightTop = {
			x = 800,
			y = 480,
		},
	},
	scaleSprite = {
		bkg = {
			h = 480,
			path = "bg_gongneng_03dise.png",
			w = 800,
			x = 400,
			y = 240,
		},
		midBkg = {
			h = 407,
			path = "bg_08.png",
			w = 710,
			x = 400,
			y = 220,
		},
		noteBigPanelBoardIn = {
			h = 256,
			path = "bg_tips_01_2.png",
			w = 546,
			x = 400,
			y = 252,
		},
		scrollbar = {
			h = 9,
			path = "bg_latiao.png",
			w = 9,
		},
		titleBoard = {
			ax = 0,
			ay = 1,
			h = 40,
			path = "bg_gongneng_03.png",
			w = 800,
			x = 0,
			y = 480,
		},


		norm = {
			path = "btn_n1_01.png",
			w = 66,
			h = 30,
		},
		sel = {
			path = "btn_n1_01_sel.png",
			w = 66,
			h = 30,
		},
	},
	size = {
		combatNumber = {
			h = 27,
			w = 24,
		},
		itemCountNumber = {
			h = 11,
			w = 10,
		},
		wordNumber = {
			w = 26,
			h = 19,
		},
		vipNumber = {
			w = 12,
			h = 17,
		},
		portalName = {
			h = 124,
			w = 174,
		},
	},
	sprite = {
		logoJianZhiXuanYuan = {
			path = "data-a/ui/unplist/label_logo_jianzhixuanyuan.png",
			x = 400,
			y = 240,
		},

		logoLieYanZhanShen = {
			path = "data-a/ui/unplist/label_logo_lieyanzhanshen.png",
			x = 400,
			y = 240,
		},

		logoReXueTuLong = {
			path = "data-a/ui/unplist/label_logo_rexuetolong.png",
			x = 400,
			y = 240,
		},
		logoChiYanZhanShen = {
			path = "data-a/ui/unplist/label_logo_chiyanzhanshen.png",
			x = 400,
			y = 370,
		},
		logoLieYanFenTian = {
			path = "data-a/ui/unplist/label_logo_lieyanfentian.png",
			x = 400,
			y = 370,
		},

		logoXueRen = {
			path = "data-a/ui/unplist/label_logo_xueren.png",
			x = 400,
			y = 240,
		},
		logoChuanQiZhanShen = {
			path = "data-a/ui/unplist/label_logo_chuanqizhanshen.png",
			x = 400,
			y = 370,
		},

		logoYingXiongChuanQi = {
			path = "data-a/ui/unplist/label_logo_yingxiongchuanqi.png",
			x = 400,
			y = 370,
		},
		logoShaChengChuanQi = {
			path = "data-a/ui/unplist/label_logo_shachengchuanqi.png",
			x = 400,
			y = 370,
		},
		logoMengHuiShaCheng = {
			path = "data-a/ui/unplist/label_logo_menghuishacheng.png",
			x = 400,
			y = 370,
		},
		logoJingLongZhuan = {
			path = "data-a/ui/unplist/label_logo_jinglongzhuan.png",
			x = 430,--惊龙传400-370
			y = 430,
		},
		logoReXueTianYa = {
			path = "data-a/ui/unplist/label_logo_rexuetianya.png",
			x = 400,
			y = 370,
		},
		logoDaMoDaoGe = {
			path = "data-a/ui/unplist/label_logo_damodaoge.png",
			x = 400,
			y = 240,
		},
		logoBaDao = {
			path = "data-a/ui/unplist/label_logo_badao.png",
			x = 400,
			y = 240,
			},

		floatBoard = {
			ax = 0,
			ay = 0,
			path = "bg_tips_03.png",
			x = 0,
			y = 0,
		},
		midTitleBoard = {
			path = "bg_01.png",
			x = 400,
			y = 400,
		},
		midTitleBoardDecorationL = {
			fx = 1,
			path = "bg_gongneng_huawen.png",
			x = 130,
			y = 397,
		},
		midTitleBoardDecorationR = {
			path = "bg_gongneng_huawen.png",
			x = 670,
			y = 397,
		},
		noteBigPanelBoard = {
			path = "bg_tips_02.png",
			x = 400,
			y = 240,
		},
		notePanelBoard = {
			path = "bg_tips_03.png",
			x = 400,
			y = 240,
		},
		shadow = {
			path = "label_shadow.png",
		},
		titleBoardDecorationL = {
			fx = 1,
			path = "bg_gongneng_huawen.png",
			x = 70,
			y = 460,
		},
		titleBoardDecorationR = {
			path = "bg_gongneng_huawen.png",
			x = 730,
			y = 460,
		},
		titleDecorationL = {
			path = "label_liangdian.png",
			x = 290,
			y = 460,
		},
		titleDecorationR = {
			fx = 1,
			path = "label_liangdian.png",
			x = 510,
			y = 460,
		},
		vipLabel = {
			path = "word_vip.png",
		},
		vip1 = {
			path = "bg_vip_1.png",
		},
		vip2 = {
			path = "bg_vip_2.png",
		},
		vip3 = {
			path = "bg_vip_3.png",
		},
		vip4 = {
			path = "bg_vip_4.png",
		},
		vip5 = {
			path = "bg_vip_5.png",
		},
		vip6 = {
			path = "bg_vip_6.png",
		},
		vip7 = {
			path = "bg_vip_7.png",
		},
		vip8 = {
			path = "bg_vip_8.png",
		},
		vip9 = {
			path = "bg_vip_9.png",
		},
		vip10 = {
			path = "bg_vip_10.png",
		},
		wait = {
			path = "label_wait.png",
			x = 400,
			y = 240,
		},
	},
	str = {
		combatNumber = "data-a/ui/common/word_shuzi_ xueliangshuzi.png",
		itemCountNumber = "data-a/ui/common/word_wupinshuliang.png",
		wordNumber = "data-a/ui/common/word_daxieshuzi1-10.png",
		vipNumber = "data-a/ui/common/word_vip_shuzi.png",
		effectAnimPath = "data-a/animation/effect/",
		monsterDieAnim = "effect/e_128",
		levelupAnim = "effect/e_003",
		reliveAnim = "effect/e_155",
		waitIconFrameName = "label_wait.png",
		itemIconPath = "data-a/icon/",
		defaultIcon = "default.png",
        defaultPic = "data-a/icon/default.png",
		lifeBarBoardFrameName = "bg_06.png",
		lifeBarFrameName = "bg_007.png",

		changeMiningTools = "请更换矿锄进行挖矿。",
		hasChangedMiningTools = "已更换矿锄，可以挖矿了！",
		findNoAim = "没有找到目标",

		dog = "的骷髅",
		dog2 = "的神兽",
		pet = "的宠物",
		market = "的摊位",

		exp = "经验",
		gold = "元宝",
		honor = "荣誉",
		level = "级",
		money = "金币",

		netConnect = "正在尝试连入网络...",
		noMiningTools = "我要去买个矿锄的说。",

		num1 = "一",
		num2 = "二",
		num3 = "三",
		num4 = "四",
		num5 = "五",
		num6 = "六",
		num7 = "七",
		num8 = "八",
		num9 = "九",

		job1 = "战士",
		job2 = "法师",
		job3 = "道士",

		reborn = "转",

		year = "年",
		month = "月",
		date = "日",

		day = "天",
		hour = "时",
		minute = "分",
		second = "秒",
		couple_wife = "[妻子]：",
		couple_husband = "[夫君]：",
		couple_partner = "[伴侣]：",
	},

	menuItemLabelImg = {
		floatConfirm = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "确 定",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 95,
			h = 40,
			x = 104,
			y = 43,
		},

		floatCancel = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			dis = "btn_n1_01_huise.png",
			text = "取 消",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			w = 95,
			h = 40,
			x = 334,
			y = 43,
		},
	},

	editBox = {
		floatInput = {
			path = "bg_liaotiankuang.png",
			font = "Arial",
			size = 14,
			lenmax = 20,
			w = 388,
			h = 40,
			x = 220,
			y = 135,
		},
	},
}
