//////////////////////////////////////////////////////////////////////////
// NetRunnable.h
// 
// W.Y-J
// 2011.11.21
//////////////////////////////////////////////////////////////////////////

#ifndef __NETRUNNABLE_H__
#define __NETRUNNABLE_H__

#ifndef WIN32
#include <netinet/in.h>
#else
#include <winsock2.h>
#endif

#include "Threading.h"
#include "LockedQueue.h"
#include "Message/MsgIf.h"
#include "Message/MsgBuilderSimple.h"
#include "Event.h"
#include "CommonType.h"
#include "MsgBuffer.h"

class IMsg;
class MsgBuffer;
namespace WOE
{
class NetRunnable : public Runnable
{
public:
	NetRunnable(MsgBuilderWithFactory* builder, LockedQueue<Event *> &eventq, bool enableBackground);
	~NetRunnable();

	virtual void run();
	virtual void stop();

	virtual bool Connect();
	virtual bool Reconnect(const std::string& ip, uint16 port);
	virtual bool Disconnect();

	virtual bool Send(IMsg *msg);

	void checkAlive();

	void setIP(std::string ip) { m_ip = ip; }
	std::string getIP() const { return m_ip; }

	void setPort(uint16 port) { m_port = port; }
	uint16 getPort() const { return m_port; }

	void setIsBackground(bool v);
	void setIsDownloading(bool v);

	void networkBorn();
	void networkBroken();
	void networkNotReady();
	void networkAlive();
private:
	bool Initialize();
	bool UnInitialize();
	void do_disconnect();

	bool Dispath();

	int handle_input();

	int handle_output();

	void ping();
private:
	unsigned int m_sockClient;
	struct sockaddr_in m_addrSrv;

	std::string m_ip;
	uint16		m_port;
	bool		m_to_be_disconnected;	//reconnect

	MsgBuilderWithFactory* m_MsgBuilder;

	LockedQueue<MsgBuffer *> snd_queue; 
	LockedQueue<MsgBuffer *> rcv_queue; 

	LockedQueue<Event *>	&event_queue;


	volatile bool	m_stopEvent;
	bool		m_netConnected;

	time_t		m_lastSendMsgTime;		// last received message time
	time_t	    m_lastRecvMsgTime;
	bool		m_ping;			// just ping
	bool		m_checking_alive;
	bool		m_isInBackgroud;
	bool		m_isInDownloading;
	int		m_aging_counter;	

};

}
#endif // __NETRUNNABLE_H__ 
