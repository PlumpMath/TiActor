
#ifndef TIACTOR_ACTOR_ACTORSYSTEM_H
#define TIACTOR_ACTOR_ACTORSYSTEM_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <unordered_map>

#include "TiActor/basic/stddef.h"
#include "TiActor/config/ActorConfig.h"
#include "TiActor/config/Config.h"
#include "TiActor/config/ConfigurationFactory.h"
#include "TiActor/actor/ActorRef.h"
#include "TiActor/actor/Props.h"
#include "TiActor/actor/IActorRefFactory.h"
#include "TiActor/actor/IDisposable.h"

#include "TiActor/actor/Message.h"
#include "TiActor/queue/RingQueue.h"

namespace TiActor {

class Mailboxes;
class Dispatchers;
class IScheduler;

class ActorSystem : public IActorRefFactory, public IDisposable {
public:
    typedef std::unordered_map<std::string, ActorSystem *>                  actorsystem_map_type;
    typedef std::unordered_map<std::string, ActorSystem *>::iterator        actorsystem_iter;
    typedef std::unordered_map<std::string, ActorSystem *>::const_iterator  const_actorsystem_iter;
    typedef std::pair<std::string, ActorSystem *>                           actorsystem_pair_type;

    typedef std::unordered_map<std::string, Actor *>                    actor_map_type;
    typedef std::unordered_map<std::string, Actor *>::iterator          actor_iter;
    typedef std::unordered_map<std::string, Actor *>::const_iterator    const_actor_iter;
    typedef std::pair<std::string, Actor *>                             actor_pair_type;

    typedef RingQueue<Message *, 8192>    queue_type;

private:
    //

public:
    static actorsystem_map_type actorsystem_map_;
    static actor_map_type       actor_map_;
    static queue_type           msg_queue_;

public:
    ActorSystem(const std::string & name) {}
    ActorSystem(const std::string & name, const Config & withFallBack) {}
    ~ActorSystem() {
    }

private:
    //

protected:
    static ActorSystem * createAndStartSystem(const std::string & name, const Config & withFallBack);

public:
    virtual Dispatchers * getDispatchers() const = 0;
    virtual Mailboxes * getMailboxes() const = 0;
    virtual IActorRef * getDeadLetters() const = 0;

    static ActorSystem * create(const std::string & name) {
        return createAndStartSystem(name, ConfigurationFactory::load());
    }

    static ActorSystem * create(const std::string & name, const Config & config) {
        return createAndStartSystem(name, config);
    }

    virtual ActorSystem * create() = 0;

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

    static void addActor(const std::string & name, Actor * actor) {
        actor_pair_type actor_pair(name, actor);
        actor_map_.insert(actor_pair);
    }

    static void removeActor(const std::string & name) {
        actor_map_.erase(name);
    }

    virtual std::string getName() const = 0;
    virtual void setName(const std::string & name) = 0;

    virtual int start() = 0;
    virtual void stop(IActorRef * actor) = 0;
    virtual void shutdown() = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSYSTEM_H */
