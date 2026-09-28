layout_notification = init_table_safely(layout_notification)
layout_notification = {
	float = {
		topNoteMovePerTime = 0.01,
	},
	int = {
		topNoteOx = 50,
		topNoteMaxWith = 420,
		topNoteFontSize = 18,
	},
	label = {
		normalNote = {
			b = 255,
			font = "Arial",
			g = 228,
			r = 0,
			size = 18,
		},
		rightCornerNote = {
			ax = 1,
			ay = 0,
			b = 0,
			font = "Arial",
			g = 255,
			r = 0,
			size = 20,
			x = 800,
			y = 0,
		},
		trivialNote = {
			b = 0,
			font = "Arial",
			g = 255,
			r = 48,
			size = 15,
		},
	},
	point = {
		noteAreaLowerRight = {--右下角通知ui经验那些
			x = 700,
			y = 210,--150
		},
		noteAreaMidRight = {
			x = 750,--使用消费通知ui
			y = 260,
		},
		noteAreaTop = {--通知ui上
			x = 600,
			y = 500,
		},
		noteAreaTopAnimL = {
			x = 160,
			y = 405,
		},
		noteAreaTopAnimR = {
			x = 650,
			y = 405,
		},
		offset = {
			x = 0,
			y = -25,
		},
		start = {
			x = 0,
			y = 0,
		},
	},
	size = {
		noteBaseAreaTop = {
			w = 545,
			h = 10,
		},
		noteAreaLowerRight = {
			h = 75,
			w = 200,
		},
		noteAreaMidRight = {
			h = 125,
			w = 300,
		},
	},
	scaleSprite = {
		topNoteBoard = {
			path = "bg_tishi_001.png",
		},
	},
	str = {
		intoPeaceArea = "您已经进入了安全区",
		outPeaceArea = "您已经离开了安全区",
		touchAnim = "data-a/animation/effect/anim_click",
	},
}
