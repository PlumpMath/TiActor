
#ifndef TIACTOR_ACTOR_DEPLOY_H
#define TIACTOR_ACTOR_DEPLOY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

namespace TiActor {

class Config;
class RouterConfig;

class Deploy {
private:
    Config * config_;
    RouterConfig * routerConfig_;

public:
    static Deploy * local_;
    static Deploy * none_;

public:
    Deploy() : routerConfig_(nullptr) {
    }

    Deploy(RouterConfig * routerConfig)
        : routerConfig_(routerConfig) {
    }

    Deploy(const Deploy & src) {
        cloneDeploy(src);
    }

    ~Deploy() {
    }

private:
    void initDeploy(const RouterConfig * routerConfig) {
        routerConfig_ = const_cast<RouterConfig *>(routerConfig);
    }

protected:
    void cloneDeploy(const Deploy & src) {
        this->routerConfig_ = src.routerConfig_;
    }

public:
    void destroy() {
        //
    }

    Deploy * withRouterConfig(const RouterConfig * routerConfig) {
        routerConfig_ = const_cast<RouterConfig *>(routerConfig);
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_DEPLOY_H */
