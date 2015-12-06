
#include "TiActor/actor/Props.h"
#include "TiActor/actor/Deploy.h"

namespace TiActor {

Deploy * Props::defaultDeploy = new Deploy();

Props::~Props() {
    if (actor_) {
        delete actor_;
    }

    if (deploy_ && deploy_ != defaultDeploy) {
        deploy_->destroy();
        delete deploy_;
    }
}

} // namespace TiActor
