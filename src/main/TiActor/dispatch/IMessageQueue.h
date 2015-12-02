
#ifndef TIACTOR_DISPATCH_IMESSAGEQUEUE_H
#define TIACTOR_DISPATCH_IMESSAGEQUEUE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class IMessageQueue {
public:
    virtual bool hasMessages() const = 0;
    virtual int  getCount() const = 0;
    virtual void enqueue() const = 0;
    virtual bool tryEnqueue() const = 0;
};


} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_IMESSAGEQUEUE_H */
