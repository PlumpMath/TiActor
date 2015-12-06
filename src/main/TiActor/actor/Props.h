
#ifndef TIACTOR_ACTOR_PROPS_H
#define TIACTOR_ACTOR_PROPS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

#include "TiActor/basic/stdint.h"
#include "TiActor/actor/Deploy.h"

namespace TiActor {

//class Deploy;
class Router;
class UntypedActor;
class ActorBase;
class IIndirectActorProducer;
class RouterConfig;
class IActorContext;
class IInternalActorRef;

class Props {
private:
    std::string name_;
    Deploy * deploy_;
    ActorBase * actor_;
    uint32_t inputType_;
    uint32_t outputType_;
    IIndirectActorProducer * producer_;

    static IIndirectActorProducer * defaultProducer;

public:
    static Deploy * defaultDeploy;

protected:
    Props() : deploy_(nullptr), actor_(nullptr), inputType_(0), outputType_(0),
              producer_(nullptr) {
        deploy_ = defaultDeploy;
        initProps();
    }

    Props(const Props & src) {
        copyProps(src);
    }

public:
    Props(const Deploy & deploy, uint32_t inputType) : Props() {
        deploy_ = const_cast<Deploy * >(&deploy);
        inputType_ = inputType;
        initProps();
    }

    Props(const Deploy * deploy, uint32_t inputType) : Props() {
        deploy_ = const_cast<Deploy * >(deploy);
        inputType_ = inputType;
        initProps();
    }

    Props(const ActorBase * actor) : Props() {
        actor_ = const_cast<ActorBase * >(actor);
        initProps();
    }

    Props(const UntypedActor * actor) : Props() {
        actor_ = reinterpret_cast<ActorBase * >(const_cast<UntypedActor *>(actor));
        initProps();
    }

    ~Props();

    void initProps() {
        producer_ = createProducer();
    }

    static IIndirectActorProducer * createProducer();

    virtual ActorBase * newActor(IActorContext * context);

    std::string getName() const {
        return name_;
    }

    void setName(const std::string & name) {
        name_ = name;
    }

    IInternalActorRef * getActorRef() const {
        return reinterpret_cast<IInternalActorRef *>(actor_);
    }

    Props * withRouter(RouterConfig * routerConfig) {
        Props * copy = new Props();
        if (copy) {
            copy->copyProps(*this);
            copy->deploy_ = new Deploy(routerConfig);
        }
        return copy;
    }

    static Props * createWithRouter(Deploy * deploy, uint32_t inputType, RouterConfig * routerConfig) {
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

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_PROPS_H */
