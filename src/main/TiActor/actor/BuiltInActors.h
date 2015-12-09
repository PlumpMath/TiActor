
#ifndef TIACTOR_ACTOR_BUILTINACTORS_H
#define TIACTOR_ACTOR_BUILTINACTORS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/ActorBase.h"
#include "TiActor/actor/MessageBase.h"
#include "TiActor/actor/SystemMessage.h"
#include "TiActor/actor/ActorSystem.h"
#include "TiActor/actor/EmptyLocalActorRef.h"

namespace TiActor {

class IMessage;
class StopChild;

class StopChild : public MessageBase<StopChild> {
public:
    IActorRef * getChild() const {
        return nullptr;
    }
};

class DeadLetter : public MessageBase<DeadLetter> {
public:
    DeadLetter(IMessage * message, IActorRef * sender, IActorRef * self) {}
    ~DeadLetter() {}
};

class EventStreamActor : public ActorBase {
protected:
    virtual bool receive(IMessage * message) override {
        return true;
    }
};

class GuardianActor : public ActorBase {
protected:
    virtual bool receive(IMessage * message) override {
        IActorContext * context = this->getContext();
        message_type msgType = message->getType();
        if (msgType == ISystemMessage::InnerMessage::Terminate) {
            if (context) {
                context->stop(this->getSelf());
            }
        }
        else if (msgType == ISystemMessage::InnerMessage::StopChild) {
            auto stopChild = reinterpret_cast<StopChild *>(message);
            if (context != nullptr && stopChild != nullptr) {
                context->stop(stopChild->getChild());
            }
        }
        else {
            if (context) {
                ActorSystem * system = context->getSystem();
                if (system) {
                    IActorRef * deadLetters = system->getDeadLetters();
                    if (deadLetters) {
                        deadLetters->tell(new DeadLetter(message, this->getSender(), this->getSelf()), this->getSender());
                    }
                }
            }
        }
        return true;
    }
};

class DeadLetterActorRef : public EmptyLocalActorRef {
    //
};

class SystemGuardianActor : public ActorBase {
private:
    IActorRef * userGuardian_;

public:
    SystemGuardianActor(IActorRef * userGuardian) : userGuardian_(userGuardian) {
    }

    ~SystemGuardianActor() {
    }

protected:
    virtual bool receive(IMessage * message) override {
        IActorContext * context = this->getContext();
        message_type msgType = message->getType();
        if (msgType == ISystemMessage::InnerMessage::Terminate) {
            if (context) {
                context->stop(this->getSelf());
            }
        }
        else if (msgType == ISystemMessage::InnerMessage::StopChild) {
            auto stopChild = reinterpret_cast<StopChild *>(message);
            if (context != nullptr && stopChild != nullptr) {
                context->stop(stopChild->getChild());
            }
        }
        else {
            if (context) {
                ActorSystem * system = context->getSystem();
                if (system) {
                    IActorRef * deadLetters = system->getDeadLetters();
                    if (deadLetters) {
                        deadLetters->tell(new DeadLetter(message, this->getSender(), this->getSelf()), this->getSender());
                    }
                }
            }
        }
        return true;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_BUILTINACTORS_H */
