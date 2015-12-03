
#ifndef TIACTOR_ACTOR_MESSAGE_H
#define TIACTOR_ACTOR_MESSAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/MessageBase.h"

namespace TiActor {

class IActorRef;
class IMessage;

class Envelope {
public:
    IActorRef * sender;
    IMessage *  message;
};

class Message : public MessageBase<Message> {
private:
    //

public:
    Message() : MessageBase() {
        //
    }

    ~Message() { }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_MESSAGE_H */
