
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include <memory>
#include <vector>
#include <functional>

#include "Pi.h"

#include <TiActor/basic/stddef.h>
#include <TiActor/queue/RingQueue.h>

#include <TiActor/config/static_link.h>

void RingQueue_simple_test()
{
    uint64_t value = 1, ret, *ret_val;

    std::cout << "push value: " << value << std::endl;

    RingQueue<uint64_t, 32> queue;
    queue.capacity();
    queue.push(&value);
    ret_val = queue.pop();
    ret = *ret_val;

    std::cout << "pop  value: " << ret << std::endl;
}

int main(int argn, char * argv[])
{
    only_test_for_api_export();

    ActorBase * actorBase = new ActorBase();
    if (actorBase) {
        IActorContext * context = actorBase->getActorContext();
        if (context) {
            context->release();
            delete context;
        }
        delete actorBase;
    }

    ActorSystem * actorSystem = ActorSystem::create("Factorial N");
    if (actorSystem) {
        std::string systemName = actorSystem->getName();
        printf("Welcome to use TiActor!\n");
        printf("ActorSystem Name: %s.\n", systemName.c_str());
        printf("\n");
        delete actorSystem;
    }

    Pi::main(argn, argv);

    RingQueue_simple_test();

    std::cout << std::endl;
    system("pause");
    return 0;
}
