#ifndef ___RES_PATH_H__
#define ___RES_PATH_H__

#include <string>



class PathR
{
public:
	static void		initialize();

	//
	//	convert a relative path to an absolute path
	static void		convert(std::string& path, const char* relative);
	static void		convert(std::string& path);


	const char*	convert(const char* relative);
protected:
	static std::string  _path_header;
	std::string			_path_data;
};

class PathW
{
public:
	static void		initialize();

	//
	//	convert a relative path to an absolute path
	static void		convert(std::string& path, const char* relative);
	static void		convert(std::string& path);


	const char*	convert(const char* relative);
protected:
	static std::string  _path_header;
	std::string			_path_data;
};


#endif

