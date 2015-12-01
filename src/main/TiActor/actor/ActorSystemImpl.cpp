
#include "TiActor/actor/ActorSystem.h"
#include "TiActor/actor/ActorSystemImpl.h"

namespace TiActor {

ActorSystem * ActorSystemImpl::createSystemImpl(const std::string & name, const Config & config) {
	ActorSystem * system = new ActorSystemImpl(name, config);
	return system;
}

ActorSystem * ActorSystemImpl::createAndStartSystemImpl(const std::string & name, const Config & config) {
	ActorSystem * system = new ActorSystemImpl(name, config);
	if (system) {
		system->start();
	}
	return system;
}

} // namespace TiActor
