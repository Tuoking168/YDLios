layout_loading = init_table_safely(layout_loading)
layout_loading = {
	int = {
		tipsNoteFontSize = 16,--进入字体大小
		animStartX = 50,
	},

	str = {
		updateScript = "正在数据更新: ",
		updatePatch = "正在增量更新: ",
		updatePatchFailed = "更新失败，请重新启动游戏。",
		patchNewPackage = "正在整合数据...",
	},

	label = {
		percentNote = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 0,
			size = 18,
			text = "0%",
		},
	},
	point = {
		tipsNote = {
			x = 600,--进入字体ui
			y = 35,
		},
	},
	sprite = {
		bkg = {
			path = "bg_loading.png",--进入背景图
			x = 600,
			y = 310,
		},

		bkgLieYanZhanShen = {
			path = "data-a/ui/unplist/bg_loading_lieyanzhanshen.jpg",
			x = 400,
			y = 240,
		},

		progressBar = {
			path = "bg_jiazaitiao_.png",
		},
		progressBoard = {
			path = "rim_jiazaikuang_.png",
			x = 600,--进入进度条
			y = 60,
		},
	},
}
