#ifndef __MineData_H__
#define __MineData_H__

#include "stdafx.h"

class MineData
{
public:
	static void addMine(int sid ,int count = 1);
	static void clear();
	static int getNewMineCount(int sid);
	static int getAllMineCount(int sid);

private:
	static std::map<int,int> minedata_map;	
	static bool isMine(int sid);
};


#endif//__Emigrated_DATA_H__