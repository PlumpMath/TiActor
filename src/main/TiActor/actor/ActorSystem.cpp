
#include <stdexcept>

#include "TiActor/actor/ActorSystem.h"
#include "TiActor/actor/ActorSystemImpl.h"

#include "TiActor/actor/ActorCell.h"
#include "TiActor/actor/Deploy.h"
#include "TiActor/basic/threadlocal.h"

#include "TiActor/actor/IIndirectActorProducer.h"
#include "TiActor/actor/DefaultProducer.h"

namespace TiActor {

ActorSystem::actorsystem_map_type	ActorSystem::actorsystem_map_;
ActorSystem::actor_map_type			ActorSystem::actor_map_;

Deploy * Deploy::local_ = new Deploy();
Deploy * Deploy::none_ = new Deploy();

IIndirectActorProducer * Props::defaultProducer = new DefaultProducer();

volatile TI_THREAD_LOCAL ActorCell * InternalCurrentActorCellKeeper::current_ = nullptr;

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

IActorRef * ActorSystem::actorOf(Props * props, const std::string & name /*= ""*/)
{
    throw std::logic_error("The method or operation is not implemented.");
}

ActorSelection * ActorSystem::getActorSelection(const ActorPath * actorPath) const
{
    throw std::logic_error("The method or operation is not implemented.");
}

ActorSelection * ActorSystem::getActorSelection(const std::string & actorPath) const
{
    throw std::logic_error("The method or operation is not implemented.");
}

void ActorSystem::dispose()
{
    throw std::logic_error("The method or operation is not implemented.");
}

} // namespace TiActor
