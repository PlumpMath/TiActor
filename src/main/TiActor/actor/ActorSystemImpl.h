
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

#include "TiActor/actor/ActorRefProvider.h"

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

    // ExtendedActorSystem
    IActorRefProvider * getProvider() const {
        return provider_;
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

    virtual Dispatchers * getDispatchers() const {
        return dispatchers_;
    }

    virtual Mailboxes * getMailboxes() const {
        return mailboxes_;
    }

    virtual IActorRef * getDeadLetters() const {
        if (provider_ != nullptr) {
            return provider_->getDeadLetters();
        }
        return nullptr;
        //return deadLetters_;
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

    // IActorRefFactory
    IActorRef * actorOf(Props * props, const std::string & name = "");

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

    // Startup the actor systems
    virtual void start() {
        //
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
