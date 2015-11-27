
#ifndef TIACTOR_BASIC_STDDEF_H
#define TIACTOR_BASIC_STDDEF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/basic/stdint.h"

#if defined(TIACTOR_USE_SHARED)
#define TIACTOR_API        extern "C" _declspec(dllimport)
#elif defined(TIACTOR_SHARED_DLL)
#define TIACTOR_API        extern "C" _declspec(dllexport)
#else
// TIACTOR_USE_STATIC, TIACTOR_STATIC_LIB
#define TIACTOR_API        extern "C" static
#endif

#ifndef TIACTOR_CACHE_LINE_SIZE
#define TIACTOR_CACHE_LINE_SIZE    64
#endif

#endif  /* TIACTOR_BASIC_STDDEF_H */
