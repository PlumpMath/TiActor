
#ifndef TIACTOR_ACTOR_ACTORREF_H
#define TIACTOR_ACTOR_ACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <iostream>

#include "TiActor/basic/stddef.h"
#include "TiActor/actor/ActorPath.h"
#include "TiActor/actor/IActorRef.h"
#include "TiActor/actor/IActorRefScope.h"
#include "TiActor/actor/SystemMessage.h"
#include "TiActor/actor/IInternalActorRef.h"

#include "TiActor/actor/IActorContext.h"
#include "TiActor/actor/ActorBase.h"
#include "TiActor/utils/StringUtils.h"

namespace TiActor {

class ICell;
class IActorRefProvider;

class ILocalRef : public IActorRefScope {
public:
    virtual bool isLocal() const { return true; }
};

class IRepointableRef : public IActorRefScope {
public:
    virtual bool isStarted() const = 0;
};

class ActorRefBase : public IInternalActorRef {
private:
    ActorPath * path_;

protected:
    virtual void tellInternal(IMessage * message, IActorRef * sender = nullptr) = 0;

public:
    // ICanTell
    virtual void tell(IMessage * message, IActorRef * sender = nullptr) override;

    // ISurrogated
    virtual ISurrogated * toSurrogate(const ActorSystem * system) override {
        return nullptr;
    }

    // IActorRef
    virtual ActorPath * getPath() const override {
        return path_;
    }

    const char * toString() {
        return StringUtils::format(path_->getLength() + 2, "[%s]", path_->toString());
    }
};

class InternalActorRefBase : public ActorRefBase {
private:
    IInternalActorRef * parent_;
    IActorRefProvider * provider_;

public:
    InternalActorRefBase() {}

    // IInternalActorRef
    virtual IInternalActorRef * getParent() const { return parent_; }
    virtual IActorRefProvider * getProvider() const { return provider_; }

    virtual bool isTerminated() const = 0;
    virtual IActorRef * getChild(const std::string & name) const = 0;

    virtual void resume() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void restart() = 0;
    virtual void suspend() = 0;

    void sendSystemMessage(ISystemMessage * message, IActorRef * sender = nullptr ) {
        int msgType = message->getType();
        if (msgType == ISystemMessage::InnerMessage::Terminate) {
            stop();
        }
        else if (message != nullptr) {
            this->ActorRefBase::tell(message, sender);
        }
    }

    // IActorRefScope
    virtual bool isLocal() const = 0;
};

class MinimalActorRef : public InternalActorRefBase, public ILocalRef {

protected:
    // For ICanTell
    virtual void tellInternal(IMessage * message, IActorRef * sender = nullptr) {
    }

public:
    // IInternalActorRef
    virtual IInternalActorRef * getParent() const override;

    virtual bool isTerminated() const { return false; }
    virtual IActorRef * getChild(const std::string & name) const override;

    virtual void resume() override {
    }

    virtual void start() override {
    }

    virtual void stop() override {
    }

    virtual void restart() override {
    }

    virtual void suspend() override {
    }

    // IActorRefScope
    virtual bool isLocal() const { return true; }
};

class ActorRefWithCell : public InternalActorRefBase {
public:
    virtual ICell * getUnderlying() const = 0;

    virtual IInternalActorRef * getChildrens() const = 0;
    virtual IInternalActorRef * getSingleChild(const std::string & name) const = 0;
};

class Nobody : public MinimalActorRef {
public:
    static Nobody * instance_;

private:
    ActorPath * path_;

private:
    Nobody() : path_(nullptr) {
        path_ = new RootActorPath("/Nobody");
    }

public:
    ~Nobody() { }

protected:
    virtual void tellInternal(IMessage * message, IActorRef * sender = nullptr) override {
    }

public:
    static void initNobody();

    static Nobody * getInstance() {
        return instance_;
    }

    ActorPath * getPath() const { return path_; }
    IActorRefProvider * getProvider() const { return nullptr; }

    // ICanTell
    //void tell(IMessage * message, IActorRef * sender = nullptr) override {
    //}

    // ISurrogated
    ISurrogated * toSurrogate(const ActorSystem * system) override {
        return nullptr;
    }

    virtual bool isTerminated() const override {
        return false;
    }

    virtual IActorRef * getChild(const std::string & name) const override {
        return nullptr;
    }

    virtual bool isLocal() const override {
        return true;
    }

};

class ActorRefs {
public:
    static Nobody * nobody_;
    static IActorRef * nosender_;

public:
    static void staticInit() {
        nobody_ = Nobody::getInstance();
        nosender_ = nullptr;
    }

    static void staticFree() {
        nobody_ = nullptr;
        nosender_ = nullptr;
    }

    static Nobody * getNobody() {
        return nobody_;
    }

    static IActorRef * getNoSender() {
        return nosender_;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORREF_H */
