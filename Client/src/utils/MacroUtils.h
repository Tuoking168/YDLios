#ifndef __MacroUtils_h__
#define __MacroUtils_h__

#include <assert.h>
#include "CCPlatformConfig.h"

// debug code
#ifdef _DEBUG
	#define DebugCode(code) {code;}
#else
	#define DebugCode(code) 
#endif

// win32 code
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#define Win32Code(code) {code;}
#else
	#define Win32Code(code) 
#endif

// android code
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#define AndroidCode(code) {code;}
#else
	#define AndroidCode(code)
#endif

// ios code
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	#define IOSCode(code) {code;}
#else
	#define IOSCode(code)
#endif

// assert
#define CPAssert(expression) DebugCode(assert(expression))

// unused data
#define CPUnused(data)

// make static class
#define CP_MAKE_STATIC_CLASS(_class_) \
	_class_(); \
	_class_(const _class_ &); \
	_class_ &operator=(const _class_ &); \
	~_class_();

// dynamic cast return
#define CP_DYNAMIC_CAST_RETURN(_class_, _target_, _result_) \
	_result_ = dynamic_cast<_class_ *>(_target_); \
	if (!_result_) \
	{ \
		return; \
	}

// for each
#define CPForeach(_v_, _container_type_, _container_) \
	for (_container_type_::iterator _v_ = _container_.begin(); _v_ != _container_.end(); _v_++)

#endif //__MacroUtils_h__