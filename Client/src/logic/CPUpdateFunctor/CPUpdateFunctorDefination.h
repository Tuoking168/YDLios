#ifndef __CPUPUDATEFUNCTOR_DEFINATION__
#define __CPUPUDATEFUNCTOR_DEFINATION__

namespace CPUFDefination
{
	enum TagID
	{
		PotionTagBegin = 100,

		PotionHpBegin = 100,
		HpLow_Potion1 = 101,
		HpLow_Potion2 = 102,
		HpLow_Scroll  = 103,
		PotionHpEnd   = 120,

		PotionMpBegin = 120,
		MpLow_Potion1 = 121,
		MpLow_Potion2 = 122,
		PotionMpEnd	  = 140,

		EquipDuration = 140,

		PotionTagEnd = 200,

		SkillTagBegin = 201,
		Skill_DS_Hui_Fu_Shu = 201,
		Skill_DS_ZhaoHuan   = 202,
		SkillTagEnd = 300,
	};
}

#endif