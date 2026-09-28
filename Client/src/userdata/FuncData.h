#ifndef __FuncData_H__
#define __FuncData_H__

#include "stdafx.h"
#include "cocos2d.h"

using namespace cocos2d;
struct Func
{
	int datax;
	int datay;
	int dataz;
};

typedef std::map<int, Func> FuncMap;
class FuncData
{
public:
	static int getCurFuncID();
	static void setCurFuncID(int funcid);
	static void sendFuncMsgWithID(int funcid,int datax= 0,int datay= 0,int dataz= 0);
	static void sendFuncMsg(int datax = 0,int datay= 0,int dataz= 0);

	static int getdatax(int funcid);
	static void setdatax(int data);
	static int getdatay(int funcid);
	static void setdatay(int data);
	static int getdataz(int funcid);
	static void setdataz(int data);

	static void clearFunc(int funcid);

	static int checkNowMemory();
private:
	static int m_iFuncID;
	static FuncMap m_mFuncList;
};


#endif//__Emigrated_DATA_H__