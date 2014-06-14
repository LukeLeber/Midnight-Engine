#ifndef RESOURCE_EXCEPTION_HPP
#    define RESOURCE_EXCEPTION_HPP

#    include "BuildConstraints.hpp"

#    include "GLException.hpp"

namespace midnight
{

class ResourceException : public GLException
{
  public:
    explicit ResourceException(const std::string& message);
};

}

#    include "ResourceException.inl"

#endif
