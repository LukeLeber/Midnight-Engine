#ifndef MESH_HPP
#define MESH_HPP

#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

#include "Vertex.hpp"

#include "Material.hpp"

namespace midnight
{
    /// Forward Declaration for our friends
    class Mesh;
}

/**
 * Inserts the provided Mesh into the provided output stream
 * 
 * @param stream the output stream to write to
 * 
 * @param mesh the Mesh to insert
 * 
 * @return the provided output stream
 * 
 */

std::ostream& operator<<(std::ostream& stream, const midnight::Mesh& mesh);

/**
 * Inserts the provided Mesh into the provided output stream
 * 
 * @param stream the output stream to write to
 * 
 * @param mesh the Mesh to insert
 * 
 * @return the provided output stream
 * 
 * @note [optimization] this method should be preferred when the provided Mesh is not used by the calling method
 * 
 */

std::ostream& operator<<(std::ostream& stream, midnight::Mesh&& mesh);

/**
 * Extracts a Mesh from the provided input stream
 * 
 * @param stream the input stream to read from
 * 
 * @param mesh the Mesh to populate with the extracted data
 * 
 * @return the provided input stream
 * 
 */

std::istream& operator>>(std::istream& stream, midnight::Mesh& mesh);

namespace midnight
{

    /**
     * A general-purpose static 3D mesh implementation
     * 
     */
    
    class Mesh
    {

        friend std::ostream& operator<<(std::ostream&, const Mesh&);
        friend std::ostream& operator<<(std::ostream&, Mesh&&);
        friend std::istream& operator>>(std::istream&, Mesh&);

      public:
        
        /**
         * A discrete rendering unit
         * 
         */
        struct Renderable
        {
            /// The index of the Material to use in this sub-mesh
            std::size_t materialIndex;
            
            /// The list of indices of this sub-mesh
            std::vector<std::size_t> indices;
            
            Renderable(std::size_t materialIndex) : materialIndex(materialIndex)
            {
                
            }
        };
      private:
        
        std::vector<Vertex32F> vertices;

        /// The Material data of this Mesh
        std::vector<Material> materials;
        
        /// The sub-meshes of this Mesh
        std::vector<Renderable> meshes;
        
      public:
        
        Mesh(const std::vector<Vertex32F>& vertices, const std::vector<midnight::Material>& materials, const std::vector<midnight::Mesh::Renderable>& renderables);

        const std::vector<Vertex32F>& getVertices() const noexcept
        {
            return vertices;
        }
        const std::vector<Renderable> getMeshes() const noexcept
        {
            return meshes;
        }
    };

}

#include "Mesh.inl"
#endif