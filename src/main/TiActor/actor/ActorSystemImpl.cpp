
#include "TiActor/actor/ActorSystemImpl.h"
#include "TiActor/actor/ActorRefProvider.h"
#include "TiActor/actor/LocalActorRef.h"
#include "TiActor/dispatch/Mailboxes.h"
#include "TiActor/dispatch/Dispatchers.h"
#include "TiActor/dispatch/ThreadPoolDispatcher.h"
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
#if 1
    IActorRef * actor = nullptr;
    ActorCell * cell = getUserGuardianCell();
    if (cell) {
        actor = cell->actorOf(props, name);
    }
    return actor;
#else
    if (InternalCurrentActorCellKeeper::getCurrent() == nullptr) {
        MessageDispatcher * dispatcher = new ThreadPoolDispatcher(nullptr);
        LocalActorRef * actorRef = new LocalActorRef(this->getSystemImpl(), props, dispatcher, nullptr, nullptr);
        ActorCell * actorCell = actorRef->getCell();
        actorCell->init();
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
#endif
}

void ActorSystemImpl::start()
{
    if (provider_) {
        provider_->init(this);
    }
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
