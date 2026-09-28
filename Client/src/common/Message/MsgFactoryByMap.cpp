#include "stdafx.h"
#include "MsgFactoryByMap.h"


MsgFactoryByMap::MsgFactoryByMap()
{
}

MsgFactoryByMap::~MsgFactoryByMap()
{
}

IMsg*	
MsgFactoryByMap::createMsg(int nCate, int nID)
{
	nCate <<= 16;
	nCate |= nID;

	MessageFunctor func = m_theMap[nCate];

	if (func)
	{
		return func();
	}
	else
	{
		return NULL;
	}
}

void MsgFactoryByMap::registerMsg(int nCate, int nID, MessageFunctor func)
{
	nCate <<= 16;
	nCate |= nID;

	m_theMap[nCate] = func;
}