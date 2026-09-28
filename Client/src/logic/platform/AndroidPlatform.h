#ifndef __AndroidPlatform_h__
#define __AndroidPlatform_h__

#include "IPlatform.h"

class AndroidPlatform : public IPlatform
{
public:
	AndroidPlatform();
	~AndroidPlatform();

	virtual void login();
	virtual void pay(int yuan);
	virtual void operate(int opID);
	virtual std::string convert(const std::string &data);
	virtual void selectGameSever( int selectedserver );
};
#endif //AndroidPlatform
