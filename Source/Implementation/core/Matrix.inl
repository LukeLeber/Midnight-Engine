#include <algorithm>
#include "constexpr_math.hpp"
#include "dynamic_assert.hpp"

/// @internal Implementation details that are of no use to library users are confined to their own namespace.
namespace detail
{

    template<int ...> struct sequence
    {
    };

    template<int N, int ...S> struct sequence_generator : sequence_generator<N - 1, N - 1, S...>
    {
    };

    template<int ...S> struct sequence_generator < 0, S...>
    {
        using type = sequence<S...>;
    };

    template<std::size_t X, std::size_t Y>
    constexpr int get_element(std::size_t pos)
    {
        return pos % Y == pos / Y;
    }

    template <typename T, std::size_t Rows, std::size_t Columns, int ...S>
    constexpr std::array<T, Rows * Columns> get_identity_array(sequence<S...>)
    {
        return std::array<T, Rows * Columns> {{ get_element<Rows, Columns>(S)...}};
    }
    
    template<typename T, std::size_t N, bool UseEpsilon>
    struct EqualityHelper
    {
        static constexpr bool equal(T arg0, T arg1)
        {
            return arg0 == arg1;
        }
    };
    
    template<typename T, std::size_t N>
    struct EqualityHelper<T, N, true>
    {
        static constexpr bool equal(T arg0, T arg1)
        {
            return std::abs(arg0 - arg1) <= ::DEFAULT_EPSILON<T>();
        }
    };
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline bool operator==(const midnight::Matrix<T, Rows, Columns>& lhs, const midnight::Matrix<T, Rows, Columns>& rhs) noexcept
{
    return std::equal(
            lhs.elements.begin(), 
            lhs.elements.end(), 
            rhs.elements.begin(), 
            detail::EqualityHelper<T, Rows * Columns, std::is_floating_point<T>::value>::equal);
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline bool operator!=(const midnight::Matrix<T, Rows, Columns>& lhs, const midnight::Matrix<T, Rows, Columns>& rhs) noexcept
{
    return !std::equal(
            lhs.elements.begin(), 
            lhs.elements.end(), 
            rhs.elements.begin(), 
            detail::EqualityHelper<T, Rows * Columns, std::is_floating_point<T>::value>::equal);
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline std::ostream& operator<<(std::ostream& stream, const midnight::Matrix<T, Rows, Columns>& /*matrix*/)
{
    
    // TODO: Implement
    return stream;
}

template<typename T, std::size_t Rows, std::size_t Columns>
std::istream& operator>>(std::istream& stream, midnight::Matrix<T, Rows, Columns>& /*matrix*/)
{

    // TODO: Implement
    return stream;
}

template<typename T, std::size_t Rows, std::size_t Columns>
midnight::Matrix<T, Rows, Columns> operator-(const midnight::Matrix<T, Rows, Columns>& source) noexcept
{
    midnight::Matrix<T, Rows, Columns> rv(source);
    for(T& element : rv)
    {
        element *= -1;
    }
    return rv;
}
namespace midnight
{

template<typename T, std::size_t Rows, std::size_t Columns>
Matrix<T, Rows, Columns>& Matrix<T, Rows, Columns>::translate(const Vector<T, Rows>& direction)
{
    for(std::size_t i = 1; i < Rows + 1; ++i)
    {
        elements[Columns * i - 1] += direction[i - 1];
    }
    return *this;    
}

template<typename T, std::size_t Rows, std::size_t Columns>
constexpr Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::IDENTITY() noexcept
{
    return Matrix<T, Rows, Columns>{::detail::get_identity_array<T, Rows, Columns>(typename ::detail::sequence_generator<Rows * Columns>::type())};
}

template<typename T, std::size_t Rows, std::size_t Columns>
constexpr Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::ZERO() noexcept
{
    return Matrix{};
}

template<typename T, std::size_t Rows, std::size_t Columns>
constexpr Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::PERSPECTIVE(T fov, T zNear, T zFar) noexcept
{
    return Matrix{static_cast<T>(1) / std::tan(toRadians(fov) / static_cast<T>(2)), 0, 0, 0,
        0, static_cast<T>(1) / tan(toRadians(fov) / static_cast<T>(2)), 0, 0,
        0, 0, (zFar + zNear) / (zNear - zFar), -1.0f,
        0, 0, (2 * zFar * zNear) / (zNear - zFar), 0};
}

template<typename T, std::size_t Rows, std::size_t Columns>
constexpr Matrix<T, Rows, Columns>::Matrix() noexcept : elements
{
    {
        0
    }
}
{

}

template<typename T, std::size_t Rows, std::size_t Columns>
constexpr Matrix<T, Rows, Columns>::Matrix(const std::array<T, Rows * Columns>& values) noexcept : elements(values)
{
    
}

template<typename T, std::size_t Rows, std::size_t Columns>
constexpr Matrix<T, Rows, Columns>::Matrix(std::array<T, Rows * Columns>&& array) noexcept : elements(array)
{
    
}

template<typename T, std::size_t Rows, std::size_t Columns>
template<typename ...E>
constexpr Matrix<T, Rows, Columns>::Matrix(T first, E&&... elements) noexcept : elements
{
    {
        first, std::forward<T>(static_cast<T>(elements))...
    }
}
{
    static_assert(sizeof...(elements) == ((Rows * Columns) - 1), "Incorrect number of elements provided to Matrix");
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::iterator Matrix<T, Rows, Columns>::begin() noexcept
{
    return elements.begin();
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::const_iterator Matrix<T, Rows, Columns>::begin() const noexcept
{
    return elements.begin();
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::iterator Matrix<T, Rows, Columns>::end() noexcept
{
    return elements.end();
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::const_iterator Matrix<T, Rows, Columns>::end() const noexcept
{
    return elements.end();
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::reverse_iterator Matrix<T, Rows, Columns>::rbegin() noexcept
{
    return elements.rbegin();
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::const_reverse_iterator Matrix<T, Rows, Columns>::rbegin() const noexcept
{
    return elements.rbegin();
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::reverse_iterator Matrix<T, Rows, Columns>::rend() noexcept
{
    return elements.rend();
}

template<typename T, std::size_t Rows, std::size_t Columns>
inline typename Matrix<T, Rows, Columns>::const_reverse_iterator Matrix<T, Rows, Columns>::rend() const noexcept
{
    return elements.rend();
}

template<typename T, std::size_t Rows, std::size_t Columns>
const T& Matrix<T, Rows, Columns>::operator()(std::size_t row, std::size_t column) const noexcept
{
    dynamic_assert(row >= 0 && row < Rows, "access violation (row index " << row << " out of range [" << Rows << "])");
    dynamic_assert(column >= 0 && column < Columns, "access violation (column " << column << " out of range [" << Columns << "])");
    return elements[column * Rows + row];
}

template<typename T, std::size_t Rows, std::size_t Columns>
T& Matrix<T, Rows, Columns>::operator()(std::size_t row, std::size_t column) noexcept
{
    dynamic_assert(row >= 0 && row < Rows, 
                   "access violation (row index " << row << " out of range [" << Rows << "])");
    dynamic_assert(column >= 0 && column < Columns, 
                   "access violation (column " << column << " out of range [" << Columns << "])");
    return elements[column * Rows + row];
}

template<typename T, std::size_t Rows, std::size_t Columns>
template<typename ...E>
void Matrix<T, Rows, Columns>::set(E&&... elements) noexcept
{
    static_assert(sizeof...(elements) == (Rows * Columns), "Incorrect number of elements provided to Matrix");
    this->elements = {{ static_cast<T>(std::forward<E>(elements))... }};
}

template<typename T, std::size_t Rows, std::size_t Columns>
const T* Matrix<T, Rows, Columns>::operator&() const
{
    return &elements[0];
}

}