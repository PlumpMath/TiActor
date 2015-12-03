
#ifndef TIACTOR_ACTOR_ACTORSYSTEM_IPP_
#define TIACTOR_ACTOR_ACTORSYSTEM_IPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/Actor.h"
#include "TiActor/actor/ActorSystem.h"
#include "TiActor/actor/ActorSystemImpl.h"

namespace TiActor {

class Config;

ActorSystem::actorsystem_map_type	ActorSystem::actorsystem_map_;
ActorSystem::actor_map_type			ActorSystem::actor_map_;

IActorRef * ActorSystem::findActorRef(const std::string & name) {
    IActorRef * actorRef = nullptr;
    ActorBase * actor;
    const_actor_iter actorIter = actor_map_.find(name);
    if (actorIter != actor_map_.end()) {
        actor = actorIter->second;
        if (actor) {
            actorRef = actor->getSelf();
        }
    }
    return actorRef;
}

ActorSystem * ActorSystem::createAndStartSystem(const std::string & name, const Config & withFallBack) {
    ActorSystem * system = findActorSystem(name);
    if (system == nullptr) {
        system = new ActorSystemImpl(name, withFallBack);
        if (system) {
			ActorCell * actorCell = (ActorCell *)InternalCurrentActorCellKeeper::getCurrent();
			if (actorCell == nullptr) {
				ActorCell * cellNew = new ActorCell();
				InternalCurrentActorCellKeeper::setCurrent(cellNew);
			}
			actorsystem_pair_type system_pair(name, system);
			actorsystem_map_.insert(system_pair);
            system->start();
        }
    }
    return system;
}

void ActorSystem::destroyAll() {
    // Actor HashMap
    actor_iter ait = actor_map_.begin();
    for (ait = actor_map_.begin(); ait != actor_map_.end(); ++ait) {
        ActorBase * actor = ait->second;
        actor_map_.erase(ait);
        if (actor) {
            delete actor;
        }
    }
    actor_map_.clear();

    // ActorSystem HashMap
    actorsystem_iter it = actorsystem_map_.begin();
    for (it = actorsystem_map_.begin(); it != actorsystem_map_.end(); ++it) {
        ActorSystem * system = it->second;
        actorsystem_map_.erase(it);
        if (system) {
            delete system;
        }
    }
    actorsystem_map_.clear();
}

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSYSTEM_IPP_ */
