
#ifndef TIACTOR_ACTOR_EXTENDEDACTORSYSTEM_H
#define TIACTOR_ACTOR_EXTENDEDACTORSYSTEM_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/ActorSystem.h"

namespace TiActor {

class IActorRefProvider;
class IInternalActorRef;
class IActorRef;
class Props;

class ExtendedActorSystem : public ActorSystem {
public:
public:
    ExtendedActorSystem(const std::string & name) : ActorSystem(name) {
    }

    ExtendedActorSystem(const std::string & name, const Config & withFallBack)
     : ActorSystem(name, withFallBack) {
    }

public:
    virtual IActorRefProvider * getProvider() const = 0;
    virtual IInternalActorRef * getGuardian() const = 0;
    virtual IInternalActorRef * getSystemGuardian() const = 0;

    virtual IActorRef * systemActorOf(Props * props, const std::string & name) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_EXTENDEDACTORSYSTEM_H */
