#ifndef VERTEX_BUFFER_HPP
#    define VERTEX_BUFFER_HPP

/// Puke if clang is not used
static_assert(__clang__, "Your compiler is not supported.");

#    include <string>
#    include <vector>

namespace midnight
{

/**
 * An encapsulation of a Vertex Buffer Object (https://www.opengl.org/wiki/Vertex_Specification#Vertex_Buffer_Object)
 * 
 * Various built-in types of VBOs are provided as template aliases including:
 * <ul>
 *  <li>StreamDrawVertexBuffer</li>
 *  <li>StreamReadVertexBuffer</li>
 *  <li>StreamCopyVertexBuffer</li>
 *  <li>StaticDrawVertexBuffer</li>
 *  <li>StaticReadVertexBuffer</li>
 *  <li>StaticCopyVertexBuffer</li>
 *  <li>DynamicDrawVertexBuffer</li>
 *  <li>DynamicReadVertexBuffer</li>
 *  <li>DynamicCopyVertexBuffer</li>
 * </ul>
 * 
 * Please refer to https://www.opengl.org/sdk/docs/man4/xhtml/glBufferData.xml to decide which to use.
 * 
 * More built-in types shall be added to this API as the opengl specification evolves.
 * 
 */
template<typename T>
class VertexBuffer
{
  public:

    /**
     * Constructs a VertexBuffer from the provided array of data
     * 
     * @param data the array of data to build this VertexBuffer with
     * 
     */
    VertexBuffer(const std::vector<T>& data);

    /**
     * Constructs a VertexBuffer from the provided array of data
     * 
     * @param data the array of data to build this VertexBuffer with
     * 
     */
    VertexBuffer(std::vector<T>&& data);

    /**
     * Retrieves the number of vertices contained in this VertexBuffer
     * 
     * @return the number of vertices contained in this VertexBuffer
     * 
     */
    virtual std::size_t vertexCount() = 0;

    /**
     * Sets the data contained in this VertexBuffer
     * 
     * @param data the new data
     * 
     */
    virtual void setVertexData(std::vector<T>&& data) = 0;

    /**
     * Sets the data contained in this VertexBuffer
     * 
     * @param data the new data
     * 
     */
    virtual void setVertexData(const std::vector<T>& data) = 0;

    /**
     * Binds this VertexBuffer to the implementation based on the currently bound program
     * 
     * @throws BindException if there is currently no program bound to the implementation
     * 
     */
    virtual void bind() = 0;

    /**
     * Unbinds this VertexBuffer from the implementation
     * 
     */
    virtual void unbind() noexcept = 0;

    /**
     * Resets all of the attribute pointers that are applied to this VertexBuffer
     * 
     */
    virtual void resetAttributes() noexcept = 0;

    /**
     * Adds an attribute pointer to this VertexBuffer
     * 
     * @param name the name of the attribute
     * 
     * @param size the number of elements that the attribute is composed of
     * 
     * @param type the type of element that the attribute is composed of
     * 
     * @param normalized should the values of this VertexBuffer be normalized?
     * 
     * @param stride the distance between the interleaved data sets in this VertexBuffer
     * 
     * @param offset the offset from the beginning of this VertexBuffer to find the first element at
     * 
     */
    virtual void addAttributePointer(const std::string& name,
            GLint size,
            GLenum type,
            GLboolean normalized,
            GLsizei stride,
            const GLvoid* offset) = 0;

    /**
     * Adds an integer attribute pointer to this VertexBuffer
     * 
     * @param name the name of the attribute
     * 
     * @param size the number of elements that the attribute is composed of
     * 
     * @param type the type of element that the attribute is composed of
     * 
     * @param stride the distance between the interleaved data sets in this VertexBuffer
     * 
     * @param offset the offset from the beginning of this VertexBuffer to find the first element at
     * 
     */
    virtual void addAttributeIPointer(const std::string& name,
            GLint size,
            GLenum type,
            GLsizei stride,
            const GLvoid* offset) = 0;

    /**
     * Adds an long floating point attribute pointer to this VertexBuffer
     * 
     * @param name the name of the attribute
     * 
     * @param size the number of elements that the attribute is composed of
     * 
     * @param stride the distance between the interleaved data sets in this VertexBuffer
     * 
     * @param offset the offset from the beginning of this VertexBuffer to find the first element at
     * 
     */
    virtual void addAttributeLPointer(const std::string& name,
            GLint size,
            GLsizei stride,
            const GLvoid* offset) = 0;

    /**
     * Cleans up any GPU resources that were allocated by this VertexBuffer
     * 
     */
    virtual ~VertexBuffer()
    {
    }
};

}

#    include "VertexBuffer.inl"

namespace midnight
{
    
template<typename T>
using StreamDrawTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_STREAM_DRAW>;

template<typename T>
using StreamReadTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_STREAM_READ>;

template<typename T>
using StreamCopyTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_STREAM_COPY>;

template<typename T>
using StaticDrawTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_STATIC_DRAW>;

template<typename T>
using StaticReadTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_STATIC_READ>;

template<typename T>
using StaticCopyTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_STATIC_COPY>;

template<typename T>
using DynamicDrawTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_DYNAMIC_DRAW>;

template<typename T>
using DynamicReadTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_DYNAMIC_READ>;

template<typename T>
using DynamicCopyTriangleBuffer = detail::VertexBufferImpl<T, GL_TRIANGLES, GL_DYNAMIC_COPY>;


template<typename T>
using StreamDrawQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_STREAM_DRAW>;

template<typename T>
using StreamReadQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_STREAM_READ>;

template<typename T>
using StreamCopyQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_STREAM_COPY>;

template<typename T>
using StaticDrawQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_STATIC_DRAW>;

template<typename T>
using StaticReadQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_STATIC_READ>;

template<typename T>
using StaticCopyQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_STATIC_COPY>;

template<typename T>
using DynamicDrawQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_DYNAMIC_DRAW>;

template<typename T>
using DynamicReadQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_DYNAMIC_READ>;

template<typename T>
using DynamicCopyQuadBuffer = detail::VertexBufferImpl<T, GL_QUADS, GL_DYNAMIC_COPY>;

}

#endif
