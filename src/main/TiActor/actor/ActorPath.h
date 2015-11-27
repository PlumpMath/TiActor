
#ifndef TIACTOR_ACTOR_ACTORPATH_H
#define TIACTOR_ACTOR_ACTORPATH_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>
#include <type_traits>  // for std::move()

namespace TiActor {

class ActorPath {
private:
    std::string path_;

public:
    ActorPath(const std::string & path) {
        path_ = path;
    }

    ~ActorPath() {
    }

    std::string path() const {
        return path_;
    }

    void getPath(std::string & out) const {
        out = path_;
    }

    std::string & getPathRef(std::string & out) const {
        out = std::move(path_);
    }

    std::size_t getLength() const {
        return path_.length();
    }

    const char * toString() const {
        return path_.c_str();
    }
};

class RootActorPath : public ActorPath {
public:
    RootActorPath(std::string path) : ActorPath(path) {
    }

    ~RootActorPath() {
    }
};

}  /* namespace TiActor */

#endif  /* TIACTOR_ACTOR_ACTORPATH_H */
