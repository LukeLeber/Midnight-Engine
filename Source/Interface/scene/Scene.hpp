#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "Camera.hpp"
#include "Program.hpp"
#include "SceneGraphNode.hpp"

namespace midnight
{

template<typename T>
class Scene
{
    
    std::vector<std::shared_ptr<SceneGraphNode>> sceneGraph;
    
//    Program program;
    
    Camera camera;
   
  public:

    Scene(const Camera& camera) : 
        camera(camera)
    {
        
    }
        
    void add(std::shared_ptr<SceneGraphNode> node)
    {
        sceneGraph.push_back(node);
    }

    void render(const Camera& camera)
    {
        for(const auto& node : sceneGraph)
        {
            node->render(camera);
        }
    }
};

}

#endif
