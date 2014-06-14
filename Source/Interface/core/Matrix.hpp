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
#ifndef MATRIX_2_4_2014_HPP
#define MATRIX_2_4_2014_HPP

#include "BuildConstraints.hpp"

#include <array>
#include <cstdint>
#include <initializer_list>
#include <iosfwd>
#include <iterator>

#include "Vector.hpp"

namespace midnight
{

template<typename T, std::size_t Rows, std::size_t Columns>
class Matrix;

}

/**
 * Performs a component-wise comparison between the two provided matrices
 * 
 * @param lhs the first matrix to compare
 * 
 * @param rhs the second matrix to compare
 * 
 * @return true if the two matrices are equal, otherwise false
 * 
 */
template<typename T, std::size_t Rows, std::size_t Columns>
bool operator==(const midnight::Matrix<T, Rows, Columns>& lhs, const midnight::Matrix<T, Rows, Columns>& rhs) noexcept;

/**
 * Performs a component-wise comparison between the two provided matrices
 * 
 * @param lhs the first matrix to compare
 * 
 * @param rhs the second matrix to compare
 * 
 * @return true if the two matrices are not equal, otherwise false
 * 
 */
template<typename T, std::size_t Rows, std::size_t Columns>
bool operator!=(const midnight::Matrix<T, Rows, Columns>& lhs, const midnight::Matrix<T, Rows, Columns>& rhs) noexcept;

template<typename T, std::size_t Rows, std::size_t Columns>
midnight::Matrix<T, Rows, Columns> operator-(const midnight::Matrix<T, Rows, Columns>& source) noexcept;

/**
 * Inserts the provided Matrix into the provided output stream
 * 
 * @param stream the stream to insert the provided Matrix into
 * 
 * @param matrix the Matrix to insert into the provided stream
 * 
 * @return the provided stream
 * 
 */
template<typename T, std::size_t Rows, std::size_t Columns>
std::ostream& operator<<(std::ostream& stream, const midnight::Matrix<T, Rows, Columns>& matrix);

/**
 * Extracts a Matrix from the provided input stream
 * 
 * @param stream the stream to extract from
 * 
 * @param matrix the Matrix to extract into
 * 
 * @return the provided input stream
 * 
 */
template<typename T, std::size_t Rows, std::size_t Columns>
std::istream& operator>>(std::istream& stream, midnight::Matrix<T, Rows, Columns>& matrix);

namespace midnight
{
    
/**
 * A modern general-purpose object-oriented matrix class without any legacy hacks from C
 * 
 * Several common tuples are also defined in the following format:
 * 
 * Matrix {number of rows} x {number of columns} {type abbreviation}
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
 * example: Matrix3x3F - A Matrix that holds 3x3 float elements
 * 
 * User-defined Matrix types are expected to follow the aforementioned format.
 * 
 * @tparam T the type of data stored in this matrix
 * 
 * @tparam Rows the number of rows in this matrix
 * 
 * @tparam Columns the number of columns in this matrix
 */
template<typename T, std::size_t Rows, std::size_t Columns>
class Matrix
{
    static_assert(Rows > 0, "The number of rows in a Matrix must be greater than zero");
    static_assert(Columns > 0, "The number of columns in a Matrix must be greater than zero");

    friend std::ostream& ::operator<<<>(std::ostream&, const Matrix<T, Rows, Columns>&);
    friend std::istream& ::operator>><>(std::istream&, Matrix<T, Rows, Columns>&);
    friend bool ::operator!=<>(const Matrix<T, Rows, Columns>&, const Matrix<T, Rows, Columns>&) noexcept;
    friend bool ::operator==<>(const Matrix<T, Rows, Columns>&, const Matrix<T, Rows, Columns>&) noexcept;

    constexpr static std::size_t elements_length = Rows * Columns;
    
    std::array<T, elements_length> elements;

    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    
    typedef typename std::array<T, elements_length>::difference_type difference_type;
    typedef typename std::array<T, elements_length>::size_type size_type;
    
    typedef typename std::array<T, elements_length>::iterator iterator;
    typedef typename std::array<T, elements_length>::const_iterator const_iterator;
    typedef typename std::array<T, elements_length>::reverse_iterator reverse_iterator;
    typedef typename std::array<T, elements_length>::const_reverse_iterator const_reverse_iterator;
    
    
  public:

    /**
     * Translates this matrix in the provided direction.
     * 
     * @param direction the vector along which to translate
     * 
     * @return *this
     * 
     * @note Matrix mutation operations may be chained.
     * 
     */
    Matrix& translate(const Vector<T, Rows>& direction);
    
    /**
     * Retrieves the identity-matrix
     * 
     * @note Prefer this factory method opposed to manually creating an identity matrix with values.
     * 
     * @return the identity-matrix
     * 
     */
    static constexpr Matrix IDENTITY() noexcept;

    /**
     * Retrieves the zero-matrix
     * 
     * @note This factory method is roughly equivalent to the default constructor
     * 
     * @return the zero-matrix
     * 
     */
    static constexpr Matrix ZERO() noexcept;


    /**
     * Generates a perspective projection matrix based on the provided frustum parameters
     * 
     * @param fieldOfView the angle (in degrees) of the field of view
     * 
     * @param zNear the z-value of the near clipping plane
     * 
     * @param zFar the z-value of the far clipping plane
     * 
     * @return a perspective projection matrix
     * 
     */
    static constexpr Matrix PERSPECTIVE(T fieldOfView, T zNear, T zFar) noexcept;

    /**
     * Constructs a Matrix with each element initialized to zero
     * 
     */
    constexpr Matrix() noexcept;

    /**
     * Constructs a Matrix whose elements are initialized to the provided array
     * 
     * @param elements the array to initialize this Matrix with
     * 
     * TODO: Check on moving vs copying std::array
     * 
     */
    explicit constexpr Matrix(const std::array<T, Rows * Columns>& elements) noexcept;

    /**
     * Constructs a Matrix whose elements are initialized to the provided array
     * 
     * @param elements the array to initialize this Matrix with
     * 
     * TODO: Check on moving vs copying std::array
     * 
     */
    explicit constexpr Matrix(std::array<T, Rows * Columns>&& elements) noexcept;

    /**
     * Constructs a Matrix whose elements are initialized with the provided values
     * 
     * @param element the first value
     * 
     * @param elements all subsequent values
     * 
     * <pre>Matrix<int, 3, 3> matrix(1, 2, 3, 1, 2, 3, 1,2 ,3);</pre>
     * 
     */
    template<typename ...E>
    explicit constexpr Matrix(T element, E&&... elements) noexcept;

    Matrix(Matrix&& rhs) = default;
    
    Matrix(const Matrix& rhs) = default;
    
    Matrix& operator=(const Matrix& rhs) = default;
    
    Matrix& operator=(Matrix&& rhs) = default;
    
    /**
     * Returns an iterator to the first element of this Matrix
     * 
     * @return  an iterator to the first element of this Matrix
     * 
     */
    iterator begin() noexcept;

    /**
     * Returns a const_iterator to the first element of this Matrix
     * 
     * @return  a const_iterator to the first element of this Matrix
     * 
     */
    const_iterator begin() const noexcept;

    /**
     * Returns an iterator to one beyond the last element of this Matrix
     * 
     * @return  an iterator to one beyond the last element of this Matrix
     * 
     */
    iterator end() noexcept;

    /**
     * Returns a const_iterator to one beyond the last element of this Matrix
     * 
     * @return  a const_iterator to one beyond the last element of this Matrix
     * 
     */
    const_iterator end() const noexcept;

    /**
     * Returns a reverse_iterator to the first element of this Matrix
     * 
     * @return a reverse_iterator to the first element of this Matrix
     * 
     */
    reverse_iterator rbegin() noexcept;

    /**
     * Returns a const_reverse_iterator to the first element of this Matrix
     * 
     * @return a const_reverse_iterator to the first element of this Matrix
     * 
     */
    const_reverse_iterator rbegin() const noexcept;

    /**
     * Returns a reverse_iterator to one beyond the end of this Matrix
     * 
     * @return a reverse_iterator to one beyond the end of this Matrix
     * 
     */
    reverse_iterator rend() noexcept;

    /**
     * Returns a const_reverse_iterator to one beyond the end of this Matrix
     * 
     * @return a const_reverse_iterator to one beyond the end of this Matrix
     * 
     */
    const_reverse_iterator rend() const noexcept;
    
    /**
     * Retrieves a const reference to the element at the provided row and column
     * 
     * @param row the row to access
     * 
     * @param column the column to access
     * 
     * @return the element at the provided row and column
     * 
     * @note Attempting to access an out of bounds position will behave according to 
     * the <i>MIDNIGHT_ENABLE_ASSERTIONS</i> compile-time flag.  If dynamic assertions 
     * are enabled, then a diagnostic message is printed to <i>std::cerr</i> and 
     * <i>std::exit</i> is called.  If dynamic assertions are disabled, then the 
     * result is undefined.
     * 
     */
    const T& operator()(std::size_t row, std::size_t column) const noexcept;

    /**
     * Retrieves a reference to the element at the provided row and column
     * 
     * @param row the row to access
     * 
     * @param column the column to access
     * 
     * @return the element at the provided row and column
     * 
     * @note Attempting to access an out of bounds position will behave according to 
     * the <i>MIDNIGHT_ENABLE_ASSERTIONS</i> compile-time flag.  If dynamic assertions 
     * are enabled, then a diagnostic message is printed to <i>std::cerr</i> and 
     * <i>std::exit</i> is called.  If dynamic assertions are disabled, then the 
     * result is undefined.
     * 
     */
    T& operator()(std::size_t row, std::size_t column) noexcept;

    /**
     * Retrieves a valid pointer to the first underlying element of this Matrix.  It can be assumed that 
     * the elements of this Matrix are contiguous in memory, and as such may be freely passed to the OpenGL 
     * implementation like so:
     * <pre>
     *  Matrix3x3F projection = Matrix3x3F::PROJECTION(45.0f, 0.5f, 100.0f);
     *  glUniformMatrix4fv(perspectiveMatrixHandle, 1, GL_FALSE, &projection);
     * </pre>
     * 
     * @warning The effects of attempting to use this pointer after this Matrix exits scope are undefined.
     * 
     * @return a valid pointer to the underlying elements of this Matrix
     * 
     */
    const T* operator&() const;

    /**
     * Sets the elements of this Matrix to the provided elements
     * 
     * @param elements the new elements of this Matrix
     * 
     * @note The number of elements provided <i>must</i> match the number of elements of this Matrix, 
     * otherwise a compile-time is triggered
     * 
     * @note Each provided element must be implicitly convertible to <i>T</i>, otherwise a compile-time 
     * error is triggered
     * 
     */
    template<typename ...E>
    void set(E&&... elements) noexcept;
    
};

}

#include "Matrix.inl"

namespace midnight
{
    
typedef Matrix<uint8_t, 2, 2> Matrix2x2UC;
typedef Matrix<uint8_t, 3, 3> Matrix3x3UC;
typedef Matrix<uint8_t, 4, 4> Matrix4x4UC;

typedef Matrix<int8_t, 2, 2> Matrix2x2C;
typedef Matrix<int8_t, 3, 3> Matrix3x3C;
typedef Matrix<int8_t, 4, 4> Matrix4x4C;

typedef Matrix<uint16_t, 2, 2> Matrix2x2US;
typedef Matrix<uint16_t, 3, 3> Matrix3x3US;
typedef Matrix<uint16_t, 4, 4> Matrix4x4US;

typedef Matrix<int16_t, 2, 2> Matrix2x2S;
typedef Matrix<int16_t, 3, 3> Matrix3x3S;
typedef Matrix<int16_t, 4, 4> Matrix4x4S;

typedef Matrix<uint32_t, 2, 2> Matrix2x2UI;
typedef Matrix<uint32_t, 3, 3> Matrix3x3UI;
typedef Matrix<uint32_t, 4, 4> Matrix4x4UI;

typedef Matrix<int32_t, 2, 2> Matrix2x2I;
typedef Matrix<int32_t, 3, 3> Matrix3x3I;
typedef Matrix<int32_t, 4, 4> Matrix4x4I;

typedef Matrix<uint64_t, 2, 2> Matrix2x2UL;
typedef Matrix<uint64_t, 3, 3> Matrix3x3UL;
typedef Matrix<uint64_t, 4, 4> Matrix4x4UL;

typedef Matrix<int64_t, 2, 2> Matrix2x2L;
typedef Matrix<int64_t, 3, 3> Matrix3x3L;
typedef Matrix<int64_t, 4, 4> Matrix4x4L;

typedef Matrix<float, 2, 2> Matrix2x2F;
typedef Matrix<float, 3, 3> Matrix3x3F;
typedef Matrix<float, 4, 4> Matrix4x4F;

typedef Matrix<double, 2, 2> Matrix2x2D;
typedef Matrix<double, 3, 3> Matrix3x3D;
typedef Matrix<double, 4, 4> Matrix4x4D;

}

#endif
