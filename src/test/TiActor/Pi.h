
#ifndef TIACTOR_TEST_PI_H
#define TIACTOR_TEST_PI_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

//#define TIACTOR_USE_STATICLIB
#include <TiActor/all.h>
#include <TiActor/actor/Message.h>
#include <TiActor/actor/IActorContext.h>
#include <TiActor/actor/ActorBase.h>
#include <TiActor/actor/ActorRef.h>
#include <TiActor/actor/Props.h>
#include <TiActor/actor/UntypedActor.h>
#include <TiActor/actor/ActorSystem.h>
#include <TiActor/actor/ActorSystemImpl.h>
#include <TiActor/routing/RouterConfig.h>
#include <TiActor/routing/Router.h>
#include <TiActor/routing/RoundRobinRouter.h>
#include <TiActor/utils/Runtime.h>

using namespace TiActor;

class Calculate : public MessageBase<Calculate> {
    //
};

class Work : public MessageBase<Work> {
private:
    int start_;
    int numOfElements_;

public:
    Work(int start, int numOfElements) {
        start_ = start;
        numOfElements_ = numOfElements;
    }

    int getStart() const {
        return start_;
    }

    int getNumOfElements() const {
        return numOfElements_;
    }
};

class Result : public MessageBase<Result> {
private:
    double value_;

public:
    Result(double value) {
        value_ = value;
    }

    double getValue() const {
        return value_;
    }
};

class PiApproximation : public MessageBase<PiApproximation> {
private:
    double pi_;
    double duration_;

public:
    PiApproximation(double pi, double duration) {
        pi_ = pi;
        duration_ = duration;
    }

    double getPi() const {
        return pi_;
    }

    double getDuration() const {
        return duration_;
    }
};

static
double calulatePiFor(int start, int numOfElements) {
    double acc = 0.0;
    for (int i = start * numOfElements; i <= ((start + 1) * numOfElements - 1); ++i) {
        acc += 4.0 * (1 - (i % 2) * 2) / (2 * i + 1);
    }
    return acc;
}

class Worker : public UntypedActor {
public:
    struct InnerMessage {
        enum { Dummy = 0, Work };
    };

public:
    void onReceive(IMessage * message);
};

class Master : public UntypedActor {
private:
    int numOfWorkers_;
    int numOfMessages_;
    int numOfElements_;

    volatile int numOfResults;

    IActorRef * listener_;
    IActorRef * workerRouter_;

public:
    struct InnerMessage {
        enum { Dummy = 0, Calculate, Result };
    };

public:
    Master(int numOfWorkers, int numOfMessages, int numOfElements, IActorRef * listener)
        : UntypedActor(), numOfWorkers_(numOfWorkers), numOfMessages_(numOfMessages),
          numOfElements_(numOfElements), numOfResults(0), listener_(nullptr),
          workerRouter_(nullptr) {
        this->numOfMessages_ = numOfMessages;
        this->numOfElements_ = numOfElements;
        this->listener_ = listener;

        TiActor::Router * router = new TiActor::RoundRobinRouter(numOfWorkers);
        if (router) {
            TiActor::RouterConfig * routerConfig = router->getRouterConfig();
            if (routerConfig) {
                TiActor::Deploy * deploy = new TiActor::Deploy();
                if (deploy) {
                    TiActor::Props * props = TiActor::Props::createWithRouter(deploy, 0, routerConfig);
                    if (props) {
                        IActorContext * context = this->getContext();
                        if (context) {
                            workerRouter_ = context->actorOf(props, "workerRouter");
                        }
                        //delete props;
                    }
                    //delete deploy;
                }
                //delete routerConfig;
            }
            //delete router;
        }        
    }

    ~Master() {
        //listener_ = nullptr;
        if (listener_) {
            delete listener_;
            listener_ = nullptr;
        }
        if (workerRouter_) {
            delete workerRouter_;
            workerRouter_ = nullptr;
        }
    }

    void onReceive(IMessage * message) {
        message_type msgType = message->getType();
        if (msgType == InnerMessage::Calculate) {
            if (workerRouter_) {
                for (int start = 0; start < numOfMessages_; ++start) {
                    Work * work = new Work(start, numOfElements_);
                    work->setType(Worker::InnerMessage::Work);
                    workerRouter_->tell(work, this->getSelf());
                }
            }
        }
        else if (msgType == InnerMessage::Result) {
            //
        }
        else {
            unhandleMessage("Master", message);
        }
    }
};

class Listener : public UntypedActor {
public:
    struct InnerMessage {
        enum { Dummy = 0, PiApproximation };
    };
public:
    void onReceive(IMessage * message) {
        message_type msgType = message->getType();
        if (msgType == InnerMessage::PiApproximation) {
            PiApproximation * approximation = reinterpret_cast<PiApproximation *>(message);
            if (approximation) {
                std::cout << std::endl << "Pi approximation: \t\t" << approximation->getPi()
                    << "\n\tCalculation time: \t" << approximation->getDuration();
                IActorContext * context = this->getContext();
                if (context) {
                    ActorSystem * system = context->getSystem();
                    if (system) {
                        system->shutdown();
                    }
                }
                delete approximation;
            }
        }
        else {
            unhandleMessage("Listener", message);
        }
    }
};

class UntypedActorFactory : public UntypedActor {
public:
    UntypedActorFactory() {}
    ~UntypedActorFactory() {}
};

class Pi {
public:
    Pi() {}
    ~Pi() {}

    void calculate(int numOfWorkers, int numOfMessages, int numOfElements) {
        // Create an actor system
        ActorSystem * system = ActorSystem::create("PiSystem");
        if (system) {
            // Create the result listener, which will print the result and shutdown the system.
            IActorRef * listener = system->actorOf(new Props(new Listener()), "listener");
            if (listener) {
                // Create the master
                UntypedActor * masterActor = new Master(numOfWorkers, numOfMessages, numOfElements, listener);
                if (masterActor) {
                    IActorRef * master = system->actorOf(new Props(masterActor), "master");
                    if (master) {
#if 1
                        master->tell((new Calculate())->setTypeEx(Master::InnerMessage::Calculate));
#else
                        Calculate * calculate = new Calculate();
                        if (calculate) {
                            calculate->setType(Master::InnerMessage::Calculate);
                            master->tell(calculate);
                        }
#endif
                    }
                }
            }
        }
    }

    static void main(int argn, char * argv[]) {
        Pi * pi = new Pi();
        int numOfProcessors = Runtime::getAvailableProcessors();
        if (pi) {
            pi->calculate(numOfProcessors, 10000, 10000);
            delete pi;
        }
    }
};

#endif  /* TIACTOR_TEST_PI_H */
