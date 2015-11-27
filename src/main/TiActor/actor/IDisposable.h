
#ifndef TIACTOR_ACTOR_IDISPOSABLE_H
#define TIACTOR_ACTOR_IDISPOSABLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace TiActor {

class IDisposable {
public:
    virtual void Dispose() = 0;
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ACTOR_IDISPOSABLE_H */
