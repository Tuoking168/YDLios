#ifndef	___MSG_LISTENER___
#define ___MSG_LISTENER___

#include <string>
#include "CCObject.h"
#include "../common/LockedQueue.h"
#include "../common/Threading.h"
#include "../common/Event.h"
#include "../../shared/CommonType.h"
#include "HttpTextRecv.h"

class IMsg;
namespace WOE
{
	class NetRunnable;
};


class MsgListener : public cocos2d::CCObject
{
public:
	MsgListener(bool bUseCRC = true);
	virtual ~MsgListener();
	virtual void stopServer();
	virtual void startServer(std::string ip, uint16 port);
	virtual void update(float dt);

	virtual void addScheduleUpdate();

private:
	void handleClientEvent(int eventType);
	void startTextRecv();
	void stopTextRecv();

public:
	bool m_bUseCRC;
	WOE::NetRunnable*	m_network;
	WOE::Thread			m_thread;

	httpTextRecv*		m_httptextRecv;
	WOE::Thread			m_httpthread;

	typedef WOE::LockedQueue<Event *> EventQueue;
	EventQueue m_events;

	float m_ping_interval;

private:
	int MsgUseSize;
};

#endif
