#ifndef QUAD_HPP
#    define QUAD_HPP

#    include "BuildConstraints.hpp"

#    include <iostream>

#    include "Point.hpp"

namespace midnight
{
    
template<typename T, std::size_t N>
class Quad;

}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const midnight::Quad<T, N>& quad);

template<typename T, std::size_t N>
std::istream& operator>>(std::istream& stream, midnight::Quad<T, N>& quad);

template<typename T, std::size_t N>
bool operator==(const midnight::Quad<T, N>& lhs, const midnight::Quad<T, N>& rhs);

template<typename T, std::size_t N>
bool operator!=(const midnight::Quad<T, N>& lhs, const midnight::Quad<T, N>& rhs);

namespace midnight
{

template<typename T, std::size_t N>
class Quad
{
    static_assert(N > 1, "Triangles may only exist in dimensionalities >= 2");

    friend std::ostream& operator<<<>(std::ostream&, const Quad<T, N>&);
    friend std::istream& operator>><>(std::istream& Quad<T, N>&);
    friend bool operator==(const Quad<T, N>&, const Quad<T, N>&);
    friend bool operator!=(const Quad<T, N>&, const Quad<T, N>&);


    Point<T, N> upperLeft;
    Point<T, N> lowerRight;

  public:

    Quad();
    Quad(const Point<T, N>& upperLeft, const Point<T, N>& lowerRight);
    Quad(Point<T, N>&& upperLeft, Point<T, N>&& lowerRight);

    Quad(const Quad& rhs);
    Quad(Quad&& rhs);

    Quad& operator=(const Quad& rhs);
    Quad& operator=(Quad&& rhs);

};

}

#    include "Quad.inl"

namespace midnight
{

    using Quad2F = Quad<float, 2>;    
    using Quad3F = Quad<float, 3>;
   
}

#endif