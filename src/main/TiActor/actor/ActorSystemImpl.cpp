
#include "TiActor/actor/Actor.h"
#include "TiActor/actor/ActorSystem.h"
#include "TiActor/actor/ActorSystemImpl.h"
#include "TiActor/actor/ActorRefProvider.h"
#include "TiActor/dispatch/Mailboxes.h"
#include "TiActor/dispatch/Dispatchers.h"
#include "TiActor/scheduler/SchedulerBase.h"

namespace TiActor {

ActorSystem * ActorSystemImpl::createSystemImpl(const std::string & name, const Config & config) {
	ActorSystem * system = new ActorSystemImpl(name, config);
	return system;
}

ActorSystem * ActorSystemImpl::createAndStartSystemImpl(const std::string & name, const Config & config) {
	ActorSystem * system = new ActorSystemImpl(name, config);
	if (system) {
		system->start();
	}
	return system;
}

// IActorRefFactory
IActorRef * ActorSystemImpl::actorOf(Props * props, const std::string & name) {
    if (InternalCurrentActorCellKeeper::getCurrent() == nullptr) {
        ActorCell * actorCell = new ActorCell(this->getSystemImpl(), nullptr, props, nullptr, nullptr);
        InternalCurrentActorCellKeeper::setCurrent(actorCell);
    }

    IActorRef * actorNew = ActorSystem::findActorRef(props, name);
    if (actorNew == nullptr) {
        ActorCell * actorCell = InternalCurrentActorCellKeeper::getCurrent();
        if (actorCell) {
            ActorBase * actor = actorCell->createNewActorInstance();
            ActorSystem::addActor(name, actor);
            actorNew = actor->getSelf();
            actor->start();
        }
    }
    return actorNew;
}

void ActorSystemImpl::configureSettings(const Config & config) {
    //
}

void ActorSystemImpl::configureEventStream() {
    //
}

void ActorSystemImpl::configureProvider() {
    provider_ = new LocalActorRefProvider(name_);
}

void ActorSystemImpl::configureScheduler() {
    scheduler_ = new SchedulerBase();
}

void ActorSystemImpl::configureSerialization() {
    //
}

void ActorSystemImpl::configureMailboxes() {
    mailboxes_ = new Mailboxes(this);
}

void ActorSystemImpl::configureDispatchers() {
    dispatchers_ = new Dispatchers(this);
}

void ActorSystemImpl::configureActorProducerPipeline() {
    //
}

} // namespace TiActor
