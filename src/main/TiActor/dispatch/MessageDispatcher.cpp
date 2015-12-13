

#include "TiActor/dispatch/MessageDispatcher.h"
#include "TiActor/actor/ActorCell.h"

namespace TiActor {

void MessageDispatcher::dispatch(ActorCell * cell, Envelope * envelope)
{
    if (cell) {
        cell->invoke(envelope);
    }
}

void MessageDispatcher::systemDispatch(ActorCell * cell, Envelope * envelope)
{
    if (cell) {
        cell->systemInvoke(envelope);
    }
}

} // namespace TiActor
