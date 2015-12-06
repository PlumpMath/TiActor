
#include "TiActor/actor/ActorRefProvider.h"
#include "TiActor/actor/RootGuardianActorRef.h"
#include "TiActor/actor/BuiltInActors.h"

namespace TiActor {

RootGuardianActorRef * LocalActorRefProvider::createRootGuardion(ActorSystemImpl * system)
{
    rootGuardian_ = new RootGuardianActorRef(system, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    return rootGuardian_;
}

} // namespace TiActor
