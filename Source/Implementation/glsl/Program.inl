#include <initializer_list>
#include <functional>
#include <tuple>

#include "BindException.hpp"
#include "dynamic_warn.hpp"
#include "LinkingError.hpp"
#include "ResourceException.hpp"
#include "Tuple.hpp"
#include "UniformNotFoundException.hpp"
#include "UniformMismatchException.hpp"


namespace detail
{

    /**
     * A struct that holds the compile-time value of the type checking
     * 
     */
    template <template<typename> class ConversionChecker, typename First, typename ...Remaining>
    struct TypeChecker
    {
        static constexpr bool value = ConversionChecker<First>::value && TypeChecker<ConversionChecker, Remaining...>::value;
    };

    /**
     * Recursion's End
     * 
     */
    template <template<typename> class ConversionChecker, typename Last>
    struct TypeChecker<ConversionChecker, Last>
    {
        static constexpr bool value = ConversionChecker<Last>::value;
    };

    /**
     * A helper struct to redefine the first type found in a parameter pack
     * 
     */
    template <typename T, typename ...Args>
    struct FirstTypeGrabber
    {
        typedef T Type;
    };

    /**
     * Performs a compile-time assertion that all of the types in the 
     * provided parameter pack are the same.
     * 
     */
    template <typename ...Args>
    struct TypeCheckAssertion
    {
        template <typename T>
        using ConversionChecker = std::is_convertible<typename FirstTypeGrabber<Args...>::Type&, T>;

        static_assert(TypeChecker<ConversionChecker, Args...>::value, "Type mismatch detected");
    };

    GLint getUniformLocation(GLuint handle, const std::string& uniformID)
    {
        GLint location = glGetUniformLocation(handle,
                static_cast<const GLchar*>(uniformID.c_str()));
        /// Call returns -1 upon failure
        if(location == -1)
        {
            throw midnight::glsl::UniformNotFoundException(std::string("Unable to locate uniform \"") + uniformID + "\"");
        }
        return location;
    }

    /**
     * Copies the provided tuple in the provided array
     * 
     * @tparam ElementType the type of element that is being copied
     * 
     * @tparam TupleType the type of tuple that is being copied
     * 
     * @tparam ArrayLength the length of the array and tuple types
     * 
     * @tparam Index the current index that is being copied
     * 
     * 
     */
    template<typename ElementType, typename TupleType, std::size_t ArrayLength, std::size_t Index = ArrayLength>
    struct CopyHelper
    {

        static void copy(const TupleType& t, std::array<ElementType, ArrayLength> & arr)
        {
            CopyHelper<ElementType, TupleType, ArrayLength, Index - 1 > ::copy(t, arr);
            arr[Index - 1] = std::get < Index - 1 > (t);
        }
    };

    /// Partial-specialization to deal with Index == 0 to terminate recursion
    template<typename ElementType, typename TupleType, std::size_t ArrayLength>
    struct CopyHelper<ElementType, TupleType, ArrayLength, 1>
    {

        static void copy(const TupleType& t, std::array<ElementType, ArrayLength> & arr)
        {
            arr[0] = std::get<0>(t);
        }
    };

    /**
     * Copies the provided tuple in the provided array
     * 
     * @tparam T the type of the elements to copy
     * 
     * @tparam Remaining a parameter pack containing the number of elements
     * 
     * @param tuple the tuple to copy into the provided array
     * 
     * @param array the array to copy the provided tuple into
     * 
     */
    template<typename T, typename... Remaining>
    void copyTupleToArray(const std::tuple<T, Remaining...>& tuple, std::array<T, sizeof...(Remaining) + 1 > & array)
    {
        CopyHelper<T, decltype(tuple), sizeof...(Remaining) + 1 > ::copy(tuple, array);
    }

    /**
     * A wrapper for std::tuple_cat that concats the raw elements of the 
     * provided Tuples
     * 
     * @param tuples the Tuples to concat
     * 
     * @return the newly formed std::tuple containing the provided values
     * 
     */
    template<typename...E>
    auto tuple_cat(E&&... tuples) -> decltype(std::tuple_cat(tuples.asArray()...))
    {
        return std::tuple_cat(tuples.asArray()...);
    }
    
    /**
     * A helper-template to delegate the calls to the underlying 
     * implementation
     * 
     */
    template<typename T, std::size_t N, std::size_t I, std::size_t J>
    struct UniformArrayHelper
    {
        /// A specialization must be used!
        static void glUniformXXX(GLint uniformLocation, const std::array<T, N>& data) = delete;
    };

    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLuint, N, 1, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLuint, N>& data)
        {
            glUniform1uiv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLuint, N, 2, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLuint, N>& data)
        {
            glUniform2uiv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLuint, N, 3, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLuint, N>& data)
        {
            glUniform3uiv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLuint, N, 4, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLuint, N>& data)
        {
            glUniform4uiv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLint, N, 1, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLint, N>& data)
        {
            glUniform1iv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLint, N, 2, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLint, N>& data)
        {
            glUniform2iv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLint, N, 3, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLint, N>& data)
        {
            glUniform3iv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLint, N, 4, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLint, N>& data)
        {
            glUniform4iv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLfloat, N, 1, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLfloat, N>& data)
        {
            glUniform1fv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLfloat, N, 2, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLfloat, N>& data)
        {
            glUniform2fv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLfloat, N, 3, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLfloat, N>& data)
        {
            glUniform3fv(uniformLocation, J, &data[0]);
        }
    };
    
    template<std::size_t N, std::size_t J>
    struct UniformArrayHelper<GLfloat, N, 4, J>
    {
        static void glUniformXXX(GLint uniformLocation, const std::array<GLfloat, N>& data)
        {
            glUniform4fv(uniformLocation, J, &data[0]);
        }
    };

    /// A helper class that binds the requested program object at 
    /// construction and likewise restores the previously bound program 
    /// upon destruction.

    class BindHelper
    {
        GLint preserved;

      public:

        BindHelper(GLuint handle)
        {
            glGetIntegerv(GL_CURRENT_PROGRAM, &preserved);
            glUseProgram(handle);
        }

        ~BindHelper()
        {
            glUseProgram(preserved);
        }
    };

    /// A helper class that attaches the provided shaders at construction, 
    /// and likewise detaches them at destruction, ensuring proper resource 
    /// cleanup even in exceptional circumstances.

    class LinkHelper
    {
        GLuint handle;
        const std::initializer_list<Shader*>& shaders;

      public:

        LinkHelper(GLuint handle, const std::initializer_list<Shader*>& shaders) :
        handle(handle),
        shaders(shaders)
        {
            for(Shader* s : shaders)
            {
                /// Will fail if a duplicate shader was in the array
                glAttachShader(handle, s->getHandle());
                if(glGetError() == GL_INVALID_OPERATION)
                {
                    throw midnight::glsl::LinkingError("Unable to attach duplicate shader");
                }
            }
        }

        ~LinkHelper()
        {
            for(Shader* s : shaders)
            {
                /// Will set GL_INVALID_OPERATION if an attach failed
                /// and this shader was not yet attached, but we'll just 
                /// silently ignore these 'expected' errors.
                glDetachShader(handle, s->getHandle());
            }
            /// So silently swallow up error-states that were set
            /// as not to leave a 'false' error flag in the state machine.
            glGetError();
        }
    };
}

Program::Program(const std::initializer_list<Shader*>& shaders) :
handle(glCreateProgram())
{
    /// Implementation must return '0' on error
    if(handle == 0)
    {
        throw midnight::ResourceException("implementation failed to create program");
    }

    /// Utilize RAII to attach (and ultimately detach) the shaders
    detail::LinkHelper helper(handle, shaders);

    /// Link the program

    /// This should not set any flags
    /// http://www.opengl.org/sdk/docs/man/xhtml/glLinkProgram.xml
    glLinkProgram(handle);
    GLint result;

    /// This should not set any flags, nor fail
    /// http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetProgramiv.xml
    glGetProgramiv(handle, GL_LINK_STATUS, &result);

    /// Failed to link
    if(result == GL_FALSE)
    {
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &result);
        std::unique_ptr < GLchar[] > buffer(new GLchar[result]);

        /// This shouldn't set any flags, nor fail
        /// http://www.opengl.org/sdk/docs/man/xhtml/glGetProgramInfoLog.xml
        glGetProgramInfoLog(handle, result, nullptr, buffer.get());

        /// Shaders implicitly detached by the LinkHelper destructor
        throw midnight::glsl::LinkingError(std::string(buffer.get()));
    }
}

template<typename ...E>
inline Program::Program(std::shared_ptr<Shader> first, E&&... shaders) :
Program({first.get(), shaders.get()...})
{

}

template<typename ...E>
inline Program::Program(Shader&& first, E&&... shaders) :
Program({&first, &shaders...})
{

}

template<typename... E>
inline Program::Program(Shader& first, E&... shaders) : Program({&first, &shaders...})
{

}

Program::Program(Program&& other) : handle(other.handle)
{
    /// Copy-constructing from self would create a resource leak!
    if(&other != this)
    {
        other.handle = 0;
    }
    else
    {
        dynamic_warn("Move construction invoked with this pointer");
    }
}

Program& Program::operator=(Program&& other)
{
    if(&other != this)
    {
        this->handle = other.handle;
        other.handle = 0;
    }
    else
    {
        dynamic_warn("Move assignment invoked with this pointer");
    }
    return *this;
}

void Program::bind()
{
    /// It's a bit...ambiguous why this might fail...
    /// Spec designers dropped the ball on this one.
    /// http://www.opengl.org/sdk/docs/man4/xhtml/glUseProgram.xml
    glUseProgram(handle);
    if(glGetError() == GL_INVALID_OPERATION)
    {
        throw midnight::glsl::BindException("Unable to bind program");
    }
}

void Program::unbind()
{
    GLint current;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current);
    if(handle == static_cast<GLuint>(current))
    {
        /// It's a bit...ambiguous why this might fail...
        /// Spec designers dropped the ball on this one.
        /// http://www.opengl.org/sdk/docs/man4/xhtml/glUseProgram.xml
        glUseProgram(0);
        if(glGetError() == GL_INVALID_OPERATION)
        {
            throw midnight::glsl::BindException("Unable to unbind program");
        }
    }
    else
    {
        dynamic_warn("Attempted to unbind a program that was not currently bound");
    }
}

template<typename... E>
void Program::setUniform(const std::string& uniformID, E&&... tuples)
{
    /// Compile-time assertion that the tuples aren't mixed and matched...
    detail::TypeCheckAssertion < E...>();
    /// Deduce tuple type, element type, and size
    using TupleType = decltype(detail::tuple_cat(std::forward<E>(tuples)...));
    using T = typename std::tuple_element<0, TupleType>::type;
    constexpr std::size_t N = std::tuple_size<TupleType>::value;
    /// Make sure we're only passing element types allowed in GLSL
    static_assert((N / sizeof...(E)) > 0 && (N / sizeof...(E)) < 5, "Invalid uniform array element type");

    /// Can fail with an exception, so try this before copying the provided tuples
    GLint uniformLocation = detail::getUniformLocation(handle, uniformID);

    /// Copy the provided tuples into a monolithic array to pass to the GPU
    std::array<T, N> array;
    detail::copyTupleToArray(detail::tuple_cat(std::forward<E>(tuples)...), array);

    /// Use RAII to temporarily bind this program
    detail::BindHelper binder(handle);
    
    /// <N, I>
    /// Invoke the correct call to the implementation
    detail::UniformArrayHelper<T, N, N / sizeof...(tuples), sizeof...(tuples)>::glUniformXXX(uniformLocation, array);
        
    /// Apparently, a shitload of things can go wrong...
    /// http://www.opengl.org/sdk/docs/man4/xhtml/glUniform.xml
    GLenum error = glGetError();
    if(error == GL_INVALID_OPERATION)
    {
        throw midnight::glsl::UniformMismatchException(std::string("The provided uniform type \"") + uniformID +
                "\" is incompatible with the type declared in the program");
    }
}

namespace detail
{
    template<typename T, std::size_t Rows, std::size_t Columns>
    struct MatrixUniformHelper
    {
        inline static void setUniform(GLint uniformLocation, const midnight::Matrix<T, Rows, Columns>& matrix) = delete;
    };
    
    template<typename T>
    struct MatrixUniformHelper<T, 3, 3>
    {
        inline static void setUniform(GLint uniformLocation, const midnight::Matrix<T, 3, 3>& matrix)
        {
            glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &matrix);
        }
    };
    
    template<typename T>
    struct MatrixUniformHelper<T, 4, 4>
    {
        inline static void setUniform(GLint uniformLocation, const midnight::Matrix<T, 4, 4>& matrix)
        {
            glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix);
        }
    };

    
    
}

template<typename T, std::size_t Rows, std::size_t Columns>
void Program::setMatrixUniform(const std::string& uniformID, const midnight::Matrix<T, Rows, Columns>& matrix)
{
    GLint uniformLocation = detail::getUniformLocation(handle, uniformID);
    detail::BindHelper binder(handle);
    detail::MatrixUniformHelper<T, Rows, Columns>::setUniform(uniformLocation, matrix);
}
