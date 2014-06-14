
#include "Vertex.hpp"

template<typename T>
bool operator==(const midnight::Vertex<T>& vertex0, const midnight::Vertex<T>& vertex1) noexcept
{
    return vertex0.position == vertex1.position && 
            vertex0.normal == vertex1.normal && 
            vertex0.texCoord == vertex1.texCoord;
}

template<typename T>
bool operator!=(const midnight::Vertex<T>& vertex0, const midnight::Vertex<T>& vertex1) noexcept
{
    return vertex0.position != vertex1.position || 
            vertex0.normal != vertex1.normal || 
            vertex0.texCoord != vertex1.texCoord;
}

template<typename T>
std::istream& operator>>(std::istream stream, midnight::Vertex<T>& vertex)
{
    return stream >> vertex.position >> vertex.normal >> vertex.texCoord;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const midnight::Vertex<T>& vertex)
{
    return stream << vertex.position << vertex.normal << vertex.texCoord;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, midnight::Vertex<T>&& vertex)
{
    return stream << std::move(vertex.position) << std::move(vertex.normal) << std::move(vertex.texCoord);
}

namespace midnight
{
    
    template<typename T>
    Vertex<T>::Vertex(const Point<T, 3>& position, const Vector<T, 3>& normal, const Point<T, 2>& texCoord) : 
        position(position),
        normal(normal),
        texCoord(texCoord)
    {
        
    }
    
    template<typename T>
    Vertex<T>::Vertex(Point<T, 3>&& position, Vector<T, 3>&& normal, Point<T, 2>&& texCoord) : 
        position(std::move(position)),
        normal(std::move(normal)), 
        texCoord(std::move(texCoord))
    {
        
    }
    
    template<typename T>
    Point<T, 3>& Vertex<T>::getPosition()
    {
        return position;
    }
    
    template<typename T>
    Vector<T, 3>& Vertex<T>::getNormal()
    {
        return normal;
    }

    template<typename T>
    Point<T, 2>& Vertex<T>::getTexCoord()
    {
        return texCoord;
    }
    
    template<typename T>
    const Point<T, 3>& Vertex<T>::getPosition() const
    {
        return position;
    }
    
    template<typename T>
    const Vector<T, 3>& Vertex<T>::getNormal() const
    {
        return normal;
    }

    template<typename T>
    const Point<T, 2>& Vertex<T>::getTexCoord() const
    {
        return texCoord;
    }
    
    template<typename T>
    void Vertex<T>::setPosition(const Point<T, 3>& position)
    {
        this->position = position;
    }
    
    template<typename T>
    void Vertex<T>::setNormal(const Vector<T, 3>& normal)
    {
        this->normal = normal;
    }
    
    template<typename T>
    void Vertex<T>::setTexCoord(const Point<T, 2>& texCoord)
    {
        this->texCoord = texCoord;
    }
    
    template<typename T>
    void Vertex<T>::setPosition(Point<T, 3>&& position)
    {
        this->position = std::move(position);
    }
    
    template<typename T>
    void Vertex<T>::setNormal(Vector<T, 3>&& normal)
    {
        this->normal = std::move(normal);
    }
    
    template<typename T>
    void Vertex<T>::setTexCoord(Point<T, 2>&& texCoord)
    {
        this->texCoord = std::move(texCoord);
    }
}
