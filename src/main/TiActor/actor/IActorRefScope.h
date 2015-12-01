
#ifndef TIACTOR_ACTOR_IACTORREFSCOPE_H
#define TIACTOR_ACTOR_IACTORREFSCOPE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class IActorRefScope {
public:
    virtual bool isLocal() const = 0;
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_IACTORREFSCOPE_H */
