
#include <string>
#include <iostream>

#include "TiActor/actor/ActorRef.h"

namespace TiActor {

// class Nobody
Nobody *	Nobody::instance_ = new Nobody();

// class ActorRefs
Nobody *    ActorRefs::nobody_ = Nobody::instance_;
IActorRef * ActorRefs::nosender_ = nullptr;

void ActorRefBase::tell(IMessage * message, IActorRef * sender /* = nullptr */) {
    if (sender == nullptr) {
        sender = ActorRefs::getNoSender();
    }
    this->tellInternal(message, sender);
}

IInternalActorRef * MinimalActorRef::getParent() const {
    return reinterpret_cast<IInternalActorRef *>(ActorRefs::getNobody());
}

IActorRef * MinimalActorRef::getChild(const std::string & name) const {
    return (IActorRef *)ActorRefs::getNobody();
}

void Nobody::initNobody() {
    Nobody::instance_ = new Nobody();
}

} // namespace TiActor
