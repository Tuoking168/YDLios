#ifndef __HeroData_h__
#define __HeroData_h__

#include <vector>
#include "utils/MacroUtils.h"
#include <string>

typedef std::vector<int> IDVector;
class HeroData
{
public:
	static void setPID(int pid);
	static int getPID();

	static void setLevel(int level);
	static int getLevel();
	static std::string getLevelString();

	static void setJob(int job);
	static int getJob();

	static void setGender(int gender);
	static int getGender();

	static void setProp(int key, int value);
	static int getProp(int key);

	static void updateBuff(int geneID, int duration ,int buffid);
	static int getBuffTime(int geneID);
	static int getBuffStartTime(int geneID);
	static void removeBuff(int geneID);
	static bool hasBuff(int geneID);
	static IDVector getBuffVect();

	static void resetGlobalCD();
	static void setGlobalCD(float cd);
	static float getGlobalCD();

	static void setCommonCD(int cdID, int cd, int ex);
	static int getCommonCD(int cdID);
	static int getCommonCDEx(int cdID);

	// skill
	static void setSkillExp(int skillID, int exp);
	static int getSkillExp(int skillID);

	static void setSkillCD(int skillID, int cd);
	static int getSkillCD(int skillID);

	static IDVector getSkillVect();
	static bool hasSkill(int skillID);
	static void clearSkill(int skillID);
	static void clearAllSkill();

	//
	static void setRewardTime(int timeID, int time, int data1, int data2, int data3);
	static int getRewardTime(int timeID);
	static void getRewardTimeEx(int timeID, int &data1, int &data2, int &data3);

	// head name
	static IDVector getOwnedHeadNames();
	static IDVector getWornHeadNames();
	static IDVector getHeadNames(int base);
	static bool getHeadNameIsOwned(int id);
	static bool getHeadNameIsWorn(int id);

	static void clear();

private:
	CP_MAKE_STATIC_CLASS(HeroData);
};
#endif //__HeroData_h__