#ifndef POINT_1_22_2014_HPP
#    define POINT_1_22_2014_HPP

#include "BuildConstraints.hpp"

#    include "Tuple.hpp"
#    include "Vector.hpp"

namespace midnight
{

template<typename T, std::size_t N>
class Point;

}

/**
 * Calculates the linear distance between the provided Point and this one
 * 
 * @param rhs the Point to measure from
 * 
 * @return the linear distance between the provided point and this one
 * 
 */
template<typename T, std::size_t N>
T distanceBetween(const midnight::Point<T, N>& lhs, const midnight::Point<T, N>& rhs) noexcept;

/**
 * Computes a negated version of the provided point in which each of the 
 * elements is the unary negation of the original
 * 
 * @param point the point to negate
 * 
 * @return a negated version of the provided point
 */
template<typename T, std::size_t N>
midnight::Point<T, N> operator-(const midnight::Point<T, N>& point) noexcept;

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const midnight::Point<T, N>& point)
{
    std::copy(point.begin(), point.end(), std::ostream_iterator<T>(stream));
    return stream;
}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, midnight::Point<T, N>&& point);

template<typename T, std::size_t N>
std::istream& operator>>(std::istream& stream, midnight::Point<T, N>& point);

namespace midnight
{

/**
 * A specialized Tuple that represents a point.  In addition to the base 
 * operations, distance between points may also be calculated.
 * 
 * Several common points are also defined in the following format:
 * 
 * Point {number of elements} {type abbreviation}
 * 
 * where the predefined type abbreviations are:
 * type		-	abbreviation
 * --------------------------
 * double 	-	D
 * float		-	F
 * int64_t	-	L
 * uint64_t	-	UL
 * int32_t	-	I
 * uint32_t	-	UI
 * int16_t	-	S
 * uint16_t	-	US
 * int8_t	-	C
 * uint8_t	-	UC
 * 
 * example: Point3F - A point in 3 dimensional space that uses float units
 * 
 * User-defined points are expected to follow the aforementioned format.
 * 
 * @tparam T the type of the elements that are stored in this point
 * 
 * @tparam N the number of elements that are stored in this point
 * 
 */
template<typename T, std::size_t N>
class Point : public Tuple<T, N>
{
    friend T distanceBetween <>(const Point<T, N>& lhs, const Point<T, N>& rhs) noexcept;

  public:

    /**
     * Default constructor - all elements of this Point are zero-initialized
     * 
     * <pre>
     * /// Elements = {0.0f, 0.0f, 0.0f}
     * Point3F example;
     * </pre>
     * 
     */
    constexpr Point() noexcept;

    /**
     * Constructs a Point from the provided elements
     * 
     * @param element the first element to fill this Point with
     * 
     * @param elements the rest of the elements to fill this Point with
     * 
     * <pre>
     * /// Elements = {1.0f, 2.0f, 3.0f}
     * Point3F example(1.0f, 2.0f, 3.0f);
     * </pre>
     * 
     */
    template<typename ...E>
    constexpr explicit Point(T element, E&&...elements) noexcept;

    /**
     * Copy constructor
     * 
     * @param rhs the Point to copy
     * 
     */
    Point(const Point& rhs) noexcept = default;

    /**
     * Move constructor
     * 
     * @param rhs the Point to move
     * 
     */
    Point(Point&& rhs) noexcept = default;

    /**
     * Assignment
     * 
     * @param rhs the Point to assign
     * 
     * @return *this
     * 
     */
    Point& operator=(const Point& rhs) noexcept = default;

    /**
     * Calculates the linear distance between the provided Point and this one
     * 
     * @param rhs the Point to measure from
     * 
     * @return the linear distance between the provided point and this one
     * 
     */
    T distanceFrom(const Point& rhs) const noexcept;

    /**
     * Generates a vector between this point and the provided point
     * 
     * @param point the point to generate a vector to
     * 
     * @return a vector between this point and the provided point
     * 
     */
    Vector<T, N> vectorTo(const Point& point) const noexcept;

    virtual ~Point() noexcept = default;
};

}

#    include "Point.inl"

namespace midnight
{
    
typedef Point<double, 1> Point1D; /** A point that holds 1 double */
typedef Point<double, 2> Point2D; /** A point that holds 2 doubles */
typedef Point<double, 3> Point3D; /** A point that holds 3 doubles */
typedef Point<double, 4> Point4D; /** A point that holds 4 doubles */

typedef Point<float, 1> Point1F; /** A point that holds 1 float */
typedef Point<float, 2> Point2F; /** A point that holds 2 floats */
typedef Point<float, 3> Point3F; /** A point that holds 3 floats */
typedef Point<float, 4> Point4F; /** A point that holds 4 floats */

typedef Point<int64_t, 1> Point1L; /** A point that holds 1 signed long */
typedef Point<int64_t, 2> Point2L; /** A point that holds 2 signed longs */
typedef Point<int64_t, 3> Point3L; /** A point that holds 3 signed longs */
typedef Point<int64_t, 4> Point4L; /** A point that holds 4 signed longs */

typedef Point<uint64_t, 1> Point1UL; /** A point that holds 1 unsigned long */
typedef Point<uint64_t, 2> Point2UL; /** A point that holds 2 unsigned longs */
typedef Point<uint64_t, 3> Point3UL; /** A point that holds 3 unsigned longs */
typedef Point<uint64_t, 4> Point4UL; /** A point that holds 4 unsigned longs */

typedef Point<int32_t, 1> Point1I; /** A point that holds 1 signed int */
typedef Point<int32_t, 2> Point2I; /** A point that holds 2 signed ints */
typedef Point<int32_t, 3> Point3I; /** A point that holds 3 signed ints */
typedef Point<int32_t, 4> Point4I; /** A point that holds 4 signed ints */

typedef Point<uint32_t, 1> Point1UI; /** A point that holds 1 unsigned int */
typedef Point<uint32_t, 2> Point2UI; /** A point that holds 2 unsigned ints */
typedef Point<uint32_t, 3> Point3UI; /** A point that holds 3 unsigned ints */
typedef Point<uint32_t, 4> Point4UI; /** A point that holds 4 unsigned ints */

typedef Point<int16_t, 1> Point1S; /** A point that holds 1 signed short */
typedef Point<int16_t, 2> Point2S; /** A point that holds 2 signed shorts */
typedef Point<int16_t, 3> Point3S; /** A point that holds 3 signed shorts */
typedef Point<int16_t, 4> Point4S; /** A point that holds 4 signed shorts */

typedef Point<uint16_t, 1> Point1US; /** A point that holds 1 unsigned short */
typedef Point<uint16_t, 2> Point2US; /** A point that holds 2 unsigned shorts */
typedef Point<uint16_t, 3> Point3US; /** A point that holds 3 unsigned shorts */
typedef Point<uint16_t, 4> Point4US; /** A point that holds 4 unsigned shorts */

typedef Point<int8_t, 1> Point1C; /** A point that holds 1 signed char */
typedef Point<int8_t, 2> Point2C; /** A point that holds 2 signed chars */
typedef Point<int8_t, 3> Point3C; /** A point that holds 3 signed chars */
typedef Point<int8_t, 4> Point4C; /** A point that holds 4 signed chars */

typedef Point<uint8_t, 1> Point1UC; /** A point that holds 1 unsigned char */
typedef Point<uint8_t, 2> Point2UC; /** A point that holds 2 unsigned chars */
typedef Point<uint8_t, 3> Point3UC; /** A point that holds 3 unsigned chars */
typedef Point<uint8_t, 4> Point4UC; /** A point that holds 4 unsigned chars */

}

#endif