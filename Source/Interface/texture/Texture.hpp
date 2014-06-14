#ifndef TEXTURE_HPP
#    define TEXTURE_HPP

#    include "Platform.hpp"

namespace midnight
{

class Texture
{
    std::vector<unsigned char> data;

  public:
    GLuint handle;

    Texture(std::size_t width, std::size_t height, const std::vector<unsigned char>& data)
    {
        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    }
    
    void bind()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, handle);
    }

    void unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
};

}

#endif