#include "TestData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/AliveGhost.h"
#include "userdata/teamdata/TeamData.h"
#include "userdata/activitydata/TreasureHuntData.h"

void DataTest::TestSkill()
{////
	////GameData::s_user->m_pMainRole->m_skill
	////作为测试，先自行填充一些数据，以供显示使用，这里填充一些技能的id,和param1：0被动，1主动
	//int SkillTestData[4][4] = 
	//{
	//	{0,0,0,0},
	//	{131,121,141,111},
	//	{211,221,231,261},
	//	{301,311,321,331}
	//};
	//int job = HeroData::getJob();
	//for (int i=0; i<4; i++)
	//{
	//	NetSkill pSkill;
	//	pSkill.mTypeID = SkillTestData[job][i];
	//	pSkill.mParam1 = 1;
	//	GameData::s_user->m_pMainRole->m_netSkill.push_back(pSkill);
	//}
}

void DataTest::InitAllTestData()
{
	//
//	TestSkill();
//	TestNetStatus();
//	TestTeamData();
}

void DataTest::TestSelectRole()
{
// 	std::vector<NetChar>& charList = GameData::s_user->mCharList;
// 	int listsize = charList.size();
// 	for(int i=0; i<listsize; i++)
// 	{
// 		NetChar &nc = charList[i];
// 		nc.mWeapon = -1;
// 		if (nc.mGender == UserData::SEX_FEMALE)
// 		{
// 			if(nc.mJob == UserData::CARRER_ZS)	
// 			{
// 				nc.mCloth = 70035;
// 			}
// 			else if(nc.mJob == UserData::CARRER_FS)
// 			{
// 				nc.mCloth = 70001; 
// 			}
// 			else if(nc.mJob == UserData::CARRER_DS)
// 			{
// 				nc.mCloth = 70050;
// 			}
// 		}
// 		else
// 		{
// 			if(nc.mJob == UserData::CARRER_ZS)	
// 			{
// 				nc.mCloth = 70034; 
// 			}
// 			else if(nc.mJob == UserData::CARRER_FS)
// 			{
// 				nc.mCloth = 70000; 
// 			}
// 			else if(nc.mJob == UserData::CARRER_DS)
// 			{
// 				nc.mCloth = 70049;
// 			}
// 		}
// 	}
}

void DataTest::TestMainRole()
{
	//
}

void DataTest::TestNetStatus()
{
	//
}

void DataTest::TestTeamData()
{
	TeamData::mTeamMembers.resize(5);
	for (int i=0; i<5; i++)
	{
		TeamData::TeamMember gm;
		gm.pid = i;
		gm.name = "Member "+SystemData::intToString(i);
		gm.state = 1;
		TeamData::mTeamMembers[i] = gm;
	}
}

void DataTest::TestTreasureHunt()
{
	///TODO: set some test data for TreasureHunt
}

