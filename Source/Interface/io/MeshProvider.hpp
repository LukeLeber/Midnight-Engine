#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

#include <memory>
#include <string>
#include <vector>

#include "Mesh.hpp"

namespace midnight
{
namespace spi
{

    class MeshProvider
    {
      public:
        virtual bool isLoadableExtension(const std::string& extension) const noexcept = 0;
        virtual midnight::Mesh loadMesh(const std::string& file) = 0;
        virtual ~MeshProvider() = default;
    };

    std::vector<std::shared_ptr<MeshProvider>> meshProviders;
}
    
namespace io
{     
    midnight::Mesh loadMesh(const std::string& fileName)
    {
        std::string extension = fileName.substr(fileName.find_last_of("."));
        for(auto provider : spi::meshProviders)
        {
            if(provider->isLoadableExtension(extension))
            {
                return provider->loadMesh(fileName);
            }
        }
        throw std::runtime_error("No known provider for " + extension + " format");
    }

}
}

#endif
