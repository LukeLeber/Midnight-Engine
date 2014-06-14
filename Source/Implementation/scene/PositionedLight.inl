template<typename T>
PositionedLight<T>::PositionedLight(const Color<T, 3>& color, const Point<T, 3>& position) :
Light<T>(color),
position(position)
{

}

template<typename T>
PositionedLight<T>::PositionedLight(Color<T, 3>&& color, Point<T, 3>&& position) :
Light<T>(std::forward(color)),
position(position)
{

}

template<typename T>
PositionedLight<T>::PositionedLight(T r, T g, T b, T x, T y, T z) :
Light<T>(r, g, b),
position(x, y, z)
{

}

template<typename T>
const Point<T, 3>& PositionedLight<T>::getPosition() const
{
    return position;
}

template<typename T>
Point<T, 3>& PositionedLight<T>::getPosition()
{
    return position;
}

template<typename T>
void PositionedLight<T>::setPosition(const Point<T, 3>& position)
{
    this->position = position;
}

template<typename T>
void PositionedLight<T>::setPosition(Point<T, 3>&& position)
{
    this->position = std::forward(position);
}

template<typename T>
void PositionedLight<T>::setPosition(T x, T y, T z)
{
    this->position.set(x, y, z);
}