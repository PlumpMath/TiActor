
#ifndef TIACTOR_ACTOR_ACTORREF_IPP_
#define TIACTOR_ACTOR_ACTORREF_IPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <iostream>

#include "TiActor/actor/ActorRef.h"

namespace TiActor {

// class Nobody
Nobody *	Nobody::instance_ = new Nobody();

// class ActorRefs
Nobody *    ActorRefs::nobody_ = Nobody::instance_;
IActorRef * ActorRefs::nosender_ = nullptr;

void Nobody::initNobody() {
    Nobody::instance_ = new Nobody();
}

IInternalActorRef * MinimalActorRef::getParent() const {
    return reinterpret_cast<IInternalActorRef *>(ActorRefs::getNobody());
}

void ActorRefBase::tell(MessageObject message, IActorRef * sender /* = nullptr */) {
    if (sender == nullptr) {
        sender = ActorRefs::getNoSender();
    }
	this->tellInternal(message, sender);
}

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORREF_IPP_ */
