
#ifndef TIACTOR_ACTOR_IACTORREF_H
#define TIACTOR_ACTOR_IACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/ICanTell.h"
#include "TiActor/actor/ISurrogated.h"

namespace TiActor {

class ActorPath;

class IActorRef : public ICanTell, public ISurrogated {
public:
    virtual ActorPath * getPath() const = 0;
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ACTOR_IACTORREF_H */
