#ifndef ATTRIBUTE_NOT_FOUND_EXCEPTION_HPP
#    define ATTRIBUTE_NOT_FOUND_EXCEPTION_HPP

/// Puke if clang is not used
static_assert(__clang__, "Your compiler is not supported.");

#    include "GLException.hpp"

/**
 * An exception that represents a situation where an attribute could not be found in a specified program
 * 
 * @see GLException
 * 
 */
class AttributeNotFoundException : public midnight::GLException
{
  public:

    /**
     * Constructs a AttributeNotFoundException with the provided message
     * 
     * @param message a brief message explaining the error condition
     * 
     */
    AttributeNotFoundException(const std::string& message) noexcept;
};

/// External implementation
#    include "AttributeNotFoundException.inl"

#endif
