#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "BuildConstraints.hpp"

#include <iostream>

#include "Angle.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

namespace midnight
{
    template<typename T>
    class Quaternion;
}

/**
 * Extracts a Quaternion from the provided input stream
 * 
 * @param stream the input stream to extract from
 * 
 * @param quaternion the Quaternion to extract into
 * 
 * @return the provided input stream
 * 
 */
template<typename T>
std::istream& operator>>(std::istream& stream, midnight::Quaternion<T>& quaternion);

/**
 * Inserts the provided Quaternion into the provided output stream
 * 
 * @param stream the output stream to insert into
 * 
 * @param quaternion the Quaternion to insert
 * 
 * @return the provided output stream
 * 
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, const midnight::Quaternion<T>& quaternion);

/**
 * Inserts the provided Quaternion into the provided output stream
 * 
 * @param stream the output stream to insert into
 * 
 * @param quaternion the Quaternion to insert
 * 
 * @return the provided output stream
 * 
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, midnight::Quaternion<T>&& quaternion);

/**
 * Compares two Quaternions for equality
 * 
 * @param lhs the first Quaternion to compare
 * 
 * @param rhs the second Quaternion to compare
 * 
 * @return true if and only if the two Quaternions have the same axis and angle, otherwise false
 * 
 * @note This method <i>may</i> utilize epsilon-value floating point comparisons
 * 
 */
template<typename T>
bool operator==(const midnight::Quaternion<T>& lhs, const midnight::Quaternion<T>& rhs);

/**
 * Compares two Quaternions for inequality
 * 
 * @param lhs the first Quaternion to compare
 * 
 * @param rhs the second Quaternion to compare
 * 
 * @return true if the two Quaternions have the differing axes or angles, otherwise false
 * 
 * @note This method <i>may</i> utilize epsilon-value floating point comparisons
 * 
 */
template<typename T>
bool operator!=(const midnight::Quaternion<T>& lhs, const midnight::Quaternion<T>& rhs);

template<typename T>
midnight::Quaternion<T> operator*(const midnight::Quaternion<T>& lhs, const midnight::Quaternion<T>& rhs);

template<typename T>
midnight::Quaternion<T> operator*(midnight::Quaternion<T>&& lhs, midnight::Quaternion<T>&& rhs);

namespace midnight
{
    /**
     * Quaternions represent a way of mathematically encoding a rotation about an arbitrary axis.
     */
    template<typename T>
    class Quaternion
    {
        friend std::istream& operator>><>(std::istream& stream, Quaternion& quaternion);
        friend std::ostream& operator<<<>(std::ostream& stream, const Quaternion<T>& quaternion);
        friend std::ostream& operator<<<>(std::ostream& stream, Quaternion<T>&& quaternion);

        friend bool operator==<>(const Quaternion<T>& lhs, const Quaternion<T>& rhs);
        friend bool operator!=<>(const Quaternion<T>& lhs, const Quaternion<T>& rhs);
        
        /// The axis about which to rotate
        Vector<T, 3> axis;
        
        /// The angle by which to rotate
        Radians<T> angle;
        
      public:
        
        /**
         * Constructs a Quaternion from the provided axis and angle (in radians)
         * 
         * @param axis the axis about which to rotate
         * 
         * @param angle the angle (in radians) by which to rotate
         * 
         */
        Quaternion(const Vector<T, 3>& axis, const Radians<T>& angle);
        
        /**
         * Constructs a Quaternion from the provided axis and angle (in radians)
         * 
         * @param axis the axis about which to rotate
         * 
         * @param angle the angle (in radians) by which to rotate
         * 
         */
        Quaternion(Vector<T, 3>&& axis, Radians<T>&& angle);
        
        /**
         * Constructs a Quaternion from the provided axis and angle (in degrees)
         * 
         * @param axis the axis about which to rotate
         * 
         * @param angle the angle (in degrees) by which to rotate
         * 
         */
        Quaternion(const Vector<T, 3>& axis, const Degrees<T>& angle);
        
        /**
         * Constructs a Quaternion from the provided axis and angle (in degrees)
         * 
         * @param axis the axis about which to rotate
         * 
         * @param angle the angle (in degrees) by which to rotate
         * 
         */
        Quaternion(Vector<T, 3>&& axis, Degrees<T>&& angle);
        
        /**
         * Constructs an identity-Quaternion
         * 
         */
        constexpr Quaternion() noexcept;
        
        /**
         * Move constructs a Quaternion from the provided Quaternion
         * 
         * @param rhs the Quaternion to construct this one with
         * 
         */
        Quaternion(Quaternion&& rhs) noexcept = default;

        /**
         * Copy constructs a Quaternion from the provided Quaternion
         * 
         * @param rhs the Quaternion to construct this one with
         * 
         */
        Quaternion(const Quaternion& rhs) noexcept = default;

        /**
         * Copy-assigns the provided Quaternion to this Quaternion
         * 
         * @param rhs the Quaternion to assign to this one
         * 
         * @return *this
         * 
         */
        Quaternion& operator=(const Quaternion& rhs) noexcept = default;

        /**
         * Move-assigns the provided Quaternion to this Quaternion
         * 
         * @param rhs the Quaternion to assign to this one
         * 
         * @return *this
         * 
         */
        Quaternion& operator=(Quaternion&& rhs) noexcept = default;
        
        /**
         * Explicit conversion operator to a 4x4 matrix
         * 
         * @return a rotation Matrix built from this Quaternion
         * 
         */
        explicit operator Matrix<T, 4, 4>() const noexcept;

        /**
         * Retrieves the axis about which to rotate
         * 
         * @return the axis about which to rotate
         * 
         */
        const Vector<T, 3>& getAxis() const noexcept;
        
        /**
         * Retrieves the angle by which to rotate
         * 
         * @return the angle by which to rotate
         * 
         */
        const Radians<T>& getAngle() const noexcept;

        /**
         * Normalizes this Quaternion in place
         * 
         */
        void normalize() noexcept;
        
        /**
         * Multiplies this Quaternion by the provided Quaternion
         * 
         * @param rhs the Quaternion to multiply by
         * 
         * @return *this
         * 
         */
        Quaternion& operator*=(const Quaternion& rhs) noexcept;

        /**
         * Multiplies this Quaternion by the provided Quaternion
         * 
         * @param rhs the Quaternion to multiply by
         * 
         * @return *this
         * 
         */
        Quaternion& operator*=(Quaternion&& rhs) noexcept;

        /**
         * Default trivial constructor
         * 
         */
        ~Quaternion() noexcept = default;
    };
    
}

#include "Quaternion.inl"

#endif
