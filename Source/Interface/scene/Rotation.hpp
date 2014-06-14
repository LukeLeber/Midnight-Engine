#ifndef ROTATION_HPP
#define ROTATION_HPP

#include "SceneGraphNode.hpp"

namespace midnight
{
    template<typename T>
    class Rotation : public SceneGraphNode
    {
        Quaternion<T> rotation;
        
      public:
          
        Rotation(Radians<T> angle, Vector<T, 3> axis) : 
            rotation(axis, angle)
        {
            
        }
            
        virtual void render(const Camera& camera)
        {
            Camera rotated(camera);
            rotated.rotate(rotation);
            for(const auto& child : getChildren())
            {
                child->render(rotated);
            }
        }

        virtual bool isPickable()
        {
            return false;
        }
    };
}

#endif