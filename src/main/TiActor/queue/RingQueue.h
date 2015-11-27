
#ifndef TIACTOR_QUEUE_RINGQUEUE_H
#define TIACTOR_QUEUE_RINGQUEUE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#define NOMINMAX
#include <algorithm>

#include "TiActor/basic/stddef.h"

#include "TiActor/utils/MinMax.h"
#include "TiActor/utils/PowOf2.h"

namespace TiActor {

struct RingQueueHead
{
    volatile uint32_t head;
    char padding1[TIACTOR_CACHE_LINE_SIZE - sizeof(uint32_t)];

    volatile uint32_t tail;
    char padding2[TIACTOR_CACHE_LINE_SIZE - sizeof(uint32_t)];
};

typedef struct RingQueueHead RingQueueHead;

///////////////////////////////////////////////////////////////////
// class SmallRingQueueCore<Capacity>
///////////////////////////////////////////////////////////////////

template <typename T, uint32_t Capacity>
class SmallRingQueueCore
{
public:
    typedef uint32_t    size_type;
    typedef T *         item_type;

public:
    static const size_type  kCapacityCore   = (size_type)TIACTOR_MAX(utils::round_up_to_pow2<Capacity>::value, 2);
    static const bool       kIsAllocOnHeap  = false;

public:
    RingQueueHead       info;
    item_type           queue[kCapacityCore];
};

///////////////////////////////////////////////////////////////////
// class RingQueueCore<Capacity>
///////////////////////////////////////////////////////////////////

template <typename T, uint32_t Capacity>
class RingQueueCore
{
public:
    typedef T *         item_type;

    RingQueueCore()  {}
    ~RingQueueCore() {}

public:
    static const bool kIsAllocOnHeap = true;

public:
    RingQueueHead       info;
    item_type *         queue;
};

///////////////////////////////////////////////////////////////////
// class RingQueueBase<T, Capacity, CoreTy>
///////////////////////////////////////////////////////////////////

template <typename T, uint32_t Capacity = 16U,
    typename CoreTy = RingQueueCore<T, Capacity> >
class RingQueueBase
{
public:
    typedef uint32_t                    size_type;
    typedef uint32_t                    index_type;
    typedef T *                         value_type;
    typedef typename CoreTy::item_type  item_type;
    typedef CoreTy                      core_type;
    typedef T *                         pointer;
    typedef const T *                   const_pointer;
    typedef T &                         reference;
    typedef const T &                   const_reference;

public:
    static const size_type  kCapacity   = (size_type)TIACTOR_MAX(utils::round_up_to_pow2<Capacity>::value, 2);
    static const index_type kMask       = (index_type)(kCapacity - 1);

public:
    RingQueueBase(bool bInitHead = false) {}
    ~RingQueueBase() {}

public:
    void dump_info();
    void dump_detail();

    index_type mask() const      { return kMask;     };
    size_type capacity() const   { return kCapacity; };
    size_type length() const     { return sizes();   };
    size_type sizes() const;

    void init(bool bInitHead = false);

    int push(T * item);
    T * pop();

protected:
    core_type       core;
    //spin_mutex_t    spin_mutex;
    //pthread_mutex_t queue_mutex;
};

}  /* namespace TiActor */

#endif  /* TIACTOR_QUEUE_RINGQUEUE_H */
