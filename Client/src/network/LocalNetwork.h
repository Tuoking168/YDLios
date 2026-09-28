//////////////////////////////////////////////////////////////////////////
// LocalNetwork.h
// 
// W.Y-J
// 2012.5.21
//////////////////////////////////////////////////////////////////////////

#ifndef __LOCALNETWORK_H__
#define __LOCALNETWORK_H__

typedef enum _LNState
{
	Disable = 0,
	WiFi,
	WWan
} LNState;

class LocalNetwork
{
public:
	LocalNetwork();
	~LocalNetwork();

	static LNState checkNetworkState();
};

#endif // __LOCALNETWORK_H__