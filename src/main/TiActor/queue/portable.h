
#ifndef TIACTOR_QUEUE_PORTABLE_H
#define TIACTOR_QUEUE_PORTABLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <emmintrin.h>

#include "TiActor/basic/stddef.h"
#include "TiActor/basic/stdint.h"
#include "TiActor/basic/stdbool.h"

#if defined(_WIN64) || defined(_M_X64) || defined(_M_AMD64) || defined(_M_IA64) || defined(__amd64__) || defined(__x86_64__)
#define TI_SIZE_T_SIZEOF    8
#else
#define TI_SIZE_T_SIZEOF    4
#endif

/**
 * macro for round to power of 2
 */
#define ti_b2(x)            (      (x) | (      (x) >>  1))
#define ti_b4(x)            ( ti_b2(x) | ( ti_b2(x) >>  2))
#define ti_b8(x)            ( ti_b4(x) | ( ti_b4(x) >>  4))
#define ti_b16(x)           ( ti_b8(x) | ( ti_b8(x) >>  8))
#define ti_b32(x)           (ti_b16(x) | (ti_b16(x) >> 16))
#define ti_b64(x)           (ti_b32(x) | (ti_b32(x) >> 32))

#define ti_next_power_of_2(x)       (ti_b32((x) - 1) + 1)
#define ti_next_power_of_2_64(x)    (ti_b64((uint64_t)(x) - 1) + 1)

#if defined(TI_SIZE_T_SIZEOF) && (TI_SIZE_T_SIZEOF == 8)
#define TI_ROUND_TO_POW2(N)         ti_next_power_of_2_64(N)
#else
#define TI_ROUND_TO_POW2(N)         ti_next_power_of_2(N)
#endif

#define ti_nbits2(n)        (((n) & 2) ? 1 : 0)
#define ti_nbits4(n)        (((n) & 0x0000000CU) ? (2  +  ti_nbits2((n) >> 2)) : ( ti_nbits2(n)))
#define ti_nbits8(n)        (((n) & 0x000000F0U) ? (4  +  ti_nbits4((n) >> 4)) : ( ti_nbits4(n)))
#define ti_nbits16(n)       (((n) & 0x0000FF00U) ? (8  +  ti_nbits8((n) >> 8)) : ( ti_nbits8(n)))
#define ti_nbits32(n)       (((n) & 0xFFFF0000U) ? (16 + ti_nbits16((n) >>16)) : (ti_nbits16(n)))
#define ti_nbits_t(n)       (((n) == 0) ? 0 : (ti_nbits32(n) + 1))

#ifndef TI_POPCONUT
#define TI_POPCONUT(N)      ti_nbits_t(N)
#endif  /* TI_POPCONUT */

#define ti_popcnt1(n)       ((n) - (((n) >> 1) & 0x55555555U))
#define ti_popcnt2(n)       ((ti_popcnt1(n) & 0x33333333U) + ((ti_popcnt1(n) >> 2) & 0x33333333U))
#define ti_popcnt3(n)       ((ti_popcnt2(n) & 0x0F0F0F0FU) + ((ti_popcnt2(n) >> 4) & 0x0F0F0F0FU))
#define ti_popcnt4(n)       ((ti_popcnt3(n) & 0x0000FFFFU) +  (ti_popcnt3(n) >>16))
#define ti_popcnt5(n)       ((ti_popcnt4(n) & 0x000000FFU) +  (ti_popcnt4(n) >> 8))

#ifndef TI_POPCONUT32
#define TI_POPCONUT32(N)    ti_popcnt5(N)
#endif  /* TI_POPCONUT32 */

#ifndef ti_mm_pause
#define ti_mm_pause         _mm_pause
#endif

#if defined(_MSC_VER) || defined(__INTER_COMPILER) || defined(__ICC)

#ifndef ti_likely
#define ti_likely(x)        (x)
#endif

#ifndef ti_unlikely
#define ti_unlikely(x)      (x)
#endif

#ifndef TIC_INLINE
#define TIC_INLINE              __inline
#endif

#define ALIGN_PREFIX(N)         __declspec(align(N))
#define ALIGN_SUFFIX(N)

#define CACHE_ALIGN_PREFIX      __declspec(align(TI_CACHE_LINE_SIZE))
#define CACHE_ALIGN_SUFFIX

#if defined(__INTER_COMPILER) || defined(__ICC)

#define Ti_ReadCompilerBarrier()      __memory_barrier()
#define Ti_WriteCompilerBarrier()     __memory_barrier()
#define Ti_CompilerBarrier()          __memory_barrier()

#define Ti_ReadMemoryBarrier()        __memory_barrier()
#define Ti_WriteMemoryBarrier()       __memory_barrier()
#define Ti_MemoryBarrier()            __memory_barrier()

#define Ti_FullMemoryBarrier()        __memory_barrier()

#else

///
/// _ReadWriteBarrier
///
/// See: http://msdn.microsoft.com/en-us/library/f20w0x5e%28VS.80%29.aspx
///
/// See: http://en.wikipedia.org/wiki/Memory_ordering
///
#define Ti_ReadCompilerBarrier()      _ReadBarrier()
#define Ti_WriteCompilerBarrier()     _WriteBarrier()
#define Ti_CompilerBarrier()          _ReadWriteBarrier()

#define Ti_ReadMemoryBarrier()        MemoryBarrier()
#define Ti_WriteMemoryBarrier()       MemoryBarrier()
#define Ti_MemoryBarrier()            MemoryBarrier()

#define Ti_FullMemoryBarrier()        MemoryBarrier()

#endif  /* __INTER_COMPILER || __ICC */

#define Ti_CPU_ReadMemoryBarrier()    do { __asm { lfence } } while (0)
#define Ti_CPU_WriteMemoryBarrier()   do { __asm { sfence } } while (0)
#define Ti_CPU_MemoryBarrier()        do { __asm { mfence } } while (0)

#else  /* !_MSC_VER */

#ifndef ti_likely
#define ti_likely(x)            __builtin_expect((x), 1)
#endif

#ifndef ti_unlikely
#define ti_unlikely(x)          __builtin_expect((x), 0)
#endif

#ifndef TIC_INLINE
#define TIC_INLINE              inline
#endif

#define ALIGN_PREFIX(N)         __attribute__((__aligned__((N))))
#define ALIGN_SUFFIX(N)

#define CACHE_ALIGN_PREFIX      __attribute__((__aligned__((TI_CACHE_LINE_SIZE))))
#define CACHE_ALIGN_SUFFIX

#define PACKED_ALIGN_PREFIX(N)
#define PACKED_ALIGN_SUFFIX(N)  __attribute__((packed, aligned(N)))

///
/// See: http://en.wikipedia.org/wiki/Memory_ordering
///
/// See: http://bbs.csdn.net/topics/310025520
///

//#define Ti_CompilerBarrier()          do { asm volatile ("":::"memory"); } while (0)
#define Ti_ReadCompilerBarrier()      do { __asm__ __volatile__ ("" : : : "memory"); } while (0)
#define Ti_WriteCompilerBarrier()     do { __asm__ __volatile__ ("" : : : "memory"); } while (0)
#define Ti_CompilerBarrier()          do { __asm__ __volatile__ ("" : : : "memory"); } while (0)

#define Ti_ReadMemoryBarrier()        do { __sync_synchronize(); } while (0)
#define Ti_WriteMemoryBarrier()       do { __sync_synchronize(); } while (0)
#define Ti_MemoryBarrier()            do { __sync_synchronize(); } while (0)

#define Ti_FullMemoryBarrier()        do { __sync_synchronize(); } while (0)

#define Ti_CPU_ReadMemoryBarrier()    do { __asm__ __volatile__ ("lfence" : : : "memory"); } while (0)
#define Ti_CPU_WriteMemoryBarrier()   do { __asm__ __volatile__ ("sfence" : : : "memory"); } while (0)
#define Ti_CPU_MemoryBarrier()        do { __asm__ __volatile__ ("mfence" : : : "memory"); } while (0)

#endif  /* _MSC_VER */

#if defined(_MSC_VER) || defined(__INTER_COMPILER) || defined(__ICC)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "TiActor/basic/msvc//targetver.h"
#include <windows.h>
#include <intrin.h>

#define ti_val_compare_and_swap32(destPtr, oldValue, newValue)        \
    (int32_t)(InterlockedCompareExchange((volatile LONG *)(destPtr),    \
                            (LONG)(newValue), (LONG)(oldValue)))

#define ti_val_compare_and_swap32u(destPtr, oldValue, newValue)       \
    (uint32_t)(InterlockedCompareExchange((volatile LONG *)(destPtr),   \
                            (LONG)(newValue), (LONG)(oldValue)))

#define ti_val_compare_and_swap64(destPtr, oldValue, newValue)           \
    (int64_t)(InterlockedCompareExchange64((volatile LONG64 *)(destPtr),   \
                            (LONG64)(newValue), (LONG64)(oldValue)))

#define ti_val_compare_and_swap64u(destPtr, oldValue, newValue)          \
    (uint64_t)(InterlockedCompareExchange64((volatile LONG64 *)(destPtr),  \
                            (LONG64)(newValue), (LONG64)(oldValue)))

#define ti_bool_compare_and_swap32(destPtr, oldValue, newValue)       \
    (InterlockedCompareExchange((volatile LONG *)(destPtr),             \
                            (LONG)(newValue), (LONG)(oldValue))         \
                                == (LONG)(oldValue))

#define ti_bool_compare_and_swap64(destPtr, oldValue, newValue)       \
    (InterlockedCompareExchange64((volatile LONG64 *)(destPtr),         \
                            (LONG64)(newValue), (LONG64)(oldValue))     \
                                == (LONG64)(oldValue))

#define ti_lock_test_and_set32(destPtr, newValue)                     \
    (int32_t)(InterlockedExchange((volatile LONG *)(destPtr), (LONG)(newValue)))

#define ti_lock_test_and_set32u(destPtr, newValue)                    \
    (uint32_t)(InterlockedExchange((volatile LONG *)(destPtr), (LONG)(newValue)))

#define ti_lock_test_and_set64(destPtr, newValue)                     \
    (int64_t)(InterlockedExchange64((volatile LONGLONG *)(destPtr),     \
                                    (LONGLONG)(newValue)))

#define ti_lock_test_and_set64u(destPtr, newValue)                    \
    (uint64_t)(InterlockedExchange64((volatile LONGLONG *)(destPtr),    \
                                    (LONGLONG)(newValue)))

#define ti_fetch_and_add32(destPtr, addValue)                         \
    (uint32_t)(InterlockedExchangeAdd((volatile LONG *)(destPtr), (LONG)(addValue)))

#define ti_fetch_and_add64(destPtr, addValue)                         \
    (uint64_t)(InterlockedExchangeAdd64((volatile LONGLONG *)(destPtr), \
                                        (LONGLONG)(addValue)))

#elif defined(__GUNC__) || defined(__linux__) \
   || defined(__clang__) || defined(__APPLE__) || defined(__FreeBSD__) \
   || defined(__CYGWIN__) || defined(__MINGW32__)

#define ti_val_compare_and_swap32(destPtr, oldValue, newValue)       \
    __sync_val_compare_and_swap((volatile int32_t *)(destPtr),         \
                            (int32_t)(oldValue), (int32_t)(newValue))

#define ti_val_compare_and_swap32u(destPtr, oldValue, newValue)       \
    __sync_val_compare_and_swap((volatile uint32_t *)(destPtr),         \
                            (uint32_t)(oldValue), (uint32_t)(newValue))

#define ti_val_compare_and_swap64(destPtr, oldValue, newValue)        \
    __sync_val_compare_and_swap((volatile int64_t *)(destPtr),          \
                            (int64_t)(oldValue), (int64_t)(newValue))

#define ti_val_compare_and_swap64u(destPtr, oldValue, newValue)       \
    __sync_val_compare_and_swap((volatile uint64_t *)(destPtr),         \
                            (uint64_t)(oldValue), (uint64_t)(newValue))

#define ti_val_compare_and_swap(destPtr, oldValue, newValue)          \
    __sync_val_compare_and_swap((destPtr), (oldValue), (newValue))

#define ti_bool_compare_and_swap32(destPtr, oldValue, newValue)       \
    __sync_bool_compare_and_swap((volatile uint32_t *)(destPtr),        \
                            (uint32_t)(oldValue), (uint32_t)(newValue))

#define ti_bool_compare_and_swap64(destPtr, oldValue, newValue)       \
    __sync_bool_compare_and_swap((volatile uint64_t *)(destPtr),        \
                            (uint64_t)(oldValue), (uint64_t)(newValue))

#define ti_bool_compare_and_swap(destPtr, oldValue, newValue)         \
    __sync_bool_compare_and_swap((destPtr), (oldValue), (newValue))

#define ti_lock_test_and_set32(destPtr, newValue)                     \
    __sync_lock_test_and_set((volatile int32_t *)(destPtr),             \
                             (int32_t)(newValue))

#define ti_lock_test_and_set32u(destPtr, newValue)                    \
    __sync_lock_test_and_set((volatile uint32_t *)(destPtr),            \
                             (uint32_t)(newValue))

#define ti_lock_test_and_set64(destPtr, newValue)                     \
    __sync_lock_test_and_set((volatile int64_t *)(destPtr),             \
                             (int64_t)(newValue))

#define ti_lock_test_and_set64u(destPtr, newValue)                    \
    __sync_lock_test_and_set((volatile uint64_t *)(destPtr),            \
                             (uint64_t)(newValue))

#define ti_fetch_and_add32(destPtr, addValue)                         \
    __sync_fetch_and_add((volatile uint32_t *)(destPtr),                \
                         (uint32_t)(addValue))

#define ti_fetch_and_add64(destPtr, addValue)                         \
    __sync_fetch_and_add((volatile uint64_t *)(destPtr),                \
                         (uint64_t)(addValue))

#else

#define ti_val_compare_and_swap32(destPtr, oldValue, newValue)        \
    __internal_val_compare_and_swap32((volatile uint32_t *)(destPtr),   \
                                (uint32_t)(oldValue), (uint32_t)(newValue))

#define ti_val_compare_and_swap64(destPtr, oldValue, newValue)        \
    __internal_val_compare_and_swap64((volatile uint64_t *)(destPtr),   \
                                (uint64_t)(oldValue), (uint64_t)(newValue))

#define ti_bool_compare_and_swap32(destPtr, oldValue, newValue)       \
    __internal_bool_compare_and_swap32((volatile int32_t *)(destPtr),   \
                                (int32_t)(oldValue), (int32_t)(newValue))

#define ti_bool_compare_and_swap32u(destPtr, oldValue, newValue)      \
    __internal_bool_compare_and_swap32((volatile uint32_t *)(destPtr),  \
                                (uint32_t)(oldValue), (uint32_t)(newValue))

#define ti_bool_compare_and_swap64(destPtr, oldValue, newValue)       \
    __internal_bool_compare_and_swap64((volatile int64_t *)(destPtr),   \
                                (int64_t)(oldValue), (int64_t)(newValue))

#define ti_bool_compare_and_swap64u(destPtr, oldValue, newValue)      \
    __internal_bool_compare_and_swap64((volatile uint64_t *)(destPtr),  \
                                (uint64_t)(oldValue), (uint64_t)(newValue))

#define ti_lock_test_and_set32(destPtr, newValue)                     \
    __internal_lock_test_and_set32((volatile int32_t *)(destPtr),       \
                                (int32_t)(newValue))

#define ti_lock_test_and_set32u(destPtr, newValue)                    \
    __internal_lock_test_and_set32((volatile uint32_t *)(destPtr),      \
                                (uint32_t)(newValue))

#define ti_lock_test_and_set64(destPtr, newValue)                     \
    __internal_lock_test_and_set64((volatile int64_t *)(destPtr),       \
                                (int64_t)(newValue))

#define ti_lock_test_and_set64u(destPtr, newValue)                    \
    __internal_lock_test_and_set64u((volatile uint64_t *)(destPtr),     \
                                (uint64_t)(newValue))

#define ti_fetch_and_add32(destPtr, addValue)                         \
    __internal_fetch_and_add32((volatile uint32_t *)(destPtr),          \
                                (uint32_t)(addValue))

#define ti_fetch_and_add64(destPtr, addValue)                         \
    __internal_fetch_and_add64((volatile uint64_t *)(destPtr),          \
                                (uint64_t)(addValue))

#endif  /* defined(_MSC_VER) || defined(__INTER_COMPILER) */

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)  || defined(__ICC) \
 || defined(__MINGW32__) || defined(__CYGWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "TiActor/basic/msvc/targetver.h"
#include <windows.h>
#elif defined(__linux__) || defined(__GUNC__) \
   || defined(__clang__) || defined(__APPLE__) || defined(__FreeBSD__)
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static TIC_INLINE
int get_num_of_processors(void)
{
#if defined(_MSC_VER) || defined(__INTEL_COMPILER)  || defined(__ICC) \
 || defined(__MINGW32__) || defined(__CYGWIN__)

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwNumberOfProcessors;

#elif defined(__linux__) || defined(__GUNC__) \
   || defined(__clang__) || defined(__APPLE__) || defined(__FreeBSD__)

    int nprocs = -1;
  #ifdef _SC_NPROCESSORS_ONLN
    nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  #endif
    return nprocs;

#else
    return 1;
#endif
}

static TIC_INLINE
int32_t __internal_val_compare_and_swap32(volatile int32_t *destPtr,
                                          int32_t oldValue,
                                          int32_t newValue)
{
    int32_t origValue = *destPtr;
    Ti_CompilerBarrier();
    if (*destPtr == oldValue) {
        *destPtr = newValue;
    }
    return origValue;
}

static TIC_INLINE
uint32_t __internal_val_compare_and_swap32u(volatile uint32_t *destPtr,
                                            uint32_t oldValue,
                                            uint32_t newValue)
{
    uint32_t origValue = *destPtr;
    Ti_CompilerBarrier();
    if (*destPtr == oldValue) {
        *destPtr = newValue;
    }
    return origValue;
}

static TIC_INLINE
int64_t __internal_val_compare_and_swap64(volatile int64_t *destPtr,
                                          int64_t oldValue,
                                          int64_t newValue)
{
    int64_t origValue = *destPtr;
    Ti_CompilerBarrier();
    if (*destPtr == oldValue) {
        *destPtr = newValue;
    }
    return origValue;
}

static TIC_INLINE
uint64_t __internal_val_compare_and_swap64u(volatile uint64_t *destPtr,
                                            uint64_t oldValue,
                                            uint64_t newValue)
{
    uint64_t origValue = *destPtr;
    Ti_CompilerBarrier();
    if (*destPtr == oldValue) {
        *destPtr = newValue;
    }
    return origValue;
}

static TIC_INLINE
bool __internal_bool_compare_and_swap32(volatile uint32_t *destPtr,
                                        uint32_t oldValue,
                                        uint32_t newValue)
{
    Ti_CompilerBarrier();
    if (*destPtr == oldValue) {
        *destPtr = newValue;
        return 1;
    }
    else return 0;
}

static TIC_INLINE
bool __internal_bool_compare_and_swap64(volatile int64_t *destPtr,
                                        int64_t oldValue,
                                        int64_t newValue)
{
    Ti_CompilerBarrier();
    if (*destPtr == oldValue) {
        *destPtr = newValue;
        return 1;
    }
    else return 0;
}

static TIC_INLINE
bool __internal_bool_compare_and_swap64u(volatile uint64_t *destPtr,
                                         uint64_t oldValue,
                                         uint64_t newValue)
{
    Ti_CompilerBarrier();
    if (*destPtr == oldValue) {
        *destPtr = newValue;
        return 1;
    }
    else return 0;
}

static TIC_INLINE
int32_t __internal_lock_test_and_set32(volatile int32_t *destPtr,
                                       int32_t newValue)
{
    int32_t origValue = *destPtr;
    *destPtr = newValue;
    Ti_CompilerBarrier();
    return origValue;
}

static TIC_INLINE
uint32_t __internal_lock_test_and_set32u(volatile uint32_t *destPtr,
                                         uint32_t newValue)
{
    uint32_t origValue = *destPtr;
    *destPtr = newValue;
    Ti_CompilerBarrier();
    return origValue;
}

static TIC_INLINE
int64_t __internal_lock_test_and_set64(volatile int64_t *destPtr,
                                       int64_t newValue)
{
    int64_t origValue = *destPtr;
    *destPtr = newValue;
    Ti_CompilerBarrier();
    return origValue;
}

static TIC_INLINE
uint64_t __internal_lock_test_and_set64u(volatile uint64_t *destPtr,
                                         uint64_t newValue)
{
    uint64_t origValue = *destPtr;
    *destPtr = newValue;
    Ti_CompilerBarrier();
    return origValue;
}

static TIC_INLINE
uint32_t __internal_fetch_and_add32(volatile uint32_t *destPtr,
                                    uint32_t addValue)
{
    uint32_t origValue = *destPtr;
    *destPtr += addValue;
    Ti_CompilerBarrier();
    return origValue;
}

static TIC_INLINE
uint64_t __internal_fetch_and_add64(volatile uint64_t *destPtr,
                                    uint64_t addValue)
{
    uint64_t origValue = *destPtr;
    *destPtr += addValue;
    Ti_CompilerBarrier();
    return origValue;
}

#ifdef __cplusplus
}
#endif

#endif  /* TIACTOR_QUEUE_PORTABLE_H */
