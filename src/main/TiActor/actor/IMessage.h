
#ifndef TIACTOR_ACTOR_IMESSAGE_H
#define TIACTOR_ACTOR_IMESSAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/MessageObject.h"

namespace TiActor {

typedef uint32_t message_type;

enum actor_type_t {
    ACTOR_TYPE_UNKNOWN = 0,
    ACTOR_TYPE_START = 0,
    ACTOR_TYPE_PARALLEL_PI,
    ACTOR_TYPE_LAST
};

enum message_type_t {
    UnknownMessage = (message_type)(-1)
};

class IActorRef;

class IMessage {
public:
    virtual message_type getType() const = 0;
    virtual void setType(message_type type) = 0;
    virtual MessageObject getObject() const = 0;
    virtual void setObject(MessageObject type) = 0;
    virtual IActorRef * getSender() const = 0;
    virtual void setSender(IActorRef * sender) = 0;
    virtual IActorRef * getReceiver() const = 0;
    virtual void setReceiver(IActorRef * receiver) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_IMESSAGE_H */
