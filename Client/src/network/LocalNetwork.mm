//////////////////////////////////////////////////////////////////////////
// LocalNetwork.mm
// 
// W.Y-J
// 2012.5.21
//////////////////////////////////////////////////////////////////////////

#include "LocalNetwork.h"
#import "Reachability.h"

static bool g_first_time = true;

LocalNetwork::LocalNetwork()
{
}

LocalNetwork::~LocalNetwork()
{
}

LNState LocalNetwork::checkNetworkState()
{
	if (g_first_time)
	{
		g_first_time = false;
		return WiFi;
	}
	
	Reachability *r = [Reachability reachabilityWithHostName:@"www.baidu.com"];
    switch ([r currentReachabilityStatus]) 
	{
		case NotReachable:
			return Disable;
		case ReachableViaWiFi:
			return WiFi;
		case ReachableViaWWAN:
			return WWan;
    }
    return Disable;
}