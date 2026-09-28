if not (type(gdGuilddata)=="table") then
	gdGuilddata = {}
end

gdGuilddata[1] = {level=1,maxmember=30,praycnt=20,}
gdGuilddata[2] = {level=2,maxmember=35,praycnt=23,}
gdGuilddata[3] = {level=3,maxmember=40,praycnt=26,}
gdGuilddata[4] = {level=4,maxmember=45,praycnt=29,}
gdGuilddata[5] = {level=5,maxmember=50,praycnt=32,}
gdGuilddata[6] = {level=6,maxmember=55,praycnt=35,}
gdGuilddata[7] = {level=7,maxmember=60,praycnt=38,}
gdGuilddata[8] = {level=8,maxmember=65,praycnt=41,}
gdGuilddata[9] = {level=9,maxmember=70,praycnt=44,}
gdGuilddata[10] = {level=10,maxmember=75,praycnt=47,}
gdGuilddata[11] = {level=11,maxmember=80,praycnt=50,}
gdGuilddata[12] = {level=12,maxmember=85,praycnt=53,}
gdGuilddata[13] = {level=13,maxmember=90,praycnt=56,}
gdGuilddata[14] = {level=14,maxmember=95,praycnt=59,}
gdGuilddata[15] = {level=15,maxmember=100,praycnt=62,}
gdGuilddata[16] = {level=16,maxmember=105,praycnt=65,}
gdGuilddata[17] = {level=17,maxmember=110,praycnt=68,}
gdGuilddata[18] = {level=18,maxmember=115,praycnt=71,}
gdGuilddata[19] = {level=19,maxmember=120,praycnt=74,}
gdGuilddata[20] = {level=20,maxmember=125,praycnt=77,}


if not (type(gdGuildJobReward)=="table") then
	gdGuildJobReward = {}
end

gdGuildJobReward =
{
	[0]= {count=1,job=0,nickname="普通会员",reward=40048,},
	[1]= {count=2,job=1,nickname="会长",reward=40048,},
	[2]= {count=2,job=2,nickname="副会长",reward=40048,},
	[3]= {count=1,job=3,nickname="精英",reward=40048,},
}


if not (type(gdGuildPrayExp)=="table") then
	gdGuildPrayExp = {}
end

gdGuildPrayExp =
{
	[30]= {goldexp=27192,honorexp=20394,lvl=30,moneyexp=13596,},
	[31]= {goldexp=35080,honorexp=26310,lvl=31,moneyexp=17540,},
	[32]= {goldexp=45292,honorexp=33969,lvl=32,moneyexp=22646,},
	[33]= {goldexp=58504,honorexp=43878,lvl=33,moneyexp=29252,},
	[34]= {goldexp=75604,honorexp=56703,lvl=34,moneyexp=37802,},
	[35]= {goldexp=97736,honorexp=73302,lvl=35,moneyexp=48868,},
	[36]= {goldexp=107424,honorexp=80568,lvl=36,moneyexp=53712,},
	[37]= {goldexp=118088,honorexp=88566,lvl=37,moneyexp=59044,},
	[38]= {goldexp=129856,honorexp=97392,lvl=38,moneyexp=64928,},
	[39]= {goldexp=142804,honorexp=107103,lvl=39,moneyexp=71402,},
	[40]= {goldexp=157064,honorexp=117798,lvl=40,moneyexp=78532,},
	[41]= {goldexp=172760,honorexp=129570,lvl=41,moneyexp=86380,},
	[42]= {goldexp=190044,honorexp=142533,lvl=42,moneyexp=95022,},
	[43]= {goldexp=209052,honorexp=156789,lvl=43,moneyexp=104526,},
	[44]= {goldexp=230000,honorexp=172500,lvl=44,moneyexp=115000,},
	[45]= {goldexp=253044,honorexp=189783,lvl=45,moneyexp=126522,},
	[46]= {goldexp=278404,honorexp=208803,lvl=46,moneyexp=139202,},
	[47]= {goldexp=306484,honorexp=229863,lvl=47,moneyexp=153242,},
	[48]= {goldexp=344916,honorexp=258687,lvl=48,moneyexp=172458,},
	[49]= {goldexp=385092,honorexp=288819,lvl=49,moneyexp=192546,},
	[50]= {goldexp=428252,honorexp=321189,lvl=50,moneyexp=214126,},
	[51]= {goldexp=469160,honorexp=351870,lvl=51,moneyexp=234580,},
	[52]= {goldexp=517688,honorexp=388266,lvl=52,moneyexp=258844,},
	[53]= {goldexp=556936,honorexp=417702,lvl=53,moneyexp=278468,},
	[54]= {goldexp=599512,honorexp=449634,lvl=54,moneyexp=299756,},
	[55]= {goldexp=630976,honorexp=473232,lvl=55,moneyexp=315488,},
	[56]= {goldexp=702844,honorexp=527133,lvl=56,moneyexp=351422,},
	[57]= {goldexp=796692,honorexp=597519,lvl=57,moneyexp=398346,},
	[58]= {goldexp=885160,honorexp=663870,lvl=58,moneyexp=442580,},
	[59]= {goldexp=982944,honorexp=737208,lvl=59,moneyexp=491472,},
	[60]= {goldexp=1108428,honorexp=831321,lvl=60,moneyexp=554214,},
	[61]= {goldexp=1248540,honorexp=936405,lvl=61,moneyexp=624270,},
	[62]= {goldexp=1362912,honorexp=1022184,lvl=62,moneyexp=681456,},
	[63]= {goldexp=1503024,honorexp=1127268,lvl=63,moneyexp=751512,},
	[64]= {goldexp=1642936,honorexp=1232202,lvl=64,moneyexp=821468,},
	[65]= {goldexp=1782952,honorexp=1337214,lvl=65,moneyexp=891476,},
	[66]= {goldexp=1931524,honorexp=1448643,lvl=66,moneyexp=965762,},
	[67]= {goldexp=2110296,honorexp=1582722,lvl=67,moneyexp=1055148,},
	[68]= {goldexp=2284708,honorexp=1713531,lvl=68,moneyexp=1142354,},
	[69]= {goldexp=2469156,honorexp=1851867,lvl=69,moneyexp=1234578,},
	[70]= {goldexp=2695788,honorexp=2021841,lvl=70,moneyexp=1347894,},
}


if not (type(gdGuildBuild)=="table") then
	gdGuildBuild = {}
end

gdGuildBuild =
{
	[17]= {
			id=17,
			name="行会主殿",
			baselvl=1,
			lvlup= {
					[1]= {lvl=1,upmoney=10000000,uptime=36000,},
					[2]= {lvl=2,upmoney=13000000,uptime=50400,},
					[3]= {lvl=3,upmoney=16000000,uptime=64800,},
					[4]= {lvl=4,upmoney=19000000,uptime=79200,},
					[5]= {lvl=5,upmoney=22000000,uptime=93600,},
					[6]= {lvl=6,upmoney=25000000,uptime=108000,},
					[7]= {lvl=7,upmoney=28000000,uptime=122400,},
					[8]= {lvl=8,upmoney=31000000,uptime=136800,},
					[9]= {lvl=9,upmoney=34000000,uptime=151200,},
					[10]= {lvl=10,upmoney=37000000,uptime=165600,},
					[11]= {lvl=11,upmoney=40000000,uptime=180000,},
					[12]= {lvl=12,upmoney=43000000,uptime=194400,},
					[13]= {lvl=13,upmoney=46000000,uptime=208800,},
					[14]= {lvl=14,upmoney=49000000,uptime=223200,},
					[15]= {lvl=15,upmoney=52000000,uptime=237600,},
					[16]= {lvl=16,upmoney=55000000,uptime=252000,},
					[17]= {lvl=17,upmoney=58000000,uptime=266400,},
					[18]= {lvl=18,upmoney=61000000,uptime=280800,},
					[19]= {lvl=19,upmoney=64000000,uptime=295200,},
				},
			maxlvl=20,
			openlvl=1,
		},
	[18]= {
			id=18,
			name="行会关公",
			baselvl=1,
			lvlup= {
					[1]= {lvl=1,upmoney=0,uptime=0,},
				},
			maxlvl=1,
			openlvl=1,
		},
	[19]= {
			id=19,
			name="行会福利",
			baselvl=1,
			lvlup= {
					[1]= {lvl=1,upmoney=0,uptime=0,},
				},
			maxlvl=1,
			openlvl=3,
		},
	[20]= {
			id=20,
			name="行会探险",
			baselvl=1,
			lvlup= {
					[1]= {lvl=1,upmoney=6000000,uptime=21600,},
					[2]= {lvl=2,upmoney=9000000,uptime=32400,},
					[3]= {lvl=3,upmoney=12000000,uptime=43200,},
					[4]= {lvl=4,upmoney=15000000,uptime=54000,},
					[5]= {lvl=5,upmoney=18000000,uptime=64800,},
					[6]= {lvl=6,upmoney=21000000,uptime=75600,},
					[7]= {lvl=7,upmoney=24000000,uptime=86400,},
					[8]= {lvl=8,upmoney=27000000,uptime=97200,},
					[9]= {lvl=9,upmoney=30000000,uptime=108000,},
					[10]= {lvl=10,upmoney=33000000,uptime=118800,},
					[11]= {lvl=11,upmoney=36000000,uptime=129600,},
					[12]= {lvl=12,upmoney=39000000,uptime=140400,},
					[13]= {lvl=13,upmoney=42000000,uptime=151200,},
					[14]= {lvl=14,upmoney=45000000,uptime=162000,},
					[15]= {lvl=15,upmoney=48000000,uptime=172800,},
					[16]= {lvl=16,upmoney=51000000,uptime=183600,},
					[17]= {lvl=17,upmoney=54000000,uptime=194400,},
					[18]= {lvl=18,upmoney=57000000,uptime=205200,},
					[19]= {lvl=19,upmoney=60000000,uptime=216000,},
				},
			maxlvl=20,
			openlvl=4,
		},
	[21]= {
			id=21,
			name="行会神兽",
			baselvl=1,
			lvlup= {
					[1]= {lvl=1,upmoney=8000000,uptime=28800,},
					[2]= {lvl=2,upmoney=11000000,uptime=39600,},
					[3]= {lvl=3,upmoney=14000000,uptime=50400,},
					[4]= {lvl=4,upmoney=17000000,uptime=61200,},
					[5]= {lvl=5,upmoney=20000000,uptime=72000,},
					[6]= {lvl=6,upmoney=23000000,uptime=82800,},
					[7]= {lvl=7,upmoney=26000000,uptime=93600,},
					[8]= {lvl=8,upmoney=29000000,uptime=104400,},
					[9]= {lvl=9,upmoney=32000000,uptime=115200,},
					[10]= {lvl=10,upmoney=35000000,uptime=126000,},
					[11]= {lvl=11,upmoney=38000000,uptime=136800,},
					[12]= {lvl=12,upmoney=41000000,uptime=147600,},
					[13]= {lvl=13,upmoney=44000000,uptime=158400,},
					[14]= {lvl=14,upmoney=47000000,uptime=169200,},
					[15]= {lvl=15,upmoney=50000000,uptime=180000,},
					[16]= {lvl=16,upmoney=53000000,uptime=190800,},
					[17]= {lvl=17,upmoney=56000000,uptime=201600,},
					[18]= {lvl=18,upmoney=59000000,uptime=212400,},
					[19]= {lvl=19,upmoney=62000000,uptime=223200,},
				},
			maxlvl=20,
			openlvl=5,
		},
	[22]= {
			id=22,
			name="行会商店",
			baselvl=1,
			lvlup= {
					[1]= {lvl=1,upmoney=4000000,uptime=14400,},
					[2]= {lvl=2,upmoney=6000000,uptime=21600,},
					[3]= {lvl=3,upmoney=8000000,uptime=28800,},
					[4]= {lvl=4,upmoney=10000000,uptime=36000,},
					[5]= {lvl=5,upmoney=12000000,uptime=43200,},
					[6]= {lvl=6,upmoney=14000000,uptime=50400,},
					[7]= {lvl=7,upmoney=16000000,uptime=57600,},
					[8]= {lvl=8,upmoney=18000000,uptime=64800,},
					[9]= {lvl=9,upmoney=20000000,uptime=72000,},
					[10]= {lvl=10,upmoney=22000000,uptime=79200,},
					[11]= {lvl=11,upmoney=24000000,uptime=86400,},
					[12]= {lvl=12,upmoney=26000000,uptime=93600,},
					[13]= {lvl=13,upmoney=28000000,uptime=100800,},
					[14]= {lvl=14,upmoney=30000000,uptime=108000,},
					[15]= {lvl=15,upmoney=32000000,uptime=115200,},
					[16]= {lvl=16,upmoney=34000000,uptime=122400,},
					[17]= {lvl=17,upmoney=36000000,uptime=129600,},
					[18]= {lvl=18,upmoney=38000000,uptime=136800,},
					[19]= {lvl=19,upmoney=40000000,uptime=144000,},
				},
			maxlvl=20,
			openlvl=1,
		},
	[23]= {
			id=23,
			name="行会光环",
			baselvl=1,
			lvlup= {
					[1]= {lvl=1,upmoney=0,uptime=0,},
				},
			maxlvl=1,
			openlvl=2,
		},
}

if not(type(gdGuildGuanghuan) == "table") then
	gdGuildGuanghuan = {}
end

gdGuildGuanghuan =
{
	[1]= {name="嗜血光环",buffdata=10,buffdesc="伤害输出+10%",bufftype="伤害输出",cost=100000,gene_id=70001,time=10,},
	[2]= {name="圣盾光环",buffdata=50,buffdesc="最大物理防御+50",bufftype="最大物理防御",cost=100000,gene_id=70002,time=10,},
	[3]= {name="神赐光环",buffdata=50,buffdesc="最大魔法防御+50",bufftype="最大魔法防御",cost=100000,gene_id=70003,time=10,},
	[4]= {name="永恒光环",buffdata=5,buffdesc="生命值上限+5%",bufftype="生命值上限",cost=100000,gene_id=70004,time=10,},
	[5]= {name="秘法光环",buffdata=5,buffdesc="魔法值上限+5%",bufftype="魔法值上限",cost=100000,gene_id=70005,time=10,},
	[6]= {name="先祖光环",buffdata=20,buffdesc="杀怪经验+20%",bufftype="杀怪经验",cost=100000,gene_id=70006,time=30,},
}

if not(type(gdGuildTanxian) == "table") then
	gdGuildTanxian = {}
end

gdGuildTanxian =
{
	count= {
			[1]=6,
			[2]=6,
			[3]=7,
			[4]=7,
			[5]=8,
			[6]=8,
			[7]=9,
			[8]=9,
			[9]=10,
			[10]=10,
			[11]=11,
			[12]=11,
			[13]=12,
			[14]=12,
			[15]=13,
			[16]=13,
			[17]=14,
			[18]=14,
			[19]=15,
			[20]=15,
		},
	items= {
			[1]= {
					probability=10,
					[40053]= {probability=100,},
				},
			[2]= {
					probability=10,
					[30208]= {probability=100,},
				},
			[3]= {
					probability=10,
					[30064]= {probability=100,},
				},
			[4]= {
					probability=10,
					[30017]= {probability=30,},
					[30018]= {probability=70,},
				},
			[5]= {
					probability=10,
					[30033]= {probability=60,},
					[30034]= {probability=40,},
				},
			[6]= {
					probability=10,
					[39017]= {probability=50,},
					[39018]= {probability=50,},
				},
			[7]= {
					probability=10,
					[39024]= {probability=50,},
					[39026]= {probability=50,},
				},
			[8]= {
					probability=10,
					[30046]= {probability=30,},
					[39029]= {probability=70,},
				},
			[9]= {
					probability=10,
					[30052]= {probability=50,},
					[30053]= {probability=50,},
				},
			[10]= {
					probability=10,
					[30002]= {probability=40,},
					[30003]= {probability=30,},
					[30005]= {probability=30,},
				},
		},
}

if not(type(gdGuildWelfare) == "table") then
	gdGuildWelfare = {}
end

gdGuildWelfare =
{
	[1]= {contribution=25,cost=1000000,cost_type=1,item=40081,},
	[2]= {contribution=25,cost=1000000,cost_type=1,item=30046,},
	[3]= {contribution=25,cost=1000000,cost_type=1,item=30003,},
	[4]= {contribution=50,cost=100,cost_type=2,item=30042,},
}
