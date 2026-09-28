#ifndef __OptionsHelper_h__
#define __OptionsHelper_h__

#include <string>
#include "LoginModule.h"
#include "CCSprite.h"
#include "MsgGuild.h"

using namespace cocos2d;

struct OptionsInfo {
	std::string resource;
	std::string title;
	int owner;
	int idx;
}; 
typedef std::vector<OptionsInfo> OptionsList;

class OptionsHelper
{
public:
	//static std::string getMyGuildName();
	static int getMainSize(std::string tableName);
	static std::string  getMainResource(std::string tableName,int idx);
	static std::string  getMainTitle(std::string tableName,int idx);
	static int getMainCtrlID(std::string tableName,int idx);
	static int  getMainOwner(std::string tableName,int idx);
	static int  getMainTag(std::string tableName,int idx);
	static bool  hasSubOption(std::string tableName,int idx);

	static int getSubSize(std::string tableName,int idx);
	static std::string  getSubResource(std::string tableName,int idx,int sidx);
	static std::string  getSubTitle(std::string tableName,int idx,int sidx);
	static int getSubCtrlID(std::string tableName,int idx,int sidx);
	static int  getSubOwner(std::string tableName,int idx,int sidx);

	static void initAllOptionsList(OptionsList& oList,std::string tableName);
	static void openOption(OptionsList& oList,std::string tableName,int idx);
	static void closeOption(OptionsList& oList,std::string tableName,int idx);

	static void printOptions(OptionsList& oList);
	static int  getDefaultTag();
	static void setDefaultTag(int idx);
private:
	OptionsHelper();
	OptionsHelper(const OptionsHelper &);
	OptionsHelper &operator=(const OptionsHelper &);  
	~OptionsHelper();

	static int m_defaultidx ;

};

#endif //__OptionsHelper_h__