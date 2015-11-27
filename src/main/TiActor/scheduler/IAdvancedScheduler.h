
#ifndef TIACTOR_SCHEDULER_IADVANCEDSCHEDULER_H
#define TIACTOR_SCHEDULER_IADVANCEDSCHEDULER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/scheduler/IActionScheduler.h"

namespace TiActor {

class IAdvancedScheduler : public IActionScheduler {
public:
    virtual IAdvancedScheduler * getAdvanced() const = 0;
};

}  /* namespace TiActor */

#endif  /* TIACTOR_SCHEDULER_IADVANCEDSCHEDULER_H */
