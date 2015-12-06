
#ifndef TIACTOR_ACTOR_LOCALACTORREF_H
#define TIACTOR_ACTOR_LOCALACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <stdexcept>

#include "TiActor/actor/ActorRef.h"

namespace TiActor {

class IInternalActorRef;
class ActorSystem;
class Props;
class ActorCell;

class LocalActorRef : public ActorRefWithCell, public ILocalRef {
private:
    ActorSystem * system_;
    Props * props_;
    MessageDispatcher * dispatcher_;
    ActorPath * path_;
    ActorCell * cell_;

public:
    LocalActorRef(ActorSystemImpl * system, Props * props, MessageDispatcher * dispatcher,
                  Mailbox * mailbox, IInternalActorRef * supervisor, ActorPath * path)
        : system_(nullptr), props_(nullptr),
          dispatcher_(nullptr), path_(nullptr), cell_(nullptr) {
        system_ = reinterpret_cast<ActorSystem *>(system);
        props_ = props;
        dispatcher_ = dispatcher;
        path_ = path;
        cell_ = createActorCell(system, props, dispatcher, supervisor);
    }

    ~LocalActorRef() { }

    ActorCell * getCell() const { return cell_; }

    virtual ICell * getUnderlying() const { return reinterpret_cast<ICell *>(cell_); }

    virtual IInternalActorRef * getChildrens() const { return nullptr; }
    virtual IInternalActorRef * getSingleChild(const std::string & name) const {
        return nullptr;
    }

private:
    ActorCell * createActorCell(ActorSystemImpl * system, Props * props,
                                MessageDispatcher * dispatcher,
                                IInternalActorRef * supervisor) {
        ActorCell * cell = new ActorCell(system, this, props, dispatcher, supervisor);
        if (cell) {
            cell->init();
        }
        return cell;
    }

protected:
    ActorSystem * getSystem() const { return system_; }
    Props * getProps() const { return props_; }
    MessageDispatcher * getDispatcher() const { return dispatcher_; }

    virtual IInternalActorRef * getParent() const { return nullptr; }
    virtual IActorRefProvider * getProvider() const { return nullptr; }

    virtual bool isTerminated() const override {
        if (cell_)
            return cell_->isTerminated();
        else
            return false;
    }

    virtual void tellInternal(IMessage * message, IActorRef * sender = nullptr) override {
        if (cell_) {
            cell_->post(sender, message);
        }
    }

    virtual void resume() override {
        if (cell_)
            cell_->resume();
    }

    virtual void start() override {
        if (cell_)
            cell_->start();
    }

    virtual void stop() override {
        if (cell_)
            cell_->stop();
    }

    virtual void restart() override {
        if (cell_)
            cell_->restart();
    }

    virtual void suspend() override {
        if (cell_)
            cell_->suspend();
    }

    virtual bool isLocal() const override {
        return true;
    }

    virtual ActorPath * getPath() const override {
        return path_;
    }

    virtual ISurrogated * toSurrogate(const ActorSystem * system) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void sendSystemMessage(ISystemMessage * message, IActorRef * sender = nullptr) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual IActorRef * getChild(const std::string & name) const { return nullptr; }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_LOCALACTORREF_H */
