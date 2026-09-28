#ifndef	__LUA_WRAPPER__
#define __LUA_WRAPPER__

#include <string>
using namespace std;
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

const char *  AToU8( const char* str );
const char *  U8ToA( const char* str );

//
//	simple wrapper for lua
//
class  Lua
{
public:
	//Lua();
	Lua(lua_State* pState);

	static Lua*  instance();

	lua_State*	state();

	void load(const char *libname, const luaL_Reg *l);
	void dofile(const char *fname);

	void addSearchPath(const char *path);

	bool getglobal(const char* name, bool& val);
	bool getglobal(const char* name, int& val);
	bool getglobal(const char* name, float& val);
	bool getglobal(const char* name, std::string& val);
	bool setglobal(const char* name, bool val);
	bool setglobal(const char* field, int val);
	bool setglobal(const char* field, float val);
	bool setglobal(const char* field, const char* fmt, ...);
	bool setglobal(const char* field, const std::string& val);

	bool table(const char* name);
	bool setfield();
	bool setfield(const char* field, int val);
	bool setfield(const char* field, float val);
	bool setfield(const char* field, const char* fmt, ...);
	bool setfield(const char* field, const std::string& val);

	bool setfield(int field, int val);
	bool setfield(int field, float val);
	bool setfield(int field, const char* fmt, ...);

	bool getfield(const char* field, int& val);
	bool getfield(const char* field, float& val);
	bool getfield(const char* field, std::string& val);

	//
	//	execute a lua code block
	bool call(const char* code);
	//
	//	execute a lua function with specific input parameters in the stack and specific ouput paramter back in the stack
	bool call(const char* func, int narg, int nres = 0);

	//
	//	execute a lua function with specific input parameters in the stack and specific ouput paramter back in the stack
	bool call(const char* ns, const char* func, int narg, int nres = 0);

	//
	//	execute a lua function with any input parameter and output parameter
	//bool call(const char* func, const char* sig, ...);

	bool push(int val);
	bool push(float val);
	bool push(const char* val);
	bool push(const char* fmt, ...);
	bool push(const std::string& val);
	bool push_utf8(const string& val);
	bool push_global(const char* val);
	bool pop();
	bool pop(bool& val);
	bool pop(short& val);
	bool pop(int& val);
	bool pop(float& val);
	bool pop(std::string& val);
	bool pop_utf8(std::string& val);
protected:
	lua_State* m_pState;
private:
	Lua();
	virtual ~Lua();
	static Lua* s_instance;
};
#define CPLua Lua::instance()

#endif

