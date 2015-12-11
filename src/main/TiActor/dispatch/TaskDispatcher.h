
#ifndef TIACTOR_DISPATCH_TASKDISPATCHER_H
#define TIACTOR_DISPATCH_TASKDISPATCHER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <stdexcept>

#include "TiActor/dispatch/MessageDispatcher.h"

namespace TiActor {

class TaskDispatcher : public MessageDispatcher {
public:
    TaskDispatcher() {
        //
    }

    virtual void schedule(action_type run) override {
        // TODO: task::run();
    }

    virtual void schedule(run_func run, void * data) override {
        // TODO: task::(*run)(data);
    }

    virtual void dispatch(ActorCell * cell, Envelope * envelope) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void systemDispatch(ActorCell * cell, Envelope * envelope) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void attach(ActorCell * cell) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void detach(ActorCell * cell) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_TASKDISPATCHER_H */
