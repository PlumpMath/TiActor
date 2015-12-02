
#ifndef TIACTOR_DISPATCH_MAILBOXES_H
#define TIACTOR_DISPATCH_MAILBOXES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class ActorSystem;
class DeadLetterMailbox;
class Mailbox;

class Mailboxes {
public:
    static const int kDefaultThroughput = 100;
    static const char kDefaultMailboxName[];

private:
    ActorSystem * system_;
    DeadLetterMailbox * deadLetterMailbox_;

public:
    Mailboxes(ActorSystem * system) : system_(system), deadLetterMailbox_(nullptr) {
        //
    }

    DeadLetterMailbox * getDeadLetterMailbox() const {
        return deadLetterMailbox_;
    }

    Mailbox * createMailbox() {
        Mailbox * mailbox = nullptr;
        return mailbox;
    }
};

const char Mailboxes::kDefaultMailboxName[] = "TiActor.actor.default-mailbox";

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_MAILBOXES_H */
