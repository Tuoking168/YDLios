//////////////////////////////////////////////////////////////////////////
// NetworkService.mm
// 
// W.Y-J
// 2012.5.23
//////////////////////////////////////////////////////////////////////////

#ifndef WIN32
#include "stdafx.h"
#endif
#include "NetworkService.h"
#include "netrunnable.h"

WOE::NetRunnable * NetworkService::m_task = NULL;
NetState	NetworkService::m_snetState = NS_Disconnected;

bool NetworkService::OpenBackgroundSocket(unsigned int s, void *& iStream, void *&oStream)
{
	iStream = 0;
	oStream = 0;
	if (s == 0)
		return false;
	
	CFReadStreamRef readStream;
	CFWriteStreamRef writeStream;
	CFStreamCreatePairWithSocket(NULL, s,  &readStream, &writeStream);
	NSInputStream *inStream = (NSInputStream *)readStream;
	NSOutputStream *outStream = (NSOutputStream *)writeStream;       
	
	if(inStream == nil)
		return false;
	[inStream setProperty:NSStreamNetworkServiceTypeVoIP forKey:NSStreamNetworkServiceType];
	[outStream setProperty:NSStreamNetworkServiceTypeVoIP forKey:NSStreamNetworkServiceType];
	
	[inStream open];
	[outStream open];
	
	iStream = (void *)inStream;
	oStream = (void *)outStream;
	return true;
}

bool NetworkService::CloseBackgroundSocket(void *& iStream, void *&oStream)
{
	int ret = true;
	if (iStream != nil)
	{
		NSInputStream *inStream = (NSInputStream *)iStream;
		[inStream close];
		iStream = nil;
	}
	else 
	{
		ret = false;
	}

	
	if (oStream != nil)
	{
		NSOutputStream *outStream = (NSOutputStream *)oStream;
		[outStream close];
		oStream = nil;
	}
	else
	{
		ret = false;
	}
	
	return ret;
}

void NetworkService::BackgroundPing()
{
	if (m_task)
		m_task->BackgroundPing();
}

void NetworkService::updateLastMsgTime()
{
	if (m_task)
		m_task->updateLastMsgTime();
}

void NetworkService::setNetworkDeviceError()
{
	printf("================ NetworkService::setNetworkDeviceError : %p(WOE::NS_DeviceError)\n", m_task);
	setNetState(NS_DeviceError);
}