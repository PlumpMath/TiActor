
#ifndef TIACTOR_ROUTING_ROUTERCONFIG_H
#define TIACTOR_ROUTING_ROUTERCONFIG_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

namespace TiActor {

class RouterConfig {
protected:
    int numOfWorkers_;

public:
    RouterConfig() : numOfWorkers_(0) {
    }

    RouterConfig(int numOfWorkers) : numOfWorkers_(numOfWorkers) {
    }

    ~RouterConfig() {
    }
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ROUTING_ROUTERCONFIG_H */
