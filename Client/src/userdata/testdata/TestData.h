//////////////////////////////////////////////////////////////////////////
//功能：客户端临时完成一些数据结构的临时数据填充，以方便上层界面功能的实现。
//		填充的数据结构可能有：物品数据，技能数据等等。
//时间：2013-07-11 10:20
//作者tom
//////////////////////////////////////////////////////////////////////////
#ifndef __TEST_DATA_H__
#define __TEST_DATA_H__

class  DataTest
{
public:
	//初始化所有测试数据
	static void InitAllTestData();
	//填充技能临时数
	static void TestSkill();
	//填充角色列表临时数据
	static void TestSelectRole();
	//填充主角临时数据
	static void TestMainRole();
	//填充状态数据，比如魔法盾状态，中毒状态等
	static void TestNetStatus();
	//填充组队数据，用于测试
	static void TestTeamData();
	//填充寻宝数据，用于测试
	static void TestTreasureHunt();
};

#endif//__TEST_DATA_H__