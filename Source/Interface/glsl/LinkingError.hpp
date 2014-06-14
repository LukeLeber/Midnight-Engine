#ifndef LINKING_ERROR_HPP
#    define LINKING_ERROR_HPP

#include "BuildConstraints.hpp"

#    include "GLException.hpp"

namespace midnight
{
namespace glsl
{

/**
 * An exception that represents a situation where the implementation fails to link a GLSL shader program
 * 
 * @see GLException
 * 
 */
class LinkingError : public midnight::GLException
{
  public:

    /**
     * Constructs a LinkingError with the provided message
     * 
     * @param message a brief message explaining the error condition 
     * 
     */
    LinkingError(const std::string& message) noexcept;
};

}
}

/// External Implementation
#    include "LinkingError.inl"

#endif
