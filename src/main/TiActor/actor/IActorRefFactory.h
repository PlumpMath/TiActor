
#ifndef TIACTOR_ACTOR_IACTORREFFACTORY_H
#define TIACTOR_ACTOR_IACTORREFFACTORY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

namespace TiActor {

class IActorRef;
class Props;
class ActorPath;
class ActorSelection;

class IActorRefFactory {
public:
    virtual IActorRef * actorOf(Props * props, const std::string & name = "") = 0;
    virtual ActorSelection * getActorSelection(const ActorPath * actorPath) const = 0;
    virtual ActorSelection * getActorSelection(const std::string & actorPath) const = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_IACTORREFFACTORY_H */
