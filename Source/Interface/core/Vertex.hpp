#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>

#include "Point.hpp"
#include "Vector.hpp"

namespace midnight
{
    template<typename T>
    class Vertex;
}
    /**
     * Equality operator for Vertices
     * 
     * @param vertex0 the first Vertex to compare
     * 
     * @param vertex1 the second Vertex to compare
     * 
     * @return true if the first Vertex equals the second, otherwise false
     * 
     * @note This method may utilize epsilon-value comparisons.
     * 
     */
    template<typename T>
    bool operator==(const midnight::Vertex<T>& vertex0, const midnight::Vertex<T>& vertex1) noexcept;
    
    /**
     * Inequality operator for Vertices
     * 
     * @param vertex0 the first Vertex to compare
     * 
     * @param vertex1 the second Vertex to compare
     * 
     * @return true if the first Vertex is not equal to the second, otherwise false
     * 
     * @note This method may utilize epsilon-value comparisons.
     */
    template<typename T>
    bool operator!=(const midnight::Vertex<T>& vertex0, const midnight::Vertex<T>& vertex1) noexcept;
    
    /**
     * Extracts a Vertex from the provided input stream
     * 
     * @param stream the input stream to read from
     * 
     * @param vertex the Vertex to read into
     * 
     * @return the provided input stream
     * 
     */
    template<typename T>
    std::istream& operator>>(std::istream& stream, midnight::Vertex<T>& vertex);
    
    /**
     * Inserts a Vertex into the provided output stream
     * 
     * @param stream the output stream to write to
     * 
     * @param vertex the Vertex to insert
     * 
     * @return the provided output stream
     * 
     */
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const midnight::Vertex<T>& vertex);
    
    /**
     * Inserts a Vertex into the provided output stream
     * 
     * @param stream the output stream to write to
     * 
     * @param vertex the Vertex to insert
     * 
     * @return the provided output stream
     * 
     */
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, midnight::Vertex<T>&& vertex);

namespace midnight
{
    /**
     * A generic type that holds all of the data that a single vertex represents.
     * 
     */
    template<typename T>
    class Vertex
    {
        friend bool ::operator== <>(const Vertex<T>&, const Vertex<T>&) noexcept;
        friend bool ::operator!= <>(const Vertex<T>&, const Vertex<T>&) noexcept;
        
        friend std::ostream& ::operator<<<>(std::ostream&, const Vertex<T>&);
        friend std::ostream& ::operator<<(std::ostream&, midnight::Vertex<T>&&);
        friend std::istream& ::operator>><>(std::istream&, Vertex<T>&);

        /// The position data of this Vertex
        Point<T, 3> position;
        
        /// The normal data of this Vertex
        Vector<T, 3> normal;
        
        /// The texture-coordinate data of this Vertex
        Point<T, 2> texCoord;
        
      public:

        /**
         * Constructs a Vertex with the provided attributes
         * 
         * @param position the geometric position attribute of this Vertex
         * 
         * @param normal the normal attribute of this Vertex
         * 
         * @param texCoord the texture coordinate attribute of this Vertex
         * 
         */
        Vertex(const Point<T, 3>& position, const Vector<T, 3>& normal, const Point<T, 2>& texCoord);
        
        /**
         * Constructs a Vertex with the provided attributes
         * 
         * @param position the geometric position attribute of this Vertex
         * 
         * @param normal the normal attribute of this Vertex
         * 
         * @param texCoord the texture coordinate attribute of this Vertex
         * 
         */
        Vertex(Point<T, 3>&& position, Vector<T, 3>&& normal, Point<T, 2>&& texCoord);
        
        /**
         * Retrieves a mutable reference to the position attribute of this Vertex
         * 
         * @return a mutable reference to the position attribute of this Vertex
         * 
         */
        Point<T, 3>& getPosition();
        
        /**
         * Retrieves a mutable reference to the normal attribute of this Vertex
         * 
         * @return a mutable reference to the normal attribute of this Vertex
         * 
         */
        Vector<T, 3>& getNormal();
        
        /**
         * Retrieves a mutable reference to the texture coordinate attribute of this Vertex
         * 
         * @return a mutable reference to the texture coordinate attribute of this Vertex
         * 
         */
        Point<T, 2>& getTexCoord();
        
        /**
         * Retrieves an immutable reference to the position attribute of this Vertex
         * 
         * @return a mutable reference to the position attribute of this Vertex
         * 
         */
        const Point<T, 3>& getPosition() const;
        
        /**
         * Retrieves an immutable reference to the normal attribute of this Vertex
         * 
         * @return a mutable reference to the normal attribute of this Vertex
         * 
         */
        const Vector<T, 3>& getNormal() const;
        
        /**
         * Retrieves an immutable reference to the texture coordinate attribute of this Vertex
         * 
         * @return a mutable reference to the texture coordinate attribute of this Vertex
         * 
         */
        const Point<T, 2>& getTexCoord() const;
        
        /**
         * Sets the position attribute of this Vertex
         * 
         * @param position the new position attribute
         * 
         */
        void setPosition(const Point<T, 3>& position);
        
        /**
         * Sets the normal attribute of this Vertex
         * 
         * @param normal the new normal attribute
         * 
         */
        void setNormal(const Vector<T, 3>& normal);
        
        /**
         * Sets the texture coordinate attribute of this Vertex
         * 
         * @param texCoord the new texture coordinate attribute
         * 
         */
        void setTexCoord(const Point<T, 2>& texCoord);
        
        /**
         * Sets the position attribute of this Vertex
         * 
         * @param position the new position attribute
         * 
         */
        void setPosition(Point<T, 3>&& position);

        /**
         * Sets the normal attribute of this Vertex
         * 
         * @param normal the new normal attribute
         * 
         */
        void setNormal(Vector<T, 3>&& normal);

        /**
         * Sets the texture coordinate attribute of this Vertex
         * 
         * @param texCoord the new texture coordinate attribute
         * 
         */
        void setTexCoord(Point<T, 2>&& texCoord);
                
    };
}

#include "Vertex.inl"

namespace midnight
{
    typedef Vertex<float> Vertex32F;
    typedef Vertex<double> Vertex64F;
}

#endif
