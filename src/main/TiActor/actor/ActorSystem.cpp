
#include <stdexcept>

#include "TiActor/actor/ActorSystem.h"

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

IActorRef * ActorSystem::actorOf(Props * props, const std::string & name /*= ""*/)
{
    throw std::logic_error("The method or operation is not implemented.");
}

ActorSelection * ActorSystem::getActorSelection(const ActorPath * actorPath) const
{
    throw std::logic_error("The method or operation is not implemented.");
}

ActorSelection * ActorSystem::getActorSelection(const std::string & actorPath) const
{
    throw std::logic_error("The method or operation is not implemented.");
}

void ActorSystem::dispose()
{
    throw std::logic_error("The method or operation is not implemented.");
}

} // namespace TiActor
