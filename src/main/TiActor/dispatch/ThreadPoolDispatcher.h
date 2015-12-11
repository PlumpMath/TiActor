
#ifndef TIACTOR_DISPATCH_THREADPOOLDISPATCHER_H
#define TIACTOR_DISPATCH_THREADPOOLDISPATCHER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/dispatch/MessageDispatcher.h"
#include "TiActor/actor/ActorCell.h"
//#include "TiActor/actor/Action.h"

namespace TiActor {

class Mailbox;
class Action;

class ThreadPoolDispatcher : public MessageDispatcher {
private:
    static const bool isFullTrusted_ = true;

    MessageDispatcher * dispatcher_;

public:
    ThreadPoolDispatcher(MessageDispatcher * dispatcher)
        : dispatcher_(dispatcher) {
    }

    ~ThreadPoolDispatcher() {
    }

    virtual void schedule(action_type run) {
        if (isFullTrusted_) {
            //ThreadPool::UnsafeQueueUserWorkItem(wc, null);
        }
        else {
            //ThreadPool::QueueUserWorkItem(wc, null);
        }
        //run();
    }

    virtual void schedule(run_func run, void * data) {
        if (isFullTrusted_) {
            //ThreadPool::UnsafeQueueUserWorkItem(wc, null);
        }
        else {
            //ThreadPool::QueueUserWorkItem(wc, null);
        }
        static int count = 0;
        count++;
        if (count < 5)
            (*run)(data);
    };

    virtual void dispatch(ActorCell * cell, Envelope * envelope) {
        if (cell) {
            cell->invoke(envelope);
        }
    }

    virtual void systemDispatch(ActorCell * cell, Envelope * envelope) {
        if (cell) {
            cell->systemInvoke(envelope);
        }
    }

    virtual void attach(ActorCell * cell) {
        //
    }

    virtual void detach(ActorCell * cell) {
        //
    }
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_THREADPOOLDISPATCHER_H */
