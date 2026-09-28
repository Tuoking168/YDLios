#ifndef __TaskData_h__
#define __TaskData_h__

#include <vector>
#include <map>
#include "utils/MacroUtils.h"

typedef std::vector<int> IDVector;
typedef std::map<int, int> StateMap;
class TaskData
{
public:
	static void setTask(int id, int line, int state, int data1, int data2, int data3);
	static int getTaskLine(int id);
	static int getTaskState(int id);
	static bool getTaskExData(int id, int &data1, int &data2, int &data3);
	static IDVector getCurrentTasks();
	static IDVector getAccessTasks();
	static int getFirstMainLineTask();
	static int getFirstTask(int line);
	static void setCurrentDoingTask(int id);
	static int getCurrentDoingTask();

	static void clearTasks();

private:
	CP_MAKE_STATIC_CLASS(TaskData);

private:
	static StateMap sStateMap;
};
#endif //__TaskData_h__