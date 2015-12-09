
#include "TiActor/actor/ActorRefProvider.h"
#include "TiActor/actor/ActorSystemImpl.h"
#include "TiActor/actor/RootGuardianActorRef.h"
#include "TiActor/actor/BuiltInActors.h"
#include "TiActor/dispatch/Dispatchers.h"
#include "TiActor/dispatch/Mailbox.h"
#include "TiActor/dispatch/Mailboxes.h"

#include "TiActor/actor/SupervisorStrategy.h"

namespace TiActor {

IDecider * SupervisorStrategy::DefaultDecider = nullptr;
SupervisorStrategy * SupervisorStrategy::DefaultStrategy = new OneForOneStrategy(SupervisorStrategy::DefaultDecider);
OneForOneStrategy * SupervisorStrategy::StoppingStrategy = new OneForOneStrategy(Directive::Stop);

void LocalActorRefProvider::init(ActorSystemImpl * system) {
    system_ = system;
    rootGuardian_ = createRootGuardion(system);
    if (rootGuardian_) {
        userGuardian_ = createUserGuardion(rootGuardian_, "user");
        systemGuardian_ = createSystemGuardion(rootGuardian_, "system", userGuardian_);
        rootGuardian_->start();
    }
}

MessageDispatcher * LocalActorRefProvider::getDefaultDispatcher() const {
    if (system_) {
        Dispatchers * dispathers = system_->getDispatchers();
        if (dispathers) {
            return dispathers->getDefaultGlobalDispatchers();
        }
    }
    return nullptr;
}

RootGuardianActorRef * LocalActorRefProvider::createRootGuardion(ActorSystemImpl * system)
{
    IInternalActorRef * supervisor = nullptr;
    //TODO: supervisor = new RootGuardianSupervisor(rootPath_, this, terminationPromise_, log_);
    MessageDispatcher * dispatcher = this->getDefaultDispatcher();
    Props * props = nullptr;
    // TODO: profs = Props::create<GuardianActor>(rootGuardianStrategy);
    rootGuardian_ = new RootGuardianActorRef(system, props, dispatcher, defaultMailbox_, supervisor, rootPath_, deadLetters_);
    return rootGuardian_;
}

LocalActorRef * LocalActorRefProvider::userGuardionChildCreator() {
    LocalActorRef * userGuardion = nullptr;
    ActorBase * guardianActor = new GuardianActor();
    Props * props = new Props(guardianActor, getUserGuardianSupervisorStrategy());
    if (props) {
        userGuardion = new LocalActorRef(system_, props, getDefaultDispatcher(),
            defaultMailbox_, rootGuardian_->getInternalActorRef(), nullptr);
    }
    return userGuardion;
}

LocalActorRef * LocalActorRefProvider::createUserGuardion(LocalActorRef * rootGuardian, const std::string & name) {
    LocalActorRef * child = nullptr;
    if (rootGuardian_) {
        ActorCell * cell = rootGuardian_->getCell();
        if (cell) {
            cell->reserveChild(name);
            child = userGuardionChildCreator();
            if (child) {
                cell->initChild(child);
                child->start();
            }
        }
    }
    return child;
}

LocalActorRef * LocalActorRefProvider::systemGuardionChildCreator() {
    LocalActorRef * systemGuardion = nullptr;
    ActorBase * guardianActor = new SystemGuardianActor(userGuardian_);
    Props * props = new Props(guardianActor, getUserGuardianSupervisorStrategy());
    if (props) {
        systemGuardion = new LocalActorRef(system_, props, getDefaultDispatcher(),
            defaultMailbox_, rootGuardian_->getInternalActorRef(), nullptr);
    }
    return systemGuardion;
}

LocalActorRef * LocalActorRefProvider::createSystemGuardion(LocalActorRef * rootGuardian, const std::string & name,
    LocalActorRef * userGuardian) {
    LocalActorRef * child = nullptr;
    if (rootGuardian_) {
        ActorCell * cell = rootGuardian_->getCell();
        if (cell) {
            cell->reserveChild(name);
            child = systemGuardionChildCreator();
            if (child) {
                cell->initChild(child);
                child->start();
            }
        }
    }
    return child;
}

IInternalActorRef * LocalActorRefProvider::actorOf(ActorSystemImpl * system, Props * props, IInternalActorRef * supervisor,
    ActorPath * path, bool systemService, Deploy * deploy, bool lookupDeploy, bool async) {
    IInternalActorRef * actor = nullptr;
    if (props) {
        //actor = props->getInternalActorRef();
        MessageDispatcher * dispatcher = system->getDispatchers()->lookupDispatcher(props->getDispatcherName());
        Mailbox * mailbox = system->getMailboxes()->createMailbox(props->getMailboxName());
        actor = new LocalActorRef(system, props, dispatcher, mailbox, supervisor, path);
    }
    return actor;
}

} // namespace TiActor
