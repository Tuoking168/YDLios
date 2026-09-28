#include "Properties.h"
#include <stdlib.h>
#include "userdata/luadata/LuaData.h"

namespace woe
{

	Properties::Properties(const std::string& file_name /* = */ )
	{
		if (!file_name.empty())
		{
			init(file_name);
		}
	}

	bool Properties::init(const std::string& file_name)
	{	
		file_name_ =  file_name;
		return true;
	}

	bool Properties::parse(const std::string& key)
	{
		if (!LuaData::checkKeyExist(file_name_,key))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Properties::parse(const std::string& key, std::string& value)
	{
		if (!LuaData::getProp(file_name_,key,value))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Properties::parse(const std::string& key, short& value)
	{
		int value_i;
		if (!LuaData::getProp(file_name_,key,value_i))
		{
			return false;
		}
		else
		{
			value = value_i;
			return true;
		}
	}

	bool Properties::parse(const std::string& key, int& value)
	{
		if (!LuaData::getProp(file_name_,key,value))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Properties::parse(const std::string& key, float& value)
	{
		if (!LuaData::getProp(file_name_,key,value))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Properties::parse(const std::string& key, bool& value)
	{
		int value_i;
		if (!LuaData::getProp(file_name_,key,value_i))
		{
			return false;
		}
		else
		{
			value = (value_i!=0);
			return true;
		}
	}
}