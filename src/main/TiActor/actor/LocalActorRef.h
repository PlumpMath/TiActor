
#ifndef TIACTOR_ACTOR_LOCALACTORREF_H
#define TIACTOR_ACTOR_LOCALACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

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
    LocalActorRef() : system_(nullptr), props_(nullptr),
        dispatcher_(nullptr), path_(nullptr), cell_(nullptr) {
        //
    }

    ~LocalActorRef() { }

    ActorCell * getCell() const { return cell_; }

    virtual ICell * getUnderlying() const { return reinterpret_cast<ICell *>(cell_); }

    virtual IInternalActorRef * getChildrens() const { return nullptr; }
    virtual IInternalActorRef * getSingleChild(const std::string & name) const {
        return nullptr;
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

    virtual void tellInternal(MessageObject message, IActorRef * sender)
    {
        cell_->post(sender, message);
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_LOCALACTORREF_H */
