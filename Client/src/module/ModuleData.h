#ifndef __ModuleData_h__
#define __ModuleData_h__

#include <string>
#include <vector>

class ModuleData
{
public:
	static void setInt(const std::string &module, const std::string &key, int value);
	static void setFloat(const std::string &module, const std::string &key, float value);
	static void setString(const std::string &module, const std::string &key, const std::string &value);

	//
	static bool getInt(const std::string &module, const std::string &key, int &value);
	static bool getFloat(const std::string &module, const std::string &key, float &value);
	static bool getString(const std::string &module, const std::string &key, std::string &value);

	//
	static bool getSize(const std::string &module, int &size);
	static bool loadModule(const std::string &module);
	static bool saveModule(const std::string &module);
	static bool clearModule(const std::string &module);
	static bool clearAll();

private:
	ModuleData();
	ModuleData(const ModuleData &);
	ModuleData &operator=(const ModuleData &);
	~ModuleData();
};

/////////SubModuleData/////////////////////////////////////////////
typedef std::vector<int> IDVector;
class SubModuleData
{
public:
	static void init(const std::string &module, const std::string &subModule);

	//
	static void setInt(int id, const std::string &key, int value);
	static void setFloat(int id, const std::string &key, float value);
	static void setString(int id, const std::string &key, const std::string &value);

	//
	static bool getInt(int id, const std::string &key, int &value);
	static bool getFloat(int id, const std::string &key, float &value);
	static bool getString(int id, const std::string &key, std::string &value);

	//
	static bool getSize(int &size);
	static bool getIDVector(IDVector &idVector);
	static bool clearData(int id);
	static bool clearAll();

private:
	SubModuleData();
	SubModuleData(const SubModuleData &);
	SubModuleData &operator=(const SubModuleData &);
	~SubModuleData();

private:
	static std::string moduleName;
	static std::string subModuleName;
};
#endif //__ModuleData_h__