#include <iterator>

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const midnight::Tuple<T, N>& tuple)
{
    std::copy(tuple.begin(), tuple.end(), std::ostream_iterator<T>(stream));
    return stream;
}

template<typename T, std::size_t N>
std::istream& operator>>(std::istream& stream, midnight::Tuple<T, N>& tuple)
{
    for(typename midnight::Tuple<T, N>::iterator iter = tuple.begin(); iter != tuple.end(); ++iter)
    {
        stream >> *iter;
    }
    return stream;
}

template<typename T, std::size_t N>
midnight::Tuple<T, N> operator-(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    midnight::Tuple<T, N> rv(lhs);
    rv -= rhs;
    return rv;
}

template<typename T, std::size_t N>
inline bool operator==(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    return lhs.elements == rhs.elements;
}

template<typename T, std::size_t N>
inline bool operator!=(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    return lhs.elements != rhs.elements;
}

template<typename T, std::size_t N>
inline bool operator<(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    return lhs.elements < rhs.elements;
}

template<typename T, std::size_t N>
inline bool operator<=(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    return lhs.elements <= rhs.elements;
}

template<typename T, std::size_t N>
inline bool operator>(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    return lhs.elements > rhs.elements;
}

template<typename T, std::size_t N>
inline bool operator>=(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    return lhs.elements >= rhs.elements;
}

template<typename T, std::size_t N>
midnight::Tuple<T, N> operator-(const midnight::Tuple<T, N>& tuple) noexcept
{
    midnight::Tuple<T, N> rv(tuple);
    for(T& t : rv)
    {
        t = -t;
    }
    return rv;
}

template <size_t I, class T, size_t N>
inline constexpr T& get(midnight::Tuple<T, N>& tuple) noexcept
{
    return tuple[I];
}

template <size_t I, class T, size_t N>
inline constexpr T&& get(midnight::Tuple<T, N>&& tuple) noexcept
{
    return std::move(tuple[I]);
}

template <size_t I, class T, size_t N>
inline constexpr T get(const midnight::Tuple<T, N>& tuple) noexcept
{
    return tuple[I];
}

template<typename T, std::size_t N>
midnight::Tuple<T, N> operator*(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    midnight::Tuple<T, N> rv(lhs);
    rv *= rhs;
    return rv;
}

template<typename T, std::size_t N>
midnight::Tuple<T, N> operator*(const midnight::Tuple<T, N>& tuple, T scalar) noexcept
{
    midnight::Tuple<T, N> rv(tuple);
    tuple *= scalar;
    return rv;
}

template<typename T, std::size_t N>
midnight::Tuple<T, N> operator+(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept
{
    midnight::Tuple<T, N> rv(lhs);
    rv += rhs;
    return rv;
}

namespace midnight
{
    
template<typename T, std::size_t N>
inline constexpr Tuple<T, N>::Tuple() noexcept : elements
{
}
{

}

template<typename T, std::size_t N>
inline Tuple<T, N>::Tuple(const std::initializer_list<T> elements)
{
    std::copy(elements.begin(), elements.end(), this->elements.begin());
}

template<typename T, std::size_t N>
template<typename ...E>
inline constexpr Tuple<T, N>::Tuple(T element, E&&...elements) noexcept : elements
{
    {
        element, static_cast<T>(std::forward<E>(elements))...
    }
}
{
    static_assert(sizeof...(E) == (N - 1), "Incorrect number of elements provided to constructor");
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::iterator Tuple<T, N>::begin() noexcept
{
    return elements.begin();
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::const_iterator Tuple<T, N>::begin() const noexcept
{
    return elements.begin();
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::iterator Tuple<T, N>::end() noexcept
{
    return elements.end();
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::const_iterator Tuple<T, N>::end() const noexcept
{
    return elements.end();
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::reverse_iterator Tuple<T, N>::rbegin() noexcept
{
    return elements.rbegin();
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::const_reverse_iterator Tuple<T, N>::rbegin() const noexcept
{
    return elements.rbegin();
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::reverse_iterator Tuple<T, N>::rend() noexcept
{
    return elements.rend();
}

template<typename T, std::size_t N>
inline typename Tuple<T, N>::const_reverse_iterator Tuple<T, N>::rend() const noexcept
{
    return elements.rend();
}

template<typename T, std::size_t N>
inline constexpr typename Tuple<T, N>::size_type Tuple<T, N>::size() const noexcept
{
    return N;
}

template<typename T, std::size_t N>
inline constexpr T Tuple<T, N>::operator[](Tuple<T, N>::size_type index) const noexcept
{
    return elements[index];
}

template<typename T, std::size_t N>
inline T& Tuple<T, N>::operator[](Tuple<T, N>::size_type index) noexcept
{
    return elements[index];
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::operator*=(T scalar)noexcept
{
    for(Tuple<T, N>::size_type i = 0; i < N; ++i)
    {
        elements[i] *= scalar;
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::operator*=(const Tuple<T, N>& rhs) noexcept
{
    for(Tuple<T, N>::size_type i = 0; i < N; ++i)
    {
        elements[i] *= rhs.elements[i];
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::operator+=(T scalar)noexcept
{
    for(Tuple<T, N>::size_type i = 0; i < N; ++i)
    {
        elements[i] += scalar;
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::operator+=(const Tuple<T, N>& rhs) noexcept
{
    for(Tuple<T, N>::size_type i = 0; i < N; ++i)
    {
        elements[i] += rhs.elements[i];
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::operator-=(T scalar)noexcept
{
    for(Tuple<T, N>::size_type i = 0; i < N; ++i)
    {
        elements[i] -= scalar;
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::operator-=(const Tuple<T, N>& rhs) noexcept
{
    for(std::size_t i = 0; i < N; ++i)
    {
        elements[i] -= rhs.elements[i];
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::clampMin(T min) noexcept
{
    for(T& element : elements)
    {
        if(element < min)
        {
            element = min;
        }
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::clamp(T min, T max) noexcept
{
    for(T& element : elements)
    {
        if(element < min)
        {
            element = min;
        }
        else if(element > max)
        {
            element = max;
        }
    }
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::clampMax(T max) noexcept
{
    for(T& element : elements)
    {
        if(element > max)
        {
            element = max;
        }
    }
    return *this;
}

template<typename T, std::size_t N>
T Tuple<T, N>::dot(const Tuple<T, N>& rhs) const noexcept
{
    T rv = 0;
    for(std::size_t i = 0; i < N; ++i)
    {
        rv += (this->elements[i] * rhs.elements[i]);
    }
    return rv;
}

template<typename T, std::size_t N>
template<typename ...E>
Tuple<T, N>& Tuple<T, N>::set(T element, E&&...elements) noexcept
{
    this->elements = {
        {element, std::forward<E>(elements)...}
    };
    return *this;
}

template<typename T, std::size_t N>
Tuple<T, N>& Tuple<T, N>::set(const std::array<T, N>& elements) noexcept
{
    this->elements = elements;
    return *this;
}

template<typename T, std::size_t N>
const std::array<T, N> Tuple<T, N>::asArray() const
{
    return elements;
}

}
