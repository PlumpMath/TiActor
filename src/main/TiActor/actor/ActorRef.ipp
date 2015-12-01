
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
Nobody *	Nobody::instance_ = nullptr;

// class ActorRefs
Nobody *    ActorRefs::nobody_ = nullptr;
IActorRef * ActorRefs::nosender_ = nullptr;

void Nobody::initNobody() {
    Nobody::instance_ = new Nobody();
}

void ActorRefBase::tell(MessageObject message, const IActorRef * sender) {
    if (sender == nullptr) {
        sender = ActorRefs::getNoSender();
    }
    this->tellInternal(message, sender);
}

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORREF_IPP_ */
