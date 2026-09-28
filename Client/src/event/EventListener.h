#ifndef __EVENT_LISTENER_H__
#define __EVENT_LISTENER_H__

class  EventListener
{
public:
	EventListener():m_nChannel(-1) {}
	virtual ~EventListener()
	{
	}

public:
	virtual void handleEvent(int channel){};

protected:
	void setChannel(int channel) {m_nChannel=channel;}

private:
	int m_nChannel;
};

#endif // __EVENT_LISTENER_H__
