#ifndef SERVICE_PROVIDERS_HPP
#define SERVICE_PROVIDERS_HPP

#include "TextureProvider.hpp"

namespace midnight
{
    namespace spi
    {
        enum class ServiceProviderType
        {
            TEXTURE_PROVIDER,
            MESH_PROVIDER
        };
        
        template<typename T>
        void loadProviders(const std::string& library, std::vector<std::shared_ptr<T>>& providers)
        {
            auto loaded = std::shared_ptr<std::vector<T*>>(midnight::internal::Library(library).loadSymbol<std::vector<T*>*>("loadProviders")());
            for(auto provider : *loaded)
            {
                providers.push_back(std::shared_ptr<T>(provider));
            }
        }
    }


}

#endif