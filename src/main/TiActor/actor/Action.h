
#ifndef TIACTOR_ACTOR_ACTION_H
#define TIACTOR_ACTOR_ACTION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>

namespace TiActor {

typedef void(* run_func)(void *);

typedef std::function<void (void)>  action_type;
typedef std::function<void (void)>  run_type;

#define action_type_def(T)  std::function<void (const T &)>
#define action_type_def2(T) std::function<void (T &)>

#define action_type2 template <typename ...Args> std::function<void (Args && ...args)>

class Action {
private:
    //

public:
    Action() {
    }

    Action(const Action & src) {
        cloneActor(src);
    }

    ~Action() {
    }

protected:
    void cloneActor(const Action & src) {
        //
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_ACTION_H */
