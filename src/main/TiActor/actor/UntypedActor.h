
#ifndef TIACTOR_ACTOR_UNTYPEDACTOR_H
#define TIACTOR_ACTOR_UNTYPEDACTOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/Actor.h"

namespace TiActor {

class IActorRef;

class UntypedActor : public Actor {
private:
    //

public:
    UntypedActor() : Actor() {
    }

    UntypedActor(const std::string & path) : Actor(path) {
    }

    ~UntypedActor() {
    }
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ACTOR_UNTYPEDACTOR_H */
