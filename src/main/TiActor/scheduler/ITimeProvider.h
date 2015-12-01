
#ifndef TIACTOR_SCHEDULER_ITIMEPROVIDER_H
#define TIACTOR_SCHEDULER_ITIMEPROVIDER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/basic/stddef.h"

namespace TiActor {

class ITimeProvider {
public:
    virtual uint64_t now() const = 0;
    virtual uint64_t monotonicClock() const = 0;
    virtual uint64_t highResMonotonicClock() const = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_SCHEDULER_ITIMEPROVIDER_H */
