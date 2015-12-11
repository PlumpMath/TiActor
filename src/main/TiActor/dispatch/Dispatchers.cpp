
#include <string>
#include <unordered_map>

#include "TiActor/dispatch/Dispatchers.h"
#include "TiActor/dispatch/MessageDispatcher.h"
#include "TiActor/dispatch/ThreadPoolDispatcher.h"
#include "TiActor/dispatch/Mailboxes.h"

namespace TiActor {

const char Dispatchers::kDefaultDispatcherName[] = "TiActor.actor.default-dispatcher";
const char Dispatchers::kSynchronizedDispatcheName[] = "TiActor.actor.synchronized-dispatcher";

const char Mailboxes::kDefaultMailboxName[] = "TiActor.actor.default-mailbox";

Dispatchers::~Dispatchers() {
    if (dispatchersMap_) {
        // MessageDispatcher HashMap
        map_iter it = dispatchersMap_->begin();
        for (it = dispatchersMap_->begin(); it != dispatchersMap_->end(); ++it) {
            MessageDispatcher * dispatcher = it->second;
            dispatchersMap_->erase(it);
            it->second = nullptr;
            if (dispatcher) {
                delete dispatcher;
            }
        }
        dispatchersMap_->clear();

        delete dispatchersMap_;
    }
}

MessageDispatcher * Dispatchers::lookup(const std::string & name) {
    MessageDispatcher * dispatcher;
    if (dispatchersMap_) {
        const_map_iter it = dispatchersMap_->find(name);
        if (it != dispatchersMap_->end()) {
            dispatcher = it->second;
            return dispatcher;
        }
        else {
            // Not found
            dispatcher = new ThreadPoolDispatcher(nullptr);
            if (dispatcher)
                dispatchersMap_->insert(std::make_pair(name, dispatcher));
        }
    }
    return nullptr;
}

} // namespace TiActor
