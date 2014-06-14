template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const midnight::Triangle<T, N>& triangle)
{
    return stream << triangle.a << triangle.b << triangle.c;
}

template<typename T, std::size_t N>
std::istream& operator>>(std::istream& stream, midnight::Triangle<T, N>& triangle)
{
    return stream >> triangle.a >> triangle.b >> triangle.c;
}

template<typename T, std::size_t N>
bool operator==(const midnight::Triangle<T, N>& lhs, const midnight::Triangle<T, N>& rhs)
{
    return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
}

template<typename T, std::size_t N>
bool operator!=(const midnight::Triangle<T, N>& lhs, const midnight::Triangle<T, N>& rhs)
{
    return lhs.a != rhs.a || lhs.b != rhs.b || lhs.c != rhs.c;
}

namespace midnight
{

template<typename T, std::size_t N>
Triangle<T, N>::Triangle() :
a(),
b(),
c()
{

}

template<typename T, std::size_t N>
Triangle<T, N>::Triangle(const Point<T, N>& a, const Point<T, N>& b, const Point<T, N>& c) :
a(a),
b(b),
c(c)
{

}

template<typename T, std::size_t N>
Triangle<T, N>::Triangle(Point<T, N>&& a, Point<T, N>&& b, Point<T, N>&& c) :
a(std::move(a)),
b(std::move(b)),
c(std::move(c))
{

}

template<typename T, std::size_t N>
Triangle<T, N>::Triangle(const Triangle& rhs) :
a(rhs.a),
b(rhs.b),
c(rhs.c)
{

}

template<typename T, std::size_t N>
Triangle<T, N>::Triangle(Triangle&& rhs) :
a(std::move(rhs.a)),
b(std::move(rhs.b)),
c(std::move(rhs.c))
{

}

template<typename T, std::size_t N>
Triangle<T, N>& Triangle<T, N>::operator=(const Triangle& rhs)
{
    this->a = rhs.a;
    this->b = rhs.b;
    this->c = rhs.c;
    return *this;
}

template<typename T, std::size_t N>
Triangle<T, N>& Triangle<T, N>::operator=(Triangle&& rhs)
{
    this->a = std::move(rhs.a);
    this->b = std::move(rhs.b);
    this->c = std::move(rhs.c);
    return *this;
}

template<typename T, std::size_t N>
void Triangle<T, N>::set(const Point<T, N>& a, const Point<T, N>& b, const Point<T, N>& c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

template<typename T, std::size_t N>
void Triangle<T, N>::set(Point<T, N>&& a, Point<T, N>&& b, Point<T, N>&& c)
{
    this->a = std::move(a);
    this->b = std::move(b);
    this->c = std::move(c);
}

}
