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

#include "IllegalArgumentException.hpp"


namespace midnight
{
    inline IllegalArgumentException::IllegalArgumentException(const std::string& message) noexcept : 
        GLException(message)
    {
        
    }
    
    inline IllegalArgumentException::IllegalArgumentException(std::string&& message) noexcept : 
        GLException(std::move(message))
    {
        
    }
}