namespace midnight
{
    template<typename T>
    AmbientLight<T>::AmbientLight(const Color<T, 4>& color) :
    color(color)
    {

    }

    template<typename T>
    AmbientLight<T>::AmbientLight(Color<T, 4>&& color) :
    color(std::forward(color))
    {

    }

    template<typename T>
    AmbientLight<T>::AmbientLight(T r, T g, T b, T a) :
    color(r, g, b, a)
    {

    }
    
    template<typename T>
    AmbientLight<T>::AmbientLight()
    {
        
    }

    template<typename T>
    const Color<T, 4>& AmbientLight<T>::getColor() const
    {
        return color;
    }

    template<typename T>
    Color<T, 4>& AmbientLight<T>::getColor()
    {
        return color;
    }

    template<typename T>
    void AmbientLight<T>::setColor(const Color<T, 4>& color)
    {
        this->color = color;
    }

    template<typename T>
    void AmbientLight<T>::setColor(Color<T, 4>&& color)
    {
        this->color = std::forward(color);
    }

    template<typename T>
    void AmbientLight<T>::setColor(T r, T g, T b, T a)
    {
        this->color.set(r, g, b, a);
    }
}
