#ifndef __Spider_DATA_H__
#define __Spider_DATA_H__

#include "stdafx.h"
#include "userdata/UserItemData.h"


class spiderdata
{
public:
	static void addItem(UserItem* p);
	static void rmvItem(UserItem* p);
	static void rmvallItem();
	static bool hasItem(UserItem* p);
public:
	static std::vector<UserItem*> zmjz_list;	
	static bool m_bisdouble;
	static std::vector<int> vec_iid;
};


#endif//__Spider_DATA_H__