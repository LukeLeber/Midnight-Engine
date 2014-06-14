/**
 * Internal Utility Header - do not include this in user code!
 * 
 * Internal files make no guarantee of backward-compatibility and may break user-code if used directly.
 * 
 * 
 * dynamic_warn is roughly the equivalent of a non-fatal assertion
 * 
 */



#ifndef DYNAMIC_WARN_HPP
#    define DYNAMIC_WARN_HPP

/// Puke if clang is not used
static_assert(__clang__, "Your compiler is not supported.");

#    if defined(OPENGL_RUNTIME_WARNINGS)
#        include <iostream>
#        define dynamic_warn(message) \
                std::cout << \
                        "warning triggered in " \
                        << __FILE__ \
                        << " line " \
                         << __LINE__ \
                        << ": " \
                        << message \
                << std::endl
#        define conditional_warn(condition, message) \
                if(condition) dynamic_warn(message)
#    else
#        define dynamic_warn(message) do { } while(false)
#        define conditional_warn(condition, message) do {} while(false)
#    endif
#endif