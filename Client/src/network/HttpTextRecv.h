#ifndef __HTTP_TEXT_RECV_H__
#define __HTTP_TEXT_RECV_H__

#include "Threading.h"

#include <string>
class httpTextRecv : public WOE::Runnable
{
public:
	httpTextRecv();
	httpTextRecv(std::string url);
	~httpTextRecv();

	virtual void run();
	virtual void stop();

	virtual bool Send(IMsg *msg);
public:
	/*void		GetUrlText();*/
	void		setUrl(std::string url);
	bool		isRecv();
	std::string getRecvText();
private:	
	void	GetUrlText();
protected:
	volatile bool	m_stopEvent;
	WOE::Thread			m_thread;
	std::string		m_recv;
	std::string		m_url;
	bool			m_isRecv;
};
#endif
