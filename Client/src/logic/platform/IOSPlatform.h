#ifndef __IOSPlatform_h__
#define __IOSPlatform_h__

#include "IPlatform.h"

class IOSPlatform : public IPlatform
{
public:
	IOSPlatform();
	~IOSPlatform();

	virtual void login();
	virtual void pay(int yuan);
	virtual void operate(int opID);
	virtual std::string convert(const std::string &data);
	virtual void selectGameSever(int);
};
#endif //__IOSPlatform_h__
