/**
 * This file is protected under the KILLGPL License.
 * 
 * For more information visit www.midnightengine.com/license
 *  
 * @version 1.1
 *      1/22/2014 - initial draft
 *      3/26/2014 - API & Documentation Enhancement
 * 
 * @since 1.0
 * 
 * @author Luke A. Leber <LukeLeber@gmail.com>
 * 
 */
#ifndef GL_EXCEPTION_1_22_2014_HPP
#define GL_EXCEPTION_1_22_2014_HPP

#include "BuildConstraints.hpp"

#include <stdexcept>
#include <string>

namespace midnight
{

/**
 * @brief The base class for all exceptions originating from failed calls to OpenGL
 * 
 * In addition to the standard exception interface, GLExceptions also attempt to 
 * capture the opengl state at the time of their creation.  This "Freeze 
 * Frame" data contains the raw error message provided by the opengl 
 * implementation and is provided on a best attempt basis, and as such all 
 * exceptions may not contain freeze-frame data.
 * 
 * @see std::runtime_error
 * 
 */
class GLException : public std::runtime_error
{
    /// The raw message captured from the underlying opengl implementation
    std::string freezeFrameData;
    
  public:

    /**
     * Constructs a GLException with the provided message
     * 
     * @param message A brief message describing the exceptional condition
     * 
     */
    explicit GLException(const std::string& message = "") noexcept;

    /**
     * Retrieves the freeze-frame data of this GLException
     * 
     * @return the freeze-frame data of this GLException
     * 
     * @note The string returned may be empty if no freeze-frame data was available.
     * 
     */
    const std::string& getFreezeFrameData() const noexcept;

    /**
     * Copy-constructs a GLException
     * 
     * @param other the GLException to copy
     * 
     */
    GLException(const GLException& other) = default;
    
    /**
     * Move-constructs a GLException
     * 
     * @param other the GLException to move
     * 
     * @note Remember that accessing a moved resource from the calling code is an error!
     * 
     */
    GLException(GLException&& other) = default;


    /**
     * Copy-assigns a GLException
     * 
     * @param other the GLException to copy
     * 
     * @return *this
     * 
     */
    GLException& operator=(const GLException& other) = default;
    
    /**
     * Move-assigns a GLException
     * 
     * @param other the GLException to move
     * 
     * @return *this
     * 
     * @note Remember that accessing a moved resource from the calling code is an error!
     * 
     */
    GLException& operator=(GLException&& other) = default;

    /**
     * Default virtual destructor - no special cleanup is required
     * 
     */
    virtual ~GLException() noexcept = default;
};

}

#    include "GLException.inl"

#endif
