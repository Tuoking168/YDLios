#include "NetRunnable.h"
#include "HandleMessage.h"
#include "Message/MsgIf.h"
#include "MsgListener.h"
#include "MsgCreator.h"

#include "Msghandler/MsgMaster.h"

MsgListener	* HandleMessage::s_msglistener		= NULL;
MsgListener	* HandleMessage::s_gsMsglistener	= NULL;
MsgListener	* HandleMessage::s_amsMsglistener	= NULL;
MsgListener	* HandleMessage::s_csMsglistener	= NULL;
MsgMaster	* HandleMessage::s_user				= NULL;

void HandleMessage::RecvMessage(IMsg* msg)
{
	if (s_user)
		s_user->updateMessage(msg);
}

void HandleMessage::sendMessage(IMsg* msg)
{
	if (!msg)
	{
		return;
	}

	switch (msg->getMsgCate())
	{
	case Msg::MC_Auth:
		if (s_amsMsglistener && s_amsMsglistener->m_network)
		{
			s_amsMsglistener->m_network->Send(msg);
		}
		else
		{
			delete msg;
		}
		break;
	default:
		if (s_gsMsglistener && s_gsMsglistener->m_network)
		{
			s_gsMsglistener->m_network->Send(msg);
		}
		else if (s_csMsglistener && s_csMsglistener->m_network)
		{
			s_csMsglistener->m_network->Send(msg);
		}
		else
		{
			delete msg;
		}
		break;
	}

// 	if (s_msglistener->m_network)
// 	{
// 		s_msglistener->m_network->Send(msg);
// 	}
// 	else
// 	{
// 		delete msg;
// 	}
}

void HandleMessage::sendMessage( const std::string &name )
{
	IMsg *msg = MsgCreator::create(name);
	if (msg)
	{
		sendMessage(msg);
	}
}

void HandleMessage::setUser( MsgMaster* m_master )
{
	if (s_user)
	{
		delete s_user;
	}
	s_user = m_master;
}

bool HandleMessage::hasUser()
{
	return s_user!=NULL;
}

void HandleMessage::createMsgListener()
{
	s_msglistener = new MsgListener();
	s_msglistener->addScheduleUpdate();

	s_gsMsglistener = new MsgListener();
	s_gsMsglistener->addScheduleUpdate();

	s_amsMsglistener = new MsgListener(false);
	s_amsMsglistener->addScheduleUpdate();

	s_csMsglistener = new MsgListener();
	s_csMsglistener->addScheduleUpdate();
}

void HandleMessage::releaseMsgListener()
{
	if (s_msglistener)
	{
		s_msglistener->stopServer();
		s_msglistener->release();
	}

	if (s_gsMsglistener)
	{
		s_gsMsglistener->stopServer();
		s_gsMsglistener->release();
	}

	if (s_amsMsglistener)
	{
		s_amsMsglistener->stopServer();
		s_amsMsglistener->release();
	}

	if (s_csMsglistener)
	{
		s_csMsglistener->stopServer();
		s_csMsglistener->release();
	}
}

void HandleMessage::setIsBackground(bool value)
{
	if (s_gsMsglistener && s_gsMsglistener->m_network)
	{
		s_gsMsglistener->m_network->setIsBackground(value);
	}

	if (s_amsMsglistener && s_amsMsglistener->m_network)
	{
		s_amsMsglistener->m_network->setIsBackground(value);
	}

	if (s_msglistener && s_msglistener->m_network)
	{
		s_msglistener->m_network->setIsBackground(value);
	}

	if (s_csMsglistener && s_csMsglistener->m_network)
	{
		s_csMsglistener->m_network->setIsBackground(value);
	}
}

void HandleMessage::startAMSServer(const std::string &ip, uint16 port)
{	
	if (s_amsMsglistener)
	{
		s_amsMsglistener->startServer(ip, port);
	}

	// close other listener
	if (s_gsMsglistener)
	{
		s_gsMsglistener->stopServer();
	}
	if (s_csMsglistener)
	{
		s_csMsglistener->stopServer();
	}
}

void HandleMessage::restartAMSServer(const std::string &ip, uint16 port)
{	
	if (s_amsMsglistener)
	{
		// Modify By Tony. 2014/9/30 9:39
		// If you want to restart server, you make sure ip is not equal to latest ip.
		// use empty string to replace the latest ip.
		s_amsMsglistener->startServer("", 0);
		s_amsMsglistener->startServer(ip, port);
	}

	// close other listener
	if (s_gsMsglistener)
	{
		s_gsMsglistener->stopServer();
	}
	if (s_csMsglistener)
	{
		s_csMsglistener->stopServer();
	}
}

void HandleMessage::startGSServer(const std::string &ip, uint16 port)
{
	if (s_gsMsglistener)
	{
		s_gsMsglistener->startServer(ip, port);
	}

	// close other listener
	if (s_amsMsglistener)
	{
		s_amsMsglistener->stopServer();
	}
	if (s_csMsglistener)
	{
		s_csMsglistener->stopServer();
	}
}

void HandleMessage::restartGSServer(const std::string &ip, uint16 port)
{
	if (s_gsMsglistener)
	{
		// Modify By Tony. 2014/9/30 9:39
		// If you want to restart server, you make sure ip is not equal to latest ip.
		// use empty string to replace the latest ip.
		s_gsMsglistener->startServer("", 0);
		s_gsMsglistener->startServer(ip, port);
	}

	// close other listener
	if (s_amsMsglistener)
	{
		s_amsMsglistener->stopServer();
	}
	if (s_csMsglistener)
	{
		s_csMsglistener->stopServer();
	}
}

void HandleMessage::startCSServer(const std::string &ip, uint16 port)
{
	if (s_csMsglistener)
	{
		s_csMsglistener->startServer(ip, port);
	}

	// close other listener
	if (s_amsMsglistener)
	{
		s_amsMsglistener->stopServer();
	}
	if (s_gsMsglistener)
	{
		s_gsMsglistener->stopServer();
	}
}

void HandleMessage::restartCSServer(const std::string &ip, uint16 port)
{	
	if (s_csMsglistener)
	{
		// Modify By Tony. 2014/9/30 9:39
		// If you want to restart server, you make sure ip is not equal to latest ip.
		// use empty string to replace the latest ip.
		s_csMsglistener->startServer("", 0);
		s_csMsglistener->startServer(ip, port);
	}

	// close other listener
	if (s_amsMsglistener)
	{
		s_amsMsglistener->stopServer();
	}
	if (s_gsMsglistener)
	{
		s_gsMsglistener->stopServer();
	}
}