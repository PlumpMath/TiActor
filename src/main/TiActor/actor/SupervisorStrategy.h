
#ifndef TIACTOR_ACTOR_SUPERVISORSTRATEGY_H
#define TIACTOR_ACTOR_SUPERVISORSTRATEGY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <stdexcept>

#include "TiActor/actor/ISurrogated.h"

namespace TiActor {

class IActorRef;
class ActorCell;
class ActorSystemImpl;
class IInternalActorRef;
class IActorContext;
class LogEvent;
class OneForOneStrategy;
class IDecider;

enum Directive {
    Resume,
    Restart,
    Escalate,
    Stop
};

class IDecider {
public:
    virtual Directive decide(const std::exception & cause) = 0;
};

class SupervisorStrategy : public ISurrogated {
private:
    bool loggingEnabled_;

public:
    static IDecider * DefaultDecider;
    static SupervisorStrategy * DefaultStrategy;
    static OneForOneStrategy * StoppingStrategy;

public:
    SupervisorStrategy() : loggingEnabled_(false) {
    }

    ~SupervisorStrategy() {
    }

private:
    void publish(IActorContext * context, LogEvent * logEvent) {
        try {
            //TODO: getContext().getSystem()
        }
        catch (...) {
            // swallow any exceptions
        }
    }

protected:
    virtual Directive * handle(IActorRef * child, const std::exception & x) = 0;
    virtual void processFailure(IActorContext * actorCell, bool restart, const std::exception & cause) = 0;

    void * restartChild(IActorRef * child, const std::exception & cause, bool suspendFirst) {
        // TODO:
    }

    void * resumeChild(IActorRef * child, std::exception cause) {
        // TODO: child->AsInstanceOf<IInternalActorRef>()->resume(exception);
    }

    virtual void logFailure(IActorContext * context, IActorRef * child,
        const std::exception & cause, Directive * directive) {
        if (isLoggingEnabled()) {
            // TODO:
        }
    }

    bool isLoggingEnabled() const { return loggingEnabled_; }

    void setLoggingEnabled(bool loggingEnabled) {
        loggingEnabled_ = loggingEnabled;
    }

public:
    virtual bool handleFailure(ActorCell * actorCell, const std::exception & cause) {
        return false;
    }

    virtual ISurrogated * toSurrogate(const ActorSystem * system) override {
        return nullptr;
    }
};

class SupervisorStrategyBase : public SupervisorStrategy {
private:
    int         maxNumberOfRetries_;
    int         withinTimeRangeMilliseconds_;
    IDecider *  decider_;

public:
    SupervisorStrategyBase(IDecider * decider) : maxNumberOfRetries_(0), withinTimeRangeMilliseconds_(0),
        decider_(decider) {
    }

    SupervisorStrategyBase(Directive directive) : SupervisorStrategyBase((IDecider *)nullptr){
    }

    ~SupervisorStrategyBase() {
    }

    int getMxNumberOfRetries() const { return maxNumberOfRetries_; }
    int getWithinTimeRangeMilliseconds() const { return withinTimeRangeMilliseconds_; }

    IDecider * getDecider() const { return decider_; }
};

class OneForOneStrategy : public SupervisorStrategyBase {
public:
    OneForOneStrategy(IDecider * decider) : SupervisorStrategyBase(decider) {
    }

    OneForOneStrategy(Directive directive) : SupervisorStrategyBase(directive) {
    }

    ~OneForOneStrategy() {
    }

protected:
    virtual Directive * handle(IActorRef * child, const std::exception & x) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void processFailure(IActorContext * actorCell, bool restart, const std::exception & cause) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void logFailure(IActorContext * context, IActorRef * child, const std::exception & cause, Directive * directive) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

public:
    virtual bool handleFailure(ActorCell * actorCell, const std::exception & cause) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual ISurrogated * toSurrogate(const ActorSystem * system) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }
};

class AllForOneStrategy : public SupervisorStrategyBase {
public:
    AllForOneStrategy(IDecider * decider) : SupervisorStrategyBase(decider) {
    }

    AllForOneStrategy(Directive directive) : SupervisorStrategyBase(directive) {
    }

    ~AllForOneStrategy() {
    }

protected:
    virtual Directive * handle(IActorRef * child, const std::exception & x) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void processFailure(IActorContext * actorCell, bool restart, const std::exception & cause) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual void logFailure(IActorContext * context, IActorRef * child, const std::exception & cause, Directive * directive) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

public:
    virtual bool handleFailure(ActorCell * actorCell, const std::exception & cause) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    virtual ISurrogated * toSurrogate(const ActorSystem * system) override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }
};


} // namespace TiActor

#endif  /* TIACTOR_ACTOR_SUPERVISORSTRATEGY_H */
