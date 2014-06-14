#ifndef COMPILATION_ERROR_HPP
#    define COMPILATION_ERROR_HPP

#include "BuildConstraints.hpp"

#    include "GLException.hpp"

namespace midnight
{

namespace glsl
{
    
/**
 * An exception that represents a situation where the implementation fails to compile a GLSL shader
 * 
 * @see GLException
 * 
 */
class CompilationError : public GLException
{
    /// The source code of the shader that failed to compile
    const std::string shaderSource;

  public:

    /**
     * Constructs a CompilationError with the provided message and source
     * 
     * @param message a brief message explaining the error condition
     * 
     * @param shaderSource the source code of the shader that failed to compile
     * 
     */
    CompilationError(const std::string& message, const std::string& shaderSource) noexcept;

    /**
     * Retrieves the source code of the shader that failed to compile
     * 
     * @return the source code of the shader that failed to compile
     * 
     */
    const std::string& getShaderSource() const noexcept;
};

}
}

/// External Implementation
#    include "CompilationError.inl"

#endif
