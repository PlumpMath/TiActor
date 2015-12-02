
#ifndef TIACTOR_DISPATCH_CONCURRENTQUEUEMAILBOX_H
#define TIACTOR_DISPATCH_CONCURRENTQUEUEMAILBOX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/Message.h"
#include "TiActor/actor/ISystemMessage.h"
#include "TiActor/dispatch/Mailbox.h"
#include "TiActor/queue/RingQueue.h"
#include "TiActor/dispatch/MessageDispatcher.h"

namespace TiActor {

class IMessage;
class MessageDispatcher;

class ConcurrentQueueMailbox : public Mailbox {
private:
    typedef IMessage                    msg_type;
    typedef IMessage *                  msg_point_type;
    typedef RingQueue<msg_type, 1024>   sys_queue_type;
    typedef RingQueue<msg_type, 8192>   user_queue_type;

    sys_queue_type  systemMessages_;
    user_queue_type userMessages_;

    volatile bool isClosed_;

public:
    ConcurrentQueueMailbox()
        : systemMessages_(true, true),
          userMessages_(true, true), isClosed_(true) {
        //
    }

    ~ConcurrentQueueMailbox() { }

private:
    void run() {
        if (isClosed_)
            return;

        if (systemMessages_.sizes() > 0 || (!isSuspended && userMessages_.sizes() > 0)) {
            hasUnscheduledMessages = true;

            schedule();
        }
    }

public:
    virtual void schedule() {
        if (this->dispatcher) {
            this->dispatcher->schedule(run);
        }
    }

    virtual void post(IActorRef * receiver, IMessage * message) {
        if (isClosed_)
            return;

        hasUnscheduledMessages = true;
        message_type msgType = message->getType();
        if (msgType >= SYSTEM_MESSAGE_START) {
            // system message
            systemMessages_.push(message);
        }
        else {
            // user message
            userMessages_.push(message);
        }

        schedule();
    }

    virtual void cleanup() {
        //
    }

    virtual int getNumberOfMessages() const {
        return userMessages_.sizes();
    }
};


} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_CONCURRENTQUEUEMAILBOX_H */
