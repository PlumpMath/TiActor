
#ifndef TIACTOR_ACTOR_ACTORCELL_H
#define TIACTOR_ACTOR_ACTORCELL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/IUntypedActorContext.h"
#include "TiActor/actor/ICell.h"
//#include "TiActor/actor/ActorBase.h"

namespace TiActor {

class ActorBase;
class IInternalActorRef;
class MessageDispatcher;
class Props;
class ActorPath;
class IActorRef;
class ActorSelection;

class ActorCell : public IUntypedActorContext, public ICell {
private:
    IInternalActorRef * self_;
    ActorBase * actor_;
    bool actorHasBeenCleared_;

public:
    ActorCell() : self_(nullptr), actor_(nullptr), actorHasBeenCleared_(false) {
    }

    ActorCell(ActorSystemImpl * system, IInternalActorRef * self, Props * props,
        MessageDispatcher * dispatcher, IInternalActorRef * parent = nullptr)
        : self_(nullptr), actor_(nullptr), actorHasBeenCleared_(false) {
    }

    ActorCell(const ActorCell & src) {
        cloneActorCell(src);
    }

    ~ActorCell() {
    }

private:
    void initActorCell(const std::string & name) {
        //
    }

protected:
    void cloneActorCell(const ActorCell & src) {
        //
    }

public:
    bool getActorHasBeenCleared() const {
        return actorHasBeenCleared_;
    }

    IActorContext * getActorContext() const {
        return nullptr;
    }

    // IActorCntext
    virtual Props * getProps() const { return nullptr; }
    virtual IActorRef * getSelf() const { return reinterpret_cast<IActorRef *>(self_); }
    virtual IActorRef * getSender() const { return nullptr; }
    virtual IActorRef * getParent() const { return nullptr; }
    virtual IActorRef * getChild() const { return nullptr; }
    virtual ActorSystem * getSystem() const { return nullptr; }

    virtual void setProps(Props * props) {}
    virtual void setSelf(IActorRef * self) {}
    virtual void setSender(IActorRef * sender) {}
    virtual void setParent(IActorRef * parent) {}
    virtual void setChild(IActorRef * child) {}
    virtual void setSystem(ActorSystem * system) {}

    // IActorRefFactory
    virtual IActorRef * actorOf(const Props * props, const std::string & name = "") { return nullptr; }
    virtual ActorSelection * getActorSelection(const ActorPath * actorPath) const { return nullptr; }
    virtual ActorSelection * getActorSelection(const std::string & actorPath) const { return nullptr; }

    // Other operations
    virtual IActorContext * create() { return nullptr; }
    virtual void stop(IActorRef * child) {}
    virtual void release() {}

    // IUntypedActorContext
    virtual void become(UntypedReceive * receive) {
        //
    };

    // ICell
    virtual IActorRef * getSelf2() const { return nullptr; }
    virtual ActorSystem * getSystem2() const { return nullptr; }
    virtual ActorSystemImpl * getSystemImpl() const { return nullptr; }
    virtual IInternalActorRef * getParent2() const { return self_; }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORCELL_H */
