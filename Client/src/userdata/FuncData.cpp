#include "FuncData.h"
#include "event/CPEventHelper.h"
#include <cstring>
#include "WorldDefinition.h"
#include "MsgWorld.h"
#include "network/HandleMessage.h"
#include "MsgPlayer.h"
#include "logic/platform/IPlatform.h"
#include "script/LuaWrapper.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "module/UserDataModule.h"


int FuncData::m_iFuncID;
FuncMap FuncData::m_mFuncList;
int FuncData::getCurFuncID()
{
	return FuncData::m_iFuncID;
}

void FuncData::setCurFuncID( int funcid )
{
	FuncData::m_iFuncID = funcid;
	Func f;
	f.datax = 0;
	f.datay = 0;
	f.dataz = 0;
	m_mFuncList[funcid] = f;
}

void FuncData::sendFuncMsgWithID( int funcid,int datax/*= 0*/,int datay/*= 0*/,int dataz/*= 0*/ )
{
	MsgFuncDataOperatorRequest* req = new MsgFuncDataOperatorRequest;
	req->funcid = funcid;
	req->datax = datax;
	req->datay = datay;
	req->dataz = dataz;
	HandleMessage::sendMessage(req);

	clearFunc(funcid);
}

void FuncData::sendFuncMsg( int datax /*= 0*/,int datay/*= 0*/,int dataz/*= 0*/ )
{
	sendFuncMsgWithID(FuncData::getCurFuncID(),datax,datay,dataz);
}

int FuncData::getdatax(int funcid)
{
	FuncMap::iterator it = m_mFuncList.find(funcid);
	if (it != m_mFuncList.end())
	{
		return it->second.datax;
	}
	return 0;
}

void FuncData::setdatax( int data )
{
	m_mFuncList[getCurFuncID()].datax = data;
}

int FuncData::getdatay(int funcid)
{
	FuncMap::iterator it = m_mFuncList.find(funcid);
	if (it != m_mFuncList.end())
	{
		return it->second.datay;
	}
	return 0;
}

void FuncData::setdatay( int data )
{
	m_mFuncList[getCurFuncID()].datay = data;
}

int FuncData::getdataz(int funcid)
{
	FuncMap::iterator it = m_mFuncList.find(funcid);
	if (it != m_mFuncList.end())
	{
		return it->second.dataz;
	}
	return 0;
}

void FuncData::setdataz( int data )
{
	m_mFuncList[getCurFuncID()].dataz = data;
}

void FuncData::clearFunc( int funcid )
{
	FuncMap::iterator it = m_mFuncList.find(funcid);
	if (it != m_mFuncList.end())
	{
		m_mFuncList.erase(it);
	}
}

int FuncData::checkNowMemory()
{
	int n = 0;
	Lua::instance()->call("getNowMemory",0,1);
	Lua::instance()->pop(n);

	return n;
}

