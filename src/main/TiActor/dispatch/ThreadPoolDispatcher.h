
#ifndef TIACTOR_DISPATCH_THREADPOOLDISPATCHER_H
#define TIACTOR_DISPATCH_THREADPOOLDISPATCHER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/dispatch/MessageDispatcher.h"

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
        //
    }

    virtual void schedule(Action * run) {
        if (isFullTrusted_) {
            //ThreadPool::UnsafeQueueUserWorkItem(wc, null);
        }
        else {
            //ThreadPool::QueueUserWorkItem(wc, null);
        }
    }
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_THREADPOOLDISPATCHER_H */
