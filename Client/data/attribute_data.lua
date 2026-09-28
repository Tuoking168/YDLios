if not (type(gdEnhanceAttribute)=="table") then
	gdEnhanceAttribute = {}
end

if not (type(gdStoneAttribute)=="table") then
	gdStoneAttribute = {}
end

if not (type(gdEvolutionAttribute)=="table") then
	gdEvolutionAttribute = {}
end

if not (type(gdEvolutionCondition)=="table") then
	gdEvolutionCondition = {}
end

if not (type(gdSuitAttribute)=="table") then
	gdSuitAttribute = {}
end

 gdEnhanceAttribute[1] = {
	id=1,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+15",data=15,type=6,},
			[2]= {name="最大魔法攻击+15",data=15,type=8,},
			[3]= {name="最大道术攻击+15",data=15,type=10,},
			[4]= {name="生命上限+1%",data=100,type=40,},
			[5]= {name="魔法上限+1%",data=100,type=41,},
			[6]= {
					name="魂石最大攻击+1%",
					data=100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+1%",data=100,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+1%",data=100,isstone=true,type=53,},
		},
	reqlvl=4,
}
gdEnhanceAttribute[2] = {
	id=2,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+25",data=25,type=6,},
			[2]= {name="最大魔法攻击+25",data=25,type=8,},
			[3]= {name="最大道术攻击+25",data=25,type=10,},
			[4]= {name="生命上限+3%",data=300,type=40,},
			[5]= {name="魔法上限+3%",data=300,type=41,},
			[6]= {
					name="魂石最大攻击+1%",
					data=100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+1%",data=100,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+1%",data=100,isstone=true,type=53,},
		},
	reqlvl=5,
}
gdEnhanceAttribute[3] = {
	id=3,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+40",data=40,type=6,},
			[2]= {name="最大魔法攻击+40",data=40,type=8,},
			[3]= {name="最大道术攻击+40",data=40,type=10,},
			[4]= {name="生命上限+5%",data=500,type=40,},
			[5]= {name="魔法上限+5%",data=500,type=41,},
			[6]= {
					name="魂石最大攻击+2%",
					data=200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+2%",data=200,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+2%",data=200,isstone=true,type=53,},
		},
	reqlvl=6,
}
gdEnhanceAttribute[4] = {
	id=4,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+55",data=55,type=6,},
			[2]= {name="最大魔法攻击+55",data=55,type=8,},
			[3]= {name="最大道术攻击+55",data=55,type=10,},
			[4]= {name="生命上限+5%",data=500,type=40,},
			[5]= {name="魔法上限+5%",data=500,type=41,},
			[6]= {
					name="魂石最大攻击+2%",
					data=200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+2%",data=200,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+2%",data=200,isstone=true,type=53,},
		},
	reqlvl=7,
}
gdEnhanceAttribute[5] = {
	id=5,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+70",data=70,type=6,},
			[2]= {name="最大魔法攻击+70",data=70,type=8,},
			[3]= {name="最大道术攻击+70",data=70,type=10,},
			[4]= {name="生命上限+8%",data=800,type=40,},
			[5]= {name="魔法上限+8%",data=800,type=41,},
			[6]= {
					name="魂石最大攻击+3%",
					data=300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+3%",data=300,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+3%",data=300,isstone=true,type=53,},
		},
	reqlvl=8,
}
gdEnhanceAttribute[6] = {
	id=6,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+85",data=85,type=6,},
			[2]= {name="最大魔法攻击+85",data=85,type=8,},
			[3]= {name="最大道术攻击+85",data=85,type=10,},
			[4]= {name="生命上限+8%",data=800,type=40,},
			[5]= {name="魔法上限+8%",data=800,type=41,},
			[6]= {
					name="魂石最大攻击+3%",
					data=300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+3%",data=300,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+3%",data=300,isstone=true,type=53,},
		},
	reqlvl=9,
}
gdEnhanceAttribute[7] = {
	id=7,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+100",data=100,type=6,},
			[2]= {name="最大魔法攻击+100",data=100,type=8,},
			[3]= {name="最大道术攻击+100",data=100,type=10,},
			[4]= {name="生命上限+10%",data=1000,type=40,},
			[5]= {name="魔法上限+10%",data=1000,type=41,},
			[6]= {
					name="魂石最大攻击+5%",
					data=500,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+5%",data=500,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+5%",data=500,isstone=true,type=53,},
		},
	reqlvl=10,
}
gdEnhanceAttribute[8] = {
	id=8,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+120",data=120,type=6,},
			[2]= {name="最大魔法攻击+120",data=120,type=8,},
			[3]= {name="最大道术攻击+120",data=120,type=10,},
			[4]= {name="生命上限+13%",data=1300,type=40,},
			[5]= {name="魔法上限+13%",data=1300,type=41,},
			[6]= {
					name="魂石最大攻击+8%",
					data=800,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+8%",data=800,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+8%",data=800,isstone=true,type=53,},
		},
	reqlvl=11,
}
gdEnhanceAttribute[9] = {
	id=9,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+140",data=140,type=6,},
			[2]= {name="最大魔法攻击+140",data=140,type=8,},
			[3]= {name="最大道术攻击+140",data=140,type=10,},
			[4]= {name="生命上限+18%",data=1800,type=40,},
			[5]= {name="魔法上限+18%",data=1800,type=41,},
			[6]= {
					name="魂石最大攻击+12%",
					data=1200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+12%",data=1200,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+12%",data=1200,isstone=true,type=53,},
		},
	reqlvl=12,
}
gdEnhanceAttribute[10] = {
	id=10,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+160",data=160,type=6,},
			[2]= {name="最大魔法攻击+160",data=160,type=8,},
			[3]= {name="最大道术攻击+160",data=160,type=10,},
			[4]= {name="生命上限+25%",data=2500,type=40,},
			[5]= {name="魔法上限+25%",data=2500,type=41,},
			[6]= {
					name="魂石最大攻击+17%",
					data=1700,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+17%",data=1700,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+17%",data=1700,isstone=true,type=53,},
		},
	reqlvl=13,
}
gdEnhanceAttribute[11] = {
	id=11,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+180",data=180,type=6,},
			[2]= {name="最大魔法攻击+180",data=180,type=8,},
			[3]= {name="最大道术攻击+180",data=180,type=10,},
			[4]= {name="生命上限+35%",data=3500,type=40,},
			[5]= {name="魔法上限+35%",data=3500,type=41,},
			[6]= {
					name="魂石最大攻击+23%",
					data=2300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+23%",data=2300,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+23%",data=2300,isstone=true,type=53,},
		},
	reqlvl=14,
}
gdEnhanceAttribute[12] = {
	id=12,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+200",data=200,type=6,},
			[2]= {name="最大魔法攻击+200",data=200,type=8,},
			[3]= {name="最大道术攻击+200",data=200,type=10,},
			[4]= {name="生命上限+50%",data=5000,type=40,},
			[5]= {name="魔法上限+50%",data=5000,type=41,},
			[6]= {
					name="魂石最大攻击+30%",
					data=3000,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+30%",data=3000,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+30%",data=3000,isstone=true,type=53,},
		},
	reqlvl=15,
}
gdEnhanceAttribute[13] = {
	id=13,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+220",data=220,type=6,},
			[2]= {name="最大魔法攻击+220",data=220,type=8,},
			[3]= {name="最大道术攻击+220",data=220,type=10,},
			[4]= {name="生命上限+65%",data=6500,type=40,},
			[5]= {name="魔法上限+65%",data=6500,type=41,},
			[6]= {
					name="魂石最大攻击+37%",
					data=3700,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+37%",data=3700,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+37%",data=3700,isstone=true,type=53,},
		},
	reqlvl=16,
}
gdEnhanceAttribute[14] = {
	id=14,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+240",data=240,type=6,},
			[2]= {name="最大魔法攻击+240",data=240,type=8,},
			[3]= {name="最大道术攻击+240",data=240,type=10,},
			[4]= {name="生命上限+80%",data=8000,type=40,},
			[5]= {name="魔法上限+80%",data=8000,type=41,},
			[6]= {
					name="魂石最大攻击+44%",
					data=4400,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+44%",data=4400,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+44%",data=4400,isstone=true,type=53,},
		},
	reqlvl=17,
}
gdEnhanceAttribute[15] = {
	id=15,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+260",data=260,type=6,},
			[2]= {name="最大魔法攻击+260",data=260,type=8,},
			[3]= {name="最大道术攻击+260",data=260,type=10,},
			[4]= {name="生命上限+95%",data=9500,type=40,},
			[5]= {name="魔法上限+95%",data=9500,type=41,},
			[6]= {
					name="魂石最大攻击+51%",
					data=5100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+51%",data=5100,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+51%",data=5100,isstone=true,type=53,},
		},
	reqlvl=18,
}
gdEnhanceAttribute[16] = {
	id=16,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+280",data=280,type=6,},
			[2]= {name="最大魔法攻击+280",data=280,type=8,},
			[3]= {name="最大道术攻击+280",data=280,type=10,},
			[4]= {name="生命上限+110%",data=11000,type=40,},
			[5]= {name="魔法上限+110%",data=11000,type=41,},
			[6]= {
					name="魂石最大攻击+58%",
					data=5800,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+58%",data=5800,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+58%",data=5800,isstone=true,type=53,},
		},
	reqlvl=19,
}
gdEnhanceAttribute[17] = {
	id=17,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+300",data=300,type=6,},
			[2]= {name="最大魔法攻击+300",data=300,type=8,},
			[3]= {name="最大道术攻击+300",data=300,type=10,},
			[4]= {name="生命上限+125%",data=12500,type=40,},
			[5]= {name="魔法上限+125%",data=12500,type=41,},
			[6]= {
					name="魂石最大攻击+65%",
					data=6500,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+65%",data=6500,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+65%",data=6500,isstone=true,type=53,},
		},
	reqlvl=20,
}
gdEnhanceAttribute[18] = {
	id=18,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+320",data=320,type=6,},
			[2]= {name="最大魔法攻击+320",data=320,type=8,},
			[3]= {name="最大道术攻击+320",data=320,type=10,},
			[4]= {name="生命上限+140%",data=14000,type=40,},
			[5]= {name="魔法上限+140%",data=14000,type=41,},
			[6]= {
					name="魂石最大攻击+72%",
					data=7200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+72%",data=7200,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+72%",data=7200,isstone=true,type=53,},
		},
	reqlvl=21,
}
gdEnhanceAttribute[19] = {
	id=19,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+340",data=340,type=6,},
			[2]= {name="最大魔法攻击+340",data=340,type=8,},
			[3]= {name="最大道术攻击+340",data=340,type=10,},
			[4]= {name="生命上限+155%",data=15500,type=40,},
			[5]= {name="魔法上限+155%",data=15500,type=41,},
			[6]= {
					name="魂石最大攻击+79%",
					data=7900,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+79%",data=7900,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+79%",data=7900,isstone=true,type=53,},
		},
	reqlvl=22,
}
gdEnhanceAttribute[20] = {
	id=20,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+360",data=360,type=6,},
			[2]= {name="最大魔法攻击+360",data=360,type=8,},
			[3]= {name="最大道术攻击+360",data=360,type=10,},
			[4]= {name="生命上限+170%",data=17000,type=40,},
			[5]= {name="魔法上限+170%",data=17000,type=41,},
			[6]= {
					name="魂石最大攻击+86%",
					data=8600,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+86%",data=8600,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+86%",data=8600,isstone=true,type=53,},
		},
	reqlvl=23,
}
gdEnhanceAttribute[21] = {
	id=21,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+380",data=380,type=6,},
			[2]= {name="最大魔法攻击+380",data=380,type=8,},
			[3]= {name="最大道术攻击+380",data=380,type=10,},
			[4]= {name="生命上限+185%",data=18500,type=40,},
			[5]= {name="魔法上限+185%",data=18500,type=41,},
			[6]= {
					name="魂石最大攻击+93%",
					data=9300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+93%",data=9300,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+93%",data=9300,isstone=true,type=53,},
		},
	reqlvl=24,
}
gdEnhanceAttribute[22] = {
	id=22,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+400",data=400,type=6,},
			[2]= {name="最大魔法攻击+400",data=400,type=8,},
			[3]= {name="最大道术攻击+400",data=400,type=10,},
			[4]= {name="生命上限+200%",data=20000,type=40,},
			[5]= {name="魔法上限+200%",data=20000,type=41,},
			[6]= {
					name="魂石最大攻击+100%",
					data=10000,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+100%",data=10000,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+100%",data=10000,isstone=true,type=53,},
		},
	reqlvl=25,
}
gdEnhanceAttribute[23] = {
	id=23,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+420",data=420,type=6,},
			[2]= {name="最大魔法攻击+420",data=420,type=8,},
			[3]= {name="最大道术攻击+420",data=420,type=10,},
			[4]= {name="生命上限+215%",data=21500,type=40,},
			[5]= {name="魔法上限+215%",data=21500,type=41,},
			[6]= {
					name="魂石最大攻击+107%",
					data=10700,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+107%",data=10700,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+107%",data=10700,isstone=true,type=53,},
		},
	reqlvl=26,
}
gdEnhanceAttribute[24] = {
	id=24,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+440",data=440,type=6,},
			[2]= {name="最大魔法攻击+440",data=440,type=8,},
			[3]= {name="最大道术攻击+440",data=440,type=10,},
			[4]= {name="生命上限+230%",data=23000,type=40,},
			[5]= {name="魔法上限+230%",data=23000,type=41,},
			[6]= {
					name="魂石最大攻击+114%",
					data=11400,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+114%",data=11400,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+114%",data=11400,isstone=true,type=53,},
		},
	reqlvl=27,
}
gdEnhanceAttribute[25] = {
	id=25,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+460",data=460,type=6,},
			[2]= {name="最大魔法攻击+460",data=460,type=8,},
			[3]= {name="最大道术攻击+460",data=460,type=10,},
			[4]= {name="生命上限+245%",data=24500,type=40,},
			[5]= {name="魔法上限+245%",data=24500,type=41,},
			[6]= {
					name="魂石最大攻击+121%",
					data=12100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+121%",data=12100,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+121%",data=12100,isstone=true,type=53,},
		},
	reqlvl=28,
}
gdEnhanceAttribute[26] = {
	id=26,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+480",data=480,type=6,},
			[2]= {name="最大魔法攻击+480",data=480,type=8,},
			[3]= {name="最大道术攻击+480",data=480,type=10,},
			[4]= {name="生命上限+260%",data=26000,type=40,},
			[5]= {name="魔法上限+260%",data=26000,type=41,},
			[6]= {
					name="魂石最大攻击+128%",
					data=12800,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+128%",data=12800,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+128%",data=12800,isstone=true,type=53,},
		},
	reqlvl=29,
}
gdEnhanceAttribute[27] = {
	id=27,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+500",data=500,type=6,},
			[2]= {name="最大魔法攻击+500",data=500,type=8,},
			[3]= {name="最大道术攻击+500",data=500,type=10,},
			[4]= {name="生命上限+275%",data=27500,type=40,},
			[5]= {name="魔法上限+275%",data=27500,type=41,},
			[6]= {
					name="魂石最大攻击+135%",
					data=13500,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+135%",data=13500,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+135%",data=13500,isstone=true,type=53,},
		},
	reqlvl=30,
}
gdEnhanceAttribute[28] = {
	id=28,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+520",data=520,type=6,},
			[2]= {name="最大魔法攻击+520",data=520,type=8,},
			[3]= {name="最大道术攻击+520",data=520,type=10,},
			[4]= {name="生命上限+290%",data=29000,type=40,},
			[5]= {name="魔法上限+290%",data=29000,type=41,},
			[6]= {
					name="魂石最大攻击+142%",
					data=14200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+142%",data=14200,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+142%",data=14200,isstone=true,type=53,},
		},
	reqlvl=31,
}
gdEnhanceAttribute[29] = {
	id=29,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+540",data=540,type=6,},
			[2]= {name="最大魔法攻击+540",data=540,type=8,},
			[3]= {name="最大道术攻击+540",data=540,type=10,},
			[4]= {name="生命上限+305%",data=30500,type=40,},
			[5]= {name="魔法上限+305%",data=30500,type=41,},
			[6]= {
					name="魂石最大攻击+149%",
					data=14900,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+149%",data=14900,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+149%",data=14900,isstone=true,type=53,},
		},
	reqlvl=32,
}
gdEnhanceAttribute[30] = {
	id=30,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+560",data=560,type=6,},
			[2]= {name="最大魔法攻击+560",data=560,type=8,},
			[3]= {name="最大道术攻击+560",data=560,type=10,},
			[4]= {name="生命上限+320%",data=32000,type=40,},
			[5]= {name="魔法上限+320%",data=32000,type=41,},
			[6]= {
					name="魂石最大攻击+156%",
					data=15600,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+156%",data=15600,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+156%",data=15600,isstone=true,type=53,},
		},
	reqlvl=33,
}
gdEnhanceAttribute[31] = {
	id=31,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+580",data=580,type=6,},
			[2]= {name="最大魔法攻击+580",data=580,type=8,},
			[3]= {name="最大道术攻击+580",data=580,type=10,},
			[4]= {name="生命上限+335%",data=33500,type=40,},
			[5]= {name="魔法上限+335%",data=33500,type=41,},
			[6]= {
					name="魂石最大攻击+163%",
					data=16300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+163%",data=16300,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+163%",data=16300,isstone=true,type=53,},
		},
	reqlvl=34,
}
gdEnhanceAttribute[32] = {
	id=32,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+600",data=600,type=6,},
			[2]= {name="最大魔法攻击+600",data=600,type=8,},
			[3]= {name="最大道术攻击+600",data=600,type=10,},
			[4]= {name="生命上限+350%",data=35000,type=40,},
			[5]= {name="魔法上限+350%",data=35000,type=41,},
			[6]= {
					name="魂石最大攻击+170%",
					data=17000,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+170%",data=17000,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+170%",data=17000,isstone=true,type=53,},
		},
	reqlvl=35,
}
gdEnhanceAttribute[33] = {
	id=33,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+620",data=620,type=6,},
			[2]= {name="最大魔法攻击+620",data=620,type=8,},
			[3]= {name="最大道术攻击+620",data=620,type=10,},
			[4]= {name="生命上限+365%",data=36500,type=40,},
			[5]= {name="魔法上限+365%",data=36500,type=41,},
			[6]= {
					name="魂石最大攻击+177%",
					data=17700,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+177%",data=17700,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+177%",data=17700,isstone=true,type=53,},
		},
	reqlvl=36,
}
gdEnhanceAttribute[34] = {
	id=34,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+640",data=640,type=6,},
			[2]= {name="最大魔法攻击+640",data=640,type=8,},
			[3]= {name="最大道术攻击+640",data=640,type=10,},
			[4]= {name="生命上限+380%",data=38000,type=40,},
			[5]= {name="魔法上限+380%",data=38000,type=41,},
			[6]= {
					name="魂石最大攻击+184%",
					data=18400,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+184%",data=18400,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+184%",data=18400,isstone=true,type=53,},
		},
	reqlvl=37,
}
gdEnhanceAttribute[35] = {
	id=35,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+660",data=660,type=6,},
			[2]= {name="最大魔法攻击+660",data=660,type=8,},
			[3]= {name="最大道术攻击+660",data=660,type=10,},
			[4]= {name="生命上限+395%",data=39500,type=40,},
			[5]= {name="魔法上限+395%",data=39500,type=41,},
			[6]= {
					name="魂石最大攻击+191%",
					data=19100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+191%",data=19100,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+191%",data=19100,isstone=true,type=53,},
		},
	reqlvl=38,
}
gdEnhanceAttribute[36] = {
	id=36,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+680",data=680,type=6,},
			[2]= {name="最大魔法攻击+680",data=680,type=8,},
			[3]= {name="最大道术攻击+680",data=680,type=10,},
			[4]= {name="生命上限+410%",data=41000,type=40,},
			[5]= {name="魔法上限+410%",data=41000,type=41,},
			[6]= {
					name="魂石最大攻击+198%",
					data=19800,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+198%",data=19800,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+198%",data=19800,isstone=true,type=53,},
		},
	reqlvl=39,
}
gdEnhanceAttribute[37] = {
	id=37,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+700",data=700,type=6,},
			[2]= {name="最大魔法攻击+700",data=700,type=8,},
			[3]= {name="最大道术攻击+700",data=700,type=10,},
			[4]= {name="生命上限+425%",data=42500,type=40,},
			[5]= {name="魔法上限+425%",data=42500,type=41,},
			[6]= {
					name="魂石最大攻击+205%",
					data=20500,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+205%",data=20500,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+205%",data=20500,isstone=true,type=53,},
		},
	reqlvl=40,
}
gdEnhanceAttribute[38] = {
	id=38,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+720",data=720,type=6,},
			[2]= {name="最大魔法攻击+720",data=720,type=8,},
			[3]= {name="最大道术攻击+720",data=720,type=10,},
			[4]= {name="生命上限+440%",data=44000,type=40,},
			[5]= {name="魔法上限+440%",data=44000,type=41,},
			[6]= {
					name="魂石最大攻击+212%",
					data=21200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+212%",data=21200,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+212%",data=21200,isstone=true,type=53,},
		},
	reqlvl=41,
}
gdEnhanceAttribute[39] = {
	id=39,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+740",data=740,type=6,},
			[2]= {name="最大魔法攻击+740",data=740,type=8,},
			[3]= {name="最大道术攻击+740",data=740,type=10,},
			[4]= {name="生命上限+455%",data=45500,type=40,},
			[5]= {name="魔法上限+455%",data=45500,type=41,},
			[6]= {
					name="魂石最大攻击+219%",
					data=21900,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+219%",data=21900,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+219%",data=21900,isstone=true,type=53,},
		},
	reqlvl=42,
}
gdEnhanceAttribute[40] = {
	id=40,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+760",data=760,type=6,},
			[2]= {name="最大魔法攻击+760",data=760,type=8,},
			[3]= {name="最大道术攻击+760",data=760,type=10,},
			[4]= {name="生命上限+470%",data=47000,type=40,},
			[5]= {name="魔法上限+470%",data=47000,type=41,},
			[6]= {
					name="魂石最大攻击+226%",
					data=22600,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+226%",data=22600,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+226%",data=22600,isstone=true,type=53,},
		},
	reqlvl=43,
}
gdEnhanceAttribute[41] = {
	id=41,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+780",data=780,type=6,},
			[2]= {name="最大魔法攻击+780",data=780,type=8,},
			[3]= {name="最大道术攻击+780",data=780,type=10,},
			[4]= {name="生命上限+485%",data=48500,type=40,},
			[5]= {name="魔法上限+485%",data=48500,type=41,},
			[6]= {
					name="魂石最大攻击+233%",
					data=23300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+233%",data=23300,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+233%",data=23300,isstone=true,type=53,},
		},
	reqlvl=44,
}
gdEnhanceAttribute[42] = {
	id=42,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+800",data=800,type=6,},
			[2]= {name="最大魔法攻击+800",data=800,type=8,},
			[3]= {name="最大道术攻击+800",data=800,type=10,},
			[4]= {name="生命上限+500%",data=50000,type=40,},
			[5]= {name="魔法上限+500%",data=50000,type=41,},
			[6]= {
					name="魂石最大攻击+240%",
					data=24000,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+240%",data=24000,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+240%",data=24000,isstone=true,type=53,},
		},
	reqlvl=45,
}
gdEnhanceAttribute[43] = {
	id=43,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+820",data=820,type=6,},
			[2]= {name="最大魔法攻击+820",data=820,type=8,},
			[3]= {name="最大道术攻击+820",data=820,type=10,},
			[4]= {name="生命上限+515%",data=51500,type=40,},
			[5]= {name="魔法上限+515%",data=51500,type=41,},
			[6]= {
					name="魂石最大攻击+247%",
					data=24700,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+247%",data=24700,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+247%",data=24700,isstone=true,type=53,},
		},
	reqlvl=46,
}
gdEnhanceAttribute[44] = {
	id=44,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+840",data=840,type=6,},
			[2]= {name="最大魔法攻击+840",data=840,type=8,},
			[3]= {name="最大道术攻击+840",data=840,type=10,},
			[4]= {name="生命上限+530%",data=53000,type=40,},
			[5]= {name="魔法上限+530%",data=53000,type=41,},
			[6]= {
					name="魂石最大攻击+254%",
					data=25400,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+254%",data=25400,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+254%",data=25400,isstone=true,type=53,},
		},
	reqlvl=47,
}
gdEnhanceAttribute[45] = {
	id=45,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+860",data=860,type=6,},
			[2]= {name="最大魔法攻击+860",data=860,type=8,},
			[3]= {name="最大道术攻击+860",data=860,type=10,},
			[4]= {name="生命上限+545%",data=54500,type=40,},
			[5]= {name="魔法上限+545%",data=54500,type=41,},
			[6]= {
					name="魂石最大攻击+261%",
					data=26100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+261%",data=26100,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+261%",data=26100,isstone=true,type=53,},
		},
	reqlvl=48,
}
gdEnhanceAttribute[46] = {
	id=46,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+880",data=880,type=6,},
			[2]= {name="最大魔法攻击+880",data=880,type=8,},
			[3]= {name="最大道术攻击+880",data=880,type=10,},
			[4]= {name="生命上限+560%",data=56000,type=40,},
			[5]= {name="魔法上限+560%",data=56000,type=41,},
			[6]= {
					name="魂石最大攻击+268%",
					data=26800,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+268%",data=26800,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+268%",data=26800,isstone=true,type=53,},
		},
	reqlvl=49,
}
gdEnhanceAttribute[47] = {
	id=47,
	name="全身加成",
	attr= {
			[1]= {name="最大物理攻击+900",data=900,type=6,},
			[2]= {name="最大魔法攻击+900",data=900,type=8,},
			[3]= {name="最大道术攻击+900",data=900,type=10,},
			[4]= {name="生命上限+575%",data=57500,type=40,},
			[5]= {name="魔法上限+575%",data=57500,type=41,},
			[6]= {
					name="魂石最大攻击+275%",
					data=27500,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[7]= {name="魂石最大物理防御+275%",data=27500,isstone=true,type=51,},
			[8]= {name="魂石最大魔法防御+275%",data=27500,isstone=true,type=53,},
		},
	reqlvl=50,
}


-------------------------------------------------------------------------------------------------------------
gdStoneAttribute[1] = {
	id=1,
	name="12个2级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+5",data=5,type=6,},
			[2]= {name="最大魔法攻击+5",data=5,type=8,},
			[3]= {name="最大道术攻击+5",data=5,type=10,},
			[4]= {name="生命上限+0.5%",data=50,type=40,},
			[5]= {name="魔法上限+0.5%",data=50,type=41,},
		},
	reqcnt=12,
	reqlvl=2,
}
gdStoneAttribute[2] = {
	id=2,
	name="12个3级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+10",data=10,type=6,},
			[2]= {name="最大魔法攻击+10",data=10,type=8,},
			[3]= {name="最大道术攻击+10",data=10,type=10,},
			[4]= {name="生命上限+1%",data=100,type=40,},
			[5]= {name="魔法上限+1%",data=100,type=41,},
		},
	reqcnt=12,
	reqlvl=3,
}
gdStoneAttribute[3] = {
	id=3,
	name="12个4级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+15",data=15,type=6,},
			[2]= {name="最大魔法攻击+15",data=15,type=8,},
			[3]= {name="最大道术攻击+15",data=15,type=10,},
			[4]= {name="生命上限+1.5%",data=150,type=40,},
			[5]= {name="魔法上限+1.5%",data=150,type=41,},
		},
	reqcnt=12,
	reqlvl=4,
}
gdStoneAttribute[4] = {
	id=4,
	name="12个5级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+20",data=20,type=6,},
			[2]= {name="最大魔法攻击+20",data=20,type=8,},
			[3]= {name="最大道术攻击+20",data=20,type=10,},
			[4]= {name="生命上限+2%",data=200,type=40,},
			[5]= {name="魔法上限+2%",data=200,type=41,},
		},
	reqcnt=12,
	reqlvl=5,
}
gdStoneAttribute[5] = {
	id=5,
	name="12个6级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+35",data=35,type=6,},
			[2]= {name="最大魔法攻击+35",data=35,type=8,},
			[3]= {name="最大道术攻击+35",data=35,type=10,},
			[4]= {name="生命上限+3.5%",data=350,type=40,},
			[5]= {name="魔法上限+3.5%",data=350,type=41,},
		},
	reqcnt=12,
	reqlvl=6,
}
gdStoneAttribute[6] = {
	id=6,
	name="12个7级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+45",data=45,type=6,},
			[2]= {name="最大魔法攻击+45",data=45,type=8,},
			[3]= {name="最大道术攻击+45",data=45,type=10,},
			[4]= {name="生命上限+4.5%",data=450,type=40,},
			[5]= {name="魔法上限+4.5%",data=450,type=41,},
		},
	reqcnt=12,
	reqlvl=7,
}
gdStoneAttribute[7] = {
	id=7,
	name="12个8级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+60",data=60,type=6,},
			[2]= {name="最大魔法攻击+60",data=60,type=8,},
			[3]= {name="最大道术攻击+60",data=60,type=10,},
			[4]= {name="生命上限+6%",data=600,type=40,},
			[5]= {name="魔法上限+6%",data=600,type=41,},
		},
	reqcnt=12,
	reqlvl=8,
}
gdStoneAttribute[8] = {
	id=8,
	name="12个9级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+120",data=120,type=6,},
			[2]= {name="最大魔法攻击+120",data=120,type=8,},
			[3]= {name="最大道术攻击+120",data=120,type=10,},
			[4]= {name="生命上限+8%",data=800,type=40,},
			[5]= {name="魔法上限+8%",data=800,type=41,},
		},
	reqcnt=12,
	reqlvl=9,
}
gdStoneAttribute[9] = {
	id=9,
	name="12个10级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+200",data=200,type=6,},
			[2]= {name="最大魔法攻击+200",data=200,type=8,},
			[3]= {name="最大道术攻击+200",data=200,type=10,},
			[4]= {name="生命上限+10%",data=1000,type=40,},
			[5]= {name="魔法上限+10%",data=1000,type=41,},
		},
	reqcnt=12,
	reqlvl=10,
}
gdStoneAttribute[10] = {
	id=10,
	name="12个11级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+300",data=300,type=6,},
			[2]= {name="最大魔法攻击+300",data=300,type=8,},
			[3]= {name="最大道术攻击+300",data=300,type=10,},
			[4]= {name="生命上限+12%",data=1200,type=40,},
			[5]= {name="魔法上限+12%",data=1200,type=41,},
		},
	reqcnt=12,
	reqlvl=11,
}
gdStoneAttribute[11] = {
	id=11,
	name="12个12级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+400",data=400,type=6,},
			[2]= {name="最大魔法攻击+400",data=400,type=8,},
			[3]= {name="最大道术攻击+400",data=400,type=10,},
			[4]= {name="生命上限+14%",data=1400,type=40,},
			[5]= {name="魔法上限+14%",data=1400,type=41,},
		},
	reqcnt=12,
	reqlvl=12,
}
gdStoneAttribute[12] = {
	id=12,
	name="12个13级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+500",data=500,type=6,},
			[2]= {name="最大魔法攻击+500",data=500,type=8,},
			[3]= {name="最大道术攻击+500",data=500,type=10,},
			[4]= {name="生命上限+16%",data=1600,type=40,},
			[5]= {name="魔法上限+16%",data=1600,type=41,},
		},
	reqcnt=12,
	reqlvl=13,
}
gdStoneAttribute[13] = {
	id=13,
	name="12个14级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+600",data=600,type=6,},
			[2]= {name="最大魔法攻击+600",data=600,type=8,},
			[3]= {name="最大道术攻击+600",data=600,type=10,},
			[4]= {name="生命上限+18%",data=1800,type=40,},
			[5]= {name="魔法上限+18%",data=1800,type=41,},
		},
	reqcnt=12,
	reqlvl=14,
}
gdStoneAttribute[14] = {
	id=14,
	name="12个15级以上魂石",
	attr= {
			[1]= {name="最大物理攻击+700",data=700,type=6,},
			[2]= {name="最大魔法攻击+700",data=700,type=8,},
			[3]= {name="最大道术攻击+700",data=700,type=10,},
			[4]= {name="生命上限+20%",data=2000,type=40,},
			[5]= {name="魔法上限+20%",data=2000,type=41,},
		},
	reqcnt=12,
	reqlvl=15,
}
--------------------------------------------------16级魂石-----------------------------
gdStoneAttribute[15] = {
	id=15,
	name="12个16级以上魂石",
	attr= {
			[1] = {name="最大物理攻击+900", data=900, type=6, },
			[2] = {name="最大魔法攻击+900", data=900, type=8, },
			[3] = {name="最大道术攻击+900", data=900, type=10, },
			[4] = {name="生命上限+24%", data=2400, type=40, },
			[5] = {name="魔法上限+24%", data=2400, type=41, },
		},
	reqcnt=12,
	reqlvl=16,
}
gdStoneAttribute[16] = {
	id=16,
	name="12个17级以上魂石",
	attr= {
			[1] = {name="最大物理攻击+1100", data=1100, type=6, },
			[2] = {name="最大魔法攻击+1100", data=1100, type=8, },
			[3] = {name="最大道术攻击+1100", data=1100, type=10, },
			[4] = {name="生命上限+26%", data=2600, type=40, },
			[5] = {name="魔法上限+26%", data=2600, type=41, },
		},
	reqcnt=12,
	reqlvl=17,
}
gdStoneAttribute[17] = {
	id=17,
	name="12个18级以上魂石",
	attr= {
			[1] = {name="最大物理攻击+1300", data=1300, type=6, },
			[2] = {name="最大魔法攻击+1300", data=1300, type=8, },
			[3] = {name="最大道术攻击+1300", data=1300, type=10, },
			[4] = {name="生命上限+28%", data=2800, type=40, },
			[5] = {name="魔法上限+28%", data=2800, type=41, },
		},
	reqcnt=12,
	reqlvl=18,
}
gdStoneAttribute[18] = {
	id=18,
	name="12个19级以上魂石",
	attr= {
			[1] = {name="最大物理攻击+1500", data=1500, type=6, },
			[2] = {name="最大魔法攻击+1500", data=1500, type=8, },
			[3] = {name="最大道术攻击+1500", data=1500, type=10, },
			[4] = {name="生命上限+30%", data=3000, type=40, },
			[5] = {name="魔法上限+30%", data=3000, type=41, },
		},
	reqcnt=12,
	reqlvl=19,
}
gdStoneAttribute[19] = {
	id=19,
	name="12个20级以上魂石",
	attr= {
			[1] = {name="最大物理攻击+1800", data=1800, type=6, },
			[2] = {name="最大魔法攻击+1800", data=1800, type=8, },
			[3] = {name="最大道术攻击+1800", data=1800, type=10, },
			[4] = {name="生命上限+32%", data=3200, type=40, },
			[5] = {name="魔法上限+32%", data=3200, type=41, },
		},
	reqcnt=12,
	reqlvl=20,
}

gdEvolutionAttribute[1] = {
	id=1,
	name="1转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+1%",
					data=100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+1%",data=100,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+1%",data=100,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+1400",data=1400,type=1,},
			[2]= {name="魔法上限+800",data=800,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+1000",data=1000,type=1,},
			[2]= {name="魔法上限+1400",data=1400,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+1700",data=1700,type=1,},
			[2]= {name="魔法上限+100",data=100,type=2,},
		},
}
gdEvolutionAttribute[2] = {
	id=2,
	name="2转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+1.5%",
					data=150,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+1.5%",data=150,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+1.5%",data=150,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+2300",data=2300,type=1,},
			[2]= {name="魔法上限+1600",data=1600,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+1500",data=1500,type=1,},
			[2]= {name="魔法上限+2800",data=2800,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+2900",data=2900,type=1,},
			[2]= {name="魔法上限+200",data=200,type=2,},
		},
}
gdEvolutionAttribute[3] = {
	id=3,
	name="3转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+2%",
					data=200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+2%",data=200,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+2%",data=200,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+3200",data=3200,type=1,},
			[2]= {name="魔法上限+2400",data=2400,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+2000",data=2000,type=1,},
			[2]= {name="魔法上限+4200",data=4200,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+4100",data=4100,type=1,},
			[2]= {name="魔法上限+300",data=300,type=2,},
		},
}
gdEvolutionAttribute[4] = {
	id=4,
	name="4转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+2.5%",
					data=250,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+2.5%",data=250,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+2.5%",data=250,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+4100",data=4100,type=1,},
			[2]= {name="魔法上限+3200",data=3200,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+2500",data=2500,type=1,},
			[2]= {name="魔法上限+5600",data=5600,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+5300",data=5300,type=1,},
			[2]= {name="魔法上限+400",data=400,type=2,},
		},
}
gdEvolutionAttribute[5] = {
	id=5,
	name="5转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+3%",
					data=300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+3%",data=300,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+3%",data=300,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+5000",data=5000,type=1,},
			[2]= {name="魔法上限+4000",data=4000,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+3000",data=3000,type=1,},
			[2]= {name="魔法上限+7000",data=7000,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+6500",data=6500,type=1,},
			[2]= {name="魔法上限+500",data=500,type=2,},
		},
}
gdEvolutionAttribute[6] = {
	id=6,
	name="6转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+3.5%",
					data=350,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+3.5%",data=350,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+3.5%",data=350,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+5900",data=5900,type=1,},
			[2]= {name="魔法上限+4800",data=4800,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+3500",data=3500,type=1,},
			[2]= {name="魔法上限+8400",data=8400,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+7700",data=7700,type=1,},
			[2]= {name="魔法上限+600",data=600,type=2,},
		},
}
gdEvolutionAttribute[7] = {
	id=7,
	name="7转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+4%",
					data=400,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+4%",data=400,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+4%",data=400,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+6800",data=6800,type=1,},
			[2]= {name="魔法上限+5600",data=5600,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+4000",data=4000,type=1,},
			[2]= {name="魔法上限+9800",data=9800,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+8900",data=8900,type=1,},
			[2]= {name="魔法上限+700",data=700,type=2,},
		},
}
gdEvolutionAttribute[8] = {
	id=8,
	name="8转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+4.5%",
					data=450,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+4.5%",data=450,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+4.5%",data=450,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+7700",data=7700,type=1,},
			[2]= {name="魔法上限+6400",data=6400,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+4500",data=4500,type=1,},
			[2]= {name="魔法上限+11200",data=11200,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+10100",data=10100,type=1,},
			[2]= {name="魔法上限+800",data=800,type=2,},
		},
}
gdEvolutionAttribute[9] = {
	id=9,
	name="9转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+5%",
					data=500,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+5%",data=500,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+5%",data=500,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+8600",data=8600,type=1,},
			[2]= {name="魔法上限+7200",data=7200,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+5000",data=5000,type=1,},
			[2]= {name="魔法上限+12600",data=12600,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+11300",data=11300,type=1,},
			[2]= {name="魔法上限+900",data=900,type=2,},
		},
}
gdEvolutionAttribute[10] = {
	id=10,
	name="10转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+5.5%",
					data=550,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+5.5%",data=550,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+5.5%",data=550,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+9500",data=9500,type=1,},
			[2]= {name="魔法上限+8000",data=8000,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+5500",data=5500,type=1,},
			[2]= {name="魔法上限+14000",data=14000,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+12500",data=12500,type=1,},
			[2]= {name="魔法上限+1000",data=1000,type=2,},
		},
}
gdEvolutionAttribute[11] = {
	id=11,
	name="11转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+6%",
					data=600,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+6%",data=600,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+6%",data=600,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+10400",data=10400,type=1,},
			[2]= {name="魔法上限+8800",data=8800,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+6000",data=6000,type=1,},
			[2]= {name="魔法上限+15400",data=15400,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+13700",data=13700,type=1,},
			[2]= {name="魔法上限+1100",data=1100,type=2,},
		},
}
gdEvolutionAttribute[12] = {
	id=12,
	name="12转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+6.5%",
					data=650,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+6.5%",data=650,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+6.5%",data=650,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+11300",data=11300,type=1,},
			[2]= {name="魔法上限+9600",data=9600,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+6500",data=6500,type=1,},
			[2]= {name="魔法上限+16800",data=16800,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+14900",data=14900,type=1,},
			[2]= {name="魔法上限+1200",data=1200,type=2,},
		},
}
gdEvolutionAttribute[13] = {
	id=13,
	name="13转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+7%",
					data=700,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+7%",data=700,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+7%",data=700,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+12200",data=12200,type=1,},
			[2]= {name="魔法上限+10400",data=10400,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+7000",data=7000,type=1,},
			[2]= {name="魔法上限+18200",data=18200,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+16100",data=16100,type=1,},
			[2]= {name="魔法上限+1300",data=1300,type=2,},
		},
}
gdEvolutionAttribute[14] = {
	id=14,
	name="14转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+7.5%",
					data=750,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+7.5%",data=750,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+7.5%",data=750,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+13100",data=13100,type=1,},
			[2]= {name="魔法上限+11200",data=11200,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+7500",data=7500,type=1,},
			[2]= {name="魔法上限+19600",data=19600,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+17300",data=17300,type=1,},
			[2]= {name="魔法上限+1400",data=1400,type=2,},
		},
}
gdEvolutionAttribute[15] = {
	id=15,
	name="15转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+8%",
					data=800,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+8%",data=800,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+8%",data=800,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+14000",data=14000,type=1,},
			[2]= {name="魔法上限+12000",data=12000,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+8000",data=8000,type=1,},
			[2]= {name="魔法上限+21000",data=21000,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+18500",data=18500,type=1,},
			[2]= {name="魔法上限+1500",data=1500,type=2,},
		},
}
gdEvolutionAttribute[16] = {
	id=16,
	name="16转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+8.5%",
					data=850,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+8.5%",data=850,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+8.5%",data=850,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+14900",data=14900,type=1,},
			[2]= {name="魔法上限+12800",data=12800,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+8500",data=8500,type=1,},
			[2]= {name="魔法上限+22400",data=22400,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+19700",data=19700,type=1,},
			[2]= {name="魔法上限+1600",data=1600,type=2,},
		},
}
gdEvolutionAttribute[17] = {
	id=17,
	name="17转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+9%",
					data=900,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+9%",data=900,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+9%",data=900,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+15800",data=15800,type=1,},
			[2]= {name="魔法上限+13600",data=13600,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+9000",data=9000,type=1,},
			[2]= {name="魔法上限+23800",data=23800,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+20900",data=20900,type=1,},
			[2]= {name="魔法上限+1700",data=1700,type=2,},
		},
}
gdEvolutionAttribute[18] = {
	id=18,
	name="18转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+9.5%",
					data=950,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+9.5%",data=950,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+9.5%",data=950,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+16700",data=16700,type=1,},
			[2]= {name="魔法上限+14400",data=14400,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+9500",data=9500,type=1,},
			[2]= {name="魔法上限+25200",data=25200,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+22100",data=22100,type=1,},
			[2]= {name="魔法上限+1800",data=1800,type=2,},
		},
}
gdEvolutionAttribute[19] = {
	id=19,
	name="19转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+10%",
					data=1000,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+10%",data=1000,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+10%",data=1000,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+17600",data=17600,type=1,},
			[2]= {name="魔法上限+15200",data=15200,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+10000",data=10000,type=1,},
			[2]= {name="魔法上限+26600",data=26600,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+23300",data=23300,type=1,},
			[2]= {name="魔法上限+1900",data=1900,type=2,},
		},
}
gdEvolutionAttribute[20] = {
	id=20,
	name="20转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+10.5%",
					data=1050,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+10.5%",data=1050,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+10.5%",data=1050,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+18500",data=18500,type=1,},
			[2]= {name="魔法上限+16000",data=16000,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+10500",data=10500,type=1,},
			[2]= {name="魔法上限+28000",data=28000,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+24500",data=24500,type=1,},
			[2]= {name="魔法上限+2000",data=2000,type=2,},
		},
}
gdEvolutionAttribute[21] = {
	id=21,
	name="21转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+11%",
					data=1100,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+11%",data=1100,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+11%",data=1100,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+19400",data=19400,type=1,},
			[2]= {name="魔法上限+16800",data=16800,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+11000",data=11000,type=1,},
			[2]= {name="魔法上限+29400",data=29400,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+26200",data=26200,type=1,},
			[2]= {name="魔法上限+2100",data=2100,type=2,},
		},
}
gdEvolutionAttribute[22] = {
	id=22,
	name="22转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+12%",
					data=1200,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+12%",data=1200,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+12%",data=1200,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+20300",data=20300,type=1,},
			[2]= {name="魔法上限+17600",data=17600,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+11500",data=11500,type=1,},
			[2]= {name="魔法上限+30800",data=30800,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+27900",data=27900,type=1,},
			[2]= {name="魔法上限+2200",data=2200,type=2,},
		},
}
gdEvolutionAttribute[23] = {
	id=23,
	name="23转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+13%",
					data=1300,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+13%",data=1300,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+13%",data=1300,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+21200",data=21200,type=1,},
			[2]= {name="魔法上限+18400",data=18400,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+12000",data=12000,type=1,},
			[2]= {name="魔法上限+32200",data=32200,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+29600",data=29600,type=1,},
			[2]= {name="魔法上限+2300",data=2300,type=2,},
		},
}
gdEvolutionAttribute[24] = {
	id=24,
	name="24转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+14%",
					data=1400,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+14%",data=1400,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+14%",data=1400,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+22100",data=22100,type=1,},
			[2]= {name="魔法上限+19200",data=19200,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+12500",data=12500,type=1,},
			[2]= {name="魔法上限+33600",data=33600,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+31300",data=31300,type=1,},
			[2]= {name="魔法上限+2400",data=2400,type=2,},
		},
}
gdEvolutionAttribute[25] = {
	id=25,
	name="25转效果",
	attr= {
			[1]= {
					name="魂石最大攻击+15%",
					data=1500,
					isstone=true,
					typetable= {[1]=45,[2]=49,[3]=47,},
				},
			[2]= {name="魂石最大物理防御+15%",data=1500,isstone=true,type=51,},
			[3]= {name="魂石最大魔法防御+15%",data=1500,isstone=true,type=53,},
		},
	dsattr= {
			[1]= {name="生命上限+23000",data=23000,type=1,},
			[2]= {name="魔法上限+20000",data=20000,type=2,},
		},
	fsattr= {
			[1]= {name="生命上限+13000",data=13000,type=1,},
			[2]= {name="魔法上限+35000",data=35000,type=2,},
		},
	zsattr= {
			[1]= {name="生命上限+33300",data=33300,type=1,},
			[2]= {name="魔法上限+2500",data=2500,type=2,},
		},
}
-- 26-30转
gdEvolutionAttribute[26] = {
    id = 26,
    name = "凝气1",
    attr = {
        { name = "魂石最大攻击+16%", data = 1600, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+16%", data = 1600, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+16%", data = 1600, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+23900", data = 23900, type = 1 },
        { name = "魔法上限+20800", data = 20800, type = 2 },
		{ name = "暴击率+0.1", data = 10, type = 32 },
    },
    fsattr = {
        { name = "生命上限+13500", data = 13500, type = 1 },
        { name = "魔法上限+36400", data = 36400, type = 2 },
		{ name = "暴击率+0.1", data = 10, type = 32 },
    },
    zsattr = {
        { name = "生命上限+35300", data = 35300, type = 1 },
        { name = "魔法上限+2600", data = 2600, type = 2 },
		{ name = "暴击率+0.1", data = 10, type = 32 },
    },
}

gdEvolutionAttribute[27] = {
    id = 27,
    name = "凝气2",
    attr = {
        { name = "魂石最大攻击+17%", data = 1700, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+17%", data = 1700, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+17%", data = 1700, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+24800", data = 24800, type = 1 },
        { name = "魔法上限+21600", data = 21600, type = 2 },
		{ name = "暴击率+0.2", data = 20, type = 32 },
    },
    fsattr = {
        { name = "生命上限+14000", data = 14000, type = 1 },
        { name = "魔法上限+37800", data = 37800, type = 2 },
		{ name = "暴击率+0.2", data = 20, type = 32 },
    },
    zsattr = {
        { name = "生命上限+37300", data = 37300, type = 1 },
        { name = "魔法上限+2700", data = 2700, type = 2 },
		{ name = "暴击率+0.2", data = 20, type = 32 },
    },
}

gdEvolutionAttribute[28] = {
    id = 28,
    name = "凝气3",
    attr = {
        { name = "魂石最大攻击+18%", data = 1800, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+18%", data = 1800, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+18%", data = 1800, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+25700", data = 25700, type = 1 },
        { name = "魔法上限+22400", data = 22400, type = 2 },
		{ name = "暴击率+0.3", data = 30, type = 32 },
    },
    fsattr = {
        { name = "生命上限+14500", data = 14500, type = 1 },
        { name = "魔法上限+39200", data = 39200, type = 2 },
		{ name = "暴击率+0.3", data = 30, type = 32 },
    },
    zsattr = {
        { name = "生命上限+39300", data = 39300, type = 1 },
        { name = "魔法上限+2800", data = 2800, type = 2 },
		{ name = "暴击率+0.3", data = 30, type = 32 },
    },
}

gdEvolutionAttribute[29] = {
    id = 29,
    name = "凝气4",
    attr = {
        { name = "魂石最大攻击+19%", data = 1900, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+19%", data = 1900, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+19%", data = 1900, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+26600", data = 26600, type = 1 },
        { name = "魔法上限+23200", data = 23200, type = 2 },
		{ name = "暴击率+0.4", data = 40, type = 32 },
    },
    fsattr = {
        { name = "生命上限+15000", data = 15000, type = 1 },
        { name = "魔法上限+40600", data = 40600, type = 2 },
		{ name = "暴击率+0.4", data = 40, type = 32 },
    },
    zsattr = {
        { name = "生命上限+41300", data = 41300, type = 1 },
        { name = "魔法上限+2900", data = 2900, type = 2 },
		{ name = "暴击率+0.4", data = 40, type = 32 },
    },
}

gdEvolutionAttribute[30] = {
    id = 30,
    name = "凝气5",
    attr = {
        { name = "魂石最大攻击+20%", data = 2000, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+20%", data = 2000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+20%", data = 2000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+27500", data = 27500, type = 1 },
        { name = "魔法上限+24000", data = 24000, type = 2 },
		{ name = "暴击率+0.5", data = 50, type = 32 },
    },
    fsattr = {
        { name = "生命上限+15500", data = 15500, type = 1 },
        { name = "魔法上限+42000", data = 42000, type = 2 },
		{ name = "暴击率+0.5", data = 50, type = 32 },
    },
    zsattr = {
        { name = "生命上限+43300", data = 43300, type = 1 },
        { name = "魔法上限+3000", data = 3000, type = 2 },
		{ name = "暴击率+0.5", data = 50, type = 32 },
    },
}

-- 31-35转
gdEvolutionAttribute[31] = {
    id = 31,
    name = "凝气6",
    attr = {
        { name = "魂石最大攻击+21%", data = 2100, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+21%", data = 2100, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+21%", data = 2100, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+28400", data = 28400, type = 1 },
        { name = "魔法上限+24800", data = 24800, type = 2 },
		{ name = "暴击率+0.6", data = 60, type = 32 },
    },
    fsattr = {
        { name = "生命上限+16000", data = 16000, type = 1 },
        { name = "魔法上限+43400", data = 43400, type = 2 },
		{ name = "暴击率+0.6", data = 60, type = 32 },
    },
    zsattr = {
        { name = "生命上限+45300", data = 45300, type = 1 },
        { name = "魔法上限+3100", data = 3100, type = 2 },
		{ name = "暴击率+0.6", data = 60, type = 32 },
    },
}

gdEvolutionAttribute[32] = {
    id = 32,
    name = "凝气7",
    attr = {
        { name = "魂石最大攻击+22%", data = 2200, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+22%", data = 2200, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+22%", data = 2200, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+29300", data = 29300, type = 1 },
        { name = "魔法上限+25600", data = 25600, type = 2 },
		{ name = "暴击率+0.7", data = 70, type = 32 },
    },
    fsattr = {
        { name = "生命上限+16500", data = 16500, type = 1 },
        { name = "魔法上限+44800", data = 44800, type = 2 },
		{ name = "暴击率+0.7", data = 70, type = 32 },
    },
    zsattr = {
        { name = "生命上限+47300", data = 47300, type = 1 },
        { name = "魔法上限+3200", data = 3200, type = 2 },
		{ name = "暴击率+0.7", data = 70, type = 32 },
    },
}

gdEvolutionAttribute[33] = {
    id = 33,
    name = "凝气8",
    attr = {
        { name = "魂石最大攻击+23%", data = 2300, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+23%", data = 2300, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+23%", data = 2300, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+30200", data = 30200, type = 1 },
        { name = "魔法上限+26400", data = 26400, type = 2 },
		{ name = "暴击率+0.8", data = 80, type = 32 },
    },
    fsattr = {
        { name = "生命上限+17000", data = 17000, type = 1 },
        { name = "魔法上限+46200", data = 46200, type = 2 },
		{ name = "暴击率+0.8", data = 80, type = 32 },
    },
    zsattr = {
        { name = "生命上限+49300", data = 49300, type = 1 },
        { name = "魔法上限+3300", data = 3300, type = 2 },
		{ name = "暴击率+0.8", data = 80, type = 32 },
    },
}

gdEvolutionAttribute[34] = {
    id = 34,
    name = "凝气9",
    attr = {
        { name = "魂石最大攻击+24%", data = 2400, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+24%", data = 2400, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+24%", data = 2400, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+31100", data = 31100, type = 1 },
        { name = "魔法上限+27200", data = 27200, type = 2 },
		{ name = "暴击率+0.9", data = 90, type = 32 },
    },
    fsattr = {
        { name = "生命上限+17500", data = 17500, type = 1 },
        { name = "魔法上限+47600", data = 47600, type = 2 },
		{ name = "暴击率+0.9", data = 90, type = 32 },
    },
    zsattr = {
        { name = "生命上限+51300", data = 51300, type = 1 },
        { name = "魔法上限+3400", data = 3400, type = 2 },
		{ name = "暴击率+0.9", data = 90, type = 32 },
    },
}

gdEvolutionAttribute[35] = {
    id = 35,
    name = "凝气10",
    attr = {
        { name = "魂石最大攻击+25%", data = 2500, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+25%", data = 2500, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+25%", data = 2500, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+32000", data = 32000, type = 1 },
        { name = "魔法上限+28000", data = 28000, type = 2 },
		{ name = "暴击率+1.0", data = 100, type = 32 },
    },
    fsattr = {
        { name = "生命上限+18000", data = 18000, type = 1 },
        { name = "魔法上限+49000", data = 49000, type = 2 },
		{ name = "暴击率+1.0", data = 100, type = 32 },
    },
    zsattr = {
        { name = "生命上限+53300", data = 53300, type = 1 },
        { name = "魔法上限+3500", data = 3500, type = 2 },
		{ name = "暴击率+1.0", data = 100, type = 32 },
    },
}

-- 36-40转
gdEvolutionAttribute[36] = {
    id = 36,
    name = "凝气11",
    attr = {
        { name = "魂石最大攻击+26%", data = 2600, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+26%", data = 2600, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+26%", data = 2600, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+32900", data = 32900, type = 1 },
        { name = "魔法上限+28800", data = 28800, type = 2 },
		{ name = "暴击率+1.1", data = 110, type = 32 },
    },
    fsattr = {
        { name = "生命上限+18500", data = 18500, type = 1 },
        { name = "魔法上限+50400", data = 50400, type = 2 },
		{ name = "暴击率+1.1", data = 110, type = 32 },
    },
    zsattr = {
        { name = "生命上限+55300", data = 55300, type = 1 },
        { name = "魔法上限+3600", data = 3600, type = 2 },
		{ name = "暴击率+1.1", data = 110, type = 32 },
    },
}

gdEvolutionAttribute[37] = {
    id = 37,
    name = "凝气12",
    attr = {
        { name = "魂石最大攻击+27%", data = 2700, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+27%", data = 2700, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+27%", data = 2700, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+33800", data = 33800, type = 1 },
        { name = "魔法上限+29600", data = 29600, type = 2 },
		{ name = "暴击率+1.2", data = 120, type = 32 },
    },
    fsattr = {
        { name = "生命上限+19000", data = 19000, type = 1 },
        { name = "魔法上限+51800", data = 51800, type = 2 },
		{ name = "暴击率+1.2", data = 120, type = 32 },
    },
    zsattr = {
        { name = "生命上限+57300", data = 57300, type = 1 },
        { name = "魔法上限+3700", data = 3700, type = 2 },
		{ name = "暴击率+1.2", data = 120, type = 32 },
    },
}

gdEvolutionAttribute[38] = {
    id = 38,
    name = "凝气13",
    attr = {
        { name = "魂石最大攻击+28%", data = 2800, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+28%", data = 2800, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+28%", data = 2800, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+34700", data = 34700, type = 1 },
        { name = "魔法上限+30400", data = 30400, type = 2 },
		{ name = "暴击率+1.3", data = 130, type = 32 },
    },
    fsattr = {
        { name = "生命上限+19500", data = 19500, type = 1 },
        { name = "魔法上限+53200", data = 53200, type = 2 },
		{ name = "暴击率+1.3", data = 130, type = 32 },
    },
    zsattr = {
        { name = "生命上限+59300", data = 59300, type = 1 },
        { name = "魔法上限+3800", data = 3800, type = 2 },
		{ name = "暴击率+1.3", data = 130, type = 32 },
    },
}

gdEvolutionAttribute[39] = {
    id = 39,
    name = "凝气14",
    attr = {
        { name = "魂石最大攻击+29%", data = 2900, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+29%", data = 2900, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+29%", data = 2900, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+35600", data = 35600, type = 1 },
        { name = "魔法上限+31200", data = 31200, type = 2 },
		{ name = "暴击率+1.4", data = 140, type = 32 },
    },
    fsattr = {
        { name = "生命上限+20000", data = 20000, type = 1 },
        { name = "魔法上限+54600", data = 54600, type = 2 },
		{ name = "暴击率+1.4", data = 140, type = 32 },
    },
    zsattr = {
        { name = "生命上限+61300", data = 61300, type = 1 },
        { name = "魔法上限+3900", data = 3900, type = 2 },
		{ name = "暴击率+1.4", data = 140, type = 32 },
    },
}

gdEvolutionAttribute[40] = {
    id = 40,
    name = "凝气15",
    attr = {
        { name = "魂石最大攻击+30%", data = 3000, isstone = true, typetable= {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+30%", data = 3000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+30%", data = 3000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+36500", data = 36500, type = 1 },
        { name = "魔法上限+32000", data = 32000, type = 2 },
		{ name = "暴击率+1.5", data = 150, type = 32 },
    },
    fsattr = {
        { name = "生命上限+20500", data = 20500, type = 1 },
        { name = "魔法上限+56000", data = 56000, type = 2 },
		{ name = "暴击率+1.5", data = 150, type = 32 },
    },
    zsattr = {
        { name = "生命上限+63300", data = 63300, type = 1 },
        { name = "魔法上限+4000", data = 4000, type = 2 },
		{ name = "暴击率+1.5", data = 150, type = 32 },
    },
}
-- 41转属性
gdEvolutionAttribute[41] = {
    id = 41,
    name = "筑基",
    attr = {
        { name = "魂石最大攻击+52.5%", data = 5250, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+52.5%", data = 5250, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+52.5%", data = 5250, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+128250", data = 128250, type = 1 },
        { name = "魔法上限+108300", data = 108300, type = 2 },
        { name = "暴击率+2.0", data = 200, type = 32 },
    },
    fsattr = {
        { name = "生命上限+47880", data = 47880, type = 1 },  -- 原79800×0.6=47880
        { name = "魔法上限+119700", data = 119700, type = 2 },  -- 原199500×0.6=119700
        { name = "暴击率+2.0", data = 200, type = 32 },
    },
    zsattr = {
        { name = "生命上限+242250", data = 242250, type = 1 },
        { name = "魔法上限+17100", data = 17100, type = 2 },
        { name = "暴击率+2.0", data = 200, type = 32 },
    },
}

-- 42转属性
gdEvolutionAttribute[42] = {
    id = 42,
    name = "结丹",
    attr = {
        { name = "魂石最大攻击+60%", data = 6000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+60%", data = 6000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+60%", data = 6000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+152475", data = 152475, type = 1 },
        { name = "魔法上限+125400", data = 125400, type = 2 },
        { name = "暴击率+2.5", data = 250, type = 32 },
    },
    fsattr = {
        { name = "生命上限+60705", data = 60705, type = 1 },  -- 原101175×0.6≈60705
        { name = "魔法上限+143640", data = 143640, type = 2 },  -- 原239400×0.6=143640
        { name = "暴击率+2.5", data = 250, type = 32 },
    },
    zsattr = {
        { name = "生命上限+304095", data = 304095, type = 1 },
        { name = "魔法上限+22800", data = 22800, type = 2 },
        { name = "暴击率+2.5", data = 250, type = 32 },
    },
}

-- 43转属性
gdEvolutionAttribute[43] = {
    id = 43,
    name = "元婴",
    attr = {
        { name = "魂石最大攻击+67.5%", data = 6750, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+67.5%", data = 6750, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+67.5%", data = 6750, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+176700", data = 176700, type = 1 },
        { name = "魔法上限+142500", data = 142500, type = 2 },
        { name = "暴击率+3.0", data = 300, type = 32 },
    },
    fsattr = {
        { name = "生命上限+73530", data = 73530, type = 1 },  -- 原122550×0.6=73530
        { name = "魔法上限+167580", data = 167580, type = 2 },  -- 原279300×0.6=167580
        { name = "暴击率+3.0", data = 300, type = 32 },
    },
    zsattr = {
        { name = "生命上限+365940", data = 365940, type = 1 },
        { name = "魔法上限+28500", data = 28500, type = 2 },
        { name = "暴击率+3.0", data = 300, type = 32 },
    },
}

-- 44转属性
gdEvolutionAttribute[44] = {
    id = 44,
    name = "化神",
    attr = {
        { name = "魂石最大攻击+75%", data = 7500, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+75%", data = 7500, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+75%", data = 7500, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+200925", data = 200925, type = 1 },
        { name = "魔法上限+159600", data = 159600, type = 2 },
        { name = "暴击率+5.0", data = 500, type = 32 },
    },
    fsattr = {
        { name = "生命上限+86355", data = 86355, type = 1 },  -- 原143925×0.6=86355
        { name = "魔法上限+191520", data = 191520, type = 2 },  -- 原319200×0.6=191520
        { name = "暴击率+5.0", data = 500, type = 32 },
    },
    zsattr = {
        { name = "生命上限+427785", data = 427785, type = 1 },
        { name = "魔法上限+34200", data = 34200, type = 2 },
        { name = "暴击率+5.0", data = 500, type = 32 },
    },
}

-- 45转属性
gdEvolutionAttribute[45] = {
    id = 45,
    name = "婴变",
    attr = {
        { name = "魂石最大攻击+82.5%", data = 8250, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+82.5%", data = 8250, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+82.5%", data = 8250, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+225150", data = 225150, type = 1 },
        { name = "魔法上限+176700", data = 176700, type = 2 },
        { name = "暴击率+6.0", data = 600, type = 32 },
    },
    fsattr = {
        { name = "生命上限+99180", data = 99180, type = 1 },  -- 原165300×0.6=99180
        { name = "魔法上限+215460", data = 215460, type = 2 },  -- 原359100×0.6=215460
        { name = "暴击率+6.0", data = 600, type = 32 },
    },
    zsattr = {
        { name = "生命上限+489630", data = 489630, type = 1 },
        { name = "魔法上限+39900", data = 39900, type = 2 },
        { name = "暴击率+6.0", data = 600, type = 32 },
    },
}

-- 46转属性
gdEvolutionAttribute[46] = {
    id = 46,
    name = "问鼎",
    attr = {
        { name = "魂石最大攻击+90%", data = 9000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+90%", data = 9000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+90%", data = 9000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+249375", data = 249375, type = 1 },
        { name = "魔法上限+193800", data = 193800, type = 2 },
        { name = "暴击率+7.0", data = 700, type = 32 },
    },
    fsattr = {
        { name = "生命上限+112005", data = 112005, type = 1 },  -- 原186675×0.6≈112005
        { name = "魔法上限+239400", data = 239400, type = 2 },  -- 原399000×0.6=239400
        { name = "暴击率+7.0", data = 700, type = 32 },
    },
    zsattr = {
        { name = "生命上限+551475", data = 551475, type = 1 },
        { name = "魔法上限+45600", data = 45600, type = 2 },
        { name = "暴击率+7.0", data = 700, type = 32 },
    },
}

-- 47转属性
gdEvolutionAttribute[47] = {
    id = 47,
    name = "阴虚",
    attr = {
        { name = "魂石最大攻击+99%", data = 9900, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+99%", data = 9900, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+99%", data = 9900, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+279300", data = 279300, type = 1 },
        { name = "魔法上限+213750", data = 213750, type = 2 },
        { name = "暴击率+8.0", data = 800, type = 32 },
    },
    fsattr = {
        { name = "生命上限+127395", data = 127395, type = 1 },  -- 原212325×0.6≈127395
        { name = "魔法上限+265050", data = 265050, type = 2 },  -- 原441750×0.6=265050
        { name = "暴击率+8.0", data = 800, type = 32 },
    },
    zsattr = {
        { name = "生命上限+627000", data = 627000, type = 1 },
        { name = "魔法上限+52725", data = 52725, type = 2 },
        { name = "暴击率+8.0", data = 800, type = 32 },
    },
}

-- 48转属性
gdEvolutionAttribute[48] = {
    id = 48,
    name = "阳实",
    attr = {
        { name = "魂石最大攻击+108%", data = 10800, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+108%", data = 10800, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+108%", data = 10800, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+313500", data = 313500, type = 1 },
        { name = "魔法上限+236550", data = 236550, type = 2 },
        { name = "暴击率+9.0", data = 900, type = 32 },
    },
    fsattr = {
        { name = "生命上限+145350", data = 145350, type = 1 },  -- 原242250×0.6=145350
        { name = "魔法上限+292410", data = 292410, type = 2 },  -- 原487350×0.6=292410
        { name = "暴击率+9.0", data = 900, type = 32 },
    },
    zsattr = {
        { name = "生命上限+715350", data = 715350, type = 1 },
        { name = "魔法上限+61275", data = 61275, type = 2 },
        { name = "暴击率+9.0", data = 900, type = 32 },
    },
}

-- 49转属性
gdEvolutionAttribute[49] = {
    id = 49,
    name = "窥涅",
    attr = {
        { name = "魂石最大攻击+117%", data = 11700, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+117%", data = 11700, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+117%", data = 11700, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+351975", data = 351975, type = 1 },
        { name = "魔法上限+262200", data = 262200, type = 2 },
        { name = "暴击率+10.0", data = 1000, type = 32 },
    },
    fsattr = {
        { name = "生命上限+165870", data = 165870, type = 1 },  -- 原276450×0.6=165870
        { name = "魔法上限+321480", data = 321480, type = 2 },  -- 原535800×0.6=321480
        { name = "暴击率+10.0", data = 1000, type = 32 },
    },
    zsattr = {
        { name = "生命上限+816525", data = 816525, type = 1 },
        { name = "魔法上限+71250", data = 71250, type = 2 },
        { name = "暴击率+10.0", data = 1000, type = 32 },
    },
}

-- 50转属性
gdEvolutionAttribute[50] = {
    id = 50,
    name = "净涅",
    attr = {
        { name = "魂石最大攻击+127.5%", data = 12750, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+127.5%", data = 12750, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+127.5%", data = 12750, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+394725", data = 394725, type = 1 },
        { name = "魔法上限+290700", data = 290700, type = 2 },
        { name = "暴击率+20.0", data = 2000, type = 32 },
    },
    fsattr = {
        { name = "生命上限+188100", data = 188100, type = 1 },  -- 原313500×0.6=188100
        { name = "魔法上限+352260", data = 352260, type = 2 },  -- 原587100×0.6=352260
        { name = "暴击率+20.0", data = 2000, type = 32 },
    },
    zsattr = {
        { name = "生命上限+930525", data = 930525, type = 1 },
        { name = "魔法上限+82650", data = 82650, type = 2 },
        { name = "暴击率+20.0", data = 2000, type = 32 },
    },
}

-- 51转属性
gdEvolutionAttribute[51] = {
    id = 51,
    name = "碎涅",
    attr = {
        { name = "魂石最大攻击+138%", data = 13800, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+138%", data = 13800, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+138%", data = 13800, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+441750", data = 441750, type = 1 },
        { name = "魔法上限+319200", data = 319200, type = 2 },
        { name = "暴击率+25.0", data = 2500, type = 32 },
    },
    fsattr = {
        { name = "生命上限+212040", data = 212040, type = 1 },  -- 原353400×0.6=212040
        { name = "魔法上限+384750", data = 384750, type = 2 },  -- 原641250×0.6=384750
        { name = "暴击率+25.0", data = 2500, type = 32 },
    },
    zsattr = {
        { name = "生命上限+1057350", data = 1057350, type = 1 },
        { name = "魔法上限+95475", data = 95475, type = 2 },
        { name = "暴击率+25.0", data = 2500, type = 32 },
    },
}

-- 52转属性
gdEvolutionAttribute[52] = {
    id = 52,
    name = "天人五衰",
    attr = {
        { name = "魂石最大攻击+150%", data = 15000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+150%", data = 15000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+150%", data = 15000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+493050", data = 493050, type = 1 },
        { name = "魔法上限+350550", data = 350550, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
    },
    fsattr = {
        { name = "生命上限+237690", data = 237690, type = 1 },  -- 原396150×0.6=237690
        { name = "魔法上限+418950", data = 418950, type = 2 },  -- 原698250×0.6=418950
        { name = "暴击率+30.0", data = 3000, type = 32 },
    },
    zsattr = {
        { name = "生命上限+1197000", data = 1197000, type = 1 },
        { name = "魔法上限+109725", data = 109725, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
    },
}

-- 53转属性
gdEvolutionAttribute[53] = {
    id = 53,
    name = "空涅",
    attr = {
        { name = "魂石最大攻击+162%", data = 16200, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+162%", data = 16200, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+162%", data = 16200, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+548625", data = 548625, type = 1 },
        { name = "魔法上限+384750", data = 384750, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.0", data = 100, type = 34 },
    },
    fsattr = {
        { name = "生命上限+265050", data = 265050, type = 1 },  -- 原441750×0.6=265050
        { name = "魔法上限+454860", data = 454860, type = 2 },  -- 原758100×0.6=454860
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.0", data = 100, type = 34 },
    },
    zsattr = {
        { name = "生命上限+1348050", data = 1348050, type = 1 },
        { name = "魔法上限+125400", data = 125400, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.0", data = 100, type = 34 },
    },
}

-- 54转属性
gdEvolutionAttribute[54] = {
    id = 54,
    name = "空灵",
    attr = {
        { name = "魂石最大攻击+174%", data = 17400, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+174%", data = 17400, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+174%", data = 17400, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+608475", data = 608475, type = 1 },
        { name = "魔法上限+421800", data = 421800, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.1", data = 110, type = 34 },
    },
    fsattr = {
        { name = "生命上限+294120", data = 294120, type = 1 },  -- 原490200×0.6=294120
        { name = "魔法上限+492480", data = 492480, type = 2 },  -- 原820800×0.6=492480
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.1", data = 110, type = 34 },
    },
    zsattr = {
        { name = "生命上限+1510500", data = 1510500, type = 1 },
        { name = "魔法上限+142500", data = 142500, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.1", data = 110, type = 34 },
    },
}

-- 55转属性
gdEvolutionAttribute[55] = {
    id = 55,
    name = "空玄",
    attr = {
        { name = "魂石最大攻击+187.5%", data = 18750, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+187.5%", data = 18750, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+187.5%", data = 18750, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+672600", data = 672600, type = 1 },
        { name = "魔法上限+461700", data = 461700, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.5", data = 150, type = 34 },
    },
    fsattr = {
        { name = "生命上限+324900", data = 324900, type = 1 },  -- 原541500×0.6=324900
        { name = "魔法上限+531810", data = 531810, type = 2 },  -- 原886350×0.6=531810
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.5", data = 150, type = 34 },
    },
    zsattr = {
        { name = "生命上限+1684350", data = 1684350, type = 1 },
        { name = "魔法上限+161025", data = 161025, type = 2 },
        { name = "暴击率+30.0", data = 3000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.5", data = 150, type = 34 },
    },
}

-- 56转属性
gdEvolutionAttribute[56] = {
    id = 56,
    name = "空劫",
    attr = {
        { name = "魂石最大攻击+202.5%", data = 20250, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+202.5%", data = 20250, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+202.5%", data = 20250, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+741000", data = 741000, type = 1 },
        { name = "魔法上限+504450", data = 504450, type = 2 },
        { name = "暴击率+35.0", data = 3500, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.5", data = 150, type = 34 },
    },
    fsattr = {
        { name = "生命上限+357390", data = 357390, type = 1 },  -- 原595650×0.6=357390
        { name = "魔法上限+572850", data = 572850, type = 2 },  -- 原954750×0.6=572850
        { name = "暴击率+35.0", data = 3500, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.5", data = 150, type = 34 },
    },
    zsattr = {
        { name = "生命上限+1869600", data = 1869600, type = 1 },
        { name = "魔法上限+180975", data = 180975, type = 2 },
        { name = "暴击率+35.0", data = 3500, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.5", data = 150, type = 34 },
    },
}

-- 57转属性
gdEvolutionAttribute[57] = {
    id = 57,
    name = "大尊",
    attr = {
        { name = "魂石最大攻击+217.5%", data = 21750, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+217.5%", data = 21750, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+217.5%", data = 21750, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+813675", data = 813675, type = 1 },
        { name = "魔法上限+550050", data = 550050, type = 2 },
        { name = "暴击率+40.0", data = 4000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.6", data = 160, type = 34 },
    },
    fsattr = {
        { name = "生命上限+391590", data = 391590, type = 1 },  -- 原652650×0.6=391590
        { name = "魔法上限+615600", data = 615600, type = 2 },  -- 原1026000×0.6=615600
        { name = "暴击率+40.0", data = 4000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.6", data = 160, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2066250", data = 2066250, type = 1 },
        { name = "魔法上限+202350", data = 202350, type = 2 },
        { name = "暴击率+40.0", data = 4000, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.6", data = 160, type = 34 },
    },
}

-- 58转属性
gdEvolutionAttribute[58] = {
    id = 58,
    name = "金尊",
    attr = {
        { name = "魂石最大攻击+232.5%", data = 23250, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+232.5%", data = 23250, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+232.5%", data = 23250, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+890625", data = 890625, type = 1 },
        { name = "魔法上限+598500", data = 598500, type = 2 },
        { name = "暴击率+45.0", data = 4500, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.8", data = 180, type = 34 },
    },
    fsattr = {
        { name = "生命上限+427500", data = 427500, type = 1 },  -- 原712500×0.6=427500
        { name = "魔法上限+660060", data = 660060, type = 2 },  -- 原1100100×0.6=660060
        { name = "暴击率+45.0", data = 4500, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.8", data = 180, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2274300", data = 2274300, type = 1 },
        { name = "魔法上限+225150", data = 225150, type = 2 },
        { name = "暴击率+45.0", data = 4500, type = 32 },
        { name = "防爆率+30.0", data = 3000, type = 33 },
        { name = "反弹率+1.8", data = 180, type = 34 },
    },
}

-- 59转属性
gdEvolutionAttribute[59] = {
    id = 59,
    name = "天尊",
    attr = {
        { name = "魂石最大攻击+247.5%", data = 24750, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+247.5%", data = 24750, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+247.5%", data = 24750, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+971850", data = 971850, type = 1 },
        { name = "魔法上限+649800", data = 649800, type = 2 },
        { name = "暴击率+45.0", data = 4500, type = 32 },
        { name = "防爆率+35.0", data = 3500, type = 33 },
        { name = "反弹率+2.0", data = 200, type = 34 },
    },
    fsattr = {
        { name = "生命上限+465120", data = 465120, type = 1 },  -- 原775200×0.6=465120
        { name = "魔法上限+706230", data = 706230, type = 2 },  -- 原1177050×0.6=706230
        { name = "暴击率+45.0", data = 4500, type = 32 },
        { name = "防爆率+35.0", data = 3500, type = 33 },
        { name = "反弹率+2.0", data = 200, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2493750", data = 2493750, type = 1 },
        { name = "魔法上限+249375", data = 249375, type = 2 },
        { name = "暴击率+45.0", data = 4500, type = 32 },
        { name = "防爆率+35.0", data = 3500, type = 33 },
        { name = "反弹率+2.0", data = 200, type = 34 },
    },
}

-- 60转属性
gdEvolutionAttribute[60] = {
    id = 60,
    name = "跃天尊",
    attr = {
        { name = "魂石最大攻击+262.5%", data = 26250, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+262.5%", data = 26250, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+262.5%", data = 26250, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1057350", data = 1057350, type = 1 },
        { name = "魔法上限+703950", data = 703950, type = 2 },
        { name = "暴击率+48.0", data = 4800, type = 32 },
        { name = "防爆率+40.0", data = 4000, type = 33 },
        { name = "反弹率+2.1", data = 210, type = 34 },
    },
    fsattr = {
        { name = "生命上限+504450", data = 504450, type = 1 },  -- 原840750×0.6=504450
        { name = "魔法上限+754110", data = 754110, type = 2 },  -- 原1256850×0.6=754110
        { name = "暴击率+48.0", data = 4800, type = 32 },
        { name = "防爆率+40.0", data = 4000, type = 33 },
        { name = "反弹率+2.1", data = 210, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2721750", data = 2721750, type = 1 },
        { name = "魔法上限+275025", data = 275025, type = 2 },
        { name = "暴击率+48.0", data = 4800, type = 32 },
        { name = "防爆率+40.0", data = 4000, type = 33 },
        { name = "反弹率+2.1", data = 210, type = 34 },
    },
}

-- 61转属性
gdEvolutionAttribute[61] = {
    id = 61,
    name = "大天尊",
    attr = {
        { name = "魂石最大攻击+435%", data = 43500, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+435%", data = 43500, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+435%", data = 43500, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+761805", data = 761805, type = 1 },
        { name = "魔法上限+677160", data = 677160, type = 2 },
        { name = "暴击率+48.0", data = 4800, type = 32 },
        { name = "防爆率+40.0", data = 4000, type = 33 },
        { name = "反弹率+2.5", data = 250, type = 34 },
    },
    fsattr = {
        { name = "生命上限+275823", data = 275823, type = 1 },  -- 原459705×0.6≈275823
        { name = "魔法上限+703836", data = 703836, type = 2 },  -- 原1173060×0.6=703836
        { name = "暴击率+48.0", data = 4800, type = 32 },
        { name = "防爆率+40.0", data = 4000, type = 33 },
        { name = "反弹率+2.5", data = 250, type = 34 },
    },
    zsattr = {
        { name = "生命上限+1582605", data = 1582605, type = 1 },
        { name = "魔法上限+86355", data = 86355, type = 2 },
        { name = "暴击率+48.0", data = 4800, type = 32 },
        { name = "防爆率+40.0", data = 4000, type = 33 },
        { name = "反弹率+2.5", data = 250, type = 34 },
    },
}

-- 62转属性
gdEvolutionAttribute[62] = {
    id = 62,
    name = "踏天",
    attr = {
        { name = "魂石最大攻击+510%", data = 51000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+510%", data = 51000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+510%", data = 51000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+890055", data = 890055, type = 1 },
        { name = "魔法上限+791160", data = 791160, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+45.0", data = 4500, type = 33 },
        { name = "反弹率+3.0", data = 300, type = 34 },
    },
    fsattr = {
        { name = "生命上限+322848", data = 322848, type = 1 },      -- 原538080×0.6=322848
        { name = "魔法上限+823536", data = 823536, type = 2 },      -- 原1372560×0.6=823536
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+45.0", data = 4500, type = 33 },
        { name = "反弹率+3.0", data = 300, type = 34 },
    },
    zsattr = {
        { name = "生命上限+1867605", data = 1867605, type = 1 },
        { name = "魔法上限+100605", data = 100605, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+45.0", data = 4500, type = 33 },
        { name = "反弹率+3.0", data = 300, type = 34 },
    },
}

-- 63转属性
gdEvolutionAttribute[63] = {
    id = 63,
    name = "煌天",
    attr = {
        { name = "魂石最大攻击+675%", data = 67500, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+675%", data = 67500, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+675%", data = 67500, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1018305", data = 1018305, type = 1 },
        { name = "魔法上限+905160", data = 905160, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+45.0", data = 4500, type = 33 },
        { name = "反弹率+3.0", data = 300, type = 34 },
    },
    fsattr = {
        { name = "生命上限+369873", data = 369873, type = 1 },      -- 原616455×0.6≈369873
        { name = "魔法上限+943236", data = 943236, type = 2 },      -- 原1572060×0.6=943236
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+45.0", data = 4500, type = 33 },
        { name = "反弹率+3.0", data = 300, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2152605", data = 2152605, type = 1 },
        { name = "魔法上限+114855", data = 114855, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+45.0", data = 4500, type = 33 },
        { name = "反弹率+3.0", data = 300, type = 34 },
    },
}

-- 64转属性
gdEvolutionAttribute[64] = {
    id = 64,
    name = "煌天中期",
    attr = {
        { name = "魂石最大攻击+900%", data = 90000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+900%", data = 90000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+900%", data = 90000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1140555", data = 1140555, type = 1 },
        { name = "魔法上限+981660", data = 981660, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+46.0", data = 4600, type = 33 },
        { name = "反弹率+3.5", data = 350, type = 34 },
    },
    fsattr = {
        { name = "生命上限+413838", data = 413838, type = 1 },      -- 原689730×0.6=413838
        { name = "魔法上限+1025136", data = 1025136, type = 2 },    -- 原1708560×0.6=1025136
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+46.0", data = 4600, type = 33 },
        { name = "反弹率+3.5", data = 350, type = 34 },
    },
    zsattr = {
        { name = "生命上限+1905105", data = 1905105, type = 1 },
        { name = "魔法上限+123855", data = 123855, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+46.0", data = 4600, type = 33 },
        { name = "反弹率+3.5", data = 350, type = 34 },
    },
}

-- 65转属性
gdEvolutionAttribute[65] = {
    id = 65,
    name = "煌天大圆满",
    attr = {
        { name = "魂石最大攻击+1500%", data = 150000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+1500%", data = 150000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+1500%", data = 150000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1262535", data = 1262535, type = 1 },
        { name = "魔法上限+993360", data = 993360, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+50.0", data = 5000, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    fsattr = {
        { name = "生命上限+457713", data = 457713, type = 1 },      -- 原762855×0.6≈457713
        { name = "魔法上限+1038636", data = 1038636, type = 2 },    -- 原1731060×0.6=1038636
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+50.0", data = 5000, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2217105", data = 2217105, type = 1 },
        { name = "魔法上限+134355", data = 134355, type = 2 },
        { name = "暴击率+50.0", data = 5000, type = 32 },
        { name = "防爆率+50.0", data = 5000, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
}
--------------------------------------------------------------------------------------------------
gdEvolutionAttribute[66] = {
    id = 66,
    name = "道成",
    attr = {
        { name = "魂石最大攻击+1600%", data = 160000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+1600%", data = 160000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+1600%", data = 160000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1362535", data = 1362535, type = 1 },
        { name = "魔法上限+1003360", data = 1003360, type = 2 },
        { name = "暴击率+51.0", data = 5100, type = 32 },
        { name = "防爆率+51.0", data = 5100, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    fsattr = {
        { name = "生命上限+467713", data = 467713, type = 1 },      
        { name = "魔法上限+1138636", data = 1138636, type = 2 },    
        { name = "暴击率+51.0", data = 5100, type = 32 },
        { name = "防爆率+51.0", data = 5100, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2317105", data = 2317105, type = 1 },
        { name = "魔法上限+144355", data = 144355, type = 2 },
        { name = "暴击率+51.0", data = 5100, type = 32 },
        { name = "防爆率+51.0", data = 5100, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
}
gdEvolutionAttribute[67] = {
    id = 67,
    name = "道果",
    attr = {
        { name = "魂石最大攻击+1800%", data = 180000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+1800%", data = 180000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+1800%", data = 180000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1562535", data = 1562535, type = 1 },
        { name = "魔法上限+1203360", data = 1203360, type = 2 },
        { name = "暴击率+52.0", data = 5200, type = 32 },
        { name = "防爆率+52.0", data = 5200, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    fsattr = {
        { name = "生命上限+487713", data = 487713, type = 1 },      
        { name = "魔法上限+1338636", data = 1338636, type = 2 },    
        { name = "暴击率+52.0", data = 5200, type = 32 },
        { name = "防爆率+52.0", data = 5200, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2517105", data = 2517105, type = 1 },
        { name = "魔法上限+164355", data = 164355, type = 2 },
        { name = "暴击率+52.0", data = 5200, type = 32 },
        { name = "防爆率+52.0", data = 5200, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
}
gdEvolutionAttribute[68] = {
    id = 68,
    name = "道蚀",
    attr = {
        { name = "魂石最大攻击+2000%", data = 200000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+2000%", data = 200000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+2000%", data = 200000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1762535", data = 1762535, type = 1 },
        { name = "魔法上限+1403360", data = 1403360, type = 2 },
        { name = "暴击率+53.0", data = 5300, type = 32 },
        { name = "防爆率+53.0", data = 5300, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    fsattr = {
        { name = "生命上限+507713", data = 507713, type = 1 },      
        { name = "魔法上限+1538636", data = 1538636, type = 2 },    
        { name = "暴击率+53.0", data = 5300, type = 32 },
        { name = "防爆率+53.0", data = 5300, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2717105", data = 2717105, type = 1 },
        { name = "魔法上限+184355", data = 184355, type = 2 },
        { name = "暴击率+53.0", data = 5300, type = 32 },
        { name = "防爆率+53.0", data = 5300, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
}
gdEvolutionAttribute[69] = {
    id = 69,
    name = "道涅",
    attr = {
        { name = "魂石最大攻击+2200%", data = 220000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+2200%", data = 220000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+2200%", data = 220000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+1962535", data = 1962535, type = 1 },
        { name = "魔法上限+1603360", data = 1603360, type = 2 },
        { name = "暴击率+54.0", data = 5400, type = 32 },
        { name = "防爆率+54.0", data = 5400, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    fsattr = {
        { name = "生命上限+527713", data = 527713, type = 1 },      
        { name = "魔法上限+1738636", data = 1738636, type = 2 },    
        { name = "暴击率+54.0", data = 5400, type = 32 },
        { name = "防爆率+54.0", data = 5400, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
    zsattr = {
        { name = "生命上限+2917105", data = 2917105, type = 1 },
        { name = "魔法上限+204355", data = 204355, type = 2 },
        { name = "暴击率+54.0", data = 5400, type = 32 },
        { name = "防爆率+54.0", data = 5400, type = 33 },
        { name = "反弹率+4.0", data = 400, type = 34 },
    },
}
gdEvolutionAttribute[70] = {
    id = 70,
    name = "道源",
    attr = {
        { name = "魂石最大攻击+2400%", data = 240000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+2400%", data = 240000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+2400%", data = 240000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+2162535", data = 2162535, type = 1 },
        { name = "魔法上限+1803360", data = 1803360, type = 2 },
        { name = "暴击率+55.0", data = 5500, type = 32 },
        { name = "防爆率+55.0", data = 5500, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    fsattr = {
        { name = "生命上限+547713", data = 547713, type = 1 },      
        { name = "魔法上限+1938636", data = 1938636, type = 2 },    
        { name = "暴击率+55.0", data = 5500, type = 32 },
        { name = "防爆率+55.0", data = 5500, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    zsattr = {
        { name = "生命上限+3117105", data = 3117105, type = 1 },
        { name = "魔法上限+224355", data = 224355, type = 2 },
        { name = "暴击率+55.0", data = 5500, type = 32 },
        { name = "防爆率+55.0", data = 5500, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
}
gdEvolutionAttribute[71] = {
    id = 71,
    name = "大罗",
    attr = {
        { name = "魂石最大攻击+2600%", data = 260000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+2600%", data = 260000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+2600%", data = 260000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+2362535", data = 2362535, type = 1 },
        { name = "魔法上限+2003360", data = 2003360, type = 2 },
        { name = "暴击率+56.0", data = 5600, type = 32 },
        { name = "防爆率+56.0", data = 5600, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    fsattr = {
        { name = "生命上限+567713", data = 567713, type = 1 },      
        { name = "魔法上限+2138636", data = 2138636, type = 2 },    
        { name = "暴击率+56.0", data = 5600, type = 32 },
        { name = "防爆率+56.0", data = 5600, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    zsattr = {
        { name = "生命上限+3317105", data = 3317105, type = 1 },
        { name = "魔法上限+244355", data = 244355, type = 2 },
        { name = "暴击率+56.0", data = 5600, type = 32 },
        { name = "防爆率+56.0", data = 5600, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
}
gdEvolutionAttribute[72] = {
    id = 72,
    name = "法则",
    attr = {
        { name = "魂石最大攻击+2800%", data = 280000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+2800%", data = 280000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+2800%", data = 280000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+2562535", data = 2562535, type = 1 },
        { name = "魔法上限+2203360", data = 2203360, type = 2 },
        { name = "暴击率+57.0", data = 5700, type = 32 },
        { name = "防爆率+57.0", data = 5700, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    fsattr = {
        { name = "生命上限+587713", data = 587713, type = 1 },      
        { name = "魔法上限+2338636", data = 2338636, type = 2 },    
        { name = "暴击率+57.0", data = 5700, type = 32 },
        { name = "防爆率+57.0", data = 5700, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    zsattr = {
        { name = "生命上限+3517105", data = 3517105, type = 1 },
        { name = "魔法上限+264355", data = 264355, type = 2 },
        { name = "暴击率+57.0", data = 5700, type = 32 },
        { name = "防爆率+57.0", data = 5700, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
}
gdEvolutionAttribute[73] = {
    id = 73,
    name = "无相",
    attr = {
        { name = "魂石最大攻击+3000%", data = 300000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+3000%", data = 300000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+3000%", data = 300000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+2762535", data = 2762535, type = 1 },
        { name = "魔法上限+2403360", data = 2403360, type = 2 },
        { name = "暴击率+58.0", data = 5800, type = 32 },
        { name = "防爆率+58.0", data = 5800, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    fsattr = {
        { name = "生命上限+607713", data = 607713, type = 1 },      
        { name = "魔法上限+2538636", data = 2538636, type = 2 },    
        { name = "暴击率+58.0", data = 5800, type = 32 },
        { name = "防爆率+58.0", data = 5800, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    zsattr = {
        { name = "生命上限+3717105", data = 3717105, type = 1 },
        { name = "魔法上限+284355", data = 284355, type = 2 },
        { name = "暴击率+58.0", data = 5800, type = 32 },
        { name = "防爆率+58.0", data = 5800, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
}
gdEvolutionAttribute[74] = {
    id = 74,
    name = "本源",
    attr = {
        { name = "魂石最大攻击+3200%", data = 320000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+3200%", data = 320000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+3200%", data = 320000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+3062535", data = 3062535, type = 1 },
        { name = "魔法上限+2603360", data = 2603360, type = 2 },
        { name = "暴击率+59.0", data = 5900, type = 32 },
        { name = "防爆率+59.0", data = 5900, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    fsattr = {
        { name = "生命上限+627713", data = 627713, type = 1 },      
        { name = "魔法上限+2538636", data = 2538636, type = 2 },    
        { name = "暴击率+59.0", data = 5900, type = 32 },
        { name = "防爆率+59.0", data = 5900, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
    zsattr = {
        { name = "生命上限+3917105", data = 3917105, type = 1 },
        { name = "魔法上限+304355", data = 304355, type = 2 },
        { name = "暴击率+59.0", data = 5800, type = 32 },
        { name = "防爆率+59.0", data = 5800, type = 33 },
        { name = "反弹率+5.0", data = 500, type = 34 },
    },
}
gdEvolutionAttribute[75] = {
    id = 75,
    name = "归墟",
    attr = {
        { name = "魂石最大攻击+3400%", data = 340000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+3400%", data = 340000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+3400%", data = 340000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+3262535", data = 3262535, type = 1 },
        { name = "魔法上限+2803360", data = 2803360, type = 2 },
        { name = "暴击率+60.0", data = 6000, type = 32 },
        { name = "防爆率+60.0", data = 6000, type = 33 },
        { name = "反弹率+6.0", data = 600, type = 34 },
    },
    fsattr = {
        { name = "生命上限+647713", data = 647713, type = 1 },      
        { name = "魔法上限+2738636", data = 2738636, type = 2 },    
        { name = "暴击率+60.0", data = 6000, type = 32 },
        { name = "防爆率+60.0", data = 6000, type = 33 },
        { name = "反弹率+6.0", data = 600, type = 34 },
    },
    zsattr = {
        { name = "生命上限+4117105", data = 4117105, type = 1 },
        { name = "魔法上限+324355", data = 324355, type = 2 },
        { name = "暴击率+60.0", data = 6000, type = 32 },
        { name = "防爆率+60.0", data = 6000, type = 33 },
        { name = "反弹率+6.0", data = 600, type = 34 },
    },
}
gdEvolutionAttribute[76] = {
    id = 76,
    name = "天道",
    attr = {
        { name = "魂石最大攻击+3600%", data = 360000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+3600%", data = 360000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+3600%", data = 360000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+3462535", data = 3462535, type = 1 },
        { name = "魔法上限+3003360", data = 3003360, type = 2 },
        { name = "暴击率+61.0", data = 6100, type = 32 },
        { name = "防爆率+61.0", data = 6100, type = 33 },
        { name = "反弹率+7.0", data = 700, type = 34 },
    },
    fsattr = {
        { name = "生命上限+667713", data = 667713, type = 1 },      
        { name = "魔法上限+2938636", data = 2938636, type = 2 },    
        { name = "暴击率+61.0", data = 6100, type = 32 },
        { name = "防爆率+61.0", data = 6100, type = 33 },
        { name = "反弹率+7.0", data = 700, type = 34 },
    },
    zsattr = {
        { name = "生命上限+4317105", data = 4317105, type = 1 },
        { name = "魔法上限+344355", data = 344355, type = 2 },
        { name = "暴击率+61.0", data = 6100, type = 32 },
        { name = "防爆率+61.0", data = 6100, type = 33 },
        { name = "反弹率+7.0", data = 700, type = 34 },
    },
}
gdEvolutionAttribute[77] = {
    id = 77,
    name = "因果",
    attr = {
        { name = "魂石最大攻击+3800%", data = 380000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+3800%", data = 380000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+3800%", data = 380000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+3662535", data = 3662535, type = 1 },
        { name = "魔法上限+3203360", data = 3203360, type = 2 },
        { name = "暴击率+62.0", data = 6200, type = 32 },
        { name = "防爆率+62.0", data = 6200, type = 33 },
        { name = "反弹率+7.0", data = 700, type = 34 },
    },
    fsattr = {
        { name = "生命上限+687713", data = 687713, type = 1 },      
        { name = "魔法上限+3138636", data = 3138636, type = 2 },    
        { name = "暴击率+62.0", data = 6200, type = 32 },
        { name = "防爆率+62.0", data = 6200, type = 33 },
        { name = "反弹率+7.0", data = 700, type = 34 },
    },
    zsattr = {
        { name = "生命上限+4517105", data = 4517105, type = 1 },
        { name = "魔法上限+364355", data = 364355, type = 2 },
        { name = "暴击率+62.0", data = 6200, type = 32 },
        { name = "防爆率+62.0", data = 6200, type = 33 },
        { name = "反弹率+7.0", data = 700, type = 34 },
    },
}
gdEvolutionAttribute[78] = {
    id = 78,
    name = "概念",
    attr = {
        { name = "魂石最大攻击+4000%", data = 400000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+4000%", data = 400000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+4000%", data = 400000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+3862535", data = 3862535, type = 1 },
        { name = "魔法上限+3403360", data = 3403360, type = 2 },
        { name = "暴击率+63.0", data = 6300, type = 32 },
        { name = "防爆率+63.0", data = 6300, type = 33 },
        { name = "反弹率+8.0", data = 800, type = 34 },
    },
    fsattr = {
        { name = "生命上限+717713", data = 717713, type = 1 },      
        { name = "魔法上限+3338636", data = 3338636, type = 2 },    
        { name = "暴击率+63.0", data = 6300, type = 32 },
        { name = "防爆率+63.0", data = 6300, type = 33 },
        { name = "反弹率+8.0", data = 800, type = 34 },
    },
    zsattr = {
        { name = "生命上限+4717105", data = 4717105, type = 1 },
        { name = "魔法上限+384355", data = 384355, type = 2 },
        { name = "暴击率+63.0", data = 6300, type = 32 },
        { name = "防爆率+63.0", data = 6300, type = 33 },
        { name = "反弹率+8.0", data = 800, type = 34 },
    },
}
gdEvolutionAttribute[79] = {
    id = 79,
    name = "彼岸",
    attr = {
        { name = "魂石最大攻击+4500%", data = 450000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+4500%", data = 450000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+4500%", data = 450000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+3862535", data = 3862535, type = 1 },
        { name = "魔法上限+3403360", data = 3403360, type = 2 },
        { name = "暴击率+64.0", data = 6400, type = 32 },
        { name = "防爆率+64.0", data = 6400, type = 33 },
        { name = "反弹率+9.0", data = 900, type = 34 },
    },
    fsattr = {
        { name = "生命上限+717713", data = 717713, type = 1 },      
        { name = "魔法上限+3338636", data = 3338636, type = 2 },    
        { name = "暴击率+64.0", data = 6400, type = 32 },
        { name = "防爆率+64.0", data = 6400, type = 33 },
        { name = "反弹率+9.0", data = 900, type = 34 },
    },
    zsattr = {
        { name = "生命上限+4717105", data = 4717105, type = 1 },
        { name = "魔法上限+384355", data = 384355, type = 2 },
        { name = "暴击率+64.0", data = 6400, type = 32 },
        { name = "防爆率+64.0", data = 6400, type = 33 },
        { name = "反弹率+9.0", data = 900, type = 34 },
    },
}
gdEvolutionAttribute[80] = {
    id = 80,
    name = "灭天",
    attr = {
        { name = "魂石最大攻击+5000%", data = 500000, isstone = true, typetable = {[1]=45,[2]=49,[3]=47,},},
        { name = "魂石最大物理防御+5000%", data = 500000, isstone = true, type = 51 },
        { name = "魂石最大魔法防御+5000%", data = 500000, isstone = true, type = 53 },
    },
    dsattr = {
        { name = "生命上限+4862535", data = 4862535, type = 1 },
        { name = "魔法上限+4403360", data = 4403360, type = 2 },
        { name = "暴击率+65.0", data = 6500, type = 32 },
        { name = "防爆率+65.0", data = 6500, type = 33 },
        { name = "反弹率+10.0", data = 1000, type = 34 },
    },
    fsattr = {
        { name = "生命上限+817713", data = 817713, type = 1 },      
        { name = "魔法上限+4338636", data = 4338636, type = 2 },    
        { name = "暴击率+65.0", data = 6500, type = 32 },
        { name = "防爆率+65.0", data = 6500, type = 33 },
        { name = "反弹率+10.0", data = 1000, type = 34 },
    },
    zsattr = {
        { name = "生命上限+5717105", data = 5717105, type = 1 },
        { name = "魔法上限+484355", data = 484355, type = 2 },
        { name = "暴击率+65.0", data = 6500, type = 32 },
        { name = "防爆率+65.0", data = 6500, type = 33 },
        { name = "反弹率+10.0", data = 1000, type = 34 },
    },
}

gdEvolutionCondition[0] = {id=0,afterlvl=35,maxlvl=70,reqgold=0,reqlvl=70,}
gdEvolutionCondition[1] = {id=1,afterlvl=35,maxlvl=70,reqgold=1000000,reqitem=1000,reqlvl=70,}
gdEvolutionCondition[2] = {id=2,afterlvl=35,maxlvl=70,reqgold=2000000,reqitem=2000,reqlvl=70,}
gdEvolutionCondition[3] = {id=3,afterlvl=35,maxlvl=70,reqgold=3000000,reqitem=3000,reqlvl=70,}
gdEvolutionCondition[4] = {id=4,afterlvl=35,maxlvl=70,reqgold=4000000,reqitem=4000,reqlvl=70,}
gdEvolutionCondition[5] = {id=5,afterlvl=35,maxlvl=75,reqgold=5000000,reqitem=5000,reqlvl=70,}
gdEvolutionCondition[6] = {id=6,afterlvl=35,maxlvl=75,reqgold=6000000,reqitem=6000,reqlvl=75,}
gdEvolutionCondition[7] = {id=7,afterlvl=35,maxlvl=75,reqgold=7000000,reqitem=7000,reqlvl=75,}
gdEvolutionCondition[8] = {id=8,afterlvl=35,maxlvl=75,reqgold=8000000,reqitem=8000,reqlvl=75,}
gdEvolutionCondition[9] = {id=9,afterlvl=35,maxlvl=75,reqgold=9000000,reqitem=9000,reqlvl=75,}
gdEvolutionCondition[10] = {id=10,afterlvl=35,maxlvl=80,reqgold=10000000,reqitem=10000,reqlvl=75,}
gdEvolutionCondition[11] = {id=11,afterlvl=35,maxlvl=80,reqgold=11000000,reqitem=11000,reqlvl=80,}
gdEvolutionCondition[12] = {id=12,afterlvl=35,maxlvl=80,reqgold=12000000,reqitem=12000,reqlvl=80,}
gdEvolutionCondition[13] = {id=13,afterlvl=35,maxlvl=80,reqgold=13000000,reqitem=13000,reqlvl=80,}
gdEvolutionCondition[14] = {id=14,afterlvl=35,maxlvl=80,reqgold=14000000,reqitem=14000,reqlvl=80,}
gdEvolutionCondition[15] = {id=15,afterlvl=35,maxlvl=85,reqgold=15000000,reqitem=15000,reqlvl=80,}
gdEvolutionCondition[16] = {id=16,afterlvl=35,maxlvl=85,reqgold=16000000,reqitem=16000,reqlvl=85,}
gdEvolutionCondition[17] = {id=17,afterlvl=35,maxlvl=85,reqgold=17000000,reqitem=17000,reqlvl=85,}
gdEvolutionCondition[18] = {id=18,afterlvl=35,maxlvl=85,reqgold=18000000,reqitem=18000,reqlvl=85,}
gdEvolutionCondition[19] = {id=19,afterlvl=35,maxlvl=85,reqgold=19000000,reqitem=19000,reqlvl=85,}
gdEvolutionCondition[20] = {id=20,afterlvl=35,maxlvl=90,reqgold=20000000,reqitem=20000,reqlvl=85,}
gdEvolutionCondition[21] = {id=21,afterlvl=35,maxlvl=90,reqgold=21000000,reqitem=21000,reqlvl=90,}
gdEvolutionCondition[22] = {id=22,afterlvl=35,maxlvl=90,reqgold=22000000,reqitem=22000,reqlvl=90,}
gdEvolutionCondition[23] = {id=23,afterlvl=35,maxlvl=90,reqgold=23000000,reqitem=23000,reqlvl=90,}
gdEvolutionCondition[24] = {id=24,afterlvl=35,maxlvl=90,reqgold=24000000,reqitem=24000,reqlvl=90,}
gdEvolutionCondition[25] = {id=25,afterlvl=35,maxlvl=95,reqgold=25000000,reqitem=25000,reqlvl=90,}
---------------------------------------------------------灵力-----------------------------------------------------
gdEvolutionCondition[26] = {id=26,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=1000,reqlvl=95,}
gdEvolutionCondition[27] = {id=27,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=2000,reqlvl=200,}
gdEvolutionCondition[28] = {id=28,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=3000,reqlvl=300,}
gdEvolutionCondition[29] = {id=29,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=4000,reqlvl=400,}
gdEvolutionCondition[30] = {id=30,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=5000,reqlvl=500,}
gdEvolutionCondition[31] = {id=31,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=6000,reqlvl=500,}
gdEvolutionCondition[32] = {id=32,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=7000,reqlvl=500,}
gdEvolutionCondition[33] = {id=33,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=8000,reqlvl=500,}
gdEvolutionCondition[34] = {id=34,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=9000,reqlvl=500,}
gdEvolutionCondition[35] = {id=35,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=10000,reqlvl=500,}
gdEvolutionCondition[36] = {id=36,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=11000,reqlvl=500,}
gdEvolutionCondition[37] = {id=37,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=12000,reqlvl=500,}
gdEvolutionCondition[38] = {id=38,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=13000,reqlvl=500,}
gdEvolutionCondition[39] = {id=39,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=14000,reqlvl=500,}
gdEvolutionCondition[40] = {id=40,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=15000,reqlvl=1000,}
gdEvolutionCondition[41] = {id=41,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=116000,reqlvl=1000,}
gdEvolutionCondition[42] = {id=42,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=117000,reqlvl=1000,}
gdEvolutionCondition[43] = {id=43,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=118000,reqlvl=1000,}
gdEvolutionCondition[44] = {id=44,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=119000,reqlvl=1000,}
gdEvolutionCondition[45] = {id=45,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=220000,reqlvl=1000,}
gdEvolutionCondition[46] = {id=46,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=221000,reqlvl=1000,}
gdEvolutionCondition[47] = {id=47,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=222000,reqlvl=1000,}
gdEvolutionCondition[48] = {id=48,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=223000,reqlvl=1000,}
gdEvolutionCondition[49] = {id=49,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=224000,reqlvl=1000,}
gdEvolutionCondition[50] = {id=50,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=225000,reqlvl=1000,}
gdEvolutionCondition[51] = {id=51,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=226000,reqlvl=1000,}
gdEvolutionCondition[52] = {id=52,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=227000,reqlvl=1000,}
gdEvolutionCondition[53] = {id=53,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=228000,reqlvl=1000,}
gdEvolutionCondition[54] = {id=54,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=229000,reqlvl=1000,}
gdEvolutionCondition[55] = {id=55,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=330000,reqlvl=1000,}
gdEvolutionCondition[56] = {id=56,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=331000,reqlvl=1000,}
gdEvolutionCondition[57] = {id=57,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=332000,reqlvl=1000,}
gdEvolutionCondition[58] = {id=58,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=333333,reqlvl=1000,}
gdEvolutionCondition[59] = {id=59,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=400000,reqlvl=1000,}
gdEvolutionCondition[60] = {id=60,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=500000,reqlvl=1000,}
gdEvolutionCondition[61] = {id=61,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=600000,reqlvl=1000,}
gdEvolutionCondition[62] = {id=62,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=700000,reqlvl=1000,}
gdEvolutionCondition[63] = {id=63,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=800000,reqlvl=1000,}
gdEvolutionCondition[64] = {id=64,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=900000,reqlvl=1000,}
gdEvolutionCondition[65] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=1000000,reqlvl=1000,}
--------------------------------------------------------------渡劫--------------------------------------------------------
gdEvolutionCondition[66] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=2000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[67] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=3000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[68] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=4000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[69] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=5000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[70] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=6000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[71] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=7000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[72] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=8000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[73] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=9000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[74] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=10000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[75] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=20000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[76] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=30000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[77] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=40000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[78] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=50000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[79] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=60000000,reqlvl=1000,needrobbery=1,}
gdEvolutionCondition[80] = {id=65,afterlvl=35,maxlvl=1000,reqgold=25000000,reqitem=8000,reqlingli=70000000,reqlvl=1000,needrobbery=1,}

gdSuitAttribute[1] = {
	id=1,
	name="八卦錾金套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+160",data=160,type=1,},
					attrstring="生命值上限+160",
				},
			[2]= {
					attr= {name="魔法值上限+117",data=117,type=2,},
					attrstring="魔法值上限+117",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+320",data=320,type=1,},
					attrstring="生命值上限+320",
				},
			[2]= {
					attr= {name="魔法值上限+234",data=234,type=2,},
					attrstring="魔法值上限+234",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+512",data=512,type=1,},
					attrstring="生命值上限+512",
				},
			[2]= {
					attr= {name="魔法值上限+374",data=374,type=2,},
					attrstring="魔法值上限+374",
				},
		},
}
gdSuitAttribute[2] = {
	id=2,
	name="光华若木套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+194",data=194,type=1,},
					attrstring="生命值上限+194",
				},
			[2]= {
					attr= {name="魔法值上限+147",data=147,type=2,},
					attrstring="魔法值上限+147",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+389",data=389,type=1,},
					attrstring="生命值上限+389",
				},
			[2]= {
					attr= {name="魔法值上限+294",data=294,type=2,},
					attrstring="魔法值上限+294",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+622",data=622,type=1,},
					attrstring="生命值上限+622",
				},
			[2]= {
					attr= {name="魔法值上限+471",data=471,type=2,},
					attrstring="魔法值上限+471",
				},
		},
}
gdSuitAttribute[3] = {
	id=3,
	name="九霄残月套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+232",data=232,type=1,},
					attrstring="生命值上限+232",
				},
			[2]= {
					attr= {name="魔法值上限+181",data=181,type=2,},
					attrstring="魔法值上限+181",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+464",data=464,type=1,},
					attrstring="生命值上限+464",
				},
			[2]= {
					attr= {name="魔法值上限+362",data=362,type=2,},
					attrstring="魔法值上限+362",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+743",data=743,type=1,},
					attrstring="生命值上限+743",
				},
			[2]= {
					attr= {name="魔法值上限+578",data=578,type=2,},
					attrstring="魔法值上限+578",
				},
		},
}
gdSuitAttribute[4] = {
	id=4,
	name="冥火薄天套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+273",data=273,type=1,},
					attrstring="生命值上限+273",
				},
			[2]= {
					attr= {name="魔法值上限+218",data=218,type=2,},
					attrstring="魔法值上限+218",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+547",data=547,type=1,},
					attrstring="生命值上限+547",
				},
			[2]= {
					attr= {name="魔法值上限+436",data=436,type=2,},
					attrstring="魔法值上限+436",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+875",data=875,type=1,},
					attrstring="生命值上限+875",
				},
			[2]= {
					attr= {name="魔法值上限+698",data=698,type=2,},
					attrstring="魔法值上限+698",
				},
		},
}
gdSuitAttribute[5] = {
	id=5,
	name="百鬼夜宴套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+318",data=318,type=1,},
					attrstring="生命值上限+318",
				},
			[2]= {
					attr= {name="魔法值上限+259",data=259,type=2,},
					attrstring="魔法值上限+259",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+636",data=636,type=1,},
					attrstring="生命值上限+636",
				},
			[2]= {
					attr= {name="魔法值上限+518",data=518,type=2,},
					attrstring="魔法值上限+518",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+1017",data=1017,type=1,},
					attrstring="生命值上限+1017",
				},
			[2]= {
					attr= {name="魔法值上限+828",data=828,type=2,},
					attrstring="魔法值上限+828",
				},
		},
}
gdSuitAttribute[6] = {
	id=6,
	name="太极逍遥套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+333",data=333,type=1,},
					attrstring="生命值上限+333",
				},
			[2]= {
					attr= {name="魔法值上限+332",data=332,type=2,},
					attrstring="魔法值上限+332",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+665",data=665,type=1,},
					attrstring="生命值上限+665",
				},
			[2]= {
					attr= {name="魔法值上限+663",data=663,type=2,},
					attrstring="魔法值上限+663",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+1064",data=1064,type=1,},
					attrstring="生命值上限+1064",
				},
			[2]= {
					attr= {name="魔法值上限+1061",data=1061,type=2,},
					attrstring="魔法值上限+1061",
				},
		},
}
gdSuitAttribute[7] = {
	id=7,
	name="星瀚幽路套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+232",data=232,type=1,},
					attrstring="生命值上限+232",
				},
			[2]= {
					attr= {name="魔法值上限+39",data=39,type=2,},
					attrstring="魔法值上限+39",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+464",data=464,type=1,},
					attrstring="生命值上限+464",
				},
			[2]= {
					attr= {name="魔法值上限+78",data=78,type=2,},
					attrstring="魔法值上限+78",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+743",data=743,type=1,},
					attrstring="生命值上限+743",
				},
			[2]= {
					attr= {name="魔法值上限+125",data=125,type=2,},
					attrstring="魔法值上限+125",
				},
		},
}
gdSuitAttribute[8] = {
	id=8,
	name="离情霜月套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+281",data=281,type=1,},
					attrstring="生命值上限+281",
				},
			[2]= {
					attr= {name="魔法值上限+43",data=43,type=2,},
					attrstring="魔法值上限+43",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+561",data=561,type=1,},
					attrstring="生命值上限+561",
				},
			[2]= {
					attr= {name="魔法值上限+87",data=87,type=2,},
					attrstring="魔法值上限+87",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+898",data=898,type=1,},
					attrstring="生命值上限+898",
				},
			[2]= {
					attr= {name="魔法值上限+139",data=139,type=2,},
					attrstring="魔法值上限+139",
				},
		},
}
gdSuitAttribute[9] = {
	id=9,
	name="浮犀焰阳套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+334",data=334,type=1,},
					attrstring="生命值上限+334",
				},
			[2]= {
					attr= {name="魔法值上限+48",data=48,type=2,},
					attrstring="魔法值上限+48",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+667",data=667,type=1,},
					attrstring="生命值上限+667",
				},
			[2]= {
					attr= {name="魔法值上限+96",data=96,type=2,},
					attrstring="魔法值上限+96",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+1068",data=1068,type=1,},
					attrstring="生命值上限+1068",
				},
			[2]= {
					attr= {name="魔法值上限+154",data=154,type=2,},
					attrstring="魔法值上限+154",
				},
		},
}
gdSuitAttribute[10] = {
	id=10,
	name="青虹北斗套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+391",data=391,type=1,},
					attrstring="生命值上限+391",
				},
			[2]= {
					attr= {name="魔法值上限+53",data=53,type=2,},
					attrstring="魔法值上限+53",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+783",data=783,type=1,},
					attrstring="生命值上限+783",
				},
			[2]= {
					attr= {name="魔法值上限+105",data=105,type=2,},
					attrstring="魔法值上限+105",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+1252",data=1252,type=1,},
					attrstring="生命值上限+1252",
				},
			[2]= {
					attr= {name="魔法值上限+168",data=168,type=2,},
					attrstring="魔法值上限+168",
				},
		},
}
gdSuitAttribute[11] = {
	id=11,
	name="天龙神锢套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+453",data=453,type=1,},
					attrstring="生命值上限+453",
				},
			[2]= {
					attr= {name="魔法值上限+57",data=57,type=2,},
					attrstring="魔法值上限+57",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+907",data=907,type=1,},
					attrstring="生命值上限+907",
				},
			[2]= {
					attr= {name="魔法值上限+114",data=114,type=2,},
					attrstring="魔法值上限+114",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+1451",data=1451,type=1,},
					attrstring="生命值上限+1451",
				},
			[2]= {
					attr= {name="魔法值上限+183",data=183,type=2,},
					attrstring="魔法值上限+183",
				},
		},
}
gdSuitAttribute[12] = {
	id=12,
	name="弑皇破天套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+595",data=595,type=1,},
					attrstring="生命值上限+595",
				},
			[2]= {
					attr= {name="魔法值上限+64",data=64,type=2,},
					attrstring="魔法值上限+64",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+1190",data=1190,type=1,},
					attrstring="生命值上限+1190",
				},
			[2]= {
					attr= {name="魔法值上限+129",data=129,type=2,},
					attrstring="魔法值上限+129",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+1903",data=1903,type=1,},
					attrstring="生命值上限+1903",
				},
			[2]= {
					attr= {name="魔法值上限+206",data=206,type=2,},
					attrstring="魔法值上限+206",
				},
		},
}
gdSuitAttribute[13] = {
	id=13,
	name="碎寂震天套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+87",data=87,type=1,},
					attrstring="生命值上限+87",
				},
			[2]= {
					attr= {name="魔法值上限+230",data=230,type=2,},
					attrstring="魔法值上限+230",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+174",data=174,type=1,},
					attrstring="生命值上限+174",
				},
			[2]= {
					attr= {name="魔法值上限+461",data=461,type=2,},
					attrstring="魔法值上限+461",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+278",data=278,type=1,},
					attrstring="生命值上限+278",
				},
			[2]= {
					attr= {name="魔法值上限+737",data=737,type=2,},
					attrstring="魔法值上限+737",
				},
		},
}
gdSuitAttribute[14] = {
	id=14,
	name="夜灵啸日套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+104",data=104,type=1,},
					attrstring="生命值上限+104",
				},
			[2]= {
					attr= {name="魔法值上限+284",data=284,type=2,},
					attrstring="魔法值上限+284",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+208",data=208,type=1,},
					attrstring="生命值上限+208",
				},
			[2]= {
					attr= {name="魔法值上限+569",data=569,type=2,},
					attrstring="魔法值上限+569",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+332",data=332,type=1,},
					attrstring="生命值上限+332",
				},
			[2]= {
					attr= {name="魔法值上限+910",data=910,type=2,},
					attrstring="魔法值上限+910",
				},
		},
}
gdSuitAttribute[15] = {
	id=15,
	name="雪蛊霜寒套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+122",data=122,type=1,},
					attrstring="生命值上限+122",
				},
			[2]= {
					attr= {name="魔法值上限+344",data=344,type=2,},
					attrstring="魔法值上限+344",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+244",data=244,type=1,},
					attrstring="生命值上限+244",
				},
			[2]= {
					attr= {name="魔法值上限+688",data=688,type=2,},
					attrstring="魔法值上限+688",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+391",data=391,type=1,},
					attrstring="生命值上限+391",
				},
			[2]= {
					attr= {name="魔法值上限+1101",data=1101,type=2,},
					attrstring="魔法值上限+1101",
				},
		},
}
gdSuitAttribute[16] = {
	id=16,
	name="无量沧海套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+142",data=142,type=1,},
					attrstring="生命值上限+142",
				},
			[2]= {
					attr= {name="魔法值上限+409",data=409,type=2,},
					attrstring="魔法值上限+409",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+284",data=284,type=1,},
					attrstring="生命值上限+284",
				},
			[2]= {
					attr= {name="魔法值上限+819",data=819,type=2,},
					attrstring="魔法值上限+819",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+455",data=455,type=1,},
					attrstring="生命值上限+455",
				},
			[2]= {
					attr= {name="魔法值上限+1310",data=1310,type=2,},
					attrstring="魔法值上限+1310",
				},
		},
}
gdSuitAttribute[17] = {
	id=17,
	name="五法青云套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+163",data=163,type=1,},
					attrstring="生命值上限+163",
				},
			[2]= {
					attr= {name="魔法值上限+480",data=480,type=2,},
					attrstring="魔法值上限+480",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+327",data=327,type=1,},
					attrstring="生命值上限+327",
				},
			[2]= {
					attr= {name="魔法值上限+961",data=961,type=2,},
					attrstring="魔法值上限+961",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+523",data=523,type=1,},
					attrstring="生命值上限+523",
				},
			[2]= {
					attr= {name="魔法值上限+1537",data=1537,type=2,},
					attrstring="魔法值上限+1537",
				},
		},
}
gdSuitAttribute[18] = {
	id=18,
	name="狂澜魄岳套装",
	suitcnt=8,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+155",data=155,type=1,},
					attrstring="生命值上限+155",
				},
			[2]= {
					attr= {name="魔法值上限+606",data=606,type=2,},
					attrstring="魔法值上限+606",
				},
		},
	[2]= {
			cnt=5,
			[1]= {
					attr= {name="生命值上限+310",data=310,type=1,},
					attrstring="生命值上限+310",
				},
			[2]= {
					attr= {name="魔法值上限+1211",data=1211,type=2,},
					attrstring="魔法值上限+1211",
				},
		},
	[3]= {
			cnt=8,
			[1]= {
					attr= {name="生命值上限+496",data=496,type=1,},
					attrstring="生命值上限+496",
				},
			[2]= {
					attr= {name="魔法值上限+1938",data=1938,type=2,},
					attrstring="魔法值上限+1938",
				},
		},
}
gdSuitAttribute[19] = {
	id=19,
	name="浑天磐龙套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+520",data=520,type=1,},
					attrstring="生命值上限+520",
				},
			[2]= {
					attr= {name="魔法值上限+557",data=557,type=2,},
					attrstring="魔法值上限+557",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+10",
							data=10,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+10",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+2%",
							data=200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+2%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+1040",data=1040,type=1,},
					attrstring="生命值上限+1040",
				},
			[2]= {
					attr= {name="魔法值上限+1114",data=1114,type=2,},
					attrstring="魔法值上限+1114",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+15",
							data=15,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+15",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+3%",
							data=300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+3%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+1664",data=1664,type=1,},
					attrstring="生命值上限+1664",
				},
			[2]= {
					attr= {name="魔法值上限+1782",data=1782,type=2,},
					attrstring="魔法值上限+1782",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+25",
							data=25,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+25",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+5%",
							data=500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+5%",
				},
		},
}
gdSuitAttribute[20] = {
	id=20,
	name="蚀日断魂套装",
	suitcnt=10,
	[1]= {
			cnt=10,
			[1]= {
					attr= {name="生命值上限+6000",data=6000,type=1,},
					attrstring="生命值上限+6000",
				},
			[2]= {
					attr= {name="魔法值上限+6000",data=6000,type=2,},
					attrstring="魔法值上限+6000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+75",
							data=75,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+75",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+15%",
							data=1500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+15%",
				},
		},
}
gdSuitAttribute[21] = {
	id=21,
	name="八卦錾金戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大道攻+5",data=5,type=10,},
					attrstring="最大道攻+5",
				},
		},
}
gdSuitAttribute[22] = {
	id=22,
	name="光华若木戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大道攻+8",data=8,type=10,},
					attrstring="最大道攻+8",
				},
		},
}
gdSuitAttribute[23] = {
	id=23,
	name="九霄残月戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大道攻+12",data=12,type=10,},
					attrstring="最大道攻+12",
				},
		},
}
gdSuitAttribute[24] = {
	id=24,
	name="冥火薄天戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大道攻+18",data=18,type=10,},
					attrstring="最大道攻+18",
				},
		},
}
gdSuitAttribute[25] = {
	id=25,
	name="百鬼夜宴戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大道攻+25",data=25,type=10,},
					attrstring="最大道攻+25",
				},
		},
}
gdSuitAttribute[26] = {
	id=26,
	name="太极逍遥戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大道攻+40",data=40,type=10,},
					attrstring="最大道攻+40",
				},
		},
}
gdSuitAttribute[27] = {
	id=27,
	name="星瀚幽路戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大物攻+5",data=5,type=6,},
					attrstring="最大物攻+5",
				},
		},
}
gdSuitAttribute[28] = {
	id=28,
	name="离情霜月戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大物攻+8",data=8,type=6,},
					attrstring="最大物攻+8",
				},
		},
}
gdSuitAttribute[29] = {
	id=29,
	name="浮犀焰阳戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大物攻+12",data=12,type=6,},
					attrstring="最大物攻+12",
				},
		},
}
gdSuitAttribute[30] = {
	id=30,
	name="青虹北斗戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大物攻+18",data=18,type=6,},
					attrstring="最大物攻+18",
				},
		},
}
gdSuitAttribute[31] = {
	id=31,
	name="天龙神锢戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大物攻+25",data=25,type=6,},
					attrstring="最大物攻+25",
				},
		},
}
gdSuitAttribute[32] = {
	id=32,
	name="弑皇破天戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大物攻+40",data=40,type=6,},
					attrstring="最大物攻+40",
				},
		},
}
gdSuitAttribute[33] = {
	id=33,
	name="碎寂震天戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大魔攻+5",data=5,type=8,},
					attrstring="最大魔攻+5",
				},
		},
}
gdSuitAttribute[34] = {
	id=34,
	name="夜灵啸日戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大魔攻+8",data=8,type=8,},
					attrstring="最大魔攻+8",
				},
		},
}
gdSuitAttribute[35] = {
	id=35,
	name="雪蛊霜寒戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大魔攻+12",data=12,type=8,},
					attrstring="最大魔攻+12",
				},
		},
}
gdSuitAttribute[36] = {
	id=36,
	name="无量沧海戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大魔攻+18",data=18,type=8,},
					attrstring="最大魔攻+18",
				},
		},
}
gdSuitAttribute[37] = {
	id=37,
	name="五法青云戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大魔攻+25",data=25,type=8,},
					attrstring="最大魔攻+25",
				},
		},
}
gdSuitAttribute[38] = {
	id=38,
	name="狂澜魄岳戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="最大魔攻+40",data=40,type=8,},
					attrstring="最大魔攻+40",
				},
		},
}
gdSuitAttribute[40] = {
	id=40,
	name="特殊戒指",
	suitcnt=2,
	[1]= {
			cnt=2,
			[1]= {
					attr= {name="魔法闪避+30%",data=3000,type=20,},
					attrstring="魔法闪避+30%",
				},
		},
}
gdSuitAttribute[41] = {
	id=41,
	name="绝世武神套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+696",data=696,type=1,},
					attrstring="生命值上限+696",
				},
			[2]= {
					attr= {name="魔法值上限+711",data=711,type=2,},
					attrstring="魔法值上限+711",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+12",
							data=12,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+12",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+3%",
							data=300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+3%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+1453",data=1453,type=1,},
					attrstring="生命值上限+1453",
				},
			[2]= {
					attr= {name="魔法值上限+1473",data=1473,type=2,},
					attrstring="魔法值上限+1473",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+18",
							data=18,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+18",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+5%",
							data=500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+5%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+2364",data=2364,type=1,},
					attrstring="生命值上限+2364",
				},
			[2]= {
					attr= {name="魔法值上限+2412",data=2412,type=2,},
					attrstring="魔法值上限+2412",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+30",
							data=30,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+30",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+7%",
							data=700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+7%",
				},
		},
}
gdSuitAttribute[44] = {
	id=44,
	name="极·浑天磐龙套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+676",data=676,type=1,},
					attrstring="生命值上限+676",
				},
			[2]= {
					attr= {name="魔法值上限+691",data=691,type=2,},
					attrstring="魔法值上限+691",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+10",
							data=10,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+10",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+2%",
							data=200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+2%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+1353",data=1353,type=1,},
					attrstring="生命值上限+1353",
				},
			[2]= {
					attr= {name="魔法值上限+1383",data=1383,type=2,},
					attrstring="魔法值上限+1383",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+15",
							data=15,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+15",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+3%",
							data=300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+3%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+2164",data=2164,type=1,},
					attrstring="生命值上限+2164",
				},
			[2]= {
					attr= {name="魔法值上限+2212",data=2212,type=2,},
					attrstring="魔法值上限+2212",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+25",
							data=25,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+25",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+5%",
							data=500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+5%",
				},
		},
}
--------------------------------------------------------------------------------------------------



--战士3
gdSuitAttribute[45] = {
	id=45,
	name="浮犀焰阳套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+1018",data=1018,type=1,},
					attrstring="生命值上限+1018",
				},
			[2]= {
					attr= {name="魔法值上限+127",data=127,type=2,},
					attrstring="魔法值上限+127",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+22",
							data=22,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+22",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+5",
							data=500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+5%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+2040",data=2040,type=1,},
					attrstring="生命值上限+2040",
				},
			[2]= {
					attr= {name="魔法值上限+256",data=256,type=2,},
					attrstring="魔法值上限+256",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+112",
							data=112,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+112",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+6%",
							data=600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+6%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+3264",data=3264,type=1,},
					attrstring="生命值上限+3264",
				},
			[2]= {
					attr= {name="魔法值上限+411",data=411,type=2,},
					attrstring="魔法值上限+411",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+225",
							data=225,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+225",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+7%",
							data=700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+7%",
				},
		},
}
--战士4
gdSuitAttribute[46] = {
	id=46,
	name="青虹北斗套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+1527",data=1527,type=1,},
					attrstring="生命值上限+1527",
				},
			[2]= {
					attr= {name="魔法值上限+190",data=190,type=2,},
					attrstring="魔法值上限+190",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+33",
							data=33,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+33",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+7",
							data=700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+7%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+3060",data=3060,type=1,},
					attrstring="生命值上限+3060",
				},
			[2]= {
					attr= {name="魔法值上限+384",data=384,type=2,},
					attrstring="魔法值上限+384",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+168",
							data=168,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+168",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+8%",
							data=800,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+8%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+4896",data=4896,type=1,},
					attrstring="生命值上限+4896",
				},
			[2]= {
					attr= {name="魔法值上限+616",data=616,type=2,},
					attrstring="魔法值上限+616",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+337",
							data=337,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+337",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+9%",
							data=900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+9%",
				},
		},
}
--战士5
gdSuitAttribute[47] = {
	id=47,
	name="天龙神锢套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+2290",data=2290,type=1,},
					attrstring="生命值上限+2290",
				},
			[2]= {
					attr= {name="魔法值上限+285",data=285,type=2,},
					attrstring="魔法值上限+285",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+49",
							data=49,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+49",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+9",
							data=900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+9%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+4590",data=4590,type=1,},
					attrstring="生命值上限+4590",
				},
			[2]= {
					attr= {name="魔法值上限+576",data=576,type=2,},
					attrstring="魔法值上限+576",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+252",
							data=252,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+252",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+10%",
							data=1000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+10%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+7344",data=7344,type=1,},
					attrstring="生命值上限+7344",
				},
			[2]= {
					attr= {name="魔法值上限+924",data=924,type=2,},
					attrstring="魔法值上限+924",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+505",
							data=505,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+505",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+11%",
							data=1100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+11%",
				},
		},
}
--战士6
gdSuitAttribute[48] = {
	id=48,
	name="弑皇破天套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+3435",data=3435,type=1,},
					attrstring="生命值上限+3435",
				},
			[2]= {
					attr= {name="魔法值上限+427",data=427,type=2,},
					attrstring="魔法值上限+427",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+73",
							data=73,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+73",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+11",
							data=1100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+11%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+6885",data=6885,type=1,},
					attrstring="生命值上限+6885",
				},
			[2]= {
					attr= {name="魔法值上限+864",data=864,type=2,},
					attrstring="魔法值上限+864",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+378",
							data=378,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+378",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+12%",
							data=1200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+12%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+11016",data=11016,type=1,},
					attrstring="生命值上限+11016",
				},
			[2]= {
					attr= {name="魔法值上限+1386",data=1386,type=2,},
					attrstring="魔法值上限+1386",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+757",
							data=757,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+757",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+13%",
							data=1300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+13%",
				},
		},
}
--战士7
gdSuitAttribute[49] = {
	id=49,
	name="浑天嗜魂套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+5152",data=5152,type=1,},
					attrstring="生命值上限+5152",
				},
			[2]= {
					attr= {name="魔法值上限+640",data=640,type=2,},
					attrstring="魔法值上限+640",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+109",
							data=109,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+109",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+13",
							data=1300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+13%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+10327",data=10327,type=1,},
					attrstring="生命值上限+10327",
				},
			[2]= {
					attr= {name="魔法值上限+1296",data=1296,type=2,},
					attrstring="魔法值上限+1296",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+567",
							data=567,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+567",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+14%",
							data=1400,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+14%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+16524",data=16524,type=1,},
					attrstring="生命值上限+16524",
				},
			[2]= {
					attr= {name="魔法值上限+2079",data=2079,type=2,},
					attrstring="魔法值上限+2079",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1135",
							data=1135,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1135",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+15%",
							data=1500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+15%",
				},
		},
}
--战士8
gdSuitAttribute[50] = {
	id=50,
	name="浑天嗜魂套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+7728",data=7728,type=1,},
					attrstring="生命值上限+7728",
				},
			[2]= {
					attr= {name="魔法值上限+960",data=960,type=2,},
					attrstring="魔法值上限+960",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+163",
							data=163,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+109",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+15",
							data=1500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+15%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+15490",data=15490,type=1,},
					attrstring="生命值上限+15490",
				},
			[2]= {
					attr= {name="魔法值上限+1944",data=1944,type=2,},
					attrstring="魔法值上限+1944",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+850",
							data=850,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+850",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+16%",
							data=1600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+16%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+24786",data=24786,type=1,},
					attrstring="生命值上限+24786",
				},
			[2]= {
					attr= {name="魔法值上限+3118",data=3118,type=2,},
					attrstring="魔法值上限+3118",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1702",
							data=1702,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1702",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+17%",
							data=1700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+17%",
				},
		},
}
--战士9
gdSuitAttribute[51] = {
	id=51,
	name="浑天嗜魂套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+11592",data=11592,type=1,},
					attrstring="生命值上限+11592",
				},
			[2]= {
					attr= {name="魔法值上限+1440",data=1440,type=2,},
					attrstring="魔法值上限+1440",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+244",
							data=244,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+244",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+17",
							data=1700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+17%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+23235",data=23235,type=1,},
					attrstring="生命值上限+23235",
				},
			[2]= {
					attr= {name="魔法值上限+2916",data=2916,type=2,},
					attrstring="魔法值上限+2916",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1275",
							data=1275,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1275",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+18%",
							data=1800,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+18%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+37179",data=37179,type=1,},
					attrstring="生命值上限+37179",
				},
			[2]= {
					attr= {name="魔法值上限+4677",data=4677,type=2,},
					attrstring="魔法值上限+4677",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2553",
							data=2553,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2553",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+19%",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
}
--战士10
gdSuitAttribute[52] = {
	id=52,
	name="浑天嗜魂套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+17388",data=17388,type=1,},
					attrstring="生命值上限+17388",
				},
			[2]= {
					attr= {name="魔法值上限+2160",data=2160,type=2,},
					attrstring="魔法值上限+2160",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+366",
							data=366,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+366",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+19",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+34852",data=34852,type=1,},
					attrstring="生命值上限+34852",
				},
			[2]= {
					attr= {name="魔法值上限+4374",data=4374,type=2,},
					attrstring="魔法值上限+4374",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1912",
							data=1912,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1912",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+20%",
							data=2000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+20%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+55768",data=55768,type=1,},
					attrstring="生命值上限+55768",
				},
			[2]= {
					attr= {name="魔法值上限+7015",data=7015,type=2,},
					attrstring="魔法值上限+7015",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+3829",
							data=3829,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+3829",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+21%",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
}
--战士11
gdSuitAttribute[53] = {
	id=53,
	name="浑天嗜魂套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+26082",data=26082,type=1,},
					attrstring="生命值上限+26082",
				},
			[2]= {
					attr= {name="魔法值上限+3240",data=3240,type=2,},
					attrstring="魔法值上限+3240",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+549",
							data=549,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+549",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+21",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+52278",data=52278,type=1,},
					attrstring="生命值上限+52278",
				},
			[2]= {
					attr= {name="魔法值上限+6561",data=6561,type=2,},
					attrstring="魔法值上限+6561",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2868",
							data=2868,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2868",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+22%",
							data=2200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+22%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+83652",data=83652,type=1,},
					attrstring="生命值上限+83652",
				},
			[2]= {
					attr= {name="魔法值上限+10522",data=10522,type=2,},
					attrstring="魔法值上限+10522",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+5743",
							data=5743,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+5743",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+23%",
							data=2300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+23%",
				},
		},
}
--------------------------------------------------------------------------------
---法师3
gdSuitAttribute[54] = {
	id=54,
	name="雪蛊霜寒套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+366",data=366,type=1,},
					attrstring="生命值上限+366",
				},
			[2]= {
					attr= {name="魔法值上限+1080",data=1080,type=2,},
					attrstring="魔法值上限+1080",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+22",
							data=22,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+22",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+5",
							data=500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+5%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+735",data=735,type=1,},
					attrstring="生命值上限+735",
				},
			[2]= {
					attr= {name="魔法值上限+2161",data=2161,type=2,},
					attrstring="魔法值上限+2161",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+112",
							data=112,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+112",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+6%",
							data=600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+6%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+1176",data=1176,type=1,},
					attrstring="生命值上限+1176",
				},
			[2]= {
					attr= {name="魔法值上限+3457",data=3457,type=2,},
					attrstring="魔法值上限+3457",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+225",
							data=225,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+225",
				},
			[4]= {
					attr= {
							name="魂石最大攻击7%",
							data=700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+7%",
				},
		},
}
---法师4
gdSuitAttribute[55] = {
	id=55,
	name="无量沧海套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+549",data=549,type=1,},
					attrstring="生命值上限+549",
				},
			[2]= {
					attr= {name="魔法值上限+1620",data=1620,type=2,},
					attrstring="魔法值上限+1620",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+33",
							data=33,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+33",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+7",
							data=700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+7%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+1102",data=1102,type=1,},
					attrstring="生命值上限+1102",
				},
			[2]= {
					attr= {name="魔法值上限+3241",data=3241,type=2,},
					attrstring="魔法值上限+3241",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+168",
							data=168,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+168",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+8",
							data=800,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+8%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+1764",data=1764,type=1,},
					attrstring="生命值上限+1764",
				},
			[2]= {
					attr= {name="魔法值上限+5185",data=5185,type=2,},
					attrstring="魔法值上限+5185",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+337",
							data=337,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+337",
				},
			[4]= {
					attr= {
							name="魂石最大攻击9%",
							data=900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+9%",
				},
		},
}
---法师5
gdSuitAttribute[56] = {
	id=56,
	name="五法青云套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+823",data=823,type=1,},
					attrstring="生命值上限+823",
				},
			[2]= {
					attr= {name="魔法值上限+2430",data=2430,type=2,},
					attrstring="魔法值上限+2430",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+49",
							data=49,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+49",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+9",
							data=900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+9%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+1653",data=1653,type=1,},
					attrstring="生命值上限+1653",
				},
			[2]= {
					attr= {name="魔法值上限+4861",data=4861,type=2,},
					attrstring="魔法值上限+4861",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+252",
							data=252,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+252",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+10",
							data=1000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+10%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+2646",data=2646,type=1,},
					attrstring="生命值上限+2646",
				},
			[2]= {
					attr= {name="魔法值上限+7777",data=7777,type=2,},
					attrstring="魔法值上限+7777",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+505",
							data=505,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+505",
				},
			[4]= {
					attr= {
							name="魂石最大攻击11%",
							data=1100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+11%",
				},
		},
}
---法师6
gdSuitAttribute[57] = {
	id=57,
	name="狂澜魄岳套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+1234",data=1234,type=1,},
					attrstring="生命值上限+1234",
				},
			[2]= {
					attr= {name="魔法值上限+3645",data=3645,type=2,},
					attrstring="魔法值上限+3645",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+73",
							data=73,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+73",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+11",
							data=1100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+11%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+2479",data=2479,type=1,},
					attrstring="生命值上限+2479",
				},
			[2]= {
					attr= {name="魔法值上限+7291",data=7291,type=2,},
					attrstring="魔法值上限+7291",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+378",
							data=378,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+378",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+12",
							data=1200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+12%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+3969",data=3969,type=1,},
					attrstring="生命值上限+3969",
				},
			[2]= {
					attr= {name="魔法值上限+11665",data=11665,type=2,},
					attrstring="魔法值上限+11665",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+757",
							data=757,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+757",
				},
			[4]= {
					attr= {
							name="魂石最大攻击13%",
							data=1300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+13%",
				},
		},
}
---法师7
gdSuitAttribute[58] = {
	id=58,
	name="浑天命运套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+1851",data=1851,type=1,},
					attrstring="生命值上限+1851",
				},
			[2]= {
					attr= {name="魔法值上限+5467",data=5467,type=2,},
					attrstring="魔法值上限+5467",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+109",
							data=109,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+109",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+13",
							data=1300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+13%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+3718",data=3718,type=1,},
					attrstring="生命值上限+3718",
				},
			[2]= {
					attr= {name="魔法值上限+10936",data=10936,type=2,},
					attrstring="魔法值上限+10936",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+567",
							data=567,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+567",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+14",
							data=1400,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+14%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+5953",data=5953,type=1,},
					attrstring="生命值上限+5953",
				},
			[2]= {
					attr= {name="魔法值上限+17497",data=17497,type=2,},
					attrstring="魔法值上限+17497",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1135",
							data=1135,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1135",
				},
			[4]= {
					attr= {
							name="魂石最大攻击15%",
							data=1500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+15%",
				},
		},
}
---法师8
gdSuitAttribute[59] = {
	id=59,
	name="浑天命运套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+2776",data=2776,type=1,},
					attrstring="生命值上限+2776",
				},
			[2]= {
					attr= {name="魔法值上限+8200",data=8200,type=2,},
					attrstring="魔法值上限+8200",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+163",
							data=163,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+163",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+15",
							data=1500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+15%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+5577",data=5577,type=1,},
					attrstring="生命值上限+5577",
				},
			[2]= {
					attr= {name="魔法值上限+16404",data=16404,type=2,},
					attrstring="魔法值上限+16404",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+750",
							data=750,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+750",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+16",
							data=1600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+16%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+8929",data=8929,type=1,},
					attrstring="生命值上限+8929",
				},
			[2]= {
					attr= {name="魔法值上限+26245",data=26245,type=2,},
					attrstring="魔法值上限+26245",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1702",
							data=1702,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1702",
				},
			[4]= {
					attr= {
							name="魂石最大攻击17%",
							data=1700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+17%",
				},
		},
}
---法师9
gdSuitAttribute[60] = {
	id=60,
	name="浑天命运套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+4164",data=4164,type=1,},
					attrstring="生命值上限+4164",
				},
			[2]= {
					attr= {name="魔法值上限+12300",data=12300,type=2,},
					attrstring="魔法值上限+12300",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+244",
							data=244,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+244",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+17",
							data=1700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+17%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+8365",data=8365,type=1,},
					attrstring="生命值上限+8365",
				},
			[2]= {
					attr= {name="魔法值上限+24606",data=24606,type=2,},
					attrstring="魔法值上限+24606",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1125",
							data=1125,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1125",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+18",
							data=1800,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+18%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+13393",data=13393,type=1,},
					attrstring="生命值上限+13393",
				},
			[2]= {
					attr= {name="魔法值上限+39367",data=39367,type=2,},
					attrstring="魔法值上限+39367",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2553",
							data=2553,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2553",
				},
			[4]= {
					attr= {
							name="魂石最大攻击19%",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
}
---法师10
gdSuitAttribute[61] = {
	id=61,
	name="浑天命运套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+6246",data=6246,type=1,},
					attrstring="生命值上限+6246",
				},
			[2]= {
					attr= {name="魔法值上限+18450",data=18450,type=2,},
					attrstring="魔法值上限+18450",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+366",
							data=366,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+366",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+19",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+12547",data=12547,type=1,},
					attrstring="生命值上限+12547",
				},
			[2]= {
					attr= {name="魔法值上限+36909",data=36909,type=2,},
					attrstring="魔法值上限+36909",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1687",
							data=1687,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1687",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+20",
							data=2000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+20%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+13393",data=13393,type=1,},
					attrstring="生命值上限+13393",
				},
			[2]= {
					attr= {name="魔法值上限+59050",data=59050,type=2,},
					attrstring="魔法值上限+59050",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+3829",
							data=3829,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+3829",
				},
			[4]= {
					attr= {
							name="魂石最大攻击21%",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
}
---法师11
gdSuitAttribute[62] = {
	id=62,
	name="浑天命运套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+9369",data=9369,type=1,},
					attrstring="生命值上限+9369",
				},
			[2]= {
					attr= {name="魔法值上限+27675",data=27675,type=2,},
					attrstring="魔法值上限+27675",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+549",
							data=549,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+549",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+21",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+18820",data=18820,type=1,},
					attrstring="生命值上限+18820",
				},
			[2]= {
					attr= {name="魔法值上限+55363",data=55363,type=2,},
					attrstring="魔法值上限+55363",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2530",
							data=2530,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2530",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+22%",
							data=2200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+22%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+20089",data=20089,type=1,},
					attrstring="生命值上限+20089",
				},
			[2]= {
					attr= {name="魔法值上限+88575",data=88575,type=2,},
					attrstring="魔法值上限+88575",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+5743",
							data=5743,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+5743",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+23%",
							data=2300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+23%",
				},
		},
}
--------------------------------------------------------------------------------------------------
----道士3
gdSuitAttribute[63] = {
	id=63,
	name="九霄残月套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+715",data=715,type=1,},
					attrstring="生命值上限+715",
				},
			[2]= {
					attr= {name="魔法值上限+582",data=582,type=2,},
					attrstring="魔法值上限+582",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+22",
							data=22,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+22",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+5",
							data=500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+5%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+1431",data=1431,type=1,},
					attrstring="生命值上限+1431",
				},
			[2]= {
					attr= {name="魔法值上限+1165",data=1165,type=2,},
					attrstring="魔法值上限+1165",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+112",
							data=112,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+112",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+6%",
							data=600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+6%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+2287",data=2287,type=1,},
					attrstring="生命值上限+2287",
				},
			[2]= {
					attr= {name="魔法值上限+1863",data=1863,type=2,},
					attrstring="魔法值上限+1863",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+225",
							data=225,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+225",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+7%",
							data=700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+7%",
				},
		},
}
----道士4
gdSuitAttribute[64] = {
	id=64,
	name="冥火薄天套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+1072",data=1072,type=1,},
					attrstring="生命值上限+1072",
				},
			[2]= {
					attr= {name="魔法值上限+873",data=873,type=2,},
					attrstring="魔法值上限+873",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+33",
							data=33,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+33",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+7",
							data=700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+7%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+2146",data=2146,type=1,},
					attrstring="生命值上限+2146",
				},
			[2]= {
					attr= {name="魔法值上限+1747",data=1747,type=2,},
					attrstring="魔法值上限+1747",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+168",
							data=168,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+168",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+8%",
							data=800,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+8%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+3430",data=3430,type=1,},
					attrstring="生命值上限+3430",
				},
			[2]= {
					attr= {name="魔法值上限+1094",data=1094,type=2,},
					attrstring="魔法值上限+1094",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+337",
							data=337,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+337",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+9%",
							data=900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+9%",
				},
		},
}
----道士5
gdSuitAttribute[65] = {
	id=65,
	name="百鬼夜宴套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+1608",data=1608,type=1,},
					attrstring="生命值上限+1608",
				},
			[2]= {
					attr= {name="魔法值上限+1309",data=1309,type=2,},
					attrstring="魔法值上限+1309",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+49",
							data=49,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+49",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+9",
							data=900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+9%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+3219",data=3219,type=1,},
					attrstring="生命值上限+3219",
				},
			[2]= {
					attr= {name="魔法值上限+1641",data=1641,type=2,},
					attrstring="魔法值上限+1641",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+252",
							data=252,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+252",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+10%",
							data=1000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+10%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+5145",data=5145,type=1,},
					attrstring="生命值上限+5145",
				},
			[2]= {
					attr= {name="魔法值上限+1641",data=1641,type=2,},
					attrstring="魔法值上限+1641",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+505",
							data=505,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+505",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+11%",
							data=1100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+11%",
				},
		},
}
----道士6
gdSuitAttribute[66] = {
	id=66,
	name="太极逍遥套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+2412",data=2412,type=1,},
					attrstring="生命值上限+2412",
				},
			[2]= {
					attr= {name="魔法值上限+1963",data=1963,type=2,},
					attrstring="魔法值上限+1963",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+73",
							data=73,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+73",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+11",
							data=1100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+11%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+4828",data=4828,type=1,},
					attrstring="生命值上限+4828",
				},
			[2]= {
					attr= {name="魔法值上限+2461",data=2461,type=2,},
					attrstring="魔法值上限+2461",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+567",
							data=567,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+567",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+12%",
							data=1200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+12%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+11575",data=11575,type=1,},
					attrstring="生命值上限+11575",
				},
			[2]= {
					attr= {name="魔法值上限+3691",data=3691,type=2,},
					attrstring="魔法值上限+3691",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+757",
							data=757,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+757",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+13%",
							data=1300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+11%",
				},
		},
}
----道士7
gdSuitAttribute[67] = {
	id=67,
	name="浑天逍遥套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+3618",data=3618,type=1,},
					attrstring="生命值上限+3618",
				},
			[2]= {
					attr= {name="魔法值上限+2944",data=2944,type=2,},
					attrstring="魔法值上限+2944",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+109",
							data=109,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+109",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+13",
							data=1300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+13%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+7242",data=7242,type=1,},
					attrstring="生命值上限+7242",
				},
			[2]= {
					attr= {name="魔法值上限+3691",data=3691,type=2,},
					attrstring="魔法值上限+3691",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+850",
							data=850,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1275",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+14%",
							data=1400,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+14%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+17362",data=17362,type=1,},
					attrstring="生命值上限+17362",
				},
			[2]= {
					attr= {name="魔法值上限+5536",data=5536,type=2,},
					attrstring="魔法值上限+5536",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1135",
							data=1135,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1702",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+15%",
							data=1500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+15%",
				},
		},
}
----道士8
gdSuitAttribute[68] = {
	id=68,
	name="浑天逍遥套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+5427",data=5427,type=1,},
					attrstring="生命值上限+5427",
				},
			[2]= {
					attr= {name="魔法值上限+4416",data=4416,type=2,},
					attrstring="魔法值上限+4416",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+163",
							data=109,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+109",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+15",
							data=1500,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+15%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+10863",data=10863,type=1,},
					attrstring="生命值上限+10863",
				},
			[2]= {
					attr= {name="魔法值上限+5536",data=5536,type=2,},
					attrstring="魔法值上限+5536",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1275",
							data=1275,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1275",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+16%",
							data=1600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+16%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+26043",data=26043,type=1,},
					attrstring="生命值上限+26043",
				},
			[2]= {
					attr= {name="魔法值上限+8304",data=8304,type=2,},
					attrstring="魔法值上限+8304",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1702",
							data=1702,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1702",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+17%",
							data=1700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+17%",
				},
		},
}
----道士9
gdSuitAttribute[69] = {
	id=69,
	name="浑天逍遥套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+8140",data=8140,type=1,},
					attrstring="生命值上限+8140",
				},
			[2]= {
					attr= {name="魔法值上限+6624",data=6624,type=2,},
					attrstring="魔法值上限+6624",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+244",
							data=244,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+244",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+17",
							data=1700,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+17%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+16294",data=16294,type=1,},
					attrstring="生命值上限+16294",
				},
			[2]= {
					attr= {name="魔法值上限+8304",data=8304,type=2,},
					attrstring="魔法值上限+8304",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1912",
							data=1912,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1912",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+18%",
							data=1800,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+18%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+39064",data=39064,type=1,},
					attrstring="生命值上限+39064",
				},
			[2]= {
					attr= {name="魔法值上限+12456",data=12456,type=2,},
					attrstring="魔法值上限+12456",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2553",
							data=2553,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2553",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+19%",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
}
---道士10
gdSuitAttribute[70] = {
	id=70,
	name="浑天命运套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+6246",data=6246,type=1,},
					attrstring="生命值上限+6246",
				},
			[2]= {
					attr= {name="魔法值上限+18450",data=18450,type=2,},
					attrstring="魔法值上限+18450",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+366",
							data=366,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+366",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+19",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+12547",data=12547,type=1,},
					attrstring="生命值上限+12547",
				},
			[2]= {
					attr= {name="魔法值上限+36909",data=36909,type=2,},
					attrstring="魔法值上限+36909",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1687",
							data=1687,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1687",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+20",
							data=2000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+20%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+13393",data=13393,type=1,},
					attrstring="生命值上限+13393",
				},
			[2]= {
					attr= {name="魔法值上限+59050",data=59050,type=2,},
					attrstring="魔法值上限+59050",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+3829",
							data=3829,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+3829",
				},
			[4]= {
					attr= {
							name="魂石最大攻击21%",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
}
----道士11
gdSuitAttribute[71] = {
	id=71,
	name="浑天逍遥套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+12210",data=12210,type=1,},
					attrstring="生命值上限+12210",
				},
			[2]= {
					attr= {name="魔法值上限+9936",data=9936,type=2,},
					attrstring="魔法值上限+9936",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+366",
							data=366,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+366",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+19%",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+24441",data=24441,type=1,},
					attrstring="生命值上限+24441",
				},
			[2]= {
					attr= {name="魔法值上限+12456",data=12456,type=2,},
					attrstring="魔法值上限+12456",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2868",
							data=2868,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2868",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+20%",
							data=2000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+20%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+58596",data=58596,type=1,},
					attrstring="生命值上限+58596",
				},
			[2]= {
					attr= {name="魔法值上限+18684",data=18684,type=2,},
					attrstring="魔法值上限+18684",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+3829",
							data=3829,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2553",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+21%",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
}
----道士暗影猩红套
gdSuitAttribute[72] = {
	id=72,
	name="暗影猩红套",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+12210",data=12210,type=1,},
					attrstring="生命值上限+12210",
				},
			[2]= {
					attr= {name="魔法值上限+9936",data=9936,type=2,},
					attrstring="魔法值上限+9936",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+366",
							data=366,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+366",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+19%",
							data=1900,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+19%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+24441",data=24441,type=1,},
					attrstring="生命值上限+24441",
				},
			[2]= {
					attr= {name="魔法值上限+12456",data=12456,type=2,},
					attrstring="魔法值上限+12456",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2868",
							data=2868,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2868",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+20%",
							data=2000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+20%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+58596",data=58596,type=1,},
					attrstring="生命值上限+58596",
				},
			[2]= {
					attr= {name="魔法值上限+18684",data=18684,type=2,},
					attrstring="魔法值上限+18684",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+3829",
							data=3829,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2553",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+21%",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
}
--战士暗影猩红套
gdSuitAttribute[73] = {
	id=73,
	name="浑天嗜魂套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+26082",data=26082,type=1,},
					attrstring="生命值上限+26082",
				},
			[2]= {
					attr= {name="魔法值上限+3240",data=3240,type=2,},
					attrstring="魔法值上限+3240",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+549",
							data=549,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+549",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+21",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+52278",data=52278,type=1,},
					attrstring="生命值上限+52278",
				},
			[2]= {
					attr= {name="魔法值上限+6561",data=6561,type=2,},
					attrstring="魔法值上限+6561",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2868",
							data=2868,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2868",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+22%",
							data=2200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+22%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+83652",data=83652,type=1,},
					attrstring="生命值上限+83652",
				},
			[2]= {
					attr= {name="魔法值上限+10522",data=10522,type=2,},
					attrstring="魔法值上限+10522",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+5743",
							data=5743,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+5743",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+23%",
							data=2300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+23%",
				},
		},
}
---法师暗影猩蓝套
gdSuitAttribute[74] = {
	id=74,
	name="浑天命运套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+9369",data=9369,type=1,},
					attrstring="生命值上限+9369",
				},
			[2]= {
					attr= {name="魔法值上限+27675",data=27675,type=2,},
					attrstring="魔法值上限+27675",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+549",
							data=549,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+549",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+21",
							data=2100,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+21%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+18820",data=18820,type=1,},
					attrstring="生命值上限+18820",
				},
			[2]= {
					attr= {name="魔法值上限+55363",data=55363,type=2,},
					attrstring="魔法值上限+55363",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+2530",
							data=2530,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+2530",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+22%",
							data=2200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+22%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+20089",data=20089,type=1,},
					attrstring="生命值上限+20089",
				},
			[2]= {
					attr= {name="魔法值上限+88575",data=88575,type=2,},
					attrstring="魔法值上限+88575",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+5743",
							data=5743,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+5743",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+23%",
							data=2300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+23%",
				},
		},
}

-------------------------------------------------神器套--------------------------------------------
------------------神器套装1
gdSuitAttribute[100] = {
	id=100,
	name="神器套装一",
	suitcnt=6,
	[1]= {
			cnt=6,
           [1]= {
					attr= {name="生命值上限+1000",data=1000,type=1,},
					attrstring="生命值上限+1000",
				},
			[2]= {
					attr= {name="魔法值上限+1000",data=1000,type=2,},
					attrstring="魔法值上限+1000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+10",
							data=10,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+10",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+2%",
							data=200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+2%",
				},
		},
}
------------------神器套装2
gdSuitAttribute[101] = {
	id=101,
	name="神器套装二",
	suitcnt=6,
	[1]= {
			cnt=6,
           [1]= {
					attr= {name="生命值上限+2000",data=2000,type=1,},
					attrstring="生命值上限+2000",
				},
			[2]= {
					attr= {name="魔法值上限+2000",data=2000,type=2,},
					attrstring="魔法值上限+2000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+20",
							data=20,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+20",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+4%",
							data=400,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+4%",
				},
		},
}
------------------神器套装3
gdSuitAttribute[102] = {
	id=102,
	name="神器套装三",
	suitcnt=6,
	[1]= {
			cnt=6,
           [1]= {
					attr= {name="生命值上限+4000",data=4000,type=1,},
					attrstring="生命值上限+4000",
				},
			[2]= {
					attr= {name="魔法值上限+4000",data=4000,type=2,},
					attrstring="魔法值上限+4000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+40",
							data=40,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+40",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+6%",
							data=600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+6%",
				},
		},
}
------------------神器套装4
gdSuitAttribute[103] = {
	id=103,
	name="神器套装四",
	suitcnt=6,
	[1]= {
			cnt=6,
           [1]= {
					attr= {name="生命值上限+8000",data=8000,type=1,},
					attrstring="生命值上限+8000",
				},
			[2]= {
					attr= {name="魔法值上限+8000",data=8000,type=2,},
					attrstring="魔法值上限+8000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+80",
							data=80,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+80",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+8%",
							data=800,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+8%",
				},
		},
}
------------------神器套装5
gdSuitAttribute[104] = {
	id=104,
	name="神器套装五",
	suitcnt=6,
	[1]= {
			cnt=6,
           [1]= {
					attr= {name="生命值上限+16000",data=16000,type=1,},
					attrstring="生命值上限+16000",
				},
			[2]= {
					attr= {name="魔法值上限+16000",data=16000,type=2,},
					attrstring="魔法值上限+16000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+160",
							data=160,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+160",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+16%",
							data=1600,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+16%",
				},
		},
}
------------------神器套装6
gdSuitAttribute[105] = {
	id=105,
	name="神器套装六",
	suitcnt=6,
	[1]= {
			cnt=6,
           [1]= {
					attr= {name="生命值上限+32000",data=32000,type=1,},
					attrstring="生命值上限+32000",
				},
			[2]= {
					attr= {name="魔法值上限+32000",data=32000,type=2,},
					attrstring="魔法值上限+32000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+320",
							data=320,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+320",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+32%",
							data=3200,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+32%",
				},
		},
}

---------------------------------------------------------------------------------------------------

--暗影套
gdSuitAttribute[888] = {
	id=888,
	name="暗影套装",
	suitcnt=9,
	[1]= {
			cnt=3,
			[1]= {
					attr= {name="生命值上限+10000",data=10000,type=1,},
					attrstring="生命值上限+10000",
				},
			[2]= {
					attr= {name="魔法值上限+10000",data=10000,type=2,},
					attrstring="魔法值上限+10000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+250",
							data=250,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+250",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+10",
							data=1000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+10%",
				},
		},
	[2]= {
			cnt=6,
			[1]= {
					attr= {name="生命值上限+30000",data=30000,type=1,},
					attrstring="生命值上限+30000",
				},
			[2]= {
					attr= {name="魔法值上限+30000",data=30000,type=2,},
					attrstring="魔法值上限+30000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+1000",
							data=1000,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+1000",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+20%",
							data=2000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+20%",
				},
		},
	[3]= {
			cnt=9,
			[1]= {
					attr= {name="生命值上限+60000",data=60000,type=1,},
					attrstring="生命值上限+60000",
				},
			[2]= {
					attr= {name="魔法值上限+60000",data=60000,type=2,},
					attrstring="魔法值上限+60000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+3000",
							data=3000,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+3000",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+33%",
							data=3300,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+33%",
				},
		},
}








gdSuitAttribute[999] = {
	id=999,
	name="修罗灭天套装",
	suitcnt=10,
	[1]= {
			cnt=10,
			[1]= {
					attr= {name="生命值上限+8000",data=8000,type=1,},
					attrstring="生命值上限+8000",
				},
			[2]= {
					attr= {name="魔法值上限+8000",data=8000,type=2,},
					attrstring="魔法值上限+8000",
				},
			[3]= {
					attr= {
							name="全职业最大攻击+115",
							data=115,
							typetable= {[1]=6,[2]=10,[3]=8,},
						},
					attrstring="全职业最大攻击+115",
				},
			[4]= {
					attr= {
							name="魂石最大攻击+20%",
							data=2000,
							isstone=true,
							typetable= {[1]=45,[2]=49,[3]=47,},
						},
					attrstring="魂石最大攻击+20%",
				},
		},
}
