
#ifndef TIACTOR_DISPATCH_CONCURRENTQUEUEMAILBOX_H
#define TIACTOR_DISPATCH_CONCURRENTQUEUEMAILBOX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>

#include "TiActor/actor/Message.h"
#include "TiActor/actor/ISystemMessage.h"
#include "TiActor/dispatch/Mailbox.h"
#include "TiActor/queue/RingQueue.h"
#include "TiActor/dispatch/MessageDispatcher.h"

#include "TiActor/actor/action.h"

namespace TiActor {

class IMessage;
class MessageDispatcher;

class ConcurrentQueueMailbox : public Mailbox {
private:
    typedef IMessage                    msg_type;
    typedef IMessage *                  msg_point_type;
    typedef RingQueue<msg_type, 2048>   sys_queue_type;
    typedef RingQueue<msg_type, 32768>  user_queue_type;

    sys_queue_type  systemMessages_;
    user_queue_type userMessages_;

    volatile bool isClosed_;

public:
    ConcurrentQueueMailbox()
        : Mailbox(), systemMessages_(true, true),
          userMessages_(true, true), isClosed_(false) {
        //
    }

    ~ConcurrentQueueMailbox() { }

private:
    void run() {
        if (isClosed_)
            return;

        if (systemMessages_.sizes() > 0 || (!isSuspended() && userMessages_.sizes() > 0)) {
            hasUnscheduledMessages = true;

            schedule();
        }
    }

    static void run_s(void * data) {
        ConcurrentQueueMailbox * pThis = static_cast<ConcurrentQueueMailbox *>(data);
        if (pThis != nullptr) {
            if (pThis->isClosed_)
                return;

            if (pThis->systemMessages_.sizes() > 0 || (!pThis->isSuspended() && pThis->userMessages_.sizes() > 0)) {
                pThis->hasUnscheduledMessages = true;

                pThis->schedule();
            }
        }
    }

public:
    virtual void schedule() {
        if (this->dispatcher) {
#if 0
            this->dispatcher->schedule(&ConcurrentQueueMailbox::run_s, (void *)this);
#else
            //action_type_def2(ConcurrentQueueMailbox) _run1 = &ConcurrentQueueMailbox::run;
            action_type _run = std::bind(&ConcurrentQueueMailbox::run, this);
            if (this->dispatcher)
                this->dispatcher->schedule(_run);
#endif
        }
    }

    virtual void post(IActorRef * receiver, Envelope * envelope) {
        if (isClosed_)
            return;

        hasUnscheduledMessages = true;

        IMessage * message = envelope->message;
        message_type msgType = message->getType();
        if (msgType < SYSTEM_MESSAGE_START) {
            // user message
            userMessages_.push(message);
        }
        else {
            // system message
            systemMessages_.push(message);
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
