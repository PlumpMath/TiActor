
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

class ActorSystemImpl : public ExtendedActorSystem {
public:
	ActorSystemImpl(const std::string & name) : ExtendedActorSystem(name) {
		//
	}

	ActorSystemImpl(const std::string & name, const Config & config)
		: ExtendedActorSystem(name, config) {
		//
	}

	~ActorSystemImpl() {
	}

protected:
	ActorSystem * createSystemImpl(const std::string & name, const Config & config);
	ActorSystem * createAndStartSystemImpl(const std::string & name, const Config & config);

public:
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
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORSYSTEMIMPL_H */
