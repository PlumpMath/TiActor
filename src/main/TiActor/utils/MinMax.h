
#ifndef TIACTOR_UTILS_MINMAX_H
#define TIACTOR_UTILS_MINMAX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#define NOMINMAX

#define TIACTOR_MIN(x, y)  ((x) <= (y) ? (x) : (y))
#define TIACTOR_MAX(x, y)  ((x) >= (y) ? (x) : (y))

namespace TiActor {

namespace utils {

template <typename _Ty>
_Ty (min)(const _Ty & x, const _Ty & y) {
    return (x <= y) ? x : y;
}

template <typename _Ty>
_Ty min2(const _Ty x, const _Ty y) {
    return (x <= y) ? x : y;
}

template <typename _Ty>
_Ty (max)(const _Ty & x, const _Ty & y) {
    return (x >= y) ? x : y;
}

template <typename _Ty>
_Ty max2(const _Ty x, const _Ty y) {
    return (x >= y) ? x : y;
}

}  /* namespace utils */

}  /* namespace TiActor */

#endif  /* TIACTOR_UTILS_MINMAX_H */
