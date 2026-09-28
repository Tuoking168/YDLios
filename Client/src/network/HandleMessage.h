#ifndef __HANDLE_MESSAGE_H__
#define __HANDLE_MESSAGE_H__

#include <string>
#include "../../shared/CommonType.h"

class IMsg;
class MsgListener;
class MsgMaster;
class MsgPacket;
class HandleMessage
{
public:
	static void RecvMessage(IMsg*);

	static void sendMessage(IMsg*);
	static void sendMessage(const std::string &name);

	// add observer
	static void setUser(MsgMaster* m_master);
	static bool hasUser();

	static void createMsgListener();
	static void releaseMsgListener();
	static void setIsBackground(bool value);

	static void startAMSServer(const std::string &ip, uint16 port);
	static void restartAMSServer(const std::string &ip, uint16 port);
	static void startGSServer(const std::string &ip, uint16 port);
	static void restartGSServer(const std::string &ip, uint16 port);
	static void startCSServer(const std::string &ip, uint16 port);
	static void restartCSServer(const std::string &ip, uint16 port);
public:
	static MsgListener *s_msglistener;

	// just for connecting to GS
	static MsgListener *s_gsMsglistener;
	// just for connecting to AMS
	static MsgListener *s_amsMsglistener;
	// just for connecting to AMS
	static MsgListener *s_csMsglistener;
	
private:
	static MsgMaster *s_user;
};

#endif  // __HANDLE_MESSAGE_H__