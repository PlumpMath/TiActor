
#ifndef TIACTOR_ACTOR_LOCALACTORREF_H
#define TIACTOR_ACTOR_LOCALACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

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
                  IInternalActorRef * supervisor, ActorPath * path)
        : system_(nullptr), props_(nullptr),
          dispatcher_(nullptr), path_(nullptr), cell_(nullptr) {
        system_ = system;
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
        if (cell)
            cell->init();
        return cell;
    }

protected:
    ActorSystem * getSystem() const { return system_; }
    Props * getProps() const { return props_; }
    MessageDispatcher * getDispatcher() const { return dispatcher_; }

    virtual IInternalActorRef * getParent() const { return nullptr; }
    virtual IActorRefProvider * getProvider() const { return nullptr; }

    virtual bool isTerminated() const {
        if (cell_)
            return cell_->isTerminated();
        else
            return nullptr;
    }
    virtual IActorRef * getChild(const std::string & name) const { return nullptr; }

    virtual void tellInternal(MessageObject message, IActorRef * sender = nullptr)
    {
        cell_->post(sender, message);
    }

    virtual void resume() override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void start() override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void stop() override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void restart() override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void suspend() override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual bool isLocal() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual ActorPath * getPath() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void tell(MessageObject message, IActorRef * sender = nullptr) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual ISurrogated * toSurrogate(const ActorSystem * system) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void sendSystemMessage(const ISystemMessage * message, const IActorRef * sender = nullptr) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_LOCALACTORREF_H */
