layout_map = init_table_safely(layout_map)
layout_map = {
	float = {
		blinkDT = 0.5,
		myAnimScale = 0.7,
	},
	label = {
		listItemName = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 20,
			x = 89,
			y = 17,
		},
		miniMapCoordinate = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 14,
			x = 1100,--700地图坐标
			y = 596,--466
		},
		miniMapName = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 246,
			size = 14,
			x = 1130,
			y = 530,--地图名字
		},
		portalBigName = {
			ax = 0.5,
			ay = 0,
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 20,
		},
		portalName = {
			ax = 0.5,
			ay = 0,
			font = "Arial",
			size = 14,
		},

		bossName = {
			font = "Arial",
			size = 13,
			r = 255,
			g = 255,
			b = 0,
			ax = 0.5,
			ay = 0,
		},
	},
	menuItemImg = {
		closeMiniMap = {
			ax = 1,
			ay = 1,
			norm = "btn_xiaoditu_shouhuixiaoditu.png",
			sel = "btn_xiaoditu_shouhuixiaoditu_sel.png",
			x = 1200,--800地图标记
			y = 610,--480
		},
		currentMap = {
			norm = "btn_ditu_dangqian_.png",
			sel = "btn_ditu_dangqian_sel.png",
		},
		listItem = {
			norm = "bg_02.png",
			sel = "bg_02.png",
		},
		mapTeleport = {
			norm = "btn_img_feitianxie_.png",
			sel = "btn_img_feitianxie_sel.png",
			x = 50,
			y = 30,
		},
		npcMoveTo = {
			norm = "btn_img_fzoulu.png",
			sel = "btn_img_fzoulu_sel.png",
		},
		npcTeleport = {
			norm = "btn_img_feitianxie_.png",
			sel = "btn_img_feitianxie_sel.png",
		},
		openMiniMap = {
			ax = 1,
			ay = 1,
			norm = "btn_xiaoditu_zhangkaixiaoditu.png",
			sel = "btn_xiaoditu_zhangkaixiaoditu_sel.png",
			x = 1200,--地图标记
			y = 610,
		},
		worldMap = {
			norm = "btn_ditu_shijie_.png",
			sel = "btn_ditu_shijie_sel.png",
		},
	},
	menuItemLabelImg = {
		mapList = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 38,
			norm = "btn_n1_03_.png",
			r = 255,
			sel = "btn_n1_03_.png",
			size = 16,
			text = "地图列表",
			w = 150,
			x = 705,
			y = 405,
		},
		npcList = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 38,
			norm = "btn_n1_03_.png",
			r = 255,
			sel = "btn_n1_03_.png",
			size = 16,
			text = "NPC列表",
			w = 150,
			x = 705,
			y = 405,
		},
	},
	point = {
		list = {
			x = 705,
			y = 195,
		},
		mapShowLeftTop = {
			x = 9,
			y = 430,
		},
		mapSwitch = {
			x = 500,
			y = 30,
		},
		miniMap = {
			x = 1070,--670
			y = 516,--380地图
		},
	},
	scaleSprite = {
		leftBoard = {
			h = 424,
			path = "bg_gongneng_04.png",
			w = 598,
			x = 307,
			y = 220,
		},
		rightBoard = {
			h = 424,
			path = "bg_gongneng_04.png",
			w = 180,
			x = 705,
			y = 220,
		},
	},
	size = {
		list = {
			h = 370,
			w = 176,
		},
		listScrollBar = {
			h = 370,
			w = 6,
		},
		mapShow = {
			h = 378,
			w = 596,
		},
		mapSwitch = {
			h = 42,
			w = 150,
		},
		miniMap = {
			h = 90,
			w = 126,
		},
		npcSubMenu = {
			h = 61,
			w = 160,
		},
	},
	sprite = {
		blueSign = {
			path = "label_xianshi_lanse.png",
		},
		miniMapBorder = {
			ax = 1,
			ay = 1,
			path = "rim_xiaoditukuang.png",
			x = 1200,
			y = 608,--地图框框
		},
		portalSign = {
			path = "bg_chuansongmen.png",
		},
		purpleSign = {
			path = "label_xianshi_zise.png",
		},
		redSign = {
			path = "label_xianshi_guaiwudian.png",
		},
		title = {
			path = "word_ditu.png",
			x = 400,
			y = 460,
		},
		worldMap = {
			path = "data-a/minimap/worldmap.jpg",
		},
		yellowSign = {
			path = "label_xianshi_huang.png",
		},
		bossSign = {
			path = "bg_bosstubiao.png",
		},
	},
	str = {
		mimiMapPathDefault = "data-a/minimap/mini_v103.jpg",
		mimiMapPathHead = "data-a/minimap/mini_",
		portalAnim = "cloth/npc_040",
	},
}
