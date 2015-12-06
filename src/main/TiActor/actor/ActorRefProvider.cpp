
#include "TiActor/actor/ActorRefProvider.h"
#include "TiActor/actor/ActorSystemImpl.h"
#include "TiActor/actor/RootGuardianActorRef.h"
#include "TiActor/actor/BuiltInActors.h"
#include "TiActor/dispatch/Dispatchers.h"

namespace TiActor {

void LocalActorRefProvider::init(ActorSystemImpl * system) {
    system_ = system;
    rootGuardian_ = createRootGuardion(system);
    if (rootGuardian_) {
        userGuardian_ = createUserGuardion(rootGuardian_);
        systemGuardian_ = createSystemGuardion(rootGuardian_);
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

} // namespace TiActor
