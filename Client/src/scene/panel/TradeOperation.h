#ifndef __Trade_OPERATION_H__
#define __Trade_OPERATION_H__

#include "ext/BasePanel.h"


class TradeOperation : public BasePanel
{
public:
	bool init();
	void callback(CCObject* pSender);
	void handleEvent(int channel);
	CREATE_FUNC(TradeOperation);
	
	void setStrList(std::vector<std::string> strlist);
	void onCPEvent(const std::string &eventName);
private:
	std::vector<std::string> m_vStr;
};


#endif//__Trade_OPERATION_H__