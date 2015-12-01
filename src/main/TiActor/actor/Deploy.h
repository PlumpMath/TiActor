
#ifndef TIACTOR_ACTOR_DEPLOY_H
#define TIACTOR_ACTOR_DEPLOY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/stddef.h"

namespace TiActor {

class RouterConfig;

class Deploy {
private:
    std::string name_;
    RouterConfig * routerConfig_;

public:
    Deploy() {
        initDeploy("default");
    }

    Deploy(const RouterConfig * routerConfig) {
        initDeploy(routerConfig);
    }

    Deploy(const std::string & name) {
        initDeploy(name);
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

    void initDeploy(const std::string & name) {
        name_ = name;
    }

protected:
    void cloneDeploy(const Deploy & src) {
        this->name_ = src.name_;
    }

public:
    void destroy() {
        //
    }

    std::string getName() const {
        return name_;
    }

    void setName(const std::string & name) {
        name_ = name;
    }

    Deploy * withRouterConfig(const RouterConfig * routerConfig) {
        routerConfig_ = const_cast<RouterConfig *>(routerConfig);
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_DEPLOY_H */
