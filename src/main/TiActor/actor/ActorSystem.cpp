
#include <stdio.h>

#include "TiActor/actor/Actor.h"
#include "TiActor/actor/ActorSystem.h"
#include "TiActor/actor/ActorSystemImpl.h"

#include "TiActor/actor/ActorCell.h"
#include "TiActor/actor/Deploy.h"
#include "TiActor/basic/threadlocal.h"

#include "TiActor/actor/IIndirectActorProducer.h"
#include "TiActor/actor/DefaultProducer.h"

namespace TiActor {

Deploy * Deploy::local_ = new Deploy();
Deploy * Deploy::none_ = new Deploy();

IIndirectActorProducer * Props::defaultProducer = new DefaultProducer();

volatile TI_THREAD_LOCAL ActorCell * InternalCurrentActorCellKeeper::current_ = nullptr;

} // namespace TiActor
