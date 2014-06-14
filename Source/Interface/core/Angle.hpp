#ifndef ANGLE_HPP
#define ANGLE_HPP

namespace midnight
{
    /**
     * A representation of an angle in arbitrary units
     * 
     */
    template<typename T>
    class Angle
    {
      public:
        
        /**
         * Constructs an Angle
         * 
         * @param value the value of this Angle
         * 
         */
        constexpr Angle(T value) noexcept;

        /**
         * Sets the value of this angle
         * 
         * @param value the angle to set
         * 
         */
        virtual void set(T value) noexcept = 0;
        
        /**
         * Allows for implicit type-conversion to the type T
         * 
         * @return the value of this angle
         * 
         */
        virtual operator T() noexcept = 0;

        /**
         * Default virtual constructor
         * 
         */
        virtual ~Angle() noexcept = default;
    };
}

#include "Angle.inl"

namespace midnight
{
    /// An angle in degree units
    template<typename T>
    using Degrees = detail::AngleImpl<T, detail::AngularUnit::DEGREES>;
    
    /// An angle in radian units
    template<typename T>
    using Radians = detail::AngleImpl<T, detail::AngularUnit::RADIANS>;
    
}


/// TODO: Move to implementation file?  Sloppy to have 2 though...meh.

template<typename T>
inline bool operator==(const midnight::Degrees<T>& lhs, const midnight::Degrees<T>& rhs)
{
    return midnight::detail::AngleEqualityHelper<T>::equals(lhs, rhs);
}

template<typename T>
inline bool operator==(const midnight::Radians<T>& lhs, const midnight::Radians<T>& rhs)
{
    return midnight::detail::AngleEqualityHelper<T>::equals(lhs, rhs);
}

/**
 * Equality operator for Angles in degrees and radians.  Part of the equality operator pack for 
 * Angles, both angles in Degrees and Radians are comparable through implicit unit conversions, meaning 
 * that the same angle represented in both degrees and radians will be equal.
 * 
 * @param lhs the first Angle to compare
 * 
 * @param rhs the second Angle to compare
 * 
 * @return true if the two angles are equal, otherwise false
 * 
 */
template<typename T>
inline bool operator==(const midnight::Degrees<T>& lhs, const midnight::Radians<T>& rhs)
{
    return midnight::detail::AngleEqualityHelper<T>::equals(toRadians(lhs), rhs);
}

/**
 * Equality operator for Angles in degrees and radians.  Part of the equality operator pack for 
 * Angles, both angles in Degrees and Radians are comparable through implicit unit conversions, meaning 
 * that the same angle represented in both degrees and radians will be equal.
 * 
 * @param lhs the first Angle to compare
 * 
 * @param rhs the second Angle to compare
 * 
 * @return true if the two angles are equal, otherwise false
 * 
 */
template<typename T>
inline bool operator==(const midnight::Radians<T>& lhs, const midnight::Degrees<T>& rhs)
{
    return midnight::detail::AngleEqualityHelper<T>::equals(lhs, toRadians(rhs));
}

/**
 * Inequality operator for Angles in degrees and radians.  Part of the equality operator pack for 
 * Angles, both angles in Degrees and Radians are comparable through implicit unit conversions, meaning 
 * that the same angle represented in both degrees and radians will be equal.
 * 
 * @param lhs the first Angle to compare
 * 
 * @param rhs the second Angle to compare
 * 
 * @return true if the two angles are not equal, otherwise false
 * 
 */
template<typename T>
inline bool operator!=(const midnight::Degrees<T>& lhs, const midnight::Radians<T>& rhs)
{
    return !midnight::detail::AngleEqualityHelper<T>::equals(lhs, toRadians(rhs));
}

/**
 * Inequality operator for Angles in degrees and radians.  Part of the equality operator pack for 
 * Angles, both angles in Degrees and Radians are comparable through implicit unit conversions, meaning 
 * that the same angle represented in both degrees and radians will be equal.
 * 
 * @param lhs the first Angle to compare
 * 
 * @param rhs the second Angle to compare
 * 
 * @return true if the two angles are not equal, otherwise false
 * 
 */
template<typename T>
inline bool operator!=(const midnight::Radians<T>& lhs, const midnight::Degrees<T>& rhs)
{
    return midnight::detail::AngleEqualityHelper<T>::equals(lhs, toRadians(rhs));
}

#endif
