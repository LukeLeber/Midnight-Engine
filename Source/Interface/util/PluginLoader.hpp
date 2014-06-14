#ifndef PLUGIN_LOADER_HPP
#define PLUGIN_LOADER_HPP

#include "Platform.hpp"

#if defined(MIDNIGHT_WINDOWS)
#   error Support Coming Soon!
#elif defined(MIDNIGHT_LINUX)
#   include "PluginLoader_Linux.hpp"
#elif defined(MIDNIGHT_MAC)
#   error Unsupported Platform
#endif

#endif