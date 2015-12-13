
#ifndef TIACTOR_ACTOR_IINDIRECTACTORPRODUCER_H
#define TIACTOR_ACTOR_IINDIRECTACTORPRODUCER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/basic/stdint.h"

namespace TiActor {

class ActorBase;
class IActorContext;

class IIndirectActorProducer {
public:
    virtual ActorBase * produce(ActorBase * actor) = 0;
    virtual void release(ActorBase * &actor) = 0;
    virtual uint64_t getActorType() = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_IINDIRECTACTORPRODUCER_H */
