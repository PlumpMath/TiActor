
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
    static TI_THREAD_LOCAL ActorCell * current_;

public:
    InternalCurrentActorCellKeeper() {
    }

    ~InternalCurrentActorCellKeeper() {
    }

    static ActorCell * getCurrent() {
        return current_;
    }

    static void setCurrent(ActorCell * actorCell) {
        current_ = actorCell;
    }

    static IActorContext * getCurrentContext() {
        IActorContext * context = static_cast<IActorContext *>(current_);
        return context;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_INTERNALCURRENTACTORCELLKEEPER_H */
