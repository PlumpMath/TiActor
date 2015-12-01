
#ifndef TIACTOR_ACTOR_PROPS_IPP
#define TIACTOR_ACTOR_PROPS_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/Props.h"
#include "TiActor/actor/Deploy.h"
#include "TiActor/actor/Actor.h"

namespace TiActor {

//class Deploy;

bool Props::staticInited = false;
Deploy * Props::defaultDeploy = new Deploy();

Props::~Props() {
    if (deploy_ && deploy_ != defaultDeploy) {
        deploy_->destroy();
    }
    if (actor_) {
        delete actor_;
    }
}

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_PROPS_IPP */
