#include "stdafx.h"
#include "MsgBase.h"

// #define LOG_DEBUG(a)
#define LOG_DEBUG_V(a, ...)


MsgBase::MsgBase(char nCate, short nID)
:m_nCate(nCate), m_nID(nID),m_nSessionID(0)
{
	;
}

void
MsgBase::setMsgID(short nID)
{
	m_nID = nID;
}

short
MsgBase::getMsgID()const
{
	return m_nID;
}

void
MsgBase::setMsgCate(char nID)
{
	m_nCate = nID;
}

char
MsgBase::getMsgCate()const
{
	return m_nCate;
}

const char* 
MsgBase::getMsgName()const
{
	return "MsgBase";
}

void
MsgBase::setSID(int nPID)
{
	m_nSessionID = nPID;
}

int
MsgBase::getSID()const
{
	return m_nSessionID;
}

bool
MsgBase::decode(MsgIStream& stream)
{
	LOG_DEBUG("Fuck, Please don't call me! MsgBase::decode");
	return false;
}

bool
MsgBase::encode(MsgOStream& stream)
{
	LOG_DEBUG("Fuck, Please don't call me! MsgBase::encode");
	return false;
}

void
MsgBase::dump()
{
	LOG_DEBUG_V("Msg[%d, %d][SID:%d]", m_nCate, m_nID, m_nSessionID);
}

bool
MsgBase::validate()
{
	return true;
}

