#include "SpiderData.h"

static std::vector<UserItem*> emptyItemVector;
static std::vector<int> vec_iid2;
std::vector<UserItem*> spiderdata::zmjz_list=emptyItemVector;
std::vector<int> spiderdata::vec_iid=vec_iid2;
bool spiderdata::m_bisdouble=false;

void spiderdata::addItem( UserItem* p )
{
	if (spiderdata::zmjz_list.size()>20)
	{
		return;
	}
	std::vector<UserItem*>::iterator it=spiderdata::zmjz_list.begin();
	for (it;it!=spiderdata::zmjz_list.end();it++)
	{
		UserItem* p1=*it;
		if (p1->iid==p->iid)
		{
			return;
		}
	}
	spiderdata::zmjz_list.push_back(p);
	spiderdata::vec_iid.push_back(p->iid);
}

void spiderdata::rmvItem( UserItem* p )
{
	std::vector<UserItem*>::iterator it=spiderdata::zmjz_list.begin();
	for (it;it!=spiderdata::zmjz_list.end();it++)
	{
		UserItem* p1=*it;
		if (p1->iid==p->iid)
		{
			spiderdata::zmjz_list.erase(it);
			break;
		}
	}
	std::vector<int>::iterator it2=spiderdata::vec_iid.begin();
	for (it2;it2!=spiderdata::vec_iid.end();it2++)
	{
		int p1=*it2;
		if (p1==p->iid)
		{
			spiderdata::vec_iid.erase(it2);
			break;
		}
	}
}

void spiderdata::rmvallItem()
{
	spiderdata::zmjz_list.clear();
	spiderdata::vec_iid.clear();
}

bool spiderdata::hasItem( UserItem* p )
{
	std::vector<UserItem*>::iterator it=spiderdata::zmjz_list.begin();
	for (it;it!=spiderdata::zmjz_list.end();it++)
	{
		UserItem* p1=*it;
		if (p1->iid==p->iid)
		{
			return true;
		}
	}
	return false;
}
