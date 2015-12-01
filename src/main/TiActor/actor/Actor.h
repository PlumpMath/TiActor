
#ifndef TIACTOR_ACTOR_ACTOR_H
#define TIACTOR_ACTOR_ACTOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/stddef.h"
#include "TiActor/config/Config.h"
#include "TiActor/config/ConfigurationFactory.h"

#include "TiActor/actor/IActorContext.h"
#include "TiActor/actor/ActorBase.h"

namespace TiActor {

class Actor : public ActorBase {
private:
    //

public:
    Actor() : ActorBase() {
    }

    Actor(const std::string & name, ActorSystem * parent = nullptr) : ActorBase(name, parent) {
    }

    Actor(const Actor & src) {
        cloneActor(src);
    }

    ~Actor() {
    }

private:
    void initActor(const std::string & name) {
        this->name_ = name;
    }

protected:
    void cloneActor(const Actor & src) {
        this->name_ = src.name_;
    }

public:
    int start() {
        return 0;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTOR_H */
