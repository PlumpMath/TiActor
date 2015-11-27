
#ifndef TIACTOR_ACTOR_ACTORSYSTEM_IPP_
#define TIACTOR_ACTOR_ACTORSYSTEM_IPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/ActorSystem.h"
#include "TiActor/actor/ActorSystemImpl.h"

namespace TiActor {

class Config;

ActorSystem * ActorSystem::createAndStartSystem(const std::string & name, const Config & withFallBack) {
    ActorSystem * system = new ActorSystemImpl(name, withFallBack);
    if (system) {
        system->start();
    }
    return system;
}

}  /* namespace TiActor */

#endif  /* TIACTOR_ACTOR_ACTORSYSTEM_IPP_ */
