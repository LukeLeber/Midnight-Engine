/**
 * This file is protected under the KILLGPL License.
 * 
 * For more information visit www.midnightengine.com/license
 *  
 * @version 1.1
 *      1/22/2014 - initial draft
 *      3/26/2014 - API & Documentation Enhancement
 * 
 * @since 1.0
 * 
 * @author Luke A. Leber <LukeLeber@gmail.com>
 * 
 */
#ifndef COLOR_1_22_2014_HPP
#define COLOR_1_22_2014_HPP

#include <cstdint>

#include "BuildConstraints.hpp"
#include "Tuple.hpp"

namespace midnight
{

/**
 * @brief A specialized Tuple that represents a color.
 * 
 * Colors are color-space agnostic, meaning that the elements may represent 
 * any color-space elements such as RGB, RGBA, ARGB, CMYK, XYZ, etc...
 * 
 * 
 * @tparam T the type of the elements that are stored in this color
 * 
 * @tparam N the number of elements that are stored in this color
 * 
 * TODO: HTML Table?  The chart below doesn't look so hot in the generated docs...
 * @note Several common colors are also defined in the following format:
 * 
 * Color {number of elements} {type abbreviation}
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
 * example: Color3F - A color that holds 3 float elements
 * 
 * User-defined colors are expected to follow the aforementioned format.
 * 
 */
template<typename T, std::size_t N>
class Color : public Tuple<T, N>
{
  public:

    /**
     * Default constructor - all elements of this Color are zero-initialized
     * 
     * <pre>
     *  <i>Examples</i><pre>
     *      Color3F example;
     *      std::cout << example[0] << ", " << example[1] << ", " << example[2] << std::endl;
     *      // Prints "0, 0, 0"</pre>
     * </pre>
     */
    constexpr Color() noexcept;

    /**
     * Constructs a Color from the provided elements.
     * 
     * @note The number of elements provided must be equal to the 
     * number of elements that this Color can hold, otherwise a compile-time error is generated.
     * <br>
     * <br>
     * In other words, consider this constructor to take the following form based on the template parameter N:
     * <pre>
     * // N == 1
     * Tuple(T arg1);
     * // N == 2
     * Tuple(T arg1, T arg2);
     * // N == M
     * Tuple(T arg0, T arg1, ...T argM);
     * </pre>
     * 
     * @param element the first element to fill this Color with
     * 
     * @param elements the rest of the elements to fill this Color with
     * 
     * <pre>
     *  <i>Examples:</i><pre>
     *      // Compiler error - not enough elements provided
     *      Color3F bad = {1.0f, 2.0f}; 
     * 
     *      // Compiler error - too many elements provided
     *      Color3F bad = {1.0f, 2.0f, 3.0f, 4.0f}; 
     * 
     *      Color3F good(1.0f, 2.0f, 3.0f);
     *      std::cout << good[0] << ", " << good[1] << ", " << good[2] << std::endl;
     *      // Prints "1, 2, 3"</pre>
     * </pre>
     * 
     */
    template<typename ...E>
    constexpr explicit Color(T element, E&&...elements) noexcept;

    /**
     * "Copy Constructs" a Color from the provided Tuple.  Shadowing a would-be 
     * copy constructor, this allows for copy-construction semantics with any type 
     * that extends Tuple.
     * 
     * @param tuple the Tuple to copy
     * 
     * <pre>
     *  <i>Examples:</i><pre>
     *      Color3F original(1.0f, 1.0f, 1.0f);
     *      Color3F copy(original);</pre>
     * </pre>
     * 
     */
    constexpr Color(const Tuple<T, N>& tuple) noexcept;

    /**
     * "Move Constructs" a Color from the provided Tuple.  Shadowing a would-be 
     * move constructor, this allows for move-construction semantics with any type 
     * that extends Tuple.
     * 
     * @note Remember that accessing a moved resource from the calling code is an error!
     * 
     * @param tuple the Tuple to move
     * 
     * <pre>
     *  <i>Examples</i><pre>
     *      Color3F original(1.0f, 1.0f, 1.0f);
     *      Color3F moved(std::move(original));
     * </pre>
     * 
     */
    constexpr Color(Tuple<T, N>&& tuple) noexcept;

    /**
     * Copy-Assigns the provided Tuple to this Color.
     * 
     * @param tuple the Tuple to copy
     * 
     * @return *this
     * 
     * <pre>
     *  <i>Examples</i><pre>
     *      Color3F original;
     *      Tuple3F tuple;
     *      Vector3F vector;
     *      original = tuple;
     *      original = vector;
     * </pre>
     * 
     */
    Color& operator=(const Tuple<T, N>& tuple) noexcept;

    /**
     * Move-Assigns the provided Tuple to this Color
     * 
     * @note Remember that accessing a moved resource from the calling code is an error!
     * 
     * @param tuple the Tuple to move
     * 
     * @return *this
     * 
     * <pre>
     *  <i>Examples</i><pre>
     *      Color3F original;
     *      Tuple3F tuple;
     *      Vector3F vector;
     *      original = std::move(tuple);
     *      original = std::move(vector);
     * </pre>
     * 
     */
    Color& operator=(Tuple<T, N>&& tuple) noexcept;
    
    /**
     * Default destructor - no special cleanup is required.
     * 
     */
    virtual ~Color() = default;
};

}

#    include "Color.inl"

namespace midnight
{

using Color3D = Color<double, 3>;       /** A Color that holds 3 64-bit doubles */
using Color4D = Color<double, 4>;       /** A Color that holds 4 64-doubles */
using Color3F = Color<float, 3>;        /** A Color that holds 3 32-bit floats */
using Color4F = Color<float, 4>;        /** A Color that holds 4 32-bit floats */

using Color3UL = Color<uint64_t, 3>;    /** A Color that holds 3 unsigned 64-bit integers */
using Color4UL = Color<uint64_t, 4>;    /** A Color that holds 4 unsigned 64-bit integers */
using Color3L = Color<int64_t, 3>;      /** A Color that holds 3 signed 64-bit integers */
using Color4L = Color<int64_t, 4>;      /** A Color that holds 4 signed 64-bit integers */

using Color3UI = Color<uint32_t, 3>;    /** A Color that holds 3 unsigned 32-bit integers */
using Color4UI = Color<uint32_t, 4>;    /** A Color that holds 4 unsigned 32-bit integers */
using Color3I = Color<int32_t, 3>;      /** A Color that holds 3 signed 32-bit integers */
using Color4I = Color<int32_t, 4>;      /** A Color that holds 4 signed 32-bit integers */

using Color3US = Color<uint16_t, 3>;    /** A Color that holds 3 unsigned 16-bit integers */
using Color4US = Color<uint16_t, 4>;    /** A Color that holds 4 unsigned 16-bit integers */
using Color3S = Color<int16_t, 3>;      /** A Color that holds 3 signed 16-bit integers */
using Color4S = Color<int16_t, 4>;      /** A Color that holds 4 signed 16-bit integers */

using Color3UC = Color<uint8_t, 3>;     /** A Color that holds 3 unsigned 8-bit integers */
using Color4UC = Color<uint8_t, 4>;     /** A Color that holds 4 unsigned 8-bit integers */
using Color3C = Color<int8_t, 3>;       /** A Color that holds 3 signed 8-bit integers */
using Color4C = Color<int8_t, 4>;       /** A Color that holds 4 signed 8-bit integers */

}

#endif
