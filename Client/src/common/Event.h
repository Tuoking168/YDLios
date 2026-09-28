//////////////////////////////////////////////////////////////////////////
// Scene.h
// 
// W.Y-J
// 2011.11.24
//////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_H__
#define __EVENT_H__

class Event
{
public:
	Event(){;};
	virtual ~Event(){;};
	enum {
		SERVER,
		CLIENT,
		MSGSIZE,
		DOWNLOAD,
	};
	enum ClientCmd
	{
		NETWORKBORN		= 0,
		NETWORKBROKEN		= 1,
		NETWORKNOTREADY		= 2,
		NETWORKALIVE		= 3,
	};
	enum DownloadCmd
	{
		UrlDownload		= 0,
		LuaTransfer		= 1,
		
	};
	int type;
};

class IMsg;
class SrvEvent : public Event
{
public:
	SrvEvent(){;};
	virtual ~SrvEvent(){;};
	IMsg *msg;
};

class MsgSizeEvent: public Event
{
public:
	MsgSizeEvent(){;};
	virtual ~MsgSizeEvent(){;};
	std::string MsgName;
	int	size;
};

class CliEvent : public Event
{
public:
	CliEvent(){;};
	virtual ~CliEvent(){;};
	int	cmd;
};

class DownloadEvent: public Event
{
public:
	DownloadEvent(){;};
	virtual ~DownloadEvent(){;};
	IMsg *msg;
};

#endif //__EVENT_H__
