//////////////////////////////////////////////////////////////////////////
// NetworkService.h
// 
// W.Y-J
// 2012.5.23
//////////////////////////////////////////////////////////////////////////

#ifndef __NETWORKSERVICE_H__
#define __NETWORKSERVICE_H__

namespace WOE {
	class NetRunnable;
}

typedef enum _NetState
{
	NS_Connected = 0,
	NS_Connecting,
	NS_Disconnected,
	NS_NetworkError,
	NS_DeviceError,	
} NetState;

class NetworkService
{
public:
	static bool OpenBackgroundSocket(unsigned int s, void *& iStream, void *&oStream);
	static bool CloseBackgroundSocket(void *& iStream, void *&oStream);
	
	static void BackgroundPing();

	static void setNetworkDeviceError();
	
	static void		setNetState(NetState ns);
	static NetState getNetState();
public:
	static WOE::NetRunnable *m_task;
	static NetState	m_snetState;	
};

#endif // __NETWORKSERVICE_H__