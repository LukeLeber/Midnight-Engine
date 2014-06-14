#ifndef POSITIONED_LIGHT_HPP
#    define POSITIONED_LIGHT_HPP

#    include "Light.hpp"
#    include "Point.hpp"

template<typename T>
class PositionedLight : Light<T>
{
    Point3F position;

  public:

    PositionedLight(const Color<T, 3>& color, const Point<T, 3>& position);
    PositionedLight(Color<T, 3>&& color, Point<T, 3>&& position);
    PositionedLight(T r, T g, T b, T x, T y, T z);

    const Point<T, 3>& getPosition() const;
    Point<T, 3>& getPosition();

    void setPosition(const Point<T, 3>& position);
    void setPosition(Point<T, 3>&& position);
    void setPosition(T x, T y, T z);

};

#    include "PositionedLight.inl"

#endif