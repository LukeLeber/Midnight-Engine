
#include "Quaternion.hpp"

namespace midnight
{
    
inline Camera::Camera(float fieldOfView, float aspectRatio, float zNear, float zFar) noexcept : 
    fieldOfView(fieldOfView),
    aspectRatio(aspectRatio),
    zNear(zNear),
    zFar(zFar)
{
    
}

inline void Camera::reset()
{
    orientation = Quaternion<float>();
}

inline Matrix4x4F Camera::getProjection() const noexcept
{
    return Matrix4x4F::PERSPECTIVE(fieldOfView, zNear, zFar);
}

inline Matrix4x4F Camera::getOrientation() const noexcept
{
    return orientation.operator Matrix<float,4,4>();
}

inline void Camera::rotate(const Vector3F& axis, const Radians<float>& angle)
{
    this->orientation *= Quaternion<float>(axis, angle);
    this->orientation.normalize();
}

inline void Camera::rotate(const Quaternion<float>& quaternion)
{
    this->orientation *= quaternion;
    this->orientation.normalize();
}

inline const Point3F& Camera::getPosition() const noexcept
{
    return position;
}

inline Point3F& Camera::getPosition() noexcept
{
    return position;
}

inline void Camera::setPosition(const Point3F& position) noexcept
{
    this->position = position;
}

inline void Camera::translate(const Vector3F& translation) noexcept
{
    this->position += translation;
}

inline float Camera::getFieldOfView() const noexcept
{
    return fieldOfView;
}

inline void Camera::setFieldOfView(float fieldOfView) noexcept
{
    this->fieldOfView = fieldOfView;
}

inline float Camera::getAspectRatio() const noexcept
{
    return this->aspectRatio;
}

inline void Camera::setAspectRatio(float aspectRatio) noexcept
{
    this->aspectRatio = aspectRatio;
}

inline float Camera::getNearClippingPlane() const noexcept
{
    return this->zNear;
}

inline void Camera::setNearClippingPlane(float zNear) noexcept
{
    this->zNear = zNear;
}

inline float Camera::getFarClippingPlane() const noexcept
{
    return this->zFar;
}

inline void Camera::setFarClippingPlane(float zFar) noexcept
{
    this->zFar = zFar;
}
   
}
