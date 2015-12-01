
#ifndef TIACTOR_CONFIG_STATIC_LINK_H
#define TIACTOR_CONFIG_STATIC_LINK_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(_WIN64) || defined(WIN64)
#  if defined(_DEBUG) && !defined(NDEBUG)
#    pragma comment(lib, "libTiActor-x64-Debug.lib")
#  else
#    pragma comment(lib, "libTiActor-x64-Release.lib")
#  endif
#elif defined(_WIN32) || defined(WIN32) || defined(_WINDOWS)
#  if defined(_DEBUG) && !defined(NDEBUG)
#    pragma comment(lib, "libTiActor-x86-Debug.lib")
#  else
#    pragma comment(lib, "libTiActor-x86-Release.lib")
#  endif
#else
// Linux or another OS
// Do nothing!!
#endif

#endif  /* TIACTOR_CONFIG_STATIC_LINK_H */
