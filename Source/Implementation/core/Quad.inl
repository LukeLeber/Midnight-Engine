template<typename T, std::size_t N>
inline std::ostream& operator<<(std::ostream& stream, const midnight::Quad<T, N>& quad)
{
    return stream << quad.upperLeft << quad.lowerRight;
}

template<typename T, std::size_t N>
inline std::istream& operator>>(std::istream& stream, midnight::Quad<T, N>& quad)
{
    return stream >> quad.upperLeft >> quad.lowerRight;
}

template<typename T, std::size_t N>
inline bool operator==(const midnight::Quad<T, N>& lhs, const midnight::Quad<T, N>& rhs)
{
    return lhs.upperLeft == rhs.upperLeft && lhs.lowerRight == rhs.lowerRight;
}

template<typename T, std::size_t N>
inline bool operator!=(const midnight::Quad<T, N>& lhs, const midnight::Quad<T, N>& rhs)
{
    return lhs.upperLeft != rhs.upperLeft || lhs.lowerRight != rhs.lowerRight;
}

namespace midnight
{

template<typename T, std::size_t N>
inline Quad<T, N>::Quad() :
upperLeft(),
lowerRight()
{

}

template<typename T, std::size_t N>
inline Quad<T, N>::Quad(const Point<T, N>& upperLeft, const Point<T, N>& lowerRight) :
upperLeft(upperLeft),
lowerRight(lowerRight)
{

}

template<typename T, std::size_t N>
inline Quad(Point<T, N>&& upperLeft, Point<T, N>&& lowerRight) :
upperLeft(std::move(upperLeft)),
lowerRight(std::move(lowerRight))
{

}

template<typename T, std::size_t N>
inline Quad<T, N>::Quad(const Quad<T, N>& rhs) :
upperLeft(rhs.upperLeft),
lowerRight(rhs.lowerRight)
{

}

template<typename T, std::size_t N>
inline Quad<T, N>::Quad(Quad<T, N>&& rhs)
upperLeft(std::move(rhs.upperLeft)),
lowerRight(std::move(rhs.lowerRight))
{

}

template<typename T, std::size_t N>
inline Quad<T, N>& Quad<T, N>::operator=(const Quad<T, N>& rhs)
{
    this->upperLeft = rhs.upperLeft;
    this->lowerRight = rhs.lowerRight;
}

template<typename T, std::size_t N>
inline Quad<T, N>& Quad<T, N>::operator=(Quad<T, N>&& rhs)
{
    this->upperLeft = std::move(rhs.upperLeft);
    this->lowerRight = std::move(rhs.lowerRight);
}

}
