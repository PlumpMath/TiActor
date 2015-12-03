
#ifndef TIACTOR_ACTOR_ACTIVATORPRODUCER_H
#define TIACTOR_ACTOR_ACTIVATORPRODUCER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <typeinfo>

#include "TiActor/actor/IIndirectActorProducer.h"
#include "TiActor/actor/Actor.h"

namespace TiActor {

class ActivatorProducer : public IIndirectActorProducer {
public:
    virtual ActorBase * produce() {
        return static_cast<ActorBase *>(new Actor());
    }

    virtual void release(ActorBase * &actor) {
        actor = nullptr;
    }

    virtual uint64_t getActorType() {
        return typeid(ActorBase).hash_code();
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTIVATORPRODUCER_H */
