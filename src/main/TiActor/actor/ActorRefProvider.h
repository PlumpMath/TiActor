
#ifndef TIACTOR_ACTOR_ACTORREFPROVIDER_H
#define TIACTOR_ACTOR_ACTORREFPROVIDER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <atomic>
#include <unordered_map>

namespace TiActor {

class ActorSystemImpl;
class IInternalActorRef;
class LocalActorRef;
class IActorRef;
class Props;
class ActorPath;
class Deploy;
class Deployer;
class RootGuardianActorRef;

class IActorRefProvider {
public:
    virtual void init(ActorSystemImpl * system) = 0;

    virtual IInternalActorRef * getRootGuardian() const = 0;
    virtual LocalActorRef * getGuardian() const  = 0;
    virtual LocalActorRef * getSystemGuardian() const  = 0;
    virtual IActorRef * getDeadLetters() const = 0;

    virtual IInternalActorRef * actorOf(ActorSystemImpl * system, Props * props, IInternalActorRef * supervisor,
        ActorPath * path, bool systemService, Deploy * deploy, bool lookupDeploy, bool async) = 0;
};

class LocalActorRefProvider : public IActorRefProvider {
private:
    Deployer * deployer_;
    IInternalActorRef * deadLetters_;
    RootActorPath * rootPath_;
    std::atomic<int> tempNumber_;
    ActorPath * tempNode_;
    ActorSystemImpl * system_;
    RootGuardianActorRef * rootGuardian_;
    LocalActorRef * userGuardian_;      // This is called guardian in TiActor
    LocalActorRef * systemGuardian_;
    Mailbox * defaultMailbox_;          // TODO: switch to MailboxType

    std::unordered_map<std::string, IInternalActorRef *> extraNames_;

protected:
    void inernalInit(const std::string & systemName, Deployer * deployer) {
        deployer_ = deployer;
        deadLetters_ = nullptr;
        tempNumber_ = 1;
    }

public:
    LocalActorRefProvider(const std::string & systemName)
        : deployer_(nullptr), deadLetters_(nullptr), rootPath_(nullptr),
          tempNode_(nullptr), system_(nullptr), rootGuardian_(nullptr),
          userGuardian_(nullptr), systemGuardian_(nullptr), defaultMailbox_(nullptr) {
        inernalInit(systemName, nullptr);
    }

    LocalActorRefProvider(const std::string & systemName, Deployer * deployer)
        : LocalActorRefProvider(systemName) {
        inernalInit(systemName, deployer);
    }

    RootGuardianActorRef * createRootGuardion(ActorSystemImpl * system) {
        return nullptr;
    }

    LocalActorRef * createUserGuardion(RootGuardianActorRef * rootGuardian) {
        return nullptr;
    }

    LocalActorRef * createSystemGuardion(RootGuardianActorRef * rootGuardian) {
        return nullptr;
    }

    virtual void init(ActorSystemImpl * system) {
        system_ = system;
        rootGuardian_ = createRootGuardion(system);
        if (rootGuardian_) {
            userGuardian_ = createUserGuardion(rootGuardian_);
            systemGuardian_ = createSystemGuardion(rootGuardian_);
            //rootGuardian_->start();
        }
    }

    IInternalActorRef * actorOf(ActorSystemImpl * system, Props * props) {
        return actorOf(system, props, nullptr, nullptr, false, nullptr, false, false);
    }

    virtual IInternalActorRef * actorOf(ActorSystemImpl * system, Props * props, IInternalActorRef * supervisor,
        ActorPath * path, bool systemService, Deploy * deploy, bool lookupDeploy, bool async) {
        return nullptr;
    }

    virtual IInternalActorRef * getRootGuardian() const  {
        return reinterpret_cast<IInternalActorRef *>(rootGuardian_);
    }

    virtual LocalActorRef * getGuardian() const {
        return userGuardian_;
    }

    virtual LocalActorRef * getSystemGuardian() const {
        return systemGuardian_;
    }

    virtual IActorRef * getDeadLetters() const {
        return deadLetters_;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTORREFPROVIDER_H */
