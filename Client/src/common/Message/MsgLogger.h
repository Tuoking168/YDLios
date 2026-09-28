#ifndef		___MSG_LOGGER__
#define		___MSG_LOGGER__

#include <string>
#include <stdio.h>


using namespace std;
#pragma warning(push)
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#pragma warning(disable:4996)

//
//	Input stream for messages
//
class MsgLogger //: public std::basic_iostream<char>
{
public:
	MsgLogger( void );

	template<class ComplexType>
	std::string dump(ComplexType& val)
	{
		return val.dump();	
	}

	std::string dump(char& val);
	std::string dump(unsigned char& val);
	std::string dump(short& val);
	std::string dump(unsigned short& val);
	std::string dump(int& val);
	std::string dump(unsigned int& val);
	std::string dump(int64& val);
	std::string dump(uint64& val);
	std::string dump(float& val);
	std::string dump(std::string& val);
};



#pragma warning(pop)
#endif