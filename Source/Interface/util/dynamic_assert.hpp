/**
 * Internal Utility Header:
 *	Depending on settings, framework will either use assertions, throw 
 *	exceptions, or do no error checking on user input.
 * 
 */

/// Puke if clang is not used
static_assert(__clang__, "Your compiler is not supported.");

#define OPENGL_RUNTIME_ASSERTIONS

#ifndef DYNAMIC_ASSERT_HPP
#    define DYNAMIC_ASSERT_HPP
#    if defined(MIDNIGHT_RUNTIME_ASSERTIONS)
#       include <iostream>
#       define dynamic_assert(expression, message) \
        do\
        {\
            if(!(expression))\
            {\
                std::cerr << "dynamic_assertion \"" #expression "\" failed in " << __FILE__\
                          << " line " << __LINE__ << ": " << message << std::endl;\
                std::exit(EXIT_FAILURE);\
            }\
        } while (false)
#    else
#        define dynamic_assert(expression, message) do { } while(false)
#    endif
#endif
