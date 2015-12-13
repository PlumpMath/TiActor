
#ifndef TIACTOR_ACTOR_ACTORBASE_H
#define TIACTOR_ACTOR_ACTORBASE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <iostream>

#include "TiActor/basic/stddef.h"
#include "TiActor/actor/IInternalActorRef.h"
#include "TiActor/actor/IActorContext.h"
#include "TiActor/actor/IActorRef.h"
#include "TiActor/actor/InternalCurrentActorCellKeeper.h"
#include "TiActor/actor/ActorCell.h"
#include "TiActor/utils/ToString.h"

namespace TiActor {

class ActorSystem;
class IMessage;

class IInternalActor {
public:
    virtual IActorContext * getActorContext() const = 0;
};

class ActorBase : public IInternalActor {
protected:
    IActorRef * clearedSelf_;
    IActorContext * context_;
    std::string name_;

public:
    ActorBase() : clearedSelf_(nullptr), context_(nullptr) {
        initActor("default");
    }

    ActorBase(const std::string & name, ActorSystem * parent = nullptr)
     : clearedSelf_(nullptr), context_(nullptr) {
        initActor(name);
    }

    ActorBase(const ActorBase & src) {
        cloneActor(src);
    }

    ~ActorBase() {
    }

private:
    void initActor(const std::string & name) {
        name_ = name;
    }

    bool hasBeenCleared() const {
        return (clearedSelf_ != nullptr);
    }

protected:
    void cloneActor(const ActorBase & src) {
        this->name_ = src.name_;
        this->clearedSelf_ = src.clearedSelf_;
        this->context_ = src.context_;
    }

    virtual bool receive(IMessage * message) = 0;

public:
    // For IActorContext
    Props * getProps() const {
        IActorContext * context = this->getContext();
        return ((context != nullptr) ? context->getProps() : nullptr);
    }

    IActorRef * getSelf() const {
        IActorContext * context = this->getContext();
        return (hasBeenCleared() ? clearedSelf_ : ((context != nullptr) ? context->getSelf() : nullptr));
    }

    IActorRef * getSender() const   {
        IActorContext * context = this->getContext();
        return ((context != nullptr) ? context->getSender() : nullptr);
    }

    IActorRef * getParent() const   {
        IActorContext * context = this->getContext();
        return ((context != nullptr) ? context->getParent() : nullptr);
    }

    IActorRef * getChild() const    {
        IActorContext * context = this->getContext();
        return ((context != nullptr) ? context->getChild() : nullptr);
    }

    ActorSystem * getSystem() const {
        IActorContext * context = this->getContext();
        return ((context != nullptr) ? context->getSystem() : nullptr);
    }
    
    // For call IActorContext
    static IActorContext * getContext() {
        ActorCell * actorCell = (ActorCell *)InternalCurrentActorCellKeeper::getCurrent();
        if (actorCell != nullptr) {
            IActorContext * context = static_cast<IActorContext *>((IActorContext *)actorCell);
            if (context != nullptr) {
                // Normal
            }
            else {
                // Error
            }
            return (actorCell->getActorHasBeenCleared()) ? nullptr : context;
        }
        return nullptr;
        
    }
    void setContext(IActorContext * context) { context_ = context; }

    // IInternalActor
    IActorContext * getActorContext() const override {
        return this->getContext();
    }

    void clear(IActorRef * self) {
        clearedSelf_ = self;
    }

    void unclear() {
        clearedSelf_ = nullptr;
    }

    std::string getName() const {
        return name_;
    }

    void setName(const std::string & name) {
        name_ = name;
    }

    virtual void start() {
        //
    }

    void unhandleMessage(MessageObject message) {
        std::cout << ">>> Unhandle Message, ClassName: " << StringUtils::toString(*this) << "<<<" << std::endl;
        std::cout << "Message Object: " << message << "." << std::endl;
        std::cout << ">>> ------------------------------------------------------- <<<" << std::endl;
    }

    void unhandleMessage(const std::string & className, MessageObject message) {
        std::cout << ">>> unknown message. ClassName: " << className << " <<<" << std::endl;
        std::cout << "Message Object: " << message << "." << std::endl;
        std::cout << ">>> ------------------------------------------------------- <<<" << std::endl;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORBASE_H */
