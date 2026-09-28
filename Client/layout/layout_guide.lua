layout_guide = init_table_safely(layout_guide)
layout_guide = {
	int = {
		nextFunctionDetailFontSize = 18,
		maillist = 400,
		PetHeadItemCnt = 3,
	},

	str = {
		newEquipTitle = "装备更新",
		newEquipDesc = "恭喜您获得了更好的装备！",

		newSkillTitle = "技能学习",
		newSkillDesc = "恭喜您获得了新的技能书！",

		nextFunctionTitle = "新功能预告",
		nextFunctionDesc = "即将开放新功能：",

		newGiftTitle = "系统礼包",
		newGiftDesc = "恭喜您获得新的礼包奖励！",

		hollowTitle = "物品找回",
		hollowDesc = "虚空物品找回！",


		trackTitle = "追踪结果",
		trackTitle0 = "追踪人物:",
		trackTitle1 = "所在区域为:",
		trackTitle2 = "坐标轴X:",
		trackTitle3 = "坐标轴Y:",

		mailTitle = "系统邮件",

		newItemUseTitle = "物品使用",
		newItemUseDesc = "恭喜您有新的物品可以使用！",

		chong_wu = "玩家11级后将开启[r宠物系统]\n有了宠物以后你将会没有拾取等一系列烦恼，它将是你最好的帮手！",
		zhuang_bei_qiang_hua = "玩家21级后开启[r装备强化]\n开启装备强化后就可以给你的装备进行强化了！强化等级越高提升战力越高！",
		rong_yv = "玩家27级后将开启[r荣誉系统]\n开启、升级荣誉等级将会获得额外的属性加成，进一步提升战斗力，还等什么？快去升级吧！",
		gong_ji_mo_shi = "玩家40级后将开启[r攻击模式]切换，开启攻击模式切换后将可感受到PK带来的快感！",
		zhuang_bei_jian_ding = "玩家31级后将开启[r装备鉴定]\n配合装备强化将会给你不一样的感受！",
		shi_tu = "玩家34级后开启[r师徒系统]\n34级可以拜师、70级可以收徒，具体详情可以找[y土城师徒管理员]了解。",
		hang_hui = "玩家35级后开启[r行会系统]\n 你还在为孤军奋战感到孤单吗？35级后就可以加入行会了！",
		ban_lv = "玩家36级后开启[r结婚系统]\n 男大当婚、女大当嫁，36级后你就可以和你心仪的他（她）结婚了！",
		zhuang_bei_sheng_ji = "玩家40级将开启[r装备升级]\n等级提升过快，装备属性跟不上来了？装备升级祝你一臂之力！",
		hun_shi = "玩家42级后开启[r魂石系统]\n 42级后你就可以给你心爱的装备镶嵌魂石了！",
		huan_wu_qi_ling = "玩家44级将开启[r装备启灵]\n老幻武看烦了？想用新的又不想花钱重新升阶？没问题！装备启灵祝你一臂之力！",
		he_cheng = "玩家45级后开启[r合成系统]\n 技能等级太低？翅膀等级太低？开启合成系统后你的难题将迎刃而解！",
		shu_xing_zhuan_yi = "玩家47级将开启[r属性转移]\n开启属性转移后你就可以把你装备属性转移给另外一件装备了！",
		zhuan_sheng = "玩家70级将开启[r转生系统]\n开启转生系统你将可以轮回转世！并在转世中变强！轮回次数越多属性加成越高！",
		zhuan_sheng_duan_zao = "玩家1转将开启[r转生锻造]\n转生以后是不是觉得原来的装备属性太低？转生锻造帮你转生装备！",

		pet_reborn_notice = "[r注意：进阶属性和极品属性不会被获得]\n[r被吞噬宠物会消失]",
		pet_has_no = "没有可被吞噬的宠物！",
	},

	point = {
		newItem = {
			x = 400,
			y = 240,
		},

		newItemTips = {
			x = 100,
			y = 310,
		},

		newGift = {
			x = 400,
			y = 240,
		},

		newFunctionIcon = {
			x = 400,
			y = 240,
		},

		nextFunctionDetail = {
			x = 400,
			y = 180,
		},

		maillist = {
			x = 400,
			y = 250,
		},

		tracklabel0 = {
			x = 250,
			y = 300,
		},

		tracklabel1 = {
			x = 250,
			y = 260,
		},

		tracklabel2 = {
			x = 250,
			y = 220,
		},

		tracklabel3 = {
			x = 250,
			y = 180,
		},

		beiXuanPetList = {
			x = 235,--+21
			y = 80,---18
		},
	},

	size = {
		nextFunctionDetail = {
			w = 400,
			h = 90,
		},
		maillist = {
			w = 400,
			h = 180,
		},


		beiXuanPetList = {
			w = 330,
			h = 100,
		},

		beiXuanPetListItem = {
			w = 110,
			h = 100,
		},

		beiXuanPetList = {
			w = 330,
			h = 100,
		},

		beiXuanPetListItem = {
			w = 110,
			h = 100,
		},
	},

	sprite = {
		welcome = {
			path = "data-a/ui/unplist/bg_huanyinglaidao.png",
			x = 400,
			y = 240,
		},

		logo = {
			path = "label_logo2.png",
			x = 630,
			y = 325,
		},

		arrow = {
			path = "bg_yindao_jiantou.png",
			ax = 0.5,
			ay = 0,
			x = 0,
			y = -6,
		},

		newFunction = {
			path = "bg_xingongnengkaiqi.png",
			x = 400,
			y = 350,
		},

		chong_wu = {
			path = "data-a/ui/unplist/bg_xin_chongwu.jpg",
		},

		zhuang_bei_qiang_hua = {
			path = "data-a/ui/unplist/bg_xin_zhuangbeiqianghua.jpg",
		},

		rong_yv = {
			path = "data-a/ui/unplist/bg_xin_rongyv.jpg",
		},

		gong_ji_mo_shi = {
			path = "data-a/ui/unplist/bg_xin_gongjimoshi.jpg",
		},

		zhuang_bei_jian_ding = {
			path = "data-a/ui/unplist/bg_xin_zhuangbeijianding.jpg",
		},

		shi_tu = {
			path = "data-a/ui/unplist/bg_xin_shitu.jpg",
		},

		hang_hui = {
			path = "data-a/ui/unplist/bg_xin_hanghui.jpg",
		},

		ban_lv = {
			path = "data-a/ui/unplist/bg_xin_banlv.jpg",
		},

		zhuang_bei_sheng_ji = {
			path = "data-a/ui/unplist/bg_xin_zhuangbeishengji.jpg",
		},

		hun_shi = {
			path = "data-a/ui/unplist/bg_xin_hunshi.jpg",
		},

		huan_wu_qi_ling = {
			path = "data-a/ui/unplist/bg_xin_zhuangbeiqiling.jpg",
		},

		he_cheng = {
			path = "data-a/ui/unplist/bg_xin_hecheng.jpg",
		},

		shu_xing_zhuan_yi = {
			path = "data-a/ui/unplist/bg_xin_jipinzhuanyi.jpg",
		},

		zhuan_sheng = {
			path = "data-a/ui/unplist/bg_xin_zhuansheng.jpg",
		},

		icon_ji_neng = {
			path = "data-a/ui/unplist/btn_img_gnyd_jineng.png",
		},

		icon_sel_ji_neng = {
			path = "data-a/ui/unplist/btn_img_gnyd_jineng_sel.png",
		},

		icon_zhuang_bei_qiang_hua = {
			path = "data-a/ui/unplist/btn_img_gnyd_qianghua.png",
		},

		icon_sel_zhuang_bei_qiang_hua = {
			path = "data-a/ui/unplist/btn_img_gnyd_qianghua_sel.png",
		},

		icon_rong_yv = {
			path = "data-a/ui/unplist/btn_img_gnyd_rongyu.png",
		},

		icon_sel_rong_yv = {
			path = "data-a/ui/unplist/btn_img_gnyd_rongyu_sel.png",
		},

		icon_gong_ji_mo_shi = {
			path = "data-a/ui/unplist/btn_img_gnyd_gongjimoshi.png",
		},

		icon_sel_gong_ji_mo_shi = {
			path = "data-a/ui/unplist/btn_img_gnyd_gongjimoshi_sel.png",
		},

		icon_zhuang_bei_jian_ding = {
			path = "data-a/ui/unplist/btn_img_gnyd_jianding.png",
		},

		icon_sel_zhuang_bei_jian_ding = {
			path = "data-a/ui/unplist/btn_img_gnyd_jianding_sel.png",
		},

		icon_chong_wu = {
			path = "data-a/ui/unplist/btn_img_gnyd_chongwu.png",
		},

		icon_sel_chong_wu = {
			path = "data-a/ui/unplist/btn_img_gnyd_chongwu_sel.png",
		},

		icon_shi_tu = {
			path = "data-a/ui/unplist/btn_img_gnyd_shitu.png",
		},

		icon_sel_shi_tu = {
			path = "data-a/ui/unplist/btn_img_gnyd_shitu_sel.png",
		},

		icon_hang_hui = {
			path = "data-a/ui/unplist/btn_img_gnyd_hanghui.png",
		},

		icon_sel_hang_hui = {
			path = "data-a/ui/unplist/btn_img_gnyd_hanghui_sel.png",
		},

		icon_ban_lv = {
			path = "data-a/ui/unplist/btn_img_gnyd_qinglv.png",
		},

		icon_sel_ban_lv = {
			path = "data-a/ui/unplist/btn_img_gnyd_qinglv_sel.png",
		},

		icon_zhuang_bei_sheng_ji = {
			path = "data-a/ui/unplist/btn_img_gnyd_zhuangbeishengji.png",
		},

		icon_sel_zhuang_bei_sheng_ji = {
			path = "data-a/ui/unplist/btn_img_gnyd_zhuangbeishengji_sel.png",
		},

		icon_hun_shi = {
			path = "data-a/ui/unplist/btn_img_gnyd_hunshi.png",
		},

		icon_sel_hun_shi = {
			path = "data-a/ui/unplist/btn_img_gnyd_hunshi_sel.png",
		},

		icon_huan_wu_qi_ling = {
			path = "data-a/ui/unplist/btn_img_huanwuqiling.png",
		},

		icon_sel_huan_wu_qi_ling = {
			path = "data-a/ui/unplist/btn_img_huanwuqiling_sel.png",
		},

		icon_he_cheng = {
			path = "data-a/ui/unplist/btn_img_gnyd_hecheng.png",
		},

		icon_sel_he_cheng = {
			path = "data-a/ui/unplist/btn_img_gnyd_hecheng_sel.png",
		},

		icon_shu_xing_zhuan_yi = {
			path = "data-a/ui/unplist/btn_img_gnyd_shuxingzhuanyi.png",
		},

		icon_sel_shu_xing_zhuan_yi = {
			path = "data-a/ui/unplist/btn_img_gnyd_shuxingzhuanyi_sel.png",
		},

		icon_zhuan_sheng = {
			path = "data-a/ui/unplist/btn_img_gnyd_zhuansheng.png",
		},

		icon_sel_zhuan_sheng = {
			path = "data-a/ui/unplist/btn_img_gnyd_zhuansheng_sel.png",
		},
	},

	label = {
		note = {
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
		},
	},

	menuItemImg = {
		welcome = {
			norm = "btn_n3_kaishilvchen.png",
			sel = "btn_n3_kaishilvchen_sel.png",
			x = 600,
			y = 150,
		},
	},

	scaleSprite = {
		arrowBoard = {
			path = "bg_yindao_fangkuang.png",
			w = 65,
			h = 52,
		},

		newFunctionBorder = {
			path = "rim_jinsebiankuang.png",
			w = 312,
			h = 142,
			x = 400,
			y = 303,
		},
	},

	menuItemLabelImg = {
		equipNow = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "一键换装",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 255,
			w = 112,
			h = 40,
			x = 400,
			y = 128,
		},

		leanNow = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "一键学习",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 255,
			w = 112,
			h = 40,
			x = 400,
			y = 128,
		},

		confirm = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "确  定",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 255,
			w = 112,
			h = 40,
			x = 400,
			y = 95,
		},

		get = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "一键领取",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 255,
			w = 112,
			h = 40,
			x = 400,
			y = 128,
		},

		use = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "一键使用",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 255,
			w = 112,
			h = 40,
			x = 400,
			y = 128,
		},

		ok = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			text = "确定",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 255,
			w = 112,
			h = 40,
			x = 400,
			y = 128,
		},

		skip = {
			norm = "btn_n1_01.png",
			sel = "btn_n1_01_sel.png",
			x = 700,
			y = 420,
			w = 90,
			h = 37,
			text = "跳过",
			font = "Arial",
			size = 16,
			r = 255,
			g = 255,
			b = 255,
		},
	},
}
