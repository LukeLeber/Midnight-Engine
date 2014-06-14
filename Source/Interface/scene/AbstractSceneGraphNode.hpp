#ifndef ABSTRACT_SCENE_NODE_HPP
#define ABSTRACT_SCENE_NODE_HPP

#include "SceneGraphNode.hpp"

namespace midnight
{
    class AbstractSceneGraphNode : public SceneGraphNode
    {
        /// The children of this node
        std::vector<std::shared_ptr<SceneGraphNode>> children;

        protected:

          /**
           * Retrieves the children of this node
           * 
           * @return the children of this node
           * 
           */
          const std::vector<std::shared_ptr<SceneGraphNode>>& getChildren() const override;
    
        public:

          /**
           * Default constructor
           * 
           */
          AbstractSceneGraphNode() = default;

          /**
           * Adds the provided child to this node
           * 
           * @param child the child node to add
           * 
           */
          virtual void add(std::shared_ptr<SceneGraphNode> child) override;

          /**
           * Renders this node
           * 
           * @param camera the Camera to render this node with
           * 
           */
          virtual void render(const Camera& camera) override;

          /**
           * Default virtual destructor
           * 
           */
          virtual ~AbstractSceneGraphNode() = default;
    };
}

#include "AbstractSceneGraphNode.inl"

#endif