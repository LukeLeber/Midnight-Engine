#ifndef PLUGIN_LOADER_LINUX
#define PLUGIN_LOADER_LINUX

#include <dlfcn.h>
#include <functional>
#include "ResourceException.hpp"

namespace midnight
{
    namespace internal
    {
        class Library
        {
            void* handle;
            
          public:
            
            Library(const std::string& library) :
                handle(dlopen(library.c_str(), RTLD_LAZY | RTLD_NODELETE))
            {
                /// Specification indicates that dlopen returns NULL on failure...
                if(handle == NULL)
                {
                    throw midnight::ResourceException(dlerror());
                }
            }
            
            template<typename RET, typename... ARGS>
            typename std::function<RET(ARGS...)> loadSymbol(const std::string& name)
            {
                typedef RET (*Signature)(ARGS...);
                return std::function<RET(ARGS...)>((reinterpret_cast<Signature>(dlsym(handle, name.c_str()))));
            }
            
            ~Library()
            {
                dlclose(handle);
            }
        };
    }
}

#endif
