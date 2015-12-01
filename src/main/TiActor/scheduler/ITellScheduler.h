
#ifndef TIACTOR_SCHEDULER_ITELLSCHEDULER_H
#define TIACTOR_SCHEDULER_ITELLSCHEDULER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class TimeSpan;
class ICanTell;
class MessageObject;
class IActorRef;
class ICancelable;

class ITellScheduler {
public:
    virtual void scheduleTellOnce(TimeSpan * delay, ICanTell * receiver, MessageObject message, IActorRef * sender) = 0;
    virtual void scheduleTellOnce(TimeSpan * delay, ICanTell * receiver, MessageObject message, IActorRef * sender, ICancelable * cancelable) = 0;
    virtual void scheduleTellRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, ICanTell * receiver, MessageObject message, IActorRef * sender) = 0;
    virtual void scheduleTellRepeatedly(TimeSpan * initialDelay, TimeSpan * interval, ICanTell * receiver, MessageObject message, IActorRef * sender, ICancelable * cancelable) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_SCHEDULER_ITELLSCHEDULER_H */
