
#ifndef TIACTOR_SCHEDULER_SCHEDULERBASE_H
#define TIACTOR_SCHEDULER_SCHEDULERBASE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <stdexcept>

#include "TiActor/scheduler/IScheduler.h"
#include "TiActor/scheduler/IAdvancedScheduler.h"
#include "TiActor/actor/MessageObject.h"

namespace TiActor {

class SchedulerBase : public IScheduler, public IAdvancedScheduler {

public:
    virtual IAdvancedScheduler * getAdvanced() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleTellOnce(TimeSpan * delay, ICanTell * receiver, MessageObject message, IActorRef * sender) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleTellOnce(TimeSpan * delay, ICanTell * receiver, MessageObject message, IActorRef * sender, ICancelable * cancelable) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleTellRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, ICanTell * receiver, MessageObject message, IActorRef * sender) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleTellRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, ICanTell * receiver, MessageObject message, IActorRef * sender, ICancelable * cancelable) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual uint64_t now() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual uint64_t monotonicClock() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual uint64_t highResMonotonicClock() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleOnce(TimeSpan * delay, action_type action, ICancelable * cancelable) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleOnce(TimeSpan * delay, action_type action) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type action, ICancelable * cancelable) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type action) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    template <typename T>
    void scheduleOnce(TimeSpan * delay, action_type_def(T) action, ICancelable * cancelable) {
        throw std::logic_error("The method or operation is not implemented.");
    };

    template <typename T>
    void scheduleOnce(TimeSpan * delay, action_type_def(T) action) {
        throw std::logic_error("The method or operation is not implemented.");
    };

    template <typename T>
    void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type_def(T) action, ICancelable * cancelable) {
        throw std::logic_error("The method or operation is not implemented.");
    };

    template <typename T>
    void scheduleRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, action_type_def(T) action) {
        throw std::logic_error("The method or operation is not implemented.");
    };

};

} // namespace TiActor

#endif  /* TIACTOR_SCHEDULER_SCHEDULERBASE_H */
