
#ifndef TIACTOR_DISPATCH_MESSAGEQUEUEMAILBOX_H
#define TIACTOR_DISPATCH_MESSAGEQUEUEMAILBOX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/dispatch/Mailbox.h"

namespace TiActor {

class IMessageQueue;

class MessageQueueMailbox : public Mailbox {
public:
    virtual IMessageQueue * getMessageQueue() const = 0;
};


} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_MESSAGEQUEUEMAILBOX_H */
