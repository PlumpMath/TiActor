
#ifndef TIACTOR_ROUTING_ROUTER_H
#define TIACTOR_ROUTING_ROUTER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

namespace TiActor {

class RouterConfig;

class Router {
protected:
    int numOfWorkers_;
    RouterConfig * routerConfig_;

public:
    Router() : numOfWorkers_(0) {
    }

    Router(int numOfWorkers) : numOfWorkers_(numOfWorkers) {
    }

    ~Router() {
    }

    RouterConfig * getRouterConfig() const {
        return routerConfig_;
    }
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ROUTING_ROUTER_H */
