

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include <memory>
#include <vector>
#include <functional>

#include "Pi.h"

#include "TiActor/utils/PowOf2.h"
#include "TiActor/queue/RingQueue.h"

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

    int a, b, c;
    a = b = c = 1;
    const char * text = StringUtils::format(128, "a = %d, b = %d, c = %d.\n", a, b, c);
    std::cout << text << std::endl;

    text = StringUtils::format(128, "c = %d, b = %d, a = %d.\n", c, b, a);
    std::cout << text << std::endl;

    RingQueueBase<uint64_t, 32> queue;
    queue.capacity();

    int isPow2 = TiActor::utils::is_pow_of_2<121>::value;
    std::cout << "isPow2(121) = " << isPow2 << std::endl;

    isPow2 = TiActor::utils::is_pow_of_2<128>::value;
    std::cout << "isPow2(128) = " << isPow2 << std::endl;

    size_t pow2 = TiActor::utils::round_up_to_pow2<33>::value;
    std::cout << "pow2(33) = " << pow2 << std::endl;

    std::cout << std::endl;
    system("pause");
    return 0;
}
