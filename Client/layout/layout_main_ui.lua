layout_main_ui = init_table_safely(layout_main_ui)
layout_main_ui = {
	comboBox = {
		pkMode = {
			norm = "btn_n4.png",
			sel = "btn_n4_sel.png",
			x = 235,
			y = 583,--全
		},
	},
	float = {
		miniChatDelayTime = 180,
	},
	int = {
		buffOx = 22,
		headPanelNameFontSize = 15,
		portalStonePerLine = 3,
		saiMaChangSkillCnt = 3,
		topActivityMenuOx = 100,
		miniChatRecordMax = 3,

		-- 设置界面是否显示【帐号管理】按钮
		showAccountManagementBtn23 = 1,
		showAccountManagementBtn31 = 1,
		showAccountManagementBtn35 = 1,

		-- 设置界面是否显示【游戏论坛】按钮
		showBBSBtn12 = 1,
	},
	label = {
		bossLife = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 16,
		},
		headPanelHP = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 12,
			text = "0/1",
			x = 140,
			y = 43,
		},
		headPanelLevel = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 14,
			text = "0",
			x = 84,
			y = 15,
		},
		headPanelMP = {
			b = 255,
			font = "Arial",
			g = 255,
			r = 255,
			size = 12,
			text = "0/1",
			x = 135,
			y = 31,
		},

		marketPost = {
			text = "只要998！只要998！无需卖肾抱回家!",
			font = "Arial",
			size = 14,
			align = 0,
			w = 120,
			h = 40,
			r = 100,
			g = 150,
			b = 255,
		},

		renamePanelTitle = {
			text = "名称更改",
			font = "Arial",
			size = 20,
			r = 255,
			g = 255,
			b = 0,
			x = 219,
			y = 285,
		},

		renamePanelNote = {
			text = "请输入新的名称：",
			font = "Arial",
			size = 18,
			r = 255,
			g = 255,
			b = 255,
			x = 95,
			y = 180,
		},

		accountinfo_shuoming = {
			text = "帐号说明",
			font = "Arial",
			size = 22,
			x = 400,
			y = 340,
		},

		accountinfo_dangqian = {
			text = "当前帐号",
			font = "Arial",
			size = 22,
			x = 400,
			y = 220,
		},

		accountinfo_shiwanzh = {
			text = "帐号：",
			font = "Arial",
			size = 18,
			x = 260,
			y = 180,
		},

		accountinfo_shiwanmm = {
			text = "密码：",
			font = "Arial",
			size = 18,
			x = 460,
			y = 180,
		},
	},
	menuItemFont = {
		portalStoneName = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 255,
			size = 20,
			text = "0",
		},
	},
	menuItemImg = {
		dogSkillAttack = {
			norm = "btn_img_daoshi_gongji.png",
			sel = "btn_img_daoshi_gongji_sel.png",
			x = 24,
			y = -200,--140道士宝宝技能ui 
		},
		dogSkillCall = {
			norm = "btn_img_daoshi_zhaohuan.png",
			sel = "btn_img_daoshi_zhaohuan_sel.png",
			x = 136,
			y = -200,--140 
		},
		dogSkillStop = {
			norm = "btn_img_daoshi_tingzhi.png",
			sel = "btn_img_daoshi_tingzhi_sel.png",
			x = 24,
			y = -200,--140
		},
		dogSkillUpdate = {
			norm = "btn_img_daoshi_shengji.png",
			sel = "btn_img_daoshi_shengji_sel.png",
			x = 80,
			y = -200,--140
		},
		headPanelClose = {
			norm = "btn_n3_tuichu_.png",
			sel = "btn_n3_tuichu_sel.png",
			x = 210,
			y = 58,
		},
		leftTips0 = {
			norm = "btn_zhuangtai_renwu02.png",
			sel = "btn_zhuangtai_renwu02_sel.png",
		},
		leftTips1 = {
			norm = "btn_zudui02.png",
			sel = "btn_zudui02_sel.png",
		},
		leftTips2 = {
			norm = "btn_zhuangtai_huodong.png",
			sel = "btn_zhuangtai_huodong_sel.png",
		},
		openChat = {
			norm = "btn_liaotian.png",
			sel = "btn_liaotian_sel.png",
			x = 240,--聊天
			y = 40,
		},
		saiMaChangSkill0 = {
			norm = "btn_img_saima_jiasu.png",
			sel = "btn_img_saima_jiasu_sel.png",
			x = 424,
			y = 115,
		},
		saiMaChangSkill1 = {
			norm = "btn_img_saima_shitarenjiansu.png",
			sel = "btn_img_saima_shitarenjiansu_sel.png",
			x = 480,
			y = 115,
		},
		saiMaChangSkill2 = {
			norm = "btn_img_saima_yinshen.png",
			sel = "btn_img_saima_yinshen_sel.png",
			x = 536,
			y = 115,
		},
		topButton0 = {
			norm = "btn_img_zhujiemian_jingji.png",
			sel = "btn_img_zhujiemian_jingji_sel.png",
			x = 434,
			y = 580,--竞技450
		},
		topButton1 = {
			norm = "btn_img_zhujiemian_huodong.png",
			sel = "btn_img_zhujiemian_huodong_sel.png",
			x = 498,
			y = 580,
		},
		topButton2 = {
			norm = "btn_img_zhujiemian_fuli.png",
			sel = "btn_img_zhujiemian_fuli_sel.png",
			x = 562,
			y = 580,
		},
		topButton3 = {
			norm = "btn_img_zhujiemian_bangzhu.png",
			sel = "btn_img_zhujiemian_bangzhu_sel.png",
			x = 626,
			y = 580,
		},
		topButton4 = {
			norm = "btn_img_zhujiemian_shangcheng.png",
			sel = "btn_img_zhujiemian_shangcheng_sel.png",
			x = 370,
			y = 580,
		},
		topButton5 = {
			norm = "btn_img_zhujiemian_kuafupaihangbang.png",
			sel = "btn_img_zhujiemian_kuafupaihangbang_sel.png",
			x = 690,--626
			y = 580,--382
		},
		contactusTuichu = {
			norm = "btn_n3_tuichu_.png",
			sel = "btn_n3_tuichu_sel.png",
			x = 656,
			y = 403,
		},
	},
	menuItemLabelImg = {
		skillPanelToSetting = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "快捷设置",
			w = 126,
			x = 200,
			y = 0,
		},
		systemSetting0 = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "返回登入",
			w = 136,
			x = 290,
			y = 300,
		},
		systemSetting1 = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "选择角色",
			w = 136,
			x = 290,
			y = 240,
		},
		systemSetting2 = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "系统设置",
			w = 136,
			x = 510,
			y = 300,
		},
		systemSetting3 = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "退出游戏",
			w = 136,
			x = 510,
			y = 240,
		},

		systemSetting4 = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "帐号管理",
			w = 136,
			x = 290,
			y = 180,
		},

		systemSetting5 = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "游戏论坛",
			w = 136,
			x = 290,
			y = 180,
		},

		systemSetting6 = {
			b = 255,
			font = "Arial",
			g = 255,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "用户中心",
			w = 136,
			x = 290,
			y = 180,
		},

		systemSetting7 = {
			b = 0,
			font = "Arial",
			g = 0,
			h = 42,
			norm = "btn_n1_01.png",
			r = 255,
			sel = "btn_n1_01_sel.png",
			size = 20,
			text = "帐号信息！",
			w = 136,
			x = 290,
			y = 180,
		},
	},
	point = {
		bossLifeBar = {
			x = 500,--boss血条ui330-390
			y = 525,
		},
		buffFirst = {
			x = 110,--经验buff图标 100
			y = 540,--399
		},
		headPanel = {
			x = -3,
			y = 620,--480角色头像
		},
		headPanelHPBar = {
			x = 140,
			y = 43,
		},
		headPanelMPBar = {
			x = 135,
			y = 31,
		},
		headPanelName = {
			x = 140,
			y = 59,
		},
		leftMenu = {
			x = 117,
			y = 380,
		},
		leftMenuHide = {
			x = 22,
			y = 380,
		},
		leftMenuPanel = {
			x = -7,--任务界面
			y = 110,--/-10
		},
		leftMenuShow = {
			x = 22,
			y = 380,
		},
		lvlUpNum = {
			x = 370,
			y = 20,
		},
		otherHeadPanel = {
			x = 270,
			y = 397,
		},
		portalStone = {
			x = 418,
			y = 205,
		},

		fireworks = {
			x = 400,
			y = 320,
		},

		miniChatPrivateNote1 = {
			x = 235,
			y = 85,
		},

		miniChatPrivateNote2 = {
			x = 240,
			y = 40,
		},
	},
	scaleSprite = {
		chatBoard = {
			h = 66,
			path = "bg_zhujiemianliaotianxianshidibang.png",
			w = 340,
			x = 380,
			y = 42,
		},
		leftMenuArrowBoardNorm = {
			h = 47,
			path = "btn_n4.png",
			w = 30,
		},
		leftMenuArrowBoardSel = {
			h = 47,
			path = "btn_n4_sel.png",
			w = 30,
		},
		leftMenuBoardNorm = {
			h = 47,
			path = "btn_n4.png",
			w = 54,
		},
		leftMenuBoardSel = {
			h = 47,
			path = "btn_n4_sel.png",
			w = 54,
		},

		marketPosterBoard = {
			path = "bg_baitangxinxi.png",
			w = 130,
			h = 45,
			ax = 0.5,
			ay = 0,
		},
	},
	size = {
		headPic = {
			h = 83,
			w = 78,
		},
		leftMenu = {
			h = 47,
			w = 162,
		},
		lvlUpNum = {
			h = 70,
			w = 34,
		},
		miniChat = {
			h = 66,
			w = 340,
		},
		miniChatScroll = {
			h = 66,
			w = 6,
		},
		portalStone = {
			h = 150,
			w = 510,
		},
		portalStoneItem = {
			h = 40,
			w = 170,
		},
		portalStoneScroll = {
			h = 150,
			w = 6,
		},
	},
	sprite = {
		autoFight = {
			path = "word_zidongzhandouzhong.png",
			x = 600,--自动战斗ui400-155
			y = 100,
		},
		autoMove = {
			path = "word_zidongxunlu.png",
			x = 600,--自动寻路ui
			y = 100,
		},
		bossLifeBar = {
			path = "bg_bossxuetiao.png",
		},
		bossLifeBarBoard = {
			ax = 0,
			ay = 0,
			path = "bg_bossxuetiaodise.png",
			x = 0,
			y = 0,
		},
		combatImmunity = {
			path = "word_zt_mianyi.png",
		},
		combatMiss = {
			path = "word_zt_shanbi.png",
		},
		combatcritical = {
            path = "word_zt_critical.png",--暴击
        },
        combatanticritical= {             
            path = "word_zt_anticritical.png", --防爆
        },
		combatreflect= {             
            path = "word_zt_reflect.png", --反弹
        },
		dangerous = {
			path = "data-a/ui/unplist/bg_beigongji.png",--受击框框
			x = 600,--400
			y = 310,--240
		},
		headPanelBoard = {
			ax = 0,
			ay = 0,
			path = "bg_touxiangkuang2.png",--头像
			x = 0,--左右
			y = 0,--上下
		},
		headPic11 = {
			path = "bg_touxiang_zhanshi_nan.png",
			
		},
		headPic12 = {
			path = "bg_touxiang_zhanshi_nv.png",
		},
		headPic21 = {
			path = "bg_touxiang_fashi_nan.png",
		},
		headPic22 = {
			path = "bg_touxiang_fashi_nv.png",
		},
		headPic31 = {
			path = "bg_touxiang_daoshi_nan.png",
		},
		headPic32 = {
			path = "bg_touxiang_daoshi_nv.png",
		},
		hpBar = {
			path = "bg_xuetiao2.png",
		},
		jobIcon1 = {
			path = "word_zhiye_zhan.png",
			x = 18,
			y = 19,--
		},
		jobIcon2 = {
			path = "word_zhiye_fa.png",
			x = 18,
			y = 19,--
		},
		jobIcon3 = {
			path = "word_zhiye_dao.png",
			x = 18,
			y = 19,--
		},
		leftMenuArrowNorm = {
			path = "btn_jiantou4.png",
		},
		leftMenuArrowSel = {
			path = "btn_jiantou4_sel.png",
		},
		leftMenuNorm0 = {
			path = "word_zhujiemian_renwu.png",
		},
		leftMenuNorm1 = {
			path = "word_zhujiemian_zudui.png",
		},
		leftMenuNorm2 = {
			path = "word_zhujiemian_huodong.png",
		},
		leftMenuSel0 = {
			path = "word_zhujiemian_renwu_sel.png",
		},
		leftMenuSel1 = {
			path = "word_zhujiemian_zudui_sel.png",
		},
		leftMenuSel2 = {
			path = "word_zhujiemian_huodong_sel.png",
		},
		lvlUpBoard = {
			path = "bg_shengji.png",--恭喜你升级ui
			x = 600,--400
			y = 450,--350
		},
		mpBar = {
			path = "bg_lantiao2.png",
		},
		skillArrowDown = {
			fx = 1,
			path = "label_jineng_xia_kehuadong.png",
			x = 1084,--攻击滑动
			y = 73,
		},
		skillArrowUp = {
			path = "label_jineng_xia_kehuadong.png",
			x = 1143,--攻击滑动
			y = 131,
		},

		market = {
			path = "label_tanwei.png",
		},
	},
	str = {
		lvlUpNum = "data-a/ui/common/word_shuzi_shengjishuzi.png",
		pkModeFrame0 = "word_moshi_he.png",
		pkModeFrame1 = "word_moshi_dui.png",
		pkModeFrame2 = "word_moshi_hang.png",
		pkModeFrame3 = "word_moshi_shang.png",
		pkModeFrame4 = "word_moshi_quan.png",
		systemSettingTitle = "系统",
		accountinfo_01 = "1、当前帐号为试用帐号",
		accountinfo_02 = "2、升级为正式帐号后不会因为删除游戏、恢复出场设置等操作导致帐号丢失",
	},
}
