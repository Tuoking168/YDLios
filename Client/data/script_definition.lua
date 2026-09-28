--
--	Definintion Prop Base On Script
--
--

if not (type(EntityProp)=="table") then
	EntityProp = {}
end

if not (type(SceneProp)=="table")  then
	SceneProp = {}
end
if not (type(WorldProp)=="table")  then
	WorldProp = {}
end
if not (type(GuildProp)=="table")  then
	GuildProp = {}
end
if not (type(FuncProp)=="table")  then
	FuncProp = {}
end

--
-- 	func enum ID
--
FuncProp.team_call = 1 --队伍集结
FuncProp.player_setting = 2 --人物设置
FuncProp.item_use = 3 --物品使用
FuncProp.player_relive = 4 --人物复活
FuncProp.kick_from_guild = 5 --被踢出行会
FuncProp.gift_reward	= 6 --离线奖励礼包
FuncProp.NSLogin		= 7
FuncProp.findback_item	= 8	--物品找回
FuncProp.guild_call	= 9	--行会召集
FuncProp.recharge_once = 10 -- 单笔充值礼包
FuncProp.CaiShenLanLu = 11 -- 财神拦路
FuncProp.BoothNote = 12 -- 摆摊日志
FuncProp.offlineExp = 13 -- 离线经验
FuncProp.dailyReward = 14 -- 每日活跃奖励
FuncProp.goldbowl = 15 -- 聚宝盆
FuncProp.changeItem = 16 -- 物品兑换
FuncProp.maildata	= 17 -- 邮件
FuncProp.luckycircle	= 18 -- 幸运转盘
FuncProp.repayreward	= 19 -- 回馈返利奖励
FuncProp.rename	= 20 -- 改名字
FuncProp.bind_item = 21 -- 物品绑定

FuncProp.MSQG = 22 -- 马上抢购
FuncProp.FKQG = 23 -- 疯狂抢购


--
-- 	世界全局数据定义
--
WorldProp.city_master_guild	= 1000
WorldProp.city_master_player	= 1001
WorldProp.city_own4days_reward	= 1002

WorldProp.mobai_bishi_count	= 1011
WorldProp.mobai_money_count	= 1012
WorldProp.mobai_guild_buff	= 1013
WorldProp.mobai_guild_master_reward	= 1014

WorldProp.ysjdc_rank		= 1020

WorldProp.qfxz_rank		= 1030

WorldProp.zszb			= 1040

WorldProp.prop_world_xiaojubaopen_cnt			= 1050
WorldProp.prop_world_dajubaopen_cnt			= 1051


WorldProp.city_master_get_gold = 10001

WorldProp.recharge_500_data = 10010
WorldProp.usegold_300_data = 10011

WorldProp.repay_data_1 = 10100 --兑换券兑换个数

WorldProp.FKQG = 10200
WorldProp.FKQG1 = 10201
WorldProp.FKQG2 = 10202
WorldProp.FKQG3 = 10203
WorldProp.FKQG4 = 10204
--
--	行会数据定义
--
GuildProp.rysd_open_count	= 1000

GuildProp.lyt_open_count	= 1010
GuildProp.lyt_instance_id	= 1011
GuildProp.lyt_kill_count 	= 1012
GuildProp.lyt_kill_wave_count = 1013

GuildProp.daily_tax		= 1020
GuildProp.daily_suite		= 1021

GuildProp.hhmnhs_open_count = 1030
GuildProp.hhmnhs_girl_id	= 1031
GuildProp.hhmnhs_protect_open = 1032

GuildProp.welfare = 1040

--
--	玩家魂石加成的冗余数据
--
EntityProp.stone_addbegin = -200
EntityProp.stone_addend	  = -100

--
--	所有场景公用属性
--
SceneProp.scene_time_remain = 1200
SceneProp.max_monster = 1203
SceneProp.now_monster = 1204

SceneProp.ownerguildid = 1205


--
--	九天冰宫	jtbg
--
EntityProp.attr_jtbg_time_start = 1231

--
--	武易战场	wyzc
--
SceneProp.wyzc_faction_a = 1000
SceneProp.wyzc_faction_b = 1001
SceneProp.wyzc_score_a = 1002
SceneProp.wyzc_score_b = 1003
SceneProp.wyzc_boss_id = 1004
SceneProp.wyzc_flag_id = 1235
--
--
--






--
--	活动: 行会争夺战	hhzdz
--
SceneProp.hhzdz_defend_guild = 1005
SceneProp.hhzdz_flag_eid = 1006
SceneProp.hhzdz_guild_name = 1007
SceneProp.hhzdz_finish		= 1008

--
--	天地宝窟	tdbk
--
SceneProp.tdbk_kill_count = 1010
SceneProp.tdbk_mg_id = 1011
SceneProp.tdbk_boss_idx = 1012
SceneProp.tdbk_kill_count_down = 1013
SceneProp.tdbk_buff_data = 1014
EntityProp.attr_tdbk_gene = 1001

--
--	魔龙神殿	mlsd
--
SceneProp.mlsd_defencer_count	= 1020
SceneProp.mlsd_monster_wave	= 1021

SceneProp.mlsd_guard1		= 1022
SceneProp.mlsd_guard2		= 1023
SceneProp.mlsd_guard3		= 1024

SceneProp.mlsd_lowpowcnt 	= 1025
SceneProp.mlsd_highpowcnt	= 1026

--
--	地狱结界	dyjj
--
SceneProp.dyjj_defencer_count	= 1030
SceneProp.dyjj_monster_wave	= 1031

--
--	战神争霸	zszb
--
SceneProp.zszb_player_cnt 	= 1040

--
--	烈火宫		lhg
--
SceneProp.lhg_layer 	= 1050
SceneProp.lhg_gold_to_next_layer 	= 1051
SceneProp.lhg_diamond_to_next_layer 	= 1052
SceneProp.lhg_honor_to_next_layer 	= 1053
SceneProp.lhg_liehuolin_to_next_layer	= 1054
SceneProp.lhg_exp			= 1055
SceneProp.lhg_owner_level		= 1056
SceneProp.lhg_layer_reward = 1057

--
--	水域龙都	syld
--
SceneProp.syld_longnv_posx 	= 1060
SceneProp.syld_longnv_posy	= 1061
SceneProp.syld_longwang_summon	= 1062

--
--	魔剑封印	mjfy
--
SceneProp.mjfy_summon_boss1	= 1070
SceneProp.mjfy_summon_boss2	= 1071
SceneProp.mjfy_now_bossid = 1072

--
--	五行炼狱	wxly
--
SceneProp.wxly_boss_kill_cnt 	= 1075

--
--	马拉松		sm 	mls
--
SceneProp.mls_begin_state 	= 1080
SceneProp.mls_reach_cnt		= 1081
SceneProp.mls_wait_end_time = 1082

--
--	狩猎活动	slhd
--
EntityProp.attr_slhd_score	= 1252
SceneProp.slhd 		= 1090
SceneProp.slhd_layer 	= 1091

--
--	降魔副本	xmfb
--	水寨		sz
--	高家店		gjd
--	五指山下	wzsx
--
SceneProp.xmfb_already_summon		= 1100
SceneProp.xmfb_already_summon_liemo	= 1101

SceneProp.xmfb_already_summon_liemohead	= 1102


SceneProp.xmfb_already_potion		= 1105
SceneProp.xmfb_already_killed_boss	= 1106

SceneProp.xmfb_stage		= 1107
SceneProp.xmfb_bossid		= 1108

--
--	活动:龙影潭	lyt
--
SceneProp.lyt_monster_kill 	= 1110
SceneProp.lyt_monster_realkill = 1111
SceneProp.lyt_wave		= 1112
SceneProp.lyt_player_cnt	= 1113

--
--	活动:攻城战	gcz
--
SceneProp.gcz_mastermember_count 	= 1115
SceneProp.gcz_tower_group_count 	= 1116
SceneProp.gcz_shg_last_owner		= 1120
SceneProp.gcz_tcsc_portal		= 1121

EntityProp.gcz_kill_count 	= 1300
EntityProp.gcz_dead_count 	= 1301
EntityProp.gcz_sc_holdtime 	= 1302
EntityProp.gcz_shg_holdtime 	= 1303
EntityProp.gcz_sc_hasreward 	= 1304
EntityProp.gcz_shg_hasreward 	= 1305
EntityProp.gcz_mafa_buff 	= 1306
EntityProp.gcz_defense_buff 	= 1307
EntityProp.gcz_insist_time = 1308

--
--          cscg
--
EntityProp.cscg_get_reward_state = 1350
--
--           国庆宝箱
--
EntityProp.gqbx_get_count = 1360
--
--           冲级至尊礼包
--
EntityProp.cjzzlb_get_count = 1370

--
--	转生神殿	zssd
--
SceneProp.zssd_kill_count 	= 1400
SceneProp.zssd_monster_wave 	= 1401

--
--	魔幻星宫	mhxg	十二星宫	sexg
--
SceneProp.mhxg_layer		= 1410
SceneProp.mhxg_player_index	= 1411


--
--	祈福仙子	qfxz
--
SceneProp.qfxz_scene_data	= 1420
SceneProp.qfxz_guild_data	= 1421
SceneProp.qfxz_guild_id		= 1422

--
--	团队副本	tdfb
--

SceneProp.tdfb_boss1id = 1430
SceneProp.tdfb_boss2id = 1431
SceneProp.tdfb_has70per = 1432
SceneProp.tdfb_has50per = 1433
SceneProp.tdfb_has25per = 1434



--
-- 磐龙宝箱 plbx
--
EntityProp.attr_plbx_data = 1600
EntityProp.attr_recharge_old_gift = 1601
EntityProp.attr_gold_useold_gift = 1602

EntityProp.attr_recharge_old = 1700
EntityProp.attr_gold_used_old = 1701

--
-- 幸运转盘 xyzp
--
EntityProp.attr_circle_used_old = 1800
EntityProp.attr_used_free_cnt = 1801

--
--	灵魂链接EntityID
--
EntityProp.attr_link_entity = 1900

---
--  防止pet重置
--
EntityProp.attr_pet_has_load = 1905
--
--  吸收武器
--
EntityProp.attr_m_absorb_weapon_sid = 1910
EntityProp.attr_m_absorb_weapon_lvl = 1911
EntityProp.attr_m_absorb_cloth_sid = 1912
EntityProp.attr_m_absorb_cloth_lvl = 1913
EntityProp.attr_m_absorb_fasion_sid = 1914
EntityProp.attr_m_absorb_fasion_lvl = 1915

--
-- 回馈活动记录
--
EntityProp.attr_ex_coin = 2000 -- 回馈活动兑换券
EntityProp.attr_ex_used_gold = 2001 -- 回馈活动元宝记录
--10000~20000
EntityProp.attr_repay_event = 10000--回馈活动次数记录


--
--	不要在这个代码后面定义数据
--
disableTableNewIndexing(SceneProp)
disableTableNewIndexing(ItemProp)
disableTableNewIndexing(WorldProp)
disableTableNewIndexing(GuildProp)
disableTableNewIndexing(FuncProp)
--
--	不要在这个代码后面定义数据
--
