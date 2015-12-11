
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
    ActorCell * getUserGuardianCell() const {
        ActorCell * cell = nullptr;
        if (provider_) {
            LocalActorRef * userGuardian = provider_->getGuardian();
            if (userGuardian) {
                cell = userGuardian->getCell();
            }
        }
        return cell;
    }

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
    virtual IActorRef * actorOf(Props * props, const std::string & name = "") override;

    virtual ActorSelection * getActorSelection(const ActorPath * actorPath) const override {
        // TODO:
        return nullptr;
    }

    virtual ActorSelection * getActorSelection(const std::string & actorPath) const override {
        // TODO:
        return nullptr;
    }

    // ExtendedActorSystem
    virtual IActorRef * systemActorOf(Props * props, const std::string & name = "") override {
        IActorRef * actor = nullptr;
        ActorCell * cell = getSystemGuardianCell();
        if (cell) {
            actor = cell->actorOf(props, name);
        }
        return actor;
    }

    virtual IActorRefProvider * getProvider() const override {
        return provider_;
    }

    virtual IInternalActorRef * getGuardian() const override {
        IInternalActorRef * guardian = nullptr;
        if (provider_) {
            guardian = reinterpret_cast<IInternalActorRef *>(provider_->getGuardian());
        }
        return guardian;
    }

    virtual IInternalActorRef * getSystemGuardian() const override {
        IInternalActorRef * guardian = nullptr;
        if (provider_) {
            guardian = reinterpret_cast<IInternalActorRef *>(provider_->getSystemGuardian());
        }
        return guardian;
    }

    virtual Dispatchers * getDispatchers() const override {
        return dispatchers_;
    }

    virtual Mailboxes * getMailboxes() const override {
        return mailboxes_;
    }

    virtual IActorRef * getDeadLetters() const override {
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
    virtual void start() override;

    virtual void stop(IActorRef * actor) {
        //
    }

    virtual void shutdown() {
        ActorSystem::destroyAll();
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSYSTEMIMPL_H */
