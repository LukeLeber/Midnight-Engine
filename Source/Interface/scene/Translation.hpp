#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "SceneGraphNode.hpp"
#include "Vector.hpp"

namespace midnight
{
    template<typename T>
    class Translation : public SceneGraphNode
    {
        Vector<T, 3> translation;
        
      public:
        
        Translation(T x, T y, T z) : 
            translation(x, y, z)
        {
            
        }
        
        virtual void render(const Camera& camera)
        {
            Camera translated(camera);
            translated.translate(translation);
            for(const auto& child : getChildren())
            {
                child->render(translated);
            }
        }

        virtual bool isPickable()
        {
            return false;
        }
    };
}

#endif