
#ifndef TIACTOR_ACTOR_ISYSTEMMESSAGE_H
#define TIACTOR_ACTOR_ISYSTEMMESSAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/INoSerializationVerificationNeeded.h"

namespace TiActor {

class IActorRef;

class ISystemMessage : public INoSerializationVerificationNeeded {
public:
    struct LocalMessage {
        enum {
            Terminate
        };
    };

    virtual int getType() const = 0;
    virtual void setType(int type) = 0;
};

class DeathWatchNotification : public ISystemMessage {
private:
    int type_;
    IActorRef * actor_;

private:
    void setActor(IActorRef * actor) {
        actor_ = actor;
    }

public:
    DeathWatchNotification(IActorRef * actor) {
        actor_ = actor;
    }

    int getType() const { return type_; }
    void setType(int type) { type_ = type; }

    IActorRef * getActor() const { return actor_; }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ISYSTEMMESSAGE_H */
