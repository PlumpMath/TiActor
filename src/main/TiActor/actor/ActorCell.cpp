
#include "TiActor/actor/ActorCell.h"
#include "TiActor/actor/Props.h"
#include "TiActor/actor/IActorRef.h"
#include "TiActor/actor/ISystemMessage.h"
#include "TiActor/actor/Message.h"
#include "TiActor/actor/IInternalActorRef.h"
#include "TiActor/actor/ActorState.h"
#include "TiActor/actor/InternalCurrentActorCellKeeper.h"
#include "TiActor/dispatch/Mailbox.h"
#include "TiActor/dispatch/ConcurrentQueueMailbox.h"

namespace TiActor {

void ActorCell::init() {
    if (dispatcher_)
        dispatcher_->attach(this);

    mailbox_ = new ConcurrentQueueMailbox();
    if (mailbox_) {
        mailbox_->setup(dispatcher_);
        mailbox_->setActorCell(this);

        IActorRef * self = this->getSelf();
        Envelope * envelope = new Envelope();
        envelope->sender = self;
        envelope->message = reinterpret_cast<IMessage *>(new CreateSystemMessage());
        mailbox_->post(self, envelope);
    }
}

ActorBase * ActorCell::newActor()
{
    prepareForNewActor();

    ActorBase * instance = nullptr;
    useThreadContext( [&]() {
        state_ = state_->clearBehaviorStack();
        instance = createNewActorInstance();
    });
    return instance;
}

void ActorCell::start() {
    preStart();
    mailbox_->start();
}

void ActorCell::prepareForNewActor()
{
    state_ = state_->clearBehaviorStack();
    actorHasBeenCleared_ = false;
}

ActorBase * ActorCell::createNewActorInstance()
{
    ActorBase * actor = nullptr;
    if (props_)
        actor = props_->newActor();
    return actor;
}

void ActorCell::useThreadContext(action_type action)
{
    auto tmp = InternalCurrentActorCellKeeper::getCurrent();
    InternalCurrentActorCellKeeper::setCurrent(this);

    try {
        action();
    }
    catch (...) {
        //
    }

    InternalCurrentActorCellKeeper::setCurrent(tmp);
}

} // namespace TiActor
