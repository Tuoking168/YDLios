--	购买红玫瑰
--

Opcode.buy_rose		= 10000
Opcode.teleport		= 10001

Opcode.event_ysjdc	= 10002
Opcode.event_hhzdz	= 10003

Opcode.gcz_job_reward = 10004

Opcode.springbrother = 10005
Opcode.gcz_zszl_open = 10006
Opcode.InstanceCntAdd = 10007

Opcode.qifuxianziscene	= 10008
Opcode.qifuxianziguild	= 10009

Opcode.BundlingItem		= 10010
Opcode.Exchangejysf		= 10011

Opcode.mobaixuanshang 	= 10012
Opcode.mobaiczreward	= 10013

Opcode.mhxglayerreward 	= 10014

Opcode.fcdjf			= 10015


Opcode.guildmnhs		= 10017

Opcode.mailGift			= 10018

Opcode.ArenaFight		= 10019

Opcode.GuildReward		= 10020

Opcode.ArenaReward 	= 		10021

Opcode.WeekFlee		=  10022

Opcode.RechargeOnce = 10023

Opcode.NSFightLvl		= 10100
Opcode.NSFightPet		= 10101
Opcode.NSFightStone		= 10102
Opcode.NSLogin			= 10103

Opcode.ClearRedName 		= 10104
Opcode.gcz_period_exp		= 10105
Opcode.lyt_monster_exp		= 10106
Opcode.gcz_week_gold		= 10107

Opcode.LootItemBind			= 10108

Opcode.lingshi_split				= 10110
Opcode.gcz_repairewall				= 10111

Opcode.buyGoldBowl			= 10120
Opcode.useLuckyCircle			= 10121

Opcode.use_xinfu_jingyanx_dalibao			= 10122
Opcode.use_lingshi_daijing_card			= 10123
Opcode.use_hunshi_daijin_card			= 10124
Opcode.use_pet_daijin_card			= 10125
Opcode.use_fashion_daijin_card			= 10126


Opcode.Op_Treasure_hunt_free	 = 10130

Opcode.op_summer = 10140

Opcode.op_plant = 10150

Opcode.QQ_gift = 10160

Opcode.op_feedback_shop = 10170

Opcode.op_dailyact_finish = 10180
Opcode.op_change_pet_best_attr = 10190
Opcode.op_improve_pet_advance_attr = 10200
Opcode.op_dog_to_max_lvl = 10210
Opcode.op_add_roll_cnt = 10220
Opcode.op_spider_throw_item_rmv_req = 10230

Opcode.op_guild_finish_building = 10241
Opcode.op_guild_prayto_guangong = 10242
Opcode.op_guild_add_guangong_cnt = 10243
Opcode.op_guild_open_welfare = 10244
Opcode.Op_Guild_GuildCrossGCZ = 10245

Opcode.op_msqg = 10300
Opcode.op_fkqg = 10400

--
--
--



Error.guildnotinhhmnhs	= 10000
Error.guildgirlNotReach = 10001
Error.guildhhmnhsisOpen = 10002
Error.invalidguildbuildid = 10010
Error.guildisbuilding	= 10011
Error.guildBuildnotOpen   = 10012
Error.guildBuildLvlMax	  = 10013
Error.guildNotEnoughtMoney = 10014
Error.guildHasApplyGcz	   = 10015
Error.guildGczBuffHasOn	   = 10016
Error.guildGczNotApply	   = 10017
Error.guildPrayBuyMax	   = 10018
Error.guildCanNotApplyGcz = 10019

Error.lvlnotenough40	= 10100
Error.lvlnotenough42	= 10101
Error.lvlnotenough44	= 10102
Error.lvlnotenough46	= 10103
Error.lvlnotenough48	= 10104
Error.lvlnotenough49	= 10105
Error.lvlnotenough50	= 10106


Error.PlayerStateGood   = 11001

Error.ItemRepairSome	= 11002
Error.NeedUseIt			= 11003

Error.hasgetgoldbowl	= 11010
Error.bowlnoneedrmv 	= 11011
Error.goldbowltodayhasget = 11012


--
--	不要在这个代码后面定义数据
--
disableTableNewIndexing(Error)
disableTableNewIndexing(Opcode)
--
--	不要在这个代码后面定义数据
--
