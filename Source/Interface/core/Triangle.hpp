#ifndef TRIANGLE_HPP
#    define TRIANGLE_HPP

#    include "BuildConstraints.hpp"

#    include "Point.hpp"
#    include "Vector.hpp"

#    include <iostream>

namespace midnight
{

template<typename T, std::size_t N>
class Triangle;

}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const midnight::Triangle<T, N>& triangle);

template<typename T, std::size_t N>
std::istream& operator>>(std::istream& stream, midnight::Triangle<T, N>& triangle);

template<typename T, std::size_t N>
bool operator==(const midnight::Triangle<T, N>& lhs, const midnight::Triangle<T, N>& rhs);

template<typename T, std::size_t N>
bool operator!=(const midnight::Triangle<T, N>& lhs, const midnight::Triangle<T, N>& rhs);

namespace midnight
{

template<typename T, std::size_t N>
class Triangle
{
    static_assert(N > 1, "Triangles may only exist in dimensionalities >= 2");

    friend std::ostream& operator<<<>(std::ostream&, const Triangle<T, N>&);
    friend std::istream& operator>><>(std::istream&, Triangle<T, N>&);

    Point<T, N> a;
    Point<T, N> b;
    Point<T, N> c;

  public:

    Triangle();
    Triangle(const Point<T, N>& a, const Point<T, N>& b, const Point<T, N>& c);
    Triangle(Point<T, N>&& a, Point<T, N>&& b, Point<T, N>&& c);

    Triangle(const Triangle& rhs);
    Triangle(Triangle&& rhs);

    Triangle& operator=(const Triangle& rhs);
    Triangle& operator=(Triangle&& rhs);

    void set(const Point<T, N>& a, const Point<T, N>& b, const Point<T, N>& c);
    void set(Point<T, N>&& a, Point<T, N>&& b, Point<T, N>&& c);

    // TODO: Collision Detection
    /*
        Vector<T, N> calculateNormal() const;
        T calculateArea() const;
     */


};

}

#    include "Triangle.inl"

#endif