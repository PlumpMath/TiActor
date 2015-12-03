
#ifndef TIACTOR_ACTOR_ROOTGUARDIANACTORREF_H
#define TIACTOR_ACTOR_ROOTGUARDIANACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/LocalActorRef.h"

namespace TiActor {

class IInternalActorRef;

class RootGuardianActorRef : public LocalActorRef {
private:
    //

public:
    RootGuardianActorRef() : LocalActorRef() {
        //
    }

    ~RootGuardianActorRef() { }

    IInternalActorRef * getParent() const {
        return reinterpret_cast<IInternalActorRef *>((RootGuardianActorRef *)this);
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ROOTGUARDIANACTORREF_H */
