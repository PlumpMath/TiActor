
#ifndef TIACTOR_ACTOR_ROOTGUARDIANACTORREF_H
#define TIACTOR_ACTOR_ROOTGUARDIANACTORREF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TiActor/actor/LocalActorRef.h"

namespace TiActor {

class IInternalActorRef;

class RootGuardianActorRef : public LocalActorRef {
private:
    IInternalActorRef * tempContainer_;
    IInternalActorRef * deadLetters_;

public:
    RootGuardianActorRef(ActorSystemImpl * system, Props * props, MessageDispatcher * dispatcher, Mailbox * mailbox,
        IInternalActorRef * supervisor, ActorPath * path, IInternalActorRef * deadLetters)
        : LocalActorRef(system, props, dispatcher, mailbox, supervisor, path) {
        deadLetters_ = deadLetters;
    }

    ~RootGuardianActorRef() { }

   virtual IInternalActorRef * getParent() const override {
        return reinterpret_cast<IInternalActorRef *>((RootGuardianActorRef *)this);
    }

   void setTempContainer(IInternalActorRef  * tempContainer) {
       tempContainer_ = tempContainer;
   }

   virtual IInternalActorRef * getSingleChild(const std::string & name) const override {
       if (name == "temp") {
           return tempContainer_;
       }
       else if (name == "deadLetters") {
           return deadLetters_;
       }
       else {
           return LocalActorRef::getSingleChild(name);
       }
   }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ROOTGUARDIANACTORREF_H */
