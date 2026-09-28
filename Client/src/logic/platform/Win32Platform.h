#ifndef __Win32Platform_h__
#define __Win32Platform_h__

#include "IPlatform.h"

class Win32Platform : public IPlatform
{
public:
	Win32Platform();
	~Win32Platform();

	virtual void login();
	virtual void pay(int yuan);
	virtual void operate(int opID);
	virtual std::string convert(const std::string &data);
	virtual void selectGameSever(int);
};
#endif //__Win32Platform_h__
