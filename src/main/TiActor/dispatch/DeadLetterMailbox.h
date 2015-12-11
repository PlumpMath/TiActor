
#ifndef TIACTOR_DISPATCH_DEADLETTERMAILBOX_H
#define TIACTOR_DISPATCH_DEADLETTERMAILBOX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/dispatch/Mailbox.h"

namespace TiActor {

class IActorRef;

class DeadLetterMailbox : public Mailbox {
private:
    IActorRef * deadLetters_;

public:
    DeadLetterMailbox(IActorRef * deadLetters)
        : deadLetters_(deadLetters) {
    }

    ~DeadLetterMailbox() {
    }
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_DEADLETTERMAILBOX_H */
