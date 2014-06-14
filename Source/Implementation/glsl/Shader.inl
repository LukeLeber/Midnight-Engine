/// Standard Headers
#include <memory>

/// Internal Headers
#include "dynamic_warn.hpp"

/// Public Headers
#include "CompilationError.hpp"
#include "ResourceException.hpp"

/// To maintain a strong interface, even though this does nothing

inline Shader::Shader(const std::string&)
{

}

namespace detail
{

    template<GLenum ShaderType>
    class ShaderImpl : public Shader
    {
        static_assert(
                ShaderType == GL_VERTEX_SHADER ||
                ShaderType == GL_TESS_CONTROL_SHADER ||
                ShaderType == GL_TESS_EVALUATION_SHADER ||
                ShaderType == GL_GEOMETRY_SHADER ||
                ShaderType == GL_FRAGMENT_SHADER,
                "Unsupported Shader Type");

        /// The implementation-generated handle to the GLSL program
        GLuint handle;

        GLuint getHandle() const noexcept
        {
            return handle;
        }

        /// The source of this Shader
        std::string source;

        void compile()
        {
            const char* cString = source.c_str();
            GLint length = static_cast<GLint>(source.length());
            glShaderSource(handle,
                    1,
                    static_cast<const GLchar**>(&cString),
                    static_cast<GLint*>(&length));
            glCompileShader(handle);
            GLint result;
            glGetShaderiv(handle, GL_COMPILE_STATUS, &result);
            if(result == GL_FALSE)
            {
                glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &result);
                std::unique_ptr < GLchar[] > buffer(new GLchar[result]);
                glGetShaderInfoLog(handle, result, nullptr, buffer.get());
                throw midnight::glsl::CompilationError(std::string(buffer.get()), source);
            }
        }

      public:

        ShaderImpl(const std::string& source) :
        Shader(source),
        handle(glCreateShader(ShaderType)),
        source(source)
        {
            if(handle == 0)
            {
                throw midnight::ResourceException("implementation failed to create shader");
            }
            compile();
        }

        const std::string& getSource() const noexcept
        {
            return source;
        }

        /// To ensure we only call glDeleteShader once per valid handle

        ShaderImpl(ShaderImpl&& rhs) noexcept :
        Shader(rhs.source),
        handle(rhs.handle),
        source(std::move(rhs.source))
        {
            rhs.handle = 0;
        }

        /// To ensure we only call glDeleteShader once per valid handle

        ShaderImpl& operator=(ShaderImpl&& rhs) noexcept
        {
            this->handle = rhs.handle;
            this->source = std::move(rhs.source);
            rhs.handle = 0;
            return *this;
        }

        ShaderImpl(const ShaderImpl& other) : handle(glCreateShader(ShaderType)), source(other.source)
        {
            dynamic_warn("Copy Constructing GLSL Shader (performance consideration - prefer move semantics)");
            if(handle == 0)
            {
                throw midnight::ResourceException("implementation failed to create shader");
            }
            compile();
        }

        ShaderImpl& operator=(const ShaderImpl& other)
        {
            dynamic_warn("Copy Assigning GLSL Shader (performance consideration - prefer move semantics)");
            glDeleteShader(handle);
            handle = glCreateShader(ShaderType);
            if(handle == 0)
            {
                throw midnight::ResourceException("implementation failed to create shader");
            }
            this->source = other.source;
            compile();
            return *this;
        }

        ~ShaderImpl() noexcept
        {
            /// The shader itself will remain in the implementation
            /// server-side until it is no longer referenced there,
            /// which most likely means until this shader is no longer 
            /// linked to any programs.
            glDeleteShader(handle);
        }
    };
}

#include <fstream>
#include <sstream>

#include "ResourceException.hpp"

namespace ShaderIO
{

    template<typename T>
    T loadFromStream(std::istream& stream)
    {
        std::stringstream ss;
        ss << stream.rdbuf();
        return T(ss.str());
    }

    template<typename T>
    T loadFromFile(const std::string& fileName)
    {
        std::fstream stream(fileName);
        if(!stream)
        {
            throw midnight::ResourceException(std::string("The file \"") + fileName + " could not be opened for reading");
        }
        return loadFromStream<T>(stream);
    }

    template<typename T>
    std::shared_ptr<T> loadSharedFromStream(std::istream& stream)
    {
        return std::shared_ptr<T>(new T(loadFromStream<T>(stream)));
    }

    template<typename T>
    std::shared_ptr<T> loadSharedFromFile(const std::string& fileName)
    {
        return std::shared_ptr<T>(new T(loadFromFile<T>(fileName)));
    }
}
