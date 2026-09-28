gdSoundData = {
	effect = {
		[1] = "data-a/sound/effect_zoulu.mp3",
		[2] = "data-a/sound/effect_shengji.mp3",
		[3] = "data-a/sound/effect_nangongji.mp3",
		[4] = "data-a/sound/effect_nansiwang.mp3",
		[5] = "data-a/sound/effect_nvgongji.mp3",
		[6] = "data-a/sound/effect_nvsiwang.mp3",
		[7] = "data-a/sound/effect_chibanghecheng.mp3",
		[8] = "data-a/sound/effect_dixueliang.mp3",
		[9] = "data-a/sound/effect_genghuanfangjv.mp3",
		[10] = "data-a/sound/effect_genghuanwuqi.mp3",
		[11] = "data-a/sound/effect_hecheng.mp3",
		[12] = "data-a/sound/effect_hunshixiangqian.mp3",
		[13] = "data-a/sound/effect_huodejinbi.mp3",
		[14] = "data-a/sound/effect_jianding.mp3",
		[15] = "data-a/sound/effect_jinenglengque.mp3",
		[16] = "data-a/sound/effect_jipinzhuanyi.mp3",
		[17] = "data-a/sound/effect_qianghua.mp3",
		[18] = "data-a/sound/effect_qianghuashibai.mp3",
		[19] = "",
		[20] = "",
		[21] = "",
		[22] = "",
		[23] = "",
		[24] = "",
		[25] = "",
		[26] = "",
		[27] = "",
		[28] = "",
		[29] = "",
		[30] = "",
		[31] = "",
		[32] = "",
		[33] = "",
		[34] = "",
		[35] = "",
		[36] = "",
		[37] = "",
		[38] = "",
		[39] = "",
		[40] = "",
		[41] = "",
		[42] = "",
		[43] = "",
		[44] = "",
		[45] = "",
		[46] = "",
		[47] = "",
		[48] = "",
		[49] = "",
		[50] = "",
		[51] = "",
		[52] = "",
		[53] = "",
		[54] = "",
		[55] = "",
		[56] = "",
		[57] = "",
		[58] = "",
		[59] = "",
		[60] = "",
		[61] = "",
		[62] = "",
		[63] = "",
		[64] = "",
		[65] = "",
		[66] = "",
		[67] = "",
		[68] = "",
		[69] = "",
		[70] = "",
		[71] = "",
		[72] = "",
		[73] = "",
		[74] = "",
		[75] = "",
		[76] = "",
		[77] = "",
		[78] = "",
		[79] = "",
		[80] = "",
		[81] = "",
		[82] = "",
		[83] = "",
		[84] = "",
		[85] = "",
		[86] = "",
		[87] = "",
		[88] = "",
		[89] = "",
		[90] = "",
		[91] = "",
		[92] = "",
		[93] = "",
		[94] = "",
		[95] = "",
		[96] = "",
		[97] = "",
		[98] = "",
		[99] = "",
		[100] = "",

		-- ººƒ‹“Ù–ß
		[101] = "data-a/sound/effect_banyue.mp3",
		[102] = "data-a/sound/effect_bingfengbao.mp3",
		[103] = "data-a/sound/effect_chuantoushandian.mp3",
		[104] = "data-a/sound/effect_cisha.mp3",
		[105] = "data-a/sound/effect_fashukangjv.mp3",
		[106] = "data-a/sound/effect_fuzhoushu.mp3",
		[107] = "data-a/sound/effect_hudunshu.mp3",
		[108] = "data-a/sound/effect_huifushu.mp3",
		[109] = "data-a/sound/effect_huoqiangshu.mp3",
		[110] = "data-a/sound/effect_huoqiushu.mp3",
		[111] = "data-a/sound/effect_kongjianzhuanyi.mp3",
		[112] = "data-a/sound/effect_liehuo.mp3",
		[113] = "data-a/sound/effect_mofahudun.mp3",
		[114] = "data-a/sound/effect_shenshengleiguang.mp3",
		[115] = "data-a/sound/effect_tianleishu.mp3",
		[116] = "data-a/sound/effect_yindunshu.mp3",
		[117] = "data-a/sound/effect_zhaohuanshu.mp3",
	},

	music = {
		[1] = "data-a/sound/music_login.mp3",
		[2] = "data-a/sound/music_xinshoucun.mp3",
		[3] = "data-a/sound/music_tucheng.mp3",
		[4] = "data-a/sound/music_wangcheng.mp3",
		[5] = "data-a/sound/music_other.mp3",
		[6] = "data-a/sound/music_haidishijie.mp3",
	},
}

g_get_effect_sound_cnt = function()
	local data = gdSoundData.effect
	if data then
		return #data
	end
	return 0
end

g_get_music_sound_cnt = function()
	local data = gdSoundData.music
	if data then
		return #data
	end
	return 0
end

g_get_effect_sound_path = function(index)
	local data = gdSoundData.effect
	if data then
		return data[index] or ""
	end
	return ""
end

g_get_music_sound_path = function(index)
	local data = gdSoundData.music
	if data then
		return data[index] or ""
	end
	return ""
end
