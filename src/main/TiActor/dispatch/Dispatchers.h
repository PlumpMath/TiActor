
#ifndef TIACTOR_DISPATCH_DISPATCHERS_H
#define TIACTOR_DISPATCH_DISPATCHERS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <utility>

namespace TiActor {

class ActorSystem;
class MessageDispatcher;

class Dispatchers {
public:
    typedef std::unordered_map<std::string, MessageDispatcher *>                    map_type;
    typedef std::unordered_map<std::string, MessageDispatcher *>::iterator          map_iter;
    typedef std::unordered_map<std::string, MessageDispatcher *>::const_iterator    const_map_iter;
    typedef std::pair<std::string, MessageDispatcher *>                             pair_type;

    static const char kDefaultDispatcherName[];
    static const char kSynchronizedDispatcheName[];

private:
    ActorSystem * system_;
    MessageDispatcher * defaultGlobalDispatcher_;

    map_type * dispatchersMap_;

public:
    Dispatchers(ActorSystem * system)
        : system_(system), defaultGlobalDispatcher_(nullptr) {
        dispatchersMap_ = new map_type();
        defaultGlobalDispatcher_ = this->lookup(kDefaultDispatcherName);
    }

    ~Dispatchers();

    MessageDispatcher * getDefaultGlobalDispatchers() const {
        return defaultGlobalDispatcher_;
    }

    bool hasDispatcher(const std::string & name) {
        if (dispatchersMap_) {
            const_map_iter it = dispatchersMap_->find(name);
            if (it != dispatchersMap_->end()) {
                return true;
            }
        }
        return false;
    }

    bool addDispatcher(const std::string & name, MessageDispatcher * dispatcher) {
        if (dispatchersMap_) {
            pair_type value(name, dispatcher);
            dispatchersMap_->insert(value);
            return true;
        }
        return false;
    }

    MessageDispatcher * lookup(const std::string & name);
};

} // namespace TiActor

#endif  /* TIACTOR_DISPATCH_DISPATCHERS_H */
