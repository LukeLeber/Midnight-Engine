namespace midnight
{
    
    namespace detail
    {
        struct IndexBufferBindHelper
        {
            GLint preserved;
            IndexBufferBindHelper(GLuint handle)
            {
                glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER, &preserved);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
            }
            
            ~IndexBufferBindHelper()
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, preserved);
            }
        };
    }
    
    template<typename T, GLenum Usage>
    IndexBuffer<T, Usage>::IndexBuffer(const std::vector<T>& data) : 
        data(data)
    {
        glGenBuffers(1, &handle);
        detail::IndexBufferBindHelper binder(handle);
        /// Can set GL_OUT_OF_MEMORY
        /// https://www.opengl.org/sdk/docs/man4/xhtml/glBufferData.xml
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], Usage);

        if(glGetError() == GL_OUT_OF_MEMORY)
        {
            throw ResourceException("Unable to allocate GPU memory for VertexBuffer");
        }
    }
    
    template<typename T, GLenum Usage>
    IndexBuffer<T, Usage>::IndexBuffer(std::vector<T>&& data) : 
        data(data)
    {
        glGenBuffers(1, &handle);
        detail::IndexBufferBindHelper binder(handle);
        /// Can set GL_OUT_OF_MEMORY
        /// https://www.opengl.org/sdk/docs/man4/xhtml/glBufferData.xml
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], Usage);

        if(glGetError() == GL_OUT_OF_MEMORY)
        {
            throw ResourceException("Unable to allocate GPU memory for VertexBuffer");
        }
    }
    
    template<typename T, GLenum Usage>
    void IndexBuffer<T, Usage>::bind()
    {
           GLint programHandle;
            /// Call should never fail
            glGetIntegerv(GL_CURRENT_PROGRAM, &programHandle);
            if(programHandle == 0)
            {
                throw midnight::glsl::BindException("A program must first be bound before binding an IndexBuffer");
            }
            /// Call should never fail
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    }
    
    template<typename T, GLenum Usage>
    void IndexBuffer<T, Usage>::unbind()
    {
           /// Call should never fail
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    template<typename T, GLenum Usage>
    IndexBuffer<T, Usage>::~IndexBuffer()
    {
        /// Call should never fail
        glDeleteBuffers(1, &handle);
    }
    
}