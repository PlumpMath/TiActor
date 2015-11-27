
#ifndef TIACTOR_ACTOR_PROPS_H
#define TIACTOR_ACTOR_PROPS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include <TiActor/actor/Deploy.h>

namespace TiActor {

class Router;
class Actor;

class Props {
private:
    std::string name_;
    Deploy * deploy_;
    uint32_t inputType_;
    uint32_t outputType_;

public:
    static bool staticInited;
    static Deploy * defaultDeploy;

protected:
    Props() : Props(*defaultDeploy, 0) {
    }

    Props(const Props & src) {
        copyProps(src);
    }

public:
    Props(const Deploy & deploy, uint32_t inputType) {
        *deploy_ = deploy;
        inputType_ = inputType;
    }

    Props(const Deploy * deploy, uint32_t inputType) {
        deploy_ = const_cast<Deploy * >(deploy);
        inputType_ = inputType;
    }

    Props(const Actor * actor) {
        deploy_ = nullptr;
        inputType_ = 0;
    }

    ~Props() {
        if (deploy_ && deploy_ != defaultDeploy) {
            deploy_->destroy();
        }
    }

    static void staticInit() {
        if (!staticInited) {
            defaultDeploy = new Deploy();
            staticInited = true;
        }
    }

    static void staticFree() {
        if (staticInited) {
            if (defaultDeploy) {
                delete defaultDeploy;
            }
            staticInited = false;
        }
    }

    std::string getName() const {
        return name_;
    }

    void setName(const std::string & name) {
        name_ = name;
    }

    Props * withRouter(const RouterConfig * routerConfig) {
        Props * copy = new Props();
        if (copy) {
            copy->copyProps(*this);
            copy->deploy_ = new Deploy(routerConfig);
        }
        return copy;
    }

    static Props * createWithRouter(const Deploy * deploy, uint32_t inputType, const RouterConfig * routerConfig) {
        Deploy * deployNew = new Deploy(routerConfig);;
        Props * props = new Props(deployNew, inputType);
        return props;
    }

protected:
    void copyProps(const Props & src) {
        this->name_ = src.name_;
        this->deploy_ = src.deploy_;
        this->inputType_ = src.inputType_;
        this->outputType_ = src.outputType_;
    }

private:
    //
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ACTOR_PROPS_H */
