
#include "Terrain.hpp"

namespace midnight
{
    
    template<typename T>
    Terrain<T>::Terrain(const std::string& heightmapFile, const std::string& texturemapFile, T verticalScale, T horizontalScale) : 
        verticalScale(verticalScale), 
        horizontalScale(horizontalScale), 
        heightmap(io::loadHeightmap(heightmapFile)), 
        texture(io::loadTexture(texturemapFile)), 
        program(VertexShader(VERTEX_SHADER_SRC), FragmentShader(FRAGMENT_SHADER_SRC))
    {
            std::vector<uint32_t> _indexData;
            _indexData.resize(heightmap.getWidth() * heightmap.getHeight() * 6);
            std::size_t ptr = 0;
            for(uint32_t i = 0; i < heightmap.getWidth() - 1; ++i)
            {
                for(uint32_t j = 0; j < heightmap.getHeight() - 1; ++j)
                {
                    _indexData[ptr++] = static_cast<uint32_t>(j * heightmap.getWidth() + i);
                    _indexData[ptr++] = static_cast<uint32_t>((j + 1) * heightmap.getWidth() + i);
                    _indexData[ptr++] = static_cast<uint32_t>(j * heightmap.getWidth() + i+ 1);

                    _indexData[ptr++] = static_cast<uint32_t>(j * heightmap.getWidth() + i+ 1);
                    _indexData[ptr++] = static_cast<uint32_t>((j + 1) * heightmap.getWidth() + i);
                    _indexData[ptr++] = static_cast<uint32_t>((j + 1) * heightmap.getWidth() + i+ 1);

                }
            }

            std::vector<T> _vertexData;
            constexpr std::size_t DATA_COUNT = 8;
            _vertexData.resize(heightmap.getWidth() * heightmap.getHeight() * DATA_COUNT);
            for(std::size_t i = 0; i < heightmap.getWidth(); ++i)
            {
                for(std::size_t j = 0; j < heightmap.getHeight(); ++j)
                {

                    std::size_t index = j * heightmap.getWidth() + i;

                    /// Positions
                    _vertexData[DATA_COUNT * index + 0] = (T)i - (T)((T)heightmap.getWidth() / 2.0f);
                    _vertexData[DATA_COUNT * index + 1] = -static_cast<T>(heightmap[index * 4]) / 255.0f * verticalScale;
                    _vertexData[DATA_COUNT * index + 2] = (T)j - (T)((T)heightmap.getHeight() / 2.0f);

                    /// Texture Coordinates
                    _vertexData[DATA_COUNT * index + 3] = static_cast<T>(i) / static_cast<T>(heightmap.getWidth());
                    _vertexData[DATA_COUNT * index + 4] = static_cast<T>(j) / static_cast<T>(heightmap.getHeight());
                }
            }

            for(std::size_t i = 0; i < _indexData.size(); i += 3)
            {
                Point3F p0(_vertexData[DATA_COUNT * _indexData[i + 0] + 0], _vertexData[DATA_COUNT * _indexData[i + 0] + 1], _vertexData[DATA_COUNT * _indexData[i + 0] + 2]);
                Point3F p1(_vertexData[DATA_COUNT * _indexData[i + 1] + 0], _vertexData[DATA_COUNT * _indexData[i + 1] + 1], _vertexData[DATA_COUNT * _indexData[i + 1] + 2]);
                Point3F p2(_vertexData[DATA_COUNT * _indexData[i + 2] + 0], _vertexData[DATA_COUNT * _indexData[i + 2] + 1], _vertexData[DATA_COUNT * _indexData[i + 2] + 2]);

                Vector3F v0(p0 - p1);
                Vector3F v1(p0 - p2);

                Vector3F normal = cross(v0, v1).normalize();

                _vertexData[DATA_COUNT * _indexData[i + 0] + 5] += normal[0];
                _vertexData[DATA_COUNT * _indexData[i + 0] + 6] += normal[1];
                _vertexData[DATA_COUNT * _indexData[i + 0] + 7] += normal[2];

                _vertexData[DATA_COUNT * _indexData[i + 1] + 5] += normal[0];
                _vertexData[DATA_COUNT * _indexData[i + 1] + 6] += normal[1];
                _vertexData[DATA_COUNT * _indexData[i + 1] + 7] += normal[2];

                _vertexData[DATA_COUNT * _indexData[i + 2] + 5] += normal[0];
                _vertexData[DATA_COUNT * _indexData[i + 2] + 6] += normal[1];
                _vertexData[DATA_COUNT * _indexData[i + 2] + 7] += normal[2];
            }

       this->vertexData.reset(new StaticDrawTriangleBuffer<float>(_vertexData));
       this->indexBuffer.reset(new StaticDrawIndexBuffer<uint32_t>(_indexData));

        this->vertexData->addAttributePointer("position", 3, GL_FLOAT, GL_FALSE, DATA_COUNT * 4, reinterpret_cast<GLvoid*>(0));
        this->vertexData->addAttributePointer("uv", 2, GL_FLOAT, GL_FALSE, DATA_COUNT * 4, reinterpret_cast<GLvoid*>(12));
        this->vertexData->addAttributePointer("normal", 3, GL_FLOAT, GL_FALSE, DATA_COUNT * 4, reinterpret_cast<GLvoid*>(20));
    }

    template<typename T>
    void Terrain<T>::render(const Camera& camera)
    {
        this->AbstractSceneGraphNode::render(camera);
        program.setUniform("ambient_color", ambientLighting.getColor());
        program.setUniform("sun_position", Tuple4F(0.0f, 100.0f, 1.0f, 1.0f));
        program.setUniform("sun_color", Tuple4F(1.0f, 1.0f, 0.0f, 1.0f));
        program.setUniform("offset", (Tuple3F)camera.getPosition());
        program.setMatrixUniform("projection", camera.getProjection());
        program.setMatrixUniform("orientation", camera.getOrientation());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
        this->program.bind();

        this->indexBuffer->bind();
        this->vertexData->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(heightmap.getWidth() * heightmap.getHeight() * 6), GL_UNSIGNED_INT, (GLvoid*)0);
        this->vertexData->unbind();
        this->indexBuffer->unbind();
        this->program.unbind();

    }
    
    template<typename T>
    const Heightmap& Terrain<T>::getHeightmap() const
    {
        return heightmap;
    }

    template<typename T>
    bool Terrain<T>::isPickable()
    {
        return true;
    }
    
    template<typename T>
    void Terrain<T>::setAmbience(const AmbientLight<float>& ambience)
    {
        this->ambientLighting = ambience;
    }
    
    template<typename T>
    const std::string Terrain<T>::VERTEX_SHADER_SRC = 
        "#version 130\n\
        in vec3 position;\n\
        in vec2 uv;\n\
        in vec3 normal;\n\
\
        out vec2 uv_out;\n\
        out vec4 rgba_out;\n\
\
        uniform vec4 ambient_color;\n\
        uniform vec4 sun_position;\n\
        uniform vec4 sun_color;\n\
\
        uniform vec3 offset;\n\
        uniform mat4 projection;\n\
        uniform mat4 orientation;\n\
\
        void main()\n\
        {\n\
            vec4 cameraPos = vec4(position.x, position.y, position.z, 1.0) + vec4(offset.x, offset.y, offset.z, 0.0);\n\
            cameraPos *= orientation;\n\
            cameraPos *= projection;\n\
            vec4 _normal = vec4(normal.x, normal.y, normal.z, 1.0);\n\
            _normal *= orientation;\n\
            vec4 pos = sun_position;\n\
            vec4 angle = normalize(pos - cameraPos);\n\
            gl_Position = cameraPos;\n\
            uv_out = uv;\n\
            float intensity = max(0.5f, dot(_normal, angle));\n\
            rgba_out = normalize(vec4(sun_color.x * intensity, sun_color.y * intensity, sun_color.z * intensity, sun_color.w) * ambient_color);\n\
        }";
    
    template<typename T>
    const std::string Terrain<T>::FRAGMENT_SHADER_SRC = 
        "#version 130\n\
        uniform sampler2D tex0;\n\
        in vec2 uv_out;\n\
        in vec4 rgba_out;\n\
        void main()\n\
        {\n\
            gl_FragColor = normalize(texture2D(tex0, uv_out) * rgba_out);\n\
        }";
}
