
#ifndef TIACTOR_ACTOR_UNTYPEDACTOR_H
#define TIACTOR_ACTOR_UNTYPEDACTOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/ActorBase.h"

namespace TiActor {

class IActorRef;
class IMessage;

class UntypedActor : public ActorBase {
private:
    //

public:
    UntypedActor() : ActorBase() {
    }

    UntypedActor(const std::string & path) : ActorBase(path) {
    }

    ~UntypedActor() {
    }

    virtual void onReceive(IMessage * message) = 0;

protected:
    static IUntypedActorContext * getContext() {
        return static_cast<IUntypedActorContext *>(ActorBase::getContext());
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_UNTYPEDACTOR_H */
