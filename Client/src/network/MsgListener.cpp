#include "MsgListener.h"
#include <string>
#include "HandleMessage.h"

#include "common/NetRunnable.h"
#include "common/Message/MsgIf.h"
#include "common/Threading.h"

#include "event/CPEventHelper.h"

#include "LuaWrapper.h"
#include "MsgLogin.h"

#define NetWorkReconnectTimeMax 180
#define NetWorkReconnectCntMax 3


#include "CCDirector.h"
#include "CCScheduler.h"
using namespace cocos2d;


MsgListener::MsgListener(bool bUseCRC):m_bUseCRC(bUseCRC), MsgUseSize(0),m_ping_interval(5.0f)
{
	m_network = NULL;
	m_httptextRecv = NULL;
}

MsgListener::~MsgListener()
{
	stopServer();
}

void
	MsgListener::startServer(std::string ip, uint16 port)
{
	if (m_network == NULL)
	{
		m_network = new WOE::NetRunnable(new MsgBuilderWithFactory(m_bUseCRC), m_events, true);
		m_thread.start(m_network);
	}
	m_network->Reconnect(ip, port);
	m_events.empty();
}

void
	MsgListener::stopServer()
{
	m_thread.stop();
	Event *event=NULL;
	while (m_events.next(event))
	{
		if (event)
		{
			if (event->type == Event::SERVER)
			{
				SrvEvent *se = (SrvEvent *)event;
				if (se->msg)
				{
					// HandleMessage::RecvMessage(se->msg);
					delete se->msg;
				}
			}
			delete event;
		}
	}
	if (m_network)
	{
		delete m_network;
		m_network=NULL;
	}
}

void
	MsgListener::update(float dt)
{
	const int PER_TURN = 6;

	m_ping_interval -= dt;
	if (m_ping_interval < 0)
	{
		m_ping_interval += 5.0f;
		MsgPing* pi = new MsgPing;
		if (m_network)
		{
			m_network->Send(pi);
		}
		//HandleMessage::sendMessage(pi);
	}

	Event *event = NULL;
	for (int i = 0; i < PER_TURN; i++)
	{
		bool logb = false;
		if (m_events.size() >0 )
		{
			logb = true;
		}
		if (m_events.next(event))
		{
			switch (event->type)
			{
			case Event::SERVER:
				{
					SrvEvent *se = (SrvEvent *)event;
					if (se->msg)
					{
						HandleMessage::RecvMessage(se->msg);
						delete se->msg;
					}
				}
				break;
			case Event::CLIENT:
				{
					CliEvent *ce = (CliEvent *)event;
					handleClientEvent(ce->cmd);
				}
				break;
			case Event::MSGSIZE:
				{
#ifdef WIN32
					MsgSizeEvent *ce = (MsgSizeEvent *)event;
					Lua::instance()->push(ce->MsgName);
					Lua::instance()->push(ce->size);
					Lua::instance()->call("record","msgsizerecord",2,0);
					MsgUseSize ++;
					if (MsgUseSize % 20000 == 0)
					{
						std::string url = "";
						Lua::instance()->call("record","saveRecord",0,1);
						Lua::instance()->pop(url);
						MsgUseSize = 0;
						if (url != "")
						{
							startTextRecv();
							m_httptextRecv->setUrl(url);
						}
 					}
#endif // WIN32
				}
				break;
			case Event::DOWNLOAD:
				{
					DownloadEvent *evt = (DownloadEvent *)event;
					if (evt)
					{
						HandleMessage::RecvMessage(evt->msg);
						delete evt->msg;
					}
				}
				break;
			default:
				break;
			}
			delete event;
		}
		else
		{
			return;
		}
	}	

#ifdef WIN32
	if (m_httptextRecv && m_httptextRecv->isRecv())
	{
		stopTextRecv();
	}
#endif
}

void MsgListener::handleClientEvent( int eventType )
{
	if (eventType == Event::NETWORKBROKEN ||
		eventType == Event::NETWORKBORN ||
		eventType == Event::NETWORKNOTREADY||
		eventType == Event::NETWORKALIVE)
	{
		CPEventHelper::setEventIntData(CPEventName::NET_CHANGE, CPEventData::VALUE_1, eventType);
		CPEventHelper::dispatcher(CPEventName::NET_CHANGE, "MsgListener::handleClientEvent", "");
	}
}


void MsgListener::startTextRecv()
{
	if (m_httptextRecv == NULL)
	{
		m_httptextRecv = new httpTextRecv;
	}
	m_httpthread.start(m_httptextRecv);

}

void MsgListener::stopTextRecv()
{
	m_httpthread.stop();

}

void MsgListener::addScheduleUpdate()
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->getScheduler()->scheduleUpdateForTarget(this, -1, false);
}
