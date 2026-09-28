#ifndef __GuideHelper_h__
#define __GuideHelper_h__

#include <string>
#include "utils/MacroUtils.h"

namespace FunctionName
{
	static const std::string JI_NENG = "ji_neng";
	static const std::string ZHUANG_BEI_QIANG_HUA = "zhuang_bei_qiang_hua";
	static const std::string RONG_YV = "rong_yv";
	static const std::string GONG_JI_MO_SHI = "gong_ji_mo_shi";
	static const std::string ZHUANG_BEI_JIAN_DING = "zhuang_bei_jian_ding";
	static const std::string CHONG_WU = "chong_wu";
	static const std::string SHI_TU = "shi_tu";
	static const std::string HANG_HUI = "hang_hui";
	static const std::string BAN_LV = "ban_lv";
	static const std::string ZHUANG_BEI_SHENG_JI = "zhuang_bei_sheng_ji";
	static const std::string HUN_SHI = "hun_shi";
	static const std::string HUAN_WU_QI_LING = "huan_wu_qi_ling";
	static const std::string HE_CHENG = "he_cheng";
	static const std::string SHU_XING_ZHUAN_YI = "shu_xing_zhuan_yi";
	static const std::string ZHUAN_SHENG = "zhuan_sheng";
	static const std::string ZHUAN_SHENG_DUAN_ZAO = "zhuan_sheng_duan_zao";


	static const std::string CAI_SHEN_CHUANG_GUAN = "cai_shen_chuang_guan";
	static const std::string WU_YI_ZHAN_CHANG = "wu_yi_zhan_chang";
	static const std::string ZHAN_SHEN_SHI_CE = "zhan_shen_shi_ce";
	static const std::string ZHAN_SHEN_ZHENG_BA = "zhan_shen_zheng_ba";
	static const std::string ZHAN_LI_JING_JI = "zhan_li_jing_ji";
	static const std::string YONG_SHI_JIAO_DOU_CHANG = "yong_shi_jiao_dou_chang";
	static const std::string XUN_BAO = "xun_bao";
	static const std::string HANG_HUI_ZHENG_DUO_ZHAN = "hang_hui_zheng_duo_zhan";
	static const std::string MEI_RI_GONG_ZI = "mei_ri_gong_zi"; 
	static const std::string PAI_HANG_BANG = "pai_hang_bang";
	static const std::string ZUO_QI = "zuo_qi";
}

////////////GuideHelper/////////////////////////////////////////////////
class GuideHelper
{
public:
	// static control
	static bool canOpenFunction(const std::string &funcName);

	// dynamic control by server
	static bool canOpenFunction(const int funcID);

private:
	CP_MAKE_STATIC_CLASS(GuideHelper);
};
#endif //__GuideHelper_h__