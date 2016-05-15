
#ifndef TIACTOR_QUEUE_RINGQUEUE_H
#define TIACTOR_QUEUE_RINGQUEUE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <stdlib.h>

#include <string>
#define NOMINMAX
#include <algorithm>

#include "TiActor/basic/stddef.h"

#include "TiActor/utils/MinMax.h"
#include "TiActor/utils/PowOf2.h"

#include "TiActor/queue/portable.h"
#include "TiActor/system/sleep.h"

#define MUTEX_MAX_SPIN_COUNT        1
#define SPIN_YIELD_THRESHOLD        1

namespace TiActor {

#pragma pack(push, 1)

struct spin_mutex_t
{
    char padding1[TI_CACHE_LINE_SIZE];
    volatile uint32_t locked;
    char padding2[TI_CACHE_LINE_SIZE - 1 * sizeof(uint32_t)];
    volatile uint32_t spin_counter;
    volatile uint32_t recurse_counter;
    volatile uint32_t thread_id;
    volatile uint32_t reserve;
    char padding3[TI_CACHE_LINE_SIZE - 4 * sizeof(uint32_t)];
    char padding4[TI_CACHE_LINE_SIZE];
};

typedef struct spin_mutex_t spin_mutex_t;

struct RingQueueInfo
{
    char padding1[TI_CACHE_LINE_SIZE];
    volatile uint32_t head;
    char padding2[TI_CACHE_LINE_SIZE - sizeof(uint32_t)];
    volatile uint32_t tail;
    char padding3[TI_CACHE_LINE_SIZE - sizeof(uint32_t)];
    char padding4[TI_CACHE_LINE_SIZE];
};

typedef struct RingQueueInfo RingQueueInfo;

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
    //static const size_type  kCapacityCore   = (size_type)TI_MAX(utils::round_up_to_pow2<Capacity>::value, 2);
    static const size_type  kCapacityCore   = (size_type)math::maxinum<size_type, math::round_up_to_pow2<Capacity>::value, 2>::value;
    static const bool       kIsAllocOnHeap  = false;

public:
    RingQueueInfo       info;
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
    RingQueueInfo       info;
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
    //static const size_type  kCapacity   = (size_type)TI_MAX(utils::round_up_to_pow2<Capacity>::value, 2);
    static const size_type  kCapacity   = (size_type)CompilerTime::maxinum<size_type, math::round_up_to_pow2<Capacity>::value, 2>::value;
    static const index_type kMask       = (index_type)(kCapacity - 1);

public:
    RingQueueBase(bool bInitHead = false);
    ~RingQueueBase();

public:
    void dump_info() {}
    void dump_detail() {};

    index_type mask() const      { return kMask;     };
    size_type capacity() const   { return kCapacity; };
    size_type length() const     { return sizes();   };
    size_type sizes() const;

    void init(bool bInitHead = false);

    int push(T * item);
    T * pop();

    int spin_push(T * item);
    T * spin_pop();

protected:
    core_type       core;
    spin_mutex_t    spin_mutex;
};

template <typename T, uint32_t Capacity, typename CoreTy>
RingQueueBase<T, Capacity, CoreTy>::RingQueueBase(bool bInitHead /* = false */)
{
    //printf("RingQueueBase::RingQueueBase();\n\n");
    init(bInitHead);
}

template <typename T, uint32_t Capacity, typename CoreTy>
RingQueueBase<T, Capacity, CoreTy>::~RingQueueBase()
{
    // Do nothing!
    Ti_WriteCompilerBarrier();
    spin_mutex.locked = 0;
}

template <typename T, uint32_t Capacity, typename CoreTy>
inline
void RingQueueBase<T, Capacity, CoreTy>::init(bool bInitHead /* = false */)
{
    if (!bInitHead) {
        core.info.head = 0;
        core.info.tail = 0;
    }
    else {
        memset((void *)&core.info, 0, sizeof(core.info));
    }

    Ti_CompilerBarrier();

    // Initilized spin mutex
    spin_mutex.locked = 0;
    spin_mutex.spin_counter = MUTEX_MAX_SPIN_COUNT;
    spin_mutex.recurse_counter = 0;
    spin_mutex.thread_id = 0;
    spin_mutex.reserve = 0;
}

template <typename T, uint32_t Capacity, typename CoreTy >
typename RingQueueBase<T, Capacity, CoreTy>::size_type
RingQueueBase<T, Capacity, CoreTy>::sizes() const {
    index_type head, tail;

    Ti_CompilerBarrier();
    head = core.info.head;
    tail = core.info.tail;

    return (size_type)((head - tail) <= kMask) ? (head - tail) : (size_type)(-1);
}

template <typename T, uint32_t Capacity, typename CoreTy>
inline
int RingQueueBase<T, Capacity, CoreTy>::spin_push(T * item)
{
    index_type head, tail, next;
    bool ok = false;

    Ti_CompilerBarrier();

    do {
        head = core.info.head;
        tail = core.info.tail;
        if ((head - tail) > kMask)
            return -1;
        next = head + 1;
        ok = ti_bool_compare_and_swap32(&core.info.head, head, next);
    } while (!ok);

    core.queue[head & kMask] = item;

    Ti_CompilerBarrier();

    return 0;
}

template <typename T, uint32_t Capacity, typename CoreTy>
inline
T * RingQueueBase<T, Capacity, CoreTy>::spin_pop()
{
    index_type head, tail, next;
    value_type item;
    bool ok = false;

    Ti_CompilerBarrier();

    do {
        head = core.info.head;
        tail = core.info.tail;
        if ((tail == head) || (tail > head && (head - tail) > kMask))
            return (value_type)nullptr;
        next = tail + 1;
        ok = ti_bool_compare_and_swap32(&core.info.tail, tail, next);
    } while (!ok);

    item = core.queue[tail & kMask];

    Ti_CompilerBarrier();

    return item;
}

template <typename T, uint32_t Capacity, typename CoreTy>
inline
int RingQueueBase<T, Capacity, CoreTy>::push(T * item)
{
    index_type head, tail, next;
    int32_t pause_cnt;
    uint32_t loop_count, yield_cnt, spin_count;
    static const uint32_t YIELD_THRESHOLD = SPIN_YIELD_THRESHOLD;

    Ti_CompilerBarrier();

    /* atomic_exchange usually takes less instructions than
       atomic_compare_and_exchange.  On the other hand,
       atomic_compare_and_exchange potentially generates less bus traffic
       when the lock is locked.
       We assume that the first try mostly will be successful, and we use
       atomic_exchange.  For the subsequent tries we use
       atomic_compare_and_exchange.  */
    if (ti_lock_test_and_set32(&spin_mutex.locked, 1U) != 0U) {
        loop_count = 0;
        spin_count = 1;
        do {
            if (loop_count < YIELD_THRESHOLD) {
                for (pause_cnt = spin_count; pause_cnt > 0; --pause_cnt) {
                    ti_mm_pause();
                }
                spin_count *= 2;
            }
            else {
                yield_cnt = loop_count - YIELD_THRESHOLD;
                if (false) { /* Do nothing!! */ }
#if !(defined(__MINGW32__) || defined(__CYGWIN__))
                else if ((yield_cnt & 63) == 63) {
                    ::ti_wsleep(1);
                }
#endif
                else if ((yield_cnt & 3) == 3) {
                    ::ti_wsleep(0);
                }
                else {
                    if (!::ti_yield()) {
                        ::ti_wsleep(0);
                    }
                }
            }
            loop_count++;
        } while (ti_val_compare_and_swap32(&spin_mutex.locked, 0U, 1U) != 0U);
    }

    head = core.info.head;
    tail = core.info.tail;
    if ((head - tail) > kMask) {
        Ti_CompilerBarrier();
        spin_mutex.locked = 0;
        return -1;
    }
    next = head + 1;
    core.info.head = next;

    core.queue[head & kMask] = item;

    Ti_CompilerBarrier();
    spin_mutex.locked = 0;

    return 0;
}

template <typename T, uint32_t Capacity, typename CoreTy>
inline
T * RingQueueBase<T, Capacity, CoreTy>::pop()
{
    index_type head, tail, next;
    value_type item;
    int32_t pause_cnt;
    uint32_t loop_count, yield_cnt, spin_count;
    static const uint32_t YIELD_THRESHOLD = SPIN_YIELD_THRESHOLD;

    Ti_CompilerBarrier();

    /* atomic_exchange usually takes less instructions than
       atomic_compare_and_exchange.  On the other hand,
       atomic_compare_and_exchange potentially generates less bus traffic
       when the lock is locked.
       We assume that the first try mostly will be successful, and we use
       atomic_exchange.  For the subsequent tries we use
       atomic_compare_and_exchange.  */
    if (ti_lock_test_and_set32(&spin_mutex.locked, 1U) != 0U) {
        loop_count = 0;
        spin_count = 1;
        do {
            if (loop_count < YIELD_THRESHOLD) {
                for (pause_cnt = spin_count; pause_cnt > 0; --pause_cnt) {
                    ti_mm_pause();
                }
                spin_count *= 2;
            }
            else {
                yield_cnt = loop_count - YIELD_THRESHOLD;
                if (false) { /* Do nothing!! */ }
#if !(defined(__MINGW32__) || defined(__CYGWIN__))
                else if ((yield_cnt & 63) == 63) {
                    ::ti_wsleep(1);
                }
#endif
                else if ((yield_cnt & 3) == 3) {
                    ::ti_wsleep(0);
                }
                else {
                    if (!::ti_yield()) {
                        ::ti_wsleep(0);
                    }
                }
            }
            loop_count++;
        } while (ti_val_compare_and_swap32(&spin_mutex.locked, 0U, 1U) != 0U);
    }

    head = core.info.head;
    tail = core.info.tail;
    if ((tail == head) || (tail > head && (head - tail) > kMask)) {
        Ti_CompilerBarrier();
        spin_mutex.locked = 0;
        return (value_type)nullptr;
    }
    next = tail + 1;
    core.info.tail = next;

    item = core.queue[tail & kMask];

    Ti_CompilerBarrier();
    spin_mutex.locked = 0;

    return item;
}

///////////////////////////////////////////////////////////////////
// class SmallRingQueue<T, Capacity>
///////////////////////////////////////////////////////////////////

template <typename T, uint32_t Capacity = 1024U>
class SmallRingQueue : public RingQueueBase<T, Capacity, SmallRingQueueCore<T, Capacity> >
{
public:
    typedef uint32_t        size_type;
    typedef uint32_t        index_type;
    typedef T *             value_type;
    typedef T *             pointer;
    typedef const T *       const_pointer;
    typedef T &             reference;
    typedef const T &       const_reference;

    static const size_type kCapacity = RingQueueBase<T, Capacity, SmallRingQueueCore<T, Capacity> >::kCapacity;

public:
    SmallRingQueue(bool bFillQueue = true, bool bInitHead = false);
    ~SmallRingQueue();

public:
    void dump_detail();

protected:
    void init_queue(bool bFillQueue = true);
};

template <typename T, uint32_t Capacity>
SmallRingQueue<T, Capacity>::SmallRingQueue(bool bFillQueue /* = true */,
    bool bInitHead /* = false */)
    : RingQueueBase<T, Capacity, SmallRingQueueCore<T, Capacity> >(bInitHead)
{
    init_queue(bFillQueue);
}

template <typename T, uint32_t Capacity>
SmallRingQueue<T, Capacity>::~SmallRingQueue()
{
    // Do nothing!!
}

template <typename T, uint32_t Capacity>
inline
void SmallRingQueue<T, Capacity>::init_queue(bool bFillQueue /* = true */)
{
    if (bFillQueue) {
        ::memset((void *)this->core.queue, 0, sizeof(value_type) * kCapacity);
    }
}

template <typename T, uint32_t Capacity>
void SmallRingQueue<T, Capacity>::dump_detail()
{
    printf("SmallRingQueue: (head = %u, tail = %u)\n",
        this->core.info.head, this->core.info.tail);
}

///////////////////////////////////////////////////////////////////
// class RingQueue<T, Capacity>
///////////////////////////////////////////////////////////////////

template <typename T, uint32_t Capacity = 1024U>
class RingQueue : public RingQueueBase<T, Capacity, RingQueueCore<T, Capacity> >
{
public:
    typedef uint32_t        size_type;
    typedef uint32_t        index_type;
    typedef T *             value_type;
    typedef T *             pointer;
    typedef const T *       const_pointer;
    typedef T &             reference;
    typedef const T &       const_reference;

    typedef RingQueueCore<T, Capacity>   core_type;

    static const size_type kCapacity = RingQueueBase<T, Capacity, RingQueueCore<T, Capacity> >::kCapacity;

public:
    RingQueue(bool bFillQueue = true, bool bInitHead = false);
    ~RingQueue();

public:
    void dump_detail();

protected:
    void init_queue(bool bFillQueue = true);
};

template <typename T, uint32_t Capacity>
RingQueue<T, Capacity>::RingQueue(bool bFillQueue /* = true */,
    bool bInitHead /* = false */)
    : RingQueueBase<T, Capacity, RingQueueCore<T, Capacity> >(bInitHead)
{
    init_queue(bFillQueue);
}

template <typename T, uint32_t Capacity>
RingQueue<T, Capacity>::~RingQueue()
{
    // If the queue is allocated on system heap, release them.
    if (RingQueueCore<T, Capacity>::kIsAllocOnHeap) {
        if (this->core.queue != nullptr) {
            delete[] this->core.queue;
            this->core.queue = nullptr;
        }
    }
}

template <typename T, uint32_t Capacity>
inline
void RingQueue<T, Capacity>::init_queue(bool bFillQueue /* = true */)
{
    value_type *newData = new T *[kCapacity];
    if (newData != nullptr) {
        if (bFillQueue) {
            ::memset((void *)newData, 0, sizeof(value_type) * kCapacity);
        }
        this->core.queue = newData;
    }
}

template <typename T, uint32_t Capacity>
void RingQueue<T, Capacity>::dump_detail()
{
    printf("RingQueue: (head = %u, tail = %u)\n",
        this->core.info.head, this->core.info.tail);
}

#pragma pack(pop)

} // namespace TiActor

#endif  /* TIACTOR_QUEUE_RINGQUEUE_H */
