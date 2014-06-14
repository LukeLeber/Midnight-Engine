#ifndef UNIFORM_MISMATCH_EXCEPTION_HPP
#    define UNIFORM_MISMATCH_EXCEPTION_HPP

#include "BuildConstraints.hpp"

#    include "GLException.hpp"

namespace midnight
{
namespace glsl
{


class UniformMismatchException : public midnight::GLException
{
  public:

    UniformMismatchException(const std::string& message) noexcept;
};

}
}

#    include "UniformMismatchException.inl"

#endif
