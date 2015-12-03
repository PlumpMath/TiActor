
#ifndef TIACTOR_ACTOR_ISYSTEMMESSAGE_H
#define TIACTOR_ACTOR_ISYSTEMMESSAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/INoSerializationVerificationNeeded.h"

#define SYSTEM_MESSAGE_START    60000

namespace TiActor {

class IActorRef;

class ISystemMessage : public INoSerializationVerificationNeeded {
public:
    struct InnerMessage {
        enum {
            Terminate = SYSTEM_MESSAGE_START
        };
    };

    virtual int getType() const = 0;
    virtual void setType(int type) = 0;
};

class SystemMessage : public ISystemMessage {
private:
    int type_;

public:
    int getType() const { return type_; }
    void setType(int type) { type_ = type; }
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

#endif  /* TIACTOR_ACTOR_ISYSTEMMESSAGE_H */
