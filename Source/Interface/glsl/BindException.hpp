#ifndef BIND_EXCEPTION_HPP
#    define BIND_EXCEPTION_HPP

/// Puke if clang is not used
static_assert(__clang__, "Your compiler is not supported.");

#    include "GLException.hpp"

namespace midnight
{
namespace glsl
{

/**
 * An exception that represents a situation where a construct fails to bind or unbind itself to the underlying 
 * implementation.
 * 
 * @see GLException
 * 
 */
class BindException : public midnight::GLException
{
  public:

    /**
     * Constructs a BindException with the provided message
     * 
     * @param message a brief message explaining the error condition
     * 
     */
    BindException(const std::string message) noexcept;

};

}
}

/// External Implementation
#    include "BindException.inl"

#endif
