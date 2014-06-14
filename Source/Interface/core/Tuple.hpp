#ifndef TUPLE_1_21_2014_HPP
#    define TUPLE_1_21_2014_HPP

#    include "BuildConstraints.hpp"

#    include <array>            // std::array
#    include <cstdint>          // std::size_t
#    include <initializer_list> // std::initializer_list
#    include <iostream>         // std::istream, std::ostream


namespace midnight
{

template<typename T, std::size_t N>
class Tuple;

}

/**
 * Inserts the provided tuple into the provided output stream
 * 
 * @param stream the output stream to write the provided tuple to
 * 
 * @param tuple the tuple to write
 * 
 * @return the provided output stream
 * 
 */
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const midnight::Tuple<T, N>& tuple);

/**
 * Extracts a Tuple from the provided input stream
 * 
 * @param stream the stream to read from
 * 
 * @param tuple the Tuple to write into
 * 
 * @return the provided input stream
 * 
 */
template<typename T, std::size_t N>
std::istream& operator>>(std::istream& stream, midnight::Tuple<T, N>& tuple);

/**
 * Performs a component-wise comparison between the two provided tuples
 * 
 * @param lhs the first tuple to compare
 * 
 * @param rhs the second tuple to compare
 * 
 * @return true if the two tuples are equal, otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator==(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Performs a component-wise comparison between the two provided tuples
 * 
 * @param lhs the first tuple to compare
 * 
 * @param rhs the second tuple to compare
 * 
 * @return true if the two tuples are not equal, otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator!=(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Performs a component-wise comparison between the two provided tuples
 * 
 * @param lhs the first tuple to compare
 * 
 * @param rhs the second tuple to compare
 * 
 * @return true if the first tuple is less than the second, otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator<(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Performs a component-wise comparison between the two provided tuples
 * 
 * @param lhs the first tuple to compare
 * 
 * @param rhs the second tuple to compare
 * 
 * @return true if the first tuple is less than or equal to the second, 
 * otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator<=(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Performs a component-wise comparison between the two provided tuples
 * 
 * @param lhs the first tuple to compare
 * 
 * @param rhs the second tuple to compare
 * 
 * @return true if the first tuple is greater than the second, otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator>(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Performs a component-wise comparison between the two provided tuples
 * 
 * @param lhs the first tuple to compare
 * 
 * @param rhs the second tuple to compare
 * 
 * @return true if the first tuple is greater than or equal to the second, 
 * otherwise false
 * 
 */
template<typename T, std::size_t N>
bool operator>=(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Computes a negated version of the provided tuple in which each of the 
 * elements is the unary negation of the original
 * 
 * @param tuple the tuple to negate
 * 
 * @return a negated version of the provided tuple
 */
template<typename T, std::size_t N>
midnight::Tuple<T, N> operator-(const midnight::Tuple<T, N>& tuple) noexcept;

/**
 * Computes a component-wise subtraction of the second tuple from the first
 * 
 * @param lhs the tuple to subtract the second from
 * 
 * @param rhs the tuple to subtract from the first
 * 
 * @return a subtraction of the second tuple from the first
 * 
 */
template<typename T, std::size_t N>
midnight::Tuple<T, N> operator-(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Computes a component-wise product of the second tuple and the first
 * 
 * @param lhs the tuple to multiply
 * 
 * @param rhs the other tuple to multiply
 * 
 * @return the product of the second tuple and first
 * 
 */
template<typename T, std::size_t N>
midnight::Tuple<T, N> operator*(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Computes a component-wise product of the provided Tuple and scalar
 * 
 * @param tuple the Tuple to multiply
 * 
 * @param scalar the scalar to multiply by
 * 
 * @return the product of the provided Tuple and scalar
 * 
 */
template<typename T, std::size_t N>
midnight::Tuple<T, N> operator*(const midnight::Tuple<T, N>& tuple, T scalar) noexcept;

/**
 * Computes a component-wise sum of the second tuple and the first
 * 
 * @param lhs the tuple to add
 * 
 * @param rhs the other tuple to add
 * 
 * @return the sum of the second tuple and first
 * 
 */
template<typename T, std::size_t N>
midnight::Tuple<T, N> operator+(const midnight::Tuple<T, N>& lhs, const midnight::Tuple<T, N>& rhs) noexcept;

/**
 * Relying on ADL, this function retrieves the <i>I</i>th element of the 
 * provided tuple
 * 
 * @param tuple the tuple of whose element to retrieve
 * 
 * @return <i>I</i>th element of the 
 * provided tuple
 * 
 */
template <size_t I, class T, size_t N>
constexpr T& get(midnight::Tuple<T, N>& tuple) noexcept;
/**
 * Relying on ADL, this function retrieves the <i>I</i>th element of the 
 * provided tuple
 * 
 * @param tuple the tuple of whose element to retrieve
 * 
 * @return <i>I</i>th element of the 
 * provided tuple
 * 
 */
template <size_t I, class T, size_t N>
constexpr T&& get(midnight::Tuple<T, N>&& tuple) noexcept;


/**
 * Relying on ADL, this function retrieves the <i>I</i>th element of the 
 * provided tuple
 * 
 * @param tuple the tuple of whose element to retrieve
 * 
 * @return <i>I</i>th element of the 
 * provided tuple
 * 
 */
template <size_t I, class T, size_t N>
constexpr T get(const midnight::Tuple<T, N>& tuple) noexcept;

namespace midnight
{

/**
 * A generic base class that manages basic operations.  Tuples are the 
 * basic building blocks of many types including colors, points, vectors, 
 * axis-angles, and quaternions.
 * 
 * Tuples are also compatible with numerous STL algorithms and can be 
 * considered roughly equivalent to std::array constructs.
 * 
 * Unless otherwise noted, all tuple operations are performed element-wise 
 * (meaning that the same operation is repeated on all elements).
 * 
 * For example, adding the scalar "4" to the tuple {0, 1, 2} will 
 * produce the tuple {0 + 4, 1 + 4, 2 + 4}, or {4, 5, 6}.
 * 
 * Likewise, adding the tuple {1, 2, 3} to the tuple {4, 5, 6} will produce 
 * the tuple {1 + 4, 2 + 5, 3 + 6}, or {5, 7, 9}.
 * 
 * It is also worth noting that division operations are not supported, as such 
 * operations would violate the 'noexcept' contract that this class 
 * enforces.  No operations performed on this class shall throw exceptions 
 * nor shall they otherwise fail (except for subscript operators, which 
 * will cause indeterministic behavior in the event of an out of bounds index).
 * 
 * Several common tuples are also defined in the following format:
 * 
 * Tuple {number of elements} {type abbreviation}
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
 * example: Tuple3F - A tuple that holds 3 float elements
 * 
 * User-defined tuples are expected to follow the aforementioned format.
 * 
 * @tparam T the type of the elements that are stored in this tuple
 * 
 * @tparam N the number of elements that are stored in this tuple
 * 
 */
template<typename T, std::size_t N>
class Tuple
{
    /// <= Zero-length tuples make no sense. (at least not to me)
    static_assert(N > 0, "The size of a tuple must be > 0");

    /// Allow our free functions to access 'elements'
    friend std::ostream& operator<<<>(std::ostream& stream, const Tuple<T, N>& rhs);
    friend std::istream& operator>><>(std::istream& stream, Tuple<T, N>& rhs);
    friend bool operator== <>(const Tuple<T, N>& lhs, const Tuple<T, N>& rhs) noexcept;
    friend bool operator!= <>(const Tuple& lhs, const Tuple& rhs) noexcept;
    friend bool operator< <>(const Tuple& lhs, const Tuple& rhs) noexcept;
    friend bool operator<= <>(const Tuple& lhs, const Tuple& rhs) noexcept;
    friend bool operator> <>(const Tuple& lhs, const Tuple& rhs) noexcept;
    friend bool operator>= <>(const Tuple& lhs, const Tuple& rhs) noexcept;
    friend Tuple operator*(const Tuple&, const Tuple&)noexcept;
    friend Tuple operator+(const Tuple&, const Tuple&)noexcept;

  protected:

    /// The actual container that holds the elements of our Tuple
    std::array<T, N> elements;

  public:

    static constexpr std::size_t Length = N;

    /// Some typedefs that provide a STL look and feel
    typedef T value_type;
    typedef typename std::array<T, N>::size_type size_type;
    typedef typename std::array<T, N>::difference_type difference_type;
    typedef typename std::array<T, N>::reference reference;
    typedef typename std::array<T, N>::const_reference const_reference;
    typedef typename std::array<T, N>::pointer pointer;
    typedef typename std::array<T, N>::const_pointer const_pointer;
    typedef typename std::array<T, N>::iterator iterator;
    typedef typename std::array<T, N>::const_iterator const_iterator;
    typedef typename std::array<T, N>::reverse_iterator reverse_iterator;
    typedef typename std::array<T, N>::const_reverse_iterator const_reverse_iterator;

    /**
     * Default constructor - all elements of this tuple are zero-initialized
     * 
     * <pre>
     * /// Elements = {0.0f, 0.0f, 0.0f}
     * Tuple3F example;
     * </pre>
     * 
     */
    constexpr Tuple() noexcept;


    Tuple(const std::initializer_list<T> elements);

    /**
     * Constructs a Tuple from the provided elements
     * 
     * @param element the first element to fill this Tuple with
     * 
     * @param elements the rest of the elements to fill this Tuple with
     * 
     * <pre>
     * /// Elements = {1.0f, 2.0f, 3.0f}
     * Tuple3F example(1.0f, 2.0f, 3.0f);
     * </pre>
     * 
     */
    template<typename ...E>
    constexpr explicit Tuple(T element, E&&...elements) noexcept;

    /**
     * Copy constructor
     * 
     * @param rhs the Tuple to copy
     * 
     */
    Tuple(const Tuple& rhs) noexcept = default;

    /**
     * Move constructor
     * 
     * @param rhs the Tuple to move
     * 
     */
    Tuple(Tuple&& rhs) noexcept = default;

    /**
     * Assignment
     * 
     * @param rhs the Tuple to assign
     * 
     * @return *this
     * 
     */
    Tuple& operator=(const Tuple& rhs) noexcept = default;

    /**
     * Returns an iterator to the first element of this Tuple
     * 
     * @return  an iterator to the first element of this Tuple
     * 
     */
    iterator begin() noexcept;

    /**
     * Returns a const_iterator to the first element of this Tuple
     * 
     * @return  a const_iterator to the first element of this Tuple
     * 
     */
    const_iterator begin() const noexcept;

    /**
     * Returns an iterator to one beyond the last element of this Tuple
     * 
     * @return  an iterator to one beyond the last element of this Tuple
     * 
     */
    iterator end() noexcept;

    /**
     * Returns a const_iterator to one beyond the last element of this Tuple
     * 
     * @return  a const_iterator to one beyond the last element of this Tuple
     * 
     */
    const_iterator end() const noexcept;

    /**
     * Returns a reverse_iterator to the first element of this Tuple
     * 
     * @return a reverse_iterator to the first element of this Tuple
     * 
     */
    reverse_iterator rbegin() noexcept;

    /**
     * Returns a const_reverse_iterator to the first element of this Tuple
     * 
     * @return a const_reverse_iterator to the first element of this Tuple
     * 
     */
    const_reverse_iterator rbegin() const noexcept;

    /**
     * Returns a reverse_iterator to one beyond the end of this Tuple
     * 
     * @return a reverse_iterator to one beyond the end of this Tuple
     * 
     */
    reverse_iterator rend() noexcept;

    /**
     * Returns a const_reverse_iterator to one beyond the end of this Tuple
     * 
     * @return a const_reverse_iterator to one beyond the end of this Tuple
     * 
     */
    const_reverse_iterator rend() const noexcept;

    /**
     * Retrieves the number of elements contained in this Tuple
     * 
     * @return  the number of elements contained in this Tuple
     * 
     */
    constexpr size_type size() const noexcept;

    /**
     * Multiplies this Tuple by the provided scalar
     * 
     * @param scalar the scalar value to multiply this Tuple by
     * 
     * @return *this
     * 
     */
    Tuple& operator*=(T scalar)noexcept;

    /**
     * Multiplies this Tuple by the provided Tuple
     * 
     * @param rhs the Tuple to multiply this Tuple by
     * 
     * @return *this
     * 
     */
    Tuple& operator*=(const Tuple& rhs) noexcept;

    /**
     * Adds the provided scalar value to this Tuple
     * 
     * @param scalar the scalar value to add
     * 
     * @return *this
     * 
     */
    Tuple& operator+=(T scalar)noexcept;

    /**
     * Adds the provided Tuple to this Tuple
     * 
     * @param rhs the Tuple to add
     * 
     * @return *this
     * 
     */
    Tuple& operator+=(const Tuple& rhs) noexcept;

    /**
     * Subtracts the provided scalar value from this Tuple
     * 
     * @param scalar the scalar value to subtract
     * 
     * @return *this
     * 
     */
    Tuple& operator-=(T scalar)noexcept;

    /**
     * Subtracts the provided Tuple from this Tuple
     * 
     * @param rhs the Tuple to subtract
     * 
     * @return *this
     * 
     */
    Tuple& operator-=(const Tuple& rhs) noexcept;

    /**
     * Const subscript access
     * 
     * @param index the index of the element to retrieve
     * 
     * @return the element at the provided index
     * 
     */
    constexpr T operator[](size_type index) const noexcept;

    /**
     * Subscript access
     * 
     * @param index the index of the element to retrieve
     * 
     * @return the element at the provided index
     * 
     */
    T& operator[](size_type index)noexcept;

    /**
     * Clamps the elements of this Tuple to the finite range 
     * [min, numeric_limits<T>::max()]
     * 
     * @param min the minimum value to clamp this tuple to
     * 
     * @return *this
     * 
     */
    Tuple& clampMin(T min) noexcept;

    /**
     * Clamps the elements of this Tuple to the finite range [min, max]
     * 
     * @param min the minimum value to clamp this tuple to
     * 
     * @param max the maximum value to clamp this tuple to
     * 
     * @return *this
     * 
     */
    Tuple& clamp(T min, T max) noexcept;

    /**
     * Clamps the elements of this Tuple to the finite range
     * [numeric_limits<T>::min(), max]
     * 
     * @param max the maximum value to clamp this tuple to
     * 
     * @return *this
     * 
     */
    Tuple& clampMax(T max) noexcept;

    /**
     * Calculates the dot-product of this vector and the provided vector
     * 
     * @param rhs the other vector
     * 
     * @return the dot-product of this vector and the provided vector
     * 
     */
    T dot(const Tuple& rhs) const noexcept;

    /**
     * Sets the elements of this Tuple to the provided elements
     * 
     * @param elements the elements to fill this Tuple with
     * 
     * <pre>
     * /// Elements = {1.0f, 2.0f, 3.0f}
     * Tuple3F example;
     * example.set(1.0f, 2.0f, 3.0f);
     * </pre>
     * 
     * @return *this
     */
    template<typename ...E>
    Tuple& set(T element, E&&...elements) noexcept;

    /**
     * Sets the elements of this Tuple to the provided elements
     * 
     * @param elements the elements to fill this Tuple with
     * 
     * @return *this
     * 
     * <pre>
     * /// std::array<float, 3> elements = {1.0f, 2.0f, 3.0f};
     * Tuple3F example;
     * example.set(elements);
     * </pre>
     * 
     */
    virtual Tuple& set(const std::array<T, N>& elements) noexcept;

    /**
     * Retrieves this Tuple as represented by an array
     * 
     * @return this Tuple as represented by an array
     * 
     */
    const std::array<T, N> asArray() const;

    void swap(Tuple& rhs) noexcept
    {
        this->elements.swap(rhs.elements);
    }

    /**
     * Virtual destructor
     * 
     */
    virtual ~Tuple() noexcept = default;
};

}

#    include "Tuple.inl"

namespace midnight
{

typedef Tuple<double, 1> Tuple1D; /** < A Tuple that holds 1 double */
typedef Tuple<double, 2> Tuple2D; /** < A Tuple that holds 2 doubles */
typedef Tuple<double, 3> Tuple3D; /** < A Tuple that holds 3 doubles */
typedef Tuple<double, 4> Tuple4D; /** < A Tuple that holds 4 doubles */

typedef Tuple<float, 1> Tuple1F; /** < A Tuple that holds 1 float */
typedef Tuple<float, 2> Tuple2F; /** < A Tuple that holds 2 floats */
typedef Tuple<float, 3> Tuple3F; /** < A Tuple that holds 3 floats */
typedef Tuple<float, 4> Tuple4F; /** < A Tuple that holds 4 floats */

typedef Tuple<int64_t, 1> Tuple1L; /** < A Tuple that holds 1 signed long */
typedef Tuple<int64_t, 2> Tuple2L; /** < A Tuple that holds 2 signed longs */
typedef Tuple<int64_t, 3> Tuple3L; /** < A Tuple that holds 3 signed longs */
typedef Tuple<int64_t, 4> Tuple4L; /** < A Tuple that holds 4 signed longs */

typedef Tuple<uint64_t, 1> Tuple1UL; /** < A Tuple that holds 1 unsigned long */
typedef Tuple<uint64_t, 2> Tuple2UL; /** < A Tuple that holds 2 unsigned longs */
typedef Tuple<uint64_t, 3> Tuple3UL; /** < A Tuple that holds 3 unsigned longs */
typedef Tuple<uint64_t, 4> Tuple4UL; /** < A Tuple that holds 4 unsigned longs */

typedef Tuple<int32_t, 1> Tuple1I; /** < A tuple that holds 1 signed int */
typedef Tuple<int32_t, 2> Tuple2I; /** < A Tuple that holds 2 signed ints */
typedef Tuple<int32_t, 3> Tuple3I; /** < A Tuple that holds 3 signed ints */
typedef Tuple<int32_t, 4> Tuple4I; /** < A Tuple that holds 4 signed ints */

typedef Tuple<uint32_t, 1> Tuple1UI; /** < A tuple that holds 1 unsigned int */
typedef Tuple<uint32_t, 2> Tuple2UI; /** < A Tuple that holds 2 unsigned ints */
typedef Tuple<uint32_t, 3> Tuple3UI; /** < A Tuple that holds 3 unsigned ints */
typedef Tuple<uint32_t, 4> Tuple4UI; /** < A Tuple that holds 4 unsigned ints */

typedef Tuple<int16_t, 1> Tuple1S; /** < A Tuple that holds 1 signed short */
typedef Tuple<int16_t, 2> Tuple2S; /** < A Tuple that holds 2 signed shorts */
typedef Tuple<int16_t, 3> Tuple3S; /** < A Tuple that holds 3 signed shorts */
typedef Tuple<int16_t, 4> Tuple4S; /** < A Tuple that holds 4 signed shorts */

typedef Tuple<uint16_t, 1> Tuple1US; /** < A Tuple that holds 1 unsigned short */
typedef Tuple<uint16_t, 2> Tuple2US; /** < A Tuple that holds 2 unsigned shorts */
typedef Tuple<uint16_t, 3> Tuple3US; /** < A Tuple that holds 3 unsigned shorts */
typedef Tuple<uint16_t, 4> Tuple4US; /** < A Tuple that holds 4 unsigned shorts */

typedef Tuple<int8_t, 1> Tuple1C; /** < A Tuple that holds 1 signed char */
typedef Tuple<int8_t, 2> Tuple2C; /** < A Tuple that holds 2 signed chars */
typedef Tuple<int8_t, 3> Tuple3C; /** < A Tuple that holds 3 signed chars */
typedef Tuple<int8_t, 4> Tuple4C; /** < A Tuple that holds 4 signed chars */

typedef Tuple<uint8_t, 1> Tuple1UC; /** < A Tuple that holds 1 unsigned char */
typedef Tuple<uint8_t, 2> Tuple2UC; /** < A Tuple that holds 2 unsigned chars */
typedef Tuple<uint8_t, 3> Tuple3UC; /** < A Tuple that holds 3 unsigned chars */
typedef Tuple<uint8_t, 4> Tuple4UC; /** < A Tuple that holds 4 unsigned chars */

}

#endif
