
#ifndef TIACTOR_ACTOR_ACTORCELL_H
#define TIACTOR_ACTOR_ACTORCELL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/stdint.h"
#include "TiActor/actor/IUntypedActorContext.h"
#include "TiActor/actor/ICell.h"
#include "TiActor/actor/MessageObject.h"
#include "TiActor/dispatch/MessageDispatcher.h"

namespace TiActor {

class ActorBase;
class IInternalActorRef;
class MessageDispatcher;
class Props;
class ActorPath;
class IActorRef;
class ActorSelection;
class ActorSystemImpl;
class Mailbox;
class IActorState;

class ActorCell : public IUntypedActorContext, public ICell {
private:
    IInternalActorRef * self_;
    IInternalActorRef * parent_;
    Props * props_;
    ActorBase * actor_;
    Mailbox * mailbox_;
    MessageDispatcher * dispatcher_;
    ActorSystemImpl * systemImpl_;
    IActorState * state_;
    uint64_t uid_;
    bool actorHasBeenCleared_;
    bool inited_;

public:
    ActorCell() : self_(nullptr), props_(nullptr), actor_(nullptr), mailbox_(nullptr),
        dispatcher_(nullptr), systemImpl_(nullptr), uid_(0), actorHasBeenCleared_(false), inited_(false) {
    }

    ActorCell(ActorSystemImpl * system, IInternalActorRef * self, Props * props,
        MessageDispatcher * dispatcher, IInternalActorRef * parent = nullptr)
        : self_(self), props_(props), actor_(nullptr), mailbox_(nullptr),
          dispatcher_(dispatcher), systemImpl_(system), uid_(0), actorHasBeenCleared_(false),
          inited_(false) {
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

    ActorBase * newActor();

    void setParent(IInternalActorRef * parent) {
        parent_ = parent;
    }

protected:
    void cloneActorCell(const ActorCell & src) {
        //
    }

    void prepareForNewActor();

public:
    void init();

    void useThreadContext(action_type action);
    virtual ActorBase * createNewActorInstance();

    bool getActorHasBeenCleared() const {
        return actorHasBeenCleared_;
    }

    IActorContext * getActorContext() const {
        return nullptr;
    }

    virtual bool isTerminated() const { return false; }

    // IActorCntext
    virtual Props * getProps() const { return props_; }
    virtual IActorRef * getSelf() const { return reinterpret_cast<IActorRef *>(self_); }
    virtual IActorRef * getSender() const { return nullptr; }
    virtual IActorRef * getParent() const { return reinterpret_cast<IActorRef *>(parent_); }
    virtual IActorRef * getChild() const { return nullptr; }
    virtual ActorSystem * getSystem() const { return reinterpret_cast<ActorSystem *>(systemImpl_);; }

    virtual void IActorContext::setProps(Props * props) {}
    virtual void IActorContext::setSelf(IActorRef * self) {}
    virtual void IActorContext::setSender(IActorRef * sender) {}
    virtual void IActorContext::setParent(IActorRef * parent) {}
    virtual void IActorContext::setChild(IActorRef * child) {}
    virtual void IActorContext::setSystem(ActorSystem * system) {}

    // IActorRefFactory
    virtual IActorRef * actorOf(Props * props, const std::string & name = "") { return nullptr; }
    virtual ActorSelection * getActorSelection(const ActorPath * actorPath) const { return nullptr; }
    virtual ActorSelection * getActorSelection(const std::string & actorPath) const { return nullptr; }

    // Other operations
    virtual IActorContext * create() { return nullptr; }
    virtual void stop(IActorRef * child) {}
    virtual void release() {}

    virtual void preStart() {}

    virtual void start();

    // IUntypedActorContext
    virtual void become(UntypedReceive * receive) {
        //
    };

    // ICell
    //virtual IActorRef * getSelf() const { return reinterpret_cast<IActorRef *>(self_); }
    //virtual ActorSystem * getSystem() const { return reinterpret_cast<ActorSystem *>(systemImpl_); }
    virtual ActorSystemImpl * getSystemImpl() const { return systemImpl_; }
    virtual IInternalActorRef * getInternalParent() const { return parent_; }

    IInternalActorRef * getInternelSelf() const { return self_; }

    virtual void post(IActorRef * sender, MessageObject message);
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORCELL_H */
