 //////////////////////////////////////////////////////////////////////////
// NetworkService.cpp
// 
// W.Y-J
// 2012.5.23
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetworkService.h"

WOE::NetRunnable *NetworkService::m_task = NULL;
NetState	NetworkService::m_snetState = NS_Disconnected;

bool NetworkService::OpenBackgroundSocket( unsigned int s, void *& iStream, void *&oStream )
{
	return true;
}

bool NetworkService::CloseBackgroundSocket( void *& iStream, void *&oStream )
{
	return true;
}

void NetworkService::BackgroundPing()
{
}

void NetworkService::setNetworkDeviceError()
{
}

void NetworkService::setNetState(NetState ns)
 { 
	 m_snetState = ns; 
}

NetState
NetworkService::getNetState()
{
	return m_snetState;
}