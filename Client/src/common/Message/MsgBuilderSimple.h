#ifndef ___MSG_BUILDER__SIMPLE___
#define ___MSG_BUILDER__SIMPLE___

//
//	A simple message builder with factory
//
//
class IMsg;
class MsgOStream;
class MsgIStream;
class MsgFactoryByMap;
class MsgBuilderWithFactory
{
public:
	MsgBuilderWithFactory(bool bUseCRC = true, MsgFactoryByMap* pFact = 0);
	virtual ~MsgBuilderWithFactory();
	//
	//	serialize a message into a stream
	//
	virtual bool onEncodeMsg(IMsg* pMsg, MsgOStream& stream);

	//	
	//	de-serialize a message from stream
	//
	virtual int onDecodeMsg(IMsg*& pMsg, MsgIStream& stream);

	//
	//	create a message base on message category and message id
	//
	IMsg*	createMsg(int nMsgCate, int nMsgID);
protected:
	bool m_bUseCRC;
	MsgFactoryByMap*	m_pMsgFact;
};


#endif

