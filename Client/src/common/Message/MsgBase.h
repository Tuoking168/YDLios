#ifndef __MESSAGE_BASE___
#define __MESSAGE_BASE___

#include "MsgIf.h"
#include "log.h"
//
//	Message Base
//
class MsgBase : public IMsg
{
public:
	MsgBase(char nCate, short nID);

	virtual void	setMsgID(short nID);
	virtual short	getMsgID()const;

	virtual void	setMsgCate(char nCate);
	virtual char	getMsgCate()const;

	virtual const char* getMsgName()const;

	//
	//	message session id
	//
	virtual void	setSID(int nSID);
	virtual int		getSID()const;

	//
	//	decode a message from a stream
	//
	virtual bool decode(MsgIStream& stream);
	//
	//	encode a message into a stream
	//
	virtual bool encode(MsgOStream& stream);

	//
	//	dump the message information to log
	//
	virtual void dump();

	//
	//	check validation of message
	//
	virtual bool validate();
private:
	char m_nCate;	//	message category
	short m_nID;		//	message id
	int	m_nSessionID;	// message session id
};

#endif
