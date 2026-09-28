if not (type(tActivityCfgPatch)=="table") then
	tActivityCfgPatch = {}
end

tActivityCfgPatch = {
	-- "魂石回馈"
	[20407] = {
		update = function ()
			tActivityCfgVer[20407].Ver = 1

			-- delete client old data
			local OpenID = 20407
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end
            gdEventData[5068] = {
								id=5068,
								name="魂石等级达10级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4001,
								getcnt=-1,
								openworldid=20407,
								req=10,
							}
			gdEventData[5016] = {
								id=5016,
								name="魂石等级达11级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4002,
								getcnt=-1,
								openworldid=20407,
								req=11,
							}
			gdEventData[5069] = {
								id=5069,
								name="魂石等级达12级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4003,
								getcnt=-1,
								openworldid=20407,
								req=12,
							}
			gdEventData[5017] = {
								id=5017,
								name="魂石等级达13级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4004,
								getcnt=-1,
								openworldid=20407,
								req=13,
							}
			gdEventData[5018] = {
								id=5018,
								name="魂石等级达14级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4005,
								getcnt=-1,
								openworldid=20407,
								req=14,
							}
			gdEventData[5114] = {
								id=5114,
								name="魂石等级达15级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4006,
								getcnt=-1,
								openworldid=20407,
								req=15,
							}
			gdEventData[5115] = {
								id=5115,
								name="魂石等级达16级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4007,
								getcnt=-1,
								openworldid=20407,
								req=16,
							}
			gdEventData[5110] = {
								id=5110,
								name="魂石等级达17级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4008,
								getcnt=-1,
								openworldid=20407,
								req=12,
							}
			gdEventData[5111] = {
								id=5111,
								name="魂石等级达18级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4009,
								getcnt=-1,
								openworldid=20407,
								req=18,
							}
			gdEventData[5116] = {
								id=5116,
								name="魂石等级达19级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4010,
								getcnt=-1,
								openworldid=20407,
								req=19,
							}
			gdEventData[5117] = {
								id=5117,
								name="魂石等级达20级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=4011,
								getcnt=-1,
								openworldid=20407,
								req=20,
							}
			gdEventAbbr["huikui71"] = 5110
			gdEventAbbr["huikui96"] = 5117
			gdEventAbbr["huikui95"] = 5116
			gdEventAbbr["huikui20"] = 5018
			gdEventAbbr["huikui17"] = 5016
			gdEventAbbr["huikui72"] = 5111
			gdEventAbbr["huikui70"] = 5115
			gdEventAbbr["huikui16"] = 5068
			gdEventAbbr["huikui69"] = 5114
			gdEventAbbr["huikui19"] = 5017
			gdEventAbbr["huikui18"] = 5069
			gdRepayReward[4001] = {
								id=4001,
								canrepeat=1,
								eventid=5068,
								req=10,
								reward= {
										[1]= {itemID=30315,itemIsBind=true,itemcnt=2,itemname="9级魂石袋",},
									},
								text="魂石等级达10级可领取：",
							}
			gdRepayReward[4002] = {
								id=4002,
								canrepeat=1,
								eventid=5016,
								req=11,
								reward= {
										[1]= {itemID=30316,itemIsBind=true,itemcnt=2,itemname="10级魂石袋",},
									},
								text="魂石等级达11级可领取：",
							}
			gdRepayReward[4003] = {
								id=4003,
								canrepeat=1,
								eventid=5069,
								req=12,
								reward= {
										[1]= {itemID=30317,itemIsBind=true,itemcnt=2,itemname="11级魂石袋",},
									},
								text="魂石等级达12级可领取：",
							}
			gdRepayReward[4004] = {
								id=4004,
								canrepeat=1,
								eventid=5017,
								req=13,
								reward= {
										[1]= {itemID=30345,itemIsBind=true,itemcnt=2,itemname="12级魂石袋",},
									},
								text="魂石等级达13级可领取：",
							}
			gdRepayReward[4005] = {
								id=4005,
								canrepeat=1,
								eventid=5018,
								req=14,
								reward= {
										[1]= {itemID=30346,itemIsBind=true,itemcnt=2,itemname="13级魂石袋",},
									},
								text="魂石等级达14级可领取：",
							}
			gdRepayReward[4006] = {
								id=4006,
								canrepeat=1,
								eventid=5114,
								req=15,
								reward= {
										[1]= {itemID=30347,itemIsBind=true,itemcnt=2,itemname="14级魂石袋",},
									},
								text="魂石等级达15级可领取：",
							}
			gdRepayReward[4007] = {
								id=4007,
								canrepeat=1,
								eventid=5115,
								req=16,
								reward= {
										[1]= {itemID=30348,itemIsBind=true,itemcnt=2,itemname="15级魂石袋",},
									},
								text="魂石等级达16级可领取：",
							}
			gdRepayReward[4008] = {
								id=4008,
								canrepeat=1,
								eventid=5110,
								req=17,
								reward= {
										[1]= {itemID=30348,itemIsBind=true,itemcnt=4,itemname="15级魂石袋",},
									},
								text="魂石等级达17级可领取：",
							}
			gdRepayReward[4009] = {
								id=4009,
								canrepeat=1,
								eventid=5111,
								req=18,
								reward= {
										[1]= {itemID=30348,itemIsBind=true,itemcnt=10,itemname="15级魂石袋",},
									},
								text="魂石等级达18级可领取：",
							}
			gdRepayReward[4010] = {
								id=4010,
								canrepeat=1,
								eventid=5116,
								req=19,
								reward= {
										[1]= {itemID=30348,itemIsBind=true,itemcnt=20,itemname="15级魂石袋",},
									},
								text="魂石等级达19级可领取：",
							}
			gdRepayReward[4011] = {
								id=4011,
								canrepeat=1,
								eventid=5117,
								req=20,
								reward= {
										[1]= {itemID=30348,itemIsBind=true,itemcnt=30,itemname="15级魂石袋",},
									},
								text="魂石等级达20级可领取：",
							}
			gdEventWorldDataYLink[20407] = {[1]=5068,[2]=5016,[3]=5069,[4]=5017,[5]=5018,[6]=5114,[7]=5115,[8]=5110,[9]=5111,[10]=5116,[11]=5117,}
			gdActivityText[10] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="魂石回馈",textintroduce="活动期间，每合成一颗魂石可在活动回馈处领取低于合成等级2级的魂石袋*2！",}
		end,
	},
	-- "翅膀回馈"
	[20408] = {
		update = function ()
			tActivityCfgVer[20408].Ver = 1

			-- delete client old data
			local OpenID = 20408
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5020] = {
								id=5020,
								name="翅膀等级达1级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5010,
								getcnt=-1,
								openworldid=20408,
								req=1,
							}
			gdEventData[5021] = {
								id=5021,
								name="翅膀等级达2级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5011,
								getcnt=-1,
								openworldid=20408,
								req=2,
							}
			gdEventData[5024] = {
								id=5024,
								name="翅膀等级达5级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5001,
								getcnt=-1,
								openworldid=20408,
								req=5,
							}
			gdEventData[5088] = {
								id=5088,
								name="翅膀等级达6级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5002,
								getcnt=-1,
								openworldid=20408,
								req=6,
							}
			gdEventData[5089] = {
								id=5089,
								name="翅膀等级达7级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5003,
								getcnt=-1,
								openworldid=20408,
								req=7,
							}
			gdEventData[5090] = {
								id=5090,
								name="翅膀等级达8级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5004,
								getcnt=-1,
								openworldid=20408,
								req=8,
							}
			gdEventData[5091] = {
								id=5091,
								name="翅膀等级达9级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5005,
								getcnt=-1,
								openworldid=20408,
								req=9,
							}
			gdEventData[5092] = {
								id=5092,
								name="翅膀等级达10级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5006,
								getcnt=-1,
								openworldid=20408,
								req=10,
							}
			gdEventData[5093] = {
								id=5093,
								name="翅膀等级达11级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=5007,
								getcnt=-1,
								openworldid=20408,
								req=11,
							}
			gdEventAbbr["huikui21"] = 5020
			gdEventAbbr["huikui89"] = 5088
			gdEventAbbr["huikui90"] = 5089
			gdEventAbbr["huikui94"] = 5093
			gdEventAbbr["huikui25"] = 5024
			gdEventAbbr["huikui92"] = 5091
			gdEventAbbr["huikui93"] = 5092
			gdEventAbbr["huikui22"] = 5021
			gdEventAbbr["huikui91"] = 5090
			gdRepayReward[5001] = {
								id=5001,
								canrepeat=1,
								eventid=5020,
								req=3,
								reward= {
										[1]= {itemID=30427,itemIsBind=true,itemcnt=1,itemname="神翼宝箱",},
									},
								text="翅膀等级达3级可领取：",
							}
			gdRepayReward[5002] = {
								id=5002,
								canrepeat=1,
								eventid=5021,
								req=4,
								reward= {
										[1]= {itemID=30427,itemIsBind=true,itemcnt=2,itemname="神翼宝箱",},
									},
								text="翅膀等级达4级可领取：",
							}
			gdRepayReward[5003] = {
								id=5003,
								canrepeat=1,
								eventid=5024,
								req=5,
								reward= {
										[1]= {itemID=30427,itemIsBind=true,itemcnt=5,itemname="神翼宝箱",},
									},
								text="翅膀等级达5级可领取：",
							}
			gdRepayReward[5004] = {
								id=5004,
								canrepeat=1,
								eventid=5088,
								req=6,
								reward= {
										[1]= {itemID=30311,itemIsBind=true,itemcnt=8,itemname="5级魂石袋",},
									},
								text="翅膀等级达6级可领取：",
							}
			gdRepayReward[5005] = {
								id=5005,
								canrepeat=1,
								eventid=5089,
								req=7,
								reward= {
										[1]= {itemID=30312,itemIsBind=true,itemcnt=5,itemname="6级魂石袋",},
									},
								text="翅膀等级达7级可领取：",
							}
			gdRepayReward[5006] = {
								id=5006,
								canrepeat=1,
								eventid=5090,
								req=8,
								reward= {
										[1]= {itemID=30312,itemIsBind=true,itemcnt=10,itemname="6级魂石袋",},
									},
								text="翅膀等级达8级可领取：",
							}
			gdRepayReward[5007] = {
								id=5007,
								canrepeat=1,
								eventid=5091,
								req=9,
								reward= {
										[1]= {itemID=30313,itemIsBind=true,itemcnt=8,itemname="7级魂石袋",},
									},
								text="翅膀等级达9级可领取：",
							}
			gdRepayReward[5008] = {
								id=5008,
								canrepeat=1,
								eventid=5092,
								req=10,
								reward= {
										[1]= {itemID=30314,itemIsBind=true,itemcnt=5,itemname="8级魂石袋",},
									},
								text="翅膀等级达10级可领取：",
							}
			gdRepayReward[5009] = {
								id=5009,
								canrepeat=1,
								eventid=5093,
								req=11,
								reward= {
										[1]= {itemID=30314,itemIsBind=true,itemcnt=10,itemname="8级魂石袋",},
									},
								text="翅膀等级达11级可领取：",
							}
			
			gdEventWorldDataYLink[20408] = {[1]=5020,[2]=5021,[3]=5024,[4]=5088,[5]=5089,[6]=5090,[7]=5091,[8]=5092,[9]=5093,}
			gdActivityText[11] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="翅膀回馈",textintroduce="活动期间内，合成翅膀达到相对应的等级就可以领取对应翅膀合成礼包！",}
		end,
	},
	-- "寻宝回馈"
	[20409] = {
		update = function ()
			tActivityCfgVer[20409].Ver = 1

			-- delete client old data
			local OpenID = 20409
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end
			gdEventData[5025] = {
								id=5025,
								name="寻宝达10次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6001,
								getcnt=1,
								openworldid=20409,
								req=10,
							}
			gdEventData[5026] = {
								id=5026,
								name="寻宝达30次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6002,
								getcnt=1,
								openworldid=20409,
								req=30,
							}
			gdEventData[5027] = {
								id=5027,
								name="寻宝达50次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6003,
								getcnt=1,
								openworldid=20409,
								req=50,
							}
			gdEventData[5028] = {
								id=5028,
								name="寻宝达100次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6004,
								getcnt=1,
								openworldid=20409,
								req=100,
							}
			gdEventData[5029] = {
								id=5029,
								name="寻宝达300次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6005,
								getcnt=1,
								openworldid=20409,
								req=300,
							}
			gdEventData[5095] = {
								id=5095,
								name="寻宝达500次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6006,
								getcnt=1,
								openworldid=20409,
								req=500,
							}
			gdEventData[5096] = {
								id=5096,
								name="寻宝达1000次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6007,
								getcnt=1,
								openworldid=20409,
								req=1000,
							}
			gdEventData[5097] = {
								id=5097,
								name="寻宝达2000次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6008,
								getcnt=1,
								openworldid=20409,
								req=2000,
							}
			gdEventData[5098] = {
								id=5098,
								name="寻宝达3000次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6009,
								getcnt=1,
								openworldid=20409,
								req=3000,
							}
			gdEventData[5099] = {
								id=5099,
								name="寻宝达5000次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6010,
								getcnt=1,
								openworldid=20409,
								req=5000,
							}
			gdEventData[5104] = {
								id=5104,
								name="寻宝达10000次可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6011,
								getcnt=1,
								openworldid=20409,
								req=10000,
							}
			gdEventAbbr["huikui63"] = 5104
			gdEventAbbr["huikui28"] = 5097
			gdEventAbbr["huikui26"] = 5095
			gdEventAbbr["huikui30"] = 5099
			gdEventAbbr["huikui29"] = 5098
			gdEventAbbr["huikui27"] = 5096
			gdRepayReward[6001] = {
								id=6001,
								canrepeat=0,
								eventid=5025,
								req=5,
								reward= {
										[1]= {itemID=30455,itemIsBind=true,itemcnt=1,itemname="ios魂石福袋",},
									},
								text="寻宝达5次可领取：",
							}
			gdRepayReward[6003] = {
								id=6003,
								canrepeat=0,
								eventid=5027,
								req=50,
								reward= {
										[1]= {itemID=30455,itemIsBind=true,itemcnt=10,itemname="ios魂石福袋",},
									},
								text="寻宝达50次可领取：",
							}
			gdRepayReward[6002] = {
								id=6002,
								canrepeat=0,
								eventid=5026,
								req=20,
								reward= {
										[1]= {itemID=30455,itemIsBind=true,itemcnt=4,itemname="ios魂石福袋",},
									},
								text="寻宝达20次可领取：",
							}
			gdRepayReward[6005] = {
								id=6005,
								canrepeat=0,
								eventid=5029,
								req=200,
								reward= {
										[1]= {itemID=30306,itemIsBind=true,itemcnt=10,itemname="磐龙宝箱",},
									},
								text="寻宝达200次可领取：",
							}
			gdRepayReward[6004] = {
								id=6004,
								canrepeat=0,
								eventid=5028,
								req=100,
								reward= {
										[1]= {itemID=30455,itemIsBind=true,itemcnt=20,itemname="ios魂石福袋",},
									},
								text="寻宝达100次可领取：",
							}
			gdEventWorldDataYLink[20409] = {[1]=5025,[2]=5026,[3]=5027,[4]=5028,[5]=5029,[6]=5095,[7]=5096,[8]=5097,[9]=5098,[10]=5099,[11]=5104,}
			gdActivityText[12] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="寻宝回馈",textintroduce="活动期间内，只要寻宝次数达到指定要求即可获得返利大奖！",}
		end,
	},
	-- "时装回馈"
	[20410] = {
		update = function ()
			tActivityCfgVer[20410].Ver = 1

			-- delete client old data
			local OpenID = 20410
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5030] = {
								id=5030,
								name="时装达1级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=7001,
								getcnt=3,
								openworldid=20410,
								req=1,
							}
			gdEventData[5031] = {
								id=5031,
								name="时装达3级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=7002,
								getcnt=3,
								openworldid=20410,
								req=3,
							}
			gdEventData[5032] = {
								id=5032,
								name="时装达5级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=7003,
								getcnt=3,
								openworldid=20410,
								req=5,
							}
			gdEventData[5033] = {
								id=5033,
								name="时装达7级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=7004,
								getcnt=3,
								openworldid=20410,
								req=7,
							}
			gdEventData[5034] = {
								id=5034,
								name="时装达9级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=7005,
								getcnt=3,
								openworldid=20410,
								req=9,
							}
			gdEventAbbr["huikui33"] = 5032
			gdEventAbbr["huikui34"] = 5033
			gdEventAbbr["huikui35"] = 5034
			gdEventAbbr["huikui31"] = 5030
			gdEventAbbr["huikui32"] = 5031
			gdRepayReward[7001] = {
								id=7001,
								canrepeat=1,
								eventid=5030,
								req=3,
								reward= {
										[1]= {itemID=30309,itemIsBind=true,itemcnt=3,itemname="3级魂石袋",},
									},
								text="时装达3级可领取：",
							}
			gdRepayReward[7003] = {
								id=7003,
								canrepeat=1,
								eventid=5032,
								req=7,
								reward= {
										[1]= {itemID=30311,itemIsBind=true,itemcnt=3,itemname="5级魂石袋",},
									},
								text="时装达7级可领取：",
							}
			gdRepayReward[7004] = {
								id=7004,
								canrepeat=1,
								eventid=5033,
								req=9,
								reward= {
										[1]= {itemID=80004,itemIsBind=true,itemcnt=1,itemname="粉翼彩蝶(4档)",},
									},
								text="时装达9级可领取：",
							}
			gdRepayReward[7002] = {
								id=7002,
								canrepeat=1,
								eventid=5031,
								req=5,
								reward= {
										[1]= {itemID=30310,itemIsBind=true,itemcnt=3,itemname="4级魂石袋",},
									},
								text="时装达5级可领取：",
							}
			gdEventWorldDataYLink[20410] = {[1]=5030,[2]=5031,[3]=5032,[4]=5033,[5]=5034,}
			gdActivityText[13] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="时装回馈",textintroduce="活动期间，时装升阶到对应等级领取奖励，每档限领一次。",}
		end,
	},
	-- "幻武回馈"
	[20411] = {
		update = function ()
			tActivityCfgVer[20411].Ver = 1

			-- delete client old data
			local OpenID = 20411
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5035] = {
								id=5035,
								name="幻武达1级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=8001,
								getcnt=3,
								openworldid=20411,
								req=1,
							}
			gdEventData[5036] = {
								id=5036,
								name="幻武达3级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=8002,
								getcnt=3,
								openworldid=20411,
								req=3,
							}
			gdEventData[5037] = {
								id=5037,
								name="幻武达5级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=8003,
								getcnt=3,
								openworldid=20411,
								req=5,
							}
			gdEventData[5038] = {
								id=5038,
								name="幻武达7级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=8004,
								getcnt=3,
								openworldid=20411,
								req=7,
							}
			gdEventData[5039] = {
								id=5039,
								name="幻武达9级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=8005,
								getcnt=3,
								openworldid=20411,
								req=9,
							}
			gdEventAbbr["huikui36"] = 5035
			gdEventAbbr["huikui37"] = 5036
			gdEventAbbr["huikui38"] = 5037
			gdEventAbbr["huikui39"] = 5038
			gdEventAbbr["huikui40"] = 5039
			gdRepayReward[8001] = {
								id=8001,
								canrepeat=1,
								eventid=5035,
								req=3,
								reward= {
										[1]= {itemID=40071,itemIsBind=true,itemcnt=5,itemname="幻武水晶",},
									},
								text="幻武达3级可领取：",
							}
			gdRepayReward[8003] = {
								id=8003,
								canrepeat=1,
								eventid=5037,
								req=7,
								reward= {
										[1]= {itemID=40143,itemIsBind=true,itemcnt=2,itemname="磐龙许愿盒",},
									},
								text="幻武达7级可领取：",
							}
			gdRepayReward[8004] = {
								id=8004,
								canrepeat=1,
								eventid=5038,
								req=9,
								reward= {
										[1]= {itemID=40015,itemIsBind=true,itemcnt=25,itemname="战神晶魄",},
									},
								text="幻武达9级可领取：",
							}
			gdRepayReward[8002] = {
								id=8002,
								canrepeat=1,
								eventid=5036,
								req=5,
								reward= {
										[1]= {itemID=40016,itemIsBind=true,itemcnt=60,itemname="足迹晶魄",},
									},
								text="幻武达5级可领取：",
							}
			gdEventWorldDataYLink[20411] = {[1]=5035,[2]=5036,[3]=5037,[4]=5038,[5]=5039,}
			gdActivityText[14] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="幻武回馈",textintroduce="活动期间，幻武升级到对应阶数，即可领取回馈奖励！",}
		end,
	},
	-- "元宝回馈"
	[20412] = {
		update = function ()
			tActivityCfgVer[20412].Ver = 1

			-- delete client old data
			local OpenID = 20412
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5040] = {
								id=5040,
								name="消费达500万元宝可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=9001,
								getcnt=1,
								openworldid=20412,
								req=5000000,
							}
			gdEventData[5041] = {
								id=5041,
								name="消费达1000万元宝可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=9002,
								getcnt=1,
								openworldid=20412,
								req=10000000,
							}
			gdEventData[5042] = {
								id=5042,
								name="消费达3000万元宝可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=9003,
								getcnt=1,
								openworldid=20412,
								req=30000000,
							}
			gdEventData[5043] = {
								id=5043,
								name="消费达5000万元宝可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=9004,
								getcnt=1,
								openworldid=20412,
								req=50000000,
							}
			gdEventData[5044] = {
								id=5044,
								name="消费达1亿元宝可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=9005,
								getcnt=1,
								openworldid=20412,
								req=100000000,
							}
			gdEventAbbr["huikui42"] = 5041
			gdEventAbbr["huikui44"] = 5043
			gdEventAbbr["huikui43"] = 5042
			gdEventAbbr["huikui41"] = 5040
			gdEventAbbr["huikui45"] = 5044
			gdRepayReward[9001] = {
								id=9001,
								canrepeat=1,
								eventid=5040,
								req=5000000,
								reward= {
										[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
										[2]= {itemID=85996,itemIsBind=true,itemcnt=1,itemname="蓝玫瑰",},
									},
								text="消费达500万元宝可领取：",
							}
			gdRepayReward[9002] = {
								id=9002,
								canrepeat=1,
								eventid=5041,
								req=10000000,
								reward= {
										[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
										[2]= {itemID=85996,itemIsBind=true,itemcnt=1,itemname="蓝玫瑰",},
									},
								text="消费达1000万元宝可领取：",
							}
			gdRepayReward[9003] = {
								id=9003,
								canrepeat=1,
								eventid=5042,
								req=30000000,
								reward= {
										[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
										[2]= {itemID=85996,itemIsBind=true,itemcnt=1,itemname="蓝玫瑰",},
									},
								text="消费达3000万元宝可领取：",
							}
			gdRepayReward[9004] = {
								id=9004,
								canrepeat=1,
								eventid=5043,
								req=50000000,
								reward= {
										
									[1]= {itemID=5555,itemIsBind=true,itemcnt=1,itemname="突破蛋",},
									[2]= {itemID=85996,itemIsBind=true,itemcnt=1,itemname="蓝玫瑰",},	
										
										
									},
								text="消费达5000万元宝可领取：",
							}
			gdRepayReward[9005] = {
								id=9005,
								canrepeat=1,
								eventid=5044,
								req=100000000,
								reward= {
										
									[1]= {itemID=5555,itemIsBind=true,itemcnt=2,itemname="突破蛋",},
									[2]= {itemID=85996,itemIsBind=true,itemcnt=2,itemname="蓝玫瑰",},
										
										
									},
								text="消费达1亿元宝可领取：",
							}
			gdEventWorldDataYLink[20412] = {[1]=5040,[2]=5041,[3]=5042,[4]=5043,[5]=5044,}
			gdActivityText[8] = {activityendtime="2050/12/30 23:59",activitystarttime="2020/10/1 12:00",childinterface="元宝回馈",textintroduce="活动期间，每日累充满足条件可领取累充好礼，数据每日00：00重置",}
		end,
	},
	-- "累计充值"
	[20413] = {
		update = function ()
			tActivityCfgVer[20413].Ver = 1

			-- delete client old data
			local OpenID = 20413
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5045] = {
								id=5045,
								name="累计充值达60元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=400000,
								getcnt=1,
								openworldid=20413,
								req=60,
							}
			gdEventData[5046] = {
								id=5046,
								name="累计充值达400000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10002,
								getcnt=1,
								openworldid=20413,
								req=400000,
							}
			gdEventData[5047] = {
								id=5047,
								name="累计充值达800000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10003,
								getcnt=1,
								openworldid=20413,
								req=800000,
							}
			gdEventData[5048] = {
								id=5048,
								name="累计充值达1500000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10004,
								getcnt=1,
								openworldid=20413,
								req=1500000,
							}
			gdEventData[5049] = {
								id=5049,
								name="累计充值达3000000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10005,
								getcnt=1,
								openworldid=20413,
								req=3000000,
							}
			gdEventData[5050] = {
								id=5050,
								name="累计充值达5000000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10006,
								getcnt=1,
								openworldid=20413,
								req=5000000,
							}
			gdEventData[5051] = {
								id=5051,
								name="累计充值达10000000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10007,
								getcnt=1,
								openworldid=20413,
								req=10000000,
							}
			gdEventData[5052] = {
								id=5052,
								name="累计充值达50000000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10008,
								getcnt=1,
								openworldid=20413,
								req=50000000,
							}
			gdEventData[5053] = {
								id=5053,
								name="累计充值达100000000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10009,
								getcnt=1,
								openworldid=20413,
								req=100000000,
							}
			gdEventData[5054] = {
								id=5054,
								name="累计充值达200000000元宝可领取:",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=10010,
								getcnt=1,
								openworldid=20413,
								req=200000000,
							}
			gdEventAbbr["huikui54"] = 5053
			gdEventAbbr["huikui53"] = 5052
			gdEventAbbr["huikui46"] = 5045
			gdEventAbbr["huikui47"] = 5046
			gdEventAbbr["huikui48"] = 5047
			gdEventAbbr["huikui52"] = 5051
			gdEventAbbr["huikui51"] = 5050
			gdEventAbbr["huikui50"] = 5049
			gdEventAbbr["huikui49"] = 5048
			gdRepayReward[10001] = {
								id=10001,
								canrepeat=0,
								eventid=5045,
								req=100000,
								reward= {
										[1]= {itemID=3,itemIsBind=true,itemcnt=300000,itemname="元宝",},
					                    
									},
								text="累计充值达100000元宝可领取：",
							}
			gdRepayReward[10002] = {
								id=10002,
								canrepeat=0,
								eventid=5046,
								req=400000,
								reward= {
										[1]= {itemID=3,itemIsBind=true,itemcnt=400000,itemname="元宝",},
									},
								text="累计充值达400000元宝可领取：",
							}
			gdRepayReward[10003] = {
								id=10003,
								canrepeat=0,
								eventid=5047,
								req=800000,
								reward= {
										[1]= {itemID=3,itemIsBind=true,itemcnt=800000,itemname="元宝",},
									},
								text="累计充值达800000元宝可领取：",
							}
			gdRepayReward[10004] = {
								id=10004,
								canrepeat=0,
								eventid=5048,
								req=1500000,
								reward= {
										[1]= {itemID=3,itemIsBind=true,itemcnt=2000000,itemname="元宝",},
									},
								text="累计充值达1500000元宝可领取：",
							}
			gdRepayReward[10005] = {
								id=10005,
								canrepeat=0,
								eventid=5049,
								req=3000000,
								reward= {
										[1]= {itemID=3,itemIsBind=true,itemcnt=4500000,itemname="元宝",},
									},
								text="累计充值达3000000元宝可领取：",
							}
			gdRepayReward[10006] = {
								id=10006,
								canrepeat=0,
								eventid=5050,
								req=5000000,
								reward= {
										[1]= {itemID=3,itemIsBind=true,itemcnt=10000000,itemname="元宝",},
									},
								text="累计充值达5000000元宝可领取：",
							}
			gdRepayReward[10007] = {
								id=10007,
								canrepeat=0,
								eventid=5051,
								req=10000000,
								reward= {
										[1]= {itemID=20559,itemIsBind=true,itemcnt=1,itemname="暗影勋章",},
					                    [2]= {itemID=3,itemIsBind=true,itemcnt=50000000,itemname="元宝",},
									},
								text="累计充值达10000000元宝可领取：",
							}
			gdRepayReward[10008] = {
								id=10008,
								canrepeat=0,
								eventid=5052,
								req=50000000,
								reward= {
										
										[1]= {itemID=3,itemIsBind=true,itemcnt=500000000,itemname="元宝",},
										
									},
								text="累计充值达50000000元宝可领取：",
							}
			gdRepayReward[10009] = {
								id=10009,
								canrepeat=0,
								eventid=5053,
								req=100000000,
								reward= {
										
									[1]= {itemID=3,itemIsBind=true,itemcnt=1000000000,itemname="元宝",},
										
									},
								text="累计充值达100000000元宝可领取：",
							}
			gdRepayReward[10010] = {
								id=10010,
								canrepeat=0,
								eventid=5054,
								req=200000000,
								reward= {
										
									[1]= {itemID=3,itemIsBind=true,itemcnt=2000000000,itemname="元宝",},
										
									},
								text="累计充值达200000000元宝可领取：",
							}
			gdEventWorldDataYLink[20413] = {[1]=5045,[2]=5046,[3]=5047,[4]=5048,[5]=5049,[6]=5050,[7]=5051,[8]=5052,[9]=5053,}
			gdActivityText[2] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="累计充值",textintroduce="活动期间，每日累充满足条件可领取累充好礼，数据每日00：00重置。",}
		end,
	},
	-- "重复充值"
	[20414] = {
		update = function ()
			tActivityCfgVer[20414].Ver = 1

			-- delete client old data
			local OpenID = 20414
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5056] = {
								id=5056,
								name="每充值100000元宝可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=12001,
								getcnt=1,
								openworldid=20414,
								req=100000,
							}
			gdEventAbbr["huikui57"] = 5056
			gdRepayReward[12001] = {
								id=12001,
								canrepeat=1,
								eventid=5056,
								req=100000,
								reward= {
										[1]= {itemID=30357,itemIsBind=true,itemcnt=2,itemname="元宝开开乐礼包",},
									},
								text="每充值100000元宝可领取",
							}
			gdEventWorldDataYLink[20414] = {[1]=5056,}
			gdActivityText[3] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="重复充值",textintroduce="活动期间玩家每累计充值500元宝，即可在“活动-活动回馈”领取“无双宝箱*1”",}
		end,
	},
	-- "单笔充值"
	[20415] = {
		update = function ()
			tActivityCfgVer[20415].Ver = 1

			-- delete client old data
			local OpenID = 20415
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5057] = {
								id=5057,
								name="单笔充值10元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13001,
								getcnt=-1,
								openworldid=20415,
								req=100000,
							}
			gdEventData[5058] = {
								id=5058,
								name="单笔充值40元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13002,
								getcnt=-1,
								openworldid=20415,
								req=400000,
							}
			gdEventData[5059] = {
								id=5059,
								name="单笔充值80元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13003,
								getcnt=-1,
								openworldid=20415,
								req=800000,
							}
			gdEventData[5060] = {
								id=5060,
								name="单笔充值150元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13004,
								getcnt=-1,
								openworldid=20415,
								req=1500000,
							}
			gdEventData[5061] = {
								id=5061,
								name="单笔充值200元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13005,
								getcnt=-1,
								openworldid=20415,
								req=2000000,
							}
			gdEventData[5100] = {
								id=5100,
								name="单笔充值500元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13006,
								getcnt=-1,
								openworldid=20415,
								req=5000000,
							}
			gdEventData[5101] = {
								id=5101,
								name="单笔充值1000元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13007,
								getcnt=-1,
								openworldid=20415,
								req=10000000,
							}
			gdEventData[5102] = {
								id=5102,
								name="单笔充值5000元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13008,
								getcnt=-1,
								openworldid=20415,
								req=50000000,
							}
			gdEventData[5103] = {
								id=5103,
								name="单笔充值10000元可领取",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=13009,
								getcnt=-1,
								openworldid=20415,
								req=100000000,
							}
			gdEventAbbr["huikui58"] = 5057
			gdEventAbbr["huikui59"] = 5100
			gdEventAbbr["huikui61"] = 5102
			gdEventAbbr["huikui62"] = 5103
			gdEventAbbr["huikui60"] = 5101
			gdRepayReward[13001] = {
								id=13001,
								canrepeat=1,
								eventid=5057,
								req=100000,
								reward= {
										[1]= {itemID=30346,itemIsBind=true,itemcnt=10,itemname="13级魂石袋",},
									},
								text="单笔充值10元可领取",
							}
			gdRepayReward[13002] = {
								id=13002,
								canrepeat=1,
								eventid=5058,
								req=400000,
								reward= {
										[1]= {itemID=30346,itemIsBind=true,itemcnt=20,itemname="13级魂石袋",},
					                    [2]= {itemID=80025,itemIsBind=true,itemcnt=1,itemname="流火异彩(12档)",},
					                    [3]= {itemID=676545075,itemIsBind=true,itemcnt=1,itemname="转生魂魄石",},
									},
								text="单笔充值40元可领取",
							}
	
			gdRepayReward[13003] = {
								id=13003,
								canrepeat=1,
								eventid=5059,
								req=800000,
								reward= {
										[1]= {itemID=30347,itemIsBind=true,itemcnt=10,itemname="14级魂石袋",},
					                    [2]= {itemID=53332,itemIsBind=true,itemcnt=20,itemname="复合药水",},
					                    [3]= {itemID=53331,itemIsBind=true,itemcnt=5,itemname="爆",},
									},
								text="单笔充值80元可领取",
							}
			gdRepayReward[13004] = {
								id=13004,
								canrepeat=1,
								eventid=5060,
								req=1500000,
								reward= {
										[1]= {itemID=30347,itemIsBind=true,itemcnt=50,itemname="14级魂石袋",},
										[2]= {itemID=82085,itemIsBind=false,itemcnt=1,itemname="暗影魔剑",},
					                    [3]= {itemID=3,itemIsBind=true,itemcnt=1500000,itemname="元宝",},
									},
								text="单笔充值150元可领取",
							}
			gdRepayReward[13005] = {
								id=13005,
								canrepeat=1,
								eventid=5061,
								req=2000000,
								reward= {
										[1]= {itemID=51113,itemIsBind=true,itemcnt=1,itemname="神器盒子",},
										[2]= {itemID=3,itemIsBind=true,itemcnt=3000000,itemname="元宝",},
									},
								text="单笔充值200元可领取",
							}
			gdRepayReward[13006] = {
								id=13006,
								canrepeat=1,
								eventid=5100,
								req=5000000,
								reward= {
										[1]= {itemID=51113,itemIsBind=true,itemcnt=1,itemname="神器盒子",},
										[2]= {itemID=3,itemIsBind=true,itemcnt=3000000,itemname="元宝",},
									},
								text="单笔充值500元可领取",
							}
			gdRepayReward[13007] = {
								id=13007,
								canrepeat=1,
								eventid=5101,
								req=10000000,
								reward= {
										[1]= {itemID=86018,itemIsBind=true,itemcnt=2,itemname="神器女神4-1",},
					                    [2]= {itemID=51112,itemIsBind=true,itemcnt=2,itemname="烈焰符文盒子",},
					                    [3]= {itemID=5555,itemIsBind=true,itemcnt=100,itemname="突破蛋",},
					                    [4]= {itemID=85996,itemIsBind=true,itemcnt=300,itemname="蓝玫瑰",},
					                    [5]= {itemID=3,itemIsBind=true,itemcnt=40000000,itemname="元宝",},
										
									},
								text="单笔充值1000元可领取",
							}
			gdRepayReward[13008] = {
								id=13008,
								canrepeat=1,
								eventid=5102,
								req=50000000,
								reward= {
										[1]= {itemID=86024,itemIsBind=true,itemcnt=2,itemname="神器女神5-1",},
					                    [2]= {itemID=51112,itemIsBind=true,itemcnt=5,itemname="烈焰符文盒子",},
					                    [3]= {itemID=5555,itemIsBind=true,itemcnt=500,itemname="突破蛋",},
					                    [4]= {itemID=85996,itemIsBind=true,itemcnt=1500,itemname="蓝玫瑰",},
					                    [5]= {itemID=3,itemIsBind=true,itemcnt=1000000000,itemname="元宝",},
										
									},
								text="单笔充值5000元可领取",
							}
			-- gdRepayReward[13009] = {
								-- id=13009,
								-- canrepeat=1,
								-- eventid=5103,
								-- req=100000000,
								-- reward= {
										
										-- [1]= {itemID=676545075,itemIsBind=true,itemcnt=1,itemname="无限元宝",},
										
									-- },
								-- text="单笔充值10000元可领取",
							-- }
	
			gdEventWorldDataYLink[20415] = {[1]=5057,[2]=5058,[3]=5059,[4]=5060,[5]=5061,[6]=5100,[7]=5101,[8]=5102,[9]=5103,}
			gdActivityText[4] = {activityendtime="2050/12/30 10:00",activitystarttime="2030/10/20 11:00",childinterface="单笔充值",textintroduce="活动期间，单笔充值满足条件，额外赠送海量魂石。",}
		end,
	},
	-- "活动首充"
	[20416] = {
		update = function ()
			tActivityCfgVer[20416].Ver = 1

			-- delete client old data
			local OpenID = 20416
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5055] = {
								id=5055,
								name="首次充值可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=11001,
								getcnt=1,
								openworldid=20416,
								req=1,
							}
			gdEventAbbr["huikui56"] = 5055
			gdRepayReward[11001] = {
								id=11001,
								canrepeat=0,
								eventid=5055,
								req=0,
								reward= {
										[1]= {itemID=30357,itemIsBind=true,itemcnt=1,itemname="红包开开乐",},
									},
								text="首次充值可领取：",
							}
			gdEventWorldDataYLink[20416] = {[1]=5055,}
			gdActivityText[1] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="活动首充",textintroduce="活动期间，每日消费满足条件即可领取消费礼包，数据每日00：00重置。",}
		end,
	},
	-- "幸运大转盘"
	[20417] = {
		update = function ()
			tActivityCfgVer[20417].Ver = 1

			-- delete client old data
			local OpenID = 20417
			local tSubActivityIDOld = {}
			for Key, Value in pairs(gdEventData) do
				if Value.openworldid == OpenID then
					gdEventData[Key] = nil
					tSubActivityIDOld[Key] = Key
				end	
			end
			for Key, Value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[Value] then
					gdEventAbbr[Key] = nil
				end	
			end
			gdLuckyCircleReward = nil
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[6000] = {
								id=6000,
								name="幸运大转盘",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=6000,
								getcnt=0,
								openworldid=20417,
								req=0,
							}
			gdEventAbbr["xydzp"] = 6000
			gdLuckyCircleReward = {
                       	[1]= {id=1,name="橙钻石",cnt=10,itemID=41112,probability=1,},
	                    [2]= {id=2,name="紫钻石",cnt=20,itemID=41111,probability=5,},
	                    [3]= {id=3,name="蓝钻石",cnt=50,itemID=41110,probability=10,},
	                    [4]= {id=4,name="复合药水",cnt=3,itemID=53332,probability=11,},
                        [5]= {id=5,name="元宝",cnt=20000,itemID=3,probability=8,},
                        [6]= {id=6,name="100倍经验神符(8小时)",cnt=1,itemID=30164,probability=3,},
                        [7]= {id=7,name="金蝉王",cnt=1,itemID=30059,probability=12,},
                        [8]= {id=8,name="灵魂石",cnt=500,itemID=40011,probability=25,},
							}
			gdEventWorldDataYLink[20417] = {[1]=6000,}
		end,
	},
	-- "马上抢购"
	[20418] = {
		update = function ()
			tActivityCfgVer[20418].Ver = 2

			-- delete client old data
			local OpenID = 20418
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[6015] = {
								id=6015,
								name="马上抢购",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=14001,
								getcnt=3,
								openworldid=20418,
								req=0,
							}
			gdEventAbbr["msqg"] = 6015
			gdRepayReward[14001] = {
								id=14001,
								canrepeat=0,
								eventid=6015,
								req=100,
								reward= {
										[1]= {itemID=40116,itemIsBind=true,itemcnt=5,itemname="藏宝图",},
										[2]= {itemID=30054,itemIsBind=true,itemcnt=1,itemname="6倍经验神符",},
									},
								text="100元宝礼包,限购10个：",
							}
			gdEventWorldDataYLink[20418] = {[1]=6015,}
			gdActivityText[16] = {activityendtime="2050/12/30 12:00",activitystarttime="2020/10/1 12:00",childinterface="马上抢购",textintroduce="超值豪华礼包限时供应!不容错过!",}
		end,
	},
	-- "疯狂抢购"
	[20419] = {
		update = function ()
			tActivityCfgVer[20419].Ver = 2

			-- delete client old data
			local OpenID = 20419
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[6025] = {
								id=6025,
								name="疯狂抢购",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=15001,
								getcnt=3,
								limitcnt=100,
								openworldid=20419,
								req=0,
								worldid=10200,
							}
			gdEventAbbr["fkqg"] = 6025
			gdRepayReward[15001] = {
								id=15001,
								canrepeat=0,
								eventid=6025,
								req=100,
								reward= {
										[1]= {itemID=40116,itemIsBind=true,itemcnt=5,itemname="藏宝图",},
									},
								text="100元宝礼包,剩余数量：",
							}
			gdEventWorldDataYLink[20419] = {[1]=6025,}
			gdActivityText[17] = {activityendtime="2050/12/30 12:00",activitystarttime="2020/10/1 12:00",childinterface="疯狂抢购",textintroduce="超值豪华礼包限量供应!先到先得!不容错过!",}
		end,
	},
	-- "每日回馈"
	[20404] = {
		update = function ()
			tActivityCfgVer[20404].Ver = 1

			-- delete client old data
			local OpenID = 20404
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end
            gdEventData[5000] = {
								id=5000,
								name="每日消费达500w元宝可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {[0]=1,},
								gdID=1001,
								getcnt=1,
								openworldid=20404,
								refresh=0,
								req=5000000,
							}
			gdEventData[5001] = {
								id=5001,
								name="每日消费达3000w元宝可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {[0]=1,},
								gdID=1002,
								getcnt=1,
								openworldid=20404,
								refresh=0,
								req=30000000,
							}
			gdEventData[5002] = {
								id=5002,
								name="每日消费达5000w元宝可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {[0]=1,},
								gdID=1003,
								getcnt=1,
								openworldid=20404,
								refresh=0,
								req=50000000,
							}
			gdEventData[5003] = {
								id=5003,
								name="每日消费达8000w元宝可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {[0]=1,},
								gdID=1004,
								getcnt=1,
								openworldid=20404,
								refresh=0,
								req=80000000,
							}
			gdEventData[5004] = {
								id=5004,
								name="每日消费达1亿元宝可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {[0]=1,},
								gdID=1005,
								getcnt=1,
								openworldid=20404,
								refresh=0,
								req=100000000,
							}
			gdEventAbbr["huikui1"] = 5000
			gdEventAbbr["huikui2"] = 5001
			gdEventAbbr["huikui4"] = 5003
			gdEventAbbr["huikui5"] = 5004
			gdEventAbbr["huikui3"] = 5002
			gdRepayReward[1001] = {
								id=1001,
								canrepeat=1,
								eventid=5000,
								req=5000000,
								reward= {
										[1]= {itemID=85996,itemIsBind=true,itemcnt=1,itemname="蓝玫瑰",},
										[2]= {itemID=40053,itemIsBind=true,itemcnt=10,itemname="宠物项圈",},
										[3]= {itemID=30164,itemIsBind=true,itemcnt=1,itemname="10倍8小时",},
									},
								text="每日消费达500w元宝可领取：",
							}
			gdRepayReward[1002] = {
								id=1002,
								canrepeat=1,
								eventid=5001,
								req=30000000,
								reward= {
										[1]= {itemID=85996,itemIsBind=true,itemcnt=1,itemname="蓝玫瑰",},
										[2]= {itemID=41118,itemIsBind=true,itemcnt=30,itemname="深渊挑战令",},
										[3]= {itemID=30164,itemIsBind=true,itemcnt=10,itemname="10倍8小时",},
										
									},
								text="每日消费达3000w元宝可领取：",
							}
			gdRepayReward[1003] = {
								id=1003,
								canrepeat=1,
								eventid=5002,
								req=50000000,
								reward= {
										[1]= {itemID=85996,itemIsBind=true,itemcnt=2,itemname="蓝玫瑰",},
										[2]= {itemID=41117,itemIsBind=true,itemcnt=1,itemname="符文令",},
										[3]= {itemID=41118,itemIsBind=true,itemcnt=30,itemname="深渊挑战令",},
										[4]= {itemID=85997,itemIsBind=true,itemcnt=15,itemname="暗影石",},
									},
								text="每日消费达5000w元宝可领取：",
							}
			gdRepayReward[1004] = {
								id=1004,
								canrepeat=1,
								eventid=5003,
								req=80000000,
								reward= {
										[1]= {itemID=85996,itemIsBind=true,itemcnt=3,itemname="蓝玫瑰",},
										[2]= {itemID=5555,itemIsBind=true,itemcnt=5,itemname="突破蛋",},
										[3]= {itemID=41118,itemIsBind=true,itemcnt=30,itemname="深渊挑战令",},
										[4]= {itemID=85997,itemIsBind=true,itemcnt=30,itemname="暗影石",},
									},
								text="每日消费达8000w元宝可领取：",
							}
			-- gdRepayReward[1005] = {
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
							-- }
			gdEventWorldDataYLink[20404] = {[1]=5000,[2]=5001,[3]=5002,[4]=5003,[5]=5004,}
			gdActivityText[7] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="每日回馈",textintroduce="活动期间，每日消费满足条件即可领取消费礼包，数据每日00：00重置。",}
		end,
	},
	-- "强化回馈"
	[20405] = {
		update = function ()
			tActivityCfgVer[20405].Ver = 1

			-- delete client old data
			local OpenID = 20405
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5005] = {
								id=5005,
								name="装备强化达20级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2001,
								getcnt=-1,
								openworldid=20405,
								req=20,
							}
			gdEventData[5006] = {
								id=5006,
								name="装备强化达30级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2002,
								getcnt=-1,
								openworldid=20405,
								req=30,
							}
			gdEventData[5007] = {
								id=5007,
								name="装备强化达40级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2003,
								getcnt=-1,
								openworldid=20405,
								req=40,
							}
			gdEventData[5008] = {
								id=5008,
								name="装备强化达45级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2004,
								getcnt=-1,
								openworldid=20405,
								req=45,
							}
			gdEventData[5009] = {
								id=5009,
								name="装备强化达50级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2005,
								getcnt=-1,
								openworldid=20405,
								req=50,
							}
			gdEventData[5062] = {
								id=5062,
								name="装备强化达13级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2006,
								getcnt=-1,
								openworldid=20405,
								req=13,
							}
			gdEventData[5063] = {
								id=5063,
								name="装备强化达14级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2007,
								getcnt=-1,
								openworldid=20405,
								req=14,
							}
			gdEventData[5064] = {
								id=5064,
								name="装备强化达15级可领取：",
								canrepeat=1,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=2008,
								getcnt=-1,
								openworldid=20405,
								req=15,
							}
			gdEventAbbr["huikui10"] = 5009
			gdEventAbbr["huikui6"] = 5005
			gdEventAbbr["huikui8"] = 5007
			gdEventAbbr["huikui9"] = 5008
			gdEventAbbr["huikui7"] = 5006
			gdEventAbbr["huikui65"] = 5064
			gdEventAbbr["huikui64"] = 5063
			gdRepayReward[2001] = {
								id=2001,
								canrepeat=1,
								eventid=5006,
								req=20,
								reward= {
										[1]= {itemID=40011,itemIsBind=true,itemcnt=100,itemname="灵魂石",},
									},
								text="装备强化达20级可领取：",
							}
			gdRepayReward[2002] = {
								id=2002,
								canrepeat=1,
								eventid=5007,
								req=30,
								reward= {
										[1]= {itemID=41110,itemIsBind=true,itemcnt=100,itemname="蓝钻石",},
									},
								text="装备强化达30级可领取：",
							}
			gdRepayReward[2003] = {
								id=2003,
								canrepeat=1,
								eventid=5008,
								req=40,
								reward= {
										[1]= {itemID=41111,itemIsBind=true,itemcnt=50,itemname="紫钻石",},
									},
								text="装备强化达40级可领取：",
							}
			gdRepayReward[2004] = {
								id=2004,
								canrepeat=1,
								eventid=5009,
								req=45,
								reward= {
										[1]= {itemID=41111,itemIsBind=true,itemcnt=50,itemname="紫钻石",},
									},
								text="装备强化达45级可领取：",
							}
			gdRepayReward[2005] = {
								id=2005,
								canrepeat=1,
								eventid=5062,
								req=50,
								reward= {
										[1]= {itemID=41112,itemIsBind=true,itemcnt=30,itemname="橙钻石",},
									},
								text="装备强化达50级可领取：",
							}		
			-- gdRepayReward[2006] = {
								-- id=2006,
								-- canrepeat=1,
								-- eventid=5063,
								-- req=13,
								-- reward= {
										-- [1]= {itemID=40011,itemIsBind=true,itemcnt=8,itemname="灵魂石",},
									-- },
								-- text="装备强化达13级可领取：",
							-- }
			-- gdRepayReward[2007] = {
								-- id=2007,
								-- canrepeat=1,
								-- eventid=5064,
								-- req=14,
								-- reward= {
										-- [1]= {itemID=40011,itemIsBind=true,itemcnt=13,itemname="灵魂石",},
									-- },
								-- text="装备强化达14级可领取：",
							-- }
			gdEventWorldDataYLink[20405] = {[1]=5005,[2]=5006,[3]=5007,[4]=5008,[5]=5009,[6]=5062,[7]=5063,[8]=5064,}
			gdActivityText[15] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="强化回馈",textintroduce="活动期间，强化装备送大礼，每强化装备到对应等级，可领取一次奖励。",}
		end,
	},
	-- "宠物回馈"
	[20406] = {
		update = function ()
			tActivityCfgVer[20406].Ver = 1

			-- delete client old data
			local OpenID = 20406
			local tSubActivityIDOld = {}
			for key, value in pairs(gdEventData) do
				if value.openworldid == OpenID then
					gdEventData[key] = nil
					tSubActivityIDOld[key] = key
				end	
			end
			for key, value in pairs(gdEventAbbr) do
				if tSubActivityIDOld[value] then
					gdEventAbbr[key] = nil
				end	
			end
			for key, value in pairs(gdRepayReward) do
				if tSubActivityIDOld[value.eventid] then
					gdRepayReward[key] = nil
				end 
			end	
			if gdEventWorldDataYLink[OpenID] then
				gdEventWorldDataYLink[OpenID] = nil
			end

			gdEventData[5010] = {
								id=5010,
								name="宠物等级达20级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3001,
								getcnt=1,
								openworldid=20406,
								req=20,
							}
			gdEventData[5011] = {
								id=5011,
								name="宠物等级达25级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3002,
								getcnt=1,
								openworldid=20406,
								req=25,
							}
			gdEventData[5012] = {
								id=5012,
								name="宠物等级达30级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3003,
								getcnt=1,
								openworldid=20406,
								req=30,
							}
			gdEventData[5013] = {
								id=5013,
								name="宠物等级达35级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3004,
								getcnt=1,
								openworldid=20406,
								req=35,
							}
			gdEventData[5014] = {
								id=5014,
								name="宠物等级达40级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3005,
								getcnt=1,
								openworldid=20406,
								req=40,
							}
			gdEventData[5072] = {
								id=5072,
								name="宠物等级达45级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3006,
								getcnt=1,
								openworldid=20406,
								req=45,
							}
			gdEventData[5073] = {
								id=5073,
								name="宠物等级达50级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3007,
								getcnt=1,
								openworldid=20406,
								req=50,
							}
			gdEventData[5074] = {
								id=5074,
								name="宠物等级达55级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3008,
								getcnt=1,
								openworldid=20406,
								req=55,
							}
			gdEventData[5075] = {
								id=5075,
								name="宠物等级达60级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3009,
								getcnt=1,
								openworldid=20406,
								req=60,
							}
			gdEventData[5076] = {
								id=5076,
								name="宠物等级达65级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3010,
								getcnt=1,
								openworldid=20406,
								req=65,
							}
			gdEventData[5077] = {
								id=5077,
								name="宠物等级达70级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3011,
								getcnt=1,
								openworldid=20406,
								req=70,
							}
			gdEventData[5078] = {
								id=5078,
								name="宠物等级达75级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3012,
								getcnt=1,
								openworldid=20406,
								req=75,
							}
			gdEventData[5079] = {
								id=5079,
								name="宠物等级达80级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3013,
								getcnt=1,
								openworldid=20406,
								req=80,
							}
			gdEventData[5080] = {
								id=5080,
								name="宠物等级达85级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3014,
								getcnt=1,
								openworldid=20406,
								req=85,
							}
			gdEventData[5081] = {
								id=5081,
								name="宠物等级达90级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3015,
								getcnt=1,
								openworldid=20406,
								req=90,
							}
			gdEventData[5082] = {
								id=5082,
								name="宠物等级达95级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3016,
								getcnt=1,
								openworldid=20406,
								req=95,
							}
			gdEventData[5083] = {
								id=5083,
								name="宠物等级达100级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3017,
								getcnt=1,
								openworldid=20406,
								req=100,
							}
			gdEventData[5084] = {
								id=5084,
								name="宠物等级达105级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3018,
								getcnt=1,
								openworldid=20406,
								req=105,
							}
			gdEventData[5085] = {
								id=5085,
								name="宠物等级达110级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3019,
								getcnt=1,
								openworldid=20406,
								req=110,
							}
			gdEventData[5086] = {
								id=5086,
								name="宠物等级达115级可领取：",
								canrepeat=0,
								datax=0,
								datay=0,
								dataz=0,
								dates= {},
								gdID=3020,
								getcnt=1,
								openworldid=20406,
								req=115,
							}
			-- gdEventData[5087] = {
								-- id=5087,
								-- name="宠物等级达119级可领取：",
								-- canrepeat=0,
								-- datax=0,
								-- datay=0,
								-- dataz=0,
								-- dates= {},
								-- gdID=3021,
								-- getcnt=1,
								-- openworldid=20406,
								-- req=119,
							-- }
			gdEventAbbr["huikui83"] = 5082
			gdEventAbbr["huikui86"] = 5085
			gdEventAbbr["huikui79"] = 5078
			gdEventAbbr["huikui81"] = 5080
			gdEventAbbr["huikui12"] = 5011
			gdEventAbbr["huikui15"] = 5014
			gdEventAbbr["huikui82"] = 5081
			gdEventAbbr["huikui87"] = 5086
			gdEventAbbr["huikui75"] = 5074
			gdEventAbbr["huikui13"] = 5012
			gdEventAbbr["huikui11"] = 5010
			gdEventAbbr["huikui14"] = 5013
			gdEventAbbr["huikui80"] = 5079
			gdEventAbbr["huikui85"] = 5084
			gdEventAbbr["huikui73"] = 5072
			gdEventAbbr["huikui84"] = 5083
			gdEventAbbr["huikui78"] = 5077
			gdEventAbbr["huikui74"] = 5073
			gdEventAbbr["huikui77"] = 5076
			gdEventAbbr["huikui76"] = 5075
			gdRepayReward[3001] = {
								id=3001,
								canrepeat=0,
								eventid=5010,
								req=20,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=20,itemname="宠物项圈",},
									},
								text="宠物等级达20级可领取：",
							}
			gdRepayReward[3002] = {
								id=3002,
								canrepeat=0,
								eventid=5011,
								req=25,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=25,itemname="宠物项圈",},
									},
								text="宠物等级达25级可领取：",
							}
			gdRepayReward[3003] = {
								id=3003,
								canrepeat=0,
								eventid=5012,
								req=30,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=30,itemname="宠物项圈",},
									},
								text="宠物等级达30级可领取：",
							}
			gdRepayReward[3004] = {
								id=3004,
								canrepeat=0,
								eventid=5013,
								req=35,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=35,itemname="宠物项圈",},
									},
								text="宠物等级达35级可领取：",
							}
			gdRepayReward[3005] = {
								id=3005,
								canrepeat=0,
								eventid=5014,
								req=40,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=40,itemname="宠物项圈",},
									},
								text="宠物等级达40级可领取：",
							}
			gdRepayReward[3006] = {
								id=3006,
								canrepeat=0,
								eventid=5072,
								req=45,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=45,itemname="宠物项圈",},
									},
								text="宠物等级达45级可领取：",
							}
			gdRepayReward[3007] = {
								id=3007,
								canrepeat=0,
								eventid=5073,
								req=50,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=50,itemname="宠物项圈",},
									},
								text="宠物等级达50级可领取：",
							}
			gdRepayReward[3008] = {
								id=3008,
								canrepeat=0,
								eventid=5074,
								req=55,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=55,itemname="宠物项圈",},
									},
								text="宠物等级达55级可领取：",
							}
			gdRepayReward[3009] = {
								id=3009,
								canrepeat=0,
								eventid=5075,
								req=60,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=60,itemname="宠物项圈",},
									},
								text="宠物等级达60级可领取：",
							}
			gdRepayReward[3010] = {
								id=3010,
								canrepeat=0,
								eventid=5076,
								req=65,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=65,itemname="宠物项圈",},
									},
								text="宠物等级达65级可领取：",
							}
			gdRepayReward[3011] = {
								id=3011,
								canrepeat=0,
								eventid=5077,
								req=70,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=70,itemname="宠物项圈",},
									},
								text="宠物等级达70级可领取：",
							}
			gdRepayReward[3012] = {
								id=3012,
								canrepeat=0,
								eventid=5078,
								req=75,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=75,itemname="宠物项圈",},
									},
								text="宠物等级达75级可领取：",
							}
			gdRepayReward[3013] = {
								id=3013,
								canrepeat=0,
								eventid=5079,
								req=80,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=80,itemname="宠物项圈",},
									},
								text="宠物等级达80级可领取：",
							}
			gdRepayReward[3014] = {
								id=3014,
								canrepeat=0,
								eventid=5080,
								req=85,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=85,itemname="宠物项圈",},
									},
								text="宠物等级达85级可领取：",
							}
			gdRepayReward[3015] = {
								id=3015,
								canrepeat=0,
								eventid=5081,
								req=90,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=90,itemname="宠物项圈",},
									},
								text="宠物等级达90级可领取：",
							}
			gdRepayReward[3016] = {
								id=3016,
								canrepeat=0,
								eventid=5082,
								req=95,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=95,itemname="宠物项圈",},
									},
								text="宠物等级达95级可领取：",
							}
			gdRepayReward[3017] = {
								id=3017,
								canrepeat=0,
								eventid=5083,
								req=100,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=100,itemname="宠物项圈",},
									},
								text="宠物等级达100级可领取：",
							}
			gdRepayReward[3018] = {
								id=3018,
								canrepeat=0,
								eventid=5084,
								req=105,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=105,itemname="宠物项圈",},
									},
								text="宠物等级达105级可领取：",
							}
			gdRepayReward[3019] = {
								id=3019,
								canrepeat=0,
								eventid=5085,
								req=110,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=110,itemname="宠物项圈",},
									},
								text="宠物等级达110级可领取：",
							}
			gdRepayReward[3020] = {
								id=3020,
								canrepeat=0,
								eventid=5086,
								req=115,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=115,itemname="宠物项圈",},
									},
								text="宠物等级达115级可领取：",
							}
			gdRepayReward[3021] = {
								id=3021,
								canrepeat=0,
								eventid=5087,
								req=119,
								reward= {
										[1]= {itemID=40053,itemIsBind=true,itemcnt=119,itemname="宠物项圈",},
									},
								text="宠物等级达120级可领取：",
							}
			gdEventWorldDataYLink[20406] = {
								[1]=5010,
								[2]=5011,
								[3]=5012,
								[4]=5013,
								[5]=5014,
								[6]=5072,
								[7]=5073,
								[8]=5074,
								[9]=5075,
								[10]=5076,
								[11]=5077,
								[12]=5078,
								[13]=5079,
								[14]=5080,
								[15]=5081,
								[16]=5082,
								[17]=5083,
								[18]=5084,
								[19]=5085,
								[20]=5086,
							}
			gdActivityText[9] = {activityendtime="2050/12/30 10:00",activitystarttime="2020/10/1 11:00",childinterface="宠物回馈",textintroduce="活动期间内，只要通过宠物升级使得宠物等级达到指定要求，即可获得返利大奖！",}
		end,
	},
}
-- 取得指定函数
tActivityCfgPatch["GetUpdateFunction"] = function (ID)
	if tActivityCfgPatch[ID] then
		return tActivityCfgPatch[ID].update
	else
		return nil
	end	
end
