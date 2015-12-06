
#ifndef TIACTOR_ACTOR_UNTYPEDACTOR_H
#define TIACTOR_ACTOR_UNTYPEDACTOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/ActorBase.h"

namespace TiActor {

class IActorRef;
class IMessage;

class UntypedActor : public ActorBase {
public:
    UntypedActor() : ActorBase() {
    }

    UntypedActor(const std::string & path) : ActorBase(path) {
    }

    ~UntypedActor() {
    }

    virtual void onReceive(IMessage * message) = 0;

protected:
    virtual bool receive(IMessage * message) override {
        onReceive(message);
        return true;
    }

    static IUntypedActorContext * getContext() {
        return static_cast<IUntypedActorContext *>(ActorBase::getContext());
    }
};

class EmptyUntypedActor : public UntypedActor {
public:
    EmptyUntypedActor() : UntypedActor() {
    }

    EmptyUntypedActor(const std::string & path) : UntypedActor(path) {
    }

    ~EmptyUntypedActor() {
    }

    virtual void onReceive(IMessage * message) override { }

protected:
    virtual bool receive(IMessage * message) override {
        onReceive(message);
        return true;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_UNTYPEDACTOR_H */
