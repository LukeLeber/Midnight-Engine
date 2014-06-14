#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

#include <cstdint>
#include <vector>

namespace midnight
{
    class Heightmap
    {
        std::size_t width;
        std::size_t height;
        
        std::vector<unsigned char> samples;
        
        std::size_t scale;
        
        typedef typename std::vector<unsigned char>::allocator_type allocator_type;
        typedef typename std::vector<unsigned char>::const_iterator const_iterator;
        typedef typename std::vector<unsigned char>::const_pointer const_pointer;
        typedef typename std::vector<unsigned char>::const_reference const_reference;
        typedef typename std::vector<unsigned char>::const_reverse_iterator const_reverse_iterator;
        typedef typename std::vector<unsigned char>::difference_type difference_type;
        typedef typename std::vector<unsigned char>::iterator iterator;
        typedef typename std::vector<unsigned char>::pointer pointer;
        typedef typename std::vector<unsigned char>::reference reference;
        typedef typename std::vector<unsigned char>::reverse_iterator reverse_iterator;
        typedef typename std::vector<unsigned char>::size_type size_type;
        typedef typename std::vector<unsigned char>::value_type value_type;
        
      public:

        iterator begin()
        {
            return samples.begin();
        }
        
        iterator end()
        {
            return samples.end();
        }
        
        const_iterator begin() const
        {
            return samples.begin();
        }
        
        const_iterator end() const
        {
            return samples.end();
        }
        
        Heightmap(std::size_t width, std::size_t height, const std::vector<unsigned char>& samples, std::size_t scale = 1) : 
            width(width), 
            height(height), 
            samples(samples), 
            scale(scale)
        {

        }
        
        Heightmap(std::size_t width, std::size_t height, std::vector<unsigned char>&& samples, std::size_t scale = 1) : 
            width(width), 
            height(height), 
            samples(std::move(samples)), 
            scale(scale)
        {

        }
        
        std::size_t getWidth() const
        {
            return width;
        }
        
        std::size_t getHeight() const
        {
            return height;
        }

        reference operator[](std::size_t index)
        {
            return samples[index];
        }
        
/*        template<typename T>
        T interpolate(const Point<T, 2>& point)
        {
            return T();
        }*/
    };    
}

#endif
