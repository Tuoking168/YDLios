if not (type(gdSpiderParts)=="table") then
	gdSpiderParts = {}
end

if not (type(gdSpiderPackages)=="table") then
	gdSpiderPackages = {}
end

if not (type(gdSpiderRewardEx)=="table") then
	gdSpiderRewardEx = {}
end
 gdSpiderParts[1] = {
	maxlvl=40,
	minlvl=35,
	reqcnt=1,
	[1]= {datamax=49800,datamin=46500,probability=0,sid=1,},
	[2]= {datamax=50,datamin=10,probability=8000,sid=2,},
}
gdSpiderParts[2] = {
	maxlvl=46,
	minlvl=41,
	nextitem=1,
	reqcnt=2,
	[1]= {datamax=498000,datamin=465000,probability=0,sid=1,},
	[2]= {datamax=88,datamin=20,probability=6321,sid=2,},
}
gdSpiderParts[3] = {
	maxlvl=50,
	minlvl=47,
	nextitem=2,
	reqcnt=2,
	[1]= {datamax=547000,datamin=523000,probability=0,sid=1,},
	[2]= {datamax=100,datamin=30,probability=6213,sid=2,},
	
}
gdSpiderParts[4] = {
	maxlvl=52,
	minlvl=51,
	reqcnt=5,
	[1]= {datamax=547000,datamin=523000,probability=0,sid=1,},
	[2]= {datamax=100,datamin=30,probability=6234,sid=2,},
	
}
gdSpiderParts[5] = {
	maxlvl=58,
	minlvl=53,
	nextitem=3,
	reqcnt=5,
	[1]= {datamax=602500,datamin=587500,probability=0,sid=1,},
	[2]= {datamax=100,datamin=30,probability=6233,sid=2,},

}
gdSpiderParts[6] = {
	maxlvl=60,
	minlvl=59,
	nextitem=4,
	reqcnt=5,
	[1]= {datamax=664800,datamin=643700,probability=0,sid=1,},
	[2]= {datamax=200,datamin=100,probability=6233,sid=2,},
}
gdSpiderParts[7] = {
	maxlvl=64,
	minlvl=61,
	reqcnt=8,
	[1]= {datamax=664800,datamin=643700,probability=0,sid=1,},
	[2]= {datamax=200,datamin=100,probability=6215,sid=2,},
	
}
gdSpiderParts[8] = {
	maxlvl=70,
	minlvl=65,
	reqcnt=8,
	[1]= {datamax=752600,datamin=715400,probability=0,sid=1,},
	[2]= {datamax=300,datamin=100,probability=6163,sid=2,},
	
}
gdSpiderPackages[1] = {
	maxlvl=40,
	minlvl=40,
	reqcnt=3,
	[1]= {datamax=52300,datamin=49800,probability=0,sid=1,},
	[2]= {datamax=50,datamin=20,probability=6648,sid=2,},

}
gdSpiderPackages[2] = {
	maxlvl=45,
	minlvl=45,
	reqcnt=3,
	[1]= {datamax=523000,datamin=498000,probability=0,sid=1,},
	[2]= {datamax=88,datamin=30,probability=6607,sid=2,},
	}
gdSpiderPackages[3] = {
	maxlvl=50,
	minlvl=50,
	reqcnt=4,
	[1]= {datamax=587500,datamin=547000,probability=0,sid=1,},
	[2]= {datamax=100,datamin=40,probability=6589,sid=2,},
}
gdSpiderPackages[4] = {
	maxlvl=55,
	minlvl=55,
	reqcnt=5,
	[1]= {datamax=664800,datamin=643700,probability=0,sid=1,},
	[2]= {datamax=100,datamin=50,probability=6519,sid=2,},
}
gdSpiderPackages[5] = {
	maxlvl=60,
	minlvl=60,
	reqcnt=5,
	[1]= {datamax=752600,datamin=715400,probability=0,sid=1,},
	[2]= {datamax=500,datamin=200,probability=6520,sid=2,},
	
}
gdSpiderPackages[6] = {
	maxlvl=65,
	minlvl=65,
	reqcnt=8,
	[1]= {datamax=864200,datamin=823700,probability=0,sid=1,},
	[2]= {datamax=1000,datamin=500,probability=6470,sid=2,},

}
gdSpiderPackages[7] = {
	maxlvl=70,
	minlvl=70,
	reqcnt=8,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=3000,datamin=2000,probability=6270,sid=2,},
	
	
}
gdSpiderPackages[8] = {
	maxlvl=75,
	minlvl=75,
	reqcnt=8,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=6000,datamin=3000,probability=6270,sid=2,},
	[3]= {data=2,probability=1000,sid=41003,},--回收材料装备残魂
	
}
gdSpiderPackages[9] = {
	maxlvl=80,
	minlvl=80,
	reqcnt=8,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=8000,datamin=4000,probability=6270,sid=2,},
	[3]= {data=5,probability=1000,sid=41003,},--回收材料装备残魂

}
gdSpiderPackages[10] = {
	maxlvl=85,
	minlvl=85,
	reqcnt=9,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=10000,datamin=5000,probability=6270,sid=2,},
	[3]= {data=6,probability=2000,sid=41003,},--回收材料装备残魂
}
gdSpiderPackages[11] = {
	maxlvl=90,
	minlvl=90,
	reqcnt=10,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=20000,datamin=8000,probability=6270,sid=2,},
	[3]= {data=8,probability=3000,sid=41003,},--回收材料装备残魂
}
gdSpiderPackages[12] = {
	maxlvl=95,
	minlvl=95,
	reqcnt=20,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=50000,datamin=12000,probability=6270,sid=2,},
	[3]= {data=10,probability=4000,sid=41003,},--回收材料装备残魂
}
gdSpiderPackages[13] = {
	maxlvl=150,
	minlvl=150,
	reqcnt=2147483647,
	[1]= {datamax=9500000,datamin=9200000,probability=0,sid=1,},
	[2]= {datamax=300000,datamin=250000,probability=6270,sid=2,},
	[3]= {data=1,probability=372,sid=20329,},
	[4]= {data=1,probability=608,sid=20330,},
	[5]= {data=1,probability=388,sid=20331,},
	[6]= {data=1,probability=488,sid=20332,},
	[7]= {data=1,probability=508,sid=20333,},
	[8]= {data=1,probability=708,sid=20334,},
	[9]= {data=1,probability=588,sid=20335,},
	[10]= {data=1,probability=268,sid=20336,},
	[11]= {data=1,probability=718,sid=20337,},
}
gdSpiderPackages[14] = {
	maxlvl=160,
	minlvl=160,
	reqcnt=20,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=50000,datamin=12000,probability=6270,sid=2,},
	[3]= {data=12,probability=10000,sid=41003,},--回收材料装备残魂
}
gdSpiderPackages[15] = {
	maxlvl=180,
	minlvl=180,
	reqcnt=20,
	[1]= {datamax=950000,datamin=920000,probability=0,sid=1,},
	[2]= {datamax=50000,datamin=12000,probability=6270,sid=2,},
	[3]= {data=20,probability=10000,sid=41003,},--回收材料装备残魂
}
gdSpiderRewardEx[1] = {
	[1]= {itemid=70078,},
	[2]= {itemid=70084,},
	[3]= {itemid=70090,},
	[4]= {itemid=70093,},
	[5]= {itemid=70094,},
	[6]= {itemid=70095,},
	[7]= {itemid=70110,},
	[8]= {itemid=70111,},
	[9]= {itemid=70112,},
	[10]= {itemid=70115,},
	[11]= {itemid=70116,},
	[12]= {itemid=70117,},
	[13]= {itemid=70140,},
	[14]= {itemid=70149,},
	[15]= {itemid=70158,},
}
gdSpiderRewardEx[2] = {
	[1]= {itemid=70096,},
	[2]= {itemid=70097,},
	[3]= {itemid=70098,},
	[4]= {itemid=70099,},
	[5]= {itemid=70104,},
	[6]= {itemid=70105,},
	[7]= {itemid=70106,},
	[8]= {itemid=70107,},
	[9]= {itemid=70120,},
	[10]= {itemid=70121,},
	[11]= {itemid=70122,},
	[12]= {itemid=70123,},
	[13]= {itemid=70141,},
	[14]= {itemid=70150,},
	[15]= {itemid=70159,},
}
gdSpiderRewardEx[3] = {
	[1]= {itemid=70142,},
	[2]= {itemid=70151,},
	[3]= {itemid=70160,},
}
gdSpiderRewardEx[4] = {
	[1]= {itemid=70143,},
	[2]= {itemid=70152,},
	[3]= {itemid=70161,},
}
