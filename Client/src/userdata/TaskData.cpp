#include "TaskData.h"
#include "TaskModule.h"
#include "ModuleData.h"
#include "QuestDefinition.h"


StateMap TaskData::sStateMap;
static bool isCurrentTask( int id, const StateMap &mapData )
{
	StateMap::const_iterator it = mapData.find(id);
	if (it != mapData.end())
	{
		return (it->second != Quest::state_Available);
	}
	return false;
}
void TaskData::setTask( int id, int line, int state, int data1, int data2, int data3 )
{
	sStateMap[id] = state;
	if (state != Quest::state_Available)
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::ACCESS_TASK_LIST);
		SubModuleData::clearData(id);
		SubModuleData::init(CPModuleName::TASK, CPTaskData::CURRENT_TASK_LIST);
		if (state == Quest::state_Submited)
		{
			SubModuleData::clearData(id);
			return;
		}
	}
	else
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::CURRENT_TASK_LIST);
		SubModuleData::clearData(id);
		SubModuleData::init(CPModuleName::TASK, CPTaskData::ACCESS_TASK_LIST);
	}
	SubModuleData::setInt(id, CPTaskData::LINE, line);
	SubModuleData::setInt(id, CPTaskData::STATE, state);
	SubModuleData::setInt(id, CPTaskData::DATA_1, data1);
	SubModuleData::setInt(id, CPTaskData::DATA_2, data2);
	SubModuleData::setInt(id, CPTaskData::DATA_3, data3);
}

int TaskData::getTaskLine( int id )
{
	if (isCurrentTask(id, sStateMap))
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::CURRENT_TASK_LIST);
	}
	else
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::ACCESS_TASK_LIST);
	}
	int ret = Quest::line_Invalid;
	SubModuleData::getInt(id, CPTaskData::LINE, ret);
	return ret;
}

int TaskData::getTaskState( int id )
{
	if (isCurrentTask(id, sStateMap))
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::CURRENT_TASK_LIST);
	}
	else
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::ACCESS_TASK_LIST);
	}
	int ret = Quest::state_Submited;
	SubModuleData::getInt(id, CPTaskData::STATE, ret);
	return ret;
}

bool TaskData::getTaskExData( int id, int &data1, int &data2, int &data3 )
{
	if (isCurrentTask(id, sStateMap))
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::CURRENT_TASK_LIST);
	}
	else
	{
		SubModuleData::init(CPModuleName::TASK, CPTaskData::ACCESS_TASK_LIST);
	}
	SubModuleData::getInt(id, CPTaskData::DATA_1, data1);
	SubModuleData::getInt(id, CPTaskData::DATA_2, data2);
	SubModuleData::getInt(id, CPTaskData::DATA_3, data3);
	return true;
}

IDVector TaskData::getCurrentTasks()
{
	IDVector ret;
	SubModuleData::init(CPModuleName::TASK, CPTaskData::CURRENT_TASK_LIST);
	SubModuleData::getIDVector(ret);
	return ret;
}

IDVector TaskData::getAccessTasks()
{
	IDVector ret;
	SubModuleData::init(CPModuleName::TASK, CPTaskData::ACCESS_TASK_LIST);
	SubModuleData::getIDVector(ret);
	return ret;
}

int TaskData::getFirstMainLineTask()
{
	return getFirstTask(Quest::line_Main);
}

int TaskData::getFirstTask( int line )
{
	IDVector vect = getCurrentTasks();
	for (int i = 0; i < (int)vect.size(); i++)
	{
		if (getTaskLine(vect[i]) == line)
		{
			return vect[i];
		}
	}

	vect = getAccessTasks();
	for (int i = 0; i < (int)vect.size(); i++)
	{
		if (getTaskLine(vect[i]) == line)
		{
			return vect[i];
		}
	}
	return 0;
}

void TaskData::setCurrentDoingTask( int id )
{
	ModuleData::setInt(CPModuleName::TASK, CPTaskData::CURRENT_DOING_TASK, id);
}

int TaskData::getCurrentDoingTask()
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::TASK, CPTaskData::CURRENT_DOING_TASK, ret);
	return ret;
}

void TaskData::clearTasks()
{
	sStateMap.clear();
	ModuleData::clearModule(CPModuleName::TASK);
}



