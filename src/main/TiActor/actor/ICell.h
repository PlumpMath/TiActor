
#ifndef TIACTOR_ACTOR_ICELL_H
#define TIACTOR_ACTOR_ICELL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class IActorRef;
class ActorSystem;
class ActorSystemImpl;
class IInternalActorRef;

class ICell {
public:
    virtual IActorRef * getSelf() const = 0;
    virtual ActorSystem * getSystem() const = 0;
    virtual ActorSystemImpl * getSystemImpl() const = 0;
    virtual IInternalActorRef * getInternalParent() const = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ICELL_H */
