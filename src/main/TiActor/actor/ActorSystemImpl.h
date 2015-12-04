
#ifndef TIACTOR_ACTOR_ACTORSYSTEMIMPL_H
#define TIACTOR_ACTOR_ACTORSYSTEMIMPL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/actor/ExtendedActorSystem.h"
#include "TiActor/config/Config.h"
#include "TiActor/config/ConfigurationFactory.h"

#include "TiActor/actor/ActorRefProvider.h"
#include "TiActor/actor/LocalActorRef.h"

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

    IActorRefProvider * provider_;
    Dispatchers *       dispatchers_;
    Mailboxes *         mailboxes_;
    IScheduler *        scheduler_;
    IActorRef *         deadLetters_;

public:
    ActorSystemImpl(const std::string & name) : ExtendedActorSystem(name),
        dispatchers_(nullptr), mailboxes_(nullptr),
        scheduler_(nullptr), deadLetters_(nullptr) {
        initActorSystem(name, ConfigurationFactory::load());
    }

	ActorSystemImpl(const std::string & name, const Config & withFallBack)
		: ExtendedActorSystem(name, withFallBack),
          dispatchers_(nullptr), mailboxes_(nullptr),
          scheduler_(nullptr), deadLetters_(nullptr) {
        initActorSystem(name, withFallBack);
	}

	~ActorSystemImpl() {
        removeActorSystem(name_);
	}

private:
    void initActorSystem(const std::string & name, const Config & config) {
        actorsystem_map_.rehash(128);
        actor_map_.rehash(2048);
        name_ = name;
        config_ = config;

        configureSettings(config);
        configureEventStream();
        configureProvider();
        configureScheduler();
        configureSerialization();
        configureMailboxes();
        configureDispatchers();
        configureActorProducerPipeline();
    }

protected:
	ActorSystem * createSystemImpl(const std::string & name, const Config & config);
	ActorSystem * createAndStartSystemImpl(const std::string & name, const Config & config);

    ActorCell * getSystemGuardianCell() const {
        ActorCell * cell = nullptr;
        if (provider_) {
            LocalActorRef * sysGuardian = provider_->getSystemGuardian();
            if (sysGuardian) {
                cell = sysGuardian->getCell();
            }
        }
        return cell;
    }

public:
    virtual std::string getName() const {
        return name_;
    }

    virtual void setName(const std::string & name) {
        name_ = name;
    }

    ActorSystem * getSystem() {
        return static_cast<ActorSystem *>((ActorSystemImpl *)this);
    }

    ActorSystemImpl * getSystemImpl() {
        return const_cast<ActorSystemImpl *>(this);
    }

    // IActorRefFactory
    IActorRef * actorOf(Props * props, const std::string & name = "");

    ActorSelection * getActorSelection(const ActorPath * actorPath) const {
        return nullptr;
    }

    ActorSelection * getActorSelection(const std::string & actorPath) const {
        return nullptr;
    }

    // ExtendedActorSystem
    IActorRefProvider * getProvider() const {
        return provider_;
    }

    IInternalActorRef * getGuardian() const {
        IInternalActorRef * guardian = nullptr;
        if (provider_) {
            guardian = reinterpret_cast<IInternalActorRef *>(provider_->getGuardian());
        }
        return guardian;
    }

    IInternalActorRef * getSystemGuardian() const {
        IInternalActorRef * guardian = nullptr;
        if (provider_) {
            guardian = reinterpret_cast<IInternalActorRef *>(provider_->getSystemGuardian());
        }
        return guardian;
    }

    IActorRef * systemActorOf(Props * props, const std::string & name) {
        IActorRef * actor = nullptr;
        ActorCell * cell = getSystemGuardianCell();
        if (cell) {
            actor = cell->actorOf(props, name);
        }
        return actor;
    }

    virtual Dispatchers * getDispatchers() const {
        return dispatchers_;
    }

    virtual Mailboxes * getMailboxes() const {
        return mailboxes_;
    }

    virtual IActorRef * getDeadLetters() const {
        IActorRef * deadLetters = nullptr;
        if (provider_) {
            deadLetters = provider_->getDeadLetters();
        }
        return deadLetters;
    }

    void configureSettings(const Config & config);
    void configureEventStream();
    void configureProvider();
    void configureScheduler();
    void configureSerialization();
    void configureMailboxes();
    void configureDispatchers();
    void configureActorProducerPipeline();

    virtual ActorSystem * create() {
        return ActorSystem::create(name_, config_);
    }

    // IDisposable
    void dispose() {
        //
    }

    // Startup the actor systems
    virtual void start();

    virtual void stop(IActorRef * actor) {
        //;
    }

    virtual void shutdown() {
        ActorSystem::destroyAll();
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSYSTEMIMPL_H */
