
#ifndef TIACTOR_ACTOR_ACTORSYSTEM_H
#define TIACTOR_ACTOR_ACTORSYSTEM_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/stddef.h"
#include "TiActor/config/Config.h"
#include "TiActor/config/ConfigurationFactory.h"
#include "TiActor/actor/ActorRef.h"
#include "TiActor/actor/Props.h"
#include "TiActor/actor/IActorRefFactory.h"
#include "TiActor/actor/IDisposable.h"

namespace TiActor {

class ActorSystem : public IActorRefFactory, public IDisposable {
private:
    std::string name_;
    Config config_;

public:
    ActorSystem(const std::string & name) {
        initActorSystem(name, ConfigurationFactory::load());
    }

    ActorSystem(const std::string & name, const Config & withFallBack) {
        initActorSystem(name, withFallBack);
    }

private:
    void initActorSystem(const std::string & name, const Config & withFallBack) {
        name_ = name;
        config_ = withFallBack;
    }

protected:
    static ActorSystem * createAndStartSystem(const std::string & name, const Config & withFallBack);

public:
    static ActorSystem * create(const std::string & name) {
        return createAndStartSystem(name, ConfigurationFactory::load());
    }

    static ActorSystem * create(const std::string & name, const Config & config) {
        return createAndStartSystem(name, config);
    }

    static IActorRef * findActor(const Props * props, const std::string & name) {
        return nullptr;
    }

    std::string getName() const {
        return name_;
    }

    void setName(const std::string & name) {
        name_ = name;
    }

    int create() {
        return 0;
    }

    // Startup the actor systems
    int start() {
        return 0;
    }

    void shutdown() {
        //
    }
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ACTOR_ACTORSYSTEM_H */
