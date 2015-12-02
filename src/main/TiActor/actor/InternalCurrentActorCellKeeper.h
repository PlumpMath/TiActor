
#ifndef TIACTOR_ACTOR_INTERNALCURRENTACTORCELLKEEPER_H
#define TIACTOR_ACTOR_INTERNALCURRENTACTORCELLKEEPER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/threadlocal.h"
#include "TiActor/actor/ActorCell.h"

namespace TiActor {

//class ActorCell;

class InternalCurrentActorCellKeeper {
private:
    static volatile TI_THREAD_LOCAL ActorCell * current_;

public:
    InternalCurrentActorCellKeeper() {
    }

    ~InternalCurrentActorCellKeeper() {
    }

    static volatile ActorCell * getCurrent() {
        return current_;
    }

    static void setCurrent(ActorCell * actorCell) {
        current_ = actorCell;
    }

    static IActorContext * getCurrentContext() {
        IActorContext * context = reinterpret_cast<IActorContext *>((ActorCell *)current_);
        return context;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_INTERNALCURRENTACTORCELLKEEPER_H */
