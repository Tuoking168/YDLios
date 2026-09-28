#include "LuaWrapper.h"
#include <stdarg.h>
#include "CCLuaEngine.h"
#include "script_support/CCScriptSupport.h"
#include "log.h"
#include "CCString.h"
#include "CCFileUtils.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "iconv.h"
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include <iconv.h>
#endif

using namespace cocos2d;


static void testStackBalance( lua_State *state )
{
	int i = 7000;
	while (i < 10000)
	{
		if (!lua_checkstack(state, i))
		{
			LOG_INFO("test stack balance: " << i);
			return;
		}

		i += 10;
	}
}

const char* lua_getType(lua_State* L, int idx)
{
	static const char* LUA_TYPE_NAMES[] =
	{
		"LUA_TNONE",//		(-1)

		"LUA_TNIL",//		0
		"LUA_TBOOLEAN",//		1
		"LUA_TLIGHTUSERDATA",//	2
		"LUA_TNUMBER",//		3
		"LUA_TSTRING",//		4
		"LUA_TTABLE",//		5
		"LUA_TFUNCTION",//		6
		"LUA_TUSERDATA",//		7
		"LUA_TTHREAD",//		8
	};

	int nType = lua_type(L, idx);
	if (nType>=LUA_TNONE &&
		nType<=LUA_TTHREAD)
	{
		return LUA_TYPE_NAMES[nType+1];
	}
	else
	{
		return "LUA_TXXXX";
	}
}

static int traceback (lua_State *L) {
	if (!lua_isstring(L, 1))  /* 'message' not a string? */
		return 1;  /* keep it intact */
	lua_getfield(L, LUA_GLOBALSINDEX, "debug");
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);  /* pass error message */
	lua_pushinteger(L, 2);  /* skip this function and traceback */
	lua_call(L, 2, 1);  /* call debug.traceback */
	return 1;
}

static int docall (lua_State *L, int narg, int nres) {
	int status;
	int base = lua_gettop(L) - narg;  /* function index */
	lua_pushcfunction(L, traceback);  /* push traceback function */
	lua_insert(L, base);  /* put it under chunk and args */
	status = lua_pcall(L, narg, nres, base);
	lua_remove(L, base);  /* remove traceback function */
	/* force a complete garbage collection in case of errors */
	if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
	return status;
}


#define	__USE_TRACE_BACK__
#ifdef	__USE_TRACE_BACK__
#define lua_pcall_ex(l, narg, nres)	docall(l, narg, nres)
#else 
#define lua_pcall_ex(l, narg, nres)	lua_pcall(l, narg, nres, 0)
#endif


Lua::Lua(lua_State* pState)
{
	m_pState = pState;
}

Lua::Lua()
{
	// register lua engine
	CCLuaEngine* pEngine =  CCLuaEngine::defaultEngine();
	CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
	m_pState = pEngine->getLuaStack()->getLuaState();
}

Lua::~Lua()
{
	CCScriptEngineManager::sharedManager()->setScriptEngine(NULL);
}

Lua* Lua::s_instance=NULL;
Lua*
Lua::instance()
{

	if (s_instance==NULL)
	{
		static Lua mnger; 
		s_instance=&mnger;
		return s_instance;
	}

	return s_instance;
}

lua_State*
Lua::state()
{
	return m_pState;
}

void Lua::load(const char *libname, const luaL_Reg *l)
{
	luaL_register(m_pState, libname, l);
}

void Lua::dofile(const char* fname)
{
	luaL_dofile(m_pState, fname);
}


void Lua::addSearchPath(const char *path)
{
	lua_getglobal(m_pState, "package");                                  /* stack: package */
	lua_getfield(m_pState, -1, "path");                /* get package.path, stack: package path */
	const char* cur_path =  lua_tostring(m_pState, -1);
	lua_pop(m_pState, 1);                                                /* stack: package */
	lua_pushfstring(m_pState, "%s/?.lua;%s", path, cur_path);            /* stack: package newpath */
	lua_setfield(m_pState, -2, "path");          /* package.path = newpath, stack: package */
	lua_pop(m_pState, 1);
}

bool Lua::table(const char* name)
{
	lua_newtable(m_pState);
	lua_setglobal(m_pState, name);
	lua_getglobal(m_pState, name);
	return true;
}

bool Lua::getglobal(const char* name, bool& val)
{
	int nTop = lua_gettop(m_pState);
	lua_getglobal(m_pState, name);
	if (nTop==lua_gettop(m_pState) || !lua_isboolean(m_pState, -1))
	{
		LOG_ERROR("Lua::getfield, invalid global: " << name);
		return false;
	}

	val = 0!=lua_toboolean(m_pState, -1);
	lua_pop(m_pState, 1);
	return true;
}

bool Lua::getglobal(const char* name, int& val)
{
	int nTop = lua_gettop(m_pState);
	lua_getglobal(m_pState, name);
	if (nTop==lua_gettop(m_pState) || !lua_isnumber(m_pState, -1))
	{
		LOG_ERROR("Lua::getfield, invalid global: " << name);
		return false;
	}

	val = lua_tointeger(m_pState, -1);
	lua_pop(m_pState, 1);
	return true;
}

bool Lua::getglobal(const char* name, float& val)
{
	int nTop = lua_gettop(m_pState);
	lua_getglobal(m_pState, name);

	if (nTop==lua_gettop(m_pState) || !lua_isnumber(m_pState, -1))
	{
		LOG_ERROR("Lua::getfield, invalid global: " << name);
		return false;
	}

	val =(float) lua_tonumber(m_pState, -1);
	lua_pop(m_pState, 1);
	return true;
}

bool Lua::getglobal(const char* name, string& val)
{
	int nTop = lua_gettop(m_pState);
	lua_getglobal(m_pState, name);

	if (nTop==lua_gettop(m_pState) || !lua_isstring(m_pState, -1))
	{
		LOG_ERROR("Lua::getfield, invalid global: " << name);
		return false;
	}

	val = lua_tostring(m_pState, -1);
	lua_pop(m_pState, 1);
	return true;
}

bool Lua::setglobal(const char* name, bool val)
{
	lua_pushboolean(m_pState, val);
	lua_setglobal(m_pState, name);
	return true;
}

bool Lua::setglobal(const char* name, int val)
{
	lua_pushinteger(m_pState, val);
	lua_setglobal(m_pState, name);
	return true;
}

bool Lua::setglobal(const char* name, float val)
{
	lua_pushnumber(m_pState, double(val));
	lua_setglobal(m_pState, name);
	return true;
}

bool Lua::setglobal(const char* name, const char* fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);
	lua_pushvfstring(m_pState, fmt, vl);
	lua_setglobal(m_pState, name);
	return true;
}

bool Lua::setfield()
{
	lua_settable(m_pState, -3);
	return true;
}

bool Lua::setfield(const char* field, int val)
{
	lua_pushstring(m_pState, field);
	lua_pushinteger(m_pState, val);
	lua_settable(m_pState, -3);
	return true;
}

bool Lua::setfield(const char* field, float val)
{
	lua_pushstring(m_pState, field);
	lua_pushnumber(m_pState, double(val));
	lua_settable(m_pState, -3);
	return true;
}

bool Lua::setfield(const char* field, const char* fmt, ...)
{
	lua_pushstring(m_pState, field);
	va_list vl;
	va_start(vl, fmt);
	lua_pushvfstring(m_pState, fmt, vl);
	lua_settable(m_pState, -3);
	return true;
}



bool Lua::setfield(int field, int val)
{
	lua_pushinteger(m_pState, field);
	lua_pushinteger(m_pState, val);
	lua_settable(m_pState, -3);
	return true;
}

bool Lua::setfield(int field, float val)
{
	lua_pushinteger(m_pState, field);
	lua_pushnumber(m_pState, double(val));
	lua_settable(m_pState, -3);
	return true;
}

bool Lua::setfield(int field, const char* fmt, ...)
{
	lua_pushinteger(m_pState, field);
	va_list vl;
	va_start(vl, fmt);
	char szBuff[2048];
#ifdef WIN32
	vsprintf_s(szBuff, 2048, fmt, vl);
#else
	vsnprintf(szBuff, 2048, fmt, vl);
#endif
	lua_pushstring(m_pState, szBuff);
	lua_settable(m_pState, -3);
	return true;
}

bool Lua::setfield(const char* field, const string& val)
{
	lua_pushstring(m_pState, field);
	lua_pushstring(m_pState, val.c_str());
	lua_settable(m_pState, -3);
	return true;
}

bool Lua::getfield(const char* field, int& val)
{
	if (field==NULL || !lua_istable(m_pState,-1))
	{
		return false;
	}

	lua_pushstring(m_pState, field);
	lua_gettable(m_pState, -2);	// table on -2

	if (!lua_isnumber(m_pState, -1))
	{
		//luaL_error(m_pState, "invald table field: %s", field);
		LOG_ERROR("Lua::getfield, invalid table field: " << field);
		return false;
	}

	val = lua_tointeger(m_pState, -1);
	lua_pop(m_pState, 1);
	return true;
}

bool Lua::getfield(const char* field, float& val)
{
	if (field==NULL || !lua_istable(m_pState,-1))
	{
		return false;
	}

	lua_pushstring(m_pState, field);
	lua_gettable(m_pState, -2);	// table on -2

	if (!lua_isnumber(m_pState, -1))
	{
		//luaL_error(m_pState, "invald table field: %s", field);
		LOG_ERROR("Lua::getfield, invalid table field: " << field);
		return false;
	}

	val =(float) lua_tonumber(m_pState, -1);
	lua_pop(m_pState, 1);
	return true;
}

bool Lua::getfield(const char* field, string& val)
{
	if (field==NULL || !lua_istable(m_pState,-1))
	{
		return false;
	}

	lua_pushstring(m_pState, field);
	lua_gettable(m_pState, -2);	// table on -2

	if (!lua_isstring(m_pState, -1))
	{
		//luaL_error(m_pState, "invald table field: %s", field);
		LOG_ERROR("Lua::getfield, invalid table field: " << field);
		return false;
	}

	val = lua_tostring(m_pState, -1);
	lua_pop(m_pState, 1);
	return true;
}

bool
Lua::call(const char* code)
{
	if (0==luaL_loadstring(m_pState, code))
	{
		if (0==lua_pcall_ex(m_pState, 0, 0))
		{
			return true;
		}
		else
		{
			LOG_ERROR("Lua::call, invalid code, runtime error: " << code <<" > "<<lua_tostring(m_pState, -1));
			return false;
		}
	}
	else
	{
		LOG_ERROR("Lua::call, invalid code, syntax error: " << code <<" > "<<lua_tostring(m_pState, -1));
		return false;
	}
}

bool
Lua::call(const char* func, int narg, int nres /* = 0 */)
{
	if (narg>lua_gettop(m_pState))
	{
		LOG_ERROR("Lua::call, input arg count too big : "<<narg);
		return false;
	}

	lua_getglobal(m_pState, func);
	if (!lua_isfunction(m_pState, -1))
	{
		LOG_ERROR("Lua::call, invalid function name : "<<func);
		return false;
	}

	if (narg>0)
	{
		lua_insert(m_pState, -(narg+1));
	}

	if (lua_pcall_ex(m_pState, narg, nres) != 0)
	{
		LOG_ERROR("Lua::call, invalid function: " << func <<" >  "<<lua_tostring(m_pState, -1));
		return false;
	}
	return true;
}

bool
Lua::call(const char* ns, const char* func, int narg, int nres /* = 0 */)
{
	if (narg>lua_gettop(m_pState))
	{
		LOG_ERROR("Lua::call, input arg count too big : "<<narg);
		return false;
	}

	lua_getglobal(m_pState, ns);
	if (!lua_istable(m_pState,-1))
	{
		LOG_ERROR("Lua::call, null function namespace: "<<ns);
		return false;
	}

	//
	//	try to get the funtion from ns table
	lua_pushstring(m_pState, func);
	lua_gettable(m_pState, -2);	// table on -2
	if (!lua_isfunction(m_pState, -1))
	{
		LOG_ERROR("Lua::call, invalid function name : "<<func);
		return false;
	}

	//
	//	remove the ns table
	lua_remove(m_pState, -2);

	if (narg>0)
	{
		lua_insert(m_pState, -(narg+1));
	}

	if (lua_pcall_ex(m_pState, narg, nres) != 0)
	{
		LOG_ERROR("Lua::call, invalid function: " << func <<" >  "<<lua_tostring(m_pState, -1));
		return false;
	}

	return true;
}

// bool
// Lua::call(const char* func, const char* sig, ...)
// {
// 	va_list vl;
// 	int narg = 0, nres = 0;
// 
// 	lua_getglobal(m_pState, func);
// 	if (!lua_isfunction(m_pState, -1))
// 	{
// 		LOG_ERROR("Lua::call, invalid function name : "<<func);
// 		return false;
// 	}
// 
// 	va_start(vl, sig);
// 	// push arguments
// 	narg = 0;
// 	while(*sig)
// 	{
// 		switch(*sig++)
// 		{
// 		case 'f': //	double
// 			{
// 				lua_pushnumber(m_pState, va_arg(vl, double));
// 				break;
// 			}
// 		case 'd': //	integer
// 			{
// 				lua_pushinteger(m_pState, va_arg(vl, int));
// 				break;
// 			}
// 		case 's': //	string
// 			{
// 				lua_pushstring(m_pState, va_arg(vl, char*));
// 				break;
// 			}
// 		case '>':
// 		case ':':
// 			goto endwhile;
// 		default:
// 			{
// 				LOG_ERROR("Lua::call, invalid arg option: " << *(sig-1));
// 				//luaL_error(m_pState, "invalid arg option [%c]", *(sig-1));
// 			}
// 		}
// 
// 		narg ++;
// 		luaL_checkstack(m_pState, 1, "Too many arguments");
// 	}
// endwhile:
// 
// 	nres = strlen(sig);	//	number of expected results
// 
// 	if (lua_pcall_ex(m_pState, narg, nres) != 0)
// 	{
// 		LOG_ERROR("Lua::call, invalid function: " << func <<" >  "<<lua_tostring(m_pState, -1));
// 		//luaL_error(m_pState, "Failed to call function : %s > %s", func, lua_tostring(m_pState, -1));
// 	}
// 
// 	nres = -nres;
// 	while(*sig)
// 	{
// 		switch(*sig++)
// 		{
// 		case 'f': //	double
// 			{
// 				if(!lua_isnumber(m_pState, nres))
// 				{
// 					LOG_ERROR("Lua::call, invlaid result type!");
// 					//luaL_error(m_pState, "wrong result type");
// 				}
// 				*va_arg(vl, double*) = lua_tonumber(m_pState, nres);
// 				break;
// 			}
// 		case 'd': //	integer
// 			{
// 				if(!lua_isnumber(m_pState, nres))
// 				{
// 					LOG_ERROR("Lua::call, invlaid result type!");
// 					//luaL_error(m_pState, "wrong result type");
// 				}
// 				*va_arg(vl, int*) = lua_tointeger(m_pState, nres);
// 				break;
// 			}
// 		case 's': //	string
// 			{
// 				if(!lua_isstring(m_pState, nres))
// 				{
// 					LOG_ERROR("Lua::call, invlaid result type!");
// 					//luaL_error(m_pState, "wrong result type");
// 				}
// 				*va_arg(vl, const char**) = lua_tostring(m_pState, nres);
// 				break;
// 			}
// 		default:
// 			{
// 				LOG_ERROR("Lua::call, invalid arg option: " << *(sig-1));
// 			}
// 		}
// 
// 		nres++;
// 	}
// 
// 	va_end(vl);
// 
// 	return true;
// }

bool 
Lua::push(int val)
{
	lua_pushinteger(m_pState, val);
	return true;
}

bool
Lua::push(float val)
{
	lua_pushnumber(m_pState, val);
	return true;
}

bool
Lua::push(const char* val)
{
	lua_pushstring(m_pState, val);
	return true;
}

bool
Lua::push(const char* fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	char szBuff[2048];
#ifdef WIN32
	vsprintf_s(szBuff, 2048, fmt, vl);
#else
	vsnprintf(szBuff, 2048, fmt, vl);
#endif

	lua_pushstring(m_pState, szBuff);
	return true;
}

bool
Lua::push(const string& val)
{
	lua_pushstring(m_pState, val.c_str());
	return true;
}

bool
Lua::push_global(const char* val)
{
	int nTop = lua_gettop(m_pState);
	lua_getglobal(m_pState, val);
	if (nTop<lua_gettop(m_pState))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool
Lua::pop()
{
	lua_pop(m_pState, 1);
	return true;
}

bool
Lua::pop(bool& val)
{
	if (lua_isboolean(m_pState, -1))
	{
		val = (0!=lua_toboolean(m_pState, -1));
		lua_pop(m_pState, 1);
		return true;
	}
	else
	{
#ifdef _DEBUG
		//LOG_DEBUG("Lua::pop failed, expect boolean, got "<<lua_getType(m_pState, -1));
#endif
		lua_pop(m_pState, 1);
		return false;
	}
}

bool
Lua::pop(short& val)
{
	if (lua_isnumber(m_pState, -1))
	{
		val = lua_tointeger(m_pState, -1);
		lua_pop(m_pState, 1);
		return true;
	}
	else
	{
#ifdef _DEBUG
		//LOG_DEBUG("Lua::pop failed, expect integer, got "<<lua_getType(m_pState, -1));
#endif
		lua_pop(m_pState, 1);
		return false;
	}
}


bool
Lua::pop(int& val)
{
	if (lua_isnumber(m_pState, -1))
	{
		val = lua_tointeger(m_pState, -1);
		lua_pop(m_pState, 1);
		return true;
	}
	else
	{
#ifdef _DEBUG
		//LOG_DEBUG("Lua::pop failed, expect integer, got "<<lua_getType(m_pState, -1));
#endif
		lua_pop(m_pState, 1);
		return false;
	}
}

bool
Lua::pop(float& val)
{
	if (lua_isnumber(m_pState, -1))
	{
		val = (float)lua_tonumber(m_pState, -1);
		lua_pop(m_pState, 1);
		return true;
	}
	else
	{
#ifdef _DEBUG
		//LOG_DEBUG("Lua::pop failed, expect float, got "<<lua_getType(m_pState, -1));
#endif
		lua_pop(m_pState, 1);
		return false;
	}
}

bool
Lua::pop(string& val)
{
	if (lua_isstring(m_pState, -1))
	{
		val = lua_tostring(m_pState, -1);
		lua_pop(m_pState, 1);
		return true;
	}
	else
	{
#ifdef _DEBUG
		//LOG_DEBUG("Lua::pop failed, expect string, got "<<lua_getType(m_pState, -1));
#endif
		lua_pop(m_pState, 1);
		return false;
	}
}

bool
Lua::push_utf8(const string& val)
{
	const char *result = U8ToA(val.c_str());
	if (result)
	{
		lua_pushstring(m_pState, result);
	}
	else
	{
		lua_pushstring(m_pState, val.c_str());
	}
	return true;
}

bool
Lua::pop_utf8(string& val)
{
	if (lua_isstring(m_pState, -1))
	{
		const char *str = lua_tostring(m_pState, -1);
		if (str)
		{
			const char *result = AToU8(str);
			if (result)
			{
				val = result;
			}
			else
			{
				val = str;
			}
		}

		lua_pop(m_pState, 1);
		return true;
	}
	else
	{
#ifdef _DEBUG
		//LOG_DEBUG("Lua::pop failed, expect string, got "<<lua_getType(m_pState, -1));
#endif
		lua_pop(m_pState, 1);
		return false;
	}
}


const char * AToU8( const char* str )
{
	if (str==NULL)
	{
		return NULL;
	}
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32 ||CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	//AToU
	static char AnsiConvUTF8Buf[5000] = {0};
	iconv_t iconvH;
	iconvH = iconv_open("utf-8","gbk");
	if (iconvH == 0)
	{
		return NULL;
	}
	size_t strLength = strlen(str);
	size_t outLength = strLength<<2;
	size_t copyLength = outLength;
	memset(AnsiConvUTF8Buf, 0, 5000);

	char* outbuf = (char*) malloc(outLength);
	char* pBuff = outbuf;
	memset( outbuf, 0, outLength);

	if (-1 == iconv(iconvH, &str, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return NULL;
	}
	memcpy(AnsiConvUTF8Buf,pBuff,copyLength);
	free(pBuff);
	iconv_close(iconvH);
	return AnsiConvUTF8Buf;
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	static char AnsiConvUTF8Buf[5000] = {0};
	iconv_t iconvH = iconv_open("utf-8","gbk");
	if (iconvH == 0)
	{
		return NULL;
	}

	size_t strLength = strlen(str);
	size_t outLength = strLength<<2;
	size_t copyLength = outLength;
	memset(AnsiConvUTF8Buf, 0, 5000);

	char* inbuf = (char*)str;
	char* outbuf = (char*) malloc(outLength);
	char* pBuff = outbuf;
	memset( outbuf, 0, outLength);

	if (-1 == iconv (iconvH, & inbuf, & strLength, & outbuf, & outLength) )
	{
		iconv_close(iconvH);
		return NULL;
	}
	memcpy(AnsiConvUTF8Buf,pBuff,copyLength);
	free(pBuff);
	iconv_close(iconvH);
	return AnsiConvUTF8Buf;
#else
	return str;
#endif
}

const char*  U8ToA( const char* str )
{
	if (str==NULL)
	{
		return NULL;
	}
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	static char UTF8ConvAnsiBuf[5000] = {0};
	iconv_t iconvH;
	iconvH = iconv_open("gbk","utf-8");
	if (iconvH == 0)
	{
		return NULL;
	}
	size_t strLength = strlen(str);
	size_t outLength = strLength<<2;
	size_t copyLength = outLength;
	memset(UTF8ConvAnsiBuf, 0, 5000);

	char* outbuf = (char*) malloc(outLength);
	char* pBuff = outbuf;
	memset( outbuf, 0, outLength);

	if (-1 == iconv(iconvH, &str, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return NULL;
	}
	memcpy(UTF8ConvAnsiBuf,pBuff,copyLength);
	free(pBuff);
	iconv_close(iconvH);
	return UTF8ConvAnsiBuf;
#elif (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	static char UTF8ConvAnsiBuf[5000] = {0};
	iconv_t iconvH;
	iconvH = iconv_open("gbk","utf-8");
	if (iconvH == 0)
	{
		return NULL;
	}
	size_t strLength = strlen(str);
	size_t outLength = strLength<<2;
	size_t copyLength = outLength;
	memset(UTF8ConvAnsiBuf, 0, 5000);

	char* inbuf = (char*)str;
	char* outbuf = (char*) malloc(outLength);
	char* pBuff = outbuf;
	memset( outbuf, 0, outLength);

	if (-1 == iconv(iconvH, & inbuf, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return NULL;
	}
	memcpy(UTF8ConvAnsiBuf,pBuff,copyLength);
	free(pBuff);
	iconv_close(iconvH);
	return UTF8ConvAnsiBuf;
#else
	return str;
#endif
};