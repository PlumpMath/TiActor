
#include "TiActor/actor/ActorCell.h"
#include "TiActor/actor/Props.h"
#include "TiActor/actor/IActorRef.h"
#include "TiActor/actor/SystemMessage.h"
#include "TiActor/actor/Message.h"
#include "TiActor/actor/IInternalActorRef.h"
#include "TiActor/actor/ActorState.h"
#include "TiActor/actor/InternalCurrentActorCellKeeper.h"
#include "TiActor/actor/ActorSystemImpl.h"
#include "TiActor/actor/ActorRefProvider.h"
#include "TiActor/dispatch/Mailbox.h"
#include "TiActor/dispatch/ConcurrentQueueMailbox.h"

namespace TiActor {

void ActorCell::init() {
    if (!inited_) {
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
        inited_ = true;
    }
}

ActorBase * ActorCell::newActor()
{
    prepareForNewActor();

    ActorBase * instance = nullptr;
    useThreadContext([&]() {
        state_ = state_->clearBehaviorStack();
        instance = createNewActorInstance();
    });
    return instance;
}

void ActorCell::invoke(Envelope * envelope)
{

}

void ActorCell::systemInvoke(Envelope * envelope)
{

}

IInternalActorRef * ActorCell::makeChild(Props * props, const std::string & name, bool isAsync, bool isSystemService) {
    IInternalActorRef * actorRef = nullptr;
    // TODO: makeChildActorPath(),  class ChildActorPath()
    ActorPath * childPath = nullptr;
    if (systemImpl_) {
        IActorRefProvider * provider = systemImpl_->getProvider();
        if (provider) {
            actorRef = provider->actorOf(systemImpl_, props, nullptr, childPath, isSystemService, nullptr, false, isAsync);
            if (actorRef) {
                initChild(actorRef);
                actorRef->start();
            }
        }
    }
    return actorRef;
}

void ActorCell::start() {
    preStart();
    mailbox_->start();
}

void ActorCell::post(IActorRef * sender, MessageObject message)
{
    if (mailbox_ == nullptr) return;
    auto envelope = new Envelope();
    envelope->sender = sender;
    envelope->message = (IMessage *)message;
    mailbox_->post(getSelf(), envelope);
}

void ActorCell::prepareForNewActor()
{
    state_ = state_->clearBehaviorStack();
    actorHasBeenCleared_ = false;
}

ActorBase * ActorCell::createNewActorInstance()
{
    ActorBase * actor = nullptr;
    if (props_) {
        actor = props_->newActor(actor_);
    }
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
