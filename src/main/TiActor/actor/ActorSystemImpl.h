
#ifndef TIACTOR_ACTOR_ACTORSYSTEMIMPL_H
#define TIACTOR_ACTOR_ACTORSYSTEMIMPL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/stddef.h"
#include "TiActor/actor/ExtendedActorSystem.h"
#include "TiActor/config/Config.h"
#include "TiActor/config/ConfigurationFactory.h"

namespace TiActor {

class ActorSystem;
class Props;
class IActorRef;
class ActorSelection;
class ActorPath;
class IActorRefProvider;
class IInternalActorRef;

class Mailboxes;
class Dispatchers;
class IScheduler;

class ActorSystemImpl : public ExtendedActorSystem {
private:
    std::string name_;
    Config config_;

    Dispatchers * dispatchers_;
    Mailboxes * mailboxes_;
    IActorRef * deadLetters_;
    IScheduler * scheduler_;

public:
    ActorSystemImpl(const std::string & name) : ExtendedActorSystem(name),
        dispatchers_(nullptr), mailboxes_(nullptr),
        deadLetters_(nullptr), scheduler_(nullptr) {
        initActorSystem(name, ConfigurationFactory::load());
    }

	ActorSystemImpl(const std::string & name, const Config & withFallBack)
		: ExtendedActorSystem(name, withFallBack),
          dispatchers_(nullptr), mailboxes_(nullptr),
          deadLetters_(nullptr), scheduler_(nullptr) {
        initActorSystem(name, withFallBack);
	}

	~ActorSystemImpl() {
        removeActorSystem(name_);
	}

private:
    void initActorSystem(const std::string & name, const Config & withFallBack) {
        actorsystem_map_.rehash(256);
        actor_map_.rehash(512);
        name_ = name;
        config_ = withFallBack;
    }

protected:
	ActorSystem * createSystemImpl(const std::string & name, const Config & config);
	ActorSystem * createAndStartSystemImpl(const std::string & name, const Config & config);

public:
    virtual std::string getName() const {
        return name_;
    }

    virtual void setName(const std::string & name) {
        name_ = name;
    }

    virtual Dispatchers * getDispatchers() const {
        return dispatchers_;
    }

    virtual Mailboxes * getMailboxes() const {
        return mailboxes_;
    }

    virtual IActorRef * getDeadLetters() const {
        return deadLetters_;
    }

    virtual ActorSystem * create() {
        return ActorSystem::create(name_, config_);
    }

    // IActorRefFactory
    IActorRef * actorOf(const Props * props, const std::string & name = "");

    ActorSelection * getActorSelection(const ActorPath * actorPath) const {
        return nullptr;
    }

    ActorSelection * getActorSelection(const std::string & actorPath) const {
        return nullptr;
    }

    // IDisposable
    void dispose() {
        //
    }

    // ExtendedActorSystem
    IActorRefProvider * getProvider() const {
        //
        return nullptr;
    }

    IInternalActorRef * getGuardian() const {
        //
        return nullptr;
    }

    IInternalActorRef * getSystemGuardian() const {
        //
        return nullptr;
    }

    IActorRef * systemActorOf(const Props * props, const std::string & name) {
        //
        return nullptr;
    }

    // Startup the actor systems
    virtual int start() {
        return 0;
    }

    virtual void stop(IActorRef * actor) {
        //;
    }

    virtual void shutdown() {
        ActorSystem::destroyAll();
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSYSTEMIMPL_H */
