
#ifndef TIACTOR_ACTOR_ICHILDRENCONTAINER_H
#define TIACTOR_ACTOR_ICHILDRENCONTAINER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

namespace TiActor {

class IActorRef;
class ActorSystem;
class ActorSystemImpl;
class IInternalActorRef;
class ChildRestartStats;

template <typename T>
class IReadOnlyList {
};

class IChildStats {
};

class IChildrenContainer {
public:
    virtual IChildrenContainer * add(const std::string & name, ChildRestartStats stats) const = 0;
    virtual IChildrenContainer * remove(IActorRef * child) const = 0;
    virtual bool TryGetByName(const std::string & name, IChildStats * stats) const = 0;
    virtual bool TryGetByRef(IActorRef * actor, ChildRestartStats * stats) const = 0;
    virtual IReadOnlyList<IInternalActorRef *> childrens() const = 0;
    virtual IReadOnlyList<ChildRestartStats> stats() const = 0;
    virtual IChildrenContainer * shallDie(IActorRef * actor) const = 0;
    virtual IChildrenContainer * reserve(const std::string & name) const = 0;
    virtual IChildrenContainer * unreserve(const std::string & name) const = 0;
    virtual bool isTerminating()  const = 0;
        virtual bool isNormal() const = 0;
    virtual bool contains(IActorRef * actor) const = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ICHILDRENCONTAINER_H */
