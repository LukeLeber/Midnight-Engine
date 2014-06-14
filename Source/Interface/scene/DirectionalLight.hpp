#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Color.hpp"
#include "Vector.hpp"

namespace midnight
{

    template<typename T>
    class DirectionalLight
    {
        Color<T, 4> color;
        Vector<T, 3> direction;

      public:

        DirectionalLight(const Color<T, 3>& color, const Vector<T, 3>& direction);
        DirectionalLight(Color<T, 3>&& color, Vector<T, 3>&& direction);
        DirectionalLight(T r, T g, T b, T x, T y, T z);
        DirectionalLight();

        const Vector<T, 3>& getDirection() const;
        Vector<T, 3>& getDirection();

        void setDirection(const Vector<T, 3>& direction);
        void setDirection(Vector<T, 3>&& direction);
        void setDirection(T x, T y, T z);
        
    };

}

#include "DirectionalLight.inl"

#endif
