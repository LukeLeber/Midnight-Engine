#include "constexpr_math.hpp"

template<typename T>
inline std::istream& operator>>(std::istream& stream, midnight::Quaternion<T>& quaternion)
{
    return stream >> quaternion.axis >> quaternion.angle;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const midnight::Quaternion<T>& quaternion)
{
    return stream << quaternion.axis << quaternion.angle;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, midnight::Quaternion<T>&& quaternion)
{
    return stream << quaternion.axis << quaternion.angle;
}

template<typename T>
inline bool operator==(const midnight::Quaternion<T>& lhs, const midnight::Quaternion<T>& rhs)
{
    return lhs.axis == rhs.axis && operator==(lhs.angle, rhs.angle);
}

template<typename T>
inline bool operator!=(const midnight::Quaternion<T>& lhs, const midnight::Quaternion<T>& rhs)
{
    return lhs.axis != rhs.axis || operator==(lhs.angle, rhs.angle);
}

template<typename T>
inline midnight::Quaternion<T> operator*(const midnight::Quaternion<T>& lhs, const midnight::Quaternion<T>& rhs)
{
    return (midnight::Quaternion<T>(lhs)) *= rhs;
}

template<typename T>
inline midnight::Quaternion<T> operator*(midnight::Quaternion<T>&& lhs, midnight::Quaternion<T>&& rhs)
{
    return (midnight::Quaternion<T>(std::move(lhs))) *= std::move(rhs);
}

namespace midnight
{


    template<typename T>
    inline Quaternion<T>::Quaternion(const Vector<T, 3>& axis, const Radians<T>& angle) : 
        axis(axis[0] * std::sin(angle / 2), axis[1] * std::sin(angle / 2), axis[2] * std::sin(angle / 2)),
        angle(std::cos(angle / 2))
    {
        
    }

    template<typename T>
    inline Quaternion<T>::Quaternion(Vector<T, 3>&& axis, Radians<T>&& angle) : 
        axis(std::move(axis) * std::sin(angle / 2)),
        angle(std::cos(std::move(angle) / 2))
    {
        
    }
    
    template<typename T>
    inline Quaternion<T>::Quaternion(const Vector<T, 3>& axis, const Degrees<T>& angle) : 
        axis(axis * std::sin(toRadians(angle) / 2)),
        angle(std::cos(toRadians(angle) / 2))
    {
        
    }
    
    template<typename T>
    inline Quaternion<T>::Quaternion(Vector<T, 3>&& axis, Degrees<T>&& angle) : 
        axis(axis * std::sin(toRadians(angle) / 2)),
        angle(std::cos(toRadians(angle) / 2))
    {
        
    }
    
    template<typename T>
    inline constexpr Quaternion<T>::Quaternion() noexcept : 
        axis(0.0f, 0.0f, 0.0f),
        angle(std::cos(0.5f))
    {
        
    }

    template<typename T>
    inline const Vector<T, 3>& Quaternion<T>::getAxis() const noexcept
    {
        return axis;
    }
        
    template<typename T>
    inline const Radians<T>& Quaternion<T>::getAngle() const noexcept
    {
        return angle;
    }

    template<typename T>
    void Quaternion<T>::normalize() noexcept
    {
        this->axis.normalize();
    }

    template<typename T>
    Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& rhs) noexcept
    {
        T angle = this->angle * rhs.angle - this->axis[0] * rhs.axis[0] - this->axis[1]  * rhs.axis[1] - this->axis[2] * rhs.axis[2];

        this->axis.set(this->angle * rhs.axis[0] + this->axis[0] * rhs.angle + this->axis[1] * rhs.axis[2] - this->axis[2] * rhs.axis[1],
                       this->angle * rhs.axis[1] + this->axis[1] * rhs.angle + this->axis[2] * rhs.axis[0] - this->axis[0] * rhs.axis[2], 
                       this->angle * rhs.axis[2] + this->axis[2] * rhs.angle + this->axis[0] * rhs.axis[1] - this->axis[1] * rhs.axis[0]);
        this->angle.set(angle);
        return *this;
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator*=(Quaternion<T>&& rhs) noexcept
    {
        T angle = this->angle * rhs.angle- this->axis[0] * rhs.axis[0] - this->axis[1]  * rhs.axis[1] - this->axis[2] * rhs.axis[2];

        this->axis.set(this->angle * rhs.axis[0] + this->axis[0] * rhs.angle + this->axis[1] * rhs.axis[2] - this->axis[2] * rhs.axis[1],
                       this->angle * rhs.axis[1] + this->axis[1] * rhs.angle + this->axis[2] * rhs.axis[0] - this->axis[0] * rhs.axis[2], 
                       this->angle * rhs.axis[2] + this->axis[2] * rhs.angle + this->axis[0] * rhs.axis[1] - this->axis[1] * rhs.axis[0]);
        this->angle.set(angle);
        return *this;
    }
    
    template<typename T>
    Quaternion<T>::operator Matrix<T, 4, 4>() const noexcept
    {
        return Matrix<T, 4, 4>(
            (1) - (2 * this->axis[1] * this->axis[1]) - (2 * this->axis[2] * this->axis[2]), (2 * this->axis[0] * this->axis[1]) - (2 * this->angle * this->axis[2]), (2 * this->axis[0] * this->axis[2]) + (2 * this->angle * this->axis[1]), 0,        
            (2 * this->axis[0] * this->axis[1]) + (2 * this->angle * this->axis[2]), (1) - (2 * this->axis[0] * this->axis[0]) - (2 * this->axis[2] * this->axis[2]), (2 * axis[1] * this->axis[2]) - (2 * this->angle * this->axis[0]), 0,
            (2 * this->axis[0] * this->axis[2]) - (2 * this->angle * this->axis[1]), (2 * this->axis[1] * this->axis[2]) + (2 * this->angle * this->axis[0]), (1) - (2 * this->axis[0] * this->axis[0]) - (2 * this->axis[1] * this->axis[1]), 0, 
            0, 0, 0, 1);
    }
    
}