
#ifndef TIACTOR_ACTOR_DEFAULTPRODUCER_H
#define TIACTOR_ACTOR_DEFAULTPRODUCER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <stdexcept>
#include <typeinfo>

#include "TiActor/actor/IIndirectActorProducer.h"

namespace TiActor {

class ActorBase;

class DefaultProducer : public IIndirectActorProducer {
public:
    virtual ActorBase * produce(ActorBase * actor) {
        throw std::logic_error("No actor producer specified!");
    }

    virtual void release(ActorBase * &actor) {
        actor = nullptr;
    }

    virtual uint64_t getActorType() {
        return typeid(ActorBase).hash_code();
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_DEFAULTPRODUCER_H */
