#include "MsgCreator.h"
#include "CCCommon.h"
#include "MsgPlayer.h"

#include "script/LuaWrapper.h"

using namespace cocos2d;

typedef IMsg *(*Creator)();
typedef std::map<std::string, Creator> CreatorMap;

#define ADD_CREATOR(_map_, _class_) _map_[#_class_] = create##_class_;


static IMsg *createMsgGetOtherPlayerDataRequest()
{
	MsgGetOtherPlayerDataRequest *msg = new MsgGetOtherPlayerDataRequest;
	CPLua->pop(msg->pid);
	return msg;
}

static void addCreator( CreatorMap &creatorMap )
{
	ADD_CREATOR(creatorMap, MsgGetOtherPlayerDataRequest);
}

///////MsgCreator//////////////////////////////////////////////////
IMsg * MsgCreator::create( const std::string &msgName )
{
	static CreatorMap creatorMap;
	if (creatorMap.empty())
	{
		addCreator(creatorMap);
	}

	//
	CreatorMap::iterator it = creatorMap.find(msgName);
	if (it != creatorMap.end())
	{
		return it->second();
	}
	CCLog(">>>Error: MsgCreator::create, unknown msgName = %s", msgName.c_str());
	return NULL;
}
