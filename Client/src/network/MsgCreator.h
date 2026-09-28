#ifndef __MsgCreator_h__
#define __MsgCreator_h__

#include "utils/MacroUtils.h"
#include <string>

class IMsg;
class MsgCreator
{
public:
	//
	// create msg by lua
	//
	static IMsg *create(const std::string &msgName);

private:
	CP_MAKE_STATIC_CLASS(MsgCreator);
};
#endif //__MsgCreator_h__