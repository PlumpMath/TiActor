
#ifndef TIACTOR_ACTOR_ACTORSYSTEM_H
#define TIACTOR_ACTOR_ACTORSYSTEM_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <unordered_map>

#include "TiActor/basic/stddef.h"
#include "TiActor/config/Config.h"
#include "TiActor/config/ConfigurationFactory.h"
#include "TiActor/actor/ActorRef.h"
#include "TiActor/actor/Props.h"
#include "TiActor/actor/IActorRefFactory.h"
#include "TiActor/actor/IDisposable.h"

namespace TiActor {

class ActorSystem : public IActorRefFactory, public IDisposable {
public:
    typedef std::unordered_map<std::string, ActorSystem *>                    actorsystem_map_type;
    typedef std::unordered_map<std::string, ActorSystem *>::iterator          actorsystem_iter;
    typedef std::unordered_map<std::string, ActorSystem *>::const_iterator    const_actorsystem_iter;

    typedef std::unordered_map<std::string, Actor *>                    actor_map_type;
    typedef std::unordered_map<std::string, Actor *>::iterator          actor_iter;
    typedef std::unordered_map<std::string, Actor *>::const_iterator    const_actor_iter;

private:
    std::string name_;
    Config config_;

public:
    static actorsystem_map_type actorsystem_map_;
    static actor_map_type       actor_map_;

public:
    ActorSystem(const std::string & name) {
        initActorSystem(name, ConfigurationFactory::load());
    }

    ActorSystem(const std::string & name, const Config & withFallBack) {
        initActorSystem(name, withFallBack);
    }

    ~ActorSystem() {
        removeActorSystem(name_);
    }

private:
    void initActorSystem(const std::string & name, const Config & withFallBack) {
        actorsystem_map_.rehash(512);
        actor_map_.rehash(2048);
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

    static void destroyAll();

    static ActorSystem * findActorSystem(const std::string & name) {
        ActorSystem * system = nullptr;
        const_actorsystem_iter it = actorsystem_map_.find(name);
        if (it != actorsystem_map_.end()) {
            system = it->second;
        }
        return system;
    }

    static void removeActorSystem(const std::string & name) {
        actorsystem_map_.erase(name);
    }

    static IActorRef * findActorRef(const Props * props, const std::string & name) {
        return ActorSystem::findActorRef(name);
    }

    static IActorRef * findActorRef(const std::string & name);

    static void removeActor(const std::string & name) {
        actor_map_.erase(name);
    }

    std::string getName() const {
        return name_;
    }

    void setName(const std::string & name) {
        name_ = name;
    }

    // Startup the actor systems
    int start() {
        return 0;
    }

    void shutdown() {
        ActorSystem::destroyAll();
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSYSTEM_H */
