#ifndef __CPEventHelper_h__
#define __CPEventHelper_h__

#include <string>
#include "EventModule.h"
#include "CPEvent.h"
#include "utils/MacroUtils.h"

class CPEventHelper
{
public:
	static void dispatcher(const std::string &eventName, const std::string &source, const std::string &target);

	static void msgResponse(const std::string &source, const std::string &target, int errcode);
	static void msgNotify(const std::string &source, const std::string &target);
	static void msgNotify(const std::string &source, const std::string &target, int opcode, int data1, int data2, int data3);
	static void msgNotify(const std::string &source, const std::string &target, int opcode, int data1, int data2, int data3, int data4);
	static void msgNotify(const std::string &source, const std::string &target, int opcode, std::string data1, int data2, int data3);
	static void msgNotify(const std::string &source, const std::string &target, int opcode, std::string data1, std::string data2, int data3,int data4);
	static void msgNotify(const std::string &source, const std::string &target, int opcode, int data1, int data2, int data3, std::string data4);

	static void uiNotify(const std::string &source, const std::string &target, int errcode);

	static void openPanel(const std::string &panelName);
	static void openPanel(const std::string &panelName, int data1,int data2,int data3,int data4);
	static void openPanel(const std::string &panelName, const std::string &data1, int data2, int data3, int data4);
	static void openPanel(const std::string &panelName, int data1, const std::string & data2);

	static std::string getEventSource();
	static std::string getEventTarget();
	static bool isRequestSuccess();

	static void setEventIntData(const std::string &eventName, const std::string &key, int data);
	static void setEventStringData(const std::string &eventName, const std::string &key, const std::string &data);
	static int getEventIntData(const std::string &key);
	static std::string getEventStringData(const std::string &key);

private:
	CP_MAKE_STATIC_CLASS(CPEventHelper);
};
#endif //__CPEventHelper_h__