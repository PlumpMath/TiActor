
#ifndef TIACTOR_DISPATCH_MESSAGEDISPATCHER_H
#define TIACTOR_DISPATCH_MESSAGEDISPATCHER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/Action.h"

namespace TiActor {

class ActorCell;
class Envelope;
class Action;

class MessageDispatcher {
public:
    static const int kDefaultThroughput = 100;

private:
    int throughput_;

protected:
    MessageDispatcher() : throughput_(kDefaultThroughput) {
    }

public:
    int getThroughput() const {
        return throughput_;
    }

    void setThroughput(int throughput) {
        throughput_ = throughput;
    }

    virtual void schedule(action_type run) = 0;

    virtual void schedule(run_func run, void * data) = 0;

    virtual void dispatch(ActorCell * cell, Envelope * envelope) = 0;
    virtual void systemDispatch(ActorCell * cell, Envelope * envelope) = 0;

    virtual void attach(ActorCell * cell) = 0;
    virtual void detach(ActorCell * cell) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_MESSAGEDISPATCHER_H */
