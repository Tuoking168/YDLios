if not (type(gdLoots)=="table") then
	gdLoots = {}
end

gdLoots = {
	[1]= {
			id=1,
			name="超级药",
			elems= {
					[1]= {name="超级金创药",chance=0.65,max=1,min=1,sid=39003,type=0,},
					[2]= {name="超级魔法药",chance=0.35,max=1,min=1,sid=39007,type=0,},
				},
			type=1,
		},
	[2]= {
			id=2,
			name="新手装",
			elems= {
					[1]= {name="新手布衣(男)",chance=0.33,max=1,min=1,sid=70000,type=0,},
					[2]= {name="新手布衣(女)",chance=0.33,max=1,min=1,sid=70001,type=0,},
					[3]= {name="练习木剑",chance=0.34,max=1,min=1,sid=70002,type=0,},
				},
			type=1,
		},
	[3]= {
			id=3,
			name="10级装备",
			elems= {
					[1]= {name="新兵战甲(男)",chance=0.07,max=1,min=1,sid=70003,type=0,},
					[2]= {name="新兵战甲(女)",chance=0.07,max=1,min=1,sid=70004,type=0,},
					[3]= {name="练习桃木剑",chance=0.06,max=1,min=1,sid=70005,type=0,},
					[4]= {name="阎罗戒指",chance=0.4,max=1,min=1,sid=70026,type=0,},
					[5]= {name="阎罗手套",chance=0.4,max=1,min=1,sid=70027,type=0,},
				},
			type=1,
		},
	[4]= {
			id=4,
			name="20级装备",
			elems= {
					[1]= {name="生死锏",chance=0.04,max=1,min=1,sid=70006,type=0,},
					[2]= {name="神魂项链",chance=0.04,max=1,min=1,sid=70007,type=0,},
					[3]= {name="神魂头盔",chance=0.04,max=1,min=1,sid=70008,type=0,},
					[4]= {name="神魂手镯",chance=0.04,max=1,min=1,sid=70009,type=0,},
					[5]= {name="神魂戒指",chance=0.04,max=1,min=1,sid=70010,type=0,},
					[6]= {name="轻便战甲(男)",chance=0.04,max=1,min=1,sid=70011,type=0,},
					[7]= {name="轻便战甲(女)",chance=0.04,max=1,min=1,sid=70012,type=0,},
					[8]= {name="轻便魔袍(男)",chance=0.04,max=1,min=1,sid=70013,type=0,},
					[9]= {name="轻便魔袍(女)",chance=0.04,max=1,min=1,sid=70014,type=0,},
					[10]= {name="轻便道衣(男)",chance=0.04,max=1,min=1,sid=70015,type=0,},
					[11]= {name="轻便道衣(女)",chance=0.04,max=1,min=1,sid=70016,type=0,},
					[12]= {name="龙魂刺",chance=0.04,max=1,min=1,sid=70017,type=0,},
					[13]= {name="狂战项链",chance=0.04,max=1,min=1,sid=70018,type=0,},
					[14]= {name="狂战头盔",chance=0.04,max=1,min=1,sid=70019,type=0,},
					[15]= {name="狂战手镯",chance=0.04,max=1,min=1,sid=70020,type=0,},
					[16]= {name="狂战戒指",chance=0.04,max=1,min=1,sid=70021,type=0,},
					[17]= {name="附灵头盔",chance=0.04,max=1,min=1,sid=70022,type=0,},
					[18]= {name="附灵手镯",chance=0.04,max=1,min=1,sid=70023,type=0,},
					[19]= {name="附灵戒指",chance=0.04,max=1,min=1,sid=70024,type=0,},
					[20]= {name="白骨杖",chance=0.04,max=1,min=1,sid=70175,type=0,},
					[21]= {name="附灵项链",chance=0.04,max=1,min=1,sid=70176,type=0,},
					[22]= {name="阎罗头盔",chance=0.04,max=1,min=1,sid=70025,type=0,},
					[23]= {name="阎罗宝石",chance=0.04,max=1,min=1,sid=70028,type=0,},
					[24]= {name="阎罗腰带",chance=0.04,max=1,min=1,sid=70029,type=0,},
					[25]= {name="阎罗便鞋",chance=0.04,max=1,min=1,sid=70030,type=0,},
				},
			type=1,
		},
	[5]= {
			id=5,
			name="25级武器",
			elems= {
					[1]= {name="幻影斩龙刀",chance=0.3333,max=1,min=1,sid=70031,type=0,},
					[2]= {name="幻影无极",chance=0.3333,max=1,min=1,sid=70032,type=0,},
					[3]= {name="幻影亡灵杖",chance=0.3334,max=1,min=1,sid=70040,type=0,},
				},
			type=1,
		},
	[6]= {
			id=6,
			name="30级装备",
			elems= {
					[1]= {name="斩龙刀",chance=0.0273,max=1,min=1,sid=70033,type=0,},
					[2]= {name="藤域战甲(男)",chance=0.034,max=1,min=1,sid=70034,type=0,},
					[3]= {name="藤域战甲(女)",chance=0.034,max=1,min=1,sid=70035,type=0,},
					[4]= {name="藤域腰带",chance=0.034,max=1,min=1,sid=70036,type=0,},
					[5]= {name="藤域头盔",chance=0.034,max=1,min=1,sid=70037,type=0,},
					[6]= {name="藤域项链",chance=0.034,max=1,min=1,sid=70038,type=0,},
					[7]= {name="藤域宝石",chance=0.034,max=1,min=1,sid=70039,type=0,},
					[8]= {name="藤域手镯",chance=0.034,max=1,min=1,sid=70191,type=0,},
					[9]= {name="藤域战靴",chance=0.034,max=1,min=1,sid=70192,type=0,},
					[10]= {name="藤域戒指",chance=0.034,max=1,min=1,sid=70193,type=0,},
					[11]= {name="亡灵杖",chance=0.0273,max=1,min=1,sid=70041,type=0,},
					[12]= {name="神域魔袍(男)",chance=0.034,max=1,min=1,sid=70042,type=0,},
					[13]= {name="神域项链",chance=0.034,max=1,min=1,sid=70043,type=0,},
					[14]= {name="神域戒指",chance=0.034,max=1,min=1,sid=70044,type=0,},
					[15]= {name="神域魔袍(女)",chance=0.034,max=1,min=1,sid=70045,type=0,},
					[16]= {name="神域头盔",chance=0.034,max=1,min=1,sid=70046,type=0,},
					[17]= {name="神域腰带",chance=0.034,max=1,min=1,sid=70047,type=0,},
					[18]= {name="神域手镯",chance=0.034,max=1,min=1,sid=70187,type=0,},
					[19]= {name="神域宝石",chance=0.034,max=1,min=1,sid=70188,type=0,},
					[20]= {name="神域法履",chance=0.034,max=1,min=1,sid=70189,type=0,},
					[21]= {name="无极",chance=0.0274,max=1,min=1,sid=70048,type=0,},
					[22]= {name="木域道衣(男)",chance=0.034,max=1,min=1,sid=70049,type=0,},
					[23]= {name="木域道衣(女)",chance=0.034,max=1,min=1,sid=70050,type=0,},
					[24]= {name="木域头盔",chance=0.034,max=1,min=1,sid=70051,type=0,},
					[25]= {name="木域项链",chance=0.034,max=1,min=1,sid=70052,type=0,},
					[26]= {name="木域腰带",chance=0.034,max=1,min=1,sid=70053,type=0,},
					[27]= {name="木域宝石",chance=0.034,max=1,min=1,sid=70054,type=0,},
					[28]= {name="木域手镯",chance=0.034,max=1,min=1,sid=70180,type=0,},
					[29]= {name="木域道鞋",chance=0.034,max=1,min=1,sid=70181,type=0,},
					[30]= {name="木域戒指",chance=0.034,max=1,min=1,sid=70182,type=0,},
				},
			type=1,
		},
	[7]= {
			id=7,
			name="35级散件",
			elems= {
					[1]= {name="龙神杖",chance=0.032,max=1,min=1,sid=70184,type=0,},
					[2]= {name="火神头盔",chance=0.032,max=1,min=1,sid=70056,type=0,},
					[3]= {name="火神腰带",chance=0.032,max=1,min=1,sid=70057,type=0,},
					[4]= {name="火神魔袍(男)",chance=0.0253,max=1,min=1,sid=70058,type=0,},
					[5]= {name="火神魔袍(女)",chance=0.02,max=1,min=1,sid=70059,type=0,},
					[6]= {name="火神手镯",chance=0.032,max=1,min=1,sid=70060,type=0,},
					[7]= {name="火神宝石",chance=0.032,max=1,min=1,sid=70061,type=0,},
					[8]= {name="火神法履",chance=0.032,max=1,min=1,sid=70195,type=0,},
					[9]= {name="火神项链",chance=0.032,max=1,min=1,sid=70196,type=0,},
					[10]= {name="火神戒指",chance=0.032,max=1,min=1,sid=70197,type=0,},
					[11]= {name="镇魔剑",chance=0.032,max=1,min=1,sid=70185,type=0,},
					[12]= {name="海神腰带",chance=0.032,max=1,min=1,sid=70062,type=0,},
					[13]= {name="海神项链",chance=0.032,max=1,min=1,sid=70063,type=0,},
					[14]= {name="海神手镯",chance=0.032,max=1,min=1,sid=70064,type=0,},
					[15]= {name="海神戒指",chance=0.032,max=1,min=1,sid=70065,type=0,},
					[16]= {name="海神道衣(男)",chance=0.0253,max=1,min=1,sid=70066,type=0,},
					[17]= {name="海神道衣(女)",chance=0.02,max=1,min=1,sid=70067,type=0,},
					[18]= {name="海神宝石",chance=0.032,max=1,min=1,sid=70199,type=0,},
					[19]= {name="海神头盔",chance=0.032,max=1,min=1,sid=70200,type=0,},
					[20]= {name="海神道鞋",chance=0.032,max=1,min=1,sid=70201,type=0,},
					[21]= {name="圣魂斩",chance=0.032,max=1,min=1,sid=70055,type=0,},
					[22]= {name="帝王战靴",chance=0.032,max=1,min=1,sid=70069,type=0,},
					[23]= {name="帝王战甲(男)",chance=0.0253,max=1,min=1,sid=70070,type=0,},
					[24]= {name="帝王战甲(女)",chance=0.0201,max=1,min=1,sid=70071,type=0,},
					[25]= {name="帝王头盔",chance=0.032,max=1,min=1,sid=70072,type=0,},
					[26]= {name="帝王护腕",chance=0.032,max=1,min=1,sid=70073,type=0,},
					[27]= {name="帝王戒指",chance=0.032,max=1,min=1,sid=70074,type=0,},
					[28]= {name="帝王项链",chance=0.032,max=1,min=1,sid=70203,type=0,},
					[29]= {name="帝王腰带",chance=0.032,max=1,min=1,sid=70204,type=0,},
					[30]= {name="帝王宝石",chance=0.032,max=1,min=1,sid=70075,type=0,},
					[31]= {name="道士勋章",chance=0.032,max=1,min=1,sid=70136,type=0,},
					[32]= {name="武士勋章",chance=0.032,max=1,min=1,sid=70145,type=0,},
					[33]= {name="法师勋章",chance=0.032,max=1,min=1,sid=70154,type=0,},
				},
			type=1,
		},
	[8]= {
			id=8,
			name="45级散件",
			elems= {
					[1]= {name="星魂项链",chance=0.072,max=1,min=1,sid=70077,type=0,},
					[2]= {name="星魂头盔",chance=0.072,max=1,min=1,sid=70078,type=0,},
					[3]= {name="星魂腰带",chance=0.072,max=1,min=1,sid=70079,type=0,},
					[4]= {name="星魂法履",chance=0.072,max=1,min=1,sid=70080,type=0,},
					[5]= {name="沉渊项链",chance=0.072,max=1,min=1,sid=70081,type=0,},
					[6]= {name="沉渊战靴",chance=0.072,max=1,min=1,sid=70082,type=0,},
					[7]= {name="沉渊腰带",chance=0.072,max=1,min=1,sid=70083,type=0,},
					[8]= {name="沉渊头盔",chance=0.072,max=1,min=1,sid=70084,type=0,},
					[9]= {name="仙人腰带",chance=0.072,max=1,min=1,sid=70087,type=0,},
					[10]= {name="仙人项链",chance=0.072,max=1,min=1,sid=70088,type=0,},
					[11]= {name="仙人道鞋",chance=0.072,max=1,min=1,sid=70089,type=0,},
					[12]= {name="仙人头盔",chance=0.073,max=1,min=1,sid=70090,type=0,},
					[13]= {name="道侠勋章",chance=0.045,max=1,min=1,sid=70137,type=0,},
					[14]= {name="武侠勋章",chance=0.045,max=1,min=1,sid=70146,type=0,},
					[15]= {name="法侠勋章",chance=0.045,max=1,min=1,sid=70155,type=0,},
				},
			type=1,
		},
	[9]= {
			id=9,
			name="50级散件",
			elems= {
					[1]= {name="凝月项链",chance=0.1111,max=1,min=1,sid=70093,type=0,},
					[2]= {name="凝月手镯",chance=0.1111,max=1,min=1,sid=70094,type=0,},
					[3]= {name="凝月宝石",chance=0.1111,max=1,min=1,sid=70095,type=0,},
					[4]= {name="魔月手镯",chance=0.1111,max=1,min=1,sid=70110,type=0,},
					[5]= {name="魔月项链",chance=0.1111,max=1,min=1,sid=70111,type=0,},
					[6]= {name="魔月宝石",chance=0.1111,max=1,min=1,sid=70112,type=0,},
					[7]= {name="雷鸣项链",chance=0.1111,max=1,min=1,sid=70115,type=0,},
					[8]= {name="雷鸣项链",chance=0.1111,max=1,min=1,sid=70115,type=0,},
					[9]= {name="雷鸣项链",chance=0.1112,max=1,min=1,sid=70115,type=0,},
				},
			type=1,
		},
	[10]= {
			id=10,
			name="55级散件",
			elems= {
					[1]= {name="和云头盔",chance=0.0833,max=1,min=1,sid=70096,type=0,},
					[2]= {name="和云腰带",chance=0.0833,max=1,min=1,sid=70097,type=0,},
					[3]= {name="和云戒指",chance=0.0834,max=1,min=1,sid=70098,type=0,},
					[4]= {name="和云法履",chance=0.0834,max=1,min=1,sid=70099,type=0,},
					[5]= {name="血魂头盔",chance=0.0833,max=1,min=1,sid=70120,type=0,},
					[6]= {name="血魂戒指",chance=0.0834,max=1,min=1,sid=70121,type=0,},
					[7]= {name="血魂腰带",chance=0.0833,max=1,min=1,sid=70122,type=0,},
					[8]= {name="血魂战靴",chance=0.0833,max=1,min=1,sid=70123,type=0,},
					[9]= {name="岚风戒指",chance=0.0834,max=1,min=1,sid=70104,type=0,},
					[10]= {name="岚风腰带",chance=0.0833,max=1,min=1,sid=70105,type=0,},
					[11]= {name="岚风头盔",chance=0.0833,max=1,min=1,sid=70106,type=0,},
					[12]= {name="岚风道鞋",chance=0.0833,max=1,min=1,sid=70107,type=0,},
				},
			type=1,
		},
	[11]= {
			id=11,
			name="40级勋章",
			elems= {
					[1]= {name="道宗勋章",chance=0.3334,max=1,min=1,sid=70138,type=0,},
					[2]= {name="武宗勋章",chance=0.3333,max=1,min=1,sid=70147,type=0,},
					[3]= {name="法宗勋章",chance=0.3333,max=1,min=1,sid=70156,type=0,},
				},
			type=1,
		},
	[12]= {
			id=12,
			name="45级勋章",
			elems= {
					[1]= {name="道圣勋章",chance=0.3334,max=1,min=1,sid=70139,type=0,},
					[2]= {name="武圣勋章",chance=0.3333,max=1,min=1,sid=70148,type=0,},
					[3]= {name="法圣勋章",chance=0.3333,max=1,min=1,sid=70157,type=0,},
				},
			type=1,
		},
	[13]= {
			id=13,
			name="50级勋章",
			elems= {
					[1]= {name="道尊勋章",chance=0.3334,max=1,min=1,sid=70140,type=0,},
					[2]= {name="武尊勋章",chance=0.3333,max=1,min=1,sid=70149,type=0,},
					[3]= {name="法尊勋章",chance=0.3333,max=1,min=1,sid=70158,type=0,},
				},
			type=1,
		},
	[14]= {
			id=14,
			name="55级勋章",
			elems= {
					[1]= {name="道皇勋章",chance=0.3334,max=1,min=1,sid=70141,type=0,},
					[2]= {name="武皇勋章",chance=0.3333,max=1,min=1,sid=70150,type=0,},
					[3]= {name="法皇勋章",chance=0.3333,max=1,min=1,sid=70159,type=0,},
				},
			type=1,
		},
	[15]= {
			id=15,
			name="60级勋章",
			elems= {
					[1]= {name="道神勋章",chance=0.3334,max=1,min=1,sid=70142,type=0,},
					[2]= {name="武神勋章",chance=0.3333,max=1,min=1,sid=70151,type=0,},
					[3]= {name="法神勋章",chance=0.3333,max=1,min=1,sid=70160,type=0,},
				},
			type=1,
		},
	[16]= {
			id=16,
			name="70级勋章",
			elems= {
					[1]= {name="霸王勋章*道",chance=0.3334,max=1,min=1,sid=70143,type=0,},
					[2]= {name="霸王勋章*武",chance=0.3333,max=1,min=1,sid=70152,type=0,},
					[3]= {name="霸王勋章*法",chance=0.3333,max=1,min=1,sid=70161,type=0,},
				},
			type=1,
		},
	[17]= {
			id=17,
			name="40级套装",
			elems= {
					[1]= {name="朝夕百花",chance=0.02,max=1,min=1,sid=60000,type=0,},
					[2]= {name="八卦錾金头盔",chance=0.0333,max=1,min=1,sid=60001,type=0,},
					[3]= {name="八卦錾金道衣(男)",chance=0.0164,max=1,min=1,sid=60002,type=0,},
					[4]= {name="八卦錾金道衣(女)",chance=0.0164,max=1,min=1,sid=60003,type=0,},
					[5]= {name="八卦錾金项链",chance=0.0333,max=1,min=1,sid=60004,type=0,},
					[6]= {name="八卦錾金手镯",chance=0.0571,max=1,min=1,sid=60005,type=0,},
					[7]= {name="八卦錾金宝石",chance=0.0333,max=1,min=1,sid=60006,type=0,},
					[8]= {name="八卦錾金道鞋",chance=0.0333,max=1,min=1,sid=60007,type=0,},
					[9]= {name="八卦錾金腰带",chance=0.0333,max=1,min=1,sid=60008,type=0,},
					[10]= {name="八卦錾金戒指",chance=0.0569,max=1,min=1,sid=60202,type=0,},
					[11]= {name="降魔引魂",chance=0.02,max=1,min=1,sid=60060,type=0,},
					[12]= {name="星瀚幽路头盔",chance=0.0333,max=1,min=1,sid=60061,type=0,},
					[13]= {name="星瀚幽路战甲(男)",chance=0.0164,max=1,min=1,sid=60062,type=0,},
					[14]= {name="星瀚幽路战甲(女)",chance=0.0164,max=1,min=1,sid=60063,type=0,},
					[15]= {name="星瀚幽路项链",chance=0.0333,max=1,min=1,sid=60064,type=0,},
					[16]= {name="星瀚幽路护腕",chance=0.0571,max=1,min=1,sid=60065,type=0,},
					[17]= {name="星瀚幽路宝石",chance=0.0333,max=1,min=1,sid=60066,type=0,},
					[18]= {name="星瀚幽路战靴",chance=0.0333,max=1,min=1,sid=60067,type=0,},
					[19]= {name="星瀚幽路腰带",chance=0.0333,max=1,min=1,sid=60068,type=0,},
					[20]= {name="星瀚幽路戒指",chance=0.0569,max=1,min=1,sid=60209,type=0,},
					[21]= {name="混元蚀日",chance=0.0201,max=1,min=1,sid=60120,type=0,},
					[22]= {name="碎寂震天头盔",chance=0.0333,max=1,min=1,sid=60121,type=0,},
					[23]= {name="碎寂震天魔袍(男)",chance=0.0164,max=1,min=1,sid=60122,type=0,},
					[24]= {name="碎寂震天魔袍(女)",chance=0.0164,max=1,min=1,sid=60123,type=0,},
					[25]= {name="碎寂震天项链",chance=0.0333,max=1,min=1,sid=60124,type=0,},
					[26]= {name="碎寂震天手镯",chance=0.0571,max=1,min=1,sid=60125,type=0,},
					[27]= {name="碎寂震天宝石",chance=0.0333,max=1,min=1,sid=60126,type=0,},
					[28]= {name="碎寂震天法履",chance=0.0333,max=1,min=1,sid=60127,type=0,},
					[29]= {name="碎寂震天腰带",chance=0.0333,max=1,min=1,sid=60128,type=0,},
					[30]= {name="碎寂震天戒指",chance=0.0569,max=1,min=1,sid=60216,type=0,},
				},
			type=1,
		},
	[18]= {
			id=18,
			name="45级套装",
			elems= {
					[1]= {name="游龙戏凤",chance=0.02,max=1,min=1,sid=60010,type=0,},
					[2]= {name="光华若木头盔",chance=0.0333,max=1,min=1,sid=60011,type=0,},
					[3]= {name="光华若木道衣(男)",chance=0.0164,max=1,min=1,sid=60012,type=0,},
					[4]= {name="光华若木道衣(女)",chance=0.0164,max=1,min=1,sid=60013,type=0,},
					[5]= {name="光华若木项链",chance=0.0333,max=1,min=1,sid=60014,type=0,},
					[6]= {name="光华若木手镯",chance=0.0571,max=1,min=1,sid=60015,type=0,},
					[7]= {name="光华若木宝石",chance=0.0333,max=1,min=1,sid=60016,type=0,},
					[8]= {name="光华若木道鞋",chance=0.0333,max=1,min=1,sid=60017,type=0,},
					[9]= {name="光华若木腰带",chance=0.0333,max=1,min=1,sid=60018,type=0,},
					[10]= {name="光华若木戒指",chance=0.0569,max=1,min=1,sid=60203,type=0,},
					[11]= {name="晃金摘星",chance=0.02,max=1,min=1,sid=60070,type=0,},
					[12]= {name="离情霜月头盔",chance=0.0333,max=1,min=1,sid=60071,type=0,},
					[13]= {name="离情霜月战甲(男)",chance=0.0164,max=1,min=1,sid=60072,type=0,},
					[14]= {name="离情霜月战甲(女)",chance=0.0164,max=1,min=1,sid=60073,type=0,},
					[15]= {name="离情霜月项链",chance=0.0333,max=1,min=1,sid=60074,type=0,},
					[16]= {name="离情霜月手镯",chance=0.0571,max=1,min=1,sid=60075,type=0,},
					[17]= {name="离情霜月宝石",chance=0.0333,max=1,min=1,sid=60076,type=0,},
					[18]= {name="离情霜月战靴",chance=0.0333,max=1,min=1,sid=60077,type=0,},
					[19]= {name="离情霜月腰带",chance=0.0333,max=1,min=1,sid=60078,type=0,},
					[20]= {name="离情霜月戒指",chance=0.0569,max=1,min=1,sid=60210,type=0,},
					[21]= {name="飞星舞雪",chance=0.0201,max=1,min=1,sid=60130,type=0,},
					[22]= {name="夜灵啸日头盔",chance=0.0333,max=1,min=1,sid=60131,type=0,},
					[23]= {name="夜灵啸日魔袍(男)",chance=0.0164,max=1,min=1,sid=60132,type=0,},
					[24]= {name="夜灵啸日魔袍(女)",chance=0.0164,max=1,min=1,sid=60133,type=0,},
					[25]= {name="夜灵啸日项链",chance=0.0333,max=1,min=1,sid=60134,type=0,},
					[26]= {name="夜灵啸日手镯",chance=0.0571,max=1,min=1,sid=60135,type=0,},
					[27]= {name="夜灵啸日宝石",chance=0.0333,max=1,min=1,sid=60136,type=0,},
					[28]= {name="夜灵啸日法履",chance=0.0333,max=1,min=1,sid=60137,type=0,},
					[29]= {name="夜灵啸日戒指",chance=0.0569,max=1,min=1,sid=60217,type=0,},
					[30]= {name="夜灵啸日腰带",chance=0.0333,max=1,min=1,sid=60138,type=0,},
				},
			type=1,
		},
	[19]= {
			id=19,
			name="50级套装武器",
			elems= {
					[1]= {name="无极牧歌",chance=0.3333,max=1,min=1,sid=60020,type=0,},
					[2]= {name="紫电噬日",chance=0.3333,max=1,min=1,sid=60080,type=0,},
					[3]= {name="冰海潮生",chance=0.3334,max=1,min=1,sid=60140,type=0,},
				},
			type=1,
		},
	[20]= {
			id=20,
			name="50级套装零件",
			elems= {
					[1]= {name="九霄残月头盔",chance=0.0417,max=1,min=1,sid=60021,type=0,},
					[2]= {name="九霄残月道衣(男)",chance=0.0067,max=1,min=1,sid=60022,type=0,},
					[3]= {name="九霄残月道衣(女)",chance=0.0067,max=1,min=1,sid=60023,type=0,},
					[4]= {name="九霄残月项链",chance=0.0417,max=1,min=1,sid=60024,type=0,},
					[5]= {name="九霄残月手镯",chance=0.0557,max=1,min=1,sid=60025,type=0,},
					[6]= {name="九霄残月宝石",chance=0.0417,max=1,min=1,sid=60026,type=0,},
					[7]= {name="九霄残月道鞋",chance=0.0417,max=1,min=1,sid=60027,type=0,},
					[8]= {name="九霄残月腰带",chance=0.0417,max=1,min=1,sid=60028,type=0,},
					[9]= {name="九霄残月戒指",chance=0.0557,max=1,min=1,sid=60204,type=0,},
					[10]= {name="浮犀焰阳头盔",chance=0.0417,max=1,min=1,sid=60081,type=0,},
					[11]= {name="浮犀焰阳战甲(男)",chance=0.0067,max=1,min=1,sid=60082,type=0,},
					[12]= {name="浮犀焰阳战甲(女)",chance=0.0067,max=1,min=1,sid=60083,type=0,},
					[13]= {name="浮犀焰阳项链",chance=0.0417,max=1,min=1,sid=60084,type=0,},
					[14]= {name="浮犀焰阳手镯",chance=0.0557,max=1,min=1,sid=60085,type=0,},
					[15]= {name="浮犀焰阳宝石",chance=0.0417,max=1,min=1,sid=60086,type=0,},
					[16]= {name="浮犀焰阳战靴",chance=0.0417,max=1,min=1,sid=60087,type=0,},
					[17]= {name="浮犀焰阳腰带",chance=0.0417,max=1,min=1,sid=60088,type=0,},
					[18]= {name="浮犀焰阳戒指",chance=0.0557,max=1,min=1,sid=60211,type=0,},
					[19]= {name="雪蛊霜寒头盔",chance=0.0417,max=1,min=1,sid=60141,type=0,},
					[20]= {name="雪蛊霜寒魔袍(男)",chance=0.0067,max=1,min=1,sid=60142,type=0,},
					[21]= {name="雪蛊霜寒魔袍(女)",chance=0.0067,max=1,min=1,sid=60143,type=0,},
					[22]= {name="雪蛊霜寒项链",chance=0.0417,max=1,min=1,sid=60144,type=0,},
					[23]= {name="雪蛊霜寒手镯",chance=0.0557,max=1,min=1,sid=60145,type=0,},
					[24]= {name="雪蛊霜寒宝石",chance=0.0417,max=1,min=1,sid=60146,type=0,},
					[25]= {name="雪蛊霜寒魔鞋",chance=0.0417,max=1,min=1,sid=60147,type=0,},
					[26]= {name="雪蛊霜寒戒指",chance=0.0557,max=1,min=1,sid=60218,type=0,},
					[27]= {name="雪蛊霜寒腰带",chance=0.0417,max=1,min=1,sid=60148,type=0,},
				},
			type=1,
		},
	[21]= {
			id=21,
			name="55级套装武器",
			elems= {
					[1]= {name="阴阳鸣鸿",chance=0.3333,max=1,min=1,sid=60030,type=0,},
					[2]= {name="盘龙惊鸿",chance=0.3333,max=1,min=1,sid=60090,type=0,},
					[3]= {name="苍雷万里",chance=0.3334,max=1,min=1,sid=60150,type=0,},
				},
			type=1,
		},
	[22]= {
			id=22,
			name="55级套装零件",
			elems= {
					[1]= {name="冥火薄天头盔",chance=0.0417,max=1,min=1,sid=60031,type=0,},
					[2]= {name="冥火薄天道袍(男)",chance=0.0067,max=1,min=1,sid=60032,type=0,},
					[3]= {name="冥火薄天道袍(女)",chance=0.0067,max=1,min=1,sid=60033,type=0,},
					[4]= {name="冥火薄天项链",chance=0.0417,max=1,min=1,sid=60034,type=0,},
					[5]= {name="冥火薄天手镯",chance=0.0557,max=1,min=1,sid=60035,type=0,},
					[6]= {name="冥火薄天宝石",chance=0.0417,max=1,min=1,sid=60036,type=0,},
					[7]= {name="冥火薄天道鞋",chance=0.0417,max=1,min=1,sid=60037,type=0,},
					[8]= {name="冥火薄天腰带",chance=0.0417,max=1,min=1,sid=60038,type=0,},
					[9]= {name="冥火薄天戒指",chance=0.0557,max=1,min=1,sid=60205,type=0,},
					[10]= {name="青虹北斗头盔",chance=0.0417,max=1,min=1,sid=60091,type=0,},
					[11]= {name="青虹北斗战甲(男)",chance=0.0067,max=1,min=1,sid=60092,type=0,},
					[12]= {name="青虹北斗战甲(女)",chance=0.0067,max=1,min=1,sid=60093,type=0,},
					[13]= {name="青虹北斗项链",chance=0.0417,max=1,min=1,sid=60094,type=0,},
					[14]= {name="青虹北斗手镯",chance=0.0557,max=1,min=1,sid=60095,type=0,},
					[15]= {name="青虹北斗宝石",chance=0.0417,max=1,min=1,sid=60096,type=0,},
					[16]= {name="青虹北斗战靴",chance=0.0417,max=1,min=1,sid=60097,type=0,},
					[17]= {name="青虹北斗腰带",chance=0.0417,max=1,min=1,sid=60098,type=0,},
					[18]= {name="青虹北斗戒指",chance=0.0557,max=1,min=1,sid=60212,type=0,},
					[19]= {name="无量沧海头盔",chance=0.0417,max=1,min=1,sid=60151,type=0,},
					[20]= {name="无量沧海魔袍(男)",chance=0.0067,max=1,min=1,sid=60152,type=0,},
					[21]= {name="无量沧海魔袍(女)",chance=0.0067,max=1,min=1,sid=60153,type=0,},
					[22]= {name="无量沧海项链",chance=0.0417,max=1,min=1,sid=60154,type=0,},
					[23]= {name="无量沧海手镯",chance=0.0557,max=1,min=1,sid=60155,type=0,},
					[24]= {name="无量沧海宝石",chance=0.0417,max=1,min=1,sid=60156,type=0,},
					[25]= {name="无量沧海法履",chance=0.0417,max=1,min=1,sid=60157,type=0,},
					[26]= {name="无量沧海戒指",chance=0.0557,max=1,min=1,sid=60219,type=0,},
					[27]= {name="无量沧海腰带",chance=0.0417,max=1,min=1,sid=60158,type=0,},
				},
			type=1,
		},
	[23]= {
			id=23,
			name="60级套装武器",
			elems= {
					[1]= {name="仙人指路",chance=0.3333,max=1,min=1,sid=60040,type=0,},
					[2]= {name="五虎断岳",chance=0.3333,max=1,min=1,sid=60100,type=0,},
					[3]= {name="离火薄天",chance=0.3334,max=1,min=1,sid=60160,type=0,},
				},
			type=1,
		},
	[24]= {
			id=24,
			name="60级套装零件",
			elems= {
					[1]= {name="百鬼夜宴头盔",chance=0.0417,max=1,min=1,sid=60041,type=0,},
					[2]= {name="百鬼夜宴道袍(男)",chance=0.0067,max=1,min=1,sid=60042,type=0,},
					[3]= {name="百鬼夜宴道袍(女)",chance=0.0067,max=1,min=1,sid=60043,type=0,},
					[4]= {name="百鬼夜宴项链",chance=0.0417,max=1,min=1,sid=60044,type=0,},
					[5]= {name="百鬼夜宴手镯",chance=0.0557,max=1,min=1,sid=60045,type=0,},
					[6]= {name="百鬼夜宴宝石",chance=0.0417,max=1,min=1,sid=60046,type=0,},
					[7]= {name="百鬼夜宴道鞋",chance=0.0417,max=1,min=1,sid=60047,type=0,},
					[8]= {name="百鬼夜宴腰带",chance=0.0417,max=1,min=1,sid=60048,type=0,},
					[9]= {name="百鬼夜宴戒指",chance=0.0557,max=1,min=1,sid=60206,type=0,},
					[10]= {name="天龙神锢头盔",chance=0.0417,max=1,min=1,sid=60101,type=0,},
					[11]= {name="天龙神锢战甲(男)",chance=0.0067,max=1,min=1,sid=60102,type=0,},
					[12]= {name="天龙神锢战甲(女)",chance=0.0067,max=1,min=1,sid=60103,type=0,},
					[13]= {name="天龙神锢项链",chance=0.0417,max=1,min=1,sid=60104,type=0,},
					[14]= {name="天龙神锢手镯",chance=0.0557,max=1,min=1,sid=60105,type=0,},
					[15]= {name="天龙神锢宝石",chance=0.0417,max=1,min=1,sid=60106,type=0,},
					[16]= {name="天龙神锢战靴",chance=0.0417,max=1,min=1,sid=60107,type=0,},
					[17]= {name="天龙神锢腰带",chance=0.0417,max=1,min=1,sid=60108,type=0,},
					[18]= {name="天龙神锢戒指",chance=0.0557,max=1,min=1,sid=60213,type=0,},
					[19]= {name="五法青云头盔",chance=0.0417,max=1,min=1,sid=60161,type=0,},
					[20]= {name="五法青云魔袍(男)",chance=0.0067,max=1,min=1,sid=60162,type=0,},
					[21]= {name="五法青云魔袍(女)",chance=0.0067,max=1,min=1,sid=60163,type=0,},
					[22]= {name="五法青云项链",chance=0.0417,max=1,min=1,sid=60164,type=0,},
					[23]= {name="五法青云手镯",chance=0.0557,max=1,min=1,sid=60165,type=0,},
					[24]= {name="五法青云宝石",chance=0.0417,max=1,min=1,sid=60166,type=0,},
					[25]= {name="五法青云法履",chance=0.0417,max=1,min=1,sid=60167,type=0,},
					[26]= {name="五法青云戒指",chance=0.0557,max=1,min=1,sid=60220,type=0,},
					[27]= {name="五法青云腰带",chance=0.0417,max=1,min=1,sid=60168,type=0,},
				},
			type=1,
		},
	[25]= {
			id=25,
			name="70级套装武器",
			elems= {
					[1]= {name="缚神揽月",chance=0.3333,max=1,min=1,sid=60050,type=0,},
					[2]= {name="肃魂裂天",chance=0.3333,max=1,min=1,sid=60110,type=0,},
					[3]= {name="牧云惊鸿",chance=0.3334,max=1,min=1,sid=60170,type=0,},
				},
			type=1,
		},
	[26]= {
			id=26,
			name="70级套装零件",
			elems= {
					[1]= {name="太极逍遥头盔",chance=0.0417,max=1,min=1,sid=60051,type=0,},
					[2]= {name="太极逍遥道衣(男)",chance=0.0167,max=1,min=1,sid=60052,type=0,},
					[3]= {name="太极逍遥道衣(女)",chance=0.0125,max=1,min=1,sid=60053,type=0,},
					[4]= {name="太极逍遥项链",chance=0.0417,max=1,min=1,sid=60054,type=0,},
					[5]= {name="太极逍遥手镯",chance=0.0557,max=1,min=1,sid=60055,type=0,},
					[6]= {name="太极逍遥宝石",chance=0.0417,max=1,min=1,sid=60056,type=0,},
					[7]= {name="太极逍遥道鞋",chance=0.0417,max=1,min=1,sid=60057,type=0,},
					[8]= {name="太极逍遥腰带",chance=0.0417,max=1,min=1,sid=60058,type=0,},
					[9]= {name="太极逍遥戒指",chance=0.0557,max=1,min=1,sid=60207,type=0,},
					[10]= {name="弑皇破天头盔",chance=0.0417,max=1,min=1,sid=60111,type=0,},
					[11]= {name="弑皇破天战甲(男)",chance=0.0167,max=1,min=1,sid=60112,type=0,},
					[12]= {name="弑皇破天战甲(女)",chance=0.0167,max=1,min=1,sid=60113,type=0,},
					[13]= {name="弑皇破天项链",chance=0.0417,max=1,min=1,sid=60114,type=0,},
					[14]= {name="弑皇破天手镯",chance=0.0557,max=1,min=1,sid=60115,type=0,},
					[15]= {name="弑皇破天宝石",chance=0.0417,max=1,min=1,sid=60116,type=0,},
					[16]= {name="弑皇破天战靴",chance=0.0417,max=1,min=1,sid=60117,type=0,},
					[17]= {name="弑皇破天腰带",chance=0.0417,max=1,min=1,sid=60118,type=0,},
					[18]= {name="狂澜魄岳头盔",chance=0.0417,max=1,min=1,sid=60171,type=0,},
					[19]= {name="狂澜魄岳魔袍(男)",chance=0.0167,max=1,min=1,sid=60172,type=0,},
					[20]= {name="狂澜魄岳魔袍(女)",chance=0.0167,max=1,min=1,sid=60173,type=0,},
					[21]= {name="狂澜魄岳项链",chance=0.0417,max=1,min=1,sid=60174,type=0,},
					[22]= {name="狂澜魄岳手镯",chance=0.0557,max=1,min=1,sid=60175,type=0,},
					[23]= {name="狂澜魄岳宝石",chance=0.0417,max=1,min=1,sid=60176,type=0,},
					[24]= {name="狂澜魄岳法履",chance=0.0417,max=1,min=1,sid=60177,type=0,},
					[25]= {name="狂澜魄岳腰带",chance=0.0557,max=1,min=1,sid=60178,type=0,},
					[26]= {name="狂澜魄岳戒指",chance=0.0417,max=1,min=1,sid=60221,type=0,},
				},
			type=1,
		},
	[27]= {
			id=27,
			name="特殊戒指",
			elems= {
					[1]= {name="复生戒指",chance=0.3333,max=1,min=1,sid=60223,type=0,},
					[2]= {name="定身戒指",chance=0.3333,max=1,min=1,sid=60231,type=0,},
					[3]= {name="护法戒指",chance=0.3334,max=1,min=1,sid=60239,type=0,},
				},
			type=1,
		},
	[28]= {
			id=28,
			name="魂石碎片",
			elems= {
					[1]= {name="生命魂石碎片",chance=0.2,max=1,min=1,sid=30280,type=0,},
					[2]= {name="魔法魂石碎片",chance=0.2,max=1,min=1,sid=30281,type=0,},
					[3]= {name="物防魂石碎片",chance=0.2,max=1,min=1,sid=30282,type=0,},
					[4]= {name="魔防魂石碎片",chance=0.2,max=1,min=1,sid=30283,type=0,},
					[5]= {name="物攻魂石碎片",chance=0.0666,max=1,min=1,sid=30284,type=0,},
					[6]= {name="魔攻魂石碎片",chance=0.0667,max=1,min=1,sid=30285,type=0,},
					[7]= {name="道攻魂石碎片",chance=0.0667,max=1,min=1,sid=30286,type=0,},
				},
			type=1,
		},
	[29]= {
			id=29,
			name="一级魂石",
			elems= {
					[1]= {name="1级生命魂石",chance=0.2,max=1,min=1,sid=10007,type=0,},
					[2]= {name="1级魔法魂石",chance=0.2,max=1,min=1,sid=10008,type=0,},
					[3]= {name="1级物防魂石",chance=0.2,max=1,min=1,sid=10009,type=0,},
					[4]= {name="1级魔防魂石",chance=0.2,max=1,min=1,sid=10010,type=0,},
					[5]= {name="1级物攻魂石",chance=0.0666,max=1,min=1,sid=10011,type=0,},
					[6]= {name="1级魔攻魂石",chance=0.0667,max=1,min=1,sid=10012,type=0,},
					[7]= {name="1级道攻魂石",chance=0.0667,max=1,min=1,sid=10013,type=0,},
				},
			type=1,
		},
	[30]= {
			id=30,
			name="二级魂石",
			elems= {
					[1]= {name="2级生命魂石",chance=0.2,max=1,min=1,sid=10014,type=0,},
					[2]= {name="2级魔法魂石",chance=0.2,max=1,min=1,sid=10015,type=0,},
					[3]= {name="2级物防魂石",chance=0.2,max=1,min=1,sid=10016,type=0,},
					[4]= {name="2级魔防魂石",chance=0.2,max=1,min=1,sid=10017,type=0,},
					[5]= {name="2级物攻魂石",chance=0.0666,max=1,min=1,sid=10018,type=0,},
					[6]= {name="2级魔攻魂石",chance=0.0667,max=1,min=1,sid=10019,type=0,},
					[7]= {name="2级道攻魂石",chance=0.0667,max=1,min=1,sid=10020,type=0,},
				},
			type=1,
		},
	[31]= {
			id=31,
			name="三级魂石",
			elems= {
					[1]= {name="3级生命魂石",chance=0.2,max=1,min=1,sid=10021,type=0,},
					[2]= {name="3级魔法魂石",chance=0.2,max=1,min=1,sid=10022,type=0,},
					[3]= {name="3级物防魂石",chance=0.2,max=1,min=1,sid=10023,type=0,},
					[4]= {name="3级魔防魂石",chance=0.2,max=1,min=1,sid=10024,type=0,},
					[5]= {name="3级物攻魂石",chance=0.0666,max=1,min=1,sid=10025,type=0,},
					[6]= {name="3级魔攻魂石",chance=0.0667,max=1,min=1,sid=10026,type=0,},
					[7]= {name="3级道攻魂石",chance=0.0667,max=1,min=1,sid=10027,type=0,},
				},
			type=1,
		},
	[32]= {
			id=32,
			name="四级魂石",
			elems= {
					[1]= {name="4级生命魂石",chance=0.2,max=1,min=1,sid=10028,type=0,},
					[2]= {name="4级魔法魂石",chance=0.2,max=1,min=1,sid=10029,type=0,},
					[3]= {name="4级物防魂石",chance=0.2,max=1,min=1,sid=10030,type=0,},
					[4]= {name="4级魔防魂石",chance=0.2,max=1,min=1,sid=10031,type=0,},
					[5]= {name="4级物攻魂石",chance=0.0666,max=1,min=1,sid=10032,type=0,},
					[6]= {name="4级魔攻魂石",chance=0.0667,max=1,min=1,sid=10033,type=0,},
					[7]= {name="4级道攻魂石",chance=0.0667,max=1,min=1,sid=10034,type=0,},
				},
			type=1,
		},
	[33]= {
			id=33,
			name="五级魂石",
			elems= {
					[1]= {name="5级生命魂石",chance=0.2,max=1,min=1,sid=10035,type=0,},
					[2]= {name="5级魔法魂石",chance=0.2,max=1,min=1,sid=10036,type=0,},
					[3]= {name="5级物防魂石",chance=0.2,max=1,min=1,sid=10037,type=0,},
					[4]= {name="5级魔防魂石",chance=0.2,max=1,min=1,sid=10038,type=0,},
					[5]= {name="5级物攻魂石",chance=0.0666,max=1,min=1,sid=10039,type=0,},
					[6]= {name="5级魔攻魂石",chance=0.0667,max=1,min=1,sid=10040,type=0,},
					[7]= {name="5级道攻魂石",chance=0.0667,max=1,min=1,sid=10041,type=0,},
				},
			type=1,
		},
	[34]= {
			id=34,
			name="六级魂石",
			elems= {
					[1]= {name="6级生命魂石",chance=0.2,max=1,min=1,sid=10042,type=0,},
					[2]= {name="6级魔法魂石",chance=0.2,max=1,min=1,sid=10043,type=0,},
					[3]= {name="6级物防魂石",chance=0.2,max=1,min=1,sid=10044,type=0,},
					[4]= {name="6级魔防魂石",chance=0.2,max=1,min=1,sid=10045,type=0,},
					[5]= {name="6级物攻魂石",chance=0.0666,max=1,min=1,sid=10046,type=0,},
					[6]= {name="6级魔攻魂石",chance=0.0667,max=1,min=1,sid=10047,type=0,},
					[7]= {name="6级道攻魂石",chance=0.0667,max=1,min=1,sid=10048,type=0,},
				},
			type=1,
		},
	[35]= {
			id=35,
			name="七级魂石",
			elems= {
					[1]= {name="7级生命魂石",chance=0.2,max=1,min=1,sid=10049,type=0,},
					[2]= {name="7级魔法魂石",chance=0.2,max=1,min=1,sid=10050,type=0,},
					[3]= {name="7级物防魂石",chance=0.2,max=1,min=1,sid=10051,type=0,},
					[4]= {name="7级魔防魂石",chance=0.2,max=1,min=1,sid=10052,type=0,},
					[5]= {name="7级物攻魂石",chance=0.0666,max=1,min=1,sid=10053,type=0,},
					[6]= {name="7级魔攻魂石",chance=0.0667,max=1,min=1,sid=10054,type=0,},
					[7]= {name="7级道攻魂石",chance=0.0667,max=1,min=1,sid=10055,type=0,},
				},
			type=1,
		},
	[36]= {
			id=36,
			name="八级魂石",
			elems= {
					[1]= {name="8级生命魂石",chance=0.2,max=1,min=1,sid=10056,type=0,},
					[2]= {name="8级魔法魂石",chance=0.2,max=1,min=1,sid=10057,type=0,},
					[3]= {name="8级物防魂石",chance=0.2,max=1,min=1,sid=10058,type=0,},
					[4]= {name="8级魔防魂石",chance=0.2,max=1,min=1,sid=10059,type=0,},
					[5]= {name="8级物攻魂石",chance=0.0666,max=1,min=1,sid=10060,type=0,},
					[6]= {name="8级魔攻魂石",chance=0.0667,max=1,min=1,sid=10061,type=0,},
					[7]= {name="8级道攻魂石",chance=0.0667,max=1,min=1,sid=10062,type=0,},
				},
			type=1,
		},
	[37]= {
			id=37,
			name="九级魂石",
			elems= {
					[1]= {name="9级生命魂石",chance=0.2,max=1,min=1,sid=10063,type=0,},
					[2]= {name="9级魔法魂石",chance=0.2,max=1,min=1,sid=10064,type=0,},
					[3]= {name="9级物防魂石",chance=0.2,max=1,min=1,sid=10065,type=0,},
					[4]= {name="9级魔防魂石",chance=0.2,max=1,min=1,sid=10066,type=0,},
					[5]= {name="9级物攻魂石",chance=0.0666,max=1,min=1,sid=10067,type=0,},
					[6]= {name="9级魔攻魂石",chance=0.0667,max=1,min=1,sid=10068,type=0,},
					[7]= {name="9级道攻魂石",chance=0.0667,max=1,min=1,sid=10069,type=0,},
				},
			type=1,
		},
	[38]= {
			id=38,
			name="十级魂石",
			elems= {
					[1]= {name="10级生命魂石",chance=0.2,max=1,min=1,sid=10070,type=0,},
					[2]= {name="10级魔法魂石",chance=0.2,max=1,min=1,sid=10071,type=0,},
					[3]= {name="10级物防魂石",chance=0.2,max=1,min=1,sid=10072,type=0,},
					[4]= {name="10级魔防魂石",chance=0.2,max=1,min=1,sid=10073,type=0,},
					[5]= {name="10级物攻魂石",chance=0.0666,max=1,min=1,sid=10074,type=0,},
					[6]= {name="10级魔攻魂石",chance=0.0667,max=1,min=1,sid=10075,type=0,},
					[7]= {name="10级道攻魂石",chance=0.0667,max=1,min=1,sid=10076,type=0,},
				},
			type=1,
		},
	[39]= {
			id=39,
			name="十一级魂石",
			elems= {
					[1]= {name="11级生命魂石",chance=0.25,max=1,min=1,sid=10077,type=0,},
					[2]= {name="11级魔法魂石",chance=0.25,max=1,min=1,sid=10078,type=0,},
					[3]= {name="11级物防魂石",chance=0.25,max=1,min=1,sid=10079,type=0,},
					[4]= {name="11级魔防魂石",chance=0.25,max=1,min=1,sid=10080,type=0,},
				},
			type=1,
		},
	[40]= {
			id=40,
			name="所有魂石",
			elems= {
					[1]= {name="$魂石碎片",chance=0.2,max=1,min=1,sid=28,type=1,},
					[2]= {name="$一级魂石",chance=0.2,max=1,min=1,sid=29,type=1,},
					[3]= {name="$二级魂石",chance=0.2,max=1,min=1,sid=30,type=1,},
					[4]= {name="$三级魂石",chance=0.2,max=1,min=1,sid=31,type=1,},
					[5]= {name="$四级魂石",chance=0.0666,max=1,min=1,sid=32,type=1,},
					[6]= {name="$五级魂石",chance=0.0667,max=1,min=1,sid=33,type=1,},
					[7]= {name="$六级魂石",chance=0.0667,max=1,min=1,sid=34,type=1,},
				},
			type=1,
		},
	[41]= {
			id=41,
			name="物攻击魂石",
			elems= {
					[1]= {name="物攻魂石碎片",chance=0.2,max=1,min=1,sid=30284,type=0,},
					[2]= {name="1级物攻魂石",chance=0.2,max=1,min=1,sid=10011,type=0,},
					[3]= {name="2级物攻魂石",chance=0.2,max=1,min=1,sid=10018,type=0,},
					[4]= {name="3级物攻魂石",chance=0.2,max=1,min=1,sid=10025,type=0,},
					[5]= {name="4级物攻魂石",chance=0.0666,max=1,min=1,sid=10032,type=0,},
					[6]= {name="5级物攻魂石",chance=0.0667,max=1,min=1,sid=10039,type=0,},
					[7]= {name="6级物攻魂石",chance=0.0667,max=1,min=1,sid=10046,type=0,},
				},
			type=1,
		},
	[42]= {
			id=42,
			name="技能书",
			elems= {
					[1]= {name="基础剑法",chance=0.0527,max=1,min=1,sid=30097,type=0,},
					[2]= {name="毒药术",chance=0.0527,max=1,min=1,sid=30099,type=0,},
					[3]= {name="弦月剑法",chance=0.0527,max=1,min=1,sid=30104,type=0,},
					[4]= {name="熔岩之火",chance=0.0527,max=1,min=1,sid=30110,type=0,},
					[5]= {name="火球术",chance=0.0527,max=1,min=1,sid=30112,type=0,},
					[6]= {name="天雷术",chance=0.0526,max=1,min=1,sid=30114,type=0,},
					[7]= {name="法术抗拒",chance=0.0526,max=1,min=1,sid=30116,type=0,},
					[8]= {name="穿透闪电",chance=0.0526,max=1,min=1,sid=30118,type=0,},
					[9]= {name="冰风暴",chance=0.0526,max=1,min=1,sid=30120,type=0,},
					[10]= {name="群体恢复术",chance=0.0526,max=1,min=1,sid=30125,type=0,},
					[11]= {name="符咒术",chance=0.0527,max=1,min=1,sid=30127,type=0,},
					[12]= {name="群体遁隐术",chance=0.0526,max=1,min=1,sid=30130,type=0,},
					[13]= {name="灵魂锻炼术",chance=0.0526,max=1,min=1,sid=30132,type=0,},
					[14]= {name="神圣幽灵护体术",chance=0.0526,max=1,min=1,sid=30134,type=0,},
					[15]= {name="召唤术",chance=0.0526,max=1,min=1,sid=30136,type=0,},
					[16]= {name="战神冲撞",chance=0.0526,max=1,min=1,sid=30138,type=0,},
				},
			type=1,
		},
	[43]= {
			id=43,
			name="初级技能书",
			elems= {
					[1]= {name="毒药术",chance=0.3333,max=1,min=1,sid=30099,type=0,},
					[2]= {name="基础剑法",chance=0.3334,max=1,min=1,sid=30097,type=0,},
					[3]= {name="火球术",chance=0.3333,max=1,min=1,sid=30112,type=0,},
				},
			type=1,
		},
	[44]= {
			id=44,
			name="高级技能书",
			elems= {
					[1]= {name="冰风暴",chance=0.3334,max=1,min=1,sid=30120,type=0,},
					[2]= {name="召唤术",chance=0.3333,max=1,min=1,sid=30136,type=0,},
				},
			type=1,
		},
	[45]= {
			id=45,
			name="生死状一二",
			elems= {
					[1]= {name="生死状一",chance=0.6,max=1,min=1,sid=40105,type=0,},
					[2]= {name="生死状二",chance=0.4,max=1,min=1,sid=40106,type=0,},
				},
			type=1,
		},
	[46]= {
			id=46,
			name="生死状二三",
			elems= {
					[1]= {name="生死状二",chance=0.6,max=1,min=1,sid=40106,type=0,},
					[2]= {name="生死状三",chance=0.4,max=1,min=1,sid=40107,type=0,},
				},
			type=1,
		},
	[47]= {
			id=47,
			name="生死状三四",
			elems= {
					[1]= {name="生死状三",chance=0.6,max=1,min=1,sid=40107,type=0,},
					[2]= {name="生死状四",chance=0.4,max=1,min=1,sid=40108,type=0,},
				},
			type=1,
		},
	[48]= {
			id=48,
			name="生死状四五",
			elems= {
					[1]= {name="生死状四",chance=0.6,max=1,min=1,sid=40108,type=0,},
					[2]= {name="生死状五",chance=0.4,max=1,min=1,sid=40109,type=0,},
				},
			type=1,
		},
	[49]= {
			id=49,
			name="新手鹤嘴锄",
			elems= {
					[1]= {name="铜矿",chance=0.0252,max=1,min=1,sid=40018,type=0,},
					[2]= {name="铁矿",chance=0.0124,max=1,min=1,sid=40017,type=0,},
					[3]= {name="银矿",chance=0.0058,max=1,min=1,sid=40019,type=0,},
					[4]= {name="金矿",chance=0.0034,max=1,min=1,sid=40020,type=0,},
					[5]= {name="黑铁",chance=0.0072,max=1,min=1,sid=40008,type=0,},
					[6]= {name="绿宝石",chance=0.0031,max=1,min=1,sid=40009,type=0,},
					[7]= {name="紫晶钻",chance=0.0005,max=1,min=1,sid=40010,type=0,},
				},
			type=1,
		},
	[50]= {
			id=50,
			name="老手鹤嘴锄",
			elems= {
					[1]= {name="铜矿",chance=0.02898,max=1,min=1,sid=40018,type=0,},
					[2]= {name="铁矿",chance=0.01426,max=1,min=1,sid=40017,type=0,},
					[3]= {name="银矿",chance=0.00667,max=1,min=1,sid=40019,type=0,},
					[4]= {name="金矿",chance=0.00391,max=1,min=1,sid=40020,type=0,},
					[5]= {name="黑铁",chance=0.00864,max=1,min=1,sid=40008,type=0,},
					[6]= {name="绿宝石",chance=0.003565,max=1,min=1,sid=40009,type=0,},
					[7]= {name="紫晶钻",chance=0.000575,max=1,min=1,sid=40010,type=0,},
					[8]= {name="大铜锭",chance=0.000422,max=1,min=1,sid=30033,type=0,},
				},
			type=1,
		},
	[51]= {
			id=51,
			name="大师鹤嘴锄",
			elems= {
					[1]= {name="黑铁",chance=0.204,max=1,min=1,sid=40008,type=0,},
					[2]= {name="绿宝石",chance=0.1941,max=1,min=1,sid=40009,type=0,},
					[3]= {name="紫晶钻",chance=0.106,max=1,min=1,sid=40010,type=0,},
					[4]= {name="大铜锭",chance=0.005064,max=1,min=1,sid=30033,type=0,},
					[5] = {name="灵魂石", chance=0.0876, max=1, min=1, sid=40011, type=0},      -- 0.096 * 0.6 = 0.0576
                    [6] = {name="蓝钻", chance=0.0596, max=1, min=1, sid=41110, type=0},        -- 0.066 * 0.6 = 0.0396
                    [7] = {name="紫钻", chance=0.0486, max=1, min=1, sid=41111, type=0},       -- 0.056 * 0.6 = 0.0336
                    [8] = {name="橙钻", chance=0.0350, max=1, min=1, sid=41112, type=0},       -- 0.045 * 0.6 = 0.0270
                    [9] = {name="四级灵石", chance=0.0316, max=1, min=1, sid=40003, type=0},       -- 0.036 * 0.6 = 0.0216
                    [10] = {name="五级灵石", chance=0.0234, max=1, min=1, sid=40004, type=0},     -- 0.019 * 0.6 = 0.0114
                    [11] = {name="灵光碎片", chance=0.0392, max=1, min=1, sid=40005, type=0},
					[12] = {name="清洗碎片", chance=0.009, max=1, min=1, sid=40006, type=0},
					[13]= {name="神的纯银鹤嘴锄",chance=0.0001,max=1,min=1,sid=70167,type=0,},
				},
			type=1,
		},
	[52]= {
			id=52,
			name="纯银、宝石鹤嘴锄",
			elems= {
					[1]= {name="铜矿",chance=0.0383261,max=1,min=1,sid=40018,type=0,},
					[2]= {name="铁矿",chance=0.0188589,max=1,min=1,sid=40017,type=0,},
					[3]= {name="银矿",chance=0.0088211,max=1,min=1,sid=40019,type=0,},
					[4]= {name="金矿",chance=0.005171,max=1,min=1,sid=40020,type=0,},
					[5]= {name="钻石矿",chance=0.00355,max=1,min=1,sid=40021,type=0,},
					[6]= {name="黑铁",chance=0.0124416,max=1,min=1,sid=40008,type=0,},
					[7]= {name="绿宝石",chance=0.00471471,max=1,min=1,sid=40009,type=0,},
					[8]= {name="紫晶钻",chance=0.0008,max=1,min=1,sid=40010,type=0,},
					[9]= {name="灵魂石",chance=0.00085,max=1,min=1,sid=40011,type=0,},
					[10]= {name="大铜锭",chance=0.000608,max=1,min=1,sid=30033,type=0,},
					[11]= {name="大银锭",chance=0.00022,max=1,min=1,sid=30034,type=0,},
					[12]= {name="一级灵石",chance=0.0051,max=1,min=1,sid=40000,type=0,},
					[13]= {name="二级灵石",chance=0.0041,max=1,min=1,sid=40001,type=0,},
					[14]= {name="三级灵石",chance=0.0031,max=1,min=1,sid=40002,type=0,},
					[15]= {name="四级灵石",chance=0.0021,max=1,min=1,sid=40003,type=0,},
					[16]= {name="五级级灵石",chance=0.0002,max=1,min=1,sid=40005,type=0,},
					[17]= {name="黄金鹤嘴锄",chance=1.74e-05,max=1,min=1,sid=70173,type=0,},
				},
			type=1,
		},
	[53]= {
			id=53,
			name="黄金鹤嘴锄",
			elems= {
					[1]= {name="铜矿",chance=0.0441,max=1,min=1,sid=40018,type=0,},
					[2]= {name="铁矿",chance=0.0217,max=1,min=1,sid=40017,type=0,},
					[3]= {name="银矿",chance=0.0101,max=1,min=1,sid=40019,type=0,},
					[4]= {name="金矿",chance=0.0059,max=1,min=1,sid=40020,type=0,},
					[5]= {name="钻石矿",chance=0.0041,max=1,min=1,sid=40021,type=0,},
					[6]= {name="黑铁",chance=0.0149,max=1,min=1,sid=40008,type=0,},
					[7]= {name="绿宝石",chance=0.0054,max=1,min=1,sid=40009,type=0,},
					[8]= {name="紫晶钻",chance=0.0008745,max=1,min=1,sid=40010,type=0,},
					[9]= {name="灵魂石",chance=0.000978,max=1,min=1,sid=40011,type=0,},
					[10]= {name="大铜锭",chance=0.000729,max=1,min=1,sid=30033,type=0,},
					[11]= {name="大银锭",chance=0.000264,max=1,min=1,sid=30034,type=0,},
					[12]= {name="一级灵石",chance=0.0061,max=1,min=1,sid=40000,type=0,},
					[13]= {name="二级灵石",chance=0.0051,max=1,min=1,sid=40001,type=0,},
					[14]= {name="三级灵石",chance=0.0041,max=1,min=1,sid=40002,type=0,},
					[15]= {name="四级灵石",chance=0.0031,max=1,min=1,sid=40003,type=0,},
					[16]= {name="五级级灵石",chance=0.0003,max=1,min=1,sid=40005,type=0,},
					[17]= {name="神的纯银鹤嘴锄",chance=1.74e-05,max=1,min=1,sid=70167,type=0,},
				},
			type=1,
		},
	[54] = {
    id = 54,
    name = "神的纯银鹤嘴锄",
    elems = {
        [1] = {name="灵魂石", chance=0.106, max=1, min=1, sid=40011, type=0},      
        [2] = {name="蓝钻", chance=0.086, max=1, min=1, sid=41110, type=0},        
        [3] = {name="紫钻", chance=0.066, max=1, min=1, sid=41111, type=0},       
        [4] = {name="橙钻", chance=0.045, max=1, min=1, sid=41112, type=0},       
        [5] = {name="四级灵石", chance=0.056, max=1, min=1, sid=40003, type=0},       
        [6] = {name="五级灵石", chance=0.029, max=1, min=1, sid=40004, type=0},
        [7] = {name="灵光碎片", chance=0.032, max=1, min=1, sid=40005, type=0},	
		[8] = {name="清洗碎片", chance=0.015, max=1, min=1, sid=40006, type=0},
        [9]= {name="神的黄金鹤嘴锄",chance=0.00005,max=1,min=1,sid=70168,type=0,},		
    },
    type = 1,
},

	[55] = {
    id = 55,
    name = "神的黄金鹤嘴锄",
    elems = {
        [1] = {name="灵魂石", chance=0.226, max=1, min=1, sid=40011, type=0},      
        [2] = {name="蓝钻", chance=0.216, max=1, min=1, sid=41110, type=0},        
        [3] = {name="紫钻", chance=0.186, max=1, min=1, sid=41111, type=0},       
        [4] = {name="橙钻", chance=0.109, max=1, min=1, sid=41112, type=0},       
        [5] = {name="四级灵石", chance=0.136, max=1, min=1, sid=40003, type=0},    
        [6] = {name="五级灵石", chance=0.065, max=1, min=1, sid=40004, type=0},
        [7] = {name="灵光碎片", chance=0.122, max=1, min=1, sid=40005, type=0},
		[8] = {name="清洗碎片", chance=0.045, max=1, min=1, sid=40006, type=0},	   
        
    },
    type = 1,
},

	[56]= {
			id=56,
			name="经验玉掉落",
			elems= {
					[1]= {name="经验玉(小)",chance=0.3,max=1,min=1,sid=30037,type=0,},
					[2]= {name="经验玉(中)",chance=0.2,max=1,min=1,sid=30036,type=0,},
					[3]= {name="经验灵石(小)",chance=0.3,max=1,min=1,sid=30068,type=0,},
					[4]= {name="经验灵石(中)",chance=0.2,max=1,min=1,sid=30067,type=0,},
				},
			type=1,
		},
	[57]= {
			id=57,
			name="小怪掉落杂品",
			elems= {
					[1]= {name="鉴定图鉴",chance=0.2564,max=1,min=1,sid=40060,type=0,},
					[2]= {name="强效太阳水",chance=0.392,max=1,min=1,sid=39009,type=0,},
					[3]= {name="祝福油",chance=0.0256,max=1,min=1,sid=30018,type=0,},
					[4]= {name="$经验玉掉落",chance=0.076,max=1,min=1,sid=56,type=1,},
				},
			type=1,
		},
	[58]= {
			id=58,
			name="小精英怪掉落杂品",
			elems= {
					[1]= {name="$小怪掉落杂品",chance=0.7,max=1,min=1,sid=57,type=1,},
					[2]= {name="百年人参",chance=0.1,max=1,min=1,sid=39015,type=0,},
					[3]= {name="百年雪莲",chance=0.08,max=1,min=1,sid=39019,type=0,},
					[4]= {name="攻击药水(小)",chance=0.05,max=1,min=1,sid=39023,type=0,},
					[5]= {name="防御药水(小)",chance=0.055,max=1,min=1,sid=39025,type=0,},
					[6]= {name="战神油",chance=0.015,max=1,min=1,sid=30017,type=0,},
				},
			type=1,
		},
	[59]= {
			id=59,
			name="小boss掉落常用杂品",
			elems= {
					[1]= {name="鉴定图鉴",chance=0.0769,max=1,min=1,sid=40060,type=0,},
					[2]= {name="祝福油",chance=0.0769,max=1,min=1,sid=30018,type=0,},
					[3]= {name="百年人参",chance=0.0769,max=1,min=1,sid=39015,type=0,},
					[4]= {name="百年雪莲",chance=0.0769,max=1,min=1,sid=39019,type=0,},
					[5]= {name="攻击药水(小)",chance=0.077,max=1,min=1,sid=39023,type=0,},
					[6]= {name="防御药水(小)",chance=0.077,max=1,min=1,sid=39025,type=0,},
					[7]= {name="1.5倍经验神符",chance=0.077,max=1,min=1,sid=30000,type=0,},
					[8]= {name="2倍经验神符",chance=0.0769,max=1,min=1,sid=30001,type=0,},
					[9]= {name="诛魔神石",chance=0.0769,max=1,min=1,sid=40052,type=0,},
					[10]= {name="宠物项圈",chance=0.0769,max=1,min=1,sid=40053,type=0,},
					[11]= {name="副本神符",chance=0.0769,max=1,min=1,sid=40051,type=0,},
					[12]= {name="红玫瑰",chance=0.0769,max=1,min=1,sid=39029,type=0,},
					[13]= {name="经验灵符",chance=0.0769,max=1,min=1,sid=30064,type=0,},
				},
			type=1,
		},
	[60]= {
			id=60,
			name="小boss掉落稀有杂品",
			elems= {
					[1]= {name="战神油",chance=0.1,max=1,min=1,sid=30017,type=0,},
					[2]= {name="防御药水(大)",chance=0.215,max=1,min=1,sid=39027,type=0,},
					[3]= {name="攻击药水(大)",chance=0.215,max=1,min=1,sid=39038,type=0,},
					[4]= {name="背包扩展符",chance=0.1,max=1,min=1,sid=40068,type=0,},
					[5]= {name="强化保护符",chance=0.17,max=1,min=1,sid=40012,type=0,},
					[6]= {name="清洗丹",chance=0.15,max=1,min=1,sid=40041,type=0,},
					[7]= {name="鉴定锁",chance=0.05,max=1,min=1,sid=40042,type=0,},
				},
			type=1,
		},
	[61]= {
			id=61,
			name="中boss掉落常用杂品",
			elems= {
					[1]= {name="鉴定图鉴",chance=0.08,max=1,min=1,sid=40060,type=0,},
					[2]= {name="祝福油",chance=0.08,max=1,min=1,sid=30018,type=0,},
					[3]= {name="百年人参",chance=0.04,max=1,min=1,sid=39015,type=0,},
					[4]= {name="百年雪莲",chance=0.04,max=1,min=1,sid=39019,type=0,},
					[5]= {name="千年玄参",chance=0.05,max=1,min=1,sid=39016,type=0,},
					[6]= {name="千年冰莲",chance=0.05,max=1,min=1,sid=39020,type=0,},
					[7]= {name="攻击药水(小)",chance=0.05,max=1,min=1,sid=39023,type=0,},
					[8]= {name="防御药水(小)",chance=0.05,max=1,min=1,sid=39025,type=0,},
					[9]= {name="攻击药水(中)",chance=0.04,max=1,min=1,sid=39024,type=0,},
					[10]= {name="防御药水(中)",chance=0.04,max=1,min=1,sid=39026,type=0,},
					[11]= {name="诛魔神石",chance=0.08,max=1,min=1,sid=40052,type=0,},
					[12]= {name="宠物项圈",chance=0.08,max=1,min=1,sid=40053,type=0,},
					[13]= {name="副本神符",chance=0.08,max=1,min=1,sid=40051,type=0,},
					[14]= {name="红玫瑰",chance=0.08,max=1,min=1,sid=39029,type=0,},
					[15]= {name="经验灵符",chance=0.08,max=1,min=1,sid=30064,type=0,},
				},
			type=1,
		},
	[62]= {
			id=62,
			name="中boss掉落稀有杂品",
			elems= {
					[1]= {name="战神油",chance=0.1,max=1,min=1,sid=30017,type=0,},
					[2]= {name="防御药水(大)",chance=0.195,max=1,min=1,sid=39027,type=0,},
					[3]= {name="攻击药水(大)",chance=0.195,max=1,min=1,sid=39038,type=0,},
					[4]= {name="背包扩展符",chance=0.12,max=1,min=1,sid=40068,type=0,},
					[5]= {name="强化保护符",chance=0.17,max=1,min=1,sid=40012,type=0,},
					[6]= {name="清洗丹",chance=0.15,max=1,min=1,sid=40041,type=0,},
					[7]= {name="鉴定锁",chance=0.07,max=1,min=1,sid=40042,type=0,},
				},
			type=1,
		},
	[63]= {
			id=63,
			name="大boss掉落常用杂品",
			elems= {
					[1]= {name="鉴定图鉴",chance=0.16,max=1,min=1,sid=40060,type=0,},
					[2]= {name="祝福油",chance=0.12,max=1,min=1,sid=30018,type=0,},
					[3]= {name="百年人参",chance=0.03,max=1,min=1,sid=39015,type=0,},
					[4]= {name="百年雪莲",chance=0.03,max=1,min=1,sid=39019,type=0,},
					[5]= {name="千年玄参",chance=0.06,max=1,min=1,sid=39016,type=0,},
					[6]= {name="千年冰莲",chance=0.06,max=1,min=1,sid=39020,type=0,},
					[7]= {name="攻击药水(小)",chance=0.04,max=1,min=1,sid=39023,type=0,},
					[8]= {name="防御药水(小)",chance=0.04,max=1,min=1,sid=39025,type=0,},
					[9]= {name="攻击药水(中)",chance=0.05,max=1,min=1,sid=39024,type=0,},
					[10]= {name="防御药水(中)",chance=0.05,max=1,min=1,sid=39026,type=0,},
					[11]= {name="诛魔神石",chance=0.06,max=1,min=1,sid=40052,type=0,},
					[12]= {name="宠物项圈",chance=0.1,max=1,min=1,sid=40053,type=0,},
					[13]= {name="副本神符",chance=0.06,max=1,min=1,sid=40051,type=0,},
					[14]= {name="红玫瑰",chance=0.08,max=1,min=1,sid=39029,type=0,},
					[15]= {name="经验灵符",chance=0.06,max=1,min=1,sid=30064,type=0,},
				},
			type=1,
		},
	[64]= {
			id=64,
			name="大boss掉落稀有杂品",
			elems= {
					[1]= {name="战神油",chance=0.1,max=1,min=1,sid=30017,type=0,},
					[2]= {name="防御药水(大)",chance=0.175,max=1,min=1,sid=39027,type=0,},
					[3]= {name="攻击药水(大)",chance=0.175,max=1,min=1,sid=39038,type=0,},
					[4]= {name="背包扩展符",chance=0.14,max=1,min=1,sid=40068,type=0,},
					[5]= {name="强化保护符",chance=0.17,max=1,min=1,sid=40012,type=0,},
					[6]= {name="清洗丹",chance=0.15,max=1,min=1,sid=40041,type=0,},
					[7]= {name="鉴定锁",chance=0.09,max=1,min=1,sid=40042,type=0,},
				},
			type=1,
		},
	[65]= {
			id=65,
			name="0-10级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=3,datay=12,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[66]= {
			id=66,
			name="10-20级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=13,datay=29,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[67]= {
			id=67,
			name="20-25级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=31,datay=40,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[68]= {
			id=68,
			name="25-30级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=42,datay=53,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[69]= {
			id=69,
			name="30-35级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=56,datay=69,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[70]= {
			id=70,
			name="35-40级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=72,datay=250,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[71]= {
			id=71,
			name="40-45级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=288,datay=501,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[72]= {
			id=72,
			name="45-50级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=575,datay=1000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[73]= {
			id=73,
			name="50-55级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=1148,datay=1995,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[74]= {
			id=74,
			name="55-60级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=2100,datay=3980,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[75]= {
			id=75,
			name="60-65级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=4000,datay=4000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[76]= {
			id=76,
			name="65-70级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=4000,datay=4000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[77]= {
			id=77,
			name="70-75级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=4000,datay=4000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[78]= {
			id=78,
			name="75-80级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=4000,datay=4000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[79]= {
			id=79,
			name="最高金币",
			elems= {
					[1]= {name="金币",chance=1,datax=2000,datay=2000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[80]= {
			id=80,
			name="灵石",
			elems= {
					[1]= {name="一级灵石",chance=0.4791,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0.3352,max=1,min=1,sid=40001,type=0,},
					[3]= {name="三级灵石",chance=0.1548,max=1,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.0281,max=1,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.0028,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[81]= {
			id=81,
			name="荣誉",
			elems= {
					[1]= {name="10000荣誉",chance=0.0094,max=1,min=1,sid=30206,type=0,},
					[2]= {name="5000荣誉",chance=0.0617,max=1,min=1,sid=30207,type=0,},
					[3]= {name="3000荣誉",chance=0.3475,max=1,min=1,sid=30210,type=0,},
					[4]= {name="1000荣誉",chance=0.5814,max=1,min=1,sid=30208,type=0,},
				},
			type=1,
		},
	[82]= {
			id=82,
			name="锭",
			elems= {
					[1]= {name="大铜锭",chance=0.8755,max=1,min=1,sid=30033,type=0,},
					[2]= {name="大银锭",chance=0.0841,max=1,min=1,sid=30034,type=0,},
					[3]= {name="大金锭",chance=0.0404,max=1,min=1,sid=30062,type=0,},
				},
			type=1,
		},
	[83]= {
			id=83,
			name="种子",
			elems= {
					[1]= {name="红玫瑰",chance=0.1756,max=1,min=1,sid=39029,type=0,},
					[2]= {name="金钱果",chance=0.2344,max=1,min=1,sid=30049,type=0,},
					[3]= {name="奇异果",chance=0.15,max=1,min=1,sid=30048,type=0,},
					[4]= {name="血菩提",chance=0.44,max=1,min=1,sid=30047,type=0,},
				},
			type=1,
		},
	[84]= {
			id=84,
			name="40级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=250,datay=250,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[85]= {
			id=85,
			name="41级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=288,datay=288,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[86]= {
			id=86,
			name="42级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=331,datay=331,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[87]= {
			id=87,
			name="43级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=380,datay=380,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[88]= {
			id=88,
			name="44级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=436,datay=436,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[89]= {
			id=89,
			name="45级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=501,datay=501,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[90]= {
			id=90,
			name="46级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=575,datay=575,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[91]= {
			id=91,
			name="47级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=661,datay=661,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[92]= {
			id=92,
			name="48级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=758,datay=758,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[93]= {
			id=93,
			name="49级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=871,datay=871,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[94]= {
			id=94,
			name="50级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=1000,datay=1000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[95]= {
			id=95,
			name="51级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=1148,datay=1148,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[96]= {
			id=96,
			name="52级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=1318,datay=1318,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[97]= {
			id=97,
			name="53级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=1513,datay=1513,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[98]= {
			id=98,
			name="54级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=1738,datay=1738,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[99]= {
			id=99,
			name="55级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=1995,datay=1995,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[100]= {
			id=100,
			name="56级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=2100,datay=2100,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[101]= {
			id=101,
			name="57级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=2630,datay=2630,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[102]= {
			id=102,
			name="58级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=3019,datay=3019,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[103]= {
			id=103,
			name="59级怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=3467,datay=3467,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[104]= {
			id=104,
			name="60级以上怪金币",
			elems= {
					[1]= {name="金币",chance=1,datax=4000,datay=4000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[105]= {
			id=105,
			name="幻武碎片",
			elems= {
					[1]= {name="黄金雷锤碎片",chance=0.25,max=1,min=1,sid=30288,type=0,},
					[2]= {name="如意金箍棒碎片",chance=0.25,max=1,min=1,sid=30289,type=0,},
					[3]= {name="死神之镰碎片",chance=0.25,max=1,min=1,sid=30290,type=0,},
					[4]= {name="生花妙笔碎片",chance=0.25,max=1,min=1,sid=30291,type=0,},
				},
			type=1,
		},
	[106]= {
			id=106,
			name="0-10级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=107,type=1,},
				},
			max=0,
			type=0,
		},
	[107]= {
			id=107,
			elems= {
					[1]= {name="$超级药",chance=0.0512,max=1,min=1,sid=1,type=1,},
					[2]= {name="$10级装备",chance=0.03,max=1,min=1,sid=3,type=1,},
					[3]= {name="$0-10级怪金币",chance=0.15,max=1,min=1,sid=65,type=1,},
				},
			type=1,
		},
	[108]= {
			id=108,
			name="10-20级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=109,type=1,},
				},
			max=0,
			type=0,
		},
	[109]= {
			id=109,
			elems= {
					[1]= {name="$超级药",chance=0.1041,max=1,min=1,sid=1,type=1,},
					[2]= {name="$10级装备",chance=0.0152,max=1,min=1,sid=3,type=1,},
					[3]= {name="$20级装备",chance=0.0204,max=1,min=1,sid=4,type=1,},
					[4]= {name="$经验玉掉落",chance=0.005,max=1,min=1,sid=56,type=1,},
					[5]= {name="$10-20级怪金币",chance=0.15,max=1,min=1,sid=66,type=1,},
				},
			type=1,
		},
	[110]= {
			id=110,
			name="20-25级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=111,type=1,},
				},
			max=0,
			type=0,
		},
	[111]= {
			id=111,
			elems= {
					[1]= {name="$超级药",chance=0.0724,max=1,min=1,sid=1,type=1,},
					[2]= {name="$20级装备",chance=0.0232,max=1,min=1,sid=4,type=1,},
					[3]= {name="$25级武器",chance=0.0105,max=1,min=1,sid=5,type=1,},
					[4]= {name="$经验玉掉落",chance=0.005,max=1,min=1,sid=56,type=1,},
					[5]= {name="$20-25级怪金币",chance=0.15,max=1,min=1,sid=67,type=1,},
				},
			type=1,
		},
	[112]= {
			id=112,
			name="25-30级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=113,type=1,},
				},
			max=0,
			type=0,
		},
	[113]= {
			id=113,
			elems= {
					[1]= {name="$超级药",chance=0.0724,max=1,min=1,sid=1,type=1,},
					[2]= {name="$20级装备",chance=0.0112,max=1,min=1,sid=4,type=1,},
					[3]= {name="$25级武器",chance=0.0073,max=1,min=1,sid=5,type=1,},
					[4]= {name="$30级装备",chance=0.0152,max=1,min=1,sid=6,type=1,},
					[5]= {name="$经验玉掉落",chance=0.005,max=1,min=1,sid=56,type=1,},
					[6]= {name="$25-30级怪金币",chance=0.15,max=1,min=1,sid=68,type=1,},
				},
			type=1,
		},
	[114]= {
			id=114,
			name="30-35级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=115,type=1,},
				},
			max=0,
			type=0,
		},
	[115]= {
			id=115,
			elems= {
					[1]= {name="$超级药",chance=0.07,max=1,min=1,sid=1,type=1,},
					[2]= {name="$30级装备",chance=0.0132,max=1,min=1,sid=6,type=1,},
					[3]= {name="$35级散件",chance=0.01,max=1,min=1,sid=7,type=1,},
					[4]= {name="$45级散件",chance=0.005,max=1,min=1,sid=8,type=1,},
					[5]= {name="$40级套装",chance=0.0008,max=1,min=1,sid=17,type=1,},
					[6]= {name="$小怪掉落杂品",chance=0.02,max=1,min=1,sid=57,type=1,},
					[7]= {name="一级灵石",chance=0.0037,max=1,min=1,sid=40000,type=0,},
					[8]= {name="$30-35级怪金币",chance=0.15,max=1,min=1,sid=69,type=1,},
				},
			type=1,
		},
	[116]= {
			id=116,
			name="35-40级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=117,type=1,},
				},
			max=0,
			type=0,
		},
	[117]= {
			id=117,
			elems= {
					[1]= {name="$超级药",chance=0.0724,max=1,min=1,sid=1,type=1,},
					[2]= {name="$30级装备",chance=0.0042,max=1,min=1,sid=6,type=1,},
					[3]= {name="$35级散件",chance=0.0142,max=1,min=1,sid=7,type=1,},
					[4]= {name="$45级散件",chance=0.006,max=1,min=1,sid=8,type=1,},
					[5]= {name="$40级套装",chance=0.002,max=1,min=1,sid=17,type=1,},
					[6]= {name="$小怪掉落杂品",chance=0.02,max=1,min=1,sid=57,type=1,},
					[7]= {name="一级灵石",chance=0.0039,max=1,min=1,sid=40000,type=0,},
					[8]= {name="$35-40级怪金币",chance=0.15,max=1,min=1,sid=70,type=1,},
				},
			type=1,
		},
	[118]= {
			id=118,
			name="40-45级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=119,type=1,},
				},
			max=0,
			type=0,
		},
	[119]= {
			id=119,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$35级散件",chance=0.015,max=1,min=1,sid=7,type=1,},
					[3]= {name="$45级散件",chance=0.0075,max=1,min=1,sid=8,type=1,},
					[4]= {name="$40级套装",chance=0.0021,max=1,min=1,sid=17,type=1,},
					[5]= {name="$45级套装",chance=0.0001,max=1,min=1,sid=18,type=1,},
					[6]= {name="$小怪掉落杂品",chance=0.03,max=1,min=1,sid=57,type=1,},
					[7]= {name="一级灵石",chance=0.0041,max=1,min=1,sid=40000,type=0,},
					[8]= {name="$40-45级怪金币",chance=0.15,max=1,min=1,sid=71,type=1,},
				},
			type=1,
		},
	[120]= {
			id=120,
			name="45-50级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=121,type=1,},
				},
			max=0,
			type=0,
		},
	[121]= {
			id=121,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.0145,max=1,min=1,sid=8,type=1,},
					[3]= {name="$50级散件",chance=0.0065,max=1,min=1,sid=9,type=1,},
					[4]= {name="$40级套装",chance=0.003,max=1,min=1,sid=17,type=1,},
					[5]= {name="$45级套装",chance=0.0005,max=1,min=1,sid=18,type=1,},
					[6]= {name="$50级套装零件",chance=0.0001,max=1,min=1,sid=20,type=1,},
					[7]= {name="$40级勋章",chance=0.0003,max=1,min=1,sid=11,type=1,},
					[8]= {name="$小怪掉落杂品",chance=0.03,max=1,min=1,sid=57,type=1,},
					[9]= {name="一级灵石",chance=0.0043,max=1,min=1,sid=40000,type=0,},
					[10]= {name="$45-50级怪金币",chance=0.15,max=1,min=1,sid=72,type=1,},
				},
			type=1,
		},
	[122]= {
			id=122,
			name="50-55级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=123,type=1,},
				},
			max=0,
			type=0,
		},
	[123]= {
			id=123,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.0086,max=1,min=1,sid=8,type=1,},
					[3]= {name="$50级散件",chance=0.0075,max=1,min=1,sid=9,type=1,},
					[4]= {name="$55级散件",chance=0.0055,max=1,min=1,sid=10,type=1,},
					[5]= {name="$40级套装",chance=0.00204,max=1,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.0008,max=1,min=1,sid=18,type=1,},
					[7]= {name="$50级套装零件",chance=0.00015,max=1,min=1,sid=20,type=1,},
					[8]= {name="$55级套装零件",chance=5e-005,max=1,min=1,sid=22,type=1,},
					[9]= {name="$40级勋章",chance=0.0003,max=1,min=1,sid=11,type=1,},
					[10]= {name="$45级勋章",chance=0.0001,max=1,min=1,sid=12,type=1,},
					[11]= {name="$小怪掉落杂品",chance=0.032,max=1,min=1,sid=57,type=1,},
					[12]= {name="一级灵石",chance=0.0045,max=1,min=1,sid=40000,type=0,},
					[13]= {name="$50-55级怪金币",chance=0.15,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[124]= {
			id=124,
			name="55-60级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=125,type=1,},
				},
			max=0,
			type=0,
		},
	[125]= {
			id=125,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.0076,max=1,min=1,sid=8,type=1,},
					[3]= {name="$50级散件",chance=0.0077,max=1,min=1,sid=9,type=1,},
					[4]= {name="$55级散件",chance=0.0043,max=1,min=1,sid=10,type=1,},
					[5]= {name="$40级套装",chance=0.00254,max=1,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.00173,max=1,min=1,sid=18,type=1,},
					[7]= {name="$50级套装零件",chance=0.0001,max=1,min=1,sid=20,type=1,},
					[8]= {name="$55级套装零件",chance=6e-005,max=1,min=1,sid=22,type=1,},
					[9]= {name="$60级套装零件",chance=5e-005,max=1,min=1,sid=24,type=1,},
					[10]= {name="$40级勋章",chance=0.0001,max=1,min=1,sid=11,type=1,},
					[11]= {name="$45级勋章",chance=0.0002,max=1,min=1,sid=12,type=1,},
					[12]= {name="$50级勋章",chance=3e-005,max=1,min=1,sid=13,type=1,},
					[13]= {name="$小怪掉落杂品",chance=0.032,max=1,min=1,sid=57,type=1,},
					[14]= {name="一级灵石",chance=0.0047,max=1,min=1,sid=40000,type=0,},
					[15]= {name="$55-60级怪金币",chance=0.15,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[126]= {
			id=126,
			name="60-65级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=127,type=1,},
				},
			max=0,
			type=0,
		},
	[127]= {
			id=127,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.0076,max=1,min=1,sid=8,type=1,},
					[3]= {name="$50级散件",chance=0.0087,max=1,min=1,sid=9,type=1,},
					[4]= {name="$55级散件",chance=0.0053,max=1,min=1,sid=10,type=1,},
					[5]= {name="$40级套装",chance=0.0026,max=1,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.0009,max=1,min=1,sid=18,type=1,},
					[7]= {name="$50级套装零件",chance=0.0003,max=1,min=1,sid=20,type=1,},
					[8]= {name="$55级套装零件",chance=6e-005,max=1,min=1,sid=22,type=1,},
					[9]= {name="$60级套装零件",chance=5e-005,max=1,min=1,sid=24,type=1,},
					[10]= {name="$40级勋章",chance=0.00015,max=1,min=1,sid=11,type=1,},
					[11]= {name="$45级勋章",chance=0.00013,max=1,min=1,sid=12,type=1,},
					[12]= {name="$50级勋章",chance=2e-005,max=1,min=1,sid=13,type=1,},
					[13]= {name="$小怪掉落杂品",chance=0.033,max=1,min=1,sid=57,type=1,},
					[14]= {name="一级灵石",chance=0.0047,max=1,min=1,sid=40000,type=0,},
					[15]= {name="二级灵石",chance=0.001,max=1,min=1,sid=40001,type=0,},
					[16]= {name="$60-65级怪金币",chance=0.125,max=1,min=1,sid=75,type=1,},
				},
			type=1,
		},
	[128]= {
			id=128,
			name="65-70级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=129,type=1,},
				},
			max=0,
			type=0,
		},
	[129]= {
			id=129,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.0076,max=1,min=1,sid=8,type=1,},
					[3]= {name="$50级散件",chance=0.0087,max=1,min=1,sid=9,type=1,},
					[4]= {name="$55级散件",chance=0.0053,max=1,min=1,sid=10,type=1,},
					[5]= {name="$40级套装",chance=0.0016,max=1,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.0009,max=1,min=1,sid=18,type=1,},
					[7]= {name="$50级套装零件",chance=0.0004,max=1,min=1,sid=20,type=1,},
					[8]= {name="$55级套装零件",chance=6e-005,max=1,min=1,sid=22,type=1,},
					[9]= {name="$60级套装零件",chance=5e-005,max=1,min=1,sid=24,type=1,},
					[10]= {name="$40级勋章",chance=5e-005,max=1,min=1,sid=11,type=1,},
					[11]= {name="$45级勋章",chance=8e-005,max=1,min=1,sid=12,type=1,},
					[12]= {name="$50级勋章",chance=4e-005,max=1,min=1,sid=13,type=1,},
					[13]= {name="$55级勋章",chance=2e-005,max=1,min=1,sid=14,type=1,},
					[14]= {name="$小怪掉落杂品",chance=0.033,max=1,min=1,sid=57,type=1,},
					[15]= {name="一级灵石",chance=0.0047,max=1,min=1,sid=40000,type=0,},
					[16]= {name="二级灵石",chance=0.001,max=1,min=1,sid=40001,type=0,},
					[17]= {name="$65-70级怪金币",chance=0.125,max=1,min=1,sid=76,type=1,},
				},
			type=1,
		},
	[130]= {
			id=130,
			name="70-75级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=131,type=1,},
				},
			max=0,
			type=0,
		},
	[131]= {
			id=131,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.096,max=1,min=1,sid=8,type=1,},
					[3]= {name="$50级散件",chance=0.0187,max=1,min=1,sid=9,type=1,},
					[4]= {name="$55级散件",chance=0.0073,max=1,min=1,sid=10,type=1,},
					[5]= {name="$40级套装",chance=0.15,max=1,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.001,max=1,min=1,sid=18,type=1,},
					[7]= {name="$50级套装零件",chance=0.0004,max=1,min=1,sid=20,type=1,},
					[8]= {name="$55级套装零件",chance=6e-005,max=1,min=1,sid=22,type=1,},
					[9]= {name="$60级套装零件",chance=5e-005,max=1,min=1,sid=24,type=1,},
					[10]= {name="$40级勋章",chance=5e-005,max=1,min=1,sid=11,type=1,},
					[11]= {name="$45级勋章",chance=8e-005,max=1,min=1,sid=12,type=1,},
					[12]= {name="$50级勋章",chance=4e-005,max=1,min=1,sid=13,type=1,},
					[13]= {name="$55级勋章",chance=2e-005,max=1,min=1,sid=14,type=1,},
					[14]= {name="$小怪掉落杂品",chance=0.033,max=1,min=1,sid=57,type=1,},
					[15]= {name="一级灵石",chance=0.0047,max=1,min=1,sid=40000,type=0,},
					[16]= {name="二级灵石",chance=0.001,max=1,min=1,sid=40001,type=0,},
					[17]= {name="附魔卷",chance=0.0001,max=1,min=1,sid=40148,type=0,},
					[18]= {name="$70-75级怪金币",chance=0.125,max=1,min=1,sid=77,type=1,},
				},
			type=1,
		},
	[132]= {
			id=132,
			name="75-80级怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=133,type=1,},
				},
			max=0,
			type=0,
		},
	[133]= {
			id=133,
			elems= {
					[1]= {name="$超级药",chance=0.0624,max=1,min=1,sid=1,type=1,},
					[2]= {name="$50级散件",chance=0.0097,max=1,min=1,sid=9,type=1,},
					[3]= {name="$55级散件",chance=0.0083,max=1,min=1,sid=10,type=1,},
					[4]= {name="$45级套装",chance=0.001,max=1,min=1,sid=18,type=1,},
					[5]= {name="$50级套装零件",chance=0.0004,max=1,min=1,sid=20,type=1,},
					[6]= {name="$55级套装零件",chance=0.00016,max=1,min=1,sid=22,type=1,},
					[7]= {name="$60级套装零件",chance=5e-005,max=1,min=1,sid=24,type=1,},
					[8]= {name="$40级勋章",chance=5e-005,max=1,min=1,sid=11,type=1,},
					[9]= {name="$45级勋章",chance=6e-005,max=1,min=1,sid=12,type=1,},
					[10]= {name="$50级勋章",chance=0.00013,max=1,min=1,sid=13,type=1,},
					[11]= {name="$55级勋章",chance=3e-005,max=1,min=1,sid=14,type=1,},
					[12]= {name="$小怪掉落杂品",chance=0.033,max=1,min=1,sid=57,type=1,},
					[13]= {name="一级灵石",chance=0.0047,max=1,min=1,sid=40000,type=0,},
					[14]= {name="二级灵石",chance=0.001,max=1,min=1,sid=40001,type=0,},
					[15]= {name="三级灵石",chance=0.0001,max=1,min=1,sid=40002,type=0,},
					[16]= {name="附魔卷",chance=0.0001,max=1,min=1,sid=40148,type=0,},
					[17]= {name="$75-80级怪金币",chance=0.125,max=1,min=1,sid=78,type=1,},
				},
			type=1,
		},
	[134]= {
			id=134,
			name="心魔",
			elems= {
					[1]= {name="金币",chance=1,datax=200,datay=1650,max=3,min=1,sid=2,type=0,},
					[2]= {name="投名状一",chance=1,max=1,min=1,sid=40100,type=0,},
				},
			max=0,
			type=0,
		},
	[135]= {
			id=135,
			name="情魔",
			elems= {
					[1]= {name="金币",chance=1,datax=200,datay=1650,max=3,min=1,sid=2,type=0,},
					[2]= {name="投名状二",chance=1,max=1,min=1,sid=40101,type=0,},
				},
			max=0,
			type=0,
		},
	[136]= {
			id=136,
			name="色魔",
			elems= {
					[1]= {name="金币",chance=1,datax=200,datay=1650,max=3,min=1,sid=2,type=0,},
					[2]= {name="投名状三",chance=1,max=1,min=1,sid=40102,type=0,},
				},
			max=0,
			type=0,
		},
	[137]= {
			id=137,
			name="劫魔",
			elems= {
					[1]= {name="金币",chance=1,datax=200,datay=1650,max=3,min=1,sid=2,type=0,},
					[2]= {name="投名状四",chance=1,max=1,min=1,sid=40103,type=0,},
				},
			max=0,
			type=0,
		},
	[138]= {
			id=138,
			name="欲魔",
			elems= {
					[1]= {name="金币",chance=1,datax=200,datay=1650,max=3,min=1,sid=2,type=0,},
					[2]= {name="投名状五",chance=1,max=1,min=1,sid=40104,type=0,},
				},
			max=0,
			type=0,
		},
	[139]= {
			id=139,
			name="王城精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=100,datay=300,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
					[2]= {name="$技能书",chance=0.0375,max=1,min=1,sid=42,type=1,},
					[3]= {name="$20级装备",chance=0.0685,max=1,min=1,sid=4,type=1,},
				},
			max=9,
			type=0,
		},
	[140]= {
			id=140,
			name="土城抗魔",
			elems= {
					[1]= {name="灵光碎片",chance=0.45,max=3,min=1,sid=40005,type=0,},
					[2]= {name="灵光碎片",chance=0.4,max=3,min=1,sid=40005,type=0,},
					[3]= {name="清洗碎片",chance=0.1354,max=1,min=1,sid=40006,type=0,},
				},
			max=0,
			type=0,
		},
	[141]= {
			id=141,
			name="暗之煞翼队长",
			elems= {
					[1]= {name="灵光碎片",chance=1,max=1,min=1,sid=40005,type=0,},
					[2]= {name="鉴定图鉴",chance=0.16,max=0,min=0,sid=40060,type=0,},
					[3]= {name="清洗丹",chance=0.12,max=0,min=0,sid=40041,type=0,},
					[4]= {name="清洗碎片",chance=0.264,max=1,min=1,sid=40006,type=0,},
				},
			max=0,
			type=0,
		},
	[142]= {
			id=142,
			name="矿洞精英",
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
					[2]= {name="$20级装备",chance=0.2756,max=1,min=1,sid=4,type=1,},
				},
			max=0,
			type=0,
		},
	[143]= {
			id=143,
			name="矿洞二层以上精英",
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
					[2]= {name="$20级装备",chance=0.0842,max=1,min=1,sid=4,type=1,},
				},
			max=0,
			type=0,
		},
	[144]= {
			id=144,
			name="虫洞精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=500,datay=500,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
					[2]= {name="$高级技能书",chance=0.0942,max=1,min=1,sid=44,type=1,},
					[3]= {name="$35级散件",chance=0.0528,max=1,min=1,sid=7,type=1,},
					[4]= {name="$20级装备",chance=0.0639,max=1,min=1,sid=4,type=1,},
				},
			max=9,
			type=0,
		},
	[145]= {
			id=145,
			name="猪妖洞精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=500,datay=500,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="祝福油",chance=0.0037,max=1,min=1,sid=30018,type=0,},
					[2]= {name="$35级散件",chance=0.3952,max=1,min=1,sid=7,type=1,},
					[3]= {name="$超级药",chance=1,max=2,min=1,sid=1,type=1,},
				},
			max=9,
			type=0,
		},
	[146]= {
			id=146,
			name="教皇寺庙精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=800,datay=800,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=2,min=1,sid=1,type=1,},
					[2]= {name="祝福油",chance=0.0048,max=1,min=1,sid=30018,type=0,},
					[3]= {name="$45级散件",chance=0.1158,max=1,min=1,sid=8,type=1,},
				},
			max=9,
			type=0,
		},
	[147]= {
			id=147,
			name="火龙洞精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=800,datay=800,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=6,min=4,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.1453,max=1,min=1,sid=8,type=1,},
					[3]= {name="$生死状一二",chance=1,max=1,min=1,sid=45,type=1,},
				},
			max=9,
			type=0,
		},
	[148]= {
			id=148,
			name="幽灵船精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=800,datay=1000,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=3,min=2,sid=1,type=1,},
					[2]= {name="$45级散件",chance=0.1425,max=1,min=1,sid=8,type=1,},
					[3]= {name="$生死状一二",chance=1,max=5,min=0,sid=45,type=1,},
				},
			max=9,
			type=0,
		},
	[149]= {
			id=149,
			name="蛮荒精英",
			elems= {
					[1]= {name="$超级药",chance=1,max=5,min=3,sid=1,type=1,},
					[2]= {name="金币",chance=1,datax=1000,datay=1200,max=8,min=5,sid=2,type=0,},
					[3]= {name="金币",chance=0.0677,datax=1000,datay=1000,max=10,min=6,sid=2,type=0,},
					[4]= {name="$45级散件",chance=0.2634,max=1,min=1,sid=8,type=1,},
					[5]= {name="$生死状一二",chance=1,max=3,min=2,sid=45,type=1,},
					[6]= {name="$50级套装零件",chance=0.01,max=1,min=1,sid=20,type=1,},
				},
			max=0,
			type=0,
		},
	[150]= {
			id=150,
			name="海底世界精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=4000,datay=4000,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="$超级药",chance=0.0334,max=1,min=1,sid=1,type=1,},
					[2]= {name="祝福油",chance=0.0233,max=1,min=1,sid=30018,type=0,},
					[3]= {chance=1,max=1,min=1,sid=151,type=1,},
					[4]= {name="鉴定图鉴",chance=0.02,max=1,min=1,sid=40060,type=0,},
				},
			max=9,
			type=0,
		},
	[151]= {
			id=151,
			elems= {
					[1]= {name="$55级散件",chance=0.0082,max=2,min=1,sid=10,type=1,},
					[2]= {name="$50级套装零件",chance=0.0253,max=1,min=1,sid=20,type=1,},
				},
			type=1,
		},
	[152]= {
			id=152,
			name="雪域精英",
			coplelem= {
					[1]= {name="金币",chance=0,datax=1000,datay=2000,max=9,min=9,sid=2,type=0,},
				},
			elems= {
					[1]= {name="$超级药",chance=0.0657,max=1,min=1,sid=1,type=1,},
					[2]= {name="鉴定图鉴",chance=0.01,max=1,min=1,sid=40060,type=0,},
					[3]= {name="强效太阳水",chance=0.04,max=1,min=1,sid=39009,type=0,},
					[4]= {name="祝福油",chance=0.0115,max=1,min=1,sid=30018,type=0,},
					[5]= {name="$50级套装零件",chance=0.0688,max=1,min=1,sid=20,type=1,},
					[6]= {name="$55级散件",chance=0.0547,max=1,min=1,sid=10,type=1,},
				},
			max=9,
			type=0,
		},
	[153]= {
			id=153,
			name="矿锄",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=154,type=1,},
				},
			max=0,
			type=0,
		},
	[154]= {
			id=154,
			elems= {
					[1]= {name="$新手鹤嘴锄",chance=1,max=1,min=1,sid=49,type=1,},
					[2]= {name="$老手鹤嘴锄",chance=1,max=1,min=1,sid=50,type=1,},
					[3]= {name="$大师鹤嘴锄",chance=1,max=1,min=1,sid=51,type=1,},
					[4]= {name="$纯银、宝石鹤嘴锄",chance=1,max=1,min=1,sid=52,type=1,},
					[5]= {name="$纯银、宝石鹤嘴锄",chance=1,max=1,min=1,sid=52,type=1,},
					[6]= {name="$黄金鹤嘴锄",chance=1,max=1,min=1,sid=53,type=1,},
					[7]= {name="$神的纯银鹤嘴锄",chance=1,max=1,min=1,sid=54,type=1,},
					[8]= {name="$神的黄金鹤嘴锄",chance=1,max=1,min=1,sid=55,type=1,},
				},
			type=1,
		},
	[155]= {
			id=155,
			name="飞天神猪",
			elems= {
					[1]= {name="梵天神符",chance=1,max=1,min=1,sid=40039,type=0,},
				},
			max=0,
			type=0,
		},
	[156]= {
			id=156,
			name="战神史册",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=157,type=1,},
				},
			max=0,
			type=0,
		},
	[157]= {
			id=157,
			elems= {
					[1]= {name="$超级药",chance=1,max=2,min=2,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[3]= {name="金币",chance=1,datax=300,datay=800,max=4,min=2,sid=2,type=0,},
				},
			type=1,
		},
	[158]= {
			id=158,
			name="20级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=2,min=1,sid=1,type=1,},
					[2]= {name="$初级技能书",chance=0.5,max=1,min=1,sid=43,type=1,},
					[3]= {chance=1,max=1,min=1,sid=159,type=1,},
					[4]= {name="$10-20级怪金币",chance=1,max=2,min=1,sid=66,type=1,},
				},
			max=0,
			type=0,
		},
	[159]= {
			id=159,
			elems= {
					[1]= {name="$10级装备",chance=0.4,max=1,min=1,sid=3,type=1,},
					[2]= {name="$20级装备",chance=0.6,max=1,min=1,sid=4,type=1,},
				},
			type=1,
		},
	[160]= {
			id=160,
			name="25级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=2,min=1,sid=1,type=1,},
					[2]= {chance=1,max=1,min=1,sid=161,type=1,},
					[3]= {name="$20-25级怪金币",chance=1,max=3,min=2,sid=67,type=1,},
				},
			max=0,
			type=0,
		},
	[161]= {
			id=161,
			elems= {
					[1]= {name="$10级装备",chance=0.3,max=1,min=1,sid=3,type=1,},
					[2]= {name="$20级装备",chance=0.5,max=1,min=1,sid=4,type=1,},
					[3]= {name="$25级武器",chance=0.2,max=1,min=1,sid=5,type=1,},
				},
			type=1,
		},
	[162]= {
			id=162,
			name="30级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=3,min=1,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=163,type=1,},
					[5]= {name="$25-30级怪金币",chance=1,max=3,min=2,sid=68,type=1,},
				},
			max=0,
			type=0,
		},
	[163]= {
			id=163,
			elems= {
					[1]= {name="$20级装备",chance=0.25,max=1,min=1,sid=4,type=1,},
					[2]= {name="$25级武器",chance=0.25,max=1,min=1,sid=5,type=1,},
					[3]= {name="$30级装备",chance=0.5,max=1,min=1,sid=6,type=1,},
				},
			type=1,
		},
	[164]= {
			id=164,
			name="35级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=3,min=2,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[3]= {chance=1,max=1,min=1,sid=165,type=1,},
					[4]= {name="$30-35级怪金币",chance=0.0008,max=3,min=2,sid=69,type=1,},
				},
			max=0,
			type=0,
		},
	[165]= {
			id=165,
			elems= {
					[1]= {name="$25级武器",chance=0.1,max=1,min=1,sid=5,type=1,},
					[2]= {name="$30级装备",chance=0.4,max=1,min=1,sid=6,type=1,},
					[3]= {name="$35级散件",chance=0.01,max=1,min=1,sid=7,type=1,},
					[4]= {name="$40级套装",chance=0.005,max=4,min=2,sid=17,type=1,},
					[5]= {name="$30级装备",chance=0.2,max=1,min=1,sid=6,type=1,},
					[6]= {name="$35级散件",chance=0.3,max=1,min=1,sid=7,type=1,},
					[7]= {name="$40级套装",chance=0.0042,max=1,min=1,sid=17,type=1,},
					[8]= {name="$45级散件",chance=0.0142,max=1,min=1,sid=8,type=1,},
				},
			type=1,
		},
	[166]= {
			id=166,
			name="40级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[3]= {name="$小精英怪掉落杂品",chance=0.006,max=1,min=1,sid=58,type=1,},
					[4]= {name="$35-40级怪金币",chance=0.002,max=3,min=2,sid=70,type=1,},
				},
			max=0,
			type=0,
		},
	[167]= {
			id=167,
			name="45级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=3,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=168,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.35,max=1,min=1,sid=58,type=1,},
					[6]= {name="$40-45级怪金币",chance=1,max=4,min=3,sid=71,type=1,},
				},
			max=0,
			type=0,
		},
	[168]= {
			id=168,
			elems= {
					[1]= {name="$35级散件",chance=0.23,max=1,min=1,sid=7,type=1,},
					[2]= {name="$45级散件",chance=0.3,max=1,min=1,sid=8,type=1,},
					[3]= {name="$50级散件",chance=0.0075,max=1,min=1,sid=9,type=1,},
					[4]= {name="$40级套装",chance=0.0021,max=1,min=1,sid=17,type=1,},
					[5]= {name="$45级套装",chance=0.0001,max=1,min=1,sid=18,type=1,},
					[6]= {name="$45级套装",chance=0.01,max=1,min=1,sid=18,type=1,},
					[7]= {name="$40级勋章",chance=0.03,max=1,min=1,sid=11,type=1,},
				},
			type=1,
		},
	[169]= {
			id=169,
			name="50级精英怪",
			elems= {
					[1]= {name="$超级药",chance=0.0145,max=5,min=3,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=0.0065,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=0.003,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=170,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.35,max=1,min=1,sid=58,type=1,},
					[6]= {name="$45-50级怪金币",chance=0.00274,max=5,min=4,sid=72,type=1,},
				},
			max=0,
			type=0,
		},
	[170]= {
			id=170,
			elems= {
					[1]= {name="$45级散件",chance=0.0005,max=1,min=1,sid=8,type=1,},
					[2]= {name="$50级套装零件",chance=0.0001,max=1,min=1,sid=20,type=1,},
					[3]= {name="$50级散件",chance=0.3,max=1,min=1,sid=9,type=1,},
					[4]= {name="$55级散件",chance=0.4,max=1,min=1,sid=10,type=1,},
					[5]= {name="$40级套装",chance=0.1,max=1,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.01,max=1,min=1,sid=18,type=1,},
					[7]= {name="$50级套装零件",chance=0.005,max=1,min=1,sid=20,type=1,},
					[8]= {name="$40级勋章",chance=0.0086,max=1,min=1,sid=11,type=1,},
					[9]= {name="$45级勋章",chance=0.0075,max=1,min=1,sid=12,type=1,},
					[10]= {name="$50级套装零件",chance=0.00015,max=1,min=1,sid=20,type=1,},
					[11]= {name="$55级套装零件",chance=5e-005,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[171]= {
			id=171,
			name="55级精英怪",
			elems= {
					[1]= {name="$超级药",chance=0.0008,max=5,min=3,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=172,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.0001,max=1,min=1,sid=58,type=1,},
					[6]= {name="$50-55级怪金币",chance=1,max=8,min=7,sid=73,type=1,},
				},
			max=0,
			type=0,
		},
	[172]= {
			id=172,
			elems= {
					[1]= {name="$45级散件",chance=0.143,max=1,min=1,sid=8,type=1,},
					[2]= {name="$50级散件",chance=0.28,max=1,min=1,sid=9,type=1,},
					[3]= {name="$55级散件",chance=0.42,max=1,min=1,sid=10,type=1,},
					[4]= {name="$40级套装",chance=0.08,max=1,min=1,sid=17,type=1,},
					[5]= {name="$45级套装",chance=0.0076,max=1,min=1,sid=18,type=1,},
					[6]= {name="$50级套装零件",chance=0.0077,max=1,min=1,sid=20,type=1,},
					[7]= {name="$55级套装零件",chance=0.0043,max=1,min=1,sid=22,type=1,},
					[8]= {name="$40级勋章",chance=0.00254,max=1,min=1,sid=11,type=1,},
					[9]= {name="$45级勋章",chance=0.00173,max=1,min=1,sid=12,type=1,},
					[10]= {name="$55级套装零件",chance=6e-005,max=1,min=1,sid=22,type=1,},
					[11]= {name="$60级套装零件",chance=5e-005,max=1,min=1,sid=24,type=1,},
				},
			type=1,
		},
	[173]= {
			id=173,
			name="60级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=5,min=3,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=174,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.35,max=2,min=1,sid=58,type=1,},
					[6]= {name="$55-60级怪金币",chance=1,max=8,min=7,sid=74,type=1,},
				},
			max=0,
			type=0,
		},
	[174]= {
			id=174,
			elems= {
					[1]= {name="$45级散件",chance=0.143,max=1,min=1,sid=8,type=1,},
					[2]= {name="$50级散件",chance=0.28,max=1,min=1,sid=9,type=1,},
					[3]= {name="$55级散件",chance=0.42,max=1,min=1,sid=10,type=1,},
					[4]= {name="$40级套装",chance=0.08,max=1,min=1,sid=17,type=1,},
					[5]= {name="$45级套装",chance=0.03,max=1,min=1,sid=18,type=1,},
					[6]= {name="$50级套装零件",chance=0.005,max=1,min=1,sid=20,type=1,},
					[7]= {name="$55级套装零件",chance=0.002,max=1,min=1,sid=22,type=1,},
					[8]= {name="$40级勋章",chance=0.03,max=1,min=1,sid=11,type=1,},
					[9]= {name="$45级勋章",chance=0.01,max=1,min=1,sid=12,type=1,},
				},
			type=1,
		},
	[175]= {
			id=175,
			name="65级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=5,min=3,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=176,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.35,max=3,min=2,sid=58,type=1,},
					[6]= {name="$60-65级怪金币",chance=1,max=9,min=9,sid=75,type=1,},
				},
			max=0,
			type=0,
		},
	[176]= {
			id=176,
			elems= {
					[1]= {name="$45级散件",chance=0.14,max=1,min=1,sid=8,type=1,},
					[2]= {name="$50级散件",chance=0.29,max=1,min=1,sid=9,type=1,},
					[3]= {name="$55级散件",chance=0.43,max=1,min=1,sid=10,type=1,},
					[4]= {name="$40级套装",chance=0.07,max=1,min=1,sid=17,type=1,},
					[5]= {name="$45级套装",chance=0.03,max=1,min=1,sid=18,type=1,},
					[6]= {name="$50级套装零件",chance=0.005,max=1,min=1,sid=20,type=1,},
					[7]= {name="$55级套装零件",chance=0.002,max=1,min=1,sid=22,type=1,},
					[8]= {name="$60级套装零件",chance=0.001,max=1,min=1,sid=24,type=1,},
					[9]= {name="$40级勋章",chance=0.02,max=1,min=1,sid=11,type=1,},
					[10]= {name="$45级勋章",chance=0.008,max=1,min=1,sid=12,type=1,},
					[11]= {name="$50级勋章",chance=0.004,max=1,min=1,sid=13,type=1,},
				},
			type=1,
		},
	[177]= {
			id=177,
			name="70级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=6,min=4,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=178,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.35,max=2,min=2,sid=58,type=1,},
					[6]= {name="附魔卷",chance=0.0001,max=1,min=1,sid=40148,type=0,},
					[7]= {name="$65-70级怪金币",chance=1,max=9,min=9,sid=76,type=1,},
				},
			max=0,
			type=0,
		},
	[178]= {
			id=178,
			elems= {
					[1]= {name="$45级散件",chance=0.14,max=1,min=1,sid=8,type=1,},
					[2]= {name="$50级散件",chance=0.29,max=1,min=1,sid=9,type=1,},
					[3]= {name="$55级散件",chance=0.43,max=1,min=1,sid=10,type=1,},
					[4]= {name="$40级套装",chance=0.07,max=1,min=1,sid=17,type=1,},
					[5]= {name="$45级套装",chance=0.03,max=1,min=1,sid=18,type=1,},
					[6]= {name="$50级套装零件",chance=0.005,max=1,min=1,sid=20,type=1,},
					[7]= {name="$55级套装零件",chance=0.002,max=1,min=1,sid=22,type=1,},
					[8]= {name="$60级套装零件",chance=0.001,max=1,min=1,sid=24,type=1,},
					[9]= {name="$40级勋章",chance=0.02,max=1,min=1,sid=11,type=1,},
					[10]= {name="$45级勋章",chance=0.008,max=1,min=1,sid=12,type=1,},
					[11]= {name="$50级勋章",chance=0.004,max=1,min=1,sid=13,type=1,},
				},
			type=1,
		},
	[179]= {
			id=179,
			name="75级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=180,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.35,max=2,min=2,sid=58,type=1,},
					[6]= {name="附魔卷",chance=0.0001,max=1,min=1,sid=40148,type=0,},
					[7]= {name="$70-75级怪金币",chance=1,max=9,min=9,sid=77,type=1,},
				},
			max=0,
			type=0,
		},
	[180]= {
			id=180,
			elems= {
					[1]= {name="$45级散件",chance=0.14,max=1,min=1,sid=8,type=1,},
					[2]= {name="$50级散件",chance=0.29,max=1,min=1,sid=9,type=1,},
					[3]= {name="$55级散件",chance=0.43,max=1,min=1,sid=10,type=1,},
					[4]= {name="$45级套装",chance=0.07,max=1,min=1,sid=18,type=1,},
					[5]= {name="$50级套装零件",chance=0.03,max=1,min=1,sid=20,type=1,},
					[6]= {name="$55级套装零件",chance=0.005,max=1,min=1,sid=22,type=1,},
					[7]= {name="$60级套装零件",chance=0.002,max=1,min=1,sid=24,type=1,},
					[8]= {name="$70级套装零件",chance=0.001,max=1,min=1,sid=26,type=1,},
					[9]= {name="$50级勋章",chance=0.02,max=1,min=1,sid=13,type=1,},
					[10]= {name="$55级勋章",chance=0.008,max=1,min=1,sid=14,type=1,},
					[11]= {name="$60级勋章",chance=0.004,max=1,min=1,sid=15,type=1,},
				},
			type=1,
		},
	[181]= {
			id=181,
			name="80级精英怪",
			elems= {
					[1]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
					[2]= {name="$经验玉掉落",chance=1,max=1,min=1,sid=56,type=1,},
					[3]= {name="强效太阳水",chance=1,max=2,min=1,sid=39009,type=0,},
					[4]= {chance=1,max=1,min=1,sid=182,type=1,},
					[5]= {name="$小精英怪掉落杂品",chance=0.35,max=3,min=2,sid=58,type=1,},
					[6]= {name="附魔卷",chance=0.0001,max=1,min=1,sid=40148,type=0,},
					[7]= {name="附魔强化符",chance=0.0001,max=0,min=0,sid=40149,type=0,},
					[8]= {name="$75-80级怪金币",chance=1,max=9,min=9,sid=78,type=1,},
				},
			max=0,
			type=0,
		},
	[182]= {
			id=182,
			elems= {
					[1]= {name="$45级散件",chance=0.14,max=1,min=1,sid=8,type=1,},
					[2]= {name="$50级散件",chance=0.29,max=1,min=1,sid=9,type=1,},
					[3]= {name="$55级散件",chance=0.43,max=1,min=1,sid=10,type=1,},
					[4]= {name="$45级套装",chance=0.07,max=1,min=1,sid=18,type=1,},
					[5]= {name="$50级套装零件",chance=0.03,max=1,min=1,sid=20,type=1,},
					[6]= {name="$55级套装零件",chance=0.005,max=1,min=1,sid=22,type=1,},
					[7]= {name="$60级套装零件",chance=0.002,max=1,min=1,sid=24,type=1,},
					[8]= {name="$70级套装零件",chance=0.001,max=1,min=1,sid=26,type=1,},
					[9]= {name="$55级勋章",chance=0.02,max=1,min=1,sid=14,type=1,},
					[10]= {name="$60级勋章",chance=0.008,max=1,min=1,sid=15,type=1,},
					[11]= {name="$70级勋章",chance=0.004,max=1,min=1,sid=16,type=1,},
				},
			type=1,
		},
	[183]= {
			id=183,
			name="妖月峡谷小怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=184,type=1,},
				},
			max=0,
			type=0,
		},
	[184]= {
			id=184,
			elems= {
					[1]= {name="$超级药",chance=0.1,max=1,min=1,sid=1,type=1,},
					[2]= {name="$30-35级怪金币",chance=0.12,max=1,min=1,sid=69,type=1,},
					[3]= {name="$技能书",chance=0.0433,max=1,min=1,sid=42,type=1,},
					[4]= {name="$小怪掉落杂品",chance=0.05,max=1,min=1,sid=57,type=1,},
					[5]= {name="$30级装备",chance=0.0201,max=1,min=1,sid=6,type=1,},
					[6]= {name="$35级散件",chance=0.0081,max=1,min=1,sid=7,type=1,},
				},
			type=1,
		},
	[185]= {
			id=185,
			name="妖月峡谷BOSS",
			coplelem= {
					[1]= {name="$30-35级怪金币",chance=0,max=9,min=9,sid=69,type=1,},
				},
			elems= {
					[1]= {name="行会资格证",chance=0.25,max=1,min=1,sid=40057,type=0,},
					[2]= {name="元宝",chance=1,datax=1000,datay=2000,max=1,min=1,sid=3,type=0,},
					[3]= {name="仙玉",chance=1,datax=100,datay=500,max=1,min=1,sid=4,type=0,},
					[4]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[5]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[6]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[7]= {chance=1,max=1,min=1,sid=661,type=1,},
					[8]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=9,
			type=0,
		},
	[186]= {
			id=186,
			elems= {
					[1]= {name="$45级散件",chance=0.13,max=1,min=1,sid=8,type=1,},
					[2]= {name="$30级装备",chance=0.42,max=1,min=1,sid=6,type=1,},
				},
			type=1,
		},
	[187]= {
			id=187,
			name="万年古墓小怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=188,type=1,},
				},
			max=0,
			type=0,
		},
	[188]= {
			id=188,
			elems= {
					[1]= {name="$超级药",chance=0.1,max=1,min=1,sid=1,type=1,},
					[2]= {name="$40-45级怪金币",chance=0.12,max=1,min=1,sid=71,type=1,},
					[3]= {name="$35级散件",chance=0.0118,max=1,min=1,sid=7,type=1,},
					[4]= {name="$小怪掉落杂品",chance=0.05,max=1,min=1,sid=57,type=1,},
				},
			type=1,
		},
	[189]= {
			id=189,
			name="万年古墓BOSS",
			coplelem= {
					[1]= {name="$40-45级怪金币",chance=0,max=9,min=9,sid=71,type=1,},
				},
			elems= {
					
					[2]= {name="元宝",chance=1,datax=10000,datay=20000,max=1,min=1,sid=3,type=0,},
					[3]= {name="仙玉",chance=1,datax=500,datay=1000,max=1,min=1,sid=4,type=0,},
					[4]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[5]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[6]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[7]= {chance=1,max=1,min=1,sid=661,type=1,},
					[8]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=9,
			type=0,
		},
	[190]= {
			id=190,
			name="赤月小怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=191,type=1,},
				},
			max=0,
			type=0,
		},
	[191]= {
			id=191,
			elems= {
					[1]= {name="$超级药",chance=0.1,max=1,min=1,sid=1,type=1,},
					[2]= {name="$40-45级怪金币",chance=0.12,max=1,min=1,sid=71,type=1,},
					[3]= {name="强效太阳水",chance=0.0759,max=1,min=1,sid=39009,type=0,},
				},
			type=1,
		},
	[192]= {
			id=192,
			name="赤月BOSS",
			elems= {
					[1]= {name="$超级药",chance=0.0042,max=2,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0.0142,max=2,min=1,sid=39009,type=0,},
					[3]= {name="$40-45级怪金币",chance=0.006,max=2,min=1,sid=71,type=1,},
				},
			max=0,
			type=0,
		},
	[193]= {
			id=193,
			name="宝矿洞窟怪",
			elems= {
					[1]= {name="宝矿鹤嘴锄",chance=1,max=1,min=1,sid=70174,type=0,},
					[2]= {name="黑铁",chance=0.8954,max=3,min=1,sid=40008,type=0,},
					[3]= {name="绿宝石",chance=0.3248,max=2,min=1,sid=40009,type=0,},
					[4]= {name="紫晶钻",chance=0.1615,max=1,min=1,sid=40010,type=0,},
					[5]= {name="神的纯银鹤嘴锄",chance=0.001,max=1,min=1,sid=70167,type=0,},
				},
			max=0,
			type=0,
		},
	[194]= {
			id=194,
			name="天地宝库小怪",
			elems= {
					[1]= {name="金币",chance=0.5,datax=150,datay=230,max=1,min=1,sid=2,type=0,},
				},
			max=0,
			type=0,
		},
	[195]= {
			id=195,
			name="天地宝库一号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=150,datay=350,max=99,min=99,sid=2,type=0,},
				},
			elems= {},
			max=99,
			type=0,
		},
	[196]= {
			id=196,
			name="天帝宝库二号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=220,datay=760,max=99,min=99,sid=2,type=0,},
				},
			elems= {},
			max=99,
			type=0,
		},
	[197]= {
			id=197,
			name="天帝宝库三号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=340,datay=900,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱一等",chance=0.01,max=1,min=1,sid=30250,type=0,},
				},
			max=99,
			type=0,
		},
	[198]= {
			id=198,
			name="天帝宝库四号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=570,datay=1500,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱二等",chance=0.01,max=1,min=1,sid=30251,type=0,},
				},
			max=99,
			type=0,
		},
	[199]= {
			id=199,
			name="天帝宝库五号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=600,datay=1700,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱三等",chance=0.01,max=1,min=1,sid=30252,type=0,},
				},
			max=99,
			type=0,
		},
	[200]= {
			id=200,
			name="天帝宝库六号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=700,datay=1700,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱四等",chance=0.01,max=1,min=1,sid=30253,type=0,},
				},
			max=99,
			type=0,
		},
	[201]= {
			id=201,
			name="天帝宝库七号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=750,datay=1700,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱五等",chance=0.01,max=1,min=1,sid=30254,type=0,},
				},
			max=99,
			type=0,
		},
	[202]= {
			id=202,
			name="天帝宝库八号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=800,datay=1700,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱六等",chance=0.01,max=1,min=1,sid=30255,type=0,},
				},
			max=99,
			type=0,
		},
	[203]= {
			id=203,
			name="天帝宝库九号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=900,datay=1850,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱七等",chance=0.01,max=1,min=1,sid=30256,type=0,},
				},
			max=99,
			type=0,
		},
	[204]= {
			id=204,
			name="天帝宝库十号BOSS",
			coplelem= {
					[1]= {name="金币",chance=0,datax=1000,datay=2050,max=99,min=99,sid=2,type=0,},
				},
			elems= {
					[1]= {name="天地宝箱八等",chance=0.01,max=1,min=1,sid=30257,type=0,},
				},
			max=99,
			type=0,
		},
	[205]= {
			id=205,
			name="水域龙都小怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=206,type=1,},
				},
			max=0,
			type=0,
		},
	[206]= {
			id=206,
			elems= {
					[1]= {name="$45-50级怪金币",chance=0.12,max=1,min=1,sid=72,type=1,},
					[2]= {name="鉴定图鉴",chance=0.0027,max=1,min=1,sid=40060,type=0,},
					[3]= {name="$35级散件",chance=0.012,max=1,min=1,sid=7,type=1,},
					[4]= {name="$45级散件",chance=0.003,max=1,min=1,sid=8,type=1,},
					[5]= {name="$小怪掉落杂品",chance=0.05,max=1,min=1,sid=57,type=1,},
				},
			type=1,
		},
	[207]= {
			id=207,
			name="水域龙都前3BOSS",
			coplelem= {
					[1]= {name="$45-50级怪金币",chance=0,max=9,min=9,sid=72,type=1,},
				},
			elems= {
					[1]= {name="$小精英怪掉落杂品",chance=1,max=5,min=3,sid=58,type=1,},
					[2]= {chance=1,max=1,min=1,sid=208,type=1,},
					[3]= {name="定海神珠",chance=1,max=1,min=1,sid=40124,type=0,},
				},
			max=9,
			type=0,
		},
	[208]= {
			id=208,
			elems= {
					[1]= {name="$35级散件",chance=0.012,max=1,min=1,sid=7,type=1,},
					[2]= {name="$45级散件",chance=0.003,max=1,min=1,sid=8,type=1,},
					[3]= {name="$40级套装",chance=0.001,max=1,min=1,sid=17,type=1,},
				},
			type=1,
		},
	[209]= {
			id=209,
			name="水域龙都龙女",
			elems= {
					[1]= {name="$超级药",chance=1,max=1,min=1,sid=1,type=1,},
					[2]= {name="$小精英怪掉落杂品",chance=0.0076,max=6,min=4,sid=58,type=1,},
					[3]= {chance=1,max=1,min=1,sid=210,type=1,},
					[4]= {name="定海神珠",chance=1,max=1,min=1,sid=40124,type=0,},
					[5]= {name="$45-50级怪金币",chance=0.0043,max=9,min=9,sid=72,type=1,},
				},
			max=0,
			type=0,
		},
	[210]= {
			id=210,
			elems= {
					[1]= {name="$35级散件",chance=0.012,max=1,min=1,sid=7,type=1,},
					[2]= {name="$45级散件",chance=0.003,max=1,min=1,sid=8,type=1,},
					[3]= {name="$40级套装",chance=0.001,max=1,min=1,sid=17,type=1,},
				},
			type=1,
		},
	[211]= {
			id=211,
			name="水域龙都龙王",
			elems= {
					[1]= {name="$45-50级怪金币",chance=0.0025,max=9,min=9,sid=72,type=1,},
					[2]= {name="$超级药",chance=0.0017,max=4,min=2,sid=1,type=1,},
					[3]= {name="$小精英怪掉落杂品",chance=0.0001,max=3,min=2,sid=58,type=1,},
					[4]= {chance=1,max=1,min=1,sid=212,type=1,},
					[5]= {chance=1,max=1,min=1,sid=213,type=1,},
				},
			max=0,
			type=0,
		},
	[212]= {
			id=212,
			elems= {
					[1]= {name="$50级套装零件",chance=0.4054,max=1,min=1,sid=20,type=1,},
					[2]= {name="$55级套装零件",chance=0.03,max=1,min=1,sid=22,type=1,},
					[3]= {name="$60级套装零件",chance=0.01,max=1,min=1,sid=24,type=1,},
				},
			type=1,
		},
	[213]= {
			id=213,
			elems= {
					[1]= {name="$40级套装",chance=0.5,max=1,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[214]= {
			id=214,
			name="水域龙都真龙王",
			coplelem= {
					[1]= {name="$45-50级怪金币",chance=0,max=9,min=9,sid=72,type=1,},
				},
			elems= {
					[1]= {chance=1,max=1,min=1,sid=215,type=1,},
					[2]= {name="$50级套装零件",chance=0.4054,max=1,min=1,sid=20,type=1,},
					[3]= {name="$超级药",chance=1,max=4,min=2,sid=1,type=1,},
				},
			max=9,
			type=0,
		},
	[215]= {
			id=215,
			elems= {
					[1]= {name="$40级套装",chance=0.5,max=1,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[216]= {
			id=216,
			name="绝望沙漠小怪",
			elems= {
					[1]= {name="$45-50级怪金币",chance=0.12,max=1,min=1,sid=72,type=1,},
					[2]= {name="$魂石碎片",chance=0.3,max=2,min=1,sid=28,type=1,},
				},
			max=0,
			type=0,
		},
	[217]= {
			id=217,
			name="绝望沙漠精英小怪",
			elems= {
					[1]= {name="$45-50级怪金币",chance=0.12,max=1,min=1,sid=72,type=1,},
					[2]= {chance=1,max=1,min=1,sid=218,type=1,},
				},
			max=0,
			type=0,
		},
	[218]= {
			id=218,
			elems= {
					[1]= {name="$魂石碎片",chance=0.2,max=3,min=1,sid=28,type=1,},
					[2]= {name="$一级魂石",chance=0.1,max=1,min=1,sid=29,type=1,},
				},
			type=1,
		},
	[219]= {
			id=219,
			name="沙漠门神",
			elems= {
					[1]= {name="$45-50级怪金币",chance=0.12,max=1,min=1,sid=72,type=1,},
					[2]= {chance=1,max=1,min=1,sid=220,type=1,},
				},
			max=0,
			type=0,
		},
	[220]= {
			id=220,
			elems= {
					[1]= {name="$魂石碎片",chance=0.1,max=3,min=1,sid=28,type=1,},
					[2]= {name="$一级魂石",chance=0.1,max=1,min=1,sid=29,type=1,},
					[3]= {name="$二级魂石",chance=0.05,max=1,min=1,sid=30,type=1,},
				},
			type=1,
		},
	[221]= {
			id=221,
			name="绝望沙漠BOSS",
			coplelem= {
					[1]= {name="$45-50级怪金币",chance=0,max=9,min=9,sid=72,type=1,},
				},
			elems= {
					[1]= {chance=1,max=1,min=1,sid=222,type=1,},
				},
			max=9,
			type=0,
		},
	[222]= {
			id=222,
			elems= {
					[1]= {name="$魂石碎片",chance=0.2,max=3,min=1,sid=28,type=1,},
					[2]= {name="$一级魂石",chance=0.1,max=2,min=1,sid=29,type=1,},
					[3]= {name="$二级魂石",chance=0.05,max=1,min=1,sid=30,type=1,},
					[4]= {name="$三级魂石",chance=0.02,max=1,min=1,sid=31,type=1,},
				},
			type=1,
		},
	[223]= {
			id=223,
			name="圣战、法神、道尊",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=25,min=25,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=6,min=3,sid=1,type=1,},
					[2]= {chance=1,max=1,min=1,sid=224,type=1,},
					[3]= {name="$60级套装零件",chance=0.05,max=2,min=1,sid=24,type=1,},
				},
			max=25,
			type=0,
		},
	[224]= {
			id=224,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=3,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.15,max=1,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[225]= {
			id=225,
			name="赤月魔尊",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=25,min=25,sid=74,type=1,},
				},
			elems= {
					[1]= {name="行会资格证",chance=0.25,max=1,min=1,sid=40057,type=0,},
					[2]= {name="元宝",chance=1,datax=1000,datay=2000,max=1,min=1,sid=3,type=0,},
					[3]= {name="仙玉",chance=1,datax=100,datay=600,max=1,min=1,sid=4,type=0,},
					[4]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=1,min=1,sid=40004,type=0,},
					[7]= {chance=1,max=1,min=1,sid=661,type=1,},
					[8]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=25,
			type=0,
		},
	[226]= {
			id=226,
			elems= {
					[1]= {name="$50级散件",chance=0.5,max=1,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.2,max=1,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[227]= {
			id=227,
			name="地狱结界怪",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=228,type=1,},
				},
			max=0,
			type=0,
		},
	[228]= {
			id=228,
			elems= {
					[1]= {name="$超级药",chance=0.08,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0.1,max=1,min=1,sid=39009,type=0,},
					[3]= {name="金币",chance=0.12,datax=2000,datay=2000,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[229]= {
			id=229,
			name="五行炼狱",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=230,type=1,},
				},
			max=0,
			type=0,
		},
	[230]= {
			id=230,
			elems= {
					[1]= {name="$超级药",chance=0.6455,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0.3545,max=1,min=1,sid=39009,type=0,},
				},
			type=1,
		},
	[231]= {
			id=231,
			name="魔神封印BOSS",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=25,min=25,sid=77,type=1,},
				},
			elems= {
					[1]= {chance=1,max=1,min=1,sid=232,type=1,},
					[2]= {name="$特殊戒指",chance=0.01,max=1,min=1,sid=27,type=1,},
					[3]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.4,max=2,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.3,max=1,min=1,sid=40004,type=0,},
					[6]= {chance=1,max=1,min=1,sid=233,type=1,},
					[7]= {name="$大boss掉落常用杂品",chance=1,max=9,min=6,sid=63,type=1,},
				},
			max=25,
			type=0,
		},
	[232]= {
			id=232,
			elems= {
					[1]= {name="$70级套装零件",chance=0.1686,max=1,min=1,sid=26,type=1,},
					[2]= {name="$60级套装零件",chance=0.2914,max=1,min=1,sid=24,type=1,},
					[3]= {name="$60级套装武器",chance=0.2155,max=1,min=1,sid=23,type=1,},
					[4]= {name="$55级套装零件",chance=0.3245,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[233]= {
			id=233,
			elems= {
					[1]= {name="$三级魂石",chance=0.24,max=2,min=1,sid=31,type=1,},
					[2]= {name="$四级魂石",chance=0.24,max=1,min=1,sid=32,type=1,},
				},
			type=1,
		},
	[234]= {
			id=234,
			name="水寨小怪",
			elems= {
					[1]= {name="$70-75级怪金币",chance=0.12,max=1,min=1,sid=77,type=1,},
				},
			max=0,
			type=0,
		},
	[235]= {
			id=235,
			name="水寨BOSS",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=25,min=25,sid=77,type=1,},
				},
			elems= {
					[1]= {name="$大boss掉落常用杂品",chance=1,max=5,min=3,sid=63,type=1,},
					[2]= {name="$灵石",chance=1,max=1,min=1,sid=80,type=1,},
					[3]= {chance=1,max=1,min=1,sid=236,type=1,},
					[4]= {chance=1,max=1,min=1,sid=237,type=1,},
				},
			max=25,
			type=0,
		},
	[236]= {
			id=236,
			elems= {
					[1]= {name="$60级套装零件",chance=0.15,max=1,min=1,sid=24,type=1,},
					[2]= {name="$55级套装武器",chance=0.3,max=1,min=1,sid=21,type=1,},
					[3]= {name="$55级套装零件",chance=0.55,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[237]= {
			id=237,
			elems= {
					[1]= {name="$60级套装零件",chance=0.05,max=1,min=1,sid=24,type=1,},
					[2]= {name="$55级套装武器",chance=0.15,max=1,min=1,sid=21,type=1,},
					[3]= {name="$55级套装零件",chance=0.3,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[238]= {
			id=238,
			name="高家店小怪",
			elems= {
					[1]= {name="$70-75级怪金币",chance=0.3241,max=1,min=1,sid=77,type=1,},
				},
			max=0,
			type=0,
		},
	[239]= {
			id=239,
			name="高家店BOSS",
			elems= {
					[1]= {name="$大boss掉落常用杂品",chance=0.3455,max=3,min=1,sid=63,type=1,},
					[2]= {name="$灵石",chance=0.154,max=1,min=1,sid=80,type=1,},
					[3]= {chance=1,max=1,min=1,sid=240,type=1,},
					[4]= {name="$70-75级怪金币",chance=1,max=24,min=24,sid=77,type=1,},
				},
			max=0,
			type=0,
		},
	[240]= {
			id=240,
			elems= {
					[1]= {name="$70级套装零件",chance=0.1686,max=1,min=1,sid=26,type=1,},
					[2]= {name="$60级套装零件",chance=0.2914,max=1,min=1,sid=24,type=1,},
					[3]= {name="$60级套装武器",chance=0.2155,max=1,min=1,sid=23,type=1,},
					[4]= {name="$55级套装零件",chance=0.3245,max=2,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[241]= {
			id=241,
			name="五指山小怪",
			elems= {
					[1]= {name="$70-75级怪金币",chance=0.3241,max=1,min=1,sid=77,type=1,},
				},
			max=0,
			type=0,
		},
	[242]= {
			id=242,
			name="五指山BOSS",
			elems= {
					[1]= {name="$大boss掉落常用杂品",chance=0.3455,max=3,min=1,sid=63,type=1,},
					[2]= {name="$灵石",chance=0.154,max=2,min=1,sid=80,type=1,},
					[3]= {chance=1,max=1,min=1,sid=243,type=1,},
					[4]= {name="$70-75级怪金币",chance=1,max=24,min=24,sid=77,type=1,},
				},
			max=0,
			type=0,
		},
	[243]= {
			id=243,
			elems= {
					[1]= {name="$70级套装零件",chance=0.1686,max=1,min=1,sid=26,type=1,},
					[2]= {name="$60级套装零件",chance=0.2914,max=1,min=1,sid=24,type=1,},
					[3]= {name="$60级套装武器",chance=0.2155,max=1,min=1,sid=23,type=1,},
					[4]= {name="$55级套装零件",chance=0.3245,max=2,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[244]= {
			id=244,
			name="五指山隐藏BOSS",
			elems= {
					[1]= {name="$大boss掉落稀有杂品",chance=1,max=3,min=1,sid=64,type=1,},
					[2]= {name="$灵石",chance=0.5,max=3,min=1,sid=80,type=1,},
					[3]= {chance=1,max=1,min=1,sid=245,type=1,},
					[4]= {name="$70-75级怪金币",chance=1,max=30,min=30,sid=77,type=1,},
				},
			max=0,
			type=0,
		},
	[245]= {
			id=245,
			elems= {
					[1]= {name="$70级套装零件",chance=0.1686,max=1,min=1,sid=26,type=1,},
					[2]= {name="$60级套装零件",chance=0.2914,max=1,min=1,sid=24,type=1,},
					[3]= {name="$60级套装武器",chance=0.2155,max=1,min=1,sid=23,type=1,},
					[4]= {name="$55级套装零件",chance=0.3245,max=2,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[246]= {
			id=246,
			name="龙影坛小怪",
			elems= {
					[1]= {name="$50-55级怪金币",chance=0.7651,max=5,min=2,sid=73,type=1,},
				},
			max=0,
			type=0,
		},
	[247]= {
			id=247,
			name="龙影坛BOSS",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=10,min=10,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$锭",chance=0.0411,max=2,min=1,sid=82,type=1,},
				},
			max=10,
			type=0,
		},
	[248]= {
			id=248,
			name="转生副本小怪",
			elems= {
					[1]= {name="小转生灵魄",chance=0.0147,max=1,min=1,sid=30094,type=0,},
				},
			max=0,
			type=0,
		},
	[249]= {
			id=249,
			name="火焰战将",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=64,min=64,sid=77,type=1,},
				},
			elems= {
					
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=2000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=3,min=2,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=5,min=4,sid=40004,type=0,},
					[6]= {name="初级灵石",chance=1,max=1,min=1,sid=41000,type=0,},
					[7]= {chance=0.05,max=1,min=1,sid=664,type=1,},
					[8]= {chance=1,max=1,min=1,sid=662,type=1,},
					[9]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
				},
			max=64,
			type=0,
		},
	[250]= {
			id=250,
			elems= {
					[1]= {name="$60级套装武器",chance=0.14,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.07,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.03,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[251]= {
			id=251,
			elems= {
					[1]= {name="召唤术(4级)",chance=0.01,max=1,min=1,sid=30366,type=0,},
					[2]= {name="召唤术(5级)",chance=0.01,max=1,min=1,sid=30367,type=0,},
					[3]= {name="毒药术(4级)",chance=0.01,max=1,min=1,sid=30100,type=0,},
				},
			type=1,
		},
	[252]= {
			id=252,
			name="傀儡妖人",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=2000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=3,min=2,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=5,min=4,sid=40004,type=0,},
					[6]= {name="初级灵石",chance=1,max=1,min=1,sid=41000,type=0,},
					[7]= {chance=0.2,max=1,min=1,sid=662,type=1,},
					[8]= {chance=1,max=1,min=1,sid=662,type=1,},
					[9]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
				},
			max=49,
			type=0,
		},
	[253]= {
			id=253,
			elems= {
					[1]= {name="$60级套装武器",chance=0.14,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.07,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.03,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[254]= {
			id=254,
			elems= {
					[1]= {name="召唤术(4级)",chance=0.01,max=1,min=1,sid=30366,type=0,},
					[2]= {name="召唤术(5级)",chance=0.01,max=1,min=1,sid=30367,type=0,},
					[3]= {name="毒药术(4级)",chance=0.01,max=1,min=1,sid=30100,type=0,},
				},
			type=1,
		},
	[255]= {
			id=255,
			name="雷火狼尸",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=64,min=64,sid=77,type=1,},
				},
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=2000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=3,min=2,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=5,min=4,sid=40004,type=0,},
					[6]= {name="初级灵石",chance=1,max=1,min=1,sid=41000,type=0,},
					[7]= {chance=0.1,max=1,min=1,sid=662,type=1,},
					[8]= {chance=1,max=1,min=1,sid=662,type=1,},
					[9]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
				},
			max=64,
			type=0,
		},
	[256]= {
			id=256,
			elems= {
					[1]= {name="$60级套装武器",chance=0.14,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.07,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.03,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[257]= {
			id=257,
			elems= {
					[1]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[2]= {name="附魔强化符",chance=0.01,max=1,min=1,sid=40149,type=0,},
				},
			type=1,
		},
	[258]= {
			id=258,
			name="死灵冰眼",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=64,min=64,sid=77,type=1,},
				},
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=2000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=3,min=2,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=5,min=4,sid=40004,type=0,},
					[5]= {name="初级灵石",chance=1,max=1,min=1,sid=41000,type=0,},
					[6]= {chance=0.1,max=1,min=1,sid=663,type=1,},
					[7]= {chance=1,max=1,min=1,sid=662,type=1,},
					[8]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
				},
			max=64,
			type=0,
		},
	[259]= {
			id=259,
			elems= {
					[1]= {name="$60级套装武器",chance=0.14,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.07,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.03,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[260]= {
			id=260,
			elems= {
					[1]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[2]= {name="附魔强化符",chance=0.01,max=1,min=1,sid=40149,type=0,},
				},
			type=1,
		},
	[261]= {
			id=261,
			name="火爆龙将",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=64,min=64,sid=77,type=1,},
				},
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=2000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=3,min=2,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=5,min=4,sid=40004,type=0,},
					[5]= {name="初级灵石",chance=1,max=1,min=1,sid=41000,type=0,},
					[6]= {chance=0.2,max=1,min=1,sid=663,type=1,},
					[7]= {chance=1,max=1,min=1,sid=662,type=1,},
					[8]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
				},
			max=64,
			type=0,
		},
	[262]= {
			id=262,
			elems= {
					[1]= {name="$60级套装武器",chance=0.14,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.07,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.07,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[263]= {
			id=263,
			elems= {
					[1]= {name="召唤术(4级)",chance=0.01,max=1,min=1,sid=30366,type=0,},
					[2]= {name="召唤术(5级)",chance=0.01,max=1,min=1,sid=30367,type=0,},
					[3]= {name="毒药术(4级)",chance=0.01,max=1,min=1,sid=30100,type=0,},
					[4]= {name="$特殊戒指",chance=0.01,max=1,min=1,sid=27,type=1,},
				},
			type=1,
		},
	[264]= {
			id=264,
			elems= {
					[1]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[2]= {name="附魔强化符",chance=0.02,max=1,min=1,sid=40149,type=0,},
					[3]= {name="极品附魔符",chance=0.01,max=1,min=1,sid=40150,type=0,},
				},
			type=1,
		},
	[265]= {
			id=265,
			name="无双赤鬼",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=64,min=64,sid=77,type=1,},
				},
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=2000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=3,min=2,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=5,min=4,sid=40004,type=0,},
					[5]= {name="初级灵石",chance=1,max=1,min=1,sid=41000,type=0,},
					[6]= {chance=0.3,max=1,min=1,sid=663,type=1,},
					[7]= {chance=1,max=1,min=1,sid=662,type=1,},
					[8]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
				},
			max=64,
			type=0,
		},
	[266]= {
			id=266,
			elems= {
					[1]= {name="$60级套装武器",chance=0.14,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.07,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.07,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[267]= {
			id=267,
			elems= {
					[1]= {name="召唤术(4级)",chance=0.01,max=1,min=1,sid=30366,type=0,},
					[2]= {name="召唤术(5级)",chance=0.01,max=1,min=1,sid=30367,type=0,},
					[3]= {name="毒药术(4级)",chance=0.01,max=1,min=1,sid=30100,type=0,},
					[4]= {name="$特殊戒指",chance=0.01,max=1,min=1,sid=27,type=1,},
				},
			type=1,
		},
	[268]= {
			id=268,
			elems= {
					[1]= {name="附魔卷",chance=0.05,max=1,min=1,sid=40148,type=0,},
					[2]= {name="附魔强化符",chance=0.03,max=1,min=1,sid=40149,type=0,},
					[3]= {name="极品附魔符",chance=0.02,max=1,min=1,sid=40150,type=0,},
				},
			type=1,
		},
	[269]= {
			id=269,
			name="勇士",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=270,type=1,},
				},
			max=0,
			type=0,
		},
	[270]= {
			id=270,
			elems= {
					[1]= {name="金币",chance=0.64,datax=200,datay=500,max=1,min=1,sid=2,type=0,},
					[2]= {name="1000荣誉",chance=0.3,max=3,min=1,sid=30208,type=0,},
					[3]= {name="5000荣誉",chance=0.05,max=2,min=1,sid=30207,type=0,},
					[4]= {name="10000荣誉",chance=0.01,max=1,min=1,sid=30206,type=0,},
				},
			type=1,
		},
	[271]= {
			id=271,
			name="角斗之王",
			elems= {
					[1]= {name="祝福油",chance=0.5,max=1,min=1,sid=30018,type=0,},
					[2]= {name="战神油",chance=0.06,max=1,min=1,sid=30017,type=0,},
					[3]= {name="攻击药水(中)",chance=0.1,max=1,min=1,sid=39024,type=0,},
					[4]= {name="清洗丹",chance=0.1,max=1,min=1,sid=40041,type=0,},
					[5]= {name="一级灵石",chance=0.01,max=1,min=1,sid=40000,type=0,},
					[6]= {name="二级灵石",chance=0.02,max=1,min=1,sid=40001,type=0,},
					[7]= {name="三级灵石",chance=0.07,max=1,min=1,sid=40002,type=0,},
					[8]= {name="强化保护符",chance=0.04,max=1,min=1,sid=40012,type=0,},
				},
			max=0,
			type=0,
		},
	[272]= {
			id=272,
			name="金牛座小怪",
			elems= {
					[1]= {name="金牛座卡",chance=0.25,max=1,min=1,sid=40023,type=0,},
				},
			max=0,
			type=0,
		},
	[273]= {
			id=273,
			name="巨蟹座小怪",
			elems= {
					[1]= {name="巨蟹座卡",chance=0.25,max=1,min=1,sid=40024,type=0,},
				},
			max=0,
			type=0,
		},
	[274]= {
			id=274,
			name="狮子座小怪",
			elems= {
					[1]= {name="狮子座卡",chance=0.25,max=1,min=1,sid=40025,type=0,},
				},
			max=0,
			type=0,
		},
	[275]= {
			id=275,
			name="双子座小怪",
			elems= {
					[1]= {name="双子座卡",chance=0.25,max=1,min=1,sid=40026,type=0,},
				},
			max=0,
			type=0,
		},
	[276]= {
			id=276,
			name="摩羯座小怪",
			elems= {
					[1]= {name="摩羯座卡",chance=0.25,max=1,min=1,sid=40027,type=0,},
				},
			max=0,
			type=0,
		},
	[277]= {
			id=277,
			name="射手座小怪",
			elems= {
					[1]= {name="射手座卡",chance=0.25,max=1,min=1,sid=40028,type=0,},
				},
			max=0,
			type=0,
		},
	[278]= {
			id=278,
			name="双鱼座小怪",
			elems= {
					[1]= {name="双鱼座卡",chance=0.25,max=1,min=1,sid=40029,type=0,},
				},
			max=0,
			type=0,
		},
	[279]= {
			id=279,
			name="水瓶座小怪",
			elems= {
					[1]= {name="水瓶座卡",chance=0.25,max=1,min=1,sid=40030,type=0,},
				},
			max=0,
			type=0,
		},
	[280]= {
			id=280,
			name="天秤座小怪",
			elems= {
					[1]= {name="天秤座卡",chance=0.25,max=1,min=1,sid=40031,type=0,},
				},
			max=0,
			type=0,
		},
	[281]= {
			id=281,
			name="天蝎座小怪",
			elems= {
					[1]= {name="天蝎座卡",chance=0.01,max=1,min=1,sid=40032,type=0,},
				},
			max=0,
			type=0,
		},
	[282]= {
			id=282,
			name="白羊座小怪",
			elems= {
					[1]= {name="白羊座卡",chance=0.01,max=1,min=1,sid=40033,type=0,},
				},
			max=0,
			type=0,
		},
	[283]= {
			id=283,
			name="处女座小怪",
			coplelem= {
					[1]= {name="处女座卡",chance=0,max=1,min=1,sid=40034,type=0,},
				},
			elems= {},
			max=1,
			type=0,
		},
	[284]= {
			id=284,
			name="烈火宫",
			elems= {
					[1]= {name="金币",chance=1,datax=120,datay=120,max=1,min=1,sid=2,type=0,},
				},
			max=0,
			type=0,
		},
	[285]= {
			id=285,
			name="九天冰宫一层掉落",
			elems= {
					[1]= {name="$中boss掉落常用杂品",chance=1,max=3,min=1,sid=61,type=1,},
					[2]= {chance=1,max=1,min=1,sid=286,type=1,},
					[3]= {chance=1,max=1,min=1,sid=287,type=1,},
					[4]= {chance=1,max=1,min=1,sid=288,type=1,},
					[5]= {name="五级灵石",chance=0.05,max=1,min=1,sid=40004,type=0,},
					[6]= {name="$60-65级怪金币",chance=0.0145,max=25,min=25,sid=75,type=1,},
				},
			max=0,
			type=0,
		},
	[286]= {
			id=286,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
					[3]= {name="$45级套装",chance=0.0075,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[287]= {
			id=287,
			elems= {
					[1]= {name="$50级套装零件",chance=0.1021,max=1,min=1,sid=20,type=1,},
					[2]= {name="$45级套装",chance=0.1001,max=1,min=1,sid=18,type=1,},
					[3]= {name="$55级套装零件",chance=0.05,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[288]= {
			id=288,
			elems= {
					[1]= {name="三级灵石",chance=0.3,max=2,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.2,max=1,min=1,sid=40003,type=0,},
				},
			type=1,
		},
	[289]= {
			id=289,
			name="九天冰宫二层掉落",
			elems= {
					[1]= {name="$中boss掉落常用杂品",chance=0.0065,max=4,min=2,sid=61,type=1,},
					[2]= {chance=1,max=1,min=1,sid=290,type=1,},
					[3]= {chance=1,max=1,min=1,sid=291,type=1,},
					[4]= {chance=1,max=1,min=1,sid=292,type=1,},
					[5]= {name="五级灵石",chance=0.09,max=1,min=1,sid=40004,type=0,},
					[6]= {name="$65-70级怪金币",chance=0.0075,max=25,min=25,sid=76,type=1,},
				},
			max=0,
			type=0,
		},
	[290]= {
			id=290,
			elems= {
					[1]= {name="$50级散件",chance=0.203,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.2005,max=2,min=1,sid=10,type=1,},
					[3]= {name="$50级套装零件",chance=0.0101,max=1,min=1,sid=20,type=1,},
					[4]= {name="$45级套装",chance=0.1,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[291]= {
			id=291,
			elems= {
					[1]= {name="$50级套装零件",chance=0.1,max=1,min=1,sid=20,type=1,},
					[2]= {name="$55级套装零件",chance=0.1,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[292]= {
			id=292,
			elems= {
					[1]= {name="三级灵石",chance=0.5,max=2,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.4,max=1,min=1,sid=40003,type=0,},
				},
			type=1,
		},
	[293]= {
			id=293,
			name="九天冰宫三层掉落",
			elems= {
					[1]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[2]= {chance=1,max=1,min=1,sid=294,type=1,},
					[3]= {chance=1,max=1,min=1,sid=295,type=1,},
					[4]= {chance=1,max=1,min=1,sid=296,type=1,},
					[5]= {name="五级灵石",chance=0.14,max=1,min=1,sid=40004,type=0,},
					[6]= {name="$65-70级怪金币",chance=0.0076,max=25,min=25,sid=76,type=1,},
				},
			max=0,
			type=0,
		},
	[294]= {
			id=294,
			elems= {
					[1]= {name="$50级散件",chance=0.0027,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.0008,max=2,min=1,sid=10,type=1,},
					[3]= {name="$50级套装零件",chance=0.0002,max=1,min=1,sid=20,type=1,},
					[4]= {name="$55级套装零件",chance=0.0001,max=1,min=1,sid=22,type=1,},
					[5]= {name="$45级套装",chance=0.1,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[295]= {
			id=295,
			elems= {
					[1]= {name="$50级套装零件",chance=0.3,max=1,min=1,sid=20,type=1,},
					[2]= {name="$55级套装零件",chance=0.3,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[296]= {
			id=296,
			elems= {
					[1]= {name="三级灵石",chance=0.3,max=2,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.3,max=1,min=1,sid=40003,type=0,},
				},
			type=1,
		},
	[297]= {
			id=297,
			name="狩猎场小怪",
			elems= {
					[1]= {name="1000荣誉",chance=0.0077,max=1,min=1,sid=30208,type=0,},
				},
			max=0,
			type=0,
		},
	[298]= {
			id=298,
			name="狩猎场BOSS",
			coplelem= {
					[1]= {name="$60-65级怪金币",chance=0,max=15,min=15,sid=75,type=1,},
				},
			elems= {
					[1]= {chance=1,max=1,min=1,sid=299,type=1,},
					[2]= {name="5倍经验神符",chance=0.0017,max=1,min=1,sid=30005,type=0,},
					[3]= {name="$荣誉",chance=0.1,max=1,min=1,sid=81,type=1,},
					[4]= {chance=1,max=1,min=1,sid=300,type=1,},
					[5]= {name="五级灵石",chance=1,max=1,min=1,sid=40004,type=0,},
				},
			max=15,
			type=0,
		},
	[299]= {
			id=299,
			elems= {
					[1]= {name="$45级散件",chance=0.2043,max=2,min=1,sid=8,type=1,},
					[2]= {name="$50级散件",chance=0.2525,max=2,min=1,sid=9,type=1,},
				},
			type=1,
		},
	[300]= {
			id=300,
			elems= {
					[1]= {name="$50级套装零件",chance=0.1,max=1,min=1,sid=20,type=1,},
					[2]= {name="$55级套装零件",chance=0.05,max=1,min=1,sid=22,type=1,},
					[3]= {name="$60级套装零件",chance=0.03,max=1,min=1,sid=24,type=1,},
				},
			type=1,
		},
	[301]= {
			id=301,
			name="英雄城守卫军小怪",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=5,min=5,sid=73,type=1,},
				},
			elems= {
					[1]= {name="百万经验灵符",chance=0.0615,max=1,min=1,sid=30189,type=0,},
				},
			max=5,
			type=0,
		},
	[302]= {
			id=302,
			name="英雄城守卫军BOSS",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=25,min=25,sid=73,type=1,},
				},
			elems= {
					[1]= {name="红玫瑰",chance=1,max=5,min=2,sid=39029,type=0,},
					[2]= {name="百万经验灵符",chance=1,max=4,min=1,sid=30189,type=0,},
					[3]= {name="$荣誉",chance=1,max=5,min=1,sid=81,type=1,},
				},
			max=25,
			type=0,
		},
	[303]= {
			id=303,
			name="采花大盗小怪",
			elems= {
					[1]= {name="$种子",chance=0.7158,max=2,min=1,sid=83,type=1,},
					[2]= {name="催泪弹",chance=0.656,max=1,min=1,sid=30220,type=0,},
				},
			max=0,
			type=0,
		},
	[304]= {
			id=304,
			name="采花大盗BOSS",
			elems= {
					[1]= {name="$种子",chance=1,max=24,min=16,sid=83,type=1,},
					[2]= {name="百万经验灵符",chance=1,max=20,min=15,sid=30189,type=0,},
					[3]= {name="千万经验灵符",chance=1,max=3,min=1,sid=30191,type=0,},
					[4]= {chance=1,max=1,min=1,sid=305,type=1,},
					[5]= {name="$荣誉",chance=1,max=15,min=9,sid=81,type=1,},
					[6]= {name="荣誉徽印",chance=0.25,max=1,min=1,sid=30209,type=0,},
					[7]= {name="强化保护符",chance=1,max=2,min=2,sid=40012,type=0,},
					[8]= {name="宠物项圈",chance=1,max=10,min=3,sid=40053,type=0,},
					[9]= {name="三级灵石",chance=1,max=2,min=2,sid=40002,type=0,},
					[10]= {name="四级灵石",chance=1,max=1,min=1,sid=40003,type=0,},
					[11]= {name="五级灵石",chance=0.2011,max=1,min=1,sid=40004,type=0,},
				},
			max=0,
			type=0,
		},
	[305]= {
			id=305,
			elems= {
					[1]= {name="千万经验灵符",chance=0.75,max=6,min=2,sid=30191,type=0,},
					[2]= {name="一亿经验灵符",chance=0.25,max=1,min=1,sid=30192,type=0,},
				},
			type=1,
		},
	[306]= {
			id=306,
			name="荣誉将军",
			elems= {
					[1]= {name="元宝",chance=1,datax=500000,datay=1000000,max=1,min=1,sid=3,type=0,},
					[2]= {name="金蚕王",chance=1,max=10,min=5,sid=30059,type=0,},
					[3]= {name="15级魂石袋",chance=1,max=5,min=2,sid=30348,type=0,},
					[4]= {name="1元充值",chance=1,max=5,min=2,sid=101,type=0,},
					[5]= {chance=0.1,max=1,min=1,sid=697,type=1,},
					[6]= {name="突破蛋",chance=1,max=3,min=2,sid=5555,type=0,},
					
				},
			max=0,
			type=0,
		},
	[307]= {
			id=307,
			name="勋章怪物",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=308,type=1,},
				},
			max=0,
			type=0,
		},
	[308]= {
			id=308,
			elems= {
					[1]= {name="$70级勋章",chance=0.05,max=1,min=1,sid=16,type=1,},
					[2]= {name="$60级勋章",chance=0.1,max=1,min=1,sid=15,type=1,},
					[3]= {name="$55级勋章",chance=0.2,max=1,min=1,sid=14,type=1,},
					[4]= {name="$50级勋章",chance=0.35,max=1,min=1,sid=13,type=1,},
				},
			type=1,
		},
	[309]= {
			id=309,
			name="魂石怪物",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=310,type=1,},
				},
			max=0,
			type=0,
		},
	[310]= {
			id=310,
			elems= {
					[1]= {name="$三级魂石",chance=0.35,max=1,min=1,sid=31,type=1,},
					[2]= {name="$四级魂石",chance=0.2,max=1,min=1,sid=32,type=1,},
					[3]= {name="$五级魂石",chance=0.1,max=1,min=1,sid=33,type=1,},
					[4]= {name="$六级魂石",chance=0.05,max=1,min=1,sid=34,type=1,},
				},
			type=1,
		},
	[311]= {
			id=311,
			name="灵珠怪物",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=312,type=1,},
				},
			max=0,
			type=0,
		},
	[312]= {
			id=312,
			elems= {
					[1]= {name="三级灵石",chance=0.35,max=1,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.45,max=1,min=1,sid=40003,type=0,},
					[3]= {name="五级灵石",chance=0.05,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[313]= {
			id=313,
			name="秘珠怪物",
			elems= {
					[1]= {name="低级秘珠",chance=0.75,max=1,min=1,sid=60260,type=0,},
				},
			max=0,
			type=0,
		},
	[314]= {
			id=314,
			name="发财礼包1级",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=315,type=1,},
				},
			max=0,
			type=0,
		},
	[315]= {
			id=315,
			elems= {
					[1]= {name="宠物项圈",chance=0.2,max=3,min=1,sid=40053,type=0,},
					[2]= {name="$一级魂石",chance=0.1,max=3,min=1,sid=29,type=1,},
					[3]= {name="$二级魂石",chance=0.15,max=2,min=1,sid=30,type=1,},
					[4]= {name="鉴定图鉴",chance=0.1,max=4,min=2,sid=40060,type=0,},
					[5]= {name="鉴定锁",chance=0.1,max=2,min=1,sid=40042,type=0,},
					[6]= {name="清洗丹",chance=0.1,max=2,min=1,sid=40041,type=0,},
					[7]= {name="百万经验灵符",chance=0.25,max=1,min=1,sid=30189,type=0,},
				},
			type=1,
		},
	[316]= {
			id=316,
			name="发财礼包2级",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=317,type=1,},
				},
			max=0,
			type=0,
		},
	[317]= {
			id=317,
			elems= {
					[1]= {name="宠物项圈",chance=0.15,max=6,min=3,sid=40053,type=0,},
					[2]= {name="$一级魂石",chance=0.05,max=5,min=3,sid=29,type=1,},
					[3]= {name="$二级魂石",chance=0.15,max=3,min=1,sid=30,type=1,},
					[4]= {name="$三级魂石",chance=0.15,max=1,min=1,sid=31,type=1,},
					[5]= {name="鉴定图鉴",chance=0.05,max=10,min=5,sid=40060,type=0,},
					[6]= {name="鉴定锁",chance=0.1,max=3,min=2,sid=40042,type=0,},
					[7]= {name="清洗丹",chance=0.1,max=3,min=2,sid=40041,type=0,},
					[8]= {name="百万经验灵符",chance=0.1,max=3,min=1,sid=30189,type=0,},
					[9]= {name="千万经验灵符",chance=0.15,max=1,min=1,sid=30191,type=0,},
				},
			type=1,
		},
	[318]= {
			id=318,
			name="发财礼包3级",
			elems= {
					[1]= {chance=1,max=1,min=1,sid=319,type=1,},
				},
			max=0,
			type=0,
		},
	[319]= {
			id=319,
			elems= {
					[1]= {name="宠物项圈",chance=0.15,max=10,min=5,sid=40053,type=0,},
					[2]= {name="$二级魂石",chance=0.15,max=4,min=2,sid=30,type=1,},
					[3]= {name="$三级魂石",chance=0.15,max=2,min=1,sid=31,type=1,},
					[4]= {name="$四级魂石",chance=0.05,max=1,min=1,sid=32,type=1,},
					[5]= {name="鉴定图鉴",chance=0.05,max=12,min=6,sid=40060,type=0,},
					[6]= {name="鉴定锁",chance=0.1,max=4,min=2,sid=40042,type=0,},
					[7]= {name="清洗丹",chance=0.1,max=4,min=2,sid=40041,type=0,},
					[8]= {name="百万经验灵符",chance=0.1,max=7,min=3,sid=30189,type=0,},
					[9]= {name="千万经验灵符",chance=0.15,max=2,min=1,sid=30191,type=0,},
				},
			type=1,
		},
	[320]= {
			id=320,
			name="亢金龙残影",
			elems= {
					[1]= {name="百万经验灵符",chance=1,max=1,min=1,sid=30189,type=0,},
				},
			max=0,
			type=0,
		},
	[321]= {
			id=321,
			name="土城抗魔1",
			elems= {
					[1]= {name="灵光碎片",chance=0,max=1,min=1,sid=40005,strong=1,type=0,},
					[2]= {name="清洗碎片",chance=0,max=1,min=1,sid=40006,strong=1,type=0,},
					[3]= {name="鉴定图鉴",chance=0,max=1,min=1,sid=40060,strong=1,type=0,},
					[4]= {name="清洗丹",chance=0,max=1,min=1,sid=40041,strong=1,type=0,},
				},
			type=1,
		},
	[322]= {
			id=322,
			name="圣火争霸1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[323]= {
			id=323,
			name="采花大盗1",
			elems= {
					[1]= {name="一亿经验灵符",chance=0,max=1,min=1,sid=30192,strong=1,type=0,},
					[2]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,strong=1,type=0,},
					[3]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,strong=1,type=0,},
					[4]= {name="10000荣誉",chance=0,max=1,min=1,sid=30206,strong=1,type=0,},
					[5]= {name="荣誉徽印",chance=0,max=1,min=1,sid=30209,strong=1,type=0,},
					[6]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
					[7]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,strong=1,type=0,},
					[8]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,strong=1,type=0,},
					[9]= {name="奇异果",chance=0,max=1,min=1,sid=30048,strong=1,type=0,},
					[10]= {name="金钱果",chance=0,max=1,min=1,sid=30049,strong=1,type=0,},
					[11]= {name="血菩提",chance=0,max=1,min=1,sid=30047,strong=1,type=0,},
				},
			type=1,
		},
	[324]= {
			id=324,
			name="大富翁1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
					[3]= {name="仙玉",chance=0,max=1,min=1,sid=4,strong=1,type=0,},
					[4]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,strong=1,type=0,},
					[5]= {name="清洗丹",chance=0,max=1,min=1,sid=40041,strong=1,type=0,},
					[6]= {name="鉴定锁",chance=0,max=1,min=1,sid=40042,strong=1,type=0,},
					[7]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,strong=1,type=0,},
					[8]= {name="3级物攻魂石",chance=0,max=1,min=1,sid=10025,strong=1,type=0,},
					[9]= {name="3级魔攻魂石",chance=0,max=1,min=1,sid=10026,strong=1,type=0,},
					[10]= {name="3级道攻魂石",chance=0,max=1,min=1,sid=10027,strong=1,type=0,},
				},
			type=1,
		},
	[325]= {
			id=325,
			name="皇家守卫1",
			elems= {
					[1]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[326]= {
			id=326,
			name="行会争夺战1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[327]= {
			id=327,
			name="护花使者1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[328]= {
			id=328,
			name="熔火之心1",
			elems= {
					[1]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,strong=1,type=0,},
					[2]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,strong=1,type=0,},
					[3]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,strong=1,type=0,},
					[4]= {name="盘龙惊鸿",chance=0,max=1,min=1,sid=60090,strong=1,type=0,},
					[5]= {name="苍雷万里",chance=0,max=1,min=1,sid=60150,strong=1,type=0,},
					[6]= {name="阴阳鸣鸿",chance=0,max=1,min=1,sid=60030,strong=1,type=0,},
					[7]= {name="天龙神锢戒指",chance=0,max=1,min=1,sid=60213,strong=1,type=0,},
					[8]= {name="五法青云戒指",chance=0,max=1,min=1,sid=60220,strong=1,type=0,},
					[9]= {name="百鬼夜宴戒指",chance=0,max=1,min=1,sid=60206,strong=1,type=0,},
					[10]= {name="浮犀焰阳战甲(男)",chance=0,max=1,min=1,sid=60082,strong=1,type=0,},
					[11]= {name="雪蛊霜寒魔袍(男)",chance=0,max=1,min=1,sid=60142,strong=1,type=0,},
					[12]= {name="九霄残月道衣(男)",chance=0,max=1,min=1,sid=60022,strong=1,type=0,},
					[13]= {name="降魔引魂",chance=0,max=1,min=1,sid=60060,strong=1,type=0,},
					[14]= {name="朝夕百花",chance=0,max=1,min=1,sid=60000,strong=1,type=0,},
					[15]= {name="混元蚀日",chance=0,max=1,min=1,sid=60120,strong=1,type=0,},
					[16]= {name="星瀚幽路战甲(男)",chance=0,max=1,min=1,sid=60062,strong=1,type=0,},
					[17]= {name="碎寂震天魔袍(男)",chance=0,max=1,min=1,sid=60122,strong=1,type=0,},
					[18]= {name="八卦錾金道衣(男)",chance=0,max=1,min=1,sid=60002,strong=1,type=0,},
				},
			type=1,
		},
	[329]= {
			id=329,
			name="焚天星宫1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
					[3]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,strong=1,type=0,},
					[4]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,strong=1,type=0,},
					[5]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,strong=1,type=0,},
					[6]= {name="灵魂石",chance=0,max=1,min=1,sid=40011,strong=1,type=0,},
					[7]= {name="定身戒指",chance=0,max=1,min=1,sid=60231,strong=1,type=0,},
					[8]= {name="浮犀焰阳头盔",chance=0,max=1,min=1,sid=60081,strong=1,type=0,},
					[9]= {name="雪蛊霜寒头盔",chance=0,max=1,min=1,sid=60141,strong=1,type=0,},
					[10]= {name="雪蛊霜寒项链",chance=0,max=1,min=1,sid=60144,strong=1,type=0,},
					[11]= {name="九霄残月头盔",chance=0,max=1,min=1,sid=60021,strong=1,type=0,},
					[12]= {name="九霄残月项链",chance=0,max=1,min=1,sid=60024,strong=1,type=0,},
					[13]= {name="青虹北斗头盔",chance=0,max=1,min=1,sid=60091,strong=1,type=0,},
					[14]= {name="青虹北斗项链",chance=0,max=1,min=1,sid=60094,strong=1,type=0,},
				},
			type=1,
		},
	[330]= {
			id=330,
			name="经验水晶宫1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="战神晶魄",chance=0,max=1,min=1,sid=40015,strong=1,type=0,},
					[3]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
					[4]= {name="10倍经验神符",chance=0,max=1,min=1,sid=30055,strong=1,type=0,},
					[5]= {name="8倍经验神符",chance=0,max=1,min=1,sid=30004,strong=1,type=0,},
					[6]= {name="6倍经验神符",chance=0,max=1,min=1,sid=30054,strong=1,type=0,},
					[7]= {name="10倍经验神符",chance=0,max=1,min=1,sid=30055,strong=1,type=0,},
					[8]= {name="8倍经验神符",chance=0,max=1,min=1,sid=30004,strong=1,type=0,},
					[9]= {name="6倍经验神符",chance=0.5,max=1,min=1,sid=30054,strong=1,type=0,},
				},
			type=1,
		},
	[331]= {
			id=331,
			name="马拉松1",
			elems= {
					[1]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,strong=1,type=0,},
					[2]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[3]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[332]= {
			id=332,
			name="美女护送1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[333]= {
			id=333,
			name="十二星宫1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[334]= {
			id=334,
			name="英雄城守卫军1",
			elems= {
					[1]= {name="魔龙降世(7档)(10天)",chance=0,max=1,min=1,sid=80020,strong=1,type=0,},
					[2]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,strong=1,type=0,},
					[3]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,strong=1,type=0,},
					[4]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
					[5]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[335]= {
			id=335,
			name="攻城战1",
			elems= {
					[1]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
					[2]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[336]= {
			id=336,
			name="地牢探险1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[337]= {
			id=337,
			name="降妖除魔1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="荣誉",chance=0,max=1,min=1,sid=6,strong=1,type=0,},
					[3]= {name="灵魂石",chance=0,max=1,min=1,sid=40011,strong=1,type=0,},
					[4]= {name="6倍经验神符",chance=0,max=1,min=1,sid=30054,strong=1,type=0,},
				},
			type=1,
		},
	[338]= {
			id=338,
			name="城主膜拜1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[339]= {
			id=339,
			name="群雄逐鹿1",
			elems= {
					[1]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,strong=1,type=0,},
					[2]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,strong=1,type=0,},
					[3]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,strong=1,type=0,},
					[4]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,strong=1,type=0,},
					[5]= {name="凤凰翎",chance=0,max=1,min=1,sid=40077,strong=1,type=0,},
					[6]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[7]= {name="荣誉",chance=0,max=1,min=1,sid=6,strong=1,type=0,},
					[8]= {name="足迹晶魄",chance=0,max=1,min=1,sid=40016,strong=1,type=0,},
					[9]= {name="恶魔足迹(1阶)(7天)",chance=0,max=1,min=1,sid=83000,strong=1,type=0,},
				},
			type=1,
		},
	[340]= {
			id=340,
			name="勇士竞技场1",
			elems= {
					[1]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
					[2]= {name="荣誉",chance=0,max=1,min=1,sid=6,strong=1,type=0,},
					[3]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,strong=1,type=0,},
					[4]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,strong=1,type=0,},
					[5]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,strong=1,type=0,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,strong=1,type=0,},
					[7]= {name="经验玉(中)",chance=0,max=1,min=1,sid=30036,strong=1,type=0,},
					[8]= {name="强化保护符",chance=0,max=1,min=1,sid=40012,strong=1,type=0,},
				},
			type=1,
		},
	[341]= {
			id=341,
			name="称霸天下1",
			elems= {
					[1]= {name="元宝",chance=0,max=1,min=1,sid=3,strong=1,type=0,},
					[2]= {name="荣誉",chance=0,max=1,min=1,sid=6,strong=1,type=0,},
					[3]= {name="霸王戒指",chance=0,max=1,min=1,sid=70130,strong=1,type=0,},
				},
			type=1,
		},
	[342]= {
			id=342,
			name="祭魔结阵1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
					[3]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,strong=1,type=0,},
					[4]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,strong=1,type=0,},
					[5]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,strong=1,type=0,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,strong=1,type=0,},
				},
			type=1,
		},
	[343]= {
			id=343,
			name="荣誉神殿1",
			elems= {
					[1]= {name="如梦似幻(5档)(10天)",chance=0,max=1,min=1,sid=80018,strong=1,type=0,},
					[2]= {name="荣誉",chance=0,max=1,min=1,sid=6,strong=1,type=0,},
					[3]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[344]= {
			id=344,
			name="攻沙元宝奖励1",
			elems= {
					[1]= {name="元宝",chance=0,max=1,min=1,sid=3,strong=1,type=0,},
				},
			type=1,
		},
	[345]= {
			id=345,
			name="战队竞技1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[346]= {
			id=346,
			name="绝望峡谷1",
			elems= {
					[1]= {name="鉴定图鉴",chance=0,max=1,min=1,sid=40060,strong=1,type=0,},
					[2]= {name="帝王头盔",chance=0,max=1,min=1,sid=70072,strong=1,type=0,},
					[3]= {name="帝王项链",chance=0,max=1,min=1,sid=70203,strong=1,type=0,},
					[4]= {name="帝王护腕",chance=0,max=1,min=1,sid=70073,strong=1,type=0,},
					[5]= {name="帝王腰带",chance=0,max=1,min=1,sid=70204,strong=1,type=0,},
					[6]= {name="帝王战靴",chance=0,max=1,min=1,sid=70069,strong=1,type=0,},
					[7]= {name="帝王宝石",chance=0,max=1,min=1,sid=70075,strong=1,type=0,},
					[8]= {name="帝王戒指",chance=0,max=1,min=1,sid=70074,strong=1,type=0,},
					[9]= {name="火神头盔",chance=0,max=1,min=1,sid=70056,strong=1,type=0,},
					[10]= {name="火神腰带",chance=0,max=1,min=1,sid=70057,strong=1,type=0,},
					[11]= {name="火神魔袍(男)",chance=0,max=1,min=1,sid=70058,strong=1,type=0,},
					[12]= {name="火神魔袍(女)",chance=0,max=1,min=1,sid=70059,strong=1,type=0,},
					[13]= {name="火神手镯",chance=0,max=1,min=1,sid=70060,strong=1,type=0,},
					[14]= {name="火神宝石",chance=0,max=1,min=1,sid=70061,strong=1,type=0,},
					[15]= {name="海神头盔",chance=0,max=1,min=1,sid=70200,strong=1,type=0,},
					[16]= {name="海神项链",chance=0,max=1,min=1,sid=70063,strong=1,type=0,},
					[17]= {name="海神腰带",chance=0,max=1,min=1,sid=70062,strong=1,type=0,},
					[18]= {name="海神道鞋",chance=0,max=1,min=1,sid=70201,strong=1,type=0,},
					[19]= {name="海神宝石",chance=0,max=1,min=1,sid=70199,strong=1,type=0,},
					[20]= {name="海神戒指",chance=0,max=1,min=1,sid=70065,strong=1,type=0,},
				},
			type=1,
		},
	[347]= {
			id=347,
			name="龙影坛1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[348]= {
			id=348,
			name="贵族陵墓1",
			elems= {
					[1]= {name="鉴定图鉴",chance=0,max=1,min=1,sid=40060,strong=1,type=0,},
					[2]= {name="祝福油",chance=0,max=1,min=1,sid=30018,strong=1,type=0,},
					[3]= {name="圣魂斩",chance=0,max=1,min=1,sid=70055,strong=1,type=0,},
					[4]= {name="帝王战甲(男)",chance=0,max=1,min=1,sid=70070,strong=1,type=0,},
					[5]= {name="帝王战甲(女)",chance=0,max=1,min=1,sid=70071,strong=1,type=0,},
					[6]= {name="龙神杖",chance=0,max=1,min=1,sid=70184,strong=1,type=0,},
					[7]= {name="火神魔袍(男)",chance=0,max=1,min=1,sid=70058,strong=1,type=0,},
					[8]= {name="火神魔袍(女)",chance=0,max=1,min=1,sid=70059,strong=1,type=0,},
					[9]= {name="镇魔剑",chance=0,max=1,min=1,sid=70185,strong=1,type=0,},
					[10]= {name="海神道衣(男)",chance=0,max=1,min=1,sid=70066,strong=1,type=0,},
					[11]= {name="海神道衣(女)",chance=0,max=1,min=1,sid=70067,strong=1,type=0,},
					[12]= {name="晃金摘星",chance=0,max=1,min=1,sid=60070,strong=1,type=0,},
					[13]= {name="离情霜月项链",chance=0,max=1,min=1,sid=60074,strong=1,type=0,},
					[14]= {name="武圣勋章",chance=0,max=1,min=1,sid=70148,strong=1,type=0,},
					[15]= {name="飞星舞雪",chance=0,max=1,min=1,sid=60130,strong=1,type=0,},
					[16]= {name="夜灵啸日项链",chance=0,max=1,min=1,sid=60134,strong=1,type=0,},
					[17]= {name="法圣勋章",chance=0,max=1,min=1,sid=70157,strong=1,type=0,},
					[18]= {name="游龙戏凤",chance=0,max=1,min=1,sid=60010,strong=1,type=0,},
					[19]= {name="光华若木项链",chance=0,max=1,min=1,sid=60014,strong=1,type=0,},
					[20]= {name="道圣勋章",chance=0,max=1,min=1,sid=70139,strong=1,type=0,},
					[21]= {name="星瀚幽路头盔",chance=0,max=1,min=1,sid=60061,strong=1,type=0,},
					[22]= {name="星瀚幽路项链",chance=0,max=1,min=1,sid=60064,strong=1,type=0,},
					[23]= {name="星瀚幽路宝石",chance=0,max=1,min=1,sid=60066,strong=1,type=0,},
				},
			type=1,
		},
	[349]= {
			id=349,
			name="梦魇魔域1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[350]= {
			id=350,
			name="远古矿洞1",
			elems= {
					[1]= {name="黑铁",chance=0,max=1,min=1,sid=40008,strong=1,type=0,},
					[2]= {name="绿宝石",chance=0,max=1,min=1,sid=40009,strong=1,type=0,},
					[3]= {name="紫晶钻",chance=0,max=1,min=1,sid=40010,strong=1,type=0,},
					[4]= {name="铜矿",chance=0,max=1,min=1,sid=40018,strong=1,type=0,},
					[5]= {name="铁矿",chance=0,max=1,min=1,sid=40017,strong=1,type=0,},
					[6]= {name="银矿",chance=0,max=1,min=1,sid=40019,strong=1,type=0,},
					[7]= {name="金矿",chance=0,max=1,min=1,sid=40020,strong=1,type=0,},
					[8]= {name="钻石矿",chance=0,max=1,min=1,sid=40021,strong=1,type=0,},
				},
			type=1,
		},
	[351]= {
			id=351,
			name="皇室藏宝地1",
			elems= {
					[1]= {name="金币",chance=0,datax=1,max=1,min=1,sid=2,type=0,},
				},
			type=1,
		},
	[352]= {
			id=352,
			name="恶魔庇护所1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[353]= {
			id=353,
			name="湮灭沙漠1",
			elems= {
					[1]= {name="生命魂石碎片",chance=0,max=1,min=1,sid=30280,strong=1,type=0,},
					[2]= {name="魔法魂石碎片",chance=0,max=1,min=1,sid=30281,strong=1,type=0,},
					[3]= {name="物防魂石碎片",chance=0,max=1,min=1,sid=30282,strong=1,type=0,},
					[4]= {name="魔防魂石碎片",chance=0,max=1,min=1,sid=30283,strong=1,type=0,},
					[5]= {name="物攻魂石碎片",chance=0,max=1,min=1,sid=30284,strong=1,type=0,},
					[6]= {name="魔攻魂石碎片",chance=0,max=1,min=1,sid=30285,strong=1,type=0,},
					[7]= {name="道攻魂石碎片",chance=0,max=1,min=1,sid=30286,strong=1,type=0,},
					[8]= {name="1级生命魂石",chance=0,max=1,min=1,sid=10007,strong=1,type=0,},
					[9]= {name="1级魔法魂石",chance=0,max=1,min=1,sid=10008,strong=1,type=0,},
					[10]= {name="1级物防魂石",chance=0,max=1,min=1,sid=10009,strong=1,type=0,},
					[11]= {name="1级魔防魂石",chance=0,max=1,min=1,sid=10010,strong=1,type=0,},
					[12]= {name="1级物攻魂石",chance=0,max=1,min=1,sid=10011,strong=1,type=0,},
					[13]= {name="1级魔攻魂石",chance=0,max=1,min=1,sid=10012,strong=1,type=0,},
					[14]= {name="1级道攻魂石",chance=0,max=1,min=1,sid=10013,strong=1,type=0,},
					[15]= {name="2级生命魂石",chance=0,max=1,min=1,sid=10014,strong=1,type=0,},
					[16]= {name="2级魔法魂石",chance=0,max=1,min=1,sid=10015,strong=1,type=0,},
					[17]= {name="2级物防魂石",chance=0,max=1,min=1,sid=10016,strong=1,type=0,},
					[18]= {name="2级魔防魂石",chance=0,max=1,min=1,sid=10017,strong=1,type=0,},
					[19]= {name="2级物攻魂石",chance=0,max=1,min=1,sid=10018,strong=1,type=0,},
					[20]= {name="2级魔攻魂石",chance=0,max=1,min=1,sid=10019,strong=1,type=0,},
					[21]= {name="2级道攻魂石",chance=0,max=1,min=1,sid=10020,strong=1,type=0,},
				},
			type=1,
		},
	[354]= {
			id=354,
			name="寒晶海底1",
			elems= {
					[1]= {name="盘龙惊鸿",chance=0,max=1,min=1,sid=60090,strong=1,type=0,},
					[2]= {name="苍雷万里",chance=0,max=1,min=1,sid=60150,strong=1,type=0,},
					[3]= {name="阴阳鸣鸿",chance=0,max=1,min=1,sid=60030,strong=1,type=0,},
					[4]= {name="天龙神锢戒指",chance=0,max=1,min=1,sid=60213,strong=1,type=0,},
					[5]= {name="五法青云戒指",chance=0,max=1,min=1,sid=60220,strong=1,type=0,},
					[6]= {name="百鬼夜宴戒指",chance=0,max=1,min=1,sid=60206,strong=1,type=0,},
					[7]= {name="浮犀焰阳战甲(男)",chance=0,max=1,min=1,sid=60082,strong=1,type=0,},
					[8]= {name="雪蛊霜寒魔袍(男)",chance=0,max=1,min=1,sid=60142,strong=1,type=0,},
					[9]= {name="九霄残月道衣(男)",chance=0,max=1,min=1,sid=60022,strong=1,type=0,},
					[10]= {name="降魔引魂",chance=0,max=1,min=1,sid=60060,strong=1,type=0,},
					[11]= {name="朝夕百花",chance=0,max=1,min=1,sid=60000,strong=1,type=0,},
					[12]= {name="混元蚀日",chance=0,max=1,min=1,sid=60120,strong=1,type=0,},
					[13]= {name="星瀚幽路战甲(男)",chance=0,max=1,min=1,sid=60062,strong=1,type=0,},
					[14]= {name="碎寂震天魔袍(男)",chance=0,max=1,min=1,sid=60122,strong=1,type=0,},
					[15]= {name="八卦錾金道衣(男)",chance=0,max=1,min=1,sid=60002,strong=1,type=0,},
				},
			type=1,
		},
	[355]= {
			id=355,
			name="魔神印记1",
			elems= {
					[1]= {name="盘龙惊鸿",chance=0,max=1,min=1,sid=60090,strong=1,type=0,},
					[2]= {name="苍雷万里",chance=0,max=1,min=1,sid=60150,strong=1,type=0,},
					[3]= {name="阴阳鸣鸿",chance=0,max=1,min=1,sid=60030,strong=1,type=0,},
					[4]= {name="天龙神锢戒指",chance=0,max=1,min=1,sid=60213,strong=1,type=0,},
					[5]= {name="五法青云戒指",chance=0,max=1,min=1,sid=60220,strong=1,type=0,},
					[6]= {name="百鬼夜宴戒指",chance=0,max=1,min=1,sid=60206,strong=1,type=0,},
					[7]= {name="浮犀焰阳战甲(男)",chance=0,max=1,min=1,sid=60082,strong=1,type=0,},
					[8]= {name="雪蛊霜寒魔袍(男)",chance=0,max=1,min=1,sid=60142,strong=1,type=0,},
					[9]= {name="九霄残月道衣(男)",chance=0,max=1,min=1,sid=60022,strong=1,type=0,},
					[10]= {name="降魔引魂",chance=0,max=1,min=1,sid=60060,strong=1,type=0,},
					[11]= {name="朝夕百花",chance=0,max=1,min=1,sid=60000,strong=1,type=0,},
					[12]= {name="混元蚀日",chance=0,max=1,min=1,sid=60120,strong=1,type=0,},
					[13]= {name="星瀚幽路战甲(男)",chance=0,max=1,min=1,sid=60062,strong=1,type=0,},
					[14]= {name="碎寂震天魔袍(男)",chance=0,max=1,min=1,sid=60122,strong=1,type=0,},
					[15]= {name="八卦錾金道衣(男)",chance=0,max=1,min=1,sid=60002,strong=1,type=0,},
				},
			type=1,
		},
	[356]= {
			id=356,
			name="深渊结界1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[357]= {
			id=357,
			name="镇魔塔1",
			elems= {
					[1]= {name="秘境卷",chance=0,max=1,min=1,sid=40137,strong=1,type=0,},
					[2]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
					[3]= {name="翅晶石",chance=0,max=1,min=1,sid=40069,strong=1,type=0,},
					[4]= {name="天龙神锢宝石",chance=0,max=1,min=1,sid=60106,strong=1,type=0,},
					[5]= {name="五法青云宝石",chance=0,max=1,min=1,sid=60166,strong=1,type=0,},
					[6]= {name="百鬼夜宴宝石",chance=0,max=1,min=1,sid=60046,strong=1,type=0,},
					[7]= {name="天龙神锢腰带",chance=0,max=1,min=1,sid=60108,strong=1,type=0,},
					[8]= {name="五法青云腰带",chance=0,max=1,min=1,sid=60168,strong=1,type=0,},
					[9]= {name="百鬼夜宴腰带",chance=0,max=1,min=1,sid=60048,strong=1,type=0,},
				},
			type=1,
		},
	[358]= {
			id=358,
			name="镇妖塔1",
			elems= {
					[1]= {name="秘境卷",chance=0,max=1,min=1,sid=40137,strong=1,type=0,},
					[2]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
					[3]= {name="翅晶石",chance=0,max=1,min=1,sid=40069,strong=1,type=0,},
					[4]= {name="天龙神锢宝石",chance=0,max=1,min=1,sid=60106,strong=1,type=0,},
					[5]= {name="五法青云宝石",chance=0,max=1,min=1,sid=60166,strong=1,type=0,},
					[6]= {name="百鬼夜宴宝石",chance=0,max=1,min=1,sid=60046,strong=1,type=0,},
					[7]= {name="天龙神锢腰带",chance=0,max=1,min=1,sid=60108,strong=1,type=0,},
					[8]= {name="五法青云腰带",chance=0,max=1,min=1,sid=60168,strong=1,type=0,},
					[9]= {name="百鬼夜宴腰带",chance=0,max=1,min=1,sid=60048,strong=1,type=0,},
				},
			type=1,
		},
	[359]= {
			id=359,
			name="镇地塔1",
			elems= {
					[1]= {name="秘境卷",chance=0,max=1,min=1,sid=40137,strong=1,type=0,},
					[2]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
					[3]= {name="翅晶石",chance=0,max=1,min=1,sid=40069,strong=1,type=0,},
					[4]= {name="天龙神锢宝石",chance=0,max=1,min=1,sid=60106,strong=1,type=0,},
					[5]= {name="五法青云宝石",chance=0,max=1,min=1,sid=60166,strong=1,type=0,},
					[6]= {name="百鬼夜宴宝石",chance=0,max=1,min=1,sid=60046,strong=1,type=0,},
					[7]= {name="天龙神锢腰带",chance=0,max=1,min=1,sid=60108,strong=1,type=0,},
					[8]= {name="五法青云腰带",chance=0,max=1,min=1,sid=60168,strong=1,type=0,},
					[9]= {name="百鬼夜宴腰带",chance=0,max=1,min=1,sid=60048,strong=1,type=0,},
				},
			type=1,
		},
	[360]= {
			id=360,
			name="镇天塔1",
			elems= {
					[1]= {name="秘境卷",chance=0,max=1,min=1,sid=40137,strong=1,type=0,},
					[2]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
					[3]= {name="翅晶石",chance=0,max=1,min=1,sid=40069,strong=1,type=0,},
					[4]= {name="天龙神锢宝石",chance=0,max=1,min=1,sid=60106,strong=1,type=0,},
					[5]= {name="五法青云宝石",chance=0,max=1,min=1,sid=60166,strong=1,type=0,},
					[6]= {name="百鬼夜宴宝石",chance=0,max=1,min=1,sid=60046,strong=1,type=0,},
					[7]= {name="天龙神锢腰带",chance=0,max=1,min=1,sid=60108,strong=1,type=0,},
					[8]= {name="五法青云腰带",chance=0,max=1,min=1,sid=60168,strong=1,type=0,},
					[9]= {name="百鬼夜宴腰带",chance=0,max=1,min=1,sid=60048,strong=1,type=0,},
				},
			type=1,
		},
	[361]= {
			id=361,
			name="保卫萝卜1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
					[2]= {name="木头",chance=0,max=1,min=1,sid=40119,strong=1,type=0,},
					[3]= {name="铁片",chance=0,max=1,min=1,sid=40120,strong=1,type=0,},
					[4]= {name="尖刺",chance=0,max=1,min=1,sid=40121,strong=1,type=0,},
				},
			type=1,
		},
	[362]= {
			id=362,
			name="天地降魔1",
			elems= {
					[1]= {name="弑皇破天头盔",chance=0,max=1,min=1,sid=60111,strong=1,type=0,},
					[2]= {name="弑皇破天战甲(男)",chance=0,max=1,min=1,sid=60112,strong=1,type=0,},
					[3]= {name="弑皇破天战甲(女)",chance=0,max=1,min=1,sid=60113,strong=1,type=0,},
					[4]= {name="弑皇破天项链",chance=0,max=1,min=1,sid=60114,strong=1,type=0,},
					[5]= {name="弑皇破天宝石",chance=0,max=1,min=1,sid=60116,strong=1,type=0,},
					[6]= {name="狂澜魄岳头盔",chance=0,max=1,min=1,sid=60171,strong=1,type=0,},
					[7]= {name="狂澜魄岳魔袍(男)",chance=0,max=1,min=1,sid=60172,strong=1,type=0,},
					[8]= {name="狂澜魄岳魔袍(女)",chance=0,max=1,min=1,sid=60173,strong=1,type=0,},
					[9]= {name="狂澜魄岳项链",chance=0,max=1,min=1,sid=60174,strong=1,type=0,},
					[10]= {name="狂澜魄岳宝石",chance=0,max=1,min=1,sid=60176,strong=1,type=0,},
					[11]= {name="太极逍遥头盔",chance=0,max=1,min=1,sid=60051,strong=1,type=0,},
					[12]= {name="太极逍遥道衣(男)",chance=0,max=1,min=1,sid=60052,strong=1,type=0,},
					[13]= {name="太极逍遥道衣(女)",chance=0,max=1,min=1,sid=60053,strong=1,type=0,},
					[14]= {name="太极逍遥项链",chance=0,max=1,min=1,sid=60054,strong=1,type=0,},
					[15]= {name="太极逍遥宝石",chance=0,max=1,min=1,sid=60056,strong=1,type=0,},
					[16]= {name="五虎断岳",chance=0,max=1,min=1,sid=60100,strong=1,type=0,},
					[17]= {name="天龙神锢头盔",chance=0,max=1,min=1,sid=60101,strong=1,type=0,},
					[18]= {name="天龙神锢战甲(男)",chance=0,max=1,min=1,sid=60102,strong=1,type=0,},
					[19]= {name="天龙神锢战甲(女)",chance=0,max=1,min=1,sid=60103,strong=1,type=0,},
					[20]= {name="天龙神锢项链",chance=0,max=1,min=1,sid=60104,strong=1,type=0,},
					[21]= {name="天龙神锢宝石",chance=0,max=1,min=1,sid=60106,strong=1,type=0,},
					[22]= {name="仙人指路",chance=0,max=1,min=1,sid=60040,strong=1,type=0,},
					[23]= {name="百鬼夜宴头盔",chance=0,max=1,min=1,sid=60041,strong=1,type=0,},
					[24]= {name="百鬼夜宴道袍(男)",chance=0,max=1,min=1,sid=60042,strong=1,type=0,},
					[25]= {name="百鬼夜宴道袍(女)",chance=0,max=1,min=1,sid=60043,strong=1,type=0,},
					[26]= {name="百鬼夜宴项链",chance=0,max=1,min=1,sid=60044,strong=1,type=0,},
					[27]= {name="百鬼夜宴宝石",chance=0,max=1,min=1,sid=60046,strong=1,type=0,},
					[28]= {name="离火薄天",chance=0,max=1,min=1,sid=60160,strong=1,type=0,},
					[29]= {name="五法青云头盔",chance=0,max=1,min=1,sid=60161,strong=1,type=0,},
					[30]= {name="五法青云魔袍(男)",chance=0,max=1,min=1,sid=60162,strong=1,type=0,},
					[31]= {name="五法青云魔袍(女)",chance=0,max=1,min=1,sid=60163,strong=1,type=0,},
					[32]= {name="五法青云项链",chance=0,max=1,min=1,sid=60164,strong=1,type=0,},
					[33]= {name="五法青云宝石",chance=0,max=1,min=1,sid=60166,strong=1,type=0,},
				},
			type=1,
		},
	[363]= {
			id=363,
			name="魔神封印1",
			elems= {
					[1]= {name="星瀚幽路定身戒指",chance=0,max=1,min=1,sid=60232,strong=1,type=0,},
					[2]= {name="肃魂裂天",chance=0,max=1,min=1,sid=60110,strong=1,type=0,},
					[3]= {name="牧云惊鸿",chance=0,max=1,min=1,sid=60170,strong=1,type=0,},
					[4]= {name="缚神揽月",chance=0,max=1,min=1,sid=60050,strong=1,type=0,},
					[5]= {name="10级生命魂石",chance=0,max=1,min=1,sid=10070,strong=1,type=0,},
					[6]= {name="10级魔法魂石",chance=0,max=1,min=1,sid=10071,strong=1,type=0,},
					[7]= {name="5级物攻魂石",chance=0,max=1,min=1,sid=10039,strong=1,type=0,},
					[8]= {name="5级魔攻魂石",chance=0,max=1,min=1,sid=10040,strong=1,type=0,},
					[9]= {name="5级道攻魂石",chance=0,max=1,min=1,sid=10041,strong=1,type=0,},
					[10]= {name="弑皇破天项链",chance=0,max=1,min=1,sid=60114,strong=1,type=0,},
					[11]= {name="太极逍遥项链",chance=0,max=1,min=1,sid=60054,strong=1,type=0,},
					[12]= {name="天龙神锢项链",chance=0,max=1,min=1,sid=60104,strong=1,type=0,},
					[13]= {name="五法青云项链",chance=0,max=1,min=1,sid=60164,strong=1,type=0,},
					[14]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,strong=1,type=0,},
				},
			type=1,
		},
	[364]= {
			id=364,
			name="祈福树1",
			elems= {
					[1]= {name="经验",chance=0,max=1,min=1,sid=1,strong=1,type=0,},
				},
			type=1,
		},
	[365]= {
			id=365,
			name="转生地陵（仅限单人）1",
			elems= {
					[1]= {name="转生灵魄",chance=0,max=1,min=1,sid=30091,strong=1,type=0,},
				},
			type=1,
		},
	[366]= {
			id=366,
			name="异形魔尊1",
			elems= {
					[1]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[3]= {name="朝夕百花",chance=0,max=1,min=1,sid=60000,type=0,},
					[4]= {name="降魔引魂",chance=0,max=1,min=1,sid=60060,type=0,},
					[5]= {name="混元蚀日",chance=0,max=1,min=1,sid=60120,type=0,},
					[6]= {name="飞星舞雪",chance=0,max=1,min=1,sid=60130,type=0,},
					[7]= {name="晃金摘星",chance=0,max=1,min=1,sid=60070,type=0,},
					[8]= {name="游龙戏凤",chance=0,max=1,min=1,sid=60010,type=0,},
					[9]= {name="八卦錾金道衣(男)",chance=0,max=1,min=1,sid=60002,type=0,},
					[10]= {name="光华若木道衣(女)",chance=0,max=1,min=1,sid=60013,type=0,},
					[11]= {name="星瀚幽路战甲(男)",chance=0,max=1,min=1,sid=60062,type=0,},
					[12]= {name="离情霜月战甲(女)",chance=0,max=1,min=1,sid=60073,type=0,},
					[13]= {name="碎寂震天魔袍(男)",chance=0,max=1,min=1,sid=60122,type=0,},
					[14]= {name="夜灵啸日魔袍(女)",chance=0,max=1,min=1,sid=60133,type=0,},
					[15]= {name="1级物防魂石",chance=0,max=1,min=1,sid=10009,type=0,},
					[16]= {name="1级魔防魂石",chance=0,max=1,min=1,sid=10010,type=0,},
					[17]= {name="1级物攻魂石",chance=0,max=1,min=1,sid=10011,type=0,},
					[18]= {name="2级物攻魂石",chance=0,max=1,min=1,sid=10018,type=0,},
					[19]= {name="2级魔攻魂石",chance=0,max=1,min=1,sid=10019,type=0,},
					[20]= {name="2级道攻魂石",chance=0,max=1,min=1,sid=10020,type=0,},
				},
			type=1,
		},
	[367]= {
			id=367,
			name="异形魔尊2",
			elems= {
					[1]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[3]= {name="朝夕百花",chance=0,max=1,min=1,sid=60000,type=0,},
					[4]= {name="降魔引魂",chance=0,max=1,min=1,sid=60060,type=0,},
					[5]= {name="混元蚀日",chance=0,max=1,min=1,sid=60120,type=0,},
					[6]= {name="飞星舞雪",chance=0.5,max=1,min=1,sid=60130,type=0,},
					[7]= {name="晃金摘星",chance=0.55,max=1,min=1,sid=60070,type=0,},
					[8]= {name="游龙戏凤",chance=0.4,max=1,min=1,sid=60010,type=0,},
					[9]= {name="八卦錾金道衣(男)",chance=0.45,max=1,min=1,sid=60002,type=0,},
					[10]= {name="光华若木道衣(女)",chance=0.5,max=1,min=1,sid=60013,type=0,},
					[11]= {name="星瀚幽路战甲(男)",chance=0,max=1,min=1,sid=60062,type=0,},
					[12]= {name="离情霜月战甲(女)",chance=0,max=1,min=1,sid=60073,type=0,},
					[13]= {name="碎寂震天魔袍(男)",chance=0,max=1,min=1,sid=60122,type=0,},
					[14]= {name="夜灵啸日魔袍(女)",chance=0,max=1,min=1,sid=60133,type=0,},
					[15]= {name="3级物防魂石",chance=0,max=1,min=1,sid=10023,type=0,},
					[16]= {name="3级魔防魂石",chance=0,max=1,min=1,sid=10024,type=0,},
					[17]= {name="3级物攻魂石",chance=0,max=1,min=1,sid=10025,type=0,},
					[18]= {name="2级物攻魂石",chance=0,max=1,min=1,sid=10018,type=0,},
					[19]= {name="2级魔攻魂石",chance=0,max=1,min=1,sid=10019,type=0,},
					[20]= {name="2级道攻魂石",chance=0,max=1,min=1,sid=10020,type=0,},
					[21]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[22]= {name="$50-55级怪金币",chance=0,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[368]= {
			id=368,
			name="异形魔尊3",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="$40级套装",chance=0,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[9]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[10]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=0,max=1,min=1,sid=30,type=1,},
					[12]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[13]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[14]= {name="$50-55级怪金币",chance=0,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[369]= {
			id=369,
			name="异形魔尊4",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=0,max=1,min=1,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=0,max=1,min=1,sid=64,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="$40级套装",chance=0,max=1,min=1,sid=17,type=1,},
					[7]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[8]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[9]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[10]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[11]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[12]= {name="$50-55级怪金币",chance=0.5,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[370]= {
			id=370,
			name="熔岩火龙王1",
			elems= {
					[1]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[2]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[3]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[4]= {name="$40级套装",chance=0,max=1,min=1,sid=17,type=1,},
					[5]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[6]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[7]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[371]= {
			id=371,
			name="熔岩火龙王2",
			elems= {
					[1]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[2]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[3]= {name="$40级套装",chance=0,max=1,min=1,sid=17,type=1,},
					[4]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[5]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[6]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[372]= {
			id=372,
			name="熔岩火龙王3",
			elems= {
					[1]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[2]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[3]= {name="$45级套装",chance=0,max=1,min=1,sid=18,type=1,},
					[4]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[5]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[6]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[7]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[373]= {
			id=373,
			name="熔岩火龙王4",
			elems= {
					[1]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[2]= {name="$大boss掉落常用杂品",chance=0,max=1,min=1,sid=63,type=1,},
					[3]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[4]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[5]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[374]= {
			id=374,
			name="火凤1",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[8]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[375]= {
			id=375,
			name="火凤2",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[8]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[9]= {name="$二级魂石",chance=0,max=1,min=1,sid=30,type=1,},
					[10]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[11]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[376]= {
			id=376,
			name="火凤3",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="$40级套装",chance=0,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[9]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[10]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=0,max=1,min=1,sid=30,type=1,},
					[12]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[377]= {
			id=377,
			name="火凤4",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=0,max=1,min=1,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=0,max=1,min=1,sid=64,type=1,},
					[5]= {name="$45级套装",chance=0,max=1,min=1,sid=18,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[8]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[9]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[10]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[11]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[12]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[378]= {
			id=378,
			name="牛魔王1",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[8]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[379]= {
			id=379,
			name="牛魔王2",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[8]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[9]= {name="$二级魂石",chance=0,max=1,min=1,sid=30,type=1,},
					[10]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[11]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[380]= {
			id=380,
			name="牛魔王3",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="$40级套装",chance=0,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[9]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[10]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=0,max=1,min=1,sid=30,type=1,},
					[12]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[381]= {
			id=381,
			name="牛魔王4",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=0,max=1,min=1,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=0,max=1,min=1,sid=64,type=1,},
					[5]= {name="$45级套装",chance=0,max=1,min=1,sid=18,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[8]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[9]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[10]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[11]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[12]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[382]= {
			id=382,
			name="冥轮王蛇1",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[8]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[383]= {
			id=383,
			name="冥轮王蛇2",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=0,max=1,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[8]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[9]= {name="$二级魂石",chance=0,max=1,min=1,sid=30,type=1,},
					[10]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[11]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[384]= {
			id=384,
			name="冥轮王蛇3",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=0,max=1,min=1,sid=8,type=1,},
					[6]= {name="$40级套装",chance=0,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[9]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[10]= {name="$一级魂石",chance=0,max=1,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=0,max=1,min=1,sid=30,type=1,},
					[12]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[385]= {
			id=385,
			name="冥轮王蛇4",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=0,max=1,min=1,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=0,max=1,min=1,sid=64,type=1,},
					[5]= {name="$45级套装",chance=0,max=1,min=1,sid=18,type=1,},
					[6]= {name="一级灵石",chance=0,max=1,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[8]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[9]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[10]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[11]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[12]= {name="$55-60级怪金币",chance=0,max=1,min=1,sid=74,type=1,},
				},
			type=1,
		},
	[386]= {
			id=386,
			name="冰麒麟1",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[13]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[14]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[15]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[16]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[17]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[18]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[19]= {name="$50-55级怪金币",chance=0,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[387]= {
			id=387,
			name="冰麒麟2",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[13]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[14]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[15]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[16]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[17]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[18]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[19]= {name="$50-55级怪金币",chance=0,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[388]= {
			id=388,
			name="冰麒麟3",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[13]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[14]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[15]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[16]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[17]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[18]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[19]= {name="$50-55级怪金币",chance=0,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[389]= {
			id=389,
			name="冰麒麟4",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=0,max=1,min=1,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=0,max=1,min=1,sid=64,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[13]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[14]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[15]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[16]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[17]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[18]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[19]= {name="$50-55级怪金币",chance=0,max=1,min=1,sid=73,type=1,},
				},
			type=1,
		},
	[390]= {
			id=390,
			name="冰骨魔龙1",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="$55级套装零件",chance=0,max=1,min=1,sid=22,type=1,},
					[13]= {name="$55级套装武器",chance=0,max=1,min=1,sid=21,type=1,},
					[14]= {name="$60级套装零件",chance=0,max=1,min=1,sid=24,type=1,},
					[15]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[22]= {name="$70-75级怪金币",chance=0,max=1,min=1,sid=77,type=1,},
				},
			type=1,
		},
	[391]= {
			id=391,
			name="冰骨魔龙2",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="$55级套装零件",chance=0,max=1,min=1,sid=22,type=1,},
					[13]= {name="$55级套装武器",chance=0,max=1,min=1,sid=21,type=1,},
					[14]= {name="$60级套装零件",chance=0,max=1,min=1,sid=24,type=1,},
					[15]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[22]= {name="$70-75级怪金币",chance=0,max=1,min=1,sid=77,type=1,},
				},
			type=1,
		},
	[392]= {
			id=392,
			name="冰骨魔龙3",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=0,max=1,min=1,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=0,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="$55级套装零件",chance=0,max=1,min=1,sid=22,type=1,},
					[13]= {name="$55级套装武器",chance=0,max=1,min=1,sid=21,type=1,},
					[14]= {name="$60级套装零件",chance=0,max=1,min=1,sid=24,type=1,},
					[15]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[22]= {name="$70-75级怪金币",chance=0,max=1,min=1,sid=77,type=1,},
				},
			type=1,
		},
	[393]= {
			id=393,
			name="冰骨魔龙4",
			elems= {
					[1]= {name="$超级药",chance=0,max=1,min=1,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0,max=1,min=1,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=0,max=1,min=1,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=0,max=1,min=1,sid=64,type=1,},
					[5]= {name="祝福油",chance=0,max=1,min=1,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=0,max=1,min=1,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=0,max=1,min=1,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=0,max=1,min=1,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=0,max=1,min=1,sid=30191,type=0,},
					[11]= {name="$50级套装零件",chance=0,max=1,min=1,sid=20,type=1,},
					[12]= {name="$55级套装零件",chance=0,max=1,min=1,sid=22,type=1,},
					[13]= {name="$55级套装武器",chance=0,max=1,min=1,sid=21,type=1,},
					[14]= {name="$60级套装零件",chance=0,max=1,min=1,sid=24,type=1,},
					[15]= {name="神圣戒指",chance=0,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=0,max=1,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=0,max=1,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=0,max=1,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=0,max=1,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0,max=1,min=1,sid=32,type=1,},
					[22]= {name="$70-75级怪金币",chance=0,max=1,min=1,sid=77,type=1,},
				},
			type=1,
		},
	[394]= {
			id=394,
			name="跨服攻城战1",
			elems= {
					[1]= {name="动感时尚(男)10阶[6天]",chance=0,max=1,min=1,sid=81287,type=0,},
					[2]= {name="青涩校园(男)[6天]",chance=0,max=1,min=1,sid=81289,type=0,},
					[3]= {name="足迹晶魄",chance=0,max=1,min=1,sid=40016,type=0,},
					[4]= {name="幻武水晶",chance=0,max=1,min=1,sid=40071,type=0,},
					[5]= {name="宠物项圈",chance=0,max=1,min=1,sid=40053,type=0,},
				},
			type=1,
		},
	[395]= {
			id=395,
			name="冥魂神殿1",
			elems= {
					[1]= {name="附魔卷",chance=0,max=1,min=1,sid=40148,type=0,},
					[2]= {name="附魔强化符",chance=0,max=1,min=1,sid=40149,type=0,},
					[3]= {name="极品附魔符",chance=0,max=1,min=1,sid=40150,type=0,},
					[4]= {name="复生戒指",chance=0,max=1,min=1,sid=60223,type=0,},
					[5]= {name="定身戒指",chance=0,max=1,min=1,sid=60231,type=0,},
					[6]= {name="护法戒指",chance=0,max=1,min=1,sid=60239,type=0,},
					[7]= {name="百鸟朝凤(1档)",chance=0,max=1,min=1,sid=80001,type=0,},
					[8]= {name="黄金雷锤(1阶)",chance=0,max=1,min=1,sid=82000,type=0,},
					[9]= {name="缚神揽月",chance=0,max=1,min=1,sid=60050,type=0,},
					[10]= {name="肃魂裂天",chance=0,max=1,min=1,sid=60110,type=0,},
					[11]= {name="牧云惊鸿",chance=0,max=1,min=1,sid=60170,type=0,},
					[12]= {name="五级灵石",chance=0,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[396]= {
			id=396,
			name="异形魔尊(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=2,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=397,type=1,},
					[7]= {chance=1,max=1,min=1,sid=398,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[397]= {
			id=397,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[398]= {
			id=398,
			elems= {
					[1]= {name="$40级套装",chance=0.6,max=2,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.4,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[399]= {
			id=399,
			elems= {
					[1]= {name="二级灵石",chance=0.35,max=1,min=1,sid=40001,type=0,},
					[2]= {name="$二级魂石",chance=0.35,max=1,min=1,sid=30,type=1,},
				},
			type=1,
		},
	[400]= {
			id=400,
			name="异形魔尊(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=2,min=2,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=401,type=1,},
					[7]= {chance=1,max=1,min=1,sid=402,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=0.65,max=2,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
				},
			max=81,
			type=0,
		},
	[401]= {
			id=401,
			elems= {
					[1]= {name="$50级散件",chance=0.5,max=1,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.5,max=1,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[402]= {
			id=402,
			elems= {
					[1]= {name="$40级套装",chance=0.6,max=1,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.3,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[403]= {
			id=403,
			name="异形魔尊(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=4,min=2,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=404,type=1,},
					[7]= {chance=1,max=1,min=1,sid=405,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=0.513,max=2,min=1,sid=30,type=1,},
					[12]= {name="$三级魂石",chance=0.0105,max=1,min=1,sid=31,type=1,},
				},
			max=81,
			type=0,
		},
	[404]= {
			id=404,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=1,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=1,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[405]= {
			id=405,
			elems= {
					[1]= {name="$40级套装",chance=0.6,max=1,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.3,max=1,min=1,sid=18,type=1,},
					[3]= {name="$50级套装零件",chance=0.05,max=1,min=1,sid=20,type=1,},
				},
			type=1,
		},
	[406]= {
			id=406,
			name="异形魔尊(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=1,max=6,min=4,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=0.0086,max=2,min=1,sid=64,type=1,},
					[5]= {name="$45级散件",chance=0.0075,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=407,type=1,},
					[7]= {chance=1,max=1,min=1,sid=408,type=1,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$四级魂石",chance=0.0077,max=2,min=1,sid=32,type=1,},
					[10]= {chance=1,max=1,min=1,sid=409,type=1,},
				},
			max=81,
			type=0,
		},
	[407]= {
			id=407,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=1,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.0027,max=1,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[408]= {
			id=408,
			elems= {
					[1]= {name="$40级套装",chance=0.5,max=1,min=1,sid=17,type=1,},
					[2]= {name="$55级套装零件",chance=0.015,max=1,min=1,sid=22,type=1,},
					[3]= {name="$45级套装",chance=0.4,max=1,min=1,sid=18,type=1,},
					[4]= {name="$50级套装零件",chance=0.08,max=1,min=1,sid=20,type=1,},
					[5]= {name="$50级套装武器",chance=0.005,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[409]= {
			id=409,
			elems= {
					[1]= {name="$三级魂石",chance=0.1,max=1,min=1,sid=31,type=1,},
					[2]= {name="$一级魂石",chance=0.65,max=3,min=2,sid=29,type=1,},
					[3]= {name="$二级魂石",chance=0.25,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[410]= {
			id=410,
			name="熔岩火龙王(0-5)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=9,min=9,sid=74,type=1,},
				},
			elems= {
					[1]= {name="强效太阳水",chance=1,max=3,min=2,sid=39009,type=0,},
					[2]= {name="$小boss掉落常用杂品",chance=0.56,max=2,min=1,sid=59,type=1,},
					[3]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[4]= {chance=1,max=1,min=1,sid=411,type=1,},
					[5]= {name="$40级套装",chance=1,max=1,min=1,sid=17,type=1,},
					[6]= {chance=1,max=1,min=1,sid=412,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=0.35,max=1,min=1,sid=40001,type=0,},
				},
			max=9,
			type=0,
		},
	[411]= {
			id=411,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[412]= {
			id=412,
			elems= {
					[1]= {name="$45级套装",chance=0.6,max=2,min=1,sid=18,type=1,},
					[2]= {name="$50级套装零件",chance=0.3,max=1,min=1,sid=20,type=1,},
					[3]= {name="$50级套装武器",chance=0.1,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[413]= {
			id=413,
			name="熔岩火龙王(6-10)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=9,min=9,sid=74,type=1,},
				},
			elems= {
					[1]= {name="强效太阳水",chance=1,max=3,min=2,sid=39009,type=0,},
					[2]= {name="$小boss掉落常用杂品",chance=1,max=2,min=1,sid=59,type=1,},
					[3]= {chance=1,max=1,min=1,sid=414,type=1,},
					[4]= {name="$40级套装",chance=1,max=1,min=1,sid=17,type=1,},
					[5]= {chance=1,max=1,min=1,sid=415,type=1,},
					[6]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=0.65,max=2,min=1,sid=40001,type=0,},
				},
			max=9,
			type=0,
		},
	[414]= {
			id=414,
			elems= {
					[1]= {name="$50级散件",chance=0.5,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.5,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[415]= {
			id=415,
			elems= {
					[1]= {name="$45级套装",chance=0.38,max=2,min=1,sid=18,type=1,},
					[2]= {name="$50级套装零件",chance=0.5,max=2,min=1,sid=20,type=1,},
					[3]= {name="$50级套装武器",chance=0.12,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[416]= {
			id=416,
			name="熔岩火龙王(11-15)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=9,min=9,sid=74,type=1,},
				},
			elems= {
					[1]= {name="强效太阳水",chance=1,max=3,min=2,sid=39009,type=0,},
					[2]= {name="$中boss掉落常用杂品",chance=1,max=2,min=2,sid=61,type=1,},
					[3]= {chance=1,max=1,min=1,sid=417,type=1,},
					[4]= {name="$45级套装",chance=1,max=1,min=1,sid=18,type=1,},
					[5]= {chance=1,max=1,min=1,sid=418,type=1,},
					[6]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[7]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[8]= {name="三级灵石",chance=0.6,max=1,min=1,sid=40002,type=0,},
				},
			max=9,
			type=0,
		},
	[417]= {
			id=417,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[418]= {
			id=418,
			elems= {
					[1]= {name="$50级套装零件",chance=0.65,max=2,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.15,max=1,min=1,sid=19,type=1,},
					[3]= {name="$55级套装零件",chance=0.2,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[419]= {
			id=419,
			name="熔岩火龙王(16-20)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=9,min=9,sid=74,type=1,},
				},
			elems= {
					[1]= {name="强效太阳水",chance=1,max=3,min=1,sid=39009,type=0,},
					[2]= {name="$大boss掉落常用杂品",chance=1,max=1,min=1,sid=63,type=1,},
					[3]= {chance=1,max=1,min=1,sid=420,type=1,},
					[4]= {chance=1,max=1,min=1,sid=421,type=1,},
					[5]= {chance=1,max=1,min=1,sid=422,type=1,},
					[6]= {name="二级灵石",chance=1,max=3,min=2,sid=40001,type=0,},
					[7]= {name="三级灵石",chance=0.8,max=2,min=1,sid=40002,type=0,},
				},
			max=9,
			type=0,
		},
	[420]= {
			id=420,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[421]= {
			id=421,
			elems= {
					[1]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
					[2]= {name="$50级套装零件",chance=0.5,max=2,min=1,sid=20,type=1,},
				},
			type=1,
		},
	[422]= {
			id=422,
			elems= {
					[1]= {name="$50级套装武器",chance=0.3,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.5,max=2,min=1,sid=22,type=1,},
					[3]= {name="$55级套装武器",chance=0.2,max=1,min=1,sid=21,type=1,},
				},
			type=1,
		},
	[423]= {
			id=423,
			name="火凤(0-5)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=2,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=424,type=1,},
					[7]= {chance=1,max=1,min=1,sid=425,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {chance=1,max=1,min=1,sid=426,type=1,},
				},
			max=81,
			type=0,
		},
	[424]= {
			id=424,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[425]= {
			id=425,
			elems= {
					[1]= {name="$40级套装",chance=0.6,max=2,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.4,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[426]= {
			id=426,
			elems= {
					[1]= {name="二级灵石",chance=0.35,max=1,min=1,sid=40001,type=0,},
					[2]= {name="$二级魂石",chance=0.35,max=1,min=1,sid=30,type=1,},
				},
			type=1,
		},
	[427]= {
			id=427,
			name="火凤(6-10)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=4,min=2,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=428,type=1,},
					[7]= {chance=1,max=1,min=1,sid=429,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=0.65,max=2,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[12]= {name="$三级魂石",chance=0.35,max=1,min=1,sid=31,type=1,},
				},
			max=81,
			type=0,
		},
	[428]= {
			id=428,
			elems= {
					[1]= {name="$50级散件",chance=0.5,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.5,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[429]= {
			id=429,
			elems= {
					[1]= {name="$40级套装",chance=0.4,max=2,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
					[3]= {name="$50级套装零件",chance=0.1,max=1,min=1,sid=20,type=1,},
				},
			type=1,
		},
	[430]= {
			id=430,
			name="火凤(11-15)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=431,type=1,},
					[7]= {name="$40级套装",chance=1,max=1,min=1,sid=17,type=1,},
					[8]= {chance=1,max=1,min=1,sid=432,type=1,},
					[9]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[10]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[11]= {name="三级灵石",chance=0.6,max=1,min=1,sid=40002,type=0,},
					[12]= {name="$一级魂石",chance=1,max=1,min=1,sid=29,type=1,},
					[13]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[14]= {chance=1,max=1,min=1,sid=433,type=1,},
				},
			max=81,
			type=0,
		},
	[431]= {
			id=431,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[432]= {
			id=432,
			elems= {
					[1]= {name="$45级套装",chance=0.44,max=2,min=1,sid=18,type=1,},
					[2]= {name="$50级套装零件",chance=0.5,max=1,min=1,sid=20,type=1,},
					[3]= {name="$50级套装武器",chance=0.06,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[433]= {
			id=433,
			elems= {
					[1]= {name="$三级魂石",chance=0.9,max=1,min=1,sid=31,type=1,},
					[2]= {name="$四级魂石",chance=0.1,max=1,min=1,sid=32,type=1,},
				},
			type=1,
		},
	[434]= {
			id=434,
			name="火凤(16-20)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=1,max=6,min=4,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[5]= {chance=1,max=1,min=1,sid=435,type=1,},
					[6]= {name="$45级套装",chance=1,max=1,min=1,sid=18,type=1,},
					[7]= {chance=1,max=1,min=1,sid=436,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[10]= {name="三级灵石",chance=0.8,max=1,min=1,sid=40002,type=0,},
					[11]= {name="$三级魂石",chance=1,max=1,min=1,sid=31,type=1,},
					[12]= {name="$四级魂石",chance=0.15,max=2,min=1,sid=32,type=1,},
					[13]= {chance=1,max=1,min=1,sid=437,type=1,},
				},
			max=81,
			type=0,
		},
	[435]= {
			id=435,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[436]= {
			id=436,
			elems= {
					[1]= {name="$50级套装零件",chance=0.4,max=2,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.2,max=1,min=1,sid=19,type=1,},
					[3]= {name="$55级套装零件",chance=0.4,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[437]= {
			id=437,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[438]= {
			id=438,
			name="牛魔王(0-5)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=2,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=439,type=1,},
					[7]= {chance=1,max=1,min=1,sid=440,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {chance=1,max=1,min=1,sid=441,type=1,},
				},
			max=81,
			type=0,
		},
	[439]= {
			id=439,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[440]= {
			id=440,
			elems= {
					[1]= {name="$40级套装",chance=0.6,max=2,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.4,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[441]= {
			id=441,
			elems= {
					[1]= {name="二级灵石",chance=0.35,max=1,min=1,sid=40001,type=0,},
					[2]= {name="$二级魂石",chance=0.35,max=1,min=1,sid=30,type=1,},
				},
			type=1,
		},
	[442]= {
			id=442,
			name="牛魔王(6-10)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=4,min=2,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=443,type=1,},
					[7]= {chance=1,max=1,min=1,sid=444,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=0.65,max=2,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[12]= {name="$三级魂石",chance=0.35,max=1,min=1,sid=31,type=1,},
				},
			max=81,
			type=0,
		},
	[443]= {
			id=443,
			elems= {
					[1]= {name="$50级散件",chance=0.5,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.5,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[444]= {
			id=444,
			elems= {
					[1]= {name="$40级套装",chance=0.4,max=2,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
					[3]= {name="$50级套装零件",chance=0.1,max=1,min=1,sid=20,type=1,},
				},
			type=1,
		},
	[445]= {
			id=445,
			name="牛魔王(11-15)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=446,type=1,},
					[7]= {name="$40级套装",chance=1,max=1,min=1,sid=17,type=1,},
					[8]= {chance=1,max=1,min=1,sid=447,type=1,},
					[9]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[10]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[11]= {name="三级灵石",chance=0.6,max=1,min=1,sid=40002,type=0,},
					[12]= {name="$一级魂石",chance=1,max=1,min=1,sid=29,type=1,},
					[13]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[14]= {chance=1,max=1,min=1,sid=448,type=1,},
				},
			max=81,
			type=0,
		},
	[446]= {
			id=446,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[447]= {
			id=447,
			elems= {
					[1]= {name="$45级套装",chance=0.44,max=2,min=1,sid=18,type=1,},
					[2]= {name="$50级套装零件",chance=0.5,max=1,min=1,sid=20,type=1,},
					[3]= {name="$50级套装武器",chance=0.06,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[448]= {
			id=448,
			elems= {
					[1]= {name="$三级魂石",chance=0.9,max=1,min=1,sid=31,type=1,},
					[2]= {name="$四级魂石",chance=0.1,max=1,min=1,sid=32,type=1,},
				},
			type=1,
		},
	[449]= {
			id=449,
			name="牛魔王(16-20)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=1,max=6,min=4,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[5]= {chance=1,max=1,min=1,sid=450,type=1,},
					[6]= {name="$45级套装",chance=1,max=1,min=1,sid=18,type=1,},
					[7]= {chance=1,max=1,min=1,sid=451,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[10]= {name="三级灵石",chance=0.8,max=1,min=1,sid=40002,type=0,},
					[11]= {name="四级灵石",chance=0.2,max=1,min=1,sid=40003,type=0,},
					[12]= {name="$三级魂石",chance=1,max=1,min=1,sid=31,type=1,},
					[13]= {name="$四级魂石",chance=0.15,max=1,min=1,sid=32,type=1,},
					[14]= {chance=1,max=1,min=1,sid=452,type=1,},
				},
			max=81,
			type=0,
		},
	[450]= {
			id=450,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[451]= {
			id=451,
			elems= {
					[1]= {name="$50级套装零件",chance=0.4,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.2,max=1,min=1,sid=19,type=1,},
					[3]= {name="$55级套装零件",chance=0.4,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[452]= {
			id=452,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[453]= {
			id=453,
			name="冥轮王蛇(0-5)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=2,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=454,type=1,},
					[7]= {chance=1,max=1,min=1,sid=455,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {chance=1,max=1,min=1,sid=456,type=1,},
				},
			max=81,
			type=0,
		},
	[454]= {
			id=454,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[455]= {
			id=455,
			elems= {
					[1]= {name="$40级套装",chance=0.6,max=2,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.4,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[456]= {
			id=456,
			elems= {
					[1]= {name="二级灵石",chance=0.35,max=1,min=1,sid=40001,type=0,},
					[2]= {name="$二级魂石",chance=0.35,max=1,min=1,sid=30,type=1,},
				},
			type=1,
		},
	[457]= {
			id=457,
			name="冥轮王蛇(6-10)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=4,min=2,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=458,type=1,},
					[7]= {chance=1,max=1,min=1,sid=459,type=1,},
					[8]= {name="一级灵石",chance=1,max=3,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=0.65,max=2,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[12]= {name="$三级魂石",chance=0.35,max=1,min=1,sid=31,type=1,},
				},
			max=81,
			type=0,
		},
	[458]= {
			id=458,
			elems= {
					[1]= {name="$50级散件",chance=0.5,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.5,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[459]= {
			id=459,
			elems= {
					[1]= {name="$40级套装",chance=0.4,max=2,min=1,sid=17,type=1,},
					[2]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
					[3]= {name="$50级套装零件",chance=0.1,max=1,min=1,sid=20,type=1,},
				},
			type=1,
		},
	[460]= {
			id=460,
			name="冥轮王蛇(11-15)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="$45级散件",chance=1,max=2,min=1,sid=8,type=1,},
					[6]= {chance=1,max=1,min=1,sid=461,type=1,},
					[7]= {name="$40级套装",chance=1,max=1,min=1,sid=17,type=1,},
					[8]= {chance=1,max=1,min=1,sid=462,type=1,},
					[9]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[10]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[11]= {name="三级灵石",chance=0.6,max=1,min=1,sid=40002,type=0,},
					[12]= {name="$一级魂石",chance=1,max=1,min=1,sid=29,type=1,},
					[13]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[14]= {chance=1,max=1,min=1,sid=463,type=1,},
				},
			max=81,
			type=0,
		},
	[461]= {
			id=461,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[462]= {
			id=462,
			elems= {
					[1]= {name="$45级套装",chance=0.44,max=2,min=1,sid=18,type=1,},
					[2]= {name="$50级套装零件",chance=0.5,max=1,min=1,sid=20,type=1,},
					[3]= {name="$50级套装武器",chance=0.06,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[463]= {
			id=463,
			elems= {
					[1]= {name="$三级魂石",chance=0.9,max=1,min=1,sid=31,type=1,},
					[2]= {name="$四级魂石",chance=0.1,max=1,min=1,sid=32,type=1,},
				},
			type=1,
		},
	[464]= {
			id=464,
			name="冥轮王蛇(16-20)",
			coplelem= {
					[1]= {name="$55-60级怪金币",chance=0,max=81,min=81,sid=74,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=1,max=6,min=4,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[5]= {chance=1,max=1,min=1,sid=465,type=1,},
					[6]= {name="$45级套装",chance=1,max=1,min=1,sid=18,type=1,},
					[7]= {chance=1,max=1,min=1,sid=466,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[10]= {name="三级灵石",chance=0.8,max=1,min=1,sid=40002,type=0,},
					[11]= {name="四级灵石",chance=0.01,max=1,min=1,sid=40003,type=0,},
					[12]= {name="$三级魂石",chance=1,max=1,min=1,sid=31,type=1,},
					[13]= {name="$四级魂石",chance=0.03,max=1,min=1,sid=32,type=1,},
					[14]= {chance=1,max=1,min=1,sid=467,type=1,},
				},
			max=81,
			type=0,
		},
	[465]= {
			id=465,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[466]= {
			id=466,
			elems= {
					[1]= {name="$50级套装零件",chance=0.4,max=2,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.2,max=1,min=1,sid=19,type=1,},
					[3]= {name="$55级套装零件",chance=0.4,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[467]= {
			id=467,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[468]= {
			id=468,
			name="冰麒麟(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=1,max=5,min=2,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=5,min=2,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=5,min=2,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=5,min=1,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=469,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=470,type=1,},
					[14]= {chance=1,max=1,min=1,sid=471,type=1,},
					[15]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=1,max=3,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=1,max=1,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=1,max=2,min=2,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0.1,max=2,min=1,sid=32,type=1,},
					[22]= {chance=1,max=1,min=1,sid=472,type=1,},
				},
			max=81,
			type=0,
		},
	[469]= {
			id=469,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[470]= {
			id=470,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[471]= {
			id=471,
			elems= {
					[1]= {name="$55级套装武器",chance=0.05,max=1,min=1,sid=21,type=1,},
					[2]= {name="$60级套装零件",chance=0.05,max=1,min=1,sid=24,type=1,},
				},
			type=1,
		},
	[472]= {
			id=472,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[473]= {
			id=473,
			name="冰麒麟(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=1,max=5,min=3,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=5,min=3,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=5,min=3,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=5,min=2,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=474,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=475,type=1,},
					[14]= {chance=1,max=1,min=1,sid=476,type=1,},
					[15]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=1,max=1,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0.2,max=2,min=1,sid=32,type=1,},
					[22]= {chance=1,max=1,min=1,sid=477,type=1,},
				},
			max=81,
			type=0,
		},
	[474]= {
			id=474,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[475]= {
			id=475,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[476]= {
			id=476,
			elems= {
					[1]= {name="$55级套装武器",chance=0.1,max=1,min=1,sid=21,type=1,},
					[2]= {name="$60级套装零件",chance=0.1,max=1,min=1,sid=24,type=1,},
				},
			type=1,
		},
	[477]= {
			id=477,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[478]= {
			id=478,
			name="冰麒麟(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=1,max=5,min=3,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=5,min=3,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=5,min=3,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=6,min=3,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=479,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=480,type=1,},
					[14]= {chance=1,max=1,min=1,sid=481,type=1,},
					[15]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=1,max=2,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0.3,max=2,min=1,sid=32,type=1,},
					[22]= {chance=1,max=1,min=1,sid=482,type=1,},
				},
			max=81,
			type=0,
		},
	[479]= {
			id=479,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[480]= {
			id=480,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[481]= {
			id=481,
			elems= {
					[1]= {name="$55级套装武器",chance=0.15,max=1,min=1,sid=21,type=1,},
					[2]= {name="$60级套装零件",chance=0.15,max=1,min=1,sid=24,type=1,},
				},
			type=1,
		},
	[482]= {
			id=482,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[483]= {
			id=483,
			name="冰麒麟(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=81,min=81,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=1,max=6,min=4,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[5]= {name="祝福油",chance=1,max=6,min=3,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=6,min=3,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=6,min=3,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=6,min=3,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=484,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=485,type=1,},
					[14]= {chance=1,max=1,min=1,sid=486,type=1,},
					[15]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[16]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[17]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[18]= {name="四级灵石",chance=1,max=2,min=1,sid=40003,type=0,},
					[19]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[20]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[21]= {name="$四级魂石",chance=0.55,max=2,min=1,sid=32,type=1,},
					[22]= {chance=1,max=1,min=1,sid=487,type=1,},
				},
			max=81,
			type=0,
		},
	[484]= {
			id=484,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[485]= {
			id=485,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[486]= {
			id=486,
			elems= {
					[1]= {name="$55级套装武器",chance=0.2,max=1,min=1,sid=21,type=1,},
					[2]= {name="$60级套装零件",chance=0.2,max=1,min=1,sid=24,type=1,},
				},
			type=1,
		},
	[487]= {
			id=487,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[488]= {
			id=488,
			name="冰骨魔龙(0-5)",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=81,min=81,sid=77,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=5,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=3,min=2,sid=62,type=1,},
					[5]= {name="祝福油",chance=1,max=5,min=2,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=5,min=2,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=6,min=2,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=489,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=490,type=1,},
					[14]= {name="$55级套装零件",chance=1,max=2,min=1,sid=22,type=1,},
					[15]= {name="$55级套装武器",chance=0.5,max=1,min=1,sid=21,type=1,},
					[16]= {name="$60级套装零件",chance=1,max=1,min=1,sid=24,type=1,},
					[17]= {chance=1,max=1,min=1,sid=491,type=1,},
					[18]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[19]= {name="二级灵石",chance=1,max=3,min=1,sid=40001,type=0,},
					[20]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[21]= {name="四级灵石",chance=1,max=1,min=1,sid=40003,type=0,},
					[22]= {name="五级灵石",chance=1,max=2,min=2,sid=40004,type=0,},
					[23]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[24]= {name="$四级魂石",chance=0.1,max=2,min=1,sid=32,type=1,},
					[25]= {chance=1,max=1,min=1,sid=492,type=1,},
					[26]= {name="附魔强化符",chance=1,max=1,min=1,sid=40149,type=0,},
				},
			max=81,
			type=0,
		},
	[489]= {
			id=489,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[490]= {
			id=490,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[491]= {
			id=491,
			elems= {
					[1]= {name="$60级套装武器",chance=0.05,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.05,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.05,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[492]= {
			id=492,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[493]= {
			id=493,
			name="冰骨魔龙(6-10)",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=81,min=81,sid=77,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=1,max=5,min=3,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=5,min=3,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=5,min=3,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=494,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=495,type=1,},
					[14]= {name="$55级套装零件",chance=1,max=1,min=1,sid=22,type=1,},
					[15]= {name="$55级套装武器",chance=0.55,max=1,min=1,sid=21,type=1,},
					[16]= {name="$60级套装零件",chance=1,max=1,min=1,sid=24,type=1,},
					[17]= {chance=1,max=1,min=1,sid=496,type=1,},
					[18]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[19]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[20]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[21]= {name="四级灵石",chance=1,max=1,min=1,sid=40003,type=0,},
					[22]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[23]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[24]= {name="$四级魂石",chance=0.2,max=2,min=1,sid=32,type=1,},
					[25]= {chance=1,max=1,min=1,sid=497,type=1,},
					[26]= {name="附魔卷",chance=1,max=1,min=1,sid=40148,type=0,},
				},
			max=81,
			type=0,
		},
	[494]= {
			id=494,
			elems= {
					[1]= {name="$50级散件",chance=0.2,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.8,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[495]= {
			id=495,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[496]= {
			id=496,
			elems= {
					[1]= {name="$60级套装武器",chance=0.08,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.08,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.08,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[497]= {
			id=497,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[498]= {
			id=498,
			name="冰骨魔龙(11-15)",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=81,min=81,sid=77,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$中boss掉落常用杂品",chance=1,max=5,min=3,sid=61,type=1,},
					[4]= {name="$中boss掉落稀有杂品",chance=1,max=1,min=1,sid=62,type=1,},
					[5]= {name="祝福油",chance=1,max=5,min=3,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=5,min=3,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=6,min=3,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=499,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=500,type=1,},
					[14]= {name="$55级套装零件",chance=1,max=1,min=1,sid=22,type=1,},
					[15]= {name="$55级套装武器",chance=0.55,max=1,min=1,sid=21,type=1,},
					[16]= {name="$60级套装零件",chance=1,max=1,min=1,sid=24,type=1,},
					[17]= {chance=1,max=1,min=1,sid=501,type=1,},
					[18]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[19]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[20]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[21]= {name="四级灵石",chance=1,max=2,min=1,sid=40003,type=0,},
					[22]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[23]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[24]= {name="$四级魂石",chance=0.3,max=2,min=1,sid=32,type=1,},
					[25]= {chance=1,max=1,min=1,sid=502,type=1,},
					[26]= {name="附魔卷",chance=1,max=1,min=1,sid=40148,type=0,},
				},
			max=81,
			type=0,
		},
	[499]= {
			id=499,
			elems= {
					[1]= {name="$50级散件",chance=0.2,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.8,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[500]= {
			id=500,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[501]= {
			id=501,
			elems= {
					[1]= {name="$60级套装武器",chance=0.11,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.11,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.11,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[502]= {
			id=502,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[503]= {
			id=503,
			name="冰骨魔龙(16-20)",
			coplelem= {
					[1]= {name="$70-75级怪金币",chance=0,max=81,min=81,sid=77,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=8,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=8,sid=39009,type=0,},
					[3]= {name="$大boss掉落常用杂品",chance=1,max=6,min=4,sid=63,type=1,},
					[4]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[5]= {name="祝福油",chance=1,max=6,min=3,sid=30018,type=0,},
					[6]= {name="红玫瑰",chance=1,max=6,min=3,sid=39029,type=0,},
					[7]= {name="宠物项圈",chance=1,max=10,min=5,sid=40053,type=0,},
					[8]= {name="经验灵符",chance=1,max=7,min=2,sid=30064,type=0,},
					[9]= {name="百万经验灵符",chance=1,max=12,min=5,sid=30189,type=0,},
					[10]= {name="千万经验灵符",chance=1,max=6,min=3,sid=30191,type=0,},
					[11]= {chance=1,max=1,min=1,sid=504,type=1,},
					[12]= {name="$50级套装零件",chance=1,max=1,min=1,sid=20,type=1,},
					[13]= {chance=1,max=1,min=1,sid=505,type=1,},
					[14]= {name="$55级套装零件",chance=1,max=1,min=1,sid=22,type=1,},
					[15]= {name="$55级套装武器",chance=0.55,max=1,min=1,sid=21,type=1,},
					[16]= {name="$60级套装零件",chance=1,max=1,min=1,sid=24,type=1,},
					[17]= {chance=1,max=1,min=1,sid=506,type=1,},
					[18]= {name="神圣戒指",chance=1,max=1,min=1,sid=60247,type=0,},
					[19]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[20]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[21]= {name="四级灵石",chance=1,max=2,min=1,sid=40003,type=0,},
					[22]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[23]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[24]= {name="$四级魂石",chance=0.55,max=2,min=1,sid=32,type=1,},
					[25]= {chance=1,max=1,min=1,sid=507,type=1,},
					[26]= {chance=1,max=1,min=1,sid=508,type=1,},
				},
			max=81,
			type=0,
		},
	[504]= {
			id=504,
			elems= {
					[1]= {name="$50级散件",chance=0.2,max=2,min=2,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.8,max=2,min=2,sid=10,type=1,},
				},
			type=1,
		},
	[505]= {
			id=505,
			elems= {
					[1]= {name="$50级套装武器",chance=0.4,max=1,min=1,sid=19,type=1,},
					[2]= {name="$55级套装零件",chance=0.6,max=1,min=1,sid=22,type=1,},
				},
			type=1,
		},
	[506]= {
			id=506,
			elems= {
					[1]= {name="$60级套装武器",chance=0.14,max=1,min=1,sid=23,type=1,},
					[2]= {name="$70级套装零件",chance=0.14,max=1,min=1,sid=26,type=1,},
					[3]= {name="$70级套装武器",chance=0.14,max=1,min=1,sid=25,type=1,},
				},
			type=1,
		},
	[507]= {
			id=507,
			elems= {
					[1]= {name="$一级魂石",chance=0.1,max=3,min=2,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.8,max=2,min=2,sid=30,type=1,},
				},
			type=1,
		},
	[508]= {
			id=508,
			elems= {
					[1]= {name="附魔卷",chance=0.333,max=1,min=1,sid=40148,type=0,},
					[2]= {name="附魔强化符",chance=0.333,max=1,min=1,sid=40149,type=0,},
					[3]= {name="极品附魔符",chance=0.334,max=1,min=1,sid=40150,type=0,},
				},
			type=1,
		},
	[509]= {
			id=509,
			name="沃玛主教",
			coplelem= {
					[1]= {name="$25-30级怪金币",chance=0,max=9,min=9,sid=68,type=1,},
				},
			elems= {
					[1]= {name="行会资格证",chance=0.25,max=1,min=1,sid=40057,type=0,},
					[2]= {name="黑铁",chance=1,max=2,min=1,sid=40008,type=0,},
					[3]= {name="绿宝石",chance=1,max=2,min=1,sid=40009,type=0,},
					[4]= {name="紫晶钻",chance=0.5,max=1,min=1,sid=40010,type=0,},
					[5]= {name="$小boss掉落常用杂品",chance=1,max=1,min=1,sid=59,type=1,},
					[6]= {chance=1,max=1,min=1,sid=510,type=1,},
					[7]= {name="一级灵石",chance=0.05,max=1,min=1,sid=40000,type=0,},
					[8]= {name="$生死状一二",chance=1,max=4,min=2,sid=45,type=1,},
				},
			max=9,
			type=0,
		},
	[510]= {
			id=510,
			elems= {
					[1]= {name="强化保护符",chance=0.1,max=1,min=1,sid=40012,type=0,},
					[2]= {name="鉴定锁",chance=0.1,max=1,min=1,sid=40042,type=0,},
					[3]= {name="清洗丹",chance=0.1,max=1,min=1,sid=40041,type=0,},
				},
			type=1,
		},
	[511]= {
			id=511,
			name="金甲尸王(0-5)",
			elems= {
					[1]= {name="$超级药",chance=1,max=8,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=8,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=2,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.4,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=1,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.25,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0.1,max=1,min=1,sid=40000,type=0,},
					[8]= {chance=1,max=1,min=1,sid=512,type=1,},
					[9]= {name="$生死状一二",chance=1,max=4,min=4,sid=45,type=1,},
					[10]= {name="$35-40级怪金币",chance=0.01,max=25,min=25,sid=70,type=1,},
				},
			max=0,
			type=0,
		},
	[512]= {
			id=512,
			elems= {
					[1]= {name="$一级魂石",chance=0.6,max=1,min=1,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.05,max=1,min=1,sid=30,type=1,},
				},
			type=1,
		},
	[513]= {
			id=513,
			name="金甲尸王(6-10)",
			coplelem= {
					[1]= {name="$40-45级怪金币",chance=0,max=25,min=25,sid=71,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=0.005,max=8,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0.0008,max=8,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=2,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.6,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=1,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.1,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0.0042,max=1,min=1,sid=40000,type=0,},
					[8]= {chance=1,max=1,min=1,sid=514,type=1,},
					[9]= {name="$生死状一二",chance=0.002,max=5,min=4,sid=45,type=1,},
				},
			max=25,
			type=0,
		},
	[514]= {
			id=514,
			elems= {
					[1]= {name="$一级魂石",chance=0.0142,max=1,min=1,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.006,max=1,min=1,sid=30,type=1,},
					[3]= {name="$45级套装",chance=0.0001,max=1,min=1,sid=18,type=1,},
				},
			type=1,
		},
	[515]= {
			id=515,
			name="金甲尸王(11-15)",
			elems= {
					[1]= {name="$超级药",chance=1,max=8,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=8,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=2,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.8,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=0.0075,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.0021,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0.15,max=1,min=1,sid=40000,type=0,},
					[8]= {chance=1,max=1,min=1,sid=516,type=1,},
					[9]= {name="$生死状一二",chance=1,max=5,min=4,sid=45,type=1,},
					[10]= {name="$45-50级怪金币",chance=0.0145,max=25,min=25,sid=72,type=1,},
				},
			max=0,
			type=0,
		},
	[516]= {
			id=516,
			elems= {
					[1]= {name="$一级魂石",chance=0.6,max=2,min=1,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.15,max=1,min=1,sid=30,type=1,},
					[3]= {name="$50级套装零件",chance=0.0001,max=1,min=1,sid=20,type=1,},
				},
			type=1,
		},
	[517]= {
			id=517,
			name="金甲尸王(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=25,min=25,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=0.0065,max=8,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0.003,max=8,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=0.0005,max=2,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.25,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=0.2,max=1,min=1,sid=40000,type=0,},
					[8]= {chance=1,max=1,min=1,sid=518,type=1,},
					[9]= {name="$生死状一二",chance=0.0075,max=6,min=4,sid=45,type=1,},
				},
			max=25,
			type=0,
		},
	[518]= {
			id=518,
			elems= {
					[1]= {name="$一级魂石",chance=0.6,max=2,min=1,sid=29,type=1,},
					[2]= {name="$二级魂石",chance=0.0086,max=1,min=1,sid=30,type=1,},
					[3]= {name="$50级套装零件",chance=0.0002,max=1,min=1,sid=20,type=1,},
					[4]= {name="$55级套装零件",chance=0.0001,max=1,min=1,sid=22,type=1,},
					[5]= {name="$55级套装零件",chance=0.0001,max=1,min=1,sid=22,type=1,},
					[6]= {name="$60级套装零件",chance=0.0001,max=12,min=4,sid=24,type=1,},
				},
			type=1,
		},
	[519]= {
			id=519,
			name="祖玛教皇(0-5)",
			elems= {
					[1]= {name="$超级药",chance=0.0027,max=12,min=5,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0.0008,max=12,min=5,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.5,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.75,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=0.0076,max=1,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.0077,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=0.0043,max=4,min=4,sid=46,type=1,},
					[12]= {name="$50-55级怪金币",chance=0.0025,max=49,min=49,sid=73,type=1,},
				},
			max=0,
			type=0,
		},
	[520]= {
			id=520,
			name="祖玛教皇(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=0.0017,max=12,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=0.0001,max=12,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=5,min=3,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.8,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.1,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[521]= {
			id=521,
			name="祖玛教皇(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=14,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=14,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=4,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.8,max=2,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.15,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[522]= {
			id=522,
			name="祖玛教皇(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=5,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.9,max=2,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.2,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[523]= {
			id=523,
			name="赤练猪卫(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=5,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=5,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.5,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.75,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=1,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.05,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=4,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[524]= {
			id=524,
			name="赤练猪卫(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=5,min=3,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.8,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.1,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[525]= {
			id=525,
			name="赤练猪卫(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=14,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=14,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=4,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.8,max=2,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.15,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=6,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[526]= {
			id=526,
			name="赤练猪卫(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=5,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.9,max=2,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.2,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=6,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[527]= {
			id=527,
			name="邪恶钳虫(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=5,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=5,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.5,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.75,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=1,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.05,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=4,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[528]= {
			id=528,
			name="邪恶钳虫(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=5,min=3,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.8,max=1,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.1,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[529]= {
			id=529,
			name="邪恶钳虫(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=14,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=14,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=4,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.8,max=2,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.15,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[530]= {
			id=530,
			name="邪恶钳虫(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=5,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.9,max=2,min=1,sid=17,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.2,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[531]= {
			id=531,
			name="蚁后(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=5,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=5,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.5,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.75,max=1,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=0.05,max=1,min=1,sid=18,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=1,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=0.05,max=1,min=1,sid=30,type=1,},
					[12]= {name="$生死状二三",chance=1,max=4,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[532]= {
			id=532,
			name="蚁后(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=5,min=3,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$35级散件",chance=1,max=2,min=1,sid=7,type=1,},
					[6]= {name="$40级套装",chance=0.8,max=1,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=0.2,max=1,min=1,sid=18,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=0.1,max=1,min=1,sid=30,type=1,},
					[12]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[533]= {
			id=533,
			name="蚁后(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=14,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=14,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=4,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.15,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=5,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[534]= {
			id=534,
			name="蚁后(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=5,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[6]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
					[7]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[8]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[9]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[10]= {name="$二级魂石",chance=0.2,max=1,min=1,sid=30,type=1,},
					[11]= {name="$生死状二三",chance=1,max=6,min=4,sid=46,type=1,},
				},
			max=49,
			type=0,
		},
	[535]= {
			id=535,
			name="黄泉领主(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=5,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=5,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.5,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=536,type=1,},
					[6]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=0.5,max=1,min=1,sid=18,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=3,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[12]= {name="$三级魂石",chance=0.2,max=1,min=1,sid=31,type=1,},
					[13]= {name="$生死状三四",chance=1,max=4,min=4,sid=47,type=1,},
				},
			max=49,
			type=0,
		},
	[536]= {
			id=536,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[537]= {
			id=537,
			name="黄泉领主(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=5,min=3,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=538,type=1,},
					[6]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=0.8,max=1,min=1,sid=18,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[10]= {name="三级灵石",chance=0.8,max=1,min=1,sid=40002,type=0,},
					[11]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[12]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[13]= {name="$三级魂石",chance=0.6,max=1,min=1,sid=31,type=1,},
					[14]= {name="$生死状三四",chance=1,max=5,min=4,sid=47,type=1,},
				},
			max=49,
			type=0,
		},
	[538]= {
			id=538,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[539]= {
			id=539,
			name="黄泉领主(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=14,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=14,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=4,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=540,type=1,},
					[6]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=0.8,max=2,min=1,sid=18,type=1,},
					[8]= {chance=1,max=1,min=1,sid=541,type=1,},
					[9]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[10]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[11]= {chance=1,max=1,min=1,sid=542,type=1,},
					[12]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[13]= {name="$二级魂石",chance=1,max=2,min=1,sid=30,type=1,},
					[14]= {name="$三级魂石",chance=1,max=1,min=1,sid=31,type=1,},
					[15]= {name="$四级魂石",chance=0.8,max=1,min=1,sid=32,type=1,},
					[16]= {name="$生死状三四",chance=1,max=6,min=4,sid=47,type=1,},
				},
			max=49,
			type=0,
		},
	[540]= {
			id=540,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[541]= {
			id=541,
			elems= {
					[1]= {name="$50级套装零件",chance=0.4,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.1,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[542]= {
			id=542,
			elems= {
					[1]= {name="三级灵石",chance=0.4,max=2,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.12,max=1,min=1,sid=40003,type=0,},
				},
			type=1,
		},
	[543]= {
			id=543,
			name="黄泉领主(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=5,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=544,type=1,},
					[6]= {name="$45级套装",chance=1,max=2,min=1,sid=18,type=1,},
					[7]= {chance=1,max=1,min=1,sid=545,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[10]= {chance=1,max=1,min=1,sid=546,type=1,},
					[11]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[12]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[13]= {chance=1,max=1,min=1,sid=547,type=1,},
					[14]= {name="$生死状三四",chance=1,max=6,min=4,sid=47,type=1,},
				},
			max=49,
			type=0,
		},
	[544]= {
			id=544,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[545]= {
			id=545,
			elems= {
					[1]= {name="$50级套装零件",chance=0.4,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.2,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[546]= {
			id=546,
			elems= {
					[1]= {name="三级灵石",chance=0.4,max=2,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.4,max=1,min=1,sid=40003,type=0,},
				},
			type=1,
		},
	[547]= {
			id=547,
			elems= {
					[1]= {name="$四级魂石",chance=0.4,max=1,min=1,sid=32,type=1,},
					[2]= {name="$五级魂石",chance=0.6,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[548]= {
			id=548,
			name="黑龙教主(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=5,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=5,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.5,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=549,type=1,},
					[6]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=1,max=1,min=1,sid=18,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[10]= {name="$一级魂石",chance=1,max=3,min=1,sid=29,type=1,},
					[11]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[12]= {name="$三级魂石",chance=0.2,max=1,min=1,sid=31,type=1,},
					[13]= {name="$生死状四五",chance=1,max=5,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[549]= {
			id=549,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[550]= {
			id=550,
			name="黑龙教主(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=5,min=3,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=551,type=1,},
					[6]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=1,max=1,min=1,sid=18,type=1,},
					[8]= {name="$50级散件",chance=0.3,max=1,min=1,sid=9,type=1,},
					[9]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[10]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[11]= {name="三级灵石",chance=0.8,max=1,min=1,sid=40002,type=0,},
					[12]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[13]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[14]= {name="$三级魂石",chance=0.6,max=1,min=1,sid=31,type=1,},
					[15]= {name="$生死状四五",chance=1,max=6,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[551]= {
			id=551,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[552]= {
			id=552,
			name="黑龙教主(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=14,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=14,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=4,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=553,type=1,},
					[6]= {name="$40级套装",chance=1,max=2,min=1,sid=17,type=1,},
					[7]= {name="$45级套装",chance=0.8,max=2,min=1,sid=18,type=1,},
					[8]= {chance=1,max=1,min=1,sid=554,type=1,},
					[9]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[10]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[11]= {chance=1,max=1,min=1,sid=555,type=1,},
					[12]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[13]= {name="$二级魂石",chance=1,max=2,min=1,sid=30,type=1,},
					[14]= {name="$三级魂石",chance=1,max=1,min=1,sid=31,type=1,},
					[15]= {name="$四级魂石",chance=0.8,max=1,min=1,sid=32,type=1,},
					[16]= {name="$生死状四五",chance=1,max=6,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[553]= {
			id=553,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[554]= {
			id=554,
			elems= {
					[1]= {name="$50级套装零件",chance=0.6,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.1,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[555]= {
			id=555,
			elems= {
					[1]= {name="三级灵石",chance=0.4,max=2,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.12,max=1,min=1,sid=40003,type=0,},
				},
			type=1,
		},
	[556]= {
			id=556,
			name="黑龙教主(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=5,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=557,type=1,},
					[6]= {name="$45级套装",chance=1,max=2,min=1,sid=18,type=1,},
					[7]= {chance=1,max=1,min=1,sid=558,type=1,},
					[8]= {name="一级灵石",chance=1,max=2,min=2,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[10]= {chance=1,max=1,min=1,sid=559,type=1,},
					[11]= {name="$一级魂石",chance=1,max=2,min=1,sid=29,type=1,},
					[12]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[13]= {chance=1,max=1,min=1,sid=560,type=1,},
					[14]= {name="$生死状四五",chance=1,max=6,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[557]= {
			id=557,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[558]= {
			id=558,
			elems= {
					[1]= {name="$50级套装零件",chance=0.8,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.2,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[559]= {
			id=559,
			elems= {
					[1]= {name="三级灵石",chance=0.4,max=2,min=1,sid=40002,type=0,},
					[2]= {name="四级灵石",chance=0.4,max=1,min=1,sid=40003,type=0,},
				},
			type=1,
		},
	[560]= {
			id=560,
			elems= {
					[1]= {name="$四级魂石",chance=0.4,max=1,min=1,sid=32,type=1,},
					[2]= {name="$五级魂石",chance=0.6,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[561]= {
			id=561,
			name="天龟水神(0-5)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=5,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=5,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=3,min=1,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=0.5,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=562,type=1,},
					[6]= {chance=1,max=1,min=1,sid=563,type=1,},
					[7]= {chance=1,max=1,min=1,sid=564,type=1,},
					[8]= {name="一级灵石",chance=1,max=1,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=2,min=1,sid=40001,type=0,},
					[10]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[11]= {name="四级灵石",chance=1,max=2,min=1,sid=40003,type=0,},
					[12]= {name="五级灵石",chance=0.3,max=1,min=1,sid=40004,type=0,},
					[13]= {name="$二级魂石",chance=1,max=3,min=2,sid=30,type=1,},
					[14]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[15]= {name="$四级魂石",chance=1,max=2,min=1,sid=32,type=1,},
					[16]= {name="$五级魂石",chance=0.7,max=1,min=1,sid=33,type=1,},
					[17]= {name="$生死状四五",chance=1,max=5,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[562]= {
			id=562,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[563]= {
			id=563,
			elems= {
					[1]= {name="$50级套装零件",chance=0.9,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.1,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[564]= {
			id=564,
			elems= {
					[1]= {name="$55级套装零件",chance=0.85,max=1,min=1,sid=22,type=1,},
					[2]= {name="$55级套装武器",chance=0.15,max=1,min=1,sid=21,type=1,},
				},
			type=1,
		},
	[565]= {
			id=565,
			name="天龟水神(6-10)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=12,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=12,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=5,min=3,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=566,type=1,},
					[6]= {chance=1,max=1,min=1,sid=567,type=1,},
					[7]= {chance=1,max=1,min=1,sid=568,type=1,},
					[8]= {name="二级灵石",chance=1,max=2,min=2,sid=40001,type=0,},
					[9]= {name="三级灵石",chance=1,max=3,min=2,sid=40002,type=0,},
					[10]= {name="四级灵石",chance=1,max=2,min=1,sid=40003,type=0,},
					[11]= {name="五级灵石",chance=0.4,max=1,min=1,sid=40004,type=0,},
					[12]= {name="$二级魂石",chance=1,max=1,min=1,sid=30,type=1,},
					[13]= {name="$三级魂石",chance=1,max=3,min=1,sid=31,type=1,},
					[14]= {name="$四级魂石",chance=1,max=2,min=1,sid=32,type=1,},
					[15]= {name="$五级魂石",chance=1,max=1,min=1,sid=33,type=1,},
					[16]= {name="$生死状四五",chance=1,max=6,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[566]= {
			id=566,
			elems= {
					[1]= {name="$50级散件",chance=0.6,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.4,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[567]= {
			id=567,
			elems= {
					[1]= {name="$50级套装零件",chance=0.9,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.1,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[568]= {
			id=568,
			elems= {
					[1]= {name="$55级套装零件",chance=0.8,max=1,min=1,sid=22,type=1,},
					[2]= {name="$55级套装武器",chance=0.2,max=1,min=1,sid=21,type=1,},
				},
			type=1,
		},
	[569]= {
			id=569,
			name="天龟水神(11-15)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=14,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=14,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=4,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=570,type=1,},
					[6]= {chance=1,max=1,min=1,sid=571,type=1,},
					[7]= {chance=1,max=1,min=1,sid=572,type=1,},
					[8]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[9]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[10]= {name="四级灵石",chance=1,max=3,min=2,sid=40003,type=0,},
					[11]= {name="五级灵石",chance=0.5,max=1,min=1,sid=40004,type=0,},
					[12]= {name="$二级魂石",chance=1,max=2,min=1,sid=30,type=1,},
					[13]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[14]= {name="$四级魂石",chance=1,max=2,min=1,sid=32,type=1,},
					[15]= {chance=1,max=1,min=1,sid=573,type=1,},
					[16]= {name="$生死状四五",chance=1,max=6,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[570]= {
			id=570,
			elems= {
					[1]= {name="$50级散件",chance=0.4,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.6,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[571]= {
			id=571,
			elems= {
					[1]= {name="$50级套装零件",chance=0.9,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.1,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[572]= {
			id=572,
			elems= {
					[1]= {name="$55级套装零件",chance=0.77,max=1,min=1,sid=22,type=1,},
					[2]= {name="$55级套装武器",chance=0.23,max=1,min=1,sid=21,type=1,},
				},
			type=1,
		},
	[573]= {
			id=573,
			elems= {
					[1]= {name="$五级魂石",chance=0.8,max=1,min=1,sid=33,type=1,},
					[2]= {name="$六级魂石",chance=0.2,max=1,min=1,sid=34,type=1,},
				},
			type=1,
		},
	[574]= {
			id=574,
			name="天龟水神(16-20)",
			coplelem= {
					[1]= {name="$50-55级怪金币",chance=0,max=49,min=49,sid=73,type=1,},
				},
			elems= {
					[1]= {name="$超级药",chance=1,max=15,min=4,sid=1,type=1,},
					[2]= {name="强效太阳水",chance=1,max=15,min=4,sid=39009,type=0,},
					[3]= {name="$小boss掉落常用杂品",chance=1,max=6,min=5,sid=59,type=1,},
					[4]= {name="$小boss掉落稀有杂品",chance=1,max=1,min=1,sid=60,type=1,},
					[5]= {chance=1,max=1,min=1,sid=575,type=1,},
					[6]= {chance=1,max=1,min=1,sid=576,type=1,},
					[7]= {chance=1,max=1,min=1,sid=577,type=1,},
					[8]= {name="一级灵石",chance=1,max=1,min=1,sid=40000,type=0,},
					[9]= {name="二级灵石",chance=1,max=1,min=1,sid=40001,type=0,},
					[10]= {name="三级灵石",chance=1,max=2,min=1,sid=40002,type=0,},
					[11]= {name="四级灵石",chance=1,max=3,min=2,sid=40003,type=0,},
					[12]= {name="五级灵石",chance=0.6,max=1,min=1,sid=40004,type=0,},
					[13]= {name="$二级魂石",chance=1,max=2,min=1,sid=30,type=1,},
					[14]= {name="$三级魂石",chance=1,max=2,min=1,sid=31,type=1,},
					[15]= {name="$四级魂石",chance=1,max=2,min=1,sid=32,type=1,},
					[16]= {chance=1,max=1,min=1,sid=578,type=1,},
					[17]= {name="$生死状四五",chance=1,max=6,min=4,sid=48,type=1,},
				},
			max=49,
			type=0,
		},
	[575]= {
			id=575,
			elems= {
					[1]= {name="$50级散件",chance=0.3,max=2,min=1,sid=9,type=1,},
					[2]= {name="$55级散件",chance=0.7,max=2,min=1,sid=10,type=1,},
				},
			type=1,
		},
	[576]= {
			id=576,
			elems= {
					[1]= {name="$50级套装零件",chance=0.9,max=1,min=1,sid=20,type=1,},
					[2]= {name="$50级套装武器",chance=0.1,max=1,min=1,sid=19,type=1,},
				},
			type=1,
		},
	[577]= {
			id=577,
			elems= {
					[1]= {name="$55级套装零件",chance=0.75,max=1,min=1,sid=22,type=1,},
					[2]= {name="$55级套装武器",chance=0.25,max=1,min=1,sid=21,type=1,},
				},
			type=1,
		},
	[578]= {
			id=578,
			elems= {
					[1]= {name="$五级魂石",chance=0.75,max=1,min=1,sid=33,type=1,},
					[2]= {name="$六级魂石",chance=0.25,max=1,min=1,sid=34,type=1,},
				},
			type=1,
		},
	[579]= {
			id=579,
			name="1阶寻宝物品道具",
			elems= {
					[1]= {name="金币箱",chance=0.0185,max=1,min=1,sid=30058,type=0,},
					[2]= {name="荣誉令",chance=0.0085,max=1,min=1,sid=30214,type=0,},
					[3]= {name="1000荣誉",chance=0.0486,max=1,min=1,sid=30208,type=0,},
					[4]= {name="5000荣誉",chance=0.0286,max=1,min=1,sid=30207,type=0,},
					[5]= {name="10000荣誉",chance=0.0085,max=1,min=1,sid=30206,type=0,},
					[6]= {name="仙玉票",chance=0.0061,max=1,min=1,sid=30215,type=0,},
					[7]= {name="经验灵符",chance=0.0286,max=1,min=1,sid=30064,type=0,},
					[8]= {name="百万经验灵符",chance=0.0486,max=1,min=1,sid=30189,type=0,},
					[9]= {name="千万经验灵符",chance=0.0085,max=1,min=1,sid=30191,type=0,},
					[10]= {name="宠物项圈",chance=0.0486,max=1,min=1,sid=40053,type=0,},
					[11]= {name="攻击药水(大)",chance=0.0285,max=1,min=1,sid=39038,type=0,},
					[12]= {name="防御药水(大)",chance=0.0285,max=1,min=1,sid=39027,type=0,},
					[13]= {name="超级苹果",chance=0.0185,max=1,min=1,sid=30051,type=0,},
					[14]= {name="苹果",chance=0.0286,max=1,min=1,sid=30046,type=0,},
					[15]= {name="9朵红玫瑰",chance=0.0488,max=1,min=1,sid=40081,type=0,},
					[16]= {name="强效红玫瑰",chance=0.0387,max=1,min=1,sid=39042,type=0,},
					[17]= {name="超级红玫瑰",chance=0.0285,max=1,min=1,sid=39043,type=0,},
					[18]= {name="战神油",chance=0.0285,max=1,min=1,sid=30017,type=0,},
					[19]= {name="3倍经验神符",chance=0.0388,max=1,min=1,sid=30002,type=0,},
					[20]= {name="4倍经验神符",chance=0.0287,max=1,min=1,sid=30003,type=0,},
					[21]= {name="8倍经验神符",chance=0.0185,max=1,min=1,sid=30004,type=0,},
					[22]= {name="5倍经验神符",chance=0.0285,max=1,min=1,sid=30005,type=0,},
					[23]= {name="6倍经验神符",chance=0.0285,max=1,min=1,sid=30054,type=0,},
					[24]= {name="10倍经验神符",chance=0.0085,max=1,min=1,sid=30055,type=0,},
					[25]= {name="4倍经验神符(8小时)",chance=0.0385,max=1,min=1,sid=30161,type=0,},
					[26]= {name="6倍经验神符(8小时)",chance=0.0085,max=1,min=1,sid=30162,type=0,},
					[27]= {name="5倍经验神符(8小时)",chance=0.0185,max=1,min=1,sid=30165,type=0,},
					[28]= {name="100倍经验神符(8小时)",chance=0.0185,max=1,min=1,sid=30164,type=0,},
					[29]= {name="万年人参",chance=0.0387,max=1,min=1,sid=39017,type=0,},
					[30]= {name="万年雪莲",chance=0.0387,max=1,min=1,sid=39021,type=0,},
					[31]= {name="人参王",chance=0.0287,max=1,min=1,sid=39018,type=0,},
					[32]= {name="雪莲王",chance=0.0287,max=1,min=1,sid=39022,type=0,},
					[33]= {name="强化保护符",chance=0.0385,max=1,min=1,sid=40012,type=0,},
					[34]= {name="翅膀合成符",chance=0.0185,max=1,min=1,sid=40013,type=0,},
					[35]= {name="附魔卷",chance=0.01,max=1,min=1,sid=40148,type=0,},
					[36]= {name="清洗丹",chance=0.0185,max=1,min=1,sid=40041,type=0,},
				},
			type=1,
		},
	[580]= {
			id=580,
			name="1阶寻宝灵珠",
			elems= {
					[1]= {name="一级灵石",chance=0.32,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0.375,max=1,min=1,sid=40001,type=0,},
					[3]= {name="三级灵石",chance=0.22,max=1,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.07,max=1,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.015,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[581]= {
			id=581,
			name="2阶寻宝灵珠",
			elems= {
					[1]= {name="一级灵石",chance=0.32,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0.37,max=1,min=1,sid=40001,type=0,},
					[3]= {name="三级灵石",chance=0.225,max=1,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.07,max=1,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.015,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[582]= {
			id=582,
			name="3阶寻宝灵珠",
			elems= {
					[1]= {name="一级灵石",chance=0.32,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0.37,max=1,min=1,sid=40001,type=0,},
					[3]= {name="三级灵石",chance=0.22,max=1,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.075,max=1,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.015,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[583]= {
			id=583,
			name="4阶寻宝灵珠",
			elems= {
					[1]= {name="一级灵石",chance=0.31,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0.37,max=1,min=1,sid=40001,type=0,},
					[3]= {name="三级灵石",chance=0.23,max=1,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.075,max=1,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.015,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[584]= {
			id=584,
			name="5阶寻宝灵珠",
			elems= {
					[1]= {name="一级灵石",chance=0.309,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0.37,max=1,min=1,sid=40001,type=0,},
					[3]= {name="三级灵石",chance=0.23,max=1,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.075,max=1,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.016,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[585]= {
			id=585,
			name="6阶寻宝灵珠",
			elems= {
					[1]= {name="一级灵石",chance=0.308,max=1,min=1,sid=40000,type=0,},
					[2]= {name="二级灵石",chance=0.37,max=1,min=1,sid=40001,type=0,},
					[3]= {name="三级灵石",chance=0.23,max=1,min=1,sid=40002,type=0,},
					[4]= {name="四级灵石",chance=0.075,max=1,min=1,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=0.017,max=1,min=1,sid=40004,type=0,},
				},
			type=1,
		},
	[586]= {
			id=586,
			name="1阶寻宝魂石",
			elems= {
					[1]= {name="$二级魂石",chance=0.56,max=1,min=1,sid=30,type=1,},
					[2]= {name="$三级魂石",chance=0.3,max=1,min=1,sid=31,type=1,},
					[3]= {name="$四级魂石",chance=0.12,max=1,min=1,sid=32,type=1,},
					[4]= {name="$五级魂石",chance=0.02,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[587]= {
			id=587,
			name="2阶寻宝魂石",
			elems= {
					[1]= {name="$二级魂石",chance=0.55,max=1,min=1,sid=30,type=1,},
					[2]= {name="$三级魂石",chance=0.3,max=1,min=1,sid=31,type=1,},
					[3]= {name="$四级魂石",chance=0.125,max=1,min=1,sid=32,type=1,},
					[4]= {name="$五级魂石",chance=0.025,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[588]= {
			id=588,
			name="3阶寻宝魂石",
			elems= {
					[1]= {name="$二级魂石",chance=0.55,max=1,min=1,sid=30,type=1,},
					[2]= {name="$三级魂石",chance=0.295,max=1,min=1,sid=31,type=1,},
					[3]= {name="$四级魂石",chance=0.13,max=1,min=1,sid=32,type=1,},
					[4]= {name="$五级魂石",chance=0.025,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[589]= {
			id=589,
			name="4阶寻宝魂石",
			elems= {
					[1]= {name="$二级魂石",chance=0.545,max=1,min=1,sid=30,type=1,},
					[2]= {name="$三级魂石",chance=0.295,max=1,min=1,sid=31,type=1,},
					[3]= {name="$四级魂石",chance=0.13,max=1,min=1,sid=32,type=1,},
					[4]= {name="$五级魂石",chance=0.03,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[590]= {
			id=590,
			name="5阶寻宝魂石",
			elems= {
					[1]= {name="$二级魂石",chance=0.545,max=1,min=1,sid=30,type=1,},
					[2]= {name="$三级魂石",chance=0.29,max=1,min=1,sid=31,type=1,},
					[3]= {name="$四级魂石",chance=0.135,max=1,min=1,sid=32,type=1,},
					[4]= {name="$五级魂石",chance=0.03,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[591]= {
			id=591,
			name="6阶寻宝魂石",
			elems= {
					[1]= {name="$二级魂石",chance=0.545,max=1,min=1,sid=30,type=1,},
					[2]= {name="$三级魂石",chance=0.29,max=1,min=1,sid=31,type=1,},
					[3]= {name="$四级魂石",chance=0.135,max=1,min=1,sid=32,type=1,},
					[4]= {name="$五级魂石",chance=0.03,max=1,min=1,sid=33,type=1,},
				},
			type=1,
		},
	[592]= {
			id=592,
			name="寻宝戒指",
			elems= {
					[1]= {name="复生戒指",chance=0.333,max=1,min=1,sid=60223,type=0,},
					[2]= {name="定身戒指",chance=0.334,max=1,min=1,sid=60231,type=0,},
					[3]= {name="护法戒指",chance=0.333,max=1,min=1,sid=60239,type=0,},
				},
			type=1,
		},
	[593]= {
			id=593,
			name="寻宝40级套装",
			elems= {
					[1]= {name="朝夕百花",chance=0.02,max=1,min=1,sid=60000,type=0,},
					[2]= {name="八卦錾金头盔",chance=0.03,max=1,min=1,sid=60001,type=0,},
					[3]= {name="八卦錾金道衣(男)",chance=0.03,max=1,min=1,sid=60002,type=0,},
					[4]= {name="八卦錾金道衣(女)",chance=0.03,max=1,min=1,sid=60003,type=0,},
					[5]= {name="八卦錾金项链",chance=0.03,max=1,min=1,sid=60004,type=0,},
					[6]= {name="八卦錾金手镯",chance=0.03,max=1,min=1,sid=60005,type=0,},
					[7]= {name="八卦錾金宝石",chance=0.03,max=1,min=1,sid=60006,type=0,},
					[8]= {name="八卦錾金道鞋",chance=0.034,max=1,min=1,sid=60007,type=0,},
					[9]= {name="八卦錾金腰带",chance=0.04,max=1,min=1,sid=60008,type=0,},
					[10]= {name="降魔引魂",chance=0.02,max=1,min=1,sid=60060,type=0,},
					[11]= {name="星瀚幽路头盔",chance=0.03,max=1,min=1,sid=60061,type=0,},
					[12]= {name="星瀚幽路战甲(男)",chance=0.03,max=1,min=1,sid=60062,type=0,},
					[13]= {name="星瀚幽路战甲(女)",chance=0.03,max=1,min=1,sid=60063,type=0,},
					[14]= {name="星瀚幽路项链",chance=0.03,max=1,min=1,sid=60064,type=0,},
					[15]= {name="星瀚幽路护腕",chance=0.03,max=1,min=1,sid=60065,type=0,},
					[16]= {name="星瀚幽路宝石",chance=0.03,max=1,min=1,sid=60066,type=0,},
					[17]= {name="星瀚幽路战靴",chance=0.033,max=1,min=1,sid=60067,type=0,},
					[18]= {name="星瀚幽路腰带",chance=0.04,max=1,min=1,sid=60068,type=0,},
					[19]= {name="混元蚀日",chance=0.02,max=1,min=1,sid=60120,type=0,},
					[20]= {name="碎寂震天头盔",chance=0.03,max=1,min=1,sid=60121,type=0,},
					[21]= {name="碎寂震天魔袍(男)",chance=0.03,max=1,min=1,sid=60122,type=0,},
					[22]= {name="碎寂震天魔袍(女)",chance=0.03,max=1,min=1,sid=60123,type=0,},
					[23]= {name="碎寂震天项链",chance=0.03,max=1,min=1,sid=60124,type=0,},
					[24]= {name="碎寂震天手镯",chance=0.03,max=1,min=1,sid=60125,type=0,},
					[25]= {name="碎寂震天宝石",chance=0.03,max=1,min=1,sid=60126,type=0,},
					[26]= {name="碎寂震天法履",chance=0.033,max=1,min=1,sid=60127,type=0,},
					[27]= {name="碎寂震天腰带",chance=0.04,max=1,min=1,sid=60128,type=0,},
					[28]= {name="道宗勋章",chance=0.03,max=1,min=1,sid=70138,type=0,},
					[29]= {name="武宗勋章",chance=0.03,max=1,min=1,sid=70147,type=0,},
					[30]= {name="法宗勋章",chance=0.03,max=1,min=1,sid=70156,type=0,},
					[31]= {name="八卦錾金戒指",chance=0.03,max=1,min=1,sid=60202,type=0,},
					[32]= {name="星瀚幽路戒指",chance=0.03,max=1,min=1,sid=60209,type=0,},
					[33]= {name="碎寂震天戒指",chance=0.03,max=1,min=1,sid=60216,type=0,},
				},
			type=1,
		},
	[594]= {
			id=594,
			name="寻宝45级套装",
			elems= {
					[1]= {name="游龙戏凤",chance=0.02,max=1,min=1,sid=60010,type=0,},
					[2]= {name="光华若木头盔",chance=0.03,max=1,min=1,sid=60011,type=0,},
					[3]= {name="光华若木道衣(男)",chance=0.03,max=1,min=1,sid=60012,type=0,},
					[4]= {name="光华若木道衣(女)",chance=0.03,max=1,min=1,sid=60013,type=0,},
					[5]= {name="光华若木项链",chance=0.03,max=1,min=1,sid=60014,type=0,},
					[6]= {name="光华若木手镯",chance=0.03,max=1,min=1,sid=60015,type=0,},
					[7]= {name="光华若木宝石",chance=0.03,max=1,min=1,sid=60016,type=0,},
					[8]= {name="光华若木道鞋",chance=0.034,max=1,min=1,sid=60017,type=0,},
					[9]= {name="光华若木腰带",chance=0.04,max=1,min=1,sid=60018,type=0,},
					[10]= {name="晃金摘星",chance=0.02,max=1,min=1,sid=60070,type=0,},
					[11]= {name="离情霜月头盔",chance=0.03,max=1,min=1,sid=60071,type=0,},
					[12]= {name="离情霜月战甲(男)",chance=0.03,max=1,min=1,sid=60072,type=0,},
					[13]= {name="离情霜月战甲(女)",chance=0.03,max=1,min=1,sid=60073,type=0,},
					[14]= {name="离情霜月项链",chance=0.03,max=1,min=1,sid=60074,type=0,},
					[15]= {name="离情霜月手镯",chance=0.03,max=1,min=1,sid=60075,type=0,},
					[16]= {name="离情霜月宝石",chance=0.03,max=1,min=1,sid=60076,type=0,},
					[17]= {name="离情霜月战靴",chance=0.033,max=1,min=1,sid=60077,type=0,},
					[18]= {name="离情霜月腰带",chance=0.04,max=1,min=1,sid=60078,type=0,},
					[19]= {name="飞星舞雪",chance=0.02,max=1,min=1,sid=60130,type=0,},
					[20]= {name="夜灵啸日头盔",chance=0.03,max=1,min=1,sid=60131,type=0,},
					[21]= {name="夜灵啸日魔袍(男)",chance=0.03,max=1,min=1,sid=60132,type=0,},
					[22]= {name="夜灵啸日魔袍(女)",chance=0.03,max=1,min=1,sid=60133,type=0,},
					[23]= {name="夜灵啸日项链",chance=0.03,max=1,min=1,sid=60134,type=0,},
					[24]= {name="夜灵啸日手镯",chance=0.03,max=1,min=1,sid=60135,type=0,},
					[25]= {name="夜灵啸日宝石",chance=0.03,max=1,min=1,sid=60136,type=0,},
					[26]= {name="夜灵啸日法履",chance=0.033,max=1,min=1,sid=60137,type=0,},
					[27]= {name="夜灵啸日腰带",chance=0.04,max=1,min=1,sid=60138,type=0,},
					[28]= {name="道圣勋章",chance=0.03,max=1,min=1,sid=70139,type=0,},
					[29]= {name="武圣勋章",chance=0.03,max=1,min=1,sid=70148,type=0,},
					[30]= {name="法圣勋章",chance=0.03,max=1,min=1,sid=70157,type=0,},
					[31]= {name="光华若木戒指",chance=0.03,max=1,min=1,sid=60203,type=0,},
					[32]= {name="离情霜月戒指",chance=0.03,max=1,min=1,sid=60210,type=0,},
					[33]= {name="夜灵啸日戒指",chance=0.03,max=1,min=1,sid=60217,type=0,},
				},
			type=1,
		},
	[595]= {
			id=595,
			name="寻宝50级套装",
			elems= {
					[1]= {name="无极牧歌",chance=0.02,max=1,min=1,sid=60020,type=0,},
					[2]= {name="九霄残月头盔",chance=0.03,max=1,min=1,sid=60021,type=0,},
					[3]= {name="九霄残月道衣(男)",chance=0.03,max=1,min=1,sid=60022,type=0,},
					[4]= {name="九霄残月道衣(女)",chance=0.03,max=1,min=1,sid=60023,type=0,},
					[5]= {name="九霄残月项链",chance=0.03,max=1,min=1,sid=60024,type=0,},
					[6]= {name="九霄残月手镯",chance=0.03,max=1,min=1,sid=60025,type=0,},
					[7]= {name="九霄残月宝石",chance=0.03,max=1,min=1,sid=60026,type=0,},
					[8]= {name="九霄残月道鞋",chance=0.034,max=1,min=1,sid=60027,type=0,},
					[9]= {name="九霄残月腰带",chance=0.04,max=1,min=1,sid=60028,type=0,},
					[10]= {name="紫电噬日",chance=0.02,max=1,min=1,sid=60080,type=0,},
					[11]= {name="浮犀焰阳头盔",chance=0.03,max=1,min=1,sid=60081,type=0,},
					[12]= {name="浮犀焰阳战甲(男)",chance=0.03,max=1,min=1,sid=60082,type=0,},
					[13]= {name="浮犀焰阳战甲(女)",chance=0.03,max=1,min=1,sid=60083,type=0,},
					[14]= {name="浮犀焰阳项链",chance=0.03,max=1,min=1,sid=60084,type=0,},
					[15]= {name="浮犀焰阳手镯",chance=0.03,max=1,min=1,sid=60085,type=0,},
					[16]= {name="浮犀焰阳宝石",chance=0.03,max=1,min=1,sid=60086,type=0,},
					[17]= {name="浮犀焰阳战靴",chance=0.033,max=1,min=1,sid=60087,type=0,},
					[18]= {name="浮犀焰阳腰带",chance=0.04,max=1,min=1,sid=60088,type=0,},
					[19]= {name="冰海潮生",chance=0.02,max=1,min=1,sid=60140,type=0,},
					[20]= {name="雪蛊霜寒头盔",chance=0.03,max=1,min=1,sid=60141,type=0,},
					[21]= {name="雪蛊霜寒魔袍(男)",chance=0.03,max=1,min=1,sid=60142,type=0,},
					[22]= {name="雪蛊霜寒魔袍(女)",chance=0.03,max=1,min=1,sid=60143,type=0,},
					[23]= {name="雪蛊霜寒项链",chance=0.03,max=1,min=1,sid=60144,type=0,},
					[24]= {name="雪蛊霜寒手镯",chance=0.03,max=1,min=1,sid=60145,type=0,},
					[25]= {name="雪蛊霜寒宝石",chance=0.03,max=1,min=1,sid=60146,type=0,},
					[26]= {name="雪蛊霜寒魔鞋",chance=0.033,max=1,min=1,sid=60147,type=0,},
					[27]= {name="雪蛊霜寒腰带",chance=0.04,max=1,min=1,sid=60148,type=0,},
					[28]= {name="道尊勋章",chance=0.03,max=1,min=1,sid=70140,type=0,},
					[29]= {name="武尊勋章",chance=0.03,max=1,min=1,sid=70149,type=0,},
					[30]= {name="法尊勋章",chance=0.03,max=1,min=1,sid=70158,type=0,},
					[31]= {name="九霄残月戒指",chance=0.03,max=1,min=1,sid=60204,type=0,},
					[32]= {name="浮犀焰阳戒指",chance=0.03,max=1,min=1,sid=60211,type=0,},
					[33]= {name="雪蛊霜寒戒指",chance=0.03,max=1,min=1,sid=60218,type=0,},
				},
			type=1,
		},
	[596]= {
			id=596,
			name="寻宝55级套装",
			elems= {
					[1]= {name="阴阳鸣鸿",chance=0.02,max=1,min=1,sid=60030,type=0,},
					[2]= {name="冥火薄天头盔",chance=0.03,max=1,min=1,sid=60031,type=0,},
					[3]= {name="冥火薄天道袍(男)",chance=0.03,max=1,min=1,sid=60032,type=0,},
					[4]= {name="冥火薄天道袍(女)",chance=0.03,max=1,min=1,sid=60033,type=0,},
					[5]= {name="冥火薄天项链",chance=0.03,max=1,min=1,sid=60034,type=0,},
					[6]= {name="冥火薄天手镯",chance=0.03,max=1,min=1,sid=60035,type=0,},
					[7]= {name="冥火薄天宝石",chance=0.03,max=1,min=1,sid=60036,type=0,},
					[8]= {name="冥火薄天道鞋",chance=0.034,max=1,min=1,sid=60037,type=0,},
					[9]= {name="冥火薄天腰带",chance=0.04,max=1,min=1,sid=60038,type=0,},
					[10]= {name="盘龙惊鸿",chance=0.02,max=1,min=1,sid=60090,type=0,},
					[11]= {name="青虹北斗头盔",chance=0.03,max=1,min=1,sid=60091,type=0,},
					[12]= {name="青虹北斗战甲(男)",chance=0.03,max=1,min=1,sid=60092,type=0,},
					[13]= {name="青虹北斗战甲(女)",chance=0.03,max=1,min=1,sid=60093,type=0,},
					[14]= {name="青虹北斗项链",chance=0.03,max=1,min=1,sid=60094,type=0,},
					[15]= {name="青虹北斗手镯",chance=0.03,max=1,min=1,sid=60095,type=0,},
					[16]= {name="青虹北斗宝石",chance=0.03,max=1,min=1,sid=60096,type=0,},
					[17]= {name="青虹北斗战靴",chance=0.033,max=1,min=1,sid=60097,type=0,},
					[18]= {name="青虹北斗腰带",chance=0.04,max=1,min=1,sid=60098,type=0,},
					[19]= {name="苍雷万里",chance=0.02,max=1,min=1,sid=60150,type=0,},
					[20]= {name="无量沧海头盔",chance=0.03,max=1,min=1,sid=60151,type=0,},
					[21]= {name="无量沧海魔袍(男)",chance=0.03,max=1,min=1,sid=60152,type=0,},
					[22]= {name="无量沧海魔袍(女)",chance=0.03,max=1,min=1,sid=60153,type=0,},
					[23]= {name="无量沧海项链",chance=0.03,max=1,min=1,sid=60154,type=0,},
					[24]= {name="无量沧海手镯",chance=0.03,max=1,min=1,sid=60155,type=0,},
					[25]= {name="无量沧海宝石",chance=0.03,max=1,min=1,sid=60156,type=0,},
					[26]= {name="无量沧海法履",chance=0.033,max=1,min=1,sid=60157,type=0,},
					[27]= {name="无量沧海腰带",chance=0.04,max=1,min=1,sid=60158,type=0,},
					[28]= {name="道皇勋章",chance=0.03,max=1,min=1,sid=70141,type=0,},
					[29]= {name="武皇勋章",chance=0.03,max=1,min=1,sid=70150,type=0,},
					[30]= {name="法皇勋章",chance=0.03,max=1,min=1,sid=70159,type=0,},
					[31]= {name="冥火薄天戒指",chance=0.03,max=1,min=1,sid=60205,type=0,},
					[32]= {name="青虹北斗戒指",chance=0.03,max=1,min=1,sid=60212,type=0,},
					[33]= {name="无量沧海戒指",chance=0.03,max=1,min=1,sid=60219,type=0,},
				},
			type=1,
		},
	[597]= {
			id=597,
			name="寻宝60级套装",
			elems= {
					[1]= {name="仙人指路",chance=0.02,max=1,min=1,sid=60040,type=0,},
					[2]= {name="百鬼夜宴头盔",chance=0.03,max=1,min=1,sid=60041,type=0,},
					[3]= {name="百鬼夜宴道袍(男)",chance=0.03,max=1,min=1,sid=60042,type=0,},
					[4]= {name="百鬼夜宴道袍(女)",chance=0.03,max=1,min=1,sid=60043,type=0,},
					[5]= {name="百鬼夜宴项链",chance=0.03,max=1,min=1,sid=60044,type=0,},
					[6]= {name="百鬼夜宴手镯",chance=0.03,max=1,min=1,sid=60045,type=0,},
					[7]= {name="百鬼夜宴宝石",chance=0.03,max=1,min=1,sid=60046,type=0,},
					[8]= {name="百鬼夜宴道鞋",chance=0.034,max=1,min=1,sid=60047,type=0,},
					[9]= {name="百鬼夜宴腰带",chance=0.04,max=1,min=1,sid=60048,type=0,},
					[10]= {name="五虎断岳",chance=0.02,max=1,min=1,sid=60100,type=0,},
					[11]= {name="天龙神锢头盔",chance=0.03,max=1,min=1,sid=60101,type=0,},
					[12]= {name="天龙神锢战甲(男)",chance=0.03,max=1,min=1,sid=60102,type=0,},
					[13]= {name="天龙神锢战甲(女)",chance=0.03,max=1,min=1,sid=60103,type=0,},
					[14]= {name="天龙神锢项链",chance=0.03,max=1,min=1,sid=60104,type=0,},
					[15]= {name="天龙神锢手镯",chance=0.03,max=1,min=1,sid=60105,type=0,},
					[16]= {name="天龙神锢宝石",chance=0.03,max=1,min=1,sid=60106,type=0,},
					[17]= {name="天龙神锢战靴",chance=0.033,max=1,min=1,sid=60107,type=0,},
					[18]= {name="天龙神锢腰带",chance=0.04,max=1,min=1,sid=60108,type=0,},
					[19]= {name="离火薄天",chance=0.02,max=1,min=1,sid=60160,type=0,},
					[20]= {name="五法青云头盔",chance=0.03,max=1,min=1,sid=60161,type=0,},
					[21]= {name="五法青云魔袍(男)",chance=0.03,max=1,min=1,sid=60162,type=0,},
					[22]= {name="五法青云魔袍(女)",chance=0.03,max=1,min=1,sid=60163,type=0,},
					[23]= {name="五法青云项链",chance=0.03,max=1,min=1,sid=60164,type=0,},
					[24]= {name="五法青云手镯",chance=0.03,max=1,min=1,sid=60165,type=0,},
					[25]= {name="五法青云宝石",chance=0.03,max=1,min=1,sid=60166,type=0,},
					[26]= {name="五法青云法履",chance=0.033,max=1,min=1,sid=60167,type=0,},
					[27]= {name="五法青云腰带",chance=0.04,max=1,min=1,sid=60168,type=0,},
					[28]= {name="道神勋章",chance=0.03,max=1,min=1,sid=70142,type=0,},
					[29]= {name="武神勋章",chance=0.03,max=1,min=1,sid=70151,type=0,},
					[30]= {name="法神勋章",chance=0.03,max=1,min=1,sid=70160,type=0,},
					[31]= {name="百鬼夜宴戒指",chance=0.03,max=1,min=1,sid=60206,type=0,},
					[32]= {name="天龙神锢戒指",chance=0.03,max=1,min=1,sid=60213,type=0,},
					[33]= {name="五法青云戒指",chance=0.03,max=1,min=1,sid=60220,type=0,},
				},
			type=1,
		},
	[598]= {
			id=598,
			name="寻宝70级套装",
			elems= {
					[1]= {name="缚神揽月",chance=0.02,max=1,min=1,sid=60050,type=0,},
					[2]= {name="太极逍遥头盔",chance=0.03,max=1,min=1,sid=60051,type=0,},
					[3]= {name="太极逍遥道衣(男)",chance=0.03,max=1,min=1,sid=60052,type=0,},
					[4]= {name="太极逍遥道衣(女)",chance=0.03,max=1,min=1,sid=60053,type=0,},
					[5]= {name="太极逍遥项链",chance=0.03,max=1,min=1,sid=60054,type=0,},
					[6]= {name="太极逍遥手镯",chance=0.03,max=1,min=1,sid=60055,type=0,},
					[7]= {name="太极逍遥宝石",chance=0.03,max=1,min=1,sid=60056,type=0,},
					[8]= {name="太极逍遥道鞋",chance=0.034,max=1,min=1,sid=60057,type=0,},
					[9]= {name="太极逍遥腰带",chance=0.04,max=1,min=1,sid=60058,type=0,},
					[10]= {name="肃魂裂天",chance=0.02,max=1,min=1,sid=60110,type=0,},
					[11]= {name="弑皇破天头盔",chance=0.03,max=1,min=1,sid=60111,type=0,},
					[12]= {name="弑皇破天战甲(男)",chance=0.03,max=1,min=1,sid=60112,type=0,},
					[13]= {name="弑皇破天战甲(女)",chance=0.03,max=1,min=1,sid=60113,type=0,},
					[14]= {name="弑皇破天项链",chance=0.03,max=1,min=1,sid=60114,type=0,},
					[15]= {name="弑皇破天手镯",chance=0.03,max=1,min=1,sid=60115,type=0,},
					[16]= {name="弑皇破天宝石",chance=0.03,max=1,min=1,sid=60116,type=0,},
					[17]= {name="弑皇破天战靴",chance=0.033,max=1,min=1,sid=60117,type=0,},
					[18]= {name="弑皇破天腰带",chance=0.04,max=1,min=1,sid=60118,type=0,},
					[19]= {name="牧云惊鸿",chance=0.02,max=1,min=1,sid=60170,type=0,},
					[20]= {name="狂澜魄岳头盔",chance=0.03,max=1,min=1,sid=60171,type=0,},
					[21]= {name="狂澜魄岳魔袍(男)",chance=0.03,max=1,min=1,sid=60172,type=0,},
					[22]= {name="狂澜魄岳魔袍(女)",chance=0.03,max=1,min=1,sid=60173,type=0,},
					[23]= {name="狂澜魄岳项链",chance=0.03,max=1,min=1,sid=60174,type=0,},
					[24]= {name="狂澜魄岳手镯",chance=0.03,max=1,min=1,sid=60175,type=0,},
					[25]= {name="狂澜魄岳宝石",chance=0.03,max=1,min=1,sid=60176,type=0,},
					[26]= {name="狂澜魄岳法履",chance=0.033,max=1,min=1,sid=60177,type=0,},
					[27]= {name="狂澜魄岳腰带",chance=0.04,max=1,min=1,sid=60178,type=0,},
					[28]= {name="霸王勋章*道",chance=0.03,max=1,min=1,sid=70143,type=0,},
					[29]= {name="霸王勋章*武",chance=0.03,max=1,min=1,sid=70152,type=0,},
					[30]= {name="霸王勋章*法",chance=0.03,max=1,min=1,sid=70161,type=0,},
					[31]= {name="太极逍遥戒指",chance=0.03,max=1,min=1,sid=60207,type=0,},
					[32]= {name="弑皇破天戒指",chance=0.03,max=1,min=1,sid=60214,type=0,},
					[33]= {name="狂澜魄岳戒指",chance=0.03,max=1,min=1,sid=60221,type=0,},
				},
			type=1,
		},
	[599]= {
			id=599,
			name="寻宝转生技能书",
			elems= {
					[1]= {name="烈焰重生(1级)",chance=0.3334,max=1,min=1,sid=30073,type=0,},
					[2]= {name="瞬移(1级)",chance=0.3333,max=1,min=1,sid=30078,type=0,},
					[3]= {name="大隐于市(1级)",chance=0.3333,max=1,min=1,sid=30083,type=0,},
				},
			type=1,
		},
	[600]= {
			id=600,
			name="寻宝高级技能书",
			elems= {
					[1]= {name="弦月剑法(4级)",chance=0.055,max=1,min=1,sid=30105,type=0,},
					[2]= {name="刀刺秘剑(4级)",chance=0.055,max=1,min=1,sid=30107,type=0,},
					[3]= {name="战神冲撞(4级)",chance=0.055,max=1,min=1,sid=30139,type=0,},
					[4]= {name="火焰斩(4级)",chance=0.05,max=1,min=1,sid=30102,type=0,},
					[5]= {name="火焰斩(5级)",chance=0.02,max=1,min=1,sid=30103,type=0,},
					[6]= {name="天雷术(4级)",chance=0.055,max=1,min=1,sid=30115,type=0,},
					[7]= {name="熔岩之火(4级)",chance=0.05,max=1,min=1,sid=30111,type=0,},
					[8]= {name="法术抗拒(4级)",chance=0.055,max=1,min=1,sid=30117,type=0,},
					[9]= {name="穿透闪电(4级)",chance=0.05,max=1,min=1,sid=30119,type=0,},
					[10]= {name="光影护盾(4级)",chance=0.05,max=1,min=1,sid=30124,type=0,},
					[11]= {name="冰风暴(4级)",chance=0.055,max=1,min=1,sid=30121,type=0,},
					[12]= {name="冰风暴(5级)",chance=0.02,max=1,min=1,sid=30122,type=0,},
					[13]= {name="灵魂锻炼术(4级)",chance=0.055,max=1,min=1,sid=30133,type=0,},
					[14]= {name="神圣幽灵护体术(4级)",chance=0.055,max=1,min=1,sid=30135,type=0,},
					[15]= {name="群体恢复术(4级)",chance=0.055,max=1,min=1,sid=30126,type=0,},
					[16]= {name="符咒术(4级)",chance=0.055,max=1,min=1,sid=30128,type=0,},
					[17]= {name="符咒术(5级)",chance=0.02,max=1,min=1,sid=30129,type=0,},
					[18]= {name="毒药术(4级)",chance=0.065,max=1,min=1,sid=30100,type=0,},
					[19]= {name="召唤术(4级)",chance=0.07,max=1,min=1,sid=30366,type=0,},
					[20]= {name="召唤术(5级)",chance=0.03,max=1,min=1,sid=30367,type=0,},
					[21]= {name="$寻宝转生技能书",chance=0.025,max=1,min=1,sid=599,type=1,},
				},
			type=1,
		},
	[601]= {
			id=601,
			name="幻武碎片",
			elems= {
					[1]= {name="黄金雷锤碎片",chance=0.25,max=1,min=1,sid=30288,type=0,},
					[2]= {name="如意金箍棒碎片",chance=0.25,max=1,min=1,sid=30289,type=0,},
					[3]= {name="死神之镰碎片",chance=0.25,max=1,min=1,sid=30290,type=0,},
					[4]= {name="生花妙笔碎片",chance=0.25,max=1,min=1,sid=30291,type=0,},
				},
			type=1,
		},
	[602]= {
			id=602,
			name="20级寻宝装备",
			elems= {
					[1]= {name="$寻宝40级套装",chance=0.4673,max=1,min=1,sid=593,type=1,},
					[2]= {name="$寻宝45级套装",chance=0.2843,max=1,min=1,sid=594,type=1,},
					[3]= {name="$寻宝50级套装",chance=0.1289,max=1,min=1,sid=595,type=1,},
					[4]= {name="$寻宝55级套装",chance=0.0769,max=1,min=1,sid=596,type=1,},
					[5]= {name="$寻宝60级套装",chance=0.0267,max=1,min=1,sid=597,type=1,},
					[6]= {name="$寻宝70级套装",chance=0.0159,max=1,min=1,sid=598,type=1,},
				},
			type=1,
		},
	[603]= {
			id=603,
			name="40级寻宝装备",
			elems= {
					[1]= {name="$寻宝40级套装",chance=0.4673,max=1,min=1,sid=593,type=1,},
					[2]= {name="$寻宝45级套装",chance=0.2843,max=1,min=1,sid=594,type=1,},
					[3]= {name="$寻宝50级套装",chance=0.1289,max=1,min=1,sid=595,type=1,},
					[4]= {name="$寻宝55级套装",chance=0.0769,max=1,min=1,sid=596,type=1,},
					[5]= {name="$寻宝60级套装",chance=0.0267,max=1,min=1,sid=597,type=1,},
					[6]= {name="$寻宝70级套装",chance=0.0159,max=1,min=1,sid=598,type=1,},
				},
			type=1,
		},
	[604]= {
			id=604,
			name="50级寻宝装备",
			elems= {
					[1]= {name="$寻宝40级套装",chance=0.4573,max=1,min=1,sid=593,type=1,},
					[2]= {name="$寻宝45级套装",chance=0.2743,max=1,min=1,sid=594,type=1,},
					[3]= {name="$寻宝50级套装",chance=0.1489,max=1,min=1,sid=595,type=1,},
					[4]= {name="$寻宝55级套装",chance=0.0769,max=1,min=1,sid=596,type=1,},
					[5]= {name="$寻宝60级套装",chance=0.0267,max=1,min=1,sid=597,type=1,},
					[6]= {name="$寻宝70级套装",chance=0.0159,max=1,min=1,sid=598,type=1,},
				},
			type=1,
		},
	[605]= {
			id=605,
			name="60级寻宝装备",
			elems= {
					[1]= {name="$寻宝40级套装",chance=0.4473,max=1,min=1,sid=593,type=1,},
					[2]= {name="$寻宝45级套装",chance=0.2843,max=1,min=1,sid=594,type=1,},
					[3]= {name="$寻宝50级套装",chance=0.1389,max=1,min=1,sid=595,type=1,},
					[4]= {name="$寻宝55级套装",chance=0.0869,max=1,min=1,sid=596,type=1,},
					[5]= {name="$寻宝60级套装",chance=0.0267,max=1,min=1,sid=597,type=1,},
					[6]= {name="$寻宝70级套装",chance=0.0159,max=1,min=1,sid=598,type=1,},
				},
			type=1,
		},
	[606]= {
			id=606,
			name="70级寻宝装备",
			elems= {
					[1]= {name="$寻宝40级套装",chance=0.4273,max=1,min=1,sid=593,type=1,},
					[2]= {name="$寻宝45级套装",chance=0.2743,max=1,min=1,sid=594,type=1,},
					[3]= {name="$寻宝50级套装",chance=0.1489,max=1,min=1,sid=595,type=1,},
					[4]= {name="$寻宝55级套装",chance=0.0969,max=1,min=1,sid=596,type=1,},
					[5]= {name="$寻宝60级套装",chance=0.0367,max=1,min=1,sid=597,type=1,},
					[6]= {name="$寻宝70级套装",chance=0.0159,max=1,min=1,sid=598,type=1,},
				},
			type=1,
		},
	[607]= {
			id=607,
			name="等级20以上|幸运0以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.788,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$1阶寻宝灵珠",chance=0.07,max=1,min=1,showmax=4,showmin=3,sid=580,type=1,},
					[3]= {name="$1阶寻宝魂石",chance=0.05,max=1,min=1,showmax=4,showmin=3,sid=586,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$20级寻宝装备",chance=0.046,max=1,min=1,showmax=5,showmin=4,sid=602,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[608]= {
			id=608,
			name="等级40以上|幸运0以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.788,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$1阶寻宝灵珠",chance=0.07,max=1,min=1,showmax=4,showmin=3,sid=580,type=1,},
					[3]= {name="$1阶寻宝魂石",chance=0.05,max=1,min=1,showmax=4,showmin=3,sid=586,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$40级寻宝装备",chance=0.046,max=1,min=1,showmax=5,showmin=4,sid=603,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[609]= {
			id=609,
			name="等级50以上|幸运0以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.788,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$1阶寻宝灵珠",chance=0.07,max=1,min=1,showmax=4,showmin=3,sid=580,type=1,},
					[3]= {name="$1阶寻宝魂石",chance=0.05,max=1,min=1,showmax=4,showmin=3,sid=586,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$50级寻宝装备",chance=0.046,max=1,min=1,showmax=5,showmin=4,sid=604,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[610]= {
			id=610,
			name="等级60以上|幸运0以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.788,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$1阶寻宝灵珠",chance=0.07,max=1,min=1,showmax=4,showmin=3,sid=580,type=1,},
					[3]= {name="$1阶寻宝魂石",chance=0.05,max=1,min=1,showmax=4,showmin=3,sid=586,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$60级寻宝装备",chance=0.046,max=1,min=1,showmax=5,showmin=4,sid=605,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[611]= {
			id=611,
			name="等级70以上|幸运0以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.788,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$1阶寻宝灵珠",chance=0.07,max=1,min=1,showmax=4,showmin=3,sid=580,type=1,},
					[3]= {name="$1阶寻宝魂石",chance=0.05,max=1,min=1,showmax=4,showmin=3,sid=586,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$70级寻宝装备",chance=0.046,max=1,min=1,showmax=5,showmin=4,sid=606,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[612]= {
			id=612,
			name="等级20以上|幸运25以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.785,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$2阶寻宝灵珠",chance=0.071,max=1,min=1,showmax=4,showmin=3,sid=581,type=1,},
					[3]= {name="$2阶寻宝魂石",chance=0.051,max=1,min=1,showmax=4,showmin=3,sid=587,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$20级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=602,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[613]= {
			id=613,
			name="等级40以上|幸运25以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.785,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$2阶寻宝灵珠",chance=0.071,max=1,min=1,showmax=4,showmin=3,sid=581,type=1,},
					[3]= {name="$2阶寻宝魂石",chance=0.051,max=1,min=1,showmax=4,showmin=3,sid=587,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$40级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=603,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[614]= {
			id=614,
			name="等级50以上|幸运25以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.785,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$2阶寻宝灵珠",chance=0.071,max=1,min=1,showmax=4,showmin=3,sid=581,type=1,},
					[3]= {name="$2阶寻宝魂石",chance=0.051,max=1,min=1,showmax=4,showmin=3,sid=587,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$50级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=604,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[615]= {
			id=615,
			name="等级60以上|幸运25以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.785,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$2阶寻宝灵珠",chance=0.071,max=1,min=1,showmax=4,showmin=3,sid=581,type=1,},
					[3]= {name="$2阶寻宝魂石",chance=0.051,max=1,min=1,showmax=4,showmin=3,sid=587,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$60级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=605,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[616]= {
			id=616,
			name="等级70以上|幸运25以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.785,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$2阶寻宝灵珠",chance=0.071,max=1,min=1,showmax=4,showmin=3,sid=581,type=1,},
					[3]= {name="$2阶寻宝魂石",chance=0.051,max=1,min=1,showmax=4,showmin=3,sid=587,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$70级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=606,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[617]= {
			id=617,
			name="等级20以上|幸运50以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$3阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=582,type=1,},
					[3]= {name="$3阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=588,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$20级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=602,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[618]= {
			id=618,
			name="等级40以上|幸运50以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$3阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=582,type=1,},
					[3]= {name="$3阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=588,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$40级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=603,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[619]= {
			id=619,
			name="等级50以上|幸运50以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$3阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=582,type=1,},
					[3]= {name="$3阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=588,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$50级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=604,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[620]= {
			id=620,
			name="等级60以上|幸运50以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$3阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=582,type=1,},
					[3]= {name="$3阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=588,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$60级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=605,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[621]= {
			id=621,
			name="等级70以上|幸运50以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$3阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=582,type=1,},
					[3]= {name="$3阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=588,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$70级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=606,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[622]= {
			id=622,
			name="等级20以上|幸运150以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$4阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=583,type=1,},
					[3]= {name="$4阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=589,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$20级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=602,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[623]= {
			id=623,
			name="等级40以上|幸运150以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$4阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=583,type=1,},
					[3]= {name="$4阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=589,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$40级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=603,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[624]= {
			id=624,
			name="等级50以上|幸运150以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$4阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=583,type=1,},
					[3]= {name="$4阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=589,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$50级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=604,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[625]= {
			id=625,
			name="等级60以上|幸运150以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$4阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=583,type=1,},
					[3]= {name="$4阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=589,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$60级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=605,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[626]= {
			id=626,
			name="等级70以上|幸运150以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$4阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=583,type=1,},
					[3]= {name="$4阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=589,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$70级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=606,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[627]= {
			id=627,
			name="等级20以上|幸运300以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$5阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=584,type=1,},
					[3]= {name="$5阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=590,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$20级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=602,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[628]= {
			id=628,
			name="等级40以上|幸运300以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$5阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=584,type=1,},
					[3]= {name="$5阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=590,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$40级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=603,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[629]= {
			id=629,
			name="等级50以上|幸运300以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$5阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=584,type=1,},
					[3]= {name="$5阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=590,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$50级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=604,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[630]= {
			id=630,
			name="等级60以上|幸运300以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$5阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=584,type=1,},
					[3]= {name="$5阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=590,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$60级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=605,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[631]= {
			id=631,
			name="等级70以上|幸运300以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.783,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$5阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=584,type=1,},
					[3]= {name="$5阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=590,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$70级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=606,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="附魔卷",chance=0,max=1,min=1,showmax=0,showmin=0,sid=40148,type=0,},
					[9]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[632]= {
			id=632,
			name="等级20以上|幸运500以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.777,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$6阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=585,type=1,},
					[3]= {name="$6阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=591,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$20级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=602,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="附魔强化符",chance=0.004,max=1,min=1,showmax=1,showmin=1,sid=40149,type=0,},
					[9]= {name="极品附魔符",chance=0.002,max=1,min=1,showmax=1,showmin=1,sid=40150,type=0,},
					[10]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[633]= {
			id=633,
			name="等级40以上|幸运500以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.777,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$6阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=585,type=1,},
					[3]= {name="$6阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=591,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$40级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=603,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="附魔强化符",chance=0.004,max=1,min=1,showmax=1,showmin=1,sid=40149,type=0,},
					[9]= {name="极品附魔符",chance=0.002,max=1,min=1,showmax=1,showmin=1,sid=40150,type=0,},
					[10]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[634]= {
			id=634,
			name="等级50以上|幸运500以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.777,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$6阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=585,type=1,},
					[3]= {name="$6阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=591,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$50级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=604,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="附魔强化符",chance=0.004,max=1,min=1,showmax=1,showmin=1,sid=40149,type=0,},
					[9]= {name="极品附魔符",chance=0.002,max=1,min=1,showmax=1,showmin=1,sid=40150,type=0,},
					[10]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[635]= {
			id=635,
			name="等级60以上|幸运500以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.777,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$6阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=585,type=1,},
					[3]= {name="$6阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=591,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$60级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=605,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="附魔强化符",chance=0.004,max=1,min=1,showmax=1,showmin=1,sid=40149,type=0,},
					[9]= {name="极品附魔符",chance=0.002,max=1,min=1,showmax=1,showmin=1,sid=40150,type=0,},
					[10]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
				},
			type=1,
		},
	[636]= {
			id=636,
			name="等级70以上|幸运500以上",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.777,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$6阶寻宝灵珠",chance=0.072,max=1,min=1,showmax=4,showmin=3,sid=585,type=1,},
					[3]= {name="$6阶寻宝魂石",chance=0.052,max=1,min=1,showmax=4,showmin=3,sid=591,type=1,},
					[4]= {name="$寻宝戒指",chance=0.0015,max=1,min=1,showmax=3,showmin=3,sid=592,type=1,},
					[5]= {name="低级幸运神石",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=60329,type=0,},
					[6]= {name="$70级寻宝装备",chance=0.047,max=1,min=1,showmax=5,showmin=4,sid=606,type=1,},
					[7]= {name="$幻武碎片",chance=0.04,max=1,min=1,showmax=1,showmin=0,sid=601,type=1,},
					[8]= {name="$寻宝高级技能书",chance=0.003,max=1,min=1,showmax=1,showmin=1,sid=600,type=1,},
					[9]= {name="附魔强化符",chance=0.004,max=1,min=1,showmax=1,showmin=1,sid=40149,type=0,},
					[10]= {name="极品附魔符",chance=0.002,max=1,min=1,showmax=1,showmin=1,sid=40150,type=0,},
					[11]= {name="3套",chance=0.02,max=1,min=1,showmax=1,showmin=1,sid=661,type=1,},
					[12]= {name="4套",chance=0.0095,max=1,min=1,showmax=1,showmin=1,sid=662,type=1,},
					[13]= {name="5套",chance=0.0085,max=1,min=1,showmax=1,showmin=1,sid=663,type=1,},
					[14]= {name="6套",chance=0.0075,max=1,min=1,showmax=1,showmin=1,sid=664,type=1,},
					[15]= {name="8套",chance=0.0035,max=1,min=1,showmax=1,showmin=1,sid=667,type=1,},
					[16]= {name="9套",chance=0.0025,max=1,min=1,showmax=1,showmin=1,sid=668,type=1,},
					[17]= {name="10套",chance=0.0015,max=1,min=1,showmax=1,showmin=1,sid=699,type=1,},
					[18]= {name="11套",chance=0.0005,max=1,min=1,showmax=1,showmin=1,sid=700,type=1,},
				},
			type=1,
		},
	[637]= {
			id=637,
			name="免费寻宝",
			elems= {
					[1]= {name="$1阶寻宝物品道具",chance=0.94,max=1,min=1,showmax=7,showmin=6,sid=579,type=1,},
					[2]= {name="$1阶寻宝灵珠",chance=0.03,max=1,min=1,showmax=4,showmin=3,sid=580,type=1,},
					[3]= {name="$1阶寻宝魂石",chance=0.02,max=1,min=1,showmax=4,showmin=3,sid=586,type=1,},
					[4]= {name="$幻武碎片",chance=0.01,max=1,min=1,showmax=5,showmin=1,sid=601,type=1,},
				},
			type=1,
		},
	[638]= {
			id=638,
			name="活跃礼包的数据",
			elems= {
					[1]= {name="战神油",chance=0.0408,max=1,min=1,sid=30017,type=0,},
					[2]= {name="幸运药水",chance=0.0409,max=1,min=1,sid=30020,type=0,},
				--	[3]= {name="任务完成符",chance=0.0408,max=1,min=1,sid=40045,type=0,},
					[4]= {name="传音喇叭",chance=0.0408,max=1,min=1,sid=40138,type=0,},
					[5]= {name="苹果",chance=0.0409,max=2,min=2,sid=30046,type=0,},
					[6]= {name="金条",chance=0.01,max=1,min=1,sid=30060,type=0,},
					[7]= {name="1000荣誉",chance=0.0409,max=1,min=1,sid=30208,type=0,},
					[8]= {name="3000荣誉",chance=0.0409,max=1,min=1,sid=30210,type=0,},
					[9]= {name="5000荣誉",chance=0.02,max=1,min=1,sid=30207,type=0,},
					[10]= {name="千年玄参",chance=0.12,max=2,min=2,sid=39016,type=0,},
					[11]= {name="千年冰莲",chance=0.12,max=2,min=2,sid=39020,type=0,},
					[12]= {name="攻击药水(中)",chance=0.12,max=2,min=2,sid=39024,type=0,},
					[13]= {name="防御药水(中)",chance=0.12,max=2,min=2,sid=39026,type=0,},
					[14]= {name="一级灵石",chance=0.0408,max=1,min=1,sid=40000,type=0,},
					[15]= {name="宠物项圈",chance=0.0408,max=3,min=3,sid=40053,type=0,},
					[16]= {name="清洗丹",chance=0.0408,max=1,min=1,sid=40041,type=0,},
					[17]= {name="鉴定锁",chance=0.0408,max=1,min=1,sid=40042,type=0,},
					[18]= {name="强化保护符",chance=0.0408,max=1,min=1,sid=40012,type=0,},
				},
			type=1,
		},
----------------------------------------------------------------------------------------------------------------------		
	[639]= {
			id=639,
			name="将军凌小怪",
			elems= {
			        [1]= {name="元宝",chance=0.1,datax=50,datay=400,max=1,min=1,sid=3,type=0,},
					[2]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[3]= {chance=0.002,max=1,min=1,sid=662,type=1,},
				},
			max=0,
			type=0,
		},
	[640]= {
			id=640,
			name="将军陵小怪",
			elems= {
					[1]= {name="元宝",chance=0.1,datax=100,datay=500,max=1,min=1,sid=3,type=0,},
					[2]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[3]= {chance=0.004,max=1,min=1,sid=662,type=1,},
				},
			max=0,
			type=0,
		},
	[641]= {
			id=641,
			name="暗夜殿小怪",
			elems= {
			        [1]= {name="元宝",chance=0.1,datax=200,datay=800,max=1,min=1,sid=3,type=0,},
					[2]= {chance=0.0002,max=1,min=1,sid=664,type=1,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					
				},
			max=0,
			type=0,
		},
	[642]= {
			id=642,
			name="古陵玄宫小怪",
			elems= {
			        [1]= {name="仙玉",chance=0.8,datax=10,datay=20,max=1,min=1,sid=4,type=0,},
					[2]= {chance=0.05,max=1,min=1,sid=664,type=1,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					
				},
			max=0,
			type=0,
		},	
	[643]= {
			id=643,
			name="星界囚笼小怪",
			elems= {
			        [1]= {name="仙玉",chance=0.6,datax=600,datay=1500,max=1,min=1,sid=4,type=0,},
					[2]= {chance=1,max=1,min=1,sid=664,type=1,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="五级灵石",chance=0.8,max=3,min=2,sid=40004,type=0,},
					[5]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
				},
			max=0,
			type=0,
		},	
--------------------------------------------------套装-----------------------------------------------------------
--------------------------------------------------套装-----------------------------------------------------------
--------------------------------------------------套装-----------------------------------------------------------
--------------------------------------------------套装-----------------------------------------------------------	
	[661]= {
			id=661,
			elems= {------------------------------3套
                   [1]= {name="战士",chance=0.0317,max=1,min=1,sid=20080,type=0,},
				   [2]= {name="战士",chance=0.0417,max=1,min=1,sid=20081,type=0,},
				   [3]= {name="战士",chance=0.0317,max=1,min=1,sid=20082,type=0,},
                   [4]= {name="战士",chance=0.0317,max=1,min=1,sid=20083,type=0,},
                   [5]= {name="战士",chance=0.0417,max=1,min=1,sid=20084,type=0,},
                   [6]= {name="战士",chance=0.0517,max=1,min=1,sid=20085,type=0,},
                   [7]= {name="战士",chance=0.0417,max=1,min=1,sid=20086,type=0,},
                   [8]= {name="战士",chance=0.0617,max=1,min=1,sid=20087,type=0,},
				   [9]= {name="战士",chance=0.0417,max=1,min=1,sid=20088,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0217,max=1,min=1,sid=20140,type=0,},
                   [11]= {name="法师",chance=0.0417,max=1,min=1,sid=20141,type=0,},
                   [12]= {name="法师",chance=0.0417,max=1,min=1,sid=20142,type=0,},
                -- [13]= {name="法师",chance=0.0517,max=1,min=1,sid=20143,type=0,},
                   [13]= {name="法师",chance=0.0317,max=1,min=1,sid=20144,type=0,},
                   [14]= {name="法师",chance=0.0417,max=1,min=1,sid=20145,type=0,},
                   [15]= {name="法师",chance=0.0417,max=1,min=1,sid=20146,type=0,},
                   [16]= {name="法师",chance=0.0617,max=1,min=1,sid=20147,type=0,},
                   [17]= {name="法师",chance=0.0417,max=1,min=1,sid=20148,type=0,},
                   ----------------------------------------------------------
				   [18]= {name="道士",chance=0.0217,max=1,min=1,sid=20020,type=0,},
                   [19]= {name="道士",chance=0.0517,max=1,min=1,sid=20021,type=0,},
                   [20]= {name="道士",chance=0.0417,max=1,min=1,sid=20022,type=0,},
               --  [22]= {name="道士",chance=0.0317,max=1,min=1,sid=20023,type=0,},
				   [21]= {name="道士",chance=0.0417,max=1,min=1,sid=20024,type=0,},
				   [22]= {name="道士",chance=0.0517,max=1,min=1,sid=20025,type=0,},
				   [23]= {name="道士",chance=0.0310,max=1,min=1,sid=20026,type=0,},
				   [24]= {name="道士",chance=0.0412,max=1,min=1,sid=20027,type=0,},
				   [25]= {name="道士",chance=0.0421,max=1,min=1,sid=20028,type=0,},
				   
				},
			type=1,
		},
	[662]= {
			id=662,
			elems= {------------------------------4套
                   [1]= {name="战士",chance=0.0317,max=1,min=1,sid=20090,type=0,},
				   [2]= {name="战士",chance=0.0317,max=1,min=1,sid=20091,type=0,},
				   [3]= {name="战士",chance=0.0317,max=1,min=1,sid=20092,type=0,},
                   [4]= {name="战士",chance=0.0217,max=1,min=1,sid=20093,type=0,},
                   [5]= {name="战士",chance=0.0417,max=1,min=1,sid=20094,type=0,},
                   [6]= {name="战士",chance=0.0317,max=1,min=1,sid=20095,type=0,},
                   [7]= {name="战士",chance=0.0417,max=1,min=1,sid=20096,type=0,},
                   [8]= {name="战士",chance=0.0317,max=1,min=1,sid=20097,type=0,},
				   [9]= {name="战士",chance=0.0517,max=1,min=1,sid=20098,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0117,max=1,min=1,sid=20150,type=0,},
                   [11]= {name="法师",chance=0.0317,max=1,min=1,sid=20151,type=0,},
                   [12]= {name="法师",chance=0.0217,max=1,min=1,sid=20152,type=0,},
                   [13]= {name="法师",chance=0.0317,max=1,min=1,sid=20153,type=0,},
                   [14]= {name="法师",chance=0.0317,max=1,min=1,sid=20154,type=0,},
                   [15]= {name="法师",chance=0.0317,max=1,min=1,sid=20155,type=0,},
                   [16]= {name="法师",chance=0.0417,max=1,min=1,sid=20156,type=0,},
                   [17]= {name="法师",chance=0.0317,max=1,min=1,sid=20157,type=0,},
                   [18]= {name="法师",chance=0.0517,max=1,min=1,sid=20158,type=0,},
                   ----------------------------------------------------------
				   [19]= {name="道士",chance=0.0217,max=1,min=1,sid=20030,type=0,},
                   [20]= {name="道士",chance=0.0117,max=1,min=1,sid=20031,type=0,},
                   [21]= {name="道士",chance=0.0317,max=1,min=1,sid=20032,type=0,},
                   [22]= {name="道士",chance=0.0317,max=1,min=1,sid=20033,type=0,},
				   [23]= {name="道士",chance=0.0217,max=1,min=1,sid=20034,type=0,},
				   [24]= {name="道士",chance=0.0317,max=1,min=1,sid=20035,type=0,},
				   [25]= {name="道士",chance=0.0417,max=1,min=1,sid=20036,type=0,},
				   [26]= {name="道士",chance=0.0517,max=1,min=1,sid=20037,type=0,},
				   [27]= {name="道士",chance=0.0317,max=1,min=1,sid=20038,type=0,},
				},
			type=1,
		},
	[663]= {
			id=663,
			elems= {------------------------------5套
                   [1]= {name="战士",chance=0.0217,max=1,min=1,sid=20100,type=0,},
				   [2]= {name="战士",chance=0.0417,max=1,min=1,sid=20101,type=0,},
				   [3]= {name="战士",chance=0.0617,max=1,min=1,sid=20102,type=0,},
                   [4]= {name="战士",chance=0.0317,max=1,min=1,sid=20103,type=0,},
                   [5]= {name="战士",chance=0.0517,max=1,min=1,sid=20104,type=0,},
                   [6]= {name="战士",chance=0.0317,max=1,min=1,sid=20105,type=0,},
                   [7]= {name="战士",chance=0.0317,max=1,min=1,sid=20106,type=0,},
                   [8]= {name="战士",chance=0.0217,max=1,min=1,sid=20107,type=0,},
				   [9]= {name="战士",chance=0.0317,max=1,min=1,sid=20108,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0217,max=1,min=1,sid=20160,type=0,},
                   [11]= {name="法师",chance=0.0317,max=1,min=1,sid=20161,type=0,},
                   [12]= {name="法师",chance=0.0317,max=1,min=1,sid=20162,type=0,},
                 --[13]= {name="法师",chance=1,max=1,min=1,sid=20163,type=0,},
                   [13]= {name="法师",chance=0.0417,max=1,min=1,sid=20164,type=0,},
                   [14]= {name="法师",chance=0.0517,max=1,min=1,sid=20165,type=0,},
                   [15]= {name="法师",chance=0.0317,max=1,min=1,sid=20166,type=0,},
                   [16]= {name="法师",chance=0.0217,max=1,min=1,sid=20167,type=0,},
                   [17]= {name="法师",chance=0.0317,max=1,min=1,sid=20168,type=0,},
                   ---------------------------------------------------------
				   [18]= {name="道士",chance=0.0217,max=1,min=1,sid=20040,type=0,},
                   [19]= {name="道士",chance=0.0317,max=1,min=1,sid=20041,type=0,},
                   [20]= {name="道士",chance=0.0317,max=1,min=1,sid=20042,type=0,},
                 --[22]= {name="道士",chance=1,max=1,min=1,sid=20043,type=0,},
				   [21]= {name="道士",chance=0.0217,max=1,min=1,sid=20044,type=0,},
				   [22]= {name="道士",chance=0.0317,max=1,min=1,sid=20045,type=0,},
				   [23]= {name="道士",chance=0.0317,max=1,min=1,sid=20046,type=0,},
				   [24]= {name="道士",chance=0.0517,max=1,min=1,sid=20047,type=0,},
				   [25]= {name="道士",chance=0.0317,max=1,min=1,sid=20048,type=0,},
				},
			type=1,
		},
	[664]= {
			id=664,
			elems= {------------------------------6套
                   [1]= {name="战士",chance=0.0317,max=1,min=1,sid=20110,type=0,},
				   [2]= {name="战士",chance=0.0417,max=1,min=1,sid=20111,type=0,},
				   [3]= {name="战士",chance=0.0317,max=1,min=1,sid=20112,type=0,},
                   [4]= {name="战士",chance=0.0417,max=1,min=1,sid=20113,type=0,},
                   [5]= {name="战士",chance=0.0317,max=1,min=1,sid=20114,type=0,},
                   [6]= {name="战士",chance=0.0517,max=1,min=1,sid=20115,type=0,},
                   [7]= {name="战士",chance=0.0317,max=1,min=1,sid=20116,type=0,},
                   [8]= {name="战士",chance=0.0417,max=1,min=1,sid=20117,type=0,},
				   [9]= {name="战士",chance=0.0517,max=1,min=1,sid=20118,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0117,max=1,min=1,sid=20170,type=0,},
                   [11]= {name="法师",chance=0.0217,max=1,min=1,sid=20171,type=0,},
                   [12]= {name="法师",chance=0.0317,max=1,min=1,sid=20172,type=0,},
                 --[13]= {name="法师",chance=1,max=1,min=1,sid=20173,type=0,},
                   [13]= {name="法师",chance=0.0217,max=1,min=1,sid=20174,type=0,},
                   [14]= {name="法师",chance=0.0317,max=1,min=1,sid=20175,type=0,},
                   [15]= {name="法师",chance=0.0117,max=1,min=1,sid=20176,type=0,},
                   [16]= {name="法师",chance=0.0317,max=1,min=1,sid=20177,type=0,},
                   [17]= {name="法师",chance=0.0317,max=1,min=1,sid=20178,type=0,},
                   ----------------------------------------------------------
				   [18]= {name="道士",chance=0.0217,max=1,min=1,sid=20050,type=0,},
                   [19]= {name="道士",chance=0.0517,max=1,min=1,sid=20051,type=0,},
                   [20]= {name="道士",chance=0.0317,max=1,min=1,sid=20052,type=0,},
                 --[21]= {name="道士",chance=1,max=1,min=1,sid=20053,type=0,},
				   [21]= {name="道士",chance=0.0317,max=1,min=1,sid=20054,type=0,},
				   [22]= {name="道士",chance=0.0417,max=1,min=1,sid=20055,type=0,},
				   [23]= {name="道士",chance=0.0317,max=1,min=1,sid=20056,type=0,},
				   [24]= {name="道士",chance=0.0217,max=1,min=1,sid=20057,type=0,},
				   [25]= {name="道士",chance=0.0317,max=1,min=1,sid=20058,type=0,},
				},
			type=1,
		},

	--------------------------------------------------世界boos---------------------------------------------	
	[673]= {
			id=673,
			name="世界boss1",
			elems= { 
					[1]= {name="元宝",chance=1,datax=1000,datay=5000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=100,datay=600,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.4,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=2,min=1,sid=661,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[674]= {
			id=674,
			name="世界boss2",
			elems= {
					[1]= {name="元宝",chance=1,datax=10000,datay=10000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=1000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.4,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=2,min=1,sid=661,type=1,},
					
				},
			max=81,
			type=0,
		},
	[675]= {
			id=675,
			name="世界boss3",
			elems= {
					[1]= {name="元宝",chance=1,datax=10000,datay=10000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=500,datay=1000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=3,min=2,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.4,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=2,min=1,sid=662,type=1,},
				},
			max=81,
			type=0,
		},
	[676]= {
			id=676,
			name="世界boss4",
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=50000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=1000,datay=3000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=10,min=10,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=8,min=10,sid=40004,type=0,},
					[6]= {chance=1,max=2,min=1,sid=662,type=1,},
					[7]= {name="钥匙",chance=0.4,max=1,min=1,sid=41005,type=0,},
				},
			max=81,
			type=0,
		},
	[677]= {
			id=677,
			name="世界boss5",
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=1000,datay=5000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=10,min=10,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=8,min=10,sid=40004,type=0,},
					[6]= {name="钥匙",chance=0.4,max=1,min=1,sid=41005,type=0,},
					[7]= {chance=0.6,max=1,min=1,sid=663,type=1,},
					[8]= {chance=1,max=2,min=1,sid=662,type=1,},
					
				},
			max=81,
			type=0,
		},
	[678]= {
			id=678,
			name="世界boss6",
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=1000,datay=5000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=10,min=10,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=8,min=10,sid=40004,type=0,},
					[6]= {chance=1,max=2,min=1,sid=663,type=1,},
					[7]= {name="低级缓慢",chance=0.3,max=1,min=1,sid=60301,type=0,},
					[8]= {name="低级赤炎章",chance=0.5,max=1,min=1,sid=60308,type=0,},
					[9]= {name="低级暴雷石",chance=0.3,max=1,min=1,sid=60315,type=0,},
					[10]= {name="低级暴雷石",chance=0.3,max=1,min=1,sid=60322,type=0,},
					[11]= {name="钥匙",chance=0.4,max=1,min=1,sid=41005,type=0,},
					
					
					
					
				},
			max=81,
			type=0,
		},
	[679]= {
			id=679,
			name="世界boss7",
			elems= {
					[1]= {name="元宝",chance=1,datax=50000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=1000,datay=5000,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=10,min=10,sid=40148,type=0,},
					[4]= {name="四级灵石",chance=1,max=5,min=5,sid=40003,type=0,},
					[5]= {name="五级灵石",chance=1,max=8,min=10,sid=40004,type=0,},
					[6]= {chance=0.6,max=1,min=1,sid=664,type=1,},
					[7]= {chance=0.7,max=2,min=1,sid=663,type=1,},
					[8]= {chance=0.9,max=2,min=1,sid=662,type=1,},
					[9]= {chance=1,max=3,min=1,sid=661,type=1,},
					[10]= {name="中级缓慢",chance=0.2,max=1,min=1,sid=60302,type=0,},
					[11]= {name="中级赤炎章",chance=0.5,max=1,min=1,sid=60309,type=0,},
					[12]= {name="中级暴雷石",chance=0.3,max=1,min=1,sid=60316,type=0,},
					[13]= {name="中级暴雷石",chance=0.3,max=1,min=1,sid=60323,type=0,},
					[14]= {name="钥匙",chance=0.4,max=1,min=1,sid=41005,type=0,},
					
					
					
				},
			max=81,
			type=0,
		},
		--------------------------------------------------地图boos--------------------------------------------
	[688]= {
			id=688,
			name="地图boss1",
			elems= {
					[1]= {name="行会资格证",chance=0.25,max=1,min=1,sid=40057,type=0,},
					[2]= {name="元宝",chance=1,datax=1000,datay=2000,max=1,min=1,sid=3,type=0,},
					[3]= {name="仙玉",chance=1,datax=50,datay=100,max=1,min=1,sid=4,type=0,},
					[4]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[5]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[6]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=0.5,max=1,min=1,sid=661,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[689]= {
			id=689,
			name="地图boss2",
			elems= {
					[1]= {name="行会资格证",chance=0.25,max=1,min=1,sid=40057,type=0,},
					[2]= {name="元宝",chance=1,datax=1000,datay=2000,max=1,min=1,sid=3,type=0,},
					[3]= {name="仙玉",chance=1,datax=50,datay=600,max=1,min=1,sid=4,type=0,},
					[4]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[5]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[6]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=0.5,max=1,min=1,sid=661,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[690]= {
			id=690,
			name="地图boss3",
			elems= {
					[1]= {name="行会资格证",chance=0.25,max=1,min=1,sid=40057,type=0,},
					[2]= {name="元宝",chance=1,datax=1000,datay=2000,max=1,min=1,sid=3,type=0,},
					[3]= {name="仙玉",chance=1,datax=50,datay=600,max=1,min=1,sid=4,type=0,},
					[4]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[5]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[6]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=0.5,max=1,min=1,sid=661,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[691]= {
			id=691,
			name="地图boss4",
			elems= {
					[1]= {name="元宝",chance=1,datax=1000,datay=2000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=50,datay=600,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=1,min=1,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=1,min=1,sid=661,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[692]= {
			id=692,
			name="地图boss5",
			elems= {
					[1]= {name="元宝",chance=1,datax=1000,datay=5000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=50,datay=600,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=2,min=1,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=1,min=1,sid=662,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[693]= {
			id=693,
			name="地图boss6",
			elems= {
					[1]= {name="元宝",chance=1,datax=1000,datay=5000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=50,datay=300,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=2,min=1,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=1,min=1,sid=662,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[694]= {
			id=694,
			name="地图boss7",
			elems= {
					[1]= {name="元宝",chance=1,datax=1000,datay=5000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=50,datay=600,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=2,min=1,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=1,min=1,sid=662,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[695]= {
			id=695,
			name="地图boss8",
			elems= {
					[1]= {name="元宝",chance=1,datax=5000,datay=10000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=100,datay=600,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=2,min=1,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=1,max=1,min=1,sid=662,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
		},
	[696]= {
			id=696,
			name="地图boss9",
			elems= {
					[1]= {name="元宝",chance=1,datax=5000,datay=80000,max=1,min=1,sid=3,type=0,},
					[2]= {name="仙玉",chance=1,datax=100,datay=800,max=1,min=1,sid=4,type=0,},
					[3]= {name="附魔卷",chance=0.02,max=1,min=1,sid=40148,type=0,},
					[4]= {name="三级灵石",chance=1,max=3,min=1,sid=40002,type=0,},
					[5]= {name="四级灵石",chance=1,max=3,min=1,sid=40003,type=0,},
					[6]= {name="五级灵石",chance=1,max=2,min=1,sid=40004,type=0,},
					[7]= {name="钥匙",chance=0.3,max=1,min=1,sid=41005,type=0,},
					[8]= {chance=0.8,max=1,min=1,sid=663,type=1,},
					[9]= {chance=1,max=1,min=1,sid=399,type=1,},
				},
			max=81,
			type=0,
	},
	[697]= {
			id=697,
			elems= {------------------------------8套
                   [1]= {name="战士",chance=0.0317,max=1,min=1,sid=20300,type=0,},
				   [2]= {name="战士",chance=0.0417,max=1,min=1,sid=20301,type=0,},
				   [3]= {name="战士",chance=0.0317,max=1,min=1,sid=20302,type=0,},
                   [4]= {name="战士",chance=0.0417,max=1,min=1,sid=20303,type=0,},
                   [5]= {name="战士",chance=0.0317,max=1,min=1,sid=20304,type=0,},
                   [6]= {name="战士",chance=0.0517,max=1,min=1,sid=20305,type=0,},
                   [7]= {name="战士",chance=0.0317,max=1,min=1,sid=20306,type=0,},
                   [8]= {name="战士",chance=0.0417,max=1,min=1,sid=20307,type=0,},
				   [9]= {name="战士",chance=0.0517,max=1,min=1,sid=20308,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0117,max=1,min=1,sid=20310,type=0,},
                   [11]= {name="法师",chance=0.0217,max=1,min=1,sid=20311,type=0,},
                   [12]= {name="法师",chance=0.0317,max=1,min=1,sid=20312,type=0,},
                 --[13]= {name="法师",chance=1,max=1,min=1,sid=20173,type=0,},
                   [13]= {name="法师",chance=0.0217,max=1,min=1,sid=20314,type=0,},
                   [14]= {name="法师",chance=0.0317,max=1,min=1,sid=20315,type=0,},
                   [15]= {name="法师",chance=0.0117,max=1,min=1,sid=20316,type=0,},
                   [16]= {name="法师",chance=0.0317,max=1,min=1,sid=20317,type=0,},
                   [17]= {name="法师",chance=0.0317,max=1,min=1,sid=20318,type=0,},
                   ----------------------------------------------------------
				   [18]= {name="道士",chance=0.0217,max=1,min=1,sid=20320,type=0,},
                   [19]= {name="道士",chance=0.0517,max=1,min=1,sid=20321,type=0,},
                   [20]= {name="道士",chance=0.0317,max=1,min=1,sid=20322,type=0,},
                 --[21]= {name="道士",chance=1,max=1,min=1,sid=20053,type=0,},
				   [21]= {name="道士",chance=0.0317,max=1,min=1,sid=20324,type=0,},
				   [22]= {name="道士",chance=0.0417,max=1,min=1,sid=20325,type=0,},
				   [23]= {name="道士",chance=0.0317,max=1,min=1,sid=20326,type=0,},
				   [24]= {name="道士",chance=0.0217,max=1,min=1,sid=20327,type=0,},
				   [25]= {name="道士",chance=0.0317,max=1,min=1,sid=20328,type=0,},
				},
			type=1,
		},
	[698]= {
			id=698,
			elems= {------------------------------9套
                   [1]= {name="战士",chance=0.0317,max=1,min=1,sid=20329,type=0,},
				   [2]= {name="战士",chance=0.0417,max=1,min=1,sid=20330,type=0,},
				   [3]= {name="战士",chance=0.0317,max=1,min=1,sid=20331,type=0,},
                   [4]= {name="战士",chance=0.0417,max=1,min=1,sid=20332,type=0,},
                   [5]= {name="战士",chance=0.0317,max=1,min=1,sid=20333,type=0,},
                   [6]= {name="战士",chance=0.0517,max=1,min=1,sid=20334,type=0,},
                   [7]= {name="战士",chance=0.0317,max=1,min=1,sid=20335,type=0,},
                   [8]= {name="战士",chance=0.0417,max=1,min=1,sid=20336,type=0,},
				   [9]= {name="战士",chance=0.0517,max=1,min=1,sid=20337,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0117,max=1,min=1,sid=20338,type=0,},
                   [11]= {name="法师",chance=0.0217,max=1,min=1,sid=20339,type=0,},
                   [12]= {name="法师",chance=0.0317,max=1,min=1,sid=20340,type=0,},
                 --[13]= {name="法师",chance=1,max=1,min=1,sid=20173,type=0,},
                   [13]= {name="法师",chance=0.0217,max=1,min=1,sid=20342,type=0,},
                   [14]= {name="法师",chance=0.0317,max=1,min=1,sid=20343,type=0,},
                   [15]= {name="法师",chance=0.0117,max=1,min=1,sid=20344,type=0,},
                   [16]= {name="法师",chance=0.0317,max=1,min=1,sid=20345,type=0,},
                   [17]= {name="法师",chance=0.0317,max=1,min=1,sid=20346,type=0,},
                   ----------------------------------------------------------
				   [18]= {name="道士",chance=0.0217,max=1,min=1,sid=20347,type=0,},
                   [19]= {name="道士",chance=0.0517,max=1,min=1,sid=20348,type=0,},
                   [20]= {name="道士",chance=0.0317,max=1,min=1,sid=20349,type=0,},
                 --[21]= {name="道士",chance=1,max=1,min=1,sid=20053,type=0,},
				   [21]= {name="道士",chance=0.0317,max=1,min=1,sid=20351,type=0,},
				   [22]= {name="道士",chance=0.0417,max=1,min=1,sid=20352,type=0,},
				   [23]= {name="道士",chance=0.0317,max=1,min=1,sid=20353,type=0,},
				   [24]= {name="道士",chance=0.0217,max=1,min=1,sid=20354,type=0,},
				   [25]= {name="道士",chance=0.0317,max=1,min=1,sid=20355,type=0,},
				},
			type=1,
		},
	[699]= {
			id=699,
			elems= {------------------------------10套
                   [1]= {name="战士",chance=0.0317,max=1,min=1,sid=20500,type=0,},
				   [2]= {name="战士",chance=0.0417,max=1,min=1,sid=20501,type=0,},
				   [3]= {name="战士",chance=0.0317,max=1,min=1,sid=20502,type=0,},
                   [4]= {name="战士",chance=0.0417,max=1,min=1,sid=20503,type=0,},
                   [5]= {name="战士",chance=0.0317,max=1,min=1,sid=20504,type=0,},
                   [6]= {name="战士",chance=0.0517,max=1,min=1,sid=20505,type=0,},
                   [7]= {name="战士",chance=0.0317,max=1,min=1,sid=20506,type=0,},
                   [8]= {name="战士",chance=0.0417,max=1,min=1,sid=20507,type=0,},
				   [9]= {name="战士",chance=0.0517,max=1,min=1,sid=20508,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0117,max=1,min=1,sid=20510,type=0,},
                   [11]= {name="法师",chance=0.0217,max=1,min=1,sid=20511,type=0,},
                   [12]= {name="法师",chance=0.0317,max=1,min=1,sid=20512,type=0,},
                 --[13]= {name="法师",chance=1,max=1,min=1,sid=20173,type=0,},
                   [13]= {name="法师",chance=0.0217,max=1,min=1,sid=20514,type=0,},
                   [14]= {name="法师",chance=0.0317,max=1,min=1,sid=20515,type=0,},
                   [15]= {name="法师",chance=0.0117,max=1,min=1,sid=20516,type=0,},
                   [16]= {name="法师",chance=0.0317,max=1,min=1,sid=20517,type=0,},
                   [17]= {name="法师",chance=0.0317,max=1,min=1,sid=20518,type=0,},
                   ----------------------------------------------------------
				   [18]= {name="道士",chance=0.0217,max=1,min=1,sid=20520,type=0,},
                   [19]= {name="道士",chance=0.0517,max=1,min=1,sid=20521,type=0,},
                   [20]= {name="道士",chance=0.0317,max=1,min=1,sid=20522,type=0,},
                 --[21]= {name="道士",chance=1,max=1,min=1,sid=20053,type=0,},
				   [21]= {name="道士",chance=0.0317,max=1,min=1,sid=20524,type=0,},
				   [22]= {name="道士",chance=0.0417,max=1,min=1,sid=20525,type=0,},
				   [23]= {name="道士",chance=0.0317,max=1,min=1,sid=20526,type=0,},
				   [24]= {name="道士",chance=0.0217,max=1,min=1,sid=20527,type=0,},
				   [25]= {name="道士",chance=0.0317,max=1,min=1,sid=20528,type=0,},
				},
			type=1,
		},
	[700]= {
			id=700,
			elems= {------------------------------11套
                   [1]= {name="战士",chance=0.0317,max=1,min=1,sid=20530,type=0,},
				   [2]= {name="战士",chance=0.0417,max=1,min=1,sid=20531,type=0,},
				   [3]= {name="战士",chance=0.0317,max=1,min=1,sid=20532,type=0,},
                   [4]= {name="战士",chance=0.0417,max=1,min=1,sid=20533,type=0,},
                   [5]= {name="战士",chance=0.0317,max=1,min=1,sid=20534,type=0,},
                   [6]= {name="战士",chance=0.0517,max=1,min=1,sid=20535,type=0,},
                   [7]= {name="战士",chance=0.0317,max=1,min=1,sid=20536,type=0,},
                   [8]= {name="战士",chance=0.0417,max=1,min=1,sid=20537,type=0,},
				   [9]= {name="战士",chance=0.0517,max=1,min=1,sid=20538,type=0,},
				   ----------------------------------------------------------
                   [10]= {name="法师",chance=0.0117,max=1,min=1,sid=20540,type=0,},
                   [11]= {name="法师",chance=0.0217,max=1,min=1,sid=20541,type=0,},
                   [12]= {name="法师",chance=0.0317,max=1,min=1,sid=20542,type=0,},
                 --[13]= {name="法师",chance=1,max=1,min=1,sid=20173,type=0,},
                   [13]= {name="法师",chance=0.0217,max=1,min=1,sid=20544,type=0,},
                   [14]= {name="法师",chance=0.0317,max=1,min=1,sid=20545,type=0,},
                   [15]= {name="法师",chance=0.0117,max=1,min=1,sid=20546,type=0,},
                   [16]= {name="法师",chance=0.0317,max=1,min=1,sid=20547,type=0,},
                   [17]= {name="法师",chance=0.0317,max=1,min=1,sid=20548,type=0,},
                   ----------------------------------------------------------
				   [18]= {name="道士",chance=0.0217,max=1,min=1,sid=20550,type=0,},
                   [19]= {name="道士",chance=0.0517,max=1,min=1,sid=20551,type=0,},
                   [20]= {name="道士",chance=0.0317,max=1,min=1,sid=20552,type=0,},
                 --[21]= {name="道士",chance=1,max=1,min=1,sid=20053,type=0,},
				   [21]= {name="道士",chance=0.0317,max=1,min=1,sid=20554,type=0,},
				   [22]= {name="道士",chance=0.0417,max=1,min=1,sid=20555,type=0,},
				   [23]= {name="道士",chance=0.0317,max=1,min=1,sid=20556,type=0,},
				   [24]= {name="道士",chance=0.0217,max=1,min=1,sid=20557,type=0,},
				   [25]= {name="道士",chance=0.0317,max=1,min=1,sid=20558,type=0,},
				},
			type=1,
		},
		------------------------------------------------------------------------------------------------
		------------------------------------------------------------------------------------------------
	[701]= {
			id=701,
			name="地狱男爵",
			elems= {
			        [1]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[2]= {chance=0.3,max=1,min=1,sid=697,type=1,},--8套
					[3]= {name="元宝",chance=1,datax=500000,datay=1000000,max=1,min=1,sid=3,type=0,},
					[4]= {name="金蚕王",chance=1,max=10,min=5,sid=30059,type=0,},
					[5]= {name="16级魂石袋",chance=0.5,max=1,min=1,sid=51114,type=0,},
					[6]= {name="复生戒指",chance=1,max=1,min=1,sid=60223,type=0,},
					[7]= {name="定身戒指",chance=1,max=1,min=1,sid=60231,type=0,},
					[8]= {name="护法戒指",chance=1,max=1,min=1,sid=60239,type=0,},
					[9]= {name="突破蛋",chance=1,max=5,min=2,sid=5555,type=0,},
					[10]= {name="任务完成符",chance=0.8,max=1,min=1,sid=40045,type=0,},
					--[9]= {name="1元充值",chance=0.8,max=3,min=1,sid=101,type=0,},
					
				},
			max=81,
			type=0,
		},
	[702]= {
			id=702,
			name="暗夜守护",
			elems= {
					[1]= {name="元宝",chance=1,datax=500000,datay=1000000,max=1,min=1,sid=3,type=0,},
					[2]= {name="金蚕王",chance=1,max=10,min=5,sid=30059,type=0,},
					[3]= {name="15级魂石袋",chance=1,max=5,min=2,sid=30348,type=0,},
					[4]= {name="1元充值",chance=1,max=1,min=1,sid=101,type=0,},
					[5]= {chance=0.1,max=1,min=1,sid=697,type=1,},
					[6]= {name="突破蛋",chance=1,max=10,min=2,sid=5555,type=0,},
					[7]= {name="16级魂石袋",chance=0.8,max=1,min=1,sid=51114,type=0,},
					
				},
			max=81,
			type=0,
		},
	[703]= {
			id=703,
			name="暗夜驯兽",
			elems= {
					[1]= {name="元宝",chance=1,datax=500000,datay=1000000,max=1,min=1,sid=3,type=0,},
					[2]= {name="金蚕王",chance=1,max=10,min=5,sid=30059,type=0,},
					[3]= {name="15级魂石袋",chance=1,max=5,min=2,sid=30348,type=0,},
					[4]= {name="1元充值",chance=1,max=1,min=1,sid=101,type=0,},
					[5]= {chance=0.3,max=1,min=1,sid=697,type=1,},
					[6]= {name="突破蛋",chance=1,max=10,min=2,sid=5555,type=0,},
					[7]= {name="16级魂石袋",chance=0.8,max=1,min=1,sid=51114,type=0,},
				
				},
			max=81,
			type=0,
		},
	[704]= {
			id=704,
			name="暗夜巡查",
			elems= {
			        [1]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[2]= {name="15级魂石袋",chance=1,max=1,min=1,sid=30348,type=0,},
					[3]= {name="元宝",chance=1,datax=30000,datay=50000,max=1,min=1,sid=3,type=0,},
					[4]= {name="仙玉",chance=1,datax=10000,datay=30000,max=1,min=1,sid=4,type=0,},
					[5]= {name="金蚕王",chance=1,max=5,min=2,sid=30059,type=0,},
					
				},
			max=81,
			type=0,
		},
		-------------------------------------------副本深渊boos------------------------------------------
		[710]= {
			id=710,
			name="深渊小boss",
			elems= {
			        [1]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[2]= {chance=0.1,max=1,min=1,sid=664,type=1,},
					[3]= {name="15级魂石袋",chance=0.1,max=1,min=1,sid=30348,type=0,},
					[4]= {name="复生戒指",chance=0.2,max=1,min=1,sid=60223,type=0,},
					[5]= {name="定身戒指",chance=0.3,max=1,min=1,sid=60231,type=0,},
					[6]= {name="护法戒指",chance=0.3,max=1,min=1,sid=60239,type=0,},
					
				},
			max=81,
			type=0,
		},
	[711]= {
			id=711,
			name="深渊boss",
			elems= {
			        [1]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[2]= {chance=0.7,max=1,min=1,sid=697,type=1,},
					[3]= {chance=0.6,max=1,min=1,sid=698,type=1,},
					[4]= {chance=0.1,max=1,min=1,sid=699,type=1,},
					[5]= {chance=0.05,max=1,min=1,sid=700,type=1,},
					[6]= {name="18级魂石袋",chance=0.8,max=4,min=2,sid=51116,type=0,},
					[7]= {name="19级魂石袋",chance=0.5,max=2,min=2,sid=51117,type=0,},
					
				},
			max=81,
			type=0,
		},
	
	
---------------------------------------------------------------------------------	
	--------------------------------------------------------------------------------------------------
	------------------------------------------------------------------------------------------
	--------------------------------------------------------------------------------------------------------
	-------------------------------------------------------------------------------------------------
	
	[800]= {
			id=800,
			name="怪物攻城小怪",
			elems= { 
					[1]= {name="暗影材料",chance=0.1,max=1,min=1,sid=41004,type=0,},
					
					
				},
			max=81,
			type=0,
		},
	[801]= {
			id=801,
			name="怪物攻城boos",
			elems= {
					[2]= {name="暗影材料",chance=0.3,max=1,min=1,sid=41004,type=0,},
					
				},
			max=81,
			type=0,
		},
	[802]= {
			id=802,
			name="机械boos",
			elems= {
			        [1]= {name="$大boss掉落稀有杂品",chance=1,max=2,min=1,sid=64,type=1,},
					[2]= {chance=0.3,max=1,min=1,sid=697,type=1,},--8套
					[3]= {name="元宝",chance=1,datax=200000,datay=500000,max=1,min=1,sid=3,type=0,},
					[4]= {name="金蚕王",chance=1,max=5,min=3,sid=30059,type=0,},
					[5]= {name="16级魂石袋",chance=0.5,max=1,min=1,sid=51114,type=0,},
					[6]= {name="复生戒指",chance=1,max=1,min=1,sid=60223,type=0,},
					[7]= {name="定身戒指",chance=1,max=1,min=1,sid=60231,type=0,},
					[8]= {name="护法戒指",chance=1,max=1,min=1,sid=60239,type=0,},
					[9]= {name="突破蛋",chance=1,max=1,min=1,sid=5555,type=0,},
					[10]= {name="任务完成符",chance=0.05,max=1,min=1,sid=40045,type=0,},
					--[9]= {name="1元充值",chance=0.8,max=3,min=1,sid=101,type=0,},
					
				},
			max=81,
			type=0,
		},
}
if not (type(gdTreasureHuntData)=="table") then
	gdTreasureHuntData = {}
end

gdTreasureHuntData = {
	[20]= {
			luckyloot= {[0]=607,[25]=612,[50]=617,[150]=622,[300]=627,[500]=632,},
			minlvl=20,
		},
	[40]= {
			luckyloot= {[0]=608,[25]=613,[50]=618,[150]=623,[300]=628,[500]=633,},
			minlvl=40,
		},
	[50]= {
			luckyloot= {[0]=609,[25]=614,[50]=619,[150]=624,[300]=629,[500]=634,},
			minlvl=50,
		},
	[60]= {
			luckyloot= {[0]=610,[25]=615,[50]=620,[150]=625,[300]=630,[500]=635,},
			minlvl=60,
		},
	[70]= {
			luckyloot= {[0]=611,[25]=616,[50]=621,[150]=626,[300]=631,[500]=636,},
			minlvl=70,
		},
}
if not (type(gdBroadcastLootID)=="table") then
	gdBroadcastLootID = {}
end

if not (type(gdBroadcastItemID)=="table") then
	gdBroadcastItemID = {}
end

gdBroadcastLootID = {--套装播放
	[12]=true,
	[13]=true,
	[14]=true,
	[15]=true,
	[16]=true,
	[19]=true,
	[20]=true,
	[21]=true,
	[22]=true,
	[23]=true,
	[24]=true,
	[25]=true,
	[26]=true,
	[27]=true,
	[32]=true,
	[33]=true,
	[34]=true,
	[35]=true,
	[36]=true,
	[37]=true,
	[38]=true,
	[39]=true,
	[661]=true,
	[662]=true,
	[663]=true,
	[664]=true,
	[697]=true,
	[698]=true,
	[699]=true,
	[700]=true,
	
}
gdBroadcastItemID = {-------id播放
[30192]=true,
[30206]=true,
[30207]=true,
[30209]=true,
[30299]=true,
[30328]=true,
[30329]=true,
[40002]=true,
[40003]=true,
[40004]=true,
[60329]=true,
[51114]=true,--16级魂石袋
[51115]=true,--17级魂石袋
[51116]=true,--18级魂石袋
[51117]=true,--19级魂石袋
[51118]=true,--20级魂石袋
}
if not (type(gdLootnametoID)=="table") then
	gdLootnametoID = {}
end

gdLootnametoID["万年古墓BOSS"] = 189
gdLootnametoID["中boss掉落稀有杂品"] = 62
gdLootnametoID["牛魔王4"] = 381
gdLootnametoID["六级魂石"] = 34
gdLootnametoID["熔岩火龙王1"] = 370
gdLootnametoID["傀儡妖人"] = 252
gdLootnametoID["10级装备"] = 3
gdLootnametoID["冰骨魔龙4"] = 393
gdLootnametoID["龙影坛BOSS"] = 247
gdLootnametoID["20级装备"] = 4
gdLootnametoID["十级魂石"] = 38
gdLootnametoID["免费寻宝"] = 637
gdLootnametoID["30-35级怪"] = 114
gdLootnametoID["高家店小怪"] = 238
gdLootnametoID["异形魔尊4"] = 369
gdLootnametoID["等级20以上|幸运0以上"] = 607
gdLootnametoID["天蝎座小怪"] = 281
gdLootnametoID["寻宝70级套装"] = 598
gdLootnametoID["无双赤鬼"] = 265
gdLootnametoID["技能书"] = 42
gdLootnametoID["41级怪金币"] = 85
gdLootnametoID["51级怪金币"] = 95
gdLootnametoID["雪域精英"] = 152
gdLootnametoID["冰麒麟(6-10)"] = 473
gdLootnametoID["等级60以上|幸运300以上"] = 630
gdLootnametoID["寻宝50级套装"] = 595
gdLootnametoID["冰麒麟4"] = 389
gdLootnametoID["55级套装武器"] = 21
gdLootnametoID["火凤(0-5)"] = 423
gdLootnametoID["冰骨魔龙(16-20)"] = 503
gdLootnametoID["高级技能书"] = 44
gdLootnametoID["1阶寻宝物品道具"] = 579
gdLootnametoID["采花大盗1"] = 323
gdLootnametoID["赤练猪卫(6-10)"] = 524
gdLootnametoID["远古矿洞1"] = 350
gdLootnametoID["黑龙教主(11-15)"] = 552
gdLootnametoID["英雄城守卫军BOSS"] = 302
gdLootnametoID["50-55级怪金币"] = 73
gdLootnametoID["摩羯座小怪"] = 276
gdLootnametoID["水域龙都小怪"] = 205
gdLootnametoID["20-25级怪金币"] = 67
gdLootnametoID["70级寻宝装备"] = 606
gdLootnametoID["焚天星宫1"] = 329
gdLootnametoID["50级寻宝装备"] = 604
gdLootnametoID["冰骨魔龙2"] = 391
gdLootnametoID["龙影坛1"] = 347
gdLootnametoID["王城精英"] = 139
gdLootnametoID["十二星宫1"] = 333
gdLootnametoID["色魔"] = 136
gdLootnametoID["种子"] = 83
gdLootnametoID["55级散件"] = 10
gdLootnametoID["45级散件"] = 8
gdLootnametoID["55-60级怪"] = 124
gdLootnametoID["魔神封印1"] = 363
gdLootnametoID["45-50级怪金币"] = 72
gdLootnametoID["40-45级怪"] = 118
gdLootnametoID["采花大盗小怪"] = 303
gdLootnametoID["采花大盗BOSS"] = 304
gdLootnametoID["狩猎场BOSS"] = 298
gdLootnametoID["天帝宝库五号BOSS"] = 199
gdLootnametoID["祭魔结阵1"] = 342
gdLootnametoID["经验玉掉落"] = 56
gdLootnametoID["黑龙教主(0-5)"] = 548
gdLootnametoID["天地宝库小怪"] = 194
gdLootnametoID["祖玛教皇(16-20)"] = 522
gdLootnametoID["等级70以上|幸运0以上"] = 611
gdLootnametoID["水域龙都前3BOSS"] = 207
gdLootnametoID["35级散件"] = 7
gdLootnametoID["天帝宝库九号BOSS"] = 203
gdLootnametoID["45级套装"] = 18
gdLootnametoID["圣火争霸1"] = 322
gdLootnametoID["70-75级怪金币"] = 77
gdLootnametoID["生死状三四"] = 47
gdLootnametoID["寻宝40级套装"] = 593
gdLootnametoID["冥轮王蛇2"] = 383
gdLootnametoID["梦魇魔域1"] = 349
gdLootnametoID["寻宝60级套装"] = 597
gdLootnametoID["天帝宝库三号BOSS"] = 197
gdLootnametoID["双鱼座小怪"] = 278
gdLootnametoID["矿锄"] = 153
gdLootnametoID["等级20以上|幸运25以上"] = 612
gdLootnametoID["战神史册"] = 156
gdLootnametoID["等级40以上|幸运300以上"] = 628
gdLootnametoID["亢金龙残影"] = 320
gdLootnametoID["发财礼包3级"] = 318
gdLootnametoID["宝矿洞窟怪"] = 193
gdLootnametoID["绝望沙漠小怪"] = 216
gdLootnametoID["小怪掉落杂品"] = 57
gdLootnametoID["五级魂石"] = 33
gdLootnametoID["恶魔庇护所1"] = 352
gdLootnametoID["攻城战1"] = 335
gdLootnametoID["所有魂石"] = 40
gdLootnametoID["55-60级怪金币"] = 74
gdLootnametoID["天龟水神(0-5)"] = 561
gdLootnametoID["天地宝库一号BOSS"] = 195
gdLootnametoID["最高金币"] = 79
gdLootnametoID["冥轮王蛇(16-20)"] = 464
gdLootnametoID["攻沙元宝奖励1"] = 344
gdLootnametoID["0-10级怪"] = 106
gdLootnametoID["魔神印记1"] = 355
gdLootnametoID["30-35级怪金币"] = 69
gdLootnametoID["天龟水神(6-10)"] = 565
gdLootnametoID["天地降魔1"] = 362
gdLootnametoID["五指山隐藏BOSS"] = 244
gdLootnametoID["新手装"] = 2
gdLootnametoID["狮子座小怪"] = 274
gdLootnametoID["水域龙都龙女"] = 209
gdLootnametoID["幽灵船精英"] = 148
gdLootnametoID["水域龙都龙王"] = 211
gdLootnametoID["湮灭沙漠1"] = 353
gdLootnametoID["水寨小怪"] = 234
gdLootnametoID["5阶寻宝灵珠"] = 584
gdLootnametoID["6阶寻宝灵珠"] = 585
gdLootnametoID["3阶寻宝灵珠"] = 582
gdLootnametoID["经验水晶宫1"] = 330
gdLootnametoID["蚁后(0-5)"] = 531
gdLootnametoID["2阶寻宝灵珠"] = 581
gdLootnametoID["火凤3"] = 376
gdLootnametoID["超级药"] = 1
gdLootnametoID["天帝宝库四号BOSS"] = 198
gdLootnametoID["70-75级怪"] = 130
gdLootnametoID["烈火宫"] = 284
gdLootnametoID["58级怪金币"] = 102
gdLootnametoID["邪恶钳虫(0-5)"] = 527
gdLootnametoID["黄泉领主(6-10)"] = 537
gdLootnametoID["60级套装零件"] = 24
gdLootnametoID["50级套装零件"] = 20
gdLootnametoID["48级怪金币"] = 92
gdLootnametoID["60-65级怪"] = 126
gdLootnametoID["40-45级怪金币"] = 71
gdLootnametoID["四级魂石"] = 32
gdLootnametoID["天龟水神(16-20)"] = 574
gdLootnametoID["荣誉将军"] = 306
gdLootnametoID["老手鹤嘴锄"] = 50
gdLootnametoID["金牛座小怪"] = 272
gdLootnametoID["高家店BOSS"] = 239
gdLootnametoID["活跃礼包的数据"] = 638
gdLootnametoID["冰骨魔龙3"] = 392
gdLootnametoID["等级70以上|幸运500以上"] = 636
gdLootnametoID["神的纯银鹤嘴锄"] = 54
gdLootnametoID["等级60以上|幸运500以上"] = 635
gdLootnametoID["70级勋章"] = 16
gdLootnametoID["勇士竞技场1"] = 340
gdLootnametoID["等级50以上|幸运500以上"] = 634
gdLootnametoID["等级40以上|幸运500以上"] = 633
gdLootnametoID["等级20以上|幸运500以上"] = 632
gdLootnametoID["40级勋章"] = 11
gdLootnametoID["50级勋章"] = 13
gdLootnametoID["60级勋章"] = 15
gdLootnametoID["绝望沙漠BOSS"] = 221
gdLootnametoID["赤月魔尊"] = 225
gdLootnametoID["等级50以上|幸运300以上"] = 629
gdLootnametoID["祈福树1"] = 364
gdLootnametoID["火凤1"] = 374
gdLootnametoID["55级套装零件"] = 22
gdLootnametoID["矿洞二层以上精英"] = 143
gdLootnametoID["镇魔塔1"] = 357
gdLootnametoID["冥轮王蛇(6-10)"] = 457
gdLootnametoID["等级60以上|幸运150以上"] = 625
gdLootnametoID["等级50以上|幸运150以上"] = 624
gdLootnametoID["等级70以上|幸运50以上"] = 621
gdLootnametoID["赤月BOSS"] = 192
gdLootnametoID["等级40以上|幸运150以上"] = 623
gdLootnametoID["牛魔王2"] = 379
gdLootnametoID["异形魔尊1"] = 366
gdLootnametoID["九级魂石"] = 37
gdLootnametoID["五行炼狱"] = 229
gdLootnametoID["等级50以上|幸运50以上"] = 619
gdLootnametoID["等级40以上|幸运50以上"] = 618
gdLootnametoID["等级20以上|幸运50以上"] = 617
gdLootnametoID["25-30级怪"] = 112
gdLootnametoID["等级70以上|幸运25以上"] = 616
gdLootnametoID["黑龙教主(6-10)"] = 550
gdLootnametoID["角斗之王"] = 271
gdLootnametoID["等级60以上|幸运25以上"] = 615
gdLootnametoID["熔岩火龙王3"] = 372
gdLootnametoID["等级40以上|幸运25以上"] = 613
gdLootnametoID["45-50级怪"] = 120
gdLootnametoID["冰骨魔龙1"] = 390
gdLootnametoID["等级60以上|幸运0以上"] = 610
gdLootnametoID["地狱结界怪"] = 227
gdLootnametoID["物攻击魂石"] = 41
gdLootnametoID["赤练猪卫(0-5)"] = 523
gdLootnametoID["蚁后(11-15)"] = 533
gdLootnametoID["异形魔尊(11-15)"] = 403
gdLootnametoID["56级怪金币"] = 100
gdLootnametoID["46级怪金币"] = 90
gdLootnametoID["邪恶钳虫(11-15)"] = 529
gdLootnametoID["寒晶海底1"] = 354
gdLootnametoID["黄泉领主(16-20)"] = 543
gdLootnametoID["60级寻宝装备"] = 605
gdLootnametoID["勇士"] = 269
gdLootnametoID["40级寻宝装备"] = 603
gdLootnametoID["魂石怪物"] = 309
gdLootnametoID["20级寻宝装备"] = 602
gdLootnametoID["寻宝高级技能书"] = 600
gdLootnametoID["冥轮王蛇4"] = 385
gdLootnametoID["寻宝55级套装"] = 596
gdLootnametoID["土城抗魔1"] = 321
gdLootnametoID["寻宝45级套装"] = 594
gdLootnametoID["金甲尸王(16-20)"] = 517
gdLootnametoID["城主膜拜1"] = 338
gdLootnametoID["绝望峡谷1"] = 346
gdLootnametoID["射手座小怪"] = 277
gdLootnametoID["美女护送1"] = 332
gdLootnametoID["75级精英怪"] = 179
gdLootnametoID["初级技能书"] = 43
gdLootnametoID["55级精英怪"] = 171
gdLootnametoID["45级精英怪"] = 167
gdLootnametoID["59级怪金币"] = 103
gdLootnametoID["降妖除魔1"] = 337
gdLootnametoID["金甲尸王(6-10)"] = 513
gdLootnametoID["金甲尸王(11-15)"] = 515
gdLootnametoID["双子座小怪"] = 275
gdLootnametoID["火焰战将"] = 249
gdLootnametoID["4阶寻宝魂石"] = 589
gdLootnametoID["49级怪金币"] = 93
gdLootnametoID["地牢探险1"] = 336
gdLootnametoID["金甲尸王(0-5)"] = 511
gdLootnametoID["转生地陵（仅限单人）1"] = 365
gdLootnametoID["天秤座小怪"] = 280
gdLootnametoID["祖玛教皇(0-5)"] = 519
gdLootnametoID["25级武器"] = 5
gdLootnametoID["勋章怪物"] = 307
gdLootnametoID["狩猎场小怪"] = 297
gdLootnametoID["50级散件"] = 9
gdLootnametoID["10-20级怪金币"] = 66
gdLootnametoID["冥轮王蛇(0-5)"] = 453
gdLootnametoID["转生副本小怪"] = 248
gdLootnametoID["九天冰宫二层掉落"] = 289
gdLootnametoID["4阶寻宝灵珠"] = 583
gdLootnametoID["绝望沙漠精英小怪"] = 217
gdLootnametoID["1阶寻宝灵珠"] = 580
gdLootnametoID["35级精英怪"] = 164
gdLootnametoID["白羊座小怪"] = 282
gdLootnametoID["天龟水神(11-15)"] = 569
gdLootnametoID["黑龙教主(16-20)"] = 556
gdLootnametoID["生死状一二"] = 45
gdLootnametoID["邪恶钳虫(16-20)"] = 530
gdLootnametoID["黄泉领主(11-15)"] = 539
gdLootnametoID["黄泉领主(0-5)"] = 535
gdLootnametoID["蚁后(16-20)"] = 534
gdLootnametoID["冰麒麟(0-5)"] = 468
gdLootnametoID["55级勋章"] = 14
gdLootnametoID["45级勋章"] = 12
gdLootnametoID["蚁后(6-10)"] = 532
gdLootnametoID["等级40以上|幸运0以上"] = 608
gdLootnametoID["60级套装武器"] = 23
gdLootnametoID["50级套装武器"] = 19
gdLootnametoID["邪恶钳虫(6-10)"] = 528
gdLootnametoID["蛮荒精英"] = 149
gdLootnametoID["60级以上怪金币"] = 104
gdLootnametoID["44级怪金币"] = 88
gdLootnametoID["赤练猪卫(16-20)"] = 526
gdLootnametoID["祖玛教皇(11-15)"] = 521
gdLootnametoID["十一级魂石"] = 39
gdLootnametoID["英雄城守卫军1"] = 334
gdLootnametoID["七级魂石"] = 35
gdLootnametoID["70级套装武器"] = 25
gdLootnametoID["25-30级怪金币"] = 68
gdLootnametoID["龙影坛小怪"] = 246
gdLootnametoID["等级50以上|幸运0以上"] = 609
gdLootnametoID["皇家守卫1"] = 325
gdLootnametoID["赤练猪卫(11-15)"] = 525
gdLootnametoID["水域龙都真龙王"] = 214
gdLootnametoID["沃玛主教"] = 509
gdLootnametoID["纯银、宝石鹤嘴锄"] = 52
gdLootnametoID["35-40级怪"] = 116
gdLootnametoID["75-80级怪金币"] = 78
gdLootnametoID["虫洞精英"] = 144
gdLootnametoID["飞天神猪"] = 155
gdLootnametoID["冰骨魔龙(11-15)"] = 498
gdLootnametoID["镇天塔1"] = 360
gdLootnametoID["跨服攻城战1"] = 394
gdLootnametoID["冰骨魔龙(0-5)"] = 488
gdLootnametoID["冰麒麟(16-20)"] = 483
gdLootnametoID["65级精英怪"] = 175
gdLootnametoID["异形魔尊(16-20)"] = 406
gdLootnametoID["九天冰宫一层掉落"] = 285
gdLootnametoID["锭"] = 82
gdLootnametoID["牛魔王(16-20)"] = 449
gdLootnametoID["47级怪金币"] = 91
gdLootnametoID["57级怪金币"] = 101
gdLootnametoID["天帝宝库十号BOSS"] = 204
gdLootnametoID["幻武碎片"] = 601
gdLootnametoID["牛魔王(6-10)"] = 442
gdLootnametoID["牛魔王(0-5)"] = 438
gdLootnametoID["生死状二三"] = 46
gdLootnametoID["50-55级怪"] = 122
gdLootnametoID["火凤(16-20)"] = 434
gdLootnametoID["火凤(11-15)"] = 430
gdLootnametoID["火凤(6-10)"] = 427
gdLootnametoID["生死状四五"] = 48
gdLootnametoID["神的黄金鹤嘴锄"] = 55
gdLootnametoID["战队竞技1"] = 345
gdLootnametoID["熔岩火龙王(11-15)"] = 416
gdLootnametoID["熔岩火龙王(6-10)"] = 413
gdLootnametoID["马拉松1"] = 331
gdLootnametoID["大富翁1"] = 324
gdLootnametoID["冥轮王蛇(11-15)"] = 460
gdLootnametoID["异形魔尊(6-10)"] = 400
gdLootnametoID["冥魂神殿1"] = 395
gdLootnametoID["52级怪金币"] = 96
gdLootnametoID["42级怪金币"] = 86
gdLootnametoID["异形魔尊(0-5)"] = 396
gdLootnametoID["冰骨魔龙(6-10)"] = 493
gdLootnametoID["冰麒麟3"] = 388
gdLootnametoID["天帝宝库六号BOSS"] = 200
gdLootnametoID["冰麒麟2"] = 387
gdLootnametoID["三级魂石"] = 31
gdLootnametoID["魔神封印BOSS"] = 231
gdLootnametoID["0-10级怪金币"] = 65
gdLootnametoID["寻宝转生技能书"] = 599
gdLootnametoID["称霸天下1"] = 341
gdLootnametoID["冥轮王蛇1"] = 382
gdLootnametoID["牛魔王3"] = 380
gdLootnametoID["牛魔王1"] = 378
gdLootnametoID["火凤4"] = 377
gdLootnametoID["海底世界精英"] = 150
gdLootnametoID["火凤2"] = 375
gdLootnametoID["等级20以上|幸运300以上"] = 627
gdLootnametoID["70级精英怪"] = 177
gdLootnametoID["80级精英怪"] = 181
gdLootnametoID["50级精英怪"] = 169
gdLootnametoID["60级精英怪"] = 173
gdLootnametoID["30级精英怪"] = 162
gdLootnametoID["40级精英怪"] = 166
gdLootnametoID["75-80级怪"] = 132
gdLootnametoID["20级精英怪"] = 158
gdLootnametoID["熔岩火龙王4"] = 373
gdLootnametoID["等级50以上|幸运25以上"] = 614
gdLootnametoID["熔岩火龙王2"] = 371
gdLootnametoID["劫魔"] = 137
gdLootnametoID["异形魔尊3"] = 368
gdLootnametoID["异形魔尊2"] = 367
gdLootnametoID["等级20以上|幸运150以上"] = 622
gdLootnametoID["保卫萝卜1"] = 361
gdLootnametoID["镇地塔1"] = 359
gdLootnametoID["一级魂石"] = 29
gdLootnametoID["镇妖塔1"] = 358
gdLootnametoID["巨蟹座小怪"] = 273
gdLootnametoID["深渊结界1"] = 356
gdLootnametoID["皇室藏宝地1"] = 351
gdLootnametoID["小boss掉落稀有杂品"] = 60
gdLootnametoID["九天冰宫三层掉落"] = 293
gdLootnametoID["熔岩火龙王(16-20)"] = 419
gdLootnametoID["荣誉神殿1"] = 343
gdLootnametoID["45级怪金币"] = 89
gdLootnametoID["55级怪金币"] = 99
gdLootnametoID["冥轮王蛇3"] = 384
gdLootnametoID["黄金鹤嘴锄"] = 53
gdLootnametoID["60-65级怪金币"] = 75
gdLootnametoID["矿洞精英"] = 142
gdLootnametoID["新手鹤嘴锄"] = 49
gdLootnametoID["10-20级怪"] = 108
gdLootnametoID["群雄逐鹿1"] = 339
gdLootnametoID["30级装备"] = 6
gdLootnametoID["寻宝戒指"] = 592
gdLootnametoID["情魔"] = 135
gdLootnametoID["小boss掉落常用杂品"] = 59
gdLootnametoID["小精英怪掉落杂品"] = 58
gdLootnametoID["心魔"] = 134
gdLootnametoID["二级魂石"] = 30
gdLootnametoID["发财礼包2级"] = 316
gdLootnametoID["特殊戒指"] = 27
gdLootnametoID["40级怪金币"] = 84
gdLootnametoID["熔岩火龙王(0-5)"] = 410
gdLootnametoID["圣战、法神、道尊"] = 223
gdLootnametoID["50级怪金币"] = 94
gdLootnametoID["65-70级怪"] = 128
gdLootnametoID["贵族陵墓1"] = 348
gdLootnametoID["35-40级怪金币"] = 70
gdLootnametoID["护花使者1"] = 327
gdLootnametoID["魂石碎片"] = 28
gdLootnametoID["灵珠怪物"] = 311
gdLootnametoID["欲魔"] = 138
gdLootnametoID["妖月峡谷小怪"] = 183
gdLootnametoID["妖月峡谷BOSS"] = 185
gdLootnametoID["火爆龙将"] = 261
gdLootnametoID["等级60以上|幸运50以上"] = 620
gdLootnametoID["发财礼包1级"] = 314
gdLootnametoID["秘珠怪物"] = 313
gdLootnametoID["25级精英怪"] = 160
gdLootnametoID["火龙洞精英"] = 147
gdLootnametoID["天帝宝库七号BOSS"] = 201
gdLootnametoID["处女座小怪"] = 283
gdLootnametoID["灵石"] = 80
gdLootnametoID["中boss掉落常用杂品"] = 61
gdLootnametoID["大boss掉落常用杂品"] = 63
gdLootnametoID["3阶寻宝魂石"] = 588
gdLootnametoID["2阶寻宝魂石"] = 587
gdLootnametoID["1阶寻宝魂石"] = 586
gdLootnametoID["水瓶座小怪"] = 279
gdLootnametoID["水寨BOSS"] = 235
gdLootnametoID["6阶寻宝魂石"] = 591
gdLootnametoID["5阶寻宝魂石"] = 590
gdLootnametoID["牛魔王(11-15)"] = 445
gdLootnametoID["53级怪金币"] = 97
gdLootnametoID["等级70以上|幸运150以上"] = 626
gdLootnametoID["行会争夺战1"] = 326
gdLootnametoID["43级怪金币"] = 87
gdLootnametoID["死灵冰眼"] = 258
gdLootnametoID["雷火狼尸"] = 255
gdLootnametoID["五指山BOSS"] = 242
gdLootnametoID["65-70级怪金币"] = 76
gdLootnametoID["土城抗魔"] = 140
gdLootnametoID["40级套装"] = 17
gdLootnametoID["冰麒麟1"] = 386
gdLootnametoID["八级魂石"] = 36
gdLootnametoID["熔火之心1"] = 328
gdLootnametoID["等级70以上|幸运300以上"] = 631
gdLootnametoID["祖玛教皇(6-10)"] = 520
gdLootnametoID["天帝宝库八号BOSS"] = 202
gdLootnametoID["20-25级怪"] = 110
gdLootnametoID["英雄城守卫军小怪"] = 301
gdLootnametoID["天帝宝库二号BOSS"] = 196
gdLootnametoID["赤月小怪"] = 190
gdLootnametoID["万年古墓小怪"] = 187
gdLootnametoID["沙漠门神"] = 219
gdLootnametoID["大师鹤嘴锄"] = 51
gdLootnametoID["荣誉"] = 81
gdLootnametoID["大boss掉落稀有杂品"] = 64
gdLootnametoID["70级套装零件"] = 26
gdLootnametoID["冰麒麟(11-15)"] = 478
gdLootnametoID["五指山小怪"] = 241
gdLootnametoID["教皇寺庙精英"] = 146
gdLootnametoID["猪妖洞精英"] = 145
gdLootnametoID["54级怪金币"] = 98
gdLootnametoID["暗之煞翼队长"] = 141
---------------------------------------------------------------------------------------------------------




gdLootnametoID["将军凌小怪"] = 639
gdLootnametoID["将军陵小怪"] = 640
gdLootnametoID["暗夜殿小怪"] = 641

gdLootnametoID["古陵玄宫小怪"] = 642
gdLootnametoID["星界囚笼小怪"] = 643




gdLootnametoID["世界boss1"] = 673
gdLootnametoID["世界boss2"] = 674
gdLootnametoID["世界boss3"] = 675
gdLootnametoID["世界boss4"] = 676
gdLootnametoID["世界boss5"] = 677
gdLootnametoID["世界boss6"] = 678
gdLootnametoID["世界boss7"] = 679
-------------------------------------------------
gdLootnametoID["地图boss1"] = 688
gdLootnametoID["地图boss2"] = 689
gdLootnametoID["地图boss3"] = 690
gdLootnametoID["地图boss4"] = 691
gdLootnametoID["地图boss5"] = 692
gdLootnametoID["地图boss6"] = 693
gdLootnametoID["地图boss7"] = 694
gdLootnametoID["地图boss8"] = 695
gdLootnametoID["地图boss9"] = 696
-------------------------------------------------
gdLootnametoID["地狱男爵"] = 701
gdLootnametoID["暗夜守护"] = 702
gdLootnametoID["暗夜驯兽"] = 703
gdLootnametoID["暗夜巡查"] = 704


-----------------------------------
gdLootnametoID["深渊小boss"] = 710
gdLootnametoID["深渊boss"] = 711


-----------------------------
gdLootnametoID["怪物攻城小怪"] = 800
gdLootnametoID["怪物攻城boos"] = 801

gdLootnametoID["机械boos"] = 802