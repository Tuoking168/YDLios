//////////////////////////////////////////////////////////////////////////
// Properties.h
// 
// W.Y-J
// 2012.3.28
//////////////////////////////////////////////////////////////////////////


#ifndef __PROPERTIES_H__
#define	__PROPERTIES_H__
#include <string>

namespace woe
{
	
	//
	//	a simple properties file parser
	//
	class Properties
	{
	public:
		Properties(const std::string& file_name = "");
		bool init(const std::string& file_name);

		//
		//	parse configuration
		//
		bool parse(const std::string& key);
		bool parse(const std::string& key, short& value);
		bool parse(const std::string& key, int& value);
		bool parse(const std::string& key, float& value);
		bool parse(const std::string& key, bool& value);
		bool parse(const std::string& key, std::string& value);

	protected:
		std::string	file_name_;
	};
}


#endif	// __PROPERTIES_H__

