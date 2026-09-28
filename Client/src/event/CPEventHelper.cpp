#include "CPEventHelper.h"
#include "CPEventDispatcher.h"
#include "ModuleData.h"
#include "ErrorDefinition.h"

///////////CPEventHelper///////////////////////////////////////////////////
void CPEventHelper::dispatcher( const std::string &eventName, const std::string &source, const std::string &target )
{
	setEventStringData(eventName, CPEventData::SOURCE, source);
	setEventStringData(eventName, CPEventData::TARGET, target);
	CPEvtDispatcher.dispatcherEvent(eventName);
}

void CPEventHelper::msgResponse( const std::string &source, const std::string &target, int errcode )
{
	setEventIntData(CPEventName::MSG_FINISH, CPEventData::VALUE_1, errcode);
	dispatcher(CPEventName::MSG_FINISH, source, target);
}

void CPEventHelper::msgNotify( const std::string &source, const std::string &target )
{
	msgNotify(source, target, 0, 0, 0, 0);
}

void CPEventHelper::msgNotify( const std::string &source, const std::string &target, int opcode, int data1, int data2, int data3 )
{
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_1, opcode);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_2, data1);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_3, data2);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_4, data3);
	dispatcher(CPEventName::MSG_CHANGE, source, target);
}

void CPEventHelper::msgNotify( const std::string &source, const std::string &target, int opcode, int data1, int data2, int data3, int data4 )
{
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_1, opcode);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_2, data1);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_3, data2);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_4, data3);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_5, data4);
	dispatcher(CPEventName::MSG_CHANGE, source, target);
}


void CPEventHelper::msgNotify(const std::string &source, const std::string &target, int opcode, std::string data1, int data2, int data3)
{
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_1, opcode);
	setEventStringData(CPEventName::MSG_CHANGE, CPEventData::VALUE_2, data1);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_3, data2);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_4, data3);
	dispatcher(CPEventName::MSG_CHANGE, source, target);
}

void CPEventHelper::msgNotify(const std::string &source, const std::string &target, int opcode, std::string data1, std::string data2, int data3,int data4)
{
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_1, opcode);
	setEventStringData(CPEventName::MSG_CHANGE, CPEventData::VALUE_2, data1);
	setEventStringData(CPEventName::MSG_CHANGE, CPEventData::VALUE_3, data2);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_4, data3);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_5, data4);
	dispatcher(CPEventName::MSG_CHANGE, source, target);
}

void CPEventHelper::msgNotify( const std::string &source, const std::string &target, int opcode, int data1, int data2, int data3, std::string data4 )
{
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_1, opcode);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_2, data1);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_3, data2);
	setEventIntData(CPEventName::MSG_CHANGE, CPEventData::VALUE_4, data3);
	setEventStringData(CPEventName::MSG_CHANGE, CPEventData::VALUE_5, data4);
	dispatcher(CPEventName::MSG_CHANGE, source, target);
}

void CPEventHelper::uiNotify( const std::string &source, const std::string &target, int errcode )
{
	setEventIntData(CPEventName::UI_NOTIFY, CPEventData::VALUE_1, errcode);
	dispatcher(CPEventName::UI_NOTIFY, source, target);
}

void CPEventHelper::openPanel( const std::string &panelName )
{
	setEventStringData(CPEventName::UI_OPEN, CPEventData::VALUE_1, panelName);
	dispatcher(CPEventName::UI_OPEN, "", "GameUI");
}

void CPEventHelper::openPanel( const std::string &panelName, int data1,int data2,int data3 ,int data4)
{
	setEventStringData(CPEventName::UI_OPEN, CPEventData::VALUE_1, panelName);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_2, data1);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_3, data2);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_4, data3);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_5, data4);
	dispatcher(CPEventName::UI_OPEN, "", "GameUI");
}

void CPEventHelper::openPanel( const std::string &panelName, const std::string &data1, int data2, int data3, int data4 )
{
	setEventStringData(CPEventName::UI_OPEN, CPEventData::VALUE_1, panelName);
	setEventStringData(CPEventName::UI_OPEN, CPEventData::VALUE_2, data1);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_3, data2);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_4, data3);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_5, data4);
	dispatcher(CPEventName::UI_OPEN, "", "GameUI");
}

void CPEventHelper::openPanel(const std::string &panelName, int data1, const std::string & data2)
{
	setEventStringData(CPEventName::UI_OPEN, CPEventData::VALUE_1, panelName);
	setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_2, data1);
	setEventStringData(CPEventName::UI_OPEN, CPEventData::VALUE_3, data2);
	dispatcher(CPEventName::UI_OPEN, "", "GameUI");
}

std::string CPEventHelper::getEventSource()
{
	return getEventStringData(CPEventData::SOURCE);
}

std::string CPEventHelper::getEventTarget()
{
	return getEventStringData(CPEventData::TARGET);
}

bool CPEventHelper::isRequestSuccess()
{
	const int errcode = getEventIntData(CPEventData::VALUE_1);
	return errcode == Error::Success;
}

void CPEventHelper::setEventIntData( const std::string &eventName, const std::string &key, int data )
{
	SubModuleData::init(CPModuleName::EVENT, eventName);
	SubModuleData::setInt(1, key, data);
}

void CPEventHelper::setEventStringData( const std::string &eventName, const std::string &key, const std::string &data )
{
	SubModuleData::init(CPModuleName::EVENT, eventName);
	SubModuleData::setString(1, key, data);
}

int CPEventHelper::getEventIntData( const std::string &key )
{
	int ret = 0;
	const std::string &eventName = CPEvtDispatcher.getCurrentEvent();
	if (!eventName.empty())
	{
		SubModuleData::init(CPModuleName::EVENT, eventName);
		SubModuleData::getInt(1, key, ret);
	}
	return ret;
}

std::string CPEventHelper::getEventStringData( const std::string &key )
{
	std::string ret;
	const std::string &eventName = CPEvtDispatcher.getCurrentEvent();
	if (!eventName.empty())
	{
		SubModuleData::init(CPModuleName::EVENT, eventName);
		SubModuleData::getString(1, key, ret);
	}
	return ret;
}
