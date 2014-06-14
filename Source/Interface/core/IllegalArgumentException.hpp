/**
 * This file is protected under the KILLGPL License.
 * 
 * For more information visit www.midnightengine.com/license
 *  
 * @version 1.1
 *      2/04/2014 - initial draft
 *      3/27/2014 - API & Documentation Enhancement
 * 
 * @since 1.0
 * 
 * @author Luke A. Leber <LukeLeber@gmail.com>
 * 
 */
#ifndef ILLEGAL_ARGUMENT_EXCEPTION_1_22_2014_HPP
#define ILLEGAL_ARGUMENT_EXCEPTION_1_22_2014_HPP

#include "BuildConstraints.hpp"
#include "GLException.hpp"

namespace midnight
{

class IllegalArgumentException : public GLException
{
  public:
    
    /**
     * Constructs an IllegalArgumentException with the provided message
     * 
     * @param message A brief message describing the exceptional condition
     * 
     */
    explicit IllegalArgumentException(const std::string& message = "") noexcept;
    
    /**
     * Constructs an IllegalArgumentException with the provided message
     * 
     * @param message A brief message describing the exceptional condition
     * 
     */
    explicit IllegalArgumentException(std::string&& message) noexcept;
    
   /**
     * Copy-constructs an IllegalArgumentException
     * 
     * @param other the IllegalArgumentException to copy
     * 
     */
    IllegalArgumentException(const IllegalArgumentException& other) = default;
    
    /**
     * Move-constructs an IllegalArgumentException
     * 
     * @param other the IllegalArgumentException to move
     * 
     * @note Remember that accessing a moved resource from the calling code is an error!
     * 
     */
    IllegalArgumentException(IllegalArgumentException&& other) = default;


    /**
     * Copy-assigns an IllegalArgumentException
     * 
     * @param other the IllegalArgumentException to copy
     * 
     * @return *this
     * 
     */
    IllegalArgumentException& operator=(const IllegalArgumentException& other) = default;
    
    /**
     * Move-assigns an IllegalArgumentException
     * 
     * @param other the IllegalArgumentException to move
     * 
     * @return *this
     * 
     * @note Remember that accessing a moved resource from the calling code is an error!
     * 
     */
    IllegalArgumentException& operator=(IllegalArgumentException&& other) = default;

    /**
     * Default virtual destructor - no special cleanup is required
     * 
     */
    virtual ~IllegalArgumentException() noexcept = default;
};

}

#include "IllegalArgumentException.inl"

#endif