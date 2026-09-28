// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "CommonType.h"

#include "log.h"

#ifdef WIN32

#include "targetver.h"

//
//	default macro is defined to make log interface easy to use
//	you can define your owner macro and your owner loggers too.
//

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <assert.h>
#endif



// TODO: reference additional headers your program requires here
