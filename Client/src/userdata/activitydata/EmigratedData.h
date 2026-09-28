#ifndef __Emigrated_DATA_H__
#define __Emigrated_DATA_H__

#include "stdafx.h"

struct stepcase
{
	int type;//哪一种事件
	int data;//第几个
};

class Emigrateddata
{
public:
	static std::vector<int> cscg_list;	

	static std::vector<stepcase> cscg_caselist;

};


#endif//__Emigrated_DATA_H__