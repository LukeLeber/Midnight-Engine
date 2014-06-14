namespace midnight
{
    template<typename T, std::size_t W, std::size_t H, std::size_t L>
    const std::vector<T> Skybox<T, W, H, L>::DATA = 
    {
        -static_cast<T>(W), static_cast<T>(H), -static_cast<T>(L), 
        -static_cast<T>(W), -static_cast<T>(H), -static_cast<T>(L),
        static_cast<T>(W), -static_cast<T>(H), -static_cast<T>(L),
        static_cast<T>(W), static_cast<T>(H), -static_cast<T>(L), 
        static_cast<T>(W), static_cast<T>(H), -static_cast<T>(L), 
        static_cast<T>(W), -static_cast<T>(H), -static_cast<T>(L), 
        static_cast<T>(W), -static_cast<T>(H), static_cast<T>(L), 
        static_cast<T>(W), static_cast<T>(H), static_cast<T>(L), 
        -static_cast<T>(W), static_cast<T>(H), static_cast<T>(L),
        -static_cast<T>(W), -static_cast<T>(H), static_cast<T>(L), 
        -static_cast<T>(W), -static_cast<T>(H), -static_cast<T>(L), 
        -static_cast<T>(W), static_cast<T>(H), -static_cast<T>(L), 
        -static_cast<T>(W), static_cast<T>(H), -static_cast<T>(L), 
        static_cast<T>(W), static_cast<T>(H), -static_cast<T>(L), 
        static_cast<T>(W), static_cast<T>(H), static_cast<T>(L), 
        -static_cast<T>(W), static_cast<T>(H), static_cast<T>(L), 
        -static_cast<T>(W), -static_cast<T>(H), static_cast<T>(L), 
        static_cast<T>(W), -static_cast<T>(H), static_cast<T>(L), 
        static_cast<T>(W), -static_cast<T>(H), -static_cast<T>(L), 
        -static_cast<T>(W), -static_cast<T>(H), -static_cast<T>(L), 
        static_cast<T>(W), static_cast<T>(H), static_cast<T>(L), 
        static_cast<T>(W), -static_cast<T>(H), static_cast<T>(L), 
        -static_cast<T>(W), -static_cast<T>(H), static_cast<T>(L), 
        -static_cast<T>(W), static_cast<T>(H), static_cast<T>(L), 
        0.75f, (1.0f / 3.0f),
        0.75f, (2.0f / 3.0f),
        0.5f, (2.0f / 3.0f),
        0.5f, (1.0f / 3.0f),
        0.5f, (1.0f / 3.0f),
        0.5f, (2.0f / 3.0f),
        0.25f, (2.0f / 3.0f),
        0.25f, (1.0f / 3.0f),
        1.0f, (1.0f / 3.0f),
        1.0f, (2.0f / 3.0f),
        0.75f, (2.0f / 3.0f),
        0.75f, (1.0f / 3.0f),
        0.75f, (1.0f / 3.0f),
        0.5f, (1.0f / 3.0f),
        0.5f, 0.0f,
        0.75f, 0.0f,
        0.75f, 1.0f,
        0.5f, 1.0f,
        0.5f, (2.0f / 3.0f),
        0.75f, (2.0f / 3.0f),
        0.25f, (1.0f / 3.0f),		
        0.25f, (2.0f / 3.0f),		
        0.0f, (2.0f / 3.0f),	
        0.0f, (1.0f / 3.0f)
    };

    template<typename T, std::size_t W, std::size_t H, std::size_t L>
    const std::string Skybox<T, W, H, L>::VERTEX_SHADER_SRC = 
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

    template<typename T, std::size_t W, std::size_t H, std::size_t L>
    const std::string Skybox<T, W, H, L>::FRAGMENT_SHADER_SRC = 
        "#version 130\n\
        in vec2 uv_out;\n\
        uniform sampler2D tex;\n\
        void main()\n\
        {\n\
            gl_FragColor = texture2D(tex, uv_out);\n\
        }";

    template<typename T, std::size_t W, std::size_t H, std::size_t L>
    Skybox<T, W, H, L>::Skybox(std::shared_ptr<SceneGraphNode> parent, const Texture& texture) : 
        AbstractSceneGraphNode(), 
        parent(parent), 
        program(VertexShader(VERTEX_SHADER_SRC), FragmentShader(FRAGMENT_SHADER_SRC)), 
        texture(texture), 
        vbo(DATA)
    {
        vbo.addAttributePointer("position", 3, GL_FLOAT, GL_FALSE, 0, 0);
        vbo.addAttributePointer("uv_in", 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>(48 * 6));
    }

    template<typename T, std::size_t W, std::size_t H, std::size_t L>
    void Skybox<T, W, H, L>::render(const Camera& camera)
    {
   		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
        
		program.bind();
		program.setUniform("offset", camera.getPosition());
		program.setMatrixUniform("projection", camera.getProjection());
		program.setMatrixUniform("orientation", camera.getOrientation());
		vbo.bind();
		glDrawArrays(GL_QUADS, 0, 24);
		vbo.unbind();
		program.unbind();
        this->AbstractSceneGraphNode::render(camera);
    }

    template<typename T, std::size_t W, std::size_t H, std::size_t L>
    inline bool Skybox<T, W, H, L>::isPickable()
    {
        return false;
    }
}
