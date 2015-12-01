
#ifndef TIACTOR_SCHEDULER_ISCHEDULER_H
#define TIACTOR_SCHEDULER_ISCHEDULER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/scheduler/ITellScheduler.h"
#include "TiActor/scheduler/ITimeProvider.h"

namespace TiActor {

class IAdvancedScheduler;

class IScheduler : public ITellScheduler, public ITimeProvider {
public:
    virtual IAdvancedScheduler * getAdvanced() const = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_SCHEDULER_ISCHEDULER_H */
