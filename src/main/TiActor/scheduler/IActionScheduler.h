
#ifndef TIACTOR_SCHEDULER_IACTIONSCHEDULER_H
#define TIACTOR_SCHEDULER_IACTIONSCHEDULER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/Action.h"

namespace TiActor {

class TimeSpan;
class Action;
class ICancelable;

class IActionScheduler {
public:
    virtual void scheduleOnce(TimeSpan * delay, action_type action, ICancelable * cancelable) = 0;
    virtual void scheduleOnce(TimeSpan * delay, action_type action) = 0;
    virtual void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type action, ICancelable * cancelable) = 0;
    virtual void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type action) = 0;

    template <typename T>
    void scheduleOnce(TimeSpan * delay, action_type_def(T) action, ICancelable * cancelable) {};
    template <typename T>
    void scheduleOnce(TimeSpan * delay, action_type_def(T) action) {};
    template <typename T>
    void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type_def(T) action, ICancelable * cancelable) {};
    template <typename T>
    void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type_def(T) action) {};
};

} // namespace TiActor

#endif  /* TIACTOR_SCHEDULER_IACTIONSCHEDULER_H */
