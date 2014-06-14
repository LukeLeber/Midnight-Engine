#ifndef UNIFORM_NOT_FOUND_EXCEPTION_HPP
#    define UNIFORM_NOT_FOUND_EXCEPTION_HPP

#include "BuildConstraints.hpp"

#    include "GLException.hpp"

namespace midnight
{
namespace glsl
{

/**
 * UniformNotFoundExceptions are thrown when a uniform key is not found in the 
 * requested GLSL program.  It should be noted that GLSL programs are subject 
 * to extreme optimization, meaning that any unused uniforms in a program are 
 * removed from the binary.  Attempting to access such a uniform shall result 
 * in a UniformNotFoundException being thrown.
 * 
 */
class UniformNotFoundException : public GLException
{
  public:

    /**
     * Constructs a UniformNotFoundException with the provided message
     * 
     * @param message a brief message explaining the error condition
     * 
     */
    UniformNotFoundException(const std::string& message);
};

}
}

/// External Implementation
#    include "UniformNotFoundException.inl"

#endif
