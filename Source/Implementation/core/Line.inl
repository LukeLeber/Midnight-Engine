#include "constexpr_math.hpp"
#include "IllegalArgumentException.hpp"
#include "Vector.hpp"

template<typename T, std::size_t N>
inline std::ostream& operator<<(std::ostream& stream, const midnight::Line<T, N>& line)
{
    return stream << line.point << line.vector;
}

template<typename T, std::size_t N>
inline std::istream& operator>>(std::istream& stream, midnight::Line<T, N>& line)
{
    return stream >> line.point >> line.vector;
}

template<typename T, std::size_t N>
/*inline?*/ bool operator==(const midnight::Line<T, N>& /*lhs*/, const midnight::Line<T, N>& /*rhs*/) noexcept
{
    return false; // TODO: Consult with linear algebra expert...
}

template<typename T, std::size_t N>
/*inline?*/ bool operator!=(const midnight::Line<T, N>& /*lhs*/, const midnight::Line<T, N>& /*rhs*/) noexcept
{
    return false; // TODO: Consult with linear algebra expert...
}

namespace midnight
{

template<typename T, std::size_t N>
Line<T, N>::Line(const Point<T, N>& point, const Vector<T, N>& vector) :
    point(point),
    vector(vector)
{
    if(this->vector.length() < DEFAULT_EPSILON<T>())
    {
        throw IllegalArgumentException("The provided vector must not be the zero vector");
    }
}

template<typename T, std::size_t N>
Line<T, N>::Line(const Point<T, N>& start, const Point<T, N>& end) :
    point(start),
    vector(start.vectorTo(end))
{
    if(start == end)
    {
        throw IllegalArgumentException("The provided points must not be identical");
    }
}

template<typename T, std::size_t N>
Line<T, N>::Line(Point<T, N>&& point, Vector<T, N>&& vector) :
    point(std::move(point)),
    vector(std::move(vector))
{
    if(this->vector.length() < DEFAULT_EPSILON<T>())
    {
        point = std::move(this->point);
        vector = std::move(this->vector);
        throw IllegalArgumentException("The provided vector must not be the zero vector");
    }
}

template<typename T, std::size_t N>
Line<T, N>::Line(Point<T, N>&& start, Point<T, N>&& end) :
    point(std::move(start)),
    vector(start.vectorTo(end))
{
    if(start == end)
    {
        start = std::move(this->point);
        throw IllegalArgumentException("The provided points must not be identical");
    }
}

template<typename T, std::size_t N>
inline Line<T, N>::Line(const Line& rhs) noexcept :
    point(rhs.point),
    vector(rhs.vector)
{

}

template<typename T, std::size_t N>
inline Line<T, N>::Line(Line<T, N>&& rhs) noexcept :
    point(std::move(rhs.point)),
    vector(std::move(rhs.vector))
{

}

template<typename T, std::size_t N>
Line<T, N>& Line<T, N>::operator=(const Line<T, N>& rhs) noexcept
{
    if(this != &rhs)
    {
        this->point = rhs.point;
        this->vector = rhs.vector;
    }
    return *this;
}

template<typename T, std::size_t N>
Line<T, N>&Line<T, N>::operator=(Line&& rhs) noexcept
{
    if(this != &rhs)
    {
        this->point = std::move(rhs.point);
        this->vector = std::move(rhs.vector);
    }
    return *this;
}

template<typename T, std::size_t N>
inline const Point<T, N>& Line<T, N>::getPoint() const noexcept
{
    return point;
}

template<typename T, std::size_t N>
inline Point<T, N>& Line<T, N>::getPoint() noexcept
{
    return point;
}

template<typename T, std::size_t N>
inline const Vector<T, N>& Line<T, N>::getVector() const noexcept
{
    return vector;
}

template<typename T, std::size_t N>
inline Vector<T, N>& Line<T, N>::getVector() noexcept
{
    return vector;
}

namespace detail
{
    /// @internal
    /// A helper template class that allows us to utilize different 
    /// partial-specializations to handle integral and floating point 
    /// arithmetic differently
    ///
    /// TODO: Check with linear algebra expert to confirm the code works!
    template<typename T, std::size_t N, bool IsFloatingPoint>
    struct IntersectHelper
    {

        static inline bool intersects(const Line<T, N>& line0, const Line<T, N>& line1)
        {
            return std::abs(cross(line0.getVector(), 
                    line1.getVector()).dot(line0.getPoint() - line1.getPoint())) == 0;
        }
    };

    /// Use an epsilon value for floating-point calculations
    template<typename T, std::size_t N>
    struct IntersectHelper<T, N, true>
    {

        static inline bool intersects(const Line<T, N>& line0, const Line<T, N>& line1)
        {
            return std::abs(::cross(line0.getVector(), 
                    line1.getVector()).dot(line0.getPoint() - line1.getPoint())) <= DEFAULT_EPSILON<T>();
        }
    };
}

template<typename T, std::size_t N>
inline bool Line<T, N>::intersectsWith(const Line& line) const noexcept
{
    return detail::IntersectHelper<T, N, std::is_floating_point<T>::value>::intersects(*this, line);
}

}