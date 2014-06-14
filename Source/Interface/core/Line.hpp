/**
 * This file is protected under the KILLGPL License.
 * 
 * For more information visit www.midnightengine.com/license
 *  
 * @version 1.1
 *      2/04/2014 - initial draft
 *      3/27/2014 - API & Documentation Enhancement
 * 
 * @since 1.0
 * 
 * @author Luke A. Leber <LukeLeber@gmail.com>
 * 
 */
#ifndef LINE_2_04_2014_HPP
#define LINE_2_04_2014_HPP

#include "BuildConstraints.hpp"

#include <cstdint>
#include <iostream>

#include "Point.hpp"
#include "Vector.hpp"

namespace midnight
{

template<typename T, std::size_t N>
class Line;

}

/**
 * Inserts the provided Line into the provided output stream
 * 
 * @param stream the stream to insert the provided Line into
 * 
 * @param line the line to insert
 * 
 * @return the provided output stream
 * 
 */
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const midnight::Line<T, N>& line);

/**
 * Extracts a Line from the provided input stream
 * 
 * @param stream the stream to extract from
 * 
 * @param line the Line to populate with the read data
 * 
 * @return the provided input stream
 * 
 */
template<typename T, std::size_t N>
std::istream& operator>>(std::istream& stream, midnight::Line<T, N>& line);

/**
 * Equality operator for two Lines.  Returns true if and only if the 
 * two lines have the same vector and are located at the same offset from the 
 * origin.
 * 
 * @param lhs the first Line to compare
 * 
 * @param rhs the second Line to compare
 * 
 * @return true if the two Lines are equal, otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator==(const midnight::Line<T, N>& lhs, const midnight::Line<T, N>& rhs) noexcept;

/**
 * Inequality operator for two Lines.  Returns true if the 
 * two lines have differing vectors or are located at differing offsets from the 
 * origin.
 * 
 * @param lhs the first Line to compare
 * 
 * @param rhs the second Line to compare
 * 
 * @return true if the two Lines are equal, otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator!=(const midnight::Line<T, N>& lhs, const midnight::Line<T, N>& rhs) noexcept;

namespace midnight
{

/**
 * A general purpose representation of a line in N-dimensional space
 * 
 * @tparam T the type of numeric data that represents this Line
 * 
 * @tparam N the dimensionality of the space that this Line exists in
 * 
 */
template<typename T, std::size_t N>
class Line
{
    static_assert(N > 1, "Lines may only exist in dimensionalities above 2");
    
    friend std::ostream& operator<<<>(std::ostream&, const Line<T, N>&);
    friend std::istream& operator>><>(std::istream&, Line<T, N>&);
    friend bool operator==<>(const Line<T, N>&, const Line<T, N>&) noexcept;
    friend bool operator!=<>(const Line<T, N>&, const Line<T, N>&) noexcept;

    /// An arbitrary Point on this Line
    Point<T, N> point;

    /// The Vector representing the direction of this Line
    Vector<T, N> vector;

  public:

    /**
     * Constructs a Line with the provided arbitrary Point and Vector
     * 
     * @param point an arbitrary Point on the Line
     * 
     * @param vector the direction of the Line
     * 
     * @throws IllegalArgumentException if the provided Vector is the zero vector
     * 
     */
    Line(const Point<T, N>& point, const Vector<T, N>& vector);

    /**
     * Constructs a Line with the two provided arbitrary Points by drawing a 
     * Vector between them
     * 
     * @param start the first Point on the Line
     * 
     * @param end the second Point on the Line
     * 
     * @throws IllegalArgumentException if the provided Points are equal
     * 
     */
    Line(const Point<T, N>& start, const Point<T, N>& end);

    /**
     * Constructs a Line with the provided arbitrary Point and Vector
     * 
     * @param point an arbitrary Point on the Line
     * 
     * @param vector the direction of the Line
     * 
     * @throws IllegalArgumentException if the provided Vector is the zero vector
     * 
     */
    Line(Point<T, N>&& point, Vector<T, N>&& vector);

    /**
     * Constructs a Line with the two provided arbitrary Points by drawing a 
     * Vector between them
     * 
     * @param start the first Point on the Line
     * 
     * @param end the second Point on the Line
     * 
     * @throws IllegalArgumentException if the provided Points are equal
     * 
     */
    Line(Point<T, N>&& start, Point<T, N>&& end);

    /**
     * Copy-constructs a Line with the provided Line
     * 
     * @param rhs the Line to copy
     * 
     */
    Line(const Line& rhs) noexcept;

    /**
     * Move-constructs a Line from the provided Line
     * 
     * @param rhs the Line to move
     * 
     */
    Line(Line&& rhs) noexcept;

    /**
     * Copy-assigns the provided Line to this one
     * 
     * @param rhs the Line to copy
     * 
     * @return *this
     * 
     */
    Line& operator=(const Line& rhs) noexcept;

    /**
     * Move-assigns the provided Line to this one
     * 
     * @param rhs the Line to move
     * 
     * @return *this
     * 
     */
    Line& operator=(Line&& rhs) noexcept;

    /**
     * Retrieves an arbitrary Point on this Line
     * 
     * @return an arbitrary Point on this Line
     * 
     */
    const Point<T, N>& getPoint() const noexcept;

    /**
     * Retrieves an arbitrary Point on this Line
     * 
     * @return an arbitrary Point on this Line
     * 
     */
    Point<T, N>& getPoint() noexcept;

    /**
     * Retrieves the Vector of this Line
     * 
     * @return the Vector of this Line
     * 
     */
    const Vector<T, N>& getVector() const noexcept;

    /**
     * Retrieves the Vector of this Line
     * 
     * @return the Vector of this Line
     * 
     */
    Vector<T, N>& getVector() noexcept;

    /**
     * Does this Line intersect with the provided Line?
     * 
     * @param line the other Line to test
     * 
     * @return true if and only if the two lines intersect, otherwise false
     * 
     */
    bool intersectsWith(const Line& line) const noexcept;

    /**
     * Default Destructor
     * 
     */
    ~Line() = default;
};

}

#include "Line.inl"

namespace midnight
{

typedef Line<float, 2> Line2F;
typedef Line<float, 3> Line3F;

typedef Line<double, 2> Line2D;
typedef Line<double, 3> Line3D;

}

#endif
