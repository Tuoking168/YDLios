//////////////////////////////////////////////////////////////////////////
// NetRunnable.cpp
// 
// W.Y-J
// 2011.11.21
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetRunnable.h"
#include "MsgStream.h"
#include "MsgLogin.h"
#include <assert.h>
#include "Service.h"
#include "NetworkService.h"
#include "log.h"
#include <stdlib.h>
#include "MsgDownload.h"
#ifndef WIN32
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netdb.h>
#endif


#define PING_INTERVAL		5
#define NETWORK_TOLARENT	5
#ifdef _DEBUG
#define AGING_TIME		60
#else
#define AGING_TIME		60
#endif

namespace WOE
{

NetRunnable::NetRunnable(MsgBuilderWithFactory* builder, LockedQueue<Event *> &eventq, bool enableBackground)
: m_stopEvent(false),
  event_queue(eventq),
  m_netConnected(false),
  m_lastSendMsgTime(0),
  m_lastRecvMsgTime(0),
  m_sockClient(0),
  m_to_be_disconnected(false),
  m_ping(false),
  m_checking_alive(false),
  m_isInBackgroud(false),
  m_isInDownloading(false),
  m_aging_counter(0),
  m_MsgBuilder(builder)
{
}

NetRunnable::~NetRunnable()
{
	m_stopEvent = true;
	delete m_MsgBuilder;
	m_MsgBuilder = NULL;
}

#define  Deadtime 30
void NetRunnable::run()
{
	m_stopEvent = false;

	if (!Initialize())
	{
		m_stopEvent = true;
		LOG_ERROR("NetworkService::m_task :failed to initialize");
		return;
	}

	while (!m_stopEvent)
	{
		if (m_netConnected)
		{
			handle_input();

			handle_output();
		
			time_t cur = time(NULL);
			if ( m_isInBackgroud &&
				(cur - m_lastSendMsgTime > PING_INTERVAL && m_aging_counter < (300 / PING_INTERVAL)/*|| cur - m_lastRecvMsgTime > PING_INTERVAL*/ ))
			{
				ping();
				m_aging_counter ++;
			}
			if (cur - m_lastRecvMsgTime > PING_INTERVAL+NETWORK_TOLARENT)
			{
				LOG_INFO("No Network message received for long!");
				if (NetworkService::getNetState() == NS_Connected)
					NetworkService::setNetState(NS_Disconnected);
				networkBroken();
			}	
		}

		Dispath();

		if(m_netConnected)
		{
#ifdef WIN32
			Sleep(3);
#else
			usleep(3);
#endif
		}
		else
		{
#ifdef WIN32
			Sleep(1500);
#else
			usleep(1500000);
#endif
			LOG_INFO("Network reconnecting ...");
			m_netConnected = Connect();
		}

	}

	if (!UnInitialize())
	{
		assert(false);
	}
}

void NetRunnable::stop()
{
	m_stopEvent = true;
}

bool NetRunnable::Initialize()
{
	NetworkService::m_task = this;
	LOG_INFO("Start to initialize network!");
#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err; 

	wVersionRequested = MAKEWORD(1,1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if( err != 0){
		return false;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1)
	{
			WSACleanup();
			return false;
	}
#endif
	if (m_to_be_disconnected)
	{
		m_netConnected = Connect();
	}
	if (! m_netConnected)
	{
		LOG_DEBUG("init my network no ready ");
		networkNotReady();
	}
	else
	{
		m_to_be_disconnected = false;
	}

	return true;
}

bool NetRunnable::Connect()
{
	if (m_sockClient)
	{
		LOG_INFO("m_sockclient  = "<<m_sockClient);
	}
	if (m_ip.empty())
	{
		return false;
	}
	//
	//	try to resolve the host to ip address
	//
	struct hostent *hp = gethostbyname(m_ip.c_str());
	if (hp==NULL)
	{
		LOG_INFO("Failed to resolve -> "<<m_ip<<":"<<m_port);
		return false;
	}
	struct in_addr in;
	memcpy (&in.s_addr,hp->h_addr,4);
	string m_ip=inet_ntoa(in);

	//
	//	try to connect to real server
	//
	if (m_sockClient==0)
	{
		m_sockClient = socket(AF_INET, SOCK_STREAM, 0);
	}
	m_addrSrv.sin_addr.s_addr = inet_addr(m_ip.c_str()); 
	m_addrSrv.sin_family = AF_INET;
	m_addrSrv.sin_port = htons(m_port);

	
	int ret = connect(m_sockClient, (const sockaddr*)&m_addrSrv, sizeof(const sockaddr));
	if(ret==-1)
	{
		LOG_INFO("Failed to connect -> "<<m_ip<<":"<<m_port);
#ifdef WIN32
		closesocket(m_sockClient);
#else
		close(m_sockClient);
#endif
		m_sockClient =0;
		return false;
	}

	LOG_INFO("Success to connect -> "<<m_ip<<":"<<m_port);

	m_to_be_disconnected = false;
	unsigned   long   ul   =   1; 
#ifdef WIN32
	ret   =   ioctlsocket(m_sockClient,   FIONBIO,   (unsigned   long*)&ul);
#else
	ret   =   ioctl(m_sockClient,   FIONBIO,   (unsigned   long*)&ul);
#endif
	if(ret==-1)
	{ 
		LOG_INFO("Failed to ioctlsocket , unknow error");
		return false;
	}
	m_ping = false;
	m_netConnected = true;
	NetworkService::setNetState(NS_Connected);
	networkBorn();
	m_lastSendMsgTime = time(NULL);
	m_lastRecvMsgTime = time(NULL);
	return true;
}

bool NetRunnable::Reconnect(const std::string& ip, uint16 port)
{
	if (m_ip!=ip || m_port!=port)
	{
		m_ip = ip;
		m_port = port;
		Disconnect();
	}
	else
	{
		if (m_netConnected)
		{
			networkBorn();
			LOG_INFO("Network is already connected!");
		}
		else
		{
			LOG_INFO("Network is connecting!");
		}
	}
	return true;
}

bool NetRunnable::Disconnect()
{
	m_to_be_disconnected = true;
	NetworkService::setNetState(NS_Disconnected);
	return true;
}

bool NetRunnable::UnInitialize()
{
	if (NetworkService::m_task == this) 
		NetworkService::m_task = NULL;
	LOG_INFO("Uninitialize current network");
	
#ifdef WIN32
	closesocket(m_sockClient);
	WSACleanup();
#else
	shutdown(m_sockClient, SHUT_RDWR);
	close(m_sockClient);
#endif
	MsgBuffer* buffer = NULL;
	while (snd_queue.next(buffer) && buffer)
	{
		delete buffer;
	}
	return true;
}

void NetRunnable::do_disconnect()
{
	if (m_netConnected)
	{
		LOG_INFO("do disconnect shutdown m_sockClient");
#ifdef WIN32
		shutdown(m_sockClient, SD_BOTH);
		closesocket(m_sockClient);
#else
		shutdown(m_sockClient, SHUT_RDWR);
		close(m_sockClient);
#endif
		m_sockClient = 0;
		m_netConnected = false;
		NetworkService::setNetState(NS_Disconnected);
	}
}

void NetRunnable::networkBorn()
{
 	if (!m_isInBackgroud)
 	{
		CliEvent* NetBorn = new CliEvent;
		NetBorn->cmd = Event::NETWORKBORN;
		NetBorn->type = Event::CLIENT;
		event_queue.add_back(NetBorn);
	}
}

void NetRunnable::networkBroken()
{
	m_netConnected = false;
 	if (!m_isInBackgroud)
 	{
		CliEvent* Netbroken = new CliEvent;
		Netbroken->cmd = Event::NETWORKBROKEN;
		Netbroken->type = Event::CLIENT;
		event_queue.add_back(Netbroken);
	}
}

void NetRunnable::networkNotReady()
{
 	if (!m_isInBackgroud)
 	{
		CliEvent* Netbroken = new CliEvent;
		Netbroken->cmd = Event::NETWORKNOTREADY;
		Netbroken->type = Event::CLIENT;
		event_queue.add_back(Netbroken);
	}
}

void NetRunnable::networkAlive()
{
 	if (!m_isInBackgroud)
 	{
		CliEvent* Netbroken = new CliEvent;
		Netbroken->cmd = Event::NETWORKALIVE;
		Netbroken->type = Event::CLIENT;
		event_queue.add_back(Netbroken);
	}
}

bool NetRunnable::Send( IMsg *msg )
{
	if (m_netConnected)
	{
		if (!msg)
			return false;

		MsgBuffer *buffer = new MsgBuffer;
		MsgOStream stream(*buffer);
		if (m_MsgBuilder->onEncodeMsg(msg, stream))
		{
#ifdef WIN32
			MsgSizeEvent *msgsize = new MsgSizeEvent;
			msgsize->type = Event::MSGSIZE;
			msgsize->MsgName = msg->getMsgName();
			msgsize->size = stream.size();
			event_queue.add_back(msgsize);
#endif 

			msg->dump();
			snd_queue.add_back(buffer);
	
			delete msg;
			return true;
		}

		delete buffer;
	}
	else
	{
		networkNotReady();
		if (msg)	delete msg;
	}
	return true;
}

void NetRunnable::checkAlive()
{
	if (m_netConnected)
	{
		m_checking_alive = true;
		ping();
	}
}

bool NetRunnable::Dispath()
{
	MsgBuffer *buffer = NULL;
	while (rcv_queue.next(buffer) && buffer)
	{
 		MsgIStream stream(*buffer);
 		IMsg *msg = NULL;
		stream.removeread();
		int size = stream.size();
 		int rvt = m_MsgBuilder->onDecodeMsg(msg, stream);
		//LOG_INFO("Decode one msg!");
		if (rvt == 0 && msg!=NULL)
		{
#ifdef WIN32
			MsgSizeEvent *msgsize = new MsgSizeEvent;
			msgsize->type = Event::MSGSIZE;
			msgsize->MsgName = msg->getMsgName();
			msgsize->size = size - stream.size();
			//msgsize->url = buffer->rd_ptr();
			event_queue.add_back(msgsize);
#endif
			//msg->dump();
			if (msg->getMsgCate() == Msg::MC_Login && msg->getMsgID() == MsgPong::Id)
			{
				if (m_checking_alive)
				{
					m_checking_alive = false;
					networkAlive();
				}
				delete msg;
			}
			else
			{
				SrvEvent *event = new SrvEvent;
				event->type = Event::SERVER;
				event->msg = msg;
				msg->dump();
				event_queue.add_back(event);
			}
		}
		else if (rvt == 1)
		{
			MsgBuffer *nBuffer = NULL;
			if (rcv_queue.next(nBuffer) && nBuffer)
			{
				buffer->append(*nBuffer);
				LOG_INFO("append buffer size = "<<buffer->size());
				rcv_queue.add_front(buffer);
				delete nBuffer;
				nBuffer = NULL;
				continue;
			}
			else
			{

				LOG_INFO("recv Buffer is not complete ,wait for next and leave dispath!");
				rcv_queue.add_front(buffer);
				break;
			}
		}
		else
		{
			LOG_ERROR("Failed to decode network message!");
			delete buffer;
			continue;
		}
		stream.removeread();
		if (buffer->size()== 0)
		{
			delete buffer;
		}
		else
		{
			rcv_queue.add_front(buffer);
		}

	}
	return true;
}

int NetRunnable::handle_input()
{
	fd_set   set;
	char buf[MSG_BUFF_SIZE];
	struct timeval tv;
	while (true)
	{
		FD_ZERO(&set);
		FD_SET(m_sockClient, &set);
		tv.tv_sec = 0;
		tv.tv_usec = 100;
#ifdef WIN32
		int ret = select(0, &set, NULL, NULL, &tv);
#else
		int ret = select(m_sockClient + 1, &set, NULL, NULL, &tv);
#endif
		switch (ret)
		{
		case 0:
			if (m_to_be_disconnected)
			{
				LOG_INFO("select ret = 0 and is to be disconnected");
				do_disconnect();
				m_to_be_disconnected = false;
			}
			return -1;		// over time 
		case (-1):
			{
				if (errno == EINTR)
					break;
			}
			return 0;
		default:
			if (FD_ISSET(m_sockClient, &set))
			{
				int rcv_size = recv(m_sockClient, buf, MSG_BUFF_SIZE, 0);
				if (rcv_size <= 0)
				{
					if (errno == EINTR || errno == EAGAIN || errno == 10035L)
					{
						return -1;
					}
					// quit
					// network broken
					LOG_INFO("Network disconnected!");
					do_disconnect();
	 				NetworkService::setNetState(NS_Disconnected);
					networkBroken();
					return 0;
				}
				else
				{
					m_ping = false;
					m_lastRecvMsgTime = time(NULL);
					MsgBuffer *buffer = new MsgBuffer(rcv_size);
					memcpy( buffer->wr_ptr(), buf, rcv_size );
					buffer->wr_ptr(rcv_size);

					rcv_queue.add_back(buffer);
				}
			}
		}
	}
	return -1;
}

int NetRunnable::handle_output()
{
	MsgBuffer* buffer = NULL;
	while (snd_queue.next(buffer) && buffer)
	{
		int snd_size = send(m_sockClient, buffer->rd_ptr(), buffer->size(), 0);
		if (snd_size <= 0)
		{
			snd_queue.add_front(buffer);
			return -1;
		}
		else if (snd_size < (int)buffer->size())
		{
			buffer->rd_ptr(snd_size);
			snd_queue.add_front(buffer);
		}
		else if (snd_size == buffer->size())
		{
			m_lastSendMsgTime = time(NULL);
			delete buffer;
		}
	}
	return 0;
}

void NetRunnable::ping()
{
// 	if (m_isInBackgroud && !m_isInDownloading)
// 	{
// #ifndef WIN32
// 		if (m_aging_counter++>AGING_TIME)
// 		{
// 			LOG_INFO("Too long in background, process quit!");
// 			exit(0);
// 			return;
// 		}
// #endif
// 	}
	m_ping = true;
	MsgPing* pi = new MsgPing;
	Send(pi);
}

void NetRunnable::setIsBackground(bool v)
{
	m_aging_counter = 0;
	m_isInBackgroud = v;
	if (!m_netConnected)
	{
		networkNotReady();
	}
	else
	{
		networkAlive();
	}
}

void NetRunnable::setIsDownloading(bool v)
{
	m_isInDownloading = v;
}

}