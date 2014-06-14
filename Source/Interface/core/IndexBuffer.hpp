#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include <type_traits>
#include <vector>

#include "Platform.hpp"

namespace midnight
{
    template<typename T, GLenum Usage>
    class IndexBuffer
    {
        static_assert(std::is_integral<T>::value, "Only integral types may be used to instantiate an IndexBuffer template");

        static_assert(Usage == GL_STREAM_DRAW ||
            Usage == GL_STREAM_READ ||
            Usage == GL_STREAM_COPY ||
            Usage == GL_STATIC_DRAW ||
            Usage == GL_STATIC_READ ||
            Usage == GL_STATIC_COPY ||
            Usage == GL_DYNAMIC_DRAW ||
            Usage == GL_DYNAMIC_READ ||
            Usage == GL_DYNAMIC_COPY,
            "Invalid intended usage template provided to IndexBuffer");

        GLuint handle;
        
        std::vector<T> data;
        
      public:
        
        IndexBuffer(const std::vector<T>& data);
        
        IndexBuffer(std::vector<T>&& data);
        
        void bind();
        
        void unbind();
        
        ~IndexBuffer();
    };    
}

#include "IndexBuffer.inl"

namespace midnight
{
    template<typename T>
    using StaticDrawIndexBuffer = IndexBuffer<T, GL_STATIC_DRAW>;
}

#endif