#include <cmath>

template<typename T, std::size_t N>
inline T distanceBetween(const midnight::Point<T, N>& lhs, const midnight::Point<T, N>& rhs) noexcept
{
    return lhs.distanceFrom(rhs);
}

template<typename T, std::size_t N>
midnight::Point<T, N> operator-(const midnight::Point<T, N>& point) noexcept
{
    midnight::Point<T, N> rv(point);
    for(T& t : rv)
    {
        t = -t;
    }
    return rv;
}

namespace midnight
{
    
template<typename T, std::size_t N>
Vector<T, N> Point<T, N>::vectorTo(const Point& point) const noexcept
{
    Vector<T, N> rv;
    rv.set(((*this) - point).asArray());
    return rv;
}

template<typename T, std::size_t N>
inline constexpr Point<T, N>::Point() noexcept : Tuple<T, N>()
{

}

template<typename T, std::size_t N>
template<typename ...E>
inline constexpr Point<T, N>::Point(T element, E&&... elements) noexcept : Tuple<T, N>(element, static_cast<T>(std::forward<E>(elements))...)
{

}

template<typename T, std::size_t N>
T Point<T, N>::distanceFrom(const Point<T, N>& rhs) const noexcept
{
    T distance = 0;
    for(std::size_t i = 0; i < N; ++i)
    {
        T difference = this->elements[i] - rhs.elements[i];
        distance += (difference * difference);
    }
    return std::sqrt(distance);
}

}
