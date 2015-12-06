
#ifndef TIACTOR_ACTOR_ICTIACTOR_ACTOR_EMPTYLOCALACTORREF_HELL_H
#define TIACTOR_ACTOR_EMPTYLOCALACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <stdexcept>

#include "TiActor/actor/ActorRef.h"

namespace TiActor {

class IActorRefProvider;
class ActorPath;

class EmptyLocalActorRef : public MinimalActorRef {
private:
    IActorRefProvider * provider_;
    ActorPath * path_;

public:
    EmptyLocalActorRef(IActorRefProvider * provider) : provider_(provider) {
        //
    }

    virtual IInternalActorRef * getParent() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual bool isTerminated() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual IActorRef * getChild(const std::string & name) const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual bool isLocal() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual IActorRefProvider * getProvider() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
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

    virtual void tellInternal(IMessage * message, IActorRef * sender = nullptr) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void tell(IMessage * message, IActorRef * sender = nullptr) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual ISurrogated * toSurrogate(const ActorSystem * system) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual ActorPath * getPath() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void sendSystemMessage(ISystemMessage * message, IActorRef * sender = nullptr) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_EMPTYLOCALACTORREF_H */
