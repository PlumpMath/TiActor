
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
#include "TiActor/actor/IMessage.h"
#include "TiActor/actor/SystemMessage.h"
#include "TiActor/actor/IActorRef.h"
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
    ActorCell() : self_(nullptr), parent_(nullptr), props_(nullptr), actor_(nullptr), mailbox_(nullptr),
        dispatcher_(nullptr), systemImpl_(nullptr), uid_(0), actorHasBeenCleared_(false), inited_(false) {
    }

    ActorCell(ActorSystemImpl * system, IInternalActorRef * self, Props * props,
        MessageDispatcher * dispatcher, IInternalActorRef * parent = nullptr)
        : self_(self), parent_(parent), props_(props), actor_(nullptr), mailbox_(nullptr),
        dispatcher_(dispatcher), systemImpl_(system), uid_(0), actorHasBeenCleared_(false),
        inited_(false) {
    }

    ~ActorCell() {
    }

private:
    ActorBase * newActor();

    void setParent(IInternalActorRef * parent) {
        parent_ = parent;
    }

    IActorRef * actorOf(Props * props, std::string & name, bool isAsync, bool isSystemService) {
        if (name.empty()) {
            // TODO: getRandomActorName()
            name = "getRandomActorName()";
        }
        IInternalActorRef * internalActor = makeChildActor(props, name, isAsync, isSystemService);
        IActorRef * actor = reinterpret_cast<IActorRef *>(internalActor);
        return actor;
    }

    IInternalActorRef * makeChildActor(Props * props, const std::string & name, bool isAsync, bool isSystemService);

public:
    void reserveChild(const std::string & name) {
        // TODO:
    }

    void initChild(IInternalActorRef * actor) {
        // TODO:
    }

protected:
    void prepareForNewActor();

    virtual void preStart() {}

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
    virtual ActorSystem * getSystem() const { return reinterpret_cast<ActorSystem *>(systemImpl_); }

    virtual void IActorContext::setProps(Props * props) {}
    virtual void IActorContext::setSelf(IActorRef * self) {}
    virtual void IActorContext::setSender(IActorRef * sender) {}
    virtual void IActorContext::setParent(IActorRef * parent) {}
    virtual void IActorContext::setChild(IActorRef * child) {}
    virtual void IActorContext::setSystem(ActorSystem * system) {}

    // IActorRefFactory
    virtual IActorRef * actorOf(Props * props, const std::string & name = "") override {
        return actorOf(props, const_cast<std::string &>(name), false, false);
    }

    virtual ActorSelection * getActorSelection(const ActorPath * actorPath) const { return nullptr; }
    virtual ActorSelection * getActorSelection(const std::string & actorPath) const { return nullptr; }

    // Other operations
    virtual void release() {}

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

    virtual void stop(IActorRef * child) override {
        // TODO:
    }

    void resume() {
        this->sendSystemMessage(SystemMessage::InnerMessage::Resume);
    }

    void stop() {
        this->sendSystemMessage(SystemMessage::InnerMessage::Stop);
    }

    void restart() {
        this->sendSystemMessage(SystemMessage::InnerMessage::Restart);
    }

    void suspend() {
        this->sendSystemMessage(SystemMessage::InnerMessage::Suspend);
    }

private:
    void sendSystemMessage(message_type type) {
        ISystemMessage * systemMessage = new SystemMessage(type);
        if (systemMessage)
            sendSystemMessage(systemMessage);
    }

    void sendSystemMessage(ISystemMessage * systemMessage) {
        IActorRef * self = this->getSelf();
        if (self)
            self->tell(systemMessage);
    }

    void kill() {
        // TODO: throw new ActorKilledException("Kill");
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORCELL_H */
