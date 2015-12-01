
#ifndef TIACTOR_DISPATCH_MAILBOX_H
#define TIACTOR_DISPATCH_MAILBOX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/basic/stddef.h"
#include <string>

namespace TiActor {

class ActorPath;

struct IDisposable {
    virtual void Dispose() = 0;
};

class Mailbox : public IDisposable {
private:
    std::string name_;

public:
    Mailbox() {
        initMailbox("default");
    }

    Mailbox(const std::string & name) {
        initMailbox(name);
    }

    Mailbox(const Mailbox & src) {
        this->name_ = src.name_;
    }

private:
    void initMailbox(const std::string & name) {
        name_ = name;
    }

public:
    // Interface IDisposable
    void Dispose() { /* TODO: */ }
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_MAILBOX_H */
