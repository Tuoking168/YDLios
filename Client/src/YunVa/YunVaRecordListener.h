#ifndef	___YUNVA_RECORD_LISTENER___
#define ___YUNVA_RECORD_LISTENER___

#include <string>

class YunVaRecordListener
{
public:
	virtual void onRecordFinish(int id, std::string & fileUrl, std::string & time) = 0;
};

#endif
