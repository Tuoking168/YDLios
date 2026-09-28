#ifndef __FloatPanelType_h__
#define __FloatPanelType_h__

namespace FloatPanelType
{
	enum
	{
		TradeTips_Apply			=1,//交易申请
		TradeTips_Refuse, 
		TradeTips_Over,  
		TradeTips_Failed, 
		TradeTips_Success,
		PET_MONEY,  //元宝培养宠物
		PET_ITEM,
		PET_LowBooth,
		PET_HighBooth,
		LOGIN_DelRole = 10,
		ITEM_DROP		=11,//物品丢弃
		DOG_UPDATE,
		RELIVE_SITU,
		Item_ZBQX,	//装备清洗
		Item_shoesUse,	//飞鞋
		Pet_FeedVcoin	=16,	//FeedPet
		Pet_FeedHonor,	//FeedPet
		Buy_ItemSure	=18,
		Relive_Item_NotEnough	=19,
		Gold_NotEnough = 20, //
		Team_invite,
		Team_hasteam,
		Team_application,
		Pet_seal	=24,
		Guild_Leave	=25,
		Guild_ChangeMaster	=26,
		Guild_Kick	=27,
		TradeTips_Buzy	=28,
		TradeTips_NotReflect =29,
		TradeTips_NotAllow =30,
		Guild_Invite	=31,
		Arena_add_count = 32,
		Arena_gold_refresh = 33,
		Arena_super_refresh = 34,
		Arena_clear_cd = 35,
		Guild_guan_gong_add_count = 36,
		Team_Call = 37,
		Guild_expel = 38,
		Worship_refresh = 39,
		Worship_add_count = 40,
		Quest_QuickFinish = 41,
		Time_QuickCoolDown = 42,
		Item_NotEndure = 43, 
		Coupon_NotEnough = 44,
		Score_NotEnough  = 45,     //积分
		Reborn_Tips  = 46, 
		Guild_GuangHuan_open = 47,
		Guild_Call  = 48,
		Refresh_Cahshenchuangguan = 49,
		Exit_activity_scene = 50,
		Refresh_Meinvhusong = 51, //
		Emigrate_add_count = 52, 
		Use_zhuizongling = 53, //使用追踪令
		Pet_onekeyup = 54, //一键升级宠物
		Pet_reborn_desc = 55,
		Appstore_IAP_Confirm = 56,
		Fumo_Reset = 61,
		Common_Notice = 62,
		Horse_RYPY = 63,	// 坐骑荣誉培养
		Horse_YBPY = 64,	// 坐骑元宝培养
		Horse_YJSJ = 65,	// 坐骑一键升级
		Horse_SJ = 66,		// 坐骑升阶
		HORSE_EQUIP_ADDEXP = 67,	// 坐骑装备加经验
		Horse_EQUIP_SJ = 68,		// 坐骑装备升级
	};
}
#endif //__FloatPanelType_h__