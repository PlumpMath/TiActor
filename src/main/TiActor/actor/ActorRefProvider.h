
#ifndef TIACTOR_ACTOR_ACTORREFPROVIDER_H
#define TIACTOR_ACTOR_ACTORREFPROVIDER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class ActorSystemImpl;
class IInternalActorRef;
class LocalActorRef;
class IActorRef;
class Props;
class ActorPath;
class Deploy;

class IActorRefProvider {
public:
    virtual void init(ActorSystemImpl * system) = 0;

    virtual IInternalActorRef * getRootGuardian() const = 0;
    virtual LocalActorRef * getGuardian() const  = 0;
    virtual LocalActorRef * getSystemGuardian() const  = 0;
    virtual IActorRef * getDeadLetters() const = 0;

    virtual IInternalActorRef * actorOf(ActorSystemImpl * system, Props * props, IInternalActorRef * supervisor,
        ActorPath * path, bool systemService, Deploy * deploy, bool lookupDeploy, bool async) = 0;
};

class LocalActorRefProvider : public IActorRefProvider {
    //
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORREFPROVIDER_H */
