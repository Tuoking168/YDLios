if not (type(gdActivityGift)=="table") then
	gdActivityGift = {}
end

gdActivityGift =
{
	[1]= {
			id=1,
			name="首充礼包",
			rewards= {
					[1]= {datax=1,iid=50000,},
				},
		},
	[2]= {
			id=2,
			name="每日首充",
			rewards= {
					[1]= {datax=1,iid=50001,},
				},
		},
	[3]= {
			id=3,
			name="累计充值",
			rewards= {
					[1]= {datax=5000,iid=50002,},
					[2]= {datax=10000,iid=50003,},
					[3]= {datax=20000,iid=50004,},
					[4]= {datax=50000,iid=50005,},
					[5]= {datax=100000,iid=50006,},
					[6]= {datax=200000,iid=50007,},
					[7]= {datax=500000,iid=50008,},
					[8]= {datax=1000000,iid=50009,},
					[9]= {datax=3000000,iid=50010,},
					[10]= {datax=5000000,iid=50011,},
					[11]= {datax=10000000,iid=50012,},
					[12]= {datax=20000000,iid=50013,},
					[13]= {datax=50000000,iid=50014,},
				},
		},
	[4]= {
			id=4,
			name="N月礼包",
			rewards= {
					[1]= {datax=100,iid=50015,},
				},
		},
	[5]= {
			id=5,
			name="限时大礼包",
			rewards= {
					[1]= {datax=68,datay=24,iid=50016,},
				},
		},
	[6]= {
			id=6,
			name="在线奖励",
			rewards= {
					[1]= {datax=1,iid=50017,},
					[2]= {datax=3,iid=50018,},
					[3]= {datax=6,iid=50019,},
					[4]= {datax=15,iid=50020,},
					[5]= {datax=30,iid=50021,},
				},
		},
	[7]= {
			id=7,
			name="每周工资",
			rewards= {
					[1]= {datax=2,iid=50022,},
					[2]= {datax=5,iid=50023,},
					[3]= {datax=10,iid=50024,},
					[4]= {datax=17,iid=50025,},
					[5]= {datax=26,iid=50026,},
				},
		},
	[8]= {
			id=8,
			name="消费抽奖",
			rewards= {},
		},
	[9]= {
			id=9,
			name="开服活动",
			rewards= {},
		},
	[10]= {
			id=10,
			name="冲级竞技",
			rewards= {
					[1]= {datax=60,datay=20,iid=50027,},
					[2]= {datax=70,datay=15,iid=50028,},
					[3]= {datax=50,datay=10,iid=50029,reborn=1,},
					[4]= {datax=60,datay=3,iid=50030,reborn=2,},
					[5]= {datax=70,datay=1,iid=50031,reborn=3,},
				},
		},
	[11]= {
			id=11,
			name="宠物竞技",
			rewards= {
					[1]= {datax=21,datay=20,iid=50032,},
					[2]= {datax=33,datay=15,iid=50033,},
					[3]= {datax=45,datay=10,iid=50034,},
					[4]= {datax=57,datay=3,iid=50035,},
					[5]= {datax=71,datay=1,iid=50036,},
				},
		},
	[12]= {
			id=12,
			name="魂石竞技",
			rewards= {
					[1]= {datax=500,datay=20,iid=50037,},
					[2]= {datax=1200,datay=15,iid=50038,},
					[3]= {datax=3000,datay=10,iid=50039,},
					[4]= {datax=7000,datay=3,iid=50040,},
					[5]= {datax=15000,datay=1,iid=50041,},
				},
		},
	[13]= {
			id=13,
			name="投资计划",
			rewards= {},
		},
	[14]= {
			id=14,
			name="战神史册",
			rewards= {},
		},
	[15]= {
			id=15,
			name="财神闯关",
			rewards= {},
		},
	[16]= {
			id=16,
			name="寻宝",
			rewards= {},
		},
	[17]= {
			id=17,
			name="每日活跃",
			rewards= {
					[1]= {datax=10,iid=50044,},
					[2]= {datax=40,iid=50045,},
					[3]= {datax=70,iid=50046,},
					[4]= {datax=100,iid=50047,},
				},
		},
}
if not (type(gdOpenActivitys)=="table") then
	gdOpenActivitys = {}
end

gdOpenActivitys =
{
	[1]= {
			id=1,
			activityinfo=-7,
			normalreward= {
					[1]= {count=1,reward=59,type=0,},
				},
			rewardinfo="等级达到40级",
			specialreward= {
					[1]= {count=1,reward=49,type=0,},
				},
			title="第一天：冲级达人",
		},
	[2]= {
			id=2,
			activityinfo=-8,
			normalreward= {
					[1]= {count=1,reward=60,type=0,},
				},
			rewardinfo="装备二档或以上翅膀",
			specialreward= {
					[1]= {count=1,reward=50,type=0,},
				},
			title="第二天：最炫翅膀风",
		},
	[3]= {
			id=3,
			activityinfo=-9,
			normalreward= {
					[1]= {count=1,reward=61,type=0,},
				},
			rewardinfo="战力达到1500",
			specialreward= {
					[1]= {count=1,reward=51,type=0,},
				},
			title="第三天：攻城大战",
		},
	[4]= {
			id=4,
			activityinfo=-10,
			normalreward= {
					[1]= {count=1,reward=62,type=0,},
				},
			rewardinfo="宠物达到15级以上",
			specialreward= {
					[1]= {count=1,reward=52,type=0,},
				},
			title="第四天：萌宠大比拼",
		},
	[5]= {
			id=5,
			activityinfo=-11,
			normalreward= {
					[1]= {count=1,reward=63,type=0,},
				},
			rewardinfo="消费达到888元宝",
			specialreward= {
					[1]= {count=1,reward=53,type=0,},
				},
			title="第五天：消费大回馈",
		},
	[6]= {
			id=6,
			activityinfo=-12,
			normalreward= {
					[1]= {count=1,reward=64,type=0,},
				},
			rewardinfo="战力达到1800",
			specialreward= {
					[1]= {count=1,reward=54,type=0,},
				},
			title="第六天：魂石收藏家",
		},
	[7]= {
			id=7,
			activityinfo=-13,
			normalreward= {
					[1]= {count=1,reward=65,type=0,},
				},
			rewardinfo="个人结阵数达到100",
			specialreward= {
					[1]= {count=1,reward=55,type=0,},
				},
			title="第七天：神装比拼",
		},
	[8]= {
			id=8,
			activityinfo=-14,
			normalreward= {
					[1]= {count=1,reward=66,type=0,},
				},
			rewardinfo="装备强化总和40星",
			specialreward= {
					[1]= {count=1,reward=56,type=0,},
				},
			title="第八天：强化大师",
		},
	[9]= {
			id=9,
			activityinfo=-15,
			normalreward= {
					[1]= {count=1,reward=67,type=0,},
				},
			rewardinfo="总鉴定积分达到300",
			specialreward= {
					[1]= {count=1,reward=57,type=0,},
				},
			title="第九天：鉴定大师",
		},
	[10]= {
			id=10,
			activityinfo=-16,
			normalreward= {
					[1]= {count=1,reward=68,type=0,},
				},
			rewardinfo="战力达到3000",
			specialreward= {
					[1]= {count=1,reward=58,type=0,},
				},
			title="第十天：战力我最高",
		},
}
if not (type(gdInvestPlan)=="table") then
	gdInvestPlan = {}
end

gdInvestPlan =
{
	[1]= {id=1,count1=500,count2=100,item1=3,item2=4,itemname1="500元宝",itemname2="100仙玉",},
	[2]= {id=2,count1=300,count2=100,item1=3,item2=4,itemname1="300元宝",itemname2="100仙玉",},
	[3]= {id=3,count1=200,count2=100,item1=3,item2=4,itemname1="200元宝",itemname2="100仙玉",},
	[4]= {id=4,count1=5,count2=100,item1=30094,item2=4,itemname1="500转生灵魄",itemname2="100仙玉",},
	[5]= {id=5,count1=30000,count2=100,item1=6,item2=4,itemname1="3万荣誉",itemname2="100仙玉",},
	[6]= {id=6,count1=10,count2=100,item1=30094,item2=4,itemname1="1000转生灵魄",itemname2="100仙玉",},
	[7]= {id=7,count1=50000,count2=100,item1=6,item2=4,itemname1="5万荣誉",itemname2="100仙玉",},
	[8]= {id=8,count1=10,count2=100,item1=30094,item2=4,itemname1="1000转生灵魄",itemname2="100仙玉",},
	[9]= {id=9,count1=80000,count2=100,item1=6,item2=4,itemname1="8万荣誉",itemname2="100仙玉",},
	[10]= {id=10,count1=10,count2=100,item1=30094,item2=4,itemname1="1000转生灵魄",itemname2="100仙玉",},
	[11]= {id=11,count1=100000,count2=100,item1=6,item2=4,itemname1="10万荣誉",itemname2="100仙玉",},
	[12]= {id=12,count1=10,count2=100,item1=30094,item2=4,itemname1="1000转生灵魄",itemname2="100仙玉",},
	[13]= {id=13,count1=150000,count2=100,item1=6,item2=4,itemname1="15万荣誉",itemname2="100仙玉",},
	[14]= {id=14,count1=20,count2=100,item1=30094,item2=4,itemname1="2000转生灵魄",itemname2="100仙玉",},
	[15]= {id=15,count1=200000,count2=100,item1=6,item2=4,itemname1="20万荣誉",itemname2="100仙玉",},
}
if not (type(gdFireExp)=="table") then
	gdFireExp = {}
end

gdFireExp =
{
	[1]=309,
	[2]=309,
	[3]=309,
	[4]=621,
	[5]=621,
	[6]=933,
	[7]=933,
	[8]=1245,
	[9]=1245,
	[10]=1557,
	[11]=1869,
	[12]=2181,
	[13]=2493,
	[14]=3117,
	[15]=3429,
	[16]=4053,
	[17]=4365,
	[18]=4989,
	[19]=5613,
	[20]=6237,
	[21]=6858,
	[22]=7482,
	[23]=8106,
	[24]=8730,
	[25]=9354,
	[26]=9978,
	[27]=10602,
	[28]=11226,
	[29]=11850,
	[30]=13098,
	[31]=14346,
	[32]=15594,
	[33]=16842,
	[34]=18090,
	[35]=19338,
	[36]=20586,
	[37]=21834,
	[38]=23082,
	[39]=24330,
	[40]=26826,
	[41]=29322,
	[42]=31818,
	[43]=34314,
	[44]=36810,
	[45]=39306,
	[46]=41802,
	[47]=44298,
	[48]=46794,
	[49]=49290,
	[50]=54282,
	[51]=59274,
	[52]=64266,
	[53]=69258,
	[54]=74250,
	[55]=79242,
	[56]=84234,
	[57]=89226,
	[58]=94218,
	[59]=99210,
	[60]=109194,
	[61]=119178,
	[62]=129162,
	[63]=139146,
	[64]=149130,
	[65]=159114,
	[66]=169098,
	[67]=179082,
	[68]=189066,
	[69]=199050,
	[70]=219018,
	[71]=238986,
	[72]=258954,
	[73]=278922,
	[74]=298890,
	[75]=318858,
	[76]=338826,
	[77]=358794,
	[78]=378762,
	[79]=398730,
	[80]=438666,
	[81]=478602,
	[82]=518538,
	[83]=558474,
	[84]=598410,
	[85]=638346,
	[86]=678282,
	[87]=718218,
	[88]=758154,
	[89]=798090,
	[90]=877962,
	[91]=957834,
	[92]=1037706,
	[93]=1117578,
	[94]=1197450,
	[95]=1277322,
}
if not (type(gdLoginReward)=="table") then
	gdLoginReward = {}
end

gdLoginReward =
{
	[1]= {
			id=1,
			name="第一天",
			lvl=40,
			reward= {
					[1]= {name="100倍经验神符(8小时)",count=5,type=30164,},
					
				},
		},
	[2]= {
			id=2,
			name="第二天",
			lvl=45,
			reward= {
					[1]= {name="100倍经验神符(8小时)",count=10,type=30164,},
				
				},
		},
	[3]= {
			id=3,
			name="第三天",
			lvl=48,
			reward= {
					[1]= {name="100倍经验神符(8小时)",count=10,type=30164,},
					
				},
		},
	[4]= {
			id=4,
			name="第四天",
			lvl=50,
			reward= {
					[1]= {name="转生灵魄",count=100,type=30091,},
					[2]= {name="宠物项圈",count=100,type=40053,},
				},
		},
	[5]= {
			id=5,
			name="第五天",
			lvl=52,
			reward= {
					[1]= {name="灵爵",count=5,type=30092,},
					
				},
		},
	[6]= {
			id=6,
			name="第六天",
			lvl=53,
			reward= {
					[1]= {name="100倍经验神符(8小时)",count=10,type=30164,},
					[2]= {name="悟空",count=1,type=38004,},
				},
		},
	[7]= {
			id=7,
			name="第七天",
			lvl=54,
			reward= {
					[1]= {name="14级魂石袋",count=3,type=30347,},
					[2]= {name="100倍经验神符(8小时)",count=10,type=30164,},
				},
		},
	[8]= {
			id=8,
			name="第八天",
			lvl=55,
			reward= {
					[1]= {name="亡灵玫瑰",count=1,type=82084,},
					[2]= {name="100倍经验神符(8小时)",count=10,type=30164,},
				},
		},
	[9]= {
			id=9,
			name="第九天",
			lvl=55,
			reward= {
					[1]= {name="100倍经验神符(8小时)",count=10,type=30164,},
				},
		},
	[10]= {
			id=10,
			name="第十天",
			lvl=55,
			reward= {
					[1]= {name="100倍经验神符(8小时)",count=10,type=30164,},
				},
		},
}
if not (type(gdArenaExp)=="table") then
	gdArenaExp = {}
end

gdArenaExp =
{
	[1]= {loseexp=50,lvl=1,winexp=100,},
	[2]= {loseexp=58,lvl=2,winexp=115,},
	[3]= {loseexp=66,lvl=3,winexp=132,},
	[4]= {loseexp=76,lvl=4,winexp=152,},
	[5]= {loseexp=87,lvl=5,winexp=174,},
	[6]= {loseexp=101,lvl=6,winexp=201,},
	[7]= {loseexp=116,lvl=7,winexp=231,},
	[8]= {loseexp=133,lvl=8,winexp=266,},
	[9]= {loseexp=153,lvl=9,winexp=305,},
	[10]= {loseexp=176,lvl=10,winexp=352,},
	[11]= {loseexp=202,lvl=11,winexp=405,},
	[12]= {loseexp=233,lvl=12,winexp=465,},
	[13]= {loseexp=268,lvl=13,winexp=535,},
	[14]= {loseexp=308,lvl=14,winexp=615,},
	[15]= {loseexp=354,lvl=15,winexp=708,},
	[16]= {loseexp=407,lvl=16,winexp=814,},
	[17]= {loseexp=468,lvl=17,winexp=936,},
	[18]= {loseexp=538,lvl=18,winexp=1076,},
	[19]= {loseexp=619,lvl=19,winexp=1238,},
	[20]= {loseexp=712,lvl=20,winexp=1423,},
	[21]= {loseexp=818,lvl=21,winexp=1637,},
	[22]= {loseexp=941,lvl=22,winexp=1882,},
	[23]= {loseexp=1082,lvl=23,winexp=2164,},
	[24]= {loseexp=1245,lvl=24,winexp=2489,},
	[25]= {loseexp=1431,lvl=25,winexp=2863,},
	[26]= {loseexp=1646,lvl=26,winexp=3292,},
	[27]= {loseexp=1893,lvl=27,winexp=3786,},
	[28]= {loseexp=2177,lvl=28,winexp=4354,},
	[29]= {loseexp=2503,lvl=29,winexp=5007,},
	[30]= {loseexp=2879,lvl=30,winexp=5758,},
	[31]= {loseexp=3311,lvl=31,winexp=6621,},
	[32]= {loseexp=3807,lvl=32,winexp=7614,},
	[33]= {loseexp=4378,lvl=33,winexp=8757,},
	[34]= {loseexp=5035,lvl=34,winexp=10070,},
	[35]= {loseexp=5790,lvl=35,winexp=11580,},
	[36]= {loseexp=6659,lvl=36,winexp=13318,},
	[37]= {loseexp=7658,lvl=37,winexp=15315,},
	[38]= {loseexp=8806,lvl=38,winexp=17612,},
	[39]= {loseexp=10127,lvl=39,winexp=20254,},
	[40]= {loseexp=11646,lvl=40,winexp=23292,},
	[41]= {loseexp=13393,lvl=41,winexp=26786,},
	[42]= {loseexp=15402,lvl=42,winexp=30804,},
	[43]= {loseexp=17712,lvl=43,winexp=35425,},
	[44]= {loseexp=20369,lvl=44,winexp=40739,},
	[45]= {loseexp=23425,lvl=45,winexp=46850,},
	[46]= {loseexp=26938,lvl=46,winexp=53877,},
	[47]= {loseexp=30979,lvl=47,winexp=61958,},
	[48]= {loseexp=35626,lvl=48,winexp=71252,},
	[49]= {loseexp=40970,lvl=49,winexp=81940,},
	[50]= {loseexp=47116,lvl=50,winexp=94231,},
	[51]= {loseexp=54183,lvl=51,winexp=108366,},
	[52]= {loseexp=62310,lvl=52,winexp=124621,},
	[53]= {loseexp=71657,lvl=53,winexp=143314,},
	[54]= {loseexp=82405,lvl=54,winexp=164811,},
	[55]= {loseexp=94766,lvl=55,winexp=189532,},
	[56]= {loseexp=108981,lvl=56,winexp=217962,},
	[57]= {loseexp=125328,lvl=57,winexp=250657,},
	[58]= {loseexp=144128,lvl=58,winexp=288255,},
	[59]= {loseexp=165747,lvl=59,winexp=331493,},
	[60]= {loseexp=190609,lvl=60,winexp=381217,},
	[61]= {loseexp=219200,lvl=61,winexp=438400,},
	[62]= {loseexp=252080,lvl=62,winexp=504160,},
	[63]= {loseexp=289892,lvl=63,winexp=579784,},
	[64]= {loseexp=333376,lvl=64,winexp=666751,},
	[65]= {loseexp=383382,lvl=65,winexp=766764,},
	[66]= {loseexp=440889,lvl=66,winexp=881779,},
	[67]= {loseexp=507023,lvl=67,winexp=1014046,},
	[68]= {loseexp=583076,lvl=68,winexp=1166152,},
	[69]= {loseexp=670538,lvl=69,winexp=1341075,},
	[70]= {loseexp=771118,lvl=70,winexp=1542237,},
	[71]= {loseexp=886786,lvl=71,winexp=1773572,},
	[72]= {loseexp=1019804,lvl=72,winexp=2039608,},
	[73]= {loseexp=1172774,lvl=73,winexp=2345549,},
	[74]= {loseexp=1348691,lvl=74,winexp=2697381,},
	[75]= {loseexp=1550994,lvl=75,winexp=3101989,},
	[76]= {loseexp=1783643,lvl=76,winexp=3567287,},
	[77]= {loseexp=2051190,lvl=77,winexp=4102380,},
	[78]= {loseexp=2358868,lvl=78,winexp=4717737,},
	[79]= {loseexp=2712699,lvl=79,winexp=5425397,},
	[80]= {loseexp=3119603,lvl=80,winexp=6239207,},
	[81]= {loseexp=3587544,lvl=81,winexp=7175088,},
	[82]= {loseexp=4125676,lvl=82,winexp=8251351,},
	[83]= {loseexp=4744527,lvl=83,winexp=9489054,},
	[84]= {loseexp=5456206,lvl=84,winexp=10912412,},
	[85]= {loseexp=6274637,lvl=85,winexp=12549274,},
	[86]= {loseexp=7215832,lvl=86,winexp=14431665,},
	[87]= {loseexp=8298207,lvl=87,winexp=16596414,},
	[88]= {loseexp=9542938,lvl=88,winexp=19085877,},
	[89]= {loseexp=10974379,lvl=89,winexp=21948758,},
	[90]= {loseexp=12620536,lvl=90,winexp=25241072,},
}
if not (type(gdArenaTimeReward)=="table") then
	gdArenaTimeReward = {}
end

gdArenaTimeReward =
{
	[1]= {expper=1,honor=20000,},
	[2]= {expper=0.95,honor=18000,},
	[3]= {expper=0.9,honor=16201,},
	[4]= {expper=0.85,honor=13123,},
	[5]= {expper=0.8,honor=11811,},
	[6]= {expper=0.76,honor=10629,},
	[7]= {expper=0.72,honor=9567,},
	[8]= {expper=0.68,honor=8610,},
	[9]= {expper=0.64,honor=7749,},
	[10]= {expper=0.6,honor=6974,},
	[20]= {expper=0.57,honor=6276,},
	[30]= {expper=0.54,honor=5649,},
	[40]= {expper=0.51,honor=5084,},
	[50]= {expper=0.48,honor=4576,},
	[100]= {expper=0.45,honor=4118,},
	[200]= {expper=0.42,honor=3706,},
	[500]= {expper=0.39,honor=3336,},
	[1000]= {expper=0.36,honor=3002,},
}
if not (type(gdSingalRecharge)=="table") then
	gdSingalRecharge = {}
end

gdSingalRecharge =
{
	[1]= {desc="凤凰莅临，百鸟来朝",obtain="单笔充值金额达到100元，即可领取\n\n可重复领取",property="物理攻击：12-27\n法术攻击：12-27\n道术攻击：12-27\n物理防御：3-6\n法术防御：3-4",recharge=1000,sid=80001,},
	[2]= {desc="怒火战神，横扫千军",obtain="单笔充值金额达到500元，即可领取\n\n可重复领取",property="物理攻击：19-42\n法术攻击：19-42\n道术攻击：19-42\n物理防御：5-10\n法术防御：5-6",recharge=5000,sid=80003,},
	[3]= {desc="粉翼彩蝶，魅惑众生",obtain="单笔充值金额达到1000元，即可领取\n\n可重复领取",property="物理攻击：23-50\n法术攻击：23-50\n道术攻击：23-50\n物理防御：6-12\n法术防御：6-12",recharge=10000,sid=80004,},
	[4]= {desc="如梦似幻，无影无形",obtain="单笔充值金额达到2000元，即可领取\n\n可重复领取",property="物理攻击：32-70\n法术攻击：32-70\n道术攻击：32-70\n物理防御：8-17\n法术防御：8-10",recharge=20000,sid=80005,},
	[5]= {desc="萤玉之影，幻光夺目",obtain="单笔充值金额达到3000元，即可领取\n\n可重复领取",property="物理攻击：45-98\n法术攻击：45-98\n道术攻击：45-98\n物理防御：11-24\n法术防御：11-14",recharge=30000,sid=80006,},
	[6]= {desc="魔龙降世，燃尽敌躯",obtain="单笔充值金额达到5000元，即可领取\n\n可重复领取",property="物理攻击：63-137\n法术攻击：63-137\n道术攻击：63-137\n物理防御：15-34\n法术防御：15-20",recharge=50000,sid=80007,},
	[7]= {desc="七星拱瑞，刹那芳华",obtain="单笔充值金额达到10000元，即可领取\n\n可重复领取",property="物理攻击：95-206\n法术攻击：95-206\n道术攻击：95-206\n物理防御：23-51\n法术防御：23-30",recharge=100000,sid=80008,},
}
if not (type(gdLuckyCircleReward)=="table") then
	gdLuckyCircleReward = {}
end

gdLuckyCircleReward =
{
	[1]= {id=1,name="橙钻石",cnt=10,itemID=41112,probability=1,},
	[2]= {id=2,name="紫钻石",cnt=20,itemID=41111,probability=5,},
	[3]= {id=3,name="蓝钻石",cnt=50,itemID=41110,probability=10,},
	[4]= {id=4,name="仙玉",cnt=30,itemID=4,probability=5,},
    [5]= {id=5,name="元宝",cnt=20000,itemID=3,probability=8,},
	[6]= {id=6,name="100倍经验神符(8小时)",cnt=1,itemID=30164,probability=3,},
    [7]= {id=7,name="金蝉王",cnt=1,itemID=30059,probability=12,},
    [8]= {id=8,name="灵魂石",cnt=500,itemID=40011,probability=25,},
}
if not (type(gdRepayReward)=="table") then
	gdRepayReward = {}
end

gdRepayReward =
{
	[1001]= {
			id=1001,
			canrepeat=1,
			eventid=5000,
			req=5000000,
			reward= {
					[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					[2]= {itemID=40053,itemIsBind=true,itemcnt=10,itemname="宠物项圈",},
					[3]= {itemID=30164,itemIsBind=true,itemcnt=1,itemname="10倍8小时",},
				},
			text="每日消费达500w元宝可领取：",
		},
	[1002]= {
			id=1002,
			canrepeat=1,
			eventid=5001,
			req=30000000,
			reward= {
					[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					[2]= {itemID=4,itemIsBind=true,itemcnt=30,itemname="仙玉",},
					[3]= {itemID=30164,itemIsBind=true,itemcnt=10,itemname="10倍8小时",},
				},
			text="每日消费达3000w元宝可领取：",
		},
	[1003]= {
			id=1003,
			canrepeat=1,
			eventid=5002,
			req=50000000,
			reward= {
					[1]= {itemID=5555,itemIsBind=true,itemcnt=2,itemname="突破蛋",},
					[2]= {itemID=30164,itemIsBind=true,itemcnt=1,itemname="10倍8小时",},
					[3]= {itemID=4,itemIsBind=true,itemcnt=30,itemname="仙玉",},
					[4]= {itemID=41111,itemIsBind=true,itemcnt=15,itemname="紫钻石",},
				},
			text="每日消费达5000w元宝可领取：",
		},
	[1004]= {
			id=1004,
			canrepeat=1,
			eventid=5003,
			req=80000000,
			reward= {
					[1]= {itemID=5555,itemIsBind=true,itemcnt=3,itemname="突破蛋",},
					[2]= {itemID=5555,itemIsBind=true,itemcnt=5,itemname="突破蛋",},
					[3]= {itemID=4,itemIsBind=true,itemcnt=30,itemname="仙玉",},
					[4]= {itemID=41111,itemIsBind=true,itemcnt=30,itemname="紫钻石",},
				},
			text="每日消费达8000w元宝可领取：",
		},
	-- [1005]= {
			-- id=1005,
			-- canrepeat=1,
			-- eventid=5004,
			-- req=100000000,
			-- reward= {
					-- [1]= {itemID=85996,itemIsBind=true,itemcnt=3,itemname="蓝玫瑰",},
					-- [2]= {itemID=41117,itemIsBind=true,itemcnt=1,itemname="符文令",},
					-- [3]= {itemID=5555,itemIsBind=true,itemcnt=8,itemname="突破蛋",},
					-- [4]= {itemID=85997,itemIsBind=true,itemcnt=60,itemname="暗影石",},
				-- },
			-- text="每日消费达1亿元宝可领取：",
		-- },
	[2001]= {
			id=2001,
			canrepeat=1,
			eventid=5006,
			req=20,
			reward= {
					[1]= {itemID=40011,itemIsBind=true,itemcnt=100,itemname="灵魂石",},
				},
			text="装备强化达20级可领取：",
		},
	[2002]= {
			id=2002,
			canrepeat=1,
			eventid=5007,
			req=30,
			reward= {
					[1]= {itemID=41110,itemIsBind=true,itemcnt=100,itemname="蓝钻石",},
				},
			text="装备强化达30级可领取：",
		},
	[2003]= {
			id=2003,
			canrepeat=1,
			eventid=5008,
			req=40,
			reward= {
					[1]= {itemID=41111,itemIsBind=true,itemcnt=50,itemname="紫钻石",},
				},
			text="装备强化达40级可领取：",
		},
	[2004]= {
			id=2004,
			canrepeat=1,
			eventid=5009,
			req=45,
			reward= {
					[1]= {itemID=41111,itemIsBind=true,itemcnt=50,itemname="紫钻石",},
				},
			text="装备强化达45级可领取：",
		},
	[2005]= {
			id=2005,
			canrepeat=1,
			eventid=5062,
			req=50,
			reward= {
					[1]= {itemID=41112,itemIsBind=true,itemcnt=30,itemname="橙钻石",},
				},
			text="装备强化达50级可领取：",
		},
	-- [2006]= {
			-- id=2006,
			-- canrepeat=1,
			-- eventid=5063,
			-- req=13,
			-- reward= {
					-- [1]= {itemID=40011,itemIsBind=true,itemcnt=8,itemname="灵魂石",},
				-- },
			-- text="装备强化达13级可领取：",
		-- },
	-- [2007]= {
			-- id=2007,
			-- canrepeat=1,
			-- eventid=5064,
			-- req=14,
			-- reward= {
					-- [1]= {itemID=40011,itemIsBind=true,itemcnt=13,itemname="灵魂石",},
				-- },
			-- text="装备强化达14级可领取：",
		-- },
	-- [2008]= {
			-- id=2008,
			-- canrepeat=1,
			-- eventid=5065,
			-- req=15,
			-- reward= {
					-- [1]= {itemID=30311,itemIsBind=true,itemcnt=3,itemname="5级魂石袋",},
				-- },
			-- text="装备强化达15级可领取：",
		-- },
	[3001]= {
			id=3001,
			canrepeat=0,
			eventid=5010,
			req=20,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=20,itemname="宠物项圈",},
				},
			text="宠物等级达20级可领取：",
		},
	[3002]= {
			id=3002,
			canrepeat=0,
			eventid=5011,
			req=25,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=25,itemname="宠物项圈",},
				},
			text="宠物等级达25级可领取：",
		},
	[3003]= {
			id=3003,
			canrepeat=0,
			eventid=5012,
			req=30,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=30,itemname="宠物项圈",},
				},
			text="宠物等级达30级可领取：",
		},
	[3004]= {
			id=3004,
			canrepeat=0,
			eventid=5013,
			req=35,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=35,itemname="宠物项圈",},
				},
			text="宠物等级达35级可领取：",
		},
	[3005]= {
			id=3005,
			canrepeat=0,
			eventid=5014,
			req=40,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=40,itemname="宠物项圈",},
				},
			text="宠物等级达40级可领取：",
		},
	[3006]= {
			id=3006,
			canrepeat=0,
			eventid=5072,
			req=45,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=45,itemname="宠物项圈",},
				},
			text="宠物等级达45级可领取：",
		},
	[3007]= {
			id=3007,
			canrepeat=0,
			eventid=5073,
			req=50,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=50,itemname="宠物项圈",},
				},
			text="宠物等级达50级可领取：",
		},
	[3008]= {
			id=3008,
			canrepeat=0,
			eventid=5074,
			req=55,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=55,itemname="宠物项圈",},
				},
			text="宠物等级达55级可领取：",
		},
	[3009]= {
			id=3009,
			canrepeat=0,
			eventid=5075,
			req=60,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=60,itemname="宠物项圈",},
				},
			text="宠物等级达60级可领取：",
		},
	[3010]= {
			id=3010,
			canrepeat=0,
			eventid=5076,
			req=65,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=65,itemname="宠物项圈",},
				},
			text="宠物等级达65级可领取：",
		},
	[3011]= {
			id=3011,
			canrepeat=0,
			eventid=5077,
			req=70,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=70,itemname="宠物项圈",},
				},
			text="宠物等级达70级可领取：",
		},
	[3012]= {
			id=3012,
			canrepeat=0,
			eventid=5078,
			req=75,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=75,itemname="宠物项圈",},
				},
			text="宠物等级达75级可领取：",
		},
	[3013]= {
			id=3013,
			canrepeat=0,
			eventid=5079,
			req=80,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=80,itemname="宠物项圈",},
				},
			text="宠物等级达80级可领取：",
		},
	[3014]= {
			id=3014,
			canrepeat=0,
			eventid=5080,
			req=85,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=85,itemname="宠物项圈",},
				},
			text="宠物等级达85级可领取：",
		},
	[3015]= {
			id=3015,
			canrepeat=0,
			eventid=5081,
			req=90,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=90,itemname="宠物项圈",},
				},
			text="宠物等级达90级可领取：",
		},
	[3016]= {
			id=3016,
			canrepeat=0,
			eventid=5082,
			req=95,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=95,itemname="宠物项圈",},
				},
			text="宠物等级达95级可领取：",
		},
	[3017]= {
			id=3017,
			canrepeat=0,
			eventid=5083,
			req=100,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=100,itemname="宠物项圈",},
				},
			text="宠物等级达100级可领取：",
		},
	[3018]= {
			id=3018,
			canrepeat=0,
			eventid=5084,
			req=105,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=105,itemname="宠物项圈",},
				},
			text="宠物等级达105级可领取：",
		},
	[3019]= {
			id=3019,
			canrepeat=0,
			eventid=5085,
			req=110,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=110,itemname="宠物项圈",},
				},
			text="宠物等级达110级可领取：",
		},
	[3020]= {
			id=3020,
			canrepeat=0,
			eventid=5086,
			req=115,
			reward= {
					[1]= {itemID=40053,itemIsBind=true,itemcnt=115,itemname="宠物项圈",},
				},
			text="宠物等级达115级可领取：",
		},
	-- [3021]= {
			-- id=3021,
			-- canrepeat=0,
			-- eventid=5087,
			-- req=119,
			-- reward= {
					-- [1]= {itemID=40053,itemIsBind=true,itemcnt=120,itemname="宠物项圈",},
				-- },
			-- text="宠物等级达120级可领取：",
		-- },
	[4001]= {
			id=4001,
			canrepeat=1,
			eventid=5068,
			req=10,
			reward= {
					[1]= {itemID=30315,itemIsBind=true,itemcnt=2,itemname="9级魂石袋",},
				},
			text="魂石等级达10级可领取：",
		},
	[4002]= {
			id=4002,
			canrepeat=1,
			eventid=5016,
			req=11,
			reward= {
					[1]= {itemID=30316,itemIsBind=true,itemcnt=2,itemname="10级魂石袋",},
				},
			text="魂石等级达11级可领取：",
		},
	[4003]= {
			id=4003,
			canrepeat=1,
			eventid=5069,
			req=12,
			reward= {
					[1]= {itemID=30317,itemIsBind=true,itemcnt=2,itemname="11级魂石袋",},
				},
			text="魂石等级达12级可领取：",
		},
	[4004]= {
			id=4004,
			canrepeat=1,
			eventid=5017,
			req=13,
			reward= {
					[1]= {itemID=30345,itemIsBind=true,itemcnt=2,itemname="12级魂石袋",},
				},
			text="魂石等级达13级可领取：",
		},
	[4005]= {
			id=4005,
			canrepeat=1,
			eventid=5018,
			req=14,
			reward= {
					[1]= {itemID=30346,itemIsBind=true,itemcnt=2,itemname="13级魂石袋",},
				},
			text="魂石等级达14级可领取：",
		},
	[4006]= {
			id=4006,
			canrepeat=1,
			eventid=5114,
			req=15,
			reward= {
					[1]= {itemID=30347,itemIsBind=true,itemcnt=2,itemname="14级魂石袋",},
				},
			text="魂石等级达15级可领取：",
		},
	[4007]= {
			id=4007,
			canrepeat=1,
			eventid=5115,
			req=16,
			reward= {
					[1]= {itemID=30348,itemIsBind=true,itemcnt=2,itemname="15级魂石袋",},
				},
			text="魂石等级达16级可领取：",
		},
	[4008]= {
			id=4008,
			canrepeat=1,
			eventid=5110,
			req=17,
			reward= {
					[1]= {itemID=30348,itemIsBind=true,itemcnt=4,itemname="15级魂石袋",},
				},
			text="魂石等级达17级可领取：",
		},
	[4009]= {
			id=4009,
			canrepeat=1,
			eventid=5111,
			req=18,
			reward= {
					[1]= {itemID=30348,itemIsBind=true,itemcnt=10,itemname="15级魂石袋",},
				},
			text="魂石等级达18级可领取：",
		},
	[4010]= {
			id=4010,
			canrepeat=1,
			eventid=5116,
			req=19,
			reward= {
					[1]= {itemID=30348,itemIsBind=true,itemcnt=20,itemname="15级魂石袋",},
				},
			text="魂石等级达19级可领取：",
		},
	[4011]= {
			id=4011,
			canrepeat=1,
			eventid=5117,
			req=20,
			reward= {
					[1]= {itemID=30348,itemIsBind=true,itemcnt=30,itemname="15级魂石袋",},
				},
			text="魂石等级达20级可领取：",
		},
	[5001]= {
			id=5001,
			canrepeat=1,
			eventid=5020,
			req=3,
			reward= {
					[1]= {itemID=30427,itemIsBind=true,itemcnt=1,itemname="神翼宝箱",},
				},
			text="翅膀等级达3级可领取：",
		},
	[5002]= {
			id=5002,
			canrepeat=1,
			eventid=5021,
			req=4,
			reward= {
					[1]= {itemID=30427,itemIsBind=true,itemcnt=2,itemname="神翼宝箱",},
				},
			text="翅膀等级达4级可领取：",
		},
	[5003]= {
			id=5003,
			canrepeat=1,
			eventid=5024,
			req=5,
			reward= {
					[1]= {itemID=30427,itemIsBind=true,itemcnt=5,itemname="神翼宝箱",},
				},
			text="翅膀等级达5级可领取：",
		},
	[5004]= {
			id=5004,
			canrepeat=1,
			eventid=5088,
			req=6,
			reward= {
					[1]= {itemID=30311,itemIsBind=true,itemcnt=8,itemname="5级魂石袋",},
				},
			text="翅膀等级达6级可领取：",
		},
	[5005]= {
			id=5005,
			canrepeat=1,
			eventid=5089,
			req=7,
			reward= {
					[1]= {itemID=30312,itemIsBind=true,itemcnt=5,itemname="6级魂石袋",},
				},
			text="翅膀等级达7级可领取：",
		},
	[5006]= {
			id=5006,
			canrepeat=1,
			eventid=5090,
			req=8,
			reward= {
					[1]= {itemID=30312,itemIsBind=true,itemcnt=10,itemname="6级魂石袋",},
				},
			text="翅膀等级达8级可领取：",
		},
	[5007]= {
			id=5007,
			canrepeat=1,
			eventid=5091,
			req=9,
			reward= {
					[1]= {itemID=30313,itemIsBind=true,itemcnt=8,itemname="7级魂石袋",},
				},
			text="翅膀等级达9级可领取：",
		},
	[5008]= {
			id=5008,
			canrepeat=1,
			eventid=5092,
			req=10,
			reward= {
					[1]= {itemID=30314,itemIsBind=true,itemcnt=5,itemname="8级魂石袋",},
				},
			text="翅膀等级达10级可领取：",
		},
	[5009]= {
			id=5009,
			canrepeat=1,
			eventid=5093,
			req=11,
			reward= {
					[1]= {itemID=30314,itemIsBind=true,itemcnt=10,itemname="8级魂石袋",},
				},
			text="翅膀等级达11级可领取：",
		},
	[6001]= {
			id=6001,
			canrepeat=0,
			eventid=5025,
			req=5,
			reward= {
					[1]= {itemID=30455,itemIsBind=true,itemcnt=1,itemname="ios魂石福袋",},
				},
			text="寻宝达5次可领取：",
		},
	[6002]= {
			id=6002,
			canrepeat=0,
			eventid=5026,
			req=20,
			reward= {
					[1]= {itemID=30455,itemIsBind=true,itemcnt=4,itemname="ios魂石福袋",},
				},
			text="寻宝达20次可领取：",
		},
	[6003]= {
			id=6003,
			canrepeat=0,
			eventid=5027,
			req=50,
			reward= {
					[1]= {itemID=30455,itemIsBind=true,itemcnt=10,itemname="ios魂石福袋",},
				},
			text="寻宝达50次可领取：",
		},
	[6004]= {
			id=6004,
			canrepeat=0,
			eventid=5028,
			req=100,
			reward= {
					[1]= {itemID=30455,itemIsBind=true,itemcnt=20,itemname="ios魂石福袋",},
				},
			text="寻宝达100次可领取：",
		},
	[6005]= {
			id=6005,
			canrepeat=0,
			eventid=5029,
			req=200,
			reward= {
					[1]= {itemID=30306,itemIsBind=true,itemcnt=10,itemname="磐龙宝箱",},
				},
			text="寻宝达200次可领取：",
		},
	[6006]= {
			id=6006,
			canrepeat=0,
			eventid=6006,
			req=500,
			reward= {
					[1]= {itemID=30306,itemIsBind=true,itemcnt=20,itemname="磐龙宝箱",},
				},
			text="寻宝达500次可领取：",
		},
	[6007]= {
			id=6007,
			canrepeat=0,
			eventid=6007,
			req=1000,
			reward= {
					[1]= {itemID=40143,itemIsBind=true,itemcnt=1,itemname="磐龙许愿盒",},
				},
			text="寻宝达1000次可领取：",
		},
	[6008]= {
			id=6008,
			canrepeat=0,
			eventid=6008,
			req=2000,
			reward= {
					[1]= {itemID=40004,itemIsBind=true,itemcnt=10,itemname="五级灵石",},
				},
			text="寻宝达2000次可领取：",
		},
	[6009]= {
			id=6009,
			canrepeat=0,
			eventid=6009,
			req=3000,
			reward= {
					[1]= {itemID=40004,itemIsBind=true,itemcnt=15,itemname="五级灵石",},
				},
			text="寻宝达3000次可领取：",
		},
	[6010]= {
			id=6010,
			canrepeat=0,
			eventid=6010,
			req=5000,
			reward= {
					[1]= {itemID=40004,itemIsBind=true,itemcnt=20,itemname="五级灵石",},
				},
			text="寻宝达5000次可领取：",
		},
	[7001]= {
			id=7001,
			canrepeat=1,
			eventid=5030,
			req=3,
			reward= {
					[1]= {itemID=30309,itemIsBind=true,itemcnt=3,itemname="3级魂石袋",},
				},
			text="时装达3级可领取：",
		},
	[7002]= {
			id=7002,
			canrepeat=1,
			eventid=5031,
			req=5,
			reward= {
					[1]= {itemID=30310,itemIsBind=true,itemcnt=3,itemname="4级魂石袋",},
				},
			text="时装达5级可领取：",
		},
	[7003]= {
			id=7003,
			canrepeat=1,
			eventid=5032,
			req=7,
			reward= {
					[1]= {itemID=30311,itemIsBind=true,itemcnt=3,itemname="5级魂石袋",},
				},
			text="时装达7级可领取：",
		},
	[7004]= {
			id=7004,
			canrepeat=1,
			eventid=5033,
			req=9,
			reward= {
					[1]= {itemID=80004,itemIsBind=true,itemcnt=1,itemname="粉翼彩蝶(4档)",},
				},
			text="时装达9级可领取：",
		},
	[8001]= {
			id=8001,
			canrepeat=1,
			eventid=5035,
			req=3,
			reward= {
					[1]= {itemID=40071,itemIsBind=true,itemcnt=5,itemname="幻武水晶",},
				},
			text="幻武达3级可领取：",
		},
	[8002]= {
			id=8002,
			canrepeat=1,
			eventid=5036,
			req=5,
			reward= {
					[1]= {itemID=40016,itemIsBind=true,itemcnt=60,itemname="足迹晶魄",},
				},
			text="幻武达5级可领取：",
		},
	[8003]= {
			id=8003,
			canrepeat=1,
			eventid=5037,
			req=7,
			reward= {
					[1]= {itemID=40143,itemIsBind=true,itemcnt=2,itemname="磐龙许愿盒",},
				},
			text="幻武达7级可领取：",
		},
	[8004]= {
			id=8004,
			canrepeat=1,
			eventid=5038,
			req=9,
			reward= {
					[1]= {itemID=40015,itemIsBind=true,itemcnt=25,itemname="战神晶魄",},
				},
			text="幻武达9级可领取：",
		},
	[9001]= {
			id=9001,
			canrepeat=1,
			eventid=5040,
			req=5000000,
			reward= {
					[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					[2]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
				},
			text="消费达500万元宝可领取：",
		},
	[9002]= {
			id=9002,
			canrepeat=1,
			eventid=5041,
			req=10000000,
			reward= {
					[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					[2]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
				},
			text="消费达1000万元宝可领取：",
		},
	[9003]= {
			id=9003,
			canrepeat=1,
			eventid=5042,
			req=30000000,
			reward= {
					[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					[2]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
				},
			text="消费达3000万元宝可领取：",
		},
	[9004]= {
			id=9004,
			canrepeat=1,
			eventid=5043,
			req=50000000,
			reward= {
					
					[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					[2]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					
				},
			text="消费达5000万元宝可领取：",
		},
	[9005]= {
			id=9005,
			canrepeat=1,
			eventid=5044,
			req=100000000,
			reward= {
			
				[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
				[2]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
					
					
				},
			text="消费达1亿元宝可领取：",
		},
	[10001]= {
			id=10001,
			canrepeat=0,
			eventid=5045,
			req=100000,
			reward= {
					[1]= {itemID=3,itemIsBind=true,itemcnt=300000,itemname="元宝",},
				},
			text="累计充值达100000元宝可领取：",
		},
	[10002]= {
			id=10002,
			canrepeat=0,
			eventid=5046,
			req=400000,
			reward= {
					[1]= {itemID=3,itemIsBind=true,itemcnt=400000,itemname="元宝",},
				},
			text="累计充值达400000元宝可领取：",
		},
	[10003]= {
			id=10003,
			canrepeat=0,
			eventid=5047,
			req=800000,
			reward= {
					[1]= {itemID=3,itemIsBind=true,itemcnt=800000,itemname="元宝",},
				},
			text="累计充值达800000元宝可领取：",
		},
	[10004]= {
			id=10004,
			canrepeat=0,
			eventid=5048,
			req=1500000,
			reward= {
					[1]= {itemID=3,itemIsBind=true,itemcnt=2000000,itemname="元宝",},
				},
			text="累计充值达1500000元宝可领取：",
		},
	[10005]= {
			id=10005,
			canrepeat=0,
			eventid=5049,
			req=3000000,
			reward= {
					[1]= {itemID=3,itemIsBind=true,itemcnt=4500000,itemname="元宝",},
				},
			text="累计充值达3000000元宝可领取：",
		},
	[10006]= {
			id=10006,
			canrepeat=0,
			eventid=5050,
			req=5000000,
			reward= {
					[1]= {itemID=3,itemIsBind=true,itemcnt=10000000,itemname="元宝",},
				},
			text="累计充值达5000000元宝可领取：",
		},
	[10007]= {
			id=10007,
			canrepeat=0,
			eventid=5051,
			req=10000000,
			reward= {
					[1]= {itemID=86030,itemIsBind=false,itemcnt=1,itemname="虚空描点",},
					[2]= {itemID=3,itemIsBind=true,itemcnt=50000000,itemname="元宝",},
				},
			text="累计充值达10000000元宝可领取：",
		},
	[10008]= {
			id=10008,
			canrepeat=0,
			eventid=5052,
			req=50000000,
			reward= {
					
				[1]= {itemID=3,itemIsBind=true,itemcnt=500000000,itemname="元宝",},
					
				},
			text="累计充值达50000000元宝可领取：",
		},
	[10009]= {
			id=10009,
			canrepeat=0,
			eventid=5053,
			req=100000000,
			reward= {
					
				[1]= {itemID=3,itemIsBind=true,itemcnt=1000000000,itemname="元宝",},	
					
				},
			text="累计充值达100000000元宝可领取：",
		},
	[10010]= {
			id=10010,
			canrepeat=0,
			eventid=5054,
			req=200000000,
			reward= {
					
				[1]= {itemID=3,itemIsBind=true,itemcnt=2000000000,itemname="元宝",},	
					
				},
			text="累计充值达200000000元宝可领取：",
		},
	[11001]= {
			id=11001,
			canrepeat=0,
			eventid=5055,
			req=0,
			reward= {
					[1]= {itemID=30357,itemIsBind=true,itemcnt=1,itemname="红包开开乐",},
				},
			text="首次充值可领取：",
		},
	[12001]= {
			id=12001,
			canrepeat=1,
			eventid=5056,
			req=100000,
			reward= {
					[1]= {itemID=30357,itemIsBind=true,itemcnt=2,itemname="元宝开开乐礼包",},
				},
			text="每充值100000元宝可领取",
		},
	[13001]= {
			id=13001,
			canrepeat=1,
			eventid=5057,
			req=100000,
			reward= {
					[1]= {itemID=30346,itemIsBind=true,itemcnt=10,itemname="13级魂石袋",},
				},
			text="单笔充值10元宝可领取",
		},
	[13002]= {
			id=13002,
			canrepeat=1,
			eventid=5058,
			req=400000,
			reward= {
					[1]= {itemID=30346,itemIsBind=true,itemcnt=20,itemname="13级魂石袋",},
					[2]= {itemID=80025,itemIsBind=false,itemcnt=1,itemname="流火异彩(12档)",},
					[3]= {itemID=87101,itemIsBind=false,itemcnt=1,itemname="蚀光魂核（2阶）",},
				},
			text="单笔充值40元宝可领取",
		},
	[13003]= {
			id=13003,
			canrepeat=1,
			eventid=5059,
			req=800000,
			reward= {
					[1]= {itemID=30347,itemIsBind=true,itemcnt=10,itemname="14级魂石袋",},
					[2]= {itemID=4,itemIsBind=true,itemcnt=300000,itemname="仙玉",},
					[3]= {itemID=82083,itemIsBind=false,itemcnt=1,itemname="骷髅",},
					
					
				},
			text="单笔充值80元宝可领取",
		},
	[13004]= {
			id=13004,
			canrepeat=1,
			eventid=5060,
			req=1500000,
			reward= {
					[1]= {itemID=30347,itemIsBind=true,itemcnt=50,itemname="14级魂石袋",},
					[2]= {itemID=82085,itemIsBind=false,itemcnt=1,itemname="暗影魔剑",},
					[3]= {itemID=3,itemIsBind=true,itemcnt=1500000,itemname="元宝",},
				},
			text="单笔充值150元宝可领取",
		},
	[13005]= {
			id=13005,
			canrepeat=1,
			eventid=5061,
			req=2000000,
			reward= {
					[1]= {itemID=51113,itemIsBind=true,itemcnt=1,itemname="神器盒子",},
					[2]= {itemID=3,itemIsBind=true,itemcnt=3000000,itemname="元宝",},
				},
			text="单笔充值200元宝可领取",
		},
	[13006]= {
			id=13006,
			canrepeat=1,
			eventid=5100,
			req=5000000,
			reward= {
					[1]= {itemID=86012,itemIsBind=false,itemcnt=1,itemname="神器女神3-1",},
					[2]= {itemID=51113,itemIsBind=true,itemcnt=3,itemname="神器盒子",},
					[3]= {itemID=3,itemIsBind=true,itemcnt=7000000,itemname="元宝",},
					[4]= {itemID=41111,itemIsBind=true,itemcnt=6000,itemname="紫钻石",},
					[5]= {itemID=41112,itemIsBind=true,itemcnt=6000,itemname="橙钻石",},
					
				},
			text="单笔充值500元宝或以上可领取",
		},
	[13007]= {
			id=13007,
			canrepeat=1,
			eventid=5101,
			req=10000000,
			reward= {
					[1]= {itemID=86018,itemIsBind=false,itemcnt=1,itemname="神器女神4-1",},
					[2]= {itemID=5555,itemIsBind=true,itemcnt=100,itemname="突破蛋",},
					[3]= {itemID=3,itemIsBind=true,itemcnt=40000000,itemname="元宝",},
					[4]= {itemID=4,itemIsBind=true,itemcnt=800000,itemname="仙玉",},
					
				},
			text="单笔充值1000元或以上可领取",
		},
	[13008]= {
			id=13008,
			canrepeat=1,
			eventid=5102,
			req=50000000,
			reward= {
					[1]= {itemID=86024,itemIsBind=false,itemcnt=2,itemname="神器5-1",},
					[2]= {itemID=5555,itemIsBind=true,itemcnt=500,itemname="突破蛋",},
					[3]= {itemID=3,itemIsBind=true,itemcnt=1000000000,itemname="元宝",},
					[4]= {itemID=4,itemIsBind=true,itemcnt=8888888,itemname="仙玉",},
					
				},
			text="单笔充值5000元或以上可领取",
		},
	[13009]= {
			id=13009,
			canrepeat=1,
			eventid=5103,
			req=100000000,
			reward= {
					
					[1]= {itemID=676545075,itemIsBind=true,itemcnt=1,itemname="无限元宝",},
					
				},
			text="单笔充值10000元或以上可领取",
		},
	[14001]= {
			id=14001,
			canrepeat=0,
			eventid=6015,
			req=100,
			reward= {
					[1]= {itemID=40116,itemIsBind=true,itemcnt=5,itemname="藏宝图",},
					[2]= {itemID=30054,itemIsBind=true,itemcnt=1,itemname="6倍经验神符",},
				},
			text="100元宝礼包,限购10个：",
		},
--	[14002]= {
--			id=14002,
--			canrepeat=0,
--			eventid=6016,
--			req=500,
--			reward= {
--					[1]= {itemID=30166,itemIsBind=true,itemcnt=10,itemname="黄金礼票",},
--					[2]= {itemID=30094,itemIsBind=true,itemcnt=1,itemname="小转生灵魄",},
--				},
--			text="500元宝礼包,限购5个：",
--		},
--	[14003]= {
--			id=14003,
--			canrepeat=0,
--			eventid=6017,
--			req=1000,
--			reward= {
--					[1]= {itemID=30310,itemIsBind=true,itemcnt=3,itemname="4级魂石袋",},
--					[2]= {itemID=30430,itemIsBind=true,itemcnt=5,itemname="白银宝箱2",},
--					[3]= {itemID=3,itemIsBind=true,itemcnt=100,itemname="元宝",},
--				},
--			text="1000元宝礼包,限购3个：",
--		},
--	[14004]= {
--			id=14004,
--			canrepeat=0,
--			eventid=6018,
--			req=2000,
--			reward= {
--					[1]= {itemID=30433,itemIsBind=true,itemcnt=1,itemname="5级攻击魂石袋",},
--					[2]= {itemID=30430,itemIsBind=true,itemcnt=5,itemname="白银宝箱2",},
--					[3]= {itemID=30055,itemIsBind=true,itemcnt=1,itemname="10倍经验神符",},
--				},
--			text="2000元宝礼包,限购2个：",
--		},
--	[14005]= {
--			id=14005,
--			canrepeat=0,
--			eventid=6019,
--			req=5000,
--			reward= {
--					[1]= {itemID=30434,itemIsBind=true,itemcnt=1,itemname="6级攻击魂石袋",},
--					[2]= {itemID=40136,itemIsBind=true,itemcnt=1,itemname="血晶",},
--					[3]= {itemID=30166,itemIsBind=true,itemcnt=30,itemname="黄金礼票",},
--				},
--			text="5000元宝礼包,限购1个：",
--		},
--	[14006]= {
--			id=14006,
--			canrepeat=0,
--			eventid=6020,
--			req=10000,
--			reward= {
--					[1]= {itemID=30431,itemIsBind=true,itemcnt=5,itemname="黄金宝箱2",},
--					[2]= {itemID=30051,itemIsBind=true,itemcnt=3,itemname="超级苹果",},
--					[3]= {itemID=39043,itemIsBind=true,itemcnt=3,itemname="超级红玫瑰",},
--				},
--			text="10000元宝礼包,限购1个：",
--		},
--	[14007]= {
--			id=14007,
--			canrepeat=0,
--			eventid=6021,
--			req=20000,
--			reward= {
--					[1]= {itemID=30311,itemIsBind=true,itemcnt=12,itemname="5级魂石袋",},
--					[2]= {itemID=30431,itemIsBind=true,itemcnt=5,itemname="黄金宝箱2",},
--					[3]= {itemID=30059,itemIsBind=true,itemcnt=1,itemname="金蚕王",},
--				},
--			text="20000元宝礼包,限购1个：",
--		},
	[15001]= {
			id=15001,
			canrepeat=0,
			eventid=6025,
			req=100,
			reward= {
					[1]= {itemID=40116,itemIsBind=true,itemcnt=5,itemname="藏宝图",},
				},
			text="100元宝礼包,剩余数量：",
		},
--	[15002]= {
--			id=15002,
--			canrepeat=0,
--			eventid=6026,
--			req=500,
--			reward= {
--					[1]= {itemID=30166,itemIsBind=true,itemcnt=10,itemname="黄金礼票",},
--				},
--			text="500元宝礼包,剩余数量：",
--		},
--	[15003]= {
--			id=15003,
--			canrepeat=0,
--			eventid=6027,
--			req=1000,
--			reward= {
--					[1]= {itemID=30310,itemIsBind=true,itemcnt=3,itemname="4级魂石袋",},
--				},
--			text="1000元宝礼包,剩余数量：",
--		},
--	[15004]= {
--			id=15004,
--			canrepeat=0,
--			eventid=6028,
--			req=2000,
--			reward= {
--					[1]= {itemID=30433,itemIsBind=true,itemcnt=3,itemname="5级攻击魂石袋",},
--				},
--			text="2000元宝礼包,剩余数量：",
--		},
--	[15005]= {
--			id=15005,
--			canrepeat=0,
--			eventid=6029,
--			req=5000,
--			reward= {
--					[1]= {itemID=30434,itemIsBind=true,itemcnt=3,itemname="6级攻击魂石袋",},
--				},
--			text="5000元宝礼包,剩余数量：",
--		},
--	[15006]= {
--			id=15006,
--			canrepeat=0,
--			eventid=6030,
--			req=10000,
--			reward= {
--					[1]= {itemID=30431,itemIsBind=true,itemcnt=8,itemname="黄金宝箱2",},
--				},
--			text="10000元宝礼包,剩余数量：",
--		},
--	[15007]= {
--			id=15007,
--			canrepeat=0,
--			eventid=6031,
--			req=20000,
--			reward= {
--					[1]= {itemID=30311,itemIsBind=true,itemcnt=30,itemname="5级魂石袋",},
--				},
--			text="20000元宝礼包,剩余数量：",
--		},
}
