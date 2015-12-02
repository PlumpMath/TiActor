
#ifndef TIACTOR_ACTOR_ACTORSTATE_H
#define TIACTOR_ACTOR_ACTORSTATE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/MessageObject.h"

namespace TiActor {

class IActorState {
public:
    virtual IActorState * ClearWatching() = 0;
    virtual IActorState * ClearTerminated() = 0;
    virtual IActorState * clearBehaviorStack() = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSTATE_H */
