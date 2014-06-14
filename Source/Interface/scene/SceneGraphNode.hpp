#ifndef SCENEGRAPH_NODE_HPP
#define SCENEGRAPH_NODE_HPP

#include <memory>
#include <vector>

#include "Camera.hpp"

namespace midnight
{

    class SceneGraphNode
    {

        
        
      protected:

        virtual const std::vector<std::shared_ptr<SceneGraphNode>>& getChildren() const = 0;

      public:

        SceneGraphNode() = default;

        virtual void render(const Camera& camera) = 0;

        virtual void add(std::shared_ptr<SceneGraphNode> child) = 0;

        virtual bool isPickable() = 0;

        virtual ~SceneGraphNode() = default;
    };
    
}

#endif
