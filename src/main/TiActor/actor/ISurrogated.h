
#ifndef TIACTOR_ACTOR_ISURROGATED_H
#define TIACTOR_ACTOR_ISURROGATED_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class ActorSystem;

class ISurrogated {
public:
    virtual ISurrogated * toSurrogate(const ActorSystem * system) = 0;
};

class ISurrogate {
public:
    virtual ISurrogated * fromSurrogate(const ActorSystem * system) = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ISURROGATED_H */
