namespace midnight
{
    template<typename T>
    DirectionalLight<T>::DirectionalLight(const Color<T, 3>& color, const Vector<T, 3>& direction) :
    color(color), direction(direction)
    {

    }

    template<typename T>
    DirectionalLight<T>::DirectionalLight(Color<T, 3>&& color, Vector<T, 3>&& direction) :
    color(std::forward(color)), direction(std::forward(direction))
    {

    }

    template<typename T>
    DirectionalLight<T>::DirectionalLight(T r, T g, T b, T x, T y, T z) :
    color(r, g, b), direction(x, y, z)
    {

    }
    
    template<typename T>
    DirectionalLight<T>::DirectionalLight() : direction(0.0f, 1.0f, 0.0f)
    {
        
    }

    template<typename T>
    const Vector<T, 3>& DirectionalLight<T>::getDirection() const
    {
        return direction;
    }

    template<typename T>
    Vector<T, 3>& DirectionalLight<T>::getDirection()
    {
        return direction;
    }

    template<typename T>
    void DirectionalLight<T>::setDirection(const Vector<T, 3>& direction)
    {
        this->direction = direction;
    }

    template<typename T>
    void DirectionalLight<T>::setDirection(Vector<T, 3>&& direction)
    {
        this->direction = std::forward(direction);
    }

    template<typename T>
    void DirectionalLight<T>::setDirection(T x, T y, T z)
    {
        this->direction.set(x, y, z);
    }
    
}