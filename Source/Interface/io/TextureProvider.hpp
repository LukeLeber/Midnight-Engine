#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <string>
#include <vector>

#include "Heightmap.hpp"
#include "Texture.hpp"
#include <memory>
#include <stdexcept>

namespace midnight
{
namespace spi
{
    
    /**
     * The service provider interface for all Image processing
     * 
     * TODO: Docs
     */
	class TextureProvider
	{
	  public:
		virtual bool isLoadableExtension(const std::string& extension) const noexcept = 0;
		virtual midnight::Texture loadTexture(const std::string& file) = 0;
		virtual midnight::Heightmap loadHeightmap(const std::string& file) = 0;
		virtual ~TextureProvider() = default;
	};
    
    std::vector<std::shared_ptr<TextureProvider>> textureProviders;
}
namespace io
{


midnight::Heightmap loadHeightmap(const std::string& fileName)
{
    std::string extension = fileName.substr(fileName.find_last_of("."));
    for(auto provider : midnight::spi::textureProviders)
    {
        if(provider->isLoadableExtension(extension))
        {
            return provider->loadHeightmap(fileName);
        }
    }
    throw std::runtime_error("No known provider for " + extension + " format");
}

    midnight::Texture loadTexture(const std::string& fileName)
    {
        std::string extension = fileName.substr(fileName.find_last_of("."));
        for(auto provider : midnight::spi::textureProviders)
        {
            if(provider->isLoadableExtension(extension))
            {
                return provider->loadTexture(fileName);
            }
        }
        throw std::runtime_error("No known provider for " + extension + " format");
    }
}
}

#endif