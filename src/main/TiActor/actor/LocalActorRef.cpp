
#include <stdexcept>

#include "TiActor/actor/LocalActorRef.h"

#include "TiActor/actor/ActorCell.h"
#include "TiActor/actor/ActorSystemImpl.h"

namespace TiActor {

IActorRefProvider * LocalActorRef::getProvider() const {
    if (cell_) {
        ActorSystemImpl * systemImpl = cell_->getSystemImpl();
        if (systemImpl)
            return systemImpl->getProvider();
    }
    return nullptr;
}

} // namespace TiActor
