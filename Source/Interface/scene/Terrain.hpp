#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include <memory>

#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"

#include "Heightmap.hpp"
#include "AbstractSceneGraphNode.hpp"
#include "TextureProvider.hpp"
#include "Program.hpp"

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "Vector.hpp"

namespace midnight
{
    template<typename T>
    class Terrain : public AbstractSceneGraphNode
    {
        /// The vertex shader source for static Terrains
        static const std::string VERTEX_SHADER_SRC;
        
        /// The fragment shader source for static Terrains
        static const std::string FRAGMENT_SHADER_SRC;
        
        /// The vertical scale of this Terrain
        T verticalScale;
        
        /// The horizontal scale of this Terrain
        T horizontalScale;
        
        /// The height samples of this Terrain
        Heightmap heightmap;
        
        /// The texture of this Terrain
        Texture texture;
        
        /// The Program to render this Terrain with
        Program program;

        /// A triangle buffer that holds the vertex data of this Terrain
        std::unique_ptr<StaticDrawTriangleBuffer<T>> vertexData;
        
        /// The indices of this triangle buffer to render
        std::unique_ptr<StaticDrawIndexBuffer<uint32_t>> indexBuffer;
        
        /// The ambient lighting of this Terrain
        AmbientLight<float> ambientLighting;
        
        /// The directional lighting of this Terrain
        DirectionalLight<float> directionalLighting;
        
      public:

        Terrain(const std::string& heightmapFile, const std::string& texturemapFile, T verticalScale = 1.0f, T horizontalScale = 1.0f);
        
        void render(const Camera& camera) override;
            
        const Heightmap& getHeightmap() const;

        virtual bool isPickable() override;
        
        void setAmbience(const AmbientLight<float>& ambience);
        
    };
}

#include "Terrain.inl"

#endif
