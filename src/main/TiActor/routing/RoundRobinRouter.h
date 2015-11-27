
#ifndef TIACTOR_ROUTING_ROUNDROBINROUTER_H
#define TIACTOR_ROUTING_ROUNDROBINROUTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/routing/Router.h"

namespace TiActor {

class RoundRobinRouter : public Router {
private:
    //

public:
    RoundRobinRouter() : Router() {
    }

    RoundRobinRouter(int numOfWorkers) : Router(numOfWorkers) {
    }

    ~RoundRobinRouter() {
    }
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ROUTING_ROUNDROBINROUTER_H */
