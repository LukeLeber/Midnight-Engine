#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <functional>
#include "Color.hpp"

namespace midnight
{

    template<typename T>
    class AmbientLight
    {
        Color<T, 4> color;

      public:
        AmbientLight(const Color<T, 4>& color);
        AmbientLight(Color<T, 4>&& color);
        AmbientLight(T r, T g, T b, T a);
        AmbientLight();

        const Color<T, 4>& getColor() const;
        Color<T, 4>& getColor();


        void setColor(const Color<T, 4>& color);
        void setColor(Color<T, 4>&& color);
        void setColor(T r, T g, T b, T a);
        
    };

}

#include "AmbientLight.inl"

#endif