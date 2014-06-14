#include "constexpr_math.hpp"

template<typename T, std::size_t N>
inline T distanceBetween(const midnight::Vector<T, N>& lhs, const midnight::Vector<T, N>& rhs) noexcept
{
    return lhs.distanceFrom(rhs);
}

template<typename T, std::size_t N>
midnight::Vector<T, N> operator-(const midnight::Vector<T, N>& vector) noexcept
{
    midnight::Vector<T, N> rv(vector);
    for(T& t : rv)
    {
        t = -t;
    }
    return rv;
}

template<typename T, std::size_t N>
T angleBetween(const midnight::Vector<T, N>& lhs, const midnight::Vector<T, N>& rhs) noexcept
{

    return std::acos(dot(lhs, rhs) / lhs.length() / rhs.length());
}

template<typename T, std::size_t N>
T dot(const midnight::Vector<T, N>& lhs, const midnight::Vector<T, N>& rhs) noexcept
{
    T rv = 0;
    for(std::size_t i = 0; i < N; ++i)
    {
        rv += (lhs[i] * rhs[i]);
    }
    return rv;
}

template<typename T, std::size_t N>
midnight::Vector<T, N> cross(const midnight::Vector<T, N>& lhs, const midnight::Vector<T, N>& rhs) noexcept
{
    static_assert(N == 3, "Cross products may only be computed with 3-dimensional vectors");

    return midnight::Vector<T, N>(lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}

namespace midnight
{
    
template<typename T, std::size_t N>
inline constexpr Vector<T, N>::Vector() noexcept : Tuple<T, N>()
{

}

template<typename T, std::size_t N>
template<typename ...E>
inline constexpr Vector<T, N>::Vector(T element, E&&... elements) noexcept : Tuple<T, N>(element, static_cast<T>(std::forward<E>(elements))...)
{

}

template<typename T, std::size_t N>
T Vector<T, N>::length() const noexcept
{
    T sum = 0;
    for(const T& element : this->elements)
    {
        sum += (element * element);
    }
    return std::sqrt(sum);
}

template<typename T, std::size_t N>
T Vector<T, N>::lengthSquared() const noexcept
{
    T sum = 0;
    for(const T& element : this->elements)
    {
        sum += (element * element);
    }
    return sum;
}

template<typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::cross(const Vector& rhs) noexcept
{
    static_assert(N == 3, "Cross products may only be computed with 3-dimensional vectors");

    this->set((this->elements[1] * rhs.elements[2]) - (this->elements[2] * rhs.elements[1]),
            (this->elements[2] * rhs.elements[0]) - (this->elements[0] * rhs.elements[2]),
            (this->elements[0] * rhs.elements[1] - this->elements[1] * rhs.elements[0]));
    return *this;
}

template<typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::normalize() noexcept
{
    T length = this->length();
    if((length - 1) > DEFAULT_EPSILON<T>())
    {
        T inverse = 1 / length;
        for(T& element : this->elements)
        {
            element *= inverse;
        }
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Vector<T, N>::set(const std::array<T, N>& elements) noexcept
{
    this->Tuple<T, N>::set(elements);
    return *this;
}

template<typename T, std::size_t N>
template<typename ...E>
Tuple<T, N>& Vector<T, N>::set(T element, E&&...elements) noexcept
{
    this->elements = {
        {element, std::forward<E>(elements)...}
    };
    return *this;
}

template<typename T, std::size_t N>
inline T Vector<T, N>::angleBetween(const Vector& rhs) const noexcept
{
    return std::acos(this->dot(rhs) / length() / rhs.length());
}

}
