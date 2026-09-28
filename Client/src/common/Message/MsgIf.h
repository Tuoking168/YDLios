#ifndef __MESSAGE_BASE_INTERFACE___
#define __MESSAGE_BASE_INTERFACE___


//
//	Stream
//
#include "MsgStream.h"

//
//	Message Interface
//
class  IMsg
{
public:
	virtual ~IMsg(){;}

	//
	//	message id
	//
	virtual void	setMsgID(short nID) = 0;
	virtual short	getMsgID()const = 0;

	//
	//	message category
	//
	virtual void	setMsgCate(char nCate) = 0;
	virtual char	getMsgCate()const = 0;

	virtual const char* getMsgName()const = 0;
	virtual int getLength() const = 0;

	//
	//	message session id
	//
	virtual void	setSID(int nPID) = 0;
	virtual int		getSID()const = 0;

	//
	//	decode a message from a stream
	//
	virtual bool decode(MsgIStream& stream) = 0;
	//
	//	encode a message into a stream
	//
	virtual bool encode(MsgOStream& stream) = 0;

	//
	//	dump the message information to log
	//
	virtual void dump() = 0;
	
	//
	//	check validation of message
	//
	virtual bool validate() = 0;
};

#endif
