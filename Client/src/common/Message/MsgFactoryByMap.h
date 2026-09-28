#ifndef		__MSG_FACTORY__BYMAP__
#define		__MSG_FACTORY__BYMAP__

#ifdef WIN32
#include <hash_map>
#elif defined ANDROID
#include <backward/hash_map>
#else
#include <ext/hash_map>
#endif

class IMsg;
typedef IMsg* (*MessageFunctor)();

//
//	Message Factory
//

class MsgFactoryByMap
{
public:
	MsgFactoryByMap();
	virtual ~MsgFactoryByMap();


	//
	//	create a message base on message category and message id
	//
	virtual	IMsg*	createMsg(int nMsgCate, int nMsgID);


	template<class Msg>
	static IMsg*	create()
	{
		return new Msg;
	}

	void registerMsg(int nCate, int nID, MessageFunctor func);
protected:
#ifdef WIN32
	typedef	stdext::hash_map<int, MessageFunctor>	MessageCreatorMap;
#else
	typedef	__gnu_cxx::hash_map<int, MessageFunctor>	MessageCreatorMap;
#endif	
	MessageCreatorMap m_theMap;
};

#endif

