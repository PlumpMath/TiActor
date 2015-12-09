
#include "TiActor/actor/Props.h"
#include "TiActor/actor/Deploy.h"
#include "TiActor/actor/IActorRef.h"
#include "TiActor/actor/ActorBase.h"
#include "TiActor/actor/DefaultProducer.h"
#include "TiActor/actor/IIndirectActorProducer.h"
#include "TiActor/actor/IActorContext.h"
#include "TiActor/actor/ActivatorProducer.h"

namespace TiActor {

Deploy * Props::defaultDeploy = new Deploy();
IIndirectActorProducer * Props::defaultProducer = new DefaultProducer();

/* static */
IIndirectActorProducer * Props::createProducer() {
    return new ActivatorProducer();
}

Props::~Props() {
    if (actor_) {
        delete actor_;
    }

    if (deploy_ && deploy_ != defaultDeploy) {
        deploy_->destroy();
        delete deploy_;
    }
}

ActorBase * Props::newActor(IActorContext * context) {
    if (producer_) {
        return producer_->produce(context);
    }
    return nullptr;
}

IActorRef * Props::getActorRef() const {
    IActorRef * actorRef = nullptr;
    IActorContext * context;
    if (actor_) {
        context = actor_->getActorContext();
        if (context) {
            actorRef = context->getSelf();
        }
    }
    return actorRef;
}

IInternalActorRef * Props::getInternalActorRef() const {
    IActorRef * actorRef = getActorRef();
    return static_cast<IInternalActorRef *>(actorRef);
}

} // namespace TiActor
