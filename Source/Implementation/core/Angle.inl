#include "constexpr_math.hpp"

namespace midnight
{
namespace detail
{

    enum class AngularUnit
    {
        DEGREES,
        RADIANS
    };

    template<typename T, AngularUnit Unit>
    class AngleImpl
    {
        T value;

      public:

          constexpr AngleImpl(T value) : 
              value(value)
          {

          }

          void set(T value) noexcept
          {
                this->value = value;
          }

          operator T() const noexcept
          {
              return value;
          }
    };
    
    template<typename T, bool UseEpsilon = std::is_floating_point<T>::value>
    struct AngleEqualityHelper
    {
        inline static bool equals(T lhs, T rhs)
        {
            return lhs == rhs;
        }
    };

    template<typename T>
    struct AngleEqualityHelper<T, true>
    {
        inline static bool equals(T lhs, T rhs)
        {
            return (lhs - rhs) <= ::DEFAULT_EPSILON<T>();
        }
    };
}
}
