
#ifndef TIACTOR_UTILS_RUNTIME_H
#define TIACTOR_UTILS_RUNTIME_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS) || defined(WINDOWS)
#include <windows.h>
#elif defined(__MINGW32__) || defined(__CYGWIN__) || defined(__MSYS__)
#include <sys/sysinfo.h>    // For get_nprocs()
#elif defined(__linux__) || defined(LINUX) || defined(SOLARIS) || defined(AIX)
#include <sys/sysinfo.h>    // For get_nprocs()
#else
#include <unistd.h>         // For sysconf()
#endif

namespace TiActor {

namespace Runtime {

/* 
 * - _SC_NPROCESSORS_CONF
 *       The number of processors configured.
 * 
 * - _SC_NPROCESSORS_ONLN
 *       The number of processors currently online (available).
 */

static
int getAvailableProcessors() {
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS) || defined(WINDOWS)
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwNumberOfProcessors;
#elif defined(__MINGW32__) || defined(__CYGWIN__) || defined(__MSYS__)
    return get_nprocs();    // GNU fuction
#elif defined(__linux__) || defined(LINUX) || defined(SOLARIS) || defined(AIX)
    return get_nprocs();    // GNU fuction
#elif defined(__APPLE__)
    return sysconf(_SC_NPROCESSORS_ONLN);
#else
    return 0;
#endif
}

static
int getPhysicalProcessors() {
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS) || defined(WINDOWS)
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwNumberOfProcessors;
#elif defined(__MINGW32__) || defined(__CYGWIN__) || defined(__MSYS__)
    return get_nprocs_conf();    // GNU fuction
#elif defined(__linux__) || defined(LINUX) || defined(SOLARIS) || defined(AIX)
    return get_nprocs_conf();    // GNU fuction
#elif defined(__APPLE__)
    return sysconf(_SC_NPROCESSORS_CONF);
#else
    return 0;
#endif
}

}  /* namespace Runtime */

}  /* namespace TiActor */

#endif  /* TIACTOR_UTILS_RUNTIME_H */
