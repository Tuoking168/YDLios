#include "CPEventDispatcher.h"
#include "IEventListener.h"
#include "CCCommon.h"
#include "ModuleData.h"
#include "EventModule.h"
#include "script/LuaWrapper.h"


using namespace cocos2d;

static void dispatcherToLua( const std::string &eventName )
{
	Lua::instance()->push(eventName);
	Lua::instance()->call("gdceapon", "dispatcher_event", 1, 0);
}

static void clearEventData( const std::string &eventName )
{
	SubModuleData::init(CPModuleName::EVENT, eventName);
	SubModuleData::clearAll();
}

///////////CPEventDispatcher////////////////////////////////////////////
CPEventDispatcher::CPEventDispatcher()
{
	
}

CPEventDispatcher::~CPEventDispatcher()
{

}

CPEventDispatcher & CPEventDispatcher::instance()
{
	static CPEventDispatcher dispatcher;
	return dispatcher;
}

void CPEventDispatcher::addEventListener( const std::string &eventName, IEventListener *listener )
{
	if (listener)
	{
		removeEventListener(eventName, listener);
		mMapListener[eventName].push_back(listener);
	}
	else
	{
		CCLog(">>>Error: addEventListener failed, listener = NULL, eventName = %s", eventName.c_str());
	}
}

void CPEventDispatcher::removeEventListener(IEventListener* listener)
{
	if (listener)
	{
		for (ItMapList iter = mMapListener.begin(), end = mMapListener.end(); iter != end; ++ iter)
		{
			iter->second.remove(listener);
		}
	}
}

void CPEventDispatcher::removeEventListener( const std::string &eventName, IEventListener *listener )
{
	if (!eventName.empty() &&
		listener)
	{
		ItMapList itML = mMapListener.find(eventName);
		if (itML != mMapListener.end())
		{
			itML->second.remove(listener);

			//
			ItList itL = mMapTemp[eventName].begin();
			ItList itLEnd = mMapTemp[eventName].end();
			while (itL != itLEnd)
			{
				if ((*itL) == listener)
				{
					(*itL) = NULL;
				}
				itL++;
			}

			//
			if (itML->second.empty())
			{
				mMapListener.erase(itML);
			}
		}
	}
	else
	{
		CCLog(">>>Error: removeEventListener failed, listener = NULL, eventName = %s", eventName.c_str());
	}
}

void CPEventDispatcher::dispatcherEvent( const std::string &eventName )
{
	mEventNames.push_back(eventName);

	// to c++
	ItMapList itML = mMapListener.find(eventName);
	if (itML != mMapListener.end())
	{
		// mark
		mMapTemp[eventName].clear();
		ItList itL = itML->second.begin();
		ItList itLEnd = itML->second.end();
		while (itL != itLEnd)
		{
			mMapTemp[eventName].push_back((*itL));
			itL++;
		}

		// dispatcher
		itL = mMapTemp[eventName].begin();
		itLEnd = mMapTemp[eventName].end();
		while (itL != itLEnd)
		{
			IEventListener *listener = (*itL);
			if (listener)
			{
				listener->onCPEvent(eventName);
			}
			itL++;
		}
		mMapTemp[eventName].clear();
	}

	// to lua
	dispatcherToLua(eventName);

	// clear
	clearEventData(eventName);
	mEventNames.pop_back();
}

bool CPEventDispatcher::hasEventListener( const std::string &eventName )
{
	ItMapList itML = mMapListener.find(eventName);
	return (itML != mMapListener.end());
}

std::string CPEventDispatcher::getCurrentEvent() const
{
	if (!mEventNames.empty())
	{
		return mEventNames[mEventNames.size() - 1];
	}
	return "";
}
