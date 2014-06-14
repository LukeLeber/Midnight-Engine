#ifndef HASH_CODE_HPP
#    define HASH_CODE_HPP

#include <string>

/**
 * Built upon Java's implementation of generating a hash from a string, the hashes produced by this function 
 * are not guaranteed to be unique, but encountering a hash collision should be quite rare.  Internally, this 
 * function is used in conjunction with switches in order to compare string literals.  Being a constant expression, 
 * the individual cases should be evaluated at compile-time, replacing the string literals with integral values.
 * 
 * @param string the c-string to hash
 * 
 * @return a hash value calculated from the provided c-string
 * 
 */
template<typename T>
constexpr std::size_t hashCode(const T* string)
{
    return *string ? hashCode(string + 1) * 31 ^ static_cast<unsigned long>(*string) : 37;
}

/**
 * Built upon Java's implementation of generating a hash from a string, the hashes produced by this function 
 * are not guaranteed to be unique, but encountering a hash collision should be quite rare.  Internally, this 
 * function is used in conjunction with switches in order to compare string literals.  Being a constant expression, 
 * the individual cases should be evaluated at compile-time, replacing the string literals with integral values.
 * 
 * @param string the std::string to hash
 * 
 * @return a hash value calculated from the provided std::string
 * 
 */
template<typename T>
constexpr std::size_t hashCode(const std::basic_string<T>& string)
{
    return hashCode(string.c_str());
}

#endif
