
#ifndef TIACTOR_ACTOR_IUNTYPEDACTORCONTEXT_H
#define TIACTOR_ACTOR_IUNTYPEDACTORCONTEXT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/IActorContext.h"

namespace TiActor {

class UntypedReceive;

class IUntypedActorContext : public IActorContext {
public:
    virtual void become(UntypedReceive * receive) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_IUNTYPEDACTORCONTEXT_H */
