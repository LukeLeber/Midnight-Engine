#ifndef MESH_NODE_HPP
#define MESH_NODE_HPP

#include "AbstractSceneGraphNode.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "Mesh.hpp"
#include "Vertex.hpp"
#include "Program.hpp"
#include "constexpr_math.hpp"

#include <memory>

namespace midnight
{
    class MeshNode : public AbstractSceneGraphNode
    {
        
        Mesh mesh;
        
        std::unique_ptr<StaticDrawTriangleBuffer<float>> buffer;
        std::vector<std::pair<std::size_t, std::unique_ptr<StaticDrawIndexBuffer<std::size_t>>>> indexBuffers;
        
        Program program;
        const static std::string VERTEX_SHADER_SRC;
        const static std::string FRAGMENT_SHADER_SRC;
        
      public:
        
        MeshNode(const Mesh& mesh) : mesh(mesh), program(VertexShader(VERTEX_SHADER_SRC), FragmentShader(FRAGMENT_SHADER_SRC))
        {
            std::vector<float> data;
            

            data.resize(mesh.getVertices().size() * 8);
            
            for(auto entry : mesh.getVertices())
            {
                data.push_back(entry.getPosition()[0]);
                data.push_back(entry.getPosition()[1]);
                data.push_back(entry.getPosition()[2]);
                data.push_back(entry.getNormal()[0]);
                data.push_back(entry.getNormal()[1]);
                data.push_back(entry.getNormal()[2]);
                data.push_back(entry.getTexCoord()[0]);
                data.push_back(entry.getTexCoord()[1]);
            }
            
            
            for(auto renderable : mesh.getMeshes())               
            {
                std::vector<std::size_t> indices;
                for(auto index : renderable.indices)
                    indices.push_back(index);
                indexBuffers.push_back(std::make_pair(renderable.materialIndex, std::unique_ptr<StaticDrawIndexBuffer<std::size_t>>(new StaticDrawIndexBuffer<std::size_t>(indices))));
            }
            
            buffer.reset(new StaticDrawTriangleBuffer<float>(data));
            
            buffer->addAttributePointer("position", 3, GL_FLOAT, GL_FALSE, 0, 0);
            buffer->addAttributePointer("uv_in", 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>(48 * 6));
        }

        MeshNode(Mesh&& mesh);
        
        virtual void render(const Camera& camera) override
        {
            /// Render myself
/*   		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);*/
        
		program.bind();
		program.setUniform("offset", camera.getPosition());
		program.setMatrixUniform("projection", camera.getProjection());
		program.setMatrixUniform("orientation", camera.getOrientation());
		buffer->bind();
        glDrawElements(
     GL_TRIANGLES, 
     static_cast<GLsizei>(mesh.getMeshes()[0].indices.size()),
     GL_UNSIGNED_INT, 
     (void*)0);
        // TODO: Vertex Class with equ-ops
//		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh.getMeshes()[0].indices.size()));
		buffer->unbind();
		program.unbind();
            
            /// Render my children
            this->AbstractSceneGraphNode::render(camera);
            
        }
        
        virtual bool isPickable() override
        {
            return true;
        }
    };
    
    const std::string MeshNode::VERTEX_SHADER_SRC = 
        "#version 130\n\
        in vec3 position;\n\
        in vec2 uv_in;\n\
        out vec2 uv_out;\n\
        uniform vec3 offset;\n\
        uniform mat4 projection;\n\
        uniform mat4 orientation;\n\
        void main()\n\
        {\n\
            vec4 cameraPos = vec4(position.x, position.y, position.z, 1.0) + vec4(offset.x, offset.y, offset.z, 0.0);\n\
            cameraPos *= orientation;\n\
            cameraPos *= projection;\n\
            gl_Position = cameraPos;\n\
            uv_out = uv_in;\n\
        }";

    const std::string MeshNode::FRAGMENT_SHADER_SRC = 
        "#version 130\n\
        in vec2 uv_out;\n\
        uniform sampler2D tex;\n\
        void main()\n\
        {\n\
            gl_FragColor = texture2D(tex, uv_out);\n\
        }";
    
}

#endif