
#ifndef TIACTOR_ACTOR_MESSAGE_H
#define TIACTOR_ACTOR_MESSAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/stddef.h"
#include "TiActor/actor/MessageBase.h"

namespace TiActor {

class ActorPath;

class Message : public MessageBase {
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
