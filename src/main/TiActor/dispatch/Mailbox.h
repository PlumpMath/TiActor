
#ifndef TIACTOR_DISPATCH_MAILBOX_H
#define TIACTOR_DISPATCH_MAILBOX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/IDisposable.h"

namespace TiActor {

class IActorRef;
class IMessage;
class ActorCell;
class MessageDispatcher;

class Mailbox : public IDisposable {
public:
    enum MailboxStatus {
        Idle = 0, Busy,
    };

    enum MailboxSuspendStatus {
        NotSuspended = 0,
        Supervision,
        AwaitingTask
    };

private:
    volatile ActorCell * actorCell_;
    volatile MailboxSuspendStatus suspendStatus_;

protected:
    int status_;
    MessageDispatcher * dispatcher;
    volatile bool hasUnscheduledMessages;

private:
    std::string name_;

public:
    Mailbox() : actorCell_(nullptr), suspendStatus_(MailboxSuspendStatus::NotSuspended),
        status_(MailboxStatus::Busy), dispatcher(nullptr),
        hasUnscheduledMessages(false) {
        initMailbox("Mailbox Default");
    }

    Mailbox(const std::string & name)
        : actorCell_(nullptr), status_(MailboxStatus::Busy), dispatcher(nullptr),
          hasUnscheduledMessages(false) {
        initMailbox(name);
    }

    Mailbox(const Mailbox & src) {
        this->actorCell_ = src.actorCell_;
        this->status_ = src.status_;
        this->dispatcher = src.dispatcher;
        this->name_ = src.name_;
    }

    ~Mailbox() { }

private:
    void initMailbox(const std::string & name) {
        name_ = name;
    }

protected:
    virtual void schedule() = 0;
    virtual int getNumberOfMessages() const = 0;

    volatile ActorCell * getActorCell() const {
        return actorCell_;
    }

    void setActorCell(ActorCell * actorCell) {
        actorCell_ = actorCell;
    }

public:
    virtual void post(IActorRef * receiver, IMessage * message) = 0;

    // IDisposable
    void dispose() { }

    void setup(MessageDispatcher * dispatcher) {
        this->dispatcher = dispatcher;
    }

    void start() {
        status_ = MailboxStatus::Idle;
        schedule();
    }

    bool isSuspended() const {
        return 0;
    }

    int getStatus() const {
        return status_;
    }

    void setStatus(int status) {
        status_ = status;
    }

    bool hasMessages() const {
        return (getNumberOfMessages() > 0);
    }

    int numberOfMessages() const {
        return getNumberOfMessages();
    }    
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_MAILBOX_H */
