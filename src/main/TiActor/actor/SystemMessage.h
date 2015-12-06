
#ifndef TIACTOR_ACTOR_SYSTEMMESSAGE_H
#define TIACTOR_ACTOR_SYSTEMMESSAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/IMessage.h"
#include "TiActor/actor/INoSerializationVerificationNeeded.h"

#define SYSTEM_MESSAGE_START    60000

namespace TiActor {

class IActorRef;

class ISystemMessage : public IMessage, public INoSerializationVerificationNeeded {
public:
    struct InnerMessage {
        enum {
            SystemMessageStart = SYSTEM_MESSAGE_START,
            Terminate,
            Stop,
            Suspend,
            Resume,
            Restart,
            StopChild
        };
    };
};

class SystemMessage : public ISystemMessage {
private:
    message_type type_;
    IActorRef * sender_;
    IActorRef * receiver_;

public:
    SystemMessage() : type_(ISystemMessage::InnerMessage::SystemMessageStart),
        sender_(nullptr), receiver_(nullptr) {
    }

    SystemMessage(message_type type) : type_(type),
        sender_(nullptr), receiver_(nullptr) {
    }

    ~SystemMessage() { }

    virtual message_type getType() const override { return type_; }
    virtual void setType(message_type type) override { type_ = type; }

    virtual MessageObject getObject() const override { return (MessageObject)this; }
    virtual void setObject(MessageObject type) override { /* Do nothing! */ }

    virtual IActorRef * getSender() const override { return sender_; }
    virtual void setSender(IActorRef * sender) override { sender_ = sender; }

    virtual IActorRef * getReceiver() const override { return receiver_; }
    virtual void setReceiver(IActorRef * receiver) override { receiver_ = receiver; }
};

class DeathWatchNotification : public SystemMessage {
private:
    IActorRef * actor_;

private:
    void setActor(IActorRef * actor) {
        actor_ = actor;
    }

public:
    DeathWatchNotification(IActorRef * actor) {
        actor_ = actor;
    }

    IActorRef * getActor() const { return actor_; }
};


class CreateSystemMessage : public SystemMessage {
    //
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_SYSTEMMESSAGE_H */
