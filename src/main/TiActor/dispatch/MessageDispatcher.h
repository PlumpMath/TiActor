
#ifndef TIACTOR_DISPATCH_MESSAGEDISPATCHER_H
#define TIACTOR_DISPATCH_MESSAGEDISPATCHER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

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
    std::string id_;

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

    std::string getId() const { return id_; }
    void setId(const std::string & id) { id_ = id; }

    virtual void schedule(action_type run) = 0;

    virtual void schedule(run_func run, void * data) = 0;

    virtual void dispatch(ActorCell * cell, Envelope * envelope);

    virtual void systemDispatch(ActorCell * cell, Envelope * envelope);

    virtual void attach(ActorCell * cell) {
        // Empty, Do Nothing!
    }

    virtual void detach(ActorCell * cell) {
        // Empty, Do Nothing!
    }
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_MESSAGEDISPATCHER_H */
