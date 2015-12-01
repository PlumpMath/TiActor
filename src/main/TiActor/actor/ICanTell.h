
#ifndef TIACTOR_ACTOR_ICANTELL_H
#define TIACTOR_ACTOR_ICANTELL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/MessageObject.h"

namespace TiActor {

class IActorRef;

class ICanTell {
public:
    virtual void tell(MessageObject message, const IActorRef * sender = nullptr) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ICANTELL_H */
