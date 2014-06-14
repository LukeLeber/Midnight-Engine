/**
 * 
 * The purpose of this file is to centralize any and all permanent constraints pertaining to building this library.
 * 
 */
#ifndef BUILD_CONSTRAINTS_HPP
#define BUILD_CONSTRAINTS_HPP

/// These constraints will never be lifted.
#ifndef __cplusplus
#   error This source may not be built with a C compiler.
#elif __cplusplus < 201103L
#   error This source may not be built with a C++ compiler that does not conform to the C++11 Standard
#endif//__cplusplus

/// This assertion is in place to explicitly warn those compiling with other compilers.
/// Clang is the only officially supported compiler.  Remove at your own risk.
static_assert(__clang__, "Your compiler is not supported.");

#endif