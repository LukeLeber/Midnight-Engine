/**
 * This file is protected under the KILLGPL License.
 * 
 * For more information visit www.midnightengine.com/license
 *  
 * @version 1.1
 *      4/22/2014 - initial draft
 * 
 * @since 1.0
 * 
 * @author Luke A. Leber <LukeLeber@gmail.com>
 * 
 */
#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <vector>

#include "Program.hpp"
#include "AbstractSceneGraphNode.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"

namespace midnight
{

/**
 * A type of scene-graph node that holds a skybox.
 * 
 * @tparam T the type of unit used in this Skybox
 * 
 * @tparam W the width of this Skybox
 * 
 * @tparam H the height of this Skybox
 * 
 * @tparam L the length of this Skybox
 * 
 * @see SceneGraphNode
 */
template<typename T, std::size_t W, std::size_t H, std::size_t L>
class Skybox : public AbstractSceneGraphNode
{
    /// The static vertex information of this type of Skybox
    static const std::vector<T> DATA;
    
    /// The vertex Shader that this Skybox will be rendered under
    static const std::string VERTEX_SHADER_SRC;
    
    /// The fragment Shader that this Skybox will be rendered under
    static const std::string FRAGMENT_SHADER_SRC;
    
    /// TODO: Virtual base class?
    std::shared_ptr<SceneGraphNode> parent;
    
    /// The Program that this Skybox will be rendered by
    Program program;
    
    /// The Texture of this Skybox
    Texture texture;
    
    /// The VertexBuffer object of this Skybox
    midnight::StaticDrawQuadBuffer<T> vbo;
        
  public:

    /**
     * Constructs a Skybox with the provided parent and texture
     * 
     * @param parent the parent node of this Skybox
     * 
     * @param textureFile the image file for the texture of this Skybox
     * 
     */
    Skybox(std::shared_ptr<SceneGraphNode> parent, const Texture& textureFile);

    /**
     * Renders this Skybox
     * 
     * @param camera the Camera that is being used in this scene
     * 
     */
    void render(const Camera& camera) override;

    /**
     * Skyboxes are not pickable.
     * 
     * @return Always returns false..
     * 
     */
    bool isPickable() final;

    /**
     * Default destructor
     * 
     */
    ~Skybox() = default;
};

}

#include "Skybox.inl"

#endif
