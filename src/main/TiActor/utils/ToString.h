
#ifndef TIACTOR_UTILS_TOSTRING_H
#define TIACTOR_UTILS_TOSTRING_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

//
// See: http://stackoverflow.com/questions/24975147/check-if-class-has-function-with-signature
//

#undef  MEMBERFUNCTION_CHECKER_DECLEAR
#define MEMBERFUNCTION_CHECKER_DECLEAR(RETURN_TYPE, METHOD_NAME, PARAMETERS)    \
template <typename T>                                                           \
class MemberFunction ## METHOD_NAME ## IsExists                                 \
{                                                                               \
private:                                                                        \
    typedef char true_type;                                                     \
    typedef char (&false_type)[2];                                              \
                                                                                \
    template <typename U, RETURN_TYPE (U::*)PARAMETERS = &U::METHOD_NAME>       \
    struct checker {                                                            \
        typedef true_type type;                                                 \
    };                                                                          \
                                                                                \
    template <typename U>                                                       \
    static typename checker<U>::type tester(const U *);                         \
                                                                                \
    static false_type tester(...);                                              \
                                                                                \
public:                                                                         \
    enum { value = (sizeof(tester(static_cast<const T *>(0))) == sizeof(true_type)) }; \
}

#ifndef MemberFunctionIsExists
#define MemberFunctionIsExists(T, FuncName)    \
    detail::MemberFunction##FuncName##IsExists<T>::value
#endif

namespace TiActor {

//
// See: http://blog.chinaunix.net/uid-1720597-id-306773.html
//

namespace detail {

// MemberFunctiontoStringIsExists<T>::value, std::string toString(void) const
MEMBERFUNCTION_CHECKER_DECLEAR(std::string, toString, (void) const);

template<typename T>
struct HasToStringMemberFunction {
    template<typename U, std::string(U::*)() const>
    struct matcher;

    template<typename U>
    static char helper(matcher<U, &U::toString> *);

    template<typename U>
    static int helper(...);

    enum { value = (sizeof(helper<T>(nullptr)) == sizeof(char)) };
};

template <bool HasMemberFunction>
struct ToStringWrapper {};

template<>
struct ToStringWrapper<true> {
    template<typename T>
    static std::string toString(T const & x) {
        return x.toString();
    }
};

template<>
struct ToStringWrapper<false> {
    template<typename T>
    static std::string toString(T const & x) {
        return std::string(typeid(x).name());
    }
};

} // namespace detail */

namespace StringUtils {

template<typename T>
std::string toString(T const & x) {
    return detail::ToStringWrapper<MemberFunctionIsExists(T, toString)>::toString(x);
}

template<typename T>
std::string toString2(T const & x) {
    return detail::ToStringWrapper<detail::HasToStringMemberFunction<T>::value>::toString(x);
}

} // namespace StringUtils

} // namespace TiActor

#endif  /* TIACTOR_UTILS_TOSTRING_H */
