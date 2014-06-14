#ifndef VECTOR_1_22_2014_HPP
#    define VECTOR_1_22_2014_HPP

#include "BuildConstraints.hpp"

#    include "Tuple.hpp"

namespace midnight
{

template<typename T, std::size_t N>
class Vector;

}

template<typename T, std::size_t N>
T angleBetween(const midnight::Vector<T, N>& lhs, const midnight::Vector<T, N>& rhs) noexcept;

template<typename T, std::size_t N>
T dot(const midnight::Vector<T, N>& lhs, const midnight::Vector<T, N>& rhs) noexcept;

template<typename T, std::size_t N>
midnight::Vector<T, N> cross(const midnight::Vector<T, N>& lhs, const midnight::Vector<T, N>& rhs) noexcept;

/**
 * Computes a negated version of the provided vector in which each of the 
 * elements is the unary negation of the original
 * 
 * @param vector the vector to negate
 * 
 * @return a negated version of the provided vector
 */
template<typename T, std::size_t N>
midnight::Vector<T, N> operator-(const midnight::Vector<T, N>& vector) noexcept;

namespace midnight
{

/**
 * A specialized Tuple that represents a vector.  In addition to the base 
 * operations, TODO
 * 
 * Several common vectors are also defined in the following format:
 * 
 * Vector {number of elements} {type abbreviation}
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
 * example: Vector3F - A vector in 3 dimensional space that uses float units
 * 
 * User-defined vectors are expected to follow the aforementioned format.
 * 
 * @tparam T the type of the elements that are stored in this vector
 * 
 * @tparam N the number of elements that are stored in this vector
 * 
 * TODO: incomplete vector
 */
template<typename T, std::size_t N>
class Vector : public Tuple<T, N>
{
  public:

    /**
     * Default constructor - all elements of this Vector are zero-initialized
     * 
     * <pre>
     * /// Elements = {0.0f, 0.0f, 0.0f}
     * Vector3F example;
     * </pre>
     * 
     */
    constexpr Vector() noexcept;

    /**
     * Constructs a Vector from the provided elements
     * 
     * @param element the first element
     * 
     * @param elements the remaining elements to fill this Vector with
     * 
     * <pre>
     * /// Elements = {1.0f, 2.0f, 3.0f}
     * Vector3F example(1.0f, 2.0f, 3.0f);
     * </pre>
     * 
     */
    template<typename ...E>
    constexpr explicit Vector(T element, E&&... elements) noexcept;

    /**
     * Copy constructor
     * 
     * @param rhs the Vector to copy
     * 
     */
    Vector(const Vector& rhs) noexcept = default;

    Vector(const Tuple<T, N> rhs) : 
        Tuple<T, N>(rhs)
    {
        
    }
    
    /**
     * Move constructor
     * 
     * @param rhs the Vector to move
     * 
     */
    Vector(Vector&& rhs) noexcept = default;

    /**
     * Assignment
     * 
     * @param rhs the Vector to assign
     * 
     * @return *this
     * 
     */
    Vector& operator=(const Vector& rhs) noexcept = default;

    /**
     * Calculates the angle between this vector and the provided vector
     * 
     * @param rhs the other vector
     * 
     * @return the angle between this vector and the provided vector
     * 
     */
    T angleBetween(const Vector& rhs) const noexcept;

    /**
     * Calculates the length of this vector
     * 
     * @return the length of this vector
     * 
     */
    T length() const noexcept;

    /**
     * Calculates the squared length of this vector
     * 
     * @return the length of this vector
     * 
     */
    T lengthSquared() const noexcept;

    /**
     * Performs an in-place cross product of this vector and the provided one
     * 
     * @param rhs the vector to cross with this one
     * 
     * @return *this
     */
    Vector& cross(const Vector& rhs) noexcept;

    /**
     * Normalizes this vector in place
     * 
     * @return *this
     * 
     */
    Vector& normalize() noexcept;

    Tuple<T, N>& set(const std::array<T, N>& elements) noexcept;

    template<typename ...E>
    Tuple<T, N>& set(T element, E&&... remaining) noexcept;

    virtual ~Vector() = default;
};

}

#    include "Vector.inl"

namespace midnight
{

typedef Vector<double, 2> Vector2D;
typedef Vector<double, 3> Vector3D;
typedef Vector<double, 4> Vector4D;

typedef Vector<float, 2> Vector2F;
typedef Vector<float, 3> Vector3F;
typedef Vector<float, 4> Vector4F;

typedef Vector<int64_t, 2> Vector2L;
typedef Vector<int64_t, 3> Vector3L;
typedef Vector<int64_t, 4> Vector4L;

// TODO: Other types..

}

#endif
