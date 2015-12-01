
#ifndef TIACTOR_SCHEDULER_IACTIONSCHEDULER_H
#define TIACTOR_SCHEDULER_IACTIONSCHEDULER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class TimeSpan;
class Action;
class ICancelable;

class IActionScheduler {
public:
    virtual void scheduleOnce(TimeSpan * delay, Action * action, ICancelable * cancelable) = 0;
    virtual void scheduleOnce(TimeSpan * delay, Action * action) = 0;
    virtual void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, Action * action, ICancelable * cancelable) = 0;
    virtual void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, Action * action) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_SCHEDULER_IACTIONSCHEDULER_H */
