
#ifndef TIACTOR_ACTOR_IACTORCONTEXT_H
#define TIACTOR_ACTOR_IACTORCONTEXT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/IActorRefFactory.h"

namespace TiActor {

class Props;
class IActorRef;
class ActorSystem;
class IActorRefFactory;
class ActorSystem;

class IActorContext : public IActorRefFactory {
public:
    // IActorContext
    virtual Props * getProps() const = 0;
    virtual IActorRef * getSelf() const = 0;
    virtual IActorRef * getSender() const = 0;
    virtual IActorRef * getParent() const = 0;
    virtual IActorRef * getChild() const = 0;
    virtual ActorSystem * getSystem() const = 0;

    virtual void setProps(Props * props) = 0;
    virtual void setSelf(IActorRef * self) = 0;
    virtual void setSender(IActorRef * sender) = 0;
    virtual void setParent(IActorRef * parent) = 0;
    virtual void setChild(IActorRef * child) = 0;
    virtual void setSystem(ActorSystem * system) = 0;

    // Other operations
    virtual void stop(IActorRef * child) = 0;
    virtual void release() = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_IACTORCONTEXT_H */
