
#ifndef TIACTOR_UTILS_MINMAX_H
#define TIACTOR_UTILS_MINMAX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#define NOMINMAX

#define TI_MIN(x, y)  ((x) <= (y) ? (x) : (y))
#define TI_MAX(x, y)  ((x) >= (y) ? (x) : (y))

namespace TiActor {

namespace math {

template <typename _Ty>
_Ty (min)(_Ty const & x, _Ty const & y) {
    return (x <= y) ? x : y;
}

template <typename _Ty>
_Ty (min2)(_Ty const x, _Ty const y) {
    return (x <= y) ? x : y;
}

template <typename _Ty>
_Ty (max)(_Ty const & x, _Ty const & y) {
    return (x >= y) ? x : y;
}

template <typename _Ty>
_Ty (max2)( _Ty const x,  _Ty const y) {
    return (x >= y) ? x : y;
}

} // namespace math

namespace CompilerTime {

template <typename T, T M, T N>
struct mininum {
    enum { value = ((M <= N) ? M : N) };
};

template <typename T, T M, T N>
struct maxinum {
    enum { value = ((M >= N) ? M : N) };
};

} // namespace CompilerTime

} // namespace TiActor

#endif  /* TIACTOR_UTILS_MINMAX_H */
