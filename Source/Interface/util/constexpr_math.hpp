#ifndef CONSTEXPR_MATH_HPP
#    define CONSTEXPR_MATH_HPP

#include "BuildConstraints.hpp"

#    include <cmath>

template<typename T>
constexpr T pi()
{
    return std::atan(static_cast<T>(1)) * static_cast<T>(4);
}

template<typename T>
constexpr T toDegrees(T radians)
{
    return radians / pi<T>() * static_cast<T>(180);
}

template<typename T>
constexpr T toRadians(T degrees)
{
    return degrees * pi<T>() / static_cast<T>(180);
}

namespace detail
{
    long double constexpr DEFAULT_EPSILON = 0.0001L;
}

template<typename T>
constexpr T DEFAULT_EPSILON()
{
    return static_cast<T>(detail::DEFAULT_EPSILON);
}

namespace detail
{
    template<typename T, bool UseEpsilon = std::is_floating_point<T>::value>
    struct GeneralEqualityHelper
    {
        static constexpr bool equals(T arg0, T arg1)
        {
            return arg0 == arg1;
        }
    };
    
    template<typename T>
    struct GeneralEqualityHelper<T, true>
    {
        static constexpr bool equals(T arg0, T arg1)
        {
            return std::abs(arg0 - arg1) < (::DEFAULT_EPSILON<T>());
        }
    };
    
}

template<typename T, bool UseEpsilon = std::is_floating_point<T>::value>
constexpr bool equals(T arg0, T arg1)
{
    return detail::GeneralEqualityHelper<T>::equals(arg0, arg1);
}

#endif